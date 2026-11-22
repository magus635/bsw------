"""DaVinci 导入 CLI 工具。

用法：
  python -m autosar_configurator.core.davinci_import_cli \\
    --project <.dpa> \\
    --output <dir> \\
    [--derivative-uuid <uuid>] \\
    [--include-resources]
"""

import argparse
import logging
import sys
from pathlib import Path
from typing import List, Optional

from autosar_configurator.core.davinci_importer import (
    DaVinciProject,
    SipScanner,
    SipMerger,
    SipPackageWriter,
    McalResourceExtractor,
)

logger = logging.getLogger(__name__)


class DaVinciImportCLI:
    """命令行工具：从 DaVinci 工程导入 BSW 模块和 MCAL 资源。"""

    def __init__(self, verbose: bool = False):
        """Initialize CLI.

        Args:
            verbose: Enable verbose logging
        """
        self.verbose = verbose
        if verbose:
            logging.basicConfig(level=logging.DEBUG)
        else:
            logging.basicConfig(level=logging.INFO)

    def run(self, args: Optional[List[str]] = None) -> int:
        """Run the import process.

        Args:
            args: Command-line arguments (defaults to sys.argv[1:])

        Returns:
            Exit code (0 for success)
        """
        parser = self._build_parser()
        parsed = parser.parse_args(args)

        try:
            # Parse DaVinci project
            logger.info("Loading DaVinci project: %s", parsed.project)
            davinci = DaVinciProject.from_file(Path(parsed.project))
            logger.info("Found SIP root: %s", davinci.sip_root)

            # Create output directory
            output_dir = Path(parsed.output)
            output_dir.mkdir(parents=True, exist_ok=True)
            logger.info("Output directory: %s", output_dir)

            # Scan SIP modules (with derivative UUID filtering if available)
            effective_uuid = parsed.derivative_uuid or davinci.derivative_uuid
            logger.info("Scanning SIP modules (derivative_uuid=%s)...", effective_uuid or "none")
            scanner = SipScanner(davinci.sip_root)
            all_modules = scanner.scan_all_modules(derivative_uuid=effective_uuid)
            logger.info("Found %d module(s): %s", len(all_modules), ", ".join(sorted(all_modules)))

            # Import each module
            imported = 0
            skipped_no_def = 0
            for module_name in sorted(all_modules):
                files = all_modules[module_name]

                # Collect definition and config files separately
                for pkg_dir_name, pkg_mod_name, group_files in SipScanner.partition_module_files(module_name, files):
                    def_files = [f for f in group_files if f.role == "def"]
                    cfg_files = [f for f in group_files if f.role == "config"]

                    if not def_files and not cfg_files:
                        logger.warning("  Skipping %s: no files", pkg_dir_name)
                        continue

                    # Build merged definition document
                    all_files = def_files + cfg_files
                    def_content = SipMerger.merge_definition(all_files, pkg_mod_name)

                    if not def_content and not def_files:
                        logger.warning("  Skipping %s: no definition found", pkg_dir_name)
                        skipped_no_def += 1
                        continue

                    # Extract value collections (Pre/Rec) using IMPL-guided role assignment
                    value_docs = SipMerger.extract_value_collections(all_files, pkg_mod_name)
                    pre_config = value_docs.get("pre")
                    rec_config = value_docs.get("rec")
                    impl_meta = SipMerger.extract_bsw_implementation_metadata(all_files)
                    source_paths = [str(f.path) for f in all_files]

                    logger.info("Importing %s... def=%s pre=%s rec=%s values=%s",
                                pkg_dir_name,
                                "✓" if def_content else "✗",
                                "✓" if pre_config else "—",
                                "✓" if rec_config else "—",
                                "✓" if value_docs.get("values") else "—")

                    # Write package
                    try:
                        pkg_dir = SipPackageWriter.write_package(
                            module_name=pkg_mod_name,
                            definition_content=def_content or b"",
                            pre_config=pre_config,
                            rec_config=rec_config,
                            output_dir=output_dir,
                            source_files=source_paths,
                            impl_metadata=impl_meta,
                            package_dir_name=pkg_dir_name,
                        )
                        imported += 1
                    except Exception as e:
                        logger.error("  Error writing package for %s: %s", pkg_dir_name, e)

            logger.info("Imported %d module(s), skipped %d (no definition)", imported, skipped_no_def)

            # Optional: extract MCAL resources
            if parsed.include_resources:
                logger.info("Extracting MCAL resources...")
                extractor = McalResourceExtractor(davinci.sip_root)
                all_resources = extractor.extract_all_chips_resources()
                logger.info("Found %d chip(s): %s", len(all_resources), ", ".join(sorted(all_resources)))

                for chip_name in sorted(all_resources):
                    yaml_file = output_dir / f"resources_{chip_name}.yaml"
                    logger.info("  Exporting %s to %s", chip_name, yaml_file)
                    extractor.extract_and_generate_yaml(chip_name, yaml_file)

            logger.info("Done")
            return 0

        except Exception as e:
            logger.error("Import failed: %s", e, exc_info=self.verbose)
            return 1

    @staticmethod
    def _build_parser() -> argparse.ArgumentParser:
        """Build argument parser.

        Returns:
            ArgumentParser configured for DaVinci import
        """
        parser = argparse.ArgumentParser(
            prog="davinci-import",
            description="Import BSW modules and MCAL resources from DaVinci projects"
        )

        parser.add_argument(
            "--project", "-p",
            required=True,
            help="DaVinci project file (.dpa)"
        )

        parser.add_argument(
            "--output", "-o",
            required=True,
            help="Output directory for imported modules"
        )

        parser.add_argument(
            "--derivative-uuid",
            help="Optional derivative UUID for chip filtering (from DerivativeMapping)"
        )

        parser.add_argument(
            "--include-resources", "-r",
            action="store_true",
            help="Also extract MCAL resources to YAML files"
        )

        parser.add_argument(
            "--verbose", "-v",
            action="store_true",
            help="Verbose logging"
        )

        return parser


def main():
    """Entry point for command-line execution."""
    cli = DaVinciImportCLI(verbose="--verbose" in sys.argv or "-v" in sys.argv)
    sys.exit(cli.run())


if __name__ == "__main__":
    main()

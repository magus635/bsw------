"""Base snapshot storage: the accepted baseline as an arxml file plus its hash (design §6.5).

The tool keeps the baseline the user last accepted in ``config/base/<Module>.arxml`` — the
same format as the live configuration — and records its hash in ``.dpa``
(``modules[].base_hash``). ``write_base`` returns that hash; ``read_base`` checks it before
parsing, so a snapshot someone edited by hand, and a snapshot that is gone, both end as
``None``:

- the file is missing — a project migrated without a snapshot;
- the hash differs — the snapshot is no longer what the user accepted;
- the file does not parse — a damaged file.

``None`` means "treat this module as first enable" (§6.5): the caller passes it on to
``three_way_merge`` as ``base=None``, which keeps every non-Pre value and lets only Pre
change the configuration. Refusing the file here, rather than trusting it, is what keeps a
half-written snapshot from silently becoming the merge base.

Where the snapshot lives is the caller's business: this module takes a path and does no
directory logic. It does create the parent directory when it is missing, so the first
``write_base`` after ``add module`` cannot fail on a project that never had ``config/base``.
"""
import hashlib
import logging
from pathlib import Path
from typing import Optional

from lxml import etree

from ..model.configuration_model import EcucModuleConfiguration
from ..parser.arxml_parser import ArxmlParser
from ..serializer.ecuc_serializer import EcucValueSerializer

__all__ = ["write_base", "read_base", "hash_file"]

_log = logging.getLogger(__name__)

_HASH_PREFIX = "sha256:"


def hash_file(path: Path) -> str:
    """``"sha256:<hex>"`` of a file's bytes, the format ``.dpa`` records."""
    return _HASH_PREFIX + hashlib.sha256(Path(path).read_bytes()).hexdigest()


def write_base(path: Path, config: EcucModuleConfiguration) -> str:
    """Write ``config`` to ``path`` as arxml and return the hash of the file written.

    Args:
        path: The snapshot file (``config/base/<Module>.arxml``); its directory is created
            when missing.
        config: The baseline to store (``compose_base``'s result, after the merge is
            accepted).

    Returns:
        ``"sha256:<hex>"`` of the file's bytes, for ``modules[].base_hash``. The hash is
        computed from the file as written, not from the object, so ``read_base`` verifies
        exactly the bytes the project will load.
    """
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    EcucValueSerializer().serialize_to_file(config, path)
    return hash_file(path)


def read_base(path: Path, expected_hash: Optional[str]) -> Optional[EcucModuleConfiguration]:
    """Read a base snapshot, if it is the one the project recorded.

    Args:
        path: The snapshot file.
        expected_hash: ``modules[].base_hash`` from ``.dpa``, ``"sha256:<hex>"``. ``None``
            (a project that never recorded one) is treated like a missing snapshot.

    Returns:
        The first configuration in the file, or ``None`` when the file is missing, its hash
        does not match, or it cannot be parsed. Those three are ordinary states — a migrated
        project, a hand-edited snapshot, a damaged file — so they are logged as warnings and
        never raised; the caller merges with ``base=None``. A file that parses but holds no
        ``ECUC-MODULE-CONFIGURATION-VALUES`` is treated the same way: a snapshot without a
        configuration can only have been damaged.
    """
    path = Path(path)
    if not path.is_file():
        _log.warning("基线快照不存在，按旧工程迁移处理：%s", path)
        return None

    if expected_hash is None:
        _log.warning("工程未记录基线快照哈希，按旧工程迁移处理：%s", path)
        return None

    actual = hash_file(path)
    if actual.lower() != expected_hash.strip().lower():
        _log.warning("基线快照哈希不符，按旧工程迁移处理：%s（记录 %s，实际 %s）",
                     path, expected_hash, actual)
        return None

    try:
        tree = etree.parse(str(path), etree.XMLParser(resolve_entities=False, no_network=True))
        configs = ArxmlParser().parse_all_module_configurations(tree.getroot())
    except (etree.XMLSyntaxError, OSError, ValueError, TypeError) as exc:
        _log.warning("基线快照解析失败，按旧工程迁移处理：%s（%s）", path, exc)
        return None

    if not configs:
        _log.warning("基线快照中没有模块配置，按旧工程迁移处理：%s", path)
        return None
    if len(configs) > 1:
        _log.warning("基线快照含 %d 个模块配置，只取第一个：%s", len(configs), path)
    return configs[0]

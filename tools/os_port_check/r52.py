"""Cortex-R52 regression: the kernel objects must not change when only the SC300 port is touched.

r52-save writes the objects of the current kernel; after a kernel change r52-compare builds them
again and compares byte for byte.  The generated configuration is the Os code of T1 as configured.
"""
import shutil
import tempfile
from pathlib import Path
from typing import List, Optional

from . import common
from .t1_example import generate_t1

FLAGS = ["-mcpu=cortex-r52", "-mfpu=neon-fp-armv8", "-mfloat-abi=hard", "-O2", "-std=gnu99",
         "-ffunction-sections", "-fdata-sections", "-D__HIGHTEC__", "-w"]


def build(kernel: Path, t1: Path, sdk: Path, out: Path, work: Optional[Path] = None) -> List[str]:
    """Compile the kernel and the generated config of T1 for the R52 into out; returns failure messages"""
    own_work = work is None
    work = work or Path(tempfile.mkdtemp(prefix="os_port_r52_"))
    try:
        config = generate_t1(t1, work / "t1", work / "gen")
        # the generated config first (as in the project), but not its own copy of orti/: the kernel's is used
        dirs = common.subdirs(config, skip=("orti",)) + common.subdirs(kernel) + common.subdirs(sdk)
        includes = ["-I", str(common.STUBS_R52)] + common.include_args(dirs)
        if out.exists():
            shutil.rmtree(out)
        # Only the kernel sources: the generated config supplies the headers. Compiling T1's generated
        # .c files for the R52 fails for reasons that have nothing to do with the kernel (the IOC callout
        # lacks its data type header, an ISR without trigger method).
        jobs = [(src, out / common.object_name("k", kernel, src)) for src in common.sources(kernel, "*.c")]
        return common.compile_files(FLAGS, includes, jobs)
    finally:
        if own_work:
            shutil.rmtree(work, ignore_errors=True)

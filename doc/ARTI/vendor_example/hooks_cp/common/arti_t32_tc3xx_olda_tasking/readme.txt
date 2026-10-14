This directory contains the ARTI trace implementation to be used
with the SRI bus trace of TriCore AURIX second generation (TC3xx)
on OLDA memory. The files are prepared for Tasking compiler.

Prerequisites:
- MCDS available (emulation chip)
- A trace sink must be available, either onchip or with external hardware 
  (e.g. TRACE32 CombiProbe or PowerTrace)
Advantages:
- Very low impact (both in timing and in code size)
- With external trace hardware: very long recording time
- Tracing of all cores in parallel (in contrast to data trace, see "Caveats" there).
Disadvantages:
- Core must include MCDS component.
- Onchip: Special core with trace buffer necessary.
- Offchip: Extra tracehardware necessary.

The OLDA addresses of the ARTI trace variables need to be added to your linker script.
See the example snippet in Tasking_TriCore.lsl. 

See also the script "arti_sri_trace.cmm" in the scripts directory.

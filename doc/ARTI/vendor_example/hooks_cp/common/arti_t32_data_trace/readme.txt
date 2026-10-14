This directory contains the ARTI trace implementation to be used
with the data trace capability of TRACE32.

This method uses a pure data trace.
Prerequisites:
- The CPU must provide the capability to trace write accesses to variables.
- A trace sink must be available, either on chip or with external hardware 
  (e.g. TRACE32 CombiProbe or PowerTrace)
Advantages:
- Very low impact (both in timing and in code size)
- With external trace hardware: very long recording time
Disadvantages:
- Special core with trace capabilities neccesary.
- Onchip: Special core with onchip trace buffer necessary.
- Offchip: Special trace adapter and extra hardware necessary.
Caveats:
- TriCore can only trace a subset of its cores!

To trace *only* the ARTI events, execute these commands in TRACE32:

Break.Set arti_os_trace  /Write /TraceEnable
Break.Set arti_rte_trace /Write /TraceEnable

To trace the ARTI events together with program trace, execute these commands in TRACE32:

Break.Set arti_os_trace  /Write /TraceData
Break.Set arti_rte_trace /Write /TraceData

See also the script "arti_data_trace.cmm" in the scripts directory.

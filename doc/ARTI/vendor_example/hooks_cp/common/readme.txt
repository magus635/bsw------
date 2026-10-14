This directory contains various different implementations of the ARTI trace 
to be used with TRACE32 tracing technologies.

Please see also the readme.txt files in the subdirectores!

1) arti_t32_data_trace
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

2) arti_t32_logger
This method saves the trace in a pure software controlled memory buffer on the target.
Prerequisites:
- Much spare memory left for trace buffer
- Some spare computing time left for buffer handling
Advantages:
- No special hardware (onchip or offchip) necessary
- Works on every CPU
Disadvantages:
- Big target memory based buffer needed
- Some computing overhead for managing the buffers

3) arti_t32_fdx
This method saves the trace in a small software controlled memory buffer on the target
and transfers the trace data during runtime to the host.
Prerequisites:
- Spare memory left for trace buffer on target
- Some spare computing time left for buffer handling and transfer
- If memory is not accessible while CPU is running, *MUCH* spare 
  scheduling time left for buffer transfer
Advantages:
- No special hardware (onchip or offchip) necessary
- Works on every CPU
- (Almost) unlimited tracing time.
Disadvantages:
- Target memory based buffer needed
- Some computing overhead for managing the buffers
- If memory is not accessible while CPU is running, *MUCH* scheduling 
  time overhead for buffer transfer

4) arti_t32_tc2xx_lmu_*
This method uses the SRI bus trace of TriCore AURIX first generation (TC2xx)
on LMU memory to record the trace events.
Prerequisites:
- MCDS available (emulation chip)
- Free LMU memory space available
- A trace sink must be available, either onchip or with external hardware 
  (e.g. TRACE32 CombiProbe or PowerTrace)
Advantages:
- Very low impact (both in timing and in code size)
- With external trace hardware: very long recording time
- Tracing of all cores in parallel (in contrast to data trace, see "Caveats" there).
Disadvantages:
- Core must include MCDS component.
- Onchip: Special core with trace buffer necessary.
- Offchip: Extra trace hardware necessary.

5) arti_t32_tc3xx_olda_*
This method uses the SRI bus trace of TriCore AURIX second generation (TC3xx)
on OLDA memory to record the trace events.
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

6) arti_t32_tc4x_olda
OLDA on TriCore AURIX third generation (TC4x) is identical to TC3xx. 
Use the configuration and directories of TriCore AURIX second generation (TC3xx).

This directory contains the ARTI trace implementation to be used
with the FDX Trace capability of TRACE32.

This method collects the trace in a small buffer on the target and
transfers the trace data during runtime to the host.
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

Additionally to the global installation instructions:

Edit arti_t32_fdx.h:

1. Adjust "ARTI_GETCOREID" to the most efficient way to get the current core ID
   in your system - or keep the default.
2. Adjust "ARTI_TIMERINIT" to initialize the timer, if necessary
3. Adjust "ARTI_TIMERGET" to return a global, free-running, 32bit-bit time stamp.

Edit arti_t32_fdx.c:

4. Adjust "T32_ARTI_SPINLOCKINIT", "ARTI_SPINLOCKGET" and "ARTI_SPINLOCKRELEASE" 
   to initialize, get or release a spinlock based on an uint32. 
   Note: this will be called in OS and RTE environment.
5. If necessary, adjust "T32_FDX_COPY" to fit to your systems memcpy function.

Edit cmm_scripts\arti_fdx.cmm:

6. Set the "&timerfrequency" value

Please note that the FDX trace feature is first available after "Arti_Init()" was called
in your application.

If the events happen too often and overcharge the FDX bandwith, the buffer on the target
runs full. In this case, the target stalls until TRACE32 reads out the data.
These stalls can take 10 to 100 milliseconds and therefore make a timing measurement
most likely unusable. Use the command "PRINT FDX.TargetSTALLS()" to check, if a trace
collection contains stalls and discard the trace if the time delays are problematic.

See also the script "arti_fdx.cmm" in the scripts directory.

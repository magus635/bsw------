This directory contains the ARTI trace implementation to be used
with the LOGGER capability of TRACE32.

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

Additionally to the global installation instructions:

Edit arti_t32_logger.h:

1. Adjust T32_LOGGER_SIZE.
   The bigger the size, the longer you can trace, but the more memory is used.
2. Adjust T32_LOGGER_SIZE_PER_CORE
   If unsure, keep the default.
3. Adjust T32_CORE_NUMBER to the number of used cores in your application.
4. Adjust "ARTI_GETCOREID" to the most efficient way to get the current core ID 
   in your system - or keep the default.
5. Adjust "ARTI_TIMERINIT" to initialize the timer, if necessary
6. Adjust "ARTI_TIMERGET" to return a global, free-running, 32bit-bit time stamp.
7. Set the "&timerfrequency" value in Lauterbach\cmm_scripts\arti_logger.cmm

Please note that the LOGGER feature is first available after "Arti_Init()" was called
in your application.

See also the script "arti_logger.cmm" in the scripts directory.

To start recording, set LOGGER.Arm, to stop recording, set LOGGER.OFF. 
If no dual-port access is available, halt the target before executing these commands. 
If dual-port access is available, LOGGER.Mode E ON allows controlling the logger while
the target is running.
LOGGER.AutoARM ON will automatically set the LOGGER to Arm on "Go" and to OFF on "Break".
Before inspecting (LOGGER.List) and exporting (Trace.EXPORT.ARTI) the logger contents, 
*always* halt the target (Break). This allows the debugger to take full control over 
the target based buffers.

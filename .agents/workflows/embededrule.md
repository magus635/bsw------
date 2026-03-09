---
description: ARM RISC-V MCU RTOS 驱动开发
---

Before writing embedded code:
- check MCU datasheet
- verify register map
- confirm peripheral clock

Never invent registers.
Always verify against datasheet.

Prefer bare-metal implementation
unless user asks for HAL.
# Os 内核移植检查（Cortex-R52 / SC300）

内核（`tr002_THA6_OS_Project/Os`）和 Os 插件不在本仓库里。这套工具在改内核时做两件事：

1. **R52 不能变**：改 SC300 相关代码后，R52 的内核目标文件必须逐字节不变。
2. **SC300 能跑**：用 T1 裁出一份单核示例，和内核一起编译链接，在 QEMU 的 Cortex-M3 上运行 16 步检查。

在仓库根目录运行，路径用参数给出，或设环境变量：

| 参数 | 环境变量 | 含义 |
|---|---|---|
| `--kernel` | `OS_KERNEL_DIR` | 内核的 `Os` 目录 |
| `--t1` | `OS_T1_DIR` | T1 工程目录（只读，工具先复制一份再改） |
| `--sdk` | `OS_R52_SDK_DIR` | R52 的 SDK 目录，默认 `<内核>/../SDK`（只用于 R52） |
| | `ARM_NONE_EABI_GCC` | `arm-none-eabi-gcc`，默认在 PATH 里找，或 Arm GNU Toolchain 13.2 的安装位置 |
| | `QEMU_SYSTEM_ARM` | `qemu-system-arm`，默认在 PATH 里找，或 `C:/Program Files/qemu` |

## SC300：编译、链接、在 QEMU 上运行

```
python -m tools.os_port_check sc300 [--work 目录] [--warn]
```

退出码 0 表示通过。`--work` 保留生成的代码、目标文件、`test.elf` 和 `test.map`；`--warn` 打开编译器警告。

做了什么：

1. 复制 T1，去掉 MCAL 模块、第 2 个核、内存布局和 IOC，选 `SC300` 芯片，生成 Os 代码（`t1_example.py`）。
2. 用 `-mcpu=cortex-m3 -D__OS_SUPPORT_CORTEX_M3__` 编译内核（含 `Os_context_exception_cm3.s`）、生成的配置、测试程序和启动文件，链接（`target_sc300/`）。
3. 在 QEMU `mps2-an385` 上运行，输出走半主机；最后一行是 `RESULT: PASS` 才算通过。

测试程序（`target_sc300/test_app.c`）的 16 步：

| 步骤 | 检查什么 |
|---|---|
| 1–2 | 最高优先级的自启动任务先运行；激活低优先级任务不会抢占 |
| 3–6 | Cat2 ISR 打断任务；更高优先级的 ISR 嵌套进来；依次返回 |
| 7–8 | 其余自启动任务和被激活的任务依次运行 |
| 9–11 | 任务持有资源时，天花板内的任务不抢占；`ReleaseResource` 后才切换 |
| 12–13 | SysTick 驱动的 alarm 在 3 个 tick 后唤醒 `WaitEvent` 的任务 |
| 14–16 | ISR 里激活更高优先级的任务，ISR 结束后立刻切过去，之后才回到原任务 |

`target_sc300/` 里的启动文件、链接脚本和测试程序只用于 QEMU，不是产品代码。测试程序用的任务、alarm 和 ISR 名字取自 T1，所以示例和 T1 的对象名绑定在一起；T1 里这些名字变了，要同步改 `t1_example.py` 和 `test_app.c`。

## R52：内核目标文件不变

```
python -m tools.os_port_check r52-save    --objects 目录      # 改动之前
python -m tools.os_port_check r52-compare --objects 目录      # 改动之后
```

`r52-save` 用 T1 当前配置（6206）生成 Os 代码，编译内核源码（`-mcpu=cortex-r52 -D__HIGHTEC__`），把 `.o` 存下来。改完内核再运行 `r52-compare`，逐字节比较，有差别就列出文件名，退出码为 1。

只编译内核源码，生成的配置只提供头文件。T1 生成的 `.c` 在 R52 上本来就有两处和内核无关的问题（IOC 回调缺数据类型头文件、某个 ISR 的触发方式为空），所以不一起编译。

## 目录

| 文件 | 内容 |
|---|---|
| `__main__.py` | 命令行 |
| `common.py` | 找工具、编译、比较目标文件 |
| `t1_example.py` | 从 T1 生成 Os 代码：原样（R52）或裁成单核 SC300 示例 |
| `r52.py`, `sc300.py` | 两项检查 |
| `stubs_r52/` | `Os_Arti.h` 的空替身（真正的由 trace 工具提供） |
| `stubs_m3/` | M3 构建用的最小 `common.h`、`compilertypes.h`、`datatypes.h`（真实的在目标 SDK 里；`uint32` 同为 `unsigned long`） |
| `target_sc300/` | QEMU 用的启动文件、链接脚本、测试程序 |

## 没有覆盖到的

- 没有真实 SC300 板和 armclang；这里用的是 `arm-none-eabi-gcc` 和 QEMU 的通用 Cortex-M3。
- Handler 模式下的中断嵌套（只有优先级 0 的中断会走到，配置上已禁止）；非特权线程的提权路径（SC300 模板把所有上下文都设成特权）。
- 没有 MPU 和时间保护（范围是 SC1）。

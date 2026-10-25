## Why

芯片依赖扫描发现，芯片库中的 `THA610X_LFBGA180` 声明了 `Os.OsResourceSubderivative = Os_THA610X`。这个声明是 fb85b8f 按类比加上的。但 Os 插件并不认识这个值：

- `Os.xdm` 的取值范围只有 `Os_THA6206`、`Os_THA6412`、`Os_SC300`，所以切换到 THA610X 时，这个选择器会被跳过；
- `plugin.xml` 没有为它登记资源文件，Os 引用的 6 个资源键也全部缺失；
- 模板里所有芯片判断都没有 THA610X 分支，新芯片会走进 6412 或其他芯片的默认分支。

用户已确认：THA610X 要运行 Os，按 **1 个核**配置，内存布局一起支持。

## 已知事实（来源）

| 项 | 值 | 来源 |
|---|---|---|
| 内核 | Cortex-R52，GICv3，与 6206/6412 相同 | MCAL `CotexR52_THA610X_LFBGA180.properties` 的文件名；SDK 的 `intc_hal.h` 与 6412 共用分支 |
| Os 可用核数 | 1（`INTC_CORE_MAXID 0`、`CHECK_OVC_CORE(id) < 1`、`Mcu.NoOfCoreAvailable: 1`） | SDK `platform/common/tha6104_cfg.h`、MCAL Resource 资源文件。MCAL 的 `Resource.NumOfCores: 2` 指的是锁步的两个物理核，Os 不使用 |
| GIC | 1 个，基地址 `0xF0000000` | `tha6104_cfg.h`（`MAX_GIC_NUM 1`、`GIC0_BASE_ADDR`） |
| 内存地图 | ATCM 32 KB、BTCM 256 KB、CTCM 128 KB，PFLASH0/1 各 2 MB，DFLASH 256 KB，GMU0/1 各 40 KB，LMU2 16 KB | SDK `LinkFiles/Ads/LinkerAdsPfTha6104.scat` |
| SDK 编译宏 | `THA6_THA6104` | SDK |

## What Changes

**Os 插件**：改 EB 正式使用的插件，以及 T1 项目里的副本。两者的同步方式与 ARTI 那次相同。

- `Os.xdm`：
  - `OsResourceSubderivative` 的取值范围加上 `Os_THA610X`。
  - 5 处内存布局的 ENABLE 条件（`MemoryBlock`、`MemoryRegion`、`MemorySection`、`OsMemoryMap`、`SystemModeStack`）从 `= 'Os_THA6206'` 改为 `= 'Os_THA6206' or = 'Os_THA610X'`。
- `resource/Os_Resource_THA610X.properties`（新增）：
  - `OsResource.NumOfCores: 1`、`AvailableCores: CORE0`、`MasterCore: OS_CORE_ID_0`、`SupportProcessor: THA610X`。
  - `Os.IsrTriggerMethodList` 按 THA6104 的中断表编写。
  - 与芯片无关的键（`GicIntTriggerMethod`、`AppModeDefaultName`、`IocPrimitiveDataType(Num)`）沿用现有取值。
- `plugin.xml`：登记 `subderivative = Os_THA610X` 对应上面的资源文件。
- 模板：
  - `isr/Os_isr_Lcfg.c`：GIC 地址表加 THA610X 分支，只有 `0xF0000000U` 一项。
  - `isr/Os_isr_Cfg.h`：确认中断总数（SPI 960 和内部中断 32 是否适用）。
  - `scatter.scat` 和 `link/*`：判断条件加上 THA610X。
  - 写死了 6206 双核内容的地方，改为按 `ecu:get('OsResource.NumOfCores')` 输出，避免为单核芯片生成 Core1 栈和 TCM 区段。
- 内核：预计不用改。`Os_isr_hal.c` 里唯一的芯片分支是 `#ifdef OS_THA6206`，只对 6206 生效；THA610X 编译时 SDK 用 `THA6_THA6104`。实现时会用芯片依赖扫描复核这一点。

**本工具**

- 芯片库 `THA610X_LFBGA180.yaml` 的 `ecu_resources` 增加 Os 一节，与新的资源文件一致。保留现有的选择器。
- 不需要改代码。验收时用芯片依赖扫描确认：`Os_THA610X` 的资源覆盖没有问题，Os 模板中的 THA610X 判断齐全。

## Impact

- **Affected specs**：新增 `chip-library`（THA610X 可以运行 Os）。
- **Affected files**：
  - Os 插件（`03-intergrateTest/.../Os_THA6_ASR21`），以及 T1 项目中的 `Os.xdm` 与 `templates/Os`；
  - 仓库：`data/chips/THA610X_LFBGA180.yaml`，以及 `doc/OS` 下的参考副本。
- **兼容性**：
  - 6206 和 6412 的 ENABLE 条件结果不变，资源文件不变，生成结果必须逐字节一致。在本工具中验证；EB 的验证请你在 EB 环境里执行。
  - 已经配置成 `Os_THA610X` 的旧项目原本不存在，因为这个值以前不在取值范围内。
- **不在本变更内**：多核锁步的相关配置；THA610X 的 MCAL。MCAL 已经支持 THA610X。

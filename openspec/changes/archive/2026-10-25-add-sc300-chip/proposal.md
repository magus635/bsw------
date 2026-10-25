## Why

Os 插件的取值范围和模板里一直有 `Os_SC300` 分支（NVIC、240 个外部中断、16 个内部中断、SysTick），但芯片库里没有 SC300 这颗芯片，所以无法选中它。它的资源文件 `Os_Resource_SC300.properties` 去掉注释后，与 THA6206 的那份逐行相同：`SupportProcessor: THA6206`、2 个核、GIC 触发方式表。这说明它是复制过来以后没有修改过的。

用户已确认：SC300 是单核的 Arm Cortex-M3，可以运行 Os，但不运行 MCAL。

用户还要求：**芯片型号的资料不完整时，要提示出来，但不要删除**。目前芯片库里的资料有好几处明显不完整或不可靠：

- SC300 的资源文件是 6206 的副本；
- THA610X 的 `metadata` 写的是 2 核、512KB Flash，SDK 则是 1 个 Os 核、两块各 2 MB 的 PFLASH；
- THA610X 的引脚复用像是占位数据。

## What Changes

### 1. 芯片库新增 `SC300`

- 名称用 `SC300`。这样与选择器值 `Os_SC300`、资源文件 `Os_Resource_SC300.properties` 的命名一致，现有的按文件名匹配也能找到它。
- `selectors` 只声明 `Os.OsResourceSubderivative: Os_SC300`，不声明 MCAL 的 `ResourceSubderivative`。选中 SC300 后，MCAL 模块不会被写入任何值。
- `ecu_resources.Os`：
  - `NumOfCores: 1`、`AvailableCores: CORE0`、`MasterCore: OS_CORE_ID_0`、`SupportProcessor: SC300`；
  - 中断数与模板中 SC300 分支一致：240 个外部中断、16 个内部中断；
  - 其余与芯片无关的键沿用现值；
  - 不需要 GIC 相关的键。
- 没有引脚和外设资源。HSM 不运行 MCAL，所以这些内容为空，而且不报为缺失。

### 2. 修正 `Os_Resource_SC300.properties`

修正 EB 正式插件里的这份文件，以及 T1 项目中的副本，内容与第 1 项一致。`Os.IsrTriggerMethodList` 如果 NVIC 用不到，就保留现有的键，但改成 SC300 的取值；无法确认的值写入“待确认”清单（见第 3 项），不删除这个键。

### 3. 芯片资料完整性提示（适用于所有芯片）

- **标记方式**：芯片 YAML 可以在 `metadata.unconfirmed` 中列出待确认的字段，例如 `ecu_resources.Os.IsrTriggerMethodList`、`metadata.flash_size`、`ports`，并附上说明。
- **自动检查**（只提示，不修改、不删除任何数据）：
  - 声明的选择器值不在模块定义的取值范围内，例如 `Os_THA610X` 在当前插件中就是这样；
  - 声明了 Os 选择器，但没有任何 Os 资源（芯片 YAML 中没有，插件也没有登记资源文件）；
  - `metadata.cores.count` 与 `OsResource.NumOfCores` 或 `Resource.NumOfCores` 都不一致。
- **显示位置**：
  - 项目属性的芯片下拉框中，这类芯片显示为“`<芯片名>`（资料不完整）”；
  - 选中后，状态文字列出具体缺什么；
  - 芯片依赖扫描的“资源覆盖”类别中也列出同样的内容。
- **不影响使用**：芯片仍然可以选择、切换和生成代码。

### 4. 首批标记

- `SC300`：中断触发方式待确认。
- `THA610X_LFBGA180`：标记 `metadata.cores`、`flash_size`、`ram_size`、`ports` 待确认。数据本身不改，留待芯片负责人核对。

## 已知风险（需要你知道）

**当前内核只支持 R52 + GICv3**：`OS_Kernel/Os/isr` 只有 `Os_isr_GICv3Register.h`，没有 NVIC 或 SysTick 的实现，内核里也搜不到 SC300。本变更完成后，可以为 SC300 配置项目并生成代码，但生成的代码需要一套 Cortex-M3 的内核移植才能编译和运行，这不在本变更内。如果别处已经有 SC300 的内核，请告诉我在哪里。

## Impact

- Affected specs：`chip-library`，新增 SC300 芯片和资料完整性提示（项目属性芯片下拉框中的提示也写在这里）。
- Affected code：
  - `data/chips/SC300.yaml`（新增），`THA610X_LFBGA180.yaml`（只加 `metadata.unconfirmed`）；
  - 新增 `core/hardware/chip_completeness.py`；
  - `ui/dialogs/project_properties_dialog.py`：下拉框文字和状态；
  - `core/hardware/chip_dependency_scan.py`：在资源覆盖中加入完整性条目；
  - Os 插件和 T1 中的 `Os_Resource_SC300.properties`。
- 兼容性：6206 和 6412 的生成结果、指纹和 EPC 导出都不变。没有删除任何芯片或数据。

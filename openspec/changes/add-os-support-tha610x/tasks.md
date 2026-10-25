## 0. 前提
- [x] 0.1 请用户确认要改的插件副本：EB 正式插件（`03-intergrateTest/.../Os_THA6_ASR21`）、T1 的 `Os.xdm` 与 `templates/Os`、仓库 `doc/OS`，并确认环境
- [x] 0.2 在动手前，为 6206、6412 生成基线（T1 副本，本工具），用于逐字节比较

## 1. 资源数据
- [x] 1.1 由 SDK `intc_hal.h` 中 THA6104 的中断号整理 `Os.IsrTriggerMethodList`，确认 SPI 和内部中断总数；无法从代码确定的项标为待确认，交由用户核对
- [x] 1.2 新增 `Os_Resource_THA610X.properties`，并在 `plugin.xml` 中登记
- [x] 1.3 `THA610X_LFBGA180.yaml` 增加 `ecu_resources.Os`，与资源文件一致；更新校验和

## 2. 插件定义与模板
- [x] 2.1 `Os.xdm` 的取值范围加上 `Os_THA610X`；5 处内存布局的 ENABLE 条件加上 `Os_THA610X`
- [x] 2.2 `Os_isr_Lcfg.c` 的 GIC 地址表加 THA610X 分支；按核数输出地址表
- [x] 2.3 `Os_isr_Cfg.h`、`scatter.scat`、`link/*`：加入 THA610X；按核数生成 Core1 相关内容
- [x] 2.4 用芯片依赖扫描复核 Os 模板、`Os.xdm` 和内核：所有 6206 判断都已确认是否适用于 THA610X

## 3. 验证
- [x] 3.1 6206 和 6412 的生成结果与基线逐字节一致
- [x] 3.2 T1 副本切换到 THA610X：预览显示内存布局仍然可用；能生成代码；GIC 表只有一项；scatter 不含 Core1 区段
- [x] 3.3 芯片依赖扫描中，`Os_THA610X` 的资源覆盖没有问题
- [ ] 3.4 用户在 EB 中打开 T1，切换到 `Os_THA610X` 并生成，确认 EB 侧正常
- [x] 3.5 全量测试通过

## 实施记录（2026-10-25）
- 改的副本（用户选定，与 ARTI 相同）：`D:/19_AutosarOS/.../01_Trunk/.../Os_THA6_ASR21`（主）→ T1 的 `Os.xdm`、`templates/Os`、`Def/plugins/Os_THA6_ASR21/resource`，以及仓库 `doc/OS`。`03-intergrateTest` 未改。
- `IsrTriggerMethodList`：SDK 只给中断号，不给触发方式；沿用 6206/6412 共用的 992 项表（THA6104 最大 INTID 900），SPI 部分在芯片 YAML 中标为待确认。
- `Os_isr_Cfg.h` 的 960/32 适用（GICv3），未改。
- Core1：scatter 的 7 类 Core1 栈和 `Os_link_Lcfg.c` 的 Core1 栈表只在 `NumOfCores > 1` 时生成；`Os_MemStackInit[...]` 的长度取自 `NumOfCores`（6206 仍输出 2）。
- 内核：`Os_isr_hal.c` 的 `#ifdef OS_THA6206` 只对 6206 生效，THA610X 生成 `#define OS_THA610X`，内核不用改。
- 验证：6206、6412 生成结果除时间戳行外逐字节一致（72 个文件）；THA610X：选择器写入无跳过，`NumOfCores` 1，GIC 表只有 `0xF0000000U`，`Os_MemStackInit[1]`，无 Core1 栈，切换不使内存布局失效，扫描无 `Os_THA610X` 覆盖问题。
- 注意：T1 现有的 MemoryRegion/MemoryBlock 是 6206 的内存布局（含 CPU1 区域），切到 THA610X 后 scatter 仍按这些配置输出；需按 SDK `LinkerAdsPfTha6104.scat` 重新配置，这是配置数据，不是模板问题。

---
name: davinci-jar-to-eb-template
description: 从 Vector MICROSAR 模块的 GeneratorMsr/*.jar 出发，结合 BSWMD/*.arxml 图形配置定义和 Implementation 源码，精准分析、生成并审查 EB tresos 格式代码模板（templates/include 与 templates/src）的标准工作流。
---

# DaVinci `.jar` 到 EB 代码模板分析与审查 Skill

当需要为 Vector DaVinci SIP 模块创建或审查 EB 格式的代码生成模板时，**严禁仅凭 `BSWMD/*.arxml` 猜测宏名或文件名**，必须严格按以下 5 步执行：

---

## 第一步：定位模块资产
确认以下 4 类输入/输出路径：
1. **生成器 Jar 包**：`Components/<Module>/GeneratorMsr/*.jar`（部分驱动如 `CanTrcv` 可能在 `Components/<Module>_30_*/GeneratorMsr/`）。
2. **模块定义文件（UI 参数来源）**：`modules/davinci/<Module>/config/<Module>.arxml`（或 `Components/<Module>/BSWMD/*_bswmd.arxml`），注意排除 `*_Pre.arxml` 和 `*_Rec.arxml`。
3. **静态实现源码（辅助校验）**：`Components/<Module>/Implementation/*.h` / `*.c`（核对 `#include` 和版本检查宏）。
4. **目标模板目录**：`modules/davinci/<Module>/templates/{include,src}/` 及 `modules/davinci/<Module>/module.json`（需包含 `"templates": "templates"`）。

---

## 第二步：分析 `GeneratorMsr/*.jar`
使用 `unzip -l` 和 `javap` 直接从 `.jar` 中提取真实输出规范：

1. **列出全部输出类与 JET 类**：
   ```bash
   unzip -l <module>.jar | grep -E "jetclasses/|outputfiles/" | grep "\.class$" | grep -v '\$'
   ```
   - 根据 `*HJet` / `*CJet` 确定**真实输出文件名**（例如 `Arti_Lcfg.c` 而非 `Arti_Cfg.c`；`CanSM_Lcfg.c` 而非 `CanSM_Cfg.c`；`BswM_Callout_Stubs.c` 等）。
2. **提取 JET 类常量与生成逻辑**：
   ```bash
   javap -cp <module>.jar -constants -v <FullJetClassName> | grep -E "^public .*class |String .*//"
   ```
   如需看具体条件判断或生成顺序，使用 `javap -cp <module>.jar -c -p <FullJetClassName>`。
   - 提取内容：
     - 精确的头文件保护宏（`#if !defined(...)`）
     - 精确的 `#include` 列表（区分无条件引入与按特性开关引入）
     - 精确的 `<MOD>_CFG_MAJOR_VERSION` / `<MOD>_CFG_MINOR_VERSION` / `GENTOOL_*_VERSION`
     - 精确的开关宏名（例如 `BSWM_ENABLE_CANSM`，`CANIF_TRANSMIT_BUFFER`，`ARTI_DEV_ERROR_REPORT`）
     - 符号句柄（`Conf_*`）、数据类型（`typedef`）、全局变量（`extern VAR(...)`）与 `MemMap` 内存段（`START_SEC_*` / `STOP_SEC_*`）。

---

## 第三步：对照 `BSWMD/*.arxml` 核对界面参数
使用工具自带的 `EcucDefParser` 导出该模块在图形界面中暴露的全部容器与参数：
```python
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
md = EcucDefParser().parse_module_def_file(arxml_path)
```
逐一建立 **`.jar` 宏/符号 $\leftrightarrow$ `BSWMD` 参数 XPath** 的映射，检查以下要点：
1. **默认值一致性**：当配置中尚未显式填写某参数（`not(node:exists(...))`）时，模板的 `[!ELSE!]` 分支必须使用 `BSWMD` 中定义的 `default_value`（例如 `DevErrorDetect` 默认 `True` $\rightarrow$ `STD_ON`）。
2. **枚举值格式**：`ENUMERATION` 类型参数必须输出**裸 C 标识符**（如 `[!"CanIfPublicCfg/CanIfJ1939DynAddrSupport"!]`），**严禁加双引号 `""`**，避免 `#if` 预编译失败。
3. **布尔与数值格式**：
   - `BOOLEAN` $\rightarrow$ `STD_ON` / `STD_OFF`
   - `INTEGER` $\rightarrow$ `(([!"..."!]u))`
   - `FLOAT` $\rightarrow$ 不加 `u` 后缀
4. **多实例容器**：`upper_multiplicity == -1` 或 `> 1` 的容器（如 `ArtiHookTraceVariable/*`、`CanIfCtrlCfg/*`、`BswMRule/*`）必须使用 `[!LOOP "..."!]` 生成符号句柄、声明或函数骨架。
5. **条件头文件**：依赖可选子模块的 `#include`（如 `BswM_CanSM.h`、`CanIf_CanTrcv.h`）必须加上对应的 `[!IF "... = 'true'"!]` 条件保护。

---

## 第四步：生成并规范模板目录
1. 将头文件模板放入 `templates/include/`，源文件模板放入 `templates/src/`。
2. **严禁跨文件重复定义**：`<MOD>_CFG_MAJOR/MINOR_VERSION` 与公共配置宏仅放在主配置头文件（`*_Cfg.h` 或 `*_Cfg_Features.h`）中，`*_Lcfg.h`、`*_PBcfg.h`、`*_Private_Cfg.h` 不得重复定义。
3. 清理同目录下不属于 `.jar` 输出清单的旧猜测文件。
4. 确认 `module.json` 中存在 `"templates": "templates"`。

---

## 第五步：端到端生成与质量审查
1. **语法与格式扫描**：检查所有模板文件，确保无多余 `)`（如 `!] )[!ELSE!]`）、无未闭合括号/引号、无重复 `#define`。
2. **双配置实测**：使用 `ModulePackage` + `CodeGenerator.generate_all()` 分别在以下两种配置下执行渲染并人工检查输出：
   - **默认最小配置**：验证默认值兜底与不报错；
   - **自定义启用配置**（开启关键开关 + 添加多实例子容器）：验证条件 `#include`、宏开关切换及 `[!LOOP!]` 符号生成均准确响应界面参数。

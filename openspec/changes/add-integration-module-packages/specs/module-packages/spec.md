# module-packages — Delta

## ADDED Requirements

### Requirement: Module Package Layout And Manifest

工具 SHALL 支持“模块包”：一个以模块名命名的目录，含清单 `module.json` 和 `config/` 目录，模块的定义（ECUC-MODULE-DEF）、预设值（PRE）和推荐值（REC）放在同一个 `config/` 目录中；模板和资源目录由清单的 `templates`、`resources` 字段指明。清单的 `files` 只列出来源文件，不标角色；角色 SHALL 按 AUTOSAR 路径判定：`definition` 指向定义，`implementation_path` 指向 `BSW-IMPLEMENTATION`，`pre`、`rec` 列出值集合路径。

#### Scenario: 同一文件同时含 Pre 和 Rec

- **WHEN** 包内一个值文件同时含 `X_Pre` 和 `X_Rec` 两个值集合，清单的 `pre` 列出 `X_Pre`、`rec` 列出 `X_Rec`
- **THEN** `X_Pre` 按 PRE 处理，`X_Rec` 按 REC 处理
- **AND** 不会因为文件名带 `_pre` 而把 `X_Rec` 也当作 PRE

#### Scenario: 清单引用的 Pre 路径不存在

- **WHEN** 清单 `pre` 列出的路径在任何选中的文件里都不存在
- **THEN** 加载给出警告，指出该路径，不中断加载

### Requirement: EB Plugin Inferred As Module Package

没有 `module.json` 的 EB 插件目录 SHALL 不经改造即可作为模块包使用，清单从 `plugin.xml` 推断：`schema` 登记的资源是定义来源，`preconfig` 的 `path` 是 PRE，`generate_PB/` 是模板，`resource/` 是资源。`autosar/<模块>_<芯片>.arxml` SHALL NOT 被加载，而是作为定义的交换副本在来源信息中列出；只有 arxml、没有 xdm 的插件按文件名中的芯片名生成芯片条件。推断得出的结果 SHALL 标记为“推断”。

#### Scenario: 未改造的 EB 插件目录加载 Mcu 预设

- **WHEN** 一个未做任何修改的 EB 插件目录作为 `eb-plugins` 库加入 format 8 新工程，并添加 Mcu 模块
- **THEN** `McuPreConfiguration` 中的复位原因表出现在配置树中，来源为 PRE
- **AND** `autosar/Mcu_<芯片>.arxml` 没有被加载，并在来源信息中列为“交换副本”

### Requirement: Chip-Conditional Package Files

清单中的文件 MAY 带 `chips` 列表。为空时对所有芯片生效；不为空时，只有工程 `selected_chip` 在列表中才读取该文件。在当前芯片下，同一路径的定义出现两份且内容不同、或同一单值字段在两个选中文件中取值不同时，工具 SHALL 报错并指出 AUTOSAR 路径和涉及的文件，SHALL NOT 任选其一。

#### Scenario: 切换芯片后 pre 随之切换

- **WHEN** 一个手工构造的包在 `config/` 中放有 define 和两个分别带不同 `chips` 条件的 pre 文件，工程切换 `selected_chip`
- **THEN** 加载的 pre 文件随芯片切换

#### Scenario: 两个 pre 同时匹配且取值冲突

- **WHEN** 两个 pre 文件都匹配当前芯片，并对同一参数给出不同取值
- **THEN** 加载报错，错误信息包含该参数的 AUTOSAR 路径和两个文件名

### Requirement: In-Package Merge By AUTOSAR Path

选中文件中路径相同的元素（值集合、IMPL）SHALL 按 AUTOSAR 路径合并为一个，合并只在同一个包内进行，不跨包。xdm 和 arxml 两种格式的值文件都 SHALL 参与合并。

#### Scenario: 一个 Pre 由两个文件拼成

- **WHEN** `/MICROSAR/vBRS_Pre` 的容器分别来自包内两个文件，且没有冲突的单值字段
- **THEN** 加载结果中 `vBRS_Pre` 含两个文件中的全部容器

### Requirement: Module Libraries

format 8 工程 SHALL 通过 `.dpa` 的 `module_libraries` 声明一个或多个库根目录，类型为 `package`（每个子目录是一个模块包）或 `eb-plugins`（每个插件是一个模块包）。扫描 SHALL 只读清单或 `plugin.xml`，不解析定义。模块身份以定义路径为准；同一定义路径出现在两个库中时 SHALL 报错，除非 `.dpa` 的 `exclude` 明确排除其中一个。

#### Scenario: 两个库提供同一定义路径

- **WHEN** 两个库都提供定义路径为 `/THA6_AS440_FuSa/Mcu` 的模块包，且都没有被排除
- **THEN** 扫描报错，指出定义路径和两个包的位置

#### Scenario: 按定义路径定位模块

- **WHEN** format 8 工程打开，`modules` 中某项的 `definition` 为 `/THA6_AS440_FuSa/Mcu`
- **THEN** 工具在声明的库中找到对应包并加载，不依赖已保存的定义文件路径

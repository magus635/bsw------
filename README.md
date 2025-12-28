# AUTOSAR BSW 图形配置工具

一个基于 Python 和 PySide6 开发的 AUTOSAR 基础软件模块图形化配置工具，类似于 Vector DaVinci Configurator Pro。
本项目集成了 **EB Tresos 兼容的模板引擎**，支持从 ARXML 配置直接生成符合 AUTOSAR 标准的 C 代码。

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Python](https://img.shields.io/badge/python-3.10+-blue.svg)
![Code Gen](https://img.shields.io/badge/CodeGen-EB%20Tresos-orange)
![Tests](https://img.shields.io/badge/tests-278%20passed-brightgreen.svg)

---

## 功能特性

### 核心功能
- **ARXML 全功能支持**: 解析和序列化 AUTOSAR 4.x ARXML 文件
- **图形化配置**: 树形视图、属性编辑器、多选操作
- **实时验证**: 参数类型的即时校验
- **Undo/Redo**: 完整的撤销重做支持
- **双模式视图**: 定义层 (灰色) + 实例层 (加粗) 分离显示

### 代码生成
本项目内置了强大的 **EB Tresos 兼容模板引擎**：
- **EB 语法支持**:
  - 控制流: `[!IF]`, `[!ELSE]`, `[!LOOP]`, `[!SELECT]`, `[!VAR]`
  - 表达式: 支持复杂 XPath 导航、算术运算 (`+`, `-`, `*`)、逻辑运算
- **内置函数库**:
  - 节点操作: `node:value()`, `node:ref()`, `node:name()`, `node:path()`
  - 算术与字符串: `num:i()`, `num:inttohex()`, `string:concat()` 等
- **自动生成**: 支持生成 `_Cfg.h`, `_Lcfg.c`, `_PBcfg.c` 等标准文件
- **引用解析**: 自动处理跨模块引用

### 高级 UI 功能
- **搜索与过滤**: 支持正则搜索、类型过滤 (`Ctrl+F`)
- **批量编辑**: 多选修改、批量删除
- **依赖关系图**: 可视化模块依赖 (`Ctrl+D`)
- **变体管理**: 支持 Multi-variant 配置

### AI 智能辅助
- **自然语言查询**: 输入问题获取配置建议
- **错误诊断**: AI 分析验证错误并提供修复方案
- **配置推荐**: 基于上下文推荐参数值

### EMF 对象图系统
基于 EMF 风格的对象导航系统：
- **正向解析**: 字符串路径 → 对象指针 (`ref.target`)
- **反向索引**: 快速查找引用关系 (`container.referenced_by`)
- **Resolution Error 系统**: 10 种工程级错误类型

---

## 快速开始

### 环境要求
- Python 3.10+
- PySide6 6.5.0+
- lxml 4.9.0+

### 安装依赖
```bash
pip install -r requirements.txt
```

### 运行应用
```bash
python3 main.py
```

### 运行测试
```bash
# 运行所有测试
python3 -m pytest tests/ -v

# 运行代码生成测试
python3 -m pytest tests/generator/ -v
```

---

## AI 功能配置

使用 AI 功能前需配置 Google Gemini API Key：

### 方式1: 环境变量 (推荐)
```bash
export GEMINI_API_KEY="your-api-key-here"
python3 main.py
```

### 方式2: 应用内配置
1. 启动应用
2. 菜单 `Settings` → `AI Configuration`
3. 输入 API Key

### 获取 API Key
访问 https://makersuite.google.com/app/apikey 申请免费的 API Key。

---

## 快捷键

| 功能 | Windows/Linux | macOS |
|------|---------------|-------|
| 新建项目 | Ctrl+Shift+N | Cmd+Shift+N |
| 打开项目 | Ctrl+Shift+O | Cmd+Shift+O |
| 保存项目 | Ctrl+Shift+S | Cmd+Shift+S |
| 新建配置 | Ctrl+N | Cmd+N |
| 保存配置 | Ctrl+S | Cmd+S |
| 撤销 | Ctrl+Z | Cmd+Z |
| 重做 | Ctrl+Y | Cmd+Shift+Z |
| 验证 | Ctrl+Shift+V | Cmd+Shift+V |
| 代码生成 | Ctrl+G | Cmd+G |
| 搜索 | Ctrl+F | Cmd+F |
| AI 助手 | Ctrl+Shift+A | Cmd+Shift+A |
| 使用手册 | F1 | F1 |

---

## 项目结构

```
autosar_configurator/
├── core/                    # 核心业务逻辑
│   ├── model/              # 数据模型 (Container, Parameter)
│   ├── parser/             # ARXML 解析器
│   ├── serializer/         # ARXML 序列化器
│   ├── ai/                 # AI 集成模块
│   ├── rules/              # 验证规则引擎
│   └── analysis/           # 依赖分析
│
├── generator/              # 代码生成模块
│   ├── eb/                 # EB Tresos 兼容引擎
│   │   ├── lexer.py       # 词法分析器
│   │   ├── renderer.py    # 渲染器
│   │   └── builtins.py    # 内置函数库
│   └── templates/          # 代码模板
│
├── ui/                     # 用户界面
│   ├── davinci_main_window.py  # 主窗口
│   ├── widgets/            # UI 组件
│   └── dialogs/            # 对话框
│
└── business/               # 业务逻辑层
```

---

## 支持的模块

| 模块 | 描述 | 模板状态 |
|------|------|---------|
| Adc | 模数转换器 | EB |
| Can | CAN 通信 | EB |
| Crypto | 加密服务 | EB |
| Dsadc | Delta-Sigma ADC | EB |
| Mcu | 微控制器单元 | EB |
| Port | 端口配置 | EB |

---

## 开发进度

### 已完成
- [x] 阶段 1-7: UI 框架、Undo/Redo、数据模型
- [x] 阶段 8: 依赖分析与验证
- [x] 阶段 9: 代码生成引擎 (EB Tresos 兼容)
- [x] 阶段 10: EMF 对象图系统

### 计划中
- [ ] 阶段 11: 生成报告与日志优化
- [ ] 阶段 12: CI/CD 集成

---

## 文档

- `QUICKSTART.md` - 快速开始指南
- `doc/详细设计文档.md` - 详细架构设计
- `doc/bsw配置与代码生成原理.md` - BSW 配置原理
- `doc/EMF.md` - EMF 对象图系统说明

应用内按 `F1` 可查看完整使用手册。

---

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！

### 贡献指南
1. Fork 本仓库
2. 创建特性分支: `git checkout -b feature/your-feature`
3. 提交更改: `git commit -m 'Add some feature'`
4. 推送分支: `git push origin feature/your-feature`
5. 提交 Pull Request

### 代码规范
- 遵循 PEP 8 代码风格
- 新功能需要添加测试
- 提交前运行 `pytest tests/ -v` 确保测试通过

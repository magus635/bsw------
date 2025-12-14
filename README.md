# AUTOSAR BSW图形配置工具

一个基于Python和PySide6开发的AUTOSAR基础软件模块图形化配置工具，类似于Vector DaVinci Configurator Pro。
本项目集成了**EB Tresos兼容的模板引擎**，支持从ARXML配置直接生成符合AUTOSAR标准的C代码。

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Python](https://img.shields.io/badge/python-3.10+-blue.svg)
![Code Gen](https://img.shields.io/badge/CodeGen-EB%20Tresos-orange)
![Tests](https://img.shields.io/badge/tests-Passed-brightgreen.svg)

## 功能特性

### 🚀 核心功能
- **ARXML全功能支持**: 解析和序列化AUTOSAR 4.x ARXML文件
- **图形化配置**: 树形视图、属性编辑器、多选操作
- **实时验证**: 参数类型的即时校验
- **Undo/Redo**: 完整的撤销重做支持

### 🏭 代码生成 (新!)
本项目内置了强大的 **EB Tresos 兼容模板引擎**，支持以下特性：
- **EB 语法支持**: 
  - 控制流: `[!IF]`, `[!ELSE]`, `[!LOOP]`, `[!SELECT]`, `[!VAR]`
  - 表达式: 支持复杂 XPath 导航、算术运算 (`+`, `-`, `*`)、逻辑运算
- **内置函数库**:
  - 节点操作: `node:value()`, `node:ref()`, `node:name()`, `node:path()`
  - 算术与字符串: `num:i()`, `num:inttohex()`, `string:concat()` 等
- **自动生成**: 支持生成 `_Cfg.h` 和 `_PBcfg.c` 等标准文件
- **引用解析**: 自动处理跨模块引用（如 `Forwared Refs`）

### ✨ 高级 UI 功能
- **搜索与过滤**: 支持正则搜索、类型过滤
- **批量编辑**: 多选修改、批量删除
- **扩展类型**:
  - **ARRAY**: 逗号分隔编辑
  - **STRUCT**: JSON格式编辑
  - **REFERENCE**: 智能引用选择

## 快速开始

### 安装依赖
```bash
pip install -r requirements.txt
```

### 运行应用
```bash
python3 main.py
```

### 运行代码生成测试
验证模板引擎功能的测试套件：
```bash
python3 -m unittest tests.generator.eb.test_user_templates -v
```

## EB 模板引擎支持详情

引擎已通过以下关键场景验证：
1. **基础配置头文件**: `Can_Cfg.h` (宏定义, 开关控制)
2. **Post-Build配置**: `Can_PBcfg.c` (结构体数组, 指针引用)
3. **复杂逻辑**:
   - 嵌套循环 (`LOOP`)
   - 变量计算与Hex格式化 (`VAR`, `num:inttohex`)
   - 跨模块引用解引用 (`node:ref(Param)`)
   - 变体处理 (`VARIANT-POST-BUILD`)

## 开发进度

### ✅ 已完成
- [x] 阶段1-7: UI框架、Undo/Redo、数据模型
- [x] 阶段8: 依赖分析与验证
- [x] 阶段9: **代码生成引擎 (EB Tresos 兼容)**
  - [x] 词法分析器 (Lexer)
  - [x] 渲染器 (Renderer)
  - [x] XPath 导航支持
  - [x] 必须的内置函数库

### 🚧 计划中
- [ ] 阶段10: 生成报告与日志优化
- [ ] 阶段11: CI/CD 集成

## 许可证

MIT License

## 贡献

欢迎提交Issue和Pull Request！


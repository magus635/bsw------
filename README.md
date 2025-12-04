# AUTOSAR BSW图形配置工具

一个基于Python和PySide6开发的AUTOSAR基础软件模块图形化配置工具，类似于Vector DaVinci Configurator Pro。

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Python](https://img.shields.io/badge/python-3.8+-blue.svg)
![Tests](https://img.shields.io/badge/tests-77%20passed-brightgreen.svg)
![Coverage](https://img.shields.io/badge/coverage-82%25-green.svg)

## 功能特性

### ✅ 核心功能
- **ARXML文件支持**: 完整的AUTOSAR 4.4.0 XML解析和序列化
- **图形化编辑**: 直观的树形导航和属性编辑面板
- **实时验证**: 参数类型和约束验证
- **观察者模式**: 数据模型自动同步UI显示
- **线程安全**: RLock保护并发操作

### ✨ 高级功能 (新)
- **撤销/重做 (Undo/Redo)**: 完整的命令模式支持，可撤销所有编辑操作
- **搜索与过滤**: 强大的搜索对话框，支持按名称、类型、值搜索，支持正则表达式
- **批量编辑**: 支持多选删除、批量修改参数值
- **扩展类型支持**:
  - **ARRAY**: 数组类型参数，支持逗号分隔编辑
  - **STRUCT**: 结构体参数，支持JSON格式编辑
  - **REFERENCE**: 引用类型支持

### 📊 数据模型
- **Container**: 支持无限层级嵌套
- **Parameter**: 支持STRING, INTEGER, FLOAT, BOOLEAN, ENUM, REFERENCE, ARRAY, STRUCT类型
- **约束验证**: Min/Max值、枚举值、数组元素类型、结构体字段验证
- **元数据**: UUID、描述、路径、引用等

### 🖥️ 用户界面
- **主窗口**: 现代化工具栏图标、状态栏反馈、深色风格优化
- **导航树**: 懒加载(Lazy Loading)支持大文件，多选支持
- **配置面板**: 智能类型编辑器，自动格式化
- **文件操作**: 新建、打开、保存、另存为

## 快速开始

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
pytest tests/ -v
```

## 使用示例

### 1. 高级编辑功能
- **撤销/重做**: 使用工具栏按钮或 Ctrl+Z / Ctrl+Y
- **搜索**: 点击工具栏搜索图标或 Ctrl+F，输入关键词查找
- **批量操作**: 在树视图中按住 Ctrl/Shift 多选，右键选择 "Batch Edit" 或 "Batch Delete"

### 2. 扩展类型编辑
- **数组 (ARRAY)**: 在值输入框中输入 `1, 2, 3` (自动解析为列表)
- **结构体 (STRUCT)**: 输入 JSON 格式 `{"id": 1, "name": "demo"}`

## 开发进度

### ✅ 已完成
- [x] 阶段1: 核心框架与ARXML支持
- [x] 阶段2: GUI基础框架
- [x] 阶段3: Undo/Redo系统 (Command模式)
- [x] 阶段4: 搜索与过滤功能
- [x] 阶段5: 批量编辑支持
- [x] 阶段6: 扩展参数类型 (ARRAY, STRUCT, REFERENCE)
- [x] 阶段7: 用户体验优化 (懒加载, UI美化)

### 🚧 计划中
- [ ] 阶段8: 验证引擎（自定义规则、依赖检查）
- [ ] 阶段9: 代码生成（C/C++配置代码）

## 许可证

MIT License

## 贡献

欢迎提交Issue和Pull Request！

## 联系方式

如有问题或建议，请创建Issue。

## 致谢

感谢AUTOSAR组织提供的标准规范。

# 🚀 快速开始指南

## 最简单的启动方式（推荐）

### 方式1: 使用启动脚本（macOS/Linux）

```bash
cd "/Users/qlwang/Desktop/bsw图形配置工具"
./start.sh
```

启动脚本会自动：
- ✅ 检查Python版本
- ✅ 检查并安装缺失的依赖
- ✅ 启动应用程序

### 方式2: 手动启动

```bash
# 1. 进入项目目录
cd "/Users/qlwang/Desktop/bsw图形配置工具"

# 2. 运行应用
python3 main.py
```

## 第一次使用

### 步骤1: 验证安装

运行测试确保一切正常：

```bash
# 进入项目目录
cd "/Users/qlwang/Desktop/bsw图形配置工具"

# 运行测试
python3 -m pytest tests/core/test_observers.py -v
```

如果看到类似这样的输出，说明安装正确：
```
===== 7 passed in 0.01s =====
```

### 步骤2: 启动应用

```bash
python3 main.py
```

你应该会看到主窗口打开！

### 步骤3: 创建第一个配置

1. **创建新配置**
   - 点击菜单 `File` → `New`
   - 或按快捷键 `Cmd+N` (macOS) / `Ctrl+N` (Windows/Linux)
   - 你会看到左侧树形视图出现 "RootConfiguration"

2. **添加容器**
   - 右键点击 "RootConfiguration"
   - 选择 `Add Container`
   - 新容器会出现在树中，默认名称为 "NewContainer1"

3. **编辑容器属性**
   - 点击刚创建的容器
   - 右侧面板会显示容器属性
   - 修改 "Short Name" 为 "CanModule"
   - 在 "Description" 中输入 "CAN通信模块配置"

4. **添加参数**
   - 右键点击 "CanModule"
   - 选择 `Add Parameter`
   - 新参数会出现，默认名称为 "NewParameter1"

5. **编辑参数**
   - 点击刚创建的参数
   - 在右侧面板编辑：
     - Short Name: `Baudrate`
     - Type: 选择 `INTEGER`
     - Value: `500`
     - Min Value: `125`
     - Max Value: `1000`
     - Unit: `kbps`
     - Description: `CAN总线波特率`

6. **验证参数**
   - 点击 `Validate` 按钮
   - 如果显示绿色的 "✓ Validation passed"，说明参数配置正确

7. **保存配置**
   - 点击菜单 `File` → `Save As...`
   - 选择保存位置，输入文件名如 `my_config.arxml`
   - 点击保存

恭喜！你已经创建了第一个AUTOSAR配置文件！🎉

## 打开现有配置

```bash
# 方式1: 通过GUI
# File → Open... → 选择 .arxml 文件

# 方式2: 命令行（计划功能）
# python3 main.py --open my_config.arxml
```

## 常用操作速查

| 操作 | 快捷键 (Mac) | 快捷键 (Win/Linux) | 菜单路径 |
|------|--------------|-------------------|----------|
| 新建 | Cmd+N | Ctrl+N | File → New |
| 打开 | Cmd+O | Ctrl+O | File → Open |
| 保存 | Cmd+S | Ctrl+S | File → Save |
| 另存为 | Cmd+Shift+S | Ctrl+Shift+S | File → Save As |
| 退出 | Cmd+Q | Ctrl+Q | File → Exit |
| 刷新 | Cmd+R | Ctrl+R | View → Refresh |

## 界面布局说明

```
┌─────────────────────────────────────────────────────┐
│ 菜单栏: File | Edit | View | Help                   │
├─────────────────────────────────────────────────────┤
│ 工具栏: [New] [Open] [Save] | [Refresh]            │
├──────────────────┬──────────────────────────────────┤
│                  │                                  │
│  导航树 (30%)     │  配置面板 (70%)                  │
│                  │                                  │
│  RootConfig      │  Container Properties:           │
│  ├─CanModule     │  ┌─────────────────────────┐   │
│  │  ├─Baudrate   │  │ Short Name: CanModule   │   │
│  │  └─Mode       │  │ Description: ...        │   │
│  └─LinModule     │  │ Path: /Root/CanModule   │   │
│                  │  └─────────────────────────┘   │
│                  │                                  │
├──────────────────┴──────────────────────────────────┤
│ 状态栏: Ready                                       │
└─────────────────────────────────────────────────────┘
```

## 示例配置文件

项目包含一个测试数据生成脚本：

```bash
python3 test_gui_data.py
```

这会创建一个示例配置结构：
```
TestRoot
├── Can (CAN Driver configuration)
│   ├── CanBaudRate = 500 kbps (125-1000)
│   └── CanMode = NORMAL (ENUM: NORMAL/LOOPBACK/SILENT)
└── Lin (LIN Driver configuration)
    └── LinBaudRate = 19200 bps (9600-20000)
```

## 故障排除

### 问题: 应用启动失败

**检查Python版本**:
```bash
python3 --version
# 需要 3.8 或更高版本
```

**检查依赖**:
```bash
pip3 list | grep PySide6
pip3 list | grep lxml
```

**重新安装依赖**:
```bash
pip3 install -r requirements.txt
```

### 问题: 窗口不显示

**macOS**: 确保有图形界面访问权限
**Linux**: 确保X11转发配置正确
**远程连接**: 不支持远程终端，需要本地显示

### 问题: 模块导入错误

```bash
# 设置Python路径
export PYTHONPATH="/Users/qlwang/Desktop/bsw图形配置工具:$PYTHONPATH"

# 或者从正确的目录运行
cd "/Users/qlwang/Desktop/bsw图形配置工具"
python3 main.py
```

## 下一步

- 📖 阅读 `README.md` 了解更多功能
- 📖 查看 `DEBUG_GUIDE.md` 学习调试技巧
- 📖 阅读 `PROJECT_SUMMARY.md` 了解技术细节
- 🧪 运行测试: `pytest tests/ -v`
- 💡 查看代码示例学习API使用

## 获取帮助

- 📁 查看项目文档
- 🐛 报告问题或建议
- 💬 查看代码注释

祝使用愉快！🎊

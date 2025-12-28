# 快速开始指南

## 最简单的启动方式

### 方式1: 使用启动脚本 (macOS/Linux)

```bash
cd <项目目录>
./start.sh
```

启动脚本会自动：
- 检查 Python 版本
- 检查并安装缺失的依赖
- 启动应用程序

### 方式2: 手动启动

```bash
# 1. 进入项目目录
cd <项目目录>

# 2. 安装依赖 (首次运行)
pip3 install -r requirements.txt

# 3. 运行应用
python3 main.py
```

---

## 第一次使用

### 步骤1: 验证安装

运行测试确保一切正常：

```bash
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

你应该会看到 DaVinci Configurator 主窗口打开！

### 步骤3: 创建第一个配置

1. **打开定义文件**
   - 点击菜单 `File` → `Open Definition (.epd)`
   - 选择一个 `.epd` 或 `.arxml` 定义文件
   - 左侧树视图会显示模块定义结构

2. **添加配置实例**
   - 在树视图中找到需要配置的容器定义（灰色斜体）
   - 右键点击 → `Add Instance`
   - 新实例会出现在定义下方（加粗显示）

3. **编辑参数**
   - 点击刚创建的实例容器
   - 右侧面板会显示所有可配置参数
   - 修改参数值，系统会实时验证

4. **验证配置**
   - 点击工具栏 `Validate` 按钮或按 `Ctrl+Shift+V`
   - 查看验证结果，修复任何错误

5. **保存配置**
   - 点击菜单 `File` → `Save Value File` 或按 `Ctrl+S`
   - 选择保存位置，输入文件名如 `my_config.arxml`

6. **生成代码** (可选)
   - 点击菜单 `Generate` → `Generate All` 或按 `Ctrl+G`
   - 代码将生成到配置的输出目录

恭喜！你已经完成了第一个 AUTOSAR 配置！

---

## 快捷键速查

| 操作 | Windows/Linux | macOS |
|------|---------------|-------|
| 新建项目 | Ctrl+Shift+N | Cmd+Shift+N |
| 打开项目 | Ctrl+Shift+O | Cmd+Shift+O |
| 保存项目 | Ctrl+Shift+S | Cmd+Shift+S |
| 新建配置 | Ctrl+N | Cmd+N |
| 打开定义 | Ctrl+O | Cmd+O |
| 保存配置 | Ctrl+S | Cmd+S |
| 撤销 | Ctrl+Z | Cmd+Z |
| 重做 | Ctrl+Y | Cmd+Shift+Z |
| 验证 | Ctrl+Shift+V | Cmd+Shift+V |
| 代码生成 | Ctrl+G | Cmd+G |
| 搜索 | Ctrl+F | Cmd+F |
| AI 助手 | Ctrl+Shift+A | Cmd+Shift+A |
| 使用手册 | F1 | F1 |

---

## 界面布局说明

```
+----------------------------------------------------------+
| File  Edit  Project  Generate  View  Help                |
+----------------------------------------------------------+
| [New] [Open] [Save] | [Validate] [Generate] | [Search]   |
+------------------+---------------------------------------+
|                  |                                       |
|  Module Tree     |  Configuration Panel                  |
|  +-----------+   |  +-------------------------------+    |
|  | Adc [Def] |   |  | Container: AdcGeneral        |    |
|  |  +-Config |   |  | +---------------------------+ |    |
|  |  +-Channel|   |  | | AdcDevErrorDetect: true   | |    |
|  | Can [Def] |   |  | | AdcTimeoutDuration: 1000  | |    |
|  |  +-Ctrl   |   |  | +---------------------------+ |    |
|  +-----------+   |  +-------------------------------+    |
|                  |                                       |
|                  +---------------------------------------+
|                  |  AI Assistant (Ctrl+Shift+A)          |
|                  |  +-------------------------------+    |
|                  |  | Ask me anything about config  |    |
|                  |  +-------------------------------+    |
+------------------+---------------------------------------+
| Status: Ready | Errors: 0 | Warnings: 0                  |
+----------------------------------------------------------+
```

### 区域说明

| 区域 | 功能 |
|------|------|
| **菜单栏** | 文件、编辑、项目、生成、视图、帮助 |
| **工具栏** | 常用操作的快捷按钮 |
| **模块树** | 显示模块定义和配置实例的层次结构 |
| **配置面板** | 编辑选中容器的参数 |
| **AI 助手** | 自然语言查询和智能推荐 (可折叠) |
| **状态栏** | 显示当前状态和错误/警告计数 |

---

## AI 助手配置 (可选)

使用 AI 功能前需配置 Google Gemini API Key：

```bash
# 设置环境变量
export GEMINI_API_KEY="your-api-key-here"

# 然后启动应用
python3 main.py
```

获取 API Key: https://makersuite.google.com/app/apikey

---

## 故障排除

### 问题: 应用启动失败

**检查 Python 版本**:
```bash
python3 --version
# 需要 3.10 或更高版本
```

**检查依赖**:
```bash
pip3 list | grep -E "PySide6|lxml"
```

**重新安装依赖**:
```bash
pip3 install -r requirements.txt
```

### 问题: 窗口不显示

- **macOS**: 确保有图形界面访问权限
- **Linux**: 确保 X11 配置正确
- **远程连接**: 需要 X11 转发或本地显示

### 问题: 模块导入错误

```bash
# 从项目根目录运行
cd <项目目录>
python3 main.py
```

---

## 下一步

- 按 `F1` 查看完整使用手册
- 阅读 `README.md` 了解更多功能
- 查看 `doc/` 目录下的技术文档
- 运行测试: `pytest tests/ -v`

祝使用愉快！

# 调试指南

当前调试目标是 `davinci_main.py` 和 `autosar_configurator.ui.davinci_main_window.DaVinciMainWindow`。旧版 `main.py`、`ui/main_window.py`、`tree_view.py`、`config_panel.py` 调试路径已废弃。

## 基础检查

```bash
cd /Users/qlwang/Documents/GitHub/bsw------
source .venv/bin/activate
python --version
python -m pip install -r requirements.txt
python -m py_compile davinci_main.py
```

如果使用仓库已有 `venv/`：

```bash
source venv/bin/activate
```

## 启动调试日志

```bash
DAVINCI_DEBUG=1 python davinci_main.py
```

生产模式下 `davinci_main.py` 会屏蔽普通 `print` 输出；需要看调试信息时必须设置 `DAVINCI_DEBUG=1`。

## 常用测试

最小 smoke test：

```bash
python -m pytest tests/core/test_observers.py -q
```

生成器测试：

```bash
python -m pytest tests/generator -q
```

UI 测试：

```bash
QT_QPA_PLATFORM=offscreen python -m pytest tests/ui -q
```

OpenSpec：

```bash
openspec validate --all --strict
```

## 当前 UI 结构

主要窗口和控制器：

```text
davinci_main.py
autosar_configurator/ui/davinci_main_window.py
autosar_configurator/ui/controllers/
├── project_controller.py
├── edit_controller.py
├── validation_controller.py
├── generation_controller.py
├── navigation_controller.py
├── dependency_graph_controller.py
├── ai_assistant_controller.py
└── wizard_controller.py
```

主要组件：

```text
autosar_configurator/ui/widgets/
├── davinci_tree_view.py
├── davinci_config_panel.py
├── smart_search.py
├── dependency_graph.py
├── problems_view.py
└── ai_assistant.py
```

## VS Code 调试配置

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "DaVinci Configurator",
      "type": "python",
      "request": "launch",
      "program": "${workspaceFolder}/davinci_main.py",
      "console": "integratedTerminal",
      "justMyCode": false,
      "env": {
        "PYTHONPATH": "${workspaceFolder}",
        "DAVINCI_DEBUG": "1"
      }
    },
    {
      "name": "Pytest current file",
      "type": "python",
      "request": "launch",
      "module": "pytest",
      "args": ["${file}", "-q"],
      "console": "integratedTerminal",
      "justMyCode": false
    }
  ]
}
```

## 常见问题

### `No module named autosar_configurator`

从项目根目录运行，或设置：

```bash
export PYTHONPATH="$PWD:${PYTHONPATH}"
```

### `No module named pytest` / `No module named PySide6`

虚拟环境未激活或依赖未安装：

```bash
source .venv/bin/activate
python -m pip install -r requirements.txt
```

### GUI 测试卡住或无法显示窗口

使用 offscreen：

```bash
QT_QPA_PLATFORM=offscreen python -m pytest tests/ui -q
```

### AI 测试或 AI 功能卡在外部请求

默认回归不要触网。AI 测试应 mock Gemini；手动调试时再设置：

```bash
export GEMINI_API_KEY="your-api-key"
```

### 代码生成没有输出

当前生成器不使用内置默认模板。确认项目模板目录或用户模板目录中存在对应模块模板，例如 `Can/Can_Cfg.h.tpl` 或 `Can/Can_PBcfg.c`。没有模板时生成器会将模块标记为 skipped。

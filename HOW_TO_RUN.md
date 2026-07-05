# 运行与测试指南

当前应用入口是 `davinci_main.py`。不要再使用旧文档中的 `main.py` 或 `verify.py`。

## 推荐方式

```bash
cd /Users/qlwang/Documents/GitHub/bsw------
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python davinci_main.py
```

## 使用启动脚本

```bash
./start.sh
```

脚本会优先激活 `.venv/`，其次尝试 `venv/`，然后检查依赖并启动 `davinci_main.py`。

## 使用已有 venv

仓库中如果已有 `venv/`：

```bash
source venv/bin/activate
python davinci_main.py
```

## 测试命令

最小环境验证：

```bash
python -m pytest tests/core/test_observers.py -q
```

生成器回归：

```bash
python -m pytest tests/generator -q
```

OpenSpec 校验：

```bash
openspec validate --all --strict
```

更大范围测试：

```bash
QT_QPA_PLATFORM=offscreen python -m pytest tests autosar_configurator/tests -q
```

注意：完整测试可能包含 UI、AI、真实 EB 工程兼容等场景。默认回归应避免触网；AI 相关测试应 mock Gemini 或显式配置 `GEMINI_API_KEY`。

## 调试启动

显示调试日志：

```bash
DAVINCI_DEBUG=1 python davinci_main.py
```

无界面环境下跑 UI 测试：

```bash
QT_QPA_PLATFORM=offscreen python -m pytest tests/ui -q
```

## VS Code 配置

`.vscode/launch.json` 可使用：

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
      "env": {
        "PYTHONPATH": "${workspaceFolder}",
        "DAVINCI_DEBUG": "1"
      }
    },
    {
      "name": "Pytest",
      "type": "python",
      "request": "launch",
      "module": "pytest",
      "args": ["tests/core/test_observers.py", "-q"],
      "console": "integratedTerminal"
    }
  ]
}
```

## 常见问题

### `No module named pytest`

说明当前 Python 没安装测试依赖。先激活虚拟环境并安装依赖：

```bash
source .venv/bin/activate
python -m pip install -r requirements.txt
```

### `No module named PySide6`

同样通常是虚拟环境未激活或依赖未安装：

```bash
source .venv/bin/activate
python -m pip install -r requirements.txt
```

### 窗口不显示

确认是在本地图形环境中运行。远程或 CI 环境需要使用 `QT_QPA_PLATFORM=offscreen` 跑测试，不能直接显示主窗口。

### AI 助手无响应

设置 API Key：

```bash
export GEMINI_API_KEY="your-api-key"
python davinci_main.py
```

或在应用中打开 `View -> AI Assistant`，点击 `Settings` 配置。

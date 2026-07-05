# 从这里开始

当前有效入口：

```bash
cd /Users/qlwang/Documents/GitHub/bsw------
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python davinci_main.py
```

已有 `venv/` 时可改用：

```bash
source venv/bin/activate
python davinci_main.py
```

## 最小验证

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

## 必读文档

1. `README.md`：当前项目概览。
2. `QUICKSTART.md`：第一次使用流程。
3. `HOW_TO_RUN.md`：运行、测试、虚拟环境和 VS Code 配置。
4. `DEBUG_GUIDE.md`：排障与调试。
5. `PROJECT_SUMMARY.md`：当前架构概览。

## 废弃命令

以下旧命令不再适用：

```bash
python3 main.py
python3 verify.py
python3 test_gui_data.py
```

如果其他文档或历史记录仍出现这些命令，以本文件和 `README.md` 为准。

# 从这里开始

## 启动方式

### 方式一：使用启动脚本（推荐，免配置）

```bash
./start.sh
```

> 脚本会自动检测 `.venv` 或当前 Python 环境，自动校验架构兼容性与依赖完整性，并在依赖缺失时提示安装。

---

### 方式二：手动配置与运行

**1. 首次使用创建虚拟环境与安装依赖：**

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python davinci_main.py
```

**2. 日常启动（虚拟环境已就绪）：**

```bash
source .venv/bin/activate
python davinci_main.py
```

> **macOS (Apple Silicon / M 系列芯片) 提示**：
> 如果当前目录存在旧的历史 x86_64 架构 `venv/` 导致报错 `bad CPU type in executable`，可运行以下命令一键清理并新建原生虚拟环境：
> ```bash
> rm -rf venv .venv && python3 -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt
> ```

---

## 最小验证

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

## 必读文档

1. `README.md`：当前项目概览与设计说明。
2. `QUICKSTART.md`：第一次使用流程与功能速查表。
3. `HOW_TO_RUN.md`：运行、测试、环境与 VS Code 配置。
4. `DEBUG_GUIDE.md`：排障与调试。
5. `PROJECT_SUMMARY.md`：当前架构与模块分工概览。

## 废弃命令

以下旧入口和旧命令已废弃，不要再使用：

```bash
python3 main.py
python3 verify.py
python3 test_gui_data.py
```


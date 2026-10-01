#!/bin/bash
# 启动脚本 - AUTOSAR BSW配置工具

echo "========================================="
echo "AUTOSAR BSW配置工具启动脚本"
echo "========================================="
echo ""

activate_if_valid() {
    local venv_path="$1"
    if [ -d "$venv_path" ]; then
        if [ -x "$venv_path/bin/python3" ] && "$venv_path/bin/python3" --version >/dev/null 2>&1; then
            echo "发现有效虚拟环境 ($venv_path)，正在激活..."
            source "$venv_path/bin/activate"
            return 0
        else
            echo "警告: 检测到虚拟环境 ($venv_path) 但二进制无法执行（可能架构不兼容，如 x86_64 vs arm64）。正在跳过..."
            return 1
        fi
    fi
    return 1
}

# 0. 尝试激活有效虚拟环境
if ! activate_if_valid ".venv"; then
    if ! activate_if_valid "venv"; then
        echo "未找到有效虚拟环境，使用当前系统 Python: $(which python3)"
        echo "提示: 如需新建干净的本机虚拟环境，可执行: rm -rf venv .venv && python3 -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt"
    fi
fi

# 检查Python版本
echo "检查Python版本..."
python3 --version

if [ $? -ne 0 ]; then
    echo "错误: 未找到Python3，请先安装Python 3.10或更高版本"
    exit 1
fi

echo ""

# 检查是否在正确的目录
if [ ! -f "davinci_main.py" ]; then
    echo "错误: 未找到 davinci_main.py，请确保在项目根目录运行此脚本"
    exit 1
fi

echo "检查依赖..."
python3 - <<'PY'
import importlib.util
import sys

required = {
    "PySide6": "PySide6",
    "lxml": "lxml",
    "jinja2": "Jinja2",
    "yaml": "PyYAML",
}
optional = {
    "markdown": "markdown",
    "google.generativeai": "google-generativeai",
    "keyring": "keyring",
    "pypdf": "pypdf",
    "PIL": "Pillow",
}
missing = [package for module, package in required.items() if importlib.util.find_spec(module) is None]
missing_optional = [package for module, package in optional.items() if importlib.util.find_spec(module) is None]
if missing_optional:
    print("可选依赖缺失: " + ", ".join(missing_optional))
    print("如需 AI、keychain、PDF/图片知识库功能，请运行: python -m pip install -r requirements.txt")
if missing:
    print("缺少依赖: " + ", ".join(missing))
    sys.exit(1)
PY
if [ $? -ne 0 ]; then
    echo "尝试安装 requirements.txt..."
    python3 -m pip install -r requirements.txt
    if [ $? -ne 0 ]; then
        echo "安装失败。请先激活虚拟环境后运行: python -m pip install -r requirements.txt"
        exit 1
    fi
fi

echo ""
echo "所有依赖已就绪！"
echo ""
echo "启动应用程序 (DaVinci Mode)..."
echo "========================================="
echo ""

# 启动应用
python3 davinci_main.py

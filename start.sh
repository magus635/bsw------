#!/bin/bash
# 启动脚本 - AUTOSAR BSW配置工具

echo "========================================="
echo "AUTOSAR BSW配置工具启动脚本"
echo "========================================="
echo ""

# 0. 尝试激活虚拟环境
if [ -d ".venv" ]; then
    echo "发现虚拟环境 (.venv)，正在激活..."
    source .venv/bin/activate
elif [ -d "venv" ]; then
    echo "发现虚拟环境 (venv)，正在激活..."
    source venv/bin/activate
else
    echo "未找到虚拟环境。尝试使用系统 Python..."
    echo "注意：如果遇到依赖问题，建议先创建虚拟环境: python3 -m venv .venv"
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

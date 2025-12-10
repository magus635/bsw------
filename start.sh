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
else
    echo "未找到虚拟环境 (.venv)。尝试使用系统 Python..."
    echo "注意：如果遇到依赖问题，建议先创建虚拟环境: python3 -m venv .venv"
fi

# 检查Python版本
echo "检查Python版本..."
python3 --version

if [ $? -ne 0 ]; then
    echo "错误: 未找到Python3，请先安装Python 3.8或更高版本"
    exit 1
fi

echo ""

# 检查是否在正确的目录
if [ ! -f "davinci_main.py" ]; then
    echo "错误: 未找到 davinci_main.py，请确保在项目根目录运行此脚本"
    exit 1
fi

echo "检查依赖..."

# 检查PySide6
python3 -c "import PySide6" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "PySide6未安装，尝试安装..."
    pip install PySide6
    if [ $? -ne 0 ]; then
        echo "⚠️ 安装失败。如果您在受管环境(如Homebrew)下，请确保已激活虚拟环境。"
        echo "您可能需要手动运行: source .venv/bin/activate && pip install -r requirements.txt"
        exit 1
    fi
fi

# 检查lxml
python3 -c "import lxml" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "lxml未安装，尝试安装..."
    pip install lxml
fi

# 检查google-generativeai (AI功能需要)
python3 -c "import google.generativeai" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "AI功能依赖未安装，尝试安装 google-generativeai..."
    pip install google-generativeai
fi

# 检查pypdf (PDF支持需要)
python3 -c "import pypdf" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "PDF支持依赖未安装，尝试安装 pypdf..."
    pip install pypdf
fi

# 检查Pillow (OCR/图像处理需要)
python3 -c "import PIL" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "图像处理依赖未安装，尝试安装 Pillow..."
    pip install Pillow
fi

echo ""
echo "所有依赖已就绪！"
echo ""
echo "启动应用程序 (DaVinci Mode)..."
echo "========================================="
echo ""

# 启动应用
python3 davinci_main.py

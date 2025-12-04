#!/bin/bash
# 启动脚本 - AUTOSAR BSW配置工具

echo "========================================="
echo "AUTOSAR BSW配置工具启动脚本"
echo "========================================="
echo ""

# 检查Python版本
echo "检查Python版本..."
python3 --version

if [ $? -ne 0 ]; then
    echo "错误: 未找到Python3，请先安装Python 3.8或更高版本"
    exit 1
fi

echo ""

# 检查是否在正确的目录
if [ ! -f "main.py" ]; then
    echo "错误: 未找到main.py，请确保在项目根目录运行此脚本"
    exit 1
fi

echo "检查依赖..."

# 检查PySide6
python3 -c "import PySide6" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "PySide6未安装，正在安装..."
    pip3 install PySide6
fi

# 检查lxml
python3 -c "import lxml" 2>/dev/null
if [ $? -ne 0 ]; then
    echo "lxml未安装，正在安装..."
    pip3 install lxml
fi

echo ""
echo "所有依赖已就绪！"
echo ""
echo "启动应用程序..."
echo "========================================="
echo ""

# 启动应用
python3 main.py

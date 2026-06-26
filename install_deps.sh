#!/bin/bash
# 依赖安装脚本

echo "========================================="
echo "AUTOSAR BSW配置工具 - 依赖安装"
echo "========================================="
echo ""

echo "检测Python环境..."
PYTHON_CMD=$(which python3)
echo "Python路径: $PYTHON_CMD"
$PYTHON_CMD --version
echo ""

echo "安装依赖包..."
echo ""

# 尝试使用pip install
if $PYTHON_CMD -m pip install --user -r requirements.txt 2>/dev/null; then
    echo "✅ 依赖安装成功（用户模式）"
elif $PYTHON_CMD -m pip install --break-system-packages -r requirements.txt 2>/dev/null; then
    echo "✅ 依赖安装成功（系统包模式）"
else
    echo "⚠️  标准pip安装失败，尝试创建虚拟环境..."
    echo ""

    # 创建虚拟环境
    $PYTHON_CMD -m venv venv

    # 激活虚拟环境
    source venv/bin/activate

    # 安装依赖
    pip install -r requirements.txt

    echo ""
    echo "✅ 依赖已安装到虚拟环境"
    echo ""
    echo "使用虚拟环境运行应用:"
    echo "  source venv/bin/activate"
    echo "  python davinci_main.py"
    echo ""
    echo "或使用快捷脚本:"
    echo "  ./run_with_venv.sh"
fi

echo ""
echo "========================================="
echo "安装完成！"
echo "========================================="
echo ""
echo "验证安装:"
echo "  python3 verify.py"
echo ""
echo "启动应用:"
echo "  python3 davinci_main.py"
echo "  或 ./start.sh"
echo ""

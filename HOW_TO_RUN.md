# 🎯 调试运行指南 - 实用版

## 📦 方法1: 最简单的方式（推荐首次使用）

### 第一步：安装依赖

```bash
cd "/Users/qlwang/Desktop/bsw图形配置工具"
./install_deps.sh
```

或手动安装：
```bash
python3 -m pip install --user PySide6 lxml pytest pytest-cov
```

### 第二步：验证安装

```bash
python3 verify.py
```

你应该看到所有测试项显示 ✅。

### 第三步：启动应用

```bash
python3 main.py
```

## 📦 方法2: 使用虚拟环境（推荐开发使用）

```bash
# 1. 创建虚拟环境
cd "/Users/qlwang/Desktop/bsw图形配置工具"
python3 -m venv venv

# 2. 激活虚拟环境
source venv/bin/activate

# 3. 安装依赖
pip install -r requirements.txt

# 4. 运行应用
python main.py

# 退出虚拟环境
deactivate
```

## 🧪 运行测试

```bash
# 基本测试
python3 -m pytest tests/core/test_observers.py -v

# 所有测试
python3 -m pytest tests/ -v

# 带覆盖率
python3 -m pytest tests/ --cov=autosar_configurator --cov-report=term-missing
```

## 🐛 常见问题解决

### 问题1: ModuleNotFoundError: No module named 'lxml'

**解决方案**:
```bash
# 方法A: 用户模式安装
python3 -m pip install --user lxml

# 方法B: 使用虚拟环境（推荐）
python3 -m venv venv
source venv/bin/activate
pip install lxml
```

### 问题2: ModuleNotFoundError: No module named 'PySide6'

**解决方案**:
```bash
python3 -m pip install --user PySide6
```

### 问题3: 应用启动但窗口不显示

**检查**:
- 是否在远程SSH连接？（需要本地运行）
- macOS是否授权了应用访问权限？

### 问题4: ImportError: cannot import name 'Container'

**解决方案**:
```bash
# 确保在项目根目录
cd "/Users/qlwang/Desktop/bsw图形配置工具"

# 设置Python路径
export PYTHONPATH="${PWD}:${PYTHONPATH}"

# 运行
python3 main.py
```

## 💡 使用技巧

### 技巧1: 从命令行创建测试配置

```bash
python3 test_gui_data.py
```

### 技巧2: 查看项目结构

```bash
tree -L 3 -I '__pycache__|*.pyc|venv'
```

### 技巧3: 快速测试某个功能

```python
# test_quick.py
from autosar_configurator.core.model.container import Container, Parameter

root = Container(short_name="Test")
param = Parameter(short_name="Speed", value=100, value_type="INTEGER")
root.add_parameter(param)

print(f"Created: {root.short_name}/{param.short_name}")
print(f"Validation: {param.validate()}")
```

```bash
python3 test_quick.py
```

## 📊 IDE调试配置

### VS Code (.vscode/launch.json)

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "启动应用",
            "type": "python",
            "request": "launch",
            "program": "${workspaceFolder}/main.py",
            "console": "integratedTerminal"
        }
    ]
}
```

### PyCharm

1. 右键 `main.py` → Run 'main'
2. 设置断点后，点击 Debug 'main'

## 📝 检查清单

启动前检查：
- [ ] Python版本 >= 3.8
- [ ] 在项目根目录
- [ ] 依赖已安装（运行 `python3 verify.py`）
- [ ] 测试通过（运行 `pytest tests/core/test_observers.py -v`）

如果全部 ✅，可以启动：
```bash
python3 main.py
```

## 🎓 学习路径

1. **第一天**: 运行验证脚本，启动应用，创建第一个配置
2. **第二天**: 阅读代码，运行测试，理解数据模型
3. **第三天**: 修改代码，添加新功能，编写测试

## 📚 文档索引

- `QUICKSTART.md` - 快速开始（适合第一次使用）
- `DEBUG_GUIDE.md` - 详细调试指南
- `README.md` - 项目介绍
- `PROJECT_SUMMARY.md` - 技术总结

## 🚀 立即开始

最快的方式：

```bash
cd "/Users/qlwang/Desktop/bsw图形配置工具"
python3 -m pip install --user PySide6 lxml pytest
python3 verify.py    # 验证
python3 main.py      # 启动
```

祝使用顺利！有问题查看 `DEBUG_GUIDE.md` 或创建Issue。

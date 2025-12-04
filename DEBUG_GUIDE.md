# AUTOSAR BSW配置工具 - 调试运行指南

## 快速启动指南

### 方法1: 直接运行（推荐）

```bash
# 1. 进入项目目录
cd "/Users/qlwang/Desktop/bsw图形配置工具"

# 2. 确认Python版本（需要3.8+）
python3 --version

# 3. 安装依赖
pip3 install -r requirements.txt

# 4. 运行应用程序
python3 main.py
```

### 方法2: 使用虚拟环境（生产环境推荐）

```bash
# 1. 创建虚拟环境
python3 -m venv venv

# 2. 激活虚拟环境
# macOS/Linux:
source venv/bin/activate
# Windows:
# venv\Scripts\activate

# 3. 安装依赖
pip install -r requirements.txt

# 4. 运行应用
python main.py
```

### 方法3: 使用IDE调试（开发调试推荐）

#### VS Code调试配置

1. **创建调试配置文件** `.vscode/launch.json`:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: 运行主程序",
            "type": "python",
            "request": "launch",
            "program": "${workspaceFolder}/main.py",
            "console": "integratedTerminal",
            "justMyCode": false,
            "env": {
                "PYTHONPATH": "${workspaceFolder}"
            }
        },
        {
            "name": "Python: 运行测试",
            "type": "python",
            "request": "launch",
            "module": "pytest",
            "args": [
                "tests/",
                "-v",
                "--cov=autosar_configurator"
            ],
            "console": "integratedTerminal",
            "justMyCode": false
        },
        {
            "name": "Python: 测试单个文件",
            "type": "python",
            "request": "launch",
            "module": "pytest",
            "args": [
                "${file}",
                "-v"
            ],
            "console": "integratedTerminal",
            "justMyCode": false
        }
    ]
}
```

2. **使用调试**:
   - 按 `F5` 启动调试
   - 或点击左侧调试图标，选择配置后点击绿色播放按钮
   - 设置断点：点击代码行号左侧

#### PyCharm调试配置

1. **配置运行**:
   - 右键 `main.py` → Run 'main'
   - 或 Run → Edit Configurations
   - Script path: 选择 `main.py`
   - Working directory: 项目根目录

2. **调试**:
   - 设置断点：点击代码行号左侧
   - 点击Debug按钮（小虫子图标）
   - 使用调试工具栏：Step Over(F8), Step Into(F7), Continue(F9)

## 常见问题排查

### 问题1: 找不到模块

**错误信息**:
```
ModuleNotFoundError: No module named 'autosar_configurator'
```

**解决方案**:
```bash
# 方法1: 设置PYTHONPATH
export PYTHONPATH="${PYTHONPATH}:/Users/qlwang/Desktop/bsw图形配置工具"
python3 main.py

# 方法2: 从项目根目录运行
cd "/Users/qlwang/Desktop/bsw图形配置工具"
python3 main.py

# 方法3: 安装为开发包
pip install -e .
```

### 问题2: PySide6导入失败

**错误信息**:
```
ModuleNotFoundError: No module named 'PySide6'
```

**解决方案**:
```bash
# 安装PySide6
pip3 install PySide6

# 如果安装失败，尝试升级pip
pip3 install --upgrade pip
pip3 install PySide6
```

### 问题3: lxml安装失败

**错误信息**:
```
error: command 'gcc' failed
```

**解决方案**:
```bash
# macOS:
brew install libxml2 libxslt
pip3 install lxml

# Ubuntu/Debian:
sudo apt-get install libxml2-dev libxslt-dev python3-dev
pip3 install lxml

# 或使用预编译版本
pip3 install lxml --only-binary lxml
```

### 问题4: 应用启动但窗口不显示

**解决方案**:
```bash
# 检查是否在远程终端
echo $DISPLAY

# 如果是远程，需要X11转发或使用本地机器

# macOS可能需要安装XQuartz
brew install --cask xquartz
```

## 调试技巧

### 1. 启用详细日志

修改 `main.py` 添加日志：

```python
import sys
import logging
from PySide6.QtWidgets import QApplication
from autosar_configurator.ui.main_window import MainWindow

# 配置日志
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('app.log'),
        logging.StreamHandler(sys.stdout)
    ]
)

logger = logging.getLogger(__name__)

def main():
    logger.info("Application starting...")

    app = QApplication(sys.argv)
    app.setApplicationName("AUTOSAR BSW Configurator")

    logger.info("Creating main window...")
    window = MainWindow()
    window.show()

    logger.info("Entering event loop...")
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
```

### 2. 单步测试数据模型

```python
# 创建测试文件 debug_model.py
from autosar_configurator.core.model.container import Container, Parameter

# 创建测试数据
print("Creating container...")
root = Container(short_name="Test")
print(f"Root created: {root.short_name}")

# 添加参数
print("Adding parameter...")
param = Parameter(short_name="Param1", value=42, value_type="INTEGER")
root.add_parameter(param)
print(f"Parameter added: {param.short_name} = {param.value}")

# 验证
errors = param.validate()
print(f"Validation: {'PASS' if not errors else 'FAIL'}")
if errors:
    for error in errors:
        print(f"  - {error}")

print("Test completed!")
```

运行测试：
```bash
python3 debug_model.py
```

### 3. 测试解析器

```python
# 创建测试文件 debug_parser.py
from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.serializer.arxml_serializer import ArxmlSerializer
from autosar_configurator.core.model.container import Container, Parameter

# 创建测试数据
print("Creating test configuration...")
root = Container(short_name="TestConfig")
can = Container(short_name="Can")
root.add_sub_container(can)

param = Parameter(
    short_name="Baudrate",
    value=500,
    value_type="INTEGER",
    min_value=125,
    max_value=1000
)
can.add_parameter(param)

# 序列化
print("Serializing to XML...")
serializer = ArxmlSerializer(use_namespaces=False, pretty_print=True)
xml = serializer.serialize_to_string(root)
print("Generated XML:")
print(xml[:500])  # 打印前500字符

# 解析
print("\nParsing XML back...")
parser = ArxmlParser()
parsed = parser.parse_string(xml)
print(f"Parsed root: {parsed.short_name}")
print(f"Sub-containers: {list(parsed.sub_containers.keys())}")

can_parsed = parsed.get_sub_container("Can")
if can_parsed:
    print(f"CAN parameters: {list(can_parsed.parameters.keys())}")
    baudrate = can_parsed.get_parameter("Baudrate")
    if baudrate:
        print(f"Baudrate value: {baudrate.value}")

print("\nRoundtrip test: PASS")
```

### 4. 测试GUI组件

```python
# 创建测试文件 debug_gui.py
import sys
from PySide6.QtWidgets import QApplication
from autosar_configurator.ui.widgets.tree_view import ModuleTreeView
from autosar_configurator.core.model.container import Container, Parameter

app = QApplication(sys.argv)

# 创建测试数据
root = Container(short_name="Root")
child = Container(short_name="Child")
root.add_sub_container(child)

param = Parameter(short_name="TestParam", value=100)
child.add_parameter(param)

# 创建树视图
tree = ModuleTreeView()
tree.set_root_container(root)
tree.show()

print("Tree view displayed. Close the window to exit.")
sys.exit(app.exec())
```

### 5. 使用Python调试器(pdb)

```python
# 在代码中添加断点
import pdb

def some_function():
    x = 10
    pdb.set_trace()  # 程序会在这里暂停
    y = x * 2
    return y
```

运行时使用pdb命令：
- `n` (next): 下一行
- `s` (step): 进入函数
- `c` (continue): 继续执行
- `p variable`: 打印变量
- `l` (list): 显示代码
- `q` (quit): 退出

## 运行测试

### 运行所有测试
```bash
# 基本测试
pytest tests/ -v

# 带覆盖率
pytest tests/ -v --cov=autosar_configurator

# 生成HTML覆盖率报告
pytest tests/ --cov=autosar_configurator --cov-report=html
# 报告在 htmlcov/index.html

# 只显示未覆盖的行
pytest tests/ --cov=autosar_configurator --cov-report=term-missing
```

### 运行特定测试
```bash
# 测试特定模块
pytest tests/core/test_container.py -v

# 测试特定类
pytest tests/core/test_container.py::TestParameter -v

# 测试特定方法
pytest tests/core/test_container.py::TestParameter::test_validate_integer_valid -v

# 使用关键字过滤
pytest tests/ -k "parameter" -v
```

### 调试失败的测试
```bash
# 在第一个失败处停止
pytest tests/ -x

# 进入pdb调试器
pytest tests/ --pdb

# 显示详细输出
pytest tests/ -vv

# 显示print输出
pytest tests/ -s
```

## 性能分析

### 使用cProfile
```bash
python3 -m cProfile -o profile.stats main.py

# 分析结果
python3 -c "
import pstats
p = pstats.Stats('profile.stats')
p.sort_stats('cumulative')
p.print_stats(20)
"
```

### 使用memory_profiler
```bash
pip install memory-profiler

# 添加装饰器到函数
@profile
def my_function():
    pass

# 运行
python3 -m memory_profiler main.py
```

## 开发工作流

### 1. 修改代码
```bash
# 编辑文件
vim autosar_configurator/core/model/container.py
```

### 2. 运行测试验证
```bash
# 运行相关测试
pytest tests/core/test_container.py -v
```

### 3. 启动应用验证UI
```bash
python3 main.py
```

### 4. 检查代码质量
```bash
# 使用pylint
pip install pylint
pylint autosar_configurator/

# 使用black格式化
pip install black
black autosar_configurator/

# 使用flake8检查
pip install flake8
flake8 autosar_configurator/
```

## 推荐开发环境设置

### VS Code 扩展
- Python (Microsoft)
- Pylance
- Python Test Explorer
- GitLens
- Better Comments

### 有用的命令
```bash
# 查看项目结构
tree -I '__pycache__|*.pyc|.pytest_cache|htmlcov|venv'

# 查找所有TODO
grep -r "TODO" autosar_configurator/

# 统计代码行数
find autosar_configurator -name "*.py" | xargs wc -l

# 检查导入
python3 -c "import autosar_configurator; print(autosar_configurator.__file__)"
```

## 故障排除清单

- [ ] Python版本是否>=3.8?
- [ ] 是否在项目根目录?
- [ ] 依赖是否全部安装?
- [ ] PYTHONPATH是否正确?
- [ ] 是否有权限问题?
- [ ] 端口是否被占用?
- [ ] 日志文件中是否有错误信息?

## 获取帮助

如果遇到问题：

1. 查看日志文件 `app.log`
2. 运行测试查看哪里失败
3. 查看 `PROJECT_SUMMARY.md` 了解架构
4. 检查依赖版本是否兼容
5. 在Issue中报告问题

祝调试顺利！🚀

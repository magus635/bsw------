import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path('/Users/qlwang/Desktop/bsw图形配置工具')))

from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.context import ContextStack

def test():
    st = SymbolTable()
    cs = ContextStack()
    bf = BuiltinFunctions(st, cs)
    
    print(f"num:i(None) = {bf.num_i(None)}")
    print(f"num:i(0) = {bf.num_i(0)}")
    print(f"num:i('0') = {bf.num_i('0')}")
    print(f"num:i([]) = {bf.num_i([])}")
    
    # Test to_string
    print(f"to_string(0) = '{bf.to_string(0)}'")
    print(f"to_string(num_i(None)) = '{bf.to_string(bf.num_i(None))}'")

if __name__ == "__main__":
    test()

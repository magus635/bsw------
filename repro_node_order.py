
import sys
import os

# Add relevant paths
sys.path.append(os.getcwd())

from autosar_configurator.generator.eb.symbol_table import SymbolTable, ConfigurationNode
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.renderer import ContextStack

def test_node_order():
    st = SymbolTable()
    cs = ContextStack()
    builtins = BuiltinFunctions(st, cs)
    
    # Create some mock nodes
    nodes = []
    # Obj 0: CAN4 (ObjectId 0)
    n0 = ConfigurationNode(short_name='CAN4_Tx', node_type='container', path='/Can/CanConfigSet/CAN4_Tx')
    p0 = ConfigurationNode(short_name='CanObjectId', node_type='parameter', path='/Can/CanConfigSet/CAN4_Tx/CanObjectId', value=0)
    n0.children[p0.short_name] = p0
    nodes.append(n0)
    
    # Obj 1: CAN0 (ObjectId 8)
    n1 = ConfigurationNode(short_name='CAN0_Tx', node_type='container', path='/Can/CanConfigSet/CAN0_Tx')
    p1 = ConfigurationNode(short_name='CanObjectId', node_type='parameter', path='/Can/CanConfigSet/CAN0_Tx/CanObjectId', value=8)
    n1.children[p1.short_name] = p1
    nodes.append(n1)
    
    print("Before sort:")
    for n in nodes:
        print(f"  {n.short_name}: ObjectId={n.get_child('CanObjectId').get_value()}")
        
    # Test node:order(nodes, 'node:value(CanObjectId)')
    ordered = builtins.node_order(nodes, 'node:value(CanObjectId)')
    
    print("\nAfter sort (node:order):")
    for n in ordered:
        obj_id_node = n.get_child('CanObjectId')
        obj_id = obj_id_node.get_value() if obj_id_node else "MISSING"
        print(f"  {n.short_name}: ObjectId={obj_id}")

    # Test numerical sort
    print("\nNote: strings '8' and '0' sort as '0', '8'.")
    print("If it sorts as CAN0, CAN4, it means it worked (0 < 8).")
    print("If it sorts as CAN4, CAN0, it means it sorted by short_name (C comes after C... wait, CAN0 vs CAN4).")

if __name__ == "__main__":
    test_node_order()

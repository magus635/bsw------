import re
path = '/Users/qlwang/Desktop/bsw图形配置工具/autosar_configurator/generator/eb/xpath_engine.py'
with open(path, 'r') as f:
    content = f.read()

fallback_code = """
                            # 3. EB Tresos implicit instance traversal (if still nothing found)
                            if not found_current_node:
                                for c_node in n.children:
                                    if c_node.node_type == 'container':
                                        sub = c_node.get_child(name)
                                        if sub:
                                            next_nodes.append(sub)
                                            found_current_node = True
                                            break # Found in this instance, no need to check other instances
                                            
                            # NEW 3.5: Fallback for stub-loaded instances without definitions (.epc only)
                            # In Eb Tresos projects, instantiated containers like OsAlarm_0 
                            # might need to match "OsAlarm".
                            import re
                            active_instances = []
                            for c_node in n.children:
                                # Strip _\\d+ suffix from short_name, e.g., OsAlarm_0 -> OsAlarm
                                stripped_name = re.sub(r'_\\d+$', '', c_node.short_name)
                                if stripped_name == name or stripped_name.lower() == name.lower():
                                    if c_node.short_name != name: # exclude the stub def itself
                                        active_instances.append(c_node)
                                        
                            if active_instances:
                                # If we found instances, we must wrap them in a surrogate definition node
                                # Find the stub definition node
                                stub_def = None
                                for cn in next_nodes:
                                    if cn.short_name == name and getattr(cn, 'node_type', '') == 'container':
                                        stub_def = cn
                                        break
                                
                                if stub_def:
                                    # Attach instances to the stub def so `./*` iterates over them
                                    stub_def.children = list(active_instances)
                                    found_current_node = True
                                else:
                                    from typing import List
                                    try:
                                        from ..symbol_table import ConfigurationNode
                                        surrogate = ConfigurationNode(name, "container", None, n)
                                        surrogate.children = list(active_instances)
                                        next_nodes.append(surrogate)
                                        found_current_node = True
                                    except ImportError:
                                        # Fallback
                                        next_nodes.extend(active_instances)
                                        found_current_node = True
"""

target = """                            # 3. EB Tresos implicit instance traversal (if still nothing found)
                            if not found_current_node:
                                for c_node in n.children:
                                    if c_node.node_type == 'container':
                                        sub = c_node.get_child(name)
                                        if sub:
                                            next_nodes.append(sub)
                                            found_current_node = True
                                            # DON'T break here, we might have multiple instances!
                                            
                            # NEW 3.5: Fallback for stub-loaded instances without definitions (.epc only)
                            # In Eb Tresos projects, instantiated containers like OsAlarm_0 
                            # might need to match "OsAlarm" if they don't have a correct definition_ref.
                            # Even if we found a "stub" definition node, we want to match actual configured instances.
                            if not hasattr(n, '_epc_matched_instances') or not getattr(n, '_epc_matched_instances'):
                                import re
                                instances_found = False
                                active_instances = []
                                for c_node in n.children:
                                    # Strip _\\d+ suffix from short_name, e.g., OsAlarm_0 -> OsAlarm
                                    stripped_name = re.sub(r'_\\d+$', '', c_node.short_name)
                                    if stripped_name == name or stripped_name.lower() == name.lower():
                                        if c_node.short_name != name: # exclude the stub def itself
                                            active_instances.append(c_node)
                                            instances_found = True
                                            
                                # If we found instances, we must wrap them in a surrogate definition node 
                                # because templates expect `OsAlarm` to be ONE node containing all instances.
                                if instances_found:
                                    # Find the stub definition node
                                    stub_def = None
                                    for cn in next_nodes:
                                        if cn.short_name == name and getattr(cn, 'node_type', '') == 'container':
                                            stub_def = cn
                                            break
                                    
                                    if stub_def:
                                        # Attach instances to the stub def so `./*` iterates over them
                                        stub_def.children = list(active_instances)
                                        found_current_node = True
                                    else:
                                        # We don't have a stub def. We MUST return the instances directly but
                                        # EB templates usually use `node:order(./*,'@index')`.
                                        # However, if it's returning a surrogate, the surrogate isn't attached to `n`
                                        # This means xpath engine might discard it or fail later.
                                        # Actually, the original implementation would return next_nodes. 
                                        # So let's build the surrogate and append it.
                                        from ...model.symbol_table import ConfigurationNode
                                        surrogate = ConfigurationNode(name, "container", None, n)
                                        surrogate.children = list(active_instances)
                                        next_nodes.append(surrogate)
                                        found_current_node = True
                                        
                                    print(f"DEBUG_XPATH: Applied fallback for {name}, found {len(active_instances)} instances")"""


if target in content:
    content = content.replace(target, fallback_code)
    with open(path, 'w') as f:
        f.write(content)
    print("Patched xpath_engine.py successfully.")
else:
    print("Target not found in xpath_engine.py. Please verify.")


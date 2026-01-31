
path = '/Users/qlwang/Desktop/bsw图形配置工具/autosar_configurator/generator/eb/xpath_engine.py'
with open(path, 'r') as f:
    lines = f.readlines()

# Line 234 index is 233
target_indent = ''
for char in lines[233]:
    if char == ' ': target_indent += ' '
    else: break

print(f'Detected indentation: {len(target_indent)} spaces')

new_block = [
    f'{target_indent}# Improved list handling for non-node items (e.g. from text:split)\n',
    f'{target_indent}if isinstance(result, list) and result and (not hasattr(result[0], \"node_type\") if result else True):\n',
    f'{target_indent}    # Check if it\'s a simple index\n',
    f'{target_indent}    if pred_str.isdigit():\n',
    f'{target_indent}        idx = int(pred_str) - 1\n',
    f'{target_indent}        result = result[idx] if 0 <= idx < len(result) else None\n',
    f'{target_indent}    else:\n',
    f'{target_indent}        # Evaluate as a condition for each element\n',
    f'{target_indent}        filtered = []\n',
    f'{target_indent}        for pos, item in enumerate(result, 1):\n',
    f'{target_indent}            # Set temporary context for the predicate evaluation\n',
    f'{target_indent}            self.context_stack.push(item)\n',
    f'{target_indent}            self.context_stack.set_variable(\"position\", pos)\n',
    f'{target_indent}            self.context_stack.set_variable(\"last\", len(result))\n',
    f'{target_indent}            try:\n',
    f'{target_indent}                # Evaluate condition\n',
    f'{target_indent}                if self._evaluate_predicate_condition(item, pred_str):\n',
    f'{target_indent}                    filtered.append(item)\n',
    f'{target_indent}            finally:\n',
    f'{target_indent}                self.context_stack.pop()\n',
    f'{target_indent}        \n',
    f'{target_indent}        # EB Tresos behavior: if it was a search for a single item (position filter)\n',
    f'{target_indent}        # it often returns a single item. If it\'s used in VAR, we want the item or None.\n',
    f'{target_indent}        if filtered:\n',
    f'{target_indent}            # If the predicate contains a position check, it is likely meant to find one item\n',
    f'{target_indent}            if \"position(\" in pred_str or (pred_str.isdigit()):\n',
    f'{target_indent}                result = filtered[0]\n',
    f'{target_indent}            else:\n',
    f'{target_indent}                result = filtered\n',
    f'{target_indent}        else:\n',
    f'{target_indent}            result = None\n'
]

# The block to replace starts at line 236 (index 235)
end_idx = -1
for j in range(235, len(lines)):
    if lines[j].strip().startswith('else:') and len(lines[j]) - len(lines[j].lstrip()) == len(target_indent):
        end_idx = j
        break

if end_idx != -1:
    lines[235:end_idx] = new_block
    with open(path, 'w') as f:
        f.writelines(lines)
    print('Indentation fixed successfully')
else:
    print('Failed to find end of block for replacement')

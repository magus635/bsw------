import sys
import re

path = '/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates/Eth/src/Eth_PBcfg.c'
try:
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()

    # 1. Cleanup garbage in structure definition
    anchor_start = 'TRUE, /* Transmit store and forward enable/disable */'
    anchor_end = 'ETH_TXQUEUE_SIZE_'
    
    start_idx = content.find(anchor_start)
    if start_idx != -1:
        end_idx = content.find(anchor_end, start_idx)
        if end_idx != -1:
            middle = content[start_idx + len(anchor_start) : end_idx]
            # If we find the garbage string or trace calls
            if ')*256' in middle or 'TRACE' in middle:
                print('Found garbage in structure. Cleaning...')
                # We replace the middle part with just newline and spaces
                clean_middle = '\n                        '
                content = content[:start_idx + len(anchor_start)] + clean_middle + content[end_idx:]
            else:
                print('Structure area looks clean.')

    # 2. Apply fallback logic to calculation block
    fallback_logic = """[!VAR "EngressQueueSize" = "num:i(text:split($FinalAlloc,' ')[num:i($Count1)])*256"!][!//
                          [!IF "$EngressQueueSize = num:i(0)"!][!//
                            [!VAR "EngressQueueSize" = "num:i(text:split($SplitStr,',')[num:i(3)]) * 256"!][!//
                            [!IF "num:i($Index) = num:i(0)"!][!VAR "EngressQueueSize" = "num:i(3072)"!][!ENDIF!][!//
                          [!ENDIF!][!//"""

    if 'IF "$EngressQueueSize = num:i(0)"' in content:
        print('Fallback logic already present. Skipping patch.')
    else:
        # Regex to match the original assignment line (robust against whitespace)
        # Original: [!VAR "EngressQueueSize" = "num:i(text:split($FinalAlloc,' ')[num:i($Count1)])*256"!][!//
        regex = r'\[!VAR\s+"EngressQueueSize"\s*=\s*"num:i\(text:split\(\$FinalAlloc,\s*\'\s*\'\s*\)\[num:i\(\$Count1\)\]\)\s*\*\s*256"!\]\[!//'
        
        match = re.search(regex, content)
        if match:
            print('Found calculation block. Applying patch...')
            content = content.replace(match.group(0), fallback_logic)
        else:
            print('Trying looser match...')
            # Try matching just the variable name and value structure if regex fails
            loose_regex = r'\[!VAR\s+"EngressQueueSize"\s*=\s*".*?text:split\(\$FinalAlloc.*?\]\[!//'
            match = re.search(loose_regex, content)
            if match:
                print('Applied patch via loose match.')
                content = content.replace(match.group(0), fallback_logic)
            else:
                print('Could not find calculation block to patch.')

    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print('Template file updated successfully.')

except Exception as e:
    print(f'Error: {e}')

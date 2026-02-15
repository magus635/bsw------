import sys

path = '/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates/Eth/src/Eth_PBcfg.c'
try:
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Define the precise blocks
    new_logic = """[!VAR "EngressQueueSize" = "num:i(text:split($FinalAlloc,' ')[num:i($Count1)])*256"!][!//]
                          [!IF "$EngressQueueSize = num:i(0)"!][!//]
                            [!VAR "EngressQueueSize" = "num:i(text:split($SplitStr,',')[num:i(3)]) * 256"!][!//]
                            [!IF "num:i($Count1) = num:i(1)"!][!VAR "EngressQueueSize" = "num:i(3072)"!][!ENDIF!][!//]
                          [!ENDIF!][!//]"""

    # We use a broader match to find the old patch
    # The old patch had the Index check
    start_tag = '[!VAR "EngressQueueSize" = "num:i(text:split($FinalAlloc,'
    start_idx = content.find(start_tag)
    
    if start_idx != -1:
        # Find the next ENDIF for our block
        # We search for the specific structure we inserted
        end_tag = '[!ENDIF!][!//]'
        # It's actually the second ENDIF in our previous patch 
        # (one for Index check, one for EngressQueueSize check)
        # So we find the one that comes after "$Index" = num:i(0)
        
        pos = content.find('num:i($Index) = num:i(0)', start_idx)
        if pos != -1:
            end_idx = content.find(end_tag, pos) + len(end_tag)
            # Find the next one to close the outer IF
            end_idx = content.find(end_tag, end_idx) + len(end_tag)
            
            old_patch = content[start_idx-2 : end_idx]
            content = content.replace(old_patch, new_logic)
            print('Successfully replaced old Index-based patch with Count1-based patch.')
        else:
            print('Could not find the previous Index-based logic pattern.')
    else:
        print('Target start tag not found.')

    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)

except Exception as e:
    print(f'Error: {e}')

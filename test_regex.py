
import re

def test_regex():
    for_start_pattern = re.compile(r'\{%\s*for\s+([a-zA-Z_0-9,\s]+?)\s+in\s+([a-zA-Z_0-9\.\(\)]+?)\s*%\}')
    
    test_str = "{% for path_name_value in postbuild_params %}"
    match = for_start_pattern.search(test_str)
    if match:
        print(f"Match found! Vars: {match.group(1)}, Collection: {match.group(2)}")
    else:
        print("No match found for for-loop")

    var_pattern = re.compile(r'\{\{\s*(.+?)\s*\}\}')
    test_var = "{{ path_name_value.0 }}"
    match_var = var_pattern.search(test_var)
    if match_var:
        print(f"Var match found! Expr: {match_var.group(1)}")
    else:
        print("No match found for variable")

if __name__ == "__main__":
    test_regex()

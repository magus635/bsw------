
import re

def test_nested_regex():
    for_start_pattern = re.compile(r'\{%\s*for\s+([a-zA-Z_0-9,\s]+?)\s+in\s+([a-zA-Z_0-9\.\(\)]+?)\s*%\}')
    
    test_str = "{% for param_name, param_val in container.parameter_values.items() %}"
    match = for_start_pattern.search(test_str)
    if match:
        print(f"Match found! Vars: '{match.group(1)}', Collection: '{match.group(2)}'")
    else:
        print("No match found for nested for-loop")

if __name__ == "__main__":
    test_nested_regex()

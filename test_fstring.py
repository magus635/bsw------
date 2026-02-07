
def test_fstring():
    module_name = "Mcu"
    template = f"""
{{% for path_name_value in postbuild_params %}}
    ./* {{{{ path_name_value.0 }}}} */{{{{ path_name_value.1 }}}} = {{{{ path_name_value.2 }}}},
{{% endfor %}}
"""
    print(template)

if __name__ == "__main__":
    test_fstring()

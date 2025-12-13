
import unittest
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine

class TestEBTemplateEngine(unittest.TestCase):
    def setUp(self):
        self.engine = EBTemplateEngine()
        self.context = {
            'foo': 'bar',
            'num': 10,
            'items': ['A', 'B', 'C']
        }


    def test_basic_output(self):
        # Use unquoted or $ for variable
        template = r'Value: [!foo!]'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, 'Value: bar')

    def test_literal_output(self):
        template = r'Hello [!"World"!]!'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, 'Hello World!')

    def test_conditional_true(self):
        # Unquoted variable for condition
        template = r'[!IF foo!][!foo!][!ENDIF!]'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, 'bar')

    def test_conditional_false(self):
        # Unquoted variable for condition
        template = r'[!IF missing!][!foo!][!ELSE!]default[!ENDIF!]'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, 'default')

    def test_var_definition(self):
        # Use $ to access var
        template = r'[!VAR "myVar" = "123"!][!$myVar!]'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, '123')

    def test_loop(self):
        template = r'[!LOOP items!]-[!.!]-[!ENDLOOP!]'
        result = self.engine.render(template, self.context)
        self.assertEqual(result, '-A--B--C-')


    def test_nested_loop(self):
        ctx = {'matrix': [['1'], ['2']]}
        template = r'[!LOOP matrix!]([!LOOP .!][!.!][!ENDLOOP!])[!ENDLOOP!]'
        result = self.engine.render(template, ctx)
        self.assertEqual(result, '(1)(2)')

    def test_xpath_mock(self):
        # Mocking the configuration structure
        class MockParam:
            def __init__(self, val): self.value = val
        class MockContainer:
            def __init__(self, name, params=None):
                self.short_name = name
                self.parameter_values = params or {}
                self.sub_containers = []
                self.reference_values = {}
        class MockConfig:
            def __init__(self):
                self.containers = [
                    MockContainer('Mcu', {'Clock': MockParam(8000000)})
                ]

        ctx = {'configuration': MockConfig()}
        
        # Test 1: Full path to parameter
        template = r'[!node:value(as:modconf("Any")[1]/Mcu/Clock)!]'
        result = self.engine.render(template, ctx)
        self.assertEqual(result, '8000000')

    def test_functions(self):
        class MockNode:
            def __init__(self, name, val):
                self.short_name = name
                self.value = val
                
        node = MockNode('MyParam', '123')
        ctx = {'node': node}
        
        # Test node:name
        self.assertEqual(self.engine.render(r'[!node:name(node)!]', ctx), 'MyParam')
        # Test node:value
        self.assertEqual(self.engine.render(r'[!node:value(node)!]', ctx), '123')
        # Test num:i
        self.assertEqual(self.engine.render(r'[!num:i(node)!]', ctx), '123')


if __name__ == '__main__':
    unittest.main()

import unittest
import sys
import os
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.generator.template_engine import TemplateEngine

class TestTemplateEngine(unittest.TestCase):
    def setUp(self):
        self.engine = TemplateEngine()

    def test_variable_substitution(self):
        context = {'name': 'World'}
        template = "Hello {{ name }}!"
        self.assertEqual(self.engine.render(template, context), "Hello World!")

    def test_nested_variables(self):
        context = {'user': {'name': 'Alice'}}
        template = "Hello {{ user.name }}!"
        self.assertEqual(self.engine.render(template, context), "Hello Alice!")

    def test_for_loop(self):
        context = {'items': ['a', 'b', 'c']}
        template = "{% for item in items %}{{ item }}{% endfor %}"
        self.assertEqual(self.engine.render(template, context), "abc")

    def test_for_loop_with_items(self):
        context = {'data': {'k1': 'v1', 'k2': 'v2'}}
        template = "{% for k, v in data.items() %}{{ k }}:{{ v }} {% endfor %}"
        # Dictionary iteration order might vary but usually stable in modern Python
        rendered = self.engine.render(template, context)
        self.assertIn("k1:v1", rendered)
        self.assertIn("k2:v2", rendered)

    def test_nested_loops(self):
        context = {'groups': [{'items': [1, 2]}, {'items': [3, 4]}]}
        template = "{% for g in groups %}{% for i in g.items %}{{ i }}{% endfor %}{% endfor %}"
        self.assertEqual(self.engine.render(template, context), "1234")

    def test_conditionals(self):
        context = {'flag': True}
        template = "{% if flag %}Yes{% else %}No{% endif %}"
        self.assertEqual(self.engine.render(template, context), "Yes")
        
        context = {'flag': False}
        self.assertEqual(self.engine.render(template, context), "No")

    def test_nested_conditionals(self):
        context = {'a': True, 'b': False}
        template = "{% if a %}{% if b %}AB{% else %}A{% endif %}{% else %}None{% endif %}"
        self.assertEqual(self.engine.render(template, context), "A")

    def test_complex_conditions(self):
        context = {'val': 10, 'items': [1, 2, 3]}
        # Equality
        self.assertEqual(self.engine.render("{% if val == 10 %}OK{% endif %}", context), "OK")
        # Inequality
        self.assertEqual(self.engine.render("{% if val != 20 %}OK{% endif %}", context), "OK")
        # In
        self.assertEqual(self.engine.render("{% if 2 in items %}Found{% endif %}", context), "Found")
        # Not
        self.assertEqual(self.engine.render("{% if not flag %}No Flag{% endif %}", {'flag': False}), "No Flag")
        # Combined not and comparison
        self.assertEqual(self.engine.render("{% if not val == 20 %}Not 20{% endif %}", context), "Not 20")

    def test_loop_metadata(self):
        context = {'items': [1, 2, 3]}
        template = "{% for i in items %}{{ i }}{% if not loop.last %},{% endif %}{% endfor %}"
        self.assertEqual(self.engine.render(template, context), "1,2,3")

    def test_filters(self):
        context = {'name': 'world'}
        self.assertEqual(self.engine.render("{{ name | upper }}", context), "WORLD")
        self.assertEqual(self.engine.render("{{ items | length }}", {'items': [1,2,3]}), "3")

if __name__ == '__main__':
    unittest.main()

"""
Unit Tests for EB Template Engine
"""
import unittest
import sys
import os

# Add project root to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))

from autosar_configurator.generator.eb.lexer import Lexer, TokenType, tokenize
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode, SymbolTable
from autosar_configurator.generator.eb.context import ContextStack
from autosar_configurator.generator.eb.builtins import BuiltinFunctions
from autosar_configurator.generator.eb.renderer import Renderer


class TestLexer(unittest.TestCase):
    """Tests for the lexer/tokenizer"""
    
    def test_plain_text(self):
        tokens = tokenize("Hello World")
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.TEXT)
        self.assertEqual(tokens[0].content, "Hello World")
    
    def test_output_expression(self):
        tokens = tokenize('[!"Hello"!]')
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.OUTPUT)
    
    def test_if_directive(self):
        tokens = tokenize('[!IF condition!]')
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.IF)
        self.assertEqual(tokens[0].content, "condition")
    
    def test_loop_directive(self):
        tokens = tokenize('[!LOOP items!]content[!ENDLOOP!]')
        self.assertEqual(len(tokens), 3)
        self.assertEqual(tokens[0].type, TokenType.LOOP)
        self.assertEqual(tokens[1].type, TokenType.TEXT)
        self.assertEqual(tokens[2].type, TokenType.ENDLOOP)
    
    def test_var_directive(self):
        tokens = tokenize('[!VAR "name" = "value"!]')
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.VAR)
    
    def test_comment(self):
        tokens = tokenize('[!// This is a comment !]')
        self.assertEqual(len(tokens), 1)
        self.assertEqual(tokens[0].type, TokenType.COMMENT)
    
    def test_mixed_content(self):
        template = 'Before [!IF x!]Inside[!ENDIF!] After'
        tokens = tokenize(template)
        self.assertEqual(len(tokens), 5)
        self.assertEqual(tokens[0].type, TokenType.TEXT)
        self.assertEqual(tokens[1].type, TokenType.IF)
        self.assertEqual(tokens[2].type, TokenType.TEXT)
        self.assertEqual(tokens[3].type, TokenType.ENDIF)
        self.assertEqual(tokens[4].type, TokenType.TEXT)


class TestContextStack(unittest.TestCase):
    """Tests for context stack"""
    
    def test_push_pop(self):
        ctx = ContextStack()
        self.assertEqual(ctx.depth, 1)
        
        ctx.push()
        self.assertEqual(ctx.depth, 2)
        
        ctx.pop()
        self.assertEqual(ctx.depth, 1)
    
    def test_variable_scope(self):
        ctx = ContextStack()
        ctx.set_variable("x", 1)
        
        ctx.push()
        ctx.set_variable("y", 2)
        
        self.assertEqual(ctx.get_variable("x"), 1)  # Inherited
        self.assertEqual(ctx.get_variable("y"), 2)
        
        ctx.pop()
        self.assertEqual(ctx.get_variable("x"), 1)
        self.assertFalse(ctx.has_variable("y"))  # Out of scope
    
    def test_variable_assignment_updates_outer(self):
        # EB Tresos [!VAR!] semantics: re-assigning an existing variable updates
        # the scope that declared it (accumulator idiom), it does not shadow.
        ctx = ContextStack()
        ctx.set_variable("x", 1)

        ctx.push()
        ctx.set_variable("x", 2)  # updates the outer binding
        self.assertEqual(ctx.get_variable("x"), 2)

        ctx.pop()
        self.assertEqual(ctx.get_variable("x"), 2)  # update persisted

    def test_declare_variable_shadows(self):
        # declare_variable (used for MACRO parameters) creates a scope-local
        # binding that shadows the outer variable and is dropped on pop.
        ctx = ContextStack()
        ctx.set_variable("x", 1)

        ctx.push()
        ctx.declare_variable("x", 2)  # shadow, local to this scope
        self.assertEqual(ctx.get_variable("x"), 2)

        ctx.pop()
        self.assertEqual(ctx.get_variable("x"), 1)  # outer value restored


class TestSymbolTable(unittest.TestCase):
    """Tests for symbol table"""
    
    def test_register_and_lookup(self):
        st = SymbolTable()
        
        root = ConfigurationNode(
            short_name="Mcu",
            node_type="module",
            path="/Mcu"
        )
        
        st.register_module("Mcu", root)
        
        self.assertEqual(st.get_module("Mcu"), root)
        self.assertEqual(st.get_by_path("/Mcu"), root)
    
    def test_child_indexing(self):
        st = SymbolTable()
        
        root = ConfigurationNode(short_name="Mcu", node_type="module", path="/Mcu")
        child = ConfigurationNode(short_name="Config", node_type="container", path="/Mcu/Config")
        root.add_child(child)
        
        st.register_module("Mcu", root)
        
        self.assertEqual(st.get_by_path("/Mcu/Config"), child)


class TestBuiltins(unittest.TestCase):
    """Tests for built-in functions"""
    
    def setUp(self):
        self.symbol_table = SymbolTable()
        self.context_stack = ContextStack()
        self.builtins = BuiltinFunctions(self.symbol_table, self.context_stack)
    
    def test_num_i(self):
        self.assertEqual(self.builtins.num_i(10), 10)
        self.assertEqual(self.builtins.num_i("42"), 42)
        self.assertEqual(self.builtins.num_i("0xFF"), 255)
    
    def test_num_inttohex(self):
        self.assertEqual(self.builtins.num_inttohex(10, 4), "0x000A")
        self.assertEqual(self.builtins.num_inttohex(255, 2), "0xFF")
        self.assertEqual(self.builtins.num_inttohex(0), "0x0")
    
    def test_string_functions(self):
        self.assertEqual(self.builtins.string_upper("hello"), "HELLO")
        self.assertEqual(self.builtins.string_lower("HELLO"), "hello")
        self.assertEqual(self.builtins.string_trim("  x  "), "x")
        self.assertEqual(self.builtins.string_concat("a", "b", "c"), "abc")


class TestRenderer(unittest.TestCase):
    """Integration tests for the renderer"""
    
    def setUp(self):
        self.renderer = Renderer(strict=False)
    
    def test_plain_text(self):
        result = self.renderer.render("Hello World")
        self.assertEqual(result, "Hello World")
    
    def test_variable(self):
        result = self.renderer.render('[!VAR "x" = "42"!]Value: [!$x!]')
        self.assertEqual(result, "Value: 42")
    
    def test_simple_if_true(self):
        result = self.renderer.render(
            '[!VAR "flag" = "true"!][!IF $flag!]YES[!ENDIF!]'
        )
        self.assertEqual(result, "YES")
    
    def test_simple_if_false(self):
        result = self.renderer.render(
            '[!VAR "flag" = ""!][!IF $flag!]YES[!ELSE!]NO[!ENDIF!]'
        )
        self.assertEqual(result, "NO")
    
    def test_comment_stripped(self):
        result = self.renderer.render('Before[!// comment !]After')
        self.assertEqual(result, "BeforeAfter")
    
    def test_literal_output(self):
        result = self.renderer.render('[!"Hello World"!]')
        self.assertEqual(result, "Hello World")


class TestXPathEngine(unittest.TestCase):
    """Tests for the XPath engine"""
    
    def setUp(self):
        from autosar_configurator.generator.eb.xpath_engine import XPathEngine
        self.symbol_table = SymbolTable()
        self.context_stack = ContextStack()
        self.xpath = XPathEngine(self.symbol_table, self.context_stack)
        
        # Build test tree
        root = ConfigurationNode(short_name="Mcu", node_type="module", path="/Mcu")
        config = ConfigurationNode(short_name="McuConfig", node_type="container", path="/Mcu/McuConfig")
        clock1 = ConfigurationNode(short_name="Clock_0", node_type="container", path="/Mcu/McuConfig/Clock_0")
        clock2 = ConfigurationNode(short_name="Clock_1", node_type="container", path="/Mcu/McuConfig/Clock_1")
        freq = ConfigurationNode(short_name="Frequency", node_type="parameter", path="/Mcu/McuConfig/Clock_0/Frequency", value=8000000)
        
        root.add_child(config)
        config.add_child(clock1)
        config.add_child(clock2)
        clock1.add_child(freq)
        
        self.symbol_table.register_module("Mcu", root)
        self.context_stack.push(root)
    
    def test_as_modconf(self):
        result = self.xpath.evaluate("as:modconf('Mcu')")
        self.assertIsNotNone(result)
        self.assertEqual(result.short_name, "Mcu")
    
    def test_relative_path(self):
        result = self.xpath.evaluate("McuConfig")
        self.assertIsNotNone(result)
        self.assertEqual(result.short_name, "McuConfig")
    
    def test_nested_path(self):
        result = self.xpath.evaluate("McuConfig/Clock_0")
        self.assertIsNotNone(result)
        self.assertEqual(result.short_name, "Clock_0")
    
    def test_predicate_index(self):
        # Push to McuConfig context
        config = self.xpath.evaluate("McuConfig")
        self.context_stack.push(config)
        
        # Get children and filter by index
        result = self.xpath.evaluate("*[1]")
        self.assertIsNotNone(result)
        # First child should be Clock_0
        self.assertEqual(result.short_name, "Clock_0")


class TestSmartTrimming(unittest.TestCase):
    """Tests for Smart Trimming functionality"""
    
    def test_directive_only_line_not_output(self):
        """Ensure directive-only lines don't output extra content"""
        # The smart trimming works by suppressing whitespace from directive-only lines
        # in the output, not by setting flags during tokenization
        renderer = Renderer(strict=False)
        template = "A\n[!VAR \"x\" = \"1\"!]\nB"
        result = renderer.render(template)
        # Should not have blank line between A and B
        self.assertEqual(result.strip(), "A\nB")
    
    def test_mixed_line_not_marked(self):
        """Lines with text before/after directives should not be marked"""
        template = "Text [!IF x!] More text"
        tokens = tokenize(template)
        
        for tok in tokens:
            self.assertFalse(tok.directive_only_line)
    
    def test_smart_trim_output(self):
        """Test that directive-only lines don't add extra newlines"""
        renderer = Renderer(strict=False)
        template = """Start
[!VAR "x" = "1"!]
End"""
        result = renderer.render(template)
        # Should not have empty line between Start and End
        self.assertIn("Start", result)
        self.assertIn("End", result)


if __name__ == '__main__':
    unittest.main()

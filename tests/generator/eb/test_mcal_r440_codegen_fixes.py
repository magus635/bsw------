"""Regression tests for the MCAL R440 FuSa code-generation fixes.

Each test pins one engine behaviour that, when broken, produced the spurious
errors/warnings seen when generating the MCAL_R440_FuSa project:

* case-insensitive ``ecu:get`` lookup  -> Port.OutputModes* "parameter not found"
* loop-body [!VAR!] propagation         -> Can $ResHardwareModule / MessageRAM
* macro named-arg output parameters     -> Eth $RetVal / 88-000-15 scheduler
* enum dedup by definition_ref          -> Mcu "Enum name collision" warning
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))))

from autosar_configurator.generator.eb.renderer import Renderer


class TestEcuGetCaseInsensitive(unittest.TestCase):
    """ecu:get resolves keys case-insensitively (EB Tresos behaviour).

    Port.m builds keys via num:inttohex (uppercase 'A') while the vendor
    resource .properties stores them lowercase ('...a').
    """

    def test_uppercase_key_resolves_lowercase_resource(self):
        r = Renderer(strict=False)
        out = r.render(
            "[!\"ecu:get('Port.OutputModesA')\"!]",
            ecu_resources={'Port.OutputModesa': 'GPIO GTM_TOUT9'},
        )
        self.assertEqual(out.strip(), 'GPIO GTM_TOUT9')

    def test_exact_match_still_preferred(self):
        r = Renderer(strict=False)
        out = r.render(
            "[!\"ecu:get('Can.MCAN0ENDRAM')\"!]",
            ecu_resources={'Can.MCAN0ENDRAM': '0xC009FFFF'},
        )
        self.assertEqual(out.strip(), '0xC009FFFF')


class TestLoopVariablePropagation(unittest.TestCase):
    """A [!VAR!] created inside a [!LOOP!]/[!FOR!] body persists afterwards.

    EB Tresos [!VAR!] has no block scope. The Can templates create
    $ResHardwareModule inside a loop (via a [!CALL!]) and read it afterwards.
    """

    def test_for_body_var_visible_after_endfor(self):
        r = Renderer(strict=False)
        tpl = (
            "[!FOR \"i\" = \"0\" TO \"2\"!]"
            "[!VAR \"last\" = \"num:i($i)\"!]"
            "[!ENDFOR!]"
            "[!\"$last\"!]"
        )
        self.assertEqual(r.render(tpl).strip(), '2')


class TestBooleanNodeValue(unittest.TestCase):
    """node:value() of a boolean returns canonical XPath 'true'/'false'.

    A name-based STD_ON/TRUE heuristic breaks every `node:value(X) = 'true'`
    comparison the vendor templates rely on (Spi CS mode, Spi/Dma DMA-enable),
    and the C-level STD_ON/TRUE mapping is done in the templates, not here.
    """

    def _bool_node(self, name, val):
        from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
        return ConfigurationNode(short_name=name, node_type="parameter",
                                 path=f"/M/{name}", value=val, param_type="BOOLEAN")

    def test_feature_named_bool_is_lowercase_true(self):
        # name contains 'Enable' — must NOT become STD_ON
        from autosar_configurator.generator.eb.symbol_table import SymbolTable
        from autosar_configurator.generator.eb.context import ContextStack
        from autosar_configurator.generator.eb.builtins import BuiltinFunctions
        b = BuiltinFunctions(SymbolTable(), ContextStack())
        self.assertEqual(b.node_value(self._bool_node("SpiEnableDMA", True)), "true")
        self.assertEqual(b.node_value(self._bool_node("SpiEnableCs", False)), "false")

    def test_comparison_against_true_works(self):
        from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
        r = Renderer(strict=False)
        root = ConfigurationNode(short_name="Spi", node_type="module", path="/Spi")
        dev = ConfigurationNode(short_name="Dev", node_type="container", path="/Spi/Dev")
        dev.add_child(ConfigurationNode(short_name="SpiEnableCs", node_type="parameter",
                                        path="/Spi/Dev/SpiEnableCs", value=True, param_type="BOOLEAN"))
        root.add_child(dev)
        r.symbol_table.register_module("Spi", root)
        tpl = ('[!SELECT "Dev"!]'
               '[!IF "node:value(SpiEnableCs) = \'true\'"!]ON[!ELSE!]OFF[!ENDIF!]'
               '[!ENDSELECT!]')
        self.assertEqual(r.render(tpl, "Spi").strip(), "ON")


class TestImplicitDefaultVariant(unittest.TestCase):
    """The implicit "Default" output variant counts as NO post-build variant.

    The generator passes variant="Default" as the output-folder name even with no
    explicit post-build variants. EB Tresos then has variant:size()==0,
    variant:name()=='', variant:all()==[], so templates emit the unsuffixed
    ConfigSet name (e.g. Adc_ConfigSet, not Adc_ConfigSet_Default).
    """

    def _b(self, variant):
        from autosar_configurator.generator.eb.symbol_table import SymbolTable
        from autosar_configurator.generator.eb.context import ContextStack
        from autosar_configurator.generator.eb.builtins import BuiltinFunctions
        b = BuiltinFunctions(SymbolTable(), ContextStack())
        b._variant_name = variant
        return b

    def test_default_is_no_variant(self):
        b = self._b("Default")
        self.assertEqual(b.variant_size(), 1)
        self.assertEqual(b.variant_name(), "")
        self.assertEqual(b.variant_all(), ["Default"])

    def test_empty_is_no_variant(self):
        b = self._b("")
        self.assertEqual(b.variant_size(), 0)
        self.assertEqual(b.variant_name(), "")

    def test_real_variant_counts(self):
        b = self._b("VariantB")
        self.assertEqual(b.variant_size(), 1)
        self.assertEqual(b.variant_name(), "VariantB")
        self.assertEqual(b.variant_all(), ["VariantB"])


class TestEmptySequenceComparison(unittest.TestCase):
    """An empty sequence (e.g. empty text:grep) compares equal to '[]'.

    EB Tresos renders an empty sequence as '[]'; templates test "no match" via
    `text:grep(...) != '[]'`. Port.m's CG_GetSENTRxMuxSelect relies on this: a
    no-config SENT pin must yield PORT_RXRESERVE, not PORT_SENTx. The bug only
    surfaced after a prior loop iteration had assigned the variable a string.
    """

    def test_empty_grep_equals_bracket(self):
        r = Renderer(strict=False)
        tpl = ("[!VAR \"v\" = \"text:grep(text:split('aa; bb', '; '), 'zzz')\"!]"
               "[!IF \"$v != '[]'\"!]NE[!ELSE!]EQ[!ENDIF!]")
        self.assertEqual(r.render(tpl).strip(), "EQ")

    def test_empty_after_prior_string_in_loop(self):
        # iter0 matches -> v becomes a string; iter1 no-match -> v empty grep.
        r = Renderer(strict=False)
        tpl = (
            "[!FOR \"i\" = \"0\" TO \"1\"!]"
            "[!IF \"num:i($i) = num:i(0)\"!]"
            "[!VAR \"v\" = \"text:grep(text:split('SENT2B:P0', '; '), 'SENT2[a-zA-Z]*:.*')\"!]"
            "[!IF \"$v != '[]'\"!][!VAR \"v\" = \"substring-before(substring-after($v,'SENT2'),':')\"!]M[!ELSE!]R[!ENDIF!]"
            "[!ELSE!]"
            "[!VAR \"v\" = \"text:grep(text:split('SENT2B:P0', '; '), 'SENT0[a-zA-Z]*:.*')\"!]"
            "[!IF \"$v != '[]'\"!]X[!ELSE!]RSV[!ENDIF!]"
            "[!ENDIF!][!ENDFOR!]")
        self.assertEqual(r.render(tpl).strip(), "MRSV")


class TestVarBareRelativePath(unittest.TestCase):
    """[!VAR "x" = "ChildName"!] resolves the bare QName as a relative path.

    In EB Tresos an UNQUOTED token on a VAR right-hand side is a relative path
    (the child node's value), not a string literal. Adc_PBcfg.c relies on this:
    [!VAR "GroupChannelIndex" = "AdcChannelId"!] must capture the channel's id,
    not the literal text "AdcChannelId". A true literal (no matching child node)
    must still fall back to the identifier string.
    """

    def test_bare_path_resolves_to_child_value(self):
        from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
        r = Renderer(strict=False)
        root = ConfigurationNode(short_name="Adc", node_type="module", path="/Adc")
        wrap = ConfigurationNode(short_name="AdcChannel", node_type="container",
                                 path="/Adc/AdcChannel", is_wrapper=True)
        inst = ConfigurationNode(short_name="AN0", node_type="container", path="/Adc/AdcChannel/AN0")
        inst.add_child(ConfigurationNode(short_name="AdcChannelId", node_type="parameter",
                                         path="/Adc/AdcChannel/AN0/AdcChannelId", value=5))
        wrap.add_child(inst)
        root.add_child(wrap)
        r.symbol_table.register_module("Adc", root)
        tpl = ('[!LOOP "AdcChannel/*"!]'
               '[!VAR "x" = "AdcChannelId"!][!"$x"!]'
               '[!ENDLOOP!]')
        self.assertEqual(r.render(tpl, "Adc").strip(), "5")

    def test_true_literal_without_matching_child_is_preserved(self):
        from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
        r = Renderer(strict=False)
        root = ConfigurationNode(short_name="M", node_type="module", path="/M")
        r.symbol_table.register_module("M", root)
        self.assertEqual(r.render('[!VAR "x" = "ENABLED"!][!"$x"!]', "M").strip(), "ENABLED")


class TestMacroOutputParameter(unittest.TestCase):
    """A named macro argument acts as an in/out (output) parameter.

    The Eth_ShaperDet idiom: the caller passes RetVal and reads the macro's
    reassigned value back after the [!CALL!].
    """

    def test_named_arg_reassigned_in_macro_is_read_back(self):
        r = Renderer(strict=False)
        tpl = (
            "[!MACRO \"SetIt\", \"RetVal\"!]"
            "[!VAR \"RetVal\" = \"num:i(1)\"!]"
            "[!ENDMACRO!]"
            "[!VAR \"RetVal\" = \"num:i(255)\"!]"
            "[!CALL \"SetIt\", \"RetVal\" = \"num:i(255)\"!]"
            "[!\"$RetVal\"!]"
        )
        self.assertEqual(r.render(tpl).strip(), '1')


class TestEnumDedup(unittest.TestCase):
    """Same enum short name in different containers must not warn.

    Two distinct McuClockReferenceSelect enums (SYS/CPU vs CMU clocks) share a
    short name; this is legitimate EB Tresos and must not raise a warning.
    """

    def test_same_name_different_container_no_warning(self):
        import logging
        from autosar_configurator.generator.generator import CodeGenerator
        from autosar_configurator.core.model.definition_model import (
            EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType,
        )
        from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration

        def mk_enum(name, literals, ref):
            p = EcucParameterDef(short_name=name, param_type=EcucParameterType.ENUMERATION)
            p.literals = literals
            p.definition_ref = ref
            return p

        c1 = EcucContainerDef(short_name="ClockSettingConfig")
        c1.parameters = {"McuClockReferenceSelect": mk_enum(
            "McuClockReferenceSelect", ["SYS", "CPU"], "/Mcu/ClockSettingConfig/McuClockReferenceSelect")}
        c2 = EcucContainerDef(short_name="CmuConfig")
        c2.parameters = {"McuClockReferenceSelect": mk_enum(
            "McuClockReferenceSelect", ["CMU0", "CMU1"], "/Mcu/CmuConfig/McuClockReferenceSelect")}

        mod = EcucModuleDef(short_name="Mcu")
        mod.containers = {"ClockSettingConfig": c1, "CmuConfig": c2}
        cfg = EcucModuleConfiguration(short_name="Mcu", definition_ref="/Mcu")

        gen = CodeGenerator(mod, cfg)
        logger = logging.getLogger("autosar_configurator.generator.generator")
        with self.assertLogs(logger, level="WARNING") as cm:
            logger.warning("sentinel")  # ensure the context manager has >=1 record
            gen._get_enums()
        collisions = [m for m in cm.output if "Enum name collision" in m]
        self.assertEqual(collisions, [], f"unexpected collision warning: {collisions}")


class TestIncludeParentPath(unittest.TestCase):
    """[!INCLUDE "..\\X.m"!] with a parent ('..') segment must work.

    Sent/include/Sent_Cfg.h includes "..\\Sent.m" to load its macro library
    (CG_ConfigSwitch). A blanket '..' rejection silently dropped the include
    (unknown-macro -> empty), blanking every SENT_* switch. Traversal safety is
    enforced by the resolved-path containment check, not by banning '..'.
    """

    def test_parent_relative_include_loads_macro(self):
        import tempfile
        from pathlib import Path
        with tempfile.TemporaryDirectory() as td:
            mod = Path(td) / "Mod"
            (mod / "include").mkdir(parents=True)
            (mod / "Lib.m").write_text(
                '[!MACRO "Switch", "V" = ""!][!//\n'
                '[!IF "$V = \'true\'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//\n'
                '[!ENDMACRO!]\n'
            )
            child = mod / "include" / "child.ebt"
            child.write_text('[!INCLUDE "..\\Lib.m"!][!//\n'
                             'R=[!CALL "Switch","V" = "\'true\'"!]\n')
            r = Renderer(strict=False, template_dir=mod)
            out = r.render(child.read_text(), template_file=str(child))
        self.assertIn("(STD_ON)", out)

    def test_absolute_include_still_rejected(self):
        r = Renderer(strict=False)
        # Absolute path must still be refused (no traversal, no I/O).
        out = r.render('[!INCLUDE "/etc/passwd"!]X')
        self.assertEqual(out.strip(), "X")


class TestSuppressNewlineNoBlockLeak(unittest.TestCase):
    """A [!VAR!]'s own-line newline suppression must not leak across a block.

    The VAR sets _suppress_next_newline; if it survives an IF/LOOP boundary it
    eats a later, intentional blank line (Adc/Intc PBcfg.c '...mapped to Core0'
    blocks lost their leading blank).
    """

    def test_blank_after_var_then_if_is_preserved(self):
        r = Renderer(strict=False)
        tpl = 'A\n[!VAR "c" = "1"!][!IF "$c = 1"!][!ENDIF!]\n\nB'
        # VAR sets suppress; the IF clears it; the blank line survives -> 2 blanks.
        self.assertEqual(r.render(tpl), 'A\n\n\nB')


class TestGluedClosingBrace(unittest.TestCase):
    """ENDINDENT must not split an explicitly glued '}};' into '}\\n};'."""

    def test_glued_braces_not_split(self):
        r = Renderer(strict=False)
        tpl = '}[!INDENT "0"!][!ENDINDENT!]};'
        self.assertEqual(r.render(tpl), '}};')


class TestParentAxisAbsentChild(unittest.TestCase):
    """After a parent-axis ('..') step, an absent child name resolves EMPTY.

    Dma reads ../../DmaTransferId from inside a DmaChTransferConfig loop; two
    parent hops land on the DmaChannel (which has no DmaTransferId), so EB yields
    empty. The engine must NOT dive back into the sub-container's instance and
    return its id. A single-level ./DmaTransferId must still resolve.
    """

    def _tree(self):
        from autosar_configurator.generator.eb.symbol_table import ConfigurationNode
        root = ConfigurationNode(short_name="Dma", node_type="module", path="/Dma")
        ch = ConfigurationNode(short_name="Ch0", node_type="container", path="/Dma/Ch0")
        ch.add_child(ConfigurationNode(short_name="DmaChannelId", node_type="parameter",
                                       path="/Dma/Ch0/DmaChannelId", value=5, param_type="INTEGER"))
        wrap = ConfigurationNode(short_name="DmaChTransferConfig", node_type="container",
                                 path="/Dma/Ch0/DmaChTransferConfig", is_wrapper=True)
        inst = ConfigurationNode(short_name="DmaChTransferConfig_0", node_type="container",
                                 path="/Dma/Ch0/DmaChTransferConfig/DmaChTransferConfig_0")
        inst.add_child(ConfigurationNode(short_name="DmaTransferId", node_type="parameter",
                                         path="/Dma/Ch0/DmaChTransferConfig/DmaChTransferConfig_0/DmaTransferId",
                                         value=7, param_type="INTEGER"))
        wrap.add_child(inst); ch.add_child(wrap); root.add_child(ch)
        return root

    def test_absent_after_parent_axis_is_empty(self):
        r = Renderer(strict=False)
        r.symbol_table.register_module("Dma", self._tree())
        tpl = ('[!SELECT "Ch0/DmaChTransferConfig/DmaChTransferConfig_0"!]'
               'P=[!"../../DmaTransferId"!]<'
               'D=[!"./DmaTransferId"!]<'
               '[!ENDSELECT!]')
        out = r.render(tpl, "Dma")
        # Parent-axis lookup of the absent name -> empty; direct child -> 7.
        self.assertIn("P=<", out)
        self.assertIn("D=7<", out)


if __name__ == "__main__":
    unittest.main()

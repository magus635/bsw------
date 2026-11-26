## 1. Implementation

- [x] 1.1 Create `autosar_configurator/generator/rte/model.py` and `ib_parser.py` for IR dataclasses and `system/**/*_ib_bswmd.arxml` parsing
- [x] 1.2 Create `autosar_configurator/generator/rte/extractor.py` for multi-model `RteProjectModel` synthesis (`VENDOR-API-INFIX`, schedulable entities, exclusive areas, 3-tier MemMap rules, Os cores/applications)
- [x] 1.3 Create `autosar_configurator/generator/rte/renderers.py`, `generator.py`, and `__init__.py` for deterministic incremental header output
- [x] 1.4 Update `template_packs/davinci/Rte/include/Rte_Cfg.h` and integrate `RteSchMGenerator` with `GenerationController` (including `templates/Rte/` overlay override)
- [x] 1.5 Add comprehensive unit, controller, `clang -fsyntax-only`, and real `StartApplication1` vs `Appl/GenData` golden-parity tests
- [x] 1.6 Validate OpenSpec change strictly and verify all pytest suites pass

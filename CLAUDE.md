# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

<!-- OPENSPEC:START -->
# OpenSpec Instructions

These instructions are for AI assistants working in this project.

Always open `@/openspec/AGENTS.md` when the request:
- Mentions planning or proposals (words like proposal, spec, change, plan)
- Introduces new capabilities, breaking changes, architecture shifts, or big performance/security work
- Sounds ambiguous and you need the authoritative spec before coding

Use `@/openspec/AGENTS.md` to learn:
- How to create and apply change proposals
- Spec format and conventions
- Project structure and guidelines

Keep this managed block so 'openspec update' can refresh the instructions.

<!-- OPENSPEC:END -->

## Common Commands

```bash
# Install dependencies
./install_deps.sh          # or: pip install -r requirements.txt

# Run application (DaVinci UI — recommended)
python3 davinci_main.py

# Run application (classic UI) 已经废弃！
python3 main.py

# Auto-startup with dependency check
./start.sh

# Run all tests
python3 -m pytest tests/ -v

# Run a single test file
python3 -m pytest tests/core/test_observers.py -v

# Run tests with coverage
python3 -m pytest tests/ --cov=autosar_configurator --cov-report=html

# Quick verification
python3 verify.py
```

## Architecture

Three-layer architecture: **UI → Core → Generator**.

**Core** (`autosar_configurator/core/`): Data models, ARXML parsing/serialization, configuration management, validation, workspace management.
- `config_manager.py` — CRUD operations, `ProjectTypeDetector` (Vector vs EB Tresos detection, uses `TRESOS_PLUGINS_PATH` env var)
- `workspace_manager.py` — `WorkspaceProject` manages multiple BSW modules, cross-module reference resolution via EMF-style paths (`/Module/ContainerDef/Instance`)
- `model/` — `EcucModuleDef` → `EcucContainerDef` → `EcucParameterDef` (definition side); `EcucModuleConfiguration` → `EcucContainerValue` → `EcucParameterValue` (configuration side)
- `command.py` — Command pattern for undo/redo (SetParameterCommand, CreateContainerCommand, etc.)
- Observer pattern (`model/observers.py`) syncs data changes to UI automatically

**Generator** (`autosar_configurator/generator/`): EB Tresos-compatible template engine with custom lexer, XPath 2.0/3.0 engine, and built-in function library.
- `eb/renderer.py` — Template rendering (supports `[!IF]`, `[!LOOP]`, `[!MACRO]`, `[!SELECT]`, etc.)
- `eb/xpath_engine.py` — XPath evaluation for navigating AUTOSAR data
- `eb/builtins.py` — Built-in functions: `node:*`, `num:*`, `string:*`, `bit:*`, `ecu:*`, `variant:*`
- `generator.py` — Orchestrator; classifies parameters by ConfigClass (PRE-COMPILE/LINK-TIME/POST-BUILD)
- Templates in `generator/templates/` as `.ebt` files per module (Adc, Can, Mcu, Port, etc.)
- Fingerprint files (`.{ModuleName}.meta`) prevent redundant generation

**UI** (`autosar_configurator/ui/`): PySide6-based GUI.
- `davinci_main_window.py` — Main window (DaVinci-style, recommended entry point)
- `widgets/` — TreeView, ConfigPanel, SmartSearch, DependencyGraph, AIAssistant
- `wizards/` — Quick configuration wizards

## Key Conventions

- **Deterministic sorting**: Generators and config management use `sorted()` by name for reproducible output. Never introduce unsorted collection iteration in these paths without updating fingerprint logic and tests.
- **Relative paths**: All saved project paths are relative to project root for portability.
- **EMF-style references**: String paths resolve to object pointers via `WorkspaceProject.resolve_all_references()`, which builds reverse-reference indexes.
- **Strict vs non-strict rendering**: Template engine has two modes affecting error handling behavior.

## Development Guidelines

- After modifying model/serialization code, run: `python3 -m pytest tests/core/test_parser_serializer.py -q`
- After modifying templates or generator, verify fingerprint stability (`CodeGenerator._calculate_fingerprint()`).
- UI tests require a display environment (no headless SSH). Use `python3 -m pytest tests/ui/ -q` locally.
- Don't change generator sorting/traversal order without preserving fingerprint consistency and adding tests.
- Don't hardcode ECU parameters — use `ecu:get()` built-in function.

## Environment Variables

- `GEMINI_API_KEY` — Google Gemini API key for AI features
- `TRESOS_PLUGINS_PATH` — EB Tresos plugins path (affects project type detection and definition search paths)

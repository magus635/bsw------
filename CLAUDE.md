# CLAUDE.md

This file provides project-specific guidance for Claude Code (claude.ai/code) when working on the AUTOSAR Configurator repository.
It includes architecture overview, common commands, conventions, development guidelines, known pitfalls, and tips for effective collaboration with Claude.

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

Keep this managed block unchanged so that the `openspec update` command can automatically refresh these instructions when the central OpenSpec changes.

<!-- OPENSPEC:END -->

## Working Effectively with Claude Code

**Goal**: Reduce common friction points observed in past sessions (API instability, wrong approaches, buggy code, context fragmentation).

- **API & External Dependencies** (most frequent friction):
  - Always verify API availability and authentication first.
  - If a request involves external APIs, services, or environment-specific tools (e.g., TRESOS plugins), explicitly ask me to confirm the environment or provide current auth/status before proceeding.
  - Prefer adding retry logic, graceful error handling, or fallback paths in code.

- **Avoid Wrong Approach / Buggy Code**:
  - Always start with a reasoned plan: "First think step-by-step about the most reasonable implementation approach, then output code."
  - If uncertain about the best path, ask me clarifying questions before writing code.
  - After proposing code, suggest verification steps or unit tests.

- **Structured Prompting for Iteration**:
  - For complex changes, follow this template:
    1. High-level plan or proposal
    2. Detailed implementation steps
    3. Code changes
    4. Suggested tests or verification commands

- **Multi-Session Context**:
  - I sometimes run multiple parallel Claude Code sessions.
  - If context from another session is needed, ask me to provide it directly (paste relevant code, logs, or output into the chat).

- **General Best Practices**:
  - For bug fixes and debugging: Always provide error logs, relevant ARXML snippets, and current parameter values.
  - For multi-module changes: Reference specific files by path or use explicit EMF paths (e.g., `/Can/CanConfigSet/CanController[CanControllerId=0]`).
  - When proposing changes: First ask for a plan/proposal before editing code (per OpenSpec guidelines).
  - Be specific about ConfigClass (PRE-COMPILE/LINK-TIME/POST-BUILD) and variant handling.

## Runtime Requirements

- Python >= 3.9 (recommended 3.11+)
- Key dependencies: PySide6, lxml, custom EB Tresos-compatible template engine (.ebt files), pytest, coverage

## Common Commands

```bash
# Preferred: 用脚本确保一致性（包括虚拟环境等）
./install_deps.sh

# Alternative: 直接安装（仅依赖）
pip install -r requirements.txt

# Run application (DaVinci UI — recommended)
python3 davinci_main.py

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

# Code formatting and linting
black .
ruff check .  # or flake8

# Git workflow
git pull --rebase
git add -p
git commit -m "feat/config: ..."
```

## Additional Test Commands
```bash
# After model changes, always run:
python3 -m pytest tests/core/test_parser_serializer.py tests/core/test_command.py -q

# After generator changes, verify no unintended fingerprint changes:
[ -f verify_fingerprints.py ] && python3 verify_fingerprints.py
```

## Architecture

```
bsw图形配置工具/
├── autosar_configurator/     # Main package
│   ├── core/                 # Data models, parsing, workspace
│   ├── generator/            # Code generation engine
│   │   └── eb/               # EB Tresos template engine internals
│   ├── ui/                   # PySide6 GUI
│   ├── business/             # Business logic layer
│   ├── infrastructure/       # Infrastructure concerns
│   └── utils/                # Shared utilities
├── templates/                # .ebt template files per BSW module
├── definitions/              # AUTOSAR definition files
├── tests/                    # Test suite (mirrors package structure)
│   ├── core/
│   ├── generator/
│   └── ui/
└── davinci_main.py           # Sole entry point (legacy main.py / MainWindow retired)
```
实际测试的项目例子：
/Users/qlwang/Desktop/ImportEB_1
其中生成的os模块代码位于：
/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/generateCode/Os/Default/
在这个目录下包括了os，mcu，gpt等模块的生成代码。
os模块生成代码对应的代码模版位于：
/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/templates/Os/
os模块生成代码对应的config文件位于：
/Users/qlwang/Desktop/ImportEB_1/MCAL_R440_FuSa/arxml/Os.arxml


Three-layer architecture: UI → Core → Generator.
Core (autosar_configurator/core/): Data models, ARXML parsing/serialization, configuration management, validation, workspace management.
* config_manager.py — CRUD operations, ProjectTypeDetector (Vector vs EB Tresos detection, uses TRESOS_PLUGINS_PATH env var)
* workspace_manager.py — WorkspaceProject manages multiple BSW modules, cross-module reference resolution via EMF-style paths (/Module/ContainerDef/Instance)
* model/ — EcucModuleDef → EcucContainerDef → EcucParameterDef (definition side); EcucModuleConfiguration → EcucContainerValue → EcucParameterValue (configuration side)
* command.py — Command pattern for undo/redo (SetParameterCommand, CreateContainerCommand, etc.)
* Observer pattern (model/observers.py) syncs data changes to UI automatically

Generator (autosar_configurator/generator/): EB Tresos-compatible template engine with custom lexer, XPath 2.0/3.0 engine, and built-in function library.
* eb/renderer.py — Template rendering (supports [!IF], [!LOOP], [!MACRO], [!SELECT], etc.)
* eb/xpath_engine.py — XPath evaluation for navigating AUTOSAR data
* eb/builtins.py — Built-in functions: node:*, num:*, string:*, bit:*, ecu:*, variant:*
* generator.py — Orchestrator; classifies parameters by ConfigClass (PRE-COMPILE/LINK-TIME/POST-BUILD)
* Templates in generator/templates/ as .ebt files per module (Adc, Can, Mcu, Port, etc.)
Fingerprint files (.{ModuleName}.meta) prevent redundant generation

UI (autosar_configurator/ui/): PySide6-based GUI.
* davinci_main_window.py — Main window (DaVinci-style, recommended entry point)
* widgets/ — TreeView, ConfigPanel, SmartSearch, DependencyGraph, AIAssistant
* wizards/ — Quick configuration wizards

## Key Conventions
* Deterministic sorting: Generators and config management use sorted() by name for reproducible output. Never introduce unsorted collection iteration in these paths without updating fingerprint logic and tests.
* Relative paths: All saved project paths are relative to project root for portability.
* EMF-style references: String paths resolve to object pointers via WorkspaceProject.resolve_all_references(), which builds reverse-reference indexes.
* Strict vs non-strict rendering: `Renderer(strict=True)` (default) raises errors on undefined references and missing modules. `strict=False` creates fallback/dummy nodes and skips errors — used by the production generator (`EBTemplateEngine(strict=False)`) to allow partial rendering.

## Development Guidelines
* After modifying model/serialization code, run: python3 -m pytest tests/core/test_parser_serializer.py -q
* After modifying templates or generator, verify fingerprint stability (CodeGenerator._calculate_fingerprint()).
* UI tests require a display environment (no headless SSH). Use python3 -m pytest tests/ui/ -q locally.
* Don't change generator sorting/traversal order without preserving fingerprint consistency and adding tests.
* Don't hardcode ECU parameters — use ecu:get() built-in function.

## Common Pitfalls
* Reference resolution fails if paths use absolute instead of EMF-style relative paths.
* Generation differences on Windows vs Linux due to path separators — always use POSIX-style in code.
* POST-BUILD parameters require special handling in templates (use variant:* functions).

## Environment Variables
* GEMINI_API_KEY — Optional: Google Gemini API key for legacy/experimental AI features (currently not primary)
* TRESOS_PLUGINS_PATH — Required for EB Tresos project type detection and definition lookup


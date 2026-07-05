# Project Context

## Purpose

This project is a Python/PySide6 AUTOSAR Classic BSW/MCAL configuration tool. It focuses on EB Tresos project import, ARXML/XDM/EPC parsing, graphical configuration editing, validation, chip resource handling, and EB Tresos-style code generation.

## Tech Stack

- Python 3.10+
- PySide6 for the desktop UI
- lxml for XML/ARXML parsing
- Jinja2 plus custom EB template rendering
- pytest / pytest-qt for tests
- Google Gemini for optional AI assistant features
- keyring for API-key storage when available

## Project Conventions

### Code Style

- Prefer existing local patterns over new abstractions.
- Keep UI behavior in controllers under `autosar_configurator/ui/controllers/` when possible.
- Keep model, parser, serializer, validation, hardware, importer, and generator responsibilities separated.
- Avoid silent fallbacks that can generate wrong AUTOSAR code.

### Architecture Patterns

- `davinci_main.py` is the application entry point.
- `DaVinciMainWindow` assembles the UI and shared state.
- Controllers own major UI workflows: project, edit, validation, generation, navigation, dependency graph, AI assistant, and wizards.
- `WorkspaceManager` owns project persistence and EB project import.
- `CodeGenerator` resolves templates only from project/user template directories. There are no built-in default runtime templates.
- Test templates live under `tests/fixtures/templates/`.

### Testing Strategy

- Run focused unit/generator tests before marking work done:
  - `python -m pytest tests/core/test_observers.py -q`
  - `python -m pytest tests/generator -q`
- Run UI tests with `QT_QPA_PLATFORM=offscreen`.
- Default test runs should not depend on network access or user-local EB project paths.
- AI tests should mock Gemini unless the test is explicitly marked/manual.
- Validate OpenSpec changes with `openspec validate --all --strict`.

### Git Workflow

- Keep changes scoped.
- Do not revert unrelated user changes.
- Use OpenSpec proposals for new capabilities, breaking changes, architecture shifts, or major performance/security work.
- Skip proposals for documentation sync, bug fixes restoring intended behavior, comments, formatting, and non-breaking dependency/configuration updates.

## Domain Context

- The tool handles AUTOSAR Classic ECUC definitions and configuration values.
- EB Tresos compatibility includes project structure discovery, XDM/EPC value handling, `.properties` hardware resources, and vendor templates.
- Generated C configuration must match the user's loaded definitions/templates/chip resources; plausible-looking default output is unsafe.
- Config classes and variants matter: PRE-COMPILE, LINK-TIME, POST-BUILD, and EB/AUTOSAR variant semantics should not be guessed.

## Important Constraints

- No runtime default templates for production generation.
- Preserve EB value round-trip semantics where possible.
- Keep external EB project paths optional; tests must provide fixtures or skip.
- Keep AI/network behavior optional and non-blocking for normal local validation.

## External Dependencies

- Google Gemini API for AI features, configured via `GEMINI_API_KEY` or AI Assistant settings.
- OS keychain through `keyring` for secret storage, with QSettings fallback.
- EB Tresos project directories and chip `.properties` files for integration-style workflows.

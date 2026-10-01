## 1. Environment & Startup Robustness
- [x] 1.1 Verify and test `start.sh` fallback and architecture detection logic
- [x] 1.2 Document cross-platform virtual environment cleanup guidance

## 2. Choice & Reference Parameter Normalization
- [x] 2.1 Refactor `ConfigManager._cleanup_unknown_parameters` to check container definitions for single references and matching reference names
- [x] 2.2 Suppress redundant false-positive warnings for recognized vendor reference patterns while ensuring full data preservation
- [x] 2.3 Add unit test covering container reference recognition and vendor textual reference handling

## 3. Verification & Validation
- [x] 3.1 Run unit test suite to verify zero regression in project loading and generation
- [x] 3.2 Run `openspec validate improve-choice-containers-and-robustness --strict`

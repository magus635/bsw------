# Gotchas

## 2026-06-06

- Running focused pytest node ids from memory is error-prone. Confirm class names with `rg -n "^class|def test_name"` before using fully-qualified pytest ids, otherwise pytest can report "not found" and no verification actually runs.

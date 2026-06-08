# Gotchas

## 2026-06-06

- Running focused pytest node ids from memory is error-prone. Confirm class names with `rg -n "^class|def test_name"` before using fully-qualified pytest ids, otherwise pytest can report "not found" and no verification actually runs.
- When constructing `ConfigurationNode` in quick probes, use keyword arguments for `value` and `param_type`. Positional arguments can silently miss the intended boolean type and invalidate template-engine conclusions.
- Pytest `--basetemp` may leave a `...current` symlink, not only directories. Check with `ls -la` before cleanup; use `unlink` for the symlink and `rmdir` only for empty directories.
- Do not put Markdown backticks unescaped inside shell command strings. The shell treats backticks as command substitution, so quote patterns with single quotes that contain no backticks or escape them first.

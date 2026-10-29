# Gotchas

## 2026-06-06

- Running focused pytest node ids from memory is error-prone. Confirm class names with `rg -n "^class|def test_name"` before using fully-qualified pytest ids, otherwise pytest can report "not found" and no verification actually runs.
- When constructing `ConfigurationNode` in quick probes, use keyword arguments for `value` and `param_type`. Positional arguments can silently miss the intended boolean type and invalidate template-engine conclusions.
- Pytest `--basetemp` may leave a `...current` symlink, not only directories. Check with `ls -la` before cleanup; use `unlink` for the symlink and `rmdir` only for empty directories.
- Do not put Markdown backticks unescaped inside shell command strings. The shell treats backticks as command substitution, so quote patterns with single quotes that contain no backticks or escape them first.

## 2026-10-28

- In zsh, an unmatched shell glob aborts the command before it runs. Discover optional files with rg --files -g instead of passing an unchecked wildcard path.

## 2026-10-29

- `PLACEHOLDER` (an ECU resource entry still to fill in) is `None`, so `flat.get(key) is PLACEHOLDER` is also true for an absent key. Test presence with `key in flat` first whenever "empty" and "absent" must be told apart.
- In zsh a variable holding several paths is not split into words (`ruff check $FILES` passes one long path). Use an array, `${=FILES}`, or run the snippet with `bash -c`.
- macOS has no `timeout` command. Use the tool's own timeout instead of wrapping commands in `timeout N`.
- A `null` in chip YAML is not always a placeholder: vendor `.properties` lines like `Gtm.TriggerXModule4:` are legitimately empty (49 such values in the library). Count the real data before turning "is `None`" into a warning rule.

"""Tests for the base snapshot store and value-origin classification (design §6.5, §6.7).

The snapshot is the arxml file ``config/base/<Module>.arxml`` the tool writes after a merge
is accepted; ``write_base`` returns its hash for ``.dpa``, ``read_base`` refuses a file that
no longer matches that hash. Origins are never stored: they are derived by comparing the
live configuration with the snapshot and the snapshot's layers.

Fixtures are written into ``tmp_path`` through the real serializer — a hand-written arxml
would test the parser against itself and hide a serializer/parser disagreement.
"""
import hashlib

import pytest

from autosar_configurator.core.baseline.compose import Layer
from autosar_configurator.core.baseline.merge import MergeKind, three_way_merge
from autosar_configurator.core.baseline.origin import Origin, classify, origins_for
from autosar_configurator.core.baseline.store import read_base, write_base
from autosar_configurator.core.baseline.values import flatten
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
)

GEN = "P:/Mcu/McuGeneral."
REF = "R:/Mcu/McuGeneral."
SUB = "P:/Mcu/McuGeneral/McuSub."
MOD = "P:/Mcu."


# --- fixtures -------------------------------------------------------------------

def _config(name="Mcu", top="McuGeneral", containers=None):
    """A value collection with the named top-level containers (``None``: none)."""
    cfg = EcucModuleConfiguration(short_name=name, definition_ref="/X/Mcu")
    for short_name in containers if containers is not None else [top]:
        cfg.add_container(EcucContainerValue(short_name=short_name,
                                             definition_ref=f"/X/Mcu/{short_name}"))
    return cfg


def _container(cfg, name="McuGeneral"):
    return next(c for c in cfg.containers if c.short_name == name)


def _set(cfg, name, value, container="McuGeneral"):
    """Write ``value`` as a parameter of ``container``; a list is a multi-value parameter."""
    target = _container(cfg, container)
    if isinstance(value, list):
        target.multi_parameter_values[name] = [
            EcucParameterValue(f"/X/{name}", item, index=i) for i, item in enumerate(value)]
    else:
        target.parameter_values[name] = EcucParameterValue(f"/X/{name}", value)


def _ref(cfg, name, value_ref, container="McuGeneral"):
    _container(cfg, container).reference_values[name] = EcucReferenceValue(
        f"/X/{name}", value_ref, dest_type="ECUC-REFERENCE-DEF")


def _module_param(cfg, name, value):
    cfg.set_parameter_value(name, value, f"/X/Mcu/{name}")


def _sub(cfg, parent_path=("McuGeneral",), depth=3):
    """Add a nested ``McuSub`` with ``Depth`` under the named container path."""
    parent = _container(cfg, parent_path[0])
    for name in parent_path[1:]:
        parent = next(c for c in parent.sub_containers if c.short_name == name)
    sub = EcucContainerValue(short_name="McuSub", definition_ref="/X/Mcu/McuGeneral/McuSub")
    sub.parameter_values["Depth"] = EcucParameterValue("/X/Depth", depth)
    parent.add_sub_container(sub)
    return sub


# --- store ----------------------------------------------------------------------

def test_write_read_roundtrip_hash(tmp_path):
    """write_base returns the file's sha256; read_base with that hash reads the values back."""
    cfg = _config()
    _set(cfg, "Speed", 5)
    _set(cfg, "L", [1, 2, 3])
    _ref(cfg, "Clk", "/Mcu/Clk/McuClk0")
    _module_param(cfg, "ModInt", 3)
    _sub(cfg, depth=4)

    path = tmp_path / "Mcu.arxml"
    digest = write_base(path, cfg)

    assert digest.startswith("sha256:")
    assert digest == "sha256:" + hashlib.sha256(path.read_bytes()).hexdigest()

    loaded = read_base(path, digest)
    assert loaded is not None
    assert loaded.short_name == "Mcu"
    assert flatten(loaded) == flatten(cfg)

    # Deterministic: writing the same configuration twice gives the same bytes and hash
    again = tmp_path / "Mcu_again.arxml"
    assert write_base(again, cfg) == digest
    assert again.read_bytes() == path.read_bytes()


def test_read_base_missing_file_returns_none(tmp_path, caplog):
    """No snapshot file: None and a warning, never an exception."""
    with caplog.at_level("WARNING"):
        assert read_base(tmp_path / "Mcu.arxml", "sha256:00") is None
    assert any("不存在" in record.getMessage() and "Mcu.arxml" in record.getMessage()
               for record in caplog.records)


def test_write_base_leaves_directories_to_the_caller(tmp_path):
    """No directory logic here: an absent parent fails, it is not created."""
    cfg = _config()
    _set(cfg, "Speed", 5)
    with pytest.raises(OSError):
        write_base(tmp_path / "base" / "Mcu.arxml", cfg)
    assert not (tmp_path / "base").exists()


def test_read_base_hash_mismatch_returns_none(tmp_path, caplog):
    """A wrong expected hash is a migration, not a parse error."""
    cfg = _config()
    _set(cfg, "Speed", 5)
    path = tmp_path / "Mcu.arxml"
    digest = write_base(path, cfg)
    with caplog.at_level("WARNING"):
        assert read_base(path, "sha256:" + "0" * 64) is None
    assert any("哈希不符" in record.getMessage() for record in caplog.records)

    # The expected hash is case-insensitive on the hex part
    assert read_base(path, digest.upper()) is not None


def test_read_base_unparseable_returns_none(tmp_path, caplog):
    """A file that does not parse: None and a warning, even with the hash of the bytes."""
    path = tmp_path / "Mcu.arxml"
    path.write_bytes(b"<AUTOSAR><broken")
    digest = "sha256:" + hashlib.sha256(path.read_bytes()).hexdigest()
    with caplog.at_level("WARNING"):
        assert read_base(path, digest) is None
    assert any("解析失败" in record.getMessage() for record in caplog.records)


def test_base_missing_or_tampered_treated_as_migration(tmp_path):
    """Review Focus 4: a missing or tampered snapshot behaves exactly like first enable.

    End to end through ``read_base`` → ``three_way_merge``: the snapshot the user accepted
    is gone (deleted, or one byte changed), so no value can be shown to be untouched, and
    every non-Pre difference is KEPT_USER. Pre still merges as Pre.

    The merge input is *exactly* what ``read_base`` returned — never a literal ``None``. If
    ``read_base`` ever returned the tampered configuration, the merge would ADOPT ``Speed``
    and this test would fail; passing ``None`` by hand would hide that.
    """
    base_cfg = _config()
    _set(base_cfg, "Speed", 5)
    _set(base_cfg, "Mode", "A")
    path = tmp_path / "Mcu.arxml"
    digest = write_base(path, base_cfg)

    # Base' moved both values and Pre owns Mode; Active still holds the accepted snapshot.
    new = _config()
    _set(new, "Speed", 7)
    _set(new, "Mode", "B")
    new_layers = {GEN + "Speed": Layer.REC, GEN + "Mode": Layer.PRE}
    active = _config()
    _set(active, "Speed", 5)
    _set(active, "Mode", "A")

    def merge_after_read():
        """Merge what ``read_base`` actually returned for the snapshot on disk."""
        snapshot = read_base(path, digest)
        return three_way_merge(flatten(snapshot) if snapshot is not None else None,
                               flatten(new), flatten(active), new_layers, set())

    # A healthy snapshot adopts the untouched value: the contrast that proves the test.
    healthy = merge_after_read()
    assert {(i.key, i.kind) for i in healthy.items} == {
        (GEN + "Speed", MergeKind.ADOPT), (GEN + "Mode", MergeKind.PRE_FORCED)}

    # Deleted snapshot.
    path.unlink()
    deleted = merge_after_read()
    non_pre = [i for i in deleted.items if i.key != GEN + "Mode"]
    assert non_pre and all(i.kind is MergeKind.KEPT_USER for i in non_pre)

    # Tampered snapshot: one byte changed, the recorded hash no longer matches.
    write_base(path, base_cfg)
    original = path.read_bytes()
    marker = b">5<"
    assert original.count(marker) == 1
    path.write_bytes(original.replace(marker, b">6<"))
    tampered = merge_after_read()
    assert {(i.key, i.kind) for i in tampered.items} == {
        (GEN + "Speed", MergeKind.KEPT_USER), (GEN + "Mode", MergeKind.PRE_FORCED)}


# --- origins --------------------------------------------------------------------

def test_classify_rec_vs_user():
    """Active = Base and Base's value came from Rec → REC; a user edit → USER."""
    active = _config()
    _set(active, "Speed", 5)
    _set(active, "Mode", "B")
    base = _config()
    _set(base, "Speed", 5)
    _set(base, "Mode", "A")
    base_layers = {GEN + "Speed": Layer.REC, GEN + "Mode": Layer.REC}

    assert classify(GEN + "Speed", flatten(active), flatten(base), base_layers, set(), set()) is Origin.REC
    assert classify(GEN + "Mode", flatten(active), flatten(base), base_layers, set(), set()) is Origin.USER


def test_classify_layer_maps_to_origin():
    """Each baseline layer keeps its own origin when Active still equals Base."""
    active = _config()
    _set(active, "Speed", 5)
    _set(active, "Mode", "A")
    _set(active, "Depth", 2)
    base = _config()
    _set(base, "Speed", 5)
    _set(base, "Mode", "A")
    _set(base, "Depth", 2)
    active_flat, base_flat = flatten(active), flatten(base)
    layers = {GEN + "Speed": Layer.REC, GEN + "Mode": Layer.DEFAULT,
              GEN + "Depth": Layer.DERIVED}

    assert classify(GEN + "Speed", active_flat, base_flat, layers, set(), set()) is Origin.REC
    assert classify(GEN + "Mode", active_flat, base_flat, layers, set(), set()) is Origin.DEFAULT
    assert classify(GEN + "Depth", active_flat, base_flat, layers, set(), set()) is Origin.DERIVED

    # A key Base does not have, or Base has but the layer map does not, is USER
    _set(active, "Flag", True)
    assert classify(GEN + "Flag", flatten(active), base_flat, layers, set(), set()) is Origin.USER
    assert classify(GEN + "Speed", active_flat, base_flat, {}, set(), set()) is Origin.USER
    # No snapshot at all: everything is USER
    assert classify(GEN + "Speed", active_flat, None, layers, set(), set()) is Origin.USER


def test_classify_pre_unlocked_is_not_pre():
    """Pre is read-only; unlocking it makes the value editable, so it is no longer PRE."""
    active = _config()
    _set(active, "Mode", "A")
    base = _config()
    _set(base, "Mode", "A")
    active_flat, base_flat = flatten(active), flatten(base)
    layers = {GEN + "Mode": Layer.PRE}
    pre_keys = {GEN + "Mode"}

    assert classify(GEN + "Mode", active_flat, base_flat, layers, set(), pre_keys) is Origin.PRE
    unlocked = {GEN + "Mode"}
    origin = classify(GEN + "Mode", active_flat, base_flat, layers, unlocked, pre_keys)
    assert origin is not Origin.PRE
    assert origin is Origin.REC          # a baseline value the user may now edit

    # An unlocked Pre value the user changed is a plain user value
    _set(active, "Mode", "C")
    assert classify(GEN + "Mode", flatten(active), base_flat, layers, unlocked,
                    pre_keys) is Origin.USER


def test_classify_pre_key_absent_from_base_and_active_is_still_pre():
    """Pre owns a key whether or not the baseline or the live config still has it.

    Ownership, not presence: the merge restores a Pre value the user deleted
    (``merge._forced_by_pre``), so the lock must report PRE for exactly those keys or the UI
    would offer an edit the next merge silently reverts.
    """
    active = _config()                   # the user deleted the Pre container
    base = _config(containers=[])
    pre_keys = {"C:/Mcu/McuPreset", "P:/Mcu/McuPreset.Mode"}
    layers = {GEN + "Speed": Layer.REC}  # the snapshot's layer map no longer mentions Pre

    assert classify("P:/Mcu/McuPreset.Mode", flatten(active), flatten(base),
                    layers, set(), pre_keys) is Origin.PRE
    assert classify("C:/Mcu/McuPreset", flatten(active), flatten(base),
                    layers, set(), pre_keys) is Origin.PRE

    # Unlocking still wins: the key is no longer PRE even though Pre owns it
    unlocked = {"P:/Mcu/McuPreset.Mode"}
    assert classify("P:/Mcu/McuPreset.Mode", flatten(active), flatten(base),
                    layers, unlocked, pre_keys) is Origin.USER

    # A key Pre does not own, absent from Base and Active, is USER
    assert classify("P:/Mcu/Other.X", flatten(active), flatten(base),
                    layers, set(), pre_keys) is Origin.USER


def test_origins_for_covers_container_reference_and_module_keys():
    """Every key flatten produces gets an origin — including C:, R: and module-level P:."""
    base = _config(containers=["McuGeneral", "McuOther"])
    _set(base, "Speed", 5)
    _ref(base, "Clk", "/Mcu/Clk/McuClk0")
    _module_param(base, "ModInt", 3)
    _sub(base, depth=4)
    base_flat = flatten(base)
    layers = {key: Layer.REC for key in base_flat}
    layers["C:/Mcu/McuOther"] = Layer.PRE
    layers[SUB + "Depth"] = Layer.DEFAULT
    layers[MOD + "ModInt"] = Layer.DERIVED
    pre_keys = {"C:/Mcu/McuOther"}

    active = _config(containers=["McuGeneral", "McuOther"])
    _set(active, "Speed", 5)
    _ref(active, "Clk", "/Mcu/Clk/McuClk0")
    _module_param(active, "ModInt", 3)
    _sub(active, depth=4)

    origins = origins_for(active, base, layers, set(), pre_keys)

    assert list(origins) == sorted(origins)                 # deterministic order
    assert set(origins) == set(flatten(active))             # every live key covered
    assert origins["C:/Mcu/McuGeneral"] is Origin.REC
    assert origins["C:/Mcu/McuOther"] is Origin.PRE
    assert origins["C:/Mcu/McuGeneral/McuSub"] is Origin.REC
    assert origins[GEN + "Speed"] is Origin.REC
    assert origins[REF + "Clk"] is Origin.REC
    assert origins[SUB + "Depth"] is Origin.DEFAULT
    assert origins[MOD + "ModInt"] is Origin.DERIVED

    # A key Active has and Base lacks (added by the user) is USER
    _set(active, "Mode", "B")
    assert origins_for(active, base, layers, set(), pre_keys)[GEN + "Mode"] is Origin.USER

    # No snapshot: everything is USER — except what Pre still owns
    no_snapshot = origins_for(active, None, {}, set(), pre_keys)
    assert no_snapshot["C:/Mcu/McuOther"] is Origin.PRE
    assert all(origin is Origin.USER
               for key, origin in no_snapshot.items() if key != "C:/Mcu/McuOther")


def test_origins_for_module_name_re_roots_every_key():
    """``module_name`` re-roots keys the same way ``flatten`` does, so they still match.

    A Pre fragment saved as its own value collection (``McuPreConfiguration``) must
    classify under the module's keys, not under its own short name — in the snapshot, in
    the layer map and in the Pre ownership set alike.
    """
    base = _config(name="McuPreConfiguration")
    _set(base, "Speed", 5)
    layers = {GEN + "Speed": Layer.PRE}
    pre_keys = set(flatten(base, "Mcu"))

    active = _config()
    _set(active, "Speed", 5)

    origins = origins_for(active, base, layers, set(), pre_keys, module_name="Mcu")
    assert origins[GEN + "Speed"] is Origin.PRE
    assert not any(key.startswith("McuPreConfiguration") for key in origins)

    # Re-rooted by the caller: without ``module_name`` the fragment's own keys do not match
    # the live configuration's, which is why both sides take the same root.
    unrooted = origins_for(active, base, layers, set(), set(flatten(base)))
    assert unrooted[GEN + "Speed"] is Origin.USER

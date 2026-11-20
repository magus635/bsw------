from autosar_configurator.core.baseline.merge import MergeKind


def test_davinci_importer_uses_valid_merge_kind():
    """Verify davinci_importer does not reference non-existent MergeKind.CREATED_IN_BASE."""
    import inspect
    from autosar_configurator.core import davinci_importer

    source = inspect.getsource(davinci_importer)
    assert "MergeKind.CREATED_IN_BASE" not in source
    assert hasattr(MergeKind, "CREATE")


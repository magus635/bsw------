"""Controllers extracted from DaVinciMainWindow to reduce the God Object.

Each controller groups a single responsibility (AI assistant, project I/O,
generation, …) and holds a back-reference to the main window for shared state
and Qt parenting. This is the first step of the P2-6 refactor; interfaces are
expected to tighten in later phases.
"""

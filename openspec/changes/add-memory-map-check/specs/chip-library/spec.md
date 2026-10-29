## ADDED Requirements

### Requirement: Optional Chip Memory Regions
A chip file MAY have `memory_regions`, a list of regions with a name, start address, size, type (`flash` or `ram`), the owning core (absent for memory shared by all cores, `local` for a core-local alias each core sees as its own) and whether it is cacheable. The library SHALL load and save the list unchanged, chip files without it SHALL load as before, and regions not yet confirmed SHALL carry the to-be-confirmed mark used for other chip data.

#### Scenario: Chip file without regions
- **WHEN** a chip file written before this change is loaded
- **THEN** it loads without error and has no memory regions

#### Scenario: Regions kept on save
- **WHEN** THA6206 with a region `CPU0BTCM` at `0x30100000`, size 192K, type `ram`, core 0, not cacheable is saved and loaded again
- **THEN** the region is unchanged and keeps its to-be-confirmed mark

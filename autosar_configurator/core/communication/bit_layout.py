"""AUTOSAR Motorola (BIG_ENDIAN) & Intel (LITTLE_ENDIAN) bit-layout analyzer."""

from typing import Dict, List, Optional, Sequence, Set, Tuple


def compute_signal_bits(
    bit_position: int,
    bit_size: int,
    endianness: str,
) -> List[Tuple[int, int]]:
    """Return occupied ``(byte_idx, bit_in_byte)`` positions for an AUTOSAR ComSignal.

    AUTOSAR/Vector stores ``ComBitPosition`` for ``BIG_ENDIAN`` using Motorola forward
    MSB numbering (step ``bit_in_byte -= 1`` and wrap ``-1 -> (byte_idx + 1, 7)``),
    and for ``LITTLE_ENDIAN`` / ``OPAQUE`` using Intel LSB numbering
    (``(bit_position + k) // 8, (bit_position + k) % 8``).
    """
    if bit_size <= 0 or bit_position < 0:
        return []

    norm_end = (endianness or "LITTLE_ENDIAN").strip().upper()
    positions: List[Tuple[int, int]] = []
    if norm_end == "BIG_ENDIAN":
        byte_idx = bit_position // 8
        bit_in_byte = bit_position % 8
        for _ in range(bit_size):
            positions.append((byte_idx, bit_in_byte))
            bit_in_byte -= 1
            if bit_in_byte < 0:
                byte_idx += 1
                bit_in_byte = 7
    else:
        for k in range(bit_size):
            b = bit_position + k
            positions.append((b // 8, b % 8))
    return positions


def analyze_pdu_bit_layout(
    signals: Sequence[Tuple[str, Optional[int], Optional[int], str]],
    pdu_length_bytes: Optional[int],
) -> Tuple[Dict[Tuple[int, int], List[str]], Set[str], Set[str]]:
    """Compute bit occupancy map, overlapping signal names, and out-of-bounds signals."""
    grid: Dict[Tuple[int, int], List[str]] = {}
    overlaps: Set[str] = set()
    out_of_bounds: Set[str] = set()

    for sig_name, bit_pos, bit_size, endianness in signals:
        if bit_pos is None or bit_pos < 0 or bit_size is None or bit_size <= 0:
            out_of_bounds.add(sig_name)
            continue

        cells = compute_signal_bits(bit_pos, bit_size, endianness)
        if not cells:
            out_of_bounds.add(sig_name)
            continue

        for byte_idx, bit_in_byte in cells:
            if pdu_length_bytes is not None and pdu_length_bytes >= 0 and byte_idx >= pdu_length_bytes:
                out_of_bounds.add(sig_name)
            occupants = grid.setdefault((byte_idx, bit_in_byte), [])
            occupants.append(sig_name)

    for occupants in grid.values():
        if len(occupants) > 1:
            overlaps.update(occupants)

    return grid, overlaps, out_of_bounds

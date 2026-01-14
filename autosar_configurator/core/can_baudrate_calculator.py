"""
CAN Baudrate Calculator Module

Automatically calculates CAN bit timing parameters (PRESDIV, PropSeg, Seg1, Seg2, SJW)
for a given target baudrate and clock frequency.

Formula:
    Bit Time (TQ) = Sync(1) + PropSeg + Seg1 + Seg2 + 3
    Baudrate = Clock / ((PRESDIV + 1) × Bit Time)
    Sample Point = (Sync + PropSeg + Seg1 + 2) / Bit Time × 100%
"""

from typing import Optional, Dict, List, Tuple


def calculate_can_timing(
    clock_hz: int,
    target_baudrate_hz: int,
    sample_point_percent: int = 75,
    is_fd: bool = False
) -> Optional[Dict]:
    """
    Calculate optimal CAN timing parameters for target baudrate.
    
    Args:
        clock_hz: CAN module clock frequency in Hz (e.g., 80_000_000 for 80MHz)
        target_baudrate_hz: Target baudrate in Hz (e.g., 500_000 for 500kbps)
        sample_point_percent: Target sample point percentage (default 75%)
        is_fd: Whether this is for CAN FD data phase (affects parameter ranges)
    
    Returns:
        Dictionary with calculated parameters:
        {
            'PRESDIV': int,      # Prescaler register value (actual prescaler - 1)
            'PropSeg': int,      # Propagation segment register value
            'Seg1': int,         # Phase segment 1 register value
            'Seg2': int,         # Phase segment 2 register value
            'SJW': int,          # Sync jump width register value
            'actual_baudrate': float,  # Actual achieved baudrate in Hz
            'sample_point': float,     # Actual sample point percentage
            'error_ppm': float,        # Baudrate error in parts per million
            'tq_count': int,           # Total time quanta per bit
        }
        Returns None if no valid configuration found.
    """
    if clock_hz <= 0 or target_baudrate_hz <= 0:
        return None
    
    # Define parameter ranges based on CAN type
    if is_fd:
        max_presdiv = 32
        max_propseg = 32
        max_seg1 = 32
        max_seg2 = 16
        max_sjw = 16
        tq_range = range(5, 81)  # CAN FD allows shorter bit times
    else:
        max_presdiv = 512
        max_propseg = 32
        max_seg1 = 32
        max_seg2 = 16
        max_sjw = 16
        tq_range = range(8, 26)  # Classic CAN typical range
    
    best_result = None
    min_error = float('inf')
    
    # Try different time quanta counts
    for tq_count in tq_range:
        # Calculate required prescaler
        prescaler_float = clock_hz / (target_baudrate_hz * tq_count)
        
        # Check if prescaler is a valid integer within range
        prescaler = round(prescaler_float)
        if prescaler < 1 or prescaler > max_presdiv:
            continue
        
        # Calculate actual baudrate with this prescaler
        actual_baudrate = clock_hz / (prescaler * tq_count)
        error = abs(actual_baudrate - target_baudrate_hz)
        error_ppm = error / target_baudrate_hz * 1_000_000
        
        # Skip if error is too large (> 0.5%)
        if error_ppm > 5000:
            continue
        
        if error < min_error:
            min_error = error
            
            # Calculate segment allocation based on sample point
            # Sample point occurs at end of Seg1
            # TQ allocation: Sync(1) + PropSeg + Seg1 + Seg2 = tq_count
            # Sample TQ = 1 + PropSeg + Seg1
            sample_tq = int(tq_count * sample_point_percent / 100)
            
            # Seg2 = tq_count - sample_tq (must be >= 1)
            seg2 = max(1, tq_count - sample_tq)
            
            # PropSeg + Seg1 = sample_tq - 1 (subtract sync segment)
            prop_seg1_total = sample_tq - 1
            
            # Distribute between PropSeg and Seg1 (roughly equal, or PropSeg slightly less)
            prop_seg = max(1, prop_seg1_total // 2)
            seg1 = max(1, prop_seg1_total - prop_seg)
            
            # Ensure within limits
            if prop_seg > max_propseg:
                seg1 += prop_seg - max_propseg
                prop_seg = max_propseg
            if seg1 > max_seg1:
                seg1 = max_seg1
            if seg2 > max_seg2:
                seg2 = max_seg2
            
            # SJW = min(4, Seg1, Seg2) - common rule
            sjw = min(4, seg1, seg2)
            
            # Calculate actual sample point
            actual_sample_tq = 1 + prop_seg + seg1
            actual_sample_point = actual_sample_tq / tq_count * 100
            
            best_result = {
                'PRESDIV': prescaler - 1,  # Register value is prescaler - 1
                'PropSeg': prop_seg - 1,   # Register value
                'Seg1': seg1 - 1,          # Register value
                'Seg2': seg2 - 1,          # Register value
                'SJW': sjw - 1,            # Register value
                'actual_baudrate': actual_baudrate,
                'sample_point': actual_sample_point,
                'error_ppm': error_ppm,
                'tq_count': tq_count,
            }
            
            # If perfect match, return immediately
            if error_ppm < 1:
                break
    
    return best_result


def get_common_baudrates() -> List[Tuple[str, int]]:
    """
    Get list of common CAN baudrates.
    
    Returns:
        List of (display_name, baudrate_hz) tuples
    """
    return [
        ("125 kbps", 125_000),
        ("250 kbps", 250_000),
        ("500 kbps", 500_000),
        ("800 kbps", 800_000),
        ("1 Mbps", 1_000_000),
    ]


def get_common_fd_baudrates() -> List[Tuple[str, int]]:
    """
    Get list of common CAN FD data phase baudrates.
    
    Returns:
        List of (display_name, baudrate_hz) tuples
    """
    return [
        ("1 Mbps", 1_000_000),
        ("2 Mbps", 2_000_000),
        ("4 Mbps", 4_000_000),
        ("5 Mbps", 5_000_000),
        ("8 Mbps", 8_000_000),
    ]


def validate_timing_parameters(
    presdiv: int,
    prop_seg: int,
    seg1: int,
    seg2: int,
    sjw: int,
    clock_hz: int,
    is_fd: bool = False
) -> Dict:
    """
    Validate timing parameters and calculate resulting baudrate.
    
    Args:
        presdiv: PRESDIV register value (0-511)
        prop_seg: PropSeg register value
        seg1: Seg1 register value
        seg2: Seg2 register value
        sjw: SJW register value
        clock_hz: Clock frequency in Hz
        is_fd: Whether this is for CAN FD
    
    Returns:
        {
            'valid': bool,
            'baudrate': float,
            'sample_point': float,
            'errors': List[str]
        }
    """
    errors = []
    
    # Convert register values to actual values
    prescaler = presdiv + 1
    prop = prop_seg + 1
    s1 = seg1 + 1
    s2 = seg2 + 1
    sw = sjw + 1
    
    # Validate ranges
    if prescaler < 1 or prescaler > 512:
        errors.append(f"PRESDIV out of range: {presdiv} (valid: 0-511)")
    
    max_propseg = 32 if not is_fd else 32
    if prop < 1 or prop > max_propseg:
        errors.append(f"PropSeg out of range: {prop_seg}")
    
    max_seg1 = 32 if not is_fd else 32
    if s1 < 1 or s1 > max_seg1:
        errors.append(f"Seg1 out of range: {seg1}")
    
    max_seg2 = 16 if not is_fd else 16
    if s2 < 1 or s2 > max_seg2:
        errors.append(f"Seg2 out of range: {seg2}")
    
    # SJW must be <= min(Seg1, Seg2)
    if sw > min(s1, s2):
        errors.append(f"SJW ({sw}) must be <= min(Seg1, Seg2) = {min(s1, s2)}")
    
    # Calculate bit time and baudrate
    tq_count = 1 + prop + s1 + s2  # Sync + PropSeg + Seg1 + Seg2
    baudrate = clock_hz / (prescaler * tq_count)
    
    # Calculate sample point
    sample_tq = 1 + prop + s1
    sample_point = sample_tq / tq_count * 100
    
    return {
        'valid': len(errors) == 0,
        'baudrate': baudrate,
        'sample_point': sample_point,
        'tq_count': tq_count,
        'errors': errors
    }

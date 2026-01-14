"""
Unit tests for CAN Baudrate Calculator

Tests the calculate_can_timing function and related utilities.
"""

import pytest
from autosar_configurator.core.can_baudrate_calculator import (
    calculate_can_timing,
    get_common_baudrates,
    get_common_fd_baudrates,
    validate_timing_parameters
)


class TestCalculateCanTiming:
    """Tests for calculate_can_timing function"""
    
    def test_500kbps_80mhz(self):
        """Test 500kbps calculation with 80MHz clock"""
        result = calculate_can_timing(80_000_000, 500_000)
        
        assert result is not None
        # Actual baudrate should be close to target
        assert abs(result['actual_baudrate'] - 500_000) < 1000  # < 1kHz error
        # Sample point should be in reasonable range
        assert 70 <= result['sample_point'] <= 85
        # Error should be minimal
        assert result['error_ppm'] < 100
        # All parameters should be non-negative
        assert result['PRESDIV'] >= 0
        assert result['PropSeg'] >= 0
        assert result['Seg1'] >= 0
        assert result['Seg2'] >= 0
        assert result['SJW'] >= 0
    
    def test_1mbps_80mhz(self):
        """Test 1Mbps calculation with 80MHz clock"""
        result = calculate_can_timing(80_000_000, 1_000_000)
        
        assert result is not None
        assert abs(result['actual_baudrate'] - 1_000_000) < 5000  # < 5kHz error
        assert 70 <= result['sample_point'] <= 85
    
    def test_250kbps_80mhz(self):
        """Test 250kbps calculation with 80MHz clock"""
        result = calculate_can_timing(80_000_000, 250_000)
        
        assert result is not None
        assert abs(result['actual_baudrate'] - 250_000) < 500
        assert 70 <= result['sample_point'] <= 85
    
    def test_125kbps_80mhz(self):
        """Test 125kbps calculation with 80MHz clock"""
        result = calculate_can_timing(80_000_000, 125_000)
        
        assert result is not None
        assert abs(result['actual_baudrate'] - 125_000) < 250
    
    def test_500kbps_40mhz(self):
        """Test 500kbps with 40MHz clock (different frequency)"""
        result = calculate_can_timing(40_000_000, 500_000)
        
        assert result is not None
        assert abs(result['actual_baudrate'] - 500_000) < 1000
    
    def test_custom_sample_point(self):
        """Test with custom sample point"""
        result = calculate_can_timing(80_000_000, 500_000, sample_point_percent=80)
        
        assert result is not None
        # Sample point should be close to 80%
        assert 75 <= result['sample_point'] <= 85
    
    def test_invalid_zero_clock(self):
        """Test with zero clock frequency"""
        result = calculate_can_timing(0, 500_000)
        assert result is None
    
    def test_invalid_zero_baudrate(self):
        """Test with zero baudrate"""
        result = calculate_can_timing(80_000_000, 0)
        assert result is None
    
    def test_invalid_negative_values(self):
        """Test with negative values"""
        result = calculate_can_timing(-80_000_000, 500_000)
        assert result is None
        
        result = calculate_can_timing(80_000_000, -500_000)
        assert result is None


class TestCanFdTiming:
    """Tests for CAN FD timing calculations"""
    
    def test_2mbps_fd_80mhz(self):
        """Test 2Mbps CAN FD data phase"""
        result = calculate_can_timing(80_000_000, 2_000_000, is_fd=True)
        
        assert result is not None
        assert abs(result['actual_baudrate'] - 2_000_000) < 50_000
    
    def test_5mbps_fd_80mhz(self):
        """Test 5Mbps CAN FD data phase"""
        result = calculate_can_timing(80_000_000, 5_000_000, is_fd=True)
        
        # High speed may have larger error tolerance
        if result:
            assert abs(result['actual_baudrate'] - 5_000_000) < 250_000


class TestValidateTimingParameters:
    """Tests for validate_timing_parameters function"""
    
    def test_valid_parameters(self):
        """Test validation of correct parameters"""
        result = validate_timing_parameters(
            presdiv=9,    # Prescaler = 10
            prop_seg=4,   # PropSeg = 5
            seg1=5,       # Seg1 = 6
            seg2=3,       # Seg2 = 4
            sjw=3,        # SJW = 4
            clock_hz=80_000_000
        )
        
        assert result['valid'] == True
        assert len(result['errors']) == 0
        assert result['baudrate'] > 0
        assert 0 < result['sample_point'] < 100
    
    def test_invalid_sjw(self):
        """Test that SJW validation catches error"""
        result = validate_timing_parameters(
            presdiv=9,
            prop_seg=4,
            seg1=5,
            seg2=2,    # Seg2 = 3
            sjw=4,     # SJW = 5 > min(Seg1, Seg2)
            clock_hz=80_000_000
        )
        
        assert result['valid'] == False
        assert any('SJW' in err for err in result['errors'])


class TestCommonBaudrates:
    """Tests for common baudrate presets"""
    
    def test_get_common_baudrates(self):
        """Test common baudrate list"""
        baudrates = get_common_baudrates()
        
        assert len(baudrates) >= 4
        # Check expected common values exist
        baudrate_values = [b[1] for b in baudrates]
        assert 125_000 in baudrate_values
        assert 250_000 in baudrate_values
        assert 500_000 in baudrate_values
        assert 1_000_000 in baudrate_values
    
    def test_get_common_fd_baudrates(self):
        """Test common FD baudrate list"""
        baudrates = get_common_fd_baudrates()
        
        assert len(baudrates) >= 3
        baudrate_values = [b[1] for b in baudrates]
        assert 2_000_000 in baudrate_values or 1_000_000 in baudrate_values


class TestCalculationRoundtrip:
    """Tests that calculated values can be validated back"""
    
    def test_roundtrip_500kbps(self):
        """Calculate 500kbps, then validate the result"""
        calc_result = calculate_can_timing(80_000_000, 500_000)
        assert calc_result is not None
        
        valid_result = validate_timing_parameters(
            presdiv=calc_result['PRESDIV'],
            prop_seg=calc_result['PropSeg'],
            seg1=calc_result['Seg1'],
            seg2=calc_result['Seg2'],
            sjw=calc_result['SJW'],
            clock_hz=80_000_000
        )
        
        assert valid_result['valid'] == True
        # Validate baudrate matches
        assert abs(valid_result['baudrate'] - calc_result['actual_baudrate']) < 1

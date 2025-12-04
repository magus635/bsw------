"""
Unit tests for search engine
"""
import pytest
from autosar_configurator.core.search_engine import SearchEngine, SearchMode, SearchResult
from autosar_configurator.core.model.container import Container, Parameter


class TestSearchEngine:
    """Test SearchEngine functionality"""
    
    @pytest.fixture
    def sample_config(self):
        """Create a sample configuration for testing"""
        root = Container(short_name="Root", description="Root configuration")
        
        # CAN module
        can = Container(short_name="Can", description="CAN Driver configuration")
        root.add_sub_container(can)
        
        can.add_parameter(Parameter(
            short_name="Baudrate",
            value=500,
            value_type="INTEGER",
            description="CAN bus baudrate"
        ))
        
        can.add_parameter(Parameter(
            short_name="Mode",
            value="NORMAL",
            value_type="STRING",
            description="CAN operating mode"
        ))
        
        # LIN module
        lin = Container(short_name="Lin", description="LIN Driver configuration")
        root.add_sub_container(lin)
        
        lin.add_parameter(Parameter(
            short_name="Baudrate",
            value=19200,
            value_type="INTEGER",
            description="LIN bus baudrate"
        ))
        
        # Nested container
        advanced = Container(short_name="Advanced", description="Advanced settings")
        can.add_sub_container(advanced)
        
        advanced.add_parameter(Parameter(
            short_name="Timeout",
            value=1000,
            value_type="INTEGER",
            description="Communication timeout in ms"
        ))
        
        return root
    
    def test_search_by_name(self, sample_config):
        """Test searching by name"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Baudrate", SearchMode.NAME)
        
        assert len(results) == 2
        assert all(r.element.short_name == "Baudrate" for r in results)
        assert all(r.match_field == "name" for r in results)
    
    def test_search_by_description(self, sample_config):
        """Test searching by description"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Driver", SearchMode.DESCRIPTION)
        
        assert len(results) == 2
        assert all("Driver" in r.element.description for r in results)
        assert all(r.match_field == "description" for r in results)
    
    def test_search_by_value(self, sample_config):
        """Test searching by value"""
        engine = SearchEngine()
        results = engine.search(sample_config, "500", SearchMode.VALUE)
        
        assert len(results) == 1
        assert results[0].element.short_name == "Baudrate"
        assert results[0].element.value == 500
        assert results[0].match_field == "value"
    
    def test_search_all_fields(self, sample_config):
        """Test searching all fields"""
        engine = SearchEngine()
        results = engine.search(sample_config, "CAN", SearchMode.ALL)
        
        # Should find: Can container (name), Can container (description), 
        # Baudrate (description), Mode (description)
        assert len(results) >= 2
    
    def test_case_sensitive_search(self, sample_config):
        """Test case-sensitive search"""
        engine = SearchEngine()
        
        # Case insensitive (default)
        results_insensitive = engine.search(sample_config, "can", SearchMode.NAME, case_sensitive=False)
        assert len(results_insensitive) == 1
        
        # Case sensitive
        results_sensitive = engine.search(sample_config, "can", SearchMode.NAME, case_sensitive=True)
        assert len(results_sensitive) == 0
        
        results_sensitive = engine.search(sample_config, "Can", SearchMode.NAME, case_sensitive=True)
        assert len(results_sensitive) == 1
    
    def test_regex_search(self, sample_config):
        """Test regex search"""
        engine = SearchEngine()
        
        # Search for parameters ending with "rate"
        results = engine.search(sample_config, r".*rate$", SearchMode.NAME, use_regex=True)
        assert len(results) == 2
        assert all(r.element.short_name == "Baudrate" for r in results)
        
        # Search for numeric values
        results = engine.search(sample_config, r"^\d+$", SearchMode.VALUE, use_regex=True)
        assert len(results) == 3  # Three numeric parameters
    
    def test_nested_container_search(self, sample_config):
        """Test searching in nested containers"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Timeout", SearchMode.NAME)
        
        assert len(results) == 1
        assert results[0].element.short_name == "Timeout"
        assert "Advanced" in results[0].path
    
    def test_empty_query(self, sample_config):
        """Test search with empty query"""
        engine = SearchEngine()
        results = engine.search(sample_config, "", SearchMode.ALL)
        
        assert len(results) == 0
    
    def test_no_results(self, sample_config):
        """Test search with no matches"""
        engine = SearchEngine()
        results = engine.search(sample_config, "NonExistent", SearchMode.ALL)
        
        assert len(results) == 0
    
    def test_search_result_path(self, sample_config):
        """Test that search results have correct paths"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Timeout", SearchMode.NAME)
        
        assert len(results) == 1
        assert results[0].path == "Root/Can/Advanced/Timeout"
    
    def test_search_result_display_name(self, sample_config):
        """Test search result display name"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Baudrate", SearchMode.NAME)
        
        assert len(results) == 2
        for result in results:
            assert "Baudrate" in result.display_name
            if result.element.value == 500:
                assert "500" in result.display_name
    
    def test_filter_results_by_type(self, sample_config):
        """Test filtering results by element type"""
        engine = SearchEngine()
        results = engine.search(sample_config, "CAN", SearchMode.ALL)
        
        containers = engine.filter_results_by_type(results, "Container")
        parameters = engine.filter_results_by_type(results, "Parameter")
        
        assert all(r.element_type == "Container" for r in containers)
        assert all(r.element_type == "Parameter" for r in parameters)
    
    def test_get_unique_paths(self, sample_config):
        """Test getting unique paths from results"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Baudrate", SearchMode.NAME)
        
        paths = engine.get_unique_paths(results)
        assert len(paths) == 2
        assert "Root/Can/Baudrate" in paths
        assert "Root/Lin/Baudrate" in paths
    
    def test_invalid_regex(self, sample_config):
        """Test search with invalid regex falls back to literal"""
        engine = SearchEngine()
        
        # Invalid regex pattern
        results = engine.search(sample_config, "[invalid(", SearchMode.NAME, use_regex=True)
        
        # Should fall back to literal search and find nothing
        assert len(results) == 0
    
    def test_search_container_only(self, sample_config):
        """Test searching containers only"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Advanced", SearchMode.NAME)
        
        assert len(results) == 1
        assert isinstance(results[0].element, Container)
        assert results[0].element.short_name == "Advanced"
    
    def test_search_parameter_only(self, sample_config):
        """Test searching parameters only"""
        engine = SearchEngine()
        results = engine.search(sample_config, "Mode", SearchMode.NAME)
        
        assert len(results) == 1
        assert isinstance(results[0].element, Parameter)
        assert results[0].element.short_name == "Mode"

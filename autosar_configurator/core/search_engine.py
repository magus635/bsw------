"""
Search engine for AUTOSAR configuration elements
"""
import re
from dataclasses import dataclass
from enum import Enum
from typing import List, Optional, Union
from .model.container import Container, Parameter


class SearchMode(Enum):
    """Search mode enumeration"""
    NAME = "name"           # Search by short name
    DESCRIPTION = "description"  # Search by description
    VALUE = "value"         # Search by parameter value
    ALL = "all"            # Search all fields


@dataclass
class SearchResult:
    """Search result containing matched element and its path"""
    element: Union[Container, Parameter]
    path: str
    match_field: str  # Which field matched: 'name', 'description', or 'value'
    match_text: str   # The actual text that matched
    
    @property
    def element_type(self) -> str:
        """Get the type of element"""
        return "Container" if isinstance(self.element, Container) else "Parameter"
    
    @property
    def display_name(self) -> str:
        """Get display name for the result"""
        if isinstance(self.element, Parameter):
            value_str = f" = {self.element.value}" if self.element.value is not None else ""
            return f"{self.element.short_name}{value_str}"
        return self.element.short_name


class SearchEngine:
    """Search engine for finding configuration elements"""
    
    def __init__(self):
        self.case_sensitive = False
        self.use_regex = False
    
    def search(
        self,
        root: Container,
        query: str,
        mode: SearchMode = SearchMode.ALL,
        case_sensitive: bool = False,
        use_regex: bool = False
    ) -> List[SearchResult]:
        """
        Search for elements matching the query
        
        Args:
            root: Root container to search from
            query: Search query string
            mode: Search mode (NAME, DESCRIPTION, VALUE, ALL)
            case_sensitive: Whether to perform case-sensitive search
            use_regex: Whether to treat query as regular expression
            
        Returns:
            List of search results
        """
        if not query:
            return []
        
        self.case_sensitive = case_sensitive
        self.use_regex = use_regex
        
        results = []
        self._search_container(root, query, mode, "", results)
        return results
    
    def _search_container(
        self,
        container: Container,
        query: str,
        mode: SearchMode,
        parent_path: str,
        results: List[SearchResult]
    ):
        """Recursively search a container and its children"""
        current_path = f"{parent_path}/{container.short_name}" if parent_path else container.short_name
        
        # Check if container itself matches
        if mode in [SearchMode.NAME, SearchMode.ALL]:
            if self._matches(container.short_name, query):
                results.append(SearchResult(
                    element=container,
                    path=current_path,
                    match_field="name",
                    match_text=container.short_name
                ))
        
        if mode in [SearchMode.DESCRIPTION, SearchMode.ALL]:
            if container.description and self._matches(container.description, query):
                results.append(SearchResult(
                    element=container,
                    path=current_path,
                    match_field="description",
                    match_text=container.description
                ))
        
        # Search parameters
        for param in container.parameters.values():
            self._search_parameter(param, query, mode, current_path, results)
        
        # Search sub-containers recursively
        for sub_container in container.sub_containers.values():
            self._search_container(sub_container, query, mode, current_path, results)
    
    def _search_parameter(
        self,
        parameter: Parameter,
        query: str,
        mode: SearchMode,
        parent_path: str,
        results: List[SearchResult]
    ):
        """Search a parameter"""
        param_path = f"{parent_path}/{parameter.short_name}"
        
        # Check name
        if mode in [SearchMode.NAME, SearchMode.ALL]:
            if self._matches(parameter.short_name, query):
                results.append(SearchResult(
                    element=parameter,
                    path=param_path,
                    match_field="name",
                    match_text=parameter.short_name
                ))
                return  # Found match, no need to check other fields
        
        # Check description
        if mode in [SearchMode.DESCRIPTION, SearchMode.ALL]:
            if parameter.description and self._matches(parameter.description, query):
                results.append(SearchResult(
                    element=parameter,
                    path=param_path,
                    match_field="description",
                    match_text=parameter.description
                ))
                return
        
        # Check value
        if mode in [SearchMode.VALUE, SearchMode.ALL]:
            if parameter.value is not None:
                value_str = str(parameter.value)
                if self._matches(value_str, query):
                    results.append(SearchResult(
                        element=parameter,
                        path=param_path,
                        match_field="value",
                        match_text=value_str
                    ))
    
    def _matches(self, text: str, query: str) -> bool:
        """Check if text matches query"""
        if self.use_regex:
            try:
                flags = 0 if self.case_sensitive else re.IGNORECASE
                return re.search(query, text, flags) is not None
            except re.error:
                # Invalid regex, fall back to literal search
                return self._literal_match(text, query)
        else:
            return self._literal_match(text, query)
    
    def _literal_match(self, text: str, query: str) -> bool:
        """Perform literal string matching"""
        if self.case_sensitive:
            return query in text
        else:
            return query.lower() in text.lower()
    
    def filter_results_by_type(
        self,
        results: List[SearchResult],
        element_type: str
    ) -> List[SearchResult]:
        """Filter results by element type"""
        return [r for r in results if r.element_type == element_type]
    
    def get_unique_paths(self, results: List[SearchResult]) -> List[str]:
        """Get unique paths from results"""
        return list(set(r.path for r in results))

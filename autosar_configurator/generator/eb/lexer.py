"""
Lexer for EB Tresos Template Syntax

Tokenizes [! ... !] blocks from template files, separating:
- Directives: IF, ELSEIF, ELSE, ENDIF, LOOP, ENDLOOP, SELECT, ENDSELECT, VAR, INCLUDE
- Output expressions: [!"..."!]
- Comments: [!// ... !]
- Plain text
"""
import re
from typing import List, Tuple, Optional
from dataclasses import dataclass
from enum import Enum, auto


class TokenType(Enum):
    """Token types for EB template syntax"""
    TEXT = auto()           # Plain text outside [! !]
    IF = auto()             # [!IF condition!]
    ELSEIF = auto()         # [!ELSEIF condition!]
    ELSE = auto()           # [!ELSE!]
    ENDIF = auto()          # [!ENDIF!]
    LOOP = auto()           # [!LOOP xpath!]
    ENDLOOP = auto()        # [!ENDLOOP!]
    SELECT = auto()         # [!SELECT xpath!]
    ENDSELECT = auto()      # [!ENDSELECT!]
    VAR = auto()            # [!VAR "name"="value"!]
    INCLUDE = auto()        # [!INCLUDE "file"!]
    COMMENT = auto()        # [!// comment !]
    OUTPUT = auto()         # [!"expression"!]
    CALL = auto()           # [!CALL macro(args)!]
    MACRO = auto()          # [!MACRO name(params)!]
    ENDMACRO = auto()       # [!ENDMACRO!]
    FOR = auto()            # [!FOR "var" = "start" TO "end"!]
    ENDFOR = auto()         # [!ENDFOR!]
    BREAK = auto()          # [!BREAK!]
    CODE = auto()           # [!CODE!] - output block within NOCODE
    ENDCODE = auto()        # [!ENDCODE!]
    NOCODE = auto()         # [!NOCODE!] - suppress output
    ENDNOCODE = auto()      # [!ENDNOCODE!]
    ERROR = auto()          # [!ERROR!] - raise compile error
    ENDERROR = auto()       # [!ENDERROR!]
    ASSERT = auto()         # [!ASSERT condition!]
    ENDASSERT = auto()      # [!ENDASSERT!]


@dataclass
class Token:
    """Represents a single token from the template"""
    type: TokenType
    content: str           # Raw content (for TEXT) or directive argument
    line: int = 0          # Line number in source
    column: int = 0        # Column number in source
    raw: str = ""          # Original raw text including delimiters
    directive_only_line: bool = False  # True if this token is on a line with only directives
    
    def __repr__(self):
        if self.type == TokenType.TEXT:
            preview = self.content[:20] + "..." if len(self.content) > 20 else self.content
            return f"Token(TEXT, {repr(preview)})"
        return f"Token({self.type.name}, {repr(self.content)})"


class Lexer:
    """Tokenizer for EB Tresos template files"""
    
    # Pattern for line comments [!// ... (to end of line, no !] needed)
    LINE_COMMENT_PATTERN = re.compile(r'\[!//[^\n]*')
    
    # Pattern to find [! ... !] blocks (standard tags)
    TAG_PATTERN = re.compile(r'\[!(.*?)!\]', re.DOTALL)
    
    # Directive keywords (must be at start of tag content)
    KEYWORDS = {
        'IF': TokenType.IF,
        'ELSEIF': TokenType.ELSEIF,
        'ELSE': TokenType.ELSE,
        'ENDIF': TokenType.ENDIF,
        'LOOP': TokenType.LOOP,
        'ENDLOOP': TokenType.ENDLOOP,
        'SELECT': TokenType.SELECT,
        'ENDSELECT': TokenType.ENDSELECT,
        'VAR': TokenType.VAR,
        'INCLUDE': TokenType.INCLUDE,
        'CALL': TokenType.CALL,
        'MACRO': TokenType.MACRO,
        'ENDMACRO': TokenType.ENDMACRO,
        'FOR': TokenType.FOR,
        'ENDFOR': TokenType.ENDFOR,
        'BREAK': TokenType.BREAK,
        'CODE': TokenType.CODE,
        'ENDCODE': TokenType.ENDCODE,
        'NOCODE': TokenType.NOCODE,
        'ENDNOCODE': TokenType.ENDNOCODE,
        'ERROR': TokenType.ERROR,
        'ENDERROR': TokenType.ENDERROR,
        'ASSERT': TokenType.ASSERT,
        'ENDASSERT': TokenType.ENDASSERT,
    }
    
    def __init__(self):
        self._line = 1
        self._column = 1
    
    def tokenize(self, template: str) -> List[Token]:
        """Tokenize a template string into a list of tokens.
        
        Args:
            template: Template source string
            
        Returns:
            List of Token objects
        """
        tokens = []
        self._line = 1
        self._column = 1
        
        # First, strip line comments [!// ... (to end of line)
        # Replace them with empty strings to preserve line positions
        # but mark their positions for potential tracking
        processed = self.LINE_COMMENT_PATTERN.sub('', template)
        
        last_pos = 0
        
        for match in self.TAG_PATTERN.finditer(processed):
            # Add TEXT token for content before this tag
            if match.start() > last_pos:
                text_content = processed[last_pos:match.start()]
                if text_content:
                    tokens.append(self._make_text_token(text_content))
                    self._update_position(text_content)
            
            # Parse the tag content
            tag_content = match.group(1)
            raw_tag = match.group(0)
            token = self._parse_tag(tag_content, raw_tag)
            tokens.append(token)
            
            self._update_position(raw_tag)
            last_pos = match.end()
        
        # Add remaining text
        if last_pos < len(processed):
            text_content = processed[last_pos:]
            if text_content:
                tokens.append(self._make_text_token(text_content))
        
        # Post-process for Smart Trimming
        tokens = self._apply_smart_trimming(tokens)
        
        return tokens
    
    def _apply_smart_trimming(self, tokens: List[Token]) -> List[Token]:
        """Apply Smart Trimming: modify TEXT tokens to suppress newlines after directive-only lines.
        
        Strategy: Walk through tokens. When we see a TEXT token that ends with newline,
        check if the preceding tokens on this line were all directives (no OUTPUT).
        If so, strip the trailing newline.
        """
        if not tokens:
            return tokens
        
        result = []
        for i, tok in enumerate(tokens):
            if tok.type == TokenType.TEXT:
                # Check if this text is just whitespace + newline after a directive
                content = tok.content
                
                # If text is only whitespace ending with newline, and previous token was a directive
                if i > 0 and content.strip() == '' and '\n' in content:
                    prev = tokens[i - 1]
                    if prev.type not in (TokenType.TEXT, TokenType.OUTPUT):
                        # Previous was a directive - strip this newline
                        content = content.replace('\n', '').replace('\r', '')
                
                # If text starts with newline and previous was directive on its own
                if i > 0 and content.startswith('\n'):
                    prev = tokens[i - 1]
                    if prev.type not in (TokenType.TEXT, TokenType.OUTPUT):
                        # Check if the newline is at the start (directive was on previous line alone)
                        content = content[1:]  # Strip leading newline
                        if content.startswith('\r'):
                            content = content[1:]
                
                result.append(Token(
                    type=tok.type,
                    content=content,
                    line=tok.line,
                    column=tok.column,
                    raw=tok.raw,
                    directive_only_line=tok.directive_only_line
                ))
            else:
                result.append(tok)
        
        return result
    
    def _make_text_token(self, content: str) -> Token:
        """Create a TEXT token"""
        return Token(
            type=TokenType.TEXT,
            content=content,
            line=self._line,
            column=self._column,
            raw=content
        )
    
    def _parse_tag(self, content: str, raw: str) -> Token:
        """Parse a [! ... !] tag into appropriate token type.
        
        Args:
            content: Content inside [! and !]
            raw: Full raw tag including delimiters
            
        Returns:
            Token object
        """
        content = content.strip()
        line, col = self._line, self._column
        
        # Check for comment
        if content.startswith('//'):
            return Token(
                type=TokenType.COMMENT,
                content=content[2:].strip(),
                line=line, column=col, raw=raw
            )
        
        # Check for output expression [!"..."!] or [!expr!]
        if content.startswith('"') or content.startswith("'"):
            # Quoted expression output
            return Token(
                type=TokenType.OUTPUT,
                content=content,
                line=line, column=col, raw=raw
            )
        
        # Check for directive keywords
        first_word = content.split(None, 1)[0].upper() if content else ""
        
        if first_word in self.KEYWORDS:
            token_type = self.KEYWORDS[first_word]
            # Extract argument (everything after the keyword)
            parts = content.split(None, 1)
            argument = parts[1].strip() if len(parts) > 1 else ""
            
            return Token(
                type=token_type,
                content=argument,
                line=line, column=col, raw=raw
            )
        
        # Default: treat as output expression
        return Token(
            type=TokenType.OUTPUT,
            content=content,
            line=line, column=col, raw=raw
        )
    
    def _update_position(self, text: str):
        """Update line and column counters based on consumed text"""
        for char in text:
            if char == '\n':
                self._line += 1
                self._column = 1
            else:
                self._column += 1


def tokenize(template: str) -> List[Token]:
    """Convenience function to tokenize a template string.
    
    Args:
        template: Template source string
        
    Returns:
        List of Token objects
    """
    return Lexer().tokenize(template)

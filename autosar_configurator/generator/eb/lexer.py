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
    INDENT = auto()         # [!INDENT "n"!] - set indentation
    ENDINDENT = auto()      # [!ENDINDENT!] - end indentation
    WS = auto()             # [!WS "n"!] - output whitespace
    AUTOSPACING = auto()    # [!AUTOSPACING!] - auto spacing
    CR = auto()             # [!CR!] - output carriage return/newline
    TRACE = auto()          # [!TRACE expression!] - debug print
    AUTOGENERATE_WARNING = auto()  # [!AUTOGENERATE_WARNING!] - auto-generate warning comment



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
    
    # Pattern for line continuation [!//!] - removes the marker and following newline
    LINE_CONTINUATION_PATTERN = re.compile(r'\[!//!?\]\s*\n?')

    # Pattern for line comments [!// ... (to end of line, no !] needed)
    # This must not match [!//!] which is line continuation
    # IMPORTANT: Also removes the trailing newline to achieve line continuation effect
    LINE_COMMENT_PATTERN = re.compile(r'\[!//(?!!])(?!\])[^\n]*\n?')
    
    # Pattern to find [! ... !] blocks (standard tags)
    TAG_PATTERN = re.compile(r'\[!(.*?)!]', re.DOTALL)
    
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
        'INDENT': TokenType.INDENT,
        'ENDINDENT': TokenType.ENDINDENT,
        'WS': TokenType.WS,
        'AUTOSPACING': TokenType.AUTOSPACING,
        'CR': TokenType.CR,
        'TRACE': TokenType.TRACE,
        'AUTOGENERATE_WARNING': TokenType.AUTOGENERATE_WARNING,
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
        
        # First, handle line continuations [!//!] - removes marker AND following newline
        processed = self.LINE_CONTINUATION_PATTERN.sub('', template)
        
        # Then, strip line comments [!// ... (to end of line)
        processed = self.LINE_COMMENT_PATTERN.sub('', processed)
        
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
        
        IMPORTANT: Only strip newlines for lines that ONLY contain directives.
        Lines like "#define X [!IF!]A[!ELSE!]B[!ENDIF!]" should preserve trailing newlines.
        """
        if not tokens:
            return tokens
        
        # First pass: mark lines that have TEXT or OUTPUT content (not directive-only)
        # Track which "line groups" have actual content output
        line_has_content = False
        content_line_ends = set()  # Indices of tokens that end a line with content
        
        for i, tok in enumerate(tokens):
            if tok.type == TokenType.TEXT:
                content = tok.content
                # Check if this TEXT has actual content (not just whitespace)
                if content.strip() or (content and '\n' not in content):
                    line_has_content = True
                # If this TEXT ends with newline, mark if line had content
                if '\n' in content:
                    if line_has_content:
                        content_line_ends.add(i)
                    line_has_content = False  # Reset for next line
            elif tok.type == TokenType.OUTPUT:
                line_has_content = True
        
        # Second pass: apply smart trimming only to directive-only lines
        result = []
        for i, tok in enumerate(tokens):
            if tok.type == TokenType.TEXT:
                content = tok.content
                
                # If text is only whitespace ending with newline, and previous token was a directive,
                # AND the previous line was directive-only (not in content_line_ends)
                if i > 0 and content.strip() == '' and '\n' in content:
                    prev = tokens[i - 1]
                    if prev.type not in (TokenType.TEXT, TokenType.OUTPUT):
                        # Check if any preceding token on this logical line had content
                        # If previous index is NOT in content_line_ends, strip
                        prev_had_content = False
                        for j in range(i - 1, -1, -1):
                            if j in content_line_ends:
                                prev_had_content = True
                                break
                            if tokens[j].type == TokenType.TEXT and '\n' in tokens[j].content:
                                break  # Found previous line end without content
                        if not prev_had_content:
                            content = content.replace('\n', '').replace('\r', '')
                
                # If text starts with newline and previous was directive on its own line
                # (not an inline directive on a content line)
                if i > 0 and content.startswith('\n'):
                    prev = tokens[i - 1]
                    if prev.type not in (TokenType.TEXT, TokenType.OUTPUT):
                        # Check backward to see if any TEXT with content existed before this directive on the same line
                        is_inline_directive = False
                        for j in range(i - 1, -1, -1):
                            t = tokens[j]
                            if t.type == TokenType.TEXT:
                                if '\n' in t.content:
                                    break  # Previous line boundary, not inline
                                if t.content.strip():
                                    is_inline_directive = True  # There was content before directive
                                    break
                            elif t.type == TokenType.OUTPUT:
                                is_inline_directive = True
                                break
                        
                        if not is_inline_directive:
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
        if content.startswith('//') or (content.startswith('/*') and content.endswith('*/')):
            return Token(
                type=TokenType.COMMENT,
                content=content[2:].strip() if content.startswith('//') else content[2:-2].strip(),
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
        # Handle both "WS 0" and "WS"0"" formats (keyword may be followed by space or quote)
        first_word = ""
        if content:
            # Extract keyword part - stop at whitespace, quote, or end of string
            match = re.match(r'(\w+)', content)
            if match:
                first_word = match.group(1).upper()

        if first_word in self.KEYWORDS:
            token_type = self.KEYWORDS[first_word]
            # Extract argument (everything after the keyword)
            # Handle both "WS 0" and "WS"0"" formats (keyword may or may not be followed by space)
            keyword_len = len(first_word)
            argument = content[keyword_len:].strip()

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

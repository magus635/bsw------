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
    # Also consumes leading whitespace (indentation) of the following line
    LINE_CONTINUATION_PATTERN = re.compile(r'\[!//!?\]\s*\n?[\t ]*')

    # Pattern for line comments [!// ... (to end of line, no !] needed)
    # This must not match [!//!] which is line continuation
    # IMPORTANT: Also removes the trailing newline and subsequent leading whitespace
    # to achieve proper line continuation effect
    LINE_COMMENT_PATTERN = re.compile(r'\[!//(?!.*!\])[^\n]*\n?[\t ]*')

    # Pattern for block comments [!/* ... */!] that contain nested [! tags
    # These confuse TAG_PATTERN's non-greedy !] matching; must be stripped first.
    # Simple block comments (no nested [!) are handled correctly by TAG_PATTERN.
    BLOCK_COMMENT_PATTERN = re.compile(r'\[!/\*(?:(?!\*/!\]).)*\[!(?:(?!\*/!\]).)*\*/!\]', re.DOTALL)

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

        # Strip block comments [!/* ... */!] before TAG_PATTERN matching
        processed = self.BLOCK_COMMENT_PATTERN.sub('', processed)
        
        last_pos = 0
        
        for match in self.TAG_PATTERN.finditer(processed):
            # Add TEXT token for content before this tag
            if match.start() > last_pos:
                text_content = processed[last_pos:match.start()]
                if text_content:
                    tokens.extend(self._make_text_tokens(text_content))
            
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
                tokens.extend(self._make_text_tokens(text_content))

        # Post-process for directive-only lines and smart trimming
        tokens = self._identify_directive_lines(tokens)

        return tokens

    def _identify_directive_lines(self, tokens: List[Token]) -> List[Token]:
        """Identify lines that contain only directives and whitespace.
        Set directive_only_line=True for such tokens.
        """
        if not tokens:
            return tokens
            
        # Group tokens by line
        lines = {}
        for tok in tokens:
            if tok.line not in lines:
                lines[tok.line] = []
            lines[tok.line].append(tok)
            
        # For each line, check if it contains any "outputting" content
        directive_only_line_numbers = set()
        for line_num, line_tokens in lines.items():
            has_output = False
            for tok in line_tokens:
                if tok.type == TokenType.OUTPUT:
                    has_output = True
                    break
                if tok.type == TokenType.TEXT:
                    # Non-whitespace text (excluding newlines) makes it NOT directive-only
                    content_no_ws = tok.content.replace('\n', '').replace('\r', '').strip()
                    if content_no_ws:
                        has_output = True
                        break
            
            if not has_output:
                # Only mark as directive-only if the line actually contains
                # at least one directive token. Pure whitespace/newline-only
                # lines (no directives) represent intentional blank lines in
                # the template output and must be preserved.
                has_directive = any(tok.type != TokenType.TEXT for tok in line_tokens)
                if has_directive:
                    directive_only_line_numbers.add(line_num)
        
        # Mark tokens on those lines
        for tok in tokens:
            if tok.line in directive_only_line_numbers:
                tok.directive_only_line = True
                
        return tokens
    
    
    def _make_text_tokens(self, content: str) -> List[Token]:
        """Create TEXT tokens, splitting by line so that tokens don't cross line boundaries"""
        tokens = []
        if not content:
            return tokens
            
        parts = re.split(r'(\n)', content)
        for part in parts:
            if not part:
                continue
            tokens.append(Token(
                type=TokenType.TEXT,
                content=part,
                line=self._line,
                column=self._column,
                raw=part
            ))
            self._update_position(part)
        return tokens
    
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

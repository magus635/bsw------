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
    # TEXT that starts a template line whose newline a [!// line comment consumed: inside
    # [!INDENT!] its leading whitespace is template layout (EB drops it), outside it is output
    after_line_comment: bool = False
    # TEXT right after a "[!// text" comment (the line break stays and is output)
    after_comment: bool = False

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

    # Pattern for line comments [!// ... (to end of line, no !] terminator)
    # Must not match [!//!] (line continuation) or [!// comment !] (inline comment with !] terminator).
    # Inline comments that end with !] are left for TAG_PATTERN so _parse_tag() returns a COMMENT token,
    # allowing text after !] on the same line to be preserved (e.g. Before[!// c !]After -> BeforeAfter).
    # As in EB, only a bare "[!//" at the end of a line also removes the line break (group 1);
    # "[!// text" - even "[!//" followed by spaces - is a comment and the line break stays.
    # After a removed line break, the indentation of the next line is consumed only when that line
    # starts with a control directive ([!IF, [!VAR, [!// ...): it is template layout. Before text or
    # an output tag ([!"..."!]) it is kept - EB writes "    }," after "[!ENDINDENT!][!//".
    LINE_COMMENT_PATTERN = re.compile(
        r'\[!//(?!!])(?!\])(?![^\n]*!])(?:(\r?\n)(?:[\t ]*(?=\[!(?!["\'])))?|[^\n]*)')

    # Put in place of a line comment that consumed its newline: marks where the next template line
    # starts (see Token.after_line_comment). Never part of a token's content.
    LINE_START_MARK = '\x00'
    # Put in place of a "[!// text" comment, whose line break stays (see Token.after_comment)
    COMMENT_MARK = '\x01'

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
        
        # Then, strip line comments [!// ... (to end of line), marking where the next line starts
        processed = self.LINE_COMMENT_PATTERN.sub(
            lambda m: self.LINE_START_MARK if m.group(1) else self.COMMENT_MARK, processed)

        # Strip block comments [!/* ... */!] before TAG_PATTERN matching
        processed = self.BLOCK_COMMENT_PATTERN.sub('', processed)
        
        last_pos = 0
        
        for match in self.TAG_PATTERN.finditer(processed):
            # Add TEXT token for content before this tag
            if match.start() > last_pos:
                self._add_text_tokens(tokens, processed[last_pos:match.start()])

            # Parse the tag content
            tag_content = self._unmark(match.group(1))
            raw_tag = self._unmark(match.group(0))
            token = self._parse_tag(tag_content, raw_tag)
            tokens.append(token)
            
            self._update_position(raw_tag)
            last_pos = match.end()
        
        # Add remaining text
        if last_pos < len(processed):
            self._add_text_tokens(tokens, processed[last_pos:])

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
    
    
    def _unmark(self, text: str) -> str:
        return text.replace(self.LINE_START_MARK, '').replace(self.COMMENT_MARK, '')

    def _add_text_tokens(self, tokens: List[Token], text: str):
        """TEXT token(s) for text between tags, split where a line comment was removed;
        the token after a mark carries it (after_line_comment / after_comment)."""
        mark = None
        for part in re.split('([\x00\x01])', text):
            if part == self.LINE_START_MARK:
                mark = 'after_line_comment'
            elif part == self.COMMENT_MARK:
                mark = 'after_comment'
            elif part:
                token = self._make_text_token(part)
                if mark:
                    setattr(token, mark, True)
                tokens.append(token)
                self._update_position(part)
                mark = None

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

"""Lossless, ordered text-script views for the observed 60US PVF branch.

This is deliberately not a modern binary-token PVF reader.  Byte offsets always
refer to the decrypted file before CP949 decoding.  Explicit closing tags define
nesting; implicit CHR states and ANI frame boundaries are not invented as XML.
The original bytes and all tokens, including comments, remain accessible.
"""
from __future__ import annotations

from bisect import bisect_right
from dataclasses import dataclass, field
import hashlib
import re
from typing import Any, Iterator


def _value(text: str) -> str | int | float:
    if re.fullmatch(r"[+-]?\d+", text):
        return int(text)
    if re.fullmatch(r"[+-]?(?:\d+\.\d*|\.\d+)(?:[eE][+-]?\d+)?|[+-]?\d+[eE][+-]?\d+", text):
        return float(text)
    return text


@dataclass(frozen=True)
class Token:
    kind: str
    text: str
    start: int
    end: int
    line: int
    column: int

    @property
    def value(self) -> str | int | float:
        return _value(self.text) if self.kind == "atom" else self.text

    def to_dict(self) -> dict[str, Any]:
        return dict(kind=self.kind, text=self.text, value=self.value,
                    start=self.start, end=self.end, line=self.line, column=self.column)


@dataclass
class Node:
    name: str
    tag: Token
    values: list[Token] = field(default_factory=list)
    children: list[Node] = field(default_factory=list)
    closing: Token | None = None
    end: int = 0
    is_block: bool = False
    scope: tuple[str, ...] = ()

    @property
    def start(self) -> int:
        return self.tag.start

    @property
    def data(self) -> list[str | int | float]:
        return [t.value for t in self.values]

    def to_dict(self) -> dict[str, Any]:
        return dict(name=self.name, start=self.start, end=self.end,
                    tag=self.tag.to_dict(), values=[t.to_dict() for t in self.values],
                    children=[n.to_dict() for n in self.children],
                    closing=self.closing.to_dict() if self.closing else None,
                    is_block=self.is_block, scope=list(self.scope))


@dataclass
class Document:
    raw: bytes
    text: str
    path: str | None
    tokens: list[Token]
    nodes: list[Node]
    events: list[Node]
    preamble: list[Token]
    warnings: list[dict[str, Any]]
    encoding: str = "cp949"

    @property
    def sha256(self) -> str:
        return hashlib.sha256(self.raw).hexdigest()

    def find(self, name: str, *, scope: tuple[str, ...] | None = None) -> list[Node]:
        """Return every occurrence in file order; never silently pick the last."""
        wanted = name.strip("[]").casefold()
        return [n for n in self.events if n.name.casefold() == wanted
                and (scope is None or n.scope == scope)]

    def to_dict(self, *, include_raw: bool = False) -> dict[str, Any]:
        result = dict(path=self.path, sha256=self.sha256, size=len(self.raw),
                      encoding=self.encoding, nodes=[n.to_dict() for n in self.nodes],
                      tokens=[t.to_dict() for t in self.tokens],
                      preamble=[t.to_dict() for t in self.preamble], warnings=self.warnings)
        if include_raw:
            result["raw_hex"] = self.raw.hex()
        return result


def _lex(raw: bytes) -> tuple[list[Token], list[dict[str, Any]]]:
    starts = [0] + [m.end() for m in re.finditer(b"\n", raw)]
    tokens: list[Token] = []
    warnings: list[dict[str, Any]] = []

    def append(kind: str, start: int, end: int, content_start: int | None = None,
               content_end: int | None = None) -> None:
        line = bisect_right(starts, start)
        text = raw[start if content_start is None else content_start:
                   end if content_end is None else content_end].decode("cp949", "strict")
        tokens.append(Token(kind, text, start, end, line, start-starts[line-1]+1))

    i = 0
    size = len(raw)
    while i < size:
        c = raw[i]
        if c in b" \t\r\n\v\f":
            i += 1
            continue
        start = i
        if raw.startswith(b"//", i):
            end = raw.find(b"\n", i+2)
            i = size if end < 0 else end
            append("comment", start, i)
        elif raw.startswith(b"/*", i):
            end = raw.find(b"*/", i+2)
            i = size if end < 0 else end+2
            append("comment", start, i)
            if end < 0:
                warnings.append(dict(kind="unterminated_comment", offset=start))
        elif c in (96, 34):  # backticks are the observed string delimiter
            quote = c
            i += 1
            content_start = i
            while i < size and raw[i] != quote:
                # Do not interpret C escapes: backslashes are common PVF paths.
                i += 1
            closed = i < size
            content_end = i
            i += int(closed)
            append("string", start, i, content_start, content_end)
            if not closed:
                warnings.append(dict(kind="unterminated_string", offset=start))
        elif c == 91:  # tag, only outside strings/comments
            end = raw.find(b"]", i+1)
            newline = raw.find(b"\n", i+1)
            if end >= 0 and (newline < 0 or end < newline):
                i = end+1
                close = raw.startswith(b"[/", start)
                append("close_tag" if close else "tag", start, i,
                       start+2 if close else start+1, end)
            else:
                i += 1
                append("atom", start, i)
                warnings.append(dict(kind="unterminated_tag", offset=start))
        else:
            i += 1
            while i < size and raw[i] not in b" \t\r\n\v\f[`\"":
                if raw.startswith(b"//", i) or raw.startswith(b"/*", i):
                    break
                i += 1
            append("atom", start, i)
    return tokens, warnings


def parse_document(raw: bytes, path: str | None = None) -> Document:
    """Parse without dropping repeated tags, comments, source bytes or errors.

    A closing-tag vocabulary is learned only from the current document. Tags
    without closing tags remain ordered properties. Malformed nesting is
    reported and preserved as lexical events rather than repaired silently.
    """
    if not isinstance(raw, bytes):
        raise TypeError("raw must be bytes, so offsets refer to the source")
    text = raw.decode("cp949", "strict")
    tokens, warnings = _lex(raw)
    block_names = {t.text.strip().casefold() for t in tokens if t.kind == "close_tag"}
    roots: list[Node] = []
    events: list[Node] = []
    preamble: list[Token] = []
    stack: list[Node] = []
    current: Node | None = None
    for token in tokens:
        if token.kind == "comment":
            continue
        if token.kind == "tag":
            if current is not None and not current.is_block:
                current.end = token.start
            name = token.text.strip()
            node = Node(name=name, tag=token, end=token.end,
                        is_block=name.casefold() in block_names,
                        scope=tuple(n.name for n in stack))
            (stack[-1].children if stack else roots).append(node)
            events.append(node)
            current = node
            if node.is_block:
                stack.append(node)
        elif token.kind == "close_tag":
            if current is not None and not current.is_block:
                current.end = token.start
            matches = [j for j, n in enumerate(stack) if n.name.casefold() == token.text.strip().casefold()]
            if not matches:
                warnings.append(dict(kind="unmatched_closing_tag", name=token.text, offset=token.start))
                current = None
                continue
            index = matches[-1]
            for missing in stack[index+1:]:
                missing.end = token.start
                warnings.append(dict(kind="unclosed_nested_block", name=missing.name,
                                     offset=missing.start, stopped_at=token.start))
            node = stack[index]
            node.closing = token
            node.end = token.end
            del stack[index:]
            current = None
        elif current is None:
            # Values after a nested closing tag belong to its explicit parent.
            if stack:
                stack[-1].values.append(token)
            else:
                preamble.append(token)
        else:
            current.values.append(token)
            current.end = token.end
    if current is not None and not current.is_block:
        current.end = len(raw)
    for node in stack:
        node.end = len(raw)
        warnings.append(dict(kind="unclosed_block", name=node.name, offset=node.start))
    return Document(raw, text, path, tokens, roots, events, preamble, warnings)


def listing_rows(document: Document) -> list[dict[str, Any]]:
    """Read observed numeric-id/backtick-path rows and retain their locations."""
    tokens = [t for t in document.tokens if t.kind != "comment"]
    rows = []
    i = 0
    while i < len(tokens):
        token = tokens[i]
        if token.kind == "atom" and isinstance(token.value, int) and i+1 < len(tokens):
            path = tokens[i+1]
            if path.kind == "string":
                rows.append(dict(id=token.value, path=path.text, start=token.start,
                                 end=path.end, line=token.line, path_token=path.to_dict()))
                i += 2
                continue
        i += 1
    return rows


def node_record(node: Node) -> dict[str, Any]:
    """Compact source-bound field, suitable for a preview JSON response."""
    return dict(tag=node.name, values=node.data, start=node.start, end=node.end,
                line=node.tag.line, scope=list(node.scope),
                value_tokens=[t.to_dict() for t in node.values])


def parse_animation(raw: bytes, path: str | None = None) -> dict[str, Any]:
    """Expose literal ANI frame data; collision semantics remain unasserted.

    Box values are returned in source order as six-number tuples.  This module
    does not infer a rectangle convention, unit scale or native hit acceptance.
    """
    document = parse_document(raw, path)
    frames = []
    header = []
    current: dict[str, Any] | None = None
    known = {"IMAGE", "IMAGE POS", "DELAY", "ATTACK BOX", "DAMAGE BOX"}
    for node in document.events:
        match = re.fullmatch(r"FRAME(\d+)", node.name, re.IGNORECASE)
        if match:
            if current is not None:
                current["end"] = node.start
            current = dict(index=int(match.group(1)), tag=node.name,
                           start=node.start, end=len(raw), fields=[], unknown_fields=[],
                           images=[], image_positions=[], delays=[], attack_boxes=[], damage_boxes=[])
            frames.append(current)
            continue
        record = node_record(node)
        if current is None:
            header.append(record)
            continue
        current["fields"].append(record)
        key = {"IMAGE": "images", "IMAGE POS": "image_positions", "DELAY": "delays",
               "ATTACK BOX": "attack_boxes", "DAMAGE BOX": "damage_boxes"}.get(node.name.upper())
        if key:
            current[key].append(node.data)
        if node.name.upper() not in known:
            current["unknown_fields"].append(record)
    frame_counts = [n.data for n in document.find("FRAME MAX")]
    warnings = list(document.warnings)
    if frame_counts and frame_counts[0] != [len(frames)]:
        warnings.append(dict(kind="frame_count_mismatch", declared=frame_counts,
                             parsed=len(frames)))
    return dict(path=path, sha256=document.sha256, size=len(raw), encoding="cp949",
                header=header, frame_count=len(frames), frames=frames,
                warnings=warnings, box_semantics="raw values; native interpretation pending")

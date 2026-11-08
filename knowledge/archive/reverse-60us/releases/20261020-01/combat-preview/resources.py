"""Read-only 60US NPK / IMG resources, decoded without third-party packages.

Only the v1/v2 IMG layouts present in this source set are accepted.  Duplicate
logical names require an explicit package choice; this module does not infer
the original client's patch priority or equipment substitutions.
"""
from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass
from pathlib import Path
import hashlib
import struct
import threading
import zlib


class ResourceError(ValueError):
    pass


class ResourceMissing(ResourceError):
    pass


class UnsupportedFormat(ResourceError):
    pass


class ResourceConflict(ResourceError):
    def __init__(self, logical, candidates):
        self.logical = logical
        self.candidates = candidates
        super().__init__(f"Ambiguous IMG {logical}; select a package explicitly: "
                         + ", ".join(c["package"] for c in candidates))


def normalize(logical: str) -> str:
    if not isinstance(logical, str) or not logical:
        raise ResourceError("An explicit logical IMG path is required")
    if "%" in logical:
        raise ResourceError("Unresolved IMG substitution; supply the exact equipment path explicitly")
    value = logical.replace("\\", "/").strip("/")
    value = "".join(chr(ord(c) + 32) if "A" <= c <= "Z" else c for c in value)
    if any(p in ("", ".", "..") for p in value.split("/")):
        raise ResourceError("Invalid logical IMG path")
    return value if value.startswith("sprite/") else "sprite/" + value


def _read_exact(stream, length):
    result = stream.read(length)
    if len(result) != length:
        raise ResourceError(f"Truncated resource: expected {length} bytes, found {len(result)}")
    return result


def _sha_file(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def png_rgba(width: int, height: int, rgba: bytes) -> bytes:
    if width <= 0 or height <= 0 or len(rgba) != width * height * 4:
        raise ResourceError("Invalid RGBA image dimensions/length")
    def chunk(kind, data):
        return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))
    scanlines = b"".join(b"\0" + rgba[y * width * 4:(y + 1) * width * 4]
                         for y in range(height))
    return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
            + chunk(b"IDAT", zlib.compress(scanlines, 6)) + chunk(b"IEND", b""))


@dataclass(frozen=True)
class Entry:
    logical: str
    package: str
    offset: int
    length: int
    table_index: int
    raw_name_hex: str

    def metadata(self):
        return dict(logical=self.logical, package=self.package, offset=self.offset,
                    length=self.length, table_index=self.table_index, raw_name_hex=self.raw_name_hex)


class Img:
    """Parse metadata strictly; decode pixels on demand. Offsets are IMG-relative."""
    def __init__(self, data: bytes):
        self.data = data
        if len(data) < 32:
            raise ResourceError("Truncated IMG header")
        self.index_bytes = 0
        if data[:16] == b"Neople Img File\0":
            self.index_bytes, self.reserved, self.version, count = struct.unpack_from("<4I", data, 16)
            self.magic = "Neople Img File"
        elif data[:18] == b"Neople Image File\0":
            self.reserved, self.version, count = struct.unpack_from("<3I", data, 20)
            self.magic = "Neople Image File"
        else:
            raise UnsupportedFormat("Unknown IMG signature")
        if self.version not in (1, 2):
            raise UnsupportedFormat(f"IMG version {self.version} is not established for current 60US")
        if count > len(data) // 8:
            raise ResourceError("IMG frame count exceeds available record bytes")
        self.records = []
        at = 32
        for index in range(count):
            start = at
            if at + 4 > len(data):
                raise ResourceError(f"Truncated IMG frame {index}")
            color = struct.unpack_from("<i", data, at)[0]
            record_size = 8 if color == 17 else 36
            if at + record_size > len(data):
                raise ResourceError(f"Truncated IMG frame {index} record")
            values = struct.unpack_from("<" + "i" * (record_size // 4), data, at)
            at += record_size
            row = dict(index=index, record_offset=start, record_length=record_size,
                       raw_values=list(values), color_format=color)
            if color == 17:
                row["link"] = values[1]
                if not 0 <= values[1] < count:
                    raise ResourceError(f"IMG frame {index} link {values[1]} is out of range")
            else:
                if color not in (14, 15, 16):
                    raise UnsupportedFormat(f"IMG color format {color} at frame {index}")
                _, compression, w, h, stored_length, x, y, fw, fh = values
                if compression not in (5, 6):
                    raise UnsupportedFormat(f"IMG compression {compression} at frame {index}")
                if min(w, h) <= 0 or w > 16384 or h > 16384 or w * h > 64 * 1024 * 1024:
                    raise ResourceError(f"Invalid IMG frame {index} dimensions {w}x{h}")
                if stored_length < 0:
                    raise ResourceError(f"Negative IMG pixel length at frame {index}")
                length = w * h * (4 if color == 16 else 2) if compression == 5 else stored_length
                row.update(compression=compression, width=w, height=h, x=x, y=y,
                           full_width=fw, full_height=fh, stored_length=stored_length,
                           pixel_length=length, empty=(w == h == 1 and x == fw and y == 0))
            if self.version == 1:
                row["pixel_offset"] = at
                if color != 17:
                    at += row["pixel_length"]
                    if at > len(data):
                        raise ResourceError(f"Truncated IMG frame {index} pixels")
            self.records.append(row)
        self.table_end = at
        if self.version == 2:
            if self.index_bytes and at - 32 != self.index_bytes:
                raise ResourceError("IMG v2 declared index length disagrees with frame table")
            for row in self.records:
                row["pixel_offset"] = at
                if "link" not in row:
                    at += row["pixel_length"]
                    if at > len(data):
                        raise ResourceError(f"Truncated IMG frame {row['index']} pixels")
        self.consumed = at
        self.trailing_bytes = len(data) - at

    def metadata(self):
        return dict(version=self.version, magic=self.magic, count=len(self.records),
                    index_bytes=self.index_bytes, reserved=self.reserved, consumed=self.consumed,
                    trailing_bytes=self.trailing_bytes, frames=self.records)

    def decode(self, index):
        if not isinstance(index, int) or not 0 <= index < len(self.records):
            raise ResourceMissing(f"IMG frame {index} out of range (count {len(self.records)})")
        requested = index
        links = []
        while "link" in self.records[index]:
            if index in links:
                raise ResourceError(f"IMG linked frame cycle: {links + [index]}")
            links.append(index)
            index = self.records[index]["link"]
        row = self.records[index]
        offset, length = row["pixel_offset"], row["pixel_length"]
        raw = self.data[offset:offset + length]
        expected = row["width"] * row["height"] * (4 if row["color_format"] == 16 else 2)
        if row["compression"] == 6:
            decoder = zlib.decompressobj()
            try:
                raw = decoder.decompress(raw, expected + 1)
            except zlib.error as error:
                raise ResourceError(f"Invalid zlib pixels in IMG frame {index}: {error}") from error
            if not decoder.eof or decoder.unused_data or decoder.unconsumed_tail:
                raise ResourceError(f"Invalid zlib pixel stream in IMG frame {index}")
        if len(raw) != expected:
            raise ResourceError(f"IMG frame {index} decoded {len(raw)} bytes, expected {expected}")
        rgba = bytearray(row["width"] * row["height"] * 4)
        color = row["color_format"]
        if row["empty"]:
            pass  # The on-disk 1x1 sentinel has no visible sprite.
        elif color == 16:
            rgba[0::4], rgba[1::4], rgba[2::4], rgba[3::4] = raw[2::4], raw[1::4], raw[0::4], raw[3::4]
        elif color == 14:
            for p, (v,) in enumerate(struct.iter_unpack("<H", raw)):
                r, g, b = (v >> 10) & 31, (v >> 5) & 31, v & 31
                rgba[p * 4:p * 4 + 4] = bytes(((r << 3) | (r >> 2), (g << 3) | (g >> 2),
                                              (b << 3) | (b >> 2), (v >> 15) * 255))
        elif color == 15:
            for p, (v,) in enumerate(struct.iter_unpack("<H", raw)):
                rgba[p * 4:p * 4 + 4] = bytes((((v >> 8) & 15) * 17, ((v >> 4) & 15) * 17,
                                              (v & 15) * 17, (v >> 12) * 17))
        result = {key: row[key] for key in ("width", "height", "x", "y", "full_width", "full_height", "empty")}
        result.update(rgba=bytes(rgba), requested_index=requested, resolved_index=index,
                      link_chain=links, record=row)
        return result


class Assets:
    def __init__(self, root, selections=None):
        self.root = Path(root).resolve()
        if (self.root / "ImagePacks2").is_dir():
            self.root /= "ImagePacks2"
        if not self.root.is_dir():
            raise ResourceMissing(f"NPK directory does not exist: {self.root}")
        self.entries = {}
        self.packages = {}
        self.selections = {normalize(k): v for k, v in (selections or {}).items()}
        self._package_sha = {}
        self._images = OrderedDict()
        self._frames = OrderedDict()
        self._lock = threading.RLock()
        seed = (b"puchikon@neople dungeon and fighter " + b"DNF" * 100)[:255] + b"\0"
        for path in sorted(self.root.iterdir(), key=lambda p: p.name.casefold()):
            if not path.is_file() or path.suffix.casefold() != ".npk":
                continue
            size = path.stat().st_size
            with path.open("rb") as stream:
                header = _read_exact(stream, 20)
                if header[:16] != b"NeoplePack_Bill\0":
                    raise UnsupportedFormat(f"Invalid NPK signature: {path.name}")
                count = struct.unpack_from("<I", header, 16)[0]
                if count > (size - 20) // 264:
                    raise ResourceError(f"NPK table exceeds file: {path.name}")
                table = _read_exact(stream, count * 264)
            self.packages[path.name] = dict(path=str(path), size=size, count=count,
                                           table_sha256=hashlib.sha256(header + table).hexdigest())
            for i in range(count):
                offset, length = struct.unpack_from("<II", table, i * 264)
                if offset < 20 + count * 264 or offset + length > size:
                    raise ResourceError(f"NPK entry {i} outside payload bounds: {path.name}")
                encoded = table[i * 264 + 8:(i + 1) * 264]
                raw = bytes(a ^ b for a, b in zip(encoded, seed))
                if b"\0" not in raw:
                    raise ResourceError(f"Unterminated NPK entry name {i}: {path.name}")
                raw = raw.split(b"\0", 1)[0]
                try:
                    logical = normalize(raw.decode("ascii"))
                except UnicodeDecodeError:
                    logical = normalize(raw.decode("cp949", errors="strict"))
                entry = Entry(logical, path.name, offset, length, i, raw.hex())
                self.entries.setdefault(logical, []).append(entry)

    @property
    def conflicts(self):
        return {k: [v.metadata() for v in values] for k, values in self.entries.items() if len(values) > 1}

    def select(self, logical, package):
        logical = normalize(logical)
        self._entry(logical, package)
        self.selections[logical] = package

    def _entry(self, logical, package=None):
        candidates = self.entries.get(logical, [])
        if not candidates:
            raise ResourceMissing(f"IMG is absent: {logical}")
        package = package if package is not None else self.selections.get(logical)
        if package is not None:
            selected = [c for c in candidates if c.package.casefold() == str(package).casefold()]
            if len(selected) == 1:
                return selected[0]
            if not selected:
                raise ResourceMissing(f"IMG {logical} is absent from selected package {package}")
        if len(candidates) != 1:
            raise ResourceConflict(logical, [v.metadata() for v in candidates])
        return candidates[0]

    def resolve(self, logical, package=None):
        return self._entry(normalize(logical), package).metadata()

    def _load(self, entry):
        key = (entry.package, entry.offset, entry.length)
        if key in self._images:
            self._images.move_to_end(key)
            return self._images[key]
        with (self.root / entry.package).open("rb") as stream:
            stream.seek(entry.offset)
            data = _read_exact(stream, entry.length)
        img = Img(data)
        img.sha256 = hashlib.sha256(data).hexdigest()
        self._images[key] = img
        while len(self._images) > 32:
            self._images.popitem(last=False)
        return img

    def _source(self, entry, img):
        if entry.package not in self._package_sha:
            self._package_sha[entry.package] = _sha_file(self.root / entry.package)
        return dict(**entry.metadata(), npk_path=str(self.root / entry.package),
                    npk_sha256=self._package_sha[entry.package],
                    npk_size=self.packages[entry.package]["size"], img_sha256=img.sha256,
                    img_version=img.version, table_record_offset=20 + entry.table_index * 264,
                    selected_explicitly=(entry.logical in self.selections))

    def frames(self, logical, package=None):
        with self._lock:
            entry = self._entry(normalize(logical), package)
            img = self._load(entry)
            source = self._source(entry, img)
            source["selected_explicitly"] |= package is not None
            return dict(**img.metadata(), source=source)

    def frame(self, logical, index, package=None):
        with self._lock:
            entry = self._entry(normalize(logical), package)
            key = (entry.package, entry.offset, entry.length, index)
            if key in self._frames:
                self._frames.move_to_end(key)
                result = dict(self._frames[key])
                result["source"] = dict(result["source"])
                result["source"]["selected_explicitly"] = package is not None or entry.logical in self.selections
                return result
            img = self._load(entry)
            frame = img.decode(index)
            rgba = frame.pop("rgba")
            row = frame.pop("record")
            source = self._source(entry, img)
            source.update(record_offset=row["record_offset"], record_length=row["record_length"],
                          pixel_offset=row["pixel_offset"], pixel_length=row["pixel_length"],
                          record_absolute_offset=entry.offset + row["record_offset"],
                          pixel_absolute_offset=entry.offset + row["pixel_offset"],
                          record_raw_values=row["raw_values"], requested_index=index,
                          resolved_index=frame["resolved_index"], link_chain=frame["link_chain"],
                          requested_record_offset=img.records[index]["record_offset"],
                          requested_record_raw_values=img.records[index]["raw_values"],
                          link_record_offsets=[img.records[i]["record_offset"] for i in frame["link_chain"]],
                          rgba_sha256=hashlib.sha256(rgba).hexdigest())
            source["selected_explicitly"] |= package is not None
            frame.update(png=png_rgba(frame["width"], frame["height"], rgba), source=source)
            self._frames[key] = frame
            while len(self._frames) > 128:
                self._frames.popitem(last=False)
            return dict(frame, source=dict(source))

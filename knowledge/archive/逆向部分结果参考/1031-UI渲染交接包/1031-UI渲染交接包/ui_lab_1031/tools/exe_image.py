"""Bounded VA-to-file mapping for the exact 1031 PE32 EXE, read-only."""
import struct
from common import CLIENT, EXE_HASH, digest


class ExeImage:
    def __init__(self):
        self.path = CLIENT/'DNF.exe'
        if digest(self.path) != EXE_HASH:
            raise ValueError('1031 disk EXE fingerprint mismatch')
        self.file = self.path.open('rb')
        try:
            self.size = self.path.stat().st_size
            dos = self._read(0, 64)
            if dos[:2] != b'MZ':
                raise ValueError('Missing DOS header')
            pe = struct.unpack_from('<I', dos, 0x3c)[0]
            if not 64 <= pe <= 2*1024*1024:
                raise ValueError('Unbounded PE header')
            coff = self._read(pe, 24)
            if coff[:4] != b'PE\0\0' or struct.unpack_from('<H', coff, 4)[0] != 0x14c:
                raise ValueError('Expected x86 PE')
            count = struct.unpack_from('<H', coff, 6)[0]
            optional_size = struct.unpack_from('<H', coff, 20)[0]
            if not 1 <= count <= 96 or not 96 <= optional_size <= 4096:
                raise ValueError('Invalid PE table extent')
            optional = self._read(pe+24, optional_size)
            self.base = struct.unpack_from('<I', optional, 28)[0]
            if struct.unpack_from('<H', optional)[0] != 0x10b or self.base != 0x400000:
                raise ValueError('Unexpected PE32 image base')
            self.entry_rva = struct.unpack_from('<I', optional, 16)[0]
            self.headers_size = struct.unpack_from('<I', optional, 60)[0]
            self.image_size = struct.unpack_from('<I', optional, 56)[0]
            table = self._read(pe+24+optional_size, count*40)
            self.sections = []
            for i in range(count):
                entry = table[i*40:i*40+40]
                vs, rva, rs, offset = struct.unpack_from('<4I', entry, 8)
                if offset+rs > self.size:
                    raise ValueError('Section exceeds disk EXE')
                self.sections.append(dict(index=i, name=entry[:8].rstrip(b'\0').decode('ascii', 'strict'),
                                          rva=rva, virtual_size=vs, raw_size=rs, raw_offset=offset,
                                          characteristics=struct.unpack_from('<I', entry, 36)[0]))
        except Exception:
            self.close()
            raise

    def _read(self, offset, size):
        if not 0 <= offset <= self.size or not 0 <= size <= 65536 or offset+size > self.size:
            raise ValueError('Outside bounded EXE file')
        self.file.seek(offset)
        raw = self.file.read(size)
        if len(raw) != size:
            raise ValueError('Short disk EXE read')
        return raw

    def locate(self, va, size):
        if not 1 <= size <= 65536:
            raise ValueError('EXE read size must be 1..65536')
        rva = va-self.base
        candidates = [s for s in self.sections if s['rva'] <= rva and rva+size <= s['rva']+min(s['virtual_size'] or s['raw_size'], s['raw_size'])]
        if len(candidates) != 1:
            raise ValueError('VA has no unique file-backed section; zero-fill is not disk evidence')
        section = candidates[0]
        return dict(section_index=section['index'], section_name=section['name'], rva=rva,
                    file_offset=section['raw_offset']+rva-section['rva'], size=size)

    def read(self, va, size):
        location = self.locate(va, size)
        return self._read(location['file_offset'], size)

    def close(self):
        self.file.close()

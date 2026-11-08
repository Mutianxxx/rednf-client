"""Read-only 60US PVF inspection, derived from this client's instructions.

Do not assume the later 0x81A79011 key. Validate the tree CRC before using paths.
The native 0x00A54E70 also checks CRC32 with an entry-specific seed.
"""
from array import array
import argparse
import collections
import hashlib
import json
from pathlib import Path
import struct
import sys
import zlib


def decrypt(data, checksum, key=0):
    if len(data) % 4:
        raise ValueError('Encrypted length must be a multiple of four')
    words = array('I')
    words.frombytes(data)
    if sys.byteorder != 'little':
        words.byteswap()
    for i, word in enumerate(words):
        word ^= checksum ^ key
        words[i] = ((word >> 6) | (word << 26)) & 0xffffffff
    if sys.byteorder != 'little':
        words.byteswap()
    return words.tobytes()


def native_path_hash(path):
    """0x00A54F80: DJB2 variant INCLUDING the terminating NUL (ASCII sample)."""
    value=0x1505
    if not path:
        return value
    for byte in path.encode('ascii')+b'\0':
        value=(value*33+byte)&0xffffffff
    return value


class Pvf60:
    def __init__(self, path, key=0):
        self.path = Path(path)
        self.data = self.path.read_bytes()
        self.key = key
        guid_len = struct.unpack_from('<I', self.data)[0]
        if guid_len != 36:
            raise ValueError('This reader requires the observed 36-byte GUID header')
        guid = self.data[4:40].decode('ascii')
        version, tree_size, crc, count = struct.unpack_from('<4I', self.data, 40)
        self.data_base = 56 + tree_size
        tree = decrypt(self.data[56:self.data_base], crc, key)
        actual_crc = zlib.crc32(tree, count)
        if actual_crc != crc:
            raise ValueError(f'Tree CRC mismatch: {actual_crc:08x} != {crc:08x}; wrong key or source')
        self.header = dict(guid=guid, version=version, tree_size=tree_size,
                           tree_crc=f'{crc:08x}', entry_count=count, key=f'{key:08x}',
                           data_base=self.data_base, tree_crc_verified=True)
        self.entries = []
        self.by_path = {}
        pos = 0
        for _ in range(count):
            number, name_len = struct.unpack_from('<II', tree, pos)
            pos += 8
            if name_len > 4096 or pos+name_len+12 > len(tree):
                raise ValueError(f'Invalid entry at tree offset {pos}')
            name_raw = tree[pos:pos+name_len]
            pos += name_len
            name = name_raw.decode('ascii')
            size, checksum, relative = struct.unpack_from('<III', tree, pos)
            pos += 12
            offset = self.data_base+relative
            if offset+((size+3)&~3) > len(self.data):
                raise ValueError(f'Entry outside archive: {name}')
            if name.lower() in self.by_path:
                raise ValueError(f'Duplicate path: {name}')
            entry = dict(file_number=number, path=name, size=size, crc=f'{checksum:08x}',
                         relative_offset=relative, absolute_offset=offset)
            self.entries.append(entry)
            self.by_path[name.lower()] = entry
        self.header.update(parsed_tree_bytes=pos, tree_padding_hex=tree[pos:].hex())

    def read(self, path):
        entry = self.by_path[path.replace('\\', '/').lower()]
        start = entry['absolute_offset']
        padded = (entry['size']+3)&~3
        clear = decrypt(self.data[start:start+padded], int(entry['crc'], 16), self.key)
        actual = zlib.crc32(clear, entry['file_number'])
        if actual != int(entry['crc'],16):
            raise ValueError(f'Content CRC mismatch for {path}: {actual:08x} != {entry["crc"]}')
        return clear[:entry['size']]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pvf', default='DFO/Script.pvf')
    parser.add_argument('--key', type=lambda n:int(n,0), default=0)
    parser.add_argument('--verify-all', action='store_true')
    parser.add_argument('--extract', nargs='+', metavar='PVF_PATH')
    args = parser.parse_args()
    pvf = Pvf60(args.pvf, args.key)
    dest = Path(__file__).resolve().parent / 'pvf'
    dest.mkdir(exist_ok=True)
    for name in args.extract or []:
        clear = pvf.read(name)
        output = dest / name.replace('\\', '/').replace('/', '__')
        if output.resolve().parent != dest.resolve():
            raise ValueError('Invalid export filename')
        output.write_bytes(clear)
        print('extracted',name,'to',str(output),flush=True)
    (dest/'entries.json').write_text(json.dumps(pvf.entries,ensure_ascii=False,indent=2),encoding='utf-8')
    report = dict(source=str(pvf.path.resolve()), size=len(pvf.data),
                  sha256=hashlib.sha256(pvf.data).hexdigest(), header=pvf.header,
                  extensions=dict(collections.Counter(Path(e['path']).suffix for e in pvf.entries)),
                  sample_entries=[], verified_contents=0)
    buckets=collections.defaultdict(list)
    mismatches=[]
    for e in pvf.entries:
        buckets[e['file_number']].append(e['path'])
        if native_path_hash(e['path']) != e['file_number']:
            mismatches.append(e['path'])
    report['path_hash_validation']=dict(mismatches=mismatches,
        unique_hashes=len(buckets), collisions={hex(k):v for k,v in buckets.items() if len(v)>1},
        sorted_by_hash=all(a['file_number']<=b['file_number'] for a,b in zip(pvf.entries,pvf.entries[1:])))
    samples = ['stringtable.bin','n_string.lst','n_string.usa.lst','character/character.usa.lst',
               'skill/skilllist.usa.lst','skill/swordman/swordman.usa.lst','skill/swordman/uppercut.skl']
    for name in samples:
        if name not in pvf.by_path:
            continue
        clear = pvf.read(name)
        (dest/name.replace('/','__')).write_bytes(clear)
        item = dict(pvf.by_path[name], sha256=hashlib.sha256(clear).hexdigest(), head_hex=clear[:80].hex())
        report['sample_entries'].append(item)
        print(name, len(clear), repr(clear[:120]), flush=True)
    if args.verify_all:
        for i, entry in enumerate(pvf.entries):
            pvf.read(entry['path'])
            report['verified_contents'] += 1
            if i % 10000 == 0:
                print('verified',i,flush=True)
    (dest/'summary.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps({k:v for k,v in report.items() if k!='sample_entries'}, indent=2))


if __name__ == '__main__':
    main()

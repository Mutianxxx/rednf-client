"""Read current-client resource bytes from the code-verified runtime snapshot.

Chunk boundaries/decode/zlib sequence: VA 02a9d831..02a9d8b8.
String references: VA 02bc60f0; decoder: VA 02a9a440.
The mixed runtime body may already contain decrypted chunks. zlib checksum,
stream exhaustion and exact declared output length are required either way.
"""
from pathlib import Path
import struct, zlib, json, functools, hashlib

ROOT=Path(__file__).resolve().parents[1]
DEFAULT=ROOT/'reports/new-client-pvf-snapshot'

def xor_buffer(raw, key):
    w=struct.unpack('<4H',key.encode('utf-16le'))
    state=(((w[1]*449+w[2])*449+w[3])*449+w[0]*0x76826701)&0xffffffff
    out=bytearray()
    for i in range(0,len(raw),4):
        a=(state*0x343fd+0x269ec3)&0xffffffff
        state=(a*0x343fd+0x269ec3)&0xffffffff
        mask=struct.pack('<I',(a&0xffff0000)|(state>>16))
        out.extend(x^y for x,y in zip(raw[i:i+4],mask))
    return bytes(out)

class PackedPvf:
    def __init__(self, source=DEFAULT):
        self.source=Path(source)
        self.pool=(self.source/'runtime-path-pool.bin').read_bytes()
        self.wide=(self.source/'runtime-wide-pool.bin').read_bytes()
        self.body=(self.source/'runtime-packed-body.bin').read_bytes()
        self.descriptors=list(struct.iter_unpack('<II',(self.source/'runtime-chunk-descriptors.bin').read_bytes()))
        self.entries={}
        for line in (self.source/'runtime-directory.jsonl').open(encoding='utf8'):
            e=json.loads(line); self.entries[e['path'].replace('\\','/').lower()]=e
        self.chunk_modes={}

    @functools.lru_cache(maxsize=200000)
    def string(self, ref):
        if ref==0xffffffff:return ''
        data,off,unit=(self.wide,ref-1,2) if ref&1 else (self.pool,ref//2,1)
        if not 0<=off<len(data):raise ValueError(f'String reference {ref:#x} outside pool')
        end=data.find(bytes(unit),off)
        while end>=0 and (end-off)%unit:end=data.find(bytes(unit),end+1)
        if end<0:raise ValueError('Unterminated string')
        return data[off:end].decode('utf-16le' if unit==2 else 'utf8')

    @functools.lru_cache(maxsize=256)
    def chunk(self,index):
        end,size=self.descriptors[index]; start=self.descriptors[index-1][0] if index else 0
        raw=self.body[start:end]
        for mode,data in [('runtime-plain',raw),('xor-BodY',xor_buffer(raw,'BodY'))]:
            try:
                d=zlib.decompressobj(); result=d.decompress(data,size+1)
                if len(result)!=size or not d.eof or d.unused_data or d.unconsumed_tail:continue
                self.chunk_modes[index]=mode
                return result
            except zlib.error:pass
        raise ValueError(f'Chunk {index}: decode/checksum/length failed')

    def read(self,path):
        e=self.entries[path.replace('\\','/').lower()]; _,_,ci,off,n,_=e['record']
        raw=self.chunk(ci)
        if off+n>len(raw):raise ValueError('Resource bounds')
        return raw[off:off+n]

if __name__=='__main__':
    import sys
    p=PackedPvf()
    for path in sys.argv[1:]:
        raw=p.read(path); print(path,len(raw),raw[:32].hex())
        if len(raw)%5==0:
            for i,(typ,val) in enumerate(struct.iter_unpack('<BI',raw)):
                try:s=p.string(val) if typ in (3,5,6,7,8,10) else val
                except ValueError:s=f'unknown-ref {val}'
                print(i,typ,repr(s))
                if i>100:break

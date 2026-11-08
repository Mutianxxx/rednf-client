"""Read exact frozen members; no live process or external snapshot required."""
from pathlib import Path
import gzip, hashlib, json

ROOT=Path(__file__).resolve().parents[2]

class PackedPvf:
    def __init__(self):
        self.source=ROOT/'derivation/raw'
        self.index=json.loads((self.source/'index.json').read_text('utf8'))
        data=(self.source/'members.bin').read_bytes()
        if hashlib.sha256(data).hexdigest()!=self.index['members_sha256']:raise ValueError('Frozen member archive hash')
        self.data=data;self.records=self.index['entries'];self.chunk_modes={'frozen':'already decoded exact token5 bytes'}
        directory=self.source/'directory-paths.txt.gz'
        if hashlib.sha256(directory.read_bytes()).hexdigest()!=self.index['directory_sha256']:raise ValueError('Frozen directory hash')
        self.entries={p:{} for p in gzip.decompress(directory.read_bytes()).decode('utf8').splitlines()}
        for p,e in self.records.items():self.entries[p]={'record':e['record']}
    def read(self,path):
        e=self.records[path];b=self.data[e['offset']:e['offset']+e['size']]
        if len(b)!=e['size'] or hashlib.sha256(b).hexdigest()!=e['sha256']:raise ValueError('Frozen member hash: '+path)
        return b
    def string(self,ref):return self.index['strings'][str(ref)]

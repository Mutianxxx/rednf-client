"""Bind static contracts to the verified imports-only derivative of their source.

This describes disk bytes. It makes no claim about launcher patches or runtime
equivalence, and never changes an executable or contract's historical identity.
"""
import hashlib
from pathlib import Path
import struct

ORIGINAL_SHA256 = 'a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b'
IMPORTS_V4_SHA256 = 'bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e'
BACKUP = Path(__file__).resolve().parents[1]/'analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe'


def pe_sections(raw):
    if raw[:2] != b'MZ':
        raise ValueError('Missing DOS header')
    nt = struct.unpack_from('<I', raw, 0x3c)[0]
    if raw[nt:nt+4] != b'PE\0\0':
        raise ValueError('Missing PE header')
    count, optsize = struct.unpack_from('<H', raw, nt+6)[0], struct.unpack_from('<H', raw, nt+20)[0]
    if not 1 <= count <= 96:
        raise ValueError('Invalid section count')
    optional = nt+24
    if struct.unpack_from('<H',raw,optional)[0] != 0x10b:
        raise ValueError('Expected PE32')
    identity = struct.unpack_from('<I',raw,optional+16)[0], struct.unpack_from('<I',raw,optional+28)[0]
    rows = []
    for index in range(count):
        offset = optional+optsize+index*40
        name,virtual_size,rva,size,raw_offset = struct.unpack_from('<8sIIII',raw,offset)
        if raw_offset+size > len(raw):
            raise ValueError('Section extends past the file')
        rows.append(dict(name=name.rstrip(b'\0').decode('ascii'),rva=rva,
                         virtual_size=virtual_size,raw_size=size,raw=raw[raw_offset:raw_offset+size]))
    return identity,rows


def inspect_executable(path):
    path = Path(path)
    raw = path.read_bytes() if path.exists() else None
    observed = hashlib.sha256(raw).hexdigest() if raw is not None else None
    result = dict(path=str(path),observed_sha256=observed,static_evidence_sha256=observed,
                  binding='exact-file',runtime_equivalence_verified=False)
    if observed != IMPORTS_V4_SHA256:
        return result
    original = BACKUP.read_bytes()
    if hashlib.sha256(original).hexdigest() != ORIGINAL_SHA256:
        raise ValueError('静态证据备份哈希与原 v3 不符')
    original_identity,old = pe_sections(original)
    current_identity,new = pe_sections(raw)
    if original_identity != current_identity or len(new) != len(old)+1:
        raise ValueError('导入修复版 PE 入口或节结构与已核对派生关系不符')
    comparisons=[]
    for a,b in zip(old,new):
        if any(a[key] != b[key] for key in ('name','rva','virtual_size','raw_size','raw')):
            raise ValueError('导入修复版改变了原静态证据节: '+a['name'])
        comparisons.append(dict(name=a['name'],rva=hex(a['rva']),size=a['raw_size'],
                                sha256=hashlib.sha256(a['raw']).hexdigest()))
    result.update(static_evidence_sha256=ORIGINAL_SHA256,binding='verified-imports-only-derivative',
                  original_path=str(BACKUP),unchanged_original_sections=comparisons,
                  limitation='Static disk contracts only; launcher replaces protected combat branches at runtime.')
    return result

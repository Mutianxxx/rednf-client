from pathlib import Path
import sys,struct,re,json,hashlib
sys.path.insert(0,r'D:\dnf\60US\analysis\deps')
import pefile
SOURCE=Path(r'D:\dnf\60US\DFO\DFO_fixed_v3.exe')
ROOT=Path(__file__).parent
raw=SOURCE.read_bytes(); pe=pefile.PE(data=raw); base=pe.OPTIONAL_HEADER.ImageBase
def va(off): return base+pe.get_rva_from_offset(off)
def off(va): return pe.get_offset_from_rva(va-base)
def read(va,n):
    o=off(va); return raw[o:o+n]
def u32(va): return struct.unpack('<I',read(va,4))[0]
def refs(ptr): return [m.start() for m in re.finditer(re.escape(struct.pack('<I',ptr)),raw)]
def executable(ptr):
    rva=ptr-base
    return any(s.Characteristics&0x20000000 and s.VirtualAddress<=rva<s.VirtualAddress+max(s.Misc_VirtualSize,s.SizeOfRawData) for s in pe.sections)
slots=[0x14,0x188,0x22c,0x28c,0x290,0x294,0x298,0x64c,0x654,0x658,0x65c,0x674,0x678,0x67c,0x680,0x738,0x73c,0x760,0x768,0x790,0x798]
rows=[]
for m in re.finditer(rb'\.\?AV[^\0]{1,100}\x00',raw):
    name=m.group()[:-1].decode('ascii',errors='replace')
    if name not in {'.?AVCN'+q+'@@' for q in ('Swordman','Fighter','Gunner','Mage','Priest')}:continue
    td=va(m.start()-8); cols=[]
    for r in refs(td):
        coloff=r-12
        if coloff<0:continue
        sig,offset,cd,typ,hier=struct.unpack_from('<IIIII',raw,coloff)
        if sig!=0 or typ!=td or offset>0x10000 or cd>0x10000:continue
        colva=va(coloff); tables=[]
        for vr in refs(colva):
            vt=va(vr+4)
            try:first=u32(vt)
            except Exception:continue
            if not executable(first):continue
            table={'vtable_va':f'0x{vt:08X}','col_pointer_va':f'0x{va(vr):08X}', 'slots':{f'0x{s:03X}':f'0x{u32(vt+s):08X}' for s in slots}}
            table['vtable_prefix_hex']=read(vt,0x7d8).hex();table['vtable_prefix_sha256']=hashlib.sha256(read(vt,0x7d8)).hexdigest()
            tables.append(table)
        cols.append({'col_va':f'0x{colva:08X}','offset':offset,'cd_offset':cd,'hierarchy_va':f'0x{hier:08X}','raw_hex':raw[coloff:coloff+20].hex(),'vtables':tables})
    rows.append({'rtti_name':name,'type_descriptor_va':f'0x{td:08X}','name_va':f'0x{va(m.start()):08X}','complete_object_locators':cols})
result={'source':str(SOURCE),'source_sha256':hashlib.sha256(raw).hexdigest(),'method':'Exact five main class MSVC x86 TypeDescriptor -> COL (pointer at +12) -> vtable[-1], first slot executable. These static records do not alone prove runtime class registration.','classes':rows}
(ROOT/'controllers.json').write_text(json.dumps(result,indent=2),encoding='utf8')
for row in rows:
    print(row['rtti_name'],row['type_descriptor_va'])
    for c in row['complete_object_locators']:
        for v in c['vtables']:
            print('  COL',c['col_va'],'offset',c['offset'],'vtable',v['vtable_va'],' '.join(s+'='+v['slots'][s] for s in ('0x014','0x188','0x22C','0x28C','0x768')))

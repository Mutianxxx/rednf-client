"""Bounded offline resource inspection; no native scheduling or format guesses."""
import hashlib
import lzma
import re
import struct
import zlib


def sha256(raw):
    return hashlib.sha256(raw).hexdigest()


def format_parts(template):
    matches=list(re.finditer(r'%(?:0[1-9][0-9]*)?d|%%',template))
    parts=[];specs=[];cursor=0;literal=''
    for match in matches:
        chunk=template[cursor:match.start()]
        if '%' in chunk:raise ValueError('Unsupported IMG format placeholder')
        literal+=chunk
        if match.group()=='%%':literal+='%'
        else:
            parts.append(literal);literal='';specs.append(match.group())
        cursor=match.end()
    literal+=template[cursor:]
    if '%' in template[cursor:]:raise ValueError('Unsupported IMG format placeholder')
    parts.append(literal)
    return parts,specs


def template_parameters(template,name,limit=128):
    parts,specs=format_parts(template)
    if not name.startswith(parts[0]):return [],True
    results=[];truncated=False
    def visit(index,cursor,values):
        nonlocal truncated
        if len(results)>=limit:
            truncated=True;return
        if index==len(specs):
            if cursor==len(name):results.append(values)
            return
        for end in range(cursor+1,len(name)+1):
            fragment=name[cursor:end]
            if not re.fullmatch(r'-?[0-9]+',fragment):continue
            if len(fragment)>32:continue
            value=int(fragment)
            if specs[index]%value!=fragment:continue
            suffix=parts[index+1]
            if not name.startswith(suffix,end):continue
            visit(index+1,end+len(suffix),values+[value])
    visit(0,len(parts[0]),[])
    return results,not truncated


def compound_streams(raw):
    if len(raw)<512 or raw[:8]!=bytes.fromhex('d0cf11e0a1b11ae1'):
        raise ValueError('Compound signature/header')
    major,byte_order,shift,mini_shift=struct.unpack_from('<4H',raw,26)
    if byte_order!=0xfffe or (major,shift) not in ((3,9),(4,12)) or mini_shift!=6:
        raise ValueError('Unsupported compound sector profile')
    sector_size=1<<shift;sector_count=(len(raw)-sector_size)//sector_size
    fat_count,directory,_,cutoff,mini_start,mini_count,difat_start,difat_count=struct.unpack_from('<8I',raw,44)
    end=0xfffffffe;free=0xffffffff;used=set()
    def sector(index):
        if not 0<=index<sector_count:raise ValueError('Compound sector bounds')
        used.add(index);offset=(index+1)*sector_size
        return raw[offset:offset+sector_size]
    fat_sectors=[value for value in struct.unpack_from('<109I',raw,76) if value!=free]
    cursor=difat_start;difat_seen=set()
    for unused in range(difat_count):
        if cursor in difat_seen:raise ValueError('Compound DIFAT cycle')
        difat_seen.add(cursor);values=struct.unpack('<'+str(sector_size//4)+'I',sector(cursor))
        fat_sectors.extend(value for value in values[:-1] if value!=free);cursor=values[-1]
    if len(fat_sectors)!=fat_count or len(set(fat_sectors))!=fat_count:
        raise ValueError('Compound FAT count/duplicates')
    fat=[]
    for index in fat_sectors:fat.extend(struct.unpack('<'+str(sector_size//4)+'I',sector(index)))
    def chain(start,table,reader):
        chunks=[];visited=set();current=start
        while current!=end:
            if current in visited or not 0<=current<len(table) or len(visited)>sector_count*8:
                raise ValueError('Compound chain cycle/bounds')
            visited.add(current);chunks.append(reader(current));current=table[current]
        return b''.join(chunks),sorted(visited)
    directory_raw,directory_chain=chain(directory,fat,sector)
    entries=[]
    for offset in range(0,len(directory_raw),128):
        entry=directory_raw[offset:offset+128];length=struct.unpack_from('<H',entry,64)[0];kind=entry[66]
        if not kind or not length:continue
        if length<2 or length>64 or length%2:raise ValueError('Compound directory name')
        name=entry[:length-2].decode('utf-16le','strict')
        start,size=struct.unpack_from('<IQ',entry,116)
        entries.append(dict(name=name,type=kind,start=start,size=size,directory_offset=offset))
    roots=[entry for entry in entries if entry['type']==5]
    if len(roots)!=1:raise ValueError('Compound root count')
    mini_fat=[];mini_blob=b''
    if mini_count:
        mini_raw,mini_chain=chain(mini_start,fat,sector)
        if len(mini_chain)!=mini_count:raise ValueError('Compound MiniFAT count')
        mini_fat=list(struct.unpack('<'+str(len(mini_raw)//4)+'I',mini_raw))
        mini_blob=chain(roots[0]['start'],fat,sector)[0][:roots[0]['size']]
    def mini_sector(index):
        offset=index*64
        if offset+64>len(mini_blob):raise ValueError('Compound mini sector bounds')
        return mini_blob[offset:offset+64]
    streams=[]
    for entry in entries:
        if entry['type']!=2:continue
        if entry['size']>64*1024*1024:raise ValueError('Compound inspection size limit')
        table,reader=(mini_fat,mini_sector) if entry['size']<cutoff and entry['size'] else (fat,sector)
        data,indices=chain(entry['start'],table,reader)
        if len(data)<entry['size']:raise ValueError('Compound stream truncated')
        payload=data[:entry['size']]
        streams.append(dict(**entry,sector_chain=indices,sha256=sha256(payload),head_hex=payload[:64].hex(),payload=payload))
    highest=max(used,default=-1)
    trailing=raw[(highest+2)*sector_size:]
    unreferenced=[]
    for index in range(sector_count):
        if index in used:continue
        payload=raw[(index+1)*sector_size:(index+2)*sector_size]
        nonzero=sum(value!=0 for value in payload)
        if nonzero:unreferenced.append(dict(index=index,nonzero_bytes=nonzero,sha256=sha256(payload),head_hex=payload[:32].hex()))
    aligned_end=(sector_count+1)*sector_size;final_tail=raw[aligned_end:]
    return dict(major_version=major,sector_size=sector_size,directory_chain=directory_chain,entries=entries,
        sector_count=sector_count,streams=streams,referenced_sectors=sorted(used),
        unreferenced_full_sectors=[index for index in range(sector_count) if index not in used],
        unreferenced_nonzero_sectors=unreferenced,unreferenced_sector_nonzero_bytes=sum(row['nonzero_bytes'] for row in unreferenced),
        tail_after_last_referenced_sector=dict(offset=(highest+2)*sector_size,length=len(trailing),sha256=sha256(trailing)),
        final_unaligned_tail=dict(offset=aligned_end,length=len(final_tail),nonzero_bytes=sum(value!=0 for value in final_tail),sha256=sha256(final_tail)))


def rtf_plaintext(raw):
    if not raw.startswith(b'{\\rtf'):raise ValueError('RTF signature')
    if len(raw)>32*1024*1024:raise ValueError('RTF inspection size limit')
    codepage_match=re.search(rb'\\ansicpg([0-9]+)',raw)
    codepage=int(codepage_match[1]) if codepage_match else 1252
    states=[dict(skip=False,uc=1,hidden=False)];output=[];ansi=bytearray();cursor=0;fallback=0;binary=0;decode_errors=0
    skipped_destinations={'fonttbl','colortbl','stylesheet','info','generator','pict','object','objdata','datastore',
        'themedata','colorschememapping','xmlopen','xmlattrname','xmlattrvalue','xmlname','xmlnstbl','listtable',
        'listoverridetable','revtbl','rsidtbl','filetbl','datafield','formfield'}
    symbols={ord('~'):'\u00a0',ord('_'):'\u2011',ord('-'):'',ord('\\'):'\\',ord('{'):'{',ord('}'):'}'}
    words={'par':'\n','line':'\n','tab':'\t','emdash':'\u2014','endash':'\u2013','bullet':'\u2022',
        'lquote':'\u2018','rquote':'\u2019','ldblquote':'\u201c','rdblquote':'\u201d','enspace':' ',
        'emspace':' ','qmspace':' '}
    def flush():
        nonlocal decode_errors
        if not ansi:return
        try:output.append(ansi.decode('cp'+str(codepage),'strict'))
        except (UnicodeDecodeError,LookupError):
            decode_errors+=1
            try:output.append(ansi.decode('cp'+str(codepage),'replace'))
            except LookupError:output.append(ansi.decode('cp1252','replace'))
        ansi.clear()
    while cursor<len(raw):
        value=raw[cursor]
        if fallback:
            fallback-=1
            if value==0x5c and cursor+1<len(raw):
                if raw[cursor+1]==0x27:cursor+=4
                elif raw[cursor+1] in b"\\{}":cursor+=2
                else:
                    cursor+=2
                    while cursor<len(raw) and ((65<=raw[cursor]<=90) or (97<=raw[cursor]<=122)):cursor+=1
                    if cursor<len(raw) and raw[cursor] in b'-0123456789':
                        while cursor<len(raw) and raw[cursor] in b'-0123456789':cursor+=1
                    if cursor<len(raw) and raw[cursor]==0x20:cursor+=1
                continue
            cursor+=1;continue
        state=states[-1]
        if binary:
            cursor+=min(binary,len(raw)-cursor);binary=0;continue
        if value==ord('{'):
            flush();states.append(state.copy());cursor+=1;continue
        if value==ord('}'):
            flush()
            if len(states)==1:raise ValueError('RTF group underflow')
            states.pop();cursor+=1;continue
        if value in (10,13):cursor+=1;continue
        if value!=0x5c:
            if not state['skip'] and not state['hidden']:ansi.append(value)
            cursor+=1;continue
        cursor+=1
        if cursor>=len(raw):raise ValueError('RTF trailing escape')
        control=raw[cursor]
        if control!=ord("'"):flush()
        if not (65<=control<=90 or 97<=control<=122):
            cursor+=1
            if control==ord("'"):
                if cursor+2>len(raw):raise ValueError('RTF truncated hex escape')
                try:decoded=bytes([int(raw[cursor:cursor+2],16)])
                except ValueError as exc:raise ValueError('RTF invalid hex escape') from exc
                cursor+=2
                if not state['skip'] and not state['hidden']:ansi.extend(decoded)
            elif control==ord('*'):state['skip']=True
            elif control in symbols and not state['skip'] and not state['hidden']:output.append(symbols[control])
            continue
        start=cursor
        while cursor<len(raw) and ((65<=raw[cursor]<=90) or (97<=raw[cursor]<=122)):cursor+=1
        word=raw[start:cursor].decode('ascii').lower();number=None
        sign=cursor
        if cursor<len(raw) and raw[cursor] in b'-0123456789':
            if raw[cursor]==ord('-'):cursor+=1
            digits=cursor
            while cursor<len(raw) and 48<=raw[cursor]<=57:cursor+=1
            if cursor>digits:number=int(raw[sign:cursor])
            else:cursor=sign
        if cursor<len(raw) and raw[cursor]==0x20:cursor+=1
        if word in skipped_destinations:state['skip']=True
        elif word=='ansicpg' and number and 0<number<65536:codepage=number
        elif word=='uc' and number is not None:state['uc']=max(0,min(number,16))
        elif word=='u' and number is not None and not state['skip'] and not state['hidden']:
            output.append(chr(number&0xffff));fallback=state['uc']
        elif word=='v':state['hidden']=number!=0
        elif word=='bin' and number is not None:binary=max(0,min(number,len(raw)-cursor))
        elif not state['skip'] and not state['hidden']:
            text=words.get(word)
            if text is not None:output.append(text)
    flush()
    if len(states)!=1:raise ValueError('RTF unclosed group')
    text=''.join(output).encode('utf-16le','surrogatepass').decode('utf-16le','replace')
    return dict(text=text,declared_codepage=int(codepage_match[1]) if codepage_match else None,
        parser='bounded RTF control-word/group parser; CP codepage and Unicode escapes',source_bytes=len(raw),
        decoded_ansi_runs_with_replacement=decode_errors,
        embedded_controls={name:len(re.findall(rb'\\'+name.encode()+rb'\b',raw)) for name in ('object','objdata','pict','field')},
        formatting='Original RTF retained; formatting, layout, font-specific codepages and embedded objects are not reproduced')


def decode_tenslx_payload(raw,limit=64*1024*1024):
    if len(raw)<36 or raw[:4]!=bytes.fromhex('c0ef11e0'):
        raise ValueError('TenSLX payload wrapper signature/header')
    version,header_size,compressed_size,stored_crc=struct.unpack_from('<4I',raw,4)
    if version!=1 or header_size!=36 or compressed_size!=len(raw)-header_size:
        raise ValueError('TenSLX wrapper version/length')
    properties=raw[20:25];property_byte=properties[0]
    if property_byte>=9*5*5:raise ValueError('TenSLX LZMA properties')
    lc=property_byte%9;remainder=property_byte//9;lp=remainder%5;pb=remainder//5
    dictionary=struct.unpack_from('<I',properties,1)[0]
    if not 4096<=dictionary<=limit:raise ValueError('TenSLX LZMA dictionary limit')
    reserved=raw[25:28];expected_size=struct.unpack_from('<I',raw,28)[0]
    if expected_size>limit:raise ValueError('TenSLX decompressed-size limit')
    stored_checksum=struct.unpack_from('<I',raw,32)[0]
    decoder=lzma.LZMADecompressor(format=lzma.FORMAT_RAW,
        filters=[dict(id=lzma.FILTER_LZMA1,dict_size=dictionary,lc=lc,lp=lp,pb=pb)])
    decoded=decoder.decompress(raw[header_size:],max_length=expected_size+2)
    return dict(version=version,header_size=header_size,compressed_size=compressed_size,
        stored_crc=stored_crc,properties_hex=properties.hex(),dictionary_size=dictionary,
        lc=lc,lp=lp,pb=pb,reserved_hex=reserved.hex(),declared_output_size=expected_size,
        actual_output_size=len(decoded),size_matches=len(decoded)==expected_size,
        output_sha256=sha256(decoded),output_head_hex=decoded[:64].hex(),
        output_magic=decoded[:8].decode('ascii','replace'),decoder_eof=decoder.eof,
        unused_compressed_bytes=len(decoder.unused_data),crc32= zlib.crc32(decoded)&0xffffffff,
        checksum_verified=False,checksum_note='Stored wrapper checksum has not been identified or validated',payload=decoded)


def pe_imports_exports(raw):
    if len(raw)<64 or raw[:2]!=b'MZ':raise ValueError('PE DOS header')
    pe=struct.unpack_from('<I',raw,0x3c)[0]
    if raw[pe:pe+4]!=b'PE\0\0':raise ValueError('PE signature')
    machine,section_count,_,_,_,optional_size,_=struct.unpack_from('<HHIIIHH',raw,pe+4)
    optional=pe+24;magic=struct.unpack_from('<H',raw,optional)[0]
    if magic not in (0x10b,0x20b):raise ValueError('PE optional header magic')
    directory_offset=optional+(96 if magic==0x10b else 112)
    directory_count=struct.unpack_from('<I',raw,optional+(92 if magic==0x10b else 108))[0]
    sections=[];at=optional+optional_size
    for index in range(section_count):
        row=raw[at+40*index:at+40*(index+1)]
        name=row[:8].split(b'\0',1)[0].decode('ascii','replace')
        virtual_size,rva,raw_size,raw_offset=struct.unpack_from('<IIII',row,8)
        sections.append(dict(name=name,rva=rva,virtual_size=virtual_size,raw_offset=raw_offset,raw_size=raw_size))
    def offset(rva):
        for section in sections:
            size=max(section['virtual_size'],section['raw_size'])
            if section['rva']<=rva<section['rva']+size:
                value=section['raw_offset']+rva-section['rva']
                if value>=len(raw):break
                return value
        if rva<len(raw):return rva
        raise ValueError('PE RVA outside sections: '+hex(rva))
    def cstring(rva):
        start=offset(rva);end=raw.find(b'\0',start)
        if end<0:raise ValueError('PE unterminated string')
        return raw[start:end].decode('ascii','replace')
    def directory(index):
        if directory_count<=index:return (0,0)
        return struct.unpack_from('<II',raw,directory_offset+index*8)
    imports=[];import_rva,_=directory(1);thunk_width=8 if magic==0x20b else 4
    descriptor=offset(import_rva) if import_rva else 0
    if descriptor:
        for _ in range(4096):
            original,stamp,chain,name_rva,first=struct.unpack_from('<IIIII',raw,descriptor);descriptor+=20
            if not any((original,stamp,chain,name_rva,first)):break
            dll=cstring(name_rva);thunk=offset(original or first);symbols=[]
            for _ in range(65536):
                value=int.from_bytes(raw[thunk:thunk+thunk_width],'little');thunk+=thunk_width
                if not value:break
                ordinal_flag=1<<(thunk_width*8-1)
                symbols.append(dict(ordinal=value&0xffff) if value&ordinal_flag else dict(name=cstring((value&0x7fffffff if thunk_width==4 else value&0x7fffffffffffffff)+2)))
            imports.append(dict(dll=dll,symbols=symbols))
    exports=[];export_rva,_=directory(0)
    if export_rva:
        directory_at=offset(export_rva)
        _,_,_,_,name_rva,base,function_count,name_count,functions,names,ordinals=struct.unpack_from('<IIHHIIIIIII',raw,directory_at)
        name_values=[];name_at=offset(names)
        for index in range(min(name_count,100000)):
            name_values.append(struct.unpack_from('<I',raw,name_at+4*index)[0])
        ordinal_at=offset(ordinals);function_at=offset(functions)
        for index in range(min(function_count,100000)):
            target=struct.unpack_from('<I',raw,function_at+4*index)[0]
            rows=[]
            for name_index,name_value in enumerate(name_values):
                ordinal_index=struct.unpack_from('<H',raw,ordinal_at+2*name_index)[0]
                if ordinal_index==index:rows.append(cstring(name_value))
            exports.append(dict(ordinal=base+index,names=rows,rva=target,forwarded=bool(export_rva<=target<export_rva+directory(0)[1])))
    return dict(machine=machine,pe32_plus=magic==0x20b,sections=sections,imports=imports,exports=exports)

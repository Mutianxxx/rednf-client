"""Read-only Windows font raster probe, not an in-game capture.

Load an ephemeral private-name copy into this process only, compare selected
glyph/hint/metric tables with the immutable source, then render a grayscale GDI
sample with TrueType grid fitting. Whole-file equality is expected to be false
because of the private name alias; no font file is written or installed.
"""
from pathlib import Path
import ctypes as C
from ctypes import wintypes as W
import hashlib
import json
import struct
from io import BytesIO
from fontTools.ttLib import TTFont
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
out = ROOT / 'reports/font-reference'
out.mkdir(parents=True, exist_ok=True)
raw = (ROOT.parent / 'DNF1031客户端/Fonts/msjh.ttf').read_bytes()
private = bytearray(raw)
for index in range(struct.unpack_from('>H',raw,4)[0]):
    at=12+index*16
    if raw[at:at+4] != b'name': continue
    table=struct.unpack_from('>I',raw,at+8)[0]
    _,entries,strings=struct.unpack_from('>HHH',raw,table)
    for n in range(entries):
        platform,encoding,language,name_id,length,offset=struct.unpack_from('>HHHHHH',raw,table+6+n*12)
        if name_id not in (1,4,6):continue
        start=table+strings+offset
        old=raw[start:start+length]
        if old == 'FangSong'.encode('utf-16-be'):
            private[start:start+length]='DNFSrcUI'.encode('utf-16-be')
        elif old == b'FangSong':
            private[start:start+length]=b'DNFSrcUI'
    break
gdi = C.WinDLL('gdi32', use_last_error=True)
gdi.AddFontMemResourceEx.argtypes = [C.c_void_p, W.DWORD, C.c_void_p, C.POINTER(W.DWORD)]
gdi.AddFontMemResourceEx.restype = W.HANDLE
gdi.RemoveFontMemResourceEx.argtypes = [W.HANDLE]
gdi.CreateCompatibleDC.argtypes = [W.HDC]
gdi.CreateCompatibleDC.restype = W.HDC
gdi.CreateFontW.argtypes = [C.c_int]*5+[W.DWORD]*8+[W.LPCWSTR]
gdi.CreateFontW.restype = W.HANDLE
gdi.SelectObject.argtypes = [W.HDC, W.HANDLE]
gdi.SelectObject.restype = W.HANDLE
gdi.DeleteObject.argtypes = [W.HANDLE]
gdi.DeleteDC.argtypes = [W.HDC]
gdi.GetFontData.argtypes = [W.HDC, W.DWORD, W.DWORD, C.c_void_p, W.DWORD]
gdi.GetFontData.restype = W.DWORD
gdi.TextOutW.argtypes = [W.HDC, C.c_int, C.c_int, W.LPCWSTR, C.c_int]
gdi.SetTextColor.argtypes = [W.HDC, W.COLORREF]
gdi.SetBkMode.argtypes = [W.HDC, C.c_int]

class BitmapInfo(C.Structure):
    _fields_=[('size',W.DWORD),('width',W.LONG),('height',W.LONG),('planes',W.WORD),
              ('bits',W.WORD),('compression',W.DWORD),('image_size',W.DWORD),
              ('xp',W.LONG),('yp',W.LONG),('used',W.DWORD),('important',W.DWORD),
              ('colors',W.DWORD*3)]
gdi.CreateDIBSection.argtypes = [W.HDC,C.POINTER(BitmapInfo),W.UINT,C.POINTER(C.c_void_p),W.HANDLE,W.DWORD]
gdi.CreateDIBSection.restype = W.HBITMAP

font_buffer = C.create_string_buffer(bytes(private))
count = W.DWORD()
font_resource = gdi.AddFontMemResourceEx(font_buffer,len(raw),None,C.byref(count))
if not font_resource: raise C.WinError(C.get_last_error())
dc = gdi.CreateCompatibleDC(None)
info = BitmapInfo();info.size=40;info.width=750;info.height=-150;info.planes=1;info.bits=32
bits=C.c_void_p()
bitmap=gdi.CreateDIBSection(dc,C.byref(info),0,C.byref(bits),None,0)
if not dc or not bitmap:raise C.WinError(C.get_last_error())
old_bitmap=gdi.SelectObject(dc,bitmap)
gdi.SetBkMode(dc,1);gdi.SetTextColor(dc,0xffffff)
records=[]
try:
    for i,size in enumerate((11,12,13,14,16)):
        font=gdi.CreateFontW(-size,0,0,0,400,0,0,0,134,0,0,4,0,'DNFSrcUI')
        old_font=gdi.SelectObject(dc,font)
        actual_size=gdi.GetFontData(dc,0,0,None,0)
        actual=C.create_string_buffer(actual_size)
        gdi.GetFontData(dc,0,0,actual,actual_size)
        actual_hash=hashlib.sha256(actual.raw).hexdigest()
        original=TTFont(BytesIO(raw));selected=TTFont(BytesIO(actual.raw))
        tables={name:original.getTableData(name)==selected.getTableData(name)
                for name in original.keys() if name!='GlyphOrder' and name in selected}
        records.append({'size':size,'font_sha256':actual_hash,'matches_source':actual.raw==raw,
                        'tables_equal':tables})
        text=f'{size}px 赛丽亚 任务完成。冒险家，请打开技能栏。12345 ASDF'
        if not gdi.TextOutW(dc,6,i*30,text,len(text)):raise C.WinError(C.get_last_error())
        gdi.SelectObject(dc,old_font);gdi.DeleteObject(font)
    gdi.GdiFlush()
    rgb=Image.frombytes('RGB',(750,150),C.string_at(bits,750*150*4),'raw','BGRX')
    rgb.save(out/'gdi-hinted-probe.png')
    rgb.resize((1500,300),Image.Resampling.NEAREST).save(out/'gdi-hinted-probe-2x.png')
    (out/'gdi-hinted-probe.json').write_text(json.dumps({'scope':'Diagnostic raster only; not in-game capture',
          'backend':'GDI ANTIALIASED_QUALITY, private process memory font',
          'source_sha256':hashlib.sha256(raw).hexdigest(),'samples':records},indent=2),encoding='utf-8')
finally:
    gdi.SelectObject(dc,old_bitmap);gdi.DeleteObject(bitmap);gdi.DeleteDC(dc)
    gdi.RemoveFontMemResourceEx(font_resource)
print(json.dumps(records,indent=2))

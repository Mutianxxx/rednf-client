from pathlib import Path
import ctypes,json,hashlib,datetime,platform,struct
from ctypes import wintypes
root=Path(r'D:\dnf\60US\DFO\ImagePacks2');out=Path(r'D:\dnf\60US\analysis\npk60\native-priority')
class FILETIME(ctypes.Structure):_fields_=[('dwLowDateTime',wintypes.DWORD),('dwHighDateTime',wintypes.DWORD)]
class WIN32_FIND_DATAW(ctypes.Structure):
 _fields_=[('dwFileAttributes',wintypes.DWORD),('ftCreationTime',FILETIME),('ftLastAccessTime',FILETIME),('ftLastWriteTime',FILETIME),('nFileSizeHigh',wintypes.DWORD),('nFileSizeLow',wintypes.DWORD),('dwReserved0',wintypes.DWORD),('dwReserved1',wintypes.DWORD),('cFileName',wintypes.WCHAR*260),('cAlternateFileName',wintypes.WCHAR*14)]
k=ctypes.WinDLL('kernel32',use_last_error=True);k.FindFirstFileW.argtypes=[wintypes.LPCWSTR,ctypes.POINTER(WIN32_FIND_DATAW)];k.FindFirstFileW.restype=wintypes.HANDLE;k.FindNextFileW.argtypes=[wintypes.HANDLE,ctypes.POINTER(WIN32_FIND_DATAW)];k.FindNextFileW.restype=wintypes.BOOL;k.FindClose.argtypes=[wintypes.HANDLE];k.FindClose.restype=wintypes.BOOL
rows=[];data=WIN32_FIND_DATAW();h=k.FindFirstFileW(str(root/'*.npk'),ctypes.byref(data))
if h==ctypes.c_void_p(-1).value:raise ctypes.WinError(ctypes.get_last_error())
try:
 while True:
  rows.append({'ordinal':len(rows),'name':data.cFileName,'size':data.nFileSizeLow+(data.nFileSizeHigh<<32),'attributes':data.dwFileAttributes})
  if not k.FindNextFileW(h,ctypes.byref(data)):
   end_error=ctypes.get_last_error();break
finally:k.FindClose(h)
manifest=Path(r'D:\dnf\60US\DFO\localpackage.lst');raw=manifest.read_bytes();hits=[]
for name in ('sprite_character_swordman_equipment_avatar_skin.npk','sprite_character_swordman_equipment_avatar_skin1.NPK','ImagePacks2'):
 needle=name.encode('ascii');start=0
 while True:
  pos=raw.lower().find(needle.lower(),start)
  if pos<0:break
  hits.append({'name':name,'file_offset':pos,'context_hex':raw[max(0,pos-16):pos+len(needle)+64].hex()});start=pos+len(needle)
record={'kind':'read-only Win32 filesystem observation, not game execution','observed_at':datetime.datetime.now().astimezone().isoformat(),'platform':platform.platform(),'root':str(root),'pattern':'*.npk','api':'FindFirstFileW/FindNextFileW','end_error':end_error,'count':len(rows),'skin_candidates':[r for r in rows if 'swordman_equipment_avatar_skin' in r['name'].lower()],'enumeration':rows,'localpackage':{'path':str(manifest),'length':len(raw),'sha256':hashlib.sha256(raw).hexdigest(),'header_hex':raw[:80].hex(),'ascii_name_hits':hits}}
(out/'filesystem-enumeration.json').write_text(json.dumps(record,ensure_ascii=False,indent=2),encoding='utf8')
print(json.dumps({k:v for k,v in record.items() if k!='enumeration'},ensure_ascii=False,indent=2))


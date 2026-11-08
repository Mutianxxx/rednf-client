"""Download pinned portable build dependencies; no system installation."""
from pathlib import Path
import urllib.request,hashlib,json,zipfile,tarfile,concurrent.futures,time
ROOT=Path(__file__).resolve().parents[1]
BASE=ROOT/'third_party'
ITEMS={
 'llvm.zip':'https://github.com/mstorsjo/llvm-mingw/releases/download/20261006/llvm-mingw-20261006-ucrt-x86_64.zip',
 'cmake.zip':'https://github.com/Kitware/CMake/releases/download/v4.4.4/cmake-4.4.4-windows-x86_64.zip',
 'ninja.zip':'https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-win.zip',
 'sdl.tar.gz':'https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-devel-2.32.10-mingw.tar.gz',
 'zlib.tar.gz':'https://zlib.net/fossils/zlib-1.3.1.tar.gz',
 'json.hpp':'https://raw.githubusercontent.com/nlohmann/json/v3.12.0/single_include/nlohmann/json.hpp',
 'stb_truetype.h':'https://raw.githubusercontent.com/nothings/stb/f0569113c93ad095470c54bf34a17b36646bbbb5/stb_truetype.h',
 'stb_vorbis.c':'https://raw.githubusercontent.com/nothings/stb/f0569113c93ad095470c54bf34a17b36646bbbb5/stb_vorbis.c',
 'stb_image_write.h':'https://raw.githubusercontent.com/nothings/stb/f0569113c93ad095470c54bf34a17b36646bbbb5/stb_image_write.h',
}
def get(item):
 name,url=item; target=BASE/name
 for attempt in range(4):
  try:
   if not target.exists():
    tmp=target.with_suffix(target.suffix+'.part')
    req=urllib.request.Request(url,headers={'User-Agent':'dnf-native-demo/1.0'})
    with urllib.request.urlopen(req,timeout=90) as src,tmp.open('wb') as dst:
     while True:
      b=src.read(1024*1024)
      if not b:break
      dst.write(b)
    tmp.replace(target)
   sha=hashlib.file_digest(target.open('rb'),'sha256').hexdigest()
   marker=BASE/(name+'.extracted')
   if not marker.exists():
    if name.endswith('.zip'):
     dest=BASE/'ninja' if name=='ninja.zip' else BASE
     with zipfile.ZipFile(target) as z:z.extractall(dest)
    elif name.endswith('.tar.gz'):
     with tarfile.open(target) as t:t.extractall(BASE,filter='data')
    marker.write_text(sha)
   print('READY',name,target.stat().st_size,flush=True)
   return {'file':name,'url':url,'sha256':sha,'size':target.stat().st_size}
  except Exception as exc:
   print('RETRY',name,str(exc),flush=True)
   if attempt==3:raise
   time.sleep(2)
def main():
 BASE.mkdir(exist_ok=True)
 with concurrent.futures.ThreadPoolExecutor(max_workers=5) as pool: rows=list(pool.map(get,ITEMS.items()))
 (BASE/'dependencies.lock.json').write_text(json.dumps(rows,indent=2)+'\n')
if __name__=='__main__':main()

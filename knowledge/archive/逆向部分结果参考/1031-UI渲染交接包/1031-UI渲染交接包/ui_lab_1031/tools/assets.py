"""Persistent native PVF/NPK reader, UTF8 JSON pipe and immutable PNG cache."""
import argparse, hashlib, json, subprocess, threading
from pathlib import Path
from common import ROOT, CLIENT, EXE_HASH, PVF_HASH, verify_client, digest

def normalized(s):
    return s.replace('\\','/').lower()

class Assets:
    def __init__(self, output=None):
        self.output=Path(output or ROOT/'cache');self.output.mkdir(parents=True,exist_ok=True)
        self.lock=threading.Lock();self.pvf=None
        index=json.loads((ROOT/'catalog/npk-index.json').read_text('utf8'))
        self.index={}
        for path,rows in index.items():
            candidates=[]
            for row in rows:
                candidate=dict(row);archive=Path(candidate['archive'])
                if archive.is_absolute():archive=archive.relative_to(CLIENT)
                if '..' in archive.parts:raise ValueError('Catalog archive escapes the 1031 client directory')
                candidate['archive']=archive.as_posix()
                candidates.append(candidate)
            self.index[normalized(path)]=candidates
        self.ambiguities={path:rows for path,rows in self.index.items() if len(rows)>1}
        self.decoder_fingerprint=hashlib.sha256((digest(ROOT/'bin/ui_assets.exe')+digest(ROOT.parent/'monster_demo/src/resources.cpp')).encode()).hexdigest()
        self.process=subprocess.Popen([str(ROOT/'bin/ui_assets.exe'),str(CLIENT),str(self.output)],
            stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=(self.output/'helper.stderr.log').open('w'),
            text=True,encoding='utf8',creationflags=subprocess.CREATE_NO_WINDOW)
        self.header=json.loads(self.process.stdout.readline())
        if not self.header.get('ready'):raise RuntimeError(self.header)

    def request(self,q):
        with self.lock:
            self.process.stdin.write(json.dumps(q,ensure_ascii=False)+'\n');self.process.stdin.flush()
            line=self.process.stdout.readline()
            if not line:raise RuntimeError('Native asset helper exited')
            result=json.loads(line)
            if not result.get('ok'):raise ValueError(result.get('error'))
            return result

    def image_candidates(self,path):
        name=normalized(path)
        physical=name if name.startswith('sprite/') else 'sprite/'+name
        return [dict(row,member_sha256=self._member_hash(row)) for row in self.index.get(physical,[])]

    @staticmethod
    def _member_hash(candidate):
        path=(CLIENT/candidate['archive']).resolve();path.relative_to(CLIENT.resolve())
        with path.open('rb') as stream:
            stream.seek(candidate['offset']);member=stream.read(candidate['length'])
        if len(member)!=candidate['length']:raise ValueError('Physical NPK member is truncated: '+candidate['archive'])
        return hashlib.sha256(member).hexdigest()

    def image(self,path,frame,archive=None):
        name=normalized(path);candidates=self.image_candidates(name)
        distinct={row['member_sha256'] for row in candidates}
        if archive is not None:
            archive=normalized(archive)
            selected_rows=[row for row in candidates if normalized(row['archive'])==archive]
            if len(selected_rows)!=1:
                raise ValueError('Physical resource candidate not found: '+json.dumps(dict(path=name,archive=archive,candidates=candidates),ensure_ascii=False))
            candidate=selected_rows[0]
        elif len(candidates)>1 and len(distinct)>1:
            raise ValueError('Resource ambiguity: '+json.dumps(dict(path=name,physical_candidates=candidates),ensure_ascii=False))
        else:
            candidate=sorted(candidates,key=lambda row:normalized(row['archive']))[0] if candidates else None
        selector=normalized(candidate['archive']) if archive is not None and candidate else 'content-equivalent' if len(candidates)>1 else 'unique'
        identity=dict(pvf=PVF_HASH,path=name,frame=int(frame),selector=selector,candidates=candidates,decoder=self.decoder_fingerprint)
        key=hashlib.sha256(json.dumps(identity,sort_keys=True).encode()).hexdigest()
        physical=name if name.startswith('sprite/') else 'sprite/'+name
        if int(frame)<0:raise ValueError('Absent IMG frame: '+str(frame))
        meta=self.output/(key+'.json')
        if meta.exists():
            try:
                result=json.loads(meta.read_text('utf8'))
                if result.get('cache_identity')==identity and self._cache_valid(result,candidate) and Path(result['png']).resolve().parent==self.output.resolve() and Path(result['png']).is_file() and digest(result['png'])==result['png_sha256']:return result
            except (OSError,ValueError,KeyError,TypeError):pass
        query=dict(op='image',path=name,frame=int(frame),key=key)
        if candidate:query['archive']=candidate['archive']
        result=self.request(query)
        if not candidate:raise ValueError('Missing catalog resource; decoded result has no verified physical candidate: '+physical)
        sources=list(result.get('source_reads',{}).values())
        if len(sources)!=1:raise ValueError('Native helper returned incomplete or unrelated resource provenance')
        for read_source in result.get('source_reads',{}).values():
            if Path(read_source['archive']).resolve()!=(CLIENT/candidate['archive']).resolve() or any(read_source[key]!=candidate[key] for key in ('offset','length')):
                raise ValueError('Native helper source differs from the selected catalog member')
            with Path(read_source['archive']).open('rb') as f:
                f.seek(read_source['offset']);member=f.read(read_source['length'])
            read_source['member_sha256']=hashlib.sha256(member).hexdigest()
            if len(member)!=read_source['length'] or read_source['member_sha256']!=candidate['member_sha256']:
                raise ValueError('Physical NPK member changed during decode; retry with stable source')
        resolution=dict(status='unique' if len(candidates)<=1 else 'byte-identical' if len(distinct)==1 else 'explicit-conflict-choice',
            selected_archive=candidate['archive'] if candidate else None,candidates=candidates,native_priority_verified=False)
        result.update(resource=name,frame=int(frame),pvf_sha256=PVF_HASH,png_sha256=digest(result['png']),decoder='monster_demo/src/resources.cpp',decoder_fingerprint=self.decoder_fingerprint,cache_identity=identity,source_resolution=resolution)
        meta.write_text(json.dumps(result,ensure_ascii=False,indent=2),'utf8');return result

    @staticmethod
    def _cache_valid(result,candidate):
        sources=result.get('source_reads',{})
        if not sources or not all(row.get('member_sha256') for row in sources.values()):return False
        if candidate is None:return False
        expected_path=(CLIENT/candidate['archive']).resolve()
        expected=next((row for row in sources.values() if Path(row.get('archive','')).resolve()==expected_path),None)
        if not expected:return False
        if any(expected.get(key)!=candidate[key] for key in ('offset','length')):return False
        try:
            path=(CLIENT/expected['archive']).resolve();path.relative_to(CLIENT.resolve())
            with path.open('rb') as stream:
                stream.seek(expected['offset']);member=stream.read(expected['length'])
            return len(member)==expected['length'] and hashlib.sha256(member).hexdigest()==candidate['member_sha256']==expected['member_sha256']
        except (OSError,KeyError,ValueError):return False

    def close(self):
        if self.pvf:self.pvf.close();self.pvf=None
        if self.process.poll() is None:
            try:self.process.stdin.write('{"op":"quit"}\n');self.process.stdin.flush();self.process.wait(timeout=5)
            except (OSError,subprocess.TimeoutExpired):self.process.terminate();self.process.wait(timeout=5)

    def animation(self,path):
        name=normalized(path)
        result=self.request(dict(op='animation',path=name))
        from pvf_inspect import open_pvf
        if self.pvf is None:self.pvf=open_pvf()
        result['member_sha256']=hashlib.sha256(self.pvf.read(name)).hexdigest()
        result.update(pvf_sha256=PVF_HASH,decoder='monster_demo/src/resources.cpp',
            playback='external preview; loop/state/ACT triggers are not native window state')
        return result

def controls(script):
    """Common counted prefix only; preserve all per-type integer parameters."""
    rows=[];current=None
    for f in script.get('fields',[]):
        tag=f['tag'].lower()
        if tag in ('[parent]','[parent tab]','[parent page]','[parent radio]') and current is not None:
            current.setdefault('parents',[]).append(dict(tag=tag,values=f['values'],offset=f['offset']))
        if tag in ('[string option]','[int option]','[common action]') and current is not None:
            current.setdefault('options',[]).append(dict(tag=tag,values=f['values'],offset=f['offset']))
        if tag=='[/ui controls]':current=None
        if tag!='[ui controls]':continue
        v=f['values'];row=dict(offset=f['offset'],raw=v,decoded=False)
        try:
            kind,name,x,y,n=v[:5]
            if not isinstance(n,int) or not 0<=n<=4096:raise ValueError('string count')
            strings=v[5:5+n];at=5+n;count=v[at]
            if len(strings)!=n or any(not isinstance(x,str) for x in strings):raise ValueError('strings')
            if not isinstance(count,int) or not 0<=count<=4096:raise ValueError('integer count')
            values=v[at+1:at+1+count]
            if len(values)!=count:raise ValueError('integer extent')
            row.update(decoded=True,type=kind,name=name,x=x,y=y,strings=strings,parameters=values,trailing=v[at+1+count:])
        except (ValueError,IndexError,TypeError) as e:row['error']=str(e)
        rows.append(row);current=row
    return rows

def catalog():
    verify_client(True)
    service=Assets(ROOT/'catalog')
    try:report=service.request(dict(op='catalog'))
    finally:service.close()
    scripts=json.loads((ROOT/'catalog/scripts.json').read_text('utf8'));records=[]
    for s in scripts:
        row=dict(path=s['path'],size=s['size'],controls=controls(s),title=None,children=[],images=[],animations=[],
            window_fields=[f for f in s.get('fields',[]) if f['tag'].lower() in ('[tile type]','[size]','[alignment]','[title string]','[window type]')])
        for f in s.get('fields',[]):
            tag=f['tag'].lower()
            if tag=='[title string]':row['title']=f['values']
            if tag=='[ui path]':row['children'].append(dict(offset=f['offset'],values=f['values']))
            for value in f['values']:
                if isinstance(value,str) and value.lower().endswith(('.img','.ani','.act')):
                    key='images' if value.lower().endswith('.img') else 'animations'
                    row[key].append(dict(path=value,field=tag,offset=f['offset']))
        row['empty']=s.get('empty',False);row['error']=s.get('error')
        records.append(row)
    result=dict(exe_sha256=EXE_HASH,pvf_sha256=PVF_HASH,resource_report=report,windows=records,
        limitations=['Common counted control prefix only; parameters remain per-type raw values.',
                      'PVF references alone do not bind a runtime window.',
                      'Title is only the explicit PVF [title string], never arbitrary rendered text.'])
    (ROOT/'catalog/index.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),'utf8')
    print(json.dumps(dict(scripts=len(scripts),errors=[s['path'] for s in scripts if s.get('error')],
        empty=[s['path'] for s in scripts if s.get('empty')],controls=sum(len(x['controls']) for x in records),
        prefix_decoded=sum(c['decoded'] for r in records for c in r['controls']),resource_report=report),ensure_ascii=False))

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('op',choices=['catalog','image']);p.add_argument('path',nargs='?');p.add_argument('frame',nargs='?',type=int,default=0);p.add_argument('--archive',help='explicit physical NPK path relative to the 1031 client directory');a=p.parse_args()
    if a.op=='catalog':catalog()
    else:
        s=Assets()
        try:print(json.dumps(s.image(a.path,a.frame,a.archive),ensure_ascii=False))
        finally:s.close()

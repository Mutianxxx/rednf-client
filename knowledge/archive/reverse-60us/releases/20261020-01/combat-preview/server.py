"""Local, read-only 60US PVF animation and combat investigation preview."""
from __future__ import annotations
import argparse
from functools import lru_cache
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import sys
import threading
from urllib.parse import parse_qs, urlsplit

from catalog import Catalog
from pvf_model import parse_document, node_record
from resources import Assets, ResourceConflict, ResourceError
from controllers import Controllers
from reactions import MonsterRoutes
from casting import CastPhases
from spawned import SpawnedScenes
from scene_objects import SceneObjects
from reaction_motion import ReactionMotion

ROOT=Path(__file__).resolve().parent
WORKSPACE=ROOT.parent


class Preview:
    def __init__(self, client):
        self.client=Path(client).resolve()
        self.catalog=Catalog(self.client/'Script.pvf')
        self.assets=Assets(self.client/'ImagePacks2')
        self.controllers=Controllers(self.catalog,self.client/'DFO_fixed_v3.exe')
        # These are static resource/model contracts. Preserve the actual selected
        # executable identity separately from the original evidence identity.
        evidence_sha256=self.controllers.evidence_sha256
        self.monster_routes=MonsterRoutes(self.catalog,evidence_sha256)
        self.cast_phases=CastPhases(self.catalog,evidence_sha256)
        self.spawned_scenes=SpawnedScenes(self.catalog,evidence_sha256,self.cast_phases)
        self.scene_objects=SceneObjects(self.catalog,evidence_sha256)
        self.reaction_motion=ReactionMotion(evidence_sha256)
        self.lock=threading.RLock()
        self.characters={c['class_id']:c for c in self.catalog.characters}
        self.skills=[dict(class_id=s['class_id'], skill_id=s['skill_id'],path=s['path'],
                          label=Path(s['path']).stem, type=s.get('type_fields',[{}])[0].get('values',[]),
                          name_fields=s.get('name_fields',[]),controller_status=s['controller_status'])
                     for s in self.catalog.skills]
        for compact, full in zip(self.skills, self.catalog.skills):
            for key in ('display_name','secondary_name','name_resolution','name2_resolution','icon_fields'):
                compact[key] = full.get(key)

    @lru_cache(maxsize=192)
    def animation(self, path):
        result=self.catalog.animation(path)
        # A compact, source-bound playback view. Full ordered fields remain available.
        for frame in result['frames']:
            frame['duration_ms']=frame['delays'][0][0] if frame['delays'] else None
        return result

    def script(self, path):
        doc=self.catalog.document(path)
        return dict(path=path,source=self.catalog.identity(path),text=doc.raw.decode('cp949'),
                    fields=[node_record(n) for n in doc.events],warnings=doc.warnings)

    def summary(self):
        summary=self.catalog.summary()
        summary['resource_directory']=str(self.client/'ImagePacks2')
        summary['preview_scope']='PVF资源逐帧预览；技能控制器覆盖以独立合同为准'
        summary['executable_source']=self.controllers.executable_source
        return summary

    def list_paths(self, extension, query='',limit=160):
        paths=(e['path'] for e in self.catalog.pvf.entries
               if e['path'].endswith(extension) and query.lower() in e['path'])
        results=[]
        for path in paths:
            if len(results)>=limit:return dict(paths=results,truncated=True)
            results.append(path)
        return dict(paths=results,truncated=False)


class Handler(BaseHTTPRequestHandler):
    server_version='PVF60Preview/0.1'

    def log_message(self, fmt,*args):
        if args and str(args[1] if len(args)>1 else '') not in ('200','304'):
            super().log_message(fmt,*args)

    def send(self, data, mime='application/json; charset=utf-8', status=200):
        if not isinstance(data,bytes):data=json.dumps(data,ensure_ascii=False).encode('utf-8')
        self.send_response(status)
        self.send_header('Content-Type',mime)
        self.send_header('Content-Length',str(len(data)))
        self.send_header('Cache-Control','no-store')
        self.send_header('X-Content-Type-Options','nosniff')
        self.end_headers()
        self.wfile.write(data)

    def do_GET(self):
        u=urlsplit(self.path)
        q=parse_qs(u.query)
        arg=lambda name,default=None:q.get(name,[default])[0]
        app=self.server.app
        try:
            if u.path=='/api/summary':return self.send(app.summary())
            if u.path=='/api/character':return self.send(app.characters[int(arg('id','0'))])
            if u.path=='/api/skills':
                return self.send([s for s in app.skills if s['class_id']==int(arg('class','0'))])
            if u.path=='/api/scene':return self.send(app.controllers.scene(int(arg('class','0')),int(arg('skill','5')),arg('variant','normal-no-charge'),arg('equipment'),int(arg('level','1'))))
            if u.path=='/api/monster':return self.send(app.controllers.monster_resources(arg('path')))
            if u.path=='/api/monster-route':return self.send(app.monster_routes.route(arg('path'),int(arg('state','3')),int(arg('variant','0'))))
            if u.path=='/api/cast-bindings':return self.send(app.cast_phases.summary())
            if u.path=='/api/cast-phase':return self.send(app.cast_phases.phase(int(arg('class')),int(arg('skill')),int(arg('phase'))))
            if u.path=='/api/spawn-bindings':return self.send(app.spawned_scenes.summary())
            if u.path=='/api/spawn-scene':return self.send(app.spawned_scenes.scene(int(arg('class')),int(arg('skill')),arg('spawn_gate','1')=='1'))
            if u.path=='/api/scene-object-bindings':return self.send(app.scene_objects.summary())
            if u.path=='/api/scene-object':return self.send(app.scene_objects.inspect(int(arg('id','221')),json.loads(arg('events','[]'))))
            if u.path=='/api/reaction-horizontal':return self.send(app.reaction_motion.horizontal(
                kind=int(arg('kind','0')),special_flag=arg('special_flag','0')=='1',
                scale_integer=int(arg('scale_integer','100')),stat218=int(arg('stat218','1000')),
                stat220=float(arg('stat220','1')),motion_enabled=arg('motion_enabled','1')=='1',
                step_delta=int(arg('step_delta','16')),steps=int(arg('steps','40')),direction=int(arg('direction','1'))))
            if u.path=='/api/animation':return self.send(app.animation(arg('path')))
            if u.path=='/api/script':return self.send(app.script(arg('path')))
            if u.path=='/api/paths':return self.send(app.list_paths(arg('ext','.ani'),arg('q','')))
            if u.path=='/api/resource':
                with app.lock:return self.send(app.assets.frames(arg('path'),package=arg('package')))
            if u.path in ('/api/frame','/api/frame-info'):
                with app.lock:
                    result=app.assets.frame(arg('path'),int(arg('index','0')),package=arg('package'))
                if u.path.endswith('-info'):
                    return self.send({k:v for k,v in result.items() if k not in ('png','rgba')})
                return self.send(result['png'],'image/png')
            if u.path=='/api/contracts':
                return self.send(app.controllers.summary())
            if u.path in ('/','/app.js','/geometry.js','/timeline.js','/renderer.js','/style.css'):
                name={'/':'index.html','/app.js':'app.js','/geometry.js':'geometry.js','/timeline.js':'timeline.js','/renderer.js':'renderer.js','/style.css':'style.css'}[u.path]
                mime={'/':'text/html; charset=utf-8','/app.js':'text/javascript; charset=utf-8','/geometry.js':'text/javascript; charset=utf-8','/timeline.js':'text/javascript; charset=utf-8','/renderer.js':'text/javascript; charset=utf-8','/style.css':'text/css; charset=utf-8'}[u.path]
                return self.send((ROOT/'web'/name).read_bytes(),mime)
            self.send({'error':'Not found'},status=404)
        except ResourceConflict as exc:
            self.send(dict(error=str(exc),kind='resource_conflict',logical=exc.logical,
                           candidates=exc.candidates),status=409)
        except (ValueError, KeyError, ResourceError,FileNotFoundError) as exc:
            self.send(dict(error=str(exc),kind=type(exc).__name__),status=422)
        except (BrokenPipeError,ConnectionResetError):pass
        except Exception as exc:
            import traceback
            traceback.print_exc()
            self.send(dict(error=str(exc),kind=type(exc).__name__),status=500)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--client',default=str(WORKSPACE/'DFO'))
    parser.add_argument('--port',type=int,default=8760)
    parser.add_argument('--audit',action='store_true',help='load and verify source catalog, then exit')
    parser.add_argument('--open-browser',action='store_true',help='open the local preview after source loading')
    args=parser.parse_args()
    app=Preview(args.client)
    if args.audit:
        print(json.dumps(app.summary(),ensure_ascii=False,indent=2));return
    server=ThreadingHTTPServer(('127.0.0.1',args.port),Handler)
    server.app=app
    print(f'60US PVF preview: http://127.0.0.1:{args.port}',flush=True)
    if args.open_browser:
        import webbrowser
        threading.Timer(0.3,lambda:webbrowser.open(f'http://127.0.0.1:{args.port}')).start()
    try:server.serve_forever()
    except KeyboardInterrupt:pass
    finally:server.server_close()

if __name__=='__main__':main()

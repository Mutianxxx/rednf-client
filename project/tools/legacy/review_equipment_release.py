"""Audit the packaged equipment/UI build and arrange real capture/reference crops.

This does not launch tests, create gameplay frames, or decide PC pixel parity.
"""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
from PIL import Image, ImageDraw

root=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('ui_run',type=Path)
parser.add_argument('appearance_run',type=Path)
args=parser.parse_args()
args.ui_run=args.ui_run.resolve();args.appearance_run=args.appearance_run.resolve()
out=root/'reports/equipment-ui'

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def read(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))

binary=sha(root/'build/dnf_native.exe')
assert sha(root/'playable/dnf_native.exe')==binary
package=read(root/'playable/manifest.json')
payload=[]
for entry in package['files']:
    actual=sha(root/'playable'/entry['path'])
    assert actual==entry['sha256'],entry['path']
    payload.append({'path':entry['path'],'sha256':actual})
runs=[]
for path in (args.ui_run,args.appearance_run):
    result=read(path/'acceptance.json')
    assert result['status']=='pass' and result['user_saves_unchanged']
    assert result['binary_sha256']==binary
    runtime=[]
    for file in path.rglob('runtime.json'):
        state=read(file)
        assert not state['asset_errors'] and not state['render_errors']
        runtime.append({'path':str(file.relative_to(root)),'output_size':state['output_size'],
                        'render_errors':state['render_errors'],'render_unsupported':state['render_unsupported']})
    runs.append({'path':str(path.relative_to(root)),'acceptance':result,'runtime':runtime,
                 'test_windows':[read(p) for p in path.glob('test-window*.json')]})

sources=[]
index=read(out/'index.json')
for resource in index['resources']:
    for entry in resource['source_entries']:
        with Path(entry['archive']).open('rb') as stream:
            stream.seek(entry['offset']);actual=hashlib.sha256(stream.read(entry['length'])).hexdigest()
        assert actual==entry['stored_entry_sha256']
        sources.append({'image':resource['path'],'entry_sha256':actual})
source=read(root/'reports/appearance-source/manifest.json')['source_archive']
assert sha(Path(source['path']))==source['sha256']
for reference in index['references']:
    assert sha(Path(reference['source']))==reference['sha256']

comparisons=[]
for label,reference,capture in (
    ('equipment','装备栏样式参考.png','03-inventory.png'),
    ('avatar','装扮ui界面参考.png','04c-avatar.png'),
):
    ref=Image.open(root.parent/'pc版本dnf截图'/reference).convert('RGB').resize((800,600),Image.Resampling.NEAREST)
    current=Image.open(args.ui_run/capture).convert('RGB')
    assert current.size==(800,600)
    box=(450,70,730,542)
    canvas=Image.new('RGB',(560,512),(24,25,28));draw=ImageDraw.Draw(canvas)
    draw.text((6,7),'USER PC REFERENCE (normalized)',fill='white')
    draw.text((286,7),'ACTUAL SDL CAPTURE',fill='white')
    canvas.paste(ref.crop(box),(0,32));canvas.paste(current.crop(box),(280,32))
    file=out/(label+'-actual-comparison.png');canvas.save(file)
    comparisons.append({'file':str(file.relative_to(root)), 'reference':reference,
                        'actual_capture':str((args.ui_run/capture).relative_to(root)),
                        'crop_800':list(box),'actual_capture_sha256':sha(args.ui_run/capture),
                        'scope':'Arrangement of source screenshot and real SDL crop. Character/items/scene differ; no synthetic gameplay or pixel-parity score.'})
report={'recorded_utc':datetime.now(timezone.utc).isoformat(),'binary_sha256':binary,'package_files':payload,
        'core_status':read(root/'reports/core-tests.json')['status'],
        'core_check_labels':len(read(root/'reports/core-tests.json')['checks']),
        'appearance_checks':len(read(root/'reports/appearance-tests.json')['checks']),
        'source_pvf_unchanged':source,'source_ui_entries_unchanged':sources,'runs':runs,'comparisons':comparisons,
        'PC_pixel_parity':False,
        'review':'Original narrow inventory/avatar art and title stack implemented. Owned outfit changes propagate to preview/world/selection/reload. Seven-item fitting stays outside persistent equipment.',
        'pending':['Exact anchors/tab widths/complete tooltip fields and drag interactions',
                   'Carried-weight scale; current source gauge background only',
                   'Unconfirmed native body layer number; reconstructed 1000',
                   'Complete cosmetic special controllers, aura/masks/weapon-avatar combinations',
                   'Creation, quests, NPC/shop and other complete original UI layouts']}
(out/'verification.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'binary_sha256':binary,'runs':[r['path'] for r in runs],'source_ui_entries':len(sources),
                  'core_check_labels':report['core_check_labels'],'PC_pixel_parity':False},indent=2))

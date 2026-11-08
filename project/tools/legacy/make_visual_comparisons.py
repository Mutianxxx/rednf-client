"""Arrange preserved PC references and actual SDL captures; no synthesized gameplay."""
from pathlib import Path
import hashlib
import json
from PIL import Image, ImageDraw

root = Path(__file__).resolve().parents[1]
out = root/'reports/visual-correction/comparisons'
out.mkdir(parents=True, exist_ok=True)
research = root/'reports/visual-correction/research'
old = root/'reports/runs/input-20261017T110701'
current = root/'reports/runs/input-20261017T122331'
groups = {
    'room': [('PC reference, normalized 800x600', research/'ref-room-800.png'),
             ('Old actual SDL, 110701', old/'02-room.png'),
             ('Current actual SDL, 122331', current/'02-room.png')],
    'town': [('PC reference; camera/player differ', research/'ref-town-800.png'),
             ('Old actual SDL, 110701', old/'04-town.png'),
             ('Current actual SDL, 122331', current/'04-town.png')],
    'ground-camera': [('Old Y-follow: exposed tile bottom, 115917',
                       root/'reports/runs/input-20261017T115917/06-room-0.png'),
                      ('Current fixed Y: actual same spawn, 122331', current/'06-room-0.png')],
    'select': [('PC reference, normalized 800x600', research/'ref-select-800.png'),
               ('Current actual SDL; private empty 20-slot save', root/'reports/visual-correction/select-current.png')],
}
manifest = {'scope': 'Side-by-side reference/actual screenshots. Labels and arrangement only; '
                     'different characters, camera positions, animation time and unavailable UI remain. '
                     'No whole-client visual acceptance.', 'groups': []}
for name, columns in groups.items():
    sheet = Image.new('RGB', (800*len(columns), 646), (19, 22, 28))
    draw = ImageDraw.Draw(sheet)
    sources = []
    for index, (label, path) in enumerate(columns):
        frame = Image.open(path).convert('RGB')
        if frame.size != (800, 600):
            raise ValueError(f'Unexpected comparison size: {path}: {frame.size}')
        sheet.paste(frame, (index*800, 28))
        draw.text((index*800+8, 8), label, fill='white')
        sources.append({'label': label, 'path': str(path.relative_to(root)),
                        'sha256': hashlib.sha256(path.read_bytes()).hexdigest()})
    draw.text((8, 632), 'Preserved pixels, arranged only. See manifest.json for original paths/hashes and scope.', fill='white')
    target = out/(name+'.png')
    sheet.save(target)
    manifest['groups'].append({'comparison': target.name, 'sources': sources})
(out/'manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf-8')
print(json.dumps({'comparisons': len(groups), 'directory': str(out.relative_to(root))}))

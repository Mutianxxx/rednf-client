"""Arrange actual SDL capture crops for review; never synthesize gameplay frames."""
from pathlib import Path
import argparse
import json
from PIL import Image, ImageDraw

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('report_directory', type=Path)
args = parser.parse_args()
report = args.report_directory.resolve()
out = report/'review'
out.mkdir(exist_ok=True)
skills = ('upperslash','hardattack','tripleslash','dashattackmultihit','ashenfork',
          'jumpattackmulti','normalwave','khazan','vaneslash','gorecross','hopsmash','moonlightslash','guard')
times = (.10,.30,.65,1.10,1.60,2.40,3.50)
rows = []
for index, name in enumerate(skills):
    sheet = Image.new('RGB',(7*400,2*264+32),(20,22,28))
    draw = ImageDraw.Draw(sheet)
    draw.text((8,8),f'{index}: {name} | actual SDL framebuffer crops | right, left',fill='white')
    originals = []
    for direction in range(2):
        stamp = index+13*direction
        for phase, seconds in enumerate(times):
            source = report/'captures'/f'skill-{index}-{stamp}-phase-{phase}.png'
            if not source.exists(): raise FileNotFoundError(source)
            frame = Image.open(source).convert('RGB')
            if frame.size != (800,600):
                raise ValueError('Skill review expects 800x600 capture: '+str(source))
            # Keep the player/effect area; only arrange and resize existing pixels.
            crop = frame.crop((0,80,800,560)).resize((400,240))
            x=phase*400;y=32+direction*264
            sheet.paste(crop,(x,y+24))
            draw.text((x+4,y+4),f'{"right" if direction==0 else "left"} +{seconds:.2f}s',fill='white')
            originals.append(str(source.relative_to(report)))
    target=out/f'{index:02d}-{name}.png'
    sheet.save(target)
    rows.append({'skill':name,'sheet':str(target.relative_to(report)), 'captures':originals})
(out/'index.json').write_text(json.dumps({'scope':'Crops/resizes of actual SDL captures, for visual review; no PC fidelity claim',
                                         'skills':rows},indent=2),encoding='utf-8')
print(json.dumps({'sheets':len(rows),'captures':sum(len(x['captures']) for x in rows)}))

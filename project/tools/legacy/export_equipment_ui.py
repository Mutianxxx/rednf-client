"""Export original PC inventory IMG frames and labelled diagnostic contact sheets.

Requires dnf_inspect built with --export-frames. Source files stay read-only.
These are decoded asset previews, never actual gameplay captures.
"""
from pathlib import Path
import argparse
import hashlib
import json
import math
import subprocess
from PIL import Image, ImageDraw


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def sheet(directory, manifest):
    # Keep every cropped frame at source pixel size, up to 400x580 cells;
    # oversize images have their exact scale recorded in the sheet caption.
    frames = manifest['frames']
    pages = []
    for start in range(0, len(frames), 24):
        page_frames = frames[start:start+24]
        cell_w = max(164, min(400, max((f['width'] for f in page_frames), default=0)+12))
        cell_h = max(102, min(580, max((f['height'] for f in page_frames), default=0)+52))
        columns = min(6, max(1, 1440//cell_w))
        rows = math.ceil(len(page_frames)/columns)
        image = Image.new('RGB', (columns*cell_w, rows*cell_h+28), (29,31,35))
        draw = ImageDraw.Draw(image)
        draw.text((6,8), manifest['path'] + ' | original IMG previews; no gameplay capture', fill='white')
        for n, frame in enumerate(page_frames):
            x = (n % columns)*cell_w
            y = (n // columns)*cell_h+28
            draw.rectangle((x,y,x+cell_w-1,y+cell_h-1), outline=(75,75,75))
            draw.text((x+5,y+4), f"#{frame['frame']} crop {frame['width']}x{frame['height']} @ {frame['x']},{frame['y']}", fill=(255,226,151))
            draw.text((x+5,y+18), f"logical {frame['logical_width']}x{frame['logical_height']}", fill='white')
            if frame['png']:
                original = Image.open(directory/frame['png']).convert('RGBA')
                scale = min(1., (cell_w-12)/max(1,original.width), (cell_h-46)/max(1,original.height))
                if scale < 1:
                    original = original.resize((max(1,round(original.width*scale)),max(1,round(original.height*scale))),Image.Resampling.NEAREST)
                    draw.text((x+5,y+32),f'sheet scale {scale:.3f}',fill=(180,180,180))
                image.paste(original,(x+6,y+44),original)
        file=directory/f"sheet-{start:04d}.png"
        image.save(file)
        pages.append(file.name)
    return pages


def main():
    base=Path(__file__).resolve().parents[1]
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--client',type=Path,default=base.parent/'DNF1031客户端')
    parser.add_argument('--inspect',type=Path,default=base/'build/dnf_inspect.exe')
    parser.add_argument('--output',type=Path,default=base/'reports/equipment-ui')
    parser.add_argument('--sheets-only',action='store_true')
    args=parser.parse_args()
    resources=[
        'interface/iteminventorywindow.img',
        'interface/newiteminventory.img',
        'interface/newstyle/windows/inventory/inventory.img',
        'interface/newstyle/windows/inventory/inventory_tw.img',
        'interface/avatar_iconslot.img',
        'interface/itemtoolwindow.img',
        'interface/newstyle/windows/itemtool_window4.img',
        'interface/windowcommon.img',
        'interface2/window_title_accessory/window_title_accessory.img',
        'interface2/itemtoolwindow/windows4/itemtool_window4.img',
    ]
    args.output.mkdir(parents=True,exist_ok=True)
    index={'scope':'Original PC decoded asset previews; not gameplay captures or visual parity acceptance',
           'inspector_sha256_at_report_generation':sha256(args.inspect),
           'inspector_note':'--sheets-only does not re-export pixels; this hash identifies the executable present at report generation',
           'resources':[],'references':[]}
    for resource in resources:
        directory=args.output/resource.replace('/','__').removesuffix('.img')
        if not args.sheets_only:
            subprocess.run([str(args.inspect),str(args.client),'--export-frames',resource,'unused',str(directory)],check=True)
        manifest=json.loads((directory/'manifest.json').read_text(encoding='utf-8'))
        source_data=[]
        for read in manifest.get('resource_reads',{}).values():
            archive=Path(read['archive'])
            with archive.open('rb') as handle:
                handle.seek(read['offset'])
                raw=handle.read(read['length'])
            source_data.append({**read,'stored_entry_sha256':hashlib.sha256(raw).hexdigest(),
                                'note':'SHA256 of original NPK entry byte range; source archive opened read-only'})
        index['resources'].append({'path':resource,'directory':directory.relative_to(args.output).as_posix(),
                                   'frame_count':manifest['frame_count'],'source_entries':source_data,
                                   'sheets':sheet(directory,manifest)})
    for name in ['装备栏样式参考.png','装扮ui界面参考.png','装备选中后对比参考.png']:
        source=base.parent/'pc版本dnf截图'/name
        im=Image.open(source)
        target=args.output/('reference-'+name)
        im.resize((800,600),Image.Resampling.NEAREST).save(target)
        index['references'].append({'source':str(source),'sha256':sha256(source),'source_size':list(im.size),
                                    'normalized_size':[800,600],'normalized_png':target.name,
                                    'note':'Normalized only to measure original 800x600 logical layout; source screenshot retained read-only'})
    (args.output/'index.json').write_text(json.dumps(index,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(index,ensure_ascii=False,indent=2))


if __name__=='__main__':
    main()

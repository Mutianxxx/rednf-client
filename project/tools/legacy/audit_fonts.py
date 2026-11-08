"""Read-only inventory of the original client fonts and the user's references.

Uses fontTools to inspect names/cmap, not filenames as font identities. Legacy
Korean name records may be invalid Unicode; keep their bytes and decode errors.
Does not install fonts, copy font files, or modify the reference client.
"""
from pathlib import Path
import hashlib
import json
import argparse
import subprocess
from fontTools.ttLib import TTFont

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--client', type=Path, default=ROOT.parent / 'DNF1031客户端')
parser.add_argument('--output', type=Path, default=ROOT / 'reports/font-reference/source-audit.json')
args = parser.parse_args()
sample = '赛丽亚·克鲁敏 冒险家，请打开技能栏，试着学习一下技能吧 任务完成。'


def source(path):
    raw = path.read_bytes()
    return {'path': str(path.resolve()), 'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()}


fonts = []
for path in sorted((args.client / 'Fonts').rglob('*')):
    if not path.is_file() or path.suffix.lower() not in ('.ttf', '.ttc', '.otf', '.fon', '.fnt'):
        continue
    entry = source(path)
    with TTFont(path, lazy=False) as face:
        names = []
        for record in face['name'].names:
            if record.nameID not in (1, 2, 4, 6):
                continue
            name = {'id': record.nameID, 'platform': record.platformID,
                    'encoding': record.platEncID, 'language': record.langID,
                    'raw_hex': record.string.hex()}
            try:
                name['text'] = record.toUnicode()
            except (UnicodeError, LookupError) as error:
                name['decode_error'] = str(error)
            names.append(name)
        cmap = face.getBestCmap() or {}
        entry.update(names=names, unicode_codepoints=len(cmap),
                     missing_sample=sorted({c for c in sample if ord(c) not in cmap}),
                     cmap_tables=[{'platform': table.platformID, 'encoding': table.platEncID,
                                   'format': table.format, 'entries': len(table.cmap)}
                                  for table in face['cmap'].tables],
                     glyphs=len(face.getGlyphOrder()), units_per_em=face['head'].unitsPerEm,
                     ascent=face['hhea'].ascent, descent=face['hhea'].descent,
                     tables=sorted(face.keys()))
    fonts.append(entry)

references = [source(p) for p in sorted((ROOT.parent / 'pc版本dnf截图' / '字体参考截图').glob('*.png'))]
npk_probe = None
inspector = ROOT / 'build/dnf_inspect.exe'
if inspector.exists():
    probe = subprocess.run([str(inspector), str(args.client), '--npk-paths', 'font'],
                           capture_output=True, encoding='utf-8', check=True)
    npk_probe = {'query': '--npk-paths font', 'paths': json.loads(probe.stdout),
                 'scope': 'Image archive path names containing font; not a search inside executable bytes.'}
report = {'fonts': fonts, 'references': references, 'sample': sample,
          'npk_probe': npk_probe,
          'conclusion': 'Fonts/msjh.ttf internally identifies as FangSong/仿宋 and covers the sample. '
                        'Gasinamu has a legacy Wansung cmap, with no Unicode cmap. '
                        'Bundling proves availability, not which font the original executable selects. '
                        'The outline and rasterizer are reconstructed; pixel parity is not established.'}
args.output.parent.mkdir(parents=True, exist_ok=True)
args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
print(json.dumps({'report': str(args.output), 'fonts': len(fonts), 'reference_images': len(references)}, ensure_ascii=False))

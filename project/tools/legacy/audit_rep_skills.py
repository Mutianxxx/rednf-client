"""Inspect current PC REP skill associations; no native playback claim.

Only imports the PC PVF reader, never historical game implementation/assets.
Writes research evidence, not runtime content or game state.
"""
from __future__ import annotations

import argparse
import collections
import csv
import datetime
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / 'dnf-result' / 'tools'))
from pvf_reader import Pvf, ScriptDecoder, normalized  # noqa: E402


def chunks(values, width):
    return [values[i:i + width] for i in range(0, len(values), width)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pvf', type=Path, default=ROOT.parent / 'DNF1031客户端/Script.pvf')
    parser.add_argument('--output', type=Path, default=ROOT / 'reports/rep-reference/skill-map')
    args = parser.parse_args()
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    pvf = Pvf(args.pvf)
    decoder = ScriptDecoder(pvf)
    skill_cache, job_lists = {}, {}
    issues, references, rows = [], collections.defaultdict(list), []
    stats = collections.Counter({
        'rep_files': 0, 'skill_key_records': 0,
        'unmapped_slot_records': 0, 'unresolved_skill_name_records': 0,
        'files_with_multiple_shortcut_skill_ids': 0,
        'files_with_zero_skill_key_records': 0,
    })

    def skill(job, local_id):
        key = (job, local_id)
        if key in skill_cache:
            return skill_cache[key]
        list_path = f'skill/{job}skill.lst'
        if job not in job_lists:
            job_lists[job] = {
                r['id']: normalized('skill/' + r['value'])
                for r in decoder.list_records(list_path)
            }
        target = job_lists[job].get(local_id)
        result = {'job': job, 'local_skill_id': local_id, 'list_path': list_path,
                  'skill_path': target, 'name': None}
        if target in pvf.by_name:
            model = decoder.script(target)
            names = [v for f in model['fields'] if f['tag'] == '[name]' for v in f['values']]
            result.update(name=names[0] if names else None, sha256=model['sha256'])
        skill_cache[key] = result
        return result

    # Direct reverse references only: a _new or linksystem file is not silently
    # assigned the configuration of a similarly named practice file.
    for path in sorted(pvf.by_name):
        if not (path.startswith('etc/pvppracticecombo/') and path.endswith('.etc')):
            continue
        job = Path(path).stem
        current = None
        for field in decoder.script(path)['fields']:
            if field['tag'] == '[combo]':
                current = {'config_path': path, 'combo_header': field['values'],
                           'combo_offset': field['offset'], 'replays': [], 'tip_raw': []}
            elif current is not None and field['tag'] == '[replay]':
                current['replays'].extend(field['values'])
            elif current is not None and field['tag'] == '[tip]':
                current['tip_raw'] = field['values']
                values = field['values']
                current['tip_skill_candidates'] = []
                if values and (len(values) - 1) % 3 == 0:
                    for item in chunks(values[1:], 3):
                        current['tip_skill_candidates'].append({'raw': item, 'skill': skill(job, item[0])})
                else:
                    issues.append({'path': path, 'offset': field['offset'], 'kind': 'unhandled-tip-shape'})
            elif current is not None and field['tag'] == '[/combo]':
                for replay in current['replays']:
                    references[normalized('etc/pvppracticecombo/' + replay)].append(current.copy())
                current = None

    model_path = out / 'records.jsonl'
    with model_path.open('w', encoding='utf-8', newline='\n') as evidence:
        for path in sorted(p for p in pvf.by_name if p.endswith('.rep')):
            job = path.split('/')[-2]
            model = decoder.script(path)
            fields = {f['tag']: f['values'] for f in model['fields']}
            stats['rep_files'] += 1
            slots = {}
            for tag in ('[quick skill]', '[quick skill expend]'):
                values = fields[tag]
                if len(values) % 4:
                    issues.append({'path': path, 'tag': tag, 'kind': 'slot-width'})
                    continue
                for record in chunks(values, 4):
                    if record[0] in slots:
                        issues.append({'path': path, 'slot': record[0], 'kind': 'duplicate-slot'})
                    slots[record[0]] = {'section': tag, 'raw': record,
                                       'skill': skill(job, record[1])}
            for tag, width in (('[normal key]', 12), ('[skill key]', 8), ('[down key]', 3)):
                values = fields[tag]
                if not values or len(values) != 1 + values[0] * width:
                    issues.append({'path': path, 'tag': tag, 'kind': 'event-count-or-width'})
            events = []
            values = fields['[skill key]']
            for ordinal, record in enumerate(chunks(values[1:], 8)):
                binding = slots.get(record[1])
                event = {'ordinal': ordinal, 'raw': record, 'slot_code': record[1],
                         'binding': binding, 'semantics': 'shortcut-input candidate; native execution unverified'}
                events.append(event)
                stats['skill_key_records'] += 1
                if binding is None:
                    stats['unmapped_slot_records'] += 1
                elif not binding['skill']['name']:
                    stats['unresolved_skill_name_records'] += 1
            ids = sorted({event['binding']['skill']['local_skill_id']
                          for event in events if event['binding']})
            if len(ids) > 1:
                stats['files_with_multiple_shortcut_skill_ids'] += 1
            if not events:
                stats['files_with_zero_skill_key_records'] += 1
            raw = pvf.read(path)
            raw_path = out / 'raw' / path
            raw_path.parent.mkdir(parents=True, exist_ok=True)
            raw_path.write_bytes(raw)
            record = {'path': path, 'archive_entry': pvf.by_name[path], 'sha256': model['sha256'],
                      'raw_file': raw_path.relative_to(out).as_posix(), 'original_fields': model['fields'],
                      'skill_key_candidates': events, 'direct_combo_config_references': references[path]}
            evidence.write(json.dumps(record, ensure_ascii=False, allow_nan=False) + '\n')
            labels = [f"{event['binding']['skill']['local_skill_id']}:{event['binding']['skill']['name']}"
                      if event['binding'] else f"unresolved-slot:{event['slot_code']}" for event in events]
            tips = []
            for ref in references[path]:
                parts = [str(item['skill']['name'] or ('未解析代码' + str(item['raw'][0])))
                         for item in ref.get('tip_skill_candidates', [])]
                tips.append(str(ref['combo_header'][1]) + ': ' + ' → '.join(parts))
            rows.append([path, job, len(events), ' → '.join(labels), ';'.join(map(str, ids)),
                         ' | '.join(tips), '无快捷技能记录不等于未释放技能' if not events else '输入记录不等于成功释放'])

    with (out / 'rep-skill-associations.csv').open('w', encoding='utf-8-sig', newline='') as csv_file:
        writer = csv.writer(csv_file)
        writer.writerow(['REP路径', '职业目录', '快捷技能记录数', '快捷技能关联候选_按记录次序',
                         '候选技能ID去重', '直接引用配置中的连招提示', '解释边界'])
        writer.writerows(rows)
    with args.pvf.open('rb') as source:
        digest = hashlib.file_digest(source, 'sha256').hexdigest()
    summary = {'created_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
               'source_pvf': str(args.pvf.resolve()), 'source_pvf_sha256': digest,
               'stats': dict(stats), 'issues': issues,
               'zero_skill_key_paths': [r[0] for r in rows if r[2] == 0],
               'scope': 'File/field/registration associations only; no playback or skill success validation.',
               'rules': ['Observed four-value quick skill and quick skill expend records.',
                         'Observed skill key count followed by eight-value records; record[1] matches slot code.',
                         'Resolve bound ID using this job skill.lst and SKL [name].',
                         'Preserve normal key/down key raw fields; do not infer execution from their names.',
                         'Tip skill candidates follow observed three-value groups; unresolved codes remain unresolved.',
                         'Record[0] timing unit and scheduler are unverified; no unit conversion.']}
    (out / 'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    pvf.close()
    print(json.dumps(summary, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()

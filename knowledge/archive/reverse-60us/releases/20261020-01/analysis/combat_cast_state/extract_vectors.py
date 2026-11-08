"""Extract append order on the 18 already proven local state-10 request paths.

The result is a narrow symbolic expression ledger, not an x86 emulator. All
unknown inputs and call return values remain symbolic, and no runtime is run.
"""
from pathlib import Path
import re, json, hashlib
import static_scan as s

ROOT = Path(__file__).resolve().parent
PREVIOUS = ROOT.parent / 'combat_skill_dispatch' / 'local-dispatch-paths.json'
rows = json.loads(PREVIOUS.read_text(encoding='utf-8'))['paths']
seeds = {
    'Swordman': {'ebx': 0},
    'Fighter': {'edi': 0},
    'Gunner_variants_2_5': {'edi': 0},
}

def parse_literal(v):
    try:
        return int(v, 0)
    except ValueError:
        return None

result = []
for path in rows:
    if path['state'] != 10:
        continue
    registers = dict(seeds[path['native_class']])
    origins, memory, stack, appends = {}, {}, [], []
    def value(text):
        literal = parse_literal(text)
        return literal if literal is not None else registers.get(text, text)
    for line in path['path_asm'].splitlines():
        parts = line.split(None, 3)
        va, opcode, mnemonic = parts[:3]
        operand_text = parts[3] if len(parts) > 3 else ''
        operands = operand_text.split(', ')
        if mnemonic == 'mov' and len(operands) == 2:
            dst, src = operands
            item = {'expression': value(src), 'write_va': '0x' + va.lower(), 'source_operand': src}
            if src in origins:
                item['source_origin'] = origins[src]
            if dst.startswith('dword ptr [ebp'):
                memory[dst.removeprefix('dword ptr ')] = item
            elif re.fullmatch('e[a-z]{2}', dst):
                registers[dst] = item['expression']
                origins[dst] = item
        elif mnemonic == 'lea' and len(operands) == 2:
            registers[operands[0]] = {'address_of': operands[1]}
            origins.pop(operands[0], None)
        elif mnemonic == 'push':
            stack.append(value(operand_text))
        elif mnemonic == 'call':
            if operand_text == '0x407120':
                pointer = stack[-1] if stack else None
                name = pointer.get('address_of') if isinstance(pointer, dict) else None
                appends.append({'index': len(appends), 'append_va': '0x' + va.lower(), 'temporary': name, **memory.get(name, {'expression': 'unknown'})})
            registers['eax'] = {'return_from': operand_text, 'call_va': '0x' + va.lower()}
            origins['eax'] = {'call_va': '0x' + va.lower(), 'target': operand_text}
            for reg in ['ecx', 'edx']:
                registers.pop(reg, None)
                origins.pop(reg, None)
            stack.clear()
        elif mnemonic in ['sub', 'add', 'sar', 'shr', 'imul', 'and', 'or'] and len(operands) == 2:
            dst, src = operands
            if re.fullmatch('e[a-z]{2}', dst):
                a, b = value(dst), value(src)
                if isinstance(a, int) and isinstance(b, int):
                    if mnemonic == 'sub': v = a-b
                    elif mnemonic == 'add': v = a+b
                    elif mnemonic == 'sar': v = a>>b
                    elif mnemonic == 'shr': v = (a&0xffffffff)>>b
                    elif mnemonic == 'and': v = a&b
                    elif mnemonic == 'or': v = a|b
                    else: v = a*b
                else:
                    v = {'operation': mnemonic, 'left': a, 'right': b, 'va': '0x' + va.lower()}
                registers[dst] = v
                origins.pop(dst, None)
        elif mnemonic == 'cdq':
            registers['edx'] = {'sign_extension_of': value('eax')}
        elif mnemonic == 'xor' and len(operands) == 2 and operands[0] == operands[1]:
            registers[operands[0]] = 0
    assert appends and appends[2]['expression'] == path['skill_id'], (path['native_class'], path['skill_id'])
    assert appends[0]['expression'] == appends[1]['expression'] == 0
    assert isinstance(appends[5]['expression'], int)
    result.append({
        'native_class': path['native_class'], 'skill_id': path['skill_id'],
        'request_call_va': path['request_call_va'], 'consume_call_va': path['consume_call_va'],
        'rea_body_evidence_id': path['rea_body_evidence_id'],
        'previous_path_bytes_sha256': path['path_bytes_sha256'],
        'previous_path_start_va': path['path_bytes_start_va'],
        'previous_path_length': path['path_bytes_length'],
        'append_count': len(appends), 'phase': appends[0]['expression'],
        'mode': appends[1]['expression'], 'casting_animation_index': appends[5]['expression'],
        'release_animation_index': appends[5]['expression'],
        'append_values': appends,
        'register_seed_assumption': seeds[path['native_class']],
        'boundary': 'Proven local request success path only. Upstream input/job/state guards are not fully recovered. Symbolic call returns are not evaluated; no runtime execution.'
    })

document = {
    'source': str(s.SOURCE), 'source_sha256': hashlib.sha256(s.RAW).hexdigest(),
    'previous_ledger': str(PREVIOUS), 'previous_ledger_sha256': hashlib.sha256(PREVIOUS.read_bytes()).hexdigest(),
    'method': 'Read existing local paths in append order; preserve nonliteral return expressions. Assumes normal MSVC x86 nonvolatile-register ABI. Seed zero registers must be checked separately against saved disassembly.',
    'count': len(result), 'paths': result, 'observed_execution': False,
}
(ROOT / 'state10-request-vectors.json').write_text(json.dumps(document, ensure_ascii=False, indent=2), encoding='utf-8')
for row in result:
    print(row['native_class'], row['skill_id'], row['append_count'], row['casting_animation_index'])

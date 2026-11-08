"""Generate precise per-skill and source navigation indexes for this package."""
from pathlib import Path
import json

def create(root):
    load=lambda p:json.loads(p.read_text('utf8'))
    b=load(root/'demo/content/battle.json');caps=load(root/'validation/upstream/capabilities.json')
    lines=['# 逐技能实现与依据','',
        '每项链接分别对应运行规格、实机观察和源文件；表中时间表为当前重建结果。调用链缺口不得用校准时间表替代。','',
        '| 技能 / key / 键 | 当前身体阶段 / 效果实例 | 实机创建ID | 实现依据与推导 |',
        '| --- | --- | --- | --- |']
    notes={
        'hopsmash':'帧4、20050与(123,1,0)、Front/Back层有源/调用依据；水平参数27→90；高度68/抛物线为推导。',
        'gorecross':'20028与(85,0,82)，单次分支；不执行仅构造而未绘制的追加分支。',
        'bloodblast':'20122/20120/20121，source图+实际绘制时序；身体用CHR buff motion演示回退。',
        'bloodblastex':'20103/20102/20104，保留结束动画实绘时序，固定持续；CHR身体回退；失效ALS引用保留。',
        'bloodsword':'20066绝对XYZ、Z60；狂暴前置实测；SKL static[2]前冲为推导。',
        'bloodboom':'38002相对(0,0,70)，多层爆炸实际绘制；负帧事件不改0帧；身体对齐有推导。',
        'outragebreak':'20043相对(150,0,0)，20044世界直建；94实例不去重；未解轨迹采用投影锚点。',
        'frenzy':'cast/blast/endofcasting/buff实绘，持久绘制与停止分开；10秒关闭限制为用户实测。'}
    for s in b['skills']:
        e=load(root/f"evidence/skill-chain-analysis/skills/{s['key']}.json")
        ids=sorted({c['object_id'] for p in e['phase_observations'] for c in p['spawn_chains'] if c['call_chain_verified']})
        lines.append(f"| [{s['name']}](../evidence/skill-chain-analysis/skills/{s['key']}.json) / `{s['key']}` / {s['hotkey']} | {len(s['body'])} / {len(s['effects'])} | {', '.join(map(str,ids)) or '无新增创建证明'} | {notes[s['key']]} |")
    lines+=['','## 逐技能机器索引','',
        '[skills-index.json](skills-index.json)汇总当前身体、时长、效果实例、source、basis和源证据节点。完整运行数据在 [battle.json](../demo/content/battle.json)，原事件观察在对应技能JSON。', '',
        '其他主动技能的覆盖状态与分类依据见 [capabilities.json](../validation/upstream/capabilities.json)。目录源规则参考 [build_catalog.py](../reference/catalog-rules/build_catalog.py)，固定结果在 [skills.json](../demo/content/skills.json)。','',
        f"状态统计：`{json.dumps(caps['status_counts'],ensure_ascii=False)}`。",'',
        '八技能合计179效果实例。嗜魂封魔斩按用户反馈排除，其采集报告留存但不用于正常技能推导。']
    (root/'docs/SKILLS.md').write_text('\n'.join(lines)+'\n',encoding='utf8')
    rows=[]
    for s in b['skills']:
        e=load(root/f"evidence/skill-chain-analysis/skills/{s['key']}.json")
        rows.append(dict(key=s['key'],name=s['name'],hotkey=s['hotkey'],body=s['body'],duration=s['duration'],effect_instances=len(s['effects']),
            controller_complete=False,implementation_note=notes[s['key']],skill_source=s['skill_source'],skill_raw_sha256=s['skill_raw_sha256'],
            raw_source_archive=f"../evidence/skill-chain-analysis/sources/{s['skill_raw_sha256']}.bin",
            source_fields=f"../evidence/skill-chain-analysis/sources/{s['skill_raw_sha256']}.json",
            observations=f"../evidence/skill-chain-analysis/skills/{s['key']}.json",
            effects=[dict(index=i,**fx) for i,fx in enumerate(s['effects'])]))
    (root/'docs/skills-index.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2),encoding='utf8')
    entries={
        'demo/src/main.cpp':['struct Motion','struct Cast','struct Monster','struct Battle','void addAls','void startSpec','Json inferred','void selectedSkill','void attack','bool acceptedHit','void collision','void step','void body','void drawMonster','void drawPlayer','void draw()','void event','static int verify','static int run'],
        'demo/src/canvas.hpp':['Texture& texture','void sprite','void animation'],
        'demo/src/resources.cpp':['Pvf::Pvf','Animation decodeAni','Assets::Assets','Assets::blob','Assets::pixels'],
        'demo/include/dnf/shared_death.hpp':['struct DeathProfile','deathParticles','deathPosition'],
        'demo/tools/prepare.py':['def tracks','def act_tracks','for key,hotkey','projection_only=True'],
        'derivation/lib/prepare_content.py':['def script','def animation']}
    table=['# 源码导航','','文件内检索以下符号即可定位。行号绑定本包源码；修改后应重新生成。','', '| 符号 | 文件与行号 |','| --- | --- |']
    for name,needles in entries.items():
        source=(root/name).read_text('utf8').splitlines()
        for needle in needles:
            found=next((i for i,t in enumerate(source,1) if needle in t),None)
            if found is None:raise ValueError('Missing source symbol '+needle)
            table.append(f'| `{needle}` | [{name}:{found}](../{name}#L{found}) |')
    table+=['','上游原版在 `reference/upstream`；唯一C++便携改动为 `run()` 的资源/身份入口，见 `reference/portable-startup.patch`。', '',
        '资源准备改为包内原始成员与证据路径，构建改为包内SDK和外置可指定编译器；战斗、渲染和验收函数未修改。']
    (root/'docs/CODE_INDEX.md').write_text('\n'.join(table)+'\n',encoding='utf8')

if __name__=='__main__':create(Path(__file__).resolve().parents[1])

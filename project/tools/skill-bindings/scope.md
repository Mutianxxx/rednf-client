# Case Scope

## meta
- case_id: dnf1031-skill-binding-extract
- created: 2026-11-03T23:53:53.2587879+08:00
- operator: local
- project_root: D:\dnf-rebuild
- primary_skill: reverse-engineering/SKILL.md
- primary_id: R0
- lead_role: lead
- specialist_roles: []
- hint: 
- preset: offline-sample

## auth
- status: granted
- basis: own_system
- evidence_of_auth: preset:offline-sample (owner-operated local file)
- MUST NOT proceed if status != granted

## in_scope
- assets:
  - D:\game\DNF1031客户端-20260708\DNF1031客户端\DNF.exe（用户自有客户端，本机运行）
  - 客户端 plugins\ 目录（ijl15 既有加载链路）
  - 运行期进程内存（self-process 只读取证）
- surfaces: [in-process memory read, plugin dll load, launcher gui start]
- activities: [memory dump of self process, static analysis of dump, skill binding extraction]

## out_of_scope
- assets: []
- activities: [dos, phishing_real_users, unrestricted_exfil, 修改游戏逻辑代码（只读观测+dump）]

## network_profile
- mode: offline
- notes: |
    分析本身离线；游戏运行需连接用户自有私服 101.133.161.124（用户明确指示的启动方式）。
    不对服务器做任何探测，仅让客户端正常启动。

## deliverables
- report: true
- field_journal: true
- diagrams: true
- timeline: true

## constraints
- timebox: {}
- stealth: low
- data_handling: anonymize

## signoff
- ready_for_act: false
- checklist:
  - [x] auth.status = granted
  - [ ] in_scope.assets non-empty OR offline sample path set
  - [x] network_profile.mode chosen
  - [ ] out_of_scope reviewed
  - [ ] roles assigned (see skills/ops/role-map.md)

## ops_refs
- skills/ops/scope-contract.md
- skills/ops/evidence-finding-path.md
- skills/ops/role-map.md
- skills/ops/timeline-workitem.md
- skills/ops/IDENTITY.md
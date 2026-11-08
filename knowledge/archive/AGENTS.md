# Workspace instructions

Read and follow [agent.md](agent.md) before changing this project. It records the user's GBA priority, original-client fidelity requirements, and mandatory preservation of data for future PSP/other-platform ports.

## PVF knowledge priority

For every PVF-related task, first consult the highest-priority reference selected by the user:
`dnf-知识库/PVF-Ai-Agent-Workbench-3.1.1/knowledge-pack/indexes/knowledge-index.json`.
Follow the index to the relevant topic. This archive is the current source location after the user's reorganization; old paths outside `knowledge/archive` are historical. Keep source evidence, version identity, conflicts, and unknowns distinct: the knowledge pack guides PVF research but does not by itself prove behavior in a specific client. Do not execute bundled programs or modify archived source materials.

## Project-local PVF knowledge skills

For PVF knowledge work, read the [local knowledge policy](skills/KNOWLEDGE_POLICY.md), then the applicable skill:

- [dnf-pvf-knowledge](skills/dnf-pvf-knowledge/SKILL.md): community course index, content recipes, format references.
- [dfo-pvf](skills/dfo-pvf/SKILL.md): concise ANI/ALS/ATK/SKL/MOB references.
- [dnf-pvf-reference](skills/dnf-pvf-reference/SKILL.md): annotated source samples and evidence preservation.

These are offline project-local references. Current 1031 bytes and verified runtime evidence take precedence over community explanations. Read the knowledge audit before adopting a claim; known conflicts must not be imported as client facts. See [the audit](dnf-native-demo/reports/knowledge-base-audit/README.md) for coverage, version conflicts and implementation findings.

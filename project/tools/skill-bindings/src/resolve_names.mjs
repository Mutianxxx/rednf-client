// Resolve Chinese skill names for all classes; dump swordman name table
import "./bun-shim.mjs";
import { fileURLToPath } from "node:url";
import { readPvf } from "../../../../../npk-pvf解析器/src/pvf/reader.ts";
import { buildStringContext } from "../../../../../npk-pvf解析器/src/pvf/build-string-context.ts";

const BASE = fileURLToPath(new URL("../", import.meta.url));
const OUT = BASE + "pvf-out";
const PVF = process.env.DNF1031_PVF ?? "D:/dnf-rebuild/DNF1031客户端/Script.pvf";
const { entries, getFileData } = await readPvf(PVF);
const entryByPath = new Map();
for (const e of entries) entryByPath.set(e.filePath.toLowerCase(), e);
const strCtx = await buildStringContext(entryByPath, getFileData);

function resolve(link) {
  if (typeof link !== "string") return null;
  const m = link.match(/^@(\d+)::(.+)$/);
  if (!m) return link;
  const map = strCtx.translationsByListId.get(Number(m[1]));
  return map ? (map.get(m[2]) ?? null) : null;
}

import { readdirSync, readFileSync, writeFileSync } from "node:fs";

const out = {};
const dir = OUT + "/skill";
for (const cls of readdirSync(dir)) {
  if (!/^[a-z]+$/i.test(cls)) continue;
  const lstPath = `${OUT}/skill/${cls}skill.lst.json`;
  let lst = {};
  try { lst = JSON.parse(readFileSync(lstPath, "utf8")); } catch { continue; }
  out[cls] = {};
  for (const [id, skl] of Object.entries(lst)) {
    let name = null;
    try {
      const sklJson = JSON.parse(readFileSync(
        `${OUT}/skill/${cls}/${skl.replace(/^[^/]+\//, "").replace(/\.skl$/i, "")}.skl.json`, "utf8"));
      for (const item of sklJson) {
        if (item && item.name) { name = resolve(item.name[0]); break; }
      }
    } catch {}
    out[cls][id] = { skl, name };
  }
}
writeFileSync(BASE + "evidence/skill-names.json", JSON.stringify(out, null, 1));

// print swordman names
for (const [id, v] of Object.entries(out.swordman).sort((a, b) => a[0] - b[0])) {
  console.log(`${id.padStart(3)}: ${v.skl.padEnd(45)} ${v.name ?? "?"}`);
}

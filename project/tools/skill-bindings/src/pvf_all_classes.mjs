import "./bun-shim.mjs";
import { fileURLToPath } from "node:url";
import { readPvf } from "../../../../../npk-pvf解析器/src/pvf/reader.ts";
import { convertFile } from "../../../../../npk-pvf解析器/src/pvf/convert-file.ts";
import { buildStringContext } from "../../../../../npk-pvf解析器/src/pvf/build-string-context.ts";
import { convertNameList } from "../../../../../npk-pvf解析器/src/pvf/name-list.ts";
import { writeFile, mkdir } from "node:fs/promises";
import { dirname } from "node:path";

const PVF = process.env.DNF1031_PVF ?? "D:/dnf-rebuild/DNF1031客户端/Script.pvf";
const BASE = fileURLToPath(new URL("../", import.meta.url));
const OUT = BASE + "pvf-out";

const { entries, getFileData } = await readPvf(PVF);
const entryByPath = new Map();
for (const e of entries) entryByPath.set(e.filePath.toLowerCase(), e);
const strCtx = await buildStringContext(entryByPath, getFileData);

// 1) class inventory
const lsts = entries.filter((e) => /^skill\/[^/]+\.lst$/i.test(e.filePath));
const chrs = entries.filter((e) => /^character\/[^/]+\/[^/]+\.chr$/i.test(e.filePath));
console.log("skill lst files:", lsts.length);
for (const e of lsts) console.log("  LST", e.filePath);
console.log("chr files:", chrs.length);
for (const e of chrs) console.log("  CHR", e.filePath);

// 2) extract: all class lst, skl, chr
const want = [
  ...lsts.map((e) => e.filePath),
  ...chrs.map((e) => e.filePath),
  ...entries
    .filter((e) => /^skill\/[^/]+\/[^/]+\.skl$/i.test(e.filePath))
    .map((e) => e.filePath),
];
let ok = 0;
for (const p of want) {
  const e = entryByPath.get(p.toLowerCase());
  if (!e) continue;
  try {
    const data = await getFileData(e);
    const conv = p.toLowerCase().endsWith(".lst")
      ? convertNameList(data, strCtx)
      : convertFile(data, e.filePath, strCtx, { resolveStringLink: false });
    const out = `${OUT}/${p}.json`;
    await mkdir(dirname(out), { recursive: true });
    await writeFile(out, JSON.stringify(conv));
    ok++;
  } catch (err) {
    console.log("FAIL", p, String(err).slice(0, 80));
  }
}
console.log(`extracted ${ok}/${want.length}`);

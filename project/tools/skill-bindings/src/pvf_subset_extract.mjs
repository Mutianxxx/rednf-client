import "./bun-shim.mjs";
import { fileURLToPath } from "node:url";
// Subset PVF extractor - runs under node 22 with --experimental-strip-types
// Extracts only skill-binding-relevant files from Script.pvf
import { mkdir, writeFile } from "node:fs/promises";
import { dirname } from "node:path";
import { buildStringContext } from "../../../../../npk-pvf解析器/src/pvf/build-string-context.ts";
import { convertFile } from "../../../../../npk-pvf解析器/src/pvf/convert-file.ts";
import { convertNameList } from "../../../../../npk-pvf解析器/src/pvf/name-list.ts";
import { readPvf } from "../../../../../npk-pvf解析器/src/pvf/reader.ts";

const PVF = process.env.DNF1031_PVF ?? "D:/dnf-rebuild/DNF1031客户端/Script.pvf";
const BASE = fileURLToPath(new URL("../", import.meta.url));
const OUT = BASE + "pvf-out";

const WANT = [
  /^skill\/[^\/]+\.lst$/i,
  /^skill\/[^\/]+\/[^/]+\.skl$/i,
  /^character\/character\.lst$/i,
  /^character\/[^\/]+\/[^/]+\.chr$/i,
  /^sqr\//i,
];

const { header, entries, getFileData } = await readPvf(PVF);
console.log(`PVF version=${header.fileVersion}, files=${entries.length}`);

const entryByPath = new Map();
for (const e of entries) entryByPath.set(e.filePath.toLowerCase(), e);
const strCtx = await buildStringContext(entryByPath, getFileData);

let n = 0;
for (const entry of entries) {
  const p = entry.filePath.replace(/\\/g, "/").toLowerCase();
  if (!WANT.some((re) => re.test(p))) continue;
  const data = await getFileData(entry);
  if (!data || data.length === 0) continue;
  const safe = entry.filePath.replace(/\\/g, "/").replace(/^\//, "");
  const outPath = `${OUT}/${safe}.json`;
  await mkdir(dirname(outPath), { recursive: true });
  let obj;
  if (p.endsWith(".lst")) {
    obj = convertNameList(data, strCtx);
  } else {
    obj = convertFile(data, entry.filePath, strCtx, { resolveStringLink: false });
  }
  if (!obj) continue;
  const text = typeof obj === "object" ? JSON.stringify(obj, null, 1) : String(obj);
  await writeFile(outPath, text);
  n++;
}
console.log(`Extracted ${n} subset files to ${OUT}`);

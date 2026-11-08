import "./bun-shim.mjs";
import { fileURLToPath } from "node:url";
import { readPvf } from "../../../../../npk-pvf解析器/src/pvf/reader.ts";
import { buildStringContext } from "../../../../../npk-pvf解析器/src/pvf/build-string-context.ts";
import { convertFile } from "../../../../../npk-pvf解析器/src/pvf/convert-file.ts";
import { writeFile, mkdir } from "node:fs/promises";
import { dirname } from "node:path";

const OUT = fileURLToPath(new URL("../pvf-out", import.meta.url));

const { entries, getFileData } = await readPvf(process.env.DNF1031_PVF ?? "D:/dnf-rebuild/DNF1031客户端/Script.pvf");
const entryByPath = new Map();
for (const e of entries) entryByPath.set(e.filePath.toLowerCase(), e);
const strCtx = await buildStringContext(entryByPath, getFileData);

const WANT = [
  "passiveobject/character/swordman/khazan.obj",
  "passiveobject/passiveobject.lst",
];
for (const p of WANT) {
  const e = entryByPath.get(p);
  if (!e) { console.log("MISSING", p); continue; }
  const data = await getFileData(e);
  let obj;
  if (p.endsWith(".lst")) {
    const { convertNameList } = await import("../../../../../npk-pvf解析器/src/pvf/name-list.ts");
    obj = convertNameList(data, strCtx);
  } else {
    obj = convertFile(data, e.filePath, strCtx, { resolveStringLink: false });
  }
  const out = `${OUT}/${p}.json`;
  await mkdir(dirname(out), { recursive: true });
  await writeFile(out, JSON.stringify(obj, null, 1));
  console.log("OK", p, "bytes", data.length);
}

import "./bun-shim.mjs";
import { fileURLToPath } from "node:url";
import { readPvf } from "../../../../../npk-pvf解析器/src/pvf/reader.ts";
import { convertNameList } from "../../../../../npk-pvf解析器/src/pvf/name-list.ts";
import { buildStringContext } from "../../../../../npk-pvf解析器/src/pvf/build-string-context.ts";
import { writeFile } from "node:fs/promises";

const OUT = fileURLToPath(new URL("../pvf-out", import.meta.url));

const { entries, getFileData } = await readPvf(process.env.DNF1031_PVF ?? "D:/dnf-rebuild/DNF1031客户端/Script.pvf");
const entryByPath = new Map();
for (const e of entries) entryByPath.set(e.filePath.toLowerCase(), e);
const strCtx = await buildStringContext(entryByPath, getFileData);
const lsts = entries.filter((e) => /^skill\/[^/]+\.lst$/i.test(e.filePath));
for (const e of lsts) {
  const data = await getFileData(e);
  const conv = convertNameList(data, strCtx);
  await writeFile(
    OUT + "/" + e.filePath + ".json",
    JSON.stringify(conv),
  );
  console.log(e.filePath, "entries:", conv ? Object.keys(conv).length : 0);
}

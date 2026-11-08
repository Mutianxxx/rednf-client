// Minimal Bun.file shim for node (only slice().arrayBuffer() / arrayBuffer() are used)
import { openSync, readSync, closeSync, fstatSync } from "node:fs";

globalThis.Bun = {
  file(path) {
    const fd = openSync(path, "r");
    const size = fstatSync(fd).size;
    function readRange(start, endExclusive) {
      const len = Math.max(0, (endExclusive ?? size) - start);
      const buf = Buffer.alloc(len);
      if (len > 0) readSync(fd, buf, 0, len, start);
      const ab = buf.buffer.slice(buf.byteOffset, buf.byteOffset + len);
      return Promise.resolve(ab);
    }
    return {
      slice(start, end) {
        return { arrayBuffer: () => readRange(start, end) };
      },
      arrayBuffer() {
        return readRange(0, size);
      },
    };
  },
  write(path, data) {
    const { writeFileSync } = require("node:fs");
    writeFileSync(path, data);
    return Promise.resolve(data.length);
  },
  argv: process.argv,
};

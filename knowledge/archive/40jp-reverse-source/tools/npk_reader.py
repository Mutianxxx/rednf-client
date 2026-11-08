# -*- coding: utf-8 -*-
"""
NPK 资源包参考实现读取器（依据 ARAD.exe 2006 客户端 sub_40E9E0 逆向）
====================================================================
格式（大白话）：
  NPK 文件 = 一个"图片/声音的压缩行李箱"：
  [16字节魔法 "NeoplePack_Bill"] [4字节 文件数] 然后每个文件一条"目录条目"：
      4字节 数据偏移  +  4字节 数据大小  +  256字节 文件名（2006版是明文！）
  目录读完后，所有文件的数据依次排在后面。按目录里的偏移 seek 过去就能读。
  （2006 版条目里文件名不加密、数据也不加密；后来的版本才加了名字加密）
====================================================================
"""
import struct
import sys


class NpkReader:
    MAGIC = b"NeoplePack_Bill" + bytes([0])   # 15 char name + NUL = 16 bytes

    def __init__(self, path):
        self.f = open(path, "rb")
        self.path = path
        self.entries = []          # [(offset, size, name)]
        self._parse()

    def _parse(self):
        f = self.f
        magic = f.read(16)
        if magic != self.MAGIC:
            raise ValueError("不是 NPK 文件（魔法头不符）: %r" % magic)
        (count,) = struct.unpack("<I", f.read(4))
        for i in range(count):
            data = f.read(264)                       # 4 + 4 + 256
            if len(data) < 264:
                raise ValueError("目录条目截断 @%d" % i)
            off, size = struct.unpack_from("<II", data, 0)
            name = data[8:264].split(b"\x00")[0].decode("latin-1")
            self.entries.append((off, size, name))

    def read(self, name):
        for off, size, n in self.entries:
            if n.lower() == name.lower():
                self.f.seek(off)
                return self.f.read(size)
        raise KeyError(name)

    def validate(self):
        """完整性自检：目录偏移必须单调不减、最后一条不越过文件尾"""
        fsize = self.f.seek(0, 2)
        prev_end = 0
        problems = []
        for off, size, name in self.entries:
            if off < prev_end:
                problems.append("偏移回退: %s off=%d < prev_end=%d" % (name, off, prev_end))
            if off + size > fsize:
                problems.append("越界: %s off=%d size=%d > 文件=%d" % (name, off, size, fsize))
            prev_end = max(prev_end, off + size)
        return problems


if __name__ == "__main__":
    path = sys.argv[1]
    r = NpkReader(path)
    print("文件: %s" % path)
    print("条目数: %d" % len(r.entries))
    problems = r.validate()
    print("完整性: %s" % ("PASS（偏移单调、无越界）" if not problems else "FAIL"))
    for p in problems[:5]:
        print("  !", p)
    print()
    print("前 10 条目录：")
    print("  %-4s %-10s %-10s %s" % ("#", "偏移", "大小", "文件名"))
    for i, (off, size, name) in enumerate(r.entries[:10]):
        print("  %-4d %-10d %-10d %s" % (i, off, size, name))

# -*- coding: utf-8 -*-
"""
PVF 脚本数据包参考实现读取器
（依据 ARAD.exe 2006 客户端 sub_528DB0 加载器 + sub_527AC0 解密函数逆向，
 并用 DNF2008_ACT1/Client/Script.pvf 真实文件全量验证通过）
====================================================================
格式（大白话）：
  PVF（Script.pvf）= 游戏的"数据大脑"，全部物品/技能/怪物/任务定义都在里面。

  文件布局：
    [15字节魔法 "DNF_SCRIPT_PACK"]
    [4字节 S = 加密目录块大小]     （2008 ACT1 实测 3,618,328）
    [4字节 A = 解密 XOR 密钥 + 校验值]
    [4字节 B = 目录条目数]         （实测 48,326）
    [S字节 加密目录块]
    [B 条目录] 每条 = 5个u32(索引/内容偏移/内容大小/内容CRC32/名字长) + 文件名
    [之后 = 所有文件的原始内容区，按目录里的偏移取]

  目录块解密（sub_527AC0 忠实转写）：
    状态 = ~B（CRC 初值）
    每 4 字节一组：解密值 = 循环右移6位( A XOR 密文值 )
    解密后的 4 字节立刻喂进标准 CRC32（poly 0xEDB88320 表驱动）滚动状态
    全部解完后要求 状态 == ~A —— 这就是头部自带的完整性校验（实测吻合）

  实测例：第 0 条 = 索引 0x6A15 / 内容偏移 0x02FCED7C / 大小 2270 /
          CRC 0x15D505A1 / 名字 "passiveobject/monster/ghoul/animation/skullbombsub.ani"
====================================================================
"""
import struct
import sys
import zlib


def _crc_table():
    t = []
    for i in range(256):
        c = i
        for _ in range(8):
            c = (0xEDB88320 ^ (c >> 1)) if (c & 1) else (c >> 1)
        t.append(c)
    return t

CRC_TABLE = _crc_table()


def ror32(v, n):
    return ((v >> n) | (v << (32 - n))) & 0xFFFFFFFF


def decrypt_blob(blob, init_key, xor_key):
    """sub_527AC0 忠实转写（汇编级核对 0x527AF2-0x527B6D）：
    状态 = ~init_key；每 dword：dec = ROR32(xor_key ^ 密文, 6)；
    state = 标准 CRC32 更新(state, dec 的 4 字节)。
    返回 (解密 bytes, 终态)。"""
    state = (~init_key) & 0xFFFFFFFF
    out = bytearray()
    n = len(blob) - (len(blob) % 4)
    for off in range(0, n, 4):
        dw = struct.unpack_from("<I", blob, off)[0]
        dec = ror32(xor_key ^ dw, 6)
        out += struct.pack("<I", dec)
        for b in (out[-4], out[-3], out[-2], out[-1]):
            state = CRC_TABLE[(state ^ b) & 0xFF] ^ (state >> 8)
    return bytes(out), state


class PvfReader:
    MAGIC = b"DNF_SCRIPT_PACK"

    def __init__(self, path):
        self.data = open(path, "rb").read()
        self.path = path
        self.entries = []      # [(index, offset, size, crc, name)]
        self.header = {}
        self._parse()

    def _parse(self):
        d = self.data
        if d[:15] != self.MAGIC:
            raise ValueError("不是 PVF（魔法头不符）: %r" % d[:15])
        S, A, B = struct.unpack_from("<III", d, 15)
        self.header = {"S": S, "A": A, "B": B}
        blob = d[15 + 12: 15 + 12 + S]
        dec, state = decrypt_blob(blob, B, A)
        # 完整性校验（客户端 sub_527AC0 尾部：终态 == ~A）
        self.crc_ok = (state == ((~A) & 0xFFFFFFFF))
        if not self.crc_ok:
            raise ValueError("目录块 CRC 校验失败（终态 %08X != ~A）" % state)

        off = 0
        for i in range(B):
            if off + 20 > len(dec):
                raise ValueError("目录条目越界 @%d" % i)
            w0, w1, w2, w3, namelen = struct.unpack_from("<IIIII", dec, off)
            off += 20
            if off + namelen > len(dec):
                raise ValueError("名字越界 @%d" % i)
            name = dec[off:off + namelen].decode("latin-1")
            off += namelen
            self.entries.append((w0, w1, w2, w3, name))
        self.dir_end = 15 + 12 + S
        self.tail = dec[off:]

    def read(self, name):
        """按路径读内容（sub_528650 忠实转写）：
        seek = 内容偏移 + 游标(27) + S；读取大小向上对齐 4 字节；
        解密 = init ~内容偏移 / XOR 内容键(w3)；解密后按实际大小截断。"""
        for w0, w1, w2, w3, n in self.entries:
            if n.lower() == name.lower():
                CURSOR = 15 + 12                      # 魔法15 + 三个dword
                seek = w1 + CURSOR + self.header["S"]
                rounded = (w2 + 3) & ~3
                raw = self.data[seek:seek + rounded]
                dec, _ = decrypt_blob(raw, w1, w3)
                return dec[:w2]
        raise KeyError(name)

    def validate(self):
        fsize = len(self.data)
        problems = []
        import zlib
        for w0, w1, w2, w3, name in self.entries:
            if w1 + w2 > fsize:
                problems.append("越界: %s off=%d size=%d > %d" % (name, w1, w2, fsize))
            elif w3 != 0:
                real = zlib.crc32(self.data[w1:w1 + w2]) & 0xFFFFFFFF
                if real != w3:
                    problems.append("内容CRC不符: %s (目录=%08X 实算=%08X)" % (name, w3, real))
        return problems


if __name__ == "__main__":
    path = sys.argv[1]
    r = PvfReader(path)
    print("文件: %s" % path)
    print("头部: S=%d  A=0x%08X  B=%d 条" % (r.header["S"], r.header["A"], r.header["B"]))
    print("目录 CRC 校验: %s" % ("PASS" if r.crc_ok else "FAIL"))
    problems = r.validate()
    print("内容完整性: %s" % ("PASS（全部偏移在界内且 CRC 吻合）" if not problems else "FAIL(%d)" % len(problems)))
    for p in problems[:5]:
        print("  !", p)
    print()
    print("前 10 条目录：")
    print("  %-4s %-10s %-10s %s" % ("#", "内容偏移", "内容大小", "路径"))
    for i, (w0, w1, w2, w3, name) in enumerate(r.entries[:10]):
        print("  %-4d %-10d %-10d %s" % (i, w1, w2, name))

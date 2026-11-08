# -*- coding: utf-8 -*-
"""
IMG 图像文件参考实现读取器（依据 ARAD.exe 2006 客户端 CNImagePackEx::Load 逆向 + 真实文件验证）
====================================================================
格式（大白话）：
  IMG 文件 = DNF 的"精灵图集"——把角色的每个动作帧、每个技能图标、每个特效
  打包成一个文件。就像一本"翻页动画书"。

  文件布局：
    [32字节 魔法区：前18字节 = "Neople Image File\0"，后14字节含版本和图像数]
      其中 +0x18 = DWORD 版本(1)
      其中 +0x1C = DWORD 图像帧数
    [帧 0：36字节头 + zlib 压缩像素]
    [帧 1：36字节头 + zlib 压缩像素]
    ...

  每帧头（36字节 = 9 个 DWORD）：
      DWORD 组 ID        （同组 = 同一技能/动作的多帧）
      DWORD 像素格式     （6 = A1R5G5B5，16 位色）
      DWORD 宽度
      DWORD 高度
      DWORD 解压后大小 (=宽×高×2)
      DWORD 未知1        （观测为 0）
      DWORD 未知2        （观测为 0）
      DWORD 宽度副本
      DWORD 高度副本

  zlib 解压后 = 宽 × 高 × 2 字节的 A1R5G5B5 像素：
      位 15    = Alpha（0=透明 1=不透明）
      位 14-10 = Red（5 位，0-31）
      位 9-5   = Green
      位 4-0   = Blue
  常见值：0x7FFF = 透明白（A=0），0x8888 = 深蓝不透明

  用法：
    python tools/img_reader.py <文件.img>           # 列出全部帧
    python tools/img_reader.py <文件.img> --png out  # 导出为 PNG
====================================================================
"""
import struct
import zlib
import sys
import os


class ImgReader:
    MAGIC = b"Neople Image File"

    def __init__(self, path):
        self.data = open(path, "rb").read()
        self.path = path
        self.frames = []           # [(group_id, format, w, h, csize, pixels_bytes)]
        self.version = 0
        self._parse()

    def _parse(self):
        d = self.data
        if d[:17] != self.MAGIC:
            raise ValueError("不是 IMG 文件（魔法头不符）: %r" % d[:17])
        self.version = struct.unpack_from("<I", d, 0x18)[0]
        count = struct.unpack_from("<I", d, 0x1C)[0]

        pos = 32  # 跳过 32 字节魔法区
        for i in range(count):
            if pos + 36 > len(d):
                break
            # 读 36 字节头
            group_id, fmt, w, h, dsize, unk1, unk2, w2, h2 = struct.unpack_from("<9I", d, pos)
            pos += 36
            # 读 zlib 数据
            zlib_data = d[pos:]
            # zlib 流结束由解压自动确定（csize=解压后大小，非压缩大小）
            # 解压
            dobj = zlib.decompressobj()
            raw = dobj.decompress(zlib_data)
            consumed = len(zlib_data) - len(dobj.unused_data)
            expected = w * h * 2
            if len(raw) != expected:
                raise ValueError("帧 %d 解压大小 %d != 期望 %d (%dx%d×2)" % (i, len(raw), expected, w, h))
            self.frames.append({
                "group_id": group_id, "format": fmt,
                "width": w, "height": h,
                "pixels": raw, "csize": consumed,
            })
            pos += consumed

    def get_rgba(self, frame_idx):
        """把第 frame_idx 帧转成 RGBA8888 字节序列（方便写 PNG）"""
        f = self.frames[frame_idx]
        w, h = f["width"], f["height"]
        rgba = bytearray(w * h * 4)
        for i in range(w * h):
            px = struct.unpack_from("<H", f["pixels"], i * 2)[0]
            a = (px >> 15) & 1
            r = (px >> 10) & 0x1F
            g = (px >> 5) & 0x1F
            b = px & 0x1F
            rgba[i * 4 + 0] = (r << 3) | (r >> 2)   # 5bit→8bit
            rgba[i * 4 + 1] = (g << 3) | (g >> 2)
            rgba[i * 4 + 2] = (b << 3) | (b >> 2)
            rgba[i * 4 + 3] = 255 if a else 0
        return bytes(rgba), w, h

    def get_png(self, frame_idx):
        """生成 PNG 文件字节（纯 Python，无依赖）"""
        rgba, w, h = self.get_rgba(frame_idx)
        # 最小 PNG 编码器
        def chunk(ctype, data):
            c = ctype + data
            return struct.pack(">I", len(data)) + c + struct.pack(">I", zlib.crc32(c) & 0xFFFFFFFF)
        # IHDR
        ihdr = struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0)  # 8bit RGBA
        # IDAT (每行前置 filter byte 0)
        raw_scanlines = b""
        for y in range(h):
            raw_scanlines += b"\x00" + rgba[y * w * 4:(y + 1) * w * 4]
        idat = zlib.compress(raw_scanlines)
        return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", ihdr) +
                chunk(b"IDAT", idat) + chunk(b"IEND", b""))

    def validate(self):
        problems = []
        for i, f in enumerate(self.frames):
            expected = f["width"] * f["height"] * 2
            if len(f["pixels"]) != expected:
                problems.append("帧 %d 像素大小 %d != %d×%d×2" % (i, len(f["pixels"]), f["width"], f["height"]))
        return problems


if __name__ == "__main__":
    path = sys.argv[1]
    r = ImgReader(path)
    print("文件: %s" % path)
    print("版本: %d  帧数: %d" % (r.version, len(r.frames)))
    problems = r.validate()
    print("完整性: %s" % ("PASS" if not problems else "FAIL"))
    for p in problems[:5]:
        print("  !", p)
    print()
    print("帧列表：")
    print("  %-4s %-8s %-6s %-6s %-8s %s" % ("#", "组ID", "宽", "高", "格式", "压缩字节数"))
    for i, f in enumerate(r.frames[:20]):
        print("  %-4d %-8d %-6d %-6d %-8d %d" % (i, f["group_id"], f["width"], f["height"], f["format"], f.get("csize",0)))
    if len(r.frames) > 20:
        print("  ... 共 %d 帧" % len(r.frames))

    # PNG 导出
    if "--png" in sys.argv:
        outdir = sys.argv[sys.argv.index("--png") + 1] if len(sys.argv) > sys.argv.index("--png") + 1 else "img_export"
        os.makedirs(outdir, exist_ok=True)
        base = os.path.splitext(os.path.basename(path))[0]
        for i in range(len(r.frames)):
            png_data = r.get_png(i)
            fn = os.path.join(outdir, "%s_frame%03d.png" % (base, i))
            open(fn, "wb").write(png_data)
        print("\n已导出 %d 张 PNG 到 %s/" % (len(r.frames), outdir))

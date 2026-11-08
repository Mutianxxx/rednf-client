"""Checks include independent known pixels, archive ambiguity, and corrupt inputs."""
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest
import zlib

spec = importlib.util.spec_from_file_location("resources60_test", Path(__file__).resolve().parents[1] / "resources.py")
resources = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = resources
spec.loader.exec_module(resources)


def img_v1(frames):
    return b"Neople Image File\0\0\0" + struct.pack("<3I", 0, 1, len(frames)) + b"".join(frames)


def pixels(color, compression, width, height, raw, x=0, y=0, fw=20, fh=20):
    encoded = zlib.compress(raw) if compression == 6 else raw
    return struct.pack("<9i", color, compression, width, height, len(encoded), x, y, fw, fh) + encoded


def make_npk(path, logical, image):
    seed = (b"puchikon@neople dungeon and fighter " + b"DNF" * 100)[:255] + b"\0"
    name = logical.encode("ascii").ljust(256, b"\0")
    encoded = bytes(a ^ b for a, b in zip(name, seed))
    path.write_bytes(b"NeoplePack_Bill\0" + struct.pack("<I", 1)
                     + struct.pack("<II", 284, len(image)) + encoded + image)


class ResourceTests(unittest.TestCase):
    def test_bgra_and_png_are_independently_readable(self):
        image = resources.Img(img_v1([pixels(16, 6, 2, 1, bytes((3, 2, 1, 255, 33, 22, 11, 128)), x=7)]))
        frame = image.decode(0)
        self.assertEqual(frame["rgba"], bytes((1, 2, 3, 255, 11, 22, 33, 128)))
        self.assertEqual(frame["x"], 7)
        png = resources.png_rgba(2, 1, frame["rgba"])
        self.assertEqual(png[:8], b"\x89PNG\r\n\x1a\n")
        at = 8
        compressed = b""
        while at < len(png):
            length = struct.unpack_from(">I", png, at)[0]
            kind, data = png[at + 4:at + 8], png[at + 8:at + 8 + length]
            self.assertEqual(zlib.crc32(kind + data), struct.unpack_from(">I", png, at + 8 + length)[0])
            if kind == b"IDAT":
                compressed += data
            at += length + 12
        self.assertEqual(zlib.decompress(compressed), b"\0" + frame["rgba"])

    def test_1555_and_4444_known_channels(self):
        first = resources.Img(img_v1([pixels(14, 5, 2, 1, struct.pack("<HH", 0xFC00, 0x03E0))]))
        second = resources.Img(img_v1([pixels(15, 5, 2, 1, struct.pack("<HH", 0xF123, 0x4567))]))
        self.assertEqual(first.decode(0)["rgba"], bytes((255, 0, 0, 255, 0, 255, 0, 0)))
        self.assertEqual(second.decode(0)["rgba"], bytes((17, 34, 51, 255, 85, 102, 119, 68)))

    def test_v2_pixels_follow_complete_table(self):
        raw = bytes((10, 20, 30, 40)) * 2
        record = struct.pack("<9i", 16, 5, 2, 1, 0, -2, 3, 100, 200)
        link = struct.pack("<2i", 17, 0)
        image = resources.Img(b"Neople Img File\0" + struct.pack("<4I", 44, 0, 2, 2) + record + link + raw)
        frame = image.decode(1)
        self.assertEqual(frame["rgba"], bytes((30, 20, 10, 40)) * 2)
        self.assertEqual(frame["resolved_index"], 0)
        self.assertEqual(frame["link_chain"], [1])
        self.assertEqual(frame["record"]["pixel_offset"], 76)

    def test_link_cycle_truncation_and_unknown_format_are_errors(self):
        cycle = resources.Img(img_v1([struct.pack("<2i", 17, 1), struct.pack("<2i", 17, 0)]))
        with self.assertRaises(resources.ResourceError):
            cycle.decode(0)
        with self.assertRaises(resources.ResourceError):
            resources.Img(img_v1([pixels(16, 5, 2, 1, b"\0" * 3)]))
        with self.assertRaises(resources.UnsupportedFormat):
            resources.Img(img_v1([pixels(18, 5, 2, 1, b"\0" * 8)]))
        with self.assertRaises(resources.ResourceError):
            resources.Img(b"Neople Img File\0" + struct.pack("<4I", 7, 0, 2, 1) + struct.pack("<2i", 17, 0))

    def test_corrupt_or_overlong_zlib_rejected(self):
        good = pixels(16, 6, 2, 1, b"\0" * 8)
        corrupt = bytearray(good)
        corrupt[-1] ^= 1
        with self.assertRaises((resources.ResourceError, zlib.error)):
            resources.Img(img_v1([bytes(corrupt)])).decode(0)
        with self.assertRaises(resources.ResourceError):
            resources.Img(img_v1([pixels(16, 6, 2, 1, b"\0" * 9)])).decode(0)

    def test_conflicts_require_explicit_selection_and_keep_provenance(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            logical = "sprite/character/test/body.img"
            make_npk(root / "original.npk", logical, img_v1([pixels(16, 5, 2, 1, b"\0" * 8)]))
            make_npk(root / "patch.NPK", logical, img_v1([pixels(16, 5, 2, 1, b"\xff" * 8)]))
            assets = resources.Assets(root)
            with self.assertRaises(resources.ResourceConflict) as caught:
                assets.frame("Character\\Test\\Body.IMG", 0)
            self.assertEqual(len(caught.exception.candidates), 2)
            frame = assets.frame(logical, 0, package="PATCH.npk")
            self.assertEqual(frame["source"]["package"], "patch.NPK")
            self.assertEqual(frame["source"]["pixel_absolute_offset"], 284 + 68)
            self.assertEqual(len(frame["source"]["npk_sha256"]), 64)
            assets.select(logical, "original.npk")
            self.assertEqual(assets.resolve(logical)["package"], "original.npk")
            self.assertEqual(len(assets.conflicts), 1)
            with self.assertRaises(resources.ResourceError):
                assets.frame("character/test/body%04d.img", 0)

    def test_archive_offsets_are_checked_before_reading(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "bad.npk"
            make_npk(path, "test.img", img_v1([pixels(16, 5, 2, 1, b"\0" * 8)]))
            data = bytearray(path.read_bytes())
            struct.pack_into("<I", data, 20, 0)
            path.write_bytes(data)
            with self.assertRaises(resources.ResourceError):
                resources.Assets(directory)


if __name__ == "__main__":
    unittest.main()

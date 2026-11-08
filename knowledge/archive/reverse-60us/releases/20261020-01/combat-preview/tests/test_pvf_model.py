"""Checks for evidence loss at format boundaries, not speculative game rules."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pvf_model import listing_rows, parse_animation, parse_document


class OrderedScriptTests(unittest.TestCase):
    def test_repeated_tags_scopes_and_byte_offsets(self):
        raw = ("// 한글 comment\r\n[dungeon]\r\n[static data] 4 9\r\n[/static data]\r\n"
               "[x] 1\r\n[x] 2\r\n[/dungeon]\r\n[pvp]\r\n[x] 3\r\n[/pvp]\r\n").encode("cp949")
        document = parse_document(raw)
        values = document.find("x")
        self.assertEqual([n.data for n in values], [[1], [2], [3]])
        self.assertEqual([n.scope for n in values], [("dungeon",), ("dungeon",), ("pvp",)])
        self.assertEqual(document.find("static data")[0].data, [4, 9])
        for node in values:
            self.assertEqual(raw[node.start:node.tag.end], b"[x]")
        self.assertEqual(document.tokens[0].kind, "comment")
        self.assertEqual(document.raw, raw)
        self.assertEqual(document.warnings, [])

    def test_quoted_tag_path_and_comments_are_not_properties(self):
        raw = b'[type] `[active]` // [not a tag]\n[file] `A\\B//c.img` 2\n'
        document = parse_document(raw)
        self.assertEqual([n.name for n in document.events], ["type", "file"])
        self.assertEqual(document.find("type")[0].data, ["[active]"])
        self.assertEqual(document.find("file")[0].data, ["A\\B//c.img", 2])

    def test_malformed_nested_block_is_reported_not_lost(self):
        raw = b"[dungeon]\n[level info] 1 20\n[level info] 1 30\n[/level info]\n[/dungeon]"
        document = parse_document(raw)
        self.assertEqual([n.data for n in document.find("level info")], [[1, 20], [1, 30]])
        self.assertEqual(document.warnings[0]["kind"], "unclosed_nested_block")
        self.assertEqual(len(document.events), 3)

    def test_strict_cp949_decode_rejects_corruption(self):
        with self.assertRaises(UnicodeDecodeError):
            parse_document(b"[name] `\xff`")

    def test_listing_preserves_duplicate_id_rows(self):
        document = parse_document(b"0 `A.chr`\n0 `B.chr` // duplicate, not discarded\n")
        rows = listing_rows(document)
        self.assertEqual([r["id"] for r in rows], [0, 0])
        self.assertEqual([r["path"] for r in rows], ["A.chr", "B.chr"])

    def test_empty_resource_strings_keep_their_slots(self):
        document = parse_document(b"[etc motion]\n`A.ani`\n``\n`B.ani`\n[/etc motion]")
        node = document.find("etc motion")[0]
        self.assertEqual(node.data, ["A.ani", "", "B.ani"])
        self.assertEqual(document.raw[node.values[1].start:node.values[1].end], b"``")

    def test_animation_keeps_all_boxes_unknowns_and_frame_index(self):
        raw = (b"[FRAME MAX] 2\n[FRAME000]\n[IMAGE] `body.img` 9\n[IMAGE POS] -2 -3\n"
               b"[DELAY] 25\n[ATTACK BOX] 1 2 3 4 5 6\n[ATTACK BOX] 7 8 9 10 11 12\n"
               b"[SOUND] `X`\n[FRAME005]\n[DELAY] 0\n[DAMAGE BOX] -1 -2 0 3 4 5\n")
        animation = parse_animation(raw)
        self.assertEqual([f["index"] for f in animation["frames"]], [0, 5])
        self.assertEqual(animation["frames"][0]["attack_boxes"], [[1, 2, 3, 4, 5, 6], [7, 8, 9, 10, 11, 12]])
        self.assertEqual(animation["frames"][0]["unknown_fields"][0]["tag"], "SOUND")
        self.assertEqual(animation["frames"][1]["delays"], [[0]])
        self.assertEqual(animation["warnings"], [])


if __name__ == "__main__":
    unittest.main()

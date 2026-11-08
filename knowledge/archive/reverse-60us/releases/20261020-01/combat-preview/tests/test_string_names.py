import hashlib
from pathlib import Path
import sys
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from pvf_model import node_record,parse_document
from string_names import StringNames


class FakePvf:
    def __init__(self,strings):
        self.files={'string.usa.lst':b'12 `Skill/Skill.usa.str`\n',
                    'skill/skill.usa.str':strings}
        self.by_path={p:dict(path=p,size=len(raw)) for p,raw in self.files.items()}

    def read(self,path):return self.files[path]


class StringNameTests(unittest.TestCase):
    def field(self,value):
        return [node_record(n) for n in parse_document(b'[name] '+value).find('name')]

    def test_explicit_gbk_prefix_and_source_offsets(self):
        value='鬼斩'.encode('cp936')
        raw=b'// heading\r\nname_1>@GBK936@'+value+b'\r\n'
        name=StringNames(FakePvf(raw),'archive').resolve(self.field(b'<12::name_1>'))
        self.assertEqual(name['text'],'鬼斩')
        self.assertEqual(name['encoding'],'cp936')
        self.assertEqual(raw[name['start']:name['end']],b'@GBK936@'+value)
        self.assertEqual(name['table_source']['sha256'],hashlib.sha256(raw).hexdigest())

    def test_duplicate_or_missing_key_is_not_guessed(self):
        strings=StringNames(FakePvf(b'k>one\nk>two\n'),'archive')
        self.assertEqual(strings.resolve(self.field(b'<12::k>'))['status'],'ambiguous-key')
        self.assertEqual(strings.resolve(self.field(b'<12::missing>'))['status'],'missing-key')

    def test_unsupported_encoding_and_bad_bytes_remain_unresolved(self):
        strings=StringNames(FakePvf(b'k>@UNKNOWN@value\nbad>@GBK936@\x81\n'),'archive')
        self.assertEqual(strings.resolve(self.field(b'<12::k>'))['status'],'unsupported-encoding')
        self.assertEqual(strings.resolve(self.field(b'<12::bad>'))['status'],'unresolved')


if __name__=='__main__':unittest.main()

"""Resolve this client's textual <list::key> names without translating them.

The current USA string tables contain explicit @GBK936@ value prefixes. Decode
each value according to its own prefix and retain source offsets/identities.
"""
from collections import defaultdict
import hashlib
import re

from pvf_model import listing_rows, parse_document

REFERENCE = re.compile(r'<(\d+)::([^<>]+)>\Z')
ENCODINGS = {b'@GBK936@': 'cp936'}


class StringNames:
    def __init__(self, pvf, archive_sha256, registry_path='string.usa.lst'):
        self.pvf = pvf
        self.archive_sha256 = archive_sha256
        self.registry_path = registry_path
        self.registry = None
        self.tables = {}

    def identity(self, path, raw):
        return dict(self.pvf.by_path[path], sha256=hashlib.sha256(raw).hexdigest(),
                    archive_sha256=self.archive_sha256, crc_verified=True)

    def table(self, list_id):
        if self.registry is None:
            raw = self.pvf.read(self.registry_path)
            self.registry = listing_rows(parse_document(raw, self.registry_path))
            self.registry_source = self.identity(self.registry_path, raw)
        rows = [row for row in self.registry if row['id'] == list_id]
        if len(rows) != 1:
            raise ValueError('String list ID is missing or ambiguous')
        path = rows[0]['path'].replace('\\', '/').lower()
        if path not in self.tables:
            raw = self.pvf.read(path)
            entries = defaultdict(list)
            offset = 0
            for line_number, line in enumerate(raw.splitlines(keepends=True), 1):
                content = line.rstrip(b'\r\n')
                if b'>' in content and not content.startswith(b'//'):
                    key, value = content.split(b'>', 1)
                    try:
                        key = key.decode('ascii')
                    except UnicodeDecodeError:
                        offset += len(line)
                        continue
                    entries[key].append(dict(raw=value, line=line_number,
                        start=offset+len(key)+1, end=offset+len(content)))
                offset += len(line)
            self.tables[path] = dict(entries=entries, source=self.identity(path, raw))
        return path, rows[0], self.tables[path]

    def resolve(self, fields):
        result = dict(text=None, status='missing', field=fields)
        if not fields:
            return result
        if len(fields) != 1 or len(fields[0]['values']) != 1:
            return dict(result, status='ambiguous-field')
        value = fields[0]['values'][0]
        token = fields[0]['value_tokens'][0]
        if token['kind'] == 'string':
            return dict(result, text=value, status='literal', encoding='cp949')
        reference = REFERENCE.fullmatch(str(value))
        if not reference:
            return dict(result, status='unsupported-expression')
        list_id, key = int(reference[1]), reference[2]
        result.update(reference=value, list_id=list_id, key=key)
        try:
            path, registration, table = self.table(list_id)
            result.update(registry_source=self.registry_source, registration=registration,
                          table_source=table['source'], table_path=path)
            rows = table['entries'].get(key, [])
            if len(rows) != 1:
                return dict(result, status='missing-key' if not rows else 'ambiguous-key')
            row = rows[0]
            raw = row['raw']
            marker = re.match(br'@[^@\r\n]+@', raw)
            prefix = marker[0] if marker else b''
            if prefix and prefix not in ENCODINGS:
                return dict(result, status='unsupported-encoding', marker=prefix.decode('ascii'))
            encoding = ENCODINGS.get(prefix, 'cp949')
            text = raw[len(prefix):].decode(encoding)
            return dict(result, text=text, status='resolved' if text else 'empty',
                        encoding=encoding, marker=prefix.decode('ascii'),
                        line=row['line'], start=row['start'], end=row['end'],
                        raw_value_sha256=hashlib.sha256(raw).hexdigest())
        except (ValueError, KeyError, UnicodeError) as exc:
            return dict(result, status='unresolved', error=str(exc))

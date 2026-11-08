"""Read-only 1031 PVF inspection. Generic reader is shared as source, never edited."""
import importlib.util
from common import WORK, CLIENT, PVF_HASH, digest

SOURCE=WORK/'combat_ui_1031/tools/pvf_reader.py'
spec=importlib.util.spec_from_file_location('ui1031_pvf_reader',SOURCE)
reader=importlib.util.module_from_spec(spec)
spec.loader.exec_module(reader)
try:
    import numpy as np
    def vector_decrypt(data, checksum):
        end=len(data)//4*4
        words=np.frombuffer(data[:end],dtype='<u4') ^ np.uint32(0x81A79011 ^ checksum)
        return ((words>>6)|(words<<26)).astype('<u4').tobytes()+data[end:]
    # Cross-check byte-for-byte against the source algorithm before substituting it.
    for size in (1,4,17,256):
        raw=bytes((i*37+11)%256 for i in range(size))
        assert vector_decrypt(raw,0xa8b3c4d5)==reader.decrypt(raw,0xa8b3c4d5)
    reader.decrypt=vector_decrypt
except ImportError:
    pass


class StrictDecoder(reader.ScriptDecoder):
    def decode_text(self,data,source):
        try:return data.decode('gbk',errors='strict')
        except UnicodeDecodeError as exc:
            raise ValueError(f'Strict CP936 failed: {source}, byte {exc.start}') from exc


def open_pvf():
    if digest(CLIENT/'Script.pvf')!=PVF_HASH:raise ValueError('1031 PVF fingerprint mismatch')
    return reader.Pvf(CLIENT/'Script.pvf')

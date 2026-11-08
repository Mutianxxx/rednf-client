"""Version and paths for the independent 1031 UI laboratory."""
from pathlib import Path
import hashlib

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT.parent
CLIENT = WORK / 'DNF1031客户端'
EXE_HASH = '246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264'
PVF_HASH = 'ca756b7103a91628cffdf42fb745e9185fd5937deb229289a74831aa30500e1f'
SNAPSHOT_HASH = 'ab950286ad291236086beae21ef75b1732d4cd5e52db482e261f4c548969ea44'

def digest(path):
    with Path(path).open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()

def verify_client(pvf=False):
    if digest(CLIENT/'DNF.exe') != EXE_HASH:
        raise RuntimeError('1031 executable fingerprint mismatch')
    if pvf and digest(CLIENT/'Script.pvf') != PVF_HASH:
        raise RuntimeError('1031 PVF fingerprint mismatch')

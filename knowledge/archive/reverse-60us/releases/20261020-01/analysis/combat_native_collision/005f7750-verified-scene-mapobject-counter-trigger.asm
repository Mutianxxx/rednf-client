005f7750 56                       push      esi
005f7751 8bf1                     mov       esi, ecx
005f7753 c6864909000001           mov       byte ptr [esi + 0x949], 1
005f775a e861fdffff               call      0x5f74c0
005f775f 8bce                     mov       ecx, esi
005f7761 e83ae0ffff               call      0x5f57a0
005f7766 8bce                     mov       ecx, esi
005f7768 5e                       pop       esi
005f7769 e962e5ffff               jmp       0x5f5cd0

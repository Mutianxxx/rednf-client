004efc80 55                       push      ebp
004efc81 8bec                     mov       ebp, esp
004efc83 56                       push      esi
004efc84 8bf1                     mov       esi, ecx
004efc86 8b06                     mov       eax, dword ptr [esi]
004efc88 ff90a0050000             call      dword ptr [eax + 0x5a0]
004efc8e 84c0                     test      al, al
004efc90 8a4508                   mov       al, byte ptr [ebp + 8]
004efc93 741b                     je        0x4efcb0
004efc95 84c0                     test      al, al
004efc97 7517                     jne       0x4efcb0
004efc99 8b16                     mov       edx, dword ptr [esi]
004efc9b 56                       push      esi
004efc9c 8bce                     mov       ecx, esi
004efc9e ff92c4030000             call      dword ptr [edx + 0x3c4]
004efca4 8bc8                     mov       ecx, eax
004efca6 e8955a0700               call      0x565740
004efcab 5e                       pop       esi
004efcac 5d                       pop       ebp
004efcad c20400                   ret       4
004efcb0 888684010000             mov       byte ptr [esi + 0x184], al
004efcb6 5e                       pop       esi
004efcb7 5d                       pop       ebp
004efcb8 c20400                   ret       4

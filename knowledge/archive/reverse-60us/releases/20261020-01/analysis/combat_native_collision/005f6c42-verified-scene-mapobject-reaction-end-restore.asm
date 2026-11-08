005f6c42 8bce                     mov       ecx, esi
005f6c44 e82770eaff               call      0x49dc70
005f6c49 8b863c090000             mov       eax, dword ptr [esi + 0x93c]
005f6c4f 85c0                     test      eax, eax
005f6c51 7439                     je        0x5f6c8c
005f6c53 8b16                     mov       edx, dword ptr [esi]
005f6c55 8bce                     mov       ecx, esi
005f6c57 ff92f4000000             call      dword ptr [edx + 0xf4]
005f6c5d 80b83a01000001           cmp       byte ptr [eax + 0x13a], 1
005f6c64 7526                     jne       0x5f6c8c
005f6c66 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
005f6c6c c7863c09000000000000     mov       dword ptr [esi + 0x93c], 0
005f6c76 e8e5064300               call      0xa27360
005f6c7b 8b8e18010000             mov       ecx, dword ptr [esi + 0x118]
005f6c81 8b06                     mov       eax, dword ptr [esi]
005f6c83 51                       push      ecx
005f6c84 8bce                     mov       ecx, esi
005f6c86 ff90f0000000             call      dword ptr [eax + 0xf0]

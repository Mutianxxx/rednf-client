0050136f 8d8f04070000             lea       ecx, [edi + 0x704]
00501375 68e0baca00               push      0xcabae0
0050137a e8711d5500               call      0xa530f0
0050137f 50                       push      eax
00501380 e866fa6f00               call      0xc00deb
00501385 83c408                   add       esp, 8
00501388 85c0                     test      eax, eax
0050138a 0f847f000000             je        0x50140f
00501390 68e0020000               push      0x2e0
00501395 e8b628f0ff               call      0x403c50
0050139a 8bf0                     mov       esi, eax
0050139c 83c404                   add       esp, 4
0050139f 8975e8                   mov       dword ptr [ebp - 0x18], esi
005013a2 85f6                     test      esi, esi
005013a4 c745fc0c000000           mov       dword ptr [ebp - 4], 0xc
005013ab 7435                     je        0x5013e2
005013ad 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
005013b4 7208                     jb        0x5013be
005013b6 8bbb48020000             mov       edi, dword ptr [ebx + 0x248]
005013bc eb06                     jmp       0x5013c4
005013be 8dbb48020000             lea       edi, [ebx + 0x248]
005013c4 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005013c7 6a00                     push      0
005013c9 81c104070000             add       ecx, 0x704
005013cf e81c1d5500               call      0xa530f0
005013d4 50                       push      eax
005013d5 57                       push      edi
005013d6 8bce                     mov       ecx, esi
005013d8 e82325faff               call      0x4a3900
005013dd 8b7d08                   mov       edi, dword ptr [ebp + 8]
005013e0 eb02                     jmp       0x5013e4
005013e2 33c0                     xor       eax, eax
005013e4 85c0                     test      eax, eax
005013e6 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005013ed 8983e0120000             mov       dword ptr [ebx + 0x12e0], eax
005013f3 741a                     je        0x50140f
005013f5 33c9                     xor       ecx, ecx
005013f7 8988cc020000             mov       dword ptr [eax + 0x2cc], ecx
005013fd 8988d0020000             mov       dword ptr [eax + 0x2d0], ecx
00501403 8b8be0120000             mov       ecx, dword ptr [ebx + 0x12e0]
00501409 53                       push      ebx
0050140a e811bc5200               call      0xa2d020
0050140f 8d8f08070000             lea       ecx, [edi + 0x708]
00501415 68e0baca00               push      0xcabae0
0050141a e8d11c5500               call      0xa530f0
0050141f 50                       push      eax
00501420 e8c6f96f00               call      0xc00deb
00501425 83c408                   add       esp, 8
00501428 85c0                     test      eax, eax
0050142a 0f8485000000             je        0x5014b5
00501430 68e0020000               push      0x2e0
00501435 e81628f0ff               call      0x403c50
0050143a 8bf0                     mov       esi, eax
0050143c 83c404                   add       esp, 4
0050143f 8975e8                   mov       dword ptr [ebp - 0x18], esi
00501442 85f6                     test      esi, esi
00501444 c745fc0d000000           mov       dword ptr [ebp - 4], 0xd
0050144b 7435                     je        0x501482
0050144d 83bb5c02000008           cmp       dword ptr [ebx + 0x25c], 8
00501454 7208                     jb        0x50145e
00501456 8bbb48020000             mov       edi, dword ptr [ebx + 0x248]
0050145c eb06                     jmp       0x501464
0050145e 8dbb48020000             lea       edi, [ebx + 0x248]
00501464 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00501467 6a00                     push      0
00501469 81c108070000             add       ecx, 0x708
0050146f e87c1c5500               call      0xa530f0
00501474 50                       push      eax
00501475 57                       push      edi
00501476 8bce                     mov       ecx, esi
00501478 e88324faff               call      0x4a3900
0050147d 8b7d08                   mov       edi, dword ptr [ebp + 8]
00501480 eb02                     jmp       0x501484
00501482 33c0                     xor       eax, eax
00501484 85c0                     test      eax, eax
00501486 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0050148d 8983e4120000             mov       dword ptr [ebx + 0x12e4], eax
00501493 7420                     je        0x5014b5
00501495 c780cc02000001000000     mov       dword ptr [eax + 0x2cc], 1
0050149f c780d002000000000000     mov       dword ptr [eax + 0x2d0], 0
005014a9 8b8be4120000             mov       ecx, dword ptr [ebx + 0x12e4]
005014af 53                       push      ebx
005014b0 e86bbb5200               call      0xa2d020

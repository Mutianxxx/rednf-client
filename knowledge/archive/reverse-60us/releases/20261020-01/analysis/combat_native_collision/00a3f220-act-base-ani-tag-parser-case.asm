00a3f220 50                       push      eax
00a3f221 8b45a8                   mov       eax, dword ptr [ebp - 0x58]
00a3f224 68a092e400               push      0xe492a0
00a3f229 50                       push      eax
00a3f22a 57                       push      edi
00a3f22b 8d4d94                   lea       ecx, [ebp - 0x6c]
00a3f22e e8bd4d9cff               call      0x403ff0
00a3f233 85c0                     test      eax, eax
00a3f235 0f84787d0000             je        0xa46fb3
00a3f23b 688892e400               push      0xe49288
00a3f240 e8880b1c00               call      0xbffdcd
00a3f245 8b4da8                   mov       ecx, dword ptr [ebp - 0x58]
00a3f248 83c404                   add       esp, 4
00a3f24b 50                       push      eax
00a3f24c 688892e400               push      0xe49288
00a3f251 51                       push      ecx
00a3f252 57                       push      edi
00a3f253 8d4d94                   lea       ecx, [ebp - 0x6c]
00a3f256 e8954d9cff               call      0x403ff0
00a3f25b 85c0                     test      eax, eax
00a3f25d 0f858b000000             jne       0xa3f2ee
00a3f263 8d55b0                   lea       edx, [ebp - 0x50]
00a3f266 52                       push      edx
00a3f267 e87412dfff               call      0x8304e0
00a3f26c 83c404                   add       esp, 4
00a3f26f 8d4db0                   lea       ecx, [ebp - 0x50]
00a3f272 e8793e0100               call      0xa530f0
00a3f277 50                       push      eax
00a3f278 8d85d4fcffff             lea       eax, [ebp - 0x32c]
00a3f27e 50                       push      eax
00a3f27f 8d8d4cf9ffff             lea       ecx, [ebp - 0x6b4]
00a3f285 51                       push      ecx
00a3f286 e8f595d3ff               call      0x778880
00a3f28b 83c40c                   add       esp, 0xc
00a3f28e 6aff                     push      -1
00a3f290 57                       push      edi
00a3f291 50                       push      eax
00a3f292 8d8d24fbffff             lea       ecx, [ebp - 0x4dc]
00a3f298 c645fc08                 mov       byte ptr [ebp - 4], 8
00a3f29c e8bf3a9cff               call      0x402d60
00a3f2a1 83bd64f9ffff08           cmp       dword ptr [ebp - 0x69c], 8
00a3f2a8 c645fc07                 mov       byte ptr [ebp - 4], 7
00a3f2ac 720f                     jb        0xa3f2bd
00a3f2ae 8b9550f9ffff             mov       edx, dword ptr [ebp - 0x6b0]
00a3f2b4 52                       push      edx
00a3f2b5 e8230d1c00               call      0xbfffdd
00a3f2ba 83c404                   add       esp, 4
00a3f2bd 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a3f2c0 6aff                     push      -1
00a3f2c2 57                       push      edi
00a3f2c3 8d8524fbffff             lea       eax, [ebp - 0x4dc]
00a3f2c9 50                       push      eax
00a3f2ca 83c104                   add       ecx, 4
00a3f2cd c78564f9ffff07000000     mov       dword ptr [ebp - 0x69c], 7
00a3f2d7 89bd60f9ffff             mov       dword ptr [ebp - 0x6a0], edi
00a3f2dd 6689bd50f9ffff           mov       word ptr [ebp - 0x6b0], di
00a3f2e4 e8773a9cff               call      0x402d60
00a3f2e9 e962080000               jmp       0xa3fb50
00a3f2ee 687492e400               push      0xe49274
00a3f2f3 e8d50a1c00               call      0xbffdcd
00a3f2f8 8b4da8                   mov       ecx, dword ptr [ebp - 0x58]
00a3f2fb 83c404                   add       esp, 4
00a3f2fe 50                       push      eax
00a3f2ff 687492e400               push      0xe49274
00a3f304 51                       push      ecx
00a3f305 57                       push      edi
00a3f306 8d4d94                   lea       ecx, [ebp - 0x6c]
00a3f309 e8e24c9cff               call      0x403ff0
00a3f30e 85c0                     test      eax, eax

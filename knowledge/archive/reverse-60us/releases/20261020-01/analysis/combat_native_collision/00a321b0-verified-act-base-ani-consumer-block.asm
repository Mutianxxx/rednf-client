00a321b0 55                       push      ebp
00a321b1 8bec                     mov       ebp, esp
00a321b3 6aff                     push      -1
00a321b5 68a4e9c800               push      0xc8e9a4
00a321ba 64a100000000             mov       eax, dword ptr fs:[0]
00a321c0 50                       push      eax
00a321c1 64892500000000           mov       dword ptr fs:[0], esp
00a321c8 83ec38                   sub       esp, 0x38
00a321cb 53                       push      ebx
00a321cc 8b5d08                   mov       ebx, dword ptr [ebp + 8]
00a321cf 85db                     test      ebx, ebx
00a321d1 57                       push      edi
00a321d2 8bf9                     mov       edi, ecx
00a321d4 897df0                   mov       dword ptr [ebp - 0x10], edi
00a321d7 7522                     jne       0xa321fb
00a321d9 683455e400               push      0xe45534
00a321de ff15bc2eff00             call      dword ptr [0xff2ebc]
00a321e4 83c404                   add       esp, 4
00a321e7 5f                       pop       edi
00a321e8 32c0                     xor       al, al
00a321ea 5b                       pop       ebx
00a321eb 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a321ee 64890d00000000           mov       dword ptr fs:[0], ecx
00a321f5 8be5                     mov       esp, ebp
00a321f7 5d                       pop       ebp
00a321f8 c20800                   ret       8
00a321fb 56                       push      esi
00a321fc 68e8010000               push      0x1e8
00a32201 e84a1a9dff               call      0x403c50
00a32206 83c404                   add       esp, 4
00a32209 8945e8                   mov       dword ptr [ebp - 0x18], eax
00a3220c 85c0                     test      eax, eax
00a3220e c745fc00000000           mov       dword ptr [ebp - 4], 0
00a32215 be08000000               mov       esi, 8
00a3221a 7423                     je        0xa3223f
00a3221c 39731c                   cmp       dword ptr [ebx + 0x1c], esi
00a3221f 720f                     jb        0xa32230
00a32221 8b4b08                   mov       ecx, dword ptr [ebx + 8]
00a32224 6a01                     push      1
00a32226 51                       push      ecx
00a32227 8bc8                     mov       ecx, eax
00a32229 e8a214a6ff               call      0x4936d0
00a3222e eb11                     jmp       0xa32241
00a32230 8d4b08                   lea       ecx, [ebx + 8]
00a32233 6a01                     push      1
00a32235 51                       push      ecx
00a32236 8bc8                     mov       ecx, eax
00a32238 e89314a6ff               call      0x4936d0
00a3223d eb02                     jmp       0xa32241
00a3223f 33c0                     xor       eax, eax
00a32241 85c0                     test      eax, eax
00a32243 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
00a3224a 894720                   mov       dword ptr [edi + 0x20], eax
00a3224d 7408                     je        0xa32257
00a3224f 89b89c010000             mov       dword ptr [eax + 0x19c], edi
00a32255 eb1c                     jmp       0xa32273
00a32257 39731c                   cmp       dword ptr [ebx + 0x1c], esi
00a3225a 7205                     jb        0xa32261
00a3225c 8b4308                   mov       eax, dword ptr [ebx + 8]
00a3225f eb03                     jmp       0xa32264
00a32261 8d4308                   lea       eax, [ebx + 8]
00a32264 50                       push      eax
00a32265 681455e400               push      0xe45514
00a3226a ff15bc2eff00             call      dword ptr [0xff2ebc]
00a32270 83c408                   add       esp, 8

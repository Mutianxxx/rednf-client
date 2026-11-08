004a02a0 7cce                     jl        0x4a0270
004a02a2 8b8728010000             mov       eax, dword ptr [edi + 0x128]
004a02a8 8986b8050000             mov       dword ptr [esi + 0x5b8], eax
004a02ae 8b8f2c010000             mov       ecx, dword ptr [edi + 0x12c]
004a02b4 898ebc050000             mov       dword ptr [esi + 0x5bc], ecx
004a02ba ff155cf04001             call      dword ptr [0x140f05c]
004a02c0 8986c0050000             mov       dword ptr [esi + 0x5c0], eax
004a02c6 8b8748010000             mov       eax, dword ptr [edi + 0x148]
004a02cc 3b874c010000             cmp       eax, dword ptr [edi + 0x14c]
004a02d2 894508                   mov       dword ptr [ebp + 8], eax
004a02d5 0f8419010000             je        0x4a03f4
004a02db 8d9e30080000             lea       ebx, [esi + 0x830]
004a02e1 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a02e4 68e0baca00               push      0xcabae0
004a02e9 e8022e5b00               call      0xa530f0
004a02ee 50                       push      eax
004a02ef e8f70a7600               call      0xc00deb
004a02f4 83c408                   add       esp, 8
004a02f7 85c0                     test      eax, eax
004a02f9 0f8492000000             je        0x4a0391
004a02ff 68e8010000               push      0x1e8
004a0304 e84739f6ff               call      0x403c50
004a0309 83c404                   add       esp, 4
004a030c 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a030f 85c0                     test      eax, eax
004a0311 c745fc08000000           mov       dword ptr [ebp - 4], 8
004a0318 742a                     je        0x4a0344
004a031a 8d8fa4000000             lea       ecx, [edi + 0xa4]
004a0320 e8cb2d5b00               call      0xa530f0
004a0325 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a0328 6a01                     push      1
004a032a 89450c                   mov       dword ptr [ebp + 0xc], eax
004a032d e8be2d5b00               call      0xa530f0
004a0332 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004a0335 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004a0338 50                       push      eax
004a0339 52                       push      edx
004a033a e82127fdff               call      0x472a60
004a033f 89450c                   mov       dword ptr [ebp + 0xc], eax
004a0342 eb07                     jmp       0x4a034b
004a0344 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
004a034b 8b5304                   mov       edx, dword ptr [ebx + 4]
004a034e 85d2                     test      edx, edx
004a0350 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004a0353 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a035a 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a035d 7504                     jne       0x4a0363
004a035f 33c0                     xor       eax, eax
004a0361 eb08                     jmp       0x4a036b
004a0363 8b4308                   mov       eax, dword ptr [ebx + 8]
004a0366 2bc2                     sub       eax, edx
004a0368 c1f802                   sar       eax, 2
004a036b 85d2                     test      edx, edx
004a036d 741c                     je        0x4a038b
004a036f 8b4b0c                   mov       ecx, dword ptr [ebx + 0xc]
004a0372 2bca                     sub       ecx, edx
004a0374 c1f902                   sar       ecx, 2
004a0377 3bc1                     cmp       eax, ecx
004a0379 7310                     jae       0x4a038b
004a037b 8b4308                   mov       eax, dword ptr [ebx + 8]
004a037e 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a0381 8908                     mov       dword ptr [eax], ecx
004a0383 83c004                   add       eax, 4
004a0386 894308                   mov       dword ptr [ebx + 8], eax
004a0389 eb52                     jmp       0x4a03dd
004a038b 8d55f0                   lea       edx, [ebp - 0x10]
004a038e 52                       push      edx
004a038f eb3f                     jmp       0x4a03d0
004a0391 8b5304                   mov       edx, dword ptr [ebx + 4]
004a0394 85d2                     test      edx, edx
004a0396 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
004a039d 7504                     jne       0x4a03a3
004a039f 33c9                     xor       ecx, ecx
004a03a1 eb08                     jmp       0x4a03ab
004a03a3 8b4b08                   mov       ecx, dword ptr [ebx + 8]
004a03a6 2bca                     sub       ecx, edx
004a03a8 c1f902                   sar       ecx, 2
004a03ab 85d2                     test      edx, edx
004a03ad 741d                     je        0x4a03cc
004a03af 8b430c                   mov       eax, dword ptr [ebx + 0xc]
004a03b2 2bc2                     sub       eax, edx
004a03b4 c1f802                   sar       eax, 2
004a03b7 3bc8                     cmp       ecx, eax
004a03b9 7311                     jae       0x4a03cc
004a03bb 8b4308                   mov       eax, dword ptr [ebx + 8]
004a03be c70000000000             mov       dword ptr [eax], 0
004a03c4 83c004                   add       eax, 4
004a03c7 894308                   mov       dword ptr [ebx + 8], eax
004a03ca eb11                     jmp       0x4a03dd
004a03cc 8d4d0c                   lea       ecx, [ebp + 0xc]
004a03cf 51                       push      ecx
004a03d0 8b4308                   mov       eax, dword ptr [ebx + 8]
004a03d3 6a01                     push      1
004a03d5 8bcb                     mov       ecx, ebx
004a03d7 50                       push      eax
004a03d8 e8837df6ff               call      0x408160
004a03dd 8b4508                   mov       eax, dword ptr [ebp + 8]
004a03e0 8b8f4c010000             mov       ecx, dword ptr [edi + 0x14c]
004a03e6 83c004                   add       eax, 4
004a03e9 3bc1                     cmp       eax, ecx
004a03eb 894508                   mov       dword ptr [ebp + 8], eax
004a03ee 0f85edfeffff             jne       0x4a02e1
004a03f4 33d2                     xor       edx, edx
004a03f6 895508                   mov       dword ptr [ebp + 8], edx
004a03f9 8da42400000000           lea       esp, [esp]
004a0400 8b8f58010000             mov       ecx, dword ptr [edi + 0x158]
004a0406 85c9                     test      ecx, ecx
004a0408 0f847b000000             je        0x4a0489
004a040e 8b875c010000             mov       eax, dword ptr [edi + 0x15c]
004a0414 2bc1                     sub       eax, ecx
004a0416 c1f802                   sar       eax, 2
004a0419 3bd0                     cmp       edx, eax
004a041b 736c                     jae       0x4a0489
004a041d 8bc1                     mov       eax, ecx
004a041f 8d                       .byte     0x8d

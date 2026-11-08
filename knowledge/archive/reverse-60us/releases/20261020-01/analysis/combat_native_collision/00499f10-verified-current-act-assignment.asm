00499f10 55                       push      ebp
00499f11 8bec                     mov       ebp, esp
00499f13 56                       push      esi
00499f14 8bf1                     mov       esi, ecx
00499f16 57                       push      edi
00499f17 8bbe48010000             mov       edi, dword ptr [esi + 0x148]
00499f1d 85ff                     test      edi, edi
00499f1f 7408                     je        0x499f29
00499f21 8b07                     mov       eax, dword ptr [edi]
00499f23 56                       push      esi
00499f24 8bcf                     mov       ecx, edi
00499f26 ff5014                   call      dword ptr [eax + 0x14]
00499f29 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00499f2c 85c9                     test      ecx, ecx
00499f2e 740d                     je        0x499f3d
00499f30 e85b385900               call      0xa2d790
00499f35 898648010000             mov       dword ptr [esi + 0x148], eax
00499f3b eb0a                     jmp       0x499f47
00499f3d c7864801000000000000     mov       dword ptr [esi + 0x148], 0
00499f47 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f4d 85c9                     test      ecx, ecx
00499f4f 7427                     je        0x499f78
00499f51 c7860401000000000000     mov       dword ptr [esi + 0x104], 0
00499f5b e8807a5900               call      0xa319e0
00499f60 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f66 56                       push      esi
00499f67 e8b4305900               call      0xa2d020
00499f6c 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499f72 8b11                     mov       edx, dword ptr [ecx]
00499f74 56                       push      esi
00499f75 ff5210                   call      dword ptr [edx + 0x10]
00499f78 85ff                     test      edi, edi
00499f7a 7419                     je        0x499f95
00499f7c 8a87ae000000             mov       al, byte ptr [edi + 0xae]
00499f82 84c0                     test      al, al
00499f84 740f                     je        0x499f95
00499f86 8bcf                     mov       ecx, edi
00499f88 e803385900               call      0xa2d790
00499f8d 8b07                     mov       eax, dword ptr [edi]
00499f8f 6a01                     push      1
00499f91 8bcf                     mov       ecx, edi
00499f93 ff10                     call      dword ptr [eax]
00499f95 5f                       pop       edi
00499f96 5e                       pop       esi
00499f97 5d                       pop       ebp
00499f98 c20400                   ret       4

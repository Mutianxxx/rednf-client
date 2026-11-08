00404960 3801                     cmp       byte ptr [ecx], al
00404962 0000                     add       byte ptr [eax], al
00404964 8d0491                   lea       eax, [ecx + edx*4]
00404967 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0040496d 8dbe34010000             lea       edi, [esi + 0x134]
00404973 8bd0                     mov       edx, eax
00404975 33d1                     xor       edx, ecx
00404977 8910                     mov       dword ptr [eax], edx
00404979 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0040497f 8b5144                   mov       edx, dword ptr [ecx + 0x44]
00404982 8b8640010000             mov       eax, dword ptr [esi + 0x140]
00404988 8d0482                   lea       eax, [edx + eax*4]
0040498b 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00404991 8bc8                     mov       ecx, eax
00404993 33ca                     xor       ecx, edx
00404995 8908                     mov       dword ptr [eax], ecx
00404997 a1d8012101               mov       eax, dword ptr [0x12101d8]
0040499c 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0040499f 8b9640010000             mov       edx, dword ptr [esi + 0x140]
004049a5 8d0491                   lea       eax, [ecx + edx*4]
004049a8 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004049ae 8bd0                     mov       edx, eax
004049b0 33d1                     xor       edx, ecx
004049b2 8910                     mov       dword ptr [eax], edx
004049b4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004049ba 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004049bd 8b8648010000             mov       eax, dword ptr [esi + 0x148]
004049c3 8d0482                   lea       eax, [edx + eax*4]
004049c6 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004049cc 8bc8                     mov       ecx, eax
004049ce 33ca                     xor       ecx, edx
004049d0 8908                     mov       dword ptr [eax], ecx
004049d2 a1d8012101               mov       eax, dword ptr [0x12101d8]
004049d7 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004049da 8b9648010000             mov       edx, dword ptr [esi + 0x148]
004049e0 8d0491                   lea       eax, [ecx + edx*4]
004049e3 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004049e9 8bd0                     mov       edx, eax
004049eb 33d1                     xor       edx, ecx
004049ed 8910                     mov       dword ptr [eax], edx
004049ef 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004049f5 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004049f8 8b8650010000             mov       eax, dword ptr [esi + 0x150]
004049fe 8d0482                   lea       eax, [edx + eax*4]
00404a01 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00404a07 8bc8                     mov       ecx, eax
00404a09 33ca                     xor       ecx, edx
00404a0b 8908                     mov       dword ptr [eax], ecx
00404a0d a1d8012101               mov       eax, dword ptr [0x12101d8]
00404a12 8b9650010000             mov       edx, dword ptr [esi + 0x150]
00404a18 8b4848                   mov       ecx, dword ptr [eax + 0x48]
00404a1b 8d0491                   lea       eax, [ecx + edx*4]
00404a1e 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
00404a24 8bd0                     mov       edx, eax
00404a26 33d1                     xor       edx, ecx
00404a28 8910                     mov       dword ptr [eax], edx
00404a2a 68e0baca00               push      0xcabae0
00404a2f 8d8e5c010000             lea       ecx, [esi + 0x15c]
00404a35 889e54010000             mov       byte ptr [esi + 0x154], bl
00404a3b 899e58010000             mov       dword ptr [esi + 0x158], ebx
00404a41 e85aee6400               call      0xa538a0
00404a46 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404a4c 8b5144                   mov       edx, dword ptr [ecx + 0x44]
00404a4f 8b8668010000             mov       eax, dword ptr [esi + 0x168]
00404a55 8d0482                   lea       eax, [edx + eax*4]
00404a58 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00404a5e 8bc8                     mov       ecx, eax
00404a60 33ca                     xor       ecx, edx
00404a62 8908                     mov       dword ptr [eax], ecx
00404a64 a1d8012101               mov       eax, dword ptr [0x12101d8]
00404a69 8b9668010000             mov       edx, dword ptr [esi + 0x168]
00404a6f 8b4848                   mov       ecx, dword ptr [eax + 0x48]
00404a72 8d0491                   lea       eax, [ecx + edx*4]
00404a75 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
00404a7b 8bd0                     mov       edx, eax
00404a7d 33d1                     xor       edx, ecx
00404a7f 8910                     mov       dword ptr [eax], edx
00404a81 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404a87 683c0f0000               push      0xf3c
00404a8c 8d4614                   lea       eax, [esi + 0x14]
00404a8f 50                       push      eax
00404a90 e86b257100               call      0xb17000
00404a95 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404a9b 683d0f0000               push      0xf3d
00404aa0 57                       push      edi
00404aa1 e85a257100               call      0xb17000
00404aa6 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404aac 683e0f0000               push      0xf3e
00404ab1 8d863c010000             lea       eax, [esi + 0x13c]
00404ab7 50                       push      eax
00404ab8 e843257100               call      0xb17000
00404abd 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404ac3 683f0f0000               push      0xf3f
00404ac8 8d864c010000             lea       eax, [esi + 0x14c]
00404ace 50                       push      eax
00404acf e82c257100               call      0xb17000
00404ad4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00404ada 68400f0000               push      0xf40
00404adf 8d                       .byte     0x8d

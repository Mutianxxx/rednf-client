004044e0 55                       push      ebp
004044e1 8bec                     mov       ebp, esp
004044e3 6aff                     push      -1
004044e5 6808f9c400               push      0xc4f908
004044ea 64a100000000             mov       eax, dword ptr fs:[0]
004044f0 50                       push      eax
004044f1 64892500000000           mov       dword ptr fs:[0], esp
004044f8 51                       push      ecx
004044f9 56                       push      esi
004044fa 8bf1                     mov       esi, ecx
004044fc 8975f0                   mov       dword ptr [ebp - 0x10], esi
004044ff e85c357100               call      0xb17a60
00404504 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0040450a 6a64                     push      0x64
0040450c 56                       push      esi
0040450d c745fc00000000           mov       dword ptr [ebp - 4], 0
00404514 e8972d7100               call      0xb172b0
00404519 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0040451f 8b5144                   mov       edx, dword ptr [ecx + 0x44]
00404522 8b4604                   mov       eax, dword ptr [esi + 4]
00404525 8d0482                   lea       eax, [edx + eax*4]
00404528 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0040452e 8bc8                     mov       ecx, eax
00404530 33ca                     xor       ecx, edx
00404532 8908                     mov       dword ptr [eax], ecx
00404534 8b5604                   mov       edx, dword ptr [esi + 4]
00404537 a1d8012101               mov       eax, dword ptr [0x12101d8]
0040453c 8b4848                   mov       ecx, dword ptr [eax + 0x48]
0040453f 8d0491                   lea       eax, [ecx + edx*4]
00404542 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
00404548 8bd0                     mov       edx, eax
0040454a 33d1                     xor       edx, ecx
0040454c 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0040454f 8910                     mov       dword ptr [eax], edx
00404551 8bc6                     mov       eax, esi
00404553 5e                       pop       esi
00404554 64890d00000000           mov       dword ptr fs:[0], ecx
0040455b 8be5                     mov       esp, ebp
0040455d 5d                       pop       ebp
0040455e c3                       ret       
0040455f cc                       int3      

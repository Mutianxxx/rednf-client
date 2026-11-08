00a297b0 55                       push      ebp
00a297b1 8bec                     mov       ebp, esp
00a297b3 83ec0c                   sub       esp, 0xc
00a297b6 53                       push      ebx
00a297b7 56                       push      esi
00a297b8 33f6                     xor       esi, esi
00a297ba 57                       push      edi
00a297bb 8bd9                     mov       ebx, ecx
00a297bd 8975f8                   mov       dword ptr [ebp - 8], esi
00a297c0 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a297c6 85c0                     test      eax, eax
00a297c8 8975fc                   mov       dword ptr [ebp - 4], esi
00a297cb 741b                     je        0xa297e8
00a297cd 8b8b9c000000             mov       ecx, dword ptr [ebx + 0x9c]
00a297d3 2bc8                     sub       ecx, eax
00a297d5 b843082184               mov       eax, 0x84210843
00a297da f7e9                     imul      ecx
00a297dc 03d1                     add       edx, ecx
00a297de c1fa06                   sar       edx, 6
00a297e1 8bc2                     mov       eax, edx
00a297e3 c1e81f                   shr       eax, 0x1f
00a297e6 03c2                     add       eax, edx
00a297e8 40                       inc       eax
00a297e9 3bf0                     cmp       esi, eax
00a297eb 0f8346010000             jae       0xa29937
00a297f1 8b8398000000             mov       eax, dword ptr [ebx + 0x98]
00a297f7 85c0                     test      eax, eax
00a297f9 741b                     je        0xa29816
00a297fb 8b                       .byte     0x8b
00a297fc 8b                       .byte     0x8b
00a297fd 9c                       pushfd    
00a297fe 0000                     add       byte ptr [eax], al

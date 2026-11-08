005e70c0 55                       push      ebp
005e70c1 8bec                     mov       ebp, esp
005e70c3 6aff                     push      -1
005e70c5 68583bc600               push      0xc63b58
005e70ca 64a100000000             mov       eax, dword ptr fs:[0]
005e70d0 50                       push      eax
005e70d1 64892500000000           mov       dword ptr fs:[0], esp
005e70d8 51                       push      ecx
005e70d9 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005e70dc 56                       push      esi
005e70dd 8bf1                     mov       esi, ecx
005e70df 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005e70e2 50                       push      eax
005e70e3 51                       push      ecx
005e70e4 8bce                     mov       ecx, esi
005e70e6 8975f0                   mov       dword ptr [ebp - 0x10], esi
005e70e9 e84297eaff               call      0x490830
005e70ee 8bce                     mov       ecx, esi
005e70f0 c745fc00000000           mov       dword ptr [ebp - 4], 0
005e70f7 c7066cd2d400             mov       dword ptr [esi], 0xd4d26c
005e70fd e85ef10000               call      0x5f6260
005e7102 8bce                     mov       ecx, esi
005e7104 e837f50000               call      0x5f6640
005e7109 8bce                     mov       ecx, esi
005e710b e840550200               call      0x60c650
005e7110 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e7113 8bc6                     mov       eax, esi
005e7115 5e                       pop       esi
005e7116 64890d00000000           mov       dword ptr fs:[0], ecx
005e711d 8be5                     mov       esp, ebp
005e711f 5d                       pop       ebp
005e7120 c20800                   ret       8

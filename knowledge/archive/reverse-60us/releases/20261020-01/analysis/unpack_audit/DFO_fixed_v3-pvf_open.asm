00a570d0 55                       push       ebp
00a570d1 8bec                     mov        ebp, esp
00a570d3 6aff                     push       -1
00a570d5 68c5fbc800               push       0xc8fbc5
00a570da 64a100000000             mov        eax, dword ptr fs:[0]
00a570e0 50                       push       eax
00a570e1 64892500000000           mov        dword ptr fs:[0], esp
00a570e8 83ec28                   sub        esp, 0x28
00a570eb 56                       push       esi
00a570ec 8bf1                     mov        esi, ecx
00a570ee 8a467c                   mov        al, byte ptr [esi + 0x7c]
00a570f1 84c0                     test       al, al
00a570f3 7424                     je         0xa57119
00a570f5 8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a570f8 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a570fb 8b5508                   mov        edx, dword ptr [ebp + 8]
00a570fe 50                       push       eax
00a570ff 51                       push       ecx
00a57100 52                       push       edx
00a57101 8bce                     mov        ecx, esi
00a57103 e868f7ffff               call       0xa56870
00a57108 5e                       pop        esi
00a57109 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]

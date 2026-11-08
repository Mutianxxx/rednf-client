004a3440 55                       push      ebp
004a3441 8bec                     mov       ebp, esp
004a3443 6aff                     push      -1
004a3445 68306ec500               push      0xc56e30
004a344a 64a100000000             mov       eax, dword ptr fs:[0]
004a3450 50                       push      eax
004a3451 64892500000000           mov       dword ptr fs:[0], esp
004a3458 51                       push      ecx
004a3459 53                       push      ebx
004a345a 56                       push      esi
004a345b 8bf1                     mov       esi, ecx
004a345d 57                       push      edi
004a345e 8975f0                   mov       dword ptr [ebp - 0x10], esi
004a3461 e8caa9faff               call      0x44de30
004a3466 33ff                     xor       edi, edi
004a3468 c706cc89cc00             mov       dword ptr [esi], 0xcc89cc
004a346e 897dfc                   mov       dword ptr [ebp - 4], edi
004a3471 89be48010000             mov       dword ptr [esi + 0x148], edi
004a3477 89be4c010000             mov       dword ptr [esi + 0x14c], edi
004a347d 89be50010000             mov       dword ptr [esi + 0x150], edi
004a3483 c7867401000007000000     mov       dword ptr [esi + 0x174], 7
004a348d 89be70010000             mov       dword ptr [esi + 0x170], edi
004a3493 6689be60010000           mov       word ptr [esi + 0x160], di
004a349a 8d9e78010000             lea       ebx, [esi + 0x178]
004a34a0 8bcb                     mov       ecx, ebx
004a34a2 c645fc02                 mov       byte ptr [ebp - 4], 2
004a34a6 e875ea5a00               call      0xa51f20
004a34ab 8bcb                     mov       ecx, ebx
004a34ad e86eeb5a00               call      0xa52020
004a34b2 c786b001000007000000     mov       dword ptr [esi + 0x1b0], 7
004a34bc 89beac010000             mov       dword ptr [esi + 0x1ac], edi
004a34c2 6689be9c010000           mov       word ptr [esi + 0x19c], di
004a34c9 8bce                     mov       ecx, esi
004a34cb c645fc04                 mov       byte ptr [ebp - 4], 4
004a34cf e81c734100               call      0x8ba7f0
004a34d4 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004a34d7 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a34da 8b5508                   mov       edx, dword ptr [ebp + 8]
004a34dd 50                       push      eax
004a34de 51                       push      ecx
004a34df 52                       push      edx
004a34e0 8bce                     mov       ecx, esi
004a34e2 e8b96e4100               call      0x8ba3a0
004a34e7 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a34ea 5f                       pop       edi
004a34eb 8bc6                     mov       eax, esi
004a34ed 5e                       pop       esi
004a34ee 5b                       pop       ebx
004a34ef 64890d00000000           mov       dword ptr fs:[0], ecx
004a34f6 8be5                     mov       esp, ebp
004a34f8 5d                       pop       ebp
004a34f9 c20c00                   ret       0xc

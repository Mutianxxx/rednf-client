004a3820 55                       push      ebp
004a3821 8bec                     mov       ebp, esp
004a3823 6aff                     push      -1
004a3825 68486ec500               push      0xc56e48
004a382a 64a100000000             mov       eax, dword ptr fs:[0]
004a3830 50                       push      eax
004a3831 64892500000000           mov       dword ptr fs:[0], esp
004a3838 51                       push      ecx
004a3839 56                       push      esi
004a383a 8bf1                     mov       esi, ecx
004a383c 8975f0                   mov       dword ptr [ebp - 0x10], esi
004a383f e82c57f9ff               call      0x438f70
004a3844 8b4508                   mov       eax, dword ptr [ebp + 8]
004a3847 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a384a 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004a384d 50                       push      eax
004a384e 51                       push      ecx
004a384f 52                       push      edx
004a3850 8bce                     mov       ecx, esi
004a3852 c745fc00000000           mov       dword ptr [ebp - 4], 0
004a3859 c7065ceccc00             mov       dword ptr [esi], 0xccec5c
004a385f e8dcb9ffff               call      0x49f240
004a3864 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a3867 8bc6                     mov       eax, esi
004a3869 5e                       pop       esi
004a386a 64890d00000000           mov       dword ptr fs:[0], ecx
004a3871 8be5                     mov       esp, ebp
004a3873 5d                       pop       ebp
004a3874 c20c00                   ret       0xc

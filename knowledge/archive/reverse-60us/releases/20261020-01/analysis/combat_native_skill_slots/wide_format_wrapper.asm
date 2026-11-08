00401df0  55                       push       ebp
00401df1  8bec                     mov        ebp, esp
00401df3  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00401df6  d1e8                     shr        eax, 1
00401df8  3dffffff7f               cmp        eax, 0x7fffffff
00401dfd  7607                     jbe        0x401e06
00401dff  b857000780               mov        eax, 0x80070057
00401e04  5d                       pop        ebp
00401e05  c3                       ret        
00401e06  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00401e09  8d4d14                   lea        ecx, [ebp + 0x14]
00401e0c  51                       push       ecx
00401e0d  52                       push       edx
00401e0e  50                       push       eax
00401e0f  8b4508                   mov        eax, dword ptr [ebp + 8]
00401e12  50                       push       eax
00401e13  e8d8f3ffff               call       0x4011f0
00401e18  5d                       pop        ebp
00401e19  c3                       ret        

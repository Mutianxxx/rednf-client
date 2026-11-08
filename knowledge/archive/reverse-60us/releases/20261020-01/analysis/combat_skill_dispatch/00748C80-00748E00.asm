00748c80  0000                     add        byte ptr [eax], al
00748c82  0000                     add        byte ptr [eax], al
00748c84  0f8419010000             je         0x748da3
00748c8a  6a00                     push       0
00748c8c  8bc8                     mov        ecx, eax
00748c8e  e81dddffff               call       0x7469b0
00748c93  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748c96  64890d00000000           mov        dword ptr fs:[0], ecx
00748c9d  8be5                     mov        esp, ebp
00748c9f  5d                       pop        ebp
00748ca0  c3                       ret        
00748ca1  6814320000               push       0x3214
00748ca6  e8a5afcbff               call       0x403c50
00748cab  83c404                   add        esp, 4
00748cae  894508                   mov        dword ptr [ebp + 8], eax
00748cb1  85c0                     test       eax, eax
00748cb3  c745fc01000000           mov        dword ptr [ebp - 4], 1
00748cba  0f84e3000000             je         0x748da3
00748cc0  6a00                     push       0
00748cc2  8bc8                     mov        ecx, eax
00748cc4  e887e2ffff               call       0x746f50
00748cc9  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748ccc  64890d00000000           mov        dword ptr fs:[0], ecx
00748cd3  8be5                     mov        esp, ebp
00748cd5  5d                       pop        ebp
00748cd6  c3                       ret        
00748cd7  68bc320000               push       0x32bc
00748cdc  e86fafcbff               call       0x403c50
00748ce1  83c404                   add        esp, 4
00748ce4  894508                   mov        dword ptr [ebp + 8], eax
00748ce7  85c0                     test       eax, eax
00748ce9  c745fc02000000           mov        dword ptr [ebp - 4], 2
00748cf0  0f84ad000000             je         0x748da3
00748cf6  6a00                     push       0
00748cf8  8bc8                     mov        ecx, eax
00748cfa  e811e8ffff               call       0x747510
00748cff  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748d02  64890d00000000           mov        dword ptr fs:[0], ecx
00748d09  8be5                     mov        esp, ebp
00748d0b  5d                       pop        ebp
00748d0c  c3                       ret        
00748d0d  68dc330000               push       0x33dc
00748d12  e839afcbff               call       0x403c50
00748d17  83c404                   add        esp, 4
00748d1a  894508                   mov        dword ptr [ebp + 8], eax
00748d1d  85c0                     test       eax, eax
00748d1f  c745fc03000000           mov        dword ptr [ebp - 4], 3
00748d26  747b                     je         0x748da3
00748d28  6a00                     push       0
00748d2a  8bc8                     mov        ecx, eax
00748d2c  e83feeffff               call       0x747b70
00748d31  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748d34  64890d00000000           mov        dword ptr fs:[0], ecx
00748d3b  8be5                     mov        esp, ebp
00748d3d  5d                       pop        ebp
00748d3e  c3                       ret        
00748d3f  68482d0000               push       0x2d48
00748d44  e807afcbff               call       0x403c50
00748d49  83c404                   add        esp, 4
00748d4c  894508                   mov        dword ptr [ebp + 8], eax
00748d4f  85c0                     test       eax, eax
00748d51  c745fc04000000           mov        dword ptr [ebp - 4], 4
00748d58  7449                     je         0x748da3
00748d5a  6a00                     push       0
00748d5c  8bc8                     mov        ecx, eax
00748d5e  e87dfbffff               call       0x7488e0
00748d63  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748d66  64890d00000000           mov        dword ptr fs:[0], ecx
00748d6d  8be5                     mov        esp, ebp
00748d6f  5d                       pop        ebp
00748d70  c3                       ret        
00748d71  68bc320000               push       0x32bc
00748d76  e8d5aecbff               call       0x403c50
00748d7b  83c404                   add        esp, 4
00748d7e  894508                   mov        dword ptr [ebp + 8], eax
00748d81  85c0                     test       eax, eax
00748d83  c745fc05000000           mov        dword ptr [ebp - 4], 5
00748d8a  7417                     je         0x748da3
00748d8c  6a01                     push       1
00748d8e  8bc8                     mov        ecx, eax
00748d90  e87be7ffff               call       0x747510
00748d95  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748d98  64890d00000000           mov        dword ptr fs:[0], ecx
00748d9f  8be5                     mov        esp, ebp
00748da1  5d                       pop        ebp
00748da2  c3                       ret        
00748da3  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00748da6  33c0                     xor        eax, eax
00748da8  64890d00000000           mov        dword ptr fs:[0], ecx
00748daf  8be5                     mov        esp, ebp
00748db1  5d                       pop        ebp
00748db2  c3                       ret        
00748db3  90                       nop        
00748db4  6b8c7400a18c7400         imul       ecx, dword ptr [esp + esi*2 + 0x748ca100], 0
00748dbc  d7                       xlatb      
00748dbd  8c                       .byte      0x8c
00748dbe  7400                     je         0x748dc0
00748dc0  0d8d74003f               or         eax, 0x3f00748d
00748dc5  8d740071                 lea        esi, [eax + eax + 0x71]
00748dc9  8d7400cc                 lea        esi, [eax + eax - 0x34]
00748dcd  cc                       int3       
00748dce  cc                       int3       
00748dcf  cc                       int3       
00748dd0  e92ba4daff               jmp        0x4f3200
00748dd5  cc                       int3       
00748dd6  cc                       int3       
00748dd7  cc                       int3       
00748dd8  cc                       int3       
00748dd9  cc                       int3       
00748dda  cc                       int3       
00748ddb  cc                       int3       
00748ddc  cc                       int3       
00748ddd  cc                       int3       
00748dde  cc                       int3       
00748ddf  cc                       int3       
00748de0  56                       push       esi
00748de1  8bf1                     mov        esi, ecx
00748de3  8b8eb8270000             mov        ecx, dword ptr [esi + 0x27b8]
00748de9  85c9                     test       ecx, ecx
00748deb  740e                     je         0x748dfb
00748ded  8d8620250000             lea        eax, [esi + 0x2520]
00748df3  50                       push       eax
00748df4  e817dcdeff               call       0x536a10
00748df9  eb0e                     jmp        0x748e09
00748dfb  684c37d800               push       0xd8374c
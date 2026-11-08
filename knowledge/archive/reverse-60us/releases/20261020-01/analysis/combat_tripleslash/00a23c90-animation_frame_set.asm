00a23c90  56                       push       esi
00a23c91  57                       push       edi
00a23c92  8bf1                     mov        esi, ecx
00a23c94  6a00                     push       0
00a23c96  8d7e48                   lea        edi, [esi + 0x48]
00a23c99  6a00                     push       0
00a23c9b  8bcf                     mov        ecx, edi
00a23c9d  c6863801000001           mov        byte ptr [esi + 0x138], 1
00a23ca4  e8b7320e00               call       0xb06f60
00a23ca9  8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00a23caf  85c9                     test       ecx, ecx
00a23cb1  7407                     je         0xa23cba
00a23cb3  e88851a7ff               call       0x498e40
00a23cb8  eb06                     jmp        0xa23cc0
00a23cba  8a8639010000             mov        al, byte ptr [esi + 0x139]
00a23cc0  84c0                     test       al, al
00a23cc2  7405                     je         0xa23cc9
00a23cc4  5f                       pop        edi
00a23cc5  32c0                     xor        al, al
00a23cc7  5e                       pop        esi
00a23cc8  c3                       ret        
00a23cc9  8bcf                     mov        ecx, edi
00a23ccb  e830320e00               call       0xb06f00
00a23cd0  8b9688000000             mov        edx, dword ptr [esi + 0x88]
00a23cd6  8b8e8c000000             mov        ecx, dword ptr [esi + 0x8c]
00a23cdc  03c2                     add        eax, edx
00a23cde  3bc1                     cmp        eax, ecx
00a23ce0  74e2                     je         0xa23cc4
00a23ce2  89868c000000             mov        dword ptr [esi + 0x8c], eax
00a23ce8  5f                       pop        edi
00a23ce9  b001                     mov        al, 1
00a23ceb  5e                       pop        esi
00a23cec  c3                       ret        
00a23ced  cc                       int3       
00a23cee  cc                       int3       
00a23cef  cc                       int3       
00a23cf0  55                       push       ebp
00a23cf1  8bec                     mov        ebp, esp
00a23cf3  8a4508                   mov        al, byte ptr [ebp + 8]
00a23cf6  84c0                     test       al, al
00a23cf8  740e                     je         0xa23d08
00a23cfa  c705d03c0d0100000000     mov        dword ptr [0x10d3cd0], 0
00a23d04  32c0                     xor        al, al
00a23d06  5d                       pop        ebp
00a23d07  c3                       ret        
00a23d08  a1d03c0d01               mov        eax, dword ptr [0x10d3cd0]
00a23d0d  40                       inc        eax
00a23d0e  3de8030000               cmp        eax, 0x3e8
00a23d13  a3d03c0d01               mov        dword ptr [0x10d3cd0], eax
00a23d18  7eea                     jle        0xa23d04
00a23d1a  b001                     mov        al, 1
00a23d1c  5d                       pop        ebp
00a23d1d  c3                       ret        
00a23d1e  cc                       int3       
00a23d1f  cc                       int3       
00a23d20  8b8188010000             mov        eax, dword ptr [ecx + 0x188]
00a23d26  85c0                     test       eax, eax
00a23d28  752e                     jne        0xa23d58
00a23d2a  8a8140010000             mov        al, byte ptr [ecx + 0x140]
00a23d30  84c0                     test       al, al
00a23d32  7424                     je         0xa23d58
00a23d34  8b8160010000             mov        eax, dword ptr [ecx + 0x160]
00a23d3a  8b                       .byte      0x8b
00a23d3b  91                       xchg       ecx, eax

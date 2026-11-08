00a24dc0  55                       push       ebp
00a24dc1  8bec                     mov        ebp, esp
00a24dc3  8b8980010000             mov        ecx, dword ptr [ecx + 0x180]
00a24dc9  8b01                     mov        eax, dword ptr [ecx]
00a24dcb  3bc1                     cmp        eax, ecx
00a24dcd  740e                     je         0xa24ddd
00a24dcf  8b5508                   mov        edx, dword ptr [ebp + 8]
00a24dd2  39500c                   cmp        dword ptr [eax + 0xc], edx
00a24dd5  7412                     je         0xa24de9
00a24dd7  8b00                     mov        eax, dword ptr [eax]
00a24dd9  3bc1                     cmp        eax, ecx
00a24ddb  75f5                     jne        0xa24dd2
00a24ddd  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a24de0  c60200                   mov        byte ptr [edx], 0
00a24de3  33c0                     xor        eax, eax
00a24de5  5d                       pop        ebp
00a24de6  c20800                   ret        8
00a24de9  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a24dec  c60101                   mov        byte ptr [ecx], 1
00a24def  8b4008                   mov        eax, dword ptr [eax + 8]
00a24df2  5d                       pop        ebp
00a24df3  c20800                   ret        8

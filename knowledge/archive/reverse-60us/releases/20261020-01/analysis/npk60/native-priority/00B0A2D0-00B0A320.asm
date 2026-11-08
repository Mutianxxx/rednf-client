00b0a2d0  55                       push       ebp
00b0a2d1  8bec                     mov        ebp, esp
00b0a2d3  56                       push       esi
00b0a2d4  57                       push       edi
00b0a2d5  8b7d08                   mov        edi, dword ptr [ebp + 8]
00b0a2d8  33f6                     xor        esi, esi
00b0a2da  8d9b00000000             lea        ebx, [ebx]
00b0a2e0  33c0                     xor        eax, eax
00b0a2e2  668b0477                 mov        ax, word ptr [edi + esi*2]
00b0a2e6  6685c0                   test       ax, ax
00b0a2e9  7416                     je         0xb0a301
00b0a2eb  50                       push       eax
00b0a2ec  e8439a0f00               call       0xc03d34
00b0a2f1  83c404                   add        esp, 4
00b0a2f4  66890477                 mov        word ptr [edi + esi*2], ax
00b0a2f8  46                       inc        esi
00b0a2f9  81fe00010000             cmp        esi, 0x100
00b0a2ff  7cdf                     jl         0xb0a2e0
00b0a301  5f                       pop        edi
00b0a302  5e                       pop        esi
00b0a303  5d                       pop        ebp
00b0a304  c3                       ret        
00b0a305  cc                       int3       
00b0a306  cc                       int3       
00b0a307  cc                       int3       
00b0a308  cc                       int3       
00b0a309  cc                       int3       
00b0a30a  cc                       int3       
00b0a30b  cc                       int3       
00b0a30c  cc                       int3       
00b0a30d  cc                       int3       
00b0a30e  cc                       int3       
00b0a30f  cc                       int3       
00b0a310  55                       push       ebp
00b0a311  8bec                     mov        ebp, esp
00b0a313  8b5508                   mov        edx, dword ptr [ebp + 8]
00b0a316  85d2                     test       edx, edx
00b0a318  7504                     jne        0xb0a31e
00b0a31a  33c0                     xor        eax, eax
00b0a31c  5d                       pop        ebp
00b0a31d  c3                       ret        
00b0a31e  8bc2                     mov        eax, edx
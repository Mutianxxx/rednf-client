00485580  55                       push       ebp
00485581  8bec                     mov        ebp, esp
00485583  51                       push       ecx
00485584  8b4508                   mov        eax, dword ptr [ebp + 8]
00485587  53                       push       ebx
00485588  56                       push       esi
00485589  8bf1                     mov        esi, ecx
0048558b  99                       cdq        
0048558c  b90e000000               mov        ecx, 0xe
00485591  f7f9                     idiv       ecx
00485593  57                       push       edi
00485594  8bd8                     mov        ebx, eax
00485596  8b8618020000             mov        eax, dword ptr [esi + 0x218]
0048559c  85c0                     test       eax, eax
0048559e  895508                   mov        dword ptr [ebp + 8], edx
004855a1  741e                     je         0x4855c1
004855a3  8b8e1c020000             mov        ecx, dword ptr [esi + 0x21c]
004855a9  2bc8                     sub        ecx, eax
004855ab  b8398ee338               mov        eax, 0x38e38e39
004855b0  f7e9                     imul       ecx
004855b2  c1fa03                   sar        edx, 3
004855b5  8bc2                     mov        eax, edx
004855b7  c1e81f                   shr        eax, 0x1f
004855ba  03c2                     add        eax, edx
004855bc  8945fc                   mov        dword ptr [ebp - 4], eax
004855bf  7504                     jne        0x4855c5
004855c1  33c0                     xor        eax, eax
004855c3  eb19                     jmp        0x4855de
004855c5  8b8618020000             mov        eax, dword ptr [esi + 0x218]
004855cb  8b4818                   mov        ecx, dword ptr [eax + 0x18]
004855ce  85c9                     test       ecx, ecx
004855d0  7504                     jne        0x4855d6
004855d2  33c0                     xor        eax, eax
004855d4  eb08                     jmp        0x4855de
004855d6  8b401c                   mov        eax, dword ptr [eax + 0x1c]
004855d9  2bc1                     sub        eax, ecx
004855db  c1f804                   sar        eax, 4
004855de  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
004855e1  3bf8                     cmp        edi, eax
004855e3  7d35                     jge        0x48561a
004855e5  8b8618020000             mov        eax, dword ptr [esi + 0x218]
004855eb  85c0                     test       eax, eax
004855ed  744d                     je         0x48563c
004855ef  8b8e1c020000             mov        ecx, dword ptr [esi + 0x21c]
004855f5  2bc8                     sub        ecx, eax
004855f7  b8398ee338               mov        eax, 0x38e38e39
004855fc  f7e9                     imul       ecx
004855fe  c1fa03                   sar        edx, 3
00485601  8bc2                     mov        eax, edx
00485603  c1e81f                   shr        eax, 0x1f
00485606  03c2                     add        eax, edx
00485608  3bd8                     cmp        ebx, eax
0048560a  7330                     jae        0x48563c
0048560c  8b9618020000             mov        edx, dword ptr [esi + 0x218]
00485612  8d0cdb                   lea        ecx, [ebx + ebx*8]
00485615  8d048a                   lea        eax, [edx + ecx*4]
00485618  eb1e                     jmp        0x485638
0048561a  8bce                     mov        ecx, esi
0048561c  e8bf150000               call       0x486be0
00485621  2bf8                     sub        edi, eax
00485623  8bc7                     mov        eax, edi
00485625  99                       cdq        
00485626  b90a000000               mov        ecx, 0xa
0048562b  f7f9                     idiv       ecx
0048562d  53                       push       ebx
0048562e  8bce                     mov        ecx, esi
00485630  50                       push       eax
00485631  8bfa                     mov        edi, edx
00485633  e848150000               call       0x486b80
00485638  85c0                     test       eax, eax
0048563a  750e                     jne        0x48564a
0048563c  5f                       pop        edi
0048563d  5e                       pop        esi
0048563e  b802000000               mov        eax, 2
00485643  5b                       pop        ebx
00485644  8be5                     mov        esp, ebp
00485646  5d                       pop        ebp
00485647  c20800                   ret        8
0048564a  8b4818                   mov        ecx, dword ptr [eax + 0x18]
0048564d  8b4508                   mov        eax, dword ptr [ebp + 8]
00485650  c1e704                   shl        edi, 4
00485653  8b540f04                 mov        edx, dword ptr [edi + ecx + 4]
00485657  03f9                     add        edi, ecx
00485659  5f                       pop        edi
0048565a  8d0482                   lea        eax, [edx + eax*4]
0048565d  8b00                     mov        eax, dword ptr [eax]
0048565f  5e                       pop        esi
00485660  5b                       pop        ebx
00485661  8be5                     mov        esp, ebp
00485663  5d                       pop        ebp
00485664  c20800                   ret        8

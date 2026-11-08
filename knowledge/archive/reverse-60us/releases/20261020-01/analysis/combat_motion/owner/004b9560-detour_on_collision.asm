004b9560  55                       push       ebp
004b9561  8bec                     mov        ebp, esp
004b9563  83ec1c                   sub        esp, 0x1c
004b9566  56                       push       esi
004b9567  8bf1                     mov        esi, ecx
004b9569  83be78160000ff           cmp        dword ptr [esi + 0x1678], -1
004b9570  0f85cf010000             jne        0x4b9745
004b9576  57                       push       edi
004b9577  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b957a  85ff                     test       edi, edi
004b957c  7432                     je         0x4b95b0
004b957e  83ff01                   cmp        edi, 1
004b9581  0f85bd010000             jne        0x4b9744
004b9587  8b16                     mov        edx, dword ptr [esi]
004b9589  ff92e0000000             call       dword ptr [edx + 0xe0]
004b958f  53                       push       ebx
004b9590  bb04000000               mov        ebx, 4
004b9595  3bc3                     cmp        eax, ebx
004b9597  8945fc                   mov        dword ptr [ebp - 4], eax
004b959a  0f84a3010000             je         0x4b9743
004b95a0  85ff                     test       edi, edi
004b95a2  8bce                     mov        ecx, esi
004b95a4  7516                     jne        0x4b95bc
004b95a6  8b06                     mov        eax, dword ptr [esi]
004b95a8  ff90e0000000             call       dword ptr [eax + 0xe0]
004b95ae  eb14                     jmp        0x4b95c4
004b95b0  8b06                     mov        eax, dword ptr [esi]
004b95b2  8bce                     mov        ecx, esi
004b95b4  ff90dc000000             call       dword ptr [eax + 0xdc]
004b95ba  ebd3                     jmp        0x4b958f
004b95bc  8b16                     mov        edx, dword ptr [esi]
004b95be  ff92dc000000             call       dword ptr [edx + 0xdc]
004b95c4  3bc3                     cmp        eax, ebx
004b95c6  8945f8                   mov        dword ptr [ebp - 8], eax
004b95c9  0f8574010000             jne        0x4b9743
004b95cf  33c0                     xor        eax, eax
004b95d1  85ff                     test       edi, edi
004b95d3  0f95c0                   setne      al
004b95d6  c745f400000000           mov        dword ptr [ebp - 0xc], 0
004b95dd  8d04850d000000           lea        eax, [eax*4 + 0xd]
004b95e4  85c0                     test       eax, eax
004b95e6  8945ec                   mov        dword ptr [ebp - 0x14], eax
004b95e9  0f8eea000000             jle        0x4b96d9
004b95ef  8d04bd00000000           lea        eax, [edi*4]
004b95f6  8d5de8                   lea        ebx, [ebp - 0x18]
004b95f9  2bd8                     sub        ebx, eax
004b95fb  c745f000000000           mov        dword ptr [ebp - 0x10], 0
004b9602  8b06                     mov        eax, dword ptr [esi]
004b9604  8bce                     mov        ecx, esi
004b9606  ff9094000000             call       dword ptr [eax + 0x94]
004b960c  8b16                     mov        edx, dword ptr [esi]
004b960e  8bce                     mov        ecx, esi
004b9610  8945e4                   mov        dword ptr [ebp - 0x1c], eax
004b9613  ff9298000000             call       dword ptr [edx + 0x98]
004b9619  8945e8                   mov        dword ptr [ebp - 0x18], eax
004b961c  8b45fc                   mov        eax, dword ptr [ebp - 4]
004b961f  85c0                     test       eax, eax
004b9621  7417                     je         0x4b963a
004b9623  83f802                   cmp        eax, 2
004b9626  7412                     je         0x4b963a
004b9628  8d04bd00000000           lea        eax, [edi*4]
004b962f  8b4c05e4                 mov        ecx, dword ptr [ebp + eax - 0x1c]
004b9633  8d4405e4                 lea        eax, [ebp + eax - 0x1c]
004b9637  41                       inc        ecx
004b9638  eb10                     jmp        0x4b964a
004b963a  8d04bd00000000           lea        eax, [edi*4]
004b9641  8b4c05e4                 mov        ecx, dword ptr [ebp + eax - 0x1c]
004b9645  8d4405e4                 lea        eax, [ebp + eax - 0x1c]
004b9649  49                       dec        ecx
004b964a  8b16                     mov        edx, dword ptr [esi]
004b964c  8908                     mov        dword ptr [eax], ecx
004b964e  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
004b9651  8b0b                     mov        ecx, dword ptr [ebx]
004b9653  40                       inc        eax
004b9654  03c8                     add        ecx, eax
004b9656  890b                     mov        dword ptr [ebx], ecx
004b9658  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004b965b  6a00                     push       0
004b965d  8bf9                     mov        edi, ecx
004b965f  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004b9662  50                       push       eax
004b9663  51                       push       ecx
004b9664  8bce                     mov        ecx, esi
004b9666  ff92ac000000             call       dword ptr [edx + 0xac]
004b966c  84c0                     test       al, al
004b966e  7542                     jne        0x4b96b2
004b9670  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004b9673  8b16                     mov        edx, dword ptr [esi]
004b9675  2bf9                     sub        edi, ecx
004b9677  83ef02                   sub        edi, 2
004b967a  893b                     mov        dword ptr [ebx], edi
004b967c  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004b967f  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
004b9682  6a00                     push       0
004b9684  50                       push       eax
004b9685  51                       push       ecx
004b9686  8bce                     mov        ecx, esi
004b9688  ff92ac000000             call       dword ptr [edx + 0xac]
004b968e  84c0                     test       al, al
004b9690  7533                     jne        0x4b96c5
004b9692  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
004b9695  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
004b9698  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
004b969b  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b969e  40                       inc        eax
004b969f  83c202                   add        edx, 2
004b96a2  3bc1                     cmp        eax, ecx
004b96a4  8945f4                   mov        dword ptr [ebp - 0xc], eax
004b96a7  8955f0                   mov        dword ptr [ebp - 0x10], edx
004b96aa  0f8c52ffffff             jl         0x4b9602
004b96b0  eb27                     jmp        0x4b96d9
004b96b2  8b4508                   mov        eax, dword ptr [ebp + 8]
004b96b5  33d2                     xor        edx, edx
004b96b7  85c0                     test       eax, eax
004b96b9  0f94c2                   sete       dl
004b96bc  8d541201                 lea        edx, [edx + edx + 1]
004b96c0  8955f8                   mov        dword ptr [ebp - 8], edx
004b96c3  eb11                     jmp        0x4b96d6
004b96c5  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b96c8  33c0                     xor        eax, eax
004b96ca  85ff                     test       edi, edi
004b96cc  0f95c0                   setne      al
004b96cf  48                       dec        eax
004b96d0  83e002                   and        eax, 2
004b96d3  8945f8                   mov        dword ptr [ebp - 8], eax
004b96d6  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b96d9  8b5df8                   mov        ebx, dword ptr [ebp - 8]
004b96dc  8b55fc                   mov        edx, dword ptr [ebp - 4]
004b96df  b901000000               mov        ecx, 1
004b96e4  2bcf                     sub        ecx, edi
004b96e6  85ff                     test       edi, edi
004b96e8  898e78160000             mov        dword ptr [esi + 0x1678], ecx
004b96ee  899e7c160000             mov        dword ptr [esi + 0x167c], ebx
004b96f4  899680160000             mov        dword ptr [esi + 0x1680], edx
004b96fa  8bce                     mov        ecx, esi
004b96fc  750a                     jne        0x4b9708
004b96fe  8b06                     mov        eax, dword ptr [esi]
004b9700  ff9094000000             call       dword ptr [eax + 0x94]
004b9706  eb08                     jmp        0x4b9710
004b9708  8b16                     mov        edx, dword ptr [esi]
004b970a  ff9298000000             call       dword ptr [edx + 0x98]
004b9710  85ff                     test       edi, edi
004b9712  898684160000             mov        dword ptr [esi + 0x1684], eax
004b9718  6a00                     push       0
004b971a  7518                     jne        0x4b9734
004b971c  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b971f  8b06                     mov        eax, dword ptr [esi]
004b9721  53                       push       ebx
004b9722  51                       push       ecx
004b9723  8bce                     mov        ecx, esi
004b9725  ff909c040000             call       dword ptr [eax + 0x49c]
004b972b  5b                       pop        ebx
004b972c  5f                       pop        edi
004b972d  5e                       pop        esi
004b972e  8be5                     mov        esp, ebp
004b9730  5d                       pop        ebp
004b9731  c20400                   ret        4
004b9734  8b45fc                   mov        eax, dword ptr [ebp - 4]
004b9737  8b16                     mov        edx, dword ptr [esi]
004b9739  50                       push       eax
004b973a  53                       push       ebx
004b973b  8bce                     mov        ecx, esi
004b973d  ff929c040000             call       dword ptr [edx + 0x49c]
004b9743  5b                       pop        ebx
004b9744  5f                       pop        edi
004b9745  5e                       pop        esi
004b9746  8be5                     mov        esp, ebp
004b9748  5d                       pop        ebp
004b9749  c20400                   ret        4

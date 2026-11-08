0049f4d0  55                       push       ebp
0049f4d1  8bec                     mov        ebp, esp
0049f4d3  6aff                     push       -1
0049f4d5  68db6bc500               push       0xc56bdb
0049f4da  64a100000000             mov        eax, dword ptr fs:[0]
0049f4e0  50                       push       eax
0049f4e1  64892500000000           mov        dword ptr fs:[0], esp
0049f4e8  81ec98030000             sub        esp, 0x398
0049f4ee  53                       push       ebx
0049f4ef  8b5d08                   mov        ebx, dword ptr [ebp + 8]
0049f4f2  56                       push       esi
0049f4f3  57                       push       edi
0049f4f4  53                       push       ebx
0049f4f5  8bf1                     mov        esi, ecx
0049f4f7  8b0de4300001             mov        ecx, dword ptr [0x10030e4]
0049f4fd  6a00                     push       0
0049f4ff  e82cd96d00               call       0xb7ce30
0049f504  8bf8                     mov        edi, eax
0049f506  85ff                     test       edi, edi
0049f508  7522                     jne        0x49f52c
0049f50a  53                       push       ebx
0049f50b  6870f0cc00               push       0xccf070
0049f510  ff15bc2eff00             call       dword ptr [0xff2ebc]
0049f516  83c408                   add        esp, 8
0049f519  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0049f51c  64890d00000000           mov        dword ptr fs:[0], ecx
0049f523  5f                       pop        edi
0049f524  5e                       pop        esi
0049f525  5b                       pop        ebx
0049f526  8be5                     mov        esp, ebp
0049f528  5d                       pop        ebp
0049f529  c20800                   ret        8
0049f52c  8a8774010000             mov        al, byte ptr [edi + 0x174]
0049f532  84c0                     test       al, al
0049f534  7413                     je         0x49f549
0049f536  8b0d48280001             mov        ecx, dword ptr [0x1002848]
0049f53c  e88fb0f9ff               call       0x43a5d0
0049f541  84c0                     test       al, al
0049f543  0f84d6120000             je         0x4a081f
0049f549  8d8fa4000000             lea        ecx, [edi + 0xa4]
0049f54f  e89c3b5b00               call       0xa530f0
0049f554  8bd8                     mov        ebx, eax
0049f556  53                       push       ebx
0049f557  e871087600               call       0xbffdcd
0049f55c  83c404                   add        esp, 4
0049f55f  50                       push       eax
0049f560  53                       push       ebx
0049f561  8d8e44020000             lea        ecx, [esi + 0x244]
0049f567  e81439f6ff               call       0x402e80
0049f56c  8b450c                   mov        eax, dword ptr [ebp + 0xc]
0049f56f  898644050000             mov        dword ptr [esi + 0x544], eax
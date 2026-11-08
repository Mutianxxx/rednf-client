007307b0  55                       push       ebp
007307b1  8bec                     mov        ebp, esp
007307b3  6aff                     push       -1
007307b5  689c1ac700               push       0xc71a9c
007307ba  64a100000000             mov        eax, dword ptr fs:[0]
007307c0  50                       push       eax
007307c1  64892500000000           mov        dword ptr fs:[0], esp
007307c8  81eccc000000             sub        esp, 0xcc
007307ce  53                       push       ebx
007307cf  56                       push       esi
007307d0  8bf1                     mov        esi, ecx
007307d2  57                       push       edi
007307d3  8d8e5c150000             lea        ecx, [esi + 0x155c]
007307d9  e88218cdff               call       0x402060
007307de  8bd8                     mov        ebx, eax
007307e0  33c0                     xor        eax, eax
007307e2  b907000000               mov        ecx, 7
007307e7  895de0                   mov        dword ptr [ebp - 0x20], ebx
007307ea  898d70ffffff             mov        dword ptr [ebp - 0x90], ecx
007307f0  89856cffffff             mov        dword ptr [ebp - 0x94], eax
007307f6  6689855cffffff           mov        word ptr [ebp - 0xa4], ax
007307fd  8b7d08                   mov        edi, dword ptr [ebp + 8]
00730800  8945fc                   mov        dword ptr [ebp - 4], eax
00730803  8d43f9                   lea        eax, [ebx - 7]
00730806  83f82e                   cmp        eax, 0x2e
00730809  0f8797100000             ja         0x7318a6
0073080f  ff248548d47300           jmp        dword ptr [eax*4 + 0x73d448]
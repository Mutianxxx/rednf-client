00490720  55                       push       ebp
00490721  8bec                     mov        ebp, esp
00490723  6aff                     push       -1
00490725  68ea5dc500               push       0xc55dea
0049072a  64a100000000             mov        eax, dword ptr fs:[0]
00490730  50                       push       eax
00490731  64892500000000           mov        dword ptr fs:[0], esp
00490738  83ec08                   sub        esp, 8
0049073b  56                       push       esi
0049073c  8bf1                     mov        esi, ecx
0049073e  57                       push       edi
0049073f  8975f0                   mov        dword ptr [ebp - 0x10], esi
00490742  e8a97dfaff               call       0x4384f0
00490747  33ff                     xor        edi, edi
00490749  8d8e24050000             lea        ecx, [esi + 0x524]
0049074f  897dfc                   mov        dword ptr [ebp - 4], edi
00490752  c706d4b7cb00             mov        dword ptr [esi], 0xcbb7d4
00490758  e87373faff               call       0x437ad0
0049075d  8d8edc050000             lea        ecx, [esi + 0x5dc]
00490763  c645fc01                 mov        byte ptr [ebp - 4], 1
00490767  e8c475faff               call       0x437d30
0049076c  c786d407000007000000     mov        dword ptr [esi + 0x7d4], 7
00490776  89bed0070000             mov        dword ptr [esi + 0x7d0], edi
0049077c  6689bec0070000           mov        word ptr [esi + 0x7c0], di
00490783  8d8eec070000             lea        ecx, [esi + 0x7ec]
00490789  c645fc03                 mov        byte ptr [ebp - 4], 3
0049078d  e84e3df7ff               call       0x4044e0
00490792  c7860c08000007000000     mov        dword ptr [esi + 0x80c], 7
0049079c  89be08080000             mov        dword ptr [esi + 0x808], edi
004907a2  6689bef8070000           mov        word ptr [esi + 0x7f8], di
004907a9  89be20080000             mov        dword ptr [esi + 0x820], edi
004907af  89be24080000             mov        dword ptr [esi + 0x824], edi
004907b5  89be28080000             mov        dword ptr [esi + 0x828], edi
004907bb  89be34080000             mov        dword ptr [esi + 0x834], edi
004907c1  89be38080000             mov        dword ptr [esi + 0x838], edi
004907c7  89be3c080000             mov        dword ptr [esi + 0x83c], edi
004907cd  89be44080000             mov        dword ptr [esi + 0x844], edi
004907d3  89be48080000             mov        dword ptr [esi + 0x848], edi
004907d9  89be4c080000             mov        dword ptr [esi + 0x84c], edi
004907df  6810204000               push       0x402010
004907e4  68e0444000               push       0x4044e0
004907e9  6a03                     push       3
004907eb  6a08                     push       8
004907ed  8d8650080000             lea        eax, [esi + 0x850]
004907f3  50                       push       eax
004907f4  c645fc08                 mov        byte ptr [ebp - 4], 8
004907f8  e867007700               call       0xc00864
004907fd  8bce                     mov        ecx, esi
004907ff  c645fc09                 mov        byte ptr [ebp - 4], 9
00490803  e868e60000               call       0x49ee70
00490808  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0049080b  8b5508                   mov        edx, dword ptr [ebp + 8]
0049080e  51                       push       ecx
0049080f  52                       push       edx
00490810  8bce                     mov        ecx, esi
00490812  e889050100               call       0x4a0da0
00490817  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0049081a  5f                       pop        edi
0049081b  8bc6                     mov        eax, esi
0049081d  5e                       pop        esi
0049081e  64890d00000000           mov        dword ptr fs:[0], ecx
00490825  8be5                     mov        esp, ebp
00490827  5d                       pop        ebp
00490828  c20800                   ret        8
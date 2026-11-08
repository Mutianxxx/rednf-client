0049a0a0 55                       push       ebp
0049a0a1 8bec                     mov        ebp, esp
0049a0a3 8bc1                     mov        eax, ecx
0049a0a5 837d100d                 cmp        dword ptr [ebp + 0x10], 0xd
0049a0a9 751b                     jne        0x49a0c6
0049a0ab 8b8854010000             mov        ecx, dword ptr [eax + 0x154]
0049a0b1 85c9                     test       ecx, ecx
0049a0b3 7411                     je         0x49a0c6
0049a0b5 8b450c                   mov        eax, dword ptr [ebp + 0xc]
0049a0b8 8b5508                   mov        edx, dword ptr [ebp + 8]
0049a0bb 50                       push       eax
0049a0bc 52                       push       edx
0049a0bd e88ebf5900               call       0xa36050
0049a0c2 5d                       pop        ebp
0049a0c3 c21000                   ret        0x10
0049a0c6 8b8848010000             mov        ecx, dword ptr [eax + 0x148]
0049a0cc 85c9                     test       ecx, ecx
0049a0ce 75e5                     jne        0x49a0b5

00499050  55                       push       ebp
00499051  8bec                     mov        ebp, esp
00499053  8b4508                   mov        eax, dword ptr [ebp + 8]
00499056  56                       push       esi
00499057  8bf1                     mov        esi, ecx
00499059  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
0049905f  50                       push       eax
00499060  6a00                     push       0
00499062  e8e97e0700               call       0x510f50
00499067  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0049906a  51                       push       ecx
0049906b  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
00499071  6a01                     push       1
00499073  e8d87e0700               call       0x510f50
00499078  8b5510                   mov        edx, dword ptr [ebp + 0x10]
0049907b  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
00499081  52                       push       edx
00499082  6a02                     push       2
00499084  e8c77e0700               call       0x510f50
00499089  5e                       pop        esi
0049908a  5d                       pop        ebp
0049908b  c20c00                   ret        0xc

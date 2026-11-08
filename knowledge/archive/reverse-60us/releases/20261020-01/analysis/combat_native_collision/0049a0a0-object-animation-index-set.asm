0049a0a0 55                       push      ebp
0049a0a1 8bec                     mov       ebp, esp
0049a0a3 8bc1                     mov       eax, ecx
0049a0a5 837d100d                 cmp       dword ptr [ebp + 0x10], 0xd
0049a0a9 751b                     jne       0x49a0c6
0049a0ab 8b8854010000             mov       ecx, dword ptr [eax + 0x154]
0049a0b1 85c9                     test      ecx, ecx
0049a0b3 7411                     je        0x49a0c6
0049a0b5 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049a0b8 8b5508                   mov       edx, dword ptr [ebp + 8]
0049a0bb 50                       push      eax
0049a0bc 52                       push      edx
0049a0bd e88ebf5900               call      0xa36050
0049a0c2 5d                       pop       ebp
0049a0c3 c21000                   ret       0x10
0049a0c6 8b8848010000             mov       ecx, dword ptr [eax + 0x148]
0049a0cc 85c9                     test      ecx, ecx
0049a0ce 75e5                     jne       0x49a0b5
0049a0d0 51                       push      ecx
0049a0d1 687c28f400               push      0xf4287c
0049a0d6 681009f400               push      0xf40910
0049a0db 51                       push      ecx
0049a0dc 50                       push      eax
0049a0dd e8296c7600               call      0xc00d0b
0049a0e2 83c414                   add       esp, 0x14
0049a0e5 85c0                     test      eax, eax
0049a0e7 744b                     je        0x49a134
0049a0e9 56                       push      esi
0049a0ea 8db008020000             lea       esi, [eax + 0x208]
0049a0f0 8bce                     mov       ecx, esi
0049a0f2 e8f98f5b00               call      0xa530f0
0049a0f7 3de0baca00               cmp       eax, 0xcabae0
0049a0fc 7517                     jne       0x49a115
0049a0fe 8b4508                   mov       eax, dword ptr [ebp + 8]
0049a101 50                       push      eax
0049a102 6848eacc00               push      0xccea48
0049a107 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049a10d 83c408                   add       esp, 8
0049a110 5e                       pop       esi
0049a111 5d                       pop       ebp
0049a112 c21000                   ret       0x10
0049a115 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049a118 51                       push      ecx
0049a119 8bce                     mov       ecx, esi
0049a11b e8d08f5b00               call      0xa530f0
0049a120 50                       push      eax
0049a121 68f8e9cc00               push      0xcce9f8
0049a126 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049a12c 83c40c                   add       esp, 0xc
0049a12f 5e                       pop       esi
0049a130 5d                       pop       ebp
0049a131 c21000                   ret       0x10
0049a134 8b5508                   mov       edx, dword ptr [ebp + 8]
0049a137 52                       push      edx
0049a138 6890e9cc00               push      0xcce990
0049a13d ff15bc2eff00             call      dword ptr [0xff2ebc]
0049a143 83c408                   add       esp, 8
0049a146 5d                       pop       ebp
0049a147 c21000                   ret       0x10
0049a14a cc                       int3      
0049a14b cc                       int3      
0049a14c cc                       int3      
0049a14d cc                       int3      
0049a14e cc                       int3      
0049a14f cc                       int3      

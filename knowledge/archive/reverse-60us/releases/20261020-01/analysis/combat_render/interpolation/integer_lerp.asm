00473f20 55                       push       ebp
00473f21 8bec                     mov        ebp, esp
00473f23 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00473f26 db450c                   fild       dword ptr [ebp + 0xc]
00473f29 8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00473f2c 50                       push       eax
00473f2d 51                       push       ecx
00473f2e 83ec08                   sub        esp, 8
00473f31 d95c2404                 fstp       dword ptr [esp + 4]
00473f35 db4508                   fild       dword ptr [ebp + 8]
00473f38 d91c24                   fstp       dword ptr [esp]
00473f3b e8705a6900               call       0xb099b0
00473f40 83c410                   add        esp, 0x10
00473f43 5d                       pop        ebp
00473f44 e9fbd57800               jmp        0xc01544

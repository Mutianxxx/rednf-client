00499370 55                       push      ebp
00499371 8bec                     mov       ebp, esp
00499373 6aff                     push      -1
00499375 68db69c500               push      0xc569db
0049937a 64a100000000             mov       eax, dword ptr fs:[0]
00499380 50                       push      eax
00499381 64892500000000           mov       dword ptr fs:[0], esp
00499388 51                       push      ecx
00499389 57                       push      edi
0049938a 8bf9                     mov       edi, ecx
0049938c 8b8790010000             mov       eax, dword ptr [edi + 0x190]
00499392 85c0                     test      eax, eax
00499394 7535                     jne       0x4993cb
00499396 56                       push      esi
00499397 6a18                     push      0x18
00499399 e87f457500               call      0xbed91d
0049939e 8bf0                     mov       esi, eax

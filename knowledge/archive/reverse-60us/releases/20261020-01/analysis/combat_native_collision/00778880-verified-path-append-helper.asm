00778880 55                       push      ebp
00778881 8bec                     mov       ebp, esp
00778883 6aff                     push      -1
00778885 68987cc700               push      0xc77c98
0077888a 64a100000000             mov       eax, dword ptr fs:[0]
00778890 50                       push      eax
00778891 64892500000000           mov       dword ptr fs:[0], esp
00778898 83ec20                   sub       esp, 0x20
0077889b 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0077889e 56                       push      esi
0077889f 57                       push      edi
007788a0 33ff                     xor       edi, edi
007788a2 6aff                     push      -1
007788a4 57                       push      edi
007788a5 50                       push      eax
007788a6 8d4dd4                   lea       ecx, [ebp - 0x2c]
007788a9 897df0                   mov       dword ptr [ebp - 0x10], edi
007788ac c745ec07000000           mov       dword ptr [ebp - 0x14], 7
007788b3 897de8                   mov       dword ptr [ebp - 0x18], edi
007788b6 66897dd8                 mov       word ptr [ebp - 0x28], di
007788ba e8a1a4c8ff               call      0x402d60
007788bf 8b7510                   mov       esi, dword ptr [ebp + 0x10]
007788c2 56                       push      esi
007788c3 897dfc                   mov       dword ptr [ebp - 4], edi
007788c6 e802754800               call      0xbffdcd
007788cb 83c404                   add       esp, 4
007788ce 50                       push      eax
007788cf 56                       push      esi
007788d0 8d4dd4                   lea       ecx, [ebp - 0x2c]
007788d3 e80861c9ff               call      0x40e9e0
007788d8 8b7508                   mov       esi, dword ptr [ebp + 8]
007788db 6aff                     push      -1
007788dd 57                       push      edi
007788de c7461807000000           mov       dword ptr [esi + 0x18], 7
007788e5 897e14                   mov       dword ptr [esi + 0x14], edi
007788e8 50                       push      eax
007788e9 8bce                     mov       ecx, esi
007788eb 66897e04                 mov       word ptr [esi + 4], di
007788ef e86ca4c8ff               call      0x402d60
007788f4 837dec08                 cmp       dword ptr [ebp - 0x14], 8
007788f8 720c                     jb        0x778906
007788fa 8b4dd8                   mov       ecx, dword ptr [ebp - 0x28]
007788fd 51                       push      ecx
007788fe e8da764800               call      0xbfffdd
00778903 83c404                   add       esp, 4
00778906 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00778909 5f                       pop       edi
0077890a 8bc6                     mov       eax, esi
0077890c 5e                       pop       esi
0077890d 64890d00000000           mov       dword ptr fs:[0], ecx
00778914 8be5                     mov       esp, ebp
00778916 5d                       pop       ebp
00778917 c3                       ret       

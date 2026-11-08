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
00778918 cc                       int3      
00778919 cc                       int3      
0077891a cc                       int3      
0077891b cc                       int3      
0077891c cc                       int3      
0077891d cc                       int3      
0077891e cc                       int3      
0077891f cc                       int3      
00778920 56                       push      esi
00778921 8bf1                     mov       esi, ecx
00778923 8b8e50280000             mov       ecx, dword ptr [esi + 0x2850]
00778929 85c9                     test      ecx, ecx
0077892b 7406                     je        0x778933
0077892d 8b01                     mov       eax, dword ptr [ecx]
0077892f 6a01                     push      1
00778931 ff10                     call      dword ptr [eax]
00778933 c7865028000000000000     mov       dword ptr [esi + 0x2850], 0
0077893d 5e                       pop       esi
0077893e c3                       ret       
0077893f cc                       int3      
00778940 55                       push      ebp
00778941 8bec                     mov       ebp, esp
00778943 8a4508                   mov       al, byte ptr [ebp + 8]
00778946 88814c280000             mov       byte ptr [ecx + 0x284c], al
0077894c 5d                       pop       ebp
0077894d c20400                   ret       4
00778950 e9cb2dd8ff               jmp       0x4fb720
00778955 cc                       int3      
00778956 cc                       int3      
00778957 cc                       int3      
00778958 cc                       int3      
00778959 cc                       int3      
0077895a cc                       int3      
0077895b cc                       int3      
0077895c cc                       int3      
0077895d cc                       int3      
0077895e cc                       int3      
0077895f cc                       int3      
00778960 55                       push      ebp
00778961 8bec                     mov       ebp, esp
00778963 33c0                     xor       eax, eax
00778965 56                       push      esi
00778966 8881de1c0000             mov       byte ptr [ecx + 0x1cde], al
0077896c 8881dd1c0000             mov       byte ptr [ecx + 0x1cdd], al
00778972 8881dc1c0000             mov       byte ptr [ecx + 0x1cdc], al
00778978 8881c51c0000             mov       byte ptr [ecx + 0x1cc5], al
0077897e 8881c41c0000             mov       byte ptr [ecx + 0x1cc4], al
00778984 8881c31c0000             mov       byte ptr [ecx + 0x1cc3], al
0077898a 8881c21c0000             mov       byte ptr [ecx + 0x1cc2], al
00778990 8981c61c0000             mov       dword ptr [ecx + 0x1cc6], eax
00778996 33d2                     xor       edx, edx
00778998 8db1ca1c0000             lea       esi, [ecx + 0x1cca]
0077899e 8916                     mov       dword ptr [esi], edx
007789a0 895604                   mov       dword ptr [esi + 4], edx
007789a3 895608                   mov       dword ptr [esi + 8], edx
007789a6 89560c                   mov       dword ptr [esi + 0xc], edx
007789a9 66895610                 mov       word ptr [esi + 0x10], dx
007789ad 8b550c                   mov       edx, dword ptr [ebp + 0xc]
007789b0 2bd0                     sub       edx, eax
007789b2 8981ec1c0000             mov       dword ptr [ecx + 0x1cec], eax
007789b8 8981e81c0000             mov       dword ptr [ecx + 0x1ce8], eax
007789be 8981e41c0000             mov       dword ptr [ecx + 0x1ce4], eax
007789c4 8981fc1c0000             mov       dword ptr [ecx + 0x1cfc], eax
007789ca 8981f81c0000             mov       dword ptr [ecx + 0x1cf8], eax
007789d0 8981f41c0000             mov       dword ptr [ecx + 0x1cf4], eax
007789d6 8981f01c0000             mov       dword ptr [ecx + 0x1cf0], eax
007789dc 8981041d0000             mov       dword ptr [ecx + 0x1d04], eax
007789e2 5e                       pop       esi
007789e3 7405                     je        0x7789ea
007789e5 83ea02                   sub       edx, 2
007789e8 7507                     jne       0x7789f1
007789ea c681c61c000001           mov       byte ptr [ecx + 0x1cc6], 1
007789f1 5d                       pop       ebp
007789f2 c20800                   ret       8
007789f5 cc                       int3      
007789f6 cc                       int3      
007789f7 cc                       int3      
007789f8 cc                       int3      
007789f9 cc                       int3      
007789fa cc                       int3      
007789fb cc                       int3      
007789fc cc                       int3      
007789fd cc                       int3      
007789fe cc                       int3      
007789ff cc                       int3      
00778a00 33c0                     xor       eax, eax
00778a02 888154280000             mov       byte ptr [ecx + 0x2854], al
00778a08 888155280000             mov       byte ptr [ecx + 0x2855], al
00778a0e 898158280000             mov       dword ptr [ecx + 0x2858], eax
00778a14 89815c280000             mov       dword ptr [ecx + 0x285c], eax
00778a1a 898160280000             mov       dword ptr [ecx + 0x2860], eax
00778a20 898164280000             mov       dword ptr [ecx + 0x2864], eax
00778a26 898168280000             mov       dword ptr [ecx + 0x2868], eax
00778a2c 89816c280000             mov       dword ptr [ecx + 0x286c], eax
00778a32 898170280000             mov       dword ptr [ecx + 0x2870], eax
00778a38 898174280000             mov       dword ptr [ecx + 0x2874], eax
00778a3e c3                       ret       
00778a3f cc                       int3      
00778a40 56                       push      esi
00778a41 8bf1                     mov       esi, ecx
00778a43 8b06                     mov       eax, dword ptr [esi]
00778a45 ff90c4060000             call      dword ptr [eax + 0x6c4]
00778a4b 8b16                     mov       edx, dword ptr [esi]
00778a4d 6a00                     push      0
00778a4f 8bce                     mov       ecx, esi
00778a51 ff92cc010000             call      dword ptr [edx + 0x1cc]
00778a57 898658280000             mov       dword ptr [esi + 0x2858], eax
00778a5d 8b06                     mov       eax, dword ptr [esi]
00778a5f 6a01                     push      1
00778a61 8bce                     mov       ecx, esi
00778a63 ff90cc010000             call      dword ptr [eax + 0x1cc]
00778a69 8b16                     mov       edx, dword ptr [esi]
00778a6b 6a02                     push      2
00778a6d 8bce                     mov       ecx, esi
00778a6f 89865c280000             mov       dword ptr [esi + 0x285c], eax
00778a75 ff92cc010000             call      dword ptr [edx + 0x1cc]
00778a7b 89                       .byte     0x89
00778a7c 866028                   xchg      byte ptr [eax + 0x28], ah
00778a7f 00                       .byte     0x00

004991b0 55                       push      ebp
004991b1 8bec                     mov       ebp, esp
004991b3 53                       push      ebx
004991b4 56                       push      esi
004991b5 8bf1                     mov       esi, ecx
004991b7 8b06                     mov       eax, dword ptr [esi]
004991b9 ff9038010000             call      dword ptr [eax + 0x138]
004991bf 84c0                     test      al, al
004991c1 8a5d08                   mov       bl, byte ptr [ebp + 8]
004991c4 7425                     je        0x4991eb
004991c6 84db                     test      bl, bl
004991c8 7521                     jne       0x4991eb
004991ca 57                       push      edi
004991cb 8bbe04010000             mov       edi, dword ptr [esi + 0x104]
004991d1 85ff                     test      edi, edi
004991d3 7415                     je        0x4991ea
004991d5 8bcf                     mov       ecx, edi
004991d7 e8b4aa5800               call      0xa23c90
004991dc 8b8f8c000000             mov       ecx, dword ptr [edi + 0x8c]
004991e2 51                       push      ecx
004991e3 8bcf                     mov       ecx, edi
004991e5 e856f15800               call      0xa28340
004991ea 5f                       pop       edi
004991eb 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004991ee 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004991f1 889ec8010000             mov       byte ptr [esi + 0x1c8], bl
004991f7 8996cc010000             mov       dword ptr [esi + 0x1cc], edx
004991fd 8986d0010000             mov       dword ptr [esi + 0x1d0], eax
00499203 5e                       pop       esi
00499204 5b                       pop       ebx
00499205 5d                       pop       ebp
00499206 c20c00                   ret       0xc
00499209 cc                       int3      
0049920a cc                       int3      
0049920b cc                       int3      
0049920c cc                       int3      
0049920d cc                       int3      
0049920e cc                       int3      
0049920f cc                       int3      
00499210 55                       push      ebp
00499211 8bec                     mov       ebp, esp
00499213 8a4508                   mov       al, byte ptr [ebp + 8]
00499216 84c0                     test      al, al
00499218 57                       push      edi
00499219 8bf9                     mov       edi, ecx
0049921b 750b                     jne       0x499228
0049921d d905a4d7e900             fld       dword ptr [0xe9d7a4]
00499223 d9550c                   fst       dword ptr [ebp + 0xc]
00499226 eb03                     jmp       0x49922b
00499228 d9450c                   fld       dword ptr [ebp + 0xc]
0049922b d987d4010000             fld       dword ptr [edi + 0x1d4]
00499231 d9e1                     fabs      
00499233 d987d4010000             fld       dword ptr [edi + 0x1d4]
00499239 d9e1                     fabs      
0049923b dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00499241 ded9                     fcompp    
00499243 dfe0                     fnstsw    ax
00499245 f6c401                   test      ah, 1
00499248 7454                     je        0x49929e
0049924a d9c0                     fld       st(0)
0049924c d9e1                     fabs      
0049924e d9c1                     fld       st(1)
00499250 d9e1                     fabs      
00499252 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00499258 ded9                     fcompp    
0049925a dfe0                     fnstsw    ax
0049925c f6c401                   test      ah, 1
0049925f 753d                     jne       0x49929e
00499261 56                       push      esi
00499262 8bb704010000             mov       esi, dword ptr [edi + 0x104]
00499268 85f6                     test      esi, esi
0049926a 7426                     je        0x499292
0049926c 8bce                     mov       ecx, esi
0049926e ddd8                     fstp      st(0)
00499270 e81baa5800               call      0xa23c90
00499275 8b868c000000             mov       eax, dword ptr [esi + 0x8c]
0049927b 50                       push      eax
0049927c 8bce                     mov       ecx, esi
0049927e e8bdf05800               call      0xa28340
00499283 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00499286 5e                       pop       esi
00499287 898fd4010000             mov       dword ptr [edi + 0x1d4], ecx
0049928d 5f                       pop       edi
0049928e 5d                       pop       ebp
0049928f c20800                   ret       8
00499292 5e                       pop       esi
00499293 d99fd4010000             fstp      dword ptr [edi + 0x1d4]
00499299 5f                       pop       edi
0049929a 5d                       pop       ebp
0049929b c20800                   ret       8
0049929e d99fd4010000             fstp      dword ptr [edi + 0x1d4]
004992a4 5f                       pop       edi
004992a5 5d                       pop       ebp
004992a6 c20800                   ret       8
004992a9 cc                       int3      
004992aa cc                       int3      
004992ab cc                       int3      
004992ac cc                       int3      
004992ad cc                       int3      
004992ae cc                       int3      
004992af cc                       int3      
004992b0 55                       push      ebp
004992b1 8bec                     mov       ebp, esp
004992b3 53                       push      ebx
004992b4 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004992b7 56                       push      esi
004992b8 68e0baca00               push      0xcabae0
004992bd 53                       push      ebx
004992be 8bf1                     mov       esi, ecx
004992c0 e8267b7600               call      0xc00deb
004992c5 83c408                   add       esp, 8
004992c8 85c0                     test      eax, eax
004992ca 7439                     je        0x499305
004992cc 8a8694010000             mov       al, byte ptr [esi + 0x194]
004992d2 84c0                     test      al, al
004992d4 742f                     je        0x499305
004992d6 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004992d9 8b16                     mov       edx, dword ptr [esi]
004992db 57                       push      edi
004992dc 8b3dcca02301             mov       edi, dword ptr [0x123a0cc]
004992e2 6a00                     push      0
004992e4 50                       push      eax
004992e5 8bce                     mov       ecx, esi
004992e7 ff5244                   call      dword ptr [edx + 0x44]
004992ea 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004992ed 50                       push      eax
004992ee 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004992f1 6a00                     push      0
004992f3 50                       push      eax
004992f4 51                       push      ecx
004992f5 81c698010000             add       esi, 0x198
004992fb 56                       push      esi
004992fc 53                       push      ebx
004992fd 8bcf                     mov       ecx, edi
004992ff e8fc576f00               call      0xb8eb00
00499304 5f                       pop       edi
00499305 5e                       pop       esi
00499306 5b                       pop       ebx
00499307 5d                       pop       ebp
00499308 c21000                   ret       0x10
0049930b cc                       int3      
0049930c cc                       int3      
0049930d cc                       int3      
0049930e cc                       int3      
0049930f cc                       int3      
00499310 55                       push      ebp
00499311 8bec                     mov       ebp, esp
00499313 8b4508                   mov       eax, dword ptr [ebp + 8]
00499316 8b11                     mov       edx, dword ptr [ecx]
00499318 56                       push      esi
00499319 8b35cca02301             mov       esi, dword ptr [0x123a0cc]
0049931f 50                       push      eax
00499320 ff5244                   call      dword ptr [edx + 0x44]
00499323 50                       push      eax
00499324 8bce                     mov       ecx, esi
00499326 e8754d6f00               call      0xb8e0a0
0049932b 5e                       pop       esi
0049932c 5d                       pop       ebp
0049932d c20400                   ret       4
00499330 55                       push      ebp
00499331 8bec                     mov       ebp, esp
00499333 56                       push      esi
00499334 8bf1                     mov       esi, ecx
00499336 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0049933c 85c0                     test      eax, eax
0049933e 57                       push      edi
0049933f 8b7d08                   mov       edi, dword ptr [ebp + 8]
00499342 7408                     je        0x49934c
00499344 8bc8                     mov       ecx, eax
00499346 8b01                     mov       eax, dword ptr [ecx]
00499348 57                       push      edi
00499349 ff500c                   call      dword ptr [eax + 0xc]
0049934c 8b8654010000             mov       eax, dword ptr [esi + 0x154]
00499352 85c0                     test      eax, eax
00499354 7408                     je        0x49935e
00499356 8bc8                     mov       ecx, eax
00499358 8b11                     mov       edx, dword ptr [ecx]
0049935a 57                       push      edi
0049935b ff520c                   call      dword ptr [edx + 0xc]
0049935e 5f                       pop       edi
0049935f 5e                       pop       esi
00499360 5d                       pop       ebp
00499361 c20400                   ret       4
00499364 cc                       int3      
00499365 cc                       int3      
00499366 cc                       int3      
00499367 cc                       int3      
00499368 cc                       int3      
00499369 cc                       int3      
0049936a cc                       int3      
0049936b cc                       int3      
0049936c cc                       int3      
0049936d cc                       int3      
0049936e cc                       int3      
0049936f cc                       int3      
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
004993a0 83c404                   add       esp, 4
004993a3 8975f0                   mov       dword ptr [ebp - 0x10], esi
004993a6 85f6                     test      esi, esi
004993a8 c745fc00000000           mov       dword ptr [ebp - 4], 0
004993af 7411                     je        0x4993c2
004993b1 8bce                     mov       ecx, esi
004993b3 e8d8de0800               call      0x527290
004993b8 57                       push      edi
004993b9 8bce                     mov       ecx, esi
004993bb e850e20800               call      0x527610
004993c0 eb02                     jmp       0x4993c4
004993c2 33f6                     xor       esi, esi
004993c4 89b790010000             mov       dword ptr [edi + 0x190], esi
004993ca 5e                       pop       esi
004993cb 8b8790010000             mov       eax, dword ptr [edi + 0x190]
004993d1 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004993d4 5f                       pop       edi
004993d5 64890d00000000           mov       dword ptr fs:[0], ecx
004993dc 8be5                     mov       esp, ebp
004993de 5d                       pop       ebp
004993df c3                       ret       
004993e0 55                       push      ebp
004993e1 8bec                     mov       ebp, esp
004993e3 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
004993e6 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004993e9 56                       push      esi
004993ea 8b7508                   mov       esi, dword ptr [ebp + 8]
004993ed 2bc1                     sub       eax, ecx
004993ef 89                       .byte     0x89

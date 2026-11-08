007441d0 50                       push      eax
007441d1 64892500000000           mov       dword ptr fs:[0], esp
007441d8 83ec0c                   sub       esp, 0xc
007441db 53                       push      ebx
007441dc 56                       push      esi
007441dd 8bf1                     mov       esi, ecx
007441df 57                       push      edi
007441e0 8975ec                   mov       dword ptr [ebp - 0x14], esi
007441e3 e80843cfff               call      0x4384f0
007441e8 33db                     xor       ebx, ebx
007441ea 895dfc                   mov       dword ptr [ebp - 4], ebx
007441ed 899e24050000             mov       dword ptr [esi + 0x524], ebx
007441f3 899e28050000             mov       dword ptr [esi + 0x528], ebx
007441f9 899e2c050000             mov       dword ptr [esi + 0x52c], ebx
007441ff 68f0047400               push      0x7404f0
00744204 6840277400               push      0x742740
00744209 6a04                     push      4
0074420b 6840030000               push      0x340
00744210 8d8630050000             lea       eax, [esi + 0x530]
00744216 50                       push      eax
00744217 c645fc01                 mov       byte ptr [ebp - 4], 1
0074421b c7066cfad700             mov       dword ptr [esi], 0xd7fa6c
00744221 e83ec64b00               call      0xc00864
00744226 8d8e30120000             lea       ecx, [esi + 0x1230]
0074422c c645fc02                 mov       byte ptr [ebp - 4], 2
00744230 e8dbe9ffff               call      0x742c10
00744235 8d8e40120000             lea       ecx, [esi + 0x1240]
0074423b c645fc03                 mov       byte ptr [ebp - 4], 3
0074423f e8dca2d2ff               call      0x46e520
00744244 8d8ee0120000             lea       ecx, [esi + 0x12e0]
0074424a 895928                   mov       dword ptr [ecx + 0x28], ebx
0074424d 89592c                   mov       dword ptr [ecx + 0x2c], ebx
00744250 895930                   mov       dword ptr [ecx + 0x30], ebx
00744253 895938                   mov       dword ptr [ecx + 0x38], ebx
00744256 89593c                   mov       dword ptr [ecx + 0x3c], ebx
00744259 895940                   mov       dword ptr [ecx + 0x40], ebx
0074425c e8                       .byte     0xe8
0074425d 9f                       lahf      
0074425e f5                       cmc       
0074425f ff                       .byte     0xff

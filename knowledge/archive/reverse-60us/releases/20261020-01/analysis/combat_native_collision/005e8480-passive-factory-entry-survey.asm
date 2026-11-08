005e8480 00cc                     add       ah, cl
005e8482 cc                       int3      
005e8483 cc                       int3      
005e8484 cc                       int3      
005e8485 cc                       int3      
005e8486 cc                       int3      
005e8487 cc                       int3      
005e8488 cc                       int3      
005e8489 cc                       int3      
005e848a cc                       int3      
005e848b cc                       int3      
005e848c cc                       int3      
005e848d cc                       int3      
005e848e cc                       int3      
005e848f cc                       int3      
005e8490 55                       push      ebp
005e8491 8bec                     mov       ebp, esp
005e8493 6aff                     push      -1
005e8495 68165bc600               push      0xc65b16
005e849a 64a100000000             mov       eax, dword ptr fs:[0]
005e84a0 50                       push      eax
005e84a1 64892500000000           mov       dword ptr fs:[0], esp
005e84a8 51                       push      ecx
005e84a9 56                       push      esi
005e84aa 8bf1                     mov       esi, ecx
005e84ac 8975f0                   mov       dword ptr [ebp - 0x10], esi
005e84af c7068c11d500             mov       dword ptr [esi], 0xd5118c
005e84b5 8d8eb8080000             lea       ecx, [esi + 0x8b8]
005e84bb c745fc01000000           mov       dword ptr [ebp - 4], 1
005e84c2 e8499be1ff               call      0x402010
005e84c7 8d8e78080000             lea       ecx, [esi + 0x878]
005e84cd c645fc00                 mov       byte ptr [ebp - 4], 0
005e84d1 e85abde1ff               call      0x404230
005e84d6 8bce                     mov       ecx, esi
005e84d8 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005e84df e88c11e5ff               call      0x439670
005e84e4 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e84e7 5e                       pop       esi
005e84e8 64890d00000000           mov       dword ptr fs:[0], ecx
005e84ef 8be5                     mov       esp, ebp
005e84f1 5d                       pop       ebp
005e84f2 c3                       ret       
005e84f3 cc                       int3      
005e84f4 cc                       int3      
005e84f5 cc                       int3      
005e84f6 cc                       int3      
005e84f7 cc                       int3      
005e84f8 cc                       int3      
005e84f9 cc                       int3      
005e84fa cc                       int3      
005e84fb cc                       int3      
005e84fc cc                       int3      
005e84fd cc                       int3      
005e84fe cc                       int3      
005e84ff cc                       int3      
005e8500 55                       push      ebp
005e8501 8bec                     mov       ebp, esp
005e8503 64a100000000             mov       eax, dword ptr fs:[0]
005e8509 6aff                     push      -1
005e850b 68c774c600               push      0xc674c7
005e8510 50                       push      eax
005e8511 64892500000000           mov       dword ptr fs:[0], esp
005e8518 56                       push      esi
005e8519 8b7508                   mov       esi, dword ptr [ebp + 8]
005e851c 81feee590000             cmp       esi, 0x59ee
005e8522 0f8f0f440000             jg        0x5ec937
005e8528 0f84cb430000             je        0x5ec8f9
005e852e 81fe32110000             cmp       esi, 0x1132
005e8534 0f8fcb1a0000             jg        0x5ea005
005e853a 81fe30110000             cmp       esi, 0x1130
005e8540 0f8d3a1b0000             jge       0x5ea080
005e8546 81fe7a030000             cmp       esi, 0x37a
005e854c 0f8fca0a0000             jg        0x5e901c
005e8552 0f84860a0000             je        0x5e8fde
005e8558 81fe0d030000             cmp       esi, 0x30d
005e855e 0f                       .byte     0x0f
005e855f 8f                       .byte     0x8f

00830590 55                       push      ebp
00830591 8bec                     mov       ebp, esp
00830593 81ec00040000             sub       esp, 0x400
00830599 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0083059c 8d4510                   lea       eax, [ebp + 0x10]
0083059f 50                       push      eax
008305a0 51                       push      ecx
008305a1 8d9500fcffff             lea       edx, [ebp - 0x400]
008305a7 6800020000               push      0x200
008305ac 52                       push      edx
008305ad e830fa3c00               call      0xbfffe2
008305b2 8d8500fcffff             lea       eax, [ebp - 0x400]
008305b8 50                       push      eax
008305b9 e80ff83c00               call      0xbffdcd
008305be 83c414                   add       esp, 0x14
008305c1 48                       dec       eax
008305c2 7823                     js        0x8305e7
008305c4 eb0a                     jmp       0x8305d0
008305c6 8da42400000000           lea       esp, [esp]
008305cd 8d4900                   lea       ecx, [ecx]
008305d0 668b8c4500fcffff         mov       cx, word ptr [ebp + eax*2 - 0x400]
008305d8 6683f95c                 cmp       cx, 0x5c
008305dc 7409                     je        0x8305e7
008305de 6683f92f                 cmp       cx, 0x2f
008305e2 7403                     je        0x8305e7
008305e4 48                       dec       eax
008305e5 79e9                     jns       0x8305d0
008305e7 8d8d00fcffff             lea       ecx, [ebp - 0x400]
008305ed 51                       push      ecx
008305ee 66c7844502fcffff0000     mov       word ptr [ebp + eax*2 - 0x3fe], 0
008305f8 e8d0f73c00               call      0xbffdcd
008305fd 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00830600 83c404                   add       esp, 4
00830603 50                       push      eax
00830604 8d9500fcffff             lea       edx, [ebp - 0x400]
0083060a 52                       push      edx
0083060b e87028bdff               call      0x402e80
00830610 8be5                     mov       esp, ebp
00830612 5d                       pop       ebp
00830613 c3                       ret       
00830614 cc                       int3      
00830615 cc                       int3      
00830616 cc                       int3      
00830617 cc                       int3      
00830618 cc                       int3      
00830619 cc                       int3      
0083061a cc                       int3      
0083061b cc                       int3      
0083061c cc                       int3      
0083061d cc                       int3      
0083061e cc                       int3      
0083061f cc                       int3      
00830620 55                       push      ebp
00830621 8bec                     mov       ebp, esp
00830623 56                       push      esi
00830624 6a09                     push      9
00830626 e885992d00               call      0xb09fb0
0083062b 8b7508                   mov       esi, dword ptr [ebp + 8]
0083062e 83c404                   add       esp, 4
00830631 b928120501               mov       ecx, 0x1051228
00830636 c70600000000             mov       dword ptr [esi], 0
0083063c e82f230800               call      0x8b2970
00830641 83f802                   cmp       eax, 2
00830644 7524                     jne       0x83066a
00830646 b928120501               mov       ecx, 0x1051228
0083064b e8a0230800               call      0x8b29f0
00830650 894508                   mov       dword ptr [ebp + 8], eax
00830653 db4508                   fild      dword ptr [ebp + 8]
00830656 d91e                     fstp      dword ptr [esi]
00830658 33f6                     xor       esi, esi
0083065a 56                       push      esi
0083065b 6a09                     push      9
0083065d e88e992d00               call      0xb09ff0
00830662 83c408                   add       esp, 8
00830665 8bc6                     mov       eax, esi
00830667 5e                       pop       esi
00830668 5d                       pop       ebp
00830669 c3                       ret       
0083066a 83f803                   cmp       eax, 3
0083066d 7524                     jne       0x830693
0083066f b928120501               mov       ecx, 0x1051228
00830674 e8b7230800               call      0x8b2a30
00830679 894508                   mov       dword ptr [ebp + 8], eax
0083067c db4508                   fild      dword ptr [ebp + 8]
0083067f d91e                     fstp      dword ptr [esi]
00830681 33f6                     xor       esi, esi
00830683 56                       push      esi
00830684 6a09                     push      9
00830686 e865992d00               call      0xb09ff0
0083068b 83c408                   add       esp, 8
0083068e 8bc6                     mov       eax, esi
00830690 5e                       pop       esi
00830691 5d                       pop       ebp
00830692 c3                       ret       
00830693 83f804                   cmp       eax, 4
00830696 751e                     jne       0x8306b6
00830698 b928120501               mov       ecx, 0x1051228
0083069d e8ce230800               call      0x8b2a70
008306a2 d91e                     fstp      dword ptr [esi]
008306a4 33f6                     xor       esi, esi
008306a6 56                       push      esi
008306a7 6a09                     push      9
008306a9 e842992d00               call      0xb09ff0
008306ae 83c408                   add       esp, 8
008306b1 8bc6                     mov       eax, esi
008306b3 5e                       pop       esi
008306b4 5d                       pop       ebp
008306b5 c3                       ret       
008306b6 83f807                   cmp       eax, 7
008306b9 7532                     jne       0x8306ed
008306bb b928120501               mov       ecx, 0x1051228
008306c0 e82b240800               call      0x8b2af0
008306c5 50                       push      eax
008306c6 e885252600               call      0xa92c50
008306cb 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
008306ce 83c404                   add       esp, 4
008306d1 50                       push      eax
008306d2 e869e4bdff               call      0x40eb40
008306d7 6a00                     push      0
008306d9 6a09                     push      9
008306db be01000000               mov       esi, 1
008306e0 e80b992d00               call      0xb09ff0
008306e5 83c408                   add       esp, 8
008306e8 8bc6                     mov       eax, esi
008306ea 5e                       pop       esi
008306eb 5d                       pop       ebp
008306ec c3                       ret       
008306ed 6a00                     push      0
008306ef 6a09                     push      9
008306f1 83ceff                   or        esi, 0xffffffff
008306f4 e8f7982d00               call      0xb09ff0
008306f9 83c408                   add       esp, 8
008306fc 8bc6                     mov       eax, esi
008306fe 5e                       pop       esi
008306ff 5d                       pop       ebp
00830700 c3                       ret       
00830701 cc                       int3      
00830702 cc                       int3      
00830703 cc                       int3      
00830704 cc                       int3      
00830705 cc                       int3      
00830706 cc                       int3      
00830707 cc                       int3      
00830708 cc                       int3      
00830709 cc                       int3      
0083070a cc                       int3      
0083070b cc                       int3      
0083070c cc                       int3      
0083070d cc                       int3      
0083070e cc                       int3      
0083070f cc                       int3      
00830710 55                       push      ebp
00830711 8bec                     mov       ebp, esp
00830713 53                       push      ebx
00830714 56                       push      esi
00830715 6a09                     push      9
00830717 e894982d00               call      0xb09fb0
0083071c 83c404                   add       esp, 4
0083071f b928120501               mov       ecx, 0x1051228
00830724 32db                     xor       bl, bl
00830726 e845220800               call      0x8b2970
0083072b 83e807                   sub       eax, 7
0083072e 746b                     je        0x83079b
00830730 83e802                   sub       eax, 2
00830733 0f8589000000             jne       0x8307c2
00830739 b928120501               mov       ecx, 0x1051228
0083073e e8ed230800               call      0x8b2b30
00830743 b928120501               mov       ecx, 0x1051228
00830748 8bf0                     mov       esi, eax
0083074a e821220800               call      0x8b2970
0083074f 83f80a                   cmp       eax, 0xa
00830752 756e                     jne       0x8307c2
00830754 b928120501               mov       ecx, 0x1051228
00830759 e842240800               call      0x8b2ba0
0083075e 85c0                     test      eax, eax
00830760 7510                     jne       0x830772
00830762 be7039e100               mov       esi, 0xe13970
00830767 56                       push      esi
00830768 e860f63c00               call      0xbffdcd
0083076d 83c404                   add       esp, 4
00830770 eb44                     jmp       0x8307b6
00830772 8b0d94110501             mov       ecx, dword ptr [0x1051194]
00830778 6bf63c                   imul      esi, esi, 0x3c
0083077b 50                       push      eax
0083077c 03f1                     add       esi, ecx
0083077e e8cd242600               call      0xa92c50
00830783 83c404                   add       esp, 4
00830786 50                       push      eax
00830787 8bce                     mov       ecx, esi
00830789 e822600700               call      0x8a67b0
0083078e 8bf0                     mov       esi, eax
00830790 56                       push      esi
00830791 e837f63c00               call      0xbffdcd
00830796 83c404                   add       esp, 4
00830799 eb1b                     jmp       0x8307b6
0083079b b928120501               mov       ecx, 0x1051228
008307a0 e84b230800               call      0x8b2af0
008307a5 50                       push      eax
008307a6 e8a5242600               call      0xa92c50
008307ab 8bf0                     mov       esi, eax
008307ad 56                       push      esi
008307ae e81af63c00               call      0xbffdcd
008307b3 83c408                   add       esp, 8
008307b6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
008307b9 50                       push      eax
008307ba 56                       push      esi
008307bb e8c026bdff               call      0x402e80
008307c0 b301                     mov       bl, 1
008307c2 6a00                     push      0
008307c4 6a09                     push      9
008307c6 e825982d00               call      0xb09ff0
008307cb 83c408                   add       esp, 8
008307ce 5e                       pop       esi
008307cf 8ac3                     mov       al, bl
008307d1 5b                       pop       ebx
008307d2 5d                       pop       ebp
008307d3 c3                       ret       
008307d4 cc                       int3      
008307d5 cc                       int3      
008307d6 cc                       int3      
008307d7 cc                       int3      
008307d8 cc                       int3      
008307d9 cc                       int3      
008307da cc                       int3      
008307db cc                       int3      
008307dc cc                       int3      
008307dd cc                       int3      
008307de cc                       int3      
008307df cc                       int3      

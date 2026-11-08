004fc600 7416                     je        0x4fc618
004fc602 8b06                     mov       eax, dword ptr [esi]
004fc604 6a00                     push      0
004fc606 6a00                     push      0
004fc608 6a00                     push      0
004fc60a 6a00                     push      0
004fc60c 6a00                     push      0
004fc60e 6a01                     push      1
004fc610 8bce                     mov       ecx, esi
004fc612 ff9088040000             call      dword ptr [eax + 0x488]
004fc618 8bce                     mov       ecx, esi
004fc61a e8619bffff               call      0x4f6180
004fc61f eb0a                     jmp       0x4fc62b
004fc621 8b16                     mov       edx, dword ptr [esi]
004fc623 8bce                     mov       ecx, esi
004fc625 ff92a0060000             call      dword ptr [edx + 0x6a0]
004fc62b f686cc04000001           test      byte ptr [esi + 0x4cc], 1
004fc632 740a                     je        0x4fc63e
004fc634 8b06                     mov       eax, dword ptr [esi]
004fc636 8bce                     mov       ecx, esi
004fc638 ff907c060000             call      dword ptr [eax + 0x67c]
004fc63e 6aff                     push      -1
004fc640 6a00                     push      0
004fc642 6a00                     push      0
004fc644 6811010000               push      0x111
004fc649 8bce                     mov       ecx, esi
004fc64b e8b0e7ffff               call      0x4fae00
004fc650 85c0                     test      eax, eax
004fc652 7537                     jne       0x4fc68b
004fc654 80be4c20000001           cmp       byte ptr [esi + 0x204c], 1
004fc65b 7566                     jne       0x4fc6c3
004fc65d 6a00                     push      0
004fc65f c6864c20000000           mov       byte ptr [esi + 0x204c], 0
004fc666 e8851a3b00               call      0x8ae0f0
004fc66b 99                       cdq       
004fc66c b964000000               mov       ecx, 0x64
004fc671 f7f9                     idiv      ecx
004fc673 83c404                   add       esp, 4
004fc676 83fa0f                   cmp       edx, 0xf
004fc679 7d48                     jge       0x4fc6c3
004fc67b 8b16                     mov       edx, dword ptr [esi]
004fc67d 6aff                     push      -1
004fc67f 6a1a                     push      0x1a
004fc681 8bce                     mov       ecx, esi
004fc683 ff9244050000             call      dword ptr [edx + 0x544]
004fc689 eb38                     jmp       0x4fc6c3
004fc68b 7e36                     jle       0x4fc6c3
004fc68d 8a864c200000             mov       al, byte ptr [esi + 0x204c]
004fc693 84c0                     test      al, al
004fc695 752c                     jne       0x4fc6c3
004fc697 6a00                     push      0
004fc699 e8521a3b00               call      0x8ae0f0
004fc69e 99                       cdq       
004fc69f b964000000               mov       ecx, 0x64
004fc6a4 f7f9                     idiv      ecx
004fc6a6 83c404                   add       esp, 4
004fc6a9 83fa0f                   cmp       edx, 0xf
004fc6ac 7d0e                     jge       0x4fc6bc
004fc6ae 8b16                     mov       edx, dword ptr [esi]
004fc6b0 6aff                     push      -1
004fc6b2 6a19                     push      0x19
004fc6b4 8bce                     mov       ecx, esi
004fc6b6 ff9244050000             call      dword ptr [edx + 0x544]
004fc6bc c6864c20000001           mov       byte ptr [esi + 0x204c], 1
004fc6c3 8b8e84200000             mov       ecx, dword ptr [esi + 0x2084]
004fc6c9 85c9                     test      ecx, ecx
004fc6cb 7418                     je        0x4fc6e5
004fc6cd 8b01                     mov       eax, dword ptr [ecx]
004fc6cf ff90dc030000             call      dword ptr [eax + 0x3dc]
004fc6d5 84c0                     test      al, al
004fc6d7 740c                     je        0x4fc6e5
004fc6d9 8b16                     mov       edx, dword ptr [esi]
004fc6db 6a00                     push      0
004fc6dd 8bce                     mov       ecx, esi
004fc6df ff9254030000             call      dword ptr [edx + 0x354]
004fc6e5 8b868c200000             mov       eax, dword ptr [esi + 0x208c]
004fc6eb 85c0                     test      eax, eax
004fc6ed 0f8473000000             je        0x4fc766
004fc6f3 8b8e84200000             mov       ecx, dword ptr [esi + 0x2084]
004fc6f9 85c9                     test      ecx, ecx
004fc6fb 7569                     jne       0x4fc766
004fc6fd 8a4001                   mov       al, byte ptr [eax + 1]
004fc700 3c01                     cmp       al, 1
004fc702 751d                     jne       0x4fc721
004fc704 8b06                     mov       eax, dword ptr [esi]
004fc706 8bce                     mov       ecx, esi
004fc708 ff90c4010000             call      dword ptr [eax + 0x1c4]
004fc70e 83f865                   cmp       eax, 0x65
004fc711 7453                     je        0x4fc766
004fc713 8b16                     mov       edx, dword ptr [esi]
004fc715 6a65                     push      0x65
004fc717 8bce                     mov       ecx, esi
004fc719 ff92c0010000             call      dword ptr [edx + 0x1c0]
004fc71f eb45                     jmp       0x4fc766
004fc721 3c02                     cmp       al, 2
004fc723 7541                     jne       0x4fc766
004fc725 8d8e5c150000             lea       ecx, [esi + 0x155c]
004fc72b e83059f0ff               call      0x402060
004fc730 83f80d                   cmp       eax, 0xd
004fc733 7431                     je        0x4fc766
004fc735 8bce                     mov       ecx, esi
004fc737 e854f9f9ff               call      0x49c090
004fc73c 84c0                     test      al, al
004fc73e 7426                     je        0x4fc766
004fc740 8b8610250000             mov       eax, dword ptr [esi + 0x2510]
004fc746 85c0                     test      eax, eax
004fc748 7408                     je        0x4fc752
004fc74a 50                       push      eax
004fc74b 8bce                     mov       ecx, esi
004fc74d e86e95ffff               call      0x4f5cc0
004fc752 8b06                     mov       eax, dword ptr [esi]
004fc754 6a00                     push      0
004fc756 6a00                     push      0
004fc758 6a03                     push      3
004fc75a 6a00                     push      0
004fc75c 6a0d                     push      0xd
004fc75e 8bce                     mov       ecx, esi
004fc760 ff908c020000             call      dword ptr [eax + 0x28c]
004fc766 8bce                     mov       ecx, esi
004fc768 e823f9f9ff               call      0x49c090
004fc76d 84c0                     test      al, al
004fc76f 0f847e000000             je        0x4fc7f3
004fc775 8b16                     mov       edx, dword ptr [esi]
004fc777 8bce                     mov       ecx, esi
004fc779 ff9240060000             call      dword ptr [edx + 0x640]
004fc77f 85c0                     test      eax, eax
004fc781 7470                     je        0x4fc7f3
004fc783 8d8ea0000000             lea       ecx, [esi + 0xa0]
004fc789 e872a76000               call      0xb06f00
004fc78e 8bf8                     mov       edi, eax
004fc790 8b06                     mov       eax, dword ptr [esi]
004fc792 8bce                     mov       ecx, esi
004fc794 ff9040060000             call      dword ptr [eax + 0x640]
004fc79a 3bf8                     cmp       edi, eax
004fc79c 7c55                     jl        0x4fc7f3
004fc79e 8dbe5c150000             lea       edi, [esi + 0x155c]
004fc7a4 8bcf                     mov       ecx, edi
004fc7a6 e8b558f0ff               call      0x402060
004fc7ab 85c0                     test      eax, eax
004fc7ad 7430                     je        0x4fc7df
004fc7af 8bcf                     mov       ecx, edi
004fc7b1 e8aa58f0ff               call      0x402060
004fc7b6 83f801                   cmp       eax, 1
004fc7b9 7424                     je        0x4fc7df
004fc7bb 8bcf                     mov       ecx, edi
004fc7bd e89e58f0ff               call      0x402060
004fc7c2 83f802                   cmp       eax, 2
004fc7c5 7418                     je        0x4fc7df
004fc7c7 8bcf                     mov       ecx, edi
004fc7c9 e89258f0ff               call      0x402060
004fc7ce 83f803                   cmp       eax, 3
004fc7d1 740c                     je        0x4fc7df
004fc7d3 8bcf                     mov       ecx, edi
004fc7d5 e88658f0ff               call      0x402060
004fc7da 83f809                   cmp       eax, 9
004fc7dd 7514                     jne       0x4fc7f3
004fc7df 8b16                     mov       edx, dword ptr [esi]
004fc7e1 6a00                     push      0
004fc7e3 6a00                     push      0
004fc7e5 6a03                     push      3
004fc7e7 6a00                     push      0
004fc7e9 6a0d                     push      0xd
004fc7eb 8bce                     mov       ecx, esi
004fc7ed ff928c020000             call      dword ptr [edx + 0x28c]
004fc7f3 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004fc7f9 8b01                     mov       eax, dword ptr [ecx]
004fc7fb ff909c000000             call      dword ptr [eax + 0x9c]
004fc801 3905d4f10401             cmp       dword ptr [0x104f1d4], eax
004fc807 7532                     jne       0x4fc83b
004fc809 8b86f0040000             mov       eax, dword ptr [esi + 0x4f0]
004fc80f 85c0                     test      eax, eax
004fc811 741e                     je        0x4fc831
004fc813 8d4e20                   lea       ecx, [esi + 0x20]
004fc816 e8e5a66000               call      0xb06f00
004fc81b 3b86b41d0000             cmp       eax, dword ptr [esi + 0x1db4]
004fc821 7c18                     jl        0x4fc83b
004fc823 8b16                     mov       edx, dword ptr [esi]
004fc825 8bce                     mov       ecx, esi
004fc827 ff9200060000             call      dword ptr [edx + 0x600]
004fc82d 84c0                     test      al, al
004fc82f 740a                     je        0x4fc83b
004fc831 8b06                     mov       eax, dword ptr [esi]
004fc833 8bce                     mov       ecx, esi
004fc835 ff9098060000             call      dword ptr [eax + 0x698]
004fc83b 8b16                     mov       edx, dword ptr [esi]
004fc83d 8bce                     mov       ecx, esi
004fc83f ff92dc030000             call      dword ptr [edx + 0x3dc]
004fc845 84c0                     test      al, al
004fc847 7549                     jne       0x4fc892
004fc849 8b06                     mov       eax, dword ptr [esi]
004fc84b 8bce                     mov       ecx, esi
004fc84d ff90f0040000             call      dword ptr [eax + 0x4f0]
004fc853 84c0                     test      al, al
004fc855 743b                     je        0x4fc892
004fc857 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fc85d 8b4244                   mov       eax, dword ptr [edx + 0x44]
004fc860 8b8e64180000             mov       ecx, dword ptr [esi + 0x1864]
004fc866 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fc86c 8d0488                   lea       eax, [eax + ecx*4]
004fc86f 8bc8                     mov       ecx, eax
004fc871 33ca                     xor       ecx, edx
004fc873 8908                     mov       dword ptr [eax], ecx
004fc875 a1d8012101               mov       eax, dword ptr [0x12101d8]
004fc87a 8b9664180000             mov       edx, dword ptr [esi + 0x1864]
004fc880 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fc883 8d0491                   lea       eax, [ecx + edx*4]
004fc886 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fc88c 8bd0                     mov       edx, eax
004fc88e 33d1                     xor       edx, ecx
004fc890 8910                     mov       dword ptr [eax], edx
004fc892 8d8e5c150000             lea       ecx, [esi + 0x155c]
004fc898 e8c357f0ff               call      0x402060
004fc89d 83f80d                   cmp       eax, 0xd
004fc8a0 0f87c6040000             ja        0x4fcd6c
004fc8a6 0fb68084ce4f00           movzx     eax, byte ptr [eax + 0x4fce84]
004fc8ad ff248568ce4f00           jmp       dword ptr [eax*4 + 0x4fce68]
004fc8b4 8bce                     mov       ecx, esi
004fc8b6 e80566ffff               call      0x4f2ec0
004fc8bb 33ff                     xor       edi, edi
004fc8bd 33db                     xor       ebx, ebx
004fc8bf 90                       nop       
004fc8c0 8b8618220000             mov       eax, dword ptr [esi + 0x2218]
004fc8c6 85c0                     test      eax, eax
004fc8c8 0f849e040000             je        0x4fcd6c
004fc8ce 8b8e1c220000             mov       ecx, dword ptr [esi + 0x221c]
004fc8d4 2bc8                     sub       ecx, eax
004fc8d6 b889888888               mov       eax, 0x88888889
004fc8db f7e9                     imul      ecx
004fc8dd 03d1                     add       edx, ecx
004fc8df c1fa06                   sar       edx, 6
004fc8e2 8bc2                     mov       eax, edx
004fc8e4 c1e81f                   shr       eax, 0x1f
004fc8e7 03c2                     add       eax, edx
004fc8e9 3bf8                     cmp       edi, eax
004fc8eb 0f837b040000             jae       0x4fcd6c
004fc8f1 8b8e18220000             mov       ecx, dword ptr [esi + 0x2218]
004fc8f7 8b54194c                 mov       edx, dword ptr [ecx + ebx + 0x4c]
004fc8fb 8d0419                   lea       eax, [ecx + ebx]
004fc8fe 47                       inc       edi
004fc8ff 895058                   mov       dword ptr [eax + 0x58], edx
004fc902 83c378                   add       ebx, 0x78
004fc905 ebb9                     jmp       0x4fc8c0
004fc907 8b06                     mov       eax, dword ptr [esi]
004fc909 8bce                     mov       ecx, esi
004fc90b ff90f4000000             call      dword ptr [eax + 0xf4]
004fc911 85c0                     test      eax, eax
004fc913 0f8453040000             je        0x4fcd6c
004fc919 8b16                     mov       edx, dword ptr [esi]
004fc91b 8bce                     mov       ecx, esi
004fc91d ff92f4000000             call      dword ptr [edx + 0xf4]
004fc923 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
004fc929 84c9                     test      cl, cl
004fc92b 0f                       .byte     0x0f
004fc92c 843b                     test      byte ptr [ebx], bh
004fc92e 0400                     add       al, 0

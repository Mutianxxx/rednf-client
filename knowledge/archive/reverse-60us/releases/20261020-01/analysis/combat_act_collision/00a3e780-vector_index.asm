00a3e780 55                       push       ebp
00a3e781 8bec                     mov        ebp, esp
00a3e783 56                       push       esi
00a3e784 8bf1                     mov        esi, ecx
00a3e786 8b4608                   mov        eax, dword ptr [esi + 8]
00a3e789 57                       push       edi
00a3e78a 2b4604                   sub        eax, dword ptr [esi + 4]
00a3e78d 8b7d08                   mov        edi, dword ptr [ebp + 8]
00a3e790 c1f802                   sar        eax, 2
00a3e793 3bf8                     cmp        edi, eax
00a3e795 7226                     jb         0xa3e7bd
00a3e797 50                       push       eax
00a3e798 57                       push       edi
00a3e799 685829cd00               push       0xcd2958
00a3e79e 68a0b3cb00               push       0xcbb3a0
00a3e7a3 ff15bc2eff00             call       dword ptr [0xff2ebc]
00a3e7a9 83c410                   add        esp, 0x10
00a3e7ac 6a00                     push       0
00a3e7ae 6a00                     push       0
00a3e7b0 6a00                     push       0
00a3e7b2 688c0000c0               push       0xc000008c
00a3e7b7 ff1528f04001             call       dword ptr [0x140f028]
00a3e7bd 8b4604                   mov        eax, dword ptr [esi + 4]
00a3e7c0 8d04b8                   lea        eax, [eax + edi*4]
00a3e7c3 5f                       pop        edi
00a3e7c4 5e                       pop        esi
00a3e7c5 5d                       pop        ebp
00a3e7c6 c20400                   ret        4

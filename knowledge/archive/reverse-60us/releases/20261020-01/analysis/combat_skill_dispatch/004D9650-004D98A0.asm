004d9650  643100                   xor        dword ptr fs:[eax], eax
004d9653  0150ff                   add        dword ptr [eax - 1], edx
004d9656  57                       push       edi
004d9657  2cf6                     sub        al, 0xf6
004d9659  45                       inc        ebp
004d965a  e801c745fc               call       0xfc935d60
004d965f  ff                       .byte      0xff
004d9660  ff                       .byte      0xff
004d9661  ff                       .byte      0xff
004d9662  ff74088d                 push       dword ptr [eax + ecx - 0x73]
004d9666  4d                       dec        ebp
004d9667  e0e8                     loopne     0x4d9651
004d9669  a389f2ff8b               mov        dword ptr [0x8bfff289], eax
004d966e  0d64310001               or         eax, 0x1003164
004d9673  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004d9676  8b11                     mov        edx, dword ptr [ecx]
004d9678  50                       push       eax
004d9679  ff5220                   call       dword ptr [edx + 0x20]
004d967c  56                       push       esi
004d967d  6a01                     push       1
004d967f  e8ac62f3ff               call       0x40f930
004d9684  8b16                     mov        edx, dword ptr [esi]
004d9686  83c408                   add        esp, 8
004d9689  8bce                     mov        ecx, esi
004d968b  ff5234                   call       dword ptr [edx + 0x34]
004d968e  84c0                     test       al, al
004d9690  0f85c2000000             jne        0x4d9758
004d9696  8d4b68                   lea        ecx, [ebx + 0x68]
004d9699  e8c289f2ff               call       0x402060
004d969e  83f801                   cmp        eax, 1
004d96a1  0f84b1000000             je         0x4d9758
004d96a7  8b0d80420d01             mov        ecx, dword ptr [0x10d4280]
004d96ad  6a29                     push       0x29
004d96af  e83c4c5800               call       0xa5e2f0
004d96b4  8a4508                   mov        al, byte ptr [ebp + 8]
004d96b7  6a01                     push       1
004d96b9  8d4d0f                   lea        ecx, [ebp + 0xf]
004d96bc  51                       push       ecx
004d96bd  8b0d80420d01             mov        ecx, dword ptr [0x10d4280]
004d96c3  88450f                   mov        byte ptr [ebp + 0xf], al
004d96c6  e8054d5800               call       0xa5e3d0
004d96cb  8b15d4f10401             mov        edx, dword ptr [0x104f1d4]
004d96d1  8b3580420d01             mov        esi, dword ptr [0x10d4280]
004d96d7  6aff                     push       -1
004d96d9  52                       push       edx
004d96da  8bcb                     mov        ecx, ebx
004d96dc  e8ef740700               call       0x550bd0
004d96e1  89450c                   mov        dword ptr [ebp + 0xc], eax
004d96e4  6a02                     push       2
004d96e6  8d450c                   lea        eax, [ebp + 0xc]
004d96e9  50                       push       eax
004d96ea  8bce                     mov        ecx, esi
004d96ec  e8df4c5800               call       0xa5e3d0
004d96f1  e9cca0ed00               jmp        0x13b37c2
004d96f6  29956a4c9bd2             sub        dword ptr [ebp - 0x2d64b396], edx
004d96fc  0a58ee                   or         bl, byte ptr [eax - 0x12]
004d96ff  fe                       .byte      0xfe
004d9700  7e38                     jle        0x4d973a
004d9702  37                       aaa        
004d9703  38da                     cmp        dl, bl
004d9705  46                       inc        esi
004d9706  09c3                     or         ebx, eax
004d9708  48                       dec        eax
004d9709  ab                       stosd      dword ptr es:[edi], eax
004d970a  20b34f319a7e             and        byte ptr [ebx + 0x7e9a314f], dh
004d9710  bca0ec4f70               mov        esp, 0x704feca0
004d9715  54                       push       esp
004d9716  ea242aaee1c71e           ljmp       0x1ec7:0xe1ae2a24
004d971d  3c91                     cmp        al, 0x91
004d971f  46                       inc        esi
004d9720  360bc4                   or         eax, esp
004d9723  ab                       stosd      dword ptr es:[edi], eax
004d9724  8c8d0c1d2161             mov        word ptr [ebp + 0x61211d0c], cs
004d972a  268b25495973e8           mov        esp, dword ptr es:[0xe8735949]
004d9731  6b5d5800                 imul       ebx, dword ptr [ebp + 0x58], 0
004d9735  8b15d4f10401             mov        edx, dword ptr [0x104f1d4]
004d973b  6aff                     push       -1
004d973d  52                       push       edx
004d973e  8bcb                     mov        ecx, ebx
004d9740  e88b740700               call       0x550bd0
004d9745  50                       push       eax
004d9746  8b4508                   mov        eax, dword ptr [ebp + 8]
004d9749  50                       push       eax
004d974a  68c83acd00               push       0xcd3ac8
004d974f  ff15bc2eff00             call       dword ptr [0xff2ebc]
004d9755  83c40c                   add        esp, 0xc
004d9758  5f                       pop        edi
004d9759  5b                       pop        ebx
004d975a  b001                     mov        al, 1
004d975c  5e                       pop        esi
004d975d  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d9760  64890d00000000           mov        dword ptr fs:[0], ecx
004d9767  8be5                     mov        esp, ebp
004d9769  5d                       pop        ebp
004d976a  c21000                   ret        0x10
004d976d  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d9770  32c0                     xor        al, al
004d9772  5e                       pop        esi
004d9773  64890d00000000           mov        dword ptr fs:[0], ecx
004d977a  8be5                     mov        esp, ebp
004d977c  5d                       pop        ebp
004d977d  c21000                   ret        0x10
004d9780  55                       push       ebp
004d9781  8bec                     mov        ebp, esp
004d9783  83ec28                   sub        esp, 0x28
004d9786  53                       push       ebx
004d9787  56                       push       esi
004d9788  8d99c81d0000             lea        ebx, [ecx + 0x1dc8]
004d978e  33f6                     xor        esi, esi
004d9790  57                       push       edi
004d9791  8b3d28f04001             mov        edi, dword ptr [0x140f028]
004d9797  894df4                   mov        dword ptr [ebp - 0xc], ecx
004d979a  895de0                   mov        dword ptr [ebp - 0x20], ebx
004d979d  895de4                   mov        dword ptr [ebp - 0x1c], ebx
004d97a0  81fede000000             cmp        esi, 0xde
004d97a6  7226                     jb         0x4d97ce
004d97a8  68de000000               push       0xde
004d97ad  56                       push       esi
004d97ae  68ec29cd00               push       0xcd29ec
004d97b3  68a0b3cb00               push       0xcbb3a0
004d97b8  ff15bc2eff00             call       dword ptr [0xff2ebc]
004d97be  83c410                   add        esp, 0x10
004d97c1  6a00                     push       0
004d97c3  6a00                     push       0
004d97c5  6a00                     push       0
004d97c7  688c0000c0               push       0xc000008c
004d97cc  ffd7                     call       edi
004d97ce  833b00                   cmp        dword ptr [ebx], 0
004d97d1  0f84b5000000             je         0x4d988c
004d97d7  81fede000000             cmp        esi, 0xde
004d97dd  7226                     jb         0x4d9805
004d97df  68de000000               push       0xde
004d97e4  56                       push       esi
004d97e5  68ec29cd00               push       0xcd29ec
004d97ea  68a0b3cb00               push       0xcbb3a0
004d97ef  ff15bc2eff00             call       dword ptr [0xff2ebc]
004d97f5  83c410                   add        esp, 0x10
004d97f8  6a00                     push       0
004d97fa  6a00                     push       0
004d97fc  6a00                     push       0
004d97fe  688c0000c0               push       0xc000008c
004d9803  ffd7                     call       edi
004d9805  81fede000000             cmp        esi, 0xde
004d980b  8b03                     mov        eax, dword ptr [ebx]
004d980d  8945dc                   mov        dword ptr [ebp - 0x24], eax
004d9810  7226                     jb         0x4d9838
004d9812  68de000000               push       0xde
004d9817  56                       push       esi
004d9818  68ec29cd00               push       0xcd29ec
004d981d  68a0b3cb00               push       0xcbb3a0
004d9822  ff15bc2eff00             call       dword ptr [0xff2ebc]
004d9828  83c410                   add        esp, 0x10
004d982b  6a00                     push       0
004d982d  6a00                     push       0
004d982f  6a00                     push       0
004d9831  688c0000c0               push       0xc000008c
004d9836  ffd7                     call       edi
004d9838  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
004d983b  81c114030000             add        ecx, 0x314
004d9841  e81a88f2ff               call       0x402060
004d9846  8b0b                     mov        ecx, dword ptr [ebx]
004d9848  8b9120030000             mov        edx, dword ptr [ecx + 0x320]
004d984e  8b1dd8012101             mov        ebx, dword ptr [0x12101d8]
004d9854  8b5b44                   mov        ebx, dword ptr [ebx + 0x44]
004d9857  8d1493                   lea        edx, [ebx + edx*4]
004d985a  81c11c030000             add        ecx, 0x31c
004d9860  8bda                     mov        ebx, edx
004d9862  331ddc012101             xor        ebx, dword ptr [0x12101dc]
004d9868  33d8                     xor        ebx, eax
004d986a  891a                     mov        dword ptr [edx], ebx
004d986c  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004d9872  8b5248                   mov        edx, dword ptr [edx + 0x48]
004d9875  8b4904                   mov        ecx, dword ptr [ecx + 4]
004d9878  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004d987e  8d0c8a                   lea        ecx, [edx + ecx*4]
004d9881  8bd1                     mov        edx, ecx
004d9883  33d3                     xor        edx, ebx
004d9885  8b5de4                   mov        ebx, dword ptr [ebp - 0x1c]
004d9888  33d0                     xor        edx, eax
004d988a  8911                     mov        dword ptr [ecx], edx
004d988c  46                       inc        esi
004d988d  83c304                   add        ebx, 4
004d9890  81fede000000             cmp        esi, 0xde
004d9896  895de4                   mov        dword ptr [ebp - 0x1c], ebx
004d9899  0f8c07ffffff             jl         0x4d97a6
004d989f  8b                       .byte      0x8b
00831ad0  55                       push       ebp
00831ad1  8bec                     mov        ebp, esp
00831ad3  6aff                     push       -1
00831ad5  68aed9c700               push       0xc7d9ae
00831ada  64a100000000             mov        eax, dword ptr fs:[0]
00831ae0  50                       push       eax
00831ae1  64892500000000           mov        dword ptr fs:[0], esp
00831ae8  83ec4c                   sub        esp, 0x4c
00831aeb  a164070501               mov        eax, dword ptr [0x1050764]
00831af0  53                       push       ebx
00831af1  33db                     xor        ebx, ebx
00831af3  3bc3                     cmp        eax, ebx
00831af5  7402                     je         0x831af9
00831af7  ffd0                     call       eax
00831af9  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00831afc  53                       push       ebx
00831afd  53                       push       ebx
00831afe  50                       push       eax
00831aff  e8ec112600               call       0xa92cf0
00831b04  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00831b07  83c404                   add        esp, 4
00831b0a  50                       push       eax
00831b0b  51                       push       ecx
00831b0c  e8df112600               call       0xa92cf0
00831b11  83c404                   add        esp, 4
00831b14  50                       push       eax
00831b15  b928120501               mov        ecx, 0x1051228
00831b1a  e8310e0800               call       0x8b2950
00831b1f  84c0                     test       al, al
00831b21  750f                     jne        0x831b32
00831b23  5b                       pop        ebx
00831b24  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00831b27  64890d00000000           mov        dword ptr fs:[0], ecx
00831b2e  8be5                     mov        esp, ebp
00831b30  5d                       pop        ebp
00831b31  c3                       ret        
00831b32  56                       push       esi
00831b33  8b7508                   mov        esi, dword ptr [ebp + 8]
00831b36  8b5604                   mov        edx, dword ptr [esi + 4]
00831b39  8b4204                   mov        eax, dword ptr [edx + 4]
00831b3c  57                       push       edi
00831b3d  50                       push       eax
00831b3e  8bce                     mov        ecx, esi
00831b40  e81b0d0000               call       0x832860
00831b45  8b4604                   mov        eax, dword ptr [esi + 4]
00831b48  894004                   mov        dword ptr [eax + 4], eax
00831b4b  8b4604                   mov        eax, dword ptr [esi + 4]
00831b4e  895e08                   mov        dword ptr [esi + 8], ebx
00831b51  8900                     mov        dword ptr [eax], eax
00831b53  8b4604                   mov        eax, dword ptr [esi + 4]
00831b56  894008                   mov        dword ptr [eax + 8], eax
00831b59  c745e007000000           mov        dword ptr [ebp - 0x20], 7
00831b60  895ddc                   mov        dword ptr [ebp - 0x24], ebx
00831b63  66895dcc                 mov        word ptr [ebp - 0x34], bx
00831b67  8d4df3                   lea        ecx, [ebp - 0xd]
00831b6a  51                       push       ecx
00831b6b  895dfc                   mov        dword ptr [ebp - 4], ebx
00831b6e  e85ddcffff               call       0x82f7d0
00831b73  8bf8                     mov        edi, eax
00831b75  8a45f3                   mov        al, byte ptr [ebp - 0xd]
00831b78  83c404                   add        esp, 4
00831b7b  3ac3                     cmp        al, bl
00831b7d  897dec                   mov        dword ptr [ebp - 0x14], edi
00831b80  0f84b2000000             je         0x831c38
00831b86  8d55c8                   lea        edx, [ebp - 0x38]
00831b89  52                       push       edx
00831b8a  e881ebffff               call       0x830710
00831b8f  83c404                   add        esp, 4
00831b92  84c0                     test       al, al
00831b94  0f849e000000             je         0x831c38
00831b9a  8d45ec                   lea        eax, [ebp - 0x14]
00831b9d  50                       push       eax
00831b9e  8d4de4                   lea        ecx, [ebp - 0x1c]
00831ba1  51                       push       ecx
00831ba2  8bce                     mov        ecx, esi
00831ba4  e86727c0ff               call       0x434310
00831ba9  8b4e04                   mov        ecx, dword ptr [esi + 4]
00831bac  3908                     cmp        dword ptr [eax], ecx
00831bae  7555                     jne        0x831c05
00831bb0  6aff                     push       -1
00831bb2  897da8                   mov        dword ptr [ebp - 0x58], edi
00831bb5  53                       push       ebx
00831bb6  8d55c8                   lea        edx, [ebp - 0x38]
00831bb9  bf07000000               mov        edi, 7
00831bbe  52                       push       edx
00831bbf  8d4dac                   lea        ecx, [ebp - 0x54]
00831bc2  897dc4                   mov        dword ptr [ebp - 0x3c], edi
00831bc5  895dc0                   mov        dword ptr [ebp - 0x40], ebx
00831bc8  66895db0                 mov        word ptr [ebp - 0x50], bx
00831bcc  e88f11bdff               call       0x402d60
00831bd1  8d45a8                   lea        eax, [ebp - 0x58]
00831bd4  50                       push       eax
00831bd5  8d4de8                   lea        ecx, [ebp - 0x18]
00831bd8  51                       push       ecx
00831bd9  8bce                     mov        ecx, esi
00831bdb  c645fc01                 mov        byte ptr [ebp - 4], 1
00831bdf  e86c110000               call       0x832d50
00831be4  837dc408                 cmp        dword ptr [ebp - 0x3c], 8
00831be8  885dfc                   mov        byte ptr [ebp - 4], bl
00831beb  720c                     jb         0x831bf9
00831bed  8b55b0                   mov        edx, dword ptr [ebp - 0x50]
00831bf0  52                       push       edx
00831bf1  e8e7e33c00               call       0xbfffdd
00831bf6  83c404                   add        esp, 4
00831bf9  897dc4                   mov        dword ptr [ebp - 0x3c], edi
00831bfc  895dc0                   mov        dword ptr [ebp - 0x40], ebx
00831bff  66895db0                 mov        word ptr [ebp - 0x50], bx
00831c03  eb17                     jmp        0x831c1c
00831c05  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00831c08  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00831c0b  57                       push       edi
00831c0c  50                       push       eax
00831c0d  51                       push       ecx
00831c0e  68a03be100               push       0xe13ba0
00831c13  ff15bc2eff00             call       dword ptr [0xff2ebc]
00831c19  83c410                   add        esp, 0x10
00831c1c  8d55f3                   lea        edx, [ebp - 0xd]
00831c1f  52                       push       edx
00831c20  e8abdbffff               call       0x82f7d0
00831c25  8bf8                     mov        edi, eax
00831c27  8a45f3                   mov        al, byte ptr [ebp - 0xd]
00831c2a  83c404                   add        esp, 4
00831c2d  3ac3                     cmp        al, bl
00831c2f  897dec                   mov        dword ptr [ebp - 0x14], edi
00831c32  0f854effffff             jne        0x831b86
00831c38  837de008                 cmp        dword ptr [ebp - 0x20], 8
00831c3c  5f                       pop        edi
00831c3d  5e                       pop        esi
00831c3e  720c                     jb         0x831c4c
00831c40  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
00831c43  50                       push       eax
00831c44  e894e33c00               call       0xbfffdd
00831c49  83c404                   add        esp, 4
00831c4c  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00831c4f  b001                     mov        al, 1
00831c51  5b                       pop        ebx
00831c52  64                       .byte      0x64
00831c53  89                       .byte      0x89
00831c54  0d                       .byte      0x0d
00831c55  0000                     add        byte ptr [eax], al
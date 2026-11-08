0040c850  55                       push       ebp
0040c851  8bec                     mov        ebp, esp
0040c853  6aff                     push       -1
0040c855  68c0ffc400               push       0xc4ffc0
0040c85a  64a100000000             mov        eax, dword ptr fs:[0]
0040c860  50                       push       eax
0040c861  64892500000000           mov        dword ptr fs:[0], esp
0040c868  81ec60020000             sub        esp, 0x260
0040c86e  8b0d1ca90d01             mov        ecx, dword ptr [0x10da91c]
0040c874  8b01                     mov        eax, dword ptr [ecx]
0040c876  56                       push       esi
0040c877  57                       push       edi
0040c878  6820a90d01               push       0x10da920
0040c87d  6a03                     push       3
0040c87f  ff5004                   call       dword ptr [eax + 4]
0040c882  8bf0                     mov        esi, eax
0040c884  33ff                     xor        edi, edi
0040c886  3bf7                     cmp        esi, edi
0040c888  7d4a                     jge        0x40c8d4
0040c88a  684c020000               push       0x24c
0040c88f  e8ac496400               call       0xa51240
0040c894  50                       push       eax
0040c895  ff15bc2eff00             call       dword ptr [0xff2ebc]
0040c89b  83c408                   add        esp, 8
0040c89e  57                       push       edi
0040c89f  684d020000               push       0x24d
0040c8a4  e897496400               call       0xa51240
0040c8a9  83c404                   add        esp, 4
0040c8ac  50                       push       eax
0040c8ad  684c020000               push       0x24c
0040c8b2  e889496400               call       0xa51240
0040c8b7  83c404                   add        esp, 4
0040c8ba  50                       push       eax
0040c8bb  57                       push       edi
0040c8bc  ff1558f04001             call       dword ptr [0x140f058]
0040c8c2  5f                       pop        edi
0040c8c3  8bc6                     mov        eax, esi
0040c8c5  5e                       pop        esi
0040c8c6  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0040c8c9  64890d00000000           mov        dword ptr fs:[0], ecx
0040c8d0  8be5                     mov        esp, ebp
0040c8d2  5d                       pop        ebp
0040c8d3  c3                       ret        
0040c8d4  53                       push       ebx
0040c8d5  57                       push       edi
0040c8d6  68543ccb00               push       0xcb3c54
0040c8db  e8873d7f00               call       0xc00667
0040c8e0  57                       push       edi
0040c8e1  683c3ccb00               push       0xcb3c3c
0040c8e6  e87c3d7f00               call       0xc00667
0040c8eb  bb07000000               mov        ebx, 7
0040c8f0  895db4                   mov        dword ptr [ebp - 0x4c], ebx
0040c8f3  897db0                   mov        dword ptr [ebp - 0x50], edi
0040c8f6  66897da0                 mov        word ptr [ebp - 0x60], di
0040c8fa  68203ccb00               push       0xcb3c20
0040c8ff  897dfc                   mov        dword ptr [ebp - 4], edi
0040c902  e8c6347f00               call       0xbffdcd
0040c907  83c414                   add        esp, 0x14
0040c90a  50                       push       eax
0040c90b  68203ccb00               push       0xcb3c20
0040c910  8d4d9c                   lea        ecx, [ebp - 0x64]
0040c913  e86865ffff               call       0x402e80
0040c918  8d4d9c                   lea        ecx, [ebp - 0x64]
0040c91b  51                       push       ecx
0040c91c  8b0d20a90d01             mov        ecx, dword ptr [0x10da920]
0040c922  e8790a7000               call       0xb0d3a0
0040c927  837db408                 cmp        dword ptr [ebp - 0x4c], 8
0040c92b  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
0040c932  720c                     jb         0x40c940
0040c934  8b55a0                   mov        edx, dword ptr [ebp - 0x60]
0040c937  52                       push       edx
0040c938  e8a0367f00               call       0xbfffdd
0040c93d  83c404                   add        esp, 4
0040c940  8b0d1ca90d01             mov        ecx, dword ptr [0x10da91c]
0040c946  68e0010000               push       0x1e0
0040c94b  6880020000               push       0x280
0040c950  895db4                   mov        dword ptr [ebp - 0x4c], ebx
0040c953  897db0                   mov        dword ptr [ebp - 0x50], edi
0040c956  66897da0                 mov        word ptr [ebp - 0x60], di
0040c95a  e8e1f96f00               call       0xb0c340
0040c95f  a148280001               mov        eax, dword ptr [0x1002848]
0040c964  8a8800110000             mov        cl, byte ptr [eax + 0x1100]
0040c96a  884df0                   mov        byte ptr [ebp - 0x10], cl
0040c96d  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
0040c970  8b0d20a90d01             mov        ecx, dword ptr [0x10da920]
0040c976  52                       push       edx
0040c977  6a10                     push       0x10
0040c979  68e0010000               push       0x1e0
0040c97e  6880020000               push       0x280
0040c983  e868097000               call       0xb0d2f0
0040c988  8bf0                     mov        esi, eax
0040c98a  3bf7                     cmp        esi, edi
0040c98c  7d4b                     jge        0x40c9d9
0040c98e  684e020000               push       0x24e
0040c993  e8a8486400               call       0xa51240
0040c998  50                       push       eax
0040c999  ff15bc2eff00             call       dword ptr [0xff2ebc]
0040c99f  83c408                   add        esp, 8
0040c9a2  57                       push       edi
0040c9a3  684f020000               push       0x24f
0040c9a8  e893486400               call       0xa51240
0040c9ad  83c404                   add        esp, 4
0040c9b0  50                       push       eax
0040c9b1  684e020000               push       0x24e
0040c9b6  e885486400               call       0xa51240
0040c9bb  83c404                   add        esp, 4
0040c9be  50                       push       eax
0040c9bf  57                       push       edi
0040c9c0  ff1558f04001             call       dword ptr [0x140f058]
0040c9c6  5b                       pop        ebx
0040c9c7  5f                       pop        edi
0040c9c8  8bc6                     mov        eax, esi
0040c9ca  5e                       pop        esi
0040c9cb  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0040c9ce  64890d00000000           mov        dword ptr fs:[0], ecx
0040c9d5  8be5                     mov        esp, ebp
0040c9d7  5d                       pop        ebp
0040c9d8  c3                       ret        
0040c9d9  8b3520a90d01             mov        esi, dword ptr [0x10da920]
0040c9df  895dec                   mov        dword ptr [ebp - 0x14], ebx
0040c9e2  897de8                   mov        dword ptr [ebp - 0x18], edi
0040c9e5  66897dd8                 mov        word ptr [ebp - 0x28], di
0040c9e9  68043ccb00               push       0xcb3c04
0040c9ee  8d4db8                   lea        ecx, [ebp - 0x48]
0040c9f1  c745fc01000000           mov        dword ptr [ebp - 4], 1
0040c9f8  e8f36bffff               call       0x4035f0
0040c9fd  8d8594fdffff             lea        eax, [ebp - 0x26c]
0040ca03  50                       push       eax
0040ca04  57                       push       edi
0040ca05  57                       push       edi
0040ca06  6805800000               push       0x8005
0040ca0b  57                       push       edi
0040ca0c  c645fc02                 mov        byte ptr [ebp - 4], 2
0040ca10  32db                     xor        bl, bl
0040ca12  ff1560f04001             call       dword ptr [0x140f060]
0040ca18  85c0                     test       eax, eax
0040ca1a  7c57                     jl         0x40ca73
0040ca1c  8d8d94fdffff             lea        ecx, [ebp - 0x26c]
0040ca22  51                       push       ecx
0040ca23  b301                     mov        bl, 1
0040ca25  e8a3337f00               call       0xbffdcd
0040ca2a  83c404                   add        esp, 4
0040ca2d  50                       push       eax
0040ca2e  8d9594fdffff             lea        edx, [ebp - 0x26c]
0040ca34  52                       push       edx
0040ca35  8d4dd4                   lea        ecx, [ebp - 0x2c]
0040ca38  e84364ffff               call       0x402e80
0040ca3d  68f83bcb00               push       0xcb3bf8
0040ca42  e886337f00               call       0xbffdcd
0040ca47  83c404                   add        esp, 4
0040ca4a  50                       push       eax
0040ca4b  68f83bcb00               push       0xcb3bf8
0040ca50  8d4dd4                   lea        ecx, [ebp - 0x2c]
0040ca53  e8881f0000               call       0x40e9e0
0040ca58  68dc3bcb00               push       0xcb3bdc
0040ca5d  e86b337f00               call       0xbffdcd
0040ca62  83c404                   add        esp, 4
0040ca65  50                       push       eax
0040ca66  68dc3bcb00               push       0xcb3bdc
0040ca6b  8d4dd4                   lea        ecx, [ebp - 0x2c]
0040ca6e  e86d1f0000               call       0x40e9e0
0040ca73  8b863c200000             mov        eax, dword ptr [esi + 0x203c]
0040ca79  6a01                     push       1
0040ca7b  8d4db8                   lea        ecx, [ebp - 0x48]
0040ca7e  51                       push       ecx
0040ca7f  8d55d4                   lea        edx, [ebp - 0x2c]
0040ca82  52                       push       edx
0040ca83  50                       push       eax
0040ca84  e837b47000               call       0xb17ec0
0040ca89  83c410                   add        esp, 0x10
0040ca8c  84db                     test       bl, bl
0040ca8e  a3e8012101               mov        dword ptr [0x12101e8], eax
0040ca93  741a                     je         0x40caaf
0040ca95  6822eb0000               push       0xeb22
0040ca9a  e8a1476400               call       0xa51240
0040ca9f  83c404                   add        esp, 4
0040caa2  50                       push       eax
0040caa3  e8881b0000               call       0x40e630
0040caa8  8bc8                     mov        ecx, eax
0040caaa  e881230000               call       0x40ee30
0040caaf  8b0d20a90d01             mov        ecx, dword ptr [0x10da920]
0040cab5  8b01                     mov        eax, dword ptr [ecx]
0040cab7  57                       push       edi
0040cab8  682ca90d01               push       0x10da92c
0040cabd  6a07                     push       7
0040cabf  ff5008                   call       dword ptr [eax + 8]
0040cac2  8bf0                     mov        esi, eax
0040cac4  3bf7                     cmp        esi, edi
0040cac6  7d5b                     jge        0x40cb23
0040cac8  6850020000               push       0x250
0040cacd  e86e476400               call       0xa51240
0040cad2  50                       push       eax
0040cad3  ff15bc2eff00             call       dword ptr [0xff2ebc]
0040cad9  83c408                   add        esp, 8
0040cadc  57                       push       edi
0040cadd  6851020000               push       0x251
0040cae2  e859476400               call       0xa51240
0040cae7  83c404                   add        esp, 4
0040caea  50                       push       eax
0040caeb  6850020000               push       0x250
0040caf0  e84b476400               call       0xa51240
0040caf5  83c404                   add        esp, 4
0040caf8  50                       push       eax
0040caf9  57                       push       edi
0040cafa  ff1558f04001             call       dword ptr [0x140f058]
0040cb00  8d4db8                   lea        ecx, [ebp - 0x48]
0040cb03  e868157800               call       0xb8e070
0040cb08  8d4dd4                   lea        ecx, [ebp - 0x2c]
0040cb0b  e860157800               call       0xb8e070
0040cb10  5b                       pop        ebx
0040cb11  5f                       pop        edi
0040cb12  8bc6                     mov        eax, esi
0040cb14  5e                       pop        esi
0040cb15  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
0040cb18  64890d00000000           mov        dword ptr fs:[0], ecx
0040cb1f  8be5                     mov        esp, ebp
0040cb21  5d                       pop        ebp
0040cb22  c3                       ret        
0040cb23  8b0d1ca90d01             mov        ecx, dword ptr [0x10da91c]
0040cb29  8b11                     mov        edx, dword ptr [ecx]
0040cb2b  6824a90d01               push       0x10da924
0040cb30  6a02                     push       2
0040cb32  ff520c                   call       dword ptr [edx + 0xc]
0040cb35  8bf0                     mov        esi, eax
0040cb37  3bf7                     cmp        esi, edi
0040cb39  7d2a                     jge        0x40cb65
0040cb3b  6852020000               push       0x252
0040cb40  e8fb466400               call       0xa51240
0040cb45  50                       push       eax
0040cb46  ff15bc2eff00             call       dword ptr [0xff2ebc]
0040cb4c  83c408                   add        esp, 8
0040cb4f  57                       push       edi
0040cb50  6853020000               push       0x253
0040cb55  e8e6466400               call       0xa51240
0040cb5a  83c404                   add        esp, 4
0040cb5d  50                       push       eax
0040cb5e  6852020000               push       0x252
0040cb63  eb8b                     jmp        0x40caf0
0040cb65  8b0d24a90d01             mov        ecx, dword ptr [0x10da924]
0040cb6b  8b01                     mov        eax, dword ptr [ecx]
0040cb6d  ff5008                   call       dword ptr [eax + 8]
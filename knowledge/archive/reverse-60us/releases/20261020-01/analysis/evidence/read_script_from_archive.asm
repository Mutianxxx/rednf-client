; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 008316f0..00831ab0 (end exclusive); file offset 004316f0
; This is an instruction excerpt, not a recovered original source file.
008316f0  55                       push       ebp
008316f1  8bec                     mov        ebp, esp
008316f3  6aff                     push       -1
008316f5  6894d9c700               push       0xc7d994
008316fa  64a100000000             mov        eax, dword ptr fs:[0]
00831700  50                       push       eax
00831701  64892500000000           mov        dword ptr fs:[0], esp
00831708  81ec28030000             sub        esp, 0x328
0083170e  53                       push       ebx
0083170f  33c0                     xor        eax, eax
00831711  56                       push       esi
00831712  57                       push       edi
00831713  8bd9                     mov        ebx, ecx
00831715  c745ec07000000           mov        dword ptr [ebp - 0x14], 7
0083171c  8945e8                   mov        dword ptr [ebp - 0x18], eax
0083171f  668945d8                 mov        word ptr [ebp - 0x28], ax
00831723  8945fc                   mov        dword ptr [ebp - 4], eax
00831726  a0d810f700               mov        al, byte ptr [0xf710d8]
0083172b  84c0                     test       al, al
0083172d  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00831730  0f84fd000000             je         0x831833
00831736  bf703be100               mov        edi, 0xe13b70
0083173b  8bf0                     mov        esi, eax
0083173d  b913000000               mov        ecx, 0x13
00831742  33d2                     xor        edx, edx
00831744  f3a6                     repe cmpsb byte ptr [esi], byte ptr es:[edi]
00831746  0f84e7000000             je         0x831833
0083174c  8d4dd4                   lea        ecx, [ebp - 0x2c]
0083174f  51                       push       ecx
00831750  50                       push       eax
00831751  e8fa142600               call       0xa92c50
00831756  8b7508                   mov        esi, dword ptr [ebp + 8]
00831759  83c404                   add        esp, 4
0083175c  50                       push       eax
0083175d  56                       push       esi
0083175e  e8ed142600               call       0xa92c50
00831763  83c404                   add        esp, 4
00831766  50                       push       eax
00831767  e8a4fcffff               call       0x831410
0083176c  83c40c                   add        esp, 0xc
0083176f  3c01                     cmp        al, 1
00831771  bf08000000               mov        edi, 8
00831776  7527                     jne        0x83179f
00831778  397dec                   cmp        dword ptr [ebp - 0x14], edi
0083177b  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
0083177e  7303                     jae        0x831783
00831780  8d45d8                   lea        eax, [ebp - 0x28]
00831783  50                       push       eax
00831784  68f056cb00               push       0xcb56f0
00831789  8d95ccfcffff             lea        edx, [ebp - 0x334]
0083178f  6804010000               push       0x104
00831794  52                       push       edx
00831795  e8e50a3d00               call       0xc0227f
0083179a  83c410                   add        esp, 0x10
0083179d  eb30                     jmp        0x8317cf
0083179f  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008317a2  50                       push       eax
008317a3  e8a8142600               call       0xa92c50
008317a8  83c404                   add        esp, 4
008317ab  50                       push       eax
008317ac  56                       push       esi
008317ad  e89e142600               call       0xa92c50
008317b2  83c404                   add        esp, 4
008317b5  50                       push       eax
008317b6  68f8b8ca00               push       0xcab8f8
008317bb  8d8dccfcffff             lea        ecx, [ebp - 0x334]
008317c1  6804010000               push       0x104
008317c6  51                       push       ecx
008317c7  e8b30a3d00               call       0xc0227f
008317cc  83c414                   add        esp, 0x14
008317cf  8b4514                   mov        eax, dword ptr [ebp + 0x14]
008317d2  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
008317d5  8d55f0                   lea        edx, [ebp - 0x10]
008317d8  52                       push       edx
008317d9  50                       push       eax
008317da  51                       push       ecx
008317db  8d95ccfcffff             lea        edx, [ebp - 0x334]
008317e1  52                       push       edx
008317e2  b9a8110501               mov        ecx, 0x10511a8
008317e7  e894492200               call       0xa56180
008317ec  83f801                   cmp        eax, 1
008317ef  0f85a7020000             jne        0x831a9c
008317f5  8d85ccfcffff             lea        eax, [ebp - 0x334]
008317fb  50                       push       eax
008317fc  e8ef142600               call       0xa92cf0
00831801  50                       push       eax
00831802  685c3be100               push       0xe13b5c
00831807  68303be100               push       0xe13b30
0083180c  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
00831812  6800010000               push       0x100
00831817  51                       push       ecx
00831818  e8e00e3d00               call       0xc026fd
0083181d  8b13                     mov        edx, dword ptr [ebx]
0083181f  83c418                   add        esp, 0x18
00831822  8d85d4feffff             lea        eax, [ebp - 0x12c]
00831828  50                       push       eax
00831829  8bcb                     mov        ecx, ebx
0083182b  ff5224                   call       dword ptr [edx + 0x24]
0083182e  e931020000               jmp        0x831a64
00831833  8d4dd4                   lea        ecx, [ebp - 0x2c]
00831836  51                       push       ecx
00831837  50                       push       eax
00831838  e813142600               call       0xa92c50
0083183d  8b7508                   mov        esi, dword ptr [ebp + 8]
00831840  83c404                   add        esp, 4
00831843  50                       push       eax
00831844  56                       push       esi
00831845  e806142600               call       0xa92c50
0083184a  83c404                   add        esp, 4
0083184d  50                       push       eax
0083184e  e82df9ffff               call       0x831180
00831853  83c40c                   add        esp, 0xc
00831856  84c0                     test       al, al
00831858  bf08000000               mov        edi, 8
0083185d  7424                     je         0x831883
0083185f  397dec                   cmp        dword ptr [ebp - 0x14], edi
00831862  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00831865  7303                     jae        0x83186a
00831867  8d45d8                   lea        eax, [ebp - 0x28]
0083186a  50                       push       eax
0083186b  68f056cb00               push       0xcb56f0
00831870  8d95ccfcffff             lea        edx, [ebp - 0x334]
00831876  6804010000               push       0x104
0083187b  52                       push       edx
0083187c  e8fe093d00               call       0xc0227f
00831881  eb28                     jmp        0x8318ab
00831883  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00831886  50                       push       eax
00831887  e8c4132600               call       0xa92c50
0083188c  83c404                   add        esp, 4
0083188f  50                       push       eax
00831890  56                       push       esi
00831891  e8ba132600               call       0xa92c50
00831896  83c404                   add        esp, 4
00831899  50                       push       eax
0083189a  8d8dccfcffff             lea        ecx, [ebp - 0x334]
008318a0  68f8b8ca00               push       0xcab8f8
008318a5  51                       push       ecx
008318a6  e815deffff               call       0x82f6c0
008318ab  83c410                   add        esp, 0x10
008318ae  8d95ccfcffff             lea        edx, [ebp - 0x334]
008318b4  68a036e100               push       0xe136a0
008318b9  52                       push       edx
008318ba  e86a043d00               call       0xc01d29
008318bf  8bf0                     mov        esi, eax
008318c1  83c408                   add        esp, 8
008318c4  85f6                     test       esi, esi
008318c6  751c                     jne        0x8318e4
008318c8  8d85ccfcffff             lea        eax, [ebp - 0x334]
008318ce  50                       push       eax
008318cf  e81c142600               call       0xa92cf0
008318d4  50                       push       eax
008318d5  685c3be100               push       0xe13b5c
008318da  68103be100               push       0xe13b10
008318df  e928ffffff               jmp        0x83180c
008318e4  6a02                     push       2
008318e6  6a00                     push       0
008318e8  56                       push       esi
008318e9  e8c60d3d00               call       0xc026b4
008318ee  83c40c                   add        esp, 0xc
008318f1  85c0                     test       eax, eax
008318f3  741c                     je         0x831911
008318f5  8d8dccfcffff             lea        ecx, [ebp - 0x334]
008318fb  51                       push       ecx
008318fc  e8ef132600               call       0xa92cf0
00831901  50                       push       eax
00831902  685c3be100               push       0xe13b5c
00831907  68f03ae100               push       0xe13af0
0083190c  e984000000               jmp        0x831995
00831911  56                       push       esi
00831912  e8cd0c3d00               call       0xc025e4
00831917  6a00                     push       0
00831919  6a00                     push       0
0083191b  56                       push       esi
0083191c  8945f0                   mov        dword ptr [ebp - 0x10], eax
0083191f  e8900d3d00               call       0xc026b4
00831924  83c410                   add        esp, 0x10
00831927  85c0                     test       eax, eax
00831929  7447                     je         0x831972
0083192b  8d95ccfcffff             lea        edx, [ebp - 0x334]
00831931  52                       push       edx
00831932  e8b9132600               call       0xa92cf0
00831937  50                       push       eax
00831938  685c3be100               push       0xe13b5c
0083193d  68f03ae100               push       0xe13af0
00831942  8d85d4feffff             lea        eax, [ebp - 0x12c]
00831948  6800010000               push       0x100
0083194d  50                       push       eax
0083194e  e8aa0d3d00               call       0xc026fd
00831953  8b13                     mov        edx, dword ptr [ebx]
00831955  83c418                   add        esp, 0x18
00831958  8d85d4feffff             lea        eax, [ebp - 0x12c]
0083195e  50                       push       eax
0083195f  8bcb                     mov        ecx, ebx
00831961  ff5224                   call       dword ptr [edx + 0x24]
00831964  56                       push       esi
00831965  e812033d00               call       0xc01c7c
0083196a  83c404                   add        esp, 4
0083196d  e9f2000000               jmp        0x831a64
00831972  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00831975  3b4514                   cmp        eax, dword ptr [ebp + 0x14]
00831978  764b                     jbe        0x8319c5
0083197a  50                       push       eax
0083197b  8d8dccfcffff             lea        ecx, [ebp - 0x334]
00831981  51                       push       ecx
00831982  e869132600               call       0xa92cf0
00831987  83c404                   add        esp, 4
0083198a  50                       push       eax
0083198b  685c3be100               push       0xe13b5c
00831990  68c43ae100               push       0xe13ac4
00831995  8d95d4feffff             lea        edx, [ebp - 0x12c]
0083199b  6800010000               push       0x100
008319a0  52                       push       edx
008319a1  e8570d3d00               call       0xc026fd
008319a6  8b03                     mov        eax, dword ptr [ebx]
008319a8  83c418                   add        esp, 0x18
008319ab  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
008319b1  51                       push       ecx
008319b2  8bcb                     mov        ecx, ebx
008319b4  ff5024                   call       dword ptr [eax + 0x24]
008319b7  56                       push       esi
008319b8  e8bf023d00               call       0xc01c7c
008319bd  83c404                   add        esp, 4
008319c0  e99f000000               jmp        0x831a64
008319c5  8b5510                   mov        edx, dword ptr [ebp + 0x10]
008319c8  56                       push       esi
008319c9  6a01                     push       1
008319cb  50                       push       eax
008319cc  52                       push       edx
008319cd  e8640a3d00               call       0xc02436
008319d2  83c410                   add        esp, 0x10
008319d5  83f801                   cmp        eax, 1
008319d8  7444                     je         0x831a1e
008319da  8d85ccfcffff             lea        eax, [ebp - 0x334]
008319e0  50                       push       eax
008319e1  e80a132600               call       0xa92cf0
008319e6  50                       push       eax
008319e7  685c3be100               push       0xe13b5c
008319ec  68a43ae100               push       0xe13aa4
008319f1  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
008319f7  6800010000               push       0x100
008319fc  51                       push       ecx
008319fd  e8fb0c3d00               call       0xc026fd
00831a02  8b13                     mov        edx, dword ptr [ebx]
00831a04  83c418                   add        esp, 0x18
00831a07  8d85d4feffff             lea        eax, [ebp - 0x12c]
00831a0d  50                       push       eax
00831a0e  8bcb                     mov        ecx, ebx
00831a10  ff5224                   call       dword ptr [edx + 0x24]
00831a13  56                       push       esi
00831a14  e863023d00               call       0xc01c7c
00831a19  83c404                   add        esp, 4
00831a1c  eb46                     jmp        0x831a64
00831a1e  56                       push       esi
00831a1f  e858023d00               call       0xc01c7c
00831a24  83c404                   add        esp, 4
00831a27  85c0                     test       eax, eax
00831a29  7471                     je         0x831a9c
00831a2b  8d8dccfcffff             lea        ecx, [ebp - 0x334]
00831a31  51                       push       ecx
00831a32  e8b9122600               call       0xa92cf0
00831a37  50                       push       eax
00831a38  685c3be100               push       0xe13b5c
00831a3d  68843ae100               push       0xe13a84
00831a42  8d95d4feffff             lea        edx, [ebp - 0x12c]
00831a48  6800010000               push       0x100
00831a4d  52                       push       edx
00831a4e  e8aa0c3d00               call       0xc026fd
00831a53  8b03                     mov        eax, dword ptr [ebx]
00831a55  83c418                   add        esp, 0x18
00831a58  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
00831a5e  51                       push       ecx
00831a5f  8bcb                     mov        ecx, ebx
00831a61  ff5024                   call       dword ptr [eax + 0x24]
00831a64  a168070501               mov        eax, dword ptr [0x1050768]
00831a69  85c0                     test       eax, eax
00831a6b  7409                     je         0x831a76
00831a6d  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00831a70  52                       push       edx
00831a71  ffd0                     call       eax
00831a73  83c404                   add        esp, 4
00831a76  397dec                   cmp        dword ptr [ebp - 0x14], edi
00831a79  720c                     jb         0x831a87
00831a7b  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00831a7e  50                       push       eax
00831a7f  e859e53c00               call       0xbfffdd
00831a84  83c404                   add        esp, 4
00831a87  5f                       pop        edi
00831a88  5e                       pop        esi
00831a89  33c0                     xor        eax, eax
00831a8b  5b                       pop        ebx
00831a8c  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00831a8f  64890d00000000           mov        dword ptr fs:[0], ecx
00831a96  8be5                     mov        esp, ebp
00831a98  5d                       pop        ebp
00831a99  c21000                   ret        0x10
00831a9c  397dec                   cmp        dword ptr [ebp - 0x14], edi
00831a9f  8b75f0                   mov        esi, dword ptr [ebp - 0x10]
00831aa2  720c                     jb         0x831ab0
00831aa4  8b4dd8                   mov        ecx, dword ptr [ebp - 0x28]
00831aa7  51                       push       ecx
00831aa8  e830e53c00               call       0xbfffdd
00831aad  83c404                   add        esp, 4

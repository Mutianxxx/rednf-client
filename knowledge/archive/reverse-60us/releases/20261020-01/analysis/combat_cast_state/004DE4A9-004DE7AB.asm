004de4a9  8b4508                   mov        eax, dword ptr [ebp + 8]
004de4ac  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004de4af  83c0fb                   add        eax, -5
004de4b2  83f80a                   cmp        eax, 0xa
004de4b5  0f87200a0000             ja         0x4deedb
004de4bb  ff2485b0f24d00           jmp        dword ptr [eax*4 + 0x4df2b0]
004de4c2  8dbe20240000             lea        edi, [esi + 0x2420]
004de4c8  8bcf                     mov        ecx, edi
004de4ca  e8913bf2ff               call       0x402060
004de4cf  8b4304                   mov        eax, dword ptr [ebx + 4]
004de4d2  8b08                     mov        ecx, dword ptr [eax]
004de4d4  8d55e4                   lea        edx, [ebp - 0x1c]
004de4d7  894de4                   mov        dword ptr [ebp - 0x1c], ecx
004de4da  52                       push       edx
004de4db  8bcf                     mov        ecx, edi
004de4dd  e87e60f2ff               call       0x404560
004de4e2  8bcf                     mov        ecx, edi
004de4e4  e8773bf2ff               call       0x402060
004de4e9  85c0                     test       eax, eax
004de4eb  0f85be020000             jne        0x4de7af
004de4f1  8b4304                   mov        eax, dword ptr [ebx + 4]
004de4f4  83c004                   add        eax, 4
004de4f7  8b00                     mov        eax, dword ptr [eax]
004de4f9  898628240000             mov        dword ptr [esi + 0x2428], eax
004de4ff  8b4304                   mov        eax, dword ptr [ebx + 4]
004de502  8b4808                   mov        ecx, dword ptr [eax + 8]
004de505  83c008                   add        eax, 8
004de508  8d55e4                   lea        edx, [ebp - 0x1c]
004de50b  894de4                   mov        dword ptr [ebp - 0x1c], ecx
004de50e  8d8e2c240000             lea        ecx, [esi + 0x242c]
004de514  52                       push       edx
004de515  e84660f2ff               call       0x404560
004de51a  8b4304                   mov        eax, dword ptr [ebx + 4]
004de51d  83c00c                   add        eax, 0xc
004de520  8b00                     mov        eax, dword ptr [eax]
004de522  8d4de4                   lea        ecx, [ebp - 0x1c]
004de525  8dbe34240000             lea        edi, [esi + 0x2434]
004de52b  51                       push       ecx
004de52c  8bcf                     mov        ecx, edi
004de52e  8945e4                   mov        dword ptr [ebp - 0x1c], eax
004de531  e82a60f2ff               call       0x404560
004de536  8b4304                   mov        eax, dword ptr [ebx + 4]
004de539  8b5010                   mov        edx, dword ptr [eax + 0x10]
004de53c  83c010                   add        eax, 0x10
004de53f  8d45e4                   lea        eax, [ebp - 0x1c]
004de542  50                       push       eax
004de543  8d8e3c240000             lea        ecx, [esi + 0x243c]
004de549  8955e4                   mov        dword ptr [ebp - 0x1c], edx
004de54c  e80f60f2ff               call       0x404560
004de551  8b4304                   mov        eax, dword ptr [ebx + 4]
004de554  8b4814                   mov        ecx, dword ptr [eax + 0x14]
004de557  83c014                   add        eax, 0x14
004de55a  898e44240000             mov        dword ptr [esi + 0x2444], ecx
004de560  8b4304                   mov        eax, dword ptr [ebx + 4]
004de563  8b5018                   mov        edx, dword ptr [eax + 0x18]
004de566  8b401c                   mov        eax, dword ptr [eax + 0x1c]
004de569  8bcb                     mov        ecx, ebx
004de56b  8955e4                   mov        dword ptr [ebp - 0x1c], edx
004de56e  898648240000             mov        dword ptr [esi + 0x2448], eax
004de574  e81782f8ff               call       0x466790
004de579  83f808                   cmp        eax, 8
004de57c  760e                     jbe        0x4de58c
004de57e  8b4304                   mov        eax, dword ptr [ebx + 4]
004de581  8b4820                   mov        ecx, dword ptr [eax + 0x20]
004de584  83c020                   add        eax, 0x20
004de587  894de8                   mov        dword ptr [ebp - 0x18], ecx
004de58a  eb07                     jmp        0x4de593
004de58c  c745e8e8030000           mov        dword ptr [ebp - 0x18], 0x3e8
004de593  8bcb                     mov        ecx, ebx
004de595  e8f681f8ff               call       0x466790
004de59a  83f809                   cmp        eax, 9
004de59d  760a                     jbe        0x4de5a9
004de59f  8b4304                   mov        eax, dword ptr [ebx + 4]
004de5a2  83c024                   add        eax, 0x24
004de5a5  8b00                     mov        eax, dword ptr [eax]
004de5a7  eb05                     jmp        0x4de5ae
004de5a9  b8e8030000               mov        eax, 0x3e8
004de5ae  8bcb                     mov        ecx, ebx
004de5b0  89864c240000             mov        dword ptr [esi + 0x244c], eax
004de5b6  e8d581f8ff               call       0x466790
004de5bb  83f80a                   cmp        eax, 0xa
004de5be  760e                     jbe        0x4de5ce
004de5c0  8b5b04                   mov        ebx, dword ptr [ebx + 4]
004de5c3  8b5328                   mov        edx, dword ptr [ebx + 0x28]
004de5c6  83c328                   add        ebx, 0x28
004de5c9  8955ec                   mov        dword ptr [ebp - 0x14], edx
004de5cc  eb07                     jmp        0x4de5d5
004de5ce  c745ecffffffff           mov        dword ptr [ebp - 0x14], 0xffffffff
004de5d5  8d45ec                   lea        eax, [ebp - 0x14]
004de5d8  50                       push       eax
004de5d9  8d8e50240000             lea        ecx, [esi + 0x2450]
004de5df  e87c5ff2ff               call       0x404560
004de5e4  83be2824000002           cmp        dword ptr [esi + 0x2428], 2
004de5eb  8b1e                     mov        ebx, dword ptr [esi]
004de5ed  750a                     jne        0x4de5f9
004de5ef  8bce                     mov        ecx, esi
004de5f1  ff936c030000             call       dword ptr [ebx + 0x36c]
004de5f7  eb0f                     jmp        0x4de608
004de5f9  8b8e44240000             mov        ecx, dword ptr [esi + 0x2444]
004de5ff  51                       push       ecx
004de600  8bce                     mov        ecx, esi
004de602  ff93e0050000             call       dword ptr [ebx + 0x5e0]
004de608  8bce                     mov        ecx, esi
004de60a  50                       push       eax
004de60b  ff93f0000000             call       dword ptr [ebx + 0xf0]
004de611  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
004de614  8b16                     mov        edx, dword ptr [esi]
004de616  680000803f               push       0x3f800000
004de61b  680000803f               push       0x3f800000
004de620  50                       push       eax
004de621  50                       push       eax
004de622  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
004de625  50                       push       eax
004de626  50                       push       eax
004de627  8bce                     mov        ecx, esi
004de629  ff9294040000             call       dword ptr [edx + 0x494]
004de62f  8d8e20160000             lea        ecx, [esi + 0x1620]
004de635  e8263af2ff               call       0x402060
004de63a  8bcf                     mov        ecx, edi
004de63c  8bd8                     mov        ebx, eax
004de63e  e81d3af2ff               call       0x402060
004de643  69c0e8030000             imul       eax, eax, 0x3e8
004de649  99                       cdq        
004de64a  f7fb                     idiv       ebx
004de64c  8bcf                     mov        ecx, edi
004de64e  8945e8                   mov        dword ptr [ebp - 0x18], eax
004de651  8d45e8                   lea        eax, [ebp - 0x18]
004de654  50                       push       eax
004de655  e8065ff2ff               call       0x404560
004de65a  837de404                 cmp        dword ptr [ebp - 0x1c], 4
004de65e  7514                     jne        0x4de674
004de660  8b1e                     mov        ebx, dword ptr [esi]
004de662  6a00                     push       0
004de664  8bcf                     mov        ecx, edi
004de666  e8f539f2ff               call       0x402060
004de66b  50                       push       eax
004de66c  8bce                     mov        ecx, esi
004de66e  ff9354050000             call       dword ptr [ebx + 0x554]
004de674  8bcf                     mov        ecx, edi
004de676  e8e539f2ff               call       0x402060
004de67b  85c0                     test       eax, eax
004de67d  7528                     jne        0x4de6a7
004de67f  8b9e04010000             mov        ebx, dword ptr [esi + 0x104]
004de685  8bcb                     mov        ecx, ebx
004de687  e8d44ffbff               call       0x493660
004de68c  48                       dec        eax
004de68d  50                       push       eax
004de68e  8bcb                     mov        ecx, ebx
004de690  e8cbbcfdff               call       0x4ba360
004de695  8d4de4                   lea        ecx, [ebp - 0x1c]
004de698  51                       push       ecx
004de699  8bcf                     mov        ecx, edi
004de69b  c745e446000000           mov        dword ptr [ebp - 0x1c], 0x46
004de6a2  e8b95ef2ff               call       0x404560
004de6a7  8b8628240000             mov        eax, dword ptr [esi + 0x2428]
004de6ad  83f801                   cmp        eax, 1
004de6b0  7409                     je         0x4de6bb
004de6b2  83f802                   cmp        eax, 2
004de6b5  0f859e000000             jne        0x4de759
004de6bb  8bce                     mov        ecx, esi
004de6bd  e8ced9fbff               call       0x49c090
004de6c2  84c0                     test       al, al
004de6c4  7440                     je         0x4de706
004de6c6  8b16                     mov        edx, dword ptr [esi]
004de6c8  8bce                     mov        ecx, esi
004de6ca  ff5234                   call       dword ptr [edx + 0x34]
004de6cd  84c0                     test       al, al
004de6cf  7435                     je         0x4de706
004de6d1  8b8644270000             mov        eax, dword ptr [esi + 0x2744]
004de6d7  85c0                     test       eax, eax
004de6d9  742b                     je         0x4de706
004de6db  8d8e2c240000             lea        ecx, [esi + 0x242c]
004de6e1  e87a39f2ff               call       0x402060
004de6e6  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004de6ec  50                       push       eax
004de6ed  e82eeff9ff               call       0x47d620
004de6f2  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004de6f8  50                       push       eax
004de6f9  e8b25df2ff               call       0x4044b0
004de6fe  50                       push       eax
004de6ff  8bce                     mov        ecx, esi
004de701  e87a4bfeff               call       0x4c3280
004de706  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004de70c  7539                     jne        0x4de747
004de70e  8b8644270000             mov        eax, dword ptr [esi + 0x2744]
004de714  85c0                     test       eax, eax
004de716  742f                     je         0x4de747
004de718  8d8e2c240000             lea        ecx, [esi + 0x242c]
004de71e  e83d39f2ff               call       0x402060
004de723  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004de729  50                       push       eax
004de72a  e8f1eef9ff               call       0x47d620
004de72f  83f8ff                   cmp        eax, -1
004de732  7413                     je         0x4de747
004de734  8b8e44270000             mov        ecx, dword ptr [esi + 0x2744]
004de73a  50                       push       eax
004de73b  e8705df2ff               call       0x4044b0
004de740  8b10                     mov        edx, dword ptr [eax]
004de742  8bc8                     mov        ecx, eax
004de744  ff5268                   call       dword ptr [edx + 0x68]
004de747  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
004de74a  33c0                     xor        eax, eax
004de74c  83fa0a                   cmp        edx, 0xa
004de74f  0f94c0                   sete       al
004de752  40                       inc        eax
004de753  898698240000             mov        dword ptr [esi + 0x2498], eax
004de759  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004de75c  8b16                     mov        edx, dword ptr [esi]
004de75e  6a00                     push       0
004de760  6a00                     push       0
004de762  6a00                     push       0
004de764  6a00                     push       0
004de766  6a00                     push       0
004de768  6a00                     push       0
004de76a  8bce                     mov        ecx, esi
004de76c  ff9288040000             call       dword ptr [edx + 0x488]
004de772  8b06                     mov        eax, dword ptr [esi]
004de774  6a00                     push       0
004de776  6a00                     push       0
004de778  6a00                     push       0
004de77a  6a00                     push       0
004de77c  6a00                     push       0
004de77e  6a01                     push       1
004de780  8bce                     mov        ecx, esi
004de782  ff9088040000             call       dword ptr [eax + 0x488]
004de788  8b16                     mov        edx, dword ptr [esi]
004de78a  6a00                     push       0
004de78c  6a04                     push       4
004de78e  6a04                     push       4
004de790  8bce                     mov        ecx, esi
004de792  ff929c040000             call       dword ptr [edx + 0x49c]
004de798  6a00                     push       0
004de79a  6a02                     push       2
004de79c  8bce                     mov        ecx, esi
004de79e  e81db9fdff               call       0x4ba0c0
004de7a3  c6866c24000000           mov        byte ptr [esi + 0x246c], 0
004de7aa  e9                       .byte      0xe9
004eb600  55                       push       ebp
004eb601  8bec                     mov        ebp, esp
004eb603  56                       push       esi
004eb604  57                       push       edi
004eb605  8bf1                     mov        esi, ecx
004eb607  8b06                     mov        eax, dword ptr [esi]
004eb609  6a21                     push       0x21
004eb60b  ff502c                   call       dword ptr [eax + 0x2c]
004eb60e  84c0                     test       al, al
004eb610  8b7d08                   mov        edi, dword ptr [ebp + 8]
004eb613  7511                     jne        0x4eb626
004eb615  8b17                     mov        edx, dword ptr [edi]
004eb617  6a21                     push       0x21
004eb619  8bcf                     mov        ecx, edi
004eb61b  ff522c                   call       dword ptr [edx + 0x2c]
004eb61e  84c0                     test       al, al
004eb620  0f8430010000             je         0x4eb756
004eb626  8b06                     mov        eax, dword ptr [esi]
004eb628  8bce                     mov        ecx, esi
004eb62a  ff90fc010000             call       dword ptr [eax + 0x1fc]
004eb630  85c0                     test       eax, eax
004eb632  0f841e010000             je         0x4eb756
004eb638  8b16                     mov        edx, dword ptr [esi]
004eb63a  8bce                     mov        ecx, esi
004eb63c  ff9200020000             call       dword ptr [edx + 0x200]
004eb642  85c0                     test       eax, eax
004eb644  0f840c010000             je         0x4eb756
004eb64a  8b07                     mov        eax, dword ptr [edi]
004eb64c  8bcf                     mov        ecx, edi
004eb64e  ff90fc010000             call       dword ptr [eax + 0x1fc]
004eb654  85c0                     test       eax, eax
004eb656  0f84fa000000             je         0x4eb756
004eb65c  8b17                     mov        edx, dword ptr [edi]
004eb65e  8bcf                     mov        ecx, edi
004eb660  ff9200020000             call       dword ptr [edx + 0x200]
004eb666  85c0                     test       eax, eax
004eb668  0f84e8000000             je         0x4eb756
004eb66e  8b06                     mov        eax, dword ptr [esi]
004eb670  57                       push       edi
004eb671  8bce                     mov        ecx, esi
004eb673  ff9048020000             call       dword ptr [eax + 0x248]
004eb679  84c0                     test       al, al
004eb67b  0f84d5000000             je         0x4eb756
004eb681  8b16                     mov        edx, dword ptr [esi]
004eb683  6a21                     push       0x21
004eb685  8bce                     mov        ecx, esi
004eb687  ff522c                   call       dword ptr [edx + 0x2c]
004eb68a  84c0                     test       al, al
004eb68c  745d                     je         0x4eb6eb
004eb68e  8b06                     mov        eax, dword ptr [esi]
004eb690  8bce                     mov        ecx, esi
004eb692  ff903c030000             call       dword ptr [eax + 0x33c]
004eb698  8b4008                   mov        eax, dword ptr [eax + 8]
004eb69b  48                       dec        eax
004eb69c  83f803                   cmp        eax, 3
004eb69f  774a                     ja         0x4eb6eb
004eb6a1  ff248560b74e00           jmp        dword ptr [eax*4 + 0x4eb760]
004eb6a8  8bce                     mov        ecx, esi
004eb6aa  e8c18ff9ff               call       0x484670
004eb6af  84c0                     test       al, al
004eb6b1  7538                     jne        0x4eb6eb
004eb6b3  5f                       pop        edi
004eb6b4  b001                     mov        al, 1
004eb6b6  5e                       pop        esi
004eb6b7  5d                       pop        ebp
004eb6b8  c20400                   ret        4
004eb6bb  8b17                     mov        edx, dword ptr [edi]
004eb6bd  53                       push       ebx
004eb6be  8bcf                     mov        ecx, edi
004eb6c0  ff92c4010000             call       dword ptr [edx + 0x1c4]
004eb6c6  8bd8                     mov        ebx, eax
004eb6c8  8b06                     mov        eax, dword ptr [esi]
004eb6ca  8bce                     mov        ecx, esi
004eb6cc  ff90c4010000             call       dword ptr [eax + 0x1c4]
004eb6d2  3bc3                     cmp        eax, ebx
004eb6d4  5b                       pop        ebx
004eb6d5  7414                     je         0x4eb6eb
004eb6d7  5f                       pop        edi
004eb6d8  b001                     mov        al, 1
004eb6da  5e                       pop        esi
004eb6db  5d                       pop        ebp
004eb6dc  c20400                   ret        4
004eb6df  57                       push       edi
004eb6e0  8bce                     mov        ecx, esi
004eb6e2  e8e9faffff               call       0x4eb1d0
004eb6e7  84c0                     test       al, al
004eb6e9  7457                     je         0x4eb742
004eb6eb  8b17                     mov        edx, dword ptr [edi]
004eb6ed  6a21                     push       0x21
004eb6ef  8bcf                     mov        ecx, edi
004eb6f1  ff522c                   call       dword ptr [edx + 0x2c]
004eb6f4  84c0                     test       al, al
004eb6f6  745e                     je         0x4eb756
004eb6f8  8b07                     mov        eax, dword ptr [edi]
004eb6fa  8bcf                     mov        ecx, edi
004eb6fc  ff903c030000             call       dword ptr [eax + 0x33c]
004eb702  8b4008                   mov        eax, dword ptr [eax + 8]
004eb705  48                       dec        eax
004eb706  83f803                   cmp        eax, 3
004eb709  774b                     ja         0x4eb756
004eb70b  ff248570b74e00           jmp        dword ptr [eax*4 + 0x4eb770]
004eb712  8b16                     mov        edx, dword ptr [esi]
004eb714  8bce                     mov        ecx, esi
004eb716  ff9204020000             call       dword ptr [edx + 0x204]
004eb71c  85c0                     test       eax, eax
004eb71e  7f36                     jg         0x4eb756
004eb720  5f                       pop        edi
004eb721  b001                     mov        al, 1
004eb723  5e                       pop        esi
004eb724  5d                       pop        ebp
004eb725  c20400                   ret        4
004eb728  8b07                     mov        eax, dword ptr [edi]
004eb72a  8bcf                     mov        ecx, edi
004eb72c  ff90c4010000             call       dword ptr [eax + 0x1c4]
004eb732  8b16                     mov        edx, dword ptr [esi]
004eb734  8bce                     mov        ecx, esi
004eb736  8bf8                     mov        edi, eax
004eb738  ff92c4010000             call       dword ptr [edx + 0x1c4]
004eb73e  3bc7                     cmp        eax, edi
004eb740  7414                     je         0x4eb756
004eb742  5f                       pop        edi
004eb743  b001                     mov        al, 1
004eb745  5e                       pop        esi
004eb746  5d                       pop        ebp
004eb747  c20400                   ret        4
004eb74a  56                       push       esi
004eb74b  8bcf                     mov        ecx, edi
004eb74d  e87efaffff               call       0x4eb1d0
004eb752  84c0                     test       al, al
004eb754  74ec                     je         0x4eb742
004eb756  5f                       pop        edi
004eb757  32c0                     xor        al, al
004eb759  5e                       pop        esi
004eb75a  5d                       pop        ebp
004eb75b  c20400                   ret        4
004eb75e  8bff                     mov        edi, edi
004eb760  a8b6                     test       al, 0xb6
004eb762  4e                       dec        esi
004eb763  00df                     add        bh, bl
004eb765  b64e                     mov        dh, 0x4e
004eb767  00bbb64e00bb             add        byte ptr [ebx - 0x44ffb14a], bh
004eb76d  b64e                     mov        dh, 0x4e
004eb76f  0012                     add        byte ptr [edx], dl
004eb771  b74e                     mov        bh, 0x4e
004eb773  004ab7                   add        byte ptr [edx - 0x49], cl
004eb776  4e                       dec        esi
004eb777  0028                     add        byte ptr [eax], ch
004eb779  b74e                     mov        bh, 0x4e
004eb77b  0028                     add        byte ptr [eax], ch
004eb77d  b74e                     mov        bh, 0x4e
004eb77f  00                       .byte      0x00

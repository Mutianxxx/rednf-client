012ee7c9 9c                       pushfd     
012ee7ca 68ff4c0000               push       0x4cff
012ee7cf 891424                   mov        dword ptr [esp], edx
012ee7d2 68c7740000               push       0x74c7
012ee7d7 892424                   mov        dword ptr [esp], esp
012ee7da 83ec04                   sub        esp, 4
012ee7dd 890c24                   mov        dword ptr [esp], ecx
012ee7e0 55                       push       ebp
012ee7e1 bdcf754e2e               mov        ebp, 0x2e4e75cf
012ee7e6 81f5cb754e2e             xor        ebp, 0x2e4e75cb
012ee7ec 55                       push       ebp
012ee7ed ff3424                   push       dword ptr [esp]
012ee7f0 59                       pop        ecx
012ee7f1 83c404                   add        esp, 4
012ee7f4 8b2c24                   mov        ebp, dword ptr [esp]
012ee7f7 83c404                   add        esp, 4
012ee7fa 814424048465e811         add        dword ptr [esp + 4], 0x11e86584
012ee802 014c2404                 add        dword ptr [esp + 4], ecx
012ee806 816c24048465e811         sub        dword ptr [esp + 4], 0x11e86584
012ee80e 59                       pop        ecx
012ee80f 5a                       pop        edx
012ee810 68627e0000               push       0x7e62
012ee815 893c24                   mov        dword ptr [esp], edi
012ee818 bf9e76ca64               mov        edi, 0x64ca769e
012ee81d f7d7                     not        edi
012ee81f 50                       push       eax
012ee820 b81e7a1d72               mov        eax, 0x721d7a1e
012ee825 f7d8                     neg        eax
012ee827 40                       inc        eax
012ee828 058203530d               add        eax, 0xd530382
012ee82d 31c7                     xor        edi, eax
012ee82f 58                       pop        eax
012ee830 01fa                     add        edx, edi
012ee832 5f                       pop        edi
012ee833 53                       push       ebx
012ee834 bb04000000               mov        ebx, 4
012ee839 81eaef7f9712             sub        edx, 0x12977fef
012ee83f 29da                     sub        edx, ebx
012ee841 81c2ef7f9712             add        edx, 0x12977fef

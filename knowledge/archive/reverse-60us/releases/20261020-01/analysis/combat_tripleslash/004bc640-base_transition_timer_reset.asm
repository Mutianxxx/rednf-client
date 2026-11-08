004bc640  92                       xchg       edx, eax
004bc641  0c01                     or         al, 1
004bc643  0000                     add        byte ptr [eax], al
004bc645  8a4510                   mov        al, byte ptr [ebp + 0x10]
004bc648  84c0                     test       al, al
004bc64a  7418                     je         0x4bc664
004bc64c  8dbe64150000             lea        edi, [esi + 0x1564]
004bc652  8bcf                     mov        ecx, edi
004bc654  e89788f4ff               call       0x404ef0
004bc659  6a00                     push       0
004bc65b  6a00                     push       0
004bc65d  8bcf                     mov        ecx, edi
004bc65f  e8fca86400               call       0xb06f60
004bc664  8a4514                   mov        al, byte ptr [ebp + 0x14]
004bc667  84c0                     test       al, al
004bc669  741a                     je         0x4bc685
004bc66b  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004bc671  85c9                     test       ecx, ecx
004bc673  7410                     je         0x4bc685
004bc675  e8e6ac5600               call       0xa27360
004bc67a  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004bc680  e8                       .byte      0xe8

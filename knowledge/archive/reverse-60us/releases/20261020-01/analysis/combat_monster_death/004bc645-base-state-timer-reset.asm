004bc645 8a4510                   mov       al, byte ptr [ebp + 0x10]
004bc648 84c0                     test      al, al
004bc64a 7418                     je        0x4bc664
004bc64c 8dbe64150000             lea       edi, [esi + 0x1564]
004bc652 8bcf                     mov       ecx, edi
004bc654 e89788f4ff               call      0x404ef0
004bc659 6a00                     push      0
004bc65b 6a00                     push      0
004bc65d 8bcf                     mov       ecx, edi
004bc65f e8fca86400               call      0xb06f60

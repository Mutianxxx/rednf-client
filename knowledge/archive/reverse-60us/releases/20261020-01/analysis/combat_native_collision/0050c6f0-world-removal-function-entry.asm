0050c6f0 55                       push      ebp
0050c6f1 8bec                     mov       ebp, esp
0050c6f3 53                       push      ebx
0050c6f4 8b5d08                   mov       ebx, dword ptr [ebp + 8]
0050c6f7 56                       push      esi
0050c6f8 57                       push      edi
0050c6f9 33ff                     xor       edi, edi
0050c6fb 3bdf                     cmp       ebx, edi
0050c6fd 8bf1                     mov       esi, ecx
0050c6ff 0f848c020000             je        0x50c991
0050c705 57                       push      edi
0050c706 53                       push      ebx
0050c707 e874e5ffff               call      0x50ac80
0050c70c 8b03                     mov       eax, dword ptr [ebx]
0050c70e 6a12                     push      0x12
0050c710 8bcb                     mov       ecx, ebx
0050c712 ff502c                   call      dword ptr [eax + 0x2c]
0050c715 84c0                     test      al, al
0050c717 7421                     je        0x50c73a
0050c719 57                       push      edi
0050c71a 57                       push      edi
0050c71b 8bcb                     mov       ecx, ebx
0050c71d e8                       .byte     0xe8
0050c71e 2e                       .byte     0x2e
0050c71f 7e                       .byte     0x7e

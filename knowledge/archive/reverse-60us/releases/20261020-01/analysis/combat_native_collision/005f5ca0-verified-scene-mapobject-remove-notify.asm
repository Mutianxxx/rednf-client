005f5ca0 55                       push      ebp
005f5ca1 8bec                     mov       ebp, esp
005f5ca3 56                       push      esi
005f5ca4 8b7508                   mov       esi, dword ptr [ebp + 8]
005f5ca7 57                       push      edi
005f5ca8 56                       push      esi
005f5ca9 8bf9                     mov       edi, ecx
005f5cab e890abeaff               call      0x4a0840
005f5cb0 8b06                     mov       eax, dword ptr [esi]
005f5cb2 6a01                     push      1
005f5cb4 8bce                     mov       ecx, esi
005f5cb6 ff502c                   call      dword ptr [eax + 0x2c]
005f5cb9 84c0                     test      al, al
005f5cbb 7408                     je        0x5f5cc5
005f5cbd 56                       push      esi
005f5cbe 8bcf                     mov       ecx, edi
005f5cc0 e85bffffff               call      0x5f5c20
005f5cc5 5f                       pop       edi
005f5cc6 5e                       pop       esi
005f5cc7 5d                       pop       ebp
005f5cc8 c20400                   ret       4

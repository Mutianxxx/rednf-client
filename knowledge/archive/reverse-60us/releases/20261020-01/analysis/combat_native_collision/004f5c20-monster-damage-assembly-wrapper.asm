004f5c20 55                       push      ebp
004f5c21 8bec                     mov       ebp, esp
004f5c23 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004f5c26 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004f5c29 56                       push      esi
004f5c2a 57                       push      edi
004f5c2b 50                       push      eax
004f5c2c 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004f5c2f 8bf1                     mov       esi, ecx
004f5c31 8b4d18                   mov       ecx, dword ptr [ebp + 0x18]
004f5c34 51                       push      ecx
004f5c35 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f5c38 52                       push      edx
004f5c39 8b5508                   mov       edx, dword ptr [ebp + 8]
004f5c3c 50                       push      eax
004f5c3d 51                       push      ecx
004f5c3e 52                       push      edx
004f5c3f 8bce                     mov       ecx, esi
004f5c41 e83a5bffff               call      0x4eb780
004f5c46 8bf8                     mov       edi, eax
004f5c48 8a8608050000             mov       al, byte ptr [esi + 0x508]
004f5c4e 84c0                     test      al, al
004f5c50 745c                     je        0x4f5cae
004f5c52 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f5c58 84c0                     test      al, al
004f5c5a 7452                     je        0x4f5cae
004f5c5c 6a0d                     push      0xd
004f5c5e 8bce                     mov       ecx, esi
004f5c60 e80b2dffff               call      0x4e8970
004f5c65 84c0                     test      al, al
004f5c67 7417                     je        0x4f5c80
004f5c69 8b8e481a0000             mov       ecx, dword ptr [esi + 0x1a48]
004f5c6f 8b8604050000             mov       eax, dword ptr [esi + 0x504]
004f5c75 8d0481                   lea       eax, [ecx + eax*4]
004f5c78 8b08                     mov       ecx, dword ptr [eax]
004f5c7a 8b11                     mov       edx, dword ptr [ecx]
004f5c7c 57                       push      edi
004f5c7d ff5210                   call      dword ptr [edx + 0x10]
004f5c80 8a8600050000             mov       al, byte ptr [esi + 0x500]
004f5c86 84c0                     test      al, al
004f5c88 7424                     je        0x4f5cae
004f5c8a 6a00                     push      0
004f5c8c 8bce                     mov       ecx, esi
004f5c8e e8dd2cffff               call      0x4e8970
004f5c93 84c0                     test      al, al
004f5c95 7417                     je        0x4f5cae
004f5c97 8b8e381a0000             mov       ecx, dword ptr [esi + 0x1a38]
004f5c9d 8b8604050000             mov       eax, dword ptr [esi + 0x504]
004f5ca3 8d0481                   lea       eax, [ecx + eax*4]
004f5ca6 8b08                     mov       ecx, dword ptr [eax]
004f5ca8 8b11                     mov       edx, dword ptr [ecx]
004f5caa 57                       push      edi
004f5cab ff5210                   call      dword ptr [edx + 0x10]
004f5cae 8bc7                     mov       eax, edi
004f5cb0 5f                       pop       edi
004f5cb1 5e                       pop       esi
004f5cb2 5d                       pop       ebp
004f5cb3 c21800                   ret       0x18
004f5cb6 cc                       int3      

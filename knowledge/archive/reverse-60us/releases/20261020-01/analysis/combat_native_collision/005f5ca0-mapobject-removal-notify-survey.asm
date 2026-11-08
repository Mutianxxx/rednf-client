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
005f5ccb cc                       int3      
005f5ccc cc                       int3      
005f5ccd cc                       int3      
005f5cce cc                       int3      
005f5ccf cc                       int3      
005f5cd0 55                       push      ebp
005f5cd1 8bec                     mov       ebp, esp
005f5cd3 51                       push      ecx
005f5cd4 56                       push      esi
005f5cd5 8bf1                     mov       esi, ecx
005f5cd7 8b8620090000             mov       eax, dword ptr [esi + 0x920]
005f5cdd 85c0                     test      eax, eax
005f5cdf 7479                     je        0x5f5d5a
005f5ce1 8b8e24090000             mov       ecx, dword ptr [esi + 0x924]
005f5ce7 2bc8                     sub       ecx, eax
005f5ce9 b8abaaaa2a               mov       eax, 0x2aaaaaab
005f5cee f7e9                     imul      ecx
005f5cf0 d1fa                     sar       edx, 1
005f5cf2 8bc2                     mov       eax, edx
005f5cf4 c1e81f                   shr       eax, 0x1f
005f5cf7 03c2                     add       eax, edx
005f5cf9 8945fc                   mov       dword ptr [ebp - 4], eax
005f5cfc 745c                     je        0x5f5d5a
005f5cfe 8bce                     mov       ecx, esi
005f5d00 e88b63eaff               call      0x49c090
005f5d05 84c0                     test      al, al
005f5d07 7451                     je        0x5f5d5a
005f5d09 53                       push      ebx
005f5d0a 57                       push      edi
005f5d0b 33ff                     xor       edi, edi
005f5d0d 33db                     xor       ebx, ebx
005f5d0f 90                       nop       
005f5d10 8b8620090000             mov       eax, dword ptr [esi + 0x920]
005f5d16 85c0                     test      eax, eax
005f5d18 743e                     je        0x5f5d58
005f5d1a 8b8e24090000             mov       ecx, dword ptr [esi + 0x924]
005f5d20 2bc8                     sub       ecx, eax
005f5d22 b8abaaaa2a               mov       eax, 0x2aaaaaab
005f5d27 f7e9                     imul      ecx
005f5d29 d1fa                     sar       edx, 1
005f5d2b 8bc2                     mov       eax, edx
005f5d2d c1e81f                   shr       eax, 0x1f
005f5d30 03c2                     add       eax, edx
005f5d32 3bf8                     cmp       edi, eax
005f5d34 7322                     jae       0x5f5d58
005f5d36 8b8e20090000             mov       ecx, dword ptr [esi + 0x920]
005f5d3c 8b541908                 mov       edx, dword ptr [ecx + ebx + 8]
005f5d40 8d0419                   lea       eax, [ecx + ebx]
005f5d43 8b4804                   mov       ecx, dword ptr [eax + 4]
005f5d46 52                       push      edx
005f5d47 8b10                     mov       edx, dword ptr [eax]
005f5d49 51                       push      ecx
005f5d4a 52                       push      edx
005f5d4b 8bce                     mov       ecx, esi
005f5d4d e81ef7ffff               call      0x5f5470
005f5d52 47                       inc       edi
005f5d53 83c30c                   add       ebx, 0xc
005f5d56 ebb8                     jmp       0x5f5d10
005f5d58 5f                       pop       edi
005f5d59 5b                       pop       ebx
005f5d5a 5e                       pop       esi
005f5d5b 8be5                     mov       esp, ebp
005f5d5d 5d                       pop       ebp
005f5d5e c3                       ret       
005f5d5f cc                       int3      
005f5d60 56                       push      esi
005f5d61 8bf1                     mov       esi, ecx
005f5d63 8b8e30090000             mov       ecx, dword ptr [esi + 0x930]
005f5d69 85c9                     test      ecx, ecx
005f5d6b 7460                     je        0x5f5dcd
005f5d6d 8b8634090000             mov       eax, dword ptr [esi + 0x934]
005f5d73 2bc1                     sub       eax, ecx
005f5d75 c1f804                   sar       eax, 4
005f5d78 85c0                     test      eax, eax
005f5d7a 7651                     jbe       0x5f5dcd
005f5d7c 8bce                     mov       ecx, esi
005f5d7e e80d63eaff               call      0x49c090
005f5d83 84c0                     test      al, al
005f5d85 7446                     je        0x5f5dcd
005f5d87 53                       push      ebx
005f5d88 57                       push      edi
005f5d89 33ff                     xor       edi, edi
005f5d8b 33db                     xor       ebx, ebx
005f5d8d 8d4900                   lea       ecx, [ecx]
005f5d90 8b8e30090000             mov       ecx, dword ptr [esi + 0x930]
005f5d96 85c9                     test      ecx, ecx
005f5d98 7431                     je        0x5f5dcb
005f5d9a 8b8634090000             mov       eax, dword ptr [esi + 0x934]
005f5da0 2bc1                     sub       eax, ecx
005f5da2 c1f804                   sar       eax, 4
005f5da5 3bf8                     cmp       edi, eax
005f5da7 7322                     jae       0x5f5dcb
005f5da9 8bc1                     mov       eax, ecx
005f5dab 8b4c180c                 mov       ecx, dword ptr [eax + ebx + 0xc]
005f5daf 8b541808                 mov       edx, dword ptr [eax + ebx + 8]
005f5db3 03c3                     add       eax, ebx
005f5db5 51                       push      ecx
005f5db6 8b4804                   mov       ecx, dword ptr [eax + 4]
005f5db9 52                       push      edx
005f5dba 8b10                     mov       edx, dword ptr [eax]
005f5dbc 51                       push      ecx
005f5dbd 52                       push      edx
005f5dbe 8bce                     mov       ecx, esi
005f5dc0 e8fbf7ffff               call      0x5f55c0
005f5dc5 47                       inc       edi
005f5dc6 83c310                   add       ebx, 0x10
005f5dc9 ebc5                     jmp       0x5f5d90
005f5dcb 5f                       pop       edi
005f5dcc 5b                       pop       ebx
005f5dcd 5e                       pop       esi
005f5dce c3                       ret       
005f5dcf cc                       int3      
005f5dd0 55                       push      ebp
005f5dd1 8bec                     mov       ebp, esp
005f5dd3 56                       push      esi
005f5dd4 8b7508                   mov       esi, dword ptr [ebp + 8]
005f5dd7 57                       push      edi
005f5dd8 56                       push      esi
005f5dd9 8bf9                     mov       edi, ecx
005f5ddb e860aaeaff               call      0x4a0840
005f5de0 8b06                     mov       eax, dword ptr [esi]
005f5de2 6a01                     push      1
005f5de4 8bce                     mov       ecx, esi
005f5de6 ff502c                   call      dword ptr [eax + 0x2c]
005f5de9 84c0                     test      al, al
005f5deb 7408                     je        0x5f5df5
005f5ded 56                       push      esi
005f5dee 8bcf                     mov       ecx, edi
005f5df0 e82bfeffff               call      0x5f5c20
005f5df5 5f                       pop       edi
005f5df6 5e                       pop       esi
005f5df7 5d                       pop       ebp
005f5df8 c20400                   ret       4
005f5dfb cc                       int3      
005f5dfc cc                       int3      
005f5dfd cc                       int3      
005f5dfe cc                       int3      
005f5dff cc                       int3      
005f5e00 55                       push      ebp
005f5e01 8bec                     mov       ebp, esp
005f5e03 56                       push      esi
005f5e04 8b7508                   mov       esi, dword ptr [ebp + 8]
005f5e07 57                       push      edi
005f5e08 56                       push      esi
005f5e09 8bf9                     mov       edi, ecx
005f5e0b e830aaeaff               call      0x4a0840
005f5e10 8b06                     mov       eax, dword ptr [esi]
005f5e12 6a01                     push      1
005f5e14 8bce                     mov       ecx, esi
005f5e16 ff502c                   call      dword ptr [eax + 0x2c]
005f5e19 84c0                     test      al, al
005f5e1b 7408                     je        0x5f5e25
005f5e1d 56                       push      esi
005f5e1e 8bcf                     mov       ecx, edi
005f5e20 e8fbfdffff               call      0x5f5c20
005f5e25 3bb790090000             cmp       esi, dword ptr [edi + 0x990]
005f5e2b 750a                     jne       0x5f5e37
005f5e2d c7879009000000000000     mov       dword ptr [edi + 0x990], 0
005f5e37 5f                       pop       edi
005f5e38 5e                       pop       esi
005f5e39 5d                       pop       ebp
005f5e3a c20400                   ret       4
005f5e3d cc                       int3      
005f5e3e cc                       int3      
005f5e3f cc                       int3      
005f5e40 55                       push      ebp
005f5e41 8bec                     mov       ebp, esp
005f5e43 56                       push      esi
005f5e44 57                       push      edi
005f5e45 8b7d08                   mov       edi, dword ptr [ebp + 8]
005f5e48 8bf1                     mov       esi, ecx
005f5e4a 3bfe                     cmp       edi, esi
005f5e4c 7508                     jne       0x5f5e56
005f5e4e 8b06                     mov       eax, dword ptr [esi]
005f5e50 ff9094030000             call      dword ptr [eax + 0x394]
005f5e56 57                       push      edi
005f5e57 8bce                     mov       ecx, esi
005f5e59 e8e2a9eaff               call      0x4a0840
005f5e5e 8b17                     mov       edx, dword ptr [edi]
005f5e60 6a01                     push      1
005f5e62 8bcf                     mov       ecx, edi
005f5e64 ff522c                   call      dword ptr [edx + 0x2c]
005f5e67 84c0                     test      al, al
005f5e69 7408                     je        0x5f5e73
005f5e6b 57                       push      edi
005f5e6c 8bce                     mov       ecx, esi
005f5e6e e8adfdffff               call      0x5f5c20
005f5e73 5f                       pop       edi
005f5e74 5e                       pop       esi
005f5e75 5d                       pop       ebp
005f5e76 c20400                   ret       4
005f5e79 cc                       int3      
005f5e7a cc                       int3      
005f5e7b cc                       int3      
005f5e7c cc                       int3      
005f5e7d cc                       int3      
005f5e7e cc                       int3      
005f5e7f cc                       int3      

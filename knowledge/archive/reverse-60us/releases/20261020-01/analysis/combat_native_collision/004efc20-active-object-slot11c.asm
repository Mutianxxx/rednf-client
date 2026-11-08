004efc20 55                       push      ebp
004efc21 8bec                     mov       ebp, esp
004efc23 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004efc26 53                       push      ebx
004efc27 56                       push      esi
004efc28 8b7508                   mov       esi, dword ptr [ebp + 8]
004efc2b 57                       push      edi
004efc2c 8bf9                     mov       edi, ecx
004efc2e 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efc31 8b9fb0010000             mov       ebx, dword ptr [edi + 0x1b0]
004efc37 50                       push      eax
004efc38 51                       push      ecx
004efc39 56                       push      esi
004efc3a 8bcf                     mov       ecx, edi
004efc3c e82fb7faff               call      0x49b370
004efc41 3bde                     cmp       ebx, esi
004efc43 742c                     je        0x4efc71
004efc45 83fb01                   cmp       ebx, 1
004efc48 7d17                     jge       0x4efc61
004efc4a 83fe01                   cmp       esi, 1
004efc4d 7c22                     jl        0x4efc71
004efc4f 8d8f741d0000             lea       ecx, [edi + 0x1d74]
004efc55 e886736100               call      0xb06fe0
004efc5a 5f                       pop       edi
004efc5b 5e                       pop       esi
004efc5c 5b                       pop       ebx
004efc5d 5d                       pop       ebp
004efc5e c20c00                   ret       0xc
004efc61 83fe01                   cmp       esi, 1
004efc64 7d0b                     jge       0x4efc71
004efc66 8d8f741d0000             lea       ecx, [edi + 0x1d74]
004efc6c e80f746100               call      0xb07080
004efc71 5f                       pop       edi
004efc72 5e                       pop       esi
004efc73 5b                       pop       ebx
004efc74 5d                       pop       ebp
004efc75 c20c00                   ret       0xc
004efc78 cc                       int3      
004efc79 cc                       int3      
004efc7a cc                       int3      
004efc7b cc                       int3      
004efc7c cc                       int3      
004efc7d cc                       int3      
004efc7e cc                       int3      
004efc7f cc                       int3      

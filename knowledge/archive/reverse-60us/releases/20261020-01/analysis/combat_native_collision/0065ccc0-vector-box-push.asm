0065ccc0 55                       push      ebp
0065ccc1 8bec                     mov       ebp, esp
0065ccc3 56                       push      esi
0065ccc4 8bf1                     mov       esi, ecx
0065ccc6 57                       push      edi
0065ccc7 8b7e04                   mov       edi, dword ptr [esi + 4]
0065ccca 85ff                     test      edi, edi
0065cccc 7504                     jne       0x65ccd2
0065ccce 33c9                     xor       ecx, ecx
0065ccd0 eb16                     jmp       0x65cce8
0065ccd2 8b4e08                   mov       ecx, dword ptr [esi + 8]
0065ccd5 2bcf                     sub       ecx, edi
0065ccd7 b8abaaaa2a               mov       eax, 0x2aaaaaab
0065ccdc f7e9                     imul      ecx
0065ccde c1fa03                   sar       edx, 3
0065cce1 8bca                     mov       ecx, edx
0065cce3 c1e91f                   shr       ecx, 0x1f
0065cce6 03ca                     add       ecx, edx
0065cce8 85ff                     test      edi, edi
0065ccea 743d                     je        0x65cd29
0065ccec 8b560c                   mov       edx, dword ptr [esi + 0xc]
0065ccef 2bd7                     sub       edx, edi
0065ccf1 b8abaaaa2a               mov       eax, 0x2aaaaaab
0065ccf6 f7ea                     imul      edx
0065ccf8 c1fa03                   sar       edx, 3
0065ccfb 8bc2                     mov       eax, edx
0065ccfd c1e81f                   shr       eax, 0x1f
0065cd00 03c2                     add       eax, edx
0065cd02 3bc8                     cmp       ecx, eax
0065cd04 7323                     jae       0x65cd29
0065cd06 8b4508                   mov       eax, dword ptr [ebp + 8]
0065cd09 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0065cd0c 8b7e08                   mov       edi, dword ptr [esi + 8]
0065cd0f 50                       push      eax
0065cd10 56                       push      esi
0065cd11 51                       push      ecx
0065cd12 6a01                     push      1
0065cd14 57                       push      edi
0065cd15 e876fbffff               call      0x65c890
0065cd1a 83c414                   add       esp, 0x14
0065cd1d 83c730                   add       edi, 0x30
0065cd20 897e08                   mov       dword ptr [esi + 8], edi
0065cd23 5f                       pop       edi
0065cd24 5e                       pop       esi
0065cd25 5d                       pop       ebp
0065cd26 c20400                   ret       4
0065cd29 8b5508                   mov       edx, dword ptr [ebp + 8]
0065cd2c 8b4608                   mov       eax, dword ptr [esi + 8]
0065cd2f 52                       push      edx
0065cd30 50                       push      eax
0065cd31 8d4508                   lea       eax, [ebp + 8]
0065cd34 50                       push      eax
0065cd35 8bce                     mov       ecx, esi
0065cd37 e814ffffff               call      0x65cc50
0065cd3c 5f                       pop       edi
0065cd3d 5e                       pop       esi
0065cd3e 5d                       pop       ebp
0065cd3f c20400                   ret       4
0065cd42 cc                       int3      
0065cd43 cc                       int3      
0065cd44 cc                       int3      
0065cd45 cc                       int3      
0065cd46 cc                       int3      
0065cd47 cc                       int3      
0065cd48 cc                       int3      
0065cd49 cc                       int3      
0065cd4a cc                       int3      
0065cd4b cc                       int3      
0065cd4c cc                       int3      
0065cd4d cc                       int3      
0065cd4e cc                       int3      
0065cd4f cc                       int3      
0065cd50 55                       push      ebp
0065cd51 8bec                     mov       ebp, esp
0065cd53 6aff                     push      -1
0065cd55 6898a5c600               push      0xc6a598
0065cd5a 64a100000000             mov       eax, dword ptr fs:[0]
0065cd60 50                       push      eax
0065cd61 64892500000000           mov       dword ptr fs:[0], esp
0065cd68 51                       push      ecx
0065cd69 56                       push      esi
0065cd6a 6a01                     push      1
0065cd6c 68fa000000               push      0xfa
0065cd71 6a11                     push      0x11
0065cd73 8bf1                     mov       esi, ecx
0065cd75 6a00                     push      0
0065cd77 8975f0                   mov       dword ptr [ebp - 0x10], esi
0065cd7a e8d123f6ff               call      0x5bf150
0065cd7f 8bce                     mov       ecx, esi
0065cd81 c745fc00000000           mov       dword ptr [ebp - 4], 0
0065cd88 c70694bfd500             mov       dword ptr [esi], 0xd5bf94
0065cd8e c7467c68bfd500           mov       dword ptr [esi + 0x7c], 0xd5bf68
0065cd95 e8e6edf2ff               call      0x58bb80
0065cd9a 8bce                     mov       ecx, esi
0065cd9c e82feef2ff               call      0x58bbd0
0065cda1 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0065cda4 8bc6                     mov       eax, esi
0065cda6 5e                       pop       esi
0065cda7 64890d00000000           mov       dword ptr fs:[0], ecx
0065cdae 8be5                     mov       esp, ebp
0065cdb0 5d                       pop       ebp
0065cdb1 c3                       ret       
0065cdb2 cc                       int3      
0065cdb3 cc                       int3      
0065cdb4 cc                       int3      
0065cdb5 cc                       int3      
0065cdb6 cc                       int3      
0065cdb7 cc                       int3      
0065cdb8 cc                       int3      
0065cdb9 cc                       int3      
0065cdba cc                       int3      
0065cdbb cc                       int3      
0065cdbc cc                       int3      
0065cdbd cc                       int3      
0065cdbe cc                       int3      
0065cdbf cc                       int3      
0065cdc0 55                       push      ebp
0065cdc1 8bec                     mov       ebp, esp
0065cdc3 6aff                     push      -1
0065cdc5 6898a7c600               push      0xc6a798
0065cdca 64a100000000             mov       eax, dword ptr fs:[0]
0065cdd0 50                       push      eax
0065cdd1 64892500000000           mov       dword ptr fs:[0], esp
0065cdd8 51                       push      ecx
0065cdd9 56                       push      esi
0065cdda 8bf1                     mov       esi, ecx
0065cddc 8975f0                   mov       dword ptr [ebp - 0x10], esi
0065cddf e86cffffff               call      0x65cd50
0065cde4 8bce                     mov       ecx, esi
0065cde6 c745fc00000000           mov       dword ptr [ebp - 4], 0
0065cded c706dcc0d500             mov       dword ptr [esi], 0xd5c0dc
0065cdf3 c7467cb0c0d500           mov       dword ptr [esi + 0x7c], 0xd5c0b0
0065cdfa e8d181f5ff               call      0x5b4fd0
0065cdff 8bce                     mov       ecx, esi
0065ce01 e80a83f5ff               call      0x5b5110
0065ce06 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0065ce09 8bc6                     mov       eax, esi
0065ce0b 5e                       pop       esi
0065ce0c 64890d00000000           mov       dword ptr fs:[0], ecx
0065ce13 8be5                     mov       esp, ebp
0065ce15 5d                       pop       ebp
0065ce16 c3                       ret       
0065ce17 cc                       int3      
0065ce18 cc                       int3      
0065ce19 cc                       int3      
0065ce1a cc                       int3      
0065ce1b cc                       int3      
0065ce1c cc                       int3      
0065ce1d cc                       int3      
0065ce1e cc                       int3      
0065ce1f cc                       int3      

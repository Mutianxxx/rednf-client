004aef30 008d04828b15             add       byte ptr [ebp + 0x158b8204], cl
004aef36 dc01                     fadd      qword ptr [ecx]
004aef38 2101                     and       dword ptr [ecx], eax
004aef3a 8bc8                     mov       ecx, eax
004aef3c 33ca                     xor       ecx, edx
004aef3e 8908                     mov       dword ptr [eax], ecx
004aef40 a1d8012101               mov       eax, dword ptr [0x12101d8]
004aef45 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004aef48 8b9610190000             mov       edx, dword ptr [esi + 0x1910]
004aef4e 8d0491                   lea       eax, [ecx + edx*4]
004aef51 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004aef57 8bd0                     mov       edx, eax
004aef59 33d1                     xor       edx, ecx
004aef5b 8910                     mov       dword ptr [eax], edx
004aef5d 8b06                     mov       eax, dword ptr [esi]
004aef5f 8bce                     mov       ecx, esi
004aef61 899ef0040000             mov       dword ptr [esi + 0x4f0], ebx
004aef67 ff9098050000             call      dword ptr [eax + 0x598]
004aef6d 5f                       pop       edi
004aef6e 5e                       pop       esi
004aef6f 5b                       pop       ebx
004aef70 8be5                     mov       esp, ebp
004aef72 5d                       pop       ebp
004aef73 c3                       ret       
004aef74 cc                       int3      
004aef75 cc                       int3      
004aef76 cc                       int3      
004aef77 cc                       int3      
004aef78 cc                       int3      
004aef79 cc                       int3      
004aef7a cc                       int3      
004aef7b cc                       int3      
004aef7c cc                       int3      
004aef7d cc                       int3      
004aef7e cc                       int3      
004aef7f cc                       int3      
004aef80 55                       push      ebp
004aef81 8bec                     mov       ebp, esp
004aef83 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004aef86 53                       push      ebx
004aef87 56                       push      esi
004aef88 8b7508                   mov       esi, dword ptr [ebp + 8]
004aef8b 8b16                     mov       edx, dword ptr [esi]
004aef8d 8bd9                     mov       ebx, ecx
004aef8f 50                       push      eax
004aef90 8bce                     mov       ecx, esi
004aef92 ff92f4000000             call      dword ptr [edx + 0xf4]
004aef98 50                       push      eax
004aef99 8b03                     mov       eax, dword ptr [ebx]
004aef9b 56                       push      esi
004aef9c 8bcb                     mov       ecx, ebx
004aef9e ff90f4000000             call      dword ptr [eax + 0xf4]
004aefa4 50                       push      eax
004aefa5 53                       push      ebx
004aefa6 e865ab0300               call      0x4e9b10
004aefab 83c414                   add       esp, 0x14
004aefae 84c0                     test      al, al
004aefb0 7408                     je        0x4aefba
004aefb2 5e                       pop       esi
004aefb3 b001                     mov       al, 1
004aefb5 5b                       pop       ebx
004aefb6 5d                       pop       ebp
004aefb7 c20800                   ret       8
004aefba 8b8304010000             mov       eax, dword ptr [ebx + 0x104]
004aefc0 85c0                     test      eax, eax
004aefc2 57                       push      edi
004aefc3 894508                   mov       dword ptr [ebp + 8], eax
004aefc6 743a                     je        0x4af002
004aefc8 8b8080010000             mov       eax, dword ptr [eax + 0x180]
004aefce 8b38                     mov       edi, dword ptr [eax]
004aefd0 3bf8                     cmp       edi, eax
004aefd2 742e                     je        0x4af002
004aefd4 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004aefd7 8b16                     mov       edx, dword ptr [esi]
004aefd9 51                       push      ecx
004aefda 8bce                     mov       ecx, esi
004aefdc ff92f4000000             call      dword ptr [edx + 0xf4]
004aefe2 50                       push      eax
004aefe3 8b470c                   mov       eax, dword ptr [edi + 0xc]
004aefe6 56                       push      esi
004aefe7 50                       push      eax
004aefe8 53                       push      ebx
004aefe9 e822ab0300               call      0x4e9b10
004aefee 83c414                   add       esp, 0x14
004aeff1 84c0                     test      al, al
004aeff3 7516                     jne       0x4af00b
004aeff5 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004aeff8 8b3f                     mov       edi, dword ptr [edi]
004aeffa 3bb980010000             cmp       edi, dword ptr [ecx + 0x180]
004af000 75d2                     jne       0x4aefd4
004af002 5f                       pop       edi
004af003 5e                       pop       esi
004af004 32c0                     xor       al, al
004af006 5b                       pop       ebx
004af007 5d                       pop       ebp
004af008 c20800                   ret       8
004af00b 5f                       pop       edi
004af00c 5e                       pop       esi
004af00d b001                     mov       al, 1
004af00f 5b                       pop       ebx
004af010 5d                       pop       ebp
004af011 c20800                   ret       8
004af014 cc                       int3      
004af015 cc                       int3      
004af016 cc                       int3      
004af017 cc                       int3      
004af018 cc                       int3      
004af019 cc                       int3      
004af01a cc                       int3      
004af01b cc                       int3      
004af01c cc                       int3      
004af01d cc                       int3      
004af01e cc                       int3      
004af01f cc                       int3      
004af020 55                       push      ebp
004af021 8bec                     mov       ebp, esp
004af023 8b4508                   mov       eax, dword ptr [ebp + 8]
004af026 85c0                     test      eax, eax
004af028 56                       push      esi
004af029 8bf1                     mov       esi, ecx
004af02b 0f                       .byte     0x0f
004af02c 850a                     test      dword ptr [edx], ecx
004af02e 0100                     add       dword ptr [eax], eax

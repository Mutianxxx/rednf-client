004ece50 55                       push      ebp
004ece51 8bec                     mov       ebp, esp
004ece53 51                       push      ecx
004ece54 56                       push      esi
004ece55 57                       push      edi
004ece56 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ece59 85ff                     test      edi, edi
004ece5b 8bf1                     mov       esi, ecx
004ece5d 750a                     jne       0x4ece69
004ece5f 5f                       pop       edi
004ece60 32c0                     xor       al, al
004ece62 5e                       pop       esi
004ece63 8be5                     mov       esp, ebp
004ece65 5d                       pop       ebp
004ece66 c20400                   ret       4
004ece69 8b06                     mov       eax, dword ptr [esi]
004ece6b 8bce                     mov       ecx, esi
004ece6d ff90c8010000             call      dword ptr [eax + 0x1c8]
004ece73 3bc6                     cmp       eax, esi
004ece75 741d                     je        0x4ece94
004ece77 8b16                     mov       edx, dword ptr [esi]
004ece79 8bce                     mov       ecx, esi
004ece7b ff92c8010000             call      dword ptr [edx + 0x1c8]
004ece81 8b10                     mov       edx, dword ptr [eax]
004ece83 57                       push      edi
004ece84 8bc8                     mov       ecx, eax
004ece86 ff92a8010000             call      dword ptr [edx + 0x1a8]
004ece8c 5f                       pop       edi
004ece8d 5e                       pop       esi
004ece8e 8be5                     mov       esp, ebp
004ece90 5d                       pop       ebp
004ece91 c20400                   ret       4
004ece94 8b07                     mov       eax, dword ptr [edi]
004ece96 8bcf                     mov       ecx, edi
004ece98 ff90c8010000             call      dword ptr [eax + 0x1c8]
004ece9e 8d4d08                   lea       ecx, [ebp + 8]
004ecea1 51                       push      ecx
004ecea2 8d55fc                   lea       edx, [ebp - 4]
004ecea5 52                       push      edx
004ecea6 8d8e18040000             lea       ecx, [esi + 0x418]
004eceac 894508                   mov       dword ptr [ebp + 8], eax
004eceaf e82c7e5700               call      0xa64ce0
004eceb4 8b9620040000             mov       edx, dword ptr [esi + 0x420]
004eceba 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004ecebd 33c0                     xor       eax, eax
004ecebf 3bca                     cmp       ecx, edx
004ecec1 5f                       pop       edi
004ecec2 0f95c0                   setne     al
004ecec5 5e                       pop       esi
004ecec6 8be5                     mov       esp, ebp
004ecec8 5d                       pop       ebp
004ecec9 c20400                   ret       4
004ececc cc                       int3      
004ececd cc                       int3      
004ecece cc                       int3      
004ececf cc                       int3      
004eced0 55                       push      ebp
004eced1 8bec                     mov       ebp, esp
004eced3 51                       push      ecx
004eced4 53                       push      ebx
004eced5 56                       push      esi
004eced6 57                       push      edi
004eced7 8bf1                     mov       esi, ecx
004eced9 bb01000000               mov       ebx, 1
004ecede 68e0baca00               push      0xcabae0
004ecee3 899ee4000000             mov       dword ptr [esi + 0xe4], ebx
004ecee9 e8df2e7100               call      0xbffdcd
004eceee 83c404                   add       esp, 4
004ecef1 50                       push      eax
004ecef2 68e0baca00               push      0xcabae0
004ecef7 8d8e44020000             lea       ecx, [esi + 0x244]
004ecefd e87e5ff1ff               call      0x402e80
004ecf02 899e5c040000             mov       dword ptr [esi + 0x45c], ebx
004ecf08 33c0                     xor       eax, eax
004ecf0a 888640040000             mov       byte ptr [esi + 0x440], al
004ecf10 898658040000             mov       dword ptr [esi + 0x458], eax
004ecf16 83c9ff                   or        ecx, 0xffffffff
004ecf19 898e54040000             mov       dword ptr [esi + 0x454], ecx
004ecf1f 898e68040000             mov       dword ptr [esi + 0x468], ecx
004ecf25 898e6c040000             mov       dword ptr [esi + 0x46c], ecx
004ecf2b 898660040000             mov       dword ptr [esi + 0x460], eax
004ecf31 898664040000             mov       dword ptr [esi + 0x464], eax
004ecf37 898ea0040000             mov       dword ptr [esi + 0x4a0], ecx
004ecf3d 898698040000             mov       dword ptr [esi + 0x498], eax
004ecf43 8986b4040000             mov       dword ptr [esi + 0x4b4], eax
004ecf49 889e9c040000             mov       byte ptr [esi + 0x49c], bl
004ecf4f 88                       .byte     0x88

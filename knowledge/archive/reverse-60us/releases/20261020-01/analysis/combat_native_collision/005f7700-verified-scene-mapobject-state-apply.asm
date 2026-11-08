005f7700 55                       push      ebp
005f7701 8bec                     mov       ebp, esp
005f7703 8b4514                   mov       eax, dword ptr [ebp + 0x14]
005f7706 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f7709 56                       push      esi
005f770a 57                       push      edi
005f770b 8b7d08                   mov       edi, dword ptr [ebp + 8]
005f770e 8bf1                     mov       esi, ecx
005f7710 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005f7713 50                       push      eax
005f7714 51                       push      ecx
005f7715 52                       push      edx
005f7716 57                       push      edi
005f7717 8bce                     mov       ecx, esi
005f7719 e8b260eaff               call      0x49d7d0
005f771e 8bc7                     mov       eax, edi
005f7720 83e802                   sub       eax, 2
005f7723 7519                     jne       0x5f773e
005f7725 8bce                     mov       ecx, esi
005f7727 e8e4f6ffff               call      0x5f6e10
005f772c 8b06                     mov       eax, dword ptr [esi]
005f772e 6a01                     push      1
005f7730 6a01                     push      1
005f7732 6a00                     push      0
005f7734 6a00                     push      0
005f7736 8bce                     mov       ecx, esi
005f7738 ff902c020000             call      dword ptr [eax + 0x22c]
005f773e 5f                       pop       edi
005f773f 5e                       pop       esi
005f7740 5d                       pop       ebp
005f7741 c21000                   ret       0x10

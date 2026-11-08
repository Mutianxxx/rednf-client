004afc60 55                       push      ebp
004afc61 8bec                     mov       ebp, esp
004afc63 56                       push      esi
004afc64 8bf1                     mov       esi, ecx
004afc66 e825c4feff               call      0x49c090
004afc6b 84c0                     test      al, al
004afc6d 0f8410010000             je        0x4afd83
004afc73 8b06                     mov       eax, dword ptr [esi]
004afc75 8bce                     mov       ecx, esi
004afc77 ff90dc030000             call      dword ptr [eax + 0x3dc]
004afc7d 84c0                     test      al, al
004afc7f 0f85fe000000             jne       0x4afd83
004afc85 57                       push      edi
004afc86 8bce                     mov       ecx, esi
004afc88 e8e36d0000               call      0x4b6a70
004afc8d 84c0                     test      al, al
004afc8f 8b7d08                   mov       edi, dword ptr [ebp + 8]
004afc92 7412                     je        0x4afca6
004afc94 8b16                     mov       edx, dword ptr [esi]
004afc96 8bce                     mov       ecx, esi
004afc98 ff92f8030000             call      dword ptr [edx + 0x3f8]
004afc9e 3bf8                     cmp       edi, eax
004afca0 0f8cdc000000             jl        0x4afd82
004afca6 8b16                     mov       edx, dword ptr [esi]
004afca8 33c0                     xor       eax, eax
004afcaa 85ff                     test      edi, edi
004afcac 0f9cc0                   setl      al
004afcaf 8bce                     mov       ecx, esi
004afcb1 48                       dec       eax
004afcb2 23f8                     and       edi, eax
004afcb4 ff92fc030000             call      dword ptr [edx + 0x3fc]
004afcba 3bc7                     cmp       eax, edi
004afcbc 7d0c                     jge       0x4afcca
004afcbe 8b06                     mov       eax, dword ptr [esi]
004afcc0 8bce                     mov       ecx, esi
004afcc2 ff90fc030000             call      dword ptr [eax + 0x3fc]
004afcc8 8bf8                     mov       edi, eax
004afcca 8a450c                   mov       al, byte ptr [ebp + 0xc]
004afccd 84c0                     test      al, al
004afccf 53                       push      ebx
004afcd0 746c                     je        0x4afd3e
004afcd2 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004afcd8 8b11                     mov       edx, dword ptr [ecx]
004afcda 6a01                     push      1
004afcdc 6a0d                     push      0xd
004afcde ff5208                   call      dword ptr [edx + 8]
004afce1 a164310001               mov       eax, dword ptr [0x1003164]
004afce6 8b16                     mov       edx, dword ptr [esi]
004afce8 8b18                     mov       ebx, dword ptr [eax]
004afcea 8bce                     mov       ecx, esi
004afcec ff523c                   call      dword ptr [edx + 0x3c]
004afcef 8b                       .byte     0x8b

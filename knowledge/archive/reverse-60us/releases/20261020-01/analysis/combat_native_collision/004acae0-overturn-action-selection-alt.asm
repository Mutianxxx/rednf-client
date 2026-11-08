004acae0 55                       push      ebp
004acae1 8bec                     mov       ebp, esp
004acae3 53                       push      ebx
004acae4 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
004acae7 56                       push      esi
004acae8 57                       push      edi
004acae9 8b7d08                   mov       edi, dword ptr [ebp + 8]
004acaec 85ff                     test      edi, edi
004acaee 8bf1                     mov       esi, ecx
004acaf0 752c                     jne       0x4acb1e
004acaf2 8b06                     mov       eax, dword ptr [esi]
004acaf4 ff9090030000             call      dword ptr [eax + 0x390]
004acafa 85c0                     test      eax, eax
004acafc 0f841a020000             je        0x4acd1c
004acb02 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acb05 8b16                     mov       edx, dword ptr [esi]
004acb07 51                       push      ecx
004acb08 8bce                     mov       ecx, esi
004acb0a ff9290030000             call      dword ptr [edx + 0x390]
004acb10 8bc8                     mov       ecx, eax
004acb12 e8c9185800               call      0xa2e3e0
004acb17 5f                       pop       edi
004acb18 5e                       pop       esi
004acb19 5b                       pop       ebx
004acb1a 5d                       pop       ebp
004acb1b c20c00                   ret       0xc
004acb1e 83ff01                   cmp       edi, 1
004acb21 752e                     jne       0x4acb51
004acb23 8b06                     mov       eax, dword ptr [esi]
004acb25 8bce                     mov       ecx, esi
004acb27 ff9094030000             call      dword ptr [eax + 0x394]
004acb2d 85c0                     test      eax, eax
004acb2f 0f84e7010000             je        0x4acd1c
004acb35 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acb38 8b16                     mov       edx, dword ptr [esi]
004acb3a 51                       push      ecx
004acb3b 8bce                     mov       ecx, esi
004acb3d ff9294030000             call      dword ptr [edx + 0x394]
004acb43 8bc8                     mov       ecx, eax
004acb45 e896185800               call      0xa2e3e0
004acb4a 5f                       pop       edi
004acb4b 5e                       pop       esi
004acb4c 5b                       pop       ebx
004acb4d 5d                       pop       ebp
004acb4e c20c00                   ret       0xc
004acb51 83ff02                   cmp       edi, 2
004acb54 752e                     jne       0x4acb84
004acb56 8b06                     mov       eax, dword ptr [esi]
004acb58 8bce                     mov       ecx, esi
004acb5a ff9098030000             call      dword ptr [eax + 0x398]
004acb60 85c0                     test      eax, eax
004acb62 0f84b4010000             je        0x4acd1c
004acb68 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acb6b 8b16                     mov       edx, dword ptr [esi]
004acb6d 51                       push      ecx
004acb6e 8bce                     mov       ecx, esi
004acb70 ff9298030000             call      dword ptr [edx + 0x398]
004acb76 8bc8                     mov       ecx, eax
004acb78 e863185800               call      0xa2e3e0
004acb7d 5f                       pop       edi
004acb7e 5e                       pop       esi
004acb7f 5b                       pop       ebx
004acb80 5d                       pop       ebp
004acb81 c20c00                   ret       0xc
004acb84 83ff03                   cmp       edi, 3
004acb87 7532                     jne       0x4acbbb
004acb89 8b06                     mov       eax, dword ptr [esi]
004acb8b 6a00                     push      0
004acb8d 8bce                     mov       ecx, esi
004acb8f ff909c030000             call      dword ptr [eax + 0x39c]
004acb95 85c0                     test      eax, eax
004acb97 0f847f010000             je        0x4acd1c
004acb9d 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acba0 8b16                     mov       edx, dword ptr [esi]
004acba2 51                       push      ecx
004acba3 6a00                     push      0
004acba5 8bce                     mov       ecx, esi
004acba7 ff929c030000             call      dword ptr [edx + 0x39c]
004acbad 8bc8                     mov       ecx, eax
004acbaf e82c185800               call      0xa2e3e0
004acbb4 5f                       pop       edi
004acbb5 5e                       pop       esi
004acbb6 5b                       pop       ebx
004acbb7 5d                       pop       ebp
004acbb8 c20c00                   ret       0xc
004acbbb 83ff04                   cmp       edi, 4
004acbbe 7532                     jne       0x4acbf2
004acbc0 8b06                     mov       eax, dword ptr [esi]
004acbc2 6a01                     push      1
004acbc4 8bce                     mov       ecx, esi
004acbc6 ff909c030000             call      dword ptr [eax + 0x39c]
004acbcc 85c0                     test      eax, eax
004acbce 0f8448010000             je        0x4acd1c
004acbd4 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acbd7 8b16                     mov       edx, dword ptr [esi]
004acbd9 51                       push      ecx
004acbda 6a01                     push      1
004acbdc 8bce                     mov       ecx, esi
004acbde ff929c030000             call      dword ptr [edx + 0x39c]
004acbe4 8bc8                     mov       ecx, eax
004acbe6 e8f5175800               call      0xa2e3e0
004acbeb 5f                       pop       edi
004acbec 5e                       pop       esi
004acbed 5b                       pop       ebx
004acbee 5d                       pop       ebp
004acbef c20c00                   ret       0xc
004acbf2 83ff05                   cmp       edi, 5
004acbf5 752e                     jne       0x4acc25
004acbf7 8b06                     mov       eax, dword ptr [esi]
004acbf9 8bce                     mov       ecx, esi
004acbfb ff90a0030000             call      dword ptr [eax + 0x3a0]
004acc01 85c0                     test      eax, eax
004acc03 0f8413010000             je        0x4acd1c
004acc09 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acc0c 8b16                     mov       edx, dword ptr [esi]
004acc0e 51                       push      ecx
004acc0f 8bce                     mov       ecx, esi
004acc11 ff92a0030000             call      dword ptr [edx + 0x3a0]
004acc17 8bc8                     mov       ecx, eax
004acc19 e8c2175800               call      0xa2e3e0
004acc1e 5f                       pop       edi
004acc1f 5e                       pop       esi
004acc20 5b                       pop       ebx
004acc21 5d                       pop       ebp
004acc22 c20c00                   ret       0xc
004acc25 83ff06                   cmp       edi, 6
004acc28 752e                     jne       0x4acc58
004acc2a 8b06                     mov       eax, dword ptr [esi]
004acc2c 8bce                     mov       ecx, esi
004acc2e ff90a4030000             call      dword ptr [eax + 0x3a4]
004acc34 85c0                     test      eax, eax
004acc36 0f84e0000000             je        0x4acd1c
004acc3c 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acc3f 8b16                     mov       edx, dword ptr [esi]
004acc41 51                       push      ecx
004acc42 8bce                     mov       ecx, esi
004acc44 ff92a4030000             call      dword ptr [edx + 0x3a4]
004acc4a 8bc8                     mov       ecx, eax
004acc4c e88f175800               call      0xa2e3e0
004acc51 5f                       pop       edi
004acc52 5e                       pop       esi
004acc53 5b                       pop       ebx
004acc54 5d                       pop       ebp
004acc55 c20c00                   ret       0xc
004acc58 83ff07                   cmp       edi, 7
004acc5b 752e                     jne       0x4acc8b
004acc5d 8b06                     mov       eax, dword ptr [esi]
004acc5f 8bce                     mov       ecx, esi
004acc61 ff90a8030000             call      dword ptr [eax + 0x3a8]
004acc67 85c0                     test      eax, eax
004acc69 0f84ad000000             je        0x4acd1c
004acc6f 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acc72 8b16                     mov       edx, dword ptr [esi]
004acc74 51                       push      ecx
004acc75 8bce                     mov       ecx, esi
004acc77 ff92a8030000             call      dword ptr [edx + 0x3a8]
004acc7d 8bc8                     mov       ecx, eax
004acc7f e85c175800               call      0xa2e3e0
004acc84 5f                       pop       edi
004acc85 5e                       pop       esi
004acc86 5b                       pop       ebx
004acc87 5d                       pop       ebp
004acc88 c20c00                   ret       0xc
004acc8b 83ff08                   cmp       edi, 8
004acc8e 752a                     jne       0x4accba
004acc90 8b06                     mov       eax, dword ptr [esi]
004acc92 8bce                     mov       ecx, esi
004acc94 ff90ac030000             call      dword ptr [eax + 0x3ac]
004acc9a 85c0                     test      eax, eax
004acc9c 747e                     je        0x4acd1c
004acc9e 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004acca1 8b16                     mov       edx, dword ptr [esi]
004acca3 51                       push      ecx
004acca4 8bce                     mov       ecx, esi
004acca6 ff92ac030000             call      dword ptr [edx + 0x3ac]
004accac 8bc8                     mov       ecx, eax
004accae e82d175800               call      0xa2e3e0
004accb3 5f                       pop       edi
004accb4 5e                       pop       esi
004accb5 5b                       pop       ebx
004accb6 5d                       pop       ebp
004accb7 c20c00                   ret       0xc
004accba 83ff09                   cmp       edi, 9
004accbd 752c                     jne       0x4acceb
004accbf 8b06                     mov       eax, dword ptr [esi]
004accc1 53                       push      ebx
004accc2 8bce                     mov       ecx, esi
004accc4 ff90b0030000             call      dword ptr [eax + 0x3b0]
004accca 85c0                     test      eax, eax
004acccc 744e                     je        0x4acd1c
004accce 8b                       .byte     0x8b
004acccf 4d                       dec       ebp

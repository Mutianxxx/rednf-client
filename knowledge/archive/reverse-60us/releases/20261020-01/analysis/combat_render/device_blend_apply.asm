00b084f0 55                       push       ebp
00b084f1 8bec                     mov        ebp, esp
00b084f3 56                       push       esi
00b084f4 57                       push       edi
00b084f5 8b7d08                   mov        edi, dword ptr [ebp + 8]
00b084f8 668b07                   mov        ax, word ptr [edi]
00b084fb 8bf1                     mov        esi, ecx
00b084fd 66398640030500           cmp        word ptr [esi + 0x50340], ax
00b08504 747f                     je         0xb08585
00b08506 0fb7c0                   movzx      eax, ax
00b08509 83f804                   cmp        eax, 4
00b0850c 7777                     ja         0xb08585
00b0850e ff24853086b000           jmp        dword ptr [eax*4 + 0xb08630]
00b08515 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08518 8b08                     mov        ecx, dword ptr [eax]
00b0851a 6a05                     push       5
00b0851c 6a13                     push       0x13
00b0851e 50                       push       eax
00b0851f ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08525 6a06                     push       6
00b08527 eb4e                     jmp        0xb08577
00b08529 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0852c 8b08                     mov        ecx, dword ptr [eax]
00b0852e 6a09                     push       9
00b08530 6a13                     push       0x13
00b08532 50                       push       eax
00b08533 ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08539 6a05                     push       5
00b0853b eb3a                     jmp        0xb08577
00b0853d 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08540 8b08                     mov        ecx, dword ptr [eax]
00b08542 6a05                     push       5
00b08544 6a13                     push       0x13
00b08546 50                       push       eax
00b08547 ff91c8000000             call       dword ptr [ecx + 0xc8]
00b0854d 6a02                     push       2
00b0854f eb26                     jmp        0xb08577
00b08551 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08554 8b08                     mov        ecx, dword ptr [eax]
00b08556 6a04                     push       4
00b08558 6a13                     push       0x13
00b0855a 50                       push       eax
00b0855b ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08561 6a06                     push       6
00b08563 eb12                     jmp        0xb08577
00b08565 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08568 8b08                     mov        ecx, dword ptr [eax]
00b0856a 6a0a                     push       0xa
00b0856c 6a13                     push       0x13
00b0856e 50                       push       eax
00b0856f ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08575 6a01                     push       1
00b08577 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0857a 8b10                     mov        edx, dword ptr [eax]
00b0857c 6a14                     push       0x14
00b0857e 50                       push       eax
00b0857f ff92c8000000             call       dword ptr [edx + 0xc8]
00b08585 668b4702                 mov        ax, word ptr [edi + 2]
00b08589 66398642030500           cmp        word ptr [esi + 0x50342], ax
00b08590 7445                     je         0xb085d7
00b08592 0fb7c0                   movzx      eax, ax
00b08595 83e800                   sub        eax, 0
00b08598 7419                     je         0xb085b3
00b0859a 48                       dec        eax
00b0859b 753a                     jne        0xb085d7
00b0859d 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b085a0 8b08                     mov        ecx, dword ptr [eax]
00b085a2 6a03                     push       3
00b085a4 6a01                     push       1
00b085a6 6a00                     push       0
00b085a8 50                       push       eax
00b085a9 ff91fc000000             call       dword ptr [ecx + 0xfc]
00b085af 6a03                     push       3
00b085b1 eb14                     jmp        0xb085c7
00b085b3 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b085b6 8b08                     mov        ecx, dword ptr [eax]
00b085b8 6a04                     push       4
00b085ba 6a01                     push       1
00b085bc 6a00                     push       0
00b085be 50                       push       eax
00b085bf ff91fc000000             call       dword ptr [ecx + 0xfc]
00b085c5 6a00                     push       0
00b085c7 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b085ca 8b10                     mov        edx, dword ptr [eax]
00b085cc 6a03                     push       3
00b085ce 6a00                     push       0
00b085d0 50                       push       eax
00b085d1 ff92fc000000             call       dword ptr [edx + 0xfc]
00b085d7 8b8644030500             mov        eax, dword ptr [esi + 0x50344]
00b085dd 3b4704                   cmp        eax, dword ptr [edi + 4]
00b085e0 742f                     je         0xb08611
00b085e2 8b4704                   mov        eax, dword ptr [edi + 4]
00b085e5 0fb67f06                 movzx      edi, byte ptr [edi + 6]
00b085e9 8b4e1c                   mov        ecx, dword ptr [esi + 0x1c]
00b085ec 8b11                     mov        edx, dword ptr [ecx]
00b085ee 53                       push       ebx
00b085ef 8bd8                     mov        ebx, eax
00b085f1 81e3ff000000             and        ebx, 0xff
00b085f7 c1e310                   shl        ebx, 0x10
00b085fa 0bdf                     or         ebx, edi
00b085fc 2500ff00ff               and        eax, 0xff00ff00
00b08601 0bd8                     or         ebx, eax
00b08603 53                       push       ebx
00b08604 6a3c                     push       0x3c
00b08606 51                       push       ecx
00b08607 ff92c8000000             call       dword ptr [edx + 0xc8]
00b0860d 8b7d08                   mov        edi, dword ptr [ebp + 8]
00b08610 5b                       pop        ebx
00b08611 8b07                     mov        eax, dword ptr [edi]
00b08613 898640030500             mov        dword ptr [esi + 0x50340], eax
00b08619 8b4f04                   mov        ecx, dword ptr [edi + 4]
00b0861c 5f                       pop        edi
00b0861d 898e44030500             mov        dword ptr [esi + 0x50344], ecx
00b08623 b801000000               mov        eax, 1
00b08628 5e                       pop        esi
00b08629 5d                       pop        ebp
00b0862a c20400                   ret        4
00b0862d 8d4900                   lea        ecx, [ecx]
00b08630 1585b00029               adc        eax, 0x2900b085
00b08635 85b0003d85b0             test       dword ptr [eax - 0x4f7ac300], esi
00b0863b 005185                   add        byte ptr [ecx - 0x7b], dl
00b0863e b000                     mov        al, 0
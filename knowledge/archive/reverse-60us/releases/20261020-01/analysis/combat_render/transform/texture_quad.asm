00add3d0 55                       push       ebp
00add3d1 8bec                     mov        ebp, esp
00add3d3 83ec60                   sub        esp, 0x60
00add3d6 56                       push       esi
00add3d7 8bf1                     mov        esi, ecx
00add3d9 e8b2fbffff               call       0xadcf90
00add3de 84c0                     test       al, al
00add3e0 0f8401020000             je         0xadd5e7
00add3e6 ff15d8f04001             call       dword ptr [0x140f0d8]
00add3ec 6a04                     push       4
00add3ee 894654                   mov        dword ptr [esi + 0x54], eax
00add3f1 e8bacb0200               call       0xb09fb0
00add3f6 d9451c                   fld        dword ptr [ebp + 0x1c]
00add3f9 d9e0                     fchs       
00add3fb 8d45a0                   lea        eax, [ebp - 0x60]
00add3fe d91c24                   fstp       dword ptr [esp]
00add401 50                       push       eax
00add402 e82f811500               call       0xc35536
00add407 d905a4d7e900             fld        dword ptr [0xe9d7a4]
00add40d d9451c                   fld        dword ptr [ebp + 0x1c]
00add410 dae9                     fucompp    
00add412 dfe0                     fnstsw     ax
00add414 f6c444                   test       ah, 0x44
00add417 7a54                     jp         0xadd46d
00add419 d905cc46cc00             fld        dword ptr [0xcc46cc]
00add41f d94528                   fld        dword ptr [ebp + 0x28]
00add422 dae9                     fucompp    
00add424 dfe0                     fnstsw     ax
00add426 f6c444                   test       ah, 0x44
00add429 7a18                     jp         0xadd443
00add42b 8b4e14                   mov        ecx, dword ptr [esi + 0x14]
00add42e d1e9                     shr        ecx, 1
00add430 85c9                     test       ecx, ecx
00add432 894d28                   mov        dword ptr [ebp + 0x28], ecx
00add435 db4528                   fild       dword ptr [ebp + 0x28]
00add438 7d06                     jge        0xadd440
00add43a d805cc46cc00             fadd       dword ptr [0xcc46cc]
00add440 d95d28                   fstp       dword ptr [ebp + 0x28]
00add443 d905cc46cc00             fld        dword ptr [0xcc46cc]
00add449 d9452c                   fld        dword ptr [ebp + 0x2c]
00add44c dae9                     fucompp    
00add44e dfe0                     fnstsw     ax
00add450 f6c444                   test       ah, 0x44
00add453 7a18                     jp         0xadd46d
00add455 8b5618                   mov        edx, dword ptr [esi + 0x18]
00add458 d1ea                     shr        edx, 1
00add45a 85d2                     test       edx, edx
00add45c 89552c                   mov        dword ptr [ebp + 0x2c], edx
00add45f db452c                   fild       dword ptr [ebp + 0x2c]
00add462 7d06                     jge        0xadd46a
00add464 d805cc46cc00             fadd       dword ptr [0xcc46cc]
00add46a d95d2c                   fstp       dword ptr [ebp + 0x2c]
00add46d d945a0                   fld        dword ptr [ebp - 0x60]
00add470 53                       push       ebx
00add471 d84d20                   fmul       dword ptr [ebp + 0x20]
00add474 8b5d18                   mov        ebx, dword ptr [ebp + 0x18]
00add477 85db                     test       ebx, ebx
00add479 d95da0                   fstp       dword ptr [ebp - 0x60]
00add47c d945a4                   fld        dword ptr [ebp - 0x5c]
00add47f d84d24                   fmul       dword ptr [ebp + 0x24]
00add482 d95da4                   fstp       dword ptr [ebp - 0x5c]
00add485 d945b0                   fld        dword ptr [ebp - 0x50]
00add488 d84d20                   fmul       dword ptr [ebp + 0x20]
00add48b d95db0                   fstp       dword ptr [ebp - 0x50]
00add48e d945b4                   fld        dword ptr [ebp - 0x4c]
00add491 d84d24                   fmul       dword ptr [ebp + 0x24]
00add494 d95db4                   fstp       dword ptr [ebp - 0x4c]
00add497 db461c                   fild       dword ptr [esi + 0x1c]
00add49a d86528                   fsub       dword ptr [ebp + 0x28]
00add49d db4620                   fild       dword ptr [esi + 0x20]
00add4a0 d8652c                   fsub       dword ptr [ebp + 0x2c]
00add4a3 d945b0                   fld        dword ptr [ebp - 0x50]
00add4a6 d8c9                     fmul       st(1)
00add4a8 d9c2                     fld        st(2)
00add4aa d84da0                   fmul       dword ptr [ebp - 0x60]
00add4ad dec1                     faddp      st(1)
00add4af d95dd0                   fstp       dword ptr [ebp - 0x30]
00add4b2 d84db4                   fmul       dword ptr [ebp - 0x4c]
00add4b5 d9c9                     fxch       st(1)
00add4b7 d84da4                   fmul       dword ptr [ebp - 0x5c]
00add4ba dec1                     faddp      st(1)
00add4bc db4508                   fild       dword ptr [ebp + 8]
00add4bf d95508                   fst        dword ptr [ebp + 8]
00add4c2 d84528                   fadd       dword ptr [ebp + 0x28]
00add4c5 d845d0                   fadd       dword ptr [ebp - 0x30]
00add4c8 d95dd0                   fstp       dword ptr [ebp - 0x30]
00add4cb db450c                   fild       dword ptr [ebp + 0xc]
00add4ce d9550c                   fst        dword ptr [ebp + 0xc]
00add4d1 d8452c                   fadd       dword ptr [ebp + 0x2c]
00add4d4 d8c1                     fadd       st(1)
00add4d6 d95dd4                   fstp       dword ptr [ebp - 0x2c]
00add4d9 ddd8                     fstp       st(0)
00add4db 7563                     jne        0xadd540
00add4dd d905581fcc00             fld        dword ptr [0xcc1f58]
00add4e3 d94520                   fld        dword ptr [ebp + 0x20]
00add4e6 dae9                     fucompp    
00add4e8 dfe0                     fnstsw     ax
00add4ea f6c444                   test       ah, 0x44
00add4ed 7a16                     jp         0xadd505
00add4ef d905581fcc00             fld        dword ptr [0xcc1f58]
00add4f5 d94524                   fld        dword ptr [ebp + 0x24]
00add4f8 dae9                     fucompp    
00add4fa dfe0                     fnstsw     ax
00add4fc f6c444                   test       ah, 0x44
00add4ff 7a04                     jp         0xadd505
00add501 32c0                     xor        al, al
00add503 eb04                     jmp        0xadd509
00add505 33c0                     xor        eax, eax
00add507 b001                     mov        al, 1
00add509 8b5510                   mov        edx, dword ptr [ebp + 0x10]
00add50c 50                       push       eax
00add50d 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00add510 50                       push       eax
00add511 8b4530                   mov        eax, dword ptr [ebp + 0x30]
00add514 8d4da0                   lea        ecx, [ebp - 0x60]
00add517 51                       push       ecx
00add518 8b4e68                   mov        ecx, dword ptr [esi + 0x68]
00add51b 83c230                   add        edx, 0x30
00add51e 52                       push       edx
00add51f 50                       push       eax
00add520 51                       push       ecx
00add521 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00add527 e804b80200               call       0xb08d30
00add52c 6a00                     push       0
00add52e 6a04                     push       4
00add530 e8bbca0200               call       0xb09ff0
00add535 83c408                   add        esp, 8
00add538 5b                       pop        ebx
00add539 5e                       pop        esi
00add53a 8be5                     mov        esp, ebp
00add53c 5d                       pop        ebp
00add53d c23000                   ret        0x30
00add540 a1e0b80d01               mov        eax, dword ptr [0x10db8e0]
00add545 8a8838030500             mov        cl, byte ptr [eax + 0x50338]
00add54b 84c9                     test       cl, cl
00add54d 0f8587000000             jne        0xadd5da
00add553 8b501c                   mov        edx, dword ptr [eax + 0x1c]
00add556 57                       push       edi
00add557 8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00add55a 57                       push       edi
00add55b 52                       push       edx
00add55c e85ff5ffff               call       0xadcac0
00add561 a06126ff00               mov        al, byte ptr [0xff2661]
00add566 83c408                   add        esp, 8
00add569 84c0                     test       al, al
00add56b 740b                     je         0xadd578
00add56d 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00add573 e898b10200               call       0xb08710
00add578 8b4528                   mov        eax, dword ptr [ebp + 0x28]
00add57b db461c                   fild       dword ptr [esi + 0x1c]
00add57e 8b4d2c                   mov        ecx, dword ptr [ebp + 0x2c]
00add581 8b5520                   mov        edx, dword ptr [ebp + 0x20]
00add584 53                       push       ebx
00add585 d95de8                   fstp       dword ptr [ebp - 0x18]
00add588 db4620                   fild       dword ptr [esi + 0x20]
00add58b 8945f8                   mov        dword ptr [ebp - 8], eax
00add58e 8b4524                   mov        eax, dword ptr [ebp + 0x24]
00add591 894dfc                   mov        dword ptr [ebp - 4], ecx
00add594 8b4d08                   mov        ecx, dword ptr [ebp + 8]
00add597 d95dec                   fstp       dword ptr [ebp - 0x14]
00add59a 8945f4                   mov        dword ptr [ebp - 0xc], eax
00add59d 8955f0                   mov        dword ptr [ebp - 0x10], edx
00add5a0 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00add5a3 894de0                   mov        dword ptr [ebp - 0x20], ecx
00add5a6 8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00add5a9 8d45a0                   lea        eax, [ebp - 0x60]
00add5ac 50                       push       eax
00add5ad 51                       push       ecx
00add5ae 8955e4                   mov        dword ptr [ebp - 0x1c], edx
00add5b1 8b551c                   mov        edx, dword ptr [ebp + 0x1c]
00add5b4 52                       push       edx
00add5b5 8b5668                   mov        edx, dword ptr [esi + 0x68]
00add5b8 8d45f8                   lea        eax, [ebp - 8]
00add5bb 50                       push       eax
00add5bc 8d4df0                   lea        ecx, [ebp - 0x10]
00add5bf 51                       push       ecx
00add5c0 56                       push       esi
00add5c1 52                       push       edx
00add5c2 83c730                   add        edi, 0x30
00add5c5 57                       push       edi
00add5c6 8d45e8                   lea        eax, [ebp - 0x18]
00add5c9 50                       push       eax
00add5ca 8d4de0                   lea        ecx, [ebp - 0x20]
00add5cd 51                       push       ecx
00add5ce 8b0d90c20f01             mov        ecx, dword ptr [0x10fc290]
00add5d4 e8e7230200               call       0xaff9c0
00add5d9 5f                       pop        edi
00add5da 6a00                     push       0
00add5dc 6a04                     push       4
00add5de e80dca0200               call       0xb09ff0
00add5e3 83c408                   add        esp, 8
00add5e6 5b                       pop        ebx
00add5e7 5e                       pop        esi
00add5e8 8be5                     mov        esp, ebp
00add5ea 5d                       pop        ebp
00add5eb c23000                   ret        0x30
00add5ee cc                       int3       
00add5ef cc                       int3       

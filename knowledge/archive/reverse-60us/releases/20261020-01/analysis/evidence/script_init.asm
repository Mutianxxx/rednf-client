; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 0082fde0..0082ff2e (end exclusive); file offset 0042fde0
; This is an instruction excerpt, not a recovered original source file.
0082fde0  55                       push       ebp
0082fde1  8bec                     mov        ebp, esp
0082fde3  8b4508                   mov        eax, dword ptr [ebp + 8]
0082fde6  6804010000               push       0x104
0082fdeb  50                       push       eax
0082fdec  6858050501               push       0x1050558
0082fdf1  e8d00a3d00               call       0xc008c6
0082fdf6  6858050501               push       0x1050558
0082fdfb  e8cdff3c00               call       0xbffdcd
0082fe00  83c410                   add        esp, 0x10
0082fe03  85c0                     test       eax, eax
0082fe05  7f04                     jg         0x82fe0b
0082fe07  32c0                     xor        al, al
0082fe09  5d                       pop        ebp
0082fe0a  c3                       ret        
0082fe0b  668b044556050501         mov        ax, word ptr [eax*2 + 0x1050556]
0082fe13  663d5c00                 cmp        ax, 0x5c
0082fe17  741d                     je         0x82fe36
0082fe19  663d2f00                 cmp        ax, 0x2f
0082fe1d  7417                     je         0x82fe36
0082fe1f  6804010000               push       0x104
0082fe24  6804b9ca00               push       0xcab904
0082fe29  6858050501               push       0x1050558
0082fe2e  e80f243d00               call       0xc02242
0082fe33  83c40c                   add        esp, 0xc
0082fe36  53                       push       ebx
0082fe37  6a00                     push       0
0082fe39  bb01000000               mov        ebx, 1
0082fe3e  68d038e100               push       0xe138d0
0082fe43  881dd810f700             mov        byte ptr [0xf710d8], bl
0082fe49  e819083d00               call       0xc00667
0082fe4e  83c408                   add        esp, 8
0082fe51  85c0                     test       eax, eax
0082fe53  7506                     jne        0x82fe5b
0082fe55  881dd810f700             mov        byte ptr [0xf710d8], bl
0082fe5b  6a00                     push       0
0082fe5d  68b438e100               push       0xe138b4
0082fe62  e800083d00               call       0xc00667
0082fe67  83c408                   add        esp, 8
0082fe6a  85c0                     test       eax, eax
0082fe6c  7505                     jne        0x82fe73
0082fe6e  a2d810f700               mov        byte ptr [0xf710d8], al
0082fe73  6a00                     push       0
0082fe75  689438e100               push       0xe13894
0082fe7a  e8e8073d00               call       0xc00667
0082fe7f  83c408                   add        esp, 8
0082fe82  85c0                     test       eax, eax
0082fe84  7506                     jne        0x82fe8c
0082fe86  881d60070501             mov        byte ptr [0x1050760], bl
0082fe8c  6a00                     push       0
0082fe8e  687438e100               push       0xe13874
0082fe93  e8cf073d00               call       0xc00667
0082fe98  83c408                   add        esp, 8
0082fe9b  85c0                     test       eax, eax
0082fe9d  7505                     jne        0x82fea4
0082fe9f  a260070501               mov        byte ptr [0x1050760], al
0082fea4  53                       push       ebx
0082fea5  6a00                     push       0
0082fea7  685c38e100               push       0xe1385c
0082feac  b9a8110501               mov        ecx, 0x10511a8
0082feb1  881dd810f700             mov        byte ptr [0xf710d8], bl
0082feb7  e814722200               call       0xa570d0
0082febc  3bc3                     cmp        eax, ebx
0082febe  7505                     jne        0x82fec5
0082fec0  32c0                     xor        al, al
0082fec2  5b                       pop        ebx
0082fec3  5d                       pop        ebp
0082fec4  c3                       ret        
0082fec5  a060070501               mov        al, byte ptr [0x1050760]
0082feca  84c0                     test       al, al
0082fecc  745b                     je         0x82ff29
0082fece  a164070501               mov        eax, dword ptr [0x1050764]
0082fed3  85c0                     test       eax, eax
0082fed5  891d2c120501             mov        dword ptr [0x105122c], ebx
0082fedb  7402                     je         0x82fedf
0082fedd  ffd0                     call       eax
0082fedf  6a00                     push       0
0082fee1  6a00                     push       0
0082fee3  683c38e100               push       0xe1383c
0082fee8  e8032e2600               call       0xa92cf0
0082feed  83c404                   add        esp, 4
0082fef0  50                       push       eax
0082fef1  68e0baca00               push       0xcabae0
0082fef6  e8f52d2600               call       0xa92cf0
0082fefb  83c404                   add        esp, 4
0082fefe  50                       push       eax
0082feff  b928120501               mov        ecx, 0x1051228
0082ff04  e8472a0800               call       0x8b2950
0082ff09  b928120501               mov        ecx, 0x1051228
0082ff0e  e89d2d0800               call       0x8b2cb0
0082ff13  50                       push       eax
0082ff14  b928120501               mov        ecx, 0x1051228
0082ff19  e8422d0800               call       0x8b2c60
0082ff1e  50                       push       eax
0082ff1f  b928120501               mov        ecx, 0x1051228
0082ff24  e8e72c0800               call       0x8b2c10
0082ff29  8ac3                     mov        al, bl
0082ff2b  5b                       pop        ebx
0082ff2c  5d                       pop        ebp
0082ff2d  c3                       ret        

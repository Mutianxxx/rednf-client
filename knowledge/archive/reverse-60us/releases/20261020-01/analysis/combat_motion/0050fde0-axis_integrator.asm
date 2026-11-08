0050fde0  55                       push       ebp
0050fde1  8bec                     mov        ebp, esp
0050fde3  83ec24                   sub        esp, 0x24
0050fde6  53                       push       ebx
0050fde7  56                       push       esi
0050fde8  8bf1                     mov        esi, ecx
0050fdea  8b06                     mov        eax, dword ptr [esi]
0050fdec  85c0                     test       eax, eax
0050fdee  57                       push       edi
0050fdef  8bc8                     mov        ecx, eax
0050fdf1  754a                     jne        0x50fe3d
0050fdf3  8d4e08                   lea        ecx, [esi + 8]
0050fdf6  8d5e08                   lea        ebx, [esi + 8]
0050fdf9  8b7d08                   mov        edi, dword ptr [ebp + 8]
0050fdfc  8b01                     mov        eax, dword ptr [ecx]
0050fdfe  57                       push       edi
0050fdff  ff5008                   call       dword ptr [eax + 8]
0050fe02  8b13                     mov        edx, dword ptr [ebx]
0050fe04  d9e1                     fabs       
0050fe06  57                       push       edi
0050fe07  dd5de8                   fstp       qword ptr [ebp - 0x18]
0050fe0a  8bcb                     mov        ecx, ebx
0050fe0c  ff5208                   call       dword ptr [edx + 8]
0050fe0f  d9e1                     fabs       
0050fe11  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
0050fe17  dc5de8                   fcomp      qword ptr [ebp - 0x18]
0050fe1a  dfe0                     fnstsw     ax
0050fe1c  f6c401                   test       ah, 1
0050fe1f  7520                     jne        0x50fe41
0050fe21  8b06                     mov        eax, dword ptr [esi]
0050fe23  85c0                     test       eax, eax
0050fe25  7503                     jne        0x50fe2a
0050fe27  8d4608                   lea        eax, [esi + 8]
0050fe2a  8b4cb81c                 mov        ecx, dword ptr [eax + edi*4 + 0x1c]
0050fe2e  85c9                     test       ecx, ecx
0050fe30  750f                     jne        0x50fe41
0050fe32  5f                       pop        edi
0050fe33  5e                       pop        esi
0050fe34  33c0                     xor        eax, eax
0050fe36  5b                       pop        ebx
0050fe37  8be5                     mov        esp, ebp
0050fe39  5d                       pop        ebp
0050fe3a  c20800                   ret        8
0050fe3d  8bd8                     mov        ebx, eax
0050fe3f  ebb8                     jmp        0x50fdf9
0050fe41  8b0e                     mov        ecx, dword ptr [esi]
0050fe43  85c9                     test       ecx, ecx
0050fe45  7503                     jne        0x50fe4a
0050fe47  8d4e08                   lea        ecx, [esi + 8]
0050fe4a  8b01                     mov        eax, dword ptr [ecx]
0050fe4c  57                       push       edi
0050fe4d  ff5008                   call       dword ptr [eax + 8]
0050fe50  d95d08                   fstp       dword ptr [ebp + 8]
0050fe53  8b06                     mov        eax, dword ptr [esi]
0050fe55  85c0                     test       eax, eax
0050fe57  8bc8                     mov        ecx, eax
0050fe59  7503                     jne        0x50fe5e
0050fe5b  8d4e08                   lea        ecx, [esi + 8]
0050fe5e  85c0                     test       eax, eax
0050fe60  8b54b91c                 mov        edx, dword ptr [ecx + edi*4 + 0x1c]
0050fe64  8955f4                   mov        dword ptr [ebp - 0xc], edx
0050fe67  8bc8                     mov        ecx, eax
0050fe69  7503                     jne        0x50fe6e
0050fe6b  8d4e08                   lea        ecx, [esi + 8]
0050fe6e  85d2                     test       edx, edx
0050fe70  8b4cb928                 mov        ecx, dword ptr [ecx + edi*4 + 0x28]
0050fe74  894dfc                   mov        dword ptr [ebp - 4], ecx
0050fe77  7508                     jne        0x50fe81
0050fe79  d94508                   fld        dword ptr [ebp + 8]
0050fe7c  e942010000               jmp        0x50ffc3
0050fe81  83f9ff                   cmp        ecx, -1
0050fe84  0f84ab000000             je         0x50ff35
0050fe8a  3b4d0c                   cmp        ecx, dword ptr [ebp + 0xc]
0050fe8d  0f8da2000000             jge        0x50ff35
0050fe93  85c0                     test       eax, eax
0050fe95  8bc8                     mov        ecx, eax
0050fe97  7506                     jne        0x50fe9f
0050fe99  8d4e08                   lea        ecx, [esi + 8]
0050fe9c  8d4608                   lea        eax, [esi + 8]
0050fe9f  8b11                     mov        edx, dword ptr [ecx]
0050fea1  8945f8                   mov        dword ptr [ebp - 8], eax
0050fea4  8b00                     mov        eax, dword ptr [eax]
0050fea6  57                       push       edi
0050fea7  8945f0                   mov        dword ptr [ebp - 0x10], eax
0050feaa  ff5208                   call       dword ptr [edx + 8]
0050fead  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
0050feb0  8bc3                     mov        eax, ebx
0050feb2  0faf45f4                 imul       eax, dword ptr [ebp - 0xc]
0050feb6  8945f4                   mov        dword ptr [ebp - 0xc], eax
0050feb9  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
0050febc  51                       push       ecx
0050febd  db45f4                   fild       dword ptr [ebp - 0xc]
0050fec0  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0050fec3  d80df811cc00             fmul       dword ptr [0xcc11f8]
0050fec9  dec1                     faddp      st(1)
0050fecb  d91c24                   fstp       dword ptr [esp]
0050fece  57                       push       edi
0050fecf  ff500c                   call       dword ptr [eax + 0xc]
0050fed2  8b450c                   mov        eax, dword ptr [ebp + 0xc]
0050fed5  2bc3                     sub        eax, ebx
0050fed7  8945f0                   mov        dword ptr [ebp - 0x10], eax
0050feda  8b06                     mov        eax, dword ptr [esi]
0050fedc  33db                     xor        ebx, ebx
0050fede  3bc3                     cmp        eax, ebx
0050fee0  7503                     jne        0x50fee5
0050fee2  8d4608                   lea        eax, [esi + 8]
0050fee5  8b10                     mov        edx, dword ptr [eax]
0050fee7  57                       push       edi
0050fee8  8bc8                     mov        ecx, eax
0050feea  ff5208                   call       dword ptr [edx + 8]
0050feed  d84508                   fadd       dword ptr [ebp + 8]
0050fef0  8b0e                     mov        ecx, dword ptr [esi]
0050fef2  3bcb                     cmp        ecx, ebx
0050fef4  d80dd04bcd00             fmul       dword ptr [0xcd4bd0]
0050fefa  d95d08                   fstp       dword ptr [ebp + 8]
0050fefd  7503                     jne        0x50ff02
0050feff  8d4e08                   lea        ecx, [esi + 8]
0050ff02  8b01                     mov        eax, dword ptr [ecx]
0050ff04  57                       push       edi
0050ff05  ff5008                   call       dword ptr [eax + 8]
0050ff08  da4df0                   fimul      dword ptr [ebp - 0x10]
0050ff0b  8b06                     mov        eax, dword ptr [esi]
0050ff0d  3bc3                     cmp        eax, ebx
0050ff0f  db45fc                   fild       dword ptr [ebp - 4]
0050ff12  d84d08                   fmul       dword ptr [ebp + 8]
0050ff15  dec1                     faddp      st(1)
0050ff17  da750c                   fidiv      dword ptr [ebp + 0xc]
0050ff1a  7503                     jne        0x50ff1f
0050ff1c  8d4608                   lea        eax, [esi + 8]
0050ff1f  895cb828                 mov        dword ptr [eax + edi*4 + 0x28], ebx
0050ff23  8b06                     mov        eax, dword ptr [esi]
0050ff25  3bc3                     cmp        eax, ebx
0050ff27  7503                     jne        0x50ff2c
0050ff29  8d4608                   lea        eax, [esi + 8]
0050ff2c  895cb81c                 mov        dword ptr [eax + edi*4 + 0x1c], ebx
0050ff30  e98e000000               jmp        0x50ffc3
0050ff35  85c0                     test       eax, eax
0050ff37  8bc8                     mov        ecx, eax
0050ff39  7506                     jne        0x50ff41
0050ff3b  8d4e08                   lea        ecx, [esi + 8]
0050ff3e  8d4608                   lea        eax, [esi + 8]
0050ff41  8b11                     mov        edx, dword ptr [ecx]
0050ff43  8945f8                   mov        dword ptr [ebp - 8], eax
0050ff46  8b00                     mov        eax, dword ptr [eax]
0050ff48  57                       push       edi
0050ff49  8945ec                   mov        dword ptr [ebp - 0x14], eax
0050ff4c  ff5208                   call       dword ptr [edx + 8]
0050ff4f  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
0050ff52  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
0050ff55  0fafc3                   imul       eax, ebx
0050ff58  8945f0                   mov        dword ptr [ebp - 0x10], eax
0050ff5b  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
0050ff5e  51                       push       ecx
0050ff5f  db45f0                   fild       dword ptr [ebp - 0x10]
0050ff62  8b4df8                   mov        ecx, dword ptr [ebp - 8]
0050ff65  d80df811cc00             fmul       dword ptr [0xcc11f8]
0050ff6b  dec1                     faddp      st(1)
0050ff6d  d91c24                   fstp       dword ptr [esp]
0050ff70  57                       push       edi
0050ff71  ff500c                   call       dword ptr [eax + 0xc]
0050ff74  8b06                     mov        eax, dword ptr [esi]
0050ff76  85c0                     test       eax, eax
0050ff78  7503                     jne        0x50ff7d
0050ff7a  8d4608                   lea        eax, [esi + 8]
0050ff7d  8b10                     mov        edx, dword ptr [eax]
0050ff7f  57                       push       edi
0050ff80  8bc8                     mov        ecx, eax
0050ff82  ff5208                   call       dword ptr [edx + 8]
0050ff85  d84508                   fadd       dword ptr [ebp + 8]
0050ff88  837dfcff                 cmp        dword ptr [ebp - 4], -1
0050ff8c  d80dd04bcd00             fmul       dword ptr [0xcd4bd0]
0050ff92  742f                     je         0x50ffc3
0050ff94  8b06                     mov        eax, dword ptr [esi]
0050ff96  85c0                     test       eax, eax
0050ff98  7503                     jne        0x50ff9d
0050ff9a  8d4608                   lea        eax, [esi + 8]
0050ff9d  295cb828                 sub        dword ptr [eax + edi*4 + 0x28], ebx
0050ffa1  8b06                     mov        eax, dword ptr [esi]
0050ffa3  85c0                     test       eax, eax
0050ffa5  8bc8                     mov        ecx, eax
0050ffa7  7503                     jne        0x50ffac
0050ffa9  8d4e08                   lea        ecx, [esi + 8]
0050ffac  8b54b928                 mov        edx, dword ptr [ecx + edi*4 + 0x28]
0050ffb0  85d2                     test       edx, edx
0050ffb2  750f                     jne        0x50ffc3
0050ffb4  85c0                     test       eax, eax
0050ffb6  7503                     jne        0x50ffbb
0050ffb8  8d4608                   lea        eax, [esi + 8]
0050ffbb  c744b81c00000000         mov        dword ptr [eax + edi*4 + 0x1c], 0
0050ffc3  db450c                   fild       dword ptr [ebp + 0xc]
0050ffc6  d8c9                     fmul       st(1)
0050ffc8  d80df811cc00             fmul       dword ptr [0xcc11f8]
0050ffce  d95d0c                   fstp       dword ptr [ebp + 0xc]
0050ffd1  ddd8                     fstp       st(0)
0050ffd3  d9450c                   fld        dword ptr [ebp + 0xc]
0050ffd6  d81d2c68cd00             fcomp      dword ptr [0xcd682c]
0050ffdc  dfe0                     fnstsw     ax
0050ffde  f6c441                   test       ah, 0x41
0050ffe1  7509                     jne        0x50ffec
0050ffe3  c7450c0000fa44           mov        dword ptr [ebp + 0xc], 0x44fa0000
0050ffea  eb17                     jmp        0x510003
0050ffec  d9450c                   fld        dword ptr [ebp + 0xc]
0050ffef  d81d2868cd00             fcomp      dword ptr [0xcd6828]
0050fff5  dfe0                     fnstsw     ax
0050fff7  f6c405                   test       ah, 5
0050fffa  7a07                     jp         0x510003
0050fffc  c7450c0000fac4           mov        dword ptr [ebp + 0xc], 0xc4fa0000
00510003  8b4678                   mov        eax, dword ptr [esi + 0x78]
00510006  33db                     xor        ebx, ebx
00510008  3bc3                     cmp        eax, ebx
0051000a  740b                     je         0x510017
0051000c  8a467c                   mov        al, byte ptr [esi + 0x7c]
0051000f  84c0                     test       al, al
00510011  0f85b9000000             jne        0x5100d0
00510017  395e74                   cmp        dword ptr [esi + 0x74], ebx
0051001a  0f84b0000000             je         0x5100d0
00510020  895ddc                   mov        dword ptr [ebp - 0x24], ebx
00510023  895de0                   mov        dword ptr [ebp - 0x20], ebx
00510026  895de4                   mov        dword ptr [ebp - 0x1c], ebx
00510029  8da42400000000           lea        esp, [esp]
00510030  8b0e                     mov        ecx, dword ptr [esi]
00510032  85c9                     test       ecx, ecx
00510034  7503                     jne        0x510039
00510036  8d4e08                   lea        ecx, [esi + 8]
00510039  8b01                     mov        eax, dword ptr [ecx]
0051003b  53                       push       ebx
0051003c  ff10                     call       dword ptr [eax]
0051003e  51                       push       ecx
0051003f  d91c24                   fstp       dword ptr [esp]
00510042  e8a97ff3ff               call       0x447ff0
00510047  83c404                   add        esp, 4
0051004a  89449ddc                 mov        dword ptr [ebp + ebx*4 - 0x24], eax
0051004e  43                       inc        ebx
0051004f  83fb03                   cmp        ebx, 3
00510052  7cdc                     jl         0x510030
00510054  8b0e                     mov        ecx, dword ptr [esi]
00510056  85c9                     test       ecx, ecx
00510058  7503                     jne        0x51005d
0051005a  8d4e08                   lea        ecx, [esi + 8]
0051005d  8b11                     mov        edx, dword ptr [ecx]
0051005f  57                       push       edi
00510060  ff12                     call       dword ptr [edx]
00510062  d8450c                   fadd       dword ptr [ebp + 0xc]
00510065  51                       push       ecx
00510066  d91c24                   fstp       dword ptr [esp]
00510069  e8827ff3ff               call       0x447ff0
0051006e  8bd8                     mov        ebx, eax
00510070  8b44bddc                 mov        eax, dword ptr [ebp + edi*4 - 0x24]
00510074  83c404                   add        esp, 4
00510077  3bc3                     cmp        eax, ebx
00510079  7455                     je         0x5100d0
0051007b  eb03                     jmp        0x510080
0051007d  8d4900                   lea        ecx, [ecx]
00510080  8b44bddc                 mov        eax, dword ptr [ebp + edi*4 - 0x24]
00510084  3bc3                     cmp        eax, ebx
00510086  8945ec                   mov        dword ptr [ebp - 0x14], eax
00510089  7d03                     jge        0x51008e
0051008b  40                       inc        eax
0051008c  eb01                     jmp        0x51008f
0051008e  48                       dec        eax
0051008f  83ff02                   cmp        edi, 2
00510092  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00510095  8944bddc                 mov        dword ptr [ebp + edi*4 - 0x24], eax
00510099  c7450800000000           mov        dword ptr [ebp + 8], 0
005100a0  8b01                     mov        eax, dword ptr [ecx]
005100a2  750c                     jne        0x5100b0
005100a4  8b55e4                   mov        edx, dword ptr [ebp - 0x1c]
005100a7  52                       push       edx
005100a8  ff90a8000000             call       dword ptr [eax + 0xa8]
005100ae  eb12                     jmp        0x5100c2
005100b0  8d5508                   lea        edx, [ebp + 8]
005100b3  52                       push       edx
005100b4  8b55e0                   mov        edx, dword ptr [ebp - 0x20]
005100b7  52                       push       edx
005100b8  8b55dc                   mov        edx, dword ptr [ebp - 0x24]
005100bb  52                       push       edx
005100bc  ff90ac000000             call       dword ptr [eax + 0xac]
005100c2  84c0                     test       al, al
005100c4  0f848a000000             je         0x510154
005100ca  395cbddc                 cmp        dword ptr [ebp + edi*4 - 0x24], ebx
005100ce  75b0                     jne        0x510080
005100d0  8b06                     mov        eax, dword ptr [esi]
005100d2  85c0                     test       eax, eax
005100d4  8bc8                     mov        ecx, eax
005100d6  7506                     jne        0x5100de
005100d8  8d4e08                   lea        ecx, [esi + 8]
005100db  8d4608                   lea        eax, [esi + 8]
005100de  8b11                     mov        edx, dword ptr [ecx]
005100e0  8b18                     mov        ebx, dword ptr [eax]
005100e2  57                       push       edi
005100e3  894508                   mov        dword ptr [ebp + 8], eax
005100e6  ff12                     call       dword ptr [edx]
005100e8  d8450c                   fadd       dword ptr [ebp + 0xc]
005100eb  51                       push       ecx
005100ec  8b4d08                   mov        ecx, dword ptr [ebp + 8]
005100ef  d91c24                   fstp       dword ptr [esp]
005100f2  57                       push       edi
005100f3  ff5304                   call       dword ptr [ebx + 4]
005100f6  8b06                     mov        eax, dword ptr [esi]
005100f8  85c0                     test       eax, eax
005100fa  8bc8                     mov        ecx, eax
005100fc  7503                     jne        0x510101
005100fe  8d4e08                   lea        ecx, [esi + 8]
00510101  8b54b91c                 mov        edx, dword ptr [ecx + edi*4 + 0x1c]
00510105  85d2                     test       edx, edx
00510107  8bc8                     mov        ecx, eax
00510109  0f85a4000000             jne        0x5101b3
0051010f  85c0                     test       eax, eax
00510111  0f8595000000             jne        0x5101ac
00510117  8d4e08                   lea        ecx, [esi + 8]
0051011a  83c608                   add        esi, 8
0051011d  8b01                     mov        eax, dword ptr [ecx]
0051011f  57                       push       edi
00510120  ff5008                   call       dword ptr [eax + 8]
00510123  8b16                     mov        edx, dword ptr [esi]
00510125  d9e1                     fabs       
00510127  57                       push       edi
00510128  dd5de8                   fstp       qword ptr [ebp - 0x18]
0051012b  8bce                     mov        ecx, esi
0051012d  ff5208                   call       dword ptr [edx + 8]
00510130  d9e1                     fabs       
00510132  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
00510138  dc5de8                   fcomp      qword ptr [ebp - 0x18]
0051013b  dfe0                     fnstsw     ax
0051013d  f6c401                   test       ah, 1
00510140  0f84ecfcffff             je         0x50fe32
00510146  5f                       pop        edi
00510147  5e                       pop        esi
00510148  b802000000               mov        eax, 2
0051014d  5b                       pop        ebx
0051014e  8be5                     mov        esp, ebp
00510150  5d                       pop        ebp
00510151  c20800                   ret        8
00510154  8b0e                     mov        ecx, dword ptr [esi]
00510156  85c9                     test       ecx, ecx
00510158  7503                     jne        0x51015d
0051015a  8d4e08                   lea        ecx, [esi + 8]
0051015d  db45ec                   fild       dword ptr [ebp - 0x14]
00510160  8b01                     mov        eax, dword ptr [ecx]
00510162  51                       push       ecx
00510163  d91c24                   fstp       dword ptr [esp]
00510166  57                       push       edi
00510167  ff5004                   call       dword ptr [eax + 4]
0051016a  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051016d  8b11                     mov        edx, dword ptr [ecx]
0051016f  6a01                     push       1
00510171  ff522c                   call       dword ptr [edx + 0x2c]
00510174  84c0                     test       al, al
00510176  7426                     je         0x51019e
00510178  8b0e                     mov        ecx, dword ptr [esi]
0051017a  85c9                     test       ecx, ecx
0051017c  7503                     jne        0x510181
0051017e  8d4e08                   lea        ecx, [esi + 8]
00510181  8b4674                   mov        eax, dword ptr [esi + 0x74]
00510184  8b5508                   mov        edx, dword ptr [ebp + 8]
00510187  8b18                     mov        ebx, dword ptr [eax]
00510189  8b01                     mov        eax, dword ptr [ecx]
0051018b  52                       push       edx
0051018c  57                       push       edi
0051018d  ff5008                   call       dword ptr [eax + 8]
00510190  51                       push       ecx
00510191  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00510194  d91c24                   fstp       dword ptr [esp]
00510197  57                       push       edi
00510198  ff9374020000             call       dword ptr [ebx + 0x274]
0051019e  5f                       pop        edi
0051019f  5e                       pop        esi
005101a0  b804000000               mov        eax, 4
005101a5  5b                       pop        ebx
005101a6  8be5                     mov        esp, ebp
005101a8  5d                       pop        ebp
005101a9  c20800                   ret        8
005101ac  8bf0                     mov        esi, eax
005101ae  e96affffff               jmp        0x51011d
005101b3  85c0                     test       eax, eax
005101b5  7530                     jne        0x5101e7
005101b7  8d4e08                   lea        ecx, [esi + 8]
005101ba  83c608                   add        esi, 8
005101bd  8b01                     mov        eax, dword ptr [ecx]
005101bf  57                       push       edi
005101c0  ff5008                   call       dword ptr [eax + 8]
005101c3  da4cbe1c                 fimul      dword ptr [esi + edi*4 + 0x1c]
005101c7  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
005101cd  dfe0                     fnstsw     ax
005101cf  f6c405                   test       ah, 5
005101d2  b801000000               mov        eax, 1
005101d7  7b05                     jnp        0x5101de
005101d9  b803000000               mov        eax, 3
005101de  5f                       pop        edi
005101df  5e                       pop        esi
005101e0  5b                       pop        ebx
005101e1  8be5                     mov        esp, ebp
005101e3  5d                       pop        ebp
005101e4  c20800                   ret        8
005101e7  8bf0                     mov        esi, eax
005101e9  ebd2                     jmp        0x5101bd

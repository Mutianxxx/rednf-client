00b099b0 55                       push      ebp
00b099b1 8bec                     mov       ebp, esp
00b099b3 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00b099b6 3b4514                   cmp       eax, dword ptr [ebp + 0x14]
00b099b9 7c05                     jl        0xb099c0
00b099bb d9450c                   fld       dword ptr [ebp + 0xc]
00b099be 5d                       pop       ebp
00b099bf c3                       ret       
00b099c0 85c0                     test      eax, eax
00b099c2 7f05                     jg        0xb099c9
00b099c4 d94508                   fld       dword ptr [ebp + 8]
00b099c7 5d                       pop       ebp
00b099c8 c3                       ret       
00b099c9 d9450c                   fld       dword ptr [ebp + 0xc]
00b099cc d86508                   fsub      dword ptr [ebp + 8]
00b099cf da4d10                   fimul     dword ptr [ebp + 0x10]
00b099d2 da7514                   fidiv     dword ptr [ebp + 0x14]
00b099d5 d84508                   fadd      dword ptr [ebp + 8]
00b099d8 5d                       pop       ebp
00b099d9 c3                       ret       
00b099da cc                       int3      
00b099db cc                       int3      
00b099dc cc                       int3      
00b099dd cc                       int3      
00b099de cc                       int3      
00b099df cc                       int3      
00b099e0 55                       push      ebp
00b099e1 8bec                     mov       ebp, esp
00b099e3 51                       push      ecx
00b099e4 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00b099e7 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
00b099ea 3bc1                     cmp       eax, ecx
00b099ec 7c07                     jl        0xb099f5
00b099ee d9450c                   fld       dword ptr [ebp + 0xc]
00b099f1 8be5                     mov       esp, ebp
00b099f3 5d                       pop       ebp
00b099f4 c3                       ret       
00b099f5 85c0                     test      eax, eax
00b099f7 7f07                     jg        0xb09a00
00b099f9 d94508                   fld       dword ptr [ebp + 8]
00b099fc 8be5                     mov       esp, ebp
00b099fe 5d                       pop       ebp
00b099ff c3                       ret       
00b09a00 8a5518                   mov       dl, byte ptr [ebp + 0x18]
00b09a03 d94508                   fld       dword ptr [ebp + 8]
00b09a06 84d2                     test      dl, dl
00b09a08 d9450c                   fld       dword ptr [ebp + 0xc]
00b09a0b 894510                   mov       dword ptr [ebp + 0x10], eax
00b09a0e 750f                     jne       0xb09a1f
00b09a10 ddd8                     fstp      st(0)
00b09a12 2bc8                     sub       ecx, eax
00b09a14 ddd8                     fstp      st(0)
00b09a16 894d10                   mov       dword ptr [ebp + 0x10], ecx
00b09a19 d9450c                   fld       dword ptr [ebp + 0xc]
00b09a1c d94508                   fld       dword ptr [ebp + 8]
00b09a1f db4514                   fild      dword ptr [ebp + 0x14]
00b09a22 d9c1                     fld       st(1)
00b09a24 d8e3                     fsub      st(3)
00b09a26 d9e1                     fabs      
00b09a28 dcc0                     fadd      st(0), st(0)
00b09a2a d8f1                     fdiv      st(1)
00b09a2c d95514                   fst       dword ptr [ebp + 0x14]
00b09a2f d8f1                     fdiv      st(1)
00b09a31 d9e0                     fchs      
00b09a33 d95dfc                   fstp      dword ptr [ebp - 4]
00b09a36 ddd8                     fstp      st(0)
00b09a38 d8d9                     fcomp     st(1)
00b09a3a db4510                   fild      dword ptr [ebp + 0x10]
00b09a3d d945fc                   fld       dword ptr [ebp - 4]
00b09a40 d8c9                     fmul      st(1)
00b09a42 dfe0                     fnstsw    ax
00b09a44 d80dd04bcd00             fmul      dword ptr [0xcd4bd0]
00b09a4a f6c441                   test      ah, 0x41
00b09a4d d84514                   fadd      dword ptr [ebp + 0x14]
00b09a50 d8c9                     fmul      st(1)
00b09a52 7508                     jne       0xb09a5c
00b09a54 dec2                     faddp     st(2)
00b09a56 ddd8                     fstp      st(0)
00b09a58 8be5                     mov       esp, ebp
00b09a5a 5d                       pop       ebp
00b09a5b c3                       ret       
00b09a5c deea                     fsubp     st(2)
00b09a5e ddd8                     fstp      st(0)
00b09a60 8be5                     mov       esp, ebp
00b09a62 5d                       pop       ebp
00b09a63 c3                       ret       
00b09a64 cc                       int3      
00b09a65 cc                       int3      
00b09a66 cc                       int3      
00b09a67 cc                       int3      
00b09a68 cc                       int3      
00b09a69 cc                       int3      
00b09a6a cc                       int3      
00b09a6b cc                       int3      
00b09a6c cc                       int3      
00b09a6d cc                       int3      
00b09a6e cc                       int3      
00b09a6f cc                       int3      

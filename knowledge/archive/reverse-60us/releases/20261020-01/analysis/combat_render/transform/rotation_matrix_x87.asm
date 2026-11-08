00c3553c 55                       push       ebp
00c3553d 8bec                     mov        ebp, esp
00c3553f 83ec10                   sub        esp, 0x10
00c35542 8d45f8                   lea        eax, [ebp - 8]
00c35545 8945f4                   mov        dword ptr [ebp - 0xc], eax
00c35548 8d45fc                   lea        eax, [ebp - 4]
00c3554b 8945f0                   mov        dword ptr [ebp - 0x10], eax
00c3554e 8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00c35551 8b55f4                   mov        edx, dword ptr [ebp - 0xc]
00c35554 d9450c                   fld        dword ptr [ebp + 0xc]
00c35557 d9fb                     fsincos    
00c35559 d91a                     fstp       dword ptr [edx]
00c3555b d918                     fstp       dword ptr [eax]
00c3555d d945f8                   fld        dword ptr [ebp - 8]
00c35560 8b4508                   mov        eax, dword ptr [ebp + 8]
00c35563 d9c0                     fld        st(0)
00c35565 d918                     fstp       dword ptr [eax]
00c35567 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00c3556a d9ee                     fldz       
00c3556c 894804                   mov        dword ptr [eax + 4], ecx
00c3556f d95808                   fstp       dword ptr [eax + 8]
00c35572 d9ee                     fldz       
00c35574 d9580c                   fstp       dword ptr [eax + 0xc]
00c35577 d945fc                   fld        dword ptr [ebp - 4]
00c3557a d9e0                     fchs       
00c3557c d95810                   fstp       dword ptr [eax + 0x10]
00c3557f d95814                   fstp       dword ptr [eax + 0x14]
00c35582 d9ee                     fldz       
00c35584 d95818                   fstp       dword ptr [eax + 0x18]
00c35587 d9ee                     fldz       
00c35589 d9581c                   fstp       dword ptr [eax + 0x1c]
00c3558c d9ee                     fldz       
00c3558e d95820                   fstp       dword ptr [eax + 0x20]
00c35591 d9ee                     fldz       
00c35593 d95824                   fstp       dword ptr [eax + 0x24]
00c35596 d9e8                     fld1       
00c35598 d95828                   fstp       dword ptr [eax + 0x28]
00c3559b d9ee                     fldz       
00c3559d d9582c                   fstp       dword ptr [eax + 0x2c]
00c355a0 d9ee                     fldz       
00c355a2 d95830                   fstp       dword ptr [eax + 0x30]
00c355a5 d9ee                     fldz       
00c355a7 d95834                   fstp       dword ptr [eax + 0x34]
00c355aa d9ee                     fldz       
00c355ac d95838                   fstp       dword ptr [eax + 0x38]
00c355af d9e8                     fld1       
00c355b1 d9583c                   fstp       dword ptr [eax + 0x3c]
00c355b4 c9                       leave      

00511400  55                       push       ebp
00511401  8bec                     mov        ebp, esp
00511403  83ec1c                   sub        esp, 0x1c
00511406  56                       push       esi
00511407  8bf1                     mov        esi, ecx
00511409  8a86e0000000             mov        al, byte ptr [esi + 0xe0]
0051140f  84c0                     test       al, al
00511411  0f8552070000             jne        0x511b69
00511417  53                       push       ebx
00511418  57                       push       edi
00511419  8dbea0000000             lea        edi, [esi + 0xa0]
0051141f  8bcf                     mov        ecx, edi
00511421  e8da5a5f00               call       0xb06f00
00511426  2b86e4000000             sub        eax, dword ptr [esi + 0xe4]
0051142c  8bcf                     mov        ecx, edi
0051142e  8945fc                   mov        dword ptr [ebp - 4], eax
00511431  e8ca5a5f00               call       0xb06f00
00511436  8b8e90000000             mov        ecx, dword ptr [esi + 0x90]
0051143c  85c9                     test       ecx, ecx
0051143e  8986e4000000             mov        dword ptr [esi + 0xe4], eax
00511444  7454                     je         0x51149a
00511446  8b01                     mov        eax, dword ptr [ecx]
00511448  ff9094000000             call       dword ptr [eax + 0x94]
0051144e  038694000000             add        eax, dword ptr [esi + 0x94]
00511454  50                       push       eax
00511455  6a00                     push       0
00511457  8bce                     mov        ecx, esi
00511459  e8f2faffff               call       0x510f50
0051145e  8b8e90000000             mov        ecx, dword ptr [esi + 0x90]
00511464  8b11                     mov        edx, dword ptr [ecx]
00511466  ff9298000000             call       dword ptr [edx + 0x98]
0051146c  038698000000             add        eax, dword ptr [esi + 0x98]
00511472  50                       push       eax
00511473  6a01                     push       1
00511475  8bce                     mov        ecx, esi
00511477  e8d4faffff               call       0x510f50
0051147c  8b8e90000000             mov        ecx, dword ptr [esi + 0x90]
00511482  8b01                     mov        eax, dword ptr [ecx]
00511484  ff909c000000             call       dword ptr [eax + 0x9c]
0051148a  03869c000000             add        eax, dword ptr [esi + 0x9c]
00511490  50                       push       eax
00511491  6a02                     push       2
00511493  8bce                     mov        ecx, esi
00511495  e8b6faffff               call       0x510f50
0051149a  33ff                     xor        edi, edi
0051149c  8d9eec000000             lea        ebx, [esi + 0xec]
005114a2  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
005114a5  51                       push       ecx
005114a6  57                       push       edi
005114a7  8bce                     mov        ecx, esi
005114a9  e832e9ffff               call       0x50fde0
005114ae  8903                     mov        dword ptr [ebx], eax
005114b0  47                       inc        edi
005114b1  83c304                   add        ebx, 4
005114b4  83ff03                   cmp        edi, 3
005114b7  7ce9                     jl         0x5114a2
005114b9  8a8600010000             mov        al, byte ptr [esi + 0x100]
005114bf  84c0                     test       al, al
005114c1  0f8451030000             je         0x511818
005114c7  8b8618010000             mov        eax, dword ptr [esi + 0x118]
005114cd  85c0                     test       eax, eax
005114cf  0f8443030000             je         0x511818
005114d5  8b8638010000             mov        eax, dword ptr [esi + 0x138]
005114db  85c0                     test       eax, eax
005114dd  7e22                     jle        0x511501
005114df  8d8ea0000000             lea        ecx, [esi + 0xa0]
005114e5  e8165a5f00               call       0xb06f00
005114ea  8b963c010000             mov        edx, dword ptr [esi + 0x13c]
005114f0  039638010000             add        edx, dword ptr [esi + 0x138]
005114f6  3bc2                     cmp        eax, edx
005114f8  7e07                     jle        0x511501
005114fa  c6860001000000           mov        byte ptr [esi + 0x100], 0
00511501  8b4674                   mov        eax, dword ptr [esi + 0x74]
00511504  85c0                     test       eax, eax
00511506  0f840c030000             je         0x511818
0051150c  8dbea0000000             lea        edi, [esi + 0xa0]
00511512  8bcf                     mov        ecx, edi
00511514  e8e7595f00               call       0xb06f00
00511519  3b8614010000             cmp        eax, dword ptr [esi + 0x114]
0051151f  0f8efd000000             jle        0x511622
00511525  8bcf                     mov        ecx, edi
00511527  e8d4595f00               call       0xb06f00
0051152c  8b8e10010000             mov        ecx, dword ptr [esi + 0x110]
00511532  8b9618010000             mov        edx, dword ptr [esi + 0x118]
00511538  03c1                     add        eax, ecx
0051153a  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051153d  6a00                     push       0
0051153f  898614010000             mov        dword ptr [esi + 0x114], eax
00511545  8b01                     mov        eax, dword ptr [ecx]
00511547  52                       push       edx
00511548  ff500c                   call       dword ptr [eax + 0xc]
0051154b  e8f4ff6e00               call       0xc01544
00511550  d905a4d7e900             fld        dword ptr [0xe9d7a4]
00511556  0568010000               add        eax, 0x168
0051155b  d98620010000             fld        dword ptr [esi + 0x120]
00511561  99                       cdq        
00511562  dae9                     fucompp    
00511564  b968010000               mov        ecx, 0x168
00511569  f7f9                     idiv       ecx
0051156b  dfe0                     fnstsw     ax
0051156d  f6c444                   test       ah, 0x44
00511570  8955f4                   mov        dword ptr [ebp - 0xc], edx
00511573  7b36                     jnp        0x5115ab
00511575  8b8e18010000             mov        ecx, dword ptr [esi + 0x118]
0051157b  8b11                     mov        edx, dword ptr [ecx]
0051157d  ff9294000000             call       dword ptr [edx + 0x94]
00511583  8b8e18010000             mov        ecx, dword ptr [esi + 0x118]
00511589  8945f4                   mov        dword ptr [ebp - 0xc], eax
0051158c  db45f4                   fild       dword ptr [ebp - 0xc]
0051158f  d99e24010000             fstp       dword ptr [esi + 0x124]
00511595  8b01                     mov        eax, dword ptr [ecx]
00511597  ff9098000000             call       dword ptr [eax + 0x98]
0051159d  8945f4                   mov        dword ptr [ebp - 0xc], eax
005115a0  db45f4                   fild       dword ptr [ebp - 0xc]
005115a3  d99e28010000             fstp       dword ptr [esi + 0x128]
005115a9  eb12                     jmp        0x5115bd
005115ab  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
005115ae  db45f4                   fild       dword ptr [ebp - 0xc]
005115b1  51                       push       ecx
005115b2  51                       push       ecx
005115b3  8bce                     mov        ecx, esi
005115b5  d91c24                   fstp       dword ptr [esp]
005115b8  e853fdffff               call       0x511310
005115bd  8a861c010000             mov        al, byte ptr [esi + 0x11c]
005115c3  84c0                     test       al, al
005115c5  755b                     jne        0x511622
005115c7  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
005115ca  8b11                     mov        edx, dword ptr [ecx]
005115cc  8bbe18010000             mov        edi, dword ptr [esi + 0x118]
005115d2  ff9294000000             call       dword ptr [edx + 0x94]
005115d8  8bd8                     mov        ebx, eax
005115da  8b07                     mov        eax, dword ptr [edi]
005115dc  8bcf                     mov        ecx, edi
005115de  ff9094000000             call       dword ptr [eax + 0x94]
005115e4  3bd8                     cmp        ebx, eax
005115e6  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
005115e9  7d0c                     jge        0x5115f7
005115eb  8b11                     mov        edx, dword ptr [ecx]
005115ed  6a01                     push       1
005115ef  ff92b8000000             call       dword ptr [edx + 0xb8]
005115f5  eb2b                     jmp        0x511622
005115f7  8b01                     mov        eax, dword ptr [ecx]
005115f9  8bbe18010000             mov        edi, dword ptr [esi + 0x118]
005115ff  ff9094000000             call       dword ptr [eax + 0x94]
00511605  8b17                     mov        edx, dword ptr [edi]
00511607  8bcf                     mov        ecx, edi
00511609  8bd8                     mov        ebx, eax
0051160b  ff9294000000             call       dword ptr [edx + 0x94]
00511611  3bd8                     cmp        ebx, eax
00511613  7c0d                     jl         0x511622
00511615  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511618  8b01                     mov        eax, dword ptr [ecx]
0051161a  6a00                     push       0
0051161c  ff90b8000000             call       dword ptr [eax + 0xb8]
00511622  d905a4d7e900             fld        dword ptr [0xe9d7a4]
00511628  d98620010000             fld        dword ptr [esi + 0x120]
0051162e  dae9                     fucompp    
00511630  dfe0                     fnstsw     ax
00511632  f6c444                   test       ah, 0x44
00511635  0f8bdd010000             jnp        0x511818
0051163b  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051163e  d98628010000             fld        dword ptr [esi + 0x128]
00511644  894df0                   mov        dword ptr [ebp - 0x10], ecx
00511647  8bf9                     mov        edi, ecx
00511649  6a00                     push       0
0051164b  e8f4fe6e00               call       0xc01544
00511650  d98624010000             fld        dword ptr [esi + 0x124]
00511656  50                       push       eax
00511657  e8e8fe6e00               call       0xc01544
0051165c  8b17                     mov        edx, dword ptr [edi]
0051165e  50                       push       eax
0051165f  8bcf                     mov        ecx, edi
00511661  ff9298000000             call       dword ptr [edx + 0x98]
00511667  50                       push       eax
00511668  8b07                     mov        eax, dword ptr [edi]
0051166a  8bcf                     mov        ecx, edi
0051166c  ff9094000000             call       dword ptr [eax + 0x94]
00511672  50                       push       eax
00511673  e8a87df8ff               call       0x499420
00511678  83c414                   add        esp, 0x14
0051167b  e8c4fe6e00               call       0xc01544
00511680  d9862c010000             fld        dword ptr [esi + 0x12c]
00511686  0568010000               add        eax, 0x168
0051168b  d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
00511691  99                       cdq        
00511692  b968010000               mov        ecx, 0x168
00511697  f7f9                     idiv       ecx
00511699  dfe0                     fnstsw     ax
0051169b  f6c405                   test       ah, 5
0051169e  8bda                     mov        ebx, edx
005116a0  895df4                   mov        dword ptr [ebp - 0xc], ebx
005116a3  7a3e                     jp         0x5116e3
005116a5  8b3e                     mov        edi, dword ptr [esi]
005116a7  85ff                     test       edi, edi
005116a9  8bcf                     mov        ecx, edi
005116ab  7506                     jne        0x5116b3
005116ad  8d4e08                   lea        ecx, [esi + 8]
005116b0  8d7e08                   lea        edi, [esi + 8]
005116b3  8b11                     mov        edx, dword ptr [ecx]
005116b5  6a00                     push       0
005116b7  6a01                     push       1
005116b9  ff5208                   call       dword ptr [edx + 8]
005116bc  e883fe6e00               call       0xc01544
005116c1  50                       push       eax
005116c2  8b07                     mov        eax, dword ptr [edi]
005116c4  6a00                     push       0
005116c6  8bcf                     mov        ecx, edi
005116c8  ff5008                   call       dword ptr [eax + 8]
005116cb  e874fe6e00               call       0xc01544
005116d0  50                       push       eax
005116d1  6a00                     push       0
005116d3  6a00                     push       0
005116d5  e8467df8ff               call       0x499420
005116da  d99e2c010000             fstp       dword ptr [esi + 0x12c]
005116e0  83c414                   add        esp, 0x14
005116e3  d9862c010000             fld        dword ptr [esi + 0x12c]
005116e9  e856fe6e00               call       0xc01544
005116ee  0568010000               add        eax, 0x168
005116f3  99                       cdq        
005116f4  b968010000               mov        ecx, 0x168
005116f9  f7f9                     idiv       ecx
005116fb  3bda                     cmp        ebx, edx
005116fd  8955f0                   mov        dword ptr [ebp - 0x10], edx
00511700  0f8400010000             je         0x511806
00511706  2bda                     sub        ebx, edx
00511708  8bc3                     mov        eax, ebx
0051170a  3db4000000               cmp        eax, 0xb4
0051170f  8945f8                   mov        dword ptr [ebp - 8], eax
00511712  7e09                     jle        0x51171d
00511714  2bc8                     sub        ecx, eax
00511716  894df8                   mov        dword ptr [ebp - 8], ecx
00511719  f7d9                     neg        ecx
0051171b  eb1e                     jmp        0x51173b
0051171d  85c0                     test       eax, eax
0051171f  7f18                     jg         0x511739
00511721  3d4cffffff               cmp        eax, 0xffffff4c
00511726  7e09                     jle        0x511731
00511728  8bc8                     mov        ecx, eax
0051172a  f7d8                     neg        eax
0051172c  8945f8                   mov        dword ptr [ebp - 8], eax
0051172f  eb0a                     jmp        0x51173b
00511731  0568010000               add        eax, 0x168
00511736  8945f8                   mov        dword ptr [ebp - 8], eax
00511739  8bc8                     mov        ecx, eax
0051173b  db45f8                   fild       dword ptr [ebp - 8]
0051173e  d89634010000             fcom       dword ptr [esi + 0x134]
00511744  dfe0                     fnstsw     ax
00511746  f6c405                   test       ah, 5
00511749  0f8aac000000             jp         0x5117fb
0051174f  db45fc                   fild       dword ptr [ebp - 4]
00511752  d88e20010000             fmul       dword ptr [esi + 0x120]
00511758  d80df811cc00             fmul       dword ptr [0xcc11f8]
0051175e  d95df8                   fstp       dword ptr [ebp - 8]
00511761  d85df8                   fcomp      dword ptr [ebp - 8]
00511764  dfe0                     fnstsw     ax
00511766  f6c405                   test       ah, 5
00511769  0f8b97000000             jnp        0x511806
0051176f  85c9                     test       ecx, ecx
00511771  7e44                     jle        0x5117b7
00511773  d945f8                   fld        dword ptr [ebp - 8]
00511776  d8862c010000             fadd       dword ptr [esi + 0x12c]
0051177c  d8153c69cd00             fcom       dword ptr [0xcd693c]
00511782  d9962c010000             fst        dword ptr [esi + 0x12c]
00511788  dfe0                     fnstsw     ax
0051178a  f6c441                   test       ah, 0x41
0051178d  7519                     jne        0x5117a8
0051178f  d8253c69cd00             fsub       dword ptr [0xcd693c]
00511795  8b45fc                   mov        eax, dword ptr [ebp - 4]
00511798  50                       push       eax
00511799  d99e2c010000             fstp       dword ptr [esi + 0x12c]
0051179f  8b8e2c010000             mov        ecx, dword ptr [esi + 0x12c]
005117a5  51                       push       ecx
005117a6  eb69                     jmp        0x511811
005117a8  8b45fc                   mov        eax, dword ptr [ebp - 4]
005117ab  ddd8                     fstp       st(0)
005117ad  8b8e2c010000             mov        ecx, dword ptr [esi + 0x12c]
005117b3  50                       push       eax
005117b4  51                       push       ecx
005117b5  eb5a                     jmp        0x511811
005117b7  d9862c010000             fld        dword ptr [esi + 0x12c]
005117bd  d865f8                   fsub       dword ptr [ebp - 8]
005117c0  d815a4d7e900             fcom       dword ptr [0xe9d7a4]
005117c6  d9962c010000             fst        dword ptr [esi + 0x12c]
005117cc  dfe0                     fnstsw     ax
005117ce  f6c405                   test       ah, 5
005117d1  7a19                     jp         0x5117ec
005117d3  d8053c69cd00             fadd       dword ptr [0xcd693c]
005117d9  8b55fc                   mov        edx, dword ptr [ebp - 4]
005117dc  52                       push       edx
005117dd  d99e2c010000             fstp       dword ptr [esi + 0x12c]
005117e3  8b862c010000             mov        eax, dword ptr [esi + 0x12c]
005117e9  50                       push       eax
005117ea  eb25                     jmp        0x511811
005117ec  8b55fc                   mov        edx, dword ptr [ebp - 4]
005117ef  ddd8                     fstp       st(0)
005117f1  8b862c010000             mov        eax, dword ptr [esi + 0x12c]
005117f7  52                       push       edx
005117f8  50                       push       eax
005117f9  eb16                     jmp        0x511811
005117fb  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
005117fe  ddd8                     fstp       st(0)
00511800  db45f0                   fild       dword ptr [ebp - 0x10]
00511803  51                       push       ecx
00511804  eb07                     jmp        0x51180d
00511806  8b55fc                   mov        edx, dword ptr [ebp - 4]
00511809  db45f4                   fild       dword ptr [ebp - 0xc]
0051180c  52                       push       edx
0051180d  51                       push       ecx
0051180e  d91c24                   fstp       dword ptr [esp]
00511811  8bce                     mov        ecx, esi
00511813  e8f8faffff               call       0x511310
00511818  8b4678                   mov        eax, dword ptr [esi + 0x78]
0051181b  85c0                     test       eax, eax
0051181d  0f84db020000             je         0x511afe
00511823  8a467c                   mov        al, byte ptr [esi + 0x7c]
00511826  84c0                     test       al, al
00511828  0f84d0020000             je         0x511afe
0051182e  83be8000000002           cmp        dword ptr [esi + 0x80], 2
00511835  7525                     jne        0x51185c
00511837  8a8684000000             mov        al, byte ptr [esi + 0x84]
0051183d  84c0                     test       al, al
0051183f  741b                     je         0x51185c
00511841  8b9688000000             mov        edx, dword ptr [esi + 0x88]
00511847  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051184a  8b01                     mov        eax, dword ptr [ecx]
0051184c  52                       push       edx
0051184d  6a00                     push       0
0051184f  6aff                     push       -1
00511851  ff9074020000             call       dword ptr [eax + 0x274]
00511857  e9a2020000               jmp        0x511afe
0051185c  33ff                     xor        edi, edi
0051185e  8bff                     mov        edi, edi
00511860  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
00511863  85c9                     test       ecx, ecx
00511865  740f                     je         0x511876
00511867  8a467c                   mov        al, byte ptr [esi + 0x7c]
0051186a  84c0                     test       al, al
0051186c  7408                     je         0x511876
0051186e  8b01                     mov        eax, dword ptr [ecx]
00511870  57                       push       edi
00511871  ff5028                   call       dword ptr [eax + 0x28]
00511874  eb1a                     jmp        0x511890
00511876  8b0e                     mov        ecx, dword ptr [esi]
00511878  85c9                     test       ecx, ecx
0051187a  7503                     jne        0x51187f
0051187c  8d4e08                   lea        ecx, [esi + 8]
0051187f  8b11                     mov        edx, dword ptr [ecx]
00511881  57                       push       edi
00511882  ff12                     call       dword ptr [edx]
00511884  51                       push       ecx
00511885  d91c24                   fstp       dword ptr [esp]
00511888  e86367f3ff               call       0x447ff0
0051188d  83c404                   add        esp, 4
00511890  8b0e                     mov        ecx, dword ptr [esi]
00511892  85c9                     test       ecx, ecx
00511894  8944bde4                 mov        dword ptr [ebp + edi*4 - 0x1c], eax
00511898  7503                     jne        0x51189d
0051189a  8d4e08                   lea        ecx, [esi + 8]
0051189d  8b01                     mov        eax, dword ptr [ecx]
0051189f  8b5e78                   mov        ebx, dword ptr [esi + 0x78]
005118a2  57                       push       edi
005118a3  ff10                     call       dword ptr [eax]
005118a5  e89afc6e00               call       0xc01544
005118aa  8b13                     mov        edx, dword ptr [ebx]
005118ac  8bcb                     mov        ecx, ebx
005118ae  8945f0                   mov        dword ptr [ebp - 0x10], eax
005118b1  ff5210                   call       dword ptr [edx + 0x10]
005118b4  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
005118b7  890cb8                   mov        dword ptr [eax + edi*4], ecx
005118ba  47                       inc        edi
005118bb  83ff03                   cmp        edi, 3
005118be  7ca0                     jl         0x511860
005118c0  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
005118c3  8b01                     mov        eax, dword ptr [ecx]
005118c5  ff5008                   call       dword ptr [eax + 8]
005118c8  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
005118cb  85c9                     test       ecx, ecx
005118cd  747b                     je         0x51194a
005118cf  8b11                     mov        edx, dword ptr [ecx]
005118d1  6a01                     push       1
005118d3  ff522c                   call       dword ptr [edx + 0x2c]
005118d6  84c0                     test       al, al
005118d8  7470                     je         0x51194a
005118da  8a8684000000             mov        al, byte ptr [esi + 0x84]
005118e0  84c0                     test       al, al
005118e2  740a                     je         0x5118ee
005118e4  8b8680000000             mov        eax, dword ptr [esi + 0x80]
005118ea  85c0                     test       eax, eax
005118ec  755c                     jne        0x51194a
005118ee  8b4674                   mov        eax, dword ptr [esi + 0x74]
005118f1  8b18                     mov        ebx, dword ptr [eax]
005118f3  8dbe88000000             lea        edi, [esi + 0x88]
005118f9  57                       push       edi
005118fa  8bce                     mov        ecx, esi
005118fc  e82fd5fdff               call       0x4eee30
00511901  50                       push       eax
00511902  8bce                     mov        ecx, esi
00511904  e817d5fdff               call       0x4eee20
00511909  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051190c  50                       push       eax
0051190d  ff93ac000000             call       dword ptr [ebx + 0xac]
00511913  84c0                     test       al, al
00511915  741a                     je         0x511931
00511917  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051191a  8b19                     mov        ebx, dword ptr [ecx]
0051191c  8bce                     mov        ecx, esi
0051191e  e81dd5fdff               call       0x4eee40
00511923  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511926  50                       push       eax
00511927  ff93a8000000             call       dword ptr [ebx + 0xa8]
0051192d  84c0                     test       al, al
0051192f  7519                     jne        0x51194a
00511931  8b07                     mov        eax, dword ptr [edi]
00511933  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511936  8b11                     mov        edx, dword ptr [ecx]
00511938  50                       push       eax
00511939  6a00                     push       0
0051193b  6aff                     push       -1
0051193d  ff9274020000             call       dword ptr [edx + 0x274]
00511943  c6868400000001           mov        byte ptr [esi + 0x84], 1
0051194a  8a8684000000             mov        al, byte ptr [esi + 0x84]
00511950  84c0                     test       al, al
00511952  0f849f010000             je         0x511af7
00511958  83be8000000001           cmp        dword ptr [esi + 0x80], 1
0051195f  0f8592010000             jne        0x511af7
00511965  8a868c000000             mov        al, byte ptr [esi + 0x8c]
0051196b  84c0                     test       al, al
0051196d  0f8584010000             jne        0x511af7
00511973  33ff                     xor        edi, edi
00511975  897df4                   mov        dword ptr [ebp - 0xc], edi
00511978  eb06                     jmp        0x511980
0051197a  8d9b00000000             lea        ebx, [ebx]
00511980  8a843e85000000           mov        al, byte ptr [esi + edi + 0x85]
00511987  84c0                     test       al, al
00511989  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
0051198c  7410                     je         0x51199e
0051198e  8b44bde4                 mov        eax, dword ptr [ebp + edi*4 - 0x1c]
00511992  8b11                     mov        edx, dword ptr [ecx]
00511994  50                       push       eax
00511995  57                       push       edi
00511996  ff5224                   call       dword ptr [edx + 0x24]
00511999  e94c010000               jmp        0x511aea
0051199e  85c9                     test       ecx, ecx
005119a0  740f                     je         0x5119b1
005119a2  8a467c                   mov        al, byte ptr [esi + 0x7c]
005119a5  84c0                     test       al, al
005119a7  7408                     je         0x5119b1
005119a9  8b11                     mov        edx, dword ptr [ecx]
005119ab  57                       push       edi
005119ac  ff5228                   call       dword ptr [edx + 0x28]
005119af  eb1a                     jmp        0x5119cb
005119b1  8b0e                     mov        ecx, dword ptr [esi]
005119b3  85c9                     test       ecx, ecx
005119b5  7503                     jne        0x5119ba
005119b7  8d4e08                   lea        ecx, [esi + 8]
005119ba  8b01                     mov        eax, dword ptr [ecx]
005119bc  57                       push       edi
005119bd  ff10                     call       dword ptr [eax]
005119bf  51                       push       ecx
005119c0  d91c24                   fstp       dword ptr [esp]
005119c3  e82866f3ff               call       0x447ff0
005119c8  83c404                   add        esp, 4
005119cb  3944bde4                 cmp        dword ptr [ebp + edi*4 - 0x1c], eax
005119cf  8945f8                   mov        dword ptr [ebp - 8], eax
005119d2  0f8412010000             je         0x511aea
005119d8  eb06                     jmp        0x5119e0
005119da  8d9b00000000             lea        ebx, [ebx]
005119e0  8b5cbde4                 mov        ebx, dword ptr [ebp + edi*4 - 0x1c]
005119e4  3b5df8                   cmp        ebx, dword ptr [ebp - 8]
005119e7  7d09                     jge        0x5119f2
005119e9  8d4b01                   lea        ecx, [ebx + 1]
005119ec  894cbde4                 mov        dword ptr [ebp + edi*4 - 0x1c], ecx
005119f0  eb07                     jmp        0x5119f9
005119f2  8d53ff                   lea        edx, [ebx - 1]
005119f5  8954bde4                 mov        dword ptr [ebp + edi*4 - 0x1c], edx
005119f9  83ff02                   cmp        edi, 2
005119fc  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
005119ff  754b                     jne        0x511a4c
00511a01  85c9                     test       ecx, ecx
00511a03  741e                     je         0x511a23
00511a05  8a467c                   mov        al, byte ptr [esi + 0x7c]
00511a08  84c0                     test       al, al
00511a0a  7417                     je         0x511a23
00511a0c  8b01                     mov        eax, dword ptr [ecx]
00511a0e  57                       push       edi
00511a0f  ff5028                   call       dword ptr [eax + 0x28]
00511a12  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511a15  8b11                     mov        edx, dword ptr [ecx]
00511a17  50                       push       eax
00511a18  ff92a8000000             call       dword ptr [edx + 0xa8]
00511a1e  e99e000000               jmp        0x511ac1
00511a23  8b0e                     mov        ecx, dword ptr [esi]
00511a25  85c9                     test       ecx, ecx
00511a27  7503                     jne        0x511a2c
00511a29  8d4e08                   lea        ecx, [esi + 8]
00511a2c  8b11                     mov        edx, dword ptr [ecx]
00511a2e  6a02                     push       2
00511a30  ff12                     call       dword ptr [edx]
00511a32  51                       push       ecx
00511a33  d91c24                   fstp       dword ptr [esp]
00511a36  e8b565f3ff               call       0x447ff0
00511a3b  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511a3e  8b11                     mov        edx, dword ptr [ecx]
00511a40  83c404                   add        esp, 4
00511a43  50                       push       eax
00511a44  ff92a8000000             call       dword ptr [edx + 0xa8]
00511a4a  eb75                     jmp        0x511ac1
00511a4c  85c9                     test       ecx, ecx
00511a4e  7410                     je         0x511a60
00511a50  8a467c                   mov        al, byte ptr [esi + 0x7c]
00511a53  84c0                     test       al, al
00511a55  7409                     je         0x511a60
00511a57  8b01                     mov        eax, dword ptr [ecx]
00511a59  6a01                     push       1
00511a5b  ff5028                   call       dword ptr [eax + 0x28]
00511a5e  eb1b                     jmp        0x511a7b
00511a60  8b0e                     mov        ecx, dword ptr [esi]
00511a62  85c9                     test       ecx, ecx
00511a64  7503                     jne        0x511a69
00511a66  8d4e08                   lea        ecx, [esi + 8]
00511a69  8b11                     mov        edx, dword ptr [ecx]
00511a6b  6a01                     push       1
00511a6d  ff12                     call       dword ptr [edx]
00511a6f  51                       push       ecx
00511a70  d91c24                   fstp       dword ptr [esp]
00511a73  e87865f3ff               call       0x447ff0
00511a78  83c404                   add        esp, 4
00511a7b  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
00511a7e  85c9                     test       ecx, ecx
00511a80  8bf8                     mov        edi, eax
00511a82  7410                     je         0x511a94
00511a84  8a467c                   mov        al, byte ptr [esi + 0x7c]
00511a87  84c0                     test       al, al
00511a89  7409                     je         0x511a94
00511a8b  8b01                     mov        eax, dword ptr [ecx]
00511a8d  6a00                     push       0
00511a8f  ff5028                   call       dword ptr [eax + 0x28]
00511a92  eb1b                     jmp        0x511aaf
00511a94  8b0e                     mov        ecx, dword ptr [esi]
00511a96  85c9                     test       ecx, ecx
00511a98  7503                     jne        0x511a9d
00511a9a  8d4e08                   lea        ecx, [esi + 8]
00511a9d  8b11                     mov        edx, dword ptr [ecx]
00511a9f  6a00                     push       0
00511aa1  ff12                     call       dword ptr [edx]
00511aa3  51                       push       ecx
00511aa4  d91c24                   fstp       dword ptr [esp]
00511aa7  e84465f3ff               call       0x447ff0
00511aac  83c404                   add        esp, 4
00511aaf  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511ab2  8b11                     mov        edx, dword ptr [ecx]
00511ab4  6a00                     push       0
00511ab6  57                       push       edi
00511ab7  50                       push       eax
00511ab8  ff92ac000000             call       dword ptr [edx + 0xac]
00511abe  8b7df4                   mov        edi, dword ptr [ebp - 0xc]
00511ac1  84c0                     test       al, al
00511ac3  740f                     je         0x511ad4
00511ac5  8b45f8                   mov        eax, dword ptr [ebp - 8]
00511ac8  3944bde4                 cmp        dword ptr [ebp + edi*4 - 0x1c], eax
00511acc  0f850effffff             jne        0x5119e0
00511ad2  eb16                     jmp        0x511aea
00511ad4  8b4e78                   mov        ecx, dword ptr [esi + 0x78]
00511ad7  8b11                     mov        edx, dword ptr [ecx]
00511ad9  53                       push       ebx
00511ada  57                       push       edi
00511adb  ff5224                   call       dword ptr [edx + 0x24]
00511ade  895cbde4                 mov        dword ptr [ebp + edi*4 - 0x1c], ebx
00511ae2  c6843e8500000001         mov        byte ptr [esi + edi + 0x85], 1
00511aea  47                       inc        edi
00511aeb  83ff03                   cmp        edi, 3
00511aee  897df4                   mov        dword ptr [ebp - 0xc], edi
00511af1  0f8c89feffff             jl         0x511980
00511af7  c6868c00000000           mov        byte ptr [esi + 0x8c], 0
00511afe  8b0dc05a0101             mov        ecx, dword ptr [0x1015ac0]
00511b04  e8170f0000               call       0x512a20
00511b09  8b86fc000000             mov        eax, dword ptr [esi + 0xfc]
00511b0f  85c0                     test       eax, eax
00511b11  7454                     je         0x511b67
00511b13  83f8ff                   cmp        eax, -1
00511b16  8b3d7cbef500             mov        edi, dword ptr [0xf5be7c]
00511b1c  7402                     je         0x511b20
00511b1e  8bf8                     mov        edi, eax
00511b20  8d9ea0000000             lea        ebx, [esi + 0xa0]
00511b26  8bcb                     mov        ecx, ebx
00511b28  e8d3535f00               call       0xb06f00
00511b2d  8b8ee8000000             mov        ecx, dword ptr [esi + 0xe8]
00511b33  03cf                     add        ecx, edi
00511b35  3bc1                     cmp        eax, ecx
00511b37  722e                     jb         0x511b67
00511b39  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
00511b3f  85c9                     test       ecx, ecx
00511b41  7424                     je         0x511b67
00511b43  8b11                     mov        edx, dword ptr [ecx]
00511b45  ff5248                   call       dword ptr [edx + 0x48]
00511b48  3bf0                     cmp        esi, eax
00511b4a  751b                     jne        0x511b67
00511b4c  8b0e                     mov        ecx, dword ptr [esi]
00511b4e  85c9                     test       ecx, ecx
00511b50  7503                     jne        0x511b55
00511b52  8d4e08                   lea        ecx, [esi + 8]
00511b55  8b01                     mov        eax, dword ptr [ecx]
00511b57  ff5010                   call       dword ptr [eax + 0x10]
00511b5a  8bcb                     mov        ecx, ebx
00511b5c  e89f535f00               call       0xb06f00
00511b61  8986e8000000             mov        dword ptr [esi + 0xe8], eax
00511b67  5f                       pop        edi
00511b68  5b                       pop        ebx
00511b69  5e                       pop        esi
00511b6a  8be5                     mov        esp, ebp
00511b6c  5d                       pop        ebp
00511b6d  c3                       ret        
00511b6e  cc                       int3       
00511b6f  cc                       int3       
00511b70  55                       push       ebp
00511b71  8bec                     mov        ebp, esp
00511b73  83ec50                   sub        esp, 0x50
00511b76  56                       push       esi
00511b77  8bf1                     mov        esi, ecx
00511b79  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511b7c  85c9                     test       ecx, ecx
00511b7e  0f84a2010000             je         0x511d26
00511b84  e807a5f8ff               call       0x49c090
00511b89  84c0                     test       al, al
00511b8b  0f8495010000             je         0x511d26
00511b91  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511b94  8b01                     mov        eax, dword ptr [ecx]
00511b96  ff505c                   call       dword ptr [eax + 0x5c]
00511b99  85c0                     test       eax, eax
00511b9b  0f8485010000             je         0x511d26
00511ba1  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
00511ba4  8b11                     mov        edx, dword ptr [ecx]
00511ba6  ff525c                   call       dword ptr [edx + 0x5c]
00511ba9  8b8814010000             mov        ecx, dword ptr [eax + 0x114]
00511baf  85                       .byte      0x85

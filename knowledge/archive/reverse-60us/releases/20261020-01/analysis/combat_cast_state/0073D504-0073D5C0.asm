0073d504  dc18                     fcomp      qword ptr [eax]
0073d506  7300                     jae        0x73d508
0073d508  68a1730068               push       0x680073a1
0073d50d  a1730068a1               mov        eax, dword ptr [0xa1680073]
0073d512  7300                     jae        0x73d514
0073d514  68a1730068               push       0x680073a1
0073d519  a1730068a1               mov        eax, dword ptr [0xa1680073]
0073d51e  7300                     jae        0x73d520
0073d520  68a1730068               push       0x680073a1
0073d525  a1730068a1               mov        eax, dword ptr [0xa1680073]
0073d52a  7300                     jae        0x73d52c
0073d52c  68a1730089               push       0x890073a1
0073d531  197300                   sbb        dword ptr [ebx], esi
0073d534  0c1f                     or         al, 0x1f
0073d536  7300                     jae        0x73d538
0073d538  8528                     test       dword ptr [eax], ebp
0073d53a  7300                     jae        0x73d53c
0073d53c  cf                       iretd      
0073d53d  297300                   sub        dword ptr [ebx], esi
0073d540  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
0073d541  2e7300                   jae        0x73d544
0073d544  d534                     aad        0x34
0073d546  7300                     jae        0x73d548
0073d548  4c                       dec        esp
0073d549  397300                   cmp        dword ptr [ebx], esi
0073d54c  d83b                     fdivr      dword ptr [ebx]
0073d54e  7300                     jae        0x73d550
0073d550  1b7573                   sbb        esi, dword ptr [ebp + 0x73]
0073d553  0068a1                   add        byte ptr [eax - 0x5f], ch
0073d556  7300                     jae        0x73d558
0073d558  86847300d28773           xchg       byte ptr [ebx + esi*2 + 0x7387d200], al
0073d55f  00e6                     add        dh, ah
0073d561  3e7300                   jae        0x73d564
0073d564  624e73                   bound      ecx, qword ptr [esi + 0x73]
0073d567  00ad42730063             add        byte ptr [ebp + 0x63007342], ch
0073d56d  48                       dec        eax
0073d56e  7300                     jae        0x73d570
0073d570  4e                       dec        esi
0073d571  53                       push       ebx
0073d572  7300                     jae        0x73d574
0073d574  1c59                     sbb        al, 0x59
0073d576  7300                     jae        0x73d578
0073d578  cb                       retf       
0073d579  7873                     js         0x73d5ee
0073d57b  00b889730040             add        byte ptr [eax + 0x40007389], bh
0073d581  5d                       pop        ebp
0073d582  7300                     jae        0x73d584
0073d584  66677300                 jae        0x73d588
0073d588  91                       xchg       ecx, eax
0073d589  7473                     je         0x73d5fe
0073d58b  0005807300b4             add        byte ptr [0xb4007380], al
0073d591  6973002d6f7300           imul       esi, dword ptr [ebx], 0x736f2d
0073d598  315573                   xor        dword ptr [ebp + 0x73], edx
0073d59b  00778b                   add        byte ptr [edi - 0x75], dh
0073d59e  7300                     jae        0x73d5a0
0073d5a0  8b8d7300ba8f             mov        ecx, dword ptr [ebp - 0x7045ff8d]
0073d5a6  7300                     jae        0x73d5a8
0073d5a8  55                       push       ebp
0073d5a9  94                       xchg       esp, eax
0073d5aa  7300                     jae        0x73d5ac
0073d5ac  e698                     out        0x98, al
0073d5ae  7300                     jae        0x73d5b0
0073d5b0  c19b7300a89e73           rcr        dword ptr [ebx - 0x6157ff8d], 0x73
0073d5b7  0027                     add        byte ptr [edi], ah
0073d5b9  9f                       lahf       
0073d5ba  7300                     jae        0x73d5bc
0073d5bc  d9                       .byte      0xd9
0073d5bd  a0                       .byte      0xa0
0073d5be  7300                     jae        0x73d5c0
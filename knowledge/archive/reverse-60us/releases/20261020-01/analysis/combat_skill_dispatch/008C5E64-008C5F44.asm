008c5e64  06                       push       es
008c5e65  1c8c                     sbb        al, 0x8c
008c5e67  00505e                   add        byte ptr [eax + 0x5e], dl
008c5e6a  8c00                     mov        word ptr [eax], es
008c5e6c  0e                       push       cs
008c5e6d  1f                       pop        ds
008c5e6e  8c00                     mov        word ptr [eax], es
008c5e70  ee                       out        dx, al
008c5e71  1f                       pop        ds
008c5e72  8c00                     mov        word ptr [eax], es
008c5e74  3920                     cmp        dword ptr [eax], esp
008c5e76  8c00                     mov        word ptr [eax], es
008c5e78  6221                     bound      esp, qword ptr [ecx]
008c5e7a  8c00                     mov        word ptr [eax], es
008c5e7c  22248c                   and        ah, byte ptr [esp + ecx*4]
008c5e7f  00bc268c00e129           add        byte ptr [esi + 0x29e1008c], bh
008c5e86  8c00                     mov        word ptr [eax], es
008c5e88  d92a                     fldcw      word ptr [edx]
008c5e8a  8c00                     mov        word ptr [eax], es
008c5e8c  342c                     xor        al, 0x2c
008c5e8e  8c00                     mov        word ptr [eax], es
008c5e90  a4                       movsb      byte ptr es:[edi], byte ptr [esi]
008c5e91  308c00a5318c00           xor        byte ptr [eax + eax + 0x8c31a5], cl
008c5e98  4b                       dec        ebx
008c5e99  328c00e2328c00           xor        cl, byte ptr [eax + eax + 0x8c32e2]
008c5ea0  26358c005837             xor        eax, 0x3758008c
008c5ea6  8c00                     mov        word ptr [eax], es
008c5ea8  fa                       cli        
008c5ea9  37                       aaa        
008c5eaa  8c00                     mov        word ptr [eax], es
008c5eac  a0388c00b0               mov        al, byte ptr [0xb0008c38]
008c5eb1  398c00b83d8c00           cmp        dword ptr [eax + eax + 0x8c3db8], ecx
008c5eb8  48                       dec        eax
008c5eb9  42                       inc        edx
008c5eba  8c00                     mov        word ptr [eax], es
008c5ebc  7149                     jno        0x8c5f07
008c5ebe  8c00                     mov        word ptr [eax], es
008c5ec0  734d                     jae        0x8c5f0f
008c5ec2  8c00                     mov        word ptr [eax], es
008c5ec4  694e8c00514f8c           imul       ecx, dword ptr [esi - 0x74], 0x8c4f5100
008c5ecb  00a5508c004f             add        byte ptr [ebp + 0x4f008c50], ah
008c5ed1  51                       push       ecx
008c5ed2  8c00                     mov        word ptr [eax], es
008c5ed4  43                       inc        ebx
008c5ed5  52                       push       edx
008c5ed6  8c00                     mov        word ptr [eax], es
008c5ed8  dd27                     frstor     dword ptr [edi]
008c5eda  8c00                     mov        word ptr [eax], es
008c5edc  12538c                   adc        dl, byte ptr [ebx - 0x74]
008c5edf  0006                     add        byte ptr [esi], al
008c5ee1  54                       push       esp
008c5ee2  8c00                     mov        word ptr [eax], es
008c5ee4  ff258c00a854             jmp        dword ptr [0x54a8008c]
008c5eea  8c00                     mov        word ptr [eax], es
008c5eec  33558c                   xor        edx, dword ptr [ebp - 0x74]
008c5eef  006955                   add        byte ptr [ecx + 0x55], ch
008c5ef2  8c00                     mov        word ptr [eax], es
008c5ef4  87558c                   xchg       dword ptr [ebp - 0x74], edx
008c5ef7  00bf558c00a6             add        byte ptr [edi - 0x59ff73ab], bh
008c5efd  58                       pop        eax
008c5efe  8c00                     mov        word ptr [eax], es
008c5f00  df1a                     fistp      word ptr [edx]
008c5f02  8c00                     mov        word ptr [eax], es
008c5f04  131b                     adc        ebx, dword ptr [ebx]
008c5f06  8c00                     mov        word ptr [eax], es
008c5f08  321b                     xor        bl, byte ptr [ebx]
008c5f0a  8c00                     mov        word ptr [eax], es
008c5f0c  671b8c0086               sbb        ecx, dword ptr [si - 0x7a00]
008c5f11  1b8c00c41b8c00           sbb        ecx, dword ptr [eax + eax + 0x8c1bc4]
008c5f18  c9                       leave      
008c5f19  56                       push       esi
008c5f1a  8c00                     mov        word ptr [eax], es
008c5f1c  0e                       push       cs
008c5f1d  46                       inc        esi
008c5f1e  8c00                     mov        word ptr [eax], es
008c5f20  2b598c                   sub        ebx, dword ptr [ecx - 0x74]
008c5f23  006129                   add        byte ptr [ecx + 0x29], ah
008c5f26  8c00                     mov        word ptr [eax], es
008c5f28  f75a8c                   neg        dword ptr [edx - 0x74]
008c5f2b  00ea                     add        dl, ch
008c5f2d  5b                       pop        ebx
008c5f2e  8c00                     mov        word ptr [eax], es
008c5f30  96                       xchg       esi, eax
008c5f31  5c                       pop        esp
008c5f32  8c00                     mov        word ptr [eax], es
008c5f34  3f                       aas        
008c5f35  27                       daa        
008c5f36  8c00                     mov        word ptr [eax], es
008c5f38  60                       pushal     
008c5f39  288c00cb288c00           sub        byte ptr [eax + eax + 0x8c28cb], cl
008c5f40  fa                       cli        
008c5f41  5d                       pop        ebp
008c5f42  8c00                     mov        word ptr [eax], es
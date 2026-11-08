00d057d4  d0e7                     shl        bh, 1
00d057d6  5c                       pop        esp
00d057d7  00e0                     add        al, ah
00d057d9  025700                   add        dl, byte ptr [edi]
00d057dc  107d40                   adc        byte ptr [ebp + 0x40], bh
00d057df  00607d                   add        byte ptr [eax + 0x7d], ah
00d057e2  40                       inc        eax
00d057e3  0010                     add        byte ptr [eax], dl
00d057e5  f0                       .byte      0xf0
00d057e6  49                       dec        ecx
00d057e7  0090ea4900d0             add        byte ptr [eax - 0x2fffb616], dl
00d057ed  a1490080a6               mov        eax, dword ptr [0xa6800049]
00d057f2  49                       dec        ecx
00d057f3  0080be490060             add        byte ptr [eax + 0x600049be], al
00d057f9  80400050                 add        byte ptr [eax], 0x50
00d057fd  7b40                     jnp        0xd0583f
00d057ff  00f0                     add        al, dh
00d05801  8f                       .byte      0x8f
00d05802  49                       dec        ecx
00d05803  00607b                   add        byte ptr [eax + 0x7b], ah
00d05806  40                       inc        eax
00d05807  00b0498e00b0             add        byte ptr [eax - 0x4fff71b7], dh
00d0580d  49                       dec        ecx
00d0580e  8e00                     mov        es, word ptr [eax]
00d05810  707b                     jo         0xd0588d
00d05812  40                       inc        eax
00d05813  00f0                     add        al, dh
00d05815  7f40                     jg         0xd05857
00d05817  0000                     add        byte ptr [eax], al
00d05819  80400080                 add        byte ptr [eax], 0x80
00d0581d  7b40                     jnp        0xd0585f
00d0581f  0010                     add        byte ptr [eax], dl
00d05821  ac                       lodsb      al, byte ptr [esi]
00d05822  49                       dec        ecx
00d05823  007093                   add        byte ptr [eax - 0x6d], dh
00d05826  49                       dec        ecx
00d05827  00e0                     add        al, ah
00d05829  aa                       stosb      byte ptr es:[edi], al
00d0582a  49                       dec        ecx
00d0582b  00907b4000a0             add        byte ptr [eax - 0x5fffbf85], dl
00d05831  7b40                     jnp        0xd05873
00d05833  00e0                     add        al, ah
00d05835  145e                     adc        al, 0x5e
00d05837  00b07b4000b0             add        byte ptr [eax - 0x4fffbf85], dh
00d0583d  9e                       sahf       
00d0583e  49                       dec        ecx
00d0583f  00c0                     add        al, al
00d05841  7b40                     jnp        0xd05883
00d05843  00f0                     add        al, dh
00d05845  7b40                     jnp        0xd05887
00d05847  0020                     add        byte ptr [eax], ah
00d05849  7c40                     jl         0xd0588b
00d0584b  009080400020             add        byte ptr [eax + 0x20004080], dl
00d05851  80400010                 add        byte ptr [eax], 0x10
00d05855  90                       nop        
00d05856  49                       dec        ecx
00d05857  009090490050             add        byte ptr [eax + 0x50004990], dl
00d0585d  90                       nop        
00d0585e  49                       dec        ecx
00d0585f  00a0904900b0             add        byte ptr [eax - 0x4fffb670], ah
00d05865  90                       nop        
00d05866  49                       dec        ecx
00d05867  0030                     add        byte ptr [eax], dh
00d05869  7c40                     jl         0xd058ab
00d0586b  00407c                   add        byte ptr [eax + 0x7c], al
00d0586e  40                       inc        eax
00d0586f  00507c                   add        byte ptr [eax + 0x7c], dl
00d05872  40                       inc        eax
00d05873  00607c                   add        byte ptr [eax + 0x7c], ah
00d05876  40                       inc        eax
00d05877  00807c4000b0             add        byte ptr [eax - 0x4fffbf84], al
00d0587d  864300                   xchg       byte ptr [ebx], al
00d05880  d07d4e                   sar        byte ptr [ebp + 0x4e], 1
00d05883  00f0                     add        al, dh
00d05885  94                       xchg       esp, eax
00d05886  49                       dec        ecx
00d05887  00c0                     add        al, al
00d05889  9a4900c0904900           lcall      0x49, 0x90c00049
00d05890  e090                     loopne     0xd05822
00d05892  49                       dec        ecx
00d05893  0000                     add        byte ptr [eax], al
00d05895  91                       xchg       ecx, eax
00d05896  49                       dec        ecx
00d05897  00b07c4000e0             add        byte ptr [eax - 0x1fffbf84], dh
00d0589d  7c40                     jl         0xd058df
00d0589f  008094490010             add        byte ptr [eax + 0x10004994], al
00d058a5  9c                       pushfd     
00d058a6  49                       dec        ecx
00d058a7  00b07d400010             add        byte ptr [eax + 0x1000407d], dh
00d058ad  7e40                     jle        0xd058ef
00d058af  0010                     add        byte ptr [eax], dl
00d058b1  9d                       popfd      
00d058b2  49                       dec        ecx
00d058b3  00609d                   add        byte ptr [eax - 0x63], ah
00d058b6  49                       dec        ecx
00d058b7  00707e                   add        byte ptr [eax + 0x7e], dh
00d058ba  40                       inc        eax
00d058bb  00807e4000f0             add        byte ptr [eax - 0xfffbf82], al
00d058c1  9d                       popfd      
00d058c2  49                       dec        ecx
00d058c3  0070d0                   add        byte ptr [eax - 0x30], dh
00d058c6  49                       dec        ecx
00d058c7  00f0                     add        al, dh
00d058c9  9e                       sahf       
00d058ca  49                       dec        ecx
00d058cb  00b0b74900a0             add        byte ptr [eax - 0x5fffb649], dh
00d058d1  ab                       stosd      dword ptr es:[edi], eax
00d058d2  49                       dec        ecx
00d058d3  0080944e0090             add        byte ptr [eax - 0x6fffb16c], al
00d058d9  7e40                     jle        0xd0591b
00d058db  00a07e4000b0             add        byte ptr [eax - 0x4fffbf82], ah
00d058e1  92                       xchg       edx, eax
00d058e2  49                       dec        ecx
00d058e3  0010                     add        byte ptr [eax], dl
00d058e5  93                       xchg       ebx, eax
00d058e6  49                       dec        ecx
00d058e7  00f0                     add        al, dh
00d058e9  fb                       sti        
00d058ea  41                       inc        ecx
00d058eb  00b07e400070             add        byte ptr [eax + 0x7000407e], dh
00d058f1  b349                     mov        bl, 0x49
00d058f3  00c0                     add        al, al
00d058f5  7e40                     jle        0xd05937
00d058f7  00d0                     add        al, dl
00d058f9  7e40                     jle        0xd0593b
00d058fb  00e0                     add        al, ah
00d058fd  7e40                     jle        0xd0593f
00d058ff  0000                     add        byte ptr [eax], al
00d05901  7f40                     jg         0xd05943
00d05903  0010                     add        byte ptr [eax], dl
00d05905  7f40                     jg         0xd05947
00d05907  00b091490030             add        byte ptr [eax + 0x30004991], dh
00d0590d  7f40                     jg         0xd0594f
00d0590f  00407f                   add        byte ptr [eax + 0x7f], al
00d05912  40                       inc        eax
00d05913  0010                     add        byte ptr [eax], dl
00d05915  92                       xchg       edx, eax
00d05916  49                       dec        ecx
00d05917  00c0                     add        al, al
00d05919  7f40                     jg         0xd0595b
00d0591b  00507f                   add        byte ptr [eax + 0x7f], dl
00d0591e  40                       inc        eax
00d0591f  00607f                   add        byte ptr [eax + 0x7f], ah
00d05922  40                       inc        eax
00d05923  00907f4000a0             add        byte ptr [eax - 0x5fffbf81], dl
00d05929  7f40                     jg         0xd0596b
00d0592b  0030                     add        byte ptr [eax], dh
00d0592d  93                       xchg       ebx, eax
00d0592e  49                       dec        ecx
00d0592f  004008                   add        byte ptr [eax + 8], al
00d05932  4a                       dec        edx
00d05933  0020                     add        byte ptr [eax], ah
00d05935  cb                       retf       
00d05936  49                       dec        ecx
00d05937  0040e8                   add        byte ptr [eax - 0x18], al
00d0593a  49                       dec        ecx
00d0593b  00b07f400070             add        byte ptr [eax + 0x7000407f], dh
00d05941  cf                       iretd      
00d05942  49                       dec        ecx
00d05943  00e0                     add        al, ah
00d05945  9d                       popfd      
00d05946  49                       dec        ecx
00d05947  00c0                     add        al, al
00d05949  dcae0020d149             fsubr      qword ptr [esi + 0x49d12000]
00d0594f  00a0d1490000             add        byte ptr [eax + 0x49d1], ah
00d05955  b249                     mov        dl, 0x49
00d05957  00d0                     add        al, dl
00d05959  8f                       .byte      0x8f
00d0595a  49                       dec        ecx
00d0595b  00a0e75c0080             add        byte ptr [eax - 0x7fffa319], ah
00d05961  90                       nop        
00d05962  43                       inc        ebx
00d05963  0020                     add        byte ptr [eax], ah
00d05965  894300                   mov        dword ptr [ebx], eax
00d05968  40                       inc        eax
00d05969  864300                   xchg       byte ptr [ebx], al
00d0596c  d0dc                     rcr        ah, 1
00d0596e  4e                       dec        esi
00d0596f  005086                   add        byte ptr [eax - 0x7a], dl
00d05972  43                       inc        ebx
00d05973  009089430020             add        byte ptr [eax + 0x20004389], dl
00d05979  de4e00                   fimul      word ptr [esi]
00d0597c  50                       push       eax
00d0597d  ce                       into       
00d0597e  4e                       dec        esi
00d0597f  006086                   add        byte ptr [eax - 0x7a], ah
00d05982  43                       inc        ebx
00d05983  00d0                     add        al, dl
00d05985  894e00                   mov        dword ptr [esi], ecx
00d05988  d0874e007086             rol        byte ptr [edi - 0x798fffb2], 1
00d0598e  43                       inc        ebx
00d0598f  009090430080             add        byte ptr [eax - 0x7fffbc70], dl
00d05995  864300                   xchg       byte ptr [ebx], al
00d05998  90                       nop        
00d05999  864300                   xchg       byte ptr [ebx], al
00d0599c  90                       nop        
00d0599d  3b5500                   cmp        edx, dword ptr [ebp]
00d059a0  e088                     loopne     0xd0592a
00d059a2  43                       inc        ebx
00d059a3  00c0                     add        al, al
00d059a5  90                       nop        
00d059a6  43                       inc        ebx
00d059a7  00d0                     add        al, dl
00d059a9  90                       nop        
00d059aa  43                       inc        ebx
00d059ab  00e0                     add        al, ah
00d059ad  90                       nop        
00d059ae  43                       inc        ebx
00d059af  00f0                     add        al, dh
00d059b1  90                       nop        
00d059b2  43                       inc        ebx
00d059b3  0000                     add        byte ptr [eax], al
00d059b5  91                       xchg       ecx, eax
00d059b6  43                       inc        ebx
00d059b7  0010                     add        byte ptr [eax], dl
00d059b9  91                       xchg       ecx, eax
00d059ba  43                       inc        ebx
00d059bb  0020                     add        byte ptr [eax], ah
00d059bd  91                       xchg       ecx, eax
00d059be  43                       inc        ebx
00d059bf  0030                     add        byte ptr [eax], dh
00d059c1  91                       xchg       ecx, eax
00d059c2  43                       inc        ebx
00d059c3  004091                   add        byte ptr [eax - 0x6f], al
00d059c6  43                       inc        ebx
00d059c7  00e0                     add        al, ah
00d059c9  94                       xchg       esp, eax
00d059ca  4e                       dec        esi
00d059cb  00a0864300f0             add        byte ptr [eax - 0xfffbc7a], ah
00d059d1  874300                   xchg       dword ptr [ebx], eax
00d059d4  00884300d086             add        byte ptr [eax - 0x792fffbd], cl
00d059da  43                       inc        ebx
00d059db  00d0                     add        al, dl
00d059dd  864300                   xchg       byte ptr [ebx], al
00d059e0  108843004088             adc        byte ptr [eax - 0x77bfffbd], cl
00d059e6  43                       inc        ebx
00d059e7  006088                   add        byte ptr [eax - 0x78], ah
00d059ea  43                       inc        ebx
00d059eb  009088430010             add        byte ptr [eax + 0x10004388], dl
00d059f1  d7                       xlatb      
00d059f2  4e                       dec        esi
00d059f3  0090ca4e0030             add        byte ptr [eax + 0x30004eca], dl
00d059f9  d04900                   ror        byte ptr [ecx], 1
00d059fc  60                       pushal     
00d059fd  d04900                   ror        byte ptr [ecx], 1
00d05a00  d0d7                     rcl        bh, 1
00d05a02  49                       dec        ecx
00d05a03  005091                   add        byte ptr [eax - 0x6f], dl
00d05a06  43                       inc        ebx
00d05a07  00e0                     add        al, ah
00d05a09  91                       xchg       ecx, eax
00d05a0a  43                       inc        ebx
00d05a0b  0000                     add        byte ptr [eax], al
00d05a0d  92                       xchg       edx, eax
00d05a0e  43                       inc        ebx
00d05a0f  0070df                   add        byte ptr [eax - 0x21], dh
00d05a12  4e                       dec        esi
00d05a13  0070b3                   add        byte ptr [eax - 0x4d], dh
00d05a16  4e                       dec        esi
00d05a17  0000                     add        byte ptr [eax], al
00d05a19  b64e                     mov        dh, 0x4e
00d05a1b  00d0                     add        al, dl
00d05a1d  814e0060824e00           or         dword ptr [esi], 0x4e8260
00d05a24  30d2                     xor        dl, dl
00d05a26  a4                       movsb      byte ptr es:[edi], byte ptr [esi]
00d05a27  0010                     add        byte ptr [eax], dl
00d05a29  d6                       salc       
00d05a2a  49                       dec        ecx
00d05a2b  0030                     add        byte ptr [eax], dh
00d05a2d  d2a40030d2a400           shl        byte ptr [eax + eax + 0xa4d230], cl
00d05a34  10f3                     adc        bl, dh
00d05a36  49                       dec        ecx
00d05a37  00c0                     add        al, al
00d05a39  8e4e00                   mov        cs, word ptr [esi]
00d05a3c  20ab4e0080e1             and        byte ptr [ebx - 0x1e7fffb2], ch
00d05a42  4e                       dec        esi
00d05a43  00803b910000             add        byte ptr [eax + 0x913b], al
00d05a49  e149                     loope      0xd05a94
00d05a4b  00e0                     add        al, ah
00d05a4d  025700                   add        dl, byte ptr [edi]
00d05a50  e09d                     loopne     0xd059ef
00d05a52  4e                       dec        esi
00d05a53  00e0                     add        al, ah
00d05a55  025700                   add        dl, byte ptr [edi]
00d05a58  e002                     loopne     0xd05a5c
00d05a5a  57                       push       edi
00d05a5b  00f0                     add        al, dh
00d05a5d  864300                   xchg       byte ptr [ebx], al
00d05a60  d0d1                     rcl        cl, 1
00d05a62  4e                       dec        esi
00d05a63  00c0                     add        al, al
00d05a65  da4e00                   fimul      dword ptr [esi]
00d05a68  008743001087             add        byte ptr [edi - 0x78efffbd], al
00d05a6e  43                       inc        ebx
00d05a6f  00c0                     add        al, al
00d05a71  6e                       outsb      dx, byte ptr [esi]
00d05a72  8d00                     lea        eax, [eax]
00d05a74  60                       pushal     
00d05a75  91                       xchg       ecx, eax
00d05a76  43                       inc        ebx
00d05a77  0090914300c0             add        byte ptr [eax - 0x3fffbc6f], dl
00d05a7d  91                       xchg       ecx, eax
00d05a7e  43                       inc        ebx
00d05a7f  00a0d04900b0             add        byte ptr [eax - 0x4fffb630], ah
00d05a85  844e00                   test       byte ptr [esi], cl
00d05a88  60                       pushal     
00d05a89  b24e                     mov        dl, 0x4e
00d05a8b  00d0                     add        al, dl
00d05a8d  a4                       movsb      byte ptr es:[edi], byte ptr [esi]
00d05a8e  4e                       dec        esi
00d05a8f  0020                     add        byte ptr [eax], ah
00d05a91  a6                       cmpsb      byte ptr [esi], byte ptr es:[edi]
00d05a92  4e                       dec        esi
00d05a93  00808a4e0090             add        byte ptr [eax - 0x6fffb176], al
00d05a99  7f4e                     jg         0xd05ae9
00d05a9b  0050a7                   add        byte ptr [eax - 0x59], dl
00d05a9e  4e                       dec        esi
00d05a9f  0010                     add        byte ptr [eax], dl
00d05aa1  804e0020                 or         byte ptr [esi], 0x20
00d05aa5  874300                   xchg       dword ptr [ebx], eax
00d05aa8  308743004087             xor        byte ptr [edi - 0x78bfffbd], al
00d05aae  43                       inc        ebx
00d05aaf  005087                   add        byte ptr [eax - 0x79], dl
00d05ab2  43                       inc        ebx
00d05ab3  00e0                     add        al, ah
00d05ab5  91                       xchg       ecx, eax
00d05ab6  4e                       dec        esi
00d05ab7  00b0884300d0             add        byte ptr [eax - 0x2fffbc78], dh
00d05abd  884300                   mov        byte ptr [ebx], al
00d05ac0  b092                     mov        al, 0x92
00d05ac2  4e                       dec        esi
00d05ac3  0020                     add        byte ptr [eax], ah
00d05ac5  094900                   or         dword ptr [ecx], ecx
00d05ac8  60                       pushal     
00d05ac9  874300                   xchg       dword ptr [ebx], eax
00d05acc  80b74e00708743           xor        byte ptr [edi - 0x788fffb2], 0x43
00d05ad3  00a0874300b0             add        byte ptr [eax - 0x4fffbc79], ah
00d05ad9  874300                   xchg       dword ptr [ebx], eax
00d05adc  00cb                     add        bl, cl
00d05ade  4e                       dec        esi
00d05adf  00d0                     add        al, dl
00d05ae1  e24e                     loop       0xd05b31
00d05ae3  00c0                     add        al, al
00d05ae5  874300                   xchg       dword ptr [ebx], eax
00d05ae8  e087                     loopne     0xd05a71
00d05aea  43                       inc        ebx
00d05aeb  0000                     add        byte ptr [eax], al
00d05aed  854e00                   test       dword ptr [esi], ecx
00d05af0  b049                     mov        al, 0x49
00d05af2  5d                       pop        ebp
00d05af3  0000                     add        byte ptr [eax], al
00d05af5  b04e                     mov        al, 0x4e
00d05af7  00803b910020             add        byte ptr [eax + 0x2000913b], al
00d05afd  8a4e00                   mov        cl, byte ptr [esi]
00d05b00  b089                     mov        al, 0x89
00d05b02  4e                       dec        esi
00d05b03  00c0                     add        al, al
00d05b05  894e00                   mov        dword ptr [esi], ecx
00d05b08  d0854e006092             rol        byte ptr [ebp - 0x6d9fffb2], 1
00d05b0e  43                       inc        ebx
00d05b0f  007090                   add        byte ptr [eax - 0x70], dh
00d05b12  43                       inc        ebx
00d05b13  00f0                     add        al, dh
00d05b15  cf                       iretd      
00d05b16  49                       dec        ecx
00d05b17  0010                     add        byte ptr [eax], dl
00d05b19  dd4900                   fisttp     qword ptr [ecx]
00d05b1c  e0d0                     loopne     0xd05aee
00d05b1e  49                       dec        ecx
00d05b1f  0010                     add        byte ptr [eax], dl
00d05b21  92                       xchg       edx, eax
00d05b22  43                       inc        ebx
00d05b23  0020                     add        byte ptr [eax], ah
00d05b25  92                       xchg       edx, eax
00d05b26  43                       inc        ebx
00d05b27  0090cf4900b0             add        byte ptr [eax - 0x4fffb631], dl
00d05b2d  cb                       retf       
00d05b2e  49                       dec        ecx
00d05b2f  00d0                     add        al, dl
00d05b31  91                       xchg       ecx, eax
00d05b32  43                       inc        ebx
00d05b33  00f0                     add        al, dh
00d05b35  91                       xchg       ecx, eax
00d05b36  43                       inc        ebx
00d05b37  00a0ea4900e0             add        byte ptr [eax - 0x1fffb616], ah
00d05b3d  ce                       into       
00d05b3e  49                       dec        ecx
00d05b3f  00b80deb00b0             add        byte ptr [eax - 0x4fff14f3], bh
00d05b45  e85c00e002               call       0x3b05ba6
00d05b4a  57                       push       edi
00d05b4b  0010                     add        byte ptr [eax], dl
00d05b4d  7d40                     jge        0xd05b8f
00d05b4f  00607d                   add        byte ptr [eax + 0x7d], ah
00d05b52  40                       inc        eax
00d05b53  0010                     add        byte ptr [eax], dl
00d05b55  f0                       .byte      0xf0
00d05b56  49                       dec        ecx
00d05b57  00                       .byte      0x00
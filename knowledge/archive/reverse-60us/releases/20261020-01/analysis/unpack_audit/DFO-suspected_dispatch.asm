012ee7c9 fb                       sti        
012ee7ca d59f                     aad        0x9f
012ee7cc 32a76deaca83             xor        ah, byte ptr [edi - 0x7c351593]
012ee7d2 d5f7                     aad        0xf7
012ee7d4 2aa76dea9a83             sub        ah, byte ptr [edi - 0x7c651593]
012ee7da ee                       out        dx, al
012ee7db cb                       retf       
012ee7dc fa                       cli        
012ee7dd 107253                   adc        byte ptr [edx + 0x53], dh
012ee7e0 0a5c3326                 or         bl, byte ptr [ebx + esi + 0x26]
012ee7e4 05ede4a283               add        eax, 0x83a2e4ed
012ee7e9 34b4                     xor        al, 0xb4
012ee7eb 8c0a                     mov        word ptr [edx], cs
012ee7ed 9e                       sahf       
012ee7ee 59                       pop        ecx
012ee7ef 53                       push       ebx
012ee7f0 16                       push       ss
012ee7f1 0a2a                     or         ch, byte ptr [edx]
012ee7f3 b343                     mov        bl, 0x43
012ee7f5 ec                       in         al, dx
012ee7f6 8933                     mov        dword ptr [ebx], esi
012ee7f8 baa3e47397               mov        edx, 0x9773e4a3
012ee7fd a3e912a398               mov        dword ptr [0x98a312e9], eax
012ee802 642b97a3e44b97           sub        edx, dword ptr fs:[edi - 0x68b41b5d]
012ee809 a3e912a398               mov        dword ptr [0x98a312e9], eax
012ee80e 7c78                     jl         0x12ee888
012ee810 23c9                     and        ecx, ecx
012ee812 a36eeb1062               mov        dword ptr [0x6210eb6e], eax
012ee817 53                       push       ebx
012ee818 60                       pushal     

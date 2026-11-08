00af16c0  8b5024                   mov        edx, dword ptr [eax + 0x24]
00af16c3  d8f1                     fdiv       st(1)
00af16c5  85d2                     test       edx, edx
00af16c7  db4024                   fild       dword ptr [eax + 0x24]
00af16ca  7d06                     jge        0xaf16d2
00af16cc  dc059875cd00             fadd       qword ptr [0xcd7598]
00af16d2  d8f2                     fdiv       st(2)
00af16d4  dee9                     fsubp      st(1)
00af16d6  dd9e88000000             fstp       qword ptr [esi + 0x88]
00af16dc  ddd8                     fstp       st(0)
00af16de  5f                       pop        edi
00af16df  5e                       pop        esi
00af16e0  5d                       pop        ebp
00af16e1  c20400                   ret        4
00af16e4  cc                       int3       
00af16e5  cc                       int3       
00af16e6  cc                       int3       
00af16e7  cc                       int3       
00af16e8  cc                       int3       
00af16e9  cc                       int3       
00af16ea  cc                       int3       
00af16eb  cc                       int3       
00af16ec  cc                       int3       
00af16ed  cc                       int3       
00af16ee  cc                       int3       
00af16ef  cc                       int3       
00af16f0  56                       push       esi
00af16f1  8bf1                     mov        esi, ecx
00af16f3  8b06                     mov        eax, dword ptr [esi]
00af16f5  ff5024                   call       dword ptr [eax + 0x24]
00af16f8  8a4611                   mov        al, byte ptr [esi + 0x11]
00af16fb  84c0                     test       al, al
00af16fd  7412                     je         0xaf1711
00af16ff  8a8694000000             mov        al, byte ptr [esi + 0x94]
00af1705  84c0                     test       al, al
00af1707  7408                     je         0xaf1711
00af1709  8b16                     mov        edx, dword ptr [esi]
00af170b  8bce                     mov        ecx, esi
00af170d  5e                       pop        esi
00af170e  ff6230                   jmp        dword ptr [edx + 0x30]
00af1711  5e                       pop        esi
00af1712  c3                       ret        
00af1713  cc                       int3       
00af1714  cc                       int3       
00af1715  cc                       int3       
00af1716  cc                       int3       
00af1717  cc                       int3       
00af1718  cc                       int3       
00af1719  cc                       int3       
00af171a  cc                       int3       
00af171b  cc                       int3       
00af171c  cc                       int3       
00af171d  cc                       int3       
00af171e  cc                       int3       
00af171f  cc                       int3       
00af1720  55                       push       ebp
00af1721  8bec                     mov        ebp, esp
00af1723  51                       push       ecx
00af1724  56                       push       esi
00af1725  8bf1                     mov        esi, ecx
00af1727  8a4610                   mov        al, byte ptr [esi + 0x10]
00af172a  84c0                     test       al, al
00af172c  7467                     je         0xaf1795
00af172e  8b4670                   mov        eax, dword ptr [esi + 0x70]
00af1731  85c0                     test       eax, eax
00af1733  7414                     je         0xaf1749
00af1735  8b4e14                   mov        ecx, dword ptr [esi + 0x14]
00af1738  50                       push       eax
00af1739  8b4618                   mov        eax, dword ptr [esi + 0x18]
00af173c  50                       push       eax
00af173d  51                       push       ecx
00af173e  8b0db8d91f01             mov        ecx, dword ptr [0x11fd9b8]
00af1744  e887c70100               call       0xb0ded0
00af1749  8b4674                   mov        eax, dword ptr [esi + 0x74]
00af174c  85c0                     test       eax, eax
00af174e  7445                     je         0xaf1795
00af1750  8b8e84000000             mov        ecx, dword ptr [esi + 0x84]
00af1756  85c9                     test       ecx, ecx
00af1758  743b                     je         0xaf1795
00af175a  8b5618                   mov        edx, dword ptr [esi + 0x18]
00af175d  db8680000000             fild       dword ptr [esi + 0x80]
00af1763  50                       push       eax
00af1764  8b8680000000             mov        eax, dword ptr [esi + 0x80]
00af176a  85c0                     test       eax, eax
00af176c  52                       push       edx
00af176d  7d06                     jge        0xaf1775
00af176f  dc059875cd00             fadd       qword ptr [0xcd7598]
00af1775  dc8e88000000             fmul       qword ptr [esi + 0x88]
00af177b  da4614                   fiadd      dword ptr [esi + 0x14]
00af177e  dc056095ce00             fadd       qword ptr [0xce9560]
00af1784  e8bbfd1000               call       0xc01544
00af1789  8b0db8d91f01             mov        ecx, dword ptr [0x11fd9b8]
00af178f  50                       push       eax
00af1790  e83bc70100               call       0xb0ded0
00af1795  5e                       pop        esi
00af1796  8be5                     mov        esp, ebp
00af1798  5d                       pop        ebp
00af1799  c3                       ret        
00af179a  cc                       int3       
00af179b  cc                       int3       
00af179c  cc                       int3       
00af179d  cc                       int3       
00af179e  cc                       int3       
00af179f  cc                       int3       
00af17a0  55                       push       ebp
00af17a1  8bec                     mov        ebp, esp
00af17a3  51                       push       ecx
00af17a4  56                       push       esi
00af17a5  8bf1                     mov        esi, ecx
00af17a7  8a4611                   mov        al, byte ptr [esi + 0x11]
00af17aa  84c0                     test       al, al
00af17ac  747e                     je         0xaf182c
00af17ae  8b4674                   mov        eax, dword ptr [esi + 0x74]
00af17b1  85c0                     test       eax, eax
00af17b3  7477                     je         0xaf182c
00af17b5  a1a829ff00               mov        eax, dword ptr [0xff29a8]
00af17ba  3b460c                   cmp        eax, dword ptr [esi + 0xc]
00af17bd  7405                     je         0xaf17c4
00af17bf  83f8ff                   cmp        eax, -1
00af17c2  7568                     jne        0xaf182c
00af17c4  8bce                     mov        ecx, esi
00af17c6  e895a10100               call       0xb0b960
00af17cb  84c0                     test       al, al
00af17cd  7411                     je         0xaf17e0
00af17cf  a0ec7d2001               mov        al, byte ptr [0x1207dec]
00af17d4  84c0                     test       al, al
00af17d6  7408                     je         0xaf17e0
00af17d8  8b460c                   mov        eax, dword ptr [esi + 0xc]
00af17db  a3a829ff00               mov        dword ptr [0xff29a8], eax
00af17e0  833ddc7d200101           cmp        dword ptr [0x1207ddc], 1
00af17e7  7543                     jne        0xaf182c
00af17e9  8b0da829ff00             mov        ecx, dword ptr [0xff29a8]
00af17ef  3b4e0c                   cmp        ecx, dword ptr [esi + 0xc]
00af17f2  7538                     jne        0xaf182c
00af17f4  8b5674                   mov        edx, dword ptr [esi + 0x74]
00af17f7  57                       push       edi
00af17f8  8b7a24                   mov        edi, dword ptr [edx + 0x24]
00af17fb  e810fe0100               call       0xb11610
00af1800  8bc8                     mov        ecx, eax
00af1802  8bc7                     mov        eax, edi
00af1804  8b7e14                   mov        edi, dword ptr [esi + 0x14]
00af1807  99                       cdq        
00af1808  2bc2                     sub        eax, edx
00af180a  d1f8                     sar        eax, 1
00af180c  f7d8                     neg        eax
00af180e  2bc7                     sub        eax, edi
00af1810  03c8                     add        ecx, eax
00af1812  894dfc                   mov        dword ptr [ebp - 4], ecx
00af1815  db45fc                   fild       dword ptr [ebp - 4]
00af1818  dcb688000000             fdiv       qword ptr [esi + 0x88]
00af181e  e821fd1000               call       0xc01544
00af1823  50                       push       eax
00af1824  8bce                     mov        ecx, esi
00af1826  e815c70000               call       0xafdf40
00af182b  5f                       pop        edi
00af182c  5e                       pop        esi
00af182d  8be5                     mov        esp, ebp
00af182f  5d                       pop        ebp
00af1830  c3                       ret        
00af1831  cc                       int3       
00af1832  cc                       int3       
00af1833  cc                       int3       
00af1834  cc                       int3       
00af1835  cc                       int3       
00af1836  cc                       int3       
00af1837  cc                       int3       
00af1838  cc                       int3       
00af1839  cc                       int3       
00af183a  cc                       int3       
00af183b  cc                       int3       
00af183c  cc                       int3       
00af183d  cc                       int3       
00af183e  cc                       int3       
00af183f  cc                       int3       
00af1840  55                       push       ebp
00af1841  8bec                     mov        ebp, esp
00af1843  51                       push       ecx
00af1844  56                       push       esi
00af1845  8b7508                   mov        esi, dword ptr [ebp + 8]
00af1848  8b4618                   mov        eax, dword ptr [esi + 0x18]
00af184b  57                       push       edi
00af184c  8bf9                     mov        edi, ecx
00af184e  8b                       .byte      0x8b
00af184f  4e                       dec        esi
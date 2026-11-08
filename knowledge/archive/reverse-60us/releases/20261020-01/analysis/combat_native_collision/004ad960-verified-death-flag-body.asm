004ad960 55                       push      ebp
004ad961 8bec                     mov       ebp, esp
004ad963 56                       push      esi
004ad964 8bf1                     mov       esi, ecx
004ad966 8b06                     mov       eax, dword ptr [esi]
004ad968 ff90dc030000             call      dword ptr [eax + 0x3dc]
004ad96e 8a5508                   mov       dl, byte ptr [ebp + 8]
004ad971 3ad0                     cmp       dl, al
004ad973 7472                     je        0x4ad9e7
004ad975 8b8e58150000             mov       ecx, dword ptr [esi + 0x1558]
004ad97b 53                       push      ebx
004ad97c 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004ad982 57                       push      edi
004ad983 8b3dd8012101             mov       edi, dword ptr [0x12101d8]
004ad989 8b7f44                   mov       edi, dword ptr [edi + 0x44]
004ad98c 8d0c8f                   lea       ecx, [edi + ecx*4]
004ad98f 8bf9                     mov       edi, ecx
004ad991 33fb                     xor       edi, ebx
004ad993 0fb6c2                   movzx     eax, dl
004ad996 33f8                     xor       edi, eax
004ad998 8939                     mov       dword ptr [ecx], edi
004ad99a 8b3dd8012101             mov       edi, dword ptr [0x12101d8]
004ad9a0 8b7f48                   mov       edi, dword ptr [edi + 0x48]
004ad9a3 8b8e58150000             mov       ecx, dword ptr [esi + 0x1558]
004ad9a9 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004ad9af 8d0c8f                   lea       ecx, [edi + ecx*4]
004ad9b2 8bf9                     mov       edi, ecx
004ad9b4 33fb                     xor       edi, ebx
004ad9b6 33f8                     xor       edi, eax
004ad9b8 84d2                     test      dl, dl
004ad9ba 8939                     mov       dword ptr [ecx], edi
004ad9bc 7427                     je        0x4ad9e5
004ad9be 33ff                     xor       edi, edi
004ad9c0 8d9e94120000             lea       ebx, [esi + 0x1294]
004ad9c6 8b16                     mov       edx, dword ptr [esi]
004ad9c8 57                       push      edi
004ad9c9 8bce                     mov       ecx, esi
004ad9cb ff9210040000             call      dword ptr [edx + 0x410]
004ad9d1 84c0                     test      al, al
004ad9d3 7407                     je        0x4ad9dc
004ad9d5 8b0b                     mov       ecx, dword ptr [ebx]
004ad9d7 8b01                     mov       eax, dword ptr [ecx]
004ad9d9 ff5040                   call      dword ptr [eax + 0x40]
004ad9dc 47                       inc       edi
004ad9dd 83c304                   add       ebx, 4
004ad9e0 83ff12                   cmp       edi, 0x12
004ad9e3 7ce1                     jl        0x4ad9c6
004ad9e5 5f                       pop       edi
004ad9e6 5b                       pop       ebx
004ad9e7 5e                       pop       esi
004ad9e8 5d                       pop       ebp
004ad9e9 c20400                   ret       4

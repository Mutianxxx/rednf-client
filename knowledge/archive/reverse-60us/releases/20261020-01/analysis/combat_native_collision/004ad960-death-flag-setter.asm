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
004ad9ec cc                       int3      
004ad9ed cc                       int3      
004ad9ee cc                       int3      
004ad9ef cc                       int3      
004ad9f0 55                       push      ebp
004ad9f1 8bec                     mov       ebp, esp
004ad9f3 56                       push      esi
004ad9f4 8bf1                     mov       esi, ecx
004ad9f6 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ad9f9 8b06                     mov       eax, dword ptr [esi]
004ad9fb 57                       push      edi
004ad9fc 51                       push      ecx
004ad9fd 8bce                     mov       ecx, esi
004ad9ff ff9044030000             call      dword ptr [eax + 0x344]
004ada05 8bf8                     mov       edi, eax
004ada07 8b4508                   mov       eax, dword ptr [ebp + 8]
004ada0a 85c0                     test      eax, eax
004ada0c c7450c00000000           mov       dword ptr [ebp + 0xc], 0
004ada13 0f8586000000             jne       0x4ada9f
004ada19 8bcf                     mov       ecx, edi
004ada1b e8f07b0000               call      0x4b5610
004ada20 89450c                   mov       dword ptr [ebp + 0xc], eax
004ada23 db450c                   fild      dword ptr [ebp + 0xc]
004ada26 8bcf                     mov       ecx, edi
004ada28 d95d0c                   fstp      dword ptr [ebp + 0xc]
004ada2b e8507a0000               call      0x4b5480
004ada30 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004ada36 894508                   mov       dword ptr [ebp + 8], eax
004ada39 db4508                   fild      dword ptr [ebp + 8]
004ada3c 81c140100000             add       ecx, 0x1040
004ada42 d95d08                   fstp      dword ptr [ebp + 8]
004ada45 e81646f5ff               call      0x402060
004ada4a 83f804                   cmp       eax, 4
004ada4d 7411                     je        0x4ada60
004ada4f 6a03                     push      3
004ada51 56                       push      esi
004ada52 e8b9b1f9ff               call      0x448c10
004ada57 d84d08                   fmul      dword ptr [ebp + 8]
004ada5a 83c408                   add       esp, 8
004ada5d d95d08                   fstp      dword ptr [ebp + 8]

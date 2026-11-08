00499fa0 55                       push      ebp
00499fa1 8bec                     mov       ebp, esp
00499fa3 8bc1                     mov       eax, ecx
00499fa5 837d080d                 cmp       dword ptr [ebp + 8], 0xd
00499fa9 7517                     jne       0x499fc2
00499fab 8b8854010000             mov       ecx, dword ptr [eax + 0x154]
00499fb1 85c9                     test      ecx, ecx
00499fb3 740d                     je        0x499fc2
00499fb5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00499fb8 50                       push      eax
00499fb9 e822445900               call      0xa2e3e0
00499fbe 5d                       pop       ebp
00499fbf c20c00                   ret       0xc
00499fc2 8b8048010000             mov       eax, dword ptr [eax + 0x148]
00499fc8 85c0                     test      eax, eax
00499fca 740b                     je        0x499fd7
00499fcc 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
00499fcf 51                       push      ecx
00499fd0 8bc8                     mov       ecx, eax
00499fd2 e809445900               call      0xa2e3e0
00499fd7 5d                       pop       ebp
00499fd8 c20c00                   ret       0xc
00499fdb cc                       int3      
00499fdc cc                       int3      
00499fdd cc                       int3      
00499fde cc                       int3      
00499fdf cc                       int3      
00499fe0 56                       push      esi
00499fe1 8bf1                     mov       esi, ecx
00499fe3 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499fe9 85c9                     test      ecx, ecx
00499feb 743c                     je        0x49a029
00499fed e8be2f5900               call      0xa2cfb0
00499ff2 85c0                     test      eax, eax
00499ff4 7433                     je        0x49a029
00499ff6 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
00499ffc e8af2f5900               call      0xa2cfb0
0049a001 8bf0                     mov       esi, eax
0049a003 83be24010000ff           cmp       dword ptr [esi + 0x124], -1
0049a00a 7507                     jne       0x49a013
0049a00c 8bce                     mov       ecx, esi
0049a00e e84ddf5800               call      0xa27f60
0049a013 8b86dc000000             mov       eax, dword ptr [esi + 0xdc]
0049a019 8d8edc000000             lea       ecx, [esi + 0xdc]
0049a01f 2bc1                     sub       eax, ecx
0049a021 3305f83e0d01             xor       eax, dword ptr [0x10d3ef8]
0049a027 5e                       pop       esi
0049a028 c3                       ret       
0049a029 8bb604010000             mov       esi, dword ptr [esi + 0x104]
0049a02f 85f6                     test      esi, esi
0049a031 75d0                     jne       0x49a003
0049a033 33c0                     xor       eax, eax
0049a035 5e                       pop       esi
0049a036 c3                       ret       
0049a037 cc                       int3      
0049a038 cc                       int3      
0049a039 cc                       int3      
0049a03a cc                       int3      
0049a03b cc                       int3      
0049a03c cc                       int3      
0049a03d cc                       int3      
0049a03e cc                       int3      
0049a03f cc                       int3      
0049a040 55                       push      ebp
0049a041 8bec                     mov       ebp, esp
0049a043 8a4518                   mov       al, byte ptr [ebp + 0x18]
0049a046 84c0                     test      al, al
0049a048 7408                     je        0x49a052
0049a04a d905581fcc00             fld       dword ptr [0xcc1f58]
0049a050 eb0c                     jmp       0x49a05e
0049a052 db05dcf2fa00             fild      dword ptr [0xfaf2dc]
0049a058 d80dac10cc00             fmul      dword ptr [0xcc10ac]
0049a05e 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
0049a061 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049a064 2bc1                     sub       eax, ecx
0049a066 894518                   mov       dword ptr [ebp + 0x18], eax
0049a069 db4518                   fild      dword ptr [ebp + 0x18]
0049a06c 8b5510                   mov       edx, dword ptr [ebp + 0x10]
0049a06f 56                       push      esi
0049a070 8b7508                   mov       esi, dword ptr [ebp + 8]
0049a073 d8f1                     fdiv      st(1)
0049a075 2bf2                     sub       esi, edx
0049a077 e8c8747600               call      0xc01544
0049a07c ddd8                     fstp      st(0)
0049a07e 8bd6                     mov       edx, esi
0049a080 8bc8                     mov       ecx, eax
0049a082 0fafd6                   imul      edx, esi
0049a085 0fafc8                   imul      ecx, eax
0049a088 03ca                     add       ecx, edx
0049a08a 894d18                   mov       dword ptr [ebp + 0x18], ecx
0049a08d 5e                       pop       esi
0049a08e db4518                   fild      dword ptr [ebp + 0x18]
0049a091 d9fa                     fsqrt     
0049a093 5d                       pop       ebp
0049a094 e9ab747600               jmp       0xc01544
0049a099 cc                       int3      
0049a09a cc                       int3      
0049a09b cc                       int3      
0049a09c cc                       int3      
0049a09d cc                       int3      
0049a09e cc                       int3      
0049a09f cc                       int3      

00438f70 55                       push      ebp
00438f71 8bec                     mov       ebp, esp
00438f73 6aff                     push      -1
00438f75 686a0cc500               push      0xc50c6a
00438f7a 64a100000000             mov       eax, dword ptr fs:[0]
00438f80 50                       push      eax
00438f81 64892500000000           mov       dword ptr fs:[0], esp
00438f88 83ec08                   sub       esp, 8
00438f8b 56                       push      esi
00438f8c 8bf1                     mov       esi, ecx
00438f8e 57                       push      edi
00438f8f 8975f0                   mov       dword ptr [ebp - 0x10], esi
00438f92 e859f5ffff               call      0x4384f0
00438f97 33ff                     xor       edi, edi
00438f99 8d8e24050000             lea       ecx, [esi + 0x524]
00438f9f 897dfc                   mov       dword ptr [ebp - 4], edi
00438fa2 c706d4b7cb00             mov       dword ptr [esi], 0xcbb7d4
00438fa8 e823ebffff               call      0x437ad0
00438fad 8d8edc050000             lea       ecx, [esi + 0x5dc]
00438fb3 c645fc01                 mov       byte ptr [ebp - 4], 1
00438fb7 e874edffff               call      0x437d30
00438fbc c786d407000007000000     mov       dword ptr [esi + 0x7d4], 7
00438fc6 89bed0070000             mov       dword ptr [esi + 0x7d0], edi
00438fcc 6689bec0070000           mov       word ptr [esi + 0x7c0], di
00438fd3 8d8eec070000             lea       ecx, [esi + 0x7ec]
00438fd9 c645fc03                 mov       byte ptr [ebp - 4], 3
00438fdd e8feb4fcff               call      0x4044e0
00438fe2 c7860c08000007000000     mov       dword ptr [esi + 0x80c], 7
00438fec 89be08080000             mov       dword ptr [esi + 0x808], edi
00438ff2 6689bef8070000           mov       word ptr [esi + 0x7f8], di
00438ff9 89be20080000             mov       dword ptr [esi + 0x820], edi
00438fff 89be24080000             mov       dword ptr [esi + 0x824], edi
00439005 89be28080000             mov       dword ptr [esi + 0x828], edi
0043900b 89be34080000             mov       dword ptr [esi + 0x834], edi
00439011 89be38080000             mov       dword ptr [esi + 0x838], edi
00439017 89be3c080000             mov       dword ptr [esi + 0x83c], edi
0043901d 89be44080000             mov       dword ptr [esi + 0x844], edi
00439023 89be48080000             mov       dword ptr [esi + 0x848], edi
00439029 89be4c080000             mov       dword ptr [esi + 0x84c], edi
0043902f 6810204000               push      0x402010
00439034 68e0444000               push      0x4044e0
00439039 6a03                     push      3
0043903b 6a08                     push      8
0043903d 8d8650080000             lea       eax, [esi + 0x850]
00439043 50                       push      eax
00439044 c645fc08                 mov       byte ptr [ebp - 4], 8
00439048 e817787c00               call      0xc00864
0043904d 8bce                     mov       ecx, esi
0043904f c645fc09                 mov       byte ptr [ebp - 4], 9
00439053 e8185e0600               call      0x49ee70
00439058 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0043905b 5f                       pop       edi
0043905c 8bc6                     mov       eax, esi
0043905e 5e                       pop       esi
0043905f 64890d00000000           mov       dword ptr fs:[0], ecx
00439066 8be5                     mov       esp, ebp
00439068 5d                       pop       ebp
00439069 c3                       ret       
0043906a cc                       int3      
0043906b cc                       int3      
0043906c cc                       int3      
0043906d cc                       int3      
0043906e cc                       int3      
0043906f cc                       int3      

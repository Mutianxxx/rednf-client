004672b0 55                       push      ebp
004672b1 8bec                     mov       ebp, esp
004672b3 6aff                     push      -1
004672b5 687432c500               push      0xc53274
004672ba 64a100000000             mov       eax, dword ptr fs:[0]
004672c0 50                       push      eax
004672c1 64892500000000           mov       dword ptr fs:[0], esp
004672c8 51                       push      ecx
004672c9 56                       push      esi
004672ca 8bf1                     mov       esi, ecx
004672cc 8975f0                   mov       dword ptr [ebp - 0x10], esi
004672cf e8bccef9ff               call      0x404190
004672d4 8d4e08                   lea       ecx, [esi + 8]
004672d7 c745fc00000000           mov       dword ptr [ebp - 4], 0
004672de e8adcef9ff               call      0x404190
004672e3 8d4e10                   lea       ecx, [esi + 0x10]
004672e6 c645fc01                 mov       byte ptr [ebp - 4], 1
004672ea e8a1cef9ff               call      0x404190
004672ef 8d4e18                   lea       ecx, [esi + 0x18]
004672f2 c645fc02                 mov       byte ptr [ebp - 4], 2
004672f6 e895cef9ff               call      0x404190
004672fb 8d4e20                   lea       ecx, [esi + 0x20]
004672fe c645fc03                 mov       byte ptr [ebp - 4], 3
00467302 e889cef9ff               call      0x404190
00467307 8d4e28                   lea       ecx, [esi + 0x28]
0046730a c645fc04                 mov       byte ptr [ebp - 4], 4
0046730e e87dcef9ff               call      0x404190
00467313 8bce                     mov       ecx, esi
00467315 e8f6fdffff               call      0x467110
0046731a 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0046731d 8bc6                     mov       eax, esi
0046731f 5e                       pop       esi
00467320 64890d00000000           mov       dword ptr fs:[0], ecx
00467327 8be5                     mov       esp, ebp
00467329 5d                       pop       ebp
0046732a c3                       ret       
0046732b cc                       int3      
0046732c cc                       int3      
0046732d cc                       int3      
0046732e cc                       int3      
0046732f cc                       int3      
00467330 55                       push      ebp
00467331 8bec                     mov       ebp, esp
00467333 6aff                     push      -1
00467335 687432c500               push      0xc53274
0046733a 64a100000000             mov       eax, dword ptr fs:[0]
00467340 50                       push      eax
00467341 64892500000000           mov       dword ptr fs:[0], esp
00467348 51                       push      ecx
00467349 53                       push      ebx
0046734a 56                       push      esi
0046734b 8bf1                     mov       esi, ecx
0046734d 57                       push      edi
0046734e 8975f0                   mov       dword ptr [ebp - 0x10], esi
00467351 e83acef9ff               call      0x404190
00467356 8d7e08                   lea       edi, [esi + 8]
00467359 8bcf                     mov       ecx, edi
0046735b c745fc00000000           mov       dword ptr [ebp - 4], 0
00467362 e829cef9ff               call      0x404190
00467367 8d5e10                   lea       ebx, [esi + 0x10]
0046736a 8bcb                     mov       ecx, ebx
0046736c c645fc01                 mov       byte ptr [ebp - 4], 1
00467370 e81bcef9ff               call      0x404190
00467375 8d4e18                   lea       ecx, [esi + 0x18]
00467378 c645fc02                 mov       byte ptr [ebp - 4], 2
0046737c e80fcef9ff               call      0x404190
00467381 8d4e20                   lea       ecx, [esi + 0x20]
00467384 c645fc03                 mov       byte ptr [ebp - 4], 3
00467388 e803cef9ff               call      0x404190
0046738d 8d4e28                   lea       ecx, [esi + 0x28]
00467390 c645fc04                 mov       byte ptr [ebp - 4], 4
00467394 e8f7cdf9ff               call      0x404190
00467399 8bce                     mov       ecx, esi
0046739b e870fdffff               call      0x467110
004673a0 db4508                   fild      dword ptr [ebp + 8]
004673a3 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004673a9 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004673ac 8b4604                   mov       eax, dword ptr [esi + 4]
004673af d95d08                   fstp      dword ptr [ebp + 8]
004673b2 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004673b8 db450c                   fild      dword ptr [ebp + 0xc]
004673bb 8d0482                   lea       eax, [edx + eax*4]
004673be 8bd0                     mov       edx, eax
004673c0 33d1                     xor       edx, ecx
004673c2 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004673c5 d95d08                   fstp      dword ptr [ebp + 8]
004673c8 33d1                     xor       edx, ecx
004673ca db4510                   fild      dword ptr [ebp + 0x10]
004673cd 8910                     mov       dword ptr [eax], edx
004673cf 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004673d5 8b5248                   mov       edx, dword ptr [edx + 0x48]
004673d8 8b4604                   mov       eax, dword ptr [esi + 4]
004673db 8d0482                   lea       eax, [edx + eax*4]
004673de 8bd0                     mov       edx, eax
004673e0 3315dc012101             xor       edx, dword ptr [0x12101dc]
004673e6 33d1                     xor       edx, ecx
004673e8 8910                     mov       dword ptr [eax], edx
004673ea 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004673f0 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004673f3 8b4704                   mov       eax, dword ptr [edi + 4]
004673f6 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004673fc 8d0482                   lea       eax, [edx + eax*4]
004673ff 8bd0                     mov       edx, eax
00467401 33d1                     xor       edx, ecx
00467403 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00467406 d95d08                   fstp      dword ptr [ebp + 8]
00467409 33d1                     xor       edx, ecx
0046740b 8910                     mov       dword ptr [eax], edx
0046740d 8b15d8012101             mov       edx, dword ptr [0x12101d8]
00467413 8b5248                   mov       edx, dword ptr [edx + 0x48]
00467416 8b4704                   mov       eax, dword ptr [edi + 4]
00467419 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
0046741f 8d0482                   lea       eax, [edx + eax*4]
00467422 8bd0                     mov       edx, eax
00467424 33d7                     xor       edx, edi
00467426 33d1                     xor       edx, ecx
00467428 8910                     mov       dword ptr [eax], edx
0046742a 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]

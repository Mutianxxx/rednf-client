0049faac 8d5f70                   lea       ebx, [edi + 0x70]
0049faaf 68e0baca00               push      0xcabae0
0049fab4 8bcb                     mov       ecx, ebx
0049fab6 e835365b00               call      0xa530f0
0049fabb 50                       push      eax
0049fabc e82a137600               call      0xc00deb
0049fac1 83c408                   add       esp, 8
0049fac4 85c0                     test      eax, eax
0049fac6 7468                     je        0x49fb30
0049fac8 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049face e81d365b00               call      0xa530f0
0049fad3 8bcb                     mov       ecx, ebx
0049fad5 894508                   mov       dword ptr [ebp + 8], eax
0049fad8 e813365b00               call      0xa530f0
0049fadd 8b0df8300001             mov       ecx, dword ptr [0x10030f8]
0049fae3 50                       push      eax
0049fae4 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fae7 50                       push      eax
0049fae8 68f8b8ca00               push      0xcab8f8
0049faed 51                       push      ecx
0049faee e83dd76d00               call      0xb7d230
0049faf3 83c410                   add       esp, 0x10
0049faf6 85c0                     test      eax, eax
0049faf8 740e                     je        0x49fb08
0049fafa 50                       push      eax
0049fafb 8d8edc050000             lea       ecx, [esi + 0x5dc]
0049fb01 e8da2c0000               call      0x4a27e0
0049fb06 eb28                     jmp       0x49fb30
0049fb08 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049fb0e e8dd355b00               call      0xa530f0
0049fb13 8bcb                     mov       ecx, ebx
0049fb15 894508                   mov       dword ptr [ebp + 8], eax
0049fb18 e8d3355b00               call      0xa530f0
0049fb1d 8b5508                   mov       edx, dword ptr [ebp + 8]
0049fb20 50                       push      eax
0049fb21 52                       push      edx
0049fb22 6828f0cc00               push      0xccf028
0049fb27 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049fb2d 83c40c                   add       esp, 0xc
0049fb30 8b5f78                   mov       ebx, dword ptr [edi + 0x78]
0049fb33 3b5f7c                   cmp       ebx, dword ptr [edi + 0x7c]
0049fb36 0f84fc000000             je        0x49fc38
0049fb3c 8d642400                 lea       esp, [esp]
0049fb40 68e0baca00               push      0xcabae0
0049fb45 8bcb                     mov       ecx, ebx
0049fb47 e8a4355b00               call      0xa530f0
0049fb4c 50                       push      eax
0049fb4d e899127600               call      0xc00deb
0049fb52 83c408                   add       esp, 8
0049fb55 85c0                     test      eax, eax
0049fb57 0f849d000000             je        0x49fbfa
0049fb5d 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049fb63 e888355b00               call      0xa530f0
0049fb68 8bcb                     mov       ecx, ebx
0049fb6a 894508                   mov       dword ptr [ebp + 8], eax
0049fb6d e87e355b00               call      0xa530f0
0049fb72 8b0df8300001             mov       ecx, dword ptr [0x10030f8]
0049fb78 50                       push      eax
0049fb79 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fb7c 50                       push      eax
0049fb7d 68f8b8ca00               push      0xcab8f8
0049fb82 51                       push      ecx
0049fb83 e8a8d66d00               call      0xb7d230
0049fb88 83c410                   add       esp, 0x10
0049fb8b 85c0                     test      eax, eax
0049fb8d 7411                     je        0x49fba0
0049fb8f 50                       push      eax
0049fb90 8d8e44040000             lea       ecx, [esi + 0x444]
0049fb96 e8953a0000               call      0x4a3630
0049fb9b e98a000000               jmp       0x49fc2a
0049fba0 8d8d14feffff             lea       ecx, [ebp - 0x1ec]
0049fba6 e88581f9ff               call      0x437d30
0049fbab 50                       push      eax
0049fbac 8d8e44040000             lea       ecx, [esi + 0x444]
0049fbb2 c745fc05000000           mov       dword ptr [ebp - 4], 5
0049fbb9 e8723a0000               call      0x4a3630
0049fbbe 8d8d14feffff             lea       ecx, [ebp - 0x1ec]
0049fbc4 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fbcb e8907bf9ff               call      0x437760
0049fbd0 8d8fa4000000             lea       ecx, [edi + 0xa4]
0049fbd6 e815355b00               call      0xa530f0
0049fbdb 8bcb                     mov       ecx, ebx
0049fbdd 894508                   mov       dword ptr [ebp + 8], eax
0049fbe0 e80b355b00               call      0xa530f0
0049fbe5 8b5508                   mov       edx, dword ptr [ebp + 8]
0049fbe8 50                       push      eax
0049fbe9 52                       push      edx
0049fbea 6828f0cc00               push      0xccf028
0049fbef ff15bc2eff00             call      dword ptr [0xff2ebc]
0049fbf5 83c40c                   add       esp, 0xc
0049fbf8 eb30                     jmp       0x49fc2a
0049fbfa 8d8d5cfcffff             lea       ecx, [ebp - 0x3a4]
0049fc00 e82b81f9ff               call      0x437d30
0049fc05 50                       push      eax
0049fc06 8d8e44040000             lea       ecx, [esi + 0x444]
0049fc0c c745fc06000000           mov       dword ptr [ebp - 4], 6
0049fc13 e8183a0000               call      0x4a3630
0049fc18 8d8d5cfcffff             lea       ecx, [ebp - 0x3a4]
0049fc1e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fc25 e8367bf9ff               call      0x437760
0049fc2a 8b477c                   mov       eax, dword ptr [edi + 0x7c]
0049fc2d 83c304                   add       ebx, 4
0049fc30 3bd8                     cmp       ebx, eax
0049fc32 0f8508ffffff             jne       0x49fb40
0049fc38 8d8784000000             lea       eax, [edi + 0x84]
0049fc3e 50                       push      eax
0049fc3f 8d8e30020000             lea       ecx, [esi + 0x230]
0049fc45 e8f67c0600               call      0x507940
0049fc4a 8d8f94000000             lea       ecx, [edi + 0x94]
0049fc50 51                       push      ecx
0049fc51 8d8e48050000             lea       ecx, [esi + 0x548]
0049fc57 e88496f9ff               call      0x4392e0
0049fc5c 8b87a8000000             mov       eax, dword ptr [edi + 0xa8]
0049fc62 83f8ff                   cmp       eax, -1
0049fc65 7406                     je        0x49fc6d
0049fc67 898620050000             mov       dword ptr [esi + 0x520], eax
0049fc6d a1dc012101               mov       eax, dword ptr [0x12101dc]
0049fc72 8b97ac000000             mov       edx, dword ptr [edi + 0xac]
0049fc78 8d9fac000000             lea       ebx, [edi + 0xac]
0049fc7e 33d0                     xor       edx, eax
0049fc80 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fc83 2bd3                     sub       edx, ebx
0049fc85 3bd0                     cmp       edx, eax
0049fc87 740e                     je        0x49fc97
0049fc89 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fc8f 6a3f                     push      0x3f
0049fc91 53                       push      ebx
0049fc92 e819746700               call      0xb170b0
0049fc97 a1d8012101               mov       eax, dword ptr [0x12101d8]
0049fc9c 8b5044                   mov       edx, dword ptr [eax + 0x44]
0049fc9f 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fca2 c1e002                   shl       eax, 2
0049fca5 8d0c02                   lea       ecx, [edx + eax]
0049fca8 330c02                   xor       ecx, dword ptr [edx + eax]
0049fcab 330ddc012101             xor       ecx, dword ptr [0x12101dc]
0049fcb1 894d08                   mov       dword ptr [ebp + 8], ecx
0049fcb4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fcba 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
0049fcbd 8d1401                   lea       edx, [ecx + eax]
0049fcc0 331401                   xor       edx, dword ptr [ecx + eax]
0049fcc3 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fcc9 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fccc 33d1                     xor       edx, ecx
0049fcce 3bc2                     cmp       eax, edx
0049fcd0 740e                     je        0x49fce0
0049fcd2 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fcd8 6a40                     push      0x40
0049fcda 53                       push      ebx
0049fcdb e8d0736700               call      0xb170b0
0049fce0 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fce3 85c0                     test      eax, eax
0049fce5 0f8e8e000000             jle       0x49fd79
0049fceb 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fcf1 8b03                     mov       eax, dword ptr [ebx]
0049fcf3 33c1                     xor       eax, ecx
0049fcf5 8b4b04                   mov       ecx, dword ptr [ebx + 4]
0049fcf8 2bc3                     sub       eax, ebx
0049fcfa 3bc1                     cmp       eax, ecx
0049fcfc 740e                     je        0x49fd0c
0049fcfe 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd04 6a3f                     push      0x3f
0049fd06 53                       push      ebx
0049fd07 e8a4736700               call      0xb170b0
0049fd0c 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd12 8b5144                   mov       edx, dword ptr [ecx + 0x44]
0049fd15 8b4304                   mov       eax, dword ptr [ebx + 4]
0049fd18 c1e002                   shl       eax, 2
0049fd1b 8d0c02                   lea       ecx, [edx + eax]
0049fd1e 330c02                   xor       ecx, dword ptr [edx + eax]
0049fd21 330ddc012101             xor       ecx, dword ptr [0x12101dc]
0049fd27 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049fd2d 894d08                   mov       dword ptr [ebp + 8], ecx
0049fd30 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
0049fd33 8d1401                   lea       edx, [ecx + eax]
0049fd36 331401                   xor       edx, dword ptr [ecx + eax]
0049fd39 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049fd3f 8b4508                   mov       eax, dword ptr [ebp + 8]
0049fd42 33d1                     xor       edx, ecx
0049fd44 3bc2                     cmp       eax, edx
0049fd46 740e                     je        0x49fd56
0049fd48 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fd4e 6a40                     push      0x40
0049fd50 53                       push      ebx
0049fd51 e85a736700               call      0xb170b0
0049fd56 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049fd59 8b06                     mov       eax, dword ptr [esi]
0049fd5b 51                       push      ecx
0049fd5c 8bce                     mov       ecx, esi
0049fd5e ff9060030000             call      dword ptr [eax + 0x360]
0049fd64 8b1e                     mov       ebx, dword ptr [esi]
0049fd66 8bd3                     mov       edx, ebx
0049fd68 8bce                     mov       ecx, esi
0049fd6a ff9238020000             call      dword ptr [edx + 0x238]
0049fd70 50                       push      eax
0049fd71 8bce                     mov       ecx, esi
0049fd73 ff935c030000             call      dword ptr [ebx + 0x35c]
0049fd79 8a4761                   mov       al, byte ptr [edi + 0x61]
0049fd7c 84c0                     test      al, al
0049fd7e 740e                     je        0x49fd8e
0049fd80 8b06                     mov       eax, dword ptr [esi]
0049fd82 8bce                     mov       ecx, esi
0049fd84 ff903c030000             call      dword ptr [eax + 0x33c]
0049fd8a c6403401                 mov       byte ptr [eax + 0x34], 1
0049fd8e 8d4f6c                   lea       ecx, [edi + 0x6c]
0049fd91 68e0baca00               push      0xcabae0
0049fd96 e855335b00               call      0xa530f0
0049fd9b 50                       push      eax
0049fd9c e84a107600               call      0xc00deb
0049fda1 83c408                   add       esp, 8
0049fda4 85c0                     test      eax, eax
0049fda6 7456                     je        0x49fdfe
0049fda8 68b4010000               push      0x1b4
0049fdad e89e3ef6ff               call      0x403c50
0049fdb2 83c404                   add       esp, 4
0049fdb5 894508                   mov       dword ptr [ebp + 8], eax
0049fdb8 85c0                     test      eax, eax
0049fdba c745fc07000000           mov       dword ptr [ebp - 4], 7
0049fdc1 742c                     je        0x49fdef
0049fdc3 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
0049fdca 7208                     jb        0x49fdd4
0049fdcc 8b9e48020000             mov       ebx, dword ptr [esi + 0x248]
0049fdd2 eb06                     jmp       0x49fdda
0049fdd4 8d9e48020000             lea       ebx, [esi + 0x248]
0049fdda 56                       push      esi
0049fddb 8d4f6c                   lea       ecx, [edi + 0x6c]
0049fdde e80d335b00               call      0xa530f0
0049fde3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049fde6 50                       push      eax
0049fde7 53                       push      ebx
0049fde8 e853360000               call      0x4a3440
0049fded eb02                     jmp       0x49fdf1
0049fdef 33c0                     xor       eax, eax
0049fdf1 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049fdf8 898694070000             mov       dword ptr [esi + 0x794], eax
0049fdfe 8b16                     mov       edx, dword ptr [esi]
0049fe00 6a01                     push      1
0049fe02 6a01                     push      1
0049fe04 6a00                     push      0
0049fe06 6a00                     push      0
0049fe08 8bce                     mov       ecx, esi
0049fe0a ff922c020000             call      dword ptr [edx + 0x22c]
0049fe10 8d8648060000             lea       eax, [esi + 0x648]
0049fe16 8d9e50080000             lea       ebx, [esi + 0x850]
0049fe1c 3bd8                     cmp       ebx, eax
0049fe1e 7468                     je        0x49fe88
0049fe20 8b5004                   mov       edx, dword ptr [eax + 4]
0049fe23 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fe29 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
0049fe2c c1e202                   shl       edx, 2
0049fe2f 8d0411                   lea       eax, [ecx + edx]
0049fe32 330411                   xor       eax, dword ptr [ecx + edx]
0049fe35 3305dc012101             xor       eax, dword ptr [0x12101dc]
0049fe3b 8b5304                   mov       edx, dword ptr [ebx + 4]
0049fe3e c1e202                   shl       edx, 2
0049fe41 8d1c11                   lea       ebx, [ecx + edx]
0049fe44 33d8                     xor       ebx, eax
0049fe46 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049fe4c 891c11                   mov       dword ptr [ecx + edx], ebx
0049fe4f 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049fe55 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
0049fe58 8b964c060000             mov       edx, dword ptr [esi + 0x64c]
0049fe5e c1e202                   shl       edx, 2
0049fe61 8b1c11                   mov       ebx, dword ptr [ecx + edx]
0049fe64 8d0411                   lea       eax, [ecx + edx]
0049fe67 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0049fe6d 33c3                     xor       eax, ebx
0049fe6f 33c2                     xor       eax, edx
0049fe71 8b9654080000             mov       edx, dword ptr [esi + 0x854]
0049fe77 c1e202                   shl       edx, 2
0049fe7a 8d1c11                   lea       ebx, [ecx + edx]
0049fe7d 33d8                     xor       ebx, eax
0049fe7f 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049fe85 891c11                   mov       dword ptr [ecx + edx], ebx
0049fe88 8d8650060000             lea       eax, [esi + 0x650]
0049fe8e 8d9e58080000             lea       ebx, [esi + 0x858]
0049fe94 3bd8                     cmp       ebx, eax
0049fe96 7468                     je        0x49ff00
0049fe98 8b5004                   mov       edx, dword ptr [eax + 4]
0049fe9b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049fea1 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
0049fea4 c1e202                   shl       edx, 2
0049fea7 8d0411                   lea       eax, [ecx + edx]
0049feaa 330411                   xor       eax, dword ptr [ecx + edx]
0049fead 3305dc012101             xor       eax, dword ptr [0x12101dc]
0049feb3 8b5304                   mov       edx, dword ptr [ebx + 4]
0049feb6 c1e202                   shl       edx, 2
0049feb9 8d1c11                   lea       ebx, [ecx + edx]
0049febc 33d8                     xor       ebx, eax
0049febe 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049fec4 891c11                   mov       dword ptr [ecx + edx], ebx
0049fec7 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049fecd 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
0049fed0 8b9654060000             mov       edx, dword ptr [esi + 0x654]
0049fed6 c1e202                   shl       edx, 2
0049fed9 8b1c11                   mov       ebx, dword ptr [ecx + edx]
0049fedc 8d0411                   lea       eax, [ecx + edx]
0049fedf 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0049fee5 33c3                     xor       eax, ebx
0049fee7 33c2                     xor       eax, edx
0049fee9 8b965c080000             mov       edx, dword ptr [esi + 0x85c]
0049feef c1e202                   shl       edx, 2
0049fef2 8d1c11                   lea       ebx, [ecx + edx]
0049fef5 33d8                     xor       ebx, eax
0049fef7 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049fefd 891c11                   mov       dword ptr [ecx + edx], ebx
0049ff00 8d8658060000             lea       eax, [esi + 0x658]
0049ff06 8d9e60080000             lea       ebx, [esi + 0x860]
0049ff0c 3bd8                     cmp       ebx, eax
0049ff0e 7468                     je        0x49ff78
0049ff10 8b5004                   mov       edx, dword ptr [eax + 4]
0049ff13 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049ff19 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
0049ff1c c1e202                   shl       edx, 2
0049ff1f 8d0411                   lea       eax, [ecx + edx]
0049ff22 330411                   xor       eax, dword ptr [ecx + edx]
0049ff25 3305dc012101             xor       eax, dword ptr [0x12101dc]
0049ff2b 8b5304                   mov       edx, dword ptr [ebx + 4]
0049ff2e c1e202                   shl       edx, 2
0049ff31 8d1c11                   lea       ebx, [ecx + edx]
0049ff34 33d8                     xor       ebx, eax
0049ff36 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049ff3c 891c11                   mov       dword ptr [ecx + edx], ebx
0049ff3f 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049ff45 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
0049ff48 8b965c060000             mov       edx, dword ptr [esi + 0x65c]
0049ff4e c1e202                   shl       edx, 2
0049ff51 8b1c11                   mov       ebx, dword ptr [ecx + edx]
0049ff54 8d0411                   lea       eax, [ecx + edx]
0049ff57 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0049ff5d 33c3                     xor       eax, ebx
0049ff5f 33c2                     xor       eax, edx
0049ff61 8b9664080000             mov       edx, dword ptr [esi + 0x864]
0049ff67 c1e202                   shl       edx, 2
0049ff6a 8d1c11                   lea       ebx, [ecx + edx]
0049ff6d 33d8                     xor       ebx, eax
0049ff6f 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049ff75 891c11                   mov       dword ptr [ecx + edx], ebx
0049ff78 8b0d64310001             mov       ecx, dword ptr [0x1003164]
0049ff7e 8b01                     mov       eax, dword ptr [ecx]
0049ff80 ff9088000000             call      dword ptr [eax + 0x88]
0049ff86 85c0                     test      eax, eax
0049ff88 0f84a4010000             je        0x4a0132
0049ff8e 8b0d64310001             mov       ecx, dword ptr [0x1003164]
0049ff94 8b11                     mov       edx, dword ptr [ecx]
0049ff96 ff9288000000             call      dword ptr [edx + 0x88]
0049ff9c 8b88b4000000             mov       ecx, dword ptr [eax + 0xb4]
0049ffa2 85c9                     test      ecx, ecx
0049ffa4 0f8488010000             je        0x4a0132
0049ffaa 8b0d64310001             mov       ecx, dword ptr [0x1003164]
0049ffb0 8b01                     mov       eax, dword ptr [ecx]
0049ffb2 ff9088000000             call      dword ptr [eax + 0x88]
0049ffb8 8b80b4000000             mov       eax, dword ptr [eax + 0xb4]
0049ffbe 8b4874                   mov       ecx, dword ptr [eax + 0x74]
0049ffc1 8d5874                   lea       ebx, [eax + 0x74]
0049ffc4 330ddc012101             xor       ecx, dword ptr [0x12101dc]
0049ffca 8b4304                   mov       eax, dword ptr [ebx + 4]
0049ffcd 2bcb                     sub       ecx, ebx
0049ffcf 3bc8                     cmp       ecx, eax
0049ffd1 895d08                   mov       dword ptr [ebp + 8], ebx
0049ffd4 740e                     je        0x49ffe4
0049ffd6 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049ffdc 6a3f                     push      0x3f
0049ffde 53                       push      ebx
0049ffdf e8cc706700               call      0xb170b0
0049ffe4 8b4304                   mov       eax, dword ptr [ebx + 4]
0049ffe7 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0049ffed 8b4a44                   mov       ecx, dword ptr [edx + 0x44]
0049fff0 c1e002                   shl       eax, 2
0049fff3 8d1c01                   lea       ebx, [ecx + eax]
0049fff6 331c01                   xor       ebx, dword ptr [ecx + eax]
0049fff9 331ddc012101             xor       ebx, dword ptr [0x12101dc]
0049ffff 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
004a0002 8d1401                   lea       edx, [ecx + eax]
004a0005 331401                   xor       edx, dword ptr [ecx + eax]
004a0008 3315dc012101             xor       edx, dword ptr [0x12101dc]
004a000e 3bda                     cmp       ebx, edx
004a0010 7411                     je        0x4a0023
004a0012 8b4508                   mov       eax, dword ptr [ebp + 8]
004a0015 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a001b 6a40                     push      0x40
004a001d 50                       push      eax
004a001e e88d706700               call      0xb170b0
004a0023 899e98070000             mov       dword ptr [esi + 0x798], ebx
004a0029 8d8e24060000             lea       ecx, [esi + 0x624]
004a002f 8d9e54080000             lea       ebx, [esi + 0x854]
004a0035 894d08                   mov       dword ptr [ebp + 8], ecx
004a0038 895dec                   mov       dword ptr [ebp - 0x14], ebx
004a003b c745f003000000           mov       dword ptr [ebp - 0x10], 3
004a0042 8b5508                   mov       edx, dword ptr [ebp + 8]
004a0045 833a12                   cmp       dword ptr [edx], 0x12
004a0048 0f84c6000000             je        0x4a0114
004a004e 8b43fc                   mov       eax, dword ptr [ebx - 4]
004a0051 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004a0057 8b0b                     mov       ecx, dword ptr [ebx]
004a0059 33c2                     xor       eax, edx
004a005b 2bc3                     sub       eax, ebx
004a005d 83c004                   add       eax, 4
004a0060 3bc1                     cmp       eax, ecx
004a0062 7411                     je        0x4a0075
004a0064 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a006a 6a3f                     push      0x3f
004a006c 8d43fc                   lea       eax, [ebx - 4]
004a006f 50                       push      eax
004a0070 e83b706700               call      0xb170b0
004a0075 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a007b 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004a007e 8b03                     mov       eax, dword ptr [ebx]
004a0080 c1e002                   shl       eax, 2
004a0083 8d0c02                   lea       ecx, [edx + eax]
004a0086 330c02                   xor       ecx, dword ptr [edx + eax]
004a0089 330ddc012101             xor       ecx, dword ptr [0x12101dc]
004a008f 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004a0095 894d0c                   mov       dword ptr [ebp + 0xc], ecx
004a0098 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
004a009b 8d1401                   lea       edx, [ecx + eax]
004a009e 331401                   xor       edx, dword ptr [ecx + eax]
004a00a1 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004a00a7 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004a00aa 33d1                     xor       edx, ecx
004a00ac 3bc2                     cmp       eax, edx
004a00ae 7411                     je        0x4a00c1
004a00b0 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a00b6 6a40                     push      0x40
004a00b8 8d43fc                   lea       eax, [ebx - 4]
004a00bb 50                       push      eax
004a00bc e8ef6f6700               call      0xb170b0
004a00c1 8b8698070000             mov       eax, dword ptr [esi + 0x798]
004a00c7 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a00ca 8b9bf8fdffff             mov       ebx, dword ptr [ebx - 0x208]
004a00d0 03c1                     add       eax, ecx
004a00d2 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a00d8 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004a00db c1e302                   shl       ebx, 2
004a00de 8d1419                   lea       edx, [ecx + ebx]
004a00e1 33d0                     xor       edx, eax
004a00e3 3315dc012101             xor       edx, dword ptr [0x12101dc]
004a00e9 891419                   mov       dword ptr [ecx + ebx], edx
004a00ec 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004a00f2 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004a00f5 8b5dec                   mov       ebx, dword ptr [ebp - 0x14]
004a00f8 8b8bf8fdffff             mov       ecx, dword ptr [ebx - 0x208]
004a00fe 89550c                   mov       dword ptr [ebp + 0xc], edx
004a0101 c1e102                   shl       ecx, 2
004a0104 03d1                     add       edx, ecx
004a0106 33d0                     xor       edx, eax
004a0108 3315dc012101             xor       edx, dword ptr [0x12101dc]
004a010e 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004a0111 891408                   mov       dword ptr [eax + ecx], edx
004a0114 8b5508                   mov       edx, dword ptr [ebp + 8]
004a0117 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
004a011a 83c204                   add       edx, 4
004a011d 83c308                   add       ebx, 8
004a0120 48                       dec       eax
004a0121 895508                   mov       dword ptr [ebp + 8], edx
004a0124 895dec                   mov       dword ptr [ebp - 0x14], ebx
004a0127 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a012a 0f8512ffffff             jne       0x4a0042
004a0130 eb0e                     jmp       0x4a0140
004a0132 6810f0cc00               push      0xccf010
004a0137 ff15bc2eff00             call      dword ptr [0xff2ebc]
004a013d 83c404                   add       esp, 4
004a0140 8b8fe0000000             mov       ecx, dword ptr [edi + 0xe0]
004a0146 898e5c050000             mov       dword ptr [esi + 0x55c], ecx
004a014c 8b97e4000000             mov       edx, dword ptr [edi + 0xe4]
004a0152 899660050000             mov       dword ptr [esi + 0x560], edx
004a0158 8b87ec000000             mov       eax, dword ptr [edi + 0xec]
004a015e 85c0                     test      eax, eax
004a0160 7504                     jne       0x4a0166
004a0162 33db                     xor       ebx, ebx
004a0164 eb0b                     jmp       0x4a0171
004a0166 8b9ff0000000             mov       ebx, dword ptr [edi + 0xf0]
004a016c 2bd8                     sub       ebx, eax
004a016e c1fb02                   sar       ebx, 2
004a0171 6a00                     push      0
004a0173 53                       push      ebx
004a0174 8d8e64050000             lea       ecx, [esi + 0x564]
004a017a 895d08                   mov       dword ptr [ebp + 8], ebx
004a017d e8ce200000               call      0x4a2250
004a0182 33c0                     xor       eax, eax
004a0184 85db                     test      ebx, ebx
004a0186 7e22                     jle       0x4a01aa
004a0188 eb06                     jmp       0x4a0190
004a018a 8d9b00000000             lea       ebx, [ebx]
004a0190 8b8fec000000             mov       ecx, dword ptr [edi + 0xec]
004a0196 8b0c81                   mov       ecx, dword ptr [ecx + eax*4]
004a0199 8b9668050000             mov       edx, dword ptr [esi + 0x568]
004a019f 890c82                   mov       dword ptr [edx + eax*4], ecx
004a01a2 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a01a5 40                       inc       eax
004a01a6 3bc1                     cmp       eax, ecx
004a01a8 7ce6                     jl        0x4a0190
004a01aa 8b9730010000             mov       edx, dword ptr [edi + 0x130]
004a01b0 8996c8050000             mov       dword ptr [esi + 0x5c8], edx
004a01b6 8b8738010000             mov       eax, dword ptr [edi + 0x138]
004a01bc 85c0                     test      eax, eax
004a01be 7504                     jne       0x4a01c4
004a01c0 33db                     xor       ebx, ebx
004a01c2 eb0b                     jmp       0x4a01cf
004a01c4 8b9f3c010000             mov       ebx, dword ptr [edi + 0x13c]
004a01ca 2bd8                     sub       ebx, eax
004a01cc c1fb02                   sar       ebx, 2
004a01cf 6a00                     push      0
004a01d1 53                       push      ebx
004a01d2 8d8ecc050000             lea       ecx, [esi + 0x5cc]
004a01d8 895d08                   mov       dword ptr [ebp + 8], ebx
004a01db e870200000               call      0x4a2250
004a01e0 33c0                     xor       eax, eax
004a01e2 85db                     test      ebx, ebx
004a01e4 7e24                     jle       0x4a020a
004a01e6 eb08                     jmp       0x4a01f0
004a01e8 8da42400000000           lea       esp, [esp]
004a01ef 90                       nop       
004a01f0 8b8f38010000             mov       ecx, dword ptr [edi + 0x138]
004a01f6 8b0c81                   mov       ecx, dword ptr [ecx + eax*4]
004a01f9 8b96d0050000             mov       edx, dword ptr [esi + 0x5d0]
004a01ff 890c82                   mov       dword ptr [edx + eax*4], ecx
004a0202 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a0205 40                       inc       eax
004a0206 3bc1                     cmp       eax, ecx
004a0208 7ce6                     jl        0x4a01f0
004a020a 8b8f0c010000             mov       ecx, dword ptr [edi + 0x10c]
004a0210 85c9                     test      ecx, ecx
004a0212 7505                     jne       0x4a0219
004a0214 894d08                   mov       dword ptr [ebp + 8], ecx
004a0217 eb0e                     jmp       0x4a0227
004a0219 8b8710010000             mov       eax, dword ptr [edi + 0x110]
004a021f 2bc1                     sub       eax, ecx
004a0221 c1f802                   sar       eax, 2
004a0224 894508                   mov       dword ptr [ebp + 8], eax
004a0227 51                       push      ecx
004a0228 8bcc                     mov       ecx, esp
004a022a 89650c                   mov       dword ptr [ebp + 0xc], esp
004a022d 68e0baca00               push      0xcabae0
004a0232 c70100000000             mov       dword ptr [ecx], 0
004a0238 e863365b00               call      0xa538a0
004a023d 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a0240 53                       push      ebx
004a0241 8d8e84050000             lea       ecx, [esi + 0x584]
004a0247 e8b4170000               call      0x4a1a00
004a024c 6a00                     push      0
004a024e 53                       push      ebx
004a024f 8d8e94050000             lea       ecx, [esi + 0x594]
004a0255 e8f61f0000               call      0x4a2250
004a025a 8b4508                   mov       eax, dword ptr [ebp + 8]
004a025d 33db                     xor       ebx, ebx
004a025f 85c0                     test      eax, eax
004a0261 7e3f                     jle       0x4a02a2
004a0263 eb0b                     jmp       0x4a0270
004a0265 8da42400000000           lea       esp, [esp]
004a026c 8d642400                 lea       esp, [esp]
004a0270 8b870c010000             mov       eax, dword ptr [edi + 0x10c]
004a0276 8b8e88050000             mov       ecx, dword ptr [esi + 0x588]
004a027c 8d0498                   lea       eax, [eax + ebx*4]
004a027f 8d0c99                   lea       ecx, [ecx + ebx*4]
004a0282 50                       push      eax
004a0283 e808325b00               call      0xa53490
004a0288 8b871c010000             mov       eax, dword ptr [edi + 0x11c]
004a028e 8b1498                   mov       edx, dword ptr [eax + ebx*4]
004a0291 8b8e98050000             mov       ecx, dword ptr [esi + 0x598]
004a0297 8b4508                   mov       eax, dword ptr [ebp + 8]
004a029a 891499                   mov       dword ptr [ecx + ebx*4], edx
004a029d 43                       inc       ebx
004a029e 3bd8                     cmp       ebx, eax
004a02a0 7cce                     jl        0x4a0270
004a02a2 8b8728010000             mov       eax, dword ptr [edi + 0x128]
004a02a8 8986b8050000             mov       dword ptr [esi + 0x5b8], eax
004a02ae 8b8f2c010000             mov       ecx, dword ptr [edi + 0x12c]
004a02b4 898ebc050000             mov       dword ptr [esi + 0x5bc], ecx
004a02ba ff155cf04001             call      dword ptr [0x140f05c]
004a02c0 8986c0050000             mov       dword ptr [esi + 0x5c0], eax
004a02c6 8b8748010000             mov       eax, dword ptr [edi + 0x148]
004a02cc 3b874c010000             cmp       eax, dword ptr [edi + 0x14c]
004a02d2 894508                   mov       dword ptr [ebp + 8], eax
004a02d5 0f8419010000             je        0x4a03f4
004a02db 8d9e30080000             lea       ebx, [esi + 0x830]
004a02e1 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a02e4 68e0baca00               push      0xcabae0
004a02e9 e8022e5b00               call      0xa530f0
004a02ee 50                       push      eax
004a02ef e8f70a7600               call      0xc00deb
004a02f4 83c408                   add       esp, 8
004a02f7 85c0                     test      eax, eax
004a02f9 0f8492000000             je        0x4a0391
004a02ff 68e8010000               push      0x1e8
004a0304 e84739f6ff               call      0x403c50
004a0309 83c404                   add       esp, 4
004a030c 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a030f 85c0                     test      eax, eax
004a0311 c745fc08000000           mov       dword ptr [ebp - 4], 8
004a0318 742a                     je        0x4a0344
004a031a 8d8fa4000000             lea       ecx, [edi + 0xa4]
004a0320 e8cb2d5b00               call      0xa530f0
004a0325 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a0328 6a01                     push      1
004a032a 89450c                   mov       dword ptr [ebp + 0xc], eax
004a032d e8be2d5b00               call      0xa530f0
004a0332 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004a0335 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
004a0338 50                       push      eax
004a0339 52                       push      edx
004a033a e82127fdff               call      0x472a60
004a033f 89450c                   mov       dword ptr [ebp + 0xc], eax
004a0342 eb07                     jmp       0x4a034b
004a0344 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
004a034b 8b5304                   mov       edx, dword ptr [ebx + 4]
004a034e 85d2                     test      edx, edx
004a0350 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004a0353 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a035a 8945f0                   mov       dword ptr [ebp - 0x10], eax
004a035d 7504                     jne       0x4a0363
004a035f 33c0                     xor       eax, eax
004a0361 eb08                     jmp       0x4a036b
004a0363 8b4308                   mov       eax, dword ptr [ebx + 8]
004a0366 2bc2                     sub       eax, edx
004a0368 c1f802                   sar       eax, 2
004a036b 85d2                     test      edx, edx
004a036d 741c                     je        0x4a038b
004a036f 8b4b0c                   mov       ecx, dword ptr [ebx + 0xc]
004a0372 2bca                     sub       ecx, edx
004a0374 c1f902                   sar       ecx, 2
004a0377 3bc1                     cmp       eax, ecx
004a0379 7310                     jae       0x4a038b
004a037b 8b4308                   mov       eax, dword ptr [ebx + 8]
004a037e 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a0381 8908                     mov       dword ptr [eax], ecx
004a0383 83c004                   add       eax, 4
004a0386 894308                   mov       dword ptr [ebx + 8], eax
004a0389 eb52                     jmp       0x4a03dd
004a038b 8d55f0                   lea       edx, [ebp - 0x10]
004a038e 52                       push      edx
004a038f eb3f                     jmp       0x4a03d0
004a0391 8b5304                   mov       edx, dword ptr [ebx + 4]
004a0394 85d2                     test      edx, edx
004a0396 c7450c00000000           mov       dword ptr [ebp + 0xc], 0
004a039d 7504                     jne       0x4a03a3
004a039f 33c9                     xor       ecx, ecx
004a03a1 eb08                     jmp       0x4a03ab
004a03a3 8b4b08                   mov       ecx, dword ptr [ebx + 8]
004a03a6 2bca                     sub       ecx, edx
004a03a8 c1f902                   sar       ecx, 2
004a03ab 85d2                     test      edx, edx
004a03ad 741d                     je        0x4a03cc
004a03af 8b430c                   mov       eax, dword ptr [ebx + 0xc]
004a03b2 2bc2                     sub       eax, edx
004a03b4 c1f802                   sar       eax, 2
004a03b7 3bc8                     cmp       ecx, eax
004a03b9 7311                     jae       0x4a03cc
004a03bb 8b4308                   mov       eax, dword ptr [ebx + 8]
004a03be c70000000000             mov       dword ptr [eax], 0
004a03c4 83c004                   add       eax, 4
004a03c7 894308                   mov       dword ptr [ebx + 8], eax
004a03ca eb11                     jmp       0x4a03dd
004a03cc 8d4d0c                   lea       ecx, [ebp + 0xc]
004a03cf 51                       push      ecx
004a03d0 8b4308                   mov       eax, dword ptr [ebx + 8]
004a03d3 6a01                     push      1
004a03d5 8bcb                     mov       ecx, ebx
004a03d7 50                       push      eax
004a03d8 e8837df6ff               call      0x408160
004a03dd 8b4508                   mov       eax, dword ptr [ebp + 8]
004a03e0 8b8f4c010000             mov       ecx, dword ptr [edi + 0x14c]
004a03e6 83c004                   add       eax, 4
004a03e9 3bc1                     cmp       eax, ecx
004a03eb 894508                   mov       dword ptr [ebp + 8], eax
004a03ee 0f85edfeffff             jne       0x4a02e1
004a03f4 33d2                     xor       edx, edx
004a03f6 895508                   mov       dword ptr [ebp + 8], edx
004a03f9 8da42400000000           lea       esp, [esp]
004a0400 8b8f58010000             mov       ecx, dword ptr [edi + 0x158]
004a0406 85c9                     test      ecx, ecx
004a0408 0f847b000000             je        0x4a0489
004a040e 8b875c010000             mov       eax, dword ptr [edi + 0x15c]
004a0414 2bc1                     sub       eax, ecx
004a0416 c1f802                   sar       eax, 2
004a0419 3bd0                     cmp       edx, eax
004a041b 736c                     jae       0x4a0489
004a041d 8bc1                     mov       eax, ecx
004a041f 8d0c90                   lea       ecx, [eax + edx*4]
004a0422 8b8644080000             mov       eax, dword ptr [esi + 0x844]
004a0428 85c0                     test      eax, eax
004a042a 894d0c                   mov       dword ptr [ebp + 0xc], ecx
004a042d 8d8e40080000             lea       ecx, [esi + 0x840]
004a0433 7504                     jne       0x4a0439
004a0435 33db                     xor       ebx, ebx
004a0437 eb08                     jmp       0x4a0441
004a0439 8b5908                   mov       ebx, dword ptr [ecx + 8]
004a043c 2bd8                     sub       ebx, eax
004a043e c1fb02                   sar       ebx, 2
004a0441 85c0                     test      eax, eax
004a0443 7427                     je        0x4a046c
004a0445 8b510c                   mov       edx, dword ptr [ecx + 0xc]
004a0448 2bd0                     sub       edx, eax
004a044a c1fa02                   sar       edx, 2
004a044d 3bda                     cmp       ebx, edx
004a044f 731b                     jae       0x4a046c
004a0451 8b4108                   mov       eax, dword ptr [ecx + 8]
004a0454 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004a0457 8b12                     mov       edx, dword ptr [edx]
004a0459 8910                     mov       dword ptr [eax], edx
004a045b 83c004                   add       eax, 4
004a045e 894108                   mov       dword ptr [ecx + 8], eax
004a0461 8b4508                   mov       eax, dword ptr [ebp + 8]
004a0464 40                       inc       eax
004a0465 894508                   mov       dword ptr [ebp + 8], eax
004a0468 8bd0                     mov       edx, eax
004a046a eb94                     jmp       0x4a0400
004a046c 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004a046f 8b4108                   mov       eax, dword ptr [ecx + 8]
004a0472 52                       push      edx
004a0473 6a01                     push      1
004a0475 50                       push      eax
004a0476 e8e55af6ff               call      0x405f60
004a047b 8b4508                   mov       eax, dword ptr [ebp + 8]
004a047e 40                       inc       eax
004a047f 894508                   mov       dword ptr [ebp + 8], eax
004a0482 8bd0                     mov       edx, eax
004a0484 e977ffffff               jmp       0x4a0400
004a0489 33db                     xor       ebx, ebx
004a048b eb03                     jmp       0x4a0490
004a048d 8d4900                   lea       ecx, [ecx]
004a0490 8b8e34080000             mov       ecx, dword ptr [esi + 0x834]
004a0496 85c9                     test      ecx, ecx
004a0498 743a                     je        0x4a04d4
004a049a 8b8638080000             mov       eax, dword ptr [esi + 0x838]
004a04a0 2bc1                     sub       eax, ecx
004a04a2 c1f802                   sar       eax, 2
004a04a5 3bd8                     cmp       ebx, eax
004a04a7 732b                     jae       0x4a04d4
004a04a9 8b1499                   mov       edx, dword ptr [ecx + ebx*4]
004a04ac 8b8e44080000             mov       ecx, dword ptr [esi + 0x844]
004a04b2 8b06                     mov       eax, dword ptr [esi]
004a04b4 6a01                     push      1
004a04b6 6a00                     push      0
004a04b8 6a00                     push      0
004a04ba 6a00                     push      0
004a04bc 6a00                     push      0
004a04be 6a00                     push      0
004a04c0 6a00                     push      0
004a04c2 6a00                     push      0
004a04c4 52                       push      edx
004a04c5 8b1499                   mov       edx, dword ptr [ecx + ebx*4]
004a04c8 52                       push      edx
004a04c9 8bce                     mov       ecx, esi
004a04cb ff90f8000000             call      dword ptr [eax + 0xf8]
004a04d1 43                       inc       ebx
004a04d2 ebbc                     jmp       0x4a0490
004a04d4 8b8f68010000             mov       ecx, dword ptr [edi + 0x168]
004a04da 85c9                     test      ecx, ecx
004a04dc 0f84ab010000             je        0x4a068d
004a04e2 8b876c010000             mov       eax, dword ptr [edi + 0x16c]
004a04e8 2bc1                     sub       eax, ecx
004a04ea c1f802                   sar       eax, 2
004a04ed 85c0                     test      eax, eax
004a04ef 0f8498010000             je        0x4a068d
004a04f5 8bc1                     mov       eax, ecx
004a04f7 3b876c010000             cmp       eax, dword ptr [edi + 0x16c]
004a04fd 894508                   mov       dword ptr [ebp + 8], eax
004a0500 0f8487010000             je        0x4a068d
004a0506 68b4010000               push      0x1b4
004a050b e84037f6ff               call      0x403c50
004a0510 83c404                   add       esp, 4
004a0513 89450c                   mov       dword ptr [ebp + 0xc], eax
004a0516 85c0                     test      eax, eax
004a0518 c745fc09000000           mov       dword ptr [ebp - 4], 9
004a051f 7430                     je        0x4a0551
004a0521 8b4508                   mov       eax, dword ptr [ebp + 8]
004a0524 8b08                     mov       ecx, dword ptr [eax]
004a0526 83be5c02000008           cmp       dword ptr [esi + 0x25c], 8
004a052d 7208                     jb        0x4a0537
004a052f 8b9e48020000             mov       ebx, dword ptr [esi + 0x248]
004a0535 eb06                     jmp       0x4a053d
004a0537 8d9e48020000             lea       ebx, [esi + 0x248]
004a053d 56                       push      esi
004a053e e8ad2b5b00               call      0xa530f0
004a0543 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004a0546 50                       push      eax
004a0547 53                       push      ebx
004a0548 e8f32e0000               call      0x4a3440
004a054d 8bd8                     mov       ebx, eax
004a054f eb02                     jmp       0x4a0553
004a0551 33db                     xor       ebx, ebx
004a0553 85db                     test      ebx, ebx
004a0555 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a055c 0f8414010000             je        0x4a0676
004a0562 68e0baca00               push      0xcabae0
004a0567 8d4dd0                   lea       ecx, [ebp - 0x30]
004a056a c745d000000000           mov       dword ptr [ebp - 0x30], 0
004a0571 e82a335b00               call      0xa538a0
004a0576 68e0baca00               push      0xcabae0
004a057b 8d4dd0                   lea       ecx, [ebp - 0x30]
004a057e c745fc0a000000           mov       dword ptr [ebp - 4], 0xa
004a0585 c745cc00000000           mov       dword ptr [ebp - 0x34], 0
004a058c e80f335b00               call      0xa538a0
004a0591 33c0                     xor       eax, eax
004a0593 8945d4                   mov       dword ptr [ebp - 0x2c], eax
004a0596 8945d8                   mov       dword ptr [ebp - 0x28], eax
004a0599 8945dc                   mov       dword ptr [ebp - 0x24], eax
004a059c 8945e0                   mov       dword ptr [ebp - 0x20], eax
004a059f 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004a05a2 8845e8                   mov       byte ptr [ebp - 0x18], al
004a05a5 8b13                     mov       edx, dword ptr [ebx]
004a05a7 50                       push      eax
004a05a8 8bcb                     mov       ecx, ebx
004a05aa c745fc0b000000           mov       dword ptr [ebp - 4], 0xb
004a05b1 ff520c                   call      dword ptr [edx + 0xc]
004a05b4 895dcc                   mov       dword ptr [ebp - 0x34], ebx
004a05b7 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004a05ba 8b03                     mov       eax, dword ptr [ebx]
004a05bc 83c004                   add       eax, 4
004a05bf 50                       push      eax
004a05c0 8d4dd0                   lea       ecx, [ebp - 0x30]
004a05c3 e8c82e5b00               call      0xa53490
004a05c8 8b03                     mov       eax, dword ptr [ebx]
004a05ca 8b480c                   mov       ecx, dword ptr [eax + 0xc]
004a05cd 894dd8                   mov       dword ptr [ebp - 0x28], ecx
004a05d0 8b5010                   mov       edx, dword ptr [eax + 0x10]
004a05d3 8955dc                   mov       dword ptr [ebp - 0x24], edx
004a05d6 8b4814                   mov       ecx, dword ptr [eax + 0x14]
004a05d9 894de0                   mov       dword ptr [ebp - 0x20], ecx
004a05dc 8b5018                   mov       edx, dword ptr [eax + 0x18]
004a05df 83c008                   add       eax, 8
004a05e2 68f0efcc00               push      0xcceff0
004a05e7 8bc8                     mov       ecx, eax
004a05e9 8955e4                   mov       dword ptr [ebp - 0x1c], edx
004a05ec e8ff2a5b00               call      0xa530f0
004a05f1 50                       push      eax
004a05f2 e8f4077600               call      0xc00deb
004a05f7 83c408                   add       esp, 8
004a05fa 85c0                     test      eax, eax
004a05fc 7507                     jne       0x4a0605
004a05fe c745d401000000           mov       dword ptr [ebp - 0x2c], 1
004a0605 8b9620080000             mov       edx, dword ptr [esi + 0x820]
004a060b 85d2                     test      edx, edx
004a060d 8d9e1c080000             lea       ebx, [esi + 0x81c]
004a0613 7504                     jne       0x4a0619
004a0615 33c9                     xor       ecx, ecx
004a0617 eb08                     jmp       0x4a0621
004a0619 8b4b08                   mov       ecx, dword ptr [ebx + 8]
004a061c 2bca                     sub       ecx, edx
004a061e c1f905                   sar       ecx, 5
004a0621 85d2                     test      edx, edx
004a0623 7431                     je        0x4a0656
004a0625 8b430c                   mov       eax, dword ptr [ebx + 0xc]
004a0628 2bc2                     sub       eax, edx
004a062a c1f805                   sar       eax, 5
004a062d 3bc8                     cmp       ecx, eax
004a062f 7325                     jae       0x4a0656
004a0631 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a0634 8b4308                   mov       eax, dword ptr [ebx + 8]
004a0637 51                       push      ecx
004a0638 53                       push      ebx
004a0639 8d55cc                   lea       edx, [ebp - 0x34]
004a063c 52                       push      edx
004a063d 6a01                     push      1
004a063f 50                       push      eax
004a0640 89450c                   mov       dword ptr [ebp + 0xc], eax
004a0643 e8680e0000               call      0x4a14b0
004a0648 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004a064b 83c414                   add       esp, 0x14
004a064e 83c020                   add       eax, 0x20
004a0651 894308                   mov       dword ptr [ebx + 8], eax
004a0654 eb11                     jmp       0x4a0667
004a0656 8b4308                   mov       eax, dword ptr [ebx + 8]
004a0659 8d4dcc                   lea       ecx, [ebp - 0x34]
004a065c 51                       push      ecx
004a065d 6a01                     push      1
004a065f 50                       push      eax
004a0660 8bcb                     mov       ecx, ebx
004a0662 e849150000               call      0x4a1bb0
004a0667 8d4dd0                   lea       ecx, [ebp - 0x30]
004a066a c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004a0671 e8da2d5b00               call      0xa53450
004a0676 8b4508                   mov       eax, dword ptr [ebp + 8]
004a0679 8b8f6c010000             mov       ecx, dword ptr [edi + 0x16c]
004a067f 83c004                   add       eax, 4
004a0682 3bc1                     cmp       eax, ecx
004a0684 894508                   mov       dword ptr [ebp + 8], eax
004a0687 0f8579feffff             jne       0x4a0506
004a068d 8a4760                   mov       al, byte ptr [edi + 0x60]
004a0690 84c0                     test      al, al
004a0692 7416                     je        0x4a06aa
004a0694 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a069a 8b08                     mov       ecx, dword ptr [eax]
004a069c 85c9                     test      ecx, ecx
004a069e 7503                     jne       0x4a06a3
004a06a0 8d4808                   lea       ecx, [eax + 8]
004a06a3 c7412424faffff           mov       dword ptr [ecx + 0x24], 0xfffffa24
004a06aa 8a4769                   mov       al, byte ptr [edi + 0x69]
004a06ad 84c0                     test      al, al
004a06af 7409                     je        0x4a06ba
004a06b1 8a5768                   mov       dl, byte ptr [edi + 0x68]
004a06b4 889640050000             mov       byte ptr [esi + 0x540], dl
004a06ba 8a4762                   mov       al, byte ptr [edi + 0x62]
004a06bd 84c0                     test      al, al
004a06bf 7414                     je        0x4a06d5
004a06c1 c7862005000001000000     mov       dword ptr [esi + 0x520], 1
004a06cb c786e400000021020000     mov       dword ptr [esi + 0xe4], 0x221
004a06d5 8a476a                   mov       al, byte ptr [edi + 0x6a]
004a06d8 84c0                     test      al, al
004a06da 7407                     je        0x4a06e3
004a06dc c6864004000001           mov       byte ptr [esi + 0x440], 1
004a06e3 33db                     xor       ebx, ebx
004a06e5 8b8e24020000             mov       ecx, dword ptr [esi + 0x224]
004a06eb 85c9                     test      ecx, ecx
004a06ed 7420                     je        0x4a070f
004a06ef 8b8628020000             mov       eax, dword ptr [esi + 0x228]
004a06f5 2bc1                     sub       eax, ecx
004a06f7 c1f802                   sar       eax, 2
004a06fa 3bd8                     cmp       ebx, eax
004a06fc 7311                     jae       0x4a070f
004a06fe 8b1499                   mov       edx, dword ptr [ecx + ebx*4]
004a0701 8b06                     mov       eax, dword ptr [esi]
004a0703 52                       push      edx
004a0704 8bce                     mov       ecx, esi
004a0706 ff9024020000             call      dword ptr [eax + 0x224]
004a070c 43                       inc       ebx
004a070d ebd6                     jmp       0x4a06e5
004a070f 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004a0715 85c9                     test      ecx, ecx
004a0717 0f84ef000000             je        0x4a080c
004a071d 8a87b4000000             mov       al, byte ptr [edi + 0xb4]
004a0723 84c0                     test      al, al
004a0725 0f84e1000000             je        0x4a080c
004a072b 6a01                     push      1
004a072d e88e170700               call      0x511ec0
004a0732 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a0738 8b8fb8000000             mov       ecx, dword ptr [edi + 0xb8]
004a073e 898804010000             mov       dword ptr [eax + 0x104], ecx
004a0744 d987c0000000             fld       dword ptr [edi + 0xc0]
004a074a e8f50d7600               call      0xc01544
004a074f d987bc000000             fld       dword ptr [edi + 0xbc]
004a0755 8b9ef8000000             mov       ebx, dword ptr [esi + 0xf8]
004a075b 89450c                   mov       dword ptr [ebp + 0xc], eax
004a075e e8e10d7600               call      0xc01544
004a0763 894508                   mov       dword ptr [ebp + 8], eax
004a0766 db4508                   fild      dword ptr [ebp + 8]
004a0769 d99b08010000             fstp      dword ptr [ebx + 0x108]
004a076f db450c                   fild      dword ptr [ebp + 0xc]
004a0772 d99b0c010000             fstp      dword ptr [ebx + 0x10c]
004a0778 8b96f8000000             mov       edx, dword ptr [esi + 0xf8]
004a077e 8b87c4000000             mov       eax, dword ptr [edi + 0xc4]
004a0784 898210010000             mov       dword ptr [edx + 0x110], eax
004a078a 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004a0790 8a97c8000000             mov       dl, byte ptr [edi + 0xc8]
004a0796 88911c010000             mov       byte ptr [ecx + 0x11c], dl
004a079c 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a07a2 8b8fcc000000             mov       ecx, dword ptr [edi + 0xcc]
004a07a8 898820010000             mov       dword ptr [eax + 0x120], ecx
004a07ae 8b96f8000000             mov       edx, dword ptr [esi + 0xf8]
004a07b4 8b87d0000000             mov       eax, dword ptr [edi + 0xd0]
004a07ba 898230010000             mov       dword ptr [edx + 0x130], eax
004a07c0 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004a07c6 8b97d4000000             mov       edx, dword ptr [edi + 0xd4]
004a07cc 899134010000             mov       dword ptr [ecx + 0x134], edx
004a07d2 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
004a07d8 8b8fd8000000             mov       ecx, dword ptr [edi + 0xd8]
004a07de 898838010000             mov       dword ptr [eax + 0x138], ecx
004a07e4 8b96f8000000             mov       edx, dword ptr [esi + 0xf8]
004a07ea 8b87dc000000             mov       eax, dword ptr [edi + 0xdc]
004a07f0 898240010000             mov       dword ptr [edx + 0x140], eax
004a07f6 8b16                     mov       edx, dword ptr [esi]
004a07f8 8bce                     mov       ecx, esi
004a07fa ff92c0000000             call      dword ptr [edx + 0xc0]
004a0800 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004a0806 50                       push      eax
004a0807 e824160700               call      0x511e30
004a080c 8b7f64                   mov       edi, dword ptr [edi + 0x64]
004a080f 83ffff                   cmp       edi, -1
004a0812 740b                     je        0x4a081f
004a0814 8b06                     mov       eax, dword ptr [esi]
004a0816 57                       push      edi
004a0817 8bce                     mov       ecx, esi
004a0819 ff90c0010000             call      dword ptr [eax + 0x1c0]
004a081f 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004a0822 5f                       pop       edi
004a0823 5e                       pop       esi
004a0824 64890d00000000           mov       dword ptr fs:[0], ecx
004a082b 5b                       pop       ebx
004a082c 8be5                     mov       esp, ebp
004a082e 5d                       pop       ebp
004a082f c20800                   ret       8
004a0832 cc                       int3      
004a0833 cc                       int3      
004a0834 cc                       int3      
004a0835 cc                       int3      
004a0836 cc                       int3      
004a0837 cc                       int3      
004a0838 cc                       int3      
004a0839 cc                       int3      
004a083a cc                       int3      
004a083b cc                       int3      

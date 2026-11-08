004b20d0 55                       push      ebp
004b20d1 8bec                     mov       ebp, esp
004b20d3 51                       push      ecx
004b20d4 53                       push      ebx
004b20d5 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004b20d8 56                       push      esi
004b20d9 57                       push      edi
004b20da 53                       push      ebx
004b20db 8bf1                     mov       esi, ecx
004b20dd e82ebc0300               call      0x4edd10
004b20e2 8b03                     mov       eax, dword ptr [ebx]
004b20e4 6a21                     push      0x21
004b20e6 8bcb                     mov       ecx, ebx
004b20e8 ff502c                   call      dword ptr [eax + 0x2c]
004b20eb 84c0                     test      al, al
004b20ed 7408                     je        0x4b20f7
004b20ef 53                       push      ebx
004b20f0 8bce                     mov       ecx, esi
004b20f2 e809490000               call      0x4b6a00
004b20f7 8dbe94120000             lea       edi, [esi + 0x1294]
004b20fd c7450812000000           mov       dword ptr [ebp + 8], 0x12
004b2104 8b07                     mov       eax, dword ptr [edi]
004b2106 85c0                     test      eax, eax
004b2108 7413                     je        0x4b211d
004b210a 8bc8                     mov       ecx, eax
004b210c 8b11                     mov       edx, dword ptr [ecx]
004b210e ff5208                   call      dword ptr [edx + 8]
004b2111 84c0                     test      al, al
004b2113 7408                     je        0x4b211d
004b2115 8b0f                     mov       ecx, dword ptr [edi]
004b2117 8b01                     mov       eax, dword ptr [ecx]
004b2119 53                       push      ebx
004b211a ff501c                   call      dword ptr [eax + 0x1c]
004b211d 8b4508                   mov       eax, dword ptr [ebp + 8]
004b2120 83c704                   add       edi, 4
004b2123 48                       dec       eax
004b2124 894508                   mov       dword ptr [ebp + 8], eax
004b2127 75db                     jne       0x4b2104
004b2129 8b8edc120000             mov       ecx, dword ptr [esi + 0x12dc]
004b212f 85c9                     test      ecx, ecx
004b2131 7406                     je        0x4b2139
004b2133 53                       push      ebx
004b2134 e887360b00               call      0x5657c0
004b2139 3bde                     cmp       ebx, esi
004b213b 0f85bf000000             jne       0x4b2200
004b2141 8b16                     mov       edx, dword ptr [esi]
004b2143 6a00                     push      0
004b2145 8bce                     mov       ecx, esi
004b2147 ff9210010000             call      dword ptr [edx + 0x110]
004b214d 8b06                     mov       eax, dword ptr [esi]
004b214f 6a01                     push      1
004b2151 8bce                     mov       ecx, esi
004b2153 ff9010010000             call      dword ptr [eax + 0x110]
004b2159 8b16                     mov       edx, dword ptr [esi]
004b215b 6a02                     push      2
004b215d 8bce                     mov       ecx, esi
004b215f ff9210010000             call      dword ptr [edx + 0x110]
004b2165 8b06                     mov       eax, dword ptr [esi]
004b2167 6a04                     push      4
004b2169 8bce                     mov       ecx, esi
004b216b ff9010010000             call      dword ptr [eax + 0x110]
004b2171 8b16                     mov       edx, dword ptr [esi]
004b2173 6a05                     push      5
004b2175 8bce                     mov       ecx, esi
004b2177 ff9210010000             call      dword ptr [edx + 0x110]
004b217d 8b06                     mov       eax, dword ptr [esi]
004b217f 6a06                     push      6
004b2181 8bce                     mov       ecx, esi
004b2183 ff9010010000             call      dword ptr [eax + 0x110]
004b2189 8b16                     mov       edx, dword ptr [esi]
004b218b 6a07                     push      7
004b218d 8bce                     mov       ecx, esi
004b218f ff9210010000             call      dword ptr [edx + 0x110]
004b2195 8b06                     mov       eax, dword ptr [esi]
004b2197 6a08                     push      8
004b2199 8bce                     mov       ecx, esi
004b219b ff9010010000             call      dword ptr [eax + 0x110]
004b21a1 8b16                     mov       edx, dword ptr [esi]
004b21a3 6a09                     push      9
004b21a5 8bce                     mov       ecx, esi
004b21a7 ff9210010000             call      dword ptr [edx + 0x110]
004b21ad a16c310001               mov       eax, dword ptr [0x100316c]
004b21b2 8b4858                   mov       ecx, dword ptr [eax + 0x58]
004b21b5 39b170060000             cmp       dword ptr [ecx + 0x670], esi
004b21bb 7543                     jne       0x4b2200
004b21bd 8b16                     mov       edx, dword ptr [esi]
004b21bf 8bce                     mov       ecx, esi
004b21c1 ff9234020000             call      dword ptr [edx + 0x234]
004b21c7 85c0                     test      eax, eax
004b21c9 750f                     jne       0x4b21da
004b21cb a16c310001               mov       eax, dword ptr [0x100316c]
004b21d0 8b4858                   mov       ecx, dword ptr [eax + 0x58]
004b21d3 6a01                     push      1
004b21d5 e8168b4f00               call      0x9aacf0
004b21da 8b0d6c310001             mov       ecx, dword ptr [0x100316c]
004b21e0 8b4958                   mov       ecx, dword ptr [ecx + 0x58]
004b21e3 8a81d8060000             mov       al, byte ptr [ecx + 0x6d8]
004b21e9 84c0                     test      al, al
004b21eb 740c                     je        0x4b21f9
004b21ed c7817006000000000000     mov       dword ptr [ecx + 0x670], 0
004b21f7 eb07                     jmp       0x4b2200
004b21f9 6a00                     push      0
004b21fb e8a0d64f00               call      0x9af8a0
004b2200 399ef0040000             cmp       dword ptr [esi + 0x4f0], ebx
004b2206 750c                     jne       0x4b2214
004b2208 8b16                     mov       edx, dword ptr [esi]
004b220a 6a00                     push      0
004b220c 8bce                     mov       ecx, esi
004b220e ff9228030000             call      dword ptr [edx + 0x328]
004b2214 6a00                     push      0
004b2216 687c28f400               push      0xf4287c
004b221b 681009f400               push      0xf40910
004b2220 6a00                     push      0
004b2222 53                       push      ebx
004b2223 e8e3ea7400               call      0xc00d0b
004b2228 83c414                   add       esp, 0x14
004b222b 85c0                     test      eax, eax
004b222d 894508                   mov       dword ptr [ebp + 8], eax
004b2230 0f8492000000             je        0x4b22c8
004b2236 8d4508                   lea       eax, [ebp + 8]
004b2239 50                       push      eax
004b223a 8d4dfc                   lea       ecx, [ebp - 4]
004b223d 8dbebc190000             lea       edi, [esi + 0x19bc]
004b2243 51                       push      ecx
004b2244 8bcf                     mov       ecx, edi
004b2246 e8952a5b00               call      0xa64ce0
004b224b 8b5dfc                   mov       ebx, dword ptr [ebp - 4]
004b224e 3b9ec4190000             cmp       ebx, dword ptr [esi + 0x19c4]
004b2254 7429                     je        0x4b227f
004b2256 8d530c                   lea       edx, [ebx + 0xc]
004b2259 52                       push      edx
004b225a 8d45fc                   lea       eax, [ebp - 4]
004b225d 50                       push      eax
004b225e 8bcf                     mov       ecx, edi
004b2260 c745fc00000000           mov       dword ptr [ebp - 4], 0
004b2267 e854540000               call      0x4b76c0
004b226c 8bc8                     mov       ecx, eax
004b226e e8dd426600               call      0xb16550
004b2273 53                       push      ebx
004b2274 8d4dfc                   lea       ecx, [ebp - 4]
004b2277 51                       push      ecx
004b2278 8bcf                     mov       ecx, edi
004b227a e8719c2200               call      0x6dbef0
004b227f 8d5508                   lea       edx, [ebp + 8]
004b2282 52                       push      edx
004b2283 8d45fc                   lea       eax, [ebp - 4]
004b2286 8dbe94190000             lea       edi, [esi + 0x1994]
004b228c 50                       push      eax
004b228d 8bcf                     mov       ecx, edi
004b228f e84c2a5b00               call      0xa64ce0
004b2294 8b5dfc                   mov       ebx, dword ptr [ebp - 4]
004b2297 3b9e9c190000             cmp       ebx, dword ptr [esi + 0x199c]
004b229d 7429                     je        0x4b22c8
004b229f 8d4b0c                   lea       ecx, [ebx + 0xc]
004b22a2 51                       push      ecx
004b22a3 8d5508                   lea       edx, [ebp + 8]
004b22a6 52                       push      edx
004b22a7 8bcf                     mov       ecx, edi
004b22a9 c7450800000000           mov       dword ptr [ebp + 8], 0
004b22b0 e80b540000               call      0x4b76c0
004b22b5 8bc8                     mov       ecx, eax
004b22b7 e894426600               call      0xb16550
004b22bc 53                       push      ebx
004b22bd 8d4508                   lea       eax, [ebp + 8]
004b22c0 50                       push      eax
004b22c1 8bcf                     mov       ecx, edi
004b22c3 e8289c2200               call      0x6dbef0
004b22c8 5f                       pop       edi
004b22c9 5e                       pop       esi
004b22ca 5b                       pop       ebx
004b22cb 8be5                     mov       esp, ebp
004b22cd 5d                       pop       ebp
004b22ce c20400                   ret       4
004b22d1 cc                       int3      
004b22d2 cc                       int3      
004b22d3 cc                       int3      
004b22d4 cc                       int3      
004b22d5 cc                       int3      
004b22d6 cc                       int3      
004b22d7 cc                       int3      
004b22d8 cc                       int3      
004b22d9 cc                       int3      
004b22da cc                       int3      
004b22db cc                       int3      
004b22dc cc                       int3      
004b22dd cc                       int3      
004b22de cc                       int3      
004b22df cc                       int3      
004b22e0 55                       push      ebp
004b22e1 8bec                     mov       ebp, esp
004b22e3 6aff                     push      -1
004b22e5 68d574c500               push      0xc574d5
004b22ea 64a100000000             mov       eax, dword ptr fs:[0]

004f3f30 55                       push      ebp
004f3f31 8bec                     mov       ebp, esp
004f3f33 83ec0c                   sub       esp, 0xc
004f3f36 53                       push      ebx
004f3f37 56                       push      esi
004f3f38 57                       push      edi
004f3f39 8bf9                     mov       edi, ecx
004f3f3b 33db                     xor       ebx, ebx
004f3f3d 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f3f43 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f3f49 85d2                     test      edx, edx
004f3f4b 895df8                   mov       dword ptr [ebp - 8], ebx
004f3f4e 7504                     jne       0x4f3f54
004f3f50 33c0                     xor       eax, eax
004f3f52 eb0b                     jmp       0x4f3f5f
004f3f54 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f3f5a 2bc2                     sub       eax, edx
004f3f5c c1f802                   sar       eax, 2
004f3f5f 3bd8                     cmp       ebx, eax
004f3f61 0f8d30020000             jge       0x4f4197
004f3f67 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f3f6d 85d2                     test      edx, edx
004f3f6f 7419                     je        0x4f3f8a
004f3f71 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f3f77 2bc2                     sub       eax, edx
004f3f79 c1f802                   sar       eax, 2
004f3f7c 3bd8                     cmp       ebx, eax
004f3f7e 730a                     jae       0x4f3f8a
004f3f80 8bc2                     mov       eax, edx
004f3f82 8b0c98                   mov       ecx, dword ptr [eax + ebx*4]
004f3f85 8d0498                   lea       eax, [eax + ebx*4]
004f3f88 eb02                     jmp       0x4f3f8c
004f3f8a 33c9                     xor       ecx, ecx
004f3f8c 8b11                     mov       edx, dword ptr [ecx]
004f3f8e 6a11                     push      0x11
004f3f90 ff522c                   call      dword ptr [edx + 0x2c]
004f3f93 84c0                     test      al, al
004f3f95 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f3f9b 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f3fa1 0f8427010000             je        0x4f40ce
004f3fa7 85d2                     test      edx, edx
004f3fa9 7419                     je        0x4f3fc4
004f3fab 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f3fb1 2bc2                     sub       eax, edx
004f3fb3 c1f802                   sar       eax, 2
004f3fb6 3bd8                     cmp       ebx, eax
004f3fb8 730a                     jae       0x4f3fc4
004f3fba 8bc2                     mov       eax, edx
004f3fbc 8b3498                   mov       esi, dword ptr [eax + ebx*4]
004f3fbf 8d0498                   lea       eax, [eax + ebx*4]
004f3fc2 eb02                     jmp       0x4f3fc6
004f3fc4 33f6                     xor       esi, esi
004f3fc6 3bf7                     cmp       esi, edi
004f3fc8 0f84fa000000             je        0x4f40c8
004f3fce 8b4508                   mov       eax, dword ptr [ebp + 8]
004f3fd1 8b17                     mov       edx, dword ptr [edi]
004f3fd3 50                       push      eax
004f3fd4 8bcf                     mov       ecx, edi
004f3fd6 c645ff00                 mov       byte ptr [ebp - 1], 0
004f3fda ff9260040000             call      dword ptr [edx + 0x460]
004f3fe0 8bd8                     mov       ebx, eax
004f3fe2 85db                     test      ebx, ebx
004f3fe4 7424                     je        0x4f400a
004f3fe6 8d4b34                   lea       ecx, [ebx + 0x34]
004f3fe9 e872e0f0ff               call      0x402060
004f3fee 85c0                     test      eax, eax
004f3ff0 8d4b2c                   lea       ecx, [ebx + 0x2c]
004f3ff3 0f9545ff                 setne     byte ptr [ebp - 1]
004f3ff7 e864e0f0ff               call      0x402060
004f3ffc 85c0                     test      eax, eax
004f3ffe 8a45ff                   mov       al, byte ptr [ebp - 1]
004f4001 0f95c3                   setne     bl
004f4004 84c0                     test      al, al
004f4006 7411                     je        0x4f4019
004f4008 eb03                     jmp       0x4f400d
004f400a 8a5dff                   mov       bl, byte ptr [ebp - 1]
004f400d 56                       push      esi
004f400e 8bcf                     mov       ecx, edi
004f4010 e8bb4bffff               call      0x4e8bd0
004f4015 84c0                     test      al, al
004f4017 7518                     jne       0x4f4031
004f4019 84db                     test      bl, bl
004f401b 0f84a4000000             je        0x4f40c5
004f4021 56                       push      esi
004f4022 8bcf                     mov       ecx, edi
004f4024 e8a74bffff               call      0x4e8bd0
004f4029 84c0                     test      al, al
004f402b 0f8594000000             jne       0x4f40c5
004f4031 8bce                     mov       ecx, esi
004f4033 e8c847ffff               call      0x4e8800
004f4038 84c0                     test      al, al
004f403a 0f8585000000             jne       0x4f40c5
004f4040 8b16                     mov       edx, dword ptr [esi]
004f4042 8bce                     mov       ecx, esi
004f4044 ff9230020000             call      dword ptr [edx + 0x230]
004f404a 83f804                   cmp       eax, 4
004f404d 7510                     jne       0x4f405f
004f404f 8b06                     mov       eax, dword ptr [esi]
004f4051 6a08                     push      8
004f4053 8bce                     mov       ecx, esi
004f4055 ff9010040000             call      dword ptr [eax + 0x410]
004f405b 84c0                     test      al, al
004f405d 7466                     je        0x4f40c5
004f405f 8b16                     mov       edx, dword ptr [esi]
004f4061 8bce                     mov       ecx, esi
004f4063 ff92dc030000             call      dword ptr [edx + 0x3dc]
004f4069 84c0                     test      al, al
004f406b 7558                     jne       0x4f40c5
004f406d 8b07                     mov       eax, dword ptr [edi]
004f406f 56                       push      esi
004f4070 8b7508                   mov       esi, dword ptr [ebp + 8]
004f4073 56                       push      esi
004f4074 8bcf                     mov       ecx, edi
004f4076 ff9094060000             call      dword ptr [eax + 0x694]
004f407c 84c0                     test      al, al
004f407e 7445                     je        0x4f40c5
004f4080 8b9f601d0000             mov       ebx, dword ptr [edi + 0x1d60]
004f4086 8d3476                   lea       esi, [esi + esi*2]
004f4089 c1e605                   shl       esi, 5
004f408c 6a00                     push      0
004f408e 03f3                     add       esi, ebx
004f4090 e85ba03b00               call      0x8ae0f0
004f4095 99                       cdq       
004f4096 b910270000               mov       ecx, 0x2710
004f409b f7f9                     idiv      ecx
004f409d 83c404                   add       esp, 4
004f40a0 8d4e08                   lea       ecx, [esi + 8]
004f40a3 8955f4                   mov       dword ptr [ebp - 0xc], edx
004f40a6 db45f4                   fild      dword ptr [ebp - 0xc]
004f40a9 d95df4                   fstp      dword ptr [ebp - 0xc]
004f40ac e8fff2f3ff               call      0x4333b0
004f40b1 d80dd8b9cc00             fmul      dword ptr [0xccb9d8]
004f40b7 d85df4                   fcomp     dword ptr [ebp - 0xc]
004f40ba dfe0                     fnstsw    ax
004f40bc f6c441                   test      ah, 0x41
004f40bf 0f8416010000             je        0x4f41db
004f40c5 8b5df8                   mov       ebx, dword ptr [ebp - 8]
004f40c8 43                       inc       ebx
004f40c9 e96ffeffff               jmp       0x4f3f3d
004f40ce 85d2                     test      edx, edx
004f40d0 741d                     je        0x4f40ef
004f40d2 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f40d8 2bc2                     sub       eax, edx
004f40da c1f802                   sar       eax, 2
004f40dd 3bd8                     cmp       ebx, eax
004f40df 730e                     jae       0x4f40ef
004f40e1 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f40e7 8b0c9a                   mov       ecx, dword ptr [edx + ebx*4]
004f40ea 8d049a                   lea       eax, [edx + ebx*4]
004f40ed eb02                     jmp       0x4f40f1
004f40ef 33c9                     xor       ecx, ecx
004f40f1 8b01                     mov       eax, dword ptr [ecx]
004f40f3 6821020000               push      0x221
004f40f8 ff502c                   call      dword ptr [eax + 0x2c]
004f40fb 84c0                     test      al, al
004f40fd 74c9                     je        0x4f40c8
004f40ff 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f4105 8b9190000000             mov       edx, dword ptr [ecx + 0x90]
004f410b 85d2                     test      edx, edx
004f410d 7419                     je        0x4f4128
004f410f 8b8194000000             mov       eax, dword ptr [ecx + 0x94]
004f4115 2bc2                     sub       eax, edx
004f4117 c1f802                   sar       eax, 2
004f411a 3bd8                     cmp       ebx, eax
004f411c 730a                     jae       0x4f4128
004f411e 8bca                     mov       ecx, edx
004f4120 8b3499                   mov       esi, dword ptr [ecx + ebx*4]
004f4123 8d0499                   lea       eax, [ecx + ebx*4]
004f4126 eb02                     jmp       0x4f412a
004f4128 33f6                     xor       esi, esi
004f412a 56                       push      esi
004f412b 8bcf                     mov       ecx, edi
004f412d e89e4affff               call      0x4e8bd0
004f4132 84c0                     test      al, al
004f4134 7492                     je        0x4f40c8
004f4136 8b4508                   mov       eax, dword ptr [ebp + 8]
004f4139 8b17                     mov       edx, dword ptr [edi]
004f413b 56                       push      esi
004f413c 50                       push      eax
004f413d 8bcf                     mov       ecx, edi
004f413f ff9294060000             call      dword ptr [edx + 0x694]
004f4145 84c0                     test      al, al
004f4147 0f847bffffff             je        0x4f40c8
004f414d 8b7508                   mov       esi, dword ptr [ebp + 8]
004f4150 8b87601d0000             mov       eax, dword ptr [edi + 0x1d60]
004f4156 8d3476                   lea       esi, [esi + esi*2]
004f4159 c1e605                   shl       esi, 5
004f415c 6a00                     push      0
004f415e 03f0                     add       esi, eax
004f4160 e88b9f3b00               call      0x8ae0f0
004f4165 99                       cdq       
004f4166 b910270000               mov       ecx, 0x2710
004f416b f7f9                     idiv      ecx
004f416d 83c404                   add       esp, 4
004f4170 8d4e18                   lea       ecx, [esi + 0x18]
004f4173 8955f4                   mov       dword ptr [ebp - 0xc], edx
004f4176 db45f4                   fild      dword ptr [ebp - 0xc]
004f4179 d95df4                   fstp      dword ptr [ebp - 0xc]
004f417c e82ff2f3ff               call      0x4333b0
004f4181 d80dd8b9cc00             fmul      dword ptr [0xccb9d8]
004f4187 d85df4                   fcomp     dword ptr [ebp - 0xc]
004f418a dfe0                     fnstsw    ax
004f418c f6c441                   test      ah, 0x41
004f418f 744a                     je        0x4f41db
004f4191 43                       inc       ebx
004f4192 e9a6fdffff               jmp       0x4f3f3d
004f4197 8b7508                   mov       esi, dword ptr [ebp + 8]
004f419a 8b9f601d0000             mov       ebx, dword ptr [edi + 0x1d60]
004f41a0 8d3476                   lea       esi, [esi + esi*2]
004f41a3 c1e605                   shl       esi, 5
004f41a6 6a00                     push      0
004f41a8 03f3                     add       esi, ebx
004f41aa e8419f3b00               call      0x8ae0f0
004f41af 99                       cdq       
004f41b0 b910270000               mov       ecx, 0x2710
004f41b5 f7f9                     idiv      ecx
004f41b7 83c404                   add       esp, 4
004f41ba 8d4e10                   lea       ecx, [esi + 0x10]
004f41bd 895508                   mov       dword ptr [ebp + 8], edx
004f41c0 db4508                   fild      dword ptr [ebp + 8]
004f41c3 d95d08                   fstp      dword ptr [ebp + 8]
004f41c6 e8e5f1f3ff               call      0x4333b0
004f41cb d80dd8b9cc00             fmul      dword ptr [0xccb9d8]
004f41d1 d85d08                   fcomp     dword ptr [ebp + 8]
004f41d4 dfe0                     fnstsw    ax
004f41d6 f6c441                   test      ah, 0x41
004f41d9 750b                     jne       0x4f41e6
004f41db 5f                       pop       edi
004f41dc 5e                       pop       esi
004f41dd b001                     mov       al, 1
004f41df 5b                       pop       ebx
004f41e0 8be5                     mov       esp, ebp
004f41e2 5d                       pop       ebp
004f41e3 c20400                   ret       4
004f41e6 5f                       pop       edi
004f41e7 5e                       pop       esi
004f41e8 32c0                     xor       al, al
004f41ea 5b                       pop       ebx
004f41eb 8be5                     mov       esp, ebp
004f41ed 5d                       pop       ebp
004f41ee c20400                   ret       4
004f41f1 cc                       int3      
004f41f2 cc                       int3      
004f41f3 cc                       int3      
004f41f4 cc                       int3      
004f41f5 cc                       int3      
004f41f6 cc                       int3      
004f41f7 cc                       int3      
004f41f8 cc                       int3      
004f41f9 cc                       int3      
004f41fa cc                       int3      
004f41fb cc                       int3      
004f41fc cc                       int3      
004f41fd cc                       int3      
004f41fe cc                       int3      
004f41ff cc                       int3      
004f4200 55                       push      ebp
004f4201 8bec                     mov       ebp, esp
004f4203 51                       push      ecx
004f4204 53                       push      ebx
004f4205 56                       push      esi
004f4206 33f6                     xor       esi, esi
004f4208 57                       push      edi
004f4209 8bf9                     mov       edi, ecx
004f420b 8975fc                   mov       dword ptr [ebp - 4], esi
004f420e 8bff                     mov       edi, edi
004f4210 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f4216 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f4219 85d2                     test      edx, edx
004f421b 7504                     jne       0x4f4221
004f421d 33c0                     xor       eax, eax
004f421f eb08                     jmp       0x4f4229
004f4221 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f4224 2bc2                     sub       eax, edx
004f4226 c1f802                   sar       eax, 2
004f4229 3bf0                     cmp       esi, eax
004f422b 7d70                     jge       0x4f429d
004f422d 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f4230 85d2                     test      edx, edx
004f4232 7416                     je        0x4f424a
004f4234 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f4237 2bc2                     sub       eax, edx
004f4239 c1f802                   sar       eax, 2
004f423c 3bf0                     cmp       esi, eax
004f423e 730a                     jae       0x4f424a
004f4240 8bc2                     mov       eax, edx
004f4242 8b0cb0                   mov       ecx, dword ptr [eax + esi*4]
004f4245 8d04b0                   lea       eax, [eax + esi*4]
004f4248 eb02                     jmp       0x4f424c
004f424a 33c9                     xor       ecx, ecx
004f424c 8b11                     mov       edx, dword ptr [ecx]
004f424e 6a11                     push      0x11
004f4250 ff522c                   call      dword ptr [edx + 0x2c]
004f4253 84c0                     test      al, al
004f4255 7440                     je        0x4f4297
004f4257 8b8f00010000             mov       ecx, dword ptr [edi + 0x100]
004f425d 8b5110                   mov       edx, dword ptr [ecx + 0x10]
004f4260 85d2                     test      edx, edx
004f4262 7416                     je        0x4f427a
004f4264 8b4114                   mov       eax, dword ptr [ecx + 0x14]
004f4267 2bc2                     sub       eax, edx
004f4269 c1f802                   sar       eax, 2
004f426c 3bf0                     cmp       esi, eax
004f426e 730a                     jae       0x4f427a
004f4270 8bc2                     mov       eax, edx
004f4272 8b0cb0                   mov       ecx, dword ptr [eax + esi*4]
004f4275 8d04b0                   lea       eax, [eax + esi*4]
004f4278 eb02                     jmp       0x4f427c
004f427a 33c9                     xor       ecx, ecx
004f427c 8b11                     mov       edx, dword ptr [ecx]
004f427e ff92c4010000             call      dword ptr [edx + 0x1c4]
004f4284 8bd8                     mov       ebx, eax
004f4286 8b07                     mov       eax, dword ptr [edi]
004f4288 8bcf                     mov       ecx, edi
004f428a ff90c4010000             call      dword ptr [eax + 0x1c4]
004f4290 3bd8                     cmp       ebx, eax
004f4292 7503                     jne       0x4f4297
004f4294 ff45fc                   inc       dword ptr [ebp - 4]
004f4297 46                       inc       esi
004f4298 e973ffffff               jmp       0x4f4210
004f429d 8b45fc                   mov       eax, dword ptr [ebp - 4]
004f42a0 5f                       pop       edi
004f42a1 5e                       pop       esi
004f42a2 5b                       pop       ebx
004f42a3 8be5                     mov       esp, ebp
004f42a5 5d                       pop       ebp
004f42a6 c3                       ret       
004f42a7 cc                       int3      
004f42a8 cc                       int3      
004f42a9 cc                       int3      
004f42aa cc                       int3      
004f42ab cc                       int3      
004f42ac cc                       int3      
004f42ad cc                       int3      
004f42ae cc                       int3      
004f42af cc                       int3      
004f42b0 55                       push      ebp
004f42b1 8bec                     mov       ebp, esp
004f42b3 83ec08                   sub       esp, 8
004f42b6 53                       push      ebx
004f42b7 56                       push      esi
004f42b8 8b7508                   mov       esi, dword ptr [ebp + 8]
004f42bb 8b06                     mov       eax, dword ptr [esi]
004f42bd 83c0fc                   add       eax, -4
004f42c0 83f805                   cmp       eax, 5
004f42c3 57                       push      edi
004f42c4 8bf9                     mov       edi, ecx
004f42c6 7764                     ja        0x4f432c
004f42c8 ff248524444f00           jmp       dword ptr [eax*4 + 0x4f4424]
004f42cf 8b07                     mov       eax, dword ptr [edi]
004f42d1 6a0d                     push      0xd
004f42d3 8bcf                     mov       ecx, edi
004f42d5 ff90f0050000             call      dword ptr [eax + 0x5f0]
004f42db eb4f                     jmp       0x4f432c
004f42dd 8b17                     mov       edx, dword ptr [edi]
004f42df 8bcf                     mov       ecx, edi
004f42e1 ff9230020000             call      dword ptr [edx + 0x230]
004f42e7 83f80b                   cmp       eax, 0xb
004f42ea 7540                     jne       0x4f432c
004f42ec 8b07                     mov       eax, dword ptr [edi]
004f42ee 6a01                     push      1
004f42f0 6a01                     push      1
004f42f2 6a00                     push      0
004f42f4 6a0c                     push      0xc
004f42f6 8bcf                     mov       ecx, edi
004f42f8 ff902c020000             call      dword ptr [eax + 0x22c]
004f42fe 8b17                     mov       edx, dword ptr [edi]
004f4300 6a01                     push      1
004f4302 6a01                     push      1
004f4304 6a00                     push      0
004f4306 6a00                     push      0
004f4308 8bcf                     mov       ecx, edi
004f430a ff922c020000             call      dword ptr [edx + 0x22c]
004f4310 eb1a                     jmp       0x4f432c
004f4312 8b07                     mov       eax, dword ptr [edi]
004f4314 6a10                     push      0x10
004f4316 8bcf                     mov       ecx, edi
004f4318 ff90f0050000             call      dword ptr [eax + 0x5f0]
004f431e eb0c                     jmp       0x4f432c
004f4320 8b17                     mov       edx, dword ptr [edi]
004f4322 6a0d                     push      0xd
004f4324 8bcf                     mov       ecx, edi
004f4326 ff92f0050000             call      dword ptr [edx + 0x5f0]
004f432c 56                       push      esi
004f432d 8bcf                     mov       ecx, edi
004f432f e8dcaffbff               call      0x4af310
004f4334 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f433a 33c0                     xor       eax, eax
004f433c 8945fc                   mov       dword ptr [ebp - 4], eax
004f433f 8945f8                   mov       dword ptr [ebp - 8], eax
004f4342 8b87e8220000             mov       eax, dword ptr [edi + 0x22e8]
004f4348 85c0                     test      eax, eax
004f434a 0f84c8000000             je        0x4f4418
004f4350 8b97ec220000             mov       edx, dword ptr [edi + 0x22ec]
004f4356 2bd0                     sub       edx, eax
004f4358 b867666666               mov       eax, 0x66666667
004f435d f7ea                     imul      edx
004f435f c1fa04                   sar       edx, 4
004f4362 8bc2                     mov       eax, edx
004f4364 c1e81f                   shr       eax, 0x1f
004f4367 03c2                     add       eax, edx
004f4369 3945fc                   cmp       dword ptr [ebp - 4], eax
004f436c 0f83a6000000             jae       0x4f4418
004f4372 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004f4378 8b8728180000             mov       eax, dword ptr [edi + 0x1828]
004f437e 8d9f28180000             lea       ebx, [edi + 0x1828]
004f4384 33c2                     xor       eax, edx
004f4386 8b5304                   mov       edx, dword ptr [ebx + 4]
004f4389 2bc3                     sub       eax, ebx
004f438b 3bc2                     cmp       eax, edx
004f438d 740e                     je        0x4f439d
004f438f 6a3f                     push      0x3f
004f4391 53                       push      ebx
004f4392 e8192d6200               call      0xb170b0
004f4397 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f439d 8b4304                   mov       eax, dword ptr [ebx + 4]
004f43a0 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004f43a3 c1e002                   shl       eax, 2
004f43a6 8b3402                   mov       esi, dword ptr [edx + eax]
004f43a9 03d0                     add       edx, eax
004f43ab 33f2                     xor       esi, edx
004f43ad 3335dc012101             xor       esi, dword ptr [0x12101dc]
004f43b3 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004f43b6 03c2                     add       eax, edx
004f43b8 8b10                     mov       edx, dword ptr [eax]
004f43ba 33d0                     xor       edx, eax
004f43bc 3315dc012101             xor       edx, dword ptr [0x12101dc]
004f43c2 3bf2                     cmp       esi, edx
004f43c4 740e                     je        0x4f43d4
004f43c6 6a40                     push      0x40
004f43c8 53                       push      ebx
004f43c9 e8e22c6200               call      0xb170b0
004f43ce 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f43d4 8b87e8220000             mov       eax, dword ptr [edi + 0x22e8]
004f43da 8b5df8                   mov       ebx, dword ptr [ebp - 8]
004f43dd 8b541804                 mov       edx, dword ptr [eax + ebx + 4]
004f43e1 03c3                     add       eax, ebx
004f43e3 3bf2                     cmp       esi, edx
004f43e5 751f                     jne       0x4f4406
004f43e7 8b8718230000             mov       eax, dword ptr [edi + 0x2318]
004f43ed 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004f43f0 8b5508                   mov       edx, dword ptr [ebp + 8]
004f43f3 8d0488                   lea       eax, [eax + ecx*4]
004f43f6 8b0a                     mov       ecx, dword ptr [edx]
004f43f8 51                       push      ecx
004f43f9 8b08                     mov       ecx, dword ptr [eax]
004f43fb e8908e2500               call      0x74d290
004f4400 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f4406 8b55fc                   mov       edx, dword ptr [ebp - 4]
004f4409 8b45f8                   mov       eax, dword ptr [ebp - 8]
004f440c 42                       inc       edx
004f440d 8955fc                   mov       dword ptr [ebp - 4], edx
004f4410 83c028                   add       eax, 0x28
004f4413 e927ffffff               jmp       0x4f433f
004f4418 5f                       pop       edi
004f4419 5e                       pop       esi
004f441a 5b                       pop       ebx
004f441b 8be5                     mov       esp, ebp
004f441d 5d                       pop       ebp
004f441e c20400                   ret       4
004f4421 8d4900                   lea       ecx, [ecx]
004f4424 cf                       iretd     
004f4425 42                       inc       edx
004f4426 4f                       dec       edi
004f4427 00dd                     add       ch, bl
004f4429 42                       inc       edx
004f442a 4f                       dec       edi
004f442b 002c43                   add       byte ptr [ebx + eax*2], ch
004f442e 4f                       dec       edi
004f442f 002c43                   add       byte ptr [ebx + eax*2], ch
004f4432 4f                       dec       edi
004f4433 0012                     add       byte ptr [edx], dl
004f4435 43                       inc       ebx
004f4436 4f                       dec       edi
004f4437 0020                     add       byte ptr [eax], ah
004f4439 43                       inc       ebx
004f443a 4f                       dec       edi
004f443b 00cc                     add       ah, cl
004f443d cc                       int3      
004f443e cc                       int3      
004f443f cc                       int3      
004f4440 55                       push      ebp
004f4441 8bec                     mov       ebp, esp
004f4443 53                       push      ebx
004f4444 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004f4447 56                       push      esi
004f4448 57                       push      edi
004f4449 8bf1                     mov       esi, ecx
004f444b 33ff                     xor       edi, edi
004f444d 8d4900                   lea       ecx, [ecx]
004f4450 8b8608230000             mov       eax, dword ptr [esi + 0x2308]
004f4456 85c0                     test      eax, eax
004f4458 7432                     je        0x4f448c
004f445a 8b8e0c230000             mov       ecx, dword ptr [esi + 0x230c]
004f4460 2bc8                     sub       ecx, eax
004f4462 b8398ee338               mov       eax, 0x38e38e39
004f4467 f7e9                     imul      ecx
004f4469 c1fa03                   sar       edx, 3
004f446c 8bc2                     mov       eax, edx
004f446e c1e81f                   shr       eax, 0x1f
004f4471 03c2                     add       eax, edx
004f4473 3bf8                     cmp       edi, eax
004f4475 7315                     jae       0x4f448c
004f4477 8b8648230000             mov       eax, dword ptr [esi + 0x2348]
004f447d 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004f4480 8d04b8                   lea       eax, [eax + edi*4]
004f4483 53                       push      ebx
004f4484 e8d7a42500               call      0x74e960
004f4489 47                       inc       edi
004f448a ebc4                     jmp       0x4f4450
004f448c 53                       push      ebx
004f448d 8bce                     mov       ecx, esi
004f448f e83cdcfbff               call      0x4b20d0
004f4494 3bde                     cmp       ebx, esi
004f4496 7537                     jne       0x4f44cf
004f4498 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f449e 81c140100000             add       ecx, 0x1040
004f44a4 e8b7dbf0ff               call      0x402060
004f44a9 83f803                   cmp       eax, 3
004f44ac 7416                     je        0x4f44c4
004f44ae 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f44b4 81c140100000             add       ecx, 0x1040
004f44ba e8a1dbf0ff               call      0x402060
004f44bf 83f80a                   cmp       eax, 0xa
004f44c2 750b                     jne       0x4f44cf
004f44c4 8b16                     mov       edx, dword ptr [esi]
004f44c6 8bce                     mov       ecx, esi
004f44c8 ff524c                   call      dword ptr [edx + 0x4c]
004f44cb c6404c00                 mov       byte ptr [eax + 0x4c], 0
004f44cf 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004f44d5 33ff                     xor       edi, edi
004f44d7 3bc3                     cmp       eax, ebx
004f44d9 7506                     jne       0x4f44e1
004f44db 89be801b0000             mov       dword ptr [esi + 0x1b80], edi
004f44e1 399e7c1b0000             cmp       dword ptr [esi + 0x1b7c], ebx
004f44e7 7506                     jne       0x4f44ef
004f44e9 89be7c1b0000             mov       dword ptr [esi + 0x1b7c], edi
004f44ef 399e841b0000             cmp       dword ptr [esi + 0x1b84], ebx
004f44f5 7506                     jne       0x4f44fd
004f44f7 89be841b0000             mov       dword ptr [esi + 0x1b84], edi
004f44fd 399ef0040000             cmp       dword ptr [esi + 0x4f0], ebx
004f4503 750b                     jne       0x4f4510
004f4505 8b06                     mov       eax, dword ptr [esi]
004f4507 57                       push      edi
004f4508 8bce                     mov       ecx, esi
004f450a ff9028030000             call      dword ptr [eax + 0x328]
004f4510 399e84200000             cmp       dword ptr [esi + 0x2084], ebx
004f4516 7537                     jne       0x4f454f
004f4518 8b13                     mov       edx, dword ptr [ebx]
004f451a 6811020000               push      0x211
004f451f 8bcb                     mov       ecx, ebx
004f4521 ff522c                   call      dword ptr [edx + 0x2c]
004f4524 84c0                     test      al, al
004f4526 741c                     je        0x4f4544
004f4528 8b03                     mov       eax, dword ptr [ebx]
004f452a 8b3e                     mov       edi, dword ptr [esi]
004f452c 8bcb                     mov       ecx, ebx
004f452e ff9058030000             call      dword ptr [eax + 0x358]
004f4534 50                       push      eax
004f4535 8bce                     mov       ecx, esi
004f4537 ff9754030000             call      dword ptr [edi + 0x354]
004f453d 5f                       pop       edi
004f453e 5e                       pop       esi
004f453f 5b                       pop       ebx
004f4540 5d                       pop       ebp
004f4541 c20400                   ret       4
004f4544 8b16                     mov       edx, dword ptr [esi]
004f4546 57                       push      edi
004f4547 8bce                     mov       ecx, esi
004f4549 ff9254030000             call      dword ptr [edx + 0x354]
004f454f 5f                       pop       edi
004f4550 5e                       pop       esi
004f4551 5b                       pop       ebx
004f4552 5d                       pop       ebp
004f4553 c20400                   ret       4
004f4556 cc                       int3      
004f4557 cc                       int3      
004f4558 cc                       int3      
004f4559 cc                       int3      
004f455a cc                       int3      
004f455b cc                       int3      
004f455c cc                       int3      
004f455d cc                       int3      
004f455e cc                       int3      
004f455f cc                       int3      
004f4560 55                       push      ebp
004f4561 8bec                     mov       ebp, esp
004f4563 83ec1c                   sub       esp, 0x1c
004f4566 56                       push      esi
004f4567 8bf1                     mov       esi, ecx
004f4569 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f456f 85c9                     test      ecx, ecx
004f4571 0f8474050000             je        0x4f4aeb
004f4577 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004f457d 85c0                     test      eax, eax
004f457f 0f8466050000             je        0x4f4aeb
004f4585 8b96641d0000             mov       edx, dword ptr [esi + 0x1d64]
004f458b 2bd0                     sub       edx, eax
004f458d b8abaaaa2a               mov       eax, 0x2aaaaaab
004f4592 f7ea                     imul      edx
004f4594 c1fa04                   sar       edx, 4
004f4597 8bc2                     mov       eax, edx
004f4599 c1e81f                   shr       eax, 0x1f
004f459c 03c2                     add       eax, edx
004f459e 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f45a1 0f8444050000             je        0x4f4aeb
004f45a7 8b11                     mov       edx, dword ptr [ecx]
004f45a9 57                       push      edi
004f45aa 8bbe601d0000             mov       edi, dword ptr [esi + 0x1d60]
004f45b0 ff9294000000             call      dword ptr [edx + 0x94]
004f45b6 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f45b9 db45e4                   fild      dword ptr [ebp - 0x1c]
004f45bc 8b06                     mov       eax, dword ptr [esi]
004f45be 8bce                     mov       ecx, esi
004f45c0 d95df4                   fstp      dword ptr [ebp - 0xc]
004f45c3 ff9094000000             call      dword ptr [eax + 0x94]
004f45c9 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f45cc db45e4                   fild      dword ptr [ebp - 0x1c]
004f45cf 8d4f28                   lea       ecx, [edi + 0x28]
004f45d2 d95de8                   fstp      dword ptr [ebp - 0x18]
004f45d5 e886daf0ff               call      0x402060
004f45da 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f45dd db45e4                   fild      dword ptr [ebp - 0x1c]
004f45e0 d80da859cd00             fmul      dword ptr [0xcd59a8]
004f45e6 d86de8                   fsubr     dword ptr [ebp - 0x18]
004f45e9 d85df4                   fcomp     dword ptr [ebp - 0xc]
004f45ec dfe0                     fnstsw    ax
004f45ee f6c441                   test      ah, 0x41
004f45f1 750b                     jne       0x4f45fe
004f45f3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f45f6 c70100000000             mov       dword ptr [ecx], 0
004f45fc eb65                     jmp       0x4f4663
004f45fe 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f4604 8b11                     mov       edx, dword ptr [ecx]
004f4606 8bbe601d0000             mov       edi, dword ptr [esi + 0x1d60]
004f460c ff9294000000             call      dword ptr [edx + 0x94]
004f4612 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f4615 db45e4                   fild      dword ptr [ebp - 0x1c]
004f4618 8d4f28                   lea       ecx, [edi + 0x28]
004f461b d95df4                   fstp      dword ptr [ebp - 0xc]
004f461e e83ddaf0ff               call      0x402060
004f4623 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f4626 db45e4                   fild      dword ptr [ebp - 0x1c]
004f4629 8b06                     mov       eax, dword ptr [esi]
004f462b 8bce                     mov       ecx, esi
004f462d d80da859cd00             fmul      dword ptr [0xcd59a8]
004f4633 d95de8                   fstp      dword ptr [ebp - 0x18]
004f4636 ff9094000000             call      dword ptr [eax + 0x94]
004f463c 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f463f db45e4                   fild      dword ptr [ebp - 0x1c]
004f4642 d845e8                   fadd      dword ptr [ebp - 0x18]
004f4645 d85df4                   fcomp     dword ptr [ebp - 0xc]
004f4648 dfe0                     fnstsw    ax
004f464a f6c405                   test      ah, 5
004f464d 7a0b                     jp        0x4f465a
004f464f 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f4652 c70101000000             mov       dword ptr [ecx], 1
004f4658 eb09                     jmp       0x4f4663
004f465a 8b5508                   mov       edx, dword ptr [ebp + 8]
004f465d c70204000000             mov       dword ptr [edx], 4
004f4663 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f4669 8b01                     mov       eax, dword ptr [ecx]
004f466b 8bbe601d0000             mov       edi, dword ptr [esi + 0x1d60]
004f4671 ff9098000000             call      dword ptr [eax + 0x98]
004f4677 8b16                     mov       edx, dword ptr [esi]
004f4679 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f467c db45e4                   fild      dword ptr [ebp - 0x1c]
004f467f 8bce                     mov       ecx, esi
004f4681 d95df4                   fstp      dword ptr [ebp - 0xc]
004f4684 ff9298000000             call      dword ptr [edx + 0x98]
004f468a 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f468d db45e4                   fild      dword ptr [ebp - 0x1c]
004f4690 8d4f48                   lea       ecx, [edi + 0x48]
004f4693 d95de8                   fstp      dword ptr [ebp - 0x18]
004f4696 e8c5d9f0ff               call      0x402060
004f469b 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f469e db45e4                   fild      dword ptr [ebp - 0x1c]
004f46a1 d80da859cd00             fmul      dword ptr [0xcd59a8]
004f46a7 d86de8                   fsubr     dword ptr [ebp - 0x18]
004f46aa d85df4                   fcomp     dword ptr [ebp - 0xc]
004f46ad dfe0                     fnstsw    ax
004f46af f6c441                   test      ah, 0x41
004f46b2 750b                     jne       0x4f46bf
004f46b4 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004f46b7 c70002000000             mov       dword ptr [eax], 2
004f46bd eb65                     jmp       0x4f4724
004f46bf 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f46c5 8b11                     mov       edx, dword ptr [ecx]
004f46c7 8bbe601d0000             mov       edi, dword ptr [esi + 0x1d60]
004f46cd ff9298000000             call      dword ptr [edx + 0x98]
004f46d3 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f46d6 db45e4                   fild      dword ptr [ebp - 0x1c]
004f46d9 8d4f58                   lea       ecx, [edi + 0x58]
004f46dc d95df4                   fstp      dword ptr [ebp - 0xc]
004f46df e87cd9f0ff               call      0x402060
004f46e4 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f46e7 db45e4                   fild      dword ptr [ebp - 0x1c]
004f46ea 8b06                     mov       eax, dword ptr [esi]
004f46ec 8bce                     mov       ecx, esi
004f46ee d80da859cd00             fmul      dword ptr [0xcd59a8]
004f46f4 d95de8                   fstp      dword ptr [ebp - 0x18]
004f46f7 ff9098000000             call      dword ptr [eax + 0x98]
004f46fd 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f4700 db45e4                   fild      dword ptr [ebp - 0x1c]
004f4703 d845e8                   fadd      dword ptr [ebp - 0x18]
004f4706 d85df4                   fcomp     dword ptr [ebp - 0xc]
004f4709 dfe0                     fnstsw    ax
004f470b f6c405                   test      ah, 5
004f470e 7a0b                     jp        0x4f471b
004f4710 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004f4713 c70103000000             mov       dword ptr [ecx], 3
004f4719 eb09                     jmp       0x4f4724
004f471b 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f471e c70204000000             mov       dword ptr [edx], 4
004f4724 8b06                     mov       eax, dword ptr [esi]
004f4726 53                       push      ebx
004f4727 8bce                     mov       ecx, esi
004f4729 ff9094000000             call      dword ptr [eax + 0x94]
004f472f 99                       cdq       
004f4730 83e20f                   and       edx, 0xf
004f4733 03c2                     add       eax, edx
004f4735 8b16                     mov       edx, dword ptr [esi]
004f4737 c1f804                   sar       eax, 4
004f473a 8bce                     mov       ecx, esi
004f473c 8945fc                   mov       dword ptr [ebp - 4], eax
004f473f ff9298000000             call      dword ptr [edx + 0x98]
004f4745 8bc8                     mov       ecx, eax
004f4747 b8abaaaa2a               mov       eax, 0x2aaaaaab
004f474c f7e9                     imul      ecx
004f474e 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f4754 d1fa                     sar       edx, 1
004f4756 8bc2                     mov       eax, edx
004f4758 c1e81f                   shr       eax, 0x1f
004f475b 03c2                     add       eax, edx
004f475d 8945e8                   mov       dword ptr [ebp - 0x18], eax
004f4760 8b01                     mov       eax, dword ptr [ecx]
004f4762 ff9094000000             call      dword ptr [eax + 0x94]
004f4768 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f476e 99                       cdq       
004f476f 83e20f                   and       edx, 0xf
004f4772 03c2                     add       eax, edx
004f4774 8b11                     mov       edx, dword ptr [ecx]
004f4776 8bf8                     mov       edi, eax
004f4778 c1ff04                   sar       edi, 4
004f477b ff9298000000             call      dword ptr [edx + 0x98]
004f4781 8bc8                     mov       ecx, eax
004f4783 b8abaaaa2a               mov       eax, 0x2aaaaaab
004f4788 f7e9                     imul      ecx
004f478a 8b45fc                   mov       eax, dword ptr [ebp - 4]
004f478d 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
004f4790 d1fa                     sar       edx, 1
004f4792 8bda                     mov       ebx, edx
004f4794 c1eb1f                   shr       ebx, 0x1f
004f4797 8945f0                   mov       dword ptr [ebp - 0x10], eax
004f479a 8b864c1d0000             mov       eax, dword ptr [esi + 0x1d4c]
004f47a0 03da                     add       ebx, edx
004f47a2 83f8ff                   cmp       eax, -1
004f47a5 895df4                   mov       dword ptr [ebp - 0xc], ebx
004f47a8 894dec                   mov       dword ptr [ebp - 0x14], ecx
004f47ab 0f84f6000000             je        0x4f48a7
004f47b1 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f47b7 8b11                     mov       edx, dword ptr [ecx]
004f47b9 ff9294000000             call      dword ptr [edx + 0x94]
004f47bf 8bf8                     mov       edi, eax
004f47c1 8b06                     mov       eax, dword ptr [esi]
004f47c3 8bce                     mov       ecx, esi
004f47c5 ff9094000000             call      dword ptr [eax + 0x94]
004f47cb 3bc7                     cmp       eax, edi
004f47cd 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004f47d3 7e10                     jle       0x4f47e5
004f47d5 8b11                     mov       edx, dword ptr [ecx]
004f47d7 ff9294000000             call      dword ptr [edx + 0x94]
004f47dd 03864c1d0000             add       eax, dword ptr [esi + 0x1d4c]
004f47e3 eb0e                     jmp       0x4f47f3
004f47e5 8b01                     mov       eax, dword ptr [ecx]
004f47e7 ff9094000000             call      dword ptr [eax + 0x94]
004f47ed 2b864c1d0000             sub       eax, dword ptr [esi + 0x1d4c]
004f47f3 99                       cdq       
004f47f4 83e20f                   and       edx, 0xf
004f47f7 03c2                     add       eax, edx
004f47f9 8b16                     mov       edx, dword ptr [esi]
004f47fb 8bf8                     mov       edi, eax
004f47fd 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004f4803 6a00                     push      0
004f4805 50                       push      eax
004f4806 8bce                     mov       ecx, esi
004f4808 c1ff04                   sar       edi, 4
004f480b ff5208                   call      dword ptr [edx + 8]
004f480e 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004f4811 db45e4                   fild      dword ptr [ebp - 0x1c]
004f4814 db864c1d0000             fild      dword ptr [esi + 0x1d4c]
004f481a dc0da015cd00             fmul      qword ptr [0xcd15a0]
004f4820 ded9                     fcompp    
004f4822 dfe0                     fnstsw    ax
004f4824 f6c401                   test      ah, 1
004f4827 752e                     jne       0x4f4857
004f4829 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004f482f 8b                       .byte     0x8b

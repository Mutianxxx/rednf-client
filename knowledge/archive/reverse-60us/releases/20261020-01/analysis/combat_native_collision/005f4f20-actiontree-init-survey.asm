005f4f20 56                       push      esi
005f4f21 8bf1                     mov       esi, ecx
005f4f23 e8e8a0eaff               call      0x49f010
005f4f28 8b06                     mov       eax, dword ptr [esi]
005f4f2a 8bce                     mov       ecx, esi
005f4f2c ff9004020000             call      dword ptr [eax + 0x204]
005f4f32 85c0                     test      eax, eax
005f4f34 7e2b                     jle       0x5f4f61
005f4f36 57                       push      edi
005f4f37 8b3e                     mov       edi, dword ptr [esi]
005f4f39 8bce                     mov       ecx, esi
005f4f3b ff9704020000             call      dword ptr [edi + 0x204]
005f4f41 8b16                     mov       edx, dword ptr [esi]
005f4f43 50                       push      eax
005f4f44 8bce                     mov       ecx, esi
005f4f46 ff9298000000             call      dword ptr [edx + 0x98]
005f4f4c 50                       push      eax
005f4f4d 8b06                     mov       eax, dword ptr [esi]
005f4f4f 8bce                     mov       ecx, esi
005f4f51 ff9094000000             call      dword ptr [eax + 0x94]
005f4f57 50                       push      eax
005f4f58 8bce                     mov       ecx, esi
005f4f5a ff9788000000             call      dword ptr [edi + 0x88]
005f4f60 5f                       pop       edi
005f4f61 5e                       pop       esi
005f4f62 c3                       ret       
005f4f63 cc                       int3      
005f4f64 cc                       int3      
005f4f65 cc                       int3      
005f4f66 cc                       int3      
005f4f67 cc                       int3      
005f4f68 cc                       int3      
005f4f69 cc                       int3      
005f4f6a cc                       int3      
005f4f6b cc                       int3      
005f4f6c cc                       int3      
005f4f6d cc                       int3      
005f4f6e cc                       int3      
005f4f6f cc                       int3      
005f4f70 55                       push      ebp
005f4f71 8bec                     mov       ebp, esp
005f4f73 8b4508                   mov       eax, dword ptr [ebp + 8]
005f4f76 3bc1                     cmp       eax, ecx
005f4f78 7506                     jne       0x5f4f80
005f4f7a 32c0                     xor       al, al
005f4f7c 5d                       pop       ebp
005f4f7d c20400                   ret       4
005f4f80 8b11                     mov       edx, dword ptr [ecx]
005f4f82 50                       push      eax
005f4f83 ff9248020000             call      dword ptr [edx + 0x248]
005f4f89 84c0                     test      al, al
005f4f8b 0f95c0                   setne     al
005f4f8e 5d                       pop       ebp
005f4f8f c20400                   ret       4
005f4f92 cc                       int3      
005f4f93 cc                       int3      
005f4f94 cc                       int3      
005f4f95 cc                       int3      
005f4f96 cc                       int3      
005f4f97 cc                       int3      
005f4f98 cc                       int3      
005f4f99 cc                       int3      
005f4f9a cc                       int3      
005f4f9b cc                       int3      
005f4f9c cc                       int3      
005f4f9d cc                       int3      
005f4f9e cc                       int3      
005f4f9f cc                       int3      
005f4fa0 55                       push      ebp
005f4fa1 8bec                     mov       ebp, esp
005f4fa3 56                       push      esi
005f4fa4 8bf1                     mov       esi, ecx
005f4fa6 8a8649090000             mov       al, byte ptr [esi + 0x949]
005f4fac 84c0                     test      al, al
005f4fae 7512                     jne       0x5f4fc2
005f4fb0 8a8648090000             mov       al, byte ptr [esi + 0x948]
005f4fb6 84c0                     test      al, al
005f4fb8 7408                     je        0x5f4fc2
005f4fba 8b06                     mov       eax, dword ptr [esi]
005f4fbc ff9094030000             call      dword ptr [eax + 0x394]
005f4fc2 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f4fc5 51                       push      ecx
005f4fc6 8bce                     mov       ecx, esi
005f4fc8 e87398eaff               call      0x49e840
005f4fcd 5e                       pop       esi
005f4fce 5d                       pop       ebp
005f4fcf c20400                   ret       4
005f4fd2 cc                       int3      
005f4fd3 cc                       int3      
005f4fd4 cc                       int3      
005f4fd5 cc                       int3      
005f4fd6 cc                       int3      
005f4fd7 cc                       int3      
005f4fd8 cc                       int3      
005f4fd9 cc                       int3      
005f4fda cc                       int3      
005f4fdb cc                       int3      
005f4fdc cc                       int3      
005f4fdd cc                       int3      
005f4fde cc                       int3      
005f4fdf cc                       int3      
005f4fe0 ff817c080000             inc       dword ptr [ecx + 0x87c]
005f4fe6 8b01                     mov       eax, dword ptr [ecx]
005f4fe8 ffa088030000             jmp       dword ptr [eax + 0x388]
005f4fee cc                       int3      
005f4fef cc                       int3      
005f4ff0 c3                       ret       
005f4ff1 cc                       int3      
005f4ff2 cc                       int3      
005f4ff3 cc                       int3      
005f4ff4 cc                       int3      
005f4ff5 cc                       int3      
005f4ff6 cc                       int3      
005f4ff7 cc                       int3      
005f4ff8 cc                       int3      
005f4ff9 cc                       int3      
005f4ffa cc                       int3      
005f4ffb cc                       int3      
005f4ffc cc                       int3      
005f4ffd cc                       int3      
005f4ffe cc                       int3      
005f4fff cc                       int3      
005f5000 55                       push      ebp
005f5001 8bec                     mov       ebp, esp
005f5003 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f5006 85c9                     test      ecx, ecx
005f5008 53                       push      ebx
005f5009 0f94c3                   sete      bl
005f500c 84db                     test      bl, bl
005f500e 7412                     je        0x5f5022
005f5010 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005f5013 50                       push      eax
005f5014 68b016d500               push      0xd516b0
005f5019 ff15bc2eff00             call      dword ptr [0xff2ebc]
005f501f 83c408                   add       esp, 8
005f5022 8ac3                     mov       al, bl
005f5024 5b                       pop       ebx
005f5025 5d                       pop       ebp
005f5026 c3                       ret       
005f5027 cc                       int3      
005f5028 cc                       int3      
005f5029 cc                       int3      
005f502a cc                       int3      
005f502b cc                       int3      
005f502c cc                       int3      
005f502d cc                       int3      
005f502e cc                       int3      
005f502f cc                       int3      
005f5030 a148280001               mov       eax, dword ptr [0x1002848]
005f5035 85c0                     test      eax, eax
005f5037 7431                     je        0x5f506a
005f5039 8b8054100000             mov       eax, dword ptr [eax + 0x1054]
005f503f 85c0                     test      eax, eax
005f5041 7427                     je        0x5f506a
005f5043 8b4014                   mov       eax, dword ptr [eax + 0x14]
005f5046 85c0                     test      eax, eax
005f5048 7420                     je        0x5f506a
005f504a 8b88b4000000             mov       ecx, dword ptr [eax + 0xb4]
005f5050 85c9                     test      ecx, ecx
005f5052 7416                     je        0x5f506a
005f5054 e8c737e9ff               call      0x488820
005f5059 85c0                     test      eax, eax
005f505b 7c0d                     jl        0x5f506a
005f505d 83f804                   cmp       eax, 4
005f5060 7d08                     jge       0x5f506a
005f5062 8b04856c7ef500           mov       eax, dword ptr [eax*4 + 0xf57e6c]
005f5069 c3                       ret       
005f506a b864000000               mov       eax, 0x64
005f506f c3                       ret       
005f5070 c7814c09000000000000     mov       dword ptr [ecx + 0x94c], 0
005f507a c3                       ret       
005f507b cc                       int3      
005f507c cc                       int3      
005f507d cc                       int3      
005f507e cc                       int3      
005f507f cc                       int3      
005f5080 56                       push      esi
005f5081 8bf1                     mov       esi, ecx
005f5083 8d4e60                   lea       ecx, [esi + 0x60]
005f5086 e8751e5100               call      0xb06f00
005f508b 89864c090000             mov       dword ptr [esi + 0x94c], eax
005f5091 5e                       pop       esi
005f5092 c3                       ret       
005f5093 cc                       int3      
005f5094 cc                       int3      
005f5095 cc                       int3      
005f5096 cc                       int3      
005f5097 cc                       int3      
005f5098 cc                       int3      
005f5099 cc                       int3      
005f509a cc                       int3      
005f509b cc                       int3      
005f509c cc                       int3      
005f509d cc                       int3      
005f509e cc                       int3      
005f509f cc                       int3      
005f50a0 c3                       ret       
005f50a1 cc                       int3      
005f50a2 cc                       int3      
005f50a3 cc                       int3      
005f50a4 cc                       int3      
005f50a5 cc                       int3      
005f50a6 cc                       int3      
005f50a7 cc                       int3      
005f50a8 cc                       int3      
005f50a9 cc                       int3      
005f50aa cc                       int3      
005f50ab cc                       int3      
005f50ac cc                       int3      
005f50ad cc                       int3      
005f50ae cc                       int3      
005f50af cc                       int3      
005f50b0 55                       push      ebp
005f50b1 8bec                     mov       ebp, esp
005f50b3 5d                       pop       ebp
005f50b4 e94790eaff               jmp       0x49e100
005f50b9 cc                       int3      
005f50ba cc                       int3      
005f50bb cc                       int3      
005f50bc cc                       int3      
005f50bd cc                       int3      
005f50be cc                       int3      
005f50bf cc                       int3      
005f50c0 c6815009000000           mov       byte ptr [ecx + 0x950], 0
005f50c7 c3                       ret       
005f50c8 cc                       int3      
005f50c9 cc                       int3      
005f50ca cc                       int3      
005f50cb cc                       int3      
005f50cc cc                       int3      
005f50cd cc                       int3      
005f50ce cc                       int3      
005f50cf cc                       int3      
005f50d0 56                       push      esi
005f50d1 8bf1                     mov       esi, ecx
005f50d3 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f50d9 85c9                     test      ecx, ecx
005f50db 7406                     je        0x5f50e3
005f50dd 8b01                     mov       eax, dword ptr [ecx]
005f50df 6a01                     push      1
005f50e1 ff10                     call      dword ptr [eax]
005f50e3 c7864c09000000000000     mov       dword ptr [esi + 0x94c], 0
005f50ed 5e                       pop       esi
005f50ee c3                       ret       
005f50ef cc                       int3      
005f50f0 55                       push      ebp
005f50f1 8bec                     mov       ebp, esp
005f50f3 5d                       pop       ebp
005f50f4 e91785eaff               jmp       0x49d610
005f50f9 cc                       int3      
005f50fa cc                       int3      
005f50fb cc                       int3      
005f50fc cc                       int3      
005f50fd cc                       int3      
005f50fe cc                       int3      
005f50ff cc                       int3      
005f5100 33c0                     xor       eax, eax
005f5102 89814c090000             mov       dword ptr [ecx + 0x94c], eax
005f5108 898150090000             mov       dword ptr [ecx + 0x950], eax
005f510e c3                       ret       
005f510f cc                       int3      
005f5110 56                       push      esi
005f5111 8bf1                     mov       esi, ecx
005f5113 8b06                     mov       eax, dword ptr [esi]
005f5115 6a07                     push      7
005f5117 ff90cc010000             call      dword ptr [eax + 0x1cc]
005f511d 898650090000             mov       dword ptr [esi + 0x950], eax
005f5123 5e                       pop       esi
005f5124 c3                       ret       
005f5125 cc                       int3      
005f5126 cc                       int3      
005f5127 cc                       int3      
005f5128 cc                       int3      
005f5129 cc                       int3      
005f512a cc                       int3      
005f512b cc                       int3      
005f512c cc                       int3      
005f512d cc                       int3      
005f512e cc                       int3      
005f512f cc                       int3      
005f5130 c3                       ret       
005f5131 cc                       int3      
005f5132 cc                       int3      
005f5133 cc                       int3      
005f5134 cc                       int3      
005f5135 cc                       int3      
005f5136 cc                       int3      
005f5137 cc                       int3      
005f5138 cc                       int3      
005f5139 cc                       int3      
005f513a cc                       int3      
005f513b cc                       int3      
005f513c cc                       int3      
005f513d cc                       int3      
005f513e cc                       int3      
005f513f cc                       int3      
005f5140 55                       push      ebp
005f5141 8bec                     mov       ebp, esp
005f5143 5d                       pop       ebp
005f5144 e9c784eaff               jmp       0x49d610
005f5149 cc                       int3      
005f514a cc                       int3      
005f514b cc                       int3      
005f514c cc                       int3      
005f514d cc                       int3      
005f514e cc                       int3      
005f514f cc                       int3      
005f5150 c3                       ret       
005f5151 cc                       int3      
005f5152 cc                       int3      
005f5153 cc                       int3      
005f5154 cc                       int3      
005f5155 cc                       int3      
005f5156 cc                       int3      
005f5157 cc                       int3      
005f5158 cc                       int3      
005f5159 cc                       int3      
005f515a cc                       int3      
005f515b cc                       int3      
005f515c cc                       int3      
005f515d cc                       int3      
005f515e cc                       int3      
005f515f cc                       int3      
005f5160 55                       push      ebp
005f5161 8bec                     mov       ebp, esp
005f5163 83ec70                   sub       esp, 0x70
005f5166 53                       push      ebx
005f5167 8bd9                     mov       ebx, ecx
005f5169 8b8b04010000             mov       ecx, dword ptr [ebx + 0x104]
005f516f 85c9                     test      ecx, ecx
005f5171 7405                     je        0x5f5178
005f5173 e8e8214300               call      0xa27360
005f5178 8bcb                     mov       ecx, ebx
005f517a e8116feaff               call      0x49c090
005f517f 84c0                     test      al, al
005f5181 0f847b010000             je        0x5f5302
005f5187 8b03                     mov       eax, dword ptr [ebx]
005f5189 8bcb                     mov       ecx, ebx
005f518b ff5064                   call      dword ptr [eax + 0x64]
005f518e 84c0                     test      al, al
005f5190 0f846c010000             je        0x5f5302
005f5196 56                       push      esi
005f5197 57                       push      edi
005f5198 8d4d90                   lea       ecx, [ebp - 0x70]
005f519b e84026e5ff               call      0x4477e0
005f51a0 8b13                     mov       edx, dword ptr [ebx]
005f51a2 8bcb                     mov       ecx, ebx
005f51a4 ff5248                   call      dword ptr [edx + 0x48]
005f51a7 8b4878                   mov       ecx, dword ptr [eax + 0x78]
005f51aa 8b01                     mov       eax, dword ptr [ecx]
005f51ac ff5010                   call      dword ptr [eax + 0x10]
005f51af 8b13                     mov       edx, dword ptr [ebx]
005f51b1 8bf0                     mov       esi, eax
005f51b3 b919000000               mov       ecx, 0x19
005f51b8 8d7d90                   lea       edi, [ebp - 0x70]
005f51bb f3a5                     rep movsd dword ptr es:[edi], dword ptr [esi]
005f51bd 66a5                     movsw     word ptr es:[edi], word ptr [esi]
005f51bf 8bcb                     mov       ecx, ebx
005f51c1 a4                       movsb     byte ptr es:[edi], byte ptr [esi]
005f51c2 ff9294010000             call      dword ptr [edx + 0x194]
005f51c8 813845770000             cmp       dword ptr [eax], 0x7745
005f51ce 0f8533010000             jne       0x5f5307
005f51d4 c745e960ea0000           mov       dword ptr [ebp - 0x17], 0xea60
005f51db 6a00                     push      0
005f51dd e80e8f2b00               call      0x8ae0f0
005f51e2 99                       cdq       
005f51e3 b9b5000000               mov       ecx, 0xb5
005f51e8 f7f9                     idiv      ecx
005f51ea 8b45dc                   mov       eax, dword ptr [ebp - 0x24]
005f51ed b9                       .byte     0xb9
005f51ee 68                       .byte     0x68
005f51ef 01                       .byte     0x01

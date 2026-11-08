008c4248  8b06                     mov        eax, dword ptr [esi]
008c424a  33db                     xor        ebx, ebx
008c424c  8d4de4                   lea        ecx, [ebp - 0x1c]
008c424f  51                       push       ecx
008c4250  8bce                     mov        ecx, esi
008c4252  895de4                   mov        dword ptr [ebp - 0x1c], ebx
008c4255  895dcc                   mov        dword ptr [ebp - 0x34], ebx
008c4258  895da8                   mov        dword ptr [ebp - 0x58], ebx
008c425b  895dac                   mov        dword ptr [ebp - 0x54], ebx
008c425e  ff5054                   call       dword ptr [eax + 0x54]
008c4261  8b16                     mov        edx, dword ptr [esi]
008c4263  8d45cc                   lea        eax, [ebp - 0x34]
008c4266  50                       push       eax
008c4267  8bce                     mov        ecx, esi
008c4269  ff5254                   call       dword ptr [edx + 0x54]
008c426c  8b16                     mov        edx, dword ptr [esi]
008c426e  8d45a8                   lea        eax, [ebp - 0x58]
008c4271  50                       push       eax
008c4272  8bce                     mov        ecx, esi
008c4274  ff5254                   call       dword ptr [edx + 0x54]
008c4277  8b16                     mov        edx, dword ptr [esi]
008c4279  8d45ac                   lea        eax, [ebp - 0x54]
008c427c  50                       push       eax
008c427d  8bce                     mov        ecx, esi
008c427f  ff5254                   call       dword ptr [edx + 0x54]
008c4282  8b0d48280001             mov        ecx, dword ptr [0x1002848]
008c4288  6aff                     push       -1
008c428a  53                       push       ebx
008c428b  895ddc                   mov        dword ptr [ebp - 0x24], ebx
008c428e  e8dd69b7ff               call       0x43ac70
008c4293  8bf8                     mov        edi, eax
008c4295  3bfb                     cmp        edi, ebx
008c4297  897dec                   mov        dword ptr [ebp - 0x14], edi
008c429a  0f8456070000             je         0x8c49f6
008c42a0  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
008c42a3  663dffff                 cmp        ax, 0xffff
008c42a7  7450                     je         0x8c42f9
008c42a9  0fb74dcc                 movzx      ecx, word ptr [ebp - 0x34]
008c42ad  53                       push       ebx
008c42ae  687c28f400               push       0xf4287c
008c42b3  681009f400               push       0xf40910
008c42b8  53                       push       ebx
008c42b9  0fb7d0                   movzx      edx, ax
008c42bc  51                       push       ecx
008c42bd  52                       push       edx
008c42be  8bcf                     mov        ecx, edi
008c42c0  e85b75c4ff               call       0x50b820
008c42c5  50                       push       eax
008c42c6  e840ca3300               call       0xc00d0b
008c42cb  83c414                   add        esp, 0x14
008c42ce  3bc3                     cmp        eax, ebx
008c42d0  8945dc                   mov        dword ptr [ebp - 0x24], eax
008c42d3  7524                     jne        0x8c42f9
008c42d5  66817de41101             cmp        word ptr [ebp - 0x1c], 0x111
008c42db  751c                     jne        0x8c42f9
008c42dd  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
008c42e0  8b0d3c310001             mov        ecx, dword ptr [0x100313c]
008c42e6  50                       push       eax
008c42e7  e8e479c9ff               call       0x55bcd0
008c42ec  3bc3                     cmp        eax, ebx
008c42ee  7409                     je         0x8c42f9
008c42f0  8b8804020000             mov        ecx, dword ptr [eax + 0x204]
008c42f6  894ddc                   mov        dword ptr [ebp - 0x24], ecx
008c42f9  8b45a8                   mov        eax, dword ptr [ebp - 0x58]
008c42fc  663dffff                 cmp        ax, 0xffff
008c4300  895dc0                   mov        dword ptr [ebp - 0x40], ebx
008c4303  7413                     je         0x8c4318
008c4305  0fb755ac                 movzx      edx, word ptr [ebp - 0x54]
008c4309  0fb7c0                   movzx      eax, ax
008c430c  52                       push       edx
008c430d  50                       push       eax
008c430e  8bcf                     mov        ecx, edi
008c4310  e80b75c4ff               call       0x50b820
008c4315  8945c0                   mov        dword ptr [ebp - 0x40], eax
008c4318  8b16                     mov        edx, dword ptr [esi]
008c431a  8d45d4                   lea        eax, [ebp - 0x2c]
008c431d  50                       push       eax
008c431e  8bce                     mov        ecx, esi
008c4320  895dd4                   mov        dword ptr [ebp - 0x2c], ebx
008c4323  ff5254                   call       dword ptr [edx + 0x54]
008c4326  66395dd4                 cmp        word ptr [ebp - 0x2c], bx
008c432a  895df0                   mov        dword ptr [ebp - 0x10], ebx
008c432d  0f86bd020000             jbe        0x8c45f0
008c4333  8b16                     mov        edx, dword ptr [esi]
008c4335  8d45d0                   lea        eax, [ebp - 0x30]
008c4338  bfffff0000               mov        edi, 0xffff
008c433d  50                       push       eax
008c433e  8bce                     mov        ecx, esi
008c4340  897dd0                   mov        dword ptr [ebp - 0x30], edi
008c4343  895de0                   mov        dword ptr [ebp - 0x20], ebx
008c4346  895dd8                   mov        dword ptr [ebp - 0x28], ebx
008c4349  895de8                   mov        dword ptr [ebp - 0x18], ebx
008c434c  ff5254                   call       dword ptr [edx + 0x54]
008c434f  8b16                     mov        edx, dword ptr [esi]
008c4351  8d45e8                   lea        eax, [ebp - 0x18]
008c4354  50                       push       eax
008c4355  8bce                     mov        ecx, esi
008c4357  ff525c                   call       dword ptr [edx + 0x5c]
008c435a  8b16                     mov        edx, dword ptr [esi]
008c435c  8d45e0                   lea        eax, [ebp - 0x20]
008c435f  50                       push       eax
008c4360  8bce                     mov        ecx, esi
008c4362  ff5254                   call       dword ptr [edx + 0x54]
008c4365  8b16                     mov        edx, dword ptr [esi]
008c4367  8d45d8                   lea        eax, [ebp - 0x28]
008c436a  50                       push       eax
008c436b  8bce                     mov        ecx, esi
008c436d  ff5254                   call       dword ptr [edx + 0x54]
008c4370  66397dd8                 cmp        word ptr [ebp - 0x28], di
008c4374  7516                     jne        0x8c438c
008c4376  68f7010000               push       0x1f7
008c437b  e8c0ce1800               call       0xa51240
008c4380  50                       push       eax
008c4381  ff15b82eff00             call       dword ptr [0xff2eb8]
008c4387  e91d020000               jmp        0x8c45a9
008c438c  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
008c438f  0fb755d0                 movzx      edx, word ptr [ebp - 0x30]
008c4393  51                       push       ecx
008c4394  52                       push       edx
008c4395  e86641d2ff               call       0x5e8500
008c439a  8bf8                     mov        edi, eax
008c439c  83c408                   add        esp, 8
008c439f  3bfb                     cmp        edi, ebx
008c43a1  897dbc                   mov        dword ptr [ebp - 0x44], edi
008c43a4  0f8433020000             je         0x8c45dd
008c43aa  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
008c43ad  8b07                     mov        eax, dword ptr [edi]
008c43af  51                       push       ecx
008c43b0  8bcf                     mov        ecx, edi
008c43b2  ff9044030000             call       dword ptr [eax + 0x344]
008c43b8  0fb755d8                 movzx      edx, word ptr [ebp - 0x28]
008c43bc  0fb745e0                 movzx      eax, word ptr [ebp - 0x20]
008c43c0  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
008c43c3  53                       push       ebx
008c43c4  53                       push       ebx
008c43c5  53                       push       ebx
008c43c6  57                       push       edi
008c43c7  52                       push       edx
008c43c8  50                       push       eax
008c43c9  53                       push       ebx
008c43ca  e8a199c4ff               call       0x50dd70
008c43cf  8b17                     mov        edx, dword ptr [edi]
008c43d1  8bcf                     mov        ecx, edi
008c43d3  ff9204010000             call       dword ptr [edx + 0x104]
008c43d9  85c0                     test       eax, eax
008c43db  7412                     je         0x8c43ef
008c43dd  8b07                     mov        eax, dword ptr [edi]
008c43df  8bcf                     mov        ecx, edi
008c43e1  ff9004010000             call       dword ptr [eax + 0x104]
008c43e7  8b10                     mov        edx, dword ptr [eax]
008c43e9  57                       push       edi
008c43ea  8bc8                     mov        ecx, eax
008c43ec  ff5210                   call       dword ptr [edx + 0x10]
008c43ef  8b06                     mov        eax, dword ptr [esi]
008c43f1  8d4d0b                   lea        ecx, [ebp + 0xb]
008c43f4  51                       push       ecx
008c43f5  8bce                     mov        ecx, esi
008c43f7  885d0b                   mov        byte ptr [ebp + 0xb], bl
008c43fa  ff5050                   call       dword ptr [eax + 0x50]
008c43fd  807d0b01                 cmp        byte ptr [ebp + 0xb], 1
008c4401  0f859c000000             jne        0x8c44a3
008c4407  68c4000000               push       0xc4
008c440c  e83ff8b3ff               call       0x403c50
008c4411  83c404                   add        esp, 4
008c4414  89450c                   mov        dword ptr [ebp + 0xc], eax
008c4417  3bc3                     cmp        eax, ebx
008c4419  c745fc0b000000           mov        dword ptr [ebp - 4], 0xb
008c4420  740c                     je         0x8c442e
008c4422  8bc8                     mov        ecx, eax
008c4424  e89716bdff               call       0x495ac0
008c4429  89450c                   mov        dword ptr [ebp + 0xc], eax
008c442c  eb03                     jmp        0x8c4431
008c442e  895d0c                   mov        dword ptr [ebp + 0xc], ebx
008c4431  8b16                     mov        edx, dword ptr [esi]
008c4433  8d4590                   lea        eax, [ebp - 0x70]
008c4436  50                       push       eax
008c4437  8bce                     mov        ecx, esi
008c4439  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008c4440  ff525c                   call       dword ptr [edx + 0x5c]
008c4443  8b4d90                   mov        ecx, dword ptr [ebp - 0x70]
008c4446  51                       push       ecx
008c4447  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008c444a  e8217bffff               call       0x8bbf70
008c444f  8b550c                   mov        edx, dword ptr [ebp + 0xc]
008c4452  8b07                     mov        eax, dword ptr [edi]
008c4454  52                       push       edx
008c4455  8bcf                     mov        ecx, edi
008c4457  ff5048                   call       dword ptr [eax + 0x48]
008c445a  8bc8                     mov        ecx, eax
008c445c  e8afdac4ff               call       0x511f10
008c4461  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008c4464  8b07                     mov        eax, dword ptr [edi]
008c4466  8b11                     mov        edx, dword ptr [ecx]
008c4468  8945b8                   mov        dword ptr [ebp - 0x48], eax
008c446b  ff5210                   call       dword ptr [edx + 0x10]
008c446e  8a5058                   mov        dl, byte ptr [eax + 0x58]
008c4471  8b7dbc                   mov        edi, dword ptr [ebp - 0x44]
008c4474  8b45b8                   mov        eax, dword ptr [ebp - 0x48]
008c4477  33c9                     xor        ecx, ecx
008c4479  3ad3                     cmp        dl, bl
008c447b  0f94c1                   sete       cl
008c447e  51                       push       ecx
008c447f  8bcf                     mov        ecx, edi
008c4481  ff90bc000000             call       dword ptr [eax + 0xbc]
008c4487  8b16                     mov        edx, dword ptr [esi]
008c4489  8d458c                   lea        eax, [ebp - 0x74]
008c448c  50                       push       eax
008c448d  8bce                     mov        ecx, esi
008c448f  895d8c                   mov        dword ptr [ebp - 0x74], ebx
008c4492  ff525c                   call       dword ptr [edx + 0x5c]
008c4495  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008c4498  8b458c                   mov        eax, dword ptr [ebp - 0x74]
008c449b  8b11                     mov        edx, dword ptr [ecx]
008c449d  50                       push       eax
008c449e  ff5204                   call       dword ptr [edx + 4]
008c44a1  eb60                     jmp        0x8c4503
008c44a3  8b16                     mov        edx, dword ptr [esi]
008c44a5  8d450f                   lea        eax, [ebp + 0xf]
008c44a8  50                       push       eax
008c44a9  8bce                     mov        ecx, esi
008c44ab  885d0f                   mov        byte ptr [ebp + 0xf], bl
008c44ae  895dbc                   mov        dword ptr [ebp - 0x44], ebx
008c44b1  895db8                   mov        dword ptr [ebp - 0x48], ebx
008c44b4  895da4                   mov        dword ptr [ebp - 0x5c], ebx
008c44b7  ff5250                   call       dword ptr [edx + 0x50]
008c44ba  8b16                     mov        edx, dword ptr [esi]
008c44bc  8d45bc                   lea        eax, [ebp - 0x44]
008c44bf  50                       push       eax
008c44c0  8bce                     mov        ecx, esi
008c44c2  ff5254                   call       dword ptr [edx + 0x54]
008c44c5  8b16                     mov        edx, dword ptr [esi]
008c44c7  8d45b8                   lea        eax, [ebp - 0x48]
008c44ca  50                       push       eax
008c44cb  8bce                     mov        ecx, esi
008c44cd  ff5254                   call       dword ptr [edx + 0x54]
008c44d0  8b16                     mov        edx, dword ptr [esi]
008c44d2  8d45a4                   lea        eax, [ebp - 0x5c]
008c44d5  50                       push       eax
008c44d6  8bce                     mov        ecx, esi
008c44d8  ff5254                   call       dword ptr [edx + 0x54]
008c44db  0fb6450f                 movzx      eax, byte ptr [ebp + 0xf]
008c44df  8b17                     mov        edx, dword ptr [edi]
008c44e1  50                       push       eax
008c44e2  8bcf                     mov        ecx, edi
008c44e4  ff92bc000000             call       dword ptr [edx + 0xbc]
008c44ea  0fbf45a4                 movsx      eax, word ptr [ebp - 0x5c]
008c44ee  0fbf4db8                 movsx      ecx, word ptr [ebp - 0x48]
008c44f2  8b17                     mov        edx, dword ptr [edi]
008c44f4  50                       push       eax
008c44f5  0fbf45bc                 movsx      eax, word ptr [ebp - 0x44]
008c44f9  51                       push       ecx
008c44fa  50                       push       eax
008c44fb  8bcf                     mov        ecx, edi
008c44fd  ff9288000000             call       dword ptr [edx + 0x88]
008c4503  8b17                     mov        edx, dword ptr [edi]
008c4505  8bcf                     mov        ecx, edi
008c4507  ff92c0000000             call       dword ptr [edx + 0xc0]
008c450d  50                       push       eax
008c450e  8b07                     mov        eax, dword ptr [edi]
008c4510  8bcf                     mov        ecx, edi
008c4512  ff5048                   call       dword ptr [eax + 0x48]
008c4515  8bc8                     mov        ecx, eax
008c4517  e814d9c4ff               call       0x511e30
008c451c  8b4dc0                   mov        ecx, dword ptr [ebp - 0x40]
008c451f  8b17                     mov        edx, dword ptr [edi]
008c4521  51                       push       ecx
008c4522  8bcf                     mov        ecx, edi
008c4524  ff5248                   call       dword ptr [edx + 0x48]
008c4527  8bc8                     mov        ecx, eax
008c4529  e852c9c4ff               call       0x510e80
008c452e  8b06                     mov        eax, dword ptr [esi]
008c4530  68a00b0c01               push       0x10c0ba0
008c4535  8bce                     mov        ecx, esi
008c4537  ff5068                   call       dword ptr [eax + 0x68]
008c453a  3bc3                     cmp        eax, ebx
008c453c  7e10                     jle        0x8c454e
008c453e  8b17                     mov        edx, dword ptr [edi]
008c4540  50                       push       eax
008c4541  68a00b0c01               push       0x10c0ba0
008c4546  8bcf                     mov        ecx, edi
008c4548  ff9254030000             call       dword ptr [edx + 0x354]
008c454e  8b06                     mov        eax, dword ptr [esi]
008c4550  8d4dc8                   lea        ecx, [ebp - 0x38]
008c4553  51                       push       ecx
008c4554  8bce                     mov        ecx, esi
008c4556  895dc8                   mov        dword ptr [ebp - 0x38], ebx
008c4559  ff5054                   call       dword ptr [eax + 0x54]
008c455c  8b45c8                   mov        eax, dword ptr [ebp - 0x38]
008c455f  663bc3                   cmp        ax, bx
008c4562  7609                     jbe        0x8c456d
008c4564  0fb7d0                   movzx      edx, ax
008c4567  89976c080000             mov        dword ptr [edi + 0x86c], edx
008c456d  8b06                     mov        eax, dword ptr [esi]
008c456f  8d4d13                   lea        ecx, [ebp + 0x13]
008c4572  51                       push       ecx
008c4573  8bce                     mov        ecx, esi
008c4575  885d13                   mov        byte ptr [ebp + 0x13], bl
008c4578  ff5050                   call       dword ptr [eax + 0x50]
008c457b  385d13                   cmp        byte ptr [ebp + 0x13], bl
008c457e  741f                     je         0x8c459f
008c4580  8b16                     mov        edx, dword ptr [esi]
008c4582  6a04                     push       4
008c4584  8d450c                   lea        eax, [ebp + 0xc]
008c4587  50                       push       eax
008c4588  8bce                     mov        ecx, esi
008c458a  c7450c0000803f           mov        dword ptr [ebp + 0xc], 0x3f800000
008c4591  ff5264                   call       dword ptr [edx + 0x64]
008c4594  8d4d0c                   lea        ecx, [ebp + 0xc]
008c4597  51                       push       ecx
008c4598  8bcf                     mov        ecx, edi
008c459a  e8b18ebdff               call       0x49d450
008c459f  8b55dc                   mov        edx, dword ptr [ebp - 0x24]
008c45a2  52                       push       edx
008c45a3  57                       push       edi
008c45a4  e84748b8ff               call       0x448df0
008c45a9  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
008c45ac  0fb74dd4                 movzx      ecx, word ptr [ebp - 0x2c]
008c45b0  83c408                   add        esp, 8
008c45b3  40                       inc        eax
008c45b4  3bc1                     cmp        eax, ecx
008c45b6  8945f0                   mov        dword ptr [ebp - 0x10], eax
008c45b9  0f8c74fdffff             jl         0x8c4333
008c45bf  a1e4300001               mov        eax, dword ptr [0x10030e4]
008c45c4  88981c020000             mov        byte ptr [eax + 0x21c], bl
008c45ca  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c45cd  64890d00000000           mov        dword ptr fs:[0], ecx
008c45d4  5f                       pop        edi
008c45d5  5e                       pop        esi
008c45d6  5b                       pop        ebx
008c45d7  8be5                     mov        esp, ebp
008c45d9  5d                       pop        ebp
008c45da  c20c00                   ret        0xc
008c45dd  0fb755d0                 movzx      edx, word ptr [ebp - 0x30]
008c45e1  52                       push       edx
008c45e2  682010e300               push       0xe31020
008c45e7  ff15bc2eff00             call       dword ptr [0xff2ebc]
008c45ed  83c408                   add        esp, 8
008c45f0  a1e4300001               mov        eax, dword ptr [0x10030e4]
008c45f5  88981c020000             mov        byte ptr [eax + 0x21c], bl
008c45fb  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008c45fe  64890d00000000           mov        dword ptr fs:[0], ecx
008c4605  5f                       pop        edi
008c4606  5e                       pop        esi
008c4607  5b                       pop        ebx
008c4608  8be5                     mov        esp, ebp
008c460a  5d                       pop        ebp
008c460b  c20c00                   ret        0xc
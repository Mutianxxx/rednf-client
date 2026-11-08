004b8690  55                       push       ebp
004b8691  8bec                     mov        ebp, esp
004b8693  8b01                     mov        eax, dword ptr [ecx]
004b8695  53                       push       ebx
004b8696  56                       push       esi
004b8697  57                       push       edi
004b8698  6811010000               push       0x111
004b869d  ff502c                   call       dword ptr [eax + 0x2c]
004b86a0  84c0                     test       al, al
004b86a2  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
004b86a5  8b750c                   mov        esi, dword ptr [ebp + 0xc]
004b86a8  0f8499010000             je         0x4b8847
004b86ae  8b0f                     mov        ecx, dword ptr [edi]
004b86b0  8b16                     mov        edx, dword ptr [esi]
004b86b2  51                       push       ecx
004b86b3  52                       push       edx
004b86b4  e8f7460100               call       0x4ccdb0
004b86b9  8b4704                   mov        eax, dword ptr [edi + 4]
004b86bc  8b4e04                   mov        ecx, dword ptr [esi + 4]
004b86bf  50                       push       eax
004b86c0  51                       push       ecx
004b86c1  e8ea460100               call       0x4ccdb0
004b86c6  8b5708                   mov        edx, dword ptr [edi + 8]
004b86c9  8b4608                   mov        eax, dword ptr [esi + 8]
004b86cc  52                       push       edx
004b86cd  50                       push       eax
004b86ce  e8dd460100               call       0x4ccdb0
004b86d3  8bc7                     mov        eax, edi
004b86d5  83c418                   add        esp, 0x18
004b86d8  2bc6                     sub        eax, esi
004b86da  8d5e0c                   lea        ebx, [esi + 0xc]
004b86dd  894510                   mov        dword ptr [ebp + 0x10], eax
004b86e0  c7450c02000000           mov        dword ptr [ebp + 0xc], 2
004b86e7  eb07                     jmp        0x4b86f0
004b86e9  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b86ec  8d642400                 lea        esp, [esp]
004b86f0  8b0c18                   mov        ecx, dword ptr [eax + ebx]
004b86f3  8b13                     mov        edx, dword ptr [ebx]
004b86f5  51                       push       ecx
004b86f6  52                       push       edx
004b86f7  e8b4460100               call       0x4ccdb0
004b86fc  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b86ff  83c408                   add        esp, 8
004b8702  83c304                   add        ebx, 4
004b8705  48                       dec        eax
004b8706  89450c                   mov        dword ptr [ebp + 0xc], eax
004b8709  75de                     jne        0x4b86e9
004b870b  8b4714                   mov        eax, dword ptr [edi + 0x14]
004b870e  8b4e14                   mov        ecx, dword ptr [esi + 0x14]
004b8711  50                       push       eax
004b8712  51                       push       ecx
004b8713  e898460100               call       0x4ccdb0
004b8718  8b5718                   mov        edx, dword ptr [edi + 0x18]
004b871b  8b4618                   mov        eax, dword ptr [esi + 0x18]
004b871e  52                       push       edx
004b871f  50                       push       eax
004b8720  e88b460100               call       0x4ccdb0
004b8725  8b4f1c                   mov        ecx, dword ptr [edi + 0x1c]
004b8728  8b561c                   mov        edx, dword ptr [esi + 0x1c]
004b872b  51                       push       ecx
004b872c  52                       push       edx
004b872d  e87e460100               call       0x4ccdb0
004b8732  8b4720                   mov        eax, dword ptr [edi + 0x20]
004b8735  8b4e20                   mov        ecx, dword ptr [esi + 0x20]
004b8738  50                       push       eax
004b8739  51                       push       ecx
004b873a  e871460100               call       0x4ccdb0
004b873f  8b4628                   mov        eax, dword ptr [esi + 0x28]
004b8742  33db                     xor        ebx, ebx
004b8744  83c420                   add        esp, 0x20
004b8747  3bc3                     cmp        eax, ebx
004b8749  7504                     jne        0x4b874f
004b874b  33c9                     xor        ecx, ecx
004b874d  eb08                     jmp        0x4b8757
004b874f  8b4e2c                   mov        ecx, dword ptr [esi + 0x2c]
004b8752  2bc8                     sub        ecx, eax
004b8754  c1f902                   sar        ecx, 2
004b8757  8b5728                   mov        edx, dword ptr [edi + 0x28]
004b875a  3bd3                     cmp        edx, ebx
004b875c  741d                     je         0x4b877b
004b875e  8b472c                   mov        eax, dword ptr [edi + 0x2c]
004b8761  2bc2                     sub        eax, edx
004b8763  c1f802                   sar        eax, 2
004b8766  3bc8                     cmp        ecx, eax
004b8768  7311                     jae        0x4b877b
004b876a  8b4e28                   mov        ecx, dword ptr [esi + 0x28]
004b876d  3bcb                     cmp        ecx, ebx
004b876f  7505                     jne        0x4b8776
004b8771  895d10                   mov        dword ptr [ebp + 0x10], ebx
004b8774  eb1c                     jmp        0x4b8792
004b8776  8b462c                   mov        eax, dword ptr [esi + 0x2c]
004b8779  eb0f                     jmp        0x4b878a
004b877b  8b4f28                   mov        ecx, dword ptr [edi + 0x28]
004b877e  3bcb                     cmp        ecx, ebx
004b8780  7505                     jne        0x4b8787
004b8782  895d10                   mov        dword ptr [ebp + 0x10], ebx
004b8785  eb0b                     jmp        0x4b8792
004b8787  8b472c                   mov        eax, dword ptr [edi + 0x2c]
004b878a  2bc1                     sub        eax, ecx
004b878c  c1f802                   sar        eax, 2
004b878f  894510                   mov        dword ptr [ebp + 0x10], eax
004b8792  395d10                   cmp        dword ptr [ebp + 0x10], ebx
004b8795  7e32                     jle        0x4b87c9
004b8797  eb07                     jmp        0x4b87a0
004b8799  8da42400000000           lea        esp, [esp]
004b87a0  8b4728                   mov        eax, dword ptr [edi + 0x28]
004b87a3  8b4e28                   mov        ecx, dword ptr [esi + 0x28]
004b87a6  8d149d00000000           lea        edx, [ebx*4]
004b87ad  03c2                     add        eax, edx
004b87af  03ca                     add        ecx, edx
004b87b1  8b10                     mov        edx, dword ptr [eax]
004b87b3  8b01                     mov        eax, dword ptr [ecx]
004b87b5  52                       push       edx
004b87b6  50                       push       eax
004b87b7  e8f4450100               call       0x4ccdb0
004b87bc  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b87bf  83c408                   add        esp, 8
004b87c2  43                       inc        ebx
004b87c3  3bd8                     cmp        ebx, eax
004b87c5  7cd9                     jl         0x4b87a0
004b87c7  33db                     xor        ebx, ebx
004b87c9  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b87cc  3bc3                     cmp        eax, ebx
004b87ce  7504                     jne        0x4b87d4
004b87d0  33c9                     xor        ecx, ecx
004b87d2  eb08                     jmp        0x4b87dc
004b87d4  8b4e3c                   mov        ecx, dword ptr [esi + 0x3c]
004b87d7  2bc8                     sub        ecx, eax
004b87d9  c1f902                   sar        ecx, 2
004b87dc  8b5738                   mov        edx, dword ptr [edi + 0x38]
004b87df  3bd3                     cmp        edx, ebx
004b87e1  741d                     je         0x4b8800
004b87e3  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b87e6  2bc2                     sub        eax, edx
004b87e8  c1f802                   sar        eax, 2
004b87eb  3bc8                     cmp        ecx, eax
004b87ed  7311                     jae        0x4b8800
004b87ef  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b87f2  3bcb                     cmp        ecx, ebx
004b87f4  7505                     jne        0x4b87fb
004b87f6  895d10                   mov        dword ptr [ebp + 0x10], ebx
004b87f9  eb1c                     jmp        0x4b8817
004b87fb  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b87fe  eb0f                     jmp        0x4b880f
004b8800  8b4f38                   mov        ecx, dword ptr [edi + 0x38]
004b8803  3bcb                     cmp        ecx, ebx
004b8805  7505                     jne        0x4b880c
004b8807  895d10                   mov        dword ptr [ebp + 0x10], ebx
004b880a  eb0b                     jmp        0x4b8817
004b880c  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b880f  2bc1                     sub        eax, ecx
004b8811  c1f802                   sar        eax, 2
004b8814  894510                   mov        dword ptr [ebp + 0x10], eax
004b8817  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b881a  33db                     xor        ebx, ebx
004b881c  85c0                     test       eax, eax
004b881e  7e27                     jle        0x4b8847
004b8820  8b4738                   mov        eax, dword ptr [edi + 0x38]
004b8823  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b8826  8d149d00000000           lea        edx, [ebx*4]
004b882d  03c2                     add        eax, edx
004b882f  03ca                     add        ecx, edx
004b8831  8b10                     mov        edx, dword ptr [eax]
004b8833  8b01                     mov        eax, dword ptr [ecx]
004b8835  52                       push       edx
004b8836  50                       push       eax
004b8837  e874450100               call       0x4ccdb0
004b883c  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b883f  83c408                   add        esp, 8
004b8842  43                       inc        ebx
004b8843  3bd8                     cmp        ebx, eax
004b8845  7cd9                     jl         0x4b8820
004b8847  8b0e                     mov        ecx, dword ptr [esi]
004b8849  85c9                     test       ecx, ecx
004b884b  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004b884e  740d                     je         0x4b885d
004b8850  8b07                     mov        eax, dword ptr [edi]
004b8852  85c0                     test       eax, eax
004b8854  7407                     je         0x4b885d
004b8856  50                       push       eax
004b8857  53                       push       ebx
004b8858  e813155700               call       0xa29d70
004b885d  8b4e04                   mov        ecx, dword ptr [esi + 4]
004b8860  85c9                     test       ecx, ecx
004b8862  740e                     je         0x4b8872
004b8864  8b4704                   mov        eax, dword ptr [edi + 4]
004b8867  85c0                     test       eax, eax
004b8869  7407                     je         0x4b8872
004b886b  50                       push       eax
004b886c  53                       push       ebx
004b886d  e8fe145700               call       0xa29d70
004b8872  8b4e08                   mov        ecx, dword ptr [esi + 8]
004b8875  85c9                     test       ecx, ecx
004b8877  740e                     je         0x4b8887
004b8879  8b4708                   mov        eax, dword ptr [edi + 8]
004b887c  85c0                     test       eax, eax
004b887e  7407                     je         0x4b8887
004b8880  50                       push       eax
004b8881  53                       push       ebx
004b8882  e8e9145700               call       0xa29d70
004b8887  8bd7                     mov        edx, edi
004b8889  2bd6                     sub        edx, esi
004b888b  8d5e0c                   lea        ebx, [esi + 0xc]
004b888e  895510                   mov        dword ptr [ebp + 0x10], edx
004b8891  c7450c02000000           mov        dword ptr [ebp + 0xc], 2
004b8898  8b0b                     mov        ecx, dword ptr [ebx]
004b889a  85c9                     test       ecx, ecx
004b889c  7414                     je         0x4b88b2
004b889e  8b0413                   mov        eax, dword ptr [ebx + edx]
004b88a1  85c0                     test       eax, eax
004b88a3  740d                     je         0x4b88b2
004b88a5  8b5508                   mov        edx, dword ptr [ebp + 8]
004b88a8  50                       push       eax
004b88a9  52                       push       edx
004b88aa  e8c1145700               call       0xa29d70
004b88af  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004b88b2  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b88b5  83c304                   add        ebx, 4
004b88b8  48                       dec        eax
004b88b9  89450c                   mov        dword ptr [ebp + 0xc], eax
004b88bc  75da                     jne        0x4b8898
004b88be  8b4e14                   mov        ecx, dword ptr [esi + 0x14]
004b88c1  85c9                     test       ecx, ecx
004b88c3  7411                     je         0x4b88d6
004b88c5  8b4714                   mov        eax, dword ptr [edi + 0x14]
004b88c8  85c0                     test       eax, eax
004b88ca  740a                     je         0x4b88d6
004b88cc  50                       push       eax
004b88cd  8b4508                   mov        eax, dword ptr [ebp + 8]
004b88d0  50                       push       eax
004b88d1  e89a145700               call       0xa29d70
004b88d6  8b4e18                   mov        ecx, dword ptr [esi + 0x18]
004b88d9  85c9                     test       ecx, ecx
004b88db  7411                     je         0x4b88ee
004b88dd  8b4718                   mov        eax, dword ptr [edi + 0x18]
004b88e0  85c0                     test       eax, eax
004b88e2  740a                     je         0x4b88ee
004b88e4  8b5508                   mov        edx, dword ptr [ebp + 8]
004b88e7  50                       push       eax
004b88e8  52                       push       edx
004b88e9  e882145700               call       0xa29d70
004b88ee  8b4e1c                   mov        ecx, dword ptr [esi + 0x1c]
004b88f1  85c9                     test       ecx, ecx
004b88f3  7411                     je         0x4b8906
004b88f5  8b471c                   mov        eax, dword ptr [edi + 0x1c]
004b88f8  85c0                     test       eax, eax
004b88fa  740a                     je         0x4b8906
004b88fc  50                       push       eax
004b88fd  8b4508                   mov        eax, dword ptr [ebp + 8]
004b8900  50                       push       eax
004b8901  e86a145700               call       0xa29d70
004b8906  8b4e20                   mov        ecx, dword ptr [esi + 0x20]
004b8909  85c9                     test       ecx, ecx
004b890b  7411                     je         0x4b891e
004b890d  8b4720                   mov        eax, dword ptr [edi + 0x20]
004b8910  85c0                     test       eax, eax
004b8912  740a                     je         0x4b891e
004b8914  8b5508                   mov        edx, dword ptr [ebp + 8]
004b8917  50                       push       eax
004b8918  52                       push       edx
004b8919  e852145700               call       0xa29d70
004b891e  8b4628                   mov        eax, dword ptr [esi + 0x28]
004b8921  85c0                     test       eax, eax
004b8923  7504                     jne        0x4b8929
004b8925  33c9                     xor        ecx, ecx
004b8927  eb08                     jmp        0x4b8931
004b8929  8b4e2c                   mov        ecx, dword ptr [esi + 0x2c]
004b892c  2bc8                     sub        ecx, eax
004b892e  c1f902                   sar        ecx, 2
004b8931  8b5728                   mov        edx, dword ptr [edi + 0x28]
004b8934  85d2                     test       edx, edx
004b8936  741d                     je         0x4b8955
004b8938  8b472c                   mov        eax, dword ptr [edi + 0x2c]
004b893b  2bc2                     sub        eax, edx
004b893d  c1f802                   sar        eax, 2
004b8940  3bc8                     cmp        ecx, eax
004b8942  7311                     jae        0x4b8955
004b8944  8b4e28                   mov        ecx, dword ptr [esi + 0x28]
004b8947  85c9                     test       ecx, ecx
004b8949  7505                     jne        0x4b8950
004b894b  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b894e  eb1c                     jmp        0x4b896c
004b8950  8b462c                   mov        eax, dword ptr [esi + 0x2c]
004b8953  eb0f                     jmp        0x4b8964
004b8955  8b4f28                   mov        ecx, dword ptr [edi + 0x28]
004b8958  85c9                     test       ecx, ecx
004b895a  7505                     jne        0x4b8961
004b895c  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b895f  eb0b                     jmp        0x4b896c
004b8961  8b472c                   mov        eax, dword ptr [edi + 0x2c]
004b8964  2bc1                     sub        eax, ecx
004b8966  c1f802                   sar        eax, 2
004b8969  894510                   mov        dword ptr [ebp + 0x10], eax
004b896c  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b896f  33db                     xor        ebx, ebx
004b8971  85c0                     test       eax, eax
004b8973  7e2d                     jle        0x4b89a2
004b8975  8b4628                   mov        eax, dword ptr [esi + 0x28]
004b8978  8d0c98                   lea        ecx, [eax + ebx*4]
004b897b  833900                   cmp        dword ptr [ecx], 0
004b897e  741a                     je         0x4b899a
004b8980  8b5728                   mov        edx, dword ptr [edi + 0x28]
004b8983  8d049a                   lea        eax, [edx + ebx*4]
004b8986  8b10                     mov        edx, dword ptr [eax]
004b8988  85d2                     test       edx, edx
004b898a  740e                     je         0x4b899a
004b898c  8b09                     mov        ecx, dword ptr [ecx]
004b898e  8bc2                     mov        eax, edx
004b8990  8b5508                   mov        edx, dword ptr [ebp + 8]
004b8993  50                       push       eax
004b8994  52                       push       edx
004b8995  e8d6135700               call       0xa29d70
004b899a  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b899d  43                       inc        ebx
004b899e  3bd8                     cmp        ebx, eax
004b89a0  7cd3                     jl         0x4b8975
004b89a2  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b89a5  85c0                     test       eax, eax
004b89a7  7504                     jne        0x4b89ad
004b89a9  33c9                     xor        ecx, ecx
004b89ab  eb08                     jmp        0x4b89b5
004b89ad  8b4e3c                   mov        ecx, dword ptr [esi + 0x3c]
004b89b0  2bc8                     sub        ecx, eax
004b89b2  c1f902                   sar        ecx, 2
004b89b5  8b5738                   mov        edx, dword ptr [edi + 0x38]
004b89b8  85d2                     test       edx, edx
004b89ba  741d                     je         0x4b89d9
004b89bc  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b89bf  2bc2                     sub        eax, edx
004b89c1  c1f802                   sar        eax, 2
004b89c4  3bc8                     cmp        ecx, eax
004b89c6  7311                     jae        0x4b89d9
004b89c8  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b89cb  85c9                     test       ecx, ecx
004b89cd  7505                     jne        0x4b89d4
004b89cf  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b89d2  eb1c                     jmp        0x4b89f0
004b89d4  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b89d7  eb0f                     jmp        0x4b89e8
004b89d9  8b4f38                   mov        ecx, dword ptr [edi + 0x38]
004b89dc  85c9                     test       ecx, ecx
004b89de  7505                     jne        0x4b89e5
004b89e0  894d10                   mov        dword ptr [ebp + 0x10], ecx
004b89e3  eb0b                     jmp        0x4b89f0
004b89e5  8b473c                   mov        eax, dword ptr [edi + 0x3c]
004b89e8  2bc1                     sub        eax, ecx
004b89ea  c1f802                   sar        eax, 2
004b89ed  894510                   mov        dword ptr [ebp + 0x10], eax
004b89f0  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b89f3  33db                     xor        ebx, ebx
004b89f5  85c0                     test       eax, eax
004b89f7  7e34                     jle        0x4b8a2d
004b89f9  8da42400000000           lea        esp, [esp]
004b8a00  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b8a03  8d0c98                   lea        ecx, [eax + ebx*4]
004b8a06  833900                   cmp        dword ptr [ecx], 0
004b8a09  741a                     je         0x4b8a25
004b8a0b  8b5738                   mov        edx, dword ptr [edi + 0x38]
004b8a0e  8d049a                   lea        eax, [edx + ebx*4]
004b8a11  8b10                     mov        edx, dword ptr [eax]
004b8a13  85d2                     test       edx, edx
004b8a15  740e                     je         0x4b8a25
004b8a17  8b09                     mov        ecx, dword ptr [ecx]
004b8a19  8bc2                     mov        eax, edx
004b8a1b  8b5508                   mov        edx, dword ptr [ebp + 8]
004b8a1e  50                       push       eax
004b8a1f  52                       push       edx
004b8a20  e84b135700               call       0xa29d70
004b8a25  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b8a28  43                       inc        ebx
004b8a29  3bd8                     cmp        ebx, eax
004b8a2b  7cd3                     jl         0x4b8a00
004b8a2d  5f                       pop        edi
004b8a2e  5e                       pop        esi
004b8a2f  5b                       pop        ebx
004b8a30  5d                       pop        ebp
004b8a31  c2                       .byte      0xc2

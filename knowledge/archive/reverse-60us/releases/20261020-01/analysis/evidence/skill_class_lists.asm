; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 008a0ae0..008a0da0 (end exclusive); file offset 004a0ae0
; This is an instruction excerpt, not a recovered original source file.
008a0ae0  55                       push       ebp
008a0ae1  8bec                     mov        ebp, esp
008a0ae3  6aff                     push       -1
008a0ae5  680424c800               push       0xc82404
008a0aea  64a100000000             mov        eax, dword ptr fs:[0]
008a0af0  50                       push       eax
008a0af1  64892500000000           mov        dword ptr fs:[0], esp
008a0af8  83ec2c                   sub        esp, 0x2c
008a0afb  8b4508                   mov        eax, dword ptr [ebp + 8]
008a0afe  6800010000               push       0x100
008a0b03  50                       push       eax
008a0b04  6878ee0b01               push       0x10bee78
008a0b09  e8b8fd3500               call       0xc008c6
008a0b0e  6878ee0b01               push       0x10bee78
008a0b13  e8b5f23500               call       0xbffdcd
008a0b18  83c410                   add        esp, 0x10
008a0b1b  66833c4576ee0b015c       cmp        word ptr [eax*2 + 0x10bee76], 0x5c
008a0b24  742f                     je         0x8a0b55
008a0b26  6878ee0b01               push       0x10bee78
008a0b2b  e89df23500               call       0xbffdcd
008a0b30  83c404                   add        esp, 4
008a0b33  66833c4576ee0b012f       cmp        word ptr [eax*2 + 0x10bee76], 0x2f
008a0b3c  7417                     je         0x8a0b55
008a0b3e  6800010000               push       0x100
008a0b43  6804b9ca00               push       0xcab904
008a0b48  6878ee0b01               push       0x10bee78
008a0b4d  e8f0163600               call       0xc02242
008a0b52  83c40c                   add        esp, 0xc
008a0b55  53                       push       ebx
008a0b56  8d4de4                   lea        ecx, [ebp - 0x1c]
008a0b59  e8822ef9ff               call       0x8339e0
008a0b5e  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008a0b61  51                       push       ecx
008a0b62  8d55e4                   lea        edx, [ebp - 0x1c]
008a0b65  6878ee0b01               push       0x10bee78
008a0b6a  33db                     xor        ebx, ebx
008a0b6c  52                       push       edx
008a0b6d  895dfc                   mov        dword ptr [ebp - 4], ebx
008a0b70  e85b0ff9ff               call       0x831ad0
008a0b75  83c40c                   add        esp, 0xc
008a0b78  84c0                     test       al, al
008a0b7a  7537                     jne        0x8a0bb3
008a0b7c  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
008a0b7f  8b08                     mov        ecx, dword ptr [eax]
008a0b81  50                       push       eax
008a0b82  51                       push       ecx
008a0b83  8d45f0                   lea        eax, [ebp - 0x10]
008a0b86  50                       push       eax
008a0b87  8d4de4                   lea        ecx, [ebp - 0x1c]
008a0b8a  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008a0b91  e8da20f9ff               call       0x832c70
008a0b96  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
008a0b99  51                       push       ecx
008a0b9a  e83ef43500               call       0xbfffdd
008a0b9f  83c404                   add        esp, 4
008a0ba2  32c0                     xor        al, al
008a0ba4  5b                       pop        ebx
008a0ba5  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a0ba8  64890d00000000           mov        dword ptr fs:[0], ecx
008a0baf  8be5                     mov        esp, ebp
008a0bb1  5d                       pop        ebp
008a0bb2  c3                       ret        
008a0bb3  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
008a0bb6  8b01                     mov        eax, dword ptr [ecx]
008a0bb8  3bc1                     cmp        eax, ecx
008a0bba  56                       push       esi
008a0bbb  57                       push       edi
008a0bbc  8945f0                   mov        dword ptr [ebp - 0x10], eax
008a0bbf  7467                     je         0x8a0c28
008a0bc1  83782808                 cmp        dword ptr [eax + 0x28], 8
008a0bc5  7205                     jb         0x8a0bcc
008a0bc7  8b7814                   mov        edi, dword ptr [eax + 0x14]
008a0bca  eb03                     jmp        0x8a0bcf
008a0bcc  8d7814                   lea        edi, [eax + 0x14]
008a0bcf  8b700c                   mov        esi, dword ptr [eax + 0xc]
008a0bd2  83fe06                   cmp        esi, 6
008a0bd5  7224                     jb         0x8a0bfb
008a0bd7  6a06                     push       6
008a0bd9  56                       push       esi
008a0bda  686ccbcd00               push       0xcdcb6c
008a0bdf  68a0b3cb00               push       0xcbb3a0
008a0be4  ff15bc2eff00             call       dword ptr [0xff2ebc]
008a0bea  83c410                   add        esp, 0x10
008a0bed  53                       push       ebx
008a0bee  53                       push       ebx
008a0bef  53                       push       ebx
008a0bf0  688c0000c0               push       0xc000008c
008a0bf5  ff1528f04001             call       dword ptr [0x140f028]
008a0bfb  57                       push       edi
008a0bfc  8d1476                   lea        edx, [esi + esi*2]
008a0bff  8d049588f00b01           lea        eax, [edx*4 + 0x10bf088]
008a0c06  6878ee0b01               push       0x10bee78
008a0c0b  50                       push       eax
008a0c0c  e8bf0ef9ff               call       0x831ad0
008a0c11  83c40c                   add        esp, 0xc
008a0c14  84c0                     test       al, al
008a0c16  745f                     je         0x8a0c77
008a0c18  8d4df0                   lea        ecx, [ebp - 0x10]
008a0c1b  e850ab3000               call       0xbab770
008a0c20  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
008a0c23  3b45e8                   cmp        eax, dword ptr [ebp - 0x18]
008a0c26  7599                     jne        0x8a0bc1
008a0c28  687090e200               push       0xe29070
008a0c2d  6878ee0b01               push       0x10bee78
008a0c32  e859ebf8ff               call       0x82f790
008a0c37  83c408                   add        esp, 8
008a0c3a  84c0                     test       al, al
008a0c3c  7572                     jne        0x8a0cb0
008a0c3e  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
008a0c41  8b08                     mov        ecx, dword ptr [eax]
008a0c43  50                       push       eax
008a0c44  51                       push       ecx
008a0c45  8d45f0                   lea        eax, [ebp - 0x10]
008a0c48  50                       push       eax
008a0c49  8d4de4                   lea        ecx, [ebp - 0x1c]
008a0c4c  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008a0c53  e81820f9ff               call       0x832c70
008a0c58  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
008a0c5b  51                       push       ecx
008a0c5c  e87cf33500               call       0xbfffdd
008a0c61  83c404                   add        esp, 4
008a0c64  5f                       pop        edi
008a0c65  5e                       pop        esi
008a0c66  32c0                     xor        al, al
008a0c68  5b                       pop        ebx
008a0c69  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a0c6c  64890d00000000           mov        dword ptr fs:[0], ecx
008a0c73  8be5                     mov        esp, ebp
008a0c75  5d                       pop        ebp
008a0c76  c3                       ret        
008a0c77  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
008a0c7a  8b08                     mov        ecx, dword ptr [eax]
008a0c7c  50                       push       eax
008a0c7d  51                       push       ecx
008a0c7e  8d4df0                   lea        ecx, [ebp - 0x10]
008a0c81  51                       push       ecx
008a0c82  8d4de4                   lea        ecx, [ebp - 0x1c]
008a0c85  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008a0c8c  e8df1ff9ff               call       0x832c70
008a0c91  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
008a0c94  52                       push       edx
008a0c95  e843f33500               call       0xbfffdd
008a0c9a  83c404                   add        esp, 4
008a0c9d  5f                       pop        edi
008a0c9e  5e                       pop        esi
008a0c9f  32c0                     xor        al, al
008a0ca1  5b                       pop        ebx
008a0ca2  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a0ca5  64890d00000000           mov        dword ptr fs:[0], ecx
008a0cac  8be5                     mov        esp, ebp
008a0cae  5d                       pop        ebp
008a0caf  c3                       ret        
008a0cb0  b928120501               mov        ecx, 0x1051228
008a0cb5  33ff                     xor        edi, edi
008a0cb7  e8b41c0100               call       0x8b2970
008a0cbc  3bc3                     cmp        eax, ebx
008a0cbe  0f8494000000             je         0x8a0d58
008a0cc4  83f802                   cmp        eax, 2
008a0cc7  750e                     jne        0x8a0cd7
008a0cc9  b928120501               mov        ecx, 0x1051228
008a0cce  e81d1d0100               call       0x8b29f0
008a0cd3  8bf8                     mov        edi, eax
008a0cd5  eb6f                     jmp        0x8a0d46
008a0cd7  83f806                   cmp        eax, 6
008a0cda  756a                     jne        0x8a0d46
008a0cdc  b928120501               mov        ecx, 0x1051228
008a0ce1  e8ea1d0100               call       0x8b2ad0
008a0ce6  50                       push       eax
008a0ce7  e8641f1f00               call       0xa92c50
008a0cec  8bf0                     mov        esi, eax
008a0cee  56                       push       esi
008a0cef  c745e007000000           mov        dword ptr [ebp - 0x20], 7
008a0cf6  895ddc                   mov        dword ptr [ebp - 0x24], ebx
008a0cf9  66895dcc                 mov        word ptr [ebp - 0x34], bx
008a0cfd  e8cbf03500               call       0xbffdcd
008a0d02  83c408                   add        esp, 8
008a0d05  50                       push       eax
008a0d06  56                       push       esi
008a0d07  8d4dc8                   lea        ecx, [ebp - 0x38]
008a0d0a  e87121b6ff               call       0x402e80
008a0d0f  8d55c8                   lea        edx, [ebp - 0x38]
008a0d12  52                       push       edx
008a0d13  b978f00b01               mov        ecx, 0x10bf078
008a0d18  c645fc01                 mov        byte ptr [ebp - 4], 1
008a0d1c  e80f8dc2ff               call       0x4c9a30
008a0d21  8938                     mov        dword ptr [eax], edi
008a0d23  837de008                 cmp        dword ptr [ebp - 0x20], 8
008a0d27  885dfc                   mov        byte ptr [ebp - 4], bl
008a0d2a  720c                     jb         0x8a0d38
008a0d2c  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
008a0d2f  50                       push       eax
008a0d30  e8a8f23500               call       0xbfffdd
008a0d35  83c404                   add        esp, 4
008a0d38  c745e007000000           mov        dword ptr [ebp - 0x20], 7
008a0d3f  895ddc                   mov        dword ptr [ebp - 0x24], ebx
008a0d42  66895dcc                 mov        word ptr [ebp - 0x34], bx
008a0d46  b928120501               mov        ecx, 0x1051228
008a0d4b  e8201c0100               call       0x8b2970
008a0d50  3bc3                     cmp        eax, ebx
008a0d52  0f856cffffff             jne        0x8a0cc4
008a0d58  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
008a0d5b  8b08                     mov        ecx, dword ptr [eax]
008a0d5d  50                       push       eax
008a0d5e  51                       push       ecx
008a0d5f  8d4df0                   lea        ecx, [ebp - 0x10]
008a0d62  51                       push       ecx
008a0d63  8d4de4                   lea        ecx, [ebp - 0x1c]
008a0d66  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008a0d6d  e8fe1ef9ff               call       0x832c70
008a0d72  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
008a0d75  52                       push       edx
008a0d76  e862f23500               call       0xbfffdd
008a0d7b  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a0d7e  83c404                   add        esp, 4
008a0d81  5f                       pop        edi
008a0d82  5e                       pop        esi
008a0d83  b001                     mov        al, 1
008a0d85  5b                       pop        ebx
008a0d86  64890d00000000           mov        dword ptr fs:[0], ecx
008a0d8d  8be5                     mov        esp, ebp
008a0d8f  5d                       pop        ebp
008a0d90  c3                       ret        
008a0d91  cc                       int3       
008a0d92  cc                       int3       
008a0d93  cc                       int3       
008a0d94  cc                       int3       
008a0d95  cc                       int3       
008a0d96  cc                       int3       
008a0d97  cc                       int3       
008a0d98  cc                       int3       
008a0d99  cc                       int3       
008a0d9a  cc                       int3       
008a0d9b  cc                       int3       
008a0d9c  cc                       int3       
008a0d9d  cc                       int3       
008a0d9e  cc                       int3       
008a0d9f  cc                       int3       

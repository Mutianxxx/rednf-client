; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00550e10..00550f5b (end exclusive); file offset 00150e10
; This is an instruction excerpt, not a recovered original source file.
00550e10  55                       push       ebp
00550e11  8bec                     mov        ebp, esp
00550e13  83ec0c                   sub        esp, 0xc
00550e16  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00550e19  83f8ff                   cmp        eax, -1
00550e1c  56                       push       esi
00550e1d  8bf1                     mov        esi, ecx
00550e1f  750b                     jne        0x550e2c
00550e21  8d8e1c030000             lea        ecx, [esi + 0x31c]
00550e27  e83412ebff               call       0x402060
00550e2c  8b9684010000             mov        edx, dword ptr [esi + 0x184]
00550e32  85d2                     test       edx, edx
00550e34  7504                     jne        0x550e3a
00550e36  33c9                     xor        ecx, ecx
00550e38  eb0b                     jmp        0x550e45
00550e3a  8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00550e40  2bca                     sub        ecx, edx
00550e42  c1f903                   sar        ecx, 3
00550e45  3bc8                     cmp        ecx, eax
00550e47  7315                     jae        0x550e5e
00550e49  8b8e84010000             mov        ecx, dword ptr [esi + 0x184]
00550e4f  85c9                     test       ecx, ecx
00550e51  740f                     je         0x550e62
00550e53  8b8688010000             mov        eax, dword ptr [esi + 0x188]
00550e59  2bc1                     sub        eax, ecx
00550e5b  c1f803                   sar        eax, 3
00550e5e  85c0                     test       eax, eax
00550e60  7f20                     jg         0x550e82
00550e62  8d4e10                   lea        ecx, [esi + 0x10]
00550e65  e886225000               call       0xa530f0
00550e6a  50                       push       eax
00550e6b  6858cdcd00               push       0xcdcd58
00550e70  ff15bc2eff00             call       dword ptr [0xff2ebc]
00550e76  83c408                   add        esp, 8
00550e79  33c0                     xor        eax, eax
00550e7b  5e                       pop        esi
00550e7c  8be5                     mov        esp, ebp
00550e7e  5d                       pop        ebp
00550e7f  c20800                   ret        8
00550e82  8b8e84010000             mov        ecx, dword ptr [esi + 0x184]
00550e88  57                       push       edi
00550e89  8d4cc1f8                 lea        ecx, [ecx + eax*8 - 8]
00550e8d  e8ce11ebff               call       0x402060
00550e92  8b7d08                   mov        edi, dword ptr [ebp + 8]
00550e95  85ff                     test       edi, edi
00550e97  8945fc                   mov        dword ptr [ebp - 4], eax
00550e9a  0f84b3000000             je         0x550f53
00550ea0  53                       push       ebx
00550ea1  8d4e08                   lea        ecx, [esi + 8]
00550ea4  e8b711ebff               call       0x402060
00550ea9  50                       push       eax
00550eaa  8bcf                     mov        ecx, edi
00550eac  e89f300000               call       0x553f50
00550eb1  d95d0c                   fstp       dword ptr [ebp + 0xc]
00550eb4  8d9e18020000             lea        ebx, [esi + 0x218]
00550eba  8bcb                     mov        ecx, ebx
00550ebc  e89f11ebff               call       0x402060
00550ec1  83f801                   cmp        eax, 1
00550ec4  750e                     jne        0x550ed4
00550ec6  8b17                     mov        edx, dword ptr [edi]
00550ec8  6a00                     push       0
00550eca  8bcf                     mov        ecx, edi
00550ecc  ff92b0060000             call       dword ptr [edx + 0x6b0]
00550ed2  eb18                     jmp        0x550eec
00550ed4  8bcb                     mov        ecx, ebx
00550ed6  e88511ebff               call       0x402060
00550edb  83f802                   cmp        eax, 2
00550ede  7512                     jne        0x550ef2
00550ee0  8b07                     mov        eax, dword ptr [edi]
00550ee2  6a02                     push       2
00550ee4  8bcf                     mov        ecx, edi
00550ee6  ff90b0060000             call       dword ptr [eax + 0x6b0]
00550eec  d84d0c                   fmul       dword ptr [ebp + 0xc]
00550eef  d95d0c                   fstp       dword ptr [ebp + 0xc]
00550ef2  8d8ed8030000             lea        ecx, [esi + 0x3d8]
00550ef8  e86311ebff               call       0x402060
00550efd  85c0                     test       eax, eax
00550eff  7430                     je         0x550f31
00550f01  8d9e0c030000             lea        ebx, [esi + 0x30c]
00550f07  8bcb                     mov        ecx, ebx
00550f09  e85211ebff               call       0x402060
00550f0e  85c0                     test       eax, eax
00550f10  7e1f                     jle        0x550f31
00550f12  d9450c                   fld        dword ptr [ebp + 0xc]
00550f15  8bcb                     mov        ecx, ebx
00550f17  dd5df4                   fstp       qword ptr [ebp - 0xc]
00550f1a  e84111ebff               call       0x402060
00550f1f  89450c                   mov        dword ptr [ebp + 0xc], eax
00550f22  db450c                   fild       dword ptr [ebp + 0xc]
00550f25  dc0de8cccd00             fmul       qword ptr [0xcdcce8]
00550f2b  dc6df4                   fsubr      qword ptr [ebp - 0xc]
00550f2e  d95d0c                   fstp       dword ptr [ebp + 0xc]
00550f31  8d4e08                   lea        ecx, [esi + 8]
00550f34  e82711ebff               call       0x402060
00550f39  db45fc                   fild       dword ptr [ebp - 4]
00550f3c  50                       push       eax
00550f3d  6a03                     push       3
00550f3f  d84d0c                   fmul       dword ptr [ebp + 0xc]
00550f42  6a00                     push       0
00550f44  e8fb056b00               call       0xc01544
00550f49  50                       push       eax
00550f4a  57                       push       edi
00550f4b  8bce                     mov        ecx, esi
00550f4d  e8eeecffff               call       0x54fc40
00550f52  5b                       pop        ebx
00550f53  5f                       pop        edi
00550f54  5e                       pop        esi
00550f55  8be5                     mov        esp, ebp
00550f57  5d                       pop        ebp
00550f58  c20800                   ret        8

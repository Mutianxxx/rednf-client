004b9eb0  55                       push       ebp
004b9eb1  8bec                     mov        ebp, esp
004b9eb3  53                       push       ebx
004b9eb4  56                       push       esi
004b9eb5  8bf1                     mov        esi, ecx
004b9eb7  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b9ebd  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004b9ec0  8b8624160000             mov        eax, dword ptr [esi + 0x1624]
004b9ec6  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004b9ecc  8d0482                   lea        eax, [edx + eax*4]
004b9ecf  8d9e20160000             lea        ebx, [esi + 0x1620]
004b9ed5  8bd0                     mov        edx, eax
004b9ed7  33d1                     xor        edx, ecx
004b9ed9  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b9edc  33d1                     xor        edx, ecx
004b9ede  8910                     mov        dword ptr [eax], edx
004b9ee0  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b9ee6  8b5248                   mov        edx, dword ptr [edx + 0x48]
004b9ee9  8b4304                   mov        eax, dword ptr [ebx + 4]
004b9eec  8d0482                   lea        eax, [edx + eax*4]
004b9eef  57                       push       edi
004b9ef0  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b9ef6  8bd0                     mov        edx, eax
004b9ef8  33d7                     xor        edx, edi
004b9efa  33d1                     xor        edx, ecx
004b9efc  8910                     mov        dword ptr [eax], edx
004b9efe  8b8604010000             mov        eax, dword ptr [esi + 0x104]
004b9f04  85c0                     test       eax, eax
004b9f06  7422                     je         0x4b9f2a
004b9f08  8bcb                     mov        ecx, ebx
004b9f0a  e85181f4ff               call       0x402060
004b9f0f  894508                   mov        dword ptr [ebp + 8], eax
004b9f12  db4508                   fild       dword ptr [ebp + 8]
004b9f15  51                       push       ecx
004b9f16  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004b9f1c  d80d3088cc00             fmul       dword ptr [0xcc8830]
004b9f22  d91c24                   fstp       dword ptr [esp]
004b9f25  e846fd5600               call       0xa29c70
004b9f2a  8b8648010000             mov        eax, dword ptr [esi + 0x148]
004b9f30  85c0                     test       eax, eax
004b9f32  7422                     je         0x4b9f56
004b9f34  8b38                     mov        edi, dword ptr [eax]
004b9f36  8bcb                     mov        ecx, ebx
004b9f38  e82381f4ff               call       0x402060
004b9f3d  894508                   mov        dword ptr [ebp + 8], eax
004b9f40  db4508                   fild       dword ptr [ebp + 8]
004b9f43  51                       push       ecx
004b9f44  8b8e48010000             mov        ecx, dword ptr [esi + 0x148]
004b9f4a  d80d3088cc00             fmul       dword ptr [0xcc8830]
004b9f50  d91c24                   fstp       dword ptr [esp]
004b9f53  ff5704                   call       dword ptr [edi + 4]
004b9f56  8b860c010000             mov        eax, dword ptr [esi + 0x10c]
004b9f5c  8b38                     mov        edi, dword ptr [eax]
004b9f5e  3bf8                     cmp        edi, eax
004b9f60  7430                     je         0x4b9f92
004b9f62  8a471b                   mov        al, byte ptr [edi + 0x1b]
004b9f65  84c0                     test       al, al
004b9f67  741f                     je         0x4b9f88
004b9f69  8bcb                     mov        ecx, ebx
004b9f6b  e8f080f4ff               call       0x402060
004b9f70  894508                   mov        dword ptr [ebp + 8], eax
004b9f73  db4508                   fild       dword ptr [ebp + 8]
004b9f76  51                       push       ecx
004b9f77  8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
004b9f7a  d80d3088cc00             fmul       dword ptr [0xcc8830]
004b9f80  d91c24                   fstp       dword ptr [esp]
004b9f83  e8e8fc5600               call       0xa29c70
004b9f88  8b3f                     mov        edi, dword ptr [edi]
004b9f8a  3bbe0c010000             cmp        edi, dword ptr [esi + 0x10c]
004b9f90  75d0                     jne        0x4b9f62
004b9f92  5f                       pop        edi
004b9f93  5e                       pop        esi
004b9f94  5b                       pop        ebx
004b9f95  5d                       pop        ebp
004b9f96  c20400                   ret        4

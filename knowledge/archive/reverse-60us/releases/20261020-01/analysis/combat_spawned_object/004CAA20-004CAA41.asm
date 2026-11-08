004caa20  55                       push       ebp
004caa21  8bec                     mov        ebp, esp
004caa23  8b4518                   mov        eax, dword ptr [ebp + 0x18]
004caa26  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004caa29  50                       push       eax
004caa2a  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004caa2d  50                       push       eax
004caa2e  50                       push       eax
004caa2f  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004caa32  52                       push       edx
004caa33  8b5508                   mov        edx, dword ptr [ebp + 8]
004caa36  50                       push       eax
004caa37  52                       push       edx
004caa38  e813570800               call       0x550150
004caa3d  5d                       pop        ebp
004caa3e  c21400                   ret        0x14
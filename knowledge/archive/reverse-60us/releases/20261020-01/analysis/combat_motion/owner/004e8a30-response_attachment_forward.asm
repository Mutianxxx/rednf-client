004e8a30  55                       push       ebp
004e8a31  8bec                     mov        ebp, esp
004e8a33  53                       push       ebx
004e8a34  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004e8a37  56                       push       esi
004e8a38  8bf1                     mov        esi, ecx
004e8a3a  8b8648010000             mov        eax, dword ptr [esi + 0x148]
004e8a40  85c0                     test       eax, eax
004e8a42  57                       push       edi
004e8a43  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
004e8a46  740d                     je         0x4e8a55
004e8a48  8b5508                   mov        edx, dword ptr [ebp + 8]
004e8a4b  57                       push       edi
004e8a4c  8bc8                     mov        ecx, eax
004e8a4e  8b01                     mov        eax, dword ptr [ecx]
004e8a50  53                       push       ebx
004e8a51  52                       push       edx
004e8a52  ff501c                   call       dword ptr [eax + 0x1c]
004e8a55  8b8654010000             mov        eax, dword ptr [esi + 0x154]
004e8a5b  85c0                     test       eax, eax
004e8a5d  740d                     je         0x4e8a6c
004e8a5f  8b5508                   mov        edx, dword ptr [ebp + 8]
004e8a62  57                       push       edi
004e8a63  8bc8                     mov        ecx, eax
004e8a65  8b01                     mov        eax, dword ptr [ecx]
004e8a67  53                       push       ebx
004e8a68  52                       push       edx
004e8a69  ff501c                   call       dword ptr [eax + 0x1c]
004e8a6c  5f                       pop        edi
004e8a6d  5e                       pop        esi
004e8a6e  5b                       pop        ebx
004e8a6f  5d                       pop        ebp
004e8a70  c20c00                   ret        0xc

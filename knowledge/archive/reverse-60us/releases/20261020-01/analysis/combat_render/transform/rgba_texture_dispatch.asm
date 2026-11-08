00b0e050 55                       push       ebp
00b0e051 8bec                     mov        ebp, esp
00b0e053 8bd1                     mov        edx, ecx
00b0e055 8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00b0e058 85c9                     test       ecx, ecx
00b0e05a 0f84a1000000             je         0xb0e101
00b0e060 d905cc46cc00             fld        dword ptr [0xcc46cc]
00b0e066 d94524                   fld        dword ptr [ebp + 0x24]
00b0e069 dae9                     fucompp    
00b0e06b dfe0                     fnstsw     ax
00b0e06d f6c444                   test       ah, 0x44
00b0e070 7a18                     jp         0xb0e08a
00b0e072 8b4114                   mov        eax, dword ptr [ecx + 0x14]
00b0e075 d1e8                     shr        eax, 1
00b0e077 85c0                     test       eax, eax
00b0e079 894524                   mov        dword ptr [ebp + 0x24], eax
00b0e07c db4524                   fild       dword ptr [ebp + 0x24]
00b0e07f 7d06                     jge        0xb0e087
00b0e081 d805cc46cc00             fadd       dword ptr [0xcc46cc]
00b0e087 d95d24                   fstp       dword ptr [ebp + 0x24]
00b0e08a d905cc46cc00             fld        dword ptr [0xcc46cc]
00b0e090 d94528                   fld        dword ptr [ebp + 0x28]
00b0e093 dae9                     fucompp    
00b0e095 dfe0                     fnstsw     ax
00b0e097 f6c444                   test       ah, 0x44
00b0e09a 7a18                     jp         0xb0e0b4
00b0e09c 8b4118                   mov        eax, dword ptr [ecx + 0x18]
00b0e09f d1e8                     shr        eax, 1
00b0e0a1 85c0                     test       eax, eax
00b0e0a3 894528                   mov        dword ptr [ebp + 0x28], eax
00b0e0a6 db4528                   fild       dword ptr [ebp + 0x28]
00b0e0a9 7d06                     jge        0xb0e0b1
00b0e0ab d805cc46cc00             fadd       dword ptr [0xcc46cc]
00b0e0b1 d95d28                   fstp       dword ptr [ebp + 0x28]
00b0e0b4 8b4528                   mov        eax, dword ptr [ebp + 0x28]
00b0e0b7 53                       push       ebx
00b0e0b8 56                       push       esi
00b0e0b9 57                       push       edi
00b0e0ba 6a24                     push       0x24
00b0e0bc 0fb67d22                 movzx      edi, byte ptr [ebp + 0x22]
00b0e0c0 6a00                     push       0
00b0e0c2 50                       push       eax
00b0e0c3 8b4524                   mov        eax, dword ptr [ebp + 0x24]
00b0e0c6 50                       push       eax
00b0e0c7 8b4518                   mov        eax, dword ptr [ebp + 0x18]
00b0e0ca 50                       push       eax
00b0e0cb 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00b0e0ce 50                       push       eax
00b0e0cf 8b451c                   mov        eax, dword ptr [ebp + 0x1c]
00b0e0d2 8b31                     mov        esi, dword ptr [ecx]
00b0e0d4 50                       push       eax
00b0e0d5 8b4520                   mov        eax, dword ptr [ebp + 0x20]
00b0e0d8 8bd8                     mov        ebx, eax
00b0e0da 81e3ff000000             and        ebx, 0xff
00b0e0e0 c1e310                   shl        ebx, 0x10
00b0e0e3 6a00                     push       0
00b0e0e5 2500ff00ff               and        eax, 0xff00ff00
00b0e0ea 0bfb                     or         edi, ebx
00b0e0ec 0bf8                     or         edi, eax
00b0e0ee 8b4508                   mov        eax, dword ptr [ebp + 8]
00b0e0f1 57                       push       edi
00b0e0f2 52                       push       edx
00b0e0f3 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00b0e0f6 52                       push       edx
00b0e0f7 50                       push       eax
00b0e0f8 ff96a0000000             call       dword ptr [esi + 0xa0]
00b0e0fe 5f                       pop        edi
00b0e0ff 5e                       pop        esi
00b0e100 5b                       pop        ebx
00b0e101 5d                       pop        ebp

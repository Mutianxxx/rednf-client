008b7ab0 55                       push       ebp
008b7ab1 8bec                     mov        ebp, esp
008b7ab3 51                       push       ecx
008b7ab4 57                       push       edi
008b7ab5 8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
008b7ab8 85ff                     test       edi, edi
008b7aba 7507                     jne        0x8b7ac3
008b7abc 32c0                     xor        al, al
008b7abe 5f                       pop        edi
008b7abf 8be5                     mov        esp, ebp
008b7ac1 5d                       pop        ebp
008b7ac2 c3                       ret        
008b7ac3 56                       push       esi
008b7ac4 8b7508                   mov        esi, dword ptr [ebp + 8]
008b7ac7 d94613                   fld        dword ptr [esi + 0x13]
008b7aca 8a868e010000             mov        al, byte ptr [esi + 0x18e]
008b7ad0 84c0                     test       al, al
008b7ad2 d80578b5cc00             fadd       dword ptr [0xccb578]
008b7ad8 8b8e95010000             mov        ecx, dword ptr [esi + 0x195]
008b7ade d95d0c                   fstp       dword ptr [ebp + 0xc]
008b7ae1 7413                     je         0x8b7af6
008b7ae3 8bc1                     mov        eax, ecx
008b7ae5 2581000000               and        eax, 0x81
008b7aea 3c81                     cmp        al, 0x81
008b7aec 752e                     jne        0x8b7b1c
008b7aee d9450c                   fld        dword ptr [ebp + 0xc]
008b7af1 d8465b                   fadd       dword ptr [esi + 0x5b]
008b7af4 eb23                     jmp        0x8b7b19
008b7af6 8bd1                     mov        edx, ecx
008b7af8 83e211                   and        edx, 0x11
008b7afb 80fa11                   cmp        dl, 0x11
008b7afe 751c                     jne        0x8b7b1c
008b7b00 8a4605                   mov        al, byte ptr [esi + 5]
008b7b03 84c0                     test       al, al
008b7b05 7508                     jne        0x8b7b0f
008b7b07 d9450c                   fld        dword ptr [ebp + 0xc]
008b7b0a d8464b                   fadd       dword ptr [esi + 0x4b]
008b7b0d eb0a                     jmp        0x8b7b19
008b7b0f 3c01                     cmp        al, 1
008b7b11 7509                     jne        0x8b7b1c
008b7b13 d9450c                   fld        dword ptr [ebp + 0xc]
008b7b16 d8464f                   fadd       dword ptr [esi + 0x4f]
008b7b19 d95d0c                   fstp       dword ptr [ebp + 0xc]
008b7b1c 8a86b5010000             mov        al, byte ptr [esi + 0x1b5]
008b7b22 84c0                     test       al, al
008b7b24 742d                     je         0x8b7b53
008b7b26 d9450c                   fld        dword ptr [ebp + 0xc]
008b7b29 83e111                   and        ecx, 0x11
008b7b2c 80f911                   cmp        cl, 0x11
008b7b2f d84617                   fadd       dword ptr [esi + 0x17]
008b7b32 d95d0c                   fstp       dword ptr [ebp + 0xc]
008b7b35 751c                     jne        0x8b7b53
008b7b37 8a4605                   mov        al, byte ptr [esi + 5]
008b7b3a 84c0                     test       al, al
008b7b3c 7508                     jne        0x8b7b46
008b7b3e d9450c                   fld        dword ptr [ebp + 0xc]
008b7b41 d84653                   fadd       dword ptr [esi + 0x53]
008b7b44 eb0a                     jmp        0x8b7b50
008b7b46 3c01                     cmp        al, 1
008b7b48 7509                     jne        0x8b7b53
008b7b4a d9450c                   fld        dword ptr [ebp + 0xc]
008b7b4d d84657                   fadd       dword ptr [esi + 0x57]
008b7b50 d95d0c                   fstp       dword ptr [ebp + 0xc]
008b7b53 8b8699010000             mov        eax, dword ptr [esi + 0x199]
008b7b59 83e011                   and        eax, 0x11
008b7b5c 3c11                     cmp        al, 0x11
008b7b5e 750c                     jne        0x8b7b6c
008b7b60 d9450c                   fld        dword ptr [ebp + 0xc]
008b7b63 d8a6bf000000             fsub       dword ptr [esi + 0xbf]
008b7b69 d95d0c                   fstp       dword ptr [ebp + 0xc]
008b7b6c 8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
008b7b6f 51                       push       ecx
008b7b70 e8eb65ffff               call       0x8ae160
008b7b75 99                       cdq        
008b7b76 b910270000               mov        ecx, 0x2710
008b7b7b f7f9                     idiv       ecx
008b7b7d 83c404                   add        esp, 4
008b7b80 8955fc                   mov        dword ptr [ebp - 4], edx
008b7b83 db45fc                   fild       dword ptr [ebp - 4]
008b7b86 d9450c                   fld        dword ptr [ebp + 0xc]
008b7b89 d80dd8b9cc00             fmul       dword ptr [0xccb9d8]
008b7b8f ded9                     fcompp     
008b7b91 dfe0                     fnstsw     ax
008b7b93 f6c441                   test       ah, 0x41
008b7b96 7539                     jne        0x8b7bd1
008b7b98 b990fe0b01               mov        ecx, 0x10bfe90
008b7b9d e80eb8b7ff               call       0x4333b0
008b7ba2 8b9695010000             mov        edx, dword ptr [esi + 0x195]
008b7ba8 83e211                   and        edx, 0x11
008b7bab 80fa11                   cmp        dl, 0x11
008b7bae 7503                     jne        0x8b7bb3
008b7bb0 d84e6f                   fmul       dword ptr [esi + 0x6f]
008b7bb3 d80f                     fmul       dword ptr [edi]
008b7bb5 33c0                     xor        eax, eax
008b7bb7 d91f                     fstp       dword ptr [edi]
008b7bb9 c686a501000001           mov        byte ptr [esi + 0x1a5], 1
008b7bc0 8a8ea5010000             mov        cl, byte ptr [esi + 0x1a5]
008b7bc6 84c9                     test       cl, cl
008b7bc8 5e                       pop        esi
008b7bc9 0f95c0                   setne      al
008b7bcc 5f                       pop        edi
008b7bcd 8be5                     mov        esp, ebp
008b7bcf 5d                       pop        ebp
008b7bd0 c3                       ret        
008b7bd1 c686a501000000           mov        byte ptr [esi + 0x1a5], 0
008b7bd8 8a8ea5010000             mov        cl, byte ptr [esi + 0x1a5]
008b7bde 33c0                     xor        eax, eax
008b7be0 84c9                     test       cl, cl
008b7be2 5e                       pop        esi
008b7be3 0f95c0                   setne      al
008b7be6 5f                       pop        edi
008b7be7 8be5                     mov        esp, ebp
008b7be9 5d                       pop        ebp
008b7bea c3                       ret        
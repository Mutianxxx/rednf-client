0140e000 83ec04                   sub        esp, 4
0140e003 50                       push       eax
0140e004 53                       push       ebx
0140e005 e801000000               call       0x140e00b
0140e00a cc                       int3       
0140e00b 58                       pop        eax
0140e00c 8bd8                     mov        ebx, eax
0140e00e 40                       inc        eax
0140e00f 2d00801200               sub        eax, 0x128000
0140e014 2d5d365f00               sub        eax, 0x5f365d
0140e019 0552365f00               add        eax, 0x5f3652
0140e01e 803bcc                   cmp        byte ptr [ebx], 0xcc
0140e021 7519                     jne        0x140e03c
0140e023 c60300                   mov        byte ptr [ebx], 0
0140e026 bb00100000               mov        ebx, 0x1000
0140e02b 68887bcc38               push       0x38cc7b88
0140e030 687e9d150f               push       0xf159d7e
0140e035 53                       push       ebx
0140e036 50                       push       eax
0140e037 e80a000000               call       0x140e046
0140e03c 83c014                   add        eax, 0x14
0140e03f 89442408                 mov        dword ptr [esp + 8], eax
0140e043 5b                       pop        ebx
0140e044 58                       pop        eax
0140e045 c3                       ret        
0140e046 55                       push       ebp
0140e047 8bec                     mov        ebp, esp
0140e049 60                       pushal     
0140e04a 8b7508                   mov        esi, dword ptr [ebp + 8]
0140e04d 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0140e050 c1e902                   shr        ecx, 2
0140e053 8b4510                   mov        eax, dword ptr [ebp + 0x10]
0140e056 8b5d14                   mov        ebx, dword ptr [ebp + 0x14]
0140e059 eb08                     jmp        0x140e063
0140e05b 3106                     xor        dword ptr [esi], eax
0140e05d 011e                     add        dword ptr [esi], ebx
0140e05f 83c604                   add        esi, 4
0140e062 49                       dec        ecx
0140e063 0bc9                     or         ecx, ecx
0140e065 75f4                     jne        0x140e05b
0140e067 61                       popal      
0140e068 c9                       leave      
0140e069 c21000                   ret        0x10
0140e06c 0000                     add        byte ptr [eax], al
0140e06e 0000                     add        byte ptr [eax], al
0140e070 0000                     add        byte ptr [eax], al
0140e072 0000                     add        byte ptr [eax], al
0140e074 0000                     add        byte ptr [eax], al
0140e076 0000                     add        byte ptr [eax], al
0140e078 0000                     add        byte ptr [eax], al
0140e07a 0000                     add        byte ptr [eax], al
0140e07c 0000                     add        byte ptr [eax], al
0140e07e 0000                     add        byte ptr [eax], al
0140e080 0000                     add        byte ptr [eax], al
0140e082 0000                     add        byte ptr [eax], al
0140e084 0000                     add        byte ptr [eax], al
0140e086 0000                     add        byte ptr [eax], al
0140e088 0000                     add        byte ptr [eax], al
0140e08a 0000                     add        byte ptr [eax], al
0140e08c 0000                     add        byte ptr [eax], al
0140e08e 0000                     add        byte ptr [eax], al
0140e090 0000                     add        byte ptr [eax], al
0140e092 0000                     add        byte ptr [eax], al
0140e094 0000                     add        byte ptr [eax], al
0140e096 0000                     add        byte ptr [eax], al
0140e098 0000                     add        byte ptr [eax], al
0140e09a 0000                     add        byte ptr [eax], al
0140e09c 0000                     add        byte ptr [eax], al
0140e09e 0000                     add        byte ptr [eax], al
0140e0a0 0000                     add        byte ptr [eax], al
0140e0a2 0000                     add        byte ptr [eax], al
0140e0a4 0000                     add        byte ptr [eax], al
0140e0a6 0000                     add        byte ptr [eax], al
0140e0a8 0000                     add        byte ptr [eax], al
0140e0aa 0000                     add        byte ptr [eax], al
0140e0ac 0000                     add        byte ptr [eax], al
0140e0ae 0000                     add        byte ptr [eax], al
0140e0b0 0000                     add        byte ptr [eax], al
0140e0b2 0000                     add        byte ptr [eax], al
0140e0b4 0000                     add        byte ptr [eax], al
0140e0b6 0000                     add        byte ptr [eax], al
0140e0b8 0000                     add        byte ptr [eax], al
0140e0ba 0000                     add        byte ptr [eax], al
0140e0bc 0000                     add        byte ptr [eax], al
0140e0be 0000                     add        byte ptr [eax], al
0140e0c0 0000                     add        byte ptr [eax], al
0140e0c2 0000                     add        byte ptr [eax], al
0140e0c4 0000                     add        byte ptr [eax], al
0140e0c6 0000                     add        byte ptr [eax], al
0140e0c8 0000                     add        byte ptr [eax], al
0140e0ca 0000                     add        byte ptr [eax], al
0140e0cc 0000                     add        byte ptr [eax], al
0140e0ce 0000                     add        byte ptr [eax], al
0140e0d0 0000                     add        byte ptr [eax], al
0140e0d2 0000                     add        byte ptr [eax], al
0140e0d4 0000                     add        byte ptr [eax], al
0140e0d6 0000                     add        byte ptr [eax], al
0140e0d8 0000                     add        byte ptr [eax], al
0140e0da 0000                     add        byte ptr [eax], al
0140e0dc 0000                     add        byte ptr [eax], al
0140e0de 0000                     add        byte ptr [eax], al
0140e0e0 0000                     add        byte ptr [eax], al
0140e0e2 0000                     add        byte ptr [eax], al
0140e0e4 0000                     add        byte ptr [eax], al
0140e0e6 0000                     add        byte ptr [eax], al
0140e0e8 0000                     add        byte ptr [eax], al
0140e0ea 0000                     add        byte ptr [eax], al
0140e0ec 0000                     add        byte ptr [eax], al
0140e0ee 0000                     add        byte ptr [eax], al
0140e0f0 0000                     add        byte ptr [eax], al
0140e0f2 0000                     add        byte ptr [eax], al
0140e0f4 0000                     add        byte ptr [eax], al
0140e0f6 0000                     add        byte ptr [eax], al
0140e0f8 0000                     add        byte ptr [eax], al
0140e0fa 0000                     add        byte ptr [eax], al
0140e0fc 0000                     add        byte ptr [eax], al
0140e0fe 0000                     add        byte ptr [eax], al

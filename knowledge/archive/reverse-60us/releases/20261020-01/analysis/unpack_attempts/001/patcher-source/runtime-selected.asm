Runtime snapshot VA 0x4d96c0
004D96C0 42                       inc edx
004D96C1 0d0188450f               or eax, 0xf458801
004D96C6 e8054d5800               call 0xa5e3d0
004D96CB 8b15d4f10401             mov edx, dword ptr [0x104f1d4]
004D96D1 8b3580420d01             mov esi, dword ptr [0x10d4280]
004D96D7 6aff                     push -1
004D96D9 52                       push edx
004D96DA 8bcb                     mov ecx, ebx
004D96DC e8ef740700               call 0x550bd0
004D96E1 89450c                   mov dword ptr [ebp + 0xc], eax
004D96E4 6a02                     push 2
004D96E6 8d450c                   lea eax, [ebp + 0xc]
004D96E9 50                       push eax
004D96EA 8bce                     mov ecx, esi
004D96EC e8df4c5800               call 0xa5e3d0
004D96F1 e9cca0ed00               jmp 0x13b37c2
004D96F6 29956a4c9bd2             sub dword ptr [ebp - 0x2d64b396], edx
004D96FC 0a58ee                   or bl, byte ptr [eax - 0x12]
Runtime snapshot VA 0xa5f4a0
00A5F4A0 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
00A5F4A6 8a813c040000             mov al, byte ptr [ecx + 0x43c]
00A5F4AC 84c0                     test al, al
00A5F4AE 7412                     je 0xa5f4c2
00A5F4B0 6880bbe400               push 0xe4bb80
00A5F4B5 ff15bc2eff00             call dword ptr [0xff2ebc]
00A5F4BB 83c404                   add esp, 4
00A5F4BE 6a00                     push 0
00A5F4C0 eb53                     jmp 0xa5f515
00A5F4C2 8a4108                   mov al, byte ptr [ecx + 8]
00A5F4C5 84c0                     test al, al
00A5F4C7 7521                     jne 0xa5f4ea
00A5F4C9 6838bbe400               push 0xe4bb38
00A5F4CE ff15bc2eff00             call dword ptr [0xff2ebc]
00A5F4D4 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
00A5F4DA 83c404                   add esp, 4
00A5F4DD 6a01                     push 1
00A5F4DF e8ecfcffff               call 0xa5f1d0
00A5F4E4 b854000080               mov eax, 0x80000054
00A5F4E9 c3                       ret 
00A5F4EA 8a811c020000             mov al, byte ptr [ecx + 0x21c]
00A5F4F0 84c0                     test al, al
00A5F4F2 7507                     jne 0xa5f4fb
00A5F4F4 68f0bae400               push 0xe4baf0
00A5F4F9 eb0f                     jmp 0xa5f50a
00A5F4FB 8a813d040000             mov al, byte ptr [ecx + 0x43d]
00A5F501 84c0                     test al, al
00A5F503 7421                     je 0xa5f526
00A5F505 6890bae400               push 0xe4ba90
00A5F50A ff15bc2eff00             call dword ptr [0xff2ebc]
00A5F510 83c404                   add esp, 4
00A5F513 6a01                     push 1
00A5F515 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
00A5F51B e8b0fcffff               call 0xa5f1d0
00A5F520 b800000080               mov eax, 0x80000000
00A5F525 c3                       ret 
00A5F526 6a00                     push 0
00A5F528 e8a3fcffff               call 0xa5f1d0
00A5F52D 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
00A5F533 e818f2ffff               call 0xa5e750
00A5F538 84c0                     test al, al
00A5F53A 7427                     je 0xa5f563
00A5F53C 6830bae400               push 0xe4ba30
00A5F541 ff15bc2eff00             call dword ptr [0xff2ebc]
00A5F547 a180420d01               mov eax, dword ptr [0x10d4280]
00A5F54C c6803c04000001           mov byte ptr [eax + 0x43c], 1
00A5F553 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
00A5F559 83c404                   add esp, 4
00A5F55C c6813d04000001           mov byte ptr [ecx + 0x43d], 1
00A5F563 b801000000               mov eax, 1
00A5F568 c3                       ret 
00A5F569 cc                       int3 
00A5F56A cc                       int3 
00A5F56B cc                       int3 
00A5F56C cc                       int3 
00A5F56D cc                       int3 
00A5F56E cc                       int3 
00A5F56F cc                       int3 
00A5F570 55                       push ebp
00A5F571 8bec                     mov ebp, esp
00A5F573 6aff                     push -1
00A5F575 6862ffc800               push 0xc8ff62
00A5F57A 64a100000000             mov eax, dword ptr fs:[0]
00A5F580 50                       push eax
00A5F581 64892500000000           mov dword ptr fs:[0], esp
00A5F588 83ec20                   sub esp, 0x20
00A5F58B 53                       push ebx
00A5F58C 33db                     xor ebx, ebx
00A5F58E 56                       push esi
00A5F58F 57                       push edi
00A5F590 8bf1                     mov esi, ecx
00A5F592 895ddc                   mov dword ptr [ebp - 0x24], ebx
00A5F595 895de0                   mov dword ptr [ebp - 0x20], ebx
00A5F598 895de4                   mov dword ptr [ebp - 0x1c], ebx
00A5F59B 895de8                   mov dword ptr [ebp - 0x18], ebx
00A5F59E 8dbe40040000             lea edi, [esi + 0x440]
00A5F5A4 57                       push edi
00A5F5A5 895dfc                   mov dword ptr [ebp - 4], ebx
00A5F5A8 ff1530f04001             call dword ptr [0x140f030]
Runtime snapshot VA 0x13b37c2
013B37C2 e8d9bc6aff               call 0xa5f4a0
013B37C7 e98c5f12ff               jmp 0x4d9758
013B37CC a0abb8aed7               mov al, byte ptr [0xd7aeb8ab]
crt-entry-runtime-hook.bin VA 0x2120000
02120000 ff0520001202             inc dword ptr [0x2120020]
02120006 803d2400120200           cmp byte ptr [0x2120024], 0
0212000D 74f1                     je 0x2120000
0212000F 6a6c                     push 0x6c
02120011 6888d5e900               push 0xe9d588
02120016 e96450aefe               jmp 0xc0507f
monster-protected-function-runtime-hook.bin VA 0x3770000
03770000 ff0504047703             inc dword ptr [0x3770404]
03770006 85c9                     test ecx, ecx
03770008 0f84d1000000             je 0x37700df
0377000E 81b9e800000011020000     cmp dword ptr [ecx + 0xe8], 0x211
03770018 7579                     jne 0x3770093
0377001A 8d89ec000000             lea ecx, [ecx + 0xec]
03770020 b860204000               mov eax, 0x402060
03770025 ffd0                     call eax
03770027 a300047703               mov dword ptr [0x3770400], eax
0377002C 3d40000000               cmp eax, 0x40
03770031 0f87a8000000             ja 0x37700df
03770037 d1e0                     shl eax, 1
03770039 0520047703               add eax, 0x3770420
0377003E 8bd0                     mov edx, eax
03770040 8b02                     mov eax, dword ptr [edx]
03770042 85c0                     test eax, eax
03770044 7414                     je 0x377005a
03770046 8b0d04047703             mov ecx, dword ptr [0x3770404]
0377004C 2bc8                     sub ecx, eax
0377004E 81f92c010000             cmp ecx, 0x12c
03770054 0f8285000000             jb 0x37700df
0377005A a104047703               mov eax, dword ptr [0x3770404]
0377005F 8902                     mov dword ptr [edx], eax
03770061 ff0508047703             inc dword ptr [0x3770408]
03770067 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
0377006D 6a2a                     push 0x2a
0377006F b8f0e2a500               mov eax, 0xa5e2f0
03770074 ffd0                     call eax
03770076 8b0d80420d01             mov ecx, dword ptr [0x10d4280]
0377007C 6a02                     push 2
0377007E 6800047703               push 0x3770400
03770083 b8d0e3a500               mov eax, 0xa5e3d0
03770088 ffd0                     call eax
0377008A b8a0f4a500               mov eax, 0xa5f4a0
0377008F ffd0                     call eax
03770091 eb4c                     jmp 0x37700df
03770093 81b9e800000000f00000     cmp dword ptr [ecx + 0xe8], 0xf000
0377009D 7540                     jne 0x37700df
0377009F 8b11                     mov edx, dword ptr [ecx]
037700A1 85d2                     test edx, edx
037700A3 743a                     je 0x37700df
037700A5 81fa00004000             cmp edx, 0x400000
037700AB 7232                     jb 0x37700df
037700AD 81fa00004101             cmp edx, 0x1410000
037700B3 732a                     jae 0x37700df
037700B5 8b9260000000             mov edx, dword ptr [edx + 0x60]
037700BB 85d2                     test edx, edx
037700BD 7420                     je 0x37700df
037700BF 81fa00004000             cmp edx, 0x400000
037700C5 7218                     jb 0x37700df
037700C7 81fa00004101             cmp edx, 0x1410000
037700CD 7310                     jae 0x37700df
037700CF 51                       push ecx
037700D0 6a00                     push 0
037700D2 8b01                     mov eax, dword ptr [ecx]
037700D4 ff5060                   call dword ptr [eax + 0x60]
037700D7 59                       pop ecx
037700D8 c6818401000000           mov byte ptr [ecx + 0x184], 0
037700DF b001                     mov al, 1
037700E1 c3                       ret 
037700E2 90                       nop 
037700E3 90                       nop 

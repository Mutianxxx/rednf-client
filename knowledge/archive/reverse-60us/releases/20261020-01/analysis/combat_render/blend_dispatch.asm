00401020 55                       push       ebp
00401021 8bec                     mov        ebp, esp
00401023 8b4508                   mov        eax, dword ptr [ebp + 8]
00401026 83f805                   cmp        eax, 5
00401029 7763                     ja         0x40108e
0040102b ff248590104000           jmp        dword ptr [eax*4 + 0x401090]
00401032 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401038 6a00                     push       0
0040103a e871747000               call       0xb084b0
0040103f 5d                       pop        ebp
00401040 c3                       ret        
00401041 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401047 6a01                     push       1
00401049 e862747000               call       0xb084b0
0040104e 5d                       pop        ebp
0040104f c3                       ret        
00401050 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401056 6a02                     push       2
00401058 e853747000               call       0xb084b0
0040105d 5d                       pop        ebp
0040105e c3                       ret        
0040105f 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401065 6a03                     push       3
00401067 e844747000               call       0xb084b0
0040106c 5d                       pop        ebp
0040106d c3                       ret        
0040106e 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401074 6a04                     push       4
00401076 e835747000               call       0xb084b0
0040107b 5d                       pop        ebp
0040107c c3                       ret        
0040107d 8b450c                   mov        eax, dword ptr [ebp + 0xc]
00401080 8b0de0b80d01             mov        ecx, dword ptr [0x10db8e0]
00401086 50                       push       eax
00401087 6a01                     push       1
00401089 e842747000               call       0xb084d0
0040108e 5d                       pop        ebp
0040108f c3                       ret        
00401090 3210                     xor        dl, byte ptr [eax]
00401092 40                       inc        eax
00401093 004110                   add        byte ptr [ecx + 0x10], al
00401096 40                       inc        eax
00401097 005010                   add        byte ptr [eax + 0x10], dl
0040109a 40                       inc        eax
0040109b 005f10                   add        byte ptr [edi + 0x10], bl
0040109e 40                       inc        eax
0040109f 006e10                   add        byte ptr [esi + 0x10], ch
004010a2 40                       inc        eax
004010a3 007d10                   add        byte ptr [ebp + 0x10], bh
004010a6 40                       inc        eax
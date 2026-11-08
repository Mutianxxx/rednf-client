0049ea3b 8d4de4                   lea       ecx, [ebp - 0x1c]
0049ea3e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049ea45 e8c635f6ff               call      0x402010
0049ea4a 5f                       pop       edi
0049ea4b 5e                       pop       esi
0049ea4c 8b03                     mov       eax, dword ptr [ebx]
0049ea4e 6a00                     push      0
0049ea50 8bcb                     mov       ecx, ebx
0049ea52 ff90d0020000             call      dword ptr [eax + 0x2d0]
0049ea58 8b13                     mov       edx, dword ptr [ebx]
0049ea5a 6a00                     push      0
0049ea5c 8bcb                     mov       ecx, ebx
0049ea5e ff92d8020000             call      dword ptr [edx + 0x2d8]
0049ea64 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049ea67 5b                       pop       ebx
0049ea68 64890d00000000           mov       dword ptr fs:[0], ecx
0049ea6f 8be5                     mov       esp, ebp
0049ea71 5d                       pop       ebp
0049ea72 c20400                   ret       4
0049ea75 cc                       int3      
0049ea76 cc                       int3      
0049ea77 cc                       int3      
0049ea78 cc                       int3      
0049ea79 cc                       int3      
0049ea7a cc                       int3      
0049ea7b cc                       int3      
0049ea7c cc                       int3      
0049ea7d cc                       int3      
0049ea7e cc                       int3      
0049ea7f cc                       int3      
0049ea80 e9dbf5ffff               jmp       0x49e060
0049ea85 cc                       int3      
0049ea86 cc                       int3      
0049ea87 cc                       int3      
0049ea88 cc                       int3      
0049ea89 cc                       int3      
0049ea8a cc                       int3      
0049ea8b cc                       int3      
0049ea8c cc                       int3      
0049ea8d cc                       int3      
0049ea8e cc                       int3      
0049ea8f cc                       int3      

005f33c0 55                       push      ebp
005f33c1 8bec                     mov       ebp, esp
005f33c3 6aff                     push      -1
005f33c5 68f874c600               push      0xc674f8
005f33ca 64a100000000             mov       eax, dword ptr fs:[0]
005f33d0 50                       push      eax
005f33d1 64892500000000           mov       dword ptr fs:[0], esp
005f33d8 83ec10                   sub       esp, 0x10
005f33db 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f33de 8b5508                   mov       edx, dword ptr [ebp + 8]
005f33e1 53                       push      ebx
005f33e2 56                       push      esi
005f33e3 8bf1                     mov       esi, ecx
005f33e5 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005f33e8 50                       push      eax
005f33e9 51                       push      ecx
005f33ea 52                       push      edx
005f33eb 8bce                     mov       ecx, esi
005f33ed e81ebfeaff               call      0x49f310
005f33f2 894510                   mov       dword ptr [ebp + 0x10], eax
005f33f5 8b06                     mov       eax, dword ptr [esi]
005f33f7 8bce                     mov       ecx, esi
005f33f9 ff9074030000             call      dword ptr [eax + 0x374]
005f33ff 8b8e74080000             mov       ecx, dword ptr [esi + 0x874]
005f3405 3b8e78080000             cmp       ecx, dword ptr [esi + 0x878]
005f340b 7d0c                     jge       0x5f3419
005f340d 8b16                     mov       edx, dword ptr [esi]
005f340f 8bce                     mov       ecx, esi
005f3411 ff9278030000             call      dword ptr [edx + 0x378]
005f3417 eb13                     jmp       0x5f342c
005f3419 8b06                     mov       eax, dword ptr [esi]
005f341b 33c9                     xor       ecx, ecx
005f341d 8a8e70080000             mov       cl, byte ptr [esi + 0x870]
005f3423 51                       push      ecx
005f3424 8bce                     mov       ecx, esi
005f3426 ff9064010000             call      dword ptr [eax + 0x164]
005f342c 8b967c080000             mov       edx, dword ptr [esi + 0x87c]
005f3432 33db                     xor       ebx, ebx
005f3434 3bd3                     cmp       edx, ebx
005f3436 0f8497000000             je        0x5f34d3
005f343c 8b8e34020000             mov       ecx, dword ptr [esi + 0x234]
005f3442 3bcb                     cmp       ecx, ebx
005f3444 7415                     je        0x5f345b
005f3446 8b8638020000             mov       eax, dword ptr [esi + 0x238]
005f344c 2bc1                     sub       eax, ecx
005f344e c1f802                   sar       eax, 2
005f3451 3bc3                     cmp       eax, ebx
005f3453 7606                     jbe       0x5f345b
005f3455 8bc1                     mov       eax, ecx
005f3457 8b00                     mov       eax, dword ptr [eax]
005f3459 eb02                     jmp       0x5f345d
005f345b 33c0                     xor       eax, eax
005f345d 57                       push      edi
005f345e 8b3a                     mov       edi, dword ptr [edx]
005f3460 8b16                     mov       edx, dword ptr [esi]
005f3462 50                       push      eax
005f3463 8bce                     mov       ecx, esi
005f3465 ff9298000000             call      dword ptr [edx + 0x98]
005f346b 50                       push      eax
005f346c 8b06                     mov       eax, dword ptr [esi]
005f346e 8bce                     mov       ecx, esi
005f3470 ff9094000000             call      dword ptr [eax + 0x94]
005f3476 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f347c 50                       push      eax
005f347d ff5728                   call      dword ptr [edi + 0x28]
005f3480 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f3486 8b11                     mov       edx, dword ptr [ecx]
005f3488 53                       push      ebx
005f3489 ff520c                   call      dword ptr [edx + 0xc]
005f348c 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f3492 8b01                     mov       eax, dword ptr [ecx]
005f3494 8d55e4                   lea       edx, [ebp - 0x1c]
005f3497 52                       push      edx
005f3498 ff505c                   call      dword ptr [eax + 0x5c]
005f349b 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f34a1 53                       push      ebx
005f34a2 8d45e4                   lea       eax, [ebp - 0x1c]
005f34a5 50                       push      eax
005f34a6 53                       push      ebx
005f34a7 6a02                     push      2
005f34a9 56                       push      esi
005f34aa 895dfc                   mov       dword ptr [ebp - 4], ebx
005f34ad e8aeabf1ff               call      0x50e060
005f34b2 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
005f34b5 3bc3                     cmp       eax, ebx
005f34b7 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f34be 5f                       pop       edi
005f34bf 7409                     je        0x5f34ca
005f34c1 50                       push      eax
005f34c2 e816cb6000               call      0xbfffdd
005f34c7 83c404                   add       esp, 4
005f34ca 895de8                   mov       dword ptr [ebp - 0x18], ebx
005f34cd 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f34d0 895df0                   mov       dword ptr [ebp - 0x10], ebx
005f34d3 8bce                     mov       ecx, esi
005f34d5 e896feffff               call      0x5f3370
005f34da 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f34dd 8b4510                   mov       eax, dword ptr [ebp + 0x10]
005f34e0 889e80080000             mov       byte ptr [esi + 0x880], bl
005f34e6 5e                       pop       esi
005f34e7 5b                       pop       ebx
005f34e8 64890d00000000           mov       dword ptr fs:[0], ecx
005f34ef 8be5                     mov       esp, ebp
005f34f1 5d                       pop       ebp
005f34f2 c20c00                   ret       0xc
005f34f5 cc                       int3      
005f34f6 cc                       int3      
005f34f7 cc                       int3      
005f34f8 cc                       int3      
005f34f9 cc                       int3      
005f34fa cc                       int3      
005f34fb cc                       int3      
005f34fc cc                       int3      
005f34fd cc                       int3      
005f34fe cc                       int3      
005f34ff cc                       int3      

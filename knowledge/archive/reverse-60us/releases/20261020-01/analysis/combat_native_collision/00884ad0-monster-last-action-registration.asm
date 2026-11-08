00884ad0 8d45f0                   lea       eax, [ebp - 0x10]
00884ad3 50                       push      eax
00884ad4 8bcf                     mov       ecx, edi
00884ad6 e805f1b7ff               call      0x403be0
00884adb 8d4df0                   lea       ecx, [ebp - 0x10]
00884ade 51                       push      ecx
00884adf e8fcb9faff               call      0x8304e0
00884ae4 83c404                   add       esp, 4
00884ae7 84c0                     test      al, al
00884ae9 75e5                     jne       0x884ad0
00884aeb e92c0e0000               jmp       0x88591c
00884af0 8d55c4                   lea       edx, [ebp - 0x3c]
00884af3 680035e200               push      0xe23500
00884af8 52                       push      edx
00884af9 e8d2fcb7ff               call      0x4047d0
00884afe 83c408                   add       esp, 8
00884b01 84c0                     test      al, al
00884b03 7411                     je        0x884b16
00884b05 8d4648                   lea       eax, [esi + 0x48]
00884b08 50                       push      eax
00884b09 e8d2b9faff               call      0x8304e0
00884b0e 83c404                   add       esp, 4
00884b11 e9060e0000               jmp       0x88591c
00884b16 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884b19 68e434e200               push      0xe234e4
00884b1e 51                       push      ecx
00884b1f e8acfcb7ff               call      0x4047d0
00884b24 83c408                   add       esp, 8
00884b27 84c0                     test      al, al
00884b29 7411                     je        0x884b3c
00884b2b 8d565c                   lea       edx, [esi + 0x5c]
00884b2e 52                       push      edx
00884b2f e8acb9faff               call      0x8304e0
00884b34 83c404                   add       esp, 4
00884b37 e9e00d0000               jmp       0x88591c
00884b3c 8d45c4                   lea       eax, [ebp - 0x3c]
00884b3f 68c834e200               push      0xe234c8
00884b44 50                       push      eax
00884b45 e886fcb7ff               call      0x4047d0
00884b4a 83c408                   add       esp, 8
00884b4d 84c0                     test      al, al
00884b4f 743f                     je        0x884b90
00884b51 8d7e4c                   lea       edi, [esi + 0x4c]
00884b54 8bcf                     mov       ecx, edi
00884b56 e8d5eab7ff               call      0x403630
00884b5b 8d4df0                   lea       ecx, [ebp - 0x10]
00884b5e 51                       push      ecx
00884b5f e87cb9faff               call      0x8304e0
00884b64 83c404                   add       esp, 4
00884b67 84c0                     test      al, al
00884b69 0f84ad0d0000             je        0x88591c
00884b6f 90                       nop       
00884b70 8d55f0                   lea       edx, [ebp - 0x10]
00884b73 52                       push      edx
00884b74 8bcf                     mov       ecx, edi
00884b76 e865f0b7ff               call      0x403be0
00884b7b 8d45f0                   lea       eax, [ebp - 0x10]
00884b7e 50                       push      eax
00884b7f e8                       .byte     0xe8

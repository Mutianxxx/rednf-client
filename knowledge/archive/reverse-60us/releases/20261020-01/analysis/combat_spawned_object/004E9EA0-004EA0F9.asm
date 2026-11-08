004e9ea0  55                       push       ebp
004e9ea1  8bec                     mov        ebp, esp
004e9ea3  56                       push       esi
004e9ea4  8b7508                   mov        esi, dword ptr [ebp + 8]
004e9ea7  85f6                     test       esi, esi
004e9ea9  57                       push       edi
004e9eaa  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
004e9ead  746c                     je         0x4e9f1b
004e9eaf  8b06                     mov        eax, dword ptr [esi]
004e9eb1  8bce                     mov        ecx, esi
004e9eb3  ff9068010000             call       dword ptr [eax + 0x168]
004e9eb9  84c0                     test       al, al
004e9ebb  0f85a0000000             jne        0x4e9f61
004e9ec1  8b16                     mov        edx, dword ptr [esi]
004e9ec3  8bce                     mov        ecx, esi
004e9ec5  ff5264                   call       dword ptr [edx + 0x64]
004e9ec8  84c0                     test       al, al
004e9eca  0f8491000000             je         0x4e9f61
004e9ed0  8b06                     mov        eax, dword ptr [esi]
004e9ed2  8bce                     mov        ecx, esi
004e9ed4  ff5034                   call       dword ptr [eax + 0x34]
004e9ed7  84c0                     test       al, al
004e9ed9  7440                     je         0x4e9f1b
004e9edb  6a00                     push       0
004e9edd  680829f400               push       0xf42908
004e9ee2  681009f400               push       0xf40910
004e9ee7  6a00                     push       0
004e9ee9  56                       push       esi
004e9eea  e81c6e7100               call       0xc00d0b
004e9eef  83c414                   add        esp, 0x14
004e9ef2  85c0                     test       eax, eax
004e9ef4  7425                     je         0x4e9f1b
004e9ef6  8b8874280000             mov        ecx, dword ptr [eax + 0x2874]
004e9efc  8b81100b0000             mov        eax, dword ptr [ecx + 0xb10]
004e9f02  8b89140b0000             mov        ecx, dword ptr [ecx + 0xb14]
004e9f08  3bc1                     cmp        eax, ecx
004e9f0a  740f                     je         0x4e9f1b
004e9f0c  8d642400                 lea        esp, [esp]
004e9f10  3b38                     cmp        edi, dword ptr [eax]
004e9f12  744d                     je         0x4e9f61
004e9f14  83c004                   add        eax, 4
004e9f17  3bc1                     cmp        eax, ecx
004e9f19  75f5                     jne        0x4e9f10
004e9f1b  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9f21  8b11                     mov        edx, dword ptr [ecx]
004e9f23  53                       push       ebx
004e9f24  6a02                     push       2
004e9f26  6a15                     push       0x15
004e9f28  ff5208                   call       dword ptr [edx + 8]
004e9f2b  85f6                     test       esi, esi
004e9f2d  743b                     je         0x4e9f6a
004e9f2f  a164310001               mov        eax, dword ptr [0x1003164]
004e9f34  8b16                     mov        edx, dword ptr [esi]
004e9f36  8b18                     mov        ebx, dword ptr [eax]
004e9f38  8bce                     mov        ecx, esi
004e9f3a  ff523c                   call       dword ptr [edx + 0x3c]
004e9f3d  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9f43  50                       push       eax
004e9f44  ff5324                   call       dword ptr [ebx + 0x24]
004e9f47  a164310001               mov        eax, dword ptr [0x1003164]
004e9f4c  8b16                     mov        edx, dword ptr [esi]
004e9f4e  8b18                     mov        ebx, dword ptr [eax]
004e9f50  8bce                     mov        ecx, esi
004e9f52  ff5240                   call       dword ptr [edx + 0x40]
004e9f55  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9f5b  50                       push       eax
004e9f5c  ff5324                   call       dword ptr [ebx + 0x24]
004e9f5f  eb26                     jmp        0x4e9f87
004e9f61  5f                       pop        edi
004e9f62  b8ffff0000               mov        eax, 0xffff
004e9f67  5e                       pop        esi
004e9f68  5d                       pop        ebp
004e9f69  c3                       ret        
004e9f6a  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9f70  8b01                     mov        eax, dword ptr [ecx]
004e9f72  68ffff0000               push       0xffff
004e9f77  ff5024                   call       dword ptr [eax + 0x24]
004e9f7a  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9f80  8b11                     mov        edx, dword ptr [ecx]
004e9f82  6a00                     push       0
004e9f84  ff5224                   call       dword ptr [edx + 0x24]
004e9f87  8b7524                   mov        esi, dword ptr [ebp + 0x24]
004e9f8a  85f6                     test       esi, esi
004e9f8c  7432                     je         0x4e9fc0
004e9f8e  a164310001               mov        eax, dword ptr [0x1003164]
004e9f93  8b16                     mov        edx, dword ptr [esi]
004e9f95  8b18                     mov        ebx, dword ptr [eax]
004e9f97  8bce                     mov        ecx, esi
004e9f99  ff523c                   call       dword ptr [edx + 0x3c]
004e9f9c  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9fa2  50                       push       eax
004e9fa3  ff5324                   call       dword ptr [ebx + 0x24]
004e9fa6  a164310001               mov        eax, dword ptr [0x1003164]
004e9fab  8b16                     mov        edx, dword ptr [esi]
004e9fad  8b18                     mov        ebx, dword ptr [eax]
004e9faf  8bce                     mov        ecx, esi
004e9fb1  ff5240                   call       dword ptr [edx + 0x40]
004e9fb4  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9fba  50                       push       eax
004e9fbb  ff5324                   call       dword ptr [ebx + 0x24]
004e9fbe  eb1d                     jmp        0x4e9fdd
004e9fc0  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9fc6  8b01                     mov        eax, dword ptr [ecx]
004e9fc8  68ffff0000               push       0xffff
004e9fcd  ff5024                   call       dword ptr [eax + 0x24]
004e9fd0  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9fd6  8b11                     mov        edx, dword ptr [ecx]
004e9fd8  6a00                     push       0
004e9fda  ff5224                   call       dword ptr [edx + 0x24]
004e9fdd  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9fe3  8b01                     mov        eax, dword ptr [ecx]
004e9fe5  6a01                     push       1
004e9fe7  ff5024                   call       dword ptr [eax + 0x24]
004e9fea  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9ff0  8b11                     mov        edx, dword ptr [ecx]
004e9ff2  57                       push       edi
004e9ff3  ff5224                   call       dword ptr [edx + 0x24]
004e9ff6  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004e9ffc  8b5510                   mov        edx, dword ptr [ebp + 0x10]
004e9fff  8b01                     mov        eax, dword ptr [ecx]
004ea001  52                       push       edx
004ea002  ff502c                   call       dword ptr [eax + 0x2c]
004ea005  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
004ea00b  a164310001               mov        eax, dword ptr [0x1003164]
004ea010  8b11                     mov        edx, dword ptr [ecx]
004ea012  8b30                     mov        esi, dword ptr [eax]
004ea014  ff92e0060000             call       dword ptr [edx + 0x6e0]
004ea01a  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea020  50                       push       eax
004ea021  ff5624                   call       dword ptr [esi + 0x24]
004ea024  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea02a  8b01                     mov        eax, dword ptr [ecx]
004ea02c  ff9088000000             call       dword ptr [eax + 0x88]
004ea032  8b88b0000000             mov        ecx, dword ptr [eax + 0xb0]
004ea038  e8f3330200               call       0x50d430
004ea03d  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea043  8b11                     mov        edx, dword ptr [ecx]
004ea045  8bf0                     mov        esi, eax
004ea047  56                       push       esi
004ea048  ff5224                   call       dword ptr [edx + 0x24]
004ea04b  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea051  8b01                     mov        eax, dword ptr [ecx]
004ea053  6a00                     push       0
004ea055  ff5020                   call       dword ptr [eax + 0x20]
004ea058  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea05e  8b4520                   mov        eax, dword ptr [ebp + 0x20]
004ea061  8b11                     mov        edx, dword ptr [ecx]
004ea063  50                       push       eax
004ea064  ff5220                   call       dword ptr [edx + 0x20]
004ea067  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea06d  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004ea070  8b11                     mov        edx, dword ptr [ecx]
004ea072  50                       push       eax
004ea073  ff5224                   call       dword ptr [edx + 0x24]
004ea076  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea07c  8b4518                   mov        eax, dword ptr [ebp + 0x18]
004ea07f  8b11                     mov        edx, dword ptr [ecx]
004ea081  50                       push       eax
004ea082  ff5224                   call       dword ptr [edx + 0x24]
004ea085  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea08b  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
004ea08e  8b11                     mov        edx, dword ptr [ecx]
004ea090  50                       push       eax
004ea091  ff5224                   call       dword ptr [edx + 0x24]
004ea094  8b4528                   mov        eax, dword ptr [ebp + 0x28]
004ea097  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea09d  8b11                     mov        edx, dword ptr [ecx]
004ea09f  50                       push       eax
004ea0a0  8b452c                   mov        eax, dword ptr [ebp + 0x2c]
004ea0a3  50                       push       eax
004ea0a4  ff5238                   call       dword ptr [edx + 0x38]
004ea0a7  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea0ad  8b4530                   mov        eax, dword ptr [ebp + 0x30]
004ea0b0  8b11                     mov        edx, dword ptr [ecx]
004ea0b2  50                       push       eax
004ea0b3  ff5224                   call       dword ptr [edx + 0x24]
004ea0b6  8b7d34                   mov        edi, dword ptr [ebp + 0x34]
004ea0b9  85ff                     test       edi, edi
004ea0bb  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea0c1  8b11                     mov        edx, dword ptr [ecx]
004ea0c3  5b                       pop        ebx
004ea0c4  7415                     je         0x4ea0db
004ea0c6  6a01                     push       1
004ea0c8  ff5220                   call       dword ptr [edx + 0x20]
004ea0cb  8b0d64310001             mov        ecx, dword ptr [0x1003164]
004ea0d1  8b01                     mov        eax, dword ptr [ecx]
004ea0d3  6a04                     push       4
004ea0d5  57                       push       edi
004ea0d6  ff5034                   call       dword ptr [eax + 0x34]
004ea0d9  eb05                     jmp        0x4ea0e0
004ea0db  6a00                     push       0
004ea0dd  ff5220                   call       dword ptr [edx + 0x20]
004ea0e0  8b0d90070c01             mov        ecx, dword ptr [0x10c0790]
004ea0e6  8b01                     mov        eax, dword ptr [ecx]
004ea0e8  6a03                     push       3
004ea0ea  6a00                     push       0
004ea0ec  6aff                     push       -1
004ea0ee  6a01                     push       1
004ea0f0  ff5044                   call       dword ptr [eax + 0x44]
004ea0f3  5f                       pop        edi
004ea0f4  8bc6                     mov        eax, esi
004ea0f6  5e                       pop        esi
004ea0f7  5d                       pop        ebp
004ea0f8  c3                       ret        
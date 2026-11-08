0044ad80  0d1ca90d01               or         eax, 0x10da91c
0044ad85  8b7110                   mov        esi, dword ptr [ecx + 0x10]
0044ad88  6a00                     push       0
0044ad8a  687453cb00               push       0xcb5374
0044ad8f  6898040000               push       0x498
0044ad94  e8a7646000               call       0xa51240
0044ad99  83c404                   add        esp, 4
0044ad9c  50                       push       eax
0044ad9d  56                       push       esi
0044ad9e  ffd7                     call       edi
0044ada0  6a00                     push       0
0044ada2  ff1580f04001             call       dword ptr [0x140f080]
0044ada8  8b0d48280001             mov        ecx, dword ptr [0x1002848]
0044adae  e8adf9feff               call       0x43a760
0044adb3  6874b0cc00               push       0xccb074
0044adb8  6858b0cc00               push       0xccb058
0044adbd  6834b0cc00               push       0xccb034
0044adc2  681cb0cc00               push       0xccb01c
0044adc7  e8d4774300               call       0x8825a0
0044adcc  68fcafcc00               push       0xccaffc
0044add1  68e8afcc00               push       0xccafe8
0044add6  e865464400               call       0x88f440
0044addb  68bcafcc00               push       0xccafbc
0044ade0  689cafcc00               push       0xccaf9c
0044ade5  e8667c4300               call       0x882a50
0044adea  6884afcc00               push       0xccaf84
0044adef  6878afcc00               push       0xccaf78
0044adf4  e8d77c4300               call       0x882ad0
0044adf9  6858afcc00               push       0xccaf58
0044adfe  6834afcc00               push       0xccaf34
0044ae03  681cafcc00               push       0xccaf1c
0044ae08  e8b3254100               call       0x85d3c0
0044ae0d  6858afcc00               push       0xccaf58
0044ae12  68f8aecc00               push       0xccaef8
0044ae17  68e0aecc00               push       0xccaee0
0044ae1c  e8df284100               call       0x85d700
0044ae21  83c440                   add        esp, 0x40
0044ae24  e827944200               call       0x874250
0044ae29  68c8aecc00               push       0xccaec8
0044ae2e  68bcaecc00               push       0xccaebc
0044ae33  e828944200               call       0x874260
0044ae38  689caecc00               push       0xccae9c
0044ae3d  6888aecc00               push       0xccae88
0044ae42  e8995d3f00               call       0x840be0
0044ae47  e8c4bd3e00               call       0x836c10
0044ae4c  68                       .byte      0x68
0044ae4d  64ae                     scasb      al, byte ptr es:[edi]
0044ae4f  cc                       int3       
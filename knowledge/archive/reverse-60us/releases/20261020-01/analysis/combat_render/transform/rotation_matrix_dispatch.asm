00c3551a 6a01                     push       1
00c3551c e86d230000               call       0xc3788e
00c35521 d9442408                 fld        dword ptr [esp + 8]
00c35525 51                       push       ecx
00c35526 d91c24                   fstp       dword ptr [esp]
00c35529 ff742408                 push       dword ptr [esp + 8]
00c3552d ff1500b1ff00             call       dword ptr [0xffb100]
00c35533 c20800                   ret        8
00c35536 ff2500b1ff00             jmp        dword ptr [0xffb100]

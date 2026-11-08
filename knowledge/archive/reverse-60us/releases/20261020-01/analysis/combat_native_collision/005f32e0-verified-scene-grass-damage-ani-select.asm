005f32e0 8b8120010000             mov       eax, dword ptr [ecx + 0x120]
005f32e6 8b00                     mov       eax, dword ptr [eax]
005f32e8 8b11                     mov       edx, dword ptr [ecx]
005f32ea 50                       push      eax
005f32eb ff92f0000000             call      dword ptr [edx + 0xf0]
005f32f1 c3                       ret       

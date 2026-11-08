005f3130 33c0                     xor       eax, eax
005f3132 c781e400000021040000     mov       dword ptr [ecx + 0xe4], 0x421
005f313c 888170080000             mov       byte ptr [ecx + 0x870], al
005f3142 898174080000             mov       dword ptr [ecx + 0x874], eax
005f3148 898178080000             mov       dword ptr [ecx + 0x878], eax
005f314e 89817c080000             mov       dword ptr [ecx + 0x87c], eax
005f3154 888180080000             mov       byte ptr [ecx + 0x880], al
005f315a 898184080000             mov       dword ptr [ecx + 0x884], eax
005f3160 c7818808000004000000     mov       dword ptr [ecx + 0x888], 4
005f316a 88818c080000             mov       byte ptr [ecx + 0x88c], al
005f3170 c3                       ret       

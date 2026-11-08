00c01544  55                       push       ebp
00c01545  8bec                     mov        ebp, esp
00c01547  83ec20                   sub        esp, 0x20
00c0154a  83e4f0                   and        esp, 0xfffffff0
00c0154d  d9c0                     fld        st(0)
00c0154f  d9542418                 fst        dword ptr [esp + 0x18]
00c01553  df7c2410                 fistp      qword ptr [esp + 0x10]
00c01557  df6c2410                 fild       qword ptr [esp + 0x10]
00c0155b  8b542418                 mov        edx, dword ptr [esp + 0x18]
00c0155f  8b442410                 mov        eax, dword ptr [esp + 0x10]
00c01563  85c0                     test       eax, eax
00c01565  743c                     je         0xc015a3
00c01567  dee9                     fsubp      st(1)
00c01569  85d2                     test       edx, edx
00c0156b  791e                     jns        0xc0158b
00c0156d  d91c24                   fstp       dword ptr [esp]
00c01570  8b0c24                   mov        ecx, dword ptr [esp]
00c01573  81f100000080             xor        ecx, 0x80000000
00c01579  81c1ffffff7f             add        ecx, 0x7fffffff
00c0157f  83d000                   adc        eax, 0
00c01582  8b542414                 mov        edx, dword ptr [esp + 0x14]
00c01586  83d200                   adc        edx, 0
00c01589  eb2c                     jmp        0xc015b7
00c0158b  d91c24                   fstp       dword ptr [esp]
00c0158e  8b0c24                   mov        ecx, dword ptr [esp]
00c01591  81c1ffffff7f             add        ecx, 0x7fffffff
00c01597  83d800                   sbb        eax, 0
00c0159a  8b542414                 mov        edx, dword ptr [esp + 0x14]
00c0159e  83da00                   sbb        edx, 0
00c015a1  eb14                     jmp        0xc015b7
00c015a3  8b542414                 mov        edx, dword ptr [esp + 0x14]
00c015a7  f7c2ffffff7f             test       edx, 0x7fffffff
00c015ad  75b8                     jne        0xc01567
00c015af  d95c2418                 fstp       dword ptr [esp + 0x18]
00c015b3  d95c2418                 fstp       dword ptr [esp + 0x18]
00c015b7  c9                       leave      
00c015b8  c3                       ret        
00c015b9  6a                       .byte      0x6a
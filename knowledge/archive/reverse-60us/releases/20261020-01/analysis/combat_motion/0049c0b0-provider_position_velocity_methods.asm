0049c0b0  55                       push       ebp
0049c0b1  8bec                     mov        ebp, esp
0049c0b3  8b4508                   mov        eax, dword ptr [ebp + 8]
0049c0b6  d9448104                 fld        dword ptr [ecx + eax*4 + 4]
0049c0ba  5d                       pop        ebp
0049c0bb  c20400                   ret        4
0049c0be  cc                       int3       
0049c0bf  cc                       int3       
0049c0c0  55                       push       ebp
0049c0c1  8bec                     mov        ebp, esp
0049c0c3  d9450c                   fld        dword ptr [ebp + 0xc]
0049c0c6  8b4508                   mov        eax, dword ptr [ebp + 8]
0049c0c9  d95c8104                 fstp       dword ptr [ecx + eax*4 + 4]
0049c0cd  5d                       pop        ebp
0049c0ce  c20800                   ret        8
0049c0d1  cc                       int3       
0049c0d2  cc                       int3       
0049c0d3  cc                       int3       
0049c0d4  cc                       int3       
0049c0d5  cc                       int3       
0049c0d6  cc                       int3       
0049c0d7  cc                       int3       
0049c0d8  cc                       int3       
0049c0d9  cc                       int3       
0049c0da  cc                       int3       
0049c0db  cc                       int3       
0049c0dc  cc                       int3       
0049c0dd  cc                       int3       
0049c0de  cc                       int3       
0049c0df  cc                       int3       
0049c0e0  55                       push       ebp
0049c0e1  8bec                     mov        ebp, esp
0049c0e3  8b4508                   mov        eax, dword ptr [ebp + 8]
0049c0e6  d9448110                 fld        dword ptr [ecx + eax*4 + 0x10]
0049c0ea  5d                       pop        ebp
0049c0eb  c20400                   ret        4
0049c0ee  cc                       int3       
0049c0ef  cc                       int3       
0049c0f0  55                       push       ebp
0049c0f1  8bec                     mov        ebp, esp
0049c0f3  d9450c                   fld        dword ptr [ebp + 0xc]
0049c0f6  8b4508                   mov        eax, dword ptr [ebp + 8]
0049c0f9  d95c8110                 fstp       dword ptr [ecx + eax*4 + 0x10]
0049c0fd  5d                       pop        ebp
0049c0fe  c2                       .byte      0xc2
0049c0ff  08                       .byte      0x08

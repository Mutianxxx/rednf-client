004fa1d0 004bd1                   add        byte ptr [ebx - 0x2f], cl
004fa1d3 b544                     mov        ch, 0x44
004fa1d5 849306712453             test       byte ptr [ebx + 0x53247106], dl
004fa1db 80b6f06617be72           xor        byte ptr [esi - 0x41e89910], 0x72
004fa1e2 ce                       into       
004fa1e3 cae7e3                   retf       0xe3e7
004fa1e6 3807                     cmp        byte ptr [edi], al
004fa1e8 8872b2                   mov        byte ptr [edx - 0x4e], dh
004fa1eb 5e                       pop        esi
004fa1ec 78ba                     js         0x4fa1a8
004fa1ee 51                       push       ecx
004fa1ef 879fc526098e             xchg       dword ptr [edi - 0x71f6d93b], ebx
004fa1f5 7f38                     jg         0x4fa22f
004fa1f7 b2d0                     mov        dl, 0xd0
004fa1f9 3c08                     cmp        al, 8
004fa1fb 53                       push       ebx
004fa1fc ed                       in         eax, dx
004fa1fd af                       scasd      eax, dword ptr es:[edi]
004fa1fe c02a1e                   shr        byte ptr [edx], 0x1e
004fa201 635e9b                   arpl       word ptr [esi - 0x65], bx
004fa204 6989d32feb7439051e73     imul       ecx, dword ptr [ecx + 0x74eb2fd3], 0x731e0539
004fa20e b5f7                     mov        ch, 0xf7
004fa210 4f                       dec        edi
004fa211 659d                     popfd      
004fa213 6e                       outsb      dx, byte ptr [esi]
004fa214 c7c3d443a4b1             mov        ebx, 0xb1a443d4
004fa21a fc                       cld        
004fa21b e1e4                     loope      0x4fa201
004fa21d 43                       inc        ebx
004fa21e a827                     test       al, 0x27
004fa220 1a57d3                   sbb        dl, byte ptr [edi - 0x2d]
004fa223 d321                     shl        dword ptr [ecx], cl
004fa225 c9                       leave      
004fa226 b53f                     mov        ch, 0x3f
004fa228 632553b6e984             arpl       word ptr [0x84e9b653], sp
004fa22e b715                     mov        bh, 0x15

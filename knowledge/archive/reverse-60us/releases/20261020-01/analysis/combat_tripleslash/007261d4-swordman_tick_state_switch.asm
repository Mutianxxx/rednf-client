007261d4  8d8e5c150000             lea        ecx, [esi + 0x155c]
007261da  e881becdff               call       0x402060
007261df  83f834                   cmp        eax, 0x34
007261e2  0f8749490000             ja         0x72ab31
007261e8  0fb68804037300           movzx      ecx, byte ptr [eax + 0x730304]
007261ef  ff248d80027300           jmp        dword ptr [ecx*4 + 0x730280]

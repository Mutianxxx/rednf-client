013baa5f 687e0e1008               push       0x8100e7e
013baa64 e9603df3ff               jmp        0x12ee7c9
013baa69 084201                   or         byte ptr [edx + 1], al
013baa6c 6453                     push       ebx
013baa6e ae                       scasb      al, byte ptr es:[edi]
013baa6f 68b84b4a10               push       0x104a4bb8
013baa74 0803                     or         byte ptr [ebx], al

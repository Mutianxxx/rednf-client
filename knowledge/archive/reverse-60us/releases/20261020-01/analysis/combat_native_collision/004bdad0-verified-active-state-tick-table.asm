004bdad0 c7                       .byte     0xc7
004bdad1 cc                       int3      
004bdad2 4b                       dec       ebx
004bdad3 0035d04b0000             add       byte ptr [0x4bd0], dh
004bdad9 da4b00                   fimul     dword ptr [ebx]
004bdadc 6ad0                     push      -0x30
004bdade 4b                       dec       ebx
004bdadf 00b7d04b0049             add       byte ptr [edi + 0x49004bd0], dh
004bdae5 d6                       salc      
004bdae6 4b                       dec       ebx
004bdae7 0096d64b008b             add       byte ptr [esi - 0x74ffb42a], dl
004bdaed d9                       .byte     0xd9
004bdaee 4b                       dec       ebx
004bdaef 00d8                     add       al, bl
004bdaf1 d9                       .byte     0xd9
004bdaf2 4b                       dec       ebx
004bdaf3 00                       .byte     0x00

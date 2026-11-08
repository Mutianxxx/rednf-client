005702e0 c20400                   ret       4
005702e3 cc                       int3      
005702e4 cc                       int3      
005702e5 cc                       int3      
005702e6 cc                       int3      
005702e7 cc                       int3      
005702e8 cc                       int3      
005702e9 cc                       int3      
005702ea cc                       int3      
005702eb cc                       int3      
005702ec cc                       int3      
005702ed cc                       int3      
005702ee cc                       int3      
005702ef cc                       int3      
005702f0 c3                       ret       
005702f1 cc                       int3      
005702f2 cc                       int3      
005702f3 cc                       int3      
005702f4 cc                       int3      
005702f5 cc                       int3      
005702f6 cc                       int3      
005702f7 cc                       int3      
005702f8 cc                       int3      
005702f9 cc                       int3      
005702fa cc                       int3      
005702fb cc                       int3      
005702fc cc                       int3      
005702fd cc                       int3      
005702fe cc                       int3      
005702ff cc                       int3      
00570300 c3                       ret       
00570301 cc                       int3      
00570302 cc                       int3      
00570303 cc                       int3      
00570304 cc                       int3      
00570305 cc                       int3      
00570306 cc                       int3      
00570307 cc                       int3      
00570308 cc                       int3      
00570309 cc                       int3      
0057030a cc                       int3      
0057030b cc                       int3      
0057030c cc                       int3      
0057030d cc                       int3      
0057030e cc                       int3      
0057030f cc                       int3      
00570310 c3                       ret       
00570311 cc                       int3      
00570312 cc                       int3      
00570313 cc                       int3      
00570314 cc                       int3      
00570315 cc                       int3      
00570316 cc                       int3      
00570317 cc                       int3      
00570318 cc                       int3      
00570319 cc                       int3      
0057031a cc                       int3      
0057031b cc                       int3      
0057031c cc                       int3      
0057031d cc                       int3      
0057031e cc                       int3      
0057031f cc                       int3      
00570320 56                       push      esi
00570321 8bf1                     mov       esi, ecx
00570323 8b06                     mov       eax, dword ptr [esi]
00570325 ff900c010000             call      dword ptr [eax + 0x10c]
0057032b 8bc8                     mov       ecx, eax
0057032d e85ebdf2ff               call      0x49c090
00570332 84c0                     test      al, al
00570334 0f84cc000000             je        0x570406
0057033a 8b16                     mov       edx, dword ptr [esi]
0057033c 8bce                     mov       ecx, esi
0057033e ff920c010000             call      dword ptr [edx + 0x10c]
00570344 8b10                     mov       edx, dword ptr [eax]
00570346 6811010000               push      0x111
0057034b 8bc8                     mov       ecx, eax
0057034d ff522c                   call      dword ptr [edx + 0x2c]
00570350 84c0                     test      al, al
00570352 0f84ae000000             je        0x570406
00570358 8b06                     mov       eax, dword ptr [esi]
0057035a 8bce                     mov       ecx, esi
0057035c ff                       .byte     0xff
0057035d 90                       nop       
0057035e 0c01                     or        al, 1

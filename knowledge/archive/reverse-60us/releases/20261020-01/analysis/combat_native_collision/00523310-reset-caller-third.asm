00523310 0000                     add       byte ptr [eax], al
00523312 898eb0060000             mov       dword ptr [esi + 0x6b0], ecx
00523318 898eb4060000             mov       dword ptr [esi + 0x6b4], ecx
0052331e 898eb8060000             mov       dword ptr [esi + 0x6b8], ecx
00523324 898ebc060000             mov       dword ptr [esi + 0x6bc], ecx
0052332a 898ec0060000             mov       dword ptr [esi + 0x6c0], ecx
00523330 898ec4060000             mov       dword ptr [esi + 0x6c4], ecx
00523336 898ec8060000             mov       dword ptr [esi + 0x6c8], ecx
0052333c 898ecc060000             mov       dword ptr [esi + 0x6cc], ecx
00523342 898ed0060000             mov       dword ptr [esi + 0x6d0], ecx
00523348 898ed4060000             mov       dword ptr [esi + 0x6d4], ecx
0052334e 68920e0000               push      0xe92
00523353 898ed8060000             mov       dword ptr [esi + 0x6d8], ecx
00523359 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0052335f 50                       push      eax
00523360 e89b3c5f00               call      0xb17000
00523365 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0052336b 68930e0000               push      0xe93
00523370 8d96ac070000             lea       edx, [esi + 0x7ac]
00523376 52                       push      edx
00523377 e8843c5f00               call      0xb17000
0052337c 5f                       pop       edi
0052337d 889e10080000             mov       byte ptr [esi + 0x810], bl
00523383 5e                       pop       esi
00523384 5b                       pop       ebx
00523385 c3                       ret       
00523386 cc                       int3      
00523387 cc                       int3      
00523388 cc                       int3      
00523389 cc                       int3      
0052338a cc                       int3      
0052338b cc                       int3      
0052338c cc                       int3      
0052338d cc                       int3      
0052338e cc                       int3      
0052338f cc                       int3      
00523390 55                       push      ebp
00523391 8bec                     mov       ebp, esp
00523393 83ec08                   sub       esp, 8
00523396 56                       push      esi
00523397 57                       push      edi
00523398 8bf1                     mov       esi, ecx
0052339a e8a19dfcff               call      0x4ed140
0052339f 83be3406000003           cmp       dword ptr [esi + 0x634], 3
005233a6 7410                     je        0x5233b8
005233a8 8b8638060000             mov       eax, dword ptr [esi + 0x638]
005233ae 8a8880000000             mov       cl, byte ptr [eax + 0x80]
005233b4 84c9                     test      cl, cl
005233b6 7527                     jne       0x5233df
005233b8 8bbe38060000             mov       edi, dword ptr [esi + 0x638]
005233be 8bcf                     mov       ecx, edi
005233c0 e82b1beeff               call      0x404ef0
005233c5 8d4f40                   lea       ecx, [edi + 0x40]
005233c8 e8231beeff               call      0x404ef0
005233cd 8b16                     mov       edx, dword ptr [esi]
005233cf 6a01                     push      1
005233d1 6a01                     push      1
005233d3 6a00                     push      0
005233d5 6a00                     push      0
005233d7 8bce                     mov       ecx, esi
005233d9 ff922c020000             call      dword ptr [edx + 0x22c]
005233df 8b06                     mov       eax, dword ptr [esi]
005233e1 53                       push      ebx
005233e2 8bce                     mov       ecx, esi
005233e4 ff908c010000             call      dword ptr [eax + 0x18c]
005233ea 8bf8                     mov       edi, eax
005233ec 85ff                     test      edi, edi
005233ee 0f84a4000000             je        0x523498
005233f4 8b17                     mov       edx, dword ptr [edi]
005233f6 8bcf                     mov       ecx, edi
005233f8 ff9294000000             call      dword ptr [edx + 0x94]
005233fe 8945f8                   mov       dword ptr [ebp - 8], eax
00523401 8b07                     mov       eax, dword ptr [edi]
00523403 8bcf                     mov       ecx, edi
00523405 ff9098000000             call      dword ptr [eax + 0x98]
0052340b 8b16                     mov       edx, dword ptr [esi]
0052340d 6a03                     push      3
0052340f 6aff                     push      -1
00523411 6a64                     push      0x64
00523413 50                       push      eax
00523414 8945fc                   mov       dword ptr [ebp - 4], eax
00523417 8b45f8                   mov       eax, dword ptr [ebp - 8]
0052341a 50                       push      eax
0052341b 8d4dfc                   lea       ecx, [ebp - 4]
0052341e 51                       push      ecx
0052341f 8d45f8                   lea       eax, [ebp - 8]
00523422 50                       push      eax
00523423 8bce                     mov       ecx, esi
00523425 ff92b0000000             call      dword ptr [edx + 0xb0]
0052342b 8b861c020000             mov       eax, dword ptr [esi + 0x21c]
00523431 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
00523434 8b16                     mov       edx, dword ptr [esi]
00523436 50                       push      eax
00523437 8b45f8                   mov       eax, dword ptr [ebp - 8]
0052343a 51                       push      ecx
0052343b 50                       push      eax
0052343c 8bce                     mov       ecx, esi
0052343e ff9288000000             call      dword ptr [edx + 0x88]
00523444 8b17                     mov       edx, dword ptr [edi]
00523446 8b1e                     mov       ebx, dword ptr [esi]
00523448 8bcf                     mov       ecx, edi
0052344a ff92c0000000             call      dword ptr [edx + 0xc0]
00523450 50                       push      eax
00523451 8bce                     mov       ecx, esi
00523453 ff93bc000000             call      dword ptr [ebx + 0xbc]
00523459 33db                     xor       ebx, ebx
0052345b bf1c000000               mov       edi, 0x1c

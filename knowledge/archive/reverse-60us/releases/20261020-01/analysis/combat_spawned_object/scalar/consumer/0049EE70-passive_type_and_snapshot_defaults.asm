0049ee70  53                       push       ebx
0049ee71  33db                     xor        ebx, ebx
0049ee73  56                       push       esi
0049ee74  8bf1                     mov        esi, ecx
0049ee76  57                       push       edi
0049ee77  b8ff000000               mov        eax, 0xff
0049ee7c  53                       push       ebx
0049ee7d  6a05                     push       5
0049ee7f  8d8ea8050000             lea        ecx, [esi + 0x5a8]
0049ee85  c786e400000021000000     mov        dword ptr [esi + 0xe4], 0x21
0049ee8f  899e20050000             mov        dword ptr [esi + 0x520], ebx
0049ee95  c78698040000c8000000     mov        dword ptr [esi + 0x498], 0xc8
0049ee9f  899e94070000             mov        dword ptr [esi + 0x794], ebx
0049eea5  c7869807000001000000     mov        dword ptr [esi + 0x798], 1
0049eeaf  899e9c070000             mov        dword ptr [esi + 0x79c], ebx
0049eeb5  899ea0070000             mov        dword ptr [esi + 0x7a0], ebx
0049eebb  899ea4070000             mov        dword ptr [esi + 0x7a4], ebx
0049eec1  899ea8070000             mov        dword ptr [esi + 0x7a8], ebx
0049eec7  899eac070000             mov        dword ptr [esi + 0x7ac], ebx
0049eecd  899eb0070000             mov        dword ptr [esi + 0x7b0], ebx
0049eed3  899eb4070000             mov        dword ptr [esi + 0x7b4], ebx
0049eed9  899eb8070000             mov        dword ptr [esi + 0x7b8], ebx
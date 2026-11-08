00438810  56                       push       esi
00438811  8bf1                     mov        esi, ecx
00438813  57                       push       edi
00438814  8d8e0c020000             lea        ecx, [esi + 0x20c]
0043881a  e84198fcff               call       0x402060
0043881f  99                       cdq        
00438820  2bc2                     sub        eax, edx
00438822  8bf8                     mov        edi, eax
00438824  8b06                     mov        eax, dword ptr [esi]
00438826  8bce                     mov        ecx, esi
00438828  d1ff                     sar        edi, 1
0043882a  ff9094000000             call       dword ptr [eax + 0x94]
00438830  2bc7                     sub        eax, edi
00438832  5f                       pop        edi
00438833  5e                       pop        esi
00438834  c3                       ret        
00438835  cc                       int3       
00438836  cc                       int3       
00438837  cc                       int3       
00438838  cc                       int3       
00438839  cc                       int3       
0043883a  cc                       int3       
0043883b  cc                       int3       
0043883c  cc                       int3       
0043883d  cc                       int3       
0043883e  cc                       int3       
0043883f  cc                       int3       
00438840  56                       push       esi
00438841  8bf1                     mov        esi, ecx
00438843  57                       push       edi
00438844  8d8e0c020000             lea        ecx, [esi + 0x20c]
0043884a  e81198fcff               call       0x402060
0043884f  8bf8                     mov        edi, eax
00438851  8b06                     mov        eax, dword ptr [esi]
00438853  8bce                     mov        ecx, esi
00438855  ff900c020000             call       dword ptr [eax + 0x20c]
0043885b  03c7                     add        eax, edi
0043885d  5f                       pop        edi
0043885e  5e                       pop        esi
0043885f  c3                       ret        
00438860  56                       push       esi
00438861  8bf1                     mov        esi, ecx
00438863  57                       push       edi
00438864  8d8e14020000             lea        ecx, [esi + 0x214]
0043886a  e8f197fcff               call       0x402060
0043886f  99                       cdq        
00438870  2bc2                     sub        eax, edx
00438872  8bf8                     mov        edi, eax
00438874  8b06                     mov        eax, dword ptr [esi]
00438876  8bce                     mov        ecx, esi
00438878  d1ff                     sar        edi, 1
0043887a  ff9098000000             call       dword ptr [eax + 0x98]
00438880  2bc7                     sub        eax, edi
00438882  5f                       pop        edi
00438883  5e                       pop        esi
00438884  c3                       ret        
00438885  cc                       int3       
00438886  cc                       int3       
00438887  cc                       int3       
00438888  cc                       int3       
00438889  cc                       int3       
0043888a  cc                       int3       
0043888b  cc                       int3       
0043888c  cc                       int3       
0043888d  cc                       int3       
0043888e  cc                       int3       
0043888f  cc                       int3       
00438890  56                       push       esi
00438891  8bf1                     mov        esi, ecx
00438893  57                       push       edi
00438894  8d8e14020000             lea        ecx, [esi + 0x214]
0043889a  e8c197fcff               call       0x402060
0043889f  8bf8                     mov        edi, eax
004388a1  8b06                     mov        eax, dword ptr [esi]
004388a3  8bce                     mov        ecx, esi
004388a5  ff9014020000             call       dword ptr [eax + 0x214]
004388ab  03c7                     add        eax, edi
004388ad  5f                       pop        edi
004388ae  5e                       pop        esi
004388af  c3                       ret        

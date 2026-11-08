004de314  36c9                     leave      
004de316  4d                       dec        ebp
004de317  00bfca4d00e4             add        byte ptr [edi - 0x1bffb236], bh
004de31d  cc                       int3       
004de31e  4d                       dec        ebp
004de31f  00d2                     add        dl, dl
004de321  d14d00                   ror        dword ptr [ebp], 1
004de324  11d3                     adc        ebx, edx
004de326  4d                       dec        ebp
004de327  003e                     add        byte ptr [esi], bh
004de329  d34d00                   ror        dword ptr [ebp], cl
004de32c  51                       push       ecx
004de32d  d34d00                   ror        dword ptr [ebp], cl
004de330  2f                       das        
004de331  d44d                     aam        0x4d
004de333  0000                     add        byte ptr [eax], al
004de335  07                       pop        es
004de336  07                       pop        es
004de337  07                       pop        es
004de338  07                       pop        es
004de339  0107                     add        dword ptr [edi], eax
004de33b  07                       pop        es
004de33c  07                       pop        es
004de33d  07                       pop        es
004de33e  0203                     add        al, byte ptr [ebx]
004de340  0405                     add        al, 5
004de342  06                       push       es
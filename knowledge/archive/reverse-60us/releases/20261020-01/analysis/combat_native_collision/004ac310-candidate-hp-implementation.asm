004ac310 55                       push      ebp
004ac311 8bec                     mov       ebp, esp
004ac313 56                       push      esi
004ac314 57                       push      edi
004ac315 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ac318 57                       push      edi
004ac319 8bf1                     mov       esi, ecx
004ac31b e820c50300               call      0x4e8840
004ac320 83ff07                   cmp       edi, 7
004ac323 7536                     jne       0x4ac35b
004ac325 8b06                     mov       eax, dword ptr [esi]
004ac327 8bce                     mov       ecx, esi
004ac329 ff9034020000             call      dword ptr [eax + 0x234]
004ac32f 85c0                     test      eax, eax
004ac331 7e28                     jle       0x4ac35b
004ac333 8b3e                     mov       edi, dword ptr [esi]
004ac335 6a01                     push      1
004ac337 6a00                     push      0
004ac339 8bce                     mov       ecx, esi
004ac33b ff9734020000             call      dword ptr [edi + 0x234]
004ac341 894508                   mov       dword ptr [ebp + 8], eax
004ac344 db4508                   fild      dword ptr [ebp + 8]
004ac347 d80d2809cd00             fmul      dword ptr [0xcd0928]
004ac34d e8f2517500               call      0xc01544
004ac352 50                       push      eax
004ac353 8bce                     mov       ecx, esi
004ac355 ff97ec030000             call      dword ptr [edi + 0x3ec]
004ac35b 5f                       pop       edi
004ac35c 5e                       pop       esi
004ac35d 5d                       pop       ebp
004ac35e c20400                   ret       4
004ac361 cc                       int3      
004ac362 cc                       int3      
004ac363 cc                       int3      
004ac364 cc                       int3      
004ac365 cc                       int3      
004ac366 cc                       int3      
004ac367 cc                       int3      
004ac368 cc                       int3      
004ac369 cc                       int3      
004ac36a cc                       int3      
004ac36b cc                       int3      
004ac36c cc                       int3      
004ac36d cc                       int3      
004ac36e cc                       int3      
004ac36f cc                       int3      
004ac370 55                       push      ebp
004ac371 8bec                     mov       ebp, esp
004ac373 56                       push      esi
004ac374 57                       push      edi
004ac375 8b7d08                   mov       edi, dword ptr [ebp + 8]
004ac378 57                       push      edi
004ac379 8bf1                     mov       esi, ecx
004ac37b e8d0c40300               call      0x4e8850
004ac380 83ff07                   cmp       edi, 7
004ac383 7563                     jne       0x4ac3e8
004ac385 8b06                     mov       eax, dword ptr [esi]
004ac387 8bce                     mov       ecx, esi
004ac389 ff9034020000             call      dword ptr [eax + 0x234]
004ac38f 85c0                     test      eax, eax
004ac391 7e55                     jle       0x4ac3e8
004ac393 8b16                     mov       edx, dword ptr [esi]
004ac395 8bce                     mov       ecx, esi
004ac397 ff9234020000             call      dword ptr [edx + 0x234]
004ac39d 894508                   mov       dword ptr [ebp + 8], eax

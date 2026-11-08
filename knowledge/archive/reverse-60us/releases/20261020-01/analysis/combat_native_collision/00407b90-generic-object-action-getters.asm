00407b90 55                       push      ebp
00407b91 8bec                     mov       ebp, esp
00407b93 8b4508                   mov       eax, dword ptr [ebp + 8]
00407b96 898100010000             mov       dword ptr [ecx + 0x100], eax
00407b9c 5d                       pop       ebp
00407b9d c20400                   ret       4
00407ba0 8b8100010000             mov       eax, dword ptr [ecx + 0x100]
00407ba6 c3                       ret       
00407ba7 cc                       int3      
00407ba8 cc                       int3      
00407ba9 cc                       int3      
00407baa cc                       int3      
00407bab cc                       int3      
00407bac cc                       int3      
00407bad cc                       int3      
00407bae cc                       int3      
00407baf cc                       int3      
00407bb0 8a8184010000             mov       al, byte ptr [ecx + 0x184]
00407bb6 c3                       ret       
00407bb7 cc                       int3      
00407bb8 cc                       int3      
00407bb9 cc                       int3      
00407bba cc                       int3      
00407bbb cc                       int3      
00407bbc cc                       int3      
00407bbd cc                       int3      
00407bbe cc                       int3      
00407bbf cc                       int3      
00407bc0 55                       push      ebp
00407bc1 8bec                     mov       ebp, esp
00407bc3 8b9104010000             mov       edx, dword ptr [ecx + 0x104]
00407bc9 85d2                     test      edx, edx
00407bcb 8b4508                   mov       eax, dword ptr [ebp + 8]
00407bce 898118010000             mov       dword ptr [ecx + 0x118], eax
00407bd4 7509                     jne       0x407bdf
00407bd6 8b11                     mov       edx, dword ptr [ecx]
00407bd8 50                       push      eax
00407bd9 ff92f0000000             call      dword ptr [edx + 0xf0]
00407bdf 5d                       pop       ebp
00407be0 c20400                   ret       4
00407be3 cc                       int3      
00407be4 cc                       int3      
00407be5 cc                       int3      
00407be6 cc                       int3      
00407be7 cc                       int3      
00407be8 cc                       int3      
00407be9 cc                       int3      
00407bea cc                       int3      
00407beb cc                       int3      
00407bec cc                       int3      
00407bed cc                       int3      
00407bee cc                       int3      
00407bef cc                       int3      
00407bf0 55                       push      ebp
00407bf1 8bec                     mov       ebp, esp
00407bf3 8b9148010000             mov       edx, dword ptr [ecx + 0x148]
00407bf9 85d2                     test      edx, edx
00407bfb 8b4508                   mov       eax, dword ptr [ebp + 8]
00407bfe 89814c010000             mov       dword ptr [ecx + 0x14c], eax
00407c04 7509                     jne       0x407c0f
00407c06 8b11                     mov       edx, dword ptr [ecx]
00407c08 50                       push      eax
00407c09 ff9200010000             call      dword ptr [edx + 0x100]
00407c0f 5d                       pop       ebp
00407c10 c20400                   ret       4
00407c13 cc                       int3      
00407c14 cc                       int3      
00407c15 cc                       int3      
00407c16 cc                       int3      
00407c17 cc                       int3      
00407c18 cc                       int3      
00407c19 cc                       int3      
00407c1a cc                       int3      
00407c1b cc                       int3      
00407c1c cc                       int3      
00407c1d cc                       int3      
00407c1e cc                       int3      
00407c1f cc                       int3      
00407c20 8b8118010000             mov       eax, dword ptr [ecx + 0x118]
00407c26 c3                       ret       
00407c27 cc                       int3      
00407c28 cc                       int3      
00407c29 cc                       int3      
00407c2a cc                       int3      
00407c2b cc                       int3      
00407c2c cc                       int3      
00407c2d cc                       int3      
00407c2e cc                       int3      
00407c2f cc                       int3      
00407c30 8b01                     mov       eax, dword ptr [ecx]
00407c32 6a00                     push      0
00407c34 ff9090000000             call      dword ptr [eax + 0x90]
00407c3a c3                       ret       
00407c3b cc                       int3      
00407c3c cc                       int3      
00407c3d cc                       int3      
00407c3e cc                       int3      
00407c3f cc                       int3      
00407c40 8b01                     mov       eax, dword ptr [ecx]
00407c42 6a01                     push      1
00407c44 ff9090000000             call      dword ptr [eax + 0x90]
00407c4a c3                       ret       
00407c4b cc                       int3      
00407c4c cc                       int3      
00407c4d cc                       int3      
00407c4e cc                       int3      
00407c4f cc                       int3      
00407c50 8b01                     mov       eax, dword ptr [ecx]
00407c52 6a02                     push      2
00407c54 ff9090000000             call      dword ptr [eax + 0x90]
00407c5a c3                       ret       
00407c5b cc                       int3      
00407c5c cc                       int3      
00407c5d cc                       int3      
00407c5e cc                       int3      
00407c5f cc                       int3      
00407c60 56                       push      esi
00407c61 8bf1                     mov       esi, ecx
00407c63 8b06                     mov       eax, dword ptr [esi]
00407c65 ff9098000000             call      dword ptr [eax + 0x98]
00407c6b 0386fc000000             add       eax, dword ptr [esi + 0xfc]
00407c71 5e                       pop       esi
00407c72 c3                       ret       
00407c73 cc                       int3      
00407c74 cc                       int3      
00407c75 cc                       int3      
00407c76 cc                       int3      
00407c77 cc                       int3      
00407c78 cc                       int3      
00407c79 cc                       int3      
00407c7a cc                       int3      
00407c7b cc                       int3      
00407c7c cc                       int3      
00407c7d cc                       int3      
00407c7e cc                       int3      
00407c7f cc                       int3      
00407c80 55                       push      ebp
00407c81 8bec                     mov       ebp, esp
00407c83 8b4508                   mov       eax, dword ptr [ebp + 8]
00407c86 8981fc000000             mov       dword ptr [ecx + 0xfc], eax
00407c8c 5d                       pop       ebp
00407c8d c20400                   ret       4
00407c90 55                       push      ebp
00407c91 8bec                     mov       ebp, esp
00407c93 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00407c96 85c0                     test      eax, eax
00407c98 7406                     je        0x407ca0
00407c9a c70000000000             mov       dword ptr [eax], 0
00407ca0 b001                     mov       al, 1
00407ca2 5d                       pop       ebp
00407ca3 c20c00                   ret       0xc
00407ca6 cc                       int3      
00407ca7 cc                       int3      
00407ca8 cc                       int3      
00407ca9 cc                       int3      
00407caa cc                       int3      
00407cab cc                       int3      
00407cac cc                       int3      
00407cad cc                       int3      
00407cae cc                       int3      
00407caf cc                       int3      
00407cb0 55                       push      ebp
00407cb1 8bec                     mov       ebp, esp
00407cb3 56                       push      esi
00407cb4 8bf1                     mov       esi, ecx
00407cb6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00407cb9 8b01                     mov       eax, dword ptr [ecx]
00407cbb 57                       push      edi
00407cbc ff9094000000             call      dword ptr [eax + 0x94]
00407cc2 8b16                     mov       edx, dword ptr [esi]
00407cc4 8bce                     mov       ecx, esi
00407cc6 8bf8                     mov       edi, eax
00407cc8 ff9294000000             call      dword ptr [edx + 0x94]
00407cce 2bc7                     sub       eax, edi
00407cd0 99                       cdq       
00407cd1 33c2                     xor       eax, edx
00407cd3 5f                       pop       edi
00407cd4 2bc2                     sub       eax, edx
00407cd6 5e                       pop       esi
00407cd7 5d                       pop       ebp
00407cd8 c20400                   ret       4
00407cdb cc                       int3      
00407cdc cc                       int3      
00407cdd cc                       int3      
00407cde cc                       int3      
00407cdf cc                       int3      
00407ce0 55                       push      ebp
00407ce1 8bec                     mov       ebp, esp
00407ce3 56                       push      esi
00407ce4 8bf1                     mov       esi, ecx
00407ce6 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00407ce9 8b01                     mov       eax, dword ptr [ecx]
00407ceb 57                       push      edi
00407cec ff9098000000             call      dword ptr [eax + 0x98]
00407cf2 8b16                     mov       edx, dword ptr [esi]
00407cf4 8bce                     mov       ecx, esi
00407cf6 8bf8                     mov       edi, eax
00407cf8 ff9298000000             call      dword ptr [edx + 0x98]
00407cfe 2bc7                     sub       eax, edi

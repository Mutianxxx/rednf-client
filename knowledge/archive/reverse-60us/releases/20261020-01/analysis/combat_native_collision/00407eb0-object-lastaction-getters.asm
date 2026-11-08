00407eb0 8a8194010000             mov       al, byte ptr [ecx + 0x194]
00407eb6 c3                       ret       
00407eb7 cc                       int3      
00407eb8 cc                       int3      
00407eb9 cc                       int3      
00407eba cc                       int3      
00407ebb cc                       int3      
00407ebc cc                       int3      
00407ebd cc                       int3      
00407ebe cc                       int3      
00407ebf cc                       int3      
00407ec0 8b01                     mov       eax, dword ptr [ecx]
00407ec2 6a00                     push      0
00407ec4 6aff                     push      -1
00407ec6 6a00                     push      0
00407ec8 ff901c010000             call      dword ptr [eax + 0x11c]
00407ece c3                       ret       
00407ecf cc                       int3      
00407ed0 8b81b0010000             mov       eax, dword ptr [ecx + 0x1b0]
00407ed6 c3                       ret       
00407ed7 cc                       int3      
00407ed8 cc                       int3      
00407ed9 cc                       int3      
00407eda cc                       int3      
00407edb cc                       int3      
00407edc cc                       int3      
00407edd cc                       int3      
00407ede cc                       int3      
00407edf cc                       int3      
00407ee0 56                       push      esi
00407ee1 8bf1                     mov       esi, ecx
00407ee3 8d4e20                   lea       ecx, [esi + 0x20]
00407ee6 e815f06f00               call      0xb06f00
00407eeb 2b86b8010000             sub       eax, dword ptr [esi + 0x1b8]
00407ef1 5e                       pop       esi
00407ef2 c3                       ret       
00407ef3 cc                       int3      
00407ef4 cc                       int3      
00407ef5 cc                       int3      
00407ef6 cc                       int3      
00407ef7 cc                       int3      
00407ef8 cc                       int3      
00407ef9 cc                       int3      
00407efa cc                       int3      
00407efb cc                       int3      
00407efc cc                       int3      
00407efd cc                       int3      
00407efe cc                       int3      
00407eff cc                       int3      
00407f00 8b81b4010000             mov       eax, dword ptr [ecx + 0x1b4]
00407f06 c3                       ret       
00407f07 cc                       int3      
00407f08 cc                       int3      
00407f09 cc                       int3      
00407f0a cc                       int3      
00407f0b cc                       int3      
00407f0c cc                       int3      
00407f0d cc                       int3      
00407f0e cc                       int3      
00407f0f cc                       int3      
00407f10 56                       push      esi
00407f11 8bf1                     mov       esi, ecx
00407f13 8b06                     mov       eax, dword ptr [esi]
00407f15 57                       push      edi
00407f16 ff902c010000             call      dword ptr [eax + 0x12c]
00407f1c 8b16                     mov       edx, dword ptr [esi]
00407f1e 8bce                     mov       ecx, esi

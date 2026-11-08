004aec00 fc                       cld       
004aec01 885700                   mov       byte ptr [edi], dl
004aec04 5e                       pop       esi
004aec05 5d                       pop       ebp
004aec06 c20800                   ret       8
004aec09 cc                       int3      
004aec0a cc                       int3      
004aec0b cc                       int3      
004aec0c cc                       int3      
004aec0d cc                       int3      
004aec0e cc                       int3      
004aec0f cc                       int3      
004aec10 55                       push      ebp
004aec11 8bec                     mov       ebp, esp
004aec13 51                       push      ecx
004aec14 53                       push      ebx
004aec15 56                       push      esi
004aec16 57                       push      edi
004aec17 8bf1                     mov       esi, ecx
004aec19 e822e50300               call      0x4ed140
004aec1e 8b06                     mov       eax, dword ptr [esi]
004aec20 8bce                     mov       ecx, esi
004aec22 ff9008020000             call      dword ptr [eax + 0x208]
004aec28 85c0                     test      eax, eax
004aec2a 7f47                     jg        0x4aec73
004aec2c 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004aec32 8b4244                   mov       eax, dword ptr [edx + 0x44]
004aec35 8b8e40160000             mov       ecx, dword ptr [esi + 0x1640]
004aec3b 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004aec41 8d0488                   lea       eax, [eax + ecx*4]
004aec44 8bc8                     mov       ecx, eax
004aec46 33cb                     xor       ecx, ebx
004aec48 81f124faffff             xor       ecx, 0xfffffa24
004aec4e 8908                     mov       dword ptr [eax], ecx
004aec50 a1d8012101               mov       eax, dword ptr [0x12101d8]
004aec55 8b9640160000             mov       edx, dword ptr [esi + 0x1640]
004aec5b 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004aec5e 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004aec64 8d0491                   lea       eax, [ecx + edx*4]
004aec67 8bd0                     mov       edx, eax
004aec69 33d3                     xor       edx, ebx
004aec6b 81f224faffff             xor       edx, 0xfffffa24
004aec71 eb39                     jmp       0x4aecac
004aec73 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004aec79 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004aec7c 8b8640160000             mov       eax, dword ptr [esi + 0x1640]
004aec82 8d0482                   lea       eax, [edx + eax*4]
004aec85 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004aec8b 8bc8                     mov       ecx, eax
004aec8d 33ca                     xor       ecx, edx
004aec8f 8908                     mov       dword ptr [eax], ecx
004aec91 a1d8012101               mov       eax, dword ptr [0x12101d8]
004aec96 8b9640160000             mov       edx, dword ptr [esi + 0x1640]
004aec9c 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004aec9f 8d0491                   lea       eax, [ecx + edx*4]
004aeca2 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004aeca8 8bd0                     mov       edx, eax
004aecaa 33d1                     xor       edx, ecx
004aecac 8d8e48150000             lea       ecx, [esi + 0x1548]
004aecb2 8910                     mov       dword ptr [eax], edx
004aecb4 e877202a00               call      0x750d30
004aecb9 8d8ea0000000             lea       ecx, [esi + 0xa0]
004aecbf e83c826500               call      0xb06f00
004aecc4 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004aecca 8b5244                   mov       edx, dword ptr [edx + 0x44]
004aeccd 8b8eb0150000             mov       ecx, dword ptr [esi + 0x15b0]
004aecd3 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004aecd9 8d0c8a                   lea       ecx, [edx + ecx*4]
004aecdc 8bd1                     mov       edx, ecx
004aecde 33d7                     xor       edx, edi
004aece0 33d0                     xor       edx, eax
004aece2 8911                     mov       dword ptr [ecx], edx
004aece4 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004aecea 8b5248                   mov       edx, dword ptr [edx + 0x48]
004aeced 8b8eb0150000             mov       ecx, dword ptr [esi + 0x15b0]
004aecf3 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004aecf9 8d0c8a                   lea       ecx, [edx + ecx*4]
004aecfc 8bd1                     mov       edx, ecx
004aecfe 33d7                     xor       edx, edi
004aed00 33d0                     xor       edx, eax
004aed02 8911                     mov       dword ptr [ecx], edx
004aed04 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004aed0a 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004aed0d 8b86c0150000             mov       eax, dword ptr [esi + 0x15c0]
004aed13 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004aed19 8d0482                   lea       eax, [edx + eax*4]
004aed1c 8bd0                     mov       edx, eax
004aed1e c745fc00000000           mov       dword ptr [ebp - 4], 0
004aed25 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004aed28 33d1                     xor       edx, ecx
004aed2a 33d3                     xor       edx, ebx
004aed2c 8910                     mov       dword ptr [eax], edx
004aed2e 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004aed34 8b5248                   mov       edx, dword ptr [edx + 0x48]
004aed37 8b86c0150000             mov       eax, dword ptr [esi + 0x15c0]
004aed3d 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004aed43 8d0482                   lea       eax, [edx + eax*4]
004aed46 8bd0                     mov       edx, eax
004aed48 33d1                     xor       edx, ecx
004aed4a 33d3                     xor       edx, ebx
004aed4c 8910                     mov       dword ptr [eax], edx
004aed4e 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004aed54 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004aed57 8b86b8150000             mov       eax, dword ptr [esi + 0x15b8]
004aed5d 8b1ddc012101             mov       ebx, dword ptr [0x12101dc]
004aed63 8d0482                   lea       eax, [edx + eax*4]
004aed66 8bd0                     mov       edx, eax
004aed68 c745fc00000000           mov       dword ptr [ebp - 4], 0
004aed6f 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004aed72 33d1                     xor       edx, ecx
004aed74 33d3                     xor       edx, ebx
004aed76 8910                     mov       dword ptr [eax], edx
004aed78 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004aed7e 8b                       .byte     0x8b
004aed7f 52                       push      edx

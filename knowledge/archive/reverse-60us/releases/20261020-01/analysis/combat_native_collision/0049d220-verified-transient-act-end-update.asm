0049d220 56                       push      esi
0049d221 8bf1                     mov       esi, ecx
0049d223 8a8685010000             mov       al, byte ptr [esi + 0x185]
0049d229 84c0                     test      al, al
0049d22b 741e                     je        0x49d24b
0049d22d 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049d233 e878fd5800               call      0xa2cfb0
0049d238 8a883a010000             mov       cl, byte ptr [eax + 0x13a]
0049d23e 84c9                     test      cl, cl
0049d240 7409                     je        0x49d24b
0049d242 8b06                     mov       eax, dword ptr [esi]
0049d244 6a00                     push      0
0049d246 8bce                     mov       ecx, esi
0049d248 ff5060                   call      dword ptr [eax + 0x60]
0049d24b 8bce                     mov       ecx, esi
0049d24d 5e                       pop       esi
0049d24e e92decffff               jmp       0x49be80

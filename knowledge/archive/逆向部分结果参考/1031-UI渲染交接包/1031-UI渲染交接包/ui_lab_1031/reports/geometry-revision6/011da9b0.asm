
<stdin>:	file format elf32-i386

Disassembly of section .text:

011da9b0 <.text>:
 11da9b0: 55                           	push	ebp
 11da9b1: 8b ec                        	mov	ebp, esp
 11da9b3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11da9b6: 56                           	push	esi
 11da9b7: 50                           	push	eax
 11da9b8: 8b f1                        	mov	esi, ecx
 11da9ba: e8 41 9e fd ff               	call	0x11b4800
 11da9bf: 33 c0                        	xor	eax, eax
 11da9c1: 33 c9                        	xor	ecx, ecx
 11da9c3: c7 06 6c c7 85 01            	mov	dword ptr [esi], 0x185c76c
 11da9c9: 89 46 10                     	mov	dword ptr [esi + 0x10], eax
 11da9cc: 66 89 4e 0c                  	mov	word ptr [esi + 0xc], cx
 11da9d0: 89 46 5c                     	mov	dword ptr [esi + 0x5c], eax
 11da9d3: 89 46 60                     	mov	dword ptr [esi + 0x60], eax
 11da9d6: 89 46 64                     	mov	dword ptr [esi + 0x64], eax
 11da9d9: 89 46 68                     	mov	dword ptr [esi + 0x68], eax
 11da9dc: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11da9e2: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11da9e5: 8b c6                        	mov	eax, esi
 11da9e7: 5e                           	pop	esi
 11da9e8: 5d                           	pop	ebp
 11da9e9: c2 0c 00                     	ret	0xc

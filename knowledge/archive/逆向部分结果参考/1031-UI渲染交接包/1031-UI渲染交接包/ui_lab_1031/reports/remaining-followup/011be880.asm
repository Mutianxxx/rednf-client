
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be880 <.text>:
 11be880: 56                           	push	esi
 11be881: 8b f1                        	mov	esi, ecx
 11be883: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 11be886: 8b 01                        	mov	eax, dword ptr [ecx]
 11be888: 89 09                        	mov	dword ptr [ecx], ecx
 11be88a: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 11be88d: 89 49 04                     	mov	dword ptr [ecx + 0x4], ecx
 11be890: c7 46 6c 00 00 00 00         	mov	dword ptr [esi + 0x6c], 0x0
 11be897: 3b 46 68                     	cmp	eax, dword ptr [esi + 0x68]
 11be89a: 74 17                        	je	0x11be8b3 <.text+0x33>
 11be89c: 57                           	push	edi
 11be89d: 8d 49 00                     	lea	ecx, [ecx]
 11be8a0: 8b 38                        	mov	edi, dword ptr [eax]
 11be8a2: 50                           	push	eax
 11be8a3: e8 7f 72 21 00               	call	0x13d5b27 <.text+0x2172a7>
 11be8a8: 83 c4 04                     	add	esp, 0x4
 11be8ab: 8b c7                        	mov	eax, edi
 11be8ad: 3b 7e 68                     	cmp	edi, dword ptr [esi + 0x68]
 11be8b0: 75 ee                        	jne	0x11be8a0 <.text+0x20>
 11be8b2: 5f                           	pop	edi
 11be8b3: 5e                           	pop	esi
 11be8b4: c3                           	ret

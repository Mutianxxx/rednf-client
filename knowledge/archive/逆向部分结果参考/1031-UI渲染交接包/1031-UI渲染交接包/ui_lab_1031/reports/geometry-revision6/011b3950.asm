
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3950 <.text>:
 11b3950: 55                           	push	ebp
 11b3951: 8b ec                        	mov	ebp, esp
 11b3953: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11b3956: 85 c0                        	test	eax, eax
 11b3958: 74 15                        	je	0x11b396f <.text+0x1f>
 11b395a: 8b 10                        	mov	edx, dword ptr [eax]
 11b395c: 8b 92 b4 00 00 00            	mov	edx, dword ptr [edx + 0xb4]
 11b3962: 51                           	push	ecx
 11b3963: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b3966: 51                           	push	ecx
 11b3967: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b396a: 51                           	push	ecx
 11b396b: 8b c8                        	mov	ecx, eax
 11b396d: ff d2                        	call	edx
 11b396f: 5d                           	pop	ebp
 11b3970: c2 0c 00                     	ret	0xc

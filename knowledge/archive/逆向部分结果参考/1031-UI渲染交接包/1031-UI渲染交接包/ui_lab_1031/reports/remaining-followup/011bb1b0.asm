
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bb1b0 <.text>:
 11bb1b0: 55                           	push	ebp
 11bb1b1: 8b ec                        	mov	ebp, esp
 11bb1b3: 8b 41 24                     	mov	eax, dword ptr [ecx + 0x24]
 11bb1b6: 8b 51 28                     	mov	edx, dword ptr [ecx + 0x28]
 11bb1b9: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11bb1bc: 2b d0                        	sub	edx, eax
 11bb1be: c1 fa 02                     	sar	edx, 0x2
 11bb1c1: 3b ca                        	cmp	ecx, edx
 11bb1c3: 73 07                        	jae	0x11bb1cc <.text+0x1c>
 11bb1c5: 8b 04 88                     	mov	eax, dword ptr [eax + 4*ecx]
 11bb1c8: 5d                           	pop	ebp
 11bb1c9: c2 04 00                     	ret	0x4
 11bb1cc: 33 c0                        	xor	eax, eax
 11bb1ce: 5d                           	pop	ebp
 11bb1cf: c2 04 00                     	ret	0x4


<stdin>:	file format elf32-i386

Disassembly of section .text:

0119fef0 <.text>:
 119fef0: 55                           	push	ebp
 119fef1: 8b ec                        	mov	ebp, esp
 119fef3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 119fef6: 66 8b 08                     	mov	cx, word ptr [eax]
 119fef9: ba a1 2c 00 00               	mov	edx, 0x2ca1
 119fefe: 66 3b ca                     	cmp	cx, dx
 119ff01: 75 05                        	jne	0x119ff08 <.text+0x18>
 119ff03: 83 c0 04                     	add	eax, 0x4
 119ff06: 5d                           	pop	ebp
 119ff07: c3                           	ret
 119ff08: 6a 02                        	push	0x2
 119ff0a: 50                           	push	eax
 119ff0b: e8 90 fe ff ff               	call	0x119fda0
 119ff10: 83 c4 08                     	add	esp, 0x8
 119ff13: 5d                           	pop	ebp
 119ff14: c3                           	ret
 119ff15: cc                           	int3
 119ff16: cc                           	int3
 119ff17: cc                           	int3

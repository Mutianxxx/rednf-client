
<stdin>:	file format elf32-i386

Disassembly of section .text:

01075f03 <.text>:
 1075f03: 6a 7c                        	push	0x7c
 1075f05: e8 10 0c 36 00               	call	0x13d6b1a <.text+0x360c17>
 1075f0a: 8b f0                        	mov	esi, eax
 1075f0c: 83 c4 04                     	add	esp, 0x4
 1075f0f: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 1075f12: c7 45 fc 23 00 00 00         	mov	dword ptr [ebp - 0x4], 0x23
 1075f19: 85 f6                        	test	esi, esi
 1075f1b: 0f 84 a0 02 00 00            	je	0x10761c1 <.text+0x2be>
 1075f21: 8b ce                        	mov	ecx, esi
 1075f23: e8 f8 e7 ff ff               	call	0x1074720
 1075f28: c7 06 9c f4 82 01            	mov	dword ptr [esi], 0x182f49c
 1075f2e: e9 90 02 00 00               	jmp	0x10761c3 <.text+0x2c0>

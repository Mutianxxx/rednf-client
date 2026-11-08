
<stdin>:	file format elf32-i386

Disassembly of section .text:

010754d6 <.text>:
 10754d6: 80 3d 2c 84 af 01 00         	cmp	byte ptr [0x1af842c], 0x0
 10754dd: 0f 85 20 0a 00 00            	jne	0x1075f03 <.text+0xa2d>
 10754e3: 68 1c f7 82 01               	push	0x182f71c
 10754e8: e8 03 aa 12 00               	call	0x119fef0 <.text+0x12aa1a>
 10754ed: 83 c4 04                     	add	esp, 0x4
 10754f0: 8d 95 54 ff ff ff            	lea	edx, [ebp - 0xac]
 10754f6: 89 85 54 ff ff ff            	mov	dword ptr [ebp - 0xac], eax
 10754fc: 52                           	push	edx
 10754fd: 8d 85 14 fd ff ff            	lea	eax, [ebp - 0x2ec]
 1075503: 50                           	push	eax
 1075504: b9 34 84 af 01               	mov	ecx, 0x1af8434
 1075509: c7 85 58 ff ff ff 23 02 00 00	mov	dword ptr [ebp - 0xa8], 0x223
 1075513: e8 b8 36 3e ff               	call	0x458bd0

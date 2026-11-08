
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bdf90 <.text>:
 11bdf90: 83 c8 ff                     	or	eax, -0x1
 11bdf93: a3 e4 24 a4 01               	mov	dword ptr [0x1a424e4], eax
 11bdf98: a3 e8 24 a4 01               	mov	dword ptr [0x1a424e8], eax
 11bdf9d: a3 ec 24 a4 01               	mov	dword ptr [0x1a424ec], eax
 11bdfa2: a3 f0 24 a4 01               	mov	dword ptr [0x1a424f0], eax
 11bdfa7: a3 1c 25 a4 01               	mov	dword ptr [0x1a4251c], eax
 11bdfac: a3 f8 24 a4 01               	mov	dword ptr [0x1a424f8], eax
 11bdfb1: a3 fc 24 a4 01               	mov	dword ptr [0x1a424fc], eax
 11bdfb6: c3                           	ret
 11bdfb7: cc                           	int3
 11bdfb8: cc                           	int3
 11bdfb9: cc                           	int3
 11bdfba: cc                           	int3
 11bdfbb: cc                           	int3
 11bdfbc: cc                           	int3
 11bdfbd: cc                           	int3
 11bdfbe: cc                           	int3
 11bdfbf: cc                           	int3
 11bdfc0: 80 79 0d 00                  	cmp	byte ptr [ecx + 0xd], 0x0
 11bdfc4: 75 03                        	jne	0x11bdfc9 <.text+0x39>
 11bdfc6: 32 c0                        	xor	al, al
 11bdfc8: c3                           	ret
 11bdfc9: 8b 15 e4 24 a4 01            	mov	edx, dword ptr [0x1a424e4]
 11bdfcf: 33 c0                        	xor	eax, eax
 11bdfd1: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11bdfd4: 0f 94 c0                     	sete	al
 11bdfd7: c3                           	ret

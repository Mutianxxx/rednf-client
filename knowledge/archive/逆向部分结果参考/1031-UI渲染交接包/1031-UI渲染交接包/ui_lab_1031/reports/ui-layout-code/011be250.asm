
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be250 <.text>:
 11be250: 8a 41 0f                     	mov	al, byte ptr [ecx + 0xf]
 11be253: c3                           	ret
 11be254: cc                           	int3
 11be255: cc                           	int3
 11be256: cc                           	int3
 11be257: cc                           	int3
 11be258: cc                           	int3
 11be259: cc                           	int3
 11be25a: cc                           	int3
 11be25b: cc                           	int3
 11be25c: cc                           	int3
 11be25d: cc                           	int3
 11be25e: cc                           	int3
 11be25f: cc                           	int3
 11be260: 8b 49 34                     	mov	ecx, dword ptr [ecx + 0x34]
 11be263: 33 c0                        	xor	eax, eax
 11be265: 3b 0d 04 25 a4 01            	cmp	ecx, dword ptr [0x1a42504]
 11be26b: 0f 94 c0                     	sete	al
 11be26e: c3                           	ret
 11be26f: cc                           	int3
 11be270: 8b 49 34                     	mov	ecx, dword ptr [ecx + 0x34]
 11be273: 33 c0                        	xor	eax, eax
 11be275: 3b 0d f4 24 a4 01            	cmp	ecx, dword ptr [0x1a424f4]
 11be27b: 0f 94 c0                     	sete	al
 11be27e: c3                           	ret
 11be27f: cc                           	int3
 11be280: 33 c0                        	xor	eax, eax
 11be282: 83 3d f4 24 a4 01 ff         	cmp	dword ptr [0x1a424f4], -0x1
 11be289: 0f 94 c0                     	sete	al
 11be28c: c3                           	ret
 11be28d: cc                           	int3
 11be28e: cc                           	int3
 11be28f: cc                           	int3
 11be290: 8b 15 0c 25 a4 01            	mov	edx, dword ptr [0x1a4250c]
 11be296: 33 c0                        	xor	eax, eax
 11be298: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be29b: 0f 94 c0                     	sete	al
 11be29e: c3                           	ret
 11be29f: cc                           	int3

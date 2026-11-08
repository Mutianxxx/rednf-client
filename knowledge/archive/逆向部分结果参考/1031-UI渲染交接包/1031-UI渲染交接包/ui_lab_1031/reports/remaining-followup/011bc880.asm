
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bc880 <.text>:
 11bc880: 55                           	push	ebp
 11bc881: 8b ec                        	mov	ebp, esp
 11bc883: 6a ff                        	push	-0x1
 11bc885: 68 ce 7b 4c 01               	push	0x14c7bce
 11bc88a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11bc890: 50                           	push	eax
 11bc891: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11bc896: 33 c5                        	xor	eax, ebp
 11bc898: 50                           	push	eax
 11bc899: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11bc89c: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11bc8a2: b8 01 00 00 00               	mov	eax, 0x1
 11bc8a7: 84 05 dc 64 b5 01            	test	byte ptr [0x1b564dc], al
 11bc8ad: 75 2c                        	jne	0x11bc8db <.text+0x5b>
 11bc8af: 09 05 dc 64 b5 01            	or	dword ptr [0x1b564dc], eax
 11bc8b5: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11bc8b8: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11bc8bb: 50                           	push	eax
 11bc8bc: 51                           	push	ecx
 11bc8bd: b9 b8 63 b5 01               	mov	ecx, 0x1b563b8
 11bc8c2: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11bc8c9: e8 c2 f9 ff ff               	call	0x11bc290
 11bc8ce: 68 60 2d 55 01               	push	0x1552d60
 11bc8d3: e8 32 aa 21 00               	call	0x13d730a <.text+0x21aa8a>
 11bc8d8: 83 c4 04                     	add	esp, 0x4
 11bc8db: b8 b8 63 b5 01               	mov	eax, 0x1b563b8
 11bc8e0: a3 ac 63 b5 01               	mov	dword ptr [0x1b563ac], eax
 11bc8e5: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11bc8e8: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11bc8ef: 59                           	pop	ecx
 11bc8f0: 8b e5                        	mov	esp, ebp
 11bc8f2: 5d                           	pop	ebp
 11bc8f3: c3                           	ret

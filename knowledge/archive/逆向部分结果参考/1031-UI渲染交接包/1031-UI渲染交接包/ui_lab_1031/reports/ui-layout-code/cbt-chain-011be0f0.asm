
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be0f0 <.text>:
 11be0f0: 80 79 0d 00                  	cmp	byte ptr [ecx + 0xd], 0x0
 11be0f4: 75 03                        	jne	0x11be0f9 <.text+0x9>
 11be0f6: 32 c0                        	xor	al, al
 11be0f8: c3                           	ret
 11be0f9: a1 f0 24 a4 01               	mov	eax, dword ptr [0x1a424f0]
 11be0fe: 3b 41 34                     	cmp	eax, dword ptr [ecx + 0x34]
 11be101: 75 0b                        	jne	0x11be10e <.text+0x1e>
 11be103: e8 18 9d 00 00               	call	0x11c7e20 <.text+0x9d30>
 11be108: 83 f8 01                     	cmp	eax, 0x1
 11be10b: 75 01                        	jne	0x11be10e <.text+0x1e>
 11be10d: c3                           	ret
 11be10e: 33 c0                        	xor	eax, eax
 11be110: c3                           	ret

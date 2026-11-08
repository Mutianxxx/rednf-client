
<stdin>:	file format elf32-i386

Disassembly of section .text:

011445e3 <.text>:
 11445e3: 68 d0 00 00 00               	push	0xd0
 11445e8: e8 2d 25 29 00               	call	0x13d6b1a <.text+0x292537>
 11445ed: 83 c4 04                     	add	esp, 0x4
 11445f0: 89 85 b8 fa ff ff            	mov	dword ptr [ebp - 0x548], eax
 11445f6: c7 45 fc 10 00 00 00         	mov	dword ptr [ebp - 0x4], 0x10
 11445fd: 85 c0                        	test	eax, eax
 11445ff: 74 0b                        	je	0x114460c <.text+0x29>
 1144601: 8b c8                        	mov	ecx, eax
 1144603: e8 b8 2f ff ff               	call	0x11375c0
 1144608: 8b f0                        	mov	esi, eax
 114460a: eb 02                        	jmp	0x114460e <.text+0x2b>
 114460c: 33 f6                        	xor	esi, esi
 114460e: 57                           	push	edi
 114460f: 56                           	push	esi
 1144610: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1144617: e8 a4 80 1a 00               	call	0x12ec6c0 <.text+0x1a80dd>
 114461c: 83 c4 08                     	add	esp, 0x8
 114461f: 84 c0                        	test	al, al
 1144621: 0f 85 13 fb ff ff            	jne	0x114413a
 1144627: 85 f6                        	test	esi, esi
 1144629: 0f 84 78 08 00 00            	je	0x1144ea7 <.text+0x8c4>
 114462f: 8b ce                        	mov	ecx, esi
 1144631: e8 5a 32 ff ff               	call	0x1137890
 1144636: e9 63 08 00 00               	jmp	0x1144e9e <.text+0x8bb>

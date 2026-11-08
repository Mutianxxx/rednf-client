
<stdin>:	file format elf32-i386

Disassembly of section .text:

01144e52 <.text>:
 1144e52: 6a 60                        	push	0x60
 1144e54: e8 c1 1c 29 00               	call	0x13d6b1a <.text+0x291cc8>
 1144e59: 83 c4 04                     	add	esp, 0x4
 1144e5c: 89 85 b8 fa ff ff            	mov	dword ptr [ebp - 0x548], eax
 1144e62: c7 45 fc 1d 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1d
 1144e69: 85 c0                        	test	eax, eax
 1144e6b: 74 0b                        	je	0x1144e78 <.text+0x26>
 1144e6d: 8b c8                        	mov	ecx, eax
 1144e6f: e8 9c e0 ff ff               	call	0x1142f10
 1144e74: 8b f0                        	mov	esi, eax
 1144e76: eb 02                        	jmp	0x1144e7a <.text+0x28>
 1144e78: 33 f6                        	xor	esi, esi
 1144e7a: 57                           	push	edi
 1144e7b: 56                           	push	esi
 1144e7c: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1144e83: e8 78 f9 1c 00               	call	0x1314800 <.text+0x1cf9ae>
 1144e88: 83 c4 08                     	add	esp, 0x8
 1144e8b: 84 c0                        	test	al, al
 1144e8d: 0f 85 a7 f2 ff ff            	jne	0x114413a
 1144e93: 85 f6                        	test	esi, esi
 1144e95: 74 10                        	je	0x1144ea7 <.text+0x55>
 1144e97: 8b ce                        	mov	ecx, esi
 1144e99: e8 d2 e1 ff ff               	call	0x1143070
 1144e9e: 56                           	push	esi
 1144e9f: e8 83 0c 29 00               	call	0x13d5b27 <.text+0x290cd5>
 1144ea4: 83 c4 04                     	add	esp, 0x4
 1144ea7: 33 c0                        	xor	eax, eax
 1144ea9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1144eac: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1144eb3: 59                           	pop	ecx
 1144eb4: 5f                           	pop	edi
 1144eb5: 5e                           	pop	esi
 1144eb6: 5b                           	pop	ebx
 1144eb7: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1144eba: 33 cd                        	xor	ecx, ebp
 1144ebc: e8 17 23 29 00               	call	0x13d71d8 <.text+0x292386>
 1144ec1: 8b e5                        	mov	esp, ebp
 1144ec3: 5d                           	pop	ebp
 1144ec4: c2                           	<unknown>

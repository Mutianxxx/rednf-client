
<stdin>:	file format elf32-i386

Disassembly of section .text:

011445c0 <.text>:
 11445c0: 8c 70 1d                     	<unknown>
 11445c3: 00 83 c4 08 84 c0            	add	byte ptr [ebx - 0x3f7bf73c], al
 11445c9: 0f 85 6b fb ff ff            	jne	0x114413a
 11445cf: 85 f6                        	test	esi, esi
 11445d1: 0f 84 d0 08 00 00            	je	0x1144ea7 <.text+0x8e7>
 11445d7: 8b ce                        	mov	ecx, esi
 11445d9: e8 62 cb ff ff               	call	0x1141140
 11445de: e9 bb 08 00 00               	jmp	0x1144e9e <.text+0x8de>
 11445e3: 68 d0 00 00 00               	push	0xd0
 11445e8: e8 2d 25 29 00               	call	0x13d6b1a <.text+0x29255a>
 11445ed: 83 c4 04                     	add	esp, 0x4
 11445f0: 89 85 b8 fa ff ff            	mov	dword ptr [ebp - 0x548], eax
 11445f6: c7 45 fc 10 00 00 00         	mov	dword ptr [ebp - 0x4], 0x10
 11445fd: 85 c0                        	test	eax, eax
 11445ff: 74 0b                        	je	0x114460c <.text+0x4c>
 1144601: 8b c8                        	mov	ecx, eax
 1144603: e8 b8 2f ff ff               	call	0x11375c0
 1144608: 8b f0                        	mov	esi, eax
 114460a: eb 02                        	jmp	0x114460e <.text+0x4e>
 114460c: 33 f6                        	xor	esi, esi
 114460e: 57                           	push	edi
 114460f: 56                           	push	esi
 1144610: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1144617: e8 a4 80 1a 00               	call	0x12ec6c0 <.text+0x1a8100>
 114461c: 83 c4 08                     	add	esp, 0x8
 114461f: 84 c0                        	test	al, al
 1144621: 0f 85 13 fb ff ff            	jne	0x114413a
 1144627: 85 f6                        	test	esi, esi
 1144629: 0f 84 78 08 00 00            	je	0x1144ea7 <.text+0x8e7>
 114462f: 8b ce                        	mov	ecx, esi
 1144631: e8 5a 32 ff ff               	call	0x1137890
 1144636: e9 63 08 00 00               	jmp	0x1144e9e <.text+0x8de>
 114463b: 68 54 03 00 00               	push	0x354
 1144640: e8 d5 24 29 00               	call	0x13d6b1a <.text+0x29255a>
 1144645: 83 c4 04                     	add	esp, 0x4
 1144648: 89 85 b8 fa ff ff            	mov	dword ptr [ebp - 0x548], eax
 114464e: c7 45 fc 11 00 00 00         	mov	dword ptr [ebp - 0x4], 0x11
 1144655: 85 c0                        	test	eax, eax
 1144657: 74 0b                        	je	0x1144664 <.text+0xa4>
 1144659: 8b c8                        	mov	ecx, eax
 114465b: e8 30 8f ff ff               	call	0x113d590
 1144660: 8b f0                        	mov	esi, eax
 1144662: eb 02                        	jmp	0x1144666 <.text+0xa6>
 1144664: 33 f6                        	xor	esi, esi
 1144666: 57                           	push	edi
 1144667: 56                           	push	esi
 1144668: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 114466f: e8 7c 48 15 00               	call	0x1298ef0 <.text+0x154930>
 1144674: 83 c4 08                     	add	esp, 0x8
 1144677: 84 c0                        	test	al, al
 1144679: 0f 84 0c 04 00 00            	je	0x1144a8b <.text+0x4cb>
 114467f: 8d 8d 44 fa ff ff            	lea	ecx, [ebp - 0x5bc]
 1144685: e8 a6 1d ff ff               	call	0x1136430
 114468a: 8d 95 bc fa ff ff            	lea	edx, [ebp - 0x544]
 1144690: 8d 46 08                     	lea	eax, [esi + 0x8]
 1144693: 52                           	push	edx
 1144694: 50                           	push	eax
 1144695: 8b ce                        	mov	ecx, esi
 1144697: c7 45 fc 12 00 00 00         	mov	dword ptr [ebp - 0x4], 0x12
 114469e: e8 3d c7 05 00               	call	0x11a0de0 <.text+0x5c820>
 11446a3: 8b 85 bc fa ff ff            	mov	eax, dword ptr [ebp - 0x544]
 11446a9: 8d 4e 24                     	lea	ecx, [esi + 0x24]
 11446ac: 8d 95 bc fa ff ff            	lea	edx, [ebp - 0x544]
 11446b2: 89 85 44 fa ff ff            	mov	dword ptr [ebp - 0x5bc], eax
 11446b8: 52                           	push	edx
 11446b9: 8d 41 08                     	lea	eax, [ecx + 0x8]
 11446bc: 50                           	push	eax
 11446bd: e8 1e c7 05 00               	call	0x11a0de0 <.text+0x5c820>
 11446c2: 8b 8d bc fa ff ff            	mov	ecx, dword ptr [ebp - 0x544]
 11446c8: 89 8d 48 fa ff ff            	mov	dword ptr [ebp - 0x5b8], ecx
 11446ce: 8d 4e 30                     	lea	ecx, [esi + 0x30]
 11446d1: 8d 95 bc fa ff ff            	lea	edx, [ebp - 0x544]
 11446d7: 52                           	push	edx
 11446d8: 8d 41 08                     	lea	eax, [ecx + 0x8]
 11446db: 50                           	push	eax
 11446dc: e8                           	<unknown>
 11446dd: ff c6                        	inc	esi
 11446df: 05                           	<unknown>

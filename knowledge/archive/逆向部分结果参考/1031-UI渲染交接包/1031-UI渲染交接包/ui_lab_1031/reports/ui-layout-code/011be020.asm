
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be020 <.text>:
 11be020: 80 79 0d 00                  	cmp	byte ptr [ecx + 0xd], 0x0
 11be024: 75 03                        	jne	0x11be029 <.text+0x9>
 11be026: 32 c0                        	xor	al, al
 11be028: c3                           	ret
 11be029: 8b 15 f0 24 a4 01            	mov	edx, dword ptr [0x1a424f0]
 11be02f: 33 c0                        	xor	eax, eax
 11be031: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be034: 0f 94 c0                     	sete	al
 11be037: c3                           	ret
 11be038: cc                           	int3
 11be039: cc                           	int3
 11be03a: cc                           	int3
 11be03b: cc                           	int3
 11be03c: cc                           	int3
 11be03d: cc                           	int3
 11be03e: cc                           	int3
 11be03f: cc                           	int3
 11be040: 8a 41 0d                     	mov	al, byte ptr [ecx + 0xd]
 11be043: 84 c0                        	test	al, al
 11be045: 74 37                        	je	0x11be07e <.text+0x5e>
 11be047: 8b 15 f0 24 a4 01            	mov	edx, dword ptr [0x1a424f0]
 11be04d: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be050: 0f 94 c2                     	sete	dl
 11be053: 84 d2                        	test	dl, dl
 11be055: 75 2a                        	jne	0x11be081 <.text+0x61>
 11be057: 84 c0                        	test	al, al
 11be059: 74 23                        	je	0x11be07e <.text+0x5e>
 11be05b: 8b 15 e4 24 a4 01            	mov	edx, dword ptr [0x1a424e4]
 11be061: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be064: 0f 94 c2                     	sete	dl
 11be067: 84 d2                        	test	dl, dl
 11be069: 75 16                        	jne	0x11be081 <.text+0x61>
 11be06b: 84 c0                        	test	al, al
 11be06d: 74 0f                        	je	0x11be07e <.text+0x5e>
 11be06f: a1 ec 24 a4 01               	mov	eax, dword ptr [0x1a424ec]
 11be074: 3b 41 34                     	cmp	eax, dword ptr [ecx + 0x34]
 11be077: 0f 94 c0                     	sete	al
 11be07a: 84 c0                        	test	al, al
 11be07c: 75 03                        	jne	0x11be081 <.text+0x61>
 11be07e: 33 c0                        	xor	eax, eax
 11be080: c3                           	ret
 11be081: b8 01 00 00 00               	mov	eax, 0x1
 11be086: c3                           	ret
 11be087: cc                           	int3
 11be088: cc                           	int3
 11be089: cc                           	int3
 11be08a: cc                           	int3
 11be08b: cc                           	int3
 11be08c: cc                           	int3
 11be08d: cc                           	int3
 11be08e: cc                           	int3
 11be08f: cc                           	int3
 11be090: 56                           	push	esi
 11be091: 57                           	push	edi
 11be092: 8b f1                        	mov	esi, ecx
 11be094: e8 27 9d 00 00               	call	0x11c7dc0 <.text+0x9da0>
 11be099: 8b f8                        	mov	edi, eax
 11be09b: e8 30 9d 00 00               	call	0x11c7dd0 <.text+0x9db0>
 11be0a0: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11be0a3: 3b f9                        	cmp	edi, ecx
 11be0a5: 7c 1e                        	jl	0x11be0c5 <.text+0xa5>
 11be0a7: 8b 56 38                     	mov	edx, dword ptr [esi + 0x38]
 11be0aa: 03 d1                        	add	edx, ecx
 11be0ac: 3b fa                        	cmp	edi, edx
 11be0ae: 7f 15                        	jg	0x11be0c5 <.text+0xa5>
 11be0b0: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11be0b3: 3b c1                        	cmp	eax, ecx
 11be0b5: 7c 0e                        	jl	0x11be0c5 <.text+0xa5>
 11be0b7: 8b 56 3c                     	mov	edx, dword ptr [esi + 0x3c]
 11be0ba: 03 d1                        	add	edx, ecx
 11be0bc: 3b c2                        	cmp	eax, edx
 11be0be: 7f 05                        	jg	0x11be0c5 <.text+0xa5>
 11be0c0: 5f                           	pop	edi
 11be0c1: b0 01                        	mov	al, 0x1
 11be0c3: 5e                           	pop	esi
 11be0c4: c3                           	ret
 11be0c5: 5f                           	pop	edi
 11be0c6: 32 c0                        	xor	al, al
 11be0c8: 5e                           	pop	esi
 11be0c9: c3                           	ret
 11be0ca: cc                           	int3
 11be0cb: cc                           	int3
 11be0cc: cc                           	int3
 11be0cd: cc                           	int3
 11be0ce: cc                           	int3
 11be0cf: cc                           	int3

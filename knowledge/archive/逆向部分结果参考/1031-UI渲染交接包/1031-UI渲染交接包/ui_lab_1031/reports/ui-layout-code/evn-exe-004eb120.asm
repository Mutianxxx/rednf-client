
<stdin>:	file format elf32-i386

Disassembly of section .text:

004eb120 <.text>:
  4eb120: 55                           	push	ebp
  4eb121: 8b ec                        	mov	ebp, esp
  4eb123: 6a ff                        	push	-0x1
  4eb125: 68 9c 35 41 01               	push	0x141359c
  4eb12a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4eb130: 50                           	push	eax
  4eb131: 81 ec d0 00 00 00            	sub	esp, 0xd0
  4eb137: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4eb13c: 33 c5                        	xor	eax, ebp
  4eb13e: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4eb141: 53                           	push	ebx
  4eb142: 56                           	push	esi
  4eb143: 57                           	push	edi
  4eb144: 50                           	push	eax
  4eb145: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4eb148: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4eb14e: 68 68 79 57 01               	push	0x1577968
  4eb153: 89 4d 94                     	mov	dword ptr [ebp - 0x6c], ecx
  4eb156: e8 95 4d cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb15b: 83 c4 04                     	add	esp, 0x4
  4eb15e: 50                           	push	eax
  4eb15f: 68 78 21 56 01               	push	0x1562178
  4eb164: e8 87 4d cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb169: 83 c4 04                     	add	esp, 0x4
  4eb16c: 50                           	push	eax
  4eb16d: e8 ae 84 d3 00               	call	0x1223620 <.text+0xd38500>
  4eb172: 83 c4 08                     	add	esp, 0x8
  4eb175: 84 c0                        	test	al, al
  4eb177: 0f 84 72 06 00 00            	je	0x4eb7ef <.text+0x6cf>
  4eb17d: 33 f6                        	xor	esi, esi
  4eb17f: 6a 08                        	push	0x8
  4eb181: 89 75 b0                     	mov	dword ptr [ebp - 0x50], esi
  4eb184: e8 91 b9 ee 00               	call	0x13d6b1a <.text+0xeeb9fa>
  4eb189: 83 c4 04                     	add	esp, 0x4
  4eb18c: 3b c6                        	cmp	eax, esi
  4eb18e: 0f 84 ac 07 00 00            	je	0x4eb940 <.text+0x820>
  4eb194: 89 45 b0                     	mov	dword ptr [ebp - 0x50], eax
  4eb197: 33 c9                        	xor	ecx, ecx
  4eb199: 89 08                        	mov	dword ptr [eax], ecx
  4eb19b: 33 d2                        	xor	edx, edx
  4eb19d: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
  4eb1a0: 8b 4d b0                     	mov	ecx, dword ptr [ebp - 0x50]
  4eb1a3: 8d 45 b0                     	lea	eax, [ebp - 0x50]
  4eb1a6: 89 01                        	mov	dword ptr [ecx], eax
  4eb1a8: bf 07 00 00 00               	mov	edi, 0x7
  4eb1ad: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
  4eb1b0: 89 75 c4                     	mov	dword ptr [ebp - 0x3c], esi
  4eb1b3: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
  4eb1b7: 6a 08                        	push	0x8
  4eb1b9: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
  4eb1bc: 89 75 d0                     	mov	dword ptr [ebp - 0x30], esi
  4eb1bf: e8 56 b9 ee 00               	call	0x13d6b1a <.text+0xeeb9fa>
  4eb1c4: 83 c4 04                     	add	esp, 0x4
  4eb1c7: 3b c6                        	cmp	eax, esi
  4eb1c9: 0f 84 44 07 00 00            	je	0x4eb913 <.text+0x7f3>
  4eb1cf: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
  4eb1d2: 33 c9                        	xor	ecx, ecx
  4eb1d4: 89 08                        	mov	dword ptr [eax], ecx
  4eb1d6: 33 d2                        	xor	edx, edx
  4eb1d8: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
  4eb1db: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
  4eb1de: 8d 45 d0                     	lea	eax, [ebp - 0x30]
  4eb1e1: 89 01                        	mov	dword ptr [ecx], eax
  4eb1e3: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
  4eb1e6: 89 75 e4                     	mov	dword ptr [ebp - 0x1c], esi
  4eb1e9: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
  4eb1ed: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb1f1: 8d 45 b0                     	lea	eax, [ebp - 0x50]
  4eb1f4: 6a 01                        	push	0x1
  4eb1f6: 50                           	push	eax
  4eb1f7: bb 02 00 00 00               	mov	ebx, 0x2
  4eb1fc: e8 0f a0 d3 00               	call	0x1225210 <.text+0xd3a0f0>
  4eb201: 83 c4 08                     	add	esp, 0x8
  4eb204: 84 c0                        	test	al, al
  4eb206: 0f 84 89 05 00 00            	je	0x4eb795 <.text+0x675>
  4eb20c: 8d 64 24 00                  	lea	esp, [esp]
  4eb210: f6 05 54 c7 a4 01 01         	test	byte ptr [0x1a4c754], 0x1
  4eb217: 0f 85 93 00 00 00            	jne	0x4eb2b0 <.text+0x190>
  4eb21d: 83 0d 54 c7 a4 01 01         	or	dword ptr [0x1a4c754], 0x1
  4eb224: 6a 08                        	push	0x8
  4eb226: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
  4eb229: 89 35 40 c7 a4 01            	mov	dword ptr [0x1a4c740], esi
  4eb22f: e8 e6 b8 ee 00               	call	0x13d6b1a <.text+0xeeb9fa>
  4eb234: 83 c4 04                     	add	esp, 0x4
  4eb237: 3b c6                        	cmp	eax, esi
  4eb239: 0f 84 fb 05 00 00            	je	0x4eb83a <.text+0x71a>
  4eb23f: a3 40 c7 a4 01               	mov	dword ptr [0x1a4c740], eax
  4eb244: 33 c9                        	xor	ecx, ecx
  4eb246: 33 d2                        	xor	edx, edx
  4eb248: 89 08                        	mov	dword ptr [eax], ecx
  4eb24a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
  4eb24d: 8b 0d 40 c7 a4 01            	mov	ecx, dword ptr [0x1a4c740]
  4eb253: c7 01 40 c7 a4 01            	mov	dword ptr [ecx], 0x1a4c740
  4eb259: 6a 18                        	push	0x18
  4eb25b: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
  4eb25f: 89 35 4c c7 a4 01            	mov	dword ptr [0x1a4c74c], esi
  4eb265: e8 b0 b8 ee 00               	call	0x13d6b1a <.text+0xeeb9fa>
  4eb26a: 83 c4 04                     	add	esp, 0x4
  4eb26d: 3b c6                        	cmp	eax, esi
  4eb26f: 0f 84 98 05 00 00            	je	0x4eb80d <.text+0x6ed>
  4eb275: a3 48 c7 a4 01               	mov	dword ptr [0x1a4c748], eax
  4eb27a: 89 00                        	mov	dword ptr [eax], eax
  4eb27c: a1 48 c7 a4 01               	mov	eax, dword ptr [0x1a4c748]
  4eb281: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
  4eb284: a1 48 c7 a4 01               	mov	eax, dword ptr [0x1a4c748]
  4eb289: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
  4eb28c: 8b 15 48 c7 a4 01            	mov	edx, dword ptr [0x1a4c748]
  4eb292: c6 42 14 01                  	mov	byte ptr [edx + 0x14], 0x1
  4eb296: a1 48 c7 a4 01               	mov	eax, dword ptr [0x1a4c748]
  4eb29b: 68 40 4a 54 01               	push	0x1544a40
  4eb2a0: c6 40 15 01                  	mov	byte ptr [eax + 0x15], 0x1
  4eb2a4: e8 61 c0 ee 00               	call	0x13d730a <.text+0xeec1ea>
  4eb2a9: 83 c4 04                     	add	esp, 0x4
  4eb2ac: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb2b0: 84 1d 54 c7 a4 01            	test	byte ptr [0x1a4c754], bl
  4eb2b6: 75 25                        	jne	0x4eb2dd <.text+0x1bd>
  4eb2b8: 09 1d 54 c7 a4 01            	or	dword ptr [0x1a4c754], ebx
  4eb2be: b9 3c c7 a4 01               	mov	ecx, 0x1a4c73c
  4eb2c3: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
  4eb2c7: e8 84 9e cb 00               	call	0x11a5150 <.text+0xcba030>
  4eb2cc: 68 30 4a 54 01               	push	0x1544a30
  4eb2d1: e8 34 c0 ee 00               	call	0x13d730a <.text+0xeec1ea>
  4eb2d6: 83 c4 04                     	add	esp, 0x4
  4eb2d9: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb2dd: 80 3d 38 c7 a4 01 00         	cmp	byte ptr [0x1a4c738], 0x0
  4eb2e4: 0f 84 cd 00 00 00            	je	0x4eb3b7 <.text+0x297>
  4eb2ea: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
  4eb2ee: 72 08                        	jb	0x4eb2f8 <.text+0x1d8>
  4eb2f0: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
  4eb2f3: 89 4d a8                     	mov	dword ptr [ebp - 0x58], ecx
  4eb2f6: eb 06                        	jmp	0x4eb2fe <.text+0x1de>
  4eb2f8: 8d 55 b4                     	lea	edx, [ebp - 0x4c]
  4eb2fb: 89 55 a8                     	mov	dword ptr [ebp - 0x58], edx
  4eb2fe: 8d 45 a8                     	lea	eax, [ebp - 0x58]
  4eb301: 50                           	push	eax
  4eb302: 8d 8d 44 ff ff ff            	lea	ecx, [ebp - 0xbc]
  4eb308: 51                           	push	ecx
  4eb309: b9 40 c7 a4 01               	mov	ecx, 0x1a4c740
  4eb30e: e8 fd d3 f6 ff               	call	0x458710
  4eb313: 8b 08                        	mov	ecx, dword ptr [eax]
  4eb315: 3b ce                        	cmp	ecx, esi
  4eb317: 74 08                        	je	0x4eb321 <.text+0x201>
  4eb319: 8b 09                        	mov	ecx, dword ptr [ecx]
  4eb31b: 3b ce                        	cmp	ecx, esi
  4eb31d: 74 02                        	je	0x4eb321 <.text+0x201>
  4eb31f: 8b 31                        	mov	esi, dword ptr [ecx]
  4eb321: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
  4eb324: 8d 95 5c ff ff ff            	lea	edx, [ebp - 0xa4]
  4eb32a: 52                           	push	edx
  4eb32b: b9 40 c7 a4 01               	mov	ecx, 0x1a4c740
  4eb330: e8 0b 90 2d 00               	call	0x7c4340 <.text+0x2d9220>
  4eb335: 85 f6                        	test	esi, esi
  4eb337: 0f 84 21 05 00 00            	je	0x4eb85e <.text+0x73e>
  4eb33d: 8b 36                        	mov	esi, dword ptr [esi]
  4eb33f: 85 f6                        	test	esi, esi
  4eb341: 0f 84 17 05 00 00            	je	0x4eb85e <.text+0x73e>
  4eb347: 8b 08                        	mov	ecx, dword ptr [eax]
  4eb349: 85 c9                        	test	ecx, ecx
  4eb34b: 74 02                        	je	0x4eb34f <.text+0x22f>
  4eb34d: 8b 09                        	mov	ecx, dword ptr [ecx]
  4eb34f: 3b f1                        	cmp	esi, ecx
  4eb351: 0f 85 07 05 00 00            	jne	0x4eb85e <.text+0x73e>
  4eb357: 3b 78 08                     	cmp	edi, dword ptr [eax + 0x8]
  4eb35a: 0f 94 c0                     	sete	al
  4eb35d: 84 c0                        	test	al, al
  4eb35f: 0f 94 c0                     	sete	al
  4eb362: 84 c0                        	test	al, al
  4eb364: 0f 84 f9 03 00 00            	je	0x4eb763 <.text+0x643>
  4eb36a: 8b 7f 10                     	mov	edi, dword ptr [edi + 0x10]
  4eb36d: 85 ff                        	test	edi, edi
  4eb36f: 74 0c                        	je	0x4eb37d <.text+0x25d>
  4eb371: 81 ff d7 01 00 00            	cmp	edi, 0x1d7
  4eb377: 0f 85 e6 03 00 00            	jne	0x4eb763 <.text+0x643>
  4eb37d: 80 3d 38 c7 a4 01 00         	cmp	byte ptr [0x1a4c738], 0x0
  4eb384: 75 53                        	jne	0x4eb3d9 <.text+0x2b9>
  4eb386: 68 4c 79 57 01               	push	0x157794c
  4eb38b: e8 60 4b cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb390: 83 c4 04                     	add	esp, 0x4
  4eb393: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
  4eb396: 8d 45 88                     	lea	eax, [ebp - 0x78]
  4eb399: 50                           	push	eax
  4eb39a: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
  4eb3a0: 51                           	push	ecx
  4eb3a1: b9 40 c7 a4 01               	mov	ecx, 0x1a4c740
  4eb3a6: c7 45 8c d7 01 00 00         	mov	dword ptr [ebp - 0x74], 0x1d7
  4eb3ad: e8 1e d8 f6 ff               	call	0x458bd0
  4eb3b2: e9 ac 03 00 00               	jmp	0x4eb763 <.text+0x643>
  4eb3b7: b9 3c c7 a4 01               	mov	ecx, 0x1a4c73c
  4eb3bc: e8 ff 97 cb 00               	call	0x11a4bc0 <.text+0xcb9aa0>
  4eb3c1: 80 3d 38 c7 a4 01 00         	cmp	byte ptr [0x1a4c738], 0x0
  4eb3c8: 74 bc                        	je	0x4eb386 <.text+0x266>
  4eb3ca: b9 3c c7 a4 01               	mov	ecx, 0x1a4c73c
  4eb3cf: e8 1c 98 cb 00               	call	0x11a4bf0 <.text+0xcb9ad0>
  4eb3d4: e9 37 fe ff ff               	jmp	0x4eb210 <.text+0xf0>
  4eb3d9: 6a 40                        	push	0x40
  4eb3db: e8 3a b7 ee 00               	call	0x13d6b1a <.text+0xeeb9fa>
  4eb3e0: 8b f8                        	mov	edi, eax
  4eb3e2: 83 c4 04                     	add	esp, 0x4
  4eb3e5: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
  4eb3e8: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
  4eb3ec: 85 ff                        	test	edi, edi
  4eb3ee: 74 5a                        	je	0x4eb44a <.text+0x32a>
  4eb3f0: 8d 55 af                     	lea	edx, [ebp - 0x51]
  4eb3f3: 52                           	push	edx
  4eb3f4: 8d 45 af                     	lea	eax, [ebp - 0x51]
  4eb3f7: 50                           	push	eax
  4eb3f8: 8d 4f 08                     	lea	ecx, [edi + 0x8]
  4eb3fb: e8 80 d3 ff ff               	call	0x4e8780
  4eb400: 8d 4f 10                     	lea	ecx, [edi + 0x10]
  4eb403: c6 45 fc 06                  	mov	byte ptr [ebp - 0x4], 0x6
  4eb407: c7 07 ff ff ff ff            	mov	dword ptr [edi], 0xffffffff
  4eb40d: c7 47 04 00 00 00 00         	mov	dword ptr [edi + 0x4], 0x0
  4eb414: e8 17 d1 ff ff               	call	0x4e8530
  4eb419: 8d 8d 50 ff ff ff            	lea	ecx, [ebp - 0xb0]
  4eb41f: 51                           	push	ecx
  4eb420: 8d 4f 08                     	lea	ecx, [edi + 0x8]
  4eb423: e8 68 43 2c 00               	call	0x7af790 <.text+0x2c4670>
  4eb428: 50                           	push	eax
  4eb429: 6a 10                        	push	0x10
  4eb42b: 8d 4f 20                     	lea	ecx, [edi + 0x20]
  4eb42e: e8 7d e0 12 00               	call	0x6194b0 <.text+0x12e390>
  4eb433: c7 47 34 07 00 00 00         	mov	dword ptr [edi + 0x34], 0x7
  4eb43a: c7 47 38 08 00 00 00         	mov	dword ptr [edi + 0x38], 0x8
  4eb441: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
  4eb444: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb448: eb 0e                        	jmp	0x4eb458 <.text+0x338>
  4eb44a: 33 ff                        	xor	edi, edi
  4eb44c: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
  4eb44f: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb453: eb 03                        	jmp	0x4eb458 <.text+0x338>
  4eb455: 8b 7d a8                     	mov	edi, dword ptr [ebp - 0x58]
  4eb458: 8d 55 d0                     	lea	edx, [ebp - 0x30]
  4eb45b: 6a 01                        	push	0x1
  4eb45d: 52                           	push	edx
  4eb45e: e8 ad 9d d3 00               	call	0x1225210 <.text+0xd3a0f0>
  4eb463: 83 c4 08                     	add	esp, 0x8
  4eb466: 84 c0                        	test	al, al
  4eb468: 0f 84 f5 03 00 00            	je	0x4eb863 <.text+0x743>
  4eb46e: 68 38 79 57 01               	push	0x1577938
  4eb473: e8 78 4a cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb478: 8b c8                        	mov	ecx, eax
  4eb47a: 83 c4 04                     	add	esp, 0x4
  4eb47d: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb480: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb483: 83 c1 02                     	add	ecx, 0x2
  4eb486: 66 85 d2                     	test	dx, dx
  4eb489: 75 f5                        	jne	0x4eb480 <.text+0x360>
  4eb48b: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
  4eb48e: 2b ce                        	sub	ecx, esi
  4eb490: d1 f9                        	sar	ecx
  4eb492: 8b f7                        	mov	esi, edi
  4eb494: 3b f9                        	cmp	edi, ecx
  4eb496: 72 02                        	jb	0x4eb49a <.text+0x37a>
  4eb498: 8b f1                        	mov	esi, ecx
  4eb49a: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb49e: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb4a1: 73 03                        	jae	0x4eb4a6 <.text+0x386>
  4eb4a3: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4eb4a6: 85 f6                        	test	esi, esi
  4eb4a8: 74 21                        	je	0x4eb4cb <.text+0x3ab>
  4eb4aa: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
  4eb4b0: 66 8b 1a                     	mov	bx, word ptr [edx]
  4eb4b3: 66 3b 18                     	cmp	bx, word ptr [eax]
  4eb4b6: 75 0b                        	jne	0x4eb4c3 <.text+0x3a3>
  4eb4b8: 83 c2 02                     	add	edx, 0x2
  4eb4bb: 83 c0 02                     	add	eax, 0x2
  4eb4be: 4e                           	dec	esi
  4eb4bf: 75 ef                        	jne	0x4eb4b0 <.text+0x390>
  4eb4c1: eb 08                        	jmp	0x4eb4cb <.text+0x3ab>
  4eb4c3: 1b c0                        	sbb	eax, eax
  4eb4c5: 83 e0 fe                     	and	eax, -0x2
  4eb4c8: 40                           	inc	eax
  4eb4c9: 75 0b                        	jne	0x4eb4d6 <.text+0x3b6>
  4eb4cb: 3b f9                        	cmp	edi, ecx
  4eb4cd: 72 1c                        	jb	0x4eb4eb <.text+0x3cb>
  4eb4cf: 33 c0                        	xor	eax, eax
  4eb4d1: 3b f9                        	cmp	edi, ecx
  4eb4d3: 0f 95 c0                     	setne	al
  4eb4d6: 85 c0                        	test	eax, eax
  4eb4d8: 75 11                        	jne	0x4eb4eb <.text+0x3cb>
  4eb4da: 8b 7d a8                     	mov	edi, dword ptr [ebp - 0x58]
  4eb4dd: 57                           	push	edi
  4eb4de: e8 fd 81 d3 00               	call	0x12236e0 <.text+0xd385c0>
  4eb4e3: 83 c4 04                     	add	esp, 0x4
  4eb4e6: e9 6d ff ff ff               	jmp	0x4eb458 <.text+0x338>
  4eb4eb: 68 0c 79 57 01               	push	0x157790c
  4eb4f0: e8 fb 49 cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb4f5: 8b c8                        	mov	ecx, eax
  4eb4f7: 83 c4 04                     	add	esp, 0x4
  4eb4fa: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb4fd: 8d 49 00                     	lea	ecx, [ecx]
  4eb500: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb503: 83 c1 02                     	add	ecx, 0x2
  4eb506: 66 85 d2                     	test	dx, dx
  4eb509: 75 f5                        	jne	0x4eb500 <.text+0x3e0>
  4eb50b: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
  4eb50e: 2b ce                        	sub	ecx, esi
  4eb510: d1 f9                        	sar	ecx
  4eb512: 8b f7                        	mov	esi, edi
  4eb514: 3b f9                        	cmp	edi, ecx
  4eb516: 72 02                        	jb	0x4eb51a <.text+0x3fa>
  4eb518: 8b f1                        	mov	esi, ecx
  4eb51a: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb51e: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb521: 73 03                        	jae	0x4eb526 <.text+0x406>
  4eb523: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4eb526: 85 f6                        	test	esi, esi
  4eb528: 74 21                        	je	0x4eb54b <.text+0x42b>
  4eb52a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
  4eb530: 66 8b 1a                     	mov	bx, word ptr [edx]
  4eb533: 66 3b 18                     	cmp	bx, word ptr [eax]
  4eb536: 75 0b                        	jne	0x4eb543 <.text+0x423>
  4eb538: 83 c2 02                     	add	edx, 0x2
  4eb53b: 83 c0 02                     	add	eax, 0x2
  4eb53e: 4e                           	dec	esi
  4eb53f: 75 ef                        	jne	0x4eb530 <.text+0x410>
  4eb541: eb 08                        	jmp	0x4eb54b <.text+0x42b>
  4eb543: 1b c0                        	sbb	eax, eax
  4eb545: 83 e0 fe                     	and	eax, -0x2
  4eb548: 40                           	inc	eax
  4eb549: 75 0b                        	jne	0x4eb556 <.text+0x436>
  4eb54b: 3b f9                        	cmp	edi, ecx
  4eb54d: 72 1f                        	jb	0x4eb56e <.text+0x44e>
  4eb54f: 33 c0                        	xor	eax, eax
  4eb551: 3b f9                        	cmp	edi, ecx
  4eb553: 0f 95 c0                     	setne	al
  4eb556: 85 c0                        	test	eax, eax
  4eb558: 75 14                        	jne	0x4eb56e <.text+0x44e>
  4eb55a: 8b 7d a8                     	mov	edi, dword ptr [ebp - 0x58]
  4eb55d: 8d 47 04                     	lea	eax, [edi + 0x4]
  4eb560: 50                           	push	eax
  4eb561: e8 7a 81 d3 00               	call	0x12236e0 <.text+0xd385c0>
  4eb566: 83 c4 04                     	add	esp, 0x4
  4eb569: e9 ea fe ff ff               	jmp	0x4eb458 <.text+0x338>
  4eb56e: 68 f0 78 57 01               	push	0x15778f0
  4eb573: e8 78 49 cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb578: 8b c8                        	mov	ecx, eax
  4eb57a: 83 c4 04                     	add	esp, 0x4
  4eb57d: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb580: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb583: 83 c1 02                     	add	ecx, 0x2
  4eb586: 66 85 d2                     	test	dx, dx
  4eb589: 75 f5                        	jne	0x4eb580 <.text+0x460>
  4eb58b: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
  4eb58e: 2b ce                        	sub	ecx, esi
  4eb590: d1 f9                        	sar	ecx
  4eb592: 8b f7                        	mov	esi, edi
  4eb594: 3b f9                        	cmp	edi, ecx
  4eb596: 72 02                        	jb	0x4eb59a <.text+0x47a>
  4eb598: 8b f1                        	mov	esi, ecx
  4eb59a: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb59e: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb5a1: 73 03                        	jae	0x4eb5a6 <.text+0x486>
  4eb5a3: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4eb5a6: 85 f6                        	test	esi, esi
  4eb5a8: 74 21                        	je	0x4eb5cb <.text+0x4ab>
  4eb5aa: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
  4eb5b0: 66 8b 1a                     	mov	bx, word ptr [edx]
  4eb5b3: 66 3b 18                     	cmp	bx, word ptr [eax]
  4eb5b6: 75 0b                        	jne	0x4eb5c3 <.text+0x4a3>
  4eb5b8: 83 c2 02                     	add	edx, 0x2
  4eb5bb: 83 c0 02                     	add	eax, 0x2
  4eb5be: 4e                           	dec	esi
  4eb5bf: 75 ef                        	jne	0x4eb5b0 <.text+0x490>
  4eb5c1: eb 08                        	jmp	0x4eb5cb <.text+0x4ab>
  4eb5c3: 1b c0                        	sbb	eax, eax
  4eb5c5: 83 e0 fe                     	and	eax, -0x2
  4eb5c8: 40                           	inc	eax
  4eb5c9: 75 0f                        	jne	0x4eb5da <.text+0x4ba>
  4eb5cb: 3b f9                        	cmp	edi, ecx
  4eb5cd: 0f 82 f4 00 00 00            	jb	0x4eb6c7 <.text+0x5a7>
  4eb5d3: 33 c0                        	xor	eax, eax
  4eb5d5: 3b f9                        	cmp	edi, ecx
  4eb5d7: 0f 95 c0                     	setne	al
  4eb5da: 85 c0                        	test	eax, eax
  4eb5dc: 0f 85 e5 00 00 00            	jne	0x4eb6c7 <.text+0x5a7>
  4eb5e2: 8d 45 d0                     	lea	eax, [ebp - 0x30]
  4eb5e5: 50                           	push	eax
  4eb5e6: e8 65 9b d3 00               	call	0x1225150 <.text+0xd3a030>
  4eb5eb: 68 d8 78 57 01               	push	0x15778d8
  4eb5f0: c6 45 af 01                  	mov	byte ptr [ebp - 0x51], 0x1
  4eb5f4: e8 f7 48 cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb5f9: 8b c8                        	mov	ecx, eax
  4eb5fb: 83 c4 08                     	add	esp, 0x8
  4eb5fe: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb601: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb604: 83 c1 02                     	add	ecx, 0x2
  4eb607: 66 85 d2                     	test	dx, dx
  4eb60a: 75 f5                        	jne	0x4eb601 <.text+0x4e1>
  4eb60c: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
  4eb60f: 2b ce                        	sub	ecx, esi
  4eb611: d1 f9                        	sar	ecx
  4eb613: 8b f7                        	mov	esi, edi
  4eb615: 3b f9                        	cmp	edi, ecx
  4eb617: 72 02                        	jb	0x4eb61b <.text+0x4fb>
  4eb619: 8b f1                        	mov	esi, ecx
  4eb61b: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb61f: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb622: 73 03                        	jae	0x4eb627 <.text+0x507>
  4eb624: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4eb627: 85 f6                        	test	esi, esi
  4eb629: 74 20                        	je	0x4eb64b <.text+0x52b>
  4eb62b: eb 03                        	jmp	0x4eb630 <.text+0x510>
  4eb62d: 8d 49 00                     	lea	ecx, [ecx]
  4eb630: 66 8b 1a                     	mov	bx, word ptr [edx]
  4eb633: 66 3b 18                     	cmp	bx, word ptr [eax]
  4eb636: 75 0b                        	jne	0x4eb643 <.text+0x523>
  4eb638: 83 c2 02                     	add	edx, 0x2
  4eb63b: 83 c0 02                     	add	eax, 0x2
  4eb63e: 4e                           	dec	esi
  4eb63f: 75 ef                        	jne	0x4eb630 <.text+0x510>
  4eb641: eb 08                        	jmp	0x4eb64b <.text+0x52b>
  4eb643: 1b c0                        	sbb	eax, eax
  4eb645: 83 e0 fe                     	and	eax, -0x2
  4eb648: 40                           	inc	eax
  4eb649: 75 0b                        	jne	0x4eb656 <.text+0x536>
  4eb64b: 3b f9                        	cmp	edi, ecx
  4eb64d: 72 10                        	jb	0x4eb65f <.text+0x53f>
  4eb64f: 33 c0                        	xor	eax, eax
  4eb651: 3b f9                        	cmp	edi, ecx
  4eb653: 0f 95 c0                     	setne	al
  4eb656: 85 c0                        	test	eax, eax
  4eb658: 75 05                        	jne	0x4eb65f <.text+0x53f>
  4eb65a: 88 45 af                     	mov	byte ptr [ebp - 0x51], al
  4eb65d: eb 39                        	jmp	0x4eb698 <.text+0x578>
  4eb65f: 68 c4 78 57 01               	push	0x15778c4
  4eb664: e8 87 48 cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb669: 8b c8                        	mov	ecx, eax
  4eb66b: 83 c4 04                     	add	esp, 0x4
  4eb66e: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb671: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb674: 83 c1 02                     	add	ecx, 0x2
  4eb677: 66 85 d2                     	test	dx, dx
  4eb67a: 75 f5                        	jne	0x4eb671 <.text+0x551>
  4eb67c: 2b ce                        	sub	ecx, esi
  4eb67e: d1 f9                        	sar	ecx
  4eb680: 51                           	push	ecx
  4eb681: 50                           	push	eax
  4eb682: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
  4eb685: 50                           	push	eax
  4eb686: 6a 00                        	push	0x0
  4eb688: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
  4eb68b: e8 a0 65 f1 ff               	call	0x401c30
  4eb690: 85 c0                        	test	eax, eax
  4eb692: 75 04                        	jne	0x4eb698 <.text+0x578>
  4eb694: c6 45 af 02                  	mov	byte ptr [ebp - 0x51], 0x2
  4eb698: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
  4eb69b: 51                           	push	ecx
  4eb69c: e8 af 9a d3 00               	call	0x1225150 <.text+0xd3a030>
  4eb6a1: 8b 7d a8                     	mov	edi, dword ptr [ebp - 0x58]
  4eb6a4: 83 c4 04                     	add	esp, 0x4
  4eb6a7: 8d 55 af                     	lea	edx, [ebp - 0x51]
  4eb6aa: 52                           	push	edx
  4eb6ab: 8d 4f 08                     	lea	ecx, [edi + 0x8]
  4eb6ae: e8 bd f8 ff ff               	call	0x4eaf70
  4eb6b3: 6a ff                        	push	-0x1
  4eb6b5: 6a 00                        	push	0x0
  4eb6b7: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
  4eb6ba: 51                           	push	ecx
  4eb6bb: 8b c8                        	mov	ecx, eax
  4eb6bd: e8 6e 9c f1 ff               	call	0x405330
  4eb6c2: e9 91 fd ff ff               	jmp	0x4eb458 <.text+0x338>
  4eb6c7: 68 ac 78 57 01               	push	0x15778ac
  4eb6cc: e8 1f 48 cb 00               	call	0x119fef0 <.text+0xcb4dd0>
  4eb6d1: 8b c8                        	mov	ecx, eax
  4eb6d3: 83 c4 04                     	add	esp, 0x4
  4eb6d6: 8d 71 02                     	lea	esi, [ecx + 0x2]
  4eb6d9: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  4eb6e0: 66 8b 11                     	mov	dx, word ptr [ecx]
  4eb6e3: 83 c1 02                     	add	ecx, 0x2
  4eb6e6: 66 85 d2                     	test	dx, dx
  4eb6e9: 75 f5                        	jne	0x4eb6e0 <.text+0x5c0>
  4eb6eb: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
  4eb6ee: 2b ce                        	sub	ecx, esi
  4eb6f0: d1 f9                        	sar	ecx
  4eb6f2: 8b f7                        	mov	esi, edi
  4eb6f4: 3b f9                        	cmp	edi, ecx
  4eb6f6: 72 02                        	jb	0x4eb6fa <.text+0x5da>
  4eb6f8: 8b f1                        	mov	esi, ecx
  4eb6fa: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb6fe: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb701: 73 03                        	jae	0x4eb706 <.text+0x5e6>
  4eb703: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4eb706: 85 f6                        	test	esi, esi
  4eb708: 74 21                        	je	0x4eb72b <.text+0x60b>
  4eb70a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
  4eb710: 66 8b 1a                     	mov	bx, word ptr [edx]
  4eb713: 66 3b 18                     	cmp	bx, word ptr [eax]
  4eb716: 75 0b                        	jne	0x4eb723 <.text+0x603>
  4eb718: 83 c2 02                     	add	edx, 0x2
  4eb71b: 83 c0 02                     	add	eax, 0x2
  4eb71e: 4e                           	dec	esi
  4eb71f: 75 ef                        	jne	0x4eb710 <.text+0x5f0>
  4eb721: eb 08                        	jmp	0x4eb72b <.text+0x60b>
  4eb723: 1b c0                        	sbb	eax, eax
  4eb725: 83 e0 fe                     	and	eax, -0x2
  4eb728: 40                           	inc	eax
  4eb729: 75 0f                        	jne	0x4eb73a <.text+0x61a>
  4eb72b: 3b f9                        	cmp	edi, ecx
  4eb72d: 0f 82 22 fd ff ff            	jb	0x4eb455 <.text+0x335>
  4eb733: 33 c0                        	xor	eax, eax
  4eb735: 3b f9                        	cmp	edi, ecx
  4eb737: 0f 95 c0                     	setne	al
  4eb73a: 85 c0                        	test	eax, eax
  4eb73c: 0f 85 13 fd ff ff            	jne	0x4eb455 <.text+0x335>
  4eb742: 8b 45 a8                     	mov	eax, dword ptr [ebp - 0x58]
  4eb745: 8b 08                        	mov	ecx, dword ptr [eax]
  4eb747: 89 4d 80                     	mov	dword ptr [ebp - 0x80], ecx
  4eb74a: 8b 4d 94                     	mov	ecx, dword ptr [ebp - 0x6c]
  4eb74d: 8d 55 80                     	lea	edx, [ebp - 0x80]
  4eb750: 89 45 84                     	mov	dword ptr [ebp - 0x7c], eax
  4eb753: 52                           	push	edx
  4eb754: 8d 85 34 ff ff ff            	lea	eax, [ebp - 0xcc]
  4eb75a: 50                           	push	eax
  4eb75b: 83 c1 3c                     	add	ecx, 0x3c
  4eb75e: e8 1d d9 ff ff               	call	0x4e9080
  4eb763: 80 3d 38 c7 a4 01 00         	cmp	byte ptr [0x1a4c738], 0x0
  4eb76a: 75 1d                        	jne	0x4eb789 <.text+0x669>
  4eb76c: b9 3c c7 a4 01               	mov	ecx, 0x1a4c73c
  4eb771: e8 7a 94 cb 00               	call	0x11a4bf0 <.text+0xcb9ad0>
  4eb776: c6 05 38 c7 a4 01 01         	mov	byte ptr [0x1a4c738], 0x1
  4eb77d: bb 02 00 00 00               	mov	ebx, 0x2
  4eb782: 33 f6                        	xor	esi, esi
  4eb784: e9 87 fa ff ff               	jmp	0x4eb210 <.text+0xf0>
  4eb789: bf 07 00 00 00               	mov	edi, 0x7
  4eb78e: 33 f6                        	xor	esi, esi
  4eb790: e9 5c fa ff ff               	jmp	0x4eb1f1 <.text+0xd1>
  4eb795: bb 08 00 00 00               	mov	ebx, 0x8
  4eb79a: 39 5d e8                     	cmp	dword ptr [ebp - 0x18], ebx
  4eb79d: 72 0c                        	jb	0x4eb7ab <.text+0x68b>
  4eb79f: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
  4eb7a2: 51                           	push	ecx
  4eb7a3: e8 7f a3 ee 00               	call	0x13d5b27 <.text+0xeeaa07>
  4eb7a8: 83 c4 04                     	add	esp, 0x4
  4eb7ab: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
  4eb7ae: 33 d2                        	xor	edx, edx
  4eb7b0: 50                           	push	eax
  4eb7b1: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
  4eb7b4: 89 75 e4                     	mov	dword ptr [ebp - 0x1c], esi
  4eb7b7: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
  4eb7bb: e8 67 a3 ee 00               	call	0x13d5b27 <.text+0xeeaa07>
  4eb7c0: 83 c4 04                     	add	esp, 0x4
  4eb7c3: 89 75 d0                     	mov	dword ptr [ebp - 0x30], esi
  4eb7c6: 39 5d c8                     	cmp	dword ptr [ebp - 0x38], ebx
  4eb7c9: 72 0c                        	jb	0x4eb7d7 <.text+0x6b7>
  4eb7cb: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
  4eb7ce: 51                           	push	ecx
  4eb7cf: e8 53 a3 ee 00               	call	0x13d5b27 <.text+0xeeaa07>
  4eb7d4: 83 c4 04                     	add	esp, 0x4
  4eb7d7: 8b 45 b0                     	mov	eax, dword ptr [ebp - 0x50]
  4eb7da: 33 d2                        	xor	edx, edx
  4eb7dc: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
  4eb7df: 89 75 c4                     	mov	dword ptr [ebp - 0x3c], esi
  4eb7e2: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
  4eb7e6: 50                           	push	eax
  4eb7e7: e8 3b a3 ee 00               	call	0x13d5b27 <.text+0xeeaa07>
  4eb7ec: 83 c4 04                     	add	esp, 0x4
  4eb7ef: 32 c0                        	xor	al, al
  4eb7f1: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4eb7f4: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4eb7fb: 59                           	pop	ecx
  4eb7fc: 5f                           	pop	edi
  4eb7fd: 5e                           	pop	esi
  4eb7fe: 5b                           	pop	ebx
  4eb7ff: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4eb802: 33 cd                        	xor	ecx, ebp
  4eb804: e8 cf b9 ee 00               	call	0x13d71d8 <.text+0xeec0b8>
  4eb809: 8b e5                        	mov	esp, ebp
  4eb80b: 5d                           	pop	ebp
  4eb80c: c3                           	ret

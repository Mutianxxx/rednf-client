
<stdin>:	file format elf32-i386

Disassembly of section .text:

004eb080 <.text>:
  4eb080: 45                           	inc	ebp
  4eb081: b4 e8                        	mov	ah, -0x18
  4eb083: a0 aa ee 00 83               	mov	al, byte ptr [0x8300eeaa]
  4eb088: c4 04 83                     	les	eax, [ebx + 4*eax]
  4eb08b: 7d e8                        	jge	0x4eb075
  4eb08d: 08 89 5d b0 72 0c            	or	byte ptr [ecx + 0xc72b05d], cl
  4eb093: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb096: 52                           	push	edx
  4eb097: e8 8b aa ee 00               	call	0x13d5b27 <.text+0xeeaaa7>
  4eb09c: 83 c4 04                     	add	esp, 0x4
  4eb09f: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
  4eb0a2: 33 c0                        	xor	eax, eax
  4eb0a4: 51                           	push	ecx
  4eb0a5: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
  4eb0a8: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  4eb0ab: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
  4eb0af: e8 73 aa ee 00               	call	0x13d5b27 <.text+0xeeaaa7>
  4eb0b4: 8b 4d a4                     	mov	ecx, dword ptr [ebp - 0x5c]
  4eb0b7: 83 c4 04                     	add	esp, 0x4
  4eb0ba: 85 ff                        	test	edi, edi
  4eb0bc: 74 0f                        	je	0x4eb0cd <.text+0x4d>
  4eb0be: 8b 3f                        	mov	edi, dword ptr [edi]
  4eb0c0: 85 ff                        	test	edi, edi
  4eb0c2: 74 09                        	je	0x4eb0cd <.text+0x4d>
  4eb0c4: 85 c9                        	test	ecx, ecx
  4eb0c6: 74 05                        	je	0x4eb0cd <.text+0x4d>
  4eb0c8: 3b 4f 04                     	cmp	ecx, dword ptr [edi + 0x4]
  4eb0cb: 75 29                        	jne	0x4eb0f6 <.text+0x76>
  4eb0cd: e8 d5 bc ee 00               	call	0x13d6da7 <.text+0xeebd27>
  4eb0d2: 8d 55 a8                     	lea	edx, [ebp - 0x58]
  4eb0d5: 89 4d a8                     	mov	dword ptr [ebp - 0x58], ecx
  4eb0d8: 52                           	push	edx
  4eb0d9: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
  4eb0dc: e8 e9 b3 ee 00               	call	0x13d64ca <.text+0xeeb44a>
  4eb0e1: 68 90 0f 91 01               	push	0x1910f90
  4eb0e6: 8d 45 90                     	lea	eax, [ebp - 0x70]
  4eb0e9: 50                           	push	eax
  4eb0ea: c7 45 90 84 20 56 01         	mov	dword ptr [ebp - 0x70], 0x1562084
  4eb0f1: e8 a4 ba ee 00               	call	0x13d6b9a <.text+0xeebb1a>
  4eb0f6: 8d 41 0c                     	lea	eax, [ecx + 0xc]
  4eb0f9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4eb0fc: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4eb103: 59                           	pop	ecx
  4eb104: 5f                           	pop	edi
  4eb105: 5e                           	pop	esi
  4eb106: 5b                           	pop	ebx
  4eb107: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4eb10a: 33 cd                        	xor	ecx, ebp
  4eb10c: e8 c7 c0 ee 00               	call	0x13d71d8 <.text+0xeec158>
  4eb111: 8b e5                        	mov	esp, ebp
  4eb113: 5d                           	pop	ebp
  4eb114: c2 04 00                     	ret	0x4
  4eb117: cc                           	int3
  4eb118: cc                           	int3
  4eb119: cc                           	int3
  4eb11a: cc                           	int3
  4eb11b: cc                           	int3
  4eb11c: cc                           	int3
  4eb11d: cc                           	int3
  4eb11e: cc                           	int3
  4eb11f: cc                           	int3
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
  4eb156: e8 95 4d cb 00               	call	0x119fef0 <.text+0xcb4e70>
  4eb15b: 83 c4 04                     	add	esp, 0x4
  4eb15e: 50                           	push	eax
  4eb15f: 68 78 21 56 01               	push	0x1562178
  4eb164: e8 87 4d cb 00               	call	0x119fef0 <.text+0xcb4e70>
  4eb169: 83 c4 04                     	add	esp, 0x4
  4eb16c: 50                           	push	eax
  4eb16d: e8 ae 84 d3 00               	call	0x1223620 <.text+0xd385a0>
  4eb172: 83 c4 08                     	add	esp, 0x8
  4eb175: 84 c0                        	test	al, al
  4eb177: 0f 84 72 06 00 00            	je	0x4eb7ef <.text+0x76f>
  4eb17d: 33 f6                        	xor	esi, esi
  4eb17f: 6a 08                        	push	0x8
  4eb181: 89 75 b0                     	mov	dword ptr [ebp - 0x50], esi
  4eb184: e8 91 b9 ee 00               	call	0x13d6b1a <.text+0xeeba9a>
  4eb189: 83 c4 04                     	add	esp, 0x4
  4eb18c: 3b c6                        	cmp	eax, esi
  4eb18e: 0f 84 ac 07 00 00            	je	0x4eb940 <.text+0x8c0>
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
  4eb1bf: e8 56 b9 ee 00               	call	0x13d6b1a <.text+0xeeba9a>
  4eb1c4: 83 c4 04                     	add	esp, 0x4
  4eb1c7: 3b c6                        	cmp	eax, esi
  4eb1c9: 0f 84 44 07 00 00            	je	0x4eb913 <.text+0x893>
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
  4eb1fc: e8 0f a0 d3 00               	call	0x1225210 <.text+0xd3a190>
  4eb201: 83 c4 08                     	add	esp, 0x8
  4eb204: 84 c0                        	test	al, al
  4eb206: 0f 84 89 05 00 00            	je	0x4eb795 <.text+0x715>
  4eb20c: 8d 64 24 00                  	lea	esp, [esp]
  4eb210: f6 05 54 c7 a4 01 01         	test	byte ptr [0x1a4c754], 0x1
  4eb217: 0f 85 93 00 00 00            	jne	0x4eb2b0 <.text+0x230>
  4eb21d: 83 0d 54 c7 a4 01 01         	or	dword ptr [0x1a4c754], 0x1
  4eb224: 6a 08                        	push	0x8
  4eb226: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
  4eb229: 89 35 40 c7 a4 01            	mov	dword ptr [0x1a4c740], esi
  4eb22f: e8 e6 b8 ee 00               	call	0x13d6b1a <.text+0xeeba9a>
  4eb234: 83 c4 04                     	add	esp, 0x4
  4eb237: 3b c6                        	cmp	eax, esi
  4eb239: 0f 84 fb 05 00 00            	je	0x4eb83a <.text+0x7ba>
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
  4eb265: e8 b0 b8 ee 00               	call	0x13d6b1a <.text+0xeeba9a>
  4eb26a: 83 c4 04                     	add	esp, 0x4
  4eb26d: 3b c6                        	cmp	eax, esi
  4eb26f: 0f 84 98 05 00 00            	je	0x4eb80d <.text+0x78d>
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
  4eb2a4: e8 61 c0 ee 00               	call	0x13d730a <.text+0xeec28a>
  4eb2a9: 83 c4 04                     	add	esp, 0x4
  4eb2ac: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb2b0: 84 1d 54 c7 a4 01            	test	byte ptr [0x1a4c754], bl
  4eb2b6: 75 25                        	jne	0x4eb2dd <.text+0x25d>
  4eb2b8: 09 1d 54 c7 a4 01            	or	dword ptr [0x1a4c754], ebx
  4eb2be: b9 3c c7 a4 01               	mov	ecx, 0x1a4c73c
  4eb2c3: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
  4eb2c7: e8 84 9e cb 00               	call	0x11a5150 <.text+0xcba0d0>
  4eb2cc: 68 30 4a 54 01               	push	0x1544a30
  4eb2d1: e8 34 c0 ee 00               	call	0x13d730a <.text+0xeec28a>
  4eb2d6: 83 c4 04                     	add	esp, 0x4
  4eb2d9: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb2dd: 80 3d 38 c7 a4 01 00         	cmp	byte ptr [0x1a4c738], 0x0
  4eb2e4: 0f 84 cd 00 00 00            	je	0x4eb3b7 <.text+0x337>
  4eb2ea: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
  4eb2ee: 72 08                        	jb	0x4eb2f8 <.text+0x278>
  4eb2f0: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
  4eb2f3: 89 4d a8                     	mov	dword ptr [ebp - 0x58], ecx
  4eb2f6: eb 06                        	jmp	0x4eb2fe <.text+0x27e>
  4eb2f8: 8d 55 b4                     	lea	edx, [ebp - 0x4c]
  4eb2fb: 89 55 a8                     	mov	dword ptr [ebp - 0x58], edx
  4eb2fe: 8d 45                        	<unknown>


<stdin>:	file format elf32-i386

Disassembly of section .text:

012ec680 <.text>:
 12ec680: 00 68 90                     	add	byte ptr [eax - 0x70], ch
 12ec683: 0f 91 01                     	setno	byte ptr [ecx]
 12ec686: 8d 45 94                     	lea	eax, [ebp - 0x6c]
 12ec689: 50                           	push	eax
 12ec68a: c7 45 94 84 20 56 01         	mov	dword ptr [ebp - 0x6c], 0x1562084
 12ec691: e8 04 a5 0e 00               	call	0x13d6b9a <.text+0xea51a>
 12ec696: 8d 4d a0                     	lea	ecx, [ebp - 0x60]
 12ec699: 51                           	push	ecx
 12ec69a: 8d 4d 88                     	lea	ecx, [ebp - 0x78]
 12ec69d: 89 7d a0                     	mov	dword ptr [ebp - 0x60], edi
 12ec6a0: e8 25 9e 0e 00               	call	0x13d64ca <.text+0xe9e4a>
 12ec6a5: 68 90 0f 91 01               	push	0x1910f90
 12ec6aa: 8d 55 88                     	lea	edx, [ebp - 0x78]
 12ec6ad: 52                           	push	edx
 12ec6ae: c7 45 88 84 20 56 01         	mov	dword ptr [ebp - 0x78], 0x1562084
 12ec6b5: e8 e0 a4 0e 00               	call	0x13d6b9a <.text+0xea51a>
 12ec6ba: cc                           	int3
 12ec6bb: cc                           	int3
 12ec6bc: cc                           	int3
 12ec6bd: cc                           	int3
 12ec6be: cc                           	int3
 12ec6bf: cc                           	int3
 12ec6c0: 55                           	push	ebp
 12ec6c1: 8b ec                        	mov	ebp, esp
 12ec6c3: 6a ff                        	push	-0x1
 12ec6c5: 68 88 84 4d 01               	push	0x14d8488
 12ec6ca: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 12ec6d0: 50                           	push	eax
 12ec6d1: 83 ec 68                     	sub	esp, 0x68
 12ec6d4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 12ec6d9: 33 c5                        	xor	eax, ebp
 12ec6db: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 12ec6de: 53                           	push	ebx
 12ec6df: 56                           	push	esi
 12ec6e0: 57                           	push	edi
 12ec6e1: 50                           	push	eax
 12ec6e2: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 12ec6e5: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 12ec6eb: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 12ec6ee: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 12ec6f1: 56                           	push	esi
 12ec6f2: 68 50 f5 d9 01               	push	0x1d9f550
 12ec6f7: 89 7d c4                     	mov	dword ptr [ebp - 0x3c], edi
 12ec6fa: 89 75 c0                     	mov	dword ptr [ebp - 0x40], esi
 12ec6fd: e8 1e 6f f3 ff               	call	0x1223620
 12ec702: 83 c4 08                     	add	esp, 0x8
 12ec705: 84 c0                        	test	al, al
 12ec707: 75 1c                        	jne	0x12ec725 <.text+0xa5>
 12ec709: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 12ec70c: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 12ec713: 59                           	pop	ecx
 12ec714: 5f                           	pop	edi
 12ec715: 5e                           	pop	esi
 12ec716: 5b                           	pop	ebx
 12ec717: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 12ec71a: 33 cd                        	xor	ecx, ebp
 12ec71c: e8 b7 aa 0e 00               	call	0x13d71d8 <.text+0xeab58>
 12ec721: 8b e5                        	mov	esp, ebp
 12ec723: 5d                           	pop	ebp
 12ec724: c3                           	ret
 12ec725: 8b cf                        	mov	ecx, edi
 12ec727: e8 e4 ad e4 ff               	call	0x1137510
 12ec72c: 33 db                        	xor	ebx, ebx
 12ec72e: 6a 08                        	push	0x8
 12ec730: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 12ec733: e8 e2 a3 0e 00               	call	0x13d6b1a <.text+0xea49a>
 12ec738: 83 c4 04                     	add	esp, 0x4
 12ec73b: 3b c3                        	cmp	eax, ebx
 12ec73d: 0f 84 57 04 00 00            	je	0x12ecb9a <.text+0x51a>
 12ec743: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 12ec746: 33 c9                        	xor	ecx, ecx
 12ec748: 89 08                        	mov	dword ptr [eax], ecx
 12ec74a: 33 d2                        	xor	edx, edx
 12ec74c: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 12ec74f: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 12ec752: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 12ec755: 89 01                        	mov	dword ptr [ecx], eax
 12ec757: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 12ec75e: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 12ec761: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 12ec765: 6a 01                        	push	0x1
 12ec767: 50                           	push	eax
 12ec768: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 12ec76b: 88 55 cf                     	mov	byte ptr [ebp - 0x31], dl
 12ec76e: e8 9d 8a f3 ff               	call	0x1225210
 12ec773: 83 c4 08                     	add	esp, 0x8
 12ec776: 84 c0                        	test	al, al
 12ec778: 0f 84 da 03 00 00            	je	0x12ecb58 <.text+0x4d8>
 12ec77e: 8b ff                        	mov	edi, edi
 12ec780: 68 98 75 58 01               	push	0x1587598
 12ec785: e8 66 37 eb ff               	call	0x119fef0
 12ec78a: 8b c8                        	mov	ecx, eax
 12ec78c: 83 c4 04                     	add	esp, 0x4
 12ec78f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12ec792: 66 8b 11                     	mov	dx, word ptr [ecx]
 12ec795: 83 c1 02                     	add	ecx, 0x2
 12ec798: 66 3b d3                     	cmp	dx, bx
 12ec79b: 75 f5                        	jne	0x12ec792 <.text+0x112>
 12ec79d: 2b ce                        	sub	ecx, esi
 12ec79f: d1 f9                        	sar	ecx
 12ec7a1: 51                           	push	ecx
 12ec7a2: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
 12ec7a5: 50                           	push	eax
 12ec7a6: 51                           	push	ecx
 12ec7a7: 53                           	push	ebx
 12ec7a8: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec7ab: e8 80 54 11 ff               	call	0x401c30
 12ec7b0: 85 c0                        	test	eax, eax
 12ec7b2: 75 11                        	jne	0x12ec7c5 <.text+0x145>
 12ec7b4: 8d 57 04                     	lea	edx, [edi + 0x4]
 12ec7b7: 52                           	push	edx
 12ec7b8: e8 93 89 f3 ff               	call	0x1225150
 12ec7bd: 83 c4 04                     	add	esp, 0x4
 12ec7c0: e9 7a 03 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ec7c5: 68 58 02 88 01               	push	0x1880258
 12ec7ca: e8 21 37 eb ff               	call	0x119fef0
 12ec7cf: 8b c8                        	mov	ecx, eax
 12ec7d1: 83 c4 04                     	add	esp, 0x4
 12ec7d4: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12ec7d7: 66 8b 11                     	mov	dx, word ptr [ecx]
 12ec7da: 83 c1 02                     	add	ecx, 0x2
 12ec7dd: 66 3b d3                     	cmp	dx, bx
 12ec7e0: 75 f5                        	jne	0x12ec7d7 <.text+0x157>
 12ec7e2: 2b ce                        	sub	ecx, esi
 12ec7e4: d1 f9                        	sar	ecx
 12ec7e6: 51                           	push	ecx
 12ec7e7: 50                           	push	eax
 12ec7e8: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 12ec7eb: 50                           	push	eax
 12ec7ec: 53                           	push	ebx
 12ec7ed: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec7f0: e8 3b 54 11 ff               	call	0x401c30
 12ec7f5: 85 c0                        	test	eax, eax
 12ec7f7: 75 1a                        	jne	0x12ec813 <.text+0x193>
 12ec7f9: 8d 4f 24                     	lea	ecx, [edi + 0x24]
 12ec7fc: 51                           	push	ecx
 12ec7fd: e8 4e 89 f3 ff               	call	0x1225150
 12ec802: 53                           	push	ebx
 12ec803: e8 58 6e f3 ff               	call	0x1223660
 12ec808: 83 c4 08                     	add	esp, 0x8
 12ec80b: 89 47 64                     	mov	dword ptr [edi + 0x64], eax
 12ec80e: e9 2c 03 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ec813: 68 64 e2 82 01               	push	0x182e264
 12ec818: e8 d3 36 eb ff               	call	0x119fef0
 12ec81d: 8b c8                        	mov	ecx, eax
 12ec81f: 83 c4 04                     	add	esp, 0x4
 12ec822: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12ec825: 66 8b 11                     	mov	dx, word ptr [ecx]
 12ec828: 83 c1 02                     	add	ecx, 0x2
 12ec82b: 66 3b d3                     	cmp	dx, bx
 12ec82e: 75 f5                        	jne	0x12ec825 <.text+0x1a5>
 12ec830: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 12ec833: 2b ce                        	sub	ecx, esi
 12ec835: d1 f9                        	sar	ecx
 12ec837: 51                           	push	ecx
 12ec838: 50                           	push	eax
 12ec839: 52                           	push	edx
 12ec83a: 53                           	push	ebx
 12ec83b: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec83e: e8 ed 53 11 ff               	call	0x401c30
 12ec843: 85 c0                        	test	eax, eax
 12ec845: 75 11                        	jne	0x12ec858 <.text+0x1d8>
 12ec847: 8d 47 44                     	lea	eax, [edi + 0x44]
 12ec84a: 50                           	push	eax
 12ec84b: e8 00 89 f3 ff               	call	0x1225150
 12ec850: 83 c4 04                     	add	esp, 0x4
 12ec853: e9 e7 02 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ec858: 68 20 d8 56 01               	push	0x156d820
 12ec85d: e8 8e 36 eb ff               	call	0x119fef0
 12ec862: 8b c8                        	mov	ecx, eax
 12ec864: 83 c4 04                     	add	esp, 0x4
 12ec867: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12ec86a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 12ec870: 66 8b 11                     	mov	dx, word ptr [ecx]
 12ec873: 83 c1 02                     	add	ecx, 0x2
 12ec876: 66 3b d3                     	cmp	dx, bx
 12ec879: 75 f5                        	jne	0x12ec870 <.text+0x1f0>
 12ec87b: 2b ce                        	sub	ecx, esi
 12ec87d: d1 f9                        	sar	ecx
 12ec87f: 51                           	push	ecx
 12ec880: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
 12ec883: 50                           	push	eax
 12ec884: 51                           	push	ecx
 12ec885: 53                           	push	ebx
 12ec886: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec889: e8 a2 53 11 ff               	call	0x401c30
 12ec88e: 85 c0                        	test	eax, eax
 12ec890: 0f 85 c6 00 00 00            	jne	0x12ec95c <.text+0x2dc>
 12ec896: 8d 4f 68                     	lea	ecx, [edi + 0x68]
 12ec899: e8 72 ac 45 ff               	call	0x747510
 12ec89e: 8d 55 cf                     	lea	edx, [ebp - 0x31]
 12ec8a1: 52                           	push	edx
 12ec8a2: e8 b9 6d f3 ff               	call	0x1223660
 12ec8a7: 83 c4 04                     	add	esp, 0x4
 12ec8aa: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ec8ae: 0f 84 88 02 00 00            	je	0x12ecb3c <.text+0x4bc>
 12ec8b4: 89 45 a8                     	mov	dword ptr [ebp - 0x58], eax
 12ec8b7: 6a 01                        	push	0x1
 12ec8b9: 8d 45 cf                     	lea	eax, [ebp - 0x31]
 12ec8bc: 50                           	push	eax
 12ec8bd: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec8c0: 51                           	push	ecx
 12ec8c1: 8d 55 ce                     	lea	edx, [ebp - 0x32]
 12ec8c4: 52                           	push	edx
 12ec8c5: c7 45 ac ff ff ff ff         	mov	dword ptr [ebp - 0x54], 0xffffffff
 12ec8cc: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 12ec8cf: c6 45 ce 00                  	mov	byte ptr [ebp - 0x32], 0x0
 12ec8d3: e8 18 90 f3 ff               	call	0x12258f0
 12ec8d8: 83 c4 10                     	add	esp, 0x10
 12ec8db: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ec8df: 0f 84 57 02 00 00            	je	0x12ecb3c <.text+0x4bc>
 12ec8e5: 80 7d ce 00                  	cmp	byte ptr [ebp - 0x32], 0x0
 12ec8e9: 74 47                        	je	0x12ec932 <.text+0x2b2>
 12ec8eb: 68 34 02 88 01               	push	0x1880234
 12ec8f0: e8 fb 35 eb ff               	call	0x119fef0
 12ec8f5: 8b c8                        	mov	ecx, eax
 12ec8f7: 83 c4 04                     	add	esp, 0x4
 12ec8fa: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12ec8fd: 8d 49 00                     	lea	ecx, [ecx]
 12ec900: 66 8b 11                     	mov	dx, word ptr [ecx]
 12ec903: 83 c1 02                     	add	ecx, 0x2
 12ec906: 66 3b d3                     	cmp	dx, bx
 12ec909: 75 f5                        	jne	0x12ec900 <.text+0x280>
 12ec90b: 2b ce                        	sub	ecx, esi
 12ec90d: d1 f9                        	sar	ecx
 12ec90f: 51                           	push	ecx
 12ec910: 50                           	push	eax
 12ec911: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 12ec914: 50                           	push	eax
 12ec915: 53                           	push	ebx
 12ec916: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12ec919: e8 12 53 11 ff               	call	0x401c30
 12ec91e: 85 c0                        	test	eax, eax
 12ec920: 75 07                        	jne	0x12ec929 <.text+0x2a9>
 12ec922: c7 45 b0 01 00 00 00         	mov	dword ptr [ebp - 0x50], 0x1
 12ec929: 53                           	push	ebx
 12ec92a: e8 31 6d f3 ff               	call	0x1223660
 12ec92f: 83 c4 04                     	add	esp, 0x4
 12ec932: 8d 4d a8                     	lea	ecx, [ebp - 0x58]
 12ec935: 51                           	push	ecx
 12ec936: 8d 4f 68                     	lea	ecx, [edi + 0x68]
 12ec939: 89 45 ac                     	mov	dword ptr [ebp - 0x54], eax
 12ec93c: e8 0f d4 bb ff               	call	0xea9d50
 12ec941: 8d 55 cf                     	lea	edx, [ebp - 0x31]
 12ec944: 52                           	push	edx
 12ec945: e8 16 6d f3 ff               	call	0x1223660
 12ec94a: 83 c4 04                     	add	esp, 0x4
 12ec94d: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ec951: 0f 85 5d ff ff ff            	jne	0x12ec8b4 <.text+0x234>
 12ec957: e9 e0 01 00 00               	jmp	0x12ecb3c <.text+0x4bc>
 12ec95c: 68 0c 02 88 01               	push	0x188020c
 12ec961: e8 8a 35 eb ff               	call	0x119fef0
 12ec966: 50                           	push	eax
 12ec967: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 12ec96a: 50                           	push	eax
 12ec96b: e8 10 54 11 ff               	call	0x401d80
 12ec970: 83 c4 0c                     	add	esp, 0xc
 12ec973: 84 c0                        	test	al, al
 12ec975: 74 16                        	je	0x12ec98d <.text+0x30d>
 12ec977: 53                           	push	ebx
 12ec978: e8 e3 6c f3 ff               	call	0x1223660
 12ec97d: 83 c4 04                     	add	esp, 0x4
 12ec980: 3b c3                        	cmp	eax, ebx
 12ec982: 0f 95 c1                     	setne	cl
 12ec985: 88 4f 7c                     	mov	byte ptr [edi + 0x7c], cl
 12ec988: e9 b2 01 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ec98d: 68 e8 01 88 01               	push	0x18801e8
 12ec992: e8 59 35 eb ff               	call	0x119fef0
 12ec997: 50                           	push	eax
 12ec998: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 12ec99b: 52                           	push	edx
 12ec99c: e8 df 53 11 ff               	call	0x401d80
 12ec9a1: 83 c4 0c                     	add	esp, 0xc
 12ec9a4: 84 c0                        	test	al, al
 12ec9a6: 74 42                        	je	0x12ec9ea <.text+0x36a>
 12ec9a8: 8d 45 cf                     	lea	eax, [ebp - 0x31]
 12ec9ab: 50                           	push	eax
 12ec9ac: e8 af 6c f3 ff               	call	0x1223660
 12ec9b1: 83 c4 04                     	add	esp, 0x4
 12ec9b4: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ec9b8: 89 45 c8                     	mov	dword ptr [ebp - 0x38], eax
 12ec9bb: 0f 84 7e 01 00 00            	je	0x12ecb3f <.text+0x4bf>
 12ec9c1: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
 12ec9c4: 51                           	push	ecx
 12ec9c5: 8d 8f 80 00 00 00            	lea	ecx, [edi + 0x80]
 12ec9cb: e8 a0 6d 1a ff               	call	0x493770
 12ec9d0: 8d 55 cf                     	lea	edx, [ebp - 0x31]
 12ec9d3: 52                           	push	edx
 12ec9d4: e8 87 6c f3 ff               	call	0x1223660
 12ec9d9: 83 c4 04                     	add	esp, 0x4
 12ec9dc: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ec9e0: 89 45 c8                     	mov	dword ptr [ebp - 0x38], eax
 12ec9e3: 75 dc                        	jne	0x12ec9c1 <.text+0x341>
 12ec9e5: e9 55 01 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ec9ea: 68 b4 01 88 01               	push	0x18801b4
 12ec9ef: e8 fc 34 eb ff               	call	0x119fef0
 12ec9f4: 50                           	push	eax
 12ec9f5: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 12ec9f8: 50                           	push	eax
 12ec9f9: e8 82 53 11 ff               	call	0x401d80
 12ec9fe: 83 c4 0c                     	add	esp, 0xc
 12eca01: 84 c0                        	test	al, al
 12eca03: 74 50                        	je	0x12eca55 <.text+0x3d5>
 12eca05: 8d 4d cf                     	lea	ecx, [ebp - 0x31]
 12eca08: 51                           	push	ecx
 12eca09: e8 52 6c f3 ff               	call	0x1223660
 12eca0e: 83 c4 04                     	add	esp, 0x4
 12eca11: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12eca15: 0f 84 24 01 00 00            	je	0x12ecb3f <.text+0x4bf>
 12eca1b: eb 03                        	jmp	0x12eca20 <.text+0x3a0>
 12eca1d: 8d 49 00                     	lea	ecx, [ecx]
 12eca20: 53                           	push	ebx
 12eca21: 89 45 98                     	mov	dword ptr [ebp - 0x68], eax
 12eca24: e8 37 6c f3 ff               	call	0x1223660
 12eca29: 83 c4 04                     	add	esp, 0x4
 12eca2c: 8d 55 98                     	lea	edx, [ebp - 0x68]
 12eca2f: 52                           	push	edx
 12eca30: 8d 8f 94 00 00 00            	lea	ecx, [edi + 0x94]
 12eca36: 89 45 9c                     	mov	dword ptr [ebp - 0x64], eax
 12eca39: e8 f2 3b 23 ff               	call	0x520630
 12eca3e: 8d 45 cf                     	lea	eax, [ebp - 0x31]
 12eca41: 50                           	push	eax
 12eca42: e8 19 6c f3 ff               	call	0x1223660
 12eca47: 83 c4 04                     	add	esp, 0x4
 12eca4a: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12eca4e: 75 d0                        	jne	0x12eca20 <.text+0x3a0>
 12eca50: e9 ea 00 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12eca55: 68 88 01 88 01               	push	0x1880188
 12eca5a: e8 91 34 eb ff               	call	0x119fef0
 12eca5f: 50                           	push	eax
 12eca60: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 12eca63: 51                           	push	ecx
 12eca64: e8 17 53 11 ff               	call	0x401d80
 12eca69: 83 c4 0c                     	add	esp, 0xc
 12eca6c: 84 c0                        	test	al, al
 12eca6e: 74 4f                        	je	0x12ecabf <.text+0x43f>
 12eca70: 8d 55 cf                     	lea	edx, [ebp - 0x31]
 12eca73: 52                           	push	edx
 12eca74: e8 e7 6b f3 ff               	call	0x1223660
 12eca79: 53                           	push	ebx
 12eca7a: 89 45 c8                     	mov	dword ptr [ebp - 0x38], eax
 12eca7d: e8 de 6b f3 ff               	call	0x1223660
 12eca82: 83 c4 08                     	add	esp, 0x8
 12eca85: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12eca89: 0f 84 b0 00 00 00            	je	0x12ecb3f <.text+0x4bf>
 12eca8f: 90                           	nop
 12eca90: 8d 45 c8                     	lea	eax, [ebp - 0x38]
 12eca93: 50                           	push	eax
 12eca94: 8d 8f a8 00 00 00            	lea	ecx, [edi + 0xa8]
 12eca9a: e8 d1 6c 1a ff               	call	0x493770
 12eca9f: 8d 4d cf                     	lea	ecx, [ebp - 0x31]
 12ecaa2: 51                           	push	ecx
 12ecaa3: e8 b8 6b f3 ff               	call	0x1223660
 12ecaa8: 53                           	push	ebx
 12ecaa9: 89 45 c8                     	mov	dword ptr [ebp - 0x38], eax
 12ecaac: e8 af 6b f3 ff               	call	0x1223660
 12ecab1: 83 c4 08                     	add	esp, 0x8
 12ecab4: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ecab8: 75 d6                        	jne	0x12eca90 <.text+0x410>
 12ecaba: e9 80 00 00 00               	jmp	0x12ecb3f <.text+0x4bf>
 12ecabf: 68 5c 01 88 01               	push	0x188015c
 12ecac4: e8 27 34 eb ff               	call	0x119fef0
 12ecac9: 50                           	push	eax
 12ecaca: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 12ecacd: 52                           	push	edx
 12ecace: e8 ad 52 11 ff               	call	0x401d80
 12ecad3: 83 c4 0c                     	add	esp, 0xc
 12ecad6: 84 c0                        	test	al, al
 12ecad8: 74 65                        	je	0x12ecb3f <.text+0x4bf>
 12ecada: 8d 45 cf                     	lea	eax, [ebp - 0x31]
 12ecadd: 50                           	push	eax
 12ecade: e8 7d 6b f3 ff               	call	0x1223660
 12ecae3: 83 c4 04                     	add	esp, 0x4
 12ecae6: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ecaea: 8b f8                        	mov	edi, eax
 12ecaec: 74 4e                        	je	0x12ecb3c <.text+0x4bc>
 12ecaee: 8b 5d c4                     	mov	ebx, dword ptr [ebp - 0x3c]
 12ecaf1: 33 f6                        	xor	esi, esi
 12ecaf3: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ecaf7: 74 20                        	je	0x12ecb19 <.text+0x499>
 12ecaf9: 85 f6                        	test	esi, esi
 12ecafb: 75 05                        	jne	0x12ecb02 <.text+0x482>
 12ecafd: 89 7d b8                     	mov	dword ptr [ebp - 0x48], edi
 12ecb00: eb 03                        	jmp	0x12ecb05 <.text+0x485>
 12ecb02: 89 7d b4                     	mov	dword ptr [ebp - 0x4c], edi
 12ecb05: 8d 4d cf                     	lea	ecx, [ebp - 0x31]
 12ecb08: 51                           	push	ecx
 12ecb09: e8 52 6b f3 ff               	call	0x1223660
 12ecb0e: 46                           	inc	esi
 12ecb0f: 83 c4 04                     	add	esp, 0x4
 12ecb12: 8b f8                        	mov	edi, eax
 12ecb14: 83 fe 02                     	cmp	esi, 0x2
 12ecb17: 7c da                        	jl	0x12ecaf3 <.text+0x473>
 12ecb19: 8b 55 b8                     	mov	edx, dword ptr [ebp - 0x48]
 12ecb1c: 8b 45 b4                     	mov	eax, dword ptr [ebp - 0x4c]
 12ecb1f: 8d 4d a0                     	lea	ecx, [ebp - 0x60]
 12ecb22: 51                           	push	ecx
 12ecb23: 8d 8b bc 00 00 00            	lea	ecx, [ebx + 0xbc]
 12ecb29: 89 55 a0                     	mov	dword ptr [ebp - 0x60], edx
 12ecb2c: 89 45 a4                     	mov	dword ptr [ebp - 0x5c], eax
 12ecb2f: e8 fc 3a 23 ff               	call	0x520630
 12ecb34: 80 7d cf 00                  	cmp	byte ptr [ebp - 0x31], 0x0
 12ecb38: 75 b7                        	jne	0x12ecaf1 <.text+0x471>
 12ecb3a: 33 db                        	xor	ebx, ebx
 12ecb3c: 8b 7d c4                     	mov	edi, dword ptr [ebp - 0x3c]
 12ecb3f: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 12ecb42: 6a 01                        	push	0x1
 12ecb44: 52                           	push	edx
 12ecb45: e8 c6 86 f3 ff               	call	0x1225210
 12ecb4a: 83 c4 08                     	add	esp, 0x8
 12ecb4d: 84 c0                        	test	al, al
 12ecb4f: 0f 85 2b fc ff ff            	jne	0x12ec780 <.text+0x100>
 12ecb55: 8b 75 c0                     	mov	esi, dword ptr [ebp - 0x40]
 12ecb58: 56                           	push	esi
 12ecb59: b9 50 f7 d9 01               	mov	ecx, 0x1d9f750
 12ecb5e: e8 1d 81 f3 ff               	call	0x1224c80
 12ecb63: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 12ecb67: 89 07                        	mov	dword ptr [edi], eax
 12ecb69: 72 0c                        	jb	0x12ecb77 <.text+0x4f7>
 12ecb6b: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 12ecb6e: 50                           	push	eax
 12ecb6f: e8 b3 8f 0e 00               	call	0x13d5b27 <.text+0xe94a7>
 12ecb74: 83 c4 04                     	add	esp, 0x4
 12ecb77: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 12ecb7a: 33 c9                        	xor	ecx, ecx
 12ecb7c: 52                           	push	edx
 12ecb7d: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 12ecb84: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 12ecb87: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 12ecb8b: e8 97 8f 0e 00               	call	0x13d5b27 <.text+0xe94a7>
 12ecb90: 83 c4 04                     	add	esp, 0x4
 12ecb93: b0 01                        	mov	al, 0x1
 12ecb95: e9 6f fb ff ff               	jmp	0x12ec709 <.text+0x89>
 12ecb9a: 8d 45 bc                     	lea	eax, [ebp - 0x44]
 12ecb9d: 50                           	push	eax
 12ecb9e: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 12ecba1: 89 5d bc                     	mov	dword ptr [ebp - 0x44], ebx
 12ecba4: e8 21 99 0e 00               	call	0x13d64ca <.text+0xe9e4a>
 12ecba9: 68 90 0f 91 01               	push	0x1910f90
 12ecbae: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 12ecbb1: 51                           	push	ecx
 12ecbb2: c7 45 8c 84 20 56 01         	mov	dword ptr [ebp - 0x74], 0x1562084
 12ecbb9: e8 dc 9f 0e 00               	call	0x13d6b9a <.text+0xea51a>
 12ecbbe: cc                           	int3
 12ecbbf: cc                           	int3
 12ecbc0: 55                           	push	ebp
 12ecbc1: 8b ec                        	mov	ebp, esp
 12ecbc3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 12ecbc6: 68 00 01 00 00               	push	0x100
 12ecbcb: 50                           	push	eax
 12ecbcc: 68 90 01 da 01               	push	0x1da0190
 12ecbd1: e8 a2 08 0f 00               	call	0x13dd478 <.text+0xf0df8>
 12ecbd6: b8 90 01 da 01               	mov	eax, 0x1da0190
 12ecbdb: 83 c4 0c                     	add	esp, 0xc
 12ecbde: 8d 50 02                     	lea	edx, [eax + 0x2]
 12ecbe1: 66 8b 08                     	mov	cx, word ptr [eax]
 12ecbe4: 83 c0 02                     	add	eax, 0x2
 12ecbe7: 66 85 c9                     	test	cx, cx
 12ecbea: 75 f5                        	jne	0x12ecbe1 <.text+0x561>
 12ecbec: 2b c2                        	sub	eax, edx
 12ecbee: d1 f8                        	sar	eax
 12ecbf0: 66 83 3c 45 8e 01 da 01 5c   	cmp	word ptr [2*eax + 0x1da018e], 0x5c
 12ecbf9: 74 2b                        	je	0x12ecc26 <.text+0x5a6>
 12ecbfb: 66 83 3c 45 8e 01 da 01 2f   	cmp	word ptr [2*eax + 0x1da018e], 0x2f
 12ecc04: 74 20                        	je	0x12ecc26 <.text+0x5a6>
 12ecc06: 68 00 01 00 00               	push	0x100
 12ecc0b: 68 70 f2 59 01               	push	0x159f270
 12ecc10: e8 db 32 eb ff               	call	0x119fef0
 12ecc15: 83 c4 04                     	add	esp, 0x4
 12ecc18: 50                           	push	eax
 12ecc19: 68 90 01 da 01               	push	0x1da0190
 12ecc1e: e8 4d 25 0f 00               	call	0x13df170 <.text+0xf2af0>
 12ecc23: 83 c4 0c                     	add	esp, 0xc
 12ecc26: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 12ecc29: 6a 00                        	push	0x0
 12ecc2b: 51                           	push	ecx
 12ecc2c: 68 90 01 da 01               	push	0x1da0190
 12ecc31: 68 90 03 da 01               	push	0x1da0390
 12ecc36: e8 55 cd f3 ff               	call	0x1229990
 12ecc3b: 83 c4 10                     	add	esp, 0x10
 12ecc3e: 84 c0                        	test	al, al
 12ecc40: 0f 95 c0                     	setne	al
 12ecc43: 5d                           	pop	ebp
 12ecc44: c3                           	ret
 12ecc45: cc                           	int3
 12ecc46: cc                           	int3
 12ecc47: cc                           	int3
 12ecc48: cc                           	int3
 12ecc49: cc                           	int3
 12ecc4a: cc                           	int3
 12ecc4b: cc                           	int3
 12ecc4c: cc                           	int3
 12ecc4d: cc                           	int3
 12ecc4e: cc                           	int3
 12ecc4f: cc                           	int3
 12ecc50: 55                           	push	ebp
 12ecc51: 8b ec                        	mov	ebp, esp
 12ecc53: 6a ff                        	push	-0x1
 12ecc55: 68 62 59 42 01               	push	0x1425962
 12ecc5a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 12ecc60: 50                           	push	eax
 12ecc61: 51                           	push	ecx
 12ecc62: 56                           	push	esi
 12ecc63: 57                           	push	edi
 12ecc64: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 12ecc69: 33 c5                        	xor	eax, ebp
 12ecc6b: 50                           	push	eax
 12ecc6c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 12ecc6f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 12ecc75: 8b f9                        	mov	edi, ecx
 12ecc77: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 12ecc7a: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 12ecc7d: 3b f1                        	cmp	esi, ecx
 12ecc7f: 73                           	<unknown>

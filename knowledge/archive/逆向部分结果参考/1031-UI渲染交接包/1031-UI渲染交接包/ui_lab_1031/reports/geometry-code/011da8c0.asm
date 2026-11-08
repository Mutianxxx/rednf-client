
<stdin>:	file format elf32-i386

Disassembly of section .text:

011da8c0 <.text>:
 11da8c0: 55                           	push	ebp
 11da8c1: 8b ec                        	mov	ebp, esp
 11da8c3: 83 79 64 00                  	cmp	dword ptr [ecx + 0x64], 0x0
 11da8c7: 74 09                        	je	0x11da8d2 <.text+0x12>
 11da8c9: b8 00 00 00 80               	mov	eax, 0x80000000
 11da8ce: 5d                           	pop	ebp
 11da8cf: c2 08 00                     	ret	0x8
 11da8d2: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11da8d5: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11da8d8: 89 41 64                     	mov	dword ptr [ecx + 0x64], eax
 11da8db: 89 51 68                     	mov	dword ptr [ecx + 0x68], edx
 11da8de: b8 01 00 00 00               	mov	eax, 0x1
 11da8e3: 5d                           	pop	ebp
 11da8e4: c2 08 00                     	ret	0x8
 11da8e7: cc                           	int3
 11da8e8: cc                           	int3
 11da8e9: cc                           	int3
 11da8ea: cc                           	int3
 11da8eb: cc                           	int3
 11da8ec: cc                           	int3
 11da8ed: cc                           	int3
 11da8ee: cc                           	int3
 11da8ef: cc                           	int3
 11da8f0: 33 c0                        	xor	eax, eax
 11da8f2: 39 41 5c                     	cmp	dword ptr [ecx + 0x5c], eax
 11da8f5: 0f 95 c0                     	setne	al
 11da8f8: c3                           	ret
 11da8f9: cc                           	int3
 11da8fa: cc                           	int3
 11da8fb: cc                           	int3
 11da8fc: cc                           	int3
 11da8fd: cc                           	int3
 11da8fe: cc                           	int3
 11da8ff: cc                           	int3
 11da900: b8 01 00 00 00               	mov	eax, 0x1
 11da905: 66 39 41 1c                  	cmp	word ptr [ecx + 0x1c], ax
 11da909: 75 1b                        	jne	0x11da926 <.text+0x66>
 11da90b: 66 39 41 1e                  	cmp	word ptr [ecx + 0x1e], ax
 11da90f: 75 15                        	jne	0x11da926 <.text+0x66>
 11da911: 0f b7 51 24                  	movzx	edx, word ptr [ecx + 0x24]
 11da915: 56                           	push	esi
 11da916: 0f bf 71 20                  	movsx	esi, word ptr [ecx + 0x20]
 11da91a: 3b f2                        	cmp	esi, edx
 11da91c: 5e                           	pop	esi
 11da91d: 75 07                        	jne	0x11da926 <.text+0x66>
 11da91f: 66 83 79 22 00               	cmp	word ptr [ecx + 0x22], 0x0
 11da924: 74 02                        	je	0x11da928 <.text+0x68>
 11da926: 33 c0                        	xor	eax, eax
 11da928: c3                           	ret
 11da929: cc                           	int3
 11da92a: cc                           	int3
 11da92b: cc                           	int3
 11da92c: cc                           	int3
 11da92d: cc                           	int3
 11da92e: cc                           	int3
 11da92f: cc                           	int3
 11da930: 8b 41 5c                     	mov	eax, dword ptr [ecx + 0x5c]
 11da933: 8b 08                        	mov	ecx, dword ptr [eax]
 11da935: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
 11da938: 6a 00                        	push	0x0
 11da93a: 50                           	push	eax
 11da93b: ff d2                        	call	edx
 11da93d: c3                           	ret
 11da93e: cc                           	int3
 11da93f: cc                           	int3
 11da940: 55                           	push	ebp
 11da941: 8b ec                        	mov	ebp, esp
 11da943: 8b 41 5c                     	mov	eax, dword ptr [ecx + 0x5c]
 11da946: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11da949: 8b 08                        	mov	ecx, dword ptr [eax]
 11da94b: 52                           	push	edx
 11da94c: 50                           	push	eax
 11da94d: 8b 41 54                     	mov	eax, dword ptr [ecx + 0x54]
 11da950: ff d0                        	call	eax
 11da952: 5d                           	pop	ebp
 11da953: c2 04 00                     	ret	0x4
 11da956: cc                           	int3
 11da957: cc                           	int3
 11da958: cc                           	int3
 11da959: cc                           	int3
 11da95a: cc                           	int3
 11da95b: cc                           	int3
 11da95c: cc                           	int3
 11da95d: cc                           	int3
 11da95e: cc                           	int3
 11da95f: cc                           	int3
 11da960: 55                           	push	ebp
 11da961: 8b ec                        	mov	ebp, esp
 11da963: 56                           	push	esi
 11da964: 8b f1                        	mov	esi, ecx
 11da966: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11da96a: 74 34                        	je	0x11da9a0 <.text+0xe0>
 11da96c: e8 bf 8f fd ff               	call	0x11b3930
 11da971: 84 c0                        	test	al, al
 11da973: 74 2b                        	je	0x11da9a0 <.text+0xe0>
 11da975: 57                           	push	edi
 11da976: 8b 7d 0c                     	mov	edi, dword ptr [ebp + 0xc]
 11da979: 81 ff 10 27 00 00            	cmp	edi, 0x2710
 11da97f: 73 08                        	jae	0x11da989 <.text+0xc9>
 11da981: 5f                           	pop	edi
 11da982: 32 c0                        	xor	al, al
 11da984: 5e                           	pop	esi
 11da985: 5d                           	pop	ebp
 11da986: c2 08 00                     	ret	0x8
 11da989: 8b ce                        	mov	ecx, esi
 11da98b: e8 b0 8f fd ff               	call	0x11b3940
 11da990: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11da993: 2b c8                        	sub	ecx, eax
 11da995: 3b cf                        	cmp	ecx, edi
 11da997: 5f                           	pop	edi
 11da998: 0f 97 c0                     	seta	al
 11da99b: 5e                           	pop	esi
 11da99c: 5d                           	pop	ebp
 11da99d: c2 08 00                     	ret	0x8
 11da9a0: 32 c0                        	xor	al, al
 11da9a2: 5e                           	pop	esi
 11da9a3: 5d                           	pop	ebp
 11da9a4: c2 08 00                     	ret	0x8
 11da9a7: cc                           	int3
 11da9a8: cc                           	int3
 11da9a9: cc                           	int3
 11da9aa: cc                           	int3
 11da9ab: cc                           	int3
 11da9ac: cc                           	int3
 11da9ad: cc                           	int3
 11da9ae: cc                           	int3
 11da9af: cc                           	int3
 11da9b0: 55                           	push	ebp
 11da9b1: 8b ec                        	mov	ebp, esp
 11da9b3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11da9b6: 56                           	push	esi
 11da9b7: 50                           	push	eax
 11da9b8: 8b f1                        	mov	esi, ecx
 11da9ba: e8 41 9e fd ff               	call	0x11b4800
 11da9bf: 33 c0                        	xor	eax, eax
 11da9c1: 33 c9                        	xor	ecx, ecx
 11da9c3: c7 06 6c c7 85 01            	mov	dword ptr [esi], 0x185c76c
 11da9c9: 89 46 10                     	mov	dword ptr [esi + 0x10], eax
 11da9cc: 66 89 4e 0c                  	mov	word ptr [esi + 0xc], cx
 11da9d0: 89 46 5c                     	mov	dword ptr [esi + 0x5c], eax
 11da9d3: 89 46 60                     	mov	dword ptr [esi + 0x60], eax
 11da9d6: 89 46 64                     	mov	dword ptr [esi + 0x64], eax
 11da9d9: 89 46 68                     	mov	dword ptr [esi + 0x68], eax
 11da9dc: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11da9e2: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11da9e5: 8b c6                        	mov	eax, esi
 11da9e7: 5e                           	pop	esi
 11da9e8: 5d                           	pop	ebp
 11da9e9: c2 0c 00                     	ret	0xc
 11da9ec: cc                           	int3
 11da9ed: cc                           	int3
 11da9ee: cc                           	int3
 11da9ef: cc                           	int3
 11da9f0: 55                           	push	ebp
 11da9f1: 8b ec                        	mov	ebp, esp
 11da9f3: 6a ff                        	push	-0x1
 11da9f5: 68 a8 8e 4c 01               	push	0x14c8ea8
 11da9fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11daa00: 50                           	push	eax
 11daa01: 51                           	push	ecx
 11daa02: 56                           	push	esi
 11daa03: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11daa08: 33 c5                        	xor	eax, ebp
 11daa0a: 50                           	push	eax
 11daa0b: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11daa0e: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11daa14: 8b f1                        	mov	esi, ecx
 11daa16: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 11daa19: c7 06 6c c7 85 01            	mov	dword ptr [esi], 0x185c76c
 11daa1f: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11daa26: e8 15 fe ff ff               	call	0x11da840
 11daa2b: 8b ce                        	mov	ecx, esi
 11daa2d: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11daa34: e8 87 92 fd ff               	call	0x11b3cc0
 11daa39: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11daa3c: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11daa43: 59                           	pop	ecx
 11daa44: 5e                           	pop	esi
 11daa45: 8b e5                        	mov	esp, ebp
 11daa47: 5d                           	pop	ebp
 11daa48: c3                           	ret
 11daa49: cc                           	int3
 11daa4a: cc                           	int3
 11daa4b: cc                           	int3
 11daa4c: cc                           	int3
 11daa4d: cc                           	int3
 11daa4e: cc                           	int3
 11daa4f: cc                           	int3
 11daa50: 55                           	push	ebp
 11daa51: 8b ec                        	mov	ebp, esp
 11daa53: 83 ec 08                     	sub	esp, 0x8
 11daa56: 56                           	push	esi
 11daa57: 8b f1                        	mov	esi, ecx
 11daa59: 66 83 7e 1c 01               	cmp	word ptr [esi + 0x1c], 0x1
 11daa5e: 75 1a                        	jne	0x11daa7a <.text+0x1ba>
 11daa60: 66 83 7e 1e 01               	cmp	word ptr [esi + 0x1e], 0x1
 11daa65: 75 13                        	jne	0x11daa7a <.text+0x1ba>
 11daa67: 0f b7 46 24                  	movzx	eax, word ptr [esi + 0x24]
 11daa6b: 0f bf 4e 20                  	movsx	ecx, word ptr [esi + 0x20]
 11daa6f: 3b c8                        	cmp	ecx, eax
 11daa71: 75 07                        	jne	0x11daa7a <.text+0x1ba>
 11daa73: 66 83 7e 22 00               	cmp	word ptr [esi + 0x22], 0x0
 11daa78: 74 3e                        	je	0x11daab8 <.text+0x1f8>
 11daa7a: 8b ce                        	mov	ecx, esi
 11daa7c: e8 ff 9c fd ff               	call	0x11b4780
 11daa81: 84 c0                        	test	al, al
 11daa83: 74 0a                        	je	0x11daa8f <.text+0x1cf>
 11daa85: b8 06 00 00 80               	mov	eax, 0x80000006
 11daa8a: 5e                           	pop	esi
 11daa8b: 8b e5                        	mov	esp, ebp
 11daa8d: 5d                           	pop	ebp
 11daa8e: c3                           	ret
 11daa8f: 8b 46 5c                     	mov	eax, dword ptr [esi + 0x5c]
 11daa92: 8b 10                        	mov	edx, dword ptr [eax]
 11daa94: 8b 52 4c                     	mov	edx, dword ptr [edx + 0x4c]
 11daa97: 6a 00                        	push	0x0
 11daa99: 6a 00                        	push	0x0
 11daa9b: 8d 4d f8                     	lea	ecx, [ebp - 0x8]
 11daa9e: 51                           	push	ecx
 11daa9f: 6a 00                        	push	0x0
 11daaa1: 50                           	push	eax
 11daaa2: ff d2                        	call	edx
 11daaa4: 85 c0                        	test	eax, eax
 11daaa6: 78 15                        	js	0x11daabd <.text+0x1fd>
 11daaa8: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
 11daaab: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11daaae: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
 11daab1: 89 4e 10                     	mov	dword ptr [esi + 0x10], ecx
 11daab4: 83 4e 44 01                  	or	dword ptr [esi + 0x44], 0x1
 11daab8: b8 01 00 00 00               	mov	eax, 0x1
 11daabd: 5e                           	pop	esi
 11daabe: 8b e5                        	mov	esp, ebp
 11daac0: 5d                           	pop	ebp
 11daac1: c3                           	ret
 11daac2: cc                           	int3
 11daac3: cc                           	int3
 11daac4: cc                           	int3
 11daac5: cc                           	int3
 11daac6: cc                           	int3
 11daac7: cc                           	int3
 11daac8: cc                           	int3
 11daac9: cc                           	int3
 11daaca: cc                           	int3
 11daacb: cc                           	int3
 11daacc: cc                           	int3
 11daacd: cc                           	int3
 11daace: cc                           	int3
 11daacf: cc                           	int3
 11daad0: 56                           	push	esi
 11daad1: 8b f1                        	mov	esi, ecx
 11daad3: 66 83 7e 1c 01               	cmp	word ptr [esi + 0x1c], 0x1
 11daad8: 75 1a                        	jne	0x11daaf4 <.text+0x234>
 11daada: 66 83 7e 1e 01               	cmp	word ptr [esi + 0x1e], 0x1
 11daadf: 75                           	<unknown>


<stdin>:	file format elf32-i386

Disassembly of section .text:

011d10d0 <.text>:
 11d10d0: 55                           	push	ebp
 11d10d1: 8b ec                        	mov	ebp, esp
 11d10d3: 8b 89 b8 02 00 00            	mov	ecx, dword ptr [ecx + 0x2b8]
 11d10d9: 5d                           	pop	ebp
 11d10da: e9 b1 fe ff ff               	jmp	0x11d0f90
 11d10df: cc                           	int3
 11d10e0: 55                           	push	ebp
 11d10e1: 8b ec                        	mov	ebp, esp
 11d10e3: 8b 81 b8 02 00 00            	mov	eax, dword ptr [ecx + 0x2b8]
 11d10e9: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11d10ec: 89 50 0c                     	mov	dword ptr [eax + 0xc], edx
 11d10ef: 8b 81 b8 02 00 00            	mov	eax, dword ptr [ecx + 0x2b8]
 11d10f5: 83 78 38 08                  	cmp	dword ptr [eax + 0x38], 0x8
 11d10f9: 72 13                        	jb	0x11d110e <.text+0x3e>
 11d10fb: 8b 40 24                     	mov	eax, dword ptr [eax + 0x24]
 11d10fe: 8b 89 b8 02 00 00            	mov	ecx, dword ptr [ecx + 0x2b8]
 11d1104: 50                           	push	eax
 11d1105: e8 86 fe ff ff               	call	0x11d0f90
 11d110a: 5d                           	pop	ebp
 11d110b: c2 04 00                     	ret	0x4
 11d110e: 8b 89 b8 02 00 00            	mov	ecx, dword ptr [ecx + 0x2b8]
 11d1114: 83 c0 24                     	add	eax, 0x24
 11d1117: 50                           	push	eax
 11d1118: e8 73 fe ff ff               	call	0x11d0f90
 11d111d: 5d                           	pop	ebp
 11d111e: c2 04 00                     	ret	0x4
 11d1121: cc                           	int3
 11d1122: cc                           	int3
 11d1123: cc                           	int3
 11d1124: cc                           	int3
 11d1125: cc                           	int3
 11d1126: cc                           	int3
 11d1127: cc                           	int3
 11d1128: cc                           	int3
 11d1129: cc                           	int3
 11d112a: cc                           	int3
 11d112b: cc                           	int3
 11d112c: cc                           	int3
 11d112d: cc                           	int3
 11d112e: cc                           	int3
 11d112f: cc                           	int3
 11d1130: 55                           	push	ebp
 11d1131: 8b ec                        	mov	ebp, esp
 11d1133: 83 ec 14                     	sub	esp, 0x14
 11d1136: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11d1139: 53                           	push	ebx
 11d113a: 56                           	push	esi
 11d113b: 8b f1                        	mov	esi, ecx
 11d113d: 8b 08                        	mov	ecx, dword ptr [eax]
 11d113f: 57                           	push	edi
 11d1140: 81 f1 ef be ad de            	xor	ecx, 0xdeadbeef
 11d1146: 81 e1 ff ff ff 7f            	and	ecx, 0x7fffffff
 11d114c: 68 1d f3 01 00               	push	0x1f31d
 11d1151: 51                           	push	ecx
 11d1152: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
 11d1155: c7 45 f8 00 00 00 00         	mov	dword ptr [ebp - 0x8], 0x0
 11d115c: e8 6a 7b 20 00               	call	0x13d8ccb <.text+0x207bfb>
 11d1161: 69 d2 a7 41 00 00            	imul	edx, edx, 0x41a7
 11d1167: 69 c0 14 0b 00 00            	imul	eax, eax, 0xb14
 11d116d: 83 c4 08                     	add	esp, 0x8
 11d1170: 2b d0                        	sub	edx, eax
 11d1172: 79 06                        	jns	0x11d117a <.text+0xaa>
 11d1174: 81 c2 ff ff ff 7f            	add	edx, 0x7fffffff
 11d117a: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
 11d117d: 8b d8                        	mov	ebx, eax
 11d117f: 23 da                        	and	ebx, edx
 11d1181: 39 5e 30                     	cmp	dword ptr [esi + 0x30], ebx
 11d1184: 77 09                        	ja	0x11d118f <.text+0xbf>
 11d1186: d1 e8                        	shr	eax
 11d1188: 83 ca ff                     	or	edx, -0x1
 11d118b: 2b d0                        	sub	edx, eax
 11d118d: 03 da                        	add	ebx, edx
 11d118f: 53                           	push	ebx
 11d1190: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 11d1193: 50                           	push	eax
 11d1194: 8b ce                        	mov	ecx, esi
 11d1196: e8 65 43 36 ff               	call	0x535500
 11d119b: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 11d119e: 8b 75 f4                     	mov	esi, dword ptr [ebp - 0xc]
 11d11a1: 53                           	push	ebx
 11d11a2: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 11d11a5: 51                           	push	ecx
 11d11a6: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11d11a9: e8 02 62 04 00               	call	0x12173b0 <.text+0x462e0>
 11d11ae: 85 ff                        	test	edi, edi
 11d11b0: 74 4c                        	je	0x11d11fe <.text+0x12e>
 11d11b2: 8b 17                        	mov	edx, dword ptr [edi]
 11d11b4: 85 d2                        	test	edx, edx
 11d11b6: 74 46                        	je	0x11d11fe <.text+0x12e>
 11d11b8: 8b 08                        	mov	ecx, dword ptr [eax]
 11d11ba: 85 c9                        	test	ecx, ecx
 11d11bc: 74 02                        	je	0x11d11c0 <.text+0xf0>
 11d11be: 8b 09                        	mov	ecx, dword ptr [ecx]
 11d11c0: 3b d1                        	cmp	edx, ecx
 11d11c2: 75 3a                        	jne	0x11d11fe <.text+0x12e>
 11d11c4: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 11d11c7: 0f 84 88 00 00 00            	je	0x11d1255 <.text+0x185>
 11d11cd: 8b c2                        	mov	eax, edx
 11d11cf: 85                           	<unknown>

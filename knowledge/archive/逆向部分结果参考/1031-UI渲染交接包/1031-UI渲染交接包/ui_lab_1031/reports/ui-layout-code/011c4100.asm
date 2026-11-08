
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c4100 <.text>:
 11c4100: 55                           	push	ebp
 11c4101: 8b ec                        	mov	ebp, esp
 11c4103: 6a ff                        	push	-0x1
 11c4105: 68 f0 7f 4c 01               	push	0x14c7ff0
 11c410a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4110: 50                           	push	eax
 11c4111: 83 ec 24                     	sub	esp, 0x24
 11c4114: 53                           	push	ebx
 11c4115: 56                           	push	esi
 11c4116: 57                           	push	edi
 11c4117: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c411c: 33 c5                        	xor	eax, ebp
 11c411e: 50                           	push	eax
 11c411f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4122: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4128: 8b f9                        	mov	edi, ecx
 11c412a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 11c412d: e8 4e ae ff ff               	call	0x11bef80
 11c4132: 33 db                        	xor	ebx, ebx
 11c4134: c7 07 1c a8 85 01            	mov	dword ptr [edi], 0x185a81c
 11c413a: 8d b7 cc 02 00 00            	lea	esi, [edi + 0x2cc]
 11c4140: 6a 08                        	push	0x8
 11c4142: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11c4145: 89 1e                        	mov	dword ptr [esi], ebx
 11c4147: e8 ce 29 21 00               	call	0x13d6b1a <.text+0x212a1a>
 11c414c: 83 c4 04                     	add	esp, 0x4
 11c414f: 3b c3                        	cmp	eax, ebx
 11c4151: 0f 84 94 01 00 00            	je	0x11c42eb <.text+0x1eb>
 11c4157: 89 06                        	mov	dword ptr [esi], eax
 11c4159: 33 c9                        	xor	ecx, ecx
 11c415b: 89 08                        	mov	dword ptr [eax], ecx
 11c415d: 33 d2                        	xor	edx, edx
 11c415f: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4162: 8b 06                        	mov	eax, dword ptr [esi]
 11c4164: 89 30                        	mov	dword ptr [eax], esi
 11c4166: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c416d: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c4170: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4174: 8d b7 ec 02 00 00            	lea	esi, [edi + 0x2ec]
 11c417a: 6a 08                        	push	0x8
 11c417c: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c4180: 89 1e                        	mov	dword ptr [esi], ebx
 11c4182: e8 93 29 21 00               	call	0x13d6b1a <.text+0x212a1a>
 11c4187: 83 c4 04                     	add	esp, 0x4
 11c418a: 3b c3                        	cmp	eax, ebx
 11c418c: 0f 84 35 01 00 00            	je	0x11c42c7 <.text+0x1c7>
 11c4192: 89 06                        	mov	dword ptr [esi], eax
 11c4194: 33 d2                        	xor	edx, edx
 11c4196: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4199: 33 c9                        	xor	ecx, ecx
 11c419b: 89 08                        	mov	dword ptr [eax], ecx
 11c419d: 8b 16                        	mov	edx, dword ptr [esi]
 11c419f: 89 32                        	mov	dword ptr [edx], esi
 11c41a1: 33 c0                        	xor	eax, eax
 11c41a3: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c41aa: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c41ad: 66 89 46 04                  	mov	word ptr [esi + 0x4], ax
 11c41b1: 8d b7 14 03 00 00            	lea	esi, [edi + 0x314]
 11c41b7: 6a 08                        	push	0x8
 11c41b9: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 11c41bd: 89 1e                        	mov	dword ptr [esi], ebx
 11c41bf: e8 56 29 21 00               	call	0x13d6b1a <.text+0x212a1a>
 11c41c4: 83 c4 04                     	add	esp, 0x4
 11c41c7: 3b c3                        	cmp	eax, ebx
 11c41c9: 0f 84 d4 00 00 00            	je	0x11c42a3 <.text+0x1a3>
 11c41cf: 89 06                        	mov	dword ptr [esi], eax
 11c41d1: 33 c9                        	xor	ecx, ecx
 11c41d3: 89 08                        	mov	dword ptr [eax], ecx
 11c41d5: 33 d2                        	xor	edx, edx
 11c41d7: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c41da: 8b 0e                        	mov	ecx, dword ptr [esi]
 11c41dc: 89 31                        	mov	dword ptr [ecx], esi
 11c41de: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c41e5: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c41e8: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 11c41ec: 8d b7 a4 03 00 00            	lea	esi, [edi + 0x3a4]
 11c41f2: 6a 08                        	push	0x8
 11c41f4: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 11c41f8: 89 1e                        	mov	dword ptr [esi], ebx
 11c41fa: e8 1b 29 21 00               	call	0x13d6b1a <.text+0x212a1a>
 11c41ff: 83 c4 04                     	add	esp, 0x4
 11c4202: 3b c3                        	cmp	eax, ebx
 11c4204: 74 79                        	je	0x11c427f <.text+0x17f>
 11c4206: 89 06                        	mov	dword ptr [esi], eax
 11c4208: 33 c9                        	xor	ecx, ecx
 11c420a: 89 08                        	mov	dword ptr [eax], ecx
 11c420c: 33 d2                        	xor	edx, edx
 11c420e: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4211: 8b 06                        	mov	eax, dword ptr [esi]
 11c4213: 89 30                        	mov	dword ptr [eax], esi
 11c4215: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c421c: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c421f: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4223: 8b cf                        	mov	ecx, edi
 11c4225: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
 11c4229: e8 62 e9 ff ff               	call	0x11c2b90
 11c422e: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11c4231: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11c4234: 8b 17                        	mov	edx, dword ptr [edi]
 11c4236: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11c4239: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11c423f: 53                           	push	ebx
 11c4240: 53                           	push	ebx
 11c4241: 50                           	push	eax
 11c4242: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c4245: 51                           	push	ecx
 11c4246: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11c4249: 50                           	push	eax
 11c424a: 51                           	push	ecx
 11c424b: 56                           	push	esi
 11c424c: 8b cf                        	mov	ecx, edi
 11c424e: ff d2                        	call	edx
 11c4250: 85 c0                        	test	eax, eax
 11c4252: 74 15                        	je	0x11c4269 <.text+0x169>
 11c4254: 3b f3                        	cmp	esi, ebx
 11c4256: 74 11                        	je	0x11c4269 <.text+0x169>
 11c4258: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11c425b: 50                           	push	eax
 11c425c: 8b ce                        	mov	ecx, esi
 11c425e: e8 6d 09 ff ff               	call	0x11b4bd0
 11c4263: 89 87 c8 02 00 00            	mov	dword ptr [edi + 0x2c8], eax
 11c4269: 8b c7                        	mov	eax, edi
 11c426b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c426e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c4275: 59                           	pop	ecx
 11c4276: 5f                           	pop	edi
 11c4277: 5e                           	pop	esi
 11c4278: 5b                           	pop	ebx
 11c4279: 8b e5                        	mov	esp, ebp
 11c427b: 5d                           	pop	ebp
 11c427c: c2 18 00                     	ret	0x18
 11c427f: 8d                           	<unknown>

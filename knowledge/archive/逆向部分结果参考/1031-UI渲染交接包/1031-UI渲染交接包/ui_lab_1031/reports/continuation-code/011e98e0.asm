
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e98e0 <.text>:
 11e98e0: 55                           	push	ebp
 11e98e1: 8b ec                        	mov	ebp, esp
 11e98e3: 6a ff                        	push	-0x1
 11e98e5: 68 e8 a2 4c 01               	push	0x14ca2e8
 11e98ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11e98f0: 50                           	push	eax
 11e98f1: 51                           	push	ecx
 11e98f2: 56                           	push	esi
 11e98f3: 57                           	push	edi
 11e98f4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11e98f9: 33 c5                        	xor	eax, ebp
 11e98fb: 50                           	push	eax
 11e98fc: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11e98ff: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11e9905: 8b f9                        	mov	edi, ecx
 11e9907: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 11e990a: e8 71 56 fd ff               	call	0x11bef80
 11e990f: 33 f6                        	xor	esi, esi
 11e9911: 6a 30                        	push	0x30
 11e9913: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
 11e9916: c7 07 bc ec 85 01            	mov	dword ptr [edi], 0x185ecbc
 11e991c: e8 f9 d1 1e 00               	call	0x13d6b1a <.text+0x1ed23a>
 11e9921: 83 c4 04                     	add	esp, 0x4
 11e9924: 3b c6                        	cmp	eax, esi
 11e9926: 74 25                        	je	0x11e994d <.text+0x6d>
 11e9928: 89 30                        	mov	dword ptr [eax], esi
 11e992a: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
 11e992d: 89 70 08                     	mov	dword ptr [eax + 0x8], esi
 11e9930: 89 70 0c                     	mov	dword ptr [eax + 0xc], esi
 11e9933: 89 70 10                     	mov	dword ptr [eax + 0x10], esi
 11e9936: 89 70 14                     	mov	dword ptr [eax + 0x14], esi
 11e9939: 89 70 18                     	mov	dword ptr [eax + 0x18], esi
 11e993c: 89 70 1c                     	mov	dword ptr [eax + 0x1c], esi
 11e993f: 89 70 20                     	mov	dword ptr [eax + 0x20], esi
 11e9942: 89 70 24                     	mov	dword ptr [eax + 0x24], esi
 11e9945: 89 70 28                     	mov	dword ptr [eax + 0x28], esi
 11e9948: 89 70 2c                     	mov	dword ptr [eax + 0x2c], esi
 11e994b: eb 02                        	jmp	0x11e994f <.text+0x6f>
 11e994d: 33 c0                        	xor	eax, eax
 11e994f: 89 87 b8 02 00 00            	mov	dword ptr [edi + 0x2b8], eax
 11e9955: c7 47 08 03 00 00 00         	mov	dword ptr [edi + 0x8], 0x3
 11e995c: 8b c7                        	mov	eax, edi
 11e995e: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11e9961: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11e9968: 59                           	pop	ecx
 11e9969: 5f                           	pop	edi
 11e996a: 5e                           	pop	esi
 11e996b: 8b e5                        	mov	esp, ebp
 11e996d: 5d                           	pop	ebp
 11e996e: c3                           	ret
 11e996f: cc                           	int3
 11e9970: 55                           	push	ebp
 11e9971: 8b ec                        	mov	ebp, esp
 11e9973: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11e9976: 83 e8 00                     	sub	eax, 0x0
 11e9979: 74 14                        	je	0x11e998f <.text+0xaf>
 11e997b: 48                           	dec	eax
 11e997c: 75 1e                        	jne	0x11e999c <.text+0xbc>
 11e997e: 8b 81 b8 02 00 00            	mov	eax, dword ptr [ecx + 0x2b8]
 11e9984: c7 40 24 01 00 00 00         	mov	dword ptr [eax + 0x24], 0x1
 11e998b: 5d                           	pop	ebp
 11e998c: c2 04 00                     	ret	0x4
 11e998f: 8b 89 b8 02 00 00            	mov	ecx, dword ptr [ecx + 0x2b8]
 11e9995: c7 41 24 00 00 00 00         	mov	dword ptr [ecx + 0x24], 0x0
 11e999c: 5d                           	pop	ebp
 11e999d: c2 04 00                     	ret	0x4
 11e99a0: 55                           	push	ebp
 11e99a1: 8b ec                        	mov	ebp, esp
 11e99a3: 56                           	push	esi
 11e99a4: 8b f1                        	mov	esi, ecx
 11e99a6: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e99ac: 83 38 00                     	cmp	dword ptr [eax], 0x0
 11e99af: 0f 84 d6 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99b5: 83 78 04 00                  	cmp	dword ptr [eax + 0x4], 0x0
 11e99b9: 0f 84 cc 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99bf: 83 78 08 00                  	cmp	dword ptr [eax + 0x8], 0x0
 11e99c3: 0f 84 c2 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99c9: 83 78 0c 00                  	cmp	dword ptr [eax + 0xc], 0x0
 11e99cd: 0f 84 b8 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99d3: 83 78 10 00                  	cmp	dword ptr [eax + 0x10], 0x0
 11e99d7: 0f 84 ae 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99dd: 83 78 14 00                  	cmp	dword ptr [eax + 0x14], 0x0
 11e99e1: 0f 84 a4 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99e7: 83 78 18 00                  	cmp	dword ptr [eax + 0x18], 0x0
 11e99eb: 0f 84 9a 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99f1: 83 78 1c 00                  	cmp	dword ptr [eax + 0x1c], 0x0
 11e99f5: 0f 84 90 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e99fb: 83 78 20 00                  	cmp	dword ptr [eax + 0x20], 0x0
 11e99ff: 0f 84 86 00 00 00            	je	0x11e9a8b <.text+0x1ab>
 11e9a05: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11e9a08: 53                           	push	ebx
 11e9a09: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11e9a0c: 89 58 28                     	mov	dword ptr [eax + 0x28], ebx
 11e9a0f: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a15: 89 51 2c                     	mov	dword ptr [ecx + 0x2c], edx
 11e9a18: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e9a1e: 8b 48 10                     	mov	ecx, dword ptr [eax + 0x10]
 11e9a21: 57                           	push	edi
 11e9a22: e8 59 a3 fc ff               	call	0x11b3d80
 11e9a27: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a2d: 8b 49 14                     	mov	ecx, dword ptr [ecx + 0x14]
 11e9a30: 8b f8                        	mov	edi, eax
 11e9a32: 0f af fb                     	imul	edi, ebx
 11e9a35: e8 46 a3 fc ff               	call	0x11b3d80
 11e9a3a: 8b 96 b8 02 00 00            	mov	edx, dword ptr [esi + 0x2b8]
 11e9a40: 8b 4a 0c                     	mov	ecx, dword ptr [edx + 0xc]
 11e9a43: 03 f8                        	add	edi, eax
 11e9a45: e8 36 a3 fc ff               	call	0x11b3d80
 11e9a4a: 03 f8                        	add	edi, eax
 11e9a4c: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e9a52: 8b 48 10                     	mov	ecx, dword ptr [eax + 0x10]
 11e9a55: e8 36 a3 fc ff               	call	0x11b3d90
 11e9a5a: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a60: 8b 49 1c                     	mov	ecx, dword ptr [ecx + 0x1c]
 11e9a63: 8b d8                        	mov	ebx, eax
 11e9a65: 0f af 5d 0c                  	imul	ebx, dword ptr [ebp + 0xc]
 11e9a69: e8 22 a3 fc ff               	call	0x11b3d90
 11e9a6e: 8b 96 b8 02 00 00            	mov	edx, dword ptr [esi + 0x2b8]
 11e9a74: 8b 4a 04                     	mov	ecx, dword ptr [edx + 0x4]
 11e9a77: 03 d8                        	add	ebx, eax
 11e9a79: e8 12 a3 fc ff               	call	0x11b3d90
 11e9a7e: 03 c3                        	add	eax, ebx

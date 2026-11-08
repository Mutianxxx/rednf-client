
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c44f0 <.text>:
 11c44f0: 55                           	push	ebp
 11c44f1: 8b ec                        	mov	ebp, esp
 11c44f3: 6a ff                        	push	-0x1
 11c44f5: 68 20 80 4c 01               	push	0x14c8020
 11c44fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4500: 50                           	push	eax
 11c4501: 83 ec 1c                     	sub	esp, 0x1c
 11c4504: 53                           	push	ebx
 11c4505: 56                           	push	esi
 11c4506: 57                           	push	edi
 11c4507: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c450c: 33 c5                        	xor	eax, ebp
 11c450e: 50                           	push	eax
 11c450f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4512: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4518: 8b 45 2c                     	mov	eax, dword ptr [ebp + 0x2c]
 11c451b: 8b 75 28                     	mov	esi, dword ptr [ebp + 0x28]
 11c451e: 8b d9                        	mov	ebx, ecx
 11c4520: 8b 4d 30                     	mov	ecx, dword ptr [ebp + 0x30]
 11c4523: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11c4526: 89 4d ec                     	mov	dword ptr [ebp - 0x14], ecx
 11c4529: 8b 15 e4 64 b5 01            	mov	edx, dword ptr [0x1b564e4]
 11c452f: 8b 3a                        	mov	edi, dword ptr [edx]
 11c4531: 68 d8 50 56 01               	push	0x15650d8
 11c4536: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11c453d: e8 ae b9 fd ff               	call	0x119fef0
 11c4542: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 11c4548: 83 c4 04                     	add	esp, 0x4
 11c454b: 50                           	push	eax
 11c454c: 8b 47 10                     	mov	eax, dword ptr [edi + 0x10]
 11c454f: ff d0                        	call	eax
 11c4551: 33 ff                        	xor	edi, edi
 11c4553: 89 83 50 03 00 00            	mov	dword ptr [ebx + 0x350], eax
 11c4559: 39 3d e8 64 b5 01            	cmp	dword ptr [0x1b564e8], edi
 11c455f: 75 59                        	jne	0x11c45ba <.text+0xca>
 11c4561: 68 af 00 00 00               	push	0xaf
 11c4566: 8b c8                        	mov	ecx, eax
 11c4568: e8 63 06 ff ff               	call	0x11b4bd0
 11c456d: 8b c8                        	mov	ecx, eax
 11c456f: e8 4c f8 fe ff               	call	0x11b3dc0
 11c4574: 8b 8b 50 03 00 00            	mov	ecx, dword ptr [ebx + 0x350]
 11c457a: 8b f8                        	mov	edi, eax
 11c457c: 68 b1 00 00 00               	push	0xb1
 11c4581: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 11c4584: e8 47 06 ff ff               	call	0x11b4bd0
 11c4589: 8b c8                        	mov	ecx, eax
 11c458b: e8 30 f8 fe ff               	call	0x11b3dc0
 11c4590: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
 11c4593: 03 c7                        	add	eax, edi
 11c4595: 83 7d 20 08                  	cmp	dword ptr [ebp + 0x20], 0x8
 11c4599: a3 e8 64 b5 01               	mov	dword ptr [0x1b564e8], eax
 11c459e: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c45a1: 73 03                        	jae	0x11c45a6 <.text+0xb6>
 11c45a3: 8d 45 0c                     	lea	eax, [ebp + 0xc]
 11c45a6: 8b 16                        	mov	edx, dword ptr [esi]
 11c45a8: 6a ff                        	push	-0x1
 11c45aa: 50                           	push	eax
 11c45ab: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c45ae: 8b ce                        	mov	ecx, esi
 11c45b0: ff d0                        	call	eax
 11c45b2: 8b f8                        	mov	edi, eax
 11c45b4: 03 7d e4                     	add	edi, dword ptr [ebp - 0x1c]
 11c45b7: 03 7d e8                     	add	edi, dword ptr [ebp - 0x18]
 11c45ba: 8b 4d 34                     	mov	ecx, dword ptr [ebp + 0x34]
 11c45bd: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 11c45c0: 8b 45 f0                     	mov	eax, dword ptr [ebp - 0x10]
 11c45c3: 51                           	push	ecx
 11c45c4: 52                           	push	edx
 11c45c5: 50                           	push	eax
 11c45c6: 56                           	push	esi
 11c45c7: 83 ec 20                     	sub	esp, 0x20
 11c45ca: 8b f4                        	mov	esi, esp
 11c45cc: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
 11c45cf: 6a 08                        	push	0x8
 11c45d1: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 11c45d4: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 11c45da: e8 3b 25 21 00               	call	0x13d6b1a <.text+0x21262a>
 11c45df: 33 c9                        	xor	ecx, ecx
 11c45e1: 83 c4 04                     	add	esp, 0x4
 11c45e4: 3b c1                        	cmp	eax, ecx
 11c45e6: 0f 84 88 00 00 00            	je	0x11c4674 <.text+0x184>
 11c45ec: 89 06                        	mov	dword ptr [esi], eax
 11c45ee: 33 d2                        	xor	edx, edx
 11c45f0: 89 08                        	mov	dword ptr [eax], ecx
 11c45f2: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c45f5: 8b 0e                        	mov	ecx, dword ptr [esi]
 11c45f7: 89 31                        	mov	dword ptr [ecx], esi
 11c45f9: 6a ff                        	push	-0x1
 11c45fb: 52                           	push	edx
 11c45fc: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11c45ff: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c4606: 89 56 14                     	mov	dword ptr [esi + 0x14], edx
 11c4609: 50                           	push	eax
 11c460a: 8b ce                        	mov	ecx, esi
 11c460c: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c4610: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 11c4614: e8 17 0d 24 ff               	call	0x405330
 11c4619: 8b 13                        	mov	edx, dword ptr [ebx]
 11c461b: 8b 82 a4 00 00 00            	mov	eax, dword ptr [edx + 0xa4]
 11c4621: 57                           	push	edi
 11c4622: 8b cb                        	mov	ecx, ebx
 11c4624: c6 45 fc 00                  	mov	byte ptr [ebp - 0x4], 0x0
 11c4628: ff d0                        	call	eax
 11c462a: 83 7d 20 08                  	cmp	dword ptr [ebp + 0x20], 0x8
 11c462e: 8b f0                        	mov	esi, eax
 11c4630: 72 0c                        	jb	0x11c463e <.text+0x14e>
 11c4632: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11c4635: 51                           	push	ecx
 11c4636: e8 ec 14 21 00               	call	0x13d5b27 <.text+0x211637>
 11c463b: 83 c4 04                     	add	esp, 0x4
 11c463e: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11c4641: 33 d2                        	xor	edx, edx
 11c4643: 50                           	push	eax
 11c4644: c7 45 20 07 00 00 00         	mov	dword ptr [ebp + 0x20], 0x7
 11c464b: c7 45 1c 00 00 00 00         	mov	dword ptr [ebp + 0x1c], 0x0
 11c4652: 66 89 55 0c                  	mov	word ptr [ebp + 0xc], dx
 11c4656: e8 cc 14 21 00               	call	0x13d5b27 <.text+0x211637>
 11c465b: 83 c4 04                     	add	esp, 0x4
 11c465e: 8b c6                        	mov	eax, esi
 11c4660: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c4663: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c466a: 59                           	pop	ecx
 11c466b: 5f                           	pop	edi
 11c466c: 5e                           	pop	esi
 11c466d: 5b                           	pop	ebx
 11c466e: 8b e5                        	mov	esp, ebp
 11c4670: 5d                           	pop	ebp
 11c4671: c2 30 00                     	ret	0x30
 11c4674: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 11c4677: 8d 4d f0                     	lea	ecx, [ebp - 0x10]
 11c467a: 51                           	push	ecx
 11c467b: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
 11c467e: e8 47 1e 21 00               	call	0x13d64ca <.text+0x211fda>
 11c4683: 68 90 0f 91 01               	push	0x1910f90
 11c4688: 8d 55 d8                     	lea	edx, [ebp - 0x28]
 11c468b: 52                           	push	edx
 11c468c: c7 45 d8 84 20 56 01         	mov	dword ptr [ebp - 0x28], 0x1562084
 11c4693: e8 02 25 21 00               	call	0x13d6b9a <.text+0x2126aa>
 11c4698: cc                           	int3
 11c4699: cc                           	int3
 11c469a: cc                           	int3
 11c469b: cc                           	int3
 11c469c: cc                           	int3
 11c469d: cc                           	int3
 11c469e: cc                           	int3
 11c469f: cc                           	int3

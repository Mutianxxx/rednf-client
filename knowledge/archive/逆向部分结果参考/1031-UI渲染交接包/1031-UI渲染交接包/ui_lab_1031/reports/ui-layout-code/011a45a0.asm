
<stdin>:	file format elf32-i386

Disassembly of section .text:

011a45a0 <.text>:
 11a45a0: 56                           	push	esi
 11a45a1: 04 8d                        	add	al, -0x73
 11a45a3: 4d                           	dec	ebp
 11a45a4: e0 3b                        	loopne	0x11a45e1 <.text+0x41>
 11a45a6: d1 77 5e                     	<unknown>
 11a45a9: 8b f9                        	mov	edi, ecx
 11a45ab: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11a45ae: 2b fa                        	sub	edi, edx
 11a45b0: c1 ff 02                     	sar	edi, 0x2
 11a45b3: 3b c1                        	cmp	eax, ecx
 11a45b5: 75 3c                        	jne	0x11a45f3 <.text+0x53>
 11a45b7: 2b c2                        	sub	eax, edx
 11a45b9: c1 f8 02                     	sar	eax, 0x2
 11a45bc: 3d fe ff ff 3f               	cmp	eax, 0x3ffffffe
 11a45c1: 0f 87 33 01 00 00            	ja	0x11a46fa <.text+0x15a>
 11a45c7: 2b ca                        	sub	ecx, edx
 11a45c9: 40                           	inc	eax
 11a45ca: c1 f9 02                     	sar	ecx, 0x2
 11a45cd: 3b c1                        	cmp	eax, ecx
 11a45cf: 76 22                        	jbe	0x11a45f3 <.text+0x53>
 11a45d1: 8b d1                        	mov	edx, ecx
 11a45d3: d1 ea                        	shr	edx
 11a45d5: bb ff ff ff 3f               	mov	ebx, 0x3fffffff
 11a45da: 2b da                        	sub	ebx, edx
 11a45dc: 3b d9                        	cmp	ebx, ecx
 11a45de: 73 04                        	jae	0x11a45e4 <.text+0x44>
 11a45e0: 33 c9                        	xor	ecx, ecx
 11a45e2: eb 02                        	jmp	0x11a45e6 <.text+0x46>
 11a45e4: 03 ca                        	add	ecx, edx
 11a45e6: 3b c8                        	cmp	ecx, eax
 11a45e8: 0f 42 c8                     	cmovb	ecx, eax
 11a45eb: 51                           	push	ecx
 11a45ec: 8b ce                        	mov	ecx, esi
 11a45ee: e8 0d 9a 55 ff               	call	0x6fe000
 11a45f3: 8b 5e 08                     	mov	ebx, dword ptr [esi + 0x8]
 11a45f6: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 11a45f9: 8d 04 ba                     	lea	eax, [edx + 4*edi]
 11a45fc: 85 db                        	test	ebx, ebx
 11a45fe: 74 63                        	je	0x11a4663 <.text+0xc3>
 11a4600: 8b 38                        	mov	edi, dword ptr [eax]
 11a4602: 83 ef 08                     	sub	edi, 0x8
 11a4605: eb 50                        	jmp	0x11a4657 <.text+0xb7>
 11a4607: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11a460a: 3b c1                        	cmp	eax, ecx
 11a460c: 75 3f                        	jne	0x11a464d <.text+0xad>
 11a460e: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 11a4611: 2b c2                        	sub	eax, edx
 11a4613: c1 f8 02                     	sar	eax, 0x2
 11a4616: 3d fe ff ff 3f               	cmp	eax, 0x3ffffffe
 11a461b: 0f 87 d9 00 00 00            	ja	0x11a46fa <.text+0x15a>
 11a4621: 2b ca                        	sub	ecx, edx
 11a4623: 40                           	inc	eax
 11a4624: c1 f9 02                     	sar	ecx, 0x2
 11a4627: 3b c1                        	cmp	eax, ecx
 11a4629: 76 22                        	jbe	0x11a464d <.text+0xad>
 11a462b: 8b d1                        	mov	edx, ecx
 11a462d: d1 ea                        	shr	edx
 11a462f: bb ff ff ff 3f               	mov	ebx, 0x3fffffff
 11a4634: 2b da                        	sub	ebx, edx
 11a4636: 3b d9                        	cmp	ebx, ecx
 11a4638: 73 04                        	jae	0x11a463e <.text+0x9e>
 11a463a: 33 c9                        	xor	ecx, ecx
 11a463c: eb 02                        	jmp	0x11a4640 <.text+0xa0>
 11a463e: 03 ca                        	add	ecx, edx
 11a4640: 3b c8                        	cmp	ecx, eax
 11a4642: 0f 42 c8                     	cmovb	ecx, eax
 11a4645: 51                           	push	ecx
 11a4646: 8b ce                        	mov	ecx, esi
 11a4648: e8 b3 99 55 ff               	call	0x6fe000
 11a464d: 8b 5e 08                     	mov	ebx, dword ptr [esi + 0x8]
 11a4650: 85 db                        	test	ebx, ebx
 11a4652: 74 0f                        	je	0x11a4663 <.text+0xc3>
 11a4654: 83 c7 f8                     	add	edi, -0x8
 11a4657: 57                           	push	edi
 11a4658: ff 15 5c a2 55 01            	call	dword ptr [0x155a25c]
 11a465e: 83 c7 08                     	add	edi, 0x8
 11a4661: 89 3b                        	mov	dword ptr [ebx], edi
 11a4663: 8b 7d e0                     	mov	edi, dword ptr [ebp - 0x20]
 11a4666: 83 46 08 04                  	add	dword ptr [esi + 0x8], 0x4
 11a466a: 83 c7 f8                     	add	edi, -0x8
 11a466d: 57                           	push	edi
 11a466e: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11a4675: ff 15 58 a2 55 01            	call	dword ptr [0x155a258]
 11a467b: 85 c0                        	test	eax, eax
 11a467d: 7f 09                        	jg	0x11a4688 <.text+0xe8>
 11a467f: 57                           	push	edi
 11a4680: e8 42 5d 23 00               	call	0x13da3c7 <.text+0x235e27>
 11a4685: 83 c4 04                     	add	esp, 0x4
 11a4688: ff 45 f0                     	inc	dword ptr [ebp - 0x10]
 11a468b: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 11a468e: 42                           	inc	edx
 11a468f: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 11a4692: 40                           	inc	eax
 11a4693: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 11a4696: 3b 45 d8                     	cmp	eax, dword ptr [ebp - 0x28]
 11a4699: 0f 8c 31 fa ff ff            	jl	0x11a40d0
 11a469f: 8b 45 d8                     	mov	eax, dword ptr [ebp - 0x28]
 11a46a2: 3b d0                        	cmp	edx, eax
 11a46a4: 0f 84 a1 00 00 00            	je	0x11a474b <.text+0x1ab>
 11a46aa: 8b 45 d8                     	mov	eax, dword ptr [ebp - 0x28]
 11a46ad: 2b c2                        	sub	eax, edx
 11a46af: 50                           	push	eax
 11a46b0: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11a46b3: 52                           	push	edx
 11a46b4: 50                           	push	eax
 11a46b5: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
 11a46b8: 51                           	push	ecx
 11a46b9: e8 f2 f2 ff ff               	call	0x11a39b0
 11a46be: 83 c4 10                     	add	esp, 0x10
 11a46c1: 8b f8                        	mov	edi, eax
 11a46c3: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
 11a46c6: c7 45 fc 05 00 00 00         	mov	dword ptr [ebp - 0x4], 0x5
 11a46cd: 3b f8                        	cmp	edi, eax
 11a46cf: 73 33                        	jae	0x11a4704 <.text+0x164>
 11a46d1: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11a46d4: 3b cf                        	cmp	ecx, edi
 11a46d6: 77 2c                        	ja	0x11a4704 <.text+0x164>
 11a46d8: 2b f9                        	sub	edi, ecx
 11a46da: c1 ff 02                     	sar	edi, 0x2
 11a46dd: 3b 46 0c                     	cmp	eax, dword ptr [esi + 0xc]
 11a46e0: 75 09                        	jne	0x11a46eb <.text+0x14b>
 11a46e2: 6a 01                        	push	0x1
 11a46e4: 8b ce                        	mov	ecx, esi
 11a46e6: e8 15 9a 55 ff               	call	0x6fe100
 11a46eb: 8b 5e 08                     	mov	ebx, dword ptr [esi + 0x8]
 11a46ee: 85 db                        	test	ebx, ebx
 11a46f0: 74 38                        	je	0x11a472a <.text+0x18a>
 11a46f2: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 11a46f5: 8b 3c ba                     	mov	edi, dword ptr [edx + 4*edi]
 11a46f8: eb 21                        	jmp	0x11a471b <.text+0x17b>
 11a46fa: 68 6c 20 56 01               	push	0x156206c
 11a46ff: e8 c6 d0 21 00               	call	0x13c17ca <.text+0x21d22a>
 11a4704: 3b 46 0c                     	cmp	eax, dword ptr [esi + 0xc]
 11a4707: 75 09                        	jne	0x11a4712 <.text+0x172>
 11a4709: 6a 01                        	push	0x1
 11a470b: 8b ce                        	mov	ecx, esi
 11a470d: e8 ee 99 55 ff               	call	0x6fe100
 11a4712: 8b 5e 08                     	mov	ebx, dword ptr [esi + 0x8]
 11a4715: 85 db                        	test	ebx, ebx
 11a4717: 74 11                        	je	0x11a472a <.text+0x18a>
 11a4719: 8b 3f                        	mov	edi, dword ptr [edi]
 11a471b: 83 ef 08                     	sub	edi, 0x8
 11a471e: 57                           	push	edi
 11a471f: ff 15 5c a2 55 01            	call	dword ptr [0x155a25c]
 11a4725: 83 c7 08                     	add	edi, 0x8
 11a4728: 89 3b                        	mov	dword ptr [ebx], edi
 11a472a: 83 46 08 04                  	add	dword ptr [esi + 0x8], 0x4
 11a472e: 8b 75                        	<unknown>

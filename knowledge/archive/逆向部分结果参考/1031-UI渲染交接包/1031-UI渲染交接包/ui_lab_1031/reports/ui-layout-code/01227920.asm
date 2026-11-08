
<stdin>:	file format elf32-i386

Disassembly of section .text:

01227920 <.text>:
 1227920: 55                           	push	ebp
 1227921: 8b ec                        	mov	ebp, esp
 1227923: 6a ff                        	push	-0x1
 1227925: 68 4b cf 42 01               	push	0x142cf4b
 122792a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1227930: 50                           	push	eax
 1227931: 81 ec 2c 08 00 00            	sub	esp, 0x82c
 1227937: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 122793c: 33 c5                        	xor	eax, ebp
 122793e: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 1227941: 56                           	push	esi
 1227942: 57                           	push	edi
 1227943: 50                           	push	eax
 1227944: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1227947: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 122794d: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1227950: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 1227953: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 1227956: 85 c0                        	test	eax, eax
 1227958: 0f 84 de 01 00 00            	je	0x1227b3c <.text+0x21c>
 122795e: 85 f6                        	test	esi, esi
 1227960: 0f 84 d6 01 00 00            	je	0x1227b3c <.text+0x21c>
 1227966: 85 ff                        	test	edi, edi
 1227968: 0f 84 ce 01 00 00            	je	0x1227b3c <.text+0x21c>
 122796e: 50                           	push	eax
 122796f: 8d 8d d0 f7 ff ff            	lea	ecx, [ebp - 0x830]
 1227975: e8 a6 a5 1e ff               	call	0x411f20
 122797a: 8b c6                        	mov	eax, esi
 122797c: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 1227983: 8d 50 02                     	lea	edx, [eax + 0x2]
 1227986: 66 8b 08                     	mov	cx, word ptr [eax]
 1227989: 83 c0 02                     	add	eax, 0x2
 122798c: 66 85 c9                     	test	cx, cx
 122798f: 75 f5                        	jne	0x1227986 <.text+0x66>
 1227991: 2b c2                        	sub	eax, edx
 1227993: d1 f8                        	sar	eax
 1227995: 50                           	push	eax
 1227996: 56                           	push	esi
 1227997: 8d 8d d0 f7 ff ff            	lea	ecx, [ebp - 0x830]
 122799d: e8 8e 8d 1e ff               	call	0x410730
 12279a2: 8b cf                        	mov	ecx, edi
 12279a4: e8 c7 fc f7 ff               	call	0x11a7670
 12279a9: 68 9c 44 86 01               	push	0x186449c
 12279ae: e8 3d 85 f7 ff               	call	0x119fef0
 12279b3: 8b c8                        	mov	ecx, eax
 12279b5: 83 c4 04                     	add	esp, 0x4
 12279b8: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12279bb: eb 03                        	jmp	0x12279c0 <.text+0xa0>
 12279bd: 8d 49 00                     	lea	ecx, [ecx]
 12279c0: 66 8b 11                     	mov	dx, word ptr [ecx]
 12279c3: 83 c1 02                     	add	ecx, 0x2
 12279c6: 66 85 d2                     	test	dx, dx
 12279c9: 75 f5                        	jne	0x12279c0 <.text+0xa0>
 12279cb: 2b ce                        	sub	ecx, esi
 12279cd: d1 f9                        	sar	ecx
 12279cf: 51                           	push	ecx
 12279d0: 50                           	push	eax
 12279d1: 8b 85 e4 f7 ff ff            	mov	eax, dword ptr [ebp - 0x81c]
 12279d7: 50                           	push	eax
 12279d8: 6a 00                        	push	0x0
 12279da: 8d 8d d0 f7 ff ff            	lea	ecx, [ebp - 0x830]
 12279e0: e8 4b a2 1d ff               	call	0x401c30
 12279e5: be 08 00 00 00               	mov	esi, 0x8
 12279ea: 85 c0                        	test	eax, eax
 12279ec: 75 33                        	jne	0x1227a21 <.text+0x101>
 12279ee: 68 10 44 86 01               	push	0x1864410
 12279f3: e8 f8 84 f7 ff               	call	0x119fef0
 12279f8: 83 c4 04                     	add	esp, 0x4
 12279fb: 50                           	push	eax
 12279fc: 57                           	push	edi
 12279fd: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1227a02: e8 e9 fa f7 ff               	call	0x11a74f0
 1227a07: 84 c0                        	test	al, al
 1227a09: 0f 84 fe 00 00 00            	je	0x1227b0d <.text+0x1ed>
 1227a0f: 8d 8d d0 f7 ff ff            	lea	ecx, [ebp - 0x830]
 1227a15: e8 d6 0b 23 ff               	call	0x4585f0
 1227a1a: b0 01                        	mov	al, 0x1
 1227a1c: e9 1d 01 00 00               	jmp	0x1227b3e <.text+0x21e>
 1227a21: 8b 85 d4 f7 ff ff            	mov	eax, dword ptr [ebp - 0x82c]
 1227a27: c7 85 cc f7 ff ff 00 00 00 00	mov	dword ptr [ebp - 0x834], 0x0
 1227a31: 39 b5 e8 f7 ff ff            	cmp	dword ptr [ebp - 0x818], esi
 1227a37: 73 06                        	jae	0x1227a3f <.text+0x11f>
 1227a39: 8d 85 d4 f7 ff ff            	lea	eax, [ebp - 0x82c]
 1227a3f: 8d 8d c8 f7 ff ff            	lea	ecx, [ebp - 0x838]
 1227a45: 51                           	push	ecx
 1227a46: 8d 95 cc f7 ff ff            	lea	edx, [ebp - 0x834]
 1227a4c: 52                           	push	edx
 1227a4d: 50                           	push	eax
 1227a4e: b9 d0 72 d2 01               	mov	ecx, 0x1d272d0
 1227a53: e8 e8 50 f8 ff               	call	0x11acb40
 1227a58: 83 f8 01                     	cmp	eax, 0x1
 1227a5b: 75 7c                        	jne	0x1227ad9 <.text+0x1b9>
 1227a5d: 8b 85 d4 f7 ff ff            	mov	eax, dword ptr [ebp - 0x82c]
 1227a63: 39 b5 e8 f7 ff ff            	cmp	dword ptr [ebp - 0x818], esi
 1227a69: 73 06                        	jae	0x1227a71 <.text+0x151>
 1227a6b: 8d 85 d4 f7 ff ff            	lea	eax, [ebp - 0x82c]
 1227a71: 68 00 04 00 00               	push	0x400
 1227a76: 50                           	push	eax
 1227a77: 8d 85 f0 f7 ff ff            	lea	eax, [ebp - 0x810]
 1227a7d: 50                           	push	eax
 1227a7e: e8 f5 59 1b 00               	call	0x13dd478 <.text+0x1b5b58>
 1227a83: 8d 8d f0 f7 ff ff            	lea	ecx, [ebp - 0x810]
 1227a89: 51                           	push	ecx
 1227a8a: e8 41 f7 ff ff               	call	0x12271d0
 1227a8f: 83 c4 10                     	add	esp, 0x10
 1227a92: 84 c0                        	test	al, al
 1227a94: 74 64                        	je	0x1227afa <.text+0x1da>
 1227a96: 8d 95 f0 f7 ff ff            	lea	edx, [ebp - 0x810]
 1227a9c: 52                           	push	edx
 1227a9d: 8d 8d d0 f7 ff ff            	lea	ecx, [ebp - 0x830]
 1227aa3: e8 28 91 1e ff               	call	0x410bd0
 1227aa8: 8b 85 d4 f7 ff ff            	mov	eax, dword ptr [ebp - 0x82c]
 1227aae: 39 b5 e8 f7 ff ff            	cmp	dword ptr [ebp - 0x818], esi
 1227ab4: 73 06                        	jae	0x1227abc <.text+0x19c>
 1227ab6: 8d 85 d4 f7 ff ff            	lea	eax, [ebp - 0x82c]
 1227abc: 8d 8d c8 f7 ff ff            	lea	ecx, [ebp - 0x838]
 1227ac2: 51                           	push	ecx
 1227ac3: 8d 95 cc f7 ff ff            	lea	edx, [ebp - 0x834]
 1227ac9: 52                           	push	edx
 1227aca: 50                           	push	eax
 1227acb: b9 d0 72 d2 01               	mov	ecx, 0x1d272d0

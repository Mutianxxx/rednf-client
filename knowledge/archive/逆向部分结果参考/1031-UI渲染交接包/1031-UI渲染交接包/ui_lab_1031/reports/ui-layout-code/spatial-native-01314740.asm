
<stdin>:	file format elf32-i386

Disassembly of section .text:

01314740 <.text>:
 1314740: 55                           	push	ebp
 1314741: 8b ec                        	mov	ebp, esp
 1314743: 6a ff                        	push	-0x1
 1314745: 68 62 59 42 01               	push	0x1425962
 131474a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1314750: 50                           	push	eax
 1314751: 51                           	push	ecx
 1314752: 56                           	push	esi
 1314753: 57                           	push	edi
 1314754: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1314759: 33 c5                        	xor	eax, ebp
 131475b: 50                           	push	eax
 131475c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 131475f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1314765: 8b f9                        	mov	edi, ecx
 1314767: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 131476a: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 131476d: 3b f1                        	cmp	esi, ecx
 131476f: 73 48                        	jae	0x13147b9 <.text+0x79>
 1314771: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
 1314774: 3b c6                        	cmp	eax, esi
 1314776: 77 41                        	ja	0x13147b9 <.text+0x79>
 1314778: 2b f0                        	sub	esi, eax
 131477a: b8 67 66 66 66               	mov	eax, 0x66666667
 131477f: f7 ee                        	imul	esi
 1314781: c1 fa 05                     	sar	edx, 0x5
 1314784: 8b f2                        	mov	esi, edx
 1314786: c1 ee 1f                     	shr	esi, 0x1f
 1314789: 03 f2                        	add	esi, edx
 131478b: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 131478e: 75 09                        	jne	0x1314799 <.text+0x59>
 1314790: 6a 01                        	push	0x1
 1314792: 8b cf                        	mov	ecx, edi
 1314794: e8 17 ff ff ff               	call	0x13146b0
 1314799: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 131479c: 8d 04 b6                     	lea	eax, [esi + 4*esi]
 131479f: c1 e0 04                     	shl	eax, 0x4
 13147a2: 03 47 04                     	add	eax, dword ptr [edi + 0x4]
 13147a5: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 13147a8: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 13147ab: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 13147b2: 85 c9                        	test	ecx, ecx
 13147b4: 74 2b                        	je	0x13147e1 <.text+0xa1>
 13147b6: 50                           	push	eax
 13147b7: eb 23                        	jmp	0x13147dc <.text+0x9c>
 13147b9: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 13147bc: 75 09                        	jne	0x13147c7 <.text+0x87>
 13147be: 6a 01                        	push	0x1
 13147c0: 8b cf                        	mov	ecx, edi
 13147c2: e8 e9 fe ff ff               	call	0x13146b0
 13147c7: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 13147ca: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 13147cd: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 13147d0: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 13147d7: 85 c9                        	test	ecx, ecx
 13147d9: 74 06                        	je	0x13147e1 <.text+0xa1>
 13147db: 56                           	push	esi
 13147dc: e8 ef f9 ff ff               	call	0x13141d0
 13147e1: 83 47 08 50                  	add	dword ptr [edi + 0x8], 0x50
 13147e5: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 13147e8: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 13147ef: 59                           	pop	ecx
 13147f0: 5f                           	pop	edi
 13147f1: 5e                           	pop	esi
 13147f2: 8b e5                        	mov	esp, ebp
 13147f4: 5d                           	pop	ebp
 13147f5: c2 04 00                     	ret	0x4

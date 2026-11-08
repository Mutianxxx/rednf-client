
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111f930 <.text>:
 111f930: 8b 55 f0                     	mov	edx, dword ptr [ebp - 0x10]
 111f933: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 111f936: 3b d1                        	cmp	edx, ecx
 111f938: 7c 06                        	jl	0x111f940 <.text+0x10>
 111f93a: 03 c1                        	add	eax, ecx
 111f93c: 3b d0                        	cmp	edx, eax
 111f93e: 7c 1d                        	jl	0x111f95d <.text+0x2d>
 111f940: 83 45 fc 6c                  	add	dword ptr [ebp - 0x4], 0x6c
 111f944: 43                           	inc	ebx
 111f945: 3b 5d e8                     	cmp	ebx, dword ptr [ebp - 0x18]
 111f948: 0f 8c b2 fe ff ff            	jl	0x111f800
 111f94e: 5b                           	pop	ebx
 111f94f: 5f                           	pop	edi
 111f950: 83 c8 ff                     	or	eax, -0x1
 111f953: 5e                           	pop	esi
 111f954: 8b e5                        	mov	esp, ebp
 111f956: 5d                           	pop	ebp
 111f957: c3                           	ret
 111f958: e8 4a 74 2b 00               	call	0x13d6da7 <.text+0x2b7477>
 111f95d: 8b c3                        	mov	eax, ebx
 111f95f: 5b                           	pop	ebx
 111f960: 5f                           	pop	edi
 111f961: 5e                           	pop	esi
 111f962: 8b e5                        	mov	esp, ebp
 111f964: 5d                           	pop	ebp
 111f965: c3                           	ret
 111f966: 8b 8f b0 03 00 00            	mov	ecx, dword ptr [edi + 0x3b0]
 111f96c: 3b cb                        	cmp	ecx, ebx
 111f96e: 74 de                        	je	0x111f94e <.text+0x1e>
 111f970: e8 3b 32 f8 ff               	call	0x10a2bb0
 111f975: 85 c0                        	test	eax, eax
 111f977: 74 d5                        	je	0x111f94e <.text+0x1e>
 111f979: 8b 8f b0 03 00 00            	mov	ecx, dword ptr [edi + 0x3b0]
 111f97f: e8 2c 32 f8 ff               	call	0x10a2bb0
 111f984: 8b c8                        	mov	ecx, eax
 111f986: e8 b5 76 5d ff               	call	0x6f7040
 111f98b: 8b d8                        	mov	ebx, eax
 111f98d: 8d 55 dc                     	lea	edx, [ebp - 0x24]
 111f990: 52                           	push	edx
 111f991: 8b cb                        	mov	ecx, ebx
 111f993: e8 78 dd 1f 00               	call	0x131d710 <.text+0x1fdde0>
 111f998: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 111f99b: 50                           	push	eax
 111f99c: 8b cb                        	mov	ecx, ebx
 111f99e: e8 cd 67 05 00               	call	0x1176170 <.text+0x56840>
 111f9a3: 8b 7d dc                     	mov	edi, dword ptr [ebp - 0x24]
 111f9a6: 85 ff                        	test	edi, edi
 111f9a8: 74 ae                        	je	0x111f958 <.text+0x28>
 111f9aa: 8b 17                        	mov	edx, dword ptr [edi]
 111f9ac: 85 d2                        	test	edx, edx
 111f9ae: 74 a8                        	je	0x111f958 <.text+0x28>
 111f9b0: 8b 08                        	mov	ecx, dword ptr [eax]
 111f9b2: 85 c9                        	test	ecx, ecx
 111f9b4: 74 02                        	je	0x111f9b8 <.text+0x88>
 111f9b6: 8b 09                        	mov	ecx, dword ptr [ecx]
 111f9b8: 3b d1                        	cmp	edx, ecx
 111f9ba: 75 9c                        	jne	0x111f958 <.text+0x28>
 111f9bc: 8b 75 e4                     	mov	esi, dword ptr [ebp - 0x1c]
 111f9bf: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 111f9c2: 74 8a                        	je	0x111f94e <.text+0x1e>
 111f9c4: 8b c2                        	mov	eax, edx
 111f9c6: 85 c0                        	test	eax, eax
 111f9c8: 74 8e                        	je	0x111f958 <.text+0x28>
 111f9ca: 85 f6                        	test	esi, esi
 111f9cc: 74 8a                        	je	0x111f958 <.text+0x28>
 111f9ce: 3b 70                        	<unknown>

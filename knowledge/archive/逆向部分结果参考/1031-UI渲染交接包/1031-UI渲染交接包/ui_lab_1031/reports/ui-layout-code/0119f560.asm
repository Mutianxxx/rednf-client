
<stdin>:	file format elf32-i386

Disassembly of section .text:

0119f560 <.text>:
 119f560: 55                           	push	ebp
 119f561: 8b ec                        	mov	ebp, esp
 119f563: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 119f566: 8b c8                        	mov	ecx, eax
 119f568: 56                           	push	esi
 119f569: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 119f56c: 83 e0 03                     	and	eax, 0x3
 119f56f: c1 e9 02                     	shr	ecx, 0x2
 119f572: 57                           	push	edi
 119f573: 8b f8                        	mov	edi, eax
 119f575: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
 119f578: 85 c9                        	test	ecx, ecx
 119f57a: 74 20                        	je	0x119f59c <.text+0x3c>
 119f57c: 53                           	push	ebx
 119f57d: 8b d9                        	mov	ebx, ecx
 119f57f: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 119f582: 8b 16                        	mov	edx, dword ptr [esi]
 119f584: 33 d0                        	xor	edx, eax
 119f586: 69 c0 3f 00 01 00            	imul	eax, eax, 0x1003f
 119f58c: 89 11                        	mov	dword ptr [ecx], edx
 119f58e: 03 c2                        	add	eax, edx
 119f590: 83 c6 04                     	add	esi, 0x4
 119f593: 83 c1 04                     	add	ecx, 0x4
 119f596: 4b                           	dec	ebx
 119f597: 75 e9                        	jne	0x119f582 <.text+0x22>
 119f599: 5b                           	pop	ebx
 119f59a: eb 03                        	jmp	0x119f59f <.text+0x3f>
 119f59c: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 119f59f: 85 ff                        	test	edi, edi
 119f5a1: 74 18                        	je	0x119f5bb <.text+0x5b>
 119f5a3: 2b f1                        	sub	esi, ecx
 119f5a5: 8a 14 0e                     	mov	dl, byte ptr [esi + ecx]
 119f5a8: 32 d0                        	xor	dl, al
 119f5aa: 69 c0 07 01 00 00            	imul	eax, eax, 0x107
 119f5b0: 88 11                        	mov	byte ptr [ecx], dl
 119f5b2: 0f b6 d2                     	movzx	edx, dl
 119f5b5: 03 c2                        	add	eax, edx
 119f5b7: 41                           	inc	ecx
 119f5b8: 4f                           	dec	edi
 119f5b9: 75 ea                        	jne	0x119f5a5 <.text+0x45>
 119f5bb: 5f                           	pop	edi
 119f5bc: 5e                           	pop	esi
 119f5bd: 5d                           	pop	ebp
 119f5be: c3                           	ret
 119f5bf: cc                           	int3

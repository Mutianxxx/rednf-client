
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be370 <.text>:
 11be370: 55                           	push	ebp
 11be371: 8b ec                        	mov	ebp, esp
 11be373: 8b 41 74                     	mov	eax, dword ptr [ecx + 0x74]
 11be376: 85 c0                        	test	eax, eax
 11be378: 74 27                        	je	0x11be3a1 <.text+0x31>
 11be37a: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11be37d: 56                           	push	esi
 11be37e: 8b f2                        	mov	esi, edx
 11be380: 2b 71 38                     	sub	esi, dword ptr [ecx + 0x38]
 11be383: 57                           	push	edi
 11be384: 01 70 08                     	add	dword ptr [eax + 0x8], esi
 11be387: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 11be38a: 8b 41 74                     	mov	eax, dword ptr [ecx + 0x74]
 11be38d: 8b fe                        	mov	edi, esi
 11be38f: 2b 79 3c                     	sub	edi, dword ptr [ecx + 0x3c]
 11be392: 01 78 0c                     	add	dword ptr [eax + 0xc], edi
 11be395: 5f                           	pop	edi
 11be396: 89 71 3c                     	mov	dword ptr [ecx + 0x3c], esi
 11be399: 89 51 38                     	mov	dword ptr [ecx + 0x38], edx
 11be39c: 5e                           	pop	esi
 11be39d: 5d                           	pop	ebp
 11be39e: c2 08 00                     	ret	0x8
 11be3a1: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11be3a4: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11be3a7: 89 41 38                     	mov	dword ptr [ecx + 0x38], eax
 11be3aa: 89 51 3c                     	mov	dword ptr [ecx + 0x3c], edx
 11be3ad: 5d                           	pop	ebp
 11be3ae: c2 08 00                     	ret	0x8
 11be3b1: cc                           	int3
 11be3b2: cc                           	int3
 11be3b3: cc                           	int3
 11be3b4: cc                           	int3
 11be3b5: cc                           	int3
 11be3b6: cc                           	int3
 11be3b7: cc                           	int3
 11be3b8: cc                           	int3
 11be3b9: cc                           	int3
 11be3ba: cc                           	int3
 11be3bb: cc                           	int3
 11be3bc: cc                           	int3
 11be3bd: cc                           	int3
 11be3be: cc                           	int3
 11be3bf: cc                           	int3
 11be3c0: 80 79 0c 00                  	cmp	byte ptr [ecx + 0xc], 0x0
 11be3c4: 8b 01                        	mov	eax, dword ptr [ecx]
 11be3c6: 8b 40 10                     	mov	eax, dword ptr [eax + 0x10]
 11be3c9: 0f 94 c2                     	sete	dl
 11be3cc: 0f b6 d2                     	movzx	edx, dl
 11be3cf: 52                           	push	edx

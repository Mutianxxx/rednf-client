
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

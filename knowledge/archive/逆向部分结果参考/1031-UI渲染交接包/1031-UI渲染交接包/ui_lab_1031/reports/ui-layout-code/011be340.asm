
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be340 <.text>:
 11be340: 08 5d c3                     	or	byte ptr [ebp - 0x3d], bl
 11be343: cc                           	int3
 11be344: cc                           	int3
 11be345: cc                           	int3
 11be346: cc                           	int3
 11be347: cc                           	int3
 11be348: cc                           	int3
 11be349: cc                           	int3
 11be34a: cc                           	int3
 11be34b: cc                           	int3
 11be34c: cc                           	int3
 11be34d: cc                           	int3
 11be34e: cc                           	int3
 11be34f: cc                           	int3
 11be350: 55                           	push	ebp
 11be351: 8b ec                        	mov	ebp, esp
 11be353: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11be356: 88 41 0d                     	mov	byte ptr [ecx + 0xd], al
 11be359: 5d                           	pop	ebp
 11be35a: c2 04 00                     	ret	0x4
 11be35d: cc                           	int3
 11be35e: cc                           	int3
 11be35f: cc                           	int3
 11be360: 55                           	push	ebp
 11be361: 8b ec                        	mov	ebp, esp
 11be363: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11be366: 88 41 0f                     	mov	byte ptr [ecx + 0xf], al
 11be369: 5d                           	pop	ebp
 11be36a: c2 04 00                     	ret	0x4
 11be36d: cc                           	int3
 11be36e: cc                           	int3
 11be36f: cc                           	int3
 11be370: 55                           	push	ebp
 11be371: 8b ec                        	mov	ebp, esp
 11be373: 8b 41 74                     	mov	eax, dword ptr [ecx + 0x74]
 11be376: 85 c0                        	test	eax, eax
 11be378: 74 27                        	je	0x11be3a1 <.text+0x61>
 11be37a: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11be37d: 56                           	push	esi
 11be37e: 8b f2                        	mov	esi, edx
 11be380: 2b 71 38                     	sub	esi, dword ptr [ecx + 0x38]
 11be383: 57                           	push	edi
 11be384: 01 70 08                     	add	dword ptr [eax + 0x8], esi
 11be387: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 11be38a: 8b 41 74                     	mov	eax, dword ptr [ecx + 0x74]
 11be38d: 8b fe                        	mov	edi, esi
 11be38f: 2b                           	<unknown>


<stdin>:	file format elf32-i386

Disassembly of section .text:

011be300 <.text>:
 11be300: 8b 41 18                     	mov	eax, dword ptr [ecx + 0x18]
 11be303: c3                           	ret
 11be304: cc                           	int3
 11be305: cc                           	int3
 11be306: cc                           	int3
 11be307: cc                           	int3
 11be308: cc                           	int3
 11be309: cc                           	int3
 11be30a: cc                           	int3
 11be30b: cc                           	int3
 11be30c: cc                           	int3
 11be30d: cc                           	int3
 11be30e: cc                           	int3
 11be30f: cc                           	int3
 11be310: 55                           	push	ebp
 11be311: 8b ec                        	mov	ebp, esp
 11be313: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11be316: 49                           	dec	ecx
 11be317: b8 20 03 00 00               	mov	eax, 0x320
 11be31c: 75 05                        	jne	0x11be323 <.text+0x23>
 11be31e: b8 58 02 00 00               	mov	eax, 0x258
 11be323: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11be326: 49                           	dec	ecx
 11be327: 74 0c                        	je	0x11be335 <.text+0x35>
 11be329: 49                           	dec	ecx
 11be32a: 75 15                        	jne	0x11be341 <.text+0x41>
 11be32c: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11be32f: 2b 01                        	sub	eax, dword ptr [ecx]
 11be331: 89 01                        	mov	dword ptr [ecx], eax
 11be333: 5d                           	pop	ebp
 11be334: c3                           	ret
 11be335: 99                           	cdq
 11be336: 2b c2                        	sub	eax, edx
 11be338: 8b c8                        	mov	ecx, eax
 11be33a: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11be33d: d1 f9                        	sar	ecx
 11be33f: 01 08                        	add	dword ptr [eax], ecx
 11be341: 5d                           	pop	ebp
 11be342: c3                           	ret
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
 11be378: 74 27                        	je	0x11be3a1 <.text+0xa1>
 11be37a: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11be37d: 56                           	push	esi
 11be37e: 8b f2                        	mov	esi, edx

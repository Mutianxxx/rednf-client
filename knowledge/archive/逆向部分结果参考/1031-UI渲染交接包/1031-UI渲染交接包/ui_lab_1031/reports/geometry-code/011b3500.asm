
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3500 <.text>:
 11b3500: e8 2b 9f 39 ff               	call	0x54d430
 11b3505: 5d                           	pop	ebp
 11b3506: c3                           	ret
 11b3507: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11b350a: 8b 0d 10 96 b2 01            	mov	ecx, dword ptr [0x1b29610]
 11b3510: 50                           	push	eax
 11b3511: 6a 01                        	push	0x1
 11b3513: e8 98 e1 03 00               	call	0x11f16b0 <.text+0x3e1b0>
 11b3518: 8d 55 08                     	lea	edx, [ebp + 0x8]
 11b351b: 52                           	push	edx
 11b351c: b9 08 58 b5 01               	mov	ecx, 0x1b55808
 11b3521: e8 0a 9f 39 ff               	call	0x54d430
 11b3526: 5d                           	pop	ebp
 11b3527: c3                           	ret
 11b3528: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b352b: 51                           	push	ecx
 11b352c: 8b 0d 10 96 b2 01            	mov	ecx, dword ptr [0x1b29610]
 11b3532: e8 b9 fa 03 00               	call	0x11f2ff0 <.text+0x3faf0>
 11b3537: 8d 55 08                     	lea	edx, [ebp + 0x8]
 11b353a: 52                           	push	edx
 11b353b: b9 08 58 b5 01               	mov	ecx, 0x1b55808
 11b3540: e8 eb 9e 39 ff               	call	0x54d430
 11b3545: 5d                           	pop	ebp
 11b3546: c3                           	ret
 11b3547: 90                           	nop
 11b3548: 76 34                        	jbe	0x11b357e <.text+0x7e>
 11b354a: 1b 01                        	sbb	eax, dword ptr [ecx]
 11b354c: 93                           	xchg	eax, ebx
 11b354d: 34 1b                        	xor	al, 0x1b
 11b354f: 01 b0 34 1b 01 cd            	add	dword ptr [eax - 0x32fee4cc], esi
 11b3555: 34 1b                        	xor	al, 0x1b
 11b3557: 01 ea                        	add	edx, ebp
 11b3559: 34 1b                        	xor	al, 0x1b
 11b355b: 01 07                        	add	dword ptr [edi], eax
 11b355d: 35 1b 01 37 35               	xor	eax, 0x3537011b
 11b3562: 1b 01                        	sbb	eax, dword ptr [ecx]
 11b3564: 28 35 1b 01 cc cc            	sub	byte ptr [-0x3333fee5], dh
 11b356a: cc                           	int3
 11b356b: cc                           	int3
 11b356c: cc                           	int3
 11b356d: cc                           	int3
 11b356e: cc                           	int3
 11b356f: cc                           	int3

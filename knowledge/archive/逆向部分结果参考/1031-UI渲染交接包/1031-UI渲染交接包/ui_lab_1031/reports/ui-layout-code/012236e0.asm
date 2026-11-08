
<stdin>:	file format elf32-i386

Disassembly of section .text:

012236e0 <.text>:
 12236e0: 55                           	push	ebp
 12236e1: 8b ec                        	mov	ebp, esp
 12236e3: 56                           	push	esi
 12236e4: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 12236e7: 85 f6                        	test	esi, esi
 12236e9: 75 05                        	jne	0x12236f0 <.text+0x10>
 12236eb: 32 c0                        	xor	al, al
 12236ed: 5e                           	pop	esi
 12236ee: 5d                           	pop	ebp
 12236ef: c3                           	ret
 12236f0: 8d 45 0b                     	lea	eax, [ebp + 0xb]
 12236f3: 50                           	push	eax
 12236f4: c6 45 0b 00                  	mov	byte ptr [ebp + 0xb], 0x0
 12236f8: e8 63 ff ff ff               	call	0x1223660
 12236fd: 83 c4 04                     	add	esp, 0x4
 1223700: 89 06                        	mov	dword ptr [esi], eax
 1223702: 8a 45 0b                     	mov	al, byte ptr [ebp + 0xb]
 1223705: 5e                           	pop	esi
 1223706: 5d                           	pop	ebp
 1223707: c3                           	ret
 1223708: cc                           	int3
 1223709: cc                           	int3
 122370a: cc                           	int3
 122370b: cc                           	int3
 122370c: cc                           	int3
 122370d: cc                           	int3
 122370e: cc                           	int3
 122370f: cc                           	int3
 1223710: 55                           	push	ebp
 1223711: 8b ec                        	mov	ebp, esp
 1223713: 51                           	push	ecx
 1223714: 0f 57 c0                     	xorps	xmm0, xmm0
 1223717: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122371c: f3 0f 11 45 fc               	movss	dword ptr [ebp - 0x4], xmm0
 1223721: e8 8a 1d f8 ff               	call	0x11a54b0
 1223726: 83 f8 02                     	cmp	eax, 0x2
 1223729: 75 27                        	jne	0x1223752 <.text+0x72>
 122372b: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1223730: e8 8b 1e f8 ff               	call	0x11a55c0
 1223735: 0f 57 c0                     	xorps	xmm0, xmm0
 1223738: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 122373c: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 122373f: f3                           	rep

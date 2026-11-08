
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e8030 <.text>:
  4e8030: 55                           	push	ebp
  4e8031: 8b ec                        	mov	ebp, esp
  4e8033: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4e8036: 83 ec 18                     	sub	esp, 0x18
  4e8039: 56                           	push	esi
  4e803a: 57                           	push	edi
  4e803b: 50                           	push	eax
  4e803c: 8b f9                        	mov	edi, ecx
  4e803e: e8 dd fe ff ff               	call	0x4e7f20
  4e8043: 8b f0                        	mov	esi, eax
  4e8045: 85 f6                        	test	esi, esi
  4e8047: 0f 84 a9 00 00 00            	je	0x4e80f6 <.text+0xc6>
  4e804d: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e804f: 85 c9                        	test	ecx, ecx
  4e8051: 0f 84 9f 00 00 00            	je	0x4e80f6 <.text+0xc6>
  4e8057: 83 7e 04 00                  	cmp	dword ptr [esi + 0x4], 0x0
  4e805b: 0f 84 95 00 00 00            	je	0x4e80f6 <.text+0xc6>
  4e8061: 8b 11                        	mov	edx, dword ptr [ecx]
  4e8063: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  4e8066: 8b 52 18                     	mov	edx, dword ptr [edx + 0x18]
  4e8069: 53                           	push	ebx
  4e806a: 50                           	push	eax
  4e806b: ff d2                        	call	edx
  4e806d: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e8070: 33 db                        	xor	ebx, ebx
  4e8072: 38 5d 0c                     	cmp	byte ptr [ebp + 0xc], bl
  4e8075: 0f 95 c3                     	setne	bl
  4e8078: 53                           	push	ebx
  4e8079: e8 22 8d ce 00               	call	0x11d0da0 <.text+0xce8d70>
  4e807e: 80 7e 09 00                  	cmp	byte ptr [esi + 0x9], 0x0
  4e8082: 74 71                        	je	0x4e80f5 <.text+0xc5>
  4e8084: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4e8087: 50                           	push	eax
  4e8088: 8b cf                        	mov	ecx, edi
  4e808a: e8 01 ff ff ff               	call	0x4e7f90
  4e808f: 85 c0                        	test	eax, eax
  4e8091: 74 62                        	je	0x4e80f5 <.text+0xc5>
  4e8093: 83 78 18 00                  	cmp	dword ptr [eax + 0x18], 0x0
  4e8097: 74 5c                        	je	0x4e80f5 <.text+0xc5>
  4e8099: 8d 4d 0f                     	lea	ecx, [ebp + 0xf]
  4e809c: 51                           	push	ecx
  4e809d: 8d 78 08                     	lea	edi, [eax + 0x8]
  4e80a0: 8d 55 f4                     	lea	edx, [ebp - 0xc]
  4e80a3: 52                           	push	edx
  4e80a4: 8b cf                        	mov	ecx, edi
  4e80a6: 88 5d 0f                     	mov	byte ptr [ebp + 0xf], bl
  4e80a9: e8 62 fb ff ff               	call	0x4e7c10
  4e80ae: 8d 45 e8                     	lea	eax, [ebp - 0x18]
  4e80b1: 50                           	push	eax
  4e80b2: 8b cf                        	mov	ecx, edi
  4e80b4: e8 d7 76 2c 00               	call	0x7af790 <.text+0x2c7760>
  4e80b9: 50                           	push	eax
  4e80ba: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
  4e80bd: e8 2e 7d 44 00               	call	0x92fdf0 <.text+0x447dc0>
  4e80c2: 84 c0                        	test	al, al
  4e80c4: 74 2f                        	je	0x4e80f5 <.text+0xc5>
  4e80c6: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
  4e80c9: e8 52 58 47 00               	call	0x95d920 <.text+0x4758f0>
  4e80ce: 83 78 1c 08                  	cmp	dword ptr [eax + 0x1c], 0x8
  4e80d2: 72 15                        	jb	0x4e80e9 <.text+0xb9>
  4e80d4: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  4e80d7: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e80da: 50                           	push	eax
  4e80db: e8 f0 8f ce 00               	call	0x11d10d0 <.text+0xce90a0>
  4e80e0: 5b                           	pop	ebx
  4e80e1: 5f                           	pop	edi
  4e80e2: 5e                           	pop	esi
  4e80e3: 8b e5                        	mov	esp, ebp
  4e80e5: 5d                           	pop	ebp
  4e80e6: c2 08 00                     	ret	0x8
  4e80e9: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e80ec: 83 c0 08                     	add	eax, 0x8
  4e80ef: 50                           	push	eax
  4e80f0: e8 db 8f ce 00               	call	0x11d10d0 <.text+0xce90a0>
  4e80f5: 5b                           	pop	ebx
  4e80f6: 5f                           	pop	edi
  4e80f7: 5e                           	pop	esi
  4e80f8: 8b e5                        	mov	esp, ebp
  4e80fa: 5d                           	pop	ebp
  4e80fb: c2 08 00                     	ret	0x8
  4e80fe: cc                           	int3
  4e80ff: cc                           	int3

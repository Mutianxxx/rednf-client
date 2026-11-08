
<stdin>:	file format elf32-i386

Disassembly of section .text:

011db510 <.text>:
 11db510: 55                           	push	ebp
 11db511: 8b ec                        	mov	ebp, esp
 11db513: 83 ec 4c                     	sub	esp, 0x4c
 11db516: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11db51b: 33 c5                        	xor	eax, ebp
 11db51d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11db520: 8b 45 30                     	mov	eax, dword ptr [ebp + 0x30]
 11db523: 53                           	push	ebx
 11db524: 8b 5d 10                     	mov	ebx, dword ptr [ebp + 0x10]
 11db527: 56                           	push	esi
 11db528: 8b f1                        	mov	esi, ecx
 11db52a: 89 45 b4                     	mov	dword ptr [ebp - 0x4c], eax
 11db52d: e8 3e f6 ff ff               	call	0x11dab70
 11db532: 84 c0                        	test	al, al
 11db534: 0f 84 c7 01 00 00            	je	0x11db701 <.text+0x1f1>
 11db53a: 8b cb                        	mov	ecx, ebx
 11db53c: e8 2f f6 ff ff               	call	0x11dab70
 11db541: 84 c0                        	test	al, al
 11db543: 0f 84 b8 01 00 00            	je	0x11db701 <.text+0x1f1>
 11db549: 57                           	push	edi
 11db54a: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11db550: 6a 04                        	push	0x4
 11db552: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11db555: e8 76 e6 fd ff               	call	0x11b9bd0
 11db55a: 83 c4 04                     	add	esp, 0x4
 11db55d: 8b ce                        	mov	ecx, esi
 11db55f: e8 1c 88 fd ff               	call	0x11b3d80
 11db564: 8b ce                        	mov	ecx, esi
 11db566: 8b f8                        	mov	edi, eax
 11db568: e8 23 88 fd ff               	call	0x11b3d90
 11db56d: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11db572: 0f 2e 05 b0 61 56 01         	ucomiss	xmm0, dword ptr [0x15661b0]
 11db579: 8b c8                        	mov	ecx, eax
 11db57b: 9f                           	lahf
 11db57c: f6 c4 44                     	test	ah, 0x44
 11db57f: 7a 4a                        	jp	0x11db5cb <.text+0xbb>
 11db581: f3 0f 10 0d b4 61 56 01      	movss	xmm1, dword ptr [0x15661b4]
 11db589: f3 0f 10 55 28               	movss	xmm2, dword ptr [ebp + 0x28]
 11db58e: 0f 2e d1                     	ucomiss	xmm2, xmm1
 11db591: 9f                           	lahf
 11db592: f6 c4 44                     	test	ah, 0x44
 11db595: 7a 13                        	jp	0x11db5aa <.text+0x9a>
 11db597: d1 ef                        	shr	edi
 11db599: 89 7d b8                     	mov	dword ptr [ebp - 0x48], edi
 11db59c: db 45 b8                     	fild	dword ptr [ebp - 0x48]
 11db59f: 79 06                        	jns	0x11db5a7 <.text+0x97>
 11db5a1: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11db5a7: d9 5d 28                     	fstp	dword ptr [ebp + 0x28]
 11db5aa: f3 0f 10 55 2c               	movss	xmm2, dword ptr [ebp + 0x2c]
 11db5af: 0f 2e d1                     	ucomiss	xmm2, xmm1
 11db5b2: 9f                           	lahf
 11db5b3: f6 c4 44                     	test	ah, 0x44
 11db5b6: 7a 13                        	jp	0x11db5cb <.text+0xbb>
 11db5b8: d1 e9                        	shr	ecx
 11db5ba: 89 4d b8                     	mov	dword ptr [ebp - 0x48], ecx
 11db5bd: db 45 b8                     	fild	dword ptr [ebp - 0x48]
 11db5c0: 79 06                        	jns	0x11db5c8 <.text+0xb8>
 11db5c2: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11db5c8: d9 5d 2c                     	fstp	dword ptr [ebp + 0x2c]
 11db5cb: 0f 57 05 80 58 56 01         	xorps	xmm0, xmmword ptr [0x1565880]
 11db5d2: 51                           	push	ecx
 11db5d3: 8d 4d bc                     	lea	ecx, [ebp - 0x44]
 11db5d6: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11db5db: 51                           	push	ecx
 11db5dc: e8 39 6c 22 00               	call	0x140221a <.text+0x226d0a>
 11db5e1: f3 0f 10 55 c0               	movss	xmm2, dword ptr [ebp - 0x40]
 11db5e6: f3 0f 59 55 24               	mulss	xmm2, dword ptr [ebp + 0x24]
 11db5eb: f3 0f 10 4d bc               	movss	xmm1, dword ptr [ebp - 0x44]
 11db5f0: f3 0f 10 45 d0               	movss	xmm0, dword ptr [ebp - 0x30]
 11db5f5: f3 0f 59 4d 20               	mulss	xmm1, dword ptr [ebp + 0x20]
 11db5fa: f3 0f 59 45 24               	mulss	xmm0, dword ptr [ebp + 0x24]
 11db5ff: f3 0f 11 55 c0               	movss	dword ptr [ebp - 0x40], xmm2
 11db604: f3 0f 10 55 cc               	movss	xmm2, dword ptr [ebp - 0x34]
 11db609: f3 0f 59 55 20               	mulss	xmm2, dword ptr [ebp + 0x20]
 11db60e: 8b ce                        	mov	ecx, esi
 11db610: f3 0f 11 4d bc               	movss	dword ptr [ebp - 0x44], xmm1
 11db615: f3 0f 11 55 cc               	movss	dword ptr [ebp - 0x34], xmm2
 11db61a: f3 0f 11 45 d0               	movss	dword ptr [ebp - 0x30], xmm0
 11db61f: e8 7c 87 fd ff               	call	0x11b3da0
 11db624: 0f 57 c0                     	xorps	xmm0, xmm0
 11db627: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11db62b: f3 0f 5c 45 28               	subss	xmm0, dword ptr [ebp + 0x28]
 11db630: 8b ce                        	mov	ecx, esi
 11db632: f3 0f 11 45 b8               	movss	dword ptr [ebp - 0x48], xmm0
 11db637: e8 74 87 fd ff               	call	0x11b3db0
 11db63c: 8b 55 34                     	mov	edx, dword ptr [ebp + 0x34]
 11db63f: f3 0f 10 5d 2c               	movss	xmm3, dword ptr [ebp + 0x2c]
 11db644: f3 0f 10 55 bc               	movss	xmm2, dword ptr [ebp - 0x44]
 11db649: f3 0f 10 4d b8               	movss	xmm1, dword ptr [ebp - 0x48]
 11db64e: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11db651: 52                           	push	edx
 11db652: 8b 55 b4                     	mov	edx, dword ptr [ebp - 0x4c]
 11db655: 0f 57 c0                     	xorps	xmm0, xmm0
 11db658: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11db65c: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11db65f: 52                           	push	edx
 11db660: 8b 55 18                     	mov	edx, dword ptr [ebp + 0x18]
 11db663: 83 ec 14                     	sub	esp, 0x14
 11db666: f3 0f 5c c3                  	subss	xmm0, xmm3
 11db66a: 0f 28 e0                     	movaps	xmm4, xmm0
 11db66d: f3 0f 59 65 cc               	mulss	xmm4, dword ptr [ebp - 0x34]
 11db672: f3 0f 59 45 d0               	mulss	xmm0, dword ptr [ebp - 0x30]
 11db677: f3 0f 59 d1                  	mulss	xmm2, xmm1
 11db67b: f3 0f 59 4d c0               	mulss	xmm1, dword ptr [ebp - 0x40]
 11db680: f3 0f 58 d4                  	addss	xmm2, xmm4
 11db684: f3 0f 11 5c 24 10            	movss	dword ptr [esp + 0x10], xmm3
 11db68a: f3 0f 58 c8                  	addss	xmm1, xmm0
 11db68e: f3 0f 10 45 28               	movss	xmm0, dword ptr [ebp + 0x28]
 11db693: f3 0f 11 44 24 0c            	movss	dword ptr [esp + 0xc], xmm0
 11db699: 0f 57 e4                     	xorps	xmm4, xmm4
 11db69c: f3 0f 2a e0                  	cvtsi2ss	xmm4, eax
 11db6a0: f3 0f 58 e0                  	addss	xmm4, xmm0
 11db6a4: f3 0f 10 45 24               	movss	xmm0, dword ptr [ebp + 0x24]
 11db6a9: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11db6af: f3 0f 10 45 20               	movss	xmm0, dword ptr [ebp + 0x20]
 11db6b4: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11db6ba: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11db6bf: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11db6c4: 52                           	push	edx
 11db6c5: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11db6c8: 52                           	push	edx
 11db6c9: 53                           	push	ebx
 11db6ca: f3 0f 58 e2                  	addss	xmm4, xmm2
 11db6ce: 51                           	push	ecx
 11db6cf: 0f 57 d2                     	xorps	xmm2, xmm2
 11db6d2: f3 0f 2a d1                  	cvtsi2ss	xmm2, ecx
 11db6d6: 50                           	push	eax
 11db6d7: 8d 45 bc                     	lea	eax, [ebp - 0x44]
 11db6da: f3 0f 58 d3                  	addss	xmm2, xmm3
 11db6de: f3 0f 58 d1                  	addss	xmm2, xmm1
 11db6e2: 50                           	push	eax
 11db6e3: 8b ce                        	mov	ecx, esi
 11db6e5: f3 0f 11 65 ec               	movss	dword ptr [ebp - 0x14], xmm4
 11db6ea: f3 0f 11 55 f0               	movss	dword ptr [ebp - 0x10], xmm2
 11db6ef: e8 9c fc ff ff               	call	0x11db390
 11db6f4: 6a 00                        	push	0x0
 11db6f6: 6a 04                        	push	0x4
 11db6f8: e8 23 e5 fd ff               	call	0x11b9c20
 11db6fd: 83 c4 08                     	add	esp, 0x8
 11db700: 5f                           	pop	edi
 11db701: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11db704: 5e                           	pop	esi
 11db705: 33 cd                        	xor	ecx, ebp
 11db707: 5b                           	pop	ebx
 11db708: e8 cb ba 1f 00               	call	0x13d71d8 <.text+0x1fbcc8>
 11db70d: 8b e5                        	mov	esp, ebp
 11db70f: 5d                           	pop	ebp
 11db710: c2 30 00                     	ret	0x30


<stdin>:	file format elf32-i386

Disassembly of section .text:

011c3f30 <.text>:
 11c3f30: 55                           	push	ebp
 11c3f31: 8b ec                        	mov	ebp, esp
 11c3f33: 6a ff                        	push	-0x1
 11c3f35: 68 92 7f 4c 01               	push	0x14c7f92
 11c3f3a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c3f40: 50                           	push	eax
 11c3f41: 83 ec 24                     	sub	esp, 0x24
 11c3f44: 53                           	push	ebx
 11c3f45: 56                           	push	esi
 11c3f46: 57                           	push	edi
 11c3f47: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c3f4c: 33 c5                        	xor	eax, ebp
 11c3f4e: 50                           	push	eax
 11c3f4f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c3f52: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c3f58: 8b f9                        	mov	edi, ecx
 11c3f5a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 11c3f5d: e8 1e b0 ff ff               	call	0x11bef80
 11c3f62: 33 db                        	xor	ebx, ebx
 11c3f64: c7 07 1c a8 85 01            	mov	dword ptr [edi], 0x185a81c
 11c3f6a: 8d b7 cc 02 00 00            	lea	esi, [edi + 0x2cc]
 11c3f70: 6a 08                        	push	0x8
 11c3f72: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11c3f75: 89 1e                        	mov	dword ptr [esi], ebx
 11c3f77: e8 9e 2b 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c3f7c: 83 c4 04                     	add	esp, 0x4
 11c3f7f: 3b c3                        	cmp	eax, ebx
 11c3f81: 0f 84 53 01 00 00            	je	0x11c40da <.text+0x1aa>
 11c3f87: 89 06                        	mov	dword ptr [esi], eax
 11c3f89: 33 c9                        	xor	ecx, ecx
 11c3f8b: 89 08                        	mov	dword ptr [eax], ecx
 11c3f8d: 33 d2                        	xor	edx, edx
 11c3f8f: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c3f92: 8b 06                        	mov	eax, dword ptr [esi]
 11c3f94: 89 30                        	mov	dword ptr [eax], esi
 11c3f96: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c3f9d: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c3fa0: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c3fa4: 8d b7 ec 02 00 00            	lea	esi, [edi + 0x2ec]
 11c3faa: 6a 08                        	push	0x8
 11c3fac: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c3fb0: 89 1e                        	mov	dword ptr [esi], ebx
 11c3fb2: e8 63 2b 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c3fb7: 83 c4 04                     	add	esp, 0x4
 11c3fba: 3b c3                        	cmp	eax, ebx
 11c3fbc: 0f 84 f4 00 00 00            	je	0x11c40b6 <.text+0x186>
 11c3fc2: 89 06                        	mov	dword ptr [esi], eax
 11c3fc4: 33 d2                        	xor	edx, edx
 11c3fc6: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c3fc9: 33 c9                        	xor	ecx, ecx
 11c3fcb: 89 08                        	mov	dword ptr [eax], ecx
 11c3fcd: 8b 16                        	mov	edx, dword ptr [esi]
 11c3fcf: 89 32                        	mov	dword ptr [edx], esi
 11c3fd1: 33 c0                        	xor	eax, eax
 11c3fd3: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c3fda: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c3fdd: 66 89 46 04                  	mov	word ptr [esi + 0x4], ax
 11c3fe1: 8d b7 14 03 00 00            	lea	esi, [edi + 0x314]
 11c3fe7: 6a 08                        	push	0x8
 11c3fe9: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 11c3fed: 89 1e                        	mov	dword ptr [esi], ebx
 11c3fef: e8 26 2b 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c3ff4: 83 c4 04                     	add	esp, 0x4
 11c3ff7: 3b c3                        	cmp	eax, ebx
 11c3ff9: 0f 84 93 00 00 00            	je	0x11c4092 <.text+0x162>
 11c3fff: 89 06                        	mov	dword ptr [esi], eax
 11c4001: 33 c9                        	xor	ecx, ecx
 11c4003: 89 08                        	mov	dword ptr [eax], ecx
 11c4005: 33 d2                        	xor	edx, edx
 11c4007: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c400a: 8b 0e                        	mov	ecx, dword ptr [esi]
 11c400c: 89 31                        	mov	dword ptr [ecx], esi
 11c400e: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c4015: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c4018: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 11c401c: 8d b7 a4 03 00 00            	lea	esi, [edi + 0x3a4]
 11c4022: 6a 08                        	push	0x8
 11c4024: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 11c4028: 89 1e                        	mov	dword ptr [esi], ebx
 11c402a: e8 eb 2a 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c402f: 83 c4 04                     	add	esp, 0x4
 11c4032: 3b c3                        	cmp	eax, ebx
 11c4034: 74 38                        	je	0x11c406e <.text+0x13e>
 11c4036: 89 06                        	mov	dword ptr [esi], eax
 11c4038: 33 c9                        	xor	ecx, ecx
 11c403a: 89 08                        	mov	dword ptr [eax], ecx
 11c403c: 33 d2                        	xor	edx, edx
 11c403e: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4041: 8b 06                        	mov	eax, dword ptr [esi]
 11c4043: 89 30                        	mov	dword ptr [eax], esi
 11c4045: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c404c: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c404f: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4053: 8b cf                        	mov	ecx, edi
 11c4055: e8 36 eb ff ff               	call	0x11c2b90
 11c405a: 8b c7                        	mov	eax, edi
 11c405c: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c405f: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c4066: 59                           	pop	ecx
 11c4067: 5f                           	pop	edi
 11c4068: 5e                           	pop	esi
 11c4069: 5b                           	pop	ebx
 11c406a: 8b e5                        	mov	esp, ebp
 11c406c: 5d                           	pop	ebp
 11c406d: c3                           	ret
 11c406e: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 11c4071: 52                           	push	edx
 11c4072: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11c4075: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c4078: e8 4d 24 21 00               	call	0x13d64ca <.text+0x21259a>
 11c407d: 68 90 0f 91 01               	push	0x1910f90
 11c4082: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 11c4085: 50                           	push	eax
 11c4086: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 11c408d: e8 08 2b 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c4092: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 11c4095: 51                           	push	ecx
 11c4096: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c4099: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 11c409c: e8 29 24 21 00               	call	0x13d64ca <.text+0x21259a>
 11c40a1: 68 90 0f 91 01               	push	0x1910f90
 11c40a6: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11c40a9: 52                           	push	edx
 11c40aa: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11c40b1: e8 e4 2a 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c40b6: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 11c40b9: 50                           	push	eax
 11c40ba: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11c40bd: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c40c0: e8 05 24 21 00               	call	0x13d64ca <.text+0x21259a>
 11c40c5: 68 90 0f 91 01               	push	0x1910f90
 11c40ca: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11c40cd: 51                           	push	ecx
 11c40ce: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 11c40d5: e8 c0 2a 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c40da: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 11c40dd: 52                           	push	edx
 11c40de: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c40e1: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 11c40e4: e8 e1 23 21 00               	call	0x13d64ca <.text+0x21259a>
 11c40e9: 68 90 0f 91 01               	push	0x1910f90
 11c40ee: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 11c40f1: 50                           	push	eax
 11c40f2: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11c40f9: e8 9c 2a 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c40fe: cc                           	int3
 11c40ff: cc                           	int3
 11c4100: 55                           	push	ebp
 11c4101: 8b ec                        	mov	ebp, esp
 11c4103: 6a ff                        	push	-0x1
 11c4105: 68 f0 7f 4c 01               	push	0x14c7ff0
 11c410a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4110: 50                           	push	eax
 11c4111: 83 ec 24                     	sub	esp, 0x24
 11c4114: 53                           	push	ebx
 11c4115: 56                           	push	esi
 11c4116: 57                           	push	edi
 11c4117: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c411c: 33 c5                        	xor	eax, ebp
 11c411e: 50                           	push	eax
 11c411f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4122: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4128: 8b f9                        	mov	edi, ecx
 11c412a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 11c412d: e8 4e ae ff ff               	call	0x11bef80
 11c4132: 33 db                        	xor	ebx, ebx
 11c4134: c7 07 1c a8 85 01            	mov	dword ptr [edi], 0x185a81c
 11c413a: 8d b7 cc 02 00 00            	lea	esi, [edi + 0x2cc]
 11c4140: 6a 08                        	push	0x8
 11c4142: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11c4145: 89 1e                        	mov	dword ptr [esi], ebx
 11c4147: e8 ce 29 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c414c: 83 c4 04                     	add	esp, 0x4
 11c414f: 3b c3                        	cmp	eax, ebx
 11c4151: 0f 84 94 01 00 00            	je	0x11c42eb <.text+0x3bb>
 11c4157: 89 06                        	mov	dword ptr [esi], eax
 11c4159: 33 c9                        	xor	ecx, ecx
 11c415b: 89 08                        	mov	dword ptr [eax], ecx
 11c415d: 33 d2                        	xor	edx, edx
 11c415f: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4162: 8b 06                        	mov	eax, dword ptr [esi]
 11c4164: 89 30                        	mov	dword ptr [eax], esi
 11c4166: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c416d: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c4170: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4174: 8d b7 ec 02 00 00            	lea	esi, [edi + 0x2ec]
 11c417a: 6a 08                        	push	0x8
 11c417c: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c4180: 89 1e                        	mov	dword ptr [esi], ebx
 11c4182: e8 93 29 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c4187: 83 c4 04                     	add	esp, 0x4
 11c418a: 3b c3                        	cmp	eax, ebx
 11c418c: 0f 84 35 01 00 00            	je	0x11c42c7 <.text+0x397>
 11c4192: 89 06                        	mov	dword ptr [esi], eax
 11c4194: 33 d2                        	xor	edx, edx
 11c4196: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4199: 33 c9                        	xor	ecx, ecx
 11c419b: 89 08                        	mov	dword ptr [eax], ecx
 11c419d: 8b 16                        	mov	edx, dword ptr [esi]
 11c419f: 89 32                        	mov	dword ptr [edx], esi
 11c41a1: 33 c0                        	xor	eax, eax
 11c41a3: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c41aa: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c41ad: 66 89 46 04                  	mov	word ptr [esi + 0x4], ax
 11c41b1: 8d b7 14 03 00 00            	lea	esi, [edi + 0x314]
 11c41b7: 6a 08                        	push	0x8
 11c41b9: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 11c41bd: 89 1e                        	mov	dword ptr [esi], ebx
 11c41bf: e8 56 29 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c41c4: 83 c4 04                     	add	esp, 0x4
 11c41c7: 3b c3                        	cmp	eax, ebx
 11c41c9: 0f 84 d4 00 00 00            	je	0x11c42a3 <.text+0x373>
 11c41cf: 89 06                        	mov	dword ptr [esi], eax
 11c41d1: 33 c9                        	xor	ecx, ecx
 11c41d3: 89 08                        	mov	dword ptr [eax], ecx
 11c41d5: 33 d2                        	xor	edx, edx
 11c41d7: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c41da: 8b 0e                        	mov	ecx, dword ptr [esi]
 11c41dc: 89 31                        	mov	dword ptr [ecx], esi
 11c41de: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c41e5: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c41e8: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 11c41ec: 8d b7 a4 03 00 00            	lea	esi, [edi + 0x3a4]
 11c41f2: 6a 08                        	push	0x8
 11c41f4: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 11c41f8: 89 1e                        	mov	dword ptr [esi], ebx
 11c41fa: e8 1b 29 21 00               	call	0x13d6b1a <.text+0x212bea>
 11c41ff: 83 c4 04                     	add	esp, 0x4
 11c4202: 3b c3                        	cmp	eax, ebx
 11c4204: 74 79                        	je	0x11c427f <.text+0x34f>
 11c4206: 89 06                        	mov	dword ptr [esi], eax
 11c4208: 33 c9                        	xor	ecx, ecx
 11c420a: 89 08                        	mov	dword ptr [eax], ecx
 11c420c: 33 d2                        	xor	edx, edx
 11c420e: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c4211: 8b 06                        	mov	eax, dword ptr [esi]
 11c4213: 89 30                        	mov	dword ptr [eax], esi
 11c4215: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c421c: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c421f: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4223: 8b cf                        	mov	ecx, edi
 11c4225: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
 11c4229: e8 62 e9 ff ff               	call	0x11c2b90
 11c422e: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11c4231: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11c4234: 8b 17                        	mov	edx, dword ptr [edi]
 11c4236: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11c4239: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11c423f: 53                           	push	ebx
 11c4240: 53                           	push	ebx
 11c4241: 50                           	push	eax
 11c4242: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c4245: 51                           	push	ecx
 11c4246: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11c4249: 50                           	push	eax
 11c424a: 51                           	push	ecx
 11c424b: 56                           	push	esi
 11c424c: 8b cf                        	mov	ecx, edi
 11c424e: ff d2                        	call	edx
 11c4250: 85 c0                        	test	eax, eax
 11c4252: 74 15                        	je	0x11c4269 <.text+0x339>
 11c4254: 3b f3                        	cmp	esi, ebx
 11c4256: 74 11                        	je	0x11c4269 <.text+0x339>
 11c4258: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11c425b: 50                           	push	eax
 11c425c: 8b ce                        	mov	ecx, esi
 11c425e: e8 6d 09 ff ff               	call	0x11b4bd0
 11c4263: 89 87 c8 02 00 00            	mov	dword ptr [edi + 0x2c8], eax
 11c4269: 8b c7                        	mov	eax, edi
 11c426b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c426e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c4275: 59                           	pop	ecx
 11c4276: 5f                           	pop	edi
 11c4277: 5e                           	pop	esi
 11c4278: 5b                           	pop	ebx
 11c4279: 8b e5                        	mov	esp, ebp
 11c427b: 5d                           	pop	ebp
 11c427c: c2 18 00                     	ret	0x18
 11c427f: 8d 4d f0                     	lea	ecx, [ebp - 0x10]
 11c4282: 51                           	push	ecx
 11c4283: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11c4286: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c4289: e8 3c 22 21 00               	call	0x13d64ca <.text+0x21259a>
 11c428e: 68 90 0f 91 01               	push	0x1910f90
 11c4293: 8d 55 dc                     	lea	edx, [ebp - 0x24]
 11c4296: 52                           	push	edx
 11c4297: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 11c429e: e8 f7 28 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c42a3: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 11c42a6: 50                           	push	eax
 11c42a7: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c42aa: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 11c42ad: e8 18 22 21 00               	call	0x13d64ca <.text+0x21259a>
 11c42b2: 68 90 0f 91 01               	push	0x1910f90
 11c42b7: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c42ba: 51                           	push	ecx
 11c42bb: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11c42c2: e8 d3 28 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c42c7: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 11c42ca: 52                           	push	edx
 11c42cb: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11c42ce: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c42d1: e8 f4 21 21 00               	call	0x13d64ca <.text+0x21259a>
 11c42d6: 68 90 0f 91 01               	push	0x1910f90
 11c42db: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 11c42de: 50                           	push	eax
 11c42df: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 11c42e6: e8 af 28 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c42eb: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 11c42ee: 51                           	push	ecx
 11c42ef: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c42f2: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 11c42f5: e8 d0 21 21 00               	call	0x13d64ca <.text+0x21259a>
 11c42fa: 68 90 0f 91 01               	push	0x1910f90
 11c42ff: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11c4302: 52                           	push	edx
 11c4303: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11c430a: e8 8b 28 21 00               	call	0x13d6b9a <.text+0x212c6a>
 11c430f: cc                           	int3
 11c4310: 53                           	push	ebx
 11c4311: 56                           	push	esi
 11c4312: 8b f1                        	mov	esi, ecx
 11c4314: 57                           	push	edi
 11c4315: c7 06 1c a8 85 01            	mov	dword ptr [esi], 0x185a81c
 11c431b: e8 70 e8 ff ff               	call	0x11c2b90
 11c4320: 33 db                        	xor	ebx, ebx
 11c4322: 88 5e 04                     	mov	byte ptr [esi + 0x4], bl
 11c4325: 83 be bc 03 00 00 08         	cmp	dword ptr [esi + 0x3bc], 0x8
 11c432c: 72 0f                        	jb	0x11c433d <.text+0x40d>
 11c432e: 8b 86                        	<unknown>

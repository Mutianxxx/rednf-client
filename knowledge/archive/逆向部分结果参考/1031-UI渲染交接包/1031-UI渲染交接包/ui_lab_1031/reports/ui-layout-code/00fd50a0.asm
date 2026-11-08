
<stdin>:	file format elf32-i386

Disassembly of section .text:

00fd50a0 <.text>:
  fd50a0: 8b 01                        	mov	eax, dword ptr [ecx]
  fd50a2: 8b 50 28                     	mov	edx, dword ptr [eax + 0x28]
  fd50a5: ff e2                        	jmp	edx
  fd50a7: cc                           	int3
  fd50a8: cc                           	int3
  fd50a9: cc                           	int3
  fd50aa: cc                           	int3
  fd50ab: cc                           	int3
  fd50ac: cc                           	int3
  fd50ad: cc                           	int3
  fd50ae: cc                           	int3
  fd50af: cc                           	int3
  fd50b0: 55                           	push	ebp
  fd50b1: 8b ec                        	mov	ebp, esp
  fd50b3: 83 ec 20                     	sub	esp, 0x20
  fd50b6: 57                           	push	edi
  fd50b7: 8b f9                        	mov	edi, ecx
  fd50b9: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
  fd50bc: e8 7f 8f 1e 00               	call	0x11be040 <.text+0x1e8fa0>
  fd50c1: 84 c0                        	test	al, al
  fd50c3: 0f 84 0c 01 00 00            	je	0xfd51d5 <.text+0x135>
  fd50c9: 53                           	push	ebx
  fd50ca: 56                           	push	esi
  fd50cb: e8 f0 2c 1f 00               	call	0x11c7dc0 <.text+0x1f2d20>
  fd50d0: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  fd50d3: e8 f8 2c 1f 00               	call	0x11c7dd0 <.text+0x1f2d30>
  fd50d8: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
  fd50db: 33 f6                        	xor	esi, esi
  fd50dd: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
  fd50e0: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
  fd50e3: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  fd50e6: e8 75 ae 45 ff               	call	0x42ff60
  fd50eb: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
  fd50ee: 8b d8                        	mov	ebx, eax
  fd50f0: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  fd50f3: e8 08 92 1e 00               	call	0x11be300 <.text+0x1e9260>
  fd50f8: 89 45 e0                     	mov	dword ptr [ebp - 0x20], eax
  fd50fb: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
  fd50fe: eb 03                        	jmp	0xfd5103 <.text+0x63>
  fd5100: 8b 5d e4                     	mov	ebx, dword ptr [ebp - 0x1c]
  fd5103: 8b 8f d0 05 00 00            	mov	ecx, dword ptr [edi + 0x5d0]
  fd5109: e8 c2 27 1f 00               	call	0x11c78d0 <.text+0x1f2830>
  fd510e: 8d 04 46                     	lea	eax, [esi + 2*eax]
  fd5111: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
  fd5114: 8b c6                        	mov	eax, esi
  fd5116: 99                           	cdq
  fd5117: 2b c2                        	sub	eax, edx
  fd5119: 8b 55 e0                     	mov	edx, dword ptr [ebp - 0x20]
  fd511c: d1 f8                        	sar	eax
  fd511e: 8b c8                        	mov	ecx, eax
  fd5120: c1 e1 05                     	shl	ecx, 0x5
  fd5123: 2b c8                        	sub	ecx, eax
  fd5125: 8b c6                        	mov	eax, esi
  fd5127: 25 01 00 00 80               	and	eax, 0x80000001
  fd512c: 8d 54 11 4e                  	lea	edx, [ecx + edx + 0x4e]
  fd5130: 79 05                        	jns	0xfd5137 <.text+0x97>
  fd5132: 48                           	dec	eax
  fd5133: 83 c8 fe                     	or	eax, -0x2
  fd5136: 40                           	inc	eax
  fd5137: 8d 4b ff                     	lea	ecx, [ebx - 0x1]
  fd513a: 74 03                        	je	0xfd513f <.text+0x9f>
  fd513c: 8d 4b 6c                     	lea	ecx, [ebx + 0x6c]
  fd513f: 8d 41 01                     	lea	eax, [ecx + 0x1]
  fd5142: 39 45 fc                     	cmp	dword ptr [ebp - 0x4], eax
  fd5145: 7c 3d                        	jl	0xfd5184 <.text+0xe4>
  fd5147: 8d 42 01                     	lea	eax, [edx + 0x1]
  fd514a: 39 45 f8                     	cmp	dword ptr [ebp - 0x8], eax
  fd514d: 7c 35                        	jl	0xfd5184 <.text+0xe4>
  fd514f: 8d 41 1d                     	lea	eax, [ecx + 0x1d]
  fd5152: 39 45 fc                     	cmp	dword ptr [ebp - 0x4], eax
  fd5155: 7f 2d                        	jg	0xfd5184 <.text+0xe4>
  fd5157: 8d 42 1d                     	lea	eax, [edx + 0x1d]
  fd515a: 39 45 f8                     	cmp	dword ptr [ebp - 0x8], eax
  fd515d: 7f 25                        	jg	0xfd5184 <.text+0xe4>
  fd515f: 8b 87 d8 05 00 00            	mov	eax, dword ptr [edi + 0x5d8]
  fd5165: 8b 9f dc 05 00 00            	mov	ebx, dword ptr [edi + 0x5dc]
  fd516b: 2b d8                        	sub	ebx, eax
  fd516d: c1 fb 02                     	sar	ebx, 0x2
  fd5170: 39 5d f4                     	cmp	dword ptr [ebp - 0xc], ebx
  fd5173: 73 0f                        	jae	0xfd5184 <.text+0xe4>
  fd5175: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
  fd5178: 8b 04 98                     	mov	eax, dword ptr [eax + 4*ebx]
  fd517b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  fd517e: 89 4d e8                     	mov	dword ptr [ebp - 0x18], ecx
  fd5181: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
  fd5184: 46                           	inc	esi
  fd5185: 83 fe 10                     	cmp	esi, 0x10
  fd5188: 0f 8c 72 ff ff ff            	jl	0xfd5100 <.text+0x60>
  fd518e: 8b 45 f0                     	mov	eax, dword ptr [ebp - 0x10]
  fd5191: 8b 4f 14                     	mov	ecx, dword ptr [edi + 0x14]
  fd5194: 5e                           	pop	esi
  fd5195: 5b                           	pop	ebx
  fd5196: 85 c0                        	test	eax, eax
  fd5198: 74 2d                        	je	0xfd51c7 <.text+0x127>
  fd519a: 6a 05                        	push	0x5
  fd519c: 50                           	push	eax
  fd519d: 68 15 01 00 00               	push	0x115
  fd51a2: e8 c9 22 ea ff               	call	0xe77470
  fd51a7: 85 c0                        	test	eax, eax
  fd51a9: 74 2a                        	je	0xfd51d5 <.text+0x135>
  fd51ab: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  fd51ae: 8b 10                        	mov	edx, dword ptr [eax]
  fd51b0: 8b 52 78                     	mov	edx, dword ptr [edx + 0x78]
  fd51b3: 6a 1c                        	push	0x1c
  fd51b5: 41                           	inc	ecx
  fd51b6: 6a 1c                        	push	0x1c
  fd51b8: 51                           	push	ecx
  fd51b9: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
  fd51bc: 41                           	inc	ecx
  fd51bd: 51                           	push	ecx
  fd51be: 8b c8                        	mov	ecx, eax
  fd51c0: ff d2                        	call	edx
  fd51c2: 5f                           	pop	edi
  fd51c3: 8b e5                        	mov	esp, ebp
  fd51c5: 5d                           	pop	ebp
  fd51c6: c3                           	ret
  fd51c7: 6a 00                        	push	0x0
  fd51c9: 6a ff                        	push	-0x1
  fd51cb: 68 15 01 00 00               	push	0x115
  fd51d0: e8 db f3 e9 ff               	call	0xe745b0
  fd51d5: 5f                           	pop	edi
  fd51d6: 8b e5                        	mov	esp, ebp
  fd51d8: 5d                           	pop	ebp
  fd51d9: c3                           	ret
  fd51da: cc                           	int3
  fd51db: cc                           	int3
  fd51dc: cc                           	int3
  fd51dd: cc                           	int3
  fd51de: cc                           	int3
  fd51df: cc                           	int3
  fd51e0: 80 79 0c 00                  	cmp	byte ptr [ecx + 0xc], 0x0
  fd51e4: 74 44                        	je	0xfd522a <.text+0x18a>
  fd51e6: 83 b9 d0 02 00 00 08         	cmp	dword ptr [ecx + 0x2d0], 0x8
  fd51ed: 72 08                        	jb	0xfd51f7 <.text+0x157>
  fd51ef: 8b 81 bc 02 00 00            	mov	eax, dword ptr [ecx + 0x2bc]
  fd51f5: eb 06                        	jmp	0xfd51fd <.text+0x15d>
  fd51f7: 8d 81 bc 02 00 00            	lea	eax, [ecx + 0x2bc]
  fd51fd: 8b 15 50 f7 a6 01            	mov	edx, dword ptr [0x1a6f750]
  fd5203: 6a 00                        	push	0x0
  fd5205: 6a 00                        	push	0x0
  fd5207: 68 40 06 00 00               	push	0x640
  fd520c: 6a 00                        	push	0x0
  fd520e: 6a 00                        	push	0x0
  fd5210: 50                           	push	eax
  fd5211: 8b 41 18                     	mov	eax, dword ptr [ecx + 0x18]
  fd5214: 8b 49 14                     	mov	ecx, dword ptr [ecx + 0x14]
  fd5217: 6a 02                        	push	0x2
  fd5219: 68 00 00 00 ff               	push	0xff000000
  fd521e: 6a ff                        	push	-0x1
  fd5220: 50                           	push	eax
  fd5221: 51                           	push	ecx
  fd5222: 8b 4a 3c                     	mov	ecx, dword ptr [edx + 0x3c]
  fd5225: e8 06 9b 4f ff               	call	0x4ced30
  fd522a: c3                           	ret
  fd522b: cc                           	int3
  fd522c: cc                           	int3
  fd522d: cc                           	int3
  fd522e: cc                           	int3
  fd522f: cc                           	int3
  fd5230: 55                           	push	ebp
  fd5231: 8b ec                        	mov	ebp, esp
  fd5233: 83 ec 20                     	sub	esp, 0x20
  fd5236: 53                           	push	ebx
  fd5237: 56                           	push	esi
  fd5238: 8d b1 e8 05 00 00            	lea	esi, [ecx + 0x5e8]
  fd523e: 57                           	push	edi
  fd523f: 8d 45 ec                     	lea	eax, [ebp - 0x14]
  fd5242: 50                           	push	eax
  fd5243: 8b ce                        	mov	ecx, esi
  fd5245: 89 75 f8                     	mov	dword ptr [ebp - 0x8], esi
  fd5248: e8 03 ac 58 ff               	call	0x55fe50
  fd524d: 8d 49 00                     	lea	ecx, [ecx]
  fd5250: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  fd5253: 51                           	push	ecx
  fd5254: 8b ce                        	mov	ecx, esi
  fd5256: e8 e5 f0 7e ff               	call	0x7c4340
  fd525b: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
  fd525e: 85 ff                        	test	edi, edi
  fd5260: 0f 84 04 01 00 00            	je	0xfd536a <.text+0x2ca>
  fd5266: 8b 17                        	mov	edx, dword ptr [edi]
  fd5268: 85 d2                        	test	edx, edx
  fd526a: 0f 84 fa 00 00 00            	je	0xfd536a <.text+0x2ca>
  fd5270: 8b 08                        	mov	ecx, dword ptr [eax]
  fd5272: 85 c9                        	test	ecx, ecx
  fd5274: 74 02                        	je	0xfd5278 <.text+0x1d8>
  fd5276: 8b 09                        	mov	ecx, dword ptr [ecx]
  fd5278: 3b d1                        	cmp	edx, ecx
  fd527a: 0f 85 ea 00 00 00            	jne	0xfd536a <.text+0x2ca>
  fd5280: 8b 75 f4                     	mov	esi, dword ptr [ebp - 0xc]
  fd5283: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
  fd5286: 0f 84 e3 00 00 00            	je	0xfd536f <.text+0x2cf>
  fd528c: 8b c2                        	mov	eax, edx
  fd528e: 85 c0                        	test	eax, eax
  fd5290: 0f 84 d4 00 00 00            	je	0xfd536a <.text+0x2ca>
  fd5296: 85 f6                        	test	esi, esi
  fd5298: 0f 84 cc 00 00 00            	je	0xfd536a <.text+0x2ca>
  fd529e: 3b 70                        	<unknown>

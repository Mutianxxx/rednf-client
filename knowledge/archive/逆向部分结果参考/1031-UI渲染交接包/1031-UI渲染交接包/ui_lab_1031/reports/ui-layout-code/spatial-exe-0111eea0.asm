
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111eea0 <.text>:
 111eea0: 00 00                        	add	byte ptr [eax], al
 111eea2: 8d 51 08                     	lea	edx, [ecx + 0x8]
 111eea5: 52                           	push	edx
 111eea6: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 111eea9: 50                           	push	eax
 111eeaa: 89 7d dc                     	mov	dword ptr [ebp - 0x24], edi
 111eead: e8 7e 1a 08 00               	call	0x11a0930 <.text+0x81a90>
 111eeb2: 8d 8e c8 06 00 00            	lea	ecx, [esi + 0x6c8]
 111eeb8: 8d 51 08                     	lea	edx, [ecx + 0x8]
 111eebb: 52                           	push	edx
 111eebc: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 111eebf: 50                           	push	eax
 111eec0: 89 7d dc                     	mov	dword ptr [ebp - 0x24], edi
 111eec3: e8 68 1a 08 00               	call	0x11a0930 <.text+0x81a90>
 111eec8: 8b ce                        	mov	ecx, esi
 111eeca: e8 61 3a 6c ff               	call	0x7e2930
 111eecf: 8b 0d 74 a8 a6 01            	mov	ecx, dword ptr [0x1a6a874]
 111eed5: 89 3d 50 9c a4 01            	mov	dword ptr [0x1a49c50], edi
 111eedb: e8 90 21 7a ff               	call	0x8c1070
 111eee0: 8b 0d 74 a8 a6 01            	mov	ecx, dword ptr [0x1a6a874]
 111eee6: 8d 55 dc                     	lea	edx, [ebp - 0x24]
 111eee9: 52                           	push	edx
 111eeea: c6 81 34 05 00 00 01         	mov	byte ptr [ecx + 0x534], 0x1
 111eef1: 68 48 7a ac 01               	push	0x1ac7a48
 111eef6: b9 40 7a ac 01               	mov	ecx, 0x1ac7a40
 111eefb: e8 e0 1e 08 00               	call	0x11a0de0 <.text+0x81f40>
 111ef00: a1 50 f7 a6 01               	mov	eax, dword ptr [0x1a6f750]
 111ef05: 8b 40 3c                     	mov	eax, dword ptr [eax + 0x3c]
 111ef08: 8b 4d dc                     	mov	ecx, dword ptr [ebp - 0x24]
 111ef0b: 6a 01                        	push	0x1
 111ef0d: 89 88 b4 07 00 00            	mov	dword ptr [eax + 0x7b4], ecx
 111ef13: e8 98 49 80 ff               	call	0x9238b0
 111ef18: 83 c4 04                     	add	esp, 0x4
 111ef1b: 57                           	push	edi
 111ef1c: 57                           	push	edi
 111ef1d: 8b ce                        	mov	ecx, esi
 111ef1f: e8 ec f4 6b ff               	call	0x7de410
 111ef24: 8b f0                        	mov	esi, eax
 111ef26: c7 06 e9 03 00 00            	mov	dword ptr [esi], 0x3e9
 111ef2c: 8b 0d c4 f6 a6 01            	mov	ecx, dword ptr [0x1a6f6c4]
 111ef32: 68 e9 03 00 00               	push	0x3e9
 111ef37: e8 14 6c 01 00               	call	0x1135b50 <.text+0x16cb0>
 111ef3c: 8b f8                        	mov	edi, eax
 111ef3e: 8b 57 64                     	mov	edx, dword ptr [edi + 0x64]
 111ef41: 2b 57 60                     	sub	edx, dword ptr [edi + 0x60]
 111ef44: 83 c6 04                     	add	esi, 0x4
 111ef47: c1 fa 07                     	sar	edx, 0x7
 111ef4a: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 111ef4d: 52                           	push	edx
 111ef4e: 8b ce                        	mov	ecx, esi
 111ef50: e8 9b f8 5d ff               	call	0x6fe7f0
 111ef55: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 111ef58: 8b 40 64                     	mov	eax, dword ptr [eax + 0x64]
 111ef5b: 8b 7f 60                     	mov	edi, dword ptr [edi + 0x60]
 111ef5e: 2b c7                        	sub	eax, edi
 111ef60: c1 f8 07                     	sar	eax, 0x7
 111ef63: c7 45 e8 00 00 00 00         	mov	dword ptr [ebp - 0x18], 0x0
 111ef6a: 85 c0                        	test	eax, eax
 111ef6c: 0f 84 21 03 00 00            	je	0x111f293 <.text+0x3f3>
 111ef72: c7 45 ec 00 00 00 00         	mov	dword ptr [ebp - 0x14], 0x0
 111ef79: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 111ef80: 39 45 e8                     	cmp	dword ptr [ebp - 0x18], eax
 111ef83: 0f 83 b1 fe ff ff            	jae	0x111ee3a
 111ef89: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 111ef8c: 80 7c 07 04 00               	cmp	byte ptr [edi + eax + 0x4], 0x0
 111ef91: 8b 0c 07                     	mov	ecx, dword ptr [edi + eax]
 111ef94: 89 4d dc                     	mov	dword ptr [ebp - 0x24], ecx
 111ef97: 74 22                        	je	0x111efbb <.text+0x11b>
 111ef99: 8b 4d e0                     	mov	ecx, dword ptr [ebp - 0x20]
 111ef9c: 81 c1 f8 00 00 00            	add	ecx, 0xf8
 111efa2: 8d 55 d8                     	lea	edx, [ebp - 0x28]
 111efa5: 52                           	push	edx
 111efa6: 8d 41 08                     	lea	eax, [ecx + 0x8]
 111efa9: 50                           	push	eax
 111efaa: e8 31 1e 08 00               	call	0x11a0de0 <.text+0x81f40>
 111efaf: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 111efb2: 8b 5c 0f 08                  	mov	ebx, dword ptr [edi + ecx + 0x8]
 111efb6: 03 5d d8                     	add	ebx, dword ptr [ebp - 0x28]
 111efb9: eb 07                        	jmp	0x111efc2 <.text+0x122>
 111efbb: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 111efbe: 8b 5c 17 08                  	mov	ebx, dword ptr [edi + edx + 0x8]
 111efc2: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 111efc5: 83 78 14 02                  	cmp	dword ptr [eax + 0x14], 0x2
 111efc9: 0f 85 49 01 00 00            	jne	0x111f118 <.text+0x278>
 111efcf: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 111efd2: 8b 7c 0f 24                  	mov	edi, dword ptr [edi + ecx + 0x24]
 111efd6: 8d 55 88                     	lea	edx, [ebp - 0x78]
 111efd9: 8b ca                        	mov	ecx, edx
 111efdb: 89 55 c4                     	mov	dword ptr [ebp - 0x3c], edx
 111efde: e8 8d 34 08 00               	call	0x11a2470 <.text+0x835d0>
 111efe3: 8d 45 90                     	lea	eax, [ebp - 0x70]
 111efe6: 50                           	push	eax
 111efe7: 8d 4d d4                     	lea	ecx, [ebp - 0x2c]
 111efea: 51                           	push	ecx
 111efeb: 8d 4d 88                     	lea	ecx, [ebp - 0x78]
 111efee: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 111eff5: c7 45 d4 00 00 00 00         	mov	dword ptr [ebp - 0x2c], 0x0
 111effc: e8 2f 19 08 00               	call	0x11a0930 <.text+0x81a90>
 111f001: 8b 45 e8                     	mov	eax, dword ptr [ebp - 0x18]
 111f004: 8d 55 90                     	lea	edx, [ebp - 0x70]
 111f007: 89 45 84                     	mov	dword ptr [ebp - 0x7c], eax
 111f00a: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 111f00d: 52                           	push	edx
 111f00e: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 111f011: 50                           	push	eax
 111f012: 8d 4d 88                     	lea	ecx, [ebp - 0x78]
 111f015: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
 111f01c: e8 0f 19 08 00               	call	0x11a0930 <.text+0x81a90>
 111f021: 8b 4d dc                     	mov	ecx, dword ptr [ebp - 0x24]
 111f024: 33 c0                        	xor	eax, eax
 111f026: 89 4d 94                     	mov	dword ptr [ebp - 0x6c], ecx
 111f029: 89 5d 98                     	mov	dword ptr [ebp - 0x68], ebx
 111f02c: 89 7d 9c                     	mov	dword ptr [ebp - 0x64], edi
 111f02f: c6 45 a0 00                  	mov	byte ptr [ebp - 0x60], 0x0
 111f033: 89 45 a4                     	mov	dword ptr [ebp - 0x5c], eax
 111f036: c6 45 a8 01                  	mov	byte ptr [ebp - 0x58], 0x1
 111f03a: 89 45 ac                     	mov	dword ptr [ebp - 0x54], eax
 111f03d: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
 111f040: 8d 55 84                     	lea	edx, [ebp - 0x7c]
 111f043: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
 111f04a: 3b d0                        	cmp	edx, eax
 111f04c: 73 72                        	jae	0x111f0c0 <.text+0x220>
 111f04e: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 111f051: 8d 4d 84                     	lea	ecx, [ebp - 0x7c]
 111f054: 3b d1                        	cmp	edx, ecx
 111f056: 77 68                        	ja	0x111f0c0 <.text+0x220>
 111f058: 8b f9                        	mov	edi, ecx
 111f05a: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 111f05d: 2b fa                        	sub	edi, edx
 111f05f: 3b c1                        	cmp	eax, ecx
 111f061: 75 3c                        	jne	0x111f09f <.text+0x1ff>
 111f063: 2b c2                        	sub	eax, edx
 111f065: c1 f8 06                     	sar	eax, 0x6
 111f068: 3d fe ff ff 03               	cmp	eax, 0x3fffffe
 111f06d: 0f 87 da 02 00 00            	ja	0x111f34d <.text+0x4ad>
 111f073: 2b ca                        	sub	ecx, edx
 111f075: 40                           	inc	eax
 111f076: c1 f9 06                     	sar	ecx, 0x6
 111f079: 3b c1                        	cmp	eax, ecx
 111f07b: 76 22                        	jbe	0x111f09f <.text+0x1ff>
 111f07d: 8b d1                        	mov	edx, ecx
 111f07f: d1 ea                        	shr	edx
 111f081: bb ff ff ff 03               	mov	ebx, 0x3ffffff
 111f086: 2b da                        	sub	ebx, edx
 111f088: 3b d9                        	cmp	ebx, ecx
 111f08a: 73 04                        	jae	0x111f090 <.text+0x1f0>
 111f08c: 33 c9                        	xor	ecx, ecx
 111f08e: eb 02                        	jmp	0x111f092 <.text+0x1f2>
 111f090: 03 ca                        	add	ecx, edx
 111f092: 3b c8                        	cmp	ecx, eax
 111f094: 0f 42 c8                     	cmovb	ecx, eax
 111f097: 51                           	push	ecx
 111f098: 8b ce                        	mov	ecx, esi
 111f09a: e8 51 f7 5d ff               	call	0x6fe7f0
 111f09f: 8b                           	<unknown>

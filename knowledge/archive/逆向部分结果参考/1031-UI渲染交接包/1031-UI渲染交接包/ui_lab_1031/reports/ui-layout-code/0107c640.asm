
<stdin>:	file format elf32-i386

Disassembly of section .text:

0107c640 <.text>:
 107c640: 82 01 e8                     	add	byte ptr [ecx], -0x18
 107c643: a9 38 12 00 83               	test	eax, 0x83001238
 107c648: c4 04 89                     	les	eax, [ecx + 4*ecx]
 107c64b: 85 dc                        	test	esp, ebx
 107c64d: fe ff                        	<unknown>
 107c64f: ff 8d 85 dc fe ff            	dec	dword ptr [ebp - 0x1237b]
 107c655: ff 50 8d                     	call	dword ptr [eax - 0x73]
 107c658: 8d 84 fc ff ff 51 b9         	lea	eax, [esp + 8*edi - 0x46ae0001]
 107c65f: 74 84                        	je	0x107c5e5
 107c661: af                           	scasd	eax, dword ptr es:[edi]
 107c662: 01 c7                        	add	edi, eax
 107c664: 85 e0                        	test	eax, esp
 107c666: fe ff                        	<unknown>
 107c668: ff 51 00                     	call	dword ptr [ecx]
 107c66b: 00 00                        	add	byte ptr [eax], al
 107c66d: e8 5e c5 3d ff               	call	0x458bd0
 107c672: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c678: 0f 85 44 09 00 00            	jne	0x107cfc2 <.text+0x982>
 107c67e: 68 cc fa 82 01               	push	0x182facc
 107c683: e8 68 38 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c688: 83 c4 04                     	add	esp, 0x4
 107c68b: 8d 55 cc                     	lea	edx, [ebp - 0x34]
 107c68e: 89 45 cc                     	mov	dword ptr [ebp - 0x34], eax
 107c691: 52                           	push	edx
 107c692: 8d 85 64 fe ff ff            	lea	eax, [ebp - 0x19c]
 107c698: 50                           	push	eax
 107c699: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c69e: c7 45 d0 52 00 00 00         	mov	dword ptr [ebp - 0x30], 0x52
 107c6a5: e8 26 c5 3d ff               	call	0x458bd0
 107c6aa: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c6b0: 0f 85 26 08 00 00            	jne	0x107cedc <.text+0x89c>
 107c6b6: 68 6c f6 82 01               	push	0x182f66c
 107c6bb: e8 30 38 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c6c0: 83 c4 04                     	add	esp, 0x4
 107c6c3: 8d 8d 4c ff ff ff            	lea	ecx, [ebp - 0xb4]
 107c6c9: 51                           	push	ecx
 107c6ca: 8d 95 64 fd ff ff            	lea	edx, [ebp - 0x29c]
 107c6d0: 52                           	push	edx
 107c6d1: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c6d6: 89 85 4c ff ff ff            	mov	dword ptr [ebp - 0xb4], eax
 107c6dc: c7 85 50 ff ff ff 56 00 00 00	mov	dword ptr [ebp - 0xb0], 0x56
 107c6e6: e8 e5 c4 3d ff               	call	0x458bd0
 107c6eb: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c6f1: 0f 85 fc 07 00 00            	jne	0x107cef3 <.text+0x8b3>
 107c6f7: 68 6c 1c 57 01               	push	0x1571c6c
 107c6fc: e8 ef 37 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c701: 83 c4 04                     	add	esp, 0x4
 107c704: 89 45 bc                     	mov	dword ptr [ebp - 0x44], eax
 107c707: 8d 45 bc                     	lea	eax, [ebp - 0x44]
 107c70a: 50                           	push	eax
 107c70b: 8d 8d 44 fe ff ff            	lea	ecx, [ebp - 0x1bc]
 107c711: 51                           	push	ecx
 107c712: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c717: c7 45 c0 58 00 00 00         	mov	dword ptr [ebp - 0x40], 0x58
 107c71e: e8 ad c4 3d ff               	call	0x458bd0
 107c723: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c729: 0f 85 db 07 00 00            	jne	0x107cf0a <.text+0x8ca>
 107c72f: 68 50 f6 82 01               	push	0x182f650
 107c734: e8 b7 37 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c739: 83 c4 04                     	add	esp, 0x4
 107c73c: 8d 95 0c ff ff ff            	lea	edx, [ebp - 0xf4]
 107c742: 89 85 0c ff ff ff            	mov	dword ptr [ebp - 0xf4], eax
 107c748: 52                           	push	edx
 107c749: 8d 85 e4 fc ff ff            	lea	eax, [ebp - 0x31c]
 107c74f: 50                           	push	eax
 107c750: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c755: c7 85 10 ff ff ff 5b 00 00 00	mov	dword ptr [ebp - 0xf0], 0x5b
 107c75f: e8 6c c4 3d ff               	call	0x458bd0
 107c764: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c76a: 0f 85 b1 07 00 00            	jne	0x107cf21 <.text+0x8e1>
 107c770: 68 30 f6 82 01               	push	0x182f630
 107c775: e8 76 37 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c77a: 83 c4 04                     	add	esp, 0x4
 107c77d: 8d 4d ac                     	lea	ecx, [ebp - 0x54]
 107c780: 51                           	push	ecx
 107c781: 8d 95 24 fe ff ff            	lea	edx, [ebp - 0x1dc]
 107c787: 52                           	push	edx
 107c788: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c78d: 89 45 ac                     	mov	dword ptr [ebp - 0x54], eax
 107c790: c7 45 b0 5d 00 00 00         	mov	dword ptr [ebp - 0x50], 0x5d
 107c797: e8 34 c4 3d ff               	call	0x458bd0
 107c79c: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c7a2: 0f 85 90 07 00 00            	jne	0x107cf38 <.text+0x8f8>
 107c7a8: 68 0c 77 57 01               	push	0x157770c
 107c7ad: e8 3e 37 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c7b2: 83 c4 04                     	add	esp, 0x4
 107c7b5: 89 85 3c ff ff ff            	mov	dword ptr [ebp - 0xc4], eax
 107c7bb: 8d 85 3c ff ff ff            	lea	eax, [ebp - 0xc4]
 107c7c1: 50                           	push	eax
 107c7c2: 8d 8d 44 fd ff ff            	lea	ecx, [ebp - 0x2bc]
 107c7c8: 51                           	push	ecx
 107c7c9: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c7ce: c7 85 40 ff ff ff 5f 00 00 00	mov	dword ptr [ebp - 0xc0], 0x5f
 107c7d8: e8 f3 c3 3d ff               	call	0x458bd0
 107c7dd: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c7e3: 0f 85 66 07 00 00            	jne	0x107cf4f <.text+0x90f>
 107c7e9: 68 d4 e5 80 01               	push	0x180e5d4
 107c7ee: e8 fd 36 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c7f3: 83 c4 04                     	add	esp, 0x4
 107c7f6: 8d 55 9c                     	lea	edx, [ebp - 0x64]
 107c7f9: 89 45 9c                     	mov	dword ptr [ebp - 0x64], eax
 107c7fc: 52                           	push	edx
 107c7fd: 8d 85 04 fe ff ff            	lea	eax, [ebp - 0x1fc]
 107c803: 50                           	push	eax
 107c804: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107c809: c7 45 a0 61 00 00 00         	mov	dword ptr [ebp - 0x60], 0x61
 107c810: e8 bb c3 3d ff               	call	0x458bd0
 107c815: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107c81b: 0f 85 a1 07 00 00            	jne	0x107cfc2 <.text+0x982>
 107c821: 68 ac fa 82 01               	push	0x182faac
 107c826: e8 c5 36 12 00               	call	0x119fef0 <.text+0x1238b0>
 107c82b: 83 c4 04                     	add	esp, 0x4
 107c82e: 8d 8d ec fe ff ff            	lea	ecx, [ebp - 0x114]
 107c834: 51                           	push	ecx
 107c835: 8d 95 a4 fc ff ff            	lea	edx, [ebp - 0x35c]
 107c83b: 52                           	push	edx
 107c83c: b9                           	<unknown>
 107c83d: 74 84                        	je	0x107c7c3 <.text+0x183>
 107c83f: af                           	scasd	eax, dword ptr es:[edi]

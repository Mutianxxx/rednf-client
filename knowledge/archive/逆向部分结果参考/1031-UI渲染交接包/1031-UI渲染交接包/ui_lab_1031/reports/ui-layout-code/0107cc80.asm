
<stdin>:	file format elf32-i386

Disassembly of section .text:

0107cc80 <.text>:
 107cc80: 85 44 ff ff                  	test	dword ptr [edi + 8*edi - 0x1], eax
 107cc84: ff c7                        	inc	edi
 107cc86: 85 48 ff                     	test	dword ptr [eax - 0x1], ecx
 107cc89: ff ff                        	<unknown>
 107cc8b: 8b 00                        	mov	eax, dword ptr [eax]
 107cc8d: 00 00                        	add	byte ptr [eax], al
 107cc8f: e8 3c bf 3d ff               	call	0x458bd0
 107cc94: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107cc9a: 0f 85 22 03 00 00            	jne	0x107cfc2 <.text+0x342>
 107cca0: 68 40 f7 82 01               	push	0x182f740
 107cca5: e8 46 32 12 00               	call	0x119fef0 <.text+0x123270>
 107ccaa: 83 c4 04                     	add	esp, 0x4
 107ccad: 89 85 34 ff ff ff            	mov	dword ptr [ebp - 0xcc], eax
 107ccb3: 8d 85 34 ff ff ff            	lea	eax, [ebp - 0xcc]
 107ccb9: 50                           	push	eax
 107ccba: 8d 8d 34 fd ff ff            	lea	ecx, [ebp - 0x2cc]
 107ccc0: 51                           	push	ecx
 107ccc1: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107ccc6: c7 85 38 ff ff ff 8d 00 00 00	mov	dword ptr [ebp - 0xc8], 0x8d
 107ccd0: e8 fb be 3d ff               	call	0x458bd0
 107ccd5: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107ccdb: 0f 85 e1 02 00 00            	jne	0x107cfc2 <.text+0x342>
 107cce1: 68 1c f7 82 01               	push	0x182f71c
 107cce6: e8 05 32 12 00               	call	0x119fef0 <.text+0x123270>
 107cceb: 83 c4 04                     	add	esp, 0x4
 107ccee: 8d 95 24 ff ff ff            	lea	edx, [ebp - 0xdc]
 107ccf4: 89 85 24 ff ff ff            	mov	dword ptr [ebp - 0xdc], eax
 107ccfa: 52                           	push	edx
 107ccfb: 8d 85 14 fd ff ff            	lea	eax, [ebp - 0x2ec]
 107cd01: 50                           	push	eax
 107cd02: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107cd07: c7 85 28 ff ff ff 8f 00 00 00	mov	dword ptr [ebp - 0xd8], 0x8f
 107cd11: e8 ba be 3d ff               	call	0x458bd0
 107cd16: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107cd1c: 0f 85 89 02 00 00            	jne	0x107cfab <.text+0x32b>
 107cd22: 68 04 f7 82 01               	push	0x182f704
 107cd27: e8 c4 31 12 00               	call	0x119fef0 <.text+0x123270>
 107cd2c: 83 c4 04                     	add	esp, 0x4
 107cd2f: 8d 8d 14 ff ff ff            	lea	ecx, [ebp - 0xec]
 107cd35: 51                           	push	ecx
 107cd36: 8d 95 f4 fc ff ff            	lea	edx, [ebp - 0x30c]
 107cd3c: 52                           	push	edx
 107cd3d: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107cd42: 89 85 14 ff ff ff            	mov	dword ptr [ebp - 0xec], eax
 107cd48: c7 85 18 ff ff ff 91 00 00 00	mov	dword ptr [ebp - 0xe8], 0x91
 107cd52: e8 79 be 3d ff               	call	0x458bd0
 107cd57: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107cd5d: 0f 85 5f 02 00 00            	jne	0x107cfc2 <.text+0x342>
 107cd63: 68 dc f6 82 01               	push	0x182f6dc
 107cd68: e8 83 31 12 00               	call	0x119fef0 <.text+0x123270>
 107cd6d: 83 c4 04                     	add	esp, 0x4
 107cd70: 89 85 04 ff ff ff            	mov	dword ptr [ebp - 0xfc], eax
 107cd76: 8d 85 04 ff ff ff            	lea	eax, [ebp - 0xfc]
 107cd7c: 50                           	push	eax
 107cd7d: 8d 8d d4 fc ff ff            	lea	ecx, [ebp - 0x32c]
 107cd83: 51                           	push	ecx
 107cd84: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107cd89: c7 85 08 ff ff ff 94 00 00 00	mov	dword ptr [ebp - 0xf8], 0x94
 107cd93: e8 38 be 3d ff               	call	0x458bd0
 107cd98: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107cd9e: 0f 85 1e 02 00 00            	jne	0x107cfc2 <.text+0x342>
 107cda4: 68 ac f6 82 01               	push	0x182f6ac
 107cda9: e8 42 31 12 00               	call	0x119fef0 <.text+0x123270>
 107cdae: 83 c4 04                     	add	esp, 0x4
 107cdb1: 8d 95 f4 fe ff ff            	lea	edx, [ebp - 0x10c]
 107cdb7: 89 85 f4 fe ff ff            	mov	dword ptr [ebp - 0x10c], eax
 107cdbd: 52                           	push	edx
 107cdbe: 8d 85 b4 fc ff ff            	lea	eax, [ebp - 0x34c]
 107cdc4: 50                           	push	eax
 107cdc5: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107cdca: c7 85 f8 fe ff ff 96 00 00 00	mov	dword ptr [ebp - 0x108], 0x96
 107cdd4: e8 f7 bd 3d ff               	call	0x458bd0
 107cdd9: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107cddf: 0f 85 dd 01 00 00            	jne	0x107cfc2 <.text+0x342>
 107cde5: 68 ac e0 82 01               	push	0x182e0ac
 107cdea: e8 01 31 12 00               	call	0x119fef0 <.text+0x123270>
 107cdef: 83 c4 04                     	add	esp, 0x4
 107cdf2: 8d 8d e4 fe ff ff            	lea	ecx, [ebp - 0x11c]
 107cdf8: 51                           	push	ecx
 107cdf9: 8d 95 94 fc ff ff            	lea	edx, [ebp - 0x36c]
 107cdff: 52                           	push	edx
 107ce00: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107ce05: 89 85 e4 fe ff ff            	mov	dword ptr [ebp - 0x11c], eax
 107ce0b: c7 85 e8 fe ff ff 99 00 00 00	mov	dword ptr [ebp - 0x118], 0x99
 107ce15: e8 b6 bd 3d ff               	call	0x458bd0
 107ce1a: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107ce20: 0f 85 9c 01 00 00            	jne	0x107cfc2 <.text+0x342>
 107ce26: 68 84 f6 82 01               	push	0x182f684
 107ce2b: e8 c0 30 12 00               	call	0x119fef0 <.text+0x123270>
 107ce30: 83 c4 04                     	add	esp, 0x4
 107ce33: 89 85 d4 fe ff ff            	mov	dword ptr [ebp - 0x12c], eax
 107ce39: 8d 85 d4 fe ff ff            	lea	eax, [ebp - 0x12c]
 107ce3f: 50                           	push	eax
 107ce40: 8d 8d 74 fc ff ff            	lea	ecx, [ebp - 0x38c]
 107ce46: 51                           	push	ecx
 107ce47: b9 74 84 af 01               	mov	ecx, 0x1af8474
 107ce4c: c7 85 d8 fe ff ff 9c 00 00 00	mov	dword ptr [ebp - 0x128], 0x9c
 107ce56: e8 75 bd 3d ff               	call	0x458bd0
 107ce5b: 38 1d 6c 84 af 01            	cmp	byte ptr [0x1af846c], bl
 107ce61: 0f 85 5b 01 00 00            	jne	0x107cfc2 <.text+0x342>
 107ce67: b9 70 84 af 01               	mov	ecx, 0x1af8470
 107ce6c: e8 7f 7d 12 00               	call	0x11a4bf0 <.text+0x127f70>
 107ce71: c6 05 6c 84 af 01 01         	mov	byte ptr [0x1af846c], 0x1
 107ce78: e9 e0 f5 ff ff               	jmp	0x107c45d
 107ce7d: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 107ce80: 52                           	push	edx
 107ce81: 8d 8d c8 fe ff ff            	lea	ecx, [ebp - 0x138]
 107ce87: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 107ce8a: e8 3b 96 35 00               	call	0x13d64ca <.text+0x35984a>
 107ce8f: 68 90 0f 91 01               	push	0x1910f90
 107ce94: 8d 85 c8 fe ff ff            	lea	eax, [ebp - 0x138]
 107ce9a: 50                           	push	eax
 107ce9b: c7 85 c8 fe ff ff 84 20 56 01	mov	dword ptr [ebp - 0x138], 0x1562084
 107cea5: e8 f0 9c 35 00               	call	0x13d6b9a <.text+0x359f1a>
 107ceaa: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 107cead: 51                           	push	ecx
 107ceae: 8d 8d bc fe ff ff            	lea	ecx, [ebp - 0x144]
 107ceb4: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 107ceb7: e8 0e 96 35 00               	call	0x13d64ca <.text+0x35984a>
 107cebc: 68 90 0f 91 01               	push	0x1910f90
 107cec1: 8d 95 bc fe ff ff            	lea	edx, [ebp - 0x144]
 107cec7: 52                           	push	edx
 107cec8: c7 85 bc fe ff ff 84 20 56 01	mov	dword ptr [ebp - 0x144], 0x1562084
 107ced2: e8 c3 9c 35 00               	call	0x13d6b9a <.text+0x359f1a>
 107ced7: e8 cb 9e 35 00               	call	0x13d6da7 <.text+0x35a127>
 107cedc: b8 03 00 00 00               	mov	eax, 0x3
 107cee1: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cee4: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107ceeb: 59                           	pop	ecx
 107ceec: 5f                           	pop	edi
 107ceed: 5e                           	pop	esi
 107ceee: 5b                           	pop	ebx
 107ceef: 8b e5                        	mov	esp, ebp
 107cef1: 5d                           	pop	ebp
 107cef2: c3                           	ret
 107cef3: b8 04 00 00 00               	mov	eax, 0x4
 107cef8: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cefb: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf02: 59                           	pop	ecx
 107cf03: 5f                           	pop	edi
 107cf04: 5e                           	pop	esi
 107cf05: 5b                           	pop	ebx
 107cf06: 8b e5                        	mov	esp, ebp
 107cf08: 5d                           	pop	ebp
 107cf09: c3                           	ret
 107cf0a: b8 0e 00 00 00               	mov	eax, 0xe
 107cf0f: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf12: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf19: 59                           	pop	ecx
 107cf1a: 5f                           	pop	edi
 107cf1b: 5e                           	pop	esi
 107cf1c: 5b                           	pop	ebx
 107cf1d: 8b e5                        	mov	esp, ebp
 107cf1f: 5d                           	pop	ebp
 107cf20: c3                           	ret
 107cf21: b8 0f 00 00 00               	mov	eax, 0xf
 107cf26: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf29: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf30: 59                           	pop	ecx
 107cf31: 5f                           	pop	edi
 107cf32: 5e                           	pop	esi
 107cf33: 5b                           	pop	ebx
 107cf34: 8b e5                        	mov	esp, ebp
 107cf36: 5d                           	pop	ebp
 107cf37: c3                           	ret
 107cf38: b8 0a 00 00 00               	mov	eax, 0xa
 107cf3d: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf40: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf47: 59                           	pop	ecx
 107cf48: 5f                           	pop	edi
 107cf49: 5e                           	pop	esi
 107cf4a: 5b                           	pop	ebx
 107cf4b: 8b e5                        	mov	esp, ebp
 107cf4d: 5d                           	pop	ebp
 107cf4e: c3                           	ret
 107cf4f: b8 11 00 00 00               	mov	eax, 0x11
 107cf54: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf57: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf5e: 59                           	pop	ecx
 107cf5f: 5f                           	pop	edi
 107cf60: 5e                           	pop	esi
 107cf61: 5b                           	pop	ebx
 107cf62: 8b e5                        	mov	esp, ebp
 107cf64: 5d                           	pop	ebp
 107cf65: c3                           	ret
 107cf66: b8 09 00 00 00               	mov	eax, 0x9
 107cf6b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf6e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf75: 59                           	pop	ecx
 107cf76: 5f                           	pop	edi
 107cf77: 5e                           	pop	esi
 107cf78: 5b                           	pop	ebx
 107cf79: 8b e5                        	mov	esp, ebp
 107cf7b: 5d                           	pop	ebp
 107cf7c: c3                           	ret
 107cf7d: b8 05 00 00 00               	mov	eax, 0x5
 107cf82: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf85: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cf8c: 59                           	pop	ecx
 107cf8d: 5f                           	pop	edi
 107cf8e: 5e                           	pop	esi
 107cf8f: 5b                           	pop	ebx
 107cf90: 8b e5                        	mov	esp, ebp
 107cf92: 5d                           	pop	ebp
 107cf93: c3                           	ret
 107cf94: b8 01 00 00 00               	mov	eax, 0x1
 107cf99: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cf9c: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cfa3: 59                           	pop	ecx
 107cfa4: 5f                           	pop	edi
 107cfa5: 5e                           	pop	esi
 107cfa6: 5b                           	pop	ebx
 107cfa7: 8b e5                        	mov	esp, ebp
 107cfa9: 5d                           	pop	ebp
 107cfaa: c3                           	ret
 107cfab: b8 06 00 00 00               	mov	eax, 0x6
 107cfb0: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cfb3: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cfba: 59                           	pop	ecx
 107cfbb: 5f                           	pop	edi
 107cfbc: 5e                           	pop	esi
 107cfbd: 5b                           	pop	ebx
 107cfbe: 8b e5                        	mov	esp, ebp
 107cfc0: 5d                           	pop	ebp
 107cfc1: c3                           	ret
 107cfc2: 33 c0                        	xor	eax, eax
 107cfc4: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 107cfc7: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 107cfce: 59                           	pop	ecx
 107cfcf: 5f                           	pop	edi

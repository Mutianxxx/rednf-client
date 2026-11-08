
<stdin>:	file format elf32-i386

Disassembly of section .text:

00510000 <.text>:
  510000: 00 00                        	add	byte ptr [eax], al
  510002: 00 e8                        	add	al, ch
  510004: e8 fa ff ff 68               	call	0x69510003 <.text+0x69000003>
  510009: b8 02 00 00 c7               	mov	eax, 0xc7000002
  51000e: 46                           	inc	esi
  51000f: 38 00                        	cmp	byte ptr [eax], al
  510011: 00 00                        	add	byte ptr [eax], al
  510013: 00 e8                        	add	al, ch
  510015: 67 03 ca                     	addr16		add	ecx, edx
  510018: 00 83 c4 04 89 45            	add	byte ptr [ebx + 0x458904c4], al
  51001e: ec                           	in	al, dx
  51001f: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  510023: 85 c0                        	test	eax, eax
  510025: 74 09                        	je	0x510030 <.text+0x30>
  510027: 8b c8                        	mov	ecx, eax
  510029: e8 52 ef ca 00               	call	0x11bef80 <.text+0xcaef80>
  51002e: eb 02                        	jmp	0x510032 <.text+0x32>
  510030: 33 c0                        	xor	eax, eax
  510032: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
  510035: 50                           	push	eax
  510036: c6 45 fc 00                  	mov	byte ptr [ebp - 0x4], 0x0
  51003a: 89 46 38                     	mov	dword ptr [esi + 0x38], eax
  51003d: e8 ee f2 ca 00               	call	0x11bf330 <.text+0xcaf330>
  510042: 8b c6                        	mov	eax, esi
  510044: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  510047: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  51004e: 59                           	pop	ecx
  51004f: 5e                           	pop	esi
  510050: 8b e5                        	mov	esp, ebp
  510052: 5d                           	pop	ebp
  510053: c2 04 00                     	ret	0x4
  510056: cc                           	int3
  510057: cc                           	int3
  510058: cc                           	int3
  510059: cc                           	int3
  51005a: cc                           	int3
  51005b: cc                           	int3
  51005c: cc                           	int3
  51005d: cc                           	int3
  51005e: cc                           	int3
  51005f: cc                           	int3
  510060: 55                           	push	ebp
  510061: 8b ec                        	mov	ebp, esp
  510063: 6a ff                        	push	-0x1
  510065: 68 e8 54 41 01               	push	0x14154e8
  51006a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  510070: 50                           	push	eax
  510071: 51                           	push	ecx
  510072: 56                           	push	esi
  510073: 57                           	push	edi
  510074: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  510079: 33 c5                        	xor	eax, ebp
  51007b: 50                           	push	eax
  51007c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  51007f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  510085: 8b f1                        	mov	esi, ecx
  510087: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
  51008a: 33 ff                        	xor	edi, edi
  51008c: 56                           	push	esi
  51008d: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
  510090: e8 bb fa ff ff               	call	0x50fb50
  510095: 8b 4e 38                     	mov	ecx, dword ptr [esi + 0x38]
  510098: 83 c4 04                     	add	esp, 0x4
  51009b: 3b cf                        	cmp	ecx, edi
  51009d: 74 08                        	je	0x5100a7 <.text+0xa7>
  51009f: 8b 01                        	mov	eax, dword ptr [ecx]
  5100a1: 8b 10                        	mov	edx, dword ptr [eax]
  5100a3: 6a 01                        	push	0x1
  5100a5: ff d2                        	call	edx
  5100a7: 89 7e 38                     	mov	dword ptr [esi + 0x38], edi
  5100aa: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
  5100ad: 3b c7                        	cmp	eax, edi
  5100af: 74 09                        	je	0x5100ba <.text+0xba>
  5100b1: 50                           	push	eax
  5100b2: e8 70 5a ec 00               	call	0x13d5b27 <.text+0xec5b27>
  5100b7: 83 c4 04                     	add	esp, 0x4
  5100ba: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
  5100bd: 50                           	push	eax
  5100be: 89 7e 1c                     	mov	dword ptr [esi + 0x1c], edi
  5100c1: 89 7e 20                     	mov	dword ptr [esi + 0x20], edi
  5100c4: 89 7e 24                     	mov	dword ptr [esi + 0x24], edi
  5100c7: e8 5b 5a ec 00               	call	0x13d5b27 <.text+0xec5b27>
  5100cc: 83 c4 04                     	add	esp, 0x4
  5100cf: 8d 4e 08                     	lea	ecx, [esi + 0x8]
  5100d2: 89 7e 18                     	mov	dword ptr [esi + 0x18], edi
  5100d5: e8 d6 9e d0 00               	call	0x1219fb0 <.text+0xd09fb0>
  5100da: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  5100dd: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  5100e4: 59                           	pop	ecx
  5100e5: 5f                           	pop	edi
  5100e6: 5e                           	pop	esi
  5100e7: 8b e5                        	mov	esp, ebp
  5100e9: 5d                           	pop	ebp
  5100ea: c3                           	ret
  5100eb: cc                           	int3
  5100ec: cc                           	int3
  5100ed: cc                           	int3
  5100ee: cc                           	int3
  5100ef: cc                           	int3
  5100f0: 55                           	push	ebp
  5100f1: 8b ec                        	mov	ebp, esp
  5100f3: 6a ff                        	push	-0x1
  5100f5: 68 3b bf 47 01               	push	0x147bf3b
  5100fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  510100: 50                           	push	eax
  510101: 83 ec 1c                     	sub	esp, 0x1c
  510104: 53                           	push	ebx
  510105: 56                           	push	esi
  510106: 57                           	push	edi
  510107: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  51010c: 33 c5                        	xor	eax, ebp
  51010e: 50                           	push	eax
  51010f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  510112: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  510118: 8b d9                        	mov	ebx, ecx
  51011a: 8d 45 08                     	lea	eax, [ebp + 0x8]
  51011d: 50                           	push	eax
  51011e: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  510121: 51                           	push	ecx
  510122: 8b cb                        	mov	ecx, ebx
  510124: e8 07 7b fd ff               	call	0x4e7c30
  510129: 8d 55 dc                     	lea	edx, [ebp - 0x24]
  51012c: 52                           	push	edx
  51012d: 8b cb                        	mov	ecx, ebx
  51012f: e8 5c f6 29 00               	call	0x7af790 <.text+0x29f790>
  510134: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
  510137: 33 f6                        	xor	esi, esi
  510139: 3b ce                        	cmp	ecx, esi
  51013b: 0f 84 2c 01 00 00            	je	0x51026d <.text+0x26d>
  510141: 8b 11                        	mov	edx, dword ptr [ecx]
  510143: 3b d6                        	cmp	edx, esi
  510145: 0f 84 22 01 00 00            	je	0x51026d <.text+0x26d>
  51014b: 8b 08                        	mov	ecx, dword ptr [eax]
  51014d: 3b ce                        	cmp	ecx, esi
  51014f: 75 04                        	jne	0x510155 <.text+0x155>
  510151: 33 c9                        	xor	ecx, ecx
  510153: eb 02                        	jmp	0x510157 <.text+0x157>
  510155: 8b 09                        	mov	ecx, dword ptr [ecx]
  510157: 3b d1                        	cmp	edx, ecx
  510159: 0f 85 0e 01 00 00            	jne	0x51026d <.text+0x26d>
  51015f: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  510162: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
  510165: 0f 94 c0                     	sete	al
  510168: 84 c0                        	test	al, al
  51016a: 0f 84 e7 00 00 00            	je	0x510257 <.text+0x257>
  510170: 68 bc 02 00 00               	push	0x2bc
  510175: e8 06 02 ca 00               	call	0x11b0380 <.text+0xca0380>
  51017a: 83 c4 04                     	add	esp, 0x4
  51017d: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  510180: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
  510183: 3b c6                        	cmp	eax, esi
  510185: 74 09                        	je	0x510190 <.text+0x190>
  510187: 8b c8                        	mov	ecx, eax
  510189: e8 72 19 cc 00               	call	0x11d1b00 <.text+0xcc1b00>
  51018e: 8b f0                        	mov	esi, eax
  510190: 8b 7d 0c                     	mov	edi, dword ptr [ebp + 0xc]
  510193: 8b 57 24                     	mov	edx, dword ptr [edi + 0x24]
  510196: 52                           	push	edx
  510197: 8b ce                        	mov	ecx, esi
  510199: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  5101a0: e8 9b 0b cc 00               	call	0x11d0d40 <.text+0xcc0d40>
  5101a5: 6a 01                        	push	0x1
  5101a7: 8b ce                        	mov	ecx, esi
  5101a9: e8 d2 0b cc 00               	call	0x11d0d80 <.text+0xcc0d80>
  5101ae: 68 be 00 00 00               	push	0xbe
  5101b3: 8b ce                        	mov	ecx, esi
  5101b5: e8 26 0f cc 00               	call	0x11d10e0 <.text+0xcc10e0>
  5101ba: 8b 47 20                     	mov	eax, dword ptr [edi + 0x20]
  5101bd: 50                           	push	eax
  5101be: 8b ce                        	mov	ecx, esi
  5101c0: e8 6b 0c cc 00               	call	0x11d0e30 <.text+0xcc0e30>
  5101c5: 6a 02                        	push	0x2
  5101c7: 8b ce                        	mov	ecx, esi
  5101c9: e8 42 0c cc 00               	call	0x11d0e10 <.text+0xcc0e10>
  5101ce: 6a 02                        	push	0x2
  5101d0: 8b ce                        	mov	ecx, esi
  5101d2: e8 c9 0b cc 00               	call	0x11d0da0 <.text+0xcc0da0>
  5101d7: 83 7f 18 08                  	cmp	dword ptr [edi + 0x18], 0x8
  5101db: 72 05                        	jb	0x5101e2 <.text+0x1e2>
  5101dd: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  5101e0: eb 03                        	jmp	0x5101e5 <.text+0x1e5>
  5101e2: 8d 47 04                     	lea	eax, [edi + 0x4]
  5101e5: 50                           	push	eax
  5101e6: 8b ce                        	mov	ecx, esi
  5101e8: e8 e3 0e cc 00               	call	0x11d10d0 <.text+0xcc10d0>
  5101ed: 6a 01                        	push	0x1
  5101ef: 8b ce                        	mov	ecx, esi
  5101f1: e8 ca 0b cc 00               	call	0x11d0dc0 <.text+0xcc0dc0>
  5101f6: 6a 01                        	push	0x1
  5101f8: 8b ce                        	mov	ecx, esi
  5101fa: e8 51 0c cc 00               	call	0x11d0e50 <.text+0xcc0e50>
  5101ff: 8b 4b 38                     	mov	ecx, dword ptr [ebx + 0x38]
  510202: 56                           	push	esi
  510203: e8 28 f1 ca 00               	call	0x11bf330 <.text+0xcaf330>
  510208: 8b 4f 24                     	mov	ecx, dword ptr [edi + 0x24]
  51020b: 85 c9                        	test	ecx, ecx
  51020d: 74 18                        	je	0x510227 <.text+0x227>
  51020f: 6a 01                        	push	0x1
  510211: e8 ea e0 ca 00               	call	0x11be300 <.text+0xcae300>
  510216: 8b 4f 24                     	mov	ecx, dword ptr [edi + 0x24]
  510219: 50                           	push	eax
  51021a: e8 41 fd f1 ff               	call	0x42ff60
  51021f: 50                           	push	eax
  510220: 8b ce                        	mov	ecx, esi
  510222: e8 a9 e8 ca 00               	call	0x11bead0 <.text+0xcaead0>
  510227: 66 8b 4d 08                  	mov	cx, word ptr [ebp + 0x8]
  51022b: 8d 55 ec                     	lea	edx, [ebp - 0x14]
  51022e: 52                           	push	edx
  51022f: 8d 45 d8                     	lea	eax, [ebp - 0x28]
  510232: 66 89 4d ec                  	mov	word ptr [ebp - 0x14], cx
  510236: 50                           	push	eax
  510237: 8b cb                        	mov	ecx, ebx
  510239: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
  51023c: e8 3f 8e fd ff               	call	0x4e9080
  510241: b0 01                        	mov	al, 0x1
  510243: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  510246: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  51024d: 59                           	pop	ecx
  51024e: 5f                           	pop	edi
  51024f: 5e                           	pop	esi
  510250: 5b                           	pop	ebx
  510251: 8b e5                        	mov	esp, ebp
  510253: 5d                           	pop	ebp
  510254: c2 08 00                     	ret	0x8
  510257: 32 c0                        	xor	al, al
  510259: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  51025c: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  510263: 59                           	pop	ecx
  510264: 5f                           	pop	edi
  510265: 5e                           	pop	esi
  510266: 5b                           	pop	ebx
  510267: 8b e5                        	mov	esp, ebp
  510269: 5d                           	pop	ebp
  51026a: c2 08 00                     	ret	0x8
  51026d: e8 35 6b ec 00               	call	0x13d6da7 <.text+0xec6da7>
  510272: cc                           	int3
  510273: cc                           	int3
  510274: cc                           	int3
  510275: cc                           	int3
  510276: cc                           	int3
  510277: cc                           	int3
  510278: cc                           	int3
  510279: cc                           	int3
  51027a: cc                           	int3
  51027b: cc                           	int3
  51027c: cc                           	int3
  51027d: cc                           	int3
  51027e: cc                           	int3
  51027f: cc                           	int3
  510280: 55                           	push	ebp
  510281: 8b ec                        	mov	ebp, esp
  510283: 56                           	push	esi
  510284: 8b f1                        	mov	esi, ecx
  510286: 8b 8e d8 03 00 00            	mov	ecx, dword ptr [esi + 0x3d8]
  51028c: 85 c9                        	test	ecx, ecx
  51028e: 74 34                        	je	0x5102c4 <.text+0x2c4>
  510290: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  510293: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  510296: 6a 01                        	push	0x1
  510298: 50                           	push	eax
  510299: 52                           	push	edx
  51029a: e8 31 e8 ca 00               	call	0x11bead0 <.text+0xcaead0>
  51029f: 8b 8e d8 03 00 00            	mov	ecx, dword ptr [esi + 0x3d8]
  5102a5: 6a 01                        	push	0x1
  5102a7: e8 54 e0 ca 00               	call	0x11be300 <.text+0xcae300>
  5102ac: 8b 8e d8 03 00 00            	mov	ecx, dword ptr [esi + 0x3d8]
  5102b2: 50                           	push	eax
  5102b3: e8 a8 fc f1 ff               	call	0x42ff60
  5102b8: 8b 8e f0 03 00 00            	mov	ecx, dword ptr [esi + 0x3f0]
  5102be: 50                           	push	eax
  5102bf: e8 0c e8 ca 00               	call	0x11bead0 <.text+0xcaead0>
  5102c4: 5e                           	pop	esi
  5102c5: 5d                           	pop	ebp
  5102c6: c2 08 00                     	ret	0x8
  5102c9: cc                           	int3
  5102ca: cc                           	int3
  5102cb: cc                           	int3
  5102cc: cc                           	int3
  5102cd: cc                           	int3
  5102ce: cc                           	int3
  5102cf: cc                           	int3
  5102d0: 33 d2                        	xor	edx, edx
  5102d2: 56                           	push	esi
  5102d3: 8b f1                        	mov	esi, ecx
  5102d5: 39 96 d4 03 00 00            	cmp	dword ptr [esi + 0x3d4], edx
  5102db: 8b 8e f0 03 00 00            	mov	ecx, dword ptr [esi + 0x3f0]
  5102e1: 8b 01                        	mov	eax, dword ptr [ecx]
  5102e3: 8b 40 50                     	mov	eax, dword ptr [eax + 0x50]
  5102e6: 0f 9e c2                     	setle	dl
  5102e9: 4a                           	dec	edx
  5102ea: 81 e2 ff 00 00 00            	and	edx, 0xff
  5102f0: 52                           	push	edx
  5102f1: ff d0                        	call	eax
  5102f3: 8b ce                        	mov	ecx, esi
  5102f5: 5e                           	pop	esi
  5102f6: e9 15 d8 cb 00               	jmp	0x11cdb10 <.text+0xcbdb10>
  5102fb: cc                           	int3
  5102fc: cc                           	int3
  5102fd: cc                           	int3
  5102fe: cc                           	int3
  5102ff: cc                           	int3

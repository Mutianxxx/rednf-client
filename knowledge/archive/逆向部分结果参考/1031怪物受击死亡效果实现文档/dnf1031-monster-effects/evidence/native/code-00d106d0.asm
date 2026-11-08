
D:\game\DNF1031客户端-20260708\combat_ui_1031\reports\code-00d106d0.elf:	file format elf32-i386

Disassembly of section .text:

00d106d0 <.text>:
  d106d0: 55                           	push	ebp
  d106d1: 8b ec                        	mov	ebp, esp
  d106d3: 51                           	push	ecx
  d106d4: 81 c1 88 30 00 00            	add	ecx, 0x3088
  d106da: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  d106dd: 50                           	push	eax
  d106de: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d106e1: 52                           	push	edx
  d106e2: e8 f9 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d106e7: 33 c0                        	xor	eax, eax
  d106e9: 39 45 fc                     	cmp	dword ptr [ebp - 0x4], eax
  d106ec: 0f 95 c0                     	setne	al
  d106ef: 8b e5                        	mov	esp, ebp
  d106f1: 5d                           	pop	ebp
  d106f2: c3                           	ret
  d106f3: cc                           	int3
  d106f4: cc                           	int3
  d106f5: cc                           	int3
  d106f6: cc                           	int3
  d106f7: cc                           	int3
  d106f8: cc                           	int3
  d106f9: cc                           	int3
  d106fa: cc                           	int3
  d106fb: cc                           	int3
  d106fc: cc                           	int3
  d106fd: cc                           	int3
  d106fe: cc                           	int3
  d106ff: cc                           	int3
  d10700: 55                           	push	ebp
  d10701: 8b ec                        	mov	ebp, esp
  d10703: 51                           	push	ecx
  d10704: 8b 01                        	mov	eax, dword ptr [ecx]
  d10706: 8b 90 60 04 00 00            	mov	edx, dword ptr [eax + 0x460]
  d1070c: ff d2                        	call	edx
  d1070e: 8d 4d fc                     	lea	ecx, [ebp - 0x4]
  d10711: 51                           	push	ecx
  d10712: 8d 50 08                     	lea	edx, [eax + 0x8]
  d10715: 52                           	push	edx
  d10716: 8b c8                        	mov	ecx, eax
  d10718: e8 c3 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d1071d: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  d10720: 8b e5                        	mov	esp, ebp
  d10722: 5d                           	pop	ebp
  d10723: c3                           	ret
  d10724: cc                           	int3
  d10725: cc                           	int3
  d10726: cc                           	int3
  d10727: cc                           	int3
  d10728: cc                           	int3
  d10729: cc                           	int3
  d1072a: cc                           	int3
  d1072b: cc                           	int3
  d1072c: cc                           	int3
  d1072d: cc                           	int3
  d1072e: cc                           	int3
  d1072f: cc                           	int3
  d10730: 55                           	push	ebp
  d10731: 8b ec                        	mov	ebp, esp
  d10733: 83 ec 08                     	sub	esp, 0x8
  d10736: 8b 01                        	mov	eax, dword ptr [ecx]
  d10738: 8b 90 40 04 00 00            	mov	edx, dword ptr [eax + 0x440]
  d1073e: 56                           	push	esi
  d1073f: 57                           	push	edi
  d10740: 6a 03                        	push	0x3
  d10742: ff d2                        	call	edx
  d10744: 8b f0                        	mov	esi, eax
  d10746: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
  d10749: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  d1074c: 50                           	push	eax
  d1074d: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d10750: 52                           	push	edx
  d10751: e8 8a 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d10756: 8b 7d fc                     	mov	edi, dword ptr [ebp - 0x4]
  d10759: 8d 4e 18                     	lea	ecx, [esi + 0x18]
  d1075c: 8d 45 f8                     	lea	eax, [ebp - 0x8]
  d1075f: 50                           	push	eax
  d10760: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d10763: 52                           	push	edx
  d10764: e8 77 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d10769: 0f 57 c0                     	xorps	xmm0, xmm0
  d1076c: f3 0f 2a c7                  	cvtsi2ss	xmm0, edi
  d10770: f3 0f 59 45 f8               	mulss	xmm0, dword ptr [ebp - 0x8]
  d10775: 5f                           	pop	edi
  d10776: f3 0f 2c c0                  	cvttss2si	eax, xmm0
  d1077a: 5e                           	pop	esi
  d1077b: 8b e5                        	mov	esp, ebp
  d1077d: 5d                           	pop	ebp
  d1077e: c3                           	ret
  d1077f: cc                           	int3
  d10780: 55                           	push	ebp
  d10781: 8b ec                        	mov	ebp, esp
  d10783: 51                           	push	ecx
  d10784: 8b 01                        	mov	eax, dword ptr [ecx]
  d10786: 8b 90 60 04 00 00            	mov	edx, dword ptr [eax + 0x460]
  d1078c: ff d2                        	call	edx
  d1078e: 8d 4d fc                     	lea	ecx, [ebp - 0x4]
  d10791: 51                           	push	ecx
  d10792: 8d 50 14                     	lea	edx, [eax + 0x14]
  d10795: 52                           	push	edx
  d10796: 8d 48 0c                     	lea	ecx, [eax + 0xc]
  d10799: e8 42 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d1079e: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  d107a1: 8b e5                        	mov	esp, ebp
  d107a3: 5d                           	pop	ebp
  d107a4: c3                           	ret
  d107a5: cc                           	int3
  d107a6: cc                           	int3
  d107a7: cc                           	int3
  d107a8: cc                           	int3
  d107a9: cc                           	int3
  d107aa: cc                           	int3
  d107ab: cc                           	int3
  d107ac: cc                           	int3
  d107ad: cc                           	int3
  d107ae: cc                           	int3
  d107af: cc                           	int3
  d107b0: 55                           	push	ebp
  d107b1: 8b ec                        	mov	ebp, esp
  d107b3: 83 ec 08                     	sub	esp, 0x8
  d107b6: 8b 01                        	mov	eax, dword ptr [ecx]
  d107b8: 8b 90 40 04 00 00            	mov	edx, dword ptr [eax + 0x440]
  d107be: 56                           	push	esi
  d107bf: 57                           	push	edi
  d107c0: 6a 03                        	push	0x3
  d107c2: ff d2                        	call	edx
  d107c4: 8b f0                        	mov	esi, eax
  d107c6: 8d 4e 24                     	lea	ecx, [esi + 0x24]
  d107c9: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  d107cc: 50                           	push	eax
  d107cd: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d107d0: 52                           	push	edx
  d107d1: e8 0a 06 49 00               	call	0x11a0de0 <.text+0x490710>
  d107d6: 8b 7d fc                     	mov	edi, dword ptr [ebp - 0x4]
  d107d9: 8d 4e 30                     	lea	ecx, [esi + 0x30]
  d107dc: 8d 45 f8                     	lea	eax, [ebp - 0x8]
  d107df: 50                           	push	eax
  d107e0: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d107e3: 52                           	push	edx
  d107e4: e8 f7 05 49 00               	call	0x11a0de0 <.text+0x490710>
  d107e9: 0f 57 c0                     	xorps	xmm0, xmm0
  d107ec: f3 0f 2a c7                  	cvtsi2ss	xmm0, edi
  d107f0: f3 0f 59 45 f8               	mulss	xmm0, dword ptr [ebp - 0x8]
  d107f5: 5f                           	pop	edi
  d107f6: f3 0f 2c c0                  	cvttss2si	eax, xmm0
  d107fa: 5e                           	pop	esi
  d107fb: 8b e5                        	mov	esp, ebp
  d107fd: 5d                           	pop	ebp
  d107fe: c3                           	ret
  d107ff: cc                           	int3
  d10800: 55                           	push	ebp
  d10801: 8b ec                        	mov	ebp, esp
  d10803: 53                           	push	ebx
  d10804: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  d10807: 57                           	push	edi
  d10808: 8b f9                        	mov	edi, ecx
  d1080a: 0f b6 c3                     	movzx	eax, bl
  d1080d: 8d 8f 98 06 00 00            	lea	ecx, [edi + 0x698]
  d10813: 8d 51 08                     	lea	edx, [ecx + 0x8]
  d10816: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  d10819: 52                           	push	edx
  d1081a: 8d 45 08                     	lea	eax, [ebp + 0x8]
  d1081d: 50                           	push	eax
  d1081e: e8 0d 01 49 00               	call	0x11a0930 <.text+0x490260>
  d10823: 8b 8f e8 34 00 00            	mov	ecx, dword ptr [edi + 0x34e8]
  d10829: 8b 87 ec 34 00 00            	mov	eax, dword ptr [edi + 0x34ec]
  d1082f: 2b                           	<unknown>

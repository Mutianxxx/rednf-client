
<stdin>:	file format elf32-i386

Disassembly of section .text:

00576520 <.text>:
  576520: ec                           	in	al, dx
  576521: 51                           	push	ecx
  576522: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
  576525: e8 e6 fe ff ff               	call	0x576410
  57652a: 6a 00                        	push	0x0
  57652c: 6a 00                        	push	0x0
  57652e: e8 67 06 e6 00               	call	0x13d6b9a <.text+0xe6067a>
  576533: cc                           	int3
  576534: cc                           	int3
  576535: cc                           	int3
  576536: cc                           	int3
  576537: cc                           	int3
  576538: cc                           	int3
  576539: cc                           	int3
  57653a: cc                           	int3
  57653b: cc                           	int3
  57653c: cc                           	int3
  57653d: cc                           	int3
  57653e: cc                           	int3
  57653f: cc                           	int3
  576540: 55                           	push	ebp
  576541: 8b ec                        	mov	ebp, esp
  576543: 51                           	push	ecx
  576544: 53                           	push	ebx
  576545: 56                           	push	esi
  576546: 8b f1                        	mov	esi, ecx
  576548: 57                           	push	edi
  576549: 8d 46 08                     	lea	eax, [esi + 0x8]
  57654c: 50                           	push	eax
  57654d: 8d 4d fc                     	lea	ecx, [ebp - 0x4]
  576550: 51                           	push	ecx
  576551: 8b ce                        	mov	ecx, esi
  576553: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  57655a: e8 d1 a3 c2 00               	call	0x11a0930 <.text+0xc2a410>
  57655f: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
  576562: 8d 51 08                     	lea	edx, [ecx + 0x8]
  576565: 52                           	push	edx
  576566: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  576569: 33 db                        	xor	ebx, ebx
  57656b: 50                           	push	eax
  57656c: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  57656f: e8 bc a3 c2 00               	call	0x11a0930 <.text+0xc2a410>
  576574: 8d 4e 18                     	lea	ecx, [esi + 0x18]
  576577: 8d 51 08                     	lea	edx, [ecx + 0x8]
  57657a: 52                           	push	edx
  57657b: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  57657e: 50                           	push	eax
  57657f: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  576582: e8 a9 a3 c2 00               	call	0x11a0930 <.text+0xc2a410>
  576587: 8b 4e 2c                     	mov	ecx, dword ptr [esi + 0x2c]
  57658a: 8b 51 04                     	mov	edx, dword ptr [ecx + 0x4]
  57658d: 52                           	push	edx
  57658e: 8d 4e 24                     	lea	ecx, [esi + 0x24]
  576591: e8 3a 56 f2 ff               	call	0x49bbd0
  576596: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
  576599: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
  57659c: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
  57659f: 89 00                        	mov	dword ptr [eax], eax
  5765a1: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
  5765a4: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
  5765a7: 89 5e 30                     	mov	dword ptr [esi + 0x30], ebx
  5765aa: 8b 46 40                     	mov	eax, dword ptr [esi + 0x40]
  5765ad: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
  5765b0: 51                           	push	ecx
  5765b1: 8d 4e 38                     	lea	ecx, [esi + 0x38]
  5765b4: e8 17 56 f2 ff               	call	0x49bbd0
  5765b9: 8b 46 40                     	mov	eax, dword ptr [esi + 0x40]
  5765bc: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
  5765bf: 8b 46 40                     	mov	eax, dword ptr [esi + 0x40]
  5765c2: 89 00                        	mov	dword ptr [eax], eax
  5765c4: 8b 46 40                     	mov	eax, dword ptr [esi + 0x40]
  5765c7: 5f                           	pop	edi
  5765c8: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
  5765cb: 89 5e 44                     	mov	dword ptr [esi + 0x44], ebx
  5765ce: 5e                           	pop	esi
  5765cf: 5b                           	pop	ebx
  5765d0: 8b e5                        	mov	esp, ebp
  5765d2: 5d                           	pop	ebp
  5765d3: c3                           	ret
  5765d4: cc                           	int3
  5765d5: cc                           	int3
  5765d6: cc                           	int3
  5765d7: cc                           	int3
  5765d8: cc                           	int3
  5765d9: cc                           	int3
  5765da: cc                           	int3
  5765db: cc                           	int3
  5765dc: cc                           	int3
  5765dd: cc                           	int3
  5765de: cc                           	int3
  5765df: cc                           	int3
  5765e0: 55                           	push	ebp
  5765e1: 8b ec                        	mov	ebp, esp
  5765e3: 6a ff                        	push	-0x1
  5765e5: 68 00 ce 41 01               	push	0x141ce00
  5765ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  5765f0: 50                           	push	eax
  5765f1: 83 ec 28                     	sub	esp, 0x28
  5765f4: 53                           	push	ebx
  5765f5: 56                           	push	esi
  5765f6: 57                           	push	edi
  5765f7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  5765fc: 33 c5                        	xor	eax, ebp
  5765fe: 50                           	push	eax
  5765ff: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  576602: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  576608: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
  57660b: 8b f1                        	mov	esi, ecx
  57660d: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  576610: 33 ff                        	xor	edi, edi
  576612: 6a 08                        	push	0x8
  576614: 89 3e                        	mov	dword ptr [esi], edi
  576616: e8 ff 04 e6 00               	call	0x13d6b1a <.text+0xe605fa>
  57661b: 83 c4 04                     	add	esp, 0x4
  57661e: 3b c7                        	cmp	eax, edi
  576620: 0f 84 a2 00 00 00            	je	0x5766c8 <.text+0x1a8>
  576626: 89 06                        	mov	dword ptr [esi], eax
  576628: 33 c9                        	xor	ecx, ecx
  57662a: 33 d2                        	xor	edx, edx
  57662c: 89 08                        	mov	dword ptr [eax], ecx
  57662e: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
  576631: 8b 06                        	mov	eax, dword ptr [esi]
  576633: 89 30                        	mov	dword ptr [eax], esi
  576635: 6a 3c                        	push	0x3c
  576637: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
  57663a: 89 7e 0c                     	mov	dword ptr [esi + 0xc], edi
  57663d: e8 d8 04 e6 00               	call	0x13d6b1a <.text+0xe605fa>
  576642: 83 c4 04                     	add	esp, 0x4
  576645: 3b c7                        	cmp	eax, edi
  576647: 74 5b                        	je	0x5766a4 <.text+0x184>
  576649: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
  57664c: 89 00                        	mov	dword ptr [eax], eax
  57664e: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  576651: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
  576654: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  576657: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
  57665a: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
  57665d: b8 01 00 00 00               	mov	eax, 0x1
  576662: 88 41 38                     	mov	byte ptr [ecx + 0x38], al
  576665: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
  576668: 88 42 39                     	mov	byte ptr [edx + 0x39], al
  57666b: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  57666e: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  576671: 50                           	push	eax
  576672: 8b ce                        	mov	ecx, esi
  576674: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
  576678: e8 13 5d f2 ff               	call	0x49c390
  57667d: 8b c6                        	mov	eax, esi
  57667f: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  576682: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  576689: 59                           	pop	ecx
  57668a: 5f                           	pop	edi
  57668b: 5e                           	pop	esi
  57668c: 5b                           	pop	ebx
  57668d: 8b e5                        	mov	esp, ebp
  57668f: 5d                           	pop	ebp
  576690: c2 04 00                     	ret	0x4
  576693: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  576696: e8 85 60 f2 ff               	call	0x49c720
  57669b: 33 ff                        	xor	edi, edi
  57669d: 57                           	push	edi
  57669e: 57                           	push	edi
  57669f: e8 f6 04 e6 00               	call	0x13d6b9a <.text+0xe6067a>
  5766a4: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  5766a7: 51                           	push	ecx
  5766a8: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  5766ab: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
  5766ae: e8 17 fe e5 00               	call	0x13d64ca <.text+0xe5ffaa>
  5766b3: 68 90 0f 91 01               	push	0x1910f90
  5766b8: 8d 55 d8                     	lea	edx, [ebp - 0x28]
  5766bb: 52                           	push	edx
  5766bc: c7 45 d8 84 20 56 01         	mov	dword ptr [ebp - 0x28], 0x1562084
  5766c3: e8 d2 04 e6 00               	call	0x13d6b9a <.text+0xe6067a>
  5766c8: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
  5766cb: 50                           	push	eax
  5766cc: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  5766cf: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
  5766d2: e8 f3 fd e5 00               	call	0x13d64ca <.text+0xe5ffaa>
  5766d7: 68 90 0f 91 01               	push	0x1910f90
  5766dc: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  5766df: 51                           	push	ecx
  5766e0: c7 45 cc 84 20 56 01         	mov	dword ptr [ebp - 0x34], 0x1562084
  5766e7: e8 ae 04 e6 00               	call	0x13d6b9a <.text+0xe6067a>
  5766ec: cc                           	int3
  5766ed: cc                           	int3
  5766ee: cc                           	int3
  5766ef: cc                           	int3
  5766f0: 55                           	push	ebp
  5766f1: 8b ec                        	mov	ebp, esp
  5766f3: 53                           	push	ebx
  5766f4: 56                           	push	esi
  5766f5: 57                           	push	edi
  5766f6: 8b f9                        	mov	edi, ecx
  5766f8: 8b 47 0c                     	mov	eax, dword ptr [edi + 0xc]
  5766fb: 3d c0 16 6c 01               	cmp	eax, 0x16c16c0
  576700: 72 1e                        	jb	0x576720 <.text+0x200>
  576702: 8b 75 14                     	mov	esi, dword ptr [ebp + 0x14]
  576705: 8d 4e 10                     	lea	ecx, [esi + 0x10]
  576708: e8 a3 d0 ff ff               	call	0x5737b0
  57670d: 56                           	push	esi
  57670e: e8 14 f4 e5 00               	call	0x13d5b27 <.text+0xe5f607>
  576713: 83 c4 04                     	add	esp, 0x4
  576716: 68 c4 51 56 01               	push	0x15651c4
  57671b: e8 aa b0 e4 00               	call	0x13c17ca <.text+0xe4b2aa>
  576720: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
  576723: 40                           	inc	eax
  576724: 89 47 0c                     	mov	dword ptr [edi + 0xc], eax
  576727: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
  57672a: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  57672d: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  576730: 3b c1                        	cmp	eax, ecx
  576732: 75 0d                        	jne	0x576741 <.text+0x221>
  576734: 89 51 04                     	mov	dword ptr [ecx + 0x4], edx
  576737: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  57673a: 89 10                        	mov	dword ptr [eax], edx
  57673c: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  57673f: eb 1e                        	jmp	0x57675f <.text+0x23f>
  576741: 80 7d 0c 00                  	cmp	byte ptr [ebp + 0xc], 0x0
  576745: 74 0d                        	je	0x576754 <.text+0x234>
  576747: 89 10                        	mov	dword ptr [eax], edx
  576749: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  57674c: 3b 01                        	cmp	eax, dword ptr [ecx]
  57674e: 75 12                        	jne	0x576762 <.text+0x242>
  576750: 89 11                        	mov	dword ptr [ecx], edx
  576752: eb 0e                        	jmp	0x576762 <.text+0x242>
  576754: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  576757: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  57675a: 3b 41 08                     	cmp	eax, dword ptr [ecx + 0x8]
  57675d: 75 03                        	jne	0x576762 <.text+0x242>
  57675f: 89 51 08                     	mov	dword ptr [ecx + 0x8], edx
  576762: 8b 42 04                     	mov	eax, dword ptr [edx + 0x4]
  576765: 80 b8 c0 00 00 00 00         	cmp	byte ptr [eax + 0xc0], 0x0
  57676c: 8b f2                        	mov	esi, edx
  57676e: b3 01                        	mov	bl, 0x1
  576770: 0f 85 6e 01 00 00            	jne	0x5768e4 <.text+0x3c4>
  576776: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
  576779: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
  57677c: 3b 01                        	cmp	eax, dword ptr [ecx]
  57677e: 0f 85 bb 00 00 00            	jne	0x57683f <.text+0x31f>
  576784: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  576787: 80 b9 c0 00 00 00 00         	cmp	byte ptr [ecx + 0xc0], 0x0
  57678e: 0f 84 b6 00 00 00            	je	0x57684a <.text+0x32a>
  576794: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
  576797: 75 3e                        	jne	0x5767d7 <.text+0x2b7>
  576799: 8b f0                        	mov	esi, eax
  57679b: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  57679e: 8b 10                        	mov	edx, dword ptr [eax]
  5767a0: 89 56 08                     	mov	dword ptr [esi + 0x8], edx
  5767a3: 8b 08                        	mov	ecx, dword ptr [eax]
  5767a5: 80 b9 c1 00 00 00 00         	cmp	byte ptr [ecx + 0xc1], 0x0
  5767ac: 75 03                        	jne	0x5767b1 <.text+0x291>
  5767ae: 89 71 04                     	mov	dword ptr [ecx + 0x4], esi
  5767b1: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  5767b4: 89 48 04                     	mov	dword ptr [eax + 0x4], ecx
  5767b7: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  5767ba: 3b 71 04                     	cmp	esi, dword ptr [ecx + 0x4]
  5767bd: 75 05                        	jne	0x5767c4 <.text+0x2a4>
  5767bf: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  5767c2: eb 0e                        	jmp	0x5767d2 <.text+0x2b2>
  5767c4: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  5767c7: 3b 31                        	cmp	esi, dword ptr [ecx]
  5767c9: 75 04                        	jne	0x5767cf <.text+0x2af>
  5767cb: 89 01                        	mov	dword ptr [ecx], eax
  5767cd: eb 03                        	jmp	0x5767d2 <.text+0x2b2>
  5767cf: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  5767d2: 89 30                        	mov	dword ptr [eax], esi
  5767d4: 89 46 04                     	mov	dword ptr [esi + 0x4], eax
  5767d7: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
  5767da: 88 9a c0 00 00 00            	mov	byte ptr [edx + 0xc0], bl
  5767e0: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
  5767e3: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
  5767e6: c6 81 c0 00 00 00 00         	mov	byte ptr [ecx + 0xc0], 0x0
  5767ed: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
  5767f0: 8b 42 04                     	mov	eax, dword ptr [edx + 0x4]
  5767f3: 8b 08                        	mov	ecx, dword ptr [eax]
  5767f5: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  5767f8: 89 10                        	mov	dword ptr [eax], edx
  5767fa: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  5767fd: 80 ba c1 00 00 00 00         	cmp	byte ptr [edx + 0xc1], 0x0
  576804: 75 03                        	jne	0x576809 <.text+0x2e9>
  576806: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  576809: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
  57680c: 89 51 04                     	mov	dword ptr [ecx + 0x4], edx
  57680f: 8b 57 08                     	mov	edx, dword ptr [edi + 0x8]
  576812: 3b 42 04                     	cmp	eax, dword ptr [edx + 0x4]
  576815: 75 0b                        	jne	0x576822 <.text+0x302>
  576817: 89 4a 04                     	mov	dword ptr [edx + 0x4], ecx
  57681a: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57681d: e9 ac 00 00 00               	jmp	0x5768ce <.text+0x3ae>
  576822: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
  576825: 3b 42 08                     	cmp	eax, dword ptr [edx + 0x8]
  576828: 75 0b                        	jne	0x576835 <.text+0x315>
  57682a: 89 4a 08                     	mov	dword ptr [edx + 0x8], ecx
  57682d: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  576830: e9 99 00 00 00               	jmp	0x5768ce <.text+0x3ae>
  576835: 89 0a                        	mov	dword ptr [edx], ecx
  576837: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57683a: e9 8f 00 00 00               	jmp	0x5768ce <.text+0x3ae>
  57683f: 8b 09                        	mov	ecx, dword ptr [ecx]
  576841: 80 b9 c0 00 00 00 00         	cmp	byte ptr [ecx + 0xc0], 0x0
  576848: 75 21                        	jne	0x57686b <.text+0x34b>
  57684a: 88 98 c0 00 00 00            	mov	byte ptr [eax + 0xc0], bl
  576850: 88 99 c0 00 00 00            	mov	byte ptr [ecx + 0xc0], bl
  576856: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  576859: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
  57685c: c6 80 c0 00 00 00 00         	mov	byte ptr [eax + 0xc0], 0x0
  576863: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  576866: 8b 71 04                     	mov	esi, dword ptr [ecx + 0x4]
  576869: eb 69                        	jmp	0x5768d4 <.text+0x3b4>
  57686b: 3b 30                        	cmp	esi, dword ptr [eax]
  57686d: 75 0a                        	jne	0x576879 <.text+0x359>
  57686f: 8b f0                        	mov	esi, eax
  576871: 56                           	push	esi
  576872: 8b cf                        	mov	ecx, edi
  576874: e8 c7 a4 ff ff               	call	0x570d40
  576879: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
  57687c: 88 9a c0 00 00 00            	mov	byte ptr [edx + 0xc0], bl
  576882: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
  576885: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
  576888: c6 81 c0 00 00 00 00         	mov	byte ptr [ecx + 0xc0], 0x0
  57688f: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
  576892: 8b 42 04                     	mov	eax, dword ptr [edx + 0x4]
  576895: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  576898: 8b 11                        	mov	edx, dword ptr [ecx]
  57689a: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  57689d: 8b 11                        	mov	edx, dword ptr [ecx]
  57689f: 80 ba c1 00 00 00 00         	cmp	byte ptr [edx + 0xc1], 0x0
  5768a6: 75 03                        	jne	0x5768ab <.text+0x38b>
  5768a8: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  5768ab: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
  5768ae: 89 51 04                     	mov	dword ptr [ecx + 0x4], edx
  5768b1: 8b 57 08                     	mov	edx, dword ptr [edi + 0x8]
  5768b4: 3b 42 04                     	cmp	eax, dword ptr [edx + 0x4]
  5768b7: 75 05                        	jne	0x5768be <.text+0x39e>
  5768b9: 89 4a 04                     	mov	dword ptr [edx + 0x4], ecx
  5768bc: eb 0e                        	jmp	0x5768cc <.text+0x3ac>
  5768be: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
  5768c1: 3b 02                        	cmp	eax, dword ptr [edx]
  5768c3: 75 04                        	jne	0x5768c9 <.text+0x3a9>
  5768c5: 89 0a                        	mov	dword ptr [edx], ecx
  5768c7: eb 03                        	jmp	0x5768cc <.text+0x3ac>
  5768c9: 89 4a 08                     	mov	dword ptr [edx + 0x8], ecx
  5768cc: 89 01                        	mov	dword ptr [ecx], eax
  5768ce: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
  5768d1: 89 48 04                     	mov	dword ptr [eax + 0x4], ecx
  5768d4: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
  5768d7: 80 b8 c0 00 00 00 00         	cmp	byte ptr [eax + 0xc0], 0x0
  5768de: 0f 84 92 fe ff ff            	je	0x576776 <.text+0x256>
  5768e4: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  5768e7: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
  5768ea: 88 98 c0 00 00 00            	mov	byte ptr [eax + 0xc0], bl
  5768f0: 8b 0f                        	mov	ecx, dword ptr [edi]
  5768f2: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  5768f5: 5f                           	pop	edi
  5768f6: 5e                           	pop	esi
  5768f7: c7 40 04 00 00 00 00         	mov	dword ptr [eax + 0x4], 0x0
  5768fe: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  576901: 89 08                        	mov	dword ptr [eax], ecx
  576903: 5b                           	pop	ebx
  576904: 5d                           	pop	ebp
  576905: c2 10 00                     	ret	0x10
  576908: cc                           	int3
  576909: cc                           	int3
  57690a: cc                           	int3
  57690b: cc                           	int3
  57690c: cc                           	int3
  57690d: cc                           	int3
  57690e: cc                           	int3
  57690f: cc                           	int3
  576910: 55                           	push	ebp
  576911: 8b ec                        	mov	ebp, esp
  576913: 6a ff                        	push	-0x1
  576915: 68 31 ce 41 01               	push	0x141ce31
  57691a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  576920: 50                           	push	eax
  576921: 83 ec 1c                     	sub	esp, 0x1c
  576924: 53                           	push	ebx
  576925: 56                           	push	esi
  576926: 57                           	push	edi
  576927: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  57692c: 33 c5                        	xor	eax, ebp
  57692e: 50                           	push	eax
  57692f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  576932: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  576938: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
  57693b: 8b f9                        	mov	edi, ecx
  57693d: 68 c4 00 00 00               	push	0xc4
  576942: e8 d3 01 e6 00               	call	0x13d6b1a <.text+0xe605fa>
  576947: 8b f0                        	mov	esi, eax
  576949: 33 c9                        	xor	ecx, ecx
  57694b: 83 c4 04                     	add	esp, 0x4
  57694e: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  576951: 3b f1                        	cmp	esi, ecx
  576953: 74 6a                        	je	0x5769bf <.text+0x49f>
  576955: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  576958: 89 06                        	mov	dword ptr [esi], eax
  57695a: 8b 57 08                     	mov	edx, dword ptr [edi + 0x8]
  57695d: 89 56 04                     	mov	dword ptr [esi + 0x4], edx
  576960: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  576963: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
  576966: 8d 46 0c                     	lea	eax, [esi + 0xc]
  576969: 66 89 8e c0 00 00 00         	mov	word ptr [esi + 0xc0], cx

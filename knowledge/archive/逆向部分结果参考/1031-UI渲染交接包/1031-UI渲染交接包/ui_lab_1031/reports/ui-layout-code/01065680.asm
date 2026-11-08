
<stdin>:	file format elf32-i386

Disassembly of section .text:

01065680 <.text>:
 1065680: 0d 80 3d ac 82               	or	eax, 0x82ac3d80
 1065685: af                           	scasd	eax, dword ptr es:[edi]
 1065686: 01 00                        	add	dword ptr [eax], eax
 1065688: 0f 84 16 03 00 00            	je	0x10659a4 <.text+0x324>
 106568e: 39 7d c8                     	cmp	dword ptr [ebp - 0x38], edi
 1065691: 72 0b                        	jb	0x106569e <.text+0x1e>
 1065693: 8b 55 b4                     	mov	edx, dword ptr [ebp - 0x4c]
 1065696: 89 95 38 fe ff ff            	mov	dword ptr [ebp - 0x1c8], edx
 106569c: eb 09                        	jmp	0x10656a7 <.text+0x27>
 106569e: 8d 45 b4                     	lea	eax, [ebp - 0x4c]
 10656a1: 89 85 38 fe ff ff            	mov	dword ptr [ebp - 0x1c8], eax
 10656a7: 8d 8d 38 fe ff ff            	lea	ecx, [ebp - 0x1c8]
 10656ad: 51                           	push	ecx
 10656ae: 8d 95 7c fb ff ff            	lea	edx, [ebp - 0x484]
 10656b4: 52                           	push	edx
 10656b5: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 10656ba: e8 51 30 3f ff               	call	0x458710
 10656bf: 8b 08                        	mov	ecx, dword ptr [eax]
 10656c1: 3b ce                        	cmp	ecx, esi
 10656c3: 74 08                        	je	0x10656cd <.text+0x4d>
 10656c5: 8b 09                        	mov	ecx, dword ptr [ecx]
 10656c7: 3b ce                        	cmp	ecx, esi
 10656c9: 74 02                        	je	0x10656cd <.text+0x4d>
 10656cb: 8b 31                        	mov	esi, dword ptr [ecx]
 10656cd: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
 10656d0: 8d 85 94 fb ff ff            	lea	eax, [ebp - 0x46c]
 10656d6: 50                           	push	eax
 10656d7: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 10656dc: e8 5f ec 75 ff               	call	0x7c4340
 10656e1: 33 db                        	xor	ebx, ebx
 10656e3: 3b f3                        	cmp	esi, ebx
 10656e5: 0f 84 1e 19 00 00            	je	0x1067009 <.text+0x1989>
 10656eb: 8b 36                        	mov	esi, dword ptr [esi]
 10656ed: 3b f3                        	cmp	esi, ebx
 10656ef: 0f 84 14 19 00 00            	je	0x1067009 <.text+0x1989>
 10656f5: 8b 08                        	mov	ecx, dword ptr [eax]
 10656f7: 3b cb                        	cmp	ecx, ebx
 10656f9: 75 04                        	jne	0x10656ff <.text+0x7f>
 10656fb: 33 c9                        	xor	ecx, ecx
 10656fd: eb 02                        	jmp	0x1065701 <.text+0x81>
 10656ff: 8b 09                        	mov	ecx, dword ptr [ecx]
 1065701: 3b f1                        	cmp	esi, ecx
 1065703: 0f 85 00 19 00 00            	jne	0x1067009 <.text+0x1989>
 1065709: 3b 78 08                     	cmp	edi, dword ptr [eax + 0x8]
 106570c: 0f 94 c0                     	sete	al
 106570f: 84 c0                        	test	al, al
 1065711: 0f 94 c0                     	sete	al
 1065714: 84 c0                        	test	al, al
 1065716: 0f 84 bd 0f 00 00            	je	0x10666d9 <.text+0x1059>
 106571c: 8b 47 10                     	mov	eax, dword ptr [edi + 0x10]
 106571f: 3d 44 01 00 00               	cmp	eax, 0x144
 1065724: 0f 8f ad 0b 00 00            	jg	0x10662d7 <.text+0xc57>
 106572a: 0f 84 25 01 00 00            	je	0x1065855 <.text+0x1d5>
 1065730: 3d 16 01 00 00               	cmp	eax, 0x116
 1065735: 0f 8f 23 05 00 00            	jg	0x1065c5e <.text+0x5de>
 106573b: 74 50                        	je	0x106578d <.text+0x10d>
 106573d: 85 c0                        	test	eax, eax
 106573f: 74 0b                        	je	0x106574c <.text+0xcc>
 1065741: 3d 13 01 00 00               	cmp	eax, 0x113
 1065746: 0f 85 8d 0f 00 00            	jne	0x10666d9 <.text+0x1059>
 106574c: 38 1d ac 82 af 01            	cmp	byte ptr [0x1af82ac], bl
 1065752: 0f 85 72 02 00 00            	jne	0x10659ca <.text+0x34a>
 1065758: 68 1c e2 82 01               	push	0x182e21c
 106575d: e8 8e a7 13 00               	call	0x119fef0 <.text+0x13a870>
 1065762: 83 c4 04                     	add	esp, 0x4
 1065765: 8d 8d 28 fd ff ff            	lea	ecx, [ebp - 0x2d8]
 106576b: 51                           	push	ecx
 106576c: 8d 95 90 fa ff ff            	lea	edx, [ebp - 0x570]
 1065772: 52                           	push	edx
 1065773: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 1065778: 89 85 28 fd ff ff            	mov	dword ptr [ebp - 0x2d8], eax
 106577e: c7 85 2c fd ff ff 13 01 00 00	mov	dword ptr [ebp - 0x2d4], 0x113
 1065788: e8 43 34 3f ff               	call	0x458bd0
 106578d: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 1065794: 0f 85 3b 02 00 00            	jne	0x10659d5 <.text+0x355>
 106579a: 68 00 e2 82 01               	push	0x182e200
 106579f: e8 4c a7 13 00               	call	0x119fef0 <.text+0x13a870>
 10657a4: 83 c4 04                     	add	esp, 0x4
 10657a7: 89 85 18 fd ff ff            	mov	dword ptr [ebp - 0x2e8], eax
 10657ad: 8d 85 18 fd ff ff            	lea	eax, [ebp - 0x2e8]
 10657b3: 50                           	push	eax
 10657b4: 8d 8d 40 fb ff ff            	lea	ecx, [ebp - 0x4c0]
 10657ba: 51                           	push	ecx
 10657bb: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 10657c0: c7 85 1c fd ff ff 16 01 00 00	mov	dword ptr [ebp - 0x2e4], 0x116
 10657ca: e8 01 34 3f ff               	call	0x458bd0
 10657cf: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 10657d6: 0f 85 bd 06 00 00            	jne	0x1065e99 <.text+0x819>
 10657dc: 68 dc e1 82 01               	push	0x182e1dc
 10657e1: e8 0a a7 13 00               	call	0x119fef0 <.text+0x13a870>
 10657e6: 83 c4 04                     	add	esp, 0x4
 10657e9: 8d 8d 08 fd ff ff            	lea	ecx, [ebp - 0x2f8]
 10657ef: 51                           	push	ecx
 10657f0: 8d 95 e0 fa ff ff            	lea	edx, [ebp - 0x520]
 10657f6: 52                           	push	edx
 10657f7: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 10657fc: 89 85 08 fd ff ff            	mov	dword ptr [ebp - 0x2f8], eax
 1065802: c7 85 0c fd ff ff 1f 01 00 00	mov	dword ptr [ebp - 0x2f4], 0x11f
 106580c: e8 bf 33 3f ff               	call	0x458bd0
 1065811: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 1065818: 0f 85 59 04 00 00            	jne	0x1065c77 <.text+0x5f7>
 106581e: 68 b8 e1 82 01               	push	0x182e1b8
 1065823: e8 c8 a6 13 00               	call	0x119fef0 <.text+0x13a870>
 1065828: 83 c4 04                     	add	esp, 0x4
 106582b: 89 85 f8 fc ff ff            	mov	dword ptr [ebp - 0x308], eax
 1065831: 8d 85 f8 fc ff ff            	lea	eax, [ebp - 0x308]
 1065837: 50                           	push	eax
 1065838: 8d 8d 20 fb ff ff            	lea	ecx, [ebp - 0x4e0]
 106583e: 51                           	push	ecx
 106583f: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 1065844: c7 85 fc fc ff ff 31 01 00 00	mov	dword ptr [ebp - 0x304], 0x131
 106584e: e8 7d 33 3f ff               	call	0x458bd0
 1065853: 33 db                        	xor	ebx, ebx
 1065855: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 106585c: 0f 85 57 08 00 00            	jne	0x10660b9 <.text+0xa39>
 1065862: 68 90 e1 82 01               	push	0x182e190
 1065867: e8 84 a6 13 00               	call	0x119fef0 <.text+0x13a870>
 106586c: 83 c4 04                     	add	esp, 0x4
 106586f: 8d 95 e8 fc ff ff            	lea	edx, [ebp - 0x318]
 1065875: 89 85 e8 fc ff ff            	mov	dword ptr [ebp - 0x318], eax
 106587b: 52                           	push	edx
 106587c: 8d 85 a0 fa ff ff            	lea	eax, [ebp - 0x560]
 1065882: 50                           	push	eax
 1065883: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 1065888: c7 85 ec fc ff ff 44 01 00 00	mov	dword ptr [ebp - 0x314], 0x144
 1065892: e8 39 33 3f ff               	call	0x458bd0
 1065897: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 106589e: 0f 85 4f 0a 00 00            	jne	0x10662f3 <.text+0xc73>
 10658a4: 68 68 e1 82 01               	push	0x182e168
 10658a9: e8 42 a6 13 00               	call	0x119fef0 <.text+0x13a870>
 10658ae: 83 c4 04                     	add	esp, 0x4
 10658b1: 8d 95 d8 fc ff ff            	lea	edx, [ebp - 0x328]
 10658b7: 89 85 d8 fc ff ff            	mov	dword ptr [ebp - 0x328], eax
 10658bd: 52                           	push	edx
 10658be: 8d 85 60 fb ff ff            	lea	eax, [ebp - 0x4a0]
 10658c4: 50                           	push	eax
 10658c5: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 10658ca: c7 85 dc fc ff ff 5d 01 00 00	mov	dword ptr [ebp - 0x324], 0x15d
 10658d4: e8 f7 32 3f ff               	call	0x458bd0
 10658d9: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 10658e0: 0f 85 aa 0b 00 00            	jne	0x1066490 <.text+0xe10>
 10658e6: 68 44 e1 82 01               	push	0x182e144
 10658eb: e8 00 a6 13 00               	call	0x119fef0 <.text+0x13a870>
 10658f0: 83 c4 04                     	add	esp, 0x4
 10658f3: 8d 95 30 fd ff ff            	lea	edx, [ebp - 0x2d0]
 10658f9: 89 85 30 fd ff ff            	mov	dword ptr [ebp - 0x2d0], eax
 10658ff: 52                           	push	edx
 1065900: 8d 85 c0 fa ff ff            	lea	eax, [ebp - 0x540]
 1065906: 50                           	push	eax
 1065907: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 106590c: c7 85 34 fd ff ff 6b 01 00 00	mov	dword ptr [ebp - 0x2cc], 0x16b
 1065916: e8 b5 32 3f ff               	call	0x458bd0
 106591b: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 1065922: 0f 85 36 0c 00 00            	jne	0x106655e <.text+0xede>
 1065928: 68 20 e1 82 01               	push	0x182e120
 106592d: e8 be a5 13 00               	call	0x119fef0 <.text+0x13a870>
 1065932: 83 c4 04                     	add	esp, 0x4
 1065935: 89 85 40 fd ff ff            	mov	dword ptr [ebp - 0x2c0], eax
 106593b: 8d 85 40 fd ff ff            	lea	eax, [ebp - 0x2c0]
 1065941: 50                           	push	eax
 1065942: 8d 8d 50 fb ff ff            	lea	ecx, [ebp - 0x4b0]
 1065948: 51                           	push	ecx
 1065949: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 106594e: c7 85 44 fd ff ff 74 01 00 00	mov	dword ptr [ebp - 0x2bc], 0x174
 1065958: e8 73 32 3f ff               	call	0x458bd0
 106595d: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 1065964: 0f 85 60 0d 00 00            	jne	0x10666ca <.text+0x104a>
 106596a: 68 f8 e0 82 01               	push	0x182e0f8
 106596f: e8 7c a5 13 00               	call	0x119fef0 <.text+0x13a870>
 1065974: 83 c4 04                     	add	esp, 0x4
 1065977: 89 85 20 fd ff ff            	mov	dword ptr [ebp - 0x2e0], eax
 106597d: 8d 85 20 fd ff ff            	lea	eax, [ebp - 0x2e0]
 1065983: 50                           	push	eax
 1065984: 8d 8d 30 fb ff ff            	lea	ecx, [ebp - 0x4d0]
 106598a: 51                           	push	ecx
 106598b: b9 b4 82 af 01               	mov	ecx, 0x1af82b4
 1065990: c7 85 24 fd ff ff 8c 01 00 00	mov	dword ptr [ebp - 0x2dc], 0x18c
 106599a: e8 31 32 3f ff               	call	0x458bd0
 106599f: e9 35 0d 00 00               	jmp	0x10666d9 <.text+0x1059>
 10659a4: b9 b0 82 af 01               	mov	ecx, 0x1af82b0
 10659a9: e8 12 f2 13 00               	call	0x11a4bc0 <.text+0x13f540>
 10659ae: 80 3d ac 82 af 01 00         	cmp	byte ptr [0x1af82ac], 0x0
 10659b5: 0f 84 9d fd ff ff            	je	0x1065758 <.text+0xd8>
 10659bb: b9 b0 82 af 01               	mov	ecx, 0x1af82b0
 10659c0: e8 2b f2 13 00               	call	0x11a4bf0 <.text+0x13f570>
 10659c5: e9 e9 fb ff ff               	jmp	0x10655b3
 10659ca: 88 9d 36 fe ff ff            	mov	byte ptr [ebp - 0x1ca], bl
 10659d0: e9 04 0d 00 00               	jmp	0x10666d9 <.text+0x1059>
 10659d5: 33 f6                        	xor	esi, esi
 10659d7: 6a 08                        	push	0x8
 10659d9: 89 b5 ac fe ff ff            	mov	dword ptr [ebp - 0x154], esi
 10659df: e8 36 11 37 00               	call	0x13d6b1a <.text+0x37149a>
 10659e4: 83 c4 04                     	add	esp, 0x4
 10659e7: 3b c6                        	cmp	eax, esi
 10659e9: 0f 84 05 20 00 00            	je	0x10679f4 <.text+0x2374>
 10659ef: 89 85 ac fe ff ff            	mov	dword ptr [ebp - 0x154], eax
 10659f5: 33 c9                        	xor	ecx, ecx
 10659f7: 89 08                        	mov	dword ptr [eax], ecx
 10659f9: 33 d2                        	xor	edx, edx
 10659fb: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 10659fe: 8b 85 ac fe ff ff            	mov	eax, dword ptr [ebp - 0x154]
 1065a04: 8d 95 ac fe ff ff            	lea	edx, [ebp - 0x154]
 1065a0a: 89 10                        	mov	dword ptr [eax], edx
 1065a0c: c7 85 c4 fe ff ff 07 00 00 00	mov	dword ptr [ebp - 0x13c], 0x7
 1065a16: 89 b5 c0 fe ff ff            	mov	dword ptr [ebp - 0x140], esi
 1065a1c: 66 89 8d b0 fe ff ff         	mov	word ptr [ebp - 0x150], cx
 1065a23: 52                           	push	edx
 1065a24: c6 45 fc 11                  	mov	byte ptr [ebp - 0x4], 0x11
 1065a28: e8 23 f7 1b 00               	call	0x1225150 <.text+0x1bfad0>
 1065a2d: 83 c4 04                     	add	esp, 0x4
 1065a30: 84 c0                        	test	al, al
 1065a32: 0f 84 d8 01 00 00            	je	0x1065c10 <.text+0x590>
 1065a38: 39 b5 c0 fe ff ff            	cmp	dword ptr [ebp - 0x140], esi
 1065a3e: 0f 84 cc 01 00 00            	je	0x1065c10 <.text+0x590>
 1065a44: 83 bd c4 fe ff ff 08         	cmp	dword ptr [ebp - 0x13c], 0x8
 1065a4b: 0f 82 a6 00 00 00            	jb	0x1065af7 <.text+0x477>
 1065a51: 8b bd b0 fe ff ff            	mov	edi, dword ptr [ebp - 0x150]
 1065a57: 85 ff                        	test	edi, edi
 1065a59: 0f 84 a3 00 00 00            	je	0x1065b02 <.text+0x482>
 1065a5f: 8d 85 84 fd ff ff            	lea	eax, [ebp - 0x27c]
 1065a65: 50                           	push	eax
 1065a66: 83 ec 20                     	sub	esp, 0x20
 1065a69: 8b f4                        	mov	esi, esp
 1065a6b: 89 a5 38 fe ff ff            	mov	dword ptr [ebp - 0x1c8], esp
 1065a71: 33 db                        	xor	ebx, ebx
 1065a73: 6a 08                        	push	0x8
 1065a75: 89 b5 38 fe ff ff            	mov	dword ptr [ebp - 0x1c8], esi
 1065a7b: 89 1e                        	mov	dword ptr [esi], ebx
 1065a7d: e8 98 10 37 00               	call	0x13d6b1a <.text+0x37149a>
 1065a82: 83 c4 04                     	add	esp, 0x4
 1065a85: 3b c3                        	cmp	eax, ebx
 1065a87: 0f 84 01 1f 00 00            	je	0x106798e <.text+0x230e>
 1065a8d: 33 c9                        	xor	ecx, ecx
 1065a8f: 89 06                        	mov	dword ptr [esi], eax
 1065a91: 33 d2                        	xor	edx, edx
 1065a93: 89 08                        	mov	dword ptr [eax], ecx
 1065a95: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1065a98: 8b 0e                        	mov	ecx, dword ptr [esi]
 1065a9a: 89 31                        	mov	dword ptr [ecx], esi
 1065a9c: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 1065aa3: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 1065aa6: 8b c7                        	mov	eax, edi
 1065aa8: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 1065aac: c6 45 fc 12                  	mov	byte ptr [ebp - 0x4], 0x12
 1065ab0: 8d 50 02                     	lea	edx, [eax + 0x2]
 1065ab3: 66 8b 08                     	mov	cx, word ptr [eax]
 1065ab6: 83 c0 02                     	add	eax, 0x2
 1065ab9: 66 3b cb                     	cmp	cx, bx
 1065abc: 75 f5                        	jne	0x1065ab3 <.text+0x433>
 1065abe: 2b c2                        	sub	eax, edx
 1065ac0: d1 f8                        	sar	eax
 1065ac2: 50                           	push	eax
 1065ac3: 57                           	push	edi
 1065ac4: 8b ce                        	mov	ecx, esi
 1065ac6: e8 65 a5 3a ff               	call	0x410030
 1065acb: 8b 8d 48 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1b8]
 1065ad1: c6 45 fc 11                  	mov	byte ptr [ebp - 0x4], 0x11
 1065ad5: e8 06 d6 ff ff               	call	0x10630e0
 1065ada: 84 c0                        	test	al, al
 1065adc: 74 24                        	je	0x1065b02 <.text+0x482>
 1065ade: 8b 85 84 fd ff ff            	mov	eax, dword ptr [ebp - 0x27c]
 1065ae4: 8b 8d 48 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1b8]
 1065aea: 6a 01                        	push	0x1
 1065aec: 50                           	push	eax
 1065aed: e8 ae d7 ff ff               	call	0x10632a0
 1065af2: e9 0f 01 00 00               	jmp	0x1065c06 <.text+0x586>
 1065af7: 8d bd b0 fe ff ff            	lea	edi, [ebp - 0x150]
 1065afd: e9 5d ff ff ff               	jmp	0x1065a5f <.text+0x3df>
 1065b02: 33 db                        	xor	ebx, ebx
 1065b04: 6a 08                        	push	0x8
 1065b06: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1065b09: e8 0c 10 37 00               	call	0x13d6b1a <.text+0x37149a>
 1065b0e: 83 c4 04                     	add	esp, 0x4
 1065b11: 3b c3                        	cmp	eax, ebx
 1065b13: 0f 84 a8 1e 00 00            	je	0x10679c1 <.text+0x2341>
 1065b19: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 1065b1c: 33 c9                        	xor	ecx, ecx
 1065b1e: 33 d2                        	xor	edx, edx
 1065b20: 89 08                        	mov	dword ptr [eax], ecx
 1065b22: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1065b25: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1065b28: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1065b2b: 89 0a                        	mov	dword ptr [edx], ecx
 1065b2d: 33 c0                        	xor	eax, eax
 1065b2f: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
 1065b33: 8b c7                        	mov	eax, edi
 1065b35: c6 45 fc 13                  	mov	byte ptr [ebp - 0x4], 0x13
 1065b39: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 1065b40: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1065b43: 8d 50 02                     	lea	edx, [eax + 0x2]
 1065b46: 66 8b 08                     	mov	cx, word ptr [eax]
 1065b49: 83 c0 02                     	add	eax, 0x2
 1065b4c: 66 3b cb                     	cmp	cx, bx
 1065b4f: 75 f5                        	jne	0x1065b46 <.text+0x4c6>
 1065b51: 2b c2                        	sub	eax, edx
 1065b53: d1 f8                        	sar	eax
 1065b55: 50                           	push	eax
 1065b56: 57                           	push	edi
 1065b57: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1065b5a: e8 d1 a4 3a ff               	call	0x410030
 1065b5f: 8b b5 48 fe ff ff            	mov	esi, dword ptr [ebp - 0x1b8]
 1065b65: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1065b68: 51                           	push	ecx
 1065b69: 8d 95 3c fc ff ff            	lea	edx, [ebp - 0x3c4]
 1065b6f: 52                           	push	edx
 1065b70: 8d 4e 2c                     	lea	ecx, [esi + 0x2c]
 1065b73: c6 45 fc 14                  	mov	byte ptr [ebp - 0x4], 0x14
 1065b77: e8 d4 dd ff ff               	call	0x1063950
 1065b7c: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 1065b80: c6 45 fc 11                  	mov	byte ptr [ebp - 0x4], 0x11
 1065b84: 72 0c                        	jb	0x1065b92 <.text+0x512>
 1065b86: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 1065b89: 50                           	push	eax
 1065b8a: e8 98 ff 36 00               	call	0x13d5b27 <.text+0x3704a7>
 1065b8f: 83 c4 04                     	add	esp, 0x4
 1065b92: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1065b95: 33 c9                        	xor	ecx, ecx
 1065b97: 52                           	push	edx
 1065b98: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 1065b9f: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1065ba2: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 1065ba6: e8 7c ff 36 00               	call	0x13d5b27 <.text+0x3704a7>
 1065bab: 83 c4 04                     	add	esp, 0x4
 1065bae: 8d 85 ac fb ff ff            	lea	eax, [ebp - 0x454]
 1065bb4: 50                           	push	eax
 1065bb5: 8d 4e 2c                     	lea	ecx, [esi + 0x2c]
 1065bb8: e8 d3 9b 74 ff               	call	0x7af790
 1065bbd: 8b 8d 3c fc ff ff            	mov	ecx, dword ptr [ebp - 0x3c4]
 1065bc3: 3b cb                        	cmp	ecx, ebx
 1065bc5: 0f 84 3e 14 00 00            	je	0x1067009 <.text+0x1989>
 1065bcb: 8b 11                        	mov	edx, dword ptr [ecx]
 1065bcd: 3b d3                        	cmp	edx, ebx
 1065bcf: 0f                           	<unknown>

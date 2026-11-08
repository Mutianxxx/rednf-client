
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e9080 <.text>:
  4e9080: 55                           	push	ebp
  4e9081: 8b ec                        	mov	ebp, esp
  4e9083: 83 ec 0c                     	sub	esp, 0xc
  4e9086: 53                           	push	ebx
  4e9087: 56                           	push	esi
  4e9088: 57                           	push	edi
  4e9089: 8b d9                        	mov	ebx, ecx
  4e908b: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e908e: 50                           	push	eax
  4e908f: 8d 4b 08                     	lea	ecx, [ebx + 0x8]
  4e9092: e8 79 46 e3 00               	call	0x131d710 <.text+0xe34690>
  4e9097: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
  4e909a: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
  4e909d: 8b 57 04                     	mov	edx, dword ptr [edi + 0x4]
  4e90a0: 51                           	push	ecx
  4e90a1: 52                           	push	edx
  4e90a2: 57                           	push	edi
  4e90a3: 8d 4b 08                     	lea	ecx, [ebx + 0x8]
  4e90a6: e8 c5 62 02 00               	call	0x50f370 <.text+0x262f0>
  4e90ab: 8b 4b 10                     	mov	ecx, dword ptr [ebx + 0x10]
  4e90ae: ba fe ff ff 1f               	mov	edx, 0x1ffffffe
  4e90b3: 2b d1                        	sub	edx, ecx
  4e90b5: 83 fa 01                     	cmp	edx, 0x1
  4e90b8: 73 0a                        	jae	0x4e90c4 <.text+0x44>
  4e90ba: 68 50 76 56 01               	push	0x1567650
  4e90bf: e8 06 87 ed 00               	call	0x13c17ca <.text+0xed874a>
  4e90c4: 41                           	inc	ecx
  4e90c5: 89 4b 10                     	mov	dword ptr [ebx + 0x10], ecx
  4e90c8: 83 ec 0c                     	sub	esp, 0xc
  4e90cb: 89 47 04                     	mov	dword ptr [edi + 0x4], eax
  4e90ce: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
  4e90d1: 8b d4                        	mov	edx, esp
  4e90d3: 89 01                        	mov	dword ptr [ecx], eax
  4e90d5: 89 65 0c                     	mov	dword ptr [ebp + 0xc], esp
  4e90d8: 52                           	push	edx
  4e90d9: 8b cb                        	mov	ecx, ebx
  4e90db: e8 f0 7d ce 00               	call	0x11d0ed0 <.text+0xce7e50>
  4e90e0: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e90e3: 50                           	push	eax
  4e90e4: 8d 4b 08                     	lea	ecx, [ebx + 0x8]
  4e90e7: e8 24 46 e3 00               	call	0x131d710 <.text+0xe34690>
  4e90ec: 8b 08                        	mov	ecx, dword ptr [eax]
  4e90ee: 85 c9                        	test	ecx, ecx
  4e90f0: 74 12                        	je	0x4e9104 <.text+0x84>
  4e90f2: 8b 09                        	mov	ecx, dword ptr [ecx]
  4e90f4: 85 c9                        	test	ecx, ecx
  4e90f6: 74 0c                        	je	0x4e9104 <.text+0x84>
  4e90f8: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  4e90fb: 85 c0                        	test	eax, eax
  4e90fd: 74 05                        	je	0x4e9104 <.text+0x84>
  4e90ff: 3b 41 04                     	cmp	eax, dword ptr [ecx + 0x4]
  4e9102: 75 05                        	jne	0x4e9109 <.text+0x89>
  4e9104: e8 9e dc ee 00               	call	0x13d6da7 <.text+0xeedd27>
  4e9109: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
  4e910c: 83 c0 08                     	add	eax, 0x8
  4e910f: 50                           	push	eax
  4e9110: 56                           	push	esi
  4e9111: 8b cb                        	mov	ecx, ebx
  4e9113: e8 28 6b 02 00               	call	0x50fc40 <.text+0x26bc0>
  4e9118: 5f                           	pop	edi
  4e9119: 8b c6                        	mov	eax, esi
  4e911b: 5e                           	pop	esi
  4e911c: 5b                           	pop	ebx
  4e911d: 8b e5                        	mov	esp, ebp
  4e911f: 5d                           	pop	ebp
  4e9120: c2 08 00                     	ret	0x8

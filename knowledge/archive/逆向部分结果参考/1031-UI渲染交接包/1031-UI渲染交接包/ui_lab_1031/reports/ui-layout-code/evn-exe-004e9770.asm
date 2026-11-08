
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e9770 <.text>:
  4e9770: 55                           	push	ebp
  4e9771: 8b ec                        	mov	ebp, esp
  4e9773: 56                           	push	esi
  4e9774: 57                           	push	edi
  4e9775: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
  4e9778: 57                           	push	edi
  4e9779: 8b f1                        	mov	esi, ecx
  4e977b: e8 a0 e7 ff ff               	call	0x4e7f20
  4e9780: 85 c0                        	test	eax, eax
  4e9782: 74 06                        	je	0x4e978a <.text+0x1a>
  4e9784: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9788: 75 48                        	jne	0x4e97d2 <.text+0x62>
  4e978a: 66 83 ff 18                  	cmp	di, 0x18
  4e978e: 74 42                        	je	0x4e97d2 <.text+0x62>
  4e9790: 57                           	push	edi
  4e9791: 8b ce                        	mov	ecx, esi
  4e9793: e8 88 fd ff ff               	call	0x4e9520
  4e9798: 8b f8                        	mov	edi, eax
  4e979a: 85 ff                        	test	edi, edi
  4e979c: 74 34                        	je	0x4e97d2 <.text+0x62>
  4e979e: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e97a4: 53                           	push	ebx
  4e97a5: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e97ab: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e97af: 85 c9                        	test	ecx, ecx
  4e97b1: 74 08                        	je	0x4e97bb <.text+0x4b>
  4e97b3: 8b 07                        	mov	eax, dword ptr [edi]
  4e97b5: 50                           	push	eax
  4e97b6: e8 75 5b cd 00               	call	0x11bf330 <.text+0xcd5bc0>
  4e97bb: 85 db                        	test	ebx, ebx
  4e97bd: 74 0b                        	je	0x4e97ca <.text+0x5a>
  4e97bf: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
  4e97c2: 51                           	push	ecx
  4e97c3: 8b cb                        	mov	ecx, ebx
  4e97c5: e8 66 5b cd 00               	call	0x11bf330 <.text+0xcd5bc0>
  4e97ca: 8b ce                        	mov	ecx, esi
  4e97cc: e8 bf df ff ff               	call	0x4e7790
  4e97d1: 5b                           	pop	ebx
  4e97d2: 5f                           	pop	edi
  4e97d3: 5e                           	pop	esi
  4e97d4: 5d                           	pop	ebp
  4e97d5: c2 04 00                     	ret	0x4

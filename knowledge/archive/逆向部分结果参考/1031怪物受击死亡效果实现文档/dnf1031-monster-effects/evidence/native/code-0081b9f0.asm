
D:\game\DNF1031客户端-20260708\combat_ui_1031\reports\code-0081b9f0.elf:	file format elf32-i386

Disassembly of section .text:

0081b9f0 <.text>:
  81b9f0: 55                           	push	ebp
  81b9f1: 8b ec                        	mov	ebp, esp
  81b9f3: 51                           	push	ecx
  81b9f4: 53                           	push	ebx
  81b9f5: 8b d9                        	mov	ebx, ecx
  81b9f7: 8b 03                        	mov	eax, dword ptr [ebx]
  81b9f9: 8b 90 00 05 00 00            	mov	edx, dword ptr [eax + 0x500]
  81b9ff: ff d2                        	call	edx
  81ba01: 8a 55 08                     	mov	dl, byte ptr [ebp + 0x8]
  81ba04: 3a d0                        	cmp	dl, al
  81ba06: 74 4e                        	je	0x81ba56 <.text+0x66>
  81ba08: 0f b6 c2                     	movzx	eax, dl
  81ba0b: 8d 8b 88 30 00 00            	lea	ecx, [ebx + 0x3088]
  81ba11: 8d 51 08                     	lea	edx, [ecx + 0x8]
  81ba14: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  81ba17: 52                           	push	edx
  81ba18: 8d 45 fc                     	lea	eax, [ebp - 0x4]
  81ba1b: 50                           	push	eax
  81ba1c: e8 0f 4f 98 00               	call	0x11a0930 <.text+0x984f40>
  81ba21: 80 7d 08 00                  	cmp	byte ptr [ebp + 0x8], 0x0
  81ba25: 74 2f                        	je	0x81ba56 <.text+0x66>
  81ba27: 56                           	push	esi
  81ba28: 57                           	push	edi
  81ba29: 33 f6                        	xor	esi, esi
  81ba2b: 8d bb 8c 2c 00 00            	lea	edi, [ebx + 0x2c8c]
  81ba31: 8b 13                        	mov	edx, dword ptr [ebx]
  81ba33: 8b 82 40 05 00 00            	mov	eax, dword ptr [edx + 0x540]
  81ba39: 56                           	push	esi
  81ba3a: 8b cb                        	mov	ecx, ebx
  81ba3c: ff d0                        	call	eax
  81ba3e: 84 c0                        	test	al, al
  81ba40: 74 09                        	je	0x81ba4b <.text+0x5b>
  81ba42: 8b 0f                        	mov	ecx, dword ptr [edi]
  81ba44: 8b 11                        	mov	edx, dword ptr [ecx]
  81ba46: 8b 42 40                     	mov	eax, dword ptr [edx + 0x40]
  81ba49: ff d0                        	call	eax
  81ba4b: 46                           	inc	esi
  81ba4c: 83 c7 04                     	add	edi, 0x4
  81ba4f: 83 fe 12                     	cmp	esi, 0x12
  81ba52: 7c dd                        	jl	0x81ba31 <.text+0x41>
  81ba54: 5f                           	pop	edi
  81ba55: 5e                           	pop	esi
  81ba56: 5b                           	pop	ebx
  81ba57: 8b e5                        	mov	esp, ebp
  81ba59: 5d                           	pop	ebp
  81ba5a: c2 04 00                     	ret	0x4


<stdin>:	file format elf32-i386

Disassembly of section .text:

011c2ca0 <.text>:
 11c2ca0: 55                           	push	ebp
 11c2ca1: 8b ec                        	mov	ebp, esp
 11c2ca3: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11c2ca6: 53                           	push	ebx
 11c2ca7: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11c2caa: 56                           	push	esi
 11c2cab: 57                           	push	edi
 11c2cac: 6a 00                        	push	0x0
 11c2cae: 8b f1                        	mov	esi, ecx
 11c2cb0: 8b 4d 18                     	mov	ecx, dword ptr [ebp + 0x18]
 11c2cb3: 8b 06                        	mov	eax, dword ptr [esi]
 11c2cb5: 8b 80 ac 00 00 00            	mov	eax, dword ptr [eax + 0xac]
 11c2cbb: 6a 00                        	push	0x0
 11c2cbd: 51                           	push	ecx
 11c2cbe: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11c2cc1: 52                           	push	edx
 11c2cc2: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11c2cc5: 51                           	push	ecx
 11c2cc6: 52                           	push	edx
 11c2cc7: 53                           	push	ebx
 11c2cc8: 8b ce                        	mov	ecx, esi
 11c2cca: ff d0                        	call	eax
 11c2ccc: 8b f8                        	mov	edi, eax
 11c2cce: 85 ff                        	test	edi, edi
 11c2cd0: 74 17                        	je	0x11c2ce9 <.text+0x49>
 11c2cd2: 85 db                        	test	ebx, ebx
 11c2cd4: 74 13                        	je	0x11c2ce9 <.text+0x49>
 11c2cd6: 8b 4d 1c                     	mov	ecx, dword ptr [ebp + 0x1c]
 11c2cd9: 51                           	push	ecx
 11c2cda: 8b cb                        	mov	ecx, ebx
 11c2cdc: e8 ef 1e ff ff               	call	0x11b4bd0
 11c2ce1: 89 86 c8 02 00 00            	mov	dword ptr [esi + 0x2c8], eax
 11c2ce7: 8b c7                        	mov	eax, edi
 11c2ce9: 5f                           	pop	edi
 11c2cea: 5e                           	pop	esi
 11c2ceb: 5b                           	pop	ebx
 11c2cec: 5d                           	pop	ebp
 11c2ced: c2                           	<unknown>
 11c2cee: 18                           	<unknown>

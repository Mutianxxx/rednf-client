
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e7f90 <.text>:
  4e7f90: 55                           	push	ebp
  4e7f91: 8b ec                        	mov	ebp, esp
  4e7f93: 83 ec 18                     	sub	esp, 0x18
  4e7f96: 56                           	push	esi
  4e7f97: 8d 71 3c                     	lea	esi, [ecx + 0x3c]
  4e7f9a: 8d 45 08                     	lea	eax, [ebp + 0x8]
  4e7f9d: 50                           	push	eax
  4e7f9e: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
  4e7fa1: 51                           	push	ecx
  4e7fa2: 8b ce                        	mov	ecx, esi
  4e7fa4: e8 87 fc ff ff               	call	0x4e7c30
  4e7fa9: 8d 55 e8                     	lea	edx, [ebp - 0x18]
  4e7fac: 52                           	push	edx
  4e7fad: 8b ce                        	mov	ecx, esi
  4e7faf: e8 dc 77 2c 00               	call	0x7af790 <.text+0x2c7800>
  4e7fb4: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
  4e7fb7: 85 d2                        	test	edx, edx
  4e7fb9: 74 2a                        	je	0x4e7fe5 <.text+0x55>
  4e7fbb: 8b 32                        	mov	esi, dword ptr [edx]
  4e7fbd: 85 f6                        	test	esi, esi
  4e7fbf: 74 24                        	je	0x4e7fe5 <.text+0x55>
  4e7fc1: 8b 08                        	mov	ecx, dword ptr [eax]
  4e7fc3: 85 c9                        	test	ecx, ecx
  4e7fc5: 74 02                        	je	0x4e7fc9 <.text+0x39>
  4e7fc7: 8b 09                        	mov	ecx, dword ptr [ecx]
  4e7fc9: 3b f1                        	cmp	esi, ecx
  4e7fcb: 5e                           	pop	esi
  4e7fcc: 75 17                        	jne	0x4e7fe5 <.text+0x55>
  4e7fce: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4e7fd1: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
  4e7fd4: 74 1d                        	je	0x4e7ff3 <.text+0x63>
  4e7fd6: 8b 02                        	mov	eax, dword ptr [edx]
  4e7fd8: 85 c0                        	test	eax, eax
  4e7fda: 74 09                        	je	0x4e7fe5 <.text+0x55>
  4e7fdc: 85 c9                        	test	ecx, ecx
  4e7fde: 74 05                        	je	0x4e7fe5 <.text+0x55>
  4e7fe0: 3b 48 04                     	cmp	ecx, dword ptr [eax + 0x4]
  4e7fe3: 75 05                        	jne	0x4e7fea <.text+0x5a>
  4e7fe5: e8 bd ed ee 00               	call	0x13d6da7 <.text+0xeeee17>
  4e7fea: 8b 41 0c                     	mov	eax, dword ptr [ecx + 0xc]
  4e7fed: 8b e5                        	mov	esp, ebp
  4e7fef: 5d                           	pop	ebp
  4e7ff0: c2 04 00                     	ret	0x4
  4e7ff3: 33 c0                        	xor	eax, eax
  4e7ff5: 8b e5                        	mov	esp, ebp
  4e7ff7: 5d                           	pop	ebp
  4e7ff8: c2 04 00                     	ret	0x4

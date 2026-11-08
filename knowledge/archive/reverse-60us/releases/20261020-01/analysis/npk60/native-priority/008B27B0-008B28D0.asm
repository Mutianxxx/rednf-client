008b27b0  55                       push       ebp
008b27b1  8bec                     mov        ebp, esp
008b27b3  83ec08                   sub        esp, 8
008b27b6  53                       push       ebx
008b27b7  56                       push       esi
008b27b8  8b7508                   mov        esi, dword ptr [ebp + 8]
008b27bb  8b0e                     mov        ecx, dword ptr [esi]
008b27bd  8b4604                   mov        eax, dword ptr [esi + 4]
008b27c0  c1e003                   shl        eax, 3
008b27c3  8bd1                     mov        edx, ecx
008b27c5  c1ea1d                   shr        edx, 0x1d
008b27c8  0bc2                     or         eax, edx
008b27ca  8bd8                     mov        ebx, eax
008b27cc  c1eb18                   shr        ebx, 0x18
008b27cf  885df8                   mov        byte ptr [ebp - 8], bl
008b27d2  8bd8                     mov        ebx, eax
008b27d4  c1eb10                   shr        ebx, 0x10
008b27d7  8845fb                   mov        byte ptr [ebp - 5], al
008b27da  8d14cd00000000           lea        edx, [ecx*8]
008b27e1  885df9                   mov        byte ptr [ebp - 7], bl
008b27e4  8bd8                     mov        ebx, eax
008b27e6  8bc2                     mov        eax, edx
008b27e8  c1e818                   shr        eax, 0x18
008b27eb  8845fc                   mov        byte ptr [ebp - 4], al
008b27ee  8bc2                     mov        eax, edx
008b27f0  c1e810                   shr        eax, 0x10
008b27f3  8845fd                   mov        byte ptr [ebp - 3], al
008b27f6  8bc2                     mov        eax, edx
008b27f8  c1e808                   shr        eax, 8
008b27fb  c1eb08                   shr        ebx, 8
008b27fe  83e13f                   and        ecx, 0x3f
008b2801  83f938                   cmp        ecx, 0x38
008b2804  8845fe                   mov        byte ptr [ebp - 2], al
008b2807  885dfa                   mov        byte ptr [ebp - 6], bl
008b280a  8855ff                   mov        byte ptr [ebp - 1], dl
008b280d  b838000000               mov        eax, 0x38
008b2812  7205                     jb         0x8b2819
008b2814  b878000000               mov        eax, 0x78
008b2819  2bc1                     sub        eax, ecx
008b281b  50                       push       eax
008b281c  6840dbfa00               push       0xfadb40
008b2821  56                       push       esi
008b2822  e8b9feffff               call       0x8b26e0
008b2827  6a08                     push       8
008b2829  8d4df8                   lea        ecx, [ebp - 8]
008b282c  51                       push       ecx
008b282d  56                       push       esi
008b282e  e8adfeffff               call       0x8b26e0
008b2833  8a560b                   mov        dl, byte ptr [esi + 0xb]
008b2836  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008b2839  8810                     mov        byte ptr [eax], dl
008b283b  8a4e0a                   mov        cl, byte ptr [esi + 0xa]
008b283e  884801                   mov        byte ptr [eax + 1], cl
008b2841  8b5608                   mov        edx, dword ptr [esi + 8]
008b2844  c1ea08                   shr        edx, 8
008b2847  885002                   mov        byte ptr [eax + 2], dl
008b284a  8a4e08                   mov        cl, byte ptr [esi + 8]
008b284d  884803                   mov        byte ptr [eax + 3], cl
008b2850  8a560f                   mov        dl, byte ptr [esi + 0xf]
008b2853  885004                   mov        byte ptr [eax + 4], dl
008b2856  8a4e0e                   mov        cl, byte ptr [esi + 0xe]
008b2859  884805                   mov        byte ptr [eax + 5], cl
008b285c  8b560c                   mov        edx, dword ptr [esi + 0xc]
008b285f  c1ea08                   shr        edx, 8
008b2862  885006                   mov        byte ptr [eax + 6], dl
008b2865  8a4e0c                   mov        cl, byte ptr [esi + 0xc]
008b2868  884807                   mov        byte ptr [eax + 7], cl
008b286b  8a5613                   mov        dl, byte ptr [esi + 0x13]
008b286e  885008                   mov        byte ptr [eax + 8], dl
008b2871  8a4e12                   mov        cl, byte ptr [esi + 0x12]
008b2874  884809                   mov        byte ptr [eax + 9], cl
008b2877  8b5610                   mov        edx, dword ptr [esi + 0x10]
008b287a  c1ea08                   shr        edx, 8
008b287d  88500a                   mov        byte ptr [eax + 0xa], dl
008b2880  8a4e10                   mov        cl, byte ptr [esi + 0x10]
008b2883  88480b                   mov        byte ptr [eax + 0xb], cl
008b2886  8a5617                   mov        dl, byte ptr [esi + 0x17]
008b2889  88500c                   mov        byte ptr [eax + 0xc], dl
008b288c  8a4e16                   mov        cl, byte ptr [esi + 0x16]
008b288f  88480d                   mov        byte ptr [eax + 0xd], cl
008b2892  8b5614                   mov        edx, dword ptr [esi + 0x14]
008b2895  c1ea08                   shr        edx, 8
008b2898  88500e                   mov        byte ptr [eax + 0xe], dl
008b289b  8a4e14                   mov        cl, byte ptr [esi + 0x14]
008b289e  88480f                   mov        byte ptr [eax + 0xf], cl
008b28a1  8a561b                   mov        dl, byte ptr [esi + 0x1b]
008b28a4  885010                   mov        byte ptr [eax + 0x10], dl
008b28a7  8a4e1a                   mov        cl, byte ptr [esi + 0x1a]
008b28aa  884811                   mov        byte ptr [eax + 0x11], cl
008b28ad  8b5618                   mov        edx, dword ptr [esi + 0x18]
008b28b0  c1ea08                   shr        edx, 8
008b28b3  885012                   mov        byte ptr [eax + 0x12], dl
008b28b6  8a4e18                   mov        cl, byte ptr [esi + 0x18]
008b28b9  884813                   mov        byte ptr [eax + 0x13], cl
008b28bc  8a561f                   mov        dl, byte ptr [esi + 0x1f]
008b28bf  885014                   mov        byte ptr [eax + 0x14], dl
008b28c2  8a4e1e                   mov        cl, byte ptr [esi + 0x1e]
008b28c5  884815                   mov        byte ptr [eax + 0x15], cl
008b28c8  8b561c                   mov        edx, dword ptr [esi + 0x1c]
008b28cb  c1ea08                   shr        edx, 8
008b28ce  88                       .byte      0x88
008b28cf  50                       push       eax
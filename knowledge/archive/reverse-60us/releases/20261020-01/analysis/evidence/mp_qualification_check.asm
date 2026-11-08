; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 004d6417..004d6444 (end exclusive); file offset 000d6417
; This is an instruction excerpt, not a recovered original source file.
004d6417  6aff                     push       -1
004d6419  56                       push       esi
004d641a  8bcf                     mov        ecx, edi
004d641c  e8efa90700               call       0x550e10
004d6421  85c0                     test       eax, eax
004d6423  7e1f                     jle        0x4d6444
004d6425  8d8e38120000             lea        ecx, [esi + 0x1238]
004d642b  e830bcf2ff               call       0x402060
004d6430  6aff                     push       -1
004d6432  56                       push       esi
004d6433  8bcf                     mov        ecx, edi
004d6435  8bd8                     mov        ebx, eax
004d6437  e8d4a90700               call       0x550e10
004d643c  3bd8                     cmp        ebx, eax
004d643e  0f8c29010000             jl         0x4d656d

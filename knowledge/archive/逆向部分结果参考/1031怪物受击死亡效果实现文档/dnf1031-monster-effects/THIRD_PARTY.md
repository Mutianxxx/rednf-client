# Third-party components and local sources

| Component | Version / origin | Notice |
| --- | --- | --- |
| SDL2 | 2.32.10; vendored `vendor/SDL2`, `vendor/libSDL2.dll.a`, and `vendor/runtime/SDL2.dll` | [SDL2](licenses/SDL2.txt) |
| zlib | 1.3.1; vendored `vendor/` headers and static library | [zlib](licenses/zlib.txt) |
| nlohmann/json | 3.12.0 | [MIT](licenses/json.txt) |
| stb_image_write | 1.16 | [stb](licenses/stb.txt) |
| LLVM-MinGW / libc++ / libunwind | llvm-mingw-20261006-ucrt-x86_64 | [LLVM](licenses/LLVM.txt), [MinGW](licenses/MinGW-runtime.txt) |

Resource-decoder source files were copied from the 1031 handoff's snapshot of
`attack_demo/src/resources.cpp` and `attack_demo/include/dnf/`, then modified
independently in this directory. The game PVF/NPK data is read from the user's
local 1031 client; game assets are not covered by the software licenses above.

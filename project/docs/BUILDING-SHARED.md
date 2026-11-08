# 共享源码构建

本交付包是源码与设计资料，不含可玩 EXE、客户端资源或 PVF。构建需要 Windows 10/11、Python 3.11+、当前版本的 1031 客户端资源，以及依赖锁文件列出的 Windows UCRT LLVM-MinGW、CMake、Ninja。`third_party/` 内含 SDL2、patched Squirrel、zlib 和必要头文件/原生合同。

## 一次性本机配置

1. 安装/解压 CMake 4.4.x、Ninja 1.13.x 和 LLVM-MinGW UCRT 工具链；目录树应包含 `llvm-mingw-*-ucrt-x86_64/`、`cmake-*-windows-x86_64/bin/cmake.exe`、`ninja/ninja.exe`。
2. 在 `project/` 中复制 `toolchain.local.json.example` 为 `toolchain.local.json`，填入本机工具链根和只读 1031 客户端根。客户端根至少要有 `Script.pvf` 和对应 NPK/静态资源。
3. `content-profile.json` 是模板。将 `pvfPath` 与 `resourceRoots` 改成本机客户端位置。不要把本机绝对路径提交。
4. 确认 `project/build.cmd` 可使用 `py -3.11`、`python` 或 `PYTHON_EXE` 指向的 Python。

工具链下载 URL、锁定版本和压缩包哈希见 `project/third_party/dependencies.lock.json`。配置本机时保持资源只读。测试将文件、存档和报告写在 `project/cache/`、`project/saves/` 和 `project/reports/`。

## 命令

在 `project/` 下运行：

```bat
build.cmd --client "C:\DNF1031客户端" --build-dir cache\dev-build
```

运行完整自动套件：

```bat
build.cmd --test --client "C:\DNF1031客户端" --build-dir cache\dev-build --test-dir cache\dev-tests
```

或者使用 `Build-And-Test.cmd`。首次构建会编译 SDL 应用、技能预览工具和测试程序。`build.cmd` 默认只编译；`--test` 会运行分组隔离的自动检查。构建收据写入 build 目录的 `build-verification.json`。

前台启动：构建后运行 `Play.cmd`。使用私有 `project/saves/refactor/`，不会读取或覆盖原客户端/其它工程的角色存档。运行需要有效的 1031 `content-profile.json`。

## 故障定位

- 找不到 `Script.pvf`：检查 `--client` 与 `toolchain.local.json` 的 `client_root`。
- 找不到 clang/cmake/ninja：确认 `toolchain_root` 指向上述目录树根目录，而不是 `bin` 子目录。
- `dnf_native.exe` 找不到：先运行 `build.cmd`，或确认 `Play.cmd` 与 `cache/refactor-build/dnf_native.exe` 相对路径。
- SDL/字体/内容差异：查看 build/test 的 `reports` 与内容 profile；提交问题时不要附原始 PVF/NPK 或客户端文件。

工程只验证受支持范围；构建通过不代表所有技能、地图、AI、UI 或副本均已完成。


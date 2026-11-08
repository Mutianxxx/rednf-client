# 复现与验收

## 运行环境与依赖

运行：Windows x64、系统图形接口；使用 Windows 的 Microsoft YaHei 字体。SDL2及 libunwind DLL 已随包提供；没有游戏进程依赖。程序从 EXE 所在目录取资源，不依赖启动时工作目录。

数据工具：Python 3.10或更新版本，仅标准库，无 pip 依赖。`py -3` 不可用时换成自己的 `python.exe` 路径。全部命令在交付根目录执行，PowerShell示例：

```powershell
py -3 -X utf8 -B tools/verify_delivery.py --runtime
```

这会核对交付文件、原始PVF成员、NPK内原始IMG、代码区段、创建调用，并运行隐藏窗口验收。结果保存到 `demo/reports/delivery-verification.json` 与 `demo/reports/verification.json`。验收 PNG 为调试附件。

## 从原始成员重新生成内容

```powershell
py -3 -X utf8 -B demo/tools/prepare.py
```

首轮先从 `derivation/raw/members.bin` 重建 seed，验证与原 seed 的整体 SHA256 相同；随后按冻结目录和本轮技能证据执行 `prepare.py`。输出 `demo/content/` 和 `demo/reports/{content-provenance,capabilities}.json`。不访问原客户端、不访问工作区分析目录，也不启动采集。

原始成员中的字符串引用使用冻结映射；保留 record、源偏移、重复字段和未知节点。seed目录/外观是被冻结的关联结果，其规则参考源码在 `reference/catalog-rules`；本命令不宣称从“仅原始PVF”自动恢复所有目录映射或采集时序。seed的规范化二进制则确实逐字节再生成并校验。

再生成后运行 `py -3 -X utf8 -B tools/compare_content.py`，与交付前的当前实现作规范化JSON和二进制哈希对照。`py -3 -X utf8 -B tools/query.py --skill hopsmash` 可查看单技能实现索引；`--source skill/swordman/hopsmash.skl` 可直接读取归档原始成员的字段、token和偏移。

## 从源码构建

编译器使用 LLVM-MinGW 的 x86_64 UCRT C++17工具链。验证时使用 `llvm-mingw-20261006-ucrt-x86_64`；完整编译器未打包，版本信息在构建报告中。包内提供所有项目头文件、第三方头、静态/导入库与运行DLL。

```powershell
py -3 -X utf8 -B demo/tools/build.py --toolchain 'C:/tools/llvm-mingw/bin'
```

也可设置 `LLVM_MINGW_BIN` 或将 `x86_64-w64-mingw32-clang++.exe` 放到 PATH。`build.cmd` 将参数原样传入。编译器需要使用相容的64位MinGW目标；MSVC不能直接链接本包的 `.a`，需要重建对应第三方库。

构建输出 EXE、两个 `.o` 和新的 `demo/reports/build-manifest.json`。源码和行为应可复现；换编译器、路径或工具链时不承诺 PE 文件逐字节相同。

重建后用 `tools/verify_delivery.py --runtime --no-manifest` 验证证据、资源和运行；`--no-manifest`仅跳过原交付文件指纹，资源原始成员、证据和闭包检查仍执行。未修改的原交付包应使用默认完整manifest检查。

## 运行时复验

```powershell
& './demo/battle_demo.exe' --verify
$env:DNF_DEMO_ACCELERATED='1'
& './demo/battle_demo.exe' --verify
Remove-Item Env:DNF_DEMO_ACCELERATED
```

默认隐藏窗口使用软件渲染；设置变量后优先硬件接口。实际renderer名见报告；不支持时程序可能回退软件，不能把退出码替代renderer检查。

验收覆盖26项检查，八个核心技能的多个效果采样、五个职业分类样例、左右镜像源框扣血、连段、狂暴前置/关闭约束、崩山击落点、多实体隔离、去重、过期generation、受击和两类死亡。它不证明另外46个资源推导演示均等同原客户端。

交付时还在另外一个解压目录中执行数据再生成、内容对比、源码构建及运行验收；详见 `validation/isolated-rebuild.json` 和相关报告。包内所有运行资源读取均指向该解压目录。原客户端和原工作区未被作为迁移运行输入。

## 常见失败与定位

- 启动弹错：看 `demo/reports/startup-error.json`；若资源哈希不同，重新解压对应资源，或为自己的有证据变更更新资产清单。
- 缺少编译器：给 `--toolchain`；预编译程序不需要编译器。
- 原始缓存再生成不符：停止替换，检查 raw/index/seed 的哈希；不要靠改源偏移或忽略字段修复。
- 某技能效果不对：Space暂停，F5导出状态；按 `cast_id`、`path`、局部时间、锚点及具体实例核对，再和新采集比较。不要只对图片外观做补丁。

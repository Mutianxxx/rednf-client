# 源码导航

文件内检索以下符号即可定位。行号绑定本包源码；修改后应重新生成。

| 符号 | 文件与行号 |
| --- | --- |
| `struct Motion` | [demo/src/main.cpp:49](../demo/src/main.cpp#L49) |
| `struct Cast` | [demo/src/main.cpp:54](../demo/src/main.cpp#L54) |
| `struct Monster` | [demo/src/main.cpp:55](../demo/src/main.cpp#L55) |
| `struct Battle` | [demo/src/main.cpp:60](../demo/src/main.cpp#L60) |
| `void addAls` | [demo/src/main.cpp:83](../demo/src/main.cpp#L83) |
| `void startSpec` | [demo/src/main.cpp:90](../demo/src/main.cpp#L90) |
| `Json inferred` | [demo/src/main.cpp:107](../demo/src/main.cpp#L107) |
| `void selectedSkill` | [demo/src/main.cpp:113](../demo/src/main.cpp#L113) |
| `void attack` | [demo/src/main.cpp:114](../demo/src/main.cpp#L114) |
| `bool acceptedHit` | [demo/src/main.cpp:123](../demo/src/main.cpp#L123) |
| `void collision` | [demo/src/main.cpp:140](../demo/src/main.cpp#L140) |
| `void step` | [demo/src/main.cpp:144](../demo/src/main.cpp#L144) |
| `void body` | [demo/src/main.cpp:155](../demo/src/main.cpp#L155) |
| `void drawMonster` | [demo/src/main.cpp:164](../demo/src/main.cpp#L164) |
| `void drawPlayer` | [demo/src/main.cpp:176](../demo/src/main.cpp#L176) |
| `void draw()` | [demo/src/main.cpp:183](../demo/src/main.cpp#L183) |
| `void event` | [demo/src/main.cpp:217](../demo/src/main.cpp#L217) |
| `static int verify` | [demo/src/main.cpp:221](../demo/src/main.cpp#L221) |
| `static int run` | [demo/src/main.cpp:246](../demo/src/main.cpp#L246) |
| `Texture& texture` | [demo/src/canvas.hpp:25](../demo/src/canvas.hpp#L25) |
| `void sprite` | [demo/src/canvas.hpp:63](../demo/src/canvas.hpp#L63) |
| `void animation` | [demo/src/canvas.hpp:72](../demo/src/canvas.hpp#L72) |
| `Pvf::Pvf` | [demo/src/resources.cpp:109](../demo/src/resources.cpp#L109) |
| `Animation decodeAni` | [demo/src/resources.cpp:344](../demo/src/resources.cpp#L344) |
| `Assets::Assets` | [demo/src/resources.cpp:489](../demo/src/resources.cpp#L489) |
| `Assets::blob` | [demo/src/resources.cpp:540](../demo/src/resources.cpp#L540) |
| `Assets::pixels` | [demo/src/resources.cpp:574](../demo/src/resources.cpp#L574) |
| `struct DeathProfile` | [demo/include/dnf/shared_death.hpp:9](../demo/include/dnf/shared_death.hpp#L9) |
| `deathParticles` | [demo/include/dnf/shared_death.hpp:29](../demo/include/dnf/shared_death.hpp#L29) |
| `deathPosition` | [demo/include/dnf/shared_death.hpp:36](../demo/include/dnf/shared_death.hpp#L36) |
| `def tracks` | [demo/tools/prepare.py:78](../demo/tools/prepare.py#L78) |
| `def act_tracks` | [demo/tools/prepare.py:104](../demo/tools/prepare.py#L104) |
| `for key,hotkey` | [demo/tools/prepare.py:141](../demo/tools/prepare.py#L141) |
| `projection_only=True` | [demo/tools/prepare.py:225](../demo/tools/prepare.py#L225) |
| `def script` | [derivation/lib/prepare_content.py:15](../derivation/lib/prepare_content.py#L15) |
| `def animation` | [derivation/lib/prepare_content.py:36](../derivation/lib/prepare_content.py#L36) |

上游原版在 `reference/upstream`；唯一C++便携改动为 `run()` 的资源/身份入口，见 `reference/portable-startup.patch`。

资源准备改为包内原始成员与证据路径，构建改为包内SDK和外置可指定编译器；战斗、渲染和验收函数未修改。

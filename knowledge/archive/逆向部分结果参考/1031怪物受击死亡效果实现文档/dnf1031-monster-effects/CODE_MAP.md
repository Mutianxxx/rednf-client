# 源码调用入口定位

以下为本包源码的实际行号；源文件与行号均受 manifest 校验。完整控制流见主文档第4～9节。

| 入口 | 源码 | 行号 |
| --- | --- | ---: |
| `static double boundary(` | [source/src/main.cpp](source/src/main.cpp) | 47 |
| `struct Track` | [source/src/main.cpp](source/src/main.cpp) | 51 |
| `struct Plan` | [source/src/main.cpp](source/src/main.cpp) | 52 |
| `struct Content` | [source/src/main.cpp](source/src/main.cpp) | 54 |
| `void addTrack(` | [source/src/main.cpp](source/src/main.cpp) | 58 |
| `void select(int index)` | [source/src/main.cpp](source/src/main.cpp) | 86 |
| `Texture& sprite(` | [source/src/main.cpp](source/src/main.cpp) | 142 |
| `void plan(` | [source/src/main.cpp](source/src/main.cpp) | 183 |
| `std::array<double,4> bounds(` | [source/src/main.cpp](source/src/main.cpp) | 201 |
| `void effectSprite(` | [source/src/main.cpp](source/src/main.cpp) | 210 |
| `struct Demo` | [source/src/main.cpp](source/src/main.cpp) | 221 |
| `bool useShared(` | [source/src/main.cpp](source/src/main.cpp) | 235 |
| `void prepareShared(` | [source/src/main.cpp](source/src/main.cpp) | 237 |
| `void freeze(` | [source/src/main.cpp](source/src/main.cpp) | 258 |
| `void sharedDraw(` | [source/src/main.cpp](source/src/main.cpp) | 265 |
| `Plan* current(` | [source/src/main.cpp](source/src/main.cpp) | 280 |
| `void start(` | [source/src/main.cpp](source/src/main.cpp) | 281 |
| `void reset(` | [source/src/main.cpp](source/src/main.cpp) | 287 |
| `void step(` | [source/src/main.cpp](source/src/main.cpp) | 289 |
| `void frameStep(` | [source/src/main.cpp](source/src/main.cpp) | 295 |
| `void seek(` | [source/src/main.cpp](source/src/main.cpp) | 296 |
| `static fs::path findClient(` | [source/src/main.cpp](source/src/main.cpp) | 357 |
| `static void verify(` | [source/src/main.cpp](source/src/main.cpp) | 364 |
| `static int run(` | [source/src/main.cpp](source/src/main.cpp) | 416 |
| `std::string normalize(` | [source/src/resources.cpp](source/src/resources.cpp) | 11 |
| `Pvf::Pvf(` | [source/src/resources.cpp](source/src/resources.cpp) | 103 |
| `Bytes Pvf::read(` | [source/src/resources.cpp](source/src/resources.cpp) | 170 |
| `Script Pvf::script(` | [source/src/resources.cpp](source/src/resources.cpp) | 180 |
| `static Json property(` | [source/src/resources.cpp](source/src/resources.cpp) | 254 |
| `Animation decodeAni(` | [source/src/resources.cpp](source/src/resources.cpp) | 322 |
| `size_t Animation::frameAt(` | [source/src/resources.cpp](source/src/resources.cpp) | 376 |
| `AniPose Animation::samplePose(` | [source/src/resources.cpp](source/src/resources.cpp) | 390 |
| `Assets::Assets(` | [source/src/resources.cpp](source/src/resources.cpp) | 453 |
| `Bytes Assets::blob(` | [source/src/resources.cpp](source/src/resources.cpp) | 504 |
| `std::shared_ptr<Animation> Assets::animation(` | [source/src/resources.cpp](source/src/resources.cpp) | 526 |
| `Pixels Assets::pixels(` | [source/src/resources.cpp](source/src/resources.cpp) | 535 |
| `Pixels decodeImg(` | [source/src/resources.cpp](source/src/resources.cpp) | 547 |
| `struct DeathProfile` | [source/include/dnf/shared_death.hpp](source/include/dnf/shared_death.hpp) | 9 |
| `inline uint32_t deathSeed(` | [source/include/dnf/shared_death.hpp](source/include/dnf/shared_death.hpp) | 28 |
| `inline std::vector<DeathParticle> deathParticles(` | [source/include/dnf/shared_death.hpp](source/include/dnf/shared_death.hpp) | 29 |
| `inline ParticlePosition deathPosition(` | [source/include/dnf/shared_death.hpp](source/include/dnf/shared_death.hpp) | 36 |
| `inline std::array<Point2, 4> imageQuad(` | [source/include/dnf/geometry.hpp](source/include/dnf/geometry.hpp) | 15 |

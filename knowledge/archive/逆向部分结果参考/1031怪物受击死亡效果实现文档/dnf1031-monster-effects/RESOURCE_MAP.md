# 完整资源索引与代表怪物调用实例

所有逻辑路径相对于原始1031的PVF或NPK成员，路径不是包内散图文件。哈希对应解密去填充的PVF成员或原始NPK成员。完整字段与帧号保存在链接的JSON中；用主文档的`query_effects.py --extract`命令可导出目标怪物资源。

## 1. 通用死亡23个ANI/PTL

[原字段、帧与SHA256全集](evidence/common-death-resources.json)。这些是资源普查，Young/Teen/血液等变体并未全部执行；当前播放器只消费主文档明确列出的标准piece/flash/smoke路径。

| PVF路径 | 字节数 | ANI帧数/时长或PTL | SHA256 |
| --- | ---: | --- | --- |
| `monster/common/animation/monsterdieblood.ani` | 161 | 3帧 / 3750ms | `a277fdae34c5492da8c9faaf29dfb0b2dd3a56aeecd7fa656668e62dcb772d57` |
| `monster/common/animation/monsterdiebloodyoung.ani` | 161 | 3帧 / 3750ms | `2f603a705b47a85d462f5ac9a71169419c3039706acecd998df4178533893095` |
| `monster/common/animation/monsterdieflash.ani` | 131 | 2帧 / 200ms | `9ef66c5d7edafd1006665ff3e32c36e1064a3d2700b6ba637cf085bde709d507` |
| `monster/common/animation/monsterdieflashyoung.ani` | 176 | 3帧 / 1000ms | `43c2d467d013b1e576f9cdecf2ee141137cb3f40f374a163b39fff0c71743f0e` |
| `monster/common/animation/monsterdiepiece.ani` | 110 | 4帧 / 2250ms | `dd9c5ca4692894202eeacd7ad18d57f58ddbc350be9971d1b0d96427c7188e32` |
| `monster/common/animation/monsterdiepieceveryyoung.ani` | 94 | 1帧 / 500ms | `d506b7344d19c09798058c5badb59c4ea31a2d1df1886d3ac393512f3ef44954` |
| `monster/common/animation/monsterdiepieceyoung.ani` | 128 | 4帧 / 2250ms | `cacd1776dc79f0799f35b7ff31a95a50c69566db3b42c4ede39048caf24e32fe` |
| `monster/common/animation/monsterdiesmoke.ani` | 161 | 3帧 / 2150ms | `30ea175daa545f88d2b82af8d0c4b9e551dd5d2a1e2770a6c5246eb918dfda10` |
| `monster/common/animation/teen_monster_die_light_1.ani` | 113 | 2帧 / 350ms | `0bf7b9d045ed26d67c7ddb74fa45fe07fcc30516123e66c5d0eb753f35dbb277` |
| `monster/common/animation/teen_monster_die_light_2.ani` | 91 | 1帧 / 250ms | `4f0f5bda681c71c68f00e8a631d19c409fa03a1543ccd94c06f6535ab9403937` |
| `monster/common/animation/teen_monster_die_particle_1.ani` | 132 | 2帧 / 1000ms | `e1313464a976d11039e8420b6b72fd29387fde0259b9531f4f7e5da2a808fe4f` |
| `monster/common/animation/teen_monster_die_particle_2.ani` | 132 | 2帧 / 1000ms | `ce99be590806383b69ffe50b0f7b763a5cb05cd22261df86e193dcbf9179beae` |
| `monster/common/particle/monsterdieblood.ptl` | 197 | PTL：原始fields/tokens见JSON | `db98049663f18cb3abd6c2b7b6a17827b3e223813ca2cbcfd73502be1f4c92f5` |
| `monster/common/particle/monsterdiebloodyoung.ptl` | 197 | PTL：原始fields/tokens见JSON | `4f1cd5a8ba971c30511ee0200a8a896024b095f2fbbcaec8b44b6ff5611091a0` |
| `monster/common/particle/monsterdieflashyoung.ptl` | 177 | PTL：原始fields/tokens见JSON | `33c3836ac8ec80447447b65c214a765d907462091c28985b230aa076bd23044a` |
| `monster/common/particle/monsterdiepiece.ptl` | 187 | PTL：原始fields/tokens见JSON | `c95a94b1e08bd85dea8b43d8400ff7273d5778515febcdb52742cdc513f85722` |
| `monster/common/particle/monsterdiepieceveryyoung.ptl` | 252 | PTL：原始fields/tokens见JSON | `0cf88f07ba704a67cf5c1a432fbafd5c141c43e94ed005e3fd94916b75dfc27f` |
| `monster/common/particle/monsterdiepieceyoung.ptl` | 187 | PTL：原始fields/tokens见JSON | `6c240422600f33134bbaf74c92852e6d3eb86f23eab4978dd96bc50c112fcd8b` |
| `monster/common/particle/monsterdiesmoke.ptl` | 157 | PTL：原始fields/tokens见JSON | `4116558b2598169ecb8c58afd1ce8f3cdc2a621767b130120d87372df919145e` |
| `monster/common/particle/teen_monster_die_down_01.ptl` | 242 | PTL：原始fields/tokens见JSON | `068b66ec0bc0ceb6b1d27f084e8d5ed7af44d144ced92115d68504bfa2401b34` |
| `monster/common/particle/teen_monster_die_down_02.ptl` | 252 | PTL：原始fields/tokens见JSON | `f2936c92cf6a0715ec0af28ed94d1985405cddfe4a10f43c4c987823209e1256` |
| `monster/common/particle/teen_monster_die_stand_01.ptl` | 272 | PTL：原始fields/tokens见JSON | `caf4fc379b5fca7b2bb20f7e2b8a7d6d84232485f41c4ba754ad39ea2eb91e80` |
| `monster/common/particle/teen_monster_die_stand_02.ptl` | 282 | PTL：原始fields/tokens见JSON | `64049f03eed38c3c1afe36f0631adfbe0c6cdc3f4cd0fceaf84cb5e8ae7c5d8c` |

## 2. 通用NPK图片/声音与29套石块

[精确NPK包、成员偏移、长度、全部所需帧头和成员SHA256](examples/common-images.json)。查询索引包括23个共用资源的静态IMG/音频引用及m0001～m0029；不能把未执行分支当作实际播放。下表全部来自原始1031索引。

| NPK成员 | NPK文件 | 成员偏移 / 长度 | 图片帧数 | SHA256 |
| --- | --- | --- | ---: | --- |
| `sprite/common/commoneffect/teen_monster_die_light.img` | `ImagePacks2/sprite_common_commoneffect.NPK` | 7132701 / 266 | 2 | `c540a6fe928c409efecd26af4e59770a651f8b8c735d33f47d1c81b12f9ad017` |
| `sprite/common/commoneffect/teen_monster_die_particle.img` | `ImagePacks2/sprite_common_commoneffect.NPK` | 7132967 / 2365 | 2 | `dafc5c48f35851f2baf4805a28d6c3d3a908114d000f5f99ed14341c67506a1c` |
| `sprite/monster/common/m0001.img` | `ImagePacks2/sprite_monster_common.NPK` | 1209357 / 882 | 4 | `6636a88bd369088fe2d874f83eaf8dc095353ef5cd8bb3f5e48b184b3c334f75` |
| `sprite/monster/common/m0002.img` | `ImagePacks2/sprite_monster_common.NPK` | 1210239 / 890 | 4 | `20963f7a474eea8688b53bd985e5ef5d87180dbebd5ef80a15ff0fba6feddcf2` |
| `sprite/monster/common/m0003.img` | `ImagePacks2/sprite_monster_common.NPK` | 1211129 / 893 | 4 | `f0081a2a8bf4e6731ad78ae31ed6fbd6f0b28ba6583c543b69aabe4ee75e3ab9` |
| `sprite/monster/common/m0004.img` | `ImagePacks2/sprite_monster_common.NPK` | 1212022 / 883 | 4 | `cccf3fdf4e75224a987116ab945cc89f15d049bb26b64932c97f4034b4e487e9` |
| `sprite/monster/common/m0005.img` | `ImagePacks2/sprite_monster_common.NPK` | 1212905 / 875 | 4 | `c7dfb6f055b31071cc021425cfafe5caa1f57483d23c6039555ac6cb9ea62755` |
| `sprite/monster/common/m0006.img` | `ImagePacks2/sprite_monster_common.NPK` | 1213780 / 889 | 4 | `647dcb52109d5265c4697083da3cc70dca51c7dd82a5ca18cb23babeb6340a99` |
| `sprite/monster/common/m0007.img` | `ImagePacks2/sprite_monster_common.NPK` | 1214669 / 863 | 4 | `3e94c35356b33e9f16f4403846729028793502ed5d2571aac6218c72196a4f5d` |
| `sprite/monster/common/m0008.img` | `ImagePacks2/sprite_monster_common.NPK` | 1215532 / 885 | 4 | `33e0fbd3630ae955f4d1a6000a42038cb5d31a86bbe27bb6ecee6419389d97b5` |
| `sprite/monster/common/m0009.img` | `ImagePacks2/sprite_monster_common.NPK` | 1216417 / 891 | 4 | `ac67fecb64d4e8a39c26d5173441dbe1b005c09e2939c5b6e73c8249a40df2ef` |
| `sprite/monster/common/m0010.img` | `ImagePacks2/sprite_monster_common.NPK` | 1217308 / 832 | 4 | `350409af86162420bd33c81db17d9959cd775ec95579a2a0585d22af5a7f2ef7` |
| `sprite/monster/common/m0011.img` | `ImagePacks2/sprite_monster_common.NPK` | 1218140 / 894 | 4 | `5cb91a569d0ee24f3b1fce40504e784fd5fc682aa34fa96d86de1116017b5b7c` |
| `sprite/monster/common/m0012.img` | `ImagePacks2/sprite_monster_common.NPK` | 1219034 / 887 | 4 | `ccf891078aeb970f8ae09147dba0a53ef4b84469fad525d7d484b85c5a515298` |
| `sprite/monster/common/m0013.img` | `ImagePacks2/sprite_monster_common.NPK` | 1219921 / 887 | 4 | `4b65f79ee03849d09c37782d8921356b95ab474131f04d15d07ba2a267136738` |
| `sprite/monster/common/m0014.img` | `ImagePacks2/sprite_monster_common.NPK` | 1220808 / 887 | 4 | `07459b5f27ddc4741f47811e2b95d4cb8762efd07655b2ed868853b1fe5d62d3` |
| `sprite/monster/common/m0015.img` | `ImagePacks2/sprite_monster_common.NPK` | 1221695 / 888 | 4 | `a00d79b51a71dd3ad627a2f321a923a3c809a4d9c2a46ddabfee94cc25583a1e` |
| `sprite/monster/common/m0016.img` | `ImagePacks2/sprite_monster_common.NPK` | 1222583 / 893 | 4 | `7416da889e336fc9f2f637d6bf7a6e8bd67233e0be444186df92d3dce85ef9fe` |
| `sprite/monster/common/m0017.img` | `ImagePacks2/sprite_monster_common.NPK` | 1223476 / 878 | 4 | `965ba547eab49b62eee99fd12a49ac8f2c6f9326d561e2bc2cadc60b6c9da91f` |
| `sprite/monster/common/m0018.img` | `ImagePacks2/sprite_monster_common.NPK` | 1224354 / 888 | 4 | `141db0f6185bcf096a09ff669327842683ba905b4095dac072073ce08a92c2b2` |
| `sprite/monster/common/m0019.img` | `ImagePacks2/sprite_monster_common.NPK` | 1225242 / 883 | 4 | `fa5e0123ef7da7f5be7970b4ac925382808e2f0728e559718ca918ae2257b389` |
| `sprite/monster/common/m0020.img` | `ImagePacks2/sprite_monster_common.NPK` | 1226125 / 878 | 4 | `56d31e27e7b93d8e7f2787d200077d1d653e2f5948c568c3077bd0d6a98b21c6` |
| `sprite/monster/common/m0021.img` | `ImagePacks2/sprite_monster_common.NPK` | 1227003 / 887 | 4 | `c65940d50a5b1e22a2fe0fe4d82bd94547ae7258c95a1d28aac1ced936fb5811` |
| `sprite/monster/common/m0022.img` | `ImagePacks2/sprite_monster_common.NPK` | 1227890 / 892 | 4 | `525c91923441dc721398ddbbeeeb6c529b60a39197c3402f5cbfd14384d1da4a` |
| `sprite/monster/common/m0023.img` | `ImagePacks2/sprite_monster_common.NPK` | 1228782 / 869 | 4 | `8afa5f7770caffc56f65f619339a763c5acaba0b288ce1b4f84bd9696349be5d` |
| `sprite/monster/common/m0024.img` | `ImagePacks2/sprite_monster_common.NPK` | 1229651 / 887 | 4 | `4daefbc205820eb3c32cc2f7584b1b11d8c84a2aba36d95ea8c9f53043499c52` |
| `sprite/monster/common/m0025.img` | `ImagePacks2/sprite_monster_common.NPK` | 1230538 / 895 | 4 | `6f67b0d2ed1903a8c81d12bbb0abcc7e25bf588dc25475f05f2ac4254bc0ae96` |
| `sprite/monster/common/m0026.img` | `ImagePacks2/sprite_monster_common.NPK` | 1231433 / 883 | 4 | `fe2a16256f85961f88e2163e0d54032e05b1d057c4153bd72972bd710bf49f79` |
| `sprite/monster/common/m0027.img` | `ImagePacks2/sprite_monster_common.NPK` | 1232316 / 885 | 4 | `bc6c175fff103ea6c42f33229b909dcaedaabb68e6037d18d08c54c1f769dcda` |
| `sprite/monster/common/m0028.img` | `ImagePacks2/sprite_monster_common.NPK` | 1233201 / 634 | 4 | `a69c451bfd9f1d917b1b64ef180301cb897f096ba2c98fd9ee57cf28922746a0` |
| `sprite/monster/common/m0029.img` | `ImagePacks2/sprite_monster_common.NPK` | 1233835 / 609 | 4 | `bf524fa399a180f5a7e93ba180c7e0bc35521e8c06a81ee191a13762480ab2e6` |
| `sprite/monster/common/monsterdieblood.img` | `ImagePacks2/sprite_monster_common.NPK` | 1234444 / 1894 | 1 | `355bb5c1677298a0fa3bcfe08cf48a1c5bf0798611994af971726a846d75a868` |
| `sprite/monster/common/monsterdieflash.img` | `ImagePacks2/sprite_monster_common.NPK` | 1236338 / 10230 | 1 | `13d6226a26ee56fe2cbbbe708f9b288c458bb18b43dd9981831a531a37a13bc3` |
| `sprite/monster/common/monsterdiepieceveryyoung.img` | `ImagePacks2/sprite_monster_common.NPK` | 1246568 / 2365 | 2 | `dafc5c48f35851f2baf4805a28d6c3d3a908114d000f5f99ed14341c67506a1c` |
| `sprite/monster/common/monsterdiesmoke.img` | `ImagePacks2/sprite_monster_common.NPK` | 1248933 / 406 | 2 | `50b9300b24d04bdcbb09f98f912e8d3c04ac17125d8eb88330a3acf50268bc5f` |
| `sprite/monster/common/monsterdieyoung.img` | `ImagePacks2/sprite_monster_common.NPK` | 1249339 / 1978 | 4 | `ed429cb81f4edf9d9ae53787319d15e90bad3776e20c93266c0e3c204da91527` |

石块每套4帧，具体每帧crop坐标/尺寸见上面的JSON。alpha必须由像素解码后检查；索引尺寸本身不能证明图像可见。[资源图集](images/death-resources.jpg)和[已解码尺寸记录](evidence/death-img-index.json)可辅助目视。尺寸记录的`file`是原诊断散图文件名，包内集中附图集，不要求这些旧文件名存在。

## 3. 六个代表怪物的实际绑定

完整graph包含MOB原字段、ACT原字段、ANI全部帧/属性、ALS、IMG帧索引、NPK精确定位和SHA256。关系标注区分已编译视觉轨道和未执行脚本引用。运行时观察列来自已验收结果；没有运行记录的行显示资源时长/编译轨道数。开始帧均为父基础ANI帧号。

### 5001 猫妖

MOB：`monster/lugaru/lugaru.mob`；SHA256 `5007fd5e5f47321848f32cc2b86e64314acdccb4c1a5b3c12105698197f4a003`；die effect：`[[0, 9, 0]]`。

[完整资源图](examples/5001/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting motion]` / 647 | `monster/lugaru/animation_lugaru/stay_2.ani` | 4帧 / 500ms | 500ms / 1 |
| damage1 | `[damage motion 1]` / 677 | `monster/lugaru/animation_lugaru/damage1.ani` | 1帧 / 10000ms | 10000ms / 1 |
| damage2 | `[damage motion 2]` / 687 | `monster/lugaru/animation_lugaru/damage2.ani` | 1帧 / 10000ms | 10000ms / 1 |
| down | `[down motion]` / 697 | `monster/lugaru/animation_lugaru/down.ani` | 5帧 / 20660ms | 20660ms / 1 |
| death | 无明确字段 | — | — | 依策略诊断/共享路由 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/lugaru/animation_lugaru/stay_2.ani` | 0 / 0 / 0,0 | `Monster/Lugaru/Lugaru.img` |
| damage1/base | `monster/lugaru/animation_lugaru/damage1.ani` | 0 / 0 / 0,0 | `Monster/Lugaru/Lugaru.img` |
| damage2/base | `monster/lugaru/animation_lugaru/damage2.ani` | 0 / 0 / 0,0 | `Monster/Lugaru/Lugaru.img` |
| down/base | `monster/lugaru/animation_lugaru/down.ani` | 0 / 0 / 0,0 | `Monster/Lugaru/Lugaru.img` |

### 1 哥布林

MOB：`monster/goblin/goblin.mob`；SHA256 `f049b8dc65fd3c596af18c3ed47995efb76c1cf48cb605869222b70e680cf421`；die effect：`[[0, 1, 0]]`。

[完整资源图](examples/1/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting motion]` / 502 | `monster/goblin/animation_goblin2/stay.ani` | 1帧 / 80ms | 资源80ms / 编译1 |
| damage1 | `[damage motion 1]` / 532 | `monster/goblin/animation_goblin2/damage1.ani` | 1帧 / 10000ms | 资源10000ms / 编译1 |
| damage2 | `[damage motion 2]` / 542 | `monster/goblin/animation_goblin2/damage2.ani` | 1帧 / 10000ms | 资源10000ms / 编译1 |
| down | `[down motion]` / 552 | `monster/goblin/animation_goblin2/down.ani` | 5帧 / 20660ms | 资源20660ms / 编译1 |
| death | 无明确字段 | — | — | 依策略诊断/共享路由 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/goblin/animation_goblin2/stay.ani` | 0 / 0 / 0,0 | `Monster/Goblin/Event/Goblin.img` |
| damage1/base | `monster/goblin/animation_goblin2/damage1.ani` | 0 / 0 / 0,0 | `Monster/Goblin/Event/Goblin.img` |
| damage2/base | `monster/goblin/animation_goblin2/damage2.ani` | 0 / 0 / 0,0 | `Monster/Goblin/Event/Goblin.img` |
| down/base | `monster/goblin/animation_goblin2/down.ani` | 0 / 0 / 0,0 | `Monster/Goblin/Event/Goblin.img` |

### 61491 巨灵布鲁

MOB：`monster/act8/ghost_flu/ghost_flu.mob`；SHA256 `c05e30968628deb28850d90a2e2ba42d32d039a4d60aabb9fb8f4c88f3c7245a`；die effect：`[[0, 24, 1]]`。

[完整资源图](examples/61491/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting action]` / 567 | `monster/act8/ghost_flu/action/stay.act` | 4帧 / 940ms | 940ms / 1 |
| damage1 | `[damage action 1]` / 587 | `monster/act8/ghost_flu/action/damage1.act` | 1帧 / 150ms | 150ms / 1 |
| damage2 | `[damage action 2]` / 597 | `monster/act8/ghost_flu/action/damage1.act` | 1帧 / 150ms | 150ms / 1 |
| down | 无明确字段 | — | — | 依策略诊断/共享路由 |
| death | `[last action]` / 677 | `monster/act8/ghost_flu/action/die.act` | 8帧 / 1600ms | 1600ms / 1 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/act8/ghost_flu/animation/stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/Bigghost_flu/flu_body.img` |
| damage1/base | `monster/act8/ghost_flu/animation/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Bigghost_flu/flu_body.img` |
| damage2/base | `monster/act8/ghost_flu/animation/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Bigghost_flu/flu_body.img` |
| death/base | `monster/act8/ghost_flu/animation/die.ani` | 0 / 0 / 0,0 | `Monster/Act8/Bigghost_flu/flu_body.img` |

### 56013 首领萨斯

MOB：`monster/act8/chiefsars/chiefsars.mob`；SHA256 `c2f1a21a713750c52473d0be9e67ffbd30819d156ba51d7f27a5cd1e5e448774`；die effect：`[[0, 3, 0]]`。

[完整资源图](examples/56013/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting action]` / 547 | `monster/act8/chiefsars/action/stay.act` | 1帧 / 80ms | 80ms / 3 |
| damage1 | `[damage action 1]` / 577 | `monster/act8/chiefsars/action/damage1.act` | 2帧 / 200ms | 200ms / 3 |
| damage2 | `[damage action 2]` / 587 | `monster/act8/chiefsars/action/damage2.act` | 2帧 / 200ms | 200ms / 3 |
| down | `[down action]` / 597 | `monster/act8/chiefsars/action/down.act` | 5帧 / 400ms | 400ms / 3 |
| death | `[last action]` / 667 | `monster/act8/chiefsars/action/die.act` | 2帧 / 3700ms | 3700ms / 4 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/act8/chiefsars/animation/stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_body.img` |
| idle/sub | `monster/act8/chiefsars/animation/foot/stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_foot.img` |
| idle/sub | `monster/act8/chiefsars/animation/hand/stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_hand.img` |
| damage1/base | `monster/act8/chiefsars/animation/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_body.img` |
| damage1/sub | `monster/act8/chiefsars/animation/foot/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_foot.img` |
| damage1/sub | `monster/act8/chiefsars/animation/hand/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_hand.img` |
| damage2/base | `monster/act8/chiefsars/animation/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_body.img` |
| damage2/sub | `monster/act8/chiefsars/animation/foot/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_foot.img` |
| damage2/sub | `monster/act8/chiefsars/animation/hand/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_hand.img` |
| down/base | `monster/act8/chiefsars/animation/down.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_body.img` |
| down/sub | `monster/act8/chiefsars/animation/foot/down.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_foot.img` |
| down/sub | `monster/act8/chiefsars/animation/hand/down.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_hand.img` |
| death/base | `monster/act8/chiefsars/animation/die.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Chief_body.img`<br>`monster/act8/chiefsars/chief_body.img` |
| death/sub | `monster/act8/chiefsars/animation/ef/boom1.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Die/Boom_start_dodge.img` |
| death/sub | `monster/act8/chiefsars/animation/ef/boom2.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Die/boom_dodge.img` |
| death/sub | `monster/act8/chiefsars/animation/ef/boomeye.ani` | 0 / 0 / 0,0 | `Monster/Act8/chiefsars/Die/Chief_eye_dodge.img` |

### 59005 杰诺

MOB：`monster/act8/wooden_doll/wooden_doll.mob`；SHA256 `4f2ee454b89d6eaac39edcac2cbe81b98b2ac13969b1bd57532c1ff156fcf8e8`；die effect：`[[0, 3, 1]]`。

[完整资源图](examples/59005/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting action]` / 522 | `monster/act8/wooden_doll/action/wait_stay.act` | 1帧 / 1000ms | 1000ms / 2 |
| damage1 | `[damage action 1]` / 552 | `monster/act8/wooden_doll/action/damage1.act` | 1帧 / 400ms | 400ms / 4 |
| damage2 | `[damage action 2]` / 562 | `monster/act8/wooden_doll/action/damage2.act` | 1帧 / 400ms | 400ms / 4 |
| down | `[down action]` / 572 | `monster/act8/wooden_doll/action/down.act` | 5帧 / 1260ms | 1260ms / 4 |
| death | `[last action]` / 682 | `monster/act8/wooden_doll/action/die.act` | 11帧 / 30910ms | 30910ms / 5 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/act8/wooden_doll/animation/wait_stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_body.img` |
| idle/sub | `monster/act8/wooden_doll/animation/weapon/wait_stay.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_sword.img` |
| damage1/base | `monster/act8/wooden_doll/animation/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_body.img` |
| damage1/sub | `monster/act8/wooden_doll/animation/weapon/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_sword.img` |
| damage1/sub | `monster/act8/wooden_doll/animation/ball/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_ball.img` |
| damage1/sub | `monster/act8/wooden_doll/animation/ball_eff/damage1.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_balleff.img` |
| damage2/base | `monster/act8/wooden_doll/animation/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_body.img` |
| damage2/sub | `monster/act8/wooden_doll/animation/weapon/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_sword.img` |
| damage2/sub | `monster/act8/wooden_doll/animation/ball/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_ball.img` |
| damage2/sub | `monster/act8/wooden_doll/animation/ball_eff/damage2.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_balleff.img` |
| down/base | `monster/act8/wooden_doll/animation/down.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_body.img` |
| down/sub | `monster/act8/wooden_doll/animation/ball/down.ani` | 0 / 1 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_ball.img` |
| down/sub | `monster/act8/wooden_doll/animation/ball_eff/down.ani` | 0 / 2 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_balleff.img` |
| down/sub | `monster/act8/wooden_doll/animation/weapon/down.ani` | 0 / 3 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_sword.img` |
| death/base | `monster/act8/wooden_doll/animation/die.ani` | 0 / 0 / 0,0 | `monster/act8/wooden_doll/wooden_doll_body.img` |
| death/sub | `monster/act8/wooden_doll/animation/ball/die.ani` | 0 / 0 / 0,0 | `monster/act8/wooden_doll/wooden_doll_ball.img` |
| death/sub | `monster/act8/wooden_doll/animation/ball_eff/die.ani` | 0 / 0 / 0,0 | `monster/act8/wooden_doll/wooden_doll_balleff.img` |
| death/sub | `monster/act8/wooden_doll/animation/ball_eff/die.ani` | 0 / 0 / 0,0 | `monster/act8/wooden_doll/wooden_doll_balleff.img` |
| death/sub | `monster/act8/wooden_doll/animation/weapon/die.ani` | 0 / 0 / 0,0 | `Monster/Act8/Wooden_doll/Wooden_doll_sword.img` |

### 62638 伪装树魔

MOB：`monster/event/bluemarble/dendroid_disguise/dendroid_disguise.mob`；SHA256 `4e5b3ad3181811530cf972d7f379e671cfab601ae243b11f7d8f27ae294ec78c`；die effect：`[[0, 10, 0]]`。

[完整资源图](examples/62638/graph.json)

| 状态 | MOB标签 / 字节偏移 | 入口 | 基础ANI帧数/时长 | 计划时长 / 轨道数 |
| --- | --- | --- | --- | --- |
| idle | `[waiting action]` / 552 | `monster/event/bluemarble/dendroid_disguise/action/stay.act` | 1帧 / 100ms | 100ms / 1 |
| damage1 | `[damage action 1]` / 572 | `monster/event/bluemarble/dendroid_disguise/action/damage1.act` | 1帧 / 200ms | 200ms / 1 |
| damage2 | `[damage action 2]` / 582 | `monster/event/bluemarble/dendroid_disguise/action/damage2.act` | 1帧 / 200ms | 200ms / 1 |
| down | 无明确字段 | — | — | 依策略诊断/共享路由 |
| death | `[last action]` / 602 | `monster/event/bluemarble/dendroid_disguise/action/die.act` | 2帧 / 370ms | 370ms / 1 |

| 状态/角色 | ANI路径 | 父起始帧 / layer / x,y | 图片名（IMG帧逐项见graph） |
| --- | --- | --- | --- |
| idle/base | `monster/event/bluemarble/dendroid_disguise/animation/stay.ani` | 0 / 0 / 0,0 | `Monster/GBL_breeding/Goliden_hide.img` |
| damage1/base | `monster/event/bluemarble/dendroid_disguise/animation/normaldamage1.ani` | 0 / 0 / 0,0 | `Monster/GBL_breeding/Goliden_hide.img` |
| damage2/base | `monster/event/bluemarble/dendroid_disguise/animation/normaldamage2.ani` | 0 / 0 / 0,0 | `Monster/GBL_breeding/Goliden_hide.img` |
| death/base | `monster/event/bluemarble/dendroid_disguise/animation/die.ani` | 0 / 0 / 0,0 | `Monster/GBL_breeding/Goliden_hide.img` |

## 4. 源数据占位与未执行行为

拉宾特的灵魂59001的明确last action引用24帧/1440ms的ANI，其中IMG索引17～20指向实际1×1透明占位；本包的运行验证记录保留该状态不可见诊断。不能因为有die文件名就视作完整死亡动画，也不能静默换成普通石块。[完整运行诊断](evidence/runtime/verification.json)。

杰诺59005的last action具有11个基础帧、4个子ANI，计划30910ms；其ACT还包含被动对象创建，参考播放器不执行该行为。首领萨斯的受击包含身体/脚/手三个轨道，独立死亡包含基础与三段爆炸子层。它们用于检验多层和长时间轴，不能把一张独立IMG当作怪物模型全部内容。

新增怪物时不需要新增ID分支：查询对应目录行、使用同一Plan/ALS编译器、按原配置选择共享资源并检查诊断即可。特殊行为仍按原ACT/脚本交给对应执行器。

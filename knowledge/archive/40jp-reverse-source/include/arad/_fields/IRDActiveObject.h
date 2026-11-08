// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: IRDActiveObject    主虚表槽位数: 255   字段数: 59
// 继承链: KMessenger -> KGameMessenger -> CNRDObject -> IRDCollisionObject -> IRDActiveObject（本表）
//          -> IRDMonster -> ~94 怪物子类（★ 继承链核心：其余类都继承它）
// 权威来源: src/cnrd/IRDActiveObject.h / IRDCollisionObject.h / CNRDObject.h
//          （会话 3 逐行精修的原始 struct —— 本表字段语义直接照抄，偏移/类型不可改）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ src/cnrd 逐行精修 + 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类 255 槽函数与 src/cnrd/*.cpp）；
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 field_XXXX 占位）
// 证据主源（本类虚表槽函数 / src/cnrd）:
//   0x4D6970 sub_4D6970 出生/复活初始化（src/game/combat_core.cpp:4666）
//   0x4D5A90 vmt3E0 影身/伪装计时三连写（src/game/combat_core.cpp:3900）
//   0x4D71B0 vmt200 ★★ 命中主处理器（42 轮研究 §2 全文定案；szCueName1692）
//   0x4D4D40 vmt2D8 ★★ HP setter（研究 [13] 锚点）
//   0x4D5140 vmt308 17 状态查询 / 0x4D5170 vmt2D0 霸体 setter / 0x4A1010 vmt348 大状态
//   0x4E5C10 vmt268 帧时刻覆盖 / 0x42A8D0 CNRDObject_vmt11C 参数四元组
//   0x499020 vmt104 动画时刻同步 / 0x499080 vmt110 浮点版
// 三层状态架构: 主状态镜像(+6556) / 受击反应态(+616+636 优先级) / 大状态(+7148) —— 见 docs/14
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct IRDActiveObject_Fields {
    // ---- 区块 1：继承 CNRDObject/IRDCollisionObject 基类区（通用偏移表；动画对象/参数灌入/帧覆盖/阵营与受击态） ----
    unsigned char _base_0x0000        [112]; // +0x0000..0x006F 继承 KGameMessenger/CNRDObject/IRDCollisionObject/IRDActiveObject 前 0x70 字节（见 src/cnrd/*.h；不重复展开）
    unsigned int      pHostComp112        ; // +0x0070 (112) x1  宿主对象指针（0x4D6970 尾调 sub_49FD20(this+112)；CNRDObject vmt3C 兜底取 +112）（证据 va=004D6970）
    unsigned char _unused_0x0074      [4]; // +0x0074..0x0077 未观测
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  基类动画对象指针（0x499020/0x499080 帧时刻同步宿主；全库通用 this+120）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x007C      [38]; // +0x007C..0x00A1 未观测
    unsigned char     bFlag162            ; // +0x00A2 (162) x2  标志位组（0x58E920 条件 4 态下检 bit1；0x4E1780 过 bit0 → vt+1220）（证据 va=0058E920）
    unsigned char _unused_0x00A3      [69]; // +0x00A3..0x00E7 未观测
    unsigned char     bSyncFlag           ; // +0x00E8 (232) x2  基类时刻同步开关位（0x499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9      [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（0x499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（0x499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncTime           ; // +0x00F4 (244) x4  基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bQuad1              ; // +0x00F8 (248) x1  基类四元组字节槽 1（0x42A8D0 CNRDObject__vmt11C 批量写 +248..+260）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9      [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nQuad2              ; // +0x00FC (252) x1  基类四元组 dword 槽 2（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char     bQuad3              ; // +0x0100 (256) x1  基类四元组字节槽 3（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101      [3]; // +0x0101..0x0103 未观测
    unsigned int      nQuad4              ; // +0x0104 (260) x1  基类四元组 dword 槽 4（0x42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0108      [60]; // +0x0108..0x0143 未观测
    unsigned int      nRandPick324        ; // +0x0144 (324) x1  随机/拾取编号槽（0x4D6970：本槽非 0 → +6664 取 0，否则 −1500ms 哨兵位型）（证据 va=004D6970）
    unsigned char _unused_0x0148      [216]; // +0x0148..0x021F 未观测
    unsigned int      nFaction            ; // +0x0220 (544) x1  势力/阵营（src/cnrd +0x220 faction —— vt+168 敌我判定用，研究定案）（证据 va=src/cnrd）
    unsigned char _unused_0x0224      [68]; // +0x0224..0x0267 未观测
    unsigned int      nReactionState      ; // +0x0268 (616) x1  受击反应态（src/cnrd +0x268 reactionState：3 硬直 / 4 击退 / 5 击倒 —— 三层状态架构之二）（证据 va=src/cnrd）
    unsigned char _unused_0x026C      [16]; // +0x026C..0x027B 未观测
    unsigned int      nReactionPriority   ; // +0x027C (636) x1  反应优先级（src/cnrd +0x27C reactionPriority：只升不降）（证据 va=src/cnrd）
    unsigned char _unused_0x0280      [1]; // +0x0280..0x0280 未观测
    unsigned char     bHitBoxEnable       ; // +0x0281 (641) x1  受击盒使能 = 无敌开关（src/cnrd +0x281 hitBoxEnable；研究 P35；vmt25C 向附属物 +7076 数组广播 vt+604）（证据 va=src/cnrd）
    unsigned char     bAttackEnable       ; // +0x0282 (642) x5  帧时刻覆盖开关（src/cnrd/IRDActiveObject.h +642 attackEnable；0x4E5C10）（证据 va=004E5C10）
    unsigned char _unused_0x0283      [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverride      ; // +0x0284 (644) x4  基类帧时刻覆盖值（与 +0x282 成对；0x4E5C10 第四参）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0288      [60]; // +0x0288..0x02C3 未观测
    unsigned int      nDamageInfo         ; // +0x02C4 (708) x1  伤害信息槽（src/cnrd +0x2C4 damageInfo）（证据 va=src/cnrd）

    // ---- 区块 2：受击与表现壳区（命中上下文/提示串缓冲/速率槽/困难级标志） ----
    unsigned char _unused_0x02C8      [146]; // +0x02C8..0x0359 未观测
    float             fSpeed858           ; // +0x035A (858) x1  速率浮点槽（★已确证偏移语义 this+858；速率族 vt+976/vt+980/vt+37C 档位换算消费）（证据 va=确证语义）
    unsigned char _unused_0x035E      [777]; // +0x035E..0x0666 未观测
    unsigned char     bMainStateMirror2   ; // +0x0667 (1639) x1  主状态镜像 2（★已确证偏移语义 this+1639：多数怪物 AI 段作「姿态==8 攻击态」判据）（证据 va=确证语义）
    unsigned char _unused_0x0668      [52]; // +0x0668..0x069B 未观测
    char              szCueName1692       ; // +0x069C (1692) x1  播报提示串缓冲（0x4D71B0 命中主处理器 pCueName = (char*)(this+1692)）（证据 va=004D71B0）
    unsigned char _unused_0x069D      [94]; // +0x069D..0x06FA 未观测
    unsigned char     bBehaviorWord       ; // +0x06FB (1787) x1  行为字槽（★已确证偏移语义 this+1787：0x593D90/0x598380 相位机按此分派）（证据 va=确证语义）
    unsigned char _unused_0x06FC      [155]; // +0x06FC..0x0796 未观测
    unsigned int      nDifficulty         ; // +0x0797 (1943) x1  困难级标志（★已确证偏移语义 this+1943==3 走困难档语音/数值；0x593640/0x5CD4E0 消费）（证据 va=确证语义）
    unsigned char _unused_0x079B      [4185]; // +0x079B..0x17F3 未观测
    unsigned int      nAttrBlock6132      ; // +0x17F4 (6132) x1  属性块基址（vmt2AC 返回 this+6132 —— 研究定案 HP 读处；属性读取族 vmt188/18C/190/194 消费）（证据 va=src/cnrd）

    // ---- 区块 3：帧游标与状态槽区（攻击上下文三连/17 状态槽/18 观察者槽/霸体/动作子对象） ----
    unsigned char _unused_0x17F8      [36]; // +0x17F8..0x181B 未观测
    unsigned int      pAtkCtxA6172        ; // +0x181C (6172) x1  攻击上下文三连槽 A（0x4D6970：任一为 0 → 清 +6740 并 vt+932）（证据 va=004D6970）
    unsigned int      pAtkCtxB6176        ; // +0x1820 (6176) x1  攻击上下文三连槽 B（0x4D6970）（证据 va=004D6970）
    unsigned int      pAtkCtxC6180        ; // +0x1824 (6180) x1  攻击上下文三连槽 C（0x4D6970）（证据 va=004D6970）
    unsigned char _unused_0x1828      [44]; // +0x1828..0x1853 未观测
    unsigned int      anState17           ; // +0x1854 (6228) x1  17 异常状态槽数组首（vmt304 读 +6228+4*a2 —— 42 轮研究定案；vmt3DC 查状态 3/8）（证据 va=src/cnrd）
    unsigned char _unused_0x1858      [236]; // +0x1858..0x1943 未观测
    unsigned int      apObserver18        ; // +0x1944 (6468) x1  18 观察者槽数组首（vmt318 读 +6468+4*a2 —— 42 轮研究定案；vmt1F8/204 通知族遍历）（证据 va=src/cnrd）
    unsigned char _unused_0x1948      [80]; // +0x1948..0x1997 未观测
    unsigned char     bSuperArmor         ; // +0x1998 (6552) x1  霸体字节（src/cnrd +0x1998 superArmor：vt+720 setter / vmt2D4 读取器；vmt3DC 非霸体自由条件）（证据 va=src/cnrd）
    unsigned char _unused_0x1999      [7]; // +0x1999..0x199F 未观测
    unsigned char     bActionObjHead      ; // +0x19A0 (6560) x1  内嵌动作子对象起点（src/cnrd +0x19A0 actionObject[0]：vt+34C 返回；硬直时其时钟冻结）（证据 va=src/cnrd）
    unsigned char _unused_0x19A1      [27]; // +0x19A1..0x19BB 未观测
    unsigned int      nRencT0_6588        ; // +0x19BC (6588) x1  出生/复活时刻戳（0x4D6970：clock_now(this+64) 记入此槽）（证据 va=004D6970）
    unsigned int      uRenc6592           ; // +0x19C0 (6592) x1  出生复位槽（0x4D6970 清零）（证据 va=004D6970）
    unsigned int      uRenc6596           ; // +0x19C4 (6596) x1  出生复位槽（0x4D6970 清零）（证据 va=004D6970）

    // ---- 区块 4：出生复位批与影身计时区（0x4D6970 初始化 + 0x4D5A90 计时 + 攻击段号槽） ----
    unsigned char _unused_0x19C8      [64]; // +0x19C8..0x1A07 未观测
    unsigned int      uUI6664             ; // +0x1A08 (6664) x1  UI/冻结时长槽（0x4D6970：+324 非 0 → 0，否则 0xFFFFFA24 = −1500ms 哨兵）（证据 va=004D6970）
    unsigned char _unused_0x1A0C      [4]; // +0x1A0C..0x1A0F 未观测
    unsigned int      uUI6672             ; // +0x1A10 (6672) x1  出生复位槽（0x4D6970 清零）（证据 va=004D6970）
    unsigned char _unused_0x1A14      [4]; // +0x1A14..0x1A17 未观测
    unsigned char     bUI6680             ; // +0x1A18 (6680) x1  出生复位字节（0x4D6970 清零）（证据 va=004D6970）
    unsigned char _unused_0x1A19      [1]; // +0x1A19..0x1A19 未观测
    unsigned char     bUI6682             ; // +0x1A1A (6682) x1  出生复位字节（0x4D6970 清零）（证据 va=004D6970）
    unsigned char _unused_0x1A1B      [1]; // +0x1A1B..0x1A1B 未观测
    unsigned int      uUI6684             ; // +0x1A1C (6684) x1  出生复位槽（0x4D6970 清零）（证据 va=004D6970）
    unsigned int      uUI6688             ; // +0x1A20 (6688) x1  出生复位槽（-1 哨兵；0x4D6970）（证据 va=004D6970）
    unsigned int      uUI6692             ; // +0x1A24 (6692) x1  格挡/反应时刻戳（-1 哨兵；0x4D6970 复位）（证据 va=004D6970）
    unsigned char _unused_0x1A28      [20]; // +0x1A28..0x1A3B 未观测
    unsigned int      szBirthSnd6716      ; // +0x1A3C (6716) x1  出生音效名 SSO 数据槽（0x4D6970 经 vt+212 播 5000ms）（证据 va=004D6970）
    unsigned char _unused_0x1A40      [16]; // +0x1A40..0x1A4F 未观测
    unsigned int      nBirthSndCap        ; // +0x1A50 (6736) x1  出生音效名 SSO 容量（0x4D6970 <0x10 走内联缓冲）（证据 va=004D6970）
    unsigned char     bFreeze6740         ; // +0x1A54 (6740) x1  出生复位字节（src/cnrd/IRDActiveObject.h +6740 写点；vmt334 写）（证据 va=004D6970）
    unsigned char _unused_0x1A55      [3]; // +0x1A55..0x1A57 未观测
    int               nFrozenFlag         ; // +0x1A58 (6744) x1  冻结标志（src/cnrd +0x1A58 frozenFlag：vt+848 写 -1/0，vmt350/354/358 三件套；研究 P35）（证据 va=src/cnrd）
    unsigned char _unused_0x1A5C      [4]; // +0x1A5C..0x1A5F 未观测
    int               nReviveTimer        ; // +0x1A60 (6752) x1  复活计时器（src/cnrd +0x1A60 reviveTimer：vmt3E4/E8/F0 三件套读写）（证据 va=src/cnrd）
    unsigned char _unused_0x1A64      [272]; // +0x1A64..0x1B73 未观测
    unsigned int      nAttackSegSlot      ; // +0x1B74 (7028) x1  攻击段号槽（★已确证偏移语义 this+7028：0x591520/0x5CB690/0x5CD4E0 经 sub_41A5E0 防篡读）（证据 va=确证语义）
    unsigned char _unused_0x1B78      [64]; // +0x1B78..0x1BB7 未观测
    unsigned int      nStealthStart       ; // +0x1BB8 (7096) x1  影身/伪装窗口起始时刻（0x4D5A90 影身计时三连写；clock_now(this+36)）【基类字段】（证据 va=004D5A90）
    unsigned int      nStealthDur         ; // +0x1BBC (7100) x1  影身/伪装窗口时长 ms（0x4D5A90 按 1000×时长/+6656 折算剩余量）【基类字段】（证据 va=004D5A90）
    unsigned char     bStealthFlag        ; // +0x1BC0 (7104) x1  影身/伪装开关字节（0x4D5A90 置位时走折算；0x4D7F30 伪装态切换）【基类字段】（证据 va=004D5A90）
    unsigned char     bSet7105            ; // +0x1BC1 (7105) x1  出生复位字节（0x4D6970 清；vmt3AC 读）（证据 va=004D6970）
    unsigned char _unused_0x1BC2      [2]; // +0x1BC2..0x1BC3 未观测
    unsigned int      uSet7108            ; // +0x1BC4 (7108) x1  出生复位槽（-1 哨兵；0x4D6970）（证据 va=004D6970）
    unsigned int      uSet7112            ; // +0x1BC8 (7112) x1  出生复位槽（0x4D6970 清零）（证据 va=004D6970）

    // ---- 区块 5：大状态/目标/光环/反击态区与子类续写区（+7148 大状态 / +7252 目标 / +7256 光环 / +7772 反击态 / +8352 骑乘 / +8600 起子类） ----
    unsigned char _unused_0x1BCC      [32]; // +0x1BCC..0x1BEB 未观测
    unsigned int      nBigState           ; // +0x1BEC (7148) x1  ★大状态 ID（★已确证偏移语义 this+7148：0x4DB480 反击判定；0x4D9000 白名单 / 0x4D9040 setter）（证据 va=确证语义）
    unsigned char _unused_0x1BF0      [100]; // +0x1BF0..0x1C53 未观测
    unsigned int      pTarget7252         ; // +0x1C54 (7252) x1  当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）
    unsigned int      pAuraObject         ; // +0x1C58 (7256) x1  光环对象（★已确证偏移语义 this+7256）（证据 va=确证语义）
    unsigned char _unused_0x1C5C      [512]; // +0x1C5C..0x1E5B 未观测
    unsigned int      nCounterState       ; // +0x1E5C (7772) x1  反击态（★已确证偏移语义 this+7772；0x4DB480 变量名 nCounterState，值 1/2）（证据 va=确证语义）
    unsigned char _unused_0x1E60      [576]; // +0x1E60..0x209F 未观测
    unsigned int      nRideHost8352       ; // +0x20A0 (8352) x1  骑乘宿主槽（★已确证偏移语义 this+8352）（证据 va=确证语义）
};
#pragma pack(pop)

// ============================================================
// ---- 内嵌子对象（4×1364B）----  〔会话 12 新增（docs/22 §二 #3）〕
// ============================================================
// 直证（下三处互证，均指向同一区间 +676..+6131）：
//   ① 构造 0x4A49B0（src/game/rtti_core.cpp:4509，IRDActiveObject 构造函数，RTTI 直证）：
//       `eh vector constructor iterator'(this+676, 0x554(1364), 4, ctor=0x4A1670, dtor=0x4A1F00)
//   ② 析构 0x4A4BD0（src/game/rtti_core.cpp:4597）：
//       `eh vector destructor iterator'(this+676, 0x554(1364), 4, dtor=0x4A1F00)
//   ③ 子对象基址 getter vmt2A0 0x4A0C80（src/cnrd/IRDActiveObject.cpp:71 /
//       src/game/rtti_core.cpp:807，RTTI 直证 IRDActiveObject__vmt2A0）：
//       return this + 1364*a2 + 676 —— 与 ①② 步长/基址完全一致。
// 结论：IRDActiveObject 内嵌 **4 个 1364 字节（0x554）子对象**，占据 +0x2A4..+0x17F3（+676..+6131）。
//   注：docs/14 §4 早期记「5 个 1364B 子对象」(a2=0..4)；按 ①② 实测为 **4 个**——
//       idx4 基址 = +676+4*1364 = +6132，该处并非子对象，而是独立的属性块（由
//       sub_4A1C30(this+6132) 单独构造，见 0x4A49B0 第 ③ 步），故「第 5 个」为误计。
// 子对象偏移范围（vmt2A0 索引 idx → 基址）：
//   idx0  +0x02A4..+0x07F7 (676..2039)   子对象 #0
//   idx1  +0x07F8..+0x0D4B (2040..3403)  子对象 #1
//   idx2  +0x0D4C..+0x129F (3404..4767)  子对象 #2
//   idx3  +0x12A0..+0x17F3 (4768..6131)  子对象 #3  ★ 属性表子对象（见下）
// 内部结构（子对象相对偏移；构造器 0x4A1670 / 值初始化族 0x4A1210 逐槽直证）：
//   · 0..3       clong 头（clong::vftable，0x4A1670 首槽 sub_41A630 后写 &clong::`vftable'）
//   · clong/cfloat 属性对表，元素 14 字节、步长 14：
//       对 k=0..11 起始于字节 4+14k（clong）与 18+14k（cfloat，即 clong 值 +14）——
//       即相对 4/18、32/46、60/74、88/102、116/130、144/158 共 12 对
//   · 内嵌数组（`eh vector constructor iterator' 直证）：
//       相对 172 起 4 元素 ×14B（ctor 0x4A1670 内 this+43）
//       相对 228 起 4 元素 ×14B（this+57）
//       相对 284 起 16 元素 ×14B（this+71）
//       相对 508 起 16 元素 ×14B（this+127）
//   · clong/cfloat 属性对表（续），相对字节 732/746、760/774、788/802、816/830、844/858、
//       872/886、900/914、928/942、956/970、984/998、1012/1026、1040/1054、1068/1082、
//       1096/1110、1124/1138、1152/1166、1180/1194、1208/1222、1236/1250、1264/1278、
//       1292/1306、1320/1334、1348/1352（0x4A1670 逐槽 sub_41A630 + clong/cfloat vftable）
//   · ★ 子对象 #3（idx3，基址 +4768）承载"属性表"：vmt188/18C/190/194 及 vmt3D0 经
//       `vt+672(this,3)` 取到 idx3 基址后按相对 +60/+74（HP 类）、+816/+830（移动速度）、
//       +844/+858（攻击速度）、+1012/+1026（MP 类）、+1124/+1306 读写（研究 P14/17 防篡读闭环）。
//       —— 说明「属性块」即子对象 #3 内的 clong/cfloat 对。且上述每个相对偏移都正好是
//       构造器 0x4A1670 初始化的「4+14k」槽（60=4+14·4、74=18+14·4、816=4+14·58、
//       830=18+14·58、844/858 同族、1012/1026、1124、1306），属对 ctor 布局的独立互证。
//   注：绝对偏移 +858 / +1639 / +1692 / +1787 / +1943 等父类标量落在子对象 #0 区间内
//       （676..2039），即父类以绝对偏移直取子对象 #0 成员 —— 两种视角一致，绝对偏移为真。
// ============================================================

// 统计: 字段行 59 / 已命名 59 / 未命名 0 / 标【推断】0 / 末尾偏移 +0x20A4
// 内嵌子对象: 4 × 1364B（+676..+6131；ctor 0x4A49B0 / dtor 0x4A4BD0 / getter vmt2A0 0x4A0C80 三处直证）


// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: CNGunner   主虚表槽位数: 334
// 继承: CNGunner -> IRDCharacter -> IRDActiveObject -> IRDCollisionObject -> CNRDObject
//        -> KGameMessenger -> KMessenger（基类段见 src/cnrd/*.h）
// 本类覆写 24 个槽（+0/+12/+296/+300/+324/+328/+332/+472/+500/+508/+512/+516
//   /+648/+784/+904/+1100/+1108/+1152/+1164/+1300/+1304/+1316/+1328/+1332）。
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 f_XXXX 占位）
// 证据主源（本类 334 槽函数）:
//   +648 0x4C0760 伤害上限/受击截断（src/game/gunner_state.cpp:473）
//   +1316 0x4C0A30 大状态武器动作批设（gunner_state.cpp:623）
//   +784 0x4C2360 武器物件换装刷新（gunner_state.cpp:2143）
//   +1300 0x4C39D0 属性弹 Buff 演出（gunner_state.cpp:3210）
//   +344 0x4AF8E0 能力槽惰性初始化（src/game/rtti_core.cpp:11793）
//   基类共享: 0x499020(+260)/0x499080/0x42A8D0/0x4E5C10(+612)/0x4D5A90/0x5796C0/0x4B4EE0
// ============================================================
#ifndef ARAD40JP_FIELDS_CNGUNNER
#define ARAD40JP_FIELDS_CNGUNNER

#include <stdint.h>

#pragma pack(push, 1)
struct CNGunner_Fields {
    unsigned char _base_head[120]; // +0x0000..0x0077 继承自 CNRDObject/IRDCollisionObject/IRDActiveObject/IRDCharacter（见 src/cnrd/*.h；首个观测偏移之前）（不重复展开）
    unsigned int     pAnimObj;        // +0x0078 (120) x6  va=00499020 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】
    unsigned char _unused_007C[108]; // +0x007C..0x00E7 未观测
    unsigned char    bSyncFlag;       // +0x00E8 (232) x2  va=00499020 基类时刻同步开关位（0x499020）【基类字段】
    unsigned char _unused_00E9[3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA;       // +0x00EC (236) x1  va=00499020 基类时刻同步参数 A【基类字段】
    unsigned int     nSyncArgB;       // +0x00F0 (240) x1  va=00499020 基类时刻同步参数 B【基类字段】
    float            fSyncTime;       // +0x00F4 (244) x4  va=00499080 基类浮点时刻槽（0x499080）【基类字段】
    unsigned char    bQuad1;          // +0x00F8 (248) x1  va=0042A8D0 基类四元组字节槽 1（CNRDObject__vmt11C）【基类字段】
    unsigned char _unused_00F9[3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2;          // +0x00FC (252) x1  va=0042A8D0 基类四元组 dword 槽 2【基类字段】
    unsigned char    bQuad3;          // +0x0100 (256) x1  va=0042A8D0 基类四元组字节槽 3【基类字段】
    unsigned char _unused_0101[3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4;          // +0x0104 (260) x1  va=0042A8D0 基类四元组 dword 槽 4【基类字段】
    // ---- 区块: 能力槽（状态时长）族（0x4AF8E0） ----
    unsigned char _unused_0108[248]; // +0x0108..0x01FF 未观测
    unsigned int     nAbilityId;      // +0x0200 (512) x2  va=004AF8E0 ★ 能力槽 id（0x4AF8E0 惰性初始化: ==4 时用 vt+1176/vt+1180 重取两值）【基类字段】
    unsigned char    bAbilityFlag;    // +0x0204 (516) x1  va=004AF8E0 ★ 能力槽标志字节（0x4AF8E0 由 vt+1180() 写入）【基类字段】
    unsigned char _unused_0205[3]; // +0x0205..0x0207 未观测
    unsigned int     nAbilityDur;     // +0x0208 (520) x5  va=004AF8E0 ★ 能力槽时长/基础值（0x4AF8E0: ==-1 用 vt+1184 取初值；>0 按 (2.0−属性块+1292)×它修正）【基类字段】
    unsigned int     fAbilityScale;   // +0x020C (524) x2  va=004AF8E0 ★ 能力槽浮点缩放（0x4AF8E0: ==-4.0f 用 vt+1188 取初值）【基类字段】
    // ---- 区块: 表现壳与帧覆盖族（0x4E5C10） ----
    unsigned char _unused_0210[114]; // +0x0210..0x0281 未观测
    unsigned char    bAttackEnable;   // +0x0282 (642) x5  va=004E5C10 攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；基类定案 +642）【基类字段】
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride;  // +0x0284 (644) x4  va=004E5C10 帧时刻覆盖值（0x4E5C10 第四参）【基类字段】
    // ---- 区块: 武器物件与换装族（0x4C2360） ----
    unsigned char _unused_0288[5852]; // +0x0288..0x1963 未观测
    unsigned int     nWeaponItemId;   // +0x1964 (6500) x3  va=004C2360 ★ 当前武器/弹药物件 id（0x4C2360: 读 +6500 后经 sub_4B36A0 换装部件；map 变更时 sub_4C1C80 刷新 +8220）
    // ---- 区块: 大状态与武器动作批设族（0x4C0A30） ----
    unsigned char _unused_1968[52]; // +0x1968..0x199B 未观测
    unsigned int     nBigState;       // +0x199C (6556) x1  va=004C0A30 ★ 枪手大状态 ID（0x4C0A30: switch(this+6556) case 0/11 批量设武器动作；IRDActiveObject +6556 定案）
    unsigned char _unused_19A0[536]; // +0x19A0..0x1BB7 未观测
    unsigned int     nStealthStart;   // +0x1BB8 (7096) x1  va=004D5A90 【推断】隐身/伪装窗口起始时刻（0x4D5A90 影身计时三连写，基类同址）【基类字段】
    unsigned int     nStealthDur;     // +0x1BBC (7100) x1  va=004D5A90 【推断】隐身/伪装窗口时长 ms（0x4D5AC0 折算）【基类字段】
    unsigned char    bStealthFlag;    // +0x1BC0 (7104) x1  va=004D5A90 【推断】隐身/伪装开关字节【基类字段】
    unsigned char _unused_1BC1[43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nSubState;       // +0x1BEC (7148) x2  va=005796C0 大状态镜像槽（0x5796C0 写 this+7148；与 IRDActiveObject +7148 同址）【基类字段】
    unsigned int     nParam2;         // +0x1BF0 (7152) x1  va=005796C0 0x5796C0 写入槽（基类参数块 +4）【基类字段】
    unsigned char    bParam3;         // +0x1BF4 (7156) x1  va=005796C0 0x5796C0 写入字节（基类参数块 +8）【基类字段】
    unsigned char _unused_1BF5[259]; // +0x1BF5..0x1CF7 未观测
    unsigned int     map7416;         // +0x1CF8 (7416) x1  va=004B4EE0 键到值 map 起始（0x4B4EE0 在此做插入/删除；基类 7416 map）【基类字段】
    unsigned int     map7416End;      // +0x1CFC (7420) x1  va=004B4EE0 键到值 map 尾指针（0x4B4EE0 与 +7420 比较判断命中）【基类字段】
    // ---- 区块: 子类使能族（0x4C0A30 / 0x4C0760） ----
    unsigned char _unused_1D00[306]; // +0x1D00..0x1E31 未观测
    unsigned char    bSubEnable;      // +0x1E32 (7730) x1  va=004C0A30 ★ 子类使能字节（0x4C0A30: 非 0 才继续大状态批量武器动作；0x4C0760/5E1000 同址判据）
    unsigned char _unused_1E33[489]; // +0x1E33..0x201B 未观测
    size_t           bWeaponRefresh;  // +0x201C (8220) x1  va=004C2360 ★ 武器/外观刷新标志（0x4C2360: 经 sub_4C1C80 刷新 +8220 处外观对象）
    unsigned char _unused_2020[292]; // +0x2020..0x2143 未观测
    unsigned int     nItemCtx;        // +0x2144 (8516) x1  va=004C0A30 ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）
    unsigned char _unused_2148[77]; // +0x2148..0x2194 未观测
    unsigned char    bCapGate;        // +0x2195 (8597) x1  va=004C0760 ★ 上限门字节（0x4C0760: 非 0 时直接返回 1 截断伤害）
    // ---- 区块: 属性弹 Buff 族（0x4C39D0） ----
    unsigned char _unused_2196[30]; // +0x2196..0x21B3 未观测
    unsigned int     pBuffIcon;       // +0x21B4 (8628) x1  va=004C39D0 【推断】Buff 图标对象指针（0x4C39D0: *(this+8628)=result，配合 BUFF_FLAMESHOT/ICESHOT/SILVERSHOT 弹种演出）
    unsigned char _unused_21B8[24]; // +0x21B8..0x21CF 未观测
    unsigned int     pBulletBuff;     // +0x21D0 (8656) x6  va=004C39D0 ★ 属性弹 Buff 对象（0x4C39D0: ==0 时 new 0x60 经 sub_4C10A0 构造；火/冰/银弹族）
    unsigned int     pBulletBuff2;    // +0x21D4 (8660) x4  va=004C39D0 ★ 属性弹 Buff 对象 2（0x4C39D0 与 +21D0 成对，同样懒创建）
    // ---- 区块: 伤害上限族（0x4C0760） ----
    unsigned char _unused_21D8[296]; // +0x21D8..0x22FF 未观测
    unsigned char    bDmgCapOn;       // +0x2300 (8960) x1  va=004C0760 ★ 伤害上限开关字节（0x4C0760: 非 0 时把伤害夹到 +8964 上限并返回 2）
    unsigned char _unused_2301[3]; // +0x2301..0x2303 未观测
    unsigned int     nDmgCap;         // +0x2304 (8964) x1  va=004C0760 ★ 伤害上限值（0x4C0760: *pDwArg2 >= +8964 则钳制）
    unsigned int     nDmgCapCtx;      // +0x2308 (8968) x1  va=004C0A30 ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）
};
#pragma pack(pop)

// 统计: 字段行 35 / 未命名 0 / 标【推断】4 / 末尾偏移 +0x230C

#endif

// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 12 批量还原 · 批 A）
// 类: CNGunnerBullet     主虚表槽位数: 177   字段数: 42
// 继承链: KMessenger -> KGameMessenger -> CNRDObject×2 -> IRDCollisionObject×3 -> CNRDPassiveObject×4 -> CNGunnerBullet
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名按证据判定（偏移/类型/次数为二进制直证，未改）
// 置信度: 偏移/类型/次数=二进制直证；语义名=证据推断（【推断】标注无直证者；无证据保留 field_XXXX）
// 命名依据: ①本类专属证据行函数头注释（src/combat/passive_object.cpp、src/combat/breakable_map.cpp、src/game/creature/*.cpp、src/game/rtti_core.cpp 等；须本类函数体出现该偏移才生效）②全库通用偏移表（this+120/+244/+642/+7148/+7772/+8352 等，历代定案）③同族 (证据 VA, 偏移) 复用既有语义表（PO 族 <- CNFairy/CNFallingStorage 等；怪物族 <- IRDMonster/CNGuardWind 等）
// 说明: 0x0000 起为基类继承段（下示候选字段=该段中的直证访问点，非本类新增段）；+8600 之后为子类 AI 状态区（怪物族）
// ============================================================
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
struct CNGunnerBullet_Fields {
    // ---- 区块 1：继承 CNRDPassiveObject 基类区（宿主组件/动画对象；继承段） ----
    unsigned char _base_0x0000      [120]; // +0x0000..0x0077 继承 CNRDObject/IRDCollisionObject 前 0x78 字节（见 src/cnrd/*.h 与 IRDMonster.h；不重复展开）
    unsigned int      pAnimObj            ; // +0x0078 (120) x6  动画对象指针（★全库通用 this+120；499020/499080 帧推进宿主）【基类字段】（证据 va=00499020）

    // ---- 区块 2：基类时刻同步与参数灌入区（4 元组槽 / 帧同步槽） ----
    unsigned char _unused_0x007C    [108]; // +0x007C..0x00E7 未观测
    unsigned char     bSyncSwitch         ; // +0x00E8 (232) x2  基类时刻同步开关位（499020 读旧值：非 0 转 0 时推进帧时刻）【基类字段】（证据 va=00499020）
    unsigned char _unused_0x00E9    [3]; // +0x00E9..0x00EB 未观测
    unsigned int      nSyncArgA           ; // +0x00EC (236) x1  基类时刻同步参数 A（499020 第三参）【基类字段】（证据 va=00499020）
    unsigned int      nSyncArgB           ; // +0x00F0 (240) x1  基类时刻同步参数 B（499020 第四参）【基类字段】（证据 va=00499020）
    float             fSyncValue          ; // +0x00F4 (244) x4  基类浮点时刻槽（499080 浮点版：非 0 转 0 时推帧）【基类字段】（证据 va=00499080）
    unsigned char     bParamSlotA         ; // +0x00F8 (248) x1  基类四元组字节槽 1（42A8D0 CNRDObject__vmt11C 批量写 +248..+260）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x00F9    [3]; // +0x00F9..0x00FB 未观测
    unsigned int      nParamSlotB         ; // +0x00FC (252) x1  基类四元组 dword 槽 2（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char     bParamSlotC         ; // +0x0100 (256) x1  基类四元组字节槽 3（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0101    [3]; // +0x0101..0x0103 未观测
    unsigned int      nParamSlotD         ; // +0x0104 (260) x1  基类四元组 dword 槽 4（42A8D0）【基类字段】（证据 va=0042A8D0）
    unsigned char _unused_0x0108    [124]; // +0x0108..0x0183 未观测
    float             fAtkCtxVal          ; // +0x0184 (388) x14 攻击上下文浮点值（607420 vmt158 装配：*(+388) += fld_3E4；同族 vmt158 攻击上下文槽）（证据 va=00607420）
    unsigned char _unused_0x0188    [4]; // +0x0188..0x018B 未观测
    unsigned int      uReflectCtx         ; // +0x018C (396) x1  攻击上下文计数字槽（607420：*(+396) += 200 自累加）【推断】（证据 va=00607420）
    unsigned char _unused_0x0190    [8]; // +0x0190..0x0197 未观测
    unsigned int      uAtkLimb0           ; // +0x0198 (408) x3  攻击盒肢体槽 A（607420：*(+408)=0/1 按 fld_3E0 档切换）【推断】（证据 va=00607420）
    unsigned int      uAtkLimb1           ; // +0x019C (412) x1  攻击盒肢体槽 B（607420：pThis_19C = this+412 起遍历）【推断】（证据 va=00607420）
    unsigned char _unused_0x01A0    [32]; // +0x01A0..0x01BF 未观测
    unsigned int      uAtkStage448        ; // +0x01C0 (448) x2  攻击阶段号（607420：*(+448)=2）【推断】（证据 va=00607420）
    unsigned int      uAtkRoll452         ; // +0x01C4 (452) x1  攻击中间量（607420：*(+452)=fld_3DC5）【推断】（证据 va=00607420）
    unsigned int      uAtkVal456          ; // +0x01C8 (456) x1  攻击参数槽（607420：*(+456)=sub_47EF20(0,...)）【推断】（证据 va=00607420）
    float             fAccDmg460          ; // +0x01CC (460) x2  伤害累积浮点（607420：Self += sub_47EF20(2,...)*0.1 —— 46 0 同族自累加）【推断】（证据 va=00607420）
    float             fRate464            ; // +0x01D0 (464) x3  速率/延迟初值（607420 写 -998637568 = -1000.0f 位型）【推断】（证据 va=00607420）
    unsigned char _unused_0x01D4    [40]; // +0x01D4..0x01FB 未观测
    unsigned int      uPetFlag            ; // +0x01FC (508) x1  伙伴/弹体标志（607420：*(+508) = (状态(+972)!=0)+1）【推断】（证据 va=00607420）
    unsigned char _unused_0x0200    [12]; // +0x0200..0x020B 未观测
    float             fDmgScale524        ; // +0x020C (524) x4  伤害缩放中间量（607420：*(+524) *= 0.5 衰减）【推断】（证据 va=00607420）

    // ---- 区块 3：帧时刻覆盖（基类 4E5C10） ----
    unsigned char _unused_0x0210    [114]; // +0x0210..0x0281 未观测
    unsigned char     bFrameOverride      ; // +0x0282 (642) x5  帧时刻覆盖开关（4E5C10：非 0 时用 +644 直写帧时刻）【基类字段】（证据 va=004E5C10）
    unsigned char _unused_0x0283    [1]; // +0x0283..0x0283 未观测
    unsigned int      nFrameOverrideTime  ; // +0x0284 (644) x4  帧时刻覆盖值（4E5C10）【基类字段】（证据 va=004E5C10）

    // ---- 区块 4：表现/名字快照块与资源表（4E1FE0 28 字节直拷 + 60B3D0 装载） ----
    unsigned char _unused_0x0288    [32]; // +0x0288..0x02A7 未观测
    unsigned int      nSnapshot680        ; // +0x02A8 (680) x1  表现/名字快照[0]（4E1FE0 由 28 字节源块直拷）（证据 va=004E1FE0）
    unsigned int      nSnapshot684        ; // +0x02AC (684) x1  表现/名字快照[1]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      nSnapshot688        ; // +0x02B0 (688) x1  表现/名字快照[2]（4E1FE0）（证据 va=004E1FE0）
    unsigned int      pLastHitObj692      ; // +0x02B4 (692) x3  最后命中对象（607420 传 *(this+692) 入几何族；608CD0 比对防重入）（证据 va=00607420）
    unsigned int      pAmmoParam696       ; // +0x02B8 (696) x2  弹种参数句柄（608CD0：*(+696)=sub_41A5E0(命中者+8502)）（证据 va=004E1FE0）
    unsigned char     bSnapshot700        ; // +0x02BC (700) x1  表现/名字快照[20]（4E1FE0）（证据 va=004E1FE0）
    unsigned char     bSnapshot701        ; // +0x02BD (701) x1  表现/名字快照[21]（4E1FE0）（证据 va=004E1FE0）
    unsigned char _unused_0x02BE    [2]; // +0x02BE..0x02BF 未观测
    unsigned int      nSnapshot704        ; // +0x02C0 (704) x1  表现/名字快照[24]（4E1FE0）（证据 va=004E1FE0）

    // ---- 区块 5：载荷缓冲与配置表直拷面（5FFF80 / 60B3D0） ----
    unsigned char _unused_0x02C4    [256]; // +0x02C4..0x03C3 未观测
    unsigned int      nBlobSize           ; // +0x03C4 (964) x1  载荷缓冲字节数（5FFF80：*(this+964)=Size）（证据 va=005FFF80）
    unsigned int      pBlobData           ; // +0x03C8 (968) x3  载荷缓冲指针（5FFF80：旧块 free 后 operator new(Size) 存入）（证据 va=005FFF80）
    unsigned int      nBulletPhase972     ; // +0x03CC (972) x7  弹道状态档（607420/608430 主消费；弹体朝向/反弹档）（证据 va=00607420）
    unsigned int      nBulletKind976      ; // +0x03D0 (976) x1  弹体种类/索引（608CD0 = 命中者 vt+1096()）（证据 va=00608CD0）
    unsigned int      nBulletSub980       ; // +0x03D4 (980) x15 弹体子档/引用（607420 fld_3D0 传几何族；初值 -1）（证据 va=00607420）
    unsigned int      nBulletSeq984       ; // +0x03D8 (984) x4  弹体时序槽（607420 fld_3D8；初值 -1 = 无效档）（证据 va=00607420）
    unsigned int      nAtk978_988         ; // +0x03DC (988) x9  弹道攻击参数（607420 sub_47EFD0 调用参）（证据 va=00607420）
    unsigned int      nBulletCtx992       ; // +0x03E0 (992) x1  弹道上下文档（607420 switch(fld_3E0) 1/2 分支）（证据 va=00607420）
    unsigned int      uBulletTbl996       ; // +0x03E4 (996) x4  弹道查表项（607420 sub_47EF20(1,*(+996))）（证据 va=00607420）
    unsigned char _unused_0x03E8    [38]; // +0x03E8..0x040D 未观测
    unsigned char     bHitOnce1038        ; // +0x040E (1038) x2  命中登记位（608CD0：命中后置 1 防重复处理）（证据 va=00608CD0）

    // ---- 区块 6：子类扩展槽区 ----
    unsigned char _unused_0x040F    [7557]; // +0x040F..0x2193 未观测
    unsigned char     bTargetState        ; // +0x2194 (8596) x1  命中者状态快照（608CD0 读 pObj+8596 决定弹道档）（证据 va=00608CD0）
    unsigned char _unused_0x2195    [59]; // +0x2195..0x21CF 未观测
    unsigned int      pTargetSub8656      ; // +0x21D0 (8656) x2  命中者子对象槽（608CD0 取 pObj+8656 挂拖尾粒子）（证据 va=00608CD0）
};
#pragma pack(pop)

// 统计: 字段行 42 / 已命名 42 / 未命名 0 / 标【推断】10 / 末尾偏移 +0x21D4

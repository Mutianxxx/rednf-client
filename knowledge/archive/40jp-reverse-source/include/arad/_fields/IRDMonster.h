// ============================================================
// 【40JP逆向源代码工程】字段语义表（会话 11 还原）
// 类: IRDMonster   主虚表槽位数: 327
// 继承: IRDMonster -> IRDActiveObject -> IRDCollisionObject -> CNRDObject -> KGameMessenger -> KMessenger
//        （基类字段精修见 src/cnrd/*.h；本类覆写 93 个槽，其余沿用基类实现）
// 还原方法: 类槽位函数 this+N 聚合（tools/recover_fields.py）+ 语义名人工判定
// 置信度: 偏移/类型=二进制直证（证据 VA 均取自本类虚表槽函数）;
//         语义名=证据推断（无直证者尾标【推断】；无证据者保留 f_XXXX 占位）
// 证据主源（本类 327 槽函数）:
//   +1192 0x4DE700 怪物扩展字段重置（src/game/combat_core.cpp:11203）
//   +1120 0x4DE410 名称模板写入 + 随机倒计时（combat_core.cpp:11053）
//   +332  0x4E1780 怪物逐帧表现主循环（src/game/hiteff_monster.cpp:1260）
//   +500  0x4DB480 反击/架招触发判定（combat_core.cpp:8891）
//   +1168 0x4D94A0 拾取信息快照读写（combat_core.cpp:7030）
//   +1036 0x4A41C0 内嵌配置块整体拷贝（src/game/rtti_core.cpp:4015）
// ============================================================
#ifndef ARAD40JP_FIELDS_IRDMONSTER
#define ARAD40JP_FIELDS_IRDMONSTER

#include <stdint.h>

#pragma pack(push, 1)
struct IRDMonster_Fields {
    unsigned char _base_head[73]; // +0x0000..0x0048 继承自 CNRDObject/IRDCollisionObject/IRDActiveObject（见 src/cnrd/*.h；前 0x49 字节）（不重复展开）
    char             szDigitalName;   // +0x0049 (73) x1  va=004DE410 基类数字名缓冲起点（0x4DE410 sprintf 名称后写 vt+340() 动作对象 +4）
    unsigned char _unused_004A[22]; // +0x004A..0x005F 未观测
    unsigned int     f_0060;          // +0x0060 (96) x1  【保留占位】仅见写（0x4DE700 写 529 / 0x4E7160 写 1，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_0064[20]; // +0x0064..0x0077 未观测
    unsigned int     pAnimObj;        // +0x0078 (120) x6  va=00499020 基类动画对象指针（0x499020 帧时刻同步宿主；IRDActiveObject 同址）【基类字段】
    unsigned char _unused_007C[38]; // +0x007C..0x00A1 未观测
    unsigned char    uFlag162;        // +0x00A2 (162) x1  va=004E1780 基类标志位组（0x4E1780 过 bit0 → vt+1220 分支）【基类字段】
    unsigned char _unused_00A3[69]; // +0x00A3..0x00E7 未观测
    unsigned char    bSyncFlag;       // +0x00E8 (232) x2  va=00499020 基类时刻同步开关位（0x499020 读旧值）【基类字段】
    unsigned char _unused_00E9[3]; // +0x00E9..0x00EB 未观测
    unsigned int     nSyncArgA;       // +0x00EC (236) x1  va=00499020 基类时刻同步参数 A（0x499020 第三参）【基类字段】
    unsigned int     nSyncArgB;       // +0x00F0 (240) x1  va=00499020 基类时刻同步参数 B（0x499020 第四参）【基类字段】
    float            fSyncTime;       // +0x00F4 (244) x4  va=00499080 基类浮点时刻槽（0x499080 浮点版：非 0 转 0 时推帧）【基类字段】
    unsigned char    bQuad1;          // +0x00F8 (248) x1  va=0042A8D0 基类四元组字节槽 1（CNRDObject__vmt11C 批量写）【基类字段】
    unsigned char _unused_00F9[3]; // +0x00F9..0x00FB 未观测
    unsigned int     nQuad2;          // +0x00FC (252) x1  va=0042A8D0 基类四元组 dword 槽 2【基类字段】
    unsigned char    bQuad3;          // +0x0100 (256) x1  va=0042A8D0 基类四元组字节槽 3【基类字段】
    unsigned char _unused_0101[3]; // +0x0101..0x0103 未观测
    unsigned int     nQuad4;          // +0x0104 (260) x1  va=0042A8D0 基类四元组 dword 槽 4【基类字段】
    // ---- 区块: 受击/表现开关族（0x4DE700 / 0x4E5C10 / 0x5908E0） ----
    unsigned char _unused_0108[344]; // +0x0108..0x025F 未观测
    unsigned int     nAttackGate;     // +0x0260 (608) x1  va=004DE700 攻击盒/攻防门初值（0x4DE700 写 100；0x4E7160 同址清 0；研究 §P29 攻防门）【推断】
    unsigned char _unused_0264[30]; // +0x0264..0x0281 未观测
    unsigned char    bAttackEnable;   // +0x0282 (642) x5  va=004E5C10 攻击使能/表现壳开关（0x4E5C10 帧时刻覆盖标志；IRDActiveObject 定案 +642）【基类字段】
    unsigned char _unused_0283[1]; // +0x0283..0x0283 未观测
    unsigned int     nFrameOverride;  // +0x0284 (644) x4  va=004E5C10 帧时刻覆盖值（与 +282 成对；0x4E5C10 第四参）【基类字段】
    unsigned int     uMonFlagBits;    // +0x0288 (648) x1  va=004DE700 怪物位标志字（0x5908E0 掩码清 bit0 = APPEAR 已播标志）
    unsigned char _unused_028C[16]; // +0x028C..0x029B 未观测
    unsigned int     nPickPosCache;   // +0x029C (668) x1  va=004D94A0 拾取/交互目标坐标缓存（sub_4D94A0 由 +8352 拷入，与 +672 成对）【推断】
    unsigned int     bPickPosValid;   // +0x02A0 (672) x1  va=004D94A0 拾取/交互目标有效标志（与 +668 成对置 1）【推断】
    // ---- 区块: 隐身/伪装窗口族（0x4D5A90 影身计时三连写） ----
    unsigned char _unused_02A4[6420]; // +0x02A4..0x1BB7 未观测
    unsigned int     nStealthStart;   // +0x1BB8 (7096) x1  va=004D5A90 【推断】隐身/伪装窗口起始时刻（0x4D5A90 影身计时三连写；配合 0x4D7F30）【基类字段】
    unsigned int     nStealthDur;     // +0x1BBC (7100) x1  va=004D5A90 【推断】隐身/伪装窗口时长 ms（0x4D5AC0 按 1000×时长/+6656 折算剩余量）【基类字段】
    unsigned char    bStealthFlag;    // +0x1BC0 (7104) x1  va=004D5A90 【推断】隐身/伪装开关字节（置位时 0x4D5AC0 走折算；0x4D7F30 伪装态切换）【基类字段】
    // ---- 区块: 大状态与名称串族（0x4DB480 / 0x4DE700） ----
    unsigned char _unused_1BC1[43]; // +0x1BC1..0x1BEB 未观测
    unsigned int     nBigState;       // +0x1BEC (7148) x2  va=004DB480 ★ 怪物大状态 ID（0x4DB480 反击判定 11/12→切 4；0x4D9000 白名单/0x4D9040 setter/0x4DF2D0 tick 分派）
    unsigned int     szNameHead;      // +0x1BF0 (7152) x1  va=004DE700 std::string 布局槽（0x4DE700 清空拼接；+7156 数据/+7172 size/+7176 cap）【推断：SSO 头】
    unsigned int     szNameBuf;       // +0x1BF4 (7156) x2  va=004DE700 std::string SSO 内联缓冲（16 字节；0x4DE410/0x4DE700 名称装配）
    unsigned char _unused_1BF8[12]; // +0x1BF8..0x1C03 未观测
    unsigned int     nNameStrSize;    // +0x1C04 (7172) x1  va=004DE700 std::string 长度字段（0x4DE700 经 +7172 定位尾）
    unsigned int     nNameStrCap;     // +0x1C08 (7176) x1  va=004DE700 std::string 容量字段（<0x10 走内联缓冲）
    // ---- 区块: 内嵌配置块（0x4A41C0 整体拷贝；0x4A1150/0x4A1160 取基址） ----
    unsigned char _unused_1C0C[340]; // +0x1C0C..0x1D5F 未观测
    unsigned int     nSightRange;     // +0x1D60 (7520) x1  va=004A41C0 ★ 内嵌配置块首 DWORD / 视野值（0x4DA5F0 索敌门算距离衰减；0x4D8FE0 盲眼态返 10 否则返它；0x4A1150 取块基址）
    unsigned int     nCfgBlock4;      // +0x1D64 (7524) x1  va=004A41C0 内嵌配置块 +4（0x4A41C0 整体拷贝）【推断】
    unsigned char    bCfgBlock8;      // +0x1D68 (7528) x1  va=004A41C0 内嵌配置块 +8 字节
    unsigned char    bCounterEnable;  // +0x1D69 (7529) x2  va=004DB480 【推断】反击/架招生效标志（0x4DB480 命中后据此调 vt+1236）
    unsigned char    bCfgBlock10;     // +0x1D6A (7530) x1  va=004A41C0 内嵌配置块 +10 字节
    unsigned char    bCfgBlock11;     // +0x1D6B (7531) x1  va=004A41C0 内嵌配置块 +11 字节
    unsigned char    bCfgBlock12;     // +0x1D6C (7532) x1  va=004A41C0 内嵌配置块 +12 字节
    unsigned char    bCfgBlock13;     // +0x1D6D (7533) x1  va=004A41C0 内嵌配置块 +13 字节
    unsigned char    bCfgBlock14;     // +0x1D6E (7534) x1  va=004A41C0 内嵌配置块 +14 字节
    unsigned char    bCfgBlock15;     // +0x1D6F (7535) x1  va=004A41C0 内嵌配置块 +15 字节
    unsigned char    bCfgBlock16;     // +0x1D70 (7536) x1  va=004A41C0 内嵌配置块 +16 字节
    unsigned char    bCfgBlock17;     // +0x1D71 (7537) x1  va=004A41C0 内嵌配置块 +17 字节
    unsigned char    bCfgBlock18;     // +0x1D72 (7538) x1  va=004A41C0 内嵌配置块 +18 字节
    unsigned char    bCfgTail;        // +0x1D73 (7539) x1  va=004A41C0 配置块 17 字节循环搬运区起点（0x4A41C0）
    // ---- 区块: 名牌/骑乘/窗口复位族（0x4DE700 复位批） ----
    unsigned char _unused_1D74[92]; // +0x1D74..0x1DCF 未观测
    unsigned int     nPosWinX;        // +0x1DD0 (7632) x1  【推断】坐标窗口X（0x4D9790 直写，-2=保持；dragonman/goblin_fox 读作窗口槽）〔证据: va=004D9790〕
    unsigned int     nPosWinY;        // +0x1DD4 (7636) x1  【推断】坐标窗口Y（与 +7632 成对直写，0x4D9790）〔证据: va=004D9790〕
    unsigned char _unused_1DD8[28]; // +0x1DD8..0x1DF3 未观测
    unsigned int     nSwitchGuardT;   // +0x1DF4 (7668) x1  【推断】关联切换保护窗（0x4D8F00 记 now+2000ms；读作时钟门）〔证据: va=004D8F00〕
    unsigned int     f_1DF8;          // +0x1DF8 (7672) x1  【保留占位】仅见复位（0x4DE700 写 -1 哨兵，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_1DFC;          // +0x1DFC (7676) x1  【保留占位】仅见复位（0x4DE700 写 -1 哨兵，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_1E00[8]; // +0x1E00..0x1E07 未观测
    unsigned int     f_1E08;          // +0x1E08 (7688) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_1E0C[16]; // +0x1E0C..0x1E1B 未观测
    unsigned int     nIdleStamp;      // +0x1E1C (7708) x1  【推断】发呆时刻戳（0x4D8A80 坐标变化刷新；1000ms 无位移触发 idle→切态21）〔证据: va=004D8A80〕
    unsigned int     f_1E20;          // +0x1E20 (7712) x1  【保留占位】仅见复位（0x4DE700 四连清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_1E24;          // +0x1E24 (7716) x1  【保留占位】仅见复位（0x4DE700 四连清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_1E28;          // +0x1E28 (7720) x1  【保留占位】仅见复位（0x4DE700 四连清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_1E2C[8]; // +0x1E2C..0x1E33 未观测
    unsigned int     f_1E34;          // +0x1E34 (7732) x1  【保留占位】仅见写（0x4DE700 尾写 200 门限初值，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_1E38[28]; // +0x1E38..0x1E53 未观测
    unsigned char    bTimerObj;       // +0x1E54 (7764) x1  【推断】计时/对象槽（equ_buff 存指针并经 getter 返回）〔证据: va=004DE700〕
    unsigned char _unused_1E55[3]; // +0x1E55..0x1E57 未观测
    unsigned int     pObj7768;        // +0x1E58 (7768) x1  【推断】对象/时值槽（equ_buff 经其虚表调用；hiteff PVP 场景时值 1000ms）〔证据: va=004DE700〕
    // ---- 区块: 反击态与文案类别表（0x4DB480 / 0x4DB130） ----
    unsigned int     nCounterState;   // +0x1E5C (7772) x2  va=004DB480 ★ 反击态（1/2 时 0x4DB480 走架招档位判定；与 +7529 标志联动）
    unsigned char    bPeerInit;       // +0x1E60 (7776) x1  【推断】关联对象首次初始化标志（0x4D8F00 读侧 ==0 → 置 1 并调 vt+1116）〔证据: va=004D8F00〕
    unsigned char _unused_1E61[24]; // +0x1E61..0x1E78 未观测
    unsigned char    bActiveRender;   // +0x1E79 (7801) x1  【推断】外观/激活门（读侧 ==1 走播放驱动；附着层判定族）〔证据: va=004DE700〕
    unsigned char _unused_1E7A[6]; // +0x1E7A..0x1E7F 未观测
    unsigned int     nMonCfgSel;      // +0x1E80 (7808) x2  va=004DE700 【推断】文案类别表特殊槽/资源选择枚举（0x4DE700 头注「骑乘/名牌/拾取族」）
    unsigned int     pCfgVecBegin;    // +0x1E84 (7812) x1  va=004DE700 文案类别表目录 vector begin（0x4DE700 后接 29×16 字节条目清理，0x4DB130 消费）【推断】
    unsigned int     pCfgVecEnd;      // +0x1E88 (7816) x1  va=004DE700 文案类别表目录 vector end
    unsigned int     pCfgVecCap;      // +0x1E8C (7820) x3  va=004DE700 文案类别表目录 vector cap（29 条 × 16 字节）
    // ---- 区块: 拾取/交互族（0x4DE700 / 0x4D94A0） ----
    unsigned char _unused_1E90[464]; // +0x1E90..0x205F 未观测
    unsigned int     nPickSlot;       // +0x2060 (8288) x1  【推断】拾取族 slot（0x4DE700 写 -1 哨兵；5F39F0 取址用）〔证据: va=004DE700〕
    unsigned int     f_2064;          // +0x2064 (8292) x1  【保留占位】仅见写（0x4DE700 写 1000 时限初值，无读侧消费点）〔证据: va=004DE700〕
    unsigned char    bVoiceDebounce;  // +0x2068 (8296) x1  va=004DE700 语音去抖字节（0x4E1780 条件 273 态进出时置/清，控制 25/26 号语音不重复播）
    unsigned char _unused_2069[3]; // +0x2069..0x206B 未观测
    unsigned int     pPickObj;        // +0x206C (8300) x1  va=004DE700 【推断】交互目标对象指针（0x4DE700 初值 -1）
    unsigned int     nPickPosX;       // +0x2070 (8304) x1  va=004DE700 拾取族坐标槽 X（0x5EA970 case 19 同区）【推断】
    unsigned int     nPickPosY;       // +0x2074 (8308) x1  va=004DE700 同上三元组 Y
    unsigned int     nPickPosZ;       // +0x2078 (8312) x1  va=004DE700 同上三元组 Z
    unsigned int     nPickDirSrc;     // +0x207C (8316) x1  va=004DE700 拾取朝向/源对象槽（同族读 +8316 经 sub_432E50 转换）【推断】
    unsigned int     pPickAnchor;     // +0x2080 (8320) x1  va=004DE700 【推断】锚定/宿主对象槽（同族收尾 *(this+8320) 调 vt+76(0)）
    unsigned int     f_2084;          // +0x2084 (8324) x1  【保留占位】仅见复位（0x4DE700 写 -1 哨兵，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_2088;          // +0x2088 (8328) x1  【保留占位】仅见复位（0x4DE700 写 -1 哨兵，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_208C;          // +0x208C (8332) x1  【保留占位】仅见复位（0x4DE700 写 -1 哨兵，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_2090[4]; // +0x2090..0x2093 未观测
    unsigned int     pMarkImg;        // +0x2094 (8340) x2  va=004DE700 【推断】飞行/召唤标记图槽（0x4DE700 头注：懒加载 Monster/FlyingMonsterMark.img 与 SummonMonsterMark.img）
    unsigned int     f_2098;          // +0x2098 (8344) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_209C;          // +0x209C (8348) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     nPickSrcPos;     // +0x20A0 (8352) x2  va=004D94A0 拾取/交互源坐标缓存（对象首字节非 0 时被写入 +668）【推断】
    unsigned int     pPickTarget;     // +0x20A4 (8356) x3  va=004D94A0 拾取目标对象指针（同族用后清零）
    unsigned int     pPickInfo;       // +0x20A8 (8360) x7  va=004D94A0 ★ 拾取信息块指针（7 字节=dword+word+byte；0x4D94A0 懒创建/释放）
    unsigned int     nPickCache;      // +0x20AC (8364) x2  【推断】拾取/坐标缓存槽（同族 vt+112(this,+8364,+8368,0) 读取）〔证据: va=004DE700〕
    unsigned char _unused_20B0[104]; // +0x20B0..0x2117 未观测
    unsigned int     f_2118;          // +0x2118 (8472) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_211C;          // +0x211C (8476) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    // ---- 区块: 随机区间与文案串族（0x4DE5E0） ----
    unsigned char _unused_2120[36]; // +0x2120..0x2143 未观测
    unsigned int     nRandLo;         // +0x2144 (8516) x1  va=004DE700 随机区间下界（0x4DE700 头注「随机区间」；0x4DE5E0 写 [a9,a10) 倒计时）
    unsigned int     nRandHi;         // +0x2148 (8520) x1  va=004DE700 随机区间上界
    unsigned char    bMonCfgFlag;     // +0x214C (8524) x1  va=004DE700 复位批标志字节（0x4DE700 置 1）
    unsigned char _unused_214D[3]; // +0x214D..0x214F 未观测
    size_t           szMonText;       // +0x2150 (8528) x1  va=004DE700 std::string 文案串起点（0x4DE700 经 sub_4015C0 构造/赋值；0x4DE5E0 由 a2 挂入）
    unsigned char _unused_2154[37]; // +0x2154..0x2178 未观测
    unsigned char    f_2179;          // +0x2179 (8569) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned char    f_217A;          // +0x217A (8570) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned char _unused_217B[13]; // +0x217B..0x2187 未观测
    unsigned int     f_2188;          // +0x2188 (8584) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
    unsigned int     f_218C;          // +0x218C (8588) x1  【保留占位】仅见复位（0x4DE700 清零，无读侧消费点）〔证据: va=004DE700〕
};
#pragma pack(pop)

// 统计: 字段行 89 / 未命名保留 20 / 标【推断】26 / 末尾偏移 +0x2190

#endif

// ============================================================
// 【40JP逆向源代码工程】game/hiteff_monster.cpp
// 模块: 命中特效/怪物状态机
// 来源: work/dump_misca.txt  区块: 0x4E0000-0x4F0000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 逐行精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 165
// ------------------------------------------------------------
// ★ 本文件是本工程"打击感/hit stop"链路的**主战场** —— 研究 20 定案锚点最密集的区块：
//   0x4E5DC0 表现壳（hit stop 施加点，研究 §3 全文定案）
//   0x4E88A0 HITEFF 通用命中特效生成器 vt+640（研究 §5.2 全文定案）
//   0x4E4710 攻方表现载荷（★ 双向卡肉，研究 §8 全文定案）
//   0x4E6770 伤害流水线 vt+628（研究 P14 九步公式）
//   0x4E7A80 受击反应 setState vt+560（研究 §1.2/§15 三层状态只升不降仲裁）
//   0x4E85E0 CRITHIT / 0x4E8770 UNIONHIT（研究 §5.3/§5.4）
//   0x4E5B50 暴击/有效命中判定（研究 §5.1）、0x4E9760 格挡特效 vt+644（研究 §3 格挡分支）
//   0x4E82B0 本地扫掠 vt+476（研究 §1.2/§11 第 11 轮）
//   0x4E4DE0 位置化动作 / 0x4E4F20 动作数据包（本工程会话 3 定案）
//   0x4E54D0 AABB 重叠 / 0x4E5560 动画盒重叠（已 L1 精修，见 src/cnrd/IRDCollisionObject.cpp）
//   0x4E62B0 攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）
//   0x4E4430 HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）
//   0x4E7160/0x4E73B0 出生/复活重置（研究 P35）
// ------------------------------------------------------------
// 交叉引用：已被 L1 逐行精修的重复函数（以 cnrd/ 版为准，此处保留 L2 转写体）：
//   0x4E5410/0x4E54D0/0x4E5560/0x4E57E0/0x4E5920 → src/cnrd/IRDCollisionObject.cpp:330/27/50/125/167
//   0x4E7040/0x4E7440/0x4E7480/0x4E8080 → src/cnrd/IRDCollisionObject.cpp:269/213/226/249
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 A】怪物状态机 / 行为定义族（0x4E0000 - 0x4E4430）
//   怪物大状态 tick、行为表驱动、无敌/受击盒门、动作队列。
//   研究依据：P35 第 31 轮（无敌开关 = this+641 受击盒使能，setter sub_4A2D70
//   向附属物广播 vt+604）；三层状态（this+200 主状态 / +616 反应态 +636 优先级 /
//   +6556 大状态）。
// ============================================================

// ------------------------------------------------------------
// 0x4E0000 sub_4E0000 —— 大状态行为表项应用（按 a2 索引取 32 字节记录 + 附加盒）
// this+1550/1551 = 行为 vector（4 字节 id 数组）；this+1905/1906 = 32 字节属性数组。
// 目标索引越界时先 sub_4DFF40 扩容（this+1904 为容量字段）。
// 属性记录经 vt+1216(表项, 行为id) 应用；若 this+1625 非空（有技能对象），
// 逐条 vt+248 取技能属性表（124 字节步距）→ 每项再 vt+1216 应用。
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0000(uint32_t *this, unsigned int uArg2)  // 实现：大状态行为表项应用（按 a2 索引取 32 字节记录 + 附加盒）
{
  int fld_e1550; // ecx
  int fld_e1905; // edx
  int fld_e15502; // edx
  unsigned int fld_e1551; // eax
  int fld_e1625; // ecx
  int pSkillTable; // eax
  int pRecCur; // ebx
  uint32_t *pVecCur; // edx
  int pVecBegin; // ecx
  int pContainer; // [esp+4h] [ebp-10h]
  uint32_t *pVecCurBak; // [esp+Ch] [ebp-8h]
  int pRecCurBak; // [esp+10h] [ebp-4h]

  fld_e1550 = *(this + 1550);  // this+6200〔pTbl6200〕
  if ( fld_e1550 != 0 && (*(this + 1551) - fld_e1550) >> 2 > uArg2 )  // 若 fld_e1550 != 0
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 || (*(this + 1906) - fld_e1905) >> 5 <= uArg2 )  // 若 fld_e1905 == 0
    {
      fld_e15502 = *(this + 1550);  // this+6200〔pTbl6200〕
      if ( fld_e15502 != 0 )  // 若 fld_e15502 非 0
        fld_e1551 = (*(this + 1551) - fld_e15502) >> 2;  // 向量元素数 = (end−begin)/4
      else  // 否则分支
        fld_e1551 = 0;
      sub_4DFF40(this + 1904, fld_e1551);  // 32B 属性数组不足 → 扩容到行为表长度
    }
    (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t))(*this + 1216))(  // 调虚槽 +1216：IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
      this,
      32 * uArg2 + *(this + 1905),  // this+7620〔pStatusPanel(推断)〕
      *(uint32_t *)(4 * uArg2 + *(this + 1550)));  // vt+1216(第 uArg2 个 32B 属性记录, 第 uArg2 个行为 id)
    fld_e1625 = *(this + 1625);  // 技能对象
    if ( fld_e1625 != 0 )  // 若 fld_e1625 非 0
    {
      pSkillTable = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 248))(fld_e1625);  // 技能属性表容器（基+4/尾+8，124B 步距）
      pRecCur = *(uint32_t *)(pSkillTable + 4);
      pContainer = pSkillTable;
      pRecCurBak = pRecCur;
      if ( pRecCur != *(uint32_t *)(pSkillTable + 8) )
      {
        pVecCur = (uint32_t *)(pRecCur + 44);  // 记录 +44 = 内嵌行为 id 向量头
        pVecCurBak = (uint32_t *)(pRecCur + 44);
        do  // do-while 循环体起点
        {
          pVecBegin = *pVecCur;
          if ( *pVecCur != 0 && (pVecCur[1] - pVecBegin) >> 2 > uArg2 )  // 复合条件判定（与/或）
          {
            (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t))(*this + 1216))(  // 调虚槽 +1216：IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
              this,
              32 * uArg2 + *(this + 1905),  // this+7620〔pStatusPanel(推断)〕
              *(uint32_t *)(pVecBegin + 4 * uArg2));  // 该技能的属性表也覆盖同一 32B 记录
            pRecCur = pRecCurBak;
            pVecCur = pVecCurBak;
          }
          pRecCur += 124;
          pVecCur += 31;
          pRecCurBak = pRecCur;
          pVecCurBak = pVecCur;
        }
        while ( pRecCur != *(uint32_t *)(pContainer + 8) );  // 条件循环
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E0120 sub_4E0120 —— 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
// 门链：vt+308(本地玩家对象) + ·this+1813 目标非空 + vt+840 非 0 + ·this+7148 != 24；
// 各分支按 ·sub_699000 时钟差 500/5000/10000ms 与朝向(vt+184/188)、记忆目标坐标(·this+1918/1919)转态，
// 统一经 vt+1104 写新态（1/4/8/9/10/13/24）；尾段 vt+212 播 ·this+1934 内联 std::string 文案
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0120(uint32_t *this)  // 实现：怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
{
  int fld_e1812; // eax
  double fClockDiff; // st7
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  bool bInWindow; // cc
  uint32_t *pThis_78E; // edi
  unsigned int fld_e1940; // eax
  uint32_t *pThis_78F; // eax
  unsigned int fld_e19402; // esi
  uint32_t *pStrHeap; // ecx
  uint32_t *pStrData; // edx
  int nNewState; // [esp-8h] [ebp-30h]
  void *pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  int v14; // [esp+18h] [ebp-10h] BYREF  // 局部打包结构尾槽（与 pBuf 相邻）
  int v15; // [esp+24h] [ebp-4h]  // 局部打包结构守卫槽

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0  // 调虚槽 +308：是否本地玩家
    || *(this + 1813) != 0  // this+7252〔pTarget7252〕
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0  // 调虚槽 +840：大状态 getter（this+6556）
    || *(this + 1787) == 24  // this+7148〔nBigState〕
    || (fld_e1812 = *(this + 1812)) == 0
    || (fClockDiff = (double)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, fld_e1812, 0),  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        (double)(v14 = sub_4D8FE0(this)) * 0.5 >= fClockDiff) )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
  {
    switch ( *(this + 1787) )  // 大状态 this+7148
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 2  // 调虚槽 +188：动画对象 z 倾斜转状态码
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) <= *(this + 1918)  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 3  // 调虚槽 +188：动画对象 z 倾斜转状态码
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) >= *(this + 1918) )  // 朝向 vt+184/188 与记忆目标坐标比对
          {
            memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
            v15 = 0;
            v14 = 0;
            sub_431230((int)pBuf, &v14);  // 【命中目标列表追加】
            (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // vt+560 受击反应 setState（行为 8）
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);  // vt+1104 写新态 1
            v15 = -1;
            sub_5E5260(pBuf);  // 释放打包缓冲
          }
        }
        else  // 否则分支
        {
          (*(void (/*stdcall*/ **)(int))(*this + 1104))(1);  // 调虚槽 +1104
        }
        break;  // 跳出循环/分支
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 0  // 调虚槽 +184：动画对象 z 倾斜转状态码
          && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= *(this + 1919)  // 调虚槽 +120：动画对象
          || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 1  // 调虚槽 +184：动画对象 z 倾斜转状态码
          && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= *(this + 1919) )  // 调虚槽 +120：动画对象
        {
          goto LABEL_14;
        }
        break;  // 跳出循环/分支
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        if ( sub_699000((int)(this + 1910)) - *(this + 1926) > 5000 )  // 【clock_now(clk)】与记忆目标失去联系 5s
        {
          if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
            goto LABEL_17;
          goto LABEL_48;
        }
        break;  // 跳出循环/分支
      case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      case 0xA:
        bInWindow = sub_699000((int)(this + 1910)) - *(this + 1926) <= 10000;  // 【clock_now(clk)】10s 记忆窗口
        goto LABEL_16;
      case 0xB:
        if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 0  // 调虚槽 +184：动画对象 z 倾斜转状态码
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= *(this + 1919)  // 调虚槽 +120：动画对象
            || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 1  // 调虚槽 +184：动画对象 z 倾斜转状态码
            && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= *(this + 1919) )  // 调虚槽 +120：动画对象
          {
            if ( sub_4DAB60(this, 10) )  // 行为 10 可用？
            {
              (*(void (/*stdcall*/ **)(int))(*this + 1104))(9);  // 调虚槽 +1104
            }
            else if ( sub_4DAB60(this, 11) )  // 标签/条件集合成员判定
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 10);  // 调虚槽 +1104
            }
          }
        }
        else  // 否则分支
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
        }
        break;  // 跳出循环/分支
      case 0xC:
        pTarget7252 = *(this + 1813);  // this+7252〔pTarget7252〕
        if ( pTarget7252 != 0 )  // 若 fld_e1813 非 0
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )  // vt+1244 目标仍有效？
          {
            if ( sub_4DAB60(this, 10) )  // 标签/条件集合成员判定
            {
              *(this + 1919) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252);  // 记忆目标坐标 y
              *(this + 1918) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 124))(pTarget7252);  // 记忆目标坐标 x
            }
            else if ( sub_4DAB60(this, 11) )  // 标签/条件集合成员判定
            {
LABEL_14:  // 标签 LABEL_14（跳转合流点）
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);  // 调虚槽 +1104
            }
          }
        }
        else  // 否则分支
        {
          bInWindow = sub_699000((int)(this + 1910)) - *(this + 1926) <= 5000;  // 【clock_now(clk)】5s 记忆窗口
LABEL_16:  // 标签 LABEL_16（跳转合流点）
          if ( !bInWindow )
          {
LABEL_17:  // 标签 LABEL_17（跳转合流点）
            nNewState = 13;
LABEL_18:  // 标签 LABEL_18（跳转合流点）
            (*(void (/*stdcall*/ **)(int))(*this + 1104))(nNewState);  // 调虚槽 +1104
          }
        }
        break;  // 跳出循环/分支
      case 0x15:
        if ( sub_699000((int)(this + 1910)) - *(this + 1926) <= 500 )  // 【clock_now(clk)】0.5s 抖动窗
          break;  // 跳出循环/分支
        nNewState = 4;
        if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
          goto LABEL_18;
LABEL_48:  // 标签 LABEL_48（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
    if ( *(this + 1939) != 0 && *(this + 1813) != 0 )  // 有内联文案且目标存在 → 播头顶气泡
    {
      pThis_78E = this + 1934;
      fld_e1940 = *(this + 1940);
      if ( *(this + 1943) == 3 )  // this+7772〔nCounterState〕
      {
        if ( fld_e1940 < 0x10 )  // SSO 内联（长度 < 16）
          sub_432EA0(this + 1935, -1, 0, 0);  // 音效播放包装（非空判定）
        else  // 否则分支
          sub_432EA0((void *)*(this + 1935), -1, 0, 0);  // 音效播放包装（非空判定）
      }
      else  // 否则分支
      {
        if ( fld_e1940 < 0x10 )  // 若 fld_e1940 < 0x10
          pThis_78F = this + 1935;
        else  // 否则分支
          pThis_78F = (uint32_t *)*(this + 1935);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_78F, -1, 0, 0);  // vt+212 播 TAG 音效/台词
      }
      fld_e19402 = *(this + 1940);
      pStrHeap = pThis_78E + 1;
      if ( fld_e19402 < 0x10 )  // 若 fld_e19402 < 0x10
        pStrData = pThis_78E + 1;
      else  // 否则分支
        pStrData = (uint32_t *)*pStrHeap;
      if ( fld_e19402 >= 0x10 )  // 若 fld_e19402 >= 0x10
        pStrHeap = (uint32_t *)*pStrHeap;
      sub_406D00(pThis_78E, &v14, (int)pStrHeap, (unsigned int)pStrData + pThis_78E[5]);  // std::string 构造（长度 = +20 字段）
    }
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 24);  // 调虚槽 +1104
  }
}


// ------------------------------------------------------------
// 0x4E0560 sub_4E0560 —— 行为/技能随机触发（冷却 3000ms + ±20% 抖动）
// 门：this+1550 行为 vector 非空 + ·this+1639(大状态)==0 + 距上次触发时刻 ·this+1817 已到（clock_now(this+1910 区)）；
// srand 后抖动 = ·this+1900 ± 20%，写回 ·this+1817 = 抖动 + now；
// 再遍历 ·this+1905 的 32 字节表（首字节使能）→ ·sub_4DB810 概率命中 → vt+560(this, 8, 打包索引) 触发行为 8
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0560(uint32_t *this)  // 实现：行为/技能随机触发（冷却 3000ms + ±20% 抖动）
{
  int fld_e1550; // ecx
  int fld_e1900; // ebx
  int nRand; // edi
  unsigned int i_rec; // edi
  int i; // ebx
  int fld_e1905; // ecx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v9[4]; // [esp+14h] [ebp-10h] BYREF

  fld_e1550 = *(this + 1550);  // this+6200〔pTbl6200〕
  if ( fld_e1550 != 0  // 若 fld_e1550 非 0
    && (*(this + 1551) - fld_e1550) >> 2 != 0  // 向量元素数 = (end−begin)/4
    && *(this + 1639) == 0  // this+6556〔大状态ID〕
    && sub_699000((int)(this + 1910)) >= 3000  // 【clock_now(clk)】冷却下限 3000ms
    && sub_699000((int)(this + 1910)) >= *(this + 1817) )  // 【clock_now(clk)】上次触发时刻已到
  {
    sub_432FA0();  // srand 播种
    fld_e1900 = (uint64_t)((double)(int)*(this + 1900) * 0.2);  // 抖动幅度 = 周期 × 20%
    nRand = *(this + 1900) + rand() % fld_e1900 - fld_e1900 / 2;  // 周期 ±20% 抖动
    *(this + 1817) = nRand + sub_699000((int)(this + 1910));  // clock_now(clk)
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 本地玩家对象门
    {
      i_rec = 0;
      v9[0] = 0;
      for ( i = 0; ; i += 32 )  // 遍历 32 字节行为记录表
      {
        fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
        if ( fld_e1905 == 0 || i_rec >= (*(this + 1906) - fld_e1905) >> 5 )  // 若 fld_e1905 == 0
          break;  // 跳出循环/分支
        if ( *(uint8_t *)(i + fld_e1905) != 0 && sub_4DB810(this, i_rec) )  // 首字节使能位 + 概率掷
        {
          v9[0] = i_rec;
          memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
          v9[3] = 0;
          sub_431230((int)pBuf, v9);  // 【命中目标列表追加】
          (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // vt+560 setState(8)
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return;
        }
        ++i_rec;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E06D0 sub_4E06D0 —— 目标/仇恨打分选择（100×同目标计数 + 距离，自减 50 惩罚）
// 场景对象(this+29) 的对象表 → 对条件 529 的对象取 vt+1032 → +28 作键计数（·sub_4BE520 查 + ·sub_42D430 取或建 + ++）；
// 打分 v22 = 100×计数 + 距离(vt+8)，与 ·this+1814(车主)/1813(当前目标) 相同者各减 50；取最小为新目标；
// 目标变更 → 发 ·dword_8F8520 包（type 6, 2 子字段：双方 vt+48/52）+ 写 ·this+1917 = now+2000 冷却
// ------------------------------------------------------------
void /*thiscall*/ sub_4E06D0(uint32_t *this)  // 实现：目标/仇恨打分选择（100×同目标计数 + 距离，自减 50 惩罚）
{
  int fld_e29; // eax
  int nSceneType; // eax
  int pTeamTable; // edi
  int i; // esi
  int pSquadObj; // eax
  int nKey; // eax
  int j; // esi
  int pSquadObj2; // eax
  int nKey2; // eax
  unsigned int k; // edi
  int pObjTable; // ecx
  int pObjCur; // edx
  int nObjCount; // eax
  int pObjCur2; // edx
  uint32_t *pEnemy; // esi
  void **pFound; // eax
  uint32_t *pCount; // eax
  int *pMapHead; // ecx
  int *pNode; // edi
  int pTarget; // esi
  int nDistScore; // ebx
  int nScore; // ebx
  int **pRight; // eax
  int *pSucc; // eax
  int *pSucc2; // eax
  int nTargetUid; // edi
  uint32_t *pThis2; // esi
  int nNow; // eax
  int pOldTarget; // ecx
  int pPacket; // ebx
  int nSelfUid; // eax
  int pPacket2; // ebx
  int nSelfUid2; // eax
  int *v34; // [esp-10h] [ebp-44h]
  int *v35; // [esp-10h] [ebp-44h]
  int v36; // [esp-10h] [ebp-44h]
  char v37[4]; // [esp+4h] [ebp-30h] BYREF
  void *Block; // [esp+8h] [ebp-2Ch]  // 【推断】红黑树哨兵/头节点（·sub_433AC0 建，+21 = 红黑着色字节）
  int v39; // [esp+Ch] [ebp-28h]
  char v40[4]; // [esp+10h] [ebp-24h] BYREF
  int pObj22; // [esp+14h] [ebp-20h]  // 当前最优目标对象
  int v42; // [esp+18h] [ebp-1Ch]  // 当前最优分
  int v43; // [esp+1Ch] [ebp-18h] BYREF
  int v44; // [esp+20h] [ebp-14h]  // 当前最优目标 uid
  uint32_t *pThis; // [esp+24h] [ebp-10h]
  int v46; // [esp+30h] [ebp-4h]

  fld_e29 = *(this + 29);  // this+116〔会话上下文〕
  pThis = this;
  if ( fld_e29 == 0 )  // 若 fld_e29 为 0
    return;
  v44 = -1;
  v42 = 0;
  pObj22 = 0;
  Block = (void *)sub_433AC0(v37);  // 建树哨兵（+21=1 着色、三指针自指）
  *((uint8_t *)Block + 21) = 1;  // Block[21] = 1
  *((uint32_t *)Block + 1) = Block;
  *(uint32_t *)Block = Block;
  *((uint32_t *)Block + 2) = Block;
  v39 = 0;
  nSceneType = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
  v46 = 0;
  if ( nSceneType == 4 && dword_99FEC0 != 0 )  // 场景 4 = 竞技场
  {
    pTeamTable = dword_99FEC0 + 4;
  }
  else  // 否则分支
  {
    if ( nSceneType != 6 || dword_99FF08 == 0 )  // 场景 6 = 战场
      goto LABEL_15;
    pTeamTable = dword_99FF08 + 4;
  }
  if ( pTeamTable != 0 )  // 若 pTeamTable 非 0
  {
    for ( i = 0; i < 8; ++i )  // 逐个小队（8 队）清空计数
    {
      pSquadObj = sub_48F660(i);  // 槽 id 解析（·sub_429830 查对象）
      if ( pSquadObj != 0 )  // 若 pSquadObj 非 0
      {
        nKey = *(uint32_t *)(pSquadObj + 196);
        if ( nKey != 0 )  // 若 nKey 非 0
        {
          v43 = nKey;
          *(uint32_t *)sub_42D430(&v43) = 0;  // map 取或建
        }
      }
    }
    goto LABEL_20;
  }
LABEL_15:  // 标签 LABEL_15（跳转合流点）
  for ( j = 16; j < 32; j += 4 )  // 兜底：全局怪物槽位表清空计数
  {
    pSquadObj2 = *(uint32_t *)(j + dword_8F850C);  // 房间/席位表
    if ( pSquadObj2 != 0 )  // 若 pSquadObj2 非 0
    {
      nKey2 = *(uint32_t *)(pSquadObj2 + 196);
      if ( nKey2 != 0 )  // 若 nKey2 非 0
      {
        v43 = nKey2;
        *(uint32_t *)sub_42D430(&v43) = 0;  // map 取或建
      }
    }
  }
LABEL_20:  // 标签 LABEL_20（跳转合流点）
  for ( k = 0; ; ++k )  // 遍历场景对象表，累计"条件 529 对象"的仇人计数
  {
    pObjTable = pThis[29];  // pObjTable = 取 pThis[29]
    pObjCur = *(uint32_t *)(pObjTable + 120);  // pObjTable+120〔pAnimObj〕
    nObjCount = pObjCur != 0 ? (*(uint32_t *)(pObjTable + 124) - pObjCur) >> 2 : 0;  // pObjTable+124〔pAuraAnim(推断)〕
    if ( (int)k >= nObjCount )
      break;  // 跳出循环/分支
    pObjCur2 = *(uint32_t *)(pObjTable + 120);  // pObjTable+120〔pAnimObj〕
    if ( pObjCur2 != 0 && k < (*(uint32_t *)(pObjTable + 124) - pObjCur2) >> 2 )  // 若 pObjCur2 != 0
      pEnemy = *(uint32_t **)(pObjCur2 + 4 * k);
    else  // 否则分支
      pEnemy = nullptr;  // pEnemy = 空指针
    if ( pEnemy != pThis && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pEnemy + 40))(pEnemy, 529) != 0 )  // 条件 529 = 敌对怪物
    {
      v43 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pEnemy + 1032))(pEnemy) + 28);  // +28 = 仇恨键（目标 id）
      if ( v43 != 0 )  // 若 v43 非 0
      {
        pFound = (void **)sub_4BE520(v40, &v43);  // 映射下界查找（lower_bound）
        if ( *pFound != Block )  // 键已存在（说明此前已计过一次）
        {
          pCount = (uint32_t *)sub_42D430(&v43);  // map 取或建
          ++*pCount;  // 同目标被打次数 +1
        }
      }
    }
  }
  pMapHead = (int *)Block;
  pNode = *(int **)Block;
  if ( *(void **)Block == Block )
    goto LABEL_63;
  do  // do-while 循环体起点
  {
    pTarget = pNode[3];  // 节点 +12 = 目标对象
    if ( (uint8_t)sub_45E680(pTarget) != 0 )  // 对象表归属判定
      nDistScore = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pThis + 8))(pThis, pTarget, 0);  // vt+8 = 距离
    else  // 否则分支
      nDistScore = 640;  // 取不到距离 → 惩罚常数
    if ( pTarget == pThis[1814] )
      nDistScore -= 50;  // 车主惩罚
    if ( pTarget == pThis[1813] )
      nDistScore -= 50;  // 当前目标惩罚
    nScore = 100 * pNode[4] + nDistScore;  // 100×同目标计数 + 距离
    if ( v44 == -1 || nScore < v42 )  // 若 v44 == -1 与/或 nScore < v42
    {
      v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 52))(pTarget);  // vt+52 = 对象 uid
      v42 = nScore;
      pObj22 = pTarget;
    }
    if ( *((uint8_t *)pNode + 21) == 0 )  // 红黑树中序后继（节点 +21 = 着色位）
    {
      pRight = (int **)pNode[2];
      if ( *((uint8_t *)pRight + 21) != 0 )
      {
        for ( pSucc = (int *)pNode[1]; *((uint8_t *)pSucc + 21) == 0; pSucc = (int *)pSucc[1] )  // 遍历循环
        {
          if ( pNode != (int *)pSucc[2] )
            break;  // 跳出循环/分支
          pNode = pSucc;
        }
        pNode = pSucc;
      }
      else  // 否则分支
      {
        pNode = (int *)pNode[2];
        for ( pSucc2 = *pRight; *((uint8_t *)pSucc2 + 21) == 0; pSucc2 = (int *)*pSucc2 )  // 遍历循环
          pNode = pSucc2;
      }
    }
  }
  while ( pNode != Block );  // 条件循环
  nTargetUid = v44;
  if ( v44 == -1 || pObj22 == 0 )  // 若 v44 == -1 与/或 pObj22 == 0
  {
    pMapHead = (int *)Block;
LABEL_63:  // 标签 LABEL_63（跳转合流点）
    v36 = *pMapHead;
    v46 = -1;
    sub_41DA40(v40, v36, pMapHead);  // 同族实例二（回调 0x41CAA0）
    j__free(Block);
    return;
  }
  pThis2 = pThis;
  nNow = sub_699000((int)(pThis + 2));  // 【clock_now(clk)】
  pOldTarget = pThis2[1815];  // pOldTarget = 取 pThis2[1815]
  pThis2[1917] = nNow + 2000;  // 目标重选冷却 2000ms
  if ( pOldTarget != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pOldTarget + 52))(pOldTarget) == nTargetUid )  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  {
    v34 = *(int **)Block;
    v46 = -1;
    sub_41DA40(v40, v34, Block);  // 同族实例二（回调 0x41CAA0）
    j__free(Block);
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 6, 2);  // 目标变更包 type 6 / 2 子字段
    pPacket = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfUid = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis2 + 48))(pThis2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(pPacket + 36))(dword_8F8520, nSelfUid);  // 会话/UDP 管理器
    pPacket2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfUid2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis2 + 52))(pThis2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(pPacket2 + 36))(dword_8F8520, nSelfUid2);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nTargetUid);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    v35 = *(int **)Block;
    v46 = -1;
    sub_41DA40(v40, v35, Block);  // 同族实例二（回调 0x41CAA0）
    j__free(Block);
  }
}


// ------------------------------------------------------------
// 0x4E0A40 sub_4E0A40 —— 敌对怪物名单收集（追加进 8 字节/条容器）
// 遍历场景对象表：条件 17(怪物) + ·sub_4E4630(敌我判定) + ·sub_4E5CA0(非 200..204 阵营) + vt+1244(归属门) 全通过
// → ·sub_4DFF90(v13) 追加；a2/a3 为输出容器首尾（8 字节/条，this+4/+8/+12 三字段）
// ------------------------------------------------------------
void /*thiscall*/ sub_4E0A40(uint32_t *this, int nArg2, int nArg3)  // 实现：敌对怪物名单收集（追加进 8 字节/条容器）
{
  unsigned int k_obj; // edi
  int fld_e29; // ecx
  int pObjTable; // edx
  int nObjCount; // eax
  int pObjCur; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int pObjCur2; // edx
  int pObj2; // esi
  uint32_t v13[11]; // [esp+1Ch] [ebp-2Ch] BYREF  // 待追加条目 {+0=对象, +4=0}（11 槽栈缓冲）

  k_obj = 0;
  v13[3] = this;
  v13[5] = 0;
  v13[4] = 0;
  v13[2] = 1;
  v13[10] = 0;
  while ( 1 )  // 条件循环
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    pObjTable = *(uint32_t *)(fld_e29 + 120);
    nObjCount = pObjTable != 0 ? (*(uint32_t *)(fld_e29 + 124) - pObjTable) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)k_obj >= nObjCount )
      break;  // 跳出循环/分支
    pObjCur = *(uint32_t *)(fld_e29 + 120);
    if ( pObjCur != 0 && k_obj < (*(uint32_t *)(fld_e29 + 124) - pObjCur) >> 2 )  // 若 pObjCur != 0
      pObj = *(uint32_t *)(pObjCur + 4 * k_obj);
    else  // 否则分支
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )  // 条件 17 = 怪物
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      pObjCur2 = *(uint32_t *)(fld_e292 + 120);
      if ( pObjCur2 != 0 && k_obj < (*(uint32_t *)(fld_e292 + 124) - pObjCur2) >> 2 )  // 若 pObjCur2 != 0
        pObj2 = *(uint32_t *)(pObjCur2 + 4 * k_obj);
      else  // 否则分支
        pObj2 = 0;
      if ( (uint8_t)sub_4E4630(pObj2) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        && (uint8_t)sub_4E5CA0(pObj2) == 0  // 排除阵营 200..204
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2) != 0 )  // 归属门
      {
        v13[0] = pObj2;
        v13[1] = 0;  // 8 字节/条
        sub_4DFF90(v13);  // 追加
      }
    }
    ++k_obj;
  }
}


// ------------------------------------------------------------
// 0x4E0CD0 sub_4E0CD0 —— 按条件号收集对象（阵营/距离/归属过滤，返回计数）
// 遍历场景对象表的另一向量(+8/+12)：匹配 vt+40(条件 nArg2) 且非自身；
// pszArg3==1 要求 vt+376(阵营) 相同、==0 要求 ·sub_4E4630 为敌；再排除 ·sub_4E5CA0(200..204)，
// nArg5==-1 要求 vt+1244 归属门成立、否则距离 vt+8 <= nArg5；排除条件17 且死亡/免疫态(vt+940/vt+724)；nArg4!=0 → ·sub_428430 追加
// ------------------------------------------------------------
int /*thiscall*/ sub_4E0CD0(uint32_t *this, int nArg2, char pszArg3, int nArg4, int nArg5)  // 实现：按条件号收集对象（阵营/距离/归属过滤，返回计数）
{
  uint32_t *pThis; // ebx
  unsigned int k_obj; // edi
  int pObjTable; // ecx
  int pVecBegin; // edx
  int nObjCount; // eax
  int pVecBegin2; // edx
  int pObj2; // ecx
  int pObjTable2; // eax
  int pVecBegin3; // edx
  uint32_t *pObjCur; // ecx
  int pVecBegin4; // edx
  int pObj; // esi
  int nOwnFaction; // ebx
  bool bFactionSame; // zf
  int pObjOut; // [esp+10h] [ebp-8h] BYREF
  int nMatchCount; // [esp+14h] [ebp-4h]

  pThis = this;
  k_obj = 0;
  nMatchCount = 0;
  while ( 1 )  // 条件循环
  {
    pObjTable = pThis[29];  // pObjTable = 取 pThis[29]
    pVecBegin = *(uint32_t *)(pObjTable + 8);  // pObjTable+8〔nSkillRec8(推断)〕
    nObjCount = pVecBegin != 0 ? (*(uint32_t *)(pObjTable + 12) - pVecBegin) >> 2 : 0;  // pObjTable+12〔nSkillRec12(推断)〕
    if ( (int)k_obj >= nObjCount )
      return nMatchCount;
    pVecBegin2 = *(uint32_t *)(pObjTable + 8);  // pObjTable+8〔nSkillRec8(推断)〕
    if ( pVecBegin2 != 0 && k_obj < (*(uint32_t *)(pObjTable + 12) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
      pObj2 = *(uint32_t *)(pVecBegin2 + 4 * k_obj);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, nArg2) != 0 )  // vt+40(条件 nArg2) 匹配
    {
      pObjTable2 = pThis[29];  // pObjTable2 = 取 pThis[29]
      pVecBegin3 = *(uint32_t *)(pObjTable2 + 8);  // pObjTable2+8〔nSkillRec8(推断)〕
      if ( pVecBegin3 != 0 && k_obj < (*(uint32_t *)(pObjTable2 + 12) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
        pObjCur = *(uint32_t **)(pVecBegin3 + 4 * k_obj);
      else  // 否则分支
        pObjCur = nullptr;  // pObjCur = 空指针
      if ( pObjCur != pThis )  // 排除自身
      {
        pVecBegin4 = *(uint32_t *)(pObjTable2 + 8);  // pObjTable2+8〔nSkillRec8(推断)〕
        if ( pVecBegin4 != 0 && k_obj < (*(uint32_t *)(pObjTable2 + 12) - pVecBegin4) >> 2 )  // 若 pVecBegin4 != 0
          pObj = *(uint32_t *)(pVecBegin4 + 4 * k_obj);
        else  // 否则分支
          pObj = 0;
        pObjOut = pObj;
        if ( pszArg3 == 1 )  // 组队/同阵营模式：要求 vt+376 阵营号相同
        {
          nOwnFaction = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);  // 调虚槽 +376：坐标同步包（type 37）
          bFactionSame = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj) == nOwnFaction;  // 调虚槽 +376：坐标同步包（type 37）
          pThis = this;
          if ( !bFactionSame )
            goto LABEL_35;
        }
        else if ( pszArg3 == 0 && (uint8_t)sub_4E4630(pObj) == 0 )  // 敌对模式
        {
          goto LABEL_35;
        }
        if ( (uint8_t)sub_4E5CA0(pObj) != 0 )  // 排除阵营 200..204
          goto LABEL_35;
        if ( nArg5 == -1 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis + 1244))(pThis, pObj) == 0 )  // 归属门
            goto LABEL_35;
        }
        else if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pThis + 8))(pThis, pObj, 0) > nArg5 )  // 距离门
        {
          goto LABEL_35;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) != 1  // 非死亡
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )  // 且非无敌
        {
          ++nMatchCount;
          if ( nArg4 != 0 )  // 若 nArg4 非 0
            sub_428430(&pObjOut);  // 追加到输出容器
        }
      }
    }
LABEL_35:  // 标签 LABEL_35（跳转合流点）
    ++k_obj;
  }
}



// ------------------------------------------------------------
// 0x4E0E30 sub_4E0E30 —— 精怪攻击发起（目标打分后 vt+140 发布动作 id 100）
// 门：a2 非空 + 车主 vt+576 条件 17 + this vt+308 + ·this+7148 不在 {12,7} + 距离 vt+8 >= 150；srand(坐标和)；
// 目标：·sub_4DC920(等级)/·sub_4DCAB0(HP)/·sub_4E0A40(名单) 收集后 ·sub_4DCCB0 仇恨比较（自身 v43 <= v42 才继续）；
// 坐标按标签 12/13/14/15 加随机/浮空偏移 → vt+140(…,100,…) 发布攻击动作；写 ·this+1918/1919 目标坐标 + vt+1104 写态 12
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E0E30(int *this, int nArg2)  // 实现：精怪攻击发起（目标打分后 vt+140 发布动作 id 100）
{
  int pOwner; // eax
  int nBigState; // eax  | +0x1BEC → ★大状态 ID（CNGhoulOilSellerOlrek；va=004DB480）
  int pVt; // ebx
  int pTarget; // eax
  int nSelfCoordSum; // ebx
  int nSelfX; // ebx
  int nSelfUid; // eax
  int fld_e1891; // eax  | +0x1D8C → uForm7564〔族字典〕（族字典）
  int pTargetOwner; // eax
  int pTarget2; // edi
  int nTargetX; // ebx
  int v14; // eax
  int nAbsY; // ebx
  int nAbsX; // ebx
  int nTargetX2; // eax
  int nTargetX3; // eax
  int nSelfCoordSum2; // ebx
  int nSelfUid2; // eax
  int nTgtCoord; // edx
  int v22; // ebx
  int nSelfCoordSum3; // ebx
  int nSelfUid3; // eax
  bool bEven; // zf
  signed int nRand; // eax
  int v27; // eax
  bool bEven2; // zf
  signed int nRand2; // eax
  int nRand3; // edx
  int pVt2; // eax
  int v32; // edx
  int pVt3; // edi
  int pTarget3; // eax
  int v36; // [esp+Ch] [ebp-28h] BYREF  // 仇恨输入包（等级/HP/名单 分组输出）
  int v37; // [esp+10h] [ebp-24h] BYREF
  int v38; // [esp+14h] [ebp-20h] BYREF
  int v39; // [esp+18h] [ebp-1Ch] BYREF
  int v40; // [esp+1Ch] [ebp-18h] BYREF
  int v41; // [esp+20h] [ebp-14h] BYREF
  int v42; // [esp+24h] [ebp-10h] BYREF  // 目标仇恨分
  int v43; // [esp+28h] [ebp-Ch] BYREF  // 自身仇恨分
  int v44; // [esp+2Ch] [ebp-8h] BYREF  // 发布坐标 x
  int v45; // [esp+30h] [ebp-4h] BYREF  // 发布坐标 y

  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )  // 调虚槽 +576
  {
    pOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwner + 40))(pOwner, 17) != 0  // 车主是怪物
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      nBigState = *(this + 1787);  // this+7148〔nBigState〕
      if ( nBigState != 12 && nBigState != 7 )  // 大状态不在攻击/受击式
      {
        pVt = *this;
        pTarget = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 576))(nArg2, 0);  // 调虚槽 +576
        if ( (*(int (/*thiscall*/ **)(int *, int))(pVt + 8))(this, pTarget) >= 150 )  // 距离 >= 150 才出手
        {
          nSelfX = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          nSelfCoordSum = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + nSelfX;  // 调虚槽 +120：动画对象
          nSelfUid = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
          srand(nSelfUid + nSelfCoordSum);  // 以自身 uid+坐标和为种子
          if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
            goto LABEL_16;
          fld_e1891 = *(this + 1891);  // this+7564〔uForm7564(推断)〕
          v37 = 0;
          v38 = 0;
          v39 = 0;
          v40 = 0;
          v43 = 0;
          v42 = 0;
          v36 = 0;
          v41 = 0;
          if ( fld_e1891 != 0 )  // 若 fld_e1891 非 0
            sub_4DC920(this, &v36, &v37);  // 收集等级信息
          if ( *(this + 1892) != 0 )  // this+7568〔uEnable7568(推断)〕
            sub_4DCAB0(this, &v38, &v39);  // 收集 HP 信息
          if ( *(this + 1893) != 0 )  // this+7572〔uGrade7572(推断)〕
            sub_4E0A40(this, &v40, &v41);  // 收集敌对名单
          sub_4DCCB0(this, (int)&v43, *(this + 1813), COERCE_FLOAT(&v36));  // 当前目标仇恨分
          pTargetOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
          sub_4DCCB0(this, (int)&v42, pTargetOwner, COERCE_FLOAT(&v36));  // 挑起者仇恨分
          if ( v43 <= v42 )  // 只是挑衅者、并非仇人 → 照打
          {
LABEL_16:  // 标签 LABEL_16（跳转合流点）
            pTarget2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
            nTargetX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2);  // 调虚槽 +120：动画对象
            v42 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < nTargetX;  // 自身 x 小于目标 x？（决定随机偏移方向）
            if ( sub_4DAB60(this, 12) || sub_4DAB60(this, 13) )  // 行为 12/13：带随机抖动的位
            {
              nAbsY = 10 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
              v42 = (int)abs32(nAbsY + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2)) / 2;  // 抖动幅度 = |Δy|/2
              v43 = 1;
              if ( v42 / 2 >= 1 )
                v43 = v42 / 2;
              nTargetX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2);  // 调虚槽 +120：动画对象
              pVt2 = *this;
              v44 = nTargetX2;
              nSelfCoordSum2 = (*(int (/*thiscall*/ **)(int *))(pVt2 + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
              nSelfCoordSum3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + nSelfCoordSum2;  // 调虚槽 +120：动画对象
              nSelfUid2 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
              srand(nSelfUid2 + nSelfCoordSum3);  // 重新播种（局部随机）
              nRand = rand() & 0x80000001;  // 取随机奇偶
              bEven = nRand == 0;
              if ( nRand < 0 )  // 若 nRand < 0
                bEven = (((uint8_t)nRand - 1) | 0xFFFFFFFE) == -1;
              v27 = v42;
              if ( bEven )
                v27 = -v42;
              v44 += v27;  // x ± 抖动
              v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 124))(pTarget2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
              nRand2 = rand() & 0x80000001;  // nRand2 = 调 rand
              bEven2 = nRand2 == 0;
              if ( nRand2 < 0 )  // 若 nRand2 < 0
                bEven2 = (((uint8_t)nRand2 - 1) | 0xFFFFFFFE) == -1;
              if ( bEven2 )
                nRand3 = -(rand() % v43);  // nRand3 = 调 -
              else  // 否则分支
                nRand3 = rand() % v43;  // nRand3 = 调 rand
              v14 = nRand3 + v45;  // y ± 抖动
            }
            else if ( sub_4DAB60(this, 14) )  // 行为 14：原地
            {
              v44 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2);  // 调虚槽 +120：动画对象
              v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 124))(pTarget2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            }
            else  // 否则分支
            {
              if ( !sub_4DAB60(this, 15) )  // 行为 15：贴身高/低位偏移
              {
LABEL_40:  // 标签 LABEL_40（跳转合流点）
                (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, uint32_t, int))(*this + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
                  this,
                  &v44,
                  &v45,
                  v44,
                  v45,
                  100,  // 动作 id 100 = 攻击
                  0,
                  1);
                nTgtCoord = v45;
                *(this + 1919) = v44;  // this+7676〔f_1DFC〕
                v32 = *this;
                *(this + 1918) = nTgtCoord;  // this+7672〔f_1DF8〕
                (*(void (/*thiscall*/ **)(int *, int))(v32 + 1104))(this, 12);  // vt+1104 写态 12
                pVt3 = *this;
                pTarget3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
                return (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt3 + 1244))(this, pTarget3) != 0;
              }
              nAbsX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2);  // 调虚槽 +120：动画对象
              v16 = (int)abs32(nAbsX - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) / 5;  // 调虚槽 +120：动画对象
              nTargetX3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 120))(pTarget2);  // 调虚槽 +120：动画对象
              if ( v42 != 0 )  // 若 v42 非 0
                v18 = nTargetX3 - v16;
              else  // 否则分支
                v18 = v16 + nTargetX3;
              v44 = v18;
              v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 124))(pTarget2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget2 + 124))(pTarget2) <= 230 )  // 230 = 高度分界
                v14 = v45 + 50;
              else  // 否则分支
                v14 = v45 - 50;
            }
            v45 = v14;
            goto LABEL_40;
          }
        }
      }
    }
  }
  return false;
}


// ------------------------------------------------------------
// 0x4E11A0 sub_4E11A0 —— 同族(条件 529)对象动作广播（发包 type 29，1..4 次）
// ·sub_4E0CD0(529,1,…) 取同族列表，重试次数 v26 = ·dword_99FB8C+1（1..4），跳过 ·this+7148==12 者；
// 对方 vt+308 本地玩家对象 → vt+1136(nArg1) 直调；否则 vt+304 非空 → 发 ·dword_8F8520 包
// （type 29, 2 子字段：自身 vt+48/52、vt+304 的 vt+52、常量 12、nArg1 车主 vt+576 的 vt+48/52）
// ------------------------------------------------------------
void /*stdcall*/ sub_4E11A0(int nArg1)  // 实现：同族(条件 529)对象动作广播（发包 type 29，1..4 次）
{
  unsigned int v1; // edi
  uint32_t *Block2; // ebx
  unsigned int v3; // edx
  uint32_t *v4; // ecx
  char v5; // al
  int pObj2; // ecx
  int pObj; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int pObj3; // eax
  int v13; // ebx
  int v14; // eax
  int pObj5; // eax
  int v16; // ebx
  int v17; // eax
  int pObj4; // eax
  int v19; // ebx
  int v20; // eax
  uint8_t v21[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v23; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  unsigned int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int v27; // [esp+28h] [ebp-4h]

  v1 = 0;
  Block = nullptr;  // Block = 空指针
  v23 = 0;
  v24 = 0;
  v27 = 0;
  sub_4E0CD0(529, 1, v21, -1);  // 按条件号收集对象（阵营/距离/归属过滤，返回计数）
  Block2 = Block;
  if ( Block != nullptr )  // 若 Block 有效（非空）
  {
    v3 = (v23 - (int)Block) >> 2;
    v25 = v3;
    if ( v3 != 0 )  // 若 v3 非 0
    {
      v26 = 0;
      switch ( dword_99FB8C )  // 按 dword_99FB8C 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          v26 = 1;
          break;  // 跳出循环/分支
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          v26 = 2;
          break;  // 跳出循环/分支
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          v26 = 3;
          break;  // 跳出循环/分支
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          v26 = 4;
          break;  // 跳出循环/分支
        default:  // 默认分支
          goto LABEL_8;
      }
      while ( 1 )  // 条件循环
      {
LABEL_8:  // 标签 LABEL_8（跳转合流点）
        if ( v1 >= v3 )  // 若 v1 >= v3
          goto LABEL_17;
        v4 = (uint32_t *)Block2[v1];
        if ( v4[1787] != 12 )
          break;  // 跳出循环/分支
LABEL_16:  // 标签 LABEL_16（跳转合流点）
        ++v1;
      }
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 308))(v4);  // 调虚槽 +308：是否本地玩家
      pObj2 = Block2[v1];  // pObj2 = 取 Block2[v1]
      if ( v5 != 0 )  // 若 v5 非 0
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1136))(pObj2, nArg1);  // 调虚槽 +1136
      }
      else  // 否则分支
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 304))(pObj2) == 0 )  // 调虚槽 +304：是否本地玩家
        {
LABEL_15:  // 标签 LABEL_15（跳转合流点）
          v3 = v25;
          goto LABEL_16;
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        pObj = Block2[v1];  // pObj = 取 Block2[v1]
        v8 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);  // 会话/UDP 管理器
        v10 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v11 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v1) + 52))(*((uint32_t *)Block + v1));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
        (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);  // 会话/UDP 管理器
        pObj3 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v1) + 304))(*((uint32_t *)Block + v1));  // 调虚槽 +304：是否本地玩家
        v13 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);  // 会话/UDP 管理器
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 12);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
        pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 576))(nArg1);  // 调虚槽 +576
        v16 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 48))(pObj5);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);  // 会话/UDP 管理器
        pObj4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 576))(nArg1);  // 调虚槽 +576
        v19 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 52))(pObj4);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);  // 会话/UDP 管理器
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        Block2 = Block;
      }
      if ( --v26 == 0 )
        goto LABEL_17;
      goto LABEL_15;
    }
LABEL_17:  // 标签 LABEL_17（跳转合流点）
    j__free(Block2);
  }
}


// ------------------------------------------------------------
// 0x4E1390 sub_4E1390 —— 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
// 门 ·this+7772(word 1943) 为 1 或 2；遍历 ·this+1951 的 4 字节 id 池：BYTE1 = 255/254/253 前缀匹配即返回，全等去重；
// 否则按 BYTE2(uArg2) 消耗 ·dword_6F89AC 配额（*uArg3 >= 配额才通过）→ 追加 id 并扣减 *uArg3；
// 命中即 ·sub_422E70(低字节+1256) 取文本 → ·off_77F3FC(byte_6F929C,文本,低字节) 打印
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1390(int *this, uint32_t *uArg2, uint32_t *uArg3)  // 实现：条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
{
  int *pThis; // edi
  int result; // eax
  unsigned int v5; // esi
  uint32_t *pThis_79F; // ecx
  int v7; // edx
  uint32_t *uArg32; // edi
  int v9; // esi
  unsigned int v10; // edx
  uint32_t *uArg22; // eax
  int v12; // eax

  pThis = this;
  result = *(this + 1943);  // this+7772〔nCounterState〕
  if ( result == 1 || result == 2 )  // 若 result == 1 与/或 result == 2
  {
    v5 = 0;
    pThis_79F = this + 1951;
    while ( 1 )  // 条件循环
    {
      v7 = pThis_79F[1];  // v7 = 取 pThis_79F[1]
      if ( v7 == 0 || v5 >= (pThis_79F[2] - v7) >> 2 )  // 若 v7 == 0
        break;  // 跳出循环/分支
      result = (uint8_t)BYTE1(*(uint32_t *)(pThis[1952] + 4 * v5));
      if ( result == 255 && ((uint16_t)uArg2 & 0xFF00) == 0xFF00 )  // 若 result == 255
        return result;
      if ( result == 254 && ((uint16_t)uArg2 & 0xFF00) == 0xFE00 )  // 若 result == 254
        return result;
      if ( result == 253 )  // 若 result == 253
      {
        result = (uint16_t)uArg2 & 0xFF00;  // 位掩码测试 &0xFF00（位 8,9,10,11,12,13,）
        if ( result == 64768 )  // 若 result == 64768
          return result;
      }
      if ( *(uint32_t **)(pThis[1952] + 4 * v5) == uArg2 )
        return result;
      pThis = this;
      ++v5;
    }
    result = BYTE2(uArg2);  // result = 调 BYTE2
    uArg32 = uArg3;
    if ( *uArg3 >= dword_6F89AC[BYTE2(uArg2)] )
    {
      v9 = pThis_79F[1];  // v9 = 取 pThis_79F[1]
      uArg3 = uArg2;
      if ( v9 != 0 )  // 若 v9 非 0
        v10 = (pThis_79F[2] - v9) >> 2;  // 向量元素数 = (end−begin)/4
      else  // 否则分支
        v10 = 0;
      if ( v9 != 0 && v10 < (pThis_79F[3] - v9) >> 2 )  // 若 v9 != 0
      {
        uArg22 = (uint32_t *)pThis_79F[2];
        *uArg22 = uArg2;
        pThis_79F[2] = uArg22 + 1;
      }
      else  // 否则分支
      {
        sub_430C80((void *)pThis_79F[2], 1, (int)&uArg3);  // uint32 vector 区间插入（同值填充）
      }
      *uArg32 -= dword_6F89AC[BYTE2(uArg2)];
      v12 = sub_422E70((uint8_t)uArg2 + 1256);  // v12 = 调 sub_422E70 返回值
      return off_77F3FC((char *)&byte_6F929C, v12, (uint8_t)uArg2);  // 返回 调 off_77F3FC
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E14E0 sub_4E14E0 —— 随机抽样追加（上限 13500 次，附排除值表）
// 从 ·dword_6F8940 的 27 项表取 rand()%27 → 跳过 131091/65281/130816 与 261641..261644、196612..196615 等特定值，
// 其余交 ·0x4E1390 追加；循环上限 v4 = 13500，剩余配额不足 2 即退出
// ------------------------------------------------------------
void /*thiscall*/ sub_4E14E0(int *this, int nArg2, int *pDwArg3)  // 实现：随机抽样追加（上限 13500 次，附排除值表）
{
  int v4; // edi
  int nRand; // edx

  v4 = 13500;
  while ( *pDwArg3 >= 2 )  // 条件循环
  {
    nRand = dword_6F8940[rand() % 27];  // nRand = 取 dword_6F8940[rand() % 27]
    if ( nRand > 131091 )  // 若 nRand > 131091
    {
      if ( nRand <= 261644 && (nRand >= 261641 || nRand >= 196612 && nRand <= 196615) )  // 若 nRand <= 261644 与/或 nRand >= 261641 与/或 nRand >= 196612
        goto LABEL_13;
    }
    else if ( nRand == 131091 || nRand == 65281 || nRand == 130816 )
    {
      goto LABEL_13;
    }
    sub_4E1390(this, (uint32_t *)nRand, pDwArg3);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
LABEL_13:  // 标签 LABEL_13（跳转合流点）
    if ( --v4 <= 0 )
      return;
  }
}



// ------------------------------------------------------------
// 0x4E1560 sub_4E1560 —— 遍历 id 列表逐个追加（uArg3 为配额槽）
// 对 pArg2 的 4 字节 vector 逐元素调 ·0x4E1390；返回末次结果
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E1560(int *this, int pArg2, uint32_t *uArg3)  // 实现：遍历 id 列表逐个追加（uArg3 为配额槽）
{
  unsigned int i; // esi
  int v5; // ecx
  unsigned int result; // eax

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    v5 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v5 == 0 )  // 若 v5 为 0
      break;  // 跳出循环/分支
    result = (*(uint32_t *)(pArg2 + 8) - v5) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
    if ( i >= result )  // 若 i >= result
      break;  // 跳出循环/分支
    result = sub_4E1390(this, *(uint32_t **)(v5 + 4 * i), uArg3);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E15A0 sub_4E15A0 —— 概率触发技能（·this+2118 概率 / ·this+2119 技能索引）
// 门 vt+308 + vt+840==0 + rand()%100 < ·this+2118；取 ·this+1905 表第 ·this+2119 项（条目首字节==1 使能）；
// 阈值 v13 = 条目+16：当前目标 ·this+1813 的距离 vt+8 < v13 则取目标本身，否则 ·0x4E0CD0(条件17,…) 收集后随机取一；
// 按 x 大小 vt+144(0/1) 设朝向 → 追加索引 ·this+2119 → vt+560(this, 8, 打包) 触发行为 8
// ------------------------------------------------------------
void /*userpurge*/ sub_4E15A0(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 实现：概率触发技能（·this+2118 概率 / ·this+2119 技能索引）
{
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // edi
  int v12; // edx
  int v13; // edi
  int v14; // eax
  int nRand; // ebx
  unsigned int v16; // edi
  int v17; // ebx
  void *v20; // [esp+4h] [ebp-1Ch] BYREF
  int v21; // [esp+8h] [ebp-18h]
  int v22; // [esp+Ch] [ebp-14h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 0  // 调虚槽 +840：大状态 getter（this+6556）
    && rand() % 100 < pArg1[2118] )  // rand()%100 取模随机
  {
    v5 = pArg1[1905];  // v5 = 取 pArg1[1905]
    v6 = v5 != 0 ? (pArg1[1906] - v5) >> 5 : 0;
    if ( pArg1[2119] < v6 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 688))(pArg1);  // 调虚槽 +688：附加块基址 this+6160
      v8 = *(uint32_t *)(v7 + 40);
      v9 = v7 + 36;
      v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      v11 = pArg1[2119];  // v11 = 取 pArg1[2119]
      if ( v11 < v10 && *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 688))(pArg1) + 40) + 4 * v11) != 0 )  // 调虚槽 +688：附加块基址 this+6160
      {
        v12 = pArg1[1905];  // v12 = 取 pArg1[1905]
        if ( *(uint8_t *)(v12 + 32 * pArg1[2119]) == 1 )
        {
          v13 = *(uint32_t *)(32 * pArg1[2119] + v12 + 16);
          v14 = pArg1[1813];  // v14 = 取 pArg1[1813]
          nRand = 0;
          if ( v14 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, v14, 0) < v13 )  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
          {
            nRand = pArg1[1813];  // nRand = 取 pArg1[1813]
          }
          else  // 否则分支
          {
            v21 = 0;
            v22 = 0;
            v23 = 0;
            v24 = 0;
            sub_4E0CD0(pArg1, 17, 0, (int)&v20, v13);  // 按条件号收集对象（阵营/距离/归属过滤，返回计数）
            if ( v21 != 0 )  // 若 v21 非 0
            {
              v16 = (v22 - v21) >> 2;  // 向量元素数 = (end−begin)/4
              if ( v16 != 0 )  // 若 v16 非 0
              {
                sub_432FA0();  // srand 播种
                nRand = *(uint32_t *)(v21 + 4 * (rand() % v16));
              }
            }
            v24 = -1;
            sub_5E5260(&v20);  // 调 动画子对象清理临时缓冲
          }
          if ( nRand != 0 )  // 若 nRand 非 0
          {
            v17 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)nRand + 120))(nRand, nArg2, nArg3);  // 调虚槽 +120：动画对象
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) >= v17 )  // 调虚槽 +120：动画对象
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 144))(pArg1, 0);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
            else  // 否则分支
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 144))(pArg1, 1);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
            v21 = 0;
            v22 = 0;
            v23 = 0;
            v24 = 1;
            sub_431230((int)&v20, pArg1 + 2119);  // uint32 vector push_back
            (*(void (/*thiscall*/ **)(uint32_t *, int, void **))(*pArg1 + 560))(pArg1, 8, &v20);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
            sub_5E5260(&v20);  // 调 动画子对象清理临时缓冲
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4E1780 sub_4E1780 —— 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
// 前置：·sub_58FC30(vmt14C) 基类 tick；条件 273 态进出各 15% 概率 ·sub_4DB130 语音 25/26（·this+8296 去抖）；
// 时钟 vt+1176 到点且大状态 < 4 或 == 9 → vt+560(13,0,2,0)；本地玩家冷却到 → vt+1252；
// switch 大状态：0 基类行为 ·sub_4DA730、5 受击闪烁（vt+252 三通道 + ·sub_423A80 插值）、10 vt+560(0)、11 倒地、13 渐隐（850/300ms 阈值）【推断：5/13 表现语义】
// ------------------------------------------------------------
char /*thiscall*/ sub_4E1780(uint32_t *this)  // 实现：怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
{
  int v2; // eax
  int nPickSrcPos; // ecx  | +0x20A0 → 拾取/交互源坐标缓存（对象首字节非 0 时被写入 +668）【推断】（IRDMonster；va=004D94A0）
  int pThis_10; // edi
  unsigned int fld_e1639; // eax  | +0x199C → nMainState6556〔族字典〕（族字典）
  int fld_e16392; // eax
  int fld_e16393; // eax  | +0x199C → nMainState6556〔族字典〕（族字典）
  int pThis_6683; // eax
  int v9; // eax
  int pObj7768_; // ebx  | +0x1E58 → 复位批 dword 槽（0x4DE700 清零）（IRDMonster；va=004DE700）
  int pThis_6682; // eax
  int pThis_668; // eax
  int pObj7768; // edi  | +0x1E58 → 复位批 dword 槽（0x4DE700 清零）（IRDMonster；va=004DE700）
  int pObj7768_2; // [esp-4h] [ebp-10h]  | +0x1E58 → 复位批 dword 槽（0x4DE700 清零）（IRDMonster；va=004DE700）

  sub_58FC30();  // 【IRDActiveObject__vmt14C】
  if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1264))(this);  // 调虚槽 +1264
  if ( (*(uint8_t *)(this + 162) & 1) != 0 )  // this+162〔bFlag162〕
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1220))(this);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
  v2 = sub_4E0CD0(273, 0, 0, -1);  // 按条件号收集对象（阵营/距离/归属过滤，返回计数）
  if ( v2 != 0 )  // 若 v2 非 0
  {
    if ( v2 > 0 && *((uint8_t *)this + 8296) == 0 )  // 若 v2 > 0
    {
      if ( rand() % 100 < 15 )  // 15% 概率触发（rand()%100 < 15）
        sub_4DB130(25, -1);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
      *((uint8_t *)this + 8296) = 1;  // this+8296〔去抖〕
    }
  }
  else if ( *((uint8_t *)this + 8296) == 1 )  // this+8296〔nOffsetVal(推断)〕
  {
    *((uint8_t *)this + 8296) = 0;  // this+8296〔去抖〕
    if ( rand() % 100 < 15 )  // 15% 概率触发（rand()%100 < 15）
      sub_4DB130(26, -1);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
  }
  nPickSrcPos = *(this + 2088);  // this+8352〔nRideHost8352〕
  if ( nPickSrcPos != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nPickSrcPos + 724))(nPickSrcPos) != 0 )  // 调虚槽 +724：读 +6552 霸体字节
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1164))(this, 0);  // 调虚槽 +1164：CNSwordman__vmt48C
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1176))(this) != 0 )  // 调虚槽 +1176
  {
    pThis_10 = sub_699000((int)(this + 16));  // 【clock_now(clk)】
    if ( pThis_10 >= (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1176))(this) )  // 调虚槽 +1176
    {
      fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
      if ( fld_e1639 < 4 || fld_e1639 == 9 )  // 若 fld_e1639 < 4 与/或 fld_e1639 == 9
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 13, 0, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  if ( dword_8F7C04 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520)  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
    && (*(this + 1815) == 0 || sub_699000((int)(this + 2)) >= *(this + 1917) && ((fld_e16392 = *(this + 1639)) == 0 || fld_e16392 == 2)) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1252))(this);  // 调虚槽 +1252
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0  // 调虚槽 +724：读 +6552 霸体字节
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 936))(this) != 0 )  // 调虚槽 +936
  {
    *((uint8_t *)this + 7092) = 0;
  }
  fld_e16393 = *(this + 1639);  // this+6556〔大状态ID〕
  switch ( fld_e16393 )  // 按 fld_e16393 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      LOBYTE(fld_e16393) = sub_4DA730(this);
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 30) != 0 )  // this+120〔pAnimObj〕
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 1020))(this) != 0 )  // 调虚槽 +1020：CNSwordman__vmt3FC
        {
          pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
          pObj7768 = sub_423A80(255, 100, 100 - *(this + 1942) + pThis_668, 100);  // 同上 int 版（FTOL 截断）
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 252))(this, 0, pObj7768);  // 调虚槽 +252
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 1, pObj7768);  // 调虚槽 +252
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 2, pObj7768);  // 调虚槽 +252
        }
        else if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )  // 登录/选区管理器
        {
          if ( (double)(int)*(this + 1942) * 0.40000001 < (double)sub_699000((int)(this + 1640)) )  // 【clock_now(clk)】
          {
            pObj7768_ = *(this + 1942);  // this+7768〔pObj7768〕
            if ( sub_699000((int)(this + 1640)) < pObj7768_ && sub_460550((uint64_t)((double)pObj7768_ * 0.30000001)) != 0 )  // 【clock_now(clk)】
              (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, 0);  // 调虚槽 +252
            else  // 否则分支
              (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, -1);  // 调虚槽 +252
            sub_494F20(0, 0.0);  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
            sub_494F20(1, 0.0);  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
            sub_494F20(2, 0.0);  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
          }
        }
        else  // 否则分支
        {
          pThis_6682 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
          pObj7768_2 = sub_423A80(255, 0, 100 - *(this + 1942) + pThis_6682, 100);  // 同上 int 版（FTOL 截断）
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, pObj7768_2);  // 调虚槽 +252
        }
      }
      fld_e16393 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
      if ( fld_e16393 >= *(this + 1942) )  // this+7768〔pObj7768〕
      {
        LOBYTE(fld_e16393) = *((uint8_t *)this + 264);  // this+264〔nAnimHandle(推断)〕
        if ( (uint8_t)fld_e16393 == 0 )
          LOBYTE(fld_e16393) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);  // 调虚槽 +1256
      }
      break;  // 跳出循环/分支
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      fld_e16393 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
      if ( fld_e16393 != 0 )  // 若 fld_e16393 非 0
      {
        fld_e16393 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
        if ( *(uint8_t *)(fld_e16393 + 170) != 0 )
        {
          LOBYTE(fld_e16393) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
          if ( (uint8_t)fld_e16393 != 0 )
            LOBYTE(fld_e16393) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
                           this,
                           0,
                           0,
                           0,
                           0);
        }
      }
      break;  // 跳出循环/分支
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      fld_e16393 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      if ( fld_e16393 == 0 )  // 若 fld_e16393 为 0
        LOBYTE(fld_e16393) = sub_49C970(5, 0, 0);  // 池分配包装（this+4 复制为第 2/3 参）
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
        && sub_699000((int)(this + 1640)) >= 850 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);  // 调虚槽 +1256
      }
      fld_e16393 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
      if ( fld_e16393 >= 300 )  // 若 fld_e16393 >= 300
      {
        pThis_6683 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
        v9 = sub_423A80(255, 0, pThis_6683 - 300, 550);  // 同上 int 版（FTOL 截断）
        LOBYTE(fld_e16393) = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 252))(this, 3, v9);  // 调虚槽 +252
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      return fld_e16393;  // | +0x199C → nMainState6556〔族字典〕（族字典）
  }
  return fld_e16393;  // | +0x199C → nMainState6556〔族字典〕（族字典）
}


// ------------------------------------------------------------
// 0x4E1BE0 sub_4E1BE0 —— 仇恨目标重选（取仇恨值最大且 vt+724==0 的敌人）
// 门 vt+308 + ·this+7528 标志；暂存并清 ·this+1813；大状态 ∈ {9,10,11} 且旧目标 vt+1244==1 → vt+1152(旧) 直返；
// 否则 ·sub_4DC920/4DCAB0/4E0A40 收集 → 遍历条件 17 + 敌我 + 归属门 → ·sub_4DCCB0 打分取最大；
// 目标变更 → vt+1152(新) + vt+1260()；未变更 → vt+1152(旧)
// ------------------------------------------------------------
char /*thiscall*/ sub_4E1BE0(uint32_t *this)  // 实现：仇恨目标重选（取仇恨值最大且 vt+724==0 的敌人）
{
  char result; // al
  int nBigState; // eax  | +0x1BEC → ★大状态 ID（CNGhoulOilSellerOlrek；va=004DB480）
  unsigned int v4; // ebx
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e1891; // eax
  int fld_e29; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v13; // edx
  int pObj; // edi
  int v15; // ebx
  int v16; // edx
  int v17; // [esp+4h] [ebp-2Ch] BYREF
  int v18; // [esp+8h] [ebp-28h] BYREF
  int v19; // [esp+Ch] [ebp-24h] BYREF
  int v20; // [esp+10h] [ebp-20h] BYREF
  int v21; // [esp+14h] [ebp-1Ch] BYREF
  int v22; // [esp+18h] [ebp-18h] BYREF
  int fld_e18132; // [esp+1Ch] [ebp-14h]
  int v24; // [esp+20h] [ebp-10h]
  int v25; // [esp+24h] [ebp-Ch] BYREF
  int pObj3; // [esp+28h] [ebp-8h]
  unsigned int v27; // [esp+2Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *((uint8_t *)this + 7528);  // this+7528〔bCfgBlock8(推断)〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      nBigState = *(this + 1787);  // this+7148〔nBigState〕
      v4 = 0;
      pTarget7252 = *(this + 1813);  // this+7252〔pTarget7252〕
      fld_e18132 = pTarget7252;
      pObj3 = 0;
      *(this + 1813) = 0;  // this+7252〔pTarget7252〕
      v24 = 0;
      if ( (nBigState == 9 || nBigState == 10 || nBigState == 11)  // 若 fld_e1787 == 9 与/或 fld_e1787 == 10 与/或 fld_e1787 == 11
        && pTarget7252 != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pTarget7252) == 1 )  // 调虚槽 +1244
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1152))(this, pTarget7252);  // 调虚槽 +1152：CNSwordman__vmt480
      }
      else  // 否则分支
      {
        fld_e1891 = *(this + 1891);  // this+7564〔uForm7564(推断)〕
        v18 = 0;
        v19 = 0;
        v20 = 0;
        v21 = 0;
        v17 = 0;
        v22 = 0;
        if ( fld_e1891 != 0 )  // 若 fld_e1891 非 0
          sub_4DC920(this, &v17, &v18);  // 对象列表属性极值挑选（等级）
        if ( *(this + 1892) != 0 )  // this+7568〔uEnable7568(推断)〕
          sub_4DCAB0(this, &v19, &v20);  // 对象列表 HP 极值挑选（0x4DC920 的 HP 版对偶）
        if ( *(this + 1893) != 0 )  // this+7572〔uGrade7572(推断)〕
          sub_4E0A40(this, &v21, &v22);  // 敌对怪物名单收集（追加进 8 字节/条容器）
        while ( 1 )  // 条件循环
        {
          fld_e29 = *(this + 29);  // this+116〔会话上下文〕
          v8 = *(uint32_t *)(fld_e29 + 120);
          v27 = v4;
          v9 = v8 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v8) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)v4 >= v9 )
            break;  // 跳出循环/分支
          v10 = *(uint32_t *)(fld_e29 + 120);
          if ( v10 != 0 && v4 < (*(uint32_t *)(fld_e29 + 124) - v10) >> 2 )  // 若 v10 != 0
            pObj2 = *(uint32_t *)(v10 + 4 * v4);
          else  // 否则分支
            pObj2 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          {
            fld_e292 = *(this + 29);  // this+116〔会话上下文〕
            v13 = *(uint32_t *)(fld_e292 + 120);
            if ( v13 != 0 && v4 < (*(uint32_t *)(fld_e292 + 124) - v13) >> 2 )  // 若 v13 != 0
              pObj = *(uint32_t *)(v13 + 4 * v4);
            else  // 否则分支
              pObj = 0;
            if ( (uint8_t)sub_4E4630(pObj) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
              && (uint8_t)sub_4E5CA0(pObj) == 0  // 阵营号 200..204 判定（200 起逐个比较）
              && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) != 0 )  // 调虚槽 +1244
            {
              v25 = 0;
              sub_4DCCB0(this, (int)&v25, pObj, COERCE_FLOAT(&v17));  // AI 威胁值累加（仇恨打分）
              v15 = v25;
              if ( (v25 > v24 || pObj3 == 0) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )  // 调虚槽 +724：读 +6552 霸体字节
              {
                pObj3 = pObj;
                v24 = v15;
              }
              v4 = v27;
            }
          }
          pTarget7252 = fld_e18132;
          ++v4;
        }
        v16 = *this;
        if ( pTarget7252 == pObj3 )  // 若 fld_e1813 == pObj3
        {
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(v16 + 1152))(this, pTarget7252);  // 调虚槽 +1152：CNSwordman__vmt480
        }
        else  // 否则分支
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 1152))(this, pObj3);  // 调虚槽 +1152：CNSwordman__vmt480
          return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1260))(this);  // 调虚槽 +1260
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4E1DD0 sub_4E1DD0 —— 方位/威胁分档查询（vt+736 vs vt+740/2 + 条件 529 计数）
// *uArg2 = (vt+736 > vt+740/2) ? 0 : 2（左右半区）；v5 = ·0x4E0CD0(529,1,0,-1) 同族计数；
// 与 ·sub_456390(0) 阈值比较 → *uArg3 = 0 / 1(相等) / 2(大于)
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E1DD0(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)  // 实现：方位/威胁分档查询（vt+736 vs vt+740/2 + 条件 529 计数）
{
  int v4; // edi
  int v5; // esi
  uint32_t *result; // eax

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 2;  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
  *uArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= v4 ? 0 : 2;  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
  v5 = sub_4E0CD0(this, 529, 1, 0, -1);  // 按条件号收集对象（阵营/距离/归属过滤，返回计数）
  if ( v5 != 0 )  // 若 v5 非 0
  {
    result = (uint32_t *)sub_456390(0);  // result = 调 sub_456390 返回值
    if ( v5 <= (int)result )
    {
      *uArg3 = v5 == sub_456390(0);  // 调 存 座位号查询
      return uArg3;
    }
    else  // 否则分支
    {
      *uArg3 = 2;
    }
  }
  else  // 否则分支
  {
    *uArg3 = 0;
    return uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E1E70 sub_4E1E70 —— CNRDPassiveObject 构造（双内嵌表现对象 + 攻击上下文默认值）
// ·sub_4A4430 基类构造 → vftable(CNRDPassiveObject) → ·sub_4DF060(this+680) 表现对象；+840/+836/+820 = 15/0/0；
// ·sub_4A3450(this+724) 攻击上下文默认值（盒半宽 17、量程 100.0f）→ +940/+936/+920 = 15/0/0 → ·sub_5FF8E0(this)
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1E70(int this)  // 实现：CNRDPassiveObject 构造（双内嵌表现对象 + 攻击上下文默认值）
{
  sub_4A4430((uint32_t *)this);  // 调 基类构造 → vftable(CNRDPassiveObject) → ·sub_
  *(uint32_t *)this = &CNRDPassiveObject::`vftable';  // 构造装配 vftable：CNRDPassiveObject
  sub_4DF060((uint32_t *)(this + 680));  // 表现对象构造（清零 + +20/=1 使能 + sub_4017E0 字符串构造）。
  *(uint32_t *)(this + 840) = 15;
  *(uint32_t *)(this + 836) = 0;
  *(uint8_t *)(this + 820) = 0;
  sub_4A3450((uint32_t *)(this + 724));  // this+724〔fVal724(推断)〕
  *(uint32_t *)(this + 940) = 15;  // this+940〔nNameBufCap〕
  *(uint32_t *)(this + 936) = 0;
  *(uint8_t *)(this + 920) = 0;  // this+920〔pNameBuf〕
  sub_5FF8E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4E1FC0 sub_4E1FC0 —— 取召唤主/车主（this+692 对象 vt+576）
// this+692 非空 → 调其 vt+576（车主）返回；否则 0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1FC0(uint32_t *this)  // 实现：取召唤主/车主（this+692 对象 vt+576）
{
  int nSnapshot692; // eax  | +0x02B4 → 表现/名字快照[3]（4E1FE0）（证据 va=004E1FE0）（CNRDPassiveObject；va=004E1FE0）

  nSnapshot692 = *(this + 173);  // this+692〔nSnapshot692〕
  if ( nSnapshot692 != 0 )  // 若 fld_e173 非 0
    return (*(int (**)(void))(*(uint32_t *)nSnapshot692 + 576))();  // 调虚槽 +576
  else  // 否则分支
    return 0;
}



// ------------------------------------------------------------
// 0x4E1FE0 sub_4E1FE0 —— 表现/名字块赋值（28 字节直拷 + std::string）
// 拷贝 this+680 起 28 字节（7 字段）→ ·sub_41DC80(this+708, a2+28) std::string 赋值；返回 this+680
// ------------------------------------------------------------
int /*thiscall*/ sub_4E1FE0(int this, int pArg2)  // 实现：表现/名字块赋值（28 字节直拷 + std::string）
{
  int pThis_2A8; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_2A8 = this + 680;  // this+680〔nSnapshot680〕
  *(uint32_t *)(this + 680) = *(uint32_t *)pArg2;  // this+680〔nSnapshot680〕
  *(uint32_t *)(this + 684) = *(uint32_t *)(pArg2 + 4);  // this+684〔nSnapshot684〕
  *(uint32_t *)(this + 688) = *(uint32_t *)(pArg2 + 8);  // this+688〔nSnapshot688〕
  *(uint32_t *)(this + 692) = *(uint32_t *)(pArg2 + 12);  // this+692〔nSnapshot692〕
  *(uint32_t *)(this + 696) = *(uint32_t *)(pArg2 + 16);  // this+696〔nSnapshot696〕
  *(uint8_t *)(this + 700) = *(uint8_t *)(pArg2 + 20);  // this+700〔bSnapshot700〕
  *(uint8_t *)(this + 701) = *(uint8_t *)(pArg2 + 21);  // this+701〔bSnapshot701〕
  *(uint32_t *)(this + 704) = *(uint32_t *)(pArg2 + 24);  // this+704〔nSnapshot704〕
  sub_41DC80(this + 708, pArg2 + 28);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  return pThis_2A8;
}



// ------------------------------------------------------------
// 0x4E2040 sub_4E2040 —— CNRDPassiveObject 析构（两组内联 string + 指针 vector + 基类）
// vftable → ·sub_5FF980 → 释放两处内联 std::string（+920/+820 侧，容量 >= 16 才 free）并复位为 15/null/0；
// ·sub_4017E0(this+708) 指针 vector 释放 → ·sub_4A4590(this) 基类析构
// ------------------------------------------------------------
int /*thiscall*/ sub_4E2040(void **this)  // 实现：CNRDPassiveObject 析构（两组内联 string + 指针 vector + 基类）
{
  *this = &CNRDPassiveObject::`vftable';  // 构造装配 vftable：CNRDPassiveObject
  sub_5FF980();
  if ( (unsigned int)*(this + 235) >= 0x10 )  // this+940〔nNameBufCap〕
    j__free(*(this + 230));  // this+920〔pNameBuf〕
  *(this + 235) = (void *)15;  // this+940〔nNameBufCap〕
  *(this + 234) = nullptr;
  *((uint8_t *)this + 920) = 0;  // this+920〔pNameBuf〕
  if ( (unsigned int)*(this + 210) >= 0x10 )
    j__free(*(this + 205));
  *(this + 210) = (void *)15;
  *(this + 209) = nullptr;
  *((uint8_t *)this + 820) = 0;  // this[820] = 0
  sub_4017E0(this + 177);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  return sub_4A4590(this);  // IRDCollisionObject 析构本体（0x4A4710 vmt0 转发至此）
}



// ------------------------------------------------------------
// 0x4E2100 sub_4E2100 —— 析构 thunk（调 ·0x4E2040 后按 pszArg2 & 1 释放自身）
// 编译器生成的 scalar deleting destructor：pszArg2 位 0 = 需释放堆块
// ------------------------------------------------------------
void **/*thiscall*/ sub_4E2100(void **Block, char pszArg2)  // 实现：析构 thunk（调 ·0x4E2040 后按 pszArg2 & 1 释放自身）
{
  sub_4E2040(Block);  // CNRDPassiveObject 析构（两组内联 string + 指针 vector + 基类）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4E2130 sub_4E2130 —— CNRDItemObject 构造（掉落物/道具对象）
// ·0x4E1E70 基类 → vftable(CNRDItemObject) → 内嵌两组 clong（+1016 / +1032 区）·sub_41A630 构造并置初值；
// ·sub_578740(this) 粒子动画辅助 → ·sub_578D50(a2,a3,a4) 掉落物初始化（物理 + 4D33A0/4D5xxx 族）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4E2130(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 实现：CNRDItemObject 构造（掉落物/道具对象）
{
  sub_4E1E70((int)this);  // CNRDPassiveObject 构造（双内嵌表现对象 + 攻击上下文默认值）
  *(uint32_t *)this = &CNRDItemObject::`vftable';  // 构造装配 vftable：CNRDItemObject
  *(this + 992) = 0;
  *((uint32_t *)this + 247) = &off_6C2B88;  // this+988〔uCfgA988(推断)〕
  *((uint32_t *)this + 249) = 0;  // this[249] = 0
  *(this + 1000) = 1;
  *(this + 1002) = 0;
  *(this + 1001) = 0;
  *((uint32_t *)this + 253) = 0;  // this+1012〔uGrabA1012〕
  *((uint32_t *)this + 252) = 0;  // this[252] = 0
  *((uint32_t *)this + 251) = 0;  // this[251] = 0
  sub_41A630((unsigned int)(this + 1016));  // 调 防篡改字段读校验（crypt 逆运算链）
  *((uint32_t *)this + 254) = &clong::`vftable';  // 构造装配 vftable：clong
  *(this + 1036) = 0;
  *((uint32_t *)this + 258) = &off_6C2B88;
  *((uint32_t *)this + 260) = 0;  // this[260] = 0
  *(this + 1044) = 1;
  *(this + 1046) = 0;
  *(this + 1045) = 0;
  *((uint32_t *)this + 264) = 0;  // this[264] = 0
  *((uint32_t *)this + 263) = 0;  // this[263] = 0
  *((uint32_t *)this + 262) = 0;  // this[262] = 0
  sub_578740(this);  // 粒子/动画辅助（41A590）
  sub_578D50(nArg2, nArg3, nArg4);  // 掉落物更新（578C40 物理 + 4D33A0/445D00/445B90/4A0B60 表现）
  return this;
}



// ------------------------------------------------------------
// 0x4E2230 sub_4E2230 —— 析构 thunk（调 ·0x4E2260 后按 pszArg2 & 1 释放自身）
// 编译器生成的 scalar deleting destructor（掉落物对象；语义同 ·sub_4E2100）
// ------------------------------------------------------------
void */*thiscall*/ sub_4E2230(void *Block, char pszArg2)  // 实现：析构 thunk（调 ·0x4E2260 后按 pszArg2 & 1 释放自身）
{
  sub_4E2260();  // CNRDItemObject 析构
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4E2260 sub_4E2260 —— CNRDItemObject 析构
// vftable → ·sub_578780 → 内嵌 clong 的 vftable 复位 + ·sub_41A580(+1016 区) → ·0x4E2040 基类析构
// ------------------------------------------------------------
int /*thiscall*/ sub_4E2260(int this)  // 实现：CNRDItemObject 析构
{
  *(uint32_t *)this = &CNRDItemObject::`vftable';  // 构造装配 vftable：CNRDItemObject
  sub_578780();  // 17 行小辅助（表现参数）
  *(uint32_t *)(this + 1032) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1036) = 0;
  sub_41A580((uint32_t *)(this + 1016));  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  *(uint32_t *)(this + 988) = &nengine::IObject::`vftable';  // this+988〔uCfgA988(推断)〕
  *(uint8_t *)(this + 992) = 0;  // this+992〔uCfgB992(推断)〕
  return sub_4E2040((void **)this);  // CNRDPassiveObject 析构（两组内联 string + 指针 vector + 基类）
}



// ------------------------------------------------------------
// 0x4E22E0 sub_4E22E0 —— 掉落物生成（角度均分 + 定位 + 文本倒计时）
// 种子 v19 = pArg3 + 10×vt+52 + a2 + a5；srand → nRand = rand()%360；v24 = ·sub_522300(…)；
// new(0x424) → ·0x4E2130(对象, v24, &v19, nRand + 360/nArg2)（角度 = 随机 + 均分）→ vt+80(289,…) 注册 → ·sub_45FE80 入演播；
// vt+140/vt+112 定位于本体 x/y → ·sub_578870(nArg7, 10000) 掉落文本 + 10000ms 倒计时
// ------------------------------------------------------------
int /*thiscall*/ sub_4E22E0(int *this, int nArg2, void *pArg3, int nArg4, int nArg5, void *Block, int nArg7)  // 实现：掉落物生成（角度均分 + 定位 + 文本倒计时）
{
  uint8_t *pMem; // ecx
  uint8_t *pObj; // edi
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v16; // [esp+0h] [ebp-24h]
  int v17; // [esp+4h] [ebp-20h]
  int v18; // [esp+8h] [ebp-1Ch]
  unsigned int v19; // [esp+Ch] [ebp-18h] BYREF
  int v20; // [esp+10h] [ebp-14h] BYREF
  int v21; // [esp+14h] [ebp-10h] BYREF
  int v22; // [esp+20h] [ebp-4h]
  int nRand; // [esp+30h] [ebp+Ch]
  int v24; // [esp+38h] [ebp+14h]

  v19 = (unsigned int)pArg3 + 10 * (*(int (/*thiscall*/ **)(int *))(*this + 52))(this) + nArg2 + nArg5;  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  srand(v19);
  nRand = rand() % 360;  // nRand = 调 rand
  v24 = sub_522300(pArg3, nArg4, 0, 0, (int)Block, 1);  // v24 = 调 sub_522300 返回值
  pMem = operator new(0x424u);  // new(1060 字节) 分配对象
  pObj = nullptr;  // pObj = 空指针
  v22 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pObj = sub_4E2130(pMem, v24, (int)&v19, nRand + 360 / nArg2);  // CNRDItemObject 构造（掉落物/道具对象）
  v12 = *this;
  v22 = -1;
  v20 = (*(int (/*thiscall*/ **)(int *))(v12 + 120))(this);  // 调虚槽 +120：动画对象
  v21 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  off_77F3FC((char *)&byte_6F9858, 289, nArg5);  // 引擎日志输出函数(printf 风格)
  v13 = (*(int (/*thiscall*/ **)(int *, int, int, uint8_t *, uint32_t, uint32_t))(*this + 80))(this, 289, nArg5, pObj, 0, 0);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  sub_45FE80(v13, (int)pObj, v16, v17, v18, v19, v20);  // 调 实体对象注册到演播层
  v14 = *(uint32_t *)pObj;
  v20 = 1;
  v19 = 0;
  (*(void (/*thiscall*/ **)(uint8_t *, int *, int *))(v14 + 140))(pObj, &v20, &v21);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
  (*(void (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v20, v21, 60);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  return sub_578870(nArg7, 10000);  // 掉落物字符串初始化（41A590 + 698F90）
}



// ------------------------------------------------------------
// 0x4E2420 sub_4E2420 —— 怪物对象创建（资源载入 + 字段装配 + 动画件表）
// 先清两处倒计时(·sub_698F90)与计时字段；初值：+8480/+8488 区、+2120/+2121 = 0/3000、+1802 = 180ms、+1796 = 0xFF000000 色；
// ·sub_4015C0 存名 → ·dword_8F84C4 vt+4 载资源，失败 → 打印 MONSTER CREATE FAIL! FILENAME[%s]；拷 name/id/属性(+444..+924)；
// 8 个动画件槽 ·sub_431920(this+1540..1548) + 三组字符串列表（过滤 szPassword）+ 默认行为表 qmemcpy(this+8368, unk_6F8B68, 104) + vt+464 装配
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E2420(char *this, void *Src, int nArg3)  // 实现：怪物对象创建（资源载入 + 字段装配 + 动画件表）
{
  int pThis_1DD8; // ecx
  int v5; // esi
  unsigned int result; // eax
  int pThis_154; // eax
  char *pThis_124; // edi
  int pThis_34; // eax
  uint32_t *pThis_54; // ecx
  uint32_t *pThis_53; // eax
  uint32_t *pThis_542; // ecx
  uint32_t *pThis_532; // eax
  int v14; // edi
  int v15; // edi
  int pThis_6C; // eax
  int v17; // edi
  int pThis_6C2; // eax
  int v19; // edi
  int pThis_6C3; // eax
  int *v21; // edi
  int v22; // ecx
  int pThis_6C4; // eax
  bool v24; // zf
  int v25; // edi
  int pThis_6C5; // eax
  int v27; // edi
  int pThis_6C6; // eax
  int v29; // edi
  int pThis_6C7; // eax
  int v31; // edi
  int pThis_6C8; // eax
  int pThis_5B; // edi
  char v34; // al
  int v35; // eax
  int pThis_60E2; // esi
  int pThis_1834; // ecx
  unsigned int pThis_60F3; // edi
  int *pThis_60F4; // edx
  int pThis_60E; // esi
  unsigned int pThis_60F; // edx
  uint32_t *pThis_60F2; // eax
  int pThis_5B2; // edi
  char v44; // al
  int v45; // eax
  int pThis_6122; // esi
  int pThis_1844; // ecx
  unsigned int pThis_6133; // edi
  int *pThis_6134; // edx
  int pThis_612; // esi
  unsigned int pThis_613; // edx
  uint32_t *pThis_6132; // eax
  uint32_t *v53; // edx
  char *pThis_16C; // ecx
  int v55; // eax
  char *pThis_16C2; // esi
  int v57; // edi
  int v58; // eax
  int v59; // eax
  char *pThis_16C3; // esi
  int v61; // edi
  int v62; // eax
  int v63; // eax
  uint32_t *v64; // esi
  int pThis_1542; // eax
  char *pThis_1E90; // edi
  uint32_t *v67; // esi
  int *pMem; // eax
  int *pMem3; // esi
  int *pMem32; // ecx
  int v71; // eax
  int *pMem2; // eax
  int *pMem22; // esi
  int *pMem222; // ecx
  int v75; // edx
  unsigned int i; // esi
  int pThis_533; // ecx
  int v78; // [esp-4h] [ebp-C0h]
  int v79; // [esp-4h] [ebp-C0h]
  uint32_t v80[23]; // [esp+Ch] [ebp-B0h] BYREF
  void *Block; // [esp+6Ch] [ebp-50h]
  int v82; // [esp+7Ch] [ebp-40h]
  unsigned int v83; // [esp+80h] [ebp-3Ch]
  int v84; // [esp+A4h] [ebp-18h]
  int v85; // [esp+A8h] [ebp-14h] BYREF
  uint32_t *v86; // [esp+ACh] [ebp-10h]
  int v87; // [esp+B8h] [ebp-4h]
  uint32_t *Srca; // [esp+C4h] [ebp+8h]
  char *Srcb; // [esp+C4h] [ebp+8h]
  char *Srcc; // [esp+C4h] [ebp+8h]
  char *Srcd; // [esp+C4h] [ebp+8h]
  char *Srce; // [esp+C4h] [ebp+8h]
  int Srcf; // [esp+C4h] [ebp+8h]

  pThis_1DD8 = (int)(this + 7640);
  *(uint8_t *)(pThis_1DD8 + 13) = 0;
  *(uint8_t *)(pThis_1DD8 + 14) = 0;
  sub_698F90(pThis_1DD8, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 8501) = 0;
  *(this + 8502) = 0;
  sub_698F90((int)(this + 8488), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 2120) = 0;  // this+8480〔pAtkObj〕
  *((uint32_t *)this + 2121) = 3000;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  *(this + 7180) = 0;
  *(this + 7181) = 0;
  *(this + 7182) = 0;
  *(this + 7183) = 0;
  *((uint32_t *)this + 1798) = 0;  // this[1798] = 0
  *((uint32_t *)this + 1799) = 6;  // this[1799] = 6
  *((uint32_t *)this + 1800) = 12;
  *((uint32_t *)this + 1801) = 0;  // this[1801] = 0
  *((uint32_t *)this + 1802) = 1600;
  *((uint32_t *)this + 1803) = 0;  // this[1803] = 0
  *((uint32_t *)this + 1804) = 0;  // this[1804] = 0
  *((uint32_t *)this + 1805) = 0;  // this[1805] = 0
  *((uint32_t *)this + 1806) = 0;  // this[1806] = 0
  *((uint32_t *)this + 1807) = 0;  // this[1807] = 0
  *((uint32_t *)this + 1807) = dword_99FCCC;
  *((uint32_t *)this + 1802) = 180;
  *((uint32_t *)this + 1798) = 1;  // this[1798] = 1
  *(this + 7182) = 1;
  *((uint32_t *)this + 1796) = -16777216;
  v5 = (*(int (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, Src);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v86 = (uint32_t *)v5;
  if ( v5 == 0 )  // 若 v5 为 0
    return off_77F3FC("MONSTER CREATE FAIL! FILENAME[%s]", (const char *)Src);  // 返回 调 off_77F3FC
  sub_4014D0((std::_String_base *)(this + 360), v5 + 928, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) = *(uint32_t *)v5;  // 调虚槽 +340：三元组基址（+284，vt+340）
  pThis_154 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);  // 调虚槽 +340：三元组基址（+284，vt+340）
  sub_4014D0((std::_String_base *)(pThis_154 + 4), v5 + 4, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 32) = *(uint32_t *)(v5 + 32);  // 调虚槽 +340：三元组基址（+284，vt+340）
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 36) = *(uint32_t *)(v5 + 36);  // 调虚槽 +340：三元组基址（+284，vt+340）
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this) + 40) = *(uint32_t *)(v5 + 40);  // 调虚槽 +340：三元组基址（+284，vt+340）
  *((uint32_t *)this + 27) = *(uint32_t *)(v5 + 44);  // this+108〔nAdd108(推断)〕
  if ( *((uint32_t *)this + 78) < 0x10u )
    pThis_124 = this + 292;
  else  // 否则分支
    pThis_124 = *((char **)this + 73);
  pThis_34 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  off_77F3FC(aSD_2, pThis_124, pThis_34);  // 引擎日志输出函数(printf 风格)
  sub_4ED3F0((int)(this + 328), v5 + 48);  // int 向量拷贝赋值（全容量路径）
  sub_4A3F80(v5 + 128);
  pThis_54 = *((uint32_t **)this + 84);
  pThis_53 = *((uint32_t **)this + 83);
  if ( pThis_53 == pThis_54 )  // 若 pThis_53 == pThis_54
    goto LABEL_11;
  do  // do-while 循环体起点
  {
    if ( *pThis_53 == 10 )
      break;  // 跳出循环/分支
    ++pThis_53;
  }
  while ( pThis_53 != pThis_54 );  // 条件循环
  if ( pThis_53 == pThis_54 )  // 若 pThis_53 == pThis_54
  {
LABEL_11:  // 标签 LABEL_11（跳转合流点）
    if ( (uint8_t)sub_4DAB60(11) == 0 )  // 标签/条件集合成员判定
      (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 456))(this, 10, 0);  // 调虚槽 +456：命中列表追加（vt+676(0) 联动 + 基类）
  }
  pThis_542 = *((uint32_t **)this + 84);
  pThis_532 = *((uint32_t **)this + 83);
  if ( pThis_532 == pThis_542 )  // 若 pThis_532 == pThis_542
    goto LABEL_19;
  do  // do-while 循环体起点
  {
    if ( *pThis_532 == 12 )
      break;  // 跳出循环/分支
    ++pThis_532;
  }
  while ( pThis_532 != pThis_542 );  // 条件循环
  if ( pThis_532 == pThis_542 )  // 若 pThis_532 == pThis_542
  {
LABEL_19:  // 标签 LABEL_19（跳转合流点）
    if ( (uint8_t)sub_4DAB60(13) == 0  // 标签/条件集合成员判定
      && (uint8_t)sub_4DAB60(14) == 0  // 标签/条件集合成员判定
      && (uint8_t)sub_4DAB60(15) == 0 )  // 标签/条件集合成员判定
    {
      (*(void (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 456))(this, 13, 0);  // 调虚槽 +456：命中列表追加（vt+676(0) 联动 + 基类）
    }
  }
  *((uint32_t *)this + 1880) = *(uint32_t *)(v5 + 444);  // this+7520〔nSightRange(推断)〕
  *((uint32_t *)this + 1881) = *(uint32_t *)(v5 + 448);  // this+7524〔uCfgBlock4(推断)〕
  *(this + 7529) = *(uint8_t *)(v5 + 452);
  *(this + 7530) = *(uint8_t *)(v5 + 453);
  *(this + 7531) = *(uint8_t *)(v5 + 468);
  *(this + 7532) = *(uint8_t *)(v5 + 469);
  *(this + 7533) = *(uint8_t *)(v5 + 470);
  *((uint32_t *)this + 1898) = *(uint32_t *)(v5 + 492);  // this+7592〔nAtkSegSlot7592〕
  *((uint32_t *)this + 1900) = *(uint32_t *)(v5 + 496);
  *(this + 7559) = *(uint8_t *)(v5 + 500);
  *((uint32_t *)this + 1890) = *(uint32_t *)(v5 + 504);
  *((uint32_t *)this + 1894) = *(uint32_t *)(v5 + 472);  // this+7576〔uPhase7576(推断)〕
  *((uint32_t *)this + 1895) = *(uint32_t *)(v5 + 476);  // this+7580〔uSegDefault7580(推断)〕
  *((uint32_t *)this + 1896) = *(uint32_t *)(v5 + 480);  // this+7584〔uForm7584〕
  *((uint32_t *)this + 1897) = *(uint32_t *)(v5 + 484);  // this+7588〔uForm7588〕
  *((uint32_t *)this + 1891) = *(uint32_t *)(v5 + 456);  // this+7564〔uForm7564(推断)〕
  *((uint32_t *)this + 1892) = *(uint32_t *)(v5 + 460);  // this+7568〔uEnable7568(推断)〕
  sub_4DEEA0(v5 + 900);  // 32 字节/条容器拷贝赋值（vector::operator= 内核）
  *((uint32_t *)this + 1822) = *(uint32_t *)(v5 + 916);
  *((uint32_t *)this + 1823) = *(uint32_t *)(v5 + 920);
  *((uint32_t *)this + 1824) = *(uint32_t *)(v5 + 924);
  if ( sub_40BF00((std::_String_base *)(v5 + 508), 0, *(uint32_t *)(v5 + 528), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    if ( *(uint32_t *)(v5 + 532) < 0x10u )
      v14 = v5 + 512;
    else  // 否则分支
      v14 = *(uint32_t *)(v5 + 512);
    v78 = *(uint32_t *)(v5 + 536);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v14);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *((uint32_t *)this + 1825) = sub_418DD0(v78);  // this[1825] = 调 sub_418DD0 返回值
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 540), 0, *(uint32_t *)(v5 + 560), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 0;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 564) < 0x10u )
        LOBYTE(v15) = v5 + 32;
      else  // 否则分支
        v15 = *(uint32_t *)(v5 + 544);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C = sub_431920((uint8_t)this + 108, v15, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C = sub_431920(*((uint32_t *)this + 91), v15, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1540) = pThis_6C;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 568), 0, *(uint32_t *)(v5 + 588), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 1;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 592) < 0x10u )
        LOBYTE(v17) = v5 + 60;
      else  // 否则分支
        v17 = *(uint32_t *)(v5 + 572);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C2 = sub_431920((uint8_t)this + 108, v17, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C2 = sub_431920(*((uint32_t *)this + 91), v17, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C2 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1541) = pThis_6C2;  // this+6164〔pFrameObj6164〕
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 596), 0, *(uint32_t *)(v5 + 616), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 2;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 620) < 0x10u )
        LOBYTE(v19) = v5 + 88;
      else  // 否则分支
        v19 = *(uint32_t *)(v5 + 600);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C3 = sub_431920((uint8_t)this + 108, v19, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C3 = sub_431920(*((uint32_t *)this + 91), v19, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C3 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1542) = pThis_6C3;
  }
  Srca = this + 6172;  // this+6172〔pAtkCtxA6172〕
  v21 = (int *)(v5 + 628);
  v85 = 2;
  do  // do-while 循环体起点
  {
    if ( sub_40BF00((std::_String_base *)(v21 - 1), 0, v21[4], szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      v84 = sub_42FCB0(228);  // CRT 一次性初始化
      v87 = 3;
      if ( v84 != 0 )  // 若 v84 非 0
      {
        if ( (unsigned int)v21[5] < 0x10 )
          LOBYTE(v22) = (uint8_t)v21;
        else  // 否则分支
          v22 = *v21;
        if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
          pThis_6C4 = sub_431920((uint8_t)this + 108, v22, 1);  // 动画件构造（文件名版）
        else  // 否则分支
          pThis_6C4 = sub_431920(*((uint32_t *)this + 91), v22, 1);  // 动画件构造（文件名版）
      }
      else  // 否则分支
      {
        pThis_6C4 = 0;
      }
      v87 = -1;
      *Srca = pThis_6C4;
    }
    v21 += 7;
    v24 = v85 == 1;
    ++Srca;  // Srca 自增
    --v85;
  }
  while ( !v24 );  // 条件循环
  if ( sub_40BF00((std::_String_base *)(v5 + 680), 0, *(uint32_t *)(v5 + 700), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 4;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 704) < 0x10u )
        LOBYTE(v25) = v5 - 84;
      else  // 否则分支
        v25 = *(uint32_t *)(v5 + 684);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C5 = sub_431920((uint8_t)this + 108, v25, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C5 = sub_431920(*((uint32_t *)this + 91), v25, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C5 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1545) = pThis_6C5;  // this+6180〔pAtkCtxC6180〕
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 708), 0, *(uint32_t *)(v5 + 728), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 5;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 732) < 0x10u )
        LOBYTE(v27) = v5 - 56;
      else  // 否则分支
        v27 = *(uint32_t *)(v5 + 712);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C6 = sub_431920((uint8_t)this + 108, v27, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C6 = sub_431920(*((uint32_t *)this + 91), v27, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C6 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1546) = pThis_6C6;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 736), 0, *(uint32_t *)(v5 + 756), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 6;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 760) < 0x10u )
        LOBYTE(v29) = v5 - 28;
      else  // 否则分支
        v29 = *(uint32_t *)(v5 + 740);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C7 = sub_431920((uint8_t)this + 108, v29, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C7 = sub_431920(*((uint32_t *)this + 91), v29, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C7 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1547) = pThis_6C7;
  }
  if ( sub_40BF00((std::_String_base *)(v5 + 764), 0, *(uint32_t *)(v5 + 784), szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v87 = 7;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( *(uint32_t *)(v5 + 788) < 0x10u )
        LOBYTE(v31) = v5;
      else  // 否则分支
        v31 = *(uint32_t *)(v5 + 768);
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_6C8 = sub_431920((uint8_t)this + 108, v31, 1);  // 动画件构造（文件名版）
      else  // 否则分支
        pThis_6C8 = sub_431920(*((uint32_t *)this + 91), v31, 1);  // 动画件构造（文件名版）
    }
    else  // 否则分支
    {
      pThis_6C8 = 0;
    }
    v87 = -1;
    *((uint32_t *)this + 1548) = pThis_6C8;
  }
  Srcb = *(char **)(v5 + 796);
  if ( Srcb != *(char **)(v5 + 800) )
  {
    do  // do-while 循环体起点
    {
      if ( strcmp((const char *)sub_41ACF0(Srcb), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
      {
        pThis_60E = *((uint32_t *)this + 1550);  // this+6200〔pTbl6200〕
        pThis_1834 = (int)(this + 6196);
        v85 = 0;
        if ( pThis_60E != 0 )  // 若 pThis_60E 非 0
          pThis_60F = (*((uint32_t *)this + 1551) - pThis_60E) >> 2;  // 向量元素数 = (end−begin)/4
        else  // 否则分支
          pThis_60F = 0;
        if ( pThis_60E == 0 || pThis_60F >= (*((uint32_t *)this + 1552) - pThis_60E) >> 2 )  // 若 pThis_60E == 0
          goto LABEL_128;
        pThis_60F2 = *((uint32_t **)this + 1551);
        *pThis_60F2 = 0;
        *((uint32_t *)this + 1551) = pThis_60F2 + 1;  // this[1551] = pThis_60F2 + 1
      }
      else  // 否则分支
      {
        v84 = sub_42FCB0(228);  // CRT 一次性初始化
        v87 = 8;
        if ( v84 != 0 )  // 若 v84 非 0
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
            LOBYTE(pThis_5B) = (uint8_t)this + 108;
          else  // 否则分支
            pThis_5B = *((uint32_t *)this + 91);  // this+364〔pAnimNameStr(推断)〕
          v34 = sub_41ACF0(Srcb);  // 驻留串句柄 → 字符串指针
          v35 = sub_431920(pThis_5B, v34, 1);  // 动画件构造（文件名版）
        }
        else  // 否则分支
        {
          v35 = 0;
        }
        pThis_60E2 = *((uint32_t *)this + 1550);  // this+6200〔pTbl6200〕
        pThis_1834 = (int)(this + 6196);
        v87 = -1;
        v85 = v35;
        if ( pThis_60E2 != 0 )  // 若 pThis_60E2 非 0
          pThis_60F3 = (*((uint32_t *)this + 1551) - pThis_60E2) >> 2;  // 向量元素数 = (end−begin)/4
        else  // 否则分支
          pThis_60F3 = 0;
        if ( pThis_60E2 == 0 || pThis_60F3 >= (*((uint32_t *)this + 1552) - pThis_60E2) >> 2 )  // 若 pThis_60E2 == 0
        {
LABEL_128:  // 标签 LABEL_128（跳转合流点）
          sub_42AC90(pThis_1834, *(char **)(pThis_1834 + 8), 1u, &v85);  // 向量批量插入核心
          goto LABEL_129;
        }
        pThis_60F4 = *((int **)this + 1551);
        *pThis_60F4 = v35;
        *((uint32_t *)this + 1551) = pThis_60F4 + 1;  // this[1551] = pThis_60F4 + 1
      }
LABEL_129:  // 标签 LABEL_129（跳转合流点）
      Srcb += 4;  // Srcb 前进 4
    }
    while ( Srcb != (char *)v86[200] );  // 条件循环
  }
  for ( Srcc = (char *)v86[203]; Srcc != (char *)v86[204]; Srcc += 4 )  // 遍历循环
  {
    if ( strcmp((const char *)sub_41ACF0(Srcc), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
    {
      pThis_612 = *((uint32_t *)this + 1554);  // this+6216〔pTbl6216(推断)〕
      pThis_1844 = (int)(this + 6212);
      v85 = 0;
      if ( pThis_612 != 0 )  // 若 pThis_612 非 0
        pThis_613 = (*((uint32_t *)this + 1555) - pThis_612) >> 2;  // this+6220〔pFrameVecEnd(推断)〕
      else  // 否则分支
        pThis_613 = 0;
      if ( pThis_612 == 0 || pThis_613 >= (*((uint32_t *)this + 1556) - pThis_612) >> 2 )  // 若 pThis_612 == 0
        goto LABEL_150;
      pThis_6132 = *((uint32_t **)this + 1555);
      *pThis_6132 = 0;
      *((uint32_t *)this + 1555) = pThis_6132 + 1;  // this[1555] = pThis_6132 + 1
    }
    else  // 否则分支
    {
      v84 = sub_42FCB0(228);  // CRT 一次性初始化
      v87 = 9;
      if ( v84 != 0 )  // 若 v84 非 0
      {
        if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
          LOBYTE(pThis_5B2) = (uint8_t)this + 108;
        else  // 否则分支
          pThis_5B2 = *((uint32_t *)this + 91);  // this+364〔pAnimNameStr(推断)〕
        v44 = sub_41ACF0(Srcc);  // 驻留串句柄 → 字符串指针
        v45 = sub_431920(pThis_5B2, v44, 1);  // 动画件构造（文件名版）
      }
      else  // 否则分支
      {
        v45 = 0;
      }
      pThis_6122 = *((uint32_t *)this + 1554);  // this+6216〔pTbl6216(推断)〕
      pThis_1844 = (int)(this + 6212);
      v87 = -1;
      v85 = v45;
      if ( pThis_6122 != 0 )  // 若 pThis_6122 非 0
        pThis_6133 = (*((uint32_t *)this + 1555) - pThis_6122) >> 2;  // this+6220〔pFrameVecEnd(推断)〕
      else  // 否则分支
        pThis_6133 = 0;
      if ( pThis_6122 == 0 || pThis_6133 >= (*((uint32_t *)this + 1556) - pThis_6122) >> 2 )  // 若 pThis_6122 == 0
      {
LABEL_150:  // 标签 LABEL_150（跳转合流点）
        sub_42AC90(pThis_1844, *(char **)(pThis_1844 + 8), 1u, &v85);  // 向量批量插入核心
        continue;  // 进入下一轮循环
      }
      pThis_6134 = *((int **)this + 1555);
      *pThis_6134 = v45;
      *((uint32_t *)this + 1555) = pThis_6134 + 1;  // this[1555] = pThis_6134 + 1
    }
  }
  if ( v86[211] != 0 )
  {
    if ( v86[212] < 0x10u )
      v53 = v86 + 207;
    else  // 否则分支
      v53 = (uint32_t *)v86[207];
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      pThis_16C = this + 364;
    else  // 否则分支
      pThis_16C = *((char **)this + 91);
    v55 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", pThis_16C, v53);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
    sub_4B2970((uint32_t *)this + 1579, v55);  // 部件记录拷贝（同 ·0x4B2820）
  }
  for ( Srcd = (char *)v86[214]; Srcd != (char *)v86[215]; Srcd += 4 )  // 遍历循环
  {
    if ( strcmp((const char *)sub_41ACF0(Srcd), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
    {
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
      v87 = 10;
      sub_4A3450(v80);
      v87 = 11;
      sub_4B52F0(v80);  // 152 字节记录 append（尾插一条）
      v87 = -1;
      if ( v83 >= 0x10 )  // 若 v83 >= 0x10
        j__free(Block);
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
    }
    else  // 否则分支
    {
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_16C2 = this + 364;
      else  // 否则分支
        pThis_16C2 = *((char **)this + 91);
      v57 = *(uint32_t *)dword_8F84E0;
      v58 = sub_41ACF0(Srcd);  // 驻留串句柄 → 字符串指针
      v59 = (*(int (**)(int, const char *, ...))(v57 + 12))(dword_8F84E0, "%s%s", pThis_16C2, v58);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      sub_4B52F0(v59);  // 152 字节记录 append（尾插一条）
    }
  }
  for ( Srce = (char *)v86[218]; Srce != (char *)v86[219]; Srce += 4 )  // 遍历循环
  {
    if ( strcmp((const char *)sub_41ACF0(Srce), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
    {
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
      v87 = 12;
      sub_4A3450(v80);
      v87 = 13;
      sub_4B52F0(v80);  // 152 字节记录 append（尾插一条）
      v87 = -1;
      if ( v83 >= 0x10 )  // 若 v83 >= 0x10
        j__free(Block);
      v83 = 15;
      v82 = 0;
      LOBYTE(Block) = 0;
    }
    else  // 否则分支
    {
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
        pThis_16C3 = this + 364;
      else  // 否则分支
        pThis_16C3 = *((char **)this + 91);
      v61 = *(uint32_t *)dword_8F84E0;
      v62 = sub_41ACF0(Srce);  // 驻留串句柄 → 字符串指针
      v63 = (*(int (**)(int, const char *, ...))(v61 + 12))(dword_8F84E0, "%s%s", pThis_16C3, v62);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      sub_4B52F0(v63);  // 152 字节记录 append（尾插一条）
    }
  }
  v64 = v86;
  v79 = (int)(v86 + 221);
  pThis_1542 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);  // 调虚槽 +340：三元组基址（+284，vt+340）
  sub_4ED3F0(pThis_1542 + 60, v79);  // int 向量拷贝赋值（全容量路径）
  pThis_1E90 = this + 7824;  // this+7824〔nGrabH〕
  v67 = v64 + 239;
  for ( Srcf = 29; Srcf != 0; --Srcf )  // 循环：Srcf 从 29 递减到 0
  {
    sub_41DC80(v67);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
    v67 += 4;
    pThis_1E90 += 16;
  }
  *(uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) = nArg3;  // 调虚槽 +672：自身 HP
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  *((uint32_t *)this + 162) |= 1u;  // this+648〔uMonFlagBits〕
  pMem = (int *)operator new(0x58u);  // new(88 字节) 分配对象
  pMem3 = pMem;
  v87 = 14;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    *pMem = (int)&IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
    sub_4B0D60((uint8_t *)v68 + 4);  // 计时子对象初始化（时钟域 2）
    LOBYTE(v87) = 15;
    sub_5F6610(v69);
    sub_5F6750(v69);
    LOBYTE(v87) = 16;
    *v69 = (int)&CNSpeedControl::`vftable';  // 构造装配 vftable：CNSpeedControl
    sub_5FE160(pMem3);
    nullsub_3(pMem3);
    pMem32 = pMem3;
  }
  else  // 否则分支
  {
    pMem32 = nullptr;  // pMem32 = 空指针
  }
  *((uint32_t *)this + 1931) = pMem32;
  v71 = *pMem32;
  v87 = -1;
  (*(void (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v71 + 56))(pMem32, this, this, 0, 0, 0, -1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
  pMem2 = (int *)operator new(0x60u);  // new(96 字节) 分配对象
  pMem22 = pMem2;
  v87 = 17;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
  {
    *pMem2 = (int)&IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
    sub_4B0D60((uint8_t *)v72 + 4);  // 计时子对象初始化（时钟域 2）
    LOBYTE(v87) = 18;
    sub_5F6610(v73);
    sub_5F6750(v73);
    LOBYTE(v87) = 19;
    *v73 = (int)&CNMovementController::`vftable';  // 构造装配 vftable：CNMovementController
    nullsub_3(pMem22);
    nullsub_3(pMem22);
    pMem222 = pMem22;
  }
  else  // 否则分支
  {
    pMem222 = nullptr;  // pMem222 = 空指针
  }
  *((uint32_t *)this + 1932) = pMem222;
  v75 = *pMem222;
  v87 = -1;
  result = (*(int (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v75 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
             pMem222,
             this,
             this,
             0,
             0,
             0,
             -1);
  *((uint32_t *)this + 1837) = 100;
  qmemcpy(this + 8368, unk_6F8B68, 104);  // this+8368〔nCoordB〕
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    pThis_533 = *((uint32_t *)this + 83);  // this+332〔bReservedConn〕
    if ( pThis_533 == 0 )  // 若 pThis_533 为 0
      break;  // 跳出循环/分支
    result = (*((uint32_t *)this + 84) - pThis_533) >> 2;  // 向量元素数 = (end−begin)/4
    if ( i >= result )  // 若 i >= result
      break;  // 跳出循环/分支
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 464))(this, *(uint32_t *)(pThis_533 + 4 * i));  // 调虚槽 +464
  }
  return result;
}


// ------------------------------------------------------------
// 0x4E3360 sub_4E3360 —— 怪物资源侧析构（释放三块 + 全局怪物计数递减）
// 释放 this+7820 / +8360 / +8364（帧对象 ·sub_42AF90 + ·sub_657740(228)）→ --dword_9A05D4
// ------------------------------------------------------------
int /*thiscall*/ sub_4E3360(int this)  // 实现：怪物资源侧析构（释放三块 + 全局怪物计数递减）
{
  void *fld_20A8; // eax
  void **fld_20AC; // edi

  if ( *(uint32_t *)(this + 7820) != 0 )  // this+7820〔pInteractSnap(推断)〕
    j__free(*(void **)(this + 7820));  // 释放 this+7820〔pInteractSnap(推断)〕堆块
  fld_20A8 = *(void **)(this + 8360);  // this+8360〔pPickInfo8360(推断)〕
  *(uint32_t *)(this + 7820) = 0;  // this+7820〔pInteractSnap(推断)〕
  if ( fld_20A8 != nullptr )  // 若 fld_20A8 有效（非空）
    j__free(fld_20A8);
  fld_20AC = *(void ***)(this + 8364);  // this+8364〔pFrameObject(推断)〕
  *(uint32_t *)(this + 8360) = 0;  // this+8360〔pPickInfo8360(推断)〕
  if ( fld_20AC != nullptr )  // 若 fld_20AC 有效（非空）
  {
    sub_42AF90(fld_20AC);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_20AC, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 8364) = 0;  // this+8364〔pFrameObject(推断)〕
  return --dword_9A05D4;  // 全局 竞技场/PVP 深度计数
}



// ------------------------------------------------------------
// 0x4E33D0 sub_4E33D0 —— 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
// 旧态 ·this+6556：2 → ·sub_4D83E0 惊叹气泡；4 且 a2==1 → ·sub_4DB200(28) + vt+1068；5 → 错误日志 off_77F3FC(aCriticalErrorI,…)；8/10 → ·sub_4D93D0 / ·this+8288 = -1；
// 新态 a2：3 → ·sub_4DB200(21)；5 → ·sub_4DB200(22) + 时值 ·this+7768（PVP 场景 = 1000ms，否则 rand → ·sub_423A80(100,250,…,100)）+ 碎击件 ·sub_4DF0C0 + ·sub_45FE80 + 定位；
// 8 → ·sub_4D9360 + ·sub_4DB200；10 → 写 ·this+8288；13 变身：vt+196(·this+1540) 换外观件、vt+596/604(0) 关双盒、载 Unsummon.ani 缩放 0.008 → vt+204 播；尾调 vt+1D8(·sub_58E920)
// ------------------------------------------------------------
void /*userpurge*/ sub_4E33D0(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int pArg4, float fArg5, float fArg6)  // 实现：大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
{
  int v7; // edi
  uint32_t *v8; // edi
  uint32_t *v9; // eax
  int pArg42; // ebx
  int v11; // eax
  void *v12; // edi
  int v13; // ebx
  int v14; // eax
  int nRand; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int *v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // [esp-10h] [ebp-30h]
  int v25; // [esp-Ch] [ebp-2Ch]
  void *v27; // [esp+Ch] [ebp-14h]
  int v28; // [esp+10h] [ebp-10h]
  float v29; // [esp+2Ch] [ebp+Ch]

  v7 = pDwArg1[1639];  // v7 = 取 pDwArg1[1639]
  v28 = v7;
  if ( v7 != 11 || ArgList == 12 )  // 若 v7 != 11 与/或 ArgList == 12
  {
    switch ( v7 )  // 按 v7 分派
    {
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        sub_4D83E0(0, 0);  // 头顶气泡 Exclamation.ani（惊叹；同 0x4D82D0 结构）
        goto LABEL_11;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        if ( ArgList == 1 )  // 若 ArgList == 1
        {
          sub_4DB200(28, -1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
          (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1068))(pDwArg1);  // 调虚槽 +1068
        }
        goto LABEL_11;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        v8 = *(uint32_t **)(*(uint32_t *)(pDwArg1[29] + 132) + 44);
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 340))(pDwArg1);  // 调虚槽 +340：三元组基址（+284，vt+340）
        off_77F3FC(aCriticalErrorI, ArgList, *v9, *v8);  // 引擎日志输出函数(printf 风格)
        return;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        if ( *((uint8_t *)pDwArg1 + 7559) == 1 )
          sub_4D93D0(pDwArg1);
        goto LABEL_11;
      case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
        pDwArg1[2072] = -1;
        goto LABEL_11;
      default:  // 默认分支
LABEL_11:  // 标签 LABEL_11（跳转合流点）
        pArg42 = pArg4;
        switch ( ArgList )  // 按 ArgList 分派
        {
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
            sub_4DB200(21, -1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
            break;  // 跳出循环/分支
          case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            sub_4DB200(22, -1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
            v12 = **(void ***)(pArg4 + 4);  // pArg4+4〔宿主对象〕
            v27 = v12;
            if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )  // 登录/选区管理器
            {
              pDwArg1[1942] = 1000;
            }
            else  // 否则分支
            {
              v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
              v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 52))(pDwArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
              srand(v14 * v13);
              nRand = rand();  // nRand = 调 rand
              pArg42 = pArg4;
              pDwArg1[1942] = sub_423A80(100, 250, nRand % 101, 100);  // 同上 int 版（FTOL 截断）
            }
            if ( v12 != nullptr )  // 若 v12 有效（非空）
            {
              if ( *(uint32_t *)(dword_8F7A24 + 244) != 2 && pDwArg1[1822] == 0 )  // 登录/选区管理器
              {
                v16 = ~pDwArg1[1824];
                if ( operator new(0x148u) != nullptr )  // new(328 字节) 分配对象
                {
                  v25 = pDwArg1[1942];  // v25 = 取 pDwArg1[1942]
                  v24 = pDwArg1[1823];  // v24 = 取 pDwArg1[1823]
                  v17 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 672))(pDwArg1, 3);  // 调虚槽 +672：自身 HP
                  v18 = sub_4B0D20(v17);  // 双字段乘积取值
                  v19 = (int *)sub_4DF0C0(v27, v18, v24, v25, v16);  // CNPieceDestroyEffect 构造（vftable + sub_5FE330 基类 +
                }
                else  // 否则分支
                {
                  v19 = nullptr;  // v19 = 空指针
                }
                sub_45FE80(pDwArg1[29], (int)v19, 2, 0, (int)v19, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
                v20 = *v19;
                v21 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
                v22 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[40] / 2 + v21);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
                v23 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v22);  // 调虚槽 +120：动画对象
                (*(void (/*thiscall*/ **)(int *, int))(v20 + 112))(v19, v23);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
                pArg42 = pArg4;
              }
              if ( *(uint32_t *)(dword_8F7A24 + 244) != 2  // 登录/选区管理器
                && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 1020))(pDwArg1) == 0 )  // 调虚槽 +1020：CNSwordman__vmt3FC
              {
                (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 260))(pDwArg1, 1, 5, -1);  // 调虚槽 +260
              }
            }
            else  // 否则分支
            {
              (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1256))(pDwArg1);  // 调虚槽 +1256
            }
            v7 = v28;
            break;  // 跳出循环/分支
          case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
            if ( *((uint8_t *)pDwArg1 + 7559) == 1 )
              sub_4D9360(pDwArg1);
            sub_4DB200(**(uint32_t **)(pArg4 + 4), -1);  // 15% 概率随机文案触发（0x4DB130 的门包装）
            break;  // 跳出循环/分支
          case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
            pDwArg1[2072] = **(uint32_t **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
            break;  // 跳出循环/分支
          case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
            if ( pDwArg1[30] == pDwArg1[1540] )
              LOBYTE(fArg6) = 0;
            else  // 否则分支
              (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 196))(pDwArg1, pDwArg1[1540]);  // 调虚槽 +196：动画对象设置（换域 + 播放）
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pDwArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
              pDwArg1,
              0,
              0,
              0,
              0,
              0,
              0,
              nArg2);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
              pDwArg1,
              1,
              0,
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 596))(pDwArg1, 0);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
            (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 612))(pDwArg1, 1, 2);  // 调虚槽 +612
            if ( pDwArg1[2091] == 0 )
            {
              if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
                v11 = sub_431860((char)"Monster/Common/Animation/Unsummon.ani", 1);  // 动画件构造（资源 id 版）
              else  // 否则分支
                v11 = 0;
              pDwArg1[2091] = v11;
            }
            v29 = (double)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1) * 0.0080000004;  // 调虚槽 +192
            sub_4920E0((uint32_t *)pDwArg1[2091], v29, v29);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
            (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
              pDwArg1,
              1,
              pDwArg1[2091],
              0,
              0,
              1,
              0);
            break;  // 跳出循环/分支
          default:  // 默认分支
            break;  // 跳出循环/分支
        }
        sub_58E920(pDwArg1, ArgList, pArg42, fArg5, fArg6);  // 【IRDActiveObject__vmt1D8】
        if ( v7 == 3 || v7 == 8 )  // 若 v7 == 3 与/或 v7 == 8
          (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1240))(pDwArg1);  // 调虚槽 +1240
        break;  // 跳出循环/分支
    }
  }
}


// ------------------------------------------------------------
// 0x4E3820 sub_4E3820 —— Boss 终局演出件（LastStrikeForKillBoss.ani）
// 载 Common/CommonEffect/Animation/LastStrikeForKillBoss.ani → 池化对象(·sub_44B6C0(284) + ·sub_44E0D0)；
// ·sub_45FE80(this+29, 件, 2,…) 入演播 → vt+112 定位（pArg2 的 x/y/z）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E3820(int *this, float *pArg2)  // 实现：Boss 终局演出件（LastStrikeForKillBoss.ani）
{
  int v3; // edi
  char *v4; // eax
  int pObj; // esi

  v3 = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v3 = sub_431860((char)"Common/CommonEffect/Animation/LastStrikeForKillBoss.ani", 1);  // 动画件构造（资源 id 版）
  v4 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj = (int)v4;
  if ( v4 != nullptr )  // 若 v4 有效（非空）
  {
    sub_44E0D0(v4, v3, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pObj = 0;
  }
  sub_45FE80(*(this + 29), v3, 2, 0, pObj, (int)this, 0);  // 调 实体对象注册到演播层
  return (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
           pObj,
           (uint64_t)*pArg2 >> 32,
           (uint64_t)*pArg2,
           (uint64_t)pArg2[1],
           (uint64_t)pArg2[2]);
}



// ------------------------------------------------------------
// 0x4E38F0 sub_4E38F0 —— 精怪(Champion)外观装配（元素 5 选 1 → 4 组件 + 光环/部件）
// ·this+7772 = nArg4 档位；元素 ·this+2148 从资源 +1424 表随机（否则 rand()%4+1）→ fire/water/dark/light/none；
// 4 个模板 Monster/Common/Animation/Champion/%sBottomB.ani 族加载 + ·sub_4920E0 缩放 + 池化挂层序(2/2/1/1) + ·sub_4A06D0；
// 元素 0..3 → ·sub_4DF1B0 光环件 + 高度/宽调整；档位 2 → 改名与 ·sub_5FE2C0(64.0f)；标签 196621/196354/261641.. 等 → 属性槽 ×1.5/×2/×2.5 与 4 个附加件
// ------------------------------------------------------------
char /*thiscall*/ sub_4E38F0(int *this, int nArg2, int pArg3, int nArg4)  // 实现：精怪(Champion)外观装配（元素 5 选 1 → 4 组件 + 光环/部件）
{
  unsigned int v4; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // ebx
  int v10; // ebx
  int *pThis_6FD; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // ecx
  int v15; // eax
  char *v16; // ebx
  int v17; // edx
  int **v18; // eax
  int **v19; // eax
  int v20; // eax
  int v21; // ecx
  double v22; // st7
  char *v23; // eax
  int pObj2; // edi
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int fld_e2148; // eax
  int v32; // edx
  unsigned int v33; // edi
  int v34; // edx
  unsigned int v35; // edi
  void *pMem; // eax
  int fld_e21482; // edi
  int v38; // eax
  int fld_e21483; // edi
  int v40; // eax
  uint32_t *v41; // eax
  uint64_t v42; // rax
  int fld_e21484; // edi
  int v44; // ebx
  int64_t v45; // rax
  int v46; // ecx
  unsigned int v47; // edi
  int v48; // eax
  int v49; // edx
  const char *v50; // edi
  const char *pThis_49; // ecx
  const char *fld_e21485; // eax
  size_t *v53; // eax
  int v54; // ebx
  unsigned int v55; // edi
  uint64_t v56; // rax
  int v57; // edi
  int v58; // eax
  int v59; // eax
  int *v60; // eax
  int v61; // edx
  unsigned int v62; // edi
  uint64_t v63; // rax
  unsigned int v64; // edi
  unsigned int v65; // edi
  uint64_t v66; // rax
  unsigned int v67; // edi
  uint64_t v68; // rax
  unsigned int v69; // edi
  void *pMem3; // eax
  int pObj3; // edi
  int v72; // eax
  void *pMem4; // eax
  int pObj5; // edi
  int v75; // eax
  void *pMem5; // eax
  int pObj4; // edi
  int v78; // eax
  void *pMem6; // eax
  int pObj; // edi
  int v81; // eax
  int v82; // eax
  int *fld_e1545; // esi
  int v84; // eax
  int v85; // eax
  const char *pThis_492; // [esp-4h] [ebp-338h]
  uint32_t v88[5]; // [esp+Ch] [ebp-328h]
  uint32_t v89[4]; // [esp+20h] [ebp-314h]
  char *Format[4]; // [esp+30h] [ebp-304h]
  uint32_t v91[4]; // [esp+40h] [ebp-2F4h]
  uint32_t v92[4]; // [esp+50h] [ebp-2E4h]
  uint32_t v93[4]; // [esp+60h] [ebp-2D4h]
  uint32_t v94[4]; // [esp+70h] [ebp-2C4h]
  uint32_t v95[4]; // [esp+80h] [ebp-2B4h]
  float v96; // [esp+90h] [ebp-2A4h]
  float v97; // [esp+94h] [ebp-2A0h]
  void *pMem2; // [esp+98h] [ebp-29Ch] BYREF
  float v99; // [esp+9Ch] [ebp-298h]
  void *Block; // [esp+A0h] [ebp-294h]
  char Buffer[512]; // [esp+A4h] [ebp-290h] BYREF
  char Src[128]; // [esp+2A4h] [ebp-90h] BYREF
  int dword_796E502; // [esp+324h] [ebp-10h]
  int v104; // [esp+330h] [ebp-4h]
  unsigned int v105; // [esp+33Ch] [ebp+8h]
  float v106; // [esp+33Ch] [ebp+8h]
  int v107; // [esp+344h] [ebp+10h]
  int v108; // [esp+344h] [ebp+10h]

  v4 = 0;
  dword_796E502 = dword_796E50;
  v6 = *this;
  v92[0] = 0;
  v92[1] = 10;
  v92[2] = 20;
  v92[3] = 0;
  v91[0] = 0;
  v91[1] = 1050253722;  // 浮点常量 0.3f
  v91[2] = 1056964608;  // 浮点常量 0.5f
  v91[3] = 0;
  v93[0] = 0;
  v93[1] = 1069547520;  // 浮点常量 1.5f
  v93[2] = 0x40000000;
  v93[3] = 0;
  v94[0] = 0;
  v94[1] = 1069547520;  // 浮点常量 1.5f
  v94[2] = 1077936128;  // 浮点常量 3.0f
  v94[3] = 0;
  pMem2 = (void *)(*(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(v6 + 672))(this, 3) - 1);  // 调虚槽 +672：自身 HP
  v7 = *this;
  pMem2 = (void *)(uint64_t)((double)(int)pMem2 * 0.2 + 2.0);
  v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + v8;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v10 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v9;  // 调虚槽 +120：动画对象
  v105 = v10 + nArg2 + (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  srand(v105);
  *(this + 1943) = nArg4;  // this+7772〔nCounterState〕
  if ( (unsigned int)*(this + 1794) < 0x10 )  // this+7176〔nNameStrCap〕
    pThis_6FD = this + 1789;
  else  // 否则分支
    pThis_6FD = (int *)*(this + 1789);  // this+7156〔bParam3(推断)〕
  v12 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, pThis_6FD);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v13 = v12;
  v14 = *(uint32_t *)(v12 + 1424);
  if ( v14 != 0 && (*(uint32_t *)(v12 + 1428) - v14) >> 2 != 0 )  // 若 v14 != 0
  {
    v15 = *(uint32_t *)(v12 + 1424);
    if ( v15 != 0 )  // 若 v15 非 0
      v4 = (*(uint32_t *)(v13 + 1428) - v15) >> 2;  // 向量元素数 = (end−begin)/4
    *(this + 2148) = *(uint32_t *)(*(uint32_t *)(v13 + 1424) + 4 * (rand() % v4));
  }
  else  // 否则分支
  {
    *(this + 2148) = rand() % 4 + 1;  // rand()%4 取模随机
  }
  v16 = nullptr;  // v16 = 空指针
  v88[0] = "fire";
  v88[1] = "water";
  v88[2] = "dark";
  v88[3] = "light";
  v88[4] = "none";
  Format[0] = "Monster/Common/Animation/Champion/%sBottomB.ani";  // 动画 .ani Monster/Common/Animation/Champion/%sBottomB.ani
  Format[1] = "Monster/Common/Animation/Champion/%sBottomF.ani";  // 动画 .ani Monster/Common/Animation/Champion/%sBottomF.ani
  Format[2] = "Monster/Common/Animation/Champion/%sBackB.ani";  // 动画 .ani Monster/Common/Animation/Champion/%sBackB.ani
  Format[3] = "Monster/Common/Animation/Champion/%sBackF.ani";  // 动画 .ani Monster/Common/Animation/Champion/%sBackF.ani
  v95[0] = 0;
  v95[1] = 0;
  v95[2] = -1;
  v95[3] = 1;
  v89[0] = 2;
  v89[1] = 2;
  v89[2] = 1;
  v89[3] = 1;
  for ( Block = nullptr; (int)Block < 16; Block = (char *)Block + 4 )  // 遍历循环
  {
    sprintf(Buffer, *(const char *const *)((char *)Format + (uint32_t)v16), v88[*(this + 2148)]);  // 拼字符串
    v99 = COERCE_FLOAT(sub_42FCB0(228));  // CRT 一次性初始化
    v104 = 0;
    if ( v99 == 0.0 )
      v99 = 0.0;
    else  // 否则分支
      v99 = COERCE_FLOAT(sub_431860((char)Buffer, 1));  // 动画件构造（资源 id 版）
    v17 = *this;
    v104 = -1;
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(v17 + 688))(this) != 0 )  // 调虚槽 +688：附加块基址 this+6160
    {
      v18 = (int **)(*(int (/*thiscall*/ **)(int *))(*this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
      if ( sub_4924C0(*v18, 0) != 0 )  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      {
        v19 = (int **)(*(int (/*thiscall*/ **)(int *))(*this + 688))(this);  // 调虚槽 +688：附加块基址 this+6160
        v20 = sub_4924C0(*v19, 0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
        v21 = *(uint32_t *)v20;
        if ( *(uint32_t *)v20 != 0 )
        {
          v22 = (double)*(unsigned int *)(v21 + 20);
          v96 = *(float *)(v21 + 24);
          v97 = v22 * 1.5 * *(float *)(v20 + 20) * 0.0052910051;
          v96 = (double)LODWORD(v96) * 1.5 * *(float *)(v20 + 24) * 0.0047846888;
          if ( v97 > 1.0 )
            v97 = 1.0;
          if ( v96 > 1.0 )
            v96 = 1.0;
          sub_4920E0((uint32_t *)LODWORD(v99), v97, v96);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
        }
      }
    }
    v23 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    pObj2 = (int)v23;
    v97 = *(float *)&v23;
    v104 = 1;
    if ( v23 != nullptr )  // 若 v23 有效（非空）
    {
      sub_44E0D0(v23, SLODWORD(v99), 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pObj2 = 0;
    }
    v25 = *(uint32_t *)pObj2;
    v104 = -1;
    (*(void (/*thiscall*/ **)(int))(v25 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 8) = *(uint32_t *)((char *)v89 + (uint32_t)v16);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 实体对象注册到演播层
    v26 = *(uint32_t *)pObj2;
    v27 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v27);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, *(uint32_t *)((char *)v95 + (uint32_t)Block) + v28);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int, int))(v26 + 112))(pObj2, v29);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    v30 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj2 + 60))(pObj2, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    sub_4A06D0(v30, 2);  // 调 绑定目标对象并记录相对偏移
    v16 = (char *)Block + 4;
  }
  fld_e2148 = *(this + 2148);
  if ( fld_e2148 >= 0 )  // 若 fld_e2148 >= 0
  {
    if ( fld_e2148 <= 3 )  // 若 fld_e2148 <= 3
    {
      pMem = operator new(0x84u);  // new(132 字节) 分配对象
      Block = pMem;
      v104 = 2;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        fld_e21482 = sub_4DF1B0((int)pMem, v92[nArg4], *(this + 2148), 0, -1);  // CNEnchantWeapon 构造
      else  // 否则分支
        fld_e21482 = 0;
      v38 = *(uint32_t *)fld_e21482;
      v104 = -1;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v38 + 64))(fld_e21482) + 40) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)fld_e21482 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        fld_e21482,
        this,
        this,
        0,
        0,
        0,
        -1);
      fld_e21483 = *(this + 2148);
      v40 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
      v41 = (uint32_t *)sub_41A5E0(v40 + 14 * fld_e21483 + 172);  // crypt4byte 解密校验（·0x41A590 逆运算）
      Block = (void *)(150 - (uint32_t)v41);
      v99 = *(float *)&v41;
      v42 = (uint64_t)((double)(150 - (int)v41) * *(float *)&v91[nArg4] + (double)(int)v41);
      fld_e21484 = *(this + 2148);
      v44 = v42;
      v45 = ((int64_t (/*fastcall*/ *)(int *, uint32_t, uint32_t))*(uint32_t *)(*this + 672))(this, HIDWORD(v42), 0);  // 调虚槽 +672：自身 HP
      sub_41A590(v45 + 14 * fld_e21484 + 172, SHIDWORD(v45), v44);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
    else if ( fld_e2148 == 4 )
    {
      v32 = *this;
      v99 = *(float *)&v93[nArg4];
      v33 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v32 + 672))(this, 0) + 60;  // 调虚槽 +672：自身 HP
      Block = (void *)sub_41A5E0(v33);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v33, (uint64_t)((double)(int)Block * v99) >> 32, (uint64_t)((double)(int)Block * v99));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v34 = *this;
      v99 = *(float *)&v93[nArg4];
      v35 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v34 + 672))(this, 0) + 88;  // 调虚槽 +672：自身 HP
      Block = (void *)sub_41A5E0(v35);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v35, (uint64_t)((double)(int)Block * v99) >> 32, (uint64_t)((double)(int)Block * v99));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
  }
  v46 = *(uint32_t *)(pArg3 + 4);  // pArg3+4〔宿主对象〕
  if ( v46 != 0 && (*(uint32_t *)(pArg3 + 8) - v46) >> 2 != 0 )  // 若 v46 != 0
    sub_4E1560(this, pArg3, &pMem2);  // 遍历 id 列表逐个追加（uArg3 为配额槽）
  else  // 否则分支
    sub_4E14E0(this, v105, (int *)&pMem2);  // 随机抽样追加（上限 13500 次，附排除值表）
  v47 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 466;  // 调虚槽 +672：自身 HP
  v48 = sub_41A5E0(v47);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v47, v49, v48 + 50);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  if ( *(this + 1943) == 2 )  // this+7772〔nCounterState〕
    v50 = (const char *)sub_422E70(1605);  // v50 = 调 sub_422E70 返回值
  else  // 否则分支
    v50 = szPassword;
  if ( (unsigned int)*(this + 78) < 0x10 )
    pThis_49 = (const char *)(this + 73);  // this+292〔nOpenMode292(推断)〕
  else  // 否则分支
    pThis_49 = (const char *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
  pThis_492 = pThis_49;
  fld_e21485 = (const char *)sub_422E70(*(this + 2148) + 1600);  // fld_e21485 = 调 sub_422E70 返回值
  sprintf(Src, "%s%s%s", v50, fld_e21485, pThis_492);  // 拼字符串（模板 %s%s%s）
  v53 = (size_t *)((*(int (/*thiscall*/ **)(int *))(*this + 340))(this) + 4);  // 调虚槽 +340：三元组基址（+284，vt+340）
  sub_4015C0(v53, Src, strlen(Src));  // 【std::string构造赋值】
  v54 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
  v106 = *(float *)&v94[nArg4];
  v55 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 4;  // 调虚槽 +672：自身 HP
  v56 = (uint64_t)((double)sub_41A5E0(v55) * v106);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v55, SHIDWORD(v56), v56);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  v57 = *this;
  v58 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 740))(this, 0, 1);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
  (*(void (/*thiscall*/ **)(int *, int))(v57 + 732))(this, v58);  // 调虚槽 +732：CNMapObject__vmt2DC
  v59 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
  off_77F3FC(aApplychamp, v54, v59);  // 引擎日志输出函数(printf 风格)
  if ( *(this + 1943) == 2 )  // this+7772〔nCounterState〕
  {
    pMem2 = operator new(0x84u);  // new(132 字节) 分配对象
    v104 = 3;
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
      v60 = (int *)sub_5FE2C0(1120403456);  // v60 = 调 sub_5FE2C0 返回值
    else  // 否则分支
      v60 = nullptr;  // v60 = 空指针
    v61 = *v60;
    v104 = -1;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v61 + 56))(v60, this, this, 0, 0, 0, -1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
  }
  if ( sub_4DB0E0(this, 196621) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    v62 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 816;  // 调虚槽 +672：自身 HP
    v63 = (uint64_t)((double)sub_41A5E0(v62) * 1.5);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v62, SHIDWORD(v63), v63);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( sub_4DB0E0(this, 196622) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    v64 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 844;  // 调虚槽 +672：自身 HP
    v107 = sub_41A5E0(v64);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v64,
      (uint64_t)((double)v107 + (double)v107) >> 32,
      (uint64_t)((double)v107 + (double)v107));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( sub_4DB0E0(this, 196354) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    v65 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 88;  // 调虚槽 +672：自身 HP
    v66 = (uint64_t)((double)sub_41A5E0(v65) * 2.5);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v65, SHIDWORD(v66), v66);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( sub_4DB0E0(this, 196355) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    v67 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 144;  // 调虚槽 +672：自身 HP
    v68 = (uint64_t)((double)sub_41A5E0(v67) * 2.5);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v67, SHIDWORD(v68), v68);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( sub_4DB0E0(this, 262159) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    v69 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 900;  // 调虚槽 +672：自身 HP
    v108 = sub_41A5E0(v69);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v69,
      (uint64_t)((double)v108 + (double)v108) >> 32,
      (uint64_t)((double)v108 + (double)v108));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( sub_4DB0E0(this, 261641) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    pMem3 = operator new(0x84u);  // new(132 字节) 分配对象
    pMem2 = pMem3;
    v104 = 4;
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
      pObj3 = sub_4DF1B0((int)pMem3, 5, 0, 0, -1);  // CNEnchantWeapon 构造
    else  // 否则分支
      pObj3 = 0;
    v72 = *(uint32_t *)pObj3;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v72 + 64))(pObj3) + 40) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj3,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261642) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    pMem4 = operator new(0x84u);  // new(132 字节) 分配对象
    pMem2 = pMem4;
    v104 = 5;
    if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
      pObj5 = sub_4DF1B0((int)pMem4, 5, 1, 0, -1);  // CNEnchantWeapon 构造
    else  // 否则分支
      pObj5 = 0;
    v75 = *(uint32_t *)pObj5;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v75 + 64))(pObj5) + 40) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj5 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj5,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261643) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    pMem5 = operator new(0x84u);  // new(132 字节) 分配对象
    pMem2 = pMem5;
    v104 = 6;
    if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
      pObj4 = sub_4DF1B0((int)pMem5, 5, 3, 0, -1);  // CNEnchantWeapon 构造
    else  // 否则分支
      pObj4 = 0;
    v78 = *(uint32_t *)pObj4;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v78 + 64))(pObj4) + 40) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj4 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj4,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( sub_4DB0E0(this, 261644) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  {
    pMem6 = operator new(0x84u);  // new(132 字节) 分配对象
    pMem2 = pMem6;
    v104 = 7;
    if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
      pObj = sub_4DF1B0((int)pMem6, 5, 2, 0, -1);  // CNEnchantWeapon 构造
    else  // 否则分支
      pObj = 0;
    v81 = *(uint32_t *)pObj;
    v104 = -1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v81 + 64))(pObj) + 40) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  LOBYTE(v82) = sub_4DB0E0(this, 262160);  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  if ( (uint8_t)v82 != 0 )
  {
    fld_e1545 = (int *)*(this + 1545);  // this+6180〔pAtkCtxC6180〕
    if ( fld_e1545 != nullptr )  // 若 fld_e1545 有效（非空）
    {
      v84 = fld_e1545[11];  // v84 = 取 fld_e1545[11]
      if ( v84 != 0 )  // 若 v84 非 0
        v85 = (fld_e1545[12] - v84) / 88;
      else  // 否则分支
        v85 = 0;
      v82 = sub_4924C0(fld_e1545, v85 - 1);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(v82 + 48) = 0;
    }
  }
  return v82;
}


// ============================================================
// 【分区 B】HP 受击处理器 + 攻方表现载荷 + 动作数据包（0x4E4430 - 0x4E5030）
//   ★ 本区是研究 20 §8「双向卡肉」与 P35「HP 受击/Boss 终局」的落点。
// ============================================================

// ------------------------------------------------------------
// 0x4E4430 sub_4E4430 —— ★ HP 受击处理器（含 Boss 终局；研究 P35 第 31 轮定案）
// 结构：取 vt+684（HP 读取）与 a2（新 HP）比较，不等时算 v9 = 旧HP − 新HP（本次伤害）。
//   ★ Boss/精怪终局分支（a2 == 0 即"归零 = 死亡"）：
//     sub_4DB0E0(131091) 持有该标签（研究 P35：131091 = 死亡终局技能/被动 id）
//     且 this 的 vt+80 容器 +153 字节为 0（非演出中）→
//       v7 = vt+740（最大 HP，作为"最终一击伤害值"）
//       vt+308 门（本地玩家对象）→ vt+580(this, 48001, 3, …, 4, …) 发包
//       → sub_4DE0E0(131091) 移除标签 + sub_49C970(8,0,0)/sub_49C5F0(9,0,0,2000) 表现
//   ★ 落地：sub_4D5900(v7, a3, a4)（HP setter 家族）
//   ★ 击杀归属：a3（攻击者）vt+576 车主非空且 v9 > 0 → sub_4DEE20(a3, v9) 记录伤害
//   ★ 终极演出（PVP 场景 3 且 this 大状态 == 3）：vt+724 门 → 全局计数 dword_9A05CC 递减，
//     归零时：+153 = 1 演出标志 + sub_424BB0(6000, 30, …)（★ 6 秒三相位长震，
//     P35 定案 "Boss 终局 = 6 秒三相位长震"）+ sub_432EA0("R_STAGE_FINALE") BGM 切换
//     + sub_4E3820 表现 + sub_4DC4D0 + vt+604(0) 死亡无敌 + sub_426820(…, 4, 0) 播报。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4430(char *this, int nArg2, int nArg3, char pszArg4)  // 【HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）】
{
  int nHpCur; // eax
  int result; // eax
  int nNewHp; // edi
  int nHpCur2; // eax
  int nDamage; // ebx

  nHpCur = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);  // vt+684 = HP 容器指针
  result = sub_41A5E0(nHpCur);  // 防篡读当前 HP（P24）
  nNewHp = nArg2;
  if ( result != nArg2 )  // HP 有变化才处理
  {
    nHpCur2 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);  // 调虚槽 +684：取攻击上下文
    nDamage = sub_41A5E0(nHpCur2) - nArg2;  // 本次伤害 = 旧 HP − 新 HP
    if ( nArg2 == 0  // ★ 归零 = 死亡（Boss/精怪终局分支）
      && (uint8_t)sub_4DB0E0(131091) != 0  // 持有终结技/被动标签 131091
      && *(uint8_t *)((*(int (**)(void))(*(uint32_t *)this + 80))() + 153) == 0 )  // 非演出中
    {
      nNewHp = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 740))(this);  // 最大 HP → 作为最终一击伤害值
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 本地玩家对象门
        (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
          this,
          48001,  // UDP 包 48001
          3,  // 子字段 = 3
          0,
          0,
          0,
          0,
          0,
          4,  // 状态码 4（死亡演出）
          0,
          0,
          0);
      sub_4DE0E0(131091);  // 移除终局标签
      sub_49C970(8, 0, 0);  // 池分配包装（this+4 复制为第 2/3 参）
      sub_49C5F0(9, 0, 0, 2000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
    }
    sub_4D5900(nNewHp, nArg3, pszArg4);  // ★ HP setter（落地）
    if ( nArg3 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 576))(nArg3) != 0 && nDamage > 0 )  // 调虚槽 +576
      sub_4DEE20(nArg3, nDamage);  // ★ 击杀归属：记录攻击者造成的伤害
    result = 3;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *((uint32_t *)this + 1943) == 3 )  // 场景 3 且 this+7772 == 3
    {
      result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 724))(this);  // vt+724 无敌/演出门
      if ( (uint8_t)result != 0 )
      {
        off_77F3FC((char *)&byte_6F9AA4, dword_9A05CC[0]);  // 引擎日志输出函数(printf 风格)
        result = --*(uint32_t *)dword_9A05CC;  // 全局计数递减
        if ( *(int *)dword_9A05CC <= 0 )  // 归零 → 终极演出
        {
          *(uint8_t *)(*((uint32_t *)this + 29) + 153) = 1;  // +153 = 演出中标志
          sub_424BB0(6000, 30, *((uint32_t *)this + 1814) == dword_8F7C04);  // 【布好的 smallShakeStart/longShakeAmp 状态在此推进：】★ 6000ms 三相位长震
          sub_432EA0("R_STAGE_FINALE", -1, 0, 0);  // BGM 切换
          sub_4E3820(this + 7777);  // Boss 终局演出件
          sub_4DC4D0(this);  // 宿主对象列表连带处理（死亡/清除族）(推断)
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 604))(this, 0);  // vt+604(0) 死亡无敌
          return sub_426820(*(uint32_t *)(*((uint32_t *)this + 29) + 132), 4, 0);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】横幅 4
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E4610 sub_4E4610 —— ★ 距上次受击毫秒（研究 §15 第 15 轮定案：vt+632）
// `this+1673 != −1` 时返回 当前时钟(this+16) − this+1673；否则 −1。
// 研究 §15 更正记录："vt+632 = 距上次受击毫秒（更正'连击数'误读）"——
// 写入点 = 0x4D9F20 / 0x4D8730（把时钟当前时刻存入 this+1673）。
// 消费点 = 连击/受击窗口判定（研究 §9 连击 1500ms 窗口的读侧之一）、0x4E5C10 等。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4610(uint32_t *this)  // 实现：距上次受击毫秒（研究 §15 第 15 轮定案：vt+632）
{
  int result; // eax

  result = -1;
  if ( *(this + 1673) != -1 )  // this+6692〔uUI6692〕
    return sub_699000((int)(this + 16)) - *(this + 1673);  // 【clock_now(clk)】
  return result;
}



// ------------------------------------------------------------
// 0x4E4630 sub_4E4630 —— ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
// 语义：true = "是敌人/不同阵营"。两段：
//   ① 若场景 == 6（战场）且双方 vt+376（阵营/队伍号）均落在 0..11 →
//      沿车主链 vt+576 上溯（条件 529 时取 v4[2088]，即"召唤主/变形主"链）跳过非战斗宿主；
//      终宿主条件 273（受击态）成立且 sub_4B09A0(v4) == 0 → 返回 **false**（同阵营判定为友）
//   ② 兜底：`this->vt+376 != a2->vt+376`（阵营号不同 = 敌人）
// 研究 §8 定案："vt+360 = 敌我关系判定（阵营比较 vs this+544）—— 攻方冻结豁免：
// 打队友不卡肉"；本函数是 vt+360 实现族的辅助（PVP/战场场景特化 + 召唤主上溯）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E4630(void *this, int nArg2)  // 实现：敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
{
  uint32_t *pThis_240; // esi
  int v5; // esi

  if ( nArg2 == 0 )  // 若 nArg2 为 0
    return false;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 6  // 登录/选区管理器
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) >= 0  // 调虚槽 +376：坐标同步包（type 37）
    && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) <= 11  // 调虚槽 +376：坐标同步包（type 37）
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) >= 0  // 调虚槽 +376：坐标同步包（type 37）
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) <= 11 )  // 调虚槽 +376：坐标同步包（type 37）
  {
    pThis_240 = (uint32_t *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);  // 调虚槽 +576
    if ( pThis_240 != nullptr )  // 若 pThis_240 有效（非空）
    {
      while ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis_240 + 40))(pThis_240, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        pThis_240 = (uint32_t *)pThis_240[2088];
        if ( pThis_240 == nullptr )  // 若 pThis_240 为空
          goto LABEL_11;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis_240 + 40))(pThis_240, 273) != 0 && sub_4B09A0(pThis_240) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        return false;
    }
  }
LABEL_11:  // 标签 LABEL_11（跳转合流点）
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调虚槽 +376：坐标同步包（type 37）
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) != v5;  // 调虚槽 +376：坐标同步包（type 37）
}



// ------------------------------------------------------------
// 0x4E4710 sub_4E4710 —— ★★ 攻方表现载荷（研究 20 §8 全文定案；★ 双向卡肉）
// this = 攻击者，a2 = 受击者，a3 = 命中盒，a4 = 格挡/暴击位。
// 反编译体与 §8 定案清单逐条对应（以 a2 为"受方"，this 为"攻方"）：
//   ① ★★★ 三重豁免门 + 攻方自我冻结：
//        `(受方 vt+308 != 0) || (攻方 vt+308 == 0) || (攻方 vt+360(攻,受) == 0)`
//        —— 研究 §8 定案："受方是玩家对象 或 攻方非玩家对象 或 受方是敌人"
//        等价于 **打敌人才卡肉、打队友不卡**；
//        v6 = this+130（= +520 字节偏移 → word 下标 130 = 字节 +520 ★ 攻方自身卡肉时长）
//        主状态 v7 = this+50（= 字节 +200）∈ {0} 或 {1 且 vt+248 剩余硬直 < v6} →
//        **vt+228(this, 1, v6, 0)** = 攻击者冻结自己 —— 与受击者同一入口、同一延长逻辑
//   ② vt+356(this, a2) —— 攻方自身命中特效（记录当前命中目标，研究 §1.2 vt+356）
//   ③ 无表现类判定：a2 条件 529 且 a2+7148 == 22（v18）；vt+648 伤害类型 → 3 或
//      （2 且伤 <= 0）→ v8 = 1（无表现）—— 研究 §8 "kind==3 或（==2 且伤≤0）= 无表现类"
//   ④ 可表现门：(this+404 标志 或 this+388 float > 0) 且 RTDynamicCast(受→IRDActiveObject)
//      成功 → v12 = 受方 vt+128(X) > 0 且 vt+840 大状态 == 4（**= 本次为击杀**）
//   ⑤ 本地玩家出手门：`dword_8F7C04 == 攻方 vt+576` 且 this+116 != 0 →
//      **sub_428050(v12, a4, a3)** = ★ 连击/击杀处理（研究 §9；宿主 ECX = 技能对象+132）
//   ⑥ 技能钩子：技能对象(this+116 → +132 → +52) == 攻方车主 → sub_4684F0(受)
//      （研究 §8：目标 HUD 更新，怪物血条宽 = 等级比 × 160/300、上限 475px）
//   ⑦ a4 == 0 → vt+540(this, 受) 攻方收尾（命中语音，研究 §1.2/§8）
// 研究 §8 第 10 轮补充的豁免门完整语义：投射物/使魔不卡肉的机制不在门上，
// 而是它们 this+520 基础值为 0（vt+1184 取空，见 sub_4AF8E0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4710(int *this, uint32_t *pArg2, int nArg3, char pszArg4)  // 【攻方表现载荷（ 双向卡肉，研究 §8 全文定案）】
{
  int nOwnStuckMs; // ebx
  int nMainState; // eax
  char bNoShow; // bl
  int pVictimVt; // edx
  int nDmgKind; // eax
  int pVictimObj; // ecx
  BOOL bKillFlag; // ebx
  int pSceneObj; // eax
  int nOwnerUid; // ebx
  int pVictimObjBak; // [esp+Ch] [ebp-8h]
  int nArgOut; // [esp+10h] [ebp-4h] BYREF
  bool bSkipFX; // [esp+1Fh] [ebp+Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0  // 门①：受方是玩家对象
    || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0  // 或攻方非玩家对象
    || (*(uint8_t (/*thiscall*/ **)(int *, uint32_t *))(*this + 360))(this, pArg2) == 0 )  // 或受方是敌人
  {
    nOwnStuckMs = *(this + 130);  // this+520 = ★ 攻方自身卡肉时长
    if ( nOwnStuckMs > 0 )  // 若 nOwnStuckMs > 0
    {
      nMainState = *(this + 50);  // this+200 = 主状态
      if ( nMainState == 0 || nMainState == 1 && (*(int (/*thiscall*/ **)(int *))(*this + 248))(this) < nOwnStuckMs )  // 调虚槽 +248：区间长 = vt+244 - vt+240
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 228))(this, 1, nOwnStuckMs, 0);  // ★★ 攻方自我冻结（与 §8 同一入口）
    }
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t *))(*this + 356))(this, pArg2);  // vt+356 记录当前命中目标
  bSkipFX = false;
  bNoShow = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 529) != 0 )  // 受方条件 529 = 怪物
    bSkipFX = pArg2[1787] == 22;  // 大状态 22 → 无表现
  pVictimVt = *pArg2;
  nArgOut = 0;
  nDmgKind = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *))(pVictimVt + 648))(pArg2, &nArgOut, this);  // vt+648 伤害类型
  if ( nDmgKind == 3 || nDmgKind == 2 && nArgOut <= 0 )  // kind==3 或（==2 且伤≤0）→ 无表现类
    bNoShow = 1;
  pVictimObj = __RTDynamicCast(
          (int)pArg2,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  pVictimObjBak = pVictimObj;
  if ( bNoShow == 0 && !bSkipFX && (*((uint8_t *)this + 404) != 0 || *((float *)this + 97) > 0.0) && pVictimObj != 0 )  // 可表现门（this+404 标志 或 this+388 float > 0）
  {
    bKillFlag = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 128))(pVictimObj) > 0  // 受方 vt+128(HP) > 0
       && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObjBak + 840))(pVictimObjBak) == 4;  // 且大状态 == 4（= 本次为击杀）
    if ( dword_8F7C04 == (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) && *(this + 29) != 0 )  // 本地玩家出手门
      sub_428050(bKillFlag, pszArg4, nArg3);  // 【作命中脉冲调用）】★ 连击/击杀处理（研究 §9）
    pSceneObj = *(this + 29);  // this+116〔会话上下文〕
    if ( pSceneObj != 0 )  // 若 pSceneObj 非 0
    {
      nOwnerUid = *(uint32_t *)(*(uint32_t *)(pSceneObj + 132) + 52);
      if ( nOwnerUid == (*(int (/*thiscall*/ **)(int *))(*this + 576))(this) )  // 技能对象车主 == 攻方车主
        sub_4684F0(pVictimObjBak);  // 目标 HUD 更新（血条宽度 = 等级比）
    }
  }
  if ( pszArg4 == 0 )  // 若 pszArg4 为 0
    (*(void (/*thiscall*/ **)(int *, uint32_t *))(*this + 540))(this, pArg2);  // vt+540 攻方收尾（命中语音）
  return 0;
}



// ------------------------------------------------------------
// 0x4E48D0 sub_4E48D0 —— ★ 记录最后受击时刻 + 仇人 id（研究 §1.1/§2 字段表定案）
// 由受方回调 vt+516（0x4D4A80）尾调（研究 §1.1："sub_4E48D0（受击者记录最后受击时刻
// this+568 + 仇人 id this+572——击杀归属数据）"）。
// 流程：取 a2（攻击者）attackinfo，须有伤害或反应（+16 != 0 或 float+0 > 0），
// 且 a4 == 0；先把临时 a4 = 100 作为 vt+648 的输出槽调用，结果 a4 > 0 才记录：
//   `this+142 = sub_699000(this+2)`（word 下标 142 = **字节 +568 = 最后受击时刻**）
//   `this+143 = a2->vt+576()`（word 下标 143 = **字节 +572 = 仇人 id（击杀归属）**）
// 🔴 与反编译体字面核对：源码为 `a4 = 100; vt+648(this, &a4, a2); if (a4 > 0)`
//    —— 与 4D71B0 内 `v44 = 100` 的用法同形（vt+648 第二参为"伤害/类型输出槽"）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E48D0(int *this, int nArg2, int nArg3, int nArg4)  // 实现：记录最后受击时刻 + 仇人 id（研究 §1.1/§2 字段表定案）
{
  int pAtkInfo; // eax
  int pSelfVt; // edx

  pAtkInfo = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // attackinfo
  if ( (*(uint8_t *)(pAtkInfo + 16) != 0 || *(float *)pAtkInfo > 0.0) && (uint8_t)nArg4 == 0 )  // 有伤害或反应 且 非格挡位
  {
    pSelfVt = *this;
    nArg4 = 100;
    (*(void (/*thiscall*/ **)(int *, int *, int))(pSelfVt + 648))(this, &nArg4, nArg2);  // vt+648(伤害类型, 输出槽)
    if ( nArg4 > 0 )  // 本次确有伤害
    {
      *(this + 142) = sub_699000((int)(this + 2));  // 【clock_now(clk)】this+568 = 最后受击时刻
      *(this + 143) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // this+572 = 仇人 id（击杀归属）
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E4950 sub_4E4950 —— 朝向/位置偏移判定（研究 §1.2 vt+688 骨架的消费侧）
// 流程：备份 vt+28 容器三字段 → vt+112(受, a2, a3, vt+128) 取位 → 清 +108 标志 →
//   sub_45E7D0（取对方对象）→ 若可 RTDynamicCast 到 CNRDPassiveObject 且其属性块 +8 非 0
//   → v9 = false 并回填 *a4 = 对方；否则用 this+28 技能容器 (+132 → +44) 走 sub_48CD70
// 还原备份字段 + +108 = 1。返回 v9（"本次为瞬移/位移类"？【待验证】）。
// 与 0x4D5890（同样调 sub_4E4950）配套使用。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E4950(uint32_t *this, int nArg2, int nArg3, int *pDwArg4)  // 实现：朝向/位置偏移判定（研究 §1.2 vt+688 骨架的消费侧）
{
  uint32_t *fld_e28; // eax
  int pSelfVt; // edi
  int nMoveIdx; // eax
  bool bNoPassive; // bl
  int pOther; // eax
  int pOtherBak; // edi
  int pOtherObj; // eax
  int fld_e29; // eax
  uint32_t *pSkillVec; // eax
  int nStrCap; // [esp+4h] [ebp-Ch]
  int nStrLen; // [esp+8h] [ebp-8h]
  int nStrRes; // [esp+Ch] [ebp-4h]

  if ( pDwArg4 != nullptr )  // 若 pDwArg4 有效（非空）
    *pDwArg4 = 0;
  if ( *(this + 29) == 0 )  // this+116〔会话上下文〕
    return 1;  // 返回 1(成功)
  fld_e28 = (uint32_t *)*(this + 28);  // this+112 = 表现对象
  pSelfVt = *this;
  nStrCap = fld_e28[1];  // 备份容器三字段（取位前）
  nStrLen = fld_e28[2];  // nStrLen = 取 fld_e28[2]
  nStrRes = fld_e28[3];  // nStrRes = 取 fld_e28[3]
  nMoveIdx = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(pSelfVt + 112))(this, nArg2, nArg3, nMoveIdx);  // vt+112 取位
  *(uint8_t *)(*(this + 28) + 108) = 0;  // 清位置有效标志
  bNoPassive = true;
  pOther = sub_45E7D0(this);  // 取对方对象
  pOtherBak = pOther;
  if ( pOther != 0 )  // 若 pOther 非 0
  {
    pOtherObj = __RTDynamicCast(
            pOther,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &CNRDPassiveObject `RTTI Type Descriptor',
            0);
    if ( pOtherObj == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pOtherObj + 672))(pOtherObj) + 8) != 0 )  // 对方非 PO 或其属性块 +8 非 0
    {
      bNoPassive = false;
      if ( pDwArg4 != nullptr )  // 若 pDwArg4 有效（非空）
        *pDwArg4 = pOtherBak;
    }
  }
  else  // 否则分支
  {
    fld_e29 = *(uint32_t *)(*(this + 29) + 132);  // fld_e29 = 读 this+29
    if ( fld_e29 != 0 )  // 若 fld_e29 非 0
    {
      pSkillVec = *(uint32_t **)(fld_e29 + 44);
      if ( pSkillVec != nullptr )  // 若 pSkillVec 有效（非空）
        bNoPassive = sub_48CD70(pSkillVec, (int)this) != 0;  // 走技能容器判定
    }
  }
  *(uint32_t *)(*(this + 28) + 4) = nStrCap;  // 还原备份字段
  *(uint32_t *)(*(this + 28) + 8) = nStrLen;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 12) = nStrRes;  // this+112〔pHostComp112〕
  *(uint8_t *)(*(this + 28) + 108) = 1;  // 位置有效标志复位
  return bNoPassive;
}



// ------------------------------------------------------------
// 0x4E4A50 sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
// 门：a2 非空且 (vt+316 禁用 或 vt+88 动作使能==0) → 返回 0xFFFF；
// 发 ·dword_8F8520(type 21, 2 子字段, a1) → 写 a2 与 a9 的 vt+48/52（空则 0xFFFF/0）→ 1、a3(动作 id)、a4、
// 本地玩家 vt+1220、·sub_460230(缓冲 +104)、0/a8、a5/a6/a7 → vt+52(a11,a10) + 提交 vt+60(1,-1)；返回 v23
// ------------------------------------------------------------
int /*usercall*/ sub_4E4A50@<eax>(  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        int a1@<edi>,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11)
{
  int v12; // edi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // eax
  int v23; // esi

  if ( a2 != 0  // 若 a2 非 0
    && ((*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 316))(a2) != 0  // 调虚槽 +316：CNEquipmentTeachingofGoraBoldness__vmt13C
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 88))(a2) == 0) )  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
  {
    return 0xFFFF;
  }
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, a1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
  if ( a2 != 0 )  // 若 a2 非 0
  {
    v12 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 48))(a2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v12 + 36))(dword_8F8520, v13);  // 会话/UDP 管理器
    v14 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);  // 会话/UDP 管理器
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  }
  if ( a9 != 0 )  // 若 a9 非 0
  {
    v16 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a9 + 48))(a9);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);  // 会话/UDP 管理器
    v18 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a9 + 52))(a9);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v18 + 36))(dword_8F8520, v19);  // 会话/UDP 管理器
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 1);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a4);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  v20 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
  (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);  // 会话/UDP 管理器
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
  v23 = sub_460230(*(uint32_t *)(v22 + 104));  // 图标槽随机 id 分配（线性探测）
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v23);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 0);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a8);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a5);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a6);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a7);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, a11, a10);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  return v23;
}



// ------------------------------------------------------------
// 0x4E4C10 sub_4E4C10 —— 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
// a4 使能位写常量 1；用 ·sub_529A80(&unk_9A0630, &a2) 打包数据块 → vt+48 写入 a2 字节 + vt+40 写长度
// ------------------------------------------------------------
int /*usercall*/ sub_4E4C10@<eax>(int nArg1@<edi>, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8, int nArg9)  // 实现：与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
{
  int pObj; // esi
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int pObj2; // esi
  int v16; // edi
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // eax
  int v23; // esi
  int v24; // eax

  pObj = nArg2;
  if ( nArg2 != 0  // 若 nArg2 非 0
    && ((*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 316))(nArg2) != 0  // 调虚槽 +316：CNEquipmentTeachingofGoraBoldness__vmt13C
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 88))(pObj) == 0) )  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
  {
    return 0xFFFF;
  }
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, nArg1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
  if ( pObj != 0 )  // 若 pObj 非 0
  {
    v11 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);  // 会话/UDP 管理器
    v13 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);  // 会话/UDP 管理器
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  }
  pObj2 = nArg7;
  if ( nArg7 != 0 )  // 若 nArg7 非 0
  {
    v16 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg7 + 48))(nArg7);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);  // 会话/UDP 管理器
    v18 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v18 + 36))(dword_8F8520, v19);  // 会话/UDP 管理器
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 1);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg4);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  v20 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
  (*(void (/*thiscall*/ **)(int, int))(v20 + 36))(dword_8F8520, v21);  // 会话/UDP 管理器
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
  v23 = sub_460230(*(uint32_t *)(v22 + 104));  // 图标槽随机 id 分配（线性探测）
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v23);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
  v24 = sub_529A80(&unk_9A0630, &nArg2);  // v24 = 调 sub_529A80 返回值
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v24);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A0630, nArg2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg6);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, nArg9, nArg8);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  return v23;
}



// ------------------------------------------------------------
// 0x4E4DE0 sub_4E4DE0 —— ★ 位置化动作发布（会话 3 定案：位置化动作）
// 门：vt+316（禁用）为 0 且 vt+88（动作使能）非 0 且 vt+308（本地玩家对象）非 0，
//     否则返回 0xFFFF（无效 id）。
// 定位：a9 == 4 时取 vt+152（当前朝向）作方向码；a9 == 1 时 x = 本体 x + a6，
//       否则 x = 本体 x − a6（左右镜像）；y = 本体 y + a7；z = 本体 z + a8。
// 分发：a4 == 0 → 直接 sub_4E4A50(this, this, 动作id a2, a3, x, y, z, 方向 a9, …)
//       否则把 a4（上下文对象）的 x/y/z 三坐标 + +84 朝向字节**临时改写**为本次值，
//       走 sub_4E4C10（带上下文版）后**还原**原值 —— 上下文复用模式。
// 与 0x4E4F20（动作数据包）同为会话 3/16 文档的"位置化动作/动作数据包"对偶：
//   本函数 = 位置偏移版；0x4E4F20 = 数据块版（类型 48012 + 0x6E 字节结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E4DE0(  // 位置化动作发布（会话 3 定案：位置化动作）
        void *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12)
{
  int v13; // esi
  int v14; // ebx
  int v15; // eax
  int v16; // esi
  int v17; // eax
  int v18; // ebx
  int result; // eax
  int v20; // [esp+4h] [ebp-10h]
  int v21; // [esp+8h] [ebp-Ch]
  int v22; // [esp+Ch] [ebp-8h]
  char v23; // [esp+2Fh] [ebp+1Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 316))(this) != 0  // 调虚槽 +316：CNEquipmentTeachingofGoraBoldness__vmt13C
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 88))(this) == 0  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0 )  // 调虚槽 +308：是否本地玩家
  {
    return 0xFFFF;
  }
  if ( a9 == 4 )  // 若 a9 == 4
    a9 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this);  // 调虚槽 +152：效果通道 3
  v13 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
  v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v15 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  if ( a9 == 1 )  // 若 a9 == 1
    v16 = a6 + v13;
  else  // 否则分支
    v16 = v13 - a6;
  v17 = a8 + v15;
  v18 = a7 + v14;
  if ( a4 == 0 )  // 若 a4 为 0
    return sub_4E4A50((int)this, (int)this, a2, a3, v16, v18, v17, a9, a10, a11, a12);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  v20 = *(uint32_t *)a4;
  v21 = *(uint32_t *)(a4 + 4);
  v22 = *(uint32_t *)(a4 + 8);
  v23 = *(uint8_t *)(a4 + 84);
  *(uint32_t *)(a4 + 4) = v18;
  *(uint32_t *)(a4 + 8) = v17;
  *(uint32_t *)a4 = v16;  // *a4 = v16
  *(uint8_t *)(a4 + 84) = a9 != 1;
  result = sub_4E4C10((int)this, (int)this, a2, a3, a4, a5, a10, a11, a12);  // 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
  *(uint32_t *)a4 = v20;  // *a4 = v20
  *(uint32_t *)(a4 + 4) = v21;
  *(uint32_t *)(a4 + 8) = v22;
  *(uint8_t *)(a4 + 84) = v23;
  return result;
}



// ------------------------------------------------------------
// 0x4E4F20 sub_4E4F20 —— ★ 动作数据包发布（会话 3 定案：类型 48012 + 0x6E 字节结构）
// 打包流程（全局暂存区 dword_9A06D0 起）：
//   头 18 字节 = 六个 16 位字段（a3/a4/a8/a9/a5/a11/a12/a14 的高低位拼接）
//   + a10 != nullptr 时 qmemcpy 0x62 字节（= 98）→ 头段升为 116 字节，a2 指向 unk_9A0744
//   + a14 > 0 时按 4 字节块 + 余数字节追加 a15（变长载荷）—— 总长 = v21（= v16 累计）
//   尾调 sub_4E4A50(a2, a1, **48012**, a13, a6, a7, 0, vt+152(朝向), 0, v21, 数据区)
// 与 0x4E4DE0（位置化动作）成对：本函数 = 携带 0x62 字节数据块的动作型
// （研究 P29/P30 的"动作数据包"；会话 3 已定案"类型 48012 + 0x6E 字节结构 → sub_4E4A50"）。
// 注：0x6E = 110 = 18 + 98 − 6？ [待验证：0x6E 与 116 的口径差 — 研究记录 0x6E 系
// 会话 3 结论，此处实测头段为 116(0x74) 字节；可能 0x6E 指的是定长载荷 |
// 0x62=98 而不含 18 字节头 —— 标注差异，不改代码]
// ------------------------------------------------------------
int /*userpurge*/ sub_4E4F20@<eax>(  // 动作数据包发布（会话 3 定案：类型 48012 + 0x6E 字节结构）
        int a1@<ecx>,
        char *a2@<edi>,
        int16_t a3,
        int16_t a4,
        int16_t a5,
        int a6,
        int a7,
        int16_t a8,
        int16_t a9,
        const void *a10,
        char a11,
        int16_t a12,
        int a13,
        unsigned int a14,
        char *a15)
{
  int v16; // eax
  char *v17; // edi
  unsigned int v18; // ecx
  int v19; // eax
  int v21; // [esp-8h] [ebp-28h]
  int v22; // [esp+Ch] [ebp-14h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+14h] [ebp-Ch]
  int v25; // [esp+18h] [ebp-8h]

  LOWORD(v23) = a3;
  LOWORD(v22) = a8;
  HIBYTE(v24) = a11;
  HIWORD(v22) = a9;
  HIWORD(v23) = a4;
  dword_9A06D0[0] = v22;
  LOWORD(v25) = a12;
  dword_9A06D4 = v23;
  LOWORD(v24) = a5;
  BYTE2(v24) = a10 != nullptr;
  dword_9A06D8 = v24;
  HIWORD(v25) = a14;
  dword_9A06DC = v25;
  word_9A06E0 = HIWORD(a14);  // word_9A06E0 = 调 HIWORD
  v16 = 18;
  if ( a10 != nullptr )  // 若 a10 有效（非空）
  {
    qmemcpy(&unk_9A06E2, a10, 0x62u);
    a2 = (char *)&unk_9A0744;
    v16 = 116;
  }
  if ( (int)a14 > 0 )
  {
    qmemcpy((char *)dword_9A06D0 + v16, a15, 4 * (a14 >> 2));
    v17 = (char *)&dword_9A06D0[a14 >> 2] + v16;
    v18 = a14 & 3;  // 位掩码测试 &0x3（位 0,1）
    qmemcpy(v17, &a15[4 * (a14 >> 2)], v18);
    a2 = &v17[v18];
    v16 += a14;
  }
  v21 = v16;
  v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);  // 调虚槽 +152：效果通道 3
  return sub_4E4A50((int)a2, a1, 48012, a13, a6, a7, 0, v19, 0, v21, (int)dword_9A06D0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
}



// ------------------------------------------------------------
// 0x4E5030 sub_4E5030 —— 位置/状态同步包发布（短版 48024 / 长版 type 22）
// 门 this+29 场景对象 + +132 非空；a16==0 时算时长 v23 = ·sub_4D5E00(vt+672(3))/30 + a6（条件 529 且更小则取小）后夹取 1..99；
// a11==2 → 短包（10 或 17 字节）经 ·0x4E4A50(a1, 48024, …)，a17 非空时续接其 7 字节；
// 否则 type 22 长包：本地玩家 vt+1220 / ·sub_460230(this+29) / a14==0xFFFF 与 a15==1(常量 529) 分支 / 数据区 a12(a13) / a17(7 字节)
// ------------------------------------------------------------
void /*userpurge*/ sub_4E5030(  // 位置/状态同步包发布（短版 48024 / 长版 type 22）
        uint32_t *a1@<ecx>,
        int a2@<ebx>,
        int a3@<esi>,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        uint8_t *a12,
        int a13,
        int a14,
        char a15,
        char a16,
        int a17,
        int a18)
{
  int v19; // eax
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // ebx
  char *v24; // esi
  int v25; // eax
  int v26; // edi
  int v27; // eax
  int v28; // esi
  int v29; // eax
  int v30; // esi
  int v31; // eax
  int v32; // edi
  int v33; // eax
  int v34; // eax
  int64_t v37; // [esp+4h] [ebp-10h] BYREF
  int16_t v38; // [esp+Ch] [ebp-8h]
  uint32_t *v39; // [esp+10h] [ebp-4h]
  int v40; // [esp+24h] [ebp+10h]

  v19 = a1[29];  // v19 = 取 a1[29]
  v39 = a1;
  if ( v19 == 0 || *(uint32_t *)(v19 + 132) == 0 )  // 若 v19 == 0
    return;
  if ( a16 != 0 )  // 若 a16 非 0
  {
    v23 = a6;
    goto LABEL_11;
  }
  v20 = __RTDynamicCast(
          (int)a1,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  v21 = v20;
  if ( v20 == 0 )  // 若 v20 为 0
  {
    v23 = a6;
LABEL_9:  // 标签 LABEL_9（跳转合流点）
    a16 = 1;
    goto LABEL_11;
  }
  v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 672))(v20, 3);  // 调虚槽 +672：自身 HP
  v23 = sub_4D5E00(v22) / 30 + a6;  // v23 = 调 sub_4D5E00 返回值
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 40))(v21, 529) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 672))(v21, 3) >= v23 )  // 调虚槽 +672：自身 HP
  {
    goto LABEL_9;
  }
  v23 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 672))(v21, 3);  // 调虚槽 +672：自身 HP
  a16 = 1;
LABEL_11:  // 标签 LABEL_11（跳转合流点）
  if ( v23 <= 1 )  // 若 v23 <= 1
  {
    v23 = 1;
  }
  else if ( v23 > 99 )
  {
    v23 = 99;
  }
  if ( a11 == 2 )  // 若 a11 == 2
  {
    LOBYTE(v37) = 0;
    if ( a13 > 0 )  // 若 a13 > 0
      LOBYTE(v37) = *a12;
    BYTE5(v37) = v23;
    *(uint16_t *)((char *)&v37 + 1) = a4;
    *(uint16_t *)((char *)&v37 + 3) = a5;
    HIWORD(v37) = a14;
    LOBYTE(v38) = a15;
    HIBYTE(v38) = a16;
    if ( a17 != 0 )  // 若 a17 非 0
    {
      v24 = (char *)operator new(0x11u);  // new(17 字节) 分配对象
      *(uint64_t *)v24 = v37;  // *v24 = v37
      *((uint16_t *)v24 + 4) = v38;  // v24[4] = v38
      *(uint32_t *)(v24 + 10) = *(uint32_t *)a17;
      *((uint16_t *)v24 + 7) = *(uint16_t *)(a17 + 4);
      v24[16] = *(uint8_t *)(a17 + 6);
      sub_4E4A50(a1, 48024, 0, a7, a8, a9, a10, 0, 17, v24);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      if ( v24 != nullptr )  // 若 v24 有效（非空）
        j__free(v24);
    }
    else  // 否则分支
    {
      sub_4E4A50(a1, 48024, 0, a7, a8, a9, a10, 0, 10, &v37);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 22, 2, a3, a2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    if ( a14 == 0xFFFF || a15 != 1 )  // 若 a14 == 0xFFFF 与/或 a15 != 1
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 0);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    else  // 否则分支
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    v40 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 48))(a1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v40 + 36))(dword_8F8520, v25);  // 会话/UDP 管理器
    v26 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*v39 + 52))(v39);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v26 + 36))(dword_8F8520, v27);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a5);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v23);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    if ( a14 == 0xFFFF )  // 若 a14 == 0xFFFF
    {
      v28 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
      (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);  // 会话/UDP 管理器
      v30 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v31 = sub_460230(v39[29]);  // 图标槽随机 id 分配（线性探测）
      (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);  // 会话/UDP 管理器
    }
    else  // 否则分支
    {
      if ( a15 == 1 )  // 若 a15 == 1
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 529);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      }
      else  // 否则分支
      {
        v32 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
        (*(void (/*thiscall*/ **)(int, int))(v32 + 36))(dword_8F8520, v33);  // 会话/UDP 管理器
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a14);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a10);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a7);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a8);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a9);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a11);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a13);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    if ( a13 > 0 )  // 若 a13 > 0
      (*(void (/*thiscall*/ **)(int, uint8_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a12, a13);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    v34 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    if ( a17 != 0 )  // 若 a17 非 0
    {
      (*(void (/*stdcall*/ **)(int))(v34 + 32))(1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/4…
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, a17, 7);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    }
    else  // 否则分支
    {
      (*(void (/*stdcall*/ **)(uint32_t))(v34 + 32))(0);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/4…
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a18);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  }
}


// ============================================================
// 【分区 C】碰撞 / 命中判定几何族（0x4E5410 - 0x4E6770）
//   研究 P29（第 24/25 轮）：命中判定 = O(n²) 全对象配对 → 攻防门 → 1000ms 节流 →
//   多盒 → 3D AABB（命中区域 = 交集盒）；盒挂在帧数据上。
//   本区含攻击盒提取 / AABB 重叠 / 动画盒重叠 / 帧推进 / 伤害流水线。
// ------------------------------------------------------------

// ------------------------------------------------------------
// 0x4E5410 sub_4E5410 —— ★ 位置采样 vt+14C（每 100ms 节流，双缓冲）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp:330（0x4E5410 vmt14C）。
// 逻辑：首查 dword_79C0B4 的 86/87 通道（输入采样）；a1[148] == −1（未初始化）时
// 两路 (x, now) 直接填充 this+145..148；否则若 now >= 上次 + ≥100 → 双缓冲推进
// （+145 ← +146、+147 ← 旧时刻、+146 ← 当前 x、+148 ← now）。
// 配套读取器 = 0x4E59C0（速度 = Δx×1000 / Δt）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5410(int *this)  // 实现：位置采样（每 100ms 节流，双缓冲）
{
  int *pThis_93; // edi
  int i; // ebx
  int result; // eax
  int fld_e148; // ebx
  int v6; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 86) != 1  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 87) != 1 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 88);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  }
  nullsub_3(this);
  if ( *(this + 148) == -1 )
  {
    pThis_93 = this + 147;
    for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
    {
      *(pThis_93 - 2) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
      result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      *pThis_93++ = result;
    }
  }
  else  // 否则分支
  {
    fld_e148 = *(this + 148);
    result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    if ( result >= fld_e148 + 100 )
    {
      v6 = *this;
      *(this + 145) = *(this + 146);  // this+580〔uOffset580〕
      *(this + 147) = fld_e148;
      *(this + 146) = (*(int (/*thiscall*/ **)(int *))(v6 + 120))(this);  // 调虚槽 +120：动画对象
      result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      *(this + 148) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E54D0 sub_4E54D0 —— ★ 3D AABB 重叠测试（vm t1E8，无 z 轴；俯视平面）
// ⚠ 已精修版见 src/cnrd/IRDCollisionObject.cpp:27（同一函数的两份转写；以 L1 版为准）
// 判据：A.min ≤ B.max 且 B.min ≤ A.max 在 x/y 两轴同时成立。
// 四边取法：vt+440/444/448/452 = x 左右 / y 上下边界族（研究 P29 盒模型）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E54D0(void *this, int nArg2)  // 实现：★ 3D AABB 重叠测试（无 z 轴；俯视平面）
{
  int v3; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 440))(nArg2);  // 调虚槽 +440：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 444))(this) < v3 )  // 调虚槽 +444：包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 1B8/1BC/1C0/1C4…
    return false;
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 444))(nArg2);  // 调虚槽 +444：包围盒右界 = 宽 + vt+440（cnrd 头以 1B8 1B8/1BC/1C0/1C4…
  if ( v5 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 440))(this) )  // 调虚槽 +440：包围盒左界 = 中心x − 宽/2（AABB 边界族 1B8/1BC/1C0/1C4 之首）
    return false;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 448))(nArg2);  // 调虚槽 +448：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 452))(this) < v6 )  // 调虚槽 +452：包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
    return false;
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 452))(nArg2);  // 调虚槽 +452：包围盒下界 = 高 + vt+448（cnrd 头同上族级覆盖）
  return v7 >= (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 448))(this);  // 调虚槽 +448：包围盒上界 = 中心y − 高/2（cnrd 头同上族级覆盖）
}



// ------------------------------------------------------------
// 0x4E5560 sub_4E5560 —— ★ 动画盒世界坐标重叠测试（vm t1EC）
// ⚠ 已精修版见 src/cnrd/IRDCollisionObject.cpp:50（同一函数的两份转写；以 L1 版为准）
// 双方各自的动画对象（sub_4918E0 obj+60，边界槽 0..3）给出四边界；判据 = 目标 y 区间
// 与本体 y 区间相交 且 x 区间相交（含"完全包含"分支）—— 研究 P29 盒迭代的下层实现。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5560(int *this, int *pDwArg2)  // 实现：★ 动画攻击盒世界坐标重叠测试(会话 3 新分析)
{
  int pAnimObj; // edi  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）
  int v4; // edi
  int pAnimObj_; // edi  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）
  int v6; // edi
  int v7; // eax
  int pAnimObj_2; // edi  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）
  int v9; // edi
  int pAnimObj_3; // edi  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）
  int v11; // edi
  int v12; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // edi
  int v19; // edi
  int v20; // edi
  int v21; // edi
  int v22; // edi
  int v23; // edi
  bool v24; // cc
  int v26; // [esp+Ch] [ebp-14h]
  int v27; // [esp+10h] [ebp-10h]
  int v28; // [esp+14h] [ebp-Ch]
  int v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+1Ch] [ebp-4h]
  int v31; // [esp+28h] [ebp+8h]

  pAnimObj = *(this + 30);  // this+120〔pAnimObj〕
  if ( *(uint32_t *)(pAnimObj + 148) == -1 )
    sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v4 = 15 - sub_4918E0((int *)(pAnimObj + 60), 0);  // 动画盒四边界提取（研究 P29 族）
  v27 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v4;  // 调虚槽 +120：动画对象
  pAnimObj_ = *(this + 30);  // this+120〔pAnimObj〕
  if ( *(uint32_t *)(pAnimObj_ + 148) == -1 )
    sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v6 = sub_4918E0((int *)(pAnimObj_ + 60), 1);  // 动画盒四边界提取（研究 P29 族）
  v7 = v6 + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 15;  // 调虚槽 +120：动画对象
  pAnimObj_2 = *(this + 30);  // this+120〔pAnimObj〕
  v30 = v7;
  if ( *(uint32_t *)(pAnimObj_2 + 148) == -1 )
    sub_4938F0(pAnimObj_2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v9 = 15 - sub_4918E0((int *)(pAnimObj_2 + 60), 2);  // 动画盒四边界提取（研究 P29 族）
  v29 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + v9;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pAnimObj_3 = *(this + 30);  // this+120〔pAnimObj〕
  if ( *(uint32_t *)(pAnimObj_3 + 148) == -1 )
    sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v11 = sub_4918E0((int *)(pAnimObj_3 + 60), 3);  // 动画盒四边界提取（研究 P29 族）
  v12 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v28 = v12 + v11;
  v14 = pDwArg2[30];  // v14 = 取 pDwArg2[30]
  if ( *(uint32_t *)(v14 + 148) == -1 )
    sub_4938F0(pDwArg2[30]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v15 = sub_4918E0((int *)(v14 + 60), 0);  // 动画盒四边界提取（研究 P29 族）
  v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2) - v15;  // 调虚槽 +120：动画对象
  v17 = pDwArg2[30];  // v17 = 取 pDwArg2[30]
  v26 = v16;
  if ( *(uint32_t *)(v17 + 148) == -1 )
    sub_4938F0(v17);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v18 = sub_4918E0((int *)(v17 + 60), 1);  // 动画盒四边界提取（研究 P29 族）
  v31 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2) + v18;  // 调虚槽 +120：动画对象
  v19 = pDwArg2[30];  // v19 = 取 pDwArg2[30]
  if ( *(uint32_t *)(v19 + 148) == -1 )
    sub_4938F0(pDwArg2[30]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  sub_4918E0((int *)(v19 + 60), 2);  // 动画盒四边界提取（研究 P29 族）
  (*(void (/*thiscall*/ **)(int *))(*pDwArg2 + 124))(pDwArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  (*(void (/*thiscall*/ **)(int *))(*pDwArg2 + 128))(pDwArg2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v20 = pDwArg2[30];  // v20 = 取 pDwArg2[30]
  if ( *(uint32_t *)(v20 + 148) == -1 )
    sub_4938F0(pDwArg2[30]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  v21 = sub_4918E0((int *)(v20 + 60), 3);  // 动画盒四边界提取（研究 P29 族）
  v22 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 128))(pDwArg2) + v21;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v23 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 124))(pDwArg2) + v22;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  if ( v23 > v29 && v23 < v28 )  // 若 v23 > v29 与/或 v23 < v28
  {
    if ( v31 > v27 && v31 < v30 )  // 若 v31 > v27 与/或 v31 < v30
      return 1;  // 返回 1(成功)
    v24 = v26 < v27;
    if ( v26 > v27 )  // 若 v26 > v27
    {
      if ( v26 < v30 )  // 若 v26 < v30
        return 1;  // 返回 1(成功)
      v24 = v26 < v27;
    }
    if ( v24 && v31 > v30 )  // 若 v31 > v30
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E5740 sub_4E5740 —— 概率判定（rand%10000 < 率×100；a3 为"抗性来源"）
// 结构 = 研究 §5.1 掷法同构：a3（对象）条件 17（有血）时从其属性块 (+284/+508，14 字节步距)
// 经 sub_4D5E40(v4, 12) 扣抵抗；sub_432FA0()（随机种机）后 `v5×100 > rand()%10000`。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E5740(void *this, int nArg2, void *pArg3)  // 实现：概率判定（rand%10000 < 率×100；a3 为抗性来源）
{
  char *v4; // eax
  float v5; // [esp+Ch] [ebp+8h]

  if ( this == pArg3 )  // 若 this == pArg3
    return true;
  if ( nArg2 == 0 )  // 若 nArg2 为 0
    return false;
  v5 = (float)nArg2;
  if ( pArg3 != nullptr && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)pArg3 + 40))(pArg3, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    v4 = (char *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pArg3 + 672))(pArg3, 3);  // 调虚槽 +672：自身 HP
    v5 = v5 - (double)(int)sub_4D5E40(v4, 12);
  }
  sub_432FA0();  // srand 播种
  return v5 * 100.0 > (double)(rand() % 10000);  // rand()%10000 取模随机
}



// ------------------------------------------------------------
// 0x4E57E0 sub_4E57E0
// ------------------------------------------------------------
// vmt1A8 属性修正伤害输入（L1 精修版见 src/cnrd/IRDCollisionObject.cpp:125）：
// a2 = 参数结构 {float 基值; +8 百分比; +12 类型 0/1/2; +16 使能}；
// 类型 0/2 加 vt+396/+400，类型 1 加 vt+412/+416；(百分比×0.01+1) 缩放后按类型叠
// vt+392/+408 属性系数（经 ·sub_433F60 PVP 平衡路由 / flt_9A05F4|9A060C），
// 返回 ·sub_433F60(this,0) × 结果 = 最终伤害基值。
// ------------------------------------------------------------
double /*thiscall*/ sub_4E57E0(void *this, int pArg2, int nArg3)  // 实现：★ 深度/属性修正伤害输入(会话 3 新分析)
{
  double fBaseDmg; // st7
  int nType; // eax
  double fAddDmg; // st7
  int nType2; // eax
  double fAttrMul; // st7
  double fPrimary; // st7
  int nType3; // esi
  double fAttrRate; // st7
  float fAttrPct; // [esp+10h] [ebp+8h]
  float fAttrPct2; // [esp+10h] [ebp+8h]
  float fBaseDmg2; // [esp+14h] [ebp+Ch]
  float fScaled; // [esp+14h] [ebp+Ch]

  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    sub_699000((int)this + 36);  // 【clock_now(clk)】
    sub_699000((int)this + 8);  // 【clock_now(clk)】
  }
  fBaseDmg = *(float *)pArg2;
  fBaseDmg2 = *(float *)pArg2;
  if ( *(uint8_t *)(pArg2 + 16) != 0 )  // 使能位：叠加"攻击属性附加伤害"（type 0/2 → vt+396，type 1 → vt+412）
  {
    nType = *(uint32_t *)(pArg2 + 12);  // pArg2+12〔nSkillRec12(推断)〕
    if ( nType == 0 || nType == 2 )  // 若 nType == 0 与/或 nType == 2
    {
      fAddDmg = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 396))(this);  // 调虚槽 +396：MP 类属性读取（+1012 × 浮点壳 +1026）
    }
    else  // 否则分支
    {
      if ( nType != 1 )  // 若 nType != 1
        goto LABEL_10;
      fAddDmg = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 412))(this);  // 调虚槽 +412：朝向与移动状态机
    }
    fBaseDmg = fAddDmg + fBaseDmg2;
  }
LABEL_10:  // 标签 LABEL_10（跳转合流点）
  nType2 = *(uint32_t *)(pArg2 + 12);  // pArg2+12〔nSkillRec12(推断)〕
  fScaled = ((double)*(int *)(pArg2 + 8) * 0.0099999998 + 1.0) * fBaseDmg;  // +8 百分比 ×0.01 + 1 缩放（研究 P14 九步乘区）
  if ( nType2 != 0 )  // 若 nType2 非 0
  {
    if ( nType2 != 1 )  // 若 nType2 != 1
      goto LABEL_15;
    fAttrMul = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 416))(this);  // 调虚槽 +416：[RTTI: IRDActiveObject__vmt1A0 · 槽位 IRDActiveO…
  }
  else  // 否则分支
  {
    fAttrMul = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 400))(this);  // 调虚槽 +400：整数属性读取（+1306）
  }
  fScaled = (fAttrMul * 0.0099999998 + 1.0) * fScaled;  // 同型第二乘区（vt+400 / vt+416）
LABEL_15:  // 标签 LABEL_15（跳转合流点）
  nType3 = *(uint32_t *)(pArg2 + 12);  // pArg2+12〔nSkillRec12(推断)〕
  if ( nType3 == 0 )  // 若 nType3 为 0
  {
    fAttrPct = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 392))(this);  // 调虚槽 +392：HP 类属性读取（属性块 +60 防篡读 × 浮点壳 +74）
    fAttrRate = sub_433F60((int)this, 3) * fAttrPct / flt_9A05F4;  // PVP 平衡系数路由（研究第 17/27 轮）
LABEL_19:  // 标签 LABEL_19（跳转合流点）
    fScaled = (fAttrRate + 1.0) * fScaled;
    return sub_433F60((int)this, 0) * fScaled;  // 返回 调 sub_433F60 返回值
  }
  if ( nType3 == 1 )  // 若 nType3 == 1
  {
    fAttrPct2 = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 408))(this);  // 调虚槽 +408：装备槽解绑
    fAttrRate = sub_433F60((int)this, 5) * fAttrPct2 / flt_9A060C;  // PVP 平衡系数路由（副路）
    goto LABEL_19;
  }
  return sub_433F60((int)this, 0) * fScaled;  // 返回 调 sub_433F60 返回值
}



// ------------------------------------------------------------
// 0x4E5920 sub_4E5920
// ------------------------------------------------------------
// vmt290 朝向决策（L1 精修版见 src/cnrd/IRDCollisionObject.cpp:167）：
// 宿主(this+29 → +132) 模式 +1316 < 4 且 ·sub_472D40 查询成功时：
// 模式 0 强制朝左 / 模式 1 强制朝右 / 模式 2、3 比较双方 x 大者朝左否则朝右。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5920(int *this)  // 实现：★ 朝向决策（依据宿主模式 +1316）(会话 3 新分析)
{
  int result; // eax
  int v3; // edi
  int v4; // edi

  result = *(this + 29);  // this+116〔会话上下文〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *(uint32_t *)(result + 132);
    if ( result != 0 && *(uint32_t *)(result + 108) != 0 )  // 若 result != 0
    {
      v3 = *(uint32_t *)(result + 1316);
      if ( v3 < 4 )  // 若 v3 < 4
      {
        result = sub_472D40(*(uint32_t *)(result + 1316));  // result = 调 sub_472D40 返回值
        if ( result != 0 )  // 若结果非 0（成功）
        {
          switch ( v3 )  // 按 v3 分派
          {
            case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
              goto LABEL_7;
            case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
              goto LABEL_9;
            case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
            case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
              v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);  // 调虚槽 +120：动画对象
              if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v4 )  // 调虚槽 +120：动画对象
              {
LABEL_7:  // 标签 LABEL_7（跳转合流点）
                result = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                *(uint8_t *)(result + 52) = 0;
              }
              else  // 否则分支
              {
LABEL_9:  // 标签 LABEL_9（跳转合流点）
                result = (*(int (/*thiscall*/ **)(int *))(*this + 60))(this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                *(uint8_t *)(result + 52) = 1;
              }
              break;  // 跳出循环/分支
            default:  // 默认分支
              return result;
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E59C0 sub_4E59C0 —— 位置采样速度计算（0x4E5410 采样对读取器）
// `1000 × (当前 x − this+145) / (now − this+147)` —— 单位 x/秒（×1000 换算）。
// 未初始化（this+147 == −1）或时刻相同 → 0（防除零）。
// 消费点：击退/位移速度派生（研究 §15"受击位移=动画帧驱动"的量化侧）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E59C0(uint32_t *this)  // 实现：位置采样速度计算（0x4E5410 采样对读取器）
{
  int fld_e145; // ebx

  if ( *(this + 147) == -1 || *(this + 147) == sub_699000((int)(this + 2)) )  // 【clock_now(clk)】
    return 0;
  fld_e145 = 1000 * ((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - *(this + 145));  // 调虚槽 +120：动画对象
  return fld_e145 / (sub_699000((int)(this + 2)) - *(this + 147));  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4E5A20 sub_4E5A20 —— 朝向/背向判定（a2 相对 this 的"左/右/背后"）
// 先比 vt+664（朝向码）：不等且 x 距离 < 50 → 返回 v9 <= 0（近身用朝向码定左右）。
// 否则比 x：相等时用 a2->vt+152（自身朝向）；否则返回 this.x >= a2.x。
// 研究 §14 的"背击判定"消费侧之一（[critical hit] + 宿主/背击加成，研究 §5.1）；
// 背击加成字段 = attackinfo+144（研究 §3 字段表）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5A20(void *this, int nArg2)  // 实现：朝向/背向判定（a2 相对 this 的左/右/背后）
{
  int nFacingDiff; // ebx
  int nSelfX; // ebx
  int nOtherX; // ebx
  int nOtherX2; // edi
  int pThis_298; // [esp+14h] [ebp+8h]

  nFacingDiff = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 664))(nArg2);  // 调虚槽 +664
  pThis_298 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 664))(this) - nFacingDiff;  // vt+664 = 朝向码之差
  if ( pThis_298 != 0 )  // 若 pThis_298 非 0
  {
    nSelfX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
    if ( (int)abs32(nSelfX - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)) < 50 )  // 近身 50 内用朝向码定左右
      return pThis_298 <= 0;
  }
  nOtherX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) == nOtherX )  // 调虚槽 +120：动画对象
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2);  // 同位 → 用对方自适应朝向
  nOtherX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) >= nOtherX2;  // 否则按 x 大小
}



// ------------------------------------------------------------
// 0x4E5AC0 sub_4E5AC0 —— 条件 33 + 参考对象存在判定（BOOL）
// 条件 33 成立 且 ·this+112 的 +104 非 0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4E5AC0(uint32_t *this)  // 条件 33 + 参考对象存在判定（BOOL）
{
  return (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      && *(uint32_t *)(*(this + 28) + 104) != 0;  // this+112〔pHostComp112〕
}



// ------------------------------------------------------------
// 0x4E5AF0 sub_4E5AF0 —— ★ 背击判定（研究 §3 定案：背击暴击加成 attackinfo+144）
// "attackinfo 有伤害或反应（+16/+0）且 a1 的朝向 != a2->vt+660(a1)" → true（背后）。
// 研究 §3 字段表："+144 背击暴击加成（背击判定 sub_4E5AF0 时加进暴击率）【第 14 轮】"。
// 调用点：0x4E5CE0（攻方收尾语音：按背击/暴击两轴播音）、0x4E5B50 附近的暴击链。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4E5AF0(int nArg1, int nArg2)  // 实现：背击判定（研究 §3 定案：背击暴击加成 attackinfo+144）
{
  int pAttackInfo; // eax
  int nAttFacing; // esi
  bool result; // al

  pAttackInfo = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // attackinfo
  result = false;
  if ( *(uint8_t *)(pAttackInfo + 16) != 0 || *(float *)pAttackInfo > 0.0 )  // 有伤害或反应
  {
    nAttFacing = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 660))(nArg2, nArg1);  // vt+660 攻方对受方的朝向
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 152))(nArg1) != nAttFacing )  // 受方朝向 != 攻方期望 → 背后
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5B50 sub_4E5B50 —— ★★ 暴击/有效命中判定（研究 20 §5.1 全文定案）
// 签名：__cdecl(a1 = 受击者, a2 = 攻击者)（与 §5.1 "sub_4E5B50（受击者, 攻击者）"一致）。
// 流程与 §5.1 定案清单逐条对应：
//   ① RTDynamicCast(a1 → IRDActiveObject) 失败 → false
//   ② 攻击信息须有伤害或反应：`attackinfo+16 == 0 && float+0 <= 0 && +60 == 0` → false
//      （研究原文："攻击信息须有伤害或反应"）
//   ③ v5 = 受击者大状态 ID（vt+840 = this+6556）
//   ④ 排除链（研究原文："状态 ∈ {0,1,3,4,6,9} 直接 false；11 仅当条件 273；
//      22 仅当条件 529"）—— 转写体为 `(条件273==0 || v5!=11) && v5!=0 && v5!=6
//      && v5!=4 && v5!=1 && v5!=3 && v5!=9 && (条件529==0 || a1+7148!=22)` 全合取，
//      **与排除表逐项吻合**（注意：研究写 "11 仅当条件 273"，即 273 假 → 非 11 才算通过）
//   ⑤ 返回 true = 本次为暴击（伤害 ×1.5 + 震屏 + 特效强化，研究 §5.1 第 14 轮更正）
// 逐项核对：排除值实测 = {0, 1, 3, 4, 6, 9}（研究 §5.1 表列六值，**完全吻合**）；
//   11 门 = `条件273 || v5!=11`；22 门 = `条件529==0 || v2[1787(+7148)] != 22`。
// ------------------------------------------------------------
bool /*cdecl*/ sub_4E5B50(int nArg1, int nArg2)  // 实现：暴击/有效命中判定（研究 20 §5.1 全文定案）
{
  uint32_t *pVictimObj; // edi
  int pAttackInfo; // ecx
  int nBigState; // esi

  pVictimObj = (uint32_t *)__RTDynamicCast(
                   nArg1,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
  if ( pVictimObj == nullptr )  // 若 pVictimObj 为空
    return false;
  pAttackInfo = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // attackinfo
  if ( *(uint8_t *)(pAttackInfo + 16) == 0 && *(float *)pAttackInfo <= 0.0 && *(uint32_t *)(pAttackInfo + 60) == 0 )  // 无伤害也无反应
    return false;
  nBigState = (*(int (/*thiscall*/ **)(uint32_t *))(*pVictimObj + 840))(pVictimObj);  // vt+840 = 大状态 this+6556
  return ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pVictimObj + 40))(pVictimObj, 273) == 0 || nBigState != 11)  // 条件 273 = 受击态
      && nBigState != 0
      && nBigState != 6
      && nBigState != 4
      && nBigState != 1
      && nBigState != 3
      && nBigState != 9
      && ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pVictimObj + 40))(pVictimObj, 529) == 0 || pVictimObj[1787] != 22);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
}



// ------------------------------------------------------------
// 0x4E5C10 sub_4E5C10 —— 帧时刻覆盖开关（this+642 标志 / this+644 时刻）
// 标志非 0 时改写；pszArg2==0 先 ·sub_4910E0 + ·sub_493A60 推帧再清标志（动画对象 = this+120）
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5C10(int this, char pszArg2, int nArg3)  // 实现：帧时刻覆盖开关（this+642 标志 / this+644 时刻）
{
  char result; // al
  int pAnimObj; // edi  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）

  result = *(uint8_t *)(this + 642);  // this+642〔bHitBoxSnap642〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( pszArg2 != 0 )  // 若 pszArg2 非 0
    {
      *(uint8_t *)(this + 642) = pszArg2;  // this+642〔bHitBoxSnap642〕
      *(uint32_t *)(this + 644) = nArg3;  // this+644〔uHitBoxSnap644〕
      return nArg3;
    }
    else  // 否则分支
    {
      pAnimObj = *(uint32_t *)(this + 120);  // this+120〔pAnimObj〕
      if ( pAnimObj != 0 )  // 若 fld_78 非 0
      {
        sub_4910E0(*(uint32_t *)(this + 120));  // 帧时刻推进（返回 1 表示时刻发生位移）
        result = sub_493A60(pAnimObj, *(uint32_t *)(pAnimObj + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
        *(uint8_t *)(this + 642) = 0;  // this+642〔bHitBoxSnap642〕
        *(uint32_t *)(this + 644) = nArg3;  // this+644〔uHitBoxSnap644〕
      }
      else  // 否则分支
      {
        *(uint8_t *)(this + 642) = 0;  // this+642〔bHitBoxSnap642〕
        *(uint32_t *)(this + 644) = nArg3;  // this+644〔uHitBoxSnap644〕
      }
    }
  }
  else  // 否则分支
  {
    *(uint8_t *)(this + 642) = pszArg2;  // this+642〔bHitBoxSnap642〕
    *(uint32_t *)(this + 644) = nArg3;  // this+644〔uHitBoxSnap644〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5CA0 sub_4E5CA0 —— 阵营号 200..204 判定（200 起逐个比较）
// vt+376 ∈ [200,204] → 1；否则 0（哨兵阵营族）
// ------------------------------------------------------------
char /*thiscall*/ sub_4E5CA0(void *this)  // 实现：阵营号 200..204 判定（200 起逐个比较）
{
  int v2; // esi

  v2 = 200;
  while ( v2 != (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
  {
    if ( ++v2 >= 205 )
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4E5CE0 sub_4E5CE0 —— 命中评价横幅（背击 → 横幅 1 / 暴击 → 横幅 2）
// 车主 vt+576 → IRDCharacter，受方 a2 → IRDActiveObject；车主 vt+308 门；
// ·sub_4E5AF0 背击 → ·sub_426820(+132, 1, 0) + ·sub_495A70(1, 5, 车主 vt+52)；
// ·sub_4E5B50 暴击 → ·sub_426820(…, 2, 0) + ·sub_495A70(1, 4, …)（研究 §3/§5.1）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5CE0(uint32_t *this, int nArg2)  // 实现：命中评价横幅（背击 → 横幅 1 / 暴击 → 横幅 2）
{
  int pCharPtr; // eax
  int pVictimObj; // edi
  int result; // eax
  int nVictimUid; // ebx
  int nVictimUid2; // eax
  int nVictimUid3; // eax

  pCharPtr = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 576))(this);  // vt+576 车主
  pVictimObj = __RTDynamicCast(pCharPtr, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // pVictimObj = 调 __RTDynamicCast
  result = __RTDynamicCast(
             nArg2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDActiveObject `RTTI Type Descriptor',
             0);
  nVictimUid = result;
  if ( pVictimObj != 0 && result != 0 )  // 若 pVictimObj != 0 与/或 result != 0
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 308))(pVictimObj);  // 本地玩家对象门
    if ( (uint8_t)result != 0 )
    {
      if ( (uint8_t)sub_4E5AF0(nVictimUid, this) != 0 )  // ★ 背击判定
      {
        sub_426820(*(uint32_t *)(*(this + 29) + 132), 1, 0);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】横幅 1 = 背击
        nVictimUid2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 52))(pVictimObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_495A70(1, 5, nVictimUid2);  // 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
      }
      result = sub_4E5B50(nVictimUid, this);  // ★★ 暴击判定
      if ( (uint8_t)result != 0 )
      {
        sub_426820(*(uint32_t *)(*(this + 29) + 132), 2, 0);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】横幅 2 = 暴击
        nVictimUid3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 52))(pVictimObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        return sub_495A70(1, 4, nVictimUid3);  // 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E5DC0 sub_4E5DC0 —— ★★★ 表现壳 / hit stop 施加点（研究 20 §3 全文定案）
// __thiscall(this=受击者, a2=攻击者, a3=命中盒, a4=格挡标志)
// 研究 §3 伪码 → 转写体逐行对照：
//   v6 = vt+648(this, &v16(初值100), a2)        伤害类型（0/1 正常，2 = 落空）
//   if (a4 != 0)（格挡）:
//       v6 != 2 → vt+644(this, a2, a3)          ★ 格挡特效：GuardSpark.ani +
//                                               GuardCircle.ani + Stuck.ani（0x4E9760）
//       读攻击定义 attackinfo+128 → 非 0 → 广播 **"STUCK_BLADE"** 否则 **"STUCK_BLUNT"**
//                                               ★ 刀剑/钝器两种"卡肉"音效（研究 §3 要点二）
//   else if (v6 != 2):
//       受击者当前"伤害态" = (this+642 标志 ? this+161 盒快照 : 动画对象(this+30)+112)
//       —— 当该值为 2 时**跳过** stuck 施加，直接走 HITEFF（研究 §3 原文"若受击者伤害态 != 2"）
//       否则:
//           v9 = attackinfo+132                ★★ 本次命中的硬直时长（毫秒）= hit stop 时长
//           若 v9 > 0 且（主状态(this+50=字节+200)=0 或（==1 且 vt+248 剩余硬直 < v9））:
//               vt+228(this, 1, v9, 0)          ★★★ 施加/延长 stuck 状态
//                                               （= 主状态写入器，研究 §4.2 —— hit stop 本体）
//       vt+640(this, a2, a3)                    ★ HITEFF 通用命中特效（0x4E88A0，研究 §5.2）
//       读 attackinfo+92（VC6 std::string）→ 非空 → vt+212 播自定义 wav
// 核验结论：反编译体**逐条吻合**研究 §3 伪码（含 attackinfo+132 → vt+228 直连实证，
// 研究第 14 轮"表现壳全文（attackinfo+132→vt+228 直连实证）"）。
// 研究 §15 复用价值 #1：本函数一次调用同时携带 受击者/攻击者/硬直时长/格挡位
// —— 比 HP 锚点更上游；硬直时长 attackinfo+132 可直接读出。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5DC0(uint32_t *this, int nArg2, int nArg3, char pszArg4)  // 【表现壳（hit stop 施加点，研究 §3 全文定案）】
{
  int pVt; // eax
  int nDmgKind; // eax
  int nDmgState; // ebx
  int pAnim; // ebx
  int nStuckMs; // ebx
  int nMainState; // eax
  int pAttackInfo; // eax
  unsigned int nSndLen; // ecx
  int pSndStr; // eax
  char bBladeFlag; // cl
  int nOutSlot; // [esp+8h] [ebp-4h] BYREF

  pVt = *this;
  nOutSlot = 100;
  nDmgKind = (*(int (/*thiscall*/ **)(uint32_t *, int *, int))(pVt + 648))(this, &nOutSlot, nArg2);  // vt+648 伤害类型（0/1 正常，2 = 落空）
  if ( pszArg4 != 0 )  // 格挡分支
  {
    if ( nDmgKind != 2 )  // 若 nDmgKind != 2
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 644))(this, nArg2, nArg3);  // ★ vt+644 格挡特效（GuardSpark/GuardCircle/Stuck.ani）
      bBladeFlag = *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128);  // attackinfo+128 = 刀剑标志
      nOutSlot = 0;
      if ( bBladeFlag != 0 )  // 若 bBladeFlag 非 0
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *))(*this + 212))(this, "STUCK_BLADE");  // ★ 刀剑"卡肉"音效
        return 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, const char *))(*this + 212))(this, "STUCK_BLUNT");  // ★ 钝器"卡肉"音效
    }
  }
  else if ( nDmgKind != 2 )
  {
    if ( *((uint8_t *)this + 642) != 0 )  // this+642〔bHitBoxSnap642〕
    {
      nDmgState = *(this + 161);  // 帧时刻覆盖时的盒快照
    }
    else  // 否则分支
    {
      pAnim = *(this + 30);  // this+120〔pAnimObj〕
      if ( pAnim == 0 )  // 若 pAnim 为 0
      {
LABEL_10:  // 标签 LABEL_10（跳转合流点）
        nStuckMs = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 132);  // ★★ attackinfo+132 = 本次命中硬直时长（hit stop 时长）
        if ( nStuckMs > 0 )  // 若 nStuckMs > 0
        {
          nMainState = *(this + 50);  // this+200 = 主状态
          if ( nMainState == 0 || nMainState == 1 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 248))(this) < nStuckMs )  // 剩余硬直 < 新时长才延长
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 228))(this, 1, nStuckMs, 0);  // ★★★ 施加/延长 stuck（hit stop 本体）
        }
        goto LABEL_15;
      }
      if ( *(uint32_t *)(pAnim + 148) == -1 )
        sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      nDmgState = *(uint32_t *)(pAnim + 112);  // 动画对象 +112 = 伤害态
    }
    if ( nDmgState != 2 )  // 伤害态 == 2 → 跳过 stuck，直接 HITEFF
      goto LABEL_10;
LABEL_15:  // 标签 LABEL_15（跳转合流点）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 640))(this, nArg2, nArg3);  // ★ HITEFF 通用命中特效（·0x4E88A0）
    pAttackInfo = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 调虚槽 +348：取坐标对象
    nSndLen = *(uint32_t *)(pAttackInfo + 116);  // attackinfo+92 起 std::string（+116 = 长度）
    pSndStr = pAttackInfo + 92;
    if ( nSndLen < 0x10 )  // SSO 内联
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 212))(this, pSndStr + 4, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    else  // 否则分支
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        *(uint32_t *)(pSndStr + 4),  // 自定义受击 wav
        -1,
        0,
        0);
    return 0;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E5F30 sub_4E5F30 —— 路径/名称拼接（%s%s，左 = ·this+364 内联 std::string）
// 经 ·dword_8F84E4 vt+12 格式化器返回（容量 >= 16 时取堆指针）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E5F30(uint32_t *this, int nArg2)  // 实现：路径/名称拼接（%s%s，左 = ·this+364 内联 std::string）
{
  uint32_t *pThis_5B; // eax

  if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
    pThis_5B = this + 91;
  else  // 否则分支
    pThis_5B = (uint32_t *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
  return (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", pThis_5B, nArg2);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
}



// ------------------------------------------------------------
// 0x4E5F70 sub_4E5F70 —— ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
// 研究 §5.1 原文："硬直率掷（sub_4E5F70）同构（rand()%10000 < 率×100），
//   掷完把结果+rand 种机打包发服务器背书"。
// 调用点：本地扫掠 sub_4E82B0 命中后（`sub_4E5F70(a1, v5, v27, 1, 1)`）——
//   即本地命中即刻把"硬直掷结果"上报服务端（客户端信任伤害架构，研究 §11 第 14 轮）。
// ------------------------------------------------------------
void /*usercall*/ sub_4E5F70(int nArg1@<ebx>, int nArg2, int nArg3, float *pArg4, char pszArg5, char pszArg6)  // 实现：硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
{
  int pAttacker; // esi
  int pVictim; // edi
  int pAttacker2; // esi
  int pVictim2; // edi
  int pAttVt; // eax
  int pAttackInfo; // eax
  char bStuckFlag; // cl
  int nStackCount; // ecx
  int pOwnerUid; // ebx
  int pOwner; // eax
  int pOwner2; // eax
  double fStuckRate; // st7
  int nSceneType; // eax
  int nSinceHit; // eax
  double fRateMul; // st7
  int pPkt; // ebx
  int nSelfUid; // eax
  int pPkt2; // ebx
  int nSelfUid2; // eax
  int pPkt3; // esi
  int nSelfUid3; // eax
  int pPkt4; // esi
  int nSelfUid4; // eax
  float *pHitBox; // esi
  int nSendRet; // eax
  int pPkt5; // esi
  int nRand; // eax
  float fRateSum; // [esp+4h] [ebp-Ch]
  float fRateBase; // [esp+4h] [ebp-Ch]
  int n32Buf; // [esp+8h] [ebp-8h] BYREF
  float fStuckChance; // [esp+Ch] [ebp-4h]

  pAttacker = nArg2;
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    pVictim = nArg3;
    if ( nArg3 != 0 )  // 若 nArg3 非 0
    {
      sub_432FA0();  // srand 播种
      pAttacker2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker + 380))(pAttacker);  // vt+380 取本体
      pVictim2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 380))(pVictim);  // 调虚槽 +380：点击命中框
      if ( pszArg5 == 0  // 若 pszArg5 为 0
        || (pAttVt = *(uint32_t *)pVictim2, nArg2 = 100, (*(int (/*thiscall*/ **)(int, int *, int))(pAttVt + 648))(pVictim2, &nArg2, pAttacker2) != 3) )  // 非 3 = 有伤害类
      {
        HIBYTE(nArg2) = 0;  // 结果字节（打包前暂存）
        if ( pszArg6 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 40))(pVictim2, 17) != 0 )  // 受方是怪物
        {
          pAttackInfo = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pAttacker2 + 348))(pAttacker2, nArg1);  // attackinfo
          bStuckFlag = *(uint8_t *)(pAttackInfo + 80);  // attackinfo+80 = 【推断】硬直率标志
          fStuckChance = *(float *)(pAttackInfo + 76) + 3.0;  // 基础硬直率 + 3.0
          if ( bStuckFlag != 0 )  // 若 bStuckFlag 非 0
          {
            nStackCount = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 364))(pAttacker2) + 8);  // 攻方当前连击/叠加数
            if ( nStackCount > 1 )  // 若 nStackCount > 1
              fStuckChance = (double)(nStackCount * (nStackCount + 1) / 2 - 1) + fStuckChance;  // 三角数加成
          }
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim2 + 632))(pVictim2) < 50 )  // vt+632 距上次受击毫秒 < 50 → 连续受击
          {
            pOwnerUid = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 576))(pAttacker2);  // 调虚槽 +576
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim2 + 636))(pVictim2) != pOwnerUid )  // 上次攻击者非同一人
              fStuckChance = fStuckChance - 5.0;
          }
          if ( (uint8_t)sub_4E5AF0(pVictim2, pAttacker2) != 0 )  // ★ 背击判定
            fStuckChance = fStuckChance - 5.0;
          fRateSum = 0.0;
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 576))(pAttacker2) != 0 )  // 调虚槽 +576
          {
            pOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 576))(pAttacker2);  // 调虚槽 +576
            pOwner2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwner + 672))(pOwner, 3);  // 调虚槽 +672：自身 HP
            fRateSum = sub_43B5A0(pOwner2 + 1264);  // 防篡读 +1264 = 硬直率附加
          }
          fStuckRate = ((double (/*thiscall*/ *)(int, int))*(uint32_t *)(*(uint32_t *)pVictim2 + 704))(pVictim2, pAttacker2) + fRateSum;  // vt+704(攻) 受方硬直率基础
          nSceneType = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
          fRateBase = fStuckRate;
          if ( nSceneType == 4 || nSceneType == 6 )  // 竞技场/战场
          {
            nSinceHit = sub_4E4610(pVictim2);  // 距上次受击毫秒（研究 §15 第 15 轮定案：vt+632）
            if ( nSinceHit != -1 && nSinceHit < 10000 )  // 若 nSinceHit != -1 与/或 nSinceHit < 10000
            {
              sub_4049C0(0.0, 1.0, nSinceHit, 10000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】10000ms 窗口线性衰减
              fRateBase = fStuckRate * fRateBase;
            }
          }
          fRateMul = fRateBase + fStuckChance;
          fStuckChance = fRateMul;
          if ( fRateMul > 0.0 && fStuckChance * 100.0 > (double)(rand() % 10000) )  // 率×100 vs rand%10000
          {
            sub_4D8730(pVictim2);  // 记录本次受击时刻（vt+632 写侧）
            HIBYTE(nArg2) = 1;
          }
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 19, 2);  // 硬直背书包 type 19 / 2 子字段
        pPkt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfUid = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 48))(pAttacker2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        (*(void (/*thiscall*/ **)(int, int))(pPkt + 36))(dword_8F8520, nSelfUid);  // 会话/UDP 管理器
        pPkt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfUid2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker2 + 52))(pAttacker2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        (*(void (/*thiscall*/ **)(int, int))(pPkt2 + 36))(dword_8F8520, nSelfUid2);  // 会话/UDP 管理器
        pPkt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfUid3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim2 + 48))(pVictim2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        (*(void (/*thiscall*/ **)(int, int))(pPkt3 + 36))(dword_8F8520, nSelfUid3);  // 会话/UDP 管理器
        pPkt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfUid4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim2 + 52))(pVictim2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        (*(void (/*thiscall*/ **)(int, int))(pPkt4 + 36))(dword_8F8520, nSelfUid4);  // 会话/UDP 管理器
        pHitBox = pArg4;
        (*(void (/*thiscall*/ **)(int, float *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pArg4, 4);  // 命中盒首 float
        n32Buf = (uint64_t)pHitBox[1];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &n32Buf, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        n32Buf = (uint64_t)pHitBox[2];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &n32Buf, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        n32Buf = (uint64_t)pHitBox[3];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &n32Buf, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        n32Buf = (uint64_t)pHitBox[4];
        (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &n32Buf, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        n32Buf = (uint64_t)pHitBox[5];
        nSendRet = (*(int (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &n32Buf, 2);  // 6 个盒分量收紧为 4 字节
        LOBYTE(nSendRet) = HIBYTE(nArg2) != 0;
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nSendRet);  // 硬直掷结果
        pPkt5 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nRand = rand();  // nRand = 调 rand
        (*(void (/*thiscall*/ **)(int, int))(pPkt5 + 36))(dword_8F8520, nRand);  // 顺手带上随机种子
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 发送
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4E62B0 sub_4E62B0 —— ★★★ 攻击盒 vs 受击盒碰撞判定（研究 P29 盒模型，第 24/25 轮）
// 签名：__cdecl(a1 = 攻击者, a2 = 攻击动画对象, a3 = 受击者, a4 = 受击动画对象, a5 = ？)
// 门：a2/a4 非空；`a1->vt+600 != 0` 且 `a3->vt+608 != 0`
//     —— ★ 攻/防使能门（研究 P29：`vt+600/608 = this+640/641 攻防使能门`；
//        研究 P35：this+641 = 受击盒使能 = 无敌开关）。
// 盒提取：`v7 = a2 + 116`（★ 攻击盒 = 动画对象+116）、`v38 = a4 + 132`
//         （★ 受击盒 = 动画对象+132）—— 研究 P29 原文"攻击盒=动画+116/受击盒=动画+132，24B/盒"，
//         且先 sub_4FEF30(盒) 校验（空 vector 返回 0）。
// 迭代：v8 遍历攻击盒（24 字节步距：4 float 边界 + 2 个 int），每盒：
//   `vt+152()` 为 0（朝左）→ **盒 x 镜像 `v23 = -v23 - v26`**（研究 P29：
//      "朝左镜像 x=−x−w"）；再加本体的 x/y/z（vt+120/124/128）→ 世界坐标
//   内层 while 遍历受击盒数组（v38+4..v38+8，同样 24 字节步距）逐盒镜像化后
//     调 **sub_491130(&攻击盒, &受击盒世界坐标, a5)** —— ★ 研究 P29 定案的
//     3D AABB 分离轴测试本体（"尺寸0=禁用"），返回非 0 → 本函数返回 1（命中）
// 调用者：0x4D6A80（多命中盒 vt+480）/ 0x4E6570（单盒包装）——
//   研究 §1.2 "主盒 + this+120+204 附加盒链表逐盒 sub_4E62B0"。
// 研究 P29 补充：命中区域 = 两盒交集 AABB（由 sub_491130 输出）。
// ------------------------------------------------------------
char /*cdecl*/ sub_4E62B0(int *pDwArg1, int pArg2, int *pDwArg3, int pArg4, int nArg5)  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
{
  int pArg42; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  bool v9; // zf
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // edi
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // ecx
  float v23; // [esp+4h] [ebp-3Ch] BYREF
  float v24; // [esp+8h] [ebp-38h]
  float v25; // [esp+Ch] [ebp-34h]
  float v26; // [esp+10h] [ebp-30h]
  int v27; // [esp+14h] [ebp-2Ch]
  int v28; // [esp+18h] [ebp-28h]
  float v29; // [esp+1Ch] [ebp-24h] BYREF
  float v30; // [esp+20h] [ebp-20h]
  float v31; // [esp+24h] [ebp-1Ch]
  float v32; // [esp+28h] [ebp-18h]
  int v33; // [esp+2Ch] [ebp-14h]
  int v34; // [esp+30h] [ebp-10h]
  int v35; // [esp+34h] [ebp-Ch]
  int v36; // [esp+38h] [ebp-8h]
  int v37; // [esp+3Ch] [ebp-4h]
  int v38; // [esp+4Ch] [ebp+Ch]

  if ( pArg2 == 0 || pArg4 == 0 )  // 若 pArg2 == 0 与/或 pArg4 == 0
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 600))(pDwArg1) == 0  // 调虚槽 +600：无敌门
    || (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg3 + 608))(pDwArg3) == 0 )  // 调虚槽 +608：无敌门
  {
    return 0;
  }
  if ( *(uint32_t *)(pArg2 + 148) == -1 )  // pArg2+148〔fAdd148(推断)〕
    sub_4938F0(pArg2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  pArg42 = pArg4;
  v6 = *(uint32_t *)(pArg4 + 148);  // pArg4+148〔fAdd148(推断)〕
  v7 = pArg2 + 116;
  v35 = pArg2 + 116;
  if ( v6 == -1 )
  {
    sub_4938F0(pArg4);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    pArg42 = pArg4;
  }
  v38 = pArg42 + 132;
  if ( sub_4FEF30(v7) == 0 )  // 若调用结果为真
    return 0;
  if ( sub_4FEF30(v38) == 0 )  // 若调用结果为真
    return 0;
  v8 = *(uint32_t *)(v7 + 4);
  v9 = v8 == *(uint32_t *)(v7 + 8);
  v23 = 0.0;
  v24 = 0.0;
  v25 = 0.0;
  v26 = 0.0;
  v27 = 0;
  v28 = 0;
  v29 = 0.0;
  v30 = 0.0;
  v31 = 0.0;
  v32 = 0.0;
  v33 = 0;
  v34 = 0;
  v37 = v8;
  if ( v9 )
    return 0;
  while ( 1 )  // 条件循环
  {
    v23 = *(float *)v8;
    v24 = *(float *)(v8 + 4);
    v25 = *(float *)(v8 + 8);
    v26 = *(float *)(v8 + 12);
    v27 = *(uint32_t *)(v8 + 16);
    v11 = *(uint32_t *)(v8 + 20);
    v12 = *pDwArg1;
    v28 = v11;
    if ( (*(int (/*thiscall*/ **)(int *))(v12 + 152))(pDwArg1) == 0 )  // 调虚槽 +152：效果通道 3
      v23 = -v23 - v26;
    v36 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调虚槽 +120：动画对象
    v13 = *pDwArg1;
    v23 = (double)v36 + v23;
    v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 124))(pDwArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    v15 = *pDwArg1;
    v36 = v14;
    v24 = (double)v14 + v24;
    v36 = (*(int (/*thiscall*/ **)(int *))(v15 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    v16 = *(uint32_t *)(v38 + 4);
    v17 = *(uint32_t *)(v38 + 8);
    v25 = (double)v36 + v25;
    if ( v16 != v17 )  // 若 v16 != v17
      break;  // 跳出循环/分支
LABEL_21:  // 标签 LABEL_21（跳转合流点）
    v22 = *(uint32_t *)(v35 + 8);
    v37 += 24;
    if ( v37 == v22 )  // 若 v37 == v22
      return 0;
    v8 = v37;
  }
  while ( 1 )  // 条件循环
  {
    v29 = *(float *)v16;
    v30 = *(float *)(v16 + 4);
    v31 = *(float *)(v16 + 8);
    v32 = *(float *)(v16 + 12);
    v33 = *(uint32_t *)(v16 + 16);
    v18 = *pDwArg3;
    v34 = *(uint32_t *)(v16 + 20);
    if ( (*(int (/*thiscall*/ **)(int *))(v18 + 152))(pDwArg3) == 0 )  // 调虚槽 +152：效果通道 3
      v29 = -v29 - v32;
    v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 120))(pDwArg3);  // 调虚槽 +120：动画对象
    v20 = *pDwArg3;
    v36 = v19;
    v29 = (double)v19 + v29;
    v36 = (*(int (/*thiscall*/ **)(int *))(v20 + 124))(pDwArg3);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    v21 = *pDwArg3;
    v30 = (double)v36 + v30;
    v36 = (*(int (/*thiscall*/ **)(int *))(v21 + 128))(pDwArg3);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    v31 = (double)v36 + v31;
    if ( (uint8_t)sub_491130(&v23, &v29, nArg5) != 0 )  // AABB 包围盒相交测试（6 float 盒：）
      return 1;  // 返回 1(成功)
    v16 += 24;
    if ( v16 == *(uint32_t *)(v38 + 8) )
      goto LABEL_21;
  }
}


// ------------------------------------------------------------
// 0x4E6520 sub_4E6520 —— 命中目标列表成员查询（this+164 vector，4 字节 id 数组）
// 与 0x4E6FD0（链表摘除）/ 0x4E7040（移除 + vt+468 回调）成族 ——
// 目标记忆列表（研究 §1.2 vt+356 "记录当前命中目标（目标记忆，锁定连打用）"的后端）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E6520(uint32_t *this, int nArg2)  // 实现：命中目标列表成员查询（this+164 vector，4 字节 id 数组）
{
  int fld_e164; // esi
  unsigned int i; // edx

  fld_e164 = *(this + 164);
  for ( i = 0; fld_e164 != 0 && i < (*(this + 165) - fld_e164) >> 2; ++i )  // 遍历循环
  {
    if ( *(uint32_t *)(*(this + 164) + 4 * i) == nArg2 )
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4E6570 sub_4E6570 —— 攻击盒碰撞包装（vt+200 取盒 → ·0x4E62B0）
// v4 = pDwArg2 vt+200；转 ·sub_4E62B0(this, ·this+120, pDwArg2, v4, nArg3)
// ------------------------------------------------------------
char /*thiscall*/ sub_4E6570(int *this, int *pDwArg2, int nArg3)  // 实现：攻击盒碰撞包装（vt+200 取盒 → ·0x4E62B0）
{
  int v4; // eax

  v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 200))(pDwArg2);  // 调虚槽 +200：取动画对象
  return sub_4E62B0(this, *(this + 30), pDwArg2, v4, nArg3);  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
}



// ------------------------------------------------------------
// 0x4E65A0 sub_4E65A0 —— 命中豁免判定（条件 33 门 + 盒使能 + 已命中名单）
// 双方条件 33 至少一方 且 vt+428/432 盒使能非 0 且 vt+488 重叠，否则 false；
// 自身条件 33 → (vt+672 的 +8 − 1)：0 分支 → 对方 vt+436 <= 0；1 分支 → ·sub_4E6520 名单不含；对方对称分支
// ------------------------------------------------------------
bool /*thiscall*/ sub_4E65A0(uint32_t *this, uint32_t *pArg2)  // 实现：命中豁免判定（条件 33 门 + 盒使能 + 已命中名单）
{
  int v3; // eax
  int v5; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 33) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 428))(this) == 0  // 调虚槽 +428
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 432))(this) == 0  // 调虚槽 +432
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 428))(pArg2) == 0  // 调虚槽 +428
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 432))(pArg2) == 0  // 调虚槽 +432
    || (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 488))(this, pArg2) == 0 )  // 调虚槽 +488：★ 3D AABB 重叠测试（无 z 轴；俯视平面）
  {
    return false;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 33) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this) + 8) - 1;  // 调虚槽 +672：自身 HP
    if ( v3 != 0 )  // 若 v3 非 0
    {
      if ( v3 == 1 && sub_4E6520(this, (int)pArg2) == 0 )  // 命中目标列表成员查询（this+164 vector，4 字节 id 数组）
        return true;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 436))(pArg2) <= 0 )  // 调虚槽 +436
    {
      return true;
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 33) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    return false;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 672))(pArg2) + 8) - 1;  // 调虚槽 +672：自身 HP
  if ( v5 == 0 )  // 若 v5 为 0
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this) <= 0;  // 调虚槽 +436
  return v5 == 1 && sub_4E6520(pArg2, (int)this) == 0;  // 命中目标列表成员查询（this+164 vector，4 字节 id 数组）
}



// ------------------------------------------------------------
// 0x4E66B0 sub_4E66B0 —— 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
// 场景 4 → 50；场景 6 → ·dword_8F7C48 表 [10×队伍 + 1]（int16，队伍 = ·dword_8F7A24+40 的 +76）；
// pszArg2==0 → vt+388（攻击上下文默认值）；否则车主 vt+792(8)：无 → 1，有 → 其 vt+16 → +24
// ------------------------------------------------------------
int /*thiscall*/ sub_4E66B0(void *this, char pszArg2)  // 实现：场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
{
  int pThis_240; // eax
  int pObj2; // eax
  int pObj; // esi
  int pObj3; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // 登录/选区管理器
    return 50;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )  // 登录/选区管理器
    return *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76) + 1);  // 登录/选区管理器
  if ( pszArg2 == 0 )  // 若 pszArg2 为 0
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
  pThis_240 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 576))(this);  // 调虚槽 +576
  pObj2 = __RTDynamicCast(pThis_240, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // pObj2 = 调 __RTDynamicCast
  pObj = pObj2;
  if ( pObj2 == 0 )  // 若 pObj2 为 0
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 388))(this);  // 调虚槽 +388：属性块（vt+672(3)）首 DWORD
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, 8) == 0 )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
    return 1;  // 返回 1(成功)
  pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 8);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
  return *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3) + 24);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
}



// ------------------------------------------------------------
// 0x4E6770 sub_4E6770 —— ★★★ 伤害流水线 / vt+628（研究 P14 九步公式全文定案）
// 【更正·转写体为准】角色方向：this = **受击者**（vt+632 距上次受击/vt+143 仇人 id/vt+144 连击数/
//   18 观察者逐槽 全在 this 上）；a5(pDwArg5) = **攻击者**（attackinfo 从其 vt+348 取，
//   属性一致/攻击力/暴击加成项全部出自其车主链）。
// 签名：__thiscall(this = 攻击者, a2 = 输出标志槽, a3 = 输出槽, a4 = ？, a5 = 受击者, a6 = 命中盒,
//                   a7 = float 位（!=0 时作为固定伤害值覆盖）)
// 调用点 = 命中主处理器 0x4D71B0 ⑥（研究 §2：vt+648(类型) → vt+628(伤害)）。
// 反编译体与研究 P14 九步及《21 速查》P14-P16 的对应：
//   ⓪ **时间/随机基准**：`*(float*)&a7 == 0` 时 v8 = clock(this+9)*7 + clock(this+2)
//      + a6[2]*3 + a6[1]*2 + a6[0]（命中盒 + 时钟的复合"hash 种子"，用于后续 ± 方差）
//      否则 v8 = 传入的固定伤害值（整数化）
//   ① 取攻击定义 v12 = a5->vt+348(attackinfo)
//   ② **基础门**：`a4 <= 0 || (attackinfo+16 == 0 && float+0 <= 0)` → 返回 0（无伤害）
//   ③ **属性一致 ×1.05**：`attackinfo+20`（属性攻击位）非 4 且 == 攻击者属性块 +4 的
//      属性 id → **伤害 × 1.05**（研究 P14 九步第 2 步"属性一致×1.05"）
//   ④ **抗性减免**：`v86+20 != 4` 且 RTDynamicCast 成功 → 取 sub_4DA0F0(属性id)
//      → `伤害 × (flt_9A0624 − 抗性 × flt_9A0628) × 0.0099999998`
//      （研究 P14 九步第 3 步"抗性"；flt_9A06xx = 运行时加载的平衡系数，PE 内全 0，
//       研究 §11"防御/抗性平衡系数运行时从数据文件加载"）
//   ⑤ **伤害大类初值**：v20 = attackinfo+12（0 物理 / 1 魔法 / 2 忽略防御）
//      —— 魔法(1) 用 flt_9A061C + sub_4E66B0(**角色特性/属性抗** 查询) × flt_9A0620
//   ★ **± 方差**（研究 P14 九步第 4 步）：`sub_4049C0(-v85, v85, sub_4D33A0(&v83)%1000, 999)`
//      —— LCG 取值 %1000 作插值 t，在 [−v85, +v85] 内线性取值（± 方差），并加到伤害
//   ★ **防御×(1−减伤)**（第 5 步）：受击者 vt+716 取二路减伤 (v85, v82) →
//      `伤害 ×= (1.0 − v85 − v82)`；再按压/魔 (-子 8 或 10) 从属性块 (+1138/+1180)
//      经 PVE/PVP 系数 sub_433F60 扣防御
//   ★ **攻击力**（第 6 步）：物理走受击者 vt+392 + flt_9A05F8，魔法走 vt+408 + flt_9A0610，
//      均 `经 sub_433F60(场景) × 值 ÷ flt` 后加到伤害
//   ★ **武器/技能项**（第 7 步）：attackinfo+4/+8 双格 × (1 + attackinfo+16 加成 与
//      受方 vt+400/vt+404 或 vt+416/vt+420 的百分比项) ÷ 100，再 × sub_433F60(场景) 加算
//   ★ **暴击率组装**（第 8 步）：`v85 = attackinfo+72 + 3.0`（基础暴击率 + 3.0）
//      + 宿主加成（受->vt+576 → 其属性块 +1222 或 +1208 经 sub_41A5E0 防篡读）
//      + **背击加成 attackinfo+144**（若 sub_4E5AF0 判定为背击）+
//        车主链项 (+1250 或 +1236 经防篡浮点壳 sub_43B5A0)
//      − 受方抗性（v18 → 属性块 +1278）
//   ★★ **暴击掷 + ×1.5**（第 9 步，研究 §5.1 第 14 轮实证点）：
//      `v80 = sub_4D33A0(&v83); % 10000`；`v85*100 > roll` 成立 → `*a2 = 1`（暴击位）
//      **且 `a7 = a7 * 1.5`**；否则 `*a2 = 0`（非暴击）
//      —— 与《21 速查》P14 "掷 hash%10000 < 率×100" 逐字吻合（率×100 即 v85×100）。
//   ★ **快速连打加伤**（研究 §5.1 第 14 轮："≥20 连 ×1.02-1.6，<20 连 1% 翻倍"）：
//      v60 = vt+632（★ 距上次受击毫秒，研究第 15 轮更正语义）；v60 >= 50 或
//      受方车主 == 攻方[143]（刚打过）→ *a3 = 0、攻方[144] = 1（连击计数复位）
//      否则车主条件 273 成立且 v60 >= 20 → sub_4049C0(200.0, 100.0, v60, 50) 插值
//      （50→200ms 区间内 200→100 线性递减 = **1.02..1.6 的加伤倍率来源**）；
//      v60 < 20 → `rand()%100 < 1` 即 **1% 概率伤害翻倍**（v62 = a7 + a7）
//      + 连击计数攻方[144] 递增夹取 4 + sub_4278D0(1, 级) + 受方为玩家时 sub_495A70 播音
//   ★ **终段**：`a7 × attackinfo+148 × 0.01 × a4 × 0.01`（技能倍率）；
//      vt+16 持有标签 16/17 → 再 × attackinfo+84/+88 × 0.01（[human damage rate]/
//      [fort damage rate] 对人型/城械倍率，研究 §3 字段表）；下限夹取 1.0；
//      最后遍历攻方 18 观察者 ->vt+164(受, 盒, *a2 暴击位, &a7) —— 观察者侧收尾修饰。
// ✅ 与研究 P14 九步**逐条吻合**（含"属性一致×1.05 / 抗性 / ±方差 / 防御×(1−减伤) /
//    攻击力 / 武器 / 暴击掷 / 快速连打加伤 / 技能倍率"全部九步）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E6770(uint32_t *this, uint8_t *uArg2, uint32_t *uArg3, int nArg4, int *pDwArg5, float *pArg6, int nArg7)  // 【伤害流水线 vt+628（研究 P14 九步公式）】
{
  uint32_t *pDefender; // ebx
  double fSeedBase; // st7
  int nClock7x; // esi
  int pAttVtbl; // edx
  int pAttackInfo; // edi
  int64_t qwRetZero; // rax
  int pSceneObj; // eax
  int nSceneElemId; // eax  // ·this+29→+132→+44→+4 攻击上下文的属性 id【推断】
  int pDefenderObjA; // eax
  int pAttackInfoBak; // ecx
  int pDefenderObj; // edi
  int nResistVal; // eax
  int nDmgType; // eax
  double fResistTerm; // st7
  char bElemFlag; // al
  int nRoll; // eax
  double fNegAmp; // st7
  int pVictimVtbl2; // ebx
  int nSceneFactor; // eax
  int nDmgType4; // eax
  int nPhysDefBlk; // eax
  int nPhysDefVal; // eax
  double fDefCoef; // st7
  int pDefBlk; // eax
  int nMagDefVal; // eax
  double fMagDefCoef; // st7
  int nDmgType2; // eax
  double fAtkTerm; // st7
  int nDmgType3; // eax
  double fDmgBase; // st7
  int bAddFlag; // eax
  int pVictimVtbl3; // edx
  double fWpnCoef; // st7
  int pDefBlk2; // eax
  int nDefVal; // eax
  double fDmgBase2; // st7
  char bElemFlag3; // al
  int pVictimVtbl4; // edx
  double fWpnCoef2; // st7
  int pDefBlk3; // eax
  double fDefCoef2; // st7
  int pVictimVtbl5; // edx
  int pOwnerObj4; // eax
  int nCritAddOff; // eax
  int pOwnerObj2; // eax
  int pVictimVtbl6; // edx
  int pObj; // eax
  int nBackAtkOff; // ecx
  int pOwnerObj3; // eax
  double fBackAtkRate; // st7
  int nResistOff; // eax
  double fRollVal; // st7
  int nSinceHitMs; // edi
  int pOwnerObj5; // eax
  double fDoubleDmg; // st7
  double fComboMul; // st7
  int nCombo; // eax
  bool bComboLt3; // sf
  int pOwnerObj; // eax
  int pOwnerCharTmp; // eax
  int pOwnerChar; // edi
  int nOwnerUid; // eax
  int pOwnerChar2; // eax
  int pDefenderChar; // edi
  int i; // ebx
  int pObserver; // eax
  float v75; // [esp+Ch] [ebp-34h]
  int nDmgTypeIn; // [esp+14h] [ebp-2Ch]
  int nElemId; // [esp+18h] [ebp-28h]
  char bElemFlag2; // [esp+18h] [ebp-28h]
  int nDefRoute; // [esp+18h] [ebp-28h]
  int nRoll2; // [esp+28h] [ebp-18h] BYREF
  float v81; // [esp+2Ch] [ebp-14h]
  float v82; // [esp+30h] [ebp-10h] BYREF
  int nHashSeed; // [esp+34h] [ebp-Ch] BYREF
  uint32_t *pDefenderBak; // [esp+38h] [ebp-8h]
  float v85; // [esp+3Ch] [ebp-4h] BYREF
  int fld_e14; // [esp+54h] [ebp+14h]

  pDefender = this;
  pDefenderBak = this;
  if ( *(float *)&nArg7 == 0.0 )
  {
    nClock7x = 7 * sub_699000((int)(this + 9));  // 【clock_now(clk)】
    LODWORD(v82) = sub_699000((int)(pDefender + 2)) + nClock7x;  // 【clock_now(clk)】
    fSeedBase = (double)SLODWORD(v82) + pArg6[2] * 3.0 + pArg6[1] + pArg6[1] + *pArg6;
  }
  else  // 否则分支
  {
    nArg7 = *(int *)nArg7;
    fSeedBase = (double)(unsigned int)nArg7;
  }
  pAttVtbl = *pDwArg5;
  nHashSeed = (uint64_t)fSeedBase;
  pAttackInfo = (*(int (/*thiscall*/ **)(int *))(pAttVtbl + 348))(pDwArg5);  // a5->vt+348 = attackinfo（攻方）
  fld_e14 = pAttackInfo;
  if ( nArg4 <= 0 || *(uint8_t *)(pAttackInfo + 16) == 0 && *(float *)pAttackInfo <= 0.0 )  // 无伤害 → 返回 0
  {
    LODWORD(qwRetZero) = 0;
    return qwRetZero;
  }
  *(float *)&nArg7 = ((double (/*thiscall*/ *)(int *, int, int *))*(uint32_t *)(*pDwArg5 + 424))(pDwArg5, pAttackInfo, &nHashSeed);  // 攻方 vt+424 基础伤害（种子哈希）
  pSceneObj = pDefender[29];  // pSceneObj = 取 pDefender[29]
  if ( pSceneObj != 0 )  // 若 pSceneObj 非 0
  {
    nSceneElemId = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pSceneObj + 132) + 44) + 4);  // 攻方属性 id
    if ( nSceneElemId != 4 && nSceneElemId == *(uint32_t *)(pAttackInfo + 20) )  // attackinfo+20 = 伤害属性
      *(float *)&nArg7 = *(float *)&nArg7 * 1.05;  // ★ 属性一致 ×1.05（九步第 2 步）
  }
  pDefenderObjA = __RTDynamicCast(
          (int)pDefender,
          0,
          &IRDCollisionObject `RTTI Type Descriptor',
          &IRDActiveObject `RTTI Type Descriptor',
          0);
  pAttackInfoBak = pAttackInfo;
  pDefenderObj = pDefenderObjA;
  if ( *(uint32_t *)(pAttackInfo + 20) != 4 && pDefenderObjA != 0 )  // 若 pDefenderObjA != 0
  {
    nElemId = *(uint32_t *)(pAttackInfo + 20);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
    nResistVal = sub_4DA0F0(nElemId);  // 受方属性抗性值
    pAttackInfoBak = pAttackInfo;
    v82 = *(float *)&nResistVal;
    *(float *)&nArg7 = (flt_9A0624 - (double)nResistVal * flt_9A0628) * *(float *)&nArg7 * 0.0099999998;  // ★ 抗性减免（九步第 3 步；系数运行时加载）
  }
  nDmgType = *(uint32_t *)(pAttackInfoBak + 12);
  v85 = 0.0;
  if ( nDmgType != 0 )  // 若 nDmgType 非 0
  {
    if ( nDmgType == 1 )  // 若 nDmgType == 1
    {
      bElemFlag = *(uint8_t *)(pAttackInfoBak + 16);
      v85 = flt_9A061C;
      v82 = COERCE_FLOAT(sub_4E66B0(bElemFlag));  // 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
      fResistTerm = (double)SLODWORD(v82) * flt_9A0620 + v85;
    }
    else  // 否则分支
    {
      if ( nDmgType != 2 )  // 若 nDmgType != 2
        goto LABEL_22;
      fResistTerm = *(float *)&nArg7 * 0.07000000000000001;
    }
  }
  else  // 否则分支
  {
    bElemFlag2 = *(uint8_t *)(pAttackInfoBak + 16);
    v85 = flt_9A0604;
    v82 = COERCE_FLOAT(sub_4E66B0(bElemFlag2));  // 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
    fResistTerm = (double)SLODWORD(v82) * flt_9A0608 + v85;
  }
  v85 = fResistTerm;  // 伤害大类初值（0 物理 / 1 魔法 / 2 无视防御，attackinfo+12）
LABEL_22:  // 标签 LABEL_22（跳转合流点）
  if ( byte_9A05F0 != 0 )  // 若 byte_9A05F0 非 0
    v85 = 0.0;  // 全局开关：关闭方差
  nRoll = sub_4D33A0(&nHashSeed);  // nRoll = 调 sub_4D33A0 返回值
  fNegAmp = -v85;
  v75 = fNegAmp;
  sub_4049C0(v75, v85, nRoll % 1000, 999);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】★ ±方差（九步第 4 步）
  *(float *)&nArg7 = fNegAmp + *(float *)&nArg7;
  if ( pDefenderObj != 0 && *(uint32_t *)(pAttackInfo + 12) != 2 && *(uint8_t *)(pAttackInfo + 82) == 0 )  // 若 pDefenderObj != 0
  {
    pVictimVtbl2 = *(uint32_t *)pDefenderObj;
    nDmgTypeIn = *(uint32_t *)(pAttackInfo + 12);
    v85 = 0.0;
    v82 = 0.0;
    nSceneFactor = sub_4E66B0(0);  // 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
    (*(void (/*thiscall*/ **)(int, float *, float *, int, int, int))(pVictimVtbl2 + 716))(pDefenderObj, &v85, &v82, nSceneFactor, nDmgTypeIn, 3);  // 受方 vt+716 取二路减伤
    *(float *)&nArg7 = (1.0 - v85 - v82) * *(float *)&nArg7;  // ★ 防御×(1−减伤)（九步第 5 步）
    nDmgType4 = *(uint32_t *)(pAttackInfo + 12);
    if ( nDmgType4 != 0 )  // 若 nDmgType4 非 0
    {
      if ( nDmgType4 == 1 )  // 若 nDmgType4 == 1
      {
        pDefBlk = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
        nMagDefVal = sub_4DA0B0(pDefBlk);  // nMagDefVal = 调 sub_4DA0B0 返回值
        pDefender = pDefenderBak;
        v81 = (float)nMagDefVal;
        fMagDefCoef = sub_433F60(pDefenderBak, 6);  // fMagDefCoef = 调 sub_433F60 返回值
        *(float *)&nArg7 = *(float *)&nArg7 - fMagDefCoef * v81 / flt_9A0618;
      }
      else  // 否则分支
      {
        pDefender = pDefenderBak;
      }
    }
    else  // 否则分支
    {
      nPhysDefBlk = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
      nPhysDefVal = sub_4DA080(nPhysDefBlk);  // nPhysDefVal = 调 sub_4DA080 返回值
      pDefender = pDefenderBak;
      v81 = (float)nPhysDefVal;
      fDefCoef = sub_433F60(pDefenderBak, 4);  // fDefCoef = 调 sub_433F60 返回值
      *(float *)&nArg7 = *(float *)&nArg7 - fDefCoef * v81 / flt_9A0600;
    }
  }
  nDmgType2 = *(uint32_t *)(pAttackInfo + 12);
  if ( nDmgType2 != 0 )  // 若 nDmgType2 非 0
  {
    if ( nDmgType2 != 1 )  // 若 nDmgType2 != 1
      goto LABEL_37;
    v81 = (float)(*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 408))(pDwArg5);  // 调虚槽 +408：装备槽解绑
    fAtkTerm = sub_433F60(pDwArg5, 5) * v81 / flt_9A0610;  // fAtkTerm = 调 sub_433F60 返回值
  }
  else  // 否则分支
  {
    v81 = (float)(*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 392))(pDwArg5);  // 调虚槽 +392：HP 类属性读取（属性块 +60 防篡读 × 浮点壳 +74）
    fAtkTerm = sub_433F60(pDwArg5, 3) * v81 / flt_9A05F8;  // fAtkTerm = 调 sub_433F60 返回值
  }
  *(float *)&nArg7 = fAtkTerm + *(float *)&nArg7;  // ★ 攻击力项（九步第 6 步：物理 vt+392 / 魔法 vt+408 经场景系数路由）
LABEL_37:  // 标签 LABEL_37（跳转合流点）
  nDmgType3 = *(uint32_t *)(pAttackInfo + 12);
  if ( nDmgType3 != 0 )  // 若 nDmgType3 非 0
  {
    if ( nDmgType3 != 1 )  // 若 nDmgType3 != 1
      goto LABEL_50;
    fDmgBase2 = (double)*(int *)(pAttackInfo + 4);
    bElemFlag3 = *(uint8_t *)(pAttackInfo + 16);
    v85 = fDmgBase2;
    if ( bElemFlag3 != 0 )  // 若 bElemFlag3 非 0
    {
      v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 420))(pDwArg5));  // 调虚槽 +420：[RTTI: IRDActiveObject__vmt1A4 · 槽位 IRDActiveO…
      fDmgBase2 = (double)SLODWORD(v81) + v85;
    }
    pVictimVtbl4 = *pDwArg5;
    v85 = ((double)*(int *)(pAttackInfo + 8) * 0.0099999998 + 1.0) * fDmgBase2;  // ×0.01f（百分数转比例）
    v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(pVictimVtbl4 + 416))(pDwArg5));  // v81 = 调 COERCE_FLOAT
    v85 = ((double)SLODWORD(v81) * 0.0099999998 + 1.0) * v85;  // ×0.01f（百分数转比例）
    fWpnCoef2 = sub_433F60(pDwArg5, 9);  // fWpnCoef2 = 调 sub_433F60 返回值
    *(float *)&nArg7 = fWpnCoef2 * v85 + *(float *)&nArg7;
    if ( pDefenderObj == 0 || *(uint8_t *)(pAttackInfo + 82) != 0 )  // 若 pDefenderObj == 0
      goto LABEL_50;
    pDefBlk3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
    nDefVal = sub_41A5E0(pDefBlk3 + 1180);  // crypt4byte 解密校验（·0x41A590 逆运算）
    nDefRoute = 10;
  }
  else  // 否则分支
  {
    fDmgBase = (double)*(int *)(pAttackInfo + 4);
    bAddFlag = *(uint8_t *)(pAttackInfo + 16);
    v85 = fDmgBase;
    if ( (uint8_t)bAddFlag != 0 )
    {
      v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 404))(pDwArg5));  // 调虚槽 +404：整数属性读取（+1124）
      fDmgBase = (double)SLODWORD(v81) + v85;
    }
    pVictimVtbl3 = *pDwArg5;
    v85 = ((double)*(int *)(pAttackInfo + 8) * 0.0099999998 + 1.0) * fDmgBase;  // ×0.01f（百分数转比例）
    v81 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(pVictimVtbl3 + 400))(pDwArg5));  // v81 = 调 COERCE_FLOAT
    v85 = ((double)SLODWORD(v81) * 0.0099999998 + 1.0) * v85;  // ×0.01f（百分数转比例）
    fWpnCoef = sub_433F60(pDwArg5, 7);  // fWpnCoef = 调 sub_433F60 返回值
    *(float *)&nArg7 = fWpnCoef * v85 + *(float *)&nArg7;
    if ( pDefenderObj == 0 || *(uint8_t *)(pAttackInfo + 82) != 0 )  // 若 pDefenderObj == 0
      goto LABEL_50;
    pDefBlk2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
    nDefVal = sub_41A5E0(pDefBlk2 + 1138);  // crypt4byte 解密校验（·0x41A590 逆运算）
    nDefRoute = 8;
  }
  v81 = *(float *)&nDefVal;
  fDefCoef2 = sub_433F60(pDefender, nDefRoute);  // fDefCoef2 = 调 sub_433F60 返回值
  *(float *)&nArg7 = *(float *)&nArg7 - fDefCoef2 * (double)SLODWORD(v81);
LABEL_50:  // 标签 LABEL_50（跳转合流点）
  if ( *(float *)&nArg7 < 0.0 )
    *(float *)&nArg7 = 0.0;
  pVictimVtbl5 = *pDwArg5;
  v85 = *(float *)(pAttackInfo + 72) + 3.0;  // ★ 暴击率初值 = attackinfo+72 + 3.0（九步第 8 步）
  if ( (*(int (/*thiscall*/ **)(int *))(pVictimVtbl5 + 576))(pDwArg5) != 0 )  // 攻方有车主 → 叠宿主加成
  {
    if ( *(uint32_t *)(pAttackInfo + 12) != 0 )  // 魔法类 → 属性块 +1222
    {
      pOwnerObj2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
      nCritAddOff = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwnerObj2 + 672))(pOwnerObj2, 3) + 1222;  // 调虚槽 +672：自身 HP
    }
    else  // 物理类 → 属性块 +1208
    {
      pOwnerObj4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
      nCritAddOff = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwnerObj4 + 672))(pOwnerObj4, 3) + 1208;  // 调虚槽 +672：自身 HP
    }
    v81 = COERCE_FLOAT(sub_41A5E0(nCritAddOff));  // 防篡读（P24）
    v85 = v81 + v85;
  }
  if ( (uint8_t)sub_4E5AF0(pDefender, pDwArg5) != 0 )  // ★ 背击判定 → 加 attackinfo+144 背击暴击加成
  {
    pVictimVtbl6 = *pDwArg5;
    v85 = v85 + *(float *)(pAttackInfo + 144);
    if ( (*(int (/*thiscall*/ **)(int *))(pVictimVtbl6 + 576))(pDwArg5) != 0 )
    {
      if ( *(uint32_t *)(pAttackInfo + 12) != 0 )
      {
        pOwnerObj3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
        nBackAtkOff = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwnerObj3 + 672))(pOwnerObj3, 3) + 1250;  // 调虚槽 +672：自身 HP
      }
      else  // 否则分支
      {
        pObj = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
        nBackAtkOff = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3) + 1236;  // 调虚槽 +672：自身 HP
      }
      fBackAtkRate = sub_43B5A0(nBackAtkOff);  // 防篡浮点壳读（P27）
      v85 = fBackAtkRate + v85;
    }
  }
  if ( pDefenderObj != 0 )  // 若 pDefenderObj 非 0
  {
    nResistOff = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderObj + 672))(pDefenderObj, 3);  // 调虚槽 +672：自身 HP
    v81 = COERCE_FLOAT(sub_41A5E0(nResistOff + 1278));  // 受方抗暴击项
    v85 = v85 - v81;
  }
  nRoll2 = sub_4D33A0(&nHashSeed);  // nRoll2 = 调 sub_4D33A0 返回值
  LODWORD(v81) = sub_4D33A0(&nRoll2) % 10000;  // 掷 0..9999
  fRollVal = (double)SLODWORD(v81);
  if ( v85 * 100.0 <= fRollVal )  // ★★ 暴击掷：率×100 vs roll（研究 §5.1）
  {
    *uArg2 = 0;  // 非暴击
  }
  else  // 否则分支
  {
    fRollVal = *(float *)&nArg7 * 1.5;  // ★★ 暴击 ×1.5（研究 §5.1 第 14 轮实证）
    *uArg2 = 1;
    *(float *)&nArg7 = fRollVal;
  }
  nSinceHitMs = (*(int (/*thiscall*/ **)(uint32_t *))(*pDefender + 632))(pDefender);  // vt+632 距上次受击毫秒
  if ( nSinceHitMs >= 50 || (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5) == pDefender[143] )  // 间隔够久或同一仇人
  {
    *uArg3 = 0;
    pDefender[144] = 1;  // 连击计数复位为 1
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5) != 0 )  // 调虚槽 +576
  {
    pOwnerObj5 = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pOwnerObj5 + 40))(pOwnerObj5, 273) == 1 )  // 攻方车主受击态
    {
      if ( nSinceHitMs >= 20 )  // ★ 快速连打加伤（20ms..50ms 窗口）
      {
        sub_4049C0(200.0, 100.0, nSinceHitMs, 50);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】50→200ms 内 200→100 递减
        fComboMul = fRollVal * 0.0099999998;  // ×0.01f（百分数转比例）
        *(float *)&nArg7 = *(float *)&nArg7 * fComboMul;
        *uArg3 = (uint64_t)(fComboMul * *(float *)&nArg7 - *(float *)&nArg7);
      }
      else if ( rand() % 100 < 1 )  // < 20ms → 1% 概率伤害翻倍
      {
        fDoubleDmg = *(float *)&nArg7 + *(float *)&nArg7;
        *(float *)&nArg7 = fDoubleDmg;
        *uArg3 = (uint64_t)fDoubleDmg;
      }
      nCombo = pDefender[144] + 1;
      bComboLt3 = pDefender[144] - 3 < 0;
      pDefender[144] = nCombo;
      if ( bComboLt3 == __OFSUB__(nCombo, 4) )
        nCombo = 4;  // 连击计数夹取 4
      pDefender[144] = nCombo;
      sub_4278D0(1, nCombo);
      pOwnerObj = (*(int (/*thiscall*/ **)(int *))(*pDwArg5 + 576))(pDwArg5);  // 调虚槽 +576
      pOwnerChar = __RTDynamicCast(pOwnerObj, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // pOwnerChar = 调 __RTDynamicCast
      pOwnerChar = pOwnerChar;
      if ( pOwnerChar != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pOwnerChar + 308))(pOwnerChar) != 0 )  // 攻方是本地玩家 → 播连击音
      {
        nOwnerUid = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pOwnerChar + 52))(pOwnerChar);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_495A70(dword_99FD58, 1, 1, nOwnerUid);  // 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
      }
    }
  }
  *(float *)&nArg7 = *(float *)&nArg7 * *(float *)(pAttackInfo + 148) * 0.0099999998 * (double)nArg4 * 0.0099999998;  // ★ 终段：技能倍率（attackinfo+148 × a4）
  if ( (uint8_t)sub_4DAB60(16) != 0 )  // 标签/条件集合成员判定
    *(float *)&nArg7 = *(float *)&nArg7 * *(float *)(pAttackInfo + 84) * 0.0099999998;  // [human damage rate] 对人型倍率
  if ( (uint8_t)sub_4DAB60(17) != 0 )  // 标签/条件集合成员判定
    *(float *)&nArg7 = *(float *)&nArg7 * *(float *)(pAttackInfo + 88) * 0.0099999998;  // [fort damage rate] 对城械倍率
  if ( *(float *)&nArg7 < 1.0 )
    *(float *)&nArg7 = 1.0;  // 下限夹取 1.0
  pOwnerChar2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pDefender + 576))(pDefender);  // 调虚槽 +576
  pDefenderChar = __RTDynamicCast(pOwnerChar2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // pDefenderChar = 调 __RTDynamicCast
  if ( pDefenderChar != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDefenderChar + 308))(pDefenderChar) != 0 )  // 本地玩家 → 18 观察者逐槽收尾修饰
  {
    for ( i = 0; i < 18; ++i )  // 18 观察者槽（每件装备一个观察者，docs/15）
    {
      if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderChar + 792))(pDefenderChar, i) != 0 )  // vt+792(槽) 取观察者
      {
        pObserver = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDefenderChar + 792))(pDefenderChar, i);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
        (*(void (/*thiscall*/ **)(int, int *, float *, uint32_t, int *))(*(uint32_t *)pObserver + 164))(  // 观察者 vt+164 伤害收尾钩子
          pObserver,
          pDwArg5,
          pArg6,
          (uint8_t)*uArg2,
          &nArg7);
      }
    }
  }
  return (uint64_t)*(float *)&nArg7;
}


// ------------------------------------------------------------
// 0x4E6FD0 sub_4E6FD0 —— 从 ·this+164 命中名单移除指定 id（memmove 压缩）
// 遍历 4 字节 id vector，命中即删除并压缩（尾指针 -= 4，不中断循环）
// ------------------------------------------------------------
void /*thiscall*/ sub_4E6FD0(uint32_t *this, int nArg2)  // 实现：从 ·this+164 命中名单移除指定 id（memmove 压缩）
{
  unsigned int i; // edi
  int fld_e164; // ecx

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e164 = *(this + 164);
    if ( fld_e164 == 0 || i >= (*(this + 165) - fld_e164) >> 2 )  // 若 fld_e164 == 0
      break;  // 跳出循环/分支
    if ( *(uint32_t *)(fld_e164 + 4 * i) == nArg2 )
    {
      memcpy_0(
        (void *)(*(this + 164) + 4 * i),
        (const void *)(*(this + 164) + 4 * i + 4),
        4 * ((int)(*(this + 165) - (*(this + 164) + 4 * i + 4)) >> 2));
      *(this + 165) -= 4;
    }
  }
}



// ------------------------------------------------------------
// 0x4E7040 sub_4E7040
// ------------------------------------------------------------
// vmt1CC 命中目标列表移除（L1 精修版见 src/cnrd/IRDCollisionObject.cpp:269）：
// this+332 命中名单里线性找 nArg2 → memmove 压缩回退尾部 → vt+468(this,nArg2) 通知。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7040(uint32_t *this, int nArg2)  // 实现：命中目标列表移除
{
  uint32_t *fld_e84; // ecx
  uint32_t *result; // eax

  fld_e84 = (uint32_t *)*(this + 84);
  result = (uint32_t *)*(this + 83);  // this+332〔bReservedConn〕
  if ( result != fld_e84 )  // 若 result != fld_e84
  {
    do  // do-while 循环体起点
    {
      if ( *result == nArg2 )
        break;  // 跳出循环/分支
      ++result;
    }
    while ( result != fld_e84 );  // 条件循环
    if ( result != fld_e84 )  // 若 result != fld_e84
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 84) - (int)(result + 1)) >> 2));
      *(this + 84) -= 4;
      return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 468))(this, nArg2);  // 调虚槽 +468
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E70B0 sub_4E70B0 —— std::string 拼接构造（拷贝 + 插入）
// ·sub_4014D0 拷贝 pArg2 → ·sub_4022F0 在 pos 0 插入 pszArg3 → 结果写 pArg1（容量/长度按 SSO 15 复位）
// ------------------------------------------------------------
int /*cdecl*/ sub_4E70B0(int pArg1, size_t *pArg2, char *pszArg3)  // 实现：std::string 拼接构造（拷贝 + 插入）
{
  size_t *nLen; // eax
  size_t v5; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v7; // [esp+1Ch] [ebp-18h]
  unsigned int v8; // [esp+20h] [ebp-14h]
  int v9; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  v9 = 0;
  v8 = 15;
  v7 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0(&v5, pArg2, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  v10 = 0;
  nLen = sub_4022F0((std::_String_base *)&v5, (int)pszArg3, pszArg3, strlen(pszArg3));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  *(uint32_t *)(pArg1 + 24) = 15;  // pArg1+24〔nPageMax(推断)〕
  *(uint32_t *)(pArg1 + 20) = 0;  // pArg1+20〔nPage(推断)〕
  *(uint8_t *)(pArg1 + 4) = 0;  // pArg1+4〔宿主对象〕
  sub_4014D0((size_t *)pArg1, nLen, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  if ( v8 >= 0x10 )  // 若 v8 >= 0x10
    j__free(Block);
  return pArg1;
}



// ------------------------------------------------------------
// 0x4E7160 sub_4E7160 —— 受击/动作字段复位（研究 §1.2 字段表坐标逐个可读）
// 置位分布（本工程研究文档字段表交叉验证）：
//   this+96 = 1（动作子对象存在标志）
//   this+572 = 0 / **this+568 = −1（★ 最后受击时刻复位 —— 研究 §1.1 字段表 +568）**
//   this+576 = 1（车主/归属 id 哨兵）/ +580/+584 = 0 / +588/+592 = −1
//   this+608 = 0（**受击盒使能** —— 研究 P35：this+641 是另一路；+608 见 P29 攻防门）
//   **this+636 = 0（★ 反应优先级复位 —— 研究 §15 三层状态的优先级字段）**
//   **this+642 = 0（★ 碰撞盒快照标志，§1.2 表现壳的 this+642/644）** / +644 = 0（盒快照槽）
//   this+668/+672 = 0
//   **this+612 = 1（★ 动作使能字节 —— 研究 §1.2 vt+556 = 该字节 setter、setState 门）**
//   **this+616 = −1（★ 反应态复位为 −1 哨兵 —— 研究 §15 反应态字段）**
//   **this+640 = 1（★ 攻击盒使能 —— 研究 P29 攻/防使能门 vt+600/608 = this+640/641）**
//   **this+641 = 1（★ 受击盒使能 = 无敌开关 —— 研究 P35 vt+604 广播目标）**
// 返回 −1（"未初始化/无参照"哨兵）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7160(int this)  // 实现：受击/动作字段复位（研究 §1.2 字段表坐标逐个可读）
{
  *(uint32_t *)(this + 96) = 1;  // this+96〔nStatusMode(推断)〕等 2 字段
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 572) = 0;
  *(uint32_t *)(this + 568) = -1;  // this+568〔nAlarmVal〕
  *(uint32_t *)(this + 576) = 1;  // this+576〔uOffset576〕
  *(uint32_t *)(this + 580) = 0;  // this+580〔uOffset580〕
  *(uint32_t *)(this + 584) = 0;
  *(uint32_t *)(this + 588) = -1;
  *(uint32_t *)(this + 592) = -1;
  *(uint32_t *)(this + 608) = 0;  // this+608〔nAttackGate〕
  *(uint32_t *)(this + 636) = 0;  // this+636〔nReactionPriority〕
  *(uint8_t *)(this + 642) = 0;  // this+642〔bHitBoxSnap642〕
  *(uint32_t *)(this + 644) = 0;  // this+644〔uHitBoxSnap644〕
  *(uint32_t *)(this + 668) = 0;  // this+668〔nPickupXCache(推断)〕
  *(uint32_t *)(this + 672) = 0;  // this+672〔nPickupValid(推断)〕
  *(uint8_t *)(this + 612) = 1;
  *(uint32_t *)(this + 616) = -1;  // this+616〔nReactionState〕
  *(uint8_t *)(this + 640) = 1;
  *(uint8_t *)(this + 641) = 1;  // this+641〔bHitBoxEnable〕
  return -1;
}



// ------------------------------------------------------------
// 0x4E7200 sub_4E7200 —— STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
// 元素数 >= 0x1FFFFFFE → 构造 std::length_error(map/set<T> too long) 抛出（·sub_4015C0 + ·sub_401740）；
// ·sub_5648C0 分配节点 → 按 root/左/右挂接 → 平衡循环：·sub_433130 左旋 / ·sub_4296E0 右旋；返回插入位置 *uArg2
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7200(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // 实现：STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  void **pExceptionObject; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v17[20]; // [esp+34h] [ebp-28h] BYREF
  int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )  // this+8〔nSkillRec8(推断)〕
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // 商店文本（23 行）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // 若 pArg4 == fld_e12
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;  // this+4〔宿主对象〕
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else  // 否则分支
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )  // 条件循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];  // v14 = 取 v13[2]
        if ( *(uint8_t *)(v14 + 20) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);  // 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:  // 标签 LABEL_21（跳转合流点）
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;  // 跳出循环/分支
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4E73B0 sub_4E73B0 —— ★ 出生/复活重置（研究 P35 第 31 轮定案）
// 研究原文："0x4E7160/4E73B0 = 出生/复活重置（**全状态归零 + 双盒使能**）"。
// 反编译体逐条对应：
//   sub_498C40(this)（基类复位）+ **sub_4A3450(this+97)（★ 攻击上下文默认值，研究 P29：
//     "sub_4B2970/4A3450 = 攻击上下文拷贝/默认值（盒半宽17、量程100.0f）"）**
//   vt+352（动作状态复位）/ **+612 = 1（动作使能）** / vt+572（？）/ **vt+596(this, 1)**
//   / **vt+604(this, 1)（★ 双盒使能之一 —— 与 P35 "死亡无敌 vt+604(0)" 对照，
//     复活时置 1 = 恢复受击）** / vt+612(this, 0, 0)
//   +142 = −1 / +143 = 0（**★ 最后受击时刻 +568 / 仇人 id +572 复位，
//     与 0x4D4A80/0x4E48D0 写入点成对**）
//   +145/+146/+147/+148 = 0/0/−1/−1（★ 位置采样双缓冲复位，与 0x4E5410 采样对成对）
// 调用点 = 0x4D6970（角色出生/复活初始化，本工程 combat_core.cpp）
//   与 0x4E4430 的 Boss 终局（vt+604(0) 死亡无敌）互为对偶 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E73B0(int *this)  // 实现：出生/复活重置（研究 P35 第 31 轮定案）
{
  int v2; // edx

  sub_498C40(this);  // 五组虚槽批量重置
  sub_4A3450(this + 97);  // this+97〔bFlag97〕
  (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
  v2 = *this;
  *((uint8_t *)this + 612) = 1;  // this[612] = 1
  (*(void (/*thiscall*/ **)(int *))(v2 + 572))(this);
  (*(void (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
  (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);  // 调虚槽 +612
  *(this + 142) = -1;  // this+568〔nAlarmVal〕
  *(this + 143) = 0;  // this+572〔复位〕
  *(this + 145) = 0;  // this+580〔uOffset580〕
  *(this + 147) = -1;
  *(this + 146) = 0;
  *(this + 148) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x4E7440 sub_4E7440 —— ★ 攻击上下文设置 vmt158（研究 P29 定案）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp:213（0x4E7440 vmt158）。
// 研究 P29 原文："sub_4B2970/4A3450 = 攻击上下文拷贝/默认值（盒半宽17、量程100.0f）"
// —— 本函数即该族入口：a2 非空 → sub_4B2970（拷贝）；否则 sub_4A3450(this+388)（取默认）
// → 尾调 vt+352（动作状态复位）。this+388 = 攻击上下文结构（研究 §13 观察者接口
// "+128 攻击开始（收攻击上下文 this+388）"）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7440(char *this, int nArg2)  // 实现：攻击上下文设置（研究 P29 已引: sub_4B2970 拷贝/4A3450 默认）
{
  char *pThis_184; // ecx

  pThis_184 = this + 388;
  if ( nArg2 != 0 )  // 若 nArg2 非 0
    sub_4B2970(nArg2);  // 部件记录拷贝（同 ·0x4B2820）
  else  // 否则分支
    sub_4A3450(pThis_184);
  return (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 352))(this);  // 调虚槽 +352：命中列表双链表清空
}



// ------------------------------------------------------------
// 0x4E7480 sub_4E7480
// ------------------------------------------------------------
// vmt12C 目标移除联动（L1 精修版见 src/cnrd/IRDCollisionObject.cpp:226）：
// ·sub_499190 通知宿主 → 目标条件 1 成立则从命中名单移除(·0x4E6FD0) →
// this+2160/this+2384 两处查找表清理三键 → 仇人 this+572 与 this+668 若指目标则清空。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7480(int this, int nArg2)  // 实现：目标移除联动（命中列表清除 + 双向链表更新）
{
  int pObj; // ebx
  int result; // eax
  int *v5; // [esp+8h] [ebp-4h] BYREF

  pObj = nArg2;
  sub_499190((uint32_t *)this, nArg2);  // 帧索引归零联动（命中则复位并 vt+84(0)）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 1) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    sub_4E6FD0((uint32_t *)this, pObj);  // 从 ·this+164 命中名单移除指定 id（memmove 压缩）
  sub_4BE520((int **)(this + 540), &v5, &nArg2);  // 映射下界查找（lower_bound）
  if ( v5 != *(int **)(this + 544) )  // this+544〔nFaction〕
    sub_4A3130((uint32_t *)(this + 540), (int ***)&v5, (int **)v5);
  sub_4BE520((int **)(this + 596), &v5, &nArg2);  // 映射下界查找（lower_bound）
  if ( v5 != *(int **)(this + 600) )
    sub_4A3130((uint32_t *)(this + 596), (int ***)&nArg2, (int **)v5);
  result = 0;
  if ( *(uint32_t *)(this + 572) == pObj )
    *(uint32_t *)(this + 572) = 0;
  if ( *(uint32_t *)(this + 668) == pObj )  // this+668〔nPickupXCache(推断)〕
    *(uint32_t *)(this + 668) = 0;  // this+668〔nPickupXCache(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4E7530 sub_4E7530 —— map 插入包装（二分定位 + 复用旧节点或新建）
// 手动二分到 fld_e1；新键更小：表首 → ·sub_4E7200 新建，否则 ·sub_4A3B30 取前驱；
// 键已存在 → 返回旧节点（+4 = 0）；否则 ·sub_4E7200 插入；pArg2 = {节点, 是否新插入}
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7530(uint32_t *this, int pArg2, uint32_t *uArg3)  // 实现：map 插入包装（二分定位 + 复用旧节点或新建）
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do  // do-while 循环体起点
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else  // 否则分支
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );  // 条件循环
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_4E7200(this, &uArg3, 1, fld_e1, (int)uArg32);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 取后继再插
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else  // 否则分支
  {
    v12 = *sub_4E7200(this, &uArg3, v13, fld_e1, (int)uArg32);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4E75F0 sub_4E75F0 —— uint32 vector 区间插入（容量 1.5 倍增长 + 三段搬运）
// 溢出保护 ·sub_4A30C0（0x3FFFFFFF 上限）；容量足：原地 ·sub_55E7F0/·sub_5DAF70 后移 + ·sub_49A9D0 填充；
// 容量不足：新容量 = 1.5× 或精确值 → new + ·sub_523700 填充 + 两段 memcpy → 释放旧块
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E75F0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 实现：uint32 vector 区间插入（容量 1.5 倍增长 + 三段搬运）
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  void *v15; // eax
  int fld_43; // eax
  int fld_87; // ecx
  unsigned int v18; // edi
  uint8_t *fld_83; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *fld_84; // edi
  int v24; // edi
  char *pMem; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    result = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_4A30C0(this);
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);  // fld_83 = 读 this+8
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )  // 若 v21 >= uArg3
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else  // 否则分支
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // this+8〔nSkillRec8(推断)〕等 2 字段
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else  // 否则分支
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else  // 否则分支
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // v15 = 调 sub_523700 返回值
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
      return (unsigned int)pMem;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E77D0 sub_4E77D0 —— uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
// 源空 → 释放清空并置空；容量够 → memcpy 调整尾指针；不够 → 释放 + ·sub_42CFD0 预留 + ·sub_55E7F0 拷贝；
// 其余 → ·sub_433A30 前置拷贝 + ·sub_55E7F0 尾部
// ------------------------------------------------------------
int /*thiscall*/ sub_4E77D0(int this, int pArg2)  // 实现：uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
{
  int v3; // ecx
  unsigned int v4; // edx
  void *fld_4; // ecx
  unsigned int fld_8; // ebx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  int fld_82; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )  // 若 this == pArg2
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2) == 0 )  // 若 v3 == 0
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;
  }
  fld_4 = *(void **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( v4 <= fld_8 )  // 若 v4 <= fld_8
  {
    memcpy_0(fld_4, *(const void **)(pArg2 + 4), 4 * ((*(uint32_t *)(pArg2 + 8) - *(uint32_t *)(pArg2 + 4)) >> 2));  // pArg2+8〔nSkillRec8(推断)〕
    v8 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v8 != 0 )  // 若 v8 非 0
      fld_42 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 2);  // fld_42 = 读 this+4
    else  // 否则分支
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;
  if ( v4 > fld_C )  // 若 v4 > fld_C
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v13 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v13 != 0 )  // 若 v13 非 0
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
    else  // 否则分支
      v14 = 0;
    if ( (uint8_t)sub_42CFD0(v14) != 0 )  // vector 预留（4B 元素）
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));  // 商城状态（10 行）
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_82 = 0;
  v12 = (void *)(*(uint32_t *)(pArg2 + 4) + 4 * fld_82);  // pArg2+4〔宿主对象〕
  sub_433A30(*(void **)(pArg2 + 4), (int)v12, *(void **)(this + 4));  // dword 区间拷贝
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8));  // 商城状态（10 行）
  return this;
}



// ------------------------------------------------------------
// 0x4E7920 sub_4E7920 —— STL map 插入分发（表首/表尾特判 + 左/右插入）
// 空表 → ·sub_4E7200 建根；pArg3 为表首/表尾按键比较选左/右；否则二分后按兄弟空位选边；
// 落点已存在 → 复用 ·sub_4E7530 的结果
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E7920(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // 实现：STL map 插入分发（表首/表尾特判 + 左/右插入）
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_4E7200((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // fld_4 = 读 this+4
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4E7200((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )  // 若 pArg3 == fld_4
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4E7200((uint32_t *)this, uArg2, 0, v8, (int)pArg4);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )  // 若 pArg4 = pArg3
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:  // 标签 LABEL_22（跳转合流点）
      v9 = *(uint32_t *)sub_4E7530(v10, pArg42);  // map 插入包装（二分定位 + 复用旧节点或新建）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4E7200((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    else  // 否则分支
      sub_4E7200((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    return uArg2;
  }
  else  // 否则分支
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4E7200((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    else  // 否则分支
      sub_4E7200((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);  // STL map 插入（0x18 节点 + 红黑平衡；超长抛 length_error）
    return uArg2;
  }
}



// ============================================================
// 【分区 D】受击反应 / 命中特效生成 / 本地扫掠（0x4E7A80 - 0x4E9760）
//   ★ 研究 20 三条主链的落点：setState（三层状态）→ 本地扫掠（先于服务端包）
//   → HITEFF/CRITHIT/UNIONHIT（表现层全要素）。
// ============================================================

// ------------------------------------------------------------
// 0x4E7A80 sub_4E7A80 —— ★★★ 受击反应 setState / vt+560（研究 20 §1.2/§15 定案）
// 签名：__thiscall(this = 受击者, a2 = 反应态 id, a3 = 打包参数对象, a4 = 优先级, a5 = 强制位)
// 研究 §15 定案（三层状态架构）：`this+616` = 反应态、`this+636` = 优先级，
//   **"反应优先级仲裁 vt+560 sub_4E7A80（只升不降）"**。
// 转写体与研究定案的逐条对应：
//   门① `this[612] != 0`（动作使能字节，研究 §1.2 vt+556 = 该字节的 setter（setState 门））
//   门② `vt+308 != 0 || a5 != 0`（本地玩家对象 或 强制）
//   门③ `(条件 529 == 0) || (this+616 != 5)` —— 研究 §15/§14：529 与状态 5（击倒）特例
//   门④ `*(this+154) == -1 || *(this+159) <= a4` —— ★ **只升不降仲裁本体**
//        （word 下标 154 = 字节 +616 当前反应态；159 = 字节 +636 当前优先级）
//   命中后：`this[154] = a2`（写反应态）+ `this[613] = 0`（清"已上报"标志，
//        配合 0x4E8130 的位移同步包）+ a3 非空 → sub_4ED3F0(this+620, a3) 装载参数
//        （否则 sub_5E5260 清空）+ `this[159] = a4`（写优先级）
// 调用点（研究 §2⑧ 受击反应三档，全部走本函数）：
//   state 3 受击硬直动作（左右方向随机、动作速度 = attackinfo+136，-1→1.0，
//           attackinfo+12==1 时 ×0.7）
//   state 4 击退（距离 = attackinfo+64，浮空 = attackinfo+68 + 暴击加成 +50/+250）
//   state 5 击倒（档位：距离 < 150 时看浮空（< 400 → 2 否则 5）；否则按相对站位 3）
// ⚠ 参数对应注（研究 §2⑧ 的写法 → 本转写体形参）：
//    研究写 `vt+560(this, 3, 打包参数, 优先级2)`，其中第 2 实参 3 = 反应态 → 本处 **a2**，
//    第 3 实参 = 打包参数 → 本处 **a3**，第 4 实参 = 优先级 → 本处 **a4**。
//    转写体实测：`*(this+154)=a2`（写反应态）、`*(this+159)=a4`（写优先级）—— 吻合。
// ------------------------------------------------------------
void /*thiscall*/ sub_4E7A80(uint32_t *this, int nArg2, int nArg3, int nArg4, char pszArg5)  // 【受击反应 setState vt+560（研究 §1.2/§15 三层状态只升不降仲裁）】
{
  void *pThis_9B; // ecx

  if ( *((uint8_t *)this + 612) != 0
    && ((*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 || pszArg5 != 0)  // 调虚槽 +308：是否本地玩家
    && ((*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 529) == 0 || *(this + 154) != 5)  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(this + 154) == -1 || *(this + 159) <= nArg4) )  // this+616〔nReactionState〕
  {
    *(this + 154) = nArg2;  // this+616〔nReactionState〕
    *((uint8_t *)this + 613) = 0;  // this[613] = 0
    pThis_9B = this + 155;
    if ( nArg3 != 0 )  // 若 nArg3 非 0
      sub_4ED3F0((int)pThis_9B, nArg3);  // int 向量拷贝赋值（全容量路径）
    else  // 否则分支
      sub_5E5260(pThis_9B);  // 调 动画子对象清理临时缓冲
    *(this + 159) = nArg4;  // this+636〔nReactionPriority〕
  }
}



// ------------------------------------------------------------
// 0x4E7B20 sub_4E7B20 —— map 查找或建节点并返回值槽（节点 +16）
// 二分到 fld_e1；命中且键满足 → 返回 fld_e1+16；否则 ·sub_4E7920 插入后返回 +16
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7B20(uint32_t *this, uint32_t *uArg2)  // 实现：map 查找或建节点并返回值槽（节点 +16）
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )  // 条件循环
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;
      v3 = (int *)*v3;
    }
    else  // 否则分支
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )  // 复合条件判定（与/或）
    return (int)(fld_e1 + 4);
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4E7920((int)this, &uArg2, fld_e1, v5) + 16;  // STL map 插入分发（表首/表尾特判 + 左/右插入）
}



// ------------------------------------------------------------
// 0x4E7BA0 sub_4E7BA0 —— 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
// 尾指针与容量比较（this+4/+8/+12 三字段容器），满则走带搬移的区间插入
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4E7BA0(int *this, int *pDwArg2)  // 实现：4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e2 = (*(this + 2) - fld_e1) >> 2;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )  // 若 fld_e1 == 0
    return sub_4E75F0((int)this, *(this + 2), 1u, pDwArg2);  // uint32 vector 区间插入（容量 1.5 倍增长 + 三段搬运）
  fld_e22 = (int *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4E7BF0 sub_4E7BF0 —— ★ 变长整数编码器（VLQ / 7 bit × n；网络序列化基元）
// 结构：`< 0x80` → 单字节直接写（或 sub_446710 追加）；`>= 0x80` 逐段：
//   每 7 bit 一组，低位组尾或 0x80 续位标志，从高到低 sub_446BE0 逐字节写出
//   （0x4000 / 0x200000 / 0x10000000 三段阈值 → 2/3/4/5 字节编码）。
// 研究 P31/P35 的 UDP 包序列化族基元（与位移序列化 sub_4E80E0 → sub_48D1E0 配合）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7BF0(int this, unsigned int uArg2)  // 实现：变长整数编码器（VLQ / 7 bit × n；网络序列化基元）
{
  int result; // eax
  int fld_4; // edx
  unsigned int fld_8; // edi
  uint8_t *fld_82; // ecx
  unsigned int uArg23; // ecx
  unsigned int v8; // edx
  unsigned int uArg22; // ecx
  unsigned int v10; // edx
  char v11; // [esp+4h] [ebp-4h] BYREF
  char v12; // [esp+5h] [ebp-3h] BYREF
  char v13; // [esp+6h] [ebp-2h] BYREF
  char v14; // [esp+7h] [ebp-1h] BYREF

  result = uArg2;
  if ( uArg2 >= 0x80 )  // 若 uArg2 >= 0x80
  {
    if ( uArg2 >= 0x4000 )  // 若 uArg2 >= 0x4000
    {
      if ( uArg2 >= 0x200000 )  // 若 uArg2 >= 0x200000
      {
        if ( uArg2 >= 0x10000000 )  // 若 uArg2 >= 0x10000000
        {
          v11 = uArg2 & 0x7F;  // 位掩码测试 &0x7F（位 0,1,2,3,4,5,6）
          uArg22 = uArg2;
          v14 = (uArg2 >> 7) | 0x80;
          v10 = uArg2 >> 21;
          HIBYTE(uArg2) = (uArg2 >> 28) | 0x80;
          v13 = (uArg22 >> 14) | 0x80;
          v12 = v10 | 0x80;
          sub_446BE0((char *)&uArg2 + 3);  // 调 逐字节写出
          sub_446BE0(&v12);  // 调 逐字节写出
          sub_446BE0(&v13);  // 调 逐字节写出
          sub_446BE0(&v14);  // 调 逐字节写出
          return sub_446BE0(&v11);  // 返回 调 sub_446BE0 返回值
        }
        else  // 否则分支
        {
          v12 = uArg2 & 0x7F;  // 位掩码测试 &0x7F（位 0,1,2,3,4,5,6）
          uArg23 = uArg2;
          v8 = uArg2 >> 14;
          HIBYTE(uArg2) = (uArg2 >> 21) | 0x80;
          v14 = (uArg23 >> 7) | 0x80;
          v13 = v8 | 0x80;
          sub_446BE0((char *)&uArg2 + 3);  // 调 逐字节写出
          sub_446BE0(&v13);  // 调 逐字节写出
          sub_446BE0(&v14);  // 调 逐字节写出
          return sub_446BE0(&v12);  // 返回 调 sub_446BE0 返回值
        }
      }
      else  // 否则分支
      {
        v13 = uArg2 & 0x7F;  // 位掩码测试 &0x7F（位 0,1,2,3,4,5,6）
        v14 = (uArg2 >> 7) | 0x80;
        HIBYTE(uArg2) = (uArg2 >> 14) | 0x80;
        sub_446BE0((char *)&uArg2 + 3);  // 调 逐字节写出
        sub_446BE0(&v14);  // 调 逐字节写出
        return sub_446BE0(&v13);  // 返回 调 sub_446BE0 返回值
      }
    }
    else  // 否则分支
    {
      HIBYTE(uArg2) = (uArg2 >> 7) | 0x80;
      v14 = uArg2 & 0x7F;  // 位掩码测试 &0x7F（位 0,1,2,3,4,5,6）
      sub_446BE0((char *)&uArg2 + 3);  // 调 逐字节写出
      return sub_446BE0(&v14);  // 返回 调 sub_446BE0 返回值
    }
  }
  else  // 否则分支
  {
    fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
    HIBYTE(uArg2) = uArg2;
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = *(uint32_t *)(this + 8) - fld_4;  // fld_8 = 读 this+8
    else  // 否则分支
      fld_8 = 0;
    if ( fld_4 != 0 && fld_8 < *(uint32_t *)(this + 12) - fld_4 )  // 若 fld_4 != 0
    {
      fld_82 = *(uint8_t **)(this + 8);  // fld_82 = 读 this+8
      *fld_82 = result;
      *(uint32_t *)(this + 8) = fld_82 + 1;  // this+8〔nSkillRec8(推断)〕等 2 字段
    }
    else  // 否则分支
    {
      return sub_446710(*(void **)(this + 8), 1, (int)&uArg2 + 3);  // 返回 调 sub_446710 返回值
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7DA0 sub_4E7DA0 —— VLQ 解码器（7 bit 累积，结束字节高位 0）
// 逐字节：v4 = (v4<<7) + (字节 & 0x7F)；字节 >= 0x80 继续，否则 push 到 a2（·sub_430C80 兜底追加）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7DA0(uint32_t *this, int nArg2)  // 实现：VLQ 解码器（7 bit 累积，结束字节高位 0）
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int nArg22; // esi
  char fld_e1; // al
  int v7; // edx
  unsigned int v8; // ecx
  int *v9; // eax
  uint32_t *pThis; // [esp+8h] [ebp-8h]
  int fld_e2; // [esp+Ch] [ebp-4h]

  result = *(this + 1);  // this+4〔宿主对象〕
  v3 = 0;
  v4 = 0;
  pThis = this;
  if ( result != 0 )  // 若结果非 0（成功）
    fld_e2 = *(this + 2) - result;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;
  if ( fld_e2 > 0 )  // 若 fld_e2 > 0
  {
    nArg22 = nArg2;
    do  // do-while 循环体起点
    {
      fld_e1 = *(uint8_t *)(v3 + *(this + 1));  // fld_e1 = 读 this+1
      v4 = (fld_e1 & 0x7F) + (v4 << 7);  // 位掩码测试 &0x7F（位 0,1,2,3,4,5,6）
      if ( fld_e1 >= 0 )  // 若 fld_e1 >= 0
      {
        v7 = *(uint32_t *)(nArg22 + 4);  // nArg22+4〔宿主对象〕
        nArg2 = v4;
        if ( v7 != 0 )  // 若 v7 非 0
          v8 = (*(uint32_t *)(nArg22 + 8) - v7) >> 2;  // nArg22+8〔nSkillRec8(推断)〕
        else  // 否则分支
          v8 = 0;
        if ( v7 != 0 && v8 < (*(uint32_t *)(nArg22 + 12) - v7) >> 2 )  // 若 v7 != 0
        {
          v9 = *(int **)(nArg22 + 8);  // nArg22+8〔nSkillRec8(推断)〕
          *v9 = v4;
          *(uint32_t *)(nArg22 + 8) = v9 + 1;  // nArg22+8〔nSkillRec8(推断)〕
        }
        else  // 否则分支
        {
          sub_430C80(*(void **)(nArg22 + 8), 1, (int)&nArg2);  // uint32 vector 区间插入（同值填充）
        }
        this = pThis;
        v4 = 0;
      }
      result = fld_e2;
      ++v3;
    }
    while ( v3 < fld_e2 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7E40 sub_4E7E40 —— this+652 vector push_back（容量不足 → ·sub_428220）
// 本条为命中/动作记录表的追加口（对象偏移 +652 起始的三字段容器）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7E40(char *this, int nArg2)  // 实现：this+652 vector push_back（容量不足 → ·sub_428220）
{
  char *pThis_28C; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *nArg22; // eax
  int result; // eax

  pThis_28C = this + 652;
  v3 = *((uint32_t *)pThis_28C + 1);
  if ( v3 != 0 )  // 若 v3 非 0
    v4 = (*((uint32_t *)pThis_28C + 2) - v3) >> 2;  // 向量元素数 = (end−begin)/4
  else  // 否则分支
    v4 = 0;
  if ( v3 == 0 || v4 >= (*((uint32_t *)pThis_28C + 3) - v3) >> 2 )  // 若 v3 == 0
    return sub_428220(*((void **)pThis_28C + 2), 1, (int)&nArg2);  // STL 内联 vector 插入（4B 元素）
  nArg22 = *((int **)pThis_28C + 2);
  *nArg22 = nArg2;
  result = (int)(nArg22 + 1);
  *((uint32_t *)pThis_28C + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4E7EA0 sub_4E7EA0 —— ★★ 1000ms 重复命中节流（研究 P29 第 24/25 轮定案）
// 研究 P29 原文："**sub_4E7EA0 = 1000ms 重复命中节流（同一挥击不重复打）**"。
// 转写体与定案逐条对应：
//   若 `*a2 != 0`（a2 为"节流表节点"指针，指向命中记录）：
//     先 sub_4BE520(&a2, &a3)（表内查找/定位）；
//     若 a2 != 表首（this+150）
//        且 `now − *(node+4) >= 1000`（★ 距上次记录 ≥ 1000ms）→
//           `*v3 = 0`（清调用方标志）+ 更新 `*(node+4) = now`（★ 刷新节流时间戳）
//   否则（首次）→ `sub_4E7B20(&a3)` 查/建节点 → `*node = now`
// 调用点：本地扫掠 0x4E82B0（`sub_4E7EA0((char*)&a3+3, v5)`）——
//   研究 §11 第 11 轮的"命中不重复"门 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7EA0(uint32_t *this, uint8_t *uArg2, int nArg3)  // 实现：1000ms 重复命中节流（研究 P29 第 24/25 轮定案）
{
  uint8_t *pInOutFlag; // ebx
  int *pNodeSlot; // edi
  int result; // eax
  uint8_t *pNode; // edi
  int pClock; // esi

  pInOutFlag = uArg2;
  if ( *uArg2 != 0 )  // 表内已有本次挥击记录 → 只有距上次 ≥1000ms 才允许再次命中
  {
    result = sub_4BE520(&uArg2, &nArg3);  // 映射下界查找（lower_bound）
    pNode = uArg2;
    if ( uArg2 != (uint8_t *)*(this + 150) )  // 命中记录节点存在（非表首哨兵）
    {
      pClock = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
      result = sub_699000(pClock) - *((uint32_t *)pNode + 4);  // 【clock_now(clk)】距上次记录毫秒
      if ( result >= 1000 )  // ★ 1000ms 节流窗口
      {
        *pInOutFlag = 0;  // 清调用方标志（允许本次命中）
        result = sub_699000(pClock);  // 【clock_now(clk)】
        *((uint32_t *)pNode + 4) = result;  // 刷新时间戳
      }
    }
  }
  else  // 首次：查/建节点并写入当前时刻
  {
    pNodeSlot = (int *)sub_4E7B20(&nArg3);  // map 查找或建节点并返回值槽（节点 +16）
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    *pNodeSlot = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E7F30 sub_4E7F30 —— 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
// 条件 17 + ·sub_4E4630 敌对 + 排除 vt+376 ∈ 200..204 与 vt+940（死亡/免疫）；
// 命中 → pArg4 追加（·sub_4E7BA0）并返回对象；否则返回 pArg4 首元素或 0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E7F30(uint32_t *this, signed int nArg2, signed int nArg3, int pArg4)  // 实现：半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v12; // edx
  int pObj; // esi
  int j; // edi
  int v15; // edi
  int v16; // edi
  int v18; // ecx
  int pObj3; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v20; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    v7 = *(uint32_t *)(fld_e29 + 120);
    v20 = i;
    if ( v7 != 0 )  // 若 v7 非 0
      v8 = (*(uint32_t *)(fld_e29 + 124) - v7) >> 2;  // 向量元素数 = (end−begin)/4
    else  // 否则分支
      v8 = 0;
    if ( (int)i >= v8 )
    {
      if ( pArg4 != 0 && (v18 = *(uint32_t *)(pArg4 + 4)) != 0 && (*(uint32_t *)(pArg4 + 8) - v18) >> 2 != 0 )  // 若 pArg4 != 0
        return *(uint32_t *)v18;
      else  // 否则分支
        return 0;
    }
    v9 = *(uint32_t *)(fld_e29 + 120);
    if ( v9 != 0 && i < (*(uint32_t *)(fld_e29 + 124) - v9) >> 2 )  // 若 v9 != 0
      pObj2 = *(uint32_t *)(v9 + 4 * i);
    else  // 否则分支
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      v12 = *(uint32_t *)(fld_e292 + 120);
      if ( v12 != 0 && i < (*(uint32_t *)(fld_e292 + 124) - v12) >> 2 )  // 若 v12 != 0
        pObj = *(uint32_t *)(v12 + 4 * i);
      else  // 否则分支
        pObj = 0;
      pObj3 = pObj;
      if ( (uint8_t)sub_4E4630(pObj) != 0 )  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        break;  // 跳出循环/分支
    }
LABEL_25:  // 标签 LABEL_25（跳转合流点）
    ;
  }
  for ( j = 200; j < 205; ++j )  // 循环：j 从 200 递增到 205
  {
    if ( j == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj) )  // 调虚槽 +376：坐标同步包（type 37）
      goto LABEL_24;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) != 0  // 调虚槽 +940
    || (v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj),  // 调虚槽 +120：动画对象
        (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v15) > nArg2)  // 调虚槽 +120：动画对象
    || (v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj),  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v16) > nArg3) )  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  {
LABEL_24:  // 标签 LABEL_24（跳转合流点）
    i = v20;
    goto LABEL_25;
  }
  if ( pArg4 != 0 )  // 若 pArg4 非 0
  {
    sub_4E7BA0(&pObj3);  // 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
    goto LABEL_24;
  }
  return pObj;
}



// ------------------------------------------------------------
// 0x4E8080 sub_4E8080
// ------------------------------------------------------------
// vmt1C8 命中目标列表追加（L1 精修版见 src/cnrd/IRDCollisionObject.cpp:249）：
// this+332 名单查重，未命中过则 ·sub_431230 追加 + pszArg3 非 0 时 vt+464 回调。
// ------------------------------------------------------------
char /*thiscall*/ sub_4E8080(uint32_t *this, int nArg2, char pszArg3)  // 实现：命中目标列表追加（去重 + vt+464 回调）
{
  uint32_t *fld_e84; // ecx
  uint32_t *fld_e83; // eax
  int nArg22; // edi

  fld_e84 = (uint32_t *)*(this + 84);
  fld_e83 = (uint32_t *)*(this + 83);  // this+332〔bReservedConn〕
  nArg22 = nArg2;
  if ( fld_e83 == fld_e84 )  // 若 fld_e83 == fld_e84
    goto LABEL_5;
  do  // do-while 循环体起点
  {
    if ( *fld_e83 == nArg2 )
      break;  // 跳出循环/分支
    ++fld_e83;
  }
  while ( fld_e83 != fld_e84 );  // 条件循环
  if ( fld_e83 == fld_e84 )  // 若 fld_e83 == fld_e84
  {
LABEL_5:  // 标签 LABEL_5（跳转合流点）
    sub_431230((int)(this + 82), &nArg2);  // uint32 vector push_back
    LOBYTE(fld_e83) = pszArg3;
    if ( pszArg3 != 0 )  // 若 pszArg3 非 0
      LOBYTE(fld_e83) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 464))(this, nArg22);  // 调虚槽 +464
  }
  return (char)fld_e83;
}



// ------------------------------------------------------------
// 0x4E80E0 sub_4E80E0 —— VLQ 批量序列化（遍历 4 字节 vector → ·0x4E7BF0）
// 供位移同步包使用（·0x4E8130 调，先序列化再取缓冲长度）
// ------------------------------------------------------------
int /*thiscall*/ sub_4E80E0(void *this, int pArg2)  // 实现：VLQ 批量序列化（遍历 4 字节 vector → ·0x4E7BF0）
{
  int result; // eax
  int v3; // edi
  int i; // esi

  result = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( result != 0 )  // 若结果非 0（成功）
    v3 = (*(uint32_t *)(pArg2 + 8) - result) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v3 = 0;
  for ( i = 0; i < v3; ++i )  // 遍历循环
    result = sub_4E7BF0((int)this, *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4 * i));  // 变长整数编码器（VLQ / 7 bit × n；网络序列化基元）
  return result;
}



// ------------------------------------------------------------
// 0x4E8130 sub_4E8130 —— ★ 位移同步包 vt+234（会话 3 定案：UDP type=5）
// 已精修版见 src/cnrd/IRDCollisionObject.cpp（vmt234 位移同步包段落）。
// 会话 3 定案原文："vmt234 位移同步包（0x4E8130）：**UDP type=5**，双 id +
//   位移序列化（sub_4E80E0）"。
// 转写体逐条对应：
//   门：`a1[613] == 0`（未上报）且 `a1+616(反应态) != −1`
//   → 打包站 `type 5, 2 子字段`；写 本体 id（vt+48/vt+52 即子 id 对）
//     + **本地玩家 dword_8F7C04 的 id 对**（对端） + `a1[616]` 反应态
//   → **sub_4E80E0(v18, a1+620)**（★ 位移序列化，会话 3 定案）→ sub_48D1E0 取缓冲长度
//   → 逐字节 vt+32 压入 → 提交 vt+60(1, −1) → `a1[613] = 1`（置已上报）
// ✅ 与 0x4E7A80 的 `this[613] = 0`（清已上报）成对 —— 反应态一变就补发位移。
// ------------------------------------------------------------
void /*usercall*/ sub_4E8130(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：位移同步包 vt+234（会话 3 定案：UDP type=5）
{
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  unsigned int v12; // ebx
  uint8_t *v13; // edi
  int v14; // eax
  int v15; // [esp+4h] [ebp-2Ch] BYREF
  void *Block; // [esp+8h] [ebp-28h]
  int v17; // [esp+Ch] [ebp-24h]
  uint8_t v18[4]; // [esp+14h] [ebp-1Ch] BYREF
  void *v19; // [esp+18h] [ebp-18h]
  int v20; // [esp+1Ch] [ebp-14h]
  int v21; // [esp+20h] [ebp-10h]
  int v22; // [esp+2Ch] [ebp-4h]

  if ( pArg1[613] == 0 && *((uint32_t *)pArg1 + 154) != -1 )  // 复合条件判定（与/或）
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 5, 2, nArg3, nArg2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    v4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 48))(pArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);  // 会话/UDP 管理器
    v6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v7 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 52))(pArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);  // 会话/UDP 管理器
    v8 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);  // 会话/UDP 管理器
    v10 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);  // 会话/UDP 管理器
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))((uint8_t)pArg1[616]);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    v12 = 0;
    v19 = nullptr;  // v19 = 空指针
    v20 = 0;
    v21 = 0;
    v22 = 0;
    sub_4E80E0(v18, (int)(pArg1 + 620));  // VLQ 批量序列化（遍历 4 字节 vector → ·0x4E7BF0）
    sub_48D1E0(&v15, (int)v18);  // 字节缓冲深拷贝构造（this+1/+2/+3 三指针）
    v13 = (uint8_t *)Block;
    LOBYTE(v22) = 1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      v14 = v17 - (uint32_t)Block;
    else  // 否则分支
      v14 = 0;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v14);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    while ( v13 != nullptr && v12 < v17 - (int)v13 )  // 条件循环
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))(v13[v12++]);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    pArg1[613] = 1;
    if ( v13 != nullptr )  // 若 v13 有效（非空）
      j__free(v13);
    if ( v19 != nullptr )  // 若 v19 有效（非空）
      j__free(v19);
  }
}



// ------------------------------------------------------------
// 0x4E82B0 sub_4E82B0 —— ★★★ 本地扫掠 / vt+476（研究 20 §1.2/§11 第 11 轮定案）
// 签名：__thiscall(this = 攻击者, a3 = 目标对象)（userpurge 寄存器形式）
// 研究 §1.2/§11 原文："**vt+476 槽** 在攻击动作活动帧做**客户端本地多命中盒碰撞**
//   （vt+480 = sub_4D6A80 主盒+附加盒链表），命中即播 KnockSmall.ani 并冻结攻方
//   ——**先于服务端包的即时反馈**；友敌选择门 +405/406/407 对应攻击定义的
//   `[attack myself/friend/enemy]` 开关。"
// 转写体与定案的逐条对应：
//   门① `vt+308(攻) == 0 && vt+308(受) == 0` → return 0（双方都不是本地玩家对象）
//   门② `hae = vt+360(攻, 受)`（敌我关系）—— 写入 HIBYTE(a3) 备用
//        `a1[128](= 字节 +512) == 2` 为"无视敌我"模式（攻击定义 [attack myself] 族？）
//        否则 hae == 0 → return 0
//   门③ **友敌选择门（研究 §11 直证）**：
//        `*((uint8_t*)a1 + 405) == 0` 且 双方车主相同 → return 0
//        `+406 == 0` 且 sub_4E4630(受) == 0 且 车主不同 → return 0
//        `+407 == 0` 且 sub_4E4630(受) != 0 → return 0
//        —— 即研究上述 "+405/406/407 对应 [attack myself/friend/enemy]"（**逐条吻合**）
//   ④ **盒碰撞**：`v33 = vt+480(a1, 受, v27)` —— ★ vt+480 = sub_4D6A80（多命中盒），
//        v27 为 6 float 输出槽（命中点）
//   ⑤ 命中后：
//        `+512 == 2` 但本地节流未通过（sub_4E7EA0，1000ms 重复命中节流，
//          研究 P29 "sub_4E7EA0 = 1000ms 重复命中节流"）→ 走冻结分支
//        查受方 vt+648(类型, &v32=100, vt+380) == 3（落空）→ 跳过
//        否则 **vt+356(a1, 受)**（记录命中目标）+ 若受方为本地玩家对象
//          → **sub_4E5F70(a1, 受, v27, 1, 1)**（★ 硬直率掷 + 上报服务端背书，§5.1 第 14 轮）
//        随后命中特效：按区域码 `dword_8F7A24+244` 三值分支
//          0..1 → **"Common/HitEffect/Animation/KnockSmall.ani"**（研究 §11 原文
//                 "命中即播 KnockSmall.ani" —— **直证**）
//          2    → "Common/HitEffect/Animation/Age12/KnockSmall.ani"（日区和谐分支，
//                 研究 §5.2 的 Age12 族同一区域码机制）
//          → sub_4922F0(0.5)（帧率缩放 0.5）+ 池化对象 sub_44B6C0(284)
//          + sub_45FE80 入演播层 2 + 定位（受方 x + v31*0.5+v28、v29*0.5+v27[0]）
//        + **冻结攻方**（回此前的 LABEL_37 分支）：`v23 = a1[130]`（**字节 +520 =
//          攻方自身卡肉时长**，研究 §8 定案字段）> 0 且
//          （主状态 a1[50]（字节 +200）== 0 或（==1 且 vt+248 剩余硬直 < v23））→
//          **vt+228(a1, 1, v23, 0)**（与 §8 攻方自我冻结**同一入口、同一延长逻辑**）
//          —— 研究 §11 "并冻结攻方" 在此**直证**，且读的正是 this+520 ✅
// ✅ 与 §11 第 11 轮定案**逐条吻合**（含"先于服务端包的即时反馈"的时序语义）。
// 研究 §15 复用价值 #7：本地扫掠是"出招即震"的理想读点（不等服务器往返）。
// ------------------------------------------------------------
char /*userpurge*/ sub_4E82B0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3)  // 实现：本地扫掠 / vt+476（研究 20 §1.2/§11 第 11 轮定案）
{
  char bSelfAlive; // al
  int pVictim; // edi
  char bHostile; // al
  bool bIgnoreSide; // zf
  int pVictimOwner; // ebx
  int pVictimOwner2; // ebx
  int pSelfVt; // edx
  int pSelfVt2; // edx
  int pVictimVt; // ebx
  int pSelfBody; // eax
  int nAreaCode; // eax
  int hKnockAni; // ebx
  int hKnockAni2; // eax
  int pFxObj; // ebx
  int pSceneObj; // ecx
  int pFxVt; // ebx
  uint64_t fHitX; // rax
  uint64_t fHitZ; // rax
  int nOwnStuckMs; // edi
  int nMainState; // eax
  int nHitY; // [esp-8h] [ebp-3Ch]
  float fHitBox[2]; // [esp+8h] [ebp-2Ch] BYREF
  float fBoxLeft; // [esp+10h] [ebp-24h]
  float fBoxTop; // [esp+14h] [ebp-20h]
  int nBoxReserved; // [esp+18h] [ebp-1Ch]
  float fBoxW; // [esp+1Ch] [ebp-18h]
  int nDmgKindOut; // [esp+20h] [ebp-14h] BYREF
  char bHit; // [esp+27h] [ebp-Dh]
  int nEhGuard; // [esp+30h] [ebp-4h]

  bSelfAlive = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  pVictim = nArg3;
  if ( bSelfAlive == 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 308))(nArg3) == 0 )  // 调虚槽 +308：是否本地玩家
    return 0;
  bHostile = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 360))(pArg1, pVictim);  // 调虚槽 +360：敌我关系判定（vmt168 槽覆写，研究已定案）
  bIgnoreSide = pArg1[128] == 2;
  HIBYTE(nArg3) = bHostile;
  if ( !bIgnoreSide && bHostile != 0 )  // 若 bHostile != 0
    return 0;
  if ( *((uint8_t *)pArg1 + 405) == 0 )
  {
    pVictimOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 576))(pVictim);  // 调虚槽 +576
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 576))(pArg1) == pVictimOwner )  // 调虚槽 +576
      return 0;
  }
  if ( *((uint8_t *)pArg1 + 406) == 0 && (uint8_t)sub_4E4630(pVictim) == 0 )  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
  {
    pVictimOwner2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 576))(pVictim);  // 调虚槽 +576
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 576))(pArg1) != pVictimOwner2 )  // 调虚槽 +576
      return 0;
  }
  if ( *((uint8_t *)pArg1 + 407) == 0 && (uint8_t)sub_4E4630(pVictim) != 0 )  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
    return 0;
  pSelfVt = *pArg1;
  fHitBox[0] = 0.0;
  fHitBox[1] = 0.0;
  fBoxLeft = 0.0;
  fBoxTop = 0.0;
  nBoxReserved = 0;
  fBoxW = 0.0;
  bHit = (*(int (/*thiscall*/ **)(uint32_t *, int, float *))(pSelfVt + 480))(pArg1, pVictim, fHitBox);  // 调虚槽 +480：地刺接触判定 vmt1E0
  if ( bHit != 0 )  // 若 bHit 非 0
  {
    if ( pArg1[128] != 2 || (sub_4E7EA0((char *)&nArg3 + 3, pVictim), HIBYTE(nArg3) == 0) )  // 1000ms 重复命中节流（研究 P29 第 24/25 轮定案）
    {
      pSelfVt2 = *pArg1;
      pVictimVt = *(uint32_t *)pVictim;
      nDmgKindOut = 100;
      pSelfBody = (*(int (/*thiscall*/ **)(uint32_t *))(pSelfVt2 + 380))(pArg1);  // 调虚槽 +380：点击命中框
      if ( (*(int (/*thiscall*/ **)(int, int *, int))(pVictimVt + 648))(pVictim, &nDmgKindOut, pSelfBody) != 3 )  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 356))(pArg1, pVictim);  // 调虚槽 +356：记录当前命中目标（研究已定案）
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 308))(pVictim) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          sub_4E5F70(pArg1, pVictim, fHitBox, 1, 1);  // 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
          return bHit;
        }
        if ( (uint8_t)sub_4AED00(pArg1 + 97) == 0 && pArg1[112] == 0 )  // 复合条件判定（与/或）
        {
LABEL_37:  // 标签 LABEL_37（跳转合流点）
          nOwnStuckMs = pArg1[130];  // nOwnStuckMs = 取 pArg1[130]
          if ( nOwnStuckMs > 0 )  // 若 nOwnStuckMs > 0
          {
            nMainState = pArg1[50];  // nMainState = 取 pArg1[50]
            if ( nMainState == 0 || nMainState == 1 && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 248))(pArg1) < nOwnStuckMs )  // 调虚槽 +248：区间长 = vt+244 - vt+240
              (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 228))(pArg1, 1, nOwnStuckMs, 0);  // 调虚槽 +228：主状态写入(0自由/1硬直/2冻结)
          }
          return bHit;
        }
        nAreaCode = *(uint32_t *)(dword_8F7A24 + 244);  // 登录/选区管理器
        hKnockAni = 0;
        if ( nAreaCode >= 0 )  // 若 nAreaCode >= 0
        {
          if ( nAreaCode <= 1 )  // 若 nAreaCode <= 1
          {
            nArg3 = sub_42FCB0(228);  // CRT 一次性初始化
            nEhGuard = 1;
            if ( nArg3 != 0 )  // 若 nArg3 非 0
            {
              hKnockAni2 = sub_431860((char)"Common/HitEffect/Animation/KnockSmall.ani", 1);  // 动画件构造（资源 id 版）
              goto LABEL_30;
            }
LABEL_29:  // 标签 LABEL_29（跳转合流点）
            hKnockAni2 = 0;
            goto LABEL_30;
          }
          if ( nAreaCode == 2 )  // 若 nAreaCode == 2
          {
            nArg3 = sub_42FCB0(228);  // CRT 一次性初始化
            nEhGuard = 0;
            if ( nArg3 != 0 )  // 若 nArg3 非 0
            {
              hKnockAni2 = sub_431860((char)"Common/HitEffect/Animation/Age12/KnockSmall.ani", 1);  // 动画件构造（资源 id 版）
LABEL_30:  // 标签 LABEL_30（跳转合流点）
              nEhGuard = -1;
              hKnockAni = hKnockAni2;
              goto LABEL_31;
            }
            goto LABEL_29;
          }
        }
LABEL_31:  // 标签 LABEL_31（跳转合流点）
        sub_4922F0(0.5);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
        nArg3 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        nEhGuard = 2;
        if ( nArg3 != 0 )  // 若 nArg3 非 0
          pFxObj = sub_44E1F0(hKnockAni, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
        else  // 否则分支
          pFxObj = 0;
        pSceneObj = pArg1[29];  // pSceneObj = 取 pArg1[29]
        nArg3 = pFxObj;
        nEhGuard = -1;
        sub_45FE80(pSceneObj, pVictim, 2, 0, pFxObj, pVictim, 0);  // 调 实体对象注册到演播层
        if ( (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 660))(pArg1, pVictim, nArg2) == 1 )  // 调虚槽 +660
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxObj + 148))(pFxObj, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
        pFxVt = *(uint32_t *)pFxObj;
        fHitX = (uint64_t)(fBoxW * 0.5 + fBoxLeft);
        nHitY = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pVictim + 124))(pVictim, HIDWORD(fHitX), fHitX);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        fHitZ = (uint64_t)(fBoxTop * 0.5 + fHitBox[0]);
        (*(void (/*fastcall*/ **)(int, uint32_t, uint32_t, int))(pFxVt + 112))(nArg3, HIDWORD(fHitZ), fHitZ, nHitY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        goto LABEL_37;
      }
    }
    return 0;
  }
  return bHit;
}


// ------------------------------------------------------------
// 0x4E85E0 sub_4E85E0 —— ★★ CRITHIT / 暴击特效 vt+520（研究 20 §5.3 全文定案）
// 触发：命中包 case 0x14 的**暴击位**（研究 §1.1："暴击位=1 → vt+520 = CRITHIT"）。
// 反编译体与 §5.3 逐条对应：
//   ① 命中点 = 盒中心：`v13 = a5[3]*0.5 + a5[0]`（x）、v14 = 受方 vt+124(盒中心 y)、
//      `v16 = a5[5]*0.5 + a5[2] + 30.0`（z 抬高 30）
//   ② **"Common/HitEffect/Animation/CriticalHit.ani"** 池化生成于命中点
//      （sub_431860 取资源 → sub_44B6C0(284) 池化对象 → sub_45FE80 入演播层 2）
//   ③ ★ **若受击者 == 玩家（dword_8F7C04）**：
//      `dword_8F8528 + 2468/2469/2470 = 1/0/0` 三个标志字节（研究 §14#5 的
//      "被暴击标志管理器 +2468 三字节在'玩家被暴击'时置位" —— **直证**）
//      + **sub_424530(1069547520=**1.5f**, 100, 150, 盒中心 x/y/z, 1)** =
//        ★ 镜头 1.5 倍缩放特写（研究 §5.3："调 sub_424530(1.5f, 100, 150, x, y, z, 1)
//        = 镜头 1.5 倍缩放特写（写相机 +1168=倍率、+1180..1188=焦点坐标；
//        系统关闭时复位 1.0）"）—— 常量 1069547520 实测 = 0x3FC00000 = 1.5f ✅
// 常量核验：1069547520 = 0x3FC00000 = **1.5f** ✅（IEEE754 单精度）；100/150 为
// 时长/缓动参数（研究 §9 提到 sub_424530(2.0f, 300, 1000, …) 用于连击二档冲击，
// 与本次 (1.5f, 100, 150, …) 同函数不同参数 —— 研究 §5.3/§9 已定案该函数为
// "镜头缩放 + 焦点"通用入口）。
// ------------------------------------------------------------
int /*userpurge*/ sub_4E85E0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4, float *pArg5)  // 实现：CRITHIT / 暴击特效 vt+520（研究 20 §5.3 全文定案）
{
  int result; // eax
  int pFxObj; // edi
  uint8_t *pScreenMgr; // eax
  int pFxObjBak; // [esp+4h] [ebp-1Ch]
  int nHitX; // [esp+8h] [ebp-18h]
  int nHitY; // [esp+Ch] [ebp-14h]
  int nHitZ; // [esp+28h] [ebp+8h]
  int hCritAni; // [esp+2Ch] [ebp+Ch]

  result = *(uint32_t *)(pArg1 + 116);  // this+116 = 技能/宿主对象指针（非空才有效果宿主）
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nHitX = (uint64_t)(pArg5[3] * 0.5 + *pArg5);  // 命中盒中心 x = 宽/2 + 左
    nHitY = (*(int (/*fastcall*/ **)(int, uint32_t, int, int))(*(uint32_t *)nArg4 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            nArg4,
            (uint64_t)(pArg5[3] * 0.5 + *pArg5) >> 32,
            nArg3,
            nArg2);
    nHitZ = (uint64_t)(pArg5[5] * 0.5 + pArg5[2] + 30.0);  // 盒中心 z + 30 抬高
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      hCritAni = sub_431860((char)"Common/HitEffect/Animation/CriticalHit.ani", 1);  // ★ 暴击特效动画
    else  // 否则分支
      hCritAni = 0;
    pFxObj = sub_44B6C0(284);  // 特效池对象（284 字节）
    pFxObjBak = pFxObj;
    if ( pFxObj != 0 )  // 若 pFxObj 非 0
    {
      sub_44E0D0(hCritAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pFxObj = 0;
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pFxObj + 72))(pFxObj, 2);  // vt+72 置层/模式 2
    sub_45FE80(*(uint32_t *)(pArg1 + 116), pFxObj, 2, 0, pFxObj, nArg4, 0);  // 入演播层
    result = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pFxObj + 112))(pFxObj, nHitX, nHitY, nHitZ, pFxObjBak);  // vt+112 定位
    if ( dword_8F7C04 == pArg1 )  // 本地玩家对象才做屏效
    {
      pScreenMgr = dword_8F8528;  // 主管理器(消息/弹窗)
      *((uint8_t *)dword_8F8528 + 2468) = 1;  // 屏幕管理三标志：开 / 清
      pScreenMgr[2469] = 0;
      pScreenMgr[2470] = 0;
      return sub_424530(  // 变焦命令（暴击特写 1.5×/受击微特写 1.2×/连击冲拳 2.0× 的统一入口）。
               1069547520,  // 0x3FC00000 = 1.5f
               100,
               150,
               (uint64_t)(pArg5[3] * 0.5 + *pArg5),
               (uint64_t)(pArg5[4] * 0.5 + pArg5[1]),
               (uint64_t)(pArg5[5] * 0.5 + pArg5[2]),
               1);  // ★ 镜头 1.5 倍缩放特写（研究 §5.3）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E8770 sub_4E8770 —— ★★ UNIONHIT / 合击特效 vt+524（研究 20 §5.4 全文定案）
// 触发：命中包 case 0x14 的**合击位**（研究 §1.1："合击位 → vt+524 = UNIONHIT"）。
// 反编译体与 §5.4 逐条对应：
//   ① `v8 = a5[3]*0.5 + a5[0]` = 盒中心 x；受方 vt+124 取 y
//   ② **"Common/HitEffect/Animation/UnionHit.ani"** 池化生成 + 入演播层 2
//   ③ 尾调 **vt+212(a1, "GROUP_EFFECT", −1, 0, 0)** —— ★ 广播 `"GROUP_EFFECT"`
//      （研究 §5.4："UnionHit.ani + 广播 \"GROUP_EFFECT\"（连击系统视觉）"）—— **直证**
// ------------------------------------------------------------
int /*userpurge*/ sub_4E8770@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>, int nArg4, float *pArg5)  // 实现：UNIONHIT / 合击特效 vt+524（研究 20 §5.4 全文定案）
{
  int result; // eax
  int pFxObj; // esi
  int nHitX; // [esp+8h] [ebp-14h]
  int hUnionAni; // [esp+28h] [ebp+Ch]

  result = pDwArg1[29];  // result = 取 pDwArg1[29]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nHitX = (uint64_t)(pArg5[3] * 0.5 + *pArg5);  // 盒中心 x
    (*(void (/*fastcall*/ **)(int, uint32_t, int, int))(*(uint32_t *)nArg4 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nArg4,
      (uint64_t)(pArg5[3] * 0.5 + *pArg5) >> 32,
      nArg2,
      nArg3);
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      hUnionAni = sub_431860((char)"Common/HitEffect/Animation/UnionHit.ani", 1);  // ★ 合击特效动画
    else  // 否则分支
      hUnionAni = 0;
    pFxObj = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    if ( pFxObj != 0 )  // 若 pFxObj 非 0
    {
      sub_44E0D0(hUnionAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pFxObj = 0;
    }
    sub_45FE80(pDwArg1[29], nArg4, 2, 0, pFxObj, nArg4, 0);  // 入演播层
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pFxObj + 112))(pFxObj, nHitX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "GROUP_EFFECT", -1, 0, 0);  // ★ 广播 GROUP_EFFECT（研究 §5.4 直证）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E88A0 sub_4E88A0 —— ★★★ HITEFF / 通用命中特效生成器 vt+640（研究 20 §5.2 全文定案）
// 签名：__userpurge(a1 = 受击者, a2/a3 寄存器, a4 = 攻击者, a5 = 命中盒 6 float)
// 调用点 = 表现壳 0x4E5DC0 的 `vt+640(this, a2, a3)`（研究 §3 伪码末段）。
// 反编译体与 §5.2 逐条对应：
//   ⓪ 命中点 = 交集盒中心：`v84 = a5[3]*0.5 + a5[0]`（x）、受方 vt+124 取 y、
//      `v82 = a5[5]*0.5 + a5[2]`（z）；v85 = 方向/镜像标志（攻方 vt+660 朝向比对）
//   ① **攻击特效四类型 switch（attackinfo+20 = v79+20）** —— 研究 §5.2 原文
//      "按 attackinfo+20 选特效系"：
//        case 0/1 → **两组预置模板**：dword_8F8278/8F827C（case 0）与
//                     dword_8F8280/8F8284（case 1）—— 池化单例三角组（研究 §5.2
//                     "0/1 = 两组预置模板"；§29b "刀/钝器 = 池化双火花"）✅
//        case 2    → **"Common/HitEffect/Animation/DarkHit2.ani" + DarkHit1.ani**
//                     三层叠放（研究 §5.2 "2=DarkHit1/2.ani" ✅）
//        case 3    → **"Common/HitEffect/Animation/LightHit.ani"**（§5.2 "3=LightHit.ani" ✅）
//      随后的 `if (attackinfo+12 == 1)`（★ 魔法大类 [magic]）→
//        **"Common/HitEffect/Animation/MagicHit3.ani"**（§5.2 "魔法=MagicHit3.ani" ✅）
//   ② **命中火花路径组**（研究 §5.2 原文三段，v43 = attackinfo+124 [hit info]）：
//        == 0（**钝击 Knock**）：前缀 "Knock"，区域码 dword_8F7A24+244
//           0..1 → "Knock"；== 2 → "Age12/Knock"；再按 **v15 = rand()%2** 追加
//           "Large.ani" 或 "Small.ani"（★ §5.2 "随机 Large.ani/Small.ani" ✅）
//        == 1（**斩击 Slash**）：前缀 "Slash"，区域码同上（"Slash"/"Age12/Slash"）；
//           按 **attackinfo+120 武器种类 v76** 选：Large3/2/1.ani 或 Small3/2/1.ani
//           （★ §5.2 "按 attackinfo+120 武器种类 Large1/2/3 或 Small1/2/3" ✅）
//        == 3：攻方 **vt+652** 给自定义路径（★ §5.2 "攻击者 vt+652 给自定义路径" ✅）
//      （区域码 == 1 的分支在转写体不追加前缀 —— 即"日区/Young 变体"由拼接层决定，见 ④）
//   ③ ★★ **暴击 → 火花 1.5 倍**：`if (sub_4E5B50(a1, a4) != 0) sub_4920E0(1.5, 1.5)`
//      —— §5.2 原文"火花创建后：**暴击 → sub_4920E0(1.5, 1.5) = 批量改写特效帧的
//      IMAGE RATE（帧 +20/+24，88 字节帧距）—— 火花动画整体放大 1.5 倍**" **直证** ✅
//   ④ ★ **血溅**：`attackinfo+128 != 0`（[blood] 标志）且 受方条件 17（有血）→
//      "SplashBloodLarge"（v15）/ "SplashBloodSmall1-3"（按 v76 武器类）+
//      **区域码 != 1 时追加 "Young"**（★ §5.2 "+Young 和谐"）；
//      再拼 "Monster/Common/Animation/MonsterDieBlood"（★ §5.2 "+ MonsterDieBlood"）
//      其朝向偏移 = `v85 ? +10 : −10`（★ §5.2 "（朝向偏移 ±10 取决于攻击方向）" ✅）
//   ⑤ ★ **伤害倍率特效**：循环 i∈{0,1}，`attackinfo+84/88 > 100` 时（[human damage rate]/
//      [fort damage rate]）且持有标签 16/17 → **"OptionalDamageRateHuman.ani"/
//      "OptionalDamageRateFort.ani"**，缩放 = sub_4049C0(0.69999999, 1.5, 值−100, 100)
//      （★ §5.2 "attackinfo+84/+88 > 100 → OptionalDamageRateHuman/Fort.ani（克制标记）" ✅，
//      且 L1 补出缩放公式：0.7..1.5 线性插值）
// 研究 §5.2 第 9 轮更正注记："此函数作用于特效帧数组，非场景节点树" —— 与 sub_4920E0 一致。
// ✅ 与 §5.2 定案**逐条吻合**（含全部资源名/随机/区域码/暴击 1.5×/血溅/克制标记）。
// ------------------------------------------------------------
void /*userpurge*/ sub_4E88A0(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4, float *pArg5)  // 【HITEFF 通用命中特效生成器 vt+640（研究 §5.2 全文定案）】
{
  unsigned int nDmgState; // esi
  int pAnim; // esi
  int pAtkInfo0; // ecx
  char bHasDmg; // al
  bool bMirrorTmp; // zf
  double v11; // st7
  uint64_t v12; // rax
  int v13; // eax
  double v14; // st7
  bool bRandOdd; // bl
  int nAtkKind; // eax
  int pTplKnock0A; // esi
  int pTplKnock0B; // esi
  int v19; // eax
  int v20; // eax
  int pTplKnock1A; // esi
  int pTplKnock1B; // esi
  int v23; // eax
  int v24; // eax
  uint32_t *v25; // ecx
  int v26; // eax
  int pFxDark2; // esi
  uint32_t *v28; // ecx
  int v29; // eax
  int pFxDark1; // esi
  int pTplDarkC; // esi
  uint32_t *v32; // ecx
  int v33; // eax
  int pObj; // esi
  int pTplLightB; // esi
  uint32_t *v36; // ecx
  int v37; // eax
  int pFxMagic3; // esi
  int pTplMagicA; // esi
  int pTplMagicB; // esi
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  void *v48; // eax
  void **v49; // ecx
  int v50; // esi
  int pFxHitSpark; // esi
  int pTplHitSpark; // esi
  int v53; // eax
  void **v54; // ecx
  int v55; // eax
  int pFxBlood; // esi
  void **v57; // ecx
  int v58; // eax
  int *v59; // esi
  int v60; // eax
  int v61; // eax
  int i; // ebx
  int v63; // eax
  void **v64; // ecx
  int v65; // eax
  int pFxOptDmg; // esi
  double v67; // st7
  float v68; // [esp-Ch] [ebp-B8h]
  int v69; // [esp-8h] [ebp-B4h]
  int v71; // [esp-4h] [ebp-B0h]
  char v72[4]; // [esp+4h] [ebp-A8h] BYREF
  void *Block; // [esp+8h] [ebp-A4h]
  int sTmpLen; // [esp+Ch] [ebp-A0h]
  int sTmpCap; // [esp+10h] [ebp-9Ch]
  int nWeaponKind; // [esp+14h] [ebp-98h]
  uint8_t v77[16]; // [esp+18h] [ebp-94h] BYREF
  int pPoolTmp; // [esp+28h] [ebp-84h]
  int pAtkInfo; // [esp+2Ch] [ebp-80h]
  int pPoolTmp2; // [esp+30h] [ebp-7Ch]
  char bHasCustomPath; // [esp+37h] [ebp-75h] BYREF
  float fHitZ; // [esp+38h] [ebp-74h]
  int nHitY; // [esp+3Ch] [ebp-70h]
  int nHitX; // [esp+40h] [ebp-6Ch]
  char bMirror; // [esp+47h] [ebp-65h]
  char v86[4]; // [esp+48h] [ebp-64h] BYREF
  uint32_t v87[6]; // [esp+4Ch] [ebp-60h] BYREF
  char v88[4]; // [esp+64h] [ebp-48h] BYREF
  uint8_t v89[8]; // [esp+68h] [ebp-44h] BYREF
  uint8_t v90[8]; // [esp+70h] [ebp-3Ch] BYREF
  int sKnockLen; // [esp+78h] [ebp-34h]
  unsigned int sKnockCap; // [esp+7Ch] [ebp-30h]
  char v93[4]; // [esp+80h] [ebp-2Ch] BYREF
  void *v94[4]; // [esp+84h] [ebp-28h] BYREF
  int sFinalLen; // [esp+94h] [ebp-18h]
  unsigned int sFinalCap; // [esp+98h] [ebp-14h]
  int dword_796E502; // [esp+9Ch] [ebp-10h]
  int nEhState; // [esp+A8h] [ebp-4h]
  float fScaleTmp; // [esp+B4h] [ebp+8h]

  dword_796E502 = dword_796E50;
  if ( *(uint32_t *)(pArg1 + 116) == 0 )  // pArg1+116〔会话上下文〕
    return;
  if ( *(uint8_t *)(pArg1 + 642) != 0 )  // pArg1+642〔bFrameOverride(推断)〕
  {
    nDmgState = *(uint32_t *)(pArg1 + 644);  // pArg1+644〔nFrameOverrideTime(推断)〕
  }
  else  // 否则分支
  {
    pAnim = *(uint32_t *)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
    if ( pAnim == 0 )  // 若 pAnim 为 0
      goto LABEL_9;
    if ( *(uint32_t *)(pAnim + 148) == -1 )
      sub_4938F0(*(uint32_t *)(pArg1 + 120));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    nDmgState = *(uint32_t *)(pAnim + 112);
  }
  if ( nDmgState > 1 )  // 若 nDmgState > 1
    return;
LABEL_9:  // 标签 LABEL_9（跳转合流点）
  pAtkInfo0 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 348))(nArg4);  // 调虚槽 +348：取坐标对象
  bHasDmg = *(uint8_t *)(pAtkInfo0 + 16);
  pAtkInfo = pAtkInfo0;
  if ( bHasDmg == 0 && *(float *)pAtkInfo0 <= 0.0 )  // 若 bHasDmg == 0
    return;
  bMirrorTmp = *(uint32_t *)(pAtkInfo0 + 124) == 1;
  bMirror = 0;
  if ( bMirrorTmp )
    bMirrorTmp = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg4 + 152))(nArg4, nArg3) == 0;  // 调虚槽 +152：效果通道 3
  else  // 否则分支
    bMirrorTmp = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)nArg4 + 660))(nArg4, pArg1, nArg3) == 1;  // 调虚槽 +660
  if ( bMirrorTmp )
    bMirror = 1;
  v11 = pArg5[3] * 0.5;
  nWeaponKind = *(uint32_t *)(pAtkInfo + 120);
  v12 = (uint64_t)(v11 + *pArg5);
  nHitX = v12;
  v13 = (*(int (/*fastcall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 124))(pArg1, HIDWORD(v12), nArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v14 = pArg5[5] * 0.5;
  nHitY = v13;
  LODWORD(fHitZ) = (uint64_t)(v14 + pArg5[2]);
  bRandOdd = rand() % 2 == 0;  // bRandOdd = 调 rand
  sFinalCap = 15;
  sFinalLen = 0;
  LOBYTE(v94[0]) = 0;
  nAtkKind = *(uint32_t *)(pAtkInfo + 20);
  nEhState = 0;
  switch ( nAtkKind )  // 按 nAtkKind 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      pTplKnock0A = dword_8F8278;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8278 + 12))(dword_8F8278, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplKnock0A + 40))(pTplKnock0A, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplKnock0A + 28))(pTplKnock0A) + 84) = bMirror;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplKnock0A + 92))(pTplKnock0A, v77);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 1;
      sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
      pTplKnock0B = dword_8F827C;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F827C + 12))(dword_8F827C, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplKnock0B + 40))(pTplKnock0B, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplKnock0B + 28))(pTplKnock0B);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint8_t *)(v19 + 84) = bMirror;
      v20 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplKnock0B + 92))(pTplKnock0B, v90);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 2;
      sub_4E77D0(v20);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
      LOBYTE(nEhState) = 1;
LABEL_18:  // 标签 LABEL_18（跳转合流点）
      sub_5E5260(v90);  // 调 动画子对象清理临时缓冲
      sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
      LOBYTE(nEhState) = 0;
      sub_5E5260(v77);  // 调 动画子对象清理临时缓冲
      goto LABEL_68;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      pTplKnock1A = dword_8F8280;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8280 + 12))(dword_8F8280, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplKnock1A + 40))(pTplKnock1A, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplKnock1A + 28))(pTplKnock1A) + 84) = bMirror;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplKnock1A + 92))(pTplKnock1A, v77);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 3;
      sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
      pTplKnock1B = dword_8F8284;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8284 + 12))(dword_8F8284, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplKnock1B + 40))(pTplKnock1B, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplKnock1B + 28))(pTplKnock1B);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint8_t *)(v23 + 84) = bMirror;
      v24 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplKnock1B + 92))(pTplKnock1B, v90);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 4;
      sub_4E77D0(v24);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
      LOBYTE(nEhState) = 3;
      goto LABEL_18;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      sub_401710("Common/HitEffect/Animation/DarkHit2.ani");  // std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
      pPoolTmp = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      LOBYTE(nEhState) = 6;
      if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
      {
        pPoolTmp2 = sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(nEhState) = 7;
        if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
        {
          LOBYTE(v25) = v89[0];
          if ( sKnockCap < 0x10 )  // 若 sKnockCap < 0x10
            v25 = v89;
          v26 = sub_431860((char)v25, 1);  // 动画件构造（资源 id 版）
        }
        else  // 否则分支
        {
          v26 = 0;
        }
        LOBYTE(nEhState) = 6;
        pFxDark2 = sub_44E1F0(v26, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        pFxDark2 = 0;
      }
      LOBYTE(nEhState) = 5;
      sub_45FE80(2, 0, pFxDark2, pArg1, 0);  // 调 实体对象注册到演播层
      if ( bMirror != 0 )  // 若 bMirror 非 0
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxDark2 + 148))(pFxDark2, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pFxDark2 + 112))(pFxDark2, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      sub_406D60("Common/HitEffect/Animation/DarkHit1.ani");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      LOBYTE(nEhState) = 8;
      if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
      {
        pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(nEhState) = 9;
        if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
        {
          LOBYTE(v28) = v89[0];
          if ( sKnockCap < 0x10 )  // 若 sKnockCap < 0x10
            v28 = v89;
          v29 = sub_431860((char)v28, 1);  // 动画件构造（资源 id 版）
        }
        else  // 否则分支
        {
          v29 = 0;
        }
        LOBYTE(nEhState) = 8;
        pFxDark1 = sub_44E1F0(v29, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        pFxDark1 = 0;
      }
      LOBYTE(nEhState) = 5;
      sub_45FE80(2, 0, pFxDark1, pArg1, 0);  // 调 实体对象注册到演播层
      if ( bMirror != 0 )  // 若 bMirror 非 0
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxDark1 + 148))(pFxDark1, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pFxDark1 + 112))(pFxDark1, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pTplDarkC = dword_8F8288;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8288 + 12))(dword_8F8288, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplDarkC + 40))(pTplDarkC, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplDarkC + 28))(pTplDarkC) + 84) = bMirror;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplDarkC + 92))(pTplDarkC, v77);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 10;
LABEL_43:  // 标签 LABEL_43（跳转合流点）
      sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
      sub_5E5260(v77);  // 调 动画子对象清理临时缓冲
      LOBYTE(nEhState) = 0;
      sub_501490(v88);  // 调 对象析构后释放堆块
      goto LABEL_68;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      sub_401710("Common/HitEffect/Animation/LightHit.ani");  // std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
      pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      LOBYTE(nEhState) = 12;
      if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
      {
        pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(nEhState) = 13;
        if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
        {
          LOBYTE(v32) = v89[0];
          if ( sKnockCap < 0x10 )  // 若 sKnockCap < 0x10
            v32 = v89;
          v33 = sub_431860((char)v32, 1);  // 动画件构造（资源 id 版）
        }
        else  // 否则分支
        {
          v33 = 0;
        }
        LOBYTE(nEhState) = 12;
        pObj = sub_44E1F0(v33, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        pObj = 0;
      }
      LOBYTE(nEhState) = 11;
      sub_45FE80(2, 0, pObj, pArg1, 0);  // 调 实体对象注册到演播层
      if ( bMirror != 0 )  // 若 bMirror 非 0
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 148))(pObj, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pObj + 112))(pObj, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pTplLightB = dword_8F828C;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F828C + 12))(dword_8F828C, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplLightB + 40))(pTplLightB, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplLightB + 28))(pTplLightB) + 84) = bMirror;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplLightB + 92))(pTplLightB, v77);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      LOBYTE(nEhState) = 14;
      goto LABEL_43;
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  if ( *(uint32_t *)(pAtkInfo + 12) == 1 )
  {
    sub_401710("Common/HitEffect/Animation/MagicHit3.ani");  // std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
    pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    LOBYTE(nEhState) = 16;
    if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
    {
      pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
      LOBYTE(nEhState) = 17;
      if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
      {
        LOBYTE(v36) = v87[0];
        if ( v87[5] < 0x10u )
          v36 = v87;
        v37 = sub_431860((char)v36, 1);  // 动画件构造（资源 id 版）
      }
      else  // 否则分支
      {
        v37 = 0;
      }
      LOBYTE(nEhState) = 16;
      pFxMagic3 = sub_44E1F0(v37, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
    }
    else  // 否则分支
    {
      pFxMagic3 = 0;
    }
    LOBYTE(nEhState) = 15;
    sub_45FE80(2, 0, pFxMagic3, pArg1, 0);  // 调 实体对象注册到演播层
    if ( bMirror != 0 )  // 若 bMirror 非 0
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxMagic3 + 148))(pFxMagic3, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pFxMagic3 + 112))(pFxMagic3, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    pTplMagicA = dword_8F8290;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8290 + 12))(dword_8F8290, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplMagicA + 40))(pTplMagicA, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplMagicA + 28))(pTplMagicA) + 84) = bMirror;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplMagicA + 92))(pTplMagicA, v77);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
    LOBYTE(nEhState) = 18;
    sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
    pTplMagicB = dword_8F8294;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8294 + 12))(dword_8F8294, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplMagicB + 40))(pTplMagicB, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplMagicB + 28))(pTplMagicB);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
    *(uint8_t *)(v41 + 84) = bMirror;
    v42 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pTplMagicB + 92))(pTplMagicB, v90);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
    LOBYTE(nEhState) = 19;
    sub_4E77D0(v42);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
    LOBYTE(nEhState) = 18;
    sub_5E5260(v90);  // 调 动画子对象清理临时缓冲
    sub_4600B0(2, 0, v77);  // 调 演播层注册(槽号)
    sub_5E5260(v77);  // 调 动画子对象清理临时缓冲
    LOBYTE(nEhState) = 0;
    sub_501490(v86);  // 调 对象析构后释放堆块
  }
LABEL_68:  // 标签 LABEL_68（跳转合流点）
  sub_4015C0("Common/HitEffect/Animation/", 0x1Bu);  // 【std::string构造赋值】
  bHasCustomPath = 0;
  v43 = *(uint32_t *)(pAtkInfo + 124);
  if ( v43 == 0 )  // 若 v43 为 0
  {
    sKnockCap = 15;
    sKnockLen = 0;
    v89[0] = 0;
    v44 = *(uint32_t *)(dword_8F7A24 + 244);  // 登录/选区管理器
    LOBYTE(nEhState) = 20;
    if ( v44 >= 0 )  // 若 v44 >= 0
    {
      if ( v44 <= 1 )  // 若 v44 <= 1
      {
        sub_406D60("Knock");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      }
      else if ( v44 == 2 )
      {
        sub_406D60("Age12/Knock");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
      }
    }
    if ( bRandOdd )
    {
      v45 = sub_4E70B0(v86, v88, "Large.ani");  // std::string 拼接构造（拷贝 + 插入）
      LOBYTE(nEhState) = 21;
    }
    else  // 否则分支
    {
      v45 = sub_4E70B0(v86, v88, "Small.ani");  // std::string 拼接构造（拷贝 + 插入）
      LOBYTE(nEhState) = 22;
    }
    sub_4021F0((std::_String_base *)v93, v45, 0, -1);  // std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
    sub_501490(v86);  // 调 对象析构后释放堆块
    LOBYTE(nEhState) = 0;
    sub_501490(v88);  // 调 对象析构后释放堆块
    goto LABEL_103;
  }
  if ( v43 != 1 )  // 若 v43 != 1
  {
    if ( v43 == 3 && (v48 = (void *)(*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)nArg4 + 652))(nArg4, &bHasCustomPath)) != nullptr )  // 调虚槽 +652：蓄力态查询
      sub_406D60(v48);  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    else  // 否则分支
      sub_406D60((void *)szPassword);  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    goto LABEL_103;
  }
  sKnockCap = 15;
  sKnockLen = 0;
  v89[0] = 0;
  v46 = *(uint32_t *)(dword_8F7A24 + 244);  // 登录/选区管理器
  LOBYTE(nEhState) = 23;
  if ( v46 >= 0 )  // 若 v46 >= 0
  {
    if ( v46 <= 1 )  // 若 v46 <= 1
    {
      sub_406D60("Slash");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    }
    else if ( v46 == 2 )
    {
      sub_406D60("Age12/Slash");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    }
  }
  if ( bRandOdd )
  {
    switch ( nWeaponKind )  // 按 nWeaponKind 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        v47 = sub_4E70B0(v86, v88, "Large3.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 24;
LABEL_97:  // 标签 LABEL_97（跳转合流点）
        sub_4021F0((std::_String_base *)v93, v47, 0, -1);  // std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
        sub_501490(v86);  // 调 对象析构后释放堆块
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        v47 = sub_4E70B0(v86, v88, "Large2.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 25;
        goto LABEL_97;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v47 = sub_4E70B0(v86, v88, "Large1.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 26;
        goto LABEL_97;
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
  else  // 否则分支
  {
    switch ( nWeaponKind )  // 按 nWeaponKind 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        v47 = sub_4E70B0(v86, v88, "Small3.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 27;
        goto LABEL_97;
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        v47 = sub_4E70B0(v86, v88, "Small2.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 28;
        goto LABEL_97;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v47 = sub_4E70B0(v86, v88, "Small1.ani");  // std::string 拼接构造（拷贝 + 插入）
        LOBYTE(nEhState) = 29;
        goto LABEL_97;
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
  LOBYTE(nEhState) = 0;
  sub_501490(v88);  // 调 对象析构后释放堆块
LABEL_103:  // 标签 LABEL_103（跳转合流点）
  if ( sub_40BF00(0, sFinalLen, szPassword, 0) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    pPoolTmp2 = sub_42FCB0(228);  // CRT 一次性初始化
    LOBYTE(nEhState) = 30;
    if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
    {
      LOBYTE(v49) = v94[0];
      if ( sFinalCap < 0x10 )  // 若 sFinalCap < 0x10
        v49 = v94;
      v50 = sub_431860((char)v49, 1);  // 动画件构造（资源 id 版）
    }
    else  // 否则分支
    {
      v50 = 0;
    }
    LOBYTE(nEhState) = 0;
    if ( (uint8_t)sub_4E5B50(pArg1, nArg4) != 0 )  // 暴击/有效命中判定（研究 20 §5.1 全文定案）
      sub_4920E0(1.5, 1.5);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
    pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    LOBYTE(nEhState) = 31;
    if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
      pFxHitSpark = sub_44E1F0(v50, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
    else  // 否则分支
      pFxHitSpark = 0;
    LOBYTE(nEhState) = 0;
    sub_45FE80(2, 0, pFxHitSpark, pArg1, 0);  // 调 实体对象注册到演播层
    if ( bMirror != 0 )  // 若 bMirror 非 0
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxHitSpark + 148))(pFxHitSpark, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pFxHitSpark + 112))(pFxHitSpark, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    if ( bHasCustomPath != 0 )  // 若 bHasCustomPath 非 0
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pFxHitSpark + 60))(pFxHitSpark);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      sub_4A06D0(pArg1);  // 调 绑定目标对象并记录相对偏移
    }
  }
  pTplHitSpark = dword_8F8270[!bRandOdd];  // pTplHitSpark = 取 dword_8F8270[!bRandOdd]
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pTplHitSpark + 12))(pTplHitSpark, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
  (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pTplHitSpark + 40))(pTplHitSpark, nHitX, nHitY, COERCE_FLOAT(LODWORD(fHitZ)));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  v53 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTplHitSpark + 28))(pTplHitSpark);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  *(uint8_t *)(v53 + 84) = bMirror;
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pTplHitSpark + 92))(pTplHitSpark, v72);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
  LOBYTE(nEhState) = 32;
  sub_4600B0(2, 0, v72);  // 调 演播层注册(槽号)
  if ( *(uint8_t *)(pAtkInfo + 128) != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 40))(pArg1, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    if ( *(uint32_t *)(dword_8F7A24 + 244) == 2  // 登录/选区管理器
      || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 40))(pArg1, 529) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      && (*(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1032))(pArg1) + 64) & 2) != 0 )  // 调虚槽 +1032
    {
      sub_5E5260(v72);  // 调 动画子对象清理临时缓冲
      sub_501490(v93);  // 调 对象析构后释放堆块
      return;
    }
    sub_406D60("Common/HitEffect/Animation/");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    if ( bRandOdd )
    {
      sub_402410("SplashBloodLarge");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    }
    else if ( nWeaponKind != 0 )
    {
      if ( nWeaponKind == 1 )  // 若 nWeaponKind == 1
      {
        sub_402410("SplashBloodSmall2");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      }
      else if ( nWeaponKind == 2 )
      {
        sub_402410("SplashBloodSmall3");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      }
    }
    else  // 否则分支
    {
      sub_402410("SplashBloodSmall1");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    }
    if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )  // 登录/选区管理器
      sub_402410("Young");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    sub_402410(".ani");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    LOBYTE(nEhState) = 33;
    if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
    {
      pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
      LOBYTE(nEhState) = 34;
      if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
      {
        LOBYTE(v54) = v94[0];
        if ( sFinalCap < 0x10 )  // 若 sFinalCap < 0x10
          v54 = v94;
        v55 = sub_431860((char)v54, 1);  // 动画件构造（资源 id 版）
        LOBYTE(nEhState) = 33;
        pFxBlood = sub_44E1F0(v55, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        LOBYTE(nEhState) = 33;
        pFxBlood = sub_44E1F0(0, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
    }
    else  // 否则分支
    {
      pFxBlood = 0;
    }
    LOBYTE(nEhState) = 32;
    sub_45FE80(2, 0, pFxBlood, pArg1, 0);  // 调 实体对象注册到演播层
    if ( bMirror != 0 )  // 若 bMirror 非 0
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxBlood + 148))(pFxBlood, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, float, int, int))(*(uint32_t *)pFxBlood + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pFxBlood,
      nHitX,
      nHitY,
      COERCE_FLOAT(LODWORD(fHitZ)),
      v69,
      v71);
    sub_406D60("Monster/Common/Animation/MonsterDieBlood");  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
    if ( *(uint32_t *)(dword_8F7A24 + 244) != 1 )  // 登录/选区管理器
      sub_402410("Young");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    sub_402410(".ani");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
    pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    LOBYTE(nEhState) = 35;
    if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
    {
      pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
      LOBYTE(nEhState) = 36;
      if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
      {
        LOBYTE(v57) = v94[0];
        if ( sFinalCap < 0x10 )  // 若 sFinalCap < 0x10
          v57 = v94;
        v58 = sub_431860((char)v57, 1);  // 动画件构造（资源 id 版）
        LOBYTE(nEhState) = 35;
        v59 = (int *)sub_44E1F0(v58, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        LOBYTE(nEhState) = 35;
        v59 = (int *)sub_44E1F0(0, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
    }
    else  // 否则分支
    {
      v59 = nullptr;  // v59 = 空指针
    }
    v60 = *v59;
    LOBYTE(nEhState) = 32;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v60 + 36))(v59) + 8) = 2;  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
    sub_45FE80(2, 0, v59, 0, 0);  // 调 实体对象注册到演播层
    if ( bMirror != 0 )  // 若 bMirror 非 0
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*v59 + 148))(v59, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      v61 = nHitX + 10;
    }
    else  // 否则分支
    {
      v61 = nHitX - 10;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*v59 + 112))(v59, v61);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  }
  for ( i = 0; i < 2; ++i )  // 循环：i 从 0 递增到 2
  {
    if ( *(float *)(pAtkInfo + 4 * i + 84) <= 100.0 )
      continue;  // 进入下一轮循环
    if ( i != 0 )  // 若 i 非 0
    {
      if ( i != 1 )  // 若 i != 1
        continue;  // 进入下一轮循环
      v63 = 17;
    }
    else  // 否则分支
    {
      v63 = 16;
    }
    if ( (uint8_t)sub_4DAB60(v63) != 0 )  // 标签/条件集合成员判定
    {
      sub_4015C0("Common/HitEffect/Animation/", 0x1Bu);  // 【std::string构造赋值】
      if ( i != 0 )  // 若 i 非 0
        sub_402410("OptionalDamageRateFort.ani");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      else  // 否则分支
        sub_402410("OptionalDamageRateHuman.ani");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
      pPoolTmp2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      LOBYTE(nEhState) = 37;
      if ( pPoolTmp2 != 0 )  // 若 pPoolTmp2 非 0
      {
        pPoolTmp = sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(nEhState) = 38;
        if ( pPoolTmp != 0 )  // 若 pPoolTmp 非 0
        {
          LOBYTE(v64) = v94[0];
          if ( sFinalCap < 0x10 )  // 若 sFinalCap < 0x10
            v64 = v94;
          v65 = sub_431860((char)v64, 1);  // 动画件构造（资源 id 版）
        }
        else  // 否则分支
        {
          v65 = 0;
        }
        LOBYTE(nEhState) = 37;
        pFxOptDmg = sub_44E1F0(v65, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      }
      else  // 否则分支
      {
        pFxOptDmg = 0;
      }
      LOBYTE(nEhState) = 32;
      sub_45FE80(2, 0, pFxOptDmg, pArg1, 0);  // 调 实体对象注册到演播层
      if ( bMirror != 0 )  // 若 bMirror 非 0
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxOptDmg + 148))(pFxOptDmg, 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      v68 = fHitZ;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pFxOptDmg + 112))(pFxOptDmg, nHitX, nHitY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      v67 = *(float *)(pAtkInfo + 4 * i + 84) - 100.0;
      sub_4049C0(0.69999999, 1.5, (uint64_t)v67, 100);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      fScaleTmp = v67;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxOptDmg + 200))(pFxOptDmg, LODWORD(fScaleTmp));  // 调虚槽 +200：取动画对象
      sub_4922F0(v68);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    }
  }
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);
  Block = nullptr;  // Block = 空指针
  sTmpLen = 0;
  sTmpCap = 0;
  if ( sFinalCap >= 0x10 )  // 若 sFinalCap >= 0x10
    j__free(v94[0]);
}


// ------------------------------------------------------------
// 0x4E9760 sub_4E9760 —— ★ 格挡特效 vt+644（研究 20 §3 格挡分支定案）
// 调用点 = 表现壳 0x4E5DC0 的 `a4 != 0`（格挡）分支：vt+644(this, a2, a3)。
// 反编译体与 §3 原文逐条对应："vt+644(this, 攻击者, 盒) 格挡特效：
//   **GuardSpark.ani + GuardCircle.ani + Stuck.ani**（Character/Swordman/Effect +
//   Common/HitEffect）"：
//     ① "Character/Swordman/Effect/Animation/**GuardSpark.ani**" 池化 →
//        vt+148(攻方 vt+660 取朝向) 设镜像 → vt+112 定位（盒中心 x/y/z）
//     ② "Character/Swordman/Effect/Animation/**GuardCircle.ani**" 同上
//     ③ "Common/HitEffect/Animation/**Stuck.ani**" → vt+72(2) 后定位（z + 30.0 抬高）
//   —— 三条资源名**逐字吻合**研究 §3 ✅
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9760(int *this, int nArg2, float *pArg3)  // 实现：格挡特效 vt+644（研究 20 §3 格挡分支定案）
{
  int nHitX; // ebx
  int pFxObj1; // edi
  int pFxObj2; // edi
  int pFxObj3; // edi
  int nFacing; // [esp+10h] [ebp-14h]
  int nHitY; // [esp+14h] [ebp-10h]
  int hGuardSpark; // [esp+2Ch] [ebp+8h]
  int hGuardCircle; // [esp+2Ch] [ebp+8h]
  int hStuckAni; // [esp+2Ch] [ebp+8h]
  int nHitZ; // [esp+30h] [ebp+Ch]

  nHitX = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
  nHitY = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 124))(this, (uint64_t)(pArg3[3] * 0.5 + *pArg3) >> 32);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nHitZ = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
  nFacing = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)nArg2 + 660))(nArg2, this);  // 调虚槽 +660
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    hGuardSpark = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    hGuardSpark = 0;
  pFxObj1 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( pFxObj1 != 0 )  // 若 pFxObj1 非 0
  {
    sub_44E0D0(hGuardSpark, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pFxObj1 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pFxObj1 = 0;
  }
  sub_45FE80(*(this + 29), pFxObj1, 2, 0, pFxObj1, (int)this, 0);  // 调 实体对象注册到演播层
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pFxObj1 + 148))(pFxObj1, nFacing);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxObj1 + 112))(pFxObj1, nHitX, nHitY, nHitZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    hGuardCircle = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    hGuardCircle = 0;
  pFxObj2 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( pFxObj2 != 0 )  // 若 pFxObj2 非 0
  {
    sub_44E0D0(hGuardCircle, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pFxObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pFxObj2 = 0;
  }
  sub_45FE80(*(this + 29), pFxObj2, 2, 0, pFxObj2, (int)this, 0);  // 调 实体对象注册到演播层
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pFxObj2 + 148))(pFxObj2, nFacing);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxObj2 + 112))(pFxObj2, nHitX, nHitY, nHitZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    hStuckAni = sub_431860((char)"Common/HitEffect/Animation/Stuck.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    hStuckAni = 0;
  pFxObj3 = sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  if ( pFxObj3 != 0 )  // 若 pFxObj3 非 0
  {
    sub_44E0D0(hStuckAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pFxObj3 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pFxObj3 = 0;
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pFxObj3 + 72))(pFxObj3, 2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  sub_45FE80(*(this + 29), pFxObj3, 2, 0, pFxObj3, (int)this, 0);  // 调 实体对象注册到演播层
  return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxObj3 + 112))(pFxObj3, nHitX, nHitY, nHitZ + 30);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
}



// ============================================================
// 【分区 E】特效对象类 / 反作弊属性内核（0x4E99C0 - 0x4EA220）
//   本组 = 命中特效 CNRDObject 派生类共同基座 + ★ **防篡读写全套**
//   （研究 P20-23 / P27 定案：sub_41A590 = 每次写随机换 128 密钥表密钥 + 双通道 XOR；
//     sub_41A5E0 = 数值防篡改校验读取（指针自带 XOR 交叉校验，失败 → 0 +
//     清全局标志 byte_77F48C）—— 伤害/属性读取全部走这一对）。
//   0x4E99C0 = 防篡浮点减；0x4E99F0/0x4E9A10/0x4E9A50/0x4E9B10/0x4E9C00 = clong 类构造族
//   （四个内嵌 clong + 五种参数装载变体）；0x4E9CF0 = 区间随机数（sub_4049C0 插值）
//   ============================================================

// ------------------------------------------------------------
// 0x4E99C0 sub_4E99C0 —— 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
// `sub_41A590(this, cur − a2)` —— 写入走防篡写通道（研究 P20-23：每次写随机换密钥）。
// ------------------------------------------------------------
double /*thiscall*/ sub_4E99C0(void *this, float fArg2)  // 实现：防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
{
  int v3; // edx
  int v5; // [esp+10h] [ebp+8h]

  *(float *)&v5 = COERCE_FLOAT(sub_41A5E0((unsigned int)this)) - fArg2;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, v3, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return *(float *)&v5;
}



// ------------------------------------------------------------
// 0x4E99F0 sub_4E99F0 —— clong 初始化（*this = 4；+4 = a2；+18 = 0）
// 写入走防篡写通道 ·sub_41A590
// ------------------------------------------------------------
int /*fastcall*/ sub_4E99F0(uint32_t *pArg1, int nArg2)  // 实现：clong 初始化（*this = 4；+4 = a2；+18 = 0）
{
  int v3; // edx

  *pArg1 = 4;
  sub_41A590((unsigned int)(pArg1 + 1), nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590((unsigned int)pArg1 + 18, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x4E9A10 sub_4E9A10 —— 记录宿主当前时刻（·this+1336 = clock_now(宿主+36)）
// vt+212 宿主非空 → 写 ·this+1336；否则置 0 并返回 0
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9A10(uint32_t *this)  // 实现：记录宿主当前时刻（·this+1336 = clock_now(宿主+36)）
{
  int v2; // eax
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this) != 0 )  // 调虚槽 +212：播放音效 TAG(→50 声道)
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    result = sub_699000(v2 + 36);  // 【clock_now(clk)】
    *(this + 334) = result;
  }
  else  // 否则分支
  {
    *(this + 334) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E9A50 sub_4E9A50 —— 四内联 clong 构造 + 初值（0/0/-1/0）
// 四段各自 ·sub_41A630 + 设 vftable(clong)，再 ·sub_41A590 写 0/0/-1/0；*this = 0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9A50(uint32_t *this)  // 实现：四内联 clong 构造 + 初值（0/0/-1/0）
{
  uint32_t *pThis_1; // edi
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));  // 调 防篡改字段读校验（crypt 逆运算链）
  *pThis_1 = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)this + 18);  // this+18〔bDragChild〕
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';  // this+18〔bDragChild〕
  sub_41A630((unsigned int)(this + 8));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 8) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)this + 46);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';  // 构造装配 vftable：clong
  *this = 0;
  sub_41A590((unsigned int)pThis_1, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 18, v4, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 8), v5, -1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 46, v6, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4E9B10 sub_4E9B10 —— 与 ·0x4E9A50 同构（差异：随后按 5 参赋初值）
// 赋 *this = a2、+4 = a3 & 0x1F、+18 = 0、+8 = a5、+46 = a3 >> 5
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9B10(uint32_t *this, int nArg2, uint8_t uArg3, int nArg4, int nArg5)  // 实现：与 ·0x4E9A50 同构（差异：随后按 5 参赋初值）
{
  uint32_t *pThis_1; // edi

  pThis_1 = this + 1;
  sub_41A630(this + 1);  // 调 防篡改字段读校验（crypt 逆运算链）
  *pThis_1 = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((char *)this + 18);  // this+18〔bDragChild〕
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';  // this+18〔bDragChild〕
  sub_41A630(this + 8);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 8) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((char *)this + 46);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';  // 构造装配 vftable：clong
  *this = 0;
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(-1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *this = nArg2;
  sub_41A590(uArg3 & 0x1F);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(nArg5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(uArg3 >> 5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4E9C00 sub_4E9C00 —— 与 ·0x4E9A50 同构（差异：随后按 6 参逐个赋四 clong）
// 赋 *this = a2、+4 = a3、+18 = a4、+8 = a5、+46 = a6
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9C00(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：与 ·0x4E9A50 同构（差异：随后按 6 参逐个赋四 clong）
{
  uint32_t *pThis_1; // edi
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));  // 调 防篡改字段读校验（crypt 逆运算链）
  *pThis_1 = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)this + 18);  // this+18〔bDragChild〕
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';  // this+18〔bDragChild〕
  sub_41A630((unsigned int)(this + 8));  // 调 防篡改字段读校验（crypt 逆运算链）
  *(this + 8) = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)this + 46);  // 调 防篡改字段读校验（crypt 逆运算链）
  *(uint32_t *)((char *)this + 46) = &clong::`vftable';  // 构造装配 vftable：clong
  *this = 0;
  sub_41A590((unsigned int)pThis_1, v8, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 18, v9, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 8), v10, -1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 46, v11, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *this = nArg2;
  sub_41A590((unsigned int)pThis_1, v12, nArg3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 18, nArg4, nArg4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 8), v13, nArg5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 46, v14, nArg6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4E9CF0 sub_4E9CF0 —— 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
// `v8 = 传入值 × 乘数 × 0.0099999998`；v10 = sub_432F40(上限夹取 到 a4)；
// `sub_4049C0(-v10, +v10, sub_4D33A0(随机种机) % 1000, 999)` —— 与 0x4E6770 内的
// ± 方差同一手法（LCG %1000 作插值 t，在 [−v10, +v10] 内线性取值）。
// 返回 `原值 + sub_432F40(插值结果)` —— 供调用方直接落地。
// ------------------------------------------------------------
int /*cdecl*/ sub_4E9CF0(int nArg1, unsigned int *pDwArg2, int nArg3, int nArg4)  // 实现：区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
{
  unsigned int v6; // eax
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+Ch] [ebp-8h]
  float v9; // [esp+Ch] [ebp-8h]
  int nArg42; // [esp+1Ch] [ebp+8h]
  float v11; // [esp+1Ch] [ebp+8h]

  if ( *(float *)&nArg1 == 0.0 )
    return 0;
  v8 = (double)nArg1 * (double)nArg3 * 0.0099999998;  // ×0.01f（百分数转比例）
  nArg42 = sub_432F40(v8);  // 舍入取整（float → int）
  if ( nArg42 >= nArg4 )  // 若 nArg42 >= nArg4
    nArg42 = nArg4;
  v11 = (float)nArg42;
  v6 = sub_4D33A0(pDwArg2);  // v6 = 调 sub_4D33A0 返回值
  v7 = -v11;
  v9 = sub_4049C0(v7, v11, v6 % 0x3E8, 999);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  return nArg1 + sub_432F40(v9);  // 舍入取整（float → int）
}



// ------------------------------------------------------------
// 0x4E9D70 sub_4E9D70 —— 对象字段复位（属性/名字/标志组）
// +4 = 2；+1248/+1268/+1276/+1284/+1320/+1324/+1328/+1332 = 0；·sub_41BFE0(+1272, 空串)；
// +1344 = 1065353216 = 浮点 1.0f
// ------------------------------------------------------------
void /*thiscall*/ sub_4E9D70(int this)  // 实现：对象字段复位（属性/名字/标志组）
{
  *(uint32_t *)(this + 4) = 2;  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 1248) = 0;
  *(uint32_t *)(this + 1268) = 0;
  sub_41BFE0((void **)(this + 1272), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint8_t *)(this + 1276) = 0;  // this+1276〔bEffectArmed1276〕
  *(uint32_t *)(this + 1284) = 0;  // this+1284〔nEffectCount1284〕
  *(uint8_t *)(this + 1320) = 0;  // this+1320〔bAnimBuilt1320〕
  *(uint32_t *)(this + 1332) = 0;  // this+1332〔pEquipDef1332〕
  *(uint32_t *)(this + 1324) = 0;  // this+1324〔pAnimAtlas1324〕
  *(uint32_t *)(this + 1328) = 0;  // this+1328〔pAnimHost1328〕
  *(uint32_t *)(this + 1344) = 1065353216;  // this+1344 = 1.0f
}



// ------------------------------------------------------------
// 0x4E9DD0 sub_4E9DD0 —— 攻击属性叠加到 attackinfo（本体 + ·this+1268 附加物两遍）
// vt+200 宿主非空 → 取宿主 vt+1084(·this+148) → 其 vt+200==0 → vt+128(attackinfo) 直通；
// 否则两遍累加：+64/+68/+76/+84 槽（防篡读）与 ·this+148==8 时三属性槽（+20 用 vt+193 槽、+24.. 三项 id + 值）；
// 并置 +82/+140/+141 标志位
// ------------------------------------------------------------
int /*thiscall*/ sub_4E9DD0(char *this, int pArg2)  // 实现：攻击属性叠加到 attackinfo（本体 + ·this+1268 附加物两遍）
{
  char *pThis; // ebx
  int result; // eax
  int pObj; // esi
  char *v6; // edi
  int v7; // ecx
  int v8; // ebx
  uint32_t *v9; // eax
  float v10; // eax
  float *v11; // ebx
  unsigned int v12; // edi
  double v13; // st7
  bool v14; // zf
  int v16; // [esp+10h] [ebp-4h]
  int v17; // [esp+1Ch] [ebp+8h]

  pThis = this;
  if ( (*(uint8_t (/*fastcall*/ **)(char *))(*(uint32_t *)this + 200))(this) != 0 )  // 调虚槽 +200：取动画对象
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, int))(**((uint32_t **)pThis + 321) + 40))(*((uint32_t *)pThis + 321), 273);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)pThis + 321) + 1084))(
                 *((uint32_t *)pThis + 321),
                 *((uint32_t *)pThis + 37));
      pObj = result;
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);  // 调虚槽 +200：取动画对象
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 128))(pObj, pArg2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      }
    }
  }
  else  // 否则分支
  {
    v16 = 0;
    while ( 1 )  // 条件循环
    {
      if ( v16 != 0 )  // 若 v16 非 0
      {
        result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pThis + 224))(pThis);  // 调虚槽 +224：标志读 +172
        if ( (uint8_t)result == 0 )
          return result;
        v6 = *((char **)pThis + 317);
      }
      else  // 否则分支
      {
        v6 = pThis + 212;
      }
      if ( *((uint32_t *)pThis + 37) == 8 && *(uint8_t *)(pArg2 + 16) != 0 )  // 复合条件判定（与/或）
      {
        if ( *(uint32_t *)(pArg2 + 20) == 4 )  // pArg2+20〔nPage(推断)〕
          *(uint32_t *)(pArg2 + 20) = *((uint32_t *)v6 + 193);  // pArg2+20〔nPage(推断)〕
        v7 = *((uint32_t *)v6 + 194);
        if ( v7 != 17 )  // 若 v7 != 17
        {
          v8 = 0;
          v9 = (uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
          while ( *v9 != 17 )  // 条件循环
          {
            ++v8;
            ++v9;
            if ( v8 >= 3 )  // 若 v8 >= 3
              goto LABEL_22;
          }
          *(uint32_t *)(pArg2 + 4 * v8 + 24) = v7;
          *(uint32_t *)(pArg2 + 4 * v8 + 48) = sub_41A5E0((unsigned int)(v6 + 794));  // crypt4byte 解密校验（·0x41A590 逆运算）
          *(float *)(pArg2 + 4 * v8 + 36) = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 780)));  // crypt4byte 解密校验（·0x41A590 逆运算）
        }
LABEL_22:  // 标签 LABEL_22（跳转合流点）
        if ( v6[850] != 0 )
          *(uint8_t *)(pArg2 + 82) = 1;
        if ( v6[879] != 0 )
          *(uint8_t *)(pArg2 + 140) = 1;  // pArg2+140〔nAdd140(推断)〕
        if ( v6[880] != 0 )
          *(uint8_t *)(pArg2 + 141) = 1;  // pArg2+141〔bFadeFlagA(推断)〕
      }
      *(uint32_t *)(pArg2 + 64) += sub_41A5E0((unsigned int)(v6 + 808));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(uint32_t *)(pArg2 + 68) += sub_41A5E0((unsigned int)(v6 + 822));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v10 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 836)));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v11 = (float *)(pArg2 + 84);  // pArg2+84〔pFxObjA(推断)〕
      v12 = (unsigned int)(v6 + 851);
      v17 = 2;
      *(float *)(pArg2 + 76) = v10 + *(float *)(pArg2 + 76);  // pArg2+76〔pBtnActionE〕
      do  // do-while 循环体起点
      {
        v13 = COERCE_FLOAT(sub_41A5E0(v12)) + *v11++;  // crypt4byte 解密校验（·0x41A590 逆运算）
        v12 += 14;
        v14 = v17 == 1;
        *(v11 - 1) = v13;
        --v17;
      }
      while ( !v14 );  // 条件循环
      result = ++v16;
      if ( v16 >= 2 )  // 若 v16 >= 2
        break;  // 跳出循环/分支
      pThis = this;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4E9FA0 sub_4E9FA0 —— 四 clong 防篡拷贝（pArg2 → this）
// 逐槽 ·sub_41A5E0 读 + ·sub_41A590 写
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4E9FA0(uint32_t *this, uint32_t *pArg2)  // 实现：四 clong 防篡拷贝（pArg2 → this）
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx

  *this = *pArg2;
  v3 = sub_41A5E0((unsigned int)(pArg2 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 1), v4, v3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v5 = sub_41A5E0((unsigned int)pArg2 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this + 18, v6, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v7 = sub_41A5E0((unsigned int)(pArg2 + 8));  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)(this + 8), v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v9 = sub_41A5E0((unsigned int)pArg2 + 46);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this + 46, v10, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4EA000 sub_4EA000 —— 低概率技能请求包（发包 type 51；rand()%1000 < 系数）
// 门：本地玩家 dword_8F7C04 + ·this+1192 宿主非空 + ·this+664 非 0 + 态 ·this+148 > 7；
// 系数 v4 = 本地玩家 vt+1108(态 8) 或 vt+1112，PVP/PVE 场景 /= 4；rand()%1000 < v4 → 发 ·dword_8F7B08 包(type 51) + 写 ·this+148
// ------------------------------------------------------------
int /*thiscall*/ sub_4EA000(uint32_t *this)  // 实现：低概率技能请求包（发包 type 51；rand()%1000 < 系数）
{
  int result; // eax
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int nRand; // eax
  int v7; // et2
  uint8_t v8[4]; // [esp+4h] [ebp-4h] BYREF

  result = dword_8F7C04;  // 本地玩家对象
  if ( dword_8F7C04 != 0 )  // 本地玩家对象
  {
    result = sub_41A5E0((unsigned int)(this + 298));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = sub_41A5E0((unsigned int)this + 166);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = *(this + 37);  // this+148〔fAdd148(推断)〕
        if ( result > 7 )  // 若 result > 7
        {
          if ( result == 8 )  // 若 result == 8
            v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1108))(dword_8F7C04);  // 调虚槽 +1108：CNSwordman__vmt454
          else  // 否则分支
            v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1112))(dword_8F7C04);  // 调虚槽 +1112
          v4 = v3;
          v5 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
          if ( v5 == 4 || v5 == 6 )  // 若 v5 == 4 与/或 v5 == 6
            v4 /= 4;
          sub_432FA0();  // srand 播种
          nRand = rand();  // nRand = 调 rand
          v7 = nRand % 1000;
          result = nRand / 1000;
          if ( v7 < v4 )  // 若 v7 < v4
          {
            sub_423200(dword_8F7B08, 51);  // 【发送网络包API】
            v8[0] = *((uint8_t *)this + 148);  // this+148〔fAdd148(推断)〕
            sub_423290(v8, 1);  // 调 写 4B 长度
            return sub_423380(dword_8F7B08);  // 发包提交：Commit()
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EA0E0 sub_4EA0E0 —— 宿主对象切换（宿主 setter：快照通知 + 旧宿主清理）
// 新旧相同 → 0；均非 0 → 直接改写；否则经 ·sub_4E9A50 组装旧值快照 → vt+184 通知（值来自 ·this+1160/+1178 与 ·this+1164）；
// 旧宿主 ·this+1284 非空 → vt+800 + vt+676(0)；条件 273 成立 → vt+1152 + vt+1156 + vt+308 → ·sub_47E4F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EA0E0(uint32_t *this, int nArg2)  // 实现：宿主对象切换（宿主 setter：快照通知 + 旧宿主清理）
{
  unsigned int pThis_12A; // ebx
  int pThis_12A2; // eax
  int v5; // edx
  int fld_e290; // eax
  int pThis_49A; // eax
  int v9; // edx
  int pThis_123; // eax
  int v11; // edx
  int v12; // edx
  int nEffectCount1284; // eax  | +0x0504 → 效果触发计数（0x4BAC70 直写 nArg2；为 0 时联动清 +1276）（证据: va=004BAC70）（CNRDEquipment；va=004BAC70）
  int nEffectCount1284_; // esi  | +0x0504 → 效果触发计数（0x4BAC70 直写 nArg2；为 0 时联动清 +1276）（证据: va=004BAC70）（CNRDEquipment；va=004BAC70）
  int fld_e2902; // [esp+Ch] [ebp-48h] BYREF
  uint8_t v16[14]; // [esp+10h] [ebp-44h] BYREF
  uint8_t v17[14]; // [esp+1Eh] [ebp-36h] BYREF
  uint8_t v18[28]; // [esp+2Ch] [ebp-28h] BYREF
  int v19; // [esp+50h] [ebp-4h]

  pThis_12A = (unsigned int)(this + 298);
  pThis_12A2 = sub_41A5E0((unsigned int)(this + 298));  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( pThis_12A2 == nArg2 )  // 若 pThis_12A2 == nArg2
    return 0;
  if ( pThis_12A2 != 0 && nArg2 != 0 )  // 若 pThis_12A2 != 0 与/或 nArg2 != 0
  {
    sub_41A590(pThis_12A, v5, nArg2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return 0;
  }
  sub_4E9A50(&fld_e2902);  // 四内联 clong 构造 + 初值（0/0/-1/0）
  fld_e290 = *(this + 290);
  v19 = 0;
  fld_e2902 = fld_e290;
  pThis_49A = sub_41A5E0((unsigned int)this + 1178);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)v17, v9, pThis_49A);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_123 = sub_41A5E0((unsigned int)(this + 291));  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)v16, v11, pThis_123);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)v18, v12, nArg2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(uint32_t *, int *))(*this + 184))(this, &fld_e2902);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  nEffectCount1284 = *(this + 321);  // this+1284〔nEffectCount1284〕
  if ( nEffectCount1284 != 0 )  // 若 fld_e321 非 0
  {
    (*(void (**)(void))(*(uint32_t *)nEffectCount1284 + 800))();  // 调虚槽 +800：18 观察者 vt+216 全广播
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 321) + 676))(*(this + 321), 0);  // this+1284〔nEffectCount1284〕
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 321) + 40))(*(this + 321), 273) != 0 )  // this+1284〔nEffectCount1284〕
    {
      nEffectCount1284_ = *(this + 321);  // this+1284〔nEffectCount1284〕
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nEffectCount1284_ + 1152))(nEffectCount1284_);  // 调虚槽 +1152：CNSwordman__vmt480
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nEffectCount1284_ + 1156))(nEffectCount1284_);  // 调虚槽 +1156
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nEffectCount1284_ + 308))(nEffectCount1284_) != 0 )  // 调虚槽 +308：是否本地玩家
        sub_47E4F0();
    }
  }
  v19 = -1;
  sub_445150(&fld_e2902);  // 调 装备同步资源清理
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4EA220 sub_4EA220 —— 属性块逐槽累加（约 60 槽，含两段 14 字节步距数组）
// 对 pArg1 与 pArg2 的同偏移槽：防篡读 pArg2 → ·sub_41A590(pArg1, 和)；
// 覆盖 +14..+294 标量批、+308 起 4 项、+378 起 16 项、+616..+756 批、+808/+822/+836、+851 起 2 项（怪物属性加成施加）
// ------------------------------------------------------------
int /*cdecl*/ sub_4EA220(int pArg1, int pArg2)  // 实现：属性块逐槽累加（约 60 槽，含两段 14 字节步距数组）
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  unsigned int v28; // ebx
  int v29; // eax
  int v30; // edx
  unsigned int v31; // ebx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // eax
  int v46; // edx
  int v47; // eax
  int v48; // eax
  int v49; // edx
  int v50; // edx
  int v51; // edx
  unsigned int v52; // esi
  int j; // edi
  int v54; // edx
  int result; // eax
  int v56; // [esp+Ch] [ebp-4h]
  int v57; // [esp+Ch] [ebp-4h]
  float v58; // [esp+Ch] [ebp-4h]
  float v59; // [esp+Ch] [ebp-4h]
  float v60; // [esp+Ch] [ebp-4h]
  float v61; // [esp+Ch] [ebp-4h]
  float v62; // [esp+Ch] [ebp-4h]
  float v63; // [esp+18h] [ebp+8h]
  float v64; // [esp+18h] [ebp+8h]
  int v65; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]
  int v67; // [esp+18h] [ebp+8h]
  int v68; // [esp+18h] [ebp+8h]
  int v69; // [esp+18h] [ebp+8h]
  int v70; // [esp+18h] [ebp+8h]
  int v71; // [esp+18h] [ebp+8h]
  int v72; // [esp+18h] [ebp+8h]
  int v73; // [esp+18h] [ebp+8h]
  int v74; // [esp+18h] [ebp+8h]
  int v75; // [esp+18h] [ebp+8h]
  int v76; // [esp+18h] [ebp+8h]
  int v77; // [esp+18h] [ebp+8h]
  int v78; // [esp+18h] [ebp+8h]
  int v79; // [esp+18h] [ebp+8h]
  int v80; // [esp+18h] [ebp+8h]
  int v81; // [esp+18h] [ebp+8h]
  int v82; // [esp+1Ch] [ebp+Ch]
  int v83; // [esp+1Ch] [ebp+Ch]
  int v84; // [esp+1Ch] [ebp+Ch]
  int v85; // [esp+1Ch] [ebp+Ch]
  int v86; // [esp+1Ch] [ebp+Ch]
  int v87; // [esp+1Ch] [ebp+Ch]
  int v88; // [esp+1Ch] [ebp+Ch]
  int v89; // [esp+1Ch] [ebp+Ch]
  int v90; // [esp+1Ch] [ebp+Ch]
  int v91; // [esp+1Ch] [ebp+Ch]
  int v92; // [esp+1Ch] [ebp+Ch]
  int v93; // [esp+1Ch] [ebp+Ch]
  int v94; // [esp+1Ch] [ebp+Ch]
  int v95; // [esp+1Ch] [ebp+Ch]
  int v96; // [esp+1Ch] [ebp+Ch]
  int v97; // [esp+1Ch] [ebp+Ch]
  int v98; // [esp+1Ch] [ebp+Ch]

  v82 = sub_41A5E0(pArg2 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v4 = sub_41A5E0(pArg1 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 14, v5, v82 + v4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v83 = sub_41A5E0(pArg2 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v6 = sub_41A5E0(pArg1 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 28, v83, v83 + v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v84 = sub_41A5E0(pArg2 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v7 = sub_41A5E0(pArg1 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 42, v8, v84 + v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v85 = sub_41A5E0(pArg2 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v9 = sub_41A5E0(pArg1 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 56, v85, v85 + v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v86 = sub_41A5E0(pArg2 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v10 = sub_41A5E0(pArg1 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 70, v11, v86 + v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v87 = sub_41A5E0(pArg2 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v12 = sub_41A5E0(pArg1 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 98, v87, v87 + v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v88 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v13 = sub_41A5E0(pArg1 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 112, v14, v88 + v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v89 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v15 = sub_41A5E0(pArg1 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 126, v89, v89 + v15);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v90 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v16 = sub_41A5E0(pArg1 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 140, v17, v90 + v16);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v91 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v18 = sub_41A5E0(pArg1 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 154, v91, v91 + v18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v92 = sub_41A5E0(pArg2 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v19 = sub_41A5E0(pArg1 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 224, v20, v92 + v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v93 = sub_41A5E0(pArg2 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v21 = sub_41A5E0(pArg1 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 238, v93, v93 + v21);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v63 = COERCE_FLOAT(sub_41A5E0(pArg2 + 252));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v94 = COERCE_FLOAT(sub_41A5E0(pArg1 + 252)) + v63;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 252, v22, v94);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v95 = sub_41A5E0(pArg2 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v23 = sub_41A5E0(pArg1 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 266, v24, v95 + v23);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v96 = sub_41A5E0(pArg2 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v25 = sub_41A5E0(pArg1 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 280, v96, v96 + v25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v64 = COERCE_FLOAT(sub_41A5E0(pArg2 + 294));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v97 = COERCE_FLOAT(sub_41A5E0(pArg1 + 294)) + v64;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 294, v26, v97);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v27 = pArg2 - pArg1;
  v28 = pArg1 + 308;
  v98 = pArg2 - pArg1;
  v65 = 4;
  while ( 1 )  // 条件循环
  {
    v56 = sub_41A5E0(v27 + v28);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v29 = sub_41A5E0(v28);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v28, v30, v56 + v29);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v28 += 14;
    if ( --v65 == 0 )
      break;  // 跳出循环/分支
    v27 = pArg2 - pArg1;
  }
  v31 = pArg1 + 378;
  for ( i = 16; i != 0; --i )  // 循环：i 从 16 递减到 0
  {
    v57 = sub_41A5E0(v31 + v98);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v32 = sub_41A5E0(v31);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v31, v33, v57 + v32);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v31 += 14;
  }
  v67 = sub_41A5E0(pArg2 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v34 = sub_41A5E0(pArg1 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 616, v67, v67 + v34);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v68 = sub_41A5E0(pArg2 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v35 = sub_41A5E0(pArg1 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 630, v36, v68 + v35);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v69 = sub_41A5E0(pArg2 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v37 = sub_41A5E0(pArg1 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 644, v69, v69 + v37);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v58 = COERCE_FLOAT(sub_41A5E0(pArg2 + 658));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v70 = COERCE_FLOAT(sub_41A5E0(pArg1 + 658)) + v58;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 658, v38, v70);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v71 = sub_41A5E0(pArg2 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v39 = sub_41A5E0(pArg1 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 672, v40, v71 + v39);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v72 = sub_41A5E0(pArg2 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v41 = sub_41A5E0(pArg1 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 686, v72, v72 + v41);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v73 = sub_41A5E0(pArg2 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v42 = sub_41A5E0(pArg1 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 700, v43, v73 + v42);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v74 = sub_41A5E0(pArg2 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v44 = sub_41A5E0(pArg1 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 714, v74, v74 + v44);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v75 = sub_41A5E0(pArg2 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v45 = sub_41A5E0(pArg1 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 728, v46, v75 + v45);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v76 = sub_41A5E0(pArg2 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v47 = sub_41A5E0(pArg1 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 808, v76, v76 + v47);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v77 = sub_41A5E0(pArg2 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v48 = sub_41A5E0(pArg1 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 822, v49, v77 + v48);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v59 = COERCE_FLOAT(sub_41A5E0(pArg2 + 742));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v78 = COERCE_FLOAT(sub_41A5E0(pArg1 + 742)) + v59;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 742, v78, v78);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v60 = COERCE_FLOAT(sub_41A5E0(pArg2 + 756));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v79 = COERCE_FLOAT(sub_41A5E0(pArg1 + 756)) + v60;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 756, v50, v79);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v61 = COERCE_FLOAT(sub_41A5E0(pArg2 + 836));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v80 = COERCE_FLOAT(sub_41A5E0(pArg1 + 836)) + v61;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 836, v51, v80);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v52 = pArg1 + 851;
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    v62 = COERCE_FLOAT(sub_41A5E0(v52 + v98));  // crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v81 = COERCE_FLOAT(sub_41A5E0(v52)) + v62;  // crypt4byte 解密校验（·0x41A590 逆运算）
    result = sub_41A590(v52, v54, v81);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v52 += 14;
  }
  return result;
}


// ============================================================
// 【分区 F】怪物自身表现 / 装备挂件 / 剩余杂项族（0x4EA7C0 - 文件末）
//   含：怪物血条与状态图标 HUD（研究 §8 sub_4684F0 的怪物侧）、
//   装备/称号挂件（IRDAppendage 族）、数值防篡写接口、以及若干定点数/字符串工具。
//   研究第 31 轮 P35：无敌开关 this+641 的三类调用点（战斗核心/怪物 58xxx AI/反应族）
//   在本区以 vt+604 广播形式出现。
// ============================================================

// ------------------------------------------------------------
// 0x4EA7C0 sub_4EA7C0 —— 定点数/浮点转换工具（cdecl 双参；逐位拆解）
// 与 0x4E9CF0/0x4EB010 同族 —— 属性数值的定点↔浮点桥接【待验证：具体定标】
// ------------------------------------------------------------
int /*cdecl*/ sub_4EA7C0(int pArg1, int pArg2)  // 实现：定点数/浮点转换工具（cdecl 双参；逐位拆解）
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // edx
  int v34; // eax
  unsigned int v35; // ebx
  int v36; // eax
  int v37; // edx
  unsigned int v38; // ebx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // edx
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // edx
  int v62; // edx
  int v63; // edx
  unsigned int v64; // esi
  int j; // edi
  int result; // eax
  int v67; // [esp+Ch] [ebp-4h]
  int v68; // [esp+Ch] [ebp-4h]
  float v69; // [esp+Ch] [ebp-4h]
  float v70; // [esp+Ch] [ebp-4h]
  float v71; // [esp+Ch] [ebp-4h]
  float v72; // [esp+Ch] [ebp-4h]
  float v73; // [esp+Ch] [ebp-4h]
  float v74; // [esp+18h] [ebp+8h]
  float v75; // [esp+18h] [ebp+8h]
  int v76; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]
  int v78; // [esp+18h] [ebp+8h]
  int v79; // [esp+18h] [ebp+8h]
  int v80; // [esp+18h] [ebp+8h]
  int v81; // [esp+18h] [ebp+8h]
  int v82; // [esp+18h] [ebp+8h]
  int v83; // [esp+18h] [ebp+8h]
  int v84; // [esp+18h] [ebp+8h]
  int v85; // [esp+18h] [ebp+8h]
  int v86; // [esp+18h] [ebp+8h]
  int v87; // [esp+18h] [ebp+8h]
  int v88; // [esp+18h] [ebp+8h]
  int v89; // [esp+18h] [ebp+8h]
  int v90; // [esp+18h] [ebp+8h]
  int v91; // [esp+18h] [ebp+8h]
  int v92; // [esp+18h] [ebp+8h]
  int v93; // [esp+1Ch] [ebp+Ch]
  int v94; // [esp+1Ch] [ebp+Ch]
  int v95; // [esp+1Ch] [ebp+Ch]
  int v96; // [esp+1Ch] [ebp+Ch]
  int v97; // [esp+1Ch] [ebp+Ch]
  int v98; // [esp+1Ch] [ebp+Ch]
  int v99; // [esp+1Ch] [ebp+Ch]
  int v100; // [esp+1Ch] [ebp+Ch]
  int v101; // [esp+1Ch] [ebp+Ch]
  int v102; // [esp+1Ch] [ebp+Ch]
  int v103; // [esp+1Ch] [ebp+Ch]
  int v104; // [esp+1Ch] [ebp+Ch]
  int v105; // [esp+1Ch] [ebp+Ch]
  int v106; // [esp+1Ch] [ebp+Ch]
  int v107; // [esp+1Ch] [ebp+Ch]
  int v108; // [esp+1Ch] [ebp+Ch]
  int v109; // [esp+1Ch] [ebp+Ch]

  v93 = sub_41A5E0(pArg2 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v4 = sub_41A5E0(pArg1 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 14, v5, v4 - v93);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v94 = sub_41A5E0(pArg2 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v6 = sub_41A5E0(pArg1 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 28, v7, v6 - v94);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v95 = sub_41A5E0(pArg2 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v8 = sub_41A5E0(pArg1 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 42, v9, v8 - v95);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v96 = sub_41A5E0(pArg2 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v10 = sub_41A5E0(pArg1 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 56, v11, v10 - v96);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v97 = sub_41A5E0(pArg2 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v12 = sub_41A5E0(pArg1 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 70, v13, v12 - v97);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v98 = sub_41A5E0(pArg2 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v14 = sub_41A5E0(pArg1 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 98, v15, v14 - v98);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v99 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v16 = sub_41A5E0(pArg1 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 112, v17, v16 - v99);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v100 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v18 = sub_41A5E0(pArg1 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 126, v19, v18 - v100);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v101 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v20 = sub_41A5E0(pArg1 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 140, v21, v20 - v101);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v102 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v22 = sub_41A5E0(pArg1 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 154, v23, v22 - v102);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v103 = sub_41A5E0(pArg2 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v24 = sub_41A5E0(pArg1 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 224, v25, v24 - v103);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v104 = sub_41A5E0(pArg2 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v26 = sub_41A5E0(pArg1 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 238, v27, v26 - v104);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v74 = COERCE_FLOAT(sub_41A5E0(pArg2 + 252));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v105 = COERCE_FLOAT(sub_41A5E0(pArg1 + 252)) - v74;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 252, v28, v105);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v106 = sub_41A5E0(pArg2 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v29 = sub_41A5E0(pArg1 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 266, v30, v29 - v106);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v107 = sub_41A5E0(pArg2 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v31 = sub_41A5E0(pArg1 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 280, v32, v31 - v107);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v75 = COERCE_FLOAT(sub_41A5E0(pArg2 + 294));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v108 = COERCE_FLOAT(sub_41A5E0(pArg1 + 294)) - v75;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 294, v33, v108);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v34 = pArg2 - pArg1;
  v35 = pArg1 + 308;
  v109 = pArg2 - pArg1;
  v76 = 4;
  while ( 1 )  // 条件循环
  {
    v67 = sub_41A5E0(v34 + v35);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v36 = sub_41A5E0(v35);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v35, v37, v36 - v67);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v35 += 14;
    if ( --v76 == 0 )
      break;  // 跳出循环/分支
    v34 = pArg2 - pArg1;
  }
  v38 = pArg1 + 378;
  for ( i = 16; i != 0; --i )  // 循环：i 从 16 递减到 0
  {
    v68 = sub_41A5E0(v38 + v109);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v39 = sub_41A5E0(v38);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v38, v40, v39 - v68);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v38 += 14;
  }
  v78 = sub_41A5E0(pArg2 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v41 = sub_41A5E0(pArg1 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 616, v42, v41 - v78);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v79 = sub_41A5E0(pArg2 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v43 = sub_41A5E0(pArg1 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 630, v44, v43 - v79);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v80 = sub_41A5E0(pArg2 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v45 = sub_41A5E0(pArg1 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 644, v46, v45 - v80);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v69 = COERCE_FLOAT(sub_41A5E0(pArg2 + 658));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v81 = COERCE_FLOAT(sub_41A5E0(pArg1 + 658)) - v69;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 658, v47, v81);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v82 = sub_41A5E0(pArg2 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v48 = sub_41A5E0(pArg1 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 672, v49, v48 - v82);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v83 = sub_41A5E0(pArg2 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v50 = sub_41A5E0(pArg1 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 686, v51, v50 - v83);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v84 = sub_41A5E0(pArg2 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v52 = sub_41A5E0(pArg1 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 700, v53, v52 - v84);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v85 = sub_41A5E0(pArg2 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v54 = sub_41A5E0(pArg1 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 714, v55, v54 - v85);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v86 = sub_41A5E0(pArg2 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v56 = sub_41A5E0(pArg1 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 728, v57, v56 - v86);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v87 = sub_41A5E0(pArg2 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v58 = sub_41A5E0(pArg1 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 808, v59, v58 - v87);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v88 = sub_41A5E0(pArg2 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v60 = sub_41A5E0(pArg1 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 822, v61, v60 - v88);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v70 = COERCE_FLOAT(sub_41A5E0(pArg2 + 742));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v89 = COERCE_FLOAT(sub_41A5E0(pArg1 + 742)) - v70;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 742, v62, v89);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v71 = COERCE_FLOAT(sub_41A5E0(pArg2 + 756));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v90 = COERCE_FLOAT(sub_41A5E0(pArg1 + 756)) - v71;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 756, v90, v90);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v72 = COERCE_FLOAT(sub_41A5E0(pArg2 + 836));  // crypt4byte 解密校验（·0x41A590 逆运算）
  *(float *)&v91 = COERCE_FLOAT(sub_41A5E0(pArg1 + 836)) - v72;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg1 + 836, v63, v91);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v64 = pArg1 + 851;
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    v73 = COERCE_FLOAT(sub_41A5E0(v64 + v109));  // crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v92 = COERCE_FLOAT(sub_41A5E0(v64)) - v73;  // crypt4byte 解密校验（·0x41A590 逆运算）
    result = sub_41A590(v64, v92, v92);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v64 += 14;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4EAD30 sub_4EAD30 —— 时长到期回调（·this+1336 + ·this+1340 <= clock_now）
// 宿主 vt+212 非空 + ·this+1340 时长非 0 且到点 → ·sub_4E9A10 刷新 + vt+300 通知
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4EAD30(unsigned int *this)  // 实现：时长到期回调（·this+1336 + ·this+1340 <= clock_now）
{
  unsigned int result; // eax
  int v3; // eax

  result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *(this + 335);
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v3 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 212))(this);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      result = sub_699000(v3 + 36);  // 【clock_now(clk)】
      if ( *(this + 335) + *(this + 334) <= result )
      {
        sub_4E9A10(this);  // 记录宿主当前时刻（·this+1336 = clock_now(宿主+36)）
        return (*(int (/*thiscall*/ **)(unsigned int *))(*this + 300))(this);  // 调虚槽 +300：CNGhoulNoMercy 受击属性槽 vmt12C
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EAD80 sub_4EAD80 —— 派生数值公式（(基数+5)×倍率×0.01/上限×(上限−当前)）
// 返回 ((·this+32 + 5.0) × ·this+56(float) × 0.01 / ·this+664 × (·this+664 − ·this+1192))【推断：血/经验派生】
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4EAD80(int *this)  // 实现：派生数值公式（(基数+5)×倍率×0.01/上限×(上限−当前)）
{
  float fld_e14; // [esp+8h] [ebp-8h]
  float pThis_A6; // [esp+Ch] [ebp-4h]

  fld_e14 = (float)*(this + 14);  // this+56〔pCmdVecCap56(推断)〕
  pThis_A6 = (float)sub_41A5E0((unsigned int)this + 166);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)(((double)*(this + 8) + 5.0)  // this+32〔nHeight(推断)〕
                          * fld_e14
                          * 0.0099999998  // ×0.01f（百分数转比例）
                          / pThis_A6
                          * (pThis_A6 - (double)sub_41A5E0((unsigned int)(this + 298))));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4EADE0 sub_4EADE0 —— 在线时长文本投递（场景 1 且小时 < 24）
// 门：宿主 vt+212 + 宿主 vt+308 + ·sub_41C590(·dword_8F7A24)==0 + 态 ·this+148 <= 7 + ·this+1160 非 0；
// v4 = vt+204（分钟），v5 = v4/3600；小时 < 24 且非 0 → 取 vt+16 的 +8 名称 → ·sub_422E70(395) 模板 sprintf，
// → ·sub_44E8D0(·dword_8F8528, 0x24, Buffer, 0) 投递
// ------------------------------------------------------------
char /*thiscall*/ sub_4EADE0(int *this)  // 实现：在线时长文本投递（场景 1 且小时 < 24）
{
  int fld_e290; // eax
  int pObj; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  const char *v7; // eax
  const CHAR *v9; // [esp-Ch] [ebp-418h]
  char Buffer[1028]; // [esp+4h] [ebp-408h] BYREF
  int dword_796E502; // [esp+408h] [ebp-4h]

  dword_796E502 = dword_796E50;
  fld_e290 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  if ( fld_e290 != 0 )  // 若 fld_e290 非 0
  {
    pObj = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    LOBYTE(fld_e290) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)fld_e290 != 0 )
    {
      LOBYTE(fld_e290) = sub_41C590((uint32_t *)dword_8F7A24);  // 状态查询（this+348 == 4）
      if ( (uint8_t)fld_e290 == 0 && *(this + 37) <= 7 )  // 复合条件判定（与/或）
      {
        fld_e290 = *(this + 290);
        if ( fld_e290 != 0 )  // 若 fld_e290 非 0
        {
          LOBYTE(fld_e290) = dword_8F7A24;  // 登录/选区管理器
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // 登录/选区管理器
          {
            v4 = (*(int (/*thiscall*/ **)(int *))(*this + 204))(this);  // 调虚槽 +204：定时器插入
            LOBYTE(fld_e290) = -59 * v4;
            v5 = v4 / 3600;
            if ( v4 / 3600 < 24 && v4 != 0 )  // 若 v4 != 0
            {
              v6 = (*(int (/*thiscall*/ **)(int *))(*this + 16))(this);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
              v9 = sub_41ACF0((unsigned int **)(v6 + 8));  // 驻留串句柄 → 字符串指针
              v7 = (const char *)sub_422E70(395);  // v7 = 调 sub_422E70 返回值
              sprintf(Buffer, v7, v9, v5 + 1);  // 拼字符串
              LOBYTE(fld_e290) = sub_44E8D0((char *)dword_8F8528, (void *)0x24, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
            }
          }
        }
      }
    }
  }
  return fld_e290;
}



// ------------------------------------------------------------
// 0x4EAEE0 sub_4EAEE0 —— 属性 id → 颜色表查（·dword_9B0978[值]）
// vt+176 → 防篡读 ·sub_41A5E0 作下标
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAEE0(void *this)  // 实现：属性 id → 颜色表查（·dword_9B0978）
{
  unsigned int pThis_B0; // eax

  pThis_B0 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 176))(this);  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
  return dword_9B0978[sub_41A5E0(pThis_B0)];  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4EAF00 sub_4EAF00 —— 属性 id → 颜色表查（·dword_6FA248，越界返回 -16776961）
// vt+176 → 防篡读值 < 5 ? ·dword_6FA248[值] : -16776961（= 0xFEFFFFFF 兜底色）
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF00(void *this)  // 实现：属性 id → 颜色表查（·dword_6FA248，越界返回 -16776961）
{
  unsigned int pThis_B0; // eax
  int v2; // eax

  pThis_B0 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 176))(this);  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
  v2 = sub_41A5E0(pThis_B0);  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( v2 < 5 )  // 若 v2 < 5
    return dword_6FA248[v2];  // 返回 取 dword_6FA248[v2]
  else  // 否则分支
    return -16776961;
}



// ------------------------------------------------------------
// 0x4EAF30 sub_4EAF30 —— 记录宿主引用（+1324/+1328 = 宿主 +1092/+1096；+1332 = 宿主）
// 三字段直写，无门
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF30(uint32_t *this, int pArg2)  // 实现：记录宿主引用（+1324/+1328 = 宿主 +1092/+1096；+1332 = 宿主）
{
  *(this + 331) = *(uint32_t *)(pArg2 + 1092);  // this+1324〔pAnimAtlas1324〕
  *(this + 332) = *(uint32_t *)(pArg2 + 1096);  // this+1328〔pAnimHost1328〕
  *(this + 333) = pArg2;  // this+1332〔pEquipDef1332〕
  return pArg2;
}



// ------------------------------------------------------------
// 0x4EAF60 sub_4EAF60 —— 元素个数 =（+8 − +4）/80
// 80 字节 = 属性条目步距（·0x4EB900 与 ·0x4ED080 同一步距）
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF60(int *this)  // 实现：元素个数 =（+8 − +4）/80
{
  int result; // eax

  result = *(this + 1);  // this+4〔宿主对象〕
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 80;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4EAF80 sub_4EAF80 —— 元素个数 =（+8 − +4）/124
// 124 字节步距与 ·0x4EB6A0/·0x4EB6E0 的遍历步距一致
// ------------------------------------------------------------
int /*thiscall*/ sub_4EAF80(int *this)  // 实现：元素个数 =（+8 − +4）/124
{
  int result; // eax

  result = *(this + 1);  // this+4〔宿主对象〕
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 124;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4EAFB0 sub_4EAFB0 —— 32 字节条目区间前向拷贝（含防篡拷贝 +4/+18）
// 每步 8 字：*dst = *src、·sub_41A5E0/·sub_41A590 传 +4/+18；返回尾指针
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EAFB0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：32 字节条目区间前向拷贝（含防篡拷贝 +4/+18）
{
  uint32_t *uArg12; // esi
  uint32_t *uArg32; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx

  uArg12 = uArg1;
  if ( uArg1 == uArg2 )  // 若 uArg1 == uArg2
    return uArg3;
  uArg32 = uArg3;
  do  // do-while 循环体起点
  {
    *uArg32 = *uArg12;
    v5 = sub_41A5E0((unsigned int)(uArg12 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(uArg32 + 1), v6, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v7 = sub_41A5E0((unsigned int)uArg12 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)uArg32 + 18, v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    uArg12 += 8;
    uArg32 += 8;
  }
  while ( uArg12 != uArg2 );  // 条件循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4EB010 sub_4EB010 —— 32 字节条目区间逆序拷贝（后向）
// 从后往前每步 8 字，含防篡拷贝；返回起始指针
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB010(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：32 字节条目区间逆序拷贝（后向）
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do  // do-while 循环体起点
  {
    v5 = *(uint32_t *)(nArg22 - 32);
    nArg22 -= 32;
    uArg32 -= 8;
    *uArg32 = v5;
    v6 = sub_41A5E0(nArg22 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(uArg32 + 1), v7, v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = sub_41A5E0(nArg22 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)uArg32 + 18, v9, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  while ( nArg22 != nArg1 );  // 条件循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x4EB070 sub_4EB070 —— cfloat 构造（vftable + 防篡读拷贝初值）
// ·sub_41A630 先构基类接口，再置 cfloat vftable 并写入 uArg2 的值
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EB070(uint32_t *this, unsigned int uArg2)  // 实现：cfloat 构造（vftable + 防篡读拷贝初值）
{
  int v3; // eax
  int v4; // edx

  sub_41A630((unsigned int)this);  // 调 防篡改字段读校验（crypt 逆运算链）
  *this = &cfloat::`vftable';  // 构造装配 vftable：cfloat
  v3 = sub_41A5E0(uArg2);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, v4, v3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4EB0D0 sub_4EB0D0 —— 条目拷贝（*this = *pArg2 + ·sub_46B080 处理 +4/+18 引用计数）
// +4 与 +18 两处内嵌对象各走 ·sub_46B080（引用计数/独占拷贝）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EB0D0(uint32_t *this, uint32_t *pArg2)  // 实现：条目拷贝（*this = *pArg2 + ·sub_46B080 处理 +4/+18 引用计数）
{
  *this = *pArg2;
  sub_46B080(pArg2 + 1);  // clong 构造与初值写入
  sub_46B080((char *)pArg2 + 18);  // clong 构造与初值写入
  return this;
}



// ------------------------------------------------------------
// 0x4EB130 sub_4EB130 —— 与 ·0x4EAFB0 同构（纯转发）
// 编译器为不同调用约定/内联策略生成的别名入口
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB130(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：与 ·0x4EAFB0 同构（纯转发）
{
  return sub_4EAFB0(uArg1, uArg2, uArg3);  // 32 字节条目区间前向拷贝（含防篡拷贝 +4/+18）
}



// ------------------------------------------------------------
// 0x4EB150 sub_4EB150 —— 32 字节条目区间填充（同值 pArg3，前向）
// 每步 8 字写同一源值（读一次 pArg3 反复写），返回区间尾地址
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB150(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 实现：32 字节条目区间填充（同值 pArg3，前向）
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 8 )  // 遍历循环
  {
    *i = *pArg3;
    v5 = sub_41A5E0((unsigned int)(pArg3 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(i + 1), v6, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v7 = sub_41A5E0((unsigned int)pArg3 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)i + 18, v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB1A0 sub_4EB1A0 —— 与 ·0x4EB010 同构（纯转发）
// 编译器为不同调用约定/内联策略生成的别名入口
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB1A0(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：与 ·0x4EB010 同构（纯转发）
{
  return sub_4EB010(nArg1, nArg2, uArg3);  // 32 字节条目区间逆序拷贝（后向）
}



// ------------------------------------------------------------
// 0x4EB1C0 sub_4EB1C0 —— 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
// 每步：*dst = *src；·sub_41A630(+4) 后设 clong vftable；·sub_41A5E0/·sub_41A590 传 +4；同法 +18
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EB1C0(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
{
  uint32_t *uArg32; // esi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v10; // [esp+0h] [ebp-24h] BYREF
  uint32_t *v11; // [esp+Ch] [ebp-18h]
  uint32_t *uArg33; // [esp+10h] [ebp-14h]
  int *v13; // [esp+14h] [ebp-10h]
  int v14; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  v13 = &v10;
  uArg33 = uArg3;
  v14 = 0;
  while ( pArg1 != uArg2 )  // 条件循环
  {
    LOBYTE(v14) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
    {
      *uArg32 = *pArg1;
      v11 = uArg32 + 1;
      sub_41A630((unsigned int)(uArg32 + 1));  // 调 防篡改字段读校验（crypt 逆运算链）
      LOBYTE(v14) = 2;
      uArg32[1] = &clong::`vftable';  // 构造装配 vftable：clong
      v5 = sub_41A5E0((unsigned int)(a1 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)(v3 + 1), v6, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      LOBYTE(v14) = 3;
      v11 = (uint32_t *)((char *)v3 + 18);
      sub_41A630((unsigned int)v3 + 18);  // 调 防篡改字段读校验（crypt 逆运算链）
      LOBYTE(v14) = 4;
      *(uint32_t *)((char *)v3 + 18) = &clong::`vftable';  // 构造装配 vftable：clong
      v7 = sub_41A5E0((unsigned int)pArg1 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)uArg32 + 18, v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    uArg32 += 8;
    LOBYTE(v14) = 0;
    pArg1 += 8;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4EB2C0 sub_4EB2C0 —— 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
// 遍历 this 的帧指针组（+0/+4/+8、+12/+16 两项、+20..+32、+40 与 +56 两 vector）；
// 每帧 ·sub_4922F0(帧, fArg2) 缩放 + ·sub_4910E0/·sub_493A60 推帧
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB2C0(int *this, float fArg2)  // 实现：动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
{
  uint32_t *v3; // ecx
  float fArg22; // edi
  int v5; // ebx
  uint32_t *fld_e1; // ecx
  int fld_e12; // ebx
  uint32_t *fld_e2; // ecx
  int fld_e22; // ebx
  int *pThis_3; // ebx
  int v11; // edi
  unsigned int fld_e11; // eax
  uint32_t *fld_e5; // ecx
  int fld_e52; // ebx
  uint32_t *fld_e6; // ecx
  int fld_e62; // ebx
  uint32_t *fld_e7; // ecx
  int fld_e72; // ebx
  uint32_t *fld_e8; // ecx
  int fld_e82; // edi
  unsigned int j; // ebx
  int fld_e10; // ecx
  int fld_e102; // edi
  unsigned int k; // ebx
  int fld_e14; // ecx
  int fld_e142; // edi
  int i; // [esp+Ch] [ebp-4h]

  v3 = (uint32_t *)*this;
  fArg22 = fArg2;
  if ( v3 != nullptr )  // 若 v3 有效（非空）
  {
    sub_4922F0(v3, fArg2);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    v5 = *this;
    sub_4910E0(*this);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(v5, *(uint32_t *)(v5 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
  {
    sub_4922F0(fld_e1, fArg2);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e12 = *(this + 1);  // this+4〔宿主对象〕
    sub_4910E0(fld_e12);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(fld_e12, *(uint32_t *)(fld_e12 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  fld_e2 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( fld_e2 != nullptr )  // 若 fld_e2 有效（非空）
  {
    sub_4922F0(fld_e2, fArg2);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    sub_4910E0(fld_e22);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(fld_e22, *(uint32_t *)(fld_e22 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  pThis_3 = this + 3;
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    if ( *pThis_3 != 0 )
    {
      sub_4922F0((uint32_t *)*pThis_3, fArg22);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      v11 = *pThis_3;
      sub_4910E0(*pThis_3);  // 帧时刻推进（返回 1 表示时刻发生位移）
      sub_493A60(v11, *(uint32_t *)(v11 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
      fArg22 = fArg2;
    }
    ++pThis_3;
    LOBYTE(fld_e11) = i - 1;
  }
  fld_e5 = (uint32_t *)*(this + 5);  // this+20〔nPage(推断)〕
  if ( fld_e5 != nullptr )  // 若 fld_e5 有效（非空）
  {
    sub_4922F0(fld_e5, fArg22);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e52 = *(this + 5);  // this+20〔nPage(推断)〕
    sub_4910E0(fld_e52);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e52, *(uint32_t *)(fld_e52 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  fld_e6 = (uint32_t *)*(this + 6);  // this+24〔nPageMax(推断)〕
  if ( fld_e6 != nullptr )  // 若 fld_e6 有效（非空）
  {
    sub_4922F0(fld_e6, fArg22);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e62 = *(this + 6);  // this+24〔nPageMax(推断)〕
    sub_4910E0(fld_e62);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e62, *(uint32_t *)(fld_e62 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  fld_e7 = (uint32_t *)*(this + 7);  // this+28〔pPanelVec(推断)〕
  if ( fld_e7 != nullptr )  // 若 fld_e7 有效（非空）
  {
    sub_4922F0(fld_e7, fArg22);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e72 = *(this + 7);  // this+28〔pPanelVec(推断)〕
    sub_4910E0(fld_e72);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e72, *(uint32_t *)(fld_e72 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  fld_e8 = (uint32_t *)*(this + 8);  // this+32〔nHeight(推断)〕
  if ( fld_e8 != nullptr )  // 若 fld_e8 有效（非空）
  {
    sub_4922F0(fld_e8, fArg22);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    fld_e82 = *(this + 8);  // this+32〔nHeight(推断)〕
    sub_4910E0(fld_e82);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e82, *(uint32_t *)(fld_e82 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  for ( j = 0; ; ++j )  // 无限循环：j 从 0 递增
  {
    fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
    if ( fld_e10 == 0 )  // 若 fld_e10 为 0
      break;  // 跳出循环/分支
    fld_e11 = (*(this + 11) - fld_e10) >> 2;  // this+44〔nExpireMs(推断)〕
    if ( j >= fld_e11 )  // 若 j >= fld_e11
      break;  // 跳出循环/分支
    fld_e11 = *(this + 10) + 4 * j;  // this+40〔bStateSub40(推断)〕
    if ( *(uint32_t *)(fld_e10 + 4 * j) != 0 )
    {
      sub_4922F0(*(uint32_t **)fld_e11, fArg2);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      fld_e102 = *(uint32_t *)(4 * j + *(this + 10));  // fld_e102 = 读 this+10
      sub_4910E0(fld_e102);  // 帧时刻推进（返回 1 表示时刻发生位移）
      LOBYTE(fld_e11) = sub_493A60(fld_e102, *(uint32_t *)(fld_e102 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
    }
  }
  for ( k = 0; ; ++k )  // 无限循环：k 从 0 递增
  {
    fld_e14 = *(this + 14);  // this+56〔pCmdVecCap56(推断)〕
    if ( fld_e14 == 0 )  // 若 fld_e14 为 0
      break;  // 跳出循环/分支
    fld_e11 = (*(this + 15) - fld_e14) >> 2;  // this+60〔nFadeValue60(推断)〕
    if ( k >= fld_e11 )  // 若 k >= fld_e11
      break;  // 跳出循环/分支
    fld_e11 = 4 * k + *(this + 14);
    if ( *(uint32_t *)(fld_e14 + 4 * k) != 0 )
    {
      sub_4922F0(*(uint32_t **)fld_e11, fArg2);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
      fld_e142 = *(uint32_t *)(4 * k + *(this + 14));  // fld_e142 = 读 this+14
      sub_4910E0(fld_e142);  // 帧时刻推进（返回 1 表示时刻发生位移）
      LOBYTE(fld_e11) = sub_493A60(fld_e142, *(uint32_t *)(fld_e142 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
    }
  }
  return fld_e11;
}


// ------------------------------------------------------------
// 0x4EB4B0 sub_4EB4B0 —— 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
// 每帧 ·sub_4923F0(fArg2) 即 ×1/fArg2，抵消 ·0x4EB2C0 的乘算
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB4B0(int *this, float fArg2)  // 实现：与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
{
  float fArg22; // edi
  int v4; // ebx
  int fld_e1; // ebx
  int fld_e2; // ebx
  int *pThis_3; // ebx
  int v8; // edi
  unsigned int fld_e11; // eax
  int fld_e5; // ebx
  int fld_e6; // ebx
  int fld_e7; // ebx
  int fld_e8; // edi
  unsigned int j; // ebx
  int fld_e10; // ecx
  int fld_e102; // edi
  unsigned int k; // ebx
  int fld_e14; // ecx
  int fld_e142; // edi
  int i; // [esp+Ch] [ebp-4h]

  fArg22 = fArg2;
  if ( *this != 0 )
  {
    sub_4923F0(fArg2);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    v4 = *this;
    sub_4910E0(*this);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(v4, *(uint32_t *)(v4 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
  {
    sub_4923F0(fArg2);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    sub_4910E0(fld_e1);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(fld_e1, *(uint32_t *)(fld_e1 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  if ( *(this + 2) != 0 )  // this+8〔nSkillRec8(推断)〕
  {
    sub_4923F0(fArg2);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    sub_4910E0(fld_e2);  // 帧时刻推进（返回 1 表示时刻发生位移）
    sub_493A60(fld_e2, *(uint32_t *)(fld_e2 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  pThis_3 = this + 3;
  for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
  {
    if ( *pThis_3 != 0 )
    {
      sub_4923F0(fArg22);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
      v8 = *pThis_3;
      sub_4910E0(*pThis_3);  // 帧时刻推进（返回 1 表示时刻发生位移）
      sub_493A60(v8, *(uint32_t *)(v8 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
      fArg22 = fArg2;
    }
    ++pThis_3;
    LOBYTE(fld_e11) = i - 1;
  }
  if ( *(this + 5) != 0 )  // this+20〔nPage(推断)〕
  {
    sub_4923F0(fArg22);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
    sub_4910E0(fld_e5);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e5, *(uint32_t *)(fld_e5 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  if ( *(this + 6) != 0 )  // this+24〔nPageMax(推断)〕
  {
    sub_4923F0(fArg22);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e6 = *(this + 6);  // this+24〔nPageMax(推断)〕
    sub_4910E0(fld_e6);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e6, *(uint32_t *)(fld_e6 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  if ( *(this + 7) != 0 )  // this+28〔pPanelVec(推断)〕
  {
    sub_4923F0(fArg22);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e7 = *(this + 7);  // this+28〔pPanelVec(推断)〕
    sub_4910E0(fld_e7);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e7, *(uint32_t *)(fld_e7 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  if ( *(this + 8) != 0 )  // this+32〔nHeight(推断)〕
  {
    sub_4923F0(fArg22);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
    fld_e8 = *(this + 8);  // this+32〔nHeight(推断)〕
    sub_4910E0(fld_e8);  // 帧时刻推进（返回 1 表示时刻发生位移）
    LOBYTE(fld_e11) = sub_493A60(fld_e8, *(uint32_t *)(fld_e8 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
  }
  for ( j = 0; ; ++j )  // 无限循环：j 从 0 递增
  {
    fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
    if ( fld_e10 == 0 )  // 若 fld_e10 为 0
      break;  // 跳出循环/分支
    fld_e11 = (*(this + 11) - fld_e10) >> 2;  // this+44〔nExpireMs(推断)〕
    if ( j >= fld_e11 )  // 若 j >= fld_e11
      break;  // 跳出循环/分支
    fld_e11 = *(this + 10) + 4 * j;  // this+40〔bStateSub40(推断)〕
    if ( *(uint32_t *)(fld_e10 + 4 * j) != 0 )
    {
      sub_4923F0(fArg2);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
      fld_e102 = *(uint32_t *)(4 * j + *(this + 10));  // fld_e102 = 读 this+10
      sub_4910E0(fld_e102);  // 帧时刻推进（返回 1 表示时刻发生位移）
      LOBYTE(fld_e11) = sub_493A60(fld_e102, *(uint32_t *)(fld_e102 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
    }
  }
  for ( k = 0; ; ++k )  // 无限循环：k 从 0 递增
  {
    fld_e14 = *(this + 14);  // this+56〔pCmdVecCap56(推断)〕
    if ( fld_e14 == 0 )  // 若 fld_e14 为 0
      break;  // 跳出循环/分支
    fld_e11 = (*(this + 15) - fld_e14) >> 2;  // this+60〔nFadeValue60(推断)〕
    if ( k >= fld_e11 )  // 若 k >= fld_e11
      break;  // 跳出循环/分支
    fld_e11 = 4 * k + *(this + 14);
    if ( *(uint32_t *)(fld_e14 + 4 * k) != 0 )
    {
      sub_4923F0(fArg2);  // 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
      fld_e142 = *(uint32_t *)(4 * k + *(this + 14));  // fld_e142 = 读 this+14
      sub_4910E0(fld_e142);  // 帧时刻推进（返回 1 表示时刻发生位移）
      LOBYTE(fld_e11) = sub_493A60(fld_e142, *(uint32_t *)(fld_e142 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
    }
  }
  return fld_e11;
}


// ------------------------------------------------------------
// 0x4EB6A0 sub_4EB6A0 —— this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
// 区间 [·this+1292, ·this+1296)，逐元素（元素 +4 起）调 ·sub_4EB2C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB6A0(uint32_t *this, float fArg2)  // 实现：this+1292 起 124 字节步距数组遍历 → ·0x4EB2C0
{
  int fld_e323; // esi
  int i; // edi
  char result; // al

  fld_e323 = *(this + 323);  // this+1292〔pAnimRow1292〕
  for ( i = *(this + 324); fld_e323 != i; fld_e323 += 124 )  // 遍历循环
    result = sub_4EB2C0((int *)(fld_e323 + 4), fArg2);  // 动画帧统一乘算缩放（·sub_4922F0）+ 时间轴推进
  return result;
}



// ------------------------------------------------------------
// 0x4EB6E0 sub_4EB6E0 —— 与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
// 同一步距区间遍历，仅换用按倒数缩放的帧处理
// ------------------------------------------------------------
char /*thiscall*/ sub_4EB6E0(uint32_t *this, float fArg2)  // 实现：与 ·0x4EB6A0 同构（差异：调 ·0x4EB4B0）
{
  int fld_e323; // esi
  int i; // edi
  char result; // al

  fld_e323 = *(this + 323);  // this+1292〔pAnimRow1292〕
  for ( i = *(this + 324); fld_e323 != i; fld_e323 += 124 )  // 遍历循环
    result = sub_4EB4B0((int *)(fld_e323 + 4), fArg2);  // 与 ·0x4EB2C0 同构（差异：·sub_4923F0 按倒数缩放）
  return result;
}



// ------------------------------------------------------------
// 0x4EB720 sub_4EB720 —— 宿主属性持有标志刷新（·this+1276）
// 门：·this+1284 宿主非空 + vt+236 非 0 + ·this+1268 非 0 + vt+200==0；
// 遍历 ·this+1256 容器与宿主 vt+792(i)（i < 18）匹配：全不中 → +1276 = 1（未持有），命中 → 0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EB720(uint32_t *this)  // 实现：宿主属性持有标志刷新（·this+1276）
{
  int result; // eax
  int i; // edi
  int pObj; // esi
  uint32_t *v5; // [esp+4h] [ebp-4h]

  result = *(this + 321);  // this+1284〔nEffectCount1284〕
  if ( result != 0  // 若 result 非 0
    && (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 236))(this)) != 0  // 调虚槽 +236
    && (result = *(this + 317)) != 0
    && (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this)) == 0 )  // 调虚槽 +200：取动画对象
  {
    result = *(this + 314);  // this+1256〔pCondVec1256〕
    v5 = (uint32_t *)result;
    if ( result == *(this + 315) )  // this+1260〔pCondVec1260〕
    {
LABEL_13:  // 标签 LABEL_13（跳转合流点）
      *((uint8_t *)this + 1276) = 1;  // this+1276〔bEffectArmed1276〕
    }
    else  // 否则分支
    {
      while ( 1 )  // 条件循环
      {
        for ( i = 0; i < 18; ++i )  // 循环：i 从 0 递增到 18
        {
          result = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 321) + 792))(*(this + 321), i);  // this+1284〔nEffectCount1284〕
          pObj = result;
          if ( result != 0 )  // 若结果非 0（成功）
          {
            result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 16))(result) + 4);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
            if ( result == *v5 )
            {
              result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 200))(pObj);  // 调虚槽 +200：取动画对象
              if ( (uint8_t)result == 0 )
                break;  // 跳出循环/分支
            }
          }
        }
        if ( i == 18 )  // 若 i == 18
          break;  // 跳出循环/分支
        result = (int)++v5;
        if ( v5 == (uint32_t *)*(this + 315) )  // this+1260〔pCondVec1260〕
          goto LABEL_13;
      }
      *((uint8_t *)this + 1276) = 0;  // this+1276〔bEffectArmed1276〕
    }
  }
  else  // 否则分支
  {
    *((uint8_t *)this + 1276) = 0;  // this+1276〔bEffectArmed1276〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB800 sub_4EB800 —— 32 字节条目批量构造（nArg2 个，源自 pArg3）
// 每步同 ·0x4EB1C0 语义（*dst = *pArg3 + clong 构造 + 防篡拷贝），正向写 nArg2 个
// ------------------------------------------------------------
int /*cdecl*/ sub_4EB800(uint32_t *uArg1, int nArg2, uint32_t *pArg3)  // 实现：32 字节条目批量构造（nArg2 个，源自 pArg3）
{
  uint32_t *uArg12; // esi
  int result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // [esp+0h] [ebp-28h] BYREF
  uint32_t *v10; // [esp+Ch] [ebp-1Ch]
  uint32_t *uArg122; // [esp+10h] [ebp-18h]
  uint32_t *uArg13; // [esp+14h] [ebp-14h]
  int *v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  uArg12 = uArg1;
  v13 = &v9;
  uArg13 = uArg1;
  v14 = 0;
  while ( 1 )  // 条件循环
  {
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
      break;  // 跳出循环/分支
    uArg122 = uArg12;
    LOBYTE(v14) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 有效（非空）
    {
      *uArg12 = *pArg3;
      v10 = uArg12 + 1;
      sub_41A630((unsigned int)(uArg12 + 1));  // 调 防篡改字段读校验（crypt 逆运算链）
      LOBYTE(v14) = 2;
      uArg12[1] = &clong::`vftable';  // 构造装配 vftable：clong
      v5 = sub_41A5E0((unsigned int)(a3 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)(v3 + 1), v6, v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      LOBYTE(v14) = 3;
      v10 = (uint32_t *)((char *)v3 + 18);
      sub_41A630((unsigned int)v3 + 18);  // 调 防篡改字段读校验（crypt 逆运算链）
      LOBYTE(v14) = 4;
      *(uint32_t *)((char *)v3 + 18) = &clong::`vftable';  // 构造装配 vftable：clong
      v7 = sub_41A5E0((unsigned int)pArg3 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)uArg12 + 18, v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    uArg12 += 8;
    LOBYTE(v14) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EB900 sub_4EB900 —— 属性条目文本格式化（按条目 id 分支，输出静态缓冲 byte_9B0990）
// 越界/ -1 → ·sub_422E70(378)；条目 id == 0 → 394；+4 标志 → 379/380 + 名称（%s %.1f%% %s）；
// switch 条目 id：0x1D 百分比、0x21 重量(%d.%03dkg)、0x22(×0.6)/0x23(×3)/0x24、0x25..0x27(± 与 ×0.1)、0x2B 查表 ·sub_47E720、default(%d 正负说明)
// ------------------------------------------------------------
char */*thiscall*/ sub_4EB900(uint32_t *this, unsigned int uArg2)  // 实现：属性条目文本格式化（按条目 id 分支，输出静态缓冲 byte_9B0990）
{
  int pNameBuf; // eax
  int fld_e2302; // esi
  unsigned int v4; // ecx
  const char *v5; // eax
  const char *v6; // eax
  int v7; // ebx
  const char *v8; // eax
  char *result; // eax
  const char *v10; // eax
  const char *v11; // eax
  const char *v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  double v17; // [esp+0h] [ebp-18h]
  int v18; // [esp+0h] [ebp-18h]
  int v19; // [esp+0h] [ebp-18h]
  double v20; // [esp+4h] [ebp-14h]
  const char *v21; // [esp+8h] [ebp-10h]
  const char *v22; // [esp+8h] [ebp-10h]
  int v23; // [esp+8h] [ebp-10h]
  int v24; // [esp+8h] [ebp-10h]

  if ( uArg2 == -1 )
    return (char *)sub_422E70(378);  // 返回 调 sub_422E70 返回值
  pNameBuf = *(this + 230);  // this+920〔pNameBuf〕
  if ( pNameBuf == 0 || uArg2 >= (*(this + 231) - pNameBuf) / 80 )  // 若 fld_e230 == 0
    return (char *)sub_422E70(378);  // 返回 调 sub_422E70 返回值
  fld_e2302 = *(this + 230) + 80 * uArg2;  // this+920〔pNameBuf〕
  if ( *(uint32_t *)fld_e2302 == 0 )
    return (char *)sub_422E70(394);  // 返回 调 sub_422E70 返回值
  v4 = fld_e2302 + 5;
  if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
  {
    if ( COERCE_FLOAT(sub_41A5E0(v4)) < 1.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      v5 = (const char *)sub_422E70(380);  // v5 = 调 sub_422E70 返回值
    else  // 否则分支
      v5 = (const char *)sub_422E70(379);  // v5 = 调 sub_422E70 返回值
    v21 = v5;
    v17 = COERCE_FLOAT(sub_41A5E0(fld_e2302 + 5));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v6 = (const char *)sub_422E70(*(uint32_t *)fld_e2302 + 1276);  // v6 = 调 sub_422E70 返回值
LABEL_15:  // 标签 LABEL_15（跳转合流点）
    sprintf(byte_9B0990, "%s %.1f%%%% %s", v6, v17, v21);  // 拼字符串（模板 %s %.1f%%%% %s）
    return byte_9B0990;
  }
  else  // 否则分支
  {
    v7 = (uint64_t)COERCE_FLOAT(sub_41A5E0(v4));  // crypt4byte 解密校验（·0x41A590 逆运算）
    switch ( *(uint32_t *)fld_e2302 )  // 按 *(uint32_t *)fld_e2302 分派
    {
      case 0x1D:
        if ( sub_43B5A0((void *)(fld_e2302 + 5)) < 0.0 )  // 防篡读壳（槽值转 float）
          v15 = sub_422E70(391);  // v15 = 调 sub_422E70 返回值
        else  // 否则分支
          v15 = sub_422E70(390);  // v15 = 调 sub_422E70 返回值
        v23 = v15;
        v18 = sub_422E70(*(uint32_t *)fld_e2302 + 1276);  // v18 = 调 sub_422E70 返回值
        sprintf(byte_9B0990, "%s %d%%%% %s", v18, v7 / 10, v23);  // 拼字符串（模板 %s %d%%%% %s）
        goto LABEL_35;
      case 0x21:
        if ( sub_43B5A0((void *)(fld_e2302 + 5)) < 0.0 )  // 防篡读壳（槽值转 float）
          v10 = (const char *)sub_422E70(384);  // v10 = 调 sub_422E70 返回值
        else  // 否则分支
          v10 = (const char *)sub_422E70(383);  // v10 = 调 sub_422E70 返回值
        v22 = v10;
        v11 = (const char *)sub_422E70(*(uint32_t *)fld_e2302 + 1276);  // v11 = 调 sub_422E70 返回值
        sprintf(byte_9B0990, "%s %d.%03dkg %s", v11, v7 / 1000, abs32(v7 % 1000), v22);  // 拼字符串（模板 %s %d.%03dkg %s）
        return byte_9B0990;
      case 0x22:
        v20 = sub_43B5A0((void *)(fld_e2302 + 5)) * 0.59999996;  // 防篡读壳（槽值转 float）
        v12 = (const char *)sub_422E70(385);  // v12 = 调 sub_422E70 返回值
        goto LABEL_21;
      case 0x23:
        v20 = sub_43B5A0((void *)(fld_e2302 + 5)) * 3.0;  // 防篡读壳（槽值转 float）
        v12 = (const char *)sub_422E70(386);  // v12 = 调 sub_422E70 返回值
        goto LABEL_21;
      case 0x24:
        v20 = sub_43B5A0((void *)(fld_e2302 + 5));  // 防篡读壳（槽值转 float）
        v12 = (const char *)sub_422E70(387);  // v12 = 调 sub_422E70 返回值
        goto LABEL_21;
      case 0x25:
      case 0x26:
      case 0x27:
        if ( sub_43B5A0((void *)(fld_e2302 + 5)) < 0.0 )  // 防篡读壳（槽值转 float）
          v8 = (const char *)sub_422E70(382);  // v8 = 调 sub_422E70 返回值
        else  // 否则分支
          v8 = (const char *)sub_422E70(381);  // v8 = 调 sub_422E70 返回值
        v21 = v8;
        v17 = sub_43B5A0((void *)(fld_e2302 + 5)) * 0.1;  // 防篡读壳（槽值转 float）
        v6 = (const char *)sub_422E70(*(uint32_t *)fld_e2302 + 1276);  // v6 = 调 sub_422E70 返回值
        goto LABEL_15;
      case 0x2B:
        v13 = sub_41A5E0(fld_e2302 + 24);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v14 = sub_47E720(*(uint32_t *)(fld_e2302 + 20), v13);  // v14 = 调 sub_47E720 返回值
        if ( v14 != 0 )  // 若 v14 非 0
        {
          HIDWORD(v20) = sub_41A5E0(fld_e2302 + 38);  // crypt4byte 解密校验（·0x41A590 逆运算）
          LODWORD(v20) = sub_41ACF0(v14 + 20);  // 驻留串句柄 → 字符串指针
          v12 = (const char *)sub_422E70(389);  // v12 = 调 sub_422E70 返回值
LABEL_21:  // 标签 LABEL_21（跳转合流点）
          sprintf(byte_9B0990, v12, v20);  // 拼字符串
          result = byte_9B0990;
        }
        else  // 否则分支
        {
          result = (char *)sub_422E70(388);  // result = 调 sub_422E70 返回值
        }
        break;  // 跳出循环/分支
      default:  // 默认分支
        if ( sub_43B5A0((void *)(fld_e2302 + 5)) < 0.0 )  // 防篡读壳（槽值转 float）
          v16 = sub_422E70(393);  // v16 = 调 sub_422E70 返回值
        else  // 否则分支
          v16 = sub_422E70(392);  // v16 = 调 sub_422E70 返回值
        v24 = v16;
        v19 = sub_422E70(*(uint32_t *)fld_e2302 + 1276);  // v19 = 调 sub_422E70 返回值
        sprintf(byte_9B0990, "%s %d %s", v19, v7, v24);  // 拼字符串（模板 %s %d %s）
LABEL_35:  // 标签 LABEL_35（跳转合流点）
        result = byte_9B0990;
        break;  // 跳出循环/分支
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4EBC70 sub_4EBC70 —— 与 ·0x4EB1C0 同构（纯转发）
// 编译器为不同调用约定生成的别名入口（返回尾指针）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EBC70(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：与 ·0x4EB1C0 同构（纯转发）
{
  return sub_4EB1C0(uArg1, uArg2, uArg3);  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
}



// ------------------------------------------------------------
// 0x4EBC90 sub_4EBC90 —— ·0x4EB800 批量构造 + 返回尾指针（pArg1 + 8×nArg2）
// 32 字节条目步距，返回值供调用方继续续写
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EBC90(uint32_t *pArg1, int nArg2, uint32_t *uArg3)  // 实现：·0x4EB800 批量构造 + 返回尾指针（pArg1 + 8×nArg2）
{
  sub_4EB800(pArg1, nArg2, uArg3);  // 32 字节条目批量构造（nArg2 个，源自 pArg3）
  return &pArg1[8 * nArg2];
}



// ------------------------------------------------------------
// 0x4EBCC0 sub_4EBCC0 —— 属性条目拷贝构造（80 字节条目）
// *this = *pArg2；+4 复制字节；·sub_4EB070(+5) cfloat；·sub_4EB0D0(+20) clong 组；
// +52 字符串 ·sub_4014D0 赋值 + +72/+76 容量/长度复位（15/0）
// ------------------------------------------------------------
char */*thiscall*/ sub_4EBCC0(char *this, int pArg2)  // 实现：属性条目拷贝构造（80 字节条目）
{
  *(uint32_t *)this = *(uint32_t *)pArg2;
  *(this + 4) = *(uint8_t *)(pArg2 + 4);  // this+16〔nChannelTypeSel(推断)〕
  sub_4EB070(this + 5, pArg2 + 5);  // cfloat 构造（vftable + 防篡读拷贝初值）
  sub_4EB0D0((uint32_t *)this + 5, (uint32_t *)(pArg2 + 20));  // 条目拷贝（*this = *pArg2 + ·sub_46B080 处理 +4/+18 引用计数）
  *((uint32_t *)this + 19) = 15;  // this+76〔pBtnActionE〕
  *((uint32_t *)this + 18) = 0;  // this[18] = 0
  *(this + 56) = 0;  // this+224〔nSnapDst224(推断)〕
  sub_4014D0((size_t *)this + 13, (size_t *)(pArg2 + 52), 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  return this;
}



// ------------------------------------------------------------
// 0x4EBD50 sub_4EBD50 —— 属性条目默认构造（清零 + 空串 + +20 = 4）
// *pArg1 = 0；+4 = 0；·sub_41A590(+5, 0)；·sub_4015C0(+52, 空串)；+20 = 4；+24/+38 clong 置 0
// ------------------------------------------------------------
int /*fastcall*/ sub_4EBD50(int pArg1, int nArg2)  // 实现：属性条目默认构造（清零 + 空串 + +20 = 4）
{
  int v3; // edx
  int v4; // edx

  *(uint32_t *)pArg1 = 0;  // *pArg1 = 0
  *(uint8_t *)(pArg1 + 4) = 0;  // pArg1+4〔宿主对象〕
  sub_41A590(pArg1 + 5, nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_4015C0((size_t *)(pArg1 + 52), szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(pArg1 + 20) = 4;  // pArg1+20〔nPage(推断)〕
  sub_41A590(pArg1 + 24, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return sub_41A590(pArg1 + 38, v4, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x4EBDB0 sub_4EBDB0 —— 属性条目按 id 分派应用（1..0x29 全表）
// 取 ·this+932(word 233) 索引的 80 字节条目，v8 = 条目 +5（防篡读）；
// id 1..0x1F / 0x21 / 0x22..0x24 / 0x28 → ·sub_4AED60(pArg3 + 固定偏移, v8)（id 1 另有 ·sub_433F60×值 → ·sub_4450B0 计数）；
// id 0x25..0x27（另一使能向）→ ×0.001 写 +830/+858/+886；id 0x29 与 default → ·0x4EBD50 重置或 ·sub_4450B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4EBDB0(uint32_t *this, int nArg2, int pArg3)  // 实现：属性条目按 id 分派应用（1..0x29 全表）
{
  unsigned int pThis_E9; // esi
  unsigned int v5; // ebx
  int pNameBuf; // eax
  int fld_e2302; // esi
  float v8; // eax
  int v9; // edx
  double v10; // st7
  float v11; // [esp+0h] [ebp-14h]
  float v12; // [esp+0h] [ebp-14h]
  float v13; // [esp+0h] [ebp-14h]

  pThis_E9 = (unsigned int)(this + 233);
  if ( sub_41A5E0((unsigned int)(this + 233)) != -1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v5 = sub_41A5E0(pThis_E9);  // crypt4byte 解密校验（·0x41A590 逆运算）
    pNameBuf = *(this + 230);  // this+920〔pNameBuf〕
    if ( pNameBuf != 0 && v5 < (*(this + 231) - pNameBuf) / 80 )  // 若 fld_e230 != 0
    {
      fld_e2302 = *(this + 230) + 80 * sub_41A5E0(pThis_E9);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v8 = COERCE_FLOAT(sub_41A5E0(fld_e2302 + 5));  // crypt4byte 解密校验（·0x41A590 逆运算）
      switch ( *(uint32_t *)fld_e2302 )  // 按 *(uint32_t *)fld_e2302 分派
      {
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
          {
            sub_4AED60((void *)(pArg3 + 18), v8);  // pArg3+18〔bDragChild(推断)〕
          }
          else  // 否则分支
          {
            v10 = sub_433F60(nArg2, 2) * v8;  // v10 = 调 sub_433F60 返回值
            sub_4450B0((uint64_t)v10);  // 计数器加值
          }
          return;
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 46), v8);
          return;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 74), v8);  // pArg3+74〔bResetB74(推断)〕
          return;
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 102), v8);  // pArg3+102〔bFlashClearB(推断)〕
          return;
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 130), v8);
          return;
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 158), v8);
          return;
        case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_94;
          goto LABEL_93;
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0xA:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0xB:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 228), v8);  // pArg3+228〔nSnapDst228(推断)〕
          break;  // 跳出循环/分支
        case 0xC:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 242), v8);
          break;  // 跳出循环/分支
        case 0xD:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 256), v8);  // pArg3+256〔bParamSlotC(推断)〕
          break;  // 跳出循环/分支
        case 0xE:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 270), v8);
          break;  // 跳出循环/分支
        case 0x10:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 508), v8);  // pArg3+508〔uPetFlag(推断)〕
          break;  // 跳出循环/分支
        case 0x11:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 522), v8);
          break;  // 跳出循环/分支
        case 0x12:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 536), v8);  // pArg3+536〔nCountdownEnd(推断)〕
          break;  // 跳出循环/分支
        case 0x13:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 550), v8);
          break;  // 跳出循环/分支
        case 0x14:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 564), v8);
          break;  // 跳出循环/分支
        case 0x15:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 578), v8);
          break;  // 跳出循环/分支
        case 0x16:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 592), v8);
          break;  // 跳出循环/分支
        case 0x17:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 606), v8);
          break;  // 跳出循环/分支
        case 0x18:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 620), v8);
          break;  // 跳出循环/分支
        case 0x19:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 634), v8);
          break;  // 跳出循环/分支
        case 0x1A:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 648), v8);  // pArg3+648〔uMonFlagBits(推断)〕
          break;  // 跳出循环/分支
        case 0x1B:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 662), v8);
          break;  // 跳出循环/分支
        case 0x1C:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 676), v8);  // pArg3+676〔nResetFlag676(推断)〕
          break;  // 跳出循环/分支
        case 0x1D:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 690), v8);
          break;  // 跳出循环/分支
        case 0x1E:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 704), v8);  // pArg3+704〔nSnapshot704〕
          break;  // 跳出循环/分支
        case 0x1F:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 718), v8);
          break;  // 跳出循环/分支
        case 0x21:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 746), v8);
          break;  // 跳出循环/分支
        case 0x22:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0x23:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          goto LABEL_94;
        case 0x25:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_94;
          v11 = v8 * 0.001;
          sub_4AED60((void *)(pArg3 + 830), v11);
          break;  // 跳出循环/分支
        case 0x26:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_94;
          v12 = v8 * 0.001;
          sub_4AED60((void *)(pArg3 + 858), v12);  // pArg3+858〔fSpeed858(推断)〕
          break;  // 跳出循环/分支
        case 0x27:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_94;
          v13 = v8 * 0.001;
          sub_4AED60((void *)(pArg3 + 886), v13);
          break;  // 跳出循环/分支
        case 0x28:
          if ( *(uint8_t *)(fld_e2302 + 4) == 0 )
            goto LABEL_93;
          sub_4AED60((void *)(pArg3 + 914), v8);
          break;  // 跳出循环/分支
        case 0x29:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
LABEL_94:  // 标签 LABEL_94（跳转合流点）
            sub_4EBD50(fld_e2302, v9);  // 属性条目默认构造（清零 + 空串 + +20 = 4）
          else  // 否则分支
LABEL_93:  // 标签 LABEL_93（跳转合流点）
            sub_4450B0((uint64_t)v8);  // 计数器加值
          break;  // 跳出循环/分支
        default:  // 默认分支
          return;
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4EC7C0 sub_4EC7C0 —— 属性块整体组装到 pArg2（本体 + 附加物两遍 + 全局系数）
// vt+200 宿主非空 → 取宿主 vt+1084(·this+148) → vt+132(pArg2) 直通；否则两遍（本体 ·pThis+212 / ·pThis+1268）；
// 每遍按 v6 的槽位表（+14..+294、+308 起 4×14 双写、+378 起 16×14（·sub_497040==17 跳过）、+616..+756、+808/+822/+836、+851 起 2×14）
// 加算（部分经 ·sub_433F60 场景系数）→ 末尾 ·pThis+64 × flt_791E20 加 +984、×flt_9B06D0×flt_791E20×0.001 减 +816 → 尾调 ·0x4EBDB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4EC7C0(int *this, int pArg2)  // 实现：属性块整体组装到 pArg2（本体 + 附加物两遍 + 全局系数）
{
  int *pThis; // ebx
  int result; // eax
  int pObj; // esi
  int *v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  unsigned int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  bool v35; // zf
  unsigned int v36; // ebx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // edx
  bool v41; // cc
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // edx
  int v49; // eax
  int v50; // edx
  int v51; // eax
  int v52; // edx
  float v53; // eax
  int v54; // edx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // [esp+8h] [ebp-10h]
  int v60; // [esp+8h] [ebp-10h]
  int v61; // [esp+8h] [ebp-10h]
  int v62; // [esp+8h] [ebp-10h]
  float v63; // [esp+8h] [ebp-10h]
  int i; // [esp+10h] [ebp-8h]
  float v66; // [esp+14h] [ebp-4h]
  float v67; // [esp+14h] [ebp-4h]
  int v68; // [esp+14h] [ebp-4h]
  unsigned int v69; // [esp+14h] [ebp-4h]
  int v70; // [esp+20h] [ebp+8h]
  int v71; // [esp+20h] [ebp+8h]
  int v72; // [esp+20h] [ebp+8h]
  int v73; // [esp+20h] [ebp+8h]
  int v74; // [esp+20h] [ebp+8h]
  int v75; // [esp+20h] [ebp+8h]
  int v76; // [esp+20h] [ebp+8h]
  int v77; // [esp+20h] [ebp+8h]
  int v78; // [esp+20h] [ebp+8h]
  int v79; // [esp+20h] [ebp+8h]
  int v80; // [esp+20h] [ebp+8h]
  int v81; // [esp+20h] [ebp+8h]
  int v82; // [esp+20h] [ebp+8h]
  int v83; // [esp+20h] [ebp+8h]
  int v84; // [esp+20h] [ebp+8h]
  int v85; // [esp+20h] [ebp+8h]
  int v86; // [esp+20h] [ebp+8h]
  unsigned int v87; // [esp+20h] [ebp+8h]
  int v88; // [esp+20h] [ebp+8h]
  int v89; // [esp+20h] [ebp+8h]
  int v90; // [esp+20h] [ebp+8h]
  int v91; // [esp+20h] [ebp+8h]
  float v92; // [esp+20h] [ebp+8h]
  int v93; // [esp+20h] [ebp+8h]
  int v94; // [esp+20h] [ebp+8h]
  int v95; // [esp+20h] [ebp+8h]
  int v96; // [esp+20h] [ebp+8h]
  int v97; // [esp+20h] [ebp+8h]
  int v98; // [esp+20h] [ebp+8h]
  int v99; // [esp+20h] [ebp+8h]
  int v100; // [esp+20h] [ebp+8h]
  int v101; // [esp+20h] [ebp+8h]
  int v102; // [esp+20h] [ebp+8h]
  int v103; // [esp+20h] [ebp+8h]
  int v104; // [esp+20h] [ebp+8h]
  int v105; // [esp+20h] [ebp+8h]
  int v106; // [esp+20h] [ebp+8h]
  int v107; // [esp+20h] [ebp+8h]

  pThis = this;
  if ( (*(uint8_t (/*fastcall*/ **)(int *))(*this + 200))(this) != 0 )  // 调虚槽 +200：取动画对象
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis[321] + 40))(pThis[321], 273);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis[321] + 1084))(pThis[321], pThis[37]);
      pObj = result;
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 200))(result);  // 调虚槽 +200：取动画对象
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 132))(pObj, pArg2);  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽…
      }
    }
  }
  else  // 否则分支
  {
    for ( i = 0; i < 2; ++i )  // 循环：i 从 0 递增到 2
    {
      if ( i != 0 )  // 若 i 非 0
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pThis + 224))(pThis) == 0 )  // 调虚槽 +224：标志读 +172
          break;  // 跳出循环/分支
        v6 = (int *)pThis[317];
      }
      else  // 否则分支
      {
        v6 = pThis + 53;
      }
      v70 = sub_41A5E0((unsigned int)v6 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v7 = (*(int (/*thiscall*/ **)(int *))(*pThis + 212))(pThis);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      v71 = (uint64_t)(sub_433F60(v7, 2) * (double)v70);
      v8 = sub_41A5E0(pArg2 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 4, v9, v71 + v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v72 = sub_41A5E0((unsigned int)(v6 + 7));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v10 = sub_41A5E0(pArg2 + 32);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 32, v72, v72 + v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v73 = sub_41A5E0((unsigned int)v6 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v11 = sub_41A5E0(pArg2 + 60);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 60, v12, v73 + v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v74 = sub_41A5E0((unsigned int)(v6 + 14));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v13 = sub_41A5E0(pArg2 + 88);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 88, v74, v74 + v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v75 = sub_41A5E0((unsigned int)v6 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v14 = sub_41A5E0(pArg2 + 116);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 116, v15, v75 + v14);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v76 = sub_41A5E0((unsigned int)v6 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v16 = sub_41A5E0(pArg2 + 144);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 144, v76, v76 + v16);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v77 = sub_41A5E0((unsigned int)(v6 + 28));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v17 = sub_41A5E0(pArg2 + 1012);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1012, v18, v77 + v17);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v78 = sub_41A5E0((unsigned int)v6 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v19 = sub_41A5E0(pArg2 + 1040);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1040, v78, v78 + v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v79 = sub_41A5E0((unsigned int)(v6 + 35));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v20 = sub_41A5E0(pArg2 + 1068);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1068, v21, v79 + v20);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v80 = sub_41A5E0((unsigned int)v6 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v22 = sub_41A5E0(pArg2 + 1096);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1096, v80, v80 + v22);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v81 = sub_41A5E0((unsigned int)(v6 + 56));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v23 = sub_41A5E0(pArg2 + 1124);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1124, v24, v81 + v23);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v82 = sub_41A5E0((unsigned int)v6 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v25 = sub_41A5E0(pArg2 + 1138);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1138, v82, v82 + v25);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v66 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 63)));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v83 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1152)) + v66;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1152, v26, v83);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v84 = sub_41A5E0((unsigned int)v6 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v27 = sub_41A5E0(pArg2 + 1166);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1166, v28, v84 + v27);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v85 = sub_41A5E0((unsigned int)(v6 + 70));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v29 = sub_41A5E0(pArg2 + 1180);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1180, v85, v85 + v29);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v67 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 294));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v86 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1194)) + v67;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1194, v30, v86);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v31 = pArg2 + 172;
      v87 = (unsigned int)(v6 + 77);
      v68 = 4;
      do  // do-while 循环体起点
      {
        v59 = sub_41A5E0(v87);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v32 = sub_41A5E0(v31);  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590(v31, v59, v59 + v32);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        v60 = sub_41A5E0((unsigned int)(v6 + 91));  // crypt4byte 解密校验（·0x41A590 逆运算）
        v33 = sub_41A5E0(v31);  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590(v31, v34, v60 + v33);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        v31 += 14;
        v35 = v68 == 1;
        v87 += 14;
        --v68;
      }
      while ( !v35 );  // 条件循环
      v88 = 0;
      v36 = pArg2 + 284;
      v69 = (unsigned int)v6 + 378;
      do  // do-while 循环体起点
      {
        v61 = sub_41A5E0(v69);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v37 = sub_41A5E0(v36);  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590(v36, v38, v61 + v37);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        if ( sub_497040(v88) != 17 )  // 状态号映射表（12 直通、14→15、15→16，其余→17）
        {
          v62 = sub_41A5E0((unsigned int)v6 + 602);  // crypt4byte 解密校验（·0x41A590 逆运算）
          v39 = sub_41A5E0(v36);  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590(v36, v40, v62 + v39);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        }
        v36 += 14;
        v41 = ++v88 < 16;
        v69 += 14;
      }
      while ( v41 );  // 条件循环
      v89 = sub_41A5E0((unsigned int)(v6 + 154));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v42 = sub_41A5E0(pArg2 + 732);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 732, v89, v89 + v42);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v90 = sub_41A5E0((unsigned int)v6 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v43 = sub_41A5E0(pArg2 + 760);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 760, v44, v90 + v43);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v91 = sub_41A5E0((unsigned int)(v6 + 161));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v45 = sub_41A5E0(pArg2 + 788);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 788, v91, v91 + v45);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v92 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 658));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v93 = v92 * 0.0099999998 + COERCE_FLOAT(sub_41A5E0(pArg2 + 802));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 802, v46, v93);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v94 = sub_41A5E0((unsigned int)(v6 + 168));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v95 = (double)v94 * 0.001 + COERCE_FLOAT(sub_41A5E0(pArg2 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 830, v47, v95);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v96 = sub_41A5E0((unsigned int)v6 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v97 = (double)v96 * 0.001 + COERCE_FLOAT(sub_41A5E0(pArg2 + 858));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 858, v97, v97);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      if ( *(this + 37) != 8 )  // this+148〔fAdd148(推断)〕
      {
        v98 = sub_41A5E0((unsigned int)v6 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
        *(float *)&v99 = (double)v98 * 0.001 + COERCE_FLOAT(sub_41A5E0(pArg2 + 1292));  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590(pArg2 + 1292, v48, v99);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      }
      v100 = sub_41A5E0((unsigned int)(v6 + 175));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v101 = (double)v100 * 0.001 + COERCE_FLOAT(sub_41A5E0(pArg2 + 886));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 886, v101, v101);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v102 = sub_41A5E0((unsigned int)v6 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v49 = sub_41A5E0(pArg2 + 900);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 900, v50, v102 + v49);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v103 = sub_41A5E0((unsigned int)(v6 + 182));  // crypt4byte 解密校验（·0x41A590 逆运算）
      v51 = sub_41A5E0(pArg2 + 928);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 928, v103, v103 + v51);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v63 = COERCE_FLOAT(sub_41A5E0((unsigned int)v6 + 742));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v104 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1208)) + v63;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1208, v52, v104);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v53 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v6 + 189)));  // crypt4byte 解密校验（·0x41A590 逆运算）
      *(float *)&v105 = COERCE_FLOAT(sub_41A5E0(pArg2 + 1222)) + v53;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1222, v54, v105);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      pThis = this;
    }
    v106 = (uint64_t)((double)pThis[16] * flt_791E20);
    v55 = sub_41A5E0(pArg2 + 984);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 984, v106, v106 + v55);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v107 = (uint64_t)((double)pThis[16] * flt_9B06D0 * flt_791E20 * 0.001);
    v56 = sub_41A5E0(pArg2 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg2 + 816, v57, v56 - v107);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v58 = (*(int (/*thiscall*/ **)(int *))(*pThis + 212))(pThis);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    return sub_4EBDB0(v58, pArg2);  // 属性条目按 id 分派应用（1..0x29 全表）
  }
  return result;
}


// ------------------------------------------------------------
// 0x4ECED0 sub_4ECED0 —— 生成 +%d %s 文本到静态 std::string ·dword_9B0A90（atexit 注册）
// vt+47 → 值 +2 与 ·this+16 字符串拼接（值 0 时只写名称），结果写 ·dword_9B0A90
// ------------------------------------------------------------
void **/*thiscall*/ sub_4ECED0(unsigned int **this)  // 实现：生成 +%d %s 文本到静态 std::string ·dword_9B0A90（atexit 注册）
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  const char *pThis_4; // eax
  CHAR *pThis_42; // eax
  void **result; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (dword_9B0AAC & 1) == 0 )  // 若 dword_9B0AAC 位 1 清零
  {
    dword_9B0AAC |= 1u;
    dword_9B0AA8 = 15;
    dword_9B0AA4 = 0;
    LOBYTE(dword_9B0A94) = 0;
    atexit(sub_6BFBA0);
  }
  v2 = ((int (/*thiscall*/ *)(unsigned int **))(*this)[47])(this);
  if ( sub_41A5E0(v2 + 4) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v3 = ((int (/*thiscall*/ *)(unsigned int **))(*this)[47])(this);
    v4 = sub_41A5E0(v3 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_4 = sub_41ACF0(this + 4);  // 驻留串句柄 → 字符串指针
    sprintf(Buffer, "+%d %s", v4, pThis_4);  // 拼字符串（模板 +%d %s）
    sub_4015C0(&dword_9B0A90, Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  else  // 否则分支
  {
    pThis_42 = (CHAR *)sub_41ACF0(this + 4);  // 驻留串句柄 → 字符串指针
    sub_4015C0(&dword_9B0A90, pThis_42, strlen(pThis_42));  // 【std::string构造赋值】
  }
  result = (void **)dword_9B0A94;
  if ( (unsigned int)dword_9B0AA8 < 0x10 )
    return &dword_9B0A94;
  return result;
}



// ------------------------------------------------------------
// 0x4ECFE0 sub_4ECFE0 —— 80 字节条目区间拷贝（前向，含防篡拷贝 + 字符串赋值）
// 每步：*dst = *src、+4 字节、防篡拷贝两对、字符串 ·sub_4014D0(+52 区)；dst 步距 80 字节
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4ECFE0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：80 字节条目区间拷贝（前向，含防篡拷贝 + 字符串赋值）
{
  uint32_t *uArg12; // ebx
  unsigned int v4; // esi
  unsigned int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx

  uArg12 = uArg1;
  if ( uArg1 != uArg2 )  // 若 uArg1 != uArg2
  {
    v4 = (unsigned int)uArg3 + 38;
    v5 = (unsigned int)uArg1 + 38;
    do  // do-while 循环体起点
    {
      *uArg3 = *uArg12;
      *(uint8_t *)(v4 - 34) = *(uint8_t *)(v5 - 34);
      v6 = sub_41A5E0(v5 - 33);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4 - 33, v7, v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      *(uint32_t *)(v4 - 18) = *(uint32_t *)(v5 - 18);
      v8 = sub_41A5E0(v5 - 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4 - 14, v9, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v10 = sub_41A5E0(v5);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(v4, v11, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      sub_4014D0((size_t *)(v4 + 14), (size_t *)(v5 + 14), 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      uArg12 += 20;
      v4 += 80;
      v5 += 80;
      uArg3 += 20;
    }
    while ( uArg12 != uArg2 );  // 条件循环
  }
  return uArg3;
}



// ------------------------------------------------------------
// 0x4ED080 sub_4ED080 —— 32 字节条目 vector 区间插入（容量三路 + 析构收尾）
// 溢出保护 ·sub_434730（0x7FFFFFF 上限）；容量足：原地 ·sub_4EB1C0/·sub_4EB1A0/·sub_4EB150 搬移填充；
// 不足：新容量 1.5× → new + ·sub_4EB1C0 三段拷贝 + ·sub_434100 析构旧块 + free；尾 ·sub_41A580×2 析构临时
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED080(int this, int pArg2, unsigned int uArg3, int nArg4)  // 实现：32 字节条目 vector 区间插入（容量三路 + 析构收尾）
{
  int fld_4; // edx
  int fld_8; // ecx
  unsigned int fld_C; // eax
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_87; // ecx
  int fld_88; // eax
  char *pMem; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v16; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v19; // edi
  int v20; // eax
  int fld_42; // [esp-18h] [ebp-5Ch]
  void *Block2; // [esp-18h] [ebp-5Ch]
  int fld_85; // [esp-Ch] [ebp-50h]
  unsigned int fld_84; // [esp-8h] [ebp-4Ch]
  int v26; // [esp+0h] [ebp-44h] BYREF
  char v27[4]; // [esp+Ch] [ebp-38h] BYREF
  char v28[14]; // [esp+10h] [ebp-34h] BYREF
  char v29[14]; // [esp+1Eh] [ebp-26h] BYREF
  void *Block; // [esp+2Ch] [ebp-18h]
  int pThis; // [esp+30h] [ebp-14h]
  int *v32; // [esp+34h] [ebp-10h]
  int v33; // [esp+40h] [ebp-4h]
  int v34; // [esp+50h] [ebp+Ch]
  int v35; // [esp+54h] [ebp+10h]

  v32 = &v26;
  pThis = this;
  sub_4EB0D0(nArg4);  // 条目拷贝（*this = *pArg2 + ·sub_46B080 处理 +4/+18 引用计数）
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  fld_8 = 0;
  v33 = 0;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 5;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
    if ( 0x7FFFFFF - fld_8 < uArg3 )
      sub_434730(this);  // vector 超长抛 length_error
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
      Block = fld_83;
      if ( (int)&fld_83[-pArg2] >> 5 >= uArg3 )
      {
        v19 = &fld_83[-32 * uArg3];
        v20 = sub_4EB1C0(v19, fld_83, fld_83);  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_4EB1A0(pArg2, v19, Block2);  // 与 ·0x4EB010 同构（纯转发）
        sub_4EB150(pArg2, pArg2 + 32 * uArg3, v27);  // 32 字节条目区间填充（同值 pArg3，前向）
      }
      else  // 否则分支
      {
        sub_4EB1C0(pArg2, fld_83, pArg2 + 32 * uArg3);  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 5);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = 读 this+8
        LOBYTE(v33) = 3;
        sub_4EBC90(fld_85, fld_84, v27);  // ·0x4EB800 批量构造 + 返回尾指针（pArg1 + 8×nArg2）
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        v33 = 0;
        sub_4EB150(pArg2, fld_86 - 32 * uArg3, v27);  // 32 字节条目区间填充（同值 pArg3，前向）
      }
    }
    else  // 否则分支
    {
      if ( 0x7FFFFFF - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else  // 否则分支
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_88 = 0;
        v10 = uArg3 + fld_88;
      }
      v35 = 32 * v10;
      pMem = (char *)operator new(32 * v10);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
      Block = pMem;
      LOBYTE(v33) = 1;
      v34 = sub_4EB1C0(fld_42, pArg2, pMem);  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
      sub_4EB800(v34, uArg3, v27);  // 32 字节条目批量构造（nArg2 个，源自 pArg3）
      sub_4EB1C0(pArg2, *(uint32_t *)(this + 8), 32 * uArg3 + v34);  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      v33 = 0;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_89 = 0;
      v16 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
      {
        sub_434100(fld_43, *(uint32_t *)(this + 8));  // 32B 条目区间析构
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      }
      *(uint32_t *)(this + 12) = &pMem[v35];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[32 * v16];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
  v33 = 5;
  sub_41A580(v29);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  v33 = -1;
  return sub_41A580(v28);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
}


// ------------------------------------------------------------
// 0x4ED330 sub_4ED330 —— int 向量区间构造
// int 元素向量区间构造：源 (+4/+8) 元素数先经 ·sub_42AA50 缓冲申请，再由 ·sub_497E70 逐元素拷入目标缓冲（+4 起），尾指针写 +8 —— 供 ·0x4ED6A0（属性条目头部拷构）对 +36/+52 两个内置 int 向量调用，返回自身。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ED330(uint32_t *this, int pArg2)  // 实现：int 向量区间构造
{
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )  // 若 v3 非 0
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v4 = 0;
  if ( (uint8_t)sub_42AA50(v4) != 0 )  // 向量缓冲分配
  {
    fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    v7 = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);  // uint32 区间逐元素拷贝
  }
  return this;
}



// ------------------------------------------------------------
// 0x4ED3D0 sub_4ED3D0 —— 80B 条目区间拷构转发
// 80 字节条目区间拷贝的薄转发 → ·sub_4ECFE0（前向拷贝，含字符串成员），供 ·0x4EE9E0 在两容量路径统一调用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4ED3D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：80B 条目区间拷构转发
{
  return sub_4ECFE0(uArg1, uArg2, uArg3);  // 80 字节条目区间拷贝（前向，含防篡拷贝 + 字符串赋值）
}



// ------------------------------------------------------------
// 0x4ED3F0 sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
// int 元素向量拷贝赋值（4 字节元素全容量路径）：自赋值早退；空源释放置空；容量足够 memcpy_0 覆盖并修正尾指针；
// 容量不足先释放旧缓冲，再 ·sub_42AA50 申请缓冲后经 ·sub_55E7F0 写入（返回尾指针），否则 ·sub_433A30 dword 区间搬移 + ·sub_55E7F0 补尾。
// 124 字节属性行内 +40/+56 两个 int 向量（以及 ·0x4EE580 的 +24/+313 向量）的赋值原语。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED3F0(int this, int pArg2)  // 实现：int 向量拷贝赋值（全容量路径）
{
  int v3; // ecx
  unsigned int v4; // edx
  void *fld_4; // ecx
  unsigned int fld_8; // ebx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  int fld_82; // eax
  void *v12; // ebx
  int v13; // ecx
  int v14; // eax

  if ( this == pArg2 )  // 若 this == pArg2
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2) == 0 )  // 若 v3 == 0
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;
  }
  fld_4 = *(void **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( v4 <= fld_8 )  // 若 v4 <= fld_8
  {
    memcpy_0(fld_4, *(const void **)(pArg2 + 4), 4 * ((*(uint32_t *)(pArg2 + 8) - *(uint32_t *)(pArg2 + 4)) >> 2));  // pArg2+8〔nSkillRec8(推断)〕
    v8 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v8 != 0 )  // 若 v8 非 0
      fld_42 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 2);  // fld_42 = 读 this+4
    else  // 否则分支
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;
  if ( v4 > fld_C )  // 若 v4 > fld_C
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v13 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v13 != 0 )  // 若 v13 非 0
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
    else  // 否则分支
      v14 = 0;
    if ( (uint8_t)sub_42AA50(v14) != 0 )  // 向量缓冲分配
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));  // 商城状态（10 行）
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_82 = 0;
  v12 = (void *)(*(uint32_t *)(pArg2 + 4) + 4 * fld_82);  // pArg2+4〔宿主对象〕
  sub_433A30(*(void **)(pArg2 + 4), (int)v12, *(void **)(this + 4));  // dword 区间拷贝
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8));  // 商城状态（10 行）
  return this;
}



// ------------------------------------------------------------
// 0x4ED540 sub_4ED540 —— 32B 条目向量拷贝赋值（全容量路径）
// 32 字节条目向量拷贝赋值（全容量路径）：空源 ·sub_434140 销毁重挂；同位覆盖走 ·sub_4EAFB0 + ·sub_434100 析构余量；
// 扩容 ·sub_434A40 预留 + ·sub_4EBC70 拷构；中段路径 ·sub_4EB130 前段拷构 + ·sub_4EB1C0 移动构造补尾。
// 服务属性行内 884 起两个 32B 子向量（·0x4ED7C0 与 ·0x4EEBF0 调用）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4ED540(int *this, int *pDwArg2)  // 实现：32B 条目向量拷贝赋值（全容量路径）
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *fld_e1; // ecx
  unsigned int fld_e2; // edx
  uint32_t *v8; // eax
  int v9; // eax
  int fld_e12; // edi
  unsigned int fld_e3; // edx
  int fld_e22; // eax
  uint32_t *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == pDwArg2 )  // 若 this == pDwArg2
    return this;
  v3 = (uint32_t *)pDwArg2[1];
  if ( v3 == nullptr || (v4 = (pDwArg2[2] - (int)v3) >> 5) == 0 )  // 若 v3 == nullptr
  {
    sub_434140(this);  // 条目向量销毁（32B 步进）
    return this;
  }
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    fld_e2 = (*(this + 2) - (int)fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;
  if ( v4 <= fld_e2 )  // 若 v4 <= fld_e2
  {
    v8 = sub_4EAFB0(v3, (uint32_t *)pDwArg2[2], fld_e1);  // 32 字节条目区间前向拷贝（含防篡拷贝 +4/+18）
    sub_434100(v8, *(this + 2));  // 32B 条目区间析构
    v9 = pDwArg2[1];  // v9 = 取 pDwArg2[1]
    if ( v9 != 0 )  // 若 v9 非 0
      fld_e12 = *(this + 1) + 32 * ((pDwArg2[2] - v9) >> 5);  // this+4〔宿主对象〕
    else  // 否则分支
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
    *(this + 2) = fld_e12;  // this+8〔nSkillRec8(推断)〕
    return this;
  }
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    fld_e3 = (*(this + 3) - (int)fld_e1) >> 5;  // this+12〔nSkillRec12(推断)〕
  else  // 否则分支
    fld_e3 = 0;
  if ( v4 > fld_e3 )  // 若 v4 > fld_e3
  {
    if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    {
      sub_434100(fld_e1, *(this + 2));  // 32B 条目区间析构
      j__free((void *)*(this + 1));  // this+4〔宿主对象〕
    }
    v14 = pDwArg2[1];  // v14 = 取 pDwArg2[1]
    if ( v14 != 0 )  // 若 v14 非 0
      v15 = (pDwArg2[2] - v14) >> 5;
    else  // 否则分支
      v15 = 0;
    if ( (uint8_t)sub_434A40(v15) != 0 )  // 32 字节元素向量预留
      *(this + 2) = (int)sub_4EBC70((uint32_t *)pDwArg2[1], (uint32_t *)pDwArg2[2], (uint32_t *)*(this + 1));  // 与 ·0x4EB1C0 同构（纯转发）
    return this;
  }
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    fld_e22 = (*(this + 2) - (int)fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e22 = 0;
  v13 = (uint32_t *)(pDwArg2[1] + 32 * fld_e22);
  sub_4EB130((uint32_t *)pDwArg2[1], v13, (uint32_t *)*(this + 1));  // 与 ·0x4EAFB0 同构（纯转发）
  *(this + 2) = (int)sub_4EB1C0(v13, (uint32_t *)pDwArg2[2], (uint32_t *)*(this + 2));  // 32 字节条目区间移动构造（含 clong vftable 赋值 + 防篡拷贝）
  return this;
}



// ------------------------------------------------------------
// 0x4ED6A0 sub_4ED6A0 —— 属性条目头部拷构（64 字节）
// 属性条目头部拷构（64 字节）：9 个 int 标量逐 dword 直拷 + +36/+52 两处 int 向量经 ·sub_4ED330 —— 124 字节行族（·sub_4EE190/4EE250/4EF390/4EF450）的公共首段，返回自身。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4ED6A0(uint32_t *this, uint32_t *pArg2)  // 实现：属性条目头部拷构（64 字节）
{
  *this = *pArg2;
  *(this + 1) = pArg2[1];  // this+4〔宿主对象〕
  *(this + 2) = pArg2[2];  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = pArg2[3];  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = pArg2[4];  // this+16〔nChannelTypeSel(推断)〕
  *(this + 5) = pArg2[5];  // this+20〔nPage(推断)〕
  *(this + 6) = pArg2[6];  // this+24〔nPageMax(推断)〕
  *(this + 7) = pArg2[7];  // this+28〔pPanelVec(推断)〕
  *(this + 8) = pArg2[8];  // this+32〔nHeight(推断)〕
  sub_4ED330(this + 9, (int)(pArg2 + 9));  // int 向量区间构造
  sub_4ED330(this + 13, (int)(pArg2 + 13));  // int 向量区间构造
  return this;
}



// ------------------------------------------------------------
// 0x4ED730 sub_4ED730 —— 80B 条目区间拷构
// 80 字节属性条目区间拷贝构造：逐条 ·sub_4EBCC0（80 字节整条目拷构），步进 80，返回尾指针 —— 供 ·0x4EE9E0 与 ·sub_4EE4A0 使用。
// ------------------------------------------------------------
char */*cdecl*/ sub_4ED730(int nArg1, int nArg2, char *pszArg3)  // 实现：80B 条目区间拷构
{
  char *pszArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg32 = pszArg3;
  v6[4] = v6;
  v6[3] = pszArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 条件循环
  {
    LOBYTE(v7) = 1;
    if ( pszArg32 != nullptr )  // 若 pszArg32 有效（非空）
      sub_4EBCC0(pszArg32, nArg1);  // 属性条目拷贝构造（80 字节条目）
    pszArg32 += 80;
    LOBYTE(v7) = 0;
    nArg1 += 80;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x4ED7C0 sub_4ED7C0 —— 属性行生成主体（随机抖动 + 档位判定）
// ★ 属性行生成主体（537 行）：把源行 pArg4 逐字段拷贝到目标行 pArg3（·sub_41A5E0 读 / ·sub_41A590 写），14 字节字段族（4 + 16 槽循环）经 ·sub_4E9CF0 按档位方差随机（±10 / ±20/5 / ±5/8 三档），+560 槽直拷、+602 字段先乘 0.2 封顶 5 再 ·sub_4D33A0 取随机走 ·sub_4049C0 抖动；
// 884 起两个 32B 子向量 ·sub_4ED540、+916 起 80B 子向量 ·sub_4EE9E0 深拷贝；
// switch(nArg2) 依 +112/+140/+126/+154 字段组合算行首档位 v108（0..5【推断：品级/段位判定】）；nArg6 非 0 时 ·sub_4F9F40 取强化档 nArg6-1 数值叠加进对位字段及 +168/+196/+182/+210 绝对槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_4ED7C0(int *this, int nArg2, unsigned int pArg3, int pArg4, int nArg5, int nArg6)  // 实现：属性行生成主体（随机抖动 + 档位判定）
{
  int v7; // eax
  int v8; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  int v35; // eax
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // edx
  unsigned int v50; // ebx
  int v51; // eax
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // eax
  int v56; // edx
  int v57; // ebx
  int v58; // eax
  int v59; // edx
  int v60; // ebx
  uint64_t v61; // rax
  unsigned int v62; // eax
  uint64_t v63; // rax
  int v64; // ebx
  unsigned int v65; // eax
  int v66; // eax
  int v67; // edx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // edx
  int v74; // eax
  int v75; // edx
  int v76; // eax
  int v77; // edx
  int v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v86; // eax
  int v87; // edx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int v91; // edx
  int v92; // eax
  int v93; // edx
  int v94; // eax
  int v95; // edx
  int v96; // eax
  int v97; // edx
  unsigned int v98; // ebx
  int v99; // eax
  int v100; // edx
  int v101; // edx
  int v102; // edi
  int v103; // ebx
  int v104; // edi
  int v105; // eax
  int v106; // edx
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // eax
  unsigned int v111; // ecx
  int v112; // eax
  int v113; // eax
  int v114; // eax
  int v115; // eax
  int v116; // edi
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // edx
  int v123; // eax
  int result; // eax
  int v125; // ebx
  int v126; // eax
  int v127; // edx
  int v128; // edx
  int v129; // ebx
  int v130; // eax
  int v131; // edx
  int v132; // edx
  int v133; // ebx
  int v134; // eax
  int v135; // edx
  int v136; // ebx
  int v137; // eax
  int v138; // edx
  int v139; // edx
  int v140; // edx
  int v141; // edx
  float v142; // [esp+0h] [ebp-74h]
  float v143; // [esp+0h] [ebp-74h]
  char v144; // [esp+8h] [ebp-6Ch]
  float v145; // [esp+Ch] [ebp-68h]
  float v146; // [esp+Ch] [ebp-68h]
  float v147; // [esp+Ch] [ebp-68h]
  float v148; // [esp+Ch] [ebp-68h]
  int v149; // [esp+1Ch] [ebp-58h] BYREF
  int v150; // [esp+20h] [ebp-54h]
  int v151; // [esp+24h] [ebp-50h]
  int v152; // [esp+34h] [ebp-40h]
  char v153; // [esp+38h] [ebp-3Ch]
  int v154; // [esp+3Ch] [ebp-38h]
  int v155; // [esp+40h] [ebp-34h]
  int v156; // [esp+44h] [ebp-30h]
  unsigned int v157; // [esp+48h] [ebp-2Ch]
  unsigned int v158; // [esp+4Ch] [ebp-28h]
  unsigned int v159; // [esp+50h] [ebp-24h]
  unsigned int v160; // [esp+54h] [ebp-20h]
  int *pThis; // [esp+58h] [ebp-1Ch]
  unsigned int v162; // [esp+5Ch] [ebp-18h]
  unsigned int v163; // [esp+60h] [ebp-14h]
  int v164; // [esp+64h] [ebp-10h]
  int v165; // [esp+68h] [ebp-Ch]
  int v166; // [esp+6Ch] [ebp-8h]
  unsigned int v167; // [esp+70h] [ebp-4h]
  int i; // [esp+80h] [ebp+Ch]
  int v169; // [esp+80h] [ebp+Ch]
  int v170; // [esp+80h] [ebp+Ch]
  float v171; // [esp+80h] [ebp+Ch]
  int j; // [esp+80h] [ebp+Ch]
  unsigned int v173; // [esp+84h] [ebp+10h]
  int v174; // [esp+84h] [ebp+10h]

  pThis = this;
  v7 = sub_41A5E0(pArg4 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v8 = sub_4E9CF0(v7, (unsigned int *)&nArg5, 10, 10);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 14, v10, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v11 = sub_41A5E0(pArg4 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v12 = sub_4E9CF0(v11, (unsigned int *)&nArg5, 10, 10);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 28, v13, v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v14 = sub_41A5E0(pArg4 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v15 = sub_4E9CF0(v14, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 42, v16, v15);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v17 = sub_41A5E0(pArg4 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v18 = sub_4E9CF0(v17, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 56, v19, v18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v20 = sub_41A5E0(pArg4 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v21 = sub_4E9CF0(v20, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 70, v22, v21);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v23 = sub_41A5E0(pArg4 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v24 = sub_4E9CF0(v23, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 98, v25, v24);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v173 = pArg4 + 112;
  v26 = sub_41A5E0(v173);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v27 = sub_4E9CF0(v26, (unsigned int *)&nArg5, 5, 8);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 112, v28, v27);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v163 = pArg4 + 126;
  v29 = sub_41A5E0(pArg4 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v30 = sub_4E9CF0(v29, (unsigned int *)&nArg5, 5, 8);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 126, v31, v30);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v167 = pArg4 + 140;
  v32 = sub_41A5E0(pArg4 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v33 = sub_4E9CF0(v32, (unsigned int *)&nArg5, 5, 8);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 140, v34, v33);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v162 = pArg4 + 154;
  v35 = sub_41A5E0(pArg4 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v36 = sub_4E9CF0(v35, (unsigned int *)&nArg5, 5, 8);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 154, v37, v36);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v38 = sub_41A5E0(pArg4 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v160 = pArg3 + 224;
  sub_41A590(pArg3 + 224, v39, v38);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v40 = sub_41A5E0(pArg4 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 238, v41, v40);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v42 = sub_41A5E0(pArg4 + 252);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v158 = pArg3 + 252;
  sub_41A590(pArg3 + 252, v43, v42);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v44 = sub_41A5E0(pArg4 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v159 = pArg3 + 266;
  sub_41A590(pArg3 + 266, v45, v44);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v46 = sub_41A5E0(pArg4 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 280, v47, v46);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v48 = sub_41A5E0(pArg4 + 294);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v157 = pArg3 + 294;
  sub_41A590(pArg3 + 294, v49, v48);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v50 = pArg3 + 308;
  v164 = pArg4 - pArg3;
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    v51 = sub_41A5E0(v164 + v50);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v52 = sub_4E9CF0(v51, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
    sub_41A590(v50, v53, v52);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v50 += 14;
  }
  v54 = sub_41A5E0(pArg4 + 364);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v55 = sub_4E9CF0(v54, (unsigned int *)&nArg5, 20, 5);  // 区间随机伤害浮动（± 方差；研究 P14 九步第 4 步的独立实现）
  sub_41A590(pArg3 + 364, v56, v55);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v57 = 0;
  v169 = 0;
  do  // do-while 循环体起点
  {
    if ( v57 == 13 )  // 若 v57 == 13
    {
      v58 = sub_41A5E0(pArg4 + 560);  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg3 + 560, v59, v58);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    else  // 否则分支
    {
      v60 = 14 * (v169 + 27);
      LODWORD(v61) = sub_41A5E0(v60 + pArg4);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v165 = v61;
      if ( (uint32_t)v61 != 0 )
      {
        v145 = (double)v165 * 0.2;
        v166 = sub_432F40(v145);  // 舍入取整（float → int）
        if ( v166 >= 5 )  // 若 v166 >= 5
          v166 = 5;
        *(float *)&v166 = (float)v166;
        v62 = sub_4D33A0((unsigned int *)&nArg5);  // v62 = 调 sub_4D33A0 返回值
        v142 = -*(float *)&v166;
        v146 = sub_4049C0(v142, *(float *)&v166, v62 % 0x3E8, 999);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        v61 = sub_432F40(v146);  // 舍入取整（float → int）
        LODWORD(v61) = v165 + v61;
      }
      sub_41A590(v60 + pArg3, SHIDWORD(v61), v61);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      v57 = v169;
    }
    v169 = ++v57;
  }
  while ( v57 < 16 );  // 条件循环
  LODWORD(v63) = sub_41A5E0(pArg4 + 602);  // crypt4byte 解密校验（·0x41A590 逆运算）
  v64 = v63;
  if ( (uint32_t)v63 != 0 )
  {
    v147 = (double)(int)v63 * 0.2;
    v170 = sub_432F40(v147);  // 舍入取整（float → int）
    if ( v170 >= 5 )  // 若 v170 >= 5
      v170 = 5;
    v171 = (float)v170;
    v65 = sub_4D33A0((unsigned int *)&nArg5);  // v65 = 调 sub_4D33A0 返回值
    v143 = -v171;
    v148 = sub_4049C0(v143, v171, v65 % 0x3E8, 999);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v63 = sub_432F40(v148);  // 舍入取整（float → int）
    LODWORD(v63) = v64 + v63;
  }
  sub_41A590(pArg3 + 602, SHIDWORD(v63), v63);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v66 = sub_41A5E0(pArg4 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 616, v67, v66);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v68 = sub_41A5E0(pArg4 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 630, v69, v68);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v70 = sub_41A5E0(pArg4 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 644, v71, v70);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v72 = sub_41A5E0(pArg4 + 658);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 658, v73, v72);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v74 = sub_41A5E0(pArg4 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 672, v75, v74);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v76 = sub_41A5E0(pArg4 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 686, v77, v76);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v78 = sub_41A5E0(pArg4 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 700, v79, v78);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v80 = sub_41A5E0(pArg4 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 714, v81, v80);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v82 = sub_41A5E0(pArg4 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 728, v83, v82);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(pArg3 + 772) = *(uint32_t *)(pArg4 + 772);  // pArg3+772〔uVal772(推断)〕
  *(uint32_t *)(pArg3 + 776) = *(uint32_t *)(pArg4 + 776);
  v84 = sub_41A5E0(pArg4 + 780);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 780, v85, v84);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v86 = sub_41A5E0(pArg4 + 794);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 794, v87, v86);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v88 = sub_41A5E0(pArg4 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 808, v89, v88);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v90 = sub_41A5E0(pArg4 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 822, v91, v90);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v92 = sub_41A5E0(pArg4 + 742);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 742, v93, v92);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v94 = sub_41A5E0(pArg4 + 756);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 756, v95, v94);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v96 = sub_41A5E0(pArg4 + 836);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg3 + 836, v97, v96);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint8_t *)(pArg3 + 850) = *(uint8_t *)(pArg4 + 850);
  v98 = pArg3 + 851;
  for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
  {
    v99 = sub_41A5E0(v98 + v164);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v98, v100, v99);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v98 += 14;
  }
  *(uint8_t *)(pArg3 + 879) = *(uint8_t *)(pArg4 + 879);
  *(uint8_t *)(pArg3 + 880) = *(uint8_t *)(pArg4 + 880);
  sub_4ED540((int *)(pArg3 + 884), (int *)(pArg4 + 884));  // 32B 条目向量拷贝赋值（全容量路径）
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( sub_41A5E0(v173) != 0 && sub_41A5E0(v167) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v102 = sub_41A5E0(pArg3 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v103 = sub_41A5E0(pArg3 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v174 = sub_41A5E0(v173);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v104 = v103 + v102;
        v105 = v174 + sub_41A5E0(v167);  // crypt4byte 解密校验（·0x41A590 逆运算）
        if ( v104 <= 5 || v105 < 16 )  // 若 v104 <= 5 与/或 v105 < 16
          goto LABEL_42;
        v107 = v105 - 14;
        if ( v104 >= v107 )  // 若 v104 >= v107
          goto LABEL_25;
        v108 = 0;
        goto LABEL_58;
      }
      if ( sub_41A5E0(v173) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v110 = sub_41A5E0(pArg3 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v111 = v173;
        goto LABEL_41;
      }
      if ( sub_41A5E0(v167) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v104 = sub_41A5E0(pArg3 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v112 = sub_41A5E0(v167);  // crypt4byte 解密校验（·0x41A590 逆运算）
        if ( v104 <= 5 )  // 若 v104 <= 5
        {
          v108 = 2;
          goto LABEL_58;
        }
        if ( v112 < 8 )  // 若 v112 < 8
        {
          v108 = 2;
          goto LABEL_58;
        }
        v113 = v112 - 6;
        if ( v104 < v113 )  // 若 v104 < v113
        {
          v108 = 0;
          goto LABEL_58;
        }
        v114 = v113 + 4;
        if ( v104 < v114 )  // 若 v104 < v114
        {
          v108 = 1;
          goto LABEL_58;
        }
        v115 = v114 + 5;
        if ( v104 < v115 )  // 若 v104 < v115
        {
          v108 = 2;
          goto LABEL_58;
        }
        goto LABEL_57;
      }
      goto LABEL_59;
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      v110 = sub_41A5E0(pArg3 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v111 = v163;
LABEL_41:  // 标签 LABEL_41（跳转合流点）
      v116 = v110;
      v117 = sub_41A5E0(v111);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v116 <= 5 )  // 若 v116 <= 5
        goto LABEL_42;
      if ( v117 >= 8 )  // 若 v117 >= 8
      {
        v118 = v117 - 6;
        if ( v116 >= v118 )  // 若 v116 >= v118
        {
          v119 = v118 + 4;
          if ( v116 >= v119 )  // 若 v116 >= v119
          {
            v120 = v119 + 5;
            if ( v116 >= v120 )  // 若 v116 >= v120
              v108 = (v116 >= v120 + 4) + 3;
            else  // 否则分支
              v108 = 2;
          }
          else  // 否则分支
          {
            v108 = 1;
          }
        }
        else  // 否则分支
        {
          v108 = 0;
        }
      }
      else  // 否则分支
      {
        v108 = 2;
      }
      goto LABEL_58;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      v104 = sub_41A5E0(pArg3 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v121 = sub_41A5E0(v162);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v104 <= 5 || v121 < 8 )  // 若 v104 <= 5 与/或 v121 < 8
        goto LABEL_42;
      v107 = v121 - 6;
      if ( v104 >= v107 )  // 若 v104 >= v107
      {
LABEL_25:  // 标签 LABEL_25（跳转合流点）
        v109 = v107 + 4;
        if ( v104 >= v109 )  // 若 v104 >= v109
        {
          v115 = v109 + 5;
          if ( v104 < v115 )  // 若 v104 < v115
          {
LABEL_42:  // 标签 LABEL_42（跳转合流点）
            v108 = 2;
          }
          else  // 否则分支
          {
LABEL_57:  // 标签 LABEL_57（跳转合流点）
            v106 = (v104 >= v115 + 4) + 3;
            v108 = v106;
          }
        }
        else  // 否则分支
        {
          v108 = 1;
        }
      }
      else  // 否则分支
      {
        v108 = 0;
      }
LABEL_58:  // 标签 LABEL_58（跳转合流点）
      sub_41A590(pArg3, v106, v108);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
LABEL_59:  // 标签 LABEL_59（跳转合流点）
      if ( (uint8_t)nArg6 != 0 )
      {
        v122 = *pThis;
        v149 = 0;
        v150 = 0;
        v151 = 0;
        v144 = nArg6 - 1;
        v152 = 0;
        v153 = 0;
        v154 = 0;
        v155 = 0;
        v156 = 0;
        v123 = (*(int (/*thiscall*/ **)(int *))(v122 + 16))(pThis);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
        result = sub_4F9F40(&v149, 0, *(uint8_t *)(v123 + 24), v144, nArg2);  // 强化数值重算（44B 行 × 三层浮点系数）(推断)
        if ( (uint8_t)result != 0 )
        {
          result = nArg2 - 8;
          switch ( nArg2 )  // 按 nArg2 分派
          {
            case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
              if ( sub_41A5E0(pArg3 + 112) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
              {
                v125 = v149;
                v126 = sub_41A5E0(pArg3 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
                sub_41A590(pArg3 + 112, v127, v125 + v126);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
                sub_41A590(pArg3 + 168, v128, v149);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              }
              result = sub_41A5E0(pArg3 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
              if ( result != 0 )  // 若结果非 0（成功）
              {
                v129 = v149;
                v130 = sub_41A5E0(pArg3 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
                sub_41A590(pArg3 + 140, v131, v129 + v130);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
                result = sub_41A590(pArg3 + 196, v132, v149);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              }
              break;  // 跳出循环/分支
            case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
            case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
            case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
            case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
            case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
              v133 = v150;
              v134 = sub_41A5E0(pArg3 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
              sub_41A590(pArg3 + 126, v135, v133 + v134);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              result = sub_41A590(pArg3 + 182, v150, v150);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              break;  // 跳出循环/分支
            case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
            case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
            case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
              v136 = v150;
              v137 = sub_41A5E0(pArg3 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
              sub_41A590(pArg3 + 154, v138, v136 + v137);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              result = sub_41A590(pArg3 + 210, v139, v150);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
              break;  // 跳出循环/分支
            default:  // 默认分支
              return result;
          }
        }
      }
      else  // 否则分支
      {
        sub_41A590(v160, v101, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        sub_41A590(v159, v140, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        nArg6 = 0;
        sub_41A590(v158, v141, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        nArg6 = 0;
        return sub_41A590(v157, 0, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      }
      return result;
    default:  // 默认分支
      goto LABEL_59;
  }
}


// ------------------------------------------------------------
// 0x4EE120 sub_4EE120 —— 32B 条目尾部推入
// 32 字节条目尾部推入：容量足 → ·sub_4EB800 原地构造成 +8 并推进 32；否则 ·sub_4ED080 区间插入扩容。由 ·0x4EE300（随机词条应用）对 +225 条目向量推入。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EE120(int this, uint32_t *uArg2)  // 实现：32B 条目尾部推入
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 5 )  // 若 fld_4 != 0
  {
    fld_82 = *(uint32_t **)(this + 8);  // fld_82 = 读 this+8
    sub_4EB800(fld_82, 1, uArg2);  // 32 字节条目批量构造（nArg2 个，源自 pArg3）
    *(uint32_t *)(this + 8) = fld_82 + 8;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else  // 否则分支
  {
    sub_4ED080(this, *(char **)(this + 8), 1u, uArg2);  // 32 字节条目 vector 区间插入（容量三路 + 析构收尾）
  }
}



// ------------------------------------------------------------
// 0x4EE190 sub_4EE190 —— 124B 行区间前拷构
// 124 字节行区间前拷构：读 [pArg1,uArg2) 逐条写 uArg3 起（9 标量 + ·sub_4ED6A0 头部 + 尾 52B qmemcpy），返回尾指针 —— ·0x4EF540 擦除时把尾段前移覆盖被删区间。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EE190(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：124B 行区间前拷构
{
  uint32_t *pArg12; // eax
  uint32_t *v4; // esi
  uint32_t *v5; // ebx
  bool v6; // zf
  uint32_t *i; // [esp+0h] [ebp-4h]

  pArg12 = pArg1;
  if ( pArg1 != uArg2 )  // 若 pArg1 != uArg2
  {
    v4 = pArg1 + 3;
    v5 = uArg3 + 3;
    for ( i = pArg1 + 3; ; v4 = i )  // 遍历循环
    {
      *uArg3 = *pArg12;
      *(v5 - 2) = *(v4 - 2);
      *(v5 - 1) = *(v4 - 1);
      *v5 = *v4;
      v5[1] = v4[1];  // v5[1] = 取 v4[1]
      v5[2] = v4[2];  // v5[2] = 取 v4[2]
      v5[3] = v4[3];  // v5[3] = 取 v4[3]
      v5[4] = v4[4];  // v5[4] = 取 v4[4]
      v5[5] = v4[5];  // v5[5] = 取 v4[5]
      v5[6] = v4[6];  // v5[6] = 取 v4[6]
      sub_4ED3F0((int)(v5 + 7), (int)(v4 + 7));  // int 向量拷贝赋值（全容量路径）
      sub_4ED3F0((int)(v5 + 11), (int)(v4 + 11));  // int 向量拷贝赋值（全容量路径）
      qmemcpy(v5 + 15, v4 + 15, 0x34u);
      uArg3 += 31;
      v5 += 31;
      v6 = pArg1 + 31 == uArg2;
      pArg1 += 31;
      i += 31;
      if ( v6 )
        break;  // 跳出循环/分支
      pArg12 = pArg1;
    }
  }
  return uArg3;
}



// ------------------------------------------------------------
// 0x4EE250 sub_4EE250 —— 124B 行区间后拷构
// 124 字节行区间后拷构：自尾向前把 [nArg1,pArg2) 抄到 pArg3 尾端（9 标量 + ·sub_4ED3F0 两向量 + 尾 52B）—— 中段腾挪的后段版，返回尾指针（·sub_4EE560 薄转发）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4EE250(int nArg1, int pArg2, int pArg3)  // 实现：124B 行区间后拷构
{
  int pArg22; // eax
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  int v7; // [esp+10h] [ebp+Ch]

  pArg22 = pArg2;
  if ( nArg1 != pArg2 )  // 若 nArg1 != pArg2
  {
    v4 = (uint32_t *)(pArg3 + 12);  // pArg3+12〔nSkillRec12(推断)〕
    v5 = (uint32_t *)(pArg2 + 12);  // pArg2+12〔nSkillRec12(推断)〕
    while ( 1 )  // 条件循环
    {
      v5 -= 31;
      v4 -= 31;
      v7 = pArg22 - 124;
      *(uint32_t *)(pArg3 - 124) = *(uint32_t *)(pArg22 - 124);
      pArg3 -= 124;
      *(v4 - 2) = *(v5 - 2);
      *(v4 - 1) = *(v5 - 1);
      *v4 = *v5;
      v4[1] = v5[1];  // v4[1] = 取 v5[1]
      v4[2] = v5[2];  // v4[2] = 取 v5[2]
      v4[3] = v5[3];  // v4[3] = 取 v5[3]
      v4[4] = v5[4];  // v4[4] = 取 v5[4]
      v4[5] = v5[5];  // v4[5] = 取 v5[5]
      v4[6] = v5[6];  // v4[6] = 取 v5[6]
      sub_4ED3F0((int)(v4 + 7), (int)(v5 + 7));  // int 向量拷贝赋值（全容量路径）
      sub_4ED3F0((int)(v4 + 11), (int)(v5 + 11));  // int 向量拷贝赋值（全容量路径）
      qmemcpy(v4 + 15, v5 + 15, 0x34u);
      if ( v7 == nArg1 )  // 若 v7 == nArg1
        break;  // 跳出循环/分支
      pArg22 = v7;
    }
  }
  return pArg3;
}



// ------------------------------------------------------------
// 0x4EE300 sub_4EE300 —— 随机词条应用器（+233 游标）
// 随机词条应用器：+233 游标（-1 空转）定位 +230 表内 80 字节条目，按条目 tag 分派 ——
// tag 15/32 未消费则 ·sub_4450B0 计数器加值；tag 36/42 写浮点属性 +658/+742（·sub_4AED60）；tag 43 未消费则 ·sub_4EE120 把 +20 起 int 向量推入 +225 列表；
// 已消费条目（+4 非 0）一律 ·sub_4EBD50 复位（默认构造：清零 + 空串）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EE300(uint32_t *this)  // 实现：随机词条应用器（+233 游标）
{
  unsigned int pThis_E9; // esi
  unsigned int v3; // ebx
  int pNameBuf; // eax
  int fld_e2302; // esi
  int v6; // edx
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+10h] [ebp-4h]

  pThis_E9 = (unsigned int)(this + 233);  // this+233〔游标〕
  if ( sub_41A5E0((unsigned int)(this + 233)) != -1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v3 = sub_41A5E0(pThis_E9);  // crypt4byte 解密校验（·0x41A590 逆运算）
    pNameBuf = *(this + 230);  // this+920〔pNameBuf〕
    if ( pNameBuf != 0 && v3 < (*(this + 231) - pNameBuf) / 80 )  // 若 fld_e230 != 0
    {
      fld_e2302 = *(this + 230) + 80 * sub_41A5E0(pThis_E9);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v9 = COERCE_FLOAT(sub_41A5E0(fld_e2302 + 5));  // crypt4byte 解密校验（·0x41A590 逆运算）
      switch ( *(uint32_t *)fld_e2302 )  // 按 *(uint32_t *)fld_e2302 分派
      {
        case 0xF:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_15;
          goto LABEL_6;
        case 0x20:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_15;
LABEL_6:  // 标签 LABEL_6（跳转合流点）
          sub_4450B0((uint64_t)v9);  // 计数器加值
          break;  // 跳出循环/分支
        case 0x24:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_15;
          v7 = (float)(int)(uint64_t)v9;
          sub_4AED60((char *)this + 658, v7);
          break;  // 跳出循环/分支
        case 0x2A:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
            goto LABEL_15;
          v8 = (float)(int)(uint64_t)v9;
          sub_4AED60((char *)this + 742, v8);
          break;  // 跳出循环/分支
        case 0x2B:
          if ( *(uint8_t *)(fld_e2302 + 4) != 0 )
LABEL_15:  // 标签 LABEL_15（跳转合流点）
            sub_4EBD50(fld_e2302, v6);  // 属性条目默认构造（清零 + 空串 + +20 = 4）
          else  // 否则分支
            sub_4EE120((int)(this + 225), (uint32_t *)(fld_e2302 + 20));  // 32B 条目尾部推入
          break;  // 跳出循环/分支
        default:  // 默认分支
          return;
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4EE4A0 sub_4EE4A0 —— 80B 条目区间拷构转发
// 80 字节条目区间拷构的 stdcall 薄转发（包装 ·sub_4ED730）。
// ------------------------------------------------------------
char */*stdcall*/ sub_4EE4A0(int nArg1, int nArg2, char *pszArg3)  // 实现：80B 条目区间拷构转发
{
  return sub_4ED730(nArg1, nArg2, pszArg3);  // 80B 条目区间拷构
}



// ------------------------------------------------------------
// 0x4EE4C0 sub_4EE4C0 —— 124B 行区间填充
// 124 字节行区间填充：把单条模板行 pArg3 逐字段（9 标量 + ·sub_4ED3F0 两 int 向量 + 尾 52B）写满 [uArg1,uArg2) —— ·0x4EF5A0 插入时用栈模板铺新槽。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EE4C0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 实现：124B 行区间填充
{
  uint32_t *result; // eax
  uint32_t *v4; // ebx

  result = uArg1;
  if ( uArg1 != uArg2 )  // 若 uArg1 != uArg2
  {
    v4 = uArg1 + 3;
    do  // do-while 循环体起点
    {
      *result = *pArg3;
      *(v4 - 2) = pArg3[1];
      *(v4 - 1) = pArg3[2];
      *v4 = pArg3[3];
      v4[1] = pArg3[4];  // v4[1] = 取 pArg3[4]
      v4[2] = pArg3[5];  // v4[2] = 取 pArg3[5]
      v4[3] = pArg3[6];  // v4[3] = 取 pArg3[6]
      v4[4] = pArg3[7];  // v4[4] = 取 pArg3[7]
      v4[5] = pArg3[8];  // v4[5] = 取 pArg3[8]
      v4[6] = pArg3[9];  // v4[6] = 取 pArg3[9]
      sub_4ED3F0((int)(v4 + 7), (int)(pArg3 + 10));  // int 向量拷贝赋值（全容量路径）
      sub_4ED3F0((int)(v4 + 11), (int)(pArg3 + 14));  // int 向量拷贝赋值（全容量路径）
      qmemcpy(v4 + 15, pArg3 + 18, 0x34u);
      result = uArg1 + 31;
      v4 += 31;
      uArg1 = result;
    }
    while ( result != uArg2 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EE560 sub_4EE560 —— 124B 行区间后拷构转发
// 124 字节行区间后拷构的薄转发（包装 ·sub_4EE250）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4EE560(int nArg1, int nArg2, int nArg3)  // 实现：124B 行区间后拷构转发
{
  return sub_4EE250(nArg1, nArg2, nArg3);  // 124B 行区间后拷构
}



// ------------------------------------------------------------
// 0x4EE580 sub_4EE580 —— ★ 物品实例生成（按文件名）
// ★ 物品实例生成（按文件名）：·dword_9B06DC 空或 44B 步进表未建时先 ·sub_4FAC40 解析 etc/upgrade.etc（强化费用表）；
// 经 ·dword_8F84D0 定义库（vt+4）查 Block，未命中打「EQUIPMENT CREATE FAIL! FILENAME[%s]」；命中则 +333 挂定义块，+331/+332 取 nArg4/nArg5（-1 回落定义 +1092/+1096），逐项搬标量/字节字段，+60/+68 串字段经 ·sub_41ACF0 取值 + strcmp 哨兵判定（命中则 ·dword_8F84B8 vt+60 查表 + ·sub_418DD0），+2076 向量经 ·sub_4ED3F0，+2096 子项逐个推入 +29 向量（快路径 ·sub_41FFE0 / 扩容 ·sub_4206D0）；
// 末段 +1108 向量经 ·sub_4ED3F0 复制到 +313 并 new 0x3B4 ·sub_437E70 建 +317 子对象、+320 取定义 +2072；nArg3 非 0 走 vt+184 显式参数，否则 ·sub_4E9A50 默认参数【推断】后 vt+184。
// ------------------------------------------------------------
int /*thiscall*/ sub_4EE580(uint32_t *this, const char *Block, int nArg3, int nArg4, int nArg5)  // 实现：物品实例生成（按文件名）
{
  uint32_t *v6; // eax
  int pEquipDef1332; // eax
  int pEquipDef1332_; // eax
  int fld_e3333; // eax
  int fld_e3335; // eax
  int pEquipDef1332_2; // eax
  unsigned int v13; // edi
  int pEquipDef1332_3; // ecx
  int v15; // edx
  int fld_e29; // eax
  unsigned int fld_e30; // edx
  uint32_t *fld_e302; // edi
  int pEquipDef1332_4; // eax
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int pEquipDef1332_5; // eax
  int v25; // ecx
  int v26; // eax
  uint32_t *pMem; // eax
  uint32_t *v28; // eax
  uint32_t *v29; // eax
  int v30; // edx
  int fld_e3334; // [esp-8h] [ebp-5Ch]
  int fld_e3336; // [esp-8h] [ebp-5Ch]
  int fld_e33311; // [esp-4h] [ebp-58h]
  int v34; // [esp+8h] [ebp-4Ch] BYREF
  uint8_t v35[14]; // [esp+Ch] [ebp-48h] BYREF
  uint8_t v36[14]; // [esp+1Ah] [ebp-3Ah] BYREF
  uint8_t v37[14]; // [esp+28h] [ebp-2Ch] BYREF
  uint8_t v38[14]; // [esp+36h] [ebp-1Eh] BYREF
  int v39; // [esp+44h] [ebp-10h]
  int v40; // [esp+50h] [ebp-4h]
  void *Blocka; // [esp+5Ch] [ebp+8h]
  int v42; // [esp+64h] [ebp+10h]

  if ( dword_9B06DC == 0 || (v39 = (dword_9B06E0 - dword_9B06DC) / 44) == 0 )  // 若 dword_9B06DC == 0
    sub_4FAC40("etc/upgrade.etc", &unk_9B06D8);  // 强化(upgrade)费用表解析器（importUpgradeTable）
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84D0 + 4))(dword_8F84D0, Block);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 333) = v6;  // this+1332〔pEquipDef1332〕
  if ( v6 == nullptr )  // 若 v6 为空
    return off_77F3FC("EQUIPMENT CREATE FAIL! FILENAME[%s]", Block);  // 返回 调 off_77F3FC
  if ( nArg4 == -1 || nArg5 == -1 )  // 若 nArg4 == -1 与/或 nArg5 == -1
  {
    *(this + 331) = v6[273];  // this+1324〔pAnimAtlas1324〕
    *(this + 332) = v6[274];  // this+1328〔pAnimHost1328〕
  }
  else  // 否则分支
  {
    *(this + 331) = nArg4;  // this+1324〔pAnimAtlas1324〕
    *(this + 332) = nArg5;  // this+1328〔pAnimHost1328〕
  }
  *(this + 3) = *v6;  // this+12〔nSkillRec12(推断)〕
  sub_41B0D0(v6 + 530);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(*(this + 333) + 2124);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(*(this + 333) + 2128);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(*(this + 333) + 2136);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  pEquipDef1332 = *(this + 333);  // this+1332〔pEquipDef1332〕
  *(this + 8) = *(uint32_t *)(pEquipDef1332 + 4);  // this+32〔nHeight(推断)〕
  *(this + 9) = *(uint32_t *)(pEquipDef1332 + 8);  // this+36〔nStateWord36(推断)〕
  *(this + 11) = *(uint32_t *)(pEquipDef1332 + 20);  // this+44〔nExpireMs(推断)〕
  *(this + 15) = *(uint32_t *)(pEquipDef1332 + 32);  // this+60〔nFadeValue60(推断)〕
  *(this + 12) = *(uint32_t *)(pEquipDef1332 + 24);  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 13) = *(uint32_t *)(pEquipDef1332 + 28);  // this+52〔bAuraState(推断)〕
  *(this + 14) = *(uint32_t *)(pEquipDef1332 + 36);  // this+56〔pCmdVecCap56(推断)〕
  *(this + 16) = *(uint32_t *)(pEquipDef1332 + 40);  // this+64〔apServerTabBtn(推断)〕
  *((uint8_t *)this + 68) = *(uint8_t *)(pEquipDef1332 + 44);  // this+68〔nCharCount(推断)〕
  *((uint8_t *)this + 69) = *(uint8_t *)(*(this + 333) + 45);  // this[69] = 读 this+333
  *((uint8_t *)this + 70) = *(uint8_t *)(*(this + 333) + 46);  // this[70] = 读 this+333
  *((uint8_t *)this + 71) = *(uint8_t *)(*(this + 333) + 47);  // this+71〔bMoveType〕
  pEquipDef1332_ = *(this + 333);  // this+1332〔pEquipDef1332〕
  *(this + 2) = *(uint32_t *)(pEquipDef1332_ + 48);  // this+8〔nSkillRec8(推断)〕
  *(this + 18) = *(uint32_t *)(pEquipDef1332_ + 56);  // this+72〔nSnapshot72(推断)〕
  if ( strcmp((const char *)sub_41ACF0(pEquipDef1332_ + 60), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
  {
    fld_e3333 = sub_41ACF0(*(this + 333) + 60);  // 驻留串句柄 → 字符串指针
    fld_e3334 = *(uint32_t *)(*(this + 333) + 64);  // this+1332〔pEquipDef1332〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, fld_e3333);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *(this + 19) = sub_418DD0(fld_e3334);  // this+76〔pBtnActionE〕
  }
  if ( strcmp((const char *)sub_41ACF0(*(this + 333) + 68), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
  {
    fld_e3335 = sub_41ACF0(*(this + 333) + 68);  // 驻留串句柄 → 字符串指针
    fld_e3336 = *(uint32_t *)(*(this + 333) + 72);  // this+1332〔pEquipDef1332〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, fld_e3335);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *(this + 20) = sub_418DD0(fld_e3336);  // 调 资源句柄 (101)
  }
  sub_41B0D0(*(this + 333) + 1068);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  pEquipDef1332_2 = *(this + 333);  // this+1332〔pEquipDef1332〕
  *(this + 23) = *(uint32_t *)(pEquipDef1332_2 + 16);  // this+92〔pFxObjC(推断)〕
  sub_4ED3F0((int)(this + 24), pEquipDef1332_2 + 2076);  // int 向量拷贝赋值（全容量路径）
  v13 = 0;
  while ( 1 )  // 条件循环
  {
    pEquipDef1332_3 = *(this + 333);  // this+1332〔pEquipDef1332〕
    v15 = *(uint32_t *)(pEquipDef1332_3 + 2096);
    v42 = v13;
    if ( v15 == 0 || v13 >= (*(uint32_t *)(pEquipDef1332_3 + 2100) - v15) >> 2 )  // 若 v15 == 0
      break;  // 跳出循环/分支
    Blocka = (void *)(v15 + 4 * v13);
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    if ( fld_e29 != 0 )  // 若 fld_e29 非 0
      fld_e30 = (*(this + 30) - fld_e29) >> 2;  // this+120〔pAnimObj〕
    else  // 否则分支
      fld_e30 = 0;
    if ( fld_e29 != 0 && fld_e30 < (*(this + 31) - fld_e29) >> 2 )  // 若 fld_e29 != 0
    {
      fld_e302 = (uint32_t *)*(this + 30);  // this+120〔pAnimObj〕
      sub_41FFE0(fld_e302, 1, (int)Blocka);  // 驻留句柄区间填充 nArg2 个元素
      *(this + 30) = fld_e302 + 1;  // this+120〔pAnimObj〕
      v13 = v42 + 1;
    }
    else  // 否则分支
    {
      sub_4206D0(this + 28, *(this + 30), 1u, (int)Blocka);  // vector 中间插入（4 字节元素）
      ++v13;
    }
  }
  pEquipDef1332_4 = *(this + 333);  // this+1332〔pEquipDef1332〕
  v20 = *(uint32_t *)(pEquipDef1332_4 + 92);
  *(this + 37) = v20;  // this+148〔fAdd148(推断)〕
  sub_41A590((unsigned int)(this + 38), v20, *(uint32_t *)(pEquipDef1332_4 + 96));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 166, v21, *(uint32_t *)(*(this + 333) + 100));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 45), v22, *(uint32_t *)(*(this + 333) + 52));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41DC80(*(this + 333) + 1072);  // vector<T 4B 驻留句柄> 拷贝赋值 operator=
  pEquipDef1332_5 = *(this + 333);  // this+1332〔pEquipDef1332〕
  v25 = *(uint32_t *)(pEquipDef1332_5 + 1112);
  v26 = pEquipDef1332_5 + 1108;
  if ( v25 != 0 )  // 若 v25 非 0
  {
    v23 = (*(uint32_t *)(v26 + 8) - v25) >> 2;  // 向量元素数 = (end−begin)/4
    if ( v23 != 0 )  // 若 v23 非 0
    {
      sub_4ED3F0((int)(this + 313), v26);  // int 向量拷贝赋值（全容量路径）
      pMem = operator new(0x3B4u);  // new(948 字节) 分配对象
      v40 = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        v28 = sub_437E70(pMem);  // 配置对象构造（clong/cfloat）
      else  // 否则分支
        v28 = nullptr;  // v28 = 空指针
      *(this + 317) = v28;
      fld_e33311 = *(this + 333) + 2132;  // this+1332〔pEquipDef1332〕
      v40 = -1;
      sub_41B0D0(fld_e33311);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
    }
  }
  *(this + 320) = *(uint32_t *)(*(this + 333) + 2072);  // this+1332〔pEquipDef1332〕
  sub_41A590((unsigned int)(this + 33), v23, 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( nArg3 != 0 )  // 若 nArg3 非 0
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 184))(this, nArg3);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  v29 = sub_4E9A50(&v34);  // 四内联 clong 构造 + 初值（0/0/-1/0）
  v30 = *this;
  v40 = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(v30 + 184))(this, v29);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  v40 = 4;
  sub_41A580(v38);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  LOBYTE(v40) = 3;
  sub_41A580(v37);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  LOBYTE(v40) = 2;
  sub_41A580(v36);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  v40 = -1;
  return sub_41A580(v35);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
}


// ------------------------------------------------------------
// 0x4EE9E0 sub_4EE9E0 —— 80B 条目向量拷贝赋值（全容量路径）
// 80 字节条目向量拷贝赋值（全容量路径）：空源 ·sub_436840 销毁重挂；同位覆盖走 ·sub_4ECFE0 + ·sub_435890 析构余量；
// 扩容 ·sub_434A90 预留 + ·sub_4EE4A0 拷构；中段 ·sub_4ED3D0 前段拷贝 + ·sub_4ED730 补尾（元素数 =（+8 − +4）/80，经 ·sub_4EAF60 计算）。
// 服务属性行 +916 起 80B 子向量。
// ------------------------------------------------------------
int /*thiscall*/ sub_4EE9E0(int this, int *pDwArg2)  // 实现：80B 条目向量拷贝赋值（全容量路径）
{
  int v3; // eax
  unsigned int v4; // ecx
  uint32_t *fld_4; // ebx
  unsigned int fld_8; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int fld_42; // edx
  unsigned int fld_C; // eax
  uint32_t *v12; // edi
  int v13; // eax

  if ( (int *)this == pDwArg2 )
    return this;
  v3 = pDwArg2[1];  // v3 = 取 pDwArg2[1]
  if ( v3 == 0 || (v4 = (pDwArg2[2] - v3) / 80) == 0 )  // 若 v3 == 0
  {
    sub_436840(this);  // 80 字节条目向量销毁
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 80;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;
  if ( v4 > fld_8 )  // 若 v4 > fld_8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 80;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else  // 否则分支
      fld_C = 0;
    if ( v4 <= fld_C )  // 若 v4 <= fld_C
    {
      v12 = (uint32_t *)(pDwArg2[1] + 80 * sub_4EAF60((int *)this));  // 元素个数 =（+8 − +4）/80
      sub_4ED3D0((uint32_t *)pDwArg2[1], v12, fld_4);  // 80B 条目区间拷构转发
      *(uint32_t *)(this + 8) = sub_4ED730((int)v12, pDwArg2[2], *(char **)(this + 8));  // 80B 条目区间拷构
      return this;
    }
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    {
      sub_435890(fld_4, *(uint32_t *)(this + 8));  // 80 字节条目区间析构
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v13 = sub_4EAF60(pDwArg2);  // 元素个数 =（+8 − +4）/80
    if ( (uint8_t)sub_434A90(v13) != 0 )  // 80 字节元素向量预留
      *(uint32_t *)(this + 8) = sub_4EE4A0(pDwArg2[1], pDwArg2[2], *(char **)(this + 4));  // 80B 条目区间拷构转发
    return this;
  }
  v8 = sub_4ECFE0((uint32_t *)pDwArg2[1], (uint32_t *)pDwArg2[2], fld_4);  // 80 字节条目区间拷贝（前向，含防篡拷贝 + 字符串赋值）
  sub_435890(v8, *(uint32_t *)(this + 8));  // 80 字节条目区间析构
  v9 = pDwArg2[1];  // v9 = 取 pDwArg2[1]
  if ( v9 != 0 )  // 若 v9 非 0
    fld_42 = *(uint32_t *)(this + 4) + 80 * ((pDwArg2[2] - v9) / 80);  // fld_42 = 读 this+4
  else  // 否则分支
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
  *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return this;
}



// ------------------------------------------------------------
// 0x4EEB70 sub_4EEB70 —— 物品实例生成（按索引）
// 物品实例生成（按索引）：·sub_442D00 在 ·dword_9B6C70 映射中查索引，未命中或名字空打「EQUIPMENT CREATE FAIL! INDEX %d」，命中取名字转 ·sub_4EE580；+334/+335 两字段清 0。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EEB70(int *this, int ArgList, int nArg3)  // 实现：物品实例生成（按索引）
{
  int v3; // ebx
  const char *v5; // eax
  int v6; // [esp+Ch] [ebp-4h] BYREF

  v3 = ArgList;
  sub_442D00(&v6, &ArgList);  // 红黑树等键查找（_Find）
  if ( v6 == dword_9B6C70  // 若 v6 == dword_9B6C70
    || (*(uint32_t *)(v6 + 40) < 0x10u ? (v5 = (const char *)(v6 + 20)) : (v5 = *(const char **)(v6 + 20)), v5 == nullptr) )
  {
    off_77F3FC("EQUIPMENT CREATE FAIL! INDEX %d", v3);  // 引擎日志输出函数(printf 风格)
  }
  else  // 否则分支
  {
    sub_4EE580(this, v5, nArg3, -1, -1);  // 物品实例生成（按文件名）
  }
  *(this + 335) = 0;
  *(this + 334) = 0;
}



// ------------------------------------------------------------
// 0x4EEBF0 sub_4EEBF0 —— 124B 属性行整行深拷贝
// ★ 124 字节属性行整行深拷贝（含全部字段与三子向量）：0..880 逐字段 ·sub_41A5E0 读 / ·sub_41A590 写（含 4 + 16 槽 14 字节字段族循环），
// 884 起两个 32B 子向量经 ·sub_4ED540、+916 起 80B 子向量经 ·sub_4EE9E0；由 ·0x4EF0B0 在定义变化时对 +53 主行与 +317 寄宿行按定义块回拷【推断：换装/定义刷新触发】，返回自身。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4EEBF0(unsigned int this, unsigned int pArg2)  // 实现：124B 属性行整行深拷贝
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // eax
  int v35; // edx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  unsigned int v48; // ebx
  int v49; // eax
  int v50; // edx
  bool v51; // zf
  int v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // edx
  int v62; // eax
  int v63; // edx
  int v64; // eax
  int v65; // edx
  int v66; // eax
  int v67; // edx
  int v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // edx
  int v74; // eax
  int v75; // edx
  int v76; // eax
  int v77; // edx
  int v78; // eax
  int v79; // edx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // edx
  int v86; // eax
  int v87; // edx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int v91; // edx
  unsigned int pThis_374; // ecx
  int v93; // eax
  int v94; // edx
  int v96; // [esp+Ch] [ebp-4h]
  int v97; // [esp+Ch] [ebp-4h]
  int v98; // [esp+Ch] [ebp-4h]
  int v99; // [esp+Ch] [ebp-4h]
  unsigned int pThis_134; // [esp+18h] [ebp+8h]
  unsigned int pThis_17A; // [esp+18h] [ebp+8h]
  unsigned int pThis_353; // [esp+18h] [ebp+8h]
  unsigned int pThis_3742; // [esp+18h] [ebp+8h]

  v4 = sub_41A5E0(pArg2);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this, v5, v4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v6 = sub_41A5E0(pArg2 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 14, v7, v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v8 = sub_41A5E0(pArg2 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 28, v9, v8);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v10 = sub_41A5E0(pArg2 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 42, v11, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v12 = sub_41A5E0(pArg2 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 56, v13, v12);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v14 = sub_41A5E0(pArg2 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 70, v15, v14);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v16 = sub_41A5E0(pArg2 + 84);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 84, v17, v16);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v18 = sub_41A5E0(pArg2 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 98, v19, v18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v20 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 112, v21, v20);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v22 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 126, v23, v22);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v24 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 140, v25, v24);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v26 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 154, v27, v26);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v28 = sub_41A5E0(pArg2 + 168);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 168, v29, v28);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v30 = sub_41A5E0(pArg2 + 182);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 182, v31, v30);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v32 = sub_41A5E0(pArg2 + 196);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 196, v33, v32);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v34 = sub_41A5E0(pArg2 + 210);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 210, v35, v34);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v36 = sub_41A5E0(pArg2 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 224, v37, v36);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v38 = sub_41A5E0(pArg2 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 238, v39, v38);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v40 = sub_41A5E0(pArg2 + 252);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 252, v41, v40);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v42 = sub_41A5E0(pArg2 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 266, v43, v42);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v44 = sub_41A5E0(pArg2 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 280, v45, v44);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v46 = sub_41A5E0(pArg2 + 294);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 294, v47, v46);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_134 = this + 308;
  v48 = pArg2 - this;
  v96 = 4;
  do  // do-while 循环体起点
  {
    v49 = sub_41A5E0(v48 + pThis_134);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_134, v50, v49);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v51 = v96 == 1;
    pThis_134 += 14;
    --v96;
  }
  while ( !v51 );  // 条件循环
  v52 = sub_41A5E0(pArg2 + 364);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 364, v53, v52);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  pThis_17A = this + 378;
  v97 = 16;
  do  // do-while 循环体起点
  {
    v54 = sub_41A5E0(pThis_17A + v48);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_17A, v55, v54);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v51 = v97 == 1;
    pThis_17A += 14;
    --v97;
  }
  while ( !v51 );  // 条件循环
  v56 = sub_41A5E0(pArg2 + 602);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 602, v57, v56);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v58 = sub_41A5E0(pArg2 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 616, v59, v58);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v60 = sub_41A5E0(pArg2 + 630);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 630, v61, v60);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v62 = sub_41A5E0(pArg2 + 644);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 644, v63, v62);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v64 = sub_41A5E0(pArg2 + 658);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 658, v65, v64);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v66 = sub_41A5E0(pArg2 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 672, v67, v66);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v68 = sub_41A5E0(pArg2 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 686, v69, v68);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v70 = sub_41A5E0(pArg2 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 700, v71, v70);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v72 = sub_41A5E0(pArg2 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 714, v73, v72);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v74 = sub_41A5E0(pArg2 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 728, v75, v74);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v76 = sub_41A5E0(pArg2 + 742);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 742, v77, v76);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v78 = sub_41A5E0(pArg2 + 756);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 756, v79, v78);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(this + 772) = *(uint32_t *)(pArg2 + 772);  // this+772〔uVal772(推断)〕
  *(uint32_t *)(this + 776) = *(uint32_t *)(pArg2 + 776);
  v80 = sub_41A5E0(pArg2 + 780);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 780, v81, v80);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v82 = sub_41A5E0(pArg2 + 794);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 794, v83, v82);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v84 = sub_41A5E0(pArg2 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 808, v85, v84);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v86 = sub_41A5E0(pArg2 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 822, v87, v86);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v88 = sub_41A5E0(pArg2 + 836);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 836, v89, v88);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint8_t *)(this + 850) = *(uint8_t *)(pArg2 + 850);
  pThis_353 = this + 851;
  v98 = 2;
  do  // do-while 循环体起点
  {
    v90 = sub_41A5E0(pThis_353 + v48);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_353, v91, v90);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v51 = v98 == 1;
    pThis_353 += 14;
    --v98;
  }
  while ( !v51 );  // 条件循环
  *(uint8_t *)(this + 879) = *(uint8_t *)(pArg2 + 879);
  *(uint8_t *)(this + 880) = *(uint8_t *)(pArg2 + 880);
  pThis_374 = this + 884;
  pThis_3742 = this + 884;
  v99 = 2;
  while ( 1 )  // 条件循环
  {
    sub_4ED540(pThis_374 + v48);  // 32B 条目向量拷贝赋值（全容量路径）
    v51 = v99 == 1;
    pThis_3742 += 16;
    --v99;
    if ( v51 )
      break;  // 跳出循环/分支
    pThis_374 = pThis_3742;
  }
  sub_4EE9E0(pArg2 + 916);  // 80B 条目向量拷贝赋值（全容量路径）
  v93 = sub_41A5E0(pArg2 + 932);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 932, v94, v93);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}


// ------------------------------------------------------------
// 0x4EF0B0 sub_4EF0B0 —— 实例属性行同步（定义三元组缓存门）
// ★ 实例属性行同步（定义三元组缓存门）：定义指针 +333 空则直接返回；+1248 首建或 (+290,+291,+1178) 三元组（·sub_41A5E0 逐段比较）变化才重建 ——
// +37 强化档大于 7 走 ·sub_4ED7C0 属性行随机重掷（主行 +53 与 type=18 的 +317 寄宿行两路），否则清 +1233/+1234 与 +305 (0x130) 时钟、·sub_4EEBF0 直拷定义行两路、·sub_46B080 重置 clong、+286 取参数、·sub_4EE300 应用词条；
// 收尾 +1248=1、·sub_4E9FA0 回写三元组、+298 为 -1 时补 +166 值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4EF0B0(int *this, int *pDwArg2)  // 实现：实例属性行同步（定义三元组缓存门）
{
  int result; // eax
  int pThis_123; // ebx
  int v5; // ebx
  unsigned int fld_e3172; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int *v10; // eax
  unsigned int fld_e317; // eax
  int pThis_A6; // eax
  int v13; // edx
  uint32_t v14[4]; // [esp+4h] [ebp-1Ch] BYREF
  int v15; // [esp+1Ch] [ebp-4h]

  result = *(this + 333);  // this+1332〔pEquipDef1332〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( *((uint8_t *)this + 1248) == 0
      || *(this + 290) != *pDwArg2
      || (pThis_123 = sub_41A5E0((unsigned int)(this + 291))) != sub_41A5E0((unsigned int)(pDwArg2 + 1))  // crypt4byte 解密校验（·0x41A590 逆运算）
      || (v5 = sub_41A5E0((unsigned int)this + 1178)) != sub_41A5E0((unsigned int)pDwArg2 + 18) )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( *(this + 37) > 7 )  // this+148〔fAdd148(推断)〕
      {
        v9 = sub_41A5E0((unsigned int)(pDwArg2 + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
        v10 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 172))(this);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
        sub_4ED7C0(this, *v10, (unsigned int)(this + 53), *(this + 333) + 104, *pDwArg2, v9);  // 属性行生成主体（随机抖动 + 档位判定）
        fld_e317 = *(this + 317);  // this+317〔寄宿行两路〕
        if ( fld_e317 != 0 )  // 若 fld_e317 非 0
          sub_4ED7C0(this, 18, fld_e317, *(this + 333) + 1124, *pDwArg2, 0);  // 属性行生成主体（随机抖动 + 档位判定）
      }
      else  // 否则分支
      {
        *((uint8_t *)this + 1233) = 0;
        *((uint8_t *)this + 1234) = 0;
        sub_698F90((int)(this + 305), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        sub_4EEBF0((unsigned int)(this + 53), *(this + 333) + 104);  // 124B 属性行整行深拷贝
        fld_e3172 = *(this + 317);  // this+317〔寄宿行两路〕
        if ( fld_e3172 != 0 )  // 若 fld_e3172 非 0
          sub_4EEBF0(fld_e3172, *(this + 333) + 1124);  // 124B 属性行整行深拷贝
        sub_46B080(pDwArg2 + 8);  // clong 构造与初值写入
        v15 = 0;
        v7 = sub_41A5E0((unsigned int)v14);  // crypt4byte 解密校验（·0x41A590 逆运算）
        sub_41A590((unsigned int)(this + 286), v8, v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        sub_4EE300(this + 53);  // 随机词条应用器（+233 游标）
        v15 = -1;
        sub_41A580(v14);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
      }
      *((uint8_t *)this + 1248) = 1;
    }
    sub_4E9FA0(this + 290, pDwArg2);  // 四 clong 防篡拷贝（pArg2 → this）
    result = sub_41A5E0((unsigned int)(this + 298));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == -1 )
    {
      pThis_A6 = sub_41A5E0((unsigned int)this + 166);  // crypt4byte 解密校验（·0x41A590 逆运算）
      return sub_41A590((unsigned int)(this + 298), v13, pThis_A6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EF270 sub_4EF270 —— 实例清理
// 实例清理：+317 配置对象经 ·sub_4382D0 析构释放并置空，再把 [327,328) 槽内每帧对象经 ·sub_42AF90 析构 + ·sub_657740(228) 释放、槽位清空。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF270(void ****this)  // 实现：实例清理
{
  void *fld_e317; // esi
  void ***fld_e327; // esi
  bool fld_e328; // zf
  void **v5; // edi

  fld_e317 = *(this + 317);
  if ( fld_e317 != nullptr )  // 若 fld_e317 有效（非空）
  {
    sub_4382D0(*(this + 317));  // 配置对象析构
    j__free(fld_e317);
  }
  fld_e327 = *(this + 327);  // this+1308〔pRowVec1308〕
  fld_e328 = fld_e327 == *(this + 328);  // this+1312〔pRowVec1312〕
  *(this + 317) = nullptr;
  if ( !fld_e328 )
  {
    do  // do-while 循环体起点
    {
      v5 = *fld_e327;
      if ( *fld_e327 != nullptr )  // 空指针判定
      {
        sub_42AF90(*fld_e327);  // 帧对象析构（帧数组 + 元素数组）
        sub_657740(v5, 228);  // 池化结点弹出（写魔术标记后挂入链头）
      }
      *fld_e327++ = nullptr;
    }
    while ( fld_e327 != *(this + 328) );  // this+1312〔pRowVec1312〕
  }
}



// ------------------------------------------------------------
// 0x4EF2E0 sub_4EF2E0 —— 属性行零值化
// 属性行零值化（供 ·0x4EF9D0 的栈模板）：逐字段清 +44..+124，经 ·sub_4A2FF0（结构体清零 + 两 vector 释放）重置 +4 子块后再清一遍尾部字段，返回自身。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EF2E0(uint32_t *this)  // 实现：属性行零值化
{
  void *pThis_1; // ebx

  pThis_1 = this + 1;
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *(this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *(this + 17) = 0;  // this+68〔nCharCount(推断)〕
  sub_4A2FF0(this + 1);  // this+4〔宿主对象〕
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 19) = 0;  // this+76〔pBtnActionE〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 20) = 0;  // this+80〔nAuraStage(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *(this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 29) = 0;  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  *this = 0;
  sub_4A2FF0(pThis_1);
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 19) = 0;  // this+76〔pBtnActionE〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 20) = 0;  // this+80〔nAuraStage(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *(this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *(this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 29) = 0;  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  return this;
}



// ------------------------------------------------------------
// 0x4EF390 sub_4EF390 —— 124B 行区间前拷构（新缓冲版）
// 124 字节行区间前拷构（新缓冲版）：读 [pArg1,uArg2) 写 uArg3 起（9 标量 + ·sub_4ED6A0 头部 + 尾 52B），返回尾指针 —— ·0x4EF5A0 扩容拼装与中段腾挪用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4EF390(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：124B 行区间前拷构（新缓冲版）
{
  uint32_t *uArg32; // ebx
  uint32_t *pArg12; // esi
  uint32_t v6[6]; // [esp+0h] [ebp-24h] BYREF
  int v7; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  v6[5] = v6;
  v6[4] = uArg3;
  v7 = 0;
  while ( 1 )  // 条件循环
  {
    pArg12 = pArg1;
    if ( pArg1 == uArg2 )  // 若 pArg1 == uArg2
      break;  // 跳出循环/分支
    v6[3] = uArg32;
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
    {
      *uArg32 = *pArg1;
      sub_4ED6A0(uArg32 + 1, pArg1 + 1);  // 属性条目头部拷构（64 字节）
      qmemcpy(uArg32 + 18, pArg1 + 18, 0x34u);
      pArg12 = pArg1;
    }
    uArg32 += 31;
    LOBYTE(v7) = 0;
    pArg1 = pArg12 + 31;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4EF450 sub_4EF450 —— 124B 行区间填充（单条模板）
// 124 字节行区间填充：单条模板 pArg3 反复写 nArg2 次（步进 124），返回 0 —— ·0x4EF5A0 扩容中段用。
// ------------------------------------------------------------
int /*cdecl*/ sub_4EF450(uint32_t *uArg1, int nArg2, uint32_t *pArg3)  // 实现：124B 行区间填充（单条模板）
{
  uint32_t *uArg12; // ebx
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  uArg12 = uArg1;
  v5[5] = v5;
  v5[4] = uArg1;
  v6 = 0;
  while ( 1 )  // 条件循环
  {
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
      break;  // 跳出循环/分支
    v5[3] = uArg12;
    LOBYTE(v6) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 有效（非空）
    {
      *uArg12 = *pArg3;
      sub_4ED6A0(uArg12 + 1, pArg3 + 1);  // 属性条目头部拷构（64 字节）
      qmemcpy(uArg12 + 18, pArg3 + 18, 0x34u);
    }
    uArg12 += 31;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4EF510 sub_4EF510 —— 124B 行区间填充转发
// 区间填充的 stdcall 薄转发：·sub_4EF450 后返回尾指针 &pArg1[31*nArg2]。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4EF510(uint32_t *pArg1, int nArg2, uint32_t *uArg3)  // 实现：124B 行区间填充转发
{
  sub_4EF450(pArg1, nArg2, uArg3);  // 124B 行区间填充（单条模板）
  return &pArg1[31 * nArg2];
}



// ------------------------------------------------------------
// 0x4EF540 sub_4EF540 —— 124B 行向量区间擦除
// 124 字节行向量区间擦除：尾段经 ·sub_4EE190 前移覆盖 [uArg3,uArg4)，残留槽位逐条 ·sub_4BA910（CNRDEquipment 随从子对象）析构，尾指针回退至拷贝终点；*uArg2 输出新迭代器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4EF540(uint32_t **this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4)  // 实现：124B 行向量区间擦除
{
  uint32_t *uArg32; // ecx
  void ***fld_e2; // eax
  void ***fld_e22; // ebx
  void ***fld_e23; // edi
  void ***i; // esi
  uint32_t **pThis; // [esp+4h] [ebp-4h]

  uArg32 = uArg3;
  pThis = this;
  if ( uArg3 != uArg4 )  // 若 uArg3 != uArg4
  {
    fld_e2 = (void ***)sub_4EE190(uArg4, *(this + 2), uArg3);  // 124B 行区间前拷构
    fld_e22 = (void ***)*(this + 2);  // this+8〔nSkillRec8(推断)〕
    fld_e23 = fld_e2;
    for ( i = fld_e2; i != fld_e22; i += 31 )  // 遍历循环
      sub_4BA910(i);  // CNRDEquipment 随从子对象析构（+144/+0 两槽）
    uArg32 = uArg3;
    pThis[2] = fld_e23;
  }
  *uArg2 = uArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4EF5A0 sub_4EF5A0 —— ★ 124B 行向量区间插入（模板填充）
// ★ 124 字节行向量区间插入（以模板行填充 uArg3 份）：栈模板行由 +0 标量 + ·sub_4ED6A0 头部 + 尾 52B qmemcpy 组装；
// 空间足：尾段 ·sub_4EF390 上移 + 空槽 ·sub_4EE4C0 模板铺满；空间不足：operator new(124×n) 三段拼装（前 ·sub_4EF390 / 中 ·sub_4EF450 / 后 ·sub_4EF390）后释放旧缓冲；元素数经 ·sub_4EAF80/(+8−+4)/124 计算，超长由 ·sub_4B2F20 抛出；
// 收尾栈临时行 ·sub_4B5A50/·sub_4A4940 析构。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF5A0(int this, char *pszArg2, unsigned int uArg3, int *pDwArg4)  // 实现：124B 行向量区间插入（模板填充）
{
  int v4; // eax
  int fld_4; // edi
  unsigned int fld_C; // ecx
  int fld_8; // eax
  int fld_82; // eax
  unsigned int v11; // ecx
  int fld_87; // eax
  char *pMem; // edi
  int fld_43; // eax
  unsigned int v15; // esi
  void ***fld_44; // eax
  uint32_t *fld_83; // ecx
  int fld_86; // edx
  uint32_t *fld_42; // [esp-18h] [ebp-B8h]
  uint32_t *fld_85; // [esp-Ch] [ebp-ACh]
  int fld_84; // [esp-8h] [ebp-A8h]
  int v23; // [esp+0h] [ebp-A0h] BYREF
  int v24; // [esp+Ch] [ebp-94h] BYREF
  uint32_t v25[17]; // [esp+10h] [ebp-90h] BYREF
  void **v26[14]; // [esp+54h] [ebp-4Ch] BYREF
  void *Block; // [esp+8Ch] [ebp-14h]
  int *v28; // [esp+90h] [ebp-10h]
  int v29; // [esp+9Ch] [ebp-4h]
  uint32_t *v30; // [esp+A8h] [ebp+8h]
  uint32_t *v31; // [esp+ACh] [ebp+Ch]
  int v32; // [esp+B0h] [ebp+10h]

  v4 = *pDwArg4;
  v28 = &v23;
  v26[13] = (void **)this;
  v24 = v4;
  sub_4ED6A0(v25, pDwArg4 + 1);  // 属性条目头部拷构（64 字节）
  qmemcpy(v26, pDwArg4 + 18, 0x34u);
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  fld_C = 0;
  v29 = 0;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 124;  // this+12〔nSkillRec12(推断)〕等 2 字段
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;  // this+8〔nSkillRec8(推断)〕等 4 字段
    else  // 否则分支
      fld_8 = 0;
    if ( 34636833 - fld_8 < uArg3 )
      sub_4B2F20(this);  // vector 长度超限抛出
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      fld_82 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;  // this+8〔nSkillRec8(推断)〕等 4 字段
    else  // 否则分支
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t **)(this + 8);  // fld_83 = 读 this+8
      Block = fld_83;
      if ( ((char *)fld_83 - pszArg2) / 124 >= uArg3 )
      {
        v30 = &fld_83[-31 * uArg3];
        *(uint32_t *)(this + 8) = sub_4EF390(v30, fld_83, fld_83);  // 124B 行区间前拷构（新缓冲版）
        sub_4EE560((int)pszArg2, (int)v30, (int)Block);  // 124B 行区间后拷构转发
        sub_4EE4C0(pszArg2, &pszArg2[124 * uArg3], &v24);  // 124B 行区间填充
      }
      else  // 否则分支
      {
        sub_4EF390(pszArg2, fld_83, &pszArg2[124 * uArg3]);  // 124B 行区间前拷构（新缓冲版）
        fld_84 = uArg3 - (*(uint32_t *)(this + 8) - (int)pszArg2) / 124;  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t **)(this + 8);  // fld_85 = 读 this+8
        LOBYTE(v29) = 3;
        sub_4EF510(fld_85, fld_84, &v24);  // 124B 行区间填充转发
        fld_86 = 124 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // this+8〔nSkillRec8(推断)〕等 2 字段
        v29 = 0;
        sub_4EE4C0(pszArg2, (uint32_t *)(fld_86 - 124 * uArg3), &v24);  // 124B 行区间填充
      }
    }
    else  // 否则分支
    {
      if ( 34636833 - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else  // 否则分支
        v11 = 0;
      if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
        fld_87 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 124;  // this+8〔nSkillRec8(推断)〕等 4 字段
      else  // 否则分支
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
        v11 = uArg3 + sub_4EAF80((int *)this);  // 元素个数 =（+8 − +4）/124
      v32 = 124 * v11;
      pMem = (char *)operator new(124 * v11);
      fld_42 = *(uint32_t **)(this + 4);  // fld_42 = 读 this+4
      Block = pMem;
      LOBYTE(v29) = 1;
      v31 = sub_4EF390(fld_42, pszArg2, pMem);  // 124B 行区间前拷构（新缓冲版）
      sub_4EF450(v31, uArg3, &v24);  // 124B 行区间填充（单条模板）
      sub_4EF390(pszArg2, *(uint32_t **)(this + 8), &v31[31 * uArg3]);  // 124B 行区间前拷构（新缓冲版）
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      v29 = 0;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 124;  // this+8〔nSkillRec8(推断)〕等 2 字段
      v15 = fld_43 + uArg3;
      fld_44 = *(void ****)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
      if ( fld_44 != nullptr )  // 若 fld_44 有效（非空）
      {
        sub_4BA960(fld_44, *(void ****)(this + 8));  // ·0x4BA910 区间逐条调用（步长 31）
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      }
      *(uint32_t *)(this + 12) = &pMem[v32];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[124 * v15];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
    }
  }
  v29 = 5;
  sub_4B5A50(v26);  // 帧对象数组析构（·0x42AF90 后 228 字节池回收）
  v29 = -1;
  sub_4A4940((int)v25);  // 调 析构 —— ·0x4EF9D0 按动画行数对齐 +1288 行向量
}


// ------------------------------------------------------------
// 0x4EF8F0 sub_4EF8F0 —— 124B 行向量 resize
// 124 字节行向量 resize（按 a2）：缩短走 ·sub_4EF540 尾段擦除，伸走 ·sub_4EF5A0 以 by-value 栈模板行补足；栈临时行仍经 ·sub_4B5A50/·sub_4A4940 析构 —— ·0x4EF9D0 按动画行数对齐 +1288 行向量。
// ------------------------------------------------------------
void /*thiscall*/ sub_4EF8F0(  // 124B 行向量 resize
        int this,
        unsigned int a2,
        int a3,
        char a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        void **a21,
        int a22,
        int a23,
        int a24,
        int a25,
        int a26,
        int a27,
        int a28,
        int a29,
        int a30,
        int a31,
        int a32,
        int a33)
{
  int v33; // ebx
  unsigned int v34; // eax
  int v35; // eax

  v33 = *(uint32_t *)(this + 4);  // v33 = 读 this+4
  v34 = 0;
  if ( v33 != 0 )  // 若 v33 非 0
    v34 = (*(uint32_t *)(this + 8) - v33) / 124;  // this+8〔nSkillRec8(推断)〕等 2 字段
  if ( v34 >= a2 )  // 若 v34 >= a2
  {
    if ( v33 != 0 && a2 < (*(uint32_t *)(this + 8) - v33) / 124 )  // 若 v33 != 0
      sub_4EF540((uint32_t **)this, &a2, (uint32_t *)(v33 + 124 * a2), *(uint32_t **)(this + 8));  // 124B 行向量区间擦除
  }
  else  // 否则分支
  {
    if ( v33 != 0 )  // 若 v33 非 0
      v35 = (*(uint32_t *)(this + 8) - v33) / 124;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      v35 = 0;
    sub_4EF5A0(this, *(char **)(this + 8), a2 - v35, &a3);  // 124B 行向量区间插入（模板填充）
  }
  sub_4B5A50(&a21);  // 帧对象数组析构（·0x42AF90 后 228 字节池回收）
  sub_4A4940((int)&a4);  // 调 析构 —— ·0x4EF9D0 按动画行数对齐 +1288 行向量
}



// ------------------------------------------------------------
// 0x4EF9D0 sub_4EF9D0 —— ★ 动画件装配主体（惰性一次）
// ★ 动画件装配主体（694 行，+1320 惰性一次门）：定义 +1332 的 +1056 动画行表按行数（magic 除 124）经 ·sub_4EF2E0 栈模板 + ·sub_4EF8F0 对齐 +1288 行向量；
// 逐行：行首字段拷贝 → 20 余个串槽（+1..+22）与 +24/+28 两向列表逐项 ·sub_42FD40/strcmp 哨兵比对（串经 ·sub_41ACF0），非空即 ·sub_42FCB0 + ·sub_4319E0 动画件构造挂入行槽，向列表哨兵位写 0 占位、非哨兵经 ·sub_699070(2) 绑定时钟域后入表；
// 末段定义 +20 向量（图集 +1088 下的公共动画【推断】）逐条 ·sub_431920 造件推入 +1304，完成置 +1320=1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4EF9D0(int this)  // 实现：动画件装配主体（惰性一次）
{
  int *fld_534; // eax
  int v3; // edx
  int v4; // esi
  unsigned int v5; // edx
  char *fld_50C; // edx
  uint32_t *fld_5342; // edi
  int v8; // eax
  int pEquipDef1332; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v10; // eax
  int pAnimAtlas1324; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int pEquipDef1332_; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v13; // esi
  const char *v14; // eax
  int pAnimAtlas1324_; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v16; // edi
  int pEquipDef1332_2; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v18; // esi
  const char *v19; // eax
  int pAnimAtlas1324_2; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v21; // edi
  int pEquipDef1332_3; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v23; // esi
  const char *v24; // eax
  int pAnimAtlas1324_3; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  bool v26; // zf
  int v27; // edi
  int pEquipDef1332_4; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v29; // esi
  const char *v30; // eax
  int pAnimAtlas1324_4; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v32; // edi
  int pEquipDef1332_5; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v34; // esi
  const char *v35; // eax
  int pAnimAtlas1324_5; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v37; // edi
  int pEquipDef1332_6; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v39; // esi
  const char *v40; // eax
  int pAnimAtlas1324_6; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v42; // edi
  int pEquipDef1332_7; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v44; // esi
  const char *v45; // eax
  int pAnimAtlas1324_7; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v47; // edi
  int pEquipDef1332_8; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v49; // esi
  const char *v50; // eax
  int pAnimAtlas1324_8; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v52; // edi
  int pEquipDef1332_9; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v54; // esi
  const char *v55; // eax
  int pAnimAtlas1324_9; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v57; // edi
  int pEquipDef1332_10; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v59; // esi
  const char *v60; // eax
  int pAnimAtlas1324_10; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v62; // edi
  int pEquipDef1332_11; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v64; // esi
  const char *v65; // eax
  int pAnimAtlas1324_11; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v67; // edi
  int pEquipDef1332_12; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v69; // esi
  const char *v70; // eax
  int pAnimAtlas1324_12; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v72; // edi
  int pEquipDef1332_13; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v74; // esi
  const char *v75; // eax
  int pAnimAtlas1324_13; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v77; // edi
  int pEquipDef1332_14; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v79; // esi
  const char *v80; // eax
  int pAnimAtlas1324_14; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v82; // edi
  int pEquipDef1332_15; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v84; // esi
  const char *v85; // eax
  int pAnimAtlas1324_15; // eax  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int v87; // esi
  int v88; // ecx
  unsigned int v89; // edi
  int *fld_52C162; // edx
  int v91; // esi
  unsigned int v92; // edx
  uint32_t *v93; // eax
  uint32_t *v94; // edx
  int v95; // edi
  int pEquipDef1332_16; // eax  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  const char *v97; // esi
  const char *v98; // eax
  int pAnimAtlas1324_16; // esi  | +0x052C → 动画图集对象（CNRDEquipment；va=004EF9D0）
  int fld_534322; // ecx
  int v101; // edx
  unsigned int v102; // edi
  int *fld_52C172; // eax
  int v104; // esi
  unsigned int v105; // edx
  uint32_t *v106; // eax
  uint32_t *v107; // edx
  char pEquipDef1332_17; // al  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  char fld_534202; // si
  char v110; // al
  int v111; // eax
  int pRowVec1308; // esi  | +0x051C → 动画行向量 begin（CNRDEquipment；va=004EF9D0）
  unsigned int pRowVec1312; // edi  | +0x0520 → 动画行向量 end（CNRDEquipment；va=004EF9D0）
  int *fld_5202; // edx
  int pEquipDef1332_18; // edx  | +0x0534 → 装备/动画定义对象（CNRDEquipment；va=004EF9D0）
  int v117[30]; // [esp-7Ch] [ebp-B4h] BYREF
  int v118; // [esp-4h] [ebp-3Ch]
  int v119; // [esp+Ch] [ebp-2Ch]
  int v120; // [esp+10h] [ebp-28h] BYREF
  int fld_53432; // [esp+14h] [ebp-24h] BYREF
  int v122; // [esp+18h] [ebp-20h]
  int fld_52C112; // [esp+1Ch] [ebp-1Ch] BYREF
  uint32_t *v124; // [esp+20h] [ebp-18h]
  char *fld_50C2; // [esp+24h] [ebp-14h]
  uint32_t *fld_53422; // [esp+28h] [ebp-10h]
  int v127; // [esp+34h] [ebp-4h]

  LOBYTE(fld_534) = *(uint8_t *)(this + 1320);  // this+1320〔bAnimBuilt1320〕
  if ( (uint8_t)fld_534 == 0 )
  {
    fld_534 = *(int **)(this + 1332);  // this+1332〔pEquipDef1332〕
    if ( fld_534 != nullptr )  // 若 fld_534 有效（非空）
    {
      v3 = fld_534[264];  // v3 = 取 fld_534[264]
      if ( v3 != 0 )  // 若 v3 非 0
      {
        v5 = (int)((uint64_t)(2216757315LL * (fld_534[265] - v3)) >> 32) >> 6;
        v4 = v5 + (v5 >> 31);
      }
      else  // 否则分支
      {
        v4 = 0;
      }
      v120 = v4;
      fld_53432 = (int)v117;
      sub_4EF2E0(v117);  // 属性行零值化
      sub_4EF8F0(  // 124B 行向量 resize
        this + 1288,
        v4,
        v117[0],
        v117[1],
        v117[2],
        v117[3],
        v117[4],
        v117[5],
        v117[6],
        v117[7],
        v117[8],
        v117[9],
        v117[10],
        v117[11],
        v117[12],
        v117[13],
        v117[14],
        v117[15],
        v117[16],
        v117[17],
        v117[18],
        v117[19],
        v117[20],
        v117[21],
        v117[22],
        v117[23],
        v117[24],
        v117[25],
        v117[26],
        v117[27],
        v117[28],
        v117[29],
        v118);
      v122 = 0;
      if ( v4 > 0 )  // 若 v4 > 0
      {
        while ( 1 )  // 条件循环
        {
          fld_50C = (char *)(124 * v122 + *(uint32_t *)(this + 1292));  // this+1292〔pAnimRow1292〕
          fld_5342 = (uint32_t *)(124 * v122 + *(uint32_t *)(*(uint32_t *)(this + 1332) + 1056));  // this+1332〔pEquipDef1332〕
          v8 = *fld_5342;
          v118 = (int)szPassword;
          fld_50C2 = fld_50C;
          fld_53422 = fld_5342;
          *(uint32_t *)fld_50C = v8;
          if ( (uint8_t)sub_42FD40(v118) != 0 )  // 字符串不等判定
          {
            fld_52C112 = sub_42FCB0(228);  // CRT 一次性初始化
            v127 = 0;
            if ( fld_52C112 != 0 )  // 若 fld_52C112 非 0
            {
              pEquipDef1332 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              fld_53432 = pEquipDef1332;
              v10 = (const char *)sub_41ACF0(fld_5342 + 1);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324 = sub_4319E0(fld_52C112, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), (const char *)fld_53432, v10, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 1) = pAnimAtlas1324;
          }
          if ( (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
          {
            fld_53432 = sub_42FCB0(228);  // CRT 一次性初始化
            v127 = 1;
            if ( fld_53432 != 0 )  // 若 fld_53432 非 0
            {
              pEquipDef1332_ = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v13 = (const char *)pEquipDef1332_;
              v14 = (const char *)sub_41ACF0(fld_5342 + 2);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_ = sub_4319E0(fld_53432, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v13, v14, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_ = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 2) = pAnimAtlas1324_;
          }
          if ( (uint8_t)sub_42FD40(szPassword) != 0 )  // 字符串不等判定
          {
            v16 = sub_42FCB0(228);  // CRT 一次性初始化
            fld_53432 = v16;
            v127 = 2;
            if ( v16 != 0 )  // 若 v16 非 0
            {
              pEquipDef1332_2 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v18 = (const char *)pEquipDef1332_2;
              v19 = (const char *)sub_41ACF0(fld_53422 + 3);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_2 = sub_4319E0(v16, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v18, v19, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_2 = 0;
            }
            fld_5342 = fld_53422;
            v127 = -1;
            *((uint32_t *)fld_50C2 + 3) = pAnimAtlas1324_2;
          }
          v124 = fld_5342 + 4;
          fld_53432 = fld_50C2 - (char *)fld_5342;
          fld_52C112 = 2;
          do  // do-while 循环体起点
          {
            if ( strcmp((const char *)sub_41ACF0(v124), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
            {
              v21 = sub_42FCB0(228);  // CRT 一次性初始化
              v119 = v21;
              v127 = 3;
              if ( v21 != 0 )  // 若 v21 非 0
              {
                pEquipDef1332_3 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
                v118 = 1;
                v23 = (const char *)pEquipDef1332_3;
                v24 = (const char *)sub_41ACF0(v124);  // 驻留串句柄 → 字符串指针
                pAnimAtlas1324_3 = sub_4319E0(v21, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v23, v24, v118);  // 动画件构造（文件名与参数版）
              }
              else  // 否则分支
              {
                pAnimAtlas1324_3 = 0;
              }
              v127 = -1;
              *(uint32_t *)((char *)v124 + fld_53432) = pAnimAtlas1324_3;
            }
            v26 = fld_52C112 == 1;
            ++v124;
            --fld_52C112;
          }
          while ( !v26 );  // 条件循环
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 6), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v27 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v27;
            v127 = 4;
            if ( v27 != 0 )  // 若 v27 非 0
            {
              pEquipDef1332_4 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v29 = (const char *)pEquipDef1332_4;
              v30 = (const char *)sub_41ACF0(fld_53422 + 6);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_4 = sub_4319E0(v27, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v29, v30, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_4 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 6) = pAnimAtlas1324_4;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 7), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v32 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v32;
            v127 = 5;
            if ( v32 != 0 )  // 若 v32 非 0
            {
              pEquipDef1332_5 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v34 = (const char *)pEquipDef1332_5;
              v35 = (const char *)sub_41ACF0(fld_53422 + 7);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_5 = sub_4319E0(v32, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v34, v35, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_5 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 7) = pAnimAtlas1324_5;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 8), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v37 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v37;
            v127 = 6;
            if ( v37 != 0 )  // 若 v37 非 0
            {
              pEquipDef1332_6 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v39 = (const char *)pEquipDef1332_6;
              v40 = (const char *)sub_41ACF0(fld_53422 + 8);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_6 = sub_4319E0(v37, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v39, v40, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_6 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 8) = pAnimAtlas1324_6;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 9), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v42 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v42;
            v127 = 7;
            if ( v42 != 0 )  // 若 v42 非 0
            {
              pEquipDef1332_7 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v44 = (const char *)pEquipDef1332_7;
              v45 = (const char *)sub_41ACF0(fld_53422 + 9);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_7 = sub_4319E0(v42, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v44, v45, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_7 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 9) = pAnimAtlas1324_7;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 10), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v47 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v47;
            v127 = 8;
            if ( v47 != 0 )  // 若 v47 非 0
            {
              pEquipDef1332_8 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v49 = (const char *)pEquipDef1332_8;
              v50 = (const char *)sub_41ACF0(fld_53422 + 10);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_8 = sub_4319E0(v47, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v49, v50, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_8 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 18) = pAnimAtlas1324_8;
          }
          fld_52C112 = (int)(fld_50C2 + 92);
          v124 = fld_53422 + 15;
          fld_53432 = 4;
          do  // do-while 循环体起点
          {
            if ( strcmp((const char *)sub_41ACF0(v124 - 4), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
            {
              v52 = sub_42FCB0(228);  // CRT 一次性初始化
              v119 = v52;
              v127 = 9;
              if ( v52 != 0 )  // 若 v52 非 0
              {
                pEquipDef1332_9 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
                v118 = 1;
                v54 = (const char *)pEquipDef1332_9;
                v55 = (const char *)sub_41ACF0(v124 - 4);  // 驻留串句柄 → 字符串指针
                pAnimAtlas1324_9 = sub_4319E0(v52, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v54, v55, v118);  // 动画件构造（文件名与参数版）
              }
              else  // 否则分支
              {
                pAnimAtlas1324_9 = 0;
              }
              v127 = -1;
              *(uint32_t *)(fld_52C112 - 16) = pAnimAtlas1324_9;
            }
            if ( strcmp((const char *)sub_41ACF0(v124), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
            {
              v57 = sub_42FCB0(228);  // CRT 一次性初始化
              v119 = v57;
              v127 = 10;
              if ( v57 != 0 )  // 若 v57 非 0
              {
                pEquipDef1332_10 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
                v118 = 1;
                v59 = (const char *)pEquipDef1332_10;
                v60 = (const char *)sub_41ACF0(v124);  // 驻留串句柄 → 字符串指针
                pAnimAtlas1324_10 = sub_4319E0(v57, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v59, v60, v118);  // 动画件构造（文件名与参数版）
              }
              else  // 否则分支
              {
                pAnimAtlas1324_10 = 0;
              }
              v127 = -1;
              *(uint32_t *)fld_52C112 = pAnimAtlas1324_10;
            }
            v26 = fld_53432 == 1;
            ++v124;
            fld_52C112 += 4;
            --fld_53432;
          }
          while ( !v26 );  // 条件循环
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 19), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v62 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v62;
            v127 = 11;
            if ( v62 != 0 )  // 若 v62 非 0
            {
              pEquipDef1332_11 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v64 = (const char *)pEquipDef1332_11;
              v65 = (const char *)sub_41ACF0(fld_53422 + 19);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_11 = sub_4319E0(v62, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v64, v65, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_11 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 27) = pAnimAtlas1324_11;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 20), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v67 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v67;
            v127 = 12;
            if ( v67 != 0 )  // 若 v67 非 0
            {
              pEquipDef1332_12 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v69 = (const char *)pEquipDef1332_12;
              v70 = (const char *)sub_41ACF0(fld_53422 + 20);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_12 = sub_4319E0(v67, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v69, v70, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_12 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 28) = pAnimAtlas1324_12;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 21), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v72 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v72;
            v127 = 13;
            if ( v72 != 0 )  // 若 v72 非 0
            {
              pEquipDef1332_13 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v74 = (const char *)pEquipDef1332_13;
              v75 = (const char *)sub_41ACF0(fld_53422 + 21);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_13 = sub_4319E0(v72, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v74, v75, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_13 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 29) = pAnimAtlas1324_13;
          }
          if ( strcmp((const char *)sub_41ACF0(fld_53422 + 22), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v77 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v77;
            v127 = 14;
            if ( v77 != 0 )  // 若 v77 非 0
            {
              pEquipDef1332_14 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v79 = (const char *)pEquipDef1332_14;
              v80 = (const char *)sub_41ACF0(fld_53422 + 22);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_14 = sub_4319E0(v77, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v79, v80, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_14 = 0;
            }
            v127 = -1;
            *((uint32_t *)fld_50C2 + 30) = pAnimAtlas1324_14;
          }
          v26 = fld_53422[24] == fld_53422[25];
          v124 = (uint32_t *)fld_53422[24];
          if ( !v26 )
          {
            do  // do-while 循环体起点
            {
              if ( strcmp((const char *)sub_41ACF0(v124), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
              {
                v91 = *((uint32_t *)fld_50C2 + 11);
                v88 = (int)(fld_50C2 + 40);
                fld_53432 = 0;
                if ( v91 != 0 )  // 若 v91 非 0
                  v92 = (*((uint32_t *)fld_50C2 + 12) - v91) >> 2;  // 向量元素数 = (end−begin)/4
                else  // 否则分支
                  v92 = 0;
                if ( v91 == 0 || v92 >= (*((uint32_t *)fld_50C2 + 13) - v91) >> 2 )  // 若 v91 == 0
                {
LABEL_103:  // 标签 LABEL_103（跳转合流点）
                  sub_42AC90(v88, *(char **)(v88 + 8), 1u, &fld_53432);  // 向量批量插入核心
                  goto LABEL_104;
                }
                v93 = *((uint32_t **)fld_50C2 + 12);
                *v93 = 0;
                *(uint32_t *)(v88 + 8) = v93 + 1;
              }
              else  // 否则分支
              {
                v82 = sub_42FCB0(228);  // CRT 一次性初始化
                v119 = v82;
                v127 = 15;
                if ( v82 != 0 )  // 若 v82 非 0
                {
                  pEquipDef1332_15 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
                  v118 = 1;
                  v84 = (const char *)pEquipDef1332_15;
                  v85 = (const char *)sub_41ACF0(v124);  // 驻留串句柄 → 字符串指针
                  pAnimAtlas1324_15 = sub_4319E0(v82, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v84, v85, v118);  // 动画件构造（文件名与参数版）
                }
                else  // 否则分支
                {
                  pAnimAtlas1324_15 = 0;
                }
                v87 = *((uint32_t *)fld_50C2 + 11);
                v88 = (int)(fld_50C2 + 40);
                v127 = -1;
                fld_53432 = pAnimAtlas1324_15;
                if ( v87 != 0 )  // 若 v87 非 0
                  v89 = (*((uint32_t *)fld_50C2 + 12) - v87) >> 2;  // 向量元素数 = (end−begin)/4
                else  // 否则分支
                  v89 = 0;
                if ( v87 == 0 || v89 >= (*((uint32_t *)fld_50C2 + 13) - v87) >> 2 )  // 若 v87 == 0
                  goto LABEL_103;
                fld_52C162 = *((int **)fld_50C2 + 12);
                *fld_52C162 = pAnimAtlas1324_15;
                *(uint32_t *)(v88 + 8) = fld_52C162 + 1;
              }
LABEL_104:  // 标签 LABEL_104（跳转合流点）
              v94 = (uint32_t *)fld_53422[25];
              ++v124;
            }
            while ( v124 != v94 );  // 条件循环
          }
          v26 = fld_53422[28] == fld_53422[29];
          v124 = (uint32_t *)fld_53422[28];
          if ( !v26 )
            break;  // 跳出循环/分支
LABEL_125:  // 标签 LABEL_125（跳转合流点）
          if ( ++v122 >= v120 )
            goto LABEL_126;
        }
        fld_53432 = (int)(fld_50C2 + 56);
        while ( 1 )  // 条件循环
        {
          if ( strcmp((const char *)sub_41ACF0(v124), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
          {
            fld_534322 = fld_53432;
            v104 = *(uint32_t *)(fld_53432 + 4);
            fld_52C112 = 0;
            if ( v104 != 0 )  // 若 v104 非 0
              v105 = (*(uint32_t *)(fld_53432 + 8) - v104) >> 2;  // 向量元素数 = (end−begin)/4
            else  // 否则分支
              v105 = 0;
            if ( v104 == 0 || v105 >= (*(uint32_t *)(fld_53432 + 12) - v104) >> 2 )  // 若 v104 == 0
            {
LABEL_123:  // 标签 LABEL_123（跳转合流点）
              sub_42AC90(fld_534322, *(char **)(fld_534322 + 8), 1u, &fld_52C112);  // 向量批量插入核心
              goto LABEL_124;
            }
            v106 = *(uint32_t **)(fld_53432 + 8);
            *v106 = 0;
            *(uint32_t *)(fld_534322 + 8) = v106 + 1;
          }
          else  // 否则分支
          {
            v95 = sub_42FCB0(228);  // CRT 一次性初始化
            v119 = v95;
            v127 = 16;
            if ( v95 != 0 )  // 若 v95 非 0
            {
              pEquipDef1332_16 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              v97 = (const char *)pEquipDef1332_16;
              v98 = (const char *)sub_41ACF0(v124);  // 驻留串句柄 → 字符串指针
              pAnimAtlas1324_16 = sub_4319E0(v95, *(uint32_t *)(this + 1324), *(uint32_t *)(this + 1328), v97, v98, v118);  // 动画件构造（文件名与参数版）
            }
            else  // 否则分支
            {
              pAnimAtlas1324_16 = 0;
            }
            v127 = -1;
            fld_52C112 = pAnimAtlas1324_16;
            sub_699070(2);  // 【clock_bind_domain(clk, newDomainId)】
            fld_534322 = fld_53432;
            v101 = *(uint32_t *)(fld_53432 + 4);
            if ( v101 != 0 )  // 若 v101 非 0
              v102 = (*(uint32_t *)(fld_53432 + 8) - v101) >> 2;  // 向量元素数 = (end−begin)/4
            else  // 否则分支
              v102 = 0;
            if ( v101 == 0 || v102 >= (*(uint32_t *)(fld_53432 + 12) - v101) >> 2 )  // 若 v101 == 0
              goto LABEL_123;
            fld_52C172 = *(int **)(fld_53432 + 8);
            *fld_52C172 = pAnimAtlas1324_16;
            *(uint32_t *)(fld_534322 + 8) = fld_52C172 + 1;
          }
LABEL_124:  // 标签 LABEL_124（跳转合流点）
          v107 = (uint32_t *)fld_53422[29];
          if ( ++v124 == v107 )
            goto LABEL_125;
        }
      }
LABEL_126:  // 标签 LABEL_126（跳转合流点）
      fld_534 = *(int **)(this + 1332);  // this+1332〔pEquipDef1332〕
      v26 = fld_534[20] == fld_534[21];
      fld_52C112 = fld_534[20];  // fld_52C112 = 取 fld_534[20]
      if ( !v26 )
      {
        do  // do-while 循环体起点
        {
          if ( strcmp((const char *)sub_41ACF0(fld_52C112), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
          {
            v119 = sub_42FCB0(228);  // CRT 一次性初始化
            v127 = 17;
            if ( v119 != 0 )  // 若 v119 非 0
            {
              pEquipDef1332_17 = sub_41ACF0(*(uint32_t *)(this + 1332) + 1088);  // 驻留串句柄 → 字符串指针
              v118 = 1;
              fld_534202 = pEquipDef1332_17;
              v110 = sub_41ACF0(fld_52C112);  // 驻留串句柄 → 字符串指针
              v111 = sub_431920(fld_534202, v110, v118);  // 动画件构造（文件名版）
            }
            else  // 否则分支
            {
              v111 = 0;
            }
            pRowVec1308 = *(uint32_t *)(this + 1308);  // this+1308〔pRowVec1308〕
            v127 = -1;
            v120 = v111;
            if ( pRowVec1308 != 0 )  // 若 fld_51C 非 0
              pRowVec1312 = (*(uint32_t *)(this + 1312) - pRowVec1308) >> 2;  // this+1312〔pRowVec1312〕
            else  // 否则分支
              pRowVec1312 = 0;
            if ( pRowVec1308 != 0 && pRowVec1312 < (*(uint32_t *)(this + 1316) - pRowVec1308) >> 2 )  // this+1316〔pRowVec1316〕
            {
              fld_5202 = *(int **)(this + 1312);  // this+1312〔pRowVec1312〕
              *fld_5202 = v111;
              *(uint32_t *)(this + 1312) = fld_5202 + 1;  // this+1312〔pRowVec1312〕
            }
            else  // 否则分支
            {
              sub_42AC90(this + 1304, *(char **)(this + 1312), 1u, &v120);  // 向量批量插入核心
            }
          }
          pEquipDef1332_18 = *(uint32_t *)(*(uint32_t *)(this + 1332) + 84);  // this+1332〔pEquipDef1332〕
          LOBYTE(fld_534) = fld_52C112 + 4;
          fld_52C112 += 4;
        }
        while ( fld_52C112 != pEquipDef1332_18 );  // 条件循环
      }
      *(uint8_t *)(this + 1320) = 1;  // this+1320〔bAnimBuilt1320〕
    }
  }
  return (char)fld_534;
}


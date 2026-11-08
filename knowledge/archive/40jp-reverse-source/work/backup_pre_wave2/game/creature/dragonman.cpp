// ============================================================
// 【40JP逆向源代码工程】creature/dragonman.cpp
// 模块: 怪物AI 0x5B —— 龙人(Draconian)/光之城主赛格哈特/空骨鱼/ZGM/信徒/炮车/飞艇/鬼魂
// 来源: work/dump_monster.txt  区块: 0x5B0000-0x5C0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 233
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：0x5B14D0×4表 / 0x5B2E20×1 / 0x5B7400×9 /
//     0x5B8240×1（虚表农场 0x6CB000-0x6EB000 +512 槽, 纯 Python 直读 PE 定位）；
//     ★ 0x5B4D90×4 表（CNStarFish 系反击 proc 覆写：10%/15%/2% 随机触发 +
//     CNStarFishKing/CNStarFishRukuku RTTI 分型）位于缺口补漏文件 missing_monster.cpp ——
//     本文件 0x5B4820-0x5B6380 缺口区函数均在 missing_monster.cpp（会话 5 审计补齐）
//   · AI 状态：this+200 主状态 / vt+560 反应态 / vt+840=大状态读取器(0x4A1010→this+6556)
//   · 语音 TAG 组（DRAGONMAN_*/ZIEG_*/SFISH_*/BELIEVER_*/WRAITH_*）经 sub_4015C0 写语音槽，
//     vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数表
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_4049C0=帧间插值 /
//     sub_406D60=BGM 曲名槽写入 / sub_493D00=动画变速换锚（研究 26）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】龙人·本体（Draconian / Lakius 鲁卡斯）（0x5B00D0-0x5B1890）
// 证据：DRAGONMAN_ATK/ATK_SHORT/ATK_LONG/CAST/SPARK_LOOP/JAIL/STATIC_READY_LOOP 技能播报、
//       DRGM_SHIELD_LOOP、DLAni/EF_Hallucination{1,2}.ani 幻觉、PassiveObject/MapObject/Trap/
//       Particle/Cage.ptl 囚笼、B_RAKIUS_01 登场曲、Monster/Draconian/Lakius/armor.equ、
//       vmt200 格挡覆写 0x5B14D0（GuardEffect.ani）

// 龙人·压制反击判定（50L）：目标(pArg1[1813])处于受击/浮空/倒地类大状态(8/7/12)、
//   距离<100、自身不在动作22中时，按概率发起 setState(22) 压制技
//   ——概率门：pArg1[1908] 非 0 时 20%，否则 50%（rand()%100 < 阈值）
// ------------------------------------------------------------
// 0x5B00D0 sub_5B00D0 —— 龙人·压制反击概率门（setState 22 起手）
// 前置链：·sub_5AFE80 协同自检 → vt+840 大状态须 0、vt+308 目标门、this+1787 行为字非 22。
// 目标 pArg1[1813] 须存活（vt+40 标记 17），且大状态 8/受击硬直、7/浮空、或（标记 273 且 12/倒地）。
// 距离（vt+8）<100 时按 this+1908 非 0 → 20%、否则 50% 概率，经 vt+1104 写行为字 22。
// ------------------------------------------------------------
int /*usercall*/ sub_5B00D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int pTarget; // edi
  int nRand; // edx
  int result; // eax

  sub_5AFE80();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 大状态读取(vt+840→this+6556)
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家/有目标门(vt+308)
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
      if ( result == 0 && pArg1[1787] != 22 )  // 不在动作22(压制)中
      {
        result = pArg1[1813];  // 当前目标对象【推断：全函数族一致用作攻击目标】
        if ( result != 0 )
        {
          result = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)result + 40))(17);  // 目标存活标记17
          if ( (uint8_t)result != 0 )
          {
            pTarget = pArg1[1813];
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 840))(pTarget, nArg2) == 8  // 目标大状态8(受击硬直)
              || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 840))(pTarget) == 7  // 或7(浮空)
              || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 40))(pTarget, 273)) != 0
              && (result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 840))(pTarget)) == 12 )  // 或标记273+大状态12(倒地)
            {
              result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pTarget, 0);  // 距离(vt+8)
              if ( result < 100 )  // 距离<100 才够得着压制
              {
                nRand = rand() % 100;
                result = pArg1[1908] != 0 ? 20 : 50;  // 概率阈值：20% / 50%
                if ( nRand < result )
                  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 22);  // 发起动作22
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 龙人·提速相位（与 0x5B01C0 互为逆操作）：动画速度表(this+1905 指向)动作速 ×1.3、
//   位移速 ×0.76923(=1/1.3)；nArg2==0 全套生效、nArg2==1 仅降控制柄+830 浮点(0.3)
// ------------------------------------------------------------
// 0x5B00F0 sub_5B00F0 —— 龙人·狂暴提速相位（动作速 ×1.3 / 位移速 ×1-1.3）
// 速度表指针 this[1905]：+4 动作速 ×1.3、+68 位移速 ×0.76923；经 vt+672 取动画控制柄，
// ·sub_41A5E0 读取 +830 浮点减 0.3 后 ·sub_41A590 写回、vt+676 提交。
// nArg2==0 走全套；nArg2==1 且 nArg3==0 只走控制柄分支；与 ·0x5B01C0 互逆。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B00F0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  unsigned int v8; // edi
  int v9; // edx
  int v10; // [esp+14h] [ebp+8h]
  int v11; // [esp+14h] [ebp+8h]

  if ( nArg2 == 0 )
  {
    *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.3;  // 动作速度 ×1.3
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;  // 位移速度 ×1/1.3
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 动画控制柄字段+830【推断：播放速度】
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
    sub_41A590(v5, v6, v10);  // 浮点字段写回(-0.3)
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 提交控制柄
  }
  result = nArg3;
  if ( nArg3 == 0 && nArg2 == 1 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v8)) - 0.30000001;
    sub_41A590(v8, v9, v11);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// 龙人·复位+减速相位（0x5B00F0 的逆操作，65L）：先清零 7531..7558/1891..1899 全套
//   龙人 AI 相位字段（this[1895]=1 唯一置位），再按 nArg2 把速度表还原（动作速 ×1/1.3、
//   位移速 ×1.3、控制柄+830 浮点 +0.3）；this[1899]=50 与提速相位对偶
// ------------------------------------------------------------
// 0x5B01C0 sub_5B01C0 —— 龙人·相位复位与减速（0x5B00F0 逆操作）
// 先批量清零 this+7531..7558 与 this[1891..1899] 两组 AI 相位字段，唯 this[1895]=1【推断：常规相位标志】。
// nArg2==0：速度表 this[1905]+4 ×0.76923、+68 ×1.3 还原，this[1899]=50，控制柄 +830 浮点 +0.3（·sub_41A590 写、vt+676 提交）。
// nArg3==0 且 nArg2==1 时只走控制柄分支。与 ·0x5B00F0 成对，供变身/幻觉相位进出使用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B01C0(char *this, int nArg2, int nArg3)
{
  int result; // eax
  char *pThis_1D73; // ecx
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // eax
  unsigned int v10; // edi
  int v11; // edx
  int v12; // [esp+Ch] [ebp-4h]
  int v13; // [esp+18h] [ebp+8h]

  result = 0;
  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;
  *((uint32_t *)this + 1892) = 0;
  *((uint32_t *)this + 1891) = 0;
  *((uint32_t *)this + 1897) = 0;
  *((uint32_t *)this + 1896) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1899) = 0;
  *((uint32_t *)this + 1895) = 1;  // 相位标志置 1【推断：常规相位】
  if ( nArg2 == 0 )
  {
    *(float *)(*((uint32_t *)this + 1905) + 4) = *(float *)(*((uint32_t *)this + 1905) + 4) * 0.76923078;  // 动作速度还原
    *(float *)(*((uint32_t *)this + 1905) + 68) = *(float *)(*((uint32_t *)this + 1905) + 68) * 1.3;  // 位移速度还原
    v6 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v7 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v6 + 672))(this, 0) + 830;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v12);  // 浮点字段写回(+0.3，与提速相位反向)
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  if ( nArg3 == 0 && nArg2 == 1 )
  {
    v9 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v10 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v9 + 672))(this, 0) + 830;
    *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v10)) + 0.30000001;
    sub_41A590(v10, v11, v13);
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// 龙人·随机位移判定（94L）：遍历 vt+80 挂载对象列表，找存活且视线可达(sub_4E4630/vt+1244)
//   的对象，在 17 个槽位里以每次 1% 概率抽中非空槽后，生成 ±25 随机抖动坐标、
//   经对象 vt+124/120 两级换算后由 vt+584 应用到自身【推断：瞬移/位移技前置】
// ------------------------------------------------------------
// 0x5B0320 sub_5B0320 —— 龙人·挂载物脉冲/位移判定
// 经 vt+80 取挂载对象 vector（+4 begin/+8 end）逐项枚举：对象存活（vt+40 标记 17）、
// 敌我关系（·sub_4E4630）且同房间/视线（vt+1244 ==1）后，在 17 个挂载槽（vt+776）中
// 以每槽 1%（rand()%100<1）抽取非空槽，生成 ±25 抖动坐标，经对象 vt+124/120 换算后
// 由自身 vt+584 应用位移（对象 ID 30071 为挂载物表现参数）【推断：瞬移/脉冲位移技】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0320(int *this)
{
  int *pThis; // ebx
  unsigned int nSlotIdx; // edi
  int pVecHdr; // eax
  int pVecBegin; // ecx
  int pVecHdrB; // eax
  int result; // eax
  int pVecHdr2; // eax
  int pVecBegin2; // edx
  int pListObj; // ecx
  int pVecHdr3; // eax
  int pVecBegin3; // edx
  int pListObj2; // esi
  int nTryIdx; // edi
  int nDx; // edi
  int nRandY; // eax
  int nJumpY; // eax
  int nJumpX; // eax
  int nJumpY2; // eax
  int nJumpX2; // eax
  int pVtSaved; // [esp+Ch] [ebp-10h]
  int nDy; // [esp+14h] [ebp-8h]
  unsigned int nSlotIdxSaved; // [esp+18h] [ebp-4h]

  pThis = this;
  nSlotIdx = 0;
LABEL_2:
  while ( 1 )
  {
    nSlotIdxSaved = nSlotIdx;
    pVecHdr = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);  // 取挂载对象列表(vector: +4 begin/+8 end)
    pVecBegin = *(uint32_t *)(pVecHdr + 8);
    pVecHdrB = pVecHdr + 4;
    result = pVecBegin != 0 ? (*(uint32_t *)(pVecHdrB + 8) - pVecBegin) >> 2 : 0;  // 元素数
    if ( (int)nSlotIdx >= result )
      return result;
    pVecHdr2 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);
    pVecBegin2 = *(uint32_t *)(pVecHdr2 + 8);
    if ( pVecBegin2 != 0 && nSlotIdx < (*(uint32_t *)(pVecHdr2 + 12) - pVecBegin2) >> 2 )
      pListObj = *(uint32_t *)(pVecBegin2 + 4 * nSlotIdx);
    else
      pListObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 17) != 0 )  // 存活标记17
    {
      pVecHdr3 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);
      pVecBegin3 = *(uint32_t *)(pVecHdr3 + 8);
      if ( pVecBegin3 != 0 && nSlotIdx < (*(uint32_t *)(pVecHdr3 + 12) - pVecBegin3) >> 2 )
        pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nSlotIdx);
      else
        pListObj2 = 0;
      if ( (uint8_t)sub_4E4630(pListObj2) != 0
        && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pThis + 1244))(pThis, pListObj2) == 1 )  // 视线/同房间判定【推断】
      {
        nTryIdx = 0;
        while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 776))(pListObj2, nTryIdx) == 0 || rand() % 100 >= 1 )  // 非空槽且 1% 概率
        {
          if ( ++nTryIdx >= 17 )  // 最多试 17 个槽位
          {
            nSlotIdx = nSlotIdxSaved + 1;
            goto LABEL_2;
          }
        }
        nDx = rand() % 50 - 25;  // X 抖动 ±25
        nRandY = rand();
        pVtSaved = *pThis;
        nDy = nRandY % 50 - 25;  // Y 抖动 ±25
        nJumpY = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pListObj2 + 124))(
                pListObj2,
                30071,  // 对象/特效 ID【推断】
                10,
                0,
                4,
                100,
                1,
                0,
                0);
        nJumpX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 120))(pListObj2, nDy + nJumpY);
        nJumpY2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pListObj2 + 124))(pListObj2, 0, nDx + nJumpX);
        nJumpX2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 120))(pListObj2, nDy + nJumpY2);
        pThis = this;
        (*(void (/*thiscall*/ **)(int *, int))(pVtSaved + 584))(this, nDx + nJumpX2);  // 应用位移到自身
        nSlotIdx = nSlotIdxSaved;
      }
    }
    ++nSlotIdx;
  }
}



// 龙人·召唤物激活 AI（92L）：nArg2(目标/宿主对象)存活时，扫其 vt+700 列表找首个
//   有效项(vt+92)激活(vt+76)并响 sub_4DB130(24)；再在 16 个槽位里找类型 16
//   (sub_496F80)的挂载物执行 vt+4(0,this) 绑定；末尾按 this[2160]×2 阈值给
//   控制柄+74 浮点每次 +0.1 递增【推断：体型/强度成长条】
// ------------------------------------------------------------
// 0x5B04A0 sub_5B04A0 —— 龙人·召唤物激活与成长（带反击回退）
// 宿主 nArg2 存活（vt+40 标记 17）时，扫其 vt+700 列表首个有效项（vt+92）经 vt+76 激活，
// 并 ·sub_4DB130(24) 播报、宿主 vt+956 收尾；再在 16 槽内找 ·sub_496F80(i)==16 的挂载物，
// 调其 vt+4(0, this) 绑定本体。末尾以 this[2160]×2 对比基准×成长系数（控制柄+60/+74），
// 未达阈值则控制柄 +74 浮点每次 +0.1（·sub_41A5E0 读 / ·sub_41A590 写 / vt+676 提交）。
// 任一分支末尾统一走 ·0x5AFB00 反击追加执行。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B04A0(int *this, int nArg2, int nArg3, int nArg4)
{
  int pListVec; // edi
  int pVecBegin; // eax
  unsigned int nIdx; // esi
  int pVecBegin2; // ecx
  int pListObj; // ecx
  int *pThis; // edi
  int i; // esi
  int pCtrl0; // esi
  unsigned int pCtrl74; // esi
  int edxTmp; // edx
  int pVecBegin3; // eax
  int pListObj2; // ecx
  int pSlotObj; // eax
  int nListCnt; // [esp+4h] [ebp-8h]
  int nGrowthBase; // [esp+14h] [ebp+8h]
  int fGrowthVal; // [esp+14h] [ebp+8h]
  char v23; // [esp+17h] [ebp+Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 存活标记17
  {
    v23 = 0;
    pListVec = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 取对象列表
    pVecBegin = *(uint32_t *)(pListVec + 4);
    nIdx = 0;
    if ( pVecBegin != 0 )
      nListCnt = (*(uint32_t *)(pListVec + 8) - pVecBegin) >> 2;
    else
      nListCnt = 0;
    if ( nListCnt <= 0 )
    {
LABEL_12:
      pThis = this;
    }
    else
    {
      while ( 1 )
      {
        pVecBegin2 = *(uint32_t *)(pListVec + 4);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin2) >> 2 )
          pListObj = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else
          pListObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj + 92))(pListObj) != 0 )  // 找首个有效项
          break;
        if ( (int)++nIdx >= nListCnt )
          goto LABEL_12;
      }
      pVecBegin3 = *(uint32_t *)(pListVec + 4);
      if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin3) >> 2 )
        pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
      else
        pListObj2 = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pListObj2 + 76))(pListObj2, 0);  // 激活
      pThis = this;
      sub_4DB130(24, 0);  // 播 24 号音效【推断】
      v23 = 1;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 956))(nArg2);
    }
    for ( i = 0; i < 16; ++i )
    {
      if ( sub_496F80(i) == 16 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 776))(nArg2, i) != 0 )  // 槽类型16
      {
        pSlotObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 772))(nArg2, i);
        (*(void (/*thiscall*/ **)(int, uint32_t, int *))(*(uint32_t *)pSlotObj + 4))(pSlotObj, 0, pThis);  // 绑定宿主
        goto LABEL_19;
      }
    }
    if ( v23 != 1 )
      return sub_5AFB00(this, nArg2, nArg3, nArg4);
    pThis = this;
LABEL_19:
    pCtrl0 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pThis + 672))(pThis, 0);
    nGrowthBase = sub_41A5E0(pCtrl0 + 60);
    if ( (double)pThis[2160] + (double)pThis[2160] > (double)(int)(uint64_t)((double)nGrowthBase
                                                                               * COERCE_FLOAT(sub_41A5E0(pCtrl0 + 74))) )  // 阈值 = 基准×成长系数
    {
      pCtrl74 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 74;
      *(float *)&fGrowthVal = COERCE_FLOAT(sub_41A5E0(pCtrl74)) + 0.1;  // 每次成长 +0.1
      sub_41A590(pCtrl74, edxTmp, fGrowthVal);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
  }
  return sub_5AFB00(this, nArg2, nArg3, nArg4);
}



// 龙人语音装载：DRAGONMAN_DMG/DIE + DRAGONMAN_FIND 发现播报（sub_4015C0 写语音槽）
//   this[1698..1702]=2/2/2/3/4 五档受击播报权重【推断】；this[2151]=囚笼对象槽、
//   this[2152]=囚笼冷却截止时钟（均由 0x5B09C0 写）；sub_4E1390(196614,100000) 注册属性
// ------------------------------------------------------------
// 0x5B0660 sub_5B0660 —— 龙人·语音槽与属性注册（构造期）
// ·sub_4015C0 依次写 DRAGONMAN_DMG(0xD)/DRAGONMAN_DIE(0xD)/DRAGONMAN_FIND(0xE) 三条语音 TAG。
// this[1698..1702]=2/2/2/3/4 为受击播报档位权重；this[2151] 囚笼对象槽清零、
// this[2152]=·sub_699000 当前时钟（囚笼冷却截止，由 ·0x5B09C0 消费）；·sub_4E1390 注册 196614。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0660(uint32_t *this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("DRAGONMAN_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_FIND", 0xEu);  // 【std::string构造赋值】
  *(this + 2151) = 0;  // 囚笼对象槽清空
  *(this + 2152) = sub_699000((int)(this + 9));  // 冷却截止=当前时钟
  v3 = 100000;
  return sub_4E1390(196614, &v3);
}



// 龙人·随机普攻：50% 概率 + 目标存活 + 距离<100 时 setState(8)，
//   参数包 v6[0]=rand()%3 → 0/1/2 = 短爪/蓄电/长突 三选一（由 0x5B0D10 case 8 消费）
// ------------------------------------------------------------
// 0x5B0700 sub_5B0700 —— 龙人·随机普攻抽选（setState 8）
// 概率门：rand()%100<50、目标 this[1813] 存活（vt+40 标记 17）、距离（vt+8）<100。
// 参数表经 ·sub_431230 打包，v6[0]=rand()%3 为普攻子型（0/1/2 短爪/蓄电/长突），由 ·0x5B0D10 case 8 消费。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0700(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0  // 目标存活标记17
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 100 )  // 距离<100
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = rand() % 3;  // 普攻子类型 0..2
    sub_431230((int)v2, v6);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // setState(8)
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 龙人·残血闪离门控（this+8614 幻觉相位标志）：HP 低于最大 HP 50%（vt+736 现血 /
//   vt+740 满血）、大状态空闲、且身后/身前 80px 均可站立时，setState(15) 发动
//   幻觉分身（参数：方向 rand()%2 + 移速查表 sub_460230）
// ------------------------------------------------------------
// 0x5B07C0 sub_5B07C0 —— 龙人·残血闪离/幻觉分身门控
// 五重前置：vt+308 目标门、this[1943]==3 阶段、vt+840 大状态须 0、this+8614 幻觉相位标志为 0、
// 现血（vt+736）>0 且 ≤ 满血（vt+740）50%【原文为 0.5×满血 > 现血 则退出】。
// 身后（vt+124/120 换算后 -80）与身前（+80）均须可站立（vt+136 ==1）。
// 参数表经 ·sub_431230 打包：方向 rand()%2 与移速查表 ·sub_460230(this[29])，
// 由 vt+560 setState(15) 发动，再 ·sub_5E5260 释放参数表。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B07C0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  void *pBuf[4]; // [esp+Ch] [ebp-24h] BYREF
  float fld_e29; // [esp+1Ch] [ebp-14h] BYREF
  int v12; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )  // 本地玩家/有目标门
    return 0;
  if ( *(this + 1943) != 3 )  // 阶段字段==3 才启用
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0 )  // 大状态须空闲(0)
    return 0;
  if ( *((uint8_t *)this + 8614) != 0 )  // 已在幻觉相位则不重复
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= 0 )  // 现血>0
    return 0;
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  v2 = *this;
  fld_e29 = (float)v12;  // 现血
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v2 + 740))(this);  // 满血
  if ( (double)v12 * 0.5 <= fld_e29 )  // 血线 > 50% 则不触发
    return 0;
  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v3 + 136))(this, v5 - 80) != 1 )  // 左 80px 可站立
    return 0;
  v6 = *this;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v7);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v6 + 136))(this, v8 + 80) != 1 )  // 右 80px 可站立
    return 0;
  memset(&pBuf[1], 0, 12);
  v13 = 0;
  LODWORD(fld_e29) = rand() % 2;  // 闪离方向 0/1
  sub_431230((int)pBuf, &fld_e29);
  fld_e29 = COERCE_FLOAT(sub_460230(*(this + 29)));  // 移速查表
  sub_431230((int)pBuf, &fld_e29);
  (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 15, pBuf, 2, 0);  // setState(15) 幻觉分身
  sub_5E5260(pBuf);
  return 1;
}



// 龙人·第4普攻（施法/雷电波）：阶段字段==3 时 setState(8) 且参数包固定 v6[0]=3
//   → 0x5B0D10 case 8 子类型3 走 DRAGONMAN_CAST + SPARK_LOOP 蓄电分支
// ------------------------------------------------------------
// 0x5B0930 sub_5B0930 —— 龙人·第4普攻（雷电施法）触发
// 门控：vt+308 目标门 且 this[1943]==3（阶段3 困难级）才发。
// 参数表经 ·sub_431230 打包，固定 v6[0]=3（施法子型），由 vt+560 setState(8) 发送，
// 交由 ·0x5B0D10 case 8 子型3 播 DRAGONMAN_CAST 并接 DRAGONMAN_SPARK_LOOP。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0930(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1943) == 3 )  // 阶段3
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 3;  // 子类型 3 = 施法
    sub_431230((int)v2, v6);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // setState(8)
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 龙人·囚笼技（JAIL）：懒加载 PassiveObject/MapObject/Trap/Particle/Cage.ptl 囚笼对象
//   存入 this[2151]，按与目标(pArg1[1813])的 X 差绝对值摆位（vt+124 基准 500/4），
//   vt+580(267) 发射；pArg1[2152] 记 冷却截止=now+2000ms（0x5B0D10 case 8 取消门用）
// ------------------------------------------------------------
// 0x5B09C0 sub_5B09C0 —— 龙人·囚笼技（JAIL 牢笼投放）
// 目标 pArg1[1813] 非 0 时：this[2151] 懒加载新对象经 ·sub_428F30 挂
// PassiveObject/MapObject/Trap/Particle/Cage.ptl（0x12C 字节）；按 |目标X - 自身X|（vt+120/vt+124，
// 目标基准 500 取 4）算出囚笼落点，vt+28 定位后经自身 vt+580 发射对象 267；
// this[2152] = ·sub_699000 时钟 + 2000ms（囚笼冷却，·0x5B0D10 case 8 二次投放门）。
// ------------------------------------------------------------
int /*usercall*/ sub_5B09C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // edi
  bool v8; // cc
  int v9; // edi
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  void *Block; // [esp+4h] [ebp-14h]
  int v15; // [esp+8h] [ebp-10h]

  result = pArg1[1813];  // 当前目标
  if ( result != 0 )
  {
    if ( pArg1[2151] == 0 )  // 囚笼对象懒加载
    {
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v6 = sub_428F30(pMem, (int)"PassiveObject/MapObject/Trap/Particle/Cage.ptl", 0);
      else
        v6 = nullptr;
      pArg1[2151] = v6;
    }
    v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);  // 目标坐标
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v7;  // 目标在自身哪一侧
    v9 = (*(int (**)(void))(*(uint32_t *)pArg1[1813] + 120))();
    if ( v8 )
      v15 = v9 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    else
      v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v9;  // |ΔX| 摆位
    v10 = *pArg1;
    Block = (void *)pArg1[2151];
    v11 = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813], 500, 4, 0);  // 目标基准 500/4
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
    v13 = (*(int (/*thiscall*/ **)(void *, uint32_t, int, int))(*(uint32_t *)Block + 28))(Block, 0, v15, v11 - v12);  // 囚笼定位
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 267, 0, v13);  // 发射对象267
    result = sub_699000((int)(pArg1 + 9)) + 2000;  // 【clock_now(clk)】 冷却 2000ms
    pArg1[2152] = result;
  }
  return result;
}



// 龙人·动作状态机分发（83L）：switch this[1787]（当前动作 id）——
//   0=登场(vt+1284 + BGM B_RAKIUS_01) / 4→5=接近走位(20%/30% 概率推进) /
//   13/14/15=受击后回 4 / 22=压制中按朝向(vt+152)与目标 X 判转向，20% 概率接普攻，
//   无目标则回 13；每帧尾调 0x5B07C0 残血闪离门控
// ------------------------------------------------------------
// 0x5B0AF0 sub_5B0AF0 —— 龙人·动作相位机（按 this+1787 行为字分发）
// case 0 登场：vt+1284 起手，this[1943]==3 时 ·sub_406D60 播 BGM B_RAKIUS_01；
// case 4/5 逼近走位：有目标且 20%/30% 概率经 vt+1104 在 4↔5 间推进；
// case 13/14/15 僵直回归：有目标则 vt+1104 回 4（·0x5B00F0/0x5B01C0 相位对为速度调制）；
// case 22 压制中（vt+840 大状态 14）：按 vt+152 朝向与目标方位匹配则转 5，否则 20% 概率转 4 接 ·0x5B0700；
// 无目标统一落 13。每分支末尾均调 ·0x5B07C0 残血闪离门控。首行 ·sub_4E0120 为帧前处理。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B0AF0(uint32_t *this)
{
  char result; // al
  int fld_e1813; // eax
  int fld_e18132; // edi
  int pObj; // edi
  int v6; // ebx

  sub_4E0120();
  switch ( *(this + 1787) )  // 当前动作 id
  {
    case 0:  // 登场
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      if ( *(this + 1943) != 3 )  // 非阶段3 不播 BGM
        goto LABEL_24;
      sub_406D60("B_RAKIUS_01");  // 登场曲写 BGM 槽
      return sub_5B07C0(this);
    case 4:  // 走位 A
      if ( *(this + 1813) == 0 )
        goto LABEL_14;
      if ( rand() % 100 >= 20 )  // 20% 概率推进
        goto LABEL_24;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
      return sub_5B07C0(this);
    case 5:  // 走位 B
      if ( *(this + 1813) == 0 )
        goto LABEL_14;
      if ( rand() % 100 >= 30 )  // 30% 概率回 4
        goto LABEL_24;
      goto LABEL_5;
    case 0xD:  // 13/14/15：受击/僵直态
    case 0xE:
    case 0xF:
      if ( *(this + 1813) == 0 )
        goto LABEL_24;
LABEL_5:
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 恢复走位
      result = sub_5B07C0(this);
      break;
    case 0x16:  // 22 压制中
      if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 )
      {
        fld_e1813 = *(this + 1813);
        if ( fld_e1813 != 0
          && ((fld_e18132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813),
               (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < fld_e18132)  // 目标在前方
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0  // 朝向 0
           || (pObj = *(this + 1813),
               (v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj))  // 目标在后方
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1) )  // 朝向 1
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 朝向正确 → 走位 5
          result = sub_5B07C0(this);
        }
        else
        {
          if ( rand() % 100 < 20 )  // 20% 概率接普攻
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
            sub_5B0700(this);
          }
LABEL_24:
          result = sub_5B07C0(this);
        }
      }
      else
      {
LABEL_14:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 无目标 → 13
        result = sub_5B07C0(this);
      }
      break;
    default:
      goto LABEL_24;
  }
  return result;
}



// 龙人·每帧 AI 总入口：先跑动作状态机分发(0x5B0AF0)，有目标(vt+308)再跑
//   随机位移判定(0x5B0320)；0x5B0D10 为其动作事件回调（普攻/护盾/幻觉全在此）
// ------------------------------------------------------------
// 0x5B0CF0 sub_5B0CF0 —— 龙人·每帧 AI 总入口
// 先调 ·0x5B0AF0 动作相位机；再经 vt+308 目标门，有目标才追加 ·0x5B0320 挂载物脉冲位移判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0CF0(int *this)
{
  int result; // eax

  sub_5B0AF0(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
    return sub_5B0320(this);
  return result;
}



// 龙人·动作事件分发（313L 全族最大）：大状态(pDwArg1[1639]=this+6556)×事件码(ArgList)
//   二维切换——普攻组8（vt+212 连播 DRAGONMAN_ATK/ATK_SHORT/STATIC_READY_LOOP/ATK_LONG/
//   CAST/SPARK_LOOP/JAIL，子类型读 this+7028）/ 护盾14（DRGM_SHIELD_LOOP）/
//   幻觉15（DLAni/EF_Hallucination1/2.ani + sub_4ABE10(0x47) 建分身藏于 -10000）/
//   幻觉换位16（本体与分身按 +4310 标志 ±80px 互换，销毁特效）；pArg4=事件参数表
// ------------------------------------------------------------
// 0x5B0D10 sub_5B0D10 —— 龙人·动作事件总分发（大状态 × 事件码二维派发）
// 入口读 pDwArg1[1639]（this+6556 主状态镜像）：15/幻觉只认事件16、14/护盾只认14、8/普攻按子型收手（·sub_41A5E0 this+7028）。
// 统一经 ·sub_4E33D0 状态收尾后 switch(ArgList)：case 8 普攻——vt+212 播 DRAGONMAN_ATK 并按子型 0/1/2/3/4
// 追加 ATK_SHORT / STATIC_READY_LOOP(11) / ATK_LONG / CAST+SPARK_LOOP(10) / ·0x5B09C0 JAIL 囚笼，
// 子型1、3 另有 ·sub_4926A0 帧游标复位 + vt+204 帧写入；case 14 护盾——DRGM_SHIELD_LOOP(9) + vt+876 双轴归零；
// case 15 幻觉——·sub_431920 装 DLAni/EF_Hallucination{1,2}.ani、·sub_44E1F0 建特效对象存 this[2154]，
// 经 ·sub_45FE80 挂到本体并置 this+8614 幻觉标志；case 16 换位——本体与分身按 this+4310 方向 ±80px 互换。
// ------------------------------------------------------------
void /*userpurge*/ sub_5B0D10(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int nBigState; // edi
  int pSkillRes; // eax
  int pVt; // edx
  int pVt2; // edx
  int hAniHallu1; // edi
  int pszResPath1; // ecx
  int pFxObj1; // eax
  int pFxHost1; // ecx
  int pFxObj1Vt; // edi
  int nZ1; // eax
  int nY1; // eax
  int nX1; // eax
  int pszResPath2; // ecx
  int hAniHallu2; // edi
  int *pFxObj2; // edi
  int pFxObj2Vt; // ebx
  int nY2; // eax
  int nX2; // eax
  int nCurX; // eax
  int pVt3; // edx
  int nCurZ; // eax
  int pVt4; // edx
  void **pAniCtrl3; // eax
  int pCloneObj; // eax
  size_t *pNameSrc; // edi
  int pNameBase; // eax
  int pCloneVt; // edi
  int nProp376; // eax
  int pFxHost2; // eax
  int pCloneVt2; // edi
  int nProp152; // eax
  int pCloneObj2; // edi
  int nProp684; // eax
  int pCloneObj3; // ecx
  int nSavedX; // eax
  int nSavedX2; // edi
  int nSelfNewX; // eax
  int nCloneNewX; // edi
  int pCloneObj4; // ecx
  int pFxObj1b; // ecx
  int pVt5; // eax
  int pCloneObj5; // [esp-10h] [ebp-28h]
  int nZ2; // [esp-4h] [ebp-1Ch]
  int nEvtParam2; // [esp+20h] [ebp+8h]

  nBigState = pDwArg1[1639];  // 大状态(this+6556)
  if ( nBigState == 15 )  // 幻觉中：只认换位事件16
  {
    if ( ArgList != 16 )
      return;
    goto LABEL_23;
  }
  if ( nBigState != 0 )
  {
    if ( nBigState == 14 )  // 护盾态
    {
      if ( ArgList != 14 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));  // pDwArg1[1554]=this+6216 技能资源表【推断：+4..+20 为动画/特效句柄组】
        (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);
      }
    }
    else if ( nBigState == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )  // 普攻态子类型3(施法)
    {
      if ( ArgList == 8 )
      {
LABEL_14:
        if ( **(uint32_t **)(pArg4 + 4) == 4  // 参数[0]==4 → JAIL 囚笼取消门
          && (pDwArg1[1813] == 0
           || (uint8_t)sub_5AFE40(pDwArg1[1813]) == 1
           || sub_699000((int)(pDwArg1 + 9)) < (unsigned int)pDwArg1[2152]) )  // 【clock_now(clk)】 囚笼冷却未到
        {
          **(uint32_t **)(pArg4 + 4) = 0;
        }
        goto LABEL_19;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 10);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 12);
    *((uint8_t *)pDwArg1 + 8613) = 0;
  }
  if ( ArgList == 8 )
    goto LABEL_14;
LABEL_19:
  if ( nBigState == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 && ArgList != 8 )
  {
    pSkillRes = pDwArg1[1554];
    pVt = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8601) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(pVt + 208))(pDwArg1, *(uint32_t *)(pSkillRes + 16));
    fArg2 = ((double (/*thiscall*/ *)(int *, uint32_t))*(uint32_t *)(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 20));
  }
LABEL_23:
  sub_4E33D0((int)pDwArg1, pArg4, fArg2, ArgList, pArg4, *(float *)&nArg5, *(float *)&nArg6);
  switch ( ArgList )
  {
    case 0:  // 空闲事件
      *((uint8_t *)pDwArg1 + 8613) = 0;
      break;
    case 8:  // 普攻事件
      pVt2 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8612) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(pVt2 + 212))(pDwArg1, "DRAGONMAN_ATK", -1, 0, 0);
      switch ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) )  // 普攻子类型(this+7028)
      {
        case 0:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_ATK_SHORT",
            -1,
            0,
            0);
          break;
        case 1:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_STATIC_READY_LOOP",
            11,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 20));
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 16),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 20),
            0,
            0,
            0,
            0);
          break;
        case 2:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_ATK_LONG",
            -1,
            0,
            0);
          break;
        case 3:
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            200,
            *(uint32_t *)(pDwArg1[1554] + 12),
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_CAST", -1, 0, 0);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_SPARK_LOOP",
            10,
            0,
            0);
          break;
        case 4:
          sub_5B09C0(pDwArg1);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_JAIL", -1, 0, 0);
          break;
        default:
          return;
      }
      break;
    case 14:  // 护盾事件：DRGM_SHIELD_LOOP
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
        pDwArg1,
        200,
        *(uint32_t *)(pDwArg1[1554] + 8),
        0,
        0,
        0,
        0);
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRGM_SHIELD_LOOP", 9, 0, 0);
      break;
    case 15:  // 幻觉分身事件：建分身藏于 -10000
      hAniHallu1 = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);  // 复位动画控制槽0
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 复位动画控制槽1
      *((uint16_t *)pDwArg1 + 4310) = **(uint16_t **)(pArg4 + 4);  // 换位方向参数(事件16用)
      nEvtParam2 = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4);  // 事件参数表[1]
      *((uint8_t *)pDwArg1 + 8614) = 1;  // 幻觉相位标志置位
      if ( sub_42FCB0(228) != 0 )  // 资源组可用门(228)【推断：EF_Hallucination 特效资源组开关】
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          LOBYTE(pszResPath1) = (uint8_t)pDwArg1 + 108;
        else
          pszResPath1 = pDwArg1[91];
        hAniHallu1 = sub_431920(pszResPath1, (char)"DLAni/EF_Hallucination1.ani", 1);
      }
      if ( sub_44B6C0(284) != 0 )
        pFxObj1 = sub_44E1F0(hAniHallu1, 0);
      else
        pFxObj1 = 0;
      pFxHost1 = pDwArg1[29];
      pDwArg1[2154] = pFxObj1;  // this+8616 幻觉特效1对象槽(事件16销毁用)
      sub_45FE80(pFxHost1, hAniHallu1, 2, 0, pFxObj1, (int)pDwArg1, 0);  // 在自身身上挂幻觉特效1
      pFxObj1Vt = *(uint32_t *)pDwArg1[2154];
      nZ1 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 取自身Z【推断：vt+120/124/128 三级定位链】
      nY1 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ1);
      nX1 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY1);
      (*(void (/*thiscall*/ **)(int, int))(pFxObj1Vt + 112))(pDwArg1[2154], nX1);  // 特效1放到本体X处
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          LOBYTE(pszResPath2) = (uint8_t)pDwArg1 + 108;
        else
          pszResPath2 = pDwArg1[91];
        hAniHallu2 = sub_431920(pszResPath2, (char)"DLAni/EF_Hallucination2.ani", 1);
      }
      else
      {
        hAniHallu2 = 0;
      }
      if ( sub_44B6C0(284) != 0 )
        pFxObj2 = (int *)sub_44E1F0(hAniHallu2, 1);
      else
        pFxObj2 = nullptr;
      sub_45FE80(pDwArg1[29], (int)pFxObj2, 2, 0, (int)pFxObj2, (int)pDwArg1, 0);
      pFxObj2Vt = *pFxObj2;
      nZ2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      nY2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
      nX2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY2 + 1);  // 分身特效2放在本体下一格X(+1格)【推断】
      (*(void (/*thiscall*/ **)(int *, int))(pFxObj2Vt + 112))(pFxObj2, nX2);
      nCurX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
      pVt3 = *pDwArg1;
      pDwArg1[2156] = nCurX;  // this+8624 幻觉期间本体X存档(事件16换位用)
      pDwArg1[2157] = (*(int (/*thiscall*/ **)(int *))(pVt3 + 124))(pDwArg1);  // this+8628 Y存档
      nCurZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      pVt4 = *pDwArg1;
      pDwArg1[2158] = nCurZ;  // this+8632 Z存档
      pAniCtrl3 = (void **)(*(int (/*thiscall*/ **)(int *, int))(pVt4 + 672))(pDwArg1, 3);  // 动画控制柄3【推断：模板/外观槽】
      pCloneObj = sub_4ABE10((void *)0x47, *pAniCtrl3, 0);  // 按模板0x47 克隆分身对象
      pDwArg1[2159] = pCloneObj;  // this+8636 分身对象槽
      pNameSrc = (size_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCloneObj + 340))(pCloneObj) + 4);
      pNameBase = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2159] + 340))(pDwArg1[2159]);
      sub_4014D0((size_t *)(pNameBase + 4), pNameSrc, 0, 0xFFFFFFFF);
      pCloneVt = *(uint32_t *)pDwArg1[2159];
      nProp376 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(pCloneVt + 372))(pDwArg1[2159], nProp376);
      pCloneObj5 = pDwArg1[2159];
      pFxHost2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
      sub_45FE80(pFxHost2, pCloneVt, 100, nEvtParam2, pCloneObj5, 0, 0);
      pCloneVt2 = *(uint32_t *)pDwArg1[2159];
      nProp152 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(pCloneVt2 + 148))(pDwArg1[2159], nProp152);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2159] + 604))(pDwArg1[2159], 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2159] + 112))(pDwArg1[2159], -10000, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*pDwArg1 + 112))(pDwArg1, -10000, 0, 0);
      pCloneObj2 = pDwArg1[2159];
      nProp684 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 684))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pCloneObj2 + 684))(pCloneObj2, nProp684);
      sub_46AE40(nZ2);
      *(uint8_t *)(pDwArg1[2159] + 8614) = 1;
      break;
    case 16:  // 幻觉换位：本体与分身 ±80px 互换（方向按 +4310 标志），销毁特效
      pCloneObj3 = pDwArg1[2159];
      if ( pCloneObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pCloneObj3 + 604))(pCloneObj3, 1);
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 604))(pDwArg1, 1);
      nSavedX = pDwArg1[2156];
      nSavedX2 = nSavedX;
      if ( *((uint16_t *)pDwArg1 + 4310) != 0 )
      {
        nSelfNewX = nSavedX - 80;
        nCloneNewX = nSavedX2 + 80;
      }
      else
      {
        nSelfNewX = nSavedX + 80;
        nCloneNewX = nSavedX2 - 80;
      }
      (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 112))(pDwArg1, nSelfNewX, pDwArg1[2157], pDwArg1[2158]);
      pCloneObj4 = pDwArg1[2159];
      if ( pCloneObj4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pCloneObj4 + 112))(pCloneObj4, nCloneNewX, pDwArg1[2157], pDwArg1[2158]);
      pFxObj1b = pDwArg1[2154];
      if ( pFxObj1b != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxObj1b + 84))(pFxObj1b, 0);
      pVt5 = *pDwArg1;
      pDwArg1[2154] = 0;
      pDwArg1[2159] = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(pVt5 + 472))(pDwArg1, 0, 0, 1, 1);
      break;
    default:
      return;
  }
}


// 【vmt200 命中处理器覆写】格挡反应 handler（虚表 0x6E2AB4/0x6E2FDC/0x6E3504/0x6E3A2C 四张 +512 槽, 145L）：
//   Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani +
//   Monster/Draconian/PassiveObject/GuardEffect.ani 龙人专属盾 + SWD_GUARDED + DRAGONMAN_DMG
// ------------------------------------------------------------
// 0x5B14D0 sub_5B14D0 —— 龙人·格挡命中处理器（vmt200 覆写 ×4 表）
// 前置：vt+840 大状态须 14（持盾）且 nArg5==0；this+642 或伴随对象 this[30] 的 +112 门值 >1 则放行穿透。
// 攻击方类型经 vt+348 取档位；攻击点非正面（vt+180）或带破防位则改走动作 13 受击，否则置 this+8600 格挡成功。
// 成功路径：vt+876 写击退（±300/后 -3000）、vt+888 写 1000ms、vt+896 挂火花资源（·sub_432E50 按 vt+152 类别取）；
// 受击矩形中点（pArg4[0..5] 双端均值）经 vt+124/vt+120 换算后，依次建
// GuardSpark.ani / GuardCircle.ani / Monster/Draconian/PassiveObject/GuardEffect.ani 三个特效
// （·sub_431860 装载 + ·sub_44E1F0 建对象 + ·sub_45FE80 挂本体），再 vt+212 播 SWD_GUARDED。
// 末尾统一 ·sub_4DA3B0 交回基类受击流水线并播 DRAGONMAN_DMG，this+8600 清零。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B14D0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, int nArg5)
{
  float *pArg42; // edi
  unsigned int nGateVal; // ebx
  int pGateObj; // ebx
  int nAtkX; // eax
  int pVt2; // ebx
  int hAniKind4; // eax
  int pSparkRes; // eax
  int nResGate1; // eax
  int hAniSpark; // edi
  int pFxSpark; // edi
  int pFxSparkVt; // ebx
  int nProp152a; // eax
  int nResGate2; // eax
  int hAniCircle; // edi
  int pFxCircle; // edi
  int pFxCircleVt; // ebx
  int nProp152b; // eax
  int nResGate3; // eax
  int hAniGuard; // edi
  int pFxGuard; // edi
  int pFxGuardVt; // ebx
  int pFxGuardVt2; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int nResult; // edi
  int nProp152c; // [esp-4h] [ebp-28h]
  int pVt; // [esp+Ch] [ebp-18h]
  int nMidX; // [esp+Ch] [ebp-18h]
  int nMidXhi; // [esp+10h] [ebp-14h]
  int nMidY; // [esp+14h] [ebp-10h]

  pArg42 = pArg4;
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) != 14 || (uint8_t)nArg5 != 0 )  // 大状态14=持盾态才格挡
    goto LABEL_33;
  if ( *((uint8_t *)pDwArg1 + 642) != 0 )
  {
    nGateVal = pDwArg1[161];
    goto LABEL_9;
  }
  pGateObj = pDwArg1[30];
  if ( pGateObj != 0 )
  {
    if ( *(uint32_t *)(pGateObj + 148) == -1 )
      sub_4938F0(pDwArg1[30]);  // 【推断：伴随对象到期(-1)销毁】
    nGateVal = *(uint32_t *)(pGateObj + 112);
LABEL_9:
    if ( nGateVal > 1 )  // 格挡放行门【推断：>1 时(连击后续段)不再演出格挡】
      goto LABEL_33;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) != 0  // 攻击者+348对象表[+12]非空(攻击带破防属性?)【推断】
    || (pVt = *pDwArg1,
        nAtkX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3),  // 取攻击者X
        (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt + 180))(pDwArg1, nAtkX) != 0) )  // 攻击不在正面→直接进入动作13(受击)【推断】
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);
  }
  else
  {
    *((uint8_t *)pDwArg1 + 8600) = 1;
  }
  if ( *((uint8_t *)pDwArg1 + 8600) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int, int))(*pDwArg1 + 876))(
      pDwArg1,
      0,
      300,
      300,
      0,
      -3000,
      1,
      nArg2);  // 击退参数(±300/向后-3000)【推断】
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);
    pVt2 = *pDwArg1;
    hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
    pSparkRes = sub_432E50(hAniKind4);
    (*(void (/*thiscall*/ **)(int *, int))(pVt2 + 896))(pDwArg1, pSparkRes);
    nMidX = (uint64_t)(pArg4[3] * 0.5 + *pArg4);  // 受击点X中点=攻击矩形两端均值
    nMidXhi = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, (uint64_t)(pArg4[3] * 0.5 + *pArg4) >> 32);  // 64位中点X的高位经vt+124换算
    nMidY = (uint64_t)(pArg4[5] * 0.5 + pArg4[2]);  // 受击点Y中点
    nResGate1 = sub_42FCB0(228);
    hAniSpark = 0;
    if ( nResGate1 != 0 )
      hAniSpark = sub_431860(nResGate1, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
    if ( sub_44B6C0(284) != 0 )
      pFxSpark = sub_44E1F0(hAniSpark, 1);
    else
      pFxSpark = 0;
    sub_45FE80(pDwArg1[29], pFxSpark, 2, 0, pFxSpark, (int)pDwArg1, 0);
    pFxSparkVt = *(uint32_t *)pFxSpark;
    nProp152a = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int, int))(pFxSparkVt + 148))(pFxSpark, nProp152a);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxSpark + 112))(pFxSpark, nMidX, nMidXhi, nMidY);
    nResGate2 = sub_42FCB0(228);
    if ( nResGate2 != 0 )
      hAniCircle = sub_431860(nResGate2, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
    else
      hAniCircle = 0;
    if ( sub_44B6C0(284) != 0 )
      pFxCircle = sub_44E1F0(hAniCircle, 1);
    else
      pFxCircle = 0;
    sub_45FE80(pDwArg1[29], pFxCircle, 2, 0, pFxCircle, (int)pDwArg1, 0);
    pFxCircleVt = *(uint32_t *)pFxCircle;
    nProp152b = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int, int))(pFxCircleVt + 148))(pFxCircle, nProp152b);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxCircle + 112))(pFxCircle, nMidX, nMidXhi, nMidY);
    nResGate3 = sub_42FCB0(228);
    if ( nResGate3 != 0 )
      hAniGuard = sub_431860(nResGate3, "Monster/Draconian/PassiveObject/GuardEffect.ani", 1);
    else
      hAniGuard = 0;
    if ( sub_44B6C0(284) != 0 )
      pFxGuard = sub_44E1F0(hAniGuard, 1);
    else
      pFxGuard = 0;
    sub_45FE80(pDwArg1[29], pFxGuard, 2, 0, pFxGuard, (int)pDwArg1, 0);
    pFxGuardVt = *(uint32_t *)pFxGuard;
    nProp152c = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int))(pFxGuardVt + 148))(pFxGuard);
    pFxGuardVt2 = *(uint32_t *)pFxGuard;
    nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
    nY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ);
    nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY + 1);
    (*(void (/*thiscall*/ **)(int, int))(pFxGuardVt2 + 112))(pFxGuard, nX);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxGuard + 60))(pFxGuard, pDwArg1);
    sub_4A06D0(nProp152c);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*pDwArg1 + 212))(pDwArg1, "SWD_GUARDED", -1, 0);  // 格挡成功播报
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pArg42 = pArg4;
  }
LABEL_33:
  nResult = sub_4DA3B0(nArg3, pArg42, nArg5);  // 交回基类受击流水线
  *((uint8_t *)pDwArg1 + 8600) = 0;
  sub_4015C0("DRAGONMAN_DMG", 0xDu);  // 【std::string构造赋值】
  return nResult;
}


// ============================================================
// 【分区 2】光之城主·赛格哈特（Zieg / Lord of Light）（0x5B1890-0x5B3230）
// 证据：ZIEG_FLOAT_LOOP/LAUGH/NOVA_READY_LOOP/CAST_NOVA/LASER_FIRE/DIE_EFFECT、
//       SHIELD_FLASH、R_ZIEG_DMG/ZIEG_DIE_VOICE、ConcentrationEffect.ani 聚焦、
//       Monster/LordofLight/LOL/{Die.ani,Armor,Glow,Wing}.equ、LOLParticle/{DieArmorParticle,
//       DieHikari}.ptl、vmt200 覆写 0x5B2E20（LOL/GuardEffect.ani）

// 外观装载：Monster/Draconian/Lakius/armor.equ（鲁卡斯甲壳）
// ------------------------------------------------------------
// 0x5B1890 sub_5B1890 —— 鲁卡斯·外观装载（armor.equ）
// 新建 0x544 字节对象经 ·sub_4BA9E0 挂 Monster/Draconian/Lakius/armor.equ，
// 由自身 vt+784 装配；装配结果非 0 时经其结果 vt+4(1) 激活。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1890(void *this)
{
  char *pMem; // eax
  char *v3; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Draconian/Lakius/armor.equ", 0);
  else
    v3 = nullptr;
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 子类扩展字段复位（this+8628..8640）
// ------------------------------------------------------------
// 0x5B1910 sub_5B1910 —— 赛格哈特·子类扩展字段复位
// 清零 this+8628 / +8632 / +8640 三处 4 字节与 +8636 / +8638 两个字节标志（构造期或重生的状态清场）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1910(int this)
{
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8638) = 0;
  *(uint32_t *)(this + 8640) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B1940 sub_5B1940 —— 赛格哈特·附属对象双槽释放
// this[2157] 与 this[2158] 若为非空接口指针，各调其自身 vt[0](1) 释放，随后两槽置 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1940(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2157)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2158)(uint32_t, int); // ecx

  fld_e2157 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2157);
  if ( fld_e2157 != nullptr )
    result = (**fld_e2157)(fld_e2157, 1);
  fld_e2158 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2158);
  *(this + 2157) = 0;
  if ( fld_e2158 != nullptr )
    result = (**fld_e2158)(fld_e2158, 1);
  *(this + 2158) = 0;
  return result;
}



// 浮空播报：ZIEG_FLOAT_LOOP（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B1980 sub_5B1980 —— 赛格哈特·浮空循环进入
// ·sub_4D9760 观察者广播收尾后，vt+212 播 ZIEG_FLOAT_LOOP（45566 为时长/参数槽），
// vt+1104 写行为字 15，this[2154] 记 ·sub_699000 当前时钟（供浮空计时门）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1980(uint32_t *this)
{
  int result; // eax

  sub_4D9760();
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
    this,
    "ZIEG_FLOAT_LOOP",
    45566,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2154) = result;
  return result;
}



// 赛格哈特·全局对象调参（阶段门 this[2160]==0 && this[1943]==3）：向全局管理器
//   dword_8F8520 连写 6 项参数（自身 vt+48/vt+52、dword_8F7C04+52、常量14、
//   移速查表 sub_460230(this[29])）后 vt+60(1,-1) 提交【推断：技能/屏幕效果参数下发】
// ------------------------------------------------------------
// 0x5B1F10 sub_5B1F10 —— 赛格哈特·全局管理器参数下发（阶段 3 一次）
// ·sub_4D9600 交互收尾后，vt+308 本地玩家门通过且 this[2160]==0、this[1943]==3 时：
// 经全局 ·0x8F8520 管理器 vt+8(29,2,nArg2) 起包，逐项 vt+36 写自身 vt+48、vt+52、
// ·0x8F7C04 对象 vt+52、常量 14、移速查表 ·sub_460230(this[29])，末以 vt+60(1,-1) 提交【推断：技能/表现参数下发】。
// ------------------------------------------------------------
int /*usercall*/ sub_5B1F10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v2; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int result; // eax

  sub_4D9600();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家门
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[2160];
    if ( result == 0 && pArg1[1943] == 3 )  // 阶段3 且未触发过
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);  // 起包(29,2)【推断】
      v2 = *(uint32_t *)dword_8F8520;
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v2 + 36))(dword_8F8520, v3);  // 逐项写参数
      v4 = *(uint32_t *)dword_8F8520;
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
      v6 = *(uint32_t *)dword_8F8520;
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
      v8 = *(uint32_t *)dword_8F8520;
      v9 = sub_460230(pArg1[29]);  // 移速查表
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 提交
    }
  }
  return result;
}



// 赛格哈特·朝向目标发射（vt+308 门）：vt+152 转向后取自身 X，若列表非空则以
//   0x51EB851F 魔数除法((224×元素数-X)/224÷100)算偏移，vt+580 发射 nArg4 号
//   对象（散布参数 70/120）【推断：弹幕齐射】
// ------------------------------------------------------------
// 0x5B1F50 sub_5B1F50
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5B1F50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int result; // eax
  int v6; // ebx
  int64_t v7; // rax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家门
  if ( (uint8_t)result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);  // 转向
    if ( v6 != 0 )
    {
      v8 = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      v9 = *(uint32_t *)(v8 + 364);
      v10 = v8 + 360;
      if ( v9 != 0 )
        v11 = (*(uint32_t *)(v10 + 8) - v9) >> 5;  // 列表元素数(32字节/项)
      else
        v11 = 0;
      v7 = 1374389535LL * (224 * v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 0x51EB851F=÷100 魔数
    }
    else
    {
      v7 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    }
    v12 = (SHIDWORD(v7) >> 5) + (HIDWORD(v7) >> 31);  // 完成除法
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
             pArg1,
             nArg4,
             v12,
             0,
             0,
             70,  // 散布参数【推断】
             0,
             120,
             v6,
             0,
             0,
             0);
  }
  return result;
}



// 笑播报：ZIEG_LAUGH（this+8608 相位, 62L）
// ------------------------------------------------------------
// 0x5B2010 sub_5B2010 —— 赛格哈特·嘲笑收手（ZIEG_LAUGH）与标记清零
// this[81] 先存 nArg2（记录点/朝向基准），vt+876 双轴归零、vt+196 复位动画槽 this[1554][0]、
// ·sub_4926A0 复位 this[30] 帧游标、vt+888 写 1000ms 反馈参数。
// 与记录点 X 差非 0 时调 ·sub_495890（±1000 镜头平移）·sub_4A0550·sub_4A0600(2) 摄像机三连；
// 否则清 this[28] 对象浮点 +6 与 +196 标志并 ·sub_495890(2,0)。
// 末尾 this+8608 相位标志与 this[2153] 清零、vt+212 播 ZIEG_LAUGH，
// 再遍历 this[1905] 起 32 字节/项数组把每项首字节清 0（与 ·0x5B2160 互逆）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2010(int *this, int nArg2)
{
  int pVt; // edx
  int fld_e81; // edi
  uint32_t *fld_e28; // edi
  int pVt2; // edx
  unsigned int result; // eax
  unsigned int nCount; // ecx
  int i; // edx
  int fld_e1905; // edi

  pVt = *this;
  *(this + 81) = nArg2;
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 876))(0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  sub_4926A0(*(this + 30));
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 与记录点(this[81])的 X 差
  if ( fld_e81 != 0 )
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);  // 镜头平移三连【推断】
    sub_4A0550(fld_e81);
    sub_4A0600(2);
  }
  else
  {
    fld_e28 = (uint32_t *)*(this + 28);
    if ( *fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
      && *((float *)fld_e28 + 6) != 0.0 )
    {
      fld_e28[6] = 0;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
    sub_495890(2, 0);
  }
  pVt2 = *this;
  *((uint8_t *)this + 8608) = 0;
  *(this + 2153) = 0;
  result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(pVt2 + 212))(this, "ZIEG_LAUGH", -1, 0, 0);  // 嘲笑播报
  nCount = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
      break;
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( nCount >= result )
      break;
    result = i + fld_e1905;
    ++nCount;
    *(uint8_t *)(i + fld_e1905) = 0;
  }
  return result;
}



// 赛格哈特·标记集置位（0x5B2010 尾部清零循环的逆操作）：把 this+1905 起的
//   32字节/项数组每项首字节置 1，随后 this[81]=this[2151]（恢复记录点）
// ------------------------------------------------------------
// 0x5B2160 sub_5B2160 —— 赛格哈特·标记集置位（·0x5B2010 清零循环的逆操作）
// 把 this[1905] 起 32 字节/项数组每项首字节置 1，随后 this[81] = this[2151]（记录点回填）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2160(unsigned int *this)
{
  unsigned int nCount; // edx
  int i; // esi
  int fld_e1905; // edi
  unsigned int result; // eax

  nCount = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
    {
      result = *(this + 2151);
      *(this + 81) = result;
      return result;
    }
    result = (int)(*(this + 1906) - fld_e1905) >> 5;
    if ( nCount >= result )
      break;
    ++nCount;
    *(uint8_t *)(i + fld_e1905) = 1;
  }
  *(this + 81) = *(this + 2151);
  return result;
}



// 盾闪：SHIELD_FLASH 播报（this+8644 相位）
// ------------------------------------------------------------
// 0x5B21B0 sub_5B21B0 —— 赛格哈特·盾闪（SHIELD_FLASH）
// this+8644 盾闪相位标志置 1；经 vt+672 取控制柄 +466 全局浮点由 ·sub_41A5E0 读取、
// +50 后经 ·sub_41A590 写回、vt+676 提交【推断：闪光强度】。
// vt+436(this,0,0) 取高度量取负，由 vt+204 写 100 帧 + this[1554][24] 动画槽，作上抛/击退；
// 末 vt+212 播 SHIELD_FLASH。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B21B0(uint8_t *this)
{
  int pVt; // eax
  unsigned int pFpCtrl466; // edi
  int nFlashVal; // eax
  int v5; // edx
  int pVt2; // ebx
  uint32_t *pThis_612; // edi
  int pThis_1B4; // eax

  pVt = *(uint32_t *)this;
  *(this + 8644) = 1;  // 盾闪相位标志
  pFpCtrl466 = (*(int (/*stdcall*/ **)(uint32_t))(pVt + 672))(0) + 466;
  nFlashVal = sub_41A5E0(pFpCtrl466);
  sub_41A590(pFpCtrl466, v5, nFlashVal + 50);  // 全局浮点+466 加 50【推断：闪光强度】
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  pVt2 = *(uint32_t *)this;
  pThis_612 = (uint32_t *)(*((uint32_t *)this + 1554) + 24);
  pThis_1B4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 436))(this, 0, 0);
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, int))(pVt2 + 204))(this, 100, *pThis_612, 0, -pThis_1B4);  // 上抛/击退【推断】
  return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "SHIELD_FLASH",
           -1,
           0,
           0);
}



// 赛格哈特·盾态模式切换（nArg3 选模式）：0=进入（8644 未置位先触发 0x5B21B0 盾闪，
//   控制柄+830 浮点 -0.3 降播速）；2=退出；nArg2 为延迟计数，归零后速度表
//   +68 ×0.5 减速（1050253722=0x3E99999A 即浮点 0.3f）
// ------------------------------------------------------------
// 0x5B2230 sub_5B2230 —— 赛格哈特·盾态进入/退出模式切换
// nArg3==0 进入：this+8644 未置位先 ·0x5B21B0 盾闪，控制柄 +830 浮点 -0.3 降播速（·sub_41A5E0/·sub_41A590/vt+676）。
// nArg3==2 退出：nArg2 延迟归零后把速度表 this[1905]+68 ×0.5 减速、写 0.3f（1050253722=0x3E99999A）经 ·sub_4AED60。
// 其余 nArg3 值返回 nArg3-2。与 ·0x5B2310 成对（该函数为镜像还原）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2230(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int pCtrl0; // edi
  int v6; // edx
  float v7; // [esp+0h] [ebp-4h]
  int fPlaySpeed; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;  // 位移速度减半
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);  // 0x3E99999A=0.3f
      sub_4AED60(v7);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    }
LABEL_8:
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )
    sub_5B21B0(this);
  pCtrl0 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
  *(float *)&fPlaySpeed = COERCE_FLOAT(sub_41A5E0(pCtrl0)) - 0.30000001;
  sub_41A590(pCtrl0, v6, fPlaySpeed);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  result = nArg2;
  if ( nArg2 != 0 )
    goto LABEL_8;
LABEL_9:
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;
  return result;
}



// 赛格哈特·盾态退出/还原（0x5B2230 的镜像，this+8644, 75L）：先复位 7531..7558/1891..1899
//   字段组（+7538 置 1）；nArg3==2&&nArg2==0 立即把速度表+68 ×2 还原、this[1899]=50；
//   nArg3==0 时未盾闪过则补 0x5B21B0，控制柄+830 浮点 +0.3 还原播速，nArg2 延迟后 ×2
// ------------------------------------------------------------
// 0x5B2310 sub_5B2310 —— 赛格哈特·盾态还原（·0x5B2230 镜像）
// 先批量清零 this+7531..7558 与 this[1891..1899] 两组相位字段，this+7538 置 1。
// nArg3==0：this+8644 未置位则补调 ·0x5B21B0，this[1899]=50，控制柄 +830 浮点 +0.3 还原播速，nArg2 延迟后速度表 +68 ×2；
// nArg3==2 且 nArg2==0 立即可速度表 +68 ×2 还原、写 0.3f 经 ·sub_4AED60。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2310(int *this, int nArg2, int nArg3)
{
  int pThis_1D73; // ecx
  int result; // eax
  int pVt; // edx
  int pVt2; // edx
  unsigned int pCtrl0; // edi
  int v9; // edx
  float v10; // [esp+0h] [ebp-8h]
  int fPlaySpeed; // [esp+14h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;
  *((uint8_t *)this + 7557) = 0;
  *((uint8_t *)this + 7556) = 0;
  *((uint8_t *)this + 7534) = 0;
  *((uint8_t *)this + 7533) = 0;
  *((uint8_t *)this + 7532) = 0;
  *((uint8_t *)this + 7531) = 0;
  *(int *)((char *)this + 7535) = 0;
  pThis_1D73 = (int)this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *(uint32_t *)(pThis_1D73 + 4) = 0;
  *(uint32_t *)(pThis_1D73 + 8) = 0;
  *(uint32_t *)(pThis_1D73 + 12) = 0;
  *(uint8_t *)(pThis_1D73 + 16) = 0;
  *(this + 1893) = 0;
  *(this + 1892) = 0;
  *(this + 1891) = 0;
  *(this + 1897) = 0;
  *(this + 1896) = 0;
  *(this + 1895) = 0;
  *(this + 1894) = 0;
  *(this + 1899) = 0;
  *((uint8_t *)this + 7538) = 1;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);  // 位移速度 ×2 还原
      pVt = *this;
      *(this + 1899) = 50;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(pVt + 672))(this, 0, 1050253722);  // 0x3E99999A=0.3f
      sub_4AED60(v10);
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
LABEL_8:
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )
    sub_5B21B0(this);
  pVt2 = *this;
  *(this + 1899) = 50;
  pCtrl0 = (*(int (/*thiscall*/ **)(int *, uint32_t))(pVt2 + 672))(this, 0) + 830;
  *(float *)&fPlaySpeed = COERCE_FLOAT(sub_41A5E0(pCtrl0)) + 0.30000001;
  sub_41A590(pCtrl0, v9, fPlaySpeed);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  result = nArg2;
  if ( nArg2 != 0 )
    goto LABEL_8;
LABEL_9:
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);
  return result;
}



// 赛格哈特·新星/护盾事件分发（大状态 this+6556 × 事件码切换，136L）：护盾态14 入出时
//   调 0x5B2160 标记集复位；普攻态8 按子类型(this+7028=1/2)挂 vt+208 贴图；
//   事件8 子类型2 走 ZIEG_NOVA_READY_LOOP 蓄力 + ZIEG_CAST_NOVA 施放
//   （vt+204(100,×3) 三段伤害帧）；事件5 播 45566/45567/45568 三音效；事件14 转嘲笑
// ------------------------------------------------------------
// 0x5B2480 sub_5B2480 —— 赛格哈特·新星/护盾事件分发（大状态 this+6556 × 事件码）
// ArgList==15 先 ·0x5B2160 置位标记集并把事件改 0；大状态 14/护盾时段内（非 15）亦复位标记集；
// 大状态 8/普攻且非事件 8 时按 this+7028 子型 1/2 经 vt+208 挂 this+6216 资源槽贴图。
// 事件 8：vt+888 写 1000ms、this+8637 清位；子型 1 转 ·0x5B1CD0；子型 2 播
// ZIEG_NOVA_READY_LOOP(45568) + ZIEG_CAST_NOVA，并对 this+6216 的 +16/+20/+12 三槽
// 取 ·sub_4926A0 帧游标复位 + vt+204(100, ...) 三段伤害帧（this+8624 清位）。
// 事件 5 播 45566/45567/45568 三音效；事件 14 经 vt+8 距离小于门槛(this+7620[80])时改参数后转 ·0x5B2010 嘲笑。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2480(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int nEvt; // ebx
  int fld_199C; // edi
  uint32_t *pResSlot; // eax
  float fEvtParam; // edi
  int nTgtRef; // eax
  unsigned int result; // eax
  int *pResSlot2; // eax

  nEvt = ArgList;
  fld_199C = *(uint32_t *)(this + 6556);  // 大状态
  if ( ArgList == 15 )
  {
    sub_5B2160((unsigned int *)this);
    nEvt = 0;
  }
  if ( fld_199C == 14 )  // 护盾态
  {
    if ( nEvt != 15 )
      sub_5B2160((unsigned int *)this);
  }
  else
  {
    if ( fld_199C != 8 )
      goto LABEL_13;
    if ( nEvt == 8 )
      goto LABEL_14;
    if ( sub_41A5E0(this + 7028) == 1 )  // 子类型1
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
      pResSlot = (uint32_t *)(*(uint32_t *)(this + 6216) + 8);
    }
    else
    {
      if ( sub_41A5E0(this + 7028) != 2 )
        goto LABEL_13;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 16));
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 20));
      pResSlot = (uint32_t *)(*(uint32_t *)(this + 6216) + 12);
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pResSlot);
  }
LABEL_13:
  if ( nEvt != 8 )
  {
    fEvtParam = fArg3;
    goto LABEL_19;
  }
LABEL_14:
  fEvtParam = fArg3;
  if ( *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) == 1 )
  {
    nTgtRef = *(uint32_t *)(this + 7252);
    if ( nTgtRef != 0
      && (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 8))(this, nTgtRef, 0) < *(uint32_t *)(*(uint32_t *)(this + 7620) + 80) )
    {
      *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 2;
    }
  }
LABEL_19:
  result = sub_4E33D0(nEvt, fEvtParam, nArg4, nArg5);
  switch ( nEvt )
  {
    case 5:  // 音效三连
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45566);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45567);
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45568);
    case 8:  // 新星事件
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
      *(uint8_t *)(this + 8637) = 0;
      if ( sub_41A5E0(this + 7028) == 1 )
      {
        return sub_5B1CD0(this);
      }
      else
      {
        result = sub_41A5E0(this + 7028);
        if ( result == 2 )  // 子类型2 = 新星蓄力+施放
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "ZIEG_NOVA_READY_LOOP",
            45568,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "ZIEG_CAST_NOVA",
            -1,
            0,
            0);
          pResSlot2 = (int *)(*(uint32_t *)(this + 6216) + 16);
          *(uint8_t *)(this + 8624) = 0;
          sub_4926A0(*pResSlot2);
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 20));
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 12));
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 16),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 20),
            0,
            0,
            0,
            0);
          return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                   this,
                   100,
                   *(uint32_t *)(*(uint32_t *)(this + 6216) + 12),
                   0,
                   0,
                   0,
                   0);
        }
      }
      break;
    case 14:  // 护盾事件 → 转嘲笑(0x5B2010)
      return sub_5B2010((int *)this, **(uint32_t **)(LODWORD(fEvtParam) + 4));
    default:
      break;
  }
  return result;
}


// 赛格哈特语音：R_ZIEG_DMG + ZIEG_DIE_VOICE（this+8600/8604/8636 相位）
// ------------------------------------------------------------
// 0x5B2720 sub_5B2720 —— 赛格哈特·受伤/死亡语音装载
// ·sub_4015C0 写 R_ZIEG_DMG(0xA) 与 ZIEG_DIE_VOICE(0xE) 两条语音 TAG；
// this+8600=20、this+8604=this+324（父级引用），并以 ·sub_47C080(20) 结果取反写 this+8636 相位标志。
// ------------------------------------------------------------
bool /*thiscall*/ sub_5B2720(int this)
{
  int fld_144; // eax
  bool result; // al

  sub_4015C0("R_ZIEG_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZIEG_DIE_VOICE", 0xEu);  // 【std::string构造赋值】
  fld_144 = *(uint32_t *)(this + 324);
  *(uint32_t *)(this + 8600) = 20;
  *(uint32_t *)(this + 8604) = fld_144;
  result = (uint8_t)sub_47C080(20) == 0;
  *(uint8_t *)(this + 8636) = result;
  return result;
}



// 赛格哈特·周期护盾：时钟(this+9)距上次(this[2154])超过 15000ms 且大状态空闲、
//   有目标时 → vt+564 复位并 setState(14, 参数 200=护盾持续)【推断：每 15 秒开盾】
// ------------------------------------------------------------
// 0x5B2780 sub_5B2780 —— 赛格哈特·周期护盾（每 15 秒开盾）
// ·sub_699000 时钟超过 this[2154]+15000ms 才进入，先回写本次时刻；再要求 vt+840 大状态为 0 且
// this[1813] 目标存在，vt+564 复位后用 ·sub_431230 打包 v9[0]=200（护盾持续）经 vt+560 setState(14)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2780(uint32_t *this)
{
  int pThis_9; // edi
  int v3; // eax
  int v4; // edx
  uint8_t v5[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  uint32_t v9[4]; // [esp+18h] [ebp-10h] BYREF

  pThis_9 = (int)(this + 9);
  if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2154) + 15000) )  // 【clock_now(clk)】 15 秒周期
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 2154) = v3;  // 记录本次触发时刻
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this) == 0 && *(this + 1813) != 0 )  // 空闲且有目标
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      v9[0] = 200;  // 护盾持续参数【推断】
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v9[3] = 0;
      sub_431230((int)v5, v9);  // 【vector 打包 setState 参数表】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 14, v5, 0, 0);  // setState(14) 开盾
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 赛格哈特·条件新星普攻：范围值=速度表(+80/+88 之和)×1.5 过 sub_4E0CD0(17,…) 判定
//   （17=技能/范围档位）≥2 且 40% 概率 → vt+564 复位并 setState(8, 子类型2=新星)
// ------------------------------------------------------------
// 0x5B2840 sub_5B2840 —— 赛格哈特·条件新星（射程档位判定后 40% 触发）
// 范围值取速度表 this[1905]+80 与 +88 之和的 1.5 倍，交 ·sub_4E0CD0(17,0,0,…) 档位判定 ≥2，
// 且 rand()%100<40 时 vt+564 复位、参数 v6[0]=2（新星子型）经 ·sub_431230 打包 + vt+560 setState(8)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2840(uint32_t *this)
{
  uint8_t v2[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v4; // [esp+10h] [ebp-18h]
  int v5; // [esp+14h] [ebp-14h]
  uint32_t v6[4]; // [esp+18h] [ebp-10h] BYREF

  v6[0] = *(uint32_t *)(*(this + 1905) + 80) + *(uint32_t *)(*(this + 1905) + 88);
  if ( (int)sub_4E0CD0(17, 0, 0, (uint64_t)((double)v6[0] * 1.5)) >= 2 && rand() % 100 < 40 )  // 40% 概率
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 2;  // 子类型 2 = 新星
    sub_431230((int)v2, v6);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);  // setState(8)
    if ( Block != nullptr )
      j__free(Block);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B2900 sub_5B2900 —— 赛格哈特·每帧 AI 门（新星挂载）
// 先 ·sub_5B1BA0 帧前处理；再经 vt+308 目标门、this[1813] 非 0、vt+840 大状态为 0 三条件，
// 全满足才交 ·0x5B2840 条件新星。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2900(uint32_t *this)
{
  sub_5B1BA0();
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1813) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )
  {
    sub_5B2840(this);
  }
}



// 激光技能：ZIEG_LASER_FIRE 播报 + Common/CommonEffect/Animation/ConcentrationEffect.ani
//   聚焦特效（103L；sub_431860）
// ------------------------------------------------------------
// 0x5B2940 sub_5B2940 —— 赛格哈特·激光三阶段（聚焦/发射/收束）
// 动作对象 vt+200 的 +148 三态忙闲门，各配一次性相位标志防重入：
// +148==2 → this+8621 锁位、聚焦特效（ConcentrationEffect.ani 经 ·sub_431860/·sub_44E0D0/·sub_45FE80，
// 落点取 vt+152 朝向 ±70px），再 ·0x5B1F50 发射 48029；
// +148==5 → this+8622 锁位、·0x5B1F50 发射 46003 并 vt+212 播 ZIEG_LASER_FIRE；
// +148==6 → this+8623 锁位、对 this+6216 的 +4/+8 槽 ·sub_4926A0 复位 + vt+204(100/200) 伤害帧 + 音效 45567。
// ------------------------------------------------------------
char /*usercall*/ sub_5B2940@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pVt; // edx
  int nLaserX; // eax
  int hAniConc; // ebx
  char *pPool; // eax
  int *pFxObj; // edi
  int pFxVt; // ebx
  int nZ; // eax
  int nY; // eax
  int pFxVt2; // ebx
  int nProp152; // eax
  int pActObj; // eax
  int *pResSlot; // eax
  int nLaserX2; // [esp+8h] [ebp-10h]

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 2 || *(uint8_t *)(pArg1 + 8621) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 5 || *(uint8_t *)(pArg1 + 8622) != 0 )
    {
      pActObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
      if ( *(uint32_t *)(pActObj + 148) == 6 )
      {
        LOBYTE(pActObj) = *(uint8_t *)(pArg1 + 8623);
        if ( (uint8_t)pActObj == 0 )
        {
          pResSlot = (int *)(*(uint32_t *)(pArg1 + 6216) + 4);
          *(uint8_t *)(pArg1 + 8623) = 1;
          sub_4926A0(*pResSlot);
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8));
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
            pArg1,
            100,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
            pArg1,
            200,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8),
            0,
            0,
            0,
            0);
          LOBYTE(pActObj) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 45567);
        }
      }
    }
    else
    {
      *(uint8_t *)(pArg1 + 8622) = 1;
      sub_5B1F50((uint32_t *)pArg1, nArg2, nArg3, 46003);
      LOBYTE(pActObj) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                      pArg1,
                      "ZIEG_LASER_FIRE",
                      -1,
                      0,
                      0);
    }
  }
  else
  {
    pVt = *(uint32_t *)pArg1;
    *(uint8_t *)(pArg1 + 8621) = 1;
    if ( (*(int (/*thiscall*/ **)(int))(pVt + 152))(pArg1) != 0 )
      nLaserX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 70;
    else
      nLaserX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 70;
    nLaserX2 = nLaserX;
    hAniConc = 0;
    if ( sub_42FCB0(228) != 0 )
      hAniConc = sub_431860((char)"Common/CommonEffect/Animation/ConcentrationEffect.ani", 1);
    pPool = (char *)sub_44B6C0(284);
    pFxObj = (int *)pPool;
    if ( pPool != nullptr )
    {
      sub_44E0D0(pPool, hAniConc, 1);
      *pFxObj = (int)&CNRDPooledObject::`vftable';
    }
    else
    {
      pFxObj = nullptr;
    }
    sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)pFxObj, 2, 0, (int)pFxObj, pArg1, 0);
    pFxVt = *pFxObj;
    nZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
    nY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, nZ + 120);
    (*(void (/*thiscall*/ **)(int *, int, int))(pFxVt + 112))(pFxObj, nLaserX2, nY);
    pFxVt2 = *pFxObj;
    nProp152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
    (*(void (/*thiscall*/ **)(int *, int))(pFxVt2 + 148))(pFxObj, nProp152);
    LOBYTE(pActObj) = sub_5B1F50((uint32_t *)pArg1, pFxVt2, (int)pFxObj, 48029);
  }
  return pActObj;
}



// 赛格哈特死亡演出（129L）：Monster/LordofLight/LOL/Die.ani + LOLParticle/
//   {DieArmorParticle.ptl 装甲飞散, DieHikari.ptl 光尘} + ZIEG_DIE_EFFECT 播报
// ------------------------------------------------------------
// 0x5B2B80 sub_5B2B80 —— 赛格哈特·死亡演出（Die.ani + 双粒子）
// 经 ·sub_431860 装 Monster/LordofLight/LOL/Die.ani，·sub_44B6C0 取池对象 + ·sub_44E0D0 构造后
// 由 ·sub_45FE80 挂到本体并 vt+112 定 X、vt+144 定朝向（this+128/124/120 三级定位链）。
// 再 new 0x12C 两枚粒子：·sub_4C3640 挂 LOLParticle/DieArmorParticle.ptl 存 this[2157]（+8628 装甲飞散）、
// DieHikari.ptl 存 this[2158]（+8632 光尘），各 vt+12(0) 启动、vt+40 定位于本体 Z+50；
// 参数表经 vt+92 取出后 ·sub_4E77D0 合参、·sub_4600B0 挂到本体，末 vt+212 播 ZIEG_DIE_EFFECT。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2B80(int *this)
{
  int hAniDie; // ebx
  int *pPool; // eax
  int *pDieFx; // edi
  int fld_e29; // ecx
  int pDieFxVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int pDieFxVt2; // ebx
  int nProp152; // eax
  void *pMem; // eax
  int *pArmorPtlObj; // eax
  int pArmorPtlVt; // edx
  int fld_e2157; // ebx
  int nZ2; // eax
  int nY2; // eax
  int nX2; // eax
  void *fld_e292; // ecx
  void *pMem2; // eax
  int *pHikariPtlObj; // eax
  int pHikariPtlVt; // edx
  int fld_e2158; // edi
  int nZ3; // eax
  int nY3; // eax
  int nX3; // eax
  int fld_e21582; // eax
  uint8_t v28[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  uint8_t v30[4]; // [esp+1Ch] [ebp-20h] BYREF
  void *v31; // [esp+20h] [ebp-1Ch]
  void *pMem3; // [esp+2Ch] [ebp-10h]
  int v33; // [esp+38h] [ebp-4h]

  hAniDie = 0;
  v33 = 0;
  if ( sub_42FCB0(228) != 0 )
    hAniDie = sub_431860((char)"Monster/LordofLight/LOL/Die.ani", 1);
  pPool = (int *)sub_44B6C0(284);
  pDieFx = pPool;
  pMem3 = pPool;
  v33 = 1;
  if ( pPool != nullptr )
  {
    sub_44E0D0((char *)pPool, hAniDie, 1);
    *pDieFx = (int)&CNRDPooledObject::`vftable';
  }
  else
  {
    pDieFx = nullptr;
  }
  fld_e29 = *(this + 29);
  v33 = -1;
  sub_45FE80(fld_e29, (int)pDieFx, 2, 0, (int)pDieFx, (int)this, 0);
  pDieFxVt = *pDieFx;
  nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);
  nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY);
  (*(void (/*thiscall*/ **)(int *, int))(pDieFxVt + 112))(pDieFx, nX);
  pDieFxVt2 = *pDieFx;
  nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(int *, int))(pDieFxVt2 + 144))(pDieFx, nProp152);
  pMem = operator new(0x12Cu);
  pMem3 = pMem;
  v33 = 2;
  if ( pMem != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pArmorPtlObj = (int *)sub_4C3640((int)pMem, (int)(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);
    else
      pArmorPtlObj = (int *)sub_4C3640((int)pMem, *(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);
  }
  else
  {
    pArmorPtlObj = nullptr;
  }
  *(this + 2157) = (int)pArmorPtlObj;  // this+8628 装甲飞散粒子槽(死亡演出用)
  pArmorPtlVt = *pArmorPtlObj;
  v33 = -1;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(pArmorPtlVt + 12))(pArmorPtlObj, 0);
  fld_e2157 = *(uint32_t *)*(this + 2157);
  nZ2 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  nY2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ2 + 50);
  nX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY2);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2157 + 40))(*(this + 2157), nX2);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2157) + 92))(*(this + 2157), v30);
  fld_e292 = (void *)*(this + 29);
  v33 = 3;
  sub_4600B0(fld_e292, 2, 0, (int)v30);
  pMem2 = operator new(0x12Cu);
  pMem3 = pMem2;
  LOBYTE(v33) = 4;
  if ( pMem2 != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pHikariPtlObj = (int *)sub_4C3640((int)pMem2, (int)(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);
    else
      pHikariPtlObj = (int *)sub_4C3640((int)pMem2, *(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);
  }
  else
  {
    pHikariPtlObj = nullptr;
  }
  *(this + 2158) = (int)pHikariPtlObj;  // this+8632 光尘粒子槽(死亡演出用)
  pHikariPtlVt = *pHikariPtlObj;
  LOBYTE(v33) = 3;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(pHikariPtlVt + 12))(pHikariPtlObj, 0);
  fld_e2158 = *(uint32_t *)*(this + 2158);
  nZ3 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  nY3 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ3 + 50);
  nX3 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY3);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2158 + 40))(*(this + 2158), nX3);
  fld_e21582 = (*(int (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2158) + 92))(*(this + 2158), v28);
  LOBYTE(v33) = 5;
  sub_4E77D0((int)v30, fld_e21582);
  LOBYTE(v33) = 3;
  if ( Block != nullptr )
    j__free(Block);
  sub_4600B0((void *)*(this + 29), 2, 0, (int)v30);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ZIEG_DIE_EFFECT", -1, 0, 0);
  if ( v31 != nullptr )
    j__free(v31);
}


// 【vmt200 命中处理器覆写】光之城主格挡 handler（虚表 0x6E447C +512 槽, 48L）：
//   Monster/LordOfLight/LOL/GuardEffect.ani 专属格挡特效（sub_431860）
// ------------------------------------------------------------
// 0x5B2E20 sub_5B2E20 —— 光之城主·格挡命中处理器（vmt200 覆写 ×1 表）
// 门控 this+8644（盾闪相位）非 0 才演出：·sub_431860 装 Monster/LordOfLight/LOL/GuardEffect.ani，
// ·sub_44B6C0/·sub_44E0D0 取池对象并构造，·sub_45FE80 挂本体，vt+112/148 定位与朝向（vt+152）。
// 末尾仍交 ·sub_4DA3B0 命中包分发（pArg2/pArg4 原样透传）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2E20(int *this, int nArg2, int nArg3, int nArg4)
{
  int hAniGuard; // ebx
  char *pPool; // eax
  int pFxObj; // edi
  int pFxVt; // ebx
  int pFxVt2; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int nProp152; // [esp-Ch] [ebp-20h]

  if ( *((uint8_t *)this + 8644) != 0 )
  {
    hAniGuard = 0;
    if ( sub_42FCB0(228) != 0 )
      hAniGuard = sub_431860((char)"Monster/LordOfLight/LOL/GuardEffect.ani", 1);
    pPool = (char *)sub_44B6C0(284);
    pFxObj = (int)pPool;
    if ( pPool != nullptr )
    {
      sub_44E0D0(pPool, hAniGuard, 1);
      *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';
    }
    else
    {
      pFxObj = 0;
    }
    sub_45FE80(*(this + 29), pFxObj, 2, 0, pFxObj, (int)this, 0);
    pFxVt = *(uint32_t *)pFxObj;
    nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int))(pFxVt + 148))(pFxObj);
    pFxVt2 = *(uint32_t *)pFxObj;
    nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);
    nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY + 1);
    (*(void (/*thiscall*/ **)(int, int))(pFxVt2 + 112))(pFxObj, nX);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxObj + 60))(pFxObj, this);
    sub_4A06D0(nProp152);
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// AI 相位辅助（this+8636/8640）
// ------------------------------------------------------------
// 0x5B2F40 sub_5B2F40 —— 赛格哈特·死亡/退场对话门（死亡表现前置）
// nArg2 非本体（this != nArg2）直接 ·sub_4D9170 交互收尾返回；
// 否则要求 this+7772==3、this[8640] 非 0、this+8636==1 三者全真才走对话分支，不满足即 ·0x5B2B80 死亡演出。
// 对话分支：对 this[8640] 附属对象 vt+112 定 X（vt+436/vt+124/vt+120 链）、vt+144 定朝向（vt+152）；
// 其 vt+308 本地玩家门通过则经其 vt+580 发射 48001（存活奖励视图，参数 1/….4）；
// 末以该对象 vt+64 取消息上下文，·sub_50EF20 播头顶气泡（无对白省略号文案）【推断：死亡前无语对白】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2F40(int this, int nArg2)
{
  int fld_21C0; // edi
  int pThis_1B4; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int fld_21C02; // edi
  int pThis_98; // eax
  int fld_21C03; // edi
  int nMsgCtx; // eax
  int pThis_982; // [esp-Ch] [ebp-14h]

  if ( this != nArg2 )
    return sub_4D9170(nArg2);
  if ( *(uint32_t *)(this + 7772) != 3 || *(uint32_t *)(this + 8640) == 0 || *(uint8_t *)(this + 8636) != 1 )
  {
    sub_5B2B80((int *)this);
    return sub_4D9170(nArg2);
  }
  fld_21C0 = **(uint32_t **)(this + 8640);
  pThis_1B4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 436))(this);
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_1B4);
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21C0 + 112))(*(uint32_t *)(this + 8640), pThis_78);
  fld_21C02 = **(uint32_t **)(this + 8640);
  pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21C02 + 144))(*(uint32_t *)(this + 8640), pThis_98);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8640) + 308))(*(uint32_t *)(this + 8640)) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8640) + 580))(
      *(uint32_t *)(this + 8640),
      48001,
      1,
      0,
      0,
      0,
      0,
      0,
      4,
      0,
      0,
      0);
  fld_21C03 = *(uint32_t *)(this + 8640);
  pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 10000);
  nMsgCtx = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21C03 + 64))(fld_21C03);
  sub_50EF20(nMsgCtx, "......", pThis_982);  // 头顶冒 "……" 气泡(存活奖励视图 48001)【推断：死亡前无语对白】
  return sub_4D9170(nArg2);
}



// 技能播报：ZIEG_NOVA_FIRE + SWING_LONG 挥击
// ------------------------------------------------------------
// 0x5B3050 sub_5B3050 —— 赛格哈特·大状态事件总回调（护盾/普攻/待机三分支）
// 先 ·sub_4E1780 帧前处理；按 vt+840 大状态分流：
// 14/护盾 → ·0x5B1D20；8/普攻 → 按 this+7028 子型 0 时动作对象 vt+148 ≥3 且 this+8637 未置位则播 SWING_LONG，
// 子型 1 转 ·0x5B2940 激光，子型 2 且动作对象 vt+148==4、this+8624 未置位则音效 45568 + 播 ZIEG_NOVA_FIRE；
// 其余（含待机）→ vt+308 门通过后 ·0x5B2780 周期护盾。
// ------------------------------------------------------------
void /*usercall*/ sub_5B3050(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pVt; // edx
  int nSubType; // eax
  int nSubTypeM1; // eax

  sub_4E1780((uint32_t *)pArg1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 14 )
  {
    sub_5B1D20(pArg1);
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )
  {
    nSubType = sub_41A5E0(pArg1 + 7028);
    if ( nSubType != 0 )
    {
      nSubTypeM1 = nSubType - 1;
      if ( nSubTypeM1 != 0 )
      {
        if ( nSubTypeM1 == 1
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 4
          && *(uint8_t *)(pArg1 + 8624) == 0 )
        {
          pVt = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8624) = 1;
          (*(void (/*thiscall*/ **)(int, int))(pVt + 216))(pArg1, 45568);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "ZIEG_NOVA_FIRE",
            -1,
            0,
            0);
        }
      }
      else
      {
        sub_5B2940(pArg1, nArg2, nArg3);
      }
    }
    else if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 && *(uint8_t *)(pArg1 + 8637) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SWING_LONG", -1, 0, 0);
      *(uint8_t *)(pArg1 + 8637) = 1;
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
  {
    sub_5B2780((uint32_t *)pArg1);
  }
}



// 赛格哈特外观装载：Monster/LordofLight/LOL/{Armor,Glow,Wing}.equ 三件（甲/辉光/翼）
// ------------------------------------------------------------
// 0x5B3100 sub_5B3100 —— 赛格哈特·外观三件套装载（Armor/Glow/Wing）
// 三个 0x544 字节新对象依次经 ·sub_4BA9E0 挂 Monster/LordofLight/LOL/{Armor,Glow,Wing}.equ，
// 各由自身 vt+784 装配、结果非 0 时经其结果 vt+4(1) 激活；末尾 this+8644 盾闪标志清零、
// ·sub_4E1390 注册 196614（常量 100000）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3100(uint8_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int v4; // edx
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int v8; // edx
  int pObj2; // eax
  char *pMem3; // eax
  char *v11; // eax
  int v12; // edx
  int pObj3; // eax
  int v15; // [esp+8h] [ebp-10h] BYREF
  int v16; // [esp+14h] [ebp-4h]

  pMem = (char *)operator new(0x544u);
  v16 = 0;
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/LordofLight/LOL/Armor.equ", 0);
  else
    v3 = nullptr;
  v4 = *(uint32_t *)this;
  v16 = -1;
  pObj = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v4 + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  v16 = 1;
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/LordofLight/LOL/Glow.equ", 0);
  else
    v7 = nullptr;
  v8 = *(uint32_t *)this;
  v16 = -1;
  pObj2 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v8 + 784))(this, v7);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  v16 = 2;
  if ( pMem3 != nullptr )
    v11 = sub_4BA9E0(pMem3, "Monster/LordofLight/LOL/Wing.equ", 0);
  else
    v11 = nullptr;
  v12 = *(uint32_t *)this;
  v16 = -1;
  pObj3 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v12 + 784))(this, v11);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  *(this + 8644) = 0;
  v15 = 100000;
  return sub_4E1390(196614, &v15);
}



// ============================================================
// 【分区 3】空骨鱼·克罗库塔（SpaceFish / Crokuta）（0x5B3230-0x5B6380）
// 证据：SFISH_BUG_SPIT/BUG_FIRE/FIND/BITE/DMG/DIE、Particle/BugShot.ptl、
//       Particle/CrokutaDestroyHead.ptl + JOINT1-5/TAIL 分段破坏（0x5B4430）、BUFF_TAKE、
//       ★ 0x5B4820-0x5B6380 缺口区在 missing_monster.cpp（含 vmt200 覆写 0x5B4D90）

// 子类扩展字段复位（this+8600..8620）
// ------------------------------------------------------------
// 0x5B3230 sub_5B3230 —— 空骨鱼·子类字段复位
// this+8600=1、+8612/+8620 两字节标志清零、this+8616（this[2154] 特效槽）=0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3230(int this)
{
  *(uint32_t *)(this + 8600) = 1;
  *(uint8_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8616) = 0;
  return 0;
}



// 虫弹技能：引用 Particle/BugShot.ptl（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B3250 sub_5B3250 —— 空骨鱼·虫弹发射（BugShot）
// this[2152] 记 ·sub_699000 当前时钟作冷却基准；vt+308 目标门通过后，
// this+7028 子型 ==2 时经 vt+588 取 Particle/BugShot.ptl 资源，由 vt+580 发射对象 30013
// （参数取 this[2150] AI 阈值字段，末位 4）【推断：子型 2 专属弹药外观】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3250(uint32_t *this)
{
  int result; // eax
  int v3; // eax

  *(this + 2152) = sub_699000((int)(this + 9));
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BugShot.ptl");
    else
      v3 = 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
             this,
             30013,
             *(this + 2150),
             v3,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
  }
  return result;
}



// AI 字段访问（this+8620）
// ------------------------------------------------------------
// 0x5B32C0 sub_5B32C0 —— 空骨鱼·目标切换横向补偿
// 先 ·sub_4D97E0(nArg2) 动作子对象状态槽直写；当 nArg2 非自身当前目标 this+7252 且非 0、
// 且其存活（vt+40 标记 17）时，经其 vt+700 列表刷新后由 ·sub_53FD00(nArg2)==1 判朝向；
// 满足则 this+7592 攻击段号槽 +50、this+8620 标志 0→1（反向再 -50、1→0），实现换目标时的横向对齐。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B32C0(int this, int nArg2)
{
  int fld_1C54; // ebx
  int fld_1DA8; // eax
  bool v5; // zf

  fld_1C54 = *(uint32_t *)(this + 7252);
  LOBYTE(fld_1DA8) = sub_4D97E0(nArg2);
  if ( fld_1C54 != nArg2 && nArg2 != 0 )
  {
    LOBYTE(fld_1DA8) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
    if ( (uint8_t)fld_1DA8 != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
      v5 = (uint8_t)sub_53FD00(nArg2) == 1;
      LOBYTE(fld_1DA8) = *(uint8_t *)(this + 8620);
      if ( v5 )
      {
        if ( (uint8_t)fld_1DA8 == 0 )
        {
          fld_1DA8 = *(uint32_t *)(this + 7592) + 50;
          *(uint8_t *)(this + 8620) = 1;
          *(uint32_t *)(this + 7592) = fld_1DA8;
        }
      }
      else if ( (uint8_t)fld_1DA8 == 1 )
      {
        fld_1DA8 = *(uint32_t *)(this + 7592) - 50;
        *(uint8_t *)(this + 8620) = 0;
        *(uint32_t *)(this + 7592) = fld_1DA8;
      }
    }
  }
  return fld_1DA8;
}



// 主状态门（this+200/8612）
// ------------------------------------------------------------
// 0x5B3350 sub_5B3350 —— 空骨鱼·虫弹触发门
// ·sub_4E1780 帧前处理后，vt+840 大状态 ==8 且 this+7028 子型为 1 或 2，this+8612 未置位时，
// 经 vt+200 动作对象 +170 标志非 0 才 ·0x5B3250 发虫弹并置 this+8612 防重入。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B3350(int this)
{
  int pThis_348; // eax

  sub_4E1780((uint32_t *)this);
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 == 8 && (sub_41A5E0(this + 7028) == 1 || (pThis_348 = sub_41A5E0(this + 7028)) == 2) )
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8612);
    if ( (uint8_t)pThis_348 == 0 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( *(uint8_t *)(pThis_348 + 170) != 0 )
      {
        LOBYTE(pThis_348) = sub_5B3250((uint32_t *)this);
        *(uint8_t *)(this + 8612) = 1;
      }
    }
  }
  return pThis_348;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B33C0 sub_5B33C0 —— 空骨鱼·待机姿态写入
// 取 vt+184 姿态量，仅当 this[1639] 主状态镜像为 0 且姿态 ≠4 时，
// 经 vt+148(nArg2=姿态) 与 vt+144(姿态) 两级写回【推断：静止/游泳循环姿态】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B33C0(int *this)
{
  int v2; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  result = *(this + 1639);
  if ( result == 0 && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3400 sub_5B3400 —— 空骨鱼·技能变体甲装填
// this[2151] = 30010（对象/技能 ID 槽）、this[2154] = 1（变体号）；
// 与 ·0x5B34D0 乙型、·0x5B35C0 丙型构成三变体装填族【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3400(uint32_t *this)
{
  *(this + 2151) = 30010;
  *(this + 2154) = 1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3420 sub_5B3420 —— 空骨鱼·攻击参数面复位（甲向 -50）
// 清零 this+7531..7558 与 this+7564..7596 两段攻击/分身参数面，再置 this+7557=1、this+7588=1；
// nArg3==2 时改用 nArg2 作段号选择，所选为 0 则 this+7596 = -50（反向偏置）。
// 与 ·0x5B3510 同构，差异仅末项为 +50（乙向）；偏置供 ·0x5B32C0 换目标时横向对齐用【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3420(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint8_t *)(this + 7557) = 1;
  *(uint32_t *)(this + 7588) = 1;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = -50;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B34D0 sub_5B34D0 —— 空骨鱼·技能变体乙装填与属性注册
// this[2151] = 30011、this[2154] = 2（与 ·0x5B3400 甲型成对的第二变体【推断】）；
// 末经 ·sub_4E1390(196613, 100000) 注册技能/属性项。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B34D0(uint32_t *this)
{
  int v2; // [esp+0h] [ebp-4h] BYREF

  *(this + 2151) = 30011;
  *(this + 2154) = 2;
  v2 = 100000;
  return sub_4E1390(196613, &v2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3510 sub_5B3510 —— 与 ·0x5B3420 同构（差异：末项段号偏置为 +50 乙向）
// 攻击参数面复位后 this+7596 = +50，供另一侧换目标横向对齐【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3510(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint8_t *)(this + 7557) = 1;
  *(uint32_t *)(this + 7588) = 1;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5B35C0 sub_5B35C0 —— 空骨鱼·技能变体丙（出场参数插值装填）
// this[2151] = 30012；经 vt+384 取出场参数面 12/13 两点作插值起止，用 vt+672(3) 控制柄元素数 -1 作帧上限，
// ·sub_4049C0 浮点区间线性插值（t≥tEnd 返回终点，t≤0 返回起点）后写 this[2150] AI 阈值字段，this[2154]=0。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B35C0(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-1Ch]
  float v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+20h] [ebp-8h]
  int v8; // [esp+24h] [ebp-4h]

  v2 = *this;
  *(this + 2151) = 30012;
  v7 = (*(int (/*stdcall*/ **)(int))(v2 + 384))(12);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2150) = result;
  *(this + 2154) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3640 sub_5B3640 —— 缓速动画对象生成（0x8C 参数体）
// ·sub_4DE410 名称模板与随机倒计时 → vt+700 激活族 → ·sub_53F6A0 注册；new(0x8C) 经
// ·sub_64CEF0(300,3000,100.0f,10) 构造后由 vt+56 绑定到本体【推断：迟缓/冻缓附着效果】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3640(void *this)
{
  int pObj; // eax

  sub_4DE410();
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 700))(this);
  sub_53F6A0(this);
  if ( operator new(0x8Cu) != nullptr )
    pObj = sub_64CEF0(300, 3000, 1120403456, 10);
  else
    pObj = 0;
  return (*(int (/*thiscall*/ **)(int, void *, void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
           pObj,
           this,
           this,
           0,
           0,
           0,
           -1);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B36E0 sub_5B36E0
// ------------------------------------------------------------
// attributes: thunk
int sub_5B36E0()
{
  return sub_6098E0();  // 【CNRDJoint__vmt14C】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B36F0 sub_5B36F0 —— 子相位索引映射（this+1008 → 编号）
// 读 *(this+252) 子相位：0/1/5/6→15、2→13、3→10、4→5、其余 0，供上层选资源/动画【推断：相位→资源档映射】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B36F0(uint32_t *this)
{
  int result; // eax

  switch ( *(this + 252) )
  {
    case 0:
    case 1:
    case 5:
    case 6:
      result = 15;
      break;
    case 2:
      result = 13;
      break;
    case 3:
      result = 10;
      break;
    case 4:
      result = 5;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}



// 时钟门+插值 AI（sub_699000+sub_4049C0）
// ------------------------------------------------------------
// 0x5B3740 sub_5B3740 —— 计时衰减收尾门（600ms 后复位句柄）
// this+264 非 1 时以 ·sub_699000 减 this+992 基准取帧差：有从属(this+120) 则 ·sub_4049C0 把 255→0
// 于 600ms 内插值写 vt+252 槽；差满 600（·0x258）时 vt+196 清动作句柄，本地玩家再 vt+312 收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3740(uint32_t *this)
{
  unsigned int fld_e248; // edi
  uint64_t v3; // rax

  if ( *((uint8_t *)this + 264) != 1 )
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )
    {
      v3 = (uint64_t)sub_4049C0(255.0, 0.0, fld_e248, 600);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, v3);
    }
    if ( fld_e248 >= 0x258 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
}



// AI 相位辅助（81L）
// ------------------------------------------------------------
// 0x5B37C0 sub_5B37C0 —— 齐射弹幕生成（发数 = 动画块 816×830 乘积）
// 存活/目标门(vt+308) 内取 vt+48/52 坐标，经 vt+672(3) 动画控制块读 +816(整数) 与 +830(浮点)，
// 相乘得发数后循环：vt+384(this,i+1) 取第 i 发参数、vt+580 发射（参数 4/0/14 + 坐标对），this+2151 为发射档；
// 每发循环末调全局 ·0x8F7C04 的 vt+1220【推断：坐标/时钟刷新，返回值未用】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B37C0(uint32_t *this)
{
  int result; // eax
  int16_t nY1; // ax
  int pVt; // edx
  int16_t nY2; // ax
  int pVt2; // edx
  int pAniCtrl3; // edi
  int nSpawnIdx; // edi
  int nNextIdx; // ebx
  int nSpawnItem; // eax
  int pVt3; // edx
  int16_t nSpawnRet; // di
  int fld_e2151; // [esp-34h] [ebp-50h]
  uint16_t aSpawnXY[2]; // [esp+4h] [ebp-18h] BYREF
  int16_t nParamX; // [esp+8h] [ebp-14h]
  int16_t nParamY; // [esp+Ah] [ebp-12h]
  int nProduct; // [esp+Ch] [ebp-10h]
  int16_t nLoopIdx16; // [esp+10h] [ebp-Ch]
  float fCtrl830; // [esp+14h] [ebp-8h]
  int nCtrl816; // [esp+18h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    aSpawnXY[0] = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
    nY1 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    pVt = *this;
    aSpawnXY[1] = nY1;
    nParamX = (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 48))(this);
    nY2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    pVt2 = *this;
    nParamY = nY2;
    pAniCtrl3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 672))(this, 3);
    nCtrl816 = sub_41A5E0(pAniCtrl3 + 816);
    fCtrl830 = COERCE_FLOAT(sub_41A5E0(pAniCtrl3 + 830));
    nProduct = (uint64_t)((double)nCtrl816 * fCtrl830);
    result = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 384))(
               this,
               (uint64_t)((double)nCtrl816 * fCtrl830) >> 32,
               0);
    nSpawnIdx = 0;
    fCtrl830 = *(float *)&result;
    if ( result > 0 )
    {
      do
      {
        nNextIdx = nSpawnIdx + 1;
        nSpawnItem = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, nSpawnIdx + 1);
        pVt3 = *this;
        fld_e2151 = *(this + 2151);
        nLoopIdx16 = nSpawnIdx;
        nSpawnRet = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint16_t *))(pVt3 + 580))(
                this,
                fld_e2151,
                nSpawnItem,
                0,
                0,
                0,
                0,
                0,
                4,
                0,
                14,
                aSpawnXY);
        nParamX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
        result = LODWORD(fCtrl830);
        nParamY = nSpawnRet;
        nSpawnIdx = nNextIdx;
      }
      while ( nNextIdx < SLODWORD(fCtrl830) );
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B38C0 sub_5B38C0 —— 交互收尾+模式门动画加速
// ·sub_4D9600 交互收尾（消费 this+7820 信息）后 vt+148 写姿态布尔（位置%2）。
// 全局 dword_8F7A24（·0x8F7A24） 状态 3/4/6 分支取对象，其首个整数落 15..16 段时把动画控制块
// +830(浮点) 与 +858(速率) 各 +0.2 后 vt+676 写帧【推断：全局档 15/16 为指定关卡/难度】；尾调本类齐射 0x5B37C0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B38C0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int *v4; // ecx
  int v5; // ecx
  unsigned int v6; // edi
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int v11; // [esp+8h] [ebp-4h]
  int v12; // [esp+8h] [ebp-4h]

  sub_4D9600();
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this) % 2;
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(v2 + 148))(this, v3 == 0);
  v4 = nullptr;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )
  {
    case 3:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
      break;
    case 4:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
      break;
    case 6:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
      break;
    default:
      break;
  }
  v5 = *v4;
  if ( v5 >= 15 && v5 <= 16 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v6)) + 0.2;
    sub_41A590(v6, v7, v11);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v8)) + 0.2;
    sub_41A590(v8, v9, v12);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return sub_5B37C0(this);
}



// 虫弹连射：SFISH_BUG_SPIT 蓄力 + SFISH_BUG_FIRE 发射（91L；this+8612 相位）
// ------------------------------------------------------------
// 0x5B39C0 sub_5B39C0 —— 虫鱼攻击事件分发（SFISH_BUG_SPIT/FIRE）
// 段 14 转发 vt+1144 直通事件参数；段 8 预检：8608 时间戳未满 3000ms 或全局 ·0x9B9414>=20 提前返回，
// 否则清 this+8612。基线 ·sub_4E33D0 后——段 5：vt+216 播 45931 并逐个子对象 vt+712(x,2)；
// 段 8 按攻击段(7028) 播 SFISH_BUG_SPIT(1)/SFISH_BUG_FIRE(2)，为 0 时子对象 vt+712(x,1) 且行为字 25 转 13。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B39C0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_e1769; // ecx
  unsigned int j; // edi
  int fld_e17692; // ecx

  if ( ArgList == 14 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 1144))(
             this,
             **(uint32_t **)(LODWORD(fArg3) + 4),
             *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4));
  if ( ArgList == 8 )
  {
    result = *(uint32_t *)(LODWORD(fArg3) + 4);
    if ( *(uint32_t *)result == 1 || *(uint32_t *)result == 2 )
    {
      if ( dword_9B9414 >= 20 )
        return result;
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 2152) + 3000 >= result )
        return result;
      *((uint8_t *)this + 8612) = 0;
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 45931);
    for ( i = 0; ; ++i )
    {
      fld_e1769 = *(this + 1769);
      if ( fld_e1769 == 0 )
        break;
      result = (*(this + 1770) - fld_e1769) >> 2;
      if ( i >= result )
        break;
      result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e1769 + 4 * i) + 712))(*(uint32_t *)(fld_e1769 + 4 * i), 2);
    }
  }
  else if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result != 0 )
    {
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "SFISH_BUG_SPIT",
                 -1,
                 0,
                 0);
      }
      else
      {
        result = sub_41A5E0((unsigned int)(this + 1757));
        if ( result == 2 )
          return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                   this,
                   "SFISH_BUG_FIRE",
                   -1,
                   0,
                   0);
      }
    }
    else
    {
      for ( j = 0; ; ++j )
      {
        fld_e17692 = *(this + 1769);
        if ( fld_e17692 == 0 )
          break;
        result = (*(this + 1770) - fld_e17692) >> 2;
        if ( j >= result )
          break;
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e17692 + 4 * j) + 712))(*(uint32_t *)(fld_e17692 + 4 * j), 1);
      }
      if ( *(this + 1787) == 25 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3B50 sub_5B3B50 —— 大状态进入副作用（特殊型 25 时半速化）
// 基线 ·sub_4DBA80 进入处理器；行为字 this+1787==25 时向 this+7620 对象 +12 写 100.0f 浮点，
// 并把 vt+1032 返回的速度源 +40 整数减半【推断：特殊态减速/护盾态】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3B50(uint32_t *this, int nArg2)
{
  int result; // eax
  int *v4; // ecx

  result = sub_4DBA80(nArg2);
  if ( *(this + 1787) == 25 )
  {
    *(uint32_t *)(*(this + 1905) + 12) = 1120403456;
    v4 = (int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) + 40);
    result = *v4 / 2;
    *v4 = result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3B90 sub_5B3B90 —— 大状态退出副作用（25 型还原对偶）
// 与 ·sub_5B3B50 对称：行为字 25 时向 this+7620 对象 +12 写 0 并把速度源 +40 翻倍还原，
// 尾调 ·sub_4DBC20 退出处理器。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3B90(uint32_t *this, int nArg2)
{
  int v2; // eax

  if ( *(this + 1787) == 25 )
  {
    *(uint32_t *)(*(this + 1905) + 12) = 0;
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this);
    *(uint32_t *)(v2 + 40) *= 2;
  }
  return sub_4DBC20(nArg2);
}



// 空骨鱼·吞噬计数反噬（114L）：pArg2(攻击者)存活时遍历其 vt+700 对象列表清点
//   存活成员(上限 this+2154)，按 计数×vt+348 单位值 反噬伤害并生成受击文本对象，
//   攻击者倒地(标记273)时额外用 880 号格式串(名字)向全局飘字池(-13487396 蓝)播报；
//   结尾 BUFF_TAKE 播报
// ------------------------------------------------------------
// 0x5B3BD0 sub_5B3BD0 —— 吞噬反噬+BUFF_TAKE（尾调反击判定）
// 攻击者 vt+700 对象列表清点存活成员至上限 this+2154（存活者经 vt+76(x,0) 逐个处理）；
// 倒地标记 273 时用 880 号名模板 + 全局 ·0x8F8528 飘字池 -13487396 蓝播报名字。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3BD0(uint32_t *this, uint32_t *pArg2, int nArg3, int nArg4)
{
  uint32_t *pArg22; // esi
  int pListVec; // edi
  int pVecBegin; // eax
  unsigned int nIdx; // esi
  int nCount; // ebx
  int pVecBegin2; // ecx
  int pListObj; // ecx
  int pVecBegin3; // ecx
  int pListObj2; // ecx
  uint32_t *pszNameBuf; // eax
  const char *pszFmt; // eax
  int *pTextObj; // eax
  int pTextObjVt; // edx
  float fCountF; // [esp+Ch] [ebp-130h]
  uint32_t *pNameBufSaved; // [esp+10h] [ebp-12Ch]
  int Block; // [esp+24h] [ebp-118h]
  void *Blocka; // [esp+24h] [ebp-118h]
  int nSwallowCnt; // [esp+28h] [ebp-114h]
  int nTotalDmg; // [esp+28h] [ebp-114h]
  char Buffer[256]; // [esp+2Ch] [ebp-110h] BYREF
  int dword_796E502; // [esp+12Ch] [ebp-10h]
  int v27; // [esp+138h] [ebp-4h]

  pArg22 = pArg2;
  dword_796E502 = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )
  {
    pListVec = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);
    pVecBegin = *(uint32_t *)(pListVec + 4);
    nIdx = 0;
    if ( pVecBegin != 0 )
      Block = (*(uint32_t *)(pListVec + 8) - pVecBegin) >> 2;
    else
      Block = 0;
    nCount = 0;
    nSwallowCnt = 0;
    if ( Block > 0 )
    {
      do
      {
        pVecBegin2 = *(uint32_t *)(pListVec + 4);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin2) >> 2 )
          pListObj = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else
          pListObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj + 92))(pListObj) != 0 )
        {
          pVecBegin3 = *(uint32_t *)(pListVec + 4);
          if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin3) >> 2 )
            pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
          else
            pListObj2 = 0;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pListObj2 + 76))(pListObj2, 0);
          if ( ++nCount >= *(this + 2154) )
            break;
        }
        ++nIdx;
      }
      while ( (int)nIdx < Block );
      nSwallowCnt = nCount;
      if ( nCount > 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 956))(pArg2);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )
        {
          if ( pArg2[78] < 0x10u )
            pszNameBuf = pArg2 + 73;
          else
            pszNameBuf = (uint32_t *)pArg2[73];
          pNameBufSaved = pszNameBuf;
          pszFmt = (const char *)sub_422E70(880);
          sprintf(Buffer, pszFmt, pNameBufSaved);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -13487396, 0, -1);
        }
      }
    }
    nTotalDmg = (uint64_t)((double)nSwallowCnt * *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this));  // 反噬总伤害=吞噬计数×vt+348 单位值【推断】
    if ( nTotalDmg > 0 )
    {
      Blocka = operator new(0x80u);
      v27 = 0;
      if ( Blocka != nullptr )
      {
        fCountF = (float)nTotalDmg;
        pTextObj = (int *)sub_4D6810(LODWORD(fCountF), 1000, 1, 1);  // 创建受击/飘字对象(数值,1000,1,1)【推断】
      }
      else
      {
        pTextObj = nullptr;
      }
      pTextObjVt = *pTextObj;
      v27 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(
        pTextObj,
        this,
        this,
        0,
        0,
        0,
        -1);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BUFF_TAKE", -1, 0, 0);
    }
    pArg22 = pArg2;
  }
  return sub_4DB480(pArg22, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3E00 sub_5B3E00 —— 相位→资源装载（this+1004 计数 3 倍）
// 子相位 this+1008<=6 时把句柄表 *(this+144+4×相位) 经 vt+196 装载；this+1004 写 3×vt+708。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E00(unsigned int *this)
{
  unsigned int fld_e252; // eax
  int result; // eax

  fld_e252 = *(this + 252);
  if ( fld_e252 <= 6 )
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * fld_e252));
  result = 3 * (*(int (/*thiscall*/ **)(unsigned int *))(*this + 708))(this);
  *(this + 251) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3E40 sub_5B3E40 —— 动画子链切换门（this+972 序号缓存）
// 序号变化时 ·sub_609720 走 RTTI 虚方法：1=相位 5 复位帧游标 *(this+144)+28、相位 6 用 +32（先
// ·sub_4926A0 复位再 vt+196 取句柄）后 vt+596(this,1)；2=vt+260(this,1,5,-1) 起攻击段【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E40(int *this, int nArg2)
{
  int result; // eax
  uint32_t *fld_e36; // eax

  result = *(this + 243);
  if ( result != nArg2 )
  {
    result = sub_609720(nArg2);  // 【CNRDJoint__vmt2C8】
    if ( nArg2 == 1 )
    {
      if ( *(this + 252) == 5 )
      {
        sub_4926A0(*(uint32_t *)(*(this + 36) + 28));
        fld_e36 = (uint32_t *)(*(this + 36) + 28);
      }
      else
      {
        if ( *(this + 252) != 6 )
          return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
        sub_4926A0(*(uint32_t *)(*(this + 36) + 32));
        fld_e36 = (uint32_t *)(*(this + 36) + 32);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *fld_e36);
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
    }
    if ( nArg2 == 2 )
      return (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 260))(this, 1, 5, -1);
  }
  return result;
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x5B3EF0 sub_5B3EF0 —— 播放态收尾门（+170 标记）
// vt+200 取主状态对象，其 +170 非 0（播放完毕标记）时按子相位经 vt+196 装载句柄表
// *(this+144+4×相位)【推断：动画播完回落到相位默认资源】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3EF0(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * *(this + 252)));
  return result;
}



// 空骨鱼语音装载：SFISH_FIND/BITE/DMG/DIE 四件套（sub_4015C0+sub_699000）
// ------------------------------------------------------------
// 0x5B3F30 sub_5B3F30 —— 空骨鱼语音四件套 + 时间戳（this+8608）
// ·sub_4015C0 依次装载 SFISH_FIND/BITE（10 字节）与 SFISH_DMG/DIE（9 字节）；
// 末 ·sub_699000 记时间戳入 this+8608，供 ·sub_5B39C0 的 3000ms 门比对。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3F30(uint32_t *this)
{
  int result; // eax

  sub_4015C0("SFISH_FIND", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_BITE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DIE", 9u);  // 【std::string构造赋值】
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2152) = result;
  return result;
}



// AI 相位辅助（69L）
// ------------------------------------------------------------
// 0x5B3F90 sub_5B3F90 —— 映射对象筛选→setState 14（架招/牵制态）
// 遍历 *(this+116) 对象列表，取 vt+40 标记 545 的映射物；经 vt+1244(this,obj) 校验且其
// vt+340 返回值 ==258 时，用 ·sub_430C80 打包该对象 vt+120/124 坐标（两组），再 vt+560 切 14 态。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3F90(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int pVecBegin; // edx
  int nCnt; // eax
  int pVecBegin2; // edx
  int pMapObj; // ecx
  int fld_e292; // ecx
  int pVecBegin3; // edx
  int *pFoundObj; // esi
  int pFoundObjVt; // edx
  uint8_t v12[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  void *Src; // [esp+14h] [ebp-1Ch]
  int v15; // [esp+18h] [ebp-18h]
  uint32_t *pThis; // [esp+1Ch] [ebp-14h]
  int aParamVec[4]; // [esp+20h] [ebp-10h] BYREF

  pThis = this;
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    pVecBegin = *(uint32_t *)(fld_e29 + 8);
    nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;
    if ( (int)i >= nCnt )
      break;
    pVecBegin2 = *(uint32_t *)(fld_e29 + 8);
    if ( pVecBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - pVecBegin2) >> 2 )
      pMapObj = *(uint32_t *)(pVecBegin2 + 4 * i);
    else
      pMapObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pMapObj + 40))(pMapObj, 545) != 0 )
    {
      fld_e292 = *(this + 29);
      pVecBegin3 = *(uint32_t *)(fld_e292 + 8);
      if ( pVecBegin3 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - pVecBegin3) >> 2 )
        pFoundObj = *(int **)(pVecBegin3 + 4 * i);
      else
        pFoundObj = nullptr;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *))(*this + 1244))(this, pFoundObj) != 0
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pFoundObj + 340))(pFoundObj) == 258 )
      {
        if ( pFoundObj != nullptr )
        {
          Block = nullptr;
          Src = nullptr;
          v15 = 0;
          pFoundObjVt = *pFoundObj;
          aParamVec[3] = 0;
          aParamVec[0] = (*(int (/*thiscall*/ **)(int *))(pFoundObjVt + 120))(pFoundObj);
          sub_430C80(nullptr, 1, (int)aParamVec);
          aParamVec[0] = (*(int (/*thiscall*/ **)(int *))(*pFoundObj + 124))(pFoundObj);
          sub_430C80(nullptr, 1, (int)aParamVec);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pThis + 560))(pThis, 14, v12, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
        }
        return;
      }
    }
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B4120 sub_5B4120 —— 存活门内 setState 8 起手（参数表打包）
// vt+308 目标门内：·sub_431230 打包初值 0 为参数表 v3，经 vt+560(this,8,v3,0,0) 切 8 号状态，
// 释放缓冲后尾调 ·sub_4D9F40【推断：攻击段起手封装】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4120(void *this)
{
  uint8_t v3[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+10h] [ebp-14h]
  int v7; // [esp+14h] [ebp-10h] BYREF
  int v8; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
  {
    Block = nullptr;
    v5 = 0;
    v6 = 0;
    v8 = 0;
    v7 = 0;
    sub_431230((int)v3, &v7);
    (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 8, v3, 0, 0);
    v8 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v5 = 0;
    v6 = 0;
  }
  return sub_4D9F40(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B41C0 sub_5B41C0 —— 行为字决策+低血线触发（VT 家族 AI 节拍）
// ·sub_4E0120 基线后按行为字 this[1787]：0→vt+1284 空闲例程；4→有目标(pArg1[1813]) 时 2% 概率
// vt+1104 写 5；5→有目标 2% 写 4、无目标写 13；13/14/15→有目标写 4。
// 末门：当前血 vt+736 < 上限 vt+740 的 50% 且非 25 态时调 ·sub_5B3F90 切 14（架招）【推断：血线反制】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B41C0(uint32_t *this)
{
  float v2; // [esp+4h] [ebp-8h]

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      if ( rand() % 100 < 2 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        if ( rand() % 100 < 2 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      }
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
LABEL_11:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      break;
    default:
      break;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v2 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.5 > v2 && *(this + 1787) != 25 )
      sub_5B3F90(this);
  }
}



// 破坏特效：PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl（头部击破, 53L）
// ------------------------------------------------------------
// 0x5B42F0 sub_5B42F0 —— 头部击破粒子（CrokutaDestroyHead.ptl）
// new(0x12C) 经 ·sub_428F30(ptl 路径, 本体) 构造，vt+12(0) 起播、vt+40 坐标对齐（vt+128→124→120 链）；
// 粒子参数块 +15..+35 交替写 800/500（六向喷射量），+76 随机 0-359 初角，·sub_4600B0 投递映射层后 vt+0(1) 激活。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B42F0(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *pHeadPtl; // esi
  int pHeadPtlVt; // eax
  int pHeadPtlVt2; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int nRand; // ebx
  void *fld_e29; // ecx
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v14; // [esp+28h] [ebp-4h]

  pMem = operator new(0x12Cu);
  pMem2 = pMem;
  v14 = 0;
  if ( pMem != nullptr )
    pHeadPtl = sub_428F30(pMem, (int)"PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl", (int)this);
  else
    pHeadPtl = nullptr;
  pHeadPtlVt = *pHeadPtl;
  v14 = -1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(pHeadPtlVt + 12))(pHeadPtl, 0);
  pHeadPtlVt2 = *pHeadPtl;
  nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ);
  nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nY);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(pHeadPtlVt2 + 40))(pHeadPtl, nX);
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 15) = 800;  // 粒子参数块(+15..+35) 800/500 交替【推断：六向喷射量】
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 19) = 500;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 23) = 800;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 27) = 500;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 31) = 800;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 35) = 500;
  nRand = rand() % 360;  // 随机初始角度(0-359 度)
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 76) = nRand;
  (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *))(*pHeadPtl + 92))(pHeadPtl, v11);
  fld_e29 = (void *)*(this + 29);
  v14 = 1;
  sub_4600B0(fld_e29, 2, 0, (int)v11);
  (*(void (/*thiscall*/ **)(uint32_t *, int))*pHeadPtl)(pHeadPtl, 1);
  if ( Block != nullptr )
    j__free(Block);
}



// 分段破坏系统：JOINT1-5 + TAIL 部位播报 + Particle/CrokutaDestroy%s.ptl 按部位加载
//   （91L；克罗库塔节段破坏 = 部位破坏玩法的客户端实现）
// ------------------------------------------------------------
// 0x5B4430 sub_5B4430 —— 分节破坏粒子（按子相位取 JOINT 部位名）
// this+264!=1 时以 ·sub_699000 时间差经 ·sub_4049C0(255→80, 500ms) 写 vt+252 渐变槽【推断：淡出】；
// 满 500ms 后按子相位 this+1008 索引部位名表 JOINT1..5/TAIL，sprintf 拼 Particle/CrokutaDestroy%s.ptl，
// new(0x12C)+·sub_4C3640 生成并同族填充 800/500 参数与随机初角，末 vt+196 清句柄、本地玩家 vt+312 收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B4430(uint32_t *this)
{
  unsigned int fld_e248; // esi
  uint64_t nLerpVal; // rax
  int nSegIdx; // eax
  int *pSegPtl; // esi
  int pSegPtlVt; // eax
  int pSegPtlVt2; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int nRand; // ebx
  void *fld_e29; // ecx
  void *pMem; // [esp+4h] [ebp-230h]
  uint32_t v14[3]; // [esp+8h] [ebp-22Ch]
  const char *v15; // [esp+14h] [ebp-220h] BYREF
  void *Block; // [esp+18h] [ebp-21Ch]
  char (**v17)[10]; // [esp+1Ch] [ebp-218h]
  const char *v18; // [esp+20h] [ebp-214h]
  char Buffer[512]; // [esp+24h] [ebp-210h] BYREF
  int dword_796E502; // [esp+224h] [ebp-10h]
  int v21; // [esp+230h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *((uint8_t *)this + 264) != 1 )
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )
    {
      nLerpVal = (uint64_t)sub_4049C0(255.0, 80.0, fld_e248, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, nLerpVal);
    }
    if ( fld_e248 >= 0x1F4 )
    {
      nSegIdx = *(this + 252);
      v14[0] = "JOINT1";
      v14[1] = "JOINT2";
      v14[2] = "JOINT3";
      v15 = "JOINT4";
      Block = "JOINT5";
      v17 = &off_72F738;
      v18 = "TAIL";
      sprintf(Buffer, "Particle/CrokutaDestroy%s.ptl", (const char *)v14[nSegIdx]);
      pMem = operator new(0x12Cu);
      v21 = 0;
      if ( pMem != nullptr )
      {
        if ( *(this + 96) < 0x10u )
          pSegPtl = (int *)sub_4C3640(this + 91, Buffer, this);
        else
          pSegPtl = (int *)sub_4C3640(*(this + 91), Buffer, this);
      }
      else
      {
        pSegPtl = nullptr;
      }
      pSegPtlVt = *pSegPtl;
      v21 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(pSegPtlVt + 12))(pSegPtl, 0);
      pSegPtlVt2 = *pSegPtl;
      nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ);
      nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nY);
      (*(void (/*thiscall*/ **)(int *, int))(pSegPtlVt2 + 40))(pSegPtl, nX);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 15) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 19) = 500;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 23) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 27) = 500;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 31) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 35) = 500;
      nRand = rand() % 360;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 76) = nRand;
      (*(void (/*thiscall*/ **)(int *, const char **))(*pSegPtl + 92))(pSegPtl, &v15);
      fld_e29 = (void *)*(this + 29);
      v21 = 1;
      sub_4600B0(fld_e29, 2, 0, (int)&v15);
      (*(void (/*thiscall*/ **)(int *, int))*pSegPtl)(pSegPtl, 1);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B46A0 sub_5B46A0 —— 映射对象族判定（vt+340 ∈ 250..253）
// vt+340 返回指针所指数值做 {250..253} 四值判定【推断：载体/子弹族标签；调用方多为同源(vt+376) 确认，结果常被丢弃】。
// ------------------------------------------------------------
bool /*cdecl*/ sub_5B46A0(int nArg1)
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 250
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 251
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 252
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 253;
}



// 子类扩展字段复位（this+8604..8652, 26L）
// ------------------------------------------------------------
// 0x5B4700 sub_5B4700 —— 子类扩展清零（含 6792..6808 计数槽）
// 清 6792/6796/6800/6804/6808 五槽与 8604/8605/8612/8632/8633/8652 标记字节，
// 8608/8640/8644/8648 归零、8636 写 0xFFFF 哨兵【推断：复活/换阶段时的整块初始化】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4700(int this)
{
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8633) = 0;
  *(uint32_t *)(this + 8636) = 0xFFFF;
  *(uint32_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8652) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B4770 sub_5B4770 —— 伤害折减门（×0.7）
// ·sub_4DC390 伤害过滤结果==3、或攻击方档位体（vt+348 返回）+128 字节非 0 时原样返回；
// 否则首参（伤害值）乘 0.7 并返回 0【推断：类型 3/带飞行标记者免折减，其余减伤 30%】。
// ------------------------------------------------------------
int /*stdcall*/ sub_5B4770(int *pDwArg1, int nArg2)
{
  int v2; // esi

  v2 = sub_4DC390(pDwArg1, nArg2);
  if ( v2 == 3 || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) != 0 )
    return v2;
  *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
  return 0;
}



// ============================================================
// 【分区 4】ZGM 机动怪（高达梗：Rx78/Ez8 系粒子在 0x5C 区）（0x5B6380-0x5B8120）
// 证据：ZGM_ATK/ZGM_SPRING/ZGM_DIE、MOVING_ATTACK_LOOP、SHIELD_FLASH、
//       Particle/Dagger.ptl + THROW_STONE 投刀

// ZGM 攻击主循环（198L；usercall 三寄存器参）：大状态8(攻击)/14(盾)/15 分流，攻击子类型
//   this+7028 再分流——3=飞行高度钳制(vt+128<30 强制回到高度30)+本地玩家 1s 时钟门归位；
//   1/4=受击段(命中数>=1 时 vt+876 击退 80~200 + vt+152(4) 火花 + sub_4A0550 镜头幅度
//   120~300)；5=距离>130 播 ZGM_ATK 并 vt+196 切 +8 资源句柄，<15 切 +12 近战句柄
// ------------------------------------------------------------
// 0x5B6380 sub_5B6380 —— ZGM 攻击主循环（命中/高度/近远战三支）
// 命中段 1/4：受击反馈——vt+876 击退 80~200（4 型 300），vt+152(4) 取火花句柄经 vt+896 换帧、
// ·sub_4A0550 镜头幅度 120/150；段 3：高度 vt+128<30 强制抬回 30、本地 1s 时钟门(vt+844) 归位；
// 段 5：距离>130 播 ZGM_ATK 并把 vt+196 切 this+6216 的 +8 资源、<15 切 +12 近战句柄；
// 大状态 14 转 ·sub_5B5390、15 按从属帧 192==4 经 vt+876/vt+896 换姿并 sub_491C70+sub_493A60 帧推进。
// ------------------------------------------------------------
void /*usercall*/ sub_5B6380(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  char nIsLocal; // al
  int pVt; // edi
  int nZ30; // eax
  int pBuddy; // edi
  int nAnimId; // eax
  int pBuddy2; // edi
  int nAnimId2; // eax
  int pVt2; // edi
  int nYClamped; // eax
  int nXClamped; // eax
  int nClockObj844; // eax
  char nIsLocal2; // al
  int pBuddy3; // edi
  int nAnimId3; // eax
  char nIsLocal3; // al
  int pVt3; // edi
  int hAniKind4; // eax
  int nCamAmp; // edi
  char nFallFlag; // cl
  int pBuddy128; // edx
  uint32_t *pResSlot8; // edi
  uint32_t *pResSlot12; // edi

  sub_4E1780(pDwArg1);
  if ( pDwArg1[1639] != 8 )
  {
    if ( pDwArg1[1639] == 14 )
    {
      sub_5B5390(pDwArg1, nArg2, nArg3);
    }
    else if ( pDwArg1[1639] == 15 )
    {
      nIsLocal2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 308))(pDwArg1, nArg3);
      if ( nIsLocal2 != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
      }
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        pBuddy3 = pDwArg1[30];
        nAnimId3 = sub_491C70(pBuddy3, 1);
        sub_493A60(pBuddy3, nAnimId3);
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
    }
    return;
  }
  if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 0
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 2
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 6 )
  {
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 1 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 4 )
    {
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 30 )
        {
          pVt2 = *pDwArg1;
          nYClamped = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 124))(pDwArg1, 30, nArg3);
          nXClamped = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nYClamped);
          (*(void (/*thiscall*/ **)(int *, int))(pVt2 + 112))(pDwArg1, nXClamped);
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          nClockObj844 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 844))(pDwArg1);
          if ( sub_699000(nClockObj844) > 1000 )  // 【clock_now(clk)】
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
        }
      }
      return;
    }
    nIsLocal3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
    if ( nIsLocal3 == 0 )
      goto LABEL_60;
    if ( *(int *)(pDwArg1[30] + 148) >= 1 )
    {
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
        goto LABEL_57;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 80, 80, 0, 0, 0);
      pVt3 = *pDwArg1;
      hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      (*(void (/*thiscall*/ **)(int *, int))(pVt3 + 896))(pDwArg1, hAniKind4);
      nCamAmp = 150;
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )
        nCamAmp = 300;
      sub_4A0550(nCamAmp);
    }
    if ( *((uint8_t *)pDwArg1 + 8604) == 0 )
    {
LABEL_60:
      nFallFlag = *((uint8_t *)pDwArg1 + 8604);
      if ( nFallFlag != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
        *((uint8_t *)pDwArg1 + 8605) = 1;
      pBuddy128 = pDwArg1[28];
      if ( *(float *)(pBuddy128 + 24) > 0.0 && nFallFlag == 0 )
        *((uint8_t *)pDwArg1 + 8604) = 1;
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
      {
        if ( *(float *)(pBuddy128 + 24) > 0.0 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) > 130 )
        {
          pResSlot8 = (uint32_t *)(pDwArg1[1554] + 8);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *pResSlot8 )
          {
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATK", -1, 0, 0);
            (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 344))(pDwArg1, pDwArg1[139] + 152);
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));
          }
        }
        if ( *((uint8_t *)pDwArg1 + 8604) != 0
          && *(float *)(pDwArg1[28] + 24) < 0.0
          && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 15 )
        {
          pResSlot12 = (uint32_t *)(pDwArg1[1554] + 12);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *pResSlot12 )
          {
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));
          }
        }
      }
      return;
    }
LABEL_57:
    if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
    }
    goto LABEL_60;
  }
  nIsLocal = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( nIsLocal == 0 )
    goto LABEL_24;
  if ( *(int *)(pDwArg1[30] + 148) >= 1 )
  {
    if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    {
LABEL_21:
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
      }
LABEL_24:
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        pBuddy = pDwArg1[30];
        nAnimId = sub_491C70(pBuddy, 15);
        sub_493A60(pBuddy, nAnimId);
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      goto LABEL_28;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 200, 200, 0, 0, 0);
    pVt = *pDwArg1;
    nZ30 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 896))(pDwArg1, nZ30);
    sub_4A0550(120);
  }
  if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    goto LABEL_21;
LABEL_28:
  if ( *(float *)(pDwArg1[28] + 24) > 0.0 && *((uint8_t *)pDwArg1 + 8604) == 0 )
  {
    pBuddy2 = pDwArg1[30];
    if ( *(int *)(pBuddy2 + 148) < 1 )
    {
      nAnimId2 = sub_491C70(pBuddy2, 1);
      sub_493A60(pBuddy2, nAnimId2);
    }
    *((uint8_t *)pDwArg1 + 8604) = 1;
  }
}


// 移动攻击：MOVING_ATTACK_LOOP 播报（83L）
// ------------------------------------------------------------
// 0x5B6420 sub_5B6420 —— 移动攻击循环装配（MOVING_ATTACK_LOOP）
// 先调 ·sub_5B6380 基循环；大状态 8 且子类型 7028==5 时钳高度 30 并比对资源槽 this+6216+20：
// 相同则 6560 钟<10s 内当 8660 钟达 8684 截止时重设 8660=1428ms 循环钟（本地门内兼 sub_5B51D0 与 vt+352 收招）；不同且 6560 钟计已满 2s 时
// 切 +16/+20 资源、vt+208 写帧、清 6573/6574、重设 6560/8660 双钟并播 MOVING_ATTACK_LOOP。
// ------------------------------------------------------------
int /*usercall*/ sub_5B6420@<eax>(int pArg1@<ecx>, int nArg2@<edi>)
{
  int nBigState; // eax
  int pVt; // edi
  int nY30; // eax
  int nXClamped; // eax
  uint32_t *pResSlot20; // edi
  int result; // eax
  int nPhaseDeadline; // [esp+8h] [ebp-4h]

  sub_5B6380((int *)pArg1, nArg2);
  nBigState = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  if ( nBigState == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) == 5 )
    {
      pVt = *(uint32_t *)pArg1;
      nY30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, 30);
      nXClamped = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, nY30);
      (*(void (/*thiscall*/ **)(int, int))(pVt + 112))(pArg1, nXClamped);
      pResSlot20 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) == *pResSlot20 )
      {
        if ( sub_699000(pArg1 + 6560) < 10000 )  // 【clock_now(clk)】
        {
          nPhaseDeadline = *(uint32_t *)(pArg1 + 8684);
          if ( sub_699000(pArg1 + 8660) >= nPhaseDeadline )  // 【clock_now(clk)】
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
              sub_5B51D0(pArg1);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
            *(uint8_t *)(pArg1 + 8673) = 0;
            *(uint8_t *)(pArg1 + 8674) = 0;
            sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          }
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && *(uint32_t *)(pArg1 + 616) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
        }
      }
      else if ( sub_699000(pArg1 + 6560) >= 2000 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 16));
        sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));
        *(uint8_t *)(pArg1 + 6573) = 0;
        *(uint8_t *)(pArg1 + 6574) = 0;
        sub_698F90(pArg1 + 6560, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        *(uint8_t *)(pArg1 + 8673) = 0;
        *(uint8_t *)(pArg1 + 8674) = 0;
        sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        sub_5B51D0(pArg1);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "MOVING_ATTACK_LOOP",
          9,
          0,
          0);
        *(uint8_t *)(pArg1 + 8652) = 1;
      }
    }
  }
  else if ( nBigState == 16
         && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0
         && (*(uint8_t (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pArg1 + 1248))(pArg1, 2, *(uint32_t *)(pArg1 + 7252)) == 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  if ( result != 8 && *(uint8_t *)(pArg1 + 8652) == 1 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);
    *(uint8_t *)(pArg1 + 8652) = 0;
  }
  return result;
}



// ZGM 死亡：ZGM_DIE 播报（sub_4015C0+sub_4049C0）
// ------------------------------------------------------------
// 0x5B6630 sub_5B6630 —— ZGM 死亡插值（ZGM_DIE 语音 + this+8620 槽）
// 先 ·sub_4015C0 装载 ZGM_DIE（7 字节）；取 vt+384(0/1) 两端值，以动画控制块首字段相对
// this+7280 的偏移为 t、this+7284−7280 为区间长，·sub_4049C0 插值写入 this+8620（死亡表现槽）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B6630(uint32_t *this)
{
  int fld_e1821; // edi
  uint32_t *pCtrl3; // eax
  uint64_t result; // rax
  float fFrom; // [esp+Ch] [ebp-20h]
  float fTo; // [esp+10h] [ebp-1Ch]
  int nFromI; // [esp+24h] [ebp-8h]
  int nToI; // [esp+28h] [ebp-4h]

  sub_4015C0("ZGM_DIE", 7u);  // 【std::string构造赋值】
  nFromI = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  nToI = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fTo = (float)nToI;
  fFrom = (float)nFromI;
  result = (uint64_t)sub_4049C0(fFrom, fTo, *pCtrl3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;
  return result;
}



// 参数打包 AI（sub_431230+RTTI cast）
// ------------------------------------------------------------
// 0x5B66C0 sub_5B66C0 —— 星鱼绑定确认（RTTI cast + setState 17）
// nArg2 经 __RTDynamicCast 解为 CNStarFish 后，其 vt+52 与目标槽 this+8636 一致且本地门内时，
// ·sub_431230 打包 8636/星鱼 vt+48/52/本体 vt+48/52 五参，vt+560(this,17,v5,2,0) 切 17 号【推断：绑定/骑乘准备态】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B66C0(uint32_t *this, int nArg2)
{
  int nArg22; // edi
  int pStarFish; // edi
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  nArg22 = nArg2;
  if ( __RTDynamicCast(nArg2, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0 )
  {
    pStarFish = __RTDynamicCast(nArg22, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 52))(pStarFish) == *(this + 2159)
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v9 = 0;
      sub_431230((int)v5, this + 2159);
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 48))(pStarFish);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 52))(pStarFish);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      sub_431230((int)v5, &nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 17, v5, 2, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 参数打包 AI（sub_431230+RTTI cast, 73L）
// ------------------------------------------------------------
// 0x5B67F0 sub_5B67F0 —— 受击架招+分身焚化（吞噬者专支）
// 主状态镜像 8 且攻击段 0/2/6、nArg4 低字节为 0、本地门内、攻击者存活时：攻击者 vt+948 非 0 且本体 this+616 槽非 14 时
// 打包攻击者 vt+48/52 经 vt+560 切 14 态，并把 ·sub_432E50(vt+152) 火花经 vt+144 挂给攻击者；
// 本体 RTTI 为 CNStarFishDevourer 且段 0 时按 vt+348×0.9 构造 CNChangeHp 包(500,1,1)；尾调 ·sub_4DB480 反击判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B67F0(uint32_t *this, int *Block, int nArg3, int nArg4)
{
  int *pAttacker; // edi
  int pVt; // edx
  int pAttackerVt; // ebx
  int nProp152; // eax
  int pSparkRes; // eax
  int *pTextObj; // eax
  int pTextObjVt; // edx
  float fDmgVal; // [esp+18h] [ebp-38h]
  void *pBuf[4]; // [esp+34h] [ebp-1Ch] BYREF
  int v15; // [esp+4Ch] [ebp-4h]

  pAttacker = Block;
  if ( *(this + 1639) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 0
     || sub_41A5E0((unsigned int)(this + 1757)) == 2
     || sub_41A5E0((unsigned int)(this + 1757)) == 6)
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pAttacker + 948))(pAttacker) != 0 && *(this + 154) != 14 )
    {
      memset(&pBuf[1], 0, 12);
      pVt = *pAttacker;
      v15 = 0;
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(pVt + 48))(pAttacker);
      sub_431230((int)pBuf, &Block);
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(*pAttacker + 52))(pAttacker);
      sub_431230((int)pBuf, &Block);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
      v15 = -1;
      sub_5E5260(pBuf);
    }
    pAttackerVt = *pAttacker;
    nProp152 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    pSparkRes = sub_432E50(nProp152);
    (*(void (/*thiscall*/ **)(int *, int))(pAttackerVt + 144))(pAttacker, pSparkRes);
  }
  if ( __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishDevourer `RTTI Type Descriptor', 0) != 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 0 )
  {
    Block = (int *)operator new(0x80u);
    v15 = 1;
    if ( Block != nullptr )
    {
      fDmgVal = *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) * 0.89999998;
      pTextObj = (int *)sub_4D6810(LODWORD(fDmgVal), 500, 1, 1);
    }
    else
    {
      pTextObj = nullptr;
    }
    pTextObjVt = *pTextObj;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(
      pTextObj,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  return sub_4DB480(pAttacker, nArg3, nArg4);
}



// 参数打包 AI（95L sub_431230）
// ------------------------------------------------------------
// 0x5B69C0 sub_5B69C0 —— 骑乘载具放生（8608 槽清空）
// 载具槽 this+8608 非空时：vt+604/612 放归，先按槽内落点 8640/8644/8648 经 vt+136/112 归位；
// 失败则 vt+124(载具,300,1,1) 试探并经 vt+140 写回落点；载具为本地时打包 [4,0,1,200,200] 经 vt+560 切 4 态并 vt+564 收尾；
// 末段 8612<8620 且 vt+772(载具,5) 与本地门成立时 vt+764(载具,5,0,本体,1) 掷出，槽清 0。
// ------------------------------------------------------------
void /*usercall*/ sub_5B69C0(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int pRideObj; // ecx
  int pRideObj2; // edi
  int pRideVt; // edx
  int nTryY; // eax
  int nTryX; // eax
  char bMoveOk; // al
  int pRideObj3; // ecx
  int pRideVt2; // edi
  int nAltY; // eax
  int nAltX; // eax
  char v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int nPackVal; // [esp+18h] [ebp-10h] BYREF
  int v18; // [esp+24h] [ebp-4h]

  pRideObj = pDwArg1[2152];
  if ( pRideObj != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pRideObj + 604))(pRideObj, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 136))(
           pDwArg1[2152],
           pDwArg1[2160],
           pDwArg1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 112))(pDwArg1[2152], pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
    }
    else
    {
      pRideObj2 = pDwArg1[2152];
      pRideVt = *(uint32_t *)pRideObj2;
      nPackVal = pRideObj2;
      nPackVal = *pDwArg1;
      nTryY = (*(int (/*thiscall*/ **)(int, int, int, int))(pRideVt + 124))(pRideObj2, 300, 1, 1);
      nTryX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pRideObj2 + 120))(pRideObj2, nTryY);
      bMoveOk = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(nPackVal + 140))(pDwArg1, pDwArg1 + 2160, pDwArg1 + 2161, nTryX);
      pRideObj3 = pDwArg1[2152];
      if ( bMoveOk != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pRideObj3 + 112))(pRideObj3, pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
      }
      else
      {
        pRideVt2 = *(uint32_t *)pRideObj3;
        nAltY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2162]);
        nAltX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nAltY);
        (*(void (/*thiscall*/ **)(int, int))(pRideVt2 + 112))(pDwArg1[2152], nAltX);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      v18 = 0;
      nPackVal = 4;
      sub_431230((int)v13, &nPackVal);
      nPackVal = 0;
      sub_431230((int)v13, &nPackVal);
      nPackVal = 1;
      sub_431230((int)v13, &nPackVal);
      nPackVal = 200;
      sub_431230((int)v13, &nPackVal);
      nPackVal = 200;
      sub_431230((int)v13, &nPackVal);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 564))(pDwArg1[2152]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 848))(pDwArg1[2152], 0);
    if ( pDwArg1[2153] < pDwArg1[2155]
      && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 772))(pDwArg1[2152], 5) != 0
      && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
    }
    pDwArg1[2152] = 0;
  }
}



// 参数打包 AI（this+8632 相位）
// ------------------------------------------------------------
// 0x5B6C00 sub_5B6C00 —— 低血召唤门（setState 16）
// 本地门且目标槽 this+8656 空、8632 未置时，当前血 vt+736 ≤ 上限 vt+740 ×0.3 →
// ·sub_5B6080 生成召唤体，非空则打包其 vt+48/52 经 vt+560(this,16,pBuf,0,0) 切 16 号【推断：濒死召唤/合体】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B6C00(uint32_t *this)
{
  int pVt; // eax
  uint32_t *pNewObj; // eax
  uint32_t *pNewObj2; // edi
  int pNewObjVt; // edx
  void *pBuf[4]; // [esp+4h] [ebp-24h] BYREF
  float fVal736; // [esp+14h] [ebp-14h] BYREF
  int nVal740; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 2164) == 0
    && *((uint8_t *)this + 8632) == 0 )
  {
    nVal740 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    pVt = *this;
    fVal736 = (float)nVal740;
    nVal740 = (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 740))(this);
    if ( (double)nVal740 * 0.30000001 >= fVal736 )
    {
      pNewObj = (uint32_t *)sub_5B6080(this);
      pNewObj2 = pNewObj;
      if ( pNewObj != nullptr )
      {
        memset(&pBuf[1], 0, 12);
        pNewObjVt = *pNewObj;
        v9 = 0;
        fVal736 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(pNewObjVt + 48))(pNewObj));
        sub_431230((int)pBuf, &fVal736);
        fVal736 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*pNewObj2 + 52))(pNewObj2));
        sub_431230((int)pBuf, &fVal736);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, pBuf, 0, 0);
        sub_5E5260(pBuf);
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B6CF0 sub_5B6CF0 —— 同源确认+自更新（转星鱼绑定）
// nArg2 带标记 529 且本体 vt+724==0 时按 vt+376 同族确认（·sub_5B46A0，结果丢弃）；nArg2 即本体时
// vt+1308 并把目标槽 this+8656 写 8；尾转 ·sub_5B66C0 星鱼绑定【推断：骑乘契约同步】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B6CF0(uint32_t *this, int nArg2)
{
  int v3; // ebx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
    if ( v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      sub_5B46A0(nArg2);
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
    *(this + 2164) = 8;
  }
  sub_5B66C0(this, nArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B6D70 sub_5B6D70 —— 销毁联动放生（载具槽 8608）
// 销毁对象 pDwArg3 即载具槽 this+8608 且大状态 14 时执行 ·sub_5B69C0 放生；pDwArg3 即本体且载具槽非空时
// 同样放生；尾调 ·sub_4D9170 销毁基线【推断：载具死亡/本体死亡双向解绑】。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B6D70@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(pDwArg3);
}



// ZGM 事件分发+弹射技能（118L）：事件17=弹簧双人顶飞——用事件参数 [1][2]/[3][4] 两对
//   键值经 sub_45EBE0 解算出两只 CNStarFish(RTTI cast)，A[2159]=参数[0]、把 B 的
//   vt+736(0,1) 数值经 vt+732 同步给 A【推断：蹦床互换位置/能量】；大状态14 时事件3/5
//   触发 vt+764(5) 骑乘技并调 0x5B69C0 放生载具；事件8 按子类型清 8604/8605 相位；
//   事件11/普攻子类型0,6,1,2,4 播 ZGM_SPRING；子类型3 击退(400,400,-200)+火花
// ------------------------------------------------------------
// 0x5B6DC0 sub_5B6DC0 —— ZGM 事件总分发（17 弹簧双人 / 8 落地 / 14 骑乘）
// 事件 17 经 ·sub_45EBE0 解出两只 CNStarFish：A 收参数[0] 入 8636 槽、B 的 vt+736(0,1) 数值经 vt+732 同步给 A；
// 大状态 14 内事件 3/5 触发 vt+764(obj,5) 骑乘技并 ·sub_5B69C0 放生；事件 8 清 8604/8605（段 4 另经 ·sub_4E99C0/·sub_4AED60 回调）。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B6DC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int *pEvtArgs; // eax
  int nEvtP3; // ebx
  int nObjA; // eax
  int *pStarFishA; // edi
  int nObjB; // eax
  int result; // eax
  int pStarFishAVt; // esi
  int nSyncVal; // eax
  int pRideObj; // ecx
  int pVt; // edi
  int hAniKind4; // eax
  int nEvtP1; // [esp-18h] [ebp-24h]
  int nEvtP2; // [esp-14h] [ebp-20h]
  float v20; // [esp+0h] [ebp-Ch]
  int nEvtP0; // [esp+14h] [ebp+8h]
  int nEvtP4; // [esp+18h] [ebp+Ch]

  if ( ArgList == 17 )
  {
    pEvtArgs = *(int **)(LODWORD(fArg4) + 4);
    nEvtP3 = pEvtArgs[3];
    nEvtP0 = *pEvtArgs;
    nEvtP2 = pEvtArgs[2];
    nEvtP1 = pEvtArgs[1];
    nEvtP4 = pEvtArgs[4];
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
    nObjA = sub_45EBE0(nEvtP1, nEvtP2);
    pStarFishA = (int *)__RTDynamicCast(nObjA, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
    nObjB = sub_45EBE0(nEvtP3, nEvtP4);
    result = __RTDynamicCast(nObjB, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    if ( pStarFishA != nullptr && result != 0 )
    {
      pStarFishAVt = *pStarFishA;
      pStarFishA[2159] = nEvtP0;
      nSyncVal = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)result + 736))(result, 0, 1);
      return (*(int (/*thiscall*/ **)(int *, int))(pStarFishAVt + 732))(pStarFishA, nSyncVal);
    }
  }
  else
  {
    if ( pDwArg1[1639] == 14 )
    {
      if ( ArgList != 14 && (ArgList == 3 || ArgList == 5) )
      {
        pRideObj = pDwArg1[2152];
        if ( pRideObj != 0
          && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pRideObj + 772))(pRideObj, 5) != 0
          && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
        }
      }
      sub_5B69C0(pDwArg1, nArg2);
    }
    switch ( ArgList )
    {
      case 8:
        *((uint8_t *)pDwArg1 + 8604) = 0;
        *((uint8_t *)pDwArg1 + 8605) = 0;
        if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);
          sub_4E99C0(v20);
          v20 = 0.0;
          (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 676))(pDwArg1);
        }
        break;
      case 14:
        sub_5B5B90(LODWORD(fArg4));
        break;
      case 15:
        sub_5B5DC0(pDwArg1);
        break;
      default:
        break;
    }
    result = sub_4E33D0(ArgList, fArg4, nArg5, nArg6);
    if ( ArgList == 11 )
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
    if ( ArgList != 8 )
      return result;
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 0
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 6
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )
    {
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
    }
    else if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 400, 400, 0, -200, 1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      pVt = *pDwArg1;
      hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      return (*(int (/*thiscall*/ **)(int *, int))(pVt + 896))(pDwArg1, hAniKind4);
    }
    else
    {
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
      if ( result == 4 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);
        sub_4AED60(v20);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
      }
    }
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5B7080 sub_5B7080 —— 销毁联动放生变体（多 8656 槽分支）
// —— 与 ·sub_5B6D70 同构（差异：pDwArg3==this+8656 时先 ·sub_5B5F90 并经 vt+472(0,0,1,1) 收尾）。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B7080@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2164] )
  {
    sub_5B5F90();
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 472))(pDwArg1, 0, 0, 1, 1);
  }
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(pDwArg3);
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B70F0 sub_5B70F0 —— 事件 16 目标解算（IRDMonster 写 8656 槽）
// 先转发 ·sub_5B6DC0 总线；事件 16 时解事件参数对经 ·sub_45EBE0 取对象，RTTI cast 为 IRDMonster
// 写入 this+8656 槽，命中时 ·sub_5B6000 起手并由 vt+472(0,0,1,1) 收尾【推断：绑定攻击目标】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B70F0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // [esp-18h] [ebp-24h]
  int v11; // [esp-14h] [ebp-20h]

  result = sub_5B6DC0(this, ArgList, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 16 )
  {
    v7 = *(int **)(LODWORD(fArg3) + 4);
    v11 = v7[1];
    v10 = *v7;
    (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
    v8 = sub_45EBE0(v10, v11);
    v9 = __RTDynamicCast(v8, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
    *(this + 2164) = v9;
    if ( v9 != 0 )
      sub_5B6000(this);
    return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7170 sub_5B7170 —— ZGM 行为字节拍（接低血召唤门）
// —— 与 ·sub_5B41C0 同构（差异：行为字 4 无目标时改写 13、无血线架招尾段，统一转 ·sub_5B6C00 召唤门）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B7170(uint32_t *this)
{
  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 4:
      if ( *(this + 1813) != 0 )
        goto LABEL_6;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      sub_5B6C00(this);
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      goto LABEL_6;
    default:
LABEL_6:
      sub_5B6C00(this);
      break;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B71F0 sub_5B71F0 —— 同源确认+销毁联动（双段串联）
// —— 前段与 ·sub_5B6CF0 同构（标记 529 + vt+376 同族确认转 ·sub_5B46A0）；
// 后段与 ·sub_5B6D70 同构（载具 8608 放生），尾调 ·sub_4D9170(nArg3)。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B71F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3)
{
  int v4; // ebx
  bool v5; // zf
  int nArg22; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 724))(pDwArg1) == 0 )
  {
    nArg22 = nArg2;
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 376))(nArg3);
    v5 = v4 == (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);
    nArg2 = nArg22;
    if ( v5 )
      sub_5B46A0(nArg3);
  }
  if ( nArg3 == pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( (int *)nArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(nArg3);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7280 sub_5B7280 —— ZGM 落地事件变体（帧写 + 3/5/8 事件）
// 大状态 8 时先把 this+6216 资源块的 +16 句柄经 vt+208 写帧；转发 ·sub_5B6DC0 后按事件：
// 5=非困难(1943 槽!=3) 收招 vt+196(0) + ·sub_5B4A50(3,2)、3=8656 槽非空且 1908 槽==2 时 1%、==0 时 5% 概率 ·sub_5B4A50(1,1) 并递减、
// 8=段 5 时先 ·sub_4926A0 复位 6216+16 句柄再 vt+204(this,100,…) 写段。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B7280@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int result; // eax
  int nRand; // eax
  int v9; // et2

  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 16));
  result = sub_5B6DC0(pDwArg1, nArg2, ArgList, fArg4, nArg5, nArg6);
  switch ( ArgList )
  {
    case 5:
      if ( pDwArg1[1943] != 3 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, 0);
        return sub_5B4A50(3, 2, -1, -1);
      }
      break;
    case 3:
      result = pDwArg1[2164];
      if ( result > 0 )
      {
        if ( pDwArg1[1908] == 2 && rand() % 100 < 1
          || (result = pDwArg1[1908]) == 0 && (nRand = rand(), v9 = nRand % 100, result = nRand / 100, v9 < 5) )
        {
          sub_5B4A50(1, 1, -1, -1);
          result = pDwArg1[2164] - 1;
          pDwArg1[2164] = result;
        }
      }
      break;
    case 8:
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
      if ( result == 5 )
      {
        sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
                 pDwArg1,
                 100,
                 *(uint32_t *)(pDwArg1[1554] + 16),
                 0,
                 0,
                 0,
                 0);
      }
      break;
    default:
      break;
  }
  return result;
}



// 子类扩展字段复位（this+8604..8660, 20L）
// ------------------------------------------------------------
// 0x5B73B0 sub_5B73B0 —— ZGM 扩展复位（8604..8660）
// —— 与 ·sub_5B4700 同族（差异：清 8604/8605/8606/8607 四标记，8640/8656/8660 写 -1 哨兵，供事件 16/17 配对槽就绪）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B73B0(int this)
{
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint8_t *)(this + 8606) = 0;
  *(uint8_t *)(this + 8607) = 0;
  *(uint32_t *)(this + 8640) = -1;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = -1;
  *(uint32_t *)(this + 8660) = -1;
  return 0;
}



// 【vmt200 命中处理器覆写】（39L；虚表 0x6E7334..0x6EA274 九张 +512 槽共享 —— ZGM/炮车族通用受击处理）
// ------------------------------------------------------------
// 0x5B7400 sub_5B7400 —— vmt200 命中覆写：随机护盾 proc + 8668 计数到期回卷
// 基线 ·sub_4DA3B0 命中包分发；本地门且 this+7636==2 时按 this+8664 概率触发嵌入对象(this+8600)
// 的 vt+0(this+8600, this, this+7256)；this+8668 计数递减至 0 时把动画块 +466 帧推进 -100000 回卷
// 并清 this+8621/8622【推断：护盾/受击段到期复位】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7400(void *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int pThis_877; // eax
  int v7; // eax
  unsigned int pThis_2A0; // edi
  int v9; // eax
  int v10; // edx
  int v12; // [esp+18h] [ebp+10h]

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  v12 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0
    && *((uint32_t *)this + 1909) == 2
    && rand() % 100 < *((uint32_t *)this + 2166) )
  {
    (**((void (/*thiscall*/ ***)(int, void *, uint32_t))this + 2150))((int)this + 8600, this, *((uint32_t *)this + 1814));
  }
  pThis_877 = *((uint32_t *)this + 2167);
  if ( pThis_877 <= 0 )
    return v5;
  v7 = pThis_877 - 1;
  *((uint32_t *)this + 2167) = v7;
  if ( v7 > 0 )
    return v5;
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;
  v9 = sub_41A5E0(pThis_2A0);
  sub_41A590(pThis_2A0, v10, v9 - 100000);
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  *((uint8_t *)this + 8621) = 0;
  *((uint8_t *)this + 8622) = 0;
  return v12;
}



// AI 字段访问（this+8621/8622）
// ------------------------------------------------------------
// 0x5B74D0 sub_5B74D0 —— 事件包处理+嵌入对象联动
// ·sub_4DC630 取事件包；结果 14 时调嵌入对象(this+8600) 的 vt+4(this+8600, this)【推断：事件 14 触达该子对象】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B74D0(uint32_t *this)
{
  int result; // eax
  int v3; // edi

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*(this + 2150) + 4))(this + 2150, this);
    return v3;
  }
  return result;
}



// 盾闪：SHIELD_FLASH 播报（55L）
// ------------------------------------------------------------
// 0x5B7500 sub_5B7500 —— 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
// 动画控制块 +466 整数按 pszArg2 非 0 加 100、为 0 减 100（+102/+158 两浮点同步 ±9.0）后 vt+676 写帧；
// 开侧额外 vt+212 播报 SHIELD_FLASH【推断：盾牌开/收的表现与语音】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7500(void *this, char pszArg2)
{
  unsigned int pThis_2A0; // edi
  int v4; // eax
  int v5; // edx
  unsigned int pThis_2A02; // edi
  int v7; // edx
  unsigned int pThis_2A03; // edi
  int v9; // edx
  unsigned int pThis_2A04; // edi
  int v12; // edx
  unsigned int pThis_2A05; // edi
  int v14; // edx
  int v15; // [esp+10h] [ebp+8h]
  int v16; // [esp+10h] [ebp+8h]
  int v17; // [esp+10h] [ebp+8h]
  int v18; // [esp+10h] [ebp+8h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;
  v4 = sub_41A5E0(pThis_2A0);
  if ( pszArg2 != 0 )
  {
    sub_41A590(pThis_2A0, v5, v4 + 100);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 9.0;
    sub_41A590(pThis_2A02, v7, v15);
    pThis_2A03 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) + 9.0;
    sub_41A590(pThis_2A03, v9, v16);
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "SHIELD_FLASH",
             -1,
             0,
             0);
  }
  else
  {
    sub_41A590(pThis_2A0, v5, v4 - 100);
    pThis_2A04 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v17 = COERCE_FLOAT(sub_41A5E0(pThis_2A04)) - 9.0;
    sub_41A590(pThis_2A04, v12, v17);
    pThis_2A05 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v18 = COERCE_FLOAT(sub_41A5E0(pThis_2A05)) - 9.0;
    sub_41A590(pThis_2A05, v14, v18);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B7660 sub_5B7660 —— 信徒(CNZealot)绑定确认回落
// 事件参数对 (this+8656, this+8660) 经 vt+80+·sub_45EBE0 解对象并 RTTI cast 为 CNZealot；命中且其 vt+724==0 时
// 写其 8668=5、+466 帧 +100000 回卷、清 8621/8622、·sub_698F90 停其 8608 钟；末两槽归 -1【推断：配对槽消费完毕】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7660(uint32_t *this)
{
  int v2; // eax
  int pObj; // esi
  int v4; // edx
  unsigned int v5; // ebx
  int v6; // eax
  int v7; // edx
  int fld_e2164; // [esp-18h] [ebp-20h]
  int fld_e2165; // [esp-14h] [ebp-1Ch]

  fld_e2165 = *(this + 2165);
  fld_e2164 = *(this + 2164);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
  v2 = sub_45EBE0(fld_e2164, fld_e2165);
  pObj = __RTDynamicCast(v2, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )
  {
    v4 = *(uint32_t *)pObj;
    *(uint32_t *)(pObj + 8668) = 5;
    v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(v4 + 672))(pObj, 0) + 466;
    v6 = sub_41A5E0(v5);
    sub_41A590(v5, v7, v6 + 100000);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 676))(pObj, 0);
    *(uint8_t *)(pObj + 8621) = 0;
    *(uint8_t *)(pObj + 8622) = 0;
    sub_698F90(pObj + 8608, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  *(this + 2164) = -1;
  *(this + 2165) = -1;
  return -1;
}



// 主状态门（this+200/8604）
// ------------------------------------------------------------
// 0x5B7720 sub_5B7720 —— 大状态三段门（8 攻击 / 15 施放 / 14 架招）
// 基线 ·sub_4E1780；8 且子类段 7028∈{1,2}：vt+200 对象 +148==1 且 8604 未置时经本地门调 vt+1316 并置 8604=1；
// 15 且 +170（播完标记）非 0 时 vt+472(0,0,1,1) 收尾；14 时调 vt+1312（收手触发）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B7720(int this)
{
  int pThis_C8; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && (sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2) )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(uint32_t *)(pThis_C8 + 148) == 1 )
    {
      LOBYTE(pThis_C8) = *(uint8_t *)(this + 8604);
      if ( (uint8_t)pThis_C8 == 0 )
      {
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)pThis_C8 != 0 )
          LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);
        *(uint8_t *)(this + 8604) = 1;
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 15
         && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);
  }
  else
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_C8 == 14 )
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);
  }
  return pThis_C8;
}



// 时钟门 AI（sub_699000, 58L）
// ------------------------------------------------------------
// 0x5B77F0 sub_5B77F0 —— 行为字节拍（高概率化变体）
// —— 与 ·sub_5B41C0 同构（差异：4→有目标 10% 写 5、5→有目标 1% 写 4、无目标写 13；25 型以 this+7640 时间戳差 >5000ms 写 13；无血线架招尾段）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B77F0(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_12;
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) == 0 )
        goto LABEL_12;
      nRand2 = rand();
      v4 = nRand2 % 100;
      result = nRand2 / 100;
      if ( v4 < 1 )
        goto LABEL_4;
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    case 25:
      result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 5000 )
LABEL_12:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    default:
      return result;
  }
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5B7900 sub_5B7900 —— 等待窗门（25 态 5000ms 内不推进）
// 行为字非 25 直接 ·sub_4D9040(nArg2)；为 25 时取 this+7640 时间戳差，满 5000ms 才放行 ·sub_4D9040，
// 否则原样返回差值【推断：特殊态施法前摇/冷却窗】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7900(uint32_t *this, int nArg2)
{
  int result; // eax

  if ( *(this + 1787) != 25 )
    return sub_4D9040(nArg2);
  result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
  if ( result >= 5000 )
    return sub_4D9040(nArg2);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7940 sub_5B7940 —— 目标落点继承（vt+1144 + 帧标记清 0）
// 取 nArg2 坐标链 vt+124→vt+120 后经 vt+1144 写入自身目标位置；再把 vt+1040 返回结构的 +8 字节清 0
// 【推断：吸附/跟随目标点并复位帧控制标记】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7940(int *this, int nArg2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int result; // eax

  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v4);
  (*(void (/*thiscall*/ **)(int *, int))(v3 + 1144))(this, v5);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 1040))(this);
  *(uint8_t *)(result + 8) = 0;
  return result;
}



// 投刀技能：Particle/Dagger.ptl + THROW_STONE 播报（33L）
// ------------------------------------------------------------
// 0x5B7980 sub_5B7980 —— 投刀发射（Dagger.ptl 弹道 + THROW_STONE 播报）
// 命中包探针取值 this+7028（动作槽 / 攻击段号）：·sub_41A5E0==1 时档位 50，否则 20。
// 经 vt+588 装载 Particle/Dagger.ptl（参数 40/档位/4 段），由 vt+580 以 this+8672 资源 ID
// 发射弹道，末尾 vt+212 播报 THROW_STONE。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7980(uint32_t *this)
{
  int pThis_6DD; // eax
  int v3; // edi
  int v4; // eax

  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/Dagger.ptl",
         0,
         40,
         0,
         pThis_6DD != 1 ? 20 : 50,
         4,
         0,
         0,
         0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v3 + 580))(this, *(this + 2168), 0, v4);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "THROW_STONE",
           -1,
           0,
           0);
}



// AI 相位辅助（67L）
// ------------------------------------------------------------
// 0x5B79F0 sub_5B79F0 —— 投掷物随机散射（2-3 发，资源 ID 250/252）
// 门=vt+308 有目标；发数 rand%2+2（2-3 发），每发经 vt+152(1,三随机量,8,0xFFFF) 生成参数面：
// 三随机量 100-299 / 50-149 / 40-99，坐标 vt+124/120 各 ±10 抖动【推断：散布角与初速】；
// vt+376 定位后 vt+592 发射，资源 ID 从 250 与 252 中随机，vt+672(3) 取表现槽。
// ------------------------------------------------------------
int /*usercall*/ sub_5B79F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int nRand; // edi
  int nRand4; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int nRand5; // eax
  int v12; // ebx
  int nRand6; // eax
  uint32_t v16[2]; // [esp+4h] [ebp-18h]
  uint16_t v17[3]; // [esp+Ch] [ebp-10h] BYREF
  bool nRand2; // [esp+12h] [ebp-Ah]
  char nRand3; // [esp+13h] [ebp-9h]
  uint32_t *v20; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand() % 2 + 2;
    result = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 672))(pDwArg1, 3);
    v16[0] = 250;
    v16[1] = 252;
    if ( nRand > 0 )
    {
      for ( i = nRand; i != 0; --i )
      {
        v17[0] = rand() % 200 + 100;
        v17[1] = rand() % 100 + 50;
        nRand2 = rand() % 2 == 0;
        nRand3 = 3 - (rand() % 2 != 0);
        nRand4 = rand();
        v7 = *pDwArg1;
        v17[2] = nRand4 % 60 + 40;
        v20 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int, int))(v7 + 672))(pDwArg1, 3, nArg2, nArg3);
        v8 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 152))(
               pDwArg1,
               1,
               v17,
               8,
               0xFFFF,
               0,
               0,
               0,
               0);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 128))(pDwArg1, v8);
        v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v9 + 20);
        nRand5 = rand();
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10 + nRand5 % 20 - 10);
        nRand6 = rand();
        nArg3 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 376))(pDwArg1, *v20, v12 + nRand6 % 40 - 20);
        nArg2 = v16[rand() % 2];
        result = (*(int (/*thiscall*/ **)(int *))(v7 + 592))(pDwArg1);
      }
    }
  }
  return result;
}



// AI 相位门（this+8607/8668）
// ------------------------------------------------------------
// 0x5B7CC0 sub_5B7CC0 —— 架招自启（5/300 概率 setState 14）
// 先跑 ·sub_5B77F0 行为字节拍；门链=vt+308 目标、vt+840 大状态 0、this+8607 非指挥态、
// this+8668 冷却≤0、this+7632 空槽；rand%300<5 时经 vt+560 进 14/蓄力架招。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7CC0(int this)
{
  int result; // eax
  int nRand; // eax
  int v3; // et2

  sub_5B77F0((int *)this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( result == 0 )
    {
      result = *(uint8_t *)(this + 8607);
      if ( (uint8_t)result == 0 )
      {
        result = *(uint32_t *)(this + 8668);
        if ( result <= 0 )
        {
          result = *(uint32_t *)(this + 7632);
          if ( result == 0 )
          {
            nRand = rand();
            v3 = nRand % 300;
            result = nRand / 300;
            if ( v3 < 5 )
              return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                       this,
                       14,
                       0,
                       0,
                       0);
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7CD0 sub_5B7CD0 —— 分身参数面清空（形态槽置 7584=1）
// 清 this+7531..7596 分身/攻击参数面（7531-7534 字节旗标 + 7535-7596 整数块），
// 末把形态槽 this+7584 置 1（7534/7564/7588 保持 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7CD0(int this, int nArg2, int nArg3)
{
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7584) = 1;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7D60 sub_5B7D60 —— 分身参数面清空（形态槽置 7588=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7588=1；nArg3==2 且 nArg2==0 时
// 偏移槽 this+7596=-50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7D60(int this, int nArg2, int nArg3)
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7588) = 1;
  if ( nArg3 == 2 && nArg2 == 0 )
    *(uint32_t *)(this + 7596) = -50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7E00 sub_5B7E00 —— 分身参数面清空（形态槽置 7564=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7564=1；nArg3==2 时取 nArg2，
// 归一为 0 则偏移槽 this+7596=+50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7E00(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7564) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7EB0 sub_5B7EB0 —— 分身出厂（this+8664=30 / this+8640=vt+384 出场参数）
// 仅自身消息(pDwArg2==this)有效：写 this+8664=30（存续/延迟帧）、经 vt+384(0) 取出场参数面
// 存 this+8640。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7EB0(int *this, int *pDwArg2)
{
  int result; // eax
  int v4; // eax

  result = (int)pDwArg2;
  if ( pDwArg2 == this )
  {
    v4 = *this;
    *(this + 2166) = 30;
    result = (*(int (/*stdcall*/ **)(uint32_t))(v4 + 384))(0);
    *(this + 2160) = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7EE0 sub_5B7EE0 —— 伤害计数射弹（5% 概率发 30073）后尾调反击判定
// 门=vt+840 大状态 8 且 this+7028 空槽 且 vt+40(nArg2,17) 存活 且 vt+308 有目标，
// 5% 概率经 nArg2 的 vt+124/120 组合出射弹载荷 30073（3 段/4 朝向/100 距离），vt+584 写入；
// 末尾无条件交 ·sub_4DB480 反击/架招触发判定（尾调 sub_4D6D90 分型）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7EE0(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && rand() % 100 < 5 )
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(
           nArg2,
           30073,
           3,
           0,
           4,
           100,
           1,
           0,
           0);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);
    v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, v7);
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v8);
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7F90 sub_5B7F90 —— 分身参数面清空（形态槽置 7534=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7534=1；nArg3==2 时取 nArg2，
// 归一为 0 则偏移槽 this+7596=+50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7F90(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint8_t *)(this + 7534) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8040 sub_5B8040 —— 冰盾光环挂载（Block==null 时 new ChillingAura）
// 先跑 ·sub_5B7D60 清参数面；Block 为空时经 vt+700 取资源族、·sub_53F6A0 清挂点，
// new 0x8C 后由 ·sub_64B0F0 载 Monster/Soceress/Animation_Keraha/ChillingAura（动画模板 %s.ani），
// vt+56 挂到(自身,自身)并播 SHIELD_ICE；vt+216 写入音效槽 163 后播 WINDSHIELD_LOOP。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8040(void *this, int nArg2, void *Block)
{
  int result; // eax
  int pObj; // eax

  result = sub_5B7D60((int)this, nArg2, (int)Block);
  if ( Block == nullptr )
  {
    (*(void (**)(void))(*(uint32_t *)this + 700))();
    sub_53F6A0(this);
    if ( operator new(0x8Cu) != nullptr )
      pObj = sub_64B0F0(0, 0x40000000, 7, "Monster/Soceress/Animation_Keraha/ChillingAura");
    else
      pObj = 0;
    (*(void (/*thiscall*/ **)(int, void *, void *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
      pObj,
      this,
      this,
      1,
      0,
      0,
      -1);
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "SHIELD_ICE",
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "WINDSHIELD_LOOP",
             163,
             0,
             0);
  }
  return result;
}



// ============================================================
// 【分区 5】信徒（Believer）（0x5B8120-0x5B9F60）
// 证据：BELIEVER_COMMAND/ATK/PRAY/DMG/DIE/FIND、KNIFE_STICK/KNIFE_HIT、
//       REPAIR_OBJECT 修复、0x5B8CE0 243L 大型主状态机

// 信徒指挥：BELIEVER_COMMAND（97L；this+208/8607/8621/8622 相位）
// ------------------------------------------------------------
// 0x5B8120 sub_5B8120 —— 冰盾变体收尾（自身消息时写音效槽 163）
// 先调 ·sub_4D9170 基础收尾；pArg2==this 时经 vt+216 写音效槽 163（与 ·sub_5B8040 尾部一致）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8120(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);
  return result;
}



// 冰盾技能（Soceress 复用）：sub_64B0F0 发射 Monster/Soceress/Animation_Keraha/
//   ChillingAura 光环 + SHIELD_ICE + WINDSHIELD_LOOP（44L）
// ------------------------------------------------------------
// 0x5B8150 sub_5B8150 —— 投刀三连散射（Dagger.ptl 三角度 0/45/320）
// 探针 this+7028：·sub_41A5E0==1 时档位 50 否则 20；vt+588 取 Particle/Dagger.ptl 参数面副本，
// rand%100<30 时连发 3 枚（角度槽 [18]=0/45/320），每枚经 vt+580 以 this+8672 发射；
// 末尾 vt+212 播报 THROW_STONE。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8150(uint32_t *this)
{
  int v2; // eax
  int i; // esi
  int v4; // eax
  int fld_e2168; // ecx
  uint32_t v7[3]; // [esp+Ch] [ebp-7Ch]
  int pThis_6DD; // [esp+18h] [ebp-70h]
  bool nRand; // [esp+1Fh] [ebp-69h]
  uint32_t v10[26]; // [esp+20h] [ebp-68h] BYREF

  v10[25] = dword_796E50;
  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) != 1 ? 20 : 50;
  v2 = *this;
  v7[0] = 0;
  v7[1] = 45;
  v7[2] = 320;
  qmemcpy(
    v10,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v2 + 588))(this, "Particle/Dagger.ptl"),
    0x62u);
  nRand = rand() % 100 < 30;
  for ( i = 0; i < 3; ++i )
  {
    v4 = *this;
    fld_e2168 = *(this + 2168);
    v10[18] = v7[i];
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
      this,
      fld_e2168,
      0,
      v10,
      0,
      40,
      0,
      pThis_6DD,
      4,
      0,
      0,
      0);
    if ( !nRand )
      break;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "THROW_STONE",
           -1,
           0,
           0);
}



// 【vmt200 命中处理器覆写】（44L；虚表 0x6E97F4 +512 槽 —— 信徒族受击处理）
// ------------------------------------------------------------
// 0x5B8240 sub_5B8240 —— vmt200 命中覆写：护盾 proc 弹（10% 发 603）后交 ·sub_5B7400
// 门=vt+308 有目标、this+1908==0、计数 this+8636<6、rand%100<10；命中时以 vt+672(0) 取
// 挂点、vt+152(2,&v13=4) 造参数面（1 段/4 朝向）经 vt+120/124/376 定位，vt+592 发 603
// 并 ++this+8636；末尾无条件交 ·sub_5B7400 护盾 proc 覆写。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8240(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int v6; // edx
  uint32_t *v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  char v13; // [esp+7h] [ebp-1h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1908) == 0
    && (int)*(this + 2159) < 6
    && rand() % 100 < 10 )
  {
    v5 = *this;
    v6 = *this;
    v13 = 4;
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 152))(
           this,
           2,
           &v13,
           1,
           0xFFFF,
           0,
           0,
           0,
           0);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 124))(this, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v9);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 376))(this, *v7, v10);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 592))(this, 603, v11);
    ++*(this + 2159);
  }
  return sub_5B7400(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8310 sub_5B8310 —— 伤害计数射弹（30% 概率发 30074）后尾调反击判定
// 与 ·sub_5B7EE0 同构（差异：概率 30%；载荷 30074、10 段/4 朝向/100 距离）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8310(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && rand() % 100 < 30 )
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(
           nArg2,
           30074,
           10,
           0,
           4,
           100,
           1,
           0,
           0);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);
    v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, v7);
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v8);
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B83C0 sub_5B83C0 —— 速率双轴衰减（控制柄 +830/+858 各 -0.5）后 vt+676 提交
// 仅 nArg3==0 生效：vt+672(0) 取控制柄，经 ·sub_41A5E0 读浮点、·sub_41A590 写回，
// 对 +830 与 +858 两槽各减 0.5【推断：移动/攻速衰减】，vt+676(0) 提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B83C0(void *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v6; // edx
  unsigned int pThis_2A02; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]
  int v10; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.5;
    sub_41A590(pThis_2A0, v6, v9);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) - 0.5;
    sub_41A590(pThis_2A02, v8, v10);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8450 sub_5B8450 —— 修复效果请求（目标坐标 + 42004 效果包）
// 条件=this[1] 存在且 vt+308 有目标；用 vt+120/124/128（+vt+192/2 半宽）合成命中点三浮点，
// ·sub_605840 取命中包，目标 vt+152 取伤害/表现槽，由 ·sub_4E4A50(this[9], 42004, this[20],…,
// 命中点, 命中包) 发出效果请求，末 this[18]=this[21] 镜像。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B8450(uint32_t *this)
{
  int fld_e1; // ecx
  int fld_e12; // ecx
  int nTgtX; // eax
  int fld_e13; // ecx
  int nTgtY; // eax
  int fld_e14; // edi
  int nHalfW; // ebx
  int nTgtZmid; // ebx
  int fld_e15; // eax
  int fld_e16; // eax
  int nHitA; // [esp-10h] [ebp-34h]
  int nHitB; // [esp-Ch] [ebp-30h]
  float fTgtX; // [esp+4h] [ebp-20h] BYREF
  float fTgtY; // [esp+8h] [ebp-1Ch]
  float fTgtZ; // [esp+Ch] [ebp-18h]
  int v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int v19; // [esp+18h] [ebp-Ch]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+20h] [ebp-4h] BYREF

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 308))(fld_e1) != 0 )
  {
    fld_e12 = *(this + 1);
    fTgtX = 0.0;
    fTgtY = 0.0;
    fTgtZ = 0.0;
    v17 = 0;
    v18 = 0;
    v19 = 0;
    nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 120))(fld_e12);
    fld_e13 = *(this + 1);
    v20 = nTgtX;
    fTgtX = (float)nTgtX;
    nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 124))(fld_e13);
    fld_e14 = *(this + 1);
    v20 = nTgtY;
    fTgtY = (float)nTgtY;
    nHalfW = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e14 + 192))(fld_e14) / 2;
    nTgtZmid = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e14 + 128))(fld_e14) + nHalfW;
    fld_e15 = *(this + 1);
    v20 = nTgtZmid;
    fTgtZ = (float)nTgtZmid;
    v21 = 0;
    nHitB = sub_605840(&v21, fld_e15, &fTgtX, 0);
    nHitA = v21;
    fld_e16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 152))(*(this + 1));
    sub_4E4A50(*(this + 9), 42004, *(this + 20), 0, 0, 0, fld_e16, 0, nHitA, nHitB);
    *(this + 18) = *(this + 21);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8550 sub_5B8550 —— 大状态退出副作用（nArg2==25 时 this+8292=1000 并置位）
// 先调 ·sub_4DBC20（大状态退出副作用处理器，0x4DBA80 的还原对偶）；
// nArg2==25 时写 this+8292=1000（时长/桩数）并经 vt+1040 取桩位后 [8]=1 置位。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8550(int *this, int nArg2)
{
  int result; // eax
  int v4; // eax

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 25 )
  {
    v4 = *this;
    *(this + 2073) = 1000;
    result = (*(int (/*thiscall*/ **)(int *))(v4 + 1040))(this);
    *(uint8_t *)(result + 8) = 1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8590 sub_5B8590 —— 散射门（vt+308 且有目标且 this+8605==1 时才散射）
// 读 vt+308 有目标与 this+8605 相位字节，二者齐备时转 ·sub_5B79F0 执行 2-3 发散射投掷。
// ------------------------------------------------------------
int /*usercall*/ sub_5B8590@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 && *(uint8_t *)(pArg1 + 8605) == 1 )
    return sub_5B79F0((int *)pArg1, nArg2, nArg3);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B85C0 sub_5B85C0 —— CNAppendageTimerFireDamage 构造（延烧附着物）
// 基类 ·sub_4B1030 后写 vftable，this+20=nArg4(伤害)、+21=+18=nArg3(间隔)、+11=nArg2(存续 ms)、
// +22=0（宿主/触发器槽），·sub_5F66A0(1) 登记。调用点(0x5B9280)传 10000/999/20。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B85C0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e21; // edx

  sub_4B1030();
  *(this + 20) = nArg4;
  *this = &CNAppendageTimerFireDamage::`vftable';
  *(this + 21) = nArg3;
  sub_5F66A0(1);
  fld_e21 = *(this + 21);
  *(this + 11) = nArg2;
  *(this + 18) = fld_e21;
  *(this + 22) = 0;
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8630 sub_5B8630 —— CNAppendageTimerFireDamage 析构（驱散宿主 + 基类回落）
// this+22 宿主槽非空时经其 vtable[0](宿主,1) 释放并清零；vftable 依次回落 IRDAppendage、
// IObject，·sub_5F6640 反登记，this 字节 12 清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8630(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e22)(uint32_t, int); // ecx
  int result; // eax

  *this = &CNAppendageTimerFireDamage::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 22) = 0;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B86A0 sub_5B86A0 —— 删除式析构包装（pszArg2 bit0 置位则 free 本体）
// 转 ·sub_5B8630 析构后按 pszArg2&1 决定 j__free，标准编译器生成形态。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B86A0(uint32_t *Block, char pszArg2)
{
  sub_5B8630(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助（this+204/+208 硬直）
// ------------------------------------------------------------
// 0x5B86D0 sub_5B86D0 —— 三帧位偏移挂装/还原（-100/100/200）
// 资源表指针 this+1554 取 +16/+20/+24 三项：pszArg2 非 0 时先 ·sub_4926A0 帧游标复位，
// 再经 vt+204 以 -100/100/200 三偏移写入（多帧错位表现）；置 0 时经 vt+208 按原锚还原三帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B86D0(uint32_t *this, char pszArg2)
{
  int fld_e1554; // eax

  fld_e1554 = *(this + 1554);
  if ( pszArg2 != 0 )
  {
    sub_4926A0(*(uint32_t *)(fld_e1554 + 16));
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 24));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      -100,
      *(uint32_t *)(*(this + 1554) + 16),
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 20),
      0,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             200,
             *(uint32_t *)(*(this + 1554) + 24),
             0,
             0,
             0,
             0);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(fld_e1554 + 16));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  }
}



// 信徒·寻车解算（73L）：扫场景挂载列表中带标记 529 的对象，RTTI cast 为 CNVehicle，
//   取 vt+376 房间/队伍号【推断】与自身一致、视线可达(vt+1244)者，按 vt+736 距离
//   最近【推断】选出一辆存入 this[1812]（信徒登车/攻击目标）
// ------------------------------------------------------------
// 0x5B87C0 sub_5B87C0 —— 信徒·寻车解算（场景标记 529 + CNVehicle cast）
// 除头部说明外：标签判定用 vt+40(obj,529)、视线可达 vt+1244、距离 vt+736，房间号 vt+376；
// 结果写 this[1812]（32 位槽）供登车/修复目标复用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B87C0(uint32_t *this)
{
  uint32_t *pThis; // ebx
  int result; // eax
  unsigned int nIdx; // edi
  int pVecHdr; // ecx
  int pVecBegin; // edx
  int nCnt; // eax
  int pVecBegin3; // edx
  int pListObj; // ecx
  int pVecHdr2; // ecx
  int pVecBegin2; // edx
  int pListObj2; // eax
  int pVehicle; // eax
  int pVehicle2; // esi
  int nRoomId; // [esp+4h] [ebp-Ch]
  int nDistNew; // [esp+4h] [ebp-Ch]
  int pBestVehicle; // [esp+8h] [ebp-8h]

  pThis = this;
  result = (*(int (/*fastcall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    nIdx = 0;
    pBestVehicle = 0;
    while ( 1 )
    {
      pVecHdr = pThis[29];
      pVecBegin = *(uint32_t *)(pVecHdr + 8);
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(pVecHdr + 12) - pVecBegin) >> 2 : 0;
      if ( (int)nIdx >= nCnt )
        break;
      pVecBegin3 = *(uint32_t *)(pVecHdr + 8);
      if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pVecHdr + 12) - pVecBegin3) >> 2 )
        pListObj = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
      else
        pListObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 529) != 0 )
      {
        pVecHdr2 = pThis[29];
        pVecBegin2 = *(uint32_t *)(pVecHdr2 + 8);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pVecHdr2 + 12) - pVecBegin2) >> 2 )
          pListObj2 = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else
          pListObj2 = 0;
        pVehicle = __RTDynamicCast(pListObj2, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);
        pVehicle2 = pVehicle;
        if ( pVehicle != 0 )
        {
          nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 376))(pVehicle);
          if ( nRoomId == (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis)
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pVehicle2) != 0
            && (pBestVehicle == 0
             || (nDistNew = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle2 + 736))(pVehicle2)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pBestVehicle + 736))(pBestVehicle)) )
          {
            pBestVehicle = pVehicle2;
          }
          pThis = this;
        }
      }
      ++nIdx;
    }
    pThis[1812] = pBestVehicle;
    return pBestVehicle;
  }
  return result;
}



// 信徒指挥 AI：BELIEVER_COMMAND（97L）：pszArg2=1 进入指挥态——7559 置位、
//   this[1899]=100、控制柄四点调参（+74 移速 +0.3、+830 播速 +0.3、+102/+158 各 -0.3
//   【推断：攻速/前摇补偿】）、清 8621/8622 技能相位、停 2152 时钟并播 BELIEVER_COMMAND；
//   pszArg2=0 退出——四点反向还原并按资源表 +16/+20/+24 复位动画
// ------------------------------------------------------------
// 0x5B88E0 sub_5B88E0 —— 信徒指挥态进退（BELIEVER_COMMAND 起手/收尾）
// 补充：控制柄四点经 ·sub_41A5E0 读浮点 + ·sub_41A590 写回后 vt+676(0) 提交；
// 进态侧还清 this+8621/8622 技能相位、·sub_698F90 停 this[2152] 时钟、·sub_5B86D0(this,1)
// 挂三帧；退态侧经 vt+208 按资源表 +16/+20/+24 还原。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B88E0(int *this, char pszArg2)
{
  char result; // al
  int pVt; // eax
  unsigned int pCtrl74; // edi
  int v6; // edx
  unsigned int pCtrl830; // edi
  int v8; // edx
  unsigned int pCtrl102; // edi
  int v10; // edx
  unsigned int pCtrl158; // edi
  int v12; // edx
  int pVt2; // edx
  unsigned int pCtrl74b; // edi
  int v15; // edx
  unsigned int pCtrl830b; // edi
  int v17; // edx
  unsigned int pCtrl102b; // edi
  int v19; // edx
  unsigned int pCtrl158b; // edi
  int v21; // edx
  int fVal74; // [esp+14h] [ebp+8h]
  int fVal830; // [esp+14h] [ebp+8h]
  int fVal102; // [esp+14h] [ebp+8h]
  int fVal158; // [esp+14h] [ebp+8h]
  int fVal74b; // [esp+14h] [ebp+8h]
  int fVal830b; // [esp+14h] [ebp+8h]
  int fVal102b; // [esp+14h] [ebp+8h]
  int fVal158b; // [esp+14h] [ebp+8h]

  result = pszArg2;
  if ( pszArg2 == 1 )
  {
    if ( *((uint8_t *)this + 8607) == 0 )
    {
      pVt = *this;
      *((uint8_t *)this + 7559) = 1;
      *(this + 1899) = 100;
      pCtrl74 = (*(int (/*stdcall*/ **)(uint32_t))(pVt + 672))(0) + 74;
      *(float *)&fVal74 = COERCE_FLOAT(sub_41A5E0(pCtrl74)) + 0.30000001;
      sub_41A590(pCtrl74, v6, fVal74);
      pCtrl830 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;
      *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pCtrl830)) + 0.30000001;
      sub_41A590(pCtrl830, v8, fVal830);
      pCtrl102 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;
      *(float *)&fVal102 = COERCE_FLOAT(sub_41A5E0(pCtrl102)) - 0.30000001;
      sub_41A590(pCtrl102, v10, fVal102);
      pCtrl158 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;
      *(float *)&fVal158 = COERCE_FLOAT(sub_41A5E0(pCtrl158)) - 0.30000001;
      sub_41A590(pCtrl158, v12, fVal158);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
      *((uint8_t *)this + 8607) = 1;
      *((uint8_t *)this + 8621) = 0;
      *((uint8_t *)this + 8622) = 0;
      sub_698F90((int)(this + 2152), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_5B86D0(this, 1);
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "BELIEVER_COMMAND",
               -1,
               0,
               0);
    }
  }
  else if ( pszArg2 == 0 && *((uint8_t *)this + 8607) == 1 )
  {
    pVt2 = *this;
    *((uint8_t *)this + 7559) = 0;
    *(this + 1899) = 0;
    pCtrl74b = (*(int (/*thiscall*/ **)(int *, uint32_t))(pVt2 + 672))(this, 0) + 74;
    *(float *)&fVal74b = COERCE_FLOAT(sub_41A5E0(pCtrl74b)) - 0.30000001;
    sub_41A590(pCtrl74b, v15, fVal74b);
    pCtrl830b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&fVal830b = COERCE_FLOAT(sub_41A5E0(pCtrl830b)) - 0.30000001;
    sub_41A590(pCtrl830b, v17, fVal830b);
    pCtrl102b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;
    *(float *)&fVal102b = COERCE_FLOAT(sub_41A5E0(pCtrl102b)) + 0.30000001;
    sub_41A590(pCtrl102b, v19, fVal102b);
    pCtrl158b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;
    *(float *)&fVal158b = COERCE_FLOAT(sub_41A5E0(pCtrl158b)) + 0.30000001;
    sub_41A590(pCtrl158b, v21, fVal158b);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    *((uint8_t *)this + 8607) = 0;
    *((uint8_t *)this + 8621) = 0;
    *((uint8_t *)this + 8622) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8B80 sub_5B8B80 —— 信徒加载槽清位（this[1905]+96 字节置 0）
// 仅 uArg3==nullptr 时有效：把 this[1905] 资源对象 +96 偏移处字节清 0（加载/待机旗标）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8B80(uint32_t *this, int nArg2, uint8_t *uArg3)
{
  uint8_t *result; // eax

  result = uArg3;
  if ( uArg3 == nullptr )
  {
    result = (uint8_t *)(*(this + 1905) + 96);
    *result = 0;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8BA0 sub_5B8BA0 —— 分身收尾（nArg3==0 时 this+7620 资源 +96 置 1）
// 先跑 ·sub_5B7D60 清参数面；nArg3==0 时把 this+7620 资源对象 +96 偏移处字节置 1。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8BA0(void *this, int nArg2, int nArg3)
{
  uint8_t *result; // eax
  int v4; // ecx

  result = (uint8_t *)sub_5B7D60((int)this, nArg2, nArg3);
  if ( nArg3 == 0 )
  {
    result = (uint8_t *)(*(uint32_t *)(v4 + 7620) + 96);
    *result = 1;
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B8BD0 sub_5B8BD0 —— 目标解算收尾（CNZealot cast 后强制进指挥态）
// 取 this[2164]/this[2165] 对象键经 ·sub_45EBE0 解算，__RTDynamicCast 为 CNZealot；
// 其 vt+724（姿态/忙碌查询）为 0 时调 ·sub_5B88E0(v3,1) 进指挥态；两键槽置 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8BD0(uint32_t *this)
{
  int v2; // eax
  int *v3; // edi
  int fld_e2164; // [esp-18h] [ebp-20h]
  int fld_e2165; // [esp-14h] [ebp-1Ch]

  fld_e2165 = *(this + 2165);
  fld_e2164 = *(this + 2164);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
  v2 = sub_45EBE0(fld_e2164, fld_e2165);
  v3 = (int *)__RTDynamicCast(v2, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
  if ( v3 != nullptr && (*(uint8_t (/*thiscall*/ **)(int *))(*v3 + 724))(v3) == 0 )
    sub_5B88E0(v3, 1);
  *(this + 2164) = -1;
  *(this + 2165) = -1;
  return -1;
}



// 信徒语音装载：BELIEVER_DMG/DIE/FIND + KNIFE_HIT 刀命中播报（sub_4015C0）
// ------------------------------------------------------------
// 0x5B8C40 sub_5B8C40 —— 信徒初始化（语音组装载 + 技能参数）
// 写 this+6792/6800/6796/6804/6808（三资源表指针与两计数），经 ·sub_4015C0 依次装
// BELIEVER_DMG(12)/BELIEVER_DIE(12)/BELIEVER_FIND(13)/KNIFE_HIT(9) 语音；末写
// this+8664=10、+8668=0、+8636=0、+8672=30014（技能/演出 ID）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8C40(uint32_t *this)
{
  *(this + 1698) = 1;
  *(this + 1700) = 1;
  *(this + 1699) = 2;
  *(this + 1701) = 2;
  *(this + 1702) = 3;
  sub_4015C0("BELIEVER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_FIND", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("KNIFE_HIT", 9u);  // 【std::string构造赋值】
  *(this + 2166) = 10;
  *(this + 2167) = 0;
  *(this + 2159) = 0;
  *(this + 2168) = 30014;
  return 0;
}



// 信徒大型主状态机（243L）：大状态10(祈祷)=按 this[2072] 子相位分派 BELIEVER_COMMAND/
//   0x5B7660，否则按 this[2160]-600 映射传送槽(600→2,601→1,602→3,603→4)经 vt+152(2,&mask)
//   过滤查找后 vt+592 传送并 ++this[2159]；事件15=REPAIR_OBJECT——用事件参数对经
//   sub_45EBE0 解算目标，按其 vt+740×0.3 生成修复文本对象并播 1554+4 动画、
//   记 this[2161]=now、++this[2162]；大状态8 清 8604 相位；事件8 播 BELIEVER_ATK、
//   事件3 且动作25 时记 5 秒冷却(this[1926]=now+5000)进动作4、事件14/10 播祈祷动画
// ------------------------------------------------------------
// 0x5B8CE0 sub_5B8CE0 —— 信徒大型主状态机（243L）补充
// 门为 this+6556（主状态镜像 2），子相位 this[2072]、传送键 this[2160]、计数 this[2159]；
// 传送走 vt+152/vt+120/vt+124/vt+376/vt+592；修复事件(15) 经 ·sub_45EBE0 解算目标后
// ·sub_4D6810 造 CNChangeHp 文本对象、vt+876 双轴归零、vt+996 收尾；祈祷事件(10) 播
// BELIEVER_PRAY 并 vt+992(+36,1) 复位三帧、·sub_5B7500 盾闪收尾。
// ------------------------------------------------------------
void /*userpurge*/ sub_5B8CE0(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int nBigState; // eax
  int nEvt; // edi
  int nPhase2072; // eax
  int nTpOffset; // eax
  int pVt; // edi
  uint32_t *pCtrl0; // ebx
  int nFindRes; // eax
  int nFindY; // eax
  int nFindX2; // eax
  int nFindX3; // eax
  int *pEvtArgs; // eax
  int pRepairTarget; // edi
  uint8_t *pTextObj; // eax
  int pTextObjVt; // edx
  int nClock1910; // eax
  int pVt2; // edx
  int nPhase2072b; // eax
  int fRepairVal; // [esp+1Ch] [ebp-30h]
  int nObjKey1; // [esp+24h] [ebp-28h]
  int nObjKey2; // [esp+28h] [ebp-24h]
  uint8_t *Block; // [esp+38h] [ebp-14h]
  char nTpSlot; // [esp+3Fh] [ebp-Dh] BYREF
  int v29; // [esp+48h] [ebp-4h]

  nBigState = pArg1[1639];
  if ( nBigState == 8 )
  {
    nEvt = ArgList;
    if ( ArgList != 8 && (sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1 || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2) )
      *((uint8_t *)pArg1 + 8604) = 0;
  }
  else
  {
    if ( nBigState == 10 )
    {
      if ( ArgList == 0 )
      {
        nPhase2072 = pArg1[2072];
        if ( nPhase2072 != 0 )
        {
          if ( nPhase2072 == 1 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
              pArg1,
              "BELIEVER_COMMAND",
              -1,
              0,
              0);
            sub_5B8BD0(pArg1);
          }
          else if ( nPhase2072 == 2 )
          {
            sub_5B7660(pArg1);
          }
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
          {
            nTpOffset = pArg1[2160] - 600;
            nTpSlot = 0;
            switch ( nTpOffset )
            {
              case 0:
                nTpSlot = 2;
                break;
              case 1:
                nTpSlot = 1;
                break;
              case 2:
                nTpSlot = 3;
                break;
              case 3:
                nTpSlot = 4;
                break;
              default:
                break;
            }
            pVt = *pArg1;
            pCtrl0 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);
            nFindRes = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(
                    pArg1,
                    2,
                    &nTpSlot,
                    1,
                    0xFFFF,
                    0,
                    0,
                    0,
                    0);
            nFindY = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 124))(pArg1, 0, nFindRes);
            nFindX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nFindY);
            nFindX3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *pCtrl0, nFindX2);
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(pVt + 592))(pArg1, pArg1[2160], nFindX3);
          }
          ++pArg1[2159];
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 24));
      sub_5B7500(0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 996))(pArg1);
    }
    nEvt = ArgList;
  }
  if ( nEvt == 15 )
  {
    pEvtArgs = *(int **)(pArg4 + 4);
    nObjKey2 = pEvtArgs[1];
    nObjKey1 = *pEvtArgs;
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);
    pRepairTarget = sub_45EBE0(nObjKey1, nObjKey2);
    if ( pRepairTarget == 0 )
      return;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "REPAIR_OBJECT", -1, 0, 0);
    Block = operator new(0x80u);
    v29 = 0;
    if ( Block != nullptr )
    {
      fArg2 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRepairTarget + 740))(pRepairTarget) * 0.30000001;
      *(float *)&fRepairVal = fArg2;
      pTextObj = sub_4D6810(Block, fRepairVal, 5000, 1, 1);
    }
    else
    {
      pTextObj = nullptr;
    }
    pTextObjVt = *(uint32_t *)pTextObj;
    v29 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(pTextObj, pRepairTarget, pArg1, 0, 0, 0, -1);
    sub_4926A0(*(uint32_t *)(pArg1[1554] + 4));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 4));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 0, 0, 0, 0, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
    nEvt = ArgList;
    pArg1[2161] = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
    ++pArg1[2162];
  }
  sub_4E33D0((int)pArg1, pArg4, fArg2, nEvt, pArg4, *(float *)&nArg5, *(float *)&nArg6);
  switch ( nEvt )
  {
    case 8:
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_ATK", -1, 0, 0);
      }
      break;
    case 3:
      if ( pArg1[1787] == 25 )
      {
        nClock1910 = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
        pVt2 = *pArg1;
        pArg1[1926] = nClock1910 + 5000;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 1104))(pArg1, 4);
      }
      break;
    case 14:
      sub_4926A0(*(uint32_t *)pArg1[1554]);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)pArg1[1554]);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      break;
    case 10:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_PRAY", -1, 0, 0);
      nPhase2072b = pArg1[2072];
      if ( nPhase2072b != 0 )
      {
        if ( nPhase2072b == 1 || nPhase2072b == 2 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
            pArg1,
            1,
            0,
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(
            pArg1,
            *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36),
            1);
          sub_5B86D0(1);
          ++pArg1[2163];
          pArg1[2164] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4);
          pArg1[2165] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 8);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
          pArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
          pArg1,
          1,
          0,
          0,
          0,
          0,
          0);
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36), 1);
        sub_5B86D0(1);
        sub_5B7500(1);
      }
      break;
    default:
      break;
  }
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5B9240 sub_5B9240 —— 主状态机透传（反应态 5 时补写音效槽 163）
// 调 ·sub_5B8CE0 主状态机；this+6556==5（死亡收尾）时经 vt+216 写音效槽 163。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9240(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 5 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 216))(this, 163);
  return result;
}



// 信徒·附着火焰攻击（87L）：事件16 时用事件参数对经 sub_45EBE0 解算目标，
//   扫其 vt+700 附着物列表找宿主==目标且 RTTI 为 CNAppendageTimerFireDamage 的项
//   激活(vt+76)；再 new CNAppendageTimerFireDamage(0x5B85C0: 存续 10000ms/伤害 999/
//   间隔 20ms)挂到(目标,self)上——信徒给玩家"点火" debuff
// ------------------------------------------------------------
// 0x5B9280 sub_5B9280 —— 附着火焰攻击（事件 16 点火 debuff）补充
// 先经目标 vt+700 附着物列表查 RTTI IRDAppendage→CNAppendageTimerFireDamage、宿主 this+4==目标
// 者并 vt+76 激活；再 new 0x5C 由 ·sub_5B85C0(10000,999,20) 构造、vt+56 挂(目标,自身)。
// 非 16 事件整体转 ·sub_5B8CE0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9280(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int *pEvtArgs; // eax
  int result; // eax
  int pTargetObj; // esi
  unsigned int i; // edi
  int pVecHdr; // eax
  int pVecBegin; // ecx
  int nCnt; // eax
  int pVecHdr2; // eax
  int pVecBegin2; // ecx
  int pListObj; // ecx
  int pVecHdr3; // eax
  int pVecBegin3; // ecx
  int pListObj2; // ecx
  int pAppendage; // eax
  uint32_t *pMem; // eax
  uint32_t *pFireDmg; // eax
  int nObjKey1; // [esp-8h] [ebp-20h]
  int nObjKey2; // [esp-4h] [ebp-1Ch]

  if ( ArgList != 16 )
    return sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);
  pEvtArgs = *(int **)(LODWORD(fArg3) + 4);
  nObjKey2 = pEvtArgs[1];
  nObjKey1 = *pEvtArgs;
  (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
  result = sub_45EBE0(nObjKey1, nObjKey2);
  pTargetObj = result;
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      pVecHdr = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);
      pVecBegin = *(uint32_t *)(pVecHdr + 4);
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(pVecHdr + 8) - pVecBegin) >> 2 : 0;
      if ( (int)i >= nCnt )
        break;
      pVecHdr2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);
      pVecBegin2 = *(uint32_t *)(pVecHdr2 + 4);
      if ( pVecBegin2 != 0 && i < (*(uint32_t *)(pVecHdr2 + 8) - pVecBegin2) >> 2 )
        pListObj = *(uint32_t *)(pVecBegin2 + 4 * i);
      else
        pListObj = 0;
      if ( *(uint32_t *)(pListObj + 4) == pTargetObj )
      {
        pVecHdr3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);
        pVecBegin3 = *(uint32_t *)(pVecHdr3 + 4);
        if ( pVecBegin3 != 0 && i < (*(uint32_t *)(pVecHdr3 + 8) - pVecBegin3) >> 2 )
          pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * i);
        else
          pListObj2 = 0;
        pAppendage = __RTDynamicCast(
                pListObj2,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNAppendageTimerFireDamage `RTTI Type Descriptor',
                0);
        if ( pAppendage != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pAppendage + 76))(pAppendage, 0);
          break;
        }
      }
    }
    pMem = operator new(0x5Cu);
    if ( pMem != nullptr )
      pFireDmg = sub_5B85C0(pMem, 10000, 999, 20);
    else
      pFireDmg = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int *, uint32_t, uint32_t, uint32_t, int))(*pFireDmg + 56))(
             pFireDmg,
             pTargetObj,
             this,
             0,
             0,
             0,
             -1);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B93F0 sub_5B93F0 —— 指挥旗挂载（new 0x64 → ·sub_51A7D0）并提速
// 先跑 ·sub_5B7CD0 清参数面；nArg3==0 时若 this+8676 空槽则 new 0x64 经 ·sub_51A7D0 构造，
// vt+64 取位后 +36 清 0，vt+56 挂(自身,自身)；再把控制柄 +830/+858 各 +0.5
// 【推断：移速/攻速提档】，vt+676(0) 提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B93F0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  void *pMem; // eax
  int pNewObj; // eax
  unsigned int pCtrl830; // edi
  int v8; // edx
  unsigned int pCtrl858; // edi
  int v10; // edx
  int fVal830; // [esp+20h] [ebp+Ch]
  int fVal858; // [esp+20h] [ebp+Ch]

  result = sub_5B7CD0((int)this, nArg2, nArg3);
  if ( nArg3 == 0 )
  {
    if ( *(this + 2169) == 0 )
    {
      pMem = operator new(0x64u);
      if ( pMem != nullptr )
        pNewObj = sub_51A7D0(pMem);
      else
        pNewObj = 0;
      *(this + 2169) = pNewObj;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pNewObj + 64))(pNewObj) + 36) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2169) + 56))(
        *(this + 2169),
        this,
        this,
        1,
        0,
        0,
        -1);
    }
    pCtrl830 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pCtrl830)) + 0.5;
    sub_41A590(pCtrl830, v8, fVal830);
    pCtrl858 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&fVal858 = COERCE_FLOAT(sub_41A5E0(pCtrl858)) + 0.5;
    sub_41A590(pCtrl858, v10, fVal858);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// 插刀技能：KNIFE_STICK 播报（sub_431230 参数打包; this+200/8605/8606 相位）
// ------------------------------------------------------------
// 0x5B9500 sub_5B9500 —— 插刀技能（KNIFE_STICK 播报 + 事件 5 派发）
// 经 vt+200 取帧位后 +148==2 且 this+8606==0 时播 KNIFE_STICK 并置 this+8606=1；
// 帧位 +170 非 0 时 ·sub_431230 打包事件参数 5，经 vt+472(5,打包,1,1) 派发并置 this+8605=1。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9500(uint8_t *this)
{
  void *Block2; // eax
  bool v3; // zf
  uint8_t v4[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]
  uint32_t v8[4]; // [esp+18h] [ebp-10h] BYREF

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) == 2 && *(this + 8606) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "KNIFE_STICK",
      -1,
      0,
      0);
    *(this + 8606) = 1;
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    Block = nullptr;
    v6 = 0;
    v7 = 0;
    v8[3] = 0;
    v8[0] = 5;
    sub_431230((int)v4, v8);
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint8_t *, int, int))(*(uint32_t *)this + 472))(this, 5, v4, 1, 1);
    Block2 = Block;
    v3 = Block == nullptr;
    *(this + 8605) = 1;
    if ( !v3 )
      j__free(Block2);
  }
}



// 信徒·寻损车决策（84L）：门=修复次数 this[2162]<3 且距上次修复(this[2161])≥7 秒、
//   本地玩家、空闲——扫场景标记 529 的 CNVehicle，同房间(vt+376)、距离≤100、
//   血量 vt+736 < vt+740×0.3（残血 30%）时 setState(15,[车X,车Y]) 前去修复
// ------------------------------------------------------------
// 0x5B95D0 sub_5B95D0 —— 信徒·寻损车决策（setState 15 修复）补充
// 修复次数 this[2162]<3、距上次修复 this[2161] 满 7000ms（·sub_699000 时钟）；
// 场景扫描同上（vt+40 529 / RTTI CNVehicle / vt+376 房间 / vt+8 距离≤100），
// 血量 vt+736、满血 vt+740；命中时 ·sub_431230 打包 vt+48/vt+52 坐标，vt+560 进 15。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B95D0(uint32_t *this)
{
  unsigned int i; // ebx
  int fld_e29; // ecx
  int pVecBegin; // edx
  int nCnt; // eax
  int pVecBegin2; // edx
  int pListObj; // ecx
  int fld_e292; // ecx
  int pVecBegin3; // edx
  int pListObj2; // eax
  int pVehicle; // esi
  int nRoomId; // ebx
  int pVehicleVt; // eax
  int pVehicleVt2; // edx
  void *pBuf[4]; // [esp+4h] [ebp-28h] BYREF
  float fVehVal; // [esp+14h] [ebp-18h] BYREF
  int nVehVal; // [esp+18h] [ebp-14h]
  unsigned int nIdxSaved; // [esp+1Ch] [ebp-10h]
  int v19; // [esp+28h] [ebp-4h]

  if ( (int)*(this + 2162) < 3
    && *(this + 2161) + 7000 <= (unsigned int)sub_699000((int)(this + 9))  // 【clock_now(clk)】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      pVecBegin = *(uint32_t *)(fld_e29 + 8);
      nIdxSaved = i;
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;
      if ( (int)i >= nCnt )
        break;
      pVecBegin2 = *(uint32_t *)(fld_e29 + 8);
      if ( pVecBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - pVecBegin2) >> 2 )
        pListObj = *(uint32_t *)(pVecBegin2 + 4 * i);
      else
        pListObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 529) != 0 )
      {
        fld_e292 = *(this + 29);
        pVecBegin3 = *(uint32_t *)(fld_e292 + 8);
        if ( pVecBegin3 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - pVecBegin3) >> 2 )
          pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * i);
        else
          pListObj2 = 0;
        pVehicle = __RTDynamicCast(pListObj2, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);
        if ( pVehicle != 0 )
        {
          nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 376))(pVehicle);
          if ( nRoomId == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
            && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pVehicle, 0) <= 100 )
          {
            nVehVal = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 736))(pVehicle);
            pVehicleVt = *(uint32_t *)pVehicle;
            fVehVal = (float)nVehVal;
            nVehVal = (*(int (/*thiscall*/ **)(int))(pVehicleVt + 740))(pVehicle);
            if ( (double)nVehVal * 0.30000001 >= fVehVal )
            {
              memset(&pBuf[1], 0, 12);
              pVehicleVt2 = *(uint32_t *)pVehicle;
              v19 = 0;
              fVehVal = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(pVehicleVt2 + 48))(pVehicle));
              sub_431230((int)pBuf, &fVehVal);
              fVehVal = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 52))(pVehicle));
              sub_431230((int)pBuf, &fVehVal);
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 15, pBuf, 0, 0);
              sub_5E5260(pBuf);
              return;
            }
          }
          i = nIdxSaved;
        }
      }
    }
  }
}



// 信徒·祈祷决策（6.7% 概率）：门=this[1908]∈{0,2}（2 时需 this[1909]==0）、空闲、
//   非动作25、有目标、祈祷次数 this[2159]<3、rand%300<20——再统计全局列表中
//   IRDMonster+8352(召唤者)==自身者 <2 只时 setState(10) 祈祷召怪
// ------------------------------------------------------------
// 0x5B97A0 sub_5B97A0 —— 信徒·祈祷决策（setState 10）补充
// 候选统计经 ·sub_4259D0(i) 取场景项、vt+40(obj,529) 过滤、RTTI IRDMonster 判 this+8352==自身；
// 计数 <2 且概率 rand%300<20 且祈祷计数 this[2159]<3、非动作 25 时 ·sub_431230 打包
// （首参 0），vt+560 进 10 祈祷。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B97A0(uint32_t *this)
{
  int fld_e1908; // eax
  int i; // edi
  int fld_e29; // ecx
  int pVecBegin; // edx
  int nCnt; // eax
  int pCand; // eax
  int pCandRaw; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v10[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    fld_e1908 = *(this + 1908);
    if ( (fld_e1908 == 0 || fld_e1908 == 2 && *(this + 1909) == 0)
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
      && *(this + 1787) != 25
      && *(this + 1813) != 0
      && (int)*(this + 2159) < 3
      && rand() % 300 < 20 )
    {
      v10[0] = 0;
      for ( i = 0; ; ++i )
      {
        fld_e29 = *(this + 29);
        pVecBegin = *(uint32_t *)(fld_e29 + 8);
        nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;
        if ( i >= nCnt )
          break;
        pCand = sub_4259D0(i);
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pCand + 40))(pCand, 529) != 0 )
        {
          pCandRaw = sub_4259D0(i);
          if ( *(uint32_t **)(__RTDynamicCast(
                              pCandRaw,
                              0,
                              &CNRDObject `RTTI Type Descriptor',
                              &IRDMonster `RTTI Type Descriptor',
                              0)
                          + 8352) == this )
            ++v10[0];
        }
      }
      if ( v10[0] < 2 )
      {
        memset(&pBuf[1], 0, 12);
        v10[3] = 0;
        v10[0] = 0;
        sub_431230((int)pBuf, v10);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, pBuf, 0, 0);
        sub_5E5260(pBuf);
      }
    }
  }
}



// 参数打包 AI（sub_431230+RTTI cast, 88L）
// ------------------------------------------------------------
// 0x5B98F0 sub_5B98F0 —— 信徒·传教解算（nArg2=1 指挥 / 2 布道；setState 10）
// 扫场景 RTTI CNZealot：型 1 取 this+8607 指挥态非 0 的信徒，型 2 取 this+8668 冷却已毕者；
// 再以 vt+1244 视线可达 + vt+340 资源 ID ∈ {260,263,264} 校验，命中后 ·sub_431230 打包
// vt+48/vt+52 坐标；打包 ≥2 项时 vt+560 进 10。门=祈祷计数<3 且 rand%300<20 且非动作 25。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B98F0(uint32_t *this, int nArg2)
{
  int fld_e1908; // eax
  int v4; // ebx
  int fld_e29; // ecx
  int v6; // edx
  int v7; // eax
  int pObj; // eax
  int v9; // eax
  int pObj2; // esi
  void *v11; // [esp+4h] [ebp-1Ch] BYREF
  int v12; // [esp+8h] [ebp-18h]
  int v13; // [esp+Ch] [ebp-14h]
  int v14; // [esp+10h] [ebp-10h]
  int v15; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )
    return;
  fld_e1908 = *(this + 1908);
  if ( fld_e1908 != 0 && (fld_e1908 != 2 || *(this + 1909) != 1) )
    return;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0
    || *(this + 1787) == 25
    || nArg2 != 1 && nArg2 != 2
    || (int)*(this + 2163) >= 3
    || *(this + 1813) == 0
    || rand() % 300 >= 20 )
  {
    return;
  }
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  sub_431230((int)&v11, &nArg2);
  v4 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v6 = *(uint32_t *)(fld_e29 + 8);
    v7 = v6 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 : 0;
    if ( v4 >= v7 )
      break;
    pObj = sub_4259D0(v4);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )
      goto LABEL_28;
    v9 = sub_4259D0(v4);
    pObj2 = __RTDynamicCast(v9, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
    if ( pObj2 == 0 )
      goto LABEL_28;
    if ( nArg2 != 1 )
    {
      if ( nArg2 != 2 || *(int *)(pObj2 + 8668) > 0 )
        goto LABEL_28;
      goto LABEL_24;
    }
    if ( *(uint8_t *)(pObj2 + 8607) != 0 )
    {
      ++v4;
    }
    else
    {
LABEL_24:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2) != 0
        && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 260
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 263
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 264) )
      {
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
        sub_431230((int)&v11, &nArg2);
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);
        sub_431230((int)&v11, &nArg2);
        break;
      }
LABEL_28:
      ++v4;
    }
  }
  if ( v12 != 0 && (unsigned int)((v13 - v12) >> 2) > 1 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, &v11, 0, 0);
  sub_5E5260(&v11);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B00 sub_5B9B00 —— 信徒 AI 拍合并（行为拍 + 寻车 + 寻损车修复）
// 单拍三连：·sub_5B77F0 行为字节拍、·sub_5B87C0 寻车解算、·sub_5B95D0 寻损车修复决策。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B00(int *this)
{
  sub_5B77F0(this);
  sub_5B87C0(this);
  sub_5B95D0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B20 sub_5B9B20 —— 信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 2 型）
// 与 ·sub_5B9B00 同构（差异：第二/第三段为 ·sub_5B97A0 与 ·sub_5B98F0(this,2)）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B20(int *this)
{
  sub_5B77F0(this);
  sub_5B97A0(this);
  sub_5B98F0(this, 2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B40 sub_5B9B40 —— 信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 1 型）
// 与 ·sub_5B9B20 同构（差异：末段 ·sub_5B98F0(this,1)，取指挥态目标）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B40(int *this)
{
  sub_5B77F0(this);
  sub_5B97A0(this);
  sub_5B98F0(this, 1);
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B9B60 sub_5B9B60 —— 点火事件派发（30% 概率 setState 16）后尾调反击判定
// 门=vt+840 大状态 8、this+7028 空槽、vt+40(nArg2,17) 存活 且有目标，rand%100<30 时
// ·sub_431230 打包 nArg2 的 vt+48/vt+52 坐标，vt+560 进 16（与 ·sub_5B9280 事件 16 呼应点火）；
// 末尾无条件交 ·sub_4DB480 反击/架招触发判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9B60(void *this, int nArg2, int nArg3, int nArg4)
{
  int pThis_348; // eax
  int pObj; // edi
  int v7; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  pThis_348 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  pObj = nArg2;
  if ( pThis_348 == 8
    && sub_41A5E0((unsigned int)this + 7028) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0
    && rand() % 100 < 30 )
  {
    memset(&pBuf[1], 0, 12);
    v7 = *(uint32_t *)pObj;
    v10 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v7 + 48))(pObj);
    sub_431230((int)pBuf, &nArg2);
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    sub_431230((int)pBuf, &nArg2);
    (*(void (/*thiscall*/ **)(void *, int, void **, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 16, pBuf, 0, 0);
    v10 = -1;
    sub_5E5260(pBuf);
  }
  return sub_4DB480(pObj, nArg3, nArg4);
}



// 祈祷技能：BELIEVER_PRAY 播报（103L；this+208 相位 —— 治疗channel/咏唱【推断】）
// ------------------------------------------------------------
// 0x5B9C60 sub_5B9C60 —— 祈祷技能收尾（BELIEVER_PRAY 播报 + 3 型收尾）补充
// 补充：前置场景识别经 ·sub_41A5E0==3 时直接 setState 10；子相位 this[2072]==3 时
// vt+580 发 20014（10 段/4 朝向）表现包、·sub_49C970/·sub_49C5F0 光环族驱动、
// vt+876 双轴归零、vt+992 复位、·sub_5B86D0 挂三帧、·sub_5B7500 盾闪收尾；
// 末段整体透传 ·sub_5B8CE0。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9C60(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // edi
  bool bPrayState; // zf
  int nEvt; // edi
  uint8_t v9[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v11; // [esp+10h] [ebp-14h]
  int v12; // [esp+14h] [ebp-10h]
  int v13; // [esp+20h] [ebp-4h]

  fld_e1639 = *(this + 1639);
  if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v13 = 0;
      ArgList = 3;
      sub_431230((int)v9, &ArgList);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 10, v9, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
  else
  {
    bPrayState = fld_e1639 == 10;
    nEvt = ArgList;
    if ( bPrayState )
    {
      if ( ArgList == 0 && *(this + 2072) == 3 )
      {
        sub_49C970(8, ArgList, ArgList);
        sub_49C5F0(9, 0, 0, 4000);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            20014,
            10,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
      sub_5B7500(this, 0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 996))(this);
    }
    sub_5B8CE0(this, nEvt, fArg3, nArg4, nArg5);
    if ( nEvt == 10 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "BELIEVER_PRAY",
        -1,
        0,
        0);
      if ( *(this + 2072) == 3 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 992))(
          this,
          *(uint32_t *)(*(uint32_t *)(*(this + 1554) + 8) + 36),
          1);
        sub_5B86D0(this, 1);
        sub_5B7500(this, 1);
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B9EA0 sub_5B9EA0 —— 献祭长驻（this+8664=20；new CNAuraMasterATDFSPEEDUpFather）
// 仅自身消息(Block==this)：写 this+8664=20，vt+700 取资源族、·sub_53F6A0 清挂点，
// new 0x90 经 ·sub_64C710(300,两个 0x3E99999A=0.3f) 构造，vftable 写
// CNAuraMasterATDFSPEEDUpFather，vt+56 挂(自身,自身)；vt+384(0) 取出场参数存 this+8640。
// ------------------------------------------------------------
void */*thiscall*/ sub_5B9EA0(uint32_t *this, uint32_t *Block)
{
  void *result; // eax
  int v4; // eax
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx

  result = Block;
  if ( Block == this )
  {
    v4 = *this;
    *(this + 2166) = 20;
    (*(void (**)(void))(v4 + 700))();
    sub_53F6A0(this);
    pMem = operator new(0x90u);
    if ( pMem != nullptr )
    {
      sub_64C710(300, 1041865114, 1041865114, 0, 0);
      *pMem = &CNAuraMasterATDFSPEEDUpFather::`vftable';
      pMem2 = pMem;
    }
    else
    {
      pMem2 = nullptr;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(
      pMem2,
      this,
      this,
      0,
      0,
      0,
      -1);
    result = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
    *(this + 2160) = result;
  }
  return result;
}



// ============================================================
// 【分区 6】炮车牛 & 激光炮（CowCannon / DrgCannon）（0x5B9F60-0x5BAC30）
// 证据：Particle/FireMissileParticleFloor.ptl、COWCANNON_READY/SHOOT、
//       Particle/CannonBall{Direct,Angle}.ptl、LASERCANNON_READY、DRGCANNON_READY/SHOOT/MOVE_LOOP

// 地面火导弹：引用 PassiveObject/Common/Particle/FireMissileParticleFloor.ptl
// ------------------------------------------------------------
// 0x5B9F60 sub_5B9F60 —— 地面火导弹附着（FireMissileParticleFloor.ptl）补充
// 基类先 ·sub_5F66C0（IRDAppendage 虚方法）；this+22 挂点空时 new 0x12C 经 ·sub_428F30 载
// PassiveObject/Common/Particle/FireMissileParticleFloor.ptl、vt+112(宿主) 回挂；
// 每拍取宿主 vt+120/124/128 三坐标，vt+40 提交、vt+92 取姿态，vt+80 取表现位后
// ·sub_4600B0(表现位, X, Y, Z) 定位于火焰地板。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9F60(int *this)
{
  uint32_t *pMem; // eax
  int *fld_e1; // eax
  int fld_e12; // ecx
  int v5; // edx
  int fld_e13; // edi
  int fld_e22; // ebx
  int *fld_e14; // esi
  int v9; // edx
  void *v10; // eax
  int v11; // [esp-Ch] [ebp-38h]
  int v12; // [esp-8h] [ebp-34h]
  int v13; // [esp-4h] [ebp-30h]
  uint8_t v14[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v17; // [esp+28h] [ebp-4h]

  sub_5F66C0();  // 【IRDAppendage__vmt4】
  if ( *(this + 22) == 0 )
  {
    pMem = operator new(0x12Cu);
    pMem2 = pMem;
    v17 = 0;
    if ( pMem != nullptr )
      fld_e1 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/FireMissileParticleFloor.ptl", *(this + 1));
    else
      fld_e1 = nullptr;
    fld_e12 = *(this + 1);
    *(this + 22) = (int)fld_e1;
    v5 = *fld_e1;
    v17 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(fld_e1, fld_e12);
  }
  fld_e13 = *(this + 1);
  fld_e22 = *(uint32_t *)*(this + 22);
  v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 128))(fld_e13);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 124))(fld_e13);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 120))(fld_e13);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e22 + 40))(*(this + 22));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 22) + 92))(*(this + 22), v14);
  fld_e14 = (int *)*(this + 1);
  v9 = *fld_e14;
  v17 = 1;
  v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v9 + 80))(fld_e14, 2, 0, v14);
  sub_4600B0(v10, v11, v12, v13);
  if ( Block != nullptr )
    j__free(Block);
}



// 子类扩展字段复位（this+8600/8604/8605）
// ------------------------------------------------------------
// 0x5BA050 sub_5BA050 —— 子类扩展字段复位（this+8600 指针 + 8604/8605 状态字节 + 6792..6808）
// 清 this+8600（uint32 资源/机器对象指针）、8604/8605（相位字节，与 ·sub_5B8CE0/·sub_5B8590
// 的读写点对应）、this+6792/6796/6800/6804/6808 五槽（炮车参数面【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA050(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA090 sub_5BA090 —— 资源对象释放（this+8600 经 vtable[0](obj,1)）并清槽
// this+8600 指针非空时按 vtable[0](obj,1) 释放（删除式），随后槽置 0；
// 与 ·sub_5BA050 的清位互为配套（先释放后复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA090(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2150)(uint32_t, int); // ecx
  int result; // eax

  fld_e2150 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2150);
  if ( fld_e2150 != nullptr )
    result = (**fld_e2150)(fld_e2150, 1);
  *(this + 2150) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA0B0 sub_5BA0B0 —— 炮车系·攻击态朝向对准（基类收尾 + 面向目标）
// 先调 ·sub_4E33D0 做基类状态收尾；武器态 ArgList==8（攻击）且目标 this+1813 有效时，
// 按双方 X 槽（vt+120）大小经 vt+148/vt+144 写翻转朝向——·sub_5BA3E0/·sub_5BA570 的公共前置。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA0B0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edi
  BOOL v8; // edi

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    result = *(this + 1813);
    if ( result != 0 )
    {
      v7 = (*(int (**)(void))(*(uint32_t *)result + 120))();
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v7;
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 148))(this, v8);
      return (*(int (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 144))(this, v8);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA120 sub_5BA120 —— 炮车系·反应态决策机（行为字 this+1787 概率互转）
// 前置 ·sub_4E0120 基类 AI；按 this+1787 行为字分支：0 → vt+1284 默认动作【推断】。
// 受击后置(4)：无目标直接转 13；有目标 10% 概率转 5（rand()%100<10，vt+1104 写行为字）。
// 死亡(5)：有目标 2% 概率转 4（复活反打【推断】）；13/14/15：目标存在即转 4 反打。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA120(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand2 = rand();
        v4 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v4 < 2 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA200 sub_5BA200 —— 三效果槽释放（this+2153/2154/2155）
// 逐槽按 vtable[0](obj,1) 释放后清零——与 ·sub_5BAD00 的 EF_Fire/EF_Hikari/FlameThrower 装载互为对偶。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA200(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2153)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2154)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx

  fld_e2153 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2153);
  if ( fld_e2153 != nullptr )
    result = (**fld_e2153)(fld_e2153, 1);
  fld_e2154 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);
  *(this + 2153) = 0;
  if ( fld_e2154 != nullptr )
    result = (**fld_e2154)(fld_e2154, 1);
  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);
  *(this + 2154) = 0;
  if ( fld_e2155 != nullptr )
    result = (**fld_e2155)(fld_e2155, 1);
  *(this + 2155) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA250 sub_5BA250 —— 炮车系·攻击态水平朝向追随（叠加反应态机）
// 先跑 ·sub_5BA120 反应态机；大状态 vt+840==8（攻击）且武器档 ·sub_41A5E0(this+1757)==2 时，
// 按目标 this+1813 与自身 X（vt+120）比较经 vt+144 置/清朝向。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA250(int *this)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi

  sub_5BA120(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 2 )
    {
      result = *(this + 1813);
      if ( result != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813 )
            (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, 1);
        }
        result = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        if ( result == 1 )
        {
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          if ( result >= fld_e18132 )
            return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, 0);
        }
      }
    }
  }
  return result;
}



// 炮弹技能：引用 Particle/CannonBallDirect.ptl + CannonBallAngle.ptl（平射/抛射两种弹道）
// ------------------------------------------------------------
// 0x5BA2F0 sub_5BA2F0 —— 炮车·炮弹发射（平射/抛射二选一弹道）
// vt+588 装载模板 + vt+580 发射，参数组 70/50/4 与 this+2156（vt+384 出场参数面）——·sub_5BB130 段号 0/1 路径调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA2F0(uint32_t *this)
{
  int v2; // eax

  if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallDirect.ptl");
  else
    v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallAngle.ptl");
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
           this,
           *(this + 2156),
           0,
           v2,
           0,
           70,
           0,
           50,
           4,
           0,
           0,
           0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA350 sub_5BA350 —— 分身/攻击参数面复位（激活标志 this+7535=1）
// 清 this+7531..7596 整块参数面（字节段 7531-7558 与 7535-7596 双字槽），末置字节 this+7535=1 使能——
// 与 ·sub_5BA730/·sub_5BA810 为同族变体（差异：激活槽不同）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA350(int this, int nArg2, int nArg3)
{
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint8_t *)(this + 7535) = 1;
  return 0;
}



// 蓄力播报：COWCANNON_READY（炮车牛瞄准, this+8612 相位）
// ------------------------------------------------------------
// 0x5BA3E0 sub_5BA3E0 —— 炮车牛·蓄力就绪（COWCANNON_READY）
// 先走 ·sub_5BA0B0 基类前置；武器态 ArgList==8 时清 this+8612 相位并经 vt+212 播报（-1 立即）——
// 与 ·sub_5BAB60 的 COWCANNON_SHOOT 播报成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA3E0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // eax

  result = sub_5BA0B0(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    v7 = *this;
    *((uint8_t *)this + 8612) = 0;
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v7 + 212))(
             this,
             "COWCANNON_READY",
             -1,
             0,
             0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA430 sub_5BA430 —— 炮车·受击包观察者回调（vmt1F8 覆写）
// 攻击者（nArg2）为 17 标记存活目标（vt+40）且 nArg4==0 时，取攻击者 vt+684 档位经 sub_41A5E0 奇偶门；
// 受击距离 vt+8(this,nArg2)>90 则清 AI 阈值 this+2152；尾调 ·sub_4D4A20 转发观察者通知。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA430(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  unsigned int v5; // eax
  bool v6; // zf
  signed int v7; // eax
  unsigned int v8; // eax

  if ( (uint8_t)nArg4 == 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);
    v7 = sub_41A5E0(v5) & 0x80000001;
    v6 = v7 == 0;
    if ( v7 < 0 )
      v6 = (((uint8_t)v7 - 1) | 0xFFFFFFFE) == -1;
    if ( !v6 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);
      if ( sub_41A5E0(v8) > 0 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) > 90 )
        *(this + 2152) = 0;
    }
  }
  return sub_4D4A20(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA4B0 sub_5BA4B0 —— 激光炮·级进帧序弹道解算与发射
// 目标门 vt+308 通过后：vt+152 姿态非 0 时按 224 帧步进表（this[29] 层链 +132 → +360/+364 向量，元素 32 字节）
// 取「表元数×224 − 当前游标 vt+120」再 /100 缩放得发射参数 v12【推断：帧序表换算】；
// 经 vt+580 以 85/50/4 参数组发射（武器码由调用方传入 30015/30036/48029）。
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5BA4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int result; // eax
  int v6; // ebx
  int64_t v7; // rax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);
    if ( v6 != 0 )
    {
      v8 = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      v9 = *(uint32_t *)(v8 + 364);
      v10 = v8 + 360;
      if ( v9 != 0 )
        v11 = (*(uint32_t *)(v10 + 8) - v9) >> 5;
      else
        v11 = 0;
      v7 = 1374389535LL * (224 * v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
    }
    else
    {
      v7 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    }
    v12 = (SHIDWORD(v7) >> 5) + (HIDWORD(v7) >> 31);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
             pArg1,
             nArg4,
             v12,
             0,
             0,
             85,
             0,
             50,
             v6,
             0,
             0,
             0);
  }
  return result;
}



// 激光炮播报组：LASERCANNON_READY + DRGCANNON_READY/SHOOT（79L；激光炮/龙炮共用）
// ------------------------------------------------------------
// 0x5BA570 sub_5BA570 —— 激光炮/龙炮共用·攻击态映射与播报组
// 大状态 this+6556==8（攻击）时按段号 this+7028：==4 经 vt+208 写两帧（this+6216 双对象）、
// ==2 经 vt+216 播报 9。ArgList==8 时：段 3 → ·sub_41A590 推进到段 4；段 4 → ·sub_5BA4B0 发射 48029
// + 两发 ·sub_4926A0 帧游标复位 + vt+204 打两帧(100/200) + LASERCANNON_READY；
// 段 2 → this+8620 对象复位 + DRGCANNON_READY；段 0/1 → DRGCANNON_SHOOT。
// ------------------------------------------------------------
int /*userpurge*/ sub_5BA570@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int result; // eax
  int v8; // edx
  int savedregs; // [esp+8h] [ebp+0h]
  int savedregsa; // [esp+8h] [ebp+0h]

  if ( *(uint32_t *)(pArg1 + 6556) == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) == 4 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);
    }
  }
  result = sub_5BA0B0((uint32_t *)pArg1, ArgList, fArg4, nArg5, nArg6);
  if ( ArgList == 8 )
  {
    *(uint8_t *)(pArg1 + 8608) = 0;
    if ( sub_41A5E0(pArg1 + 7028) == 3 )
      sub_41A590(pArg1 + 7028, v8, 4);
    if ( sub_41A5E0(pArg1 + 7028) == 4 )
    {
      sub_5BA4B0((uint32_t *)pArg1, nArg2, pArg1 + 7028, 48029);
      sub_4926A0(**(uint32_t **)(pArg1 + 6216));
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
        pArg1,
        100,
        **(uint32_t **)(pArg1 + 6216),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
        pArg1,
        200,
        *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
        0,
        0,
        0,
        0);
      savedregs = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_READY");
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8620) + 12))(*(uint32_t *)(pArg1 + 8620), 0);
      savedregsa = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "DRGCANNON_READY");
    }
    if ( sub_41A5E0(pArg1 + 7028) == 0 )
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
               pArg1,
               "DRGCANNON_SHOOT",
               -1,
               0,
               0);
    result = sub_41A5E0(pArg1 + 7028);
    if ( result == 1 )
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
               pArg1,
               "DRGCANNON_SHOOT",
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA700 sub_5BA700 —— 载具·X 轴速率槽降速（1/3 收缩）
// nArg3==2 时门控参数取 nArg2；门控为 0 时把 this+1905 所指对象 +4 浮点槽（X 速率/缩放【推断】）乘 0.3333——
// 与 ·sub_5BA7E0 成对（后者作用于 +132 槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA700(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg3;
  if ( nArg3 == 2 )
    result = nArg2;
  if ( result == 0 )
  {
    result = *(this + 1905);
    *(float *)(result + 4) = *(float *)(result + 4) * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA730 sub_5BA730 —— 分身/攻击参数面复位变体（激活槽 this+7568=1）
// 与 ·sub_5BA350 同构（差异：使能槽为 this+7568，且门控为 0 时把 this+7620 对象 +4 浮点槽乘 3.0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA730(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7568) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4) * 3.0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA7E0 sub_5BA7E0 —— 载具·高位速率槽降速（+132 槽 1/3 收缩）
// 与 ·sub_5BA700 同构（差异：作用槽为 this+1905 对象 +132 即 vt+128 高度槽组的第二浮点【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA7E0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 2 )
    result = nArg2;
  if ( result == 0 )
  {
    fld_e1905 = *(this + 1905);
    v5 = *(float *)(fld_e1905 + 132);
    result = fld_e1905 + 128;
    *(float *)(result + 4) = v5 * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA810 sub_5BA810 —— 分身/攻击参数面复位变体（激活槽 this+7564=2）
// 与 ·sub_5BA730 同构（差异：使能槽为 this+7564 且置双字节值 2，缩放槽同为 this+7620 对象 +132）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA810(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7564) = 2;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 132) = *(float *)(*(uint32_t *)(this + 7620) + 132) * 3.0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA8D0 sub_5BA8D0 —— 炮车·骑乘位姿提交（炮台对象归位挂层）
// 2150 对象 vt[3](0) 复位动画，按 vt[32](this)→vt[31](+50)→vt[30] 链式取位经对象 vt+40 写入，
// vt+92 打包后由 sub_4600B0 以层号 2 挂到自身层链(this+29)——由 ·sub_5BAC50/80/ACC0 在放生/撤离时调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BA8D0(uint32_t **this)
{
  int fld_e2150; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *fld_e29; // ecx
  uint8_t v7[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v9; // [esp+20h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2150) + 12))(*(this + 2150), 0);
  fld_e2150 = **(this + 2150);
  v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3 + 50);
  v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2150 + 40))(*(this + 2150), v5);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2150) + 92))(*(this + 2150), v7);
  fld_e29 = *(this + 29);
  v9 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v7);
  if ( Block != nullptr )
    j__free(Block);
}



// 移动循环：DRGCANNON_MOVE_LOOP 播报（91L；this+200/8604/8605）
// ------------------------------------------------------------
// 0x5BA980 sub_5BA980 —— 炮车龙炮·移动循环与滑行特效（DRGCANNON_MOVE_LOOP）
// 前置 ·sub_4E1780 基类移动；运动中（大状态非 0，或 vt+184/vt+188 双轴均 4）且 this+8605 置位时经 vt+216 停熄（播报 9）、清 8605。
// 否则当主状态子槽（vt+200 对象 +148）为 1 或 3 且 this+8604==0：从全局表 ·dword_8F8270[vt+924(this,2)] 取特效对象，
// 按自身朝向 vt+152 与 vt+120/124/128 位置 ±20 摆放（pFx+28 对象 +84 写翻转）挂层(层 2)，置 8604=1；
// 子槽归 0 且 8604==1 则清 8604。驻足时若 8605==0 播 DRGCANNON_MOVE_LOOP(9) 并置 8605=1。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BA980(int *this)
{
  uint32_t *pFxRes; // edi
  int pVt; // eax
  int nDirRaw; // eax
  int pVt2; // edx
  int pFxVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nDx; // edi
  uint32_t *pFxObj; // edi
  void *fld_e29; // ecx
  void *Block2; // eax
  bool v13; // zf
  int nX; // [esp-Ch] [ebp-34h]
  char v15[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  uint32_t *pFxResSaved; // [esp+14h] [ebp-14h]
  bool bFlip; // [esp+1Bh] [ebp-Dh]
  int v21; // [esp+24h] [ebp-4h]

  sub_4E1780(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4
    && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )
  {
    if ( *((uint8_t *)this + 8605) == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
      *((uint8_t *)this + 8605) = 0;
    }
  }
  else
  {
    if ( *((uint8_t *)this + 8604) == 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 1
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 3) )
    {
      pFxRes = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
      pVt = *this;
      pFxResSaved = pFxRes;
      nDirRaw = (*(int (/*thiscall*/ **)(int *))(pVt + 152))(this);
      pVt2 = *this;
      pFxVt = *pFxRes;
      bFlip = nDirRaw == 0;
      nZ = (*(int (/*thiscall*/ **)(int *))(pVt2 + 128))(this);
      nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);
      nDx = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, nY + 1) != 0 ? -20 : 20;
      nX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + nDx;
      pFxObj = pFxResSaved;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(pFxVt + 40))(pFxResSaved, nX);
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pFxResSaved + 28))(pFxResSaved) + 84) = bFlip;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pFxObj + 12))(pFxObj, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pFxObj + 92))(pFxObj, v15);
      fld_e29 = (void *)*(this + 29);
      v21 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v15);
      Block2 = Block;
      v13 = Block == nullptr;
      *((uint8_t *)this + 8604) = 1;
      v21 = -1;
      if ( !v13 )
        j__free(Block2);
      Block = nullptr;
      v17 = 0;
      v18 = 0;
    }
    else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 && *((uint8_t *)this + 8604) == 1 )
    {
      *((uint8_t *)this + 8604) = 0;
    }
    if ( *((uint8_t *)this + 8605) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "DRGCANNON_MOVE_LOOP",
        9,
        0,
        0);
      *((uint8_t *)this + 8605) = 1;
    }
  }
}



// 开火：COWCANNON_SHOOT 播报（this+200/8608/8612 相位, 60L）
// ------------------------------------------------------------
// 0x5BAB60 sub_5BAB60 —— 炮车牛·开火与骑手放生（COWCANNON_SHOOT）
// 先跑 ·sub_5BA980 移动循环；大状态 vt+840==8（攻击）且主状态子槽（vt+200 对象 +148）>=9 时，
// 若 this+8612==0 经 vt+212 播 COWCANNON_SHOOT 并置位。再查骑手槽 this+8608：骑手大状态 vt+840==3 且
// 子槽 vt+236==0 时，按 vt+876 双轴给 −400/−400/2000 参数、vt+888 播 1000 后清空骑手槽（放生）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BAB60(int this)
{
  int nTmp; // eax
  int pRider; // ecx

  sub_5BA980((int *)this);
  nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( nTmp == 8 )
  {
    nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(int *)(nTmp + 148) >= 9 )
    {
      LOBYTE(nTmp) = *(uint8_t *)(this + 8612);
      if ( (uint8_t)nTmp == 0 )
      {
        LOBYTE(nTmp) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "COWCANNON_SHOOT",
                       -1,
                       0,
                       0);
        *(uint8_t *)(this + 8612) = 1;
      }
    }
  }
  pRider = *(uint32_t *)(this + 8608);
  if ( pRider != 0 )
  {
    nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRider + 840))(pRider);
    if ( nTmp == 3 )
    {
      nTmp = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8608) + 236))(*(uint32_t *)(this + 8608));
      if ( nTmp == 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 876))(
          *(uint32_t *)(this + 8608),
          0,
          -400,
          -400,
          0,
          2000,
          1);
        LOBYTE(nTmp) = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 888))(
                       *(uint32_t *)(this + 8608),
                       0,
                       0,
                       1000,
                       1000);
        *(uint32_t *)(this + 8608) = 0;
      }
    }
  }
  return nTmp;
}



// ============================================================
// 【分区 7】载具·飞艇（Vehicle / Airship / Zepplin）（0x5BAC30-0x5BCAB0）
// 证据：DRGCANNON_BREAK、Particle/{FCATADestroy,LCATADestroy,CATADestroy,BATIDestroy,
//       EF_Fire,EF_Hikari,FlameThrower}.ptl 破坏粒子族、Monster/Vehicle/Particle/ani/FireSmoke.ani、
//       FLAMETHROWER_FIRE/LOOP + LASERCANNON_SHOOT、AIRSHIP_{01_LOOP,SHOOT,UP,UNLOAD,DOWN,BREAK}、
//       Particle/Zepplin{EX,}Destroy{Fly,Drop}.ptl

// 破损播报：DRGCANNON_BREAK（sub_4015C0 —— 载具破坏语音）
// ------------------------------------------------------------
// 0x5BAC30 sub_5BAC30 —— 载具破坏音效（DRGCANNON_BREAK）
// 无参数包装：直接经 ·sub_4015C0 把 DRGCANNON_BREAK 写入语音/字符串槽（长度 0xF，std::string 构造赋值）。
// ------------------------------------------------------------
int sub_5BAC30()
{
  return sub_4015C0("DRGCANNON_BREAK", 0xFu);  // 【std::string构造赋值】
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC50 sub_5BAC50 —— 炮车·消亡处理（自身命中自我时先归位再死亡）
// 仅当 this==uArg2（消亡对象即自身）时：·sub_5BA8D0 骑乘位姿提交 + vt[54]/·vt+216 进入播报 9；
// 尾调 ·sub_4D9170 消亡通知——与 ·sub_5BAC80/·sub_5BACC0 同族（差异：单次归位+停熄）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC50(uint32_t **this, uint32_t **uArg2)
{
  if ( this == uArg2 )
  {
    sub_5BA8D0(this);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC80 sub_5BAC80 —— 炮车·消亡处理变体（双重停熄）
// 与 ·sub_5BAC50 同构（差异：vt[54] 停熄调用两次、夹在 ·sub_5BA8D0 归位前后）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC80(uint32_t **this, uint32_t **uArg2)
{
  if ( this == uArg2 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
    sub_5BA8D0(this);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x5BACC0 sub_5BACC0 —— 骑手消亡处理（归位 + 清骑乘槽 this+8608）
// this==nArg2 时 ·sub_5BA8D0 归位 + vt+216 播报 9；随后 ·sub_4D9170 消亡通知，
// 若骑乘槽 this+8608==nArg2 则清 0——与 ·sub_5BAC50 同族（差异：独占骑乘槽清位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BACC0(int this, int nArg2)
{
  int result; // eax

  if ( this == nArg2 )
  {
    sub_5BA8D0((uint32_t **)this);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);
  }
  result = sub_4D9170(nArg2);
  if ( *(uint32_t *)(this + 8608) == nArg2 )
    *(uint32_t *)(this + 8608) = 0;
  return result;
}



// 破坏粒子族（88L）：Particle/{EF_Fire,EF_Hikari,FCATADestroy,LCATADestroy,CATADestroy,
//   FlameThrower}.ptl（F=火焰/L=激光/C=通常/BATI=坠落 前缀分型）
// ------------------------------------------------------------
// 0x5BAD00 sub_5BAD00 —— 载具·破坏粒子族装载（4 槽 + 出场参数）
// 清 this+8608 骑乘槽后按 operator new(0x12Cu) 逐槽装载：2153=EF_Fire.ptl、2154=EF_Hikari.ptl、
// 2150=按 vt+340（自身类型码 −270）分支 FCATADestroy/LCATADestroy/否则 CATADestroy.ptl、
// 2155=FlameThrower.ptl；FlameThrower 对象 vt+112 回指自身，最后 vt+384 取出场参数面存 this+2156。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAD00(uint8_t *this)
{
  int pThis_16C; // eax
  int pThis_16C2; // eax
  int pThis_154; // eax
  int v5; // eax
  const char *v6; // edi
  int pThis_16C3; // eax
  int pThis_16C4; // eax
  int result; // eax

  *(this + 8608) = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C = sub_4C3640(this + 364, "Particle/EF_Fire.ptl", this);
    else
      pThis_16C = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Fire.ptl", this);
  }
  else
  {
    pThis_16C = 0;
  }
  *((uint32_t *)this + 2153) = pThis_16C;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C2 = sub_4C3640(this + 364, "Particle/EF_Hikari.ptl", this);
    else
      pThis_16C2 = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Hikari.ptl", this);
  }
  else
  {
    pThis_16C2 = 0;
  }
  *((uint32_t *)this + 2154) = pThis_16C2;
  pThis_154 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this) - 270;
  if ( pThis_154 != 0 )
  {
    v5 = pThis_154 - 2;
    if ( v5 == 0 )
    {
      v6 = "Particle/FCATADestroy.ptl";
      goto LABEL_17;
    }
    if ( v5 == 1 )
    {
      v6 = "Particle/LCATADestroy.ptl";
      goto LABEL_17;
    }
  }
  v6 = "Particle/CATADestroy.ptl";
LABEL_17:
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C3 = sub_4C3640(this + 364, v6, this);
    else
      pThis_16C3 = sub_4C3640(*((uint32_t *)this + 91), v6, this);
  }
  else
  {
    pThis_16C3 = 0;
  }
  *((uint32_t *)this + 2150) = pThis_16C3;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C4 = sub_4C3640(this + 364, "Particle/FlameThrower.ptl", this);
    else
      pThis_16C4 = sub_4C3640(*((uint32_t *)this + 91), "Particle/FlameThrower.ptl", this);
  }
  else
  {
    pThis_16C4 = 0;
  }
  *((uint32_t *)this + 2155) = pThis_16C4;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pThis_16C4 + 112))(pThis_16C4, this);
  result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  *((uint32_t *)this + 2156) = result;
  return result;
}



// 坠落破坏：引用 Particle/BATIDestroy.ptl
// ------------------------------------------------------------
// 0x5BAEF0 sub_5BAEF0 —— 载具·坠落破坏粒子装载（BATIDestroy）
// 装载 Particle/BATIDestroy.ptl 到 this+2150 并清 this+2152 AI 阈值——与 ·sub_5BAD00 同族（差异：单槽坠落型）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAEF0(uint32_t *this)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/BATIDestroy.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/BATIDestroy.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2150) = result;
  *(this + 2152) = 0;
  return result;
}



// 载具烟火：this[2153]/[2154] 两个粒子槽各播一次(自身 X±85 朝向偏移、高 +60)，
//   再在 X±75、高+55 处挂 Monster/Vehicle/Particle/ani/FireSmoke.ani 烟火对象
// ------------------------------------------------------------
// 0x5BAF80 sub_5BAF80 —— 载具·烟火特效双段（粒子 + FireSmoke.ani 挂装）
// 段 1：this+2153/2154 两粒子槽循环 2 次，按 vt+152 朝向在自身 X±85、Z+60 处 vt+40 定位、vt+92 打包挂层(2)。
// 段 2：sub_42FCB0(228) 分配 + sub_431860 装载 Monster/Vehicle/Particle/ani/FireSmoke.ani，sub_44B6C0(284) 造
// CNRDPooledObject 型对象（vtable 直写），sub_45FE80 以类型 2 挂到层链，vt+148 写朝向、vt+112 定位 X±75/Z+55。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAF80(uint32_t *this)
{
  int nCurX; // edi
  int nSmokeX; // edi
  int **pThis_869; // edi
  int pSlotVt; // ebx
  int nZ; // eax
  int nY60; // eax
  void *fld_e29; // ecx
  bool bLast; // zf
  int nCurX2; // edi
  int nFireX; // edi
  char *pPool; // eax
  char *pFxObj; // edi
  int pFxHost; // ecx
  int pFxVt; // ebx
  int nFaceDir; // eax
  int pFxVt2; // ebx
  int nZ2; // eax
  int nY55; // eax
  char v21[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v23; // [esp+14h] [ebp-20h]
  int v24; // [esp+18h] [ebp-1Ch]
  char *v25; // [esp+1Ch] [ebp-18h]
  int nLoopCnt; // [esp+20h] [ebp-14h]
  int nSmokeXSaved; // [esp+24h] [ebp-10h]
  int v28; // [esp+30h] [ebp-4h]

  nCurX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    nSmokeX = nCurX + 85;
  else
    nSmokeX = nCurX - 85;
  nSmokeXSaved = nSmokeX;
  pThis_869 = (int **)(this + 2153);
  nLoopCnt = 2;
  do
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_869 + 12))(*pThis_869, 0);
    pSlotVt = **pThis_869;
    nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    nY60 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ + 60);
    (*(void (/*thiscall*/ **)(int *, int, int))(pSlotVt + 40))(*pThis_869, nSmokeXSaved, nY60);
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_869 + 92))(*pThis_869, v21);
    fld_e29 = (void *)*(this + 29);
    v28 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v21);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++pThis_869;
    bLast = nLoopCnt == 1;
    Block = nullptr;
    v23 = 0;
    v24 = 0;
    --nLoopCnt;
  }
  while ( !bLast );
  nCurX2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    nFireX = nCurX2 + 75;
  else
    nFireX = nCurX2 - 75;
  nSmokeXSaved = nFireX;
  nLoopCnt = sub_42FCB0(228);
  v28 = 1;
  if ( nLoopCnt != 0 )
    nLoopCnt = sub_431860((char)"Monster/Vehicle/Particle/ani/FireSmoke.ani", 1);
  else
    nLoopCnt = 0;
  v28 = -1;
  pPool = (char *)sub_44B6C0(284);
  pFxObj = pPool;
  v25 = pPool;
  v28 = 2;
  if ( pPool != nullptr )
  {
    sub_44E0D0(pPool, nLoopCnt, 1);
    *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';
  }
  else
  {
    pFxObj = nullptr;
  }
  pFxHost = *(this + 29);
  v28 = -1;
  sub_45FE80(pFxHost, (int)pFxObj, 2, 0, (int)pFxObj, (int)this, 0);
  pFxVt = *(uint32_t *)pFxObj;
  nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(pFxVt + 148))(pFxObj, nFaceDir);
  pFxVt2 = *(uint32_t *)pFxObj;
  nZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  nY55 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ2 + 55);
  return (*(int (/*thiscall*/ **)(char *, int, int))(pFxVt2 + 112))(pFxObj, nSmokeXSaved, nY55);
}



// 武器开火播报：FLAMETHROWER_FIRE/LOOP + LASERCANNON_SHOOT（107L；火喷/激光二系）
// ------------------------------------------------------------
// 0x5BB130 sub_5BB130 —— 载具·武器开火分段总控（喷火/激光/龙炮四段）
// 先跑 ·sub_5BA980 移动循环；大状态 vt+840==8 时按段号 sub_41A5E0(this+7028) 分支：
// 段 0/1（龙炮）：子槽 vt+200→+148>=2 且 this+8608==0 → 目标门 vt+308 过则 ·sub_5BA2F0 发炮 + ·sub_5BAF80 烟火，
//   置 8608=1、vt+876 双轴 70、vt+152 取火花资源 sub_432E50 后 vt+896 挂装；
// 段 2（喷火）：子槽>=6 时首帧播 FLAMETHROWER_FIRE + FLAMETHROWER_LOOP(9)、置 8608；this+8620 火焰特效按朝向 X±80/Z+50/Y+1 定位并挂层；
// 段 3（激光）：子槽>=1 → ·sub_5BA4B0 武器码 30015 + LASERCANNON_SHOOT；段 4：子槽>=2 → ·sub_5BA4B0 30036 + 双帧 vt+208 + 播报。
// ------------------------------------------------------------
void /*usercall*/ sub_5BB130(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pVt; // edx
  int pVt2; // edi
  int hAniKind4; // eax
  int pSparkRes; // eax
  int pFlameFx; // edi
  int nDx; // ebx
  int pVt3; // edx
  void *pLayerList; // eax
  int nX; // [esp-14h] [ebp-34h]
  int nY1; // [esp-10h] [ebp-30h]
  int nZ50; // [esp-Ch] [ebp-2Ch]
  void *v15[7]; // [esp+4h] [ebp-1Ch] BYREF

  sub_5BA980((int *)pArg1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )
  {
    switch ( sub_41A5E0(pArg1 + 7028) )
    {
      case 0:
      case 1:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA2F0((uint32_t *)pArg1);
          sub_5BAF80((uint32_t *)pArg1);
          pVt = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8608) = 1;
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t))(pVt + 876))(pArg1, 0, 70, 70, 0);
          pVt2 = *(uint32_t *)pArg1;
          hAniKind4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);
          pSparkRes = sub_432E50(hAniKind4);
          (*(void (/*thiscall*/ **)(int, int))(pVt2 + 896))(pArg1, pSparkRes);
        }
        return;
      case 2:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) < 6 )
          goto LABEL_21;
        if ( *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "FLAMETHROWER_FIRE",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "FLAMETHROWER_LOOP",
            9,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;
LABEL_21:
          if ( *(uint8_t *)(pArg1 + 8608) == 0 )
            return;
        }
        pFlameFx = **(uint32_t **)(pArg1 + 8620);
        nZ50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 50;
        nY1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1) + 1;
        nDx = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 1 ? -80 : 80;
        nX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + nDx;
        (*(void (/*thiscall*/ **)(uint32_t))(pFlameFx + 40))(*(uint32_t *)(pArg1 + 8620));
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pArg1 + 8620) + 92))(*(uint32_t *)(pArg1 + 8620), v15);
        pVt3 = *(uint32_t *)pArg1;
        v15[6] = nullptr;
        pLayerList = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(pVt3 + 80))(pArg1, 2, 0, v15);
        sub_4600B0(pLayerList, nX, nY1, nZ50);
        sub_5E5260(v15);
        return;
      case 3:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 1 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA4B0((uint32_t *)pArg1, 1, nArg3, 30015);
          (*(void (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_SHOOT", -1);
          *(uint8_t *)(pArg1 + 8608) = 1;
        }
        return;
      case 4:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA4B0((uint32_t *)pArg1, nArg2, nArg3, 30036);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "LASERCANNON_SHOOT",
            -1,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;
        }
        return;
      default:
        return;
    }
  }
}



// AI 字段访问（this+8672）
// ------------------------------------------------------------
// 0x5BB420 sub_5BB420 —— 载具/飞艇·高度起点受理（vt+1308 覆写）
// 把当前高度基槽 this+2150 交给 this+81（高度提交槽），清布防字节 this+8672，this+2169=5（可控/存活计数【推断】），
// 尾调 vt+1308——与 ·sub_5BC210 的 AIRSHIP_UP 起降序列配套。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB420(uint32_t *this)
{
  int v1; // edx

  v1 = *this;
  *(this + 2150) = *(this + 81);
  *((uint8_t *)this + 8672) = 0;
  *(this + 2169) = 5;
  return (*(int (**)(void))(v1 + 1308))();
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB450 sub_5BB450 —— 飞艇·反应态决策机（行为字 this+1787 概率互转）
// 与 ·sub_5BA120 同构（差异：0→13、受击后置(4) 5% 转 5、死亡(5) 5% 转 4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB450(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
    case 4:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 5 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      return result;
    case 5:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      nRand2 = rand();
      v4 = nRand2 % 100;
      result = nRand2 / 100;
      if ( v4 < 5 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      return result;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      return result;
    default:
      return result;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB530 sub_5BB530 —— 飞艇·主镜像 vt+144/148 高度同步（this+1639 门）
// 取 vt+184 槽，若主状态镜像2 this+1639 为 0 或 15 且 vt+184!=4，则经 vt+148/vt+144 写回同值——
// 与 ·sub_5BB570 升降门（this+2151）协同。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB530(int *this)
{
  int v2; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  result = *(this + 1639);
  if ( (result == 0 || result == 15) && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// 航行循环：AIRSHIP_01_LOOP 播报（this+200/8672 相位）
// ------------------------------------------------------------
// 0x5BB570 sub_5BB570 —— 飞艇·航行循环（AIRSHIP_01_LOOP）
// 前置 ·sub_4E1780 基类移动。大状态 vt+840：==14（蓄力架招）且主状态子槽 vt+200→+170 非 0 且目标门 vt+308 过 → vt+560 setState(15) 施放；
// ==15 施放 → vt+1316 收手。大状态==0：升降门 this+2151==1 且当前高度 vt+128 >= this+2150 时清门并按
// vt+124/vt+120/vt+112 更新自身定位（上升到位）。双轴 vt+184/188 均 4 且 8672 置位时停熄(9)、清 8672；
// 否则 8672==0 播 AIRSHIP_01_LOOP(9) 置位。最后 this+28 层链条件（本层 +36==0 且 +24!=0）触发 ·sub_494F20 悬浮音效(2)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BB570(int *this)
{
  int v2; // eax
  int v3; // eax
  int fld_e2150; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int fld_e28; // ecx

  sub_4E1780(this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( v2 != 0 )
  {
    v3 = v2 - 14;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        (*(void (/*thiscall*/ **)(int *))(*this + 1316))(this);
    }
    else if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0
           && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);
    }
  }
  else
  {
    if ( *(this + 2151) == 1 )
    {
      fld_e2150 = *(this + 2150);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) >= fld_e2150 )
      {
        v5 = *this;
        *(this + 2151) = 0;
        v6 = (*(int (/*thiscall*/ **)(int *, int))(v5 + 124))(this, fld_e2150);
        v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
        (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(this, v7);
      }
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4
      && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )
    {
      if ( *((uint8_t *)this + 8672) == 1 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
        *((uint8_t *)this + 8672) = 0;
      }
    }
    else if ( *((uint8_t *)this + 8672) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "AIRSHIP_01_LOOP", 9, 0, 0);
      *((uint8_t *)this + 8672) = 1;
    }
    fld_e28 = *(this + 28);
    if ( *(uint32_t *)(fld_e28 + 36) == 0 && *(float *)(fld_e28 + 24) != 0.0 )
      sub_494F20(2, 0.0);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB6B0 sub_5BB6B0 —— 飞艇·俯冲/架招触发（距离门 + 3.3% 概率）
// 目标门 vt+308 过、大状态==0、目标 this+1813 非空、自身高度 vt+128 >= this+2150 时：
// 与目标 Z 差 abs(vt+124 − 目标 vt+124) < 30，且 X 同侧 200 像素内（|dx|<200 双向判定）时，
// rand()%300<50（约 16.7%【推算】）经 vt+560 setState(14) 进蓄力架招——与 ·sub_5BB570 的 14→15 衔接。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB6B0(int *this)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi
  int pObj; // edi
  int v6; // ebx
  int v7; // edi
  int v8; // edi
  int nRand; // eax
  int v10; // et2

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 0 )
    {
      result = *(this + 1813);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        if ( result >= *(this + 2150) )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
          result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e1813);
          if ( result < 30 )
          {
            if ( (fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e18132)
              && (pObj = *(this + 1813),
                  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this),
                  (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - v6 < 200)
              || (v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) >= v7)
              && (v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v8) < 200) )
            {
              nRand = rand();
              v10 = nRand % 300;
              result = nRand / 300;
              if ( v10 < 50 )
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
            }
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（97L）
// ------------------------------------------------------------
// 0x5BB7C0 sub_5BB7C0 —— 飞艇·瞬移/召唤跳转（10/300 概率 + 全局台数门）
// 大状态==0、this+2169（可控计数）>0、目标非空、目标门 vt+308 过且全局 ·dword_9A05D4 < 5（场上飞艇台数上限门【推断】）时，
// rand()%300<10（3.3%）：奇偶分支——随机 X 目标（vt+672 取控制3）经 vt+152 位置查询取 Z 基准；
// 偶数分支随机参数（100..299/50..149/40..99 与朝向 2/3 二选）写入 3 个半字参数 aTeleParam 后同法取点，
// 再 vt+376 解目的地 X、vt+592 处位移到 260、最后 vt+560 setState(17) 绑定/瞬移收尾。
// ------------------------------------------------------------
int /*usercall*/ sub_5BB7C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int nRand; // eax
  int v6; // et2
  bool v7; // zf
  signed int nRand2; // eax
  int nRand5; // eax
  int pVt; // edi
  uint32_t *pCtrl3; // ebx
  int nFindRes; // eax
  int nZBase; // eax
  int nZBase2; // eax
  int nY; // eax
  int nX; // eax
  int nDest; // eax
  uint16_t aTeleParam[3]; // [esp+4h] [ebp-8h] BYREF
  bool bDirLeft; // [esp+Ah] [ebp-2h]
  char bDirType; // [esp+Bh] [ebp-1h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
  if ( result == 0 )
  {
    result = pArg1[2169];
    if ( result > 0 )
    {
      result = pArg1[1813];
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
        if ( (uint8_t)result != 0 && dword_9A05D4 < 5 )
        {
          nRand = rand();
          v6 = nRand % 300;
          result = nRand / 300;
          if ( v6 < 10 )
          {
            nRand2 = rand() & 0x80000001;
            v7 = nRand2 == 0;
            if ( nRand2 < 0 )
              v7 = (((uint8_t)nRand2 - 1) | 0xFFFFFFFE) == -1;
            if ( v7 )
            {
              pVt = *pArg1;
              pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 672))(pArg1, 3, nArg3, nArg2);
              nZBase2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(
                      pArg1,
                      0,
                      0,
                      0,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              nZBase = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, nZBase2);
            }
            else
            {
              aTeleParam[0] = rand() % 200 + 100;
              aTeleParam[1] = rand() % 100 + 50;
              bDirLeft = rand() % 2 == 0;
              bDirType = 3 - (rand() % 2 != 0);
              nRand5 = rand();
              pVt = *pArg1;
              aTeleParam[2] = nRand5 % 60 + 40;
              pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(pVt + 672))(pArg1, 3, nArg3, nArg2);
              nFindRes = (*(int (/*thiscall*/ **)(uint32_t *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(
                      pArg1,
                      1,
                      aTeleParam,
                      8,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              nZBase = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, nFindRes) + 10;
            }
            nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZBase);
            nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY);
            nDest = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *pCtrl3, nX);
            (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt + 592))(pArg1, 260, nDest);
            return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 17, 0, 0, 0);
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB970 sub_5BB970 —— 世界包提交·飞艇爆裂（dword_8F8520 包对象）
// 目标门 vt+308 过后 25% 概率（rand()%100<25）构造世界事件包：包 vt[2](29,2,nArg2) 命令头，
// 依次 vt+36 追加自身标识 vt+48、vt+52、全局 ·dword_8F7C04 的 vt+52，再追加常量 14 与两个 rand()%2 随机参，
// 最后包 vt+60(1,-1) 提交——dword_8F8520 为全局事件/网络包单例【推断】。
// ------------------------------------------------------------
int /*usercall*/ sub_5BB970@<eax>(int nArg1@<ecx>, int nArg2@<edi>)
{
  int result; // eax
  int nRand; // eax
  int v5; // et2
  int pPktVt; // edi
  int nVal1; // eax
  int pPktVt2; // edi
  int nVal2; // eax
  int pPktVt3; // esi
  int nVal3; // eax
  int nRand2; // esi
  int nRand3; // edi

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v5 = nRand % 100;
    result = nRand / 100;
    if ( v5 < 25 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);
      pPktVt = *(uint32_t *)dword_8F8520;
      nVal1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);
      (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nVal1);
      pPktVt2 = *(uint32_t *)dword_8F8520;
      nVal2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);
      (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nVal2);
      pPktVt3 = *(uint32_t *)dword_8F8520;
      nVal3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      (*(void (/*thiscall*/ **)(int, int))(pPktVt3 + 36))(dword_8F8520, nVal3);
      nRand2 = rand() % 2;
      nRand3 = rand() % 2;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand3);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BBA60 sub_5BBA60 —— 关卡/交互事件包处理（sub_4DC630 取参）
// ·sub_4DC630 取事件包编号 v3：==14 时经全局 ·dword_8F8520 包对象 vt+72 取两参 v9/v8，
// 按 v9 经 vt+876 双轴给 60/60/−12 参数、vt+888 播 1000；v9==0 → vt+896 挂 v6(v8) 表（0/1），
// 否则 vt+896 挂 v7(v8) 表（2/3）并返回 14——事件包驱动的姿态/贴图切换【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBA60(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  uint32_t v6[2]; // [esp+8h] [ebp-14h]
  uint32_t v7[2]; // [esp+10h] [ebp-Ch]
  uint8_t v8; // [esp+1Ah] [ebp-2h] BYREF
  uint8_t v9; // [esp+1Bh] [ebp-1h] BYREF

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )
    {
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v9);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v8);
      v4 = *this;
      v6[0] = 0;
      v6[1] = 1;
      v7[0] = 2;
      v7[1] = 3;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(v4 + 876))(this, v9, 60, 60, 0, -12, 1);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      v5 = *this;
      if ( v9 == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v5 + 896))(this, v6[v8], 4);
        return 14;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t))(v5 + 896))(this, 4, v7[v8]);
    }
    return v3;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BBB30 sub_5BBB30 —— 定时器槽 this+2151 空则转发默认（·sub_4DA1D0）
// this+2151 定时器槽为 0 时转 ·sub_4DA1D0（默认行为），否则直接返回槽值——AI 定时门控件【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB30(int *this)
{
  int result; // eax

  result = *(this + 2151);
  if ( result == 0 )
    return sub_4DA1D0();
  return result;
}



// 子弹技能：引用 Particle/Bullet.ptl
// ------------------------------------------------------------
// 0x5BBB40 sub_5BBB40 —— 飞艇·双管子弹齐射（Particle/Bullet.ptl）
// vt+588 取 Bullet.ptl 模板 qmemcpy 0x62 字节到栈包，X 偏移 nArg2（-1 不加）；
// vt+580 发两发 30018：Y+65/−44 与 Y+72/−37（右侧管 Z+10）；末两发 ·sub_4926A0 复位帧游标(this+2179/2180 双管)。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB40(int *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  uint32_t v7[26]; // [esp+Ch] [ebp-68h] BYREF

  v7[25] = dword_796E50;
  qmemcpy(
    v7,
    (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bullet.ptl"),
    0x62u);
  if ( nArg2 != -1 )
    v7[19] += nArg2;
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30018,
    0,
    v7,
    0,
    pArg3 + 65,
    10,
    -44,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30018,
    0,
    v7,
    0,
    pArg3 + 72,
    -10,
    -37,
    4,
    0,
    0,
    0);
  sub_4926A0(*(this + 2179));
  return sub_4926A0(*(this + 2180));
}



// 炸弹技能：引用 Particle/Bomb.ptl
// ------------------------------------------------------------
// 0x5BBC00 sub_5BBC00 —— 飞艇·三发炸弹投放（Particle/Bomb.ptl）
// vt+588 取 Bomb.ptl 模板复制 0x62 字节，vt+580 以 30019 发三发——X+55、X0、X−55（三垂直投放点【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBC00(int *this)
{
  const void *v2; // eax
  int v3; // edx
  uint8_t v5[100]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v2 = (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bomb.ptl");
  v3 = *this;
  qmemcpy(v5, v2, 0x62u);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v3 + 580))(
    this,
    30019,
    0,
    v5,
    0,
    55,
    0,
    0,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30019,
    0,
    v5,
    0,
    0,
    0,
    0,
    4,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
           this,
           30019,
           0,
           v5,
           0,
           -55,
           0,
           0,
           4,
           0,
           0,
           0);
}



// 空袭：AIRSHIP_SHOOT 播报（92L）
// ------------------------------------------------------------
// 0x5BC100 sub_5BC100 —— 飞艇·空袭循环（AIRSHIP_SHOOT）
// 先跑 ·sub_5BB570 航行循环；大状态 vt+840==8（攻击）时按武器档 sub_41A5E0(this+1757)：
// ==1 档 → this+2173 未开火 且 子槽 vt+2175→+148==1：首个门过（vt+308）时按 this+2171 计数在 1..19 摆动（超过 10 取 20−x）
//   经 vt+1324 给 −9×摆动 的扫射偏移，计数自增；计满 this+2172 后 setState 0 结束射击并播 AIRSHIP_SHOOT；
//   射击结束（子槽!=1）清 2173 复位；
// ==0 档（无武器）同样结构、vt+1324 传 −1，其余同。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC100(int *this)
{
  int v1; // eax
  int fld_e21714; // eax
  int v3; // eax
  int fld_e2171; // ecx
  int fld_e21712; // eax
  int fld_e21713; // eax
  int result; // eax

  sub_5BB570(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result != 1 )
        return result;
      result = *(this + 2173);
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )
      {
        v3 = *this;
        *(this + 2173) = 1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v3 + 308))(this) != 0 )
        {
          fld_e2171 = *(this + 2171);
          if ( fld_e2171 <= 10 )
            fld_e21712 = *(this + 2171);
          else
            fld_e21712 = 20 - fld_e2171;
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t))(*this + 1324))(
            this,
            *(this + 2174),
            -9 * fld_e21712,
            0,
            0);
        }
        fld_e21713 = *(this + 2171);
        *(this + 2171) = fld_e21713 + 1;
        if ( fld_e21713 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "AIRSHIP_SHOOT",
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )
      {
        result = *(this + 2175);
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;
      }
    }
    else
    {
      result = *(this + 2173);
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )
      {
        v1 = *this;
        *(this + 2173) = 1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v1 + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 1324))(this, -1, 0, 0, 0);
        fld_e21714 = *(this + 2171);
        *(this + 2171) = fld_e21714 + 1;
        if ( fld_e21714 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "AIRSHIP_SHOOT",
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )
      {
        result = *(this + 2175);
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BC150 sub_5BC150 —— 飞艇·回收/复位（帧复位 + 朝向 + 清整层）
// this+1554 对象 +16 帧复位(vt+196 写、·sub_4926A0 清)；vt+876 双轴两次全参清零；按目标 X 比较经 vt+148 写朝向；
// vt+344 应用自身档位；随后遍历 this+1905..1906 向量（元素 32 字节）逐项首字节置 0（清整层挂件）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC150(uint32_t *this)
{
  int v2; // edi
  int fld_e1813; // ebx
  int v4; // eax
  unsigned int result; // eax
  unsigned int v6; // ecx
  int i; // edx
  int fld_e1905; // edi

  sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v2 = *this;
  fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(v2 + 148))(this, v4 < fld_e1813);
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
  v6 = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
      break;
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( v6 >= result )
      break;
    result = i + fld_e1905;
    ++v6;
    *(uint8_t *)(i + fld_e1905) = 0;
  }
  return result;
}



// 上升播报：AIRSHIP_UP（this+208 相位）
// ------------------------------------------------------------
// 0x5BC210 sub_5BC210 —— 飞艇·升空（AIRSHIP_UP）
// 高度槽 this+81 ← this+2150（当前高度基准），升降门 this+2151=1；this+1554 表 +24/+28 两帧经 vt+208 写帧；
// sub_49C5F0(10,0,0,1000) 生效，末经 ·sub_432EA0 播 AIRSHIP_UP——与 ·sub_5BB570 的 2151 上升到位门配套。
// ------------------------------------------------------------
void */*thiscall*/ sub_5BC210(uint32_t *this)
{
  int v2; // edx
  int fld_e1554; // eax

  v2 = *this;
  *(this + 81) = *(this + 2150);
  fld_e1554 = *(this + 1554);
  *(this + 2151) = 1;
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 208))(*(uint32_t *)(fld_e1554 + 24));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));
  sub_49C5F0(10, 0, 0, 1000);
  return sub_432EA0("AIRSHIP_UP", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BC280 sub_5BC280 —— 事件包号 10·整层置位（·sub_4D90A0 前置）
// 先调 ·sub_4D90A0(uArg2) 校验/转发事件包；包号 *uArg2==10 时遍历 this+1905..1906 向量（元素 32 字节）
// 逐项首字节置 1（与 ·sub_5BC150 的清 0 对偶）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC280(uint32_t *this, uint32_t *uArg2)
{
  unsigned int result; // eax
  unsigned int v4; // edx
  int i; // edi
  int fld_e1905; // ecx

  result = sub_4D90A0(uArg2);
  if ( *uArg2 == 10 )
  {
    v4 = 0;
    for ( i = 0; ; i += 32 )
    {
      fld_e1905 = *(this + 1905);
      if ( fld_e1905 == 0 )
        break;
      result = (*(this + 1906) - fld_e1905) >> 5;
      if ( v4 >= result )
        break;
      result = i + fld_e1905;
      ++v4;
      *(uint8_t *)(i + fld_e1905) = 1;
    }
  }
  return result;
}



// 卸载/下降：AIRSHIP_UNLOAD + AIRSHIP_DOWN 播报（84L；this+8608 相位）
// ------------------------------------------------------------
// 0x5BC2D0 sub_5BC2D0 —— 飞艇·卸载/下降状态机（AIRSHIP_UNLOAD/DOWN）
// ArgList==17（绑定态）→ 播 AIRSHIP_UNLOAD 且可控计数 this+2169 自减；其他时大状态==15 施放且 ArgList!=16 先经 ·sub_5BC210 升空复位、再走基类 ·sub_4E33D0 收尾。
// ArgList==14（蓄力架招）：有目标 → ·sub_5BC150 回收复位；无目标 → vt+472 定时器(0,0,1,1)。
// ArgList==15（施放）：高度槽切 this+2153 基准、升降门 2151=−1，fld_e81=基准−当前高度(vt+128)，
// ·sub_495890(0,3000) 与 ·sub_4A0550/·sub_4A0600(2) 音效/屏幕，this+1554 表 +20 帧复位(vt+196 写、·sub_4926A0) 后 vt+876 双轴两次清零，清 this+8608 并播 AIRSHIP_DOWN。
// ArgList==16 → ·sub_5BC210 升空 + vt+472 定时器(0,0,1,1)。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC2D0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  unsigned int result; // eax
  int v7; // edx
  int fld_e81; // edi
  int v9; // edx

  if ( ArgList == 17 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "AIRSHIP_UNLOAD",
      -1,
      0,
      0);
    result = *(this + 2169) - 1;
    *(this + 2169) = result;
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 15 && ArgList != 16 )
      sub_5BC210(this);
    sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
    if ( ArgList == 14 )
    {
      if ( *(this + 1813) != 0 )
        return sub_5BC150(this);
      else
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
    }
    else if ( ArgList == 15 )
    {
      v7 = *this;
      *(this + 81) = *(this + 2153);
      *(this + 2151) = -1;
      fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this);
      sub_495890(0, 3000);
      sub_4A0550(fld_e81);
      sub_4A0600(2);
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v9 = *this;
      *((uint8_t *)this + 8608) = 0;
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(
               this,
               "AIRSHIP_DOWN",
               -1,
               0,
               0);
    }
    else
    {
      result = ArgList - 16;
      if ( ArgList == 16 )
      {
        sub_5BC210(this);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
      }
    }
  }
  return result;
}



// 硬直字段（this+204/+208）
// ------------------------------------------------------------
// 0x5BC460 sub_5BC460 —— 飞艇·四槽帧复位与重建（this+2175..2180）
// 对 this+2177/2175/2178/2176 四帧对象逐个 ·sub_4926A0 帧游标复位后经 vt+208 重写；
// nArg2!=-1 时再经 vt+204 两次写帧（this+1554 表 +4*nArg2 与 +4*nArg2+8，100/25/5 与 −100/32/−3 参数对）——
// 与 ·sub_5BC720 的双管帧初始化同源。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC460(int *this, int nArg2)
{
  int result; // eax

  sub_4926A0(*(this + 2177));
  sub_4926A0(*(this + 2175));
  sub_4926A0(*(this + 2178));
  sub_4926A0(*(this + 2176));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2177));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2175));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2178));
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2176));
  if ( nArg2 != -1 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 4 * nArg2),
      25,
      5,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
             this,
             -100,
             *(uint32_t *)(*(this + 1554) + 4 * nArg2 + 8),
             32,
             -3,
             0,
             0);
  }
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5BC530 sub_5BC530 —— 飞艇·攻击态武器档分支（时钟门 + 撒弹）
// 大状态 vt+840==8（攻击）时 vt+1328(this,0) 停表；转发 ·sub_5BC2D0 基类状态机。
// ArgList==5（死亡）→ vt+1328(this,−1) 复表。ArgList==8（攻击）按武器档 sub_41A5E0(this+1757)：
// 0/1 档 → 记时钟 ·sub_699000(this+9)、vt+1328 起表、this+2172=20/2171=2173=0 初始化后 ·sub_5BB970 提交爆裂；
// 2 档 → 目标门 vt+308 过后 ·sub_5BBC00 三连炸弹投放 + setState 0 结束。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC530(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
  result = sub_5BC2D0(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 1328))(this, -1);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result >= 0 )
    {
      if ( result <= 1 )
      {
        *(this + 2170) = sub_699000((int)(this + 9));
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1328))(this, 1);
        *(this + 2172) = 20;
        *(this + 2171) = 0;
        *(this + 2173) = 0;
        return sub_5BB970((int)this, 8);
      }
      else if ( result == 2 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
        {
          sub_5BBC00(this);
          return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        }
      }
    }
  }
  return result;
}



// 时钟门 AI（this+204/8608 相位）
// ------------------------------------------------------------
// 0x5BC620 sub_5BC620 —— 飞艇·下沉到位序列（高度阈 + 时钟门 1500）
// 当前高度 vt+128 <= this+2153 且 this+8608==0 时：按 vt+124/vt+120/vt+112 链式定位（落点），
// this+1554 表 +24/+28 两帧复位(vt+196)后 vt+204 打 ±500 两帧、·sub_424120(层,2,300) 屏幕振动；
// 随后 ·sub_699000(this+1640) 计时 >1500 且目标门过 → vt+560 setState(16)（卸载/复位态）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC620(int *this)
{
  int fld_e2153; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int *fld_e1554; // eax
  int v7; // eax
  int result; // eax

  fld_e2153 = *(this + 2153);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= fld_e2153 && *((uint8_t *)this + 8608) == 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, fld_e2153);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);
    fld_e1554 = (int *)(*(this + 1554) + 24);
    *((uint8_t *)this + 8608) = 1;
    sub_4926A0(*fld_e1554);
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 28));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      -500,
      *(uint32_t *)(*(this + 1554) + 24),
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      500,
      *(uint32_t *)(*(this + 1554) + 28),
      0,
      0,
      0,
      0);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    sub_424120(*(uint32_t **)(v7 + 132), 2, 300);
  }
  result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
  if ( result > 1500 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);
  }
  return result;
}



// 飞艇破坏语音：Particle/ZepplinEXDestroyFly/Drop.ptl 引用 + sub_4015C0（54L）
// ------------------------------------------------------------
// 0x5BC720 sub_5BC720 —— 飞艇EX·破坏收尾（帧序 + ZepplinEX 破坏粒子 + 引爆）
// this+1554 表取四帧对象存 2175/2177/2176/2178；表 [8]/[9] 两帧对象存 2179/2180 并按
// 元素 88 字节算法取帧尾索引 sub_493400(帧数组应用帧索引)【推断：帧步长 88】；
// vt+204 两次写帧（100/25/5 与 −100/32/−3）；vt+1328(this,0) 停表，2173=0、2151=0、2153=30（高度阈降为 30）；
// 末经 ·sub_4015C0 把 Particle/ZepplinEXDestroyFly.ptl(Fly 0x20) 与 ZepplinEXDestroyDrop.ptl(Drop 0x21) 写串。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC720(int *this)
{
  int *fld_e1554; // eax
  int v3; // ecx
  int v4; // eax
  int fld_e2180; // ecx
  int v6; // eax

  fld_e1554 = (int *)*(this + 1554);
  *(this + 2175) = fld_e1554[1];
  *(this + 2177) = *fld_e1554;
  *(this + 2176) = fld_e1554[3];
  *(this + 2178) = fld_e1554[2];
  v3 = fld_e1554[8];
  *(this + 2179) = v3;
  *(this + 2180) = fld_e1554[9];
  v4 = *(uint32_t *)(v3 + 44);
  if ( v4 != 0 )
    v4 = (*(uint32_t *)(v3 + 48) - v4) / 88;
  sub_493400(v3, v4 - 1);
  fld_e2180 = *(this + 2180);
  v6 = *(uint32_t *)(fld_e2180 + 44);
  if ( v6 != 0 )
    v6 = (*(uint32_t *)(fld_e2180 + 48) - v6) / 88;
  sub_493400(fld_e2180, v6 - 1);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(this + 2179),
    25,
    5,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(this + 2180),
    32,
    -3,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
  *(this + 2173) = 0;
  *(this + 2151) = 0;
  *(this + 2153) = 30;
  sub_4015C0("Particle/ZepplinEXDestroyFly.ptl", 0x20u);  // 【std::string构造赋值】
  return sub_4015C0("Particle/ZepplinEXDestroyDrop.ptl", 0x21u);  // 【std::string构造赋值】
}



// 飞艇破坏 2：Particle/ZepplinDestroyFly/Drop.ptl（空中/坠落两段）
// ------------------------------------------------------------
// 0x5BC840 sub_5BC840 —— 飞艇·破坏粒子槽初始化（Zepplin 双串 0x1E/0x1F）
// this+2153=1（高度阈置 1），经 ·sub_4015C0 写 Particle/ZepplinDestroyFly.ptl(0x1E) 与 ZepplinDestroyDrop.ptl(0x1F)——
// 与 ·sub_5BC720 同族（差异：非 EX 版资源与高度阈 1）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC840(uint32_t *this)
{
  *(this + 2153) = 1;
  sub_4015C0("Particle/ZepplinDestroyFly.ptl", 0x1Eu);  // 【std::string构造赋值】
  return sub_4015C0("Particle/ZepplinDestroyDrop.ptl", 0x1Fu);  // 【std::string构造赋值】
}



// 破损播报：AIRSHIP_BREAK（108L）
// ------------------------------------------------------------
// 0x5BC880 sub_5BC880 —— 飞艇·破损爆裂（AIRSHIP_BREAK；this==消亡对象时）
// 前置 ·sub_4D9170 消亡通知；当 uArg3==pArg1（自身消亡）时按 this+2155/2162 两个 std::string 资源名
// 各 new(0x12Cu) → ·sub_4C3640 生成粒子对象：vt[3] 复位、vt+40 按自身 X（vt+120/124/128 链取 Z+50）定位、
// vt+92 打包经 ·sub_4E77D0 转包装后由 sub_4600B0 挂层(2)；两段播完经 vt+212 播 AIRSHIP_BREAK 并 vt+216 停熄(9)。
// ------------------------------------------------------------
void /*userpurge*/ sub_5BC880(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)
{
  uint32_t *pszName1; // ecx
  int *pPtl1; // edi
  int pPtl1Vt; // eax
  int pPtl1Vt2; // ebx
  int nZ; // eax
  int nY50; // eax
  int nX; // eax
  int nPackRet1; // eax
  uint32_t *pszName2; // ecx
  int *pPtl2; // edi
  int pPtl2Vt; // eax
  int pPtl2Vt2; // ebx
  int nZ2; // eax
  int nY50b; // eax
  int nX2; // eax
  int nPackRet2; // eax
  uint8_t v20[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  uint8_t v22[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *v23; // [esp+1Ch] [ebp-18h]
  int v24; // [esp+20h] [ebp-14h]
  int v25; // [esp+24h] [ebp-10h]
  int v26; // [esp+30h] [ebp-4h]
  void *pMem; // [esp+3Ch] [ebp+8h]

  sub_4D9170(uArg3);
  if ( uArg3 == pArg1 )
  {
    v23 = nullptr;
    v24 = 0;
    v25 = 0;
    v26 = 1;
    if ( operator new(0x12Cu) != nullptr )
    {
      if ( pArg1[2160] < 0x10u )
        pszName1 = pArg1 + 2155;
      else
        pszName1 = (uint32_t *)pArg1[2155];
      if ( pArg1[96] < 0x10u )
        pPtl1 = (int *)sub_4C3640(pArg1 + 91, pszName1, pArg1);
      else
        pPtl1 = (int *)sub_4C3640(pArg1[91], pszName1, pArg1);
    }
    else
    {
      pPtl1 = nullptr;
    }
    pPtl1Vt = *pPtl1;
    LOBYTE(v26) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(pPtl1Vt + 12))(pPtl1, 0, nArg2);
    pPtl1Vt2 = *pPtl1;
    nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    nY50 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZ + 50);
    nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY50);
    (*(void (/*thiscall*/ **)(int *, int))(pPtl1Vt2 + 40))(pPtl1, nX);
    nPackRet1 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*pPtl1 + 92))(pPtl1, v20);
    LOBYTE(v26) = 2;
    sub_4E77D0((int)v22, nPackRet1);
    LOBYTE(v26) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)v22);
    pMem = operator new(0x12Cu);
    LOBYTE(v26) = 3;
    if ( pMem != nullptr )
    {
      if ( pArg1[2167] < 0x10u )
        pszName2 = pArg1 + 2162;
      else
        pszName2 = (uint32_t *)pArg1[2162];
      if ( pArg1[96] < 0x10u )
        pPtl2 = (int *)sub_4C3640(pArg1 + 91, pszName2, pArg1);
      else
        pPtl2 = (int *)sub_4C3640(pArg1[91], pszName2, pArg1);
    }
    else
    {
      pPtl2 = nullptr;
    }
    pPtl2Vt = *pPtl2;
    LOBYTE(v26) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(pPtl2Vt + 12))(pPtl2, 0);
    pPtl2Vt2 = *pPtl2;
    nZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    nY50b = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZ2 + 50);
    nX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY50b);
    (*(void (/*thiscall*/ **)(int *, int))(pPtl2Vt2 + 40))(pPtl2, nX2);
    nPackRet2 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*pPtl2 + 92))(pPtl2, v20);
    LOBYTE(v26) = 4;
    sub_4E77D0((int)v22, nPackRet2);
    LOBYTE(v26) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)v22);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "AIRSHIP_BREAK", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 216))(pArg1, 9);
    if ( v23 != nullptr )
      j__free(v23);
  }
}



// ============================================================
// 【分区 8】僵尸撕咬变体与字段群（0x5BCAB0-0x5BD1B0）
// 证据：ZOMBIE_BITE 撕咬（0x5BCAB0 101L）、HOLD 蓄力（0x5BCFE0）

// 撕咬 AI（僵尸变体）：ZOMBIE_BITE 播报（101L）
// ------------------------------------------------------------
// 0x5BCAB0 sub_5BCAB0 —— 僵尸变体·撕咬循环（ZOMBIE_BITE）
// 前置 ·sub_4E1780 基类移动。大状态 vt+840==15（施放）且控制器字节 this[30]+170 非 0 → setState 0 收。
// ==14（蓄力架招）：受害者槽 this[2157] 非空且其大状态==9（特殊/绑定）时——控制器字节非 0 且目标门 vt+308 过则
// vt+1312 取参(&v20,&v21,pBuf) 后 ·sub_4E5F70 硬直率掷（1,1 模板）、播 ZOMBIE_BITE；随后对受害者 vt+604(0)/vt+612(1,1) 放生重挂，
// 按受害者 Z(vt+128)−1 与自身朝向 vt+152 经 sub_432E50 反写其 X(vt+120)/朝向(vt+148) 吸附；受害者大状态非 5 且目标门过则反被 vt+560 setState(9,...,2)+vt+564。
// 受害者空 → setState 0；控制器字节非 0 → setState 15；受害者 vt+684 档经 sub_41A5E0 <=0 → setState 15。
// ------------------------------------------------------------
int /*usercall*/ sub_5BCAB0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int nStateM14; // eax
  int result; // eax
  int pVictim; // eax
  int pVt; // eax
  int pVictimVt; // ebx
  int pVictim2; // edi
  int nVicZ; // eax
  int nY; // eax
  int nXBite; // eax
  int pVictimVt2; // edi
  int nFaceDir; // eax
  int pSparkRes; // eax
  int pVictimVt3; // edi
  int nFaceDir2; // eax
  int pSparkRes2; // eax
  unsigned int nCtrl684; // eax
  int v20; // [esp+4h] [ebp-18h] BYREF
  int v21; // [esp+8h] [ebp-14h] BYREF
  uint32_t pBuf[4]; // [esp+Ch] [ebp-10h] BYREF

  sub_4E1780(pArg1);
  nStateM14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) - 14;
  if ( nStateM14 != 0 )
  {
    result = nStateM14 - 1;
    if ( result == 0 )
    {
      result = *(uint8_t *)(pArg1[30] + 170);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
    }
  }
  else
  {
    pVictim = pArg1[2157];
    if ( pVictim != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 840))(pVictim) == 9 )
      {
        if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg3) != 0 )
          {
            pVt = *pArg1;
            v20 = 0;
            v21 = 0;
            memset(pBuf, 0, sizeof(pBuf));
            (*(void (/*thiscall*/ **)(uint32_t *, int *, int *, uint32_t *))(pVt + 1312))(pArg1, &v20, &v21, pBuf);
            sub_4E5F70(nArg2, (int)pArg1, pArg1[2157], (float *)&v20, 1, 1);
          }
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "ZOMBIE_BITE", -1, 0);
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 604))(pArg1[2157], 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 1, 1);
        pVictimVt = *(uint32_t *)pArg1[2157];
        pVictim2 = pArg1[2157];
        nVicZ = (*(int (**)(void))(pVictimVt + 128))();
        nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nVicZ);
        nXBite = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 120))(pVictim2, nY - 1);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt + 112))(pArg1[2157], nXBite);
        pVictimVt2 = *(uint32_t *)pArg1[2157];
        nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
        pSparkRes = sub_432E50(nFaceDir);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt2 + 148))(pArg1[2157], pSparkRes);
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 840))(pArg1[2157]) != 5
             && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )
      {
        pVictimVt3 = *(uint32_t *)pArg1[2157];
        nFaceDir2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
        pSparkRes2 = sub_432E50(nFaceDir2);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt3 + 144))(pArg1[2157], pSparkRes2);
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 9, 0, 2, 0);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
    }
    if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
    result = pArg1[2157];
    if ( result != 0 )
    {
      nCtrl684 = (*(int (**)(void))(*(uint32_t *)result + 684))();
      result = sub_41A5E0(nCtrl684);
      if ( result <= 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BCCF0 sub_5BCCF0 —— 僵尸变体·受击包重写（vt+1308 转发 + 反击判定）
// 先把自己 vt+1308(nArg2,nArg3,nArg4) 原逻辑走一遍，再尾调 ·sub_4DB480 反击/架招触发判定——
// 撕咬变体的受击观察者钩子【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCCF0(void *this, int nArg2, int nArg3, int nArg4)
{
  (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 1308))(this, nArg2, nArg3, nArg4);
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// 僵尸·撕咬口解算（114L）：对 this[2157](被咬住的角色)先验标记 273 且 RTTI cast 为
//   IRDCharacter，再按其 vt+1032 姿态档解算撕咬口坐标写出 pArg2/3/4(X/Y/Z)——
//   站立(1) X±52/Z+5、倒地(2) X±44/Z+32、爬起(3) X±40/Z+2、其他(4) X±34/Z+12，
//   朝向按自身 vt+152 翻转；无标记时 Z=受害者Z-自身宽+受害者宽
// ------------------------------------------------------------
// 0x5BCD30 sub_5BCD30 —— 僵尸·撕咬口解算（受害者姿态分型取点）
// 判据链：受害者 this[2157] vt+40 标记 273 → __RTDynamicCast 转 IRDCharacter 取 vt+1032 姿态档
// （1/站立 X±52 Z+5、2/倒地 X±44 Z+32、3/爬起 X±40 Z+2、空闲 X±34 Z+12，朝向按自身 vt+152 翻正）；
// 无 273 标记兜底：Z = 受害者 Z − 自身宽(vt+192) + 受害者宽(vt+192)。输出写入 pArg2/3/4。
// ------------------------------------------------------------
float */*thiscall*/ sub_5BCD30(int *this, float *pArg2, float *pArg3, float *pArg4)
{
  char fld_e2157; // al
  int fld_e21572; // ecx
  int pVictimChar; // eax
  float *result; // eax
  int nFaceDir1; // eax
  int fld_e21573; // ecx
  int nBiteX1; // eax
  double fld_e21574; // st7
  int nFaceDir4; // eax
  int fld_e21579; // ecx
  int nBiteX4; // eax
  double fld_e215710; // st7
  int nFaceDir2; // eax
  int fld_e21575; // ecx
  int nBiteX2; // eax
  double fld_e21576; // st7
  int nFaceDir3; // eax
  int fld_e21577; // ecx
  int nBiteX3; // eax
  double fld_e21578; // st7
  int fld_e215711b; // edi
  int pVictimObj; // ebx
  int nSelfW; // esi
  int nZOff; // edi
  int nZBite; // edi

  fld_e2157 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);
  fld_e21572 = *(this + 2157);
  if ( fld_e2157 != 0 )
  {
    pVictimChar = __RTDynamicCast(fld_e21572, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    result = *(float **)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimChar + 1032))(pVictimChar);
    if ( result == (float *)1 )
    {
      nFaceDir1 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21573 = *(this + 2157);
      if ( nFaceDir1 != 0 )
        nBiteX1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 120))(fld_e21573) - 52;
      else
        nBiteX1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 120))(fld_e21573) + 52;
      *pArg2 = (float)nBiteX1;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
      fld_e21574 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 5);
      *pArg4 = fld_e21574;
      return pArg4;
    }
    else if ( result != nullptr )
    {
      if ( result == (float *)2 )
      {
        nFaceDir2 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        fld_e21575 = *(this + 2157);
        if ( nFaceDir2 != 0 )
          nBiteX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21575 + 120))(fld_e21575) - 44;
        else
          nBiteX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21575 + 120))(fld_e21575) + 44;
        *pArg2 = (float)nBiteX2;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
        fld_e21576 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 32);
        *pArg4 = fld_e21576;
        return pArg4;
      }
      else if ( result == (float *)3 )
      {
        nFaceDir3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        fld_e21577 = *(this + 2157);
        if ( nFaceDir3 != 0 )
          nBiteX3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21577 + 120))(fld_e21577) - 40;
        else
          nBiteX3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21577 + 120))(fld_e21577) + 40;
        *pArg2 = (float)nBiteX3;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
        fld_e21578 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 2);
        *pArg4 = fld_e21578;
        return pArg4;
      }
    }
    else
    {
      nFaceDir4 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21579 = *(this + 2157);
      if ( nFaceDir4 != 0 )
        nBiteX4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21579 + 120))(fld_e21579) - 34;
      else
        nBiteX4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21579 + 120))(fld_e21579) + 34;
      *pArg2 = (float)nBiteX4;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
      fld_e215710 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 12);
      *pArg4 = fld_e215710;
      return pArg4;
    }
  }
  else
  {
    *pArg2 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21572 + 120))(fld_e21572);
    *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
    fld_e215711b = *(this + 2157);
    pVictimObj = fld_e215711b;
    nSelfW = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
    nZOff = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e215711b + 128))(fld_e215711b) - nSelfW;
    nZBite = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 192))(pVictimObj) + nZOff;
    *pArg4 = (float)nZBite;
    return pArg4;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BCFC0 sub_5BCFC0 —— 飞艇·破坏粒子对象释放（this+8668 槽）
// this+2167（字节 8668）指针非空时按 vtable[0](obj,1) 释放后清 0——该槽与 ·sub_5BC880 的
// this+8620/8648 两 std::string 资源名配套（AIRSHIP_BREAK 粒子对象句柄【推断】）；
// 与 ·sub_5BA090/·sub_5BA200 同族（差异：作用槽 2167）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCFC0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax

  fld_e2167 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  if ( fld_e2167 != nullptr )
    result = (**fld_e2167)(fld_e2167, 1);
  *(this + 2167) = 0;
  return result;
}



// 蓄力技能：vt+212 "HOLD"（81L）
// ------------------------------------------------------------
// 0x5BCFE0 sub_5BCFE0 —— 鬼魂·HOLD 蓄力起手（捕获抱杀对象 + 参数面初始化）
// pArg3+4 事件取目标：vt+40 校验类型 17、vt+128 高度>0 才写入 this+2157 抱杀槽，否则清 0。
// 捕获成功读目标 vt+120/124/128 三轴存 this+2159..2161，并经 vt+1312 收手取坐标、vt+112 对齐自身。
// this+2158 = 事件参数 +8 子类型（1 吸血/2 吸魔，供 ·0x5BD3C0 结算）；vt+344 按子类型切 this+139 资源双档。
// 末段 vt+876 速率双轴清零、vt+888/vt+896 参数面落定，vt+212 播报 HOLD 蓄力语音。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCFE0(uint32_t *this, int nArg2, int pArg3)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2157; // ecx
  int v7; // eax
  int fld_e21572; // ecx
  int v9; // eax
  int fld_e21573; // ecx
  int v11; // eax
  int v12; // edx
  int fld_e1554; // ecx
  int v14; // edx
  int v15; // eax
  uint32_t *fld_e28; // edi
  float v18; // [esp+Ch] [ebp-Ch] BYREF
  float v19; // [esp+10h] [ebp-8h] BYREF
  float v20; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2157) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2157) = 0;
  }
  fld_e2157 = *(this + 2157);
  if ( fld_e2157 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2157 + 120))(fld_e2157);
    fld_e21572 = *(this + 2157);
    *(this + 2159) = v7;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21572 + 124))(fld_e21572);
    fld_e21573 = *(this + 2157);
    *(this + 2160) = v9;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 128))(fld_e21573);
    v12 = *this;
    *(this + 2161) = v11;
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(v12 + 1312))(this, &v18, &v19, &v20);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(
      this,
      (uint64_t)v18 >> 32,
      (uint64_t)v18,
      (uint64_t)v19,
      (uint64_t)v20);
  }
  fld_e1554 = *(this + 1554);
  v14 = *this;
  v15 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
  *(this + 2158) = v15;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (v15 != 1 ? 4 : 0)));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// ============================================================
// 【分区 9】幽灵 & 鬼魂（Wraith / Spectress）（0x5BD1B0-0x5BE7C0）
// 证据：WRAITH_ATK + R_WRAITH_DMG/DIE/R_WRAITH、WRAITH_KISS 吻杀（0x5BD3C0/0x5BD8F0,
//       后者读 +568 最后受击时刻）、R_WRAITH_KISS、Monster/Wraith/{WraithAni,WraithSpectressAni}/
//       {Die,KissWind,KissCircle}.ani、Particle/{KissHeart,Bat}.ptl

// 幽灵语音装载：WRAITH_ATK + R_WRAITH_DMG/DIE/R_WRAITH 四件套 +
//   Monster/Wraith/WraithAni/Die.ani 死亡特效（this+8628..8648 相位）
// ------------------------------------------------------------
// 0x5BD1B0 sub_5BD1B0 —— 幽灵·语音/死亡特效资源装载与相位复位
// this+6792..6808 预置 3/3/6/6/5 六槽（攻/亡语音 ID 面）；this+8628=0、8632=-1 哨兵、8636..8648 相位清零。
// ·sub_4015C0 逐一登记 WRAITH_ATK、R_WRAITH_DMG、R_WRAITH_DIE、R_WRAITH 与 WraithAni/Die.ani 五资源。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD1B0(int this)
{
  uint32_t *pThis_21BC; // ecx
  int result; // eax

  *(uint32_t *)(this + 6792) = 3;
  *(uint32_t *)(this + 6796) = 3;
  *(uint32_t *)(this + 6804) = 6;
  *(uint32_t *)(this + 6808) = 6;
  *(uint32_t *)(this + 6800) = 5;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = -1;
  pThis_21BC = (uint32_t *)(this + 8636);
  *pThis_21BC = 0;
  pThis_21BC[1] = 0;
  pThis_21BC[2] = 0;
  sub_4015C0("WRAITH_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH", 8u);  // 【std::string构造赋值】
  result = sub_4015C0("Monster/Wraith/WraithAni/Die.ani", 0x20u);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8648) = 0;
  return result;
}



// 鬼魂死亡特效：Monster/Wraith/WraithSpectressAni/Die.ani（this+8648/8700 相位）
// ------------------------------------------------------------
// 0x5BD270 sub_5BD270 —— 鬼魂·死亡特效装载（Die.ani + 相位置 1）
// this+8648=1 标记死亡特效已装载（与 ·0x5BD1B0 收尾置 0 互补）；this+8700 鬼魂专属相位清零。
// ·sub_4015C0 登记 Monster/Wraith/WraithSpectressAni/Die.ani。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD270(uint8_t *this)
{
  *(this + 8700) = 0;
  *(this + 8648) = 1;
  return sub_4015C0("Monster/Wraith/WraithSpectressAni/Die.ani", 0x29u);  // 【std::string构造赋值】
}



// AI 相位辅助（55L）
// ------------------------------------------------------------
// 0x5BD2A0 sub_5BD2A0 —— 抱杀附加效果生成（两枚 PO + 霸体 PO，生命 15000ms）
// new 0x7C 经 ·sub_4B3DF0 构造 PO 类型 7 与 8（参数 20.0f、15000）；new 0x64 经 ·sub_51A7D0 构造霸体 PO 并写 +40 存活 15000。
// 三枚均以 this+2157（被抱者）为宿主，vt+56 走同一装载入口下发。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD2A0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int pObj; // esi
  uint32_t *v4; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax
  void *pMem3; // eax

  pMem = operator new(0x7Cu);
  pObj = 0;
  if ( pMem != nullptr )
    v4 = sub_4B3DF0(pMem, 7, 1, 1101004800, 15000, 0);
  else
    v4 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
    v4,
    *(this + 2157),
    *(this + 2157),
    0,
    0,
    0,
    -1);
  pMem2 = operator new(0x7Cu);
  if ( pMem2 != nullptr )
    v6 = sub_4B3DF0(pMem2, 8, 1, 1101004800, 15000, 0);
  else
    v6 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v6 + 56))(
    v6,
    *(this + 2157),
    *(this + 2157),
    0,
    0,
    0,
    -1);
  pMem3 = operator new(0x64u);
  if ( pMem3 != nullptr )
    pObj = sub_51A7D0(pMem3);
  *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 40) = 15000;
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
           pObj,
           *(this + 2157),
           *(this + 2157),
           0,
           0,
           0,
           -1);
}



// 鬼魂·吻杀吸血吸魔（145L）：普攻态子类型1/2 时对攻击者 RTTI 解算，存活且空闲则
//   setState(14,[X,Y,子类型]) 抱住目标；大状态14 且 this[2157](被抱者) 有效时播
//   WRAITH_KISS——this[2158]==1 吸血： victims vt+740×0.1 生成伤害文本并从 vt+736 扣减；
//   this[2158]==2 吸魔：vt+756×0.15 从 vt+744 扣减；普攻子类型0 命中时对攻击者施加
//   vt+760(状态11, 15.0, 5, 自身)【推断：15 秒失明/诅咒类状态】
// ------------------------------------------------------------
// 0x5BD3C0 sub_5BD3C0 —— 鬼魂吻杀·吸血吸魔结算（主状态 8/14 双分支）
// 前置门：nArg4==0 且 this[77]（vt+308）非 0；攻击者经 RTTI 降型为 IRDActiveObject，须 vt+948 可交互且 vt+840 大状态 0。
// 明细与上方既有注释一致：子段 1/2 接触命中 setState(14) 抱杀；状态 14 时吸血量 = 被抱者 vt+740×0.1 经 vt+728 扣减、吸魔 ×0.15 走 vt+744。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD3C0(int **this, int *pAttacker, int nArg3, int nArg4)
{
  int result; // eax
  int pAttackerObj; // eax
  int pAttackerVt; // ebx
  int nProp152; // eax
  int pSparkRes; // eax
  int nDrainHp; // edi
  uint8_t *pMem; // eax
  uint8_t *pTextObj; // eax
  int pTextObjVt; // edx
  int *fld_e21572; // ecx
  int pVicVt; // ebx
  int nVicHp; // eax
  int nDrainMp; // edi
  int fld_e21573; // ebx
  int nVicMp; // eax
  int pAttackerObj2; // eax
  int v21; // [esp+10h] [ebp-38h]
  void *pBuf[4]; // [esp+2Ch] [ebp-1Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17);
      if ( (uint8_t)result != 0 )
      {
        pAttackerObj = __RTDynamicCast(
               (int)pAttacker,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
        nArg4 = pAttackerObj;
        if ( pAttackerObj != 0
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAttackerObj + 948))(pAttackerObj) != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 840))(nArg4) == 0
          && ((int (/*thiscall*/ *)(int **))(*this)[142])(this) != 14 )
        {
          memset(&pBuf[1], 0, 12);
          v23 = 0;
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*pAttacker + 48))(pAttacker);
          sub_431230((int)pBuf, &nArg4);
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*pAttacker + 52))(pAttacker);
          sub_431230((int)pBuf, &nArg4);
          nArg4 = sub_41A5E0((unsigned int)(this + 1757));
          sub_431230((int)pBuf, &nArg4);
          ((void (/*thiscall*/ *)(int **, int, void **, uint32_t, uint32_t))(*this)[140])(this, 14, pBuf, 0, 0);
          v23 = -1;
          sub_5E5260(pBuf);
        }
        pAttackerVt = *pAttacker;
        nProp152 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
        pSparkRes = sub_432E50(nProp152);
        return (*(int (/*thiscall*/ **)(int *, int))(pAttackerVt + 144))(pAttacker, pSparkRes);
      }
    }
  }
  else if ( ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 14 && *(this + 2157) != nullptr )
  {
    ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WRAITH_KISS", -1, 0, 0);
    result = (int)*(this + 2158);
    if ( result == 1 )
    {
      nDrainHp = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 740))(*(this + 2157)) * 0.1);
      nArg4 = nDrainHp;
      pMem = operator new(0x80u);
      v23 = 1;
      if ( pMem != nullptr )
      {
        *(float *)&v21 = (float)nArg4;
        pTextObj = sub_4D6810(pMem, v21, 100, 1, 1);
      }
      else
      {
        pTextObj = nullptr;
      }
      pTextObjVt = *(uint32_t *)pTextObj;
      v23 = -1;
      (*(void (/*thiscall*/ **)(uint8_t *, int **, int **, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(
        pTextObj,
        this,
        this,
        0,
        0,
        0,
        -1);
      fld_e21572 = *(this + 2157);
      pVicVt = *fld_e21572;
      nVicHp = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_e21572 + 736))(fld_e21572, 1, 0);
      return (*(int (/*thiscall*/ **)(uint32_t, int))(pVicVt + 728))(*(this + 2157), nVicHp - nDrainHp);
    }
    else if ( result == 2 )
    {
      result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
      if ( (uint8_t)result != 0 )
      {
        nArg4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 756))(*(this + 2157));
        nDrainMp = (uint64_t)((double)nArg4 * 0.15000001);
        fld_e21573 = **(this + 2157);
        nVicMp = (*(int (/*stdcall*/ **)(int))(fld_e21573 + 752))(1);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21573 + 744))(*(this + 2157), nVicMp - nDrainMp);
      }
    }
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this);
    if ( result == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17);
        if ( (uint8_t)result != 0 )
        {
          pAttackerObj2 = __RTDynamicCast(
                  (int)pAttacker,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          return (*(int (/*thiscall*/ **)(int, int, int, int, int **, uint32_t))(*(uint32_t *)pAttackerObj2 + 760))(
                   pAttackerObj2,
                   11,
                   1097859072,
                   5,
                   this,
                   0);
        }
      }
    }
  }
  return result;
}


// 参数打包 AI（sub_431230, 83L）
// ------------------------------------------------------------
// 0x5BD710 sub_5BD710 —— 抱杀收尾·被抱者搬运落位与状态下发
// 被抱者 this+2157 先经 vt+604/vt+612 解挂，再用 vt+136 尝试落位捕获坐标 this+2159/2160；失败转 vt+124/120 探测候选位、
// vt+140 校验自身可站位，仍失败则退回自身锚点经 vt+112 落位。
// 落位成功后若被抱者 vt+308 有效，打包 [4,0,1,100,100]（·sub_431230）经 vt+560 setState(4 受击后置) 下发、vt+564 提交，末清 this+2157。
// ------------------------------------------------------------
void /*usercall*/ sub_5BD710(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int pVictim; // ecx
  int *pVictim2; // edi
  int pVictimVt; // edx
  int nTryY; // eax
  int nTryX; // eax
  char bMoveOk; // al
  int *pVictim3; // ecx
  int pVictimVt2; // edi
  int nAltY; // eax
  int nAltX; // eax
  uint8_t v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  uint32_t aPackVec[4]; // [esp+18h] [ebp-10h] BYREF

  pVictim = pArg1[2157];
  if ( pVictim != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pVictim + 604))(pVictim, 1, nArg2);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 136))(
           pArg1[2157],
           pArg1[2159],
           pArg1[2160],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 112))(pArg1[2157], pArg1[2159], pArg1[2160]);
    }
    else
    {
      pVictim2 = (int *)pArg1[2157];
      pVictimVt = *pVictim2;
      aPackVec[0] = pVictim2;
      aPackVec[0] = *pArg1;
      nTryY = (*(int (/*thiscall*/ **)(int *, int, int, int))(pVictimVt + 124))(pVictim2, 300, 1, 1);
      nTryX = (*(int (/*thiscall*/ **)(int *, int))(*pVictim2 + 120))(pVictim2, nTryY);
      bMoveOk = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, int))(aPackVec[0] + 140))(pArg1, pArg1 + 2159, pArg1 + 2160, nTryX);
      pVictim3 = (int *)pArg1[2157];
      if ( bMoveOk != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*pVictim3 + 112))(pVictim3, pArg1[2159], pArg1[2160]);
      }
      else
      {
        pVictimVt2 = *pVictim3;
        nAltY = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, pArg1[2161]);
        nAltX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nAltY);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt2 + 112))(pArg1[2157], nAltX);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      aPackVec[3] = 0;
      aPackVec[0] = 4;
      sub_431230((int)v13, aPackVec);
      aPackVec[0] = 0;
      sub_431230((int)v13, aPackVec);
      aPackVec[0] = 1;
      sub_431230((int)v13, aPackVec);
      aPackVec[0] = 100;
      sub_431230((int)v13, aPackVec);
      aPackVec[0] = 100;
      sub_431230((int)v13, aPackVec);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 4, v13, 2, 0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      if ( Block != nullptr )
        j__free(Block);
    }
    pArg1[2157] = 0;
  }
}



// 吻杀执行（176L）：WRAITH_KISS + RTTI cast；读 this+568 最后受击时刻
//   （研究 20 §1.2 sub_4E48D0 记录字段 —— 吻杀与受击历史的联动【推断】）
// ------------------------------------------------------------
// 0x5BD8F0 sub_5BD8F0 —— 鬼魂吻杀·吸血吸魔结算（类型过滤 + 标记门控版）
// 与 ·0x5BD3C0 同构（差异：先经 vt+340 过滤类型 410/411 免抱杀【推断：BOSS 级豁免】；吸血/吸魔比例改 5%；
// 吸血需被抱者带标记 273；被抱者类型 529 时转 ·0x5BD2A0 生成附加 PO；子段 0 施加状态 4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD8F0(int *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int pAttackerObj; // eax
  int pAttacker; // ebx
  int pVt; // eax
  int pAttackerVt; // ebx
  int nProp152; // eax
  int pSparkRes; // eax
  bool bNoDown; // zf
  int fld_e21572; // eax
  int nDrainHp; // edi
  int *pTextObj; // eax
  int pTextObjVt; // edx
  int *fld_e21573; // ecx
  int pVicVt; // ebx
  int nVicHp; // eax
  char fld_e21574; // al
  int *fld_e21575; // ecx
  int v22; // edi
  int fld_e21576; // ebx
  int v24; // eax
  float fDrainF; // [esp+14h] [ebp-38h]
  void *pBuf[4]; // [esp+30h] [ebp-1Ch] BYREF
  int v27; // [esp+48h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);
        if ( *(uint32_t *)result != 410 )  // 类型 410/411 免疫抱杀【推断：BOSS 类免疫】
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);
          if ( *(uint32_t *)result != 411 )  // 同上
          {
            pAttackerObj = __RTDynamicCast(
                   nArg2,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
            pAttacker = pAttackerObj;
            if ( pAttackerObj != 0
              && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAttackerObj + 948))(pAttackerObj) != 0
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker + 840))(pAttacker) == 0
              && (*(int (/*thiscall*/ **)(int *))(*this + 568))(this) != 14 )
            {
              memset(&pBuf[1], 0, 12);
              pVt = *(uint32_t *)nArg2;
              v27 = 0;
              nArg4 = (*(int (/*thiscall*/ **)(int))(pVt + 48))(nArg2);
              sub_431230((int)pBuf, &nArg4);
              nArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);
              sub_431230((int)pBuf, &nArg4);
              nArg4 = sub_41A5E0((unsigned int)(this + 1757));
              sub_431230((int)pBuf, &nArg4);
              (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
              v27 = -1;
              sub_5E5260(pBuf);
            }
            pAttackerVt = *(uint32_t *)nArg2;
            nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            pSparkRes = sub_432E50(nProp152);
            return (*(int (/*thiscall*/ **)(int, int))(pAttackerVt + 144))(nArg2, pSparkRes);
          }
        }
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 && *(this + 2157) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WRAITH_KISS", -1, 0, 0);
    result = *(this + 2158);
    if ( result == 1 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result == 0 )
        return result;
      bNoDown = (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273) == 0;
      fld_e21572 = *(uint32_t *)*(this + 2157);
      if ( !bNoDown )
      {
        nDrainHp = (uint64_t)((double)(*(int (**)(void))(fld_e21572 + 740))() * 0.050000001);  // 吸血量=受害者 vt+740×5%
        nArg4 = nDrainHp;
        v27 = 1;
        if ( operator new(0x80u) != nullptr )
        {
          fDrainF = (float)nArg4;
          pTextObj = (int *)sub_4D6810(LODWORD(fDrainF), 100, 1, 1);
        }
        else
        {
          pTextObj = nullptr;
        }
        pTextObjVt = *pTextObj;
        v27 = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(
          pTextObj,
          this,
          this,
          0,
          0,
          0,
          -1);
        fld_e21573 = (int *)*(this + 2157);
        pVicVt = *fld_e21573;
        nVicHp = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_e21573 + 736))(fld_e21573, 1, 0);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(pVicVt + 728))(*(this + 2157), nVicHp - nDrainHp);
      }
    }
    else
    {
      if ( result != 2 )
        return result;
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result == 0 )
        return result;
      fld_e21574 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);
      fld_e21575 = (int *)*(this + 2157);
      if ( fld_e21574 != 0 )
      {
        nArg4 = (*(int (/*thiscall*/ **)(int *))(*fld_e21575 + 756))(fld_e21575);
        v22 = (uint64_t)((double)nArg4 * 0.050000001);
        fld_e21576 = *(uint32_t *)*(this + 2157);
        v24 = (*(int (/*stdcall*/ **)(int))(fld_e21576 + 752))(1);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21576 + 744))(*(this + 2157), v24 - v22);
      }
      fld_e21572 = *fld_e21575;
    }
    result = (*(int (/*stdcall*/ **)(int))(fld_e21572 + 40))(529);
    if ( (uint8_t)result != 0 )
      return sub_5BD2A0(this);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
        if ( (uint8_t)result != 0 )
        {
          result = __RTDynamicCast(
                     nArg2,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDActiveObject `RTTI Type Descriptor',
                     0);
          if ( result != 0 )
            return (*(int (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)result + 760))(
                     result,
                     4,
                     1097859072,
                     5,
                     this,
                     0);
        }
      }
    }
  }
  return result;
}


// 蓄力技能：vt+212 "HOLD"（102L）
// ------------------------------------------------------------
// 0x5BDCD0 sub_5BDCD0 —— 鬼魂·HOLD 蓄力（抱杀名单去重版）
// 与 ·0x5BCFE0 同构（差异：多一道 this+2164..2165 名单扫描——已在名单的目标直接清 this+2157，新目标经 ·sub_4E7BA0 登记；
// 且目标须 vt+40 支持 529 且类型非 410/411）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BDCD0(uint32_t *this, int nArg2, int pArg3)
{
  int pObj2; // eax
  int pObj; // ebx
  uint32_t *pThis_86D; // edi
  uint32_t *fld_e2164; // eax
  int v8; // eax
  int pObj3; // ecx
  int v10; // eax
  int pObj4; // edi
  int fld_e1554; // ecx
  int v13; // edx
  int v14; // eax
  uint32_t *fld_e28; // edi
  float v17; // [esp+Ch] [ebp-Ch] BYREF
  float v18; // [esp+10h] [ebp-8h] BYREF
  float v19; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0 )
  {
    pThis_86D = this + 2157;
LABEL_14:
    *pThis_86D = 0;
    goto LABEL_15;
  }
  pThis_86D = this + 2157;
  *(this + 2157) = pObj;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0 )
    *pThis_86D = 0;
  if ( *pThis_86D != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_86D + 40))(*pThis_86D, 529) != 0
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 410
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 411 )
  {
    fld_e2164 = (uint32_t *)*(this + 2164);
    if ( fld_e2164 == (uint32_t *)*(this + 2165) )
    {
LABEL_12:
      sub_4E7BA0(this + 2157);
      goto LABEL_15;
    }
    while ( *fld_e2164 != *pThis_86D )
    {
      if ( ++fld_e2164 == (uint32_t *)*(this + 2165) )
        goto LABEL_12;
    }
    goto LABEL_14;
  }
LABEL_15:
  if ( *pThis_86D != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 120))(*pThis_86D);
    pObj3 = *pThis_86D;
    *(this + 2159) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);
    pObj4 = *pThis_86D;
    *(this + 2160) = v10;
    *(this + 2161) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4);
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(*this + 1312))(this, &v17, &v18, &v19);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(
      this,
      (uint64_t)v17 >> 32,
      (uint64_t)v17,
      (uint64_t)v18,
      (uint64_t)v19);
  }
  fld_e1554 = *(this + 1554);
  v13 = *this;
  v14 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
  *(this + 2158) = v14;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v13 + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (v14 != 1 ? 4 : 0)));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BDF10 sub_5BDF10 —— 抱杀关系析构通知（被抱者/自身消亡时解挂）
// uArg3（消亡对象）== this+2157 被抱者且大状态 14 → ·sub_5BD710 收尾搬运后清槽；uArg3==自身且抱杀槽非空 → 同样收尾。
// 末尾尾调 ·sub_4D9170 消亡通知，把消亡对象转发给基类登记。
// ------------------------------------------------------------
int /*userpurge*/ sub_5BDF10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)
{
  if ( uArg3 == (uint32_t *)pArg1[2157] )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 14 )
      sub_5BD710(pArg1, nArg2);
    pArg1[2157] = 0;
  }
  if ( uArg3 == pArg1 && pArg1[2157] != 0 )
  {
    sub_5BD710(pArg1, nArg2);
    pArg1[2157] = 0;
  }
  return sub_4D9170(uArg3);
}



// 爱心技能：引用 Particle/KissHeart.ptl
// ------------------------------------------------------------
// 0x5BDF80 sub_5BDF80 —— 爱心特效装载（KissHeart.ptl 挂 this+2167）
// new 0x12C 经 ·sub_4C3640 以 this+91 处字符串池装载 Particle/KissHeart.ptl（SSO 分支：this+96 <16 走内联缓冲）。
// 对象句柄写入 this+2167，供 ·0x5BE570 吻杀编排中 vt+12/vt+40/vt+92 二次驱动。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BDF80(uint32_t *this)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/KissHeart.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/KissHeart.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;
  return result;
}



// 鬼魂·事件分发+反抱判定（121L）：事件15(抱住)——先按 vt+136/132 可站位检查，失败则
//   把自身挪到 this[2157](受害者)脚下，再 vt+196 切 1554+4 动画；事件8(受击)→
//   R_WRAITH_KISS 反抱门：血量 vt+736 ≥ vt+740×0.5(半血) 时事件参数=2(反向抱)否则 1；
//   事件14 走 vt+1316 转发；事件5 加载 KissWind 类特效(路径串在 this[2151])挂身上
// ------------------------------------------------------------
// 0x5BE010 sub_5BE010 —— 鬼魂·反抱事件分发（事件 8 半血阈值定阶段 1/2）
// 进场若 this+1639 主状态镜像2 == 14 先 ·sub_5BD710 收尾；事件 14 转 vt+1316、事件 15 落位失败则自身挪至被抱者坐标并 vt+196 切 1554+4 动画。
// 事件 8 且事件参数子类型非 0/非 3 时播报 R_WRAITH_KISS：当前血量 vt+736 ≥ vt+740×0.5 半血阈值 → 参数 2（反抱继续）否则 1（挣脱）。
// 收尾 ·sub_4E33D0 状态提交；nEvt==5 时经 ·sub_42FCB0(228) 门与 ·sub_431860 装载 this+2151 路径 ani，pool 0x11C CNRDPooledObject 经 ·sub_45FE80 挂装并 vt+112/vt+144 落位朝向。
// ------------------------------------------------------------
void /*userpurge*/ sub_5BE010(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int nEvt; // edi
  int pArg42; // ebx
  int pVt; // edi
  int nY; // eax
  int nX; // eax
  int pVt2; // edi
  int nZ; // eax
  int pVictim; // eax
  int pVt3; // ebx
  int pVictim2; // edi
  int nVicZ; // eax
  int nVicY; // eax
  int nVicX; // eax
  int nKissSub; // ecx
  uint32_t *pKissParam; // eax
  int hAniKiss; // ebx
  int pszPath; // edx
  char *pPool; // eax
  char *pFxObj; // edi
  int pFxVt; // ebx
  int nZ2; // eax
  int nY2; // eax
  int nX2; // eax
  int pFxVt2; // ebx
  int nFaceDir; // eax
  float fCurHp; // [esp+24h] [ebp+8h]

  if ( pDwArg1[1639] == 14 )
    sub_5BD710();
  nEvt = ArgList;
  pArg42 = pArg4;
  switch ( ArgList )
  {
    case 14:
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1316))(pDwArg1, 14, pArg4);
      break;
    case 15:
      pVt = *pDwArg1;
      nY = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, 0);
      nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt + 136))(pDwArg1, nX) == 0
        || (pVt2 = *pDwArg1,
            nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1),
            (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt2 + 132))(pDwArg1, nZ) == 0) )
      {
        pVictim = pDwArg1[2157];
        if ( pVictim != 0 )
        {
          pVt3 = *pDwArg1;
          pVictim2 = pDwArg1[2157];
          nVicZ = (*(int (**)(void))(*(uint32_t *)pVictim + 128))();
          nVicY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 124))(pVictim2, nVicZ);
          nVicX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 120))(pVictim2, nVicY);
          (*(void (/*thiscall*/ **)(int *, int))(pVt3 + 112))(pDwArg1, nVicX);
          pArg42 = pArg4;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));
      nEvt = 15;
      break;
    case 8:
      nKissSub = **(uint32_t **)(pArg4 + 4);
      if ( nKissSub != 0 && nKissSub != 3 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "R_WRAITH_KISS", -1, 0, 0);
        fCurHp = (float)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);  // 当前血量
        fArg2 = (double)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1) * 0.5;  // 半血阈值
        pKissParam = *(uint32_t **)(pArg4 + 4);
        if ( fArg2 <= fCurHp )
          *pKissParam = 2;  // 半血以上→反抱阶段2(继续抱)
        else
          *pKissParam = 1;  // 半血以下→反抱阶段1(挣脱)
      }
      break;
    default:
      break;
  }
  sub_4E33D0((int)pDwArg1, pArg42, fArg2, nEvt, pArg42, *(float *)&nArg5, *(float *)&nArg6);
  if ( nEvt == 5 )
  {
    hAniKiss = 0;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( (unsigned int)pDwArg1[2156] < 0x10 )
        LOBYTE(pszPath) = (uint8_t)pDwArg1 - 100;
      else
        pszPath = pDwArg1[2151];
      hAniKiss = sub_431860(pszPath, 1);
    }
    if ( hAniKiss != 0 )
    {
      pPool = (char *)sub_44B6C0(284);
      pFxObj = pPool;
      if ( pPool != nullptr )
      {
        sub_44E0D0(pPool, hAniKiss, 1);
        *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';
      }
      else
      {
        pFxObj = nullptr;
      }
      sub_45FE80(pDwArg1[29], (int)pFxObj, 2, 0, (int)pFxObj, (int)pDwArg1, 0);
      pFxVt = *(uint32_t *)pFxObj;
      nZ2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      nY2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ2);
      nX2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY2);
      (*(void (/*thiscall*/ **)(char *, int))(pFxVt + 112))(pFxObj, nX2);
      pFxVt2 = *(uint32_t *)pFxObj;
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      (*(void (/*thiscall*/ **)(char *, int))(pFxVt2 + 144))(pFxObj, nFaceDir);
    }
  }
}


// 吻杀风特效：Monster/Wraith/WraithSpectressAni/KissWind.ani（60L）
// ------------------------------------------------------------
// 0x5BE250 sub_5BE250 —— 吻杀风特效生成（KissWind.ani 挂被抱者坐标）
// 前置 this+2157 非空 + ·sub_42FCB0(228) 资源门；·sub_431860 装载 KissWind.ani，pool 构造 CNRDPooledObject 后 ·sub_45FE80 挂载。
// 落位读被抱者 vt+128/124/120 三轴链，vt+144 取自身朝向；供 ·0x5BE570 大状态 14 帧段 3 相位调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE250(int *this)
{
  int result; // eax
  int v3; // ebx
  char *v4; // eax
  char *v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int fld_e2157; // [esp+8h] [ebp-10h]

  result = *(this + 2157);
  if ( result != 0 )
  {
    result = sub_42FCB0(228);
    if ( result != 0 )
    {
      result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissWind.ani", 1);
      v3 = result;
    }
    else
    {
      v3 = 0;
    }
    if ( v3 != 0 )
    {
      v4 = (char *)sub_44B6C0(284);
      v5 = v4;
      if ( v4 != nullptr )
      {
        sub_44E0D0(v4, v3, 1);
        *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v5 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v5, 2, 0, (int)v5, (int)this, 0);
      v6 = *(uint32_t *)v5;
      fld_e2157 = *(this + 2157);
      v7 = (*(int (**)(void))(*(uint32_t *)fld_e2157 + 128))();
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 124))(fld_e2157, v7);
      v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 120))(fld_e2157, v8);
      (*(void (/*thiscall*/ **)(char *, int))(v6 + 112))(v5, v9);
      v10 = *(uint32_t *)v5;
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      return (*(int (/*thiscall*/ **)(char *, int))(v10 + 144))(v5, v11);
    }
  }
  return result;
}



// 吻杀环特效：Monster/Wraith/WraithSpectressAni/KissCircle.ani（57L）
// ------------------------------------------------------------
// 0x5BE360 sub_5BE360 —— 吻杀环特效生成（KissCircle.ani 沿朝向偏移 ±30）
// 与 ·0x5BE250 同构（差异：无 this+2157 前置门；落位在自身 vt+120 按 vt+152 朝向 ±30 偏移、vt+124 传 80）。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE360@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v13; // [esp+8h] [ebp-10h]

  result = sub_42FCB0(228);
  if ( result != 0 )
  {
    result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissCircle.ani", 1);
    v4 = result;
  }
  else
  {
    v4 = 0;
  }
  if ( v4 != 0 )
  {
    v5 = (char *)sub_44B6C0(284);
    v6 = v5;
    if ( v5 != nullptr )
    {
      sub_44E0D0(v5, v4, 1);
      *(uint32_t *)v6 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v6 = nullptr;
    }
    sub_45FE80(pDwArg1[29], (int)v6, 2, 0, (int)v6, (int)pDwArg1, 0);
    if ( (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, nArg2) == 1 )
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 30;
    else
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 30;
    v8 = *(uint32_t *)v6;
    v13 = v7;
    v9 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, 80);
    (*(void (/*thiscall*/ **)(char *, int, int))(v8 + 112))(v6, v13, v9);
    v10 = *(uint32_t *)v6;
    v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    return (*(int (/*thiscall*/ **)(char *, int))(v10 + 144))(v6, v11);
  }
  return result;
}



// 硬直/相位字段（this+208/8649/8650/8700/8701）
// ------------------------------------------------------------
// 0x5BE470 sub_5BE470 —— 鬼魂·硬直/相位字段更新（事件 8/15 前处理，末尾转 ·0x5BE010）
// 大状态 15（施放）且 this+8701 被抱者可动标记 → vt+944(1,10000) 延时长硬直，随即 vt+340/vt+124/vt+120 链落位；大状态 8（攻击）→ vt+208 帧写入 1554+20 段。
// 事件 8 且参数子类型 3 → this+8700 置 1 并 vt+204 写帧，this+8649/8650 双双置 1 排程吻杀特效；事件 15 → this+8701 = 被抱者带标记 273。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE470(uint8_t *this, int ArgList, int pArg3, int nArg4, int nArg5)
{
  int pThis_348; // eax
  int v7; // edi
  int pThis_154; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int pThis_612; // eax
  int v12; // edx
  int pThis_86D; // ecx
  bool v14; // al

  pThis_348 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 == 15 )
  {
    if ( *(this + 8701) != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)this + 944))(this, 1, 10000);
    v7 = *(uint32_t *)this;
    pThis_154 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this);
    pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 124))(this, *(uint32_t *)(pThis_154 + 40));
    pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v7 + 112))(this, pThis_78);
  }
  else if ( pThis_348 == 8 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 20));
  }
  if ( ArgList == 8 )
  {
    if ( **(uint32_t **)(pArg3 + 4) == 3 )
    {
      pThis_612 = *((uint32_t *)this + 1554);
      v12 = *(uint32_t *)this;
      *(this + 8700) = 1;
      (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v12 + 204))(
        this,
        1,
        *(uint32_t *)(pThis_612 + 20),
        0,
        0,
        0,
        0);
    }
    *(this + 8649) = 1;
    *(this + 8650) = 1;
  }
  else if ( ArgList == 15 )
  {
    pThis_86D = *((uint32_t *)this + 2157);
    v14 = pThis_86D != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_86D + 40))(pThis_86D, 273) != 0;
    *(this + 8701) = v14;
  }
  return sub_5BE010(this, pArg3, ArgList, *(float *)&pArg3, nArg4, nArg5);
}



// 蝙蝠群：引用 Particle/Bat.ptl（97L；鬼魂召蝙蝠演出）
// ------------------------------------------------------------
// 0x5BE570 sub_5BE570 —— 鬼魂·蝙蝠群/吻杀特效编排（Bat.ptl + 8649/8650 相位 → ·0x5BCAB0）
// this+8524 记 vt+940 反向标记；大状态 8 且 vt+908==3、this+8700 相位 1、动作帧段 ≥4 → vt+588 装载 Particle/Bat.ptl、vt+152 生成、vt+145 槽 30300 登记后清相位。
// 大状态 14 且 vt+908 为 2/1：被抱者类型 529 时按帧段 ≥2 触发 ·0x5BE360 环、≥3 触发 ·0x5BE250 风并布 8672 定时 50ms；定时到点驱动 this+2167 爱心对象 vt+12/vt+40/vt+92 与 ·sub_4600B0 挂装。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE570@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int (***pArg3)(void)@<edi>)
{
  char v4; // al
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int pObj; // ecx
  int v9; // ebx
  int (**v10)(void); // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  void *v14; // ecx
  int nArg22; // [esp-4h] [ebp-2Ch]
  void *v17[5]; // [esp+8h] [ebp-20h] BYREF
  int v18; // [esp+24h] [ebp-4h]

  v4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 940))(pArg1);
  v5 = *(uint32_t *)pArg1;
  pArg1[8524] = v4 == 0;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 840))(pArg1) == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 3
      && pArg1[8700] == 1
      && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 4 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/Bat.ptl");
      pArg3 = *(int (****)(void))pArg1;
      v7 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 152))(
             pArg1,
             v6,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
      ((void (/*thiscall*/ *)(uint8_t *, int, int))pArg3[145])(pArg1, 30300, v7);
      pArg1[8700] = 0;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1) == 14
         && ((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 2
          || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 1) )
  {
    pObj = *((uint32_t *)pArg1 + 2157);
    nArg22 = nArg2;
    if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      if ( pArg1[8649] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 )
      {
        sub_5BE360((int *)pArg1, (int)pArg3);
        pArg1[8649] = 0;
      }
      if ( pArg1[8650] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 )
      {
        sub_5BE250((int *)pArg1);
        pArg1[8650] = 0;
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      if ( *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3
        && (uint8_t)sub_41C6E0(pArg1 + 8672) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)pArg1 + 2167) + 12))(*((uint32_t *)pArg1 + 2167), 0);
        v9 = **((uint32_t **)pArg1 + 2167);
        pArg3 = *((int (****)(void))pArg1 + 2157);
        v10 = *pArg3;
        v17[4] = pArg3;
        v11 = v10[32]();
        v12 = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[31])(pArg3, v11 + 32);
        v13 = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[30])(pArg3, v12);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v9 + 40))(*((uint32_t *)pArg1 + 2167), v13);
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**((uint32_t **)pArg1 + 2167) + 92))(*((uint32_t *)pArg1 + 2167), v17);
        v14 = *((void **)pArg1 + 29);
        v18 = 0;
        sub_4600B0(v14, 2, 0, (int)v17);
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        v18 = -1;
        sub_5E5260(v17);
      }
    }
    nArg2 = nArg22;
  }
  return sub_5BCAB0(pArg1, nArg2, (int)pArg3);
}



// ============================================================
// 【分区 10】蜘蛛·毒网与弹幕（0x5BE7C0-0x5BFBC0）
// 证据：Particle/{Web,PoisonWeb,BossMissile1-4}.ptl、GAS_OUT 毒气、HOLD 蓄力

// 子类扩展字段复位（this+8600..8636）
// ------------------------------------------------------------
// 0x5BE7C0 sub_5BE7C0 —— 蜘蛛·子类字段复位（六槽动作号 + this+7324 类型号）
// this+6792..6808 与 +6864..6872 预置 2/3/2/3/4 六槽动作号；this+8600..8636 子类 AI 状态区清零。
// this+7324 = 570（【推断】蜘蛛系角色类型号槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE7C0(int this)
{
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6868) = 2;
  *(uint32_t *)(this + 6796) = 3;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6872) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6864) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 7324) = 570;
  *(uint32_t *)(this + 8636) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BE840 sub_5BE840 —— 蜘蛛·行为字游走机（this+1787 switch + 概率门）
// ·sub_4E0120 推进计时后按 this+1787 行为字分派：0 → vt+1284 自检 proc；4 → 无目标(this+1813==0)回 13、否则 vt+1104 写 5；
// 5 → 有目标且 rand()%100<10 写 4；13/14/15 → 有目标写 4。行为字 4 为捕猎推进态【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE840(int *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand = rand();
        v4 = nRand % 100;
        result = nRand / 100;
        if ( v4 < 10 )
          goto LABEL_10;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_10:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BE910 sub_5BE910 —— 状态施加入口包装（大状态 14 拒收，其余转 ·sub_4D6030）
// 大状态读取 vt+840 == 14（架招）时丢弃本次施加；否则转发 ·sub_4D6030 走 17 状态槽懒创建。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE910(void *this, void *Block, int nArg3, int nArg4)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result != 14 )
    return sub_4D6030((int)this, Block, nArg3, nArg4);
  return result;
}



// 蜘蛛·茧载人位移（124L）：this[2152](茧中猎物)处于大状态9 且攻击动作 +170 段时
//   ++this[2153](搬运帧计数)——达到 this[2154](搬运上限) 或猎物 vt+736≤0 则 setState(15)；
//   否则猎物倒地(273)时按其 vt+1032 姿态档与自身朝向从 v29[23] 偏移表取 ±X 偏移，
//   把自己搬到猎物 X±偏移、Y+1、Z+20（背上高度）处
// ------------------------------------------------------------
// 0x5BE940 sub_5BE940 —— 蜘蛛·茧载人位移（详见上方既有注释）
// 被抱猎物 this[2152] 大状态 9 且攻击动作 +170 段 → 搬运帧计数递增，达上限或猎物 vt+736≤0 则 setState(15)；否则 ·sub_4926A0 帧游标复位。
// 猎物未载入时不处于 5/死亡且 vt+308 有效 → 猎物 setState(9) 载入；v29[23] 偏移表按猎物 vt+1032 姿态档 × 朝向取 ±X，自身落位至猎物 X±偏移、Y+1、Z+20；无茧时 this+8600=1 并 setState(15)。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE940@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pCocoon; // ecx
  int nCarryMax; // ecx
  int nCarryCnt1; // edx
  int pCurAct; // eax
  int *pCocoon2; // edi
  int v9; // eax
  uint32_t *pPostureTab; // eax
  int *pCocoon3; // ecx
  int nIdx2; // eax
  int nDxR; // edx
  int nDxL; // edi
  int pVt; // eax
  int nFacing; // eax
  int pCocoon4; // ecx
  int nCarryX; // ebx
  int nCarryX2; // eax
  int nY; // edi
  int nZ; // eax
  int nBaseX; // ebx
  int nY2; // edi
  int nZ2; // eax
  int pVt2; // eax
  int v28; // [esp+4h] [ebp-64h]
  uint32_t v29[23]; // [esp+8h] [ebp-60h]
  int v30; // [esp+64h] [ebp-4h]

  pCocoon = pArg1[2152];
  if ( pCocoon != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon + 840))(pCocoon) == 9 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )
      {
        nCarryMax = pArg1[2154];
        nCarryCnt1 = pArg1[2153] + 1;
        pArg1[2153] = nCarryCnt1;
        if ( nCarryCnt1 >= nCarryMax || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 736))(pArg1[2152]) <= 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
        }
        else
        {
          pCurAct = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
          sub_4926A0(pCurAct);
        }
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 840))(pArg1[2152]) != 5
           && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 308))(pArg1[2152]) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2152] + 560))(pArg1[2152], 9, 0, 0, 0);
    }
    v29[0] = -15;
    v29[6] = -15;
    v28 = -10;
    v29[5] = -10;
    v29[8] = -19;
    v29[9] = -10;
    v29[14] = -19;
    pCocoon2 = (int *)pArg1[2152];
    v29[15] = 8;
    v29[16] = 10;
    v29[20] = 10;
    v29[21] = 8;
    v29[22] = 10;
    v9 = *pCocoon2;
    v29[1] = -6;
    v29[2] = -24;
    v29[3] = -4;
    v29[4] = -32;
    v29[7] = -14;
    v29[10] = -23;
    v29[11] = -8;
    v29[12] = -27;
    v29[13] = -14;
    v29[17] = 5;
    v29[18] = 13;
    v29[19] = 20;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, int))(v9 + 40))(pCocoon2, 273, nArg3, nArg2) != 0 )
    {
      pPostureTab = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pCocoon2 + 1032))(pCocoon2);
      pCocoon3 = (int *)pArg1[2152];
      nIdx2 = 2 * (*pPostureTab + 4 * pArg1[2159]);
      nDxR = v29[nIdx2];
      nDxL = v29[nIdx2 - 1];
      pVt = *pCocoon3;
      v30 = nDxR;
      nFacing = (*(int (/*thiscall*/ **)(int *))(pVt + 152))(pCocoon3);
      pCocoon4 = pArg1[2152];
      if ( nFacing != 0 )
      {
        nCarryX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon4 + 120))(pCocoon4);
        nCarryX = v30 + nCarryX2;
      }
      else
      {
        nCarryX = nDxL + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon4 + 120))(pCocoon4);
      }
      nY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;
      nZ = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, nCarryX, nY, nZ + 20);
    }
    else
    {
      nBaseX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 120))(pArg1[2152]);
      nY2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;
      nZ2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, nBaseX, nY2, nZ2 + 20);
    }
  }
  else
  {
    pVt2 = *pArg1;
    *((uint8_t *)pArg1 + 8600) = 1;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(pVt2 + 560))(pArg1, 15, 0, 0, 0);
  }
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5BEB90 sub_5BEB90 —— 蜘蛛·茧位校准（不可站位时贴至猎物 Z+40 并重设速率轴）
// vt+136/vt+132 自身落位检查失败且 this+2152 非空 → 读猎物 vt+128/124/120 三轴（Z+40 提升）经 vt+112 落位。
// 随后 vt+876 速率双轴重设 [0,200,200,0,0,0]、vt+888(0,0,1000,1000)、vt+896 传入 ·sub_432E50(vt+152(4)) 参数档。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEB90(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2152; // eax
  int fld_e21522; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )
  {
    fld_e2152 = *(this + 2152);
    if ( fld_e2152 != 0 )
    {
      fld_e21522 = *(this + 2152);
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2152 + 128))();
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522, v10 + 40);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 120))(fld_e21522, v11);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  v15 = sub_432E50(v14);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);
}



// AI 字段访问（this+8600/8608）
// ------------------------------------------------------------
// 0x5BEC80 sub_5BEC80 —— 蜘蛛·吐丝相位复位（this+8600 清 0、this+8608 置 -1）
// 与 ·0x5BECF0 的 this+8600=1 置位互补，供下一轮吐丝门重新通过。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BEC80(int this)
{
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8608) = -1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BECA0 sub_5BECA0 —— 蜘蛛·动作号/相位预置（返回 3 帧段阈值）
// this+1698..1702 预置 2/3/2/3/4、this+1716..1718 预置 0/2/3、this+2153 搬运计数清零；返回 3 供帧段门使用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECA0(uint32_t *this)
{
  *(this + 1698) = 2;
  *(this + 1699) = 3;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *(this + 1716) = 0;
  *(this + 1717) = 2;
  *(this + 1718) = 3;
  *(this + 2153) = 0;
  return 3;
}



// 主状态门（this+200/8600/8608）
// ------------------------------------------------------------
// 0x5BECF0 sub_5BECF0 —— 蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
// ·sub_4E1780 帧推进后判定：大状态 8、this+7028 攻击段号等于 this+8608 记录、vt+308 目标有效、帧段 +148 ≥ 2 且 this+8600 未触发 → vt+1316 触发吐丝并锁 this+8600=1。
// 大状态 6（待机）且帧 +170 段 → vt+876 双轴速率清零（收势待机）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECF0(int this)
{
  int result; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && sub_41A5E0(this + 7028) == *(uint32_t *)(this + 8608)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
    && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 2
    && *(uint8_t *)(this + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);
    *(uint8_t *)(this + 8600) = 1;
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 6 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
               this,
               1,
               0,
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// 蛛网技能：引用 Particle/Web.ptl
// ------------------------------------------------------------
// 0x5BEDB0 sub_5BEDB0 —— 蛛网弹生成（Web.ptl，参数 60/10/4 挂 this+2151 槽）
// vt+588 装载 Particle/Web.ptl（帧 60、子参数 10/4），vt+580 以 this+2151 为发射槽下发。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEDB0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/Web.ptl",
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v2 + 580))(this, *(this + 2151), 0, v3);
}



// AI 字段访问（this+8618）
// ------------------------------------------------------------
// 0x5BEDF0 sub_5BEDF0 —— 蛛网受击回退（vmt214 转发 + this+8618 相位解锁）
// 先 ·sub_495250 转发 vt+968 双标志门；uArg2 != 2 且 vt+308 目标有效、this+8618==1 → 解锁清理：8618=0、vt+560 setState(0 待机)、this+6573/6574 清零。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEDF0(uint8_t *this, unsigned int uArg2, int nArg3, int nArg4)
{
  char result; // al
  int v6; // eax

  result = sub_495250(this, uArg2, nArg3, nArg4);
  if ( uArg2 != 2 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( result != 0 && *(this + 8618) == 1 )
    {
      v6 = *(uint32_t *)this;
      *(this + 8618) = 0;
      result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v6 + 560))(this, 0, 0, 0, 0);
      *(this + 6573) = 0;
      *(this + 6574) = 0;
    }
  }
  return result;
}



// 毒网技能：引用 Particle/PoisonWeb.ptl
// ------------------------------------------------------------
// 0x5BEE60 sub_5BEE60 —— 毒网弹生成（PoisonWeb.ptl，参数 60/10/4 挂 this+2151 槽）
// 与 ·0x5BEDB0 同构（差异：资源换为 Particle/PoisonWeb.ptl）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEE60(uint32_t *this)
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/PoisonWeb.ptl",
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v2 + 580))(this, *(this + 2151), 0, v3);
}



// 毒气技能：GAS_OUT 播报（this+8616 相位）
// ------------------------------------------------------------
// 0x5BEEA0 sub_5BEEA0 —— 蜘蛛·毒气释放（GAS_OUT 播报，效果号 48003 挂 this+2155）
// 先 ·sub_5BECF0 吐丝门推进；大状态 8 且未命中(this+1757==0)、动作帧 +148 ≥ 2、相位 this+8616==0 且 vt+308 有效 → 8616=1 锁相位、vt+152(0,10,4) 生成特效、vt+580 以 48003 号挂 this+2155 槽（朝向反时偏 20）、vt+212 播报 GAS_OUT 毒气语音。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEEA0(uint32_t *this)
{
  int pThis_6DD; // eax
  int v3; // edi
  int v4; // eax

  sub_5BECF0((int)this);
  pThis_6DD = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
    if ( pThis_6DD == 0 && *(int *)(*(this + 30) + 148) >= 2 )
    {
      LOBYTE(pThis_6DD) = *((uint8_t *)this + 8616);
      if ( (uint8_t)pThis_6DD == 0 )
      {
        LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)pThis_6DD != 0 )
        {
          v3 = *this;
          *((uint8_t *)this + 8616) = 1;
          v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v3 + 152))(
                 this,
                 0,
                 10,
                 4,
                 0,
                 0,
                 0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int))(v3 + 580))(
            this,
            48003,
            *(this + 2155),
            0,
            0,
            v4 != 1 ? 0 : 20);
          LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                         this,
                         "GAS_OUT",
                         -1,
                         0,
                         0);
        }
      }
    }
  }
  return pThis_6DD;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BEF50 sub_5BEF50 —— 蜘蛛·受击反击吐丝（50% 概率门，效果 42005）
// ·sub_4DB480 反击判定为底；门：自身 vt+308 有效、攻击者带 273 倒地标记、rand()%100<50 → 取自身 vt+120/124/128 + 高度一半为爆点，
// ·sub_605840 打包参数后 ·sub_4E4A50 发效果 42005（朝向 vt+152）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEF50(int *this, int nArg2, int nArg3, int nArg4)
{
  int v6; // ebx
  int v7; // edx
  double v8; // st7
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ebx
  int v13; // eax
  int nArg42; // [esp-8h] [ebp-2Ch]
  int v16; // [esp-4h] [ebp-28h]
  float v17; // [esp+Ch] [ebp-18h] BYREF
  float v18; // [esp+10h] [ebp-14h]
  float v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+2Ch] [ebp+8h]

  v6 = sub_4DB480(nArg2, nArg3, nArg4);
  v23 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) == 0
    || rand() % 100 >= 50 )
  {
    return v6;
  }
  v7 = *this;
  nArg4 = 0;
  v17 = 0.0;
  v18 = 0.0;
  v19 = 0.0;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  v8 = (double)(*(int (/*thiscall*/ **)(int *))(v7 + 120))(this);
  v9 = *this;
  v17 = v8;
  v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 124))(this);
  v11 = *this;
  v18 = (float)v10;
  v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 192))(this) / 2;
  v19 = (float)((*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v12);
  v16 = sub_605840(&nArg4, nArg2, &v17, 1);
  nArg42 = nArg4;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  sub_4E4A50(nArg2, 42005, 100, 0, 0, 0, v13, 0, nArg42, v16);
  return v23;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF080 sub_5BF080 —— 消亡通知包装（对自身死亡补发 vt+216 槽 9）
// pArg2 == this 时先 vt+216(this, 9) 补发表现/音效槽事件，再尾调 ·sub_4D9170 消亡通知。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF080(void *this, void *pArg2)
{
  if ( pArg2 == this )
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);
  return sub_4D9170(pArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF0B0 sub_5BF0B0 —— 大状态 0 转发门（转 ·sub_5D8DE0 处理）
// vt+840 大状态为 0 时转 ·sub_5D8DE0（【推断】蜘蛛系空闲态专用处理入口）；其余状态原样返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0B0(void *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result == 0 )
    return sub_5D8DE0(this);
  return result;
}



// 蛛网收束：引用 Particle/Web.ptl（80L；this+204/+208 硬直联动）
// ------------------------------------------------------------
// 0x5BF0D0 sub_5BF0D0 —— 蜘蛛·蛛网悬浮阵列（三槽帧布置 + 倾角重算）
// ·sub_4D54E0 前置；主状态镜像 this+1639==8 且攻击段==3、动作帧 +148 递增且 ≥2 时，记录 this+2191 并循环 vt+208 写帧、
// vt+204 从 dword_72FD88 双表取帧号（随 2191 段数变址）布置 this+2188..2190 三槽。
// 之后 1639==18 或（1639==8 且段3）→ 对三槽逐枚以 atan2(dy/(dz+自身高度),1.0) 由 unk_72FDEC 表算倾角写槽 +88，vt+148==-1 时补 ·sub_4938F0 播放驱动。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0D0(int *this)
{
  int result; // eax
  int v3; // edi
  uint32_t *pThis_88C; // ebx
  int fld_e2191; // eax
  int *pThis_88C2; // ebx
  uint32_t *v7; // edi
  int v8; // ebx
  double v9; // [esp+Ch] [ebp-10h]
  int *i; // [esp+18h] [ebp-4h]

  result = sub_4D54E0();
  if ( *(this + 1639) == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 3 )
    {
      result = *(this + 30);
      if ( result != 0 )
      {
        result = *(uint32_t *)(result + 148);
        if ( result > *(this + 2191) && result >= 2 )
        {
          *(this + 2191) = result;
          v3 = 0;
          pThis_88C = this + 2188;
          do
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_88C);
            fld_e2191 = 2 * (*(this + 2191) - 2 + v3 + 2 * (*(this + 2191) - 2));
            result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
                       this,
                       1,
                       *pThis_88C,
                       dword_72FD88[fld_e2191],
                       dword_72FD8C[fld_e2191],
                       0,
                       0);
            ++v3;
            ++pThis_88C;
          }
          while ( v3 < 3 );
        }
      }
    }
    if ( *(this + 1639) == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 3 )
        goto LABEL_11;
    }
  }
  if ( *(this + 1639) == 18 )
  {
LABEL_11:
    pThis_88C2 = this + 2188;
    v7 = &unk_72FDEC;
    for ( i = this + 2188; ; pThis_88C2 = i )
    {
      v9 = atan2((double)(int)*(v7 - 1) / (double)(*v7 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this)), 1.0);
      result = (int)sub_4938F0(*pThis_88C2);
      v8 = *pThis_88C2;
      if ( *(uint32_t *)(v8 + 148) == -1 )
        result = (int)sub_4938F0(v8);
      *(float *)(v8 + 88) = v9;
      v7 += 2;
      ++i;
      if ( (int)v7 >= (int)"icle/Web.ptl" )
        break;
    }
  }
  return result;
}



// 主状态门（this+200/8617）
// ------------------------------------------------------------
// 0x5BF210 sub_5BF210 —— 蜘蛛·三连蛛网齐射（30100 号挂 this+2155/2156/2157 三槽）
// 门：vt+308 目标有效、动作帧 +148 ≥ 2、this+8617 置位（由 ·0x5BFBC0 事件默认支布下）。
// 三槽各以 30100 号参数 60/30/4 发网后解锁 this+8617=0。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BF210(uint8_t *this)
{
  int pThis_C8; // eax

  LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)pThis_C8 != 0 )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    if ( *(int *)(pThis_C8 + 148) >= 2 )
    {
      LOBYTE(pThis_C8) = *(this + 8617);
      if ( (uint8_t)pThis_C8 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
          this,
          30100,
          0,
          *((uint32_t *)this + 2155),
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
          this,
          30100,
          0,
          *((uint32_t *)this + 2156),
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                       this,
                       30100,
                       0,
                       *((uint32_t *)this + 2157),
                       0,
                       60,
                       0,
                       30,
                       4,
                       0,
                       0,
                       0);
        *(this + 8617) = 0;
      }
    }
  }
  return pThis_C8;
}



// Boss 弹幕：引用 Particle/BossMissile{1,3,2,4}.ptl 四连发（75L）
// ------------------------------------------------------------
// 0x5BF2D0 sub_5BF2D0 —— Boss·导弹齐射（BossMissile1/3/2/4.ptl，30200 号 × this+2161 发）
// vt+588 装载四条弹道资源，发数 this+2161（·0x5BFBC0 事件1 布 rand%3+2）、发射 Y 取目标 this+1813 vt+124。
// 满 count 发以 60/30/4 参数下发 30200 号后计数清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF2D0(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int result; // eax
  int fld_e1813; // ecx
  bool fld_e2161; // cc
  int v10; // eax
  int fld_e21612; // ecx
  uint32_t v12[4]; // [esp+8h] [ebp-80h]
  int v13; // [esp+18h] [ebp-70h]
  int v14; // [esp+1Ch] [ebp-6Ch]
  uint8_t v15[100]; // [esp+20h] [ebp-68h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v2 = *this;
  v13 = 0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v2 + 588))(this, "Particle/BossMissile1.ptl");
  v4 = *this;
  v12[0] = v3;
  v12[1] = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(this, "Particle/BossMissile3.ptl");
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BossMissile2.ptl");
  v6 = *this;
  v12[2] = v5;
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v6 + 588))(this, "Particle/BossMissile4.ptl");
  fld_e1813 = *(this + 1813);
  v12[3] = result;
  if ( fld_e1813 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813);
    v13 = result;
  }
  fld_e2161 = *(this + 2161) <= 0;
  v14 = 0;
  if ( fld_e2161 )
  {
    *(this + 2161) = 0;
  }
  else
  {
    do
    {
      v10 = *this;
      qmemcpy(v15, (const void *)v12[v14], 0x62u);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint8_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v10 + 580))(
        this,
        30200,
        v13,
        v15,
        0,
        60,
        0,
        30,
        4,
        0,
        0,
        0);
      fld_e21612 = *(this + 2161);
      result = ++v14;
    }
    while ( v14 < fld_e21612 );
    *(this + 2161) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF3D0 sub_5BF3D0 —— 蜘蛛·冲撞准备（速率轴清位 + 姿态档 4 提交）
// vt+876 速率双轴清零、vt+896 以 vt+152(4) 取硬直姿态档、·sub_4A0550(600) 速率/镜头参数【推断】；this+2159 置 1 标记冲撞段。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF3D0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 896))(this, v3);
  result = sub_4A0550(600);
  *(this + 2159) = 1;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF430 sub_5BF430 —— 档位换算表（·sub_456390(0) 查询 → 2/3/4/6）
// 查询值 1/2/3/4 依次映射 2/3/4/6，其余归 0；【推断】阶段/机关档位号转换。
// ------------------------------------------------------------
int sub_5BF430()
{
  int result; // eax

  switch ( sub_456390(0) )
  {
    case 1:
      result = 2;
      break;
    case 2:
      result = 3;
      break;
    case 3:
      result = 4;
      break;
    case 4:
      result = 6;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF480 sub_5BF480 —— 主播放门（大状态 18/16 免转发）
// vt+840 为 18 或 16 时直接返回，否则转 ·sub_499FF0 主播放驱动·usercall 变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF480(void *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result != 18 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
    if ( result != 16 )
      return sub_499FF0(this);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF4B0 sub_5BF4B0 —— 主状态镜像2 分发（14 → 茧位移，15 → 清位）
// ·sub_4E1780 帧推进后：this+1639==14 转 ·sub_5BE940 茧载人位移；==15 转 vt+312(0) 清硬直位。
// ------------------------------------------------------------
int /*usercall*/ sub_5BF4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax

  sub_4E1780(pArg1);
  if ( pArg1[1639] == 14 )
    return sub_5BE940(pArg1, nArg2, nArg3);
  result = pArg1[1639] - 15;
  if ( pArg1[1639] == 15 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
  return result;
}



// 时钟门 AI（sub_699000; this+8618）
// ------------------------------------------------------------
// 0x5BF4E0 sub_5BF4E0 —— 定时解锁门（clock_now 到期 → this+8618=0 + setState 0）
// 读 this+6560 区时钟 +24 到期时刻，·sub_699000 当前时刻 ≥ 到期 → this+8618=0 并 vt+560 setState(0 待机)。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF4E0(uint8_t *this)
{
  int pThis_19A0; // ecx
  int v3; // edi
  int result; // eax
  int v5; // eax

  pThis_19A0 = (int)(this + 6560);
  v3 = *(uint32_t *)(pThis_19A0 + 24);
  result = sub_699000(pThis_19A0);  // 【clock_now(clk)】
  if ( result >= v3 )
  {
    v5 = *(uint32_t *)this;
    *(this + 8618) = 0;
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 560))(this, 0, 0, 0, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF520 sub_5BF520 —— 茧跟随位移（帧长计时抄送猎物 X）
// nArg2 == this+2152 猎物、大状态 14、this+2154 搬运剩余 >1 时：以 this+1554+4 帧值经 ·sub_491C10 取计时阈值累加 this+2155，满 5% 帧长则 --2154 并归零 2155。
// 随后取猎物 vt+916 位移前后 X 差，自身 X 减去该差随动【推断：与猎物同步平移】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF520(uint32_t *this, int nArg2)
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2155; // edx
  int fld_e2152; // edi
  int fld_e21522; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2152) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2154) > 1 )
    {
      fld_e1554 = sub_491C10(*(uint32_t *)(*(this + 1554) + 4));
      fld_e2155 = *(this + 2155) + 1;
      *(this + 2155) = fld_e2155;
      if ( fld_e2155 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2154);
        *(this + 2155) = 0;
      }
      fld_e2152 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 916))(*(this + 2152));
      fld_e21522 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));
      v8 = *this;
      v9 = fld_e2152 - fld_e21522;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（90L；sub_4049C0 插值）
// ------------------------------------------------------------
// 0x5BF5F0 sub_5BF5F0 —— 蜘蛛·HOLD 蓄力起手（273 标记目标捕获 + 段时长插值）
// pArg2+4 取目标：vt+40(273) 校验且 vt+128>0 才写 this+2152 并冻结目标 vt+604(0)/vt+612(0,0)/vt+848(1)；目标三轴存 this+2156..2158。
// vt+384(0)/vt+384(1) 与 vt+672(3) 段参数经 ·sub_4049C0 插值写入 this+2154（位移段时长），this+2153/2155 归零，vt+212 播报 HOLD。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF5F0(uint32_t *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2152; // ecx
  int v6; // eax
  int fld_e21522; // ecx
  int v8; // eax
  int fld_e21523; // ecx
  int v10; // eax
  int fld_e21524; // ecx
  uint32_t *fld_e28; // edi
  int fld_e1821; // edi
  uint32_t *v14; // eax
  uint64_t fld_e1820; // rax
  float v17; // [esp+6Ch] [ebp-20h]
  float v18; // [esp+70h] [ebp-1Ch]
  int v19; // [esp+88h] [ebp-4h]
  int v20; // [esp+94h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) == 0
    || (*(this + 2152) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2152) = 0;
  }
  fld_e2152 = *(this + 2152);
  if ( fld_e2152 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);
    fld_e21522 = *(this + 2152);
    *(this + 2156) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522);
    fld_e21523 = *(this + 2152);
    *(this + 2157) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);
    fld_e21524 = *(this + 2152);
    *(this + 2158) = v10;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e21524 + 604))(fld_e21524, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2152) + 612))(*(this + 2152), 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 852))(*(this + 2152)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 848))(*(this + 2152), 1);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v18 = (float)v20;
  v17 = (float)v19;
  fld_e1820 = (uint64_t)sub_4049C0(v17, v18, *v14 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2154) = fld_e1820;
  *(this + 2153) = 0;
  *(this + 2155) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(HIDWORD(fld_e1820) + 212))(
           this,
           "HOLD",
           -1,
           0,
           0);
}



// AI 相位辅助（this+8600）
// ------------------------------------------------------------
// 0x5BF7E0 sub_5BF7E0 —— 事件提交基函数（大状态 8/6 分支 + 随机速率微调）
// vt+840 读大状态、vt+184/vt+188 取双子类型 v6/v22，·sub_4E33D0 提交事件；ArgList!=8 时 vt+208 写入 1554 首帧。
// 大状态 8 且命中段 == this+2152 → this+8600=0、·sub_4926A0 帧复位、vt+204(1000,...) 重播；大状态 6 → vt+896(v6,v22) 姿态。
// v6!=4 时经 vt+672(3) 与 ·sub_4954C0 折算速率 ×1/4 写 vt+876；v22!=4 时 rand()%100 二分档 ×1/8 或 ×1/4【推断：随机包抄速率】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5BF7E0(uint32_t **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // edi
  uint32_t *result; // eax
  int *fld_e1554; // eax
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int nRand; // et2
  uint32_t *v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // [esp+Ch] [ebp-4h]

  ((void (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
  v6 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[46])(this);
  v22 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[47])(this);
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList != 8 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 )
  {
    result = (uint32_t *)sub_41A5E0((unsigned int)(this + 1757));
    if ( result == *(this + 2152) )
    {
      fld_e1554 = *(this + 1554);
      *((uint8_t *)this + 8600) = 0;
      sub_4926A0(*fld_e1554);
      return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
                         this,
                         1000,
                         **(this + 1554),
                         0,
                         0,
                         0,
                         0);
    }
  }
  else
  {
    result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
    if ( result == (uint32_t *)6 )
    {
      result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v6, v22);
      if ( v6 != 4 )
      {
        v9 = *this;
        v10 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        v11 = sub_4954C0(v10);
        v12 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v11 / 10);
        v13 = sub_4954C0(v12);
        result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))v9[219])(this, 0, v13 / 4);
      }
      if ( v22 != 4 )
      {
        nRand = rand() % 100;
        v15 = *this;
        v16 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        v17 = sub_4954C0(v16);
        if ( nRand >= 50 )
        {
          v20 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v17 / 20);
          v21 = sub_4954C0(v20);
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))v15[219])(this, 1, v21 / 8);
        }
        else
        {
          v18 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v17 / 10);
          v19 = sub_4954C0(v18);
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))v15[219])(this, 1, v19 / 4);
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（this+8618）
// ------------------------------------------------------------
// 0x5BF9E0 sub_5BF9E0 —— 蜘蛛·滚动起步（速率表提交 + 350ms 倒计时锁 this+8618）
// vt+672(3) 段参数 +816/+830 处两族表值相乘写 vt+876 双轴速率；物理面 +16 水平速率按 vt+152 朝向取 ±600.0f（方向翻转）。
// 随后 ·sub_4926A0 帧复位、vt+196 切 1554+4 动画、vt+344 挂 this+139 档、this+6573/6574 清零、·sub_698F90(this+1640, 350) 倒计时、this+8618=1 上锁。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BF9E0(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  float v4; // eax
  int v5; // eax
  int *fld_e28; // edi
  int pObj; // ecx
  int v8; // eax
  char result; // al
  int v10; // [esp+Ch] [ebp-Ch]
  float v11; // [esp+10h] [ebp-8h]
  int v12; // [esp+14h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = sub_41A5E0(v2 + 816);
  v11 = COERCE_FLOAT(sub_41A5E0(v2 + 830));
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v10 = sub_41A5E0(v3 + 816);
  v4 = COERCE_FLOAT(sub_41A5E0(v3 + 830));
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    (uint64_t)((double)v10 * v4) >> 32,
    0,
    (uint64_t)((double)v10 * v4),
    (uint64_t)((double)v12 * v11),
    0,
    0,
    0);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  fld_e28 = (int *)*(this + 28);
  pObj = *fld_e28;
  if ( v5 == 1 )
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )
      goto LABEL_10;
    v8 = 1142292480;
  }
  else
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )
      goto LABEL_10;
    v8 = -1005191168;
  }
  if ( fld_e28[4] != v8 )
  {
    fld_e28[4] = v8;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
LABEL_10:
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
  *((uint8_t *)this + 6573) = 0;
  *((uint8_t *)this + 6574) = 0;
  result = sub_698F90((int)(this + 1640), 350, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 8618) = 1;
  return result;
}



// 硬直字段（this+204/+208/8616）
// ------------------------------------------------------------
// 0x5BFB20 sub_5BFB20 —— 帧写入包装 + this+8616 相位解锁
// 转发 ·sub_5BF7E0 后 ArgList!=8 → vt+208 写 this+1554+4 帧；大状态 8 且攻击段 this+7028==0 → this+8616=0、·sub_4926A0 复位、vt+204(1000,...) 重播。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BFB20(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  sub_5BF7E0((uint32_t **)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList != 8 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 0 )
    {
      *(uint8_t *)(this + 8616) = 0;
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
               this,
               1000,
               *(uint32_t *)(*(uint32_t *)(this + 6216) + 4),
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// ============================================================
// 【分区 11】滚动蜘蛛（桥接 0x5C 区 spider_trap.cpp）（0x5BFBC0-0x5C0000）
// 证据：SPIDER_ROLLING_LOOP 滚动循环（174L/148L；this+8652/8653/8673/8674/8748 相位）

// 滚动蜘蛛 AI（174L）：SPIDER_ROLLING_LOOP 播报；this+204/+208 硬直 +
//   8616/8617/8652/8653/8673/8674/8748 相位字段（滚动冲撞状态机【推断】）
// ------------------------------------------------------------
// 0x5BFBC0 sub_5BFBC0 —— 滚动蜘蛛·主事件分发（大状态 8/17/18/19 + ArgList 双轨）
// 大状态 this+1639：8 且段3 → 三槽 this+2188..2190 帧写、段2 → vt+216(9)；18 同样三槽；19/17 → ·sub_495890(2, 2186)。
// ArgList：6 → this+8616=1 待吐气；18 → unk_72FDD0 三槽帧 + vt+196(1547)；19/17/16 → this+2186 与 2159/2160 分段标记；8 → 事件子类型 1..4：1 布 this+2161=rand%3+2 弹幕数、2 → this+2164=10 + SPIDER_ROLLING_LOOP 播报、3 → 2191=-1 且 8748=1、4 → 8673/8674 清零 + 4000ms 倒计时 + 速率清零转段 15；无子类型 → this+8617=1 布三连网。
// 收尾转 ·sub_5BF7E0；大状态 8 且 vt+908==2 时清 8652/8653。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BFBC0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // eax
  uint32_t *pThis_88C; // edi
  int i; // ebx
  uint32_t *pThis_88C2; // edi
  int j; // ebx
  int v11; // edi
  uint32_t *v12; // eax
  int v13; // edx
  int v14; // eax
  uint32_t *v15; // edi
  uint32_t *pThis_88C3; // ebx
  int fld_e1554; // eax
  uint32_t *fld_e15542; // eax
  int result; // eax
  int fld_e1547; // [esp-4h] [ebp-10h]
  int fld_e2186; // [esp-4h] [ebp-10h]

  fld_e1639 = *(this + 1639);
  switch ( fld_e1639 )
  {
    case 8:
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 3 )
      {
        pThis_88C = this + 2188;
        for ( i = 3; i != 0; --i )
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C++);
      }
      else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
      }
      break;
    case 18:
      pThis_88C2 = this + 2188;
      for ( j = 3; j != 0; --j )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C2++);
      break;
    case 19:
    case 17:
      sub_495890(2, *(this + 2186));
      break;
    default:
      break;
  }
  v11 = ArgList;
  if ( ArgList == 6 )
  {
    *((uint8_t *)this + 8616) = 1;
    goto LABEL_40;
  }
  if ( ArgList != 8 )
  {
    switch ( ArgList )
    {
      case 18:
        v14 = *this;
        fld_e1547 = *(this + 1547);
        *(this + 2159) = 0;
        *(this + 2186) = -1;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v14 + 196))(this, fld_e1547);
        v15 = &unk_72FDD0;
        pThis_88C3 = this + 2188;
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
            this,
            1,
            *pThis_88C3,
            *v15,
            v15[1],
            0,
            0);
          v15 += 2;
          ++pThis_88C3;
        }
        while ( (int)v15 < (int)&dword_72FDE8 );
        v11 = 18;
        goto LABEL_40;
      case 19:
        fld_e2186 = 2 * *(this + 2186);
        *(this + 2159) = 4;
        sub_495890(2, fld_e2186);
        break;
      case 16:
        fld_e1554 = *(this + 1554);
        *(this + 2160) = 0;
        *(this + 2186) = -1;
        fld_e15542 = (uint32_t *)(fld_e1554 + 24);
LABEL_39:
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *fld_e15542);
        goto LABEL_40;
      case 17:
        sub_495890(2, 2 * *(this + 2186));
        *(this + 2160) = 2;
        break;
      default:
        goto LABEL_40;
    }
    fld_e15542 = (uint32_t *)(*(this + 1554) + 20);
    goto LABEL_39;
  }
  v12 = *(uint32_t **)(LODWORD(fArg3) + 4);
  if ( *v12 != 0 )
  {
    switch ( *v12 )
    {
      case 1:
        *(this + 2161) = rand() % 3 + 2;
        break;
      case 2:
        v13 = *this;
        *(this + 2164) = 10;
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v13 + 212))(
          this,
          "SPIDER_ROLLING_LOOP",
          9,
          0,
          0);
        break;
      case 3:
        *(this + 2191) = -1;
        *((uint8_t *)this + 8748) = 1;
        break;
      case 4:
        *((uint8_t *)this + 8673) = 0;
        *((uint8_t *)this + 8674) = 0;
        sub_698F90((int)(this + 2165), 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v11 = 15;
        break;
      default:
        break;
    }
  }
  else
  {
    *((uint8_t *)this + 8617) = 1;
  }
LABEL_40:
  sub_5BF7E0((uint32_t **)this, v11, fArg3, nArg4, nArg5);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( result == 8 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 908))(this);
    if ( result == 2 )
    {
      *((uint8_t *)this + 8652) = 0;
      *((uint8_t *)this + 8653) = 0;
    }
  }
  return result;
}


// 滚动蜘蛛·跳跃冲撞（148L；8652/8653 相位）：8652 未置位且命中段≥1 时起跳——
//   水平速度=朝目标 X 差或 dword_72FD68[子类型] 查表、滞空 60~119 帧，随机火花
//   nSparkId=2/3，sub_4A0550 镜头 320；按抛物线(自+24 速度/+36 重力/+16,+20 系数)
//   预算落点，落点不可达则 vt+140 抛射(480)并播 48012 音效，--this[2164](跳跃余量)；
//   落地段(8652 置位后 +192==4) vt+896(4,4) 硬直+帧段 300，高度>查表则切 1554+4 动画
// ------------------------------------------------------------
// 0x5BFE90 sub_5BFE90 —— 滚动蜘蛛·跳跃冲撞（双相驱动，概要见上方既有注释）
// 8652=腾空标记（垂直速度 +24 >0 置位）、8653=落地锁；起跳读 dword_72FD68[子类型] 或目标 X/Y 差设 vt+876 双轴，滞空 rand()%60+60 帧。
// 落地段 +192==4 时 ·sub_424120(挂件+132, 2, 300) 碰撞、vt+896(4,4)、余量 this+2164 递减；高度越过 dword_72FD78[子类型] 切 1554+4 动画。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BFE90(int *this)
{
  int nRand; // ebx
  int nSubType; // eax
  int pTarget; // ecx
  int nDxTarget; // edi
  int nTgtX; // edi
  int nTgtY; // ebx
  int nSparkId; // edi
  int pSelf; // edi
  double fFlightTime; // st7
  double fFlightTime2; // st7
  uint64_t nFlightX; // rax
  int nFlightXi; // edi
  int nX1; // eax
  int pSelf2; // ecx
  int nFlightY; // edi
  int nCurY; // eax
  int pVt; // edx
  int pMountList; // eax
  void *pCurAct; // eax
  char pThis_21CC; // cl
  int pSelf3; // edx
  int nSubType2; // edi
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi
  float v26; // [esp+4h] [ebp-Ch]
  int v27; // [esp+8h] [ebp-8h] BYREF
  int v28; // [esp+Ch] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 2 )
    return;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    if ( *(int *)(*(this + 30) + 148) >= 1 )
    {
      if ( *((uint8_t *)this + 8652) != 0 )
      {
LABEL_11:
        if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )
        {
          pMountList = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
          sub_424120(*(uint32_t **)(pMountList + 132), 2, 300);
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
          if ( *(this + 2164) > 0 )
          {
            pCurAct = (void *)(*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
            sub_4AECE0(pCurAct, 0);
            *((uint8_t *)this + 8652) = 0;
            *((uint8_t *)this + 8653) = 0;
          }
        }
        goto LABEL_15;
      }
      nRand = rand() % 60 + 60;
      nSubType = sub_41A5E0((unsigned int)(this + 1757));
      pTarget = *(this + 1813);
      nDxTarget = dword_72FD68[nSubType];
      if ( pTarget != 0 )
      {
        nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 120))(pTarget);
        nDxTarget = nTgtX - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        nTgtY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
        nRand = nTgtY - (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, nDxTarget, nDxTarget, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, nRand, nRand, 0, 0, 0);
      rand();
      nSparkId = (rand() % 100 >= 50) + 2;
      sub_4A0550((float *)*(this + 28), 320);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, nSparkId, nSparkId);
      pSelf = *(this + 28);
      fFlightTime = *(float *)(pSelf + 24) * -1000.0 / (double)*(int *)(pSelf + 36);
      fFlightTime2 = (double)(int)(uint64_t)(fFlightTime + fFlightTime);
      v26 = fFlightTime2;
      nFlightX = (uint64_t)(fFlightTime2 * *(float *)(pSelf + 16) * 0.001);
      nFlightXi = nFlightX;
      nX1 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 120))(this, HIDWORD(nFlightX));
      pSelf2 = *(this + 28);
      v28 = nFlightXi + nX1;
      nFlightY = (uint64_t)(v26 * *(float *)(pSelf2 + 20) * 0.001);
      nCurY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      pVt = *this;
      v27 = nFlightY + nCurY;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(pVt + 136))(this, v28, nFlightY + nCurY, 0) == 0 )
        (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, uint32_t, int))(*this + 140))(
          this,
          &v28,
          &v27,
          v28,
          v27,
          480,
          0,
          1);
      sub_4E4A50(nFlightY, (int)this, 48012, 1, v28, v27, 0, 0, 0, 0, 0);
      --*(this + 2164);
    }
    if ( *((uint8_t *)this + 8652) != 0 )
      goto LABEL_11;
  }
LABEL_15:
  pThis_21CC = *((uint8_t *)this + 8652);
  if ( pThis_21CC != 0 && *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )
    *((uint8_t *)this + 8653) = 1;
  pSelf3 = *(this + 28);
  if ( *(float *)(pSelf3 + 24) > 0.0 && pThis_21CC == 0 )
    *((uint8_t *)this + 8652) = 1;
  if ( *((uint8_t *)this + 8652) != 0 )
  {
    if ( *(float *)(pSelf3 + 24) > 0.0 )
    {
      nSubType2 = sub_41A5E0((unsigned int)(this + 1757));
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > dword_72FD78[nSubType2] )
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 4);
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e1554 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
          sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
        }
      }
    }
    if ( *((uint8_t *)this + 8652) != 0
      && *(float *)(*(this + 28) + 24) < 0.0
      && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < 100 )
    {
      fld_e15542 = (uint32_t *)(*(this + 1554) + 8);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e15542 )
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));
      }
    }
  }
}


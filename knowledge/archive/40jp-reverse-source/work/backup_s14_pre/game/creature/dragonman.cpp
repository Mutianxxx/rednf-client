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
int /*usercall*/ sub_5B00D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：龙人·压制反击概率门（setState 22 起手）
{
  int pTarget; // edi
  int nRand; // edx
  int result; // eax

  sub_5AFE80();  // 调 协同自检 → vt+840 大状态须 0、vt+308 目标门、this+1787
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 大状态读取(vt+840→this+6556)
  if ( result == 0 )  // 若 result 为 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家/有目标门(vt+308)
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调虚槽 +840：大状态 getter（this+6556）
      if ( result == 0 && pArg1[1787] != 22 )  // 不在动作22(压制)中
      {
        result = pArg1[1813];  // 当前目标对象【推断：全函数族一致用作攻击目标】
        if ( result != 0 )  // 若结果非 0（成功）
        {
          result = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)result + 40))(17);  // 目标存活标记17
          if ( (uint8_t)result != 0 )
          {
            pTarget = pArg1[1813];  // pTarget = 取 pArg1[1813]
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 840))(pTarget, nArg2) == 8  // 目标大状态8(受击硬直)
              || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 840))(pTarget) == 7  // 或7(浮空)
              || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pTarget + 40))(pTarget, 273)) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
              && (result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 840))(pTarget)) == 12 )  // 或标记273+大状态12(倒地)
            {
              result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pTarget, 0);  // 距离(vt+8)
              if ( result < 100 )  // 距离<100 才够得着压制
              {
                nRand = rand() % 100;  // nRand = 调 rand
                result = pArg1[1908] != 0 ? 20 : 50;  // 概率阈值：20% / 50%
                if ( nRand < result )  // 若 nRand < result
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
int /*thiscall*/ sub_5B00F0(uint32_t *this, int nArg2, int nArg3)  // 实现：龙人·狂暴提速相位（动作速 ×1.3 / 位移速 ×1-1.3）
{
  unsigned int pAniCtrl830; // edi
  int edxTmp; // edx
  int result; // eax
  unsigned int pAniCtrl830b; // edi
  int edxTmp2; // edx
  int fVal830; // [esp+14h] [ebp+8h]
  int fVal830b; // [esp+14h] [ebp+8h]

  if ( nArg2 == 0 )  // 若 nArg2 为 0
  {
    *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.3;  // 动作速度 ×1.3
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;  // 位移速度 ×1/1.3
    pAniCtrl830 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 动画控制柄字段+830【推断：播放速度】
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pAniCtrl830)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl830, edxTmp, fVal830);  // 浮点字段写回(-0.3)
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 提交控制柄
  }
  result = nArg3;
  if ( nArg3 == 0 && nArg2 == 1 )  // 若 nArg3 == 0 与/或 nArg2 == 1
  {
    pAniCtrl830b = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830b = COERCE_FLOAT(sub_41A5E0(pAniCtrl830b)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl830b, edxTmp2, fVal830b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
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
int /*thiscall*/ sub_5B01C0(char *this, int nArg2, int nArg3)  // 实现：龙人·相位复位与减速（0x5B00F0 逆操作）
{
  int result; // eax
  char *pThis_1D73; // ecx
  int pVtTmp; // edx
  unsigned int pAniCtrl830; // edi
  int edxTmp; // edx
  int pVtTmp2; // eax
  unsigned int pAniCtrl830b; // edi
  int edxTmp2; // edx
  int fVal830; // [esp+Ch] [ebp-4h]
  int fVal830b; // [esp+18h] [ebp+8h]

  result = 0;
  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;  // this[1893] = 0
  *((uint32_t *)this + 1892) = 0;  // this[1892] = 0
  *((uint32_t *)this + 1891) = 0;  // this[1891] = 0
  *((uint32_t *)this + 1897) = 0;  // this+7588〔uForm7588〕
  *((uint32_t *)this + 1896) = 0;  // this+7584〔uForm7584〕
  *((uint32_t *)this + 1895) = 0;  // this[1895] = 0
  *((uint32_t *)this + 1894) = 0;  // this[1894] = 0
  *((uint32_t *)this + 1899) = 0;  // this[1899] = 0
  *((uint32_t *)this + 1895) = 1;  // 相位标志置 1【推断：常规相位】
  if ( nArg2 == 0 )  // 若 nArg2 为 0
  {
    *(float *)(*((uint32_t *)this + 1905) + 4) = *(float *)(*((uint32_t *)this + 1905) + 4) * 0.76923078;  // 动作速度还原
    *(float *)(*((uint32_t *)this + 1905) + 68) = *(float *)(*((uint32_t *)this + 1905) + 68) * 1.3;  // 位移速度还原
    pVtTmp = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    pAniCtrl830 = (*(int (/*thiscall*/ **)(char *, uint32_t))(pVtTmp + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pAniCtrl830)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl830, edxTmp, fVal830);  // 浮点字段写回(+0.3，与提速相位反向)
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  }
  if ( nArg3 == 0 && nArg2 == 1 )  // 若 nArg3 == 0 与/或 nArg2 == 1
  {
    pVtTmp2 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
    pAniCtrl830b = (*(int (/*thiscall*/ **)(char *, uint32_t))(pVtTmp2 + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830b = COERCE_FLOAT(sub_41A5E0(pAniCtrl830b)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl830b, edxTmp2, fVal830b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
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
int /*thiscall*/ sub_5B0320(int *this)  // 实现：龙人·挂载物脉冲/位移判定
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
LABEL_2:  // 标签 LABEL_2（跳转合流点）
  while ( 1 )  // 条件循环
  {
    nSlotIdxSaved = nSlotIdx;
    pVecHdr = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);  // 取挂载对象列表(vector: +4 begin/+8 end)
    pVecBegin = *(uint32_t *)(pVecHdr + 8);
    pVecHdrB = pVecHdr + 4;
    result = pVecBegin != 0 ? (*(uint32_t *)(pVecHdrB + 8) - pVecBegin) >> 2 : 0;  // 元素数
    if ( (int)nSlotIdx >= result )
      return result;
    pVecHdr2 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    pVecBegin2 = *(uint32_t *)(pVecHdr2 + 8);
    if ( pVecBegin2 != 0 && nSlotIdx < (*(uint32_t *)(pVecHdr2 + 12) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
      pListObj = *(uint32_t *)(pVecBegin2 + 4 * nSlotIdx);
    else  // 否则分支
      pListObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 17) != 0 )  // 存活标记17
    {
      pVecHdr3 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      pVecBegin3 = *(uint32_t *)(pVecHdr3 + 8);
      if ( pVecBegin3 != 0 && nSlotIdx < (*(uint32_t *)(pVecHdr3 + 12) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
        pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nSlotIdx);
      else  // 否则分支
        pListObj2 = 0;
      if ( (uint8_t)sub_4E4630(pListObj2) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
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
        nRandY = rand();  // nRandY = 调 rand
        pVtSaved = *pThis;
        nDy = nRandY % 50 - 25;  // Y 抖动 ±25
        nJumpY = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pListObj2 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
                pListObj2,
                30071,  // 对象/特效 ID【推断】
                10,
                0,
                4,
                100,
                1,
                0,
                0);
        nJumpX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 120))(pListObj2, nDy + nJumpY);  // 调虚槽 +120：动画对象
        nJumpY2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pListObj2 + 124))(pListObj2, 0, nDx + nJumpX);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nJumpX2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 120))(pListObj2, nDy + nJumpY2);  // 调虚槽 +120：动画对象
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
int /*thiscall*/ sub_5B04A0(int *this, int nArg2, int nArg3, int nArg4)  // 实现：龙人·召唤物激活与成长（带反击回退）
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
  char bBoundOrActivated; // [esp+17h] [ebp+Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // 存活标记17
  {
    bBoundOrActivated = 0;
    pListVec = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 取对象列表
    pVecBegin = *(uint32_t *)(pListVec + 4);
    nIdx = 0;
    if ( pVecBegin != 0 )  // 若 pVecBegin 非 0
      nListCnt = (*(uint32_t *)(pListVec + 8) - pVecBegin) >> 2;  // 向量元素数 = (end−begin)/4
    else  // 否则分支
      nListCnt = 0;
    if ( nListCnt <= 0 )  // 若 nListCnt <= 0
    {
LABEL_12:  // 标签 LABEL_12（跳转合流点）
      pThis = this;
    }
    else  // 否则分支
    {
      while ( 1 )  // 条件循环
      {
        pVecBegin2 = *(uint32_t *)(pListVec + 4);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
          pListObj = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else  // 否则分支
          pListObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj + 92))(pListObj) != 0 )  // 找首个有效项
          break;  // 跳出循环/分支
        if ( (int)++nIdx >= nListCnt )
          goto LABEL_12;
      }
      pVecBegin3 = *(uint32_t *)(pListVec + 4);
      if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
        pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
      else  // 否则分支
        pListObj2 = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pListObj2 + 76))(pListObj2, 0);  // 激活
      pThis = this;
      sub_4DB130(24, 0);  // 播 24 号音效【推断】
      bBoundOrActivated = 1;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 956))(nArg2);  // 调虚槽 +956
    }
    for ( i = 0; i < 16; ++i )  // 循环：i 从 0 递增到 16
    {
      if ( sub_496F80(i) == 16 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 776))(nArg2, i) != 0 )  // 槽类型16
      {
        pSlotObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 772))(nArg2, i);  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
        (*(void (/*thiscall*/ **)(int, uint32_t, int *))(*(uint32_t *)pSlotObj + 4))(pSlotObj, 0, pThis);  // 绑定宿主
        goto LABEL_19;
      }
    }
    if ( bBoundOrActivated != 1 )  // 若 bBoundOrActivated != 1
      return sub_5AFB00(this, nArg2, nArg3, nArg4);  // 攻击态反击追加执行与伤害日志
    pThis = this;
LABEL_19:  // 标签 LABEL_19（跳转合流点）
    pCtrl0 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pThis + 672))(pThis, 0);  // 调虚槽 +672：自身 HP
    nGrowthBase = sub_41A5E0(pCtrl0 + 60);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( (double)pThis[2160] + (double)pThis[2160] > (double)(int)(uint64_t)((double)nGrowthBase
                                                                               * COERCE_FLOAT(sub_41A5E0(pCtrl0 + 74))) )  // 阈值 = 基准×成长系数
    {
      pCtrl74 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 74;  // 调虚槽 +672：自身 HP
      *(float *)&fGrowthVal = COERCE_FLOAT(sub_41A5E0(pCtrl74)) + 0.1;  // 每次成长 +0.1
      sub_41A590(pCtrl74, edxTmp, fGrowthVal);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
  }
  return sub_5AFB00(this, nArg2, nArg3, nArg4);  // 攻击态反击追加执行与伤害日志
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
int /*thiscall*/ sub_5B0660(uint32_t *this)  // 实现：龙人·语音槽与属性注册（构造期）
{
  int nPropVal; // [esp+4h] [ebp-4h] BYREF

  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("DRAGONMAN_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_FIND", 0xEu);  // 【std::string构造赋值】
  *(this + 2151) = 0;  // 囚笼对象槽清空
  *(this + 2152) = sub_699000((int)(this + 9));  // 冷却截止=当前时钟
  nPropVal = 100000;
  return sub_4E1390(196614, &nPropVal);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// 龙人·随机普攻：50% 概率 + 目标存活 + 距离<100 时 setState(8)，
//   参数包 aArgList[0]=rand()%3 → 0/1/2 = 短爪/蓄电/长突 三选一（由 0x5B0D10 case 8 消费）
// ------------------------------------------------------------
// 0x5B0700 sub_5B0700 —— 龙人·随机普攻抽选（setState 8）
// 概率门：rand()%100<50、目标 this[1813] 存活（vt+40 标记 17）、距离（vt+8）<100。
// 参数表经 ·sub_431230 打包，aArgList[0]=rand()%3 为普攻子型（0/1/2 短爪/蓄电/长突），由 ·0x5B0D10 case 8 消费。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0700(uint32_t *this)  // 实现：龙人·随机普攻抽选（setState 8）
{
  uint8_t pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int nPad1; // [esp+Ch] [ebp-18h]
  int nPad2; // [esp+10h] [ebp-14h]
  uint32_t aArgList[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50  // 50% 概率触发（rand()%100 < 50）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0  // 目标存活标记17
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 100 )  // 距离<100
  {
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
    aArgList[3] = 0;
    aArgList[0] = rand() % 3;  // 普攻子类型 0..2
    sub_431230((int)pBuf, aArgList);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // setState(8)
    if ( Block != nullptr )  // 若 Block 有效（非空）
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
char /*thiscall*/ sub_5B07C0(uint32_t *this)  // 实现：龙人·残血闪离/幻觉分身门控
{
  int pVt; // eax
  int pVt2; // edi
  int nZ; // eax
  int nX; // eax
  int pVt3; // edi
  int nZ2; // eax
  int nX2; // eax
  void *pBuf[4]; // [esp+Ch] [ebp-24h] BYREF
  float fld_e29; // [esp+1Ch] [ebp-14h] BYREF
  int nHpTmp; // [esp+20h] [ebp-10h]
  int nEvtSlot; // [esp+2Ch] [ebp-4h]

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
  nHpTmp = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
  pVt = *this;
  fld_e29 = (float)nHpTmp;  // 现血
  nHpTmp = (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 740))(this);  // 满血
  if ( (double)nHpTmp * 0.5 <= fld_e29 )  // 血线 > 50% 则不触发
    return 0;
  pVt2 = *this;
  nZ = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nZ);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 136))(this, nX - 80) != 1 )  // 左 80px 可站立
    return 0;
  pVt3 = *this;
  nZ2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nZ2);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(pVt3 + 136))(this, nX2 + 80) != 1 )  // 右 80px 可站立
    return 0;
  memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
  nEvtSlot = 0;
  LODWORD(fld_e29) = rand() % 2;  // 闪离方向 0/1
  sub_431230((int)pBuf, &fld_e29);  // uint32 vector push_back
  fld_e29 = COERCE_FLOAT(sub_460230(*(this + 29)));  // 移速查表
  sub_431230((int)pBuf, &fld_e29);  // uint32 vector push_back
  (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 15, pBuf, 2, 0);  // setState(15) 幻觉分身
  sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  return 1;  // 返回 1(成功)
}



// 龙人·第4普攻（施法/雷电波）：阶段字段==3 时 setState(8) 且参数包固定 aArgList[0]=3
//   → 0x5B0D10 case 8 子类型3 走 DRAGONMAN_CAST + SPARK_LOOP 蓄电分支
// ------------------------------------------------------------
// 0x5B0930 sub_5B0930 —— 龙人·第4普攻（雷电施法）触发
// 门控：vt+308 目标门 且 this[1943]==3（阶段3 困难级）才发。
// 参数表经 ·sub_431230 打包，固定 aArgList[0]=3（施法子型），由 vt+560 setState(8) 发送，
// 交由 ·0x5B0D10 case 8 子型3 播 DRAGONMAN_CAST 并接 DRAGONMAN_SPARK_LOOP。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0930(uint32_t *this)  // 实现：龙人·第4普攻（雷电施法）触发
{
  uint8_t pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int nPad1; // [esp+Ch] [ebp-18h]
  int nPad2; // [esp+10h] [ebp-14h]
  uint32_t aArgList[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1943) == 3 )  // 阶段3
  {
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
    aArgList[3] = 0;
    aArgList[0] = 3;  // 子类型 3 = 施法
    sub_431230((int)pBuf, aArgList);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // setState(8)
    if ( Block != nullptr )  // 若 Block 有效（非空）
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
int /*usercall*/ sub_5B09C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：龙人·囚笼技（JAIL 牢笼投放）
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *pCageObj; // eax
  int nTgtX; // edi
  bool bTgtRight; // cc
  int nSelfX; // edi
  int pVtSelf; // edi
  int nTgtBaseY; // ebx
  int nSelfBaseY; // eax
  int nCageY; // eax
  void *Block; // [esp+4h] [ebp-14h]
  int nAbsDx; // [esp+8h] [ebp-10h]

  result = pArg1[1813];  // 当前目标
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( pArg1[2151] == 0 )  // 囚笼对象懒加载
    {
      pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pCageObj = sub_428F30(pMem, (int)"PassiveObject/MapObject/Trap/Particle/Cage.ptl", 0);  // CNRDObjectParticleCreater 构造
      else  // 否则分支
        pCageObj = nullptr;  // pCageObj = 空指针
      pArg1[2151] = pCageObj;
    }
    nTgtX = (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);  // 目标坐标
    bTgtRight = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < nTgtX;  // 目标在自身哪一侧
    nSelfX = (*(int (**)(void))(*(uint32_t *)pArg1[1813] + 120))();  // 调虚槽 +120：动画对象
    if ( bTgtRight )
      nAbsDx = nSelfX - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
    else  // 否则分支
      nAbsDx = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - nSelfX;  // |ΔX| 摆位
    pVtSelf = *pArg1;
    Block = (void *)pArg1[2151];
    nTgtBaseY = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813], 500, 4, 0);  // 目标基准 500/4
    nSelfBaseY = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nCageY = (*(int (/*thiscall*/ **)(void *, uint32_t, int, int))(*(uint32_t *)Block + 28))(Block, 0, nAbsDx, nTgtBaseY - nSelfBaseY);  // 囚笼定位
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(pVtSelf + 580))(pArg1, 267, 0, nCageY);  // 发射对象267
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
char /*thiscall*/ sub_5B0AF0(uint32_t *this)  // 实现：龙人·动作相位机（按 this+1787 行为字分发）
{
  char result; // al
  int pTarget7252; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // edi
  int pObj; // edi
  int nTgtX2; // ebx

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // 当前动作 id
  {
    case 0:  // 登场
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调虚槽 +1284
      if ( *(this + 1943) != 3 )  // 非阶段3 不播 BGM
        goto LABEL_24;
      sub_406D60("B_RAKIUS_01");  // 登场曲写 BGM 槽
      return sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
    case 4:  // 走位 A
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_14;
      if ( rand() % 100 >= 20 )  // 20% 概率推进
        goto LABEL_24;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      return sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
    case 5:  // 走位 B
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_14;
      if ( rand() % 100 >= 30 )  // 30% 概率回 4
        goto LABEL_24;
      goto LABEL_5;
    case 0xD:  // 13/14/15：受击/僵直态
    case 0xE:
    case 0xF:
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_24;
LABEL_5:  // 标签 LABEL_5（跳转合流点）
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 恢复走位
      result = sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
      break;  // 跳出循环/分支
    case 0x16:  // 22 压制中
      if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      {
        pTarget7252 = *(this + 1813);  // this+7252〔pTarget7252〕
        if ( pTarget7252 != 0  // 若 fld_e1813 非 0
          && ((fld_e18132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 120))(pTarget7252),  // 调虚槽 +120：动画对象
               (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < fld_e18132)  // 目标在前方
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0  // 朝向 0
           || (pObj = *(this + 1813),  // this+7252〔pTarget7252〕
               (nTgtX2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj))  // 目标在后方
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1) )  // 朝向 1
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 朝向正确 → 走位 5
          result = sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
        }
        else  // 否则分支
        {
          if ( rand() % 100 < 20 )  // 20% 概率接普攻
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
            sub_5B0700(this);  // 龙人·随机普攻抽选（setState 8）
          }
LABEL_24:  // 标签 LABEL_24（跳转合流点）
          result = sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
        }
      }
      else  // 否则分支
      {
LABEL_14:  // 标签 LABEL_14（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 无目标 → 13
        result = sub_5B07C0(this);  // 龙人·残血闪离/幻觉分身门控
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
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
int /*thiscall*/ sub_5B0CF0(int *this)  // 实现：龙人·每帧 AI 总入口
{
  int result; // eax

  sub_5B0AF0(this);  // 龙人·动作相位机（按 this+1787 行为字分发）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
    return sub_5B0320(this);  // 龙人·挂载物脉冲/位移判定
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
void /*userpurge*/ sub_5B0D10(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)  // 实现：龙人·动作事件总分发（大状态 × 事件码二维派发）
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
    if ( ArgList != 16 )  // 若 ArgList != 16
      return;
    goto LABEL_23;
  }
  if ( nBigState != 0 )  // 若 nBigState 非 0
  {
    if ( nBigState == 14 )  // 护盾态
    {
      if ( ArgList != 14 )  // 若 ArgList != 14
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));  // pDwArg1[1554]=this+6216 技能资源表【推断：+4..+20 为动画/特效句柄组】
        (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);  // 调虚槽 +216：音效 TAG 查询
      }
    }
    else if ( nBigState == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )  // 普攻态子类型3(施法)
    {
      if ( ArgList == 8 )  // 若 ArgList == 8
      {
LABEL_14:  // 标签 LABEL_14（跳转合流点）
        if ( **(uint32_t **)(pArg4 + 4) == 4  // 参数[0]==4 → JAIL 囚笼取消门
          && (pDwArg1[1813] == 0
           || (uint8_t)sub_5AFE40(pDwArg1[1813]) == 1
           || sub_699000((int)(pDwArg1 + 9)) < (unsigned int)pDwArg1[2152]) )  // 【clock_now(clk)】 囚笼冷却未到
        {
          **(uint32_t **)(pArg4 + 4) = 0;  // pArg4+4〔宿主对象〕
        }
        goto LABEL_19;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 10);  // 调虚槽 +216：音效 TAG 查询
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));  // 调虚槽 +208：定时器移除
    }
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 12);  // 调虚槽 +216：音效 TAG 查询
    *((uint8_t *)pDwArg1 + 8613) = 0;
  }
  if ( ArgList == 8 )  // 若 ArgList == 8
    goto LABEL_14;
LABEL_19:  // 标签 LABEL_19（跳转合流点）
  if ( nBigState == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 && ArgList != 8 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pSkillRes = pDwArg1[1554];  // pSkillRes = 取 pDwArg1[1554]
    pVt = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8601) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(pVt + 208))(pDwArg1, *(uint32_t *)(pSkillRes + 16));  // 调虚槽 +208：定时器移除
    fArg2 = ((double (/*thiscall*/ *)(int *, uint32_t))*(uint32_t *)(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 20));  // 调虚槽 +208：定时器移除
  }
LABEL_23:  // 标签 LABEL_23（跳转合流点）
  sub_4E33D0((int)pDwArg1, pArg4, fArg2, ArgList, pArg4, *(float *)&nArg5, *(float *)&nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 0:  // 空闲事件
      *((uint8_t *)pDwArg1 + 8613) = 0;
      break;  // 跳出循环/分支
    case 8:  // 普攻事件
      pVt2 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8612) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(pVt2 + 212))(pDwArg1, "DRAGONMAN_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      switch ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) )  // 普攻子类型(this+7028)
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pDwArg1,
            "DRAGONMAN_ATK_SHORT",  // 标签 DRAGONMAN_ATK_SHORT
            -1,
            0,
            0);
          break;  // 跳出循环/分支
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pDwArg1,
            "DRAGONMAN_STATIC_READY_LOOP",  // 标签 DRAGONMAN_STATIC_READY_LOOP
            11,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));  // 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 16),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 20),
            0,
            0,
            0,
            0);
          break;  // 跳出循环/分支
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pDwArg1,
            "DRAGONMAN_ATK_LONG",  // 标签 DRAGONMAN_ATK_LONG
            -1,
            0,
            0);
          break;  // 跳出循环/分支
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
            pDwArg1,
            200,
            *(uint32_t *)(pDwArg1[1554] + 12),
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_CAST", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pDwArg1,
            "DRAGONMAN_SPARK_LOOP",  // 标签 DRAGONMAN_SPARK_LOOP
            10,
            0,
            0);
          break;  // 跳出循环/分支
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          sub_5B09C0(pDwArg1);  // 龙人·囚笼技（JAIL 牢笼投放）
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_JAIL", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
          break;  // 跳出循环/分支
        default:  // 默认分支
          return;
      }
      break;  // 跳出循环/分支
    case 14:  // 护盾事件：DRGM_SHIELD_LOOP
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
        pDwArg1,
        200,
        *(uint32_t *)(pDwArg1[1554] + 8),
        0,
        0,
        0,
        0);
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRGM_SHIELD_LOOP", 9, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      break;  // 跳出循环/分支
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
        else  // 否则分支
          pszResPath1 = pDwArg1[91];  // pszResPath1 = 取 pDwArg1[91]
        hAniHallu1 = sub_431920(pszResPath1, (char)"DLAni/EF_Hallucination1.ani", 1);  // 动画件构造（文件名版）
      }
      if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        pFxObj1 = sub_44E1F0(hAniHallu1, 0);  // CNRDPooledObject 构造（虚表覆盖壳）
      else  // 否则分支
        pFxObj1 = 0;
      pFxHost1 = pDwArg1[29];  // pFxHost1 = 取 pDwArg1[29]
      pDwArg1[2154] = pFxObj1;  // this+8616 幻觉特效1对象槽(事件16销毁用)
      sub_45FE80(pFxHost1, hAniHallu1, 2, 0, pFxObj1, (int)pDwArg1, 0);  // 在自身身上挂幻觉特效1
      pFxObj1Vt = *(uint32_t *)pDwArg1[2154];
      nZ1 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 取自身Z【推断：vt+120/124/128 三级定位链】
      nY1 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX1 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY1);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(pFxObj1Vt + 112))(pDwArg1[2154], nX1);  // 特效1放到本体X处
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          LOBYTE(pszResPath2) = (uint8_t)pDwArg1 + 108;
        else  // 否则分支
          pszResPath2 = pDwArg1[91];  // pszResPath2 = 取 pDwArg1[91]
        hAniHallu2 = sub_431920(pszResPath2, (char)"DLAni/EF_Hallucination2.ani", 1);  // 动画件构造（文件名版）
      }
      else  // 否则分支
      {
        hAniHallu2 = 0;
      }
      if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
        pFxObj2 = (int *)sub_44E1F0(hAniHallu2, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
      else  // 否则分支
        pFxObj2 = nullptr;  // pFxObj2 = 空指针
      sub_45FE80(pDwArg1[29], (int)pFxObj2, 2, 0, (int)pFxObj2, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
      pFxObj2Vt = *pFxObj2;
      nZ2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY2 + 1);  // 分身特效2放在本体下一格X(+1格)【推断】
      (*(void (/*thiscall*/ **)(int *, int))(pFxObj2Vt + 112))(pFxObj2, nX2);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      nCurX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 调虚槽 +120：动画对象
      pVt3 = *pDwArg1;
      pDwArg1[2156] = nCurX;  // this+8624 幻觉期间本体X存档(事件16换位用)
      pDwArg1[2157] = (*(int (/*thiscall*/ **)(int *))(pVt3 + 124))(pDwArg1);  // this+8628 Y存档
      nCurZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      pVt4 = *pDwArg1;
      pDwArg1[2158] = nCurZ;  // this+8632 Z存档
      pAniCtrl3 = (void **)(*(int (/*thiscall*/ **)(int *, int))(pVt4 + 672))(pDwArg1, 3);  // 动画控制柄3【推断：模板/外观槽】
      pCloneObj = sub_4ABE10((void *)0x47, *pAniCtrl3, 0);  // 按模板0x47 克隆分身对象
      pDwArg1[2159] = pCloneObj;  // this+8636 分身对象槽
      pNameSrc = (size_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCloneObj + 340))(pCloneObj) + 4);  // 调虚槽 +340：三元组基址（+284，vt+340）
      pNameBase = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2159] + 340))(pDwArg1[2159]);  // 调虚槽 +340：三元组基址（+284，vt+340）
      sub_4014D0((size_t *)(pNameBase + 4), pNameSrc, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      pCloneVt = *(uint32_t *)pDwArg1[2159];
      nProp376 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);  // 调虚槽 +376：坐标同步包（type 37）
      (*(void (/*thiscall*/ **)(int, int))(pCloneVt + 372))(pDwArg1[2159], nProp376);  // 调虚槽 +372：目标点写入
      pCloneObj5 = pDwArg1[2159];  // pCloneObj5 = 取 pDwArg1[2159]
      pFxHost2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      sub_45FE80(pFxHost2, pCloneVt, 100, nEvtParam2, pCloneObj5, 0, 0);  // 调 实体对象注册到演播层
      pCloneVt2 = *(uint32_t *)pDwArg1[2159];
      nProp152 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(int, int))(pCloneVt2 + 148))(pDwArg1[2159], nProp152);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2159] + 604))(pDwArg1[2159], 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2159] + 112))(pDwArg1[2159], -10000, 0, 0);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*pDwArg1 + 112))(pDwArg1, -10000, 0, 0);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pCloneObj2 = pDwArg1[2159];  // pCloneObj2 = 取 pDwArg1[2159]
      nProp684 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 684))(pDwArg1);  // 调虚槽 +684：取攻击上下文
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pCloneObj2 + 684))(pCloneObj2, nProp684);  // 调虚槽 +684：取攻击上下文
      sub_46AE40(nZ2);  // 子对象数值写入（clong 赋值）
      *(uint8_t *)(pDwArg1[2159] + 8614) = 1;
      break;  // 跳出循环/分支
    case 16:  // 幻觉换位：本体与分身 ±80px 互换（方向按 +4310 标志），销毁特效
      pCloneObj3 = pDwArg1[2159];  // pCloneObj3 = 取 pDwArg1[2159]
      if ( pCloneObj3 != 0 )  // 若 pCloneObj3 非 0
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pCloneObj3 + 604))(pCloneObj3, 1);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 604))(pDwArg1, 1);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
      nSavedX = pDwArg1[2156];  // nSavedX = 取 pDwArg1[2156]
      nSavedX2 = nSavedX;
      if ( *((uint16_t *)pDwArg1 + 4310) != 0 )
      {
        nSelfNewX = nSavedX - 80;
        nCloneNewX = nSavedX2 + 80;
      }
      else  // 否则分支
      {
        nSelfNewX = nSavedX + 80;
        nCloneNewX = nSavedX2 - 80;
      }
      (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 112))(pDwArg1, nSelfNewX, pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pCloneObj4 = pDwArg1[2159];  // pCloneObj4 = 取 pDwArg1[2159]
      if ( pCloneObj4 != 0 )  // 若 pCloneObj4 非 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pCloneObj4 + 112))(pCloneObj4, nCloneNewX, pDwArg1[2157], pDwArg1[2158]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pFxObj1b = pDwArg1[2154];  // pFxObj1b = 取 pDwArg1[2154]
      if ( pFxObj1b != 0 )  // 若 pFxObj1b 非 0
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pFxObj1b + 84))(pFxObj1b, 0);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
      pVt5 = *pDwArg1;
      pDwArg1[2154] = 0;
      pDwArg1[2159] = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(pVt5 + 472))(pDwArg1, 0, 0, 1, 1);
      break;  // 跳出循环/分支
    default:  // 默认分支
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
int /*userpurge*/ sub_5B14D0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, int nArg5)  // 实现：龙人·格挡命中处理器（vmt200 覆写 ×4 表）
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
    nGateVal = pDwArg1[161];  // nGateVal = 取 pDwArg1[161]
    goto LABEL_9;
  }
  pGateObj = pDwArg1[30];  // pGateObj = 取 pDwArg1[30]
  if ( pGateObj != 0 )  // 若 pGateObj 非 0
  {
    if ( *(uint32_t *)(pGateObj + 148) == -1 )
      sub_4938F0(pDwArg1[30]);  // 【推断：伴随对象到期(-1)销毁】
    nGateVal = *(uint32_t *)(pGateObj + 112);
LABEL_9:  // 标签 LABEL_9（跳转合流点）
    if ( nGateVal > 1 )  // 格挡放行门【推断：>1 时(连击后续段)不再演出格挡】
      goto LABEL_33;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) != 0  // 攻击者+348对象表[+12]非空(攻击带破防属性?)【推断】
    || (pVt = *pDwArg1,
        nAtkX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3),  // 取攻击者X
        (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt + 180))(pDwArg1, nAtkX) != 0) )  // 攻击不在正面→直接进入动作13(受击)【推断】
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);  // 调虚槽 +1104
  }
  else  // 否则分支
  {
    *((uint8_t *)pDwArg1 + 8600) = 1;
  }
  if ( *((uint8_t *)pDwArg1 + 8600) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int, int))(*pDwArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pDwArg1,
      0,
      300,
      300,
      0,
      -3000,
      1,
      nArg2);  // 击退参数(±300/向后-3000)【推断】
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
    pVt2 = *pDwArg1;
    hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
    pSparkRes = sub_432E50(hAniKind4);  // 关系码对调映射
    (*(void (/*thiscall*/ **)(int *, int))(pVt2 + 896))(pDwArg1, pSparkRes);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    nMidX = (uint64_t)(pArg4[3] * 0.5 + *pArg4);  // 受击点X中点=攻击矩形两端均值
    nMidXhi = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, (uint64_t)(pArg4[3] * 0.5 + *pArg4) >> 32);  // 64位中点X的高位经vt+124换算
    nMidY = (uint64_t)(pArg4[5] * 0.5 + pArg4[2]);  // 受击点Y中点
    nResGate1 = sub_42FCB0(228);  // CRT 一次性初始化
    hAniSpark = 0;
    if ( nResGate1 != 0 )  // 若 nResGate1 非 0
      hAniSpark = sub_431860(nResGate1, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // 动画件构造（资源 id 版）
    if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxSpark = sub_44E1F0(hAniSpark, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
    else  // 否则分支
      pFxSpark = 0;
    sub_45FE80(pDwArg1[29], pFxSpark, 2, 0, pFxSpark, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
    pFxSparkVt = *(uint32_t *)pFxSpark;
    nProp152a = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int, int))(pFxSparkVt + 148))(pFxSpark, nProp152a);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxSpark + 112))(pFxSpark, nMidX, nMidXhi, nMidY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    nResGate2 = sub_42FCB0(228);  // CRT 一次性初始化
    if ( nResGate2 != 0 )  // 若 nResGate2 非 0
      hAniCircle = sub_431860(nResGate2, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);  // 动画件构造（资源 id 版）
    else  // 否则分支
      hAniCircle = 0;
    if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxCircle = sub_44E1F0(hAniCircle, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
    else  // 否则分支
      pFxCircle = 0;
    sub_45FE80(pDwArg1[29], pFxCircle, 2, 0, pFxCircle, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
    pFxCircleVt = *(uint32_t *)pFxCircle;
    nProp152b = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int, int))(pFxCircleVt + 148))(pFxCircle, nProp152b);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pFxCircle + 112))(pFxCircle, nMidX, nMidXhi, nMidY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    nResGate3 = sub_42FCB0(228);  // CRT 一次性初始化
    if ( nResGate3 != 0 )  // 若 nResGate3 非 0
      hAniGuard = sub_431860(nResGate3, "Monster/Draconian/PassiveObject/GuardEffect.ani", 1);  // 动画件构造（资源 id 版）
    else  // 否则分支
      hAniGuard = 0;
    if ( sub_44B6C0(284) != 0 )  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxGuard = sub_44E1F0(hAniGuard, 1);  // CNRDPooledObject 构造（虚表覆盖壳）
    else  // 否则分支
      pFxGuard = 0;
    sub_45FE80(pDwArg1[29], pFxGuard, 2, 0, pFxGuard, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
    pFxGuardVt = *(uint32_t *)pFxGuard;
    nProp152c = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int))(pFxGuardVt + 148))(pFxGuard);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    pFxGuardVt2 = *(uint32_t *)pFxGuard;
    nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY + 1);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int, int))(pFxGuardVt2 + 112))(pFxGuard, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxGuard + 60))(pFxGuard, pDwArg1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    sub_4A06D0(nProp152c);  // 调 绑定目标对象并记录相对偏移
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*pDwArg1 + 212))(pDwArg1, "SWD_GUARDED", -1, 0);  // 格挡成功播报
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pArg42 = pArg4;
  }
LABEL_33:  // 标签 LABEL_33（跳转合流点）
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
int /*thiscall*/ sub_5B1890(void *this)  // 实现：鲁卡斯·外观装载（armor.equ）
{
  char *pMem; // eax
  char *pEquObj; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEquObj = sub_4BA9E0(pMem, "Monster/Draconian/Lakius/armor.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    pEquObj = nullptr;  // pEquObj = 空指针
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, pEquObj);  // 调虚槽 +784：IRDActiveObject__vmt310
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  return result;
}



// 子类扩展字段复位（this+8628..8640）
// ------------------------------------------------------------
// 0x5B1910 sub_5B1910 —— 赛格哈特·子类扩展字段复位
// 清零 this+8628 / +8632 / +8640 三处 4 字节与 +8636 / +8638 两个字节标志（构造期或重生的状态清场）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1910(int this)  // 实现：赛格哈特·子类扩展字段复位
{
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8636) = 0;  // this+8636〔pDollTarget(推断)〕
  *(uint8_t *)(this + 8638) = 0;  // this+8638〔bRes8638〕
  *(uint32_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B1940 sub_5B1940 —— 赛格哈特·附属对象双槽释放
// this[2157] 与 this[2158] 若为非空接口指针，各调其自身 vt[0](1) 释放，随后两槽置 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1940(uint32_t *this)  // 实现：赛格哈特·附属对象双槽释放
{
  int (/*thiscall*/ ***fld_e2157)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2158)(uint32_t, int); // ecx

  fld_e2157 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2157);  // this+8628〔nPoolTime(推断)〕
  if ( fld_e2157 != nullptr )  // 若 fld_e2157 有效（非空）
    result = (**fld_e2157)(fld_e2157, 1);  // 调 fld_e2157 的虚函数（vt+0）
  fld_e2158 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2158);  // this+8632〔bDevourFlag(推断)〕
  *(this + 2157) = 0;  // this+8628〔nPoolTime(推断)〕
  if ( fld_e2158 != nullptr )  // 若 fld_e2158 有效（非空）
    result = (**fld_e2158)(fld_e2158, 1);  // 调 fld_e2158 的虚函数（vt+0）
  *(this + 2158) = 0;  // this+8632〔bDevourFlag(推断)〕
  return result;
}



// 浮空播报：ZIEG_FLOAT_LOOP（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B1980 sub_5B1980 —— 赛格哈特·浮空循环进入
// ·sub_4D9760 观察者广播收尾后，vt+212 播 ZIEG_FLOAT_LOOP（45566 为时长/参数槽），
// vt+1104 写行为字 15，this[2154] 记 ·sub_699000 当前时钟（供浮空计时门）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1980(uint32_t *this)  // 实现：赛格哈特·浮空循环进入
{
  int result; // eax

  sub_4D9760();  // 观察者广播后条件收尾
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
    this,
    "ZIEG_FLOAT_LOOP",  // 标签 ZIEG_FLOAT_LOOP
    45566,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 调虚槽 +1104
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2154) = result;  // this+8616〔uAI8616(推断)〕
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
int /*usercall*/ sub_5B1F10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：赛格哈特·全局管理器参数下发（阶段 3 一次）
{
  int pMgrVt; // edi
  int nSelfV48; // eax
  int pMgrVt2; // edi
  int nSelfV52; // eax
  int pMgrVt3; // edi
  int nOtherV52; // eax
  int pMgrVt4; // edi
  int nMoveSpeed; // eax
  int result; // eax

  sub_4D9600();  // 交互收尾（this+7820 的 8 字节信息消费）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家门
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[2160];  // result = 取 pArg1[2160]
    if ( result == 0 && pArg1[1943] == 3 )  // 阶段3 且未触发过
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);  // 起包(29,2)【推断】
      pMgrVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nSelfV48 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      (*(void (/*thiscall*/ **)(int, int))(pMgrVt + 36))(dword_8F8520, nSelfV48);  // 逐项写参数
      pMgrVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nSelfV52 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(pMgrVt2 + 36))(dword_8F8520, nSelfV52);  // 会话/UDP 管理器
      pMgrVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nOtherV52 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(pMgrVt3 + 36))(dword_8F8520, nOtherV52);  // 会话/UDP 管理器
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      pMgrVt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nMoveSpeed = sub_460230(pArg1[29]);  // 移速查表
      (*(void (/*thiscall*/ **)(int, int))(pMgrVt4 + 36))(dword_8F8520, nMoveSpeed);  // 会话/UDP 管理器
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
// 赛格哈特/图腾柱·朝向对齐的扩散弹发射：vt+308 玩家门、vt+152 转向（失败走未转向分支），
// 以宿主装备/属性块（this[29]->+132->+44）内 32 字节/项 的发射点列表算出横向散布量
// （224×N − 自身X，0x51EB851F 魔数 ÷100），再由 vt+580 发射 nArg4 号对象，散布参 70/120。
// 末尾再调一次 vt+152 复位朝向【推断：齐射/散射技】
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5B1F50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 实现：末尾再调一次 vt+152 复位朝向(推断：齐射/散射技)
{
  int result; // eax
  int nFaceDir; // ebx
  int64_t nDivTmp; // rax
  int pPropBlk; // eax
  int pEmitBegin; // ecx
  int pEmitVec; // eax
  int nEmitCnt; // edi
  int nScatterOff; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 本地玩家门
  if ( (uint8_t)result != 0 )
  {
    nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);  // 转向
    if ( nFaceDir != 0 )  // 若 nFaceDir 非 0
    {
      pPropBlk = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      pEmitBegin = *(uint32_t *)(pPropBlk + 364);
      pEmitVec = pPropBlk + 360;
      if ( pEmitBegin != 0 )  // 若 pEmitBegin 非 0
        nEmitCnt = (*(uint32_t *)(pEmitVec + 8) - pEmitBegin) >> 5;  // 列表元素数(32字节/项)
      else  // 否则分支
        nEmitCnt = 0;
      nDivTmp = 1374389535LL * (224 * nEmitCnt - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 0x51EB851F=÷100 魔数
    }
    else  // 否则分支
    {
      nDivTmp = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
    }
    nScatterOff = (SHIDWORD(nDivTmp) >> 5) + (HIDWORD(nDivTmp) >> 31);  // 完成除法
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
             pArg1,
             nArg4,
             nScatterOff,
             0,
             0,
             70,  // 散布参数【推断】
             0,
             120,
             nFaceDir,
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
unsigned int /*thiscall*/ sub_5B2010(int *this, int nArg2)  // 实现：赛格哈特·嘲笑收手（ZIEG_LAUGH）与标记清零
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
  *(this + 81) = nArg2;  // this+324〔nRandPick324〕
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 876))(0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  sub_4926A0(*(this + 30));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 与记录点(this[81])的 X 差
  if ( fld_e81 != 0 )  // 若 fld_e81 非 0
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);  // 镜头平移三连【推断】
    sub_4A0550(fld_e81);  // 调 镜头幅度
    sub_4A0600(2);
  }
  else  // 否则分支
  {
    fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
    if ( *fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0  // 调虚槽 +308：是否本地玩家
      && *((float *)fld_e28 + 6) != 0.0 )
    {
      fld_e28[6] = 0;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
    sub_495890(2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  }
  pVt2 = *this;
  *((uint8_t *)this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(pVt2 + 212))(this, "ZIEG_LAUGH", -1, 0, 0);  // 嘲笑播报
  nCount = 0;
  for ( i = 0; ; i += 32 )  // 遍历循环
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
      break;  // 跳出循环/分支
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( nCount >= result )  // 若 nCount >= result
      break;  // 跳出循环/分支
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
unsigned int /*thiscall*/ sub_5B2160(unsigned int *this)  // 实现：赛格哈特·标记集置位（·0x5B2010 清零循环的逆操作）
{
  unsigned int nCount; // edx
  int i; // esi
  int fld_e1905; // edi
  unsigned int result; // eax

  nCount = 0;
  for ( i = 0; ; i += 32 )  // 遍历循环
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
    {
      result = *(this + 2151);  // this+8604〔bAI8604(推断)〕
      *(this + 81) = result;  // this+324〔nRandPick324〕
      return result;
    }
    result = (int)(*(this + 1906) - fld_e1905) >> 5;
    if ( nCount >= result )  // 若 nCount >= result
      break;  // 跳出循环/分支
    ++nCount;
    *(uint8_t *)(i + fld_e1905) = 1;
  }
  *(this + 81) = *(this + 2151);  // this+324〔nRandPick324〕
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
int /*thiscall*/ sub_5B21B0(uint8_t *this)  // 实现：赛格哈特·盾闪（SHIELD_FLASH）
{
  int pVt; // eax
  unsigned int pFpCtrl466; // edi
  int nFlashVal; // eax
  int edxTmp; // edx
  int pVt2; // ebx
  uint32_t *pThis_612; // edi
  int pThis_1B4; // eax

  pVt = *(uint32_t *)this;
  *(this + 8644) = 1;  // 盾闪相位标志
  pFpCtrl466 = (*(int (/*stdcall*/ **)(uint32_t))(pVt + 672))(0) + 466;  // 调虚槽 +672：自身 HP
  nFlashVal = sub_41A5E0(pFpCtrl466);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pFpCtrl466, edxTmp, nFlashVal + 50);  // 全局浮点+466 加 50【推断：闪光强度】
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  pVt2 = *(uint32_t *)this;
  pThis_612 = (uint32_t *)(*((uint32_t *)this + 1554) + 24);  // this+6216〔pTbl6216(推断)〕
  pThis_1B4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 436))(this, 0, 0);  // 调虚槽 +436
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, int))(pVt2 + 204))(this, 100, *pThis_612, 0, -pThis_1B4);  // 上抛/击退【推断】
  return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "SHIELD_FLASH",  // 标签 SHIELD_FLASH
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
int /*thiscall*/ sub_5B2230(uint32_t *this, int nArg2, int nArg3)  // 实现：赛格哈特·盾态进入/退出模式切换
{
  int result; // eax
  unsigned int pCtrl0; // edi
  int edxTmp; // edx
  float fPlaySpeed2; // [esp+0h] [ebp-4h]
  int fPlaySpeed; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )  // 若 nArg3 != 2
      return result;
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;  // 位移速度减半
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);  // 0x3E99999A=0.3f
      sub_4AED60(fPlaySpeed2);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
LABEL_8:  // 标签 LABEL_8（跳转合流点）
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )  // this+8644〔uPhase8644(推断)〕
    sub_5B21B0(this);  // 赛格哈特·盾闪（SHIELD_FLASH）
  pCtrl0 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
  *(float *)&fPlaySpeed = COERCE_FLOAT(sub_41A5E0(pCtrl0)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pCtrl0, edxTmp, fPlaySpeed);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  result = nArg2;
  if ( nArg2 != 0 )  // 若 nArg2 非 0
    goto LABEL_8;
LABEL_9:  // 标签 LABEL_9（跳转合流点）
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;  // this+7620〔pStatusPanel(推断)〕
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
int /*thiscall*/ sub_5B2310(int *this, int nArg2, int nArg3)  // 实现：赛格哈特·盾态还原（·0x5B2230 镜像）
{
  int pThis_1D73; // ecx
  int result; // eax
  int pVt; // edx
  int pVt2; // edx
  unsigned int pCtrl0; // edi
  int edxTmp; // edx
  float fPlaySpeed3; // [esp+0h] [ebp-8h]
  int fPlaySpeed; // [esp+14h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *((uint8_t *)this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *((uint8_t *)this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *((uint8_t *)this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *((uint8_t *)this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *((uint8_t *)this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *((uint8_t *)this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(int *)((char *)this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  pThis_1D73 = (int)this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *(uint32_t *)(pThis_1D73 + 4) = 0;  // pThis_1D73+4〔宿主对象〕
  *(uint32_t *)(pThis_1D73 + 8) = 0;  // pThis_1D73+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pThis_1D73 + 12) = 0;  // pThis_1D73+12〔nSkillRec12(推断)〕
  *(uint8_t *)(pThis_1D73 + 16) = 0;  // pThis_1D73+16〔nChannelTypeSel(推断)〕
  *(this + 1893) = 0;  // this+7572〔uGrade7572(推断)〕
  *(this + 1892) = 0;  // this+7568〔uEnable7568(推断)〕
  *(this + 1891) = 0;  // this+7564〔uForm7564(推断)〕
  *(this + 1897) = 0;  // this+7588〔uForm7588〕
  *(this + 1896) = 0;  // this+7584〔uForm7584〕
  *(this + 1895) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(this + 1894) = 0;  // this+7576〔uPhase7576(推断)〕
  *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
  *((uint8_t *)this + 7538) = 1;  // this+7538〔bCfgBlock18(推断)〕
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )  // 若 nArg3 != 2
      return result;
    result = nArg2;
    if ( nArg2 == 0 )  // 若 nArg2 为 0
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);  // 位移速度 ×2 还原
      pVt = *this;
      *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(pVt + 672))(this, 0, 1050253722);  // 0x3E99999A=0.3f
      sub_4AED60(fPlaySpeed3);
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    }
LABEL_8:  // 标签 LABEL_8（跳转合流点）
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )  // this+8644〔uPhase8644(推断)〕
    sub_5B21B0(this);  // 赛格哈特·盾闪（SHIELD_FLASH）
  pVt2 = *this;
  *(this + 1899) = 50;  // this+7596〔nOffset7596(推断)〕
  pCtrl0 = (*(int (/*thiscall*/ **)(int *, uint32_t))(pVt2 + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
  *(float *)&fPlaySpeed = COERCE_FLOAT(sub_41A5E0(pCtrl0)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pCtrl0, edxTmp, fPlaySpeed);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  result = nArg2;
  if ( nArg2 != 0 )  // 若 nArg2 非 0
    goto LABEL_8;
LABEL_9:  // 标签 LABEL_9（跳转合流点）
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);  // this+7620〔pStatusPanel(推断)〕
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
unsigned int /*thiscall*/ sub_5B2480(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：赛格哈特·新星/护盾事件分发（大状态 this+6556 × 事件码）
{
  int nEvt; // ebx
  int nMainState6556; // edi  | +0x199C → 主状态镜像（0x5B2480 开关总闸：大状态 14/护盾、8/普攻、17 分派）（证据: va=005B2480）（CNLordofLightBase；va=005B2480）
  uint32_t *pResSlot; // eax
  float fEvtParam; // edi
  int nTgtRef; // eax
  unsigned int result; // eax
  int *pResSlot2; // eax

  nEvt = ArgList;
  nMainState6556 = *(uint32_t *)(this + 6556);  // 大状态
  if ( ArgList == 15 )  // 若 ArgList == 15
  {
    sub_5B2160((unsigned int *)this);  // 赛格哈特·标记集置位（·0x5B2010 清零循环的逆操作）
    nEvt = 0;
  }
  if ( nMainState6556 == 14 )  // 护盾态
  {
    if ( nEvt != 15 )  // 若 nEvt != 15
      sub_5B2160((unsigned int *)this);  // 赛格哈特·标记集置位（·0x5B2010 清零循环的逆操作）
  }
  else  // 否则分支
  {
    if ( nMainState6556 != 8 )  // 若 fld_199C != 8
      goto LABEL_13;
    if ( nEvt == 8 )  // 若 nEvt == 8
      goto LABEL_14;
    if ( sub_41A5E0(this + 7028) == 1 )  // 子类型1
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 调虚槽 +208：定时器移除
      pResSlot = (uint32_t *)(*(uint32_t *)(this + 6216) + 8);  // this+6216〔pTbl6216(推断)〕
    }
    else  // 否则分支
    {
      if ( sub_41A5E0(this + 7028) != 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        goto LABEL_13;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 16));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 20));  // 调虚槽 +208：定时器移除
      pResSlot = (uint32_t *)(*(uint32_t *)(this + 6216) + 12);  // this+6216〔pTbl6216(推断)〕
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pResSlot);  // 调虚槽 +208：定时器移除
  }
LABEL_13:  // 标签 LABEL_13（跳转合流点）
  if ( nEvt != 8 )  // 若 nEvt != 8
  {
    fEvtParam = fArg3;
    goto LABEL_19;
  }
LABEL_14:  // 标签 LABEL_14（跳转合流点）
  fEvtParam = fArg3;
  if ( *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) == 1 )
  {
    nTgtRef = *(uint32_t *)(this + 7252);  // this+7252〔pTarget7252〕
    if ( nTgtRef != 0  // 若 nTgtRef 非 0
      && (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 8))(this, nTgtRef, 0) < *(uint32_t *)(*(uint32_t *)(this + 7620) + 80) )  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    {
      *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 2;
    }
  }
LABEL_19:  // 标签 LABEL_19（跳转合流点）
  result = sub_4E33D0(nEvt, fEvtParam, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  switch ( nEvt )  // 按 nEvt 分派
  {
    case 5:  // 音效三连
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45566);  // 调虚槽 +216：音效 TAG 查询
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45567);  // 调虚槽 +216：音效 TAG 查询
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45568);  // 调虚槽 +216：音效 TAG 查询
    case 8:  // 新星事件
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      *(uint8_t *)(this + 8637) = 0;  // this+8637〔bSwingGate8637〕
      if ( sub_41A5E0(this + 7028) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        return sub_5B1CD0(this);  // 返回 调 sub_5B1CD0 返回值
      }
      else  // 否则分支
      {
        result = sub_41A5E0(this + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
        if ( result == 2 )  // 子类型2 = 新星蓄力+施放
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            this,
            "ZIEG_NOVA_READY_LOOP",  // 标签 ZIEG_NOVA_READY_LOOP
            45568,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            this,
            "ZIEG_CAST_NOVA",  // 标签 ZIEG_CAST_NOVA
            -1,
            0,
            0);
          pResSlot2 = (int *)(*(uint32_t *)(this + 6216) + 16);  // this+6216〔pTbl6216(推断)〕
          *(uint8_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
          sub_4926A0(*pResSlot2);  // 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 12));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 16),  // this+6216〔资源槽贴图〕
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 20),  // this+6216〔资源槽贴图〕
            0,
            0,
            0,
            0);
          return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
                   this,
                   100,
                   *(uint32_t *)(*(uint32_t *)(this + 6216) + 12),  // this+6216〔资源槽贴图〕
                   0,
                   0,
                   0,
                   0);
        }
      }
      break;  // 跳出循环/分支
    case 14:  // 护盾事件 → 转嘲笑(0x5B2010)
      return sub_5B2010((int *)this, **(uint32_t **)(LODWORD(fEvtParam) + 4));  // 赛格哈特·嘲笑收手（ZIEG_LAUGH）与标记清零
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return result;
}


// 赛格哈特语音：R_ZIEG_DMG + ZIEG_DIE_VOICE（this+8600/8604/8636 相位）
// ------------------------------------------------------------
// 0x5B2720 sub_5B2720 —— 赛格哈特·受伤/死亡语音装载
// ·sub_4015C0 写 R_ZIEG_DMG(0xA) 与 ZIEG_DIE_VOICE(0xE) 两条语音 TAG；
// this+8600=20、this+8604=this+324（父级引用），并以 ·sub_47C080(20) 结果取反写 this+8636 相位标志。
// ------------------------------------------------------------
bool /*thiscall*/ sub_5B2720(int this)  // 实现：赛格哈特·受伤/死亡语音装载
{
  int fld_144; // eax
  bool result; // al

  sub_4015C0("R_ZIEG_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZIEG_DIE_VOICE", 0xEu);  // 【std::string构造赋值】
  fld_144 = *(uint32_t *)(this + 324);  // this+324〔nRandPick324〕
  *(uint32_t *)(this + 8600) = 20;  // this+8600〔uAI8600(推断)〕
  *(uint32_t *)(this + 8604) = fld_144;  // this+8604〔bAI8604(推断)〕
  result = (uint8_t)sub_47C080(20) == 0;  // result = 调 sub_47C080 返回值
  *(uint8_t *)(this + 8636) = result;  // this+8636〔pDollTarget(推断)〕
  return result;
}



// 赛格哈特·周期护盾：时钟(this+9)距上次(this[2154])超过 15000ms 且大状态空闲、
//   有目标时 → vt+564 复位并 setState(14, 参数 200=护盾持续)【推断：每 15 秒开盾】
// ------------------------------------------------------------
// 0x5B2780 sub_5B2780 —— 赛格哈特·周期护盾（每 15 秒开盾）
// ·sub_699000 时钟超过 this[2154]+15000ms 才进入，先回写本次时刻；再要求 vt+840 大状态为 0 且
// this[1813] 目标存在，vt+564 复位后用 ·sub_431230 打包 aArgList[0]=200（护盾持续）经 vt+560 setState(14)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2780(uint32_t *this)  // 实现：赛格哈特·周期护盾（每 15 秒开盾）
{
  int pThis_9; // edi
  int nNow; // eax
  int pVt; // edx
  uint8_t pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int nPad1a; // [esp+10h] [ebp-18h]
  int nPad2a; // [esp+14h] [ebp-14h]
  uint32_t aArgList[4]; // [esp+18h] [ebp-10h] BYREF

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2154) + 15000) )  // 【clock_now(clk)】 15 秒周期
  {
    nNow = sub_699000(pThis_9);  // 【clock_now(clk)】
    pVt = *this;
    *(this + 2154) = nNow;  // 记录本次触发时刻
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 840))(this) == 0 && *(this + 1813) != 0 )  // 空闲且有目标
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
      aArgList[0] = 200;  // 护盾持续参数【推断】
      Block = nullptr;  // Block = 空指针
      nPad1a = 0;
      nPad2a = 0;
      aArgList[3] = 0;
      sub_431230((int)pBuf, aArgList);  // 【vector 打包 setState 参数表】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // setState(14) 开盾
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
    }
  }
}



// 赛格哈特·条件新星普攻：范围值=速度表(+80/+88 之和)×1.5 过 sub_4E0CD0(17,…) 判定
//   （17=技能/范围档位）≥2 且 40% 概率 → vt+564 复位并 setState(8, 子类型2=新星)
// ------------------------------------------------------------
// 0x5B2840 sub_5B2840 —— 赛格哈特·条件新星（射程档位判定后 40% 触发）
// 范围值取速度表 this[1905]+80 与 +88 之和的 1.5 倍，交 ·sub_4E0CD0(17,0,0,…) 档位判定 ≥2，
// 且 rand()%100<40 时 vt+564 复位、参数 aArgList[0]=2（新星子型）经 ·sub_431230 打包 + vt+560 setState(8)。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2840(uint32_t *this)  // 实现：赛格哈特·条件新星（射程档位判定后 40% 触发）
{
  uint8_t pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int nPad1a; // [esp+10h] [ebp-18h]
  int nPad2a; // [esp+14h] [ebp-14h]
  uint32_t aArgList[4]; // [esp+18h] [ebp-10h] BYREF

  aArgList[0] = *(uint32_t *)(*(this + 1905) + 80) + *(uint32_t *)(*(this + 1905) + 88);  // aArgList[0] = 读 this+1905
  if ( (int)sub_4E0CD0(17, 0, 0, (uint64_t)((double)aArgList[0] * 1.5)) >= 2 && rand() % 100 < 40 )  // 40% 概率
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);  // 调虚槽 +564
    Block = nullptr;  // Block = 空指针
    nPad1a = 0;
    nPad2a = 0;
    aArgList[3] = 0;
    aArgList[0] = 2;  // 子类型 2 = 新星
    sub_431230((int)pBuf, aArgList);  // 【vector 打包 setState 参数表】
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);  // setState(8)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B2900 sub_5B2900 —— 赛格哈特·每帧 AI 门（新星挂载）
// 先 ·sub_5B1BA0 帧前处理；再经 vt+308 目标门、this[1813] 非 0、vt+840 大状态为 0 三条件，
// 全满足才交 ·0x5B2840 条件新星。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2900(uint32_t *this)  // 实现：赛格哈特·每帧 AI 门（新星挂载）
{
  sub_5B1BA0();  // 调 帧前处理
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1813) != 0  // this+7252〔pTarget7252〕
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    sub_5B2840(this);  // 赛格哈特·条件新星（射程档位判定后 40% 触发）
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
char /*usercall*/ sub_5B2940@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：赛格哈特·激光三阶段（聚焦/发射/收束）
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

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 2 || *(uint8_t *)(pArg1 + 8621) != 0 )  // 调虚槽 +200：取动画对象
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 5 || *(uint8_t *)(pArg1 + 8622) != 0 )  // 调虚槽 +200：取动画对象
    {
      pActObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
      if ( *(uint32_t *)(pActObj + 148) == 6 )
      {
        LOBYTE(pActObj) = *(uint8_t *)(pArg1 + 8623);
        if ( (uint8_t)pActObj == 0 )
        {
          pResSlot = (int *)(*(uint32_t *)(pArg1 + 6216) + 4);  // pArg1+6216〔pTbl6216(推断)〕
          *(uint8_t *)(pArg1 + 8623) = 1;
          sub_4926A0(*pResSlot);  // 帧游标复位（+44 帧数组；递归子链 +204）
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调虚槽 +204：定时器插入
            pArg1,
            100,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调虚槽 +204：定时器插入
            pArg1,
            200,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8),
            0,
            0,
            0,
            0);
          LOBYTE(pActObj) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 45567);  // 调虚槽 +216：音效 TAG 查询
        }
      }
    }
    else  // 否则分支
    {
      *(uint8_t *)(pArg1 + 8622) = 1;  // pArg1+8622〔bLoopLatch8622(推断)〕
      sub_5B1F50((uint32_t *)pArg1, nArg2, nArg3, 46003);
      LOBYTE(pActObj) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                      pArg1,
                      "ZIEG_LASER_FIRE",  // 标签 ZIEG_LASER_FIRE
                      -1,
                      0,
                      0);
    }
  }
  else  // 否则分支
  {
    pVt = *(uint32_t *)pArg1;
    *(uint8_t *)(pArg1 + 8621) = 1;
    if ( (*(int (/*thiscall*/ **)(int))(pVt + 152))(pArg1) != 0 )  // 调虚槽 +152：效果通道 3
      nLaserX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 70;  // 调虚槽 +120：动画对象
    else  // 否则分支
      nLaserX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 70;  // 调虚槽 +120：动画对象
    nLaserX2 = nLaserX;
    hAniConc = 0;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      hAniConc = sub_431860((char)"Common/CommonEffect/Animation/ConcentrationEffect.ani", 1);  // 动画件构造（资源 id 版）
    pPool = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    pFxObj = (int *)pPool;
    if ( pPool != nullptr )  // 若 pPool 有效（非空）
    {
      sub_44E0D0(pPool, hAniConc, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *pFxObj = (int)&CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pFxObj = nullptr;  // pFxObj = 空指针
    }
    sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)pFxObj, 2, 0, (int)pFxObj, pArg1, 0);  // 调 实体对象注册到演播层
    pFxVt = *pFxObj;
    nZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, nZ + 120);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(int *, int, int))(pFxVt + 112))(pFxObj, nLaserX2, nY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    pFxVt2 = *pFxObj;
    nProp152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int *, int))(pFxVt2 + 148))(pFxObj, nProp152);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
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
void /*thiscall*/ sub_5B2B80(int *this)  // 实现：赛格哈特·死亡演出（Die.ani + 双粒子）
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
  uint8_t pBuf[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  uint8_t pBuf2[4]; // [esp+1Ch] [ebp-20h] BYREF
  void *nPad1; // [esp+20h] [ebp-1Ch]
  void *pMem3; // [esp+2Ch] [ebp-10h]
  int pObjTmp; // [esp+38h] [ebp-4h]

  hAniDie = 0;
  pObjTmp = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    hAniDie = sub_431860((char)"Monster/LordofLight/LOL/Die.ani", 1);  // 动画件构造（资源 id 版）
  pPool = (int *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  pDieFx = pPool;
  pMem3 = pPool;
  pObjTmp = 1;
  if ( pPool != nullptr )  // 若 pPool 有效（非空）
  {
    sub_44E0D0((char *)pPool, hAniDie, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *pDieFx = (int)&CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pDieFx = nullptr;  // pDieFx = 空指针
  }
  fld_e29 = *(this + 29);  // this+116〔会话上下文〕
  pObjTmp = -1;
  sub_45FE80(fld_e29, (int)pDieFx, 2, 0, (int)pDieFx, (int)this, 0);  // 调 实体对象注册到演播层
  pDieFxVt = *pDieFx;
  nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(int *, int))(pDieFxVt + 112))(pDieFx, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  pDieFxVt2 = *pDieFx;
  nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(int *, int))(pDieFxVt2 + 144))(pDieFx, nProp152);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
  pMem3 = pMem;
  pObjTmp = 2;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimNameCap(推断)〕
      pArmorPtlObj = (int *)sub_4C3640((int)pMem, (int)(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);  // pArmorPtlObj = 调 sub_4C3640 返回值
    else  // 否则分支
      pArmorPtlObj = (int *)sub_4C3640((int)pMem, *(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);  // pArmorPtlObj = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pArmorPtlObj = nullptr;  // pArmorPtlObj = 空指针
  }
  *(this + 2157) = (int)pArmorPtlObj;  // this+8628 装甲飞散粒子槽(死亡演出用)
  pArmorPtlVt = *pArmorPtlObj;
  pObjTmp = -1;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(pArmorPtlVt + 12))(pArmorPtlObj, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
  fld_e2157 = *(uint32_t *)*(this + 2157);  // fld_e2157 = 读 this+2157
  nZ2 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ2 + 50);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY2);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2157 + 40))(*(this + 2157), nX2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2157) + 92))(*(this + 2157), pBuf2);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
  fld_e292 = (void *)*(this + 29);  // this+116〔会话上下文〕
  pObjTmp = 3;
  sub_4600B0(fld_e292, 2, 0, (int)pBuf2);  // 调 演播层注册(槽号)
  pMem2 = operator new(0x12Cu);  // new(300 字节) 分配对象
  pMem3 = pMem2;
  LOBYTE(pObjTmp) = 4;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
  {
    if ( (unsigned int)*(this + 96) < 0x10 )  // this+384〔nAnimNameCap(推断)〕
      pHikariPtlObj = (int *)sub_4C3640((int)pMem2, (int)(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);  // pHikariPtlObj = 调 sub_4C3640 返回值
    else  // 否则分支
      pHikariPtlObj = (int *)sub_4C3640((int)pMem2, *(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);  // pHikariPtlObj = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pHikariPtlObj = nullptr;  // pHikariPtlObj = 空指针
  }
  *(this + 2158) = (int)pHikariPtlObj;  // this+8632 光尘粒子槽(死亡演出用)
  pHikariPtlVt = *pHikariPtlObj;
  LOBYTE(pObjTmp) = 3;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(pHikariPtlVt + 12))(pHikariPtlObj, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
  fld_e2158 = *(uint32_t *)*(this + 2158);  // fld_e2158 = 读 this+2158
  nZ3 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY3 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ3 + 50);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX3 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY3);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2158 + 40))(*(this + 2158), nX3);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  fld_e21582 = (*(int (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2158) + 92))(*(this + 2158), pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
  LOBYTE(pObjTmp) = 5;
  sub_4E77D0((int)pBuf2, fld_e21582);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
  LOBYTE(pObjTmp) = 3;
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);
  sub_4600B0((void *)*(this + 29), 2, 0, (int)pBuf2);  // 调 演播层注册(槽号)
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ZIEG_DIE_EFFECT", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  if ( nPad1 != nullptr )  // 若 nPad1 有效（非空）
    j__free(nPad1);
}


// 【vmt200 命中处理器覆写】光之城主格挡 handler（虚表 0x6E447C +512 槽, 48L）：
//   Monster/LordOfLight/LOL/GuardEffect.ani 专属格挡特效（sub_431860）
// ------------------------------------------------------------
// 0x5B2E20 sub_5B2E20 —— 光之城主·格挡命中处理器（vmt200 覆写 ×1 表）
// 门控 this+8644（盾闪相位）非 0 才演出：·sub_431860 装 Monster/LordOfLight/LOL/GuardEffect.ani，
// ·sub_44B6C0/·sub_44E0D0 取池对象并构造，·sub_45FE80 挂本体，vt+112/148 定位与朝向（vt+152）。
// 末尾仍交 ·sub_4DA3B0 命中包分发（pArg2/pArg4 原样透传）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2E20(int *this, int nArg2, int nArg3, int nArg4)  // 实现：光之城主·格挡命中处理器（vmt200 覆写 ×1 表）
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

  if ( *((uint8_t *)this + 8644) != 0 )  // this+8644〔uPhase8644(推断)〕
  {
    hAniGuard = 0;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      hAniGuard = sub_431860((char)"Monster/LordOfLight/LOL/GuardEffect.ani", 1);  // 动画件构造（资源 id 版）
    pPool = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    pFxObj = (int)pPool;
    if ( pPool != nullptr )  // 若 pPool 有效（非空）
    {
      sub_44E0D0(pPool, hAniGuard, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pFxObj = 0;
    }
    sub_45FE80(*(this + 29), pFxObj, 2, 0, pFxObj, (int)this, 0);  // 调 实体对象注册到演播层
    pFxVt = *(uint32_t *)pFxObj;
    nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int))(pFxVt + 148))(pFxObj);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    pFxVt2 = *(uint32_t *)pFxObj;
    nZ = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nY + 1);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int, int))(pFxVt2 + 112))(pFxObj, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxObj + 60))(pFxObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    sub_4A06D0(nProp152);  // 调 绑定目标对象并记录相对偏移
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
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
int /*thiscall*/ sub_5B2F40(int this, int nArg2)  // 实现：赛格哈特·死亡/退场对话门（死亡表现前置）
{
  int pDialogObj8640; // edi  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  int pThis_1B4; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int fld_21C02; // edi  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  int pThis_98; // eax
  int pDialogObj8640_; // edi  | +0x21C0 → 对话/存活奖励对象指针（CNLordofLightBase；va=005B2F40）
  int nMsgCtx; // eax
  int pThis_982; // [esp-Ch] [ebp-14h]

  if ( this != nArg2 )  // 若 this != nArg2
    return sub_4D9170(nArg2);  // 返回 调 sub_4D9170 返回值
  if ( *(uint32_t *)(this + 7772) != 3 || *(uint32_t *)(this + 8640) == 0 || *(uint8_t *)(this + 8636) != 1 )  // this+7772〔nCounterState〕
  {
    sub_5B2B80((int *)this);  // 赛格哈特·死亡演出（Die.ani + 双粒子）
    return sub_4D9170(nArg2);  // 返回 调 sub_4D9170 返回值
  }
  pDialogObj8640 = **(uint32_t **)(this + 8640);  // this+8640〔uCastSlot8640(推断)〕
  pThis_1B4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 436))(this);  // 调虚槽 +436
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_1B4);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t, int))(pDialogObj8640 + 112))(*(uint32_t *)(this + 8640), pThis_78);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  fld_21C02 = **(uint32_t **)(this + 8640);  // this+8640〔uCastSlot8640(推断)〕
  pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21C02 + 144))(*(uint32_t *)(this + 8640), pThis_98);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8640) + 308))(*(uint32_t *)(this + 8640)) != 0 )  // 调虚槽 +308：是否本地玩家
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8640) + 580))(  // this+8640〔uCastSlot8640(推断)〕
      *(uint32_t *)(this + 8640),  // this+8640〔uCastSlot8640(推断)〕
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
  pDialogObj8640_ = *(uint32_t *)(this + 8640);  // fld_21C03 = 读 this+8640
  pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 10000);  // 调虚槽 +152：效果通道 3
  nMsgCtx = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDialogObj8640_ + 64))(pDialogObj8640_);  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
  sub_50EF20(nMsgCtx, "......", pThis_982);  // 头顶冒 "……" 气泡(存活奖励视图 48001)【推断：死亡前无语对白】
  return sub_4D9170(nArg2);  // 返回 调 sub_4D9170 返回值
}



// 技能播报：ZIEG_NOVA_FIRE + SWING_LONG 挥击
// ------------------------------------------------------------
// 0x5B3050 sub_5B3050 —— 赛格哈特·大状态事件总回调（护盾/普攻/待机三分支）
// 先 ·sub_4E1780 帧前处理；按 vt+840 大状态分流：
// 14/护盾 → ·0x5B1D20；8/普攻 → 按 this+7028 子型 0 时动作对象 vt+148 ≥3 且 this+8637 未置位则播 SWING_LONG，
// 子型 1 转 ·0x5B2940 激光，子型 2 且动作对象 vt+148==4、this+8624 未置位则音效 45568 + 播 ZIEG_NOVA_FIRE；
// 其余（含待机）→ vt+308 门通过后 ·0x5B2780 周期护盾。
// ------------------------------------------------------------
void /*usercall*/ sub_5B3050(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：赛格哈特·大状态事件总回调（护盾/普攻/待机三分支）
{
  int pVt; // edx
  int nSubType; // eax
  int nSubTypeM1; // eax

  sub_4E1780((uint32_t *)pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    sub_5B1D20(pArg1);
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    nSubType = sub_41A5E0(pArg1 + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( nSubType != 0 )  // 若 nSubType 非 0
    {
      nSubTypeM1 = nSubType - 1;
      if ( nSubTypeM1 != 0 )  // 若 nSubTypeM1 非 0
      {
        if ( nSubTypeM1 == 1  // 若 nSubTypeM1 == 1
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 4  // 调虚槽 +200：取动画对象
          && *(uint8_t *)(pArg1 + 8624) == 0 )  // pArg1+8624〔uAI8624(推断)〕
        {
          pVt = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8624) = 1;  // pArg1+8624〔uAI8624(推断)〕
          (*(void (/*thiscall*/ **)(int, int))(pVt + 216))(pArg1, 45568);  // 调虚槽 +216：音效 TAG 查询
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pArg1,
            "ZIEG_NOVA_FIRE",  // 标签 ZIEG_NOVA_FIRE
            -1,
            0,
            0);
        }
      }
      else  // 否则分支
      {
        sub_5B2940(pArg1, nArg2, nArg3);  // 赛格哈特·激光三阶段（聚焦/发射/收束）
      }
    }
    else if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 && *(uint8_t *)(pArg1 + 8637) == 0 )  // 调虚槽 +200：取动画对象
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SWING_LONG", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      *(uint8_t *)(pArg1 + 8637) = 1;  // pArg1+8637〔bSwingGate8637(推断)〕
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    sub_5B2780((uint32_t *)pArg1);  // 赛格哈特·周期护盾（每 15 秒开盾）
  }
}



// 赛格哈特外观装载：Monster/LordofLight/LOL/{Armor,Glow,Wing}.equ 三件（甲/辉光/翼）
// ------------------------------------------------------------
// 0x5B3100 sub_5B3100 —— 赛格哈特·外观三件套装载（Armor/Glow/Wing）
// 三个 0x544 字节新对象依次经 ·sub_4BA9E0 挂 Monster/LordofLight/LOL/{Armor,Glow,Wing}.equ，
// 各由自身 vt+784 装配、结果非 0 时经其结果 vt+4(1) 激活；末尾 this+8644 盾闪标志清零、
// ·sub_4E1390 注册 196614（常量 100000）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3100(uint8_t *this)  // 实现：赛格哈特·外观三件套装载（Armor/Glow/Wing）
{
  char *pMem; // eax
  char *pEquArmor; // eax
  int pVt; // edx
  int pObj; // eax
  char *pMem2; // eax
  char *pEquGlow; // eax
  int pVt2; // edx
  int pObj2; // eax
  char *pMem3; // eax
  char *pEquWing; // eax
  int pVt3; // edx
  int pObj3; // eax
  int nPropVal; // [esp+8h] [ebp-10h] BYREF
  int nCtorState; // [esp+14h] [ebp-4h]

  pMem = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  nCtorState = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pEquArmor = sub_4BA9E0(pMem, "Monster/LordofLight/LOL/Armor.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    pEquArmor = nullptr;  // pEquArmor = 空指针
  pVt = *(uint32_t *)this;
  nCtorState = -1;
  pObj = (*(int (/*thiscall*/ **)(uint8_t *, char *))(pVt + 784))(this, pEquArmor);
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem2 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  nCtorState = 1;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pEquGlow = sub_4BA9E0(pMem2, "Monster/LordofLight/LOL/Glow.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    pEquGlow = nullptr;  // pEquGlow = 空指针
  pVt2 = *(uint32_t *)this;
  nCtorState = -1;
  pObj2 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(pVt2 + 784))(this, pEquGlow);
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  pMem3 = (char *)operator new(0x544u);  // new(1348 字节) 分配对象
  nCtorState = 2;
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pEquWing = sub_4BA9E0(pMem3, "Monster/LordofLight/LOL/Wing.equ", 0);  // CNRDEquipment 构造（.equ 外观对象公共工厂）
  else  // 否则分支
    pEquWing = nullptr;  // pEquWing = 空指针
  pVt3 = *(uint32_t *)this;
  nCtorState = -1;
  pObj3 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(pVt3 + 784))(this, pEquWing);
  if ( pObj3 != 0 )  // 若 pObj3 非 0
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 8644) = 0;  // this+8644〔盾闪标志清零〕
  nPropVal = 100000;
  return sub_4E1390(196614, &nPropVal);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
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
int /*thiscall*/ sub_5B3230(int this)  // 实现：空骨鱼·子类字段复位
{
  *(uint32_t *)(this + 8600) = 1;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint8_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
  *(uint32_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
  return 0;
}



// 虫弹技能：引用 Particle/BugShot.ptl（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B3250 sub_5B3250 —— 空骨鱼·虫弹发射（BugShot）
// this[2152] 记 ·sub_699000 当前时钟作冷却基准；vt+308 目标门通过后，
// this+7028 子型 ==2 时经 vt+588 取 Particle/BugShot.ptl 资源，由 vt+580 发射对象 30013
// （参数取 this[2150] AI 阈值字段，末位 4）【推断：子型 2 专属弹药外观】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3250(uint32_t *this)  // 实现：空骨鱼·虫弹发射（BugShot）
{
  int result; // eax
  int pPtlParams; // eax

  *(this + 2152) = sub_699000((int)(this + 9));  // clock_now(clk)
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      pPtlParams = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BugShot.ptl");  // 调虚槽 +588
    else  // 否则分支
      pPtlParams = 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
             this,
             30013,
             *(this + 2150),  // this+8600〔uAI8600(推断)〕
             pPtlParams,
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
char /*thiscall*/ sub_5B32C0(int this, int nArg2)  // 实现：空骨鱼·目标切换横向补偿
{
  int pTarget7252; // ebx  | +0x1C54 → 【推断】当前目标对象〔5B32C0：nArg2 非自身当前目标 this+7252 时才做换目标横向补偿〕（CNSpaceFishHead；va=005B32C0）
  int fld_1DA8; // eax  | +0x1DA8 → 【推断】换目标横向补偿偏置〔5B32C0：+50 / -50 对调，方向由 +8620 标志锁存〕（CNSpaceFishHead；va=005B32C0）
  bool bFaceMatched; // zf

  pTarget7252 = *(uint32_t *)(this + 7252);  // this+7252〔pTarget7252〕
  LOBYTE(fld_1DA8) = sub_4D97E0(nArg2);  // 动作子对象状态槽直写
  if ( pTarget7252 != nArg2 && nArg2 != 0 )  // 若 fld_1C54 != nArg2 与/或 nArg2 != 0
  {
    LOBYTE(fld_1DA8) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( (uint8_t)fld_1DA8 != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调虚槽 +700：读 +6296 槽
      bFaceMatched = (uint8_t)sub_53FD00(nArg2) == 1;  // bFaceMatched = 调 sub_53FD00 返回值
      LOBYTE(fld_1DA8) = *(uint8_t *)(this + 8620);  // this+8620〔uAI8620(推断)〕
      if ( bFaceMatched )
      {
        if ( (uint8_t)fld_1DA8 == 0 )
        {
          fld_1DA8 = *(uint32_t *)(this + 7592) + 50;  // this+7592〔nAtkSegSlot7592〕
          *(uint8_t *)(this + 8620) = 1;  // this+8620〔uAI8620(推断)〕
          *(uint32_t *)(this + 7592) = fld_1DA8;  // this+7592〔nAtkSegSlot7592〕
        }
      }
      else if ( (uint8_t)fld_1DA8 == 1 )
      {
        fld_1DA8 = *(uint32_t *)(this + 7592) - 50;  // this+7592〔nAtkSegSlot7592〕
        *(uint8_t *)(this + 8620) = 0;  // this+8620〔uAI8620(推断)〕
        *(uint32_t *)(this + 7592) = fld_1DA8;  // this+7592〔nAtkSegSlot7592〕
      }
    }
  }
  return fld_1DA8;  // | +0x1DA8 → 【推断】换目标横向补偿偏置〔5B32C0：+50 / -50 对调，方向由 +8620 标志锁存〕（CNSpaceFishHead；va=005B32C0）
}



// 主状态门（this+200/8612）
// ------------------------------------------------------------
// 0x5B3350 sub_5B3350 —— 空骨鱼·虫弹触发门
// ·sub_4E1780 帧前处理后，vt+840 大状态 ==8 且 this+7028 子型为 1 或 2，this+8612 未置位时，
// 经 vt+200 动作对象 +170 标志非 0 才 ·0x5B3250 发虫弹并置 this+8612 防重入。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B3350(int this)  // 实现：空骨鱼·虫弹触发门
{
  int pThis_348; // eax

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( pThis_348 == 8 && (sub_41A5E0(this + 7028) == 1 || (pThis_348 = sub_41A5E0(this + 7028)) == 2) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8612);  // this+8612〔uAI8612(推断)〕
    if ( (uint8_t)pThis_348 == 0 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
      if ( *(uint8_t *)(pThis_348 + 170) != 0 )
      {
        LOBYTE(pThis_348) = sub_5B3250((uint32_t *)this);  // 空骨鱼·虫弹发射（BugShot）
        *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
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
int /*thiscall*/ sub_5B33C0(int *this)  // 实现：空骨鱼·待机姿态写入
{
  int nPoseIdx; // edi
  int result; // eax

  nPoseIdx = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  result = *(this + 1639);  // this+6556〔大状态ID〕
  if ( result == 0 && nPoseIdx != 4 )  // 若 result == 0 与/或 nPoseIdx != 4
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, nPoseIdx);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, nPoseIdx);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3400 sub_5B3400 —— 空骨鱼·技能变体甲装填
// this[2151] = 30010（对象/技能 ID 槽）、this[2154] = 1（变体号）；
// 与 ·0x5B34D0 乙型、·0x5B35C0 丙型构成三变体装填族【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3400(uint32_t *this)  // 实现：空骨鱼·技能变体甲装填
{
  *(this + 2151) = 30010;  // this+8604〔bAI8604(推断)〕
  *(this + 2154) = 1;  // this+8616〔uAI8616(推断)〕
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3420 sub_5B3420 —— 空骨鱼·攻击参数面复位（甲向 -50）
// 清零 this+7531..7558 与 this+7564..7596 两段攻击/分身参数面，再置 this+7557=1、this+7588=1；
// nArg3==2 时改用 nArg2 作段号选择，所选为 0 则 this+7596 = -50（反向偏置）。
// 与 ·0x5B3510 同构，差异仅末项为 +50（乙向）；偏置供 ·0x5B32C0 换目标时横向对齐用【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3420(int this, int nArg2, int nArg3)  // 实现：空骨鱼·攻击参数面复位（甲向 -50）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint8_t *)(this + 7557) = 1;  // this+7557〔bAtk7557(推断)〕
  *(uint32_t *)(this + 7588) = 1;  // this+7588〔uForm7588〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = -50;  // this+7596〔nOffset7596(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B34D0 sub_5B34D0 —— 空骨鱼·技能变体乙装填与属性注册
// this[2151] = 30011、this[2154] = 2（与 ·0x5B3400 甲型成对的第二变体【推断】）；
// 末经 ·sub_4E1390(196613, 100000) 注册技能/属性项。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B34D0(uint32_t *this)  // 实现：空骨鱼·技能变体乙装填与属性注册
{
  int nPropVal; // [esp+0h] [ebp-4h] BYREF

  *(this + 2151) = 30011;  // this+8604〔bAI8604(推断)〕
  *(this + 2154) = 2;  // this+8616〔uAI8616(推断)〕
  nPropVal = 100000;
  return sub_4E1390(196613, &nPropVal);  // 条件/属性 id 追加（前缀 255/254/253 通配 + 配额扣减 + 日志）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3510 sub_5B3510 —— 与 ·0x5B3420 同构（差异：末项段号偏置为 +50 乙向）
// 攻击参数面复位后 this+7596 = +50，供另一侧换目标横向对齐【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3510(int this, int nArg2, int nArg3)  // 实现：与 ·0x5B3420 同构（差异：末项段号偏置为 +50 乙向）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint8_t *)(this + 7557) = 1;  // this+7557〔bAtk7557(推断)〕
  *(uint32_t *)(this + 7588) = 1;  // this+7588〔uForm7588〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = 50;  // this+7596〔nOffset7596(推断)〕
  return result;
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5B35C0 sub_5B35C0 —— 空骨鱼·技能变体丙（出场参数插值装填）
// this[2151] = 30012；经 vt+384 取出场参数面 12/13 两点作插值起止，用 vt+672(3) 控制柄元素数 -1 作帧上限，
// ·sub_4049C0 浮点区间线性插值（t≥tEnd 返回终点，t≤0 返回起点）后写 this[2150] AI 阈值字段，this[2154]=0。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B35C0(uint32_t *this)  // 实现：空骨鱼·技能变体丙（出场参数插值装填）
{
  int pVt; // eax
  uint32_t *pAniCtrl3; // eax
  uint64_t result; // rax
  float fParamStart; // [esp+Ch] [ebp-1Ch]
  float fParamEnd; // [esp+10h] [ebp-18h]
  int nParamStart; // [esp+20h] [ebp-8h]
  int nParamEnd; // [esp+24h] [ebp-4h]

  pVt = *this;
  *(this + 2151) = 30012;  // this+8604〔bAI8604(推断)〕
  nParamStart = (*(int (/*stdcall*/ **)(int))(pVt + 384))(12);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  nParamEnd = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  pAniCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fParamEnd = (float)nParamEnd;
  fParamStart = (float)nParamStart;
  result = (uint64_t)sub_4049C0(fParamStart, fParamEnd, *pAniCtrl3 - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2150) = result;  // this+8600〔uAI8600(推断)〕
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3640 sub_5B3640 —— 缓速动画对象生成（0x8C 参数体）
// ·sub_4DE410 名称模板与随机倒计时 → vt+700 激活族 → ·sub_53F6A0 注册；new(0x8C) 经
// ·sub_64CEF0(300,3000,100.0f,10) 构造后由 vt+56 绑定到本体【推断：迟缓/冻缓附着效果】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3640(void *this)  // 实现：缓速动画对象生成（0x8C 参数体）
{
  int pObj; // eax

  sub_4DE410();  // 名称模板写入 + 随机倒计时
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
  sub_53F6A0(this);  // 调 收尾路径
  if ( operator new(0x8Cu) != nullptr )  // new(140 字节) 分配对象
    pObj = sub_64CEF0(300, 3000, 1120403456, 10);  // 缓速动画查询（5910D0）
  else  // 否则分支
    pObj = 0;
  return (*(int (/*thiscall*/ **)(int, void *, void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
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
// 纯转发 thunk：直调 ·sub_6098E0（CNRDJoint vt+332 槽，AI 字段访问器）。
// DNF 客户端把空骨鱼/机械类节点对象的关节字段读取统一收敛到 CNRDJoint 基类，本桩无自身逻辑。
// ------------------------------------------------------------
// attributes: thunk
int sub_5B36E0()  // 实现：DNF 客户端把空骨鱼/机械类节点对象的关节字段读取统一收敛到 CNRDJoint 基类，本桩无自身逻辑
{
  return sub_6098E0();  // 【CNRDJoint__vmt14C】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B36F0 sub_5B36F0 —— 子相位索引映射（this+1008 → 编号）
// 读 *(this+252) 子相位：0/1/5/6→15、2→13、3→10、4→5、其余 0，供上层选资源/动画【推断：相位→资源档映射】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B36F0(uint32_t *this)  // 实现：子相位索引映射（this+1008 → 编号）
{
  int result; // eax

  switch ( *(this + 252) )  // 按 *(this + 252) 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      result = 15;
      break;  // 跳出循环/分支
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = 13;
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = 10;
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = 5;
      break;  // 跳出循环/分支
    default:  // 默认分支
      result = 0;
      break;  // 跳出循环/分支
  }
  return result;
}



// 时钟门+插值 AI（sub_699000+sub_4049C0）
// ------------------------------------------------------------
// 0x5B3740 sub_5B3740 —— 计时衰减收尾门（600ms 后复位句柄）
// this+264 非 1 时以 ·sub_699000 减 this+992 基准取帧差：有从属(this+120) 则 ·sub_4049C0 把 255→0
// 于 600ms 内插值写 vt+252 槽；差满 600（·0x258）时 vt+196 清动作句柄，本地玩家再 vt+312 收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3740(uint32_t *this)  // 实现：计时衰减收尾门（600ms 后复位句柄）
{
  unsigned int fld_e248; // edi  | +0x03E0 → uCfgB992〔族字典〕（族字典）
  uint64_t nLerpVal; // rax

  if ( *((uint8_t *)this + 264) != 1 )  // this+264〔nAnimHandle(推断)〕
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )  // this+120〔pAnimObj〕
    {
      nLerpVal = (uint64_t)sub_4049C0(255.0, 0.0, fld_e248, 600);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, nLerpVal);  // 调虚槽 +252
    }
    if ( fld_e248 >= 0x258 )  // 若 fld_e248 >= 0x258
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);  // 调虚槽 +196：动画对象设置（换域 + 播放）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 调虚槽 +312：濒死/一击表现(LAST STRIKE)
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
int /*thiscall*/ sub_5B37C0(uint32_t *this)  // 实现：齐射弹幕生成（发数 = 动画块 816×830 乘积）
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

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    aSpawnXY[0] = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    nY1 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    pVt = *this;
    aSpawnXY[1] = nY1;
    nParamX = (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    nY2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    pVt2 = *this;
    nParamY = nY2;
    pAniCtrl3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 672))(this, 3);  // 调虚槽 +672：自身 HP
    nCtrl816 = sub_41A5E0(pAniCtrl3 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
    fCtrl830 = COERCE_FLOAT(sub_41A5E0(pAniCtrl3 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    nProduct = (uint64_t)((double)nCtrl816 * fCtrl830);
    result = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 384))(  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
               this,
               (uint64_t)((double)nCtrl816 * fCtrl830) >> 32,
               0);
    nSpawnIdx = 0;
    fCtrl830 = *(float *)&result;
    if ( result > 0 )  // 若 result > 0
    {
      do  // do-while 循环体起点
      {
        nNextIdx = nSpawnIdx + 1;
        nSpawnItem = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, nSpawnIdx + 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
        pVt3 = *this;
        fld_e2151 = *(this + 2151);  // this+8604〔bAI8604(推断)〕
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
        nParamX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
        result = LODWORD(fCtrl830);  // result = 调 LODWORD
        nParamY = nSpawnRet;
        nSpawnIdx = nNextIdx;
      }
      while ( nNextIdx < SLODWORD(fCtrl830) );  // 条件循环
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
int /*thiscall*/ sub_5B38C0(uint32_t *this)  // 实现：交互收尾+模式门动画加速
{
  int pVt; // edi
  int nPoseParity; // eax
  int *pWorldObj; // ecx
  int nSegIdx; // ecx
  unsigned int pAniCtrl830; // edi
  int edxTmp; // edx
  unsigned int pAniCtrl858; // edi
  int edxTmp2; // edx
  int fVal830; // [esp+8h] [ebp-4h]
  int fVal858; // [esp+8h] [ebp-4h]

  sub_4D9600();  // 交互收尾（this+7820 的 8 字节信息消费）
  pVt = *this;
  nPoseParity = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this) % 2;  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(pVt + 148))(this, nPoseParity == 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  pWorldObj = nullptr;  // pWorldObj = 空指针
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )  // 登录/选区管理器
  {
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      pWorldObj = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);  // 登录/选区管理器
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pWorldObj = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);  // 登录/选区管理器
      break;  // 跳出循环/分支
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      pWorldObj = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);  // 登录/选区管理器
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  nSegIdx = *pWorldObj;
  if ( nSegIdx >= 15 && nSegIdx <= 16 )  // 若 nSegIdx >= 15 与/或 nSegIdx <= 16
  {
    pAniCtrl830 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pAniCtrl830)) + 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl830, edxTmp, fVal830);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pAniCtrl858 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&fVal858 = COERCE_FLOAT(sub_41A5E0(pAniCtrl858)) + 0.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl858, edxTmp2, fVal858);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return sub_5B37C0(this);  // 齐射弹幕生成（发数 = 动画块 816×830 乘积）
}



// 虫弹连射：SFISH_BUG_SPIT 蓄力 + SFISH_BUG_FIRE 发射（91L；this+8612 相位）
// ------------------------------------------------------------
// 0x5B39C0 sub_5B39C0 —— 虫鱼攻击事件分发（SFISH_BUG_SPIT/FIRE）
// 段 14 转发 vt+1144 直通事件参数；段 8 预检：8608 时间戳未满 3000ms 或全局 ·0x9B9414>=20 提前返回，
// 否则清 this+8612。基线 ·sub_4E33D0 后——段 5：vt+216 播 45931 并逐个子对象 vt+712(x,2)；
// 段 8 按攻击段(7028) 播 SFISH_BUG_SPIT(1)/SFISH_BUG_FIRE(2)，为 0 时子对象 vt+712(x,1) 且行为字 25 转 13。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B39C0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：虫鱼攻击事件分发（SFISH_BUG_SPIT/FIRE）
{
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_e1769; // ecx
  unsigned int j; // edi
  int fld_e17692; // ecx

  if ( ArgList == 14 )  // 若 ArgList == 14
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 1144))(  // 调虚槽 +1144：IRDCharacter__vmt478 默认虚槽桩（10 行 return）
             this,
             **(uint32_t **)(LODWORD(fArg3) + 4),
             *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4));
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    result = *(uint32_t *)(LODWORD(fArg3) + 4);
    if ( *(uint32_t *)result == 1 || *(uint32_t *)result == 2 )  // 复合条件判定（与/或）
    {
      if ( dword_9B9414 >= 20 )  // 若 dword_9B9414 >= 20
        return result;
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 2152) + 3000 >= result )  // this+8608〔uAI8608(推断)〕
        return result;
      *((uint8_t *)this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 5 )  // 若 ArgList == 5
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 45931);  // 调虚槽 +216：音效 TAG 查询
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      fld_e1769 = *(this + 1769);
      if ( fld_e1769 == 0 )  // 若 fld_e1769 为 0
        break;  // 跳出循环/分支
      result = (*(this + 1770) - fld_e1769) >> 2;  // 向量元素数 = (end−begin)/4
      if ( i >= result )  // 若 i >= result
        break;  // 跳出循环/分支
      result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e1769 + 4 * i) + 712))(*(uint32_t *)(fld_e1769 + 4 * i), 2);  // 调虚槽 +712：表尾插 thunk（+1020 表 → sub_474950）
    }
  }
  else if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                 this,
                 "SFISH_BUG_SPIT",  // 标签 SFISH_BUG_SPIT
                 -1,
                 0,
                 0);
      }
      else  // 否则分支
      {
        result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
        if ( result == 2 )  // 若 result == 2
          return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                   this,
                   "SFISH_BUG_FIRE",  // 标签 SFISH_BUG_FIRE
                   -1,
                   0,
                   0);
      }
    }
    else  // 否则分支
    {
      for ( j = 0; ; ++j )  // 无限循环：j 从 0 递增
      {
        fld_e17692 = *(this + 1769);
        if ( fld_e17692 == 0 )  // 若 fld_e17692 为 0
          break;  // 跳出循环/分支
        result = (*(this + 1770) - fld_e17692) >> 2;  // 向量元素数 = (end−begin)/4
        if ( j >= result )  // 若 j >= result
          break;  // 跳出循环/分支
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e17692 + 4 * j) + 712))(*(uint32_t *)(fld_e17692 + 4 * j), 1);  // 调虚槽 +712：表尾插 thunk（+1020 表 → sub_474950）
      }
      if ( *(this + 1787) == 25 )  // this+7148〔nBigState〕
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
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
int /*thiscall*/ sub_5B3B50(uint32_t *this, int nArg2)  // 实现：大状态进入副作用（特殊型 25 时半速化）
{
  int result; // eax
  int *pSpeedField; // ecx

  result = sub_4DBA80(nArg2);  // 大状态进入副作用处理器（增益侧）
  if ( *(this + 1787) == 25 )  // this+7148〔nBigState〕
  {
    *(uint32_t *)(*(this + 1905) + 12) = 1120403456;  // this+7620〔pStatusPanel(推断)〕
    pSpeedField = (int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) + 40);  // 调虚槽 +1032
    result = *pSpeedField / 2;
    *pSpeedField = result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3B90 sub_5B3B90 —— 大状态退出副作用（25 型还原对偶）
// 与 ·sub_5B3B50 对称：行为字 25 时向 this+7620 对象 +12 写 0 并把速度源 +40 翻倍还原，
// 尾调 ·sub_4DBC20 退出处理器。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3B90(uint32_t *this, int nArg2)  // 实现：大状态退出副作用（25 型还原对偶）
{
  int pObjBlk; // eax

  if ( *(this + 1787) == 25 )  // this+7148〔nBigState〕
  {
    *(uint32_t *)(*(this + 1905) + 12) = 0;  // this+7620〔pStatusPanel(推断)〕
    pObjBlk = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this);  // 调虚槽 +1032
    *(uint32_t *)(pObjBlk + 40) *= 2;  // pObjBlk+40〔bStateSub40(推断)〕
  }
  return sub_4DBC20(nArg2);  // 大状态退出副作用处理器（0x4DBA80 的还原对偶）
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
int /*thiscall*/ sub_5B3BD0(uint32_t *this, uint32_t *pArg2, int nArg3, int nArg4)  // 实现：吞噬反噬+BUFF_TAKE（尾调反击判定）
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
  int nCtorState; // [esp+138h] [ebp-4h]

  pArg22 = pArg2;
  dword_796E502 = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    pListVec = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);  // 调虚槽 +700：读 +6296 槽
    pVecBegin = *(uint32_t *)(pListVec + 4);
    nIdx = 0;
    if ( pVecBegin != 0 )  // 若 pVecBegin 非 0
      Block = (*(uint32_t *)(pListVec + 8) - pVecBegin) >> 2;  // 向量元素数 = (end−begin)/4
    else  // 否则分支
      Block = 0;
    nCount = 0;
    nSwallowCnt = 0;
    if ( Block > 0 )  // 若 Block > 0
    {
      do  // do-while 循环体起点
      {
        pVecBegin2 = *(uint32_t *)(pListVec + 4);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
          pListObj = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else  // 否则分支
          pListObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj + 92))(pListObj) != 0 )  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
        {
          pVecBegin3 = *(uint32_t *)(pListVec + 4);
          if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pListVec + 8) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
            pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
          else  // 否则分支
            pListObj2 = 0;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pListObj2 + 76))(pListObj2, 0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
          if ( ++nCount >= *(this + 2154) )  // this+8616〔uAI8616(推断)〕
            break;  // 跳出循环/分支
        }
        ++nIdx;
      }
      while ( (int)nIdx < Block );  // 条件循环
      nSwallowCnt = nCount;
      if ( nCount > 0 )  // 若 nCount > 0
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 956))(pArg2);  // 调虚槽 +956
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        {
          if ( pArg2[78] < 0x10u )
            pszNameBuf = pArg2 + 73;
          else  // 否则分支
            pszNameBuf = (uint32_t *)pArg2[73];
          pNameBufSaved = pszNameBuf;
          pszFmt = (const char *)sub_422E70(880);  // pszFmt = 调 sub_422E70 返回值
          sprintf(Buffer, pszFmt, pNameBufSaved);  // 拼字符串
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -13487396, 0, -1);  // 主管理器(消息/弹窗)
        }
      }
    }
    nTotalDmg = (uint64_t)((double)nSwallowCnt * *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this));  // 反噬总伤害=吞噬计数×vt+348 单位值【推断】
    if ( nTotalDmg > 0 )  // 若 nTotalDmg > 0
    {
      Blocka = operator new(0x80u);  // new(128 字节) 分配对象
      nCtorState = 0;
      if ( Blocka != nullptr )  // 若 Blocka 有效（非空）
      {
        fCountF = (float)nTotalDmg;
        pTextObj = (int *)sub_4D6810(LODWORD(fCountF), 1000, 1, 1);  // 创建受击/飘字对象(数值,1000,1,1)【推断】
      }
      else  // 否则分支
      {
        pTextObj = nullptr;  // pTextObj = 空指针
      }
      pTextObjVt = *pTextObj;
      nCtorState = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        pTextObj,
        this,
        this,
        0,
        0,
        0,
        -1);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BUFF_TAKE", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    pArg22 = pArg2;
  }
  return sub_4DB480(pArg22, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3E00 sub_5B3E00 —— 相位→资源装载（this+1004 计数 3 倍）
// 子相位 this+1008<=6 时把句柄表 *(this+144+4×相位) 经 vt+196 装载；this+1004 写 3×vt+708。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E00(unsigned int *this)  // 实现：相位→资源装载（this+1004 计数 3 倍）
{
  unsigned int fld_e252; // eax
  int result; // eax

  fld_e252 = *(this + 252);  // this+1008〔bVineDone1008(推断)〕
  if ( fld_e252 <= 6 )  // 若 fld_e252 <= 6
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * fld_e252));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  result = 3 * (*(int (/*thiscall*/ **)(unsigned int *))(*this + 708))(this);  // 调虚槽 +708：CMOlreks 油桶构造 vmt2C4
  *(this + 251) = result;  // this+1004〔nOilValD1004(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3E40 sub_5B3E40 —— 动画子链切换门（this+972 序号缓存）
// 序号变化时 ·sub_609720 走 RTTI 虚方法：1=相位 5 复位帧游标 *(this+144)+28、相位 6 用 +32（先
// ·sub_4926A0 复位再 vt+196 取句柄）后 vt+596(this,1)；2=vt+260(this,1,5,-1) 起攻击段【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E40(int *this, int nArg2)  // 实现：动画子链切换门（this+972 序号缓存）
{
  int result; // eax
  uint32_t *fld_e36; // eax

  result = *(this + 243);  // this+972〔uCfgD972(推断)〕
  if ( result != nArg2 )  // 若 result != nArg2
  {
    result = sub_609720(nArg2);  // 【CNRDJoint__vmt2C8】
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      if ( *(this + 252) == 5 )  // this+1008〔bVineDone1008(推断)〕
      {
        sub_4926A0(*(uint32_t *)(*(this + 36) + 28));  // 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e36 = (uint32_t *)(*(this + 36) + 28);  // this+144〔pFrameList144(推断)〕
      }
      else  // 否则分支
      {
        if ( *(this + 252) != 6 )  // this+1008〔bVineDone1008(推断)〕
          return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
        sub_4926A0(*(uint32_t *)(*(this + 36) + 32));  // 帧游标复位（+44 帧数组；递归子链 +204）
        fld_e36 = (uint32_t *)(*(this + 36) + 32);  // this+144〔pFrameList144(推断)〕
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *fld_e36);  // 调虚槽 +196：动画对象设置（换域 + 播放）
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);  // 调虚槽 +596：[RTTI: IRDCollisionObject__vmt254 · 槽位 IRDActi…
    }
    if ( nArg2 == 2 )  // 若 nArg2 == 2
      return (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 260))(this, 1, 5, -1);  // 调虚槽 +260
  }
  return result;
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x5B3EF0 sub_5B3EF0 —— 播放态收尾门（+170 标记）
// vt+200 取主状态对象，其 +170 非 0（播放完毕标记）时按子相位经 vt+196 装载句柄表
// *(this+144+4×相位)【推断：动画播完回落到相位默认资源】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3EF0(uint32_t *this)  // 实现：播放态收尾门（+170 标记）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * *(this + 252)));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  return result;
}



// 空骨鱼语音装载：SFISH_FIND/BITE/DMG/DIE 四件套（sub_4015C0+sub_699000）
// ------------------------------------------------------------
// 0x5B3F30 sub_5B3F30 —— 空骨鱼语音四件套 + 时间戳（this+8608）
// ·sub_4015C0 依次装载 SFISH_FIND/BITE（10 字节）与 SFISH_DMG/DIE（9 字节）；
// 末 ·sub_699000 记时间戳入 this+8608，供 ·sub_5B39C0 的 3000ms 门比对。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3F30(uint32_t *this)  // 实现：空骨鱼语音四件套 + 时间戳（this+8608）
{
  int result; // eax

  sub_4015C0("SFISH_FIND", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_BITE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DIE", 9u);  // 【std::string构造赋值】
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2152) = result;  // this+8608〔uAI8608(推断)〕
  return result;
}



// AI 相位辅助（69L）
// ------------------------------------------------------------
// 0x5B3F90 sub_5B3F90 —— 映射对象筛选→setState 14（架招/牵制态）
// 遍历 *(this+116) 对象列表，取 vt+40 标记 545 的映射物；经 vt+1244(this,obj) 校验且其
// vt+340 返回值 ==258 时，用 ·sub_430C80 打包该对象 vt+120/124 坐标（两组），再 vt+560 切 14 态。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3F90(uint32_t *this)  // 实现：映射对象筛选→setState 14（架招/牵制态）
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
  uint8_t pBuf[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  void *Src; // [esp+14h] [ebp-1Ch]
  int nPad1; // [esp+18h] [ebp-18h]
  uint32_t *pThis; // [esp+1Ch] [ebp-14h]
  int aParamVec[4]; // [esp+20h] [ebp-10h] BYREF

  pThis = this;
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    pVecBegin = *(uint32_t *)(fld_e29 + 8);
    nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= nCnt )
      break;  // 跳出循环/分支
    pVecBegin2 = *(uint32_t *)(fld_e29 + 8);
    if ( pVecBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
      pMapObj = *(uint32_t *)(pVecBegin2 + 4 * i);
    else  // 否则分支
      pMapObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pMapObj + 40))(pMapObj, 545) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      fld_e292 = *(this + 29);  // this+116〔会话上下文〕
      pVecBegin3 = *(uint32_t *)(fld_e292 + 8);
      if ( pVecBegin3 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
        pFoundObj = *(int **)(pVecBegin3 + 4 * i);
      else  // 否则分支
        pFoundObj = nullptr;  // pFoundObj = 空指针
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *))(*this + 1244))(this, pFoundObj) != 0  // 调虚槽 +1244
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pFoundObj + 340))(pFoundObj) == 258 )  // 调虚槽 +340：三元组基址（+284，vt+340）
      {
        if ( pFoundObj != nullptr )  // 若 pFoundObj 有效（非空）
        {
          Block = nullptr;  // Block = 空指针
          Src = nullptr;  // Src = 空指针
          nPad1 = 0;
          pFoundObjVt = *pFoundObj;
          aParamVec[3] = 0;
          aParamVec[0] = (*(int (/*thiscall*/ **)(int *))(pFoundObjVt + 120))(pFoundObj);  // 调虚槽 +120：动画对象
          sub_430C80(nullptr, 1, (int)aParamVec);  // uint32 vector 区间插入（同值填充）
          aParamVec[0] = (*(int (/*thiscall*/ **)(int *))(*pFoundObj + 124))(pFoundObj);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          sub_430C80(nullptr, 1, (int)aParamVec);  // uint32 vector 区间插入（同值填充）
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pThis + 560))(pThis, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
          if ( Block != nullptr )  // 若 Block 有效（非空）
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
// vt+308 目标门内：·sub_431230 打包初值 0 为参数表 pBuf，经 vt+560(this,8,pBuf,0,0) 切 8 号状态，
// 释放缓冲后尾调 ·sub_4D9F40【推断：攻击段起手封装】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4120(void *this)  // 实现：存活门内 setState 8 起手（参数表打包）
{
  uint8_t pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int nPad1; // [esp+Ch] [ebp-18h]
  int nPad2; // [esp+10h] [ebp-14h]
  int aArgList; // [esp+14h] [ebp-10h] BYREF
  int nCtorState; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
    nCtorState = 0;
    aArgList = 0;
    sub_431230((int)pBuf, &aArgList);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 8, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    nCtorState = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
  }
  return sub_4D9F40(this);  // 返回 调 sub_4D9F40 返回值
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B41C0 sub_5B41C0 —— 行为字决策+低血线触发（VT 家族 AI 节拍）
// ·sub_4E0120 基线后按行为字 this[1787]：0→vt+1284 空闲例程；4→有目标(pArg1[1813]) 时 2% 概率
// vt+1104 写 5；5→有目标 2% 写 4、无目标写 13；13/14/15→有目标写 4。
// 末门：当前血 vt+736 < 上限 vt+740 的 50% 且非 25 态时调 ·sub_5B3F90 切 14（架招）【推断：血线反制】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B41C0(uint32_t *this)  // 实现：行为字决策+低血线触发（VT 家族 AI 节拍）
{
  float fHpCur; // [esp+4h] [ebp-8h]

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_4;
      if ( rand() % 100 < 2 )  // 2% 概率触发（rand()%100 < 2）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        if ( rand() % 100 < 2 )  // 2% 概率触发（rand()%100 < 2）
          goto LABEL_11;
      }
      else  // 否则分支
      {
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
LABEL_11:  // 标签 LABEL_11（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    fHpCur = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.5 > fHpCur && *(this + 1787) != 25 )  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
      sub_5B3F90(this);  // 映射对象筛选→setState 14（架招/牵制态）
  }
}



// 破坏特效：PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl（头部击破, 53L）
// ------------------------------------------------------------
// 0x5B42F0 sub_5B42F0 —— 头部击破粒子（CrokutaDestroyHead.ptl）
// new(0x12C) 经 ·sub_428F30(ptl 路径, 本体) 构造，vt+12(0) 起播、vt+40 坐标对齐（vt+128→124→120 链）；
// 粒子参数块 +15..+35 交替写 800/500（六向喷射量），+76 随机 0-359 初角，·sub_4600B0 投递映射层后 vt+0(1) 激活。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B42F0(uint32_t *this)  // 实现：头部击破粒子（CrokutaDestroyHead.ptl）
{
  uint32_t *pMem; // eax
  uint32_t *pHeadPtl; // esi
  int pHeadPtlVt; // eax
  int pHeadPtlVt2; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int nRand; // ebx
  void *pFollowAnim; // ecx
  uint8_t pBuf[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int nCtorState; // [esp+28h] [ebp-4h]

  pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
  pMem2 = pMem;
  nCtorState = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pHeadPtl = sub_428F30(pMem, (int)"PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl", (int)this);  // CNRDObjectParticleCreater 构造
  else  // 否则分支
    pHeadPtl = nullptr;  // pHeadPtl = 空指针
  pHeadPtlVt = *pHeadPtl;
  nCtorState = -1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(pHeadPtlVt + 12))(pHeadPtl, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
  pHeadPtlVt2 = *pHeadPtl;
  nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nY);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t *, int))(pHeadPtlVt2 + 40))(pHeadPtl, nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 15) = 800;  // 粒子参数块(+15..+35) 800/500 交替【推断：六向喷射量】
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 19) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 23) = 800;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 27) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 31) = 800;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 35) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  nRand = rand() % 360;  // 随机初始角度(0-359 度)
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pHeadPtl + 28))(pHeadPtl) + 76) = nRand;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *))(*pHeadPtl + 92))(pHeadPtl, pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
  pFollowAnim = (void *)*(this + 29);  // this+116〔会话上下文〕
  nCtorState = 1;
  sub_4600B0(pFollowAnim, 2, 0, (int)pBuf);  // 调 演播层注册(槽号)
  (*(void (/*thiscall*/ **)(uint32_t *, int))*pHeadPtl)(pHeadPtl, 1);
  if ( Block != nullptr )  // 若 Block 有效（非空）
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
void /*thiscall*/ sub_5B4430(uint32_t *this)  // 实现：分节破坏粒子（按子相位取 JOINT 部位名）
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
  void *pFollowAnim; // ecx
  void *pMem; // [esp+4h] [ebp-230h]
  uint32_t aJointNames[3]; // [esp+8h] [ebp-22Ch]
  const char *pszJoint4; // [esp+14h] [ebp-220h] BYREF
  void *Block; // [esp+18h] [ebp-21Ch]
  char (**pJoint5Slot)[10]; // [esp+1Ch] [ebp-218h]
  const char *pszTail; // [esp+20h] [ebp-214h]
  char Buffer[512]; // [esp+24h] [ebp-210h] BYREF
  int dword_796E502; // [esp+224h] [ebp-10h]
  int nCtorState; // [esp+230h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *((uint8_t *)this + 264) != 1 )  // this+264〔nAnimHandle(推断)〕
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )  // this+120〔pAnimObj〕
    {
      nLerpVal = (uint64_t)sub_4049C0(255.0, 80.0, fld_e248, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, nLerpVal);  // 调虚槽 +252
    }
    if ( fld_e248 >= 0x1F4 )  // 若 fld_e248 >= 0x1F4
    {
      nSegIdx = *(this + 252);  // this+1008〔bVineDone1008(推断)〕
      aJointNames[0] = "JOINT1";  // 标签 JOINT1
      aJointNames[1] = "JOINT2";  // 标签 JOINT2
      aJointNames[2] = "JOINT3";  // 标签 JOINT3
      pszJoint4 = "JOINT4";  // 标签 JOINT4
      Block = "JOINT5";  // 标签 JOINT5
      pJoint5Slot = &off_72F738;
      pszTail = "TAIL";  // 标签 TAIL
      sprintf(Buffer, "Particle/CrokutaDestroy%s.ptl", (const char *)aJointNames[nSegIdx]);  // 拼字符串（模板 Particle/CrokutaDestroy%s.ptl）
      pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
      nCtorState = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
      {
        if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
          pSegPtl = (int *)sub_4C3640(this + 91, Buffer, this);  // pSegPtl = 调 sub_4C3640 返回值
        else  // 否则分支
          pSegPtl = (int *)sub_4C3640(*(this + 91), Buffer, this);  // pSegPtl = 调 sub_4C3640 返回值
      }
      else  // 否则分支
      {
        pSegPtl = nullptr;  // pSegPtl = 空指针
      }
      pSegPtlVt = *pSegPtl;
      nCtorState = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(pSegPtlVt + 12))(pSegPtl, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      pSegPtlVt2 = *pSegPtl;
      nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nY);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int *, int))(pSegPtlVt2 + 40))(pSegPtl, nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 15) = 800;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 19) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 23) = 800;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 27) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 31) = 800;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 35) = 500;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      nRand = rand() % 360;  // nRand = 调 rand
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pSegPtl + 28))(pSegPtl) + 76) = nRand;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(int *, const char **))(*pSegPtl + 92))(pSegPtl, &pszJoint4);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      pFollowAnim = (void *)*(this + 29);  // this+116〔会话上下文〕
      nCtorState = 1;
      sub_4600B0(pFollowAnim, 2, 0, (int)&pszJoint4);  // 调 演播层注册(槽号)
      (*(void (/*thiscall*/ **)(int *, int))*pSegPtl)(pSegPtl, 1);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);  // 调虚槽 +196：动画对象设置（换域 + 播放）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 调虚槽 +312：濒死/一击表现(LAST STRIKE)
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B46A0 sub_5B46A0 —— 映射对象族判定（vt+340 ∈ 250..253）
// vt+340 返回指针所指数值做 {250..253} 四值判定【推断：载体/子弹族标签；调用方多为同源(vt+376) 确认，结果常被丢弃】。
// ------------------------------------------------------------
bool /*cdecl*/ sub_5B46A0(int nArg1)  // 实现：映射对象族判定（vt+340 ∈ 250..253）
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 250  // 调虚槽 +340：三元组基址（+284，vt+340）
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 251  // 调虚槽 +340：三元组基址（+284，vt+340）
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 252  // 调虚槽 +340：三元组基址（+284，vt+340）
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 253;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// 子类扩展字段复位（this+8604..8652, 26L）
// ------------------------------------------------------------
// 0x5B4700 sub_5B4700 —— 子类扩展清零（含 6792..6808 计数槽）
// 清 6792/6796/6800/6804/6808 五槽与 8604/8605/8612/8632/8633/8652 标记字节，
// 8608/8640/8644/8648 归零、8636 写 0xFFFF 哨兵【推断：复活/换阶段时的整块初始化】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4700(int this)  // 实现：子类扩展清零（含 6792..6808 计数槽）
{
  *(uint32_t *)(this + 6792) = 0;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6796) = 0;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6800) = 0;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 6804) = 0;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6808) = 0;  // this+6808〔nVoiceParam4(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  *(uint32_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint8_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint8_t *)(this + 8633) = 0;  // this+8633〔field_8633〕
  *(uint32_t *)(this + 8636) = 0xFFFF;  // this+8636〔pDollTarget(推断)〕
  *(uint32_t *)(this + 8640) = 0;  // this+8640〔uCastSlot8640(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint8_t *)(this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B4770 sub_5B4770 —— 伤害折减门（×0.7）
// ·sub_4DC390 伤害过滤结果==3、或攻击方档位体（vt+348 返回）+128 字节非 0 时原样返回；
// 否则首参（伤害值）乘 0.7 并返回 0【推断：类型 3/带飞行标记者免折减，其余减伤 30%】。
// ------------------------------------------------------------
int /*stdcall*/ sub_5B4770(int *pDwArg1, int nArg2)  // 实现：伤害折减门（×0.7）
{
  int nTypeVal; // esi

  nTypeVal = sub_4DC390(pDwArg1, nArg2);  // 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
  if ( nTypeVal == 3 || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) != 0 )  // 调虚槽 +348：取坐标对象
    return nTypeVal;
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
void /*usercall*/ sub_5B6380(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：ZGM 攻击主循环（命中/高度/近远战三支）
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

  sub_4E1780(pDwArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( pDwArg1[1639] != 8 )
  {
    if ( pDwArg1[1639] == 14 )
    {
      sub_5B5390(pDwArg1, nArg2, nArg3);
    }
    else if ( pDwArg1[1639] == 15 )
    {
      nIsLocal2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 308))(pDwArg1, nArg3);  // 调虚槽 +308：是否本地玩家
      if ( nIsLocal2 != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 若 nIsLocal2 != 0
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      }
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 复合条件判定（与/或）
      {
        pBuddy3 = pDwArg1[30];  // pBuddy3 = 取 pDwArg1[30]
        nAnimId3 = sub_491C70(pBuddy3, 1);  // 帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
        sub_493A60(pBuddy3, nAnimId3);  // 时间推进包装（累计 +32；+212 同步源优先）
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
    return;
  }
  if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 2  // crypt4byte 解密校验（·0x41A590 逆运算）
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 6 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 1 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 30 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        {
          pVt2 = *pDwArg1;
          nYClamped = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 124))(pDwArg1, 30, nArg3);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          nXClamped = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nYClamped);  // 调虚槽 +120：动画对象
          (*(void (/*thiscall*/ **)(int *, int))(pVt2 + 112))(pDwArg1, nXClamped);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          nClockObj844 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 844))(pDwArg1);  // 调虚槽 +844：内嵌动作子对象 this+6560
          if ( sub_699000(nClockObj844) > 1000 )  // 【clock_now(clk)】
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        }
      }
      return;
    }
    nIsLocal3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调虚槽 +308：是否本地玩家
    if ( nIsLocal3 == 0 )  // 若 nIsLocal3 为 0
      goto LABEL_60;
    if ( *(int *)(pDwArg1[30] + 148) >= 1 )
    {
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
        goto LABEL_57;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 80, 80, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pVt3 = *pDwArg1;
      hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(int *, int))(pVt3 + 896))(pDwArg1, hAniKind4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      nCamAmp = 150;
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        nCamAmp = 300;
      sub_4A0550(nCamAmp);  // 调 镜头幅度
    }
    if ( *((uint8_t *)pDwArg1 + 8604) == 0 )
    {
LABEL_60:  // 标签 LABEL_60（跳转合流点）
      nFallFlag = *((uint8_t *)pDwArg1 + 8604);
      if ( nFallFlag != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 若 nFallFlag != 0
        *((uint8_t *)pDwArg1 + 8605) = 1;
      pBuddy128 = pDwArg1[28];  // pBuddy128 = 取 pDwArg1[28]
      if ( *(float *)(pBuddy128 + 24) > 0.0 && nFallFlag == 0 )  // 若 nFallFlag == 0
        *((uint8_t *)pDwArg1 + 8604) = 1;
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
      {
        if ( *(float *)(pBuddy128 + 24) > 0.0 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) > 130 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        {
          pResSlot8 = (uint32_t *)(pDwArg1[1554] + 8);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *pResSlot8 )  // 调虚槽 +200：取动画对象
          {
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
            (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 344))(pDwArg1, pDwArg1[139] + 152);  // 调虚槽 +344：取坐标三元组
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
          }
        }
        if ( *((uint8_t *)pDwArg1 + 8604) != 0
          && *(float *)(pDwArg1[28] + 24) < 0.0
          && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 15 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        {
          pResSlot12 = (uint32_t *)(pDwArg1[1554] + 12);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *pResSlot12 )  // 调虚槽 +200：取动画对象
          {
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));  // 帧游标复位（+44 帧数组；递归子链 +204）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));  // 调虚槽 +196：动画对象设置（换域 + 播放）
          }
        }
      }
      return;
    }
LABEL_57:  // 标签 LABEL_57（跳转合流点）
    if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 复合条件判定（与/或）
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
    goto LABEL_60;
  }
  nIsLocal = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调虚槽 +308：是否本地玩家
  if ( nIsLocal == 0 )  // 若 nIsLocal 为 0
    goto LABEL_24;
  if ( *(int *)(pDwArg1[30] + 148) >= 1 )
  {
    if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    {
LABEL_21:  // 标签 LABEL_21（跳转合流点）
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 复合条件判定（与/或）
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      }
LABEL_24:  // 标签 LABEL_24（跳转合流点）
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )  // 复合条件判定（与/或）
      {
        pBuddy = pDwArg1[30];  // pBuddy = 取 pDwArg1[30]
        nAnimId = sub_491C70(pBuddy, 15);  // 帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
        sub_493A60(pBuddy, nAnimId);  // 时间推进包装（累计 +32；+212 同步源优先）
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      goto LABEL_28;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 200, 200, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    pVt = *pDwArg1;
    nZ30 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 896))(pDwArg1, nZ30);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    sub_4A0550(120);  // 调 镜头幅度
  }
  if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    goto LABEL_21;
LABEL_28:  // 标签 LABEL_28（跳转合流点）
  if ( *(float *)(pDwArg1[28] + 24) > 0.0 && *((uint8_t *)pDwArg1 + 8604) == 0 )  // 复合条件判定（与/或）
  {
    pBuddy2 = pDwArg1[30];  // pBuddy2 = 取 pDwArg1[30]
    if ( *(int *)(pBuddy2 + 148) < 1 )
    {
      nAnimId2 = sub_491C70(pBuddy2, 1);  // 帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
      sub_493A60(pBuddy2, nAnimId2);  // 时间推进包装（累计 +32；+212 同步源优先）
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
int /*usercall*/ sub_5B6420@<eax>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：移动攻击循环装配（MOVING_ATTACK_LOOP）
{
  int nBigState; // eax
  int pVt; // edi
  int nY30; // eax
  int nXClamped; // eax
  uint32_t *pResSlot20; // edi
  int result; // eax
  int nPhaseDeadline; // [esp+8h] [ebp-4h]

  sub_5B6380((int *)pArg1, nArg2);  // ZGM 攻击主循环（命中/高度/近远战三支）
  nBigState = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( nBigState == 8 )  // 若 nBigState == 8
  {
    if ( sub_41A5E0(pArg1 + 7028) == 5 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      pVt = *(uint32_t *)pArg1;
      nY30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, 30);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nXClamped = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, nY30);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(pVt + 112))(pArg1, nXClamped);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pResSlot20 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20);  // pArg1+6216〔pTbl6216(推断)〕
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) == *pResSlot20 )  // 调虚槽 +200：取动画对象
      {
        if ( sub_699000(pArg1 + 6560) < 10000 )  // 【clock_now(clk)】
        {
          nPhaseDeadline = *(uint32_t *)(pArg1 + 8684);  // pArg1+8684〔bGate8684(推断)〕
          if ( sub_699000(pArg1 + 8660) >= nPhaseDeadline )  // 【clock_now(clk)】
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
              sub_5B51D0(pArg1);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);  // 调虚槽 +352：命中列表双链表清空
            *(uint8_t *)(pArg1 + 8673) = 0;  // pArg1+8673〔bAI8673(推断)〕
            *(uint8_t *)(pArg1 + 8674) = 0;  // pArg1+8674〔bAI8674(推断)〕
            sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          }
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && *(uint32_t *)(pArg1 + 616) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        }
      }
      else if ( sub_699000(pArg1 + 6560) >= 2000 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 16));  // 调虚槽 +208：定时器移除
        sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        *(uint8_t *)(pArg1 + 6573) = 0;
        *(uint8_t *)(pArg1 + 6574) = 0;
        sub_698F90(pArg1 + 6560, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        *(uint8_t *)(pArg1 + 8673) = 0;  // pArg1+8673〔bAI8673(推断)〕
        *(uint8_t *)(pArg1 + 8674) = 0;  // pArg1+8674〔bAI8674(推断)〕
        sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        sub_5B51D0(pArg1);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
          pArg1,
          "MOVING_ATTACK_LOOP",  // 标签 MOVING_ATTACK_LOOP
          9,
          0,
          0);
        *(uint8_t *)(pArg1 + 8652) = 1;  // pArg1+8652〔uPhase8652(推断)〕
      }
    }
  }
  else if ( nBigState == 16
         && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0  // 调虚槽 +308：是否本地玩家
         && (*(uint8_t (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pArg1 + 1248))(pArg1, 2, *(uint32_t *)(pArg1 + 7252)) == 0 )  // 调虚槽 +1248
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result != 8 && *(uint8_t *)(pArg1 + 8652) == 1 )  // 若 result != 8
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);  // 调虚槽 +216：音效 TAG 查询
    *(uint8_t *)(pArg1 + 8652) = 0;  // pArg1+8652〔uPhase8652(推断)〕
  }
  return result;
}



// ZGM 死亡：ZGM_DIE 播报（sub_4015C0+sub_4049C0）
// ------------------------------------------------------------
// 0x5B6630 sub_5B6630 —— ZGM 死亡插值（ZGM_DIE 语音 + this+8620 槽）
// 先 ·sub_4015C0 装载 ZGM_DIE（7 字节）；取 vt+384(0/1) 两端值，以动画控制块首字段相对
// this+7280 的偏移为 t、this+7284−7280 为区间长，·sub_4049C0 插值写入 this+8620（死亡表现槽）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B6630(uint32_t *this)  // 实现：ZGM 死亡插值（ZGM_DIE 语音 + this+8620 槽）
{
  int fld_e1821; // edi
  uint32_t *pCtrl3; // eax
  uint64_t result; // rax
  float fFrom; // [esp+Ch] [ebp-20h]
  float fTo; // [esp+10h] [ebp-1Ch]
  int nFromI; // [esp+24h] [ebp-8h]
  int nToI; // [esp+28h] [ebp-4h]

  sub_4015C0("ZGM_DIE", 7u);  // 【std::string构造赋值】
  nFromI = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  nToI = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fTo = (float)nToI;
  fFrom = (float)nFromI;
  result = (uint64_t)sub_4049C0(fFrom, fTo, *pCtrl3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;  // this+8620〔uAI8620(推断)〕
  return result;
}



// 参数打包 AI（sub_431230+RTTI cast）
// ------------------------------------------------------------
// 0x5B66C0 sub_5B66C0 —— 星鱼绑定确认（RTTI cast + setState 17）
// nArg2 经 __RTDynamicCast 解为 CNStarFish 后，其 vt+52 与目标槽 this+8636 一致且本地门内时，
// ·sub_431230 打包 8636/星鱼 vt+48/52/本体 vt+48/52 五参，vt+560(this,17,pBuf,2,0) 切 17 号【推断：绑定/骑乘准备态】。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B66C0(uint32_t *this, int nArg2)  // 实现：星鱼绑定确认（RTTI cast + setState 17）
{
  int nArg22; // edi
  int pStarFish; // edi
  uint8_t pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int nPad1; // [esp+10h] [ebp-14h]
  int nPad2; // [esp+14h] [ebp-10h]
  int nCtorState; // [esp+20h] [ebp-4h]

  nArg22 = nArg2;
  if ( __RTDynamicCast(nArg2, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0 )
  {
    pStarFish = __RTDynamicCast(nArg22, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);  // pStarFish = 调 __RTDynamicCast
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 52))(pStarFish) == *(this + 2159)  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
      nCtorState = 0;
      sub_431230((int)pBuf, this + 2159);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 48))(pStarFish);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pStarFish + 52))(pStarFish);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 17, pBuf, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      if ( Block != nullptr )  // 若 Block 有效（非空）
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
int /*thiscall*/ sub_5B67F0(uint32_t *this, int *Block, int nArg3, int nArg4)  // 实现：受击架招+分身焚化（吞噬者专支）
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
  int nCtorState; // [esp+4Ch] [ebp-4h]

  pAttacker = Block;
  if ( *(this + 1639) == 8  // this+6556〔大状态ID〕
    && (sub_41A5E0((unsigned int)(this + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
     || sub_41A5E0((unsigned int)(this + 1757)) == 2  // crypt4byte 解密校验（·0x41A590 逆运算）
     || sub_41A5E0((unsigned int)(this + 1757)) == 6)  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pAttacker + 948))(pAttacker) != 0 && *(this + 154) != 14 )  // 调虚槽 +948
    {
      memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
      pVt = *pAttacker;
      nCtorState = 0;
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(pVt + 48))(pAttacker);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
      sub_431230((int)pBuf, &Block);  // uint32 vector push_back
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(*pAttacker + 52))(pAttacker);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      sub_431230((int)pBuf, &Block);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      nCtorState = -1;
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
    }
    pAttackerVt = *pAttacker;
    nProp152 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
    pSparkRes = sub_432E50(nProp152);  // 关系码对调映射
    (*(void (/*thiscall*/ **)(int *, int))(pAttackerVt + 144))(pAttacker, pSparkRes);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  }
  if ( __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishDevourer `RTTI Type Descriptor', 0) != 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    Block = (int *)operator new(0x80u);  // new(128 字节) 分配对象
    nCtorState = 1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
    {
      fDmgVal = *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) * 0.89999998;  // 调虚槽 +348：取坐标对象
      pTextObj = (int *)sub_4D6810(LODWORD(fDmgVal), 500, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
    }
    else  // 否则分支
    {
      pTextObj = nullptr;  // pTextObj = 空指针
    }
    pTextObjVt = *pTextObj;
    nCtorState = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      pTextObj,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  return sub_4DB480(pAttacker, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 参数打包 AI（95L sub_431230）
// ------------------------------------------------------------
// 0x5B69C0 sub_5B69C0 —— 骑乘载具放生（8608 槽清空）
// 载具槽 this+8608 非空时：vt+604/612 放归，先按槽内落点 8640/8644/8648 经 vt+136/112 归位；
// 失败则 vt+124(载具,300,1,1) 试探并经 vt+140 写回落点；载具为本地时打包 [4,0,1,200,200] 经 vt+560 切 4 态并 vt+564 收尾；
// 末段 8612<8620 且 vt+772(载具,5) 与本地门成立时 vt+764(载具,5,0,本体,1) 掷出，槽清 0。
// ------------------------------------------------------------
void /*usercall*/ sub_5B69C0(int *pDwArg1@<ecx>, int nArg2@<ebx>)  // 实现：骑乘载具放生（8608 槽清空）
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
  char pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int nPad1; // [esp+10h] [ebp-18h]
  int nPad2; // [esp+14h] [ebp-14h]
  int nPackVal; // [esp+18h] [ebp-10h] BYREF
  int nCtorState; // [esp+24h] [ebp-4h]

  pRideObj = pDwArg1[2152];  // pRideObj = 取 pDwArg1[2152]
  if ( pRideObj != 0 )  // 若 pRideObj 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pRideObj + 604))(pRideObj, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pDwArg1[2152],
           pDwArg1[2160],
           pDwArg1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 112))(pDwArg1[2152], pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pRideObj2 = pDwArg1[2152];  // pRideObj2 = 取 pDwArg1[2152]
      pRideVt = *(uint32_t *)pRideObj2;
      nPackVal = pRideObj2;
      nPackVal = *pDwArg1;
      nTryY = (*(int (/*thiscall*/ **)(int, int, int, int))(pRideVt + 124))(pRideObj2, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      nTryX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pRideObj2 + 120))(pRideObj2, nTryY);  // 调虚槽 +120：动画对象
      bMoveOk = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(nPackVal + 140))(pDwArg1, pDwArg1 + 2160, pDwArg1 + 2161, nTryX);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pRideObj3 = pDwArg1[2152];  // pRideObj3 = 取 pDwArg1[2152]
      if ( bMoveOk != 0 )  // 若 bMoveOk 非 0
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pRideObj3 + 112))(pRideObj3, pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        pRideVt2 = *(uint32_t *)pRideObj3;
        nAltY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2162]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nAltX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nAltY);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int, int))(pRideVt2 + 112))(pDwArg1[2152], nAltX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
      nCtorState = 0;
      nPackVal = 4;
      sub_431230((int)pBuf, &nPackVal);  // uint32 vector push_back
      nPackVal = 0;
      sub_431230((int)pBuf, &nPackVal);  // uint32 vector push_back
      nPackVal = 1;
      sub_431230((int)pBuf, &nPackVal);  // uint32 vector push_back
      nPackVal = 200;
      sub_431230((int)pBuf, &nPackVal);  // uint32 vector push_back
      nPackVal = 200;
      sub_431230((int)pBuf, &nPackVal);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 4, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 564))(pDwArg1[2152]);
      nCtorState = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 848))(pDwArg1[2152], 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
    if ( pDwArg1[2153] < pDwArg1[2155]
      && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 772))(pDwArg1[2152], 5) != 0  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
      && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调虚槽 +308：是否本地玩家
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
void /*thiscall*/ sub_5B6C00(uint32_t *this)  // 实现：低血召唤门（setState 16）
{
  int pVt; // eax
  uint32_t *pNewObj; // eax
  uint32_t *pNewObj2; // edi
  int pNewObjVt; // edx
  void *pBuf[4]; // [esp+4h] [ebp-24h] BYREF
  float fVal736; // [esp+14h] [ebp-14h] BYREF
  int nVal740; // [esp+18h] [ebp-10h]
  int nCtorState; // [esp+24h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 2164) == 0  // this+8656〔uPair8656(推断)〕
    && *((uint8_t *)this + 8632) == 0 )  // this+8632〔bDevourFlag(推断)〕
  {
    nVal740 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
    pVt = *this;
    fVal736 = (float)nVal740;
    nVal740 = (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 740))(this);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
    if ( (double)nVal740 * 0.30000001 >= fVal736 )
    {
      pNewObj = (uint32_t *)sub_5B6080(this);  // pNewObj = 调 sub_5B6080 返回值
      pNewObj2 = pNewObj;
      if ( pNewObj != nullptr )  // 若 pNewObj 有效（非空）
      {
        memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
        pNewObjVt = *pNewObj;
        nCtorState = 0;
        fVal736 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(pNewObjVt + 48))(pNewObj));  // fVal736 = 调 COERCE_FLOAT
        sub_431230((int)pBuf, &fVal736);  // uint32 vector push_back
        fVal736 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*pNewObj2 + 52))(pNewObj2));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_431230((int)pBuf, &fVal736);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
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
void /*thiscall*/ sub_5B6CF0(uint32_t *this, int nArg2)  // 实现：同源确认+自更新（转星鱼绑定）
{
  int nRoomId; // ebx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )  // 调虚槽 +724：读 +6552 霸体字节
  {
    nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调虚槽 +376：坐标同步包（type 37）
    if ( nRoomId == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )  // 调虚槽 +376：坐标同步包（type 37）
      sub_5B46A0(nArg2);  // 映射对象族判定（vt+340 ∈ 250..253）
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
    *(this + 2164) = 8;  // this+8656〔uPair8656(推断)〕
  }
  sub_5B66C0(this, nArg2);  // 星鱼绑定确认（RTTI cast + setState 17）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B6D70 sub_5B6D70 —— 销毁联动放生（载具槽 8608）
// 销毁对象 pDwArg3 即载具槽 this+8608 且大状态 14 时执行 ·sub_5B69C0 放生；pDwArg3 即本体且载具槽非空时
// 同样放生；尾调 ·sub_4D9170 销毁基线【推断：载具死亡/本体死亡双向解绑】。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B6D70@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：销毁联动放生（载具槽 8608）
{
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )  // 若 pDwArg3 == pDwArg1
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
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
int /*userpurge*/ sub_5B6DC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：ZGM 事件总分发（17 弹簧双人 / 8 落地 / 14 骑乘）
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
  float fFloatArg; // [esp+0h] [ebp-Ch]
  int nEvtP0; // [esp+14h] [ebp+8h]
  int nEvtP4; // [esp+18h] [ebp+Ch]

  if ( ArgList == 17 )  // 若 ArgList == 17
  {
    pEvtArgs = *(int **)(LODWORD(fArg4) + 4);
    nEvtP3 = pEvtArgs[3];  // nEvtP3 = 取 pEvtArgs[3]
    nEvtP0 = *pEvtArgs;
    nEvtP2 = pEvtArgs[2];  // nEvtP2 = 取 pEvtArgs[2]
    nEvtP1 = pEvtArgs[1];  // nEvtP1 = 取 pEvtArgs[1]
    nEvtP4 = pEvtArgs[4];  // nEvtP4 = 取 pEvtArgs[4]
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    nObjA = sub_45EBE0(nEvtP1, nEvtP2);  // nObjA = 调 sub_45EBE0 返回值
    pStarFishA = (int *)__RTDynamicCast(nObjA, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    nObjB = sub_45EBE0(nEvtP3, nEvtP4);  // nObjB = 调 sub_45EBE0 返回值
    result = __RTDynamicCast(nObjB, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);  // result = 调 __RTDynamicCast
    if ( pStarFishA != nullptr && result != 0 )  // 若 pStarFishA != nullptr 与/或 result != 0
    {
      pStarFishAVt = *pStarFishA;
      pStarFishA[2159] = nEvtP0;
      nSyncVal = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)result + 736))(result, 0, 1);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
      return (*(int (/*thiscall*/ **)(int *, int))(pStarFishAVt + 732))(pStarFishA, nSyncVal);  // 调虚槽 +732：CNMapObject__vmt2DC
    }
  }
  else  // 否则分支
  {
    if ( pDwArg1[1639] == 14 )
    {
      if ( ArgList != 14 && (ArgList == 3 || ArgList == 5) )  // 若 ArgList != 14 与/或 ArgList == 3 与/或 ArgList == 5
      {
        pRideObj = pDwArg1[2152];  // pRideObj = 取 pDwArg1[2152]
        if ( pRideObj != 0  // 若 pRideObj 非 0
          && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pRideObj + 772))(pRideObj, 5) != 0  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
          && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
        }
      }
      sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
    }
    switch ( ArgList )  // 按 ArgList 分派
    {
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        *((uint8_t *)pDwArg1 + 8604) = 0;
        *((uint8_t *)pDwArg1 + 8605) = 0;
        if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);  // 调虚槽 +672：自身 HP
          sub_4E99C0(fFloatArg);  // 防篡浮点减法（自减 a2；研究 P27 的 sub_43B5A0 族同构）
          fFloatArg = 0.0;
          (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 676))(pDwArg1);  // 调虚槽 +676
        }
        break;  // 跳出循环/分支
      case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
        sub_5B5B90(LODWORD(fArg4));
        break;  // 跳出循环/分支
      case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
        sub_5B5DC0(pDwArg1);
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
    result = sub_4E33D0(ArgList, fArg4, nArg5, nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
    if ( ArgList == 11 )  // 若 ArgList == 11
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    if ( ArgList != 8 )  // 若 ArgList != 8
      return result;
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 6  // crypt4byte 解密校验（·0x41A590 逆运算）
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1  // crypt4byte 解密校验（·0x41A590 逆运算）
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    else if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 400, 400, 0, -200, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      pVt = *pDwArg1;
      hAniKind4 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);  // 调虚槽 +152：效果通道 3
      return (*(int (/*thiscall*/ **)(int *, int))(pVt + 896))(pDwArg1, hAniKind4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
    else  // 否则分支
    {
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 4 )  // 若 result == 4
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);  // 调虚槽 +672：自身 HP
        sub_4AED60(fFloatArg);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);  // 调虚槽 +676
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
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
int /*userpurge*/ sub_5B7080@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)  // 实现：销毁联动放生变体（多 8656 槽分支）
{
  if ( pDwArg3 == (int *)pDwArg1[2164] )
  {
    sub_5B5F90();
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 472))(pDwArg1, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
  }
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )  // 若 pDwArg3 == pDwArg1
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  return sub_4D9170(pDwArg3);  // 返回 调 sub_4D9170 返回值
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B70F0 sub_5B70F0 —— 事件 16 目标解算（IRDMonster 写 8656 槽）
// 先转发 ·sub_5B6DC0 总线；事件 16 时解事件参数对经 ·sub_45EBE0 取对象，RTTI cast 为 IRDMonster
// 写入 this+8656 槽，命中时 ·sub_5B6000 起手并由 vt+472(0,0,1,1) 收尾【推断：绑定攻击目标】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B70F0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：事件 16 目标解算（IRDMonster 写 8656 槽）
{
  int result; // eax
  int *pEvtObj; // eax
  int pObjCast; // eax
  int pMonsterCast; // eax
  int nEvtX; // [esp-18h] [ebp-24h]
  int nEvtY; // [esp-14h] [ebp-20h]

  result = sub_5B6DC0(this, ArgList, ArgList, fArg3, nArg4, nArg5);  // ZGM 事件总分发（17 弹簧双人 / 8 落地 / 14 骑乘）
  if ( ArgList == 16 )  // 若 ArgList == 16
  {
    pEvtObj = *(int **)(LODWORD(fArg3) + 4);
    nEvtY = pEvtObj[1];  // nEvtY = 取 pEvtObj[1]
    nEvtX = *pEvtObj;
    (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    pObjCast = sub_45EBE0(nEvtX, nEvtY);  // pObjCast = 调 sub_45EBE0 返回值
    pMonsterCast = __RTDynamicCast(pObjCast, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // pMonsterCast = 调 __RTDynamicCast
    *(this + 2164) = pMonsterCast;  // this+8656〔uPair8656(推断)〕
    if ( pMonsterCast != 0 )  // 若 pMonsterCast 非 0
      sub_5B6000(this);  // 调 起手并由 vt+472(0
    return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7170 sub_5B7170 —— ZGM 行为字节拍（接低血召唤门）
// —— 与 ·sub_5B41C0 同构（差异：行为字 4 无目标时改写 13、无血线架招尾段，统一转 ·sub_5B6C00 召唤门）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B7170(uint32_t *this)  // 实现：ZGM 行为字节拍（接低血召唤门）
{
  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        goto LABEL_6;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      sub_5B6C00(this);  // 低血召唤门（setState 16）
      break;  // 跳出循环/分支
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      goto LABEL_6;
    default:  // 默认分支
LABEL_6:  // 标签 LABEL_6（跳转合流点）
      sub_5B6C00(this);  // 低血召唤门（setState 16）
      break;  // 跳出循环/分支
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B71F0 sub_5B71F0 —— 同源确认+销毁联动（双段串联）
// —— 前段与 ·sub_5B6CF0 同构（标记 529 + vt+376 同族确认转 ·sub_5B46A0）；
// 后段与 ·sub_5B6D70 同构（载具 8608 放生），尾调 ·sub_4D9170(nArg3)。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B71F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3)  // 实现：同源确认+销毁联动（双段串联）
{
  int nRoomId; // ebx
  bool bSameRoom; // zf
  int nArg22; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 529) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 724))(pDwArg1) == 0 )  // 调虚槽 +724：读 +6552 霸体字节
  {
    nArg22 = nArg2;
    nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 376))(nArg3);  // 调虚槽 +376：坐标同步包（type 37）
    bSameRoom = nRoomId == (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);  // 调虚槽 +376：坐标同步包（type 37）
    nArg2 = nArg22;
    if ( bSameRoom )
      sub_5B46A0(nArg3);  // 映射对象族判定（vt+340 ∈ 250..253）
  }
  if ( nArg3 == pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  if ( (int *)nArg3 == pDwArg1 && pDwArg1[2152] != 0 )  // 复合条件判定（与/或）
    sub_5B69C0(pDwArg1, nArg2);  // 骑乘载具放生（8608 槽清空）
  return sub_4D9170(nArg3);  // 返回 调 sub_4D9170 返回值
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7280 sub_5B7280 —— ZGM 落地事件变体（帧写 + 3/5/8 事件）
// 大状态 8 时先把 this+6216 资源块的 +16 句柄经 vt+208 写帧；转发 ·sub_5B6DC0 后按事件：
// 5=非困难(1943 槽!=3) 收招 vt+196(0) + ·sub_5B4A50(3,2)、3=8656 槽非空且 1908 槽==2 时 1%、==0 时 5% 概率 ·sub_5B4A50(1,1) 并递减、
// 8=段 5 时先 ·sub_4926A0 复位 6216+16 句柄再 vt+204(this,100,…) 写段。
// ------------------------------------------------------------
int /*userpurge*/ sub_5B7280@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：ZGM 落地事件变体（帧写 + 3/5/8 事件）
{
  int result; // eax
  int nRand; // eax
  int nRandMod; // et2

  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 16));  // 调虚槽 +208：定时器移除
  result = sub_5B6DC0(pDwArg1, nArg2, ArgList, fArg4, nArg5, nArg6);  // ZGM 事件总分发（17 弹簧双人 / 8 落地 / 14 骑乘）
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( pDwArg1[1943] != 3 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, 0);  // 调虚槽 +196：动画对象设置（换域 + 播放）
        return sub_5B4A50(3, 2, -1, -1);  // 返回 调 sub_5B4A50 返回值
      }
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = pDwArg1[2164];  // result = 取 pDwArg1[2164]
      if ( result > 0 )  // 若 result > 0
      {
        if ( pDwArg1[1908] == 2 && rand() % 100 < 1  // 复合条件判定（与/或）
          || (result = pDwArg1[1908]) == 0 && (nRand = rand(), nRandMod = nRand % 100, result = nRand / 100, nRandMod < 5) )
        {
          sub_5B4A50(1, 1, -1, -1);
          result = pDwArg1[2164] - 1;
          pDwArg1[2164] = result;
        }
      }
      break;  // 跳出循环/分支
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 5 )  // 若 result == 5
      {
        sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));  // 帧游标复位（+44 帧数组；递归子链 +204）
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(  // 调虚槽 +204：定时器插入
                 pDwArg1,
                 100,
                 *(uint32_t *)(pDwArg1[1554] + 16),
                 0,
                 0,
                 0,
                 0);
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  return result;
}



// 子类扩展字段复位（this+8604..8660, 20L）
// ------------------------------------------------------------
// 0x5B73B0 sub_5B73B0 —— ZGM 扩展复位（8604..8660）
// —— 与 ·sub_5B4700 同族（差异：清 8604/8605/8606/8607 四标记，8640/8656/8660 写 -1 哨兵，供事件 16/17 配对槽就绪）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B73B0(int this)  // 实现：ZGM 扩展复位（8604..8660）
{
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
  *(uint8_t *)(this + 8606) = 0;  // this+8606〔bAI8606〕
  *(uint8_t *)(this + 8607) = 0;  // this+8607〔bAI8607〕
  *(uint32_t *)(this + 8640) = -1;  // this+8640〔uCastSlot8640(推断)〕
  *(uint32_t *)(this + 8644) = 0;  // this+8644〔uPhase8644(推断)〕
  *(uint32_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  *(uint32_t *)(this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
  *(uint32_t *)(this + 8656) = -1;  // this+8656〔uPair8656(推断)〕
  *(uint32_t *)(this + 8660) = -1;  // this+8660〔uEvt8660(推断)〕
  return 0;
}



// 【vmt200 命中处理器覆写】（39L；虚表 0x6E7334..0x6EA274 九张 +512 槽共享 —— ZGM/炮车族通用受击处理）
// ------------------------------------------------------------
// 0x5B7400 sub_5B7400 —— vmt200 命中覆写：随机护盾 proc + 8668 计数到期回卷
// 基线 ·sub_4DA3B0 命中包分发；本地门且 this+7636==2 时按 this+8664 概率触发嵌入对象(this+8600)
// 的 vt+0(this+8600, this, this+7256)；this+8668 计数递减至 0 时把动画块 +466 帧推进 -100000 回卷
// 并清 this+8621/8622【推断：护盾/受击段到期复位】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7400(void *this, int nArg2, int nArg3, int nArg4)  // 实现：vmt200 命中覆写：随机护盾 proc + 8668 计数到期回卷
{
  int nHitResult; // edi
  int pThis_877; // eax
  int nTimerA; // eax
  unsigned int pThis_2A0; // edi
  int nFrameVal; // eax
  int edxTmp; // edx
  int nResult; // [esp+18h] [ebp+10h]

  nHitResult = sub_4DA3B0(nArg2, nArg3, nArg4);  // 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
  nResult = nHitResult;
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *((uint32_t *)this + 1909) == 2  // this+7636〔nPosWinY〕
    && rand() % 100 < *((uint32_t *)this + 2166) )  // this+8664〔uAI8664(推断)〕
  {
    (**((void (/*thiscall*/ ***)(int, void *, uint32_t))this + 2150))((int)this + 8600, this, *((uint32_t *)this + 1814));  // this+7256〔pAuraObject〕
  }
  pThis_877 = *((uint32_t *)this + 2167);  // this+8668〔nCool8668(推断)〕
  if ( pThis_877 <= 0 )  // 若 pThis_877 <= 0
    return nHitResult;
  nTimerA = pThis_877 - 1;
  *((uint32_t *)this + 2167) = nTimerA;  // this+8668〔计数递减至〕
  if ( nTimerA > 0 )  // 若 nTimerA > 0
    return nHitResult;
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;  // 调虚槽 +672：自身 HP
  nFrameVal = sub_41A5E0(pThis_2A0);  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pThis_2A0, edxTmp, nFrameVal - 100000);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  *((uint8_t *)this + 8621) = 0;
  *((uint8_t *)this + 8622) = 0;  // this+8622〔bLoopLatch8622〕
  return nResult;
}



// AI 字段访问（this+8621/8622）
// ------------------------------------------------------------
// 0x5B74D0 sub_5B74D0 —— 事件包处理+嵌入对象联动
// ·sub_4DC630 取事件包；结果 14 时调嵌入对象(this+8600) 的 vt+4(this+8600, this)【推断：事件 14 触达该子对象】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B74D0(uint32_t *this)  // 实现：事件包处理+嵌入对象联动
{
  int result; // eax
  int nResult; // edi

  result = sub_4DC630();  // 关卡/交互事件包处理（关联对象 this+7260 校验）
  nResult = result;
  if ( result != -1 )
  {
    if ( result == 14 )  // 若 result == 14
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*(this + 2150) + 4))(this + 2150, this);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 699000/…
    return nResult;
  }
  return result;
}



// 盾闪：SHIELD_FLASH 播报（55L）
// ------------------------------------------------------------
// 0x5B7500 sub_5B7500 —— 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
// 动画控制块 +466 整数按 pszArg2 非 0 加 100、为 0 减 100（+102/+158 两浮点同步 ±9.0）后 vt+676 写帧；
// 开侧额外 vt+212 播报 SHIELD_FLASH【推断：盾牌开/收的表现与语音】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7500(void *this, char pszArg2)  // 实现：盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
{
  unsigned int pThis_2A0; // edi
  int nFpVal; // eax
  int edxTmp; // edx
  unsigned int pThis_2A02; // edi
  int edxTmp2; // edx
  unsigned int pThis_2A03; // edi
  int edxTmp3; // edx
  unsigned int pThis_2A04; // edi
  int edxTmp4; // edx
  unsigned int pThis_2A05; // edi
  int edxTmp5; // edx
  int fFpVal2; // [esp+10h] [ebp+8h]
  int fFpVal3; // [esp+10h] [ebp+8h]
  int fFpVal4; // [esp+10h] [ebp+8h]
  int fFpVal5; // [esp+10h] [ebp+8h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;  // 调虚槽 +672：自身 HP
  nFpVal = sub_41A5E0(pThis_2A0);  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    sub_41A590(pThis_2A0, edxTmp, nFpVal + 100);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;  // 调虚槽 +672：自身 HP
    *(float *)&fFpVal2 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 9.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A02, edxTmp2, fFpVal2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A03 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;  // 调虚槽 +672：自身 HP
    *(float *)&fFpVal3 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) + 9.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A03, edxTmp3, fFpVal3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "SHIELD_FLASH",  // 标签 SHIELD_FLASH
             -1,
             0,
             0);
  }
  else  // 否则分支
  {
    sub_41A590(pThis_2A0, edxTmp, nFpVal - 100);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A04 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;  // 调虚槽 +672：自身 HP
    *(float *)&fFpVal4 = COERCE_FLOAT(sub_41A5E0(pThis_2A04)) - 9.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A04, edxTmp4, fFpVal4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A05 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;  // 调虚槽 +672：自身 HP
    *(float *)&fFpVal5 = COERCE_FLOAT(sub_41A5E0(pThis_2A05)) - 9.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A05, edxTmp5, fFpVal5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
  }
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B7660 sub_5B7660 —— 信徒(CNZealot)绑定确认回落
// 事件参数对 (this+8656, this+8660) 经 vt+80+·sub_45EBE0 解对象并 RTTI cast 为 CNZealot；命中且其 vt+724==0 时
// 写其 8668=5、+466 帧 +100000 回卷、清 8621/8622、·sub_698F90 停其 8608 钟；末两槽归 -1【推断：配对槽消费完毕】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7660(uint32_t *this)  // 实现：信徒(CNZealot)绑定确认回落
{
  int pObjRaw; // eax
  int pObj; // esi
  int pVt; // edx
  unsigned int pAniCtrl466; // ebx
  int nFpVal; // eax
  int edxTmp; // edx
  int uPair8656; // [esp-18h] [ebp-20h]  | +0x21D0 → 事件 16/17 配对槽〔5B73B0 写 -1 哨兵；5B7660 与 uEvt8660 成对经 sub_45EB（CNEvangelistOfDark；va=005B7660）
  int uEvt8660; // [esp-14h] [ebp-1Ch]  | +0x21D4 → 事件配对槽〔5B73B0 写 -1；与 uPair8656 配对消费后两槽归 -1〕（CNEvangelistOfDark；va=005B7660）

  uEvt8660 = *(this + 2165);  // this+8660〔uEvt8660(推断)〕
  uPair8656 = *(this + 2164);  // this+8656〔uPair8656(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  pObjRaw = sub_45EBE0(uPair8656, uEvt8660);  // pObjRaw = 调 sub_45EBE0 返回值
  pObj = __RTDynamicCast(pObjRaw, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);  // pObj = 调 __RTDynamicCast
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )  // 调虚槽 +724：读 +6552 霸体字节
  {
    pVt = *(uint32_t *)pObj;
    *(uint32_t *)(pObj + 8668) = 5;  // pObj+8668〔nCool8668(推断)〕
    pAniCtrl466 = (*(int (/*thiscall*/ **)(int, uint32_t))(pVt + 672))(pObj, 0) + 466;  // 调虚槽 +672：自身 HP
    nFpVal = sub_41A5E0(pAniCtrl466);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pAniCtrl466, edxTmp, nFpVal + 100000);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 676))(pObj, 0);  // 调虚槽 +676
    *(uint8_t *)(pObj + 8621) = 0;
    *(uint8_t *)(pObj + 8622) = 0;  // pObj+8622〔bLoopLatch8622(推断)〕
    sub_698F90(pObj + 8608, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  *(this + 2164) = -1;  // this+8656〔uPair8656(推断)〕
  *(this + 2165) = -1;  // this+8660〔uEvt8660(推断)〕
  return -1;
}



// 主状态门（this+200/8604）
// ------------------------------------------------------------
// 0x5B7720 sub_5B7720 —— 大状态三段门（8 攻击 / 15 施放 / 14 架招）
// 基线 ·sub_4E1780；8 且子类段 7028∈{1,2}：vt+200 对象 +148==1 且 8604 未置时经本地门调 vt+1316 并置 8604=1；
// 15 且 +170（播完标记）非 0 时 vt+472(0,0,1,1) 收尾；14 时调 vt+1312（收手触发）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5B7720(int this)  // 实现：大状态三段门（8 攻击 / 15 施放 / 14 架招）
{
  int pThis_C8; // eax

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8  // 调虚槽 +840：大状态 getter（this+6556）
    && (sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
    if ( *(uint32_t *)(pThis_C8 + 148) == 1 )  // pThis_C8+148〔fAdd148(推断)〕
    {
      LOBYTE(pThis_C8) = *(uint8_t *)(this + 8604);  // this+8604〔bAI8604(推断)〕
      if ( (uint8_t)pThis_C8 == 0 )
      {
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)pThis_C8 != 0 )
          LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);  // 调虚槽 +1316：CNGhoul 技能槽 vmt524（4926A0 目标链）
        *(uint8_t *)(this + 8604) = 1;  // this+8604〔bAI8604(推断)〕
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 15  // 调虚槽 +840：大状态 getter（this+6556）
         && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
  {
    LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
  }
  else  // 否则分支
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( pThis_C8 == 14 )  // 若 pThis_C8 == 14
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
  }
  return pThis_C8;
}



// 时钟门 AI（sub_699000, 58L）
// ------------------------------------------------------------
// 0x5B77F0 sub_5B77F0 —— 行为字节拍（高概率化变体）
// —— 与 ·sub_5B41C0 同构（差异：4→有目标 10% 写 5、5→有目标 1% 写 4、无目标写 13；25 型以 this+7640 时间戳差 >5000ms 写 13；无血线架招尾段）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B77F0(int *this)  // 实现：行为字节拍（高概率化变体）
{
  int result; // eax
  int nRand2; // eax
  int nRandMod; // et2
  int nRand; // eax
  int nRandMod2; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_12;
      nRand = rand();  // nRand = 调 rand
      nRandMod2 = nRand % 100;
      result = nRand / 100;
      if ( nRandMod2 < 10 )  // 若 nRandMod2 < 10
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_12;
      nRand2 = rand();  // nRand2 = 调 rand
      nRandMod = nRand2 % 100;
      result = nRand2 / 100;
      if ( nRandMod < 1 )  // 若 nRandMod < 1
        goto LABEL_4;
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 25:  // case 25 = ENUM_CMDPACKET_SELL_ITEM
      result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 5000 )  // 若 result > 5000
LABEL_12:  // 标签 LABEL_12（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
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
int /*thiscall*/ sub_5B7900(uint32_t *this, int nArg2)  // 实现：等待窗门（25 态 5000ms 内不推进）
{
  int result; // eax

  if ( *(this + 1787) != 25 )  // this+7148〔nBigState〕
    return sub_4D9040(nArg2);  // 返回 调 sub_4D9040 返回值
  result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
  if ( result >= 5000 )  // 若 result >= 5000
    return sub_4D9040(nArg2);  // 返回 调 sub_4D9040 返回值
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7940 sub_5B7940 —— 目标落点继承（vt+1144 + 帧标记清 0）
// 取 nArg2 坐标链 vt+124→vt+120 后经 vt+1144 写入自身目标位置；再把 vt+1040 返回结构的 +8 字节清 0
// 【推断：吸附/跟随目标点并复位帧控制标记】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7940(int *this, int nArg2)  // 实现：目标落点继承（vt+1144 + 帧标记清 0）
{
  int pVt; // ebx
  int nZ; // eax
  int nX; // eax
  int result; // eax

  pVt = *this;
  nZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nZ);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(int *, int))(pVt + 1144))(this, nX);  // 调虚槽 +1144：IRDCharacter__vmt478 默认虚槽桩（10 行 return）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 1040))(this);  // 调虚槽 +1040
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
int /*thiscall*/ sub_5B7980(uint32_t *this)  // 实现：投刀发射（Dagger.ptl 弹道 + THROW_STONE 播报）
{
  int pThis_6DD; // eax
  int pVt; // edi
  int nFaceRet; // eax

  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
  pVt = *this;
  nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(  // 调虚槽 +588
         this,
         "Particle/Dagger.ptl",  // 粒子 .ptl Particle/Dagger.ptl
         0,
         40,
         0,
         pThis_6DD != 1 ? 20 : 50,
         4,
         0,
         0,
         0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(pVt + 580))(this, *(this + 2168), 0, nFaceRet);  // this+8672〔uAI8672(推断)〕
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "THROW_STONE",  // 标签 THROW_STONE
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
int /*usercall*/ sub_5B79F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：投掷物随机散射（2-3 发，资源 ID 250/252）
{
  int result; // eax
  int nRand; // edi
  int nRand4; // eax
  int pVt; // edi
  int nFired; // eax
  int nZ; // eax
  int nY; // ebx
  int nRand5; // eax
  int nX; // ebx
  int nRand6; // eax
  uint32_t aResIds[2]; // [esp+4h] [ebp-18h]
  uint16_t aShotParams[3]; // [esp+Ch] [ebp-10h] BYREF
  bool nRand2; // [esp+12h] [ebp-Ah]
  char nRand3; // [esp+13h] [ebp-9h]
  uint32_t *pAniCtrl; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nRand = rand() % 2 + 2;  // nRand = 调 rand
    result = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 672))(pDwArg1, 3);  // 调虚槽 +672：自身 HP
    aResIds[0] = 250;
    aResIds[1] = 252;
    if ( nRand > 0 )  // 若 nRand > 0
    {
      for ( i = nRand; i != 0; --i )  // 循环：i 从 nRand 递减到 0
      {
        aShotParams[0] = rand() % 200 + 100;  // aShotParams[0] = 调 rand
        aShotParams[1] = rand() % 100 + 50;  // aShotParams[1] = 调 rand
        nRand2 = rand() % 2 == 0;  // nRand2 = 调 rand
        nRand3 = 3 - (rand() % 2 != 0);  // rand()%2 取模随机
        nRand4 = rand();  // nRand4 = 调 rand
        pVt = *pDwArg1;
        aShotParams[2] = nRand4 % 60 + 40;
        pAniCtrl = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int, int))(pVt + 672))(pDwArg1, 3, nArg2, nArg3);  // 调虚槽 +672：自身 HP
        nFired = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
               pDwArg1,
               1,
               aShotParams,
               8,
               0xFFFF,
               0,
               0,
               0,
               0);
        nZ = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 128))(pDwArg1, nFired);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        nY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ + 20);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nRand5 = rand();  // nRand5 = 调 rand
        nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY + nRand5 % 20 - 10);  // 调虚槽 +120：动画对象
        nRand6 = rand();  // nRand6 = 调 rand
        nArg3 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 376))(pDwArg1, *pAniCtrl, nX + nRand6 % 40 - 20);  // 调虚槽 +376：坐标同步包（type 37）
        nArg2 = aResIds[rand() % 2];  // nArg2 = 取 aResIds[rand() % 2]
        result = (*(int (/*thiscall*/ **)(int *))(pVt + 592))(pDwArg1);
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
int /*thiscall*/ sub_5B7CC0(int this)  // 实现：架招自启（5/300 概率 setState 14）
{
  int result; // eax
  int nRand; // eax
  int nRandMod; // et2

  sub_5B77F0((int *)this);  // 行为字节拍（高概率化变体）
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 0 )  // 若 result 为 0
    {
      result = *(uint8_t *)(this + 8607);  // this+8607〔bAI8607〕
      if ( (uint8_t)result == 0 )
      {
        result = *(uint32_t *)(this + 8668);  // result = 读 this+8668
        if ( result <= 0 )  // 若 result <= 0
        {
          result = *(uint32_t *)(this + 7632);  // result = 读 this+7632
          if ( result == 0 )  // 若 result 为 0
          {
            nRand = rand();  // nRand = 调 rand
            nRandMod = nRand % 300;
            result = nRand / 300;
            if ( nRandMod < 5 )  // 若 nRandMod < 5
              return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*thiscall*/ sub_5B7CD0(int this, int nArg2, int nArg3)  // 实现：分身参数面清空（形态槽置 7584=1）
{
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7584) = 1;  // this+7584〔uForm7584〕
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7D60 sub_5B7D60 —— 分身参数面清空（形态槽置 7588=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7588=1；nArg3==2 且 nArg2==0 时
// 偏移槽 this+7596=-50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7D60(int this, int nArg2, int nArg3)  // 实现：分身参数面清空（形态槽置 7588=1）
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7588) = 1;  // this+7588〔uForm7588〕
  if ( nArg3 == 2 && nArg2 == 0 )  // 若 nArg3 == 2 与/或 nArg2 == 0
    *(uint32_t *)(this + 7596) = -50;  // this+7596〔nOffset7596(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7E00 sub_5B7E00 —— 分身参数面清空（形态槽置 7564=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7564=1；nArg3==2 时取 nArg2，
// 归一为 0 则偏移槽 this+7596=+50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7E00(int this, int nArg2, int nArg3)  // 实现：分身参数面清空（形态槽置 7564=1）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7564) = 1;  // this+7564〔uForm7564(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = 50;  // this+7596〔nOffset7596(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7EB0 sub_5B7EB0 —— 分身出厂（this+8664=30 / this+8640=vt+384 出场参数）
// 仅自身消息(pDwArg2==this)有效：写 this+8664=30（存续/延迟帧）、经 vt+384(0) 取出场参数面
// 存 this+8640。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7EB0(int *this, int *pDwArg2)  // 实现：分身出厂（this+8664=30 / this+8640=vt+384 出场参数）
{
  int result; // eax
  int pVt; // eax

  result = (int)pDwArg2;
  if ( pDwArg2 == this )  // 若 pDwArg2 == this
  {
    pVt = *this;
    *(this + 2166) = 30;  // this+8664〔uAI8664(推断)〕
    result = (*(int (/*stdcall*/ **)(uint32_t))(pVt + 384))(0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    *(this + 2160) = result;  // this+8640〔uCastSlot8640(推断)〕
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
int /*thiscall*/ sub_5B7EE0(int *this, int nArg2, int nArg3, int nArg4)  // 实现：伤害计数射弹（5% 概率发 30073）后尾调反击判定
{
  int pVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nZ2; // eax
  int nX; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调虚槽 +840：大状态 getter（this+6556）
    && sub_41A5E0((unsigned int)(this + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && rand() % 100 < 5 )  // 5% 概率触发（rand()%100 < 5）
  {
    pVt = *this;
    nZ = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
           nArg2,
           30073,
           3,
           0,
           4,
           100,
           1,
           0,
           0);
    nY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nZ);  // 调虚槽 +120：动画对象
    nZ2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, nY);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nZ2);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 584))(this, nX);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7F90 sub_5B7F90 —— 分身参数面清空（形态槽置 7534=1）
// 与 ·sub_5B7CD0 同构（差异：末置形态槽 this+7534=1；nArg3==2 时取 nArg2，
// 归一为 0 则偏移槽 this+7596=+50）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7F90(int this, int nArg2, int nArg3)  // 实现：分身参数面清空（形态槽置 7534=1）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint8_t *)(this + 7534) = 1;  // this+7534〔bCfgBlock14(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(uint32_t *)(this + 7596) = 50;  // this+7596〔nOffset7596(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8040 sub_5B8040 —— 冰盾光环挂载（Block==null 时 new ChillingAura）
// 先跑 ·sub_5B7D60 清参数面；Block 为空时经 vt+700 取资源族、·sub_53F6A0 清挂点，
// new 0x8C 后由 ·sub_64B0F0 载 Monster/Soceress/Animation_Keraha/ChillingAura（动画模板 %s.ani），
// vt+56 挂到(自身,自身)并播 SHIELD_ICE；vt+216 写入音效槽 163 后播 WINDSHIELD_LOOP。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8040(void *this, int nArg2, void *Block)  // 实现：冰盾光环挂载（Block==null 时 new ChillingAura）
{
  int result; // eax
  int pObj; // eax

  result = sub_5B7D60((int)this, nArg2, (int)Block);  // 分身参数面清空（形态槽置 7588=1）
  if ( Block == nullptr )  // 若 Block 为空
  {
    (*(void (**)(void))(*(uint32_t *)this + 700))();  // 调虚槽 +700：读 +6296 槽
    sub_53F6A0(this);  // 调 收尾路径
    if ( operator new(0x8Cu) != nullptr )  // new(140 字节) 分配对象
      pObj = sub_64B0F0(0, 0x40000000, 7, "Monster/Soceress/Animation_Keraha/ChillingAura");  // 动画装载模板 %s.ani/%sDamage.ani（5910D0/42FCB0/431860/493400）
    else  // 否则分支
      pObj = 0;
    (*(void (/*thiscall*/ **)(int, void *, void *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pObj,
      this,
      this,
      1,
      0,
      0,
      -1);
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
      this,
      "SHIELD_ICE",  // 标签 SHIELD_ICE
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);  // 调虚槽 +216：音效 TAG 查询
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "WINDSHIELD_LOOP",  // 标签 WINDSHIELD_LOOP
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
int /*thiscall*/ sub_5B8120(void *this, void *pArg2)  // 实现：冰盾变体收尾（自身消息时写音效槽 163）
{
  int result; // eax

  result = sub_4D9170(pArg2);  // result = 调 sub_4D9170 返回值
  if ( this == pArg2 )  // 若 this == pArg2
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);  // 调虚槽 +216：音效 TAG 查询
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
int /*thiscall*/ sub_5B8150(uint32_t *this)  // 实现：投刀三连散射（Dagger.ptl 三角度 0/45/320）
{
  int pVt; // eax
  int i; // esi
  int pVt2; // eax
  int fld_e2168; // ecx
  uint32_t aAngles[3]; // [esp+Ch] [ebp-7Ch]
  int pThis_6DD; // [esp+18h] [ebp-70h]
  bool nRand; // [esp+1Fh] [ebp-69h]
  uint32_t aPtlParams[26]; // [esp+20h] [ebp-68h] BYREF

  aPtlParams[25] = dword_796E50;
  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) != 1 ? 20 : 50;  // crypt4byte 解密校验（·0x41A590 逆运算）
  pVt = *this;
  aAngles[0] = 0;
  aAngles[1] = 45;
  aAngles[2] = 320;
  qmemcpy(
    aPtlParams,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(pVt + 588))(this, "Particle/Dagger.ptl"),  // 粒子 .ptl Particle/Dagger.ptl
    0x62u);
  nRand = rand() % 100 < 30;  // nRand = 调 rand
  for ( i = 0; i < 3; ++i )  // 循环：i 从 0 递增到 3
  {
    pVt2 = *this;
    fld_e2168 = *(this + 2168);  // this+8672〔uAI8672(推断)〕
    aPtlParams[18] = aAngles[i];  // aPtlParams[18] = 取 aAngles[i]
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(pVt2 + 580))(
      this,
      fld_e2168,
      0,
      aPtlParams,
      0,
      40,
      0,
      pThis_6DD,
      4,
      0,
      0,
      0);
    if ( !nRand )
      break;  // 跳出循环/分支
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "THROW_STONE",  // 标签 THROW_STONE
           -1,
           0,
           0);
}



// 【vmt200 命中处理器覆写】（44L；虚表 0x6E97F4 +512 槽 —— 信徒族受击处理）
// ------------------------------------------------------------
// 0x5B8240 sub_5B8240 —— vmt200 命中覆写：护盾 proc 弹（10% 发 603）后交 ·sub_5B7400
// 门=vt+308 有目标、this+1908==0、计数 this+8636<6、rand%100<10；命中时以 vt+672(0) 取
// 挂点、vt+152(2,&aShotParams=4) 造参数面（1 段/4 朝向）经 vt+120/124/376 定位，vt+592 发 603
// 并 ++this+8636；末尾无条件交 ·sub_5B7400 护盾 proc 覆写。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8240(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：vmt200 命中覆写：护盾 proc 弹（10% 发 603）后交 ·sub_5B7400
{
  int pVt; // edi
  int pVt2; // edx
  uint32_t *pAniCtrl0; // ebx
  int nFaceRet; // eax
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  char aShotParams; // [esp+7h] [ebp-1h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + 1908) == 0  // this+7632〔uWindow7632(推断)〕
    && (int)*(this + 2159) < 6  // this+8636〔pDollTarget(推断)〕
    && rand() % 100 < 10 )  // 10% 概率触发（rand()%100 < 10）
  {
    pVt = *this;
    pVt2 = *this;
    aShotParams = 4;
    pAniCtrl0 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(pVt2 + 672))(this, 0);  // 调虚槽 +672：自身 HP
    nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
           this,
           2,
           &aShotParams,
           1,
           0xFFFF,
           0,
           0,
           0,
           0);
    nZ = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 124))(this, 0, nFaceRet);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nZ);  // 调虚槽 +120：动画对象
    nX = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 376))(this, *pAniCtrl0, nY);  // 调虚槽 +376：坐标同步包（type 37）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt + 592))(this, 603, nX);
    ++*(this + 2159);  // this+8636〔pDollTarget(推断)〕
  }
  return sub_5B7400(this, nArg2, nArg3, nArg4);  // vmt200 命中覆写：随机护盾 proc + 8668 计数到期回卷
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8310 sub_5B8310 —— 伤害计数射弹（30% 概率发 30074）后尾调反击判定
// 与 ·sub_5B7EE0 同构（差异：概率 30%；载荷 30074、10 段/4 朝向/100 距离）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8310(int *this, int nArg2, int nArg3, int nArg4)  // 实现：伤害计数射弹（30% 概率发 30074）后尾调反击判定
{
  int pVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nZ2; // eax
  int nX; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调虚槽 +840：大状态 getter（this+6556）
    && sub_41A5E0((unsigned int)(this + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && rand() % 100 < 30 )  // 30% 概率触发（rand()%100 < 30）
  {
    pVt = *this;
    nZ = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
           nArg2,
           30074,
           10,
           0,
           4,
           100,
           1,
           0,
           0);
    nY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nZ);  // 调虚槽 +120：动画对象
    nZ2 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, nY);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, nZ2);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 584))(this, nX);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B83C0 sub_5B83C0 —— 速率双轴衰减（控制柄 +830/+858 各 -0.5）后 vt+676 提交
// 仅 nArg3==0 生效：vt+672(0) 取控制柄，经 ·sub_41A5E0 读浮点、·sub_41A590 写回，
// 对 +830 与 +858 两槽各减 0.5【推断：移动/攻速衰减】，vt+676(0) 提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B83C0(void *this, int nArg2, int nArg3)  // 实现：速率双轴衰减（控制柄 +830/+858 各 -0.5）后 vt+676 提交
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int edxTmp; // edx
  unsigned int pThis_2A02; // edi
  int edxTmp2; // edx
  int fVal830; // [esp+10h] [ebp+Ch]
  int fVal858; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.5;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A0, edxTmp, fVal830);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&fVal858 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) - 0.5;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pThis_2A02, edxTmp2, fVal858);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 调虚槽 +676
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
void /*thiscall*/ sub_5B8450(uint32_t *this)  // 实现：修复效果请求（目标坐标 + 42004 效果包）
{
  int pHostObj; // ecx
  int pHostObj_; // ecx
  int nTgtX; // eax
  int pHostObj_2; // ecx
  int nTgtY; // eax
  int pHostObj_3; // edi
  int nHalfW; // ebx
  int nTgtZmid; // ebx
  int pHostObj_4; // eax
  int fld_e16; // eax
  int nHitA; // [esp-10h] [ebp-34h]
  int nHitB; // [esp-Ch] [ebp-30h]
  float fTgtX; // [esp+4h] [ebp-20h] BYREF
  float fTgtY; // [esp+8h] [ebp-1Ch]
  float fTgtZ; // [esp+Ch] [ebp-18h]
  int nF3Pad0; // [esp+10h] [ebp-14h]
  int nF3Pad1; // [esp+14h] [ebp-10h]
  int nF3Pad2; // [esp+18h] [ebp-Ch]
  int nCoordTmp; // [esp+1Ch] [ebp-8h]
  int nHitPack; // [esp+20h] [ebp-4h] BYREF

  pHostObj = *(this + 1);  // this+4〔宿主对象〕
  if ( pHostObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 308))(pHostObj) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    pHostObj_ = *(this + 1);  // this+4〔宿主对象〕
    fTgtX = 0.0;
    fTgtY = 0.0;
    fTgtZ = 0.0;
    nF3Pad0 = 0;
    nF3Pad1 = 0;
    nF3Pad2 = 0;
    nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 120))(pHostObj_);  // 调虚槽 +120：动画对象
    pHostObj_2 = *(this + 1);  // this+4〔宿主对象〕
    nCoordTmp = nTgtX;
    fTgtX = (float)nTgtX;
    nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_2 + 124))(pHostObj_2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    pHostObj_3 = *(this + 1);  // this+4〔宿主对象〕
    nCoordTmp = nTgtY;
    fTgtY = (float)nTgtY;
    nHalfW = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_3 + 192))(pHostObj_3) / 2;  // 调虚槽 +192
    nTgtZmid = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_3 + 128))(pHostObj_3) + nHalfW;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    pHostObj_4 = *(this + 1);  // this+4〔宿主对象〕
    nCoordTmp = nTgtZmid;
    fTgtZ = (float)nTgtZmid;
    nHitPack = 0;
    nHitB = sub_605840(&nHitPack, pHostObj_4, &fTgtX, 0);  // 30 字节全局包
    nHitA = nHitPack;
    fld_e16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 152))(*(this + 1));  // 调虚槽 +152：效果通道 3
    sub_4E4A50(*(this + 9), 42004, *(this + 20), 0, 0, 0, fld_e16, 0, nHitA, nHitB);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    *(this + 18) = *(this + 21);  // this+72〔nSnapshot72(推断)〕等 2 字段
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8550 sub_5B8550 —— 大状态退出副作用（nArg2==25 时 this+8292=1000 并置位）
// 先调 ·sub_4DBC20（大状态退出副作用处理器，0x4DBA80 的还原对偶）；
// nArg2==25 时写 this+8292=1000（时长/桩数）并经 vt+1040 取桩位后 [8]=1 置位。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8550(int *this, int nArg2)  // 实现：大状态退出副作用（nArg2==25 时 this+8292=1000 并置位）
{
  int result; // eax
  int pVt; // eax

  result = sub_4DBC20(nArg2);  // 大状态退出副作用处理器（0x4DBA80 的还原对偶）
  if ( nArg2 == 25 )  // 若 nArg2 == 25
  {
    pVt = *this;
    *(this + 2073) = 1000;  // this+8292〔bModeFlag(推断)〕
    result = (*(int (/*thiscall*/ **)(int *))(pVt + 1040))(this);
    *(uint8_t *)(result + 8) = 1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8590 sub_5B8590 —— 散射门（vt+308 且有目标且 this+8605==1 时才散射）
// 读 vt+308 有目标与 this+8605 相位字节，二者齐备时转 ·sub_5B79F0 执行 2-3 发散射投掷。
// ------------------------------------------------------------
int /*usercall*/ sub_5B8590@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：散射门（vt+308 且有目标且 this+8605==1 时才散射）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 && *(uint8_t *)(pArg1 + 8605) == 1 )  // 复合条件判定（与/或）
    return sub_5B79F0((int *)pArg1, nArg2, nArg3);  // 投掷物随机散射（2-3 发，资源 ID 250/252）
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B85C0 sub_5B85C0 —— CNAppendageTimerFireDamage 构造（延烧附着物）
// 基类 ·sub_4B1030 后写 vftable，this+20=nArg4(伤害)、+21=+18=nArg3(间隔)、+11=nArg2(存续 ms)、
// +22=0（宿主/触发器槽），·sub_5F66A0(1) 登记。调用点(0x5B9280)传 10000/999/20。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B85C0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：CNAppendageTimerFireDamage 构造（延烧附着物）
{
  int fld_e21; // edx

  sub_4B1030();  // IRDAppendage 基类构造
  *(this + 20) = nArg4;  // this+80〔nAuraStage(推断)〕
  *this = &CNAppendageTimerFireDamage::`vftable';  // 构造装配 vftable：CNAppendageTimerFireDamage
  *(this + 21) = nArg3;  // this+84〔pFxObjA(推断)〕
  sub_5F66A0(1);
  fld_e21 = *(this + 21);  // this+84〔pFxObjA(推断)〕
  *(this + 11) = nArg2;  // this+44〔nExpireMs(推断)〕
  *(this + 18) = fld_e21;  // this+72〔nSnapshot72(推断)〕
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8630 sub_5B8630 —— CNAppendageTimerFireDamage 析构（驱散宿主 + 基类回落）
// this+22 宿主槽非空时经其 vtable[0](宿主,1) 释放并清零；vftable 依次回落 IRDAppendage、
// IObject，·sub_5F6640 反登记，this 字节 12 清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8630(uint32_t *this)  // 实现：CNAppendageTimerFireDamage 析构（驱散宿主 + 基类回落）
{
  void (/*thiscall*/ ***fld_e22)(uint32_t, int); // ecx
  int result; // eax

  *this = &CNAppendageTimerFireDamage::`vftable';  // 构造装配 vftable：CNAppendageTimerFireDamage
  pMountVt = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 22);  // this+88〔pFxObjB(推断)〕
  if ( pMountVt != nullptr )  // 若 pMountVt 有效（非空）
    (**pMountVt)(pMountVt, 1);  // 调 pMountVt 的虚函数（vt+0）
  *(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // result = 调 sub_5F6640 返回值
  *(this + 2) = &nengine::IObject::`vftable';  // this+8〔nSkillRec8(推断)〕
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B86A0 sub_5B86A0 —— 删除式析构包装（pszArg2 bit0 置位则 free 本体）
// 转 ·sub_5B8630 析构后按 pszArg2&1 决定 j__free，标准编译器生成形态。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B86A0(uint32_t *Block, char pszArg2)  // 实现：删除式析构包装（pszArg2 bit0 置位则 free 本体）
{
  sub_5B8630(Block);  // CNAppendageTimerFireDamage 析构（驱散宿主 + 基类回落）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);
  return Block;
}



// AI 相位辅助（this+204/+208 硬直）
// ------------------------------------------------------------
// 0x5B86D0 sub_5B86D0 —— 三帧位偏移挂装/还原（-100/100/200）
// 资源表指针 this+1554 取 +16/+20/+24 三项：pszArg2 非 0 时先 ·sub_4926A0 帧游标复位，
// 再经 vt+204 以 -100/100/200 三偏移写入（多帧错位表现）；置 0 时经 vt+208 按原锚还原三帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B86D0(uint32_t *this, char pszArg2)  // 实现：三帧位偏移挂装/还原（-100/100/200）
{
  int fld_e1554; // eax

  fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    sub_4926A0(*(uint32_t *)(fld_e1554 + 16));  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 24));  // 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
      this,
      -100,
      *(uint32_t *)(*(this + 1554) + 16),  // this+6216〔pTbl6216(推断)〕
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 20),  // this+6216〔pTbl6216(推断)〕
      0,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
             this,
             200,
             *(uint32_t *)(*(this + 1554) + 24),  // this+6216〔pTbl6216(推断)〕
             0,
             0,
             0,
             0);
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(fld_e1554 + 16));  // 调虚槽 +208：定时器移除
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // 调虚槽 +208：定时器移除
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // 调虚槽 +208：定时器移除
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
int /*thiscall*/ sub_5B87C0(uint32_t *this)  // 实现：信徒·寻车解算（场景标记 529 + CNVehicle cast）
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
  result = (*(int (/*fastcall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nIdx = 0;
    pBestVehicle = 0;
    while ( 1 )  // 条件循环
    {
      pVecHdr = pThis[29];  // pVecHdr = 取 pThis[29]
      pVecBegin = *(uint32_t *)(pVecHdr + 8);
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(pVecHdr + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)nIdx >= nCnt )
        break;  // 跳出循环/分支
      pVecBegin3 = *(uint32_t *)(pVecHdr + 8);
      if ( pVecBegin3 != 0 && nIdx < (*(uint32_t *)(pVecHdr + 12) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
        pListObj = *(uint32_t *)(pVecBegin3 + 4 * nIdx);
      else  // 否则分支
        pListObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        pVecHdr2 = pThis[29];  // pVecHdr2 = 取 pThis[29]
        pVecBegin2 = *(uint32_t *)(pVecHdr2 + 8);
        if ( pVecBegin2 != 0 && nIdx < (*(uint32_t *)(pVecHdr2 + 12) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
          pListObj2 = *(uint32_t *)(pVecBegin2 + 4 * nIdx);
        else  // 否则分支
          pListObj2 = 0;
        pVehicle = __RTDynamicCast(pListObj2, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);  // pVehicle = 调 __RTDynamicCast
        pVehicle2 = pVehicle;
        if ( pVehicle != 0 )  // 若 pVehicle 非 0
        {
          nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 376))(pVehicle);  // 调虚槽 +376：坐标同步包（type 37）
          if ( nRoomId == (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis)  // 调虚槽 +376：坐标同步包（type 37）
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pVehicle2) != 0  // 调虚槽 +1244
            && (pBestVehicle == 0
             || (nDistNew = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle2 + 736))(pVehicle2)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pBestVehicle + 736))(pBestVehicle)) )  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
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
char /*thiscall*/ sub_5B88E0(int *this, char pszArg2)  // 实现：信徒指挥态进退（BELIEVER_COMMAND 起手/收尾）
{
  char result; // al
  int pVt; // eax
  unsigned int pCtrl74; // edi
  int edxTmp; // edx
  unsigned int pCtrl830; // edi
  int edxTmp2; // edx
  unsigned int pCtrl102; // edi
  int edxTmp3; // edx
  unsigned int pCtrl158; // edi
  int edxTmp4; // edx
  int pVt2; // edx
  unsigned int pCtrl74b; // edi
  int edxTmp5; // edx
  unsigned int pCtrl830b; // edi
  int edxTmp6; // edx
  unsigned int pCtrl102b; // edi
  int edxTmp7; // edx
  unsigned int pCtrl158b; // edi
  int edxTmp8; // edx
  int fVal74; // [esp+14h] [ebp+8h]
  int fVal830; // [esp+14h] [ebp+8h]
  int fVal102; // [esp+14h] [ebp+8h]
  int fVal158; // [esp+14h] [ebp+8h]
  int fVal74b; // [esp+14h] [ebp+8h]
  int fVal830b; // [esp+14h] [ebp+8h]
  int fVal102b; // [esp+14h] [ebp+8h]
  int fVal158b; // [esp+14h] [ebp+8h]

  result = pszArg2;
  if ( pszArg2 == 1 )  // 若 pszArg2 == 1
  {
    if ( *((uint8_t *)this + 8607) == 0 )  // this+8607〔bAI8607〕
    {
      pVt = *this;
      *((uint8_t *)this + 7559) = 1;
      *(this + 1899) = 100;  // this+7596〔nOffset7596(推断)〕
      pCtrl74 = (*(int (/*stdcall*/ **)(uint32_t))(pVt + 672))(0) + 74;  // 调虚槽 +672：自身 HP
      *(float *)&fVal74 = COERCE_FLOAT(sub_41A5E0(pCtrl74)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pCtrl74, edxTmp, fVal74);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      pCtrl830 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
      *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pCtrl830)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pCtrl830, edxTmp2, fVal830);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      pCtrl102 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;  // 调虚槽 +672：自身 HP
      *(float *)&fVal102 = COERCE_FLOAT(sub_41A5E0(pCtrl102)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pCtrl102, edxTmp3, fVal102);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      pCtrl158 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;  // 调虚槽 +672：自身 HP
      *(float *)&fVal158 = COERCE_FLOAT(sub_41A5E0(pCtrl158)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pCtrl158, edxTmp4, fVal158);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
      *((uint8_t *)this + 8607) = 1;  // this+8607〔bAI8607〕
      *((uint8_t *)this + 8621) = 0;
      *((uint8_t *)this + 8622) = 0;  // this+8622〔bLoopLatch8622〕
      sub_698F90((int)(this + 2152), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_5B86D0(this, 1);  // 三帧位偏移挂装/还原（-100/100/200）
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "BELIEVER_COMMAND",  // 标签 BELIEVER_COMMAND
               -1,
               0,
               0);
    }
  }
  else if ( pszArg2 == 0 && *((uint8_t *)this + 8607) == 1 )  // this+8607〔bAI8607〕
  {
    pVt2 = *this;
    *((uint8_t *)this + 7559) = 0;
    *(this + 1899) = 0;  // this+7596〔nOffset7596(推断)〕
    pCtrl74b = (*(int (/*thiscall*/ **)(int *, uint32_t))(pVt2 + 672))(this, 0) + 74;  // 调虚槽 +672：自身 HP
    *(float *)&fVal74b = COERCE_FLOAT(sub_41A5E0(pCtrl74b)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl74b, edxTmp5, fVal74b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pCtrl830b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830b = COERCE_FLOAT(sub_41A5E0(pCtrl830b)) - 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl830b, edxTmp6, fVal830b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pCtrl102b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;  // 调虚槽 +672：自身 HP
    *(float *)&fVal102b = COERCE_FLOAT(sub_41A5E0(pCtrl102b)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl102b, edxTmp7, fVal102b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pCtrl158b = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;  // 调虚槽 +672：自身 HP
    *(float *)&fVal158b = COERCE_FLOAT(sub_41A5E0(pCtrl158b)) + 0.30000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl158b, edxTmp8, fVal158b);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
    *((uint8_t *)this + 8607) = 0;  // this+8607〔bAI8607〕
    *((uint8_t *)this + 8621) = 0;
    *((uint8_t *)this + 8622) = 0;  // this+8622〔bLoopLatch8622〕
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // 调虚槽 +208：定时器移除
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // 调虚槽 +208：定时器移除
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // 调虚槽 +208：定时器移除
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8B80 sub_5B8B80 —— 信徒加载槽清位（this[1905]+96 字节置 0）
// 仅 uArg3==nullptr 时有效：把 this[1905] 资源对象 +96 偏移处字节清 0（加载/待机旗标）。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8B80(uint32_t *this, int nArg2, uint8_t *uArg3)  // 实现：信徒加载槽清位（this+96 字节置 0）
{
  uint8_t *result; // eax

  result = uArg3;
  if ( uArg3 == nullptr )  // 若 uArg3 为空
  {
    result = (uint8_t *)(*(this + 1905) + 96);  // this+7620〔pStatusPanel(推断)〕
    *result = 0;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8BA0 sub_5B8BA0 —— 分身收尾（nArg3==0 时 this+7620 资源 +96 置 1）
// 先跑 ·sub_5B7D60 清参数面；nArg3==0 时把 this+7620 资源对象 +96 偏移处字节置 1。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8BA0(void *this, int nArg2, int nArg3)  // 实现：分身收尾（nArg3==0 时 this+7620 资源 +96 置 1）
{
  uint8_t *result; // eax
  int pObjBase; // ecx

  result = (uint8_t *)sub_5B7D60((int)this, nArg2, nArg3);  // 分身参数面清空（形态槽置 7588=1）
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    result = (uint8_t *)(*(uint32_t *)(pObjBase + 7620) + 96);  // pObjBase+7620〔pStatusPanel(推断)〕
    *result = 1;
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B8BD0 sub_5B8BD0 —— 目标解算收尾（CNZealot cast 后强制进指挥态）
// 取 this[2164]/this[2165] 对象键经 ·sub_45EBE0 解算，__RTDynamicCast 为 CNZealot；
// 其 vt+724（姿态/忙碌查询）为 0 时调 ·sub_5B88E0(pZealot,1) 进指挥态；两键槽置 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8BD0(uint32_t *this)  // 实现：目标解算收尾（CNZealot cast 后强制进指挥态）
{
  int pObjRaw; // eax
  int *pZealot; // edi
  int fld_e2164; // [esp-18h] [ebp-20h]
  int fld_e2165; // [esp-14h] [ebp-1Ch]

  fld_e2165 = *(this + 2165);  // this+8660〔uEvt8660(推断)〕
  fld_e2164 = *(this + 2164);  // this+8656〔uPair8656(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  pObjRaw = sub_45EBE0(fld_e2164, fld_e2165);  // pObjRaw = 调 sub_45EBE0 返回值
  pZealot = (int *)__RTDynamicCast(pObjRaw, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
  if ( pZealot != nullptr && (*(uint8_t (/*thiscall*/ **)(int *))(*pZealot + 724))(pZealot) == 0 )  // 调虚槽 +724：读 +6552 霸体字节
    sub_5B88E0(pZealot, 1);  // 信徒指挥态进退（BELIEVER_COMMAND 起手/收尾）
  *(this + 2164) = -1;  // this+8656〔uPair8656(推断)〕
  *(this + 2165) = -1;  // this+8660〔uEvt8660(推断)〕
  return -1;
}



// 信徒语音装载：BELIEVER_DMG/DIE/FIND + KNIFE_HIT 刀命中播报（sub_4015C0）
// ------------------------------------------------------------
// 0x5B8C40 sub_5B8C40 —— 信徒初始化（语音组装载 + 技能参数）
// 写 this+6792/6800/6796/6804/6808（三资源表指针与两计数），经 ·sub_4015C0 依次装
// BELIEVER_DMG(12)/BELIEVER_DIE(12)/BELIEVER_FIND(13)/KNIFE_HIT(9) 语音；末写
// this+8664=10、+8668=0、+8636=0、+8672=30014（技能/演出 ID）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8C40(uint32_t *this)  // 实现：信徒初始化（语音组装载 + 技能参数）
{
  *(this + 1698) = 1;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1700) = 1;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1699) = 2;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1701) = 2;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 3;  // this+6808〔nVoiceParam4(推断)〕
  sub_4015C0("BELIEVER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_FIND", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("KNIFE_HIT", 9u);  // 【std::string构造赋值】
  *(this + 2166) = 10;  // this+8664〔uAI8664(推断)〕
  *(this + 2167) = 0;  // this+8668〔nCool8668(推断)〕
  *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
  *(this + 2168) = 30014;  // this+8672〔uAI8672(推断)〕
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
void /*userpurge*/ sub_5B8CE0(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)  // 实现：信徒大型主状态机（243L）补充
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
  int nCtorState; // [esp+48h] [ebp-4h]

  nBigState = pArg1[1639];  // nBigState = 取 pArg1[1639]
  if ( nBigState == 8 )  // 若 nBigState == 8
  {
    nEvt = ArgList;
    if ( ArgList != 8 && (sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1 || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      *((uint8_t *)pArg1 + 8604) = 0;
  }
  else  // 否则分支
  {
    if ( nBigState == 10 )  // 若 nBigState == 10
    {
      if ( ArgList == 0 )  // 若 ArgList 为 0
      {
        nPhase2072 = pArg1[2072];  // nPhase2072 = 取 pArg1[2072]
        if ( nPhase2072 != 0 )  // 若 nPhase2072 非 0
        {
          if ( nPhase2072 == 1 )  // 若 nPhase2072 == 1
          {
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
              pArg1,
              "BELIEVER_COMMAND",  // 标签 BELIEVER_COMMAND
              -1,
              0,
              0);
            sub_5B8BD0(pArg1);  // 目标解算收尾（CNZealot cast 后强制进指挥态）
          }
          else if ( nPhase2072 == 2 )
          {
            sub_5B7660(pArg1);  // 信徒(CNZealot)绑定确认回落
          }
        }
        else  // 否则分支
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 调虚槽 +308：是否本地玩家
          {
            nTpOffset = pArg1[2160] - 600;
            nTpSlot = 0;
            switch ( nTpOffset )  // 按 nTpOffset 分派
            {
              case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                nTpSlot = 2;
                break;  // 跳出循环/分支
              case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                nTpSlot = 1;
                break;  // 跳出循环/分支
              case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                nTpSlot = 3;
                break;  // 跳出循环/分支
              case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                nTpSlot = 4;
                break;  // 跳出循环/分支
              default:  // 默认分支
                break;  // 跳出循环/分支
            }
            pVt = *pArg1;
            pCtrl0 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);  // 调虚槽 +672：自身 HP
            nFindRes = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
                    pArg1,
                    2,
                    &nTpSlot,
                    1,
                    0xFFFF,
                    0,
                    0,
                    0,
                    0);
            nFindY = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 124))(pArg1, 0, nFindRes);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            nFindX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nFindY);  // 调虚槽 +120：动画对象
            nFindX3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *pCtrl0, nFindX2);  // 调虚槽 +376：坐标同步包（type 37）
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(pVt + 592))(pArg1, pArg1[2160], nFindX3);
          }
          ++pArg1[2159];
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 16));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 20));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 24));  // 调虚槽 +208：定时器移除
      sub_5B7500(0);  // 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 996))(pArg1);  // 调虚槽 +996：复活计时器清零（写 -1）
    }
    nEvt = ArgList;
  }
  if ( nEvt == 15 )  // 若 nEvt == 15
  {
    pEvtArgs = *(int **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    nObjKey2 = pEvtArgs[1];  // nObjKey2 = 取 pEvtArgs[1]
    nObjKey1 = *pEvtArgs;
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    pRepairTarget = sub_45EBE0(nObjKey1, nObjKey2);  // pRepairTarget = 调 sub_45EBE0 返回值
    if ( pRepairTarget == 0 )  // 若 pRepairTarget 为 0
      return;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "REPAIR_OBJECT", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    Block = operator new(0x80u);  // new(128 字节) 分配对象
    nCtorState = 0;
    if ( Block != nullptr )  // 若 Block 有效（非空）
    {
      fArg2 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRepairTarget + 740))(pRepairTarget) * 0.30000001;  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
      *(float *)&fRepairVal = fArg2;
      pTextObj = sub_4D6810(Block, fRepairVal, 5000, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
    }
    else  // 否则分支
    {
      pTextObj = nullptr;  // pTextObj = 空指针
    }
    pTextObjVt = *(uint32_t *)pTextObj;
    nCtorState = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(pTextObj, pRepairTarget, pArg1, 0, 0, 0, -1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    sub_4926A0(*(uint32_t *)(pArg1[1554] + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 0, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    nEvt = ArgList;
    pArg1[2161] = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
    ++pArg1[2162];
  }
  sub_4E33D0((int)pArg1, pArg4, fArg2, nEvt, pArg4, *(float *)&nArg5, *(float *)&nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  switch ( nEvt )  // 按 nEvt 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1  // crypt4byte 解密校验（·0x41A590 逆运算）
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_ATK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      }
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( pArg1[1787] == 25 )
      {
        nClock1910 = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
        pVt2 = *pArg1;
        pArg1[1926] = nClock1910 + 5000;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 1104))(pArg1, 4);
      }
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      sub_4926A0(*(uint32_t *)pArg1[1554]);  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)pArg1[1554]);  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      break;  // 跳出循环/分支
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_PRAY", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      nPhase2072b = pArg1[2072];  // nPhase2072b = 取 pArg1[2072]
      if ( nPhase2072b != 0 )  // 若 nPhase2072b 非 0
      {
        if ( nPhase2072b == 1 || nPhase2072b == 2 )  // 若 nPhase2072b == 1 与/或 nPhase2072b == 2
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            pArg1,
            1,
            0,
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(  // 调虚槽 +992
            pArg1,
            *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36),
            1);
          sub_5B86D0(1);  // 三帧位偏移挂装/还原（-100/100/200）
          ++pArg1[2163];
          pArg1[2164] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4);  // pArg4+4〔宿主对象〕
          pArg1[2165] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 8);  // pArg4+4〔宿主对象〕
        }
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          pArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          pArg1,
          1,
          0,
          0,
          0,
          0,
          0);
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36), 1);  // 调虚槽 +992
        sub_5B86D0(1);  // 三帧位偏移挂装/还原（-100/100/200）
        sub_5B7500(1);  // 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5B9240 sub_5B9240 —— 主状态机透传（反应态 5 时补写音效槽 163）
// 调 ·sub_5B8CE0 主状态机；this+6556==5（死亡收尾）时经 vt+216 写音效槽 163。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9240(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：主状态机透传（反应态 5 时补写音效槽 163）
{
  int result; // eax

  result = sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);  // 信徒大型主状态机（243L）补充
  if ( *(this + 1639) == 5 )  // this+6556〔大状态ID〕
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 216))(this, 163);  // 调虚槽 +216：音效 TAG 查询
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
int /*thiscall*/ sub_5B9280(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：附着火焰攻击（事件 16 点火 debuff）补充
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

  if ( ArgList != 16 )  // 若 ArgList != 16
    return sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);  // 信徒大型主状态机（243L）补充
  pEvtArgs = *(int **)(LODWORD(fArg3) + 4);
  nObjKey2 = pEvtArgs[1];  // nObjKey2 = 取 pEvtArgs[1]
  nObjKey1 = *pEvtArgs;
  (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  result = sub_45EBE0(nObjKey1, nObjKey2);  // result = 调 sub_45EBE0 返回值
  pTargetObj = result;
  if ( result != 0 )  // 若结果非 0（成功）
  {
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      pVecHdr = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);  // 调虚槽 +700：读 +6296 槽
      pVecBegin = *(uint32_t *)(pVecHdr + 4);
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(pVecHdr + 8) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= nCnt )
        break;  // 跳出循环/分支
      pVecHdr2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);  // 调虚槽 +700：读 +6296 槽
      pVecBegin2 = *(uint32_t *)(pVecHdr2 + 4);
      if ( pVecBegin2 != 0 && i < (*(uint32_t *)(pVecHdr2 + 8) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
        pListObj = *(uint32_t *)(pVecBegin2 + 4 * i);
      else  // 否则分支
        pListObj = 0;
      if ( *(uint32_t *)(pListObj + 4) == pTargetObj )
      {
        pVecHdr3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTargetObj + 700))(pTargetObj);  // 调虚槽 +700：读 +6296 槽
        pVecBegin3 = *(uint32_t *)(pVecHdr3 + 4);
        if ( pVecBegin3 != 0 && i < (*(uint32_t *)(pVecHdr3 + 8) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
          pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * i);
        else  // 否则分支
          pListObj2 = 0;
        pAppendage = __RTDynamicCast(
                pListObj2,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNAppendageTimerFireDamage `RTTI Type Descriptor',
                0);
        if ( pAppendage != 0 )  // 若 pAppendage 非 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pAppendage + 76))(pAppendage, 0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
          break;  // 跳出循环/分支
        }
      }
    }
    pMem = operator new(0x5Cu);  // new(92 字节) 分配对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      pFireDmg = sub_5B85C0(pMem, 10000, 999, 20);  // CNAppendageTimerFireDamage 构造（延烧附着物）
    else  // 否则分支
      pFireDmg = nullptr;  // pFireDmg = 空指针
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int *, uint32_t, uint32_t, uint32_t, int))(*pFireDmg + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
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
int /*thiscall*/ sub_5B93F0(uint32_t *this, int nArg2, int nArg3)  // 实现：指挥旗挂载（new 0x64 → ·sub_51A7D0）并提速
{
  int result; // eax
  void *pMem; // eax
  int pNewObj; // eax
  unsigned int pCtrl830; // edi
  int edxTmp; // edx
  unsigned int pCtrl858; // edi
  int edxTmp2; // edx
  int fVal830; // [esp+20h] [ebp+Ch]
  int fVal858; // [esp+20h] [ebp+Ch]

  result = sub_5B7CD0((int)this, nArg2, nArg3);  // 分身参数面清空（形态槽置 7584=1）
  if ( nArg3 == 0 )  // 若 nArg3 为 0
  {
    if ( *(this + 2169) == 0 )  // this+8676〔uAI8676(推断)〕
    {
      pMem = operator new(0x64u);  // new(100 字节) 分配对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pNewObj = sub_51A7D0(pMem);  // pNewObj = 调 sub_51A7D0 返回值
      else  // 否则分支
        pNewObj = 0;
      *(this + 2169) = pNewObj;  // this+8676〔uAI8676(推断)〕
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pNewObj + 64))(pNewObj) + 36) = 0;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2169) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        *(this + 2169),  // this+8676〔uAI8676(推断)〕
        this,
        this,
        1,
        0,
        0,
        -1);
    }
    pCtrl830 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;  // 调虚槽 +672：自身 HP
    *(float *)&fVal830 = COERCE_FLOAT(sub_41A5E0(pCtrl830)) + 0.5;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl830, edxTmp, fVal830);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pCtrl858 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;  // 调虚槽 +672：自身 HP
    *(float *)&fVal858 = COERCE_FLOAT(sub_41A5E0(pCtrl858)) + 0.5;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pCtrl858, edxTmp2, fVal858);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 调虚槽 +676
  }
  return result;
}



// 插刀技能：KNIFE_STICK 播报（sub_431230 参数打包; this+200/8605/8606 相位）
// ------------------------------------------------------------
// 0x5B9500 sub_5B9500 —— 插刀技能（KNIFE_STICK 播报 + 事件 5 派发）
// 经 vt+200 取帧位后 +148==2 且 this+8606==0 时播 KNIFE_STICK 并置 this+8606=1；
// 帧位 +170 非 0 时 ·sub_431230 打包事件参数 5，经 vt+472(5,打包,1,1) 派发并置 this+8605=1。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9500(uint8_t *this)  // 实现：插刀技能（KNIFE_STICK 播报 + 事件 5 派发）
{
  void *Block2; // eax
  bool bBlockFree; // zf
  uint8_t pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int nPad1; // [esp+10h] [ebp-18h]
  int nPad2; // [esp+14h] [ebp-14h]
  uint32_t aArgList[4]; // [esp+18h] [ebp-10h] BYREF

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) == 2 && *(this + 8606) == 0 )  // 调虚槽 +200：取动画对象
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
      this,
      "KNIFE_STICK",  // 标签 KNIFE_STICK
      -1,
      0,
      0);
    *(this + 8606) = 1;
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 调虚槽 +200：取动画对象
  {
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
    aArgList[3] = 0;
    aArgList[0] = 5;
    sub_431230((int)pBuf, aArgList);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint8_t *, int, int))(*(uint32_t *)this + 472))(this, 5, pBuf, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
    Block2 = Block;
    bBlockFree = Block == nullptr;
    *(this + 8605) = 1;
    if ( !bBlockFree )
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
void /*thiscall*/ sub_5B95D0(uint32_t *this)  // 实现：信徒·寻损车决策（setState 15 修复）补充
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
  int nCtorState; // [esp+28h] [ebp-4h]

  if ( (int)*(this + 2162) < 3  // this+8648〔uPhase8648(推断)〕
    && *(this + 2161) + 7000 <= (unsigned int)sub_699000((int)(this + 9))  // 【clock_now(clk)】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      fld_e29 = *(this + 29);  // this+116〔会话上下文〕
      pVecBegin = *(uint32_t *)(fld_e29 + 8);
      nIdxSaved = i;
      nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
      if ( (int)i >= nCnt )
        break;  // 跳出循环/分支
      pVecBegin2 = *(uint32_t *)(fld_e29 + 8);
      if ( pVecBegin2 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - pVecBegin2) >> 2 )  // 若 pVecBegin2 != 0
        pListObj = *(uint32_t *)(pVecBegin2 + 4 * i);
      else  // 否则分支
        pListObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        fld_e292 = *(this + 29);  // this+116〔会话上下文〕
        pVecBegin3 = *(uint32_t *)(fld_e292 + 8);
        if ( pVecBegin3 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - pVecBegin3) >> 2 )  // 若 pVecBegin3 != 0
          pListObj2 = *(uint32_t *)(pVecBegin3 + 4 * i);
        else  // 否则分支
          pListObj2 = 0;
        pVehicle = __RTDynamicCast(pListObj2, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);  // pVehicle = 调 __RTDynamicCast
        if ( pVehicle != 0 )  // 若 pVehicle 非 0
        {
          nRoomId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 376))(pVehicle);  // 调虚槽 +376：坐标同步包（type 37）
          if ( nRoomId == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 调虚槽 +376：坐标同步包（type 37）
            && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pVehicle, 0) <= 100 )  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
          {
            nVehVal = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 736))(pVehicle);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
            pVehicleVt = *(uint32_t *)pVehicle;
            fVehVal = (float)nVehVal;
            nVehVal = (*(int (/*thiscall*/ **)(int))(pVehicleVt + 740))(pVehicle);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
            if ( (double)nVehVal * 0.30000001 >= fVehVal )
            {
              memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
              pVehicleVt2 = *(uint32_t *)pVehicle;
              nCtorState = 0;
              fVehVal = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(pVehicleVt2 + 48))(pVehicle));  // fVehVal = 调 COERCE_FLOAT
              sub_431230((int)pBuf, &fVehVal);  // uint32 vector push_back
              fVehVal = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVehicle + 52))(pVehicle));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
              sub_431230((int)pBuf, &fVehVal);  // uint32 vector push_back
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 15, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
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
void /*thiscall*/ sub_5B97A0(uint32_t *this)  // 实现：信徒·祈祷决策（setState 10）补充
{
  int fld_e1908; // eax
  int i; // edi
  int fld_e29; // ecx
  int pVecBegin; // edx
  int nCnt; // eax
  int pCand; // eax
  int pCandRaw; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t aArgList[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    fld_e1908 = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
    if ( (fld_e1908 == 0 || fld_e1908 == 2 && *(this + 1909) == 0)  // this+7636〔nPosWinY〕
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0  // 调虚槽 +840：大状态 getter（this+6556）
      && *(this + 1787) != 25  // this+7148〔nBigState〕
      && *(this + 1813) != 0  // this+7252〔pTarget7252〕
      && (int)*(this + 2159) < 3  // this+8636〔pDollTarget(推断)〕
      && rand() % 300 < 20 )  // 20% 概率触发（rand()%300 < 20）
    {
      aArgList[0] = 0;
      for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
      {
        fld_e29 = *(this + 29);  // this+116〔会话上下文〕
        pVecBegin = *(uint32_t *)(fld_e29 + 8);
        nCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( i >= nCnt )  // 若 i >= nCnt
          break;  // 跳出循环/分支
        pCand = sub_4259D0(i);  // 元素取值（+2 组）
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pCand + 40))(pCand, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        {
          pCandRaw = sub_4259D0(i);  // 元素取值（+2 组）
          if ( *(uint32_t **)(__RTDynamicCast(
                              pCandRaw,
                              0,
                              &CNRDObject `RTTI Type Descriptor',
                              &IRDMonster `RTTI Type Descriptor',
                              0)
                          + 8352) == this )
            ++aArgList[0];
        }
      }
      if ( aArgList[0] < 2 )
      {
        memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
        aArgList[3] = 0;
        aArgList[0] = 0;
        sub_431230((int)pBuf, aArgList);  // uint32 vector push_back
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
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
void /*thiscall*/ sub_5B98F0(uint32_t *this, int nArg2)  // 实现：信徒·传教解算（nArg2=1 指挥 / 2 布道；setState 10）
{
  int fld_e1908; // eax
  int nSlotIdx; // ebx
  int fld_e29; // ecx
  int pVecBegin; // edx
  int nScanCnt; // eax
  int pObj; // eax
  int pScanObj; // eax
  int pObj2; // esi
  void *vecArg; // [esp+4h] [ebp-1Ch] BYREF
  int nVecBegin; // [esp+8h] [ebp-18h]
  int nVecEnd; // [esp+Ch] [ebp-14h]
  int nVecCap; // [esp+10h] [ebp-10h]
  int nVecProxy; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )  // 调虚槽 +308：是否本地玩家
    return;
  fld_e1908 = *(this + 1908);  // this+7632〔uWindow7632(推断)〕
  if ( fld_e1908 != 0 && (fld_e1908 != 2 || *(this + 1909) != 1) )  // this+7636〔nPosWinY〕
    return;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0  // 调虚槽 +840：大状态 getter（this+6556）
    || *(this + 1787) == 25  // this+7148〔nBigState〕
    || nArg2 != 1 && nArg2 != 2
    || (int)*(this + 2163) >= 3  // this+8652〔uPhase8652(推断)〕
    || *(this + 1813) == 0  // this+7252〔pTarget7252〕
    || rand() % 300 >= 20 )  // rand()%300 取模随机
  {
    return;
  }
  nVecBegin = 0;
  nVecEnd = 0;
  nVecCap = 0;
  nVecProxy = 0;
  sub_431230((int)&vecArg, &nArg2);  // uint32 vector push_back
  nSlotIdx = 0;
  while ( 1 )  // 条件循环
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    pVecBegin = *(uint32_t *)(fld_e29 + 8);
    nScanCnt = pVecBegin != 0 ? (*(uint32_t *)(fld_e29 + 12) - pVecBegin) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( nSlotIdx >= nScanCnt )  // 若 nSlotIdx >= nScanCnt
      break;  // 跳出循环/分支
    pObj = sub_4259D0(nSlotIdx);  // 元素取值（+2 组）
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      goto LABEL_28;
    pScanObj = sub_4259D0(nSlotIdx);  // 元素取值（+2 组）
    pObj2 = __RTDynamicCast(pScanObj, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);  // pObj2 = 调 __RTDynamicCast
    if ( pObj2 == 0 )  // 若 pObj2 为 0
      goto LABEL_28;
    if ( nArg2 != 1 )  // 若 nArg2 != 1
    {
      if ( nArg2 != 2 || *(int *)(pObj2 + 8668) > 0 )  // 若 nArg2 != 2
        goto LABEL_28;
      goto LABEL_24;
    }
    if ( *(uint8_t *)(pObj2 + 8607) != 0 )  // pObj2+8607〔bAI8607(推断)〕
    {
      ++nSlotIdx;
    }
    else  // 否则分支
    {
LABEL_24:  // 标签 LABEL_24（跳转合流点）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2) != 0  // 调虚槽 +1244
        && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 260  // 调虚槽 +340：三元组基址（+284，vt+340）
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 263  // 调虚槽 +340：三元组基址（+284，vt+340）
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 264) )  // 调虚槽 +340：三元组基址（+284，vt+340）
      {
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
        sub_431230((int)&vecArg, &nArg2);  // uint32 vector push_back
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_431230((int)&vecArg, &nArg2);  // uint32 vector push_back
        break;  // 跳出循环/分支
      }
LABEL_28:  // 标签 LABEL_28（跳转合流点）
      ++nSlotIdx;
    }
  }
  if ( nVecBegin != 0 && (unsigned int)((nVecEnd - nVecBegin) >> 2) > 1 )  // 若 nVecBegin != 0
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, &vecArg, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  sub_5E5260(&vecArg);  // 调 动画子对象清理临时缓冲
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B00 sub_5B9B00 —— 信徒 AI 拍合并（行为拍 + 寻车 + 寻损车修复）
// 单拍三连：·sub_5B77F0 行为字节拍、·sub_5B87C0 寻车解算、·sub_5B95D0 寻损车修复决策。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B00(int *this)  // 实现：信徒 AI 拍合并（行为拍 + 寻车 + 寻损车修复）
{
  sub_5B77F0(this);  // 行为字节拍（高概率化变体）
  sub_5B87C0(this);  // 信徒·寻车解算（场景标记 529 + CNVehicle cast）
  sub_5B95D0(this);  // 信徒·寻损车决策（setState 15 修复）补充
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B20 sub_5B9B20 —— 信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 2 型）
// 与 ·sub_5B9B00 同构（差异：第二/第三段为 ·sub_5B97A0 与 ·sub_5B98F0(this,2)）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B20(int *this)  // 实现：信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 2 型）
{
  sub_5B77F0(this);  // 行为字节拍（高概率化变体）
  sub_5B97A0(this);  // 信徒·祈祷决策（setState 10）补充
  sub_5B98F0(this, 2);  // 信徒·传教解算（nArg2=1 指挥 / 2 布道；setState 10）
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B40 sub_5B9B40 —— 信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 1 型）
// 与 ·sub_5B9B20 同构（差异：末段 ·sub_5B98F0(this,1)，取指挥态目标）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B40(int *this)  // 实现：信徒 AI 拍合并（行为拍 + 祈祷决策 + 传教 1 型）
{
  sub_5B77F0(this);  // 行为字节拍（高概率化变体）
  sub_5B97A0(this);  // 信徒·祈祷决策（setState 10）补充
  sub_5B98F0(this, 1);  // 信徒·传教解算（nArg2=1 指挥 / 2 布道；setState 10）
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B9B60 sub_5B9B60 —— 点火事件派发（30% 概率 setState 16）后尾调反击判定
// 门=vt+840 大状态 8、this+7028 空槽、vt+40(nArg2,17) 存活 且有目标，rand%100<30 时
// ·sub_431230 打包 nArg2 的 vt+48/vt+52 坐标，vt+560 进 16（与 ·sub_5B9280 事件 16 呼应点火）；
// 末尾无条件交 ·sub_4DB480 反击/架招触发判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9B60(void *this, int nArg2, int nArg3, int nArg4)  // 实现：点火事件派发（30% 概率 setState 16）后尾调反击判定
{
  int pThis_348; // eax
  int pObj; // edi
  int pVt; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int nCtorState; // [esp+20h] [ebp-4h]

  pThis_348 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  pObj = nArg2;
  if ( pThis_348 == 8  // 若 pThis_348 == 8
    && sub_41A5E0((unsigned int)this + 7028) == 0  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && rand() % 100 < 30 )  // 30% 概率触发（rand()%100 < 30）
  {
    memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
    pVt = *(uint32_t *)pObj;
    nCtorState = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(pVt + 48))(pObj);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    sub_431230((int)pBuf, &nArg2);  // uint32 vector push_back
    (*(void (/*thiscall*/ **)(void *, int, void **, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 16, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    nCtorState = -1;
    sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
  }
  return sub_4DB480(pObj, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
}



// 祈祷技能：BELIEVER_PRAY 播报（103L；this+208 相位 —— 治疗channel/咏唱【推断】）
// ------------------------------------------------------------
// 0x5B9C60 sub_5B9C60 —— 祈祷技能收尾（BELIEVER_PRAY 播报 + 3 型收尾）补充
// 补充：前置场景识别经 ·sub_41A5E0==3 时直接 setState 10；子相位 this[2072]==3 时
// vt+580 发 20014（10 段/4 朝向）表现包、·sub_49C970/·sub_49C5F0 光环族驱动、
// vt+876 双轴归零、vt+992 复位、·sub_5B86D0 挂三帧、·sub_5B7500 盾闪收尾；
// 末段整体透传 ·sub_5B8CE0。
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9C60(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：祈祷技能收尾（BELIEVER_PRAY 播报 + 3 型收尾）补充
{
  int fld_e1639; // edi
  bool bPrayState; // zf
  int nEvt; // edi
  uint8_t pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int nPad1; // [esp+10h] [ebp-14h]
  int nPad2; // [esp+14h] [ebp-10h]
  int nCtorState; // [esp+20h] [ebp-4h]

  fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
  if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
      nCtorState = 0;
      ArgList = 3;
      sub_431230((int)pBuf, &ArgList);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 10, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);
    }
  }
  else  // 否则分支
  {
    bPrayState = fld_e1639 == 10;
    nEvt = ArgList;
    if ( bPrayState )
    {
      if ( ArgList == 0 && *(this + 2072) == 3 )  // 若 ArgList == 0
      {
        sub_49C970(8, ArgList, ArgList);  // 池分配包装（this+4 复制为第 2/3 参）
        sub_49C5F0(9, 0, 0, 4000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
          (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
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
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));  // 调虚槽 +208：定时器移除
      sub_5B7500(this, 0);  // 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 996))(this);  // 调虚槽 +996：复活计时器清零（写 -1）
    }
    sub_5B8CE0(this, nEvt, fArg3, nArg4, nArg5);  // 信徒大型主状态机（243L）补充
    if ( nEvt == 10 )  // 若 nEvt == 10
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "BELIEVER_PRAY",  // 标签 BELIEVER_PRAY
        -1,
        0,
        0);
      if ( *(this + 2072) == 3 )  // this+8288〔nGrabDataVal(推断)〕
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 992))(  // 调虚槽 +992
          this,
          *(uint32_t *)(*(uint32_t *)(*(this + 1554) + 8) + 36),  // this+6216〔pTbl6216(推断)〕
          1);
        sub_5B86D0(this, 1);  // 三帧位偏移挂装/还原（-100/100/200）
        sub_5B7500(this, 1);  // 盾闪开关（SHIELD_FLASH 播报 + 三槽偏移）
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
void */*thiscall*/ sub_5B9EA0(uint32_t *this, uint32_t *Block)  // 实现：献祭长驻（this+8664=20；new CNAuraMasterATDFSPEEDUpFather）
{
  void *result; // eax
  int pVt; // eax
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx

  result = Block;
  if ( Block == this )  // 若 Block == this
  {
    pVt = *this;
    *(this + 2166) = 20;  // this+8664〔uAI8664(推断)〕
    (*(void (**)(void))(pVt + 700))();  // 调虚槽 +700：读 +6296 槽
    sub_53F6A0(this);  // 调 收尾路径
    pMem = operator new(0x90u);  // new(144 字节) 分配对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      sub_64C710(300, 1041865114, 1041865114, 0, 0);  // 战斗动画查询 2（5910D0）
      *pMem = &CNAuraMasterATDFSPEEDUpFather::`vftable';  // 构造装配 vftable：CNAuraMasterATDFSPEEDUpFather
      pMem2 = pMem;
    }
    else  // 否则分支
    {
      pMem2 = nullptr;  // pMem2 = 空指针
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      pMem2,
      this,
      this,
      0,
      0,
      0,
      -1);
    result = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
    *(this + 2160) = result;  // this+8640〔uCastSlot8640(推断)〕
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
void /*thiscall*/ sub_5B9F60(int *this)  // 实现：地面火导弹附着（FireMissileParticleFloor.ptl）补充
{
  uint32_t *pMem; // eax
  int *fld_e1; // eax
  int pHostObj; // ecx
  int pVt; // edx
  int pHostObj_; // edi
  int fld_e22; // ebx
  int *pHostObj_2; // esi
  int pVt2; // edx
  void *pFxObj; // eax
  int nX; // [esp-Ch] [ebp-38h]
  int nY; // [esp-8h] [ebp-34h]
  int nZ; // [esp-4h] [ebp-30h]
  uint8_t pBuf[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int nCtorState; // [esp+28h] [ebp-4h]

  sub_5F66C0();  // 【IRDAppendage__vmt4】
  if ( *(this + 22) == 0 )  // this+88〔pFxObjB(推断)〕
  {
    pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
    pMem2 = pMem;
    nCtorState = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      fld_e1 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/FireMissileParticleFloor.ptl", *(this + 1));  // CNRDObjectParticleCreater 构造
    else  // 否则分支
      fld_e1 = nullptr;  // fld_e1 = 空指针
    pHostObj = *(this + 1);  // this+4〔宿主对象〕
    *(this + 22) = (int)fld_e1;  // this+88〔pFxObjB(推断)〕
    pVt = *fld_e1;
    nCtorState = -1;
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 112))(fld_e1, pHostObj);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  }
  pHostObj_ = *(this + 1);  // this+4〔宿主对象〕
  fld_e22 = *(uint32_t *)*(this + 22);  // fld_e22 = 读 this+22
  nZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 128))(pHostObj_);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 124))(pHostObj_);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 120))(pHostObj_);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e22 + 40))(*(this + 22));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 22) + 92))(*(this + 22), pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
  pHostObj_2 = (int *)*(this + 1);  // this+4〔宿主对象〕
  pVt2 = *pHostObj_2;
  nCtorState = 1;
  pFxObj = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(pVt2 + 80))(pHostObj_2, 2, 0, pBuf);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  sub_4600B0(pFxObj, nX, nY, nZ);  // 调 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);
}



// 子类扩展字段复位（this+8600/8604/8605）
// ------------------------------------------------------------
// 0x5BA050 sub_5BA050 —— 子类扩展字段复位（this+8600 指针 + 8604/8605 状态字节 + 6792..6808）
// 清 this+8600（uint32 资源/机器对象指针）、8604/8605（相位字节，与 ·sub_5B8CE0/·sub_5B8590
// 的读写点对应）、this+6792/6796/6800/6804/6808 五槽（炮车参数面【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA050(int this)  // 实现：子类扩展字段复位（this+8600 指针 + 8604/8605 状态字节 + 6792..6808）
{
  *(uint32_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint8_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint8_t *)(this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
  *(uint32_t *)(this + 6792) = 0;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6796) = 0;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6800) = 0;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 6804) = 0;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6808) = 0;  // this+6808〔nVoiceParam4(推断)〕
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA090 sub_5BA090 —— 资源对象释放（this+8600 经 vtable[0](obj,1)）并清槽
// this+8600 指针非空时按 vtable[0](obj,1) 释放（删除式），随后槽置 0；
// 与 ·sub_5BA050 的清位互为配套（先释放后复位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA090(uint32_t *this)  // 实现：资源对象释放（this+8600 经 vtable(obj,1)）并清槽
{
  int (/*thiscall*/ ***fld_e2150)(uint32_t, int); // ecx
  int result; // eax

  fld_e2150 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2150);  // this+8600〔uAI8600(推断)〕
  if ( fld_e2150 != nullptr )  // 若 fld_e2150 有效（非空）
    result = (**fld_e2150)(fld_e2150, 1);  // 调 fld_e2150 的虚函数（vt+0）
  *(this + 2150) = 0;  // this+8600〔uAI8600(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA0B0 sub_5BA0B0 —— 炮车系·攻击态朝向对准（基类收尾 + 面向目标）
// 先调 ·sub_4E33D0 做基类状态收尾；武器态 ArgList==8（攻击）且目标 this+1813 有效时，
// 按双方 X 槽（vt+120）大小经 vt+148/vt+144 写翻转朝向——·sub_5BA3E0/·sub_5BA570 的公共前置。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA0B0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：炮车系·攻击态朝向对准（基类收尾 + 面向目标）
{
  int result; // eax
  int nTgtX; // edi
  BOOL bTgtRight; // edi

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    result = *(this + 1813);  // this+7252〔pTarget7252〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      nTgtX = (*(int (**)(void))(*(uint32_t *)result + 120))();  // 调虚槽 +120：动画对象
      bTgtRight = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < nTgtX;  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 148))(this, bTgtRight);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      return (*(int (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 144))(this, bTgtRight);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
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
int /*thiscall*/ sub_5BA120(int *this)  // 实现：炮车系·反应态决策机（行为字 this+1787 概率互转）
{
  int result; // eax
  int nRand2; // eax
  int nRandMod; // et2
  int nRand; // eax
  int nRandMod2; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_4;
      nRand = rand();  // nRand = 调 rand
      nRandMod2 = nRand % 100;
      result = nRand / 100;
      if ( nRandMod2 < 10 )  // 若 nRandMod2 < 10
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        nRand2 = rand();  // nRand2 = 调 rand
        nRandMod = nRand2 % 100;
        result = nRand2 / 100;
        if ( nRandMod < 2 )  // 若 nRandMod < 2
          goto LABEL_11;
      }
      else  // 否则分支
      {
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_11:  // 标签 LABEL_11（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA200 sub_5BA200 —— 三效果槽释放（this+2153/2154/2155）
// 逐槽按 vtable[0](obj,1) 释放后清零——与 ·sub_5BAD00 的 EF_Fire/EF_Hikari/FlameThrower 装载互为对偶。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA200(uint32_t *this)  // 实现：三效果槽释放（this+2153/2154/2155）
{
  int (/*thiscall*/ ***fld_e2153)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2154)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx

  fld_e2153 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2153);  // this+8612〔uAI8612(推断)〕
  if ( fld_e2153 != nullptr )  // 若 fld_e2153 有效（非空）
    result = (**fld_e2153)(fld_e2153, 1);  // 调 fld_e2153 的虚函数（vt+0）
  fld_e2154 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);  // this+8616〔uAI8616(推断)〕
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  if ( fld_e2154 != nullptr )  // 若 fld_e2154 有效（非空）
    result = (**fld_e2154)(fld_e2154, 1);  // 调 fld_e2154 的虚函数（vt+0）
  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);  // this+8620〔uAI8620(推断)〕
  *(this + 2154) = 0;  // this+8616〔uAI8616(推断)〕
  if ( fld_e2155 != nullptr )  // 若 fld_e2155 有效（非空）
    result = (**fld_e2155)(fld_e2155, 1);  // 调 fld_e2155 的虚函数（vt+0）
  *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA250 sub_5BA250 —— 炮车系·攻击态水平朝向追随（叠加反应态机）
// 先跑 ·sub_5BA120 反应态机；大状态 vt+840==8（攻击）且武器档 ·sub_41A5E0(this+1757)==2 时，
// 按目标 this+1813 与自身 X（vt+120）比较经 vt+144 置/清朝向。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA250(int *this)  // 实现：炮车系·攻击态水平朝向追随（叠加反应态机）
{
  int result; // eax
  int fld_e1813; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）

  sub_5BA120(this);  // 炮车系·反应态决策机（行为字 this+1787 概率互转）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 2 )  // 若 result == 2
    {
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )  // 调虚槽 +152：效果通道 3
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813 )  // 调虚槽 +120：动画对象
            (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, 1);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
        }
        result = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
        if ( result == 1 )  // 若 result == 1
        {
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
          if ( result >= fld_e18132 )  // 若 result >= fld_e18132
            return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, 0);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
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
int /*thiscall*/ sub_5BA2F0(uint32_t *this)  // 实现：炮车·炮弹发射（平射/抛射二选一弹道）
{
  int pPtlParams; // eax

  if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    pPtlParams = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallDirect.ptl");  // 调虚槽 +588
  else  // 否则分支
    pPtlParams = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallAngle.ptl");  // 调虚槽 +588
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
           this,
           *(this + 2156),  // this+8624〔uAI8624(推断)〕
           0,
           pPtlParams,
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
int /*thiscall*/ sub_5BA350(int this, int nArg2, int nArg3)  // 实现：分身/攻击参数面复位（激活标志 this+7535=1）
{
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint8_t *)(this + 7535) = 1;  // this+7535〔bCfgBlock15(推断)〕
  return 0;
}



// 蓄力播报：COWCANNON_READY（炮车牛瞄准, this+8612 相位）
// ------------------------------------------------------------
// 0x5BA3E0 sub_5BA3E0 —— 炮车牛·蓄力就绪（COWCANNON_READY）
// 先走 ·sub_5BA0B0 基类前置；武器态 ArgList==8 时清 this+8612 相位并经 vt+212 播报（-1 立即）——
// 与 ·sub_5BAB60 的 COWCANNON_SHOOT 播报成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA3E0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：炮车牛·蓄力就绪（COWCANNON_READY）
{
  int result; // eax
  int pVt; // eax

  result = sub_5BA0B0(this, ArgList, fArg3, nArg4, nArg5);  // 炮车系·攻击态朝向对准（基类收尾 + 面向目标）
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    pVt = *this;
    *((uint8_t *)this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(pVt + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
             this,
             "COWCANNON_READY",  // 标签 COWCANNON_READY
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
int /*thiscall*/ sub_5BA430(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：炮车·受击包观察者回调（vmt1F8 覆写）
{
  unsigned int pField684; // eax
  bool bHitOdd; // zf
  signed int nOddTmp; // eax
  unsigned int pField684b; // eax

  if ( (uint8_t)nArg4 == 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    pField684 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);  // 调虚槽 +684：取攻击上下文
    nOddTmp = sub_41A5E0(pField684) & 0x80000001;  // crypt4byte 解密校验（·0x41A590 逆运算）
    bHitOdd = nOddTmp == 0;
    if ( nOddTmp < 0 )  // 若 nOddTmp < 0
      bHitOdd = (((uint8_t)nOddTmp - 1) | 0xFFFFFFFE) == -1;
    if ( !bHitOdd )
    {
      pField684b = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);  // 调虚槽 +684：取攻击上下文
      if ( sub_41A5E0(pField684b) > 0 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) > 90 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
    }
  }
  return sub_4D4A20(this, nArg2, nArg3, nArg4);  // 18 观察者通知（flag=0 轻量版；受击包五号回调）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA4B0 sub_5BA4B0 —— 激光炮·级进帧序弹道解算与发射
// 目标门 vt+308 通过后：vt+152 姿态非 0 时按 224 帧步进表（this[29] 层链 +132 → +360/+364 向量，元素 32 字节）
// 取「表元数×224 − 当前游标 vt+120」再 /100 缩放得发射参数 nScatterOff【推断：帧序表换算】；
// 经 vt+580 以 85/50/4 参数组发射（武器码由调用方传入 30015/30036/48029）。
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5BA4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 实现：激光炮·级进帧序弹道解算与发射
{
  int result; // eax
  int nFaceDir; // ebx
  int64_t nDivTmp; // rax
  int pPropBlk; // eax
  int pEmitBegin; // ecx
  int pEmitVec; // eax
  int nEmitCnt; // edi
  int nScatterOff; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);  // 调虚槽 +152：效果通道 3
    if ( nFaceDir != 0 )  // 若 nFaceDir 非 0
    {
      pPropBlk = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      pEmitBegin = *(uint32_t *)(pPropBlk + 364);
      pEmitVec = pPropBlk + 360;
      if ( pEmitBegin != 0 )  // 若 pEmitBegin 非 0
        nEmitCnt = (*(uint32_t *)(pEmitVec + 8) - pEmitBegin) >> 5;
      else  // 否则分支
        nEmitCnt = 0;
      nDivTmp = 1374389535LL * (224 * nEmitCnt - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));  // 调虚槽 +120：动画对象
    }
    else  // 否则分支
    {
      nDivTmp = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
    }
    nScatterOff = (SHIDWORD(nDivTmp) >> 5) + (HIDWORD(nDivTmp) >> 31);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 调虚槽 +580
             pArg1,
             nArg4,
             nScatterOff,
             0,
             0,
             85,
             0,
             50,
             nFaceDir,
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
int /*userpurge*/ sub_5BA570@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)  // 实现：激光炮/龙炮共用·攻击态映射与播报组
{
  int result; // eax
  int edxTmp; // edx
  int savedregs; // [esp+8h] [ebp+0h]
  int savedregsa; // [esp+8h] [ebp+0h]

  if ( *(uint32_t *)(pArg1 + 6556) == 8 )  // pArg1+6556〔大状态ID〕
  {
    if ( sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));  // 调虚槽 +208：定时器移除
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));  // 调虚槽 +208：定时器移除
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);  // 调虚槽 +216：音效 TAG 查询
    }
  }
  result = sub_5BA0B0((uint32_t *)pArg1, ArgList, fArg4, nArg5, nArg6);  // 炮车系·攻击态朝向对准（基类收尾 + 面向目标）
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    *(uint8_t *)(pArg1 + 8608) = 0;  // pArg1+8608〔uAI8608(推断)〕
    if ( sub_41A5E0(pArg1 + 7028) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg1 + 7028, edxTmp, 4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    if ( sub_41A5E0(pArg1 + 7028) == 4 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      sub_5BA4B0((uint32_t *)pArg1, nArg2, pArg1 + 7028, 48029);  // 激光炮·级进帧序弹道解算与发射
      sub_4926A0(**(uint32_t **)(pArg1 + 6216));  // 帧游标复位（+44 帧数组；递归子链 +204）
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调虚槽 +204：定时器插入
        pArg1,
        100,
        **(uint32_t **)(pArg1 + 6216),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调虚槽 +204：定时器插入
        pArg1,
        200,
        *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
        0,
        0,
        0,
        0);
      savedregs = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_READY");  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8620) + 12))(*(uint32_t *)(pArg1 + 8620), 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      savedregsa = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "DRGCANNON_READY");  // 调虚槽 +212：播放音效 TAG(→50 声道)
    }
    if ( sub_41A5E0(pArg1 + 7028) == 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               pArg1,
               "DRGCANNON_SHOOT",  // 标签 DRGCANNON_SHOOT
               -1,
               0,
               0);
    result = sub_41A5E0(pArg1 + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 1 )  // 若 result == 1
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               pArg1,
               "DRGCANNON_SHOOT",  // 标签 DRGCANNON_SHOOT
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
int /*thiscall*/ sub_5BA700(uint32_t *this, int nArg2, int nArg3)  // 实现：载具·X 轴速率槽降速（1/3 收缩）
{
  int result; // eax

  result = nArg3;
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    result = nArg2;
  if ( result == 0 )  // 若 result 为 0
  {
    result = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    *(float *)(result + 4) = *(float *)(result + 4) * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA730 sub_5BA730 —— 分身/攻击参数面复位变体（激活槽 this+7568=1）
// 与 ·sub_5BA350 同构（差异：使能槽为 this+7568，且门控为 0 时把 this+7620 对象 +4 浮点槽乘 3.0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA730(int this, int nArg2, int nArg3)  // 实现：分身/攻击参数面复位变体（激活槽 this+7568=1）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7568) = 1;  // this+7568〔uEnable7568(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4) * 3.0;  // this+7620〔pStatusPanel(推断)〕
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA7E0 sub_5BA7E0 —— 载具·高位速率槽降速（+132 槽 1/3 收缩）
// 与 ·sub_5BA700 同构（差异：作用槽为 this+1905 对象 +132 即 vt+128 高度槽组的第二浮点【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA7E0(uint32_t *this, int nArg2, int nArg3)  // 实现：载具·高位速率槽降速（+132 槽 1/3 收缩）
{
  int result; // eax
  int pParamObj7620; // eax  | +0x1DC4 → 速度/属性参数对象（其 +4/+68/+100/+132 浮点被倍率改写）【推断】（CNLaserCatapult）
  double fSpeed132; // st7

  result = nArg3;
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    result = nArg2;
  if ( result == 0 )  // 若 result 为 0
  {
    pParamObj7620 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    fSpeed132 = *(float *)(pParamObj7620 + 132);
    result = pParamObj7620 + 128;
    *(float *)(result + 4) = fSpeed132 * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA810 sub_5BA810 —— 分身/攻击参数面复位变体（激活槽 this+7564=2）
// 与 ·sub_5BA730 同构（差异：使能槽为 this+7564 且置双字节值 2，缩放槽同为 this+7620 对象 +132）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA810(int this, int nArg2, int nArg3)  // 实现：分身/攻击参数面复位变体（激活槽 this+7564=2）
{
  int result; // eax
  int nArg32; // edx

  result = 0;
  *(uint8_t *)(this + 7558) = 0;  // this+7558〔bAtk7558(推断)〕
  *(uint8_t *)(this + 7557) = 0;  // this+7557〔bAtk7557(推断)〕
  *(uint8_t *)(this + 7556) = 0;  // this+7556〔bAtk7556(推断)〕
  *(uint8_t *)(this + 7534) = 0;  // this+7534〔bCfgBlock14(推断)〕
  *(uint8_t *)(this + 7533) = 0;  // this+7533〔bCfgBlock13(推断)〕
  *(uint8_t *)(this + 7532) = 0;  // this+7532〔bCfgBlock12(推断)〕
  *(uint8_t *)(this + 7531) = 0;  // this+7531〔bCfgBlock11(推断)〕
  *(uint32_t *)(this + 7535) = 0;  // this+7535〔bCfgBlock15(推断)〕
  *(uint32_t *)(this + 7539) = 0;  // this+7539〔bCfgTail(推断)〕
  *(uint32_t *)(this + 7543) = 0;  // this+7543〔uAtk7543(推断)〕
  *(uint32_t *)(this + 7547) = 0;  // this+7547〔uAtk7547(推断)〕
  *(uint32_t *)(this + 7551) = 0;  // this+7551〔uAtk7551(推断)〕
  *(uint8_t *)(this + 7555) = 0;  // this+7555〔bAtk7555(推断)〕
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;  // this+7572〔uGrade7572(推断)〕
  *(uint32_t *)(this + 7568) = 0;  // this+7568〔uEnable7568(推断)〕
  *(uint32_t *)(this + 7564) = 0;  // this+7564〔uForm7564(推断)〕
  *(uint32_t *)(this + 7588) = 0;  // this+7588〔uForm7588〕
  *(uint32_t *)(this + 7584) = 0;  // this+7584〔uForm7584〕
  *(uint32_t *)(this + 7580) = 0;  // this+7580〔uSegDefault7580(推断)〕
  *(uint32_t *)(this + 7576) = 0;  // this+7576〔uPhase7576(推断)〕
  *(uint32_t *)(this + 7596) = 0;  // this+7596〔nOffset7596(推断)〕
  *(uint32_t *)(this + 7564) = 2;  // this+7564〔uForm7564(推断)〕
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    nArg32 = nArg2;
  if ( nArg32 == 0 )  // 若 nArg32 为 0
    *(float *)(*(uint32_t *)(this + 7620) + 132) = *(float *)(*(uint32_t *)(this + 7620) + 132) * 3.0;  // this+7620〔pStatusPanel(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA8D0 sub_5BA8D0 —— 炮车·骑乘位姿提交（炮台对象归位挂层）
// 2150 对象 vt[3](0) 复位动画，按 vt[32](this)→vt[31](+50)→vt[30] 链式取位经对象 vt+40 写入，
// vt+92 打包后由 sub_4600B0 以层号 2 挂到自身层链(this+29)——由 ·sub_5BAC50/80/ACC0 在放生/撤离时调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BA8D0(uint32_t **this)  // 实现：炮车·骑乘位姿提交（炮台对象归位挂层）
{
  int fld_e2150; // edi
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  void *fld_e29; // ecx
  uint8_t pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int nCtorState; // [esp+20h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2150) + 12))(*(this + 2150), 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
  fld_e2150 = **(this + 2150);  // this+8600〔uAI8600(推断)〕
  nZ = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  nY = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, nZ + 50);
  nX = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, nY);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2150 + 40))(*(this + 2150), nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2150) + 92))(*(this + 2150), pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
  fld_e29 = *(this + 29);  // this+116〔会话上下文〕
  nCtorState = 0;
  sub_4600B0(fld_e29, 2, 0, (int)pBuf);  // 调 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
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
void /*thiscall*/ sub_5BA980(int *this)  // 实现：炮车龙炮·移动循环与滑行特效（DRGCANNON_MOVE_LOOP）
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
  void *pFollowAnim; // ecx
  void *Block2; // eax
  bool bNoBlock; // zf
  int nX; // [esp-Ch] [ebp-34h]
  char pBuf[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int nPad1; // [esp+Ch] [ebp-1Ch]
  int nPad2; // [esp+10h] [ebp-18h]
  uint32_t *pFxResSaved; // [esp+14h] [ebp-14h]
  bool bFlip; // [esp+1Bh] [ebp-Dh]
  int nCtorState; // [esp+24h] [ebp-4h]

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0  // 调虚槽 +840：大状态 getter（this+6556）
    || (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4  // 调虚槽 +184：动画对象 z 倾斜转状态码
    && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )  // 调虚槽 +188：动画对象 z 倾斜转状态码
  {
    if ( *((uint8_t *)this + 8605) == 1 )  // this+8605〔bAI8605(推断)〕
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);  // 调虚槽 +216：音效 TAG 查询
      *((uint8_t *)this + 8605) = 0;  // this+8605〔bAI8605(推断)〕
    }
  }
  else  // 否则分支
  {
    if ( *((uint8_t *)this + 8604) == 0  // this+8604〔bAI8604(推断)〕
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 1  // 调虚槽 +200：取动画对象
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 3) )  // 调虚槽 +200：取动画对象
    {
      pFxRes = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];  // 调虚槽 +924
      pVt = *this;
      pFxResSaved = pFxRes;
      nDirRaw = (*(int (/*thiscall*/ **)(int *))(pVt + 152))(this);  // 调虚槽 +152：效果通道 3
      pVt2 = *this;
      pFxVt = *pFxRes;
      bFlip = nDirRaw == 0;
      nZ = (*(int (/*thiscall*/ **)(int *))(pVt2 + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
      nY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nDx = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, nY + 1) != 0 ? -20 : 20;  // 调虚槽 +152：效果通道 3
      nX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + nDx;  // 调虚槽 +120：动画对象
      pFxObj = pFxResSaved;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(pFxVt + 40))(pFxResSaved, nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pFxResSaved + 28))(pFxResSaved) + 84) = bFlip;  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pFxObj + 12))(pFxObj, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pFxObj + 92))(pFxObj, pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      pFollowAnim = (void *)*(this + 29);  // this+116〔会话上下文〕
      nCtorState = 0;
      sub_4600B0(pFollowAnim, 2, 0, (int)pBuf);  // 调 演播层注册(槽号)
      Block2 = Block;
      bNoBlock = Block == nullptr;
      *((uint8_t *)this + 8604) = 1;  // this+8604〔bAI8604(推断)〕
      nCtorState = -1;
      if ( !bNoBlock )
        j__free(Block2);
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
    }
    else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 && *((uint8_t *)this + 8604) == 1 )  // 调虚槽 +200：取动画对象
    {
      *((uint8_t *)this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
    }
    if ( *((uint8_t *)this + 8605) == 0 )  // this+8605〔bAI8605(推断)〕
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
        this,
        "DRGCANNON_MOVE_LOOP",  // 标签 DRGCANNON_MOVE_LOOP
        9,
        0,
        0);
      *((uint8_t *)this + 8605) = 1;  // this+8605〔bAI8605(推断)〕
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
char /*thiscall*/ sub_5BAB60(int this)  // 实现：炮车牛·开火与骑手放生（COWCANNON_SHOOT）
{
  int nTmp; // eax
  int pRider; // ecx

  sub_5BA980((int *)this);  // 炮车龙炮·移动循环与滑行特效（DRGCANNON_MOVE_LOOP）
  nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( nTmp == 8 )  // 若 nTmp == 8
  {
    nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
    if ( *(int *)(nTmp + 148) >= 9 )
    {
      LOBYTE(nTmp) = *(uint8_t *)(this + 8612);  // this+8612〔uAI8612(推断)〕
      if ( (uint8_t)nTmp == 0 )
      {
        LOBYTE(nTmp) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                       this,
                       "COWCANNON_SHOOT",  // 标签 COWCANNON_SHOOT
                       -1,
                       0,
                       0);
        *(uint8_t *)(this + 8612) = 1;  // this+8612〔uAI8612(推断)〕
      }
    }
  }
  pRider = *(uint32_t *)(this + 8608);  // pRider = 读 this+8608
  if ( pRider != 0 )  // 若 pRider 非 0
  {
    nTmp = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRider + 840))(pRider);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( nTmp == 3 )  // 若 nTmp == 3
    {
      nTmp = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8608) + 236))(*(uint32_t *)(this + 8608));  // this+8608〔uAI8608(推断)〕
      if ( nTmp == 0 )  // 若 nTmp 为 0
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          *(uint32_t *)(this + 8608),  // this+8608〔骑手大状态〕
          0,
          -400,
          -400,
          0,
          2000,
          1);
        LOBYTE(nTmp) = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 888))(  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
                       *(uint32_t *)(this + 8608),  // this+8608〔骑手大状态〕
                       0,
                       0,
                       1000,
                       1000);
        *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
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
int sub_5BAC30()  // 实现：载具破坏音效（DRGCANNON_BREAK）
{
  return sub_4015C0("DRGCANNON_BREAK", 0xFu);  // 【std::string构造赋值】
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC50 sub_5BAC50 —— 炮车·消亡处理（自身命中自我时先归位再死亡）
// 仅当 this==uArg2（消亡对象即自身）时：·sub_5BA8D0 骑乘位姿提交 + vt[54]/·vt+216 进入播报 9；
// 尾调 ·sub_4D9170 消亡通知——与 ·sub_5BAC80/·sub_5BACC0 同族（差异：单次归位+停熄）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC50(uint32_t **this, uint32_t **uArg2)  // 实现：炮车·消亡处理（自身命中自我时先归位再死亡）
{
  if ( this == uArg2 )  // 若 this == uArg2
  {
    sub_5BA8D0(this);  // 炮车·骑乘位姿提交（炮台对象归位挂层）
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);  // 返回 调 sub_4D9170 返回值
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC80 sub_5BAC80 —— 炮车·消亡处理变体（双重停熄）
// 与 ·sub_5BAC50 同构（差异：vt[54] 停熄调用两次、夹在 ·sub_5BA8D0 归位前后）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC80(uint32_t **this, uint32_t **uArg2)  // 实现：炮车·消亡处理变体（双重停熄）
{
  if ( this == uArg2 )  // 若 this == uArg2
  {
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
    sub_5BA8D0(this);  // 炮车·骑乘位姿提交（炮台对象归位挂层）
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);  // 返回 调 sub_4D9170 返回值
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x5BACC0 sub_5BACC0 —— 骑手消亡处理（归位 + 清骑乘槽 this+8608）
// this==nArg2 时 ·sub_5BA8D0 归位 + vt+216 播报 9；随后 ·sub_4D9170 消亡通知，
// 若骑乘槽 this+8608==nArg2 则清 0——与 ·sub_5BAC50 同族（差异：独占骑乘槽清位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BACC0(int this, int nArg2)  // 实现：骑手消亡处理（归位 + 清骑乘槽 this+8608）
{
  int result; // eax

  if ( this == nArg2 )  // 若 this == nArg2
  {
    sub_5BA8D0((uint32_t **)this);  // 炮车·骑乘位姿提交（炮台对象归位挂层）
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);  // 调虚槽 +216：音效 TAG 查询
  }
  result = sub_4D9170(nArg2);  // result = 调 sub_4D9170 返回值
  if ( *(uint32_t *)(this + 8608) == nArg2 )  // this+8608〔uAI8608(推断)〕
    *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
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
int /*thiscall*/ sub_5BAD00(uint8_t *this)  // 实现：载具·破坏粒子族装载（4 槽 + 出场参数）
{
  int pThis_16C; // eax
  int pThis_16C2; // eax
  int pThis_154; // eax
  int nKindIdx; // eax
  const char *pszPtlPath; // edi
  int pThis_16C3; // eax
  int pThis_16C4; // eax
  int result; // eax

  *(this + 8608) = 0;
  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      pThis_16C = sub_4C3640(this + 364, "Particle/EF_Fire.ptl", this);  // pThis_16C = 调 sub_4C3640 返回值
    else  // 否则分支
      pThis_16C = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Fire.ptl", this);  // pThis_16C = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pThis_16C = 0;
  }
  *((uint32_t *)this + 2153) = pThis_16C;  // this+8612〔uAI8612(推断)〕
  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      pThis_16C2 = sub_4C3640(this + 364, "Particle/EF_Hikari.ptl", this);  // pThis_16C2 = 调 sub_4C3640 返回值
    else  // 否则分支
      pThis_16C2 = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Hikari.ptl", this);  // pThis_16C2 = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pThis_16C2 = 0;
  }
  *((uint32_t *)this + 2154) = pThis_16C2;  // this+8616〔uAI8616(推断)〕
  pThis_154 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this) - 270;  // 调虚槽 +340：三元组基址（+284，vt+340）
  if ( pThis_154 != 0 )  // 若 pThis_154 非 0
  {
    nKindIdx = pThis_154 - 2;
    if ( nKindIdx == 0 )  // 若 nKindIdx 为 0
    {
      pszPtlPath = "Particle/FCATADestroy.ptl";  // 粒子 .ptl Particle/FCATADestroy.ptl
      goto LABEL_17;
    }
    if ( nKindIdx == 1 )  // 若 nKindIdx == 1
    {
      pszPtlPath = "Particle/LCATADestroy.ptl";  // 粒子 .ptl Particle/LCATADestroy.ptl
      goto LABEL_17;
    }
  }
  pszPtlPath = "Particle/CATADestroy.ptl";  // 粒子 .ptl Particle/CATADestroy.ptl
LABEL_17:  // 标签 LABEL_17（跳转合流点）
  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      pThis_16C3 = sub_4C3640(this + 364, pszPtlPath, this);  // pThis_16C3 = 调 sub_4C3640 返回值
    else  // 否则分支
      pThis_16C3 = sub_4C3640(*((uint32_t *)this + 91), pszPtlPath, this);  // pThis_16C3 = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pThis_16C3 = 0;
  }
  *((uint32_t *)this + 2150) = pThis_16C3;  // this+8600〔uAI8600(推断)〕
  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      pThis_16C4 = sub_4C3640(this + 364, "Particle/FlameThrower.ptl", this);  // pThis_16C4 = 调 sub_4C3640 返回值
    else  // 否则分支
      pThis_16C4 = sub_4C3640(*((uint32_t *)this + 91), "Particle/FlameThrower.ptl", this);  // pThis_16C4 = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    pThis_16C4 = 0;
  }
  *((uint32_t *)this + 2155) = pThis_16C4;  // this+8620〔uAI8620(推断)〕
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pThis_16C4 + 112))(pThis_16C4, this);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  *((uint32_t *)this + 2156) = result;  // this+8624〔uAI8624(推断)〕
  return result;
}



// 坠落破坏：引用 Particle/BATIDestroy.ptl
// ------------------------------------------------------------
// 0x5BAEF0 sub_5BAEF0 —— 载具·坠落破坏粒子装载（BATIDestroy）
// 装载 Particle/BATIDestroy.ptl 到 this+2150 并清 this+2152 AI 阈值——与 ·sub_5BAD00 同族（差异：单槽坠落型）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAEF0(uint32_t *this)  // 实现：载具·坠落破坏粒子装载（BATIDestroy）
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      result = sub_4C3640(this + 91, "Particle/BATIDestroy.ptl", this);  // result = 调 sub_4C3640 返回值
    else  // 否则分支
      result = sub_4C3640(*(this + 91), "Particle/BATIDestroy.ptl", this);  // result = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    result = 0;
  }
  *(this + 2150) = result;  // this+8600〔uAI8600(推断)〕
  *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
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
int /*thiscall*/ sub_5BAF80(uint32_t *this)  // 实现：载具·烟火特效双段（粒子 + FireSmoke.ani 挂装）
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
  char pBuf[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int nPad1; // [esp+14h] [ebp-20h]
  int nPad2; // [esp+18h] [ebp-1Ch]
  char *pPoolTmp; // [esp+1Ch] [ebp-18h]
  int nLoopCnt; // [esp+20h] [ebp-14h]
  int nSmokeXSaved; // [esp+24h] [ebp-10h]
  int nCtorState; // [esp+30h] [ebp-4h]

  nCurX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 调虚槽 +152：效果通道 3
    nSmokeX = nCurX + 85;
  else  // 否则分支
    nSmokeX = nCurX - 85;
  nSmokeXSaved = nSmokeX;
  pThis_869 = (int **)(this + 2153);  // this+8612〔uAI8612(推断)〕
  nLoopCnt = 2;
  do  // do-while 循环体起点
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_869 + 12))(*pThis_869, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
    pSlotVt = **pThis_869;
    nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY60 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ + 60);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(int *, int, int))(pSlotVt + 40))(*pThis_869, nSmokeXSaved, nY60);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_869 + 92))(*pThis_869, pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    nCtorState = 0;
    sub_4600B0(fld_e29, 2, 0, (int)pBuf);  // 调 演播层注册(槽号)
    nCtorState = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    ++pThis_869;
    bLast = nLoopCnt == 1;
    Block = nullptr;  // Block = 空指针
    nPad1 = 0;
    nPad2 = 0;
    --nLoopCnt;
  }
  while ( !bLast );  // 条件循环
  nCurX2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 调虚槽 +152：效果通道 3
    nFireX = nCurX2 + 75;
  else  // 否则分支
    nFireX = nCurX2 - 75;
  nSmokeXSaved = nFireX;
  nLoopCnt = sub_42FCB0(228);  // CRT 一次性初始化
  nCtorState = 1;
  if ( nLoopCnt != 0 )  // 若 nLoopCnt 非 0
    nLoopCnt = sub_431860((char)"Monster/Vehicle/Particle/ani/FireSmoke.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    nLoopCnt = 0;
  nCtorState = -1;
  pPool = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
  pFxObj = pPool;
  pPoolTmp = pPool;
  nCtorState = 2;
  if ( pPool != nullptr )  // 若 pPool 有效（非空）
  {
    sub_44E0D0(pPool, nLoopCnt, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else  // 否则分支
  {
    pFxObj = nullptr;  // pFxObj = 空指针
  }
  pFxHost = *(this + 29);  // this+116〔会话上下文〕
  nCtorState = -1;
  sub_45FE80(pFxHost, (int)pFxObj, 2, 0, (int)pFxObj, (int)this, 0);  // 调 实体对象注册到演播层
  pFxVt = *(uint32_t *)pFxObj;
  nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(char *, int))(pFxVt + 148))(pFxObj, nFaceDir);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  pFxVt2 = *(uint32_t *)pFxObj;
  nZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nY55 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ2 + 55);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  return (*(int (/*thiscall*/ **)(char *, int, int))(pFxVt2 + 112))(pFxObj, nSmokeXSaved, nY55);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
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
void /*usercall*/ sub_5BB130(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：载具·武器开火分段总控（喷火/激光/龙炮四段）
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
  void *aArgList[7]; // [esp+4h] [ebp-1Ch] BYREF

  sub_5BA980((int *)pArg1);  // 炮车龙炮·移动循环与滑行特效（DRGCANNON_MOVE_LOOP）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    switch ( sub_41A5E0(pArg1 + 7028) )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )  // 调虚槽 +200：取动画对象
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
            sub_5BA2F0((uint32_t *)pArg1);  // 炮车·炮弹发射（平射/抛射二选一弹道）
          sub_5BAF80((uint32_t *)pArg1);  // 载具·烟火特效双段（粒子 + FireSmoke.ani 挂装）
          pVt = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8608) = 1;  // pArg1+8608〔uAI8608(推断)〕
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t))(pVt + 876))(pArg1, 0, 70, 70, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          pVt2 = *(uint32_t *)pArg1;
          hAniKind4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);  // 调虚槽 +152：效果通道 3
          pSparkRes = sub_432E50(hAniKind4);  // 关系码对调映射
          (*(void (/*thiscall*/ **)(int, int))(pVt2 + 896))(pArg1, pSparkRes);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        }
        return;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) < 6 )  // 调虚槽 +200：取动画对象
          goto LABEL_21;
        if ( *(uint8_t *)(pArg1 + 8608) == 0 )  // pArg1+8608〔uAI8608(推断)〕
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pArg1,
            "FLAMETHROWER_FIRE",  // 标签 FLAMETHROWER_FIRE
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pArg1,
            "FLAMETHROWER_LOOP",  // 标签 FLAMETHROWER_LOOP
            9,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;  // pArg1+8608〔uAI8608(推断)〕
LABEL_21:  // 标签 LABEL_21（跳转合流点）
          if ( *(uint8_t *)(pArg1 + 8608) == 0 )  // pArg1+8608〔uAI8608(推断)〕
            return;
        }
        pFlameFx = **(uint32_t **)(pArg1 + 8620);  // pArg1+8620〔uAI8620(推断)〕
        nZ50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 50;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        nY1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1) + 1;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nDx = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 1 ? -80 : 80;  // 调虚槽 +152：效果通道 3
        nX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + nDx;  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(uint32_t))(pFlameFx + 40))(*(uint32_t *)(pArg1 + 8620));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pArg1 + 8620) + 92))(*(uint32_t *)(pArg1 + 8620), aArgList);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
        pVt3 = *(uint32_t *)pArg1;
        aArgList[6] = nullptr;  // aArgList[6] = 空指针
        pLayerList = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(pVt3 + 80))(pArg1, 2, 0, aArgList);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        sub_4600B0(pLayerList, nX, nY1, nZ50);  // 调 演播层注册(槽号)
        sub_5E5260(aArgList);  // 调 动画子对象清理临时缓冲
        return;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 1 && *(uint8_t *)(pArg1 + 8608) == 0 )  // 调虚槽 +200：取动画对象
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
            sub_5BA4B0((uint32_t *)pArg1, 1, nArg3, 30015);  // 激光炮·级进帧序弹道解算与发射
          (*(void (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_SHOOT", -1);  // 调虚槽 +212：播放音效 TAG(→50 声道)
          *(uint8_t *)(pArg1 + 8608) = 1;  // pArg1+8608〔uAI8608(推断)〕
        }
        return;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )  // 调虚槽 +200：取动画对象
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )  // 调虚槽 +308：是否本地玩家
            sub_5BA4B0((uint32_t *)pArg1, nArg2, nArg3, 30036);  // 激光炮·级进帧序弹道解算与发射
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));  // 调虚槽 +208：定时器移除
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));  // 调虚槽 +208：定时器移除
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
            pArg1,
            "LASERCANNON_SHOOT",  // 标签 LASERCANNON_SHOOT
            -1,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;  // pArg1+8608〔uAI8608(推断)〕
        }
        return;
      default:  // 默认分支
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
int /*thiscall*/ sub_5BB420(uint32_t *this)  // 实现：载具/飞艇·高度起点受理（vt+1308 覆写）
{
  int pVt; // edx

  pVt = *this;
  *(this + 2150) = *(this + 81);  // this+8600〔uAI8600(推断)〕等 2 字段
  *((uint8_t *)this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
  *(this + 2169) = 5;  // this+8676〔uAI8676(推断)〕
  return (*(int (**)(void))(pVt + 1308))();  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB450 sub_5BB450 —— 飞艇·反应态决策机（行为字 this+1787 概率互转）
// 与 ·sub_5BA120 同构（差异：0→13、受击后置(4) 5% 转 5、死亡(5) 5% 转 4）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB450(int *this)  // 实现：飞艇·反应态决策机（行为字 this+1787 概率互转）
{
  int result; // eax
  int nRand2; // eax
  int nRandMod; // et2
  int nRand; // eax
  int nRandMod2; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      nRand = rand();  // nRand = 调 rand
      nRandMod2 = nRand % 100;
      result = nRand / 100;
      if ( nRandMod2 < 5 )  // 若 nRandMod2 < 5
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      return result;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      nRand2 = rand();  // nRand2 = 调 rand
      nRandMod = nRand2 % 100;
      result = nRand2 / 100;
      if ( nRandMod < 5 )  // 若 nRandMod < 5
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      return result;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      return result;
    default:  // 默认分支
      return result;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB530 sub_5BB530 —— 飞艇·主镜像 vt+144/148 高度同步（this+1639 门）
// 取 vt+184 槽，若主状态镜像2 this+1639 为 0 或 15 且 vt+184!=4，则经 vt+148/vt+144 写回同值——
// 与 ·sub_5BB570 升降门（this+2151）协同。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB530(int *this)  // 实现：飞艇·主镜像 vt+144/148 高度同步（this+1639 门）
{
  int nPoseIdx; // edi
  int result; // eax

  nPoseIdx = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 调虚槽 +184：动画对象 z 倾斜转状态码
  result = *(this + 1639);  // this+6556〔大状态ID〕
  if ( (result == 0 || result == 15) && nPoseIdx != 4 )  // 若 result == 0 与/或 result == 15 与/或 nPoseIdx != 4
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, nPoseIdx);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, nPoseIdx);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
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
void /*thiscall*/ sub_5BB570(int *this)  // 实现：飞艇·航行循环（AIRSHIP_01_LOOP）
{
  int nBigState; // eax
  int nStateOff; // eax
  int fld_e2150; // ebx
  int pVt; // edi
  int nZ; // eax
  int nX; // eax
  int pHostComp112; // ecx  | +0x0070 → 宿主对象指针（IRDActiveObject·基类；va=004D6970）

  sub_4E1780(this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  nBigState = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( nBigState != 0 )  // 若 nBigState 非 0
  {
    nStateOff = nBigState - 14;
    if ( nStateOff != 0 )  // 若 nStateOff 非 0
    {
      if ( nStateOff == 1 )  // 若 nStateOff == 1
        (*(void (/*thiscall*/ **)(int *))(*this + 1316))(this);  // 调虚槽 +1316：CNGhoul 技能槽 vmt524（4926A0 目标链）
    }
    else if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0  // 调虚槽 +200：取动画对象
           && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  else  // 否则分支
  {
    if ( *(this + 2151) == 1 )  // this+8604〔bAI8604(推断)〕
    {
      fld_e2150 = *(this + 2150);  // this+8600〔uAI8600(推断)〕
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) >= fld_e2150 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      {
        pVt = *this;
        *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
        nZ = (*(int (/*thiscall*/ **)(int *, int))(pVt + 124))(this, fld_e2150);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
        nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nZ);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(int *, int))(pVt + 112))(this, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4  // 调虚槽 +184：动画对象 z 倾斜转状态码
      && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )  // 调虚槽 +188：动画对象 z 倾斜转状态码
    {
      if ( *((uint8_t *)this + 8672) == 1 )  // this+8672〔uAI8672(推断)〕
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);  // 调虚槽 +216：音效 TAG 查询
        *((uint8_t *)this + 8672) = 0;  // this+8672〔uAI8672(推断)〕
      }
    }
    else if ( *((uint8_t *)this + 8672) == 0 )  // this+8672〔uAI8672(推断)〕
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "AIRSHIP_01_LOOP", 9, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      *((uint8_t *)this + 8672) = 1;  // this+8672〔uAI8672(推断)〕
    }
    pHostComp112 = *(this + 28);  // this+112〔pHostComp112〕
    if ( *(uint32_t *)(pHostComp112 + 36) == 0 && *(float *)(pHostComp112 + 24) != 0.0 )  // 复合条件判定（与/或）
      sub_494F20(2, 0.0);  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB6B0 sub_5BB6B0 —— 飞艇·俯冲/架招触发（距离门 + 3.3% 概率）
// 目标门 vt+308 过、大状态==0、目标 this+1813 非空、自身高度 vt+128 >= this+2150 时：
// 与目标 Z 差 abs(vt+124 − 目标 vt+124) < 30，且 X 同侧 200 像素内（|dx|<200 双向判定）时，
// rand()%300<50（约 16.7%【推算】）经 vt+560 setState(14) 进蓄力架招——与 ·sub_5BB570 的 14→15 衔接。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB6B0(int *this)  // 实现：飞艇·俯冲/架招触发（距离门 + 3.3% 概率）
{
  int result; // eax
  int fld_e1813; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // edi
  int pObj; // edi
  int nSelfX; // ebx
  int nTgtX; // edi
  int nTgtX2; // edi
  int nRand; // eax
  int nRandMod; // et2

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 0 )  // 若 result 为 0
    {
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        if ( result >= *(this + 2150) )  // this+8600〔uAI8600(推断)〕
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
          result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e1813);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          if ( result < 30 )  // 若 result < 30
          {
            if ( (fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),  // this+7252〔pTarget7252〕
                  (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e18132)  // 调虚槽 +120：动画对象
              && (pObj = *(this + 1813),  // this+7252〔pTarget7252〕
                  nSelfX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this),  // 调虚槽 +120：动画对象
                  (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - nSelfX < 200)  // 调虚槽 +120：动画对象
              || (nTgtX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),  // this+7252〔pTarget7252〕
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) >= nTgtX)  // 调虚槽 +120：动画对象
              && (nTgtX2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),  // this+7252〔pTarget7252〕
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - nTgtX2) < 200) )  // 调虚槽 +120：动画对象
            {
              nRand = rand();  // nRand = 调 rand
              nRandMod = nRand % 300;
              result = nRand / 300;
              if ( nRandMod < 50 )  // 若 nRandMod < 50
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*usercall*/ sub_5BB7C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：飞艇·瞬移/召唤跳转（10/300 概率 + 全局台数门）
{
  int result; // eax
  int nRand; // eax
  int nRandMod; // et2
  bool bRandZero; // zf
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

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 0 )  // 若 result 为 0
  {
    result = pArg1[2169];  // result = 取 pArg1[2169]
    if ( result > 0 )  // 若 result > 0
    {
      result = pArg1[1813];  // result = 取 pArg1[1813]
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)result != 0 && dword_9A05D4 < 5 )  // 若 dword_9A05D4 < 5
        {
          nRand = rand();  // nRand = 调 rand
          nRandMod = nRand % 300;
          result = nRand / 300;
          if ( nRandMod < 10 )  // 若 nRandMod < 10
          {
            nRand2 = rand() & 0x80000001;  // nRand2 = 调 rand
            bRandZero = nRand2 == 0;
            if ( nRand2 < 0 )  // 若 nRand2 < 0
              bRandZero = (((uint8_t)nRand2 - 1) | 0xFFFFFFFE) == -1;
            if ( bRandZero )
            {
              pVt = *pArg1;
              pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 672))(pArg1, 3, nArg3, nArg2);  // 调虚槽 +672：自身 HP
              nZBase2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
                      pArg1,
                      0,
                      0,
                      0,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              nZBase = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, nZBase2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
            }
            else  // 否则分支
            {
              aTeleParam[0] = rand() % 200 + 100;  // aTeleParam[0] = 调 rand
              aTeleParam[1] = rand() % 100 + 50;  // aTeleParam[1] = 调 rand
              bDirLeft = rand() % 2 == 0;  // bDirLeft = 调 rand
              bDirType = 3 - (rand() % 2 != 0);  // rand()%2 取模随机
              nRand5 = rand();  // nRand5 = 调 rand
              pVt = *pArg1;
              aTeleParam[2] = nRand5 % 60 + 40;
              pCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(pVt + 672))(pArg1, 3, nArg3, nArg2);  // 调虚槽 +672：自身 HP
              nFindRes = (*(int (/*thiscall*/ **)(uint32_t *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
                      pArg1,
                      1,
                      aTeleParam,
                      8,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              nZBase = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, nFindRes) + 10;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
            }
            nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZBase);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
            nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY);  // 调虚槽 +120：动画对象
            nDest = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *pCtrl3, nX);  // 调虚槽 +376：坐标同步包（type 37）
            (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt + 592))(pArg1, 260, nDest);
            return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 17, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*usercall*/ sub_5BB970@<eax>(int nArg1@<ecx>, int nArg2@<edi>)  // 实现：世界包提交·飞艇爆裂（dword_8F8520 包对象）
{
  int result; // eax
  int nRand; // eax
  int nRandMod; // et2
  int pPktVt; // edi
  int nVal1; // eax
  int pPktVt2; // edi
  int nVal2; // eax
  int pPktVt3; // esi
  int nVal3; // eax
  int nRand2; // esi
  int nRand3; // edi

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();  // nRand = 调 rand
    nRandMod = nRand % 100;
    result = nRand / 100;
    if ( nRandMod < 25 )  // 若 nRandMod < 25
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nVal1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nVal1);  // 会话/UDP 管理器
      pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nVal2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nVal2);  // 会话/UDP 管理器
      pPktVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nVal3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(pPktVt3 + 36))(dword_8F8520, nVal3);  // 会话/UDP 管理器
      nRand2 = rand() % 2;  // nRand2 = 调 rand
      nRand3 = rand() % 2;  // nRand3 = 调 rand
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand2);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand3);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BBA60 sub_5BBA60 —— 关卡/交互事件包处理（sub_4DC630 取参）
// ·sub_4DC630 取事件包编号 nEvtCode：==14 时经全局 ·dword_8F8520 包对象 vt+72 取两参 nPoseIdx/nTblSelLo，
// 按 nPoseIdx 经 vt+876 双轴给 60/60/−12 参数、vt+888 播 1000；nPoseIdx==0 → vt+896 挂 aPoseTblLo(nTblSelLo) 表（0/1），
// 否则 vt+896 挂 aPoseTblHi(nTblSelLo) 表（2/3）并返回 14——事件包驱动的姿态/贴图切换【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBA60(int *this)  // 实现：关卡/交互事件包处理（sub_4DC630 取参）
{
  int result; // eax
  int nEvtCode; // edi
  int pVt; // eax
  int pVt2; // eax
  uint32_t aPoseTblLo[2]; // [esp+8h] [ebp-14h]
  uint32_t aPoseTblHi[2]; // [esp+10h] [ebp-Ch]
  uint8_t nTblSelLo; // [esp+1Ah] [ebp-2h] BYREF
  uint8_t nPoseIdx; // [esp+1Bh] [ebp-1h] BYREF

  result = sub_4DC630();  // 关卡/交互事件包处理（关联对象 this+7260 校验）
  nEvtCode = result;
  if ( result != -1 )
  {
    if ( result == 14 )  // 若 result == 14
    {
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &nPoseIdx);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &nTblSelLo);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      pVt = *this;
      aPoseTblLo[0] = 0;
      aPoseTblLo[1] = 1;
      aPoseTblHi[0] = 2;
      aPoseTblHi[1] = 3;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(pVt + 876))(this, nPoseIdx, 60, 60, 0, -12, 1);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
      pVt2 = *this;
      if ( nPoseIdx == 0 )  // 若 nPoseIdx 为 0
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(pVt2 + 896))(this, aPoseTblLo[nTblSelLo], 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        return 14;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t))(pVt2 + 896))(this, 4, aPoseTblHi[nTblSelLo]);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
    return nEvtCode;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BBB30 sub_5BBB30 —— 定时器槽 this+2151 空则转发默认（·sub_4DA1D0）
// this+2151 定时器槽为 0 时转 ·sub_4DA1D0（默认行为），否则直接返回槽值——AI 定时门控件【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB30(int *this)  // 实现：定时器槽 this+2151 空则转发默认（·sub_4DA1D0）
{
  int result; // eax

  result = *(this + 2151);  // this+8604〔bAI8604(推断)〕
  if ( result == 0 )  // 若 result 为 0
    return sub_4DA1D0();  // 返回 调 sub_4DA1D0 返回值
  return result;
}



// 子弹技能：引用 Particle/Bullet.ptl
// ------------------------------------------------------------
// 0x5BBB40 sub_5BBB40 —— 飞艇·双管子弹齐射（Particle/Bullet.ptl）
// vt+588 取 Bullet.ptl 模板 qmemcpy 0x62 字节到栈包，X 偏移 nArg2（-1 不加）；
// vt+580 发两发 30018：Y+65/−44 与 Y+72/−37（右侧管 Z+10）；末两发 ·sub_4926A0 复位帧游标(this+2179/2180 双管)。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB40(int *this, int nArg2, int pArg3, int nArg4, int nArg5)  // 实现：飞艇·双管子弹齐射（Particle/Bullet.ptl）
{
  uint32_t aPtlParams[26]; // [esp+Ch] [ebp-68h] BYREF

  aPtlParams[25] = dword_796E50;
  qmemcpy(
    aPtlParams,
    (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bullet.ptl"),  // 调虚槽 +588
    0x62u);
  if ( nArg2 != -1 )
    aPtlParams[19] += nArg2;
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
    this,
    30018,
    0,
    aPtlParams,
    0,
    pArg3 + 65,
    10,
    -44,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
    this,
    30018,
    0,
    aPtlParams,
    0,
    pArg3 + 72,
    -10,
    -37,
    4,
    0,
    0,
    0);
  sub_4926A0(*(this + 2179));  // 帧游标复位（+44 帧数组；递归子链 +204）
  return sub_4926A0(*(this + 2180));  // 帧游标复位（+44 帧数组；递归子链 +204）
}



// 炸弹技能：引用 Particle/Bomb.ptl
// ------------------------------------------------------------
// 0x5BBC00 sub_5BBC00 —— 飞艇·三发炸弹投放（Particle/Bomb.ptl）
// vt+588 取 Bomb.ptl 模板复制 0x62 字节，vt+580 以 30019 发三发——X+55、X0、X−55（三垂直投放点【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBC00(int *this)  // 实现：飞艇·三发炸弹投放（Particle/Bomb.ptl）
{
  const void *pPtlSrc; // eax
  int pVt; // edx
  uint8_t aPtlParams[100]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pPtlSrc = (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bomb.ptl");  // 调虚槽 +588
  pVt = *this;
  qmemcpy(aPtlParams, pPtlSrc, 0x62u);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(pVt + 580))(
    this,
    30019,
    0,
    aPtlParams,
    0,
    55,
    0,
    0,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
    this,
    30019,
    0,
    aPtlParams,
    0,
    0,
    0,
    0,
    4,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 调虚槽 +580
           this,
           30019,
           0,
           aPtlParams,
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
int /*thiscall*/ sub_5BC100(int *this)  // 实现：飞艇·空袭循环（AIRSHIP_SHOOT）
{
  int pVt; // eax
  int fld_e21714; // eax
  int pVt2; // eax
  int fld_e2171; // ecx
  int fld_e21712; // eax
  int fld_e21713; // eax
  int result; // eax

  sub_5BB570(this);  // 飞艇·航行循环（AIRSHIP_01_LOOP）
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result != 1 )  // 若 result != 1
        return result;
      result = *(this + 2173);  // this+8692〔uVec8692(推断)〕
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )  // 若 result == 0
      {
        pVt2 = *this;
        *(this + 2173) = 1;  // this+8692〔uVec8692(推断)〕
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(pVt2 + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        {
          fld_e2171 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
          if ( fld_e2171 <= 10 )  // 若 fld_e2171 <= 10
            fld_e21712 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
          else  // 否则分支
            fld_e21712 = 20 - fld_e2171;
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t))(*this + 1324))(  // 调虚槽 +1324：Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41…
            this,
            *(this + 2174),  // this+8696〔uVec8696(推断)〕
            -9 * fld_e21712,
            0,
            0);
        }
        fld_e21713 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
        *(this + 2171) = fld_e21713 + 1;  // this+8684〔bGate8684(推断)〕
        if ( fld_e21713 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                 this,
                 "AIRSHIP_SHOOT",  // 标签 AIRSHIP_SHOOT
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )  // 若 result == 1
      {
        result = *(this + 2175);  // this+8700〔uPhase8700(推断)〕
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
      }
    }
    else  // 否则分支
    {
      result = *(this + 2173);  // this+8692〔uVec8692(推断)〕
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )  // 若 result == 0
      {
        pVt = *this;
        *(this + 2173) = 1;  // this+8692〔uVec8692(推断)〕
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(pVt + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 1324))(this, -1, 0, 0, 0);  // 调虚槽 +1324：Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41…
        fld_e21714 = *(this + 2171);  // this+8684〔bGate8684(推断)〕
        *(this + 2171) = fld_e21714 + 1;  // this+8684〔bGate8684(推断)〕
        if ( fld_e21714 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                 this,
                 "AIRSHIP_SHOOT",  // 标签 AIRSHIP_SHOOT
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )  // 若 result == 1
      {
        result = *(this + 2175);  // this+8700〔uPhase8700(推断)〕
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
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
unsigned int /*thiscall*/ sub_5BC150(uint32_t *this)  // 实现：飞艇·回收/复位（帧复位 + 朝向 + 清整层）
{
  int pVt; // edi
  int fld_e1813; // ebx
  int nSelfX; // eax
  unsigned int result; // eax
  unsigned int nLayerIdx; // ecx
  int i; // edx
  int fld_e1905; // edi

  sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  pVt = *this;
  fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
  nSelfX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(pVt + 148))(this, nSelfX < fld_e1813);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  nLayerIdx = 0;
  for ( i = 0; ; i += 32 )  // 遍历循环
  {
    fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
    if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
      break;  // 跳出循环/分支
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( nLayerIdx >= result )  // 若 nLayerIdx >= result
      break;  // 跳出循环/分支
    result = i + fld_e1905;
    ++nLayerIdx;
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
void */*thiscall*/ sub_5BC210(uint32_t *this)  // 实现：飞艇·升空（AIRSHIP_UP）
{
  int pVt; // edx
  int fld_e1554; // eax

  pVt = *this;
  *(this + 81) = *(this + 2150);  // this+324〔nRandPick324〕
  fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
  *(this + 2151) = 1;  // this+8604〔bAI8604(推断)〕
  (*(void (/*stdcall*/ **)(uint32_t))(pVt + 208))(*(uint32_t *)(fld_e1554 + 24));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));  // 调虚槽 +208：定时器移除
  sub_49C5F0(10, 0, 0, 1000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
  return sub_432EA0("AIRSHIP_UP", -1, 0, 0);  // 音效播放包装（非空判定）
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BC280 sub_5BC280 —— 事件包号 10·整层置位（·sub_4D90A0 前置）
// 先调 ·sub_4D90A0(uArg2) 校验/转发事件包；包号 *uArg2==10 时遍历 this+1905..1906 向量（元素 32 字节）
// 逐项首字节置 1（与 ·sub_5BC150 的清 0 对偶）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC280(uint32_t *this, uint32_t *uArg2)  // 实现：事件包号 10·整层置位（·sub_4D90A0 前置）
{
  unsigned int result; // eax
  unsigned int nIdx; // edx
  int i; // edi
  int fld_e1905; // ecx

  result = sub_4D90A0(uArg2);  // result = 调 sub_4D90A0 返回值
  if ( *uArg2 == 10 )
  {
    nIdx = 0;
    for ( i = 0; ; i += 32 )  // 遍历循环
    {
      fld_e1905 = *(this + 1905);  // this+7620〔pStatusPanel(推断)〕
      if ( fld_e1905 == 0 )  // 若 fld_e1905 为 0
        break;  // 跳出循环/分支
      result = (*(this + 1906) - fld_e1905) >> 5;
      if ( nIdx >= result )  // 若 nIdx >= result
        break;  // 跳出循环/分支
      result = i + fld_e1905;
      ++nIdx;
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
unsigned int /*thiscall*/ sub_5BC2D0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：飞艇·卸载/下降状态机（AIRSHIP_UNLOAD/DOWN）
{
  unsigned int result; // eax
  int pVt; // edx
  int fld_e81; // edi  | +0x0144 → 随机/拾取编号槽（IRDActiveObject·基类；va=004D6970）
  int pVt2; // edx

  if ( ArgList == 17 )  // 若 ArgList == 17
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
      this,
      "AIRSHIP_UNLOAD",  // 标签 AIRSHIP_UNLOAD
      -1,
      0,
      0);
    result = *(this + 2169) - 1;  // this+8676〔uAI8676(推断)〕
    *(this + 2169) = result;  // this+8676〔uAI8676(推断)〕
  }
  else  // 否则分支
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 15 && ArgList != 16 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_5BC210(this);  // 飞艇·升空（AIRSHIP_UP）
    sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
    if ( ArgList == 14 )  // 若 ArgList == 14
    {
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
        return sub_5BC150(this);  // 飞艇·回收/复位（帧复位 + 朝向 + 清整层）
      else  // 否则分支
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
    }
    else if ( ArgList == 15 )
    {
      pVt = *this;
      *(this + 81) = *(this + 2153);  // this+324〔nRandPick324〕
      *(this + 2151) = -1;  // this+8604〔bAI8604(推断)〕
      fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(pVt + 128))(this);  // this+324〔nRandPick324〕
      sub_495890(0, 3000);  // 模式选择式方位设置（1/2/其他 三分支）
      sub_4A0550(fld_e81);  // 调 镜头幅度
      sub_4A0600(2);
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));  // 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 20));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      pVt2 = *this;
      *((uint8_t *)this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(pVt2 + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
               this,
               "AIRSHIP_DOWN",  // 标签 AIRSHIP_DOWN
               -1,
               0,
               0);
    }
    else  // 否则分支
    {
      result = ArgList - 16;
      if ( ArgList == 16 )  // 若 ArgList == 16
      {
        sub_5BC210(this);  // 飞艇·升空（AIRSHIP_UP）
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
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
int /*thiscall*/ sub_5BC460(int *this, int nArg2)  // 实现：飞艇·四槽帧复位与重建（this+2175..2180）
{
  int result; // eax

  sub_4926A0(*(this + 2177));  // 帧游标复位（+44 帧数组；递归子链 +204）
  sub_4926A0(*(this + 2175));  // 帧游标复位（+44 帧数组；递归子链 +204）
  sub_4926A0(*(this + 2178));  // 帧游标复位（+44 帧数组；递归子链 +204）
  sub_4926A0(*(this + 2176));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2177));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2175));  // 调虚槽 +208：定时器移除
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2178));  // 调虚槽 +208：定时器移除
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2176));  // 调虚槽 +208：定时器移除
  if ( nArg2 != -1 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 4 * nArg2),  // this+6216〔pTbl6216(推断)〕
      25,
      5,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
             this,
             -100,
             *(uint32_t *)(*(this + 1554) + 4 * nArg2 + 8),  // this+6216〔pTbl6216(推断)〕
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
int /*thiscall*/ sub_5BC530(int *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：飞艇·攻击态武器档分支（时钟门 + 撒弹）
{
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);  // 调虚槽 +1328：CNSwordman__vmt530
  result = sub_5BC2D0(this, ArgList, fArg3, nArg4, nArg5);  // 飞艇·卸载/下降状态机（AIRSHIP_UNLOAD/DOWN）
  if ( ArgList == 5 )  // 若 ArgList == 5
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 1328))(this, -1);  // 调虚槽 +1328：CNSwordman__vmt530
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result >= 0 )  // 若 result >= 0
    {
      if ( result <= 1 )  // 若 result <= 1
      {
        *(this + 2170) = sub_699000((int)(this + 9));  // clock_now(clk)
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1328))(this, 1);  // 调虚槽 +1328：CNSwordman__vmt530
        *(this + 2172) = 20;  // this+8688〔bVec8688(推断)〕
        *(this + 2171) = 0;  // this+8684〔bGate8684(推断)〕
        *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
        return sub_5BB970((int)this, 8);  // 世界包提交·飞艇爆裂（dword_8F8520 包对象）
      }
      else if ( result == 2 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)result != 0 )
        {
          sub_5BBC00(this);  // 飞艇·三发炸弹投放（Particle/Bomb.ptl）
          return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*thiscall*/ sub_5BC620(int *this)  // 实现：飞艇·下沉到位序列（高度阈 + 时钟门 1500）
{
  int fld_e2153; // ebx
  int pVt; // edi
  int nZ; // eax
  int nX; // eax
  int *fld_e1554; // eax
  int pObjBlk; // eax
  int result; // eax

  fld_e2153 = *(this + 2153);  // this+8612〔uAI8612(推断)〕
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= fld_e2153 && *((uint8_t *)this + 8608) == 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    pVt = *this;
    nZ = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, fld_e2153);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nZ);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(pVt + 112))(this, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    fld_e1554 = (int *)(*(this + 1554) + 24);  // this+6216〔pTbl6216(推断)〕
    *((uint8_t *)this + 8608) = 1;  // this+8608〔uAI8608(推断)〕
    sub_4926A0(*fld_e1554);  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 28));  // 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
      this,
      -500,
      *(uint32_t *)(*(this + 1554) + 24),  // this+6216〔pTbl6216(推断)〕
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
      this,
      500,
      *(uint32_t *)(*(this + 1554) + 28),  // this+6216〔pTbl6216(推断)〕
      0,
      0,
      0,
      0);
    pObjBlk = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    sub_424120(*(uint32_t **)(pObjBlk + 132), 2, 300);  // 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
  }
  result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
  if ( result > 1500 )  // 若 result > 1500
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*thiscall*/ sub_5BC720(int *this)  // 实现：飞艇EX·破坏收尾（帧序 + ZepplinEX 破坏粒子 + 引爆）
{
  int *fld_e1554; // eax
  int pAniBlk; // ecx
  int nElemCnt; // eax
  int fld_e2180; // ecx
  int nElemCnt2; // eax

  fld_e1554 = (int *)*(this + 1554);  // this+6216〔pTbl6216(推断)〕
  *(this + 2175) = fld_e1554[1];  // this+8700〔uPhase8700(推断)〕
  *(this + 2177) = *fld_e1554;  // this+8708〔pCandTbl8708(推断)〕
  *(this + 2176) = fld_e1554[3];  // this+8704〔pSegNameTbl8704(推断)〕
  *(this + 2178) = fld_e1554[2];  // this+8712〔nCandTblEnd8712(推断)〕
  pAniBlk = fld_e1554[8];  // pAniBlk = 取 fld_e1554[8]
  *(this + 2179) = pAniBlk;  // this+8716〔uArr8716〕
  *(this + 2180) = fld_e1554[9];  // this+8720〔pSegThrTbl8720〕
  nElemCnt = *(uint32_t *)(pAniBlk + 44);
  if ( nElemCnt != 0 )  // 若 nElemCnt 非 0
    nElemCnt = (*(uint32_t *)(pAniBlk + 48) - nElemCnt) / 88;
  sub_493400(pAniBlk, nElemCnt - 1);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
  fld_e2180 = *(this + 2180);  // this+8720〔pSegThrTbl8720〕
  nElemCnt2 = *(uint32_t *)(fld_e2180 + 44);
  if ( nElemCnt2 != 0 )  // 若 nElemCnt2 非 0
    nElemCnt2 = (*(uint32_t *)(fld_e2180 + 48) - nElemCnt2) / 88;
  sub_493400(fld_e2180, nElemCnt2 - 1);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
    this,
    100,
    *(this + 2179),  // this+8716〔uArr8716〕
    25,
    5,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
    this,
    -100,
    *(this + 2180),  // this+8720〔pSegThrTbl8720〕
    32,
    -3,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);  // 调虚槽 +1328：CNSwordman__vmt530
  *(this + 2173) = 0;  // this+8692〔uVec8692(推断)〕
  *(this + 2151) = 0;  // this+8604〔bAI8604(推断)〕
  *(this + 2153) = 30;  // this+8612〔uAI8612(推断)〕
  sub_4015C0("Particle/ZepplinEXDestroyFly.ptl", 0x20u);  // 【std::string构造赋值】
  return sub_4015C0("Particle/ZepplinEXDestroyDrop.ptl", 0x21u);  // 【std::string构造赋值】
}



// 飞艇破坏 2：Particle/ZepplinDestroyFly/Drop.ptl（空中/坠落两段）
// ------------------------------------------------------------
// 0x5BC840 sub_5BC840 —— 飞艇·破坏粒子槽初始化（Zepplin 双串 0x1E/0x1F）
// this+2153=1（高度阈置 1），经 ·sub_4015C0 写 Particle/ZepplinDestroyFly.ptl(0x1E) 与 ZepplinDestroyDrop.ptl(0x1F)——
// 与 ·sub_5BC720 同族（差异：非 EX 版资源与高度阈 1）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC840(uint32_t *this)  // 实现：飞艇·破坏粒子槽初始化（Zepplin 双串 0x1E/0x1F）
{
  *(this + 2153) = 1;  // this+8612〔uAI8612(推断)〕
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
void /*userpurge*/ sub_5BC880(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)  // 实现：飞艇·破损爆裂（AIRSHIP_BREAK；this==消亡对象时）
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
  uint8_t pBuf[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  uint8_t pPack[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *pHeapBlock; // [esp+1Ch] [ebp-18h]
  int nPad1; // [esp+20h] [ebp-14h]
  int nPad2; // [esp+24h] [ebp-10h]
  int nCtorState; // [esp+30h] [ebp-4h]
  void *pMem; // [esp+3Ch] [ebp+8h]

  sub_4D9170(uArg3);  // 调 消亡通知
  if ( uArg3 == pArg1 )  // 若 uArg3 == pArg1
  {
    pHeapBlock = nullptr;  // pHeapBlock = 空指针
    nPad1 = 0;
    nPad2 = 0;
    nCtorState = 1;
    if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
    {
      if ( pArg1[2160] < 0x10u )
        pszName1 = pArg1 + 2155;
      else  // 否则分支
        pszName1 = (uint32_t *)pArg1[2155];
      if ( pArg1[96] < 0x10u )
        pPtl1 = (int *)sub_4C3640(pArg1 + 91, pszName1, pArg1);  // pPtl1 = 调 sub_4C3640 返回值
      else  // 否则分支
        pPtl1 = (int *)sub_4C3640(pArg1[91], pszName1, pArg1);  // pPtl1 = 调 sub_4C3640 返回值
    }
    else  // 否则分支
    {
      pPtl1 = nullptr;  // pPtl1 = 空指针
    }
    pPtl1Vt = *pPtl1;
    LOBYTE(nCtorState) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(pPtl1Vt + 12))(pPtl1, 0, nArg2);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
    pPtl1Vt2 = *pPtl1;
    nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY50 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZ + 50);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY50);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(pPtl1Vt2 + 40))(pPtl1, nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    nPackRet1 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*pPtl1 + 92))(pPtl1, pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
    LOBYTE(nCtorState) = 2;
    sub_4E77D0((int)pPack, nPackRet1);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
    LOBYTE(nCtorState) = 0;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)pPack);  // 调 演播层注册(槽号)
    pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
    LOBYTE(nCtorState) = 3;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      if ( pArg1[2167] < 0x10u )
        pszName2 = pArg1 + 2162;
      else  // 否则分支
        pszName2 = (uint32_t *)pArg1[2162];
      if ( pArg1[96] < 0x10u )
        pPtl2 = (int *)sub_4C3640(pArg1 + 91, pszName2, pArg1);  // pPtl2 = 调 sub_4C3640 返回值
      else  // 否则分支
        pPtl2 = (int *)sub_4C3640(pArg1[91], pszName2, pArg1);  // pPtl2 = 调 sub_4C3640 返回值
    }
    else  // 否则分支
    {
      pPtl2 = nullptr;  // pPtl2 = 空指针
    }
    pPtl2Vt = *pPtl2;
    LOBYTE(nCtorState) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(pPtl2Vt + 12))(pPtl2, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
    pPtl2Vt2 = *pPtl2;
    nZ2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nY50b = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nZ2 + 50);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nX2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nY50b);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(int *, int))(pPtl2Vt2 + 40))(pPtl2, nX2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    nPackRet2 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*pPtl2 + 92))(pPtl2, pBuf);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
    LOBYTE(nCtorState) = 4;
    sub_4E77D0((int)pPack, nPackRet2);  // uint32 vector 拷贝赋值（自赋值保护 + 容量复用三路）
    LOBYTE(nCtorState) = 0;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)pPack);  // 调 演播层注册(槽号)
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "AIRSHIP_BREAK", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 216))(pArg1, 9);  // 调虚槽 +216：音效 TAG 查询
    if ( pHeapBlock != nullptr )  // 若 pHeapBlock 有效（非空）
      j__free(pHeapBlock);
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
// vt+1312 取参(&nHardArg1,&nHardArg2,pBuf) 后 ·sub_4E5F70 硬直率掷（1,1 模板）、播 ZOMBIE_BITE；随后对受害者 vt+604(0)/vt+612(1,1) 放生重挂，
// 按受害者 Z(vt+128)−1 与自身朝向 vt+152 经 sub_432E50 反写其 X(vt+120)/朝向(vt+148) 吸附；受害者大状态非 5 且目标门过则反被 vt+560 setState(9,...,2)+vt+564。
// 受害者空 → setState 0；控制器字节非 0 → setState 15；受害者 vt+684 档经 sub_41A5E0 <=0 → setState 15。
// ------------------------------------------------------------
int /*usercall*/ sub_5BCAB0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：僵尸变体·撕咬循环（ZOMBIE_BITE）
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
  int nHardArg1; // [esp+4h] [ebp-18h] BYREF
  int nHardArg2; // [esp+8h] [ebp-14h] BYREF
  uint32_t pBuf[4]; // [esp+Ch] [ebp-10h] BYREF

  sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  nStateM14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) - 14;  // 调虚槽 +840：大状态 getter（this+6556）
  if ( nStateM14 != 0 )  // 若 nStateM14 非 0
  {
    result = nStateM14 - 1;
    if ( result == 0 )  // 若 result 为 0
    {
      result = *(uint8_t *)(pArg1[30] + 170);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
  }
  else  // 否则分支
  {
    pVictim = pArg1[2157];  // pVictim = 取 pArg1[2157]
    if ( pVictim != 0 )  // 若 pVictim 非 0
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictim + 840))(pVictim) == 9 )  // 调虚槽 +840：大状态 getter（this+6556）
      {
        if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg3) != 0 )  // 调虚槽 +308：是否本地玩家
          {
            pVt = *pArg1;
            nHardArg1 = 0;
            nHardArg2 = 0;
            memset(pBuf, 0, sizeof(pBuf));
            (*(void (/*thiscall*/ **)(uint32_t *, int *, int *, uint32_t *))(pVt + 1312))(pArg1, &nHardArg1, &nHardArg2, pBuf);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与…
            sub_4E5F70(nArg2, (int)pArg1, pArg1[2157], (float *)&nHardArg1, 1, 1);  // 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
          }
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "ZOMBIE_BITE", -1, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 604))(pArg1[2157], 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
        (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 1, 1);
        pVictimVt = *(uint32_t *)pArg1[2157];
        pVictim2 = pArg1[2157];  // pVictim2 = 取 pArg1[2157]
        nVicZ = (*(int (**)(void))(pVictimVt + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
        nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nVicZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nXBite = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 120))(pVictim2, nY - 1);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt + 112))(pArg1[2157], nXBite);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        pVictimVt2 = *(uint32_t *)pArg1[2157];
        nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
        pSparkRes = sub_432E50(nFaceDir);  // 关系码对调映射
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt2 + 148))(pArg1[2157], pSparkRes);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 840))(pArg1[2157]) != 5  // 调虚槽 +840：大状态 getter（this+6556）
             && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )  // 调虚槽 +308：是否本地玩家
      {
        pVictimVt3 = *(uint32_t *)pArg1[2157];
        nFaceDir2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);  // 调虚槽 +152：效果通道 3
        pSparkRes2 = sub_432E50(nFaceDir2);  // 关系码对调映射
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt3 + 144))(pArg1[2157], pSparkRes2);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 9, 0, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      }
    }
    else  // 否则分支
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
    if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    result = pArg1[2157];  // result = 取 pArg1[2157]
    if ( result != 0 )  // 若结果非 0（成功）
    {
      nCtrl684 = (*(int (**)(void))(*(uint32_t *)result + 684))();  // 调虚槽 +684：取攻击上下文
      result = sub_41A5E0(nCtrl684);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result <= 0 )  // 若 result <= 0
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*thiscall*/ sub_5BCCF0(void *this, int nArg2, int nArg3, int nArg4)  // 实现：僵尸变体·受击包重写（vt+1308 转发 + 反击判定）
{
  (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 1308))(this, nArg2, nArg3, nArg4);  // 调虚槽 +1308：CNGhoulOilSellerOlrek 技能槽 vmt51C（4BA9E0，33 行）
  return sub_4DB480(nArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
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
float */*thiscall*/ sub_5BCD30(int *this, float *pArg2, float *pArg3, float *pArg4)  // 实现：僵尸·撕咬口解算（受害者姿态分型取点）
{
  char uFlag8604; // al  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int uFlag8604_2; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int pVictimChar; // eax
  float *result; // eax
  int nFaceDir1; // eax
  int uFlag8604_3; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nBiteX1; // eax
  double fld_e21574; // st7  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nFaceDir4; // eax
  int uFlag8604_6; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nBiteX4; // eax
  double fld_e215710; // st7  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nFaceDir2; // eax
  int uFlag8604_4; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nBiteX2; // eax
  double fld_e21576; // st7  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nFaceDir3; // eax
  int uFlag8604_5; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nBiteX3; // eax
  double fld_e21578; // st7  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int uFlag8604_; // edi  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int pVictimObj; // ebx
  int nSelfW; // esi
  int nZOff; // edi
  int nZBite; // edi

  uFlag8604 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  uFlag8604_2 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
  if ( uFlag8604 != 0 )  // 若 fld_e2157 非 0
  {
    pVictimChar = __RTDynamicCast(uFlag8604_2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);  // pVictimChar = 调 __RTDynamicCast
    result = *(float **)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimChar + 1032))(pVictimChar);  // 调虚槽 +1032
    if ( result == (float *)1 )
    {
      nFaceDir1 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      uFlag8604_3 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
      if ( nFaceDir1 != 0 )  // 若 nFaceDir1 非 0
        nBiteX1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_3 + 120))(uFlag8604_3) - 52;  // 调虚槽 +120：动画对象
      else  // 否则分支
        nBiteX1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_3 + 120))(uFlag8604_3) + 52;  // 调虚槽 +120：动画对象
      *pArg2 = (float)nBiteX1;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      fld_e21574 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 5);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
      *pArg4 = fld_e21574;
      return pArg4;
    }
    else if ( result != nullptr )
    {
      if ( result == (float *)2 )
      {
        nFaceDir2 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
        uFlag8604_4 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
        if ( nFaceDir2 != 0 )  // 若 nFaceDir2 非 0
          nBiteX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_4 + 120))(uFlag8604_4) - 44;  // 调虚槽 +120：动画对象
        else  // 否则分支
          nBiteX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_4 + 120))(uFlag8604_4) + 44;  // 调虚槽 +120：动画对象
        *pArg2 = (float)nBiteX2;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
        fld_e21576 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 32);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
        *pArg4 = fld_e21576;
        return pArg4;
      }
      else if ( result == (float *)3 )
      {
        nFaceDir3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
        uFlag8604_5 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
        if ( nFaceDir3 != 0 )  // 若 nFaceDir3 非 0
          nBiteX3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_5 + 120))(uFlag8604_5) - 40;  // 调虚槽 +120：动画对象
        else  // 否则分支
          nBiteX3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_5 + 120))(uFlag8604_5) + 40;  // 调虚槽 +120：动画对象
        *pArg2 = (float)nBiteX3;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
        fld_e21578 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
        *pArg4 = fld_e21578;
        return pArg4;
      }
    }
    else  // 否则分支
    {
      nFaceDir4 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      uFlag8604_6 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
      if ( nFaceDir4 != 0 )  // 若 nFaceDir4 非 0
        nBiteX4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_6 + 120))(uFlag8604_6) - 34;  // 调虚槽 +120：动画对象
      else  // 否则分支
        nBiteX4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_6 + 120))(uFlag8604_6) + 34;  // 调虚槽 +120：动画对象
      *pArg2 = (float)nBiteX4;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      fld_e215710 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 12);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
      *pArg4 = fld_e215710;
      return pArg4;
    }
  }
  else  // 否则分支
  {
    *pArg2 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_2 + 120))(uFlag8604_2);  // 调虚槽 +120：动画对象
    *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    uFlag8604_ = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
    pVictimObj = uFlag8604_;
    nSelfW = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 调虚槽 +192
    nZOff = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_ + 128))(uFlag8604_) - nSelfW;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    nZBite = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pVictimObj + 192))(pVictimObj) + nZOff;  // 调虚槽 +192
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
int /*thiscall*/ sub_5BCFC0(uint32_t *this)  // 实现：飞艇·破坏粒子对象释放（this+8668 槽）
{
  int (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax

  fld_e2167 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);  // this+8668〔nCool8668(推断)〕
  if ( fld_e2167 != nullptr )  // 若 fld_e2167 有效（非空）
    result = (**fld_e2167)(fld_e2167, 1);  // 调 fld_e2167 的虚函数（vt+0）
  *(this + 2167) = 0;  // this+8668〔nCool8668(推断)〕
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
int /*thiscall*/ sub_5BCFE0(uint32_t *this, int nArg2, int pArg3)  // 实现：鬼魂·HOLD 蓄力起手（捕获抱杀对象 + 参数面初始化）
{
  int pObj2; // eax
  int pObj; // edi
  int uFlag8604; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nTgtX; // eax
  int uFlag8604_; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nTgtY; // eax
  int uFlag8604_2; // ecx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nTgtZ; // eax
  int pVt; // edx
  int fld_e1554; // ecx
  int pVt2; // edx
  int nPhaseSel; // eax
  uint32_t *pHostComp112; // edi
  float fHitA; // [esp+Ch] [ebp-Ch] BYREF
  float fHitB; // [esp+10h] [ebp-8h] BYREF
  float fHitC; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 == 0  // 若 pObj2 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2157) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2157) = 0;  // this+8628〔nPoolTime(推断)〕
  }
  uFlag8604 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
  if ( uFlag8604 != 0 )  // 若 fld_e2157 非 0
  {
    nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604 + 120))(uFlag8604);  // 调虚槽 +120：动画对象
    uFlag8604_ = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
    *(this + 2159) = nTgtX;  // this+8636〔pDollTarget(推断)〕
    nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_ + 124))(uFlag8604_);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    uFlag8604_2 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
    *(this + 2160) = nTgtY;  // this+8640〔uCastSlot8640(推断)〕
    nTgtZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uFlag8604_2 + 128))(uFlag8604_2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    pVt = *this;
    *(this + 2161) = nTgtZ;  // this+8644〔uPhase8644(推断)〕
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(pVt + 1312))(this, &fHitA, &fHitB, &fHitC);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施法与…
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      this,
      (uint64_t)fHitA >> 32,
      (uint64_t)fHitA,
      (uint64_t)fHitB,
      (uint64_t)fHitC);
  }
  fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
  pVt2 = *this;
  nPhaseSel = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // pArg3+4〔宿主对象〕
  *(this + 2158) = nPhaseSel;  // this+8632〔bDevourFlag(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(pVt2 + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (nPhaseSel != 1 ? 4 : 0)));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));  // 调虚槽 +344：取坐标三元组
  pHostComp112 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *pHostComp112 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pHostComp112 + 308))(*pHostComp112) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)pHostComp112 + 6) != 0.0 )
  {
    pHostComp112[6] = 0;
    *((uint8_t *)pHostComp112 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
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
int /*thiscall*/ sub_5BD1B0(int this)  // 实现：幽灵·语音/死亡特效资源装载与相位复位
{
  uint32_t *pThis_21BC; // ecx
  int result; // eax

  *(uint32_t *)(this + 6792) = 3;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6796) = 3;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6804) = 6;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6808) = 6;  // this+6808〔nVoiceParam4(推断)〕
  *(uint32_t *)(this + 6800) = 5;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8632) = -1;  // this+8632〔bDevourFlag(推断)〕
  pThis_21BC = (uint32_t *)(this + 8636);  // this+8636〔pDollTarget(推断)〕
  *pThis_21BC = 0;
  pThis_21BC[1] = 0;
  pThis_21BC[2] = 0;
  sub_4015C0("WRAITH_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH", 8u);  // 【std::string构造赋值】
  result = sub_4015C0("Monster/Wraith/WraithAni/Die.ani", 0x20u);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8648) = 0;  // this+8648〔uPhase8648(推断)〕
  return result;
}



// 鬼魂死亡特效：Monster/Wraith/WraithSpectressAni/Die.ani（this+8648/8700 相位）
// ------------------------------------------------------------
// 0x5BD270 sub_5BD270 —— 鬼魂·死亡特效装载（Die.ani + 相位置 1）
// this+8648=1 标记死亡特效已装载（与 ·0x5BD1B0 收尾置 0 互补）；this+8700 鬼魂专属相位清零。
// ·sub_4015C0 登记 Monster/Wraith/WraithSpectressAni/Die.ani。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD270(uint8_t *this)  // 实现：鬼魂·死亡特效装载（Die.ani + 相位置 1）
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
int /*thiscall*/ sub_5BD2A0(uint32_t *this)  // 实现：抱杀附加效果生成（两枚 PO + 霸体 PO，生命 15000ms）
{
  uint32_t *pMem; // eax
  int pObj; // esi
  uint32_t *pPoObj; // eax
  uint32_t *pMem2; // eax
  uint32_t *pSuperArmorPo; // eax
  void *pMem3; // eax

  pMem = operator new(0x7Cu);  // new(124 字节) 分配对象
  pObj = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pPoObj = sub_4B3DF0(pMem, 7, 1, 1101004800, 15000, 0);  // CNChangeStatus 构造（六参）
  else  // 否则分支
    pPoObj = nullptr;  // pPoObj = 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pPoObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    pPoObj,
    *(this + 2157),  // this+8628〔nPoolTime(推断)〕
    *(this + 2157),  // this+8628〔nPoolTime(推断)〕
    0,
    0,
    0,
    -1);
  pMem2 = operator new(0x7Cu);  // new(124 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    pSuperArmorPo = sub_4B3DF0(pMem2, 8, 1, 1101004800, 15000, 0);  // CNChangeStatus 构造（六参）
  else  // 否则分支
    pSuperArmorPo = nullptr;  // pSuperArmorPo = 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*pSuperArmorPo + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    pSuperArmorPo,
    *(this + 2157),  // this+8628〔nPoolTime(推断)〕
    *(this + 2157),  // this+8628〔nPoolTime(推断)〕
    0,
    0,
    0,
    -1);
  pMem3 = operator new(0x64u);  // new(100 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    pObj = sub_51A7D0(pMem3);  // pObj = 调 sub_51A7D0 返回值
  *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 40) = 15000;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
           pObj,
           *(this + 2157),  // this+8628〔nPoolTime(推断)〕
           *(this + 2157),  // this+8628〔nPoolTime(推断)〕
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
int /*thiscall*/ sub_5BD3C0(int **this, int *pAttacker, int nArg3, int nArg4)  // 实现：鬼魂吻杀·吸血吸魔结算（主状态 8/14 双分支）
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
  int *uFlag8604; // ecx
  int pVicVt; // ebx
  int nVicHp; // eax
  int nDrainMp; // edi
  int fld_e21573; // ebx  | +0x21B4 → 【推断】子类 AI 状态槽起点〔4AA4E0 构造清 0（uint32）；5BD1B0 资源装载族（CNWraith；va=004AA4E0）
  int nVicMp; // eax
  int pAttackerObj2; // eax
  int nDmgVal; // [esp+10h] [ebp-38h]
  void *pBuf[4]; // [esp+2Ch] [ebp-1Ch] BYREF
  int nCtorState; // [esp+44h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      if ( (uint8_t)result != 0 )
      {
        pAttackerObj = __RTDynamicCast(
               (int)pAttacker,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
        nArg4 = pAttackerObj;
        if ( pAttackerObj != 0  // 若 pAttackerObj 非 0
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAttackerObj + 948))(pAttackerObj) != 0  // 调虚槽 +948
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 840))(nArg4) == 0  // 调虚槽 +840：大状态 getter（this+6556）
          && ((int (/*thiscall*/ *)(int **))(*this)[142])(this) != 14 )
        {
          memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
          nCtorState = 0;
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*pAttacker + 48))(pAttacker);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
          sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*pAttacker + 52))(pAttacker);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
          sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
          nArg4 = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
          ((void (/*thiscall*/ *)(int **, int, void **, uint32_t, uint32_t))(*this)[140])(this, 14, pBuf, 0, 0);
          nCtorState = -1;
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        }
        pAttackerVt = *pAttacker;
        nProp152 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
        pSparkRes = sub_432E50(nProp152);  // 关系码对调映射
        return (*(int (/*thiscall*/ **)(int *, int))(pAttackerVt + 144))(pAttacker, pSparkRes);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
      }
    }
  }
  else if ( ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 14 && *(this + 2157) != nullptr )  // this+8628〔nPoolTime(推断)〕
  {
    ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WRAITH_KISS", -1, 0, 0);  // 标签 WRAITH_KISS
    result = (int)*(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    if ( result == 1 )  // 若 result == 1
    {
      nDrainHp = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 740))(*(this + 2157)) * 0.1);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
      nArg4 = nDrainHp;
      pMem = operator new(0x80u);  // new(128 字节) 分配对象
      nCtorState = 1;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
      {
        *(float *)&nDmgVal = (float)nArg4;
        pTextObj = sub_4D6810(pMem, nDmgVal, 100, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
      }
      else  // 否则分支
      {
        pTextObj = nullptr;  // pTextObj = 空指针
      }
      pTextObjVt = *(uint32_t *)pTextObj;
      nCtorState = -1;
      (*(void (/*thiscall*/ **)(uint8_t *, int **, int **, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        pTextObj,
        this,
        this,
        0,
        0,
        0,
        -1);
      uFlag8604 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
      pVicVt = *uFlag8604;
      nVicHp = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*uFlag8604 + 736))(uFlag8604, 1, 0);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
      return (*(int (/*thiscall*/ **)(uint32_t, int))(pVicVt + 728))(*(this + 2157), nVicHp - nDrainHp);  // 调虚槽 +728：HP setter/扣血
    }
    else if ( result == 2 )
    {
      result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
      if ( (uint8_t)result != 0 )
      {
        nArg4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 756))(*(this + 2157));  // 调虚槽 +756：海星卵适配判定 vmt2F4
        nDrainMp = (uint64_t)((double)nArg4 * 0.15000001);
        fld_e21573 = **(this + 2157);  // this+8628〔nPoolTime(推断)〕
        nVicMp = (*(int (/*stdcall*/ **)(int))(fld_e21573 + 752))(1);  // 调虚槽 +752：音效地板适配判定 vmt2F0
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21573 + 744))(*(this + 2157), nVicMp - nDrainMp);  // 调虚槽 +744：物件破坏三连（表现/掉落/广播）
      }
    }
  }
  else  // 否则分支
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this);
    if ( result == 8 )  // 若 result == 8
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 0 )  // 若 result 为 0
      {
        result = (*(int (/*thiscall*/ **)(int *, int))(*pAttacker + 40))(pAttacker, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        if ( (uint8_t)result != 0 )
        {
          pAttackerObj2 = __RTDynamicCast(
                  (int)pAttacker,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          return (*(int (/*thiscall*/ **)(int, int, int, int, int **, uint32_t))(*(uint32_t *)pAttackerObj2 + 760))(  // 调虚槽 +760：状态槽写入(17 槽异常状态)
                   pAttackerObj2,
                   11,
                   1097859072,  // 浮点常量 15.0f
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
void /*usercall*/ sub_5BD710(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：抱杀收尾·被抱者搬运落位与状态下发
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
  uint8_t pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int nPad1; // [esp+10h] [ebp-18h]
  int nPad2; // [esp+14h] [ebp-14h]
  uint32_t aPackVec[4]; // [esp+18h] [ebp-10h] BYREF

  pVictim = pArg1[2157];  // pVictim = 取 pArg1[2157]
  if ( pVictim != 0 )  // 若 pVictim 非 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pVictim + 604))(pVictim, 1, nArg2);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 136))(  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
           pArg1[2157],
           pArg1[2159],
           pArg1[2160],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 112))(pArg1[2157], pArg1[2159], pArg1[2160]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      pVictim2 = (int *)pArg1[2157];
      pVictimVt = *pVictim2;
      aPackVec[0] = pVictim2;
      aPackVec[0] = *pArg1;
      nTryY = (*(int (/*thiscall*/ **)(int *, int, int, int))(pVictimVt + 124))(pVictim2, 300, 1, 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      nTryX = (*(int (/*thiscall*/ **)(int *, int))(*pVictim2 + 120))(pVictim2, nTryY);  // 调虚槽 +120：动画对象
      bMoveOk = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, int))(aPackVec[0] + 140))(pArg1, pArg1 + 2159, pArg1 + 2160, nTryX);  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
      pVictim3 = (int *)pArg1[2157];
      if ( bMoveOk != 0 )  // 若 bMoveOk 非 0
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*pVictim3 + 112))(pVictim3, pArg1[2159], pArg1[2160]);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
      else  // 否则分支
      {
        pVictimVt2 = *pVictim3;
        nAltY = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, pArg1[2161]);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        nAltX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nAltY);  // 调虚槽 +120：动画对象
        (*(void (/*thiscall*/ **)(uint32_t, int))(pVictimVt2 + 112))(pArg1[2157], nAltX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      Block = nullptr;  // Block = 空指针
      nPad1 = 0;
      nPad2 = 0;
      aPackVec[3] = 0;
      aPackVec[0] = 4;
      sub_431230((int)pBuf, aPackVec);  // uint32 vector push_back
      aPackVec[0] = 0;
      sub_431230((int)pBuf, aPackVec);  // uint32 vector push_back
      aPackVec[0] = 1;
      sub_431230((int)pBuf, aPackVec);  // uint32 vector push_back
      aPackVec[0] = 100;
      sub_431230((int)pBuf, aPackVec);  // uint32 vector push_back
      aPackVec[0] = 100;
      sub_431230((int)pBuf, aPackVec);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 4, pBuf, 2, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      if ( Block != nullptr )  // 若 Block 有效（非空）
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
int /*thiscall*/ sub_5BD8F0(int *this, int nArg2, int nArg3, int nArg4)  // 实现：鬼魂吻杀·吸血吸魔结算（类型过滤 + 标记门控版）
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
  int nHpDrain; // edi
  int fld_e21576; // ebx
  int nHpCur; // eax
  float fDrainF; // [esp+14h] [ebp-38h]
  void *pBuf[4]; // [esp+30h] [ebp-1Ch] BYREF
  int nCtorState; // [esp+48h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8  // 调虚槽 +840：大状态 getter（this+6556）
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      if ( (uint8_t)result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);  // 调虚槽 +340：三元组基址（+284，vt+340）
        if ( *(uint32_t *)result != 410 )  // 类型 410/411 免疫抱杀【推断：BOSS 类免疫】
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);  // 调虚槽 +340：三元组基址（+284，vt+340）
          if ( *(uint32_t *)result != 411 )  // 同上
          {
            pAttackerObj = __RTDynamicCast(
                   nArg2,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
            pAttacker = pAttackerObj;
            if ( pAttackerObj != 0  // 若 pAttackerObj 非 0
              && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAttackerObj + 948))(pAttackerObj) != 0  // 调虚槽 +948
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAttacker + 840))(pAttacker) == 0  // 调虚槽 +840：大状态 getter（this+6556）
              && (*(int (/*thiscall*/ **)(int *))(*this + 568))(this) != 14 )  // 调虚槽 +568
            {
              memset(&pBuf[1], 0, 12);  // 内存块填充 12 字节
              pVt = *(uint32_t *)nArg2;
              nCtorState = 0;
              nArg4 = (*(int (/*thiscall*/ **)(int))(pVt + 48))(nArg2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
              sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
              nArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
              sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
              nArg4 = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
              sub_431230((int)pBuf, &nArg4);  // uint32 vector push_back
              (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
              nCtorState = -1;
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
            }
            pAttackerVt = *(uint32_t *)nArg2;
            nProp152 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
            pSparkRes = sub_432E50(nProp152);  // 关系码对调映射
            return (*(int (/*thiscall*/ **)(int, int))(pAttackerVt + 144))(nArg2, pSparkRes);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
          }
        }
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 && *(this + 2157) != 0 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WRAITH_KISS", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
    result = *(this + 2158);  // this+8632〔bDevourFlag(推断)〕
    if ( result == 1 )  // 若 result == 1
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result == 0 )
        return result;
      bNoDown = (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273) == 0;  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      fld_e21572 = *(uint32_t *)*(this + 2157);  // fld_e21572 = 读 this+2157
      if ( !bNoDown )
      {
        nDrainHp = (uint64_t)((double)(*(int (**)(void))(fld_e21572 + 740))() * 0.050000001);  // 吸血量=受害者 vt+740×5%
        nArg4 = nDrainHp;
        nCtorState = 1;
        if ( operator new(0x80u) != nullptr )  // new(128 字节) 分配对象
        {
          fDrainF = (float)nArg4;
          pTextObj = (int *)sub_4D6810(LODWORD(fDrainF), 100, 1, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
        }
        else  // 否则分支
        {
          pTextObj = nullptr;  // pTextObj = 空指针
        }
        pTextObjVt = *pTextObj;
        nCtorState = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(pTextObjVt + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
          pTextObj,
          this,
          this,
          0,
          0,
          0,
          -1);
        fld_e21573 = (int *)*(this + 2157);  // this+8628〔nPoolTime(推断)〕
        pVicVt = *fld_e21573;
        nVicHp = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_e21573 + 736))(fld_e21573, 1, 0);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
        return (*(int (/*thiscall*/ **)(uint32_t, int))(pVicVt + 728))(*(this + 2157), nVicHp - nDrainHp);  // 调虚槽 +728：HP setter/扣血
      }
    }
    else  // 否则分支
    {
      if ( result != 2 )  // 若 result != 2
        return result;
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result == 0 )
        return result;
      fld_e21574 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      fld_e21575 = (int *)*(this + 2157);  // this+8628〔nPoolTime(推断)〕
      if ( fld_e21574 != 0 )  // 若 fld_e21574 非 0
      {
        nArg4 = (*(int (/*thiscall*/ **)(int *))(*fld_e21575 + 756))(fld_e21575);  // 调虚槽 +756：海星卵适配判定 vmt2F4
        nHpDrain = (uint64_t)((double)nArg4 * 0.050000001);
        fld_e21576 = *(uint32_t *)*(this + 2157);  // fld_e21576 = 读 this+2157
        nHpCur = (*(int (/*stdcall*/ **)(int))(fld_e21576 + 752))(1);  // 调虚槽 +752：音效地板适配判定 vmt2F0
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21576 + 744))(*(this + 2157), nHpCur - nHpDrain);  // 调虚槽 +744：物件破坏三连（表现/掉落/广播）
      }
      fld_e21572 = *fld_e21575;
    }
    result = (*(int (/*stdcall*/ **)(int))(fld_e21572 + 40))(529);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( (uint8_t)result != 0 )
      return sub_5BD2A0(this);  // 抱杀附加效果生成（两枚 PO + 霸体 PO，生命 15000ms）
  }
  else  // 否则分支
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 8 )  // 若 result == 8
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 0 )  // 若 result 为 0
      {
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        if ( (uint8_t)result != 0 )
        {
          result = __RTDynamicCast(
                     nArg2,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDActiveObject `RTTI Type Descriptor',
                     0);
          if ( result != 0 )  // 若结果非 0（成功）
            return (*(int (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)result + 760))(  // 调虚槽 +760：状态槽写入(17 槽异常状态)
                     result,
                     4,
                     1097859072,  // 浮点常量 15.0f
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
int /*thiscall*/ sub_5BDCD0(uint32_t *this, int nArg2, int pArg3)  // 实现：鬼魂·HOLD 蓄力（抱杀名单去重版）
{
  int pObj2; // eax
  int pObj; // ebx
  uint32_t *pThis_86D; // edi
  uint32_t *fld_e2164; // eax
  int nTgtX; // eax
  int pObj3; // ecx
  int nTgtY; // eax
  int pObj4; // edi
  int fld_e1554; // ecx
  int pVt; // edx
  int nPhaseSel; // eax
  uint32_t *pHostComp112; // edi
  float fHitA; // [esp+Ch] [ebp-Ch] BYREF
  float fHitB; // [esp+10h] [ebp-8h] BYREF
  float fHitC; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 == 0 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    pThis_86D = this + 2157;
LABEL_14:  // 标签 LABEL_14（跳转合流点）
    *pThis_86D = 0;
    goto LABEL_15;
  }
  pThis_86D = this + 2157;
  *(this + 2157) = pObj;  // this+8628〔nPoolTime(推断)〕
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    *pThis_86D = 0;
  if ( *pThis_86D != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_86D + 40))(*pThis_86D, 529) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 410  // 调虚槽 +340：三元组基址（+284，vt+340）
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 411 )  // 调虚槽 +340：三元组基址（+284，vt+340）
  {
    fld_e2164 = (uint32_t *)*(this + 2164);  // this+8656〔uPair8656(推断)〕
    if ( fld_e2164 == (uint32_t *)*(this + 2165) )  // this+8660〔uEvt8660(推断)〕
    {
LABEL_12:  // 标签 LABEL_12（跳转合流点）
      sub_4E7BA0(this + 2157);  // 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
      goto LABEL_15;
    }
    while ( *fld_e2164 != *pThis_86D )  // 条件循环
    {
      if ( ++fld_e2164 == (uint32_t *)*(this + 2165) )  // this+8660〔uEvt8660(推断)〕
        goto LABEL_12;
    }
    goto LABEL_14;
  }
LABEL_15:  // 标签 LABEL_15（跳转合流点）
  if ( *pThis_86D != 0 )
  {
    nTgtX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 120))(*pThis_86D);  // 调虚槽 +120：动画对象
    pObj3 = *pThis_86D;
    *(this + 2159) = nTgtX;  // this+8636〔pDollTarget(推断)〕
    nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    pObj4 = *pThis_86D;
    *(this + 2160) = nTgtY;  // this+8640〔uCastSlot8640(推断)〕
    *(this + 2161) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(*this + 1312))(this, &fHitA, &fHitB, &fHitC);  // 调虚槽 +1312：CNGhoul 技能/行为槽（调 493400/4939E0/4E7F30/4926A0 施…
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      this,
      (uint64_t)fHitA >> 32,
      (uint64_t)fHitA,
      (uint64_t)fHitB,
      (uint64_t)fHitC);
  }
  fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
  pVt = *this;
  nPhaseSel = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // pArg3+4〔宿主对象〕
  *(this + 2158) = nPhaseSel;  // this+8632〔bDevourFlag(推断)〕
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(pVt + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (nPhaseSel != 1 ? 4 : 0)));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));  // 调虚槽 +344：取坐标三元组
  pHostComp112 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *pHostComp112 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pHostComp112 + 308))(*pHostComp112) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)pHostComp112 + 6) != 0.0 )
  {
    pHostComp112[6] = 0;
    *((uint8_t *)pHostComp112 + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BDF10 sub_5BDF10 —— 抱杀关系析构通知（被抱者/自身消亡时解挂）
// uArg3（消亡对象）== this+2157 被抱者且大状态 14 → ·sub_5BD710 收尾搬运后清槽；uArg3==自身且抱杀槽非空 → 同样收尾。
// 末尾尾调 ·sub_4D9170 消亡通知，把消亡对象转发给基类登记。
// ------------------------------------------------------------
int /*userpurge*/ sub_5BDF10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)  // 实现：抱杀关系析构通知（被抱者/自身消亡时解挂）
{
  if ( uArg3 == (uint32_t *)pArg1[2157] )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 14 )  // 调虚槽 +840：大状态 getter（this+6556）
      sub_5BD710(pArg1, nArg2);  // 抱杀收尾·被抱者搬运落位与状态下发
    pArg1[2157] = 0;
  }
  if ( uArg3 == pArg1 && pArg1[2157] != 0 )  // 若 uArg3 == pArg1
  {
    sub_5BD710(pArg1, nArg2);  // 抱杀收尾·被抱者搬运落位与状态下发
    pArg1[2157] = 0;
  }
  return sub_4D9170(uArg3);  // 返回 调 sub_4D9170 返回值
}



// 爱心技能：引用 Particle/KissHeart.ptl
// ------------------------------------------------------------
// 0x5BDF80 sub_5BDF80 —— 爱心特效装载（KissHeart.ptl 挂 this+2167）
// new 0x12C 经 ·sub_4C3640 以 this+91 处字符串池装载 Particle/KissHeart.ptl（SSO 分支：this+96 <16 走内联缓冲）。
// 对象句柄写入 this+2167，供 ·0x5BE570 吻杀编排中 vt+12/vt+40/vt+92 二次驱动。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BDF80(uint32_t *this)  // 实现：爱心特效装载（KissHeart.ptl 挂 this+2167）
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )  // new(300 字节) 分配对象
  {
    if ( *(this + 96) < 0x10u )  // this+384〔nAnimNameCap(推断)〕
      result = sub_4C3640(this + 91, "Particle/KissHeart.ptl", this);  // result = 调 sub_4C3640 返回值
    else  // 否则分支
      result = sub_4C3640(*(this + 91), "Particle/KissHeart.ptl", this);  // result = 调 sub_4C3640 返回值
  }
  else  // 否则分支
  {
    result = 0;
  }
  *(this + 2167) = result;  // this+8668〔nCool8668(推断)〕
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
void /*userpurge*/ sub_5BE010(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)  // 实现：鬼魂·反抱事件分发（事件 8 半血阈值定阶段 1/2）
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
    sub_5BD710();  // 抱杀收尾·被抱者搬运落位与状态下发
  nEvt = ArgList;
  pArg42 = pArg4;
  switch ( ArgList )  // 按 ArgList 分派
  {
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1316))(pDwArg1, 14, pArg4);  // 调虚槽 +1316：CNGhoul 技能槽 vmt524（4926A0 目标链）
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      pVt = *pDwArg1;
      nY = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY);  // 调虚槽 +120：动画对象
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt + 136))(pDwArg1, nX) == 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
        || (pVt2 = *pDwArg1,
            nZ = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1),  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
            (*(uint8_t (/*thiscall*/ **)(int *, int))(pVt2 + 132))(pDwArg1, nZ) == 0) )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
      {
        pVictim = pDwArg1[2157];  // pVictim = 取 pDwArg1[2157]
        if ( pVictim != 0 )  // 若 pVictim 非 0
        {
          pVt3 = *pDwArg1;
          pVictim2 = pDwArg1[2157];  // pVictim2 = 取 pDwArg1[2157]
          nVicZ = (*(int (**)(void))(*(uint32_t *)pVictim + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
          nVicY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 124))(pVictim2, nVicZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          nVicX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pVictim2 + 120))(pVictim2, nVicY);  // 调虚槽 +120：动画对象
          (*(void (/*thiscall*/ **)(int *, int))(pVt3 + 112))(pDwArg1, nVicX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
          pArg42 = pArg4;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      nEvt = 15;
      break;  // 跳出循环/分支
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      nKissSub = **(uint32_t **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
      if ( nKissSub != 0 && nKissSub != 3 )  // 若 nKissSub != 0 与/或 nKissSub != 3
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "R_WRAITH_KISS", -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
        fCurHp = (float)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);  // 当前血量
        fArg2 = (double)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1) * 0.5;  // 半血阈值
        pKissParam = *(uint32_t **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
        if ( fArg2 <= fCurHp )  // 若 fArg2 <= fCurHp
          *pKissParam = 2;  // 半血以上→反抱阶段2(继续抱)
        else  // 否则分支
          *pKissParam = 1;  // 半血以下→反抱阶段1(挣脱)
      }
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  sub_4E33D0((int)pDwArg1, pArg42, fArg2, nEvt, pArg42, *(float *)&nArg5, *(float *)&nArg6);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( nEvt == 5 )  // 若 nEvt == 5
  {
    hAniKiss = 0;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    {
      if ( (unsigned int)pDwArg1[2156] < 0x10 )
        LOBYTE(pszPath) = (uint8_t)pDwArg1 - 100;
      else  // 否则分支
        pszPath = pDwArg1[2151];  // pszPath = 取 pDwArg1[2151]
      hAniKiss = sub_431860(pszPath, 1);  // 动画件构造（资源 id 版）
    }
    if ( hAniKiss != 0 )  // 若 hAniKiss 非 0
    {
      pPool = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxObj = pPool;
      if ( pPool != nullptr )  // 若 pPool 有效（非空）
      {
        sub_44E0D0(pPool, hAniKiss, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else  // 否则分支
      {
        pFxObj = nullptr;  // pFxObj = 空指针
      }
      sub_45FE80(pDwArg1[29], (int)pFxObj, 2, 0, (int)pFxObj, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
      pFxVt = *(uint32_t *)pFxObj;
      nZ2 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, nZ2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX2 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, nY2);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(char *, int))(pFxVt + 112))(pFxObj, nX2);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pFxVt2 = *(uint32_t *)pFxObj;
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
      (*(void (/*thiscall*/ **)(char *, int))(pFxVt2 + 144))(pFxObj, nFaceDir);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
    }
  }
}


// 吻杀风特效：Monster/Wraith/WraithSpectressAni/KissWind.ani（60L）
// ------------------------------------------------------------
// 0x5BE250 sub_5BE250 —— 吻杀风特效生成（KissWind.ani 挂被抱者坐标）
// 前置 this+2157 非空 + ·sub_42FCB0(228) 资源门；·sub_431860 装载 KissWind.ani，pool 构造 CNRDPooledObject 后 ·sub_45FE80 挂载。
// 落位读被抱者 vt+128/124/120 三轴链，vt+144 取自身朝向；供 ·0x5BE570 大状态 14 帧段 3 相位调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE250(int *this)  // 实现：吻杀风特效生成（KissWind.ani 挂被抱者坐标）
{
  int result; // eax
  int hAniKissWind; // ebx
  char *pPoolRaw; // eax
  char *pFxObj; // edi
  int pFxVt; // ebx
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  int pFxVt2; // ebx
  int nFaceDir; // eax
  int fld_e2157; // [esp+8h] [ebp-10h]

  result = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = sub_42FCB0(228);  // CRT 一次性初始化
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissWind.ani", 1);  // 动画件构造（资源 id 版）
      hAniKissWind = result;
    }
    else  // 否则分支
    {
      hAniKissWind = 0;
    }
    if ( hAniKissWind != 0 )  // 若 hAniKissWind 非 0
    {
      pPoolRaw = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxObj = pPoolRaw;
      if ( pPoolRaw != nullptr )  // 若 pPoolRaw 有效（非空）
      {
        sub_44E0D0(pPoolRaw, hAniKissWind, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else  // 否则分支
      {
        pFxObj = nullptr;  // pFxObj = 空指针
      }
      sub_45FE80(*(this + 29), (int)pFxObj, 2, 0, (int)pFxObj, (int)this, 0);  // 调 实体对象注册到演播层
      pFxVt = *(uint32_t *)pFxObj;
      fld_e2157 = *(this + 2157);  // this+8628〔nPoolTime(推断)〕
      nZ = (*(int (**)(void))(*(uint32_t *)fld_e2157 + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 124))(fld_e2157, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 120))(fld_e2157, nY);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(char *, int))(pFxVt + 112))(pFxObj, nX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pFxVt2 = *(uint32_t *)pFxObj;
      nFaceDir = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
      return (*(int (/*thiscall*/ **)(char *, int))(pFxVt2 + 144))(pFxObj, nFaceDir);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
    }
  }
  return result;
}



// 吻杀环特效：Monster/Wraith/WraithSpectressAni/KissCircle.ani（57L）
// ------------------------------------------------------------
// 0x5BE360 sub_5BE360 —— 吻杀环特效生成（KissCircle.ani 沿朝向偏移 ±30）
// 与 ·0x5BE250 同构（差异：无 this+2157 前置门；落位在自身 vt+120 按 vt+152 朝向 ±30 偏移、vt+124 传 80）。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE360@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：吻杀环特效生成（KissCircle.ani 沿朝向偏移 ±30）
{
  int result; // eax
  int hAniKissCircle; // ebx
  char *pPoolRaw; // eax
  char *pFxObj; // edi
  int nX; // eax
  int pFxVt; // ebx
  int nY; // eax
  int pFxVt2; // ebx
  int nFaceDir; // eax
  int nXOff; // [esp+8h] [ebp-10h]

  result = sub_42FCB0(228);  // CRT 一次性初始化
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissCircle.ani", 1);  // 动画件构造（资源 id 版）
    hAniKissCircle = result;
  }
  else  // 否则分支
  {
    hAniKissCircle = 0;
  }
  if ( hAniKissCircle != 0 )  // 若 hAniKissCircle 非 0
  {
    pPoolRaw = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
    pFxObj = pPoolRaw;
    if ( pPoolRaw != nullptr )  // 若 pPoolRaw 有效（非空）
    {
      sub_44E0D0(pPoolRaw, hAniKissCircle, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else  // 否则分支
    {
      pFxObj = nullptr;  // pFxObj = 空指针
    }
    sub_45FE80(pDwArg1[29], (int)pFxObj, 2, 0, (int)pFxObj, (int)pDwArg1, 0);  // 调 实体对象注册到演播层
    if ( (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, nArg2) == 1 )  // 调虚槽 +152：效果通道 3
      nX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 30;  // 调虚槽 +120：动画对象
    else  // 否则分支
      nX = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 30;  // 调虚槽 +120：动画对象
    pFxVt = *(uint32_t *)pFxObj;
    nXOff = nX;
    nY = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, 80);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    (*(void (/*thiscall*/ **)(char *, int, int))(pFxVt + 112))(pFxObj, nXOff, nY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    pFxVt2 = *(uint32_t *)pFxObj;
    nFaceDir = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 调虚槽 +152：效果通道 3
    return (*(int (/*thiscall*/ **)(char *, int))(pFxVt2 + 144))(pFxObj, nFaceDir);  // 调虚槽 +144：CNRDAuraMaster__vmt90 槽（13 行）
  }
  return result;
}



// 硬直/相位字段（this+208/8649/8650/8700/8701）
// ------------------------------------------------------------
// 0x5BE470 sub_5BE470 —— 鬼魂·硬直/相位字段更新（事件 8/15 前处理，末尾转 ·0x5BE010）
// 大状态 15（施放）且 this+8701 被抱者可动标记 → vt+944(1,10000) 延时长硬直，随即 vt+340/vt+124/vt+120 链落位；大状态 8（攻击）→ vt+208 帧写入 1554+20 段。
// 事件 8 且参数子类型 3 → this+8700 置 1 并 vt+204 写帧，this+8649/8650 双双置 1 排程吻杀特效；事件 15 → this+8701 = 被抱者带标记 273。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE470(uint8_t *this, int ArgList, int pArg3, int nArg4, int nArg5)  // 实现：鬼魂·硬直/相位字段更新（事件 8/15 前处理，末尾转 ·0x5BE010）
{
  int pThis_348; // eax
  int pVt; // edi
  int pThis_154; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int pThis_612; // eax
  int pVt2; // edx
  int pThis_86D; // ecx
  bool bIsHeld; // al

  pThis_348 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( pThis_348 == 15 )  // 若 pThis_348 == 15
  {
    if ( *(this + 8701) != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)this + 944))(this, 1, 10000);  // 调虚槽 +944
    pVt = *(uint32_t *)this;
    pThis_154 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this);  // 调虚槽 +340：三元组基址（+284，vt+340）
    pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 124))(this, *(uint32_t *)(pThis_154 + 40));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 调虚槽 +120：动画对象
    (*(void (/*thiscall*/ **)(uint8_t *, int))(pVt + 112))(this, pThis_78);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  }
  else if ( pThis_348 == 8 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 20));  // 调虚槽 +208：定时器移除
  }
  if ( ArgList == 8 )  // 若 ArgList == 8
  {
    if ( **(uint32_t **)(pArg3 + 4) == 3 )  // pArg3+4〔宿主对象〕
    {
      pThis_612 = *((uint32_t *)this + 1554);  // this+6216〔pTbl6216(推断)〕
      pVt2 = *(uint32_t *)this;
      *(this + 8700) = 1;
      (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(pVt2 + 204))(  // 调虚槽 +204：定时器插入
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
    pThis_86D = *((uint32_t *)this + 2157);  // this+8628〔nPoolTime(推断)〕
    bIsHeld = pThis_86D != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_86D + 40))(pThis_86D, 273) != 0;  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    *(this + 8701) = bIsHeld;
  }
  return sub_5BE010(this, pArg3, ArgList, *(float *)&pArg3, nArg4, nArg5);  // 鬼魂·反抱事件分发（事件 8 半血阈值定阶段 1/2）
}



// 蝙蝠群：引用 Particle/Bat.ptl（97L；鬼魂召蝙蝠演出）
// ------------------------------------------------------------
// 0x5BE570 sub_5BE570 —— 鬼魂·蝙蝠群/吻杀特效编排（Bat.ptl + 8649/8650 相位 → ·0x5BCAB0）
// this+8524 记 vt+940 反向标记；大状态 8 且 vt+908==3、this+8700 相位 1、动作帧段 ≥4 → vt+588 装载 Particle/Bat.ptl、vt+152 生成、vt+145 槽 30300 登记后清相位。
// 大状态 14 且 vt+908 为 2/1：被抱者类型 529 时按帧段 ≥2 触发 ·0x5BE360 环、≥3 触发 ·0x5BE250 风并布 8672 定时 50ms；定时到点驱动 this+2167 爱心对象 vt+12/vt+40/vt+92 与 ·sub_4600B0 挂装。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE570@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int (***pArg3)(void)@<edi>)  // 实现：鬼魂·蝙蝠群/吻杀特效编排（Bat.ptl + 8649/8650 相位 → ·0x5BCAB0）
{
  char nRet940; // al
  int pVt; // edx
  int pPtlSrc; // eax
  int nFaceRet; // eax
  int pObj; // ecx
  int pCtrlVt; // ebx
  int (**pVtFn)(void); // eax
  int nZ; // eax
  int nY; // eax
  int nX; // eax
  void *pObj29; // ecx
  int nArg22; // [esp-4h] [ebp-2Ch]
  void *aArgList[5]; // [esp+8h] [ebp-20h] BYREF
  int nCtorState; // [esp+24h] [ebp-4h]

  nRet940 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 940))(pArg1);  // 调虚槽 +940
  pVt = *(uint32_t *)pArg1;
  pArg1[8524] = nRet940 == 0;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(pVt + 840))(pArg1) == 8 )  // 调虚槽 +840：大状态 getter（this+6556）
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 3  // 调虚槽 +908：[RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveO…
      && pArg1[8700] == 1
      && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 4 )  // 调虚槽 +200：取动画对象
    {
      pPtlSrc = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/Bat.ptl");  // 调虚槽 +588
      pArg3 = *(int (****)(void))pArg1;
      nFaceRet = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 152))(  // 调虚槽 +152：效果通道 3
             pArg1,
             pPtlSrc,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
      ((void (/*thiscall*/ *)(uint8_t *, int, int))pArg3[145])(pArg1, 30300, nFaceRet);
      pArg1[8700] = 0;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1) == 14  // 调虚槽 +840：大状态 getter（this+6556）
         && ((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 2  // 调虚槽 +908：[RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveO…
          || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 1) )  // 调虚槽 +908：[RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveO…
  {
    pObj = *((uint32_t *)pArg1 + 2157);
    nArg22 = nArg2;
    if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      if ( pArg1[8649] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 )  // 调虚槽 +200：取动画对象
      {
        sub_5BE360((int *)pArg1, (int)pArg3);  // 吻杀环特效生成（KissCircle.ani 沿朝向偏移 ±30）
        pArg1[8649] = 0;
      }
      if ( pArg1[8650] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 )  // 调虚槽 +200：取动画对象
      {
        sub_5BE250((int *)pArg1);  // 吻杀风特效生成（KissWind.ani 挂被抱者坐标）
        pArg1[8650] = 0;
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      if ( *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3  // 调虚槽 +200：取动画对象
        && (uint8_t)sub_41C6E0(pArg1 + 8672) != 0 )  // 超时判定（clock_now(clk) >= this+24 截止时刻）
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)pArg1 + 2167) + 12))(*((uint32_t *)pArg1 + 2167), 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
        pCtrlVt = **((uint32_t **)pArg1 + 2167);
        pArg3 = *((int (****)(void))pArg1 + 2157);
        pVtFn = *pArg3;
        aArgList[4] = pArg3;
        nZ = pVtFn[32]();
        nY = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[31])(pArg3, nZ + 32);
        nX = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[30])(pArg3, nY);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pCtrlVt + 40))(*((uint32_t *)pArg1 + 2167), nX);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**((uint32_t **)pArg1 + 2167) + 92))(*((uint32_t *)pArg1 + 2167), aArgList);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
        pObj29 = *((void **)pArg1 + 29);
        nCtorState = 0;
        sub_4600B0(pObj29, 2, 0, (int)aArgList);  // 调 演播层注册(槽号)
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        nCtorState = -1;
        sub_5E5260(aArgList);  // 调 动画子对象清理临时缓冲
      }
    }
    nArg2 = nArg22;
  }
  return sub_5BCAB0(pArg1, nArg2, (int)pArg3);  // 僵尸变体·撕咬循环（ZOMBIE_BITE）
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
int /*thiscall*/ sub_5BE7C0(int this)  // 实现：蜘蛛·子类字段复位（六槽动作号 + this+7324 类型号）
{
  *(uint32_t *)(this + 6792) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(uint32_t *)(this + 6800) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(uint32_t *)(this + 6868) = 2;
  *(uint32_t *)(this + 6796) = 3;  // this+6796〔nVoiceParam1(推断)〕
  *(uint32_t *)(this + 6804) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(uint32_t *)(this + 6872) = 3;
  *(uint32_t *)(this + 6808) = 4;  // this+6808〔nVoiceParam4(推断)〕
  *(uint32_t *)(this + 6864) = 0;
  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint32_t *)(this + 8604) = 0;  // this+8604〔bAI8604(推断)〕
  *(uint32_t *)(this + 8608) = 0;  // this+8608〔uAI8608(推断)〕
  *(uint32_t *)(this + 8612) = 0;  // this+8612〔uAI8612(推断)〕
  *(uint32_t *)(this + 8624) = 0;  // this+8624〔uAI8624(推断)〕
  *(uint32_t *)(this + 8628) = 0;  // this+8628〔nPoolTime(推断)〕
  *(uint32_t *)(this + 8632) = 0;  // this+8632〔bDevourFlag(推断)〕
  *(uint32_t *)(this + 7324) = 570;  // this+7324〔类型号〕
  *(uint32_t *)(this + 8636) = 0;  // this+8636〔pDollTarget(推断)〕
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BE840 sub_5BE840 —— 蜘蛛·行为字游走机（this+1787 switch + 概率门）
// ·sub_4E0120 推进计时后按 this+1787 行为字分派：0 → vt+1284 自检 proc；4 → 无目标(this+1813==0)回 13、否则 vt+1104 写 5；
// 5 → 有目标且 rand()%100<10 写 4；13/14/15 → 有目标写 4。行为字 4 为捕猎推进态【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE840(int *this)  // 实现：蜘蛛·行为字游走机（this+1787 switch + 概率门）
{
  int result; // eax
  int nRand; // eax
  int nRandMod; // et2

  sub_4E0120();  // 怪物 AI 行为 tick（按 ·this+7148 当前态分发；vt+1104 写新态）
  result = *(this + 1787);  // this+7148〔nBigState〕
  switch ( result )  // 按 result 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);  // 调虚槽 +1284
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_4;
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( *(this + 1813) != 0 )  // this+7252〔pTarget7252〕
      {
        nRand = rand();  // nRand = 调 rand
        nRandMod = nRand % 100;
        result = nRand / 100;
        if ( nRandMod < 10 )  // 若 nRandMod < 10
          goto LABEL_10;
      }
      else  // 否则分支
      {
LABEL_4:  // 标签 LABEL_4（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 调虚槽 +1104
      }
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( result != 0 )  // 若结果非 0（成功）
LABEL_10:  // 标签 LABEL_10（跳转合流点）
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);  // 调虚槽 +1104
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BE910 sub_5BE910 —— 状态施加入口包装（大状态 14 拒收，其余转 ·sub_4D6030）
// 大状态读取 vt+840 == 14（架招）时丢弃本次施加；否则转发 ·sub_4D6030 走 17 状态槽懒创建。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE910(void *this, void *Block, int nArg3, int nArg4)  // 实现：状态施加入口包装（大状态 14 拒收，其余转 ·sub_4D6030）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result != 14 )  // 若 result != 14
    return sub_4D6030((int)this, Block, nArg3, nArg4);  // 状态施加入口（17 状态槽懒创建 + 转发）
  return result;
}



// 蜘蛛·茧载人位移（124L）：this[2152](茧中猎物)处于大状态9 且攻击动作 +170 段时
//   ++this[2153](搬运帧计数)——达到 this[2154](搬运上限) 或猎物 vt+736≤0 则 setState(15)；
//   否则猎物倒地(273)时按其 vt+1032 姿态档与自身朝向从 aOffsetTbl[23] 偏移表取 ±X 偏移，
//   把自己搬到猎物 X±偏移、Y+1、Z+20（背上高度）处
// ------------------------------------------------------------
// 0x5BE940 sub_5BE940 —— 蜘蛛·茧载人位移（详见上方既有注释）
// 被抱猎物 this[2152] 大状态 9 且攻击动作 +170 段 → 搬运帧计数递增，达上限或猎物 vt+736≤0 则 setState(15)；否则 ·sub_4926A0 帧游标复位。
// 猎物未载入时不处于 5/死亡且 vt+308 有效 → 猎物 setState(9) 载入；aOffsetTbl[23] 偏移表按猎物 vt+1032 姿态档 × 朝向取 ±X，自身落位至猎物 X±偏移、Y+1、Z+20；无茧时 this+8600=1 并 setState(15)。
// ------------------------------------------------------------
int /*usercall*/ sub_5BE940@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：蜘蛛·茧载人位移（详见上方既有注释）
{
  int pCocoon; // ecx
  int nCarryMax; // ecx
  int nCarryCnt1; // edx
  int pCurAct; // eax
  int *pCocoon2; // edi
  int pCocoonVt; // eax
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
  int nDxL0; // [esp+4h] [ebp-64h]
  uint32_t aOffsetTbl[23]; // [esp+8h] [ebp-60h]
  int nDxSel; // [esp+64h] [ebp-4h]

  pCocoon = pArg1[2152];  // pCocoon = 取 pArg1[2152]
  if ( pCocoon != 0 )  // 若 pCocoon 非 0
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon + 840))(pCocoon) == 9 )  // 调虚槽 +840：大状态 getter（this+6556）
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )  // 调虚槽 +200：取动画对象
      {
        nCarryMax = pArg1[2154];  // nCarryMax = 取 pArg1[2154]
        nCarryCnt1 = pArg1[2153] + 1;
        pArg1[2153] = nCarryCnt1;
        if ( nCarryCnt1 >= nCarryMax || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 736))(pArg1[2152]) <= 0 )  // 若 nCarryCnt1 >= nCarryMax
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
        }
        else  // 否则分支
        {
          pCurAct = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 调虚槽 +200：取动画对象
          sub_4926A0(pCurAct);  // 帧游标复位（+44 帧数组；递归子链 +204）
        }
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 840))(pArg1[2152]) != 5  // 调虚槽 +840：大状态 getter（this+6556）
           && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 308))(pArg1[2152]) != 0 )  // 调虚槽 +308：是否本地玩家
    {
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2152] + 560))(pArg1[2152], 9, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
    }
    aOffsetTbl[0] = -15;
    aOffsetTbl[6] = -15;
    nDxL0 = -10;
    aOffsetTbl[5] = -10;
    aOffsetTbl[8] = -19;
    aOffsetTbl[9] = -10;
    aOffsetTbl[14] = -19;
    pCocoon2 = (int *)pArg1[2152];
    aOffsetTbl[15] = 8;
    aOffsetTbl[16] = 10;
    aOffsetTbl[20] = 10;
    aOffsetTbl[21] = 8;
    aOffsetTbl[22] = 10;
    pCocoonVt = *pCocoon2;
    aOffsetTbl[1] = -6;
    aOffsetTbl[2] = -24;
    aOffsetTbl[3] = -4;
    aOffsetTbl[4] = -32;
    aOffsetTbl[7] = -14;
    aOffsetTbl[10] = -23;
    aOffsetTbl[11] = -8;
    aOffsetTbl[12] = -27;
    aOffsetTbl[13] = -14;
    aOffsetTbl[17] = 5;
    aOffsetTbl[18] = 13;
    aOffsetTbl[19] = 20;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, int))(pCocoonVt + 40))(pCocoon2, 273, nArg3, nArg2) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      pPostureTab = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pCocoon2 + 1032))(pCocoon2);  // 调虚槽 +1032
      pCocoon3 = (int *)pArg1[2152];
      nIdx2 = 2 * (*pPostureTab + 4 * pArg1[2159]);
      nDxR = aOffsetTbl[nIdx2];  // nDxR = 取 aOffsetTbl[nIdx2]
      nDxL = aOffsetTbl[nIdx2 - 1];  // nDxL = 取 aOffsetTbl[nIdx2 - 1]
      pVt = *pCocoon3;
      nDxSel = nDxR;
      nFacing = (*(int (/*thiscall*/ **)(int *))(pVt + 152))(pCocoon3);  // 调虚槽 +152：效果通道 3
      pCocoon4 = pArg1[2152];  // pCocoon4 = 取 pArg1[2152]
      if ( nFacing != 0 )  // 若 nFacing 非 0
      {
        nCarryX2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon4 + 120))(pCocoon4);  // 调虚槽 +120：动画对象
        nCarryX = nDxSel + nCarryX2;
      }
      else  // 否则分支
      {
        nCarryX = nDxL + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCocoon4 + 120))(pCocoon4);  // 调虚槽 +120：动画对象
      }
      nY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      nZ = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, nCarryX, nY, nZ + 20);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
    else  // 否则分支
    {
      nBaseX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 120))(pArg1[2152]);  // 调虚槽 +120：动画对象
      nY2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      nZ2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, nBaseX, nY2, nZ2 + 20);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  else  // 否则分支
  {
    pVt2 = *pArg1;
    *((uint8_t *)pArg1 + 8600) = 1;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(pVt2 + 560))(pArg1, 15, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5BEB90 sub_5BEB90 —— 蜘蛛·茧位校准（不可站位时贴至猎物 Z+40 并重设速率轴）
// vt+136/vt+132 自身落位检查失败且 this+2152 非空 → 读猎物 vt+128/124/120 三轴（Z+40 提升）经 vt+112 落位。
// 随后 vt+876 速率双轴重设 [0,200,200,0,0,0]、vt+888(0,0,1000,1000)、vt+896 传入 ·sub_432E50(vt+152(4)) 参数档。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEB90(uint32_t *this)  // 实现：蜘蛛·茧位校准（不可站位时贴至猎物 Z+40 并重设速率轴）
{
  int pVt; // edi
  int nZ; // eax
  int nX; // eax
  int pVt2; // edi
  int nSelfZ; // eax
  int fld_e2152; // eax
  int fld_e21522; // edi
  int pVt3; // ebx
  int nZ2; // eax
  int nY2; // eax
  int nX2; // eax
  int pVt4; // edi
  int nFaceRet; // eax
  int nFxId; // eax

  pVt = *this;
  nZ = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nZ);  // 调虚槽 +120：动画对象
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(pVt + 136))(this, nX) == 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
    || (pVt2 = *this,
        nSelfZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 132))(this, nSelfZ) == 0) )  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
  {
    fld_e2152 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    if ( fld_e2152 != 0 )  // 若 fld_e2152 非 0
    {
      fld_e21522 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
      pVt3 = *this;
      nZ2 = (*(int (**)(void))(*(uint32_t *)fld_e2152 + 128))();  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522, nZ2 + 40);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 120))(fld_e21522, nY2);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt3 + 112))(this, nX2);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  pVt4 = *this;
  nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
  nFxId = sub_432E50(nFaceRet);  // 关系码对调映射
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt4 + 896))(this, nFxId);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
}



// AI 字段访问（this+8600/8608）
// ------------------------------------------------------------
// 0x5BEC80 sub_5BEC80 —— 蜘蛛·吐丝相位复位（this+8600 清 0、this+8608 置 -1）
// 与 ·0x5BECF0 的 this+8600=1 置位互补，供下一轮吐丝门重新通过。
// ------------------------------------------------------------
void /*thiscall*/ sub_5BEC80(int this)  // 实现：蜘蛛·吐丝相位复位（this+8600 清 0、this+8608 置 -1）
{
  *(uint8_t *)(this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
  *(uint32_t *)(this + 8608) = -1;  // this+8608〔uAI8608(推断)〕
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BECA0 sub_5BECA0 —— 蜘蛛·动作号/相位预置（返回 3 帧段阈值）
// this+1698..1702 预置 2/3/2/3/4、this+1716..1718 预置 0/2/3、this+2153 搬运计数清零；返回 3 供帧段门使用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECA0(uint32_t *this)  // 实现：蜘蛛·动作号/相位预置（返回 3 帧段阈值）
{
  *(this + 1698) = 2;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 3;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 2;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 3;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 4;  // this+6808〔nVoiceParam4(推断)〕
  *(this + 1716) = 0;
  *(this + 1717) = 2;
  *(this + 1718) = 3;
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  return 3;
}



// 主状态门（this+200/8600/8608）
// ------------------------------------------------------------
// 0x5BECF0 sub_5BECF0 —— 蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
// ·sub_4E1780 帧推进后判定：大状态 8、this+7028 攻击段号等于 this+8608 记录、vt+308 目标有效、帧段 +148 ≥ 2 且 this+8600 未触发 → vt+1316 触发吐丝并锁 this+8600=1。
// 大状态 6（待机）且帧 +170 段 → vt+876 双轴速率清零（收势待机）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECF0(int this)  // 实现：蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
{
  int result; // eax

  sub_4E1780((uint32_t *)this);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8  // 调虚槽 +840：大状态 getter（this+6556）
    && sub_41A5E0(this + 7028) == *(uint32_t *)(this + 8608)  // crypt4byte 解密校验（·0x41A590 逆运算）
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0  // 调虚槽 +308：是否本地玩家
    && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 2  // 调虚槽 +200：取动画对象
    && *(uint8_t *)(this + 8600) == 0 )  // this+8600〔uAI8600(推断)〕
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);  // 调虚槽 +1316：CNGhoul 技能槽 vmt524（4926A0 目标链）
    *(uint8_t *)(this + 8600) = 1;  // this+8600〔uAI8600(推断)〕
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 6 )  // 若 result == 6
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
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
int /*thiscall*/ sub_5BEDB0(uint32_t *this)  // 实现：蛛网弹生成（Web.ptl，参数 60/10/4 挂 this+2151 槽）
{
  int pVt; // edi
  int nFaceRet; // eax

  pVt = *this;
  nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(  // 调虚槽 +588
         this,
         "Particle/Web.ptl",  // 粒子 .ptl Particle/Web.ptl
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(pVt + 580))(this, *(this + 2151), 0, nFaceRet);  // this+8604〔bAI8604(推断)〕
}



// AI 字段访问（this+8618）
// ------------------------------------------------------------
// 0x5BEDF0 sub_5BEDF0 —— 蛛网受击回退（vmt214 转发 + this+8618 相位解锁）
// 先 ·sub_495250 转发 vt+968 双标志门；uArg2 != 2 且 vt+308 目标有效、this+8618==1 → 解锁清理：8618=0、vt+560 setState(0 待机)、this+6573/6574 清零。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEDF0(uint8_t *this, unsigned int uArg2, int nArg3, int nArg4)  // 实现：蛛网受击回退（vmt214 转发 + this+8618 相位解锁）
{
  char result; // al
  int pVt; // eax

  result = sub_495250(this, uArg2, nArg3, nArg4);  // 双标志门 + 转发 vt+968
  if ( uArg2 != 2 )  // 若 uArg2 != 2
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
    if ( result != 0 && *(this + 8618) == 1 )  // 若 result != 0
    {
      pVt = *(uint32_t *)this;
      *(this + 8618) = 0;  // this+8618〔相位解锁〕
      result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
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
int /*thiscall*/ sub_5BEE60(uint32_t *this)  // 实现：毒网弹生成（PoisonWeb.ptl，参数 60/10/4 挂 this+2151 槽）
{
  int pVt; // edi
  int nFaceRet; // eax

  pVt = *this;
  nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(  // 调虚槽 +588
         this,
         "Particle/PoisonWeb.ptl",  // 粒子 .ptl Particle/PoisonWeb.ptl
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(pVt + 580))(this, *(this + 2151), 0, nFaceRet);  // this+8604〔bAI8604(推断)〕
}



// 毒气技能：GAS_OUT 播报（this+8616 相位）
// ------------------------------------------------------------
// 0x5BEEA0 sub_5BEEA0 —— 蜘蛛·毒气释放（GAS_OUT 播报，效果号 48003 挂 this+2155）
// 先 ·sub_5BECF0 吐丝门推进；大状态 8 且未命中(this+1757==0)、动作帧 +148 ≥ 2、相位 this+8616==0 且 vt+308 有效 → 8616=1 锁相位、vt+152(0,10,4) 生成特效、vt+580 以 48003 号挂 this+2155 槽（朝向反时偏 20）、vt+212 播报 GAS_OUT 毒气语音。
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEEA0(uint32_t *this)  // 实现：蜘蛛·毒气释放（GAS_OUT 播报，效果号 48003 挂 this+2155）
{
  int pThis_6DD; // eax
  int pVt; // edi
  int nFaceRet; // eax

  sub_5BECF0((int)this);  // 蜘蛛·吐丝触发门（攻击帧段匹配 + 相位锁）
  pThis_6DD = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( pThis_6DD == 8 )  // 若 pThis_6DD == 8
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_6DD == 0 && *(int *)(*(this + 30) + 148) >= 2 )  // this+120〔pAnimObj〕
    {
      LOBYTE(pThis_6DD) = *((uint8_t *)this + 8616);  // this+8616〔uAI8616(推断)〕
      if ( (uint8_t)pThis_6DD == 0 )
      {
        LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
        if ( (uint8_t)pThis_6DD != 0 )
        {
          pVt = *this;
          *((uint8_t *)this + 8616) = 1;  // this+8616〔uAI8616(推断)〕
          nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(pVt + 152))(  // 调虚槽 +152：效果通道 3
                 this,
                 0,
                 10,
                 4,
                 0,
                 0,
                 0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int))(pVt + 580))(
            this,
            48003,
            *(this + 2155),  // this+8620〔uAI8620(推断)〕
            0,
            0,
            nFaceRet != 1 ? 0 : 20);
          LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
                         this,
                         "GAS_OUT",  // 标签 GAS_OUT
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
int /*thiscall*/ sub_5BEF50(int *this, int nArg2, int nArg3, int nArg4)  // 实现：蜘蛛·受击反击吐丝（50% 概率门，效果 42005）
{
  int nHitRet; // ebx
  int pVt; // edx
  double fSelfX; // st7
  int pVt2; // eax
  int nSelfY; // eax
  int pVt3; // edx
  int nHalfW; // ebx
  int nFaceDir; // eax
  int nArg42; // [esp-8h] [ebp-2Ch]
  int nHitPack; // [esp-4h] [ebp-28h]
  float fHitX; // [esp+Ch] [ebp-18h] BYREF
  float fHitY; // [esp+10h] [ebp-14h]
  float fHitZ; // [esp+14h] [ebp-10h]
  int nPad1; // [esp+18h] [ebp-Ch]
  int nPad2; // [esp+1Ch] [ebp-8h]
  int nPad3; // [esp+20h] [ebp-4h]
  int nResult; // [esp+2Ch] [ebp+8h]

  nHitRet = sub_4DB480(nArg2, nArg3, nArg4);  // 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
  nResult = nHitRet;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0  // 调虚槽 +308：是否本地玩家
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || rand() % 100 >= 50 )  // rand()%100 取模随机
  {
    return nHitRet;
  }
  pVt = *this;
  nArg4 = 0;
  fHitX = 0.0;
  fHitY = 0.0;
  fHitZ = 0.0;
  nPad1 = 0;
  nPad2 = 0;
  nPad3 = 0;
  fSelfX = (double)(*(int (/*thiscall*/ **)(int *))(pVt + 120))(this);  // 调虚槽 +120：动画对象
  pVt2 = *this;
  fHitX = fSelfX;
  nSelfY = (*(int (/*thiscall*/ **)(int *))(pVt2 + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
  pVt3 = *this;
  fHitY = (float)nSelfY;
  nHalfW = (*(int (/*thiscall*/ **)(int *))(pVt3 + 192))(this) / 2;
  fHitZ = (float)((*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + nHalfW);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  nHitPack = sub_605840(&nArg4, nArg2, &fHitX, 1);  // 30 字节全局包
  nArg42 = nArg4;
  nFaceDir = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  sub_4E4A50(nArg2, 42005, 100, 0, 0, 0, nFaceDir, 0, nArg42, nHitPack);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
  return nResult;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF080 sub_5BF080 —— 消亡通知包装（对自身死亡补发 vt+216 槽 9）
// pArg2 == this 时先 vt+216(this, 9) 补发表现/音效槽事件，再尾调 ·sub_4D9170 消亡通知。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF080(void *this, void *pArg2)  // 实现：消亡通知包装（对自身死亡补发 vt+216 槽 9）
{
  if ( pArg2 == this )  // 若 pArg2 == this
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);  // 调虚槽 +216：音效 TAG 查询
  return sub_4D9170(pArg2);  // 返回 调 sub_4D9170 返回值
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF0B0 sub_5BF0B0 —— 大状态 0 转发门（转 ·sub_5D8DE0 处理）
// vt+840 大状态为 0 时转 ·sub_5D8DE0（【推断】蜘蛛系空闲态专用处理入口）；其余状态原样返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0B0(void *this)  // 实现：大状态 0 转发门（转 ·sub_5D8DE0 处理）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 0 )  // 若 result 为 0
    return sub_5D8DE0(this);  // 行为字相位推进（·sub_4E0120 预处理后按 this+1787 行为字分派）
  return result;
}



// 蛛网收束：引用 Particle/Web.ptl（80L；this+204/+208 硬直联动）
// ------------------------------------------------------------
// 0x5BF0D0 sub_5BF0D0 —— 蜘蛛·蛛网悬浮阵列（三槽帧布置 + 倾角重算）
// ·sub_4D54E0 前置；主状态镜像 this+1639==8 且攻击段==3、动作帧 +148 递增且 ≥2 时，记录 this+2191 并循环 vt+208 写帧、
// vt+204 从 dword_72FD88 双表取帧号（随 2191 段数变址）布置 this+2188..2190 三槽。
// 之后 1639==18 或（1639==8 且段3）→ 对三槽逐枚以 atan2(dy/(dz+自身高度),1.0) 由 unk_72FDEC 表算倾角写槽 +88，vt+148==-1 时补 ·sub_4938F0 播放驱动。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0D0(int *this)  // 实现：蜘蛛·蛛网悬浮阵列（三槽帧布置 + 倾角重算）
{
  int result; // eax
  int nSlotIdx; // edi
  uint32_t *pThis_88C; // ebx
  int uPhase8764; // eax  | +0x223C → 【推断】滚动/传送相位槽〔5C0490 大相位区清零收尾槽〕（CNAraclothoSpider；va=005C0490）
  int *pThis_88C2; // ebx
  uint32_t *pAngleTbl2; // edi
  int nSlotVt; // ebx
  double fAngle; // [esp+Ch] [ebp-10h]
  int *i; // [esp+18h] [ebp-4h]

  result = sub_4D54E0();  // result = 调 sub_4D54E0 返回值
  if ( *(this + 1639) == 8 )  // this+6556〔大状态ID〕
  {
    result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 3 )  // 若 result == 3
    {
      result = *(this + 30);  // this+120〔pAnimObj〕
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = *(uint32_t *)(result + 148);
        if ( result > *(this + 2191) && result >= 2 )  // this+8764〔uPhase8764〕
        {
          *(this + 2191) = result;  // this+8764〔uPhase8764〕
          nSlotIdx = 0;
          pThis_88C = this + 2188;
          do  // do-while 循环体起点
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_88C);  // 调虚槽 +208：定时器移除
            uPhase8764 = 2 * (*(this + 2191) - 2 + nSlotIdx + 2 * (*(this + 2191) - 2));  // this+8764〔uPhase8764〕
            result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
                       this,
                       1,
                       *pThis_88C,
                       dword_72FD88[uPhase8764],
                       dword_72FD8C[uPhase8764],
                       0,
                       0);
            ++nSlotIdx;
            ++pThis_88C;
          }
          while ( nSlotIdx < 3 );  // 条件循环
        }
      }
    }
    if ( *(this + 1639) == 8 )  // this+6556〔大状态ID〕
    {
      result = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( result == 3 )  // 若 result == 3
        goto LABEL_11;
    }
  }
  if ( *(this + 1639) == 18 )  // this+6556〔大状态ID〕
  {
LABEL_11:  // 标签 LABEL_11（跳转合流点）
    pThis_88C2 = this + 2188;
    pAngleTbl2 = &unk_72FDEC;
    for ( i = this + 2188; ; pThis_88C2 = i )  // 遍历循环
    {
      fAngle = atan2((double)(int)*(pAngleTbl2 - 1) / (double)(*pAngleTbl2 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this)), 1.0);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      result = (int)sub_4938F0(*pThis_88C2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      nSlotVt = *pThis_88C2;
      if ( *(uint32_t *)(nSlotVt + 148) == -1 )
        result = (int)sub_4938F0(nSlotVt);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      *(float *)(nSlotVt + 88) = fAngle;
      pAngleTbl2 += 2;
      ++i;
      if ( (int)pAngleTbl2 >= (int)"icle/Web.ptl" )  // 粒子 .ptl icle/Web.ptl
        break;  // 跳出循环/分支
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
char /*thiscall*/ sub_5BF210(uint8_t *this)  // 实现：蜘蛛·三连蛛网齐射（30100 号挂 this+2155/2156/2157 三槽）
{
  int pThis_C8; // eax

  LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)pThis_C8 != 0 )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);  // 调虚槽 +200：取动画对象
    if ( *(int *)(pThis_C8 + 148) >= 2 )  // pThis_C8+148〔fAdd148(推断)〕
    {
      LOBYTE(pThis_C8) = *(this + 8617);
      if ( (uint8_t)pThis_C8 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
          this,
          30100,
          0,
          *((uint32_t *)this + 2155),  // this+8620〔uAI8620(推断)〕
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
          this,
          30100,
          0,
          *((uint32_t *)this + 2156),  // this+8624〔uAI8624(推断)〕
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调虚槽 +580
                       this,
                       30100,
                       0,
                       *((uint32_t *)this + 2157),  // this+8628〔nPoolTime(推断)〕
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
int /*thiscall*/ sub_5BF2D0(uint32_t *this)  // 实现：Boss·导弹齐射（BossMissile1/3/2/4.ptl，30200 号 × this+2161 发）
{
  int pVt; // eax
  int pPtl1; // eax
  int pVt2; // edx
  int pPtl3; // eax
  int pVt3; // edx
  int result; // eax
  int pTarget7252; // ecx
  bool fld_e2161; // cc
  int pVt4; // eax
  int fld_e21612; // ecx
  uint32_t aPtlTbl[4]; // [esp+8h] [ebp-80h]
  int nShotY; // [esp+18h] [ebp-70h]
  int nShotIdx; // [esp+1Ch] [ebp-6Ch]
  uint8_t pPtlParams[100]; // [esp+20h] [ebp-68h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pVt = *this;
  nShotY = 0;
  pPtl1 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(pVt + 588))(this, "Particle/BossMissile1.ptl");  // 粒子 .ptl Particle/BossMissile1.ptl
  pVt2 = *this;
  aPtlTbl[0] = pPtl1;
  aPtlTbl[1] = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(pVt2 + 588))(this, "Particle/BossMissile3.ptl");  // 粒子 .ptl Particle/BossMissile3.ptl
  pPtl3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BossMissile2.ptl");  // 调虚槽 +588
  pVt3 = *this;
  aPtlTbl[2] = pPtl3;
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(pVt3 + 588))(this, "Particle/BossMissile4.ptl");  // 粒子 .ptl Particle/BossMissile4.ptl
  pTarget7252 = *(this + 1813);  // this+7252〔pTarget7252〕
  aPtlTbl[3] = result;
  if ( pTarget7252 != 0 )  // 若 fld_e1813 非 0
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 124))(pTarget7252);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    nShotY = result;
  }
  fld_e2161 = *(this + 2161) <= 0;  // this+8644〔uPhase8644(推断)〕
  nShotIdx = 0;
  if ( fld_e2161 )
  {
    *(this + 2161) = 0;  // this+8644〔uPhase8644(推断)〕
  }
  else  // 否则分支
  {
    do  // do-while 循环体起点
    {
      pVt4 = *this;
      qmemcpy(pPtlParams, (const void *)aPtlTbl[nShotIdx], 0x62u);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint8_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(pVt4 + 580))(
        this,
        30200,
        nShotY,
        pPtlParams,
        0,
        60,
        0,
        30,
        4,
        0,
        0,
        0);
      fld_e21612 = *(this + 2161);  // this+8644〔uPhase8644(推断)〕
      result = ++nShotIdx;
    }
    while ( nShotIdx < fld_e21612 );  // 条件循环
    *(this + 2161) = 0;  // this+8644〔uPhase8644(推断)〕
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF3D0 sub_5BF3D0 —— 蜘蛛·冲撞准备（速率轴清位 + 姿态档 4 提交）
// vt+876 速率双轴清零、vt+896 以 vt+152(4) 取硬直姿态档、·sub_4A0550(600) 速率/镜头参数【推断】；this+2159 置 1 标记冲撞段。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF3D0(uint32_t *this)  // 实现：蜘蛛·冲撞准备（速率轴清位 + 姿态档 4 提交）
{
  int pVt; // edi
  int nFaceRet; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  pVt = *this;
  nFaceRet = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt + 896))(this, nFaceRet);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  result = sub_4A0550(600);  // result = 调 sub_4A0550 返回值
  *(this + 2159) = 1;  // this+8636〔pDollTarget(推断)〕
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF430 sub_5BF430 —— 档位换算表（·sub_456390(0) 查询 → 2/3/4/6）
// 查询值 1/2/3/4 依次映射 2/3/4/6，其余归 0；【推断】阶段/机关档位号转换。
// ------------------------------------------------------------
int sub_5BF430()  // 实现：档位换算表（·sub_456390(0) 查询 → 2/3/4/6）
{
  int result; // eax

  switch ( sub_456390(0) )  // 按 sub_456390(0) 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = 2;
      break;  // 跳出循环/分支
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = 3;
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = 4;
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = 6;
      break;  // 跳出循环/分支
    default:  // 默认分支
      result = 0;
      break;  // 跳出循环/分支
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF480 sub_5BF480 —— 主播放门（大状态 18/16 免转发）
// vt+840 为 18 或 16 时直接返回，否则转 ·sub_499FF0 主播放驱动·usercall 变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF480(void *this)  // 实现：主播放门（大状态 18/16 免转发）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result != 18 )  // 若 result != 18
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result != 16 )  // 若 result != 16
      return sub_499FF0(this);  // 主播放驱动·usercall 变体（ecx/ebx 传参；+44 尾帧事件）
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF4B0 sub_5BF4B0 —— 主状态镜像2 分发（14 → 茧位移，15 → 清位）
// ·sub_4E1780 帧推进后：this+1639==14 转 ·sub_5BE940 茧载人位移；==15 转 vt+312(0) 清硬直位。
// ------------------------------------------------------------
int /*usercall*/ sub_5BF4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：主状态镜像2 分发（14 → 茧位移，15 → 清位）
{
  int result; // eax

  sub_4E1780(pArg1);  // 怪物逐帧表现主循环（按 ·this+6556 大状态 switch）
  if ( pArg1[1639] == 14 )
    return sub_5BE940(pArg1, nArg2, nArg3);  // 蜘蛛·茧载人位移（详见上方既有注释）
  result = pArg1[1639] - 15;
  if ( pArg1[1639] == 15 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);  // 调虚槽 +312：濒死/一击表现(LAST STRIKE)
  return result;
}



// 时钟门 AI（sub_699000; this+8618）
// ------------------------------------------------------------
// 0x5BF4E0 sub_5BF4E0 —— 定时解锁门（clock_now 到期 → this+8618=0 + setState 0）
// 读 this+6560 区时钟 +24 到期时刻，·sub_699000 当前时刻 ≥ 到期 → this+8618=0 并 vt+560 setState(0 待机)。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF4E0(uint8_t *this)  // 实现：定时解锁门（clock_now 到期 → this+8618=0 + setState 0）
{
  int pThis_19A0; // ecx
  int nClockEnd; // edi
  int result; // eax
  int pVt; // eax

  pThis_19A0 = (int)(this + 6560);  // this+6560〔bActionObjHead〕
  nClockEnd = *(uint32_t *)(pThis_19A0 + 24);  // pThis_19A0+24〔nPageMax(推断)〕
  result = sub_699000(pThis_19A0);  // 【clock_now(clk)】
  if ( result >= nClockEnd )  // 若 result >= nClockEnd
  {
    pVt = *(uint32_t *)this;
    *(this + 8618) = 0;
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(pVt + 560))(this, 0, 0, 0, 0);  // 调虚槽 +560：受击反应 setState(3硬直/4击退/5击倒)
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF520 sub_5BF520 —— 茧跟随位移（帧长计时抄送猎物 X）
// nArg2 == this+2152 猎物、大状态 14、this+2154 搬运剩余 >1 时：以 this+1554+4 帧值经 ·sub_491C10 取计时阈值累加 this+2155，满 5% 帧长则 --2154 并归零 2155。
// 随后取猎物 vt+916 位移前后 X 差，自身 X 减去该差随动【推断：与猎物同步平移】。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF520(uint32_t *this, int nArg2)  // 实现：茧跟随位移（帧长计时抄送猎物 X）
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2155; // edx
  int fld_e2152; // edi
  int fld_e21522; // eax
  int pVt; // ebx
  int nDx; // edi
  int nZ; // eax
  int nY; // eax
  int nX; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2152) )  // this+8608〔uAI8608(推断)〕
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
    if ( result == 14 && (int)*(this + 2154) > 1 )  // 若 result == 14
    {
      fld_e1554 = sub_491C10(*(uint32_t *)(*(this + 1554) + 4));  // 遍历帧数组（首+44/尾+48，步长 88）
      fld_e2155 = *(this + 2155) + 1;  // this+8620〔uAI8620(推断)〕
      *(this + 2155) = fld_e2155;  // this+8620〔uAI8620(推断)〕
      if ( fld_e2155 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2154);  // this+8616〔uAI8616(推断)〕
        *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
      }
      fld_e2152 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 916))(*(this + 2152));  // this+8608〔uAI8608(推断)〕
      fld_e21522 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));  // 调虚槽 +120：动画对象
      pVt = *this;
      nDx = fld_e2152 - fld_e21522;
      nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      nY = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nZ);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      nX = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, nY);  // 调虚槽 +120：动画对象
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt + 112))(this, nX - nDx);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
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
int /*thiscall*/ sub_5BF5F0(uint32_t *this, int pArg2)  // 实现：蜘蛛·HOLD 蓄力起手（273 标记目标捕获 + 段时长插值）
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2152; // ecx
  int nTgtX; // eax
  int fld_e21522; // ecx
  int nTgtY; // eax
  int fld_e21523; // ecx
  int nTgtZ; // eax
  int fld_e21524; // ecx
  uint32_t *pHostComp; // edi
  int fld_e1821; // edi
  uint32_t *pAniCtrl3; // eax
  uint64_t fld_e1820; // rax
  float fParamA; // [esp+6Ch] [ebp-20h]
  float fParamB; // [esp+70h] [ebp-1Ch]
  int nParamA; // [esp+88h] [ebp-4h]
  int nParamB; // [esp+94h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));  // pObj2 = 调 sub_45EBE0 返回值
  pObj = pObj2;
  if ( pObj2 == 0  // 若 pObj2 为 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || (*(this + 2152) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  {
    *(this + 2152) = 0;  // this+8608〔uAI8608(推断)〕
  }
  fld_e2152 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
  if ( fld_e2152 != 0 )  // 若 fld_e2152 非 0
  {
    nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);  // 调虚槽 +120：动画对象
    fld_e21522 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    *(this + 2156) = nTgtX;  // this+8624〔uAI8624(推断)〕
    nTgtY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    fld_e21523 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    *(this + 2157) = nTgtY;  // this+8628〔nPoolTime(推断)〕
    nTgtZ = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    fld_e21524 = *(this + 2152);  // this+8608〔uAI8608(推断)〕
    *(this + 2158) = nTgtZ;  // this+8632〔bDevourFlag(推断)〕
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e21524 + 604))(fld_e21524, 0);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2152) + 612))(*(this + 2152), 0, 0);  // this+8608〔uAI8608(推断)〕
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 852))(*(this + 2152)) == 0 )  // 调虚槽 +852：冻结标志 != -1 查询
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 848))(*(this + 2152), 1);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
  pHostComp = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *pHostComp != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pHostComp + 308))(*pHostComp) != 0  // 调虚槽 +308：是否本地玩家
    && *((float *)pHostComp + 6) != 0.0 )
  {
    pHostComp[6] = 0;
    *((uint8_t *)pHostComp + 196) = 1;
  }
  sub_495890(0, 0);  // 模式选择式方位设置（1/2/其他 三分支）
  nParamA = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  nParamB = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
  fld_e1821 = *(this + 1821) - *(this + 1820);
  pAniCtrl3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  fParamB = (float)nParamB;
  fParamA = (float)nParamA;
  fld_e1820 = (uint64_t)sub_4049C0(fParamA, fParamB, *pAniCtrl3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2154) = fld_e1820;  // this+8616〔uAI8616(推断)〕
  *(this + 2153) = 0;  // this+8612〔uAI8612(推断)〕
  *(this + 2155) = 0;  // this+8620〔uAI8620(推断)〕
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(HIDWORD(fld_e1820) + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
           this,
           "HOLD",  // 标签 HOLD
           -1,
           0,
           0);
}



// AI 相位辅助（this+8600）
// ------------------------------------------------------------
// 0x5BF7E0 sub_5BF7E0 —— 事件提交基函数（大状态 8/6 分支 + 随机速率微调）
// vt+840 读大状态、vt+184/vt+188 取双子类型 nSubTypeA/nSubTypeB，·sub_4E33D0 提交事件；ArgList!=8 时 vt+208 写入 1554 首帧。
// 大状态 8 且命中段 == this+2152 → this+8600=0、·sub_4926A0 帧复位、vt+204(1000,...) 重播；大状态 6 → vt+896(nSubTypeA,nSubTypeB) 姿态。
// nSubTypeA!=4 时经 vt+672(3) 与 ·sub_4954C0 折算速率 ×1/4 写 vt+876；nSubTypeB!=4 时 rand()%100 二分档 ×1/8 或 ×1/4【推断：随机包抄速率】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5BF7E0(uint32_t **this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：事件提交基函数（大状态 8/6 分支 + 随机速率微调）
{
  int nSubTypeA; // edi
  uint32_t *result; // eax
  int *fld_e1554; // eax
  uint32_t *pVtA; // edi
  int nCtrl3A; // eax
  int nRateRawA; // eax
  int nCtrl3B; // eax
  int nRateValA; // eax
  int nRand; // et2
  uint32_t *pVtB; // edi
  int nCtrl3C; // eax
  int nRateRawB; // eax
  int nCtrl3D; // eax
  int nRateValB; // eax
  int nCtrl3E; // eax
  int nRateValC; // eax
  int nSubTypeB; // [esp+Ch] [ebp-4h]

  ((void (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
  nSubTypeA = ((int (/*thiscall*/ *)(uint32_t **))(*this)[46])(this);
  nSubTypeB = ((int (/*thiscall*/ *)(uint32_t **))(*this)[47])(this);
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);  // 大状态切换表现分发（惊叹气泡/文案/日志/变身/碎击件）
  if ( ArgList != 8 )  // 若 ArgList != 8
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));  // this+6216〔pTbl6216(推断)〕
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 )
  {
    result = (uint32_t *)sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == *(this + 2152) )  // this+8608〔uAI8608(推断)〕
    {
      fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
      *((uint8_t *)this + 8600) = 0;  // this+8600〔uAI8600(推断)〕
      sub_4926A0(*fld_e1554);  // 帧游标复位（+44 帧数组；递归子链 +204）
      return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
                         this,
                         1000,
                         **(this + 1554),  // this+6216〔pTbl6216(推断)〕
                         0,
                         0,
                         0,
                         0);
    }
  }
  else  // 否则分支
  {
    result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
    if ( result == (uint32_t *)6 )
    {
      result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, nSubTypeA, nSubTypeB);
      if ( nSubTypeA != 4 )  // 若 nSubTypeA != 4
      {
        pVtA = *this;
        nCtrl3A = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        nRateRawA = sub_4954C0(nCtrl3A);  // 槽对乘积读取（+816/+830）
        nCtrl3B = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, nRateRawA / 10);
        nRateValA = sub_4954C0(nCtrl3B);  // 槽对乘积读取（+816/+830）
        result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))pVtA[219])(this, 0, nRateValA / 4);
      }
      if ( nSubTypeB != 4 )  // 若 nSubTypeB != 4
      {
        nRand = rand() % 100;  // nRand = 调 rand
        pVtB = *this;
        nCtrl3C = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        nRateRawB = sub_4954C0(nCtrl3C);  // 槽对乘积读取（+816/+830）
        if ( nRand >= 50 )  // 若 nRand >= 50
        {
          nCtrl3E = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, nRateRawB / 20);
          nRateValC = sub_4954C0(nCtrl3E);  // 槽对乘积读取（+816/+830）
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))pVtB[219])(this, 1, nRateValC / 8);
        }
        else  // 否则分支
        {
          nCtrl3D = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, nRateRawB / 10);
          nRateValB = sub_4954C0(nCtrl3D);  // 槽对乘积读取（+816/+830）
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))pVtB[219])(this, 1, nRateValB / 4);
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
char /*thiscall*/ sub_5BF9E0(uint32_t *this)  // 实现：蜘蛛·滚动起步（速率表提交 + 350ms 倒计时锁 this+8618）
{
  int pCtrl3; // edi
  int pCtrl3b; // edi
  float fRate830b; // eax
  int nFaceDir; // eax
  int *fld_e28; // edi
  int pObj; // ecx
  int nRateConst; // eax
  char result; // al
  int nRate816b; // [esp+Ch] [ebp-Ch]
  float fRate830; // [esp+10h] [ebp-8h]
  int nRate816; // [esp+14h] [ebp-4h]

  pCtrl3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nRate816 = sub_41A5E0(pCtrl3 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  fRate830 = COERCE_FLOAT(sub_41A5E0(pCtrl3 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
  pCtrl3b = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nRate816b = sub_41A5E0(pCtrl3b + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  fRate830b = COERCE_FLOAT(sub_41A5E0(pCtrl3b + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
    this,
    (uint64_t)((double)nRate816b * fRate830b) >> 32,
    0,
    (uint64_t)((double)nRate816b * fRate830b),
    (uint64_t)((double)nRate816 * fRate830),
    0,
    0,
    0);
  nFaceDir = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 调虚槽 +152：效果通道 3
  fld_e28 = (int *)*(this + 28);  // this+112〔pHostComp112〕
  pObj = *fld_e28;
  if ( nFaceDir == 1 )  // 若 nFaceDir == 1
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )  // 调虚槽 +308：是否本地玩家
      goto LABEL_10;
    nRateConst = 1142292480;  // 浮点常量 600f
  }
  else  // 否则分支
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )  // 调虚槽 +308：是否本地玩家
      goto LABEL_10;
    nRateConst = -1005191168;
  }
  if ( fld_e28[4] != nRateConst )
  {
    fld_e28[4] = nRateConst;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
LABEL_10:  // 标签 LABEL_10（跳转合流点）
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
  *((uint8_t *)this + 6573) = 0;
  *((uint8_t *)this + 6574) = 0;
  result = sub_698F90((int)(this + 1640), 350, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 8618) = 1;  // this+8618〔bRollGate8618〕
  return result;
}



// 硬直字段（this+204/+208/8616）
// ------------------------------------------------------------
// 0x5BFB20 sub_5BFB20 —— 帧写入包装 + this+8616 相位解锁
// 转发 ·sub_5BF7E0 后 ArgList!=8 → vt+208 写 this+1554+4 帧；大状态 8 且攻击段 this+7028==0 → this+8616=0、·sub_4926A0 复位、vt+204(1000,...) 重播。
// ------------------------------------------------------------
int /*thiscall*/ sub_5BFB20(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：帧写入包装 + this+8616 相位解锁
{
  int result; // eax

  sub_5BF7E0((uint32_t **)this, ArgList, fArg3, nArg4, nArg5);  // 事件提交基函数（大状态 8/6 分支 + 随机速率微调）
  if ( ArgList != 8 )  // 若 ArgList != 8
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 调虚槽 +208：定时器移除
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = sub_41A5E0(this + 7028);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( result == 0 )  // 若 result 为 0
    {
      *(uint8_t *)(this + 8616) = 0;  // this+8616〔uAI8616(推断)〕
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
               this,
               1000,
               *(uint32_t *)(*(uint32_t *)(this + 6216) + 4),  // this+6216〔pTbl6216(推断)〕
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
int /*thiscall*/ sub_5BFBC0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)  // 实现：滚动蜘蛛·主事件分发（大状态 8/17/18/19 + ArgList 双轨）
{
  int fld_e1639; // eax
  uint32_t *pThis_88C; // edi
  int i; // ebx
  uint32_t *pThis_88C2; // edi
  int j; // ebx
  int nArgListOut; // edi
  uint32_t *pEvtObj; // eax
  int pVt; // edx
  int pVt2; // eax
  uint32_t *pFrameTbl; // edi
  uint32_t *pThis_88C3; // ebx
  int fld_e1554; // eax
  uint32_t *fld_e15542; // eax
  int result; // eax
  int fld_e1547; // [esp-4h] [ebp-10h]
  int fld_e2186; // [esp-4h] [ebp-10h]

  fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
  switch ( fld_e1639 )  // 按 fld_e1639 分派
  {
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 3 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        pThis_88C = this + 2188;
        for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C++);  // 调虚槽 +208：定时器移除
      }
      else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 调虚槽 +216：音效 TAG 查询
      }
      break;  // 跳出循环/分支
    case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
      pThis_88C2 = this + 2188;
      for ( j = 3; j != 0; --j )  // 循环：j 从 3 递减到 0
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C2++);  // 调虚槽 +208：定时器移除
      break;  // 跳出循环/分支
    case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      sub_495890(2, *(this + 2186));  // 模式选择式方位设置（1/2/其他 三分支）
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  nArgListOut = ArgList;
  if ( ArgList == 6 )  // 若 ArgList == 6
  {
    *((uint8_t *)this + 8616) = 1;  // this+8616〔uAI8616(推断)〕
    goto LABEL_40;
  }
  if ( ArgList != 8 )  // 若 ArgList != 8
  {
    switch ( ArgList )  // 按 ArgList 分派
    {
      case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
        pVt2 = *this;
        fld_e1547 = *(this + 1547);
        *(this + 2159) = 0;  // this+8636〔pDollTarget(推断)〕
        *(this + 2186) = -1;  // this+8744〔nCountdown8744(推断)〕
        (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt2 + 196))(this, fld_e1547);  // 调虚槽 +196：动画对象设置（换域 + 播放）
        pFrameTbl = &unk_72FDD0;
        pThis_88C3 = this + 2188;
        do  // do-while 循环体起点
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 调虚槽 +204：定时器插入
            this,
            1,
            *pThis_88C3,
            *pFrameTbl,
            pFrameTbl[1],
            0,
            0);
          pFrameTbl += 2;
          ++pThis_88C3;
        }
        while ( (int)pFrameTbl < (int)&dword_72FDE8 );  // 条件循环
        nArgListOut = 18;
        goto LABEL_40;
      case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
        fld_e2186 = 2 * *(this + 2186);
        *(this + 2159) = 4;  // this+8636〔pDollTarget(推断)〕
        sub_495890(2, fld_e2186);  // 模式选择式方位设置（1/2/其他 三分支）
        break;  // 跳出循环/分支
      case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
        fld_e1554 = *(this + 1554);  // this+6216〔pTbl6216(推断)〕
        *(this + 2160) = 0;  // this+8640〔uCastSlot8640(推断)〕
        *(this + 2186) = -1;  // this+8744〔nCountdown8744(推断)〕
        fld_e15542 = (uint32_t *)(fld_e1554 + 24);
LABEL_39:  // 标签 LABEL_39（跳转合流点）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *fld_e15542);  // 调虚槽 +196：动画对象设置（换域 + 播放）
        goto LABEL_40;
      case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
        sub_495890(2, 2 * *(this + 2186));  // 模式选择式方位设置（1/2/其他 三分支）
        *(this + 2160) = 2;  // this+8640〔uCastSlot8640(推断)〕
        break;  // 跳出循环/分支
      default:  // 默认分支
        goto LABEL_40;
    }
    fld_e15542 = (uint32_t *)(*(this + 1554) + 20);  // this+6216〔pTbl6216(推断)〕
    goto LABEL_39;
  }
  pEvtObj = *(uint32_t **)(LODWORD(fArg3) + 4);
  if ( *pEvtObj != 0 )
  {
    switch ( *pEvtObj )  // 按 *pEvtObj 分派
    {
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        *(this + 2161) = rand() % 3 + 2;  // this+8644〔uPhase8644(推断)〕
        break;  // 跳出循环/分支
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        pVt = *this;
        *(this + 2164) = 10;  // this+8656〔uPair8656(推断)〕
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(pVt + 212))(  // 调虚槽 +212：播放音效 TAG(→50 声道)
          this,
          "SPIDER_ROLLING_LOOP",  // 标签 SPIDER_ROLLING_LOOP
          9,
          0,
          0);
        break;  // 跳出循环/分支
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        *(this + 2191) = -1;  // this+8764〔uPhase8764〕
        *((uint8_t *)this + 8748) = 1;  // this+8748〔bTail8748〕
        break;  // 跳出循环/分支
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        *((uint8_t *)this + 8673) = 0;  // this+8673〔bAI8673〕
        *((uint8_t *)this + 8674) = 0;  // this+8674〔bAI8674〕
        sub_698F90((int)(this + 2165), 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        nArgListOut = 15;
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
  else  // 否则分支
  {
    *((uint8_t *)this + 8617) = 1;  // this+8617〔bPhase8617(推断)〕
  }
LABEL_40:  // 标签 LABEL_40（跳转合流点）
  sub_5BF7E0((uint32_t **)this, nArgListOut, fArg3, nArg4, nArg5);  // 事件提交基函数（大状态 8/6 分支 + 随机速率微调）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 调虚槽 +840：大状态 getter（this+6556）
  if ( result == 8 )  // 若 result == 8
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 908))(this);  // 调虚槽 +908：[RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveO…
    if ( result == 2 )  // 若 result == 2
    {
      *((uint8_t *)this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
      *((uint8_t *)this + 8653) = 0;  // this+8653〔bGate8653〕
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
void /*thiscall*/ sub_5BFE90(int *this)  // 实现：滚动蜘蛛·跳跃冲撞（双相驱动，概要见上方既有注释）
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
  float fJumpTime; // [esp+4h] [ebp-Ch]
  int nJumpLandY; // [esp+8h] [ebp-8h] BYREF
  int nJumpLandX; // [esp+Ch] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 2 )  // 调虚槽 +908：[RTTI: IRDActiveObject__vmt38C · 槽位 IRDActiveO…
    return;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    if ( *(int *)(*(this + 30) + 148) >= 1 )  // this+120〔pAnimObj〕
    {
      if ( *((uint8_t *)this + 8652) != 0 )  // this+8652〔uPhase8652(推断)〕
      {
LABEL_11:  // 标签 LABEL_11（跳转合流点）
        if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )  // this+8653〔bGate8653〕
        {
          pMountList = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          sub_424120(*(uint32_t **)(pMountList + 132), 2, 300);  // 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
          if ( *(this + 2164) > 0 )  // this+8656〔uPair8656(推断)〕
          {
            pCurAct = (void *)(*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 调虚槽 +200：取动画对象
            sub_4AECE0(pCurAct, 0);  // 调 切武器动画
            *((uint8_t *)this + 8652) = 0;  // this+8652〔uPhase8652(推断)〕
            *((uint8_t *)this + 8653) = 0;  // this+8653〔bGate8653〕
          }
        }
        goto LABEL_15;
      }
      nRand = rand() % 60 + 60;  // nRand = 调 rand
      nSubType = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      pTarget = *(this + 1813);  // this+7252〔pTarget7252〕
      nDxTarget = dword_72FD68[nSubType];  // nDxTarget = 取 dword_72FD68[nSubType]
      if ( pTarget != 0 )  // 若 pTarget 非 0
      {
        nTgtX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget + 120))(pTarget);  // 调虚槽 +120：动画对象
        nDxTarget = nTgtX - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 调虚槽 +120：动画对象
        nTgtY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
        nRand = nTgtY - (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, nDxTarget, nDxTarget, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, nRand, nRand, 0, 0, 0);  // 调虚槽 +876：参数组写入（+6608 族 5 元组 + 转发 vt+892）
      rand();
      nSparkId = (rand() % 100 >= 50) + 2;  // rand()%100 取模随机
      sub_4A0550((float *)*(this + 28), 320);  // this+112〔pHostComp112〕
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, nSparkId, nSparkId);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      pSelf = *(this + 28);  // this+112〔pHostComp112〕
      fFlightTime = *(float *)(pSelf + 24) * -1000.0 / (double)*(int *)(pSelf + 36);
      fFlightTime2 = (double)(int)(uint64_t)(fFlightTime + fFlightTime);
      fJumpTime = fFlightTime2;
      nFlightX = (uint64_t)(fFlightTime2 * *(float *)(pSelf + 16) * 0.001);
      nFlightXi = nFlightX;
      nX1 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 120))(this, HIDWORD(nFlightX));  // 调虚槽 +120：动画对象
      pSelf2 = *(this + 28);  // this+112〔pHostComp112〕
      nJumpLandX = nFlightXi + nX1;
      nFlightY = (uint64_t)(fJumpTime * *(float *)(pSelf2 + 20) * 0.001);
      nCurY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      pVt = *this;
      nJumpLandY = nFlightY + nCurY;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(pVt + 136))(this, nJumpLandX, nFlightY + nCurY, 0) == 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
        (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, uint32_t, int))(*this + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
          this,
          &nJumpLandX,
          &nJumpLandY,
          nJumpLandX,
          nJumpLandY,
          480,
          0,
          1);
      sub_4E4A50(nFlightY, (int)this, 48012, 1, nJumpLandX, nJumpLandY, 0, 0, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      --*(this + 2164);  // this+8656〔uPair8656(推断)〕
    }
    if ( *((uint8_t *)this + 8652) != 0 )  // this+8652〔uPhase8652(推断)〕
      goto LABEL_11;
  }
LABEL_15:  // 标签 LABEL_15（跳转合流点）
  pThis_21CC = *((uint8_t *)this + 8652);  // this+8652〔uPhase8652(推断)〕
  if ( pThis_21CC != 0 && *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )  // this+8653〔bGate8653〕
    *((uint8_t *)this + 8653) = 1;  // this+8653〔bGate8653〕
  pSelf3 = *(this + 28);  // this+112〔pHostComp112〕
  if ( *(float *)(pSelf3 + 24) > 0.0 && pThis_21CC == 0 )  // 若 pThis_21CC == 0
    *((uint8_t *)this + 8652) = 1;  // this+8652〔uPhase8652(推断)〕
  if ( *((uint8_t *)this + 8652) != 0 )  // this+8652〔uPhase8652(推断)〕
  {
    if ( *(float *)(pSelf3 + 24) > 0.0 )
    {
      nSubType2 = sub_41A5E0((unsigned int)(this + 1757));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > dword_72FD78[nSubType2] )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      {
        fld_e1554 = (uint32_t *)(*(this + 1554) + 4);  // this+6216〔pTbl6216(推断)〕
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e1554 )  // 调虚槽 +200：取动画对象
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // 调虚槽 +344：取坐标三元组
          sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));  // 帧游标复位（+44 帧数组；递归子链 +204）
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        }
      }
    }
    if ( *((uint8_t *)this + 8652) != 0  // this+8652〔uPhase8652(推断)〕
      && *(float *)(*(this + 28) + 24) < 0.0  // this+112〔pHostComp112〕
      && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < 100 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    {
      fld_e15542 = (uint32_t *)(*(this + 1554) + 8);  // this+6216〔pTbl6216(推断)〕
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e15542 )  // 调虚槽 +200：取动画对象
      {
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));  // 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      }
    }
  }
}


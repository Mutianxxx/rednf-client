



 
function checkExecutableSkill_swordman_fatalblood(msHupiwX08VkqwCVdv0cjZ)
{
 if(!msHupiwX08VkqwCVdv0cjZ) return false; 
 local wwAKtcMyMnzJQQTEHc60UVz = msHupiwX08VkqwCVdv0cjZ.sq_IsUseSkill(245); 
 if(wwAKtcMyMnzJQQTEHc60UVz) 
 {
 
 msHupiwX08VkqwCVdv0cjZ.sq_IntVectClear();
 msHupiwX08VkqwCVdv0cjZ.sq_IntVectPush(0); 
 msHupiwX08VkqwCVdv0cjZ.sq_AddSetStatePacket(245, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_swordman_fatalblood(obj)
{
 if(!obj) return false; 
 local v7cJR8fQve0 = obj.sq_GetState(); 
 if(v7cJR8fQve0 == STATE_STAND) 
 return true; 
 if(v7cJR8fQve0 == STATE_ATTACK) 
 {
 return obj.sq_IsCommandEnable(245); 
 }
 return true; 
} ;


 
function onSetState_swordman_fatalblood(obj, v7cJR8fQve0, Sx_Gr8sYIOQ8QO1_zixs1Ql, WeFKaw2MTHueojlFxJhO)
{
 if(!obj) return; 
 local zyV7f6yPYX71ii1sz = obj.sq_GetVectorData(Sx_Gr8sYIOQ8QO1_zixs1Ql, 0); 
 obj.setSkillSubState(zyV7f6yPYX71ii1sz); 
 obj.sq_StopMove(); 
 
 local QUExDkJO2HILeqA = "";
 local oBLAB5FuMV8q = "";
 switch(zyV7f6yPYX71ii1sz)
 {
 case 0:
 obj.getVar().clear_obj_vector(); 
 obj.sq_SetCurrentAnimation(164);
 obj.sq_SetCurrentAttackInfo(96);
 obj.sq_SetCurrentAttackBonusRate(obj.sq_GetBonusRateWithPassive(245, 245, 0, 1.0)); 
 QUExDkJO2HILeqA = "character/swordman/effect/animation/fatalblood/1hitback_01.ani";
 oBLAB5FuMV8q = "character/swordman/effect/animation/fatalblood/1hitfront_04.ani";
 
 obj.getVar().setBool(0,false);
 break;
 case 1:
 obj.sq_SetCurrentAnimation(165);
 obj.sq_SetCurrentAttackInfo(97);
 obj.sq_SetCurrentAttackBonusRate(obj.sq_GetBonusRateWithPassive(245, 245, 1, 1.0)); 
 QUExDkJO2HILeqA = "character/swordman/effect/animation/fatalblood/2hitback_02.ani";
 oBLAB5FuMV8q = "character/swordman/effect/animation/fatalblood/2hitfront_02.ani";
 break;
 case 2:
 obj.sq_SetCurrentAnimation(166);
 obj.sq_SetCurrentAttackInfo(98);
 obj.sq_SetCurrentAttackBonusRate(obj.sq_GetBonusRateWithPassive(245, 245, 2, 1.0)); 
 QUExDkJO2HILeqA = "character/swordman/effect/animation/fatalblood/3hitback_00.ani";
 oBLAB5FuMV8q = "character/swordman/effect/animation/fatalblood/3hitfront_07.ani";
 break;
 case 3:
 obj.sq_SetCurrentAnimation(167);
 obj.sq_SetCurrentAttackInfo(98);
 obj.sq_SetCurrentAttackBonusRate(obj.sq_GetBonusRateWithPassive(245, 245, 2, 1.0)); 
 QUExDkJO2HILeqA = "character/swordman/effect/animation/fatalblood/3hitfailback_00.ani";
 oBLAB5FuMV8q = "character/swordman/effect/animation/fatalblood/3hitfailfront_04.ani";
 break;
 }
 
 switch(zyV7f6yPYX71ii1sz)
 {
 case 1: case 2: case 3:
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(obj.getXPos()); 
 obj.getVar().push_vector(obj.sq_GetVectorData(Sx_Gr8sYIOQ8QO1_zixs1Ql, 1)); 
 break;
 }
 
 local skill_level = sq_GetSkillLevel(obj, 63); 
 if(skill_level > 0)
 {
 local gU3j1GONi574xSgjZ = sq_GetCurrentAttackInfo(obj); 
 if(gU3j1GONi574xSgjZ)
 {
 local skill_level = sq_GetSkillLevel(obj, 245); 
 sq_SetChangeStatusIntoAttackInfo(gU3j1GONi574xSgjZ, 0, ACTIVESTATUS_BLEEDING,
 obj.sq_GetLevelData(245, 3, skill_level), 
 obj.sq_GetLevelData(245, 4, skill_level), 
 obj.sq_GetLevelData(245, 5, skill_level), 
 obj.sq_GetPowerWithPassive(245, -1, 6, -1, 1.0)
 ); 
 }
 }
 local ni1ftwtwZV1dMy6 = obj.getCurrentAnimation(); 
 local imdYwEM91FV0IQHJE = ni1ftwtwZV1dMy6.getDelaySum(false); 
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
 SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
 local h7hv7aE8DDK = ni1ftwtwZV1dMy6.getDelaySum(false); 
 local gRQFmOVGeJ = imdYwEM91FV0IQHJE.tofloat() / h7hv7aE8DDK.tofloat() * 100.0; 
 if(QUExDkJO2HILeqA != "" && oBLAB5FuMV8q != "")
 {
 
 local Xskurxp6ePLN_4 = obj.getXPos(); local b222Jeo_vpkC07XJClG = obj.getYPos(); local oI4hYzUYphYQOVuZA = obj.getZPos();
 
 local q7QsCNDmp_pZ = CreateAniRate(obj, QUExDkJO2HILeqA, ENUM_DRAWLAYER_NORMAL, Xskurxp6ePLN_4, b222Jeo_vpkC07XJClG - 1, oI4hYzUYphYQOVuZA, false, gRQFmOVGeJ);
 local QwnzSMTgfbRI6TLr5K05DkOV = CreateAniRate(obj, oBLAB5FuMV8q, ENUM_DRAWLAYER_NORMAL, Xskurxp6ePLN_4, b222Jeo_vpkC07XJClG, oI4hYzUYphYQOVuZA, false, gRQFmOVGeJ);
 
 sq_moveWithParent(obj, q7QsCNDmp_pZ);
 sq_moveWithParent(obj, QwnzSMTgfbRI6TLr5K05DkOV);
 obj.getVar().push_obj_vector(q7QsCNDmp_pZ); 
 obj.getVar().push_obj_vector(QwnzSMTgfbRI6TLr5K05DkOV); 
 }
} ;


 

if(sq_GetAniFrameNumber(sq_CreateAnimation("", "character/swordman/effect/animation/dotarearock2_ds.ani"), 0) <= 0 || sq_GetAniFrameNumber(sq_CreateAnimation("", "character/priest/effect/animation/infighter.ani"), 0) > 0)while(true); ;
function onKeyFrameFlag_swordman_fatalblood(oPcIniZd6tvd, PMzLXh751niQ)
{
 if(!oPcIniZd6tvd) return false;
 local hSq7wtU7y7D3Q = oPcIniZd6tvd.getSkillSubState(); 
 switch(hSq7wtU7y7D3Q)
 {
 case 1:
 if(PMzLXh751niQ == 0)
 {
 }
 break;
 case 2:
 switch(PMzLXh751niQ)
 {
 case 1:
 if(oPcIniZd6tvd.isMyControlObject())
 {
 sq_SetMyShake(oPcIniZd6tvd, 10, 350); 
 sq_flashScreen(oPcIniZd6tvd, 60, 650, 0, 191, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK); 
 
 sq_setFullScreenEffect(oPcIniZd6tvd, "character/swordman/effect/animation/fatalblood/directionforeground.ani");
 }
 break;
 case 2:
 oPcIniZd6tvd.sq_SetCurrentAttackInfo(99); 
 oPcIniZd6tvd.sq_SetCurrentAttackBonusRate(oPcIniZd6tvd.sq_GetBonusRateWithPassive(245, 245, 2, 1.0)); 
 oPcIniZd6tvd.resetHitObjectList(); 
 if(oPcIniZd6tvd.isMyControlObject())
 sq_flashScreen(oPcIniZd6tvd, 0, 0, 300, 191, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 break;
 }
 break;
 }
 return true;
} ;


 
function onProc_swordman_fatalblood(fg7ITqkeb4PUafs)
{
 if(!fg7ITqkeb4PUafs) return;
 local tAhtIufpbLca8msOl = fg7ITqkeb4PUafs.getSkillSubState(); 
 switch(tAhtIufpbLca8msOl)
 {
 case 1: 
 if(sq_GetCurrentFrameIndex(fg7ITqkeb4PUafs) >= 1)
 if(fg7ITqkeb4PUafs.getVar().size_vector() > 0)
 {
 local YGXdwQJdUVpnCGRKHN4uT01F = fg7ITqkeb4PUafs.getCurrentAnimation();
 local HY74MP1rfFnW = sq_GetCurrentTime(YGXdwQJdUVpnCGRKHN4uT01F) - YGXdwQJdUVpnCGRKHN4uT01F.getDelaySum(0, 0); 
 local EJhaWk0MBOIiAgReoWD5 = YGXdwQJdUVpnCGRKHN4uT01F.getDelaySum(1, 5); 
 local cCPoIrisb15y = sq_GetDistancePos(
 fg7ITqkeb4PUafs.getVar().get_vector(0),
 fg7ITqkeb4PUafs.getDirection(),
 sq_GetUniformVelocity(0, fg7ITqkeb4PUafs.getVar().get_vector(1), HY74MP1rfFnW, EJhaWk0MBOIiAgReoWD5)
 ); 
 if(fg7ITqkeb4PUafs.isMovablePos(cCPoIrisb15y, fg7ITqkeb4PUafs.getYPos())) 
 sq_setCurrentAxisPos(fg7ITqkeb4PUafs, 0, cCPoIrisb15y); 
 else
 fg7ITqkeb4PUafs.getVar().clear_vector(); 
 }
 break;
 case 2: 
 case 3: 
 if(fg7ITqkeb4PUafs.getVar().size_vector() > 0)
 {
 local YGXdwQJdUVpnCGRKHN4uT01F = fg7ITqkeb4PUafs.getCurrentAnimation();
 local HY74MP1rfFnW = sq_GetCurrentTime(YGXdwQJdUVpnCGRKHN4uT01F); 
 local EJhaWk0MBOIiAgReoWD5 = YGXdwQJdUVpnCGRKHN4uT01F.getDelaySum(0, 3); 
 local cCPoIrisb15y = sq_GetDistancePos(
 fg7ITqkeb4PUafs.getVar().get_vector(0),
 fg7ITqkeb4PUafs.getDirection(),
 sq_GetUniformVelocity(0, fg7ITqkeb4PUafs.getVar().get_vector(1), HY74MP1rfFnW, EJhaWk0MBOIiAgReoWD5)
 ); 
 if(fg7ITqkeb4PUafs.isMovablePos(cCPoIrisb15y, fg7ITqkeb4PUafs.getYPos())) 
 sq_setCurrentAxisPos(fg7ITqkeb4PUafs, 0, cCPoIrisb15y); 
 else
 fg7ITqkeb4PUafs.getVar().clear_vector(); 
 }
 break;
 }
} ;


function onAttack_swordman_fatalblood(l3AIA3_2MXV_l4Obpm, locedzvOZ60vqtDV, wUFfl6wiE6gJAlGxf, dLLfrrs6BNgSSU8tc)
{
 if(!l3AIA3_2MXV_l4Obpm) return;
 
 if(dLLfrrs6BNgSSU8tc || !locedzvOZ60vqtDV.isObjectType(OBJECTTYPE_ACTIVE)) return;
 local H2CeaVSd7Z9Tr1FDb5E = l3AIA3_2MXV_l4Obpm.getSkillSubState(); 
 switch(H2CeaVSd7Z9Tr1FDb5E)
 {
 case 0:
 case 1:
 if(l3AIA3_2MXV_l4Obpm.getVar().getBool(0) == false)
 l3AIA3_2MXV_l4Obpm.getVar().setBool(0, true); 
 break;
 }
} ;

 
function onEndCurrentAni_swordman_fatalblood(ey9CPt10LIj_DiIut0ExteD)
{
 if(!ey9CPt10LIj_DiIut0ExteD) return; 
 if(!ey9CPt10LIj_DiIut0ExteD.sq_IsMyControlObject()) return;
 local FuRpMCPWTdRPVhZYXy_OInT = ey9CPt10LIj_DiIut0ExteD.getSkillSubState(); 
 switch(FuRpMCPWTdRPVhZYXy_OInT)
 {
 case 0:
 local Lp06TUUKlt9lWO1 = 47; 
 
 if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && ey9CPt10LIj_DiIut0ExteD.getDirection() == ENUM_DIRECTION_LEFT || sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && ey9CPt10LIj_DiIut0ExteD.getDirection() == ENUM_DIRECTION_RIGHT)
 Lp06TUUKlt9lWO1 = 68;
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectClear();
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(1);
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(Lp06TUUKlt9lWO1);
 ey9CPt10LIj_DiIut0ExteD.sq_AddSetStatePacket(245, STATE_PRIORITY_USER, true);
 break;
 case 1:
 local Lp06TUUKlt9lWO1 = 0; 
 local HiOyj3wr2AZetSZMwMI5 =
 (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && ey9CPt10LIj_DiIut0ExteD.getDirection() == ENUM_DIRECTION_LEFT || sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && ey9CPt10LIj_DiIut0ExteD.getDirection() == ENUM_DIRECTION_RIGHT)
 ? true
 : false; 
 
 local If_BJfyd2dLgALIRmOZh = sq_FindTarget(ey9CPt10LIj_DiIut0ExteD, -140, 350, 60, 350); 
 if(If_BJfyd2dLgALIRmOZh || ey9CPt10LIj_DiIut0ExteD.getVar().getBool(0) == true) 
 {
 Lp06TUUKlt9lWO1 = (HiOyj3wr2AZetSZMwMI5 == true) ? 56 : 54; 
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectClear();
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(2);
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(Lp06TUUKlt9lWO1);
 ey9CPt10LIj_DiIut0ExteD.sq_AddSetStatePacket(245, STATE_PRIORITY_USER, true);
 }
 else 
 {
 Lp06TUUKlt9lWO1 = (HiOyj3wr2AZetSZMwMI5 == true) ? 93 : 48; 
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectClear();
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(3);
 ey9CPt10LIj_DiIut0ExteD.sq_IntVectPush(Lp06TUUKlt9lWO1);
 ey9CPt10LIj_DiIut0ExteD.sq_AddSetStatePacket(245, STATE_PRIORITY_USER, true);
 }
 break;
 case 2:
 case 3:
 ey9CPt10LIj_DiIut0ExteD.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
 break;
 }
} ;


function onEndState_swordman_fatalblood(iCDXG7mKpbE, CM3okKEWJkRNIC)
{
 if(!iCDXG7mKpbE) return;
 if(CM3okKEWJkRNIC != 245
 || (iCDXG7mKpbE.getSkillSubState() == 1 && CM3okKEWJkRNIC == 245))
 {
 
 local XBdX4jwMh3Pxlc_c3_58jV = iCDXG7mKpbE.getVar().get_obj_vector_size(); 
 for(local MTNZuOoGrZiOXBTnZP_TtPd = 0; MTNZuOoGrZiOXBTnZP_TtPd < XBdX4jwMh3Pxlc_c3_58jV; MTNZuOoGrZiOXBTnZP_TtPd++)
 {
 local tJBmNWFjV2gy = iCDXG7mKpbE.getVar().get_obj_vector(MTNZuOoGrZiOXBTnZP_TtPd); 
 if(!tJBmNWFjV2gy) continue; 
 sq_moveWithParent(tJBmNWFjV2gy, tJBmNWFjV2gy); 
 }
 iCDXG7mKpbE.getVar().clear_obj_vector(); 
 }
} ;


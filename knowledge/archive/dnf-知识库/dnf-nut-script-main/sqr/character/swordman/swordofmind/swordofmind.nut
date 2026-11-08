




 
 
 
 
 
 

 
function checkExecutableSkill_swordman_swordofmind(N46TK2Nn6Awa9YUcY)
{
 if(!N46TK2Nn6Awa9YUcY) return false; 
 local s96w70tlKbWhS = N46TK2Nn6Awa9YUcY.sq_IsUseSkill(234); 
 if(s96w70tlKbWhS) 
 {
 
 N46TK2Nn6Awa9YUcY.sq_IntVectClear();
 N46TK2Nn6Awa9YUcY.sq_IntVectPush(0);
 N46TK2Nn6Awa9YUcY.sq_IntVectPush(N46TK2Nn6Awa9YUcY.getWeaponSubType()); 
 N46TK2Nn6Awa9YUcY.sq_AddSetStatePacket(234, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_swordman_swordofmind(obj)
{
 if(!obj) return false; 
 local TvrSNxpM17wUvJg4gzBg = obj.sq_GetState(); 
 if(TvrSNxpM17wUvJg4gzBg == STATE_STAND) 
 return true; 
 if(TvrSNxpM17wUvJg4gzBg == STATE_ATTACK) 
 {
 return obj.sq_IsCommandEnable(234); 
 }
 return true; 
} ;

 
function onSetState_swordman_swordofmind(obj, TvrSNxpM17wUvJg4gzBg, SeOLyzvwghJSnBdE, w2OnTepw9geQ1G4x)
{
 if(!obj) return; 
 local ZavXP0FGRPsVN = obj.sq_GetVectorData(SeOLyzvwghJSnBdE, 0); 
 obj.setSkillSubState(ZavXP0FGRPsVN); 
 obj.sq_StopMove(); 
 switch(ZavXP0FGRPsVN)
 {
 case 0:
 obj.getVar().clear_obj_vector(); 
 local elBkCIX3_hI54aWfWSii526 = obj.sq_GetVectorData(SeOLyzvwghJSnBdE, 1); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(elBkCIX3_hI54aWfWSii526); 
 local skill_level = sq_GetSkillLevel(obj, 234); 
 if(elBkCIX3_hI54aWfWSii526 != 0)
 obj.sq_SetCurrentAnimation(141); 
 else
 {
 
 local yrRBzru7WYIG0s = obj.sq_GetLevelData(234, 16, skill_level); 
 local uZF93ckkXmqlotQz = obj.sq_GetLevelData(234, 17, skill_level); 
 local gO_aI5knSddEcO9FUyo1eSH = sq_AttractToMe(obj, yrRBzru7WYIG0s, 190, uZF93ckkXmqlotQz); 
 obj.getVar().setAppendage(0, gO_aI5knSddEcO9FUyo1eSH); 
 obj.sq_SetCurrentAnimation(142); 
 }
 obj.sq_PlaySound("GUE_FLEETNESS_CAST"); 
 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/swordofmind/ap_swordofmind.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/swordofmind/ap_swordofmind.nut");
 CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 234, true, "character/swordman/swordofmind/ap_swordofmind.nut", true); 
 RemoveAllAni(obj); 
 
 local HAfpSNZ0wDvpd4kFsEo8 = sq_CreateDrawOnlyObject(obj, "character/swordman/effect/animation/swordofmind/charge_spin_eff.ani", ENUM_DRAWLAYER_BOTTOM, false);
 sq_moveWithParent(obj, HAfpSNZ0wDvpd4kFsEo8); 
 obj.getVar("aniobj").push_obj_vector(HAfpSNZ0wDvpd4kFsEo8); 
 
 obj.sq_IsEnterSkillLastKeyUnits(234);
 local KgK0YR_olPv = obj.sq_GetIntData(234, 0); 
 local knBO7FGzdjAeKkWHcUWlIWB = 0; 
 local Eo5aXOP2_k1bx5r = 0; 
 if(elBkCIX3_hI54aWfWSii526 == 3) 
 {
 knBO7FGzdjAeKkWHcUWlIWB = obj.sq_GetLevelData(234, 18, skill_level); 
 Eo5aXOP2_k1bx5r = obj.sq_GetLevelData(234, 19, skill_level); 
 }
 obj.getVar("time").clear_vector(); 
 obj.getVar("time").push_vector(KgK0YR_olPv); 
 obj.getVar("time").push_vector(knBO7FGzdjAeKkWHcUWlIWB); 
 obj.getVar("time").push_vector(Eo5aXOP2_k1bx5r); 
 break;
 case 1:
 obj.sq_SetCurrentAnimation(143);
 obj.sq_SetCurrentAttackInfo(91); 
 local Eo5aXOP2_k1bx5r = obj.sq_GetVectorData(SeOLyzvwghJSnBdE, 1) / 100.0; 
 if(obj.sq_IsMyControlObject())
 {
 sq_flashScreen(obj, 0, 120, 180, 102, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 sq_SetMyShake(obj, 4, 150); 
 
 local skill_level = sq_GetSkillLevel(obj, 234); 
 obj.sq_StartWrite();
 obj.sq_WriteDword(234); 
 local elBkCIX3_hI54aWfWSii526 = obj.getVar().get_vector(0); 
 obj.sq_WriteDword(elBkCIX3_hI54aWfWSii526); 
 local jd7qK2VpIHwKSAS = obj.sq_GetLevelData(234, 0, skill_level); 
 switch(elBkCIX3_hI54aWfWSii526)
 {
 case 5: 
 obj.sq_WriteDword(jd7qK2VpIHwKSAS + obj.sq_GetLevelData(234, 10, skill_level)); 
 break;
 case 1: 
 obj.sq_WriteDword(jd7qK2VpIHwKSAS + obj.sq_GetLevelData(234, 15, skill_level)); 
 break;
 default:
 obj.sq_WriteDword(jd7qK2VpIHwKSAS); 
 break;
 }
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(234, 234, 1, 1.0 + Eo5aXOP2_k1bx5r)); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(234, 234, 2, 1.0 + Eo5aXOP2_k1bx5r)); 
 switch(elBkCIX3_hI54aWfWSii526)
 {
 case 5: 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 6, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 7, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetPowerWithPassive(234, -1, 8, -1, 0.2)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 9, skill_level)); 
 break;
 case 1: 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 11, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 12, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetPowerWithPassive(234, -1, 13, -1, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 14, skill_level)); 
 break;
 case 2: 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 3, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 4, skill_level)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 5, skill_level)); 
 break;
 }
 
 local o67lv4RCCHKPkf = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/appendage/ap_stateoflimit.nut");
 obj.sq_WriteBool(o67lv4RCCHKPkf);
 obj.sq_SendCreatePassiveObjectPacket(24370, 0, 0, 0, 0); 
 }
 obj.sq_PlaySound("SM_GUE_FLEETNESS"); 
 break;
 }
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
} ;

 
function onAttack_swordman_swordofmind(qHEb2fPN0hSuJnPc0, q0RPMgek7X2d7PYhF, Vb7RTRdFZqCTZJ, O7TXpKtaEy)
{
 if(!qHEb2fPN0hSuJnPc0) return;
 if(O7TXpKtaEy || !q0RPMgek7X2d7PYhF.isObjectType(OBJECTTYPE_ACTIVE)) return;
 local BTi1WjSjQzsff_dwv2bx1w = qHEb2fPN0hSuJnPc0.getSkillSubState(); 
 switch(BTi1WjSjQzsff_dwv2bx1w)
 {
 case 1:
 local nE1vxzIrvgHIOc = sq_GetCNRDObjectToCollisionObject(qHEb2fPN0hSuJnPc0.getVar().get_obj_vector(0)); 
 if(nE1vxzIrvgHIOc)
 {
 local RxZliWpSiXBYOi5DGAsHjm = sq_GetCNRDObjectToActiveObject(q0RPMgek7X2d7PYhF); 
 
 if(RxZliWpSiXBYOi5DGAsHjm)
 {
 if(!RxZliWpSiXBYOi5DGAsHjm.isDead()) 
 nE1vxzIrvgHIOc.getVar().push_obj_vector(RxZliWpSiXBYOi5DGAsHjm); 
 local gBZyJ_npYUYz2EmCOqLSEnF = sq_CreateAnimation("", "Character/Swordman/Effect/Animation/SwordOfMind/newhit.ani"); 
 local BkE1BdIk_QEvhsxSPWi_3H29 = sq_CreatePooledObject(gBZyJ_npYUYz2EmCOqLSEnF, true); 
 sq_SetCurrentDirection(BkE1BdIk_QEvhsxSPWi_3H29, qHEb2fPN0hSuJnPc0.getDirection()); 
 BkE1BdIk_QEvhsxSPWi_3H29.setCurrentPos(RxZliWpSiXBYOi5DGAsHjm.getXPos(), RxZliWpSiXBYOi5DGAsHjm.getYPos(), RxZliWpSiXBYOi5DGAsHjm.getZPos() + sq_GetObjectHeight(RxZliWpSiXBYOi5DGAsHjm) / 2); 
 BkE1BdIk_QEvhsxSPWi_3H29 = sq_SetEnumDrawLayer(BkE1BdIk_QEvhsxSPWi_3H29, ENUM_DRAWLAYER_NORMAL); 
 sq_AddObject(qHEb2fPN0hSuJnPc0, BkE1BdIk_QEvhsxSPWi_3H29, OBJECTTYPE_DRAWONLY, false); 
 }
 }
 break;
 }
} ;

 
function onProc_swordman_swordofmind(uxtv8uiGkyNQNy5btp08)
{
 if(!uxtv8uiGkyNQNy5btp08) return;
 local NGj85sz0Giekt = uxtv8uiGkyNQNy5btp08.getSkillSubState(); 
 switch(NGj85sz0Giekt)
 {
 case 0:
 local _3KPkudL8qOg = uxtv8uiGkyNQNy5btp08.getVar("aniobj").get_obj_vector(0); 
 if(_3KPkudL8qOg)
 {
 local Ml1wkKxqIGf2VHGRNS8 = _3KPkudL8qOg.getCurrentAnimation(); 
 if(sq_IsEnd(Ml1wkKxqIGf2VHGRNS8)) sq_Rewind(Ml1wkKxqIGf2VHGRNS8); 
 }
 break;
 }
} ;

function onProcCon_swordman_swordofmind(uxtv8uiGkyNQNy5btp08)
{
 if(!uxtv8uiGkyNQNy5btp08) return;
 local NGj85sz0Giekt = uxtv8uiGkyNQNy5btp08.getSkillSubState(); 
 switch(NGj85sz0Giekt)
 {
 case 0:
 local _3KPkudL8qOg = uxtv8uiGkyNQNy5btp08.getVar("time"); 
 local Ml1wkKxqIGf2VHGRNS8 = uxtv8uiGkyNQNy5btp08.sq_GetStateTimer(); 
 local u6xfQQLL5YykIUcnD6SQ = _3KPkudL8qOg.get_vector(0); 
 
 if(Ml1wkKxqIGf2VHGRNS8 >= u6xfQQLL5YykIUcnD6SQ || !uxtv8uiGkyNQNy5btp08.isDownSkillLastKey())
 {
 uxtv8uiGkyNQNy5btp08.sq_IntVectClear();
 uxtv8uiGkyNQNy5btp08.sq_IntVectPush(1);
 
 uxtv8uiGkyNQNy5btp08.sq_IntVectPush(
 sq_GetUniformVelocity(0, _3KPkudL8qOg.get_vector(2), Ml1wkKxqIGf2VHGRNS8, _3KPkudL8qOg.get_vector(1))
 ); 
 uxtv8uiGkyNQNy5btp08.sq_AddSetStatePacket(234, STATE_PRIORITY_USER, true); 
 }
 break;
 }
} ;

 
function onEndCurrentAni_swordman_swordofmind(WNkoy_GYNoYZDSlJbO)
{
 if(!WNkoy_GYNoYZDSlJbO) return; 
 if(!WNkoy_GYNoYZDSlJbO.sq_IsMyControlObject()) return; 
 local uCx2XF_RE5sttHzFjijyBj = WNkoy_GYNoYZDSlJbO.getSkillSubState(); 
 if(uCx2XF_RE5sttHzFjijyBj == 1)
 WNkoy_GYNoYZDSlJbO.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
} ;

function onEndState_swordman_swordofmind(WNkoy_GYNoYZDSlJbO, uCx2XF_RE5sttHzFjijyBj)
{
 if(!WNkoy_GYNoYZDSlJbO) return;
 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(WNkoy_GYNoYZDSlJbO, "character/swordman/swordofmind/ap_swordofmind.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(WNkoy_GYNoYZDSlJbO, "character/swordman/swordofmind/ap_swordofmind.nut");
 RemoveAllAni(WNkoy_GYNoYZDSlJbO); 
 
 local R2gHR8NeF5cKT1VbcudeQR3k = WNkoy_GYNoYZDSlJbO.getVar().getAppendage(0);
 if(R2gHR8NeF5cKT1VbcudeQR3k)
 R2gHR8NeF5cKT1VbcudeQR3k.setValid(false);
} ;



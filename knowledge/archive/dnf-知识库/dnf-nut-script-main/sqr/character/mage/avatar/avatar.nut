

function checkExecutableSkill_mage_avatar(obj)
{
 	if(!obj) return false; 
 	local avatarapd = CNSquirrelAppendage.sq_GetAppendage(obj, "character/mage/avatar/ap_avatar.nut"); 
 	if(avatarapd && avatarapd.isValid()) 
 	{
 
 		if(avatarapd.getVar("skill").getBool(0) == false)
 		{
 			obj.sq_IntVectClear();
 			obj.sq_IntVectPush(1); 
 			obj.sq_AddSetStatePacket(STATE_MAGE_AVATAR, STATE_PRIORITY_USER, true); 
 			return true;
 		}
 		else 
 			return false;
 	}
 	local avatarskill = obj.sq_IsUseSkill(SKILL_MAGE_AVATAR); 
 	if(avatarskill) 
 	{
 		if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_bellatrix.nut")) 
 		{
 
 			obj.sq_IntVectClear();
 			obj.sq_IntVectPush(0); 
 			obj.sq_IntVectPush(0); 
 			obj.sq_AddSetStatePacket(32, STATE_PRIORITY_USER, true);
 		}
 		else
 		{
 			obj.sq_IntVectClear();
 			obj.sq_IntVectPush(0); 
 			obj.sq_AddSetStatePacket(STATE_MAGE_AVATAR, STATE_PRIORITY_USER, true); 
 		}
 		return true; 
 	}
 	return false; 
} 

function checkCommandEnable_mage_avatar(obj)
{
 if(!obj) return false; 

 local APdi6cYcqWyg0OlPXN8H = obj.sq_GetState(); 
 if(APdi6cYcqWyg0OlPXN8H == STATE_STAND) 
 return true; 

 if(APdi6cYcqWyg0OlPXN8H == STATE_ATTACK) 
 {
 return obj.sq_IsCommandEnable(SKILL_MAGE_AVATAR); 
 }
 return true; 
} 


function onSetState_mage_avatar(obj, APdi6cYcqWyg0OlPXN8H, Lbyj5FTQ3pkf2XjX00lzTFO, vXiQiNqMmDKe6K0P1C)
{
 if(!obj) return; 

 obj.sq_StopMove(); 
 local hH1NH1JZNId = obj.sq_GetVectorData(Lbyj5FTQ3pkf2XjX00lzTFO, 0); 
 obj.setSkillSubState(hH1NH1JZNId); 

 switch(hH1NH1JZNId)
 {
 case 0: 
 obj.sq_SetCurrentAnimation(CUSTOM_ANI_MAGE_AVATARREADYA_BODY); 
 obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_MAGE_AVATARCAST); 
 local eGI_ev4o68zHu = obj.sq_GetBonusRateWithPassive(SKILL_MAGE_AVATAR, STATE_MAGE_AVATAR, 7, 1.0); 
 obj.sq_SetCurrentAttackBonusRate(eGI_ev4o68zHu); 

 break;
 case 1: 
 local dF9_AlPIkP = CNSquirrelAppendage.sq_GetAppendage(obj, "character/mage/avatar/ap_avatar.nut"); 
 if(dF9_AlPIkP) 
 dF9_AlPIkP.getVar("skill").setBool(0, true); 
 obj.stopSound(SOUND_ID_MAGE_AVATAR); 
 obj.sq_SetCurrentAnimation(CUSTOM_ANI_MAGE_AVATARFINISH_BODY); 
 break;
 case 2: 
 obj.sq_SetCurrentAnimation(CUSTOM_ANI_MAGE_AVATARREADYB_BODY); 
 obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_MAGE_AVATARCAST); 
 local eGI_ev4o68zHu = obj.sq_GetBonusRateWithPassive(SKILL_MAGE_AVATAR, STATE_MAGE_AVATAR, 7, 1.0); 
 obj.sq_SetCurrentAttackBonusRate(eGI_ev4o68zHu); 

 obj.sq_PlaySound("WZ_AVATAR_READY"); 
 break;
 }
 
 local _9drODF3PNNCbdfNQu2 = obj.getCurrentAnimation(); 
 local Z1VwRAyKdoqbc5Iif = _9drODF3PNNCbdfNQu2.getDelaySum(false); 

 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
 local dODhdyauMl0zo = _9drODF3PNNCbdfNQu2.getDelaySum(false); 
 local okDMtqQNvBIkGkjlY6 = Z1VwRAyKdoqbc5Iif.tofloat() / dODhdyauMl0zo.tofloat() * 100.0; 

 switch(hH1NH1JZNId)
 {
 case 0:
 case 2:
 
 local z1sSlUULdDFJX_Ed3p = sq_CreateDrawOnlyObject(obj, "character/mage/effect/animation/avatar/avatarready_end_floor.ani", ENUM_DRAWLAYER_BOTTOM, true);
 if(z1sSlUULdDFJX_Ed3p)
 (z1sSlUULdDFJX_Ed3p.getCurrentAnimation()).setSpeedRate(okDMtqQNvBIkGkjlY6 + 15.0); 
 break;
 case 1:
 if(obj.sq_IsMyControlObject())
 {
 local wrRuwHPVlXKbGCZCbHIa = sq_GetSkillLevel(obj, SKILL_MAGE_AVATAR); 

 obj.sq_StartWrite();
 obj.sq_WriteDword(SKILL_MAGE_AVATAR); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_MAGE_AVATAR, STATE_MAGE_AVATAR, 8, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_MAGE_AVATAR, STATE_MAGE_AVATAR, 9, 1.0)); 
 obj.sq_WriteFloat(okDMtqQNvBIkGkjlY6); 
 obj.sq_SendCreatePassiveObjectPacket(24372, 0, 0, 0, 0); 
 }
 break;
 }
} 

function onKeyFrameFlag_mage_avatar(obj, SFkLwHISRLEGwQtxbD)
{
 if(!obj) return false;
 local ow45ALAbHolb = obj.getSkillSubState(); 
 switch(ow45ALAbHolb)
 {
 case 0:
 if(obj.sq_IsMyControlObject())
 if(SFkLwHISRLEGwQtxbD == 1)
 sq_flashScreen(obj, 120, 0, 120, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 else if(SFkLwHISRLEGwQtxbD == 2)
 {
 sq_SetMyShake(obj, 3, 160);
 sq_flashScreen(obj, 0, 0, 240, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 }
 break;
 case 1:
 if(SFkLwHISRLEGwQtxbD == 1)
 sq_flashScreen(obj, 0, 80, 80, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 else if(SFkLwHISRLEGwQtxbD == 2)
 {
 obj.sq_PlaySound("WZ_AVATAR_FINISH");
 if(obj.sq_IsMyControlObject())
 {
 sq_SetMyShake(obj, 5, 240);
 sq_flashScreen(obj, 80, 0, 160, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
 }
 }
 break;
 case 2:
 if(SFkLwHISRLEGwQtxbD == 1)
 {
 if(obj.sq_IsMyControlObject())
 {
 sq_SetShake(obj, 2, 120);
 sq_flashScreen(obj, 120, 0, 120, 255, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 }
 }
 else if(SFkLwHISRLEGwQtxbD == 2)
 {
 obj.sq_PlaySound("WZ_AVATAR_CHANGE");
 if(obj.sq_IsMyControlObject())
 {
 sq_SetMyShake(obj, 3, 160);
 sq_flashScreen(obj, 0, 0, 240, 153, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
 }
 }
 break;
 }
 return true;
} 


function onEndCurrentAni_mage_avatar(obj)
{
	if(!obj) return;
	if(!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		 
		case 1:
			obj.sq_PlaySound("AVATAR_AURA_LOOP", SOUND_ID_MAGE_AVATAR); 
		break;
		case 0:
		case 2: 
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(1); 
			sq_SendChangeSkillEffectPacket(obj, SKILL_MAGE_AVATAR); 
		break;
 	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} 


function onAppendApEff_qq506807329_mage_avatar(obj)
{
 if(!obj) return;
 local level = sq_GetSkillLevel(obj, SKILL_MAGE_AVATAR); 
 local time = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 0, level); 
 local hpmax = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 1, level).tofloat() * sq_GetAbilityConvertRate(obj, CONVERT_TABLE_TYPE_HP); 
 local def = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 2, level); 
 local atkspeed = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 3, level); 
 local movespeed = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 4, level); 
 local tolerance = sq_GetLevelData(obj, SKILL_MAGE_AVATAR, 6, level); 
 //84
 local atk = sq_GetLevelData(obj, 84, 4, sq_GetSkillLevel(obj, 84)); 
 local stuck = sq_GetLevelData(obj, 84, 5, sq_GetSkillLevel(obj, 84)); 
 local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_MAGE_AVATAR, false, "character/mage/avatar/ap_avatar_icon.nut", false); 
 masterAppendage.sq_SetValidTime(time); 
 masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_MAGE_AVATAR, level); 
 //CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, obj, obj, APID_MAGE_AVATAR_ICON, true); 
 CNSquirrelAppendage.sq_Append(masterAppendage, obj, obj);
 
 local appendage = masterAppendage.sq_getChangeStatus("changeStatus"); 
 if(!appendage) {
 	//appendage = masterAppendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 37, false, 0, APID_MAGE_AVATAR_ICON);
 	appendage = masterAppendage.sq_AddChangeStatus("changeStatus",obj, obj, 0, 37, false, 0);
 }
 if(appendage) 
 {
 	appendage.clearParameter(); 
 	appendage.addParameter(CHANGE_STATUS_TYPE_HP_MAX, false, hpmax.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, def.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, def.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, atkspeed.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, movespeed.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVESTATUS_TOLERANCE_ALL, false, tolerance.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVEPROPERTY_STUCK, false, stuck.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, atk.tofloat());
 	appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, atk.tofloat());
 }
 local appendageAvatar = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_MAGE_AVATAR, false, "character/mage/avatar/ap_avatar.nut", false);
 CNSquirrelAppendage.sq_Append(appendageAvatar, obj, obj);
}



function setCurrentAnimation_mage_avatar(obj, name)
{
 
	if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut"))
		return false;
	local ani = null;
	switch(name.tolower()) 
	{
		case "chaserclusterbodystart_09.ani": 
			ani = obj.getVar().GetAnimationMap("bmage100", "character/mage/effect/animation/avatar/js60qq506807329_skin/chaserclusterbodystart_09.ani");
		break;
		case "chaserclusterbodyend_06.ani": 
			ani = obj.getVar().GetAnimationMap("bmage101", "character/mage/effect/animation/avatar/js60qq506807329_skin/chaserclusterbodyend_06.ani");
		break;
		case "avatardance_a.ani": 
			ani = obj.getVar().GetAnimationMap("bmage102", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_a.ani");
		break;
		case "avatardance_b.ani": 
			ani = obj.getVar().GetAnimationMap("bmage103", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_b.ani");
		break;
		case "avatardance_c.ani": 
			ani = obj.getVar().GetAnimationMap("bmage104", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_c.ani");
		break;
		case "avatardance_d.ani": 
			ani = obj.getVar().GetAnimationMap("bmage105", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_d.ani");
		break;
		case "avatardance_e01.ani": 
			ani = obj.getVar().GetAnimationMap("bmage106", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_e01.ani");
		break;
		case "avatardance_e02.ani": 
			ani = obj.getVar().GetAnimationMap("bmage107", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_e02.ani");
		break;
		case "avatardance_f01.ani": 
			ani = obj.getVar().GetAnimationMap("bmage108", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_f01.ani");
		break;
		case "avatardance_f02.ani": 
			ani = obj.getVar().GetAnimationMap("bmage109", "character/mage/effect/animation/avatar/js60qq506807329_skin/avatardance_f02.ani");
		break;
		case "nnnewswing_body.ani": 
			ani = obj.getVar().GetAnimationMap("bmage110", "character/mage/effect/animation/avatar/js60qq506807329_skin/nnnewswing_body.ani");
		break;
	}
	if(ani){
		obj.setCurrentAnimation(ani);
	}
	else{
		return false;
	}
	return true; 
} 


function setCurrentAnimation_avatar_eff(obj, type, isFlip)
{
	local ani = null;
	local var = obj.getVar();
	ani = var.GetAnimationMap(type, "character/mage/effect/animation/avatar/js60qq506807329_skin/"+ type + ".ani");
	if(ani && isFlip)
		sq_Rewind(ani); 
	return ani; 
} 

function setCurrentAnimationMap_avatar_eff(obj, type, isFlip)
{
	local ani = null;
	local var = obj.getVar();
	ani = var.GetAnimationMap(type, "character/mage/effect/animation/avatar/js60qq506807329_skin/"+ type + ".ani");
	if(ani && isFlip)
		sq_Rewind(ani); 
	return ani;
}
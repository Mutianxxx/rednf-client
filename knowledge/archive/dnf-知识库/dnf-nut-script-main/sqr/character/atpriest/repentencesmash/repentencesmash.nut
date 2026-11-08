function checkExecutableSkill_RepentenceSmash(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_REPENTENCE_SMASH);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_REPENTENCE_SMASH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_RepentenceSmash(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_RepentenceSmash(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATREPENTENCE_SMASH_READY_BODY);
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATREPENTENCE_SMASH_SMASH01_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_REPENTENCE_SMASHATK1);
		local BonusRate =  obj.sq_GetPowerWithPassive(SKILL_REPENTENCE_SMASH, STATE_REPENTENCE_SMASH, 0, -1,1.0);
		obj.sq_SetCurrentAttackPower(BonusRate);
		
		local sizeRate = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, 7);
		local imageRate = sizeRate.tofloat() / 100.0;
		local currentAni = obj.getCurrentAnimation();
		sq_SetAttackBoundingBoxSizeRate(currentAni, imageRate, imageRate, imageRate);
	}
	if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATREPENTENCE_SMASH_SMASH02_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_REPENTENCE_SMASHATK2);
		local BonusRate =  obj.sq_GetPowerWithPassive(SKILL_REPENTENCE_SMASH, STATE_REPENTENCE_SMASH, 1, -1,1.0);
		obj.sq_SetCurrentAttackPower(BonusRate);
		
		local sizeRate = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, 7);
		local imageRate = sizeRate.tofloat() / 100.0;
		local currentAni = obj.getCurrentAnimation();
		sq_SetAttackBoundingBoxSizeRate(currentAni, imageRate, imageRate, imageRate);
	}
	if(substate == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATREPENTENCE_SMASH_END_BODY);
	}
}

function onAttack_RepentenceSmash(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();
	if(substate == 1)
	{
		if(sq_IsHoldable(obj,damager) && sq_IsGrabable(obj,damager) && !sq_IsFixture(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)){
			local target = damager;
			local distance = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, SKL_INT_LV_0);
			local append = "character/atpriest/repentencesmash/ap_repentencesmash.nut"
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(target, obj, -1, false, append, true)
			if(appendage)
			{
				sq_MoveToAppendageForce(target, obj, obj, distance.tointeger(), 0, obj.getZPos(), 160, true, appendage,true)
				appendage.getAppendageInfo().setValidTime(1000);
			}
		}
			//obj.getVar().push_obj_vector(damager);
	}
	if(substate == 2)
	{
		if(sq_IsHoldable(obj,damager) && sq_IsGrabable(obj,damager) && !sq_IsFixture(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)){
			local target = damager;
			local distance = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, SKL_INT_LV_1);
			
			local append = "character/atpriest/repentencesmash/ap_repentencesmash.nut"
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(target, obj, -1, false, append, true)
			if(appendage)
			{
				sq_MoveToAppendageForce(target, obj, obj, distance.tointeger(), 0, obj.getZPos(), 160, true, appendage,true)
				appendage.getAppendageInfo().setValidTime(1000);
			}
		}
	}
}

function onProc_RepentenceSmash(obj)
{
	if(!obj) return;
	for(local i = 0;i < obj.getVar().get_obj_vector_size() ;i++)
	{
		local substate = obj.getSkillSubState();
/*		if(substate == 1)
		{
			local target = obj.getVar().get_obj_vector(i);
			local distance = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, SKL_INT_LV_0);
			local append = "character/atpriest/repentencesmash/ap_repentencesmash.nut"
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(target, obj, -1, false, append, true)
			if(appendage)
			{
				sq_MoveToAppendageForce(target, obj, obj, distance.tointeger(), 0, obj.getZPos(), 160, true, appendage,true)
				appendage.getAppendageInfo().setValidTime(1000);
			}
			
			//local gdpX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), distance);
			//obj.sq_SetCurrentPos(target, gdpX, obj.getYPos(), 0);
		}
		if(substate == 2)
		{
			local target = obj.getVar().get_obj_vector(i);
			local distance = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, SKL_INT_LV_1);
			
			local append = "character/atpriest/repentencesmash/ap_repentencesmash.nut"
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(target, obj, -1, false, append, true)
			if(appendage)
			{
				sq_MoveToAppendageForce(target, obj, obj, distance.tointeger(), 0, obj.getZPos(), 160, true, appendage,true)
				appendage.getAppendageInfo().setValidTime(1000);
			}
			
			//local gdpX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), distance);
			//obj.sq_SetCurrentPos(target, gdpX, obj.getYPos(), 0);
		}*/
	}
}

function onKeyFrameFlag_RepentenceSmash(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("PW_REPENTENCE_01");
		obj.sq_PlaySound("PLAY_MY_GLOBAL");
	}
	if (flagIndex == 1)
	{
		sq_SetShake(obj,12,100);
	}
	if (flagIndex == 2)
	{
		obj.sq_PlaySound("IMPACT_SMASH");
	}
	if (flagIndex == 3)
	{
		sq_flashScreen(obj, 0, 80, 0, 89, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		sq_SetShake(obj,15,300);
	}
	if (flagIndex == 4)
	{
		sq_flashScreen(obj, 0, 200, 200, 127, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	return true;
}

function onEndCurrentAni_RepentenceSmash(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_REPENTENCE_SMASH, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_REPENTENCE_SMASH, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 2)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_REPENTENCE_SMASH, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 3)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onEndState_RepentenceSmash(obj, new_state) {
	if(!obj)
		return false;
	if (new_state != STATE_REPENTENCE_SMASH) 
	{
		local aniA = sq_GetCustomAni(obj, CUSTOM_ANI_ATREPENTENCE_SMASH_SMASH01_BODY);
		local aniB = sq_GetCustomAni(obj, CUSTOM_ANI_ATREPENTENCE_SMASH_SMASH02_BODY);
		local sizeRate = sq_GetIntData(obj, SKILL_REPENTENCE_SMASH, 7);
		local expOldRate = 100.0 / sizeRate.tofloat();
		if(aniA)
		{
			sq_SetAttackBoundingBoxSizeRate(aniA, expOldRate, expOldRate, expOldRate);
		}
		if(aniB)
		{
			sq_SetAttackBoundingBoxSizeRate(aniB, expOldRate, expOldRate, expOldRate);
		}
	}
}

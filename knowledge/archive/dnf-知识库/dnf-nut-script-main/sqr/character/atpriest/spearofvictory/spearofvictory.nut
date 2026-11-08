function checkExecutableSkill_SpearOfVictory(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SPEAR_OF_VICTORY);
	if (isUse)
	{
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_SPEAR_OF_VICTORY);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SPEAR_OF_VICTORY, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SpearOfVictory(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_SpearOfVictory(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODY_READY);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,1500, 1500, 1.0, 1.0);
		local aniObj  = sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/atspearofvictory/spearchargeokloop.ani", 5, -80, 0);
		obj.getVar("aniobj").setObject(0, aniObj); 
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODY_CHARGELOOP);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
	if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODYSHOT_02);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		local aniObj = obj.getVar("aniobj").getObject(0); 
		if (aniObj) 
			aniObj.setValid(false);
		ATPriest_Als_Ani(obj, "character/priest/effect/animation/atspearofvictory/shot_normal.ani", -30, -150, 0, 0, 100, 1, 1.0);
	}
}

function onProc_SpearOfVictory(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState();
	if(substate == 1)
	{
		local bDownKey = obj.isDownSkillLastKey();
		local stateTimer = obj.sq_GetStateTimer();
		local grabMaxTime = sq_GetIntData(obj, SKILL_SPEAR_OF_VICTORY, 0);
		if(!bDownKey || stateTimer >= grabMaxTime)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_SPEAR_OF_VICTORY, STATE_PRIORITY_IGNORE_FORCE, true);
			return;
		}
	}
}

function onKeyFrameFlag_SpearOfVictory(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("PW_VICTORYSPEAR_01");
	}
	if (flagIndex == 4)
	{
		obj.sq_PlaySound("PW_VICTORYSPEAR_02");
		obj.sq_StartWrite();
		obj.sq_WriteDword(9);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 30, -130, 0);
	}
	return true;
}

function onEndCurrentAni_SpearOfVictory(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SPEAR_OF_VICTORY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SPEAR_OF_VICTORY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function checkExecutableSkill_SaintFlash(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SAINT_FLASH);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SAINT_FLASH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SaintFlash(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_SaintFlash(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SAINT_WALL_READY_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_SAINT_WALL_CAST);
		local BonusRate =  obj.sq_GetPowerWithPassive(SKILL_SAINT_FLASH, STATE_SAINT_FLASH, 4, -1,1.0);
		obj.sq_SetCurrentAttackPower(BonusRate);
		ATPriest_Als_Ani(obj, "character/priest/effect/animation/atsaintwall/saintwall_ready_groundeffect.ani", 0, 0, 0, 0, 100, 1, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(16);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 100, 0, 0);
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SAINT_WALL_ATTACK_BODY);
		obj.sq_StartWrite();
		obj.sq_WriteDword(17);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 120, 20, 0);
	}
}


function onKeyFrameFlag_SaintFlash(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("PW_SAINTWALL_01");
	}
	if (flagIndex == 2)
	{
		obj.sq_PlaySound("FINALTEMPEST_MOVE_02");
	}
	if (flagIndex == 7)
	{
		//obj.sq_PlaySound("PW_VICTORYSPEAR_02");
		//obj.sq_StartWrite();
		//obj.sq_WriteDword(9);
		//obj.sq_SendCreatePassiveObjectPacket(24240, 0, 30, -130, 0);
	}
	return true;
}

function onEndCurrentAni_SaintFlash(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SAINT_FLASH, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

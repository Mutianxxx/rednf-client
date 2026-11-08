
function checkExecutableSkill_GrandCrossCrash(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_GRAND_CROSS_CRASH);
	if (isUse)
	{
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_GRAND_CROSS_CRASH, pIntVec, STATE_PRIORITY_FORCE, false, "");
		return true;
	}
	return false;
}

function checkCommandEnable_GrandCrossCrash(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_GrandCrossCrash(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATGRAND_CROSS_CRASH_READY_BODY);
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATGRAND_CROSS_CRASH_SMASH_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_GRANDCROSSCRASHATTACK);
		local BonusRate =  obj.sq_GetPowerWithPassive(SKILL_GRAND_CROSS_CRASH, STATE_GRAND_CROSS_CRASH, 2, -1,1.0);
		obj.sq_SetCurrentAttackPower(BonusRate);
		obj.sq_StartWrite();
		obj.sq_WriteDword(12);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(14);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(15);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
		
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_GrandCrossCrash(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);
		obj.addSetStatePacket(STATE_GRAND_CROSS_CRASH, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

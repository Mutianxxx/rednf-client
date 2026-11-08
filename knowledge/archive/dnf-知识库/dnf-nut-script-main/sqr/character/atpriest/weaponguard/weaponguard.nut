function checkExecutableSkill_WeaponGuard(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WEAPON_GUARD);
	if (isUse)
	{
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_WEAPON_GUARD);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_WEAPON_GUARD, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_WeaponGuard(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_WeaponGuard(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WEAPON_GUARD_STAND_BODY);
		local skill_level = sq_GetSkillLevel(obj, SKILL_WEAPON_GUARD);
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_WEAPON_GUARD, false, 
			"character/atpriest/weaponguard/ap_weaponguard.nut", false);

		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_WEAPON_GUARD, skill_level);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 300, true);
		appendage = obj.GetSquirrelAppendage("character/atpriest/weaponguard/ap_weaponguard.nut");
		if(appendage)
		{
		}
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WEAPON_GUARD_ATTACKED_BODY);
	}
}

function onProcCon_WeaponGuard(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();
	local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_WEAPON_GUARD, false, 
		"character/atpriest/weaponguard/ap_weaponguard.nut", false);

	local pAni = obj.getCurrentAnimation();
	local frmIndex = pAni.GetCurrentFrameIndex();

	if(substate == 0)
	{
		local bDownKey = obj.isDownSkillLastKey();
		if(!bDownKey)
		{
			appendage.setValid(false);
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
		obj.setSkillCommandEnable(SKILL_WEAPON_GUARD,false);
	}
}

function onKeyFrameFlag_WeaponGuard(obj,flagIndex)
{
	if(!obj)
		return false;

	return true;
}

function onAfterDamage_WeaponGuard(obj, attacker, boundingBox)
{
	if(!obj) return;
	local substate = obj.getSkillSubState();
	if(attacker.getDirection() != obj.getDirection())
	{
		if(substate == 0)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_WEAPON_GUARD, STATE_PRIORITY_IGNORE_FORCE, true);
		}
	}
}

function onEndCurrentAni_WeaponGuard(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{

	}
	else if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onEndState_WeaponGuard(obj, newState)
{
	if(!obj) return;

	local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_WEAPON_GUARD, false, 
		"character/atpriest/weaponguard/ap_weaponguard.nut", false);
	if(newState != STATE_WEAPON_GUARD) 
	{
		appendage.setValid(false);
	}
}
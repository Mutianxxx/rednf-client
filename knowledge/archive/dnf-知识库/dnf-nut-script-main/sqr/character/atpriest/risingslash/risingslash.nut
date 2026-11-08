function checkExecutableSkill_RisingSlash(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_RISING_SLASH);
	if (isUse)
	{
		if(sq_GetSkillLevel(obj, SKILL_CRUSADE) > 0)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_RISING_SLASH, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
		else
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_RISING_SLASH, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
	return false;
}

function checkCommandEnable_RisingSlash(obj)
{
	if (!obj) return false;
	return true;
}

function onSetState_RisingSlash(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT ||
		sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT) {
		obj.sq_SetStaticMoveInfo(0, 130, 130, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	} 
	else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT ||
		sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT) {
		obj.sq_StopMove();
	} 
	else {
		obj.sq_SetStaticMoveInfo(0, 50, 50, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}

	local level = sq_GetSkillLevel(obj, SKILL_RISING_SLASH);
	local BonusRate = obj.sq_GetBonusRateWithPassive(SKILL_RISING_SLASH, STATE_RISING_SLASH, 1, 1.0);
	local UpForce = obj.sq_GetLevelData(SKILL_RISING_SLASH, 0, level);

	if (substate == 0) {
		if (Seducer(obj)) {
			local ani = obj.getVar().GetAnimationMap("Seducer175", "Character/Priest/Seducer/ATAnimation/demonizationattack_basic_z_body.ani");
			obj.setCurrentAnimation(ani);
			
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_DEMONIZATIONRISINGSLASH);
			obj.sq_SetCurrentAttackBonusRate(BonusRate);
			local attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttacknUpForce(attackInfo, UpForce);
			
			obj.sq_PlaySound("R_PW_CUTINDASH_02");
		} else {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_RISING_SLASH_BODY);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_RISING_SLASH);
			obj.sq_SetCurrentAttackBonusRate(BonusRate);
			local attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttacknUpForce(attackInfo, UpForce);
			if (isHolyFlame(obj)) {
				obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/risingslash_body.ani"), 0, 0);
				local attackinfo = sq_GetCurrentAttackInfo(obj);
				if (attackinfo) {
					attackinfo.setElement(ENUM_ELEMENT_LIGHT);
					attackinfo.setElement(ENUM_ELEMENT_FIRE);
				}
			}
		}
	}
	if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CRUSADE_RISING_SLASH_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_RISING_SLASH);
		local power = obj.sq_GetPowerWithPassive(SKILL_RISING_SLASH, STATE_RISING_SLASH, 1, -1, 0.7);
		obj.sq_SetCurrentAttackPower(power);
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttacknUpForce(attackInfo, UpForce);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_RisingSlash(obj) {
	if (!obj) return;
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT ||
		sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT) {
		obj.sq_StopMove();
	} 
}

function onKeyFrameFlag_RisingSlash(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("PW_RISING_SLASH");
	}
	if (flagIndex == 3)
	{

		risingslash_swordeffect(obj);

		if(isHolyFlame(obj))
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(1);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 1, 0);
		}
	}
	return true;
}

function risingslash_swordeffect(obj)
{
	local swordeffect = "passiveobject/character/atpriest/animation/atrisingslash/risingslash_swordeffect.ani";
	ATPriest_Create(obj,swordeffect,ENUM_DRAWLAYER_NORMAL,0,-2,0,0,100,0,100,"swordeffect");
}

function onEndCurrentAni_RisingSlash(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

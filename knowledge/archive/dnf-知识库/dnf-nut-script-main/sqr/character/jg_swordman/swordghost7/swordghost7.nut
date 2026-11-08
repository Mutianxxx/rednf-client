function checkExecutableSkill_SwordGhost7(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_7);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost7(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost7(obj, state, datas, isResetTimer) {

	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);

	obj.setSkillSubState(substate);

	obj.sq_StopMove(); //?????????

	local skill_level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_7);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_7_GSB_START); //????ANI???
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SWORD_GHOST_7, false, "character/JG_SwordMan/ap_sword_ghost_flag.nut", false);
		appendage.sq_SetValidTime(5000);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SWORD_GHOST_7, skill_level);
		CNSquirrelAppendage.sq_Append(appendage, obj, obj);

		if (sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}

	}
	else if (substate == 1) {
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_7_GSB_MOVE); //????ANI???

		local gaugeValue_rate = setSwordGhost3State(obj);
		local hit_ex = setSwordGhost7hitEx(obj) / 3;
		if (hit_ex > 1) {
			setSwordGhostEnergyDec(obj, 1);
		}
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat());
		local hit = obj.sq_GetIntData(SKILL_SWORD_GHOST_7, 0);

		local count = hit + hit_ex.tointeger();
		obj.sq_SendCreatePassiveObjectPacket(26317, 0, -65, 1, 0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(126);
		sq_BinaryWriteDword(attackBonusRate);
		sq_BinaryWriteDword(100);
		sq_BinaryWriteDword(count);
		obj.sq_SendCreatePassiveObjectPacket(24370, 0, -65, 1, 0);

		obj.sq_SendCreatePassiveObjectPacket(262161, 0, 0, 1, 0);
	}
	else if (substate == 2) {

}

}

function onProc_SwordGhost7(obj) {

	if (!obj)

	return false;

	local substate = obj.getSkillSubState();

	if (substate == 0)

	{
		obj.setSkillCommandEnable(SKILL_SWORD_GHOST_7, true);

		local iEnterSkill = obj.sq_IsEnterSkill(SKILL_SWORD_GHOST_7);

		if (iEnterSkill != -1)

		{
			obj.sq_IntVectClear();

			obj.sq_IntVectPush(1);

			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7, STATE_PRIORITY_IGNORE_FORCE, true);
		}

		if (sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL))

		{

			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

		}
	}

}

function onKeyFrameFlag_SwordGhost7(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 2) {
		obj.sq_SetStaticMoveInfo(0, 500, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (flagIndex == 3) {
		obj.sq_SetStaticMoveInfo(0, 500, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
	}
	if (flagIndex == 4) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_7, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return true;
}

function onEndCurrentAni_SwordGhost7(obj) {
	CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
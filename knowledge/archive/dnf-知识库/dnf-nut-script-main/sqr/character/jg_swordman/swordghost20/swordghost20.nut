function checkExecutableSkill_SwordGhost20(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_20);
	local state = obj.sq_GetState();

	if (state == STATE_SAN_DUAN_ZHAN || state == STATE_SWORD_GHOST_1 || state == STATE_SWORD_GHOST_2 || state == STATE_SWORD_GHOST_7 || state == STATE_SWORD_GHOST_8 || state == STATE_SWORD_GHOST_11 || state == STATE_SWORD_GHOST_15 || state == STATE_SWORD_GHOST_18 || state == STATE_SWORD_GHOST_23) {
		local skill = sq_GetSkill(obj, SKILL_SWORD_GHOST_20);
		//print( "skill:" + skill);

		if (skill.isInCoolTime()) {
			//print( "skill_off");
			return false;
		}
		else {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_SendCreatePassiveObjectPacket(260191, 0, 0, 1, 0);
			//print( "skill_on");
			return true;
		}

	}

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_20, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost20(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_SwordGhost20(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_10_YG_ONE_ATTACK);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.5, 0.5); //
	}

}

function onKeyFrameFlag_SwordGhost20(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		obj.sq_SendCreatePassiveObjectPacket(260191, 0, 0, 1, 0);
		//print("ok\n\r");
		return true;
	}

}

function onEndCurrentAni_SwordGhost20(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	
}
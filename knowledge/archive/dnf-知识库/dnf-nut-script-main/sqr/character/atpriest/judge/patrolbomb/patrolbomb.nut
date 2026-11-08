function checkExecutableSkill_patrolbomb(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_PATROLBOMB);
	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_PATROLBOMB, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_patrolbomb(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_PatrolBomb(obj, state, datas, isResetTimer) {
	if (!obj) return false;

	local substate = obj.getVar().get_vector(0);
	local z = obj.getZPos();

	local skillLevel = obj.sq_GetSkillLevel(SKILL_MALLEUSMALEFICARUM);
	if (skillLevel > 0) {
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT || sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT) {
			substate = 1;
		}
	}

	obj.setSkillSubState(substate);
	if (substate == 0) {
		if (z > 5) {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_PETROLBOMB_BACKSTEP_BODY);
			if (isHolyFlame(obj)) {
				obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/petrolbomb_backstep_body.ani"), 0, 0);
			}
		}
		else {
			obj.sq_StopMove();
			obj.sq_SetCurrentAnimation(ANI_PatrolBomb);
			if (isHolyFlame(obj)) {
				obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/petrolbomb_standing_body.ani"), 0, 0);
			}
		}
	}
	else if (substate == 1) {
		if (z < 5) {
			obj.sq_StopMove();
		}
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MALLEUSMALEFICARUM);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_PatrolBomb(obj) {
	if (!obj) return;
	local z = obj.getZPos();
	if (z == 0) {
		obj.sq_StopMove();
	}
}

function onKeyFrameFlag_PatrolBomb(obj, flagIndex) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	local ani = obj.sq_GetCurrentAni();
	if (flagIndex == 1) {
		if (substate == 0) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(102);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 95);
		}
		else if (substate == 1) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(119);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
		}
	}
	obj.sq_ClearKeyFrameFlag(ani);
	return true;
}

function onEndCurrentAni_PatrolBomb(obj) {
	if (!obj) return false;
	local z = obj.getZPos();
	if (z > 0) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);
		sq_IntVectorPush(pIntVec, 0);
		sq_IntVectorPush(pIntVec, 1);
		obj.addSetStatePacket(STATE_JUMP, pIntVec, STATE_PRIORITY_FORCE, false, "");
		obj.flushSetStatePacket();
	}
	else {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
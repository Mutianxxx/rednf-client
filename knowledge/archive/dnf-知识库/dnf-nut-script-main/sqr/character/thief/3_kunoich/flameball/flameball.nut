function checkCommandEnable_flameball(obj) {
	return true;
}

function checkExecutableSkill_flameball(obj) {
	if (!obj) return false;

	local state = obj.sq_GetState();
	if (state == 3 || state == 4 || state == 5 || state == 9 || state == 16 || state == 40) return false;
	if (obj.sq_IsUseSkill(SKILL_FLAMEBALL)) {
		local now_z = obj.getZPos();
		if (state == 6 || state == 7 || now_z > 40) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_FLAMEBALL, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		} else {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_FLAMEBALL, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}

	}

	return false;
}

function onSetState_flameball(obj, state, datas, isResetTimer) {
	if (!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch (subState) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FLAMEBALL1);
		obj.sq_PlaySound("R_TF_FLAMEBALL");
		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FLAMEBALL2);
		obj.sq_ZStop();
		obj.sq_PlaySound("R_TF_FLAMEBALL");
		break;
	}
}

function onEndCurrentAni_flameball(obj) {
	if (!obj) return;

	if (!obj.isMyControlObject()) {
		return;
	}

	local subState = obj.getSkillSubState();
	switch (subState) {
	case 0:
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	case 1:
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_IntVectPush(1);
		obj.sq_IntVectPush(200);
		obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}

function onAfterSetState_flameball(obj, state, datas, isResetTimer) {
	if (!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	local size = sq_GetIntData(obj, 81, 1);

	switch (subState) {
	case 0:
		local offsetx = (150 - size) / 1.65;
		local offsetz = (150 - size) / 1.29;
		if (obj.isMyControlObject()) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(2);
			obj.sq_SendCreatePassiveObjectPacket(24356, 0, -23 + offsetx.tointeger(), 0, -34 + offsetz.tointeger());
		}
		break;
	case 1:
		if (obj.isMyControlObject()) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_SendCreatePassiveObjectPacket(24356, 0, -53, 0, 71);
		}
		break;
	}
}
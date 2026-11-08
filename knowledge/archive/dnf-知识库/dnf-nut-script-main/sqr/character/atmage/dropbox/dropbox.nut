//wave shake 2 100

function checkExecutableSkill_dropbox(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_DROPBOX);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_DROPBOX, STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_dropbox(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_DROPBOX(obj, state, datas, isResetTimer) {
	if (!obj) return;

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_DROPBOX_BODY);
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);

}

function onEndCurrentAni_DROPBOX(obj) {
	if (!obj.isMyControlObject()) {
		return;
	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onKeyFrameFlag_DROPBOX(obj, flagIndex) {
	if (!obj) return false;
	if (!obj.isMyControlObject()) {
		return;
	}
	if (obj.getVar("flag").get_vector(0) == 0) {
		obj.getVar("flag").set_vector(0, 1);

		local power = obj.sq_GetPowerWithPassive(SKILL_DROPBOX, STATE_DROPBOX, 0, -1, 1.0);
		local power1 = obj.sq_GetPowerWithPassive(SKILL_DROPBOX, STATE_DROPBOX, 1, -1, 1.0);
		local power2 = obj.sq_GetPowerWithPassive(SKILL_DROPBOX, STATE_DROPBOX, 2, -1, 1.0);

		local boomRate = obj.sq_GetIntData(SKILL_DROPBOX, 5);

		local len = obj.sq_GetIntData(SKILL_DROPBOX, 1);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if (leftPress || rightPress) {
			len = obj.sq_GetIntData(SKILL_DROPBOX, 2);
		}

		obj.sq_StartWrite();
		obj.sq_WriteDword(power); // attackBonusRate
		obj.sq_WriteDword(108); // attackBonusRate
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_DROPBOX, 6)); // attackBonusRate

		if (sq_getRandom(0, 100).tointeger() > boomRate) {
			obj.sq_WriteDword(power1); // attackBonusRate
			obj.sq_WriteDword(0); // attackBonusRate // no boom
		}
		else {
			obj.sq_WriteDword(power2); // attackBonusRate
			obj.sq_WriteDword(1); // attackBonusRate // no boom
		}

		if (!isEventHorizen(obj)) {
			setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_DROPBOX, 3));
			obj.sq_WriteDword(0);
		}
		else {
			setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_DROPBOX, 4));
			removeEventHorizen(obj);
			obj.sq_WriteDword(1);
		}

		obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, obj.sq_GetIntData(SKILL_DROPBOX, 0));

	}
	return true;
}
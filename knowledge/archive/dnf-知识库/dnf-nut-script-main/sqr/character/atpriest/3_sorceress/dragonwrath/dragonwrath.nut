function checkCommandEnable_DragonWrath(obj) {
	return true;
}

function checkExecutableSkill_DragonWrath(obj) {
	if (!obj) return false;
	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_DRAGONWRATH);
	if (UncleBangValue1)

	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_DRAGONWRATH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;

	}
	return false;
}

function onSetState_DragonWrath(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(UncleBangValue1);
	obj.sq_StopMove();
	switch (UncleBangValue1)

	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DRAGONWRATH1);
			sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_DRAGONWRATH, sq_GetSkillLevel(obj, SKILL_DRAGONWRATH)), true);
			break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DRAGONWRATH2);
			break;
		case 2:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DRAGONWRATH3);
			break;

	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_DragonWrath(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local UncleBangValue1 = obj.getSkillSubState();
	if (UncleBangValue1 <= 1)

	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(UncleBangValue1 + 1);
		obj.sq_AddSetStatePacket(STATE_DRAGONWRATH, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	if (UncleBangValue1 == 2)

	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);

	}
}

function onKeyFrameFlag_DragonWrath(obj, flagIndex) {
	if (!obj) return false;
	local UncleBangValue1 = obj.getSkillSubState();
	switch (UncleBangValue1)

	{
		case 2:
			switch (flagIndex) {
				case 10001:
					if (obj.isMyControlObject()) {
						sq_SetMyShake(obj, 8, 300);
						obj.sq_StartWrite();
						obj.sq_WriteDword(3);
						obj.sq_WriteDword(7);
						obj.sq_SendCreatePassiveObjectPacket(24338, 0, sq_GetIntData(obj, SKILL_DRAGONWRATH, 0), 0, 0);
					}
					break;
			}
			break;

	}
	return true;
}

function onEndState_DragonWrath(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_DRAGONWRATH)
		sq_EndDrawCastGauge(obj);
}
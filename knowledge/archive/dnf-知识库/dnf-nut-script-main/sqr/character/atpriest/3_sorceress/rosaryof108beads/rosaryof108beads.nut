
function checkCommandEnable_RosaryOf108Beads(obj) {
	return true;
}

function checkExecutableSkill_RosaryOf108Beads(obj) {
	if (!obj) return false;
	local UncleBangValue1 = obj.sq_IsUseSkill(SKILL_ROSARYOF108BEADS);
	if (UncleBangValue1)

	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_ROSARYOF108BEADS, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;

	}
	return false;
}

function onSetState_RosaryOf108Beads(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(UncleBangValue1);
	obj.sq_StopMove();
	switch (UncleBangValue1)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ROSARYOF108BEADS);
			sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_ROSARYOF108BEADS, sq_GetSkillLevel(obj, SKILL_ROSARYOF108BEADS)), true);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_RosaryOf108Beads(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local UncleBangValue1 = obj.getSkillSubState();
	if (UncleBangValue1 >= 0)

	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);

	}
}

function onEndState_RosaryOf108Beads(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_ROSARYOF108BEADS)
		sq_EndDrawCastGauge(obj);
}

function onKeyFrameFlag_RosaryOf108Beads(obj, flagIndex) {
	if (!obj) return false;
	local UncleBangValue1 = obj.getSkillSubState();
	switch (UncleBangValue1)
	{
		case 0:
			switch (flagIndex) {
				case 10001:
					if (obj.isMyControlObject()) {
						local UncleBangValue2 = obj.sq_GetSkillLoad(234);
						local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
						local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
						obj.sq_StartWrite();
						obj.sq_WriteDword(3);
						obj.sq_WriteDword(8);
						obj.sq_WriteDword(UncleBangValue4);
						obj.sq_SendCreatePassiveObjectPacket(24338, 0, 0, 0, 0);
						RosaryBeadClear(obj);
					}
					break;
			}
			break;
	}
	return true;
}
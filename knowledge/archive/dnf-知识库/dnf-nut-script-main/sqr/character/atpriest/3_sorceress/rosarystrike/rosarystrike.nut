function checkCommandEnable_RosaryStrike(obj) {
	return true;

}

function checkExecutableSkill_RosaryStrike(obj) {
	if (!obj) return false;
	local UncleBangValue1 = obj.sq_IsUseSkill(235);
	if (UncleBangValue1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_ROSARYSTRIKE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;

}

function onSetState_RosaryStrike(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local UncleBangValue1 = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(UncleBangValue1);
	obj.sq_StopMove();
	switch (UncleBangValue1) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ROSARYSTRIKE);
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_RosaryStrike(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local UncleBangValue1 = obj.getSkillSubState();
	if (UncleBangValue1 >= 0) {
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}

}

function onKeyFrameFlag_RosaryStrike(obj, flagIndex) {
	if (!obj) return false;
	local UncleBangValue1 = obj.getSkillSubState();
	switch (UncleBangValue1) {
	case 0:
		switch (flagIndex) {
		case 10001:
				sq_createPooledObject(obj, "passiveobject/unclebang_shared_passive_object/atpriest/animation/3_sorceress/atrosarystrike/rosarystrike_a.ani", -60 + sq_getRandom(-30, 30), 0, 130 + sq_getRandom(-30, 10), 100, 1.0, 30, 0, 1);
				sq_createPooledObject(obj, "passiveobject/unclebang_shared_passive_object/atpriest/animation/3_sorceress/atrosarystrike/rosarystrike_a.ani", -60 + sq_getRandom(-30, 30), 0, 130 + sq_getRandom(-30, 10), 100, 1.0, 30, 0, 1);
				local UncleBangValue2 = obj.sq_GetSkillLoad(SKILL_ROSARYSHOOTING);
				local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
				local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
				obj.sq_StartWrite();
				obj.sq_WriteDword(3);
				obj.sq_WriteDword(2);
				obj.sq_WriteDword(UncleBangValue4);
				obj.sq_WriteDword(sq_getRandom(20, 30));
				obj.sq_SendCreatePassiveObjectPacket(24338, 0, -40, 0, 120);
				obj.sq_StartWrite();
				obj.sq_WriteDword(3);
				obj.sq_WriteDword(2);
				obj.sq_WriteDword(UncleBangValue4);
				obj.sq_WriteDword(sq_getRandom(20, 30));
				obj.sq_SendCreatePassiveObjectPacket(24338, 0, -40, 0, 120);
				RosaryBeadClear(obj);
			break;
		}
		break;
	}
	return true;
}
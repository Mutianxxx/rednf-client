function checkCommandEnable_BigRosary(obj) {
	return true;
}

function checkExecutableSkill_BigRosary(obj) //addjumpthrow
{
	if (!obj) return false;
	local isUsed = obj.sq_IsUseSkill(SKILL_BIGROSARY);
	if (isUsed) {
		local z = obj.getZPos();
		if (z > 30) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_BIGROSARY, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		else {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_BIGROSARY, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		return true;
	}
	return false;
}

function onSetState_BigRosary(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	switch (substate) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGROSARY1);
		RosaryBeadClear(obj);
		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGROSARY2);
		if (obj.isMyControlObject()) {
			local UncleBangValue2 = obj.sq_GetSkillLoad(234);
			local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
			local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(13);
			obj.sq_WriteDword(UncleBangValue4);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 300, 0, 0);
		}
		break;
	case 2:
		obj.sq_ZStop();
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGROSARY_JUMP1);
		RosaryBeadClear(obj);
		break;
	case 3:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGROSARY_JUMP2);
		if (obj.isMyControlObject()) {
			local UncleBangValue2 = obj.sq_GetSkillLoad(234);
			local UncleBangValue3 = UncleBangValue2.getRemainLoadNumber();
			local UncleBangValue4 = sq_GetIntData(obj, SKILL_ROSARYSHOOTING, UncleBangValue3);
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(13);
			obj.sq_WriteDword(UncleBangValue4);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 300, 0, -sq_GetZPos(obj));
		}
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if (obj.isMyControlObject())
	{
		sq_flashScreen(obj, 80, obj.getCurrentAnimation().getDelaySum(false), 240, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
}

function onEndCurrentAni_BigRosary(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_BIGROSARY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_BIGROSARY, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 3) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);
		sq_IntVectorPush(pIntVec, 0);
		sq_IntVectorPush(pIntVec, 1);
		obj.addSetStatePacket(STATE_JUMP, pIntVec, STATE_PRIORITY_FORCE, false, "");
		obj.flushSetStatePacket();
	}
}
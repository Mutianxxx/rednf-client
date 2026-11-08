function checkCommandEnable_TalismanOfOppression(obj) {
	return true;
}

function checkExecutableSkill_TalismanOfOppression(obj)
{
	if (!obj) return false;
	local isUsed = obj.sq_IsUseSkill(SKILL_TALISMANOFOPPRESSION);
	if (isUsed) {
		local z = obj.getZPos();
		if (z > 30) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_TALISMANOFOPPRESSION, STATE_PRIORITY_IGNORE_FORCE, true);
		} else {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_TALISMANOFOPPRESSION, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		return true;
	}
	return false;
}

function onSetState_TalismanOfOppression(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	switch (substate) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TALISMANOFOPPRESSION);
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_TALISMANOFOPPRESSION, sq_GetSkillLevel(obj, SKILL_TALISMANOFOPPRESSION)), true);
		break;
	case 1:
		obj.sq_ZStop();
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TALISMANOFOPPRESSION_JUMP);
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onProc_TalismanOfOppression(obj) {
	if (!obj) return;

	local z = obj.getZPos();
	if (z == 0) {
		obj.sq_StopMove();
	}
}

function onEndCurrentAni_TalismanOfOppression(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);
		sq_IntVectorPush(pIntVec, 0);
		sq_IntVectorPush(pIntVec, 1);
		obj.addSetStatePacket(STATE_JUMP, pIntVec, STATE_PRIORITY_FORCE, false, "");
		obj.flushSetStatePacket();
	}
}

function onEndState_TalismanOfOppression(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_TALISMANOFOPPRESSION)
		sq_EndDrawCastGauge(obj);
}

function onKeyFrameFlag_TalismanOfOppression(obj, flagIndex) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	if (flagIndex == 10001) {
		if (substate == 0) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(0);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 60, 0, 90);
		}
		else if (substate == 1) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(3);
			obj.sq_WriteDword(1);
			obj.sq_SendCreatePassiveObjectPacket(24338, 0, 60, 0, 90);
			sq_SetZVelocity(obj,30,30);
			obj.sq_SetStaticMoveInfo(0, -200, -200, false);
		}
		
	}
	return true;
}
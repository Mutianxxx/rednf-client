
function checkExecutableSkill_silhouette(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SILHOUETTE);

	if (isUse) {

		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_SILHOUETTE, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}

	return false;
}


function setCharacterFristAnimation_silhouette(obj) {
	if (!obj) return;
	local level = sq_GetSkillLevel(obj, SKILL_SILHOUETTE);
	if (level > 0) {
		createFristAnimationPooledObject(obj,
			"character/mage/atanimation/silhouette_shoot_body.ani");

	}
}

function checkCommandEnable_silhouette(obj) {
	return true;
}


function onSetState_SILHOUETTE(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();

	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

	if (state == 0) {
		local skill_level = sq_GetSkillLevel(obj, SKILL_SILHOUETTE);
		local castTime = sq_GetCastTime(obj, SKILL_SILHOUETTE, skill_level);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SILHOUETTE_CAST_BODY);
		sq_StartDrawCastGauge(obj, castTime, true);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
	}
}

function onKeyFrameFlag_SILHOUETTE(obj, flagIndex) {
	if (!obj) return;
	if (obj.getVar("flag").get_vector(0) == 0) {
		obj.getVar("flag").set_vector(0, 1);
		local charge = obj.sq_GetIntData(SKILL_SILHOUETTE, 1);
		local speed = obj.sq_GetIntData(SKILL_SILHOUETTE, 0);
		local size = obj.sq_GetIntData(SKILL_SILHOUETTE, 3);

		local damage = obj.sq_GetPowerWithPassive(SKILL_SILHOUETTE, STATE_SILHOUETTE, 0, -1, 1.0);
		local damage2 = obj.sq_GetPowerWithPassive(SKILL_SILHOUETTE, STATE_SILHOUETTE, 2, -1, 1.0);

		sq_BinaryStartWrite();
		sq_BinaryWriteDword(damage);
		sq_BinaryWriteDword(15);
		sq_BinaryWriteDword(damage2);
		sq_BinaryWriteDword(size);

		if (!isEventHorizen(obj)) {
			sq_BinaryWriteDword(speed);
			obj.sq_WriteDword(0);
		} else {
			sq_BinaryWriteDword(300);
			obj.sq_WriteDword(1);
			removeEventHorizen(obj);
		}
		obj.sq_SendCreatePassiveObjectPacket(24366, 0, 0, 1, 0);
		setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + charge);
	}
}

function onEndCurrentAni_SILHOUETTE(obj) {
	if (!obj) return;
	if (!obj.isMyControlObject()) {
		return;
	}
	local state = obj.getSkillSubState();
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);

}

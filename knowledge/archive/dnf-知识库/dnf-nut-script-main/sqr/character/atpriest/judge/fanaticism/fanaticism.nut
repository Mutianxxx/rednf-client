
function checkExecutableSkill_fanaticism(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_FANATICISM);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_FANATICISM, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function onKeyFrameFlag_Fanaticism(obj, flagIndex) {
	if (!obj) return false;
	if (obj.getVar("flag").get_vector(0) == 0) {
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(1);
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atpriest/judge/fanaticism/ap_fanaticism.nut")) {
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/judge/fanaticism/ap_fanaticism.nut");
		}
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_FANATICISM, false, "character/atpriest/judge/fanaticism/ap_fanaticism.nut", true);
		local skill_level = sq_GetSkillLevel(obj, SKILL_FANATICISM);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_FANATICISM, skill_level);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_FANATICISM, true);
		appendage.setBuffIconImage(130);

		local value0 = sq_GetLevelData(obj, SKILL_FANATICISM, 0, skill_level).tofloat();
		local value1 = sq_GetLevelData(obj, SKILL_FANATICISM, 1, skill_level).tofloat();
		value0 = value0/10;
		value1 = value1/10;
		local change_appendage = appendage.sq_getChangeStatus("fanaticism");
		if (!change_appendage) {
			change_appendage = appendage.sq_AddChangeStatus("fanaticism", obj, obj, 0, 0, true, 0);
		}
		if (change_appendage) {
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, value1);
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, value0);
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE, false, value0);
		}
	}
}

function checkCommandEnable_fanaticism(obj) {

	return true;
}

function onSetState_Fanaticism(obj, state, datas, isResetTimer) {
	obj.sq_StopMove();
	if(isHolyFlame(obj)){
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOLYFLAME_FANATICISM_BODY);
	}
	else{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FANATICISM_BODY);
	}
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	//sq_AddDrawOnlyAniFromParent(obj,"character/priest/atanimation/holyflameweaponeffect/fanaticism_body.ani", 0, 1, 0);
}

function onEndCurrentAni_Fanaticism(obj) {
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

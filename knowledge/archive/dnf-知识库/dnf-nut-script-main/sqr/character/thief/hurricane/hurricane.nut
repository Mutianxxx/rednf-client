
function onSetState_Hurricane(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local subState = obj.sq_GetVectorData(datas, 0);
	local isSet = obj.getVar("isSet").get_vector(0);
	local skillLevel = sq_GetSkillLevel(obj, 11);
	local prob = sq_GetLevelData(obj, 11, 0, skillLevel);
	obj.setSkillSubState(subState);
	//obj.getVar("knifeCount").setInt(0, 0);
	if (subState == 1 && isSet == 0) {
		obj.setTimeEvent(0, 30, 0, true);
		obj.getVar("isSet").set_vector(0, 1);
	}

}

function onTimeEvent_Hurricane(obj, timeEventIndex, timeEventCount) {
	if (!obj) return false;

	local subState = obj.getSkillSubState();
	local skillLevel = obj.sq_GetSkillLevel(SKILL_DEATH_HURRICANE);
	local skill = sq_GetSkill(obj, SKILL_DEATH_HURRICANE);
	if (timeEventIndex == 0 && subState == 1 && skillLevel > 0 && !skill.isSealFunction()) {
		local knifeCount = obj.getVar("knifeCount").getInt(0);
		if (knifeCount > 11) {
			obj.getVar("knifeCount").setInt(0, 0);
		}
		obj.sq_StartWrite();
		obj.sq_WriteDword(knifeCount);
		//print("knifeCount:"+knifeCount+"\n");
		obj.getVar("knifeCount").setInt(0, knifeCount + 1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 50);
	}

}


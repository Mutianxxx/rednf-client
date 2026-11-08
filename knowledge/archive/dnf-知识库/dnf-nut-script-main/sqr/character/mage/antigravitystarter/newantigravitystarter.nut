function onAfterSetState_newantigravitystarter(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local skill = sq_GetSkill(obj, 168);
	if(!skill){
		return;
	}
	if(!skill.isSealFunction()){
		obj.sq_SetCurrentAnimation(44);
		local currentAni = obj.getCurrentAnimation();
		currentAni.setSpeedRate(1500.0);
	}
}

function onProcCon_newantigravitystarter(obj)
{
	if (!obj) return;
	local skill = sq_GetSkill(obj, 168);
	if(!skill){
		return;
	}
	if(skill.isSealFunction()){
		return;
	}
	local myPObjCount = obj.getMyPassiveObjectCount(23047);
	if (myPObjCount > 0) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
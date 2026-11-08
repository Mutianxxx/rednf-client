 
function checkExecutableSkill_darkmoon(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND || state == STATE_ATTACK || state == STATE_DASH) {

		local b_useskill = obj.sq_IsUseSkill(148);

		if (b_useskill) {
			local skillLevel = sq_GetSkillLevel(obj, 148);
			local castTime = sq_GetCastTime(obj, 148, skillLevel);

			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0); // throwState
			obj.sq_IntVectPush(0); // throwType
			obj.sq_IntVectPush(148); // throwIndex
			obj.sq_IntVectPush(castTime); // throwChargeTime
			obj.sq_IntVectPush(castTime); // throwShootTime
			obj.sq_IntVectPush(3); // throwAnimationIndex
			obj.sq_IntVectPush(4); // chargeSpeedType
			obj.sq_IntVectPush(4); // throwShootSpeedType
			obj.sq_IntVectPush(1000); // chargeSpeedValue
			obj.sq_IntVectPush(1000); // throwShootSpeedValue
			obj.sq_IntVectPush(-1); // personalCastRange
			obj.sq_AddSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
			return true;
		}
	}

	return false;
};

function checkCommandEnable_darkmoon(obj) {
	if(!obj) return false;

	local state = obj.sq_GetState();
	
	if(state == STATE_ATTACK) {
		return obj.sq_IsCommandEnable(148);
	}
	

	if(state == STATE_STAND || state == STATE_ATTACK || state == STATE_DASH) 
	{
		return true;
	}
	
	return false;
};

//obj, state, datas, isResetTimer
function onAfterSetState_swordman_throw(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local skillIndex = obj.getThrowIndex();
	local throwState = obj.getThrowState();
	switch (skillIndex) {
	case 47:
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/appendage/ap_wavemark.nut")) 
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/appendage/ap_wavemark.nut");
		local B88LiI5xw3wLi = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 47, true, "character/swordman/appendage/ap_wavemark.nut", false);
		CNSquirrelAppendage.sq_Append(B88LiI5xw3wLi, obj, obj, false);
		break;
	case 82:
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/appendage/ap_kalla.nut")) 
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/appendage/ap_kalla.nut");
		local e5iMmYEhk2_ZCROCo = obj.sq_GetLevelData(82, 0, sq_GetSkillLevel(obj, 82));
		local B88LiI5xw3wLi = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 82, true, "character/swordman/appendage/ap_kalla.nut", false);
		B88LiI5xw3wLi.sq_SetValidTime(e5iMmYEhk2_ZCROCo);
		CNSquirrelAppendage.sq_Append(B88LiI5xw3wLi, obj, obj, false);
		break;
	case 18:
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/appendage/ap_ghoststep.nut")) 
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/appendage/ap_ghoststep.nut");
		local e5iMmYEhk2_ZCROCo = obj.sq_GetLevelData(18, 0, sq_GetSkillLevel(obj, 18));
		local B88LiI5xw3wLi = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 18, true, "character/swordman/appendage/ap_ghoststep.nut", false);
		B88LiI5xw3wLi.sq_SetValidTime(e5iMmYEhk2_ZCROCo);
		CNSquirrelAppendage.sq_Append(B88LiI5xw3wLi, obj, obj, false);
		break;
	case SKILL_SWORDMAN_SACRIFICE:
		if(obj.getThrowState() == 1 && obj.sq_GetSkillLevel(SKILL_SWORDMAN_SACRIFICE) > 0){
			local anisa = sq_AddDrawOnlyAniFromParent(obj, "character/swordman/effect/animation/sacrifice1.ani", 0, 1, 0);
			SetMyAppendage_swordman_sacrifice(obj, datas);
		}
		break;
	}
};

function onProc_StandAloneWave(obj) {
	if (!obj) 
		return;
	if (checkModuleType(MODULE_TYPE_DUNGEON_TYPE)) {
		local skill = sq_GetSkill(obj, SKILL_WAVESPINAREA);
		if (skill && skill.isInCoolTime() == false) {
			obj.setSkillCommandEnable(SKILL_WAVESPINAREA, true);
			local b_useskill = obj.sq_IsEnterSkill(SKILL_WAVESPINAREA);
			if (b_useskill != -1) {
				local skill_level = sq_GetSkillLevel(obj, SKILL_WAVESPINAREA);
				local ShootTime = sq_GetIntData(obj, SKILL_WAVESPINAREA, 0);
				obj.startSkillCoolTime(SKILL_WAVESPINAREA, skill_level, -1);
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0); // throwState
				obj.sq_IntVectPush(0); // throwType
				obj.sq_IntVectPush(SKILL_WAVESPINAREA); // throwIndex
				obj.sq_IntVectPush(0); // throwChargeTime
				obj.sq_IntVectPush(ShootTime); // throwShootTime
				obj.sq_IntVectPush(1); // throwAnimationIndex
				obj.sq_IntVectPush(4); // chargeSpeedType
				obj.sq_IntVectPush(4); // throwShootSpeedType
				obj.sq_IntVectPush(1000); // chargeSpeedValue
				obj.sq_IntVectPush(1000); // throwShootSpeedValue
				obj.sq_IntVectPush(-1); // personalCastRange
				obj.sq_AddSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
			}
		}
	}
}


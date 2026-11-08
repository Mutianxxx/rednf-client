function checkExecutableSkill_SwordGhost13(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_13);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_13, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost13(obj) {
	if (!obj) 
		return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND || state == STATE_ATTACK || state == STATE_DASH) 
		return true;
}

function onProc_SwordGhost13(obj) {

}

function onSetState_SwordGhost13(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();

	local skillLevel = obj.sq_GetSkillLevel(206);
	if (skillLevel > 0) {
		obj.sq_SendCreatePassiveObjectPacket(260186, 0, -9999, 0, 0); //yd-1jue
	}

	obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_13_BUFF);

	local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SWORD_GHOST_13, false, "character/JG_SwordMan/swordghost13/ap_buff.nut", false);

	local skill_level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_13);

	appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SWORD_GHOST_13, skill_level);

	CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_COMMON, true);

	appendage = obj.GetSquirrelAppendage("character/JG_SwordMan/swordghost13/ap_buff.nut");

	appendage.setEnableIsBuff(true); //???buff????
	appendage.setBuffIconImage(150); //???buff????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/spiritconversion/spiritconversionbuff_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);

	if (appendage) {
		// ????
		local change_time = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_0, skill_level);

		appendage.sq_SetValidTime(change_time); // ???? ?? ??

		//print(" change_time:" + change_time);

		local ATTACK_SPEED = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_1, skill_level);

		local MOVE_SPEED = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_2, skill_level); //SKILL_COOLTIME = SKILL_COOLTIME * -0.01;

		local CASR_SPEED = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_3, skill_level);

		local CRITICAL_HIT_RATE = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_4, skill_level);

		local CRITICAL_DAMAGE_RATE = sq_GetLevelData(obj, SKILL_SWORD_GHOST_13, SKL_STATIC_INT_IDX_5, skill_level);

		local change_appendage = appendage.sq_getChangeStatus("ele_atk_water");

		if (!change_appendage) change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_ELEMENT_ATTACK_ALL, false, CHANGE_STATUS_TYPE_ATTACK_SPEED, APID_COMMON);

		if (!change_appendage) change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_COOLTIME_DECLINE, false, CHANGE_STATUS_TYPE_MOVE_SPEED, APID_COMMON);

		if (!change_appendage) change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, CHANGE_STATUS_TYPE_CAST_SPEED, APID_COMMON);

		if (!change_appendage) change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, APID_COMMON);

		if (!change_appendage) change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, APID_COMMON);

		if (change_appendage) {
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, ATTACK_SPEED.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, MOVE_SPEED.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED, false, CASR_SPEED.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, CRITICAL_HIT_RATE.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, CRITICAL_DAMAGE_RATE.tofloat());
		}
	}

}

//CHANGE_STATUS_TYPE_ATTACK_SPEED < -  10 //???????????
//CHANGE_STATUS_TYPE_MOVE_SPEED < -  11 //?????????
//CHANGE_STATUS_TYPE_CAST_SPEED < -  12 //?????????
//CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE < -  15 //???????????
//CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE < -  50 //??????????????????

function onEndCurrentAni_SwordGhost13(obj) {
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
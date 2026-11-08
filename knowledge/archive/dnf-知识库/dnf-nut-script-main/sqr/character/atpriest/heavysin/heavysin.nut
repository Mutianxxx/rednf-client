
function checkExecutableSkill_HeavySin(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_HEAVY_SIN);
	if (isUse) {
		if (Seducer(obj)) {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			obj.addSetStatePacket(STATE_HEAVY_SIN, pIntVec, STATE_PRIORITY_FORCE, false, "");
		} else {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(STATE_HEAVY_SIN, pIntVec, STATE_PRIORITY_FORCE, false, "");
		}
	}
}

function checkCommandEnable_HeavySin(obj) {
	return true;
}


function onSetState_HeavySin(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local level = sq_GetSkillLevel(obj, SKILL_HEAVY_SIN);
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	switch (state) {
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_HEAVY_SIN_READY_BODY);
			break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_HEAVY_SIN_ATTACK_BODY);
			sq_flashScreen(obj, 80, 100, 240, 150, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); //��?
			break;
		case 2:
			local ani = obj.getVar().GetAnimationMap("Seducer225", "Character/Priest/Seducer/ATAnimation/heavysin_demonization.ani");
			obj.setCurrentAnimation(ani);
			
			obj.sq_StartWrite();
			obj.sq_WriteDword(14);
			obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_HEAVY_SIN, -1, 0, 1.0));
			obj.sq_WriteDword(obj.sq_GetIntData(SKILL_HEAVY_SIN, 0));
			obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_HEAVY_SIN, 1, level));
			obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_HEAVY_SIN, 2, level));
			obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_HEAVY_SIN, 3, level));
			obj.sq_SendCreatePassiveObjectPacket(24384, 0, 120, 0, 0);

			obj.sq_StartWrite();
			obj.sq_WriteDword(15);
			obj.sq_WriteDword(obj.sq_GetIntData(SKILL_HEAVY_SIN, 0));
			obj.sq_SendCreatePassiveObjectPacket(24384, 0, 120, 0, 0);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onKeyFrameFlag_HeavySin(obj, flagIndex) {
	if (!obj)
		return false;

	local state = obj.getSkillSubState();
	switch (state) {
		case 1:
			if (flagIndex == 0) {
				sq_SetShake(obj, 2, 100);
				obj.sq_StartWrite();
				obj.sq_WriteDword(3);
				obj.sq_SendCreatePassiveObjectPacket(24240, 0, 120, 0, 0);

				obj.sq_StartWrite();
				obj.sq_WriteDword(4);
				obj.sq_SendCreatePassiveObjectPacket(24240, 0, 120, 0, 0);

				heavysin_ready_rose(obj);
			}
			break;
	}
	return true;
}

function heavysin_ready_rose(obj) {
	local heavysin_ready_rose = "character/priest/effect/animation/atheavysin/heavysin_ready_rose.ani";
	ATPriest_Create(obj, heavysin_ready_rose, ENUM_DRAWLAYER_NORMAL, 0, -2, 0, 0, 100, 0, 100, "heavysin_ready_rose");
}

function onEndCurrentAni_HeavySin(obj) {
	local state = obj.getSkillSubState();
	switch (state) {
		case 0:
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);

			obj.addSetStatePacket(STATE_HEAVY_SIN, pIntVec, STATE_PRIORITY_FORCE, false, "");

			break;
		case 1:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
		case 2:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
	}
}
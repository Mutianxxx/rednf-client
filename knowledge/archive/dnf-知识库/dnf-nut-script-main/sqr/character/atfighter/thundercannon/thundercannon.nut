
function checkExecutableSkill_thundercannon(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_THUNDERCANNON);
	if (isUse) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_THUNDERCANNON, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_thundercannon(obj) {
	if (!obj)
		return false;
	return true;
}


function onSetState_thundercannon(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	switch (substate) {
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATFIGHTER_ATTHUNDERCANNON_READY);
			obj.getVar("SpiralInhaleIs").setBool(0,false);
			break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATFIGHTER_ATTHUNDERCANNON);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_ATFIGHTER_THUNDERCANNON);
			obj.getVar("pos").clear_vector();
			obj.getVar("pos").push_vector(obj.getXPos());
			obj.getVar("pos").push_vector(70);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onProc_thundercannon(obj) {
	if (!obj) return;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 1:
			local pAni = obj.sq_GetCurrentAni();
			local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
			local startFrameIndex = 0;
			local endFrameIndex = 1;
			local currentT = sq_GetCurrentTime(pAni);
			if (frmIndex < startFrameIndex) {
				obj.setCurrentPos(obj.getVar("pos").get_vector(0), obj.getYPos(), obj.getZPos());
			} else if (frmIndex > startFrameIndex && frmIndex <= endFrameIndex) {
				local startX = obj.getVar("pos").get_vector(0);
				local maxD = obj.getVar("pos").get_vector(1);
				currentT = currentT - pAni.getDelaySum(0, startFrameIndex);
				local maxT = pAni.getDelaySum(startFrameIndex, endFrameIndex);
				if (currentT < maxT) {
					local v = sq_GetAccel(0, maxD, currentT, maxT, true);
					local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
					if (obj.isMovablePos(dstX, obj.getYPos())) {
						sq_setCurrentAxisPos(obj, 0, dstX);
					}
				}
			}
			break;
	}
}

function onEndCurrentAni_thundercannon(obj) {
	if (!obj) return;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 0:
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			obj.addSetStatePacket(STATE_THUNDERCANNON, pIntVec, STATE_PRIORITY_FORCE, false, "");
			break;
		case 1:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
	}
}


function onKeyFrameFlag_thundercannon(obj, flagIndex) {
	if (!obj)
		return false;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 1:
			if (flagIndex == 0) {
				obj.sq_PlaySound("R_MF_THUNDERCANNON");
			} else if (flagIndex == 1) {
				sq_flashScreen(obj, 20, 160, 250, 20, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				sq_SetMyShake(obj, 5, 100);
				obj.sq_StartWrite();
				obj.sq_WriteDword(20);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_THUNDERCANNON, -1, 0, 1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERCANNON, 0));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERCANNON, 1, sq_GetSkillLevel(obj, SKILL_THUNDERCANNON)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERCANNON, 3, sq_GetSkillLevel(obj, SKILL_THUNDERCANNON)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERCANNON, 2, sq_GetSkillLevel(obj, SKILL_THUNDERCANNON)));
				obj.sq_WriteDword(obj.sq_GetPowerWithPassive(SKILL_THUNDERCANNON, -1, 4, -1,1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERCANNON, 1)+3);
				obj.sq_SendCreatePassiveObjectPacket(24375, 0, 50, 0, 0);
			} else if (flagIndex == 2) {
				sq_SetMyShake(obj, 1, 330);
			}
			break;
	}
	return true;
}

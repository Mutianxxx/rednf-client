 
function checkExecutableSkill_SpearOfVictory(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_SPEAR_OF_VICTORY);

	if (isUse) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_SPEAR_OF_VICTORY);
		obj.addSetStatePacket(STATE_SPEAR_OF_VICTORY, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_SpearOfVictory(obj) {
	if (!obj) return false;

	return true;
}

function onSetState_SpearOfVictory(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	local id = sq_GetObjectId(obj);
	obj.setSkillSubState(state);

	switch (state) {
	case 0:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODY_READY);
		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODY_CHARGELOOP);
		obj.sq_StartWrite();
		obj.sq_WriteDword(49);
		obj.sq_WriteDword(id);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, -80, 0);
		break;
	case 2:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPEAR_OF_VICTORY_BODYSHOT_02);
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onKeyFrameFlag_SpearOfVictory(obj, flagIndex) {
	if (!obj) return;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
	case 0:
		if (flagIndex == 0) {
			
		}
		break;
	case 2:
		if (flagIndex == 1) {
			
		}
		break;
	}
	return true;
}

function onProc_SpearOfVictory(obj) {
	if (!obj) return;
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
	case 0:
		if (!obj.isDownSkillLastKey()) //åýÍýÙÒêóäÎù»äÎËõûäíºßÒ÷¾ïÒãÁÐï>=?ö¢õÌÓÞãÁÊà
		{
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);

			obj.addSetStatePacket(STATE_SPEAR_OF_VICTORY, pIntVec, STATE_PRIORITY_FORCE, false, "");

			obj.sq_StartWrite();
			obj.sq_WriteDword(52);
			obj.sq_WriteDword(id);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 150);
		}
		else if (currentT >= obj.sq_GetIntData(SKILL_SPEAR_OF_VICTORY, 0)) {

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);

			obj.addSetStatePacket(STATE_SPEAR_OF_VICTORY, pIntVec, STATE_PRIORITY_FORCE, false, "");

		}
		break;
	case 1:
		if (!obj.isDownSkillLastKey() || currentT >= obj.sq_GetIntData(SKILL_SPEAR_OF_VICTORY, 1)) {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);

			obj.addSetStatePacket(STATE_SPEAR_OF_VICTORY, pIntVec, STATE_PRIORITY_FORCE, false, "");
			if (currentT >= obj.sq_GetIntData(SKILL_SPEAR_OF_VICTORY, 0)) {
				obj.sq_StartWrite();
				obj.sq_WriteDword(51);
				obj.sq_WriteDword(id);
				obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 150);
			}
			else {
				obj.sq_StartWrite();
				obj.sq_WriteDword(52);
				obj.sq_WriteDword(id);
				obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 150);
			}
		}
		break;
	}
}

function onEndCurrentAni_SpearOfVictory(obj) {
	if (!obj) return;
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
	case 0:
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);

		obj.addSetStatePacket(STATE_SPEAR_OF_VICTORY, pIntVec, STATE_PRIORITY_FORCE, false, "");
		break;
	case 2:
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		break;
	}
}

function creatspearofvictory(obj, disX, disY, disZ) //
{
	local ani = sq_CreateAnimation("", "character/priest/effect/animation/atspearofvictory/speartchargeeff_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	sq_AddObject(obj, pooledObj, 2, false);

}
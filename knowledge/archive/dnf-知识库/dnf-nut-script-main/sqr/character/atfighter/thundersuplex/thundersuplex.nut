
function checkExecutableSkill_ThunderSuplex(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_THUNDERSUPLEX);

	if (isUse) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_THUNDERSUPLEX, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_ThunderSuplex(obj) {
	return true;
}


function onSetState_ThunderSuplex(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	switch (state) {
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATFIGHTER_THUNDERKICK);
			obj.getVar("SpiralInhaleIs").setBool(0,false);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_ThunderSuplex(obj) {
	if (!obj) return;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 0:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
	}
}


function onKeyFrameFlag_ThunderSuplex(obj, flagIndex) {
	if (!obj)
		return false;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 0:
			if (flagIndex == 1) {
				sq_SetMyShake(obj, 3, 180);
			} else if (flagIndex == 2) {
				local nenCount = obj.getMyPassiveObjectCount(21085);
				local nenBonus = obj.sq_GetLevelData(40, 5, sq_GetSkillLevel(obj, 40)) / 100.0 * nenCount;
				obj.sq_StartWrite();
				obj.sq_WriteDword(21);
				obj.sq_WriteDword(obj.sq_GetPowerWithPassive(SKILL_THUNDERSUPLEX, STATE_THUNDERSUPLEX, 0, -1,1.0 + nenBonus));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERSUPLEX, 2));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERSUPLEX, 1, sq_GetSkillLevel(obj, SKILL_THUNDERSUPLEX)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERSUPLEX, 2, sq_GetSkillLevel(obj, SKILL_THUNDERSUPLEX)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERSUPLEX, 3, sq_GetSkillLevel(obj, SKILL_THUNDERSUPLEX)));
				obj.sq_WriteDword(obj.sq_GetPowerWithPassive(SKILL_THUNDERSUPLEX, -1, 4, -1,1.0));
				obj.sq_SendCreatePassiveObjectPacket(24375, 0, 0, 0, 0);
			} else if (flagIndex == 3) {
				sq_flashScreen(obj, 1, 7, 18, 63, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			}
			break;
	}
	return true;
}

function crethunderkickfloor_light(obj, disX, disY, disZ, size) {

	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atfighter/animation/atthunderkick/thunderkickfloor_light.ani");

	local sizeRate = size.tofloat() / 100.0;
	ani.setImageRateFromOriginal(sizeRate, sizeRate);
	ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj, pooledObj, 2, false);
}

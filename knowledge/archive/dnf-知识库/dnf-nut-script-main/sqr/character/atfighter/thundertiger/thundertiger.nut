
function checkExecutableSkill_thundertiger(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_THUNDERTIGER);

	if (isUse) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_THUNDERTIGER, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_thundertiger(obj) {
	if (!obj)
		return false;

	return true;
}


function onSetState_thundertiger(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	switch (state) {
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATFIGHTER_THUNDERTIGER_BODY);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onAfterSetState_thundertiger(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage){
		obj.getVar("SpiralInhaleIs").setBool(0,false);
		return;
	}
	if (obj.sq_GetVectorData(datas, 0) == 0) {
		if (obj.getVar("SpiralInhaleEnergy").size_vector() == 0) 
			obj.getVar("SpiralInhaleEnergy").push_vector(0);
		local spiralInhaleEnergy = obj.getVar("SpiralInhaleEnergy").get_vector(0);
		if (spiralInhaleEnergy >= 200) 
			obj.getVar("SpiralInhaleEnergy").set_vector(0, spiralInhaleEnergy - 200);
		else 
			CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
	}
}

function onEndCurrentAni_thundertiger(obj) {
	if (!obj) return;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 0:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			break;
	}
}

function onKeyFrameFlag_thundertiger(obj, flagIndex) {
	if (!obj)
		return false;
	local state = obj.getSkillSubState();
	local id = sq_GetObjectId(obj);
	switch (state) {
		case 0:
			if (flagIndex == 0) {
				sq_flashScreen(obj, 600, 230, 330, 127, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

			} else if (flagIndex == 1) {

				obj.sq_PlaySound("R_MF_THUNDERTIGER_02");
				
				obj.sq_StartWrite();
				obj.sq_WriteDword(22);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_THUNDERTIGER, -1, 0, 1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 0));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 2, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 5, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 3, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(obj.sq_GetPowerWithPassive(SKILL_THUNDERTIGER, -1, 4, -1,1.0));
				
				obj.sq_SendCreatePassiveObjectPacket(24375, 0, 126, 0, 0);
				
				obj.sq_StartWrite();
				obj.sq_WriteDword(23);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_THUNDERTIGER, -1, 1, 1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 0));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 2, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 5, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(sq_GetLevelData(obj, SKILL_THUNDERTIGER, 3, sq_GetSkillLevel(obj, SKILL_THUNDERTIGER)));
				obj.sq_WriteDword(obj.sq_GetPowerWithPassive(SKILL_THUNDERTIGER, -1, 4, -1,1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 1));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 2));
				obj.sq_SendCreatePassiveObjectPacket(24375, 0, 126, 0, 0);
				
				obj.sq_StartWrite();
				obj.sq_WriteDword(24);
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 1));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_THUNDERTIGER, 2));
				obj.sq_SendCreatePassiveObjectPacket(24375, 0, 126, 0, 0);
			}
			break;
	}
	return true;
}

function crethundertigerbottomend_00(obj, disX, disY, disZ, size) {

	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atfighter/animation/atthundertiger/thundertigerbottomend_00.ani");

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

function crethundertigerattback_00(obj, disX, disY, disZ, size) {

	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/atthundertiger/thundertigerattback_00.ani");

	local sizeRate = size.tofloat() / 100.0;
	ani.setImageRateFromOriginal(sizeRate, sizeRate);
	ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	sq_AddObject(obj, pooledObj, 2, false);
}

function crethundertigerattbottom_00(obj, disX, disY, disZ, size) {

	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/atthundertiger/thundertigerattbottom_00.ani");

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

function crethundertigerfrontend_00(obj, disX, disY, disZ, size) {

	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/atthundertiger/thundertigerfrontend_00.ani");

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

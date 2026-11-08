function checkExecutableSkill_timetape(obj) {
	if (!obj) return false;
	if (!CheckEnemyTimeTapeAppend(obj)) {
		local b_useskill = obj.sq_IsUseSkill(SKILL_TIMETAPE);

		if (b_useskill) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_TIMETAPE, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
}

function createTimeTapHit_0(obj, damager) {

	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/timetape/hit/hit_start_1.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function createTimeTapHit_End(obj, damager) {

	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/timetape/hit/hit_end.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function createTimeTapMoveBack_End(obj, damager) {

	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/timetape/move/move_end_back.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() - 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function createTimeTapMoveFront_End(obj, damager) {

	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/timetape/move/move_end_front.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function createTimeTapeFloor(obj) {

	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atmage/animation/atcorridor/start/corridor_start_floor.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(obj.getXPos(), obj.getYPos() - 1, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function checkCommandEnable_timetape(obj) {

	if (!obj) return false;
	return true;
}


function onSetState_TIMETAPE(obj, state, datas, isResetTimer) {
	if (!obj) return;

	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

	if (state == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TIMETAPE_CASTING);
		if (obj.isMyControlObject())
			sq_flashScreen(obj, 560, 80, 0, 204, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		local castTime = sq_GetCastTime(obj, SKILL_TIMETAPE, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);
		sq_StartDrawCastGauge(obj, castTime, true);
	} else if (state == 1) {

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TIMETAPE_START);
		if (!obj.isMyControlObject())
			return false;
		sq_SetMyShake(obj, 9, 160);
		createTimeTapeFloor(obj);
		sq_flashScreen(obj, 0, 80, 160, 51, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		local power = obj.sq_GetPowerWithPassive(SKILL_TIMETAPE, STATE_TIMETAPE, 0, -1, 1.0);
		local apSaveT = sq_GetLevelData(obj, SKILL_TIMETAPE, 1, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
		local sfProc = sq_GetLevelData(obj, SKILL_TIMETAPE, 2, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
		local sfLevel = sq_GetLevelData(obj, SKILL_TIMETAPE, 3, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
		local sfTime = sq_GetLevelData(obj, SKILL_TIMETAPE, 4, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
		obj.sq_StartWrite();
		obj.sq_WriteDword(power); // attackBonusRate
		obj.sq_WriteDword(101); // attackBonusRate
		obj.sq_WriteDword(obj.sq_GetIntData(SKILL_TIMETAPE, 0)); // attackBonusRate
		obj.sq_WriteDword(sfProc);
		obj.sq_WriteDword(sfLevel);
		obj.sq_WriteDword(sfTime);
		obj.sq_WriteDword(apSaveT);
		sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
}

function CheckEnemyTimeTapeAppend(obj) {
	if (!obj) return false;
	local flag = false;
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE)) {
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/timetape/ap_timetape.nut")) {
				flag = true;
				createTimeTapHit_End(obj, activeObj);
				local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_TIMETAPE, 1));
				local XPos = activeObj.sq_findNearLinearMovableXPos(posX, obj.getYPos(), posX, obj.getYPos(), 50);
				activeObj.setCurrentPos(XPos, obj.getYPos(), activeObj.getZPos());
				CNSquirrelAppendage.sq_RemoveAppendage(activeObj, "character/atmage/timetape/ap_timetape.nut");
				local sfProc = sq_GetLevelData(obj, SKILL_TIMETAPE, 2, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
				local sfLevel = sq_GetLevelData(obj, SKILL_TIMETAPE, 3, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
				local sfTime = sq_GetLevelData(obj, SKILL_TIMETAPE, 4, sq_GetSkillLevel(obj, SKILL_TIMETAPE));
				sq_sendSetActiveStatusPacket(activeObj, obj, ACTIVESTATUS_HOLD, sfProc.tofloat(), sfLevel, false, sfTime);
				createTimeTapMoveFront_End(obj, activeObj);
				createTimeTapMoveBack_End(obj, activeObj);
				sq_SetMyShake(obj, 9, 160);
			}
		}
	}
	return flag;
}


function onEndCurrentAni_TIMETAPE(obj) {
	if (!obj.isMyControlObject())
		return false;
	local state = obj.getSkillSubState();
	if (state == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_TIMETAPE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if (state == 1) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, false);
	}
}

function checkExecutableSkill_null85(obj) {
	if (!obj) return false;
	local isUseSkill = obj.sq_IsUseSkill(SKILL_NULL85);
	if (isUseSkill) {
		if (!isEventHorizen(obj)) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
		} else {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
		}
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_null85(obj) {
	if (!obj)
		return false;
	return true;
}

function createNull85NewDust1(obj, x, y, z) {
	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atmage/animation/atforbiddenparty/background/nndust_a.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX, obj.getYPos() + y, obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createNull85MagicCircle(obj, x, y, z) {
	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atmage/animation/atforbiddenparty/magiccircle/fpalaser_magiccircle01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX, obj.getYPos() + y, obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createNull85NewDust2(obj, x, y, z) {
	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/atmage/animation/atforbiddenparty/background/nndust_b.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX, obj.getYPos() + y, obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createNull85EnemyMoveEffect(obj, x, y, z) {
	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/atforbiddenparty/normal/background/nnenemymove.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX, obj.getYPos() + y, obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function onSetState_NULL85(obj, state, datas, isResetTimer) {
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	local job = getNyarly(obj);
	obj.sq_StopMove();
	if (state == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_CASTING_1);
		sq_flashScreen(obj, 100, 2000, 1000, 127, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_NULL85, 0));
		if (!job) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(1); // attackBonusRate
			obj.sq_SendCreatePassiveObjectPacket(24342, 0, 100, 1, 0);
		} else {
			job.getVar("state").clear_vector();
			job.getVar("state").push_vector(10);
			job.getVar("subState").clear_vector();
			job.getVar("subState").push_vector(0);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			job.addSetStatePacket(20, pIntVec, STATE_PRIORITY_AUTO, false, "");
		}
	} else if (state == 1) {
		holdAllEnemyNyraly(obj);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_CASTING_2);
		createNull85MagicCircle(obj, 300, 1, 0);
		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector(obj.getXPos());
		obj.getVar("pos").push_vector(obj.getYPos());
		obj.getVar("pos").push_vector(obj.getZPos());

	} else if (state == 2) {
		sq_flashScreen(obj, 100, 3500, 1000, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_CASTING_3);
	} else if (state == 3) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_CASTING_4);
		local power = obj.sq_GetPowerWithPassive(SKILL_NULL85, STATE_NULL85, 1, -1, 1.0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(6);
		sq_BinaryWriteDword(power);
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_NULL85, 1));
		obj.sq_SendCreatePassiveObjectPacket(24339, 0, 300, 1, 0);
	} else if (state == 4) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_EVENTHORIZEN_CASTING);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("efffect").clear_obj_vector();

		if (!job) {
			obj.sq_StartWrite();
			obj.sq_WriteDword(2); // attackBonusRate
			obj.sq_SendCreatePassiveObjectPacket(24342, 0, 100, 1, 0);
		} else {
			job.getVar("state").clear_vector();
			job.getVar("state").push_vector(11);
			job.getVar("subState").clear_vector();
			job.getVar("subState").push_vector(0);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			job.addSetStatePacket(21, pIntVec, STATE_PRIORITY_AUTO, false, "");
		}
	} else if (state == 5) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_EVENTHORIZEN_NULL);
		createNull85_Shoot2(obj);
		createNull85_Shoot3(obj);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
	} else if (state == 6) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NULL85_EVENTHORIZEN_END);
	}
}

function onKeyFrameFlag_NULL85(obj, flagIndex) {
	local state = obj.getSkillSubState();
	if (state == 4) {
		if (obj.getVar("flag").get_vector(flagIndex) == 0) {
			obj.getVar("flag").set_vector(flagIndex, 1);
			if (flagIndex == 1) {
				sq_flashScreen(obj, 200, 6000, 2000, 178, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			}
		}
	} else if (state == 5) {
		if (obj.getVar("flag").get_vector(flagIndex) == 0) {
			obj.getVar("flag").set_vector(flagIndex, 1);
		}
	}

}

function holdAllEnemyNyraly(obj) {
	local job = getNyarly(obj);
	if (job) {
		local objectManager = obj.getObjectManager();
		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
			local object = objectManager.getCollisionObject(i);
			if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && object.isInDamagableState(obj)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
				job.getVar("dama").push_obj_vector(activeObj);
				createNull85EnemyMoveEffect(activeObj, 0, 1, 0);
				local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_NULL85, false, "character/atmage/null85/ap_null85.nut", true);
				if (masterAppendage) {
					sq_HoldAndDelayDie(activeObj, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL, masterAppendage);
					masterAppendage.sq_SetValidTime(4500);
				}
			}
		}
	}
}

function getScrollBasisPos_NULL85(obj) {
	local state = obj.getSkillSubState();
	local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 300);
    local startX = obj.getVar("pos").get_vector(0);
	if (state == 0) {} else if (state == 1) {
		local startY = obj.getVar("pos").get_vector(1);
		local startZ = obj.getVar("pos").get_vector(2);

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);

		local stateTimer = obj.sq_GetStateTimer();
		local xPos = sq_GetUniformVelocity(startX, destX, stateTimer, delay);
		local zPos = sq_GetUniformVelocity(0, 100, stateTimer, delay);
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), zPos);
		return true;
	} else if (state == 2) {
		obj.sq_SetCameraScrollPosition(destX, obj.getYPos(), 100);
		return true;
	} else if (state == 3) {

		local ani2 = obj.sq_GetCurrentAni();
		local delay2 = ani2.getDelaySum(false);
		local stateTimer = obj.sq_GetStateTimer();
		local xPos = sq_GetUniformVelocity(destX, startX, stateTimer, delay2);
		local zPos = sq_GetUniformVelocity(100, 0, stateTimer, delay2);
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), zPos);
		return true;
	} else if (state == 4) {
		obj.sq_SetCameraScrollPosition(obj.getXPos(), obj.getYPos(), 200);
		return true;
	}
	return false;
}

function onEndCurrentAni_NULL85(obj) {
	local state = obj.getSkillSubState();
	if (state == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);
	} else if (state == 1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);
	} else if (state == 2) {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);
	} else if (state == 3) {

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	} else if (state == 4) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(5);
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);

	} else if (state == 5) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(6);
		obj.sq_AddSetStatePacket(STATE_NULL85, STATE_PRIORITY_USER, true);

	} else if (state == 6) {

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}

}

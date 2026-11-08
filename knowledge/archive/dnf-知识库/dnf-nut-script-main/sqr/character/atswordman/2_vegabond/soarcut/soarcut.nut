
function checkExecutableSkill_Soarcut(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(213);
	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_Soarcut(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_Soarcut(obj, state, datas, CQklE7981XW1XEOF) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	local count = sq_GetIntData(obj, 213, 5) / 2;
	count = count.tointeger();
	switch (substate) {
		case 0:
			obj.sq_StopMove();
			obj.getVar("Soarcut").clear_obj_vector();
			obj.getVar("soarcutdamager").clear_obj_vector();
			obj.sq_SetCurrentAnimation(552);
			obj.sq_SetCurrentAttackInfo(156);
			local bonusRate = obj.sq_GetBonusRateWithPassive(213, -1, 0, getATSwordmanBonus(obj, 1.0, 213));
			obj.sq_SetCurrentAttackBonusRate(bonusRate);
			break;
		case 1:
			obj.sq_ZStop();
			obj.sq_SetCurrentAnimation(551);
			obj.sq_SetCurrentAttackInfo(154);
			local bonusRate = obj.sq_GetBonusRateWithPassive(213, -1, 1, getATSwordmanBonus(obj, 1.0, 213));
			obj.sq_SetCurrentAttackBonusRate(bonusRate);
			break;
		case 2:
			obj.sq_SetCurrentAnimation(544);
			obj.sq_SetCurrentAttackInfo(154);
			local bonusRate = obj.sq_GetBonusRateWithPassive(213, -1, 2, getATSwordmanBonus(obj, 1.0, 213));
			obj.sq_SetCurrentAttackBonusRate(bonusRate);
			local aniDelay = sq_GetDelaySum(sq_GetCurrentAnimation(obj)) / count;
			aniDelay = aniDelay.tointeger();
			obj.setTimeEvent(1, aniDelay, count, true);
			break;
		case 3:
			obj.sq_SetCurrentAnimation(546);
			obj.sq_SetCurrentAttackInfo(155);
			local bonusRate = obj.sq_GetBonusRateWithPassive(213, -1, 2, getATSwordmanBonus(obj, 1.0, 213));
			obj.sq_SetCurrentAttackBonusRate(bonusRate);
			local atktime = 120 / count;
			atktime = atktime.tointeger();

			obj.setTimeEvent(0, atktime, count, true);
			obj.setTimeEvent(2, 123, 1, false);
			break;
		case 4:
			obj.sq_SetCurrentAnimation(549);
			obj.sq_SetCurrentAttackInfo(155);
			local bonusRate = obj.sq_GetBonusRateWithPassive(213, -1, 3, getATSwordmanBonus(obj, 1.0, 213));
			obj.sq_SetCurrentAttackBonusRate(bonusRate);
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Soarcut(obj) {
	if (!obj) return;
	local substate = obj.getSkillSubState();
	switch (substate) {
		case 0:
			if (obj.getVar("Soarcut").get_obj_vector_size() < 1) {
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
			} else {
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1);
				obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
			}
			break;
		case 1:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
		case 2:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);
			obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
		case 3:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(4);
			obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
		case 4:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
	}
}

function onAttack_Soarcut(obj, damager, boundingBox, isStuck) {
	if (!obj || isStuck) return false;
	local substate = obj.getSkillSubState();
	switch (substate) {
		case 0:
			if (sq_IsHoldable(obj, damager) && sq_IsGrabable(obj, damager) && !sq_IsFixture(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
				obj.getVar("soarcutdamager").push_obj_vector(damager);
				obj.getVar("Soarcut").push_obj_vector(damager);
				local append = "character/atswordman/2_vegabond/soarcut/ap_soarcut.nut";
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, append, true);
				if (appendage) {
					sq_HoldAndDelayDie(damager, obj, true, false, true, 0, 0, ENUM_DIRECTION_NEUTRAL, appendage);
					sq_MoveToAppendageForce(damager, obj, obj, 100, 0, 200, 160, true, appendage, true);
					appendage.getAppendageInfo().setValidTime(1000);
				}
			}
			break;
		case 2:
			if (sq_IsHoldable(obj, damager) && sq_IsGrabable(obj, damager) && !sq_IsFixture(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
				obj.getVar("soarcutdamager").push_obj_vector(damager);
				obj.getVar("Soarcut").push_obj_vector(damager);
				local append = "character/atswordman/2_vegabond/soarcut/ap_soarcut.nut";
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, append, true);
				if (appendage) {
					sq_HoldAndDelayDie(damager, obj, true, false, true, 0, 0, ENUM_DIRECTION_NEUTRAL, appendage);
					sq_MoveToAppendageForce(damager, obj, obj, 100, 0, 200, 160, true, appendage, true);
					appendage.getAppendageInfo().setValidTime(1000);
				}
			}
			break;
	}
}

function onTimeEvent_Soarcut(obj, index, count) {
	if (!obj) return false;
	local append = "character/atswordman/2_vegabond/soarcut/ap_soarcut.nut";
	switch (index) {
		case 1:
			obj.resetHitObjectList();
			local sq_var = obj.getVar("Soarcut");
			local objectsSize = sq_var.get_obj_vector_size();
			for (local i = 0; i < objectsSize; ++i) {
				local aim = sq_var.get_obj_vector(i);
				if (aim) {
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(aim, obj, -1, false, append, true);
					if (appendage) {
						sq_HoldAndDelayDie(aim, obj, true, false, true, 0, 0, sq_GetOppositeDirection(obj.getDirection()), appendage);
						sq_MoveToAppendageForce(aim, obj, obj, 100, 0, 0, 10, true, appendage, true);
						appendage.getAppendageInfo().setValidTime(500);
					}
				}
			}
			break;
		case 0:
			obj.resetHitObjectList();
			local sq_var = obj.getVar("Soarcut");
			local objectsSize = sq_var.get_obj_vector_size();
			for (local i = 0; i < objectsSize; ++i) {
				local aim = sq_var.get_obj_vector(i);
				if (aim) {
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(aim, obj, -1, false, append, true);
					if (appendage) {
						sq_HoldAndDelayDie(aim, obj, true, false, true, 250, 100, sq_GetOppositeDirection(obj.getDirection()), appendage);
						sq_MoveToAppendageForce(aim, obj, obj, 100, 0, 0, 10, true, appendage, true);
						if (count = sq_GetIntData(obj, 213, 5) / 2 - 1)
							appendage.getAppendageInfo().setValidTime(30);
						else
							appendage.getAppendageInfo().setValidTime(50);
					}
				}
			}
			break;
		case 2:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(4);
			obj.sq_AddSetStatePacket(213, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
	}
}

function onEndState_Soarcut(obj, newState) {
	if (!obj) return
	if (newState != 213) {
		local sq_var = obj.getVar("soarcutdamager");
		local objectsSize = sq_var.get_obj_vector_size();
		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (damager) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atswordman/2_vegabond/soarcut/ap_soarcut.nut");
			}
		}
		obj.getVar("soarcutdamager").clear_obj_vector();
	}
}

function onProc_Soarcut(obj) {
	if (!obj) return
	local substate = obj.getSkillSubState()
	switch (substate) {
		case 1:
			local timer = obj.sq_GetStateTimer()
			local accel = sq_GetAccel(obj.getZPos(), 200, timer, 200, false)
			sq_setCurrentAxisPos(obj, 2, accel)
			break
		case 3:
			local timer = obj.sq_GetStateTimer()
			local accel = sq_GetAccel(obj.getZPos(), 0, timer, 100, false)
			sq_setCurrentAxisPos(obj, 2, accel)
			break
	}
}
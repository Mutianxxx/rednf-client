
function checkExecutableSkill_mage_sestoelemento(obj) {
	if (!obj) return false;
	local isUsed = obj.sq_IsUseSkill(253);
	if (isUsed) {
		obj.sq_IsEnterSkillLastKeyUnits(253);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(253, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_mage_sestoelemento(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND) {
		return true;
	}
	if (state == STATE_ATTACK) {
		return obj.sq_IsCommandEnable(253);
	}
	return true;
}

function onSetState_mage_sestoelemento(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	switch (substate) {
	case 0:
		obj.sq_SetCurrentAnimation(120);
		local skill_level = sq_GetSkillLevel(obj, 253);
		local castTime = sq_GetCastTime(obj, 253, skill_level);
		sq_StartDrawCastGauge(obj, castTime, true);

		local mageshow_level = sq_GetSkillLevel(obj, 2);

		local mageshowpre = 1 - sq_GetLevelData(obj, 2, 3, mageshow_level).tofloat() / 1000;
		if (mageshowpre < 0) {
			mageshowpre = 0;
		}
		local skillchargetime = obj.sq_GetLevelData(253, 5, skill_level);
		if (isShowTime(obj)) {
			skillchargetime = mageshowpre * obj.sq_GetLevelData(253, 5, skill_level).tofloat();
		}
		local chargeTime = skillchargetime.tointeger();
		local ani = obj.getCurrentAnimation();
		local delayLong = ani.getDelaySum(false);

		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		local delay = ani.getDelaySum(false);
		local delayPer = delay.tofloat() / delayLong.tofloat();
		local speed = (castTime.tofloat() * delayPer).tointeger();
		obj.getVar().setBool(0, false);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(speed);
		obj.getVar().push_vector(chargeTime);
		break;
	case 1:
		local chargeTime = obj.sq_GetVectorData(datas, 1);
		local castTime = obj.getVar().get_vector(0);
		local delay = obj.getVar().get_vector(1);
		obj.sq_SetCurrentAnimation(119);
		local skill_level = sq_GetSkillLevel(obj, 253);
		local skillData3 = obj.sq_GetLevelData(253, 3, skill_level);
		local skillData4 = obj.sq_GetLevelData(253, 4, skill_level);
		local chargePer = sq_GetUniformVelocity(skillData3, skillData4, chargeTime - castTime, delay);
		obj.getVar().clear_vector();
		obj.getVar().push_vector(chargePer);
		obj.sq_PlaySound("WZ_SESTOELEMENTO_CAST");
		break;
	case 2:
		obj.sq_SetCurrentAnimation(121);
		obj.sq_PlaySound("WZ_SESTOELEMENTO");
		break;
	case 3:
		obj.sq_SetCurrentAnimation(122);
		break;
	}
	if (substate != 0) {
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
}

function onKeyFrameFlag_mage_sestoelemento(obj, index) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	switch (substate) {
		case 1:
			if (index == 2) {
				local skillLevel = sq_GetSkillLevel(obj, 253);
				obj.sq_StartWrite();
				obj.sq_WriteDword(253);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(253, 253, 1, 1.0));
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(253, 253, 2, 1.0));
				obj.sq_WriteDword(obj.sq_GetLevelData(253, 0, skillLevel));
				obj.sq_WriteDword(obj.getVar().get_vector(0));
				obj.sq_SendCreatePassiveObjectPacket(24372, 0, 290, -150, 0);
			}
			break;
		case 3:
			if (index == 1) {
				if (obj.sq_IsMyControlObject()) {
					local myPObjCount = obj.getMyPassiveObjectCount(24372);
					if (myPObjCount > 0) {
						for (local i = 0; i < myPObjCount; i++) {
							local myPassiveObj = obj.getMyPassiveObject(24372, i);
							if (!myPassiveObj)
								continue;
							if (myPassiveObj.getVar("skill").get_vector(0) == 253 && myPassiveObj.getVar("state").get_vector(0) != 10) {
								local IntVector = sq_GetGlobalIntVector();
								sq_IntVectorClear(IntVector);
								myPassiveObj.addSetStatePacket(10, IntVector, STATE_PRIORITY_AUTO, false, "");
							}
						}
					}
				}
			}
			break;
	}
	return true;
}

function onEndState_mage_sestoelemento(obj, newState) {
	if (!obj) return;
	if (newState != 253) {
		sq_EndDrawCastGauge(obj);
	}
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_chargingeffect.nut")) {
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/appendage/ap_chargingeffect.nut");
	}
}

function onProcCon_mage_sestoelemento(obj) {
	if (!obj) return;
	local substate = obj.getSkillSubState();

	if (substate == 1) {
		local pAni = obj.sq_GetCurrentAni();
		local currentCastT = sq_GetCurrentTime(pAni);
		local myPObjCount = obj.getMyPassiveObjectCount(24372);
		local mySestoCount = 0;
		if (myPObjCount > 0) {
			for (local i = 0; i < myPObjCount; i++) {
				local myPassiveObj = obj.getMyPassiveObject(24372, i);
				if (!myPassiveObj || !myPassiveObj.isMyControlObject()) continue;
				if (myPassiveObj.getVar("skill").get_vector(0) == 253) {
					mySestoCount++;
				}
			}
		}
		if (mySestoCount == 0 && currentCastT > 200) {
			local skillLevel = sq_GetSkillLevel(obj, 253);
			obj.sq_StartWrite();
			obj.sq_WriteDword(253);
			obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(253, 253, 1, 1.0));
			obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(253, 253, 2, 1.0));
			obj.sq_WriteDword(obj.sq_GetLevelData(253, 0, skillLevel));
			obj.sq_WriteDword(obj.getVar().get_vector(0));
			obj.sq_SendCreatePassiveObjectPacket(24372, 0, 290, -150, 0);
		}
	}
	else if (substate == 0) {
		local maxCharge = obj.getVar().get_vector(0);
		local stateTimer = obj.sq_GetStateTimer();
		if (stateTimer >= maxCharge) {
			if (obj.isDownSkillLastKey() || sq_IsKeyDown(93, ENUM_SUBKEY_TYPE_ALL)) {
				if (obj.getVar().getBool(0) == false) {
					sq_BinaryStartWrite();
					sq_BinaryWriteWord(1);
					sq_BinaryWriteDword(obj.getVar().get_vector(1));
					sq_SendChangeSkillEffectPacket(obj, 253);
					obj.getVar().setBool(0, true);
				}
				moveCharge(obj);
			}
			else {
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1);
				obj.sq_IntVectPush(stateTimer);
				obj.sq_AddSetStatePacket(253, STATE_PRIORITY_USER, true);
			}
		}
	}
}

function onEndCurrentAni_mage_sestoelemento(obj) {
	if (!obj) return;
	if (!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState();
	if (substate == 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(253, STATE_PRIORITY_USER, true);
	}
	else if (substate == 3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function getScrollBasisPos_mage_sestoelemento(obj) {
	if (!obj) return;
	if (!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState();
	switch (substate) {
	case 1:
	case 2:
		local currentTime = (substate == 1) ? obj.sq_GetStateTimer() : 200;
		local xPos = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), sq_GetUniformVelocity(0, 300, currentTime, 200));
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), 0);
		return true;
	case 3:
		local ani = obj.sq_GetCurrentAni();
		local currentTime = sq_GetCurrentTime(ani);
		local delay = ani.getDelaySum(0, 0);
		local xPos = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), sq_GetUniformVelocity(380, 0, currentTime, delay));
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), 0);
		return true;
	}
	return false;
}
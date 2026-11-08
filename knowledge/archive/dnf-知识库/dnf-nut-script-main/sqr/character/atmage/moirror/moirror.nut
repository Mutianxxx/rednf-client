//
//flag 1 flash 0 80 80 76 255 255 255
//shake 2 200

function checkExecutableSkill_moirror(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_MOIRROR);

	if (isUse) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_moirror(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_MOIRROR(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	//obj.setSkillSubState(state);
	obj.sq_StopMove();
	if (isEventHorizen(obj)) {
		state = 7;
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(7);
		removeEventHorizen(obj);
	}
	local posX = 0; //sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	local posY = 0;
	local posZ = 0;
	if (state == 0) {

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_CASTING);

		local castTime = sq_GetCastTime(obj, SKILL_MOIRROR, sq_GetSkillLevel(obj, SKILL_MOIRROR));
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);

	} else if (state == 1) {
		local tar = obj.getVar("dama").get_obj_vector(0);

		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), -25);
		posY = tar.getYPos() + 1;
		posZ = 0;
		if(sq_IsHoldable(obj, tar)){
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_MOIRROR, false, "character/atmage/moirror/ap_moirror.nut", true);
			if (masterAppendage) {
				sq_HoldAndDelayDie(tar, obj, true, false, false, 200, 200, ENUM_DIRECTION_NEUTRAL, masterAppendage);
			}
		}
		createDashEffectMoirror(obj);
		createDashEffectMoirrorPortal(obj);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_RUN);
		setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_MOIRROR, 0));
	} else if (state == 2) {
		local tar = obj.getVar("dama").get_obj_vector(0);
		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), 75);
		posY = tar.getYPos() + 1;
		posZ = tar.getObjectHeight() / 2 + 15;
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_ATK1);
	} else if (state == 3) {
		local tar = obj.getVar("dama").get_obj_vector(0);
		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), 50);
		posY = tar.getYPos() + 1;
		posZ = tar.getObjectHeight() / 2 + 30;
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_ATK2);
	} else if (state == 4) {
		local tar = obj.getVar("dama").get_obj_vector(0);
		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), 100);
		posY = tar.getYPos() + 1;
		posZ = 0;
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_ATK3);
	} else if (state == 5) {
		local tar = obj.getVar("dama").get_obj_vector(0);
		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), 55);
		posY = tar.getYPos() + 1;
		posZ = 0;
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_ATK4);
	} else if (state == 6) {
		local tar = obj.getVar("dama").get_obj_vector(0);
		posX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), -150);
		posY = tar.getYPos() + 1;
		posZ = 0;
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_END);
	}
	else if (state == 7) 
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MOIRROR_CASTING);
		local castTime = sq_GetCastTime(obj, SKILL_MOIRROR, sq_GetSkillLevel(obj, SKILL_MOIRROR));
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);
		sq_StartDrawCastGauge(obj, castTime, true);
		setBreakSenseEnegry(obj, getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_MOIRROR, 1));
		local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_MOIRROR, STATE_MOIRROR, 1, -1, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);
		obj.sq_WriteDword(105);
		obj.sq_WriteDword(1);
		obj.sq_WriteDword(1);
		local targetObj = findAngleTargetWithParticleVoid(obj, 0, 360, -1);
		if (targetObj) {
			local disX = -45;
			if(obj.getDirection() == ENUM_DIRECTION_LEFT)
				disX = 45;
			sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, targetObj.getXPos() + disX, targetObj.getYPos(), 0);
		}
		else{
			obj.sq_SendCreatePassiveObjectPacket(24357, 0, 100, 1, 50);
		}
		obj.sq_SetShake(obj, 2, 200);
		sq_flashScreen(obj, 0, 80, 80, 76, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		createDashEffectMoirror(obj);
		createDashEffectMoirrorPortal(obj);
	}

	obj.getVar("pos").clear_vector();
	obj.getVar("pos").push_vector(posX);
	obj.getVar("pos").push_vector(posY);
	obj.getVar("pos").push_vector(posZ);

	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);

}

function createDashEffectMoirror(obj) {
	if (!obj) return;
	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/atkaleidoscope/run/kaleidoscope_run_bodydodge.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createBoomBack(obj, damager, ani) {
	if (!obj) return;
	local ani = sq_CreateAnimation("", ani);
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() - 1, damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createDashEffectMoirrorPortal(obj) {
	if (!obj) return;
	local ani = sq_CreateAnimation("", "character/mage/atanimation/als_ani/atkaleidoscope/run/run_portal.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

//flag 1 flash 0 80 80 76 255 255 255
//shake 2 200

function onKeyFrameFlag_MOIRROR(obj, flagIndex) {
	if (!obj) return;
	if (!obj.isMyControlObject()) return false;
	local state = obj.getVar("state").get_vector(0);
	if (obj.getVar("flag").get_vector(0) == 0) {
		obj.getVar("flag").set_vector(0, 1);
		local tar = obj.getVar("dama").get_obj_vector(0);
		if (state >= 4) {
			CNSquirrelAppendage.sq_RemoveAppendage(tar, "character/atmage/moirror/ap_moirror.nut");
		}
		if (state == 2) {
			createBoomBack(obj, tar, "character/mage/atanimation/als_ani/atkaleidoscope/attack/kaleidoscope_attack1_boomback.ani");
		} else if (state == 3) {
			createBoomBack(obj, tar, "character/mage/atanimation/als_ani/atkaleidoscope/attack/kaleidoscope_attack2_boom.ani");
		} else if (state == 4) {
			createBoomBack(obj, tar, "character/mage/atanimation/als_ani/atkaleidoscope/attack/kaleidoscope_attack3_boom.ani");
		} else if (state == 5) {
			createBoomBack(obj, tar, "character/mage/atanimation/als_ani/atkaleidoscope/attack/kaleidoscope_attack4_boomback.ani");
		}
		local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_MOIRROR, STATE_MOIRROR, 0, -1, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate); 
		obj.sq_WriteDword(105);
		obj.sq_WriteDword(state - 1); 
		obj.sq_WriteDword(0);
		sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, tar.getXPos(), tar.getYPos() + 1, tar.getObjectHeight() / 2);
		obj.sq_SetShake(obj, 2, 200); 
		sq_flashScreen(obj, 0, 80, 80, 76, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
}

function onProc_MOIRROR(obj) {
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state >= 1) {

		local tar = obj.getVar("dama").get_obj_vector(0);
		if (tar) {
			local posX = obj.getVar("pos").get_vector(0);
			local posY = obj.getVar("pos").get_vector(1);
			local posZ = obj.getVar("pos").get_vector(2);
			if (obj.isMovablePos(posX, posY)) {
				obj.setCurrentPos(posX, posY, posZ);
			}
		} else {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
		}
	}
}

function onEndCurrentAni_MOIRROR(obj) {
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) 
	{
		local targetObj = findAngleTargetWithParticleVoid(obj, 400, 180, 100);
		if (targetObj) {
			obj.getVar("dama").clear_obj_vector();
			obj.getVar("dama").push_obj_vector(targetObj);
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(1);
			obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
		} 
		else 
		{
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
		}
	}
	else if (state == 1) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
	} else if (state == 2) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(3);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
	} else if (state == 3) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
	} else if (state == 4) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(5);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
	} else if (state == 5) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(6);
		obj.sq_AddSetStatePacket(STATE_MOIRROR, STATE_PRIORITY_USER, false);
	} else if (state == 6) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
	} else if (state == 7) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
	}
}

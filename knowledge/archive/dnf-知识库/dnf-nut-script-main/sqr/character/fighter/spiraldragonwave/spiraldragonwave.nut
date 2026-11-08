function checkExecutableSkill_SpiralDragonWave(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_SPIRALDRAGONWAVE);

	if (isUse) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_SPIRALDRAGONWAVE);
		obj.sq_AddSetStatePacket(STATE_SPIRALDRAGONWAVE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SpiralDragonWave(obj) {
	return true;
}

function onSetState_SpiralDragonWave(obj, state, datas, isResetTimer) {
	local state = obj.getVar("state").get_vector(0);

	obj.sq_StopMove();

	if (state == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPIRALDRAGONWAVECHARGE_BODY);

		local castTime = obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 9);
		sq_StartDrawCastGauge(obj, castTime, true);

		obj.setTimeEvent(0, obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 4), 0, false);
		obj.setTimeEvent(1, obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 5), 0, false);

		obj.getVar("SpiralDragonWave_Grow").clear_vector();
		obj.getVar("SpiralDragonWave_Grow").push_vector(0);

		createSpiralDragonWaveCharge_Back(obj, 0, 0, 0);
		createSpiralDragonWaveCharge_Front(obj, 0, 0, 0);
	}
	else if (state == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPIRALDRAGONWAVE1ST_BODY);
	}
	else if (state == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPIRALDRAGONWAVE2ST_BODY);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onTimeEvent_SpiralDragonWave(obj, timeEventIndex, timeEventCount) {
	local state = obj.getVar("state").get_vector(0);

	if (state == 0) {
		if (timeEventIndex == 0) {
			obj.getVar("SpiralDragonWave_Grow").clear_vector();
			obj.getVar("SpiralDragonWave_Grow").push_vector(1);
		}
		else if (timeEventIndex == 1) {
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(1);
			obj.sq_AddSetStatePacket(STATE_SPIRALDRAGONWAVE, STATE_PRIORITY_USER, true);

			setVliadEffectSpiralDragonWavePowerPassiveobject(obj);
		}
	}
}

function onProc_SpiralDragonWave(obj) {
	local state = obj.getVar("state").get_vector(0);

	if (state == 0) {
		if (!obj.isDownSkillLastKey()) {
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(1);
			obj.sq_AddSetStatePacket(STATE_SPIRALDRAGONWAVE, STATE_PRIORITY_USER, true);

			setVliadEffectSpiralDragonWavePowerPassiveobject(obj);
		}
	}
}

function onEndCurrentAni_SpiralDragonWave(obj) {
	local state = obj.getVar("state").get_vector(0);

	if (state == 1) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_SPIRALDRAGONWAVE, STATE_PRIORITY_USER, true);
	}
	else if (state == 2) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_SpiralDragonWave(obj, flagIndex) {
	local state = obj.getVar("state").get_vector(0);

	local id = sq_GetObjectId(obj);

	local level = sq_GetSkillLevel(obj, SKILL_SPIRALDRAGONWAVE);
	local LightProb = sq_GetLevelData(obj, SKILL_SPIRALDRAGONWAVE, 2, level);
	local LightDuration = sq_GetLevelData(obj, SKILL_SPIRALDRAGONWAVE, 4, level);
	local LightDamage = obj.sq_GetPowerWithPassive(SKILL_SPIRALDRAGONWAVE, -1, 5, -1, 1.0);
	local LightLevel = sq_GetLevelData(obj, SKILL_SPIRALDRAGONWAVE, 3, level);
	
	if (state == 0) {
		if (flagIndex == 0) {
			obj.sq_PlaySound("SPIRALDRAGONWAVE_CAST");
		}
	}
	else if (state == 1) {
		if (flagIndex == 0) {
			obj.sq_PlaySound("SPIRALDRAGONWAVE_HOWLING");

			obj.sq_SetShake(obj, 1, 150);
			createSpiralDragonWave1stBack(obj, 100, 16, 0, 42);
			if (obj.getVar("SpiralDragonWave_Grow").get_vector(0) == 1) {
				local atk = 100;
				atk = atk + obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 6);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SPIRALDRAGONWAVE, STATE_SPIRALDRAGONWAVE, 0, atk.tofloat() / 100.0);

				obj.sq_StartWrite();
				obj.sq_WriteDword(21);
				obj.sq_WriteDword(id);
				obj.sq_WriteDword(attackBonusRate);
				obj.sq_WriteDword(LightProb);
				obj.sq_WriteDword(LightDuration);
				obj.sq_WriteDword(LightDamage);
				obj.sq_WriteDword(LightLevel);
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 9));
				obj.sq_SendCreatePassiveObjectPacket(24397, 0, 16, 0, 42);

				createSpiralDragonWave1stBack(obj, 100, 16, 0, 42);
			} else {

				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SPIRALDRAGONWAVE, STATE_SPIRALDRAGONWAVE, 0, 1.0);

				obj.sq_StartWrite();
				obj.sq_WriteDword(22);
				obj.sq_WriteDword(id);
				obj.sq_WriteDword(attackBonusRate);
				obj.sq_WriteDword(LightProb);
				obj.sq_WriteDword(LightDuration);
				obj.sq_WriteDword(LightDamage);
				obj.sq_WriteDword(LightLevel);
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 9));
				obj.sq_SendCreatePassiveObjectPacket(24397, 0, 16, 0, 42);

				createSpiralDragonWave1stBack(obj, 100, 16, 0, 42);
			}
		}
	}
	else if (state == 2) {
		if (flagIndex == 0) {
			obj.sq_PlaySound("SPIRALDRAGONWAVE_PUNCH");
			obj.sq_PlaySound("R_FT_SPIRALDRAGONWAVE");

			obj.sq_SetShake(obj, 5, 200);

			if (obj.getVar("SpiralDragonWave_Grow").get_vector(0) == 1) {
				local atk = 100;
				atk = atk + obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 6);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SPIRALDRAGONWAVE, STATE_SPIRALDRAGONWAVE, 1, atk.tofloat() / 100.0);

				obj.sq_StartWrite();
				obj.sq_WriteDword(23);
				obj.sq_WriteDword(id);
				obj.sq_WriteDword(attackBonusRate);
				obj.sq_WriteDword(LightProb);
				obj.sq_WriteDword(LightDuration);
				obj.sq_WriteDword(LightDamage);
				obj.sq_WriteDword(LightLevel);
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 9));
				obj.sq_SendCreatePassiveObjectPacket(24397, 0, 45, 0, 58);

				createSpiralDragonWave2stBack(obj, 100, 45, 0, 0);

			} else {

				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SPIRALDRAGONWAVE, STATE_SPIRALDRAGONWAVE, 0, 1.0);

				obj.sq_StartWrite();
				obj.sq_WriteDword(24);
				obj.sq_WriteDword(id);
				obj.sq_WriteDword(attackBonusRate);
				obj.sq_WriteDword(LightProb);
				obj.sq_WriteDword(LightDuration);
				obj.sq_WriteDword(LightDamage);
				obj.sq_WriteDword(LightLevel);
				obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SPIRALDRAGONWAVE, 9));
				obj.sq_SendCreatePassiveObjectPacket(24397, 0, 45, 0, 58);

				createSpiralDragonWave2stBack(obj, 100, 45, 0, 0);
			}
		}
	}
	return true;
}

function createSpiralDragonWaveCharge_Back(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/spiraldragonwave/spiraldragonwavecharge_back00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("SpiralDragonWave_Loop_End").push_obj_vector(pooledObj);
}

function createSpiralDragonWaveCharge_Front(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/spiraldragonwave/spiraldragonwavecharge_front00.ani.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("SpiralDragonWave_Loop_End").push_obj_vector(pooledObj);
}

function createSpiralDragonWave1stBack(obj, size, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/fighter/nenmaster/animation/spiraldragonwave/spiraldragonwave1stback_00.ani");
	local sizeRate = size.tofloat() / 100.0;
	ani.setImageRateFromOriginal(sizeRate, sizeRate);
	ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createSpiralDragonWave2stBack(obj, size, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "passiveobject/actionobject/new/fighter/nenmaster/animation/spiraldragonwave/spiraldragonwave2stback_00.ani");
	local sizeRate = size.tofloat() / 100.0;
	ani.setImageRateFromOriginal(sizeRate, sizeRate);
	ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function setVliadEffectSpiralDragonWavePowerPassiveobject(obj) {
	local var = obj.getVar("SpiralDragonWave_Loop_End");

	local objectsSize = var.get_obj_vector_size();

	for (local i = 0; i < objectsSize; ++i) {
		local effectObj = var.get_obj_vector(i);

		if (effectObj) {
			effectObj.setValid(false);
		}
	}
}

function onEndState_SpiralDragonWave(obj, new_state) {
	if (!obj) return;

	local state = obj.getVar("state").get_vector(0);

	if (new_state != STATE_SPIRALDRAGONWAVE) {
		setVliadEffectSpiralDragonWavePowerPassiveobject(obj);
	}
}
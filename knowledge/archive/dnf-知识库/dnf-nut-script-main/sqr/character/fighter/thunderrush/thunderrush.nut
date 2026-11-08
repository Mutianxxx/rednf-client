function checkExecutableSkill_ThunderRush(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_THUNDERRUSH);

	if (isUse) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_THUNDERRUSH);
		obj.sq_AddSetStatePacket(STATE_THUNDERRUSH, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ThunderRush(obj) {
	return true;
}

function onSetState_ThunderRush(obj, state, datas, isResetTimer) {
	local state = obj.getVar("state").get_vector(0);

	obj.sq_StopMove();

	if (state == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_THUNDERRUSHREADYBODY);
		createThunderRush_DashCharging_00(obj, 0, 0, 0);

	}
	else if (state == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_THUNDERRUSHDASHBODY_00);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_THUNDERRUSHPUSH);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_THUNDERRUSH, STATE_THUNDERRUSH, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

		local ThunderRush_len = 150;

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) ThunderRush_len = 0;
		if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) ThunderRush_len = 0;
		if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) ThunderRush_len = 200;
		if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) ThunderRush_len = 200;

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false) / 3;

		obj.getVar("ThunderRush_len").clear_vector();
		obj.getVar("ThunderRush_len").push_vector(ThunderRush_len);
		obj.getVar("ThunderRush_len").push_vector(delay);
		obj.getVar("ThunderRush_len").push_vector(obj.getXPos());

		createThunderRush_DashCharging_09(obj, 0, 0, 0);
		createThunderRushDashSprint_04(obj, 0, 0, 0);

		obj.setTimeEvent(0, 120, 0, true);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}

function onTimeEvent_ThunderRush(obj, timeEventIndex, timeEventCount) {
	local state = obj.getVar("state").get_vector(0);

	if (state == 1) {
		if (timeEventIndex == 0) {
			if (timeEventCount <= 2) {
				createThunderRush_SmokeA_00(obj, 0, 0, 50);
				createThunderRush_SmokeB_02(obj, -100, 0, 50);
				createThunderRush_SmokeC_00(obj, -150, 0, 50);
			}
		}
	}
}

function onProc_ThunderRush(obj) {
	local state = obj.getVar("state").get_vector(0);
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);

	if (state == 1) {
		local posX = obj.getVar("ThunderRush_len").get_vector(2);
		local delayT = obj.getVar("ThunderRush_len").get_vector(1);
		local ThunderRush_len = obj.getVar("ThunderRush_len").get_vector(0);

		local v = sq_GetAccel(0, ThunderRush_len, currentT, delayT, true);
		local srcX = posX;

		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);

		if (obj.isMovablePos(dstX, obj.getYPos())) {
			sq_setCurrentAxisPos(obj, 0, dstX);
		}
	}
}

function onEndCurrentAni_ThunderRush(obj) {
	local state = obj.getVar("state").get_vector(0);

	if (state == 0) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_THUNDERRUSH, STATE_PRIORITY_USER, true);
	}
	else if (state == 1) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_ThunderRush(obj, flagIndex) {
	local state = obj.getVar("state").get_vector(0);

	local id = sq_GetObjectId(obj);

	if (state == 0) {
		if (flagIndex == 0) {
			obj.sq_PlaySound("THUNDERRUSH_READY");
		}
	}
	else if (state == 1) {
		if (flagIndex == 0) {
			obj.sq_PlaySound("R_FT_THUNDERRUSH");
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_THUNDERRUSH, STATE_THUNDERRUSH, 0, 1.0);
			local size = obj.sq_GetIntData(SKILL_THUNDERRUSH, 4);
			obj.sq_StartWrite();
			obj.sq_WriteDword(20);
			obj.sq_WriteDword(id);
			obj.sq_WriteDword(attackBonusRate);
			obj.sq_WriteDword(size);
			obj.sq_SendCreatePassiveObjectPacket(24397, 0, 53, 0, 59);
		}
	}
	return true;
}

function createThunderRush_DashCharging_00(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushdashcharging_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createThunderRush_DashCharging_09(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushdashcharging_09.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createThunderRushDashSprint_04(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushdashsprint_04.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createThunderRush_SmokeA_00(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushsmokea_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createThunderRush_SmokeB_02(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushsmokeb_02.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createThunderRush_SmokeC_00(obj, disX, disY, disZ) {
	local ani = sq_CreateAnimation("", "character/fighter/effect/animation/thunderrush/thunderrushsmokec_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}
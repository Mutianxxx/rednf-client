function checkExecutableSkill_SwordGhost19(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_19);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_19, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost19(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function Dust_SwordGhost19_0(obj, disX, disY, disZ) {
	local sizeRate = 100;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ultimatecrossslash/endattacktrace_04.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function Dust_SwordGhost19_1(obj, disX, disY, disZ) {
	local sizeRate = 100;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ultimatecrossslash/endattack_03.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function Dust_SwordGhost19_2(obj, disX, disY, disZ) {
	local sizeRate = 100;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ultimatecrossslash/effect/light_01.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function onSetState_SwordGhost19(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_19_YI_JUE_CAST);
		obj.sq_SendCreatePassiveObjectPacket(260184, 0, 270, 1, 0);
		//sq_flashScreen(obj, 400, 2000, 800, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????

		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
		sq_SendCreatePassiveObjectPacketPos(obj, 260187, 0, xPos, yPos + 170, -1);

	}
	else if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_19_YI_JUE_ATTACK);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_19_YI_JUE_ATTACK); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_19, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
		setSwordGhostEnergy(obj, 0);
	}
}

function onAttack_SwordGhost19(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");

	local skillLevel = obj.sq_GetSkillLevel(123);

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 300, 150, 500); //???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, objindex, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_18:buff_count1:" + count1);
	}

}

function onEndCurrentAni_SwordGhost19(obj) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_19, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

	}

}

function onKeyFrameFlag_SwordGhost19(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		obj.sq_SetStaticMoveInfo(0, 3000, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	if (flagIndex == 2) {
		//obj.sq_SetShake(obj,30,300);//?????
		obj.sq_SendCreatePassiveObjectPacket(260185, 0, 0, 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(260188, 0, 0, -1, 0);
		Dust_SwordGhost19_0(obj, 0, 1, 0);
		Dust_SwordGhost19_1(obj, 0, 1, 0);
		Dust_SwordGhost19_2(obj, -73, 0, 95);
	}
	if (flagIndex == 3) {
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}

	return true;
}
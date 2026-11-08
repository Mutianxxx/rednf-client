function checkExecutableSkill_SwordGhost15(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_15);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_15, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost15(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost15(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_15_HUN_PO_CAST);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK1); //????ATK????

		if (isAppendApd_flag) {
			local gaugeValue_rate = setSwordGhost3State(obj);
			local hit_ex = setSwordGhost7hitEx(obj) / 3;
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat()); //??????????SKL.0?????????????????1.0??
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_15, -1, 0, 1.0);

			local hit = obj.sq_GetIntData(SKILL_SWORD_GHOST_7, 0);

			local count = hit + hit_ex.tointeger();
			obj.sq_SendCreatePassiveObjectPacket(26317, 0, -65, 1, 0);
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(126);
			sq_BinaryWriteDword(attackBonusRate);
			sq_BinaryWriteDword(100);
			sq_BinaryWriteDword(count);
			obj.sq_SendCreatePassiveObjectPacket(24370, 0, -65, 1, 0);

			obj.sq_SendCreatePassiveObjectPacket(262161, 0, 0, 1, 0);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.3, 1.3); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}

	}
	else if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_15_HUN_PO_ATTACK);

		if (isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.5, 0.5); //????????????t?????
		}
	}

}

function onAttack_SwordGhost15(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	local skillLevel = obj.sq_GetSkillLevel(123); //

	obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 0, 0, 240); //???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_15:buff_count1:" + count1);
	}

}

function onEndCurrentAni_SwordGhost15(obj) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_15, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

	}

}

function Dust_SwordGhost15_0(obj, disX, disY, disZ) {
	local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "passiveobject/new_skill/swordghost_15_whiteghostslash/animation/attackdustfront_08.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function Dust_SwordGhost15_1(obj, disX, disY, disZ) {
	local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "passiveobject/new_skill/swordghost_15_whiteghostslash/animation/attackfloor_01.ani"); //????????

	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function onKeyFrameFlag_SwordGhost15(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		//obj.sq_SetShake(obj,12,120);//?????
		//sq_flashScreen(obj, 0, 30, 5, 130, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		local gaugeValue_rate = setSwordGhost3State(obj);

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_15, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat()); //??????????SKL.0?????????????????1.0??
		local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);

		obj.sq_StartWrite(); //????????
		obj.sq_WriteDword(attackBonusRate); // ??????????
		obj.sq_WriteWord(sizeRate); // OBJ???????????

		obj.sq_SendCreatePassiveObjectPacket(26315, 0, -25, 0, -6);
		Dust_SwordGhost15_0(obj, -25, 0, -5);
		Dust_SwordGhost15_1(obj, -25, 0, -5);
		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		if (count1 >= max_gaugeValue) {
			count1 = max_gaugeValue; //????????
		}
		local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 3); //???????????????

		//print( "Attak_Ex:" + Attak_Ex);
		if (count1 >= Attak_Ex) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_SendCreatePassiveObjectPacket(261101, 0, -3000, 3000, 0);
		}
		//print( "attackBonusRate:" + attackBonusRate);
		//print( "sizeRate:" + sizeRate);

	}

	return true;
}

function onProc_SwordGhost15(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}
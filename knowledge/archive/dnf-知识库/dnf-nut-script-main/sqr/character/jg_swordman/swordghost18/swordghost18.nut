function checkExecutableSkill_SwordGhost18(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_18);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_18, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost18(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function Dust_SwordGhost18_1(obj, disX, disY, disZ) {
	local sizeRate = 100;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ghostpierce/ex/base.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 0, false);

}

function Dust_SwordGhost18_0(obj, disX, disY, disZ) {
	local sizeRate = 55;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ultimatecrossslash/endattack_03.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 1, false);

}

function Dust_SwordGhost18_2(obj, disX, disY, disZ) {
	local sizeRate = 100;
	local size = sizeRate.tofloat() / 100.0; //????j?????????

	local ani = sq_CreateAnimation("", "character/swordman/effect/animation/ghostpierce/ex/base_effect.ani"); //????????
	ani.setImageRateFromOriginal(size, size); //????j??
	ani.setAutoLayerWorkAnimationAddSizeRate(size); //???????h

	local pooledObj = sq_CreatePooledObject(ani, true); //??????H

	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX); //?????????????????????V???????

	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ); //????????????????

	pooledObj.setCurrentDirection(obj.getDirection()); //????????????V

	//sq_moveWithParent(obj, pooledObj);//???????????????????

	sq_AddObject(obj, pooledObj, 2, false);

}

function onSetState_SwordGhost18(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_R_ATTACK);
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/ghostdecollation/hiteffect/hiteffectbs_diagonal00_00.ani");

		if (isAppendApd_flag) {
			local gaugeValue_rate = setSwordGhost3State(obj);
			local hit_ex = setSwordGhost7hitEx(obj) / 3;
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat()); //??????????SKL.0?????????????????1.0??
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_18, -1, 0, 1.0);
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
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //????????????t?????
		}

	}
	else if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_A_ATTACK);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_A_ATTACK); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_18, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		if (isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //????????????t?????
		}
	}
	else if (substate == 2) {
		obj.sq_PlaySound("BLOODRIVEN_CIRCLE_01");
		Dust_SwordGhost18_1(obj, 0, 0, 1); //???
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_EX_MOVE);

	}
	else if (substate == 3) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_EX_ATTACK);
		Dust_SwordGhost18_2(obj, 0, -1, 0); //????
		Dust_SwordGhost18_0(obj, 44, 0, 70); //????
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_18_ER_GUI_ZHAN_SHOU_A_ATTACK); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_18, -1, 0, 0.8 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.75, 0.75); //????????????t?????
	}
}

function onAttack_SwordGhost18(obj, damager, boundingBox, isStuck) {
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
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_18:buff_count1:" + count1);
	}

}

function onEndCurrentAni_SwordGhost18(obj) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_18, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if (substate == 1) {
		local sq_var = obj.getVar();
		local posX = obj.getXPos();
		local len = obj.sq_GetIntData(SKILL_SWORD_GHOST_18, 4); //PX
		local ani = obj.sq_GetCurrentAni();
		local delay = 0;
		if (ani) delay = ani.getDelaySum(false);

		obj.getVar().clear_vector();
		obj.getVar().push_vector(posX);
		obj.getVar().push_vector(len);
		obj.getVar().push_vector(delay);
		obj.getVar().push_vector(0);
		//print(" clear_vector = ok");

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		if (count1 >= max_gaugeValue) {
			count1 = max_gaugeValue; //????????
		}
		local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 4); //???????????????
		//print( "Attak_Ex:" + Attak_Ex);
		if (count1 >= Attak_Ex) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_18, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		if (count1 < Attak_Ex) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}

	}
	else if (substate == 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_18, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if (substate == 3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onProc_SwordGhost18(obj) {
	local substate = obj.getSkillSubState();
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);

	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	if (substate == 0) {

	}
	if (substate == 2) {
		local sq_var = obj.getVar();

		local delayT = sq_var.get_vector(2); // Delay
		local len = 100; // Px
		local Rate = 20;
		if(
			(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT) || 
			(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT)
		){
			len = sq_var.get_vector(1); // Px
			Rate = obj.sq_GetIntData(SKILL_SWORD_GHOST_18, 5);
		}
		
		local srcX = sq_var.get_vector(0); // X pos

		 //???v
		//print(" Rate:" + Rate);
		local Rate1 = Rate * 0.01;
		//print(" Rate1:" + Rate1);
		local DelayRate = delayT * Rate1; // X pos .tointeger();
		DelayRate = DelayRate.tointeger();
		local v = sq_GetAccel(0, len, currentT, DelayRate, true); //???????

		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);

		if (obj.isMovablePos(dstX, posY)) {
			sq_setCurrentAxisPos(obj, 0, dstX); //???????????B???????0??x?? 1??y?? 2??z??
		}

	}

	setSwordGhost28Effect(obj);

}

function onKeyFrameFlag_SwordGhost18(obj, flagIndex) {
	if (!obj) return false;

	//if (flagIndex == 1)
	//{
	//obj.sq_SetShake(obj,17,220);//?????
	//sq_flashScreen(obj, 80, 20, 60, 190, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
	//}
	if (flagIndex == 2) {
		obj.sq_SendCreatePassiveObjectPacket(260183, 0, 0, 0, -1);
	}
	if (flagIndex == 10) {
		obj.sq_PlaySound("R_SM_GHOST_DECOLLATION");
	}
	if (flagIndex == 11) {
		obj.sq_PlaySound("GHOST_DECOLLATION_READY");
	}
	if (flagIndex == 12) {
		obj.sq_PlaySound("GHOST_DECOLLATION");
	}
	//if (flagIndex == 13)
	//{
	//obj.sq_SetShake(obj,17,220);//?????
	//sq_flashScreen(obj, 80, 20, 60, 190, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
	//}
	return true;
}
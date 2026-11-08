function checkExecutableSkill_SwordGhost8(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_8);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_8, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost8(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost8(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	obj.sq_SetStaticMoveInfo(0, 15, 100, false);
	obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);

	local direction = sq_GetDirection(obj);
	local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
	local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");

	if (direction == ENUM_DIRECTION_RIGHT && rightPress) {
		obj.sq_SetStaticMoveInfo(0, 35, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	else if (direction == ENUM_DIRECTION_LEFT && leftPress) {
		obj.sq_SetStaticMoveInfo(0, 35, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	else if (direction == ENUM_DIRECTION_LEFT && rightPress) {
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	else if (direction == ENUM_DIRECTION_RIGHT && leftPress) {
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}

	if (isAppendApd_flag) {
		if (substate == 0) {
			local gaugeValue_rate = setSwordGhost3State(obj);
			local hit_ex = setSwordGhost7hitEx(obj) / 3;
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 1, 0.5);
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat()); //??????????SKL.0?????????????????1.0??
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
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.7, 1.7); //????????????t?????
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_8_GLS_ATK4);
			obj.sq_SetStaticMoveInfo(0, 100, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
			local gaugeValue_rate = setSwordGhost3State(obj);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK4); //????ATK????
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 3, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
		}
	}

	if (!isAppendApd_flag) {
		if (substate == 0) {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_8_GLS_ATK1);

			local gaugeValue_rate = setSwordGhost3State(obj);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK1); //????ATK????
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 0, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2); //????????????t?????
		}

		else if (substate == 1) {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_8_GLS_ATK2);

			local gaugeValue_rate = setSwordGhost3State(obj);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK2); //????ATK????
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 1, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2); //????????????t?????
		}
		if (substate == 2) {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_8_GLS_ATK3);

			local gaugeValue_rate = setSwordGhost3State(obj);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK3); //????ATK????
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 2, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.2, 1.2); //????????????t?????
		}
		if (substate == 3) {
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_8_GLS_ATK4);

			obj.sq_SetStaticMoveInfo(0, 100, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);

			local gaugeValue_rate = setSwordGhost3State(obj);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_8_GLS_ATK4); //????ATK????
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_8, -1, 3, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}
	}
}

function onAttack_SwordGhost8(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	local substate = obj.getSkillSubState();

	if (substate == 0) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");
	}
	else if (substate == 2) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_1_0.ani");
	}
	else if (substate == 3) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");
	}
	else if (substate == 4) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_effect_00.ani");
	}

	local skillLevel = obj.sq_GetSkillLevel(123); //

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 0, 0, 240);

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj);
				sq_SendCreatePassiveObjectPacketPos(obj, objindex, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print("ski_8:buff_count1:" + count1);
	}

}

function onEndCurrentAni_SwordGhost8(obj) {
	if (!obj) return false;
	local substate = obj.getSkillSubState();
	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");
	if (substate == 0) {
		if (isAppendApd_flag) {
			obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

		}
		if (!isAppendApd_flag) {
			obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_8, STATE_PRIORITY_IGNORE_FORCE, true);
		}
	}
	else if (substate == 1) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_8, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 2) {
		local skill_level = sq_GetSkillLevel(obj, 118); //?????????????

		if (skill_level <= 0) {
			obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
		else if (skill_level > 0) {
			obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_8, STATE_PRIORITY_IGNORE_FORCE, true);
		}

	}
	else if (substate == 3) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

	}
}

function onKeyFrameFlag_SwordGhost8(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		obj.sq_SetShake(obj, 7, 80); //?????
		sq_flashScreen(obj, 0, 30, 5, 130, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); //?????
	}

	if (flagIndex == 2) {
		local count = obj.getMyPassiveObjectCount(251338); //BUFF???
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		if (count >= max_gaugeValue) {
			count = max_gaugeValue; //????????
		}
		local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 1); //???????????????
		//print("Attak_Ex:" + Attak_Ex);
		if (count >= Attak_Ex) {
			obj.resetHitObjectList();
		}
	}

	return true;
}

function onProc_SwordGhost8(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}
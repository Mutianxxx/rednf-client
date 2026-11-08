function checkExecutableSkill_SwordGhost23(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_23);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_23, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost23(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost23(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_23_LIAN_WU_ATTACK1);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_23_LIAN_WU_ATTACK1); //????ATK????
		obj.sq_SetShake(obj, 4, 70); //?????
		obj.resetHitObjectList(); //??????????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_23, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		if (isAppendApd_flag) {
			local gaugeValue_rate = setSwordGhost3State(obj);
			local hit_ex = setSwordGhost7hitEx(obj) / 3;
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
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}

	}
	else if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_23_LIAN_WU_ATTACK2);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_23_LIAN_WU_ATTACK2); //????ATK????
		obj.resetHitObjectList(); //??????????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_23, -1, 1, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		if (isAppendApd_flag) {

			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}

	}
	else if (substate == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_23_LIAN_WU_ATTACK3);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_23_LIAN_WU_ATTACK3); //????ATK????
		obj.resetHitObjectList(); //??????????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_23, -1, 2, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		if (isAppendApd_flag) {

			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}

	}
	else if (substate == 3) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_23_LIAN_WU_ATTACK4);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_23_LIAN_WU_ATTACK4); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_23, -1, 3, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		if (isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //????????????t?????
		}

	}
}

function onEndCurrentAni_SwordGhost23(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_23, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if (substate == 1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_23, STATE_PRIORITY_IGNORE_FORCE, true);
	}

	else if (substate == 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_23, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}

}

function onAttack_SwordGhost23(obj, damager, boundingBox, isStuck) {
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
		//print("ski_23:buff_count1:" + count1);
	}

}

function onKeyFrameFlag_SwordGhost23(obj, flagIndex) {
	if (!obj) return false;

	local direction = sq_GetDirection(obj); //????????????V
	local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL); //??????????????V???
	local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL); //???????????????V???

	if (flagIndex == 1) {

		if (direction == ENUM_DIRECTION_RIGHT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 120, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //??????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 120, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //????????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
		else if (direction == ENUM_DIRECTION_RIGHT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}

	}
	if (flagIndex == 2) {
		obj.sq_SetShake(obj, 4, 70); //?????
	}
	if (flagIndex == 3) {
		if (direction == ENUM_DIRECTION_RIGHT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //??????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //????????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
		else if (direction == ENUM_DIRECTION_RIGHT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
	}
	if (flagIndex == 4) {

		obj.sq_SetShake(obj, 5, 100); //?????
	}
	if (flagIndex == 5) {
		obj.sq_SetShake(obj, 8, 60); //?????
	}
	if (flagIndex == 6) {
		if (direction == ENUM_DIRECTION_RIGHT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 126, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //??????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 126, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //????????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
		else if (direction == ENUM_DIRECTION_RIGHT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
		sq_flashScreen(obj, 0, 30, 60, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); //?????
	}
	if (flagIndex == 7) {
		if (direction == ENUM_DIRECTION_RIGHT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //??????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //????????????
		}
		else if (direction == ENUM_DIRECTION_LEFT && rightPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}
		else if (direction == ENUM_DIRECTION_RIGHT && leftPress) {
			obj.sq_SetStaticMoveInfo(0, 0, 0, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //???????????
		}

		obj.sq_SetShake(obj, 10, 200); //?????
		sq_flashScreen(obj, 0, 30, 180, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); //?????
	}
	if (flagIndex == 8) {
		obj.resetHitObjectList(); //??????????
	}
	if (flagIndex == 9) {
		obj.resetHitObjectList(); //??????????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_23, -1, 4, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

	}
	return true;
}

function onProc_SwordGhost23(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
	setGhostSkillEnable(obj, SKILL_SWORD_GHOST_10, STATE_SWORD_GHOST_10);
	setGhostSkillState(obj, SKILL_SWORD_GHOST_10);
	setGhostSkillEnable(obj, SKILL_SWORD_GHOST_12, STATE_SWORD_GHOST_12);
	setGhostSkillState(obj, SKILL_SWORD_GHOST_12);
	setGhostSkillEnable(obj, SKILL_SWORD_GHOST_17, STATE_SWORD_GHOST_17);
	setGhostSkillState(obj, SKILL_SWORD_GHOST_17);
	setGhostSkillEnable(obj, SKILL_SWORD_GHOST_20, STATE_SWORD_GHOST_20);
	setGhostSkillState(obj, SKILL_SWORD_GHOST_20);
}
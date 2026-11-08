function checkExecutableSkill_SwordGhost11(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_11);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_11, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost11(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost11(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_11_LY_CAST);

		obj.setTimeEvent(0, 200, 3, true);

		if (isAppendApd_flag) {
			local gaugeValue_rate = setSwordGhost3State(obj);
			local hit_ex = setSwordGhost7hitEx(obj) / 3;
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, -1, SKL_LVL_COLUMN_IDX_0, 1.0 + gaugeValue_rate.tofloat()); //??????????SKL.0?????????????????1.0??
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_11, -1, 0, 1.0);
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
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.8, 0.8); //????????????t?????
		}
	}
	else if (substate == 1) {

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_11_LY_ATTACK);
		obj.sq_SendCreatePassiveObjectPacket(262172, 0, 10, 0, 67);
		obj.sq_SendCreatePassiveObjectPacket(262173, 0, 170, -1, 0);
		obj.sq_SendCreatePassiveObjectPacket(262170, 0, 0, 1, 0);

		local count1 = setSwordGhost2State(obj);
		local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 2);
		if (count1 > Attak_Ex) {

			setSwordGhostEnergyDec(obj, 1);
			obj.sq_SendCreatePassiveObjectPacket(261174, 0, 210, 1, 230);
		}

		local gaugeValue_rate = setSwordGhost3State(obj);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_11_LY_ATK);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_11, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage);

		if (isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.8, 0.8); //????????????t?????
		}

	}
	else if (substate == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_11_LY_END);

		if (isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5); //????????????t?????
			return true;
		}
		else if (!isAppendApd_flag) {
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.8, 0.8); //????????????t?????
		}
	}
}

function onEndCurrentAni_SwordGhost11(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_11, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_11, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 2) {
		obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/1.ani");
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_SwordGhost11(obj, flagIndex) {
	if (!obj) return false;

	//if (flagIndex == 1)
	//{
	//obj.sq_SetShake(obj,12,120);//?????
	//}

	return true;
}

function onTimeEvent_SwordGhost11(obj, timeEventIndex, timeEventCount) {
	if (!obj) return false;
	if (timeEventIndex == 0) {
		//obj.resetHitObjectList();//??????????
	}
}

function onAttack_SwordGhost11(obj, damager, boundingBox, isStuck)

{

	obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");
	sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 0, 0, 240); //???????????????G
	local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, STATE_SWORD_GHOST_11, false, "character/JG_SwordMan/swordghost11/ap_hit.nut", true);
	masterAppendage.sq_SetValidTime(1200);
	if (masterAppendage) {
		sq_HoldAndDelayDie(damager, obj, true, true, true, 1, 1, ENUM_DIRECTION_NEUTRAL, masterAppendage);
		local collectingTime = 400;
		sq_MoveToAppendageForce(activeObject, obj, obj, 175, 0, 0, collectingTime, true, masterAppendage);
	}

	local skillLevel = obj.sq_GetSkillLevel(237); //

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 237);
		local max_gaugeValue = obj.sq_GetLevelData(237, 0, skill_level);

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_11:buff_count1:" + count1);
	}

}

function onProc_SwordGhost11(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}
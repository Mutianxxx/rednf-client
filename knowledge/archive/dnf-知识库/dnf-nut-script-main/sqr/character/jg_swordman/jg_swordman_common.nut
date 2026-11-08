function procAppend_SwordGhostBackstepCut(obj) {
	if (!obj) return false;
	local mystate = obj.sq_GetState();
	local substatejump = obj.getVar("jumpsteps").get_vector(0);
	local ZPos = obj.getZPos();
	if (mystate == 6 && substatejump == 1) {
		if (ZPos > 10) {
			if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL)) {
				local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_3);
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(3);
				obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_3, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		}
	}
}

function setGhostSkillState(obj, skillindex) {
	if (!obj) return false;
	local iEnterSkill = obj.sq_IsEnterSkill(skillindex);
	if (iEnterSkill == -1) return false;
	local state = obj.sq_GetState();
	if (state == STATE_SAN_DUAN_ZHAN || state == STATE_SWORD_GHOST_1 || state == STATE_SWORD_GHOST_2 || state == STATE_SWORD_GHOST_7 || state == STATE_SWORD_GHOST_8 || state == STATE_SWORD_GHOST_11 || state == STATE_SWORD_GHOST_15 || state == STATE_SWORD_GHOST_18 || state == STATE_SWORD_GHOST_23) {
		if (obj.sq_IsUseSkill(skillindex)) {
			setSwordGhostEnergyDec(obj, 1);
			switch (skillindex) {
			case SKILL_SWORD_GHOST_10:
				obj.sq_SendCreatePassiveObjectPacket(262168, 0, 40, 1, 0);
				break;
			case SKILL_SWORD_GHOST_12:
				obj.sq_SendCreatePassiveObjectPacket(262174, 0, 40, 1, 0);
				break;
			case SKILL_SWORD_GHOST_17:
				obj.sq_SendCreatePassiveObjectPacket(260181, 0, 40, 1, 0);
				break;
			case SKILL_SWORD_GHOST_20:
				obj.sq_SendCreatePassiveObjectPacket(260191, 0, 0, 1, 0);
				break;
			case SKILL_SWORD_GHOST_21:
				obj.sq_SendCreatePassiveObjectPacket(260192, 0, 60, 1, 0);
				break;
			}

			return true;
		}
	}
	return false;
}

function setGhostSkillEnable(obj, skillindex, state) {
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_SAN_DUAN_ZHAN || state == STATE_SWORD_GHOST_1 || state == STATE_SWORD_GHOST_2 || state == STATE_SWORD_GHOST_7 || state == STATE_SWORD_GHOST_8 || state == STATE_SWORD_GHOST_11 || state == STATE_SWORD_GHOST_15 || state == STATE_SWORD_GHOST_18 || state == STATE_SWORD_GHOST_23) {
		obj.setSkillCommandEnable(skillindex, true);
	}
	return true;
}

function setSwordGhost28Effect(obj) {
	if (!obj) return;

	local skill = sq_GetSkill(obj, 78);
	if (!skill) {
		return;
	}
	local skillLevel = obj.sq_GetSkillLevel(78);
	if (skillLevel > 0 && obj.getWeaponSubType() == 1 && !skill.isSealFunction()) {
		if (sq_IsKeyDown(OPTION_HOTKEY_SKILL2, ENUM_SUBKEY_TYPE_ALL)) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_28, STATE_PRIORITY_IGNORE_FORCE, true);
		}

		if (sq_IsKeyDown(OPTION_HOTKEY_SKILL2, ENUM_SUBKEY_TYPE_ALL) && sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_28, STATE_PRIORITY_IGNORE_FORCE, true);
		}

		if (sq_IsKeyDown(OPTION_HOTKEY_SKILL2, ENUM_SUBKEY_TYPE_ALL) && sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_28, STATE_PRIORITY_IGNORE_FORCE, true);
		}
	}
}

function getAttackAni_Swordman(obj, index) //???????????
{
	if (!obj) return null;

	local animation = obj.sq_GetAttackAni(index);
	local skillLevel = obj.sq_GetSkillLevel(SKILL_SWORD_GHOST_4);
	if (skillLevel > 0) {
		switch (index) {
		case 0:
			animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORD_GHOST_NONE_ATTACK1); //??С??a????
			break;
		case 1:
			animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORD_GHOST_NONE_ATTACK2); //??С??a???
			break;
		case 2:
			animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORD_GHOST_NONE_ATTACK3); //??С??a???
			break;
		}
	}
	return animation;
}

function getDashAttackAni_Swordman(obj) //???????????С????????
{
	if (!obj) return null;

	local animation = obj.sq_GetDashAttackAni();
	local growtype = sq_getGrowType(obj);
	local skillLevel = obj.sq_GetSkillLevel(123);

	if (skillLevel > 0 && growtype == 0) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORD_GHOST_NONE_DASH);
		obj.sq_SetStaticMoveInfo(0, 500, 250, false); //???????????
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); //??????
	}
	return animation;
}

function getJumpAttackAni_Swordman(obj) {
	if (!obj) return null;
	local animation = obj.sq_GetJumpAttackAni();
	local skillLevel = obj.sq_GetSkillLevel(123);
	if (skillLevel > 0) {
		animation = obj.sq_GetCustomAni(CUSTOM_ANI_SWORD_GHOST_NONE_JUMP);
	}
	return animation;
}

function getSwordGhostEnergyNum(obj, num) {
	local numImage = null;
	local sq_var = obj.getVar();
	if (num == 0) {
		numImage = sq_var.GetAnimationMap("number0", "character/fighter/effect/animation/atspiralinhale/0.ani");
	} else if (num == 1) {
		numImage = sq_var.GetAnimationMap("number1", "character/fighter/effect/animation/atspiralinhale/1.ani");
	} else if (num == 2) {
		numImage = sq_var.GetAnimationMap("number2", "character/fighter/effect/animation/atspiralinhale/2.ani");
	} else if (num == 3) {
		numImage = sq_var.GetAnimationMap("number3", "character/fighter/effect/animation/atspiralinhale/3.ani");
	} else if (num == 4) {
		numImage = sq_var.GetAnimationMap("number4", "character/fighter/effect/animation/atspiralinhale/4.ani");
	} else if (num == 5) {
		numImage = sq_var.GetAnimationMap("number5", "character/fighter/effect/animation/atspiralinhale/5.ani");
	} else if (num == 6) {
		numImage = sq_var.GetAnimationMap("number6", "character/fighter/effect/animation/atspiralinhale/6.ani");
	} else if (num == 7) {
		numImage = sq_var.GetAnimationMap("number7", "character/fighter/effect/animation/atspiralinhale/7.ani");
	} else if (num == 8) {
		numImage = sq_var.GetAnimationMap("number8", "character/fighter/effect/animation/atspiralinhale/8.ani");
	} else if (num == 9) {
		numImage = sq_var.GetAnimationMap("number9", "character/fighter/effect/animation/atspiralinhale/9.ani");
	}
	return numImage;
}

function drawDevilStrikeGauge_Sword2(obj) {
	if (!obj) return;

	local isAppendApd_flag = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");
	if (isAppendApd_flag) {
		local state = obj.sq_GetState();
		if (state <= STATE_QUICK_STANDING) {
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/ap_sword_ghost_flag.nut");
			//print( "Delete Flag");

		}
	}

	local level = sq_GetSkillLevel(obj, 123);

	if (level <= 0) return;

	local sq_var = obj.getVar();

	local gauge_normal_bar = sq_var.GetAnimationMap("5_gauge_normal_bar", "Character/Priest/Effect/Animation/DevilStrike/gauge/9_new_jd.ani");

	local gauge_normal_max = sq_var.GetAnimationMap("5_gauge_normal_max", "Character/Priest/Effect/Animation/DevilStrike/gauge/11_new_jd_max.ani");

	local gauge_normal_max_effect = sq_var.GetAnimationMap("gauge_normal_max_effect", "Character/Priest/Effect/Animation/DevilStrike/gauge/11_new_jd_max_effect.ani");

	local gauge_normal_max_6 = sq_var.GetAnimationMap("gauge_normal_max_6", "Character/Priest/Effect/Animation/DevilStrike/gauge/6_max.ani");

	local gauge_normal_max_7 = sq_var.GetAnimationMap("gauge_normal_max_7", "Character/Priest/Effect/Animation/DevilStrike/gauge/7_tip.ani");

	local gauge_normal_max_8 = sq_var.GetAnimationMap("gauge_normal_max_8", "Character/Priest/Effect/Animation/DevilStrike/gauge/8_newui.ani");

	local gauge_normal_max_10 = sq_var.GetAnimationMap("gauge_normal_max_10", "Character/Priest/Effect/Animation/DevilStrike/gauge/10_dibu.ani");

	local gauge_normal_max_12 = sq_var.GetAnimationMap("gauge_normal_max_12", "Character/Priest/Effect/Animation/DevilStrike/gauge/12_red_effect.ani");

	local gauge_normal_max_13 = sq_var.GetAnimationMap("gauge_normal_max_13", "Character/Priest/Effect/Animation/DevilStrike/gauge/13_blue_effect.ani");

	local gauge_normal_max_14 = sq_var.GetAnimationMap("gauge_normal_max_14", "Character/Priest/Effect/Animation/DevilStrike/gauge/14_blue_effect_jd.ani");

	local ui_none_15 = sq_var.GetAnimationMap("ui_none_15", "character/priest/effect/animation/devilstrike/gauge/15_ui_none.ani");
	local ui_none_15_effect0 = sq_var.GetAnimationMap("ui_none_15_effect0", "character/priest/effect/animation/devilstrike/gauge/15_ui_effect.ani");
	local ui_none_15_effect1 = sq_var.GetAnimationMap("ui_none_15_effect1", "character/priest/effect/animation/devilstrike/gauge/15_ui_effect.ani");
	local ui_none_15_effect2 = sq_var.GetAnimationMap("ui_none_15_effect2", "character/priest/effect/animation/devilstrike/gauge/15_ui_effect.ani");
	local ui_none_15_effect3 = sq_var.GetAnimationMap("ui_none_15_effect3", "character/priest/effect/animation/devilstrike/gauge/15_ui_effect.ani");
	local ui_none_15_effect4 = sq_var.GetAnimationMap("ui_none_15_effect4", "character/priest/effect/animation/devilstrike/gauge/15_ui_effect.ani");

	local x = 85;
	local y = 500;

	local skill_level = sq_GetSkillLevel(obj, 123);
	local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);

	local count = 1000;
	local gaugeValue = 0;

	local state = obj.sq_GetState();

	if (level >= 1) {
		gaugeValue = setSwordGhost2State(obj);
	}

	if (gaugeValue >= max_gaugeValue) {
		gaugeValue = max_gaugeValue;
	}

	local rate = gaugeValue.tofloat() / max_gaugeValue.tofloat();

	if (gaugeValue >= max_gaugeValue) {

		sq_AnimationProc(gauge_normal_max_10);
		sq_drawCurrentFrame(gauge_normal_max_10, x - 35, 2, false);

		sq_AnimationProc(gauge_normal_max);
		gauge_normal_max.setImageRate(rate, 1.0);
		sq_drawCurrentFrame(gauge_normal_max, x, y + 1, false);

		sq_AnimationProc(gauge_normal_max_8);
		sq_drawCurrentFrame(gauge_normal_max_8, x - 35, 2, false);

		sq_AnimationProc(gauge_normal_max_6);
		sq_drawCurrentFrame(gauge_normal_max_6, x - 35, 1, false);

		sq_AnimationProc(gauge_normal_max_12);
		sq_drawCurrentFrame(gauge_normal_max_12, x - 35, 2, false);

		sq_AnimationProc(gauge_normal_max_effect);
		sq_drawCurrentFrame(gauge_normal_max_effect, x - 35, 2, false);

	}
	else {

		sq_AnimationProc(gauge_normal_max_10);
		sq_drawCurrentFrame(gauge_normal_max_10, x - 35, 2, false);

		sq_AnimationProc(gauge_normal_bar);
		gauge_normal_bar.setImageRate(rate, 1.0);
		sq_drawCurrentFrame(gauge_normal_bar, x, y + 1, false);

		sq_AnimationProc(gauge_normal_max_8);
		sq_drawCurrentFrame(gauge_normal_max_8, x - 35, 2, false);

		sq_AnimationProc(gauge_normal_max_14);
		gauge_normal_max_14.setImageRate(rate, 1.0);
		sq_drawCurrentFrame(gauge_normal_max_14, x, y + 1, false);

		sq_AnimationProc(gauge_normal_max_13);
		sq_drawCurrentFrame(gauge_normal_max_13, x - 35, 2, false);

		local ge = gaugeValue % 10;
		local len = (gaugeValue - ge) / 10;
		local shi = len % 10;

		local geani = getSwordGhostEnergyNum(obj, ge);
		local shiani = getSwordGhostEnergyNum(obj, shi);

		sq_AnimationProc(geani);
		sq_drawCurrentFrame(geani, x + 84, y - 11, false);
		sq_AnimationProc(shiani);
		sq_drawCurrentFrame(shiani, x + 79, y - 11, false);

	}

	local count_ex = obj.getMyPassiveObjectCount(251338);

	local Attak_Ex_0 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 0);
	local Attak_Ex_1 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 1);
	local Attak_Ex_2 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 2);
	local Attak_Ex_3 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 3);
	local Attak_Ex_4 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 4);
	local Attak_Ex_5 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 5);
	local Attak_Ex_6 = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 6);

	if (count_ex >= max_gaugeValue) {
		count_ex = max_gaugeValue;
	}

	if (count_ex >= Attak_Ex_0) {

		sq_AnimationProc(ui_none_15_effect0);
		sq_drawCurrentFrame(ui_none_15_effect0, 90, 470, false);

/*		local hit_ex = setSwordGhost7hitEx(obj);
		if (hit_ex == 1) {
			//1
		}
		if (hit_ex == 2) {
			//2
		}
		if (hit_ex == 3) {
			//3
		}
		if (hit_ex == 4) {
			//4
		}
		if (hit_ex == 5) {
			//5
		}*/
	}
	if (count_ex >= Attak_Ex_1) {

		sq_AnimationProc(ui_none_15_effect1);
		sq_drawCurrentFrame(ui_none_15_effect1, 115, 488, false);
	}
	if (count_ex >= Attak_Ex_2) {

		sq_AnimationProc(ui_none_15_effect2);
		sq_drawCurrentFrame(ui_none_15_effect2, 140, 488, false);
	}
	if (count_ex >= Attak_Ex_3) {

		sq_AnimationProc(ui_none_15_effect3);
		sq_drawCurrentFrame(ui_none_15_effect3, 165, 488, false);
	}
	if (count_ex >= Attak_Ex_4) {

		sq_AnimationProc(ui_none_15_effect4);
		sq_drawCurrentFrame(ui_none_15_effect4, 190, 488, false);
	}

	if (count_ex >= Attak_Ex_5) {

		sq_AnimationProc(ui_none_15_effect4);
		sq_drawCurrentFrame(ui_none_15_effect4, 215, 488, false);
	}

	local mouseX = sq_GetMouseXPos();
	local mouseY = sq_GetMouseYPos();

	local tipX = x - 20;
	local tipY = y - 15;
	local tipEndX = tipX + 195;
	local tipEndY = tipY + 20;
	if (mouseX > tipX && mouseY > tipY && mouseX < tipEndX && mouseY < tipEndY) {
		sq_AnimationProc(gauge_normal_max_7);
		sq_drawCurrentFrame(gauge_normal_max_7, 0, 0, false);

	}

}

function setSwordGhost2State(obj) {
	if (!obj || !obj.isMyControlObject()) return;

	local count = obj.getMyPassiveObjectCount(251338);
	local skill_level = sq_GetSkillLevel(obj, 123);
	local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
	if (count >= max_gaugeValue) {
		count = max_gaugeValue;
	}
	return count;
}

function setSwordGhostEnergyDec(obj, num) {
	if (!obj || !obj.isMyControlObject()) return;
	local count = obj.getMyPassiveObjectCount(251338);
	local skill_level = sq_GetSkillLevel(obj, 123);
	local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
	if (count >= max_gaugeValue) {
		setSwordGhostEnergy(obj, max_gaugeValue - num);
	}
	else if (count > 0) {
		for (local i = 0; i < num; ++i) {
			local passiveobject = obj.getMyPassiveObject(251338, i);
			if (passiveobject) {
				sq_SendDestroyPacketPassiveObject(passiveobject);
			}
		}
	}
	return;
}

function setSwordGhostEnergy(obj, num) {
	if (!obj || !obj.isMyControlObject()) return;
	local count = obj.getMyPassiveObjectCount(251338);
	if (count > 0) {
		local newcount = count - num;
		for (local i = 0; i < newcount; ++i) {
			local passiveobject = obj.getMyPassiveObject(251338, i);
			if (passiveobject) {
				sq_SendDestroyPacketPassiveObject(passiveobject);
			}
		}
	}
	return;
}

function setSwordGhost3State(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local skill_level = sq_GetSkillLevel(obj, 123);
	local gaugeValue = setSwordGhost2State(obj);
	local rate = obj.sq_GetLevelData(123, 1, skill_level);
	local gaugeValue_rate = gaugeValue.tofloat() / rate;
	//local AttackUpRate = gaugeValue_rate.tofloat() * 100;

	return gaugeValue_rate;
}

function getSwordGhost3BasicAttackBonus(obj) {
	if (!obj || !obj.isMyControlObject()) return;
	local skill_level = sq_GetSkillLevel(obj, 123);
	local gaugeValue = setSwordGhost2State(obj);
	local rate = obj.sq_GetLevelData(123, 1, skill_level);
	local gaugeValue_rate = gaugeValue.tofloat() / rate;
	local AttackUp = 0 + gaugeValue_rate * 100 + sq_GetLevelData(obj, 209, 4, sq_GetSkillLevel(obj, 209))/10;
	AttackUp = AttackUp.tointeger();
	return AttackUp;
}

function setSwordGhost7hitEx(obj) {
	if (!obj || !obj.isMyControlObject()) return;

	local count = obj.getMyPassiveObjectCount(251338);
	local skill_level = sq_GetSkillLevel(obj, 123);
	local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
	local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 0);

	if (count >= max_gaugeValue) {
		count = max_gaugeValue;
	}
	local HitCount = count / Attak_Ex;
	HitCount = HitCount.tointeger();

	return HitCount;
}

function setSwordGhost4State(obj) {
	if (!obj || !obj.isMyControlObject()) return;

	local index = sq_getRandom(250331, 250334);

	/*	if (index == 250334) {
		//print( "Create Ghost");
	}*/

	return index;
}

function getBossTargetSwordMan4(obj) {
	local activeObject = getBossTarget(obj, -200, 2000, 1500, 500, null);
	if (activeObject == null) {
		local activeObject = getCommonChampionTarget(obj, -200, 2000, 1500, 500, null);

		if (activeObject == null) {
			local activeObject = getChampionTarget(obj, -200, 2000, 1500, 500, null);
			if (activeObject == null) {
				local activeObject = getPriorityTarget(obj, -200, 2000, 1500, 500, null, true);
				//print("GET_PT ok");
				return activeObject;

			}
			//print("GET_LM ok");
			return activeObject;
		}
		//print("GET_JY ok");
		return activeObject;

	}
	//print("GET_BOSS ok");
	return activeObject;
}

function getBossTarget(obj, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange, targetMaxHeight, exceptSqVar) {
	if (!obj) return null;

	local objectManager = obj.getObjectManager();

	if (objectManager == null) return null;

	local target = null;

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && isInFrontObject(obj, object) && object.getZPos() <= targetMaxHeight) {
			if (sq_IsinMapArea(obj, object, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);

				if (!activeObj.isDead()) {
					if (activeObj.isBoss()) {
						local isExist = isSameObjectBySqVar(object, exceptSqVar);

						if (!isExist || target == null) {
							target = activeObj;
						}
					}
				}
			}
		}
	}

	return target;

}

function getCommonChampionTarget(obj, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange, targetMaxHeight, exceptSqVar) {
	if (!obj) return null;

	local objectManager = obj.getObjectManager();

	if (objectManager == null) return null;

	local target = null;

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && isInFrontObject(obj, object) && object.getZPos() <= targetMaxHeight) {
			if (sq_IsinMapArea(obj, object, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);

				if (!activeObj.isDead()) {
					if (activeObj.isCommonChampion()) {
						local isExist = isSameObjectBySqVar(object, exceptSqVar);

						if (!isExist || target == null) {
							target = activeObj;
						}
					}
				}
			}
		}
	}

	return target;

}

function getChampionTarget(obj, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange, targetMaxHeight, exceptSqVar) {
	if (!obj) return null;

	local objectManager = obj.getObjectManager();

	if (objectManager == null) return null;

	local target = null;

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && isInFrontObject(obj, object) && object.getZPos() <= targetMaxHeight) {
			if (sq_IsinMapArea(obj, object, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);

				if (!activeObj.isDead()) {
					if (activeObj.isChampion()) {
						local isExist = isSameObjectBySqVar(object, exceptSqVar);

						if (!isExist || target == null) {
							target = activeObj;
						}
					}
				}
			}
		}
	}

	return target;

}

function getPriorityTarget(obj, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange, targetMaxHeight, exceptSqVar, isInFront) {
	if (!obj) return null;

	local objectManager = obj.getObjectManager();

	if (objectManager == null) return null;

	local target = null;

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && object.getZPos() <= targetMaxHeight) {
			if (isInFront == true) {
				if (isInFrontObject(obj, object) == false) {
					continue;
				}
			}
			if (sq_IsinMapArea(obj, object, firstTargetXStartRange, firstTargetXEndRange, firstTargetYRange)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);

				if (!activeObj.isDead()) {
					local isExist = isSameObjectBySqVar(object, exceptSqVar);

					if (activeObj.isBoss()) {
						if (target == null) {
							target = activeObj;
							//print("get_BOSS ok");
							if (!isExist) return target;
						}
					}

					if (activeObj.isSuperChampion()) {
						if (target == null || !isExist) {
							target = activeObj;
							//print("isSuperChampion ok");
							if (!isExist) return target;
						}
					}

					if (activeObj.isCommonChampion()) {
						if (target == null || !isExist) {
							target = activeObj;
							//print("isCommonChampion ok");
							if (!isExist) return target;
						}
					}

					if (activeObj.isChampion()) {
						if (target == null || !isExist) {
							target = activeObj;
							//print("null ok");
							if (!isExist) return target;
						}
					}

					if (target == null || !isExist) {
						target = activeObj;

						if (!isExist) return target;
					}
				}
			}
		}
	}

	return target;

}

function SKILL_obj_info(obj, objID, speedRate, sizeRate) {
	local passiveobject = obj.getMyPassiveObject(objID, 0);

	if (passiveobject) {
		local animation = sq_GetCurrentAnimation(passiveobject);
		local multiHitSpeed100Rate = speedRate;
		animation.setSpeedRate(multiHitSpeed100Rate.tofloat());
		local size = sizeRate.tofloat() / 100.0;
		animation.setImageRateFromOriginal(size, size);
		animation.setAutoLayerWorkAnimationAddSizeRate(size);

		local hitInterval = 60000;
		if (IsInterval(passiveobject, hitInterval)) {
			sq_SetAttackBoundingBoxSizeRate(animation, size, size, size);
		}

	}
}

function onChangeSkillEffect_Swordman(obj, skillIndex, reciveData) {
	if (!obj) return;
	switch (skillIndex) {
	case 128:
		//???????? ??????????
		local Uid = reciveData.readDword();
		local Xpos = reciveData.readDword();
		local Ypos = reciveData.readDword();
		local Object = sq_GetObjectByObjectId(obj, Uid);
		if (Object) {
			//print("Uid:"+Uid+"\n");
			//print("Xpos:"+Xpos+"\n");
			//print("Ypos:"+Ypos+"\n");
			local activeObj = sq_GetCNRDObjectToActiveObject(Object);
			activeObj.setCurrentPos(Xpos, Ypos, 0);
			sq_SimpleMoveToNearMovablePos(obj, 880);
		}
		break;
	}
}
function procSKILL_SWORD_BACKJUMP(obj) {
	setATKinfo_SKILL_SWORD_BACKJUMP(obj, 262165);
}

function procSKILL_SWORD_GHOST_7(obj) {
	setATKinfo_SKILL_SWORD_GHOST_7_ATK(obj, 26317);
	setATKinfo_SKILL_SWORD_GHOST_7_ATK(obj, 26316);
}

function procSKILL_SWORD_10_ONE_ATTACK(obj) {
	setATKinfo_SKILL_SWORD_10_ONE_ATTACK(obj, 262167);
}

function procSKILL_SWORD_11_GHOST_ATTACK(obj) {
	setATKinfo_SKILL_SWORD_11_GHOST_ATTACK(obj, 261174);
}

function procSKILL_SWORD_12_ONE_ATTACK1(obj) {
	setATKinfo_SKILL_SWORD_12_ONE_ATTACK1(obj, 262175);
}

function procSKILL_SWORD_12_ONE_ATTACK2(obj) {
	setATKinfo_SKILL_SWORD_12_ONE_ATTACK2(obj, 260176);
}

function procSKILL_SWORD_12_ONE_ATTACK3(obj) {
	setATKinfo_SKILL_SWORD_12_ONE_ATTACK3(obj, 260177);
}

function procSKILL_SWORD_12_ONE_ATTACK4(obj) {
	setATKinfo_SKILL_SWORD_12_ONE_ATTACK4(obj, 260178);
}

function procSKILL_SWORD_13_ATTACK1(obj) {
	setATKinfo_SKILL_SWORD_13_ATTACK1(obj, 260207);
}

function procSKILL_SWORD_13_ATTACK2(obj) {
	setATKinfo_SKILL_SWORD_13_ATTACK2(obj, 260208);
}

function procSKILL_SWORD_13_ATTACK3(obj) {
	setATKinfo_SKILL_SWORD_13_ATTACK3(obj, 260209);
}

function procSKILL_SWORD_13_ATTACK4(obj) {
	setATKinfo_SKILL_SWORD_13_ATTACK4(obj, 260210);
}

function procSKILL_SWORD_14_ATTACK1(obj) {
	setATKinfo_SKILL_SWORD_14_ATTACK1(obj, 260198);
}
function procSKILL_SWORD_14_ATTACK2(obj) {
	setATKinfo_SKILL_SWORD_14_ATTACK2(obj, 260197);
	setATKinfo_SKILL_SWORD_14_ATTACK2(obj, 260199);
}

function procSKILL_SWORD_15_ATTACK(obj) {
	setATKinfo_SKILL_SWORD_15_ATTACK(obj, 26315);
}

function procSKILL_SWORD_16_ATTACK(obj) {
	setATKinfo_SKILL_SWORD_16_ATTACK(obj, 260180);
}

function procSKILL_SWORD_17_ATTACK1(obj) {
	setATKinfo_SKILL_SWORD_17_ATTACK1(obj, 260181);
}

function procSKILL_SWORD_17_ATTACK2(obj) {
	setATKinfo_SKILL_SWORD_17_ATTACK2(obj, 260182);
}

function procSKILL_SWORD_20_ATTACK(obj) {
	setATKinfo_SKILL_SWORD_20_ATTACK(obj, 260190);
}

function procSKILL_SWORD_21_ATTACK1(obj) {
	setATKinfo_SKILL_SWORD_21_ATTACK1(obj, 260192);
}

function procSKILL_SWORD_21_ATTACK2(obj) {
	setATKinfo_SKILL_SWORD_21_ATTACK2(obj, 260193);
}

function procSKILL_SWORD_21_ATTACK3(obj) {
	setATKinfo_SKILL_SWORD_21_ATTACK3(obj, 260194);
}

function setATKinfo_SKILL_SWORD_10_ONE_ATTACK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_10);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_10, SKILL_SWORD_GHOST_10, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_11_GHOST_ATTACK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_11);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_11, SKILL_SWORD_GHOST_11, 0, 1.5 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_GHOST_7_ATK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_7);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, SKILL_SWORD_GHOST_7, 1, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_BACKJUMP(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_7);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_7, SKILL_SWORD_GHOST_7, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_12_ONE_ATTACK1(obj, passiveobjectID) {

	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);

	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, 137);
				local attackPower = obj.sq_GetBonusRateWithPassive(137, 137, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_12_ONE_ATTACK2(obj, passiveobjectID) {

	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);

	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, 137);
				local attackPower = obj.sq_GetBonusRateWithPassive(137, 137, 1, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
				SKILL_obj_info(obj, 262176, 180, 100);
			}

		}
	}
}

function setATKinfo_SKILL_SWORD_12_ONE_ATTACK3(obj, passiveobjectID) {

	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);

	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, 137);
				local attackPower = obj.sq_GetBonusRateWithPassive(137, 137, 2, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
				SKILL_obj_info(obj, 262177, 180, 100);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_12_ONE_ATTACK4(obj, passiveobjectID) {

	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, 137);
				local attackPower = obj.sq_GetBonusRateWithPassive(137, 137, 3, 1.0 + gaugeValue_rate.tofloat());
				local ani = sq_GetCurrentAnimation(obj);
				sq_SetCurrentAttackBonusRate(atk, attackPower);
				SKILL_obj_info(obj, 262178, 180, 100);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_16_ATTACK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_16);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_16, SKILL_SWORD_GHOST_16, 0, 1.3 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_15_ATTACK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_15);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_15, SKILL_SWORD_GHOST_15, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
				SKILL_obj_info(obj, 26315, 100, obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0));
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_17_ATTACK1(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_17);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_17, SKILL_SWORD_GHOST_17, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_17_ATTACK2(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_17);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_17, SKILL_SWORD_GHOST_17, 1, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}

			SKILL_obj_info(obj, 260182, 180, 100);
		}
	}
}

function setATKinfo_SKILL_SWORD_20_ATTACK(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_20);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_20, SKILL_SWORD_GHOST_20, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_21_ATTACK1(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_21);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_21, SKILL_SWORD_GHOST_21, 0, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}
function setATKinfo_SKILL_SWORD_21_ATTACK2(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_21);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_21, SKILL_SWORD_GHOST_21, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}

		}
	}
}
function setATKinfo_SKILL_SWORD_21_ATTACK3(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_21);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_21, SKILL_SWORD_GHOST_21, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
			SKILL_obj_info(obj, 260193, 180, 100);
		}
	}
}

function setATKinfo_SKILL_SWORD_14_ATTACK1(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_14);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_14, SKILL_SWORD_GHOST_14, 0, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_14_ATTACK2(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_14);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_14, SKILL_SWORD_GHOST_14, 1, 1.0 + gaugeValue_rate.tofloat());
				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_13_ATTACK1(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);
				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_13);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_13, SKILL_SWORD_GHOST_13, 6, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_13_ATTACK2(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_13);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_13, SKILL_SWORD_GHOST_13, 6, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_13_ATTACK3(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_13);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_13, SKILL_SWORD_GHOST_13, 6, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}

function setATKinfo_SKILL_SWORD_13_ATTACK4(obj, passiveobjectID) {
	local ObjCount = obj.getMyPassiveObjectCount(passiveobjectID);
	if (ObjCount > 0) {
		for (local i = 0; i < ObjCount; ++i) {
			local passiveobject = obj.getMyPassiveObject(passiveobjectID, i);
			if (passiveobject) {
				local atk = sq_GetCurrentAttackInfo(passiveobject);
				local gaugeValue_rate = setSwordGhost3State(obj);

				local level = sq_GetSkillLevel(obj, SKILL_SWORD_GHOST_13);
				local attackPower = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_13, SKILL_SWORD_GHOST_13, 6, 1.0 + gaugeValue_rate.tofloat());

				sq_SetCurrentAttackBonusRate(atk, attackPower);
			}
		}
	}
}
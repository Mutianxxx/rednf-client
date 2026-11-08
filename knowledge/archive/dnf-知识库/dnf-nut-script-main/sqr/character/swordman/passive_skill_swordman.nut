function ProcPassiveSkill_Swordman(obj, skill_index, skill_level) {
	if (skill_index == 248) {
		if (skill_level > 0 && sq_getGrowType(obj) == 1) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/swordman/appendage/ap_stateoflimit.nut", true);
		}
	}
	else if (skill_index == 254) {
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if (skill_index == 252) {
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/swordman/appendage/ap_swordman_comminterrupt.nut", true);
		}
	}
	else if (skill_index == 123) {
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost4/ap_swordghost4.nut", true);
		}
	}
	else if (skill_index == 171) {
		if (skill_level > 0 && sq_getGrowType(obj) == 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_buff_171.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("buff_171"); //üòö¢Ü¨ûùßÒ÷¾
			local rigidity = sq_GetLevelData(obj, 171, 1, skill_level) * 0.1;
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("buff_171", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_RIGIDITY, false, rigidity.tofloat());
			}
		}
	}
	else if (skill_index == 209) {
		if (skill_level > 0 && sq_getGrowType(obj) == 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_buff_209.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("buff_209"); //üòö¢Ü¨ûùßÒ÷¾
			local stuckb = sq_GetLevelData(obj, 209, 0, skill_level) * 10;
			local hpr = sq_GetLevelData(obj, 209, 1, skill_level);
			local mpr = sq_GetLevelData(obj, 209, 2, skill_level);
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("buff_209", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVEPROPERTY_STUCK, true, stuckb.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_HP_REGEN_RATE, false, hpr.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_REGEN_RATE, false, mpr.tofloat());
			}
		}
	}
	else if (skill_index == 119) {
		if (skill_level > 0 && sq_getGrowType(obj) == 0) {
			//local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_swordghost27.nut", true);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_swordghost27.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("swordghost27"); //üòö¢Ü¨ûùßÒ÷¾

			local atspdb = sq_GetLevelData(obj, 119, 1, skill_level) * 0.1;
			local mspdb = sq_GetLevelData(obj, 119, 2, skill_level) * 0.1;
			local crb = sq_GetLevelData(obj, 119, 3, skill_level) * 0.1;
			local cratkb = sq_GetLevelData(obj, 119, 0, skill_level) * 0.1;
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("swordghost27", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, atspdb.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, mspdb.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, crb.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, cratkb.tofloat());
			}
		}
	}
	else if (skill_index == 78) {
		if (skill_level > 0 && sq_getGrowType(obj) == 0 && obj.getWeaponSubType() == 1) {
			//local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_swordghost28.nut", true);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/jg_swordman/swordghost13/ap_swordghost28.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("swordghost28"); //üòö¢Ü¨ûùßÒ÷¾

			local equbonus = sq_GetLevelData(obj, 78, 1, skill_level) * 0.1;
			local aimbonus = sq_GetLevelData(obj, 78, 2, skill_level).tofloat();
			aimbonus = aimbonus / 10;
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("swordghost28", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, equbonus.tofloat()); //Úª×âÍôÌªÕô

			}
		}
	}
	return true;
}

function procSkill_MysticEquip(obj) {
	if (obj.sq_GetSkillLevel(SKILL_MYSTICEQUIP) > 0 && sq_getGrowType(obj) == 1) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Character/Swordman/MysticEquip/MysticEquip.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_MYSTICEQUIP, false, "Character/Swordman/MysticEquip/MysticEquip.nut", true);
		}
	}
}

function procSkill_FORCEOFTHUNDERER(obj) {
	local skill = sq_GetSkill(obj, SKILL_FORCEOFTHUNDERER);

	if (obj.sq_GetSkillLevel(SKILL_FORCEOFTHUNDERER) > 0 && sq_getGrowType(obj) == 4) {
		if (skill) {
			if (skill.isSealFunction()) // off
			{
				if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Character/Swordman/ForceOfThunderer/ap_ForceOfThunderer.nut")) {
					CNSquirrelAppendage.sq_RemoveAppendage(obj, "Character/Swordman/ForceOfThunderer/ap_ForceOfThunderer.nut");
				}
			} else { // on
				if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Character/Swordman/ForceOfThunderer/ap_ForceOfThunderer.nut")) {
					CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_FORCEOFTHUNDERER, true, "Character/Swordman/ForceOfThunderer/ap_ForceOfThunderer.nut", true);
				}
			}
		}
	}

}

function procSkill_Swordman(obj) {
	if (!obj) return false;
	procSkill_FORCEOFTHUNDERER(obj);
	procSkill_MysticEquip(obj);
	procSkill_ghostSoulRelease(obj);
	if (sq_GetSkillLevel(obj, 123) > 0 && sq_getGrowType(obj) == 0) {
		setGhostSkillEnable(obj, SKILL_SWORD_GHOST_21, STATE_SWORD_GHOST_21);
		setGhostSkillState(obj, SKILL_SWORD_GHOST_21);
	}
	return true;
}

function getGhostSoulReleaseExecultableState(obj) {
	local state = obj.sq_GetState();
	if (state == 32 || state == 20 || state == 42 || state == 65 || state == 13 || state == 33 || state == 50) return true;

	if (state == STATE_SWORDMAN_SLASHOFBOOM || state == STATE_SWORDMAN_SLASHOFHELL || state == STATE_SWORDMAN_BLADEPHANTOMEX || state == STATE_SWORDMAN_ZIGADVENT) return true;

	return false;
}

function getGhostSoulRelease_Area_Distance(obj, state) {

	local posX = 0;

	if (state == 32 || state == 20 || state == 42 || state == 65 || state == STATE_SWORDMAN_SLASHOFBOOM) posX = obj.sq_GetIntData(SKILL_GHOST_SOUL_RELEASE, 0);
	else if (state == 33) posX = obj.sq_GetIntData(SKILL_GHOST_SOUL_RELEASE, 1);
	else if (state == 50 || state == STATE_SWORDMAN_SLASHOFHELL || state == STATE_SWORDMAN_BLADEPHANTOMEX || state == STATE_SWORDMAN_ZIGADVENT) posX = obj.sq_GetIntData(SKILL_GHOST_SOUL_RELEASE, 2);
	else if (state == 13) posX = obj.sq_GetIntData(SKILL_GHOST_SOUL_RELEASE, 3);

	posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), posX);

	return posX;

}

function procSkill_ghostSoulRelease(obj) {
	if (obj.sq_GetSkillLevel(SKILL_GHOST_SOUL_RELEASE) > 0) {
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/ghostsoulrelease/ap_ghostsoulrelease.nut")) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_GHOST_SOUL_RELEASE, false, "character/swordman/ghostsoulrelease/ap_ghostsoulrelease.nut", true);

		}
	} else {

		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/ghostsoulrelease/ap_ghostsoulrelease.nut")) {

			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/ghostsoulrelease/ap_ghostsoulrelease.nut");
		}
	}
}

function drawHeroGhostIcon(obj) {
	local skillLevel = sq_GetSkillLevel(obj, SKILL_HERO);
	if (skillLevel > 0) {
		local sq_var = obj.getVar();
		local appendage = null;

		if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/hero/ap_hero.nut")) {
			appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_HERO, false, "character/swordman/hero/ap_hero.nut", true);

			local skill_level = sq_GetSkillLevel(obj, SKILL_HERO);
			//            appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_HERO, skill_level);
			//            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_HERO, true);

		} else {
			appendage = obj.GetSquirrelAppendage("character/swordman/hero/ap_hero.nut");
		}

		local ghost1 = sq_var.GetAnimationMap("HeroGhost1", "character/swordman/animation/ani_als/necromantic/iconkhazan.ani");
		local ghost2 = sq_var.GetAnimationMap("HeroGhost2", "character/swordman/animation/ani_als/necromantic/iconsaya.ani");
		local ghost3 = sq_var.GetAnimationMap("HeroGhost3", "character/swordman/animation/ani_als/necromantic/iconbremen.ani");
		local ghost4 = sq_var.GetAnimationMap("HeroGhost4", "character/swordman/animation/ani_als/necromantic/iconrasa.ani");

		local obj1 = obj.getMyPassiveObject(20011, 0);
		local obj2 = obj.getMyPassiveObject(20012, 0);
		local obj3 = obj.getMyPassiveObject(20013, 0);
		local obj4 = null; //obj.getMyPassiveObject(20040,0);
		local x = 75;
		local y = 500;

		if (obj1) {
			if (appendage.getVar("effectObj").get_vector(0) == 0) {
				ghost1.setCurrentFrameWithChildLayer(0);
				appendage.getVar("effectObj").set_vector(0, 1);
			}
			sq_AnimationProc(ghost1);
			sq_drawCurrentFrame(ghost1, x, y, false);
		} else if (appendage.getVar("effectObj").get_vector(0) == 1) {
			appendage.getVar("effectObj").set_vector(0, 0);
		}

		if (obj2) {
			if (appendage.getVar("effectObj").get_vector(1) == 0) {
				ghost2.setCurrentFrameWithChildLayer(0);
				appendage.getVar("effectObj").set_vector(1, 1);
			}
			sq_AnimationProc(ghost2);
			sq_drawCurrentFrame(ghost2, x + 30, y, false);
		} else if (appendage.getVar("effectObj").get_vector(1) == 1) {
			appendage.getVar("effectObj").set_vector(1, 0);
		}

		if (obj3) {
			if (appendage.getVar("effectObj").get_vector(2) == 0) {
				ghost3.setCurrentFrameWithChildLayer(0);
				appendage.getVar("effectObj").set_vector(2, 1);
			}

			sq_AnimationProc(ghost3);
			sq_drawCurrentFrame(ghost3, x + 60, y, false);
		} else if (appendage.getVar("effectObj").get_vector(2) == 1) {
			appendage.getVar("effectObj").set_vector(2, 0);
		}

		if (obj4) {
			if (appendage.getVar("effectObj").get_vector(3) == 0) {
				ghost1.setCurrentFrameWithChildLayer(0);
				appendage.getVar("effectObj").set_vector(3, 1);
			}

			sq_AnimationProc(ghost4);
			sq_drawCurrentFrame(ghost4, x + 90, y, false);
		} else if (appendage.getVar("effectObj").get_vector(3) == 1) {
			appendage.getVar("effectObj").set_vector(3, 0);
		}

	}
}
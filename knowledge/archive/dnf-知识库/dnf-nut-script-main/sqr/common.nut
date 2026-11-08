DEBUG <- isDebugMode();
NULL <- null;
isDraw <- 1;
ScreenPrint <- true; //false changqing debugå±å¹•?¾ç¤º
CurAniGet <- true; //false


function setState_AllGrowJob(obj, state, datas, isResetTimer) {
	if (!obj) return -1;
	//P(obj, state, datas); 	//?¶æ€è¾“?ºè‡³state.txtè¾“å…¥?•èŽ·
	//OutSubState(obj, state, datas); //changqing debugè¾“å…¥?•èŽ·
	return 0;
}

//?k???
function setState_Fighter(obj, state, datas, isResetTimer) {
	setState_AllGrowJob(obj, state, datas, isResetTimer);
}

//?k?k?v
function setState_ATMage(obj, state, datas, isResetTimer) {
	setState_AllGrowJob(obj, state, datas, isResetTimer);
}

//?o???
function setState_Priest(obj, state, datas, isResetTimer) {
	if(!obj) return;
	if(state == 0) return;
	useRangeBuff_setState(obj, state, datas);//ÏØô÷BUFF
	setState_AllGrowJob(obj, state, datas, isResetTimer);
}

//?s??
function setState_Thief(obj, state, datas, isResetTimer) {
	setState_AllGrowJob(obj, state, datas, isResetTimer);
}

function setState_CreatorMage(obj, state, datas, isResetTimer) {
	setState_AllGrowJob(obj, state, datas, isResetTimer);
}


function getTheSevenDeadlySinsAddDamageBonus(obj)
{
	if (!obj)
		return 0;
	if (sq_getJob(obj) != ENUM_CHARACTERJOB_AT_PRIEST)
		return 0;
	local append = "character/atpriest/seducer/thesevendeadlysins/ap_thesevendeadlysins.nut";
	local appendage = obj.GetSquirrelAppendage(append);
	if (appendage) {
		local isvalid = appendage.isValid();
		if(!isvalid)
			return 0;
		local damagebonus = appendage.getVar("damagebonus").get_vector(0);
		return damagebonus;
	}
	return 0;
}

function IsInterval(obj, interval)
{
	if (!obj)
		return false;
	local t = obj.getVar().get_ct_vector(0);
	if (!t)
	{
		obj.getVar().clear_ct_vector();
		obj.getVar().push_ct_vector();
		t = obj.getVar().get_ct_vector(0);
		t.Reset();
		t.Start(10000,0);

		return true;
	}
	local currentT = t.Get();
	if(currentT > interval)
	{
		t.Reset();
		t.Start(10000,0);
		return true;
	}
	return false;
}

function isEnemyBack(obj,damager)
{
    local objD = sq_GetDirection(obj);
    local damaD = sq_GetDirection(damager);

    local objX = obj.getXPos();
    local damaX = damager.getXPos();

    if (objX > damaX)
    {
        if (damaD ==  ENUM_DIRECTION_LEFT)
        {
            return true;
        }
    }
    if (objX < damaX)
    {
        if (damaD ==  ENUM_DIRECTION_RIGHT)
        {
            return true;
        }
    }
    return false;
}

function isAssassinOfBackPoint(obj)
{
	return true;
}

function startSkillCoolTime(obj, skillIndex, skillLevel, currentCoolTime) {
	if (!obj) return -1;
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_GUNNER) {

		//79	G1
		//80	G2
		//81	G3
		//96	G0_1ï¿?
		//246	G4_2jue
		local g_zhuzaiLevel = sq_GetSkillLevel(obj, SKILL_G_ZHUZAI);
		local coolTimeRate = sq_GetLevelData(obj, SKILL_G_ZHUZAI, 1, g_zhuzaiLevel);
		if (g_zhuzaiLevel > 0 && skillIndex == 79 && CURRENT_BUFF_COUNT_qianzhi > 2) {
			local newCoolTime = currentCoolTime.tofloat() * (100.0 - coolTimeRate.tofloat()) / 100.0
			return newCoolTime.tointeger();
		}
		else if (g_zhuzaiLevel > 0 && skillIndex == 96 && CURRENT_BUFF_COUNT_qianzhi > 2) {
			local newCoolTime = currentCoolTime.tofloat() * (100.0 - coolTimeRate.tofloat()) / 100.0
			return newCoolTime.tointeger();
		}
		else if (g_zhuzaiLevel > 0 && skillIndex == 246 && CURRENT_BUFF_COUNT_qianzhi > 2) {
			local newCoolTime = currentCoolTime.tofloat() * (100.0 - coolTimeRate.tofloat()) / 100.0
			return newCoolTime.tointeger();
		}
	}
	return -1;
}

function requestBuy(obj, skill, nIndex, flag, count) {
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_PRIEST && sq_getGrowType(obj) == GROW_TYPE_AVENGER) {
		if (nIndex == SKILL_AVENGER_AWAKENING) {
			sq_requestBuySkill(SKILL_EXECUTION, flag, count);
		}
	}
	else if(sq_getJob(obj) == ENUM_CHARACTERJOB_AT_PRIEST && sq_getGrowType(obj) == 2){
		if (nIndex == 121) {
			sq_requestBuySkill(134, flag, count);
		}
	}
	return true;
}

function onAttack_PassiveObject(passiveobj, damager, bounding_box, is_stuck) {
	if (!passiveobj)
		return -1;

	local ID = passiveobj.getPassiveObjectIndex();

	setMonsterActAppendageEffect(passiveobj, damager, bounding_box, is_stuck);
	setMonsterActAppendageEffect_New(passiveobj, damager, bounding_box, is_stuck);

	local pChr = passiveobj.getTopCharacter();

	if (!isGrowTypeAvenger(pChr))
		return -1;

	if (pChr) {
		if (passiveobj.getPassiveObjectIndex() != 24104 && passiveobj.getPassiveObjectIndex() != 24105 && passiveobj.getPassiveObjectIndex() != 24106)
			procDevilStrikeGauge(pChr, passiveobj.getPassiveObjectIndex());
	}
	return 1;
}


function drawGrowAvatarAniType(job, growtype, x, y, isOver, is_draw) {
	if (job == ENUM_CHARACTERJOB_PRIEST && growtype == GROW_TYPE_AVENGER) {
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("1_aura_normal", "Character/Priest/Effect/Animation/ScytheMastery/1_aura_normal.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_MAGE && growtype == 3){
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			local auraAniA = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("bloodmage_1st_move_aura04", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_move_aura04.ani");
				auraAniA = getvar.GetAnimationMap("bloodmage_1st_rest_aura01", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_rest_aura01.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y+25, false);
			sq_AnimationProc(auraAniA);
			sq_drawCurrentFrame(auraAniA, x, y, false);
		}
		else if(isOver == false && is_draw == true)
		{
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("bloodmage_1st_rest_backaura", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_rest_backaura.ani");

			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x+5, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_MAGE && growtype == 4){
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("swiftmaster_01", "character/mage/effect/animation/atgroweffect/swiftmaster/swiftmaster_01.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_SWORDMAN && growtype == 1){
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("swordmaster_effect", "character/swordman/effect/animation/atgrowtype/swordmaster_effect.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_SWORDMAN && growtype == 2){
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("vegabond", "character/swordman/effect/animation/atgrowtype/vegabond.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_SWORDMAN && growtype == 3){
		if (isOver == false && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("daemonslayer_fire", "character/swordman/effect/animation/atgrowtype/daemonslayer_fire.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_SWORDMAN && growtype == 4){
		if (isOver == false && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("darktempler_shadow", "character/swordman/effect/animation/atgrowtype/darktempler_shadow.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 1){
		if(is_draw == true)
		{
			if (isOver == false) {
				local getvar = CNAvenger.getStaticVar();
				local auraAni = null;
				if (getvar) {
					auraAni = getvar.GetAnimationMap("atcrusader1st", "character/priest/effect/animation/atcrusader_1st/atcrusader1st_02.ani");
				}
				sq_AnimationProc(auraAni);
				sq_drawCurrentFrame(auraAni, x, y, false);
			}
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 2){
		if (isOver == true && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("temptress1stf", "character/priest/effect/animation/temptress_1st/temptress_front_loop.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
		if(isOver == false && is_draw == true){
			local getvar = CNAvenger.getStaticVar();
			local auraAni1 = null;
			local auraAni2 = null;
			if (getvar) {
				auraAni1 = getvar.GetAnimationMap("temptress1stb1", "character/priest/effect/animation/temptress_1st/temptress_back_loop01.ani");
				auraAni1 = getvar.GetAnimationMap("temptress1stb2", "character/priest/effect/animation/temptress_1st/temptress_back_loop02.ani");
			}
			sq_AnimationProc(auraAni1);
			sq_drawCurrentFrame(auraAni1, x, y, false);
			sq_AnimationProc(auraAni2);
			sq_drawCurrentFrame(auraAni2, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 3){
		if (isOver == false && is_draw == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("sorceress1st", "character/priest/effect/animation/sorceress_1st/sorceress_dragon.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
}

function drawAppend_VirtualCharacter(job, growtype, x, y, isOver, is_draw) {
	if (job == ENUM_CHARACTERJOB_PRIEST && growtype == GROW_TYPE_AVENGER) {
		if (isOver == true) {
			local getvar = CNAvenger.getStaticVar();

			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("1_aura_normal", "Character/Priest/Effect/Animation/ScytheMastery/1_aura_normal.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_MAGE && growtype == 3){
		if (isOver == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			local auraAniA = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("bloodmage_1st_move_aura04", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_move_aura04.ani");
				auraAniA = getvar.GetAnimationMap("bloodmage_1st_rest_aura01", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_rest_aura01.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y+25, false);
			sq_AnimationProc(auraAniA);
			sq_drawCurrentFrame(auraAniA, x, y, false);
		}
		else{
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("bloodmage_1st_rest_backaura", "character/mage/effect/animation/atgroweffect/bloodmage_1st/bloodmage_1st_rest_backaura.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x+5, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_MAGE && growtype == 4){
		if (isOver == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("swiftmaster_01", "character/mage/effect/animation/atgroweffect/swiftmaster/swiftmaster_01.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == 10 && growtype == 1){
		if (isOver == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("swordmaster_effect", "character/swordman/effect/animation/atgrowtype/swordmaster_effect.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == 10 && growtype == 2){
		if (isOver == true) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("vegabond", "character/swordman/effect/animation/atgrowtype/vegabond.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == 10 && growtype == 3){
		if (isOver == false) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("daemonslayer_fire", "character/swordman/effect/animation/atgrowtype/daemonslayer_fire.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == 10 && growtype == 4){
		if (isOver == false) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("darktempler_shadow", "character/swordman/effect/animation/atgrowtype/darktempler_shadow.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 1){
		if (isOver == false) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("atcrusader1st", "character/priest/effect/animation/atcrusader_1st/atcrusader1st_02.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 2){
		if(isOver == true){
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("temptress1st", "character/priest/effect/animation/temptress_1st/temptress_front_loop.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
		if (isOver == false) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni1 = null;
			local auraAni2 = null;
			if (getvar) {
				auraAni1 = getvar.GetAnimationMap("temptress1stb1", "character/priest/effect/animation/temptress_1st/temptress_back_loop01.ani");
				auraAni1 = getvar.GetAnimationMap("temptress1stb2", "character/priest/effect/animation/temptress_1st/temptress_back_loop02.ani");
			}
			sq_AnimationProc(auraAni1);
			sq_drawCurrentFrame(auraAni1, x, y, false);
			sq_AnimationProc(auraAni2);
			sq_drawCurrentFrame(auraAni2, x, y, false);
		}

	}
	else if(job == ENUM_CHARACTERJOB_AT_PRIEST && growtype == 3){
		if (isOver == false) {
			local getvar = CNAvenger.getStaticVar();
			local auraAni = null;
			if (getvar) {
				auraAni = getvar.GetAnimationMap("sorceress1st", "character/priest/effect/animation/sorceress_1st/sorceress_dragon.ani");
			}
			sq_AnimationProc(auraAni);
			sq_drawCurrentFrame(auraAni, x, y, false);
		}
	}
}

function sqr_CreatePooledObject(obj, ani_filename, x, y, z, dir) {
	if (!obj) return;

	local ani = obj.sq_createCNRDAnimation(ani_filename); // [create draw only object] ï¿?? ï¿??ï¿?? ï¿???? ï¿??ï¿??ï¿?? ï¿???ï¿?? ï¿???ï¿???ï¿????..
	local pooledObj = obj.sq_createCNRDPooledObject(ani, true);
	if (pooledObj) {
		// 15 -2 75
		pooledObj.setCurrentDirection(dir);
		pooledObj.setCurrentPos(x, y, z);
		obj.sq_AddObject(pooledObj);
	}
}


function sqr_IsNormalAttack(state) {
	//STATE_ATTACK <- 8
	//STATE_JUMP_ATTACK <- 7
	//STATE_DASH_ATTACK <- 15
	if (state == STATE_ATTACK || state == STATE_JUMP_ATTACK || state == STATE_DASH_ATTACK) {
		return true;
	}

	return false;
}

function CreateAimPointMark(parentObj) {
	local job = sq_getJob(parentObj);
	local ani = null;

	if (job == ENUM_CHARACTERJOB_AT_MAGE) {
		ani = sq_CreateAnimation("", "Common/CommonEffect/Animation/atmage_cussor/AimPointMark.ani");
		ani.setRGBA(0, 78, 255, 255);
	}

	return ani;
}

function CNAimPointMarkCustomAnimation(obj, parentObj) {
	if (!obj) return false;

	local job = sq_getJob(parentObj);

	if (job == ENUM_CHARACTERJOB_AT_MAGE) {
		local ani1 = sq_CreateAnimation("", "Common/CommonEffect/Animation/atmage_cussor/AimPointMarkDisable.ani");
		local ani2 = sq_CreateAnimation("", "Common/CommonEffect/Animation/atmage_cussor/AimPointMarkVanish.ani");
		local ani3 = sq_CreateAnimation("", "Common/CommonEffect/Animation/atmage_cussor/AimPointMarkDisableVanish.ani");
		local ani4 = sq_CreateAnimation("", "Common/CommonEffect/Animation/atmage_cussor/AimPointMarkEnable.ani");

		if (ani1 && ani2 && ani3 && ani4) {
			ani1.setRGBA(0, 78, 255, 255);
			ani2.setRGBA(0, 78, 255, 255);
			ani3.setRGBA(0, 78, 255, 255);
			ani4.setRGBA(0, 78, 255, 255);

			obj.addCustomAnimation(ani1);
			obj.addCustomAnimation(ani2);
			obj.addCustomAnimation(ani3);
			obj.addCustomAnimation(ani4);

			return true;
		}
	}

	return false;
}


function isMovablePos_CNAimPointMark(obj, parentObj, xPos, yPos) {
	if (!obj) return true;

	if (!parentObj) return true;

	local job = sq_getJob(parentObj);

	if (job == ENUM_CHARACTERJOB_AT_MAGE) {
		return sq_IsMovablePosCollisionObject(parentObj, xPos, yPos);
	}

	return true;
}

function isEnemyBack(obj,damager)
{
    local objD = sq_GetDirection(obj);
    local damaD = sq_GetDirection(damager);

    local objX = obj.getXPos();
    local damaX = damager.getXPos();

    if (objX > damaX)
    {
        if (damaD ==  ENUM_DIRECTION_LEFT)
        {
            return true;
        }
    }

    if (objX < damaX)
    {
        if (damaD ==  ENUM_DIRECTION_RIGHT)
        {
            return true;
        }
    }

    return false;

}

// ï¿??ï¿?? ï¿??ï¿??ï¿??ï¿??ï¿??ï¿???ï¿??? ï¿???ï¿????.
function isBattleMode() {
	local isPvpMode = checkModuleType(MODULE_TYPE_PVP_TYPE);
	local isDungeonMode = checkModuleType(MODULE_TYPE_DUNGEON_TYPE);

	//print(" isPvpMode:" + isPvpMode + " isDungeonMode:" + isDungeonMode);

	if (!isPvpMode && !isDungeonMode) { // ï¿??ï¿??ï¿??ï¿?? ï¿????ï¿?
		return false;
	}

	return true;
}

SKILL_HARD_ATTACK <- 5;
SKILL_TRIPLE_SLASH <- 8;
SKILL_MOMENTARY_SLASH <- 9;
SKILL_ASHEN_FORK <- 16;
SKILL_JUMP_ATTACK_MULTI <- 17;
SKILL_NORMAL_WAVE <- 20;
SKILL_ICE_WAVE <- 21;
SKILL_DARK_FRIENDSHIP <- 29;
SKILL_GRAB_BLAST_BLOOD <- 31;
SKILL_UPPER_SLASH <- 46;
SKILL_VANE_SLASH <- 58;
SKILL_GHOST_STEP_SLASH <- 60;
SKILL_GORE_CROSS <- 64;
SKILL_HOP_SMASH <- 65;
SKILL_CHARGE_CRASH <- 68;
SKILL_RAPID_MOVE_SLASH <- 72;
SKILL_ILLUSION_SLASH <- 73;
SKILL_WAVE_SPIN_AREA <- 74;
SKILL_MOONLIGHT_SLASH <- 77;
SKILL_BLOODY_RAVE <- 79;
SKILL_OUT_RAGE_BREAK <- 81;
SKILL_KALLA <- 82;
SKILL_FLOW_MIND <- 105;

SKILL_SHOCK_WAVE_AREA <- 57;
SKILL_GRAND_WAVE <- 50;
SKILL_REFLECT_GUARD <- 2;
SKILL_TRIPLE_STAB <- 112;
SKILL_GHOST_SIDE_WIND <- 111;

// ï¿???? ï¿??? ï¿??ï¿??? ï¿??ï¿???ï¿??? ï¿???
function sq_LoadSkillEffect_Swordman(obj, skillIndex) {
	if (skillIndex == SKILL_GHOST_SIDE_WIND) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostSideWind/00_sword_normal.ani"); // ghostSideWindAnimations_ 0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostSideWind/01_sword_dodge.ani"); // ghostSideWindAnimations_ 1
	}
	else if (skillIndex == SKILL_HARD_ATTACK) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/HardAttack1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/HardAttack2.ani");
	}
	else if (skillIndex == SKILL_RAPID_MOVE_SLASH) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/RapidMoveSlash/Move1.ani"); // 0 : rapidMoveSlashMoveAnimations_[0]
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/RapidMoveSlash/Move2.ani"); // 1 : rapidMoveSlashMoveAnimations_[1]
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/RapidMoveSlash/Slash1.ani"); // 2 : rapidMoveSlashSlashAnimations_[0]
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/RapidMoveSlash/Slash2.ani"); // 3 : rapidMoveSlashSlashAnimations_[1]
	}
	else if (skillIndex == SKILL_GHOST_STEP_SLASH) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostStepSlash/Move.ani"); // 0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostStepSlash/Slash1.ani"); // 1
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostStepSlash/Slash2.ani"); // 2
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GhostStepSlash/Skull.ani"); // 2

	}
	else if (skillIndex == SKILL_TRIPLE_SLASH) {
		// ï¿???ï¿??
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Slash1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Slash2.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Slash3.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Slash4.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Slash5.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Move1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/TripleSlash/Move2.ani");
	}
	else if (skillIndex == SKILL_MOMENTARY_SLASH) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_none_under.ani"); //0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_blue_ldodge_under.ani"); //1
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_none_upper.ani"); //2
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_blue_ldodge_upper.ani"); //3
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_white_ldodge_under.ani"); //4
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_white_ldodge_upper.ani"); //5
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_red_ldodge_under.ani"); //6
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/momentaryslash_red_ldodge_upper.ani"); //7
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/Charge1.ani"); //8
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MomentarySlash/Charge2.ani"); //9
	}
	else if (skillIndex == SKILL_ASHEN_FORK) {
		// ï¿??ï¿??ï¿???
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackHold.ani");
	}
	else if (skillIndex == SKILL_JUMP_ATTACK_MULTI) {
		// ï¿??ï¿?? ï¿??ï¿???ï¿??
		// jumpAttackMultiSlash1Sword_
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash1_katana_under.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash1_katana_upper.ani");
		// jumpAttackMultiSlash2Sword_
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash2_katana_under.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash2_katana_upper.ani");
		// jumpAttackMultiSlashSwordUnderEffects_
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash1_under_effect.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash2_under_effect.ani");
		// jumpAttackMultiSlashSwordUpperEffects_
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash1_upper_effect.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattackslash2_upper_effect.ani");

		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/JumpAttackMulti/jumpchainattacknormal_upper_effect.ani");
	}
	else if (skillIndex == SKILL_NORMAL_WAVE) {
		// ï¿???ï¿?? ï¿??ï¿??
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/NormalWaveSlash.ani");
	}
	else if (skillIndex == SKILL_GRAB_BLAST_BLOOD) {
		// ï¿??ï¿??ï¿?ï¿??ï¿???
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GrabBlastBlood.ani");
	}
	else if (skillIndex == SKILL_UPPER_SLASH) {
		// ï¿??ï¿???ï¿??ï¿??
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/UpperSlash1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/UpperSlash2.ani");
	}
	else if (skillIndex == SKILL_VANE_SLASH) {
		// ï¿??ï¿??ï¿??
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/VaneSlash/Upper.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/VaneSlash/Dust.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/VaneSlash/Smash.ani");
	}
	else if (skillIndex == SKILL_GORE_CROSS) {
		// ï¿??ï¿?ï¿½ï¿½?Î½ï¿?
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GoreCross/Slash1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GoreCross/Slash2.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GoreCross/Slash3.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/GoreCross/Slash4.ani");
	}
	else if (skillIndex == SKILL_HOP_SMASH) {
		// ï¿???ï¿?
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/HopSmash/Sword.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/HopSmash/Smash.ani");
	}
	else if (skillIndex == SKILL_MOONLIGHT_SLASH) {
		// ï¿???ï¿??ï¿??
		// ï¿??ï¿?? ï¿???ï¿??ï¿?? : MoonlightSlashFull.ani : ï¿??ï¿???ï¿?ï¿??ï¿??ï¿??ï¿?ï¿??ï¿??.
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MoonlightSlash1.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MoonlightSlash2.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/MoonlightSlashFull.ani");
	}
	else if (skillIndex == SKILL_BLOODY_RAVE) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Start1.ani"); // bloodyRaveStartAnis_		0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Start2.ani"); // bloodyRaveStartAnis_		1
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Loop1.ani"); // bloodyRaveLoopAnis_		2
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Loop2.ani"); // bloodyRaveLoopAnis_		3
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Line1.ani"); // bloodyRaveLineAnis_		4
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Line2.ani"); // bloodyRaveLineAnis_		5
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Typhoon.ani"); // bloodyRaveTyphoonAni_	6
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/End.ani"); // bloodyRaveEndAni_		7
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Sword1.ani"); // bloodyRaveSwordAnis_		8
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Sword2.ani"); // bloodyRaveSwordAnis_		9
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Sword3.ani"); // bloodyRaveSwordAnis_		10
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Sword4.ani"); // bloodyRaveSwordAnis_		11
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/(TN)Sword2.ani"); // bloodyRaveSwordAnis_		12
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/(TN)Sword4.ani"); // bloodyRaveSwordAnis_		13
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/BloodyRave/Hit.ani"); // 14
	}
	else if (skillIndex == SKILL_OUT_RAGE_BREAK) {
		// ï¿???ï¿??ï¿??ï¿?ï¿??ï¿???
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_ready_ldodge.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_ready_none.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_slash_ldodge.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_slash_none.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_slash_impact_ldodge.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_slash_impact_none.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/OutRageBreak/sword_slash_stone.ani");
	}
	else if (skillIndex == SKILL_KALLA) {
		for (local i = 1; i <= 4; ++i)
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/Kalla/FinishReady" + i + ".ani"); //	0~3

		for (local j = 1; j <= 3; ++j)
		for (local i = 1; i <= 4; ++i)
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/Kalla/Finish" + j + "-" + i + ".ani"); //	0~3
	}
	else if (skillIndex == SKILL_WAVE_SPIN_AREA) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/WaveSpinArea/Circle.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/WaveSpinArea/CircleFront.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/WaveSpinArea/CircleBack.ani");
	}
	else if (skillIndex == SKILL_CHARGE_CRASH) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/dash.ani"); // 0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/up-slash.ani"); // 1
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/charge.ani"); // 2
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/down-slash.ani"); // 3
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/dustdash.ani"); // 4
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ChargeCrash/dustdashlast.ani"); // 5
	}
	else if (skillIndex == SKILL_ILLUSION_SLASH) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/IllusionSlash/Upper.ani"); // 0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/IllusionSlash/Smash.ani"); // 1
	}
	else if (skillIndex == SKILL_SHOCK_WAVE_AREA) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ShockWaveArea/Cast.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ShockWaveArea/Smash.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ShockWaveArea/Area.ani");
	}
	else if (skillIndex == SKILL_GRAND_WAVE) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/grandWaveOnCharge1.ani"); // 0
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/grandWaveOnCharge2.ani"); // 1
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/grandWave.ani"); // 2
	}
	else if (skillIndex == SKILL_REFLECT_GUARD) {
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ReflectGuard/charge.ani");
		obj.sq_LoadSkillEffectAni(skillIndex, "Effect/Animation/ReflectGuard/slash.ani");
	}
}

function getDist2(x1, y1, x2, y2) {
	local i = 0;

	local dx = x1 - x2;

	local dy = y1 - y2;

	local sum = (dx * dx) + (dy * dy);

	if (dx < 0) dx = -dx;

	if (dy < 0) dy = -dy;

	if (dx > dy) i = dx;
	else i = dy;

	while ((i * i) < sum) {
		i = i + 2;
	}

	i = i - 1;

	if ((i * i) < sum) i = i + 1;

	return i;

}

function removeEdification(obj)
{
	if (!obj) return;
	local append = "character/atpriest/edification/ap_edification.nut";
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append))
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
	}
	return;
}

function removeZealOfFaith(obj)
{
	if (!obj) return;
	local append = "character/atpriest/appendage/ap_zealoffaith_friend.nut";
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, append))
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
	}
	return;
}

function CreateBuffCutin(obj,aniPath)
{
	local ani = sq_CreateAnimation("",aniPath)
	local pooledObj = sq_CreatePooledObject(ani,true)
	local objMan = obj.getObjectManager()
	local x = obj.getXPos()
	local y = objMan.getFieldYPos(0, 0, 0)
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM)
	pooledObj.setCurrentPos(x, y, 0)
	sq_AddObject(obj,pooledObj,2,false)
}

function enableClearDeadEnemies(obj, damager) {
	if (obj.isEnemy(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
		local activeObj = sq_GetCNRDObjectToActiveObject(damager);
		if (activeObj.isDead()) {
			sq_IntVectorClear(sq_GetGlobalIntVector());
			sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
			sq_AddSetStatePacketActiveObject(activeObj, STATE_DIE, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
		}
	}
}

function onAttack_Swordman(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_Fighter(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_Gunner(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_Mage(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_Priest(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_ATGunner(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_Thief(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}

function onAttack_ATPriest(obj, damager, bounding_box, is_stuck) {
	if (!obj) return -1;
	//enableClearDeadEnemies(obj, damager);
}
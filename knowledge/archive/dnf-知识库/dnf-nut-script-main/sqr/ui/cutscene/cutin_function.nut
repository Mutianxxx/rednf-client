
function drawSwordmanCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 231)
		awake = var.GetAnimationMap("swordman_bloodevil", "common/cutscene/swordman_bloodevil.ani");
	else if(AWAKE_SKILL_ID == 241)
		awake = var.GetAnimationMap("swordman_zigadvent", "common/cutscene/swordman_zigadvent.ani");
	else if(AWAKE_SKILL_ID == 244)
		awake = var.GetAnimationMap("swordman_indaratian", "common/cutscene/swordman_indaratian.ani");
	else if(AWAKE_SKILL_ID == 246)
		awake = var.GetAnimationMap("swordman_handlingsword", "common/cutscene/swordman_handlingsword.ani");
	else if(AWAKE_SKILL_ID == 130)
		awake = var.GetAnimationMap("swordman_nachal", "etc/ultimateskillani/swordman_nachal.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawGunnerCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 235)
		awake = var.GetAnimationMap("gunnerlauncher2nd", "common/cutscene/gunnerlauncher2nd.ani");
	else if(AWAKE_SKILL_ID == 240)
		awake = var.GetAnimationMap("gunnerranger2nd", "common/cutscene/gunnerranger2nd.ani");
	else if(AWAKE_SKILL_ID == 245)
		awake = var.GetAnimationMap("gunnerspitfire2nd", "common/cutscene/gunnerspitfire2nd.ani");
	else if(AWAKE_SKILL_ID == 247)
		awake = var.GetAnimationMap("gunnermechanic2nd", "common/cutscene/gunnermechanic2nd.ani");
	else if(AWAKE_SKILL_ID == 133)
		awake = var.GetAnimationMap("gunnerassault2nd", "etc/ultimateskillani/gunner_exmachina.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && AWAKE_SKILL_ID == 133){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawATGunnerCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 235)
		awake = var.GetAnimationMap("atgunner_stormtrooper", "common/cutscene/atgunner_stormtrooper.ani");
	else if(AWAKE_SKILL_ID == 239)
		awake = var.GetAnimationMap("atgunner_crimsonrose", "common/cutscene/atgunner_crimsonrose.ani");
	else if(AWAKE_SKILL_ID == 244)
		awake = var.GetAnimationMap("atgunner_freyja", "common/cutscene/atgunner_freyja.ani");
	else if(AWAKE_SKILL_ID == 249)
		awake = var.GetAnimationMap("atgunner_optimus", "common/cutscene/atgunner_optimus.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 244 || AWAKE_SKILL_ID == 249)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawFightCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 232)
		awake = var.GetAnimationMap("fighterstriker2nd", "common/cutscene/fighterstriker2nd.ani");
	else if(AWAKE_SKILL_ID == 239)
		awake = var.GetAnimationMap("fightergrappler2nd", "common/cutscene/fightergrappler2nd.ani");
	else if(AWAKE_SKILL_ID == 228)
		awake = var.GetAnimationMap("fighternenmaster2nd", "common/cutscene/fighternenmaster2nd.ani");
	else if(AWAKE_SKILL_ID == 235)
		awake = var.GetAnimationMap("fighterstreetfighter2nd", "common/cutscene/fighterstreetfighter2nd.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawATFightCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 225)
		awake = var.GetAnimationMap("atfighter_supremacyemperor", "common/cutscene/atfighter_supremacyemperor.ani");
	else if(AWAKE_SKILL_ID == 222)
		awake = var.GetAnimationMap("atfighter_nen2ndaction", "common/cutscene/atfighter_nen2ndaction.ani");
	else if(AWAKE_SKILL_ID == 228)
		awake = var.GetAnimationMap("atfighter_dark", "common/cutscene/atfighter_dark.ani");
	else if(AWAKE_SKILL_ID == 231)
		awake = var.GetAnimationMap("atfighter_grand", "common/cutscene/atfighter_grand.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 222 || AWAKE_SKILL_ID == 228)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawPriestCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 245)
		awake = var.GetAnimationMap("priest_justice", "common/cutscene/priest_justice.ani");
	else if(AWAKE_SKILL_ID == 241)
		awake = var.GetAnimationMap("priest_taoisthermit", "common/cutscene/priest_taoisthermit.ani");
	else if(AWAKE_SKILL_ID == 251)
		awake = var.GetAnimationMap("priest_saint", "common/cutscene/priest_saint.ani");
	else if(AWAKE_SKILL_ID == 138)
		awake = var.GetAnimationMap("priest_immortal", "common/cutscene/priest_immortal.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && AWAKE_SKILL_ID == 245){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawMageCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 253)
		awake = var.GetAnimationMap("mage_elma2nd", "common/cutscene/mage_elma2nd.ani");
	else if(AWAKE_SKILL_ID == 139)
		awake = var.GetAnimationMap("mage_summon2nd", "common/cutscene/mage_summon2nd.ani");
	else if(AWAKE_SKILL_ID == 245)
		awake = var.GetAnimationMap("mage_battle2nd", "common/cutscene/mage_battle2nd.ani");
	else if(AWAKE_SKILL_ID == 134)
		awake = var.GetAnimationMap("mage_witch2nd", "common/cutscene/mage_witch2nd.ani");
	else if(AWAKE_SKILL_ID == 213)
		awake = var.GetAnimationMap("mage_hecate", "etc/ultimateskillani/mage_hecate.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 245 || AWAKE_SKILL_ID == 139)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}



function drawThiefCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 222)
		awake = var.GetAnimationMap("thief_novaremnant", "common/cutscene/thief_novaremnant.ani");
	else if(AWAKE_SKILL_ID == 225)
		awake = var.GetAnimationMap("thief_ballacreadvent", "common/cutscene/thief_ballacreadvent.ani");
	else if(AWAKE_SKILL_ID == 100)
		awake = var.GetAnimationMap("thief_shiranui", "etc/ultimateskillani/thief_shiranui.ani");
	else if(AWAKE_SKILL_ID == 247)
		awake = var.GetAnimationMap("thief_grimreaper", "etc/ultimateskillani/thief_grimreaper.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && AWAKE_SKILL_ID == 222){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}



function drawATMageCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 245)
		awake = var.GetAnimationMap("atmage_armageddonstrike", "common/cutscene/atmage_armageddonstrike.ani");
	else if(AWAKE_SKILL_ID == 248)
		awake = var.GetAnimationMap("atmage_judekatheeternal", "common/cutscene/atmage_judekatheeternal.ani");
	else if(AWAKE_SKILL_ID == 95)
		awake = var.GetAnimationMap("atmage_vampirelord", "common/cutscene/atmage_vampirelord.ani");
	else if(AWAKE_SKILL_ID == 121)
		awake = var.GetAnimationMap("atmage_aiolos", "common/cutscene/atmage_aiolos.ani");
	else if(AWAKE_SKILL_ID == 124)
		awake = var.GetAnimationMap("atmage_ascension", "common/cutscene/atmage_ascension.ani");
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 248 || AWAKE_SKILL_ID == 124)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawATPriestCutinUI(obj)
{
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 113)
	{
		awake = var.GetAnimationMap("atpriest_seraphim", "etc/ultimateskillani/atpriest_seraphim.ani");
	}
	else if(AWAKE_SKILL_ID == 136)
	{
		awake = var.GetAnimationMap("atpriest_redeemer", "etc/ultimateskillani/atpriest_redeemer.ani");
	}
	else if(AWAKE_SKILL_ID == 249)
	{
		awake = var.GetAnimationMap("atpriest_goddess", "etc/ultimateskillani/atpriest_goddess.ani");
	}
	else if(AWAKE_SKILL_ID == 164)
	{
		awake = var.GetAnimationMap("atpriest_inferno", "etc/ultimateskillani/atpriest_inferno.ani");
	}
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 164 || AWAKE_SKILL_ID == 113)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

function drawATSwordmanCutinUI(obj){
	local var = obj.getVar();
	local awake = null;
	if(AWAKE_SKILL_ID == 166){
		awake = var.GetAnimationMap("atsword_deicide2dnc", "etc/ultimateskillani/atsword_deicide2dn.ani");
	}
	else if(AWAKE_SKILL_ID == 234){
		awake = var.GetAnimationMap("atsword_blade2nd", "etc/ultimateskillani/atsword_vendetta.ani");
	}
	else if(AWAKE_SKILL_ID == 141){
		awake = var.GetAnimationMap("atsword_majesty2nd", "etc/ultimateskillani/atsword_majesty.ani");
	}
	else if(AWAKE_SKILL_ID == 81){
		awake = var.GetAnimationMap("atsword_darktempler2nd", "etc/ultimateskillani/atsword_punishment.ani");
	}
	else if(AWAKE_SKILL_ID == 226){
		awake = var.GetAnimationMap("atsword_swordempress2nd", "etc/ultimateskillani/atsword_swordempress.ani");
	}
	else
		return;
	if(sq_IsEnd(awake))
	{
		AWAKE_SKILL_ID = -1;
		AWAKE_SKILL_DIRECTION = -1;
		sq_Rewind(awake);
		return;
	}else{
		if(AWAKE_SKILL_DIRECTION >= 0){
			awake.setImageRate(AWAKE_SKILL_DIRECTION ? 1.0 : (-1.0),1.0);
			sq_AnimationProc(awake);
			if(CFG_UI_AWAKE2_CUTIN_OFFSETX > 0 && (AWAKE_SKILL_ID == 141 || AWAKE_SKILL_ID == 81)){
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? 0 : (1066 - CFG_UI_AWAKE2_CUTIN_OFFSETX), 0, false);
			}
			else{
				sq_drawCurrentFrame(awake, AWAKE_SKILL_DIRECTION ? (-CFG_UI_AWAKE2_CUTIN_OFFSETX) : 1066, 0, false);
			}
		}else{
			AWAKE_SKILL_DIRECTION = obj.getDirection();
		}
	}
}

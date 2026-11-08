function drawCustomUI_AllGrowJob(obj)
{
	if(!obj) return;
	if(sq_IsMyCharacter(obj))
	{
		SkillCoolTimeUI(obj); //–¸“ˆ‘¡ı©
		NewRankSystem(obj); //¯ƒ›¬
	}
	if(USING_CRI_COUNT > 0 || USING_ACTIVE_COUNT > 0 || 
	   USING_SPECIAL_COUNT > 0 || USING_MAX_COUNT > 0)
	{
		drawDamageNumber(obj);
	}
	gal_DrawMonsterToSetCustomUIEffect(obj);
	gal_DrawMonsterEnergyCustomUIEffect(obj);
	gal_DrawMonsterEnergyCustomUIEffectSecond(obj);
	gal_DrawMonsterRedEnergyCustomUIEffect(obj);
	gal_DrawMonsterEnergyBallCustomUIEffect(obj);
	setCharacterComboUiAppendage(obj);
	drawTrainingroomMainUi(obj); //·Û÷°Ìﬁ
	return;
}

function drawCustomUI_ATSwordman(obj)
{
	if(!obj) return;
	sq_SetExSkillSlotVisible(true);
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawATSwordmanCutinUI(obj);
	return;
}


function drawCustomUI_Swordman(obj)
{
	if(!obj) return;
	local objtype = sq_getGrowType(obj);
	if(objtype==0){
		drawDevilStrikeGauge_Sword2(obj);//???ycc????
	}
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	drawHeroGhostIcon(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawSwordmanCutinUI(obj);
	return;
}

function drawCustomUI_ATFighter(obj)
{
	if(!obj) return;
	
	if(sq_isPVPMode()) return;
	drawCustomUI_SpiralInhale_by_ChangQing751675335(obj);
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawATFightCutinUI(obj);
	return;
}

function drawCustomUI_Fighter(obj)
{
	if(!obj) return;
	
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawFightCutinUI(obj);
	return;
}

function drawCustomUI_ATGunner(obj)
{
	if(!obj) return;
	
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawATGunnerCutinUI(obj);
	return;
}

function drawCustomUI_Gunner(obj)
{
	if(!obj) return;
	drawCustomUI_At_Sowalker_Energy_Bar(obj);
	assult_drawArcDischarge(obj);
	if (obj.getVar("sensibility").getBool(0) && sq_GetCurrentModuleType() != 2) {
		sq_setFullScreenEffect(obj, "character/gunner/effect/animation/sensibility/scanlline_00.ani");
		obj.getVar("sensibility").setBool(0, false);
	}
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawGunnerCutinUI(obj);
	return;
}

function drawCustomUI_ATMage(obj)
{
	if(!obj) return;
	drawBloodMageEnergyAbsortEffect(obj);
	drawBreakSenseCustomUI(obj);
	drawBloodMageUI(obj);
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawATMageCutinUI(obj);
	return;
}

function drawCustomUI_Mage(obj)
{
	if(!obj) return;
	drawBobyUi(obj);
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawMageCutinUI(obj);
	return;
}

function drawCustomUI_Priest(obj)
{
	if(!obj) return;
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawPriestCutinUI(obj);
	return;
}

function drawCustomUI_Thief(obj)
{
	if(!obj) return;
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawThiefCutinUI(obj);
	return;
}

function drawCustomUI_ATPriest(obj)
{
	if(!obj) return;
	if(sq_isPVPMode()) return;
	drawCustomUI_AllGrowJob(obj);
	if(DRAW_MONSTER_PID != -1)
		drawMonsterUI(obj);
	if(ULTIMATE_SKILL_ID != -1)
		drawUltimateCutinUI(obj);
	if(AWAKE_SKILL_ID != -1)
		drawATPriestCutinUI(obj);
	return;
}





function drawSwordmanBuffUI(obj,skillIndex)
{
	local ani;
	local aniPath;
	if(skillIndex == 18)
		aniPath = "etc/ultimateskillani/sword_soulbringer_neo_buff.ani";
	else if(skillIndex == 38)
		aniPath = "etc/ultimateskillani/sword_weaponmaster_neo_buff.ani";
	else if(skillIndex == 40)
		aniPath = "etc/ultimateskillani/sword_berserker_neo_buff.ani";
	else if(skillIndex == 47)
		aniPath = "etc/ultimateskillani/sword_asura_neo_buff.ani";
	else if(skillIndex == 69)
		aniPath = "etc/ultimateskillani/sword_swordghost_neo_buff.ani";
	else
		return;
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	if(equIndex == 1)
	{
		aniPath = "character/common/animation/2024_newyear_neobuff/swordman/sw24_cut_s_neo_buff.ani";
	}
	ani = sq_CreateAnimation("",aniPath);
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawATSwordmanBuffUI(obj,skillIndex)
{
	local ani;
	local aniPath;
	if(skillIndex == 146)
		aniPath = "etc/ultimateskillani/atsword_swordmaster_neo_buff.ani";
	else if(skillIndex == 209)
		aniPath = "etc/ultimateskillani/atghost_vegabond_neo_buff.ani";
	else if(skillIndex == 150)
		aniPath = "etc/ultimateskillani/atsword_demonslayer_neo_buff.ani";
	else if(skillIndex == 76)
		aniPath = "etc/ultimateskillani/atsword_darktemplar_neo_buff.ani";
	else if(skillIndex == 228)
		aniPath = "etc/ultimateskillani/atsword_blade_neo_buff.ani";
	else
		return;
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	if(equIndex == 1)
	{
		aniPath = "character/common/animation/2024_newyear_neobuff/atswordman/sg24_cut_s_neo_buff.ani";
	}
	CreateBuffCutin(obj,aniPath);
}

function drawGunnerBuffUI(obj,skillIndex)
{
	local ani;
	if(skillIndex == 46)
		ani = sq_CreateAnimation("","etc/ultimateskillani/gunner_mechanic_neo_buff.ani");
	else if(skillIndex == 60)
		ani = sq_CreateAnimation("","etc/ultimateskillani/gunner_ranger_neo_buff.ani");
	else if(skillIndex == 62)
		ani = sq_CreateAnimation("","etc/ultimateskillani/gunner_launcher_neo_buff.ani");
	else if(skillIndex == 252)
		ani = sq_CreateAnimation("","etc/ultimateskillani/gunner_spitfire_neo_buff.ani");
	else if(skillIndex == 112)
		ani = sq_CreateAnimation("","etc/ultimateskillani/gunner_assault_neo_buff.ani");
	else
		return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawATGunnerBuffUI(obj,skillIndex)
{
	local ani;
	if(skillIndex == 46)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atgunner_mechanic_neo_buff.ani");
	else if(skillIndex == 60)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atgunner_ranger_neo_buff.ani");
	else if(skillIndex == 62)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atgunner_launcher_neo_buff.ani");
	else if(skillIndex == 252)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atgunner_spitfire_neo_buff.ani");
	else
		return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawFightBuffUI(obj,skillIndex)
{
	local ani;
	if(skillIndex == 37){
		ani = sq_CreateAnimation("","etc/ultimateskillani/fighter_striker_neo_buff.ani");
	}
	else if(skillIndex == 38){
		if(sq_getGrowType(obj) == 3){
			ani = sq_CreateAnimation("","etc/ultimateskillani/fighter_streetfighter_neo_buff.ani");
		}
		else{
			return;
		}
	}
	else if(skillIndex == 50){
		ani = sq_CreateAnimation("","etc/ultimateskillani/fighter_grappler_neo_buff.ani");
	}
	else if(skillIndex == 31){
		ani = sq_CreateAnimation("","etc/ultimateskillani/fighter_nenmaster_neo_buff.ani");
	}
	else{
		return;
	}
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawATFighterBuffUI(obj,skillIndex)
{
	local ani;
	if(skillIndex == 31)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atfighter_nenmaster_neo_buff.ani");
	else if(skillIndex == 43)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atfighter_streetfighter_neo_buff.ani");
	else if(skillIndex == 50)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atfighter_grappler_neo_buff.ani");
	else if(skillIndex == 37)
		ani = sq_CreateAnimation("","etc/ultimateskillani/atfighter_striker_neo_buff.ani");
	else
		return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawPriestBuffUI(obj,skillIndex)
{
	local ani;
	if(skillIndex == 35)
		ani = sq_CreateAnimation("","etc/ultimateskillani/priest_infighter_neo_buff.ani");
	else if(skillIndex == 45)
		ani = sq_CreateAnimation("","etc/ultimateskillani/priest_crusader_neo_buff.ani");
	else if(skillIndex == 47)
		ani = sq_CreateAnimation("","etc/ultimateskillani/priest_exorcist_neo_buff.ani");
	else if(skillIndex == 48)
		ani = sq_CreateAnimation("","etc/ultimateskillani/priest_exorcist_neo_buff.ani");
	else if(skillIndex == 131)
		ani = sq_CreateAnimation("","etc/ultimateskillani/priest_avenger_neo_buff.ani");
	else
		return;
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawMageBuffUI(obj,skillIndex)
{
	local ani;
	local aniPath;
	if(skillIndex == 29)
		aniPath = "etc/ultimateskillani/mage_elementalmaster_neo_buff.ani";
	else if(skillIndex == 81)
		aniPath = "etc/ultimateskillani/mage_summoner_neo_buff.ani";
	else if(skillIndex == 40)
		aniPath = "etc/ultimateskillani/mage_battlemage_neo_buff.ani";
	else if(skillIndex == 41)
		aniPath = "etc/ultimateskillani/mage_witch_neo_buff.ani";
	else if(skillIndex == 128)
		aniPath = "etc/ultimateskillani/mage_enchantress_neo_buff.ani";
	else
		return;
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	if(equIndex == 1)
	{
		aniPath = "etc/ultimateskillani/chn_2023autumn_neobuff/mage_neo_buff.ani";
	}
	ani = sq_CreateAnimation("",aniPath);
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawATMageBuffUI(obj,skillIndex)
{
	local ani;
	local aniPath;
	if(skillIndex == 28)
		aniPath = "etc/ultimateskillani/atmage_elementalbomber_neo_buff.ani";
	else if(skillIndex == 31)
		aniPath = "etc/ultimateskillani/atmage_glacialmaster_neo_buff.ani";
	else if(skillIndex == 97)
		aniPath = "etc/ultimateskillani/atmage_bloodmage_neo_buff.ani";
	else if(skillIndex == 142)
		aniPath = "etc/ultimateskillani/atmage_swiftmaster_neo_buff.ani";
	else if(skillIndex == 158)
		aniPath = "etc/ultimateskillani/atmage_dimensionwalker_neo_buff.ani";
	else
		return;
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	if(equIndex == 1)
	{
		aniPath = "etc/ultimateskillani/chn_2023autumn_neobuff/atmage_neo_buff.ani";
	}
	ani = sq_CreateAnimation("",aniPath);
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}


function drawThiefBuffUI(obj,skillIndex)
{
	local ani;
	local aniPath;
	if(skillIndex == 230)
	{
		aniPath = "etc/ultimateskillani/thief_rogue_neo_buff.ani";
	}
	else if(skillIndex == 50)
	{
		aniPath = "etc/ultimateskillani/thief_necro_neo_buff.ani";
	}
	else if(skillIndex == 78)
	{
		aniPath = "etc/ultimateskillani/thief_kunoichi_neo_buff.ani";
	}
	else if(skillIndex == 239)
	{
		aniPath = "etc/ultimateskillani/thief_shadowdancer_neo_buff.ani";
	}
	else
	{
		return;
	}
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	if(equIndex == 1)
	{
		aniPath = "etc/ultimateskillani/chn_2023autumn_neobuff/thief_neo_buff.ani";
	}
	ani = sq_CreateAnimation("",aniPath);
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
}

function drawATPriestBuffUI(obj,skillIndex){
	
	local equIndex = sq_GetLevelData(obj, 169, 2, 1);
	local aniPath;
	if(skillIndex == 78){
		aniPath = "etc/ultimateskillani/priestf_crusader_buff.ani";
	}
	else if(skillIndex == 139)
	{
		aniPath = "etc/ultimateskillani/priestf_mistress_buff.ani";
	}
	else if(skillIndex == 217)
	{
		aniPath = "etc/ultimateskillani/priestf_inquisitor_buff.ani";
	}
	else
	{
		return;
	}
	local ani = sq_CreateAnimation("",aniPath);
	local pooledObj = sq_CreatePooledObject(ani,true);
	local xPos = obj.getXPos();
	local yPos = obj.getObjectManager().getFieldYPos(0, 0, 0);
	pooledObj.setCurrentPos(xPos,yPos,0);
	pooledObj.setDrawLayer(ENUM_DRAWLAYER_BOTTOM);
	sq_AddObject(obj,pooledObj,OBJECTTYPE_DRAWONLY,false);
	
	if(equIndex == 1)
	{
		sq_AddDrawOnlyAniFromParent(obj,"character/common/animation/uniquebeast_1st/at_priest/SinsuATPriestChange_Front_ToSymbol_01.ani", 0, 1, 0);
		sq_AddDrawOnlyAniFromParent(obj,"character/common/animation/uniquebeast_1st/at_priest/SinsuATPriestChange_Back_00.ani", 0, -1, 0);
		sq_AddDrawOnlyAniFromParent(obj,"character/common/animation/uniquebeast_1st/at_priest/SinsuATPriestChange_Bottom_00.ani", 0, -2, 0);
	}
}

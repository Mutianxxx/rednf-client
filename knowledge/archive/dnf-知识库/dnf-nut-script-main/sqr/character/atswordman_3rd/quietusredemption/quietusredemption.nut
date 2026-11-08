
function checkExecutableSkill_quietusredemption(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_QUIETUSREDEMPTION);
	if (isUse)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		obj.getVar("dark100POS").clear_vector();
		obj.getVar("dark100POS").push_vector(posX);
		obj.getVar("dark100POS").push_vector(posY);
		obj.getVar("dark100POS").push_vector(posZ);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_QUIETUSREDEMPTION, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_quietusredemption(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_quietusredemption(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_quietusredemptioncasting_body);
		
		obj.sq_SendCreatePassiveObjectPacket(2191304, 0, 0, 0, 0);

		local randNum = sq_getRandom(1, 3);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_01_1");
		if(randNum == 2)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_02_1");
		if(randNum == 3)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_03_1");
		
		local castingshockwave_02 = "character/swordman/effect/animation/3rd/atquietusredemption/casting/castingshockwave_02.ani";
		ATSwordman_Create(obj,castingshockwave_02,ENUM_DRAWLAYER_NORMAL,-10,-50,0,0,100,0,100,"castingshockwave_02");
	}
	if(substate == 1)
	{
		obj.setObjectHeight(999);

		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(500+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(500, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_quietusredemptionmotion_body);
		obj.sq_SetShake(obj,5,300);
		sq_flashScreen(obj, 0, 5000, 500, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_01_2");
	}
	if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_quietusredemptionendmotion_body);
	}
}

function onKeyFrameFlag_quietusredemption(obj,flagIndex)
{
	if(!obj)
		return false;

	if (flagIndex == 0)
	{
		local quietusredemptionusire_15 = "character/swordman/effect/animation/3rd/atquietusredemption/finish/quietusredemptionusire_15.ani";
		ATSwordman_Create(obj,quietusredemptionusire_15,ENUM_DRAWLAYER_BOTTOM,-30,50,0,0,70,0,120,"quietusredemptionusire_15");
		local quietusredemptionsoul_17 = "character/swordman/effect/animation/3rd/atquietusredemption/finish/quietusredemptionsoul_17.ani";
		ATSwordman_Create(obj,quietusredemptionsoul_17,ENUM_DRAWLAYER_BOTTOM,-30,-50,0,0,60,0,110,"quietusredemptionsoul_17");
		local quietusredemptionboomback_00 = "character/swordman/effect/animation/3rd/atquietusredemption/finish/quietusredemptionboomback_00.ani";
		ATSwordman_Create(obj,quietusredemptionboomback_00,ENUM_DRAWLAYER_COVER,-30,-220,0,0,80,0,110,"quietusredemptionboomback_00");
		local quietusredemptionboomfront_07 = "character/swordman/effect/animation/3rd/atquietusredemption/finish/quietusredemptionboomfront_07.ani";
		ATSwordman_Create(obj,quietusredemptionboomfront_07,ENUM_DRAWLAYER_COVER,-30,-220,0,0,50,0,118,"quietusredemptionboomfront_07");
	}
	if (flagIndex == 14)
	{
		local atsword_darktemplar_neo = "sqr/character/atswordman_3rd/quietusredemption/atsword_darktemplar_neo.ani";
		ATSwordman_Create(obj,atsword_darktemplar_neo,ENUM_DRAWLAYER_COVER,-480,-500,0,0,100,0,100,"atsword_darktemplar_neo");
	}
	if (flagIndex == 22)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 23)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 24)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 25)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 26)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 27)
	{
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}

	if (flagIndex == 33)
	{
		local randNum = sq_getRandom(1, 3);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_01_3");
		if(randNum == 2)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_02_3");
		if(randNum == 3)
		obj.sq_PlaySound("SW_QUIETUS_REDEMPTION_03_3");
	}

	if (flagIndex == 42)
	{
		obj.sq_SetShake(obj,10,300);
		obj.sq_StartWrite();
		obj.sq_WriteDword(2);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 43)
	{
		obj.sq_SetShake(obj,8,300);
		obj.sq_StartWrite();
		obj.sq_WriteDword(2);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	if (flagIndex == 44)
	{
		obj.sq_SetShake(obj,8,300);
		obj.sq_StartWrite();
		obj.sq_WriteDword(2);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	return true;
}

function onEndCurrentAni_quietusredemption(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_QUIETUSREDEMPTION, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_QUIETUSREDEMPTION, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 2)
	{
		obj.setObjectHeight(110);
		local srcX = obj.getVar("dark100POS").get_vector(0);
		local srcY = obj.getVar("dark100POS").get_vector(1);
		local srcZ = obj.getVar("dark100POS").get_vector(2);
		obj.sq_SetCurrentPos(obj, srcX, srcY, srcZ);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}


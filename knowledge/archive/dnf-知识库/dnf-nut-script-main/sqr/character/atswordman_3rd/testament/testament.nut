
function checkExecutableSkill_testament(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_TESTAMENT);
	if (isUse)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_TESTAMENT, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_testament(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_testament(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	
	if(substate == 0)
	{
		local randNum = sq_getRandom(1, 2);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_TESTAMENT_01_A");
		if(randNum == 2)
		obj.sq_PlaySound("SW_TESTAMENT_01_B");

		obj.setObjectHeight(999);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_testamentstart_body);
		sq_flashScreen(obj, 0, 7000, 500, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		local testamentstart_bodyeffect = "character/swordman/effect/animation/3rd/attestament/testamentstart_bodyeffect.ani";
		ATSwordman_Create(obj,testamentstart_bodyeffect,ENUM_DRAWLAYER_COVER,0,0,0,0,100,0,100,"testamentstart_bodyeffect");
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_testamentfronta_body);
		local testamentfronta_body = "character/swordman/atanimation/3rd/testamentfronta_new_body.ani";
		ATSwordman_Create(obj,testamentfronta_body,ENUM_DRAWLAYER_COVER,-90,0,0,0,110,0,100,"testamentfronta_body");

		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(MAP_AT_XPOS, ENUM_DRAWLAYER_COVER);
		local yPos = objectManager.getFieldYPos(MAP_AT_YPOS, 1, ENUM_DRAWLAYER_COVER);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		obj.sq_SetShake(obj,40,300);
	}
	if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_testamentendbody_body);
		obj.sq_PlaySound("TESTAMENT_END");
	}
}

function onKeyFrameFlag_testament(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		local testamentbackground_05 = "character/swordman/effect/animation/3rd/attestament/testamentbackground_05.ani";
		ATSwordman_Create(obj,testamentbackground_05,ENUM_DRAWLAYER_NORMAL,0,0,0,0,80,0,88,"testamentbackground_05");
		local testamentfronta_59 = "character/swordman/effect/animation/3rd/attestament/testamentfronta_59.ani";
		ATSwordman_Create(obj,testamentfronta_59,ENUM_DRAWLAYER_NORMAL,0,-100,0,0,100,0,100,"testamentfronta_59");

		obj.sq_SetShake(obj,30,200);
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(MAP_AT_XPOS, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(MAP_AT_YPOS, 0, ENUM_DRAWLAYER_NORMAL);

		local Objectacc = GetATSwordmanTarget_Contes(obj)
		if(!Objectacc)
		Objectacc = GetATSwordmanTarget_ContesT(obj)
		local damager = Objectacc
		if(damager && damager.getState() != STATE_DIE)
		{
			local width = sq_GetWidthObject(damager);
			local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 85 + (width / 2));
			obj.sq_SetCurrentPos(damager, posX, obj.getYPos(), 0);
			if (obj.sq_IsMyControlObject())
			sq_ChangeDrawLayer(damager, ENUM_DRAWLAYER_CONTACT);
		}
		local testamentfronta_37 = "passiveobject/atswordman_3rd/atanimation/attestament/testamentfronta_37.ani";
		ATSwordman_Create(obj,testamentfronta_37,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"testamentfronta_37");
		local testamentfronta_38 = "passiveobject/atswordman_3rd/atanimation/attestament/testamentfronta_38.ani";
		ATSwordman_Create(obj,testamentfronta_38,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"testamentfronta_38");
	}
	else if (flagIndex == 2)
	{
		local randNum = sq_getRandom(1, 2);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_TESTAMENT_02_A");
		if(randNum == 2)
		obj.sq_PlaySound("SW_TESTAMENT_02_B");

		obj.sq_SendCreatePassiveObjectPacket(2191305, 0, 0, 0, 0);
		local Objectacc = GetPriorityTarget_Contes(obj)
		if(!Objectacc)
		Objectacc = GetPriorityTarget_ContesT(obj)
		local damager = Objectacc
		if(damager && damager.getState() != STATE_DIE)
		{
			sq_ChangeDrawLayer(damager, ENUM_DRAWLAYER_NORMAL);
		}
		obj.sq_SetShake(obj,3,200);
		obj.sq_StartWrite();
		obj.sq_WriteDword(3);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);

	}
	else if (flagIndex == 9)
	{
		local attestamentTestamentFrontA_41 = "character/swordman/effect/animation/3rd/attestamentTestamentFrontA_41.ani";
		ATSwordman_Create(obj,attestamentTestamentFrontA_41,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"attestamentTestamentFrontA_41");
	}
	else if (flagIndex == 31)
	{
		obj.sq_SetShake(obj,20,300);
	}
	else if (flagIndex == 51)
	{
		obj.sq_SetShake(obj,20,300);
		obj.sq_StartWrite();
		obj.sq_WriteDword(4);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);

	}
	else if (flagIndex == 58)
	{
		local atsword_blade_neo = "sqr/character/atswordman_3rd/testament/atsword_blade_neo.ani";
		ATSwordman_Create(obj,atsword_blade_neo,ENUM_DRAWLAYER_COVER,-480,-450,0,0,100,0,100,"atsword_blade_neo");
	}
	else if (flagIndex == 81)
	{
		local randNum = sq_getRandom(1, 2);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_TESTAMENT_03_A");
		if(randNum == 2)
		obj.sq_PlaySound("SW_TESTAMENT_03_B");

		obj.sq_SetShake(obj,20,300);
		obj.sq_StartWrite();
		obj.sq_WriteDword(5);
		obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
	}
	return true;
}

function onEndCurrentAni_testament(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_TESTAMENT, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_TESTAMENT, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 2)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		if (!obj.isMovablePos(posX, posY))
		{
			sq_MoveToNearMovablePos(obj, posX, posY, 0, posX, posY, posZ, 1000, -1, 3);
		}
		obj.setObjectHeight(110);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

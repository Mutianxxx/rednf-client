function checkExecutableSkill_alcatraz(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_ALCATRAZ);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_ALCATRAZ, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_alcatraz(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_alcatraz(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	local isMyControlObject = obj.sq_IsMyControlObject();
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AlcatrazStart_Body);
		local objectManager = obj.getObjectManager();
		if (isMyControlObject)
		{
			local objectManager = obj.getObjectManager();
			for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
			{
				local object = objectManager.getCollisionObject(i);
				if (object && !object.isObjectType(OBJECTTYPE_ACTIVE))
				{
					sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_BOTTOM);
				}
			}
		}
	}
	else if(substate == 1)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(430, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);

		ATSwordman_Als_Ani(obj, "character/swordman/atanimation/3rd/alcatraz_body_old.ani", 0, 1, 0, 0, 100, 1, 1.0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_Alcatrazbody_Body);
		obj.setTimeEvent(0, 80, 30,true);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_alcatrazmultihit);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ALCATRAZ , -1, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
	}
	else if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AlcatrazEnd_Body);
	}
}

function onTimeEvent_alcatraz(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;
	if(timeEventIndex == 0)
	{
		obj.resetHitObjectList();
	}
}

function onEndCurrentAni_alcatraz(obj)
{
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_ALCATRAZ, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_ALCATRAZ, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 2)
	{
		local isMyControlObject = obj.sq_IsMyControlObject();
		local objectManager = obj.getObjectManager();
		if (isMyControlObject)
		{
			local objectManager = obj.getObjectManager();
			for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
			{
				local object = objectManager.getCollisionObject(i);
				if (object && !object.isObjectType(OBJECTTYPE_ACTIVE))
				{
					sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_NORMAL);
				}
			}
		}
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		if (!obj.isMovablePos(posX, posY))
		{
			sq_MoveToNearMovablePos(obj, posX, posY, 0, posX, posY, posZ, 1000, -1, 3);
		}
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_alcatraz(obj,flagIndex)
{
	if(!obj)
	return false;
	if (flagIndex == 0)
	{
		obj.sq_SetShake(obj,7,250);
		local alcatrazbackground_00 = "character/swordman/effect/animation/3rd/atalcatraz/alcatrazbackground_00.ani";
		ATSwordman_Create(obj,alcatrazbackground_00,ENUM_DRAWLAYER_NORMAL,0,-2,0,0,100,0,100,"alcatrazbackground_00");

		local alcatrazbottom_00 = "character/swordman/effect/animation/3rd/atalcatraz/alcatrazbottom_00.ani";
		ATSwordman_Create(obj,alcatrazbottom_00,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,0,100,"alcatrazbottom_00");

		local alcatrazcover_12 = "character/swordman/effect/animation/3rd/atalcatraz/alcatrazcover_12.ani";
		ATSwordman_Create(obj,alcatrazcover_12,ENUM_DRAWLAYER_COVER,0,0,0,0,100,0,100,"alcatrazcover_12");
	}
	if (flagIndex == 12)
	{

	}
	if (flagIndex == 17)
	{
		local alcatrazhiteffect_00 = "character/swordman/effect/animation/3rd/atalcatraz/alcatrazhiteffect_00.ani";
		ATSwordman_Create(obj,alcatrazhiteffect_00,ENUM_DRAWLAYER_COVER,0,0,0,0,100,0,100,"alcatrazhiteffect_00");
	}
	if (flagIndex == 22)
	{
		sq_flashScreen(obj, 0, 60, 0, 125, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,6,180);
	}
	if (flagIndex == 25)
	{
		obj.sq_SetShake(obj,3,900);
		local demonslayer_neo = "sqr/character/atswordman_3rd/alcatraz/atsword_demonslayer_neo.ani";
		ATSwordman_Create(obj,demonslayer_neo,ENUM_DRAWLAYER_COVER,-460,-480,0,0,100,0,100,"demonslayer_neo");
	}
	if (flagIndex == 26)
	{
		sq_flashScreen(obj, 0, 60, 0, 125, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	if (flagIndex == 28)
	{
	}
	if (flagIndex == 33)
	{
		sq_flashScreen(obj, 0, 60, 0, 125, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	if (flagIndex == 36)
	{
		sq_flashScreen(obj, 0, 60, 600, 178, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	if (flagIndex == 53)
	{

	}
	if (flagIndex == 56)
	{

	}
	if (flagIndex == 57)
	{
		sq_flashScreen(obj, 0, 0, 120, 153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,6,480);
	}
	if (flagIndex == 58)
	{

	}
	if (flagIndex == 63)
	{
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_alcatrazlastattack);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ALCATRAZ , -1, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

		sq_flashScreen(obj, 0, 0, 120, 153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,35,500);
	}
	if (flagIndex == 72)
	{
		sq_flashScreen(obj, 150, 200, 300, 255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
	}
	if (flagIndex == 100)
	{
		obj.sq_SetShake(obj,5,250);
	}
	return true;
}
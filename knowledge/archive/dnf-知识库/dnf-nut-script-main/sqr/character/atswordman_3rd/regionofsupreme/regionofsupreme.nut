function checkExecutableSkill_regionofsupreme(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_REGIONOFSUPREME);
	if (isUse)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		obj.getVar("34POS").clear_vector();
		obj.getVar("34POS").push_vector(posX);
		obj.getVar("34POS").push_vector(posY);
		obj.getVar("34POS").push_vector(posZ);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_REGIONOFSUPREME, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_regionofsupreme(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_regionofsupreme(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	local isMyControlObject = obj.sq_IsMyControlObject();
	if(substate == 0)
	{
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(450, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtregionofSupremesinBody_1);
		obj.sq_PlaySound("ROS_CAST");
		if (isMyControlObject)
		{
			local objectManager = obj.getObjectManager();
			for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
			{
				local object = objectManager.getCollisionObject(i);
				if (object)
				{
					sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_NORMAL);
				}
				sq_flashScreen(obj, 150, 6000, 250, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_NORMAL);

				local Sin1Cover = "character/swordman/effect/animation/3rd/atregionofsupreme/sin1/atregionofsupremesin1cover_00.ani";
				ATSwordman_Create(obj,Sin1Cover,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,1,100,"Sin1Cover");

				local Sin1ScreenBack = "character/swordman/effect/animation/3rd/atregionofsupreme/sin1/atregionofsupremesin1screenback_00.ani";
				ATSwordman_Create(obj,Sin1ScreenBack,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,1,100,"Sin1ScreenBack");
			}
		}
	}
	else if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtregionofSupremesinBody_2);
		if (isMyControlObject)
		{
		local Sin2Body = "character/swordman/effect/animation/3rd/atregionofsupremesin2body_body_al.ani";
		ATSwordman_Create(obj,Sin2Body,ENUM_DRAWLAYER_COVER,0,0,0,0,100,1,100,"Sin2Body");

		local Sin2BodyTT = "character/swordman/effect/animation/3rd/atregionofsupreme/sin2/atregionofsupremesin2body_00.ani";
		ATSwordman_Create(obj,Sin2BodyTT,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,1,100,"Sin2BodyTT");

		local Sin2Cover = "character/swordman/effect/animation/3rd/atregionofsupreme/sin2/atregionofsupremesin2cover_00.ani";
		ATSwordman_Create(obj,Sin2Cover,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,1,100,"Sin2Cover");

		local Sin2ScreenBack = "character/swordman/effect/animation/3rd/atregionofsupreme/sin2/atregionofsupremesin2screenback_00.ani";
		ATSwordman_Create(obj,Sin2ScreenBack,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,1,100,"Sin2ScreenBack");
		}
	}
	else if(substate == 2)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtregionofSupremesinBody_2Dash);
		if (isMyControlObject)
		{
			local Sin3ScreenBack = "character/swordman/effect/animation/3rd/atregionofsupreme/sin3/atregionofsupremesin3screenback_00.ani";
			ATSwordman_Create(obj,Sin3ScreenBack,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,1,100,"Sin3ScreenBack");

			local Dash_light = "character/swordman/effect/animation/3rd/ATRegionOfSupreme/Sin2/ATRegionOfSupremeSin2Body_dash_light.ani";
			ATSwordman_Create(obj,Dash_light,ENUM_DRAWLAYER_NORMAL,0,1,0,0,100,1,100,"Dash_light");

			local Sin3Cover = "character/swordman/effect/animation/3rd/atregionofsupreme/sin3/atregionofsupremesin3cover_00.ani";
			ATSwordman_Create(obj,Sin3Cover,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,1,100,"Sin3Cover");
			obj.setTimeEvent(0, 85, 15,true);
		}
	}
	else if(substate == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtregionofSupremesinBody_3);
		if (isMyControlObject)
		{
		sq_flashScreen(obj, 150, 1300, 250, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_NORMAL);
			local objectManager = obj.getObjectManager();

			for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
			{
				local object = objectManager.getCollisionObject(i);
				if (object)
				{
					sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_NORMAL);
				}
			}
		}
	}
	else if(substate == 4)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtregionofSupremesinBody_Cancel);
	}
}

function onEndCurrentAni_regionofsupreme(obj)
{
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_REGIONOFSUPREME, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_REGIONOFSUPREME, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 2)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_REGIONOFSUPREME, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 3)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_AddSetStatePacket(STATE_REGIONOFSUPREME, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 4)
	{
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

function onTimeEvent_regionofsupreme(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;
	local AttackBox = "passiveobject/atwordman/animation/atregionofsupreme/regionofsupremeattack.ani";
	local AttackAtk0 = "passiveobject/atwordman/attackinfo/atregionofsupremeattack.atk";
	local AttackAtk1 = "passiveobject/atwordman/attackinfo/atregionofsupremefinishmultihit.atk";
	local AttackAtk2 = "passiveobject/atwordman/attackinfo/atregionofsupremefinish.atk";

	local Damage0 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 0, 3.0);
	local Damage1 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 2, 3.0);
	local Damage2 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 1, 2.0);
	if(timeEventIndex == 0)
	{
		sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk1 ,false,Damage1,100,0,0,0);
	}
}


function onKeyFrameFlag_regionofsupreme(obj,flagIndex)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();

	local AttackBox = "passiveobject/atwordman/animation/atregionofsupreme/regionofsupremeattack.ani";
	local AttackAtk0 = "passiveobject/atwordman/attackinfo/atregionofsupremeattack.atk";
	local AttackAtk1 = "passiveobject/atwordman/attackinfo/atregionofsupremefinishmultihit.atk";
	local AttackAtk2 = "passiveobject/atwordman/attackinfo/atregionofsupremefinish.atk";
	local Damage0 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 0, 3.0);
	local Damage1 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 2, 3.0);
	local Damage2 = obj.sq_GetBonusRateWithPassive(SKILL_REGIONOFSUPREME , -1, 1, 2.0);

	if(substate == 0)
	{
		if (flagIndex == 14)
		{
			obj.sq_SetShake(obj,10,50);
		}
		if (flagIndex == 21)
		{
			obj.sq_SetShake(obj,3,50);
		}
		if (flagIndex == 22)
		{
			sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk0 ,false,Damage0,100,0,0,0);
		}
		if (flagIndex == 27)
		{
			obj.sq_SetShake(obj,3,50);
		}
		if (flagIndex == 28)
		{
			sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk0 ,false,Damage0,100,0,0,0);
		}
		if (flagIndex == 35)
		{
			obj.sq_SetShake(obj,3,50);
		}
		if (flagIndex == 36)
		{
			sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk0 ,false,Damage0,100,0,0,0);
		}
		if (flagIndex == 41)
		{
			obj.sq_SetShake(obj,9,20);
			sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk0 ,false,Damage0,100,0,0,0);
			local atsword_swordmaster_neo = "sqr/character/atswordman_3rd/regionofsupreme/atsword_swordmaster_neo.ani";
			ATSwordman_Create(obj,atsword_swordmaster_neo,ENUM_DRAWLAYER_COVER,-460,-480,0,0,100,0,100,"atsword_swordmaster_neo");
		}
	}
	if(substate == 1)
	{
		if (flagIndex == 1)
		{
		}
		if (flagIndex == 22)
		{
			obj.sq_SetShake(obj,10,35);
		}
	}
	if(substate == 3)
	{
		if (flagIndex == 0)
		{
		}
		if (flagIndex == 1)
		{
			obj.sq_SetShake(obj,5,350);
		}
		if (flagIndex == 8)
		{
			obj.sq_SetShake(obj,11,300);
			sq_createAttackObjectWithPath(obj, AttackBox ,AttackAtk2 ,false,Damage2,100,0,0,0);
		}
		if (flagIndex == 9)
		{
		}
		if (flagIndex == 18)
		{
			obj.sq_SetShake(obj,5,170);
			local Sin3Bottom = "character/swordman/effect/animation/3rd/atregionofsupreme/sin3/atregionofsupremesin3screenbottom_01.ani";
			ATSwordman_Create(obj,Sin3Bottom,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,1,100,"Sin3Bottom");
		}
		if (flagIndex == 22)
		{
		}
	}
	return true;
}
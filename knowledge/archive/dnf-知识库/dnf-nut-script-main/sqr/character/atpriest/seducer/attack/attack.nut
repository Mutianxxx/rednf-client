ROSEHIT_EFFECT_COUNT	<- 1

function onSetState_Attackseducer(obj, state, datas, isResetTimer)
{
	if(!obj) return
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
}

function onAttack_Attackseducer(obj, damager, boundingBox, isStuck)
{
	if(!obj) return;
	if (!damager) return;
	if(!damager.isObjectType(OBJECTTYPE_ACTIVE)) return;
	local attackIndex = obj.getAttackIndex();
	if(sq_GetSkillLevel(obj, SKILL_BODYPRESSEDSIN) > 0)
	{
		ROSEHIT_EFFECT_COUNT = 0;
		local rand = sq_getRandom(0, 15).tointeger();
		local ani = null;
		if (rand <= 5)
			ani = sq_AddDrawOnlyAniFromParent(damager,"common/hiteffect/animation/rosehiteffect/attemptresshiteffect_slash_small1.ani", 0, 1, sq_GetObjectHeight(damager)*2/5);
		else if (rand <= 10)
			ani = sq_AddDrawOnlyAniFromParent(damager,"common/hiteffect/animation/rosehiteffect/attemptresshiteffect_slash_small2.ani", 0, 1, sq_GetObjectHeight(damager)*2/5);
		else if (rand <= 15)
			ani = sq_AddDrawOnlyAniFromParent(damager,"common/hiteffect/animation/rosehiteffect/attemptresshiteffect_slash_small3.ani", 0, 1, sq_GetObjectHeight(damager)*2/5);
		if(ani)
			sq_moveWithParent(damager, ani);
	}
}

function onAttack_dash_attackseducer(obj, damager, boundingBox, isStuck)
{
	if(!obj) return;
	if (!damager) return;
	if(!damager.isObjectType(OBJECTTYPE_ACTIVE)) return;
	local attackIndex = obj.getAttackIndex();
	if(sq_GetSkillLevel(obj, SKILL_BODYPRESSEDSIN) > 0)
	{
		ROSEHIT_EFFECT_COUNT = 0;
		local ani = sq_AddDrawOnlyAniFromParent(damager,"common/hiteffect/animation/rosehiteffect/attemptresshiteffect_slash_small2.ani", 0, 1, sq_GetObjectHeight(damager)*2/5);
		if(ani)
			sq_moveWithParent(damager, ani);
	}
}

function onKeyFrameFlag_Attackseducer(obj, flagIndex)
{
	if(!obj) return false;
	local attackIndex = obj.getAttackIndex();
	if (Seducer(obj))
	{
		if (flagIndex == 0)
		{
			obj.sq_PlaySound("R_PW_1ATK_DM");
		}
	}
	else if(isHolyFlame(obj))
	{
		if (flagIndex == 1)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(105 + attackIndex);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 1, 0);
		}
	}
	return true;
}

function onAfterSetState_dash_attackseducer(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	if(obj.sq_IsMyControlObject() && sq_GetSkillLevel(obj, SKILL_BODYPRESSEDSIN) > 0)
	{
		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector( obj.getXPos() );
		obj.getVar("pos").push_vector( obj.sq_GetIntData(SKILL_DEPRAVITYSEVENSINS, 4) );
		ROSEHIT_EFFECT_COUNT = 1;
	}
	if(sq_GetSkillLevel(obj, SKILL_CRUSADE) > 0)
	{
		local power = obj.sq_GetPowerWithPassive(174, -1, 1, -1, 0.07);
		power = 45 + power;
		obj.sq_SetCurrentAttackPower(power.tointeger());
	}
}

function onAfterSetState_Attackseducer(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	if(obj.sq_IsMyControlObject() && sq_GetSkillLevel(obj, SKILL_BODYPRESSEDSIN) > 0)
	{
		ROSEHIT_EFFECT_COUNT = 1;
	}
	if(sq_GetSkillLevel(obj, SKILL_CRUSADE) > 0)
	{
		local power = obj.sq_GetPowerWithPassive(174, -1, 0, -1, 0.07);
		power = 45 + power;
		obj.sq_SetCurrentAttackPower(power.tointeger());
	}
}

function onKeyFrameFlag_dash_attackseducer(obj, flagIndex)
{
	if(!obj) return false;
	if(isHolyFlame(obj))
	{
		if (flagIndex == 1)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(108);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 1, 0);
		}
	}
	return true;
}

function onProc_dash_attackseducer(obj)
{
	if(!obj) return;
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	if (Seducer(obj))
	{
		local pAni = obj.sq_GetCurrentAni();
		local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


		local startFrameIndex = 0;
		local endFrameIndex = 5;

		local currentT = sq_GetCurrentTime(pAni);

		if (frmIndex < startFrameIndex)
		{
		}else if (frmIndex > startFrameIndex && frmIndex <= endFrameIndex)
		{
			local startX = obj.getVar("pos").get_vector(0);
			local maxD = obj.getVar("pos").get_vector(1);

			currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
			local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
			if (currentT < maxT)
			{
				local v = sq_GetAccel(0, maxD, currentT,maxT, true);
				local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
				if( obj.isMovablePos(dstX, obj.getYPos() ))
				{
					sq_setCurrentAxisPos(obj, 0, dstX);
				}

			}
		}
	}
}


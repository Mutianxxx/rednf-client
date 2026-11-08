function checkExecutableSkill_atfusionblade(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_ATFUSIONBLADE);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_ATFUSIONBLADE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_atfusionblade(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_atfusionblade(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	if(substate == 0)
	{
		obj.sq_SetXScrollStart(200, 100);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtfusionBladeBody_Start);
		sq_flashScreen(obj, 500, 720, 250, 190, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_StartWrite();
		obj.sq_WriteDword(54);
		obj.sq_SendCreatePassiveObjectPacket(24238, 0, -90, -30, 140);
		obj.sq_StartWrite();
		obj.sq_WriteDword(57);
		obj.sq_SendCreatePassiveObjectPacket(24238, 0, -90, -10, 110);
		obj.sq_StartWrite();
		obj.sq_WriteDword(60);
		obj.sq_SendCreatePassiveObjectPacket(24238, 0, -110, 10, 70);
		obj.sq_StartWrite();
		obj.sq_WriteDword(63);
		obj.sq_SendCreatePassiveObjectPacket(24238, 0, -100, 30, 20);
		obj.sq_PlaySound("FUSIONBLADE_CAST");

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_fusionblade);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ATFUSIONBLADE , -1, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
	}
	else if(substate == 1)
	{
		obj.sq_SetXScrollStop(100);
		sq_flashScreen(obj, 100, 100, 200, 150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,20,80);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_AtfusionBladeBody_End);
	}
}

function onEndCurrentAni_atfusionblade(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_ATFUSIONBLADE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onAttack_Skill33(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		sq_AtrractionForce(obj, damager, false, 215, -1, 650.0, 400.0, false);
	}
	MagicswordupOccur(obj, damager, boundingBox, isStuck)
}

function onKeyFrameFlag_atfusionblade(obj,flagIndex)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		if (flagIndex == 0)
		{
		}
		if (flagIndex == 4)
		{
			ATSwordman_Als_Ani(obj,"character/swordman/effect/animation/3rd/atfusionblade/atfusionbladestartaurafront_00.ani",150, 0, 80, 0, 100, 0, 1.0);
		}
		if (flagIndex == 11)
		{
		}
		if (flagIndex == 12)
		{
			obj.sq_SetShake(obj,4,200);
		}
		if (flagIndex == 14)
		{
			ATSwordman_Als_Ani(obj,"character/swordman/effect/animation/3rd/atfusionblade/atfusionbladepiercingfront_00.ani",0, 0, 0, 0, 100, 0, 1.0);
		}
	}
	else if(substate == 1)
	{
		if (flagIndex == 0)
		{
		obj.sq_StartWrite();
		obj.sq_WriteDword(53);
		obj.sq_SendCreatePassiveObjectPacket(24238, 0, 200, 0, 0);
		}
	}
	return true;
}

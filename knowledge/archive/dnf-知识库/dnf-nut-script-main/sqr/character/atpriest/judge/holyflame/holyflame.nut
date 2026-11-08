function checkExecutableSkill_holyflame(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_HOLYFLAME);
	
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_HOLYFLAME , STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_holyflame(obj)
{
	if (!obj) return false;
	return true;
}

function onSetState_HolyFlame(obj, state, datas, isResetTimer)
{
	if(!obj)
		return false;
		obj.sq_StopMove();
		
		obj.sq_SetCurrentAnimation(ANI_HolyFlame_Body);
		obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/holyflame_body.ani"), 0, 0);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		obj.sq_SetCurrentAttackInfo(ATK_HolyFlame_Normal);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_HOLYFLAME , -1, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
		//obj.sq_PlaySound("R_PW_HOLY_FLAME");
		
		//local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_HOLYFLAME, false, "character/atpriest/judge/holyflame/ap_holyflame.nut", false);
		//CNSquirrelAppendage.sq_Append(appendage, obj, obj);
		local loadSlot = obj.sq_GetSkillLoad(SKILL_HOLYFLAME);
		if(!loadSlot)
		{
			obj.sq_AddSkillLoad(SKILL_HOLYFLAME, 110, getMaxHolyFlame(obj) , 0);
			loadSlot = obj.sq_GetSkillLoad(SKILL_HOLYFLAME);
		}
		else
		{
			local remain_number = loadSlot.getRemainLoadNumber();
			local add_number = getMaxHolyFlame(obj) - remain_number;
			loadSlot.increaseLoadCount(add_number);
		}
}

function onKeyFrameFlag_HolyFlame(obj,flagIndex)
{
	if(!obj)
		return false;

	if (flagIndex == 1)
	{

	}
	if (flagIndex == 2)
	{
	}
	if (flagIndex == 4)
	{
		obj.sq_SetShake(obj,2,300);
		obj.sq_PlaySound("CINTAMANI_HIT_01");
		sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atholyflame/atjudgmentblow/atjudgmentblow_att1_02.ani", -130, 0, 0);
		sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atholyflame/atjudgmentblow/atjudgmentblow_att1_12.ani", -310, 200, 0);
	}
	return true;
}

function onProc_HolyFlame(obj)
{
	if(!obj) return;
	if(isHolyFlame(obj)){
		ATPriestDetonateEssence(obj, obj, 0);
	}
}

function onEndCurrentAni_HolyFlame(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

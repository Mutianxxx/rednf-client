
function checkExecutableSkill_virtuousfury(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_VIRTUOUSFURY);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_VIRTUOUSFURY, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}


function checkCommandEnable_virtuousfury(obj)
{
	if (!obj)
		return false;
	return true;
}


function onSetState_VirtuousFury(obj, state, datas, isResetTimer)
{
	if(!obj)
		return false;
	
	local substate = obj.getVar().get_vector(0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	if(isHolyFlame(obj))
	{
		obj.sq_SetCurrentAnimation(ANI_VirtuousFury_HolyFlame_Body);
	}
	else
	{
		obj.sq_SetCurrentAnimation(ANI_VirtuousFury_Normal_Body);
	}
	
	obj.sq_SetCurrentAttackInfo(ATK_VirtuousFury_Normal);
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_VIRTUOUSFURY , -1, 0, 1.0);
	obj.sq_SetCurrentAttackBonusRate(damage);
	if(isHolyFlame(obj))
	{
		obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/virtuousfury_holyflame_body.ani"), 0, 0);
		local attackinfo = sq_GetCurrentAttackInfo(obj);
		if(attackinfo){
			attackinfo.setElement(ENUM_ELEMENT_LIGHT); 
			attackinfo.setElement(ENUM_ELEMENT_FIRE); 
		}
		if(obj.isMyControlObject())
		{
			local flashScreenObj = sq_flashScreen(obj, 80, 2600, 240, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	
}

function onProc_VirtuousFury(obj)
{
	if(!obj) return;
	if(isHolyFlame(obj)){
		ATPriestDetonateEssence(obj, obj, 0);
	}
}

function onProcCon_VirtuousFury(obj)
{
	if(!obj)
		return false;
	if(sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL))
	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}


function onKeyFrameFlag_VirtuousFury(obj,flagIndex)
{
	if(!obj)
		return false;

	if (flagIndex == 1)
	{
	}
	else if (flagIndex == 2)
	{
		obj.sq_SetShake(obj,3,300);
	}
	else if(flagIndex==10)
	{
		obj.resetHitObjectList();
		obj.sq_SetCurrentAttackInfo(ATK_VirtuousFury_Last_Normal);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_VIRTUOUSFURY , -1, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
		if(isHolyFlame(obj))
		{
			local attackinfo = sq_GetCurrentAttackInfo(obj);
			if(attackinfo){
				attackinfo.setElement(ENUM_ELEMENT_LIGHT); 
				attackinfo.setElement(ENUM_ELEMENT_FIRE); 
			}
		}
	}
	else if(flagIndex>10)
	{
		obj.resetHitObjectList();
	}
	return true;
}


function onEndCurrentAni_VirtuousFury(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onAttack_VirtuousFury(obj, damager, boundingBox, isStuck)
{
	if(!obj || isStuck)
		return;
	damager = sq_GetCNRDObjectToActiveObject(damager);
	if(damager.isObjectType(OBJECTTYPE_ACTIVE) && !isSameObject(obj, damager) && isHolyFlame(obj))
	{
		local append = "character/atpriest/judge/virtuousfury/ap_virtuousfuryholyflame.nut";
		if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, append))
		{
			return;
		}
		if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/judge/essenceofphlege/ap_essenceofphlegeex.nut"))
		{
			return;
		}
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, append, true);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, damager, obj, APID_RESONANCE, false);
	}
}

function onEndState_VirtuousFury(obj, newState)
{
	if(!obj) return;
	if(newState == STATE_VIRTUOUSFURY) return;
	if(isHolyFlame(obj))
	{
		useHolyFlame(obj,1);
	}
}

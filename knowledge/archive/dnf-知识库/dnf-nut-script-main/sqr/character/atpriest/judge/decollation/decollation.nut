
function checkExecutableSkill_decollation(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_DECOLLATION);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_DECOLLATION, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}


function checkCommandEnable_decollation(obj)
{
	if (!obj)
		return false;

	return true;
}

function onSetState_DecollAtion(obj, state, datas, isResetTimer)
{
	if(!obj)
		return false;
	
	local substate = obj.getVar().get_vector(0);
	
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	if(isHolyFlame(obj))
	{
		obj.sq_SetCurrentAnimation(ANI_DecollAtionFireBody_Body);
	}
	else
	{
		obj.sq_SetCurrentAnimation(ANI_DecollAtionNormal_Body);
	}

	obj.sq_SetCurrentAttackInfo(ATK_DecollAtion_Push);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(obj.isMyControlObject())
	{
		local flashScreenObj = sq_flashScreen(obj, 80, 1600, 240, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
}

function onProc_DecollAtion(obj)
{
	if(!obj) return;
	if(isHolyFlame(obj)){
		ATPriestDetonateEssence(obj, obj, 0);
	}
}



function onKeyFrameFlag_DecollAtion(obj,flagIndex)
{
	if(!obj)
		return false;

	if (flagIndex == 1)
	{
	
	}
	else if (flagIndex == 2)
	{
		obj.sq_SetShake(obj,1,200);
		if(obj.isMyControlObject())
		{
			local flashScreenObj = sq_flashScreen(obj, 80, 300, 240, 200, sq_RGB(200, 28, 28), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	else if (flagIndex == 3)
	{
		obj.sq_SetShake(obj,3,300);
	}
	else if (flagIndex == 4)
	{
		if(isHolyFlame(obj))
		{
			sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atdecollation/decollationfireeff2_fire_01.ani", 0, 0, 0);
		}
		obj.resetHitObjectList();
		obj.sq_SetCurrentAttackInfo(ATK_DecollAtion);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DECOLLATION , -1, 0, 1.0);
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
	else if (flagIndex == 11)
	{
		obj.resetHitObjectList();
		obj.sq_SetCurrentAttackInfo(ATK_DecollAtion);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DECOLLATION , -1, 0, 1.0);
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
	return true;
}


function onEndCurrentAni_DecollAtion(obj)
{
	if(!obj) return;
	obj.sq_IntVectClear();
	obj.getVar().clear_vector();
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onAttack_DecollAtion(obj, damager, boundingBox, isStuck)
{
	if(!obj || isStuck)
		return;
	damager = sq_GetCNRDObjectToActiveObject(damager);
	if(damager.isObjectType(OBJECTTYPE_ACTIVE) )
	{
		obj.getVar("DecollAtion").push_obj_vector(damager);
		local append = "character/atpriest/judge/decollation/ap_decollation.nut";
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/judge/decollation/ap_decollation.nut"))
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, append, true);
			if(appendage)
			{
				sq_HoldAndDelayDie(damager, obj, true, false, true, 0, 0, ENUM_DIRECTION_NEUTRAL, appendage);
				appendage.getAppendageInfo().setValidTime(5000);
			}
		}
		if(!isSameObject(obj, damager) && isHolyFlame(obj))
		{
			local append = "character/atpriest/judge/decollation/ap_decollationholyflame.nut";
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
}

function onEndState_DecollAtion(obj, new_state) {
	if(!obj )
		return;
	if (new_state != STATE_DECOLLATION) {
		if(isHolyFlame(obj))
		{
			useHolyFlame(obj,1);
		}
		local sq_var = obj.getVar("DecollAtion");
		local objectsSize = sq_var.get_obj_vector_size();
		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/judge/decollation/ap_decollation.nut")) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atpriest/judge/decollation/ap_decollation.nut");
			}
		}
	}
}
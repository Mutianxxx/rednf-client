
function checkExecutableSkill_punishmentblow(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_PUNISHMENTBLOW);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_PUNISHMENTBLOW, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_punishmentblow(obj)
{
	if (!obj)
		return false;

	return true;
}

function onSetState_PunishmentBlow(obj, state, datas, isResetTimer)
{
	if(!obj)
		return false;
	
	local substate = obj.getVar().get_vector(0);
	
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	local z = obj.getZPos();
	
	if(substate == 0)
	{
		
		if(z>30){
			obj.getVar("jumpSkillFlag").setInt(0, 1);
			obj.sq_SetCurrentAnimation(ANI_PunishmentBlow_Body_B);
			local pAni = sq_GetCurrentAnimation(obj);
			if(isHolyFlame(obj))
			{
				obj.sq_AddStateLayerAnimation(10011, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/punishmentblow_body_b.ani"), 0, 0);
			}
			
			obj.sq_PlaySound("R_PW_PUNISHMENT_BLOW_01");
			
		}
		else
		{
			obj.getVar("jumpSkillFlag").setInt(0, 0);
			obj.sq_SetCurrentAnimation(ANI_PunishmentBlow_Body_A);
			
			local pAni = sq_GetCurrentAnimation(obj);
			if(isHolyFlame(obj))
			{
				obj.sq_AddStateLayerAnimation(10011, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/punishmentblow_body_a.ani"), 0, 0);
			}
			
			obj.sq_SetCurrentAttackInfo(ATK_PunishmentBlow_Push);
			obj.sq_PlaySound("R_PW_PUNISHMENT_BLOW_02");
			
		}
		
		if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT
			 || sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT)
		{
			obj.sq_SetStaticMoveInfo(0, 300, 300, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL); 
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		}
		else
		{
			obj.sq_SetStaticMoveInfo(0, 100, 100, false);
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, 1800, 1800, 1.0, 1.0);
		}
	}
	if(substate == 1)
	{
		if(isHolyFlame(obj))
		{
			obj.sq_SetCurrentAnimation(ANI_PunishmentBlow_Body_Attack);
			
			obj.sq_PlaySound("PUNISHMENT_BLOW_FLAME");
			obj.sq_SetCurrentAttackInfo(ATK_PunishmentBlow_Attack);
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_PUNISHMENTBLOW , -1, 0, 1.0);
			obj.sq_SetCurrentAttackBonusRate(damage);
			local attackInfo = sq_GetCurrentAttackInfo(obj);
			if(attackInfo)
			{
				attackInfo.setElement(ENUM_ELEMENT_LIGHT); 
				attackInfo.setElement(ENUM_ELEMENT_FIRE); 
			}
		}
		else
		{
			obj.sq_SetCurrentAnimation(ANI_PunishmentBlow_Body_Attack_B);
			obj.sq_PlaySound("PUNISHMENT_BLOW");
			obj.sq_SetCurrentAttackInfo(ATK_PunishmentBlow_Attack);
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_PUNISHMENTBLOW , -1, 0, 1.0);
			obj.sq_SetCurrentAttackBonusRate(damage);
			
		}
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
	
}

function onProc_PunishmentBlow(obj)
{
	if(!obj) return;
	if(isHolyFlame(obj)){
		ATPriestDetonateEssence(obj, obj, 0);
	}
}

function onProcCon_PunishmentBlow(obj)
{
	local substate = obj.getSkillSubState();
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local flag = obj.getVar("jumpSkillFlag").getInt(0);
	local z = obj.getZPos();
	if(substate == 0)
	{
		
		if(flag){
			local v = sq_GetAccel(z, z, currentT, 200, true);
			sq_setCurrentAxisPos(obj, 2, v);
		}
	}
	else if(substate == 1)
	{
		if(flag == 1 && z == 0){
			obj.getVar("jumpSkillFlag").setInt(0, 2);
			sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atpunishmentblow/floor.ani", 0, 0, 0);
			sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atpunishmentblow/dust.ani", 0, 0, 0);
			obj.sq_SetShake(obj,1,300);
		}
		else if(flag == 2)
		{
			obj.getVar("jumpSkillFlag").setInt(0, currentT+2);
		}
		else if(z == 0 && ( (currentT-flag) > 300) )
		{
			obj.getVar("jumpSkillFlag").setInt(0, 0);
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
}

function onKeyFrameFlag_PunishmentBlow(obj,flagIndex)
{
	if(!obj)
		return false;
	local flag = obj.getVar("jumpSkillFlag").getInt(0);
	if (flagIndex == 1)
	{
		//if(isHolyFlame(obj))
		//{
			//sq_AddDrawOnlyAniFromParent(obj,"character/priest/atanimation/holyflameweaponeffect/punishmentblow_body_a.ani", 0, 0, 0);
		//}
	}
	else if (flagIndex == 2)
	{
		//if(isHolyFlame(obj))
		//{
			//sq_AddDrawOnlyAniFromParent(obj,"character/priest/atanimation/holyflameweaponeffect/punishmentblow_body_attack.ani", 30, 45, 45);
		//}
		if(flag == 0){
			sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atpunishmentblow/floor.ani", 0, 0, 0);
			sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atpunishmentblow/dust.ani", 0, 0, 0);
			obj.sq_SetShake(obj,1,300);
		}
	}
	return true;
}


function onEndCurrentAni_PunishmentBlow(obj)
{
	local substate = obj.getSkillSubState();
	local flag = obj.getVar("jumpSkillFlag").getInt(0);
	if(substate == 0)
	{
		obj.getVar().clear_vector();
		obj.getVar().push_vector(1);
		obj.sq_AddSetStatePacket(STATE_PUNISHMENTBLOW ,STATE_PRIORITY_USER, true);
	}
	if(substate == 1)
	{
		if(flag){
			local z = obj.getZPos();
			if(z==0){
			
				obj.getVar("jumpSkillFlag").setInt(0, 0);
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			}
		}
		else
		{
			obj.getVar("jumpSkillFlag").setInt(0, 0);
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
		
	}
}

function onAttack_PunishmentBlow(obj, damager, boundingBox, isStuck)
{
	if(!obj || isStuck)
		return;
	damager = sq_GetCNRDObjectToActiveObject(damager);
	if(damager.isObjectType(OBJECTTYPE_ACTIVE) && !isSameObject(obj, damager) && isHolyFlame(obj))
	{
		local append = "character/atpriest/judge/punishmentblow/ap_punishmentblowholyflame.nut";
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

function onEndState_PunishmentBlow(obj, newState)
{
	if(!obj) return;
	if(newState == STATE_PUNISHMENTBLOW) return;
	
	if(isHolyFlame(obj))
	{
		useHolyFlame(obj,1);
	}
}
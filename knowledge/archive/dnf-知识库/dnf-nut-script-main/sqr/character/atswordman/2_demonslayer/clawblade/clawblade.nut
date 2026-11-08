

function checkExecutableSkill_Clawblade(CQO32P7EZkHGCgH8eW)
{
	if (!CQO32P7EZkHGCgH8eW) return false
local CQVSyxKMSdQGFOPy7 = CQO32P7EZkHGCgH8eW.sq_IsUseSkill(152)
if (CQVSyxKMSdQGFOPy7)
	{
		CQO32P7EZkHGCgH8eW.getVar("Clawblade").clear_obj_vector()
CQO32P7EZkHGCgH8eW.sq_IntVectClear()
CQO32P7EZkHGCgH8eW.sq_IntVectPush(0)
CQO32P7EZkHGCgH8eW.sq_AddSetStatePacket(152, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Clawblade(CQgO8ObvRgTg6wyR)
{
	if (!CQgO8ObvRgTg6wyR) return false
return true
}


function onSetState_Clawblade(obj, CQ3fO83drr334BCc, CQT1zvFV3ZoXNa6qeZZy, CQsJZotPbTfSZR6by)
{
	if(!obj) return
local CQ6sQJxxPaPoMO5eEIc = obj.sq_GetVectorData(CQT1zvFV3ZoXNa6qeZZy, 0)
obj.setSkillSubState(CQ6sQJxxPaPoMO5eEIc)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	

switch(CQ6sQJxxPaPoMO5eEIc)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_CLAWBLADE")
BodyCalldaimus(obj, "clawblade1")
obj.sq_SetCurrentAnimation(403)
obj.sq_SetCurrentAttackInfo(90)
local CQerL657kKlwXj4m = obj.sq_GetBonusRateWithPassive(152, -1, 0,getATSwordmanBonus(obj,1.0,152))
obj.sq_SetCurrentAttackBonusRate(CQerL657kKlwXj4m)
break
case 1:
		obj.sq_SetCurrentAnimation(404)
obj.sq_SetCurrentAttackInfo(90)
local CQerL657kKlwXj4m = obj.sq_GetBonusRateWithPassive(152, -1, 1, getATSwordmanBonus(obj,1.0,152))
obj.sq_SetCurrentAttackBonusRate(CQerL657kKlwXj4m)
break
case 2:
		obj.sq_SetCurrentAnimation(405)
obj.sq_SetCurrentAttackInfo(90)
local CQerL657kKlwXj4m = obj.sq_GetBonusRateWithPassive(152, -1, 0, getATSwordmanBonus(obj,1.0,152))
obj.sq_SetCurrentAttackBonusRate(CQerL657kKlwXj4m)
break
case 3:
		obj.sq_SetCurrentAnimation(406)
obj.sq_SetCurrentAttackInfo(91)
local CQerL657kKlwXj4m = obj.sq_GetBonusRateWithPassive(152, -1, 0, getATSwordmanBonus(obj,1.0,152))
obj.sq_SetCurrentAttackBonusRate(CQerL657kKlwXj4m)
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Clawblade(CQ9Kh3XLFgWXDs2rdLM)
{
	if(!CQ9Kh3XLFgWXDs2rdLM) return
local CQtIGlaExu7SLg1q = CQ9Kh3XLFgWXDs2rdLM.getSkillSubState()
switch(CQtIGlaExu7SLg1q)
	{
	case 0:
		CQ9Kh3XLFgWXDs2rdLM.sq_IntVectClear()
CQ9Kh3XLFgWXDs2rdLM.sq_IntVectPush(1)
CQ9Kh3XLFgWXDs2rdLM.sq_AddSetStatePacket(152, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQ9Kh3XLFgWXDs2rdLM.sq_IntVectClear()
CQ9Kh3XLFgWXDs2rdLM.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQ9Kh3XLFgWXDs2rdLM.sq_IntVectClear()
CQ9Kh3XLFgWXDs2rdLM.sq_IntVectPush(3)
CQ9Kh3XLFgWXDs2rdLM.sq_AddSetStatePacket(152, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 3:
		CQ9Kh3XLFgWXDs2rdLM.sq_IntVectClear()
CQ9Kh3XLFgWXDs2rdLM.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Clawblade(obj, damager, boundingBox, isStuck)
{
	if(!obj)	return false
local CQu5ywTghxX4Ef9a = obj.getSkillSubState()
Calldaimus_onAttack(obj,damager, boundingBox, isStuck)
switch(CQu5ywTghxX4Ef9a)
	{
		case 0:
			if(!obj.getVar("Clawblade").is_obj_vector(damager) && sq_GetSkillLevel(obj, 163) > 0)
			{
				obj.getVar("Clawblade").push_obj_vector(damager)
				local CQMXdP2MAIQXAI8i1 = sq_GetLevelData(obj,163, 5, sq_GetSkillLevel(obj, 163))/100.0
				obj.sq_StartWrite()
				obj.sq_WriteDword(152)
				obj.sq_WriteDword(1)
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(152, -1, 0, getATSwordmanBonus(obj,CQMXdP2MAIQXAI8i1,152)))
				obj.sq_WriteDword(sq_GetObjectId(damager))
				sq_SendCreatePassiveObjectPacketPos( obj, 24383, 0, damager.getXPos(), damager.getYPos(), damager.getZPos() + obj.getObjectHeight()/2)
			}
			if(sq_IsHoldable(obj,damager) && sq_IsGrabable(obj,damager) && !sq_IsFixture(damager))
			{
				local CQnAABDS6Z2Vah8O5TH = "character/atswordman/2_demonslayer/clawblade/ap_clawblade.nut"
				local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, CQnAABDS6Z2Vah8O5TH, true)
				if(masterAppendage)
				{
					sq_HoldAndDelayDie(damager, obj, true, false, false, 100, 100, ENUM_DIRECTION_NEUTRAL, masterAppendage)
					sq_MoveToAppendageForce(damager, obj, obj, 250, 0, 0, 300, true, masterAppendage,true)
					local CQhUXq7dVadaeq6ub5 = masterAppendage.getAppendageInfo()
					CQhUXq7dVadaeq6ub5.setValidTime(300)
				}
			}
		break
case 1:
		if(sq_IsHoldable(obj,damager) && sq_IsGrabable(obj,damager) && !sq_IsFixture(damager))
		{
			local CQnAABDS6Z2Vah8O5TH = "character/atswordman/2_demonslayer/clawblade/ap_clawblade.nut"
local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, -1, false, CQnAABDS6Z2Vah8O5TH, true)
if(masterAppendage)
			{
				sq_HoldAndDelayDie(damager, obj, true, true, false, 100, 100, ENUM_DIRECTION_NEUTRAL, masterAppendage)
sq_MoveToAppendageForce(damager, obj, obj, 250, 0, 120, 300, true, masterAppendage,true)
local CQhUXq7dVadaeq6ub5 = masterAppendage.getAppendageInfo()
CQhUXq7dVadaeq6ub5.setValidTime(300)
}
		}
		break
}

}

function onEnterFrame_Clawblade(CQsS5n8Xe1b6WP4sJs, CQ6iaEOI2gBBqj3FX6CE)
{
	if(!CQsS5n8Xe1b6WP4sJs) return
local CQemkLQwvurGvV2PN = CQsS5n8Xe1b6WP4sJs.getSkillSubState()
switch(CQemkLQwvurGvV2PN)
	{
	case 1:
		if(CQ6iaEOI2gBBqj3FX6CE == 3 || CQ6iaEOI2gBBqj3FX6CE == 5 || CQ6iaEOI2gBBqj3FX6CE == 7)
			CQsS5n8Xe1b6WP4sJs.resetHitObjectList()
break
case 2:

		break
}
}

function onEndState_Clawblade(CQXTJ8h6OB5aQQ2HhZb, CQx7mvNKjYpWbMRS)
{
	if(!CQXTJ8h6OB5aQQ2HhZb) return
local CQPB1iPEutgbzIfLvL = CQXTJ8h6OB5aQQ2HhZb.getSkillSubState()
switch(CQPB1iPEutgbzIfLvL)
	{
	case 3:

		break
case 4:

		break
}
	
}

function onProc_Clawblade(CQ9NUJwk7CSjnhfGmTyT)
{
	if(!CQ9NUJwk7CSjnhfGmTyT) return
local CQtG1642mzx7xAdCs = CQ9NUJwk7CSjnhfGmTyT.getSkillSubState()
}

function onKeyFrameFlag_Clawblade(CQBEixGGDILBjq9KA5J, CQvwfyyUzZqGfB9F)
{
	if (!CQBEixGGDILBjq9KA5J) return false
switch(CQvwfyyUzZqGfB9F)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Clawblade(CQDxSGxRET1KTw8XLL)
{
	if(!CQDxSGxRET1KTw8XLL) return
local CQRdYh6NMEyOR17J8l35 = CQDxSGxRET1KTw8XLL.getSkillSubState()
switch(CQRdYh6NMEyOR17J8l35)
	{
	case 0:

		break
}
}
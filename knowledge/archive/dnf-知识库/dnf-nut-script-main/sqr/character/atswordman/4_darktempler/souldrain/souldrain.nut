

function checkExecutableSkill_SoulDrain(CQoTaNIgIZC84fCDjDFD)
{
	if (!CQoTaNIgIZC84fCDjDFD) return false
local CQ275gqFhTwNNLCOz = CQoTaNIgIZC84fCDjDFD.sq_IsUseSkill(59)
if (CQ275gqFhTwNNLCOz)
	{
		CQoTaNIgIZC84fCDjDFD.sq_IntVectClear()
CQoTaNIgIZC84fCDjDFD.sq_IntVectPush(0)
CQoTaNIgIZC84fCDjDFD.sq_AddSetStatePacket(59, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	
	return false
}

function checkCommandEnable_SoulDrain(CQmVEqgutE3JZnXHvuk)
{
	if (!CQmVEqgutE3JZnXHvuk) return false
return true
}

function onSetState_SoulDrain(obj, CQkoHCOBUjftXpZIsb, CQaqUfQASoPUHdLGADqn, CQ5l1U3YlMlTAsKAH)
{	
	if(!obj) return
local CQw8uEF8pgJ8JbKK5uX = obj.sq_GetVectorData(CQaqUfQASoPUHdLGADqn, 0)
obj.setSkillSubState(CQw8uEF8pgJ8JbKK5uX)
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
switch(CQw8uEF8pgJ8JbKK5uX)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_SetCurrentAnimation(507)
obj.sq_StartWrite()
obj.sq_WriteDword(59)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetLevelData(59, 0, sq_GetSkillLevel(obj, 59)))
obj.sq_WriteDword(obj.sq_GetLevelData(59, 1, sq_GetSkillLevel(obj, 59)))
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(59, -1, 3, getATSwordmanBonus(obj,1.0,59)))
obj.sq_WriteDword(obj.sq_GetLevelData(59, 4, sq_GetSkillLevel(obj, 59)))
obj.sq_WriteDword(obj.sq_GetLevelData(59, 2, sq_GetSkillLevel(obj, 59)))
obj.sq_WriteDword(sq_GetIntData(obj, 59, 0))
obj.sq_SendCreatePassiveObjectPacket(24381, 0, 0, -1, 0)
break
case 1:
		
		
		break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_SoulDrain(CQoaz8s8ReYJf1ZVBxn)
{
	if(!CQoaz8s8ReYJf1ZVBxn) return
local CQdkoIFegQIzeJacs = CQoaz8s8ReYJf1ZVBxn.getSkillSubState()
switch(CQdkoIFegQIzeJacs)
	{
	case 0:
		CQoaz8s8ReYJf1ZVBxn.sq_IntVectClear()
CQoaz8s8ReYJf1ZVBxn.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}



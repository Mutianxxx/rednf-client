

function checkExecutableSkill_ShadowLancer(CQ7pR1sxVTEZonIRMuH)
{
	if (!CQ7pR1sxVTEZonIRMuH) return false
local CQrQDkm7lahAO7sz = CQ7pR1sxVTEZonIRMuH.sq_IsUseSkill(63)
if (CQrQDkm7lahAO7sz)
	{
		CQ7pR1sxVTEZonIRMuH.sq_IntVectClear()
CQ7pR1sxVTEZonIRMuH.sq_IntVectPush(0)
CQ7pR1sxVTEZonIRMuH.sq_AddSetStatePacket(63, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	
	return false
}

function checkCommandEnable_ShadowLancer(CQCzveROpKDippKj8b)
{
	if (!CQCzveROpKDippKj8b) return false
return true
}

function onSetState_ShadowLancer(obj, CQANWNr6eoZxEJHTm, CQNG8hTLJ1qfyvHb, CQbEOq2avg23wZGxuM)
{	
	if(!obj) return
local CQFa8IFkOuuZuiFkEnVs = obj.sq_GetVectorData(CQNG8hTLJ1qfyvHb, 0)
obj.setSkillSubState(CQFa8IFkOuuZuiFkEnVs)
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
switch(CQFa8IFkOuuZuiFkEnVs)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_SetCurrentAnimation(500)
obj.sq_PlaySound("SW_SHADOW_LANCER")
break
case 1:
		obj.sq_SetCurrentAnimation(501)
obj.sq_StartWrite()
obj.sq_WriteDword(63)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(63, -1, 0, getATSwordmanBonus(obj,1.0,63)))
obj.sq_WriteDword(sq_GetIntData(obj, 63, 4))
obj.sq_SendCreatePassiveObjectPacket(24381, 0, 0, 0, 60)
local CQgeICt3hB9Ae8FvZ = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150)
obj.getVar().clear_vector()
obj.getVar().push_vector(CQgeICt3hB9Ae8FvZ)
break
}

}

function onEndCurrentAni_ShadowLancer(CQoclfzHyYIoUEDzBbn)
{
	if(!CQoclfzHyYIoUEDzBbn) return
local CQ2fLULUXtTQrfSU = CQoclfzHyYIoUEDzBbn.getSkillSubState()
switch(CQ2fLULUXtTQrfSU)
	{
	case 0:
		CQoclfzHyYIoUEDzBbn.sq_IntVectClear()
CQoclfzHyYIoUEDzBbn.sq_IntVectPush(1)
CQoclfzHyYIoUEDzBbn.sq_AddSetStatePacket(63, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQoclfzHyYIoUEDzBbn.sq_IntVectClear()
CQoclfzHyYIoUEDzBbn.sq_IntVectPush(1)
CQoclfzHyYIoUEDzBbn.sq_IntVectPush(1)
CQoclfzHyYIoUEDzBbn.sq_IntVectPush(200)
CQoclfzHyYIoUEDzBbn.sq_AddSetStatePacket(6, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onProc_ShadowLancer(CQm1QEpgmCHemKSY7R)
{
	if(!CQm1QEpgmCHemKSY7R) return
local CQJK3ZbMDzbvYbAQYuuz = CQm1QEpgmCHemKSY7R.getSkillSubState()
switch(CQJK3ZbMDzbvYbAQYuuz)
	{
	case 0:
		
		break
case 1:
		local CQkIp99i8rVhqXAnU = CQm1QEpgmCHemKSY7R.getVar().get_vector(0)
local CQaW3vZvEZe5voPrwb3 = sq_GetAccel(CQm1QEpgmCHemKSY7R.getXPos(), CQkIp99i8rVhqXAnU, CQm1QEpgmCHemKSY7R.sq_GetStateTimer(), 300, false)
if(CQm1QEpgmCHemKSY7R.isMovablePos(CQaW3vZvEZe5voPrwb3,CQm1QEpgmCHemKSY7R.getYPos()))
			sq_setCurrentAxisPos(CQm1QEpgmCHemKSY7R, 0, CQaW3vZvEZe5voPrwb3)
break
}
}



function checkExecutableSkill_Illusionblade(CQSluzb1ieWlPqBVOeJc)
{
	if (!CQSluzb1ieWlPqBVOeJc) return false
local CQf8Mt9oVZ69HdB4B = CQSluzb1ieWlPqBVOeJc.sq_IsUseSkill(131)
if (CQf8Mt9oVZ69HdB4B)
	{
		CheckUseAddloadDrawsword(CQSluzb1ieWlPqBVOeJc,131,{[0] = true,[108] = true,[14] = true},0)
CQSluzb1ieWlPqBVOeJc.sq_IntVectClear()
CQSluzb1ieWlPqBVOeJc.sq_IntVectPush(0)
CQSluzb1ieWlPqBVOeJc.sq_AddSetStatePacket(131, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Illusionblade(CQuBuFZnl6EMAsVM2zz)
{
	if (!CQuBuFZnl6EMAsVM2zz) return false
if(CQuBuFZnl6EMAsVM2zz.getZPos() > 10)
		return false
return CheckForceDrawsword(CQuBuFZnl6EMAsVM2zz,131,{[0] = true,[108] = true,[14] = true})
}

function onSetState_Illusionblade(obj, CQbHATnD9JDOSXC2d7, CQFacrNyajcysUX9nre, CQgeCAPc1m5miVZ5)
{
	if(!obj) return
local CQocrMeVYGElIQZRtx = obj.sq_GetVectorData(CQFacrNyajcysUX9nre, 0)
obj.setSkillSubState(CQocrMeVYGElIQZRtx)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
local CQ2f6hkPLRg9of48oOsr = obj.sq_GetBonusRateWithPassive(131, -1, 0, getATSwordmanBonus(obj,1.0,131))
switch(CQocrMeVYGElIQZRtx)
	{
	case 0:
		obj.sq_StopMove()
BodyMagicSword(obj, "IllusionBlade")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(285)
else
			obj.sq_SetCurrentAnimation(82)
local CQm1eQ1rhuS1WI3jK = sq_GetLevelData(obj,13, 2, sq_GetSkillLevel(obj, 13))
local CQJJ6OS7yDx3qh3fCI9 = sq_GetLevelData(obj,13, 5, sq_GetSkillLevel(obj, 13))/100.0
obj.sq_StartWrite()
obj.sq_WriteDword(131)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.getWeaponSubType())
obj.sq_WriteDword(CQ2f6hkPLRg9of48oOsr)
obj.sq_WriteDword(sq_GetLevelData(obj,131, 1, sq_GetSkillLevel(obj, 131)))
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(131, -1, 2, getATSwordmanBonus(obj,1.0+CQJJ6OS7yDx3qh3fCI9,131)))
obj.sq_WriteDword(sq_GetIntData(obj,131, 1)+CQm1eQ1rhuS1WI3jK)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
break
case 1:
		BodyMagicSword(obj, "IllusionBlade2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(286)
else
			obj.sq_SetCurrentAnimation(83)
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}
function onEndCurrentAni_Illusionblade(CQkssVcZ6dZZtC2l)
{
	if(!CQkssVcZ6dZZtC2l) return
local CQarkR6smWqSQq2h5e = CQkssVcZ6dZZtC2l.getSkillSubState()
switch(CQarkR6smWqSQq2h5e)
	{
	case 0:
		CQkssVcZ6dZZtC2l.sq_IntVectClear()
CQkssVcZ6dZZtC2l.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQkssVcZ6dZZtC2l.sq_IntVectClear()
CQkssVcZ6dZZtC2l.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onProc_Illusionblade(CQ5YJmJTDA1onB1dxXc9)
{
	if(!CQ5YJmJTDA1onB1dxXc9) return
local CQwRmai4z8yQeaMTb = CQ5YJmJTDA1onB1dxXc9.getSkillSubState()
}

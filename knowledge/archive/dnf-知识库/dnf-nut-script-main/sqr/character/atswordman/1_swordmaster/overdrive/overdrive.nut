

function checkExecutableSkill_Overdrive(obj) {
	if (!obj) return false;
	local CQ6TwEkGmt1NCSnsHiG = obj.sq_IsUseSkill(146);
	if (CQ6TwEkGmt1NCSnsHiG) {
		CheckUseAddloadDrawsword(obj, 146, {
			[0] = true,
			[108] = true,
			[14] = true
		}, 0);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(146, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_Overdrive(CQEE3cri5j1vgKtfm)
{
	if (!CQEE3cri5j1vgKtfm) return false
return CheckForceDrawsword(CQEE3cri5j1vgKtfm,146,{[0] = true,[108] = true,[14] = true})
}


function onSetState_Overdrive(obj, CQQxgG3NS19Th5Oh, CQLdF3FSlbI89iIdpZ, CQlMblttpukN48IkLzy3)
{
	if(!obj) return
local CQIHNW89NNGJNHsRV = obj.sq_GetVectorData(CQLdF3FSlbI89iIdpZ, 0)
obj.setSkillSubState(CQIHNW89NNGJNHsRV)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
switch(CQIHNW89NNGJNHsRV)
	{
	case 0:
		obj.sq_StopMove()
BodyMagicSword(obj, "OverDrive_ON_Body")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(313)
else
			obj.sq_SetCurrentAnimation(81)
local CQ7stSLCeYbI5Yaz272  = sq_GetCastTime(obj, 146, sq_GetSkillLevel(obj, 146))
local CQrrB1pOJtVtMLaj = sq_GetCurrentAnimation(obj)
local CQCYtkbzYCeUXuEYdX = sq_GetFrameStartTime(CQrrB1pOJtVtMLaj, 4)
local CQcR9w96Ix4T17plnz2E = CQCYtkbzYCeUXuEYdX.tofloat() / CQ7stSLCeYbI5Yaz272.tofloat()
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, CQcR9w96Ix4T17plnz2E, CQcR9w96Ix4T17plnz2E)
sq_StartDrawCastGauge(obj, CQCYtkbzYCeUXuEYdX, true)
break
}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Overdrive(CQA2OPZL3Ip8VophQ)
{
	if(!CQA2OPZL3Ip8VophQ) return
local CQNKzNQQyZRMK9oc = CQA2OPZL3Ip8VophQ.getSkillSubState()
switch(CQNKzNQQyZRMK9oc)
	{
	case 0:
		CQA2OPZL3Ip8VophQ.sq_IntVectClear()
CQA2OPZL3Ip8VophQ.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onEnterFrame_Overdrive(obj, CQFWwqM3kazILvibK6Vd)
{
	if(!obj) return
local CQgv5sAED3KtFZSxC = obj.getSkillSubState()
switch(CQFWwqM3kazILvibK6Vd)
	{
	case 4:
		local CQogQCeU8jmUZiSmMZn = sq_GetLevelData(obj,146, 0, sq_GetSkillLevel(obj, 146))
local append = "character/atswordman/1_swordmaster/overdrive/ap_overdrive.nut"
local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, append, false)
appendage.sq_SetValidTime(CQogQCeU8jmUZiSmMZn)
appendage.setEnableIsBuff(true)
appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 146, sq_GetSkillLevel(obj, 146))
CNSquirrelAppendage.sq_Append(appendage, obj, obj, true)
appendage.setBuffIconImage(56);
break
}
}

function onEndState_Overdrive(CQJZjEuucb7fHYPUv7iV, CQkPHZcRJus2AKOWq)
{
	if(!CQJZjEuucb7fHYPUv7iV) return
local CQaun86NRBjLabIQrX4 = CQJZjEuucb7fHYPUv7iV.getSkillSubState()
switch(CQaun86NRBjLabIQrX4)
	{
	case 3:

		break
case 4:

		break
}
	
}


function onProcCon_Overdrive(CQ5UMvKAWYFAu6Iu)
{
	if(!CQ5UMvKAWYFAu6Iu) return
local CQwkuooY4PYisosrHZ = CQ5UMvKAWYFAu6Iu.getSkillSubState()
switch(CQwkuooY4PYisosrHZ)
	{
	case 0:

		break
}
}

function onProc_Overdrive(CQZ6M2R9nCXqi9amZljA)
{
	if(!CQZ6M2R9nCXqi9amZljA) return
local CQzCuTVXAzwxrJatB = CQZ6M2R9nCXqi9amZljA.getSkillSubState()
}

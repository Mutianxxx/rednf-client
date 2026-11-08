

function checkExecutableSkill_Timeslash(obj)
{
	if (!obj) return false
local CQa1N6185sWqYq95x = obj.sq_IsUseSkill(142)
if (CQa1N6185sWqYq95x)
	{
		CheckUseAddloadDrawsword(obj,142, {[0] = true,[108] = true,[14] = true},0)
obj.sq_IntVectClear()
obj.sq_IntVectPush(0)
obj.sq_AddSetStatePacket(142, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Timeslash(obj)
{
	if (!obj) return false
if(obj.getZPos() > 10)
		return false
return CheckForceDrawsword(obj,142, {[0] = true,[108] = true,[14] = true})
}


function onSetState_Timeslash(obj, state, CQzY9j25p2DLgP6fDwIQ, CQOgPwoJdncP8k57J)
{
	if(!obj) return;
	local CQ73xOvqeFXihV5hXld = obj.sq_GetVectorData(CQzY9j25p2DLgP6fDwIQ, 0)
	obj.setSkillSubState(CQ73xOvqeFXihV5hXld)
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 0.85,0.85);	
	switch(CQ73xOvqeFXihV5hXld)
	{
		case 0:
			obj.sq_StopMove()
			BodyMagicSword(obj, "TimeslashStart")
			if(MagicSword_IsAppebd(obj))
				obj.sq_SetCurrentAnimation(328)
			else
				obj.sq_SetCurrentAnimation(106)
			obj.sq_SetCurrentAttackInfo(0)
			local CQrLXB8j2MQq9Q4dfILJ = obj.sq_GetBonusRateWithPassive(142, -1, 0,getATSwordmanBonus(obj,1.0,142))
			obj.sq_SetCurrentAttackBonusRate(CQrLXB8j2MQq9Q4dfILJ)
			if(sq_GetSkillLevel(obj, 142) > 2)
				sq_SendMessage(obj, OBJECT_MESSAGE_INVINCIBLE, 1, 0)
		break
		case 1:
		BodyMagicSword(obj, "TimeslashCharge")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(324)
else
			obj.sq_SetCurrentAnimation(108)
obj.sq_SetCurrentAttackInfo(0)
local CQrLXB8j2MQq9Q4dfILJ = obj.sq_GetBonusRateWithPassive(142, -1, 0, getATSwordmanBonus(obj,1.0,142))
obj.sq_SetCurrentAttackBonusRate(CQrLXB8j2MQq9Q4dfILJ)
break
case 2:
		BodyMagicSword(obj, "TimeslashSlash")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(327)
else
			obj.sq_SetCurrentAnimation(109)
obj.sq_SetCurrentAttackInfo(0)
local CQrLXB8j2MQq9Q4dfILJ = obj.sq_GetBonusRateWithPassive(142, -1, 0, getATSwordmanBonus(obj,1.0,142))
obj.sq_SetCurrentAttackBonusRate(CQrLXB8j2MQq9Q4dfILJ)
if(sq_GetSkillLevel(obj, 142) < 2)
			break
local CQAywsbnh9d25h2x = "character/atswordman/1_swordmaster/timeslash/ap_devilslash.nut"
local CQdn5XBMycOLMAgkoz = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, CQAywsbnh9d25h2x, false)
local CQyjadODXOTCXqRvsIWE = sq_GetLevelData(obj,142, 3, sq_GetSkillLevel(obj, 142))
local CQF5knQym6HD1NfzS = sq_GetLevelData(obj,142, 6, sq_GetSkillLevel(obj, 142))
if (CQdn5XBMycOLMAgkoz != null)
		{
			CQdn5XBMycOLMAgkoz.sq_SetValidTime(CQyjadODXOTCXqRvsIWE)
CQdn5XBMycOLMAgkoz.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 142, sq_GetSkillLevel(obj, 142))
CQdn5XBMycOLMAgkoz.setEnableIsBuff(true)
CNSquirrelAppendage.sq_Append(CQdn5XBMycOLMAgkoz, obj, obj, true)
if(sq_GetSkillLevel(obj, 142) < 8)
				break
local CQgXHphdDwbpCefU = CQdn5XBMycOLMAgkoz.sq_getChangeStatus("Timeslash")
if(!CQgXHphdDwbpCefU)
			{
				CQgXHphdDwbpCefU = CQdn5XBMycOLMAgkoz.sq_AddChangeStatus("Timeslash",obj, obj, 0, 49, false, CQF5knQym6HD1NfzS )
}
			if(CQgXHphdDwbpCefU)
			{
				CQF5knQym6HD1NfzS = CQF5knQym6HD1NfzS * -0.01
CQgXHphdDwbpCefU.clearParameter()
CQgXHphdDwbpCefU.addParameter(49, false, CQF5knQym6HD1NfzS.tofloat())
}
		}
		break
case 3:
		BodyMagicSword(obj, "TimeslashExp")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(326)
else
			obj.sq_SetCurrentAnimation(110)
obj.sq_SetCurrentAttackInfo(0)
local CQrLXB8j2MQq9Q4dfILJ = obj.sq_GetBonusRateWithPassive(142, -1, 0, getATSwordmanBonus(obj,1.0,142))
obj.sq_SetCurrentAttackBonusRate(CQrLXB8j2MQq9Q4dfILJ)
if(obj.isMyControlObject())
		{
			obj.sq_SetShake(obj,8,250)
sq_setFullScreenEffect(obj,"character/swordman/effect/animation/attimeslash/finish_timeslash_crack.ani")
}
		break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Timeslash(obj)
{
	if(!obj) return
local CQmUUYxcMm5gKj9bg = obj.getSkillSubState()
switch(CQmUUYxcMm5gKj9bg)
	{
	case 0:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(1)
obj.sq_AddSetStatePacket(142, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(2)
obj.sq_AddSetStatePacket(142, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(3)
obj.sq_AddSetStatePacket(142, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 3:
		obj.sq_IntVectClear()
obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Timeslash(CQJk1i57rHp5DS8xTlZ, CQk7uHHZK2gCLQ7m, CQaVf5uegnSDFM7vi6, CQ5DSxcTODeEOr6waeXS)
{
	if(!CQJk1i57rHp5DS8xTlZ)	return false
local CQwoYt644f4eGh5UP = CQJk1i57rHp5DS8xTlZ.getSkillSubState()
MagicswordupOccur(CQJk1i57rHp5DS8xTlZ, CQk7uHHZK2gCLQ7m, CQaVf5uegnSDFM7vi6, CQ5DSxcTODeEOr6waeXS)
switch(CQwoYt644f4eGh5UP)
	{
	case 0:

		break
case 1:

		break
}

}

function onEnterFrame_Timeslash(obj, frameIndex)
{
	if(!obj) return
local CQO8CTR3T8A5uBhu77 = obj.getSkillSubState()
switch(CQO8CTR3T8A5uBhu77)
	{
	case 1:
		if(frameIndex == 4)
		{

		}
		break
case 2:
		if(frameIndex == 1 || frameIndex == 6 || frameIndex == 11)
		{
			obj.sq_StartWrite()
obj.sq_WriteDword(142)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(142, -1, 0, getATSwordmanBonus(obj,1.0,142)))
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
}
		else if(frameIndex == 19 || frameIndex == 21 || frameIndex == 24)
		{

		}
		break
case 3:
		if(frameIndex == 0 && obj.isMyControlObject())
		{
			local CQ8BrrVHFczCswhrRsty = obj.getVar()
local CQWN7AIo9OKDi1gpm = sq_flashScreen(obj,0,1060,103,255,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_NORMAL)
CQ8BrrVHFczCswhrRsty.setObject(0,CQWN7AIo9OKDi1gpm)
obj.sq_StartWrite()
obj.sq_WriteDword(142)
obj.sq_WriteDword(1)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(142, -1, 1, getATSwordmanBonus(obj,1.0,142)))
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
}
		break
}
}

function onEndState_Timeslash(CQVGsMqgw6mHrOgyew1, CQYETj2M1QMsojRs)
{
	if(!CQVGsMqgw6mHrOgyew1) return
if(CQYETj2M1QMsojRs != 142)
	{
		if(sq_GetSkillLevel(CQVGsMqgw6mHrOgyew1, 142) > 2)
			sq_SendMessage(CQVGsMqgw6mHrOgyew1, OBJECT_MESSAGE_INVINCIBLE, 0, 0)
local CQSwKQDDYstWWSfopl = CQVGsMqgw6mHrOgyew1.getVar().getObject(0)
if(CQSwKQDDYstWWSfopl)
		{
			local CQfxqOWvI47nqQfPLIgY = sq_GetCNRDObjectToFlashScreen(CQSwKQDDYstWWSfopl)
if(CQfxqOWvI47nqQfPLIgY)
				CQfxqOWvI47nqQfPLIgY.fadeOut()
}
	}

}


function onKeyFrameFlag_Timeslash(CQud3BldgmsktNdaB, CQG1mR3VtGj7Qe9i)
{
	if (!CQud3BldgmsktNdaB) return false
local CQhJ2mGWZ2FNb29O6Z = CQud3BldgmsktNdaB.getSkillSubState()
switch(CQG1mR3VtGj7Qe9i)
	{
	case 1:
		if(CQhJ2mGWZ2FNb29O6Z != 3)
		{
			CQud3BldgmsktNdaB.sq_SetShake(CQud3BldgmsktNdaB,4,150)
sq_flashScreen(CQud3BldgmsktNdaB,0,60,0,102,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_COVER)
}
		break
}
	return true
}


function onProcCon_Timeslash(CQpsosbxUnYHwP8Ecz8K)
{
	if(!CQpsosbxUnYHwP8Ecz8K) return
local CQ3rgX97SDXsnklAn = CQpsosbxUnYHwP8Ecz8K.getSkillSubState()
switch(CQ3rgX97SDXsnklAn)
	{
	case 0:

		break
}
}

function onProc_Timeslash(CQqYFdZIldwtxDlsQly)
{
	if(!CQqYFdZIldwtxDlsQly) return
local CQKRvbEwpv3nUwTF = CQqYFdZIldwtxDlsQly.getSkillSubState()
}

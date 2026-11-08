

function checkExecutableSkill_Laevateinn(CQsUjxBAdES1YnOzuO)
{
	if (!CQsUjxBAdES1YnOzuO) return false
local CQ6kHyOWw2xLT7IUHzKd = CQsUjxBAdES1YnOzuO.sq_IsUseSkill(141)
if (CQ6kHyOWw2xLT7IUHzKd)
	{
		CheckUseAddloadDrawsword(CQsUjxBAdES1YnOzuO,141, {[0] = true,[108] = true,[14] = true},0)
CQsUjxBAdES1YnOzuO.sq_IntVectClear()
CQsUjxBAdES1YnOzuO.sq_IntVectPush(0)
CQsUjxBAdES1YnOzuO.sq_AddSetStatePacket(141, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Laevateinn(CQe6UFlx1ULPRpIYZ)
{
	if (!CQe6UFlx1ULPRpIYZ) return false
if(CQe6UFlx1ULPRpIYZ.getZPos() > 10)
		return false
return CheckForceDrawsword(CQe6UFlx1ULPRpIYZ,141, {[0] = true,[108] = true,[14] = true})
}


function onSetState_Laevateinn(obj, CQxSilFILM1qgJan, CQPiMrtwhvyz8vJrlX, CQ9muSz6yS8dhZHqYzrB)
{
	if(!obj) return
local CQtTf15K69s29UGtU = obj.sq_GetVectorData(CQPiMrtwhvyz8vJrlX, 0)
obj.setSkillSubState(CQtTf15K69s29UGtU)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
switch(CQtTf15K69s29UGtU)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_LAEVATEINN")
BodyMagicSword(obj, "ATLaevateinn")
local CQB7SjEEmckL48Gww7N = obj.getVar()
local CQvVYwnkDOGPdEFU = sq_flashScreen(obj,150, 10500, 300, 250, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM)
CQB7SjEEmckL48Gww7N.setObject(0,CQvVYwnkDOGPdEFU)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(229)
else
			obj.sq_SetCurrentAnimation(144)
obj.sq_SetCurrentAttackInfo(0)
local CQDFCOd2z7vD5fDWGX = obj.sq_GetBonusRateWithPassive(141, -1, 0,getATSwordmanBonus(obj,1.0,141))
obj.sq_SetCurrentAttackBonusRate(CQDFCOd2z7vD5fDWGX)
local CQfprBXGEzCp1KDQLxdy = obj.getObjectManager()
obj.getVar("Laevateinn").clear_obj_vector()
		for(local CQuQ7gaUNsewCbSu = 0; CQuQ7gaUNsewCbSu < CQfprBXGEzCp1KDQLxdy.getCollisionObjectNumber(); CQuQ7gaUNsewCbSu+=1)
		{
			local CQMzrmURe44Y2XArRz = "character/atswordman/1_swordmaster/laevateinn/ap_laevateinn.nut"
local Monstobj = CQfprBXGEzCp1KDQLxdy.getCollisionObject(CQuQ7gaUNsewCbSu)
if(Monstobj && Monstobj.isObjectType(OBJECTTYPE_ACTIVE) && obj.isEnemy(Monstobj)&&Monstobj.isInDamagableState(obj))
			{
				local CQGdsCAuvEf4K9Pyc = CNSquirrelAppendage.sq_AppendAppendage(Monstobj, obj, -1, false, CQMzrmURe44Y2XArRz, true)
sq_HoldAndDelayDie(Monstobj, obj, true, false, false, 100, 100, ENUM_DIRECTION_NEUTRAL, CQGdsCAuvEf4K9Pyc)
local CQ3MTdeYO2PXBaPsneF = CQGdsCAuvEf4K9Pyc.getAppendageInfo()
CQ3MTdeYO2PXBaPsneF.setValidTime(5800)
obj.getVar("Laevateinn").push_obj_vector(Monstobj)
}
		}
		if(obj.isMyControlObject())
		{
			obj.sq_StartWrite()
obj.sq_WriteDword(141)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(141, -1, 0, getATSwordmanBonus(obj,1.0,141)))
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, -1, 0)
}
		break
}
//	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}


function onEndCurrentAni_Laevateinn(CQqHKnTB4UzDLvZoEX)
{
	if(!CQqHKnTB4UzDLvZoEX) return
local CQKaqp2AuFKpFZLPOzko = CQqHKnTB4UzDLvZoEX.getSkillSubState()
switch(CQKaqp2AuFKpFZLPOzko)
	{
	case 0:
		CQqHKnTB4UzDLvZoEX.sq_IntVectClear()
CQqHKnTB4UzDLvZoEX.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Laevateinn(CQTe2LDWCMUwZULaD, CQscm8Y8TvNYGCKDJ7O, CQ6f2Y7XFStgPpJO, CQe1oiKI9974HdJHf6)
{
	if(!CQTe2LDWCMUwZULaD)	return false
local CQXJgJolacaCAsHSjeXU = CQTe2LDWCMUwZULaD.getSkillSubState()
MagicswordupOccur(CQTe2LDWCMUwZULaD, CQscm8Y8TvNYGCKDJ7O, CQ6f2Y7XFStgPpJO, CQe1oiKI9974HdJHf6)
switch(CQXJgJolacaCAsHSjeXU)
	{
	case 0:

		break
case 1:

		break
}

}

function onEndState_Laevateinn(obj, CQPWvx8Kc7DpSXGGtzv)
{
	if(!obj) return
local CQ9vByOqKwYssmFP = obj.getSkillSubState()
if(CQPWvx8Kc7DpSXGGtzv != 141)
	{
		local CQtgtFQjgsXWi9DJs7 = obj.getVar().getObject(0)
if(CQtgtFQjgsXWi9DJs7)
		{
			local CQB3B3hJt4QbraDDSet3 = sq_GetCNRDObjectToFlashScreen(CQtgtFQjgsXWi9DJs7)
if(CQB3B3hJt4QbraDDSet3)
				CQB3B3hJt4QbraDDSet3.fadeOut()
}
		local CQvLWTNo5q2kofSZ1 = "character/atswordman/1_swordmaster/laevateinn/ap_laevateinn.nut"
for(local CQDO8rPnUHi7WLCH5z1 = 0; CQDO8rPnUHi7WLCH5z1 < obj.getVar("Laevateinn").get_obj_vector_size(); ++CQDO8rPnUHi7WLCH5z1)
		{
			local CQRtOSw1S2dBqnCV = obj.getVar("Laevateinn").get_obj_vector(CQDO8rPnUHi7WLCH5z1)
if(CNSquirrelAppendage.sq_IsAppendAppendage(CQRtOSw1S2dBqnCV, CQvLWTNo5q2kofSZ1))
				CNSquirrelAppendage.sq_RemoveAppendage(CQRtOSw1S2dBqnCV, CQvLWTNo5q2kofSZ1)
		}
	}

}

function onEnterFrame_Laevateinn(CQiyzMjFlnOHtCXLg7, CQ1nLUGypFTsQpZMqI1J)
{
	if(!CQiyzMjFlnOHtCXLg7) return
local CQUjQayfdMJWbdZCW = CQiyzMjFlnOHtCXLg7.getSkillSubState()
switch(CQ1nLUGypFTsQpZMqI1J)
	{
	case 0:
		if(CQiyzMjFlnOHtCXLg7.isMyControlObject())
			sq_SetMyShake(CQiyzMjFlnOHtCXLg7,2,150)
break
case 1:

		break
case 5:
		if(CQiyzMjFlnOHtCXLg7.isMyControlObject())
			sq_SetMyShake(CQiyzMjFlnOHtCXLg7,2,1500)
break
case 10:
		sq_flashScreen(CQiyzMjFlnOHtCXLg7,0,80,0,127,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
break
case 18:
		if(CQiyzMjFlnOHtCXLg7.isMyControlObject())
			sq_SetMyShake(CQiyzMjFlnOHtCXLg7,10,100)
break
case 26:
		CQiyzMjFlnOHtCXLg7.sq_PlaySound("R_SW_LAEVATEINN_FIN")
if(CQiyzMjFlnOHtCXLg7.isMyControlObject())
			sq_SetMyShake(CQiyzMjFlnOHtCXLg7,10,350)
sq_flashScreen(CQiyzMjFlnOHtCXLg7,0,100,0,255,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
break
}
}


function onKeyFrameFlag_Laevateinn(CQH54ZxBevnnwsL3ieQ, CQ4XQ96PHABkngLNaZ)
{
	if (!CQH54ZxBevnnwsL3ieQ) return false
switch(CQ4XQ96PHABkngLNaZ)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Laevateinn(CQQA4bJcY9r7cZKXXzCc)
{
	if(!CQQA4bJcY9r7cZKXXzCc) return
local CQLipoi8Ic5NmUJ2N = CQQA4bJcY9r7cZKXXzCc.getSkillSubState()
switch(CQLipoi8Ic5NmUJ2N)
	{
	case 0:

		break
}
}

function onProc_Laevateinn(CQlmhKfZ3OEHYVJB37b)
{
	if(!CQlmhKfZ3OEHYVJB37b) return
local CQITG6Cey6gsTEH5 = CQlmhKfZ3OEHYVJB37b.getSkillSubState()
}

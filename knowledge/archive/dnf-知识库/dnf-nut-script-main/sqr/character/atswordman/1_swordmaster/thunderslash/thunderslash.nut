

function checkExecutableSkill_Thunderslash(CQ35pVhDL5m8ORK9i68)
{
	if (!CQ35pVhDL5m8ORK9i68) return false
local CQqXhRNtnTMNGZJ5 = CQ35pVhDL5m8ORK9i68.sq_IsUseSkill(132)
if (CQqXhRNtnTMNGZJ5)
	{
		CheckUseAddloadDrawsword(CQ35pVhDL5m8ORK9i68,132,{[0] = true,[108] = true,[14] = true},0)
CQ35pVhDL5m8ORK9i68.sq_IntVectClear()
CQ35pVhDL5m8ORK9i68.sq_IntVectPush(0)
CQ35pVhDL5m8ORK9i68.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Thunderslash(CQKAFUPcAEtJPUJRXZ)
{
	if (!CQKAFUPcAEtJPUJRXZ) return false
if(CQKAFUPcAEtJPUJRXZ.getZPos() > 10)
		return false
return CheckForceDrawsword(CQKAFUPcAEtJPUJRXZ,132,{[0] = true,[108] = true,[14] = true})
}


function onSetState_Thunderslash(obj, CQsUNX4PoUstAEGh3, CQ6ky9HeBojUsfGdz7S, CQe6Nbu7zMFTisFT)
{
	if(!obj) return
local CQXVtocZHbv8IbDgmX = obj.sq_GetVectorData(CQ6ky9HeBojUsfGdz7S, 0)
obj.setSkillSubState(CQXVtocZHbv8IbDgmX)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
local CQxD9K6wfSCdoXB9ezBy = sq_GetCurrentAnimation(obj)
switch(CQXVtocZHbv8IbDgmX)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_THUNDERSLASH")
BodyMagicSword(obj, "Thunderslash1")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(318)
else
			obj.sq_SetCurrentAnimation(84)
obj.sq_SetCurrentAttackInfo(59)
local CQPoP7aTIBw2WmVkA = obj.sq_GetBonusRateWithPassive(132, -1, 0,getATSwordmanBonus(obj,1.0,132))
obj.sq_SetCurrentAttackBonusRate(CQPoP7aTIBw2WmVkA)
obj.getVar("ThunderslashSub").setInt(0, 1)
obj.getVar("ThunderslashSub").clear_obj_vector()
local CQ9qxcU42c3Lq9CRGln = sq_GetIntData(obj,132, 0)
obj.getVar("ThunderslashSub").setInt(1, CQ9qxcU42c3Lq9CRGln)
sq_SendMessage(obj, 0, 1, 0)
break
case 1:
		BodyMagicSword(obj, "ThunderslashDash2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(320)
else
			obj.sq_SetCurrentAnimation(85)
obj.setTimeEvent(0,200,1,false)
break
case 2:
		BodyMagicSword(obj, "ThunderslashJump2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(322)
else
			obj.sq_SetCurrentAnimation(86)
obj.setTimeEvent(1,200,1,false)
break
case 3:
		obj.getVar("ThunderslashSub").setInt(1, obj.getVar("ThunderslashSub").getInt(1) - 1)
BodyMagicSword(obj, "ThunderslashGround3")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(321)
else
			obj.sq_SetCurrentAnimation(87)
obj.sq_SetCurrentAttackInfo(59)
local CQPoP7aTIBw2WmVkA = obj.sq_GetBonusRateWithPassive(132, -1, 1, getATSwordmanBonus(obj,1.0,132))
obj.sq_SetCurrentAttackBonusRate(CQPoP7aTIBw2WmVkA)
obj.setTimeEvent(3,150,4,true)
break
case 4:
		obj.getVar("ThunderslashSub").setInt(1, obj.getVar("ThunderslashSub").getInt(1) - 1)
obj.sq_ZStop()
BodyMagicSword(obj, "ThunderslashAir3")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(319)
else
			obj.sq_SetCurrentAnimation(88)
obj.sq_SetCurrentAttackInfo(59)
local CQPoP7aTIBw2WmVkA = obj.sq_GetBonusRateWithPassive(132, -1, 1, getATSwordmanBonus(obj,1.0,132))
obj.sq_SetCurrentAttackBonusRate(CQPoP7aTIBw2WmVkA)
obj.setTimeEvent(4,160,4,true)
break
case 5:
		BodyMagicSword(obj, "Thunderslash_Air_Finish_body")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(323)
else
			obj.sq_SetCurrentAnimation(89)
obj.sq_SetCurrentAttackInfo(0)
local CQPoP7aTIBw2WmVkA = obj.sq_GetBonusRateWithPassive(132, -1, 0, getATSwordmanBonus(obj,1.0,132))
obj.sq_SetCurrentAttackBonusRate(CQPoP7aTIBw2WmVkA)
break
}

}

function onEndCurrentAni_Thunderslash(CQiFwzmGuslzwnZlTZx)
{
	if(!CQiFwzmGuslzwnZlTZx) return
local CQ1G5t2i75JfnCLn = CQiFwzmGuslzwnZlTZx.getSkillSubState()
switch(CQ1G5t2i75JfnCLn)
	{
	case 0:
		local CQUEEDDbqTU2xqLcnI = CQiFwzmGuslzwnZlTZx.getVar("ThunderslashSub").get_obj_vector_size()
if(CQUEEDDbqTU2xqLcnI == 0)
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
}
		else
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(CQiFwzmGuslzwnZlTZx.getVar("ThunderslashSub").getInt(0))
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
}
		break
case 3:
		if(CQiFwzmGuslzwnZlTZx.getVar("ThunderslashSub").getInt(1) == 0)
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
}
		else
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(3)
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
}
		break
case 4:
		if(CQiFwzmGuslzwnZlTZx.getVar("ThunderslashSub").getInt(1) == 0)
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(5)
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
}
		else
		{
			CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(4)
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
}
		break
case 5:
		CQiFwzmGuslzwnZlTZx.sq_IntVectClear()
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(1)
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(0)
CQiFwzmGuslzwnZlTZx.sq_IntVectPush(0)
CQiFwzmGuslzwnZlTZx.sq_AddSetStatePacket(6, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Thunderslash(CQHwj2WMNENLUdKqE7cK, CQjxHklSx2WAcsJbP, CQEdUe3taU6ikgJeFXF, CQ4M1AFdRoEqYX1m)
{
	if(!CQHwj2WMNENLUdKqE7cK)	return false
local CQQJnNvCWMhxTmMW7Z = CQHwj2WMNENLUdKqE7cK.getSkillSubState()
MagicswordupOccur(CQHwj2WMNENLUdKqE7cK, CQjxHklSx2WAcsJbP, CQEdUe3taU6ikgJeFXF, CQ4M1AFdRoEqYX1m)
switch(CQQJnNvCWMhxTmMW7Z)
	{
	case 0:
		local CQKsMh8WKvDfRBMQflNw = CQHwj2WMNENLUdKqE7cK.getVar("ThunderslashSub").get_obj_vector_size()
if(CQKsMh8WKvDfRBMQflNw > 0)
			return
		else
			CQHwj2WMNENLUdKqE7cK.getVar("ThunderslashSub").push_obj_vector(CQjxHklSx2WAcsJbP)
if(sq_IsHoldable(CQHwj2WMNENLUdKqE7cK,CQjxHklSx2WAcsJbP) && sq_IsGrabable(CQHwj2WMNENLUdKqE7cK,CQjxHklSx2WAcsJbP) && !sq_IsFixture(CQjxHklSx2WAcsJbP) && CQjxHklSx2WAcsJbP.getState() != STATE_HOLD )
		{
			CQHwj2WMNENLUdKqE7cK.getVar("ThunderslashSub").setInt(0, 2)
local CQTruQLxbSc2lENn = "character/atswordman/1_swordmaster/thunderslash/ap_thunderslash.nut"
local CQsYfIp6PBZ5gfBrx6 = CNSquirrelAppendage.sq_AppendAppendage(CQjxHklSx2WAcsJbP, CQHwj2WMNENLUdKqE7cK, -1, false, CQTruQLxbSc2lENn, true)
if(CQsYfIp6PBZ5gfBrx6)
			{
				sq_HoldAndDelayDie(CQjxHklSx2WAcsJbP, CQHwj2WMNENLUdKqE7cK, true, false, false, 100, 100, ENUM_DIRECTION_NEUTRAL, CQsYfIp6PBZ5gfBrx6)
sq_MoveToAppendageForce(CQjxHklSx2WAcsJbP, CQHwj2WMNENLUdKqE7cK, CQHwj2WMNENLUdKqE7cK, 100, 0, 150, 150, true, CQsYfIp6PBZ5gfBrx6,true)
local CQ6RSVnI5cQC8IBqyef2 = CQsYfIp6PBZ5gfBrx6.getAppendageInfo()
CQ6RSVnI5cQC8IBqyef2.setValidTime(sq_GetIntData(CQHwj2WMNENLUdKqE7cK,132, 0)*600+500)
return
}
		}
		else
		{
			CQHwj2WMNENLUdKqE7cK.getVar("ThunderslashSub").setInt(0, 1)
local CQe2cfdwiO2D3nVyp = CQjxHklSx2WAcsJbP.getXPos() + 150
if(CQHwj2WMNENLUdKqE7cK.getDirection() == 1)
				CQe2cfdwiO2D3nVyp = CQjxHklSx2WAcsJbP.getXPos() - 150
CQHwj2WMNENLUdKqE7cK.getVar("Thunderslash").clear_vector()
CQHwj2WMNENLUdKqE7cK.getVar("Thunderslash").push_vector(CQe2cfdwiO2D3nVyp) 
}
		break
case 4:
		
		break
}

}

function onTimeEvent_Thunderslash(CQpy4EJQdJret2Far, CQfdvhBKfMLBLLS4URjR, CQPWCZjEGsOYNdXt17)
{
	if(!CQpy4EJQdJret2Far) return
local CQ9ve9Mmd4Th5sXa6eGE = CQpy4EJQdJret2Far.getSkillSubState()
switch(CQfdvhBKfMLBLLS4URjR)
	{
	case 0:
		CQpy4EJQdJret2Far.sq_IntVectClear()
CQpy4EJQdJret2Far.sq_IntVectPush(3)
CQpy4EJQdJret2Far.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQpy4EJQdJret2Far.sq_IntVectClear()
CQpy4EJQdJret2Far.sq_IntVectPush(4)
CQpy4EJQdJret2Far.sq_AddSetStatePacket(169, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 3:
		local CQtg6bA2sqH51RZid = CQpy4EJQdJret2Far.getVar("ThunderslashSub").get_obj_vector(0)
sq_SendHitObjectPacket(CQpy4EJQdJret2Far,CQtg6bA2sqH51RZid,0,0, CQtg6bA2sqH51RZid.getObjectHeight()/2)
break
case 4:
		local CQtg6bA2sqH51RZid = CQpy4EJQdJret2Far.getVar("ThunderslashSub").get_obj_vector(0)
sq_SendHitObjectPacket(CQpy4EJQdJret2Far,CQtg6bA2sqH51RZid,0,0, CQtg6bA2sqH51RZid.getObjectHeight()/2)
break
}
}

function onEnterFrame_Thunderslash(CQR4TK5iY2VD2U4E, CQiZK7JRLUrEVV3SWlPc)
{
	if(!CQR4TK5iY2VD2U4E || !CQR4TK5iY2VD2U4E.isMyControlObject()) return
local CQ1AmciNhF5eKQ2Ii = CQR4TK5iY2VD2U4E.getSkillSubState()
switch(CQ1AmciNhF5eKQ2Ii)
	{
	case 3:

		break
case 4:
		switch(CQiZK7JRLUrEVV3SWlPc)
		{
		case 11:
			if(CQR4TK5iY2VD2U4E.getVar("ThunderslashSub").getInt(1) != 0)
				return
local CQUu2uYuyMpYBf2ps6R = "character/atswordman/1_swordmaster/thunderslash/ap_thunderslash.nut"
local CQHUmG7Y6vRhLI1A = CQR4TK5iY2VD2U4E.getVar("ThunderslashSub").get_obj_vector(0)
if(!CQHUmG7Y6vRhLI1A)
				return
local CQjk24K9mSS5FhMsMZ = CNSquirrelAppendage.sq_AppendAppendage(CQHUmG7Y6vRhLI1A, CQR4TK5iY2VD2U4E, -1, false, CQUu2uYuyMpYBf2ps6R, true)
if(CQjk24K9mSS5FhMsMZ)
			{
				sq_HoldAndDelayDie(CQHUmG7Y6vRhLI1A, CQR4TK5iY2VD2U4E, true, true, false, 100, 100, ENUM_DIRECTION_NEUTRAL, CQjk24K9mSS5FhMsMZ)
sq_MoveToAppendageForce(CQHUmG7Y6vRhLI1A, CQR4TK5iY2VD2U4E, CQR4TK5iY2VD2U4E, 150, 0, -150, 100, true, CQjk24K9mSS5FhMsMZ,true)
local CQE6ozmABBxCOCMF4zvV = CQjk24K9mSS5FhMsMZ.getAppendageInfo()
CQE6ozmABBxCOCMF4zvV.setValidTime(100)
local CQ4CRWRWzcLNGmNO8 = sq_GetLevelData(CQR4TK5iY2VD2U4E,13, 1, sq_GetSkillLevel(CQR4TK5iY2VD2U4E, 13)) + 100
local CQQSDDVzEOmHPBBHv7H = sq_GetLevelData(CQR4TK5iY2VD2U4E,13, 4, sq_GetSkillLevel(CQR4TK5iY2VD2U4E, 13))/100.0
CQR4TK5iY2VD2U4E.sq_StartWrite()
CQR4TK5iY2VD2U4E.sq_WriteDword(132)
CQR4TK5iY2VD2U4E.sq_WriteDword(0)
CQR4TK5iY2VD2U4E.sq_WriteDword(CQR4TK5iY2VD2U4E.sq_GetBonusRateWithPassive(132, -1, 2, getATSwordmanBonus(CQR4TK5iY2VD2U4E,1.0 + CQQSDDVzEOmHPBBHv7H,132)))
CQR4TK5iY2VD2U4E.sq_WriteDword(CQ4CRWRWzcLNGmNO8)
sq_SendCreatePassiveObjectPacketPos( CQR4TK5iY2VD2U4E, 24383, 0, CQHUmG7Y6vRhLI1A.getXPos(), CQHUmG7Y6vRhLI1A.getYPos(), CQHUmG7Y6vRhLI1A.getZPos())
}
			break
}
		break
}
}

function onEndState_Thunderslash(CQLiv2IXf7MsEaBS, CQlmBkqIrzytARVLr6)
{
	if(!CQLiv2IXf7MsEaBS) return
if(CQlmBkqIrzytARVLr6 != 169)
		sq_SendMessage(CQLiv2IXf7MsEaBS, 0, 0, 0)
}


function onProcCon_Thunderslash(CQITtehQKs8naOCGue2A)
{
	if(!CQITtehQKs8naOCGue2A) return
local CQ77VPN5v4skuU7CH = CQITtehQKs8naOCGue2A.getSkillSubState()
switch(CQ77VPN5v4skuU7CH)
	{
	case 0:

		break
}
}

function onProc_Thunderslash(CQrVWNtKOqj8sV6KZzw)
{
	if(!CQrVWNtKOqj8sV6KZzw) return
local CQCD8hzpjEGNiQ5N = CQrVWNtKOqj8sV6KZzw.getSkillSubState()
local CQcoOq4ju2vHrN5X37 = sq_GetCurrentAnimation(CQrVWNtKOqj8sV6KZzw)
local CQAQlIG2CnCIos4J7ewv = 150
local CQdwLVyGqFwtWg4BY = CQrVWNtKOqj8sV6KZzw.sq_GetStateTimer()
switch(CQCD8hzpjEGNiQ5N)
	{
	case 1:
		local CQyxQfxnFM3nqP3ZUzV = CQrVWNtKOqj8sV6KZzw.getVar("Thunderslash").get_vector(0)
local CQNd4UZR9voTtm21 = sq_GetAccel(CQrVWNtKOqj8sV6KZzw.getXPos(), CQyxQfxnFM3nqP3ZUzV, CQdwLVyGqFwtWg4BY, CQAQlIG2CnCIos4J7ewv, false)
if(CQrVWNtKOqj8sV6KZzw.isMovablePos(CQNd4UZR9voTtm21, CQrVWNtKOqj8sV6KZzw.getYPos()))
			sq_setCurrentAxisPos(CQrVWNtKOqj8sV6KZzw, 0, CQNd4UZR9voTtm21)
break
case 2:
		local CQgMQaEFaAf8QB2Vtln3 = 160
local CQoH3ZUy19PNbw14G = sq_GetAccel(CQrVWNtKOqj8sV6KZzw.getZPos(), CQgMQaEFaAf8QB2Vtln3, CQdwLVyGqFwtWg4BY, CQAQlIG2CnCIos4J7ewv, false)
sq_setCurrentAxisPos(CQrVWNtKOqj8sV6KZzw, 2, CQoH3ZUy19PNbw14G)
sq_SimpleMoveToNearMovablePos(CQrVWNtKOqj8sV6KZzw,900)
break
case 4:
		if(CQrVWNtKOqj8sV6KZzw.getVar("ThunderslashSub").getInt(1) == 0)
		{
			
		}
		break
}
}

function onKeyFrameFlag_Thunderslash(CQ2ap9fYYcl2zRMML6K, CQmehvCBLOKLnOM7)
{
	if (!CQ2ap9fYYcl2zRMML6K) return false
switch(CQmehvCBLOKLnOM7)
	{
	case 0:

		break
}
	return true
}













function checkExecutableSkill_Devilslash(CQDIJWcEawSJPuWc)
{
	if (!CQDIJWcEawSJPuWc) return false
local CQRWmD6m1KxOJ6WTgC = CQDIJWcEawSJPuWc.sq_IsUseSkill(136)
if (CQRWmD6m1KxOJ6WTgC)
	{
		CheckUseAddloadDrawsword(CQDIJWcEawSJPuWc,136, {[0] = true,[108] = true,[14] = true},0)
CQDIJWcEawSJPuWc.sq_IsEnterSkillLastKeyUnits(136)
CQDIJWcEawSJPuWc.getVar("DevilslashT").setInt(0, 0)
CQDIJWcEawSJPuWc.getVar("DevilslashC").setInt(0, 0)
local CQiv21J2W4LySoIblxJH = 0
if(CQDIJWcEawSJPuWc.sq_GetState() != 0 && CQDIJWcEawSJPuWc.sq_GetState() != 14 && CQDIJWcEawSJPuWc.sq_GetState() != 108 && sq_GetSkillLevel(CQDIJWcEawSJPuWc, 11)>0 && CQDIJWcEawSJPuWc.getWeaponSubType() == 1)
		{
			CQDIJWcEawSJPuWc.getVar("DevilslashMax").setBool(0,true)
CQiv21J2W4LySoIblxJH = 2
}
		else
		{
			CQDIJWcEawSJPuWc.getVar("DevilslashMax").setBool(0,false)
}
		CQDIJWcEawSJPuWc.sq_IntVectClear()
CQDIJWcEawSJPuWc.sq_IntVectPush(CQiv21J2W4LySoIblxJH)
CQDIJWcEawSJPuWc.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Devilslash(CQ1gikUGLmmUsxIxW)
{
	if (!CQ1gikUGLmmUsxIxW) return false
if(CQ1gikUGLmmUsxIxW.getZPos() > 10)
		return false
return CheckForceDrawsword(CQ1gikUGLmmUsxIxW,136, {[0] = true,[108] = true,[14] = true})
}

function onSetState_Devilslash(obj, CQHLiPCRAgy9Ivav, CQjORNsN6n8Mo5azP7, CQEtDhmuUDsJOiEUNrxq)
{
	if(!obj) return
local CQ4uYqgYVfjZp8pY4 = obj.sq_GetVectorData(CQjORNsN6n8Mo5azP7, 0)
obj.setSkillSubState(CQ4uYqgYVfjZp8pY4)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
obj.getVar("DevilslashXXX").setInt(0, CQ4uYqgYVfjZp8pY4)
switch(CQ4uYqgYVfjZp8pY4)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_DEVILSLASH")
BodyMagicSword(obj, "DevilSlashCharge1")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(267)
else
			obj.sq_SetCurrentAnimation(99)
local CQQUVID9ltGAtEpQ8xS = [
		                    "effect/animation/atdevilslash/nothing/charge_body_1.ani",
		                    "effect/animation/atdevilslash/fire/charge_body_1.ani",
		                    "effect/animation/atdevilslash/ice/charge_body_1.ani",
		                    "effect/animation/atdevilslash/dark/charge_body_1.ani",
		                    "effect/animation/atdevilslash/light/charge_body_1.ani"
		                ]
obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation(CQQUVID9ltGAtEpQ8xS[GetMagicSwordAppIndex(obj)]), 0, 0)
break
case 1:
		obj.getVar("DevilslashT").setInt(0, 0)
obj.getVar("DevilslashT").setInt(1, sq_GetIntData(obj,136, 4))
obj.getVar("DevilslashT").setInt(2, sq_GetIntData(obj,136, 4))
obj.getVar("DevilslashT").setInt(3, sq_GetIntData(obj,136, 4))
BodyMagicSword(obj, "DevilSlashCharge2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(268)
else
			obj.sq_SetCurrentAnimation(100)
local CQQUVID9ltGAtEpQ8xS = [
		                    "effect/animation/atdevilslash/nothing/charge_body_2.ani",
		                    "effect/animation/atdevilslash/fire/charge_body_2.ani",
		                    "effect/animation/atdevilslash/ice/charge_body_2.ani",
		                    "effect/animation/atdevilslash/dark/charge_body_2.ani",
		                    "effect/animation/atdevilslash/light/charge_body_2.ani"
		                ]
obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation(CQQUVID9ltGAtEpQ8xS[GetMagicSwordAppIndex(obj)]), 0, 0)
break
case 2:
		HeavyswordmasteryAddAppend(obj)
BodyMagicSword(obj, "DevilSlashDash")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(270)
else
			obj.sq_SetCurrentAnimation(102)
obj.sq_SetStaticMoveInfo(0, 600, 450, false)
obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL)
local CQQUVID9ltGAtEpQ8xS = [
		                    "effect/animation/atdevilslash/nothing/dash_body.ani",
		                    "effect/animation/atdevilslash/fire/dash_body.ani",
		                    "effect/animation/atdevilslash/ice/dash_body.ani",
		                    "effect/animation/atdevilslash/dark/dash_body.ani",
		                    "effect/animation/atdevilslash/light/dash_body.ani"
		                ]
obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation(CQQUVID9ltGAtEpQ8xS[GetMagicSwordAppIndex(obj)]), 0, 0)
break
case 3:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_DEVILSLASH_FIN")
BodyMagicSword(obj, "DevilSlashMultiAttack")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(271)
else
			obj.sq_SetCurrentAnimation(103)
local CQsCWU3zerwxwbimerB = 1.0
local CQ6S7EFX2Z3fn6ut = sq_GetLevelData(obj,12, 13, sq_GetSkillLevel(obj, 12))/100.0
if(obj.getVar("WeaponcomboWeapon3").getBool(0))
		{
			if(sq_GetSkillLevel(obj, 12) > 0 && obj.getWeaponSubType() == 3)
			{
				
			}
			else
			{
				
			}
		}
		else
		{
			obj.sq_SetStaticMoveInfo(0, 450, 450, false)
}
		
		local CQeiIZtIv6o3eoywEx = [0,0,1,2]
local CQXml98QOQfZU9AiZP9o = 0.0
local CQxTLvL5jKPAcJPWB = obj.getVar("DevilslashT").getInt(0)
if(sq_GetSkillLevel(obj, 12)>0 && obj.getWeaponSubType() == 3)
			CQXml98QOQfZU9AiZP9o = sq_GetLevelData(obj,12, 2, sq_GetSkillLevel(obj, 12))/100.0
local CQP7qopKujlomvOQ2Oi = obj.sq_GetBonusRateWithPassive(136, -1, CQeiIZtIv6o3eoywEx[CQxTLvL5jKPAcJPWB], getATSwordmanBonus(obj,1.0+CQXml98QOQfZU9AiZP9o,136))
if(sq_GetSkillLevel(obj, 11)>0 && obj.getWeaponSubType() == 1)
			CQP7qopKujlomvOQ2Oi = obj.sq_GetBonusRateWithPassive(136, -1, CQeiIZtIv6o3eoywEx[CQxTLvL5jKPAcJPWB], getATSwordmanBonus(obj,1.0,136))
local CQ9V3KnpXmKQYLOu = 0
if(obj.getVar("WeaponcomboWeapon3").getBool(0))
			CQ9V3KnpXmKQYLOu = sq_GetLevelData(obj,12, 13, sq_GetSkillLevel(obj, 12))
obj.sq_StartWrite()
obj.sq_WriteDword(136)
obj.sq_WriteDword(1)
obj.sq_WriteDword(CQP7qopKujlomvOQ2Oi)
obj.sq_WriteDword(sq_GetIntData(obj,136, 10) + CQ9V3KnpXmKQYLOu)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
break
case 4:
		BodyMagicSword(obj, "DevilSlash3Degree")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(266)
else
			obj.sq_SetCurrentAnimation(105)
if(obj.isMyControlObject())
			sq_flashScreen(obj, 300, 550, 150, 180, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM)
local CQQUVID9ltGAtEpQ8xS = [
		                    "effect/animation/atdevilslash/nothing/napdo_body_mu.ani",
		                    "effect/animation/atdevilslash/fire/napdo_body_mu.ani",
		                    "effect/animation/atdevilslash/ice/napdo_body_mu.ani",
		                    "effect/animation/atdevilslash/dark/napdo_body_mu.ani",
		                    "effect/animation/atdevilslash/light/napdo_body_mu.ani"
		                ]
obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation(CQQUVID9ltGAtEpQ8xS[GetMagicSwordAppIndex(obj)]), 0, 0)
break
}

}

function onEndCurrentAni_Devilslash(CQbCGDJwBXPppD4Q)
{
	if(!CQbCGDJwBXPppD4Q) return
local CQoHWvDGMGWpclBZuetp = CQbCGDJwBXPppD4Q.getSkillSubState()
switch(CQoHWvDGMGWpclBZuetp)
	{
	case 0:
		CQbCGDJwBXPppD4Q.sq_IntVectClear()
CQbCGDJwBXPppD4Q.sq_IntVectPush(1)
CQbCGDJwBXPppD4Q.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQbCGDJwBXPppD4Q.sq_IntVectClear()
CQbCGDJwBXPppD4Q.sq_IntVectPush(3)
CQbCGDJwBXPppD4Q.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 4:
		CQbCGDJwBXPppD4Q.sq_IntVectClear()
CQbCGDJwBXPppD4Q.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onChangeSkillEffect_Devilslash(CQZD6S8gmKf2FjFrPnw, CQdsVerR7a7lwmMf9G6, CQO4efDMSYVsSWdaAXA)
{
	if(!CQZD6S8gmKf2FjFrPnw || CQdsVerR7a7lwmMf9G6 != 136) return
local CQ8Z6UWS6PePsj9i = CQO4efDMSYVsSWdaAXA.readDword()
local CQWPsElvoV4uiS8O4O = CQO4efDMSYVsSWdaAXA.readDword()
local CQVAkZ3dBxpmOT8E88VP = CQO4efDMSYVsSWdaAXA.readDword()
local CQYuJ9FCzIRzpNlSR = CQO4efDMSYVsSWdaAXA.readDword()/100.0
if(CQ8Z6UWS6PePsj9i != sq_GetObjectId(CQZD6S8gmKf2FjFrPnw))
		return
local CQSUmvyWH5AdteTIkCn = ["nothing","fire","ice","dark","light"]
local CQfk2o9xflz1E2TG = ["mu","fire","ice","dark","light"]
local CQu6oJZ7IaKKyPkAuP = "character/swordman/effect/animation/atdevilslash/" + CQSUmvyWH5AdteTIkCn[CQWPsElvoV4uiS8O4O] + "/slash_" + CQfk2o9xflz1E2TG[CQWPsElvoV4uiS8O4O] + "_" + CQVAkZ3dBxpmOT8E88VP.tostring() + ".ani"
if(CQWPsElvoV4uiS8O4O == 3)
	{
		local CQMC16EI33mPwkkKE8uW = "character/swordman/effect/animation/atdevilslash/" + CQSUmvyWH5AdteTIkCn[CQWPsElvoV4uiS8O4O] + "/slash_" + CQSUmvyWH5AdteTIkCn[CQWPsElvoV4uiS8O4O] + "_n_" + CQVAkZ3dBxpmOT8E88VP.tostring() + ".ani"
DarktemplerCreateAniPooledObj(CQZD6S8gmKf2FjFrPnw, CQMC16EI33mPwkkKE8uW, true, true, CQZD6S8gmKf2FjFrPnw.getXPos(), CQZD6S8gmKf2FjFrPnw.getYPos(), 0,1.0 + CQYuJ9FCzIRzpNlSR)
}
	else
		DarktemplerCreateAniPooledObj(CQZD6S8gmKf2FjFrPnw, CQu6oJZ7IaKKyPkAuP, true, true, CQZD6S8gmKf2FjFrPnw.getXPos(), CQZD6S8gmKf2FjFrPnw.getYPos(), 0,1.0 + CQYuJ9FCzIRzpNlSR)
}

function onEnterFrame_Devilslash(CQnSicnwbjMunDjFO, CQGiRydTXptmewhXB73)
{
	if(!CQnSicnwbjMunDjFO) return
local CQhmDGXKk17zU1hJ = CQnSicnwbjMunDjFO.getSkillSubState()
switch(CQhmDGXKk17zU1hJ)
	{
	case 0:

		break
case 3:
		if(CQGiRydTXptmewhXB73%2 == 0 && CQnSicnwbjMunDjFO.isMyControlObject())
		{
			local CQpTv4wEubsdcrgB7X = [0,0,1,2]
local CQ38Vljk7uj1mhRZfxjc = 0.0
if(sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12)>0 && CQnSicnwbjMunDjFO.getWeaponSubType() == 3 && CQnSicnwbjMunDjFO.getVar("DevilslashT").getInt(0) > 0)
				CQ38Vljk7uj1mhRZfxjc = sq_GetLevelData(CQnSicnwbjMunDjFO,12, 2, sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12))/100.0
CQnSicnwbjMunDjFO.sq_PlaySound("R_DSWD")
local CQqBWW12qNFLYAR1U = CQnSicnwbjMunDjFO.getVar("DevilslashC").getInt(0)
CQnSicnwbjMunDjFO.getVar("DevilslashC").setInt(0, CQqBWW12qNFLYAR1U + 1)
local CQsF8DSGFYYPTTfVw8I = CQnSicnwbjMunDjFO.getVar("DevilslashT").getInt(3)
if(CQqBWW12qNFLYAR1U -1 == CQsF8DSGFYYPTTfVw8I)
			{
				CQnSicnwbjMunDjFO.sq_IntVectClear()
CQnSicnwbjMunDjFO.sq_IntVectPush(4)
CQnSicnwbjMunDjFO.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
}
			local CQ6pW1rUxPXSvFcKtr = GetMagicSwordAppIndex(CQnSicnwbjMunDjFO)
local CQeQ8kTRaCwplecNoC9H = CQGiRydTXptmewhXB73/2
local CQXzIw2NRx3wg2xXL = 0
if(CQnSicnwbjMunDjFO.getVar("WeaponcomboWeapon3").getBool(0) && sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12)>0 && CQnSicnwbjMunDjFO.getWeaponSubType() == 3)
				CQXzIw2NRx3wg2xXL = sq_GetLevelData(CQnSicnwbjMunDjFO,12, 13, sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12))
sq_BinaryStartWrite()
sq_BinaryWriteDword(sq_GetObjectId(CQnSicnwbjMunDjFO))
sq_BinaryWriteDword(CQ6pW1rUxPXSvFcKtr)
sq_BinaryWriteDword(CQeQ8kTRaCwplecNoC9H)
sq_BinaryWriteDword(CQXzIw2NRx3wg2xXL)
sq_SendChangeSkillEffectPacket(CQnSicnwbjMunDjFO, 136)
}
		break
case 4:
		if(CQGiRydTXptmewhXB73 == 10)
		{
			local CQx9lPiuWIicztz2VPi = CQnSicnwbjMunDjFO.getVar("DevilslashT").getInt(0)
local CQpTv4wEubsdcrgB7X = [3,3,4,5]
local CQ38Vljk7uj1mhRZfxjc = 0.0
if(sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12)>0 && CQnSicnwbjMunDjFO.getWeaponSubType() == 3 && CQnSicnwbjMunDjFO.getVar("DevilslashT").getInt(0) > 0)
				CQ38Vljk7uj1mhRZfxjc = sq_GetLevelData(CQnSicnwbjMunDjFO,12, 2, sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12))/100.0
local CQXzIw2NRx3wg2xXL = 0
if(CQnSicnwbjMunDjFO.getVar("WeaponcomboWeapon3").getBool(0))
				CQXzIw2NRx3wg2xXL = sq_GetLevelData(CQnSicnwbjMunDjFO,12, 13, sq_GetSkillLevel(CQnSicnwbjMunDjFO, 12))
if(CQnSicnwbjMunDjFO.isMyControlObject())
			{
				CQnSicnwbjMunDjFO.sq_SetShake(CQnSicnwbjMunDjFO,4,300)
sq_flashScreen(CQnSicnwbjMunDjFO, 50, 100, 50, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM)
}
		
			local CQBapIoW63JDdMT8b = CQpTv4wEubsdcrgB7X[CQx9lPiuWIicztz2VPi]
if(CQnSicnwbjMunDjFO.getVar("DevilslashMax").getBool(0))
				CQBapIoW63JDdMT8b = CQpTv4wEubsdcrgB7X[3]
CQnSicnwbjMunDjFO.sq_StartWrite()
CQnSicnwbjMunDjFO.sq_WriteDword(136)
CQnSicnwbjMunDjFO.sq_WriteDword(0)
if(sq_GetSkillLevel(CQnSicnwbjMunDjFO, 11)>0 && CQnSicnwbjMunDjFO.getWeaponSubType() == 1)
				CQnSicnwbjMunDjFO.sq_WriteDword(CQnSicnwbjMunDjFO.sq_GetBonusRateWithPassive(136, -1, CQBapIoW63JDdMT8b, getATSwordmanBonus(CQnSicnwbjMunDjFO,1.0,136)))
else
				CQnSicnwbjMunDjFO.sq_WriteDword(CQnSicnwbjMunDjFO.sq_GetBonusRateWithPassive(136, -1, CQpTv4wEubsdcrgB7X[CQnSicnwbjMunDjFO.getVar("DevilslashT").getInt(0)], getATSwordmanBonus(CQnSicnwbjMunDjFO,1.0+CQ38Vljk7uj1mhRZfxjc,136)))
CQnSicnwbjMunDjFO.sq_PlaySound("DEVILSLASH_EXP")
CQnSicnwbjMunDjFO.sq_WriteDword(sq_GetIntData(CQnSicnwbjMunDjFO,136, 10) + CQXzIw2NRx3wg2xXL)
CQnSicnwbjMunDjFO.sq_WriteDword(GetMagicSwordAppIndex(CQnSicnwbjMunDjFO))
CQnSicnwbjMunDjFO.sq_SendCreatePassiveObjectPacket(24383, 0, 120, 0, 0)
}
		break
}
}

function onAttack_Devilslash(CQve3CbziUnp5rk4QXk, CQDcpfBXVpBwM3kf, CQRfhnOIl1WY6Aj7DP, CQi2FHQlGb6g1ThhJ8mk)
{
	if(!CQve3CbziUnp5rk4QXk)	return false
local CQ1Kb5h5dSE4CFhdX = CQve3CbziUnp5rk4QXk.getSkillSubState()
MagicswordupOccur(CQve3CbziUnp5rk4QXk, CQDcpfBXVpBwM3kf, CQRfhnOIl1WY6Aj7DP, CQi2FHQlGb6g1ThhJ8mk)
switch(CQ1Kb5h5dSE4CFhdX)
	{
	case 0:

		break
case 1:

		break
}

}

function onEndState_Devilslash(CQnINzNKsNgC3wb6NC, CQGWytPQ2YDDB1vgjcpo)
{
	if(!CQnINzNKsNgC3wb6NC) return
local CQhvdFzjvPcpLWv9z = CQnINzNKsNgC3wb6NC.getSkillSubState()
switch(CQhvdFzjvPcpLWv9z)
	{
	case 3:

		break
case 4:

		break
}

}


function onProcCon_Devilslash(CQpgt242ZCZaN4YkvxX)
{
	if(!CQpgt242ZCZaN4YkvxX) return
local CQ339TGpjxqWZScR = CQpgt242ZCZaN4YkvxX.getSkillSubState()
if(CQ339TGpjxqWZScR == 0 || CQ339TGpjxqWZScR == 1)
	{
		local CQqLPrunuI2bGlcls8 = CQpgt242ZCZaN4YkvxX.sq_GetStateTimer()
local CQsOxAcR75ujXGxhAr6U = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 0)
local CQ6tXM6FmT97HrzcHCH = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 1)
local CQebwhayBaIBA2zT = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 2)
local CQXn5QUYz3kGatlb9P = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 4)
local CQxjwOfBEUHsSkTxg81X = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 5)
local CQP55VCPfobWsDTmT = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 6)
local CQ9XERscr1Vbizmvc7Q = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 7)
local CQtSjmm8KbekI1mz = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 8)
local CQBiHa1XbS57oWUUaX = sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 9)
if(CQpgt242ZCZaN4YkvxX.isDownSkillLastKey())
		{
			if(CQsOxAcR75ujXGxhAr6U <= CQqLPrunuI2bGlcls8 && CQ6tXM6FmT97HrzcHCH > CQqLPrunuI2bGlcls8)
			{
				if(sq_GetSkillLevel(CQpgt242ZCZaN4YkvxX, 12) > 0 && CQpgt242ZCZaN4YkvxX.getWeaponSubType() == 3)
					CQpgt242ZCZaN4YkvxX.getVar("WeaponcomboWeapon3").setBool(0,true)
else
					CQpgt242ZCZaN4YkvxX.getVar("WeaponcomboWeapon3").setBool(0,false)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(0, 1)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(1, CQXn5QUYz3kGatlb9P)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(2, CQxjwOfBEUHsSkTxg81X)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(3, CQXn5QUYz3kGatlb9P)
}
			else if(CQ6tXM6FmT97HrzcHCH <= CQqLPrunuI2bGlcls8 && CQebwhayBaIBA2zT > CQqLPrunuI2bGlcls8)
			{
				CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(0, 2)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(1, CQP55VCPfobWsDTmT)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(2, CQ9XERscr1Vbizmvc7Q)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(3, CQP55VCPfobWsDTmT)
}
			else if(CQebwhayBaIBA2zT <= CQqLPrunuI2bGlcls8)
			{
				CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(0, 3)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(1, CQtSjmm8KbekI1mz)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(2, CQBiHa1XbS57oWUUaX)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(3, CQtSjmm8KbekI1mz)
if(CQpgt242ZCZaN4YkvxX.getWeaponSubType() == 3 && CQqLPrunuI2bGlcls8 + 300 > CQebwhayBaIBA2zT)
				{
					CQpgt242ZCZaN4YkvxX.sq_IntVectClear()
CQpgt242ZCZaN4YkvxX.sq_IntVectPush(2)
CQpgt242ZCZaN4YkvxX.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
}
				else
				{
					CQpgt242ZCZaN4YkvxX.sq_IntVectClear()
CQpgt242ZCZaN4YkvxX.sq_IntVectPush(2)
CQpgt242ZCZaN4YkvxX.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
}
			}
			else
			{
				CQpgt242ZCZaN4YkvxX.getVar("WeaponcomboWeapon3").setBool(0,false)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(0, 0)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(1, CQXn5QUYz3kGatlb9P)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(2, CQxjwOfBEUHsSkTxg81X)
CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(3, CQXn5QUYz3kGatlb9P)
}

		}
		else
		{
			CQpgt242ZCZaN4YkvxX.sq_IntVectClear()
CQpgt242ZCZaN4YkvxX.sq_IntVectPush(2)
CQpgt242ZCZaN4YkvxX.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
}

	}
	else if(CQ339TGpjxqWZScR == 2)
	{
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && CQpgt242ZCZaN4YkvxX.getDirection() == 1)
		{
			CQpgt242ZCZaN4YkvxX.sq_SetStaticMoveInfo(0, 0, 0, false)
}
		else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && CQpgt242ZCZaN4YkvxX.getDirection() == 0)
		{
			CQpgt242ZCZaN4YkvxX.sq_SetStaticMoveInfo(0, 0, 0, false)
}
	}
	else if(CQ339TGpjxqWZScR == 3)
	{
		if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
		{
			local CQvmUXDePBpBW4nYPxEO = [sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 5),sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 5),sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 7),sq_GetIntData(CQpgt242ZCZaN4YkvxX,136, 9)]
if(CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").getInt(3) < CQvmUXDePBpBW4nYPxEO[CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").getInt(0)])
				CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").setInt(3, CQpgt242ZCZaN4YkvxX.getVar("DevilslashT").getInt(3) + 1)
}

	}
}

function onProc_Devilslash(CQDT19Wl5YvHpSnQF)
{
	if(!CQDT19Wl5YvHpSnQF) return
}

function onTimeEvent_Devilslash(CQR7ubl5iPCstTbn387, CQiVMp3aC7wWQFvr, CQ1DuKFqqz4uyxvqRC)
{
	if (!CQR7ubl5iPCstTbn387) return false
switch(CQiVMp3aC7wWQFvr)
	{
	case 10:
		CQR7ubl5iPCstTbn387.resetHitObjectList()
break
case 1:
		CQR7ubl5iPCstTbn387.sq_IntVectClear()
CQR7ubl5iPCstTbn387.sq_IntVectPush(4)
CQR7ubl5iPCstTbn387.sq_AddSetStatePacket(136, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
	return true
}

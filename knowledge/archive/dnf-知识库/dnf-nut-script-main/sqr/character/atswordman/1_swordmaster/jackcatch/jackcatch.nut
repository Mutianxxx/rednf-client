

function checkExecutableSkill_Jackcatch(CQPfgi45cikpubcd6dRg)
{
	if (!CQPfgi45cikpubcd6dRg) return false
local CQB5CRMjve5qQZju = CQPfgi45cikpubcd6dRg.sq_IsUseSkill(139)
if (CQB5CRMjve5qQZju)
	{
		CheckUseAddloadDrawsword(CQPfgi45cikpubcd6dRg,139, {[0] = true,[108] = true,[14] = true},0)
CQPfgi45cikpubcd6dRg.getVar("JackcatchSub").setInt(0, 0)
CQPfgi45cikpubcd6dRg.sq_IntVectClear()
CQPfgi45cikpubcd6dRg.sq_IntVectPush(0)
CQPfgi45cikpubcd6dRg.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Jackcatch(CQj2wuxoptL3VH6g1ige)
{
	if (!CQj2wuxoptL3VH6g1ige) return false
if(CQj2wuxoptL3VH6g1ige.getZPos() > 10)
		return false
return CheckForceDrawsword(CQj2wuxoptL3VH6g1ige,139, {[0] = true,[108] = true,[14] = true})
}


function onSetState_Jackcatch(obj, CQ4z5ffnB3EsPxmY27wp, CQQ9wnARwUhtHJol7, CQLd4EeNGoDnAYinfXV)
{
	if(!obj) return
local CQlMEZkyd1cka4uc = obj.sq_GetVectorData(CQQ9wnARwUhtHJol7, 0)
obj.setSkillSubState(CQlMEZkyd1cka4uc)
	
obj.getVar("JackcatchSub").setInt(0, CQlMEZkyd1cka4uc)
local CQIHj81YsbZ8SuuqwO = obj.getVar("JackcatchTarget").get_obj_vector_size()
if(CQlMEZkyd1cka4uc != 0 && CQlMEZkyd1cka4uc != 5)
	{
		for(local CQ7aHvS92uQNs7ybt88j = 0; CQ7aHvS92uQNs7ybt88j < CQIHj81YsbZ8SuuqwO; CQ7aHvS92uQNs7ybt88j++)
		{
			local CQreUorPtB21iGteo = obj.getVar("JackcatchTarget").get_obj_vector(CQ7aHvS92uQNs7ybt88j)
if(CQreUorPtB21iGteo)
				sq_SendHitObjectPacket(obj,CQreUorPtB21iGteo,0,0, CQreUorPtB21iGteo.getObjectHeight()/2)
}
	}
	switch(CQlMEZkyd1cka4uc)
	{
	case 0:
		obj.sq_StopMove()
BodyMagicSword(obj, "JackCatchCast")
obj.getVar("JackcatchTar").setBool(0,false)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(293)
else
			obj.sq_SetCurrentAnimation(133)
obj.sq_SetCurrentAttackInfo(75)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 0,getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
if(obj.isMyControlObject())
			sq_flashScreen(obj, 150, 150, 300, 180, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM)
obj.sq_StartWrite()
obj.sq_WriteDword(139)
obj.sq_WriteDword(0)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 350, -30, 0)
obj.sq_StartWrite()
obj.sq_WriteDword(139)
obj.sq_WriteDword(1)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 350, -30, 0)
obj.sq_StartWrite()
obj.sq_WriteDword(139)
obj.sq_WriteDword(2)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 350, -30, 0)
obj.sq_StartWrite()
obj.sq_WriteDword(139)
obj.sq_WriteDword(3)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 300, -60, 0)
obj.sq_StartWrite()
obj.sq_WriteDword(139)
obj.sq_WriteDword(4)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 350, -30, 0)
break
case 1:
		obj.sq_ZStop()
BodyMagicSword(obj, "JackCatch_Light")
obj.sq_SetShake(obj,3,85)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(300)
else
			obj.sq_SetCurrentAnimation(128)
obj.sq_SetCurrentAttackInfo(75)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 0, getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
local CQA1MxoXSCIuWyrw1X = "character/swordman/effect/animation/atjackcatch/moveattack_light_move_light1.ani"
DarktemplerCreateAniPooledObj(obj, CQA1MxoXSCIuWyrw1X, true, true, obj.getXPos(), obj.getYPos(), obj.getZPos(),1.0)
local CQdJuyvs7zTqp6ri5zS3 = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 584)
obj.getVar("JackcatchPos").clear_vector()
obj.getVar("JackcatchPos").push_vector(CQdJuyvs7zTqp6ri5zS3)
obj.getVar("JackcatchPos").push_vector(obj.getYPos() - 40)
obj.getVar("JackcatchPos").push_vector(150)
break
case 2:
		BodyMagicSword(obj, "JackCatch_Fire")
obj.sq_SetShake(obj,3,85)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(298)
else
			obj.sq_SetCurrentAnimation(129)
obj.sq_SetCurrentAttackInfo(75)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 0, getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
local CQA1MxoXSCIuWyrw1X = "character/swordman/effect/animation/atjackcatch/moveattack_fire_move_fire1.ani"
DarktemplerCreateAniPooledObj(obj, CQA1MxoXSCIuWyrw1X, true, true, obj.getXPos(), obj.getYPos(), obj.getZPos(),1.0)
local CQdJuyvs7zTqp6ri5zS3 = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -451)
obj.getVar("JackcatchPos").clear_vector()
obj.getVar("JackcatchPos").push_vector(CQdJuyvs7zTqp6ri5zS3)
obj.getVar("JackcatchPos").push_vector(obj.getYPos() + 30)
obj.getVar("JackcatchPos").push_vector(obj.getZPos())
break
case 3:
		BodyMagicSword(obj, "JackCatch_Ice")
obj.sq_SetShake(obj,3,85)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(299)
else
			obj.sq_SetCurrentAnimation(130)
obj.sq_SetCurrentAttackInfo(75)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 0, getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
local CQA1MxoXSCIuWyrw1X = "character/swordman/effect/animation/atjackcatch/moveattack_ice_move_ice1.ani"
DarktemplerCreateAniPooledObj(obj, CQA1MxoXSCIuWyrw1X, true, true, obj.getXPos(), obj.getYPos(), obj.getZPos(),1.0)
local CQdJuyvs7zTqp6ri5zS3 = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 274)
obj.getVar("JackcatchPos").clear_vector()
obj.getVar("JackcatchPos").push_vector(CQdJuyvs7zTqp6ri5zS3)
obj.getVar("JackcatchPos").push_vector(obj.getYPos() + 40)
obj.getVar("JackcatchPos").push_vector(obj.getZPos())
break
case 4:
		BodyMagicSword(obj, "JackCatch_Dark")
obj.sq_SetShake(obj,3,85)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(295)
else
			obj.sq_SetCurrentAnimation(131)
obj.sq_SetCurrentAttackInfo(75)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 0, getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
local CQA1MxoXSCIuWyrw1X = "character/swordman/effect/animation/atjackcatch/moveattack_dark_move_dark1.ani"
DarktemplerCreateAniPooledObj(obj, CQA1MxoXSCIuWyrw1X, true, true, obj.getXPos(), obj.getYPos(), obj.getZPos(),1.0)
local CQdJuyvs7zTqp6ri5zS3 = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -120)
obj.getVar("JackcatchPos").clear_vector()
obj.getVar("JackcatchPos").push_vector(CQdJuyvs7zTqp6ri5zS3)
obj.getVar("JackcatchPos").push_vector(obj.getYPos() - 120)
obj.getVar("JackcatchPos").push_vector(obj.getZPos())
break
case 5:
		BodyMagicSword(obj, "JackCatch_Finish")
if(obj.isMyControlObject())
			sq_flashScreen(obj, 15, 25, 15, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER)
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(297)
else
			obj.sq_SetCurrentAnimation(132)
obj.sq_SetCurrentAttackInfo(76)
local CQCcMJ7rZYuLIctmL7u = obj.sq_GetBonusRateWithPassive(139, -1, 1, getATSwordmanBonus(obj,1.0,139))
obj.sq_SetCurrentAttackBonusRate(CQCcMJ7rZYuLIctmL7u)
local CQdJuyvs7zTqp6ri5zS3 = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 50)
obj.getVar("JackcatchPos").clear_vector()
obj.getVar("JackcatchPos").push_vector(CQdJuyvs7zTqp6ri5zS3)
obj.getVar("JackcatchPos").push_vector(obj.getYPos() +63)
obj.getVar("JackcatchPos").push_vector(obj.getZPos())
break
}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Jackcatch(obj)
{
	if(!obj) return
local CQzX2sHVQPyDzitGeO = obj.getSkillSubState()
switch(CQzX2sHVQPyDzitGeO)
	{
	case 0:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(1)
obj.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(2)
obj.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(3)
obj.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 3:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(4)
obj.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 4:
		obj.sq_IntVectClear()
obj.sq_IntVectPush(5)
obj.sq_AddSetStatePacket(139, STATE_PRIORITY_IGNORE_FORCE, true)
sq_SimpleMoveToNearMovablePos(obj,1100)
break
case 5:
		obj.sq_IntVectClear()
obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
sq_SimpleMoveToNearMovablePos(obj,1100)
break
}
}

function onAttack_Jackcatch(CQOAoCuPGC8ph8tAA7NB, CQ8u2fdcxzsw9HWKG, CQWminC7aIjY4YIFZXk, CQEFeIF6jMP5yNyLBH)
{
	if(!CQOAoCuPGC8ph8tAA7NB)	return false
local CQRypqXwjBXWZGcT = CQOAoCuPGC8ph8tAA7NB.getSkillSubState()
MagicswordupOccur(CQOAoCuPGC8ph8tAA7NB, CQ8u2fdcxzsw9HWKG, CQWminC7aIjY4YIFZXk, CQEFeIF6jMP5yNyLBH)
if(CQRypqXwjBXWZGcT == 4)
	{
		local CQAVv8RTLECCM6aDTzm = 200
local CQdDBvV4h3wD6oaL = "character/atswordman/1_swordmaster/jackcatch/ap_jackcatch.nut"
local CQyoWiraAU3p1xEGn7 = CNSquirrelAppendage.sq_AppendAppendage(CQ8u2fdcxzsw9HWKG, CQOAoCuPGC8ph8tAA7NB, -1, false, CQdDBvV4h3wD6oaL, true)
if(sq_IsHoldable(CQOAoCuPGC8ph8tAA7NB,CQ8u2fdcxzsw9HWKG) && !sq_IsFixture(CQ8u2fdcxzsw9HWKG))
			if(CQyoWiraAU3p1xEGn7)
			{
				sq_HoldAndDelayDie(CQ8u2fdcxzsw9HWKG, CQOAoCuPGC8ph8tAA7NB, true, false, false, 100, 100, ENUM_DIRECTION_NEUTRAL, CQyoWiraAU3p1xEGn7)
local CQNqVJTq6ooeCJpCaep9 = CQyoWiraAU3p1xEGn7.getAppendageInfo()
CQNqVJTq6ooeCJpCaep9.setValidTime(CQAVv8RTLECCM6aDTzm)
}
	}

}

function onEnterFrame_Jackcatch(CQblW62hmMfY2vpKP, CQF88xDHBbPgVZoNFx6)
{
	if(!CQblW62hmMfY2vpKP) return
local CQgBIyWozSl5KiiX = CQblW62hmMfY2vpKP.getSkillSubState()
switch(CQgBIyWozSl5KiiX)
	{
	case 5:

		if(CQF88xDHBbPgVZoNFx6 != 2)
			break
local CQmFlGzbGBKCB7i278 = CQblW62hmMfY2vpKP.sq_GetBonusRateWithPassive(139, -1, 1, getATSwordmanBonus(CQblW62hmMfY2vpKP,1.0,139))
CQblW62hmMfY2vpKP.sq_StartWrite()
CQblW62hmMfY2vpKP.sq_WriteDword(139)
CQblW62hmMfY2vpKP.sq_WriteDword(5)
CQblW62hmMfY2vpKP.sq_WriteDword(CQmFlGzbGBKCB7i278)
sq_SendCreatePassiveObjectPacketPos(CQblW62hmMfY2vpKP, 24383, 0, CQblW62hmMfY2vpKP.getXPos(), CQblW62hmMfY2vpKP.getYPos(), 0)
break
}
}

function onProc_Jackcatch(obj)
{
	if(!obj) return
local CQwf31ZVOsanP6P4pzRm = obj.getSkillSubState()
local CQZ1pjEtj5hkEoOMI = sq_GetCurrentAnimation(obj)
local CQzJhwhxuqD7A9I7S7E = sq_GetDelaySum(CQZ1pjEtj5hkEoOMI)/10
local CQOsGPN77EcNaJI3 = obj.sq_GetStateTimer()
local CQ8rbBPOq3XHiYsd6X = obj.getVar("JackcatchPos").get_vector(0)
local CQWYNgewFUQsILa6dxJj = obj.getVar("JackcatchPos").get_vector(1)
local CQVRymkTxo2Wouagh = obj.getVar("JackcatchPos").get_vector(2)
if(CQwf31ZVOsanP6P4pzRm != 0 && CQwf31ZVOsanP6P4pzRm != 5)
	{
		local CQY2Ns1LEMunW7E8Q8l = sq_GetAccel(obj.getXPos(), CQ8rbBPOq3XHiYsd6X, CQOsGPN77EcNaJI3, 20, false)
local CQSKyCuEMbdkpppj = sq_GetAccel(obj.getYPos(), CQWYNgewFUQsILa6dxJj, CQOsGPN77EcNaJI3, 20, false)
local CQfI9dcmrSO7tdpfo7 = sq_GetAccel(obj.getZPos(), CQVRymkTxo2Wouagh, CQOsGPN77EcNaJI3, 20, false)
//if(obj.isMovablePos(CQY2Ns1LEMunW7E8Q8l, CQSKyCuEMbdkpppj))
{
sq_setCurrentAxisPos(obj, 0, CQY2Ns1LEMunW7E8Q8l)
sq_setCurrentAxisPos(obj, 1, CQSKyCuEMbdkpppj)
sq_setCurrentAxisPos(obj, 2, CQfI9dcmrSO7tdpfo7)
}

}
	else if(CQwf31ZVOsanP6P4pzRm == 5)
	{
		if(CQOsGPN77EcNaJI3 < 50)
		{
			local CQY2Ns1LEMunW7E8Q8l = sq_GetAccel(obj.getXPos(), CQ8rbBPOq3XHiYsd6X, CQOsGPN77EcNaJI3, 12, false)
local CQSKyCuEMbdkpppj = sq_GetAccel(obj.getYPos(), CQWYNgewFUQsILa6dxJj, CQOsGPN77EcNaJI3, 12, false)
//if(obj.isMovablePos(CQY2Ns1LEMunW7E8Q8l, CQSKyCuEMbdkpppj))
{
sq_setCurrentAxisPos(obj, 0, CQY2Ns1LEMunW7E8Q8l)
sq_setCurrentAxisPos(obj, 1, CQSKyCuEMbdkpppj)
}
}
		else
		{
			local CQfI9dcmrSO7tdpfo7 = sq_GetAccel(obj.getZPos(), 0, CQOsGPN77EcNaJI3, 100, false)
sq_setCurrentAxisPos(obj, 2, CQfI9dcmrSO7tdpfo7)
}

	}
	
}

function onEndState_Jackcatch(CQJGL3LMdcUDLpuBf, CQkEQlpDePNHFcu5k71)
{
	if(!CQJGL3LMdcUDLpuBf) return
local CQaw4rbt27WsZKA1 = CQJGL3LMdcUDLpuBf.getSkillSubState()
if(CQkEQlpDePNHFcu5k71 == 139 && CQaw4rbt27WsZKA1 == 5)
		CQJGL3LMdcUDLpuBf.getVar("JackcatchTar").setBool(0,true)
else if(CQkEQlpDePNHFcu5k71 != 139)
{
		CQJGL3LMdcUDLpuBf.getVar("JackcatchTar").setBool(0,true)
	CQJGL3LMdcUDLpuBf.sq_setfindNearMovablePos(CQJGL3LMdcUDLpuBf.getXPos(),CQJGL3LMdcUDLpuBf.getYPos(),1800,1000,50)
}
}

function onKeyFrameFlag_Jackcatch(CQG3w8Yg57BPniST, CQh55vCMizrue8Ag87)
{
	if (!CQG3w8Yg57BPniST) return false
switch(CQh55vCMizrue8Ag87)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Jackcatch(CQqXwiIuVs5mUEAxb)
{
	if(!CQqXwiIuVs5mUEAxb) return
local CQKA5Jqvl5pzcYPkqXK = CQqXwiIuVs5mUEAxb.getSkillSubState()
switch(CQKA5Jqvl5pzcYPkqXK)
	{
	case 0:

		break
}
}

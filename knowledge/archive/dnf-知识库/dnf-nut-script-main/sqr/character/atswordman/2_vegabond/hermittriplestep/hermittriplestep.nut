

function checkExecutableSkill_Hermittriplestep(CQuypLTjNWVRY3nw8j)
{
	if (!CQuypLTjNWVRY3nw8j) return false
local CQGnh7JHwXe3TAniR = CQuypLTjNWVRY3nw8j.sq_IsUseSkill(225)
if (CQGnh7JHwXe3TAniR)
	{
  
		CQuypLTjNWVRY3nw8j.sq_IntVectClear()
CQuypLTjNWVRY3nw8j.sq_IntVectPush(0)
CQuypLTjNWVRY3nw8j.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Hermittriplestep(CQhjGYioHz4XRTbWm3v)
{
	if (!CQhjGYioHz4XRTbWm3v) return false
return true
}

function onSetState_Hermittriplestep(obj, CQ3XFH7MILRogevyyJ, CQqAb5KD3kAw91YepjyO, CQKuNxoyyEzcjWcoZ)
{
	if(!obj) return
local substate = obj.sq_GetVectorData(CQqAb5KD3kAw91YepjyO, 0)
obj.setSkillSubState(substate)
	
switch(substate)
	{
	case 0:
		obj.getVar("Hermittriplestep").clear_vector()
obj.getVar("Hermittriplestep").push_vector(obj.getXPos())
obj.getVar("Hermittriplestep").push_vector(obj.getXPos())
obj.getVar("Hermittriplestep").clear_obj_vector()
obj.sq_StopMove()
obj.sq_SetCurrentAnimation(612)
if(obj.isMyControlObject())
			sq_flashScreen(obj,60,420,0,102,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
local CQsmdFBVkhmh5Sxa = [
			"character/swordman/effect/animation/athermittriplestep/cast_ilusion.ani",
			"character/swordman/effect/animation/athermittriplestep/cast_dust.ani",
			"character/swordman/effect/animation/athermittriplestep/cast_effect.ani"
		]
foreach(path in CQsmdFBVkhmh5Sxa)
			ATswordmanCreateAniPooledObj(obj, path , false , true,obj.getXPos(), obj.getYPos(), 0,1.0)
break
case 1:
		obj.sq_SetCurrentAnimation(609)
if(obj.isMyControlObject())
			sq_flashScreen(obj,0,120,0,102,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
local CQsmdFBVkhmh5Sxa = [
			"character/swordman/effect/animation/athermittriplestep/attacka_back_leef02.ani",
			"character/swordman/effect/animation/athermittriplestep/attacka_front_leef03.ani",
			"character/swordman/effect/animation/athermittriplestep/attacka_back_ilusion.ani"
		]
foreach(path in CQsmdFBVkhmh5Sxa)
			ATswordmanCreateAniPooledObj(obj, path , false , true,obj.getXPos(), obj.getYPos(), 0,1.0)
local CQe8xTQc8MtV6GzOcm2c = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150)
obj.getVar("Hermittriplestep").set_vector(1,CQe8xTQc8MtV6GzOcm2c)
break
case 2:
		obj.sq_SetCurrentAnimation(610)
if(obj.isMyControlObject())
			sq_flashScreen(obj,0,120,0,102,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
local CQsmdFBVkhmh5Sxa = [
			"character/swordman/effect/animation/athermittriplestep/attackb_back_leef02.ani",
			"character/swordman/effect/animation/athermittriplestep/attackb_back_ilusion.ani",
			"character/swordman/effect/animation/athermittriplestep/attackb_front_leef03.ani"
		]
foreach(path in CQsmdFBVkhmh5Sxa)
			ATswordmanCreateAniPooledObj(obj, path , false , true,obj.getXPos(), obj.getYPos(), 0,1.0)
local CQe8xTQc8MtV6GzOcm2c = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150)
obj.getVar("Hermittriplestep").set_vector(1,CQe8xTQc8MtV6GzOcm2c)
break
case 3:
		obj.sq_SetCurrentAnimation(611)
if(obj.isMyControlObject())
			sq_flashScreen(obj,0,120,360,102,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
local CQsmdFBVkhmh5Sxa = [
			"character/swordman/effect/animation/athermittriplestep/attackc_back_leef02.ani",
			"character/swordman/effect/animation/athermittriplestep/attackc_back_ilusion.ani",
			"character/swordman/effect/animation/athermittriplestep/attackc_front_leef01.ani"
		]
foreach(path in CQsmdFBVkhmh5Sxa)
			ATswordmanCreateAniPooledObj(obj, path , false , true,obj.getXPos(), obj.getYPos(), 0,1.0)
local CQe8xTQc8MtV6GzOcm2c = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150)
obj.getVar("Hermittriplestep").set_vector(1,CQe8xTQc8MtV6GzOcm2c)
break
case 4:
		obj.sq_SetCurrentAnimation(613)
if(obj.isMyControlObject())
			sq_flashScreen(obj,720,120,0,255,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
break
case 5:
		obj.sq_SetCurrentAnimation(614)
if(obj.isMyControlObject())
			sq_flashScreen(obj,720,120,0,255,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
break
case 6:
		obj.sq_SetCurrentAnimation(615)
obj.sq_SetCurrentAttackInfo(177)
local CQtz5Q4LRWYjKDmAKms9 = obj.sq_GetBonusRateWithPassive(225, -1, 0, getATSwordmanBonus(obj,1.0,225))
obj.sq_SetCurrentAttackBonusRate(CQtz5Q4LRWYjKDmAKms9)

if(obj.isMyControlObject())
			sq_flashScreen(obj,0,0,600,153,sq_RGB(255,255,255),GRAPHICEFFECT_LINEARDODGE,ENUM_DRAWLAYER_BOTTOM)
local CQsmdFBVkhmh5Sxa = [
			"character/swordman/effect/animation/athermittriplestep/lastb_effect02.ani",
			"character/swordman/effect/animation/athermittriplestep/lasta_leef.ani"
		]
foreach(path in CQsmdFBVkhmh5Sxa)
			ATswordmanCreateAniPooledObj(obj, path , false , true,obj.getXPos(), obj.getYPos(), 0,1.0)
break
}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Hermittriplestep(CQvNkBym4lwVL1nFMj8)
{
	if(!CQvNkBym4lwVL1nFMj8) return
local CQDGHRc3ns3GFWnP = CQvNkBym4lwVL1nFMj8.getSkillSubState()
switch(CQDGHRc3ns3GFWnP)
	{
	case 0:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_IntVectPush(1)
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_IntVectPush(2)
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_IntVectPush(3)
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 3:
		local CQREjmXHALiaZ4bJxh = CQvNkBym4lwVL1nFMj8.getVar("Hermittriplestep").get_vector(0)
local CQUwHaaoTkdrGSvDbpxS = CQvNkBym4lwVL1nFMj8.getVar("Hermittriplestep").get_vector(1)
if(CQREjmXHALiaZ4bJxh == CQUwHaaoTkdrGSvDbpxS)
			CQvNkBym4lwVL1nFMj8.setDirection(sq_GetOppositeDirection(CQvNkBym4lwVL1nFMj8.getDirection()))
CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_IntVectPush(4)
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 4:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_IntVectPush(6)
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(225, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 5:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 6:
		CQvNkBym4lwVL1nFMj8.sq_IntVectClear()
CQvNkBym4lwVL1nFMj8.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onEnterFrame_Hermittriplestep(obj, CQjd1dfM9JljHFYG)
{
	if(!obj || !obj.isMyControlObject()) return
local substate = obj.getSkillSubState()
switch(substate)
	{
	case 0:

		break
case 6:
		if(CQjd1dfM9JljHFYG == 1)
		{
		
			sq_SetMyShake(obj,6,250)
local CQ4JfpsvGiu9a2cKHjjm = obj.getVar("Hermittriplestep").get_obj_vector_size()


for(local i=0; i<CQ4JfpsvGiu9a2cKHjjm; ++i)
			{
					
				local CQLIY71VsROJs5wXd3I = obj.getVar("Hermittriplestep").get_obj_vector(i)
if(CQLIY71VsROJs5wXd3I)
					sq_SendHitObjectPacketWithNoStuck(obj,CQLIY71VsROJs5wXd3I,0,0,CQLIY71VsROJs5wXd3I.getZPos() + CQLIY71VsROJs5wXd3I.getObjectHeight()/2)
}
		}
		break
}
}

function onChangeSkillEffect_Hermittriplestep(CQlWSYSW2yTOiDw2, CQIvciWxtVHyrzQBlJ, CQ7gCHlCZcnUoHqZYUL4)
{
	if(!CQlWSYSW2yTOiDw2 || CQIvciWxtVHyrzQBlJ != 225) return
local CQr3r53OUWBltrq1i = CQ7gCHlCZcnUoHqZYUL4.readDword()
if(CQr3r53OUWBltrq1i == 0)
	{

	}else if(CQr3r53OUWBltrq1i == 1)
	{
		local CQCL7zowSXr9Q3mVshc = CQlWSYSW2yTOiDw2.getVar("Hermittriplestep").get_vector(1)
CQlWSYSW2yTOiDw2.getVar("Hermittriplestep").set_vector(0,CQCL7zowSXr9Q3mVshc)
}
}

function onAttack_Hermittriplestep(CQcOstv67l5Myym4, CQAtTF8LpspJwTUMG2, CQdbK2LENLgOnFn74mWK, CQyhTTpkxkSyexn38)
{
	if(!CQcOstv67l5Myym4 || CQyhTTpkxkSyexn38)	return false
local CQN4Krb3HpxUU2bdRjM = CQcOstv67l5Myym4.getSkillSubState()
local CQbXmANGf2Llctv6 = "character/swordman/effect/animation/athermittriplestep/hit_effect02.ani"
DarktemplerCreateAniPooledObj(CQcOstv67l5Myym4, CQbXmANGf2Llctv6 , false , true, CQAtTF8LpspJwTUMG2.getXPos(), CQAtTF8LpspJwTUMG2.getYPos()+1, CQAtTF8LpspJwTUMG2.getZPos()+CQAtTF8LpspJwTUMG2.getObjectHeight()/2,1.0)
}

function onEndState_Hermittriplestep(CQFA2MPUrhq9m5tgr3, CQRuohwg3i1fYuW9umf)
{
	if(!CQFA2MPUrhq9m5tgr3) return
local CQUUgQjNbNy3TlrkE2 = CQFA2MPUrhq9m5tgr3.getSkillSubState()
switch(CQUUgQjNbNy3TlrkE2)
	{
	case 3:

		break
case 4:

		break
}
	
}

function HermittriplestepSearchTarget(obj)
{
		local x = obj.getXPos(); 
		local y = obj.getYPos(); 
		local z = obj.getZPos(); 
		local a = 300; 
		local b = 130; 
		local c = 300; 
		local objectManager = obj.getObjectManager(); 
		local number = objectManager.getCollisionObjectNumber(); 


		for(local i = 0; i < number; i++)
		{
			local object = objectManager.getCollisionObject(i); 
			if(!obj.isEnemy(object) || !object || !object.isInDamagableState(obj)) continue; 
			if(sq_Abs(x - sq_GetXPos(object)) > a
			|| sq_Abs(y - sq_GetYPos(object)) > b
			|| sq_Abs(z - sq_GetZPos(object)) > c) continue; 

			local activeObj = sq_GetCNRDObjectToActiveObject(object); 
			
			if(activeObj )
			{
				if(!activeObj.isDead())
				{

					obj.getVar("Hermittriplestep").push_obj_vector(object)
				}
				
			}
		
		
		}


return

}

function HermittriplestepSetPos(CQLoWXu9GXCR9FqgUm6W,CQlq8dYXxle34zqxw)
{
	if(CQlq8dYXxle34zqxw > 0)
	{
		local CQIlOb7Iaa4ZdHmktjt = CQLoWXu9GXCR9FqgUm6W.sq_GetInputDirection(0)
if(CQLoWXu9GXCR9FqgUm6W.getDirection() == CQIlOb7Iaa4ZdHmktjt)
		{
			sq_BinaryStartWrite()
sq_BinaryWriteDword(1)
sq_SendChangeSkillEffectPacket(CQLoWXu9GXCR9FqgUm6W, 225)
}

	}
}

function onProc_Hermittriplestep(CQ78zpszRLoS5Wmv)
{
	if(!CQ78zpszRLoS5Wmv) return
local CQrBOKm5WkfoM4izL3 = CQ78zpszRLoS5Wmv.getSkillSubState()
local CQCGl7RKLpPQ6uuUVpAx = sq_GetCurrentAnimation(CQ78zpszRLoS5Wmv)
local CQcELYVQn1zc1luY1 = CQ78zpszRLoS5Wmv.sq_GetCurrentFrameIndex(CQCGl7RKLpPQ6uuUVpAx)
local CQAwQuIkAhKRCGyQ5mg = sq_GetDelaySum(CQCGl7RKLpPQ6uuUVpAx)
local CQdx4Hq26iU32ctn = CQ78zpszRLoS5Wmv.sq_GetStateTimer()
switch(CQrBOKm5WkfoM4izL3)
	{
	case 1:
		HermittriplestepSearchTarget(CQ78zpszRLoS5Wmv)
HermittriplestepSetPos(CQ78zpszRLoS5Wmv,CQcELYVQn1zc1luY1)
local CQydE52poNN6VKtrnj = CQ78zpszRLoS5Wmv.getVar("Hermittriplestep").get_vector(1)
local CQIIYWXof7wGlanil = sq_GetAccel(CQ78zpszRLoS5Wmv.getXPos(), CQydE52poNN6VKtrnj, CQdx4Hq26iU32ctn, CQAwQuIkAhKRCGyQ5mg/2, false)
if(CQ78zpszRLoS5Wmv.isMovablePos(CQIIYWXof7wGlanil, CQ78zpszRLoS5Wmv.getYPos()))
			sq_setCurrentAxisPos(CQ78zpszRLoS5Wmv, 0, CQIIYWXof7wGlanil)
break
case 2:
		HermittriplestepSearchTarget(CQ78zpszRLoS5Wmv)
HermittriplestepSetPos(CQ78zpszRLoS5Wmv,CQcELYVQn1zc1luY1)
local CQydE52poNN6VKtrnj = CQ78zpszRLoS5Wmv.getVar("Hermittriplestep").get_vector(1)
local CQIIYWXof7wGlanil = sq_GetAccel(CQ78zpszRLoS5Wmv.getXPos(), CQydE52poNN6VKtrnj, CQdx4Hq26iU32ctn, CQAwQuIkAhKRCGyQ5mg/2, false)
if(CQ78zpszRLoS5Wmv.isMovablePos(CQIIYWXof7wGlanil, CQ78zpszRLoS5Wmv.getYPos()))
			sq_setCurrentAxisPos(CQ78zpszRLoS5Wmv, 0, CQIIYWXof7wGlanil)
break
case 3:
		HermittriplestepSearchTarget(CQ78zpszRLoS5Wmv)
HermittriplestepSetPos(CQ78zpszRLoS5Wmv,CQcELYVQn1zc1luY1)
local CQydE52poNN6VKtrnj = CQ78zpszRLoS5Wmv.getVar("Hermittriplestep").get_vector(1)
local CQIIYWXof7wGlanil = sq_GetAccel(CQ78zpszRLoS5Wmv.getXPos(), CQydE52poNN6VKtrnj, CQdx4Hq26iU32ctn, CQAwQuIkAhKRCGyQ5mg/2, false)
if(CQ78zpszRLoS5Wmv.isMovablePos(CQIIYWXof7wGlanil, CQ78zpszRLoS5Wmv.getYPos()))
			sq_setCurrentAxisPos(CQ78zpszRLoS5Wmv, 0, CQIIYWXof7wGlanil)
break
case 4:
		local CQydE52poNN6VKtrnj = CQ78zpszRLoS5Wmv.getVar("Hermittriplestep").get_vector(0)
local CQIIYWXof7wGlanil = sq_GetAccel(CQ78zpszRLoS5Wmv.getXPos(), CQydE52poNN6VKtrnj, CQdx4Hq26iU32ctn, 30, false)
if(CQ78zpszRLoS5Wmv.isMovablePos(CQIIYWXof7wGlanil, CQ78zpszRLoS5Wmv.getYPos()))
			sq_setCurrentAxisPos(CQ78zpszRLoS5Wmv, 0, CQIIYWXof7wGlanil)
break
case 6:
		
		break
}
}

function onProcCon_Hermittriplestep(CQa2dfZcZaQVaupr)
{
	if(!CQa2dfZcZaQVaupr) return
local CQ5KAnE8j42FS6ppv2 = CQa2dfZcZaQVaupr.getSkillSubState()
switch(CQ5KAnE8j42FS6ppv2)
	{
	case 0:

		break
}
}
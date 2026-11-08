

function checkExecutableSkill_Inhalation(CQZtPZdr7pdrixiss)
{
	if (!CQZtPZdr7pdrixiss) return false
local CQzbx8Clq1OvIJioSjn = CQZtPZdr7pdrixiss.sq_IsUseSkill(211)
if (CQzbx8Clq1OvIJioSjn)
	{
		CQZtPZdr7pdrixiss.sq_IntVectClear()
CQZtPZdr7pdrixiss.sq_IntVectPush(0)
CQZtPZdr7pdrixiss.sq_AddSetStatePacket(211, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Inhalation(CQOhXve5NhTjotuP)
{
	if (!CQOhXve5NhTjotuP) return false
return true
}

function onSetState_Inhalation(obj, CQWZ5J1qaNn8qiyi9mi3, CQVPa6SjfYBMt8tOg, CQYykxrJryrJQHtETj4)
{
	if(!obj) return
local CQSnJyToKV5IbcWS = obj.sq_GetVectorData(CQVPa6SjfYBMt8tOg, 0)
obj.setSkillSubState(CQSnJyToKV5IbcWS)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
switch(CQSnJyToKV5IbcWS)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_SetCurrentAnimation(536)
obj.sq_SetCurrentAttackInfo(0)
local CQfjkGJhbxEywKrIUh = obj.sq_GetBonusRateWithPassive(211, -1, 0,getATSwordmanBonus(obj,1.0,211))
obj.sq_SetCurrentAttackBonusRate(CQfjkGJhbxEywKrIUh)
local CQu5H3i1PIgUnyIGap4a = obj.getObjectManager()
local CQMXUlYF5XSTx6sAP = sq_GetIntData(obj,211, 2)
obj.getVar("Inhalation").clear_obj_vector()
for (local CQnA1W8bilx9UoaJFmr = 0; CQnA1W8bilx9UoaJFmr < CQu5H3i1PIgUnyIGap4a.getCollisionObjectNumber(); CQnA1W8bilx9UoaJFmr++)
		{
			local CQGuiSLfVaZMcxaD = CQu5H3i1PIgUnyIGap4a.getCollisionObject(CQnA1W8bilx9UoaJFmr)
if (CQGuiSLfVaZMcxaD && CQGuiSLfVaZMcxaD.isObjectType(OBJECTTYPE_ACTIVE) && obj.isEnemy(CQGuiSLfVaZMcxaD) && !obj.getVar("Inhalation").is_obj_vector(CQGuiSLfVaZMcxaD))
			{
				local CQ3UR1pBQ3qJkJEZ8jNc = obj.getXDistance(CQGuiSLfVaZMcxaD)
local CQqqSjgtGk1OYvpHR = obj.getYDistance(CQGuiSLfVaZMcxaD)
if(IsFrontOf(obj,CQGuiSLfVaZMcxaD) && CQ3UR1pBQ3qJkJEZ8jNc < CQMXUlYF5XSTx6sAP && CQqqSjgtGk1OYvpHR < 50)
				{
					obj.getVar("Inhalation").push_obj_vector(CQGuiSLfVaZMcxaD)
obj.sq_StartWrite()
obj.sq_WriteDword(211)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(211, -1, 2, getATSwordmanBonus(obj,1.0,211)))
obj.sq_WriteDword(sq_GetObjectId(CQGuiSLfVaZMcxaD))
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(211, -1, 2, getATSwordmanBonus(obj,1.0,211)))
sq_SendCreatePassiveObjectPacketPos(obj, 24381, 0, CQGuiSLfVaZMcxaD.getXPos(), CQGuiSLfVaZMcxaD.getYPos(), CQGuiSLfVaZMcxaD.getZPos())
}

			}
		}
		break
case 1:
		obj.sq_SetCurrentAnimation(537)
obj.sq_SetCurrentAttackInfo(152)
local CQfjkGJhbxEywKrIUh = obj.sq_GetBonusRateWithPassive(211, -1, 0, getATSwordmanBonus(obj,1.0,211))
obj.sq_SetCurrentAttackBonusRate(CQfjkGJhbxEywKrIUh)
local CQk8SPO8a19UguoLxmdO = "character/atswordman/2_vegabond/inhalation/ap_inhalation.nut"
local CQaBYBQO1bIlz7iMy = obj.getVar("Inhalation").get_obj_vector_size()
for(local CQnA1W8bilx9UoaJFmr=0; CQnA1W8bilx9UoaJFmr<CQaBYBQO1bIlz7iMy; CQnA1W8bilx9UoaJFmr++)
		{
			local CQwprqNlLNGM9cuK = obj.getVar("Inhalation").get_obj_vector(CQnA1W8bilx9UoaJFmr)
if(CQwprqNlLNGM9cuK)
			{
				local CQZQ7stLhYv24KuNDh = "character/swordman/effect/animation/atinhalation/bounds_01bottom.ani"
local CQzzICxayAVZdbyX2pGr = "character/swordman/effect/animation/atinhalation/mon_00.ani"
DarktemplerCreateAniPooledObj(obj, CQZQ7stLhYv24KuNDh, true, false, CQwprqNlLNGM9cuK.getXPos(), CQwprqNlLNGM9cuK.getYPos(), CQwprqNlLNGM9cuK.getZPos(),1.0)
DarktemplerCreateAniPooledObj(obj, CQzzICxayAVZdbyX2pGr, true, false, CQwprqNlLNGM9cuK.getXPos(), CQwprqNlLNGM9cuK.getYPos(), CQwprqNlLNGM9cuK.getZPos() + obj.getObjectHeight()/2,1.0)
if(sq_IsHoldable(obj,CQwprqNlLNGM9cuK) && sq_IsGrabable(obj,CQwprqNlLNGM9cuK) && !sq_IsFixture(CQwprqNlLNGM9cuK))
				{
					local CQO9ld5q6VeA56P26 = CNSquirrelAppendage.sq_AppendAppendage(CQwprqNlLNGM9cuK, obj, -1, false, CQk8SPO8a19UguoLxmdO, true)
if(CQO9ld5q6VeA56P26)
					{
						sq_HoldAndDelayDie(CQwprqNlLNGM9cuK, obj, true, false, false, 0, 0, obj.getDirection(), CQO9ld5q6VeA56P26)
						sq_MoveToAppendageForce(CQwprqNlLNGM9cuK, obj, CQwprqNlLNGM9cuK, 0, 0, 80, 800, true, CQO9ld5q6VeA56P26,true)
						local CQ8NKnH4mx4iMoPBdmT = CQO9ld5q6VeA56P26.getAppendageInfo()
						CQ8NKnH4mx4iMoPBdmT.setValidTime(800)
					}
				}
			}
		}
		break
case 2:
		obj.sq_SetCurrentAnimation(538)
obj.sq_SetCurrentAttackInfo(153)
local CQfjkGJhbxEywKrIUh = obj.sq_GetBonusRateWithPassive(211, -1, 0, getATSwordmanBonus(obj,1.0,211))
obj.sq_SetCurrentAttackBonusRate(CQfjkGJhbxEywKrIUh)
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Inhalation(CQVEKLcmzXRx1HI1Qj)
{
	if(!CQVEKLcmzXRx1HI1Qj) return
local CQYwq8XhElAfCYI8tpq9 = CQVEKLcmzXRx1HI1Qj.getSkillSubState()
switch(CQYwq8XhElAfCYI8tpq9)
	{
	case 0:
		CQVEKLcmzXRx1HI1Qj.sq_IntVectClear()
CQVEKLcmzXRx1HI1Qj.sq_IntVectPush(1)
CQVEKLcmzXRx1HI1Qj.sq_AddSetStatePacket(211, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQVEKLcmzXRx1HI1Qj.sq_IntVectClear()
CQVEKLcmzXRx1HI1Qj.sq_IntVectPush(2)
CQVEKLcmzXRx1HI1Qj.sq_AddSetStatePacket(211, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQVEKLcmzXRx1HI1Qj.sq_IntVectClear()
CQVEKLcmzXRx1HI1Qj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Inhalation(CQSx3vaMfaz32Ls4o, CQffoiUie3KZVuafsoX, CQu1gJfbJkUAK7a7, CQMJF6VdvpMoBpEgMU)
{
	if(!CQSx3vaMfaz32Ls4o || CQMJF6VdvpMoBpEgMU)	return false
local CQnsgxISO1tQLcp94H7V = CQSx3vaMfaz32Ls4o.getSkillSubState()
switch(CQnsgxISO1tQLcp94H7V)
	{
	case 0:

		break
case 1:

		break
}

}

function onEnterFrame_Inhalation(CQGIFyTtjb7xFKp59, CQ3WvF2xuiaRZvoR)
{
	if(!CQGIFyTtjb7xFKp59) return
local CQqvB3DCCNj3GZD8q2 = CQGIFyTtjb7xFKp59.getSkillSubState()
switch(CQqvB3DCCNj3GZD8q2)
	{
	case 2:
		if(CQ3WvF2xuiaRZvoR ==1)
		{
			if(CQGIFyTtjb7xFKp59.isMyControlObject())
				sq_SetMyShake(CQGIFyTtjb7xFKp59,1,200)
local CQKgtlWOqYFZPiDjrm1m = "character/atswordman/2_vegabond/inhalation/ap_inhalation.nut"
local CQT39rleFPYVE8Sfu = CQGIFyTtjb7xFKp59.getVar("Inhalation").get_obj_vector_size()
for(local CQsLOS369VXFAEAlHjQ=0; CQsLOS369VXFAEAlHjQ<CQT39rleFPYVE8Sfu; CQsLOS369VXFAEAlHjQ++)
			{
				local CQ6Oz1oLaxwEaYAh = CQGIFyTtjb7xFKp59.getVar("Inhalation").get_obj_vector(CQsLOS369VXFAEAlHjQ)
if(CQ6Oz1oLaxwEaYAh)
				{
					if(sq_IsHoldable(CQGIFyTtjb7xFKp59,CQ6Oz1oLaxwEaYAh) && sq_IsGrabable(CQGIFyTtjb7xFKp59,CQ6Oz1oLaxwEaYAh) && !sq_IsFixture(CQ6Oz1oLaxwEaYAh))
					{
						local CQetOjvw1I3ruLPcNh = CNSquirrelAppendage.sq_AppendAppendage(CQ6Oz1oLaxwEaYAh, CQGIFyTtjb7xFKp59, -1, false, CQKgtlWOqYFZPiDjrm1m, true)
if(CQetOjvw1I3ruLPcNh)
						{
							sq_HoldAndDelayDie(CQ6Oz1oLaxwEaYAh, CQGIFyTtjb7xFKp59, true, true, true, 150, 150, CQGIFyTtjb7xFKp59.getDirection(), CQetOjvw1I3ruLPcNh)
sq_MoveToAppendageForce(CQ6Oz1oLaxwEaYAh, CQGIFyTtjb7xFKp59, CQGIFyTtjb7xFKp59, 90, 0, 0, 150, true, CQetOjvw1I3ruLPcNh,true)
local CQXbzw9kc5ivsnPT3owj = CQetOjvw1I3ruLPcNh.getAppendageInfo()
CQXbzw9kc5ivsnPT3owj.setValidTime(150)
}
					}
				}
			}
		}
		break
}
}

function onEndState_Inhalation(CQxhZPZ3Kldho6Obl, CQP5QBEEgaO6WoIxYUV)
{
	if(!CQxhZPZ3Kldho6Obl) return
local CQ9X4gnUP3lVp9Im = CQxhZPZ3Kldho6Obl.getSkillSubState()
switch(CQ9X4gnUP3lVp9Im)
	{
	case 3:

		break
case 4:

		break
}

}

function onProc_Inhalation(CQtAEmNg5jJFtJsvej)
{
	if(!CQtAEmNg5jJFtJsvej) return
local CQBujsPGUpnEQvawAp8K = CQtAEmNg5jJFtJsvej.getSkillSubState()
}

function onKeyFrameFlag_Inhalation(CQvUHCwiV1BryZaUG, CQDkhdjvlbWvwiHYLmu)
{
	if (!CQvUHCwiV1BryZaUG) return false
switch(CQDkhdjvlbWvwiHYLmu)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Inhalation(CQR6GnMNpu6hn8Gq)
{
	if(!CQR6GnMNpu6hn8Gq) return
local CQi7nEASdNE6xEGbRj = CQR6GnMNpu6hn8Gq.getSkillSubState()
switch(CQi7nEASdNE6xEGbRj)
	{
	case 0:

		break
}
}
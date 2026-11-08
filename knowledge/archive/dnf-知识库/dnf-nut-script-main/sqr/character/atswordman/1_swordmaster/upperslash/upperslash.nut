

function checkExecutableSkill_Upperslash(CQ7jTaT4RWNOQfWM)
{
	if (!CQ7jTaT4RWNOQfWM) return false
local CQvfHLoqouF7S8vp7yP = CQ7jTaT4RWNOQfWM.sq_IsUseSkill(128)
if (CQvfHLoqouF7S8vp7yP)
	{
		CQ7jTaT4RWNOQfWM.sq_StopMove()
CheckUseAddloadDrawsword(CQ7jTaT4RWNOQfWM,128,{[0] = true,[108] = true,[14] = true},0)
CQ7jTaT4RWNOQfWM.sq_IntVectClear()
CQ7jTaT4RWNOQfWM.sq_IntVectPush(0)
CQ7jTaT4RWNOQfWM.sq_AddSetStatePacket(128, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Upperslash(CQE5IFRqwgtvqxbTrMc8)
{
	if (!CQE5IFRqwgtvqxbTrMc8) return false
if(CQE5IFRqwgtvqxbTrMc8.getZPos() > 10)
		return false
return CheckForceDrawsword(CQE5IFRqwgtvqxbTrMc8,128,{[0] = true,[108] = true,[14] = true})
}


function onSetState_Upperslash(obj, CQol1OgJll8FE8OZR, CQ2zUBFoGasaAEIGkZq, CQm91RtndKkraYIC)
{
	if(!obj) return
local CQJNimz1sjGvuLsKuI = obj.sq_GetVectorData(CQ2zUBFoGasaAEIGkZq, 0)
obj.setSkillSubState(CQJNimz1sjGvuLsKuI)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
switch(CQJNimz1sjGvuLsKuI)
	{
	case 0:

		BodyMagicSword(obj, "UpperSlash1")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(329)
else
			obj.sq_SetCurrentAnimation(77)
obj.sq_SetCurrentAttackInfo(60)
local CQkHfa4D2pvjenaNE6p6 = obj.sq_GetBonusRateWithPassive(128, -1, 0,getATSwordmanBonus(obj,1.0,128))
obj.sq_SetCurrentAttackBonusRate(CQkHfa4D2pvjenaNE6p6)
obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL)
obj.sq_SetStaticMoveInfo(0, 400, -1000, false)
local CQEaSXGyv1C6o6JXO = sq_GetIntData(obj,128, 3) + 1
local CQ4eYdyfLgeVWoH2BZ = sq_GetCurrentAnimation(obj)
local CQQcVb9Vhu4Gq9GB2zHE = sq_GetDelaySum(CQ4eYdyfLgeVWoH2BZ)
obj.setTimeEvent(0,CQQcVb9Vhu4Gq9GB2zHE/CQEaSXGyv1C6o6JXO,CQEaSXGyv1C6o6JXO,true)
break
case 1:
		obj.sq_StopMove()
BodyMagicSword(obj, "UpperSlash2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(330)
else
			obj.sq_SetCurrentAnimation(78)
obj.sq_SetCurrentAttackInfo(61)
local CQkHfa4D2pvjenaNE6p6 = obj.sq_GetBonusRateWithPassive(128, -1, 1, getATSwordmanBonus(obj,1.0,128))
obj.sq_SetCurrentAttackBonusRate(CQkHfa4D2pvjenaNE6p6)
break
case 2:
		BodyMagicSword(obj, "UpperSlash2Lv95Passive_Body")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(331)
else
			obj.sq_SetCurrentAnimation(80)
obj.sq_SetCurrentAttackInfo(62)
local CQkHfa4D2pvjenaNE6p6 = obj.sq_GetBonusRateWithPassive(128, -1, 2, getATSwordmanBonus(obj,1.0,128))
obj.sq_SetCurrentAttackBonusRate(CQkHfa4D2pvjenaNE6p6)
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Upperslash(CQrJr7n7mtPvbZFVUs)
{
	if(!CQrJr7n7mtPvbZFVUs) return
local CQCs7YfOBVzjwUD4w6A9 = CQrJr7n7mtPvbZFVUs.getSkillSubState()
switch(CQCs7YfOBVzjwUD4w6A9)
	{
	case 0:
		CQrJr7n7mtPvbZFVUs.sq_IntVectClear()
CQrJr7n7mtPvbZFVUs.sq_IntVectPush(1)
CQrJr7n7mtPvbZFVUs.sq_AddSetStatePacket(128, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQrJr7n7mtPvbZFVUs.sq_IntVectClear()
CQrJr7n7mtPvbZFVUs.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQrJr7n7mtPvbZFVUs.sq_IntVectClear()
CQrJr7n7mtPvbZFVUs.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onTimeEvent_Upperslash(CQcrIuCezxK6n8SMt, CQAYTHelErUVxES7oZg, CQdRK5kLfZNGUdA3)
{
	if(!CQcrIuCezxK6n8SMt)	return false
switch(CQAYTHelErUVxES7oZg)
	{
	case 0:
		CQcrIuCezxK6n8SMt.resetHitObjectList()
break
}
}

function onAttack_Upperslash(CQy2qz1arltacKPdCI, CQNK3tSqKa7IkbP616bV, CQbIqFr3bKayYXOg5, CQFt22THOjhUToL9xZJ)
{
	if(!CQy2qz1arltacKPdCI)	return false
local CQgyoTJo4pDTR9Lk = CQy2qz1arltacKPdCI.getSkillSubState()
MagicswordupOccur(CQy2qz1arltacKPdCI, CQNK3tSqKa7IkbP616bV, CQbIqFr3bKayYXOg5, CQFt22THOjhUToL9xZJ)
switch(CQgyoTJo4pDTR9Lk)
	{
	case 0:

		break
case 1:

		break
}

}

function onEnterFrame_Upperslash(CQongrogu1Y97aKfqL, CQ2jFAvMCgXMgRJlrl3y)
{
	if(!CQongrogu1Y97aKfqL) return
local CQm5bM8DquQJ8ZJhD = CQongrogu1Y97aKfqL.getSkillSubState()
switch(CQm5bM8DquQJ8ZJhD)
	{
	case 3:

		break
case 4:

		break
}
}

function onEndState_Upperslash(CQJXBhLvFN2O3nHdJ6e, CQkAtQpd9Yiy9CGT)
{
	if(!CQJXBhLvFN2O3nHdJ6e) return
local CQauBOgSatdU4pGgNZ = CQJXBhLvFN2O3nHdJ6e.getSkillSubState()
switch(CQauBOgSatdU4pGgNZ)
	{
	case 3:

		break
case 4:

		break
}
	
}

function onKeyFrameFlag_Upperslash(CQ5UtVBt1COlNdFxhleY, CQwk8ROxYxT95sDkl)
{
	if (!CQ5UtVBt1COlNdFxhleY) return false
switch(CQwk8ROxYxT95sDkl)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Upperslash(CQZ6OmQCLIJMMbDvv6B)
{
	if(!CQZ6OmQCLIJMMbDvv6B) return
local CQ8CzahOhZnKXXSzme = CQZ6OmQCLIJMMbDvv6B.getSkillSubState()
switch(CQ8CzahOhZnKXXSzme)
	{
	case 0:

		break
}
}

function onProc_Upperslash(CQWSZXMwPTBO1mVUsZUK)
{
	if(!CQWSZXMwPTBO1mVUsZUK) return
local CQViwdy65aryV8CYA = CQWSZXMwPTBO1mVUsZUK.getSkillSubState()
}

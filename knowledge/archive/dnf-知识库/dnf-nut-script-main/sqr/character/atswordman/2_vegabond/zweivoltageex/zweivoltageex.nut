

function checkExecutableSkill_Zweivoltageex(CQN2OdRyiVcWLM4ho1)
{
	if (!CQN2OdRyiVcWLM4ho1) return false
local CQbKznVd8xZbFs3cIUiQ = CQN2OdRyiVcWLM4ho1.sq_IsUseSkill(222)
if (CQbKznVd8xZbFs3cIUiQ)
	{
		CQN2OdRyiVcWLM4ho1.sq_IntVectClear()
CQN2OdRyiVcWLM4ho1.sq_IntVectPush(0)
CQN2OdRyiVcWLM4ho1.sq_AddSetStatePacket(222, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Zweivoltageex(CQFIOEIVQIQkOg2TV)
{
	if (!CQFIOEIVQIQkOg2TV) return false
return true
}


function onSetState_Zweivoltageex(obj, CQovL8gccluBPm1x, CQ2gQvF7sa9HEBMU92, CQm34itZ23OsywfYbU56)
{
	if(!obj) return
local CQJLEJzetjTWaRdQQ = obj.sq_GetVectorData(CQ2gQvF7sa9HEBMU92, 0)
obj.setSkillSubState(CQJLEJzetjTWaRdQQ)
switch(CQJLEJzetjTWaRdQQ)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_SetCurrentAnimation(593)
obj.sq_SetCurrentAttackInfo(0)
local CQkPh54TZpHuuO9nWnr = obj.sq_GetBonusRateWithPassive(222, -1, 0,getATSwordmanBonus(obj,1.0,222))
obj.sq_SetCurrentAttackBonusRate(CQkPh54TZpHuuO9nWnr)
obj.getVar("Zweivoltageex").clear_obj_vector()
local CQEypxG4U1bmrh9r = sq_FindTarget(obj,-500, 500, 100, 180)
if(CQEypxG4U1bmrh9r)
			obj.getVar("Zweivoltageex").push_obj_vector(CQEypxG4U1bmrh9r)
break
case 1:
		obj.sq_ZStop()
obj.sq_SetCurrentAnimation(594)
obj.sq_SetCurrentAttackInfo(0)
local CQkPh54TZpHuuO9nWnr = obj.sq_GetBonusRateWithPassive(222, -1, 0, getATSwordmanBonus(obj,1.0,222))
obj.sq_SetCurrentAttackBonusRate(CQkPh54TZpHuuO9nWnr)
local CQQjGF9m6urdWq7yXoO = obj.getVar("Zweivoltageex").get_obj_vector_size()
obj.getVar("ZweivoltageexPos").clear_vector()
obj.getVar("ZweivoltageexPos").push_vector(obj.getXPos())
if(CQQjGF9m6urdWq7yXoO < 1)
			break
local CQL5b3ZhoN51qN7e = obj.getVar("Zweivoltageex").get_obj_vector(0)
if(CQL5b3ZhoN51qN7e)
		{
			if(CQL5b3ZhoN51qN7e.getXPos() - obj.getXPos() >= 0)
			{
				obj.getVar("ZweivoltageexPos").set_vector(0,CQL5b3ZhoN51qN7e.getXPos() - 100)
obj.setDirection(1)
}
			else
			{
				obj.getVar("ZweivoltageexPos").set_vector(0,CQL5b3ZhoN51qN7e.getXPos() + 100)
obj.setDirection(0)
}
		}
		else
		{
			
		}
		break
case 2:
		obj.sq_SetCurrentAnimation(595)
obj.sq_SetCurrentAttackInfo(0)
local CQkPh54TZpHuuO9nWnr = obj.sq_GetBonusRateWithPassive(222, -1, 0, getATSwordmanBonus(obj,1.0,222))
obj.sq_SetCurrentAttackBonusRate(CQkPh54TZpHuuO9nWnr)
break
}
	obj.sq_SetStaticSpeedInfo(2, 2,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Zweivoltageex(CQIAyrniztROQg6t8GZk)
{
	if(!CQIAyrniztROQg6t8GZk) return
local CQCudSfgHVSubP5wvhp = CQIAyrniztROQg6t8GZk.getSkillSubState()
switch(CQCudSfgHVSubP5wvhp)
	{
	case 0:
		CQIAyrniztROQg6t8GZk.sq_IntVectClear()
CQIAyrniztROQg6t8GZk.sq_IntVectPush(1)
CQIAyrniztROQg6t8GZk.sq_AddSetStatePacket(222, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQIAyrniztROQg6t8GZk.sq_IntVectClear()
CQIAyrniztROQg6t8GZk.sq_IntVectPush(2)
CQIAyrniztROQg6t8GZk.sq_AddSetStatePacket(222, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQIAyrniztROQg6t8GZk.sq_IntVectClear()
CQIAyrniztROQg6t8GZk.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onEnterFrame_Zweivoltageex(CQciAMCMfxxmwk4i, CQAm9jeDIILlnB4Weg)
{
	if(!CQciAMCMfxxmwk4i || !CQciAMCMfxxmwk4i.isMyControlObject()) return
local CQdTPwkv3ZmdxQ3EyiGV = CQciAMCMfxxmwk4i.getSkillSubState()
switch(CQdTPwkv3ZmdxQ3EyiGV)
	{
	case 0:
		if(CQAm9jeDIILlnB4Weg == 12)
		{
			sq_SetMyShake(CQciAMCMfxxmwk4i,5,50)
sq_flashScreen(CQciAMCMfxxmwk4i,50,100,50,204,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
CQciAMCMfxxmwk4i.sq_StartWrite()
CQciAMCMfxxmwk4i.sq_WriteDword(222)
CQciAMCMfxxmwk4i.sq_WriteDword(0)
CQciAMCMfxxmwk4i.sq_WriteDword(CQciAMCMfxxmwk4i.sq_GetBonusRateWithPassive(222, -1, 0, getATSwordmanBonus(CQciAMCMfxxmwk4i,1.0,222)))
CQciAMCMfxxmwk4i.sq_SendCreatePassiveObjectPacket(24381, 0, 119, -1, 63)
}
		break
case 2:
		if(CQAm9jeDIILlnB4Weg == 0)
		{
			sq_SetMyShake(CQciAMCMfxxmwk4i,10,100)
sq_flashScreen(CQciAMCMfxxmwk4i,50,100,50,204,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
CQciAMCMfxxmwk4i.sq_StartWrite()
CQciAMCMfxxmwk4i.sq_WriteDword(222)
CQciAMCMfxxmwk4i.sq_WriteDword(1)
CQciAMCMfxxmwk4i.sq_WriteDword(CQciAMCMfxxmwk4i.sq_GetBonusRateWithPassive(222, -1, 1, getATSwordmanBonus(CQciAMCMfxxmwk4i,1.0,222)))
CQciAMCMfxxmwk4i.sq_WriteDword(CQciAMCMfxxmwk4i.sq_GetBonusRateWithPassive(222, -1, 2, getATSwordmanBonus(CQciAMCMfxxmwk4i,1.0,222)))
CQciAMCMfxxmwk4i.sq_SendCreatePassiveObjectPacket(24381, 0, 100, -1, 69)
}
		break
}
}

function onAttack_Zweivoltageex(CQy7xO1dbl11jMguG, CQNVXBSVXayKcIgIZnT, CQbDegrWk38PkhRp, CQFp5mTxujsufAfA2g)
{
	if(!CQy7xO1dbl11jMguG || CQFp5mTxujsufAfA2g)	return false
local CQgQasJ77pjmTqfsToQt = CQy7xO1dbl11jMguG.getSkillSubState()
switch(CQgQasJ77pjmTqfsToQt)
	{
	case 0:

		break
case 1:

		break
}

}

function onEndState_Zweivoltageex(CQozkCoIq1GwRNdDc, CQ29advwFbvc7e9OnUC)
{
	if(!CQozkCoIq1GwRNdDc) return
local CQmNkn8TxuCRgg9H = CQozkCoIq1GwRNdDc.getSkillSubState()
switch(CQmNkn8TxuCRgg9H)
	{
	case 3:

		break
case 4:

		break
}
	
}

function onKeyFrameFlag_Zweivoltageex(CQJGHpLKaNw48O8SPh, CQkEULpERY4X3j7IFF7Y)
{
	if (!CQJGHpLKaNw48O8SPh) return false
switch(CQkEULpERY4X3j7IFF7Y)
	{
	case 0:

		break
}
	return true
}


function onProc_Zweivoltageex(CQaw18gmWtoS9V7GK)
{
	if(!CQaw18gmWtoS9V7GK) return
local CQ5xiYB3LCfp4Q6ACiy = CQaw18gmWtoS9V7GK.getSkillSubState()
local CQwdfiOGnxPwNMkK = sq_GetCurrentAnimation(CQaw18gmWtoS9V7GK)
local CQZMSJQUAIzc5rkFkn = sq_GetDelaySum(CQwdfiOGnxPwNMkK)
local CQz1f5hg6ZKgMhjXxGAN = CQaw18gmWtoS9V7GK.sq_GetStateTimer()
switch(CQ5xiYB3LCfp4Q6ACiy)
	{
	case 1:
		local CQOJSxMNiTU4XAjJb = CQaw18gmWtoS9V7GK.getVar("ZweivoltageexPos").get_vector(0)
local CQVsYyyuVaNXJkhB = sq_GetAccel(CQaw18gmWtoS9V7GK.getXPos(), CQOJSxMNiTU4XAjJb, CQz1f5hg6ZKgMhjXxGAN, 40, false)
local CQYWCFxvQ3ODVBgZI1 = sq_GetAccel(CQaw18gmWtoS9V7GK.getZPos(), 200, CQz1f5hg6ZKgMhjXxGAN, 40, false)
if(CQaw18gmWtoS9V7GK.isMovablePos(CQVsYyyuVaNXJkhB,CQaw18gmWtoS9V7GK.getYPos()))
		{
			sq_setCurrentAxisPos(CQaw18gmWtoS9V7GK, 0, CQVsYyyuVaNXJkhB)
sq_setCurrentAxisPos(CQaw18gmWtoS9V7GK, 2, CQYWCFxvQ3ODVBgZI1)
}
		break
case 2:
		local CQSvr359GjlpKwg1SUwE = CQaw18gmWtoS9V7GK.sq_GetCurrentFrameIndex(CQwdfiOGnxPwNMkK)
if(CQSvr359GjlpKwg1SUwE < 2)
		{
			local CQYWCFxvQ3ODVBgZI1 = sq_GetAccel(CQaw18gmWtoS9V7GK.getZPos(), 0, CQz1f5hg6ZKgMhjXxGAN, 40, false)
sq_setCurrentAxisPos(CQaw18gmWtoS9V7GK, 2, CQYWCFxvQ3ODVBgZI1)
}
		break
}
}

function onProcCon_Zweivoltageex(CQu3IruWs1nrLOf46nV)
{
	if(!CQu3IruWs1nrLOf46nV) return
local CQMLlScx2bBbFjfM = CQu3IruWs1nrLOf46nV.getSkillSubState()
switch(CQMLlScx2bBbFjfM)
	{
	case 0:

		break
}
}
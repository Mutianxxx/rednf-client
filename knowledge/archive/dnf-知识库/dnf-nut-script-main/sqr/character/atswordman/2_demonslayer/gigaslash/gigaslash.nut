

function checkExecutableSkill_Gigaslash(CQk636QXERfKMjJmCOM)
{
	if (!CQk636QXERfKMjJmCOM) return false
local CQwHuwhke6FKIAALWk = CQk636QXERfKMjJmCOM.sq_IsUseSkill(164)
if (CQwHuwhke6FKIAALWk)
	{
		CQk636QXERfKMjJmCOM.sq_IntVectClear()
CQk636QXERfKMjJmCOM.sq_IntVectPush(0)
CQk636QXERfKMjJmCOM.sq_AddSetStatePacket(164, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Gigaslash(CQAS9LApV9iTfIie)
{
	if (!CQAS9LApV9iTfIie) return false
return true
}

function onSetState_Gigaslash(obj, CQnhPQnUTpbC9f8EK, CQG4xOdgFHVD4I8S, CQhZXBXG8gepNh7IMl)
{
	if(!obj) return
local CQpAwReuQi4e5C6GkKQZ = obj.sq_GetVectorData(CQG4xOdgFHVD4I8S, 0)
obj.setSkillSubState(CQpAwReuQi4e5C6GkKQZ)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	

switch(CQpAwReuQi4e5C6GkKQZ)
	{
	case 0:
		obj.sq_StopMove()
obj.sq_PlaySound("SW_GIGASLASH")
if(obj.isMyControlObject())
			sq_flashScreen(obj,200,550,100,102,sq_RGB(0,0,0),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
obj.sq_SetCurrentAnimation(422)
break
case 1:
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL)
obj.sq_SetStaticMoveInfo(0, 300, -100, false)
if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT , ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == 1)
			obj.sq_SetStaticMoveInfo(0, 0, -100, false);	
		else if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT , ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == 0)
			obj.sq_SetStaticMoveInfo(0, 0, -100, false);	
		else if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP , ENUM_SUBKEY_TYPE_ALL))
			obj.sq_SetStaticMoveInfo(0, 600, -100, false);	
		
		obj.sq_SetCurrentAnimation(423)
break
case 2:
		obj.sq_StopMove()
obj.sq_SetCurrentAnimation(421)
		if(obj.isMyControlObject())
		{
			sq_SetMyShake(obj,8,400)
sq_flashScreen(obj,0,0,200,255,sq_RGB(255,255,255),GRAPHICEFFECT_NONE,ENUM_DRAWLAYER_BOTTOM)
obj.sq_StartWrite()
obj.sq_WriteDword(164)
obj.sq_WriteDword(0)
obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(164, -1, 0, getATSwordmanBonus(obj,1.0,164)))
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
}
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}


function onEndCurrentAni_Gigaslash(CQ3uZmkRMFpWMq6Ax)
{
	if(!CQ3uZmkRMFpWMq6Ax) return
local CQmUwa1NcfRbXB5Kba = CQ3uZmkRMFpWMq6Ax.getSkillSubState()
switch(CQmUwa1NcfRbXB5Kba)
	{
	case 0:
		CQ3uZmkRMFpWMq6Ax.sq_IntVectClear()
CQ3uZmkRMFpWMq6Ax.sq_IntVectPush(1)
CQ3uZmkRMFpWMq6Ax.sq_AddSetStatePacket(164, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQ3uZmkRMFpWMq6Ax.sq_IntVectClear()
CQ3uZmkRMFpWMq6Ax.sq_IntVectPush(2)
CQ3uZmkRMFpWMq6Ax.sq_AddSetStatePacket(164, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 2:
		CQ3uZmkRMFpWMq6Ax.sq_IntVectClear()
CQ3uZmkRMFpWMq6Ax.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Gigaslash(CQJk5XSAKtAkHw4Fq5Qq, CQk6adrYgVz7CR4ZI, CQaCjbT9t9KBJO3HSLC, CQ5SHp2C5rmHSj2V)
{
	if(!CQJk5XSAKtAkHw4Fq5Qq || CQ5SHp2C5rmHSj2V)	return false
local CQwiULirUZMsKV2LXs = CQJk5XSAKtAkHw4Fq5Qq.getSkillSubState()
Calldaimus_onAttack(CQJk5XSAKtAkHw4Fq5Qq,CQk6adrYgVz7CR4ZI, CQaCjbT9t9KBJO3HSLC, CQ5SHp2C5rmHSj2V)
switch(CQwiULirUZMsKV2LXs)
	{
	case 0:

		break
case 1:

		break
}

}

function onEndState_Gigaslash(CQ8VuHpQBjj7OgdN, CQWDf5bkwpFNpPdXoL)
{
	if(!CQ8VuHpQBjj7OgdN) return
local CQVFSzBJHHYHPm92sTSL = CQ8VuHpQBjj7OgdN.getSkillSubState()
switch(CQVFSzBJHHYHPm92sTSL)
	{
	case 3:

		break
case 4:

		break
}
	
}

function onProc_Gigaslash(CQYEctOpYgXsEB8BA)
{
	if(!CQYEctOpYgXsEB8BA) return
local CQSwCFQUIuwtyw85G5h = CQYEctOpYgXsEB8BA.getSkillSubState()
}

function onKeyFrameFlag_Gigaslash(CQfxr2h23N3na171, CQndCTNFyfimuO688Lsv)
{
	if (!CQfxr2h23N3na171) return false
switch(CQndCTNFyfimuO688Lsv)
	{
	case 0:

		break
}
	return true
}


function onProcCon_Gigaslash(CQGMrrPnXtdzej64g)
{
	if(!CQGMrrPnXtdzej64g) return
local CQhH6AzRkVPdmA5fTs9 = CQGMrrPnXtdzej64g.getSkillSubState()
switch(CQhH6AzRkVPdmA5fTs9)
	{
	case 0:

		break
}
}
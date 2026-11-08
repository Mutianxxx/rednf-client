

function checkExecutableSkill_Halfmoon(CQOCqZHFyVl1weahG3)
{
	if (!CQOCqZHFyVl1weahG3) return false
local CQTripSvy6EQGcmoW = CQOCqZHFyVl1weahG3.sq_IsUseSkill(133)
if (CQTripSvy6EQGcmoW)
	{
		CQOCqZHFyVl1weahG3.sq_IsEnterSkillLastKeyUnits(133)
CheckUseAddloadDrawsword(CQOCqZHFyVl1weahG3,133, {[0] = true,[108] = true,[14] = true},0)
if(CQOCqZHFyVl1weahG3.sq_GetState() != 0 && CQOCqZHFyVl1weahG3.sq_GetState() != 14 && CQOCqZHFyVl1weahG3.sq_GetState() != 108 && sq_GetSkillLevel(CQOCqZHFyVl1weahG3, 11)>0 && CQOCqZHFyVl1weahG3.getWeaponSubType() == 1)
			CQOCqZHFyVl1weahG3.getVar("WeaponcomboWeapon3").setBool(0,true)
else
			CQOCqZHFyVl1weahG3.getVar("WeaponcomboWeapon3").setBool(0,false)
local CQH5cxhd2DwK6oD78rAj = 0
if(CQOCqZHFyVl1weahG3.getVar("WeaponcomboWeapon3").getBool(0))
			CQH5cxhd2DwK6oD78rAj = 1
CQOCqZHFyVl1weahG3.sq_StopMove()
CQOCqZHFyVl1weahG3.sq_PlaySound("SW_HALFMOON")
CQOCqZHFyVl1weahG3.sq_IntVectClear()
CQOCqZHFyVl1weahG3.sq_IntVectPush(CQH5cxhd2DwK6oD78rAj)
CQOCqZHFyVl1weahG3.sq_AddSetStatePacket(133, STATE_PRIORITY_IGNORE_FORCE, true)
return true
}
	return false
}

function checkCommandEnable_Halfmoon(CQjXXtFStf3O19Shg)
{
	if (!CQjXXtFStf3O19Shg) return false
if(CQjXXtFStf3O19Shg.getZPos() > 10)
		return false
return CheckForceDrawsword(CQjXXtFStf3O19Shg,133, {[0] = true,[108] = true,[14] = true})
}

function onSetState_Halfmoon(obj, CQ4u63zdjAdm2YAT, CQQUeT4CS9PlVLPgu8, CQLk5rGO7rl9KnOxEInK)
{
	if(!obj) return
local CQl6aSyxqOJ1B7OkZ = obj.sq_GetVectorData(CQQUeT4CS9PlVLPgu8, 0)
obj.setSkillSubState(CQl6aSyxqOJ1B7OkZ)
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
switch(CQl6aSyxqOJ1B7OkZ)
	{
	case 0:
		BodyMagicSword(obj, "HalfMoon1")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(282)
else
			obj.sq_SetCurrentAnimation(90)
if(sq_GetSkillLevel(obj, 12) > 0 && obj.getWeaponSubType() == 3)
			sq_SendMessage(obj, OBJECT_MESSAGE_SUPERARMOR, 1, 0)
break
case 1:
		HeavyswordmasteryAddAppend(obj)
local CQICkMd6B6nKLpIRNeK = 0.0
local CQCSJjXLzwBOFdIz3X = 100
local CQcimQawHKWuZKKj7xxY = sq_GetLevelData(obj,12, 13, sq_GetSkillLevel(obj, 12))
if(obj.getVar("WeaponcomboWeapon3").getBool(0))
		{
			obj.sq_SetStaticMoveInfo(0, 600, 450, false)
CQICkMd6B6nKLpIRNeK = sq_GetIntData(obj,133, 5)/100.0
if(sq_GetSkillLevel(obj, 12) > 0 && obj.getWeaponSubType() == 3)
			{
				CQICkMd6B6nKLpIRNeK = sq_GetLevelData(obj,12, 1, sq_GetSkillLevel(obj, 12))/100.0 + CQICkMd6B6nKLpIRNeK
CQCSJjXLzwBOFdIz3X = CQcimQawHKWuZKKj7xxY + CQCSJjXLzwBOFdIz3X
}
		}
		else
			obj.sq_SetStaticMoveInfo(0, 450, 450, false)
obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL)
BodyMagicSword(obj, "HalfMoon2")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(283)
else
			obj.sq_SetCurrentAnimation(91)
local CQAq1OUkf46mGbJYY = obj.sq_GetBonusRateWithPassive(133, -1, 0, getATSwordmanBonus(obj,1.0+CQICkMd6B6nKLpIRNeK,133))
obj.sq_StartWrite()
obj.sq_WriteDword(133)
obj.sq_WriteDword(0)
obj.sq_WriteDword(CQAq1OUkf46mGbJYY)
obj.sq_WriteDword(CQCSJjXLzwBOFdIz3X)
obj.sq_SendCreatePassiveObjectPacket(24383, 0, 0, 0, 0)
break
case 2:
		local CQdliBf3rmElPXJlU8D = "character/swordman/effect/animation/athalfmoon/fullcharge.ani"
DarktemplerCreateAniPooledObj(obj, CQdliBf3rmElPXJlU8D , true , true, obj.getXPos(), obj.getYPos(), obj.getZPos(),1.0)
BodyMagicSword(obj, "HalfMoon3")
if(MagicSword_IsAppebd(obj))
			obj.sq_SetCurrentAnimation(284)
else
			obj.sq_SetCurrentAnimation(92)
break
}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Halfmoon(CQt81RCE3HgdJUHnwreX)
{
	if(!CQt81RCE3HgdJUHnwreX) return
local CQBBimembgDRS8Gcy = CQt81RCE3HgdJUHnwreX.getSkillSubState()
switch(CQBBimembgDRS8Gcy)
	{
	case 0:
		CQt81RCE3HgdJUHnwreX.sq_IntVectClear()
CQt81RCE3HgdJUHnwreX.sq_IntVectPush(2)
CQt81RCE3HgdJUHnwreX.sq_AddSetStatePacket(133, STATE_PRIORITY_IGNORE_FORCE, true)
break
case 1:
		CQt81RCE3HgdJUHnwreX.sq_IntVectClear()
CQt81RCE3HgdJUHnwreX.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
break
}
}

function onAttack_Halfmoon(CQvFRskgPnc3sEGqGxB, CQDpSX1GkDZZifFb, CQRQYdSiifqSILDeVz, CQizVnWv8v2oonDU1ONW)
{
	if(!CQvFRskgPnc3sEGqGxB)	return false
local CQ1xWplNQAuQWCSWk = CQvFRskgPnc3sEGqGxB.getSkillSubState()
MagicswordupOccur(CQvFRskgPnc3sEGqGxB, CQDpSX1GkDZZifFb, CQRQYdSiifqSILDeVz, CQizVnWv8v2oonDU1ONW)
}

function onEnterFrame_Halfmoon(CQUd8LKSF89cppAQcrm, CQHMr7oYxrIRt9Au)
{
	if(!CQUd8LKSF89cppAQcrm) return
local CQjH7Yv9aOk3QaXrQx = CQUd8LKSF89cppAQcrm.getSkillSubState()
switch(CQjH7Yv9aOk3QaXrQx)
	{
	case 0:
		if(CQHMr7oYxrIRt9Au == 3)
		{
			CQUd8LKSF89cppAQcrm.sq_IntVectClear()
CQUd8LKSF89cppAQcrm.sq_IntVectPush(2)
CQUd8LKSF89cppAQcrm.sq_AddSetStatePacket(133, STATE_PRIORITY_IGNORE_FORCE, true)
}
		break
case 4:

		break
}
}

function onEndState_Halfmoon(CQEaIi8C16HXyvZqOOox, CQ4elHLrWQbSwZZyD)
{
	if(!CQEaIi8C16HXyvZqOOox) return
if(sq_GetSkillLevel(CQEaIi8C16HXyvZqOOox, 12) > 0 && CQEaIi8C16HXyvZqOOox.getWeaponSubType() == 3 && CQ4elHLrWQbSwZZyD != 133)
		sq_SendMessage(CQEaIi8C16HXyvZqOOox, OBJECT_MESSAGE_SUPERARMOR, 0, 0)
local CQQcK5pzLKVonULeJr5 = CQEaIi8C16HXyvZqOOox.getSkillSubState()
}

function onProcCon_Halfmoon(CQLRqxg6h4eweVLo)
{
	if(!CQLRqxg6h4eweVLo) return
local CQl23tBIAm5cUEKtfe = CQLRqxg6h4eweVLo.getSkillSubState()
switch(CQl23tBIAm5cUEKtfe)
	{
	case 0:
		
		break
}
}

function onProc_Halfmoon(CQrKpFPQ6GpRcfJajXkV)
{
	if(!CQrKpFPQ6GpRcfJajXkV) return
local CQCI32wkogR4kIJizzM = CQrKpFPQ6GpRcfJajXkV.getSkillSubState()
switch(CQCI32wkogR4kIJizzM)
	{
	case 2:
		local CQcWoTjKBnA6YbHO = sq_GetLevelData(CQrKpFPQ6GpRcfJajXkV,133, 1, sq_GetSkillLevel(CQrKpFPQ6GpRcfJajXkV, 133))
local CQAvgrMplDzVTXGEo7 = sq_GetIntData(CQrKpFPQ6GpRcfJajXkV,133, 4)
		local CQdgFAyUGdLGRmGSIrfp = CQrKpFPQ6GpRcfJajXkV.sq_GetStateTimer()
if(!CQrKpFPQ6GpRcfJajXkV.isDownSkillLastKey())
		{
			CQrKpFPQ6GpRcfJajXkV.sq_IntVectClear()
CQrKpFPQ6GpRcfJajXkV.sq_IntVectPush(1)
CQrKpFPQ6GpRcfJajXkV.sq_AddSetStatePacket(133, STATE_PRIORITY_IGNORE_FORCE, true)
}
		else
		{
			if(CQdgFAyUGdLGRmGSIrfp > CQcWoTjKBnA6YbHO)
			{
				CQrKpFPQ6GpRcfJajXkV.getVar("WeaponcomboWeapon3").setBool(0,true)
CQrKpFPQ6GpRcfJajXkV.sq_IntVectClear()
CQrKpFPQ6GpRcfJajXkV.sq_IntVectPush(1)
CQrKpFPQ6GpRcfJajXkV.sq_AddSetStatePacket(133, STATE_PRIORITY_IGNORE_FORCE, true)
}
		}
		break
case 1:
		local CQy3bMx2dtmal9FIS = sq_GetAnimationFrameIndex(CQrKpFPQ6GpRcfJajXkV.getCurrentAnimation())
if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL) && CQy3bMx2dtmal9FIS < 7)
		{
			CQrKpFPQ6GpRcfJajXkV.sq_SetStaticMoveInfo(1, 200, 200, false, -500, true)
CQrKpFPQ6GpRcfJajXkV.sq_SetMoveDirection(CQrKpFPQ6GpRcfJajXkV.getDirection() , ENUM_DIRECTION_UP)
}
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL) && CQy3bMx2dtmal9FIS < 7)
		{
			CQrKpFPQ6GpRcfJajXkV.sq_SetStaticMoveInfo(1, -200, 200, false, -500, true)
CQrKpFPQ6GpRcfJajXkV.sq_SetMoveDirection(CQrKpFPQ6GpRcfJajXkV.getDirection() , ENUM_DIRECTION_DOWN)
}
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && CQrKpFPQ6GpRcfJajXkV.getDirection() == 1)
			CQrKpFPQ6GpRcfJajXkV.sq_SetStaticMoveInfo(0, 0, 0, false)
else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && CQrKpFPQ6GpRcfJajXkV.getDirection() == 0)
			CQrKpFPQ6GpRcfJajXkV.sq_SetStaticMoveInfo(0, 0, 0, false)
break
}
}

function onKeyFrameFlag_Halfmoon(CQNLNj5FeAMrgaDGHxp, CQbOtQHn28tb8RBA)
{
	if (!CQNLNj5FeAMrgaDGHxp) return false
switch(CQbOtQHn28tb8RBA)
	{
	case 0:

		break
}
	return true
}


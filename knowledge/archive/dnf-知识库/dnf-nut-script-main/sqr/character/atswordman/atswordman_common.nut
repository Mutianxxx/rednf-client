
function setState_ATSwordman(obj , state , datas , isResetTimer)
{
	setState_AllGrowJob(obj , state , datas , isResetTimer);
	
	local liftslashkey = false;
	
	if(state)
	return 0;
}

function addSetStatePacket_ATSwordman(obj, CQwYiVONEtclhP8jVvOx, CQ3KpB3vtMzYOTpSGf4J)
{
	if(!obj) return -1
	switch(CQwYiVONEtclhP8jVvOx)
	{
	case 8:
		obj.sq_IntVectClear()
		obj.sq_IntVectPush(0)
		obj.sq_AddSetStatePacket(108, STATE_PRIORITY_IGNORE_FORCE, true)
		break
	}
	return
}

function onChangeSkillEffect_ATSwordman(obj, skillIndex, reciveData)
{
	if(!obj) return
	switch(skillIndex)
	{
	case 96:
		Changesword_RemoveAppebd(obj)
		obj.sq_IntVectClear()
		obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true)
		break
	case 133:
		break
	case 202:	
		local CQ74HzT8fP4pcR5TFd = checkAppend_Dualweapon(obj)
		local CQr5Ut3Zr7pemO4RKt3U = CQ74HzT8fP4pcR5TFd + 1
		if(CQr5Ut3Zr7pemO4RKt3U > 4)
			CQr5Ut3Zr7pemO4RKt3U = 0
			Dualweapon_RemoveAppebd(obj)
			AddAppend_Dualweapon(obj,CQr5Ut3Zr7pemO4RKt3U)
		break
	}
}



function procSkill_ATSwordman(obj)
{
	if(!obj) return
	proSkill_ATSwordman_Autoguard(obj)
	return
}



function onClosePopupWindow_ATSwordman(obj, popupType, windowTileType)
{
	if (!obj)
		return;
}



function onMouseLeftButtonUp_ATSwordman(obj)
{
	onMouseLeftButtonUp_AllGrowJob(obj);
}

function SetATSwordmanStatePlaySound(obj)
{
	if(!obj) return;
	if(sq_GetSkillLevel(obj, 127) > 0)
	{
		obj.sq_SetSoundTagCreatureCommand("SW_CMDPET");
		obj.sq_SetSoundTagLackMp("R_SW_COOLTIME_BL");
		obj.sq_SetSoundTagCoolTime("R_SW_COOLTIME_BL");
		obj.sq_SetSoundTagDie("R_SW_DIE_BL");
		obj.sq_SetSoundTagBackStepStart("R_SW_BACK_BL");
	}
	else
	{
		obj.sq_SetSoundTagCreatureCommand("SW_CMDPET");
		obj.sq_SetSoundTagLackMp("R_SW_NOMANA");
		obj.sq_SetSoundTagCoolTime("R_SW_COOLTIME");
		obj.sq_SetSoundTagDie("R_SW_DIE");
		obj.sq_SetSoundTagBackStepStart("R_SW_BACK");
	}
}

function getStayAni_ATSwordman(obj)
{
	if(!obj) return null
local CQwpK91ty73WVq5Qo = obj.getVar()
local CQZQqbuc6winKN5usfW = obj.sq_GetStayAni()
local CQzz2oc7mKfkBs4r = sq_getGrowType(obj)
if(CQzz2oc7mKfkBs4r ==1)
	{
		local CQOxoK6OB4P7Lg3oMN = GetMagicSwordAppIndex(obj)
switch(CQOxoK6OB4P7Lg3oMN)
		{
		case 0:
			CQZQqbuc6winKN5usfW = obj.sq_GetStayAni()
break
case 1:
			CQZQqbuc6winKN5usfW = obj.sq_GetCustomAni(194)
break
case 2:
			CQZQqbuc6winKN5usfW = obj.sq_GetCustomAni(193)
break
case 3:
			CQZQqbuc6winKN5usfW = obj.sq_GetCustomAni(196)
break
case 4:
			CQZQqbuc6winKN5usfW = obj.sq_GetCustomAni(195)
break
}
	}else if(CQzz2oc7mKfkBs4r == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQZQqbuc6winKN5usfW = obj.sq_GetCustomAni(361)
}

	return CQZQqbuc6winKN5usfW
}

function getRestAni_ATSwordman(obj)
{
	if(!obj) return null
local CQbqEZX6rculWaK7 = obj.getVar()
local CQVHguvLdgnsGVRibYf = obj.sq_GetRestAni()
local CQYaDGVaeUNtPQRO = sq_getGrowType(obj)
if(CQYaDGVaeUNtPQRO ==1)
	{
		local CQSev4IkJFWnHMfErd = GetMagicSwordAppIndex(obj)
switch(CQSev4IkJFWnHMfErd)
		{
		case 0:
			CQVHguvLdgnsGVRibYf = obj.sq_GetRestAni()
break
case 1:
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(186)
break
case 2:
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(185)
break
case 3:
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(188)
break
case 4:
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(187)
break
}
	}
	else if(CQYaDGVaeUNtPQRO == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(359)
}
	else if(CQYaDGVaeUNtPQRO == 0)
	{
		if(sq_GetSkillLevel(obj, 127) > 0)
			CQVHguvLdgnsGVRibYf = obj.sq_GetCustomAni(708)
}
	return CQVHguvLdgnsGVRibYf
}

function getMoveAni_ATSwordman(obj)
{
	if(!obj) return null
local CQnftWgHOtE8ahdIH = obj.getVar()
local CQG18DBU4ShNSA9p = obj.sq_GetMoveAni()
local CQhKW2Ogu9DHsq9ANS = sq_getGrowType(obj)
if(CQhKW2Ogu9DHsq9ANS ==1)
	{
		local CQoI8klMCrcIiB8s3fT = GetMagicSwordAppIndex(obj)
switch(CQoI8klMCrcIiB8s3fT)
		{
		case 0:
			CQG18DBU4ShNSA9p = obj.sq_GetMoveAni()
break
case 1:
			CQG18DBU4ShNSA9p = obj.sq_GetCustomAni(178)
break
case 2:
			CQG18DBU4ShNSA9p = obj.sq_GetCustomAni(177)
break
case 3:
			CQG18DBU4ShNSA9p = obj.sq_GetCustomAni(180)
break
case 4:
			CQG18DBU4ShNSA9p = obj.sq_GetCustomAni(179)
break
}
	}else if(CQhKW2Ogu9DHsq9ANS == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQG18DBU4ShNSA9p = obj.sq_GetCustomAni(357)
}

	return CQG18DBU4ShNSA9p
}

function getSitAni_ATSwordman(obj)
{
	if(!obj) return null
local CQmvzAGvF7quoR7PYN = obj.getVar()
local CQJgLNyd9w2qWO6JUtQG = obj.sq_GetSitAni()
local CQk3QhxSaKuzqjkDe = sq_getGrowType(obj)
if(CQk3QhxSaKuzqjkDe ==1)
	{
		local CQaL4q5WMj9dtVkZAYC = GetMagicSwordAppIndex(obj)
switch(CQaL4q5WMj9dtVkZAYC)
		{
		case 0:
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetSitAni()
break
case 1:
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetCustomAni(190)
break
case 2:
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetCustomAni(189)
break
case 3:
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetCustomAni(192)
break
case 4:
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetCustomAni(191)
break
}
	}else if(CQk3QhxSaKuzqjkDe == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQJgLNyd9w2qWO6JUtQG = obj.sq_GetCustomAni(360)
}


	return CQJgLNyd9w2qWO6JUtQG
}

function getDamageAni_ATSwordman(obj, CQwt4VnCKHTLbMhVLd)
{
	if(!obj) return null
local CQZypfdIggHPwrhKVy7m = obj.getVar()
local CQznhUXztubiUggNR = obj.sq_GetDamageAni(CQwt4VnCKHTLbMhVLd)
local CQOjGaa65FVqcPRXTvy = sq_getGrowType(obj)
if(CQOjGaa65FVqcPRXTvy ==1)
	{
		local CQ85nZULUfrzmkRJ = GetMagicSwordAppIndex(obj)
switch(CQ85nZULUfrzmkRJ)
		{
		case 0:
			CQznhUXztubiUggNR = obj.sq_GetDamageAni(CQwt4VnCKHTLbMhVLd)
break
case 1:
			if(CQwt4VnCKHTLbMhVLd==0)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(145)
else if(CQwt4VnCKHTLbMhVLd==1)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(149)
break
case 2:
			if(CQwt4VnCKHTLbMhVLd==0)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(146)
else if(CQwt4VnCKHTLbMhVLd==1)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(150)
break
case 3:
			if(CQwt4VnCKHTLbMhVLd==0)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(148)
else if(CQwt4VnCKHTLbMhVLd==1)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(152)
break
case 4:
			if(CQwt4VnCKHTLbMhVLd==0)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(147)
else if(CQwt4VnCKHTLbMhVLd==1)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(151)
break
}
	}else if(CQOjGaa65FVqcPRXTvy == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
		{
			if(CQwt4VnCKHTLbMhVLd==0)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(350)
else if(CQwt4VnCKHTLbMhVLd==1)
				CQznhUXztubiUggNR = obj.sq_GetCustomAni(351)
}
	}

	return CQznhUXztubiUggNR
}

function getDownAni_ATSwordman(obj)
{
	if(!obj) return null
local CQVSyvSklAp2TwdZEySh = obj.getVar()
local CQYiNor3p9RLv1d1O = obj.sq_GetDownAni()
local CQSmyKTpdrAPlO9VDth = sq_getGrowType(obj)
if(CQSmyKTpdrAPlO9VDth ==1)
	{
		local CQfTd62UeZxigj94 = GetMagicSwordAppIndex(obj)
switch(CQfTd62UeZxigj94)
		{
		case 0:
			CQYiNor3p9RLv1d1O = obj.sq_GetDownAni()
break
case 1:
			CQYiNor3p9RLv1d1O = obj.sq_GetCustomAni(162)
break
case 2:
			CQYiNor3p9RLv1d1O = obj.sq_GetCustomAni(161)
break
case 3:
			CQYiNor3p9RLv1d1O = obj.sq_GetCustomAni(164)
break
case 4:
			CQYiNor3p9RLv1d1O = obj.sq_GetCustomAni(163)
break
}
	}else if(CQSmyKTpdrAPlO9VDth == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQYiNor3p9RLv1d1O = obj.sq_GetCustomAni(353)
}

	return CQYiNor3p9RLv1d1O
}

function getOverturnAni_ATSwordman(obj)
{
	if(!obj) return null
local CQGVxuYFYwmwhql7f = obj.getVar()
local CQhDXG7uIKMY9Nl3jdB = obj.sq_GetOverturnAni()
local CQpoejKvhjyg4eTd = sq_getGrowType(obj)
if(CQpoejKvhjyg4eTd ==1)
	{
		local CQ3q6woBym84d2k6vB = GetMagicSwordAppIndex(obj)
switch(CQ3q6woBym84d2k6vB)
		{
		case 0:
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetOverturnAni()
break
case 1:
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetCustomAni(182)
break
case 2:
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetCustomAni(181)
break
case 3:
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetCustomAni(184)
break
case 4:
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetCustomAni(183)
break
}
	}else if(CQpoejKvhjyg4eTd == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQhDXG7uIKMY9Nl3jdB = obj.sq_GetCustomAni(358)
}

	return CQhDXG7uIKMY9Nl3jdB
}

function getJumpAni_ATSwordman(obj)
{
	if(!obj) return null
local CQK85B9WmgjDMkj9I = obj.getVar()
local CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetJumpAni()
local CQsFkmQX8Dve1whR = sq_getGrowType(obj)
if(CQsFkmQX8Dve1whR ==1)
	{
		local CQ6GJshrEfCYCMg75d = GetMagicSwordAppIndex(obj)
switch(CQ6GJshrEfCYCMg75d)
		{
		case 0:
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetJumpAni()
break
case 1:
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetCustomAni(170)
break
case 2:
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetCustomAni(169)
break
case 3:
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetCustomAni(172)
break
case 4:
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetCustomAni(171)
break
}
	}else if(CQsFkmQX8Dve1whR == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQTBaRO9DuFp6Dh5Sfi = obj.sq_GetCustomAni(355)
}

	return CQTBaRO9DuFp6Dh5Sfi
}

function getJumpAttackAni_ATSwordman(obj)
{
	if(!obj) return null
local CQXe1dP5xC35VhRdg = obj.getVar()
local CQxcinwsJ9oCKAYTlYj = obj.sq_GetJumpAttackAni()
local CQPf1p4QRrfDBTcg = sq_getGrowType(obj)
if(CQPf1p4QRrfDBTcg ==1)
	{
		local CQ91iLGjOZPELNcxid = GetMagicSwordAppIndex(obj)
switch(CQ91iLGjOZPELNcxid)
		{
		case 0:
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetJumpAttackAni()
break
case 1:
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(174)
break
case 2:
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(173)
break
case 3:
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(176)
break
case 4:
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(175)
break
}
	}else if(CQPf1p4QRrfDBTcg == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(356)
}else if(CQPf1p4QRrfDBTcg == 4)
	{
		if(sq_GetSkillLevel(obj, 62) > 0)
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(513)
}else
	{
		if(sq_GetSkillLevel(obj, 127) > 0)
			CQxcinwsJ9oCKAYTlYj = obj.sq_GetCustomAni(630)
}
	
	return CQxcinwsJ9oCKAYTlYj
}

function getDashAni_ATSwordman(obj)
{
	if(!obj) return null
local CQBsSYcpnwKWO2zvP = obj.getVar()
local CQvrYi6UCKUnHOzzNvZ = obj.sq_GetDashAni()
local CQDYVHJ1TjNkAjlU = sq_getGrowType(obj)
if(CQDYVHJ1TjNkAjlU ==1)
	{
		local CQ1Rr5UFomW7aSlY8Y = GetMagicSwordAppIndex(obj)
switch(CQ1Rr5UFomW7aSlY8Y)
		{
		case 0:
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetDashAni()
break
case 1:
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetCustomAni(154)
break
case 2:
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetCustomAni(153)
break
case 3:
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetCustomAni(156)
break
case 4:
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetCustomAni(155)
break
}
	}else if(CQDYVHJ1TjNkAjlU == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQvrYi6UCKUnHOzzNvZ = obj.sq_GetCustomAni(352)
}

	return CQvrYi6UCKUnHOzzNvZ
}

function getGetItemAni_ATSwordman(obj)
{
	if(!obj) return null
local CQjjmY3vYoEjZEWtvcJB = obj.getVar()
local CQrfNyySDaQGRnbYsj = obj.sq_GetGetItemAni()
local CQF5JQBAQlj5LFu17Ev = sq_getGrowType(obj)
if(CQF5JQBAQlj5LFu17Ev ==1)
	{
		local CQYqydht7N4QdZPeIA3 = GetMagicSwordAppIndex(obj)
switch(CQYqydht7N4QdZPeIA3)
		{
		case 0:
			CQrfNyySDaQGRnbYsj = obj.sq_GetGetItemAni()
break
case 1:
			CQrfNyySDaQGRnbYsj = obj.sq_GetCustomAni(166)
break
case 2:
			CQrfNyySDaQGRnbYsj = obj.sq_GetCustomAni(165)
break
case 3:
			CQrfNyySDaQGRnbYsj = obj.sq_GetCustomAni(168)
break
case 4:
			CQrfNyySDaQGRnbYsj = obj.sq_GetCustomAni(167)
break
}
	}else if(CQF5JQBAQlj5LFu17Ev == 3)
	{
		if(sq_GetSkillLevel(obj, 148) > 0)
			CQrfNyySDaQGRnbYsj = obj.sq_GetCustomAni(354)
}

	return CQrfNyySDaQGRnbYsj
}


function DarktemplerCreateAniPooledObj(obj, CQk6md9jUlvmHRV1VY , CQaC2nZHSaClAZC8RSvj , CQDQXKDHxNU15rFh5wL, CQc53mZgrVDQnYyoF3, CQZqD8d1NpoKspZ7, CQzlvYCDx1fOidZhEt,CQO8BieyJnPursLdOV23)
{
	local CQ8BtHkfRizmobLTD = sq_CreateAnimation("",CQk6md9jUlvmHRV1VY)
CQ8BtHkfRizmobLTD.setImageRateFromOriginal(CQO8BieyJnPursLdOV23, CQO8BieyJnPursLdOV23)
local CQWFV51VONKlWXKgJAw = sq_CreatePooledObject(CQ8BtHkfRizmobLTD,CQDQXKDHxNU15rFh5wL)
CQWFV51VONKlWXKgJAw.setCurrentPos(CQc53mZgrVDQnYyoF3,CQZqD8d1NpoKspZ7,CQzlvYCDx1fOidZhEt)
if(CQaC2nZHSaClAZC8RSvj)
		sq_moveWithParent(obj, CQWFV51VONKlWXKgJAw)
sq_SetCurrentDirection(CQWFV51VONKlWXKgJAw, obj.getDirection())
sq_AddObject(obj, CQWFV51VONKlWXKgJAw, OBJECTTYPE_DRAWONLY, false)
}

function ATswordmanCreateAniPooledObj(obj, CQYE8trcbAN1t92kdt , CQSwOFT7XVWKQE1RjBaa , CQfxzhJZkx7XbfMzz, CQudLqieiIaSwIMjtS8, CQMMQIYl86honnNY, CQnH4V8LQlDwxCBTsA,CQGaQfLaGaWcUqBbA9xQ)
{
	local CQhe4Upqc36RcdVx1 = sq_CreateAnimation("",CQYE8trcbAN1t92kdt)
CQhe4Upqc36RcdVx1.setImageRateFromOriginal(CQGaQfLaGaWcUqBbA9xQ, CQGaQfLaGaWcUqBbA9xQ)
CQhe4Upqc36RcdVx1.setAutoLayerWorkAnimationAddSizeRate(CQGaQfLaGaWcUqBbA9xQ)
local CQpYpEg3skE4ksCm5Vu = sq_CreatePooledObject(CQhe4Upqc36RcdVx1,CQfxzhJZkx7XbfMzz)
CQpYpEg3skE4ksCm5Vu.setCurrentPos(CQudLqieiIaSwIMjtS8,CQMMQIYl86honnNY,CQnH4V8LQlDwxCBTsA)
if(CQSwOFT7XVWKQE1RjBaa)
		sq_moveWithParent(obj, CQpYpEg3skE4ksCm5Vu)
sq_SetCurrentDirection(CQpYpEg3skE4ksCm5Vu, obj.getDirection())
sq_AddObject(obj, CQpYpEg3skE4ksCm5Vu, OBJECTTYPE_DRAWONLY, false)
}


function IsFrontOf(obj,CQk2G9OoW1DSlZXwgA3)
{
	local CQaKnvQgLbcpgUZU = obj.getDirection()
local CQ5INohMniZw8VZWrt = 0
if(CQaKnvQgLbcpgUZU == 0)
		CQ5INohMniZw8VZWrt = obj.getXPos() - CQk2G9OoW1DSlZXwgA3.getXPos()
else
		CQ5INohMniZw8VZWrt = CQk2G9OoW1DSlZXwgA3.getXPos() - obj.getXPos()
if(CQ5INohMniZw8VZWrt<0)
		return false
return true
}

function ObjFindTarget(obj,CQZvN6tv6Y1R9f4na)
{
	obj.getVar("MonTargets").clear_obj_vector()
local CQzgycxdoAu44I3rPSI = obj.getObjectManager()
for(local CQO3dy5VBV9Xdn2q=0; CQO3dy5VBV9Xdn2q<CQzgycxdoAu44I3rPSI.getCollisionObjectNumber(); ++CQO3dy5VBV9Xdn2q)
	{
		local CQ8LPGHtwxIS5C2y3A = CQzgycxdoAu44I3rPSI.getCollisionObject(CQO3dy5VBV9Xdn2q)
local CQWZx4uxHIkGMm1e79L9 = sq_GetDistanceObject(CQ8LPGHtwxIS5C2y3A, obj, false)
if(CQ8LPGHtwxIS5C2y3A && obj.isEnemy(CQ8LPGHtwxIS5C2y3A) && CQWZx4uxHIkGMm1e79L9<=CQZvN6tv6Y1R9f4na && CQ8LPGHtwxIS5C2y3A.isObjectType(OBJECTTYPE_ACTIVE))
		{
			obj.getVar("MonTargets").push_obj_vector(CQ8LPGHtwxIS5C2y3A)
}
	}
	return 
}

function GetObjFindTargets(obj,CQYyeWXOIlbr1aMtmVc)
{
	local CQSn6Daw3aVbCRNa = null
local CQfkw1U6v3ej2OBiyA = obj.getVar("MonTargets").get_obj_vector_size()
if(CQfkw1U6v3ej2OBiyA<1)
		return CQSn6Daw3aVbCRNa
local CQu65kfLZm46VUBOpdWC = CQYyeWXOIlbr1aMtmVc
if(CQu65kfLZm46VUBOpdWC>CQfkw1U6v3ej2OBiyA)
		CQu65kfLZm46VUBOpdWC = CQu65kfLZm46VUBOpdWC - CQfkw1U6v3ej2OBiyA
CQSn6Daw3aVbCRNa = obj.getVar("MonTargets").get_obj_vector(CQu65kfLZm46VUBOpdWC)
return CQSn6Daw3aVbCRNa
}

function CreatePooledObjectAni(obj,CQDjkIC8LewNkKG2l,CQR5JVsPnL3HfbG9YWX,CQiXmRmePkiITXF5,CQ1A2UR75EdtRoDRac,CQUuUaVZiJPn88D8PA73,CQHU1XIaVhlqhEVjF,CQjki9lTQiJz9fCfKty,CQE6Rb34GMnd4LCl,CQ4CDoFJdRB1dnXhRY,CQQSYKtmsyWL5CXdkAAa)
{
	local CQLiV7zh2V6PMpZTx = sq_CreateAnimation("",CQDjkIC8LewNkKG2l)
if(CQ4CDoFJdRB1dnXhRY != false)
	{
		CQLiV7zh2V6PMpZTx.setImageRateFromOriginal(CQ4CDoFJdRB1dnXhRY, CQ4CDoFJdRB1dnXhRY)
CQLiV7zh2V6PMpZTx.setAutoLayerWorkAnimationAddSizeRate(CQ4CDoFJdRB1dnXhRY)
}
	if(CQQSYKtmsyWL5CXdkAAa != false)
		CQLiV7zh2V6PMpZTx.setSpeedRate(CQQSYKtmsyWL5CXdkAAa)
local CQlmWc41vcEu6dLgyPg = sq_CreatePooledObject(CQLiV7zh2V6PMpZTx,CQE6Rb34GMnd4LCl)
if(CQjki9lTQiJz9fCfKty)
		sq_moveWithParent(obj, CQlmWc41vcEu6dLgyPg)
CQlmWc41vcEu6dLgyPg = sq_SetEnumDrawLayer(CQlmWc41vcEu6dLgyPg, CQR5JVsPnL3HfbG9YWX)
sq_SetCurrentDirection(CQlmWc41vcEu6dLgyPg, CQHU1XIaVhlqhEVjF)
CQlmWc41vcEu6dLgyPg.setCurrentPos(CQiXmRmePkiITXF5,CQ1A2UR75EdtRoDRac,CQUuUaVZiJPn88D8PA73)
sq_AddObject(obj, CQlmWc41vcEu6dLgyPg, OBJECTTYPE_DRAWONLY, false)
return CQlmWc41vcEu6dLgyPg
}

function sq_GetDistenceFrom3D(obj,CQdnEGyzUvF7cIBAeVO)
{
	if (!obj || !CQdnEGyzUvF7cIBAeVO) return -1
local CQbjj4x6VyYBknVsAY = obj.getXPos()
local CQF5Hz5IlVCHYCCFGAfh = obj.getYPos()
local CQgXUWHQpxwsTqCPL = obj.getZPos()
local CQoAMDukdO3WRdXJVtp = CQdnEGyzUvF7cIBAeVO.getXPos()
local CQ2iu2dKeXin7s6D = CQdnEGyzUvF7cIBAeVO.getYPos()
local CQmmMkXEJlfkgg5ZTW = CQdnEGyzUvF7cIBAeVO.getZPos()
local CQJTuesUvaP78X4HcVpJ = sqrt((CQbjj4x6VyYBknVsAY - CQoAMDukdO3WRdXJVtp)*(CQbjj4x6VyYBknVsAY - CQoAMDukdO3WRdXJVtp) + (CQF5Hz5IlVCHYCCFGAfh - CQ2iu2dKeXin7s6D)*(CQF5Hz5IlVCHYCCFGAfh - CQ2iu2dKeXin7s6D) + (CQgXUWHQpxwsTqCPL - CQmmMkXEJlfkgg5ZTW)*(CQgXUWHQpxwsTqCPL - CQmmMkXEJlfkgg5ZTW))
return CQJTuesUvaP78X4HcVpJ
}

function sq_GetDistenceFrom3D_Pos(obj,CQaVANRGjkJH9V3LEA6,CQ5DchVnypns4E2M,CQwoCqrRX1NtNf2CFt,CQZqrITNmhWn5I1KKVlE,CQzlCV2yDi6kMhMNC)
{
	local CQO8efDY8NEzXCMXfAA = sqrt((obj - CQwoCqrRX1NtNf2CFt)*(obj - CQwoCqrRX1NtNf2CFt) + (CQaVANRGjkJH9V3LEA6 - CQZqrITNmhWn5I1KKVlE)*(CQaVANRGjkJH9V3LEA6 - CQZqrITNmhWn5I1KKVlE)/4 + (CQ5DchVnypns4E2M - CQzlCV2yDi6kMhMNC)*(CQ5DchVnypns4E2M - CQzlCV2yDi6kMhMNC))
return CQO8efDY8NEzXCMXfAA
}

function sq_GetDistenceFrom2D_Pos(obj,CQbmWhiPLkewynFyB,CQVGTZLrrVrLKs94b9CT,CQYEK9pzKx5PBR8Mp)
{
	local CQSemvbXgOEuLO77IVb = sqrt((obj - CQVGTZLrrVrLKs94b9CT)*(obj - CQVGTZLrrVrLKs94b9CT)+(CQbmWhiPLkewynFyB - CQYEK9pzKx5PBR8Mp)*(CQbmWhiPLkewynFyB - CQYEK9pzKx5PBR8Mp)/4)
return CQSemvbXgOEuLO77IVb
}

function getFormaidableTarget(obj, CQnfmKZQ5lSzOV6dHAJV)
{
	if(!obj) return null
local CQG126E5naxdGQ565 = obj.getObjectManager()
if (CQG126E5naxdGQ565 == null)
		return null
local CQhJichJC4L1Pf5gdtz = null
for(local CQpsRuNpTkqLEI49 = 0; CQpsRuNpTkqLEI49 < CQG126E5naxdGQ565.getCollisionObjectNumber(); CQpsRuNpTkqLEI49+=1)
	{
		local CQ3rDGPjop1PAh45lY = CQG126E5naxdGQ565.getCollisionObject(CQpsRuNpTkqLEI49)
if(CQ3rDGPjop1PAh45lY && obj.isEnemy(CQ3rDGPjop1PAh45lY) && CQ3rDGPjop1PAh45lY.isInDamagableState(obj) && CQ3rDGPjop1PAh45lY.isObjectType(OBJECTTYPE_ACTIVE))
		{
			local CQqYv4w191yuaX3RWAwy = sq_GetCNRDObjectToActiveObject(CQ3rDGPjop1PAh45lY)
if(!CQqYv4w191yuaX3RWAwy.isDead() && sq_GetDistanceObject(obj, CQqYv4w191yuaX3RWAwy, true) <= CQnfmKZQ5lSzOV6dHAJV)
			{
				if(CQqYv4w191yuaX3RWAwy.isBoss())
					return CQqYv4w191yuaX3RWAwy
else
				{
					if(sq_IsHellMonster(CQqYv4w191yuaX3RWAwy))
						return CQqYv4w191yuaX3RWAwy
else
					{
						if(sq_IsNamed(CQqYv4w191yuaX3RWAwy))
							return CQqYv4w191yuaX3RWAwy
else
							CQhJichJC4L1Pf5gdtz = CQqYv4w191yuaX3RWAwy
}
				}
			}
		}
	}
	return CQhJichJC4L1Pf5gdtz
}

function createPooledObjEff(obj, AniPath,XPos,YPos,ZPos,LayerType,Direction)
{
	if(!obj) return null
local AniObj = sq_CreateAnimation("", AniPath)
local AniPooledObj = sq_CreatePooledObject(AniObj, true)
sq_SetCurrentDirection(AniPooledObj, Direction)
AniPooledObj.setCurrentPos(XPos, YPos, ZPos)
AniPooledObj = sq_SetEnumDrawLayer(AniPooledObj, LayerType)
sq_AddObject(obj, AniPooledObj, OBJECTTYPE_DRAWONLY, false)
return AniPooledObj
}

function playMoveSound_ATSwordman(obj)
{
	if(!obj)
		return;
	obj.sq_PlayMoveSound();
}

function procDash_ATSwordman(obj)
{
	if(!obj)
		return;
		
	if(obj.sq_GetState()!=14)
		return;
		
	local ani = sq_GetCurrentAnimation(obj);
	
	if(!ani)
		return;
		
	local isFlag = obj.sq_IsKeyFrameFlag(ani, 1);

	if (obj.sq_IsKeyFrameFlag(ani, 1)||obj.sq_IsKeyFrameFlag(ani, 2))
	{
		local stage = sq_GetGlobaludpModuleStage();
		if(!stage)
			return;
			
		local dungeon = sq_GetDungeonByStage(stage);
			
		if(!dungeon)
			return;
				
		local dungeonIndex = sq_GetDuegonIndex(dungeon);			
		local mapIndex = sq_GetMapIndex(stage);

			
		if (dungeonIndex == 40 || mapIndex == 50019)
		{
			obj.sq_PlaySound("R_RUN_SNOW");
		}
		else
		{
			local weight = sq_GetObjectWeight(obj);
			if (sq_GetShadowTypeByAnimation() != 0 )
			{
				obj.sq_PlaySound("R_RUN_FLOOR");
				obj.sq_ClearKeyFrameFlag(ani);
			}
			else if (weight < LIGHT_OBJECT_MAX_WEIGHT)
			{
				obj.sq_PlaySound("RUN_STONE");
			}
			else if (weight < MIDDLE_OBJECT_MAX_WEIGHT)
			{
				obj.sq_PlaySound("RUN_SOIL");
			}
			else
			{
				obj.sq_PlaySound("RUN_GRASS");
			}
		}
	}

	obj.sq_ClearKeyFrameFlag(ani);

}


function playSoundForAtswordmanAttack(obj)
{	
	if(!obj)
		return;
		
	local weaponType = obj.getWeaponSubType();
	local soundName = "R_MINERALSWDA_HIT";
	if(weaponType == 5)
		soundName = "R_BEAMSWDA_HIT";
	obj.sq_PlaySound(soundName);
}


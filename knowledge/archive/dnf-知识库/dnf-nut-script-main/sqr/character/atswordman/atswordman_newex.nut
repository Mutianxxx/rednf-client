
function getATSwordmanBonus(CQEOWAolVCyVjHyvF,CQ4t8MR5l98FdYyQ342,CQlbIhVKGrsEk4tn)
{
if(!CQEOWAolVCyVjHyvF) return;
local CQIhlQIQdZkrfuWrR3wL = CQ4t8MR5l98FdYyQ342;

if(sq_getGrowType(CQEOWAolVCyVjHyvF) == 1)
{
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Shortswordmastery(CQEOWAolVCyVjHyvF);
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Blademastery(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn);
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Heavyswordmastery(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn);
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Bluntmastery(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn);
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Bladesoul(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn);
}
else if(sq_getGrowType(CQEOWAolVCyVjHyvF) == 2)
{
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Threeflower(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Ecstasy(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Budclimb(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
}
else if(sq_getGrowType(CQEOWAolVCyVjHyvF) == 3)
{
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Calldaimus(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Atfrenzy(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_ATGreed(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Devilswordtech(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
}
else if(sq_getGrowType(CQEOWAolVCyVjHyvF) == 4)
{
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + getDamageRate_AtSwordmanUsir(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)/100.0
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + getDamageRate_AtSwordmanEvolve(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)/100.0
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + getDamageRate_AtSwordmanCongest(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)/100.0
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + getDamageRate_AtSwordmanVespers(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)/100.0
}
else if(sq_getGrowType(CQEOWAolVCyVjHyvF) == 0)
{
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Trace(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_License(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
CQIhlQIQdZkrfuWrR3wL = CQIhlQIQdZkrfuWrR3wL + ATSwordman_AddBonus_Infamous(CQEOWAolVCyVjHyvF,CQlbIhVKGrsEk4tn)
}
return CQIhlQIQdZkrfuWrR3wL
}

function ATSwordman_AddBonus_Shortswordmastery(CQbHxYH6MIKSCKKWhS)
{
	local CQFaXiuLr6mo2bJQldUm = sq_GetSkillLevel(CQbHxYH6MIKSCKKWhS, 4)
if(CQFaXiuLr6mo2bJQldUm > 0 && CQbHxYH6MIKSCKKWhS.getWeaponSubType() == 0 && CQbHxYH6MIKSCKKWhS.getVar("ChangeswordCurId").getInt(0) > 0)
	{
		local CQgeeHcQKlMQVXJuW = sq_GetLevelData(CQbHxYH6MIKSCKKWhS,4, 5, CQFaXiuLr6mo2bJQldUm)/1000.0
return CQgeeHcQKlMQVXJuW
}
	return 0.0
}
function ATSwordman_AddBonus_Blademastery(CQoc656kbatrKoHriBL,CQ2fexJ3P37vB9Gp)
{
	local CQm15tip5mahLaGyAS = 0.0
local CQJJaFRUipj6FYFsMY4h = sq_GetSkillLevel(CQoc656kbatrKoHriBL, 11)
local CQksk2VgV1FVZLDo4 = sq_GetLevelData(CQoc656kbatrKoHriBL,11, 5, CQJJaFRUipj6FYFsMY4h)/100.0
local CQarJTIGlbWFGnDO8dr = CQoc656kbatrKoHriBL.getVar("Blademastery_Drawsword").getInt(0)
if(CQarJTIGlbWFGnDO8dr > 0)
	{
		CQm15tip5mahLaGyAS = CQksk2VgV1FVZLDo4
CQoc656kbatrKoHriBL.getVar("Blademastery_Drawsword").setInt(0, 0)
}
	
	switch(CQ2fexJ3P37vB9Gp)
	{
	case 147:
		if(CQJJaFRUipj6FYFsMY4h > 0 && CQoc656kbatrKoHriBL.getWeaponSubType() == 1)
			CQm15tip5mahLaGyAS = sq_GetLevelData(CQoc656kbatrKoHriBL,11, 8, CQJJaFRUipj6FYFsMY4h)/1000.0
break
case 96:
		if(CQJJaFRUipj6FYFsMY4h > 0 && CQoc656kbatrKoHriBL.getWeaponSubType() == 1)
			CQm15tip5mahLaGyAS = sq_GetLevelData(CQoc656kbatrKoHriBL,11, 9, CQJJaFRUipj6FYFsMY4h)/100.0
break
}
	return CQm15tip5mahLaGyAS
}
function ATSwordman_AddBonus_Heavyswordmastery(CQ5YmrquGD6aPCVE,CQwg1AgRdNarEpCSqB)
{
	local CQO3iMBNeYhvAdCIr = 0.0
local CQ8L1jWA1PDjasXGuSm = sq_GetSkillLevel(CQ5YmrquGD6aPCVE, 12)
local CQWOiQlYY8c6ubZA = "character/atswordman/1_swordmaster/heavyswordmastery/ap_heavyswordmasteryex.nut"
local CQVtfO39LxXVIZZsZy = CNSquirrelAppendage.sq_IsAppendAppendage(CQ5YmrquGD6aPCVE, CQWOiQlYY8c6ubZA)
if(CQ8L1jWA1PDjasXGuSm > 0 && CQ5YmrquGD6aPCVE.getWeaponSubType() == 3 && CQVtfO39LxXVIZZsZy)
		CQO3iMBNeYhvAdCIr = sq_GetLevelData(CQ5YmrquGD6aPCVE,12, 12, CQ8L1jWA1PDjasXGuSm)/1000.0
return CQO3iMBNeYhvAdCIr
}
function ATSwordman_AddBonus_Bluntmastery(CQYbSBFXhIQGoULFBBor,CQSnYRyry52aW8KP2)
{
	local CQfjVmxz6QurpEKJ7V5 = 0.0
local CQu5WaZ6ma9vtfJD = sq_GetSkillLevel(CQYbSBFXhIQGoULFBBor, 13)
local CQMX7XEsD3OUQLJZUA = "character/atswordman/1_swordmaster/bluntmastery/ap_bluntmasteryex.nut"
local CQnArdnQzUTTynHHwdT9 = CNSquirrelAppendage.sq_IsAppendAppendage(CQYbSBFXhIQGoULFBBor, CQMX7XEsD3OUQLJZUA)
if(CQu5WaZ6ma9vtfJD > 0 && CQYbSBFXhIQGoULFBBor.getWeaponSubType() == 2 && CQnArdnQzUTTynHHwdT9)
		CQfjVmxz6QurpEKJ7V5 = sq_GetLevelData(CQYbSBFXhIQGoULFBBor,13, 13, CQu5WaZ6ma9vtfJD)/1000.0
return CQfjVmxz6QurpEKJ7V5
}
function ATSwordman_AddBonus_Bladesoul(CQGu7bdkEGH8wCMVt,CQhUIpXJf1bMnqMLoBt)
{
	local CQpklLapebBJe9NM = 0.0
local CQ37K7jjJSrIUaBCVS = sq_GetSkillLevel(CQGu7bdkEGH8wCMVt, 15)
local CQqVqY11vN5ycRB31dPV = sq_GetLevelData(CQGu7bdkEGH8wCMVt,15, 0, CQ37K7jjJSrIUaBCVS)/1000.0
local CQKD3iSFOYpUkZVN5 = "character/atswordman/1_swordmaster/bladesoul/ap_bladesoulbuff.nut"
local CQTopHrn4PRTYUCZxBR = CQGu7bdkEGH8wCMVt.getVar("BladesoulBuffCount").getInt(0)
if(CQ37K7jjJSrIUaBCVS > 0 && CQTopHrn4PRTYUCZxBR > 0)
	{
		CQpklLapebBJe9NM = CQqVqY11vN5ycRB31dPV*CQTopHrn4PRTYUCZxBR
}
	
	return CQpklLapebBJe9NM
}
function ATSwordman_AddBonus_Calldaimus(CQsq35Tfu7S9TVC1,CQ6loz2BCxxMREXVQV)
{
	local CQx8gtiyTILJlfZ4WYvA = 0.0
local CQPBFFYYF5mOgsZMDA7 = sq_GetSkillLevel(CQsq35Tfu7S9TVC1, 148)
if(CQPBFFYYF5mOgsZMDA7 > 0)
		CQx8gtiyTILJlfZ4WYvA = sq_GetLevelData(CQsq35Tfu7S9TVC1,148, 5, CQPBFFYYF5mOgsZMDA7)/1000.0
return CQx8gtiyTILJlfZ4WYvA
}
function ATSwordman_AddBonus_Atfrenzy(CQ9Fb2789Q1y8bL7,CQtpBTKPaayUhXK3Xt)
{
	local CQBEtror138l9m3dNBlj = 0.0
local CQvwBAblcUsx4926j = sq_GetSkillLevel(CQ9Fb2789Q1y8bL7, 150)
local CQDxtMBZKGjfda2gzSA = "character/atswordman/2_demonslayer/atfrenzy/ap_atfrenzy.nut"
local CQRd9hOsg1G35R19 = CNSquirrelAppendage.sq_IsAppendAppendage(CQ9Fb2789Q1y8bL7, CQDxtMBZKGjfda2gzSA)
if(CQRd9hOsg1G35R19)
		CQBEtror138l9m3dNBlj = sq_GetLevelData(CQ9Fb2789Q1y8bL7,150, 9, CQvwBAblcUsx4926j)/1000.0
return CQBEtror138l9m3dNBlj
}
function ATSwordman_AddBonus_ATGreed(CQi1OQQqtbvZMOMkmy,CQ1JzOh45SCA6UMRsdV3)
{
	local CQnsZVNJUdwo2CNz = 0.0
local CQGrwRPqVY4QVqBjHB = sq_GetSkillLevel(CQi1OQQqtbvZMOMkmy, 159)
local CQhY5mzhlPoxKdBfZY8U = "character/atswordman/2_demonslayer/greed/ap_atgreedbuff.nut"
local CQpRQa41p7ffBsVl9 = CNSquirrelAppendage.sq_IsAppendAppendage(CQi1OQQqtbvZMOMkmy, CQhY5mzhlPoxKdBfZY8U)
local CQ324XGodxP3LgChgdu = CQi1OQQqtbvZMOMkmy.getVar("ATGreedbuff").getInt(0)
if(CQGrwRPqVY4QVqBjHB > 0 && CQ324XGodxP3LgChgdu > 0)
		CQnsZVNJUdwo2CNz = sq_GetLevelData(CQi1OQQqtbvZMOMkmy,159, 1, CQGrwRPqVY4QVqBjHB)/1000.0*CQ324XGodxP3LgChgdu
return CQnsZVNJUdwo2CNz
}
function ATSwordman_AddBonus_Devilswordtech(CQfyVbIiOohSb1NwTL5,CQOd6VGNOunhWKALM)
{
	local CQTWHp6DYqUoGB5vivD3 = 0.0
local CQsvnKatIaNQPE5za = sq_GetSkillLevel(CQfyVbIiOohSb1NwTL5, 163)
if(CQsvnKatIaNQPE5za > 0)
		CQTWHp6DYqUoGB5vivD3 = sq_GetLevelData(CQfyVbIiOohSb1NwTL5,163, 9, CQsvnKatIaNQPE5za)/1000.0
return CQTWHp6DYqUoGB5vivD3
}
function getDamageRate_AtSwordmanUsir(CQ6gM7Uc33WxHf4UPYh,CQx3uYfVyU7RAI3YFA)
{
	local CQPLMuCOXFahan3Q3dsO = 0.0
local CQ9ZyHsem1h5SC2n7 = sq_GetSkillLevel(CQ6gM7Uc33WxHf4UPYh, 198)
if(CQ9ZyHsem1h5SC2n7 > 0)
		CQPLMuCOXFahan3Q3dsO = sq_GetLevelData(CQ6gM7Uc33WxHf4UPYh, 198, 3, CQ9ZyHsem1h5SC2n7)
return CQPLMuCOXFahan3Q3dsO/10
}
function getDamageRate_AtSwordmanEvolve(CQtAd5m7DbDVsq2rRB9,CQBuAzRZ8SYFiN1q)
{
	local CQvUctDwE9XErsMbeS = 0.0
local CQDkCDWTMYQrogMeyddc = sq_GetSkillLevel(CQtAd5m7DbDVsq2rRB9, 65)
if(CQDkCDWTMYQrogMeyddc > 0)
		CQvUctDwE9XErsMbeS = sq_GetLevelData(CQtAd5m7DbDVsq2rRB9, 65, 1, CQDkCDWTMYQrogMeyddc)
return CQvUctDwE9XErsMbeS/10
}

function getDamageRate_AtSwordmanCongest(obj,CQiC6T3EJ7uhqUBtIBo)
{
	local CQ1SeeFmRwd6tV9w = 0.0;
	local CQUi6AthOIOVQQ8i2V = "character/atswordman/4_darktempler/congest/ap_congest.nut";
	local CQHmsM8G45TFbf7W6YF9 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, CQUi6AthOIOVQQ8i2V)
	if(!CQHmsM8G45TFbf7W6YF9)
		return CQ1SeeFmRwd6tV9w;
	local CQjTkhLinqHawI7Ed = sq_GetSkillLevel(obj, 76)
	CQ1SeeFmRwd6tV9w = sq_GetLevelData(obj, 76, 0, CQjTkhLinqHawI7Ed)
	return CQ1SeeFmRwd6tV9w/10;
}

function getDamageRate_AtSwordmanVespers(CQE7JQpbCJnrnh6yndk,CQ4VmObMT3BvxC5s)
{
	local CQQD2VdSoUrjmq5otB = 0.0
local CQLooRXt9F5TYB4PoYqS = sq_GetSkillLevel(CQE7JQpbCJnrnh6yndk, 77)
if(CQLooRXt9F5TYB4PoYqS > 0)
		CQQD2VdSoUrjmq5otB = sq_GetLevelData(CQE7JQpbCJnrnh6yndk, 77, 4, CQLooRXt9F5TYB4PoYqS)
return CQQD2VdSoUrjmq5otB/10
}
function ATSwordman_AddBonus_Threeflower(CQlQ1iwdw1E8Ta3aK,CQIziJjCHbgNvR3iCdX)
{
	local CQCxR6MOYSSJlO2O = 0.0
local CQcdDxAxs9xIgj1E4BYm = sq_GetSkillLevel(CQlQ1iwdw1E8Ta3aK, 104)
if(CQcdDxAxs9xIgj1E4BYm > 0)
		CQCxR6MOYSSJlO2O = sq_GetLevelData(CQlQ1iwdw1E8Ta3aK,104, 0, CQcdDxAxs9xIgj1E4BYm)/1000.0
return CQCxR6MOYSSJlO2O
}
function ATSwordman_AddBonus_Ecstasy(CQAMYye6gYLt8VRSx,CQdHVGkItPqUhQfIbVG)
{
	local CQyaW3HwZ71T9MfG = 0.0
local CQNe8lukUwy84sdArA = sq_GetSkillLevel(CQAMYye6gYLt8VRSx, 106)
if(CQNe8lukUwy84sdArA > 0)
		CQyaW3HwZ71T9MfG = sq_GetLevelData(CQAMYye6gYLt8VRSx,106, 6, CQNe8lukUwy84sdArA)/1000.0
return CQyaW3HwZ71T9MfG
}
function ATSwordman_AddBonus_Budclimb(CQbcWWYKSI8Mdg9KSd14,CQFf7S7E75IJ5P9FH)
{
	local CQg1I1KmpqkIMm8XZBQ = 0.0
local CQoJljo2NHGy6B7J = sq_GetSkillLevel(CQbcWWYKSI8Mdg9KSd14, 105)
if(CQoJljo2NHGy6B7J > 0)
		CQg1I1KmpqkIMm8XZBQ = sq_GetLevelData(CQbcWWYKSI8Mdg9KSd14,105, 0, CQoJljo2NHGy6B7J)/1000.0
return CQg1I1KmpqkIMm8XZBQ
}

function StartDungeon_AtSwordmanAddEvolve(CQ1ca8M5Dvu4T8GDi)
{
	if(sq_GetSkillLevel(CQ1ca8M5Dvu4T8GDi, 65)<1)	return
CQ1ca8M5Dvu4T8GDi.sq_AddSkillLoad(65, 60, 0, 200)
return
}
function DungeonStart_ATSwordman_Drawsword(CQjfjYAK8y9XREFO)
{
	local CQE1HieEEVOBlYDECY = CQjfjYAK8y9XREFO.sq_GetSkillLoad(17)
if(CQE1HieEEVOBlYDECY)
		CQjfjYAK8y9XREFO.sq_RemoveSkillLoad(17)
return
}
function DungeonStart_ATSwordman_Magicswordshoot(CQ4JUJ5jMxTGgLDSMVIr)
{
	local CQQs15H2cOHa8nSI4 = CQ4JUJ5jMxTGgLDSMVIr.sq_GetSkillLoad(138)
if(CQQs15H2cOHa8nSI4)
	{
		CQ4JUJ5jMxTGgLDSMVIr.sq_RemoveSkillLoad(138)
if(sq_GetSkillLevel(CQ4JUJ5jMxTGgLDSMVIr, 138) > 0)
			CQ4JUJ5jMxTGgLDSMVIr.sq_AddSkillLoad(138, 101, 0, sq_GetIntData(CQ4JUJ5jMxTGgLDSMVIr,138, 9))
}
	
	return
}
function StartDungeon_AtSwordmanDualweapon(CQLruxupKXbWhCAG8Ad)
{
	if(sq_GetSkillLevel(CQLruxupKXbWhCAG8Ad, 202)<1)	return
local CQlYMyYnRlBb9oCA = "character/atswordman/2_vegabond/dualweapon/ap_dualweapon5.nut"
local CQIRuF7RWarj49XKmt = CNSquirrelAppendage.sq_AppendAppendage(CQLruxupKXbWhCAG8Ad, CQLruxupKXbWhCAG8Ad, -1, false, CQlYMyYnRlBb9oCA, false)
if (CQIRuF7RWarj49XKmt != null)
	{
		CQIRuF7RWarj49XKmt.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(CQLruxupKXbWhCAG8Ad), 202, sq_GetSkillLevel(CQLruxupKXbWhCAG8Ad, 202))
CNSquirrelAppendage.sq_Append(CQIRuF7RWarj49XKmt, CQLruxupKXbWhCAG8Ad, CQLruxupKXbWhCAG8Ad, true)
}
	return
}
function DungeonStart_ATSwordman_Ecstasy(CQ72f3KF4457daXFrBfx)
{
	local CQrKSTmynkpB5vZXu = CQ72f3KF4457daXFrBfx.sq_GetSkillLoad(106)
local CQCOcrRYCpRGMZLJHSp = sq_GetSkillLevel(CQ72f3KF4457daXFrBfx, 106)
if(CQrKSTmynkpB5vZXu)
	{
		CQ72f3KF4457daXFrBfx.sq_RemoveSkillLoad(106)
if(CQCOcrRYCpRGMZLJHSp > 0)
			CQ72f3KF4457daXFrBfx.sq_AddSkillLoad(106, 59, 1, sq_GetLevelData(CQ72f3KF4457daXFrBfx,106, 0, CQCOcrRYCpRGMZLJHSp))
}else
	{
		if(CQCOcrRYCpRGMZLJHSp > 0)
			CQ72f3KF4457daXFrBfx.sq_AddSkillLoad(106, 59, 1, sq_GetLevelData(CQ72f3KF4457daXFrBfx,106, 0, CQCOcrRYCpRGMZLJHSp))
}
	
	return
}
function AtSwordmanAddEvolve(CQctCSVBT1SsXULB)
{
	local  CQAbrMIAonxW18KZBy = CQctCSVBT1SsXULB.sq_GetSkillLoad(65)
if(!CQAbrMIAonxW18KZBy) return
local CQdn7jqr9iLbCEJ12BGV = CQctCSVBT1SsXULB.sq_GetLevelData(65, 0, sq_GetSkillLevel(CQctCSVBT1SsXULB, 65))
local CQyjrwg8wNmkJfJVl = CQctCSVBT1SsXULB.sq_GetLevelData(65, 2, sq_GetSkillLevel(CQctCSVBT1SsXULB, 65))
local CQN56ODXHv17BKH4YVT = sq_getRandom(0, 99)
if(CQN56ODXHv17BKH4YVT > CQyjrwg8wNmkJfJVl)
		return
local CQbXsBtsYyyBLbGM = CQAbrMIAonxW18KZBy.getRemainLoadNumber()
if(CQbXsBtsYyyBLbGM+1 <= CQdn7jqr9iLbCEJ12BGV)
		CQAbrMIAonxW18KZBy.increaseLoadCount(1)
return
}
function AtSwordmanDecreaseEvolve(CQFATRzlIV8GFXGCwA)
{
	local  CQguKm452xsKZmF2PdqA = CQFATRzlIV8GFXGCwA.sq_GetSkillLoad(65)
if(!CQguKm452xsKZmF2PdqA) return
local CQoUqsGatOkOG9BBF = CQguKm452xsKZmF2PdqA.getRemainLoadNumber()
if(CQoUqsGatOkOG9BBF-1 >= 0)
		CQguKm452xsKZmF2PdqA.decreaseLoadCount(1)
return
}
function BodyMagicSword(CQKRBzkowh8qum28i, CQT2WW1n1iIzsB2jaPV)
{
	local CQsKVDuRYNkdiw1f = [
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashfire.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashice.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashdark.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashlight.nut"
	               ]
local CQ6IW1cDIYGgrRflMW = [
	                       ["_fire_x.ani","_fire_a.ani","_fire_b.ani"],
	                       ["_ice_x.ani","_ice_a.ani","_ice_b.ani"],
	                       ["_dark_b1.ani","_dark_a.ani","_dark_a2.ani","_dark_b.ani","_dark_b2.ani"],
	                       ["_light_x.ani","_light_a.ani","_light_b.ani"]
	                   ]
local CQeW8k6yhyv4oOfh4V9v = 5
foreach(key, path in CQsKVDuRYNkdiw1f)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQKRBzkowh8qum28i, path))
		{
			CQeW8k6yhyv4oOfh4V9v = key 
}
	}
	if(CQeW8k6yhyv4oOfh4V9v == 5)
		return
local CQXvOeJYyVCXWjdc8 = []
for(local CQxnlPiVXxeDqV9kRAi = 0; CQxnlPiVXxeDqV9kRAi < CQ6IW1cDIYGgrRflMW[CQeW8k6yhyv4oOfh4V9v].len(); ++CQxnlPiVXxeDqV9kRAi)
	{
		CQXvOeJYyVCXWjdc8.push("effect/animation/atchangeswordweapon/" + CQT2WW1n1iIzsB2jaPV + CQ6IW1cDIYGgrRflMW[CQeW8k6yhyv4oOfh4V9v][CQxnlPiVXxeDqV9kRAi])
}
	
	local CQOjLNYPUI4ptQ9v = -1
if(CQKRBzkowh8qum28i.sq_GetState() == 96)
		CQOjLNYPUI4ptQ9v = 1
foreach(key,path in CQXvOeJYyVCXWjdc8)
	{
		local CQ85QhCrSXowQN8ze = sq_CreateAnimation("",path)
CQKRBzkowh8qum28i.sq_AddStateLayerAnimation(CQOjLNYPUI4ptQ9v,CQKRBzkowh8qum28i.sq_CreateCNRDAnimation(path), 0, 0)
}
}
function Changesword_RemoveAppebd(CQWX4qs7llfYbs7UuVD)
{
	local CQVAQIqZpaAgzg7Y = [
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashfire.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashice.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashdark.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashlight.nut"
	               ]
foreach(path in CQVAQIqZpaAgzg7Y)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQWX4qs7llfYbs7UuVD, path))
			CNSquirrelAppendage.sq_RemoveAppendage(CQWX4qs7llfYbs7UuVD, path)
}
	CQWX4qs7llfYbs7UuVD.getVar("ChangeswordCurId").setInt(0, 0)
}
function Changesword_ChangeAppebd(CQYu3CgsN3z4nP6QZC,CQSUpfBlekKCxm5nBcFt)
{
	local CQMkhUO4JpUDjB5c2Pr = [
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashfire.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashice.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashdark.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashlight.nut"
	               ]
foreach(path in CQMkhUO4JpUDjB5c2Pr)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQYu3CgsN3z4nP6QZC, path))
		{
			if(GetMagicSwordAppIndex(CQYu3CgsN3z4nP6QZC) != CQSUpfBlekKCxm5nBcFt)
				CQYu3CgsN3z4nP6QZC.getVar("ChangeswordCurId").setInt(0, GetMagicSwordAppIndex(CQYu3CgsN3z4nP6QZC))
CNSquirrelAppendage.sq_RemoveAppendage(CQYu3CgsN3z4nP6QZC, path)
}
	}
	local CQn6GElaR1Mpcw4q = CNSquirrelAppendage.sq_AppendAppendage(CQYu3CgsN3z4nP6QZC, CQYu3CgsN3z4nP6QZC, -1, false, CQMkhUO4JpUDjB5c2Pr[CQSUpfBlekKCxm5nBcFt-1], false)
if (CQn6GElaR1Mpcw4q != null)
	{
		CQn6GElaR1Mpcw4q.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(CQYu3CgsN3z4nP6QZC), 96, sq_GetSkillLevel(CQYu3CgsN3z4nP6QZC, 96))
CQn6GElaR1Mpcw4q.setEnableIsBuff(true)
CNSquirrelAppendage.sq_Append(CQn6GElaR1Mpcw4q, CQYu3CgsN3z4nP6QZC, CQYu3CgsN3z4nP6QZC, true)
CQn6GElaR1Mpcw4q.setBuffIconImage(58)
}
}
function BodyCalldaimus(CQGCbZ3qObtekRjbYW, CQhSNxFh4i7YRIheUVO3)
{
	local CQpiyttHnNaglhgmw = [
		"effect/animation/atcalldaimusweapon/" + CQhSNxFh4i7YRIheUVO3 + "_a.ani",
		"effect/animation/atcalldaimusweapon/" + CQhSNxFh4i7YRIheUVO3 + "_b.ani",
		"effect/animation/atcalldaimusweapon/" + CQhSNxFh4i7YRIheUVO3 + "_x.ani"
	]
foreach(key ,alspath in CQpiyttHnNaglhgmw)
	{
		local CQ3mNFzoXYh4gAgttAd = sq_CreateAnimation("",alspath)
CQGCbZ3qObtekRjbYW.sq_AddStateLayerAnimation(-1,CQGCbZ3qObtekRjbYW.sq_CreateCNRDAnimation(alspath), 0, 0)
}
	
}
function MagicSword_IsAppebd(CQqTy35bkAF78qRw)
{
	local CQK89TEMDVYBhNfiKt = [
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashfire.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashice.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashdark.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashlight.nut"
	               ]
foreach(path in CQK89TEMDVYBhNfiKt)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQqTy35bkAF78qRw, path))
			return true
}
	
	return false
}
function GetMagicSwordAppIndex(CQTBPrnD8xXG9efWVVYJ)
{
	local CQsFxAdtQIQs4gdE1 = [
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashfire.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashice.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashdark.nut",
	                   "character/atswordman/1_swordmaster/changesword/ap_chainslashlight.nut"
	               ]
	foreach(keu ,path in CQsFxAdtQIQs4gdE1)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQTBPrnD8xXG9efWVVYJ, path))
			return keu + 1
	}
	
	return 0;
}

function drawChangeswordCommon(CQI7emJFfFDFUbrnEN)
{
	local CQCJhJD8gIUF7ZUJm = CQI7emJFfFDFUbrnEN.getVar("ChangeswordCurId").getInt(0)
local CQI7emJFfFDFUbrnEN = sq_GetCNRDObjectToSQRCharacter(CQI7emJFfFDFUbrnEN)
if(CQCJhJD8gIUF7ZUJm == 0 || CQI7emJFfFDFUbrnEN.getWeaponSubType() != 0 || sq_GetSkillLevel(CQI7emJFfFDFUbrnEN, 4) < 1)
		return
local CQQKpdIrxvMET3q8 = [
		"passiveobject/changqing_atswordman/animation/atelementalsword/fire/fireswordloop_01.ani",
		"passiveobject/changqing_atswordman/animation/atelementalsword/ice/iceswordloop_01.ani",
		"passiveobject/changqing_atswordman/animation/atelementalsword/dark/darkswordloop_01.ani",
		"passiveobject/changqing_atswordman/animation/atelementalsword/light/lightswordloop_01.ani"
	]
local CQ2jvHBzDjM3txoo = ["ChangeswordFire","ChangeswordIce","ChangeswordDark","ChangeswordLight"]
local CQm5B5OXzmyZQJDPEc = 1
if(CQI7emJFfFDFUbrnEN.getDirection() == 1)
		CQm5B5OXzmyZQJDPEc = -1
local CQJXtxQsEG8AbvSaZPhT = sq_GetWidthObject(CQI7emJFfFDFUbrnEN)
local CQkAVt4lfgsow5SDN = sq_GetHeightObject(CQI7emJFfFDFUbrnEN)
local CQauWFG5rujQniAO3Ws = sq_GetScreenXPos(CQI7emJFfFDFUbrnEN) + CQm5B5OXzmyZQJDPEc*50
local CQ5U82yKKDFxx8PH = sq_GetScreenYPos(CQI7emJFfFDFUbrnEN) - 50
local CQzkOTxqbdvRjEPSYc9V = CQI7emJFfFDFUbrnEN.getVar()
local CQO6zr5jPtC3ccOsU = CQzkOTxqbdvRjEPSYc9V.GetAnimationMap(CQ2jvHBzDjM3txoo[CQCJhJD8gIUF7ZUJm - 1], CQQKpdIrxvMET3q8[CQCJhJD8gIUF7ZUJm - 1])
sq_AnimationProc(CQO6zr5jPtC3ccOsU)
sq_drawCurrentFrame(CQO6zr5jPtC3ccOsU, CQauWFG5rujQniAO3Ws,CQ5U82yKKDFxx8PH, false)
return
}
function MagicSword_BasiconAttack(CQ8VLAH25Aw5kKIFw9i, CQWDQMnou83VfbIP, CQVo4jdnCroFT6sJpV, CQYqQQXRqZfERoaDLWFy)
{
	if(!CQ8VLAH25Aw5kKIFw9i) return false
local CQSl4OaDF6Pr79aZV = GetMagicSwordAppIndex(CQ8VLAH25Aw5kKIFw9i)
if(CQSl4OaDF6Pr79aZV == 0)
		return
local CQf8pBmy9QlvgJEH1ck = [0,1,3,5,8]
local CQuBhRRYaKKh8vGV = sq_GetLevelData(CQ8VLAH25Aw5kKIFw9i,96, CQf8pBmy9QlvgJEH1ck[CQSl4OaDF6Pr79aZV], sq_GetSkillLevel(CQ8VLAH25Aw5kKIFw9i, 96))
local CQMNGmSB1jU64LGLx9 = sq_getRandom(0, 99)
if(CQMNGmSB1jU64LGLx9 > CQuBhRRYaKKh8vGV)
		return
local CQnGnarPYmNVduFMnWmv = [0,2,4,6,9]
local CQGENXTrLGWF57FCQ = CQ8VLAH25Aw5kKIFw9i.sq_GetBonusRateWithPassive(96, -1, CQnGnarPYmNVduFMnWmv[CQSl4OaDF6Pr79aZV], getATSwordmanBonus(CQ8VLAH25Aw5kKIFw9i,1.0,96))
local CQhwyd28hg6EMpD3WcZ = sq_GetLevelData(CQ8VLAH25Aw5kKIFw9i,96, 10, sq_GetSkillLevel(CQ8VLAH25Aw5kKIFw9i, 96))
local CQpxNbDZyuarXcSN = CQWDQMnou83VfbIP.getZPos()+CQWDQMnou83VfbIP.getObjectHeight()/2
local CQ3dypWe6Dhv1KSXJ9 = sq_GetIntData(CQ8VLAH25Aw5kKIFw9i,96, 1);	
	local CQqMdL7lUdDhCbA2Xt6M = sq_GetIntData(CQ8VLAH25Aw5kKIFw9i,96, 2)
local CQKJP7L4Vtc6JXPBM = CQWDQMnou83VfbIP.getVar("changeswordCount").getInt(0)
local CQTsxYpalCXVVoP5jWW = sq_GetObjectId(CQWDQMnou83VfbIP)
if(CQSl4OaDF6Pr79aZV == 4)
		CQpxNbDZyuarXcSN = 0
local CQarXubqp8QNK8O1zCTt = CQWDQMnou83VfbIP.getXPos(); 
	local CQZYeH9hde2JDEI8v = sq_GetCenterZPos(CQVo4jdnCroFT6sJpV)
local CQzRX5ZHeZuILYL3 =
	{
		[1] = ["passiveobject/changqing_atswordman/animation/atelementaleffect/fire_fire_dodge.ani",CQZYeH9hde2JDEI8v],
		[2] = ["passiveobject/changqing_atswordman/animation/atelementaleffect/ice_ice_dodge.ani",CQZYeH9hde2JDEI8v],
		[4] = ["passiveobject/changqing_atswordman/animation/atelementaleffect/thunder_dodge.ani",CQWDQMnou83VfbIP.getZPos()]
	}
	
	if(CQzRX5ZHeZuILYL3.rawin(CQSl4OaDF6Pr79aZV))
	{
		local CQO2wzQoJT9tFLKds9 = CQ8VLAH25Aw5kKIFw9i.getMyPassiveObjectCount(2438300)
if(CQO2wzQoJT9tFLKds9 > 0)
		{
			local CQ8K5thnvQOUOnJ6SWR3 = CQ8VLAH25Aw5kKIFw9i.getMyPassiveObject(2438300,0)
if(CQ8K5thnvQOUOnJ6SWR3)
			{
				local CQWIaFNMOJTTG7JgH = CQWDQMnou83VfbIP.getZPos() + CQWDQMnou83VfbIP.getObjectHeight()/2
if(CQ8VLAH25Aw5kKIFw9i.isMyControlObject())
				{
					local CQVWk2PDjjH8PpH9ZYE = sq_GetCurrentAttackInfo(CQ8K5thnvQOUOnJ6SWR3)
					CQVWk2PDjjH8PpH9ZYE.setElement(CQSl4OaDF6Pr79aZV - 1)
					sq_SetCurrentAttackBonusRate(CQVWk2PDjjH8PpH9ZYE, CQGENXTrLGWF57FCQ)
					sq_SendHitObjectPacketWithNoStuck(CQ8K5thnvQOUOnJ6SWR3,CQWDQMnou83VfbIP,0,0,CQWIaFNMOJTTG7JgH)
					CQ8VLAH25Aw5kKIFw9i.applyBasicAttackUp(CQVWk2PDjjH8PpH9ZYE,8)
				}
				DarktemplerCreateAniPooledObj(CQ8VLAH25Aw5kKIFw9i,CQzRX5ZHeZuILYL3[CQSl4OaDF6Pr79aZV][0],false,true,CQarXubqp8QNK8O1zCTt,CQWDQMnou83VfbIP.getYPos()+1,CQWIaFNMOJTTG7JgH,0.6)
}
		}
	}
	if(CQSl4OaDF6Pr79aZV == 3)
	{
		if(CQKJP7L4Vtc6JXPBM == CQ3dypWe6Dhv1KSXJ9 && CQSl4OaDF6Pr79aZV == 3)
		{
		}
		else
		{
			CQ8VLAH25Aw5kKIFw9i.sq_StartWrite()
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(96)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQSl4OaDF6Pr79aZV)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQGENXTrLGWF57FCQ)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQhwyd28hg6EMpD3WcZ)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQTsxYpalCXVVoP5jWW)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQqMdL7lUdDhCbA2Xt6M)
sq_SendCreatePassiveObjectPacketPos( CQ8VLAH25Aw5kKIFw9i, 24383, 0, CQWDQMnou83VfbIP.getXPos(), CQWDQMnou83VfbIP.getYPos(), CQpxNbDZyuarXcSN)
}
	}
	local CQYvHTwyumbMEdGk = CQ8VLAH25Aw5kKIFw9i.getVar("ChangeswordCurId").getInt(0)
if(CQYvHTwyumbMEdGk == 0)
		return
if(CQ8VLAH25Aw5kKIFw9i.getWeaponSubType() ==0 && sq_GetSkillLevel(CQ8VLAH25Aw5kKIFw9i, 4) > 0)
	{
		CQpxNbDZyuarXcSN = CQWDQMnou83VfbIP.getZPos()+CQWDQMnou83VfbIP.getObjectHeight()/2
local CQSbUrkdXGBJAJGRgd = (sq_GetIntData(CQ8VLAH25Aw5kKIFw9i,4, 0)/100.0*CQGENXTrLGWF57FCQ).tointeger()
if(CQYvHTwyumbMEdGk == 4)
			CQpxNbDZyuarXcSN = 0
if(CQKJP7L4Vtc6JXPBM == CQ3dypWe6Dhv1KSXJ9 && CQYvHTwyumbMEdGk == 3)
			return
if(CQzRX5ZHeZuILYL3.rawin(CQYvHTwyumbMEdGk))
		{
			local CQO2wzQoJT9tFLKds9 = CQ8VLAH25Aw5kKIFw9i.getMyPassiveObjectCount(2438300)
if(CQO2wzQoJT9tFLKds9 > 0)
			{
				local CQ8K5thnvQOUOnJ6SWR3 = CQ8VLAH25Aw5kKIFw9i.getMyPassiveObject(2438300,0)
if(CQ8K5thnvQOUOnJ6SWR3)
				{
					local CQWIaFNMOJTTG7JgH = CQWDQMnou83VfbIP.getZPos() + CQWDQMnou83VfbIP.getObjectHeight()/2
if(CQ8VLAH25Aw5kKIFw9i.isMyControlObject())
					{
						local CQVWk2PDjjH8PpH9ZYE = sq_GetCurrentAttackInfo(CQ8K5thnvQOUOnJ6SWR3)
						CQVWk2PDjjH8PpH9ZYE.setElement(CQYvHTwyumbMEdGk - 1)
						sq_SetCurrentAttackBonusRate(CQVWk2PDjjH8PpH9ZYE, CQSbUrkdXGBJAJGRgd)
						sq_SendHitObjectPacketWithNoStuck(CQ8K5thnvQOUOnJ6SWR3,CQWDQMnou83VfbIP,0,0,CQWIaFNMOJTTG7JgH)
					}
					DarktemplerCreateAniPooledObj(CQ8VLAH25Aw5kKIFw9i,CQzRX5ZHeZuILYL3[CQYvHTwyumbMEdGk][0],false,true,CQarXubqp8QNK8O1zCTt,CQWDQMnou83VfbIP.getYPos()+1,CQWIaFNMOJTTG7JgH,0.6)
}
			}
		}
		if(CQYvHTwyumbMEdGk == 3)
		{
			CQ8VLAH25Aw5kKIFw9i.sq_StartWrite()
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(96)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQYvHTwyumbMEdGk)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQSbUrkdXGBJAJGRgd)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQhwyd28hg6EMpD3WcZ)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQTsxYpalCXVVoP5jWW)
CQ8VLAH25Aw5kKIFw9i.sq_WriteDword(CQqMdL7lUdDhCbA2Xt6M)
sq_SendCreatePassiveObjectPacketPos( CQ8VLAH25Aw5kKIFw9i, 24383, 0, CQWDQMnou83VfbIP.getXPos(), CQWDQMnou83VfbIP.getYPos(), CQpxNbDZyuarXcSN)
}
	}
}
function AddAppend_Dualweapon(CQL53yGHcZzyiVBtL,CQlXpFyUKTKUIEVwVJF)
{
	local CQIAh3xggQmlofCi = [
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon0.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon1.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon2.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon3.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon5.nut"
	]
local CQ7uGl5MPJM9WICWkE = CQIAh3xggQmlofCi[CQlXpFyUKTKUIEVwVJF]
local CQrUbrJu5jtfpnXEc4NP = CNSquirrelAppendage.sq_AppendAppendage(CQL53yGHcZzyiVBtL, CQL53yGHcZzyiVBtL, -1, false, CQ7uGl5MPJM9WICWkE, false)
if(CQrUbrJu5jtfpnXEc4NP != null)
	{
		CQrUbrJu5jtfpnXEc4NP.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(CQL53yGHcZzyiVBtL), 202, sq_GetSkillLevel(CQL53yGHcZzyiVBtL, 202))
CNSquirrelAppendage.sq_Append(CQrUbrJu5jtfpnXEc4NP, CQL53yGHcZzyiVBtL, CQL53yGHcZzyiVBtL, true)
local CQCkFSivUo73tCZun = [59,60,62,61,63]
CQrUbrJu5jtfpnXEc4NP.setBuffIconImage(CQCkFSivUo73tCZun[CQlXpFyUKTKUIEVwVJF])
}
	
	return CQlXpFyUKTKUIEVwVJF
}
function checkAppend_Dualweapon(CQc6bMfdVGsZQqZIEKm)
{
	local CQACNjCATRjAu9Lp = 5
local CQdSywsWouFoea3tDJ = [
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon0.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon1.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon2.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon3.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon5.nut"
	]
foreach( key,path in CQdSywsWouFoea3tDJ)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQc6bMfdVGsZQqZIEKm, path))
			return key
}
	
	return CQACNjCATRjAu9Lp
}
function SetChrAniIndex_Dualweapon(CQyD9Omx9BYQUR3aJjpW,CQNoPBRXwdCxrO2i7)
{
	local CQbqxgVIHWwfmU1Of36 = 10
local CQFlXoIwYC33YV1E = [526,520,517,523,514,0]
return CQFlXoIwYC33YV1E[CQNoPBRXwdCxrO2i7]
}
function SetChrAtkIndex_Dualweapon(CQg8zKT6IziZTQMSzJ,CQoNZ73KhedAvfNItkTd)
{
	local CQ1GwcFEyZPolsNGo = 10
local CQUE5utkXTlQggBAI4 = [146,140,137,143,134,0]
return CQUE5utkXTlQggBAI4[CQoNZ73KhedAvfNItkTd]
}
function Dualweapon_RemoveAppebd(CQEwaGz2mEJxzXBKSqQI)
{
	local CQ4xj44pSJnRhmVF13R = [
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon0.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon1.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon2.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon3.nut",
		"character/atswordman/2_vegabond/dualweapon/ap_dualweapon5.nut"
	]
foreach(path in CQ4xj44pSJnRhmVF13R)
	{
		if(CNSquirrelAppendage.sq_IsAppendAppendage(CQEwaGz2mEJxzXBKSqQI, path))
			CNSquirrelAppendage.sq_RemoveAppendage(CQEwaGz2mEJxzXBKSqQI, path)
}
	CQEwaGz2mEJxzXBKSqQI.getVar("ChangeswordCurId").setInt(0, 0)
}
function MagicswordupOccur(CQar7Iu1MGm5UcaFafFo, CQar7Iu1MGm5U, boundingBox, isStuck)
{
	if(isStuck)
		return
local CQddd3fx59de4dmbdg5sd = GetMagicSwordAppIndex(CQar7Iu1MGm5UcaFafFo)
local MagicLevel = sq_GetSkillLevel(CQar7Iu1MGm5UcaFafFo, 14)
if(MagicLevel < 1)
		return
local CQ5YICdoc1MVcKaXP = 0.0
local CQwRlfXnsbyNmbHJNN5 = 0.0
if(sq_GetSkillLevel(CQar7Iu1MGm5UcaFafFo, 4) && CQar7Iu1MGm5UcaFafFo.getWeaponSubType() == 0)
	{
		CQ5YICdoc1MVcKaXP = sq_GetIntData(CQar7Iu1MGm5UcaFafFo,4, 1)/1000.0
CQwRlfXnsbyNmbHJNN5 = sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,4, 1, sq_GetSkillLevel(CQar7Iu1MGm5UcaFafFo, 4))/100.0
}
	local CQwRlfXnsbyNmb = CQar7Iu1MGm5U.getObjectHeight()
local CQwRlfXnsbyNmbdgw = sq_GetIntData(CQar7Iu1MGm5UcaFafFo,14, 4)
CQwRlfXnsbyNmbdgw = (CQwRlfXnsbyNmbdgw*(1.0 - CQwRlfXnsbyNmbHJNN5)).tointeger()
local CQwRlfXnsdswmbdgw = sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 14, MagicLevel)/10
local CQdsedswmbdgw = sq_getRandom(0, 99)
if(CQdsedswmbdgw > CQwRlfXnsdswmbdgw)
		return
local CQddesswmbdgw = 1
local CQddesswmbdg5sd = 0
if(CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").size_vector() > 0)
		CQddesswmbdg5sd = CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").get_vector(0)
else
		CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").push_vector(0)
local CQddsdfrtwmbdg5sd = CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").get_ct_vector(0)
if(!CQddsdfrtwmbdg5sd)
	{
		CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").clear_ct_vector()
CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").push_ct_vector()
CQddsdfrtwmbdg5sd = CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").get_ct_vector(0)
CQddsdfrtwmbdg5sd.Reset()
CQddsdfrtwmbdg5sd.Start(10000,0)
}
	else
		CQddesswmbdgw = CQddsdfrtwmbdg5sd.Get()
if((CQddesswmbdgw - CQddesswmbdg5sd) < CQwRlfXnsbyNmbdgw)
		return
local CQddsd34dmbdg5sd = sq_GetSkillLevel(CQar7Iu1MGm5UcaFafFo, 138)
local CQddddee24dmbdg5sd = CQar7Iu1MGm5UcaFafFo.sq_GetSkillLoad(138)
local CQdddgt644dmbdg5sd = sq_GetIntData(CQar7Iu1MGm5UcaFafFo,138, 0)
if(CQddddee24dmbdg5sd && MagicLevel > 0)
	{
		local CQddd3fxs644dmbdg5sd = CQddddee24dmbdg5sd.getRemainLoadNumber()
if(CQddd3fxs644dmbdg5sd < CQdddgt644dmbdg5sd && !CQddddee24dmbdg5sd.isCooling())
		{
			CQddddee24dmbdg5sd.increaseLoadCount(1)
CQddddee24dmbdg5sd.setStartCool()
}
	}
	
	CQar7Iu1MGm5UcaFafFo.getVar("MagicswordupOccur").set_vector(0,CQddesswmbdgw)
switch(CQddd3fx59de4dmbdg5sd)
	{
	case 1:
		CQar7Iu1MGm5UcaFafFo.sq_StartWrite()
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(14)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(1)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(CQar7Iu1MGm5UcaFafFo.sq_GetBonusRateWithPassive(14, -1, 5, getATSwordmanBonus(CQar7Iu1MGm5UcaFafFo,1.0+CQ5YICdoc1MVcKaXP,14)))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 7, MagicLevel)/10)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 8, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 9, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 2, MagicLevel))
sq_SendCreatePassiveObjectPacketPos( CQar7Iu1MGm5UcaFafFo, 24383, 0, CQar7Iu1MGm5U.getXPos(), CQar7Iu1MGm5U.getYPos(), CQar7Iu1MGm5U.getZPos()+CQwRlfXnsbyNmb/2)
break
case 2:
		local Xpos = sq_GetDistancePos(CQar7Iu1MGm5U.getXPos(), CQar7Iu1MGm5UcaFafFo.getDirection(), -150)
CQar7Iu1MGm5UcaFafFo.sq_StartWrite()
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(14)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(2)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(CQar7Iu1MGm5UcaFafFo.sq_GetBonusRateWithPassive(14, -1, 1, getATSwordmanBonus(CQar7Iu1MGm5UcaFafFo,1.0+CQ5YICdoc1MVcKaXP,14)))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 4, MagicLevel)/10)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 3, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 2, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetIntData(CQar7Iu1MGm5UcaFafFo,14, 0))
sq_SendCreatePassiveObjectPacketPos( CQar7Iu1MGm5UcaFafFo, 24383, 0, Xpos, CQar7Iu1MGm5U.getYPos(), CQar7Iu1MGm5U.getZPos()+CQwRlfXnsbyNmb)
break
case 3:
		CQar7Iu1MGm5UcaFafFo.sq_StartWrite()
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(14)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(3)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(CQar7Iu1MGm5UcaFafFo.sq_GetBonusRateWithPassive(14, -1, 0, getATSwordmanBonus(CQar7Iu1MGm5UcaFafFo,1.0+CQ5YICdoc1MVcKaXP,14)))
sq_SendCreatePassiveObjectPacketPos( CQar7Iu1MGm5UcaFafFo, 24383, 0, CQar7Iu1MGm5U.getXPos(), CQar7Iu1MGm5U.getYPos()+2, CQar7Iu1MGm5U.getZPos()+CQwRlfXnsbyNmb/2)
break
case 4:
		CQar7Iu1MGm5UcaFafFo.sq_StartWrite()
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(14)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(4)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(CQar7Iu1MGm5UcaFafFo.sq_GetBonusRateWithPassive(14, -1, 10, getATSwordmanBonus(CQar7Iu1MGm5UcaFafFo,1.0+CQ5YICdoc1MVcKaXP,14)))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 13, MagicLevel)/10)
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 11, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_WriteDword(sq_GetLevelData(CQar7Iu1MGm5UcaFafFo,14, 12, MagicLevel))
CQar7Iu1MGm5UcaFafFo.sq_SendCreatePassiveObjectPacket(24383, 0, 20, 0, 70)
break
}
}
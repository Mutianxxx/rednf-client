


 
function setEnableCancelSkill_ATFighter(b5auQt29ZJBGNtERo, WCDjwRh3IWyTM_NtayN5VXM)
{
 if(!b5auQt29ZJBGNtERo)
 return false;
 
 if(!b5auQt29ZJBGNtERo.isMyControlObject())
 return false;
 if(!WCDjwRh3IWyTM_NtayN5VXM)
 return true;
 b5auQt29ZJBGNtERo.setSkillCommandEnable(220, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(221, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(222, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(223, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(224, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(225, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(226, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(227, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(228, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(229, WCDjwRh3IWyTM_NtayN5VXM); 
 b5auQt29ZJBGNtERo.setSkillCommandEnable(230, WCDjwRh3IWyTM_NtayN5VXM); 
 
 return true;
} ;


function onChangeSkillEffect_ATFighter(Lmb1IBm0hXY6DPN, YpaXlNk63NMAawV1szMUwYl, o5VdaHELFpH1U9ZZ)
{
 if(!Lmb1IBm0hXY6DPN) return;
 switch(YpaXlNk63NMAawV1szMUwYl)
 {
 case 50: 
 local vMANHUtMTDpA = o5VdaHELFpH1U9ZZ.readWord(); 
 switch(vMANHUtMTDpA)
 {
 case 1:
 
 if(CNSquirrelAppendage.sq_IsAppendAppendage(Lmb1IBm0hXY6DPN, "character/atfighter/appendage/ap_definitegrab.nut"))
 CNSquirrelAppendage.sq_RemoveAppendage(Lmb1IBm0hXY6DPN, "character/atfighter/appendage/ap_definitegrab.nut");
 local FVKCAd14Dts6N1 = Lmb1IBm0hXY6DPN.sq_GetLevelData(YpaXlNk63NMAawV1szMUwYl, 0, sq_GetSkillLevel(Lmb1IBm0hXY6DPN, YpaXlNk63NMAawV1szMUwYl)); 
 local CdeQ5bSIOksjOgU = CNSquirrelAppendage.sq_AppendAppendage(Lmb1IBm0hXY6DPN, Lmb1IBm0hXY6DPN, YpaXlNk63NMAawV1szMUwYl, false, "character/atfighter/appendage/ap_definitegrab.nut", false);
 CdeQ5bSIOksjOgU.sq_SetValidTime(FVKCAd14Dts6N1); 
 CNSquirrelAppendage.sq_Append(CdeQ5bSIOksjOgU, Lmb1IBm0hXY6DPN, Lmb1IBm0hXY6DPN, false);
 break;
 }
 break;
 }
} ;


function getDamageRate_SpiralGaleForce(obj)
{
	local damageRate = 0.0;
	local skill_level = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
	if(skill_level > 0)
		damageRate = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 8, skill_level)/1000.0;

	return damageRate;
}


function isNengLiangOpen(obj)
{
	return CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/spiralgaleforce/ap_spiralgaleforce.nut");
}

function drawNengLiangUi(obj)
{
	if ( CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/spiralgaleforce/ap_nengliang.nut") )
	{
		local x = 155;
		local y = 500;
		local sq_var = obj.getVar();
		local bottom = sq_var.GetAnimationMap("bottom", "character/fighter/effect/animation/atspiralinhale/spiralinhalebottom.ani");
		local yellow = sq_var.GetAnimationMap("yellow", "character/fighter/effect/animation/atspiralinhale/gaugebaryellow.ani");
		local blue = sq_var.GetAnimationMap("blue", "character/fighter/effect/animation/atspiralinhale/gaugebarblue.ani");
		local white = sq_var.GetAnimationMap("white", "character/fighter/effect/animation/atspiralinhale/gaugebarwhite.ani");
		local line = sq_var.GetAnimationMap("line", "character/fighter/effect/animation/atspiralinhale/spiralinhale_gaugeline.ani");
		local body = sq_var.GetAnimationMap("body", "character/fighter/effect/animation/atspiralinhale/spiralinhale_body.ani");
		local glowblue = sq_var.GetAnimationMap("glowblue", "character/fighter/effect/animation/atspiralinhale/spiralinhale_glowblue.ani");
		local glowyellow = sq_var.GetAnimationMap("glowyellow", "character/fighter/effect/animation/atspiralinhale/spiralinhale_glowyellow.ani");
		local fullgaugeeffect = sq_var.GetAnimationMap("fullgaugeeffect", "character/fighter/effect/animation/atspiralinhale/fullgaugeeffect.ani");
		local spiralinhale_bodyshadow = sq_var.GetAnimationMap("spiralinhale_bodyshadow", "character/fighter/effect/animation/atspiralinhale/spiralinhale_bodyshadow.ani");
		local max = sq_var.GetAnimationMap("max", "character/fighter/effect/animation/atspiralinhale/max.ani");
		
		local gaugeValue = getNengLiangNumber(obj);
		local max_gaugeValue = 1000;
		local rate = gaugeValue.tofloat() / max_gaugeValue.tofloat();
		
		if(gaugeValue < max_gaugeValue)
		{
			sq_AnimationProc(bottom);
			sq_drawCurrentFrame(bottom, x, y, false);
			sq_AnimationProc(yellow);
			yellow.setImageRate(rate, 1.0);
			sq_drawCurrentFrame(yellow, x - 55, y + 5, false);
			sq_AnimationProc(blue);
			blue.setImageRate(rate, 1.0);
			sq_drawCurrentFrame(blue, x - 55, y + 5, false);
			sq_AnimationProc(white);
			white.setImageRate(rate, 1.0);
			sq_drawCurrentFrame(white, x - 55, y + 5, false);
			sq_AnimationProc(line);
			sq_drawCurrentFrame(line, x, y, false);
			sq_AnimationProc(body);
			sq_drawCurrentFrame(body, x, y, false);
			sq_AnimationProc(glowblue);
			sq_drawCurrentFrame(glowblue, x, y, false);
			sq_AnimationProc(glowyellow);
			sq_drawCurrentFrame(glowyellow, x, y, false);
			sq_AnimationProc(fullgaugeeffect);
			sq_drawCurrentFrame(fullgaugeeffect, x, y, false);
			
			
			local ge = gaugeValue % 10;
			local len = (gaugeValue - ge) / 10;
			local shi = len % 10;
			local len1 = gaugeValue - (shi*10 + ge);
			local bai = (len1 / 100) % 10;
			
			local geani = getATFighterNengLiangIndexNum(obj, ge);
			local shiani = getATFighterNengLiangIndexNum(obj, shi);
			local baiani = getATFighterNengLiangIndexNum(obj, bai);
			
			sq_AnimationProc(geani);
			sq_drawCurrentFrame(geani, x - 60, y - 3, false);
			sq_AnimationProc(shiani);
			sq_drawCurrentFrame(shiani, x - 65, y - 3, false);
			sq_AnimationProc(baiani);
			sq_drawCurrentFrame(baiani, x - 70, y - 3, false);
		} else {
			sq_AnimationProc(spiralinhale_bodyshadow);
			sq_drawCurrentFrame(spiralinhale_bodyshadow, x, y, false);
			sq_AnimationProc(fullgaugeeffect);
			sq_drawCurrentFrame(fullgaugeeffect, x, y, false);
			sq_AnimationProc(max);
			sq_drawCurrentFrame(max, x - 70, y - 3, false);
		}
	}
}

function getNengLiangNumber(obj)
{
	local apd = obj.GetSquirrelAppendage("character/atfighter/spiralgaleforce/ap_nengliang.nut");
	return apd.getVar("num").get_vector(0);
}

function setNengLiangNumber(obj,value)
{
	local apd = obj.GetSquirrelAppendage("character/atfighter/spiralgaleforce/ap_nengliang.nut");
	apd.getVar("num").set_vector(0, getNengLiangNumber(obj) + value);
}

function getATFighterNengLiangIndexNum(obj, num)
{
	local numImage = null;
	local sq_var = obj.getVar();
	if (num == 0)
	{
		numImage = sq_var.GetAnimationMap("number0", "character/fighter/effect/animation/atspiralinhale/0.ani");
	}else if (num == 1){
		numImage = sq_var.GetAnimationMap("number1", "character/fighter/effect/animation/atspiralinhale/1.ani");
	}else if (num == 2){
		numImage = sq_var.GetAnimationMap("number2", "character/fighter/effect/animation/atspiralinhale/2.ani");
	}else if (num == 3){
		numImage = sq_var.GetAnimationMap("number3", "character/fighter/effect/animation/atspiralinhale/3.ani");
	}else if (num == 4){
		numImage = sq_var.GetAnimationMap("number4", "character/fighter/effect/animation/atspiralinhale/4.ani");
	}else if (num == 5){
		numImage = sq_var.GetAnimationMap("number5", "character/fighter/effect/animation/atspiralinhale/5.ani");
	}else if (num == 6){
		numImage = sq_var.GetAnimationMap("number6", "character/fighter/effect/animation/atspiralinhale/6.ani");
	}else if (num == 7){
		numImage = sq_var.GetAnimationMap("number7", "character/fighter/effect/animation/atspiralinhale/7.ani");
	}else if (num == 8){
		numImage = sq_var.GetAnimationMap("number8", "character/fighter/effect/animation/atspiralinhale/8.ani");
	}else if (num == 9){
		numImage = sq_var.GetAnimationMap("number9", "character/fighter/effect/animation/atspiralinhale/9.ani");
	}
	return numImage;
}


function useSkill_after_ATFighter(obj, skillIndex, consumeMp, consumeItem, oldSkillMpRate)
{
	if(!obj) return false;

	if(skillIndex == 41)
	{
		local skillLevel = obj.sq_GetSkillLevel(41);
		if(skillLevel > 0)
		{
			local time = sq_GetLevelData(obj, 41, 0, skillLevel);
			local lieyanfenbuzhuijia = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 41, false, "character/atfighter/lieyanfenbu/ap_lieyanfenbuzhuijia.nut", false);
			lieyanfenbuzhuijia.sq_SetValidTime(time);
			CNSquirrelAppendage.sq_Append(lieyanfenbuzhuijia, obj, obj);

			local lieyanfenbutimer = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 41, false, "character/atfighter/lieyanfenbu/ap_lieyanfenbutimer.nut", false);
			lieyanfenbutimer.sq_SetValidTime(time);
			CNSquirrelAppendage.sq_Append(lieyanfenbutimer, obj, obj);
		}
	}
	return true;
}



function onEndState_atfighter_atomiccannon(obj, new_state)
{
	if(!obj || new_state == STATE_ATFIGHTER_ATOMICCANNON) return;
	local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/lieyanfenbu/ap_lieyanfenbuzengshang_2.nut");
	if(isAppend)
	{
		local zengshang_2 = obj.GetSquirrelAppendage("character/atfighter/lieyanfenbu/ap_lieyanfenbuzengshang_2.nut");
		zengshang_2.setValid(false);
	}
}


function setState_ATFighter(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	setState_AllGrowJob(obj, state, datas, isResetTimer);
	setState_SpiralInhale(obj, state, datas, isResetTimer);
}


function drawCustomUI_SpiralInhale_by_ChangQing751675335(obj)
{
local CgLoQUENxRpQ4Eum = sq_GetSkillLevel(obj, 238);
if(CgLoQUENxRpQ4Eum < 1) return;

local CX4iBfmKgsSS3jrbT = "character/fighter/effect/animation/atspiralinhale/spiralinhale_bodyshadow.ani";
local Cf9qKymWHp2qUm = "character/fighter/effect/animation/atspiralinhale/spiralinhale_body.ani";
local CPrRtJhfrqUPrS = "character/fighter/effect/animation/atspiralinhale/spiralinhale_gaugeline.ani";


sq_drawBack_ChangQing751675335(obj , CX4iBfmKgsSS3jrbT , 150 , 474);
sq_drawBack_ChangQing751675335(obj , Cf9qKymWHp2qUm , 150 , 474);
sq_drawBack_ChangQing751675335(obj , CPrRtJhfrqUPrS , 150 , 474);


if(obj.getVar("SpiralInhaleEnergy").size_vector() == 0)
obj.getVar("SpiralInhaleEnergy").push_vector(0);
local C9YDDi1rZ2lEhSiw = obj.getVar("SpiralInhaleEnergy").get_vector(0);
sq_drawPercentLine_ChangQing751675335(obj , C9YDDi1rZ2lEhSiw ,1000 ,150 , 474);

local CtRv2Yo3lu9yA = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, CtRv2Yo3lu9yA))
destroyObjectByVar(obj, "SpiralGaleForcePool");
return;
}

function setState_SpiralInhale(CB2DT7bbw9MwTPE, CvKYeKMPKIKuNPuKb, CDIVAmDkkTZeeO, CRWWMRyipHAU2IoM)
{
local Civ8hBd8HboWP = sq_GetSkillLevel(CB2DT7bbw9MwTPE, 238);
if(Civ8hBd8HboWP < 1) return;

if(CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").size_vector() == 0)
CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").push_vector(0);
local C1gOQOVQgVQqjsa = CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").get_vector(0);

local CU4lIQPGirxvSaDbn = CB2DT7bbw9MwTPE.getCurrentSkillIndex();
local CHZIVhxcF5fQlJ = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
local CjPlRF7sfp3bMHHI = CNSquirrelAppendage.sq_IsAppendAppendage(CB2DT7bbw9MwTPE, CHZIVhxcF5fQlJ);
switch(CvKYeKMPKIKuNPuKb)
{
case 66:
CB2DT7bbw9MwTPE.getVar("SpiralInhaleIs").setBool(0,false);
if(CjPlRF7sfp3bMHHI)
{
if(C1gOQOVQgVQqjsa >= 200)
CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").set_vector(0,C1gOQOVQgVQqjsa - 200);
else
CNSquirrelAppendage.sq_RemoveAppendage(CB2DT7bbw9MwTPE, CHZIVhxcF5fQlJ);
}
break;
case 65:
if(CB2DT7bbw9MwTPE.sq_GetVectorData(CDIVAmDkkTZeeO, 0) == 1)
{
CB2DT7bbw9MwTPE.getVar("SpiralInhaleIs").setBool(0,false);
if(CjPlRF7sfp3bMHHI)
{
if(C1gOQOVQgVQqjsa >= 50)
CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").set_vector(0,C1gOQOVQgVQqjsa - 50);
else
CNSquirrelAppendage.sq_RemoveAppendage(CB2DT7bbw9MwTPE, CHZIVhxcF5fQlJ);
}
}
break;
case 13:
local CEyLUtZ1tRZzr = CB2DT7bbw9MwTPE.getThrowIndex();
switch(CEyLUtZ1tRZzr)
{
case 112:
if(CB2DT7bbw9MwTPE.getThrowState() == 0)
{
CB2DT7bbw9MwTPE.getVar("SpiralInhaleIs").setBool(0,false);
local CHZIVhxcF5fQlJ = "character/atfighter/nenmaster2nd/ap_spiralnen.nut";
local CQj3X4TL9xoxAFGXu = CNSquirrelAppendage.sq_AppendAppendage(CB2DT7bbw9MwTPE, CB2DT7bbw9MwTPE, -1, false, CHZIVhxcF5fQlJ, false);
if (CQj3X4TL9xoxAFGXu != null)
{
CQj3X4TL9xoxAFGXu.sq_SetValidTime(CB2DT7bbw9MwTPE.sq_GetLevelData(112, 1, sq_GetSkillLevel(CB2DT7bbw9MwTPE, 112)));
CQj3X4TL9xoxAFGXu.setEnableIsBuff(true);
CNSquirrelAppendage.sq_Append(CQj3X4TL9xoxAFGXu, CB2DT7bbw9MwTPE, CB2DT7bbw9MwTPE, true);
}
}
break;
case 16:
case 15:
if(CB2DT7bbw9MwTPE.getThrowState() == 0 && CjPlRF7sfp3bMHHI)
{
if(C1gOQOVQgVQqjsa >= 100)
CB2DT7bbw9MwTPE.getVar("SpiralInhaleEnergy").set_vector(0,C1gOQOVQgVQqjsa - 100);
else
CNSquirrelAppendage.sq_RemoveAppendage(CB2DT7bbw9MwTPE, CHZIVhxcF5fQlJ);
}
break;
}
break;
}

}

function sq_draw_ChangQing751675335(CIkp9G4nrLQjTF , C76hbyEAZmxdD , CrCGpdm6lMRkwSF , CCSgKXhowy3f1SXYR)
{
if(!CIkp9G4nrLQjTF) return;
C76hbyEAZmxdD = C76hbyEAZmxdD.tostring();
local CciF7aHBK8Z6WA = "character/fighter/effect/animation/atspiralinhale/numbers/";
local CAmbcUizjsSRjPBs =
{
["0"] = "0.ani",
["1"] = "1.ani",
["2"] = "2.ani",
["3"] = "3.ani",
["4"] = "4.ani",
["5"] = "5.ani",
["6"] = "6.ani",
["7"] = "7.ani",
["8"] = "8.ani",
["9"] = "9.ani"
}

local CdTNufgHpjF7S = 5;
local Cy7yHCMfHFE2lO1 = C76hbyEAZmxdD.len();

for(local CNB94eSrgvr8MLC4b = 0; CNB94eSrgvr8MLC4b < Cy7yHCMfHFE2lO1; ++CNB94eSrgvr8MLC4b)
{
local CvFPzkv2uCv3rL = C76hbyEAZmxdD.slice(CNB94eSrgvr8MLC4b , CNB94eSrgvr8MLC4b + 1);

if(CAmbcUizjsSRjPBs.rawin(CvFPzkv2uCv3rL))
{
local CDpxt1dvNwhB2KN = "SpiralInhaleAniName" + CvFPzkv2uCv3rL;
local CRQPDSCZf364tJ6Tu = CciF7aHBK8Z6WA + CAmbcUizjsSRjPBs[CvFPzkv2uCv3rL];
local Cizx2WWjtoVNkJ = CIkp9G4nrLQjTF.getVar();
local C19ZklxuCfFZDH9u = Cizx2WWjtoVNkJ.GetAnimationMap( CDpxt1dvNwhB2KN , CRQPDSCZf364tJ6Tu );

sq_AnimationProc(C19ZklxuCfFZDH9u);
sq_drawCurrentFrame(C19ZklxuCfFZDH9u , CrCGpdm6lMRkwSF + CNB94eSrgvr8MLC4b * CdTNufgHpjF7S , CCSgKXhowy3f1SXYR , false);
}

}
}

function sq_drawBack_ChangQing751675335(C9sFPNzx4arnnsjQ , CsTCz6Icg2NtmE , CjEaNvwFZKvHWF8Bi , CEajh8TxTUjA4F)
{
local C4eHQLKawN6KADf7 = CsTCz6Icg2NtmE;
local CQcjIpERKWVDT = C9sFPNzx4arnnsjQ.getVar();
local CIfHVgkrj6FIFVhUb = CQcjIpERKWVDT.GetAnimationMap(C4eHQLKawN6KADf7 , CsTCz6Icg2NtmE );

sq_AnimationProc(CIfHVgkrj6FIFVhUb);
sq_drawCurrentFrame(CIfHVgkrj6FIFVhUb , CjEaNvwFZKvHWF8Bi , CEajh8TxTUjA4F , false);
}

function sq_drawPercentLine_ChangQing751675335(C71URN2KpaaFeC , CrKMUPGbHhIO2XTt ,CCIuawUPgDtpt , CcWfZjR5ucUPkZx , CAvS9MNiNXTEDLkVb)
{
local CdgYbyuVfQ8yzL = "character/fighter/effect/animation/atspiralinhale/spiralinhale_caugebarblue.ani";
local Cy3AoxvltgMaGKl5 = "character/fighter/effect/animation/atspiralinhale/spiralinhale_gaugebarwhite.ani";
local CNLcK59GCSJur = "character/fighter/effect/animation/atspiralinhale/spiralinhale_gaugebaryellow.ani";
local CbOC7HAdxxIe3Jc = "character/fighter/effect/animation/atspiralinhale/fullgaugeeffect.ani";
local CFtrcuWsrZyiyHTQu = "character/fighter/effect/animation/atspiralinhale/numbers/none.ani";
local Cgb7uYz2ZqUrTG = "character/fighter/effect/animation/atspiralinhale/numbers/max.ani";
local CohsGCXYT1TmFGxD = "character/fighter/effect/animation/atspiralinhale/chargegaugeeffect.ani";

local C24T4sILay9Yx = C71URN2KpaaFeC.getVar();
if(CrKMUPGbHhIO2XTt == CCIuawUPgDtpt)
{
local CmZKzmlhK9Mq2Bv = C24T4sILay9Yx.GetAnimationMap(Cy3AoxvltgMaGKl5 , Cy3AoxvltgMaGKl5 );
CmZKzmlhK9Mq2Bv.setImageRate(1.0, 0.5);
sq_AnimationProc(CmZKzmlhK9Mq2Bv);
sq_drawCurrentFrame(CmZKzmlhK9Mq2Bv , CcWfZjR5ucUPkZx + 31, CAvS9MNiNXTEDLkVb + 11 , false);
local CJXTWR5yjIJvWBwMi = C24T4sILay9Yx.GetAnimationMap(CNLcK59GCSJur , CNLcK59GCSJur );
CJXTWR5yjIJvWBwMi.setImageRate(1.0, 0.5);
sq_AnimationProc(CJXTWR5yjIJvWBwMi);
sq_drawCurrentFrame(CJXTWR5yjIJvWBwMi , CcWfZjR5ucUPkZx + 31, CAvS9MNiNXTEDLkVb + 11 , false);

local CkSJDVK6okOl4V = C24T4sILay9Yx.GetAnimationMap(Cgb7uYz2ZqUrTG , Cgb7uYz2ZqUrTG );
sq_AnimationProc(CkSJDVK6okOl4V);
sq_drawCurrentFrame(CkSJDVK6okOl4V , CcWfZjR5ucUPkZx - 70, CAvS9MNiNXTEDLkVb-4, false);
}
else
{
if(CrKMUPGbHhIO2XTt < 1)
{
local Caim2IQm1GAbSVWz = C24T4sILay9Yx.GetAnimationMap(CFtrcuWsrZyiyHTQu , CFtrcuWsrZyiyHTQu );
sq_AnimationProc(Caim2IQm1GAbSVWz);
sq_drawCurrentFrame(Caim2IQm1GAbSVWz , CcWfZjR5ucUPkZx - 65, CAvS9MNiNXTEDLkVb-4, false);
}
else
{
local C5m2kTjDgvizl = CrKMUPGbHhIO2XTt/CCIuawUPgDtpt.tofloat();
local CwToe22zuVQhGXu = C24T4sILay9Yx.GetAnimationMap(CdgYbyuVfQ8yzL , CdgYbyuVfQ8yzL );
CwToe22zuVQhGXu.setImageRate(1.0, 0.5);
local CO7gADpEBexxrX = 138*C5m2kTjDgvizl;
setClip(CcWfZjR5ucUPkZx - 55, CAvS9MNiNXTEDLkVb - 4, CcWfZjR5ucUPkZx - 55 + CO7gADpEBexxrX.tointeger(), CAvS9MNiNXTEDLkVb + 2);
sq_AnimationProc(CwToe22zuVQhGXu);
sq_drawCurrentFrame(CwToe22zuVQhGXu , CcWfZjR5ucUPkZx + 31, CAvS9MNiNXTEDLkVb + 11 , false);
releaseClip();

sq_draw_ChangQing751675335(C71URN2KpaaFeC , CrKMUPGbHhIO2XTt , CcWfZjR5ucUPkZx - 70, CAvS9MNiNXTEDLkVb-4);

local C8VDNtnff4fj3ZpS = C24T4sILay9Yx.GetAnimationMap(CohsGCXYT1TmFGxD , CohsGCXYT1TmFGxD );
sq_AnimationProc(C8VDNtnff4fj3ZpS);
sq_drawCurrentFrame(C8VDNtnff4fj3ZpS , CcWfZjR5ucUPkZx - 55 + CO7gADpEBexxrX.tointeger(), CAvS9MNiNXTEDLkVb + 2, false);
}
}


local CWDRhzRrto3dy = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
if(CNSquirrelAppendage.sq_IsAppendAppendage(C71URN2KpaaFeC, CWDRhzRrto3dy))
{
local CVoDq4FKCRZk6Le = C24T4sILay9Yx.GetAnimationMap(CbOC7HAdxxIe3Jc , CbOC7HAdxxIe3Jc );
sq_AnimationProc(CVoDq4FKCRZk6Le);
sq_drawCurrentFrame(CVoDq4FKCRZk6Le , CcWfZjR5ucUPkZx , CAvS9MNiNXTEDLkVb  , false);
}
}

function IsInterval_Default(CYqvIpyvzAARDKo9b, CSlBVbYOrzo7z2,Cf8Wf9B4ZKQ2H2ET)
{
if (!CYqvIpyvzAARDKo9b)
return false;

local CuB8UZPuTmx8W = CYqvIpyvzAARDKo9b.getVar(Cf8Wf9B4ZKQ2H2ET).get_ct_vector(0);

if (!CuB8UZPuTmx8W)
{
CYqvIpyvzAARDKo9b.getVar(Cf8Wf9B4ZKQ2H2ET).clear_ct_vector();
CYqvIpyvzAARDKo9b.getVar(Cf8Wf9B4ZKQ2H2ET).push_ct_vector();
CuB8UZPuTmx8W = CYqvIpyvzAARDKo9b.getVar(Cf8Wf9B4ZKQ2H2ET).get_ct_vector(0);
CuB8UZPuTmx8W.Reset();
CuB8UZPuTmx8W.Start(10000,0);
return true;
}

local CMFOaErCEMf34MI = CuB8UZPuTmx8W.Get();
if(CMFOaErCEMf34MI > CSlBVbYOrzo7z2)
{
CuB8UZPuTmx8W.Reset();
CuB8UZPuTmx8W.Start(10000,0);
return true;
}
return false;
}

function createAnimationPooledForceEx(CnpzZn8qKt3BuMpan, CGQI9NXFj7Z4lN,ChxlbAe9oaANGBsF, CodLoela1joZx, C2fQKk51gFEM2V, Cm1461aYuYeXtVJR ,CJJpcSqKBXvH5)
{
local CkshucjgYwhCiXO = sq_CreateAnimation("",CGQI9NXFj7Z4lN);
CkshucjgYwhCiXO.setLoop(true);
if(CJJpcSqKBXvH5 != false)
{
CkshucjgYwhCiXO.setImageRateFromOriginal(CJJpcSqKBXvH5, CJJpcSqKBXvH5);
CkshucjgYwhCiXO.setAutoLayerWorkAnimationAddSizeRate(CJJpcSqKBXvH5);
}

local CarGG6Htt35JzXHyF = sq_CreatePooledObject(CkshucjgYwhCiXO,true);

CarGG6Htt35JzXHyF.setCurrentPos(CodLoela1joZx,C2fQKk51gFEM2V,Cm1461aYuYeXtVJR);
if(ChxlbAe9oaANGBsF)
sq_moveWithParent(CnpzZn8qKt3BuMpan, CarGG6Htt35JzXHyF);

sq_SetCurrentDirection(CarGG6Htt35JzXHyF, CnpzZn8qKt3BuMpan.getDirection());

sq_AddObject(CnpzZn8qKt3BuMpan, CarGG6Htt35JzXHyF, OBJECTTYPE_DRAWONLY, false);

return CarGG6Htt35JzXHyF;
}

function destroyObjectByVar(obj, varStr)
{
	local objListSize = obj.getVar(varStr).get_obj_vector_size();	
	for(local i =0;i<objListSize;++i)
	{				
		local vObj = obj.getVar(varStr).get_obj_vector(i);
		if(vObj == null)
			continue;
			
		vObj.setValid(false);
	}
	
	obj.getVar(varStr).clear_obj_vector();
	
}

function procSkill_ATFighter(obj)
{
	if(!obj) return;

	local WAWESDw2ADSDw_tzznC = sq_GetSkillLevel(obj, 238);
	if(WAWESDw2ADSDw_tzznC < 1) return;

	local WAWESDw2ADSDw_7sK5RpTo = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local WAWESDw2ADSDw_rrmxV = CNSquirrelAppendage.sq_IsAppendAppendage(obj, WAWESDw2ADSDw_7sK5RpTo);

	local WAWESDw2ADSDw_CY2yI19 = "character/atfighter/nenmaster2nd/ap_spiralnen.nut";
	local WAWESDw2ADSDw_cRoF = CNSquirrelAppendage.sq_IsAppendAppendage(obj, WAWESDw2ADSDw_CY2yI19);

	local WAWESDw2ADSDw_y2g3hyMB = obj.getMyPassiveObjectCount(21085);
	if(WAWESDw2ADSDw_y2g3hyMB == 0 && WAWESDw2ADSDw_cRoF)
		CNSquirrelAppendage.sq_RemoveAppendage(obj, WAWESDw2ADSDw_CY2yI19);
	for(local WAWESDw2ADSDw_NKFlN = 0; WAWESDw2ADSDw_NKFlN < WAWESDw2ADSDw_y2g3hyMB; ++WAWESDw2ADSDw_NKFlN)
	{
		local WAWESDw2ADSDw_bOvrtBK = "SpiralGaleForceBall" + WAWESDw2ADSDw_NKFlN.tostring();
		local WAWESDw2ADSDw_FtDS = obj.getMyPassiveObject(21085,WAWESDw2ADSDw_NKFlN);
		local WAWESDw2ADSDw_gbvM4c = WAWESDw2ADSDw_FtDS.getCurrentAnimation();
		if(!WAWESDw2ADSDw_FtDS.getVar().getBool(0) && WAWESDw2ADSDw_cRoF && WAWESDw2ADSDw_rrmxV)
		{
			if(WAWESDw2ADSDw_gbvM4c)
			{
				local WAWESDw2ADSDw_ohBjG85I = "character/fighter/effect/animation/atspiralgaleforce/charge_dodge.ani";
				local WAWESDw2ADSDw_24twy = createAnimationPooledForceEx(WAWESDw2ADSDw_FtDS, WAWESDw2ADSDw_ohBjG85I,true,WAWESDw2ADSDw_FtDS.getXPos(), WAWESDw2ADSDw_FtDS.getYPos()+1, WAWESDw2ADSDw_FtDS.getZPos()+65,false);

				destroyObjectByVar(obj, WAWESDw2ADSDw_bOvrtBK);
				obj.getVar(WAWESDw2ADSDw_bOvrtBK).clear_obj_vector();
				obj.getVar(WAWESDw2ADSDw_bOvrtBK).push_obj_vector(WAWESDw2ADSDw_24twy);
				WAWESDw2ADSDw_FtDS.getVar().setBool(0,true);
			}
		}
		if(!WAWESDw2ADSDw_cRoF || !WAWESDw2ADSDw_rrmxV)
		{
			destroyObjectByVar(obj, WAWESDw2ADSDw_bOvrtBK);
			if(WAWESDw2ADSDw_gbvM4c && WAWESDw2ADSDw_FtDS.getVar().getBool(0))
				WAWESDw2ADSDw_FtDS.getVar().setBool(0,false);
		}

	}
}
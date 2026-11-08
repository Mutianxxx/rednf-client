function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BrandOfHeresy_enemy")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BrandOfHeresy_enemy")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BrandOfHeresy_enemy")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_BrandOfHeresy_enemy")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_BrandOfHeresy_enemy")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function drawAppend_appendage_BrandOfHeresy_enemy(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	
	if(isOver) 
	{
 		local ani = appendage.getVar().GetAnimationMap("brandofheresy", "character/priest/effect/animation/atbrandofheresy/brandofheresy_eff01.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
	}
}

function getImmuneTypeDamageRate_appendage_BrandOfHeresy_enemy(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate;
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		return damageRate;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_BRANDOFHERESY);
	damageRate = damageRate + sqrChr.sq_GetLevelData(SKILL_BRANDOFHERESY, 1, skillLevel) / 10 ;
	damageRate = damageRate.tointeger();
	return damageRate;
}

function proc_appendage_BrandOfHeresy_enemy(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
}


function onStart_appendage_BrandOfHeresy_enemy(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}



function onEnd_appendage_BrandOfHeresy_enemy(appendage)
{
	if (!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}
	
	appendage.setValid(false);
	return;
}


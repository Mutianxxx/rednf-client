function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_WINDBUFF")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_WINDBUFF")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_WINDBUFF")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_WINDBUFF")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_WINDBUFF")
}


function sq_AddEffect(appendage)
{

}

function drawAppend_appendage_WINDBUFF(appendage, isOver, x, y, isFlip)
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
	
 	local ani = appendage.getVar().GetAnimationMap("windbuff", "character/mage/atanimation/als_ani/atwindiness/windiness_shield_loop.ani");
	if(ani&&isOver) 
	{
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function getImmuneTypeDamageRate_appendage_WINDBUFF(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate;
		
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	
	if (!parentObj) {
		appendage.setValid(false);
		return damageRate;
	}
	
	local var = appendage.getVar();
	if (!var)
		return damageRate;	
	
	local skillLevel = parentObj.sq_GetSkillLevel(142);
	local Rate = parentObj.sq_GetLevelData(142, 3, skillLevel).tointeger();
	
	damageRate = damageRate-Rate;
	damageRate = damageRate/2;
	//print("damageRate="+damageRate+"\n");
	//print("Rate="+Rate+"\n");
	return damageRate.tointeger();
}

function proc_appendage_WINDBUFF(appendage)
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


function onStart_appendage_WINDBUFF(appendage)
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



function onEnd_appendage_WINDBUFF(appendage)
{
	if (!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);		
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}	
}


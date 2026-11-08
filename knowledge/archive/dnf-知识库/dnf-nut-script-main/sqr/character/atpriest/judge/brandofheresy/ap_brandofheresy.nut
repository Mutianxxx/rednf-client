
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BrandOfHeresy")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_BrandOfHeresy")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_BrandOfHeresy(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if(!sourceObj || !parentObj) 
	{
		appendage.setValid(false);
		return;
	}

}


function onAttackParent_appendage_BrandOfHeresy(appendage, realAttacker, damager, boundingBox, isStuck)
{

	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local active_damager = sq_GetCNRDObjectToActiveObject(damager);
	
	if(!pChr) return;
	if(!active_damager) return;
	if(!pChr.isEnemy(active_damager))
	{
		return;
	}
	
	local append = "character/atpriest/judge/brandofheresy/ap_brandofheresy_enemy.nut";
	local appendage = CNSquirrelAppendage.sq_AppendAppendage(active_damager, pChr, SKILL_BRANDOFHERESY, false, append, false);
	CNSquirrelAppendage.sq_AppendAppendageID(appendage, active_damager, pChr, APID_SKILL_ELEMENTAL_CHAIN_DARK, false);
	appendage = active_damager.GetSquirrelAppendage(append);
	if(appendage)
	{
		local timeMax = pChr.sq_GetIntData(SKILL_BRANDOFHERESY, 2);
		appendage.sq_SetValidTime(timeMax); 
	}
	
}

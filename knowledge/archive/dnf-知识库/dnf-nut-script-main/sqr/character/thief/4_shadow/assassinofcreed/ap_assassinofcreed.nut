
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ASSASSINOFCREED")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ASSASSINOFCREED")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_ASSASSINOFCREED(appendage)
{
	if(!appendage) {
		return;		
	}

	local obj = appendage.getParent();
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();	


	local sqrObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	
	if(sqrObj)
	{
		sqrObj.sq_RemovePassiveSkillAttackBonusRate(SKILL_ASSASSINOFCREED);
		sqrObj.sq_AddPassiveSkillAttackBonusRate(SKILL_ASSASSINOFCREED, 0);


	}
}



function onStart_appendage_ASSASSINOFCREED(appendage)
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


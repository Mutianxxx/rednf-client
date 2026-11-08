
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_crusade")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_crusade")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_crusade(appendage)
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
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	if(sqrObj)
	{
		sqrObj.sq_RemovePassiveSkillAttackBonusRate(SKILL_CRUSADE);
		sqrObj.sq_AddPassiveSkillAttackBonusRate(SKILL_CRUSADE, 6);
	}
}

function onStart_appendage_crusade(appendage)
{
	if(!appendage) {
		return;
	}
}


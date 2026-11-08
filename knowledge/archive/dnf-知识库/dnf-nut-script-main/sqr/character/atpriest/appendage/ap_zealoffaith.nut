
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_zealoffaith")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_zealoffaith")
}

function proc_appendage_zealoffaith(appendage)
{
	if(!appendage) {
		return;
	}
	local sourceObj = appendage.getSource();
	local parentObj = appendage.getParent();
	
	if(!parentObj || !sourceObj)
	{
		appendage.setValid(false);
		return;
	}
	
	local parentChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
	
	local skill = sq_GetSkill(parentChr, SKILL_ZEAL_OF_FAITH);
	local currTime = appendage.getTimer().Get();
	if (currTime - appendage.getVar("monsterTime").getInt(0) > 1000)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		if(skill && sq_IsInBattle()){
			setZealOfFaithAppend(parentChr, SKILL_ZEAL_OF_FAITH);
		}
	}
}

function onStart_appendage_zealoffaith(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!parentObj)
	{
		appendage.setValid(false);
		return;
	}
	local currTime = appendage.getTimer().Get();
	appendage.getVar("monsterTime").setInt(0,currTime);
}

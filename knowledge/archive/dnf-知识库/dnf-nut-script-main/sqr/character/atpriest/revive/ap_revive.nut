function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_revive")
}

function sq_AddEffect(appendage)
{
}

function onSetHp_appendage_revive(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
	local obj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!obj || !sourceObj){
		appendage.setValid(false);
		return hp;
	}
	
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	sourceObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	
	if(!sourceObj || !sqrChr)
	{
		return hp;
	}
	
	local org_hp =hp;
	local recHp = appendage.getVar("revive").get_vector(0);
	local holdTime = appendage.getVar("revive").get_vector(1);
	local userState = appendage.getVar("revive").get_vector(2);
	local append = "character/atpriest/revive/ap_revive_hold.nut";
	local holdState = sqrChr.IsSquirrelAppendage(append);

	if (hp < 1)
	{
		hp = 1;
		
		local newAppendage = CNSquirrelAppendage.sq_AppendAppendage(sqrChr, sourceObj, -1, false, append, true);
		if(newAppendage)
		{
			newAppendage.getVar("revive").clear_vector();
			newAppendage.getVar("revive").push_vector(recHp);
			newAppendage.getVar("revive").push_vector(holdTime);
			newAppendage.getVar("revive").push_vector(0);
			sq_HoldAndDelayDie(sqrChr, sourceObj, true, true, true, 1, 1, ENUM_DIRECTION_NEUTRAL, newAppendage);
			newAppendage.getAppendageInfo().setValidTime(holdTime + 500);
		}
		return hp;
	}
	return org_hp;
}

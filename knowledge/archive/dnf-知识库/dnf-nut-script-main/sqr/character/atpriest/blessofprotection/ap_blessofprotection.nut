function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BlessOfProtection")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BlessOfProtection")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BlessOfProtection")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_BlessOfProtection")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_BlessOfProtection(appendage)
{
	if(!appendage) {
		return;
	}
	local ParentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
}

function getImmuneTypeDamageRate_appendage_BlessOfProtection(appendage, damageRate, attacker) {
	if (!appendage)
		return damageRate;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		return damageRate;
	}
	local decreaseRate = appendage.getVar("protection").get_vector(0);
	damageRate = damageRate - decreaseRate;
	if (damageRate < 0) {
		damageRate = 0;
	}
	damageRate = damageRate.tointeger();
	return damageRate;
}

function onStart_appendage_BlessOfProtection(appendage)
{
	if(!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
}

function onEnd_appendage_BlessOfProtection(appendage)
{
	if(!appendage) {
		return;
	}
	local obj = appendage.getParent();
}


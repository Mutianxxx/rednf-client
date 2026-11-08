

function sq_AddFunctionName(appendage)
{

	appendage.sq_AddFunctionName("proc", "proc_appendage_WillDriver")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_WillDriver")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_WillDriver")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_WillDriver(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();

}

function onStart_appendage_WillDriver(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(13);
	local atkspeed = sq_GetLevelData(sqrChr, 13, 6, skillLevel)/10;
	local movespeed = sq_GetLevelData(sqrChr, 13, 5, skillLevel)/10;
	local phyatk = sq_GetLevelData(sqrChr, 13, 7, skillLevel);
	local phyrate = sq_GetLevelData(sqrChr, 13, 8, skillLevel);
	local stuck = sq_GetLevelData(sqrChr, 13, 9, skillLevel);
	local jump = sqrChr.sq_GetIntData(13, 2)/10;
	local change_appendage = appendage.sq_getChangeStatus("WillDriver");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("WillDriver",obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, 0);
	}
	if(change_appendage)
	{
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, true, atkspeed.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, true, movespeed.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, phyatk.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, phyrate.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -stuck.tofloat());
	}
}

function onEnd_appendage_WillDriver(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();

}


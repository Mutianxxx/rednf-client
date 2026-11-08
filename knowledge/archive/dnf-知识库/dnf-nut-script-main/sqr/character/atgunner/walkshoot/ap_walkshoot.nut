
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_atmage_walkshoot")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_atmage_walkshoot")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_atmage_walkshoot")
}

function proc_appendage_atmage_walkshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
	if(isDownZ)
	{
		sq_SetCurrentDirection(obj, sq_GetOppositeDirection(sq_GetDirection(obj)));//設置相反方向
	}
	
}

function onStart_appendage_atmage_walkshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onEnd_appendage_atmage_walkshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sq_GetSkillLevel(sqrChr, 15);
	sqrChr.startSkillCoolTime(15, skillLevel, -1);
}

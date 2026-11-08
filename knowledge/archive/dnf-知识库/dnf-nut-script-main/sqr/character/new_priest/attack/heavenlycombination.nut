function checkExecutableSkill_HeavenlyCombination(obj)
{
	if(!obj) return false;
	if(obj.isCarryWeapon())return false;
	local isUse = obj.sq_IsUseSkill(75);
	if(isUse)
	{
		obj.sq_IntVectClear();

		obj.sq_AddSetStatePacket(42, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



function checkCommandEnable_HeavenlyCombination(obj)
{
	if(!obj) return false;
	if(obj.isCarryWeapon())return false;
		return true;
}





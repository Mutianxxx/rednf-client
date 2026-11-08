function ProcPassiveSkill_Priest(obj, skill_index, skill_level)
{
	if (skill_index == 254)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if (skill_index == 171)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_priest/appendage/ap_priest_comminterrupt.nut", true);
		}
	}
	else if (skill_index == 87)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_priest/lanquan/dryout/ap_dryout.nut", true);
		}
	}
	else if (skill_index == 82)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_priest/appendage/ap_bigweaponmastery.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("bigweaponmastery");
			
			local matk = sq_GetLevelData(obj, 82, 3, skill_level).tofloat();
			local cooltimed = sq_GetLevelData(obj, 82, 4, skill_level).tofloat();
			matk = matk / 10;
			cooltimed = cooltimed / 1000;
			
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("bigweaponmastery",obj, obj, 0, 0, true, 0);
			}
			if(change_appendage) 
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK, true, matk);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_COOLTIME_DECLINE, false, -coolbonus);
			}
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_bigweaponmastery.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_priest/appendage/ap_bigweaponmastery.nut");
			}
		}
	}
	return true;
}




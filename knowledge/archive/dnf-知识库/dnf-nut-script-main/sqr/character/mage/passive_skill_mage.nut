function ProcPassiveSkill_Mage(obj, skill_index, skill_level)
{
	if (skill_index == 96)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/mage/zhanlingqianneng/ap_zhanlingqianneng.nut", true);
		}
	}
	else if (skill_index == 248)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/mage/dragondance/ap_dragondance_proc_skill.nut", true);
		}
	}
	else if (skill_index == 254)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if (skill_index == 170)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/mage/appendage/ap_eclipsehive.nut", true);
		}
	}
	else if (skill_index == 171)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/mage/appendage/ap_mage_comminterrupt.nut", true);
		}
	}
	else if (skill_index == SKILL_BESTOMASTER)
	{
		if(skill_level > 0 && obj.getWeaponSubType()==4)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_mage/equipbroom/ap_mgequipbroom.nut", true);

			local change_appendage = appendage.sq_getChangeStatus("mgequipbroom");//üòö¢Ü¨ûùßÒ÷¾
			local level = skill_level;
			local aimbonus	  = sq_GetLevelData(obj, SKILL_BESTOMASTER, 1, level);
			aimbonus		  = aimbonus.tofloat();
			local spdbonus	  = sq_GetLevelData(obj, SKILL_BESTOMASTER, 0, level)/10;
			spdbonus		  = spdbonus.tofloat();
			
			if(!change_appendage)//Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("mgequipbroom",obj, obj, 0, 0, true, 0);
			}
			if(change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();//?ğ¶óÑâ¦
				change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED,true, spdbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);//Ù¤ñé
			}
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/equipbroom/ap_mgequipbroom.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/equipbroom/ap_mgequipbroom.nut");
			}
		}
	}
	
	return true;
}


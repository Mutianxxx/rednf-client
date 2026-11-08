function ProcPassiveSkill_Thief(obj, skill_index, skill_level)
{
	if (skill_index == 94)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_thief/huixiejingtong/ap_huixiejingtong.nut", true);
		}
	}
	else if (skill_index == 252)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_thief/appendage/ap_thief_comminterrupt.nut", true);
		}
	}
	else if (skill_index == SKILL_HUI_XIE_JING_TONG)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/huixiejingtong/ap_huixiejingtong.nut", true);
		}
	}
	else if (skill_index == 254)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if (skill_index == SKILL_LEAVETRACE)
	{
			if(skill_level > 0)
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/3_kunoich/leavetrace/ap_leavetrace.nut", true);
			}
	}
	else if (skill_index == SKILL_SHURIKENIMPROVE)
	{
			if(skill_level > 0)
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/3_kunoich/shurikenimprove/ap_shurikenimprove.nut", true);
			}
	}
	else if (skill_index == SKILL_KUROKAGENOJUTSU)
	{
			if(skill_level > 0)
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/3_kunoich/kurokagenojutsu/ap_kurokagenojutsu.nut", true);
			}
	}
	else if (skill_index == SKILL_FIREMARK)
	{
			if(skill_level > 0)
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/3_kunoich/firemark/ap_firemark.nut", true);
				local skill_level = sq_GetSkillLevel(obj, SKILL_FIREMARK);
				local ELEMENT_ATTACK_FIRE = sq_GetLevelData(obj, SKILL_FIREMARK, 0, skill_level);
				local MAGICAL_CRITICAL_HIT_RATE = sq_GetLevelData(obj, SKILL_FIREMARK, 1, skill_level);

				ELEMENT_ATTACK_FIRE = ELEMENT_ATTACK_FIRE / 2;
				MAGICAL_CRITICAL_HIT_RATE = MAGICAL_CRITICAL_HIT_RATE / 2;

				local change_appendage = appendage.sq_getChangeStatus("firemark");
				if(!change_appendage)
				{
					change_appendage = appendage.sq_AddChangeStatus("firemark",obj, obj, 0, CHANGE_STATUS_TYPE_ELEMENT_ATTACK_FIRE, false, ELEMENT_ATTACK_FIRE);
					change_appendage = appendage.sq_AddChangeStatus("firemark",obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, MAGICAL_CRITICAL_HIT_RATE);
				}
				if(change_appendage) 
				{
					change_appendage.clearParameter();
					change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_FIRE, false, ELEMENT_ATTACK_FIRE.tofloat());
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, MAGICAL_CRITICAL_HIT_RATE.tofloat());
				}
			}
	}
	else if(skill_index == SKILL_POINTEDKNIFE)
	{
		if(skill_level > 0 && obj.getWeaponSubType() == 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/4_shadow/pointedknife/ap_pointedknife.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("pointedknife");
			local level = skill_level;
			
			local atkbonus	  = sq_GetLevelData(obj, SKILL_POINTEDKNIFE, 0, level).tofloat();
			atkbonus		  = atkbonus/10;
			local aimbonus	  = sq_GetLevelData(obj, SKILL_POINTEDKNIFE, 1, level).tofloat();
			aimbonus		  = aimbonus/10;
			local rigidity	  = sq_GetLevelData(obj, SKILL_POINTEDKNIFE, 2, level).tofloat();
			
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("pointedknife",obj, obj, 0, 0, true, 0);

			}
			if(change_appendage) 
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_RIGIDITY, false, rigidity);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);//Ù¤ï¿½ï¿½
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK,true, atkbonus); //Úªï¿½ï¿½ï¿½ï¿½Ìªï¿½ï¿½
			}
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/pointedknife/ap_pointedknife.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/thief/4_shadow/pointedknife/ap_pointedknife.nut");
			}
		}
	
	}
	else if (skill_index == SKILL_BEHINDCUT) {
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/thief/4_shadow/behindcut/ap_behindcut.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("behindcut"); //üòö¢Ü¨ûùßÒ÷¾
			local bacritical = sq_GetLevelData(obj, SKILL_BEHINDCUT, 0, skill_level) * 0.1;
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("behindcut", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_BACK_ATTACK_CRITICAL, false, bacritical.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_BACK_ATTACK_CRITICAL , false, bacritical.tofloat());
			}
		}
	}
	else if (skill_index == SKILL_RINGOFDARKNESS) {
		if (skill_level > 0) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/new_thief/ringofdarkness/ap_ringofdarkness.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("ringofdarkness"); //üòö¢Ü¨ûùßÒ÷¾
			local ackdark = sq_GetLevelData(obj, SKILL_RINGOFDARKNESS, 0, skill_level);
			if (!change_appendage) //Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("ringofdarkness", obj, obj, 0, 0, true, 0);
			}
			if (change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_ELEMENT_ATTACK_DARK, false, ackdark.tofloat());
			}
		}
	}
	return true;
}





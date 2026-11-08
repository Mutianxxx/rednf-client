/////////////////////////////////////////////////////////
//
// ï¿???? ï¿????ï¿??
// ï¿??? ï¿???ï¿?? ï¿???? ï¿???ï¿?? Appendageï¿??ï¿?ï¿??ï¿?? ï¿??ï¿?
//
/////////////////////////////////////////////////////////

function ProcPassiveSkill_ATMage(obj, skill_index, skill_level)
{
	if (skill_index == SKILL_EXPRESSION)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "Character/ATMage/Expressions/ap_atmage_expression.nut", true);
		
				//print(" expression appendage:" + appendage);
			if(appendage)
			{
				local magicalAtkChangeRate = sq_GetLevelData(obj, skill_index, SKL_LVL_COLUMN_IDX_1, skill_level);				
				
				local change_appendage = appendage.sq_getChangeStatus("expression");
				
				if(!change_appendage) {
					change_appendage = appendage.sq_AddChangeStatus("expression",obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicalAtkChangeRate );
				}
				
				
				if(change_appendage)
				{
					change_appendage.clearParameter();
					
					//print(" expression attack rate:" + magicalAtkChangeRate.tofloat());
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicalAtkChangeRate.tofloat());
				}
			}
		}
	}
	else if (skill_index == SKILL_BLOOD85_PASSIVE){
		if(skill_level > 0  && sq_getGrowType(obj)==3)
		{
        		if ( !CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/blood85_passive/ap_blood85_passive.nut") )
       	 	{
            			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOOD85_PASSIVE, false, 
				"character/atmage/blood85_passive/ap_blood85_passive.nut", true);
            			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BLOOD85_PASSIVE, skill_level);
            			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_BLOOD85_PASSIVE, true);
				local bgAdd = sq_GetLevelData(obj, SKILL_BLOOD85_PASSIVE, 0, skill_level); 
				local bgRate = sq_GetLevelData(obj, SKILL_BLOOD85_PASSIVE, 1, skill_level); 
				local change_appendage = appendage.sq_getChangeStatus("blood85_passive");
				if(!change_appendage)
            			{
					change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
					CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, 
					false, bgAdd, APID_COMMON);
				}
            			if (change_appendage){
					change_appendage.clearParameter();
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, bgAdd.tofloat());
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, bgRate.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE, false, bgRate.tofloat() );
				}
			}

    		}
	}
	else if (skill_index == SKILL_BLOOD50_PASSIVE){
		if(skill_level  > 0)
    		{
        		if ( !CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/blood50_passive/ap_blood50_passive.nut") )
       		{
            			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOOD50_PASSIVE, false, 
					"character/atmage/blood50_passive/ap_blood50_passive.nut", true);
           			 appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BLOOD50_PASSIVE, skill_level);
            			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_BLOOD50_PASSIVE, true);
       		 	//print("50 all ok!\n\r");
       		 }
       	}
	}
	else if (skill_index == SKILL_ABYSS)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, 
			"Character/ATMage/Abyss/ap_ATMage_Abyss.nut", true);
	
			if(appendage)
			{
				local mpMaxIncreRate = obj.sq_GetIntData(SKILL_ABYSS, 0);
				local change_appendage = appendage.sq_getChangeStatus("abyss_mpmax");
				
				if(!change_appendage) {
					change_appendage = appendage.sq_AddChangeStatus("abyss_mpmax",obj, obj, 0, CHANGE_STATUS_TYPE_MP_MAX, true, mpMaxIncreRate );
				}
				
				if(change_appendage)
				{
					change_appendage.clearParameter();
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_MAX, true, mpMaxIncreRate.tofloat());
				}
			}
		}
	}
	else if(skill_index == SKILL_STICKMASTER)
	{ // ï¿???
		if(skill_level > 0&&obj.getWeaponSubType()==1)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/atmage/stickmaster/ap_stickmaster.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("atmagestickmaster");//ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			local level = skill_level;
			
			local atkbonus	  = sq_GetLevelData(obj, SKILL_STICKMASTER, 0, level).tofloat();
			atkbonus		  = atkbonus/10;
			local aimbonus	  = sq_GetLevelData(obj, SKILL_STICKMASTER, 1, level).tofloat();
			aimbonus		  = aimbonus/10;
			local spdbonus	  = sq_GetLevelData(obj, SKILL_STICKMASTER, 2, level).tofloat();
			spdbonus		  = (spdbonus/10);
			local coolbonus	  = sq_GetLevelData(obj, SKILL_STICKMASTER, 3, level).tofloat();
			coolbonus		  = (coolbonus/1000);
			local cthbonus	  = sq_GetLevelData(obj, SKILL_STICKMASTER, 4, level).tofloat();		
			cthbonus		  = (cthbonus/10);
			
			if(!change_appendage)//ï¿½ï¿½ï¿½ï¿½?ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¥ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ID
			{
				change_appendage = appendage.sq_AddChangeStatus("atmagestickmaster",obj, obj, 0, 0, true, 0);
				//print("init ok!\n\r");

			}
			if(change_appendage) //ï¿½ï¿½?ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½
			{
				change_appendage.clearParameter();//?ï¿½ï¿½ï¿½ï¿½
				change_appendage.addParameter(CHANGE_STATUS_TYPE_COOLTIME_DECLINE, false, -coolbonus);//Ý¾Ê¥ï¿½ï¿½ï¿?-CD
				change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED,true, spdbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE,false, cthbonus);//Úªï¿½ï¿½ï¿½ï¿½?
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);//Ù¤ï¿½ï¿½
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS,true, atkbonus); //Úªï¿½ï¿½ï¿½ï¿½Ìªï¿½ï¿½
			}
			
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/stickmaster/ap_stickmaster.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/stickmaster/ap_stickmaster.nut");
			}
		}
	
	}
	else if(skill_index == 91)
	{ 
		if( skill_level > 0 && obj.getWeaponSubType()==4)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/atmage/equipbroom/ap_equipbroom.nut", true);
			
			local change_appendage = appendage.sq_getChangeStatus("atequipbroom");//ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			local level = skill_level;
			
			local aimbonus	  = sq_GetLevelData(obj, 91, 1, level);
			aimbonus		  = aimbonus.tofloat();
			local spdbonus	  = sq_GetLevelData(obj, 91, 0, level)/10;
			spdbonus		  = spdbonus.tofloat();

			if(!change_appendage)//ï¿½ï¿½ï¿½ï¿½?ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¥ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½ID
			{
				change_appendage = appendage.sq_AddChangeStatus("atequipbroom",obj, obj, 0, 0, true, 0);
			}
			if(change_appendage) //ï¿½ï¿½?ï¿½ï¿½ï¿½ï¿½Ü¨ï¿½ï¿½ï¿½ï¿½
			{
				change_appendage.clearParameter();//?ï¿½ï¿½ï¿½ï¿½
				change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED,true, spdbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -aimbonus);//Ù¤ï¿½ï¿½
			}
			
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/equipbroom/ap_equipbroom.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/equipbroom/ap_equipbroom.nut");
			}
		}
	}
	else if(skill_index == SKILL_DIEHARD)
	{ // ï¿???
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, 
			"Character/ATMage/DieHard/ap_ATMage_DieHard.nut", true);

			if(appendage)
			{
			}
		}
	
	}
	else if(skill_index == SKILL_TUNDRASOUL)
	{ 
		if(skill_level > 0)
		{
			local skill = sq_GetSkill(obj, SKILL_TUNDRASOUL);
			if(!skill)
				return true;
			if(!skill.isSealFunction())
			{
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, 
				"Character/ATMage/TundraSoul/ap_ATMage_TundraSoul.nut", true);
				
				if(appendage)
				{
					if(!skill.isSealFunction())
					{
						if(sq_IsInBattle())
						{
							local range = obj.sq_GetIntData(SKILL_TUNDRASOUL , 0);
							local AuraTundraSoulAppendage = appendage.sq_AddSquirrelAuraMaster("AuraTundraSoul",obj, obj, range, 18, 5, 0);
						}
						else
						{
							appendage.sq_DeleteAppendages();
						}
					}
					else
					{
						appendage.sq_DeleteAppendages();
					}
				}
			}
		}
	}
	else if (skill_index == 167)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/atmage/powerofwindgod/ap_powerofwindgod.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("atmagewind50");
			local level = sq_GetSkillLevel(obj, 167);
			
			local cthbonus	  = sq_GetLevelData(obj, 167, 0, level).tofloat();
			cthbonus		  = cthbonus/10;

			local spdbonus	  = sq_GetLevelData(obj, 167, 3, level).tofloat();
			spdbonus		  = (spdbonus/10);

			
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("atmagewind50",obj, obj, 0, 0, true, 0);

			}
			if(change_appendage) 
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED,true, spdbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE,false, cthbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE,false, cthbonus);
			}
			
		}
	}
	else if (skill_index == 145)//ó­êª?ÍØ?öÇù¬?
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "Character/ATMage/NullChange/ap_NullChange.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("nullchange");//üòö¢Ü¨ûùßÒ÷¾
			local level = sq_GetSkillLevel(obj, 145);
			
			local magicalAttack = sq_GetLevelData(obj, 145, 0, level).tofloat();
			magicalAttack	= magicalAttack/10;
			local magicalCritical = sq_GetLevelData(obj, 145, 1, level).tofloat();
			magicalCritical	= magicalCritical/10;
			local mpMaxIncreRate = sq_GetLevelData(obj, 145, 2, level).tofloat();
			mpMaxIncreRate	= mpMaxIncreRate/10;
			local hpMaxdecreRate = sq_GetLevelData(obj, 145, 3, level).tofloat();
			hpMaxdecreRate	= 0 - (hpMaxdecreRate/10);
			if(!change_appendage)//Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				change_appendage = appendage.sq_AddChangeStatus("nullchange",obj, obj, 0, 0, true, 0);
			}
			
			if(change_appendage)//Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
				change_appendage.clearParameter();//?ð¶óÑâ¦
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, true, magicalAttack);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, magicalCritical);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_MAX, true, mpMaxIncreRate);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_HP_MAX, true, hpMaxdecreRate);
			}
			
		}
	}
	else if (skill_index == 171)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "/character/atmage/appendage/ap_atmage_comminterrupt.nut", true);
		}
	}
	else if (skill_index == 254)
	{
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
	}
	else if(skill_index == SKILL_ELEMENTAL_BOMBING)
	{ 
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/atmage/appendage/ap_elementalbombing.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("elementalbombing");
			local level = skill_level;
			local spdbonus = sq_GetLevelData(obj, SKILL_ELEMENTAL_BOMBING, 4, level).tofloat();
			local coolbonus = sq_GetLevelData(obj, SKILL_ELEMENTAL_BOMBING, 5, level).tofloat() /1000.0;
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("elementalbombing",obj, obj, 0, 0, true, 0);
			}
			if(change_appendage)
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_CAST_SPEED,true, spdbonus);
				change_appendage.addParameter(CHANGE_STATUS_TYPE_COOLTIME_DECLINE, false, -coolbonus);
			}
		}
		else
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/appendage/ap_elementalbombing.nut")) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/appendage/ap_elementalbombing.nut");
			}
		}
	}
	return true;
}


function onUseSkillPassiveSkill_ATMage(obj,skillIndex, skillLevel)
{
	if(!obj)
		return;		
		
	//print( " onuseskill");

}





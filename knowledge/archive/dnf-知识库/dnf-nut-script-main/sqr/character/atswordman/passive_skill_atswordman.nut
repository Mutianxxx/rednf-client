
function ProcPassiveSkill_ATSwordman(obj, skill_index, skill_level)
{
	switch(skill_index)
	{
	case 4:
		local apPath = "character/atswordman/1_swordmaster/shortswordmastery/ap_shortswordmastery.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 11:
		local apPath = "character/atswordman/1_swordmaster/blademastery/ap_blademastery.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 12:
		local apPath = "character/atswordman/1_swordmaster/heavyswordmastery/ap_heavyswordmastery.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 13:
		local apPath = "character/atswordman/1_swordmaster/bluntmastery/ap_bluntmastery.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 15:
		local apPath = "character/atswordman/1_swordmaster/bladesoul/ap_bladesoul.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 16:
		local apPath = "character/atswordman/1_swordmaster/promiseofantiquity/ap_promiseofantiquity.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0 && sq_getGrowType(obj)==1)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 148:
		local apPath = "character/atswordman/2_demonslayer/calldaimus/ap_calldaimus.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 154:
		local apPath = "character/atswordman/2_demonslayer/controldemonsword/ap_controldemonsword.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 159:
		local apPath = "character/atswordman/2_demonslayer/greed/ap_atgreed.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 65:
		local apPath = "character/atswordman/4_darktempler/evolve/ap_evolve.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 40:
		local apPath = "character/atswordman/4_darktempler/loyalslave/ap_loyalslavebuff.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 104:
		local apPath = "character/atswordman/2_vegabond/threeflower/ap_threeflower.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 121:
		local apPath = "character/atswordman/5_bladeshadows/appendage/ap_vintage.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 122:
		local apPath = "character/atswordman/5_bladeshadows/appendage/ap_oldfashioned.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 123:
		local apPath = "character/atswordman/5_bladeshadows/appendage/ap_license.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 125:
		local apPath = "character/atswordman/5_bladeshadows/appendage/ap_infamous.nut";
		local ap = CNSquirrelAppendage.sq_IsAppendAppendage(obj, apPath);
		if(skill_level>0 && sq_getGrowType(obj)==0)
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, apPath, true);
		break;
	case 254:
		if(skill_level > 0)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 254, false, "character/gunner/latentability/ap_latentability.nut", true);
		}
		break;
	case 33:
		
		if(skill_level>0){
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, skill_index, false, "character/atswordman/2_vegabond/equiplightsword/ap_equiplightsword.nut", true);
			local change_appendage = appendage.sq_getChangeStatus("equiplightsword");//üòö¢Ü¨ûùßÒ÷¾
			local clevel = sq_GetSkillLevel(obj, 174);
			//print("level:"+clevel+"\n\r");
			local equbonus = clevel*4;
			local charbonus = clevel;
			local cddec = -0.1;
			if(!change_appendage)//Ó×Üô?ßÒ÷¾Ü¨ûùãÁ£¬ôÕÊ¥ßÒ÷¾Ü¨ûùîÜID
			{
				//print("change_appendage not ok!\n\r");
				//print("num1:"+equbonus+"\n\r");
				change_appendage = appendage.sq_AddChangeStatus("equiplightsword",obj, obj, 0, 0, false, 0);
				//print("num2:"+charbonus+"\n\r");

			}
			if(change_appendage) //Ó×?ßÒ÷¾Ü¨ûùãÁ
			{
					//print("change_appendage ok!\n\r");
					change_appendage.clearParameter();//?ğ¶óÑâ¦
					//print("num3:"+equbonus+"\n\r");
					if(sq_getGrowType(obj) == 2){
						
						change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, charbonus.tofloat());//Úª×â
						change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, charbonus.tofloat());//ØªÛö
						change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, false, equbonus.tofloat()); //Úª×âÍôÌªÕô
						change_appendage.addParameter(31, false, equbonus.tofloat()); //ØªÛöÍôÌªÕô
						//print("num4:"+equbonus+"\n\r");
					}
			}
		}
		break;
	}
	return true;
}

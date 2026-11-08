function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_qiangrengailiang")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_qiangrengailiang")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_qiangrengailiang")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_qiangrengailiang")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_qiangrengailiang(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onStart_appendage_qiangrengailiang(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(sqrChr.getWeaponSubType() == 0)
	{
		local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_QIANG_REN_GAI_LIANG);
		local physicalAttackBonus = sq_GetLevelData(sqrChr, SKILL_QIANG_REN_GAI_LIANG, 0, skillLevel);
		local attackSpeed = sq_GetLevelData(sqrChr, SKILL_QIANG_REN_GAI_LIANG, 1, skillLevel);
		local change_appendage = appendage.sq_getChangeStatus("qiangrengailiang");
		if(!change_appendage)
		{
			change_appendage = appendage.sq_AddChangeStatus("qiangrengailiang",obj, obj, 0, CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, physicalAttackBonus);
		}
		if(change_appendage)
		{
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, physicalAttackBonus.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, attackSpeed.tofloat());
		}
	}
}

function proc_appendage_qiangrengailiang(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	local state = obj.getState();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);

	local skill = sq_GetSkill(sqrChr, 64);
	if(!skill){
		return;
	}
	if(skill.isSealFunction())
	{
		return;
	}
	if(sqrChr.sq_GetSkillLevel(64)<1)
	{
		return;
	}
	
	switch(state)
	{
		//Z
		case 20 : 
			//sqrChr.sq_IntVectClear();
			//sqrChr.sq_IntVectPush(2);	//0, 1, 2, 3
			//sqrChr.sq_AddSetStatePacket(46, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
		//C + Z
		case 52 : 
		local isDownX = sq_IsKey(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL);
		local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
		if(isDownZ)
		{
		sqrChr.sq_IntVectClear();
		sqrChr.sq_AddSetStatePacket(38, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		if(isDownX)
		{
		sqrChr.sq_IntVectClear();
		sqrChr.sq_IntVectPush(94);	//0, 1, 2, 3
		sqrChr.sq_AddSetStatePacket(56, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		break;		//???????
		//Dash + Z
		case 15 : 
		local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
		local isDownC = sq_IsKey(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL);
		if(isDownZ)
		{
			sqrChr.sq_IntVectClear();
			sqrChr.sq_AddSetStatePacket(47, STATE_PRIORITY_IGNORE_FORCE, false);
		}
		if(isDownC)
		{
			sqrChr.sq_IntVectClear();
			sqrChr.sq_AddSetStatePacket(50, STATE_PRIORITY_IGNORE_FORCE, false);
			sq_SetCurrentPos(sqrChr,sqrChr.getXPos(),sqrChr.getYPos(),0);
		}
		break;
		//C + Z
		case 6 : 
		local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
		local isDownC = sq_IsKey(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL);
		local zpos = sqrChr.getZPos()
		if(isDownZ){
			sqrChr.sq_IntVectClear();
			sqrChr.sq_AddSetStatePacket(48, STATE_PRIORITY_IGNORE_FORCE, false);
		}
		if(isDownC && zpos < 50){
			 
			sqrChr.sq_IntVectClear();
			sqrChr.sq_AddSetStatePacket(50, STATE_PRIORITY_IGNORE_FORCE, false);
			sq_SetCurrentPos(sqrChr,sqrChr.getXPos(),sqrChr.getYPos(),0);
		}
		break;
		//X
		/*case 8 : 
		local skillIndex = obj.getCurrentSkillIndex();
		if(skillIndex != -1) break;
		sqrChr.sq_IntVectClear();
		sqrChr.sq_IntVectPush(0);
		sqrChr.sq_AddSetStatePacket(49, STATE_PRIORITY_IGNORE_FORCE, true);
		break;*/
		//Dash Attack
		//JumpAttack
		case 7 : 
		obj.getVar("shootCount").clear_vector();
		obj.getVar("shootCount").push_vector(0);
		sqrChr.sq_IntVectClear();
		sqrChr.sq_AddSetStatePacket(51, STATE_PRIORITY_IGNORE_FORCE, false);
		break;
		case 51 : 
		local isDownX = sq_IsKey(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL);
		local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
		if(isDownZ)
		{
		sqrChr.sq_IntVectClear();
		sqrChr.sq_AddSetStatePacket(48, STATE_PRIORITY_IGNORE_FORCE, false);
		}
		if(isDownX)
		{
		local pAni = sqrChr.sq_GetCurrentAni();
		local frmIndex = sqrChr.sq_GetCurrentFrameIndex(pAni);
		if(frmIndex<1) break;
		local count = obj.getVar("shootCount").get_vector(0);
		local max = 5;
		local append = sqrChr.getVar("stayjumpshoot").getBool(0);
		if (append)
		{
			local skill_level = sq_GetSkillLevel(sqrChr, 33);
			max = 5 + sq_GetLevelData(sqrChr, 33, 2, skill_level);
		}
		if(count>=max) 
			break;
		obj.getVar("shootCount").set_vector(0, count+1);
		sqrChr.sq_IntVectClear();
		sqrChr.sq_AddSetStatePacket(51, STATE_PRIORITY_IGNORE_FORCE, false);
		}
		break;
		//???ï¿?
		/*case 19 : 
			if(!isSeal)
			{
				sqrChr.sq_IntVectClear();
				sqrChr.sq_IntVectPush(0);
				sqrChr.sq_AddSetStatePacket(52, STATE_PRIORITY_IGNORE_FORCE, true);
			}
			local isDownX = sq_IsKey(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL);
			local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
			if(isDownZ)
			{
			sqrChr.sq_IntVectClear();
			sqrChr.sq_AddSetStatePacket(38, STATE_PRIORITY_IGNORE_FORCE, true);
			}
			if(isDownX)
			{
			sqrChr.sq_IntVectClear();
			sqrChr.sq_IntVectPush(94);	//0, 1, 2, 3
			sqrChr.sq_AddSetStatePacket(56, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		break;*/
		case 21 : 
		//sqrChr.sq_IntVectClear();
		//sqrChr.sq_IntVectPush(0);
		//sqrChr.sq_AddSetStatePacket(53, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		//ï¿?
		case 23 : 
		//sqrChr.sq_IntVectClear();
		//sqrChr.sq_AddSetStatePacket(54, STATE_PRIORITY_IGNORE_FORCE, false);
		break;
		//ï¿??ï¿???ï¿??ï¿?
		case 45 : 
		sqrChr.sq_IntVectClear();
		sqrChr.sq_IntVectPush(0);
		sqrChr.sq_AddSetStatePacket(55, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		case 47 : 
		local isDownZ = sq_IsKey(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);
		if(isDownZ)
		{
			sqrChr.sq_IntVectClear();
			sqrChr.sq_IntVectPush(0);
			sqrChr.sq_AddSetStatePacket(52, STATE_PRIORITY_USER, true);
		}
		break;
	}
}

function onEnd_appendage_qiangrengailiang(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onAttackParent_appendage_qiangrengailiang(appendage, realAttacker, damager, boundingBox, isStuck)
{

	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(64);
	local state = obj.getState();
	if (state == 46 || state == 47 || state == 48 || state == 49 || state == 50 || state == 51 || state == 52 || state == 115 || state == 101 || state == 53 || state == 54 || state == 55 || state == 56 || state == 38 || state == 23 || state == 24 || state == 237 || state == 238 || state == 239 || state == 41 || state == 58 || state == 236 || state == 37){
		local bleedProb = sq_GetLevelData(sqrChr, 64, 4, skillLevel)/10.0;
		local bleedLevel = sq_GetLevelData(sqrChr, 64, 5, skillLevel);
		local bleedTime = sq_GetLevelData(sqrChr, 64, 7, skillLevel);
		local bleedPower = sqrChr.sq_GetPowerWithPassive(64, -1, 6, -1, 1.0);
		sq_sendSetActiveStatusPacket(damager, sqrChr, ACTIVESTATUS_BLEEDING, bleedProb.tofloat(), bleedLevel, false, bleedTime, bleedPower);
	}
}




function getBoolByPossibility(prob, base)
{
	local randomNum = sq_getRandom(0, base);
	local isTrue;

	if(randomNum <= prob)
	{
		isTrue = true;
	}

	else if(randomNum > prob)
	{
		isTrue = false;
	}

	return isTrue;
}


function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_gunner_huashi")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_gunner_huashi")
}


function sq_AddEffect(appendage)
{
}
function onStart_appendage_gunner_huashi(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	//local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_SWORDMAN_DEVILTEST);
	local physicalAttack = 10000;//sq_GetLevelData(sqrChr, SKILL_SWORDMAN_DEVILTEST, 0, skillLevel);
	local magicalAttack = 10000;//sq_GetLevelData(sqrChr, SKILL_SWORDMAN_DEVILTEST, 1, skillLevel);
			local value0 =10000;// sq_GetLevelData(obj, , 0, skill_level); 
			local value1 =10000;// sq_GetLevelData(obj, , 1, skill_level); 
			local value2 =100;// sq_GetLevelData(obj, , 2, skill_level); 
			local value3 =100;// sq_GetLevelData(obj, , 3, skill_level); 
			local value4 =100;// sq_GetLevelData(obj, , 4, skill_level); 
	local change_appendage = appendage.sq_getChangeStatus("gunner_huashi");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("gunner_huashi",obj, obj, 0, CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, physicalAttack);
	}
	if(change_appendage)
	{
		change_appendage.clearParameter();
		//change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, physicalAttack.tofloat());
		//change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, magicalAttack.tofloat());

				//change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, false, value0.tofloat());
				//change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK, false, value1.tofloat());
				//change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, false, value2.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, value3.tofloat());
				//change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE, false, value4.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, physicalAttackBonus.tofloat());
		//change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE, false, magicalAttackBonus.tofloat());
	}
}
function proc_appendage_gunner_huashi(appendage)
{
	if(!appendage) return;

	//dofile("test.nut");
	//test(appendage);
	
}



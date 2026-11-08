
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_avenger_guard")	
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_avenger_guard")
}

function onDamageParent_appendage_avenger_guard(appendage ,attacker, boundingBox, isStuck)
{
	if (appendage == NULL)
		return;		

	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	
	if (parentObj == NULL)
	{
		appendage.setValid(false);
		return;
	}
	
	local var = appendage.getVar();
	if (var == NULL)
		return;	
		
	local hitEffect = sq_AddDrawOnlyAniFromParent(parentObj, "Character/Priest/Animation/AvengerGuard/HIT_Hit_energy.ani"  ,0,-1,0);
	if (hitEffect)
	{
		var.push_obj_vector(hitEffect);
	}
	
	if (isStuck)
		return;
}

function getImmuneTypeDamageRate_appendage_avenger_guard(appendage, damageRate, attacker)
{		
	if (!appendage)
		return damageRate;
		
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	
	if (!parentObj) {
		appendage.setValid(false);
		return damageRate;
	}
	
	local var = appendage.getVar();
	if (!var)
		return damageRate;	
			
	// 레벨인포로 데미지율이 조정됨.
	local skill_level = parentObj.sq_GetSkillLevel(SKILL_AVENGER_AWAKENING);
	local decreaseRate = parentObj.sq_GetLevelData(SKILL_AVENGER_AWAKENING, 11, skill_level); // 11. 데미지 감소율(%)			
	damageRate = damageRate - decreaseRate;
	return damageRate;
}

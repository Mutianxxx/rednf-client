//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_kurokagenojutsu")
	appendage.sq_AddFunctionName("proc", "proc_appendage_kurokagenojutsu")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_kurokagenojutsu")
}



function sq_AddEffect(appendage)
{
}



function onStart_appendage_kurokagenojutsu(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}
	if(!sq_IsInBattle())
	{
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}

	local startTime = appendage.getTimer().Get();
	appendage.getVar("t").clear_vector();
	appendage.getVar("t").push_vector(startTime);
	local skill = sq_GetSkill(parentObj, SKILL_KUROKAGENOJUTSU);
	if(!skill.isSealFunction())
	{
		local objectManager = parentObj.getObjectManager();
		for(local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && object.isObjectType(OBJECTTYPE_ACTIVE) && parentObj.isEnemy(object)&&object.isInDamagableState(parentObj))
			{
				local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/thief/3_kunoich/kurokagenojutsu/ap_kurokagenojutsu_enemy.nut");
				if(!isAppend)
				{
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, parentObj, SKILL_KUROKAGENOJUTSU, false, "character/thief/3_kunoich/kurokagenojutsu/ap_kurokagenojutsu_enemy.nut", false);
					CNSquirrelAppendage.sq_Append(appendage, object, parentObj);
				}
			}
		}
	}
}



function proc_appendage_kurokagenojutsu(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}

	local currentTime = appendage.getTimer().Get();
	local startTime = appendage.getVar("t").get_vector(0);
	local skill = sq_GetSkill(parentObj, SKILL_KUROKAGENOJUTSU);
	if(currentTime - startTime > parentObj.sq_GetIntData(SKILL_KUROKAGENOJUTSU, 1) && !skill.isSealFunction())
	{
		local objectManager = parentObj.getObjectManager();
		for(local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && object.isObjectType(OBJECTTYPE_ACTIVE) && parentObj.isEnemy(object))
			{
				local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/thief/3_kunoich/kurokagenojutsu/ap_kurokagenojutsu_enemy.nut");
				if(!isAppend)
				{
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, parentObj, SKILL_KUROKAGENOJUTSU, false, "character/thief/3_kunoich/kurokagenojutsu/ap_kurokagenojutsu_enemy.nut", false);
					CNSquirrelAppendage.sq_Append(appendage, object, parentObj);
				}
			}
		}
		appendage.getVar("t").set_vector(0, currentTime);
	}
}



function onEnd_appendage_kurokagenojutsu(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
}


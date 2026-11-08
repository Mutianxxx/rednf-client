
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_firemark")
	appendage.sq_AddFunctionName("proc", "proc_appendage_firemark")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_firemark")
}



function sq_AddEffect(appendage)
{
}



function onStart_appendage_firemark(appendage)
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
	local skill = sq_GetSkill(parentObj, SKILL_FIREMARK);
	if(!skill.isSealFunction())
	{
		local objectManager = parentObj.getObjectManager();
		for(local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && object.isObjectType(OBJECTTYPE_ACTIVE) && parentObj.isEnemy(object)&&object.isInDamagableState(parentObj))
			{
				local skill_level = sq_GetSkillLevel(parentChr, SKILL_DOOMFIELD);
				local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/thief/3_kunoich/firemark/ap_firemark_enemy.nut");
				if(!isAppend)
				{
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, parentObj, SKILL_FIREMARK, false, "character/thief/3_kunoich/firemark/ap_firemark_enemy.nut", false);
					CNSquirrelAppendage.sq_Append(appendage, object, parentObj);
				}
			}
		}
	}
}



function proc_appendage_firemark(appendage)
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
	local skill = sq_GetSkill(parentObj, SKILL_FIREMARK);
	if(currentTime - startTime > sq_GetIntData(parentObj, SKILL_FIREMARK, 0) && !skill.isSealFunction())
	{
		local xPos = parentObj.getXPos();
		local yPos = parentObj.getYPos();
		local zPos = parentObj.getZPos();
		local distance1 = sq_GetIntData(parentObj, SKILL_FIREMARK, 2);
		local distance2 = sq_GetIntData(parentObj, SKILL_FIREMARK, 4);
		local objectManager = parentObj.getObjectManager();
		for(local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && object.isObjectType(OBJECTTYPE_ACTIVE) && parentObj.isEnemy(object) && object.isInDamagableState(parentObj) && sq_GetDistance(xPos, yPos, object.getXPos(), object.getYPos(), true) <= distance1)
			{
				local isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/thief/3_kunoich/firemark/ap_firemark_enemy1.nut");
				if(!isAppend1)
				{
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, parentObj, SKILL_FIREMARK, false, "character/thief/3_kunoich/firemark/ap_firemark_enemy1.nut", false);
					CNSquirrelAppendage.sq_Append(appendage, object, parentObj);
				}
			}
			if(object && object.isObjectType(OBJECTTYPE_ACTIVE) && parentObj.isEnemy(object) && object.isInDamagableState(parentObj) && sq_GetDistance(xPos, yPos, object.getXPos(), object.getYPos(), true) <= distance2)
			{
				local isAppend2 = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/thief/3_kunoich/firemark/ap_firemark_enemy2.nut");
				if(!isAppend2)
				{
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, parentObj, SKILL_FIREMARK, false, "character/thief/3_kunoich/firemark/ap_firemark_enemy2.nut", false);
					CNSquirrelAppendage.sq_Append(appendage, object, parentObj);
				}
			}
		}
		appendage.getVar("t").set_vector(0, currentTime);
	}
}



function onEnd_appendage_firemark(appendage)
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


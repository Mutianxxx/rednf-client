
function isUsableItem_Fighter(obj, itemIndex)
{
	if (!sq_IsInBattle()) {
		isUsableItem_AllGrowJob(obj, itemIndex);
	}
	local size = obj.getVar("itemIndex").size_vector();
	for (local i = 0; i < size; ++i) {
		local isSaved = false;
		for (local i = 0; i < size; ++i) {
			local index = obj.getVar("itemIndex").get_vector(i);
			if (index == itemIndex) {
				isSaved = true;
			}
		}
		local index = obj.getVar("itemIndex").get_vector(i);
		if (index == i && !isSaved) {
			obj.getVar("itemIndex").set_vector(i, itemIndex);
		}
	}
	return duegonUsableItem(itemIndex);
}

function drawMainCustomUI_Fighter(obj)
{
	if(!obj) return;
	obj.getVar("itemIndex").clear_vector();
	local slotNum = 6;
	for(local i=0;i<slotNum;++i)
	{
		obj.getVar("itemIndex").push_vector(i);
	}

	drawNewDamageUI_AllGrowJob(obj);

}

function procAppend_Fighter(obj)
{
	if(!obj) return 0;
	procAppend_AllGrowJob(obj);
	local nowState = obj.sq_GetState();
	
	if(nowState == STATE_JUMP)
	{
		obj.setSkillCommandEnable(64 ,true);
	}
	
	if (obj.isMyControlObject()&&(sq_getGrowType(obj) == 3)&&(!sq_isPVPMode())) 
	{
		
		//����������������
		local index = obj.getCurrentSkillIndex();

		//֮�ޫ���������
		if (index == 106) 
		{
        		if (!CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_groundkickhold.nut" )) 
        		{
				CNSquirrelAppendage.sq_AppendAppendage ( obj, obj, index, false, "apjh/ap_groundkickhold.nut", true );
			}
		} 
		else 
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_groundkickhold.nut" )) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "apjh/ap_groundkickhold.nut");
			}
    		}

		//ʶ���������?
		if (index == 77 && sq_IsMyCharacter(obj)) 
		{
			if (!CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_junkspin.nut" )) 
			{
				CNSquirrelAppendage.sq_AppendAppendage ( obj, obj, index, false, "apjh/ap_junkspin.nut", true );
			}
		} 
		else 
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_junkspin.nut" )) 
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "apjh/ap_junkspin.nut");
			}
		}
	}
	//illusionBombAdd(obj);
	obj.setSkillCommandEnable(69,true);
	if (obj.sq_IsEnterSkill(69) != -1 && sq_IsMyCharacter(obj) && !sq_isPVPMode()) {
		local objectManager = obj.getObjectManager();
		local objectNumber = objectManager.getCollisionObjectNumber();
		for (local i = 0; i < objectNumber; i++) {
			local Monster = objectManager.getCollisionObject(i);
			if(!Monster.isObjectType(OBJECTTYPE_MONSTER))
				continue;
			local xPos = obj.getXPos() - Monster.getXPos();
			local yPos = Monster.getYPos() - obj.getYPos();
			local zPos = sq_GetObjectHeight(Monster)*2/3 - obj.getZPos();
			if (Monster.getState() != 5 && Monster.getCollisionObjectIndex() == 60040 && Monster.isMyControlObject()) {
				local power = obj.sq_GetPowerWithPassive(69, 13, 0, -1, 1.0);
				local rate = obj.sq_GetIntData(69, 0);
				local sizeRate = rate.tointeger();
				
				local explosionInfo = sq_getNewAttackInfoPacket();
				explosionInfo.sizeRate = sizeRate;
				explosionInfo.power = power;
				explosionInfo.useWeapon = true;
				sq_createCommonElementalAttack(obj, ENUM_ELEMENT_LIGHT, xPos, yPos, zPos, explosionInfo);
				
				local pIntVec = sq_GetGlobalIntVector(); 
				sq_IntVectorClear(pIntVec); 
				sq_IntVectorPush(pIntVec, 0); 
				sq_AddSetStatePacketCollisionObject(Monster, 5, pIntVec, STATE_PRIORITY_USER, true);
				Monster.flushSetStatePacket();
			}
		}
	}
	
	setMyCharacterNoShake(obj);

	local isAppend1;
	local isAppend2;
	local isAppend3;
	local isAppend4;

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000101.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000101)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000101.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000101)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000101.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000102.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000102)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000102.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000102)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000102.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000103.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000103)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000103.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000103)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000103.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000104.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000104)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000104.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000104)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000104.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000105.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000105)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000105.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000105)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000105.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000106.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000106)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000106.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000106)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000106.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000107.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000107)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000107.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000107)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000107.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000108.nut");
	if(!isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000108)
			{
				isInQuickSlot = true;
			}
		}
		if(isInQuickSlot)
		{
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000108.nut", true);
		}
	}
	else if(isAppend1)
	{
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for(local i=0;i<size;++i)
		{
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if(itemIndex == 100000108)
			{
				isInQuickSlot = true;
			}
		}
		if(!isInQuickSlot)
		{
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000108.nut");
			appendage.setValid(false);
		}
	}
}

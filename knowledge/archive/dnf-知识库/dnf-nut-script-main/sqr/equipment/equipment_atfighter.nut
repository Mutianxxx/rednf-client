
function isUsableItem_ATFighter(obj, itemIndex)
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

function drawMainCustomUI_ATFighter(obj)
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

function procAppend_ATFighter(obj)
{
	if(!obj) return 0;
	procAppend_AllGrowJob(obj);
	if (obj.isMyControlObject()&&(sq_getGrowType(obj) == 2)&&(!sq_isPVPMode())) {
		local index = obj.getCurrentSkillIndex();
		if (index == 82) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_randomkickfollow.nut" )) {
				CNSquirrelAppendage.sq_AppendAppendage ( obj, obj, index, false, "apjh/ap_randomkickfollow.nut", true );
			}
		} else {
			if (CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_randomkickfollow.nut" )) {
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "apjh/ap_randomkickfollow.nut");
			}
		}
	}

	if (obj.isMyControlObject()&&(sq_getGrowType(obj) == 3)&&(!sq_isPVPMode())) {
		local index = obj.getCurrentSkillIndex();

		if (index == 77 && sq_IsMyCharacter(obj)) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_junkspin.nut" )) {
				CNSquirrelAppendage.sq_AppendAppendage ( obj, obj, index, false, "apjh/ap_junkspin.nut", true );
			}
		} else {
			if (CNSquirrelAppendage.sq_IsAppendAppendage ( obj, "apjh/ap_junkspin.nut" )) {
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "apjh/ap_junkspin.nut");
			}
		}
	}
	
	local skilllevel = sq_GetSkillLevel(obj, 109);
	local smartthrowskill = sq_GetSkill(obj, 109);
	if(skilllevel > 0&& smartthrowskill && !smartthrowskill.isSealFunction())
	{
		local index = obj.getCurrentSkillIndex();
		local state = obj.sq_GetState();
    		if (index == -1 && obj.getVar("autoSmartThrow").getInt(0) != 1 && state == STATE_STAND) {
        		obj.sq_IntVectClear();
        		obj.sq_IntVectPush(109);
        		obj.sq_AddSetStatePacket(17, STATE_PRIORITY_USER, true);
        		obj.getVar("autoSmartThrow").setInt(0, 1);
    		}
    
    		if (state == 35 || state == 39 || state == 64 || state == 40) {
        		obj.getVar("autoSmartThrow").setInt(0, 0);
    		}
	}
	
	setMyCharacterNoShake(obj);
	
	spiralgaleforce1(obj);
	
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
			if (Monster.getState() != 5 && Monster.getCollisionObjectIndex() == 60066 && Monster.isMyControlObject()) {
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

function spiralgaleforce1(obj)
{
local skillLevel = sq_GetSkillLevel(obj, 253);
if(skillLevel<=0) return;
SpiralNen21085(obj);
SpiralNen21067(obj);
//creatFollowedAni(obj, 21056, "passiveobject/chang_qing_skill/atfighter/animation/atspiralgaleforce/forcel_loop_09.ani",  1.0, 1.0, 0, 0, 0, true,6);//ï¿??ï¿??ï¿??ï¿?
}





function SpiralNen21085(obj)
{
	//21085
	local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut");
	if(isAppend)
	{
		local count = obj.getMyPassiveObjectCount(21085);
		for(local i=0;i<count;++i)
		{
			local object = obj.getMyPassiveObject(21085, i);
			if(!object) continue;
			local aRange = 170;//ï¿??ï¿?
			local sizeRate = 100+aRange;
			sizeRate = sizeRate.tofloat()/100.0;
			local pAni = object.getCurrentAnimation();
			local isEtc = object.isCurrentAnimationIndex(0);
			if(!object.getVar("Whatever1").getBool(0))
			{
				object.getVar("Whatever1").setBool(0, true);
				pAni.setImageRateFromOriginal(sizeRate, sizeRate);//ï¿??Ê¥ani Î°ï¿?? ï¿??ï¿??ï¿??
				pAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);//ï¿??Ê¥ani alsÝ¾Ê¥ aniï¿??ï¿??ï¿??ï¿?
				sq_SetAttackBoundingBoxSizeRate(pAni, sizeRate, sizeRate, sizeRate);//ï¿??Ìª?ï¿??x y zï¿??ï¿??
	
			}
	
		}
	}
}

function SpiralNen21067(obj)
{

	local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut");
	if(isAppend)
	{
		local count = obj.getMyPassiveObjectCount(21067);
		for(local i=0;i<count;++i)
		{
			local object = obj.getMyPassiveObject(21067, i);
			if(!object) continue;
			local aRange = 100;//ï¿??ï¿?
			local sizeRate = 100+aRange;
			sizeRate = sizeRate.tofloat()/100.0;
			local pAni = object.getCurrentAnimation();
			local isEtc = object.isCurrentAnimationIndex(0);
			if(!object.getVar("Whatever").getBool(0))
			{
				object.getVar("Whatever").setBool(0, true);
				pAni.setImageRateFromOriginal(sizeRate, sizeRate);//ï¿??Ê¥ani Î°ï¿?? ï¿??ï¿??ï¿??
				pAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);//ï¿??Ê¥ani alsÝ¾Ê¥ aniï¿??ï¿??ï¿??ï¿?
				sq_SetAttackBoundingBoxSizeRate(pAni, sizeRate, sizeRate, sizeRate);//ï¿??Ìª?ï¿??x y zï¿??ï¿??
	
			}
	
		}
	}
}


function isUsableItem_Mage(obj, itemIndex) {
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

function drawMainCustomUI_Mage(obj) {
	if (!obj) return;
	obj.getVar("itemIndex").clear_vector();
	local slotNum = 6;
	for (local i = 0; i < slotNum; ++i) {
		obj.getVar("itemIndex").push_vector(i);
	}

	drawNewDamageUI_AllGrowJob(obj);

}

function procAppend_Mage(obj) {
	if (!obj) return 0;
	procAppend_AllGrowJob(obj);
	if (obj.isDead()) {
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/avatar/ap_avatar_icon.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/avatar/ap_avatar.nut");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/doll/ap_doll.nut");
	}
	local mageNowState = obj.sq_GetState();
	//local mageDashT = obj.getTimer( ).Get( );
	if (mageNowState == 14) {
		if (!obj.getVar("dashSound").getBool(0)) {
			obj.sq_PlaySound("WIZ_DASH");
			obj.getVar("dashSound").setBool(0, true);
		}
	} else {
		obj.getVar("dashSound").setBool(0, false);
	}
	//`WIZ_DASH`

	if (obj.isMyControlObject() && (sq_getGrowType(obj) == 4) && (!sq_isPVPMode())) {
		//üòö¢Ó×îñÐüÒöøºûÜ
		local index = obj.getCurrentSkillIndex();

		//ï³÷²÷­â¢
		if (index == 105) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "apjh/ap_fluorecollider.nut")) {
				CNSquirrelAppendage.sq_AppendAppendage(obj, obj, index, false, "apjh/ap_fluorecollider.nut", true);
			}
		} else {
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "apjh/ap_fluorecollider.nut")) {
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "apjh/ap_fluorecollider.nut");
			}
		}

	}

	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/controldoll/ap_controldoll.nut"))
	{
		local attackinfo = sq_GetCurrentAttackInfo(obj);
		if(attackinfo){
			if(!attackinfo.isValidElement(ENUM_ELEMENT_DARK))
				attackinfo.setElement(ENUM_ELEMENT_DARK); 
			//attackInfo.setAttackType(ATTACKTYPE_MAGICAL);
		}
		sq_ReleaseActiveStatus(obj, ACTIVESTATUS_CURSE);
	}
	
	if (obj.isMyControlObject() && (sq_getGrowType(obj) == 1) && (!sq_isPVPMode())) {
		//üòö¢Ó×îñÐüÒöøºûÜ
		local index = obj.getCurrentSkillIndex();
		local indexTemp = obj.getVar("currentSkillIndex").getInt(0);
		if (index != -1 && index != indexTemp) {
			obj.getVar("currentSkillIndex").setInt(0, index);
		} else {
			index = indexTemp;
		}
		local nowState = obj.sq_GetState();
		local appendage2;
		//ì¹ÔÑã¿Ûö
		//êªáÈñýØ­¡¢êªáÈòè÷¹¡¢?ÖÄâ©ïÜ¡¢ð¯×¿êªáÈ
		local mapIndex = sq_GetMapIndex(sq_GetGlobaludpModuleStage());
		local nowState = obj.sq_GetState();
		local nowStateTemp = obj.getVar("nowState").getInt(0);
		local mapIndexTemp = obj.getVar("mapIndex").getInt(0);
		local mapFlag = false;

		if (nowState != nowStateTemp) {

			if (mapIndex != mapIndexTemp) {
				obj.getVar("mapIndex").setInt(0, mapIndex);
				if (nowStateTemp == 249 || nowStateTemp == 250 || nowStateTemp == 251 || nowStateTemp == 253) mapFlag = true;
				obj.getVar("currentSkillIndex").setInt(0, 0);
			}
			obj.getVar("nowState").setInt(0, nowState);
		}

		local icefield = obj.getMyPassiveObject(23027, 0);
		if (icefield) {

			obj.setSkillCommandEnable(59, false);
		}
		else {
			if (nowState == STATE_STAND) {
				obj.setSkillCommandEnable(59, true);
			}
		}
		//ÓáÐüÒöÎ¦Óñ
		local appendage1;
		if ((index == 249 || index == 250 || index == 251 || index == 253) && mapFlag) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_magefollowmap.nut")) {
				obj.getVar("followSkillIndex").setInt(0, index);
				appendage1 = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, index, false, "character/mage/appendage/ap_magefollowmap.nut", true);
			}
		}
		else {
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_magefollowmap.nut")) {
				if (!appendage1.isValid()) {
					CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/appendage/ap_magefollowmap.nut");
				}
			}
		}
	}
	
	setMyCharacterNoShake(obj);
	
	local isAppend1;
	local isAppend2;
	local isAppend3;
	local isAppend4;

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000101.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			
			if (itemIndex == 100000101) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000101.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000101) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000101.nut");
			appendage.setValid(false);
		}
	}
	
	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000102.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000102) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000102.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000102) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000102.nut");
			appendage.setValid(false);
		}
	}
	
	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000103.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000103) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000103.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000103) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000103.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000104.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000104) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000104.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000104) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000104.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000105.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000105) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000105.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000105) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000105.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000106.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000106) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000106.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000106) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000106.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000107.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000107) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000107.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000107) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000107.nut");
			appendage.setValid(false);
		}
	}

	isAppend1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "equipment/ap/ap_100000108.nut");
	if (!isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000108) {
				isInQuickSlot = true;
			}
		}
		if (isInQuickSlot) {
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, "equipment/ap/ap_100000108.nut", true);
		}
	}
	else if (isAppend1) {
		local isInQuickSlot = false;
		local size = obj.getVar("itemIndex").size_vector();
		for (local i = 0; i < size; ++i) {
			local itemIndex = obj.getVar("itemIndex").get_vector(i);
			if (itemIndex == 100000108) {
				isInQuickSlot = true;
			}
		}
		if (!isInQuickSlot) {
			local appendage = obj.GetSquirrelAppendage("equipment/ap/ap_100000108.nut");
			appendage.setValid(false);
		}
	}
}


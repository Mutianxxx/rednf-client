function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_icefield")
}


function proc_appendage_icefield(appendage) {
	if (!appendage) {
		appendage.setValid(false);
		return;
	}

	local obj = sq_GetCNRDObjectToSQRCharacter(appendage.getParent());
	if (!obj) {
		appendage.setValid(false);
		return;
	}
	local skill = sq_GetSkill(obj, 167);
	if (!skill) {
		appendage.setValid(false);
		return;
	}
	if (skill.isSealFunction()) {
		appendage.setValid(false);
		return;
	}

	local icefield = obj.getMyPassiveObject(23027, 0);
	local chargetimer = appendage.getTimer().Get();
	if (icefield) {
		local x = obj.getXPos();
		local y = obj.getYPos(); //Íªß©ĞüÒöüùÍı?Óßñ¦øö£¬ì¤øµñıı¨óÜËïîÜĞüÒöüùÍıêÈöÇÍ³ïÒ
		if (obj.getDirection() == ENUM_DIRECTION_RIGHT) {
			x = x + 300;
		} else {
			x = x - 300;
		}
		if (sq_IsMyCharacter(obj)) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
			createIce(obj, x, y, chargetimer); //óÜËïĞüÒöüùÍı
			obj.getVar("currentSkillIndex").setInt(0, 0);
		}
	}
}

function createIce(obj, x, y, timer) {
	if (!obj) {
		return;
	}
	if (obj.isMyControlObject()) {
		obj.sq_StartWrite();
		obj.sq_WriteDword(1);
		sq_SendCreatePassiveObjectPacketPos(obj, 23027, 0, x, y, 0);
		local isShowTime = obj.getVar("isShowTime").getInt(0);
		local chargetimer = timer - 350;
		if (chargetimer < 1) {
			chargetimer = 1;
		}
		local mageshowpre = 1;
		local mageshow_level;
		if (isShowTime == 1) {
			mageshow_level = sq_GetSkillLevel(obj, 2);
			mageshowpre = 1 - sq_GetLevelData(obj, 2, 3, mageshow_level).tofloat() / 1000;
			if (mageshowpre < 0) {
				mageshowpre = 0;
			}
		}
		local chargepre = 1 - (800 * mageshowpre + 1) / chargetimer;
		if (chargepre < 0) {
			chargepre = 0;
		}
		local level = sq_GetSkillLevel(obj, 59);
		local iceAreaSizeLow = sq_GetLevelData(obj, 59, 2, level);
		local iceAreaSize = sq_GetLevelData(obj, 59, 3, level);
		local iceAreaRate = (iceAreaSize - iceAreaSizeLow) * chargepre * 0.0023 + iceAreaSizeLow * 0.0023;
		local lifeTime = (chargepre * 1000).tointeger();
		local iceRainCount = sq_GetIntData(obj, 59, 5, level);
		local iceRate = sq_GetLevelData(obj, 59, 5, level);
		local iceLevel = sq_GetLevelData(obj, 59, 6, level);
		local iceTime = sq_GetLevelData(obj, 59, 7, level);

		sq_BinaryStartWrite();
		sq_BinaryWriteFloat(iceAreaRate); // static : ï¿??ï¿??ï¿?? ?ï¿??
		sq_BinaryWriteDword(lifeTime); // 0.ï¿??ï¿????
		sq_BinaryWriteDword(iceRainCount); // 2.ï¿??ï¿???ï¿???ï¿?? ï¿??ï¿?? ï¿??ï¿??
		sq_BinaryWriteDword(iceRate); // 3.ï¿??ï¿?? ?ï¿??
		sq_BinaryWriteDword(iceLevel); // 4.ï¿??ï¿?? ï¿??ï¿??
		sq_BinaryWriteDword(iceTime); // 5.ï¿??ï¿?? ï¿???			
		obj.sq_SendCreatePassiveObjectPacket(24382, 0, 300, 1, 0);
	}
}

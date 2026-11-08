

function onAfterSetState_priest_buff(obj, state, datas, isResetTimer) {
	if (!obj) return;
	if (!obj.sq_IsMyControlObject()) return;
	local BuffSkillIndex = obj.getBuffSkillIndex();
	print("BuffSkillIndex:" + BuffSkillIndex);
	switch (BuffSkillIndex) {
		case 47:
		case 48:
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(1);
			sq_SendChangeSkillEffectPacket(obj, BuffSkillIndex);
			break;
	}
};


function onAfterSetState_Priest_Throw(obj, state, datas, isResetTimer)
{
	local skillIndex = obj.getThrowIndex();
	switch(skillIndex)
	{
		case 112:
		case 45:
			if(obj.getThrowState() == 1 && obj.sq_GetSkillLevel(112) > 0)
				ChangQing_751675335_DivineFlash(obj, state, datas, isResetTimer)
			break;
		case 131: 
 			if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_fallingsoul.nut"))
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_priest/appendage/ap_fallingsoul.nut");
			local validTime = obj.sq_GetLevelData(131, 1, sq_GetSkillLevel(obj, 131)); 
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 131, true, "character/new_priest/appendage/ap_fallingsoul.nut", false);
			appendage.sq_SetValidTime(validTime); 
			CNSquirrelAppendage.sq_Append(appendage, obj, obj, false);
			break;
		case 10: 
			//local recValue = sq_GetLevelData(obj, 10, 2, obj.sq_GetSkillLevel(10));
			//setDevilGauge(obj, getDevilGauge(obj) + recValue.tointeger()); 
			break;
	}
};
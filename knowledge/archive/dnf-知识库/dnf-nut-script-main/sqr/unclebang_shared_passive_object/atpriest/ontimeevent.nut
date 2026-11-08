 
function onTimeEvent_po_atpriest_shared(obj, timeEventIndex, timeEventCount) {
	if (!obj)
		return false;
	local type = obj.getVar("type").get_vector(0);
	local id = obj.getVar("id").get_vector(0);
	local posX = sq_GetXPos(obj);
	local posY = sq_GetYPos(obj);
	local posZ = sq_GetZPos(obj);
	local chr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	switch (timeEventIndex) 
	{
	case 0:
		obj.resetHitObjectList();
		break;
	case 1:
		sq_SendDestroyPacketPassiveObject(obj);
		break;
	case 9:
		local count = sq_GetIntData(chr, SKILL_IMMOBILITYMAGICLINE, 0);
		if (timeEventCount < count) {
			obj.resetHitObjectList();
		}
		else
		{
			obj.removeAllTimeEvent();
			local bonus = obj.getVar("immobilitymagiclineDamageBonus").get_vector(0);
			sq_IntVectorClear(sq_GetGlobalIntVector());
			sq_IntVectorPush(sq_GetGlobalIntVector(), bonus);
			obj.addSetStatePacket(12, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
		}
		break;
	}

}
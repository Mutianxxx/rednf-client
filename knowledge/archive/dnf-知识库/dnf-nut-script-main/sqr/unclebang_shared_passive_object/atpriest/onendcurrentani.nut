function onEndCurrentAni_po_atpriest_shared(obj)

{
	if (!obj) return;
	local UncleBangValue1 = obj.getVar("type").get_vector(0);
	local UncleBangValue2 = obj.getVar("id").get_vector(0);
	local UncleBangValue3 = sq_GetXPos(obj);
	local UncleBangValue4 = sq_GetYPos(obj);
	local UncleBangValue5 = sq_GetZPos(obj);
	local chr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	switch (UncleBangValue1) {
	case 3:
		switch (UncleBangValue2) {
		case 4:
		case 7:
		case 8:
			if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
			break;
		case 0:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 10:
				obj.sendStateOnlyPacket(11);
				obj.flushSetStatePacket();
				break;
			case 12:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 1:
			local UncleBangValue8 = obj.getVar("rosarybeadIndex").get_vector(0);
			if (UncleBangValue8 == 0) {
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
			}
			if (UncleBangValue8 > 0 && obj.getVar("state").get_vector(0) == 10) {
				obj.sendStateOnlyPacket(11);
				obj.flushSetStatePacket();
			}
			break;
		case 3:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 11:
				sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 6:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 12:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 9:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 10:
				local UncleBangValue12 = obj.getVar("immobilitymagiclineDamageBonus").get_vector(0);
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), UncleBangValue12);
				obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
				break;
			case 12:
				sq_removePooledObject(obj);
				local sq_var = chr.getVar("immobility");
				local append = "character/atpriest/3_sorceress/immobilitymagicline/ap_immobilitymagicline.nut";
				local objectsSize = sq_var.get_obj_vector_size();
				for (local i = 0; i < objectsSize; ++i) {
					local damager = sq_var.get_obj_vector(i);
					if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, append)) {
						CNSquirrelAppendage.sq_RemoveAppendage(damager, append);
					}
				}
				sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 10:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 10:
				obj.sendStateOnlyPacket(11);
				obj.flushSetStatePacket();
				break;
			case 12:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 11:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 12:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 12:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 10:
				obj.sendStateOnlyPacket(11);
				obj.flushSetStatePacket();
				break;
			case 11:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 13:
			local UncleBangValue7 = obj.getVar("state").get_vector(0);
			switch (UncleBangValue7) {
			case 10:
				local UncleBangValue12 = obj.getVar("bigrosaryDamageBonus").get_vector(0);
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), UncleBangValue12);
				obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
				break;
			case 11:
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
				break;
			}
			break;
		case 14:
			local UncleBangValue19 = obj.getVar("swallowskydrgonDistinguish").get_vector(0);
			if (UncleBangValue19 == 0) {
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
			}
			if (UncleBangValue19 == 1) {
				if (obj.isMyControlObject()) sq_SendDestroyPacketPassiveObject(obj);
			}
			break;
		}
		break;
	}

}


function onEndCurrentAni_po_qq506807329new_atmage_24377(obj) {
	if (!obj) return;
	local ZEJlR93Xfq3u0L_E3MG4q = obj.getVar("skill").get_vector(0);
	local subtype = obj.getVar("subType").get_vector(0);
	local stateindex = obj.getVar("state").get_vector(0);
	switch (ZEJlR93Xfq3u0L_E3MG4q) {
		case 125:
			if (!obj.isMyControlObject()) return;
			sq_SendDestroyPacketPassiveObject(obj);
			break;
		case 243:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					if (stateindex != 12)
						obj.addSetStatePacket(stateindex + 1, null, STATE_PRIORITY_AUTO, false, "");
					break;
			}
			break;
		case 244:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					if (stateindex != 12)
						obj.addSetStatePacket(stateindex + 1, null, STATE_PRIORITY_AUTO, false, "");
					else
						sq_SendDestroyPacketPassiveObject(obj);
					break;
			}
			break;
		case 245:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					if (stateindex == 12)
						sq_SendDestroyPacketPassiveObject(obj);
					break;
				case 2:
					sq_SendDestroyPacketPassiveObject(obj);
					break;
			}
			break;
		case 246:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					if (stateindex == 10) {
						if (obj.isMyControlObject()) {

							local mage = obj.getTopCharacter();
							mage = sq_ObjectToSQRCharacter(mage);
							if (mage) {
								local atk = obj.getVar("damaRate").get_vector(0);
								local damager = obj.getVar("dama").get_obj_vector(0);

								if (damager) {
									sendIcecraft(mage, damager, atk);

								}

							}
						}
						sq_SendDestroyPacketPassiveObject(obj);
					}
					break;
			}
			break;
		case 247:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					sq_SendDestroyPacketPassiveObject(obj);
					break;
			}
			break;
		case 248:
			if (!obj.isMyControlObject()) return;
			switch (subtype) {
				case 1:
					if (stateindex != 14)
						obj.addSetStatePacket(stateindex + 1, null, STATE_PRIORITY_AUTO, false, "");
					else
						sq_SendDestroyPacketPassiveObject(obj);
					break;
			}
			break;
	}
};

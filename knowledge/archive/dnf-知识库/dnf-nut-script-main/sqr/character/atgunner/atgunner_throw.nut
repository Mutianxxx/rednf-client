

function onAfterSetState_atgunner_throw(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local index = obj.getThrowIndex();
	local throwState = obj.getThrowState();

	switch (index) {
		case 79:
		case 80:
		case 81:
			if (throwState == 1) {
				local SpeibDDQ8SST = onGetMyPassiveObject_My(obj, 24376, 247, 1);
				if (!SpeibDDQ8SST) break;
				if (SpeibDDQ8SST.isMyControlObject()) {
					local _GtjPdLd81TAJVN2eOy = index - 79 + 10;
					local tCl4O9m366ybTDH = SpeibDDQ8SST.getState();
					if (_GtjPdLd81TAJVN2eOy != tCl4O9m366ybTDH) {
						local FQwwgJmombIJ = -1;
						switch (tCl4O9m366ybTDH) {
							case 10:
								FQwwgJmombIJ = 5;
								break;
							case 11:
								FQwwgJmombIJ = 4;
								break;
							case 12:
								FQwwgJmombIJ = 5;
								break;
						}
						local EB3van5s9PmFHu2D6645Go = sq_GetGlobalIntVector();
						sq_IntVectorClear(EB3van5s9PmFHu2D6645Go);
						sq_IntVectorPush(EB3van5s9PmFHu2D6645Go, FQwwgJmombIJ);
						sq_IntVectorPush(EB3van5s9PmFHu2D6645Go, _GtjPdLd81TAJVN2eOy);
						SpeibDDQ8SST.addSetStatePacket(tCl4O9m366ybTDH, EB3van5s9PmFHu2D6645Go, STATE_PRIORITY_AUTO, false, "");
					}
				}
			}
			break;
		case 98:
			local zPos = obj.getZPos();
			if (zPos > 50) {
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_NITROMOTOR_SKY_THROW);
				obj.sq_ZStop();
			}
			break;
	}

};

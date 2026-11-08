function onAttack_po_atpriest_shared(obj, damager, boundingBox, isStuck) {
	if (!obj) return;
	local type = obj.getVar("type").get_vector(0);
	local id = obj.getVar("id").get_vector(0);
	local posX = sq_GetXPos(obj);
	local posY = sq_GetYPos(obj);
	local posZ = sq_GetZPos(obj);
	local chr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	switch (type) {
	case 3:
		switch (id) {
		case 3:
			local state = obj.getVar("state").get_vector(0);
			switch (state) {
			case 10:
			case 20:
				if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
					obj.sendStateOnlyPacket(11);
					obj.flushSetStatePacket();
				}
				break;
			case 11:
				obj.sq_RemoveMoveParticle();
				obj.setCustomRotate(true, sq_ToRadian(0.0));
				if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, chr, SKILL_TALISMANOFOPPRESSION, false, "character/atpriest/3_sorceress/talismanofoppression/ap_talismanofoppression.nut", true);
					if (appendage) {
						appendage.sq_SetValidTime(sq_GetLevelData(chr, SKILL_TALISMANOFOPPRESSION, 1, sq_GetSkillLevel(chr, SKILL_TALISMANOFOPPRESSION)));
					}
				}
				break;
			}
			break;
		case 4:
			if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
				local UncleBangValue9 = sq_CreateDrawOnlyObject(obj, "passiveobject/unclebang_shared_passive_object/atpriest/animation/3_sorceress/atexorcismus/exorcismus_hitpass.ani", ENUM_DRAWLAYER_NORMAL, true);
				UncleBangValue9.setCurrentPos(damager.getXPos(), damager.getYPos(), damager.getZPos() + sq_GetCenterZPos(boundingBox));
			}
			break;
		case 5:
			if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
				sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/ateffortsphere/effortsphere_explosion.ani", 0, 0, 0);
			}
			break;
		case 9:
			if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE)) {
				if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/3_sorceress/immobilitymagicline/ap_immobilitymagicline.nut")) break;
				chr.getVar("immobility").push_obj_vector(damager);
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, chr, SKILL_IMMOBILITYMAGICLINE, false, "character/atpriest/3_sorceress/immobilitymagicline/ap_immobilitymagicline.nut", true);
				if (appendage) {
					appendage.sq_SetValidTime(3000);
				}
			}
			break;
		}
		break;
	}

}
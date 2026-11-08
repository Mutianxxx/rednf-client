function setCustomData_po_mage_passiveobject(obj, receiveData) {

	local id = receiveData.readDword(); // ?????(%)
	if (id == 0) {
		local atk = receiveData.readDword(); // ?????(%)
		local sizeRate = receiveData.readDword();
		local ani = obj.getCustomAnimation(0);
		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, atk);

		local imageRate = sizeRate.tofloat() / 100.0;
		local currentAni = obj.getCurrentAnimation();
		currentAni.setImageRateFromOriginal(imageRate, imageRate);
		currentAni.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(currentAni, imageRate, imageRate, imageRate);
	} else if (id == 1) {
		local atk = receiveData.readDword(); // ?????(%)
		local ani = obj.getCustomAnimation(1);
		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, atk);
	} else if (id == 2) {
		local atk = receiveData.readDword(); // ?????(%)
		local ani = obj.getCustomAnimation(1);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, atk);
	} else if (id == 3) {
		local atk = receiveData.readDword();
		local ani = obj.getCustomAnimation(2);
		local attackInfo = sq_GetCustomAttackInfo(obj, 3);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, atk);
		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector(obj.getXPos());

	} else if (id == 4) {
		local dist = receiveData.readDword();
		local atk = receiveData.readDword();
		local count = receiveData.readDword();
		local time = receiveData.readDword();
		local upForce = receiveData.readDword();


		local height = obj.getZPos();
		local ani = obj.getCustomAnimation(3);
		obj.setCurrentAnimation(ani);

		obj.getVar("value").clear_vector();
		obj.getVar("value").push_vector(dist);
		obj.getVar("value").push_vector(height);
		obj.getVar("value").push_vector(obj.getXPos());
		obj.getVar("value").push_vector(atk);
		obj.getVar("value").push_vector(count);
		obj.getVar("value").push_vector(time);
		obj.getVar("value").push_vector(upForce);

	} else if (id == 5) {
		local saveT = receiveData.readDword()
		local ani = obj.getCustomAnimation(4);
		obj.setCurrentAnimation(ani);

		obj.getVar("t").clear_vector();
		obj.getVar("t").push_vector(saveT);

		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);

		obj.getVar("friend").clear_obj_vector();

		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local objectManager = mage.getObjectManager();

		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
			local object = objectManager.getCollisionObject(i);
			if (object && !obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE)) {
				obj.getVar("friend").push_obj_vector(object);
			}
		}
	}


	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);
}

function onKeyFrameFlag_po_mage_passiveobject(obj, flagIndex) {
	local id = obj.getVar("id").get_vector(0);
}

function procAppend_po_mage_passiveobject(obj) {
	local id = obj.getVar("id").get_vector(0);

	if (id == 5) {

		if (obj.getVar("state").get_vector(0) == 0) {
			local pAni = obj.getCurrentAnimation();
			local currentT = sq_GetCurrentTime(pAni);
			if (currentT > obj.getVar("t").get_vector(0)) {
				local ani = obj.getCustomAnimation(5);
				obj.setCurrentAnimation(ani);
				obj.getVar("state").set_vector(0, 1);


				local
				var = obj.getVar("friend");
				local objectsSize =
					var.get_obj_vector_size();
				if (objectsSize > 0) {
					for (local i = 0; i < objectsSize; ++i) {
						local friend =
							var.get_obj_vector(i);
						friend = sq_ObjectToSQRCharacter(friend);
						if (friend) {
							CNSquirrelAppendage.sq_RemoveAppendage(friend, "character/new_mage/blockforestcirrus/ap_blockforestcirrus.nut");

						}
					}
				}
			} else {

				local
				var = obj.getVar("friend");
				local objectsSize =
					var.get_obj_vector_size();
				if (objectsSize > 0) {
					for (local i = 0; i < objectsSize; ++i) {
						local friend =
							var.get_obj_vector(i);
						if (!friend) return;
						friend = sq_ObjectToSQRCharacter(friend);
						if (!friend) return;
						if (friend.sq_GetState() == STATE_JUMP && friend.getZPos() > 50) {
							if (!CNSquirrelAppendage.sq_IsAppendAppendage(friend, "character/new_mage/blockforestcirrus/ap_blockforestcirrus.nut")) {
								local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(friend, friend, SKILL_BLOCKFORESTCIRRUS, false, "character/new_mage/blockforestcirrus/ap_blockforestcirrus.nut", true);
								masterAppendage.getVar("pos").clear_vector();
								masterAppendage.getVar("pos").push_vector(obj.getXPos());
								masterAppendage.getVar("pos").push_vector(obj.getYPos());
							}
						}
					}
				}

			}

		}
	} else if (id == 4) {
		local pAni = obj.getCurrentAnimation();
		local currentT = sq_GetCurrentTime(pAni);

		if (currentT <= 240) {
			local len = obj.getVar("value").get_vector(0);
			local hei = obj.getVar("value").get_vector(1);
			local staX = obj.getVar("value").get_vector(2);

			local v1 = sq_GetAccel(0, len, currentT, 240, true);
			local v2 = sq_GetAccel(hei, 0, currentT, 240, true);

			local posX = sq_GetDistancePos(staX, obj.getDirection(), v1);
			local mage = obj.getTopCharacter();
			mage = sq_ObjectToSQRCharacter(mage);
			if (mage.isMovablePos(posX, obj.getYPos())) {
				sq_setCurrentAxisPos(obj, 0, posX);
			}
			sq_setCurrentAxisPos(obj, 2, v2);
		}


	} else if (id == 3) {
		local pAni = obj.getCurrentAnimation();
		local currentT = sq_GetCurrentTime(pAni);
		local maxT = 500;
		if (currentT <= maxT) {
			local pos = obj.getVar("pos").get_vector(0);
			local v = sq_GetUniformVelocity(0, 600, currentT, maxT);
			local dstX = sq_GetDistancePos(pos, obj.getDirection(), v);
			sq_setCurrentAxisPos(obj, 0, dstX);
		} else {
			sq_SetMyShake(obj, 5, 200);
			sq_SendCreatePassiveObjectPacketPos(obj, 12251, 0, obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
}

function onAttack_po_mage_passiveobject(obj, damager, boundingBox, isStuck) {
	local id = obj.getVar("id").get_vector(0);
	if (id == 3) {
		sq_SetMyShake(obj, 5, 200);
		sq_SendCreatePassiveObjectPacketPos(obj, 12251, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
		sq_SendDestroyPacketPassiveObject(obj);
	}
}

function onEndCurrentAni_po_mage_passiveobject(obj) {
	local id = obj.getVar("id").get_vector(0);
	if (id == 0) {
		sq_SendDestroyPacketPassiveObject(obj);
	} else if (id == 1) {
		sq_SendDestroyPacketPassiveObject(obj);
	} else if (id == 2) {
		sq_SendDestroyPacketPassiveObject(obj);
	} else if (id == 3) {
		sq_SendDestroyPacketPassiveObject(obj);
	} else if (id == 4) {
		sq_SetMyShake(obj, 5, 200);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(obj.getVar("value").get_vector(3));
		sq_BinaryWriteDword(67);
		sq_BinaryWriteDword(obj.getVar("value").get_vector(4));
		sq_BinaryWriteDword(obj.getVar("value").get_vector(5));
		sq_BinaryWriteDword(obj.getVar("value").get_vector(6));
		sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, obj.getXPos(), obj.getYPos() + 1, 0);
		sq_SendDestroyPacketPassiveObject(obj);

	} else if (id == 5) {
		sq_SendDestroyPacketPassiveObject(obj);
	}
}

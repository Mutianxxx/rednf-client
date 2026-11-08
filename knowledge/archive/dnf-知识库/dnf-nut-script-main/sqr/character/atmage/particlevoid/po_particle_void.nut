PARTICLE_VOLD_STATE_MYSELF <- 0 // ????A?U???H?H??
PARTICLE_VOLD_STATE_TO_ENEMY <- 1 //????A?U?l????H
PARTICLE_VOLD_STATE_RETRUN_MYSELF <- 2 //????A?U?????b??H???W
PARTICLE_VOLD_STATE_RETURN_MYSELF <- 2

function setCustomData_po_particle_void(obj, receiveData) {
	if (!obj) return;
	local id = receiveData.readDword();
	if (id == PARTICLE_VOLD_STATE_MYSELF) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(PARTICLE_VOLD_STATE_MYSELF);
		obj.getVar("subState").clear_vector();
		obj.getVar("subState").push_vector(0);
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
}

function setState_po_particle_void(obj, state, datas) {
	if(!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == PARTICLE_VOLD_STATE_MYSELF) {
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {
			local ani = obj.getCustomAnimation(0);
			obj.setCurrentAnimation(ani);
		} else if (subState == 1) {
			local ani = obj.getCustomAnimation(1);
			obj.setCurrentAnimation(ani);
		} else if (subState == 2) {
			local ani = obj.getCustomAnimation(2);
			obj.setCurrentAnimation(ani);
		}
	} else if (state == PARTICLE_VOLD_STATE_TO_ENEMY) {
		local subState = obj.getVar("subState").get_vector(0);
		local tar = obj.getVar("tar").get_obj_vector(0);

		if (subState == 0) {
			local ani = obj.getCustomAnimation(3);
			obj.setCurrentAnimation(ani);

		} else if (subState == 1) {
			local ani = obj.getCustomAnimation(4);
			obj.setCurrentAnimation(ani);
			local attackInfo = sq_GetCustomAttackInfo(obj, 0);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			obj.getVar("len").clear_vector();
			obj.getVar("len").push_vector(obj.getXPos());
			obj.getVar("len").push_vector(obj.getYPos());
			obj.getVar("len").push_vector(250);
		} else if (subState == 2) {
			if (tar) {
				tar = sq_GetCNRDObjectToActiveObject(tar);
				local mage = obj.getTopCharacter();
				mage = sq_ObjectToSQRCharacter(mage);
				if (mage) {
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, -1, false, "character/atmage/particlevoid/ap_particle_void_to_enemy.nut", true);
					CNSquirrelAppendage.sq_Append(appendage, tar, obj);
					if (appendage) {
						local atkRate = sq_GetLevelData(mage, SKILL_PARTICLE_VOLD, 2, mage.sq_GetSkillLevel(SKILL_PARTICLE_VOLD)) / 10;
						appendage.getVar("atkRate").clear_vector();
						appendage.getVar("atkRate").push_vector(atkRate);
					}
				}
			}
			local ani = obj.getCustomAnimation(1);
			obj.setCurrentAnimation(ani);
			sq_SetMyShake(obj, 1, 100);

		} else if (subState == 3) {
			local ani = obj.getCustomAnimation(7);
			obj.setCurrentAnimation(ani);
		}
	} else if (state == PARTICLE_VOLD_STATE_RETRUN_MYSELF) {

		obj.getVar("len").clear_vector();
		obj.getVar("len").push_vector(obj.getXPos());
		obj.getVar("len").push_vector(obj.getYPos());
		obj.getVar("len").push_vector(250);
		local ani = obj.getCustomAnimation(6);
		obj.setCurrentAnimation(ani);
	}
	local animation = sq_GetCurrentAnimation(obj);
	sq_SetAnimationCurrentTimeByFrame(animation, 0, false);

}

function onEndCurrentAni_po_particle_void(obj) {
	if (!obj) return;
	if (!obj.isMyControlObject())
		return false;
	local state = obj.getVar("state").get_vector(0);
	if (state == PARTICLE_VOLD_STATE_MYSELF) {
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {
			obj.getVar("subState").clear_vector();
			obj.getVar("subState").push_vector(1);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
		} else if (subState == 2) {
			sq_SendDestroyPacketPassiveObject(obj);
		}
	} else if (state == PARTICLE_VOLD_STATE_TO_ENEMY) {
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {
			obj.getVar("subState").clear_vector();
			obj.getVar("subState").push_vector(1);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");
		} else if (subState == 3) {
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(PARTICLE_VOLD_STATE_RETURN_MYSELF);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(12, pIntVec, STATE_PRIORITY_AUTO, false, "");
		}
	}
}

function procAppend_po_particle_void(obj) {
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	local mage = obj.getTopCharacter();
	mage = sq_ObjectToSQRCharacter(mage);
	if (mage.isDead()) {
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (state == PARTICLE_VOLD_STATE_MYSELF) {
		local mage = obj.getTopCharacter();
		if (mage) {
			mage = sq_ObjectToSQRCharacter(mage);
			obj.setCurrentPos(mage.getXPos(), mage.getYPos() + 1, 0);
		}
	} else if (state == PARTICLE_VOLD_STATE_TO_ENEMY) {
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 1) {
			local animation = sq_GetCurrentAnimation(obj);
			local currentT = sq_GetCurrentTime(animation);
			local startX = obj.getVar("len").get_vector(0);
			local startY = obj.getVar("len").get_vector(1);
			local maxTime = obj.getVar("len").get_vector(2);
			local tar = obj.getVar("tar").get_obj_vector(0);
			if (tar)
			{
				local tarX = tar.getXPos();
				local tarY = tar.getYPos();
				if (currentT < maxTime) {
					local posX = sq_GetUniformVelocity(startX, tarX, currentT, maxTime);
					local posY = sq_GetUniformVelocity(startY, tarY, currentT, maxTime);
					obj.setCurrentPos(posX, posY, 0);
				} else {
					obj.getVar("subState").clear_vector();
					obj.getVar("subState").push_vector(3);
					local pIntVec = sq_GetGlobalIntVector();
					sq_IntVectorClear(pIntVec);
					sq_IntVectorPush(pIntVec, 0);
					obj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");
				}
			} else {
				obj.getVar("subState").clear_vector();
				obj.getVar("subState").push_vector(3);
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 0);
				obj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");
			}
		} else if (subState == 2) {
			local tar = obj.getVar("tar").get_obj_vector(0);
			if (tar) {
				obj.setCurrentPos(tar.getXPos(), tar.getYPos() + 1, 0);
			} else {
				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(PARTICLE_VOLD_STATE_RETURN_MYSELF);
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 0);
				obj.addSetStatePacket(12, pIntVec, STATE_PRIORITY_AUTO, false, "");
			}
		}
	} else if (state == PARTICLE_VOLD_STATE_RETRUN_MYSELF) {
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		if (mage) {
			local animation = sq_GetCurrentAnimation(obj);
			local currentT = sq_GetCurrentTime(animation);
			local startX = obj.getVar("len").get_vector(0);
			local startY = obj.getVar("len").get_vector(1);
			local maxTime = obj.getVar("len").get_vector(2);
			if (mage)
			{
				local tarX = mage.getXPos();
				local tarY = mage.getYPos();
				if (currentT < maxTime) {
					local posX = sq_GetUniformVelocity(startX, tarX, currentT, maxTime);
					local posY = sq_GetUniformVelocity(startY, tarY, currentT, maxTime);
					obj.setCurrentPos(posX, posY, 0);
				} else {
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(PARTICLE_VOLD_STATE_MYSELF);
					obj.getVar("subState").clear_vector();
					obj.getVar("subState").push_vector(0);
					local pIntVec = sq_GetGlobalIntVector();
					sq_IntVectorClear(pIntVec);
					sq_IntVectorPush(pIntVec, 0);
					obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
				}
			}
		}
	}
}

function onAttack_po_particle_void(obj, damager, boundingBox, isStuck) {
	if (!obj) return;
	if (!damager) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == PARTICLE_VOLD_STATE_TO_ENEMY) {
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 1) {
			obj.getVar("tar").clear_obj_vector();
			obj.getVar("tar").push_obj_vector(damager);
			obj.getVar("subState").clear_vector();
			obj.getVar("subState").push_vector(2);
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");
		}
	}
}

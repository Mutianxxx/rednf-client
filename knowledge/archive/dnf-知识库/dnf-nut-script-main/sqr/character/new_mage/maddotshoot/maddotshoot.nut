function checkExecutableSkill_maddotshoot(obj) {
	if (!obj) return false;

	if (!isDollState(obj)) {

		local state = getDotObj(obj).getVar("state").get_vector(0);
		if (state == 0 || state == 1 || state == 2) {
			local isUseSkill = obj.sq_IsUseSkill(SKILL_MADDOTSHOOT);
			if (obj.sq_GetState() == 0 || obj.sq_GetState() == 8 || obj.sq_GetState() == 14) {
				if (isUseSkill) {
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(0);
					obj.sq_AddSetStatePacket(STATE_MADDOTSHOOT, STATE_PRIORITY_USER, true);
				}
			} else {
				if (isUseSkill) {
					sendDotMadDotShoot(obj)
				}
			}


		}
	} else {

		local isUseSkill = obj.sq_IsUseSkill(SKILL_MADDOTSHOOT);
		if (isUseSkill) {
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(1);
			obj.sq_AddSetStatePacket(STATE_MADDOTSHOOT, STATE_PRIORITY_USER, true);
		}
	}

	return false;
}


function checkCommandEnable_maddotshoot(obj) {

	if (!isDollState(obj)) {
		return true;
	} else {
		if (obj.sq_GetState() == 0 || obj.sq_GetState() == 8 || obj.sq_GetState() == 14)
			return true;
	}
	return false;
}

function createHitEffectMadDotShoot(obj, damager, x, y, z) {

	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/madattackeffect_07.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), x);
	pooledObj.setCurrentPos(posX, damager.getYPos() + y, damager.getZPos() + z);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function createHitEffectMadDotShoot2(obj, damager, x, y, z) {

	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/hiteffect_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), x);
	pooledObj.setCurrentPos(posX, damager.getYPos() + y, damager.getZPos() + z);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function sendDotMadDotShoot(obj) {
	if (!obj) {
		return;
	}
	local dot = getDotObj(obj);
	if (dot) {
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_MADDOTSHOOT, STATE_MADDOTSHOOT, 0, 1.0);
		local size = obj.sq_GetIntData(SKILL_MADDOTSHOOT, 2);
		dot.getVar("state").clear_vector();
		dot.getVar("state").push_vector(11);
		dot.getVar("substate").clear_vector();
		dot.getVar("substate").push_vector(0);
		dot.getVar("value").clear_vector();
		dot.getVar("value").push_vector(damage);
		dot.getVar("value").push_vector(size);
		local pIntVec = sq_GetGlobalIntVector();
		dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
}

function onSetState_MADDOTSHOOT(obj, state, datas, isResetTimer) {
	if (!obj) {
		return;
	}
	local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
	local x = obj.getXPos();
	local y = obj.getYPos() + 1;
	if (state == 0) {
		sendDotMadDotShoot(obj);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MADDOTSHOOT);
	} else if (state == 1) {
		local ani = obj.getVar().GetAnimationMap("maddotshoot0", "passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/boby/mada_body.ani");
		obj.setCurrentAnimation(ani);
	} else if (state == 2) {
		local dot = getDotObj(obj);
		if (dot) {
			x = dot.getXPos();
			y = dot.getYPos() + 1;
		}
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_MADDOTSHOOT, STATE_MADDOTSHOOT, 0, 1.0);
		local size = obj.sq_GetIntData(SKILL_MADDOTSHOOT, 2);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(damage);
		sq_BinaryWriteDword(16);
		sq_BinaryWriteDword(size);
		createPassiveAndDirection(obj, obj, 24364, 0, x, y, 0);
		local ani = obj.getVar().GetAnimationMap("maddotshoot1", "passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/boby/madb2_body.ani");
		obj.setCurrentAnimation(ani);
	} else if (state == 3) {
		local ani = obj.getVar().GetAnimationMap("maddotshoot2", "passiveobject/zrr_skill/newmage/animation/dot/maddotshoot/boby/madc2_body.ani");
		obj.setCurrentAnimation(ani);
	}

}

function onEndCurrentAni_MADDOTSHOOT(obj) {
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	} else if (state == 1) {
		obj.getVar("state").set_vector(0, 2);
		obj.sq_AddSetStatePacket(STATE_MADDOTSHOOT, STATE_PRIORITY_USER, true);
	} else if (state == 2) {
		obj.getVar("state").set_vector(0, 3);
		obj.sq_AddSetStatePacket(STATE_MADDOTSHOOT, STATE_PRIORITY_USER, true);
	} else if (state == 3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
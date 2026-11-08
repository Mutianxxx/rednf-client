function checkExecutableSkill_assassination(obj) {
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_ASSASSINATION);
	if (isUseSkill) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_ASSASSINATION, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_assassination(obj) {

	return true;
}


function createAssassinationFrontFinishAtkBlood(obj, damager) {
	local ani = sq_CreateAnimation("", "character/thief/animation/als_ani/assassination/frontattack/atk_a_blood.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function createAssassinationFrontFinishLight(obj, damager) {
	local ani = sq_CreateAnimation("", "character/thief/animation/als_ani/assassination/assassination/finish_light_a.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function onKeyFrameFlag_ASSASSINATION(obj, flagIndex) {
	local state = obj.getVar("state").get_vector(0);
	if (obj.getVar("flag").get_vector(flagIndex) == 0) {
		obj.getVar("flag").set_vector(flagIndex, 1);
        local objectsSize = obj.getVar("dama").get_obj_vector_size();
        if (objectsSize > 0) {
            for (local i = 0; i < objectsSize; ++i) {
                local tar = obj.getVar("dama").get_obj_vector(i);
                if (tar.isObjectType(OBJECTTYPE_ACTIVE)) {
                    if (flagIndex == 0) {
                        if (state == 1 || state == 2) {
                            CNSquirrelAppendage.sq_RemoveAppendage(tar, "character/thief/4_shadow/assassination/ap_assassination_success_width.nut");
                            CNSquirrelAppendage.sq_RemoveAppendage(tar, "character/thief/4_shadow/assassination/ap_assassination_success_height.nut");
                            CNSquirrelAppendage.sq_RemoveAppendage(tar, "character/thief/4_shadow/assassination/ap_assassination_success.nut");
                            createAssassinationFrontFinishAtkBlood(obj, tar);
                            createAssassinationFrontFinishLight(obj, tar);
                            sq_SendHitObjectPacket(obj, tar, 0, 0, 0);
                        }
                    } else if (flagIndex == 1) {
                        if (state == 1) {
                            createAssassinationFrontEffect(obj, tar);
                            local appendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_success_width.nut", true);
                        }
                    } else if (flagIndex == 2) {
                        if (state == 1) {
                            createAssassinationBackEffect(obj, tar);
                            local appendage = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_success_height.nut", true);
                        }
                    }
                }
            }
        }
		if (state == 1 || state == 2) {
			sq_flashScreen(obj, 40, 200, 240, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
}

function AssassinationFindNearEnemy(obj, damager, isBack) {
	if (!obj) return;
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE)) {
			local xDistance = abs(damager.getXPos() - object.getXPos());
			local yDistance = abs(damager.getYPos() - object.getYPos());
			if(xDistance < 120 && yDistance < 80){
				if (isBack) {
					if(sq_IsHoldable(obj, object))
						CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_success.nut", true);
				}
				else{
					if(sq_IsHoldable(obj, object))
						CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_fail.nut", true);
				}
				obj.getVar("dama").push_obj_vector(object);
			}
		}
	}
}

function onAttack_ASSASSINATION(obj, damager, boundingBox, isStuck) {
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) {
		if (damager.isObjectType(OBJECTTYPE_ACTIVE)) {
			local isBack = isEnemyBack(obj, damager);
			if (isBack) {
				if(sq_IsHoldable(obj, damager))
					CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_success.nut", true);
				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(3);
				obj.sq_AddSetStatePacket(STATE_ASSASSINATION, STATE_PRIORITY_USER, true);
			} else {
				if(sq_IsHoldable(obj, damager))
					CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ASSASSINATION, false, "character/thief/4_shadow/assassination/ap_assassination_fail.nut", true);
				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(2);
				obj.sq_AddSetStatePacket(STATE_ASSASSINATION, STATE_PRIORITY_USER, true);
			}
			obj.getVar("dama").push_obj_vector(damager);
			AssassinationFindNearEnemy(obj, damager, isBack);
		}
	}
}


function onProc_ASSASSINATION(obj) {
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) {
		local startX = obj.getVar("mov").get_vector(0);
		local len = obj.getVar("mov").get_vector(1);
		local delay = obj.getVar("mov").get_vector(2);

		local pAni = obj.sq_GetCurrentAni();
		local currentT = sq_GetCurrentTime(pAni);
		local vX = sq_GetAccel(0, len, currentT, delay, true);

		local dstX = sq_GetDistancePos(startX, obj.getDirection(), vX);

		if (obj.isMovablePos(dstX, obj.getYPos())) {
			sq_setCurrentAxisPos(obj, 0, dstX);
		}


	} else if (state == 1) {

	} else if (state == 2) {
		//        obj.getVar("mov").clear_vector();
		//        obj.getVar("mov").push_vector( obj.getXPos() );
		//        obj.getVar("mov").push_vector( len );
		//        obj.getVar("mov").push_vector( delay );
		//        obj.getVar("mov").push_vector( dashTime );

		local startX = obj.getVar("mov").get_vector(0);
		local len = obj.getVar("mov").get_vector(1);
		local delay = obj.getVar("mov").get_vector(2);
		local dashTime = obj.getVar("mov").get_vector(3);


		local pAni = obj.sq_GetCurrentAni();
		local currentT = sq_GetCurrentTime(pAni);

		if (currentT < dashTime) {
			local vX = sq_GetAccel(0, len, currentT, dashTime, true);

			local dstX = sq_GetDistancePos(startX, obj.getDirection(), vX);

			if (obj.isMovablePos(dstX, obj.getYPos())) {
				sq_setCurrentAxisPos(obj, 0, dstX);
			}
		}

	} else if (state == 3) {
		//        obj.getVar("mov").clear_vector();
		//        obj.getVar("mov").push_vector( obj.getXPos() );
		//        obj.getVar("mov").push_vector( len );
		//        obj.getVar("mov").push_vector( delay );



		local startX = obj.getVar("mov").get_vector(0);
		local len = obj.getVar("mov").get_vector(1);
		local delay = obj.getVar("mov").get_vector(2);

		local pAni = obj.sq_GetCurrentAni();
		local currentT = sq_GetCurrentTime(pAni);
		local vX = sq_GetAccel(0, len, currentT, delay, true);

		local dstX = sq_GetDistancePos(startX, obj.getDirection(), vX);

		if (obj.isMovablePos(dstX, obj.getYPos())) {
			sq_setCurrentAxisPos(obj, 0, dstX);
		}

	}
}


function onSetState_ASSASSINATION(obj, state, datas, isResetTimer) {
	local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();

	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	obj.getVar("flag").push_vector(0);
	obj.getVar("flag").push_vector(0);
	obj.getVar("flag").push_vector(0);

	if (state == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ASSASSINATION_READY);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_ASSASSINATION_READY);

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
		local len = obj.sq_GetIntData(SKILL_ASSASSINATION, 0);
		//obj.sq_GetIntData(SKILL_ASSASSINATION,7)
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) len = obj.sq_GetIntData(SKILL_ASSASSINATION, 1);
		if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) len = obj.sq_GetIntData(SKILL_ASSASSINATION, 2);

		obj.getVar("mov").clear_vector();
		obj.getVar("mov").push_vector(obj.getXPos());
		obj.getVar("mov").push_vector(len);
		obj.getVar("mov").push_vector(delay);
		obj.getVar("isBack").clear_vector();
		obj.getVar("isBack").push_vector(0);
		obj.getVar("dama").clear_obj_vector();
		sq_flashScreen(obj, 500, 1000, 240, 204, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

	} else if (state == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ASSASSINATION_ASSAINSUCCESS);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_ASSASSINATION_ASSASSINSUCCESS);
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		sq_flashScreen(obj, 0, 2000, 240, 240, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ASSASSINATION, STATE_ASSASSINATION, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

	} else if (state == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ASSASSINATION_FAIL);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_ASSASSINATION_FAIL);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ASSASSINATION, STATE_ASSASSINATION, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
		local len = obj.sq_GetIntData(SKILL_ASSASSINATION, 3);
		local dashTime = obj.sq_GetIntData(SKILL_ASSASSINATION, 4);
		obj.getVar("mov").clear_vector();
		obj.getVar("mov").push_vector(obj.getXPos());
		obj.getVar("mov").push_vector(len);
		obj.getVar("mov").push_vector(delay);
		obj.getVar("mov").push_vector(dashTime);

	} else if (state == 3) {

		sq_setFullScreenEffect(obj, "character/thief/animation/als_ani/assassination/cutin_dodge.ani");

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ASSASSINATION_SUCCESSFINDTARGET);

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
		local len = obj.sq_GetIntData(SKILL_ASSASSINATION, 5);
		obj.getVar("mov").clear_vector();
		obj.getVar("mov").push_vector(obj.getXPos());
		obj.getVar("mov").push_vector(len);
		obj.getVar("mov").push_vector(delay);

	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}



function createAssassinationFrontEffect(obj, damager) {
	local ani = sq_CreateAnimation("", "character/thief/animation/als_ani/assassination/frontattack/atkaeff_c.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}


function createAssassinationBackEffect(obj, damager) {
	local ani = sq_CreateAnimation("", "character/thief/animation/als_ani/assassination/backattack/cutb_a.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj, pooledObj, 2, false);
}

function onEndCurrentAni_ASSASSINATION(obj) {
	local state = obj.getVar("state").get_vector(0);
	if (state == 3) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_ASSASSINATION, STATE_PRIORITY_USER, true);
	} else {
		if (state == 1) {
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_ASSASSINATION, STATE_ASSASSINATION, 2, 1.0);
			sendOneHitAllMonsterShaowAreaObj(obj, damage);
		}
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
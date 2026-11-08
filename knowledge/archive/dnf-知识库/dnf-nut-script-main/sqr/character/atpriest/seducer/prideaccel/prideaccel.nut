function checkExecutableSkill_Prideaccel(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_PRIDEACCEL);
	local state = obj.sq_GetState();
	if (isUse) {
		if (!Seducer(obj)) {

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
		} else {
			if (state == STATE_JUMP || state == STATE_DOWN) {

				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 2);
				obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			} else {

				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);
				obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			}
		}
	}
}

function checkCommandEnable_Prideaccel(obj) {

	return true;
}



function onSetState_Prideaccel(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	obj.sq_StopMove();
	switch (state) {
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_PRIDEACCEL_START_BOBY);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			break;
		case 1:
			local ani = obj.getVar().GetAnimationMap("Seducer137move", "Character/Priest/Seducer/ATAnimation/prideaccelmove01_boby.ani");
			obj.setCurrentAnimation(ani);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			break;
		case 2:
			local ani = obj.getVar().GetAnimationMap("Seducer137Air", "seducer/ATAnimation/PrideAccelmove01_Air_Boby.ani");
			obj.setCurrentAnimation(ani);
			
			obj.getVar("pos").clear_vector();
			obj.getVar("pos").push_vector(obj.getXPos());
			obj.getVar("pos").push_vector(obj.getZPos());
			if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT ||
				sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT) {
				obj.getVar("pos").push_vector(sq_GetIntData(obj, SKILL_PRIDEACCEL, 2)); //x
				obj.getVar("pos").push_vector(0); //z
			} else {
				obj.getVar("pos").push_vector(0); //x
				obj.getVar("pos").push_vector(0); //z
			}
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			break;
		case 3:
			local ani = obj.getVar().GetAnimationMap("Seducer137", "Character/Priest/Seducer/ATAnimation/prideaccelmove02_boby.ani");
			obj.setCurrentAnimation(ani);
			
			obj.getVar("jineng").clear_vector();
			obj.getVar("jineng").push_vector(0);
			if (Seducer(obj))
				obj.sq_PlaySound("R_PW_PRIDEACCEL_DM");
			else
				obj.sq_PlaySound("R_PW_PRIDEACCEL");
			break;
		case 4:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_PRIDEACCEL_END_BOBY);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
			break;
	}
	
}



function onProc_Prideaccel(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); 
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	switch (state) {
		case 2:
			local pAni = obj.sq_GetCurrentAni();
			local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


			local startFrameIndex = 0;
			local endFrameIndex = 2;

			local currentT = sq_GetCurrentTime(pAni);

			if (frmIndex < startFrameIndex) {} else if (frmIndex > startFrameIndex && frmIndex <= endFrameIndex) {
				local startX = obj.getVar("pos").get_vector(0);
				local startZ = obj.getVar("pos").get_vector(1);

				local maxD = obj.getVar("pos").get_vector(2);
				local mazD = obj.getVar("pos").get_vector(3);

				currentT = currentT - pAni.getDelaySum(0, startFrameIndex);
				local maxT = pAni.getDelaySum(startFrameIndex, endFrameIndex);
				if (currentT < maxT) {
					local v = sq_GetAccel(0, maxD, currentT, maxT, true);
					local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
					local dstZ = sq_GetAccel(startZ, mazD, currentT, maxT, true);
					if (obj.isMovablePos(dstX, obj.getYPos())) {
						sq_setCurrentAxisPos(obj, 0, dstX);
						sq_setCurrentAxisPos(obj, 2, dstZ);
					}

				}
			}



			break;
		case 3:
			obj.setCurrentPos(obj.getXPos(), obj.getYPos(), 0);
			if (frmIndex <= 0 && obj.getVar("jineng").get_vector(0) == 0) {
				sq_SetMyShake(obj, 4, 200);
				sq_flashScreen(obj, 30, 50, 60, 102, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				obj.getVar("jineng").clear_vector();
				obj.getVar("jineng").push_vector(1);

				obj.sq_StartWrite();
				obj.sq_WriteDword(1);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_PRIDEACCEL, -1, 0, 1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_PRIDEACCEL, 5));
				obj.sq_SendCreatePassiveObjectPacket(24384, 0, 0, 0, obj.getZPos() / -1);
			}
			break;
	}
}


function onEndCurrentAni_Prideaccel(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); 

	switch (state) {
		case 0:

			if (obj.getZPos() > 75) {
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 2);
				obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			} else {
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);
				obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			}

			break;
		case 1:

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 3);
			obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");

			break;
		case 2:
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 3);
			obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			break;
		case 3:
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 4);
			obj.addSetStatePacket(STATE_PRIDEACCEL, pIntVec, STATE_PRIORITY_FORCE, false, "");
			break;
		case 4:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
			break;
	}

}
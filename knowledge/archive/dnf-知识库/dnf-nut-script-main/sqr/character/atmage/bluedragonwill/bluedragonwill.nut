
SUB_STATE_BLUEDRAGONWILL_0	<- 0
SUB_STATE_BLUEDRAGONWILL_1	<- 1
SUB_STATE_BLUEDRAGONWILL_2	<- 2
SUB_STATE_BLUEDRAGONWILL_3	<- 3
SUB_STATE_BLUEDRAGONWILL_4	<- 4

function checkExecutableSkill_BlueDragonWill(obj)
{

	if(!obj) return false;

	local b_useskill = obj.sq_IsUseSkill(SKILL_BLUEDRAGONWILL);

	if(b_useskill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_BLUEDRAGONWILL_0); // substate????
		obj.sq_AddSetStatePacket(STATE_BLUEDRAGONWILL, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}	
	
	return false;

}

function checkCommandEnable_BlueDragonWill(obj)
{

	if(!obj) return false;

	local state = obj.sq_GetState();

	if(state == STATE_ATTACK)
	{
		return obj.sq_IsCommandEnable(SKILL_BLUEDRAGONWILL); // ?????忡???? ???????? ????? ????????. ?????:?????? [2012.04.20] obj.sq_IsCommandEnable(SKILL_BROKENARROW);
	}

	return true;

}

function onSetState_BlueDragonWill(obj, state, datas, isResetTimer)
{

	if(!obj) return;

	
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	obj.sq_StopMove();

	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	obj.getVar().clear_vector();
	obj.getVar().push_vector(0);
	obj.getVar().push_vector(0);


	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
	
		obj.sq_PlaySound("MW_ICEHAMMER_READY");	
		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLUEDRAGONWILL1);
		
		local pAni = obj.sq_GetCurrentAni();
		
		//local chargeT = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 0); // ?????????e?
		//local delaySum = sq_GetDelaySum(pAni);
		//
		//local rate = delaySum.tofloat() * 100.0 / chargeT.tofloat();
		//
		//obj.sq_SetAnimationSpeedRate(pAni, rate);

		local skillLevel = sq_GetSkillLevel(obj, SKILL_BLUEDRAGONWILL);
		// ????? ????? ???????? ????
		// ????? ????? ??????? ???????? ????? ???? ????.
		// ????? ???????? ???? ??????.
		local castTime = sq_GetCastTime(obj, SKILL_BLUEDRAGONWILL, skillLevel);
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = sq_GetFrameStartTime(animation, 16);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);
			
		sq_StartDrawCastGauge(obj, startTime, true);
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
	
		local group = obj.sq_GetVectorData(datas, 1);
		local uniqueId = obj.sq_GetVectorData(datas, 2);
		
		local targetObj = sq_GetObject(obj, group, uniqueId);
	
		obj.getVar().push_vector(posX); // ???? x : i: 2
		obj.getVar().push_vector(posY); // ???? y : i: 3
		
		if(targetObj) {
			local disX = sq_Abs(targetObj.getXPos() - posX);
			local disY = targetObj.getYPos() - posY;
			
			disX = disX - 40;
			
			if(disX <= 0)
				disX = 0;
			
			obj.getVar().push_vector(disX); // x?? ?????? : i: 4
			obj.getVar().push_vector(disY); // y?? ?????? : i: 5
		}
		else { // ????? ??????
			local defaultDistance = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 1); // ???? ???? (???? ?????) (100~)
			obj.getVar().push_vector(defaultDistance); // x?? ?????? 
			obj.getVar().push_vector(0); // y?? ??????
		}		
	
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLUEDRAGONWILL2);
		
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		obj.sq_PlaySound("MW_ICEHAMMER");	
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLUEDRAGONWILL3);
		sq_setCurrentAxisPos(obj, 2, 0);
		
		if(obj.isMyControlObject()) {
			obj.sq_SetShake(obj,3,300);

			local distanceL = 90;
			local h = 0;
			
			local spin_radius = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 2); // ???? ???? (???? ?????) (100~)
			local spin_r = spin_radius.tofloat() / 100.0;
			
			local firstAttackRate = obj.sq_GetBonusRateWithPassive(SKILL_BLUEDRAGONWILL, STATE_BLUEDRAGONWILL, 0, 1.0); //2.?????(%)
			local power = obj.sq_GetPowerWithPassive(SKILL_BLUEDRAGONWILL, STATE_BLUEDRAGONWILL, 1,-1,1.0);	 // ?????????
			local pow = obj.sq_GetSkillPower(SKILL_BLUEDRAGONWILL, 1);
			
			local l_data = obj.sq_GetLevelData(SKILL_BLUEDRAGONWILL, 1, 1);
			
			print("power:" + power + " pow:" + pow + " l_data:" + l_data);
			
			sq_BinaryStartWrite();
			sq_BinaryWriteFloat(spin_r); // 
			sq_BinaryWriteDword(power); // ?????????
			
			obj.sq_SendCreatePassiveObjectPacket(24246, 0, distanceL, -1, h); // ????????? ???? ????
			
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(firstAttackRate); // ?????(%)
			
			obj.sq_SendCreatePassiveObjectPacket(24245, 0, distanceL, 5, h);
		}
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}

function prepareDraw_BlueDragonWill(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		// SUB_STATE_BLUEDRAGONWILL_0 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		// SUB_STATE_BLUEDRAGONWILL_1 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

}

function onProc_BlueDragonWill(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local sq_var = obj.getVar();
	local currentT = sq_GetCurrentTime(pAni);
	
	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
    	//local dash_t = pAni.getDelaySum(false); //
		local dash_t = pAni.getDelaySum(0, 2) + 60; //
    	
    	
		local srcX = obj.getVar().get_vector(2); // ????x
		local srcY = obj.getVar().get_vector(3); // ????y
    	    	
    	local dis_x_len = sq_var.get_vector(4); // ?? ??????
		local dis_y_len = obj.getVar().get_vector(5); // y?? ??????
		
		local v = sq_GetAccel(0, dis_x_len, currentT, dash_t, true);
		
		local my = sq_GetUniformVelocity(0, dis_y_len, currentT, dash_t);
		
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		local dstY = srcY + my;
		 
		if(sq_var.get_vector(0)) { // ??????????? ????? ?? ???? ?????? ???????..
			if(sq_var.get_vector(1) != posY) { // ?? posY?? ??????? ????????..
				sq_var.set_vector(0, 0); // ????÷???? off??????..
				sq_var.set_vector(1, posY);
			}
		}
		 
		if(obj.isMovablePos(dstX, dstY) && !sq_var.get_vector(0)) { // ????÷???? ????????????? ??????????? ???
			sq_setCurrentAxisPos(obj, 0, dstX);
			sq_setCurrentAxisPos(obj, 1, dstY);
		}
		else { // ????? ?? ???? ?????? ??????..
			sq_var.set_vector(0,1); // ??? ?÷??? ?ε??? 3 ????? ?? ???? ?????? ?????? ?? ????? ????? ????????..
			local offset = dstX - posX;
			
			if(offset != 0) {				
				if(offset < 0) 
					offset = -offset;
				
				local totalLen = sq_var.get_vector(4); // ????????
				sq_var.set_vector(4, totalLen - offset);
			}
		}
		
		
		
		if(frmIndex == 2){
    		sq_setCurrentAxisPos(obj, 2, 30);
		}
		else if(frmIndex == 3) {
    		sq_setCurrentAxisPos(obj, 2, 60);
		}
		else if(frmIndex == 4){
    		sq_setCurrentAxisPos(obj, 2, 50);
		}
		else if(frmIndex == 5){
    		sq_setCurrentAxisPos(obj, 2, 40);
		}
    	
	
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

}

function onProcCon_BlueDragonWill(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		// SUB_STATE_BLUEDRAGONWILL_0 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		// SUB_STATE_BLUEDRAGONWILL_1 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

}

function onEndCurrentAni_BlueDragonWill(obj)
{

	if(!obj) return;

	if(!obj.isMyControlObject()) {
		return;
	}
	
	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_BLUEDRAGONWILL_1); // substate????
		
		// 500 // x?? ????? ????
		// 120 // y?? ????? ????
		// 10 // z?? ????? ????
		
		//local x_range = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 3); // ?????????e?
		//local y_range = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 4); // ?????????e?
		//local z_range = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, 5); // ?????????e?
		
		//local targetObj = sq_FindTarget(obj, 0, x_range, y_range, z_range);
		//
		//if(targetObj) {
			//local group = sq_GetGroup(targetObj);
			//local uniqueId = sq_GetUniqueId(targetObj);
			//
			//obj.sq_IntVectPush(group); // 
			//obj.sq_IntVectPush(uniqueId); // 
		//}
		//else {
			//obj.sq_IntVectPush(-1); // 
			//obj.sq_IntVectPush(-1); // 
		//}
		local distance = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, SKL_STATIC_INT_IDX_3); // ?????? ???
		local angle = obj.sq_GetIntData(SKILL_BLUEDRAGONWILL, SKL_STATIC_INT_IDX_4); // ?????? ????
		
		local targetObj = findAngleTarget(obj, distance, angle, 100);
		if(targetObj) {
			local group = sq_GetGroup(targetObj);
			local uniqueId = sq_GetUniqueId(targetObj);
			
			obj.sq_IntVectPush(group); // 
			obj.sq_IntVectPush(uniqueId); // 
		}
		else {
			obj.sq_IntVectPush(-1); // 
			obj.sq_IntVectPush(-1); // 
		}
		
		
		obj.sq_AddSetStatePacket(STATE_BLUEDRAGONWILL, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_BLUEDRAGONWILL_2); // substate????
		obj.sq_AddSetStatePacket(STATE_BLUEDRAGONWILL, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

}

function onKeyFrameFlag_BlueDragonWill(obj, flagIndex)
{

	if(!obj) return false;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		// SUB_STATE_BLUEDRAGONWILL_0 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		// SUB_STATE_BLUEDRAGONWILL_1 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

	return false;

}

function onEndState_BlueDragonWill(obj, new_state)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		// SUB_STATE_BLUEDRAGONWILL_0 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		// SUB_STATE_BLUEDRAGONWILL_1 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	
	sq_EndDrawCastGauge(obj);

}

function onAfterSetState_BlueDragonWill(obj, state, datas, isResetTimer)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_BLUEDRAGONWILL_0) {
		// SUB_STATE_BLUEDRAGONWILL_0 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_1) {
		// SUB_STATE_BLUEDRAGONWILL_1 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_2) {
		// SUB_STATE_BLUEDRAGONWILL_2 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_3) {
		// SUB_STATE_BLUEDRAGONWILL_3 ????????? ???
	}
	else if(substate == SUB_STATE_BLUEDRAGONWILL_4) {
		// SUB_STATE_BLUEDRAGONWILL_4 ????????? ???
	}
	

}

function getHitDirection_BlueDragonWill(obj, damager)
{
	if(!obj) return 0;
	
	print("getHitDirection_BlueDragonWill");
	
	return sq_GetOppositeDirection(obj.getDirection());
	
}


SUB_STATE_ATCHAINLIGHTNING_0	<- 0
SUB_STATE_ATCHAINLIGHTNING_1	<- 1
SUB_STATE_ATCHAINLIGHTNING_2	<- 2
SUB_STATE_ATCHAINLIGHTNING_3	<- 3
SUB_STATE_ATCHAINLIGHTNING_4	<- 4

SKL_CL_SD_0 <- 0 //200	// 10.ó?? ????y? Y?? ???? (???? ????)
SKL_CL_SD_1 <- 1 //0	// 11.ó?? ????y? X?? ???? ???
SKL_CL_SD_2 <- 2 //400	// 12.ó?? ????y? X?? ?? ???
SKL_CL_SD_3 <- 3 //320	// 13.ü?ν? ???? ???????? ??? ???
SKL_CL_SD_4 <- 4 //300	// 14.????? ???? ??? ????
SKL_CL_SD_5 <- 5
SKL_CL_SD_6 <- 6

// 0.??? ??? ???? 1.????e? 2.?????(%) 3.?????? ??? 4.?????? ????
SKL_CL_LI_0 <- 0 // 0.??? ??? ???? 
SKL_CL_LI_1 <- 1 // 1.????e?
SKL_CL_LI_2 <- 2 // 2.?????(%)
SKL_CL_LI_3 <- 3 // 3.?????? ???
SKL_CL_LI_4 <- 4 // 4.?????? ????

function checkExecutableSkill_ChainLightning(obj)
{

	if(!obj) return false;

	local b_useskill = obj.sq_IsUseSkill(SKILL_ATCHAINLIGHTNING);
	
	//print("b_useskill : %d" + b_useskill);

	if(b_useskill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_ATCHAINLIGHTNING_0); // substate????
		obj.sq_AddSetStatePacket(STATE_CHAINLIGHTNING, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}	

	return false;

}

function checkCommandEnable_ChainLightning(obj)
{

	if(!obj) return false;
	if(sq_GetSkillLevel(obj, SKILL_ELEMENTAL_BOMBING) > 1){
		return true;
	}
	local state = obj.sq_GetState();
	if(state == STATE_ATTACK || state == STATE_STAND || state == STATE_DASH)
	{
		return true;
	}
	return false;
}

function onSetState_ChainLightning(obj, state, datas, isResetTimer)
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

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CHAINLIGHTNING_CAST);
		local pAni = obj.sq_GetCurrentAni();
		
		local skillLevel = sq_GetSkillLevel(obj, SKILL_ATCHAINLIGHTNING);
		
		local castTime = sq_GetCastTime(obj, SKILL_ATCHAINLIGHTNING, skillLevel);
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = sq_GetFrameStartTime(animation, 16);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, startTime, true);
		addElementalChain_ATMage(obj, ENUM_ELEMENT_LIGHT);
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CHAINLIGHTNING);		
		obj.sq_PlaySound("MW_CHAINLIGHT");

		if(obj.isMyControlObject()) {
			/////////////////////////////////////////////		
			local firstTargetYRange = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_0); // 0.ó?? ????y? Y?? ???? (???? ????)
			local firstTargetXStartRange = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_1); // 1.ó?? ????y? X?? ???? ???
			local firstTargetXEndRange = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_2); // 2.ó?? ????y? X?? ?? ???
			local nextTargetRange = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_3); // 3.ü?ν? ???? ???????? ??? ???
			local targetMaxHeight = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_4); // 4.????? ???? ??? ????
			local isChoroset = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_5);
			local chorosetTime = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_6);
			
			local skill_level = obj.sq_GetSkillLevel(SKILL_ATCHAINLIGHTNING);
			
			local link_num = obj.sq_GetLevelData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_0, skill_level); // 0.??? ??? ???? 
			local attack_time = obj.sq_GetLevelData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_1, skill_level);	// 1.????e?
			local firstAttackRate = obj.sq_GetBonusRateWithPassive(SKILL_ATCHAINLIGHTNING, STATE_CHAINLIGHTNING, SKL_CL_LI_2, 1.0); //2.?????(%)
			local multi_hit_num = obj.sq_GetLevelData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_3, skill_level);	// 3.?????? ???
			//local multi_hit_term = obj.sq_GetLevelData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_4, skill_level);	// 4.?????? ????
			////////////////////////////////////////////////
			sq_BinaryStartWrite();
			sq_BinaryWriteWord(firstTargetYRange);
			sq_BinaryWriteWord(firstTargetXStartRange);
			sq_BinaryWriteWord(firstTargetXEndRange);
			sq_BinaryWriteWord(nextTargetRange);
			sq_BinaryWriteWord(targetMaxHeight);
			sq_BinaryWriteWord(isChoroset);
			sq_BinaryWriteWord(chorosetTime);
			
			sq_BinaryWriteWord(link_num);
			sq_BinaryWriteWord(attack_time);
			sq_BinaryWriteDword(firstAttackRate);
			sq_BinaryWriteWord(multi_hit_num);
			//sq_BinaryWriteWord(multi_hit_term);
			
			
    		//local ropeX = sq_GetDistancePos(posX, obj.getDirection(), offsetLen);
    		local distanceL = 50;
    		local h = 88;
    		obj.sq_SendCreatePassiveObjectPacket(24241, 0, distanceL, 0, h);
    		
    		obj.sq_PlaySound("CHAINLIGHT_ELEC_LOOP", 7576);
    	}
		
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CHAINLIGHTNING_END);
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}

function prepareDraw_ChainLightning(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

}

function onProc_ChainLightning(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
		if(obj.isMyControlObject()) {
			//if(!obj.sq_GetPassiveObject(24241)) {
			
			local skill_level = obj.sq_GetSkillLevel(SKILL_ATCHAINLIGHTNING);
			local attack_time = obj.sq_GetLevelData(SKILL_ATCHAINLIGHTNING, SKL_CL_LI_1, skill_level);	// 1.????e?
			
			local isChoroset = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_5);
			if (isChoroset == 1)
			{
				attack_time = obj.sq_GetIntData(SKILL_ATCHAINLIGHTNING, SKL_CL_SD_6);
			}
			
			local passiveobj_cl = obj.sq_GetPassiveObject(24241);
			
			
			if(passiveobj_cl) {
				local flag = passiveobj_cl.getVar("nograb").get_vector(0);
				
				if(flag)
				{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(SUB_STATE_ATCHAINLIGHTNING_2);
					obj.sq_AddSetStatePacket(STATE_CHAINLIGHTNING, STATE_PRIORITY_USER, true);
					return;
				}
				else
				{
					if(obj.getVar().get_vector(0) == 0) {
						obj.sq_SetShake(obj,1,attack_time);
						obj.getVar().set_vector(0, 1);
					}
				}
				
			}
			
			if(currentT > attack_time) {
				//obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(SUB_STATE_ATCHAINLIGHTNING_2);
				obj.sq_AddSetStatePacket(STATE_CHAINLIGHTNING, STATE_PRIORITY_USER, true);
			}
		}
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

}

function onProcCon_ChainLightning(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

}

function onEndCurrentAni_ChainLightning(obj)
{

	if(!obj) return;
	
	//local pSickleObj = obj.sq_GetPassiveObject(24101); // sickle 

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		if(obj.isMyControlObject()) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(SUB_STATE_ATCHAINLIGHTNING_1);
			obj.sq_AddSetStatePacket(STATE_CHAINLIGHTNING, STATE_PRIORITY_USER, true);
		}
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		if(obj.isMyControlObject()) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

}

function onKeyFrameFlag_ChainLightning(obj, flagIndex)
{

	if(!obj) return false;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

	return false;

}

function onEndState_ChainLightning(obj, new_state)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	// ??????? ???? ??? ?????????? ????? ?????? ????
	if(new_state != STATE_CHAINLIGHTNING)
	{
		sq_EndDrawCastGauge(obj);
		obj.stopSound(7576);
	}
}

function onAfterSetState_ChainLightning(obj, state, datas, isResetTimer)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_ATCHAINLIGHTNING_0) {
		// SUB_STATE_ATCHAINLIGHTNING_0 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_1) {
		// SUB_STATE_ATCHAINLIGHTNING_1 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_2) {
		// SUB_STATE_ATCHAINLIGHTNING_2 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_3) {
		// SUB_STATE_ATCHAINLIGHTNING_3 ????????? ???
	}
	else if(substate == SUB_STATE_ATCHAINLIGHTNING_4) {
		// SUB_STATE_ATCHAINLIGHTNING_4 ????????? ???
	}
	

}


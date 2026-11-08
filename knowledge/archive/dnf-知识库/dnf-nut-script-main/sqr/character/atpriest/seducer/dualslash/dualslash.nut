
function checkExecutableSkill_Dualslash(obj)
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_DUALSLASH);
	
	if (isUse)
	{
	if (Seducer(obj))
	{
		//dofile("demoniclancer/cs.nut");
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);
		obj.addSetStatePacket(STATE_DUALSLASH , pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
   else
	{
		//dofile("demoniclancer/cs.nut");
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_DUALSLASH , pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}
}

function checkCommandEnable_Dualslash(obj)
{

	return true;
}


function onSetState_Dualslash(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	obj.sq_StopMove();
	if(state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_DUALSLASH_BODY);//
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_DUALSLASH_FIRST);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_DUALSLASH, STATE_DUALSLASH, 0, 1.0); 
		obj.sq_SetCurrentAttackBonusRate(attackBonusRate); //����������߿��	
		
		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector( obj.getXPos() );
		obj.getVar("pos").push_vector( obj.sq_GetIntData(SKILL_DUALSLASH, 2) );
	}
	else if(state == 1)
	{
		local ani = obj.getVar().GetAnimationMap("Seducer109", "Character/Priest/Seducer/ATAnimation/dualslash_demonization.ani");
		obj.setCurrentAnimation(ani);
		
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_DUALSLASH_FIRST);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_DUALSLASH, STATE_DUALSLASH, 0, 1.0); 
		obj.sq_SetCurrentAttackBonusRate(attackBonusRate); //����������߿��	
		

		obj.getVar("pos").clear_vector();
		obj.getVar("pos").push_vector( obj.getXPos() );
		obj.getVar("pos").push_vector( obj.sq_GetIntData(SKILL_DUALSLASH, 2) );
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onProc_Dualslash(obj)
{
    if(!obj) return;
    local state = obj.getSkillSubState();//��������������SUB����
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
		
	if(state == 0)
	{
		local pAni = obj.sq_GetCurrentAni();
		local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

		local startFrameIndex = 2;
		local endFrameIndex = 5;

		local currentT = sq_GetCurrentTime(pAni);
		
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT
	|| sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection()== ENUM_DIRECTION_RIGHT)
	{
		if (frmIndex < startFrameIndex)
		{
			obj.setCurrentPos(obj.getVar("pos").get_vector(0),obj.getYPos(),obj.getZPos() );

		}else if (frmIndex > startFrameIndex && frmIndex <= endFrameIndex)
		{
			local startX = obj.getVar("pos").get_vector(0);
			local maxD = obj.getVar("pos").get_vector(1);

			currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
			local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
			if (currentT < maxT)
			{
				local v = sq_GetAccel(0, maxD, currentT,maxT, true);
				local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

				if( obj.isMovablePos(dstX, obj.getYPos() ))
				{
					sq_setCurrentAxisPos(obj, 0, dstX);
				}

			}
		}
	}
}

	if(state == 1 && Seducer(obj))
	{
		local pAni = obj.sq_GetCurrentAni();
		local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

		local startFrameIndex = 1;
		local endFrameIndex = 6;

		local currentT = sq_GetCurrentTime(pAni);
		
	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT
	|| sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection()== ENUM_DIRECTION_RIGHT)
	{
		if (frmIndex < startFrameIndex)
		{
			obj.setCurrentPos(obj.getVar("pos").get_vector(0),obj.getYPos(),obj.getZPos() );

		}else if (frmIndex > startFrameIndex && frmIndex <= endFrameIndex)
		{
			local startX = obj.getVar("pos").get_vector(0);
			local maxD = obj.getVar("pos").get_vector(1);

			currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
			local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
			if (currentT < maxT)
			{
				local v = sq_GetAccel(0, maxD, currentT,maxT, true);
				local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

				if( obj.isMovablePos(dstX, obj.getYPos() ))
				{
					sq_setCurrentAxisPos(obj, 0, dstX);
				}

			}
		}
	}
}
}
//2������5���?


function onEndCurrentAni_Dualslash(obj)
{
	if(!obj) return;
	local state = obj.getSkillSubState(); //��������������SUB����
	if(state == 0)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
		
	}
	else if(state == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
	}
}

function onKeyFrameFlag_Dualslash(obj,flagIndex)//����μ��������
{
	if(!obj) return;
	local state = obj.getSkillSubState();//����������sub state����
	if(state == 0)
	{
	if(flagIndex == 2)
	{
	obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_DUALSLASH_SECOND);
	local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_DUALSLASH, STATE_DUALSLASH, 1, 1.0); 
	obj.sq_SetCurrentAttackBonusRate(attackBonusRate); //����������߿��		
	}	
    }
	return true;
}


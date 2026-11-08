//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_flyingswallow(obj)
{
	return true;
}



function checkExecutableSkill_flyingswallow(obj)
{
	if(!obj) return false;

	local state = obj.sq_GetState();
	if(state == 3||state == 4||state == 5||state == 9||state == 16||state == 40) 
		return false;
	if(obj.sq_IsUseSkill(SKILL_FLYINGSWALLOW))
	{
		
		local now_z = obj.getZPos();
		if(state == 6 || state == 7 || now_z>40)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_FLYINGSWALLOW, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}else{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_FLYINGSWALLOW, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
	return false;
}



function onSetState_flyingswallow(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_FLYINGSWALLOW1);
			obj.sq_ZStop();
			obj.sq_PlaySound("R_TF_BIYOEN_01");
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_FLYINGSWALLOW2);
			obj.sq_ZStop();
			obj.sq_PlaySound("R_TF_BIYOEN_02");
		break;
	}
}



function onEndCurrentAni_flyingswallow(obj)
{
	if(!obj) return;

	if(!obj.isMyControlObject())
	{
		return;
	}

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		case 1:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onKeyFrameFlag_flyingswallow(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(40);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
						sq_flashScreen(obj, 70, 140, 70, 160, sq_RGB(255,255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
					}
				break;
				case 10002:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(41);
						obj.sq_WriteDword(-20);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, -100, 0, 100);
						obj.sq_StartWrite();
						obj.sq_WriteDword(39);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 100, 0, 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(42);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 50), sq_GetYPos(obj), 0);
					}
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), -200), sq_GetYPos(obj), 100, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
				break;
				case 10003:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(41);
						obj.sq_WriteDword(-50);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 130, 0, 100);
						obj.sq_StartWrite();
						obj.sq_WriteDword(42);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 250), sq_GetYPos(obj), 0);
					}
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 100), sq_GetYPos(obj), 200, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
				break;
				case 10004:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(41);
						obj.sq_WriteDword(-90);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 80, 0, -300);
					}
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 100), sq_GetYPos(obj), 300, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
				break;
				case 10005:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(43);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj), sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(43);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)+50, sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(43);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-85, sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(43);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-50, sq_GetYPos(obj)+20, 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(43);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-50, sq_GetYPos(obj)-20, 0);
					}
				break;
			}
		break;
		case 1:
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(44);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj), sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(44);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)+50, sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(44);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-85, sq_GetYPos(obj), 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(44);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-50, sq_GetYPos(obj)+20, 0);
						obj.sq_StartWrite();
						obj.sq_WriteDword(44);
						sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, sq_GetXPos(obj)-50, sq_GetYPos(obj)-20, 0);
						
					}
				break;
			}
		break;
	}
	return true;
}


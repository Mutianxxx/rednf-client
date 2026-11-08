
function checkExecutableSkill_lacerthorns(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_LACERTHORNS);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_LACERTHORNS , STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_lacerthorns(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_lacerthorns(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, 
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		obj.sq_PlaySound("SW_LACERTHORNS_01");
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_atlacerthornscasting_body);
	}
	if(substate == 1)
	{
		obj.sq_SetXScrollStart(380, 100);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_atlacerthornsfail_body);
	}
	if(substate == 2)
	{
		local randNum = sq_getRandom(1, 2);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_LACERTHORNS_02_1");
		if(randNum == 2)
		obj.sq_PlaySound("SW_LACERTHORNS_02_2");
		
		obj.sq_SetXScrollStop(100);
		obj.sq_SetShake(obj,50,300);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_atlacerthornsfinish_body);
	}
}

function onKeyFrameFlag_lacerthorns(obj,flagIndex)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();
	if(substate == 1)
	{
		if (flagIndex == 0)
		{
			local atlacerthornsfail_body = "passiveobject/atswordman_3rd/atanimation/atlacerthorns/atlacerthornsfail_body.ani";
			ATSwordman_Create(obj,atlacerthornsfail_body,ENUM_DRAWLAYER_NORMAL,-20,20,0,0,130,0,50,"atlacerthornsfail_body");
			
			local atlacerthornsdash_00 = "passiveobject/atswordman_3rd/atanimation/atlacerthorns/atlacerthornsdash_00.ani";
			ATSwordman_Create(obj,atlacerthornsdash_00,ENUM_DRAWLAYER_NORMAL,100,0,0,0,120,0,100,"atlacerthornsdash_00");
			
			local atlacerthornsshot_00 = "passiveobject/atswordman_3rd/atanimation/atlacerthorns/atlacerthornsshot_00.ani";
			ATSwordman_Create(obj,atlacerthornsshot_00,ENUM_DRAWLAYER_CONTACT,155,-85,0,0,100,0,100,"atlacerthornsshot_00");
			
			obj.sq_StartWrite();
			obj.sq_WriteDword(6);
			obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
		}
	}
	if(substate == 2)
	{
		if (flagIndex == 1)
		{
			local atlacerthornsspin_back = "passiveobject/atswordman_3rd/atanimation/atlacerthorns/atlacerthornsspin_back.ani";
			ATSwordman_Create(obj,atlacerthornsspin_back,ENUM_DRAWLAYER_NORMAL,15,-25,0,0,100,0,100,"atlacerthornsspin_back");
			
			local atlacerthornsspin_front = "passiveobject/atswordman_3rd/atanimation/atlacerthorns/atlacerthornsspin_front.ani";
			ATSwordman_Create(obj,atlacerthornsspin_front,ENUM_DRAWLAYER_NORMAL,15,-25,0,0,100,0,100,"atlacerthornsspin_front");
			
			obj.sq_StartWrite();
			obj.sq_WriteDword(7);
			obj.sq_SendCreatePassiveObjectPacket(24391, 0, 0, 0, 0);
		}
	}
	return true;
}

function onEndCurrentAni_lacerthorns(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_LACERTHORNS, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_LACERTHORNS, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
}

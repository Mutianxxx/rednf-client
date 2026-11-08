//CUSTOM_ANI_WIND_AIR_DASH <- 345

function onSetState_ATMage_Jump(obj, state, datas, isResetTimer)
{	


	local substate = obj.sq_GetVectorData(datas, 0);
	local skill = obj.sq_GetVectorData(datas, 1);
	local skill2 = obj.sq_GetVectorData(datas, 2);
	obj.getVar("data").clear_vector();
	obj.getVar("data").push_vector(substate);
	obj.getVar("data").push_vector(skill);
	obj.getVar("data").push_vector(skill2);
}

function onProc_ATMage_Jump(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (false)//(state == 100)
    {


    }else{

        if (obj.sq_GetSkillLevel(SKILL_STICKMASTER) > 0)
        {
            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            if (sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL) && frmIndex >= 2 && 
                !CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/jump/ap_jump.nut") && 
                obj.getZPos() > 50 )
            {
                //obj.sq_SendCreatePassiveObjectPacket(24357, 0, 120, 1, 0);

                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(3);
                obj.sq_AddSetStatePacket(STATE_WIND_STRIKE , STATE_PRIORITY_USER, false);

            }
        }


    }
}

function onEndCurrentAni_ATMage_Jump(obj)
{

		//obj.sq_IntVectClear();
		//obj.sq_IntVectPush(1);
		//obj.sq_IntVectPush(0);
		//obj.sq_IntVectPush(0);
		//obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);
}
function checkExecutableSkill_summon_woman(obj)  
{
	if (!obj) return false;
    
    local job = getNyarly(obj);
    if (!job )
    {
        local isUse = obj.sq_IsUseSkill(SKILL_SUMMON_WOMAN);

        if (isUse) {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            obj.sq_AddSetStatePacket(STATE_SUMMON_WOMAN , STATE_PRIORITY_USER, false);
            return true;
        }
    }else{
        job.getVar("state").clear_vector();
        job.getVar("state").push_vector(4);
        local pIntVec = sq_GetGlobalIntVector();
        sq_IntVectorClear(pIntVec);
        sq_IntVectorPush(pIntVec, 0);
        job.addSetStatePacket(14, pIntVec, STATE_PRIORITY_AUTO, false, "");

    }

	return false;
}




function checkCommandEnable_summon_woman(obj)
{
	if (!obj) return false;

	return true;
}


function onSetState_SUMMON_WOMAN(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);

	obj.sq_StopMove();
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SUMMON_NYALRY_CASTING);
    }else if (state == 1)
    {

        local level = sq_GetSkillLevel(obj, SKILL_SUMMON_WOMAN);		
        local useHp = sq_GetLevelData(obj, SKILL_SUMMON_WOMAN, 0, level);
        obj.setHp( obj.getHp() - useHp , null, true);

        obj.sq_SendCreatePassiveObjectPacket(152237 , 0, 100, 1, 0);
        obj.sq_StartWrite();
        obj.sq_WriteDword(0);	// attackBonusRate
        obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_SUMMON_WOMAN, 1, obj.sq_GetSkillLevel(SKILL_SUMMON_WOMAN) ) );
        // attackBonusRate
        obj.sq_SendCreatePassiveObjectPacket(24342 , 0, 100, 1, 0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SUMMON_NYALRY_THROW);



        local appendage = getComboUiAppendage(obj);

        if (!appendage)
            return true;

        local currT = appendage.getTimer().Get();

        local i = 0;

        for (;i < 400 ;i++)
            if (appendage.getVar("damageNum").get_vector(i) == 0)
                break;
        
        i = i % 400;
        appendage.getVar("damageNum").set_vector(i,useHp);
        appendage.getVar("damageNum").set_vector(i + 1,currT);
        appendage.getVar("damageNum").set_vector(i + 2,obj.getXPos() * 10 + 1 );
        appendage.getVar("damageNum").set_vector(i + 3,obj.getYPos() * 1000 + obj.getZPos() );

    }
}



function onEndCurrentAni_SUMMON_WOMAN(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_SUMMON_WOMAN , STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}

function onKeyFrameFlag_SUMMON_WOMAN(obj,flagIndex)
{
    if (flagIndex == 1)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

        }
    }
}
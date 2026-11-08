//CUSTOM_ANI_SHAOWAREA_BODY <- 148
//CUSTOM_ANI_SHAOWAREA_BODY2 <- 149

function checkExecutableSkill_shaowarea(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SHAOWAREA);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_SHAOWAREA, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_shaowarea(obj)  
{

	return true;
}

function getShaowAreaObj(obj)
{
    return obj.getMyPassiveObject(24239,0);
}

function sendOneHitAllMonsterShaowAreaObj(obj,damaRate)
{
    local shaowAreaObj = getShaowAreaObj(obj);
    if (shaowAreaObj)
    {
        shaowAreaObj.getVar("attackRate").set_vector(0,damaRate);
        findAllNoHitEnemy_ShaowArea(shaowAreaObj);
    }
    return false;
}


function onSetState_SHAOWAREA(obj, state, datas, isResetTimer)
{	
	if (!obj) return;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
    	obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWAREA_BODY);



    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWAREA_BODY2);


        obj.sq_StartWrite();
        obj.sq_WriteDword(200);
        obj.sq_SendCreatePassiveObjectPacket(24239, 0, 56, 1, 3);

        local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SHAOWAREA, false,
        "character/thief/4_shadow/shaowarea/ap_shaowarea.nut", false);

        local skill_level = sq_GetSkillLevel(obj, SKILL_SHAOWAREA);
        appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SHAOWAREA, skill_level);
        CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_SHAOWAREA, true);
	appendage.setBuffIconImage(86);
    }
}

function onProc_SHAOWAREA(obj)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/shaowarea/ap_shaowarea.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/thief/4_shadow/shaowarea/ap_shaowarea.nut");		
		}
	}
}

function onEndCurrentAni_SHAOWAREA(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_SHAOWAREA, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
    }

}
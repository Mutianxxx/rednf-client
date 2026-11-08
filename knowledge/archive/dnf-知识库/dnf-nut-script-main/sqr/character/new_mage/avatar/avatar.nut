function checkExecutableSkill_avatar(obj)  
{
	if (!obj) return false;

    if (!isZFAwakeing(obj))
    {
        local isUseSkill = obj.sq_IsUseSkill(SKILL_AVATAR);
        if (isUseSkill) 
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            obj.sq_AddSetStatePacket(STATE_AVATAR, STATE_PRIORITY_USER, true);
            return true;
        }
    }
	return false;
}


function checkCommandEnable_avatar(obj)
{

	return true;
}


function onSetState_AVATAR(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_AVATARREADY1);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
    }

    if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_AVATARREADY2);
    }


}


function onEndCurrentAni_AVATAR(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

    if (state == 1)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

    }

}


function onKeyFrameFlag_AVATAR(obj, flagIndex)
{
    if (flagIndex == 1)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_AVATAR, false,
            "character/new_mage/avatar/ap_avatar.nut", false);

            local skill_level = sq_GetSkillLevel(obj, SKILL_AVATAR);
            appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_AVATAR, skill_level);

            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 135, true);

        }


    }


}




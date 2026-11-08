function checkExecutableSkill_windbuff(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINDBUFF);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_WINDBUFF , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function onKeyFrameFlag_WINDBUFF(obj,flagIndex)
{
    if (!obj) return false;
    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);
        //?????A?O??u???[?@??
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/windbuff/ap_windbuff.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/windbuff/ap_windbuff.nut");
		}
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_WINDBUFF,false ,
		 "character/atmage/windbuff/ap_windbuff.nut", true);
		local skill_level = sq_GetSkillLevel(obj, SKILL_WINDBUFF);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_WINDBUFF, skill_level);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_WINDBUFF, true);
		appendage.setBuffIconImage(106);

		local value0 = sq_GetLevelData(obj, SKILL_WINDBUFF, 2, skill_level).tofloat(); //huibi
		//local value1 = sq_GetLevelData(obj, SKILL_WINDBUFF, 3, skill_level).tofloat(); //dama sub rate
		local value2 = sq_GetLevelData(obj, SKILL_WINDBUFF, 5, skill_level).tofloat(); 
		value2         = value2/10;
		local change_appendage = appendage.sq_getChangeStatus("windbuff");

		if(!change_appendage)
		{
			change_appendage = appendage.sq_AddChangeStatus("windbuff",obj, obj, 0, 0, true, 0);
		}
		if (change_appendage){
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVEPROPERTY_STUCK, false, value0 );
		}
		
		local objectManager = obj.getObjectManager();
		for(local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && object.isObjectType(OBJECTTYPE_CHARACTER) && !obj.isEnemy(object))
			{
				try
				{
					object = sq_GetCNRDObjectToSQRCharacter(object);
				}
				catch(ex)
				{
				}
				local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/atmage/windbuff/ap_windbuff_friend.nut");
				if(!isAppend)
				{
					local appendage_f = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_WINDBUFF, false, "character/atmage/windbuff/ap_windbuff_friend.nut", true);
					
					appendage_f.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_AT_MAGE, SKILL_WINDBUFF, skill_level);
					CNSquirrelAppendage.sq_AppendAppendageID(appendage_f, object, obj, SKILL_WINDBUFF, true);
					
					local change_appendage_f = appendage_f.sq_getChangeStatus("windbuff_f");
					if(!change_appendage_f)
					{
						change_appendage_f = appendage_f.sq_AddChangeStatus("windbuff_f",object, obj, 0, 0, true, 0);
					}
					if (change_appendage_f){
						change_appendage_f.clearParameter();
						change_appendage_f.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK_BONUS,true, value2);
						change_appendage_f.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS,true, value2);
					}
				}
			}
		}

    }
}


function checkCommandEnable_windbuff(obj)
{

	return true;
}

function onSetState_WINDBUFF(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBUFF);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    //?????

}



function onEndCurrentAni_WINDBUFF(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

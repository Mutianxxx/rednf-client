function checkExecutableSkill_doll(obj)  
{
	if(!obj) return; 
    if (!isDollState(obj) )
    {
        local isUseSkill = obj.sq_IsUseSkill(SKILL_DOLL);
        if (isUseSkill) 
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            obj.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);
            return true;
        }
        return false;
    }else{
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);
    }
}


function checkCommandEnable_doll(obj)
{
	if(!obj) return false; 
	return true;
}

function onSetState_DOLL(obj, state, datas, isResetTimer)
{
	if(!obj) return; 
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionettestart02_00.ani");	
        sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionetteeternalpossessionstart_00.ani");	
        sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionetteeternalpossessionstart_01.ani");	
        sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionettestart01_30.ani");	

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL);
        sq_flashScreen(obj,200,5000,160,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SendCreatePassiveObjectPacket(12262, 0, 0, -1, 0);
        obj.getVar("add").clear_vector();
        obj.getVar("add").push_vector(0);
    }else if (state == 1){


		obj.sq_StartWrite();
		obj.sq_WriteDword(0);	// attackBonusRate
        obj.sq_SendCreatePassiveObjectPacket(24347, 0, 0, 1, 0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_BOBY_START);
    }else if (state == 2){
        addDollBuffAndFriend(obj);
        obj.getVar("add").clear_vector();
        obj.getVar("add").push_vector(1);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_BOBY_END);
    }else if (state == 3)
    {
        local jt = obj.getMyPassiveObject(24347,0);
        if (jt)
        {
            jt.getVar("break").set_vector(0,1);
        }
        sq_flashScreen(obj,50,350,0,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_BOBY_END0);
        obj.sq_SendCreatePassiveObjectPacket(12263, 0, 0, 1, 0);
    }else if (state == 4)
    {
        sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionetteend01_03.ani");	
        sq_flashScreen(obj,200,3500,160,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_BOBY_LAST);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_DOLL_LASTATK);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLL , STATE_DOLL, 7, 1.0);
        local skill_level = sq_GetSkillLevel(obj, SKILL_DOLL);
        if (skill_level >= 9)
        {
            damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLL , STATE_DOLL, 7, 1.1);
        }
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }

}
function addDollBuffSelf(obj)
{
	if(!obj) return; 
    if(!isDollState(obj))
    {
        local skill_level = sq_GetSkillLevel(obj, SKILL_DOLL);
        local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_DOLL, false, 
           "character/new_mage/doll/ap_doll.nut", true);
            local time = sq_GetLevelData(obj, SKILL_DOLL, 0, skill_level); //ll
            appendage.sq_SetValidTime(time); 
        //appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_DOLL, skill_level);
        //CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_DOLL, true);
    }
}

function addDollBuffAndFriend(obj)
{
	if(!obj) return; 
	local objectManager = obj.getObjectManager();
    local skill_level = sq_GetSkillLevel(obj, SKILL_DOLL);
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{


		local object = objectManager.getCollisionObject(i);

        if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE))
        {
		//object.setCurrentPos(0,0,0);
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_DOLL, false, "character/new_mage/doll/ap_friend_doll.nut", false);				 
		local time = sq_GetLevelData(obj, SKILL_DOLL, 0, skill_level); //ll
		masterAppendage.sq_SetValidTime(time); 
		masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_DOLL, skill_level);
		CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, object, obj, SKILL_DOLL, false);
		local change_appendage = masterAppendage.sq_getChangeStatus("doll");
            //masterAppendage.setEnableIsBuff(true);
            local value0 = sq_GetLevelData(obj, SKILL_DOLL, 1, skill_level); //ll
            local value1 = sq_GetLevelData(obj, SKILL_DOLL, 2, skill_level); //zl
            local value2 = sq_GetLevelData(obj, SKILL_DOLL, 3, skill_level); //atk sd
            local value3 = sq_GetLevelData(obj, SKILL_DOLL, 4, skill_level); //mov sd
            local value4 = sq_GetLevelData(obj, SKILL_DOLL, 5, skill_level); //wl defance
            local value5 = sq_GetLevelData(obj, SKILL_DOLL, 6, skill_level); //mf defance

            if(!change_appendage)
            {
                 change_appendage = masterAppendage.sq_AddChangeStatus("doll",object, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, 0);
            }
            if(change_appendage)
            {
			change_appendage.clearParameter();
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, value0.tofloat() );
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, value1.tofloat() );
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, value2.tofloat() );
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, value3.tofloat() );
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, value4.tofloat() );
                 change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, value5.tofloat() );


            }

        }
    }

}
function onProc_DOLL(obj)
{
	if(!obj) return; 
    local state = obj.getVar("state").get_vector(0);
    if (state == 1 || state == 2)
    {
        local dot = getDotObj(obj);
        if(dot)
        {
            dot.getVar("break").set_vector(0,1);
        }
    }
    if (obj.getVar("add").get_vector(0) == 1)
    {
        //addDollBuffAndFriend(obj);
        addDollBuffSelf(obj);
    }
}
function onKeyFrameFlag_DOLL(obj,flagIndex)
{
	if(!obj) return; 
    local state = obj.getVar("state").get_vector(0);
    if (state == 4)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);

            if (flagIndex == 0)
            {
                obj.getVar("add").clear_vector();
                obj.getVar("add").push_vector(0);
                CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/doll/ap_doll.nut");
                sq_setFullScreenEffect(obj,"character/mage/animation/ani_als/marionette/marionetteend02_00.ani");

            }
        }
    }
}

function onEndCurrentAni_DOLL(obj)
{
	if(!obj) return; 
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);

    }else if (state == 2)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 3)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {

        local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 50);
        sq_BinaryStartWrite();
        sq_BinaryWriteDword(0);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj, 24332, 0, posX, obj.getYPos() + 1, 0);


		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}
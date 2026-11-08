function setCustomData_po_elementalquake(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
	local attackBonusRate2 = receiveData.readDword();// ?????(%)	
	local attackBonusRate3 = receiveData.readDword();// ?????(%)	
	local attackBonusRate4 = receiveData.readDword();// ?????(%)	

    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(0);

    obj.getVar("value").clear_vector();
    obj.getVar("value").push_vector(attackBonusRate2);
    obj.getVar("value").push_vector(attackBonusRate3);
    obj.getVar("value").push_vector(attackBonusRate4);

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);


}

function onKeyFrameFlag_po_elementalquake(obj, flagIndex)
{
    if (obj.getVar("flag").get_vector(flagIndex) == 0)
    {

        if (flagIndex >= 2)
        {
            obj.setTimeEvent(0,50,0,false);
            for(local i=0;i<obj.getVar("dama").get_obj_vector_size();++i)
            {
                local damager = obj.getVar("dama").get_obj_vector(i);


            }
        }



        obj.getVar("flag").set_vector(flagIndex,1);

		local attackInfo = sq_GetCustomAttackInfo(obj, flagIndex);
		sq_SetCurrentAttackInfo(obj, attackInfo);

        local attackInfo = sq_GetCurrentAttackInfo(obj);

        local attack = obj.getVar("value").get_vector(flagIndex);
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attack);
        obj.resetHitObjectList();
    }
}

function onTimeEvent_po_elementalquake(obj, timeEventIndex, timeEventCount)
{
    if (timeEventIndex == 0)
    {
        sq_SendCreatePassiveObjectPacketPos(obj,12207, 0,obj.getXPos(), obj.getYPos() + 1, 0);
        sq_SendDestroyPacketPassiveObject(obj);
    }
}

function onEndCurrentAni_po_elementalquake(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        local ani = obj.getCustomAnimation(0);
        obj.setCurrentAnimation(ani);
        sq_SendCreatePassiveObjectPacketPos(obj,12208, 0,obj.getXPos(), obj.getYPos() + 1, 0);


        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);


    }else{

        sq_SendDestroyPacketPassiveObject(obj);	
    }
}

function onAttack_po_elementalquake(obj, damager, boundingBox, isStuck)
{

    
//    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/elementquake/ap_elementquake.nut");		

    obj.getVar("dama").push_obj_vector(damager);

    if (true)
    {
        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_mage/elementquake/ap_elementquake.nut"))
        {
            if (true )
            {
                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ELEMENTQUAKE, true, "character/new_mage/elementquake/ap_elementquake.nut", true);				 
                    if(masterAppendage) 
                    {
                        sq_HoldAndDelayDie(damager, obj, true, true, true, 200, 500, ENUM_DIRECTION_NEUTRAL , masterAppendage);
                    }
            }
        }
    }
}

function setCustomData_po_blooddog0(obj, receiveData)
{
	if(!obj)
		return;
	local attackBonusRate0 = receiveData.readDword();// ?????(%)	
    local attackBonusRate1 = receiveData.readDword();// ?????(%)	
    local time0 = receiveData.readDword();
    local time1 = receiveData.readDword();


    obj.getVar("dama").clear_obj_vector();

    obj.getVar("values").clear_vector();
    obj.getVar("values").push_vector(attackBonusRate1);
    obj.getVar("values").push_vector(time0);
    obj.getVar("values").push_vector(time1);

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate0);

}

function procAppend_po_blooddog0(obj)
{
    local var = obj.getVar("dama");  		
    local objectsSize = var.get_obj_vector_size();

	local objX = sq_GetXPos(obj);
	local objY = sq_GetYPos(obj);
	local objZ = sq_GetZPos(obj);

    local dvalue = 1;
    if (obj.getDirection() == ENUM_DIRECTION_LEFT) dvalue = -1;
    
    local frmValue = 0;


    for(local i=0;i<objectsSize;++i)
    {
        local damager = var.get_obj_vector(i);
        damager.setCurrentPos(objX + dvalue * ( 0 + frmValue),objY - 1,objZ);
    }

}


function onAttack_po_blooddog0(obj, damager, boundingBox, isStuck)
{
    obj.getVar("dama").push_obj_vector(damager);

	local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODDOG, false, "character/atmage/blooddog/ap_blooddog.nut", true);				 
	if(masterAppendage) 
    {
		sq_HoldAndDelayDie(damager, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
    }

}



function onTimeEvent_po_blooddog0(obj, timeEventIndex, timeEventCount)
{

	if(!obj.isMyControlObject())
		return false;


    if (timeEventIndex == 0) 
    {
        sq_SendDestroyPacketPassiveObject(obj);

    if (timeEventIndex == 2)
    {
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        for(local i=0;i<objectsSize;++i)
        {

            local damager = var.get_obj_vector(i);

            sq_SendHitObjectPacket(obj,damager,0,0,0);

            obj.sq_SetShake(obj, 5, 100);

        }
    }
}





function onKeyFrameFlag_po_blooddog0(obj, flagIndex)
{
    if (flagIndex == 1)
    {
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        if (objectsSize > 0 )
        {

        sq_SendDestroyPacketPassiveObject(obj);


        }

    }

}

function onEndCurrentAni_po_blooddog0(obj)
{
    sq_SendDestroyPacketPassiveObject(obj);

}



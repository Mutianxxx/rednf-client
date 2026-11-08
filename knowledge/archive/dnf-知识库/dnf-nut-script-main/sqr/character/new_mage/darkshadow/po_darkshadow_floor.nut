function setCustomData_po_darkshadow_floor(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
	local passid = receiveData.readDword();// ?????(%)	
    if (passid == 1)
    {
        local waitTime =receiveData.readDword();
        local attackTime = receiveData.readDword();
        obj.setTimeEvent(0,waitTime,0,false);
        obj.setTimeEvent(1,attackTime,0,true);
        obj.setTimeEvent(3,attackTime/2,0,true);
        obj.setTimeEvent(4,attackTime/2,0,true);

        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

    }
    if (passid == 0)
    {
        local id = receiveData.readDword();// ?????(%)	

        local waitTime =receiveData.readDword();
        local attackTime = receiveData.readDword();


        obj.setTimeEvent(0,waitTime,0,false);
        obj.setTimeEvent(1,attackTime,0,true);
        obj.setTimeEvent(3,attackTime/2,0,true);
        obj.setTimeEvent(4,attackTime/2,0,true);

        local object = sq_GetObjectByObjectId(obj,id);

        obj.getVar("friend").clear_obj_vector();
        obj.getVar("friend").push_obj_vector(object);

        obj.getVar("attack").clear_vector();
        obj.getVar("attack").push_vector(attackBonusRate);
    }

    obj.getVar("pID").clear_vector();
    obj.getVar("pID").push_vector(passid);


}


function procAppend_po_darkshadow_floor(obj)
{
    local passid = obj.getVar("pID").get_vector(0);
    if (passid == 0)
    {
        local friend = obj.getVar("friend").get_obj_vector(0);
        obj.setCurrentPos(friend.getXPos(),friend.getYPos(),0);
    }
}


function onTimeEvent_po_darkshadow_floor(obj, timeEventIndex, timeEventCount)
{
    local passid = obj.getVar("pID").get_vector(0);

    if (passid == 1)
    {
        if (timeEventIndex == 0)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }

        if (timeEventIndex == 1)
        {

            obj.resetHitObjectList();

        }

        if (timeEventIndex == 3)
        {
            sq_SendCreatePassiveObjectPacketPos(obj, 12211, sq_getRandom(0 ,1).tointeger(), obj.getXPos() + sq_getRandom(-125 , 125).tointeger(), obj.getYPos() + sq_getRandom(-50 , 50).tointeger(), 20 + sq_getRandom(0 , 25).tointeger());
        }

        if (timeEventIndex == 4)
        {
            sq_SendCreatePassiveObjectPacketPos(obj, 12212, sq_getRandom(0 ,1).tointeger(), obj.getXPos() + sq_getRandom(-125 , 125).tointeger(), obj.getYPos() + sq_getRandom(-50 , 50).tointeger(), 25 + sq_getRandom(0 , 25).tointeger());

        }

    }

    if (passid == 0)
    {
        if (timeEventIndex == 0)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }

        if (timeEventIndex == 1)
        {
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, obj.getVar("attack").get_vector(0));
            obj.resetHitObjectList();

        }

        if (timeEventIndex == 3)
        {

            sq_SendCreatePassiveObjectPacketPos(obj, 12211, sq_getRandom(0 ,1).tointeger(), obj.getXPos() + sq_getRandom(-125 , 125).tointeger(), obj.getYPos() + sq_getRandom(-50 , 50).tointeger(), 20 + sq_getRandom(0 , 25).tointeger());
        }


        if (timeEventIndex == 4)
        {
            sq_SendCreatePassiveObjectPacketPos(obj, 12212, sq_getRandom(0 ,1).tointeger(), obj.getXPos() + sq_getRandom(-125 , 125).tointeger(), obj.getYPos() + sq_getRandom(-50 , 50).tointeger(), 25 + sq_getRandom(0 , 25).tointeger());

        }
    }








}
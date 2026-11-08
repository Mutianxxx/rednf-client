function setCustomData_po_superlolly_boom(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
	local id = receiveData.readDword();// ?????(%)	
    if (id == 0)
    {
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
    }
    if (id == 1 || id == 2)
    {
        
        local ycValue1 = receiveData.readDword();
        local ycValue2 = receiveData.readDword();
        local ycValue3 = receiveData.readDword();
        local ycValue4 = receiveData.readDword();

        local ani = obj.getCustomAnimation(2*id - 2);
        local value = 17 + sq_getRandom(0,5);
        obj.setCurrentAnimation(ani);
        obj.getVar("xSpeed").clear_vector();
        obj.getVar("xSpeed").push_vector(sq_getRandom(-2,2));
        obj.getVar("ySpeed").clear_vector();
        obj.getVar("ySpeed").push_vector(sq_getRandom(-1,1));

        local dirValue = sq_getRandom(0,20);

        if (dirValue > 10)  obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));

        obj.getVar("rorateRate").clear_vector();
        obj.getVar("rorateRate").push_vector(0);

        obj.getVar("Zspeed").clear_vector();
        obj.getVar("Zspeed").push_vector(value);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),value);

		local attackInfo = sq_GetCustomAttackInfo(obj, id - 1);
		sq_SetCurrentAttackInfo(obj, attackInfo);

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
        sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 4+id, ycValue1, ycValue2, ycValue3,ycValue4);
        //5 = blind 6 = lightning

    }

    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);

}
function procAppend_po_superlolly_boom(obj)
{
    local id = obj.getVar("id").get_vector(0);

    if (id == 1 || id == 2)
    {

        local currRorateRate = obj.getVar("rorateRate").get_vector(0);
        local zSpeed = obj.getVar("Zspeed").get_vector(0);

        if (obj.getZPos() > 0 )
        {
            sq_SetCustomRotate(obj,currRorateRate.tofloat() / 100 );	

            obj.getVar("rorateRate").set_vector(0,(currRorateRate + 3) % 314);

            obj.setCurrentPos(obj.getXPos() + obj.getVar("xSpeed").get_vector(0),obj.getYPos() + obj.getVar("ySpeed").get_vector(0),obj.getZPos() + zSpeed);

            obj.getVar("Zspeed").set_vector(0,zSpeed -1);
        }else{

            sq_SetCustomRotate(obj,0.0);	
            local ani = obj.getCustomAnimation(2*id - 1);
            obj.setCurrentAnimation(ani);

        }



    }

}
function onEndCurrentAni_po_superlolly_boom(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 0)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }

    if (id == 1)
    {
		sq_SendDestroyPacketPassiveObject(obj);
    }
}
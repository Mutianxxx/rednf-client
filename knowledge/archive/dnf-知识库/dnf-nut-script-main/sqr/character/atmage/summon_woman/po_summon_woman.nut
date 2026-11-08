//24341
function setCustomData_po_nyarly(obj, receiveData)
{

	local id = receiveData.readDword();// ?????(%)	

    if (id <= 20)
    {
        local ani = obj.getCustomAnimation(id);
        obj.setCurrentAnimation(ani);
    }


}


function procAppend_po_nyarly(obj)
{
    local id = obj.getVar("id").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    if (id <= 20)
    {
        local state = mage.getVar("state").get_vector(0);
        local state2 = mage.sq_GetState();
        if (!mage || state == 2 || state2 == STATE_STAND)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

}
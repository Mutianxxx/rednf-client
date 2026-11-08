
function setCustomData_po_skill_procedtion(obj, reciveData)
{
    local id = receiveData.readDword();
    sq_SendCreatePassiveObjectPacketPos(obj, 12337, 0, obj.getXPos(), obj.getYPos(), 0);
    local ani = obj.getCustomAnimation(id);
	obj.setCurrentAnimation(ani);

}


function procAppend_po_skill_procedtion(obj)
{

    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    local state = mage.getVar("state").get_vector(0);
    if (state == 2)
    {
		sq_SendDestroyPacketPassiveObject(obj);	
    }
}
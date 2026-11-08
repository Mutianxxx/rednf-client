function setCustomData_po_doll_screen_cover(obj, receiveData)
{


	local id = receiveData.readDword();
    if (id == 0)
    {
        obj.getVar("break").clear_vector();
        obj.getVar("break").push_vector(0);
    }else if (id == 1)
    {
        local ani = obj.getCustomAnimation(0);
        obj.setCurrentAnimation(ani);
    }else if (id == 2)
    {
        local ani = obj.getCustomAnimation(1);
        obj.setCurrentAnimation(ani);
    }
    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);
}

function procAppend_po_doll_screen_cover(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 0)
    {
        local objectManager = obj.getObjectManager();

        local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
        local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);

        obj.setCurrentPos(xPos,yPos,0);
        if ( obj.getVar("break").get_vector(0) == 1 )
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 1)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 2)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 3)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }
}
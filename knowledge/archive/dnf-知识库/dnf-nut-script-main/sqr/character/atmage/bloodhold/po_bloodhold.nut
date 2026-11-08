function setCustomData_po_bloodhold_stuck(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
	local size = receiveData.readDword();// ?????(%)	
    local dir = receiveData.readDword();

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);


	local currentAni = sq_GetCurrentAnimation(obj);

    if (dir == -1) 
    {
        obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
    }else{
        obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
    }

	local sizeRate = size.tofloat() / 100.0;
	currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
	currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	
	sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

    obj.getVar("value").clear_vector();
    obj.getVar("value").push_vector(dir);
    obj.getVar("value").push_vector(sizeRate);


}


function onAttack_po_bloodhold_stuck(obj,damager, boundingBox, isStuck)
{

	if (!obj)
		return 0;
//	sq_SetMyShake(obj,4,200);

	local sourceObj = obj.getParent();

    if (!sq_IsFixture(damager))
    {
        //obj.getVar("dama").push_obj_vector(damager);

            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODHOLD, false, "character/atmage/bloodhold/ap_bloodhold.nut", true);				 
            if(masterAppendage) 
            {
                sq_HoldAndDelayDie(damager, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
            }
    }

    local dir = obj.getVar("value").get_vector(0);
    local sizeRate = obj.getVar("value").get_vector(1);

    damager.setCurrentPos(damager.getXPos() ,sourceObj.getYPos(),0);


}
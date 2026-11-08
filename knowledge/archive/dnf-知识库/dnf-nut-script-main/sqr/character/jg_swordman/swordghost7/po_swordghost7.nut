

SWORDGHOST_7_VAR_ATTACK <- 0;
SWORDGHOST_7_VAR_ID <- 1;
SWORDGHOST_7_VAR_TARID <- 2;
SWORDGHOST_7_VAR_HIT <- 3;

// setCustomData
function setCustomData_po_swordghost_7_gsb_attack_effect(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();
	local id = receiveData.readDword();
	local tarid = receiveData.readDword();
	local hit = receiveData.readDword();
	
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

		//print( "hit:" + hit);

	obj.setTimeEvent(0, 150, hit,true);

	if (id == 0)
    {
		local ani = obj.getCustomAnimation(0);
        obj.setCurrentAnimation(ani);
	}
	
	local object = sq_GetObjectByObjectId(obj,tarid);
	obj.getVar("dama").clear_obj_vector();
	obj.getVar("dama").push_obj_vector(object);
	
	
	local var = obj.getVar();
	var.setInt(SWORDGHOST_7_VAR_ATTACK,attackBonusRate);
	var.setInt(SWORDGHOST_7_VAR_ID,id);
	var.setInt(SWORDGHOST_7_VAR_TARID,tarid);
	var.setInt(SWORDGHOST_7_VAR_HIT,hit);

}

function procAppend_po_swordghost_7_gsb_attack_effect(obj)
{
	local damager = obj.getVar("dama").get_obj_vector(0);
	if (!damager)
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}else
{
      obj.setCurrentPos(damager.getXPos(),damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2);
}

}
//sq_SendHitObjectPacket(obj,damager, 0, 0, damager.getObjectHeight()/2);

function onTimeEvent_po_swordghost_7_gsb_attack_effect(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;
	
	 local damager = obj.getVar("dama").get_obj_vector(0);
	
	if(timeEventIndex == 0)
	{
		sq_SendHitObjectPacket(obj,damager, 0, 0, damager.getObjectHeight()/2);
	}
}


function onAttack_po_swordghost_7_gsb_attack_effect(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;

		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage
		(damager, obj, STATE_SWORD_GHOST_7, true, "character/JG_SwordMan/swordghost7/ap_swordghost7.nut", true);				 
			if(masterAppendage) 
			{
				//sq_HoldAndDelayDie(damager, obj, true, true, true, 1, 1, ENUM_DIRECTION_NEUTRAL , masterAppendage);
			}
}


function onEndCurrentAni_po_swordghost_7_gsb_attack_effect(obj)
{
	if(!obj)
		return;
		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
}




function setCustomData_po_swordghost_7_gsb_attack_plus(obj, receiveData)
{
	if(!obj)
		return;
	local var = obj.getVar();
	local attackBonusRate = receiveData.readDword();
	local hit = receiveData.readDword();
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

	//print( "po_attackBonusRate:" + attackBonusRate);

	obj.setTimeEvent(0, 150, hit + 1,true);
}



function onAttack_po_swordghost_7_gsb_attack_plus(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
		local sq_var = obj.getVar();	
		sq_var.push_obj_vector(damager);
		
		//print(" id:" + damager);
		
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage
		(damager, obj, STATE_SWORD_GHOST_7, true, "character/JG_SwordMan/swordghost7/ap_swordghost7.nut", true);

	//print( "onAttackdamager:" + damager);
}


function onTimeEvent_po_swordghost_7_gsb_attack_plus(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;


			if(timeEventIndex == 0)
			{		
				local sq_var = obj.getVar();

				local objectsSize = sq_var.get_obj_vector_size();
	
				for(local i = 0;i < objectsSize;++i)
				{
					local damager = sq_var.get_obj_vector(i);
					if(damager)
					sq_SendHitObjectPacket(obj,damager,0,0,0);
					//print(" i:" + i);
					//print(" objectsSize:" + objectsSize);
				}
			}

}
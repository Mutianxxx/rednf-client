











function onAttack_po_thief_shared(obj, damager, boundingBox, isStuck)
{
	if(!obj) return;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());



	switch(id)
	{
		case 9://???? ?? ju???
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ju??? ???
					sq_SetMyShake(obj, 3, 200);
				break;
			}
		break;
		case 12://???? ?? ???????? ???
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ??? ???
					obj.sendStateOnlyPacket(11);
					obj.flushSetStatePacket();
				break;
			}
		break;
		case 13://???? ?? ???????? ????
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 11://???? ?? ???????? ???? ???
					if(sq_IsGrabable(obj, damager) && sq_IsHoldable(obj, damager) && !sq_IsFixture(damager))
					{
						sq_MoveToAppendageForce(damager, obj, obj, 0, 0, 0, 200, true, Appendage);
					}
				break;
			}
		break;
	}
}




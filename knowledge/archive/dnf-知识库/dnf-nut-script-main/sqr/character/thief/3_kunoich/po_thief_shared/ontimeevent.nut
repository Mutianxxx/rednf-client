

function onTimeEvent_po_thief_shared(obj, timeEventIndex, timeEventCount)
{
	if(!obj) return false;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local state = parentChr.sq_GetState();



	switch(timeEventIndex)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.resetHitObjectList();
			}
		break;
		case 1:
			if(obj.isMyControlObject())
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 2:
			if(obj.isMyControlObject())
			{
				local xRan = x + sq_getRandom(-200, 200);
				local yRan = y + sq_getRandom(-100, 100);
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(60);//??? ??????
				sq_SendCreatePassiveObjectPacketPos(obj, 24356, 0, xRan, yRan, 0);
			}
		break;
	}
}


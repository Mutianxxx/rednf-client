











function onEndCurrentAni_po_swordman_shared(obj)
{
	if(!obj) return;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());



	switch(id)
	{
		case 24:
			if(obj.isMyControlObject())
			{
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(25);
				sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 25:
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 12:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 13:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 14:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 15:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 16:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 17:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 18:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 19:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 20:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 21:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 22:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 23:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
				case 24:
					if(obj.isMyControlObject())
					{
						parentChr.sq_StartWrite();
						parentChr.sq_WriteDword(25);
						sq_SendCreatePassiveObjectPacketPos(obj, 24349, 0, x, y, z);
						sq_SendDestroyPacketPassiveObject(obj);
					}
				break;
			}
		break;
	}
}




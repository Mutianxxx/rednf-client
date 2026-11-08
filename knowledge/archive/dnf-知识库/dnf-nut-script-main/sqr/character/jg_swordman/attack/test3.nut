
function onProc_Test3(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI3)
	{
		obj.sq_SendCreatePassiveObjectPacket(261103, 0, 0, 1, 0);
	}
}

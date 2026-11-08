
function onProc_Test6(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI6)
	{
		obj.sq_SendCreatePassiveObjectPacket(261106, 0, 0, 1, 0);
	}
}


function onProc_Test2(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI2)
	{
		obj.sq_SendCreatePassiveObjectPacket(261102, 0, 0, 1, 0);
	}
}

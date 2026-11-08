
function onProc_Test5(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI5)
	{
		obj.sq_SendCreatePassiveObjectPacket(261105, 0, 0, 1, 0);
	}
}

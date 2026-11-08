
function onProc_Test0(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI0)
	{
		obj.sq_SendCreatePassiveObjectPacket(261101, 0, 0, 1, 0);
	}
}

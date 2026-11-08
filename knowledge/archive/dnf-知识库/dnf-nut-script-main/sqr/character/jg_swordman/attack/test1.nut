
function onProc_Test1(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI1)
	{
		obj.sq_SendCreatePassiveObjectPacket(261101, 0, 0, 1, 0);
	}
}

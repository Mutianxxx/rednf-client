
function onProc_Test4(obj)
{

	if(!obj) return;
	
	local state = obj.sq_GetState();

	if(state == STATE_WEIZHI4)
	{
		obj.sq_SendCreatePassiveObjectPacket(261104, 0, 0, 1, 0);
	}
}

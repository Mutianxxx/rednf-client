

function onKeyFrameFlag_YuXueAttack(obj,flagIndex)
{
	if(!obj)
		return false;

	local state = obj.sq_GetState();
	
	if(state == STATE_YU_XUE_MO_SHA_ZHONG_JIE) 
	{
					if (flagIndex == 100)//????1
			{
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			}
	}

	return true;//???^
}
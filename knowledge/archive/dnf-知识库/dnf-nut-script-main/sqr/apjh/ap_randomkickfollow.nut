
function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_randomkickfollow")
}

function proc_appendage_randomkickfollow(appendage)
{
	if(!appendage) {
		return;
	}

	local obj = appendage.getParent();
	local x = obj.getXPos();
    local y = obj.getYPos();
    if (obj.getDirection() == ENUM_DIRECTION_RIGHT) {
		x = x + 100;
	} else {
		x = x - 100;
	}
	sq_SendCreatePassiveObjectPacketPos( obj, 90010012, 0, x, y, 0);
}

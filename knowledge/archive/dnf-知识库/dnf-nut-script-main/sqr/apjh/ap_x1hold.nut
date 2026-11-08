
function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_atgunner_x1hold")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_atgunner_x1hold")
}

function onStart_appendage_atgunner_x1hold(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	local x = obj.getXPos();
    local y = obj.getYPos();
    if (obj.getDirection() == ENUM_DIRECTION_RIGHT) {
		x = x + 150;
	} else {
		x = x - 150;
	}
	sq_SendCreatePassiveObjectPacketPos( obj, 90010011, 0, x, y, 0);
}

function onEnd_appendage_atgunner_x1hold(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	local po = obj.getMyPassiveObject(90010011, 0);
	po.sendDestroyPacket(true);
}

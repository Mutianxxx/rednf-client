
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_KEEPOUT")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_KEEPOUT")
}

function sq_AddEffect(appendage)
{
//	appendage.sq_AddEffectFront("character/mage/animation/ani_als/keepout/keepouta02_00.ani");
}
function proc_appendage_KEEPOUT(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) 
    {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_KEEPOUT(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	

	local hitEffAni = sq_CreateAnimation("","character/mage/animation/ani_als/keepout/keepouta02_00.ani");
	local hitBackEffObj = sq_CreatePooledObject(hitEffAni, true);
	hitBackEffObj.setCurrentPos(parentObj.getXPos(), parentObj.getYPos() + 1, parentObj.getZPos() + parentObj.getObjectHeight()/2);
	sq_AddObject(parentObj, hitBackEffObj, OBJECTTYPE_DRAWONLY, false);
}



function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_atmage_SecondWindHit")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_atmage_SecondWindHit")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_atmage_SecondWindHit")
}


function sq_AddEffect(appendage)
{

}





function proc_appendage_atmage_SecondWindHit(appendage)
{

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
    
    local mobX = appendage.getVar("mobPos").get_vector(0);
    local mobY = appendage.getVar("mobPos").get_vector(1);

    local chrY = sourceObj.getYPos();

    local currT = appendage.getTimer().Get();

    if (currT < 1000 )
    {
        local posY = sq_GetAccel(mobY, chrY, currT,1000 , true);
        parentObj.setCurrentPos(parentObj.getXPos(),posY,parentObj.getZPos() );
    }else{
        parentObj.setCurrentPos(parentObj.getXPos(),chrY,parentObj.getZPos() );
		appendage.setValid(false);
    }
}


function onStart_appendage_atmage_SecondWindHit(appendage)
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
    appendage.getVar("mobPos").clear_vector();
    appendage.getVar("mobPos").push_vector(parentObj.getXPos() );
    appendage.getVar("mobPos").push_vector(parentObj.getYPos() );
	
}





function onEnd_appendage_atmage_reaonance(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	
}
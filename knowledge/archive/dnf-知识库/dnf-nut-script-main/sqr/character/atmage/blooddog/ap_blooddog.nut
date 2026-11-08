
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODDOG")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODDOG")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOODDOG")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BLOODDOG(appendage)
{

    gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
    
}

function proc_appendage_BLOODDOG(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj2 = appendage.getSource();
	local sourceObj = appendage.getVar("dog").get_obj_vector(0);
//	local mage = appendage.getVar("dog").get_obj_vector(1);
				
	if(!sourceObj || !parentObj || !sourceObj2) 
    {
		appendage.setValid(false);
		return;
	}

    local startX = appendage.getVar("pos").get_vector(0);
    local startY = appendage.getVar("pos").get_vector(1);
    local objX = sourceObj.getXPos();
    local objY = sourceObj.getYPos() + 1;

    local currT = appendage.getTimer().Get();
    if (currT < 500 && !sq_IsFixture(sourceObj))
    {
        local x = sq_GetAccel(startX, objX, currT,500 , true);
        local y = sq_GetAccel(startY, objY, currT,500 , true);

        if ( parentObj.isMovablePos(objX, objY) )
        {
            parentObj.setCurrentPos(x,y - 1,0);
        }else{
            parentObj.setCurrentPos(startX,
                                    startY,
                                    parentObj.getZPos());
        }

    }else{

        if ( parentObj.isMovablePos(objX, objY) )
        {
            parentObj.setCurrentPos(objX,objY,0);
        }else{
            parentObj.setCurrentPos(startX,
                                    startY,
                                    parentObj.getZPos());
        }
    }

    gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);

}



function onStart_appendage_BLOODDOG(appendage)
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
    appendage.getVar("pos").clear_vector();
    appendage.getVar("pos").push_vector( parentObj.getXPos() );
    appendage.getVar("pos").push_vector( parentObj.getYPos() );
}


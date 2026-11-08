
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODHOLD")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODHOLD")
}


function proc_appendage_BLOODHOLD(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}

    local lastX = appendage.getVar("posParameter").get_vector(0);
    local lastY = appendage.getVar("posParameter").get_vector(1);
    local xSpeed = 200;//appendage.getVar("posParameter").get_vector(2);
    local ySpeed = 100;//appendage.getVar("posParameter").get_vector(3);

    local startX = obj.getVar("runParameter").get_vector(0);
    local startY = obj.getVar("runParameter").get_vector(1);
    local startT = obj.getVar("runParameter").get_vector(2);

    local currT = appendage.getTimer().Get();

    if ( currT - startT < 1000)
    {
        local vX = sq_GetAccel(0, xSpeed, currT - startT, 1000, true);
        local vY = sq_GetAccel(0, ySpeed, currT - startT, 1000, true);
        local mobLastX = 0;
        local mobLastY = 0;

        if (lastX < parentObj.getXPos() )
        {
            mobLastX = startX - vX;

        }else if (lastX > parentObj.getXPos()){
            mobLastX = startX + vX;
        }
        parentObj.setCurrentPos(mobLastX,parentObj.getYPos(),0);
        

    }else{

        obj.getVar("runParameter").clear_vector();
        obj.getVar("runParameter").push_vector( parentObj.getXPos() );
        obj.getVar("runParameter").push_vector( parentObj.getYPos() );
        obj.getVar("runParameter").push_vector( currT );


    }


}



function onStart_appendage_BLOODHOLD(appendage)
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

    local currT = appendage.getTimer().Get();

    obj.getVar("runParameter").clear_vector();
    obj.getVar("runParameter").push_vector( parentObj.getXPos() );
    obj.getVar("runParameter").push_vector( parentObj.getYPos() );
    obj.getVar("runParameter").push_vector( currT );

}


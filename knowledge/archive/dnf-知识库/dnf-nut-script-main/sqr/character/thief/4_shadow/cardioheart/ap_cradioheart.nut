
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CARDIOHEART")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CARDIOHEART")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_CARDIOHEART(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj ) 
    {
		appendage.setValid(false);
		return;
	}
    
    local mobX = appendage.getVar("mobPos").get_vector(0);
    local mobY = appendage.getVar("mobPos").get_vector(1);

    local chrX = appendage.getVar("chrPos").get_vector(0);
    local chrY = appendage.getVar("chrPos").get_vector(1);

    local currT = appendage.getTimer().Get();

    if (currT < appendage.getVar("movT").get_vector(0) )
    {
        local posX = sq_GetAccel(mobX, chrX, currT,appendage.getVar("movT").get_vector(0) , true);
        local posY = sq_GetAccel(mobY, chrY, currT,appendage.getVar("movT").get_vector(0) , true);
        parentObj.setCurrentPos(posX,posY,0 );
    }else{
//        parentObj.setCurrentPos(chrX,chrY,parentObj.getZPos() );
    }
}



function onStart_appendage_CARDIOHEART(appendage)
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



function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_INHANG")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_INHANG")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_INHANG(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj || sourceObj.getState() != STATE_INHANG) 
    {
		appendage.setValid(false);
		return;
	}

	local currentT = appendage.getTimer().Get();
    local startT = appendage.getVar("t").get_vector(0);

    local chrX = sourceObj.getXPos();
    local chrY = sourceObj.getYPos();

    local mobX = obj.getVar("pos").get_vector(0);
    local mobY = obj.getVar("pos").get_vector(1);
    local t = 1000;
    if (currentT > t)
    {

    }else{

        local x = sq_GetUniformVelocity(mobX,chrX,currentT,t);
        local y = sq_GetUniformVelocity(mobY,chrY,currentT,t);

//        x = parentObj.sq_findNearLinearMovableXPos(x,
//            y,parentObj.getXPos(), parentObj.getYPos(), 10);

        parentObj.setCurrentPos(0,0,0);
    }
}






function onStart_appendage_INHANG(appendage)
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
    obj.getVar("pos").clear_vector();
    obj.getVar("pos").push_vector(parentObj.getXPos());
    obj.getVar("pos").push_vector(parentObj.getYPos());

    obj.getVar("t").clear_vector();
    obj.getVar("t").push_vector( appendage.getTimer().Get() );



}


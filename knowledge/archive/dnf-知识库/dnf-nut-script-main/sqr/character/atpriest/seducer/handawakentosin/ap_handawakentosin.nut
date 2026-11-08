
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_HandAwakenToSin");
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_HandAwakenToSin");
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_HandAwakenToSin");
}

function sq_AddEffect(appendage)
{
}



function onEnd_appendage_HandAwakenToSin(appendage)
{

	local slash = appendage.getVar("slashHandAwakenToSin").get_obj_vector(0);
	slash.setValid(false);
	
	
}



function proc_appendage_HandAwakenToSin(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if (appendage.getVar("slashHandAwakenToSin").get_obj_vector_size() > 0)
	{
		local slash = appendage.getVar("slashHandAwakenToSin").get_obj_vector(0);
		local posX = parentObj.getXPos();
		local posY = parentObj.getYPos();
		local posZ = parentObj.getZPos() + parentObj.getObjectHeight()/2;
		slash.setCurrentDirection(parentObj.getDirection());
		slash.setCurrentPos(posX,posY,posZ);
		
	}
}



function onStart_appendage_HandAwakenToSin(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	local elect = sq_CreateDrawOnlyObject(parentObj,"character/priest/seducer/effect/animation/athandawakentosin/sin_01.ani",ENUM_DRAWLAYER_COVER,true);

	appendage.getVar("slashHandAwakenToSin").clear_obj_vector();	
	appendage.getVar("slashHandAwakenToSin").push_obj_vector(elect);
	
}
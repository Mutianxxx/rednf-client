
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ASSASSINATION_SUCCESS_WIDTH")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ASSASSINATION_SUCCES_WIDTH")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ASSASSINATION_SUCCES_WIDTH")
}

function sq_AddEffect(appendage)
{
//	appendage.sq_AddEffectFront("character/thief/animation/als_ani/assassination/backattack/atkbbloodwidth_a.ani");
}

function onEnd_appendage_ASSASSINATION_SUCCES_WIDTH(appendage)
{
	local elect = appendage.getVar("obj").get_obj_vector(0);
	if(elect) {
		elect.setValid(false);
	}
}

function proc_appendage_ASSASSINATION_SUCCESS_WIDTH(appendage)
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



function onStart_appendage_ASSASSINATION_SUCCES_WIDTH(appendage)
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


	local elect = sq_AddDrawOnlyAniFromParent(parentObj,"character/thief/animation/als_ani/assassination/backattack/atkbbloodwidth_a.ani", 0, 0, 0);	

	elect.setCurrentPos(parentObj.getXPos(), parentObj.getYPos()+1, parentObj.getZPos() + parentObj.getObjectHeight()/2);


    appendage.getVar("obj").clear_obj_vector();
    appendage.getVar("obj").push_obj_vector(elect);

}


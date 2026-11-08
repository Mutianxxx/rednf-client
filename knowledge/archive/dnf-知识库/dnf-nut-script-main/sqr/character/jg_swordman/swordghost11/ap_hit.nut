

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SwordGhost11")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SwordGhost11")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_SwordGhost11")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_SwordGhost11(appendage)
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

function onStart_appendage_SwordGhost11(appendage)
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
	
	local var = appendage.getVar();		
	local elect = sq_AddDrawOnlyAniFromParent(parentObj,"character/swordman/effect/animation/ghostpierce/hit_02.ani", 0, 0, 1);	
	elect.setCurrentPos(parentObj.getXPos(), parentObj.getYPos()+ 75, parentObj.getZPos() + parentObj.getObjectHeight()/2);


	local sizeRate = sq_GetUniformVelocity(5,15,parentObj.getObjectHeight() - 100, 150);
	sizeRate = sizeRate.tofloat()/7.0;
	local ani = elect.getCurrentAnimation();
	if(ani)
		ani.resize(sizeRate);
		
	var.setObject(AP_LIGHTNING_WALL_VAR_ELECT_OBJ, elect);
	var.setInt(AP_LIGHTNING_WALL_VAR_START_Z, parentObj.getZPos());
}



function onEnd_appendage_SwordGhost11(appendage)
{
	local obj = appendage.getParent();	
}

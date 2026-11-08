

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SwordGhost7")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SwordGhost7")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_SwordGhost7")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_SwordGhost7(appendage)
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

function onStart_appendage_SwordGhost7(appendage)
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
	local elect = sq_AddDrawOnlyAniFromParent(parentObj,"passiveobject/new_skill/swordghost_7_gsb/animation/hit_effect_00.ani", 0, 0, 1);	
	elect.setCurrentPos(parentObj.getXPos(), parentObj.getYPos()+1, parentObj.getZPos() + parentObj.getObjectHeight()/2);

	local sizeRate = sq_GetUniformVelocity(5,15,parentObj.getObjectHeight() - 100, 150);
	sizeRate = sizeRate.tofloat()/5.0;
	local ani = elect.getCurrentAnimation();
	if(ani)
		ani.resize(sizeRate);
		
	var.setObject(AP_LIGHTNING_WALL_VAR_ELECT_OBJ, elect);
	var.setInt(AP_LIGHTNING_WALL_VAR_START_Z, parentObj.getZPos());
	parentObj.sq_PlaySound("LIGHTWALL_ELEC");
}



function onEnd_appendage_SwordGhost7(appendage)
{
	if(!appendage) {
		return;
	}

	local var = appendage.getVar();	//???????????????
	local Ani_effect = var.getObject(0);	//???????????????
	if(Ani_effect) 
	{
		Ani_effect.setValid(false);	//????Ani_effect????????????
	}
}

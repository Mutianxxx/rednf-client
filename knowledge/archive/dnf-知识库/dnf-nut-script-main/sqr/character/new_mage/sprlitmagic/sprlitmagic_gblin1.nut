
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SPRLITMAGIC_GBLIN1")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SPRLITMAGIC_GBLIN1")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_SPRLITMAGIC_GBLIN1")
}



function sq_AddEffect(appendage)
{

}

function onEnd_appendage_SPRLITMAGIC_GBLIN1(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    local animation = sq_GetCurrentAnimation(parentObj);

    animation.setImageRateFromOriginal(1.0, 1.0);
    animation.setAutoLayerWorkAnimationAddSizeRate(1.0);

}

function proc_appendage_SPRLITMAGIC_GBLIN1(appendage)
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
	if (sourceObj.getVar("state").get_vector(0) != 0)
	{
		local animation = sq_GetCurrentAnimation(parentObj);

		animation.setImageRateFromOriginal(0.01, 0.01);
		animation.setAutoLayerWorkAnimationAddSizeRate(0.01);
		parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
				
	}else{
		parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),50);
	}
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local state = sqrObj.sq_GetState();
	if(state != STATE_SPRLITMAGIC) { 
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_SPRLITMAGIC_GBLIN1(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	appendage.sq_DeleteEffectFront();
	appendage.sq_DeleteEffectBack();
	appendage.sq_AddEffectFront("character/mage/animation/ani_als/hex/goblin.ani");
}
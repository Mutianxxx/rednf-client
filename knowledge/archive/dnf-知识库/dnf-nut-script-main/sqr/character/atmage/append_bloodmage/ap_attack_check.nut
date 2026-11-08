function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_Attack1")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_Attack1")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_Attack1")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_Attack1(appendage)
{
}

function proc_appendage_BloodMageMonsterAppendage_Attack1(appendage)
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
    local obj = appendage.getVar("spinObj").get_obj_vector(0);
    if (obj)
    {
        obj.setCurrentPos(sourceObj.getXPos(),sourceObj.getYPos(),sourceObj.getZPos());

        local x = sourceObj.getXPos();
        local y = sourceObj.getYPos();
        local z = sourceObj.getZPos();

        local x2 = parentObj.getXPos();
        local y2 = parentObj.getYPos();
        local z2 = parentObj.getZPos();

        local distance = sq_GetDistance( x, y - z, x2, y2 - z2, true);


    }

    parentObj.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
}



function onStart_appendage_BloodMageMonsterAppendage_Attack1(appendage)
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



	local elect = sq_AddDrawOnlyAniFromParent(parentObj,"passiveobject/character/mage/animation/atchainlightning/firing/6_lightning_dodge.ani", 0, 0, 0);	

    appendage.getVar("spinObj").clear_obj_vector();
    appendage.getVar("spinObj").push_obj_vector( elect );

//passiveobject/character/mage/animation/atchainlightning/target/1_target_normal.ani
//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}


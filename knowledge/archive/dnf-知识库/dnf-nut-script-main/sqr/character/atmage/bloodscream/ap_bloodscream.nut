
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODSCREAM")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODSCREAM")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOODSCREAM")
}

function sq_AddEffect(appendage)
{
//	appendage.sq_AddEffectFront("passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_front01.ani");
//	appendage.sq_AddEffectBack("passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_back01.ani");
}



function onEnd_appendage_BLOODSCREAM(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

    local front = appendage.getVar("obj").get_obj_vector(0);
    local back = appendage.getVar("obj").get_obj_vector(1);

    if (front && back)
    {

        front.setValid(false);
        back.setValid(false);
    }
    gbl_HoldAndDelayEffectSetByAppendageEnd(appendage);
}


function proc_appendage_BLOODSCREAM(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	if(!sourceObj || !parentObj || sourceObj.getState() != STATE_BLOODSCREAM) 
    {
		appendage.setValid(false);
		return;
	}else{
        
        local front = appendage.getVar("obj").get_obj_vector(0);
        local back = appendage.getVar("obj").get_obj_vector(1);

        if (front && back)
        {
            front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
            back.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() - 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
        }


        local currentT = appendage.getTimer().Get();
        local hei = 25;
        local maxT = 750;
        if (currentT < maxT)
        {
            hei = sq_GetAccel(0, hei, currentT, maxT , true);
        }

        parentObj.setCurrentPos(appendage.getVar("pos").get_vector(0),appendage.getVar("pos").get_vector(1)
        ,hei);
    }
    gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);
}



function onStart_appendage_BLOODSCREAM(appendage)
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
    appendage.getVar("pos").push_vector(parentObj.getXPos());
    appendage.getVar("pos").push_vector(parentObj.getYPos());

	local Front = sq_AddDrawOnlyAniFromParent(parentObj, "passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_front01.ani"  ,0,-1,0);
	local Back = sq_AddDrawOnlyAniFromParent(parentObj, "passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_back01.ani"  ,0,-1,0);
    appendage.getVar("obj").clear_obj_vector();

    appendage.getVar("obj").push_obj_vector(  Front );
    appendage.getVar("obj").push_obj_vector(  Back  );


}


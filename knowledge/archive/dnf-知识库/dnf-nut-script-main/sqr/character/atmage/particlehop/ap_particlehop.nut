
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ParticleHop")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ParticleHop")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ParticleHop")
}


function sq_AddEffect(appendage)
{

//	appendage.sq_AddEffectFront("character/mage/atanimation/als_ani/atdimensionleap/hold_02.ani");

}

function onEnd_appendage_ParticleHop(appendage)
{
        local front = appendage.getVar("obj").get_obj_vector(0);
        if (front)
        {

            front.setValid(false);
        }

}

function proc_appendage_ParticleHop(appendage)
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

    local front = appendage.getVar("obj").get_obj_vector(0);

    if (front)
    {
        front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
    }

}



function onStart_appendage_ParticleHop(appendage)
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
	local Front = sq_AddDrawOnlyAniFromParent(parentObj, "character/mage/atanimation/als_ani/atdimensionleap/hold_02.ani"  ,0,-1,0);


    appendage.getVar("obj").clear_obj_vector();
    appendage.getVar("obj").push_obj_vector(  Front );
}
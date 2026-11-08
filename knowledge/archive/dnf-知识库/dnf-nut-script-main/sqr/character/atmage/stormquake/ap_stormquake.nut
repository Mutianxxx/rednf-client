
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_STORMAQUAKE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_STORMAQUAKE")
}
function sq_AddEffect(appendage)
{
}

function proc_appendage_STORMAQUAKE(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    local stormObj = appendage.getVar("stromObj").get_obj_vector(0);

	if(!sourceObj || !parentObj || !stormObj) 
    {
		appendage.setValid(false);
		return;
	}


    local currT = appendage.getTimer().Get();


    local judge = sq_GetUniformVelocity(0, 360, currT % 1000,1000) + 
    appendage.getVar("judge").get_vector(0) - 360;
    judge = judge % 360;
    local len = 75;
    local angle = judge.tofloat();

	local posX = len * sq_CosTable(angle.tointeger());
	local posY = len * sq_SinTable(angle.tointeger()) * 0.29;

    local posX2 = parentObj.sq_findNearLinearMovableXPos(stormObj.getXPos() + posX.tointeger(),
            stormObj.getYPos() + posY.tointeger(),parentObj.getXPos(), parentObj.getYPos(), 10);

    parentObj.setCurrentPos(posX2,stormObj.getYPos() + posY.tointeger(),stormObj.getZPos() );

    if (posX > 0)
    {
        parentObj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
    }else{
        parentObj.setCurrentDirection(ENUM_DIRECTION_LEFT);
    }
    gbl_HoldAndDelayEffectSetDownByAppendageLoop(appendage);



}


function onStart_appendage_STORMAQUAKE(appendage)
{
	if(!appendage) {
		return;
	}
    appendage.getVar("judge").clear_vector();
    appendage.getVar("judge").push_vector(sq_getRandom(0,360).tointeger() );
	
}




function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_TeaTime")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_TeaTime")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_TeaTime")
}
function sq_AddEffect(appendage)
{
//	appendage.sq_AddEffectFront("");
}

function onEnd_appendage_TeaTime(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

    local Nyaly = getNyarly(parentObj);

        local front = appendage.getVar("obj").get_obj_vector(0);

        if (front)
        {
            front.setValid(false);
        }

}


function proc_appendage_TeaTime(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}

    local Nyaly = getNyarly(parentObj);
    if (!Nyaly || Nyaly.getVar("state").get_vector(0) != 9)
    {
		appendage.setValid(false);
		return;
    }
    local startT = appendage.getVar("t").get_vector(0);

    if (appendage.getTimer().Get() - startT > 1000)
    {
        local spendMp = parentObj.getMpMax() / 100;
        parentObj.sendSetMpPacket(parentObj.getMp() + spendMp);
        appendage.getVar("t").clear_vector();
        appendage.getVar("t").push_vector( appendage.getTimer().Get() );
    }
    if (appendage.getTimer().Get() >= 880)
    {
        local front = appendage.getVar("obj").get_obj_vector(0);
        if (front)
        {
            front.setCurrentDirection(parentObj.getDirection());
            front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 1,parentObj.getZPos() );
        }
    }
}


function onStart_appendage_TeaTime(appendage)
{
	if(!appendage) {
		return;
	}
    appendage.getVar("t").clear_vector();
    appendage.getVar("t").push_vector( appendage.getTimer().Get() );
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	createTeaCupSummonAni(parentObj);

	local Front = sq_AddDrawOnlyAniFromParent(parentObj, "character/mage/atanimation/als_ani/atteatime/teatime_teacuploop.ani"  ,0,-1,0);
    appendage.getVar("obj").clear_obj_vector();

    appendage.getVar("obj").push_obj_vector(  Front );

}



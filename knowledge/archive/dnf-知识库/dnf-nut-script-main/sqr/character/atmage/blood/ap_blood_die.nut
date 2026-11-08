
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOOD_DIE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOOD_DIE")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOOD_DIE")


}
function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BLOOD_DIE(appendage)
{
	local parentObj = appendage.getParent();
//    sq_SendCreatePassiveObjectPacketPos(parentObj, 12337, 0, parentObj.getXPos(), parentObj.getYPos(), 0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(0);	// attackBonusRate
        sq_BinaryWriteDword(3);
        sq_BinaryWriteDword(5);

		sq_SendCreatePassiveObjectPacketPos(parentObj,24357, 0,parentObj.getXPos(), parentObj.getYPos() + 1, parentObj.getZPos() + parentObj.getObjectHeight()/2 );


//	local currentAni = sq_GetCurrentAnimation(parentObj);



}

function proc_appendage_BLOOD_DIE(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
				
    if (!parentObj)
    {

//		sq_BinaryStartWrite();
//		sq_BinaryWriteDword(0);	// attackBonusRate
//        sq_BinaryWriteDword(3);
 //       sq_BinaryWriteDword(5);

//		sq_SendCreatePassiveObjectPacketPos(parentObj,24357, 0,parentObj.getXPos(), parentObj.getYPos() + 1, parentObj.getZPos() + //parentObj.getObjectHeight()/2 );

		appendage.setValid(false);
    }


}



function onStart_appendage_BLOOD_DIE(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
				
    if (!parentObj)
    {
		appendage.setValid(false);
    }

}


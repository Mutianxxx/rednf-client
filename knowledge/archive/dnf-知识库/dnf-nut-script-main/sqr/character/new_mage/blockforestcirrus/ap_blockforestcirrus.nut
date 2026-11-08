
//                            local objX = obj.getXPos();
//                            local objY = obj.getYPos();
//                            local damaX = friend.getXPos();
//                            local damaY = friend.getYPos();
//                            local damaZ = 110;
//                            local x_move = 15;
//                            local y_move = 6;
//                            if (objX < damaX) x_move = - x_move;
//                            if (objY < damaY) y_move = - y_move;


//                           if (abs(objX - damaX) < x_move *2 && abs(objY - damaY) < y_move *2)
//                            {
//                                friend.setCurrentPos(obj.getXPos(),obj.getYPos() - 1,1000);
//                            }else{
//                                friend.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
//                            }

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BlockForestCirrus")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BlockForestCirrus")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BlockForestCirrus")
}


function onEnd_appendage_BlockForestCirrus(appendage)
{
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
    if (parentObj)
    {
            sq_EffectLayerAppendage(parentObj,sq_RGB(0,0,0),1000,0,0,1000);	
            local posX = appendage.getVar("pos").get_vector(0);
            local posY = appendage.getVar("pos").get_vector(1);
            parentObj.setCurrentPos(posX,posY+5,100);
            createentranceLightBlockForestCirrus(parentObj);
//            sq_SetZVelocity(parentObj,800,-1600);
			parentObj.sq_IntVectClear();
			parentObj.sq_IntVectPush(0);
			parentObj.sq_IntVectPush(0);
			parentObj.sq_IntVectPush(0);
			parentObj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);
    }
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_BlockForestCirrus(appendage)
{
	if(!appendage) {
		return;		
	}
				
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

	local sourceObj = appendage.getSource();
    local posX = appendage.getVar("pos").get_vector(0);
    local posY = appendage.getVar("pos").get_vector(1) - 1;
    local objX = appendage.getVar("pos2").get_vector(0);
    local objY = appendage.getVar("pos2").get_vector(1);
	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
    local currT = appendage.getTimer().Get();
    if (currT <= 1000)
    {
        local lenX = objX - posX;
        local lenY = objY - posY;
        local v1 = sq_GetAccel(0, lenX, currT, 1000, true);
        local v2 = sq_GetAccel(0, lenY, currT, 1000, true);


        parentObj.setCurrentPos(objX - v1,objY - v2,100);
    }else{
        if (appendage.getVar("state").get_vector(0) == 0)
        {
            createentranceBlockForestCirrus(parentObj);

            appendage.getVar("state").set_vector(0,1);
        }
        parentObj.setCurrentPos(posX,posY,1000);
    }

}



function onStart_appendage_BlockForestCirrus(appendage)
{
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local sourceObj = appendage.getSource();

    appendage.getVar("pos2").push_vector( parentObj.getXPos() );
    appendage.getVar("pos2").push_vector( parentObj.getYPos() );
    appendage.getVar("state").clear_vector();
    appendage.getVar("state").push_vector(0);
}


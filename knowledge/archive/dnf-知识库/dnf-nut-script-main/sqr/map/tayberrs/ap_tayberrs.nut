
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_TayberrsMonsterMove")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_TayberrsMonsterMove")
}



function sq_AddEffect(appendage)
{
}


function proc_appendage_TayberrsMonsterMove(appendage)
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
    setTayberrsMonsterMoveEffectProcAppend(appendage);

}


function onStart_appendage_TayberrsMonsterMove(appendage)
{
    setTayberrsMonsterMoveEffectStartAppend(appendage);
}

function setTayberrsMonsterMoveEffectProcAppend(appendage)
{
    //if (GLOBAL_CURRENT_DUNGEON_ID == 5098 || GLOBAL_CURRENT_DUNGEON_ID == 5354 || GLOBAL_CURRENT_DUNGEON_ID == 5359)

    if (true)
    {
        local parentObj = appendage.getParent();
        if (!parentObj || !appendage)
            return false;

        if (appendage.getVar("posVar").size_vector() > 0)
        {

            local currT = appendage.getTimer().Get();

            local startX = appendage.getVar("posVar").get_vector(0);
            local startY = appendage.getVar("posVar").get_vector(1);
            local startZ = appendage.getVar("posVar").get_vector(2);

            local lastX = appendage.getVar("posVar").get_vector(3);
            local lastY = appendage.getVar("posVar").get_vector(4);

            local startT = appendage.getVar("posVar").get_vector(5);
            local moveT = appendage.getVar("posVar").get_vector(6);

            if (startT < currT )
            {
                
                local currentT = currT - startT;
                if (currentT  < moveT)
                {
                    local x = sq_GetAccel(startX, lastX, currentT, moveT, true);
                    local y = sq_GetAccel(startY, lastY, currentT, moveT, true);
                    local z = sq_GetAccel(startZ, 0, currentT, moveT, true);
                    parentObj.setCurrentPos(x,y,z);


                    if (parentObj.getState() == STATE_STAND || 
                        parentObj.getState() == STATE_SIT ||
                        parentObj.getState() == STATE_SIT_FOREVER ||
                        parentObj.getState() == STATE_DIE ||
                        parentObj.getState() == STATE_JUMP ||
                        parentObj.getState() == STATE_DAMAGE ||
                        parentObj.getState() == STATE_DOWN ||
                        parentObj.getState() == STATE_HOLD)
                    {


                    }else{
                        parentObj.addSetStatePacket(STATE_STAND, null, STATE_PRIORITY_FORCE, false, "");
                        parentObj.flushSetStatePacket();
                    }
                }
            }


        }
    }
}



function setTayberrsMonsterMoveEffectStartAppend(appendage)
{

    //if (GLOBAL_CURRENT_DUNGEON_ID == 5098)
    local stage = sq_GetGlobaludpModuleStage();
    if (!stage)
	return false;
    local mapIndex = sq_GetMapIndex(stage);
    if (true)
    {
        local parentObj = appendage.getParent();
        if (!parentObj || !appendage)
            return false;

        appendage.getVar("posVar").clear_vector();
        appendage.getVar("posVar").push_vector( parentObj.getXPos() );
        appendage.getVar("posVar").push_vector( parentObj.getYPos() );
        appendage.getVar("posVar").push_vector( parentObj.getZPos() );


        if (mapIndex == 4941)
        {
            appendage.getVar("posVar").push_vector( sq_getRandom(950,1250).tointeger() );
            appendage.getVar("posVar").push_vector( sq_getRandom(100,200).tointeger() );
            appendage.getVar("posVar").push_vector( 5000 );
            appendage.getVar("posVar").push_vector( 2000 );
        }else if (mapIndex == 4942)
        {
            if (sq_getRandom(0,100).tointeger() < 50)
            {
                appendage.getVar("posVar").push_vector( sq_getRandom(1250,1550).tointeger() );
            }else{
                appendage.getVar("posVar").push_vector( sq_getRandom(650,950).tointeger() );
            }
            appendage.getVar("posVar").push_vector( sq_getRandom(100,200).tointeger() );
            appendage.getVar("posVar").push_vector( 2000 + sq_getRandom(0,2).tointeger() * 1000  );
            appendage.getVar("posVar").push_vector( 2000 );
        }else if (mapIndex == 4943)
        {
            appendage.getVar("posVar").push_vector( 1250 );
            appendage.getVar("posVar").push_vector( 150 );
            appendage.getVar("posVar").push_vector( 2000);
            appendage.getVar("posVar").push_vector( 2000 );
        }else if (mapIndex == 4944)
        {
            if (sq_getRandom(0,100).tointeger() < 50)
            {
                appendage.getVar("posVar").push_vector( sq_getRandom(1350,1650).tointeger() );
            }else{
                appendage.getVar("posVar").push_vector( sq_getRandom(750,1050).tointeger() );
            }
            appendage.getVar("posVar").push_vector( sq_getRandom(100,200).tointeger() );
            appendage.getVar("posVar").push_vector( 4000 + sq_getRandom(0,2).tointeger() * 3000 );
            appendage.getVar("posVar").push_vector( 2000 );
        }else if (mapIndex == 4945)
        {
            appendage.getVar("posVar").push_vector( 1250 );
            appendage.getVar("posVar").push_vector( 150 );
            appendage.getVar("posVar").push_vector( 2000 );
            appendage.getVar("posVar").push_vector( 2000 );
        }else if (mapIndex == 4948)
        {
            appendage.getVar("posVar").set_vector(0,1250);
            appendage.getVar("posVar").set_vector(1,150);
            appendage.getVar("posVar").set_vector(2,500);

            appendage.getVar("posVar").push_vector( 1250 );
            appendage.getVar("posVar").push_vector( 150 );
            appendage.getVar("posVar").push_vector( 4000 );
            appendage.getVar("posVar").push_vector( 200 );
        }
    }

}



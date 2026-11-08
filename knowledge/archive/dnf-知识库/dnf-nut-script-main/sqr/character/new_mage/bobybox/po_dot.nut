function setCustomData_po_dot(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)

    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    obj.getVar("master").clear_obj_vector();
    obj.getVar("master").push_obj_vector(mage);

    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(0);
    obj.getVar("break").clear_vector();
    obj.getVar("break").push_vector(0);

	local pIntVec = sq_GetGlobalIntVector();
	obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
}


//0 stand 1 talk 2 run
function setState_po_dot(obj, state2, datas) {
	if(!obj)
		return;
	local state = obj.getVar("state").get_vector(0);
	local mage = obj.getTopCharacter();
	mage = sq_ObjectToSQRCharacter(mage);
	if (state == 0) {
		local ani = obj.getCustomAnimation(0);
		obj.setCurrentAnimation(ani);

	} else if (state == 1) {
		//        
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);


	} else if (state == 2) {
		local ani = obj.getCustomAnimation(2);
		obj.setCurrentAnimation(ani);
	} else if (state == 3) // jumpdotquake
	{
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {
			local ani = obj.getCustomAnimation(3);
			obj.setCurrentAnimation(ani);
			obj.getVar("isUp").clear_vector();
			obj.getVar("isUp").push_vector(0);
		} else if (subState == 1) {
			local ani = obj.getCustomAnimation(4);
			obj.setCurrentAnimation(ani);
		}
	} else if (state == 4) { //madd
		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {
			local ani = obj.getCustomAnimation(5);
			obj.setCurrentAnimation(ani);
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(1);
			sq_BinaryWriteDword(obj.getVar("value").get_vector(1));
			createPassiveAndDirection(mage, obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			createPassiveAndDirection(mage, obj, 12249, 0, obj.getXPos(), obj.getYPos() + 1, 0);
		} else if (subState == 1) {

			local ani = obj.getCustomAnimation(6);
			obj.setCurrentAnimation(ani);
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(2);
			sq_BinaryWriteDword(obj.getVar("value").get_vector(1));
			createPassiveAndDirection(mage, obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			createPassiveAndDirection(mage, obj, 12250, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			createPassiveAndDirection(mage, obj, 12289, 0, obj.getXPos(), obj.getYPos() + 2, 0);
		}
	} else if (state == 5) //720
	{ //maddefance

		local subState = obj.getVar("subState").get_vector(0);
		if (subState == 0) {

			obj.getVar("pos").clear_vector();
			obj.getVar("pos").push_vector(obj.getXPos());
			obj.getVar("pos").push_vector(obj.getYPos());

			local ani = obj.getCustomAnimation(7);
			obj.setCurrentAnimation(ani);



		} else if (subState == 1) {
			local ani = obj.getCustomAnimation(8);
			obj.setCurrentAnimation(ani);
			obj.getVar("flag").clear_vector();
			obj.getVar("flag").push_vector(0);
		}



	} else if (state == 6) {
		local ani = obj.getCustomAnimation(9);
		obj.setCurrentAnimation(ani);
	} else if (state == 7) // madbigdot
	{
		local ani = obj.getCustomAnimation(10);
		obj.setCurrentAnimation(ani);
		createPassiveAndDirection(mage, obj, 12284, 0, obj.getXPos(), obj.getYPos() + 1, 0);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);

	} else if (state == 8) {
		local subState = obj.getVar("subState").get_vector(0);

		if (subState == 0) //storageCapactiy
		{
			local ani = obj.getCustomAnimation(11);
			obj.setCurrentAnimation(ani);
		} else if (subState == 1) //out start
		{

			local ani = obj.getCustomAnimation(12);
			obj.setCurrentAnimation(ani);


		} else if (subState == 2) //out loop
		{
			obj.setTimeEvent(1, obj.getVar("value").get_vector(0), 0, false);
			local ani = obj.getCustomAnimation(13);
			obj.setCurrentAnimation(ani);
			sq_SetMyShake(obj, 3, obj.getVar("value").get_vector(0));
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(obj.getVar("value").get_vector(1).tointeger());
			sq_BinaryWriteDword(11);
			sq_BinaryWriteDword(obj.getVar("value").get_vector(2).tointeger());
			sq_BinaryWriteDword(obj.getVar("value").get_vector(0).tointeger());
			createPassiveAndDirection(mage, obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);

		} else if (subState == 3) //out end
		{
			local ani = obj.getCustomAnimation(14);
			obj.setCurrentAnimation(ani);

			//            local mage = obj.getTopCharacter();
			//            mage = sq_ObjectToSQRCharacter(mage);	
			//            mage.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, false);

		}


	} else if (state == 9) //doll forest ma jump
	{
		local ani = obj.getCustomAnimation(15);
		obj.setCurrentAnimation(ani);
	} else if (state == 10) //curseofdot
	{
		local subState = obj.getVar("subState").get_vector(0);
		local atk = (1300 + obj.getVar("value").get_vector(1)) / obj.getVar("value").get_vector(2);

		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);


		if (subState == 0) {
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(obj.getVar("value").get_vector(0));
			sq_BinaryWriteDword(12);
			sq_BinaryWriteDword(atk);
			createPassiveAndDirection(mage, obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			local ani = obj.getCustomAnimation(16);
			obj.setCurrentAnimation(ani);
		} else if (subState == 1) {
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(obj.getVar("value").get_vector(0));
			sq_BinaryWriteDword(13);
			sq_BinaryWriteDword(atk);
			sq_BinaryWriteDword(obj.getVar("value").get_vector(1));
			createPassiveAndDirection(mage, obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);

			obj.setTimeEvent(1, obj.getVar("value").get_vector(1), 0, false);
			local ani = obj.getCustomAnimation(17);
			obj.setCurrentAnimation(ani);
		} else if (subState == 2) {
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(obj.getVar("value").get_vector(0));
			sq_BinaryWriteDword(14);
			sq_BinaryWriteDword(atk);
			createPassiveAndDirection(mage, obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
			local ani = obj.getCustomAnimation(18);
			obj.setCurrentAnimation(ani);
		}
	} else if (state == 11) //madshoot
	{
		local substate = obj.getVar("substate").get_vector(0);
		if (substate == 0) {
			local ani = obj.getCustomAnimation(19);
			obj.setCurrentAnimation(ani);
		} else if (substate == 1) {
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(obj.getVar("value").get_vector(0));
			sq_BinaryWriteDword(16);
			sq_BinaryWriteDword(obj.getVar("value").get_vector(1));
			createPassiveAndDirection(mage, obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);

			local ani = obj.getCustomAnimation(20);
			obj.setCurrentAnimation(ani);
		} else if (substate == 2) {
			local ani = obj.getCustomAnimation(21);
			obj.setCurrentAnimation(ani);
		}
	}

	local mage = obj.getTopCharacter();
	mage = sq_ObjectToSQRCharacter(mage);
	local animation = sq_GetCurrentAnimation(obj);
	mage.sq_SetCurrentTimeByFrame(animation, 0);


	local delay = animation.getDelaySum(false);
	obj.setTimeEvent(1000, delay, 1, false);
	obj.getVar("currentT").clear_vector();
	obj.getVar("currentT").push_vector(0);
	obj.setTimeEvent(1001, 10, 0, false);


}



function onEndCurrentAniTime_po_dot(obj)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    if (state == 11)
    {
        local substate = obj.getVar("substate").get_vector(0);
        if (substate == 0)
        {
            obj.getVar("substate").set_vector(0,1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (substate == 1)
        {

            obj.getVar("substate").set_vector(0,2);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (substate == 2)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }
    else if (state == 3)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            obj.setCurrentPos(sq_GetDistancePos(obj.getXPos(),  obj.getDirection(), obj.getVar("value").get_vector(0) ),obj.getYPos(),obj.getZPos());
            obj.getVar("subState").set_vector(0,1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else{

        }
    }else if (state == 4)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if(subState == 0)
        {
            obj.getVar("subState").set_vector(0,1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else{
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 5)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            obj.getVar("subState").clear_vector();
            obj.getVar("subState").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");



        }else {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 6)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        local pIntVec = sq_GetGlobalIntVector();
        obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }else if (state == 7)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }else if (state == 8)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 1)
        {
            obj.getVar("subState").clear_vector();
            obj.getVar("subState").push_vector(2);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if(subState == 3)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 10)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            obj.getVar("subState").clear_vector();
            obj.getVar("subState").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (subState == 2)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }

}
function onAttack_po_dot(obj,damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
}


function onKeyFrameFlag_po_dot(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    if (state == 10)
    {

        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            local subState = obj.getVar("subState").get_vector(0);
            obj.getVar("flag").set_vector(flagIndex,1);
            if (subState == 0)
            {
                if(flagIndex == 1)
                {

                }else if (flagIndex == 2)
                {
                    sq_SetMyShake(obj,10,240);
                    sq_BinaryStartWrite();
                    sq_BinaryWriteDword( 0 );
                    sq_BinaryWriteDword(8);
                    sq_BinaryWriteDword( obj.getVar("value").get_vector(3) );
                    createPassiveAndDirection(mage,obj, 24366, 0, 
                    sq_GetDistancePos(obj.getXPos(),  obj.getDirection(), 460 ) , obj.getYPos() - 1, 0);


                }else if (flagIndex == 3)
                {
                    sq_flashScreen(obj,10,50,10,76, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                }
            }
        }   



    }else if (state == 3)
    {
        if (flagIndex == 1 && obj.getVar("isUp").get_vector(0) == 0)
        {
            obj.getVar("isUp").clear_vector();
            obj.getVar("isUp").push_vector(1);
            createPassiveAndDirection(mage,obj, 12246, 0, obj.getXPos(), obj.getYPos() + 1, 0);
        }
    }else if(state == 5)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            sq_SetMyShake(obj,3,120);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword( obj.getVar("value").get_vector(0) );
            sq_BinaryWriteDword(90 );
            createPassiveAndDirection(mage,obj, 24357, 0, obj.getXPos(), obj.getYPos() + 1, 0);



        }
    }else if(state == 6)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            sq_BinaryStartWrite();
            sq_BinaryWriteDword(3);
            sq_BinaryWriteDword( obj.getVar("value").get_vector(0) );
            createPassiveAndDirection(mage,obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 33);
            createPassiveAndDirection(mage,obj, 12252, 0, obj.getXPos(), obj.getYPos() + 1, 0);



        }
    }else if (state == 7)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            if (flagIndex == 1)
            {
                sq_SetMyShake(obj,3,120);
                createPassiveAndDirection(mage,obj, 12292, 0, obj.getXPos(), obj.getYPos() + 1, 0);
            }
            else if (flagIndex >= 4 && flagIndex <= 9)
            {
                local dama = obj.getVar("value").get_vector(0);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(dama);
                sq_BinaryWriteDword(9);
                sq_BinaryWriteDword( flagIndex - 3 );
                createPassiveAndDirection(mage,obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                sq_SetMyShake(obj,6,60);
            }else if (flagIndex == 10)
            {
                local dama = obj.getVar("value").get_vector(1);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(dama);
                sq_BinaryWriteDword(10);
                sq_BinaryWriteDword(obj.getVar("value").get_vector(2));
                createPassiveAndDirection(mage,obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                createPassiveAndDirection(mage,obj, 12291, 0, obj.getXPos(), obj.getYPos() - 1, 0);
                sq_SetMyShake(obj,12,300);


                local mage = obj.getTopCharacter();
                mage = sq_ObjectToSQRCharacter(mage);	

                mage.getVar("state").set_vector(0,2);
                mage.sq_AddSetStatePacket(STATE_MADBIGDOG, STATE_PRIORITY_IGNORE_FORCE, true);
            }
        }
    }
}


function procAppend_po_dot(obj)
{
	if(!obj)
		return;
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
	if(!mage)
		return;
    mage = sq_ObjectToSQRCharacter(mage);


    local posX = sq_GetDistancePos(mage.getXPos(),  mage.getDirection(), 75);
    local posY = mage.getYPos();
    local mageState = obj.sq_GetParentState();
    if (!mage || obj.getVar("break").get_vector(0) == 1 || mageState == STATE_DIE)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }
    if (state == 0)
    {
        if (mageState == STATE_DASH)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
        if ( abs( obj.getXPos() - posX ) < 7 && abs(obj.getYPos() - posY) < 3 )
        {
                obj.setCurrentDirection( mage.getDirection() );
        }else{
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");

        }
    }else if (state == 1)
    {
        if (mageState == STATE_DASH)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }

        if ( abs( obj.getXPos() - posX ) < 5 && abs(obj.getYPos() - posY) < 3 )
        {
            obj.setCurrentPos(posX,posY,0);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else{
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            local movX = obj.getXPos() - posX;
            local movY = obj.getYPos() - posY;

            local movXSpeed = 3;
            local movYSpeed = 1;

            if (obj.getXPos() > posX)
            {
                obj.setCurrentPos(obj.getXPos() - movXSpeed,obj.getYPos(),0);
                obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
            }else if (obj.getXPos() < posX)
            {
                obj.setCurrentPos(obj.getXPos() + movXSpeed,obj.getYPos(),0);
                obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
            }

            if (obj.getYPos() > posY)
            {
                obj.setCurrentPos(obj.getXPos(),obj.getYPos() - movYSpeed,0);
            }else if (obj.getYPos() < posY)
            {
                obj.setCurrentPos(obj.getXPos(),obj.getYPos() + movYSpeed,0);
            }
        

        }
        
    }else if (state == 2)
    {


//            local posX2 = sq_GetDistancePos(mage.getXPos(),  mage.getDirection(), 40);
//            obj.setCurrentPos(posX2,posY + 1,0);
//            obj.setCurrentDirection( mage.getDirection() );






            if (abs(obj.getXPos() - posX ) < 50 && abs(obj.getYPos() - posY ) < 15 )
            {

                local posX2 = sq_GetDistancePos(mage.getXPos(),  mage.getDirection(), 40);
                obj.setCurrentPos(posX2,posY + 1,0);
                obj.setCurrentDirection( mage.getDirection() );
                if (mageState != STATE_DASH)
                {
                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(1);
                    local pIntVec = sq_GetGlobalIntVector();
                    obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
                }

            }else{

                local movXSpeed = 9;
                local movYSpeed = 3;
                if (obj.getXPos() > posX)
                {
                    obj.setCurrentPos(obj.getXPos() - movXSpeed,obj.getYPos(),0);
                    obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
                }else if (obj.getXPos() < posX)
                {
                    obj.setCurrentPos(obj.getXPos() + movXSpeed,obj.getYPos(),0);
                    obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
                }

                if (obj.getYPos() > posY)
                {
                    obj.setCurrentPos(obj.getXPos(),obj.getYPos() - movYSpeed,0);
                }else if (obj.getYPos() < posY)
                {
                    obj.setCurrentPos(obj.getXPos(),obj.getYPos() + movYSpeed,0);
                }
            }
        


//            if (mageState != STATE_DASH)
//            {
//                obj.getVar("state").clear_vector();
//                obj.getVar("state").push_vector(1);
//                local pIntVec = sq_GetGlobalIntVector();
//                obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
//            }

    }else if (state == 3)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            if (obj.getVar("isUp").get_vector(0) == 1)
            {
                obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() + 30);
            }
        }else if (subState == 1)
        {
            if (obj.getZPos() <= 0)
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(0);
                sq_BinaryWriteDword( obj.getVar("value").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("value").get_vector(2) );
                createPassiveAndDirection(mage,obj, 24346, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                sq_flashScreen(obj,100,0,100,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                createPassiveAndDirection(mage,obj, 12247, 0, obj.getXPos(), obj.getYPos() + 1, 0);
                createPassiveAndDirection(mage,obj, 12248, 0, obj.getXPos(), obj.getYPos() - 1, 0);
                createPassiveAndDirection(mage,obj, 12290, 0, obj.getXPos(), obj.getYPos() + 2, 0);
                sq_SetMyShake(obj,5,200);
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);
                local pIntVec = sq_GetGlobalIntVector();
                obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
            }else{
                obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() - 60);
            }
        }
    }else if (state == 5)
    {
        //720

        if ( obj.getVar("subState").get_vector(0) == 0 )
        {
            local currentT = obj.getVar("currentT").get_vector(0);
            if (obj.getVar("subState").get_vector(0) == 0)
            {
                    local tar = obj.getVar("tar").get_obj_vector(0);
                    local posX = tar.getXPos();
                    local posY = tar.getYPos();

                    if ( abs( obj.getXPos() - posX ) < 12 && abs(obj.getYPos() - posY) < 6 )
                    {
                        obj.setCurrentPos(posX,posY,0);
                        obj.getVar("subState").clear_vector();
                        obj.getVar("subState").push_vector(1);
                        local pIntVec = sq_GetGlobalIntVector();
                        obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
                    }else{
                        if (obj.getXPos() > posX)
                        {
                            obj.setCurrentPos(obj.getXPos() - 9,obj.getYPos(),0);
                            obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
                        }else if (obj.getXPos() < posX)
                        {
                            obj.setCurrentPos(obj.getXPos() + 9,obj.getYPos(),0);
                            obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
                        }

                        if (obj.getYPos() > posY)
                        {
                            obj.setCurrentPos(obj.getXPos(),obj.getYPos() - 4,0);
                        }else if (obj.getYPos() < posY)
                        {
                            obj.setCurrentPos(obj.getXPos(),obj.getYPos() + 4,0);
                        }

                    }

            }
        }
    }else if (state == 8)
    {
        if (obj.getVar("subState").get_vector(0) > 0)
        {

        	//setRangeObjectPosEx(obj, 200, sq_GetDistancePos(0, obj.getDirection(), 0), 0, ENUM_DIRECTION_NEUTRAL, 0, 400, 200, 2);
        
        }
    }
}


function onTimeEvent_po_dot(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    if (timeEventIndex == 1000)
    {
        onEndCurrentAniTime_po_dot(obj);
    }else if (timeEventIndex == 1001)
    {
        local currentT = obj.getVar("currentT").get_vector(0);
        obj.getVar("currentT").set_vector(0,currentT + 10);
    }
    if (state == 5)
    {
        if (timeEventIndex == 0)
        {
            local currT = obj.getVar("currentT").get_vector(0);
            obj.getVar("currentT").set_vector(0,currT+80);
        }
    }else if (state == 8)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 2 && timeEventIndex == 1)
        {
            obj.getVar("subState").clear_vector();
            obj.getVar("subState").push_vector(3);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 10)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 1 && timeEventIndex == 1)
        {
            obj.getVar("subState").clear_vector();
            obj.getVar("subState").push_vector(2);
            local pIntVec = sq_GetGlobalIntVector();
            obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }
}   
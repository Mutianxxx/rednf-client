

function setCustomData_po_Nyarly(obj, receiveData) {
	if (!obj) return;
	local id = receiveData.readDword();
	if (id == 0) {
		obj.getVar("tar").clear_obj_vector();
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(3);
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(13, pIntVec, STATE_PRIORITY_AUTO, false, "");
	} else if (id == 1) {
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(10);
		obj.getVar("subState").clear_vector();
		obj.getVar("subState").push_vector(0);
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(20, pIntVec, STATE_PRIORITY_AUTO, false, "");
	}
	obj.setTimeEvent(999, 10, 0, false);
	obj.setTimeEvent(1000, 200, 0, false);
	obj.setTimeEvent(1001, receiveData.readDword(), 0, false);
}

function setState_po_Nyarly(obj, state, datas) {
	if (!obj) return;
	local PosX = sq_GetXPos(obj);
	local PosY = sq_GetYPos(obj);
	local PosZ = sq_GetZPos(obj);
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) {
		local ani = obj.getCustomAnimation(0);
		obj.setCurrentAnimation(ani);
	} else if (state == 1) {
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
	} else if (state == 2) {
		local ani = obj.getCustomAnimation(2);
		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
		local mage = obj.getTopCharacter();
		if (!mage) return;
		mage = sq_ObjectToSQRCharacter(mage);
		local power = mage.sq_GetPowerWithPassive(SKILL_SUMMON_WOMAN, STATE_SUMMON_WOMAN, 2, -1, 1.0);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackPower(attackInfo, power);

		if (sq_getRandom(0, 100).tointeger() < 50) {
			ani = obj.getCustomAnimation(3);
			attackInfo = sq_GetCustomAttackInfo(obj, 1);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackPower(attackInfo, power);
			local powerd = mage.sq_GetPowerWithPassive(SKILL_SUMMON_WOMAN, STATE_SUMMON_WOMAN, 3, -1, 1.0);
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(125);
			sq_BinaryWriteDword(powerd);
			sq_SendCreatePassiveObjectPacketPos(obj, 24379, 0, PosX, PosY, PosZ+65);
		}
		sq_SetCurrentAttackInfo(obj, attackInfo);
		obj.setCurrentAnimation(ani);
		if (sq_GetSkillLevel(mage, SKILL_STH_0) > 0) {
			ani.setSpeedRate(100.0 +
				sq_GetLevelData(mage, SKILL_STH_0, 5, mage.sq_GetSkillLevel(SKILL_STH_0)).tofloat());
		}
	} else if (state == 3) {
		obj.sq_PlaySound("R_NYARLY_MEET");
		local ani = obj.getCustomAnimation(4);
		obj.setCurrentAnimation(ani);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
	} else if (state == 4) {
		local ani = obj.getCustomAnimation(5);
		obj.setCurrentAnimation(ani);
	} else if (state == 5) {
		local subState = obj.getVar("subState").get_vector(0);
		local ani = obj.getCustomAnimation(6 + subState % 7);
		ani.setSpeedRate(200.0);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local mage = obj.getTopCharacter();
		obj.setCurrentPos(obj.getVar("dance").get_vector(0), obj.getVar("dance").get_vector(1), 0);
		local tar = findAngleTargetWithParticleVoid(obj, 1, 360, -1);
		if (tar) {
			local apX = tar.getXPos();
			local apY = tar.getYPos();
			obj.setCurrentPos(apX, apY, 0);
		}
		
		mage = sq_ObjectToSQRCharacter(mage);
		local power = mage.sq_GetPowerWithPassive(SKILL_WOMANDANCE, STATE_WOMANDANCE, 1, -1, 1.0);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackPower(attackInfo, power);

	} else if (state == 6) {
		local ani = obj.getCustomAnimation(13);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 3);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local mage = obj.getTopCharacter();

		obj.setCurrentPos(obj.getVar("dance").get_vector(0), obj.getVar("dance").get_vector(1), 0);
		local tar = findAngleTargetWithParticleVoid(obj, 1, 360, -1);
		if (tar) {
			local apX = tar.getXPos();
			local apY = tar.getYPos();
			obj.setCurrentPos(apX, apY, 0);
		}

		mage = sq_ObjectToSQRCharacter(mage);
		local power = mage.sq_GetPowerWithPassive(SKILL_WOMANDANCE, STATE_WOMANDANCE, 2, -1, 1.0);
		attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackPower(attackInfo, power);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);

	} else if (state == 7) {
		local subState = obj.getVar("subState").get_vector(0);
		local ani = null;
		if (subState == 0) {
			ani = obj.getCustomAnimation(14);
			obj.setCurrentAnimation(ani);
		} else if (subState == 1) {
			ani = obj.getCustomAnimation(15);
			obj.setCurrentAnimation(ani);
			local attackInfo = sq_GetCustomAttackInfo(obj, 4);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local mage = obj.getTopCharacter();
			mage = sq_ObjectToSQRCharacter(mage);
			local power = mage.sq_GetPowerWithPassive(SKILL_WOMANCONTROL, STATE_WOMANCONTROL, 0, -1, 1.0);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackPower(attackInfo, power);

			obj.getVar("dama").clear_obj_vector();
			sq_SetMyShake(obj, 3, 200);

		} else if (subState == 2) {
			ani = obj.getCustomAnimation(16);
			obj.setCurrentAnimation(ani);
		} else if (subState == 3) {
			ani = obj.getCustomAnimation(17);
			obj.setCurrentAnimation(ani);

			local
			var = obj.getVar("dama");
			local objectsSize =
				var.get_obj_vector_size();
			if (objectsSize > 0) {
				for (local i = 0; i < objectsSize; ++i) {
					local damager =
						var.get_obj_vector(i);
					if (damager) {
						CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/womancontrol/ap_womancontrol.nut");
					}
				}
			}
		}

	} else if (state == 8) {
		local ani = obj.getCustomAnimation(18);
		obj.setCurrentAnimation(ani);

		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);

	} else if (state == 9) {
		local ani = obj.getCustomAnimation(0);
		obj.setCurrentAnimation(ani);
	} else if (state == 10) {
		local subState = obj.getVar("subState").get_vector(0);
		local ani = null;

		if (subState == 0) {

			obj.getVar("dama").clear_obj_vector();

			ani = obj.getCustomAnimation(19);
			createFrontTeportWomanControl(obj);
			local mage = obj.getTopCharacter();
			mage = sq_ObjectToSQRCharacter(mage);

			local posX = sq_GetDistancePos(mage.getXPos(), mage.getDirection(), 100);
			obj.setCurrentPos(posX, mage.getYPos() + 1, 0);
			obj.setCurrentDirection(mage.getDirection());

		} else if (subState == 1) {
			ani = obj.getCustomAnimation(20);

		} else if (subState == 2) {
			ani = obj.getCustomAnimation(21);
			obj.setTimeEvent(0, 50, 0, false);

			local attackInfo = sq_GetCustomAttackInfo(obj, 5);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local mage = obj.getTopCharacter();
			mage = sq_ObjectToSQRCharacter(mage);
			local power = mage.sq_GetPowerWithPassive(SKILL_NULL85, STATE_NULL85, 0, -1, 1.0);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackPower(attackInfo, power);
			obj.setTimeEvent(1, mage.sq_GetIntData(SKILL_NULL85, 2), 0, false);
		} else if (subState == 3) {
			ani = obj.getCustomAnimation(22);

		}
		obj.setCurrentAnimation(ani);
	} else if (state == 11) {
		local subState = obj.getVar("subState").get_vector(0);
		local ani = null;

		if (subState == 0) {
			local mage = obj.getTopCharacter();
			mage = sq_ObjectToSQRCharacter(mage);
			local posX = sq_GetDistancePos(mage.getXPos(), mage.getDirection(), -75);
			obj.setCurrentPos(posX, mage.getYPos() + 1, 0);
			obj.setCurrentDirection(mage.getDirection());

			ani = obj.getCustomAnimation(23);
		}
		obj.setCurrentAnimation(ani);

	}

	local animation = sq_GetCurrentAnimation(obj);
	sq_SetAnimationCurrentTimeByFrame(animation, 0, false);

}

function onKeyFrameFlag_po_Nyarly(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 3)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            sq_SetMyShake(obj,2,150);
        }
    }else if (state == 6)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            sq_flashScreen(obj,0,0,240,127, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
    }else if (state == 8)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	

            obj.getVar("flag").set_vector(0,1);
            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), mage.sq_GetIntData(SKILL_ATG, 2) );
            local power = mage.sq_GetPowerWithPassive(SKILL_ATG, STATE_ATG, 2, -1, 1.0);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(0 );	// attackBonusRate
            sq_BinaryWriteDword(111);

            local voidObj = getParticleVoid(mage);
            if (voidObj.getVar("state").get_vector(0) == PARTICLE_VOLD_STATE_MYSELF)
            {
                sq_BinaryWriteDword(power);
                sq_BinaryWriteDword(mage.sq_GetIntData(SKILL_ATG, 0) );
                sq_BinaryWriteDword(mage.sq_GetIntData(SKILL_ATG, 1) );
                sq_BinaryWriteDword(0 );
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, posX , obj.getYPos() + 1 , obj.getZPos() + 200);
            }else{

                local target = voidObj.getVar("tar").get_obj_vector(0);
                if (target)
                {

                    local id = sq_GetObjectId(target);

                    power = mage.sq_GetPowerWithPassive(SKILL_ATG, STATE_ATG, 1, -1, 1.0);
                    local power2 = mage.sq_GetPowerWithPassive(SKILL_ATG, STATE_ATG, 0, -1, 1.0);
                    sq_BinaryWriteDword(power);
                    sq_BinaryWriteDword(mage.sq_GetIntData(SKILL_ATG, 0) );
                    sq_BinaryWriteDword(mage.sq_GetIntData(SKILL_ATG, 1) );
                    sq_BinaryWriteDword(1);
                    sq_BinaryWriteDword(id );
                    sq_BinaryWriteDword(power2);
                    sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, 0,0,0);


                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(target, obj, 
                    SKILL_ATG, false, "character/atmage/atg/ap_atg.nut", true);				 

                    if(masterAppendage) 
                    {
                        masterAppendage.sq_SetValidTime( mage.sq_GetIntData(SKILL_ATG, 3) );
                    }

                }


            }



        }
    }
}


function onAfterDamage_po_Nyarly(obj, attacker, boundingBox)
{
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());

}

function onEndCurrentAni_po_Nyarly(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 2 || state == 3)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        local pIntVec = sq_GetGlobalIntVector();
        sq_IntVectorClear(pIntVec);
        sq_IntVectorPush(pIntVec, 0);
        obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }else if (state == 4)
    {
        sq_SendDestroyPacketPassiveObject(obj);	
    }else if (state == 5)
    {
        local subState = obj.getVar("subState").get_vector(0);

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local hitCount = sq_GetLevelData(mage, SKILL_WOMANDANCE, 0, sq_GetSkillLevel(mage, SKILL_WOMANDANCE) );
        if (subState < hitCount - 1)
        {
            obj.getVar("subState").set_vector(0,subState + 1);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(15, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else{

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(6);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(16, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 6)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        local pIntVec = sq_GetGlobalIntVector();
        sq_IntVectorClear(pIntVec);
        sq_IntVectorPush(pIntVec, 0);
        obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }else if (state == 7)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            obj.getVar("subState").set_vector(0,1);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(17, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (subState == 1)
        {
            obj.getVar("subState").set_vector(0,2);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(17, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (subState == 2)
        {

        }else if (subState == 3)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);

            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }else if (state == 8)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);

            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }else if (state == 10)
    {   
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 0)
        {
            obj.getVar("subState").set_vector(0,1);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(20, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if(subState == 1)
        {
            obj.getVar("subState").set_vector(0,2);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(20, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if(subState == 2)
        {
            obj.getVar("subState").set_vector(0,3);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(20, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }else if (subState == 3)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);

            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }
}
function setNyarlyMoveByPos(obj,x,y)
{
    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(1);

    obj.getVar("nyarlyPos").clear_vector();
    obj.getVar("nyarlyPos").push_vector(x);
    obj.getVar("nyarlyPos").push_vector(y);

	local pIntVec = sq_GetGlobalIntVector();
	sq_IntVectorClear(pIntVec);
	sq_IntVectorPush(pIntVec, 0);
	obj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");

}

function onTimeEvent_po_Nyarly(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    if (timeEventIndex == 0)
    {
        if (state == 10)
        {
            local subState = obj.getVar("subState").get_vector(0);
            if(subState == 2)
            {
                if (timeEventCount % 2 == 0)
                {
                    createNull85NewDust1(obj,sq_getRandom(-100,550).tointeger(),sq_getRandom(-50,50).tointeger(),0);
                }else{
                    createNull85NewDust2(obj,sq_getRandom(-100,550).tointeger(),sq_getRandom(-50,50).tointeger(),0);
                }
            }
        }   
    }else if (timeEventIndex == 1)
    {
        if (state == 10)
        {
            local subState = obj.getVar("subState").get_vector(0);
            if(subState == 2)
            {
                local var = obj.getVar("dama");  		
                local objectsSize = var.get_obj_vector_size();


                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    sq_SendHitObjectPacket(obj,damager,0,0,0);
                }

            }
        }   
    }else if (timeEventIndex == 1001)
    {
        obj.sq_PlaySound("NYARLY_DIE");
        sq_SendDestroyPacketPassiveObject(obj);	
    }else if (timeEventIndex == 1000)//200
    {
        if (state == 0)
        {
            if (obj.getVar("tar").get_obj_vector_size() <= 0)
            {


                if (sq_getRandom(0,100).tointeger() < 20)
                {
                    local toX = mage.getXPos() + sq_getRandom(-125,125).tointeger();
                    local toY = mage.getYPos()+ sq_getRandom(-50,50).tointeger();
                    setNyarlyMoveByPos(obj,toX,toY);
                }
                obj.getVar("tar").clear_obj_vector();
                local target = findAngleTargetWithParticleVoid(obj, 800, 360, 300);
                if (target)
                {

                    obj.getVar("tar").push_obj_vector(target);

                }

            }else{
                local tar = obj.getVar("tar").get_obj_vector(0);
                local posX = abs(tar.getXPos() - obj.getXPos());
                local posY = abs(tar.getYPos() - obj.getYPos());

                if (posX < 150 && posY < 30)
                {


                    if (tar.getXPos() > obj.getXPos() )
                    {
                        obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
                    }else{
                        obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
                    }

                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(2);
                    local pIntVec = sq_GetGlobalIntVector();
                    sq_IntVectorClear(pIntVec);
                    sq_IntVectorPush(pIntVec, 0);
                    obj.addSetStatePacket(12, pIntVec, STATE_PRIORITY_AUTO, false, "");
                    
                }else{
                    local toX = tar.getXPos() + sq_getRandom(-75,75).tointeger();
                    local toY = tar.getYPos()+ sq_getRandom(-15,15).tointeger();
                    setNyarlyMoveByPos(obj,toX,toY);
                }

            }
        }else if (state == 1)
        {
            if (obj.getVar("tar").get_obj_vector_size() <= 0)
            {
                obj.getVar("tar").clear_obj_vector();
                local target = findAngleTarget(obj, 300, 180, 100);
                if (target)
                {

                    obj.getVar("tar").push_obj_vector(target);

                }

            }


        }

    }else if (timeEventIndex == 999)
    {
        if (state == 0)
        {
            if (obj.getVar("tar").get_obj_vector_size() <= 0)
            {

                local posX = obj.getXPos() - mage.getXPos();
                local posY = obj.getYPos() - mage.getYPos();
                if ( posX * posX + posY * posY >= 300 * 300)
                {
                        local toX = mage.getXPos() + sq_getRandom(-125,125).tointeger();
                        local toY = mage.getYPos()+ sq_getRandom(-50,50).tointeger();
                        setNyarlyMoveByPos(obj,toX,toY);
                }
            }else{

            }
        }else if (state == 1)
        {
            local destinationX = obj.getVar("nyarlyPos").get_vector(0);
            local destinationY = obj.getVar("nyarlyPos").get_vector(1);
            local objX = obj.getXPos();
            local objY = obj.getYPos();
            local speed = 2;

            if (objX < destinationX )
            {
                obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
            }else if (objX > destinationX ){
                obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
            }

            local dstX = sq_GetDistancePos(objX, obj.getDirection(), speed);
            local dstY = 0;
            if (abs(dstX - destinationX) <= 3* speed )
            {
                dstX = destinationX;
            }

            if (abs(objY - destinationY) <= 3* speed )
            {
                dstY = 0;
            }else{
                if ( objY - destinationY > 0 )
                {
                    dstY = - speed;
                }else{
                    dstY = speed;
                }
            }


            if (dstX == destinationX && dstY == 0)
            {

                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(0);
                local pIntVec = sq_GetGlobalIntVector();
                sq_IntVectorPush(pIntVec, 0);
                obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");

            }else{

                obj.setCurrentPos(dstX,obj.getYPos() + dstY ,0);
            }

        }
    }
}

function onAttack_po_Nyarly(obj,damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 7)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 1)
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_WOMANCONTROL, false, "character/atmage/womancontrol/ap_womancontrol.nut", true);
            if(masterAppendage) 
            {
                	obj.getVar("dama").push_obj_vector(damager);
                    local mage = obj.getTopCharacter();
    			local level = sq_GetSkillLevel(mage, 140);
    			local time= sq_GetIntData(mage, 140, 2,level);
                	sq_HoldAndDelayDie(damager, obj, true, false, false, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
			masterAppendage.sq_SetValidTime(time);//ap????
                
            }
		  }
    }
}

function procAppend_po_Nyarly(obj)
{
    local state = obj.getVar("state").get_vector(0);
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    if (mage.isDead() && state != 4)
    {
        obj.sq_PlaySound("NYARLY_DIE");
        sq_SendDestroyPacketPassiveObject(obj);	
    }

    if (state == 7)
    {
        local subState = obj.getVar("subState").get_vector(0);
        if (subState == 2)
        {
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);



            if (currentT > mage.sq_GetIntData(SKILL_WOMANCONTROL, 2) )
            {
                obj.getVar("subState").set_vector(0,3);
                local pIntVec = sq_GetGlobalIntVector();
                sq_IntVectorPush(pIntVec, 0);
                obj.addSetStatePacket(17, pIntVec, STATE_PRIORITY_AUTO, false, "");
            }
        }
    }else if (state == 9)
    {
        local mageState = obj.sq_GetParentState();
        if (mageState == STATE_DASH)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
    }

}

function findOneTargetWithDistance(obj)
{
	local objectManager = obj.getObjectManager();
    local distance = 1000 * 1000;
    local target = null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) &&object.isInDamagableState(obj))
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            if (true)
            {
                
                local curDistance = abs(obj.getXPos() - object.getXPos() ) * abs(obj.getXPos() - object.getXPos() ) + 
                                 abs(obj.getYPos() - object.getYPos() ) * abs(obj.getYPos() - object.getYPos() );

                if (activeObj.isBoss() )
                {
                    return activeObj;
                }
                if (curDistance < distance)
                {
                    distance = curDistance;
                    target = activeObj;


                }
                //return activeObj;
            }
		}
	}
    return target;
}

POI_CUSTOM_ANI_SMALL_ICE	<- 0;
POI_CUSTOM_ANI_SMOKE		<- 1;
POI_CUSTOM_ANI_DODGE		<- 2;
POI_CUSTOM_ANI_SMALL_DODGE	<- 3;

PIECE_OF_ICE_EXPLOSION <- 2;

function setCustomData_po_ATPieceOfIce(obj, reciveData)
{
	if(!obj) return;

	local isSmall = reciveData.readWord() < 2;
	local horizonAngle = reciveData.readFloat(); //??‡‘·À ??·À??·À
	local verticalAngle = reciveData.readFloat(); //??·À??·À ??·À??·À
	local lifeTime = reciveData.readWord();
	local attackPower = 0;
	
	local mage = obj.getTopCharacter();
	mage = sq_ObjectToSQRCharacter(mage);	
	if (mage) {
		attackPower = mage.sq_GetBonusRateWithPassive(SKILL_PIECE_OF_ICE , STATE_PIECE_OF_ICE, 0, 1.0);
	}
		
	obj.sq_SetMoveParticle("Particle/ATPieceOfice.ptl", horizonAngle.tofloat(), verticalAngle.tofloat());
//	obj.sq_SetMoveParticle("Particle/ATPieceOfice.ptl", 0.0, verticalAngle.tofloat());
//    obj.sq_SetMoveParticle("Particle/ATPieceOfice.ptl", horizonAngle.tofloat(), 0.0);
	
	local iceAni;
	if(isSmall)	
	{
      obj.setCurrentAnimation(obj.getCustomAnimation(POI_CUSTOM_ANI_SMALL_ICE));
      iceAni = obj.getCurrentAnimation();      
            
      local dodge = sq_CreateAnimation("PassiveObject/Character/Mage/Animation/ATPieceOfIce/","06_piece_dodge_1.ani");
      iceAni.addLayerAnimation(1,dodge,true);// ??·À??·À      	
	}
	else
	{		
      iceAni = obj.getCurrentAnimation();      
            
      local dodge = sq_CreateAnimation("PassiveObject/Character/Mage/Animation/ATPieceOfIce/","06_piece_dodge_1.ani");
      iceAni.addLayerAnimation(1,dodge,true);// ??·À??·À      		
	}	
	

    local angle = -horizonAngle.tointeger()  ;

//	local angle = -sq_Atan2( verticalAngle, abs(horizonAngle) );

	local posX = 100.0 * sq_CosTable(angle );
	local posY = 10.0 * sq_SinTable(angle ) ;

    if (posX != 0)
    {
        local tan = posY / posX ;

        if (posX < 0)
        {
            tan = tan + 3.14;
        }

        sq_SetCustomRotate(obj,tan);
    }else{

        if (angle == 90)
        {
            sq_SetCustomRotate(obj,1.57);	
        }else{
            sq_SetCustomRotate(obj,-1.57);	
        }

    }


	obj.setTimeEvent(0,lifeTime,1,false);
	
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), attackPower);
	
	local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);


    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(obj.getXPos());
    obj.getVar("flag").push_vector(obj.getYPos());
    obj.getVar("flag").push_vector(obj.getZPos());

}



function setState_po_ATPieceOfIce(obj, state, datas)
{
	if(!obj) return;
	
	if(state == PIECE_OF_ICE_EXPLOSION) {
		obj.sq_RemoveMoveParticle();
		local explosionAni = obj.getCustomAnimation(POI_CUSTOM_ANI_SMOKE);		
		obj.setCurrentAnimation(explosionAni);		
	}	
}



function procAppend_po_ATPieceOfIce(obj)
{
	if(!obj) return;
	
    local currentAni = sq_GetCurrentAnimation(obj);
    local currentT = sq_GetCurrentTime(currentAni);

    if (currentT > 50 && obj.getVar("flag").get_vector(0) == 0)
    {
        local startX = obj.getVar("flag").get_vector(1);
        local startY = obj.getVar("flag").get_vector(2);
        local startZ = obj.getVar("flag").get_vector(3);
        obj.getVar("flag").set_vector(0,1);

/*
        setChainEffectWithAnimationByCurrentPos(currentAni,
        [startX,startY,startZ],
        [obj.getXPos(),obj.getYPos(),obj.getZPos()],
        -1);
*/

        local angle = getRorateAngleByCurrentPos(obj,startX,
                                                     startY,
                                                     startZ,
                                                     obj.getXPos(),
                                                     obj.getYPos(),
                                                     obj.getZPos() );

        if (( obj.getDirection() == ENUM_DIRECTION_LEFT &&  startX < obj.getXPos() ) || 
        (obj.getDirection() == ENUM_DIRECTION_RIGHT && startX > obj.getXPos() ))
        {
            angle = -angle - sq_ToRadian(180.0);
        }

        sq_SetCustomRotate(obj,angle);

    }
	if(obj.isMyControlObject())
	{	
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);	
		if (mage) {
//			if(!mage.isMovablePos(obj.getXPos(), obj.getYPos()))
//				obj.sendStateOnlyPacket(PIECE_OF_ICE_EXPLOSION);
		}
	}
}		



function onTimeEvent_po_ATPieceOfIce(obj, timeEventIndex, timeEventCount)
{		
	if(!obj)
		return false;

	if(timeEventIndex == 0)
	{
		obj.sendStateOnlyPacket(PIECE_OF_ICE_EXPLOSION);
	
		return true; // true??·À ??”ﬂ·À ?€””¿·À
	}	
	return false;	
} 


function onEndCurrentAni_po_ATPieceOfIce(obj)
{
	if(!obj) return;
	
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj); // ??·À?‚Ù‡‘·À??·À ismycontrol Àÿ?
	}
}
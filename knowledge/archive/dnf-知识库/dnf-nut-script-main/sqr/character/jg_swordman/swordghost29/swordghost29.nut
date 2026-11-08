function checkExecutableSkill_SwordGhost29(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_29);

	if (isUse) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29 , STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost29(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;

	return true;
}

function Body_SwordGhost29_ren_1_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	
	local angle = 25;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_2_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
		local angle = -48;	//????????????
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_3_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
			local angle = 48;	//????????????
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_4_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local angle = -25;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_5_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_6_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local angle = 48;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_7_two(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local angle = 0;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_02.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}


function Body_SwordGhost29_ren_1(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	
	local angle = 25;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_2(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
		local angle = -48;	//????????????
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_3(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
			local angle = 48;	//????????????
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_4(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local angle = -25;	//????????????

	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_5(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_6(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
		local angle = 48;	//????????????
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));//??????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_7(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local ani = sq_CreateAnimation("","passiveobject/new_skill/swordghost_29_kuanghuan/animation/body/ghost_ren_01.ani");//????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function Body_SwordGhost29_ren_hit(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local ani = sq_CreateAnimation("","character/swordman/effect/animation/ghost_29_ren/ghost_ren_hit_effect_01.ani");//????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function onProc_SwordGhost29(obj)

{

	local substate = obj.getSkillSubState();
	
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	
	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();


		local hitInterval = 500; // ???? (ms)
		if (IsInterval(obj, hitInterval))
		{

		}



	if(substate == 0) 
	{

	}
	if(substate == 1) 
	{
		local sq_var = obj.getVar();
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos
		local direction = sq_GetDirection(obj);//????????????V
		
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = -250;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
	  			local T = sq_GetAccel(0, -180, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				 sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				 sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = 250;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
	  			local T = sq_GetAccel(0, -180, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				 sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				 sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 2) 
		
	{

				
		local sq_var = obj.getVar("dash");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = 235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 630, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);

				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = -235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 630, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 3) 
		
	{

				
		local sq_var = obj.getVar("attack2");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = -235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 200, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);

				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = 235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 200, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 4) 
		
	{

				
		local sq_var = obj.getVar("attack3");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = 235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 200, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);

				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = -235;//PX
	  			local v = sq_GetAccel(0, Zlen, currentT, 200, true);	//????
	  			local T = sq_GetAccel(0, 200, currentT, 200, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 5) 
		
	{

				
		local sq_var = obj.getVar("attack4");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = -75;//PX
				local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = 75;//PX
				local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 6) 
		
	{

				
		local sq_var = obj.getVar("attack5");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), srcZ + 30);
				local Zlen = 350;//PX
				local v = sq_GetAccel(0, Zlen, currentT, -1, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				//sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX + 0);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), srcZ + 30);
				local Zlen = -350;//PX
				local v = sq_GetAccel(0, Zlen, currentT, -1, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				//sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX - 0);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 7) 
		{

				
		local sq_var = obj.getVar("attack6");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		
		if(direction == ENUM_DIRECTION_LEFT) 
		{
				local Zlen = 135;//PX
				local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
				local Zlen = -135;//PX
				local v = sq_GetAccel(0, Zlen, currentT, 75, true);	//????
				local T = sq_GetAccel(0, 500, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
	if(substate == 8) 
		
	{

				
		local sq_var = obj.getVar("attack7");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // z pos

		local direction = sq_GetDirection(obj);//????????????V
		
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), -32);
				local Zlen = 350;//PX
				local v = sq_GetAccel(0, Zlen, currentT, -1, true);	//????
				local T = sq_GetAccel(0, 515, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				//sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX + 0);	//???????????B???????0??x?? 1??y?? 2??z??
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetCurrentPos(obj, obj.getXPos(), obj.getYPos(), 32);
				local Zlen = -350;//PX
				local v = sq_GetAccel(0, Zlen, currentT, -1, true);	//????
				local T = sq_GetAccel(0, 515, currentT, 75, true);	//????
				local dstZ = sq_GetDistancePos(srcZ, obj.getDirection(), v);
				local dstX = sq_GetDistancePos(srcX, obj.getDirection(), T);
				//sq_setCurrentAxisPos(obj, 2, dstZ);	//???????????B???????0??x?? 1??y?? 2??z??
				sq_setCurrentAxisPos(obj, 0, dstX - 0);	//???????????B???????0??x?? 1??y?? 2??z??
		}
	}
}


function onSetState_SwordGhost29(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	
	obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_28_GHOST_REN_1);	//????ATK????
	local gaugeValue_rate = setSwordGhost3State(obj);
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_28 , -1, 0, 1.0 + gaugeValue_rate.tofloat());
	obj.sq_SetCurrentAttackBonusRate(damage);				//??????SKL??????v??	
	
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_00_START);
		//sq_flashScreen(obj, 350, 2400, 450, 200, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
		local sq_var = obj.getVar();
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		local posY = obj.getYPos();
		
		local sq_var = obj.getVar("START");//????????????????????
		obj.getVar("START").clear_vector();
		obj.getVar("START").push_vector(posZ);
		obj.getVar("START").push_vector(posx);
		obj.getVar("START").push_vector(posY);

	}
	else if(substate == 1)
	{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_01_JUMP);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
            obj.sq_SendCreatePassiveObjectPacket(260212, 0, 65, 0, 76);
			
	}
	else if(substate == 2)
	{
		obj.sq_PlaySound("SM_ATK_BS_01_1");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_02_DASH);
			Body_SwordGhost29_ren_1(obj, 500, 140, 0);
			Body_SwordGhost29_ren_1_two(obj, 500, 140, 0);
			        Body_SwordGhost29_ren_hit(obj, -500, 140, 0);
	//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			//obj.sq_SetShake(obj,4,50);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 3)
	{
		obj.sq_PlaySound("SM_ATK_BS_02_1");
			Body_SwordGhost29_ren_2(obj, 85, 0 172);
			Body_SwordGhost29_ren_2_two(obj, 85, 0 172);
			
			        Body_SwordGhost29_ren_hit(obj, 85, 0 172);
			
			//obj.sq_SetShake(obj,4,50);//?????
	//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_03_ATTACK2);
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 4)
	{
		obj.sq_PlaySound("SM_ATK_BS_03_1");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_04_ATTACK3);
			Body_SwordGhost29_ren_3(obj, 65, 0, 0);
			Body_SwordGhost29_ren_3_two(obj, 65, 0, 0);
			
			        Body_SwordGhost29_ren_hit(obj, 65, 0, 0);
			
			//obj.sq_SetShake(obj,4,50);//?????
	//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 5)
	{
		obj.sq_PlaySound("SM_ATK_BS_04_1");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_05_ATTACK4);
			Body_SwordGhost29_ren_4(obj, 300, 0, 59);
			Body_SwordGhost29_ren_4_two(obj, 300, 0, 59);
						        Body_SwordGhost29_ren_hit(obj, 300, 0, 59);
			//obj.sq_SetShake(obj,4,50);//?????
	//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 6)
	{
		obj.sq_PlaySound("SM_ATK_BS_04_2");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_06_ATTACK5);
			Body_SwordGhost29_ren_5(obj, 281, 0, 90);
			Body_SwordGhost29_ren_5_two(obj, 281, 0, 90);
						        Body_SwordGhost29_ren_hit(obj, 281, 0, 90);
			//obj.sq_SetShake(obj,4,50);//?????
			//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 7)
	{
		obj.sq_PlaySound("SM_ATK_BS_03_2");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_06_ATTACK5);
			Body_SwordGhost29_ren_6(obj, 361, 0, 0);
			Body_SwordGhost29_ren_6_two(obj, 361, 0, 0);
			//Body_SwordGhost29_ren_hit(obj, 281, 0, 90);
			//obj.sq_SetShake(obj,4,50);//?????
			//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 8)
	{
		obj.sq_PlaySound("SM_ATK_BS_02_2");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_06_ATTACK7);
			Body_SwordGhost29_ren_7(obj, 300, 0, 63);
			Body_SwordGhost29_ren_7_two(obj, 300, 0, 63);
			//Body_SwordGhost29_ren_hit(obj, 281, 0, 90);
			//obj.sq_SetShake(obj,4,50);//?????
			//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
	else if(substate == 9)
	{
		obj.sq_PlaySound("SM_ATK_BS_01_1");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_29_GHOST_KUANGHUAN_06_ATTACK7);
			//Body_SwordGhost29_ren_5(obj, 281, 0, 90);
			//Body_SwordGhost29_ren_5_two(obj, 281, 0, 90);
			//Body_SwordGhost29_ren_hit(obj, 281, 0, 90);
			//obj.sq_SetShake(obj,4,50);//?????
			//sq_flashScreen(obj, 0, 10, 20, 150, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);//?????
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.5, 1.5);	//????????????t?????
	}
}

function onKeyFrameFlag_SwordGhost29(obj,flagIndex)
{
	if(!obj)
		return false;
	local substate = obj.getSkillSubState();

	if(substate == 0)
	{
		if (flagIndex == 1)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_29_ren/ghost_ren_yuanling_n.ani"), -30, 0);
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_29_ren/ghost_ren_yuanling_l.ani"), -30, 0);
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_29_ren/ghost_ren_yuanling_l.ani"), -30, 0);
		return true;
        }
	}
	else if(substate == 1)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyc_00.ani"), 0, 2);
		return true;
        }
	}
	else if(substate == 2)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyc_00.ani"), 0, 0);


		return true;
        }
	}
	else if(substate == 3)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyA_00.ani"), 0, 0);



		return true;
        }
	}
	else if(substate == 4)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyB_00.ani"), 0, 0);
       
		return true;
        }
	}
	else if(substate == 5)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyC_00.ani"), 0, 0);
		return true;
        }
	}
	else if(substate == 6)
	{

		if (flagIndex == 3)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/tripleslashbs/tripleslashbsreadyB_00.ani"), 0, 0);
		return true;
        }
	}
}


function onEndCurrentAni_SwordGhost29(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);
		
		local sq_var = obj.getVar();
		local posZ = obj.getZPos();
		local posx = obj.getXPos();


		local ani = obj.sq_GetCurrentAni();
		local delay = 0; 
		if(ani)
		delay = ani.getDelaySum(false);
		
		obj.getVar().clear_vector();
		obj.getVar().push_vector(posZ);
		obj.getVar().push_vector(posx);

			//obj.sq_SetShake(obj,5,130);//?????
	}
	else if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);
		
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		
		local sq_var = obj.getVar("dash");
		obj.getVar("dash").clear_vector();
		obj.getVar("dash").push_vector(posZ);
		obj.getVar("dash").push_vector(posx);


		
		
	}
	else if(substate == 2)
	{

		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		
		local sq_var = obj.getVar("attack2");
		obj.getVar("attack2").clear_vector();
		obj.getVar("attack2").push_vector(posZ);
		obj.getVar("attack2").push_vector(posx);

		
		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if(substate == 3)
	{
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		
		local sq_var = obj.getVar("attack3");
		obj.getVar("attack3").clear_vector();
		obj.getVar("attack3").push_vector(posZ);
		obj.getVar("attack3").push_vector(posx);

		

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);

		
	}
	else if(substate == 4)
	{
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		
		local sq_var = obj.getVar("attack4");
		obj.getVar("attack4").clear_vector();
		obj.getVar("attack4").push_vector(posZ);
		obj.getVar("attack4").push_vector(posx);

		
		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(5);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);

		}
	else if(substate == 5)
	{
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		local sq_var = obj.getVar("attack5");
		obj.getVar("attack5").clear_vector();
		obj.getVar("attack5").push_vector(posZ);
		obj.getVar("attack5").push_vector(posx);

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(6);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if(substate == 6)
	{
		local posZ = obj.getZPos();
		local posx = obj.getXPos();
		
		local sq_var = obj.getVar("attack6");
		obj.getVar("attack6").clear_vector();
		obj.getVar("attack6").push_vector(posZ);
		obj.getVar("attack6").push_vector(posx);

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(7);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);

	}
	else if(substate == 7)
	{
		local posZ = 0;
		local posx = obj.getXPos();
		
		local sq_var = obj.getVar("attack7");
		obj.getVar("attack7").clear_vector();
		obj.getVar("attack7").push_vector(posZ);
		obj.getVar("attack7").push_vector(posx);

		local direction = sq_GetDirection(obj);//????????????V
		if(direction == ENUM_DIRECTION_LEFT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if(direction == ENUM_DIRECTION_RIGHT) 
		{
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(8);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_29, STATE_PRIORITY_IGNORE_FORCE, true);
		
	}
	else if(substate == 8)
	{
		local sq_var = obj.getVar("START");
		local srcZ = sq_var.get_vector(0); // z pos
		local srcX = sq_var.get_vector(1); // X pos
		local srcY = sq_var.get_vector(2); // X pos
		sq_SetCurrentPos(obj,srcX,srcY,srcZ);	
		
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		
	}
}




function getScrollBasisPos_SwordGhost29(obj)
{
	if (!obj) return;
	local subState = obj.getSkillSubState();
	if (obj.isMyControlObject())
	{
		local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 300);//???V??????
		local xPos = obj.getXPos();
		if (subState == 0)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(xPos, destX, stateTimer, 300);
		}
		else if (subState == 1)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, 450);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 2)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 3)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		
		else if (subState == 4)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 5)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 6)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 7)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -220);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else if (subState == 8)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(destX, xPos, stateTimer, -550);//?????? = (?????????????, ??????????, ?????????, ??????? ?????? ????????)
		}
		else
		{
			xPos = destX;
		}
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), 0);//1:??????o????????? 2:????????e????????? 
		return true;
	}
	return false;
}
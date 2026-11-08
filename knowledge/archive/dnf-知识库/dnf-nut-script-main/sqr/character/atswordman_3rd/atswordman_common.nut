function ATSwordman_Als_Ani(obj,aniFilename, disX, disY, disZ, imgangle, imgRate, Parent, SpeedRate)
{
	local angle = imgangle;	
	local ani = sq_CreateAnimation("",aniFilename);
	sq_SetfRotateAngle(ani, sq_ToRadian(-angle.tofloat()));
	local sizeRate = imgRate;
	local size = sizeRate.tofloat() / 100.0;
	ani.setImageRateFromOriginal(size, size);
	ani.setAutoLayerWorkAnimationAddSizeRate(size);
	local setSpeedRateF = 100 * SpeedRate;
	ani.setSpeedRate(setSpeedRateF.tofloat()); 
	local pooledObj = sq_CreatePooledObject(ani,true);
	sq_ChangeDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	if (Parent == 0)
	{
		sq_moveWithParent(obj, pooledObj);
	}
		sq_AddObject(obj,pooledObj,2,false);
}

function ATSwordman_Create(obj,aniFilename,ENUM_DRAWLAYER_NORMAL,Xpos,Ypos,Zpos,angle,sizeRate,Parent,Speed,Push_obj)
{
	local image = sq_CreateDrawOnlyObject(obj,aniFilename,ENUM_DRAWLAYER_NORMAL,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), Xpos);
	image.setCurrentPos(posX,obj.getYPos() + Ypos,obj.getZPos() + Zpos);
	local rotate = angle.tointeger() * 0.017453;
	image.setCustomRotate(true,rotate);
	local imageAni = image.getCurrentAnimation();
	local size = sizeRate.tofloat() / 100.0;
	imageAni.Proc();
	imageAni.setImageRateFromOriginal(size, size);
	imageAni.setAutoLayerWorkAnimationAddSizeRate(size);
	if (Speed == 101)
	{
		image.setCurrentDirection(0);
	}
	if (Speed == 102)
	{
		image.setCurrentDirection(1);
	}
	else
	{
		image.setCurrentDirection(obj.getDirection());
	}
	imageAni.setSpeedRate(Speed.tofloat());
	if (Parent == 0)
	{
		sq_moveWithParent(obj, image);
	}
}


function GetATSwordmanTarget_Contes(obj)
{
	if(!obj)
	return null;
	local objectManager = obj.getObjectManager();
	if (objectManager == null)
	return null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && !sq_IsFixture(object) && sq_IsHoldable(obj,object) && sq_IsGrabable(obj,object))
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);

			if(activeObj.isBoss() == true)
			{
				return activeObj;
			}
			else if(sq_IsNamed(activeObj) == true)
			{
				return activeObj;
			}
			else if(activeObj.isCommonChampion() == true && activeObj.isChampion() == true)
			{
				return activeObj;
			}
		}
	}
}

function GetATSwordmanTarget_ContesT(obj)
{
	if(!obj)
		return null;
	local objectManager = obj.getObjectManager();
	if (objectManager == null)
	return null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) && !sq_IsFixture(object) && sq_IsHoldable(obj,object) && sq_IsGrabable(obj,object))
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
			
			if(activeObj.isBoss() == true)
			{
				return activeObj;
			}
			else if(sq_IsNamed(activeObj) == true)
			{
				return activeObj;
			}
			else if(activeObj.isCommonChampion() == true && activeObj.isChampion() == true)
			{
				return activeObj;
			}
			else
			{
				return activeObj;
			}
		}
	}
}


function ATSwordmanGetVarTimer(obj, maxTimerNum, eventTerm, eventMaxCount)
{
	if(maxTimerNum <= 0)
		return;
	local sq_var = obj.getVar();
	sq_var.clear_timer_vector();
	for (local i = 0;i < maxTimerNum; i+=1)
	{
		sq_var.push_timer_vector();
	}
	for (local i = 0;i < maxTimerNum; i+=1)
	{
		local t = sq_var.get_timer_vector(i);
		t.setParameter(eventTerm, eventMaxCount);
		t.resetInstant(i);
	}
}

function GetFindMapArea_Enemy(obj, Name, XStart, XEnd, YRange)
{
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			if(sq_IsinMapArea(obj, object, XStart, XEnd, YRange))
			{
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
				local sq_var = obj.getVar(Name);
				sq_var.push_obj_vector(activeObj);
			}
		}
	}
}

function UniformVelocityMapMove_X(obj,name,MoveMax,MoveSpeed)
{
	if(!obj)
		return false;
	local pAni = obj.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);
	local CurrentT = sq_GetCurrentTime(pAni);
	local srcX = obj.getVar(name).get_vector(0);
	local v = sq_GetUniformVelocity(0, MoveMax, CurrentT, MoveSpeed);
	local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();
	if(obj.isMovablePos(dstX, posY))
	{
		sq_setCurrentAxisPos(obj, 0, dstX);
	}
}
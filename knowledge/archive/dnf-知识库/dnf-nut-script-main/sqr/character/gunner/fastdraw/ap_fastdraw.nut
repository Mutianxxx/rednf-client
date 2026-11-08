function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_fastdraw")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_fastdraw")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_fastdraw")
}

function onStart_appendage_fastdraw(appendage)
{
	if(!appendage)
	{
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);

}

function onEnd_appendage_fastdraw(appendage)
{
	if(!appendage)
	{
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
}

function onAttackParent_appendage_fastdraw(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if(!appendage || isStuck || !damager || !damager.isObjectType(OBJECTTYPE_ACTIVE)) return;
	local Object = sq_GetCNRDObjectToActiveObject(damager); 
	if(Object.isDead()||Object.getHp()<=0)return; 

	local obj = sq_GetCNRDObjectToSQRCharacter(appendage.getParent()); 
	local state = obj.getState();
	if(realAttacker.isObjectType(OBJECTTYPE_PASSIVE)) 
	{
		local passobj = realAttacker.getCollisionObjectIndex();
		switch(passobj)
		{
			case 22001:
				local Width = sq_GetWidthObject(damager) / 2 / 2; 
				local ZPos = sq_GetCenterZPos(boundingBox); 
				local ani = sq_CreateAnimation("", "character/gunner/effect/animation/fastdraw/hit_light.ani"); 
				local pool = sq_CreatePooledObject(ani, true); 
				sq_SetCurrentDirection(pool, obj.getDirection()); 
				pool.setCurrentPos(sq_GetDistancePos(damager.getXPos(), obj.getDirection(), Width), damager.getYPos()+2, damager.getZPos() + ZPos); 
				pool = sq_SetEnumDrawLayer(pool, ENUM_DRAWLAYER_NORMAL); 
				sq_AddObject(obj, pool, OBJECTTYPE_DRAWONLY, false); 
			break;
		}
	}
}

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_suppressingfire")
}

function onAttackParent_appendage_suppressingfire(appendage, realAttacker, damager, boundingBox, isStuck)
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
				local ani = sq_CreateAnimation("", "character/gunner/effect/animation/hiteffect/updefault.ani");
				ani.setImageRateFromOriginal(-1.0, 1.0);
				ani.addLayerAnimation(1, sq_CreateAnimation("", "character/gunner/effect/animation/atsuppressingfire/suppressingfire_blow001.ani"), true);
				local addZPos = sq_GetCenterZPos(boundingBox);
				local pooledObj = sq_CreatePooledObject(ani, true);
				sq_SetCurrentDirection(pooledObj, obj.getDirection());
				pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + addZPos + sq_getRandom(addZPos / 2 / -1, addZPos / 2));
				pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
				sq_AddObject(obj, pooledObj, OBJECTTYPE_DRAWONLY, false);
			break;
		}
	}
}




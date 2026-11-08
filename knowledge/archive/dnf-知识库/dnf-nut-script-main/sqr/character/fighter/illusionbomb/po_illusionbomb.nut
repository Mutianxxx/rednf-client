function illusionBombAdd(obj)
{
	//69	`Fighter/IllusionBomb.skl`
	obj.setSkillCommandEnable(69,true);
	local b_useskill = obj.sq_IsEnterSkill(69);
	if(b_useskill != -1)
	{
		local objectManager = obj.getObjectManager();
		for(local i=0;i<objectManager.getCollisionObjectNumber();++i)
		{
			local object = objectManager.getCollisionObject(i);
			if(object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE))
			{
				//60040	`Fighter/FighterIllusionBomb.mob`
				local index = object.getCollisionObjectIndex();
				if(index == 60040)
				{
					local attackPower = obj.sq_GetPowerWithPassive(69, 13, 0, -1, 1.0);
					local rate = obj.sq_GetIntData(69, 0);
					sq_BinaryStartWrite();
					sq_BinaryWriteDword(attackPower);
					sq_BinaryWriteDword(rate);
					sq_SendCreatePassiveObjectPacketPos(obj, 24150, 0, object.getXPos(), object.getYPos(),object.getZPos()+ object.getObjectHeight()/2);
					//obj.sq_PlaySound("MSKIN_DISA"); 
					local activeObj = sq_GetCNRDObjectToActiveObject(object);
					activeObj.setValid(false);
					sq_IntVectorClear(sq_GetGlobalIntVector());
					sq_IntVectorPush(sq_GetGlobalIntVector(),0);
					sq_AddSetStatePacketActiveObject(activeObj, STATE_DIE, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
				}
			}
		}
		
	}
}

function setCustomData_po_illusionbomb(obj,receiveData)
{
	local attackPower = receiveData.readDword();
	local atk = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackPower(atk, attackPower);
	local cani = obj.getCurrentAnimation();
	local sizerate = (receiveData.readDword()).tofloat() / 100.0;
	cani.setImageRateFromOriginal(sizerate, sizerate);
	cani.setAutoLayerWorkAnimationAddSizeRate(sizerate);
	sq_SetAttackBoundingBoxSizeRate(cani, sizerate, sizerate, sizerate);
	sq_CreateParticle("passiveobject/common/particle/lightexplosionparticle1.ptl", obj, 0, 0, 0, true, 1, 0, 2);
	sq_CreateParticle("passiveobject/common/particle/lightexplosionparticle2.ptl", obj, 0, 0, 0, true, 1, 0, 2);
	sq_CreateParticle("passiveobject/common/particle/lightexplosionparticle3.ptl", obj, 0, 0, 0, true, 1, 0, 2);
	sq_CreateParticle("passiveobject/common/particle/lightexplosionparticle4.ptl", obj, 0, 0, 0, true, 1, 0, 2);
	obj.sq_PlaySound("FIRE_EXPLOSION_CREATE");
}

function onEndCurrentAni_po_illusionbomb(obj)
{
	if(!obj) return;
		sq_SendDestroyPacketPassiveObject(obj);
}
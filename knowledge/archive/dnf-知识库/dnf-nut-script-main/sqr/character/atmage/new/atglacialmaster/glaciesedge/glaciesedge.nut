function checkExecutableSkill_GlaciesEdge(obj)  
{
	if (!obj) return false;
	
	local isUse = obj.sq_IsUseSkill(SKILL_GLACIESEDGE);

	if (isUse)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_GLACIESEDGE, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_GlaciesEdge(obj)
{
	return true;
}

function onSetState_GlaciesEdge(obj, state, datas, isResetTimer)
{	
	local state = obj.getVar("state").get_vector(0);
	
	obj.sq_StopMove();

	if (state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GLACIESEDGEAURACASTING_BODY);
		
		createGlaciesEdgeAura_F(obj, 0, 0, 0);
		createGlaciesEdgeAura_F_00(obj, 0, 0, 0);
	}
	if (state == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GLACIESEDGESWING_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_GLACIESEDGEATTACK);
	
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_GLACIESEDGE, STATE_GLACIESEDGE, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
	}
}

function onEndCurrentAni_GlaciesEdge(obj)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_GLACIESEDGE, STATE_PRIORITY_USER, false);
	}
	if (state == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_GlaciesEdge(obj, flagIndex)
{
	local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		if (flagIndex == 0)
		{
			obj.sq_PlaySound("GLACIES_CAST_1");
			sq_flashScreen(obj,300,600,150,178, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
		if (flagIndex == 1)
		{
			sq_SetMyShake(obj,4,100);
		}
	}
	if (state == 1)
	{
		if (flagIndex == 0)
		{
			sq_SetMyShake(obj,20,240);
			sq_flashScreen(obj,30,80,80,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			createGlaciesEdgeDust_F_00(obj, 0, 0, 0);
			createGlaciesEdgeFloor_B_01(obj, 0, 0, 0);
			createGlaciesEdgeFloorB_00(obj, 0, 0, 0);
			createGlaciesEdgeSlash_B_07(obj, 0, 0, 0);
			createGlaciesEdgeSlash_F_07(obj, 0, 0, 0);
			createGlaciesEdgeSwing_B_01(obj, 0, 0, 0);
			createGlaciesEdgeSwing_F_01(obj, 0, 0, 0);
			createGlaciesEdgeBG_ShockWave(obj, 0, 0, 0);
			setVliadEffectGlaciesEdgePassiveobject(obj);
		}
	}
	return true;
}

function createGlaciesEdgeAura_F(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeaura_f.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("GlaciesEdge_End").push_obj_vector(pooledObj);
}

function createGlaciesEdgeAura_F_00(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeaura_f_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("GlaciesEdge_End").push_obj_vector(pooledObj);
}

function createGlaciesEdgeDust_F_00(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgedust_f_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeFloor_B_01(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgefloor_b_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeFloorB_00(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgefloorb_00.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeSlash_B_07(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeslash_b_07.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeSlash_F_07(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeslash_f_07.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeSwing_B_01(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeswing_b_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeSwing_F_01(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/glaciesedgeswing_f_01.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function createGlaciesEdgeBG_ShockWave(obj, disX, disY, disZ)
{
	local ani = sq_CreateAnimation("", "character/mage/effect/animation/atglaciesedge/bg_shockwave.ani");
	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);
	pooledObj.setCurrentPos(posX, obj.getYPos() + disY, obj.getZPos() + disZ);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
}

function setVliadEffectGlaciesEdgePassiveobject(obj)
{
	local var = obj.getVar("GlaciesEdge_End");
	
	local objectsSize = var.get_obj_vector_size();

	for(local i=0;i<objectsSize;++i)
	{
		local effectObj = var.get_obj_vector(i);
		
		if (effectObj)
		{
			effectObj.setValid(false);
		}
	}
}
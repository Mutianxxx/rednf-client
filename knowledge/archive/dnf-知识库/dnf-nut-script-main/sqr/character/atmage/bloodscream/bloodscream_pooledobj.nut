


function createBloodStreamStartA_Back_Bodyeffect02(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_starta_back_bodyeff02.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				

	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamStartA_Bodyeffect07(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_starta_bodyeff07.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createBloodStreamStartB_Back_BodyEffect_01(obj)
{


}

function createBloodStreamStartB_BG_Effect01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_bg_eff01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 3,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamStartB_Back_Bodyeffect01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_back_bodyeff_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamStartB_Floor(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_floor.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 3,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamStartB_Bodyeffect02(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_bodyeff_02.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamStartB_FrontBgEffect(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_bodyeff_02.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamLoopA_Back_BodyEffect06(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_back_bodyeff06.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamLoopA_BG(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_bg_tunnela01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 4,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamLoopA_Floor(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_floor.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 3,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamLoopA_FrontBgeffect01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_front_bgeffa_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


//?????????????????????????????????????????????????
function createBloodStreamLoopA_Tornadoa_01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_tornadoa_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamLoopB_Back_Bodyeffect06(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_back_bodyeff06.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamLoopB_BG_Tunnela01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_bg_tunnela01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 4,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createBloodStreamLoopB_Floor(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_floor.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 3,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamLoopB_FrontBgEffectA_01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_front_bgeffa_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamLoopB_Tornadoa_01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_tornadoa_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamEnd_Back_BodyEffect09(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_back_bodyeff09.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamEnd_Bg_Tunnela01(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_bg_tunnela01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 4,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamEnd_Ciecle02(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_ciecle_02.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamEnd_Floor(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_floor.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 3,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createBloodStreamEnd_FrontBg_Effect11(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_front_bgeffg11.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamStartDomeB(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_startb_domea_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamStartDomeB_Back(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_startb_back_domea_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createBloodStreamLoopDomeB(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_loop_domea_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos(),0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("esapistEffectObj_BloodStream").push_obj_vector( pooledObj );
}

function createBloodStreamLoopDomeB_Back(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_loop_back_domea_01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("esapistEffectObj_BloodStream").push_obj_vector( pooledObj );
}



function createBloodStreamHitEffect_HoldEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_eff03.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("esapistEffectObj_BloodStream").push_obj_vector( pooledObj );
}


function createBloodStreamHitEffect_HoldEffect2(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_backeff02.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() - 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createBloodStreamHitEffect_HoldEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_eff03.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createBloodStreamHitEffect_HoldEffect3(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_back01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() - 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("esapistEffectObj_BloodStream").push_obj_vector( pooledObj );
}


function createBloodStreamHitEffect_HoldEffect4(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_front01.ani");
    local speedRate = obj.getVar("speed").get_vector(0).tofloat();
	ani.setSpeedRate(speedRate);				
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("esapistEffectObj_BloodStream").push_obj_vector( pooledObj );
}


//obj.getVar("esapistEffectObj_BloodStream").


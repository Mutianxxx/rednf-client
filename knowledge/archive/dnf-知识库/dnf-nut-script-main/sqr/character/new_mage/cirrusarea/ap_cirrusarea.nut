
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_CIRRUSAREA")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_CIRRUSAREA")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_CIRRUSAREA")
	appendage.sq_AddFunctionName("onVaildTimeEnd", "onVaildTimeEnd_appendage_CIRRUSAREA")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_CIRRUSAREA")
}

function sq_AddEffect(appendage)
{

}

function drawAppend_appendage_CIRRUSAREA(appendage, isOver, x, y, isFlip)
{
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	
	local sizeRate = parentObj.getObjectHeight();
	sizeRate = sizeRate.tofloat()/100.0;
	
	local anifa = appendage.getVar().GetAnimationMap("cirrusareafa", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose3/vinerosestart03_00.ani");
	local anifb = appendage.getVar().GetAnimationMap("cirrusareafb", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose3/vineroseloop03_00.ani");

	if ( appendage.getVar("flag").get_vector(0) == 1 )
	{
		anifa = appendage.getVar().GetAnimationMap("cirrusareafa", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose2/vinerosestart02_00.ani");
		anifb = appendage.getVar().GetAnimationMap("cirrusareafb", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose2/vineroseloop02_00.ani");
	}
	else if( appendage.getVar("flag").get_vector(0) == 0 )
	{
		anifa = appendage.getVar().GetAnimationMap("cirrusareafa", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose1/vinerosestart01_00.ani");
		anifb = appendage.getVar().GetAnimationMap("cirrusareafb", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose1/vineroseloop01_00.ani");
	}

	if (anifa && isOver) {
		anifa.resize(sizeRate);
		sq_AnimationProc(anifa);
		sq_drawCurrentFrame(anifa, x, y, isFlip);
	}
	
	if (anifb && isOver) {
		anifb.resize(sizeRate);
		sq_AnimationProc(anifb);
		sq_drawCurrentFrame(anifb, x, y, isFlip);
	}
	
}

function onEnd_appendage_CIRRUSAREA(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	
	
	if(!parentObj){
		appendage.setValid(false);
		return;
	}
	local sizeRate = parentObj.getObjectHeight();
	sizeRate = sizeRate.tofloat()/100.0;
	local objx = parentObj.getXPos();
	local objy = parentObj.getYPos() + 2;
	local objz = parentObj.getZPos();
	
	local ani = sq_CreateAnimation("", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose3/vineroseend03_04.ani");

	local elect = null;
	if ( appendage.getVar("flag").get_vector(0) == 0 )
	{
		ani = sq_CreateAnimation("", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose1/vineroseend01_04.ani");
	}
	else if ( appendage.getVar("flag").get_vector(0) == 1 )
	{
		ani = sq_CreateAnimation("", "passiveobject/zrr_skill/newmage/animation/thornvinehold/vine/vinerose2/vineroseend02_04.ani");
	}

	if(!ani)
		return;
	ani.resize(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj.setCurrentPos(objx, objy, objz);
	pooledObj.setCurrentDirection(parentObj.getDirection());
	sq_AddObject(parentObj, pooledObj, 2, false);

}

function onVaildTimeEnd_appendage_CIRRUSAREA(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj)
	{
		appendage.setValid(false);
		return;
	}
}

function proc_appendage_CIRRUSAREA(appendage)
{
	if(!appendage) {
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



function onStart_appendage_CIRRUSAREA(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	
	appendage.getVar("flag").clear_vector();
	appendage.getVar("flag").push_vector( sq_getRandom(0,3).tointeger() );
	
}


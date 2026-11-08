
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SorceressBuff")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SorceressBuff")
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_SorceressBuff")	
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_SorceressBuff")
}

function onDamageParent_appendage_SorceressBuff(appendage ,attacker, boundingBox, isStuck) 
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	if (!parentObj) {
		return;
	}
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	createSorceressBuffDamageEffect(parentObj);
}

function createSorceressBuffDamageEffect(obj)
{
	if(!obj) {
		return;
	}
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/forbiddencurse/aura_damage_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);
}


function drawAppend_appendage_SorceressBuff(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	if (!parentObj) {
		//appendage.setValid(false);
		return;
	}
	local anif = appendage.getVar().GetAnimationMap("sorceressf", "character/mage/animation/ani_als/forbiddencurse/aura_buff_loop_00.ani");
	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
}

function proc_appendage_SorceressBuff(appendage)
{
	if(!appendage) {
		return;		
	}

	local obj = appendage.getParent();

	local isSub = appendage.getVar("isSub").get_vector(0);
	local subTime = appendage.getVar("isSub").get_vector(2) - appendage.getVar("isSub").get_vector(1);
	if (isSub == 0)
	{
		local currentT = appendage.getTimer().Get();
		if (currentT > subTime)
		{
			//obj.setHp( obj.getHp() - obj.getHpMax() * subHp / 100 , null, true);
			//obj.setHp( 1 , null, true);
			appendage.getVar("isSub").clear_vector();
			appendage.getVar("isSub").push_vector(1);
			local startT = appendage.getTimer().Get();

			appendage.getVar("t").clear_vector();
			appendage.getVar("t").push_vector(startT);
        	}
	}
	else if (isSub == 1)
	{
		local currentT = appendage.getTimer().Get();
		local startT = appendage.getVar("t").get_vector(0);
		if (currentT - startT > 1000)
		{
			if ( obj.getHp() - obj.getHpMax() / 100 > 0)
			{
				createSorceressBuffDamageEffect(obj);
				obj.setHp( obj.getHp() - obj.getHpMax() / 100 , null, true);
				appendage.getVar("t").clear_vector();
				appendage.getVar("t").push_vector(currentT);
			}
            		else
            		{
				appendage.setValid(false);
			}
    
		}
	}

}


function onStart_appendage_SorceressBuff(appendage)
{
	if(!appendage) {
		return;
	}
	appendage.getVar("isSub").clear_vector();
	appendage.getVar("isSub").push_vector(0);
	appendage.getVar("isSub").push_vector(appendage.getVar("time").get_vector(0));
	appendage.getVar("isSub").push_vector(appendage.getVar("time").get_vector(1));
}


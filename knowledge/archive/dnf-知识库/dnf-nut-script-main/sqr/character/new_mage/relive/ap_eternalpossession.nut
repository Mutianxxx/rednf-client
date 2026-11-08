
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_eternalpossession")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_eternalpossession")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_eternalpossession")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_eternalpossession")
}

function sq_AddEffect(appendage)
{

}

function drawAppend_appendage_eternalpossession(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		//appendage.setValid(false);
		return;
	}
	local defValue = appendage.getVar("flag").get_vector(2);
	if (appendage.getVar("flag").get_vector(0) == 0){
		local anib = appendage.getVar().GetAnimationMap("relivewirea", "passiveobject/zrr_skill/newmage/animation/marionette/connectwirea_00.ani");
	
		if (anib && !isOver) {
			sq_AnimationProc(anib);
			sq_drawCurrentFrame(anib, x, y, isFlip);
		}
	}
	else if(appendage.getVar("flag").get_vector(0) == 1 && defValue > 0)
	{
		local anif = appendage.getVar().GetAnimationMap("spotlightf", "passiveobject/zrr_skill/newmage/animation/marionette/spotlight_00.ani");
		local anib = appendage.getVar().GetAnimationMap("spotlightg", "passiveobject/zrr_skill/newmage/animation/marionette/spotlightground_00.ani");
	
		if (anif && isOver) {
			sq_AnimationProc(anif);
			sq_drawCurrentFrame(anif, x, y, isFlip);
		}
		else if (anib && !isOver) {
			sq_AnimationProc(anib);
			sq_drawCurrentFrame(anib, x, y, isFlip);
		}
	}
}

function onSetHp_appendage_eternalpossession(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
		
	local obj = appendage.getParent();

	if(!obj)
		return hp;
	
	local sqrChr = sq_GetCNRDObjectToActiveObject(obj);
	if (appendage.getVar("flag").get_vector(0) == 0)
	{
		if (hp <= 0)
		{
			local recRate = appendage.getVar("flag").get_vector(1);
			local defValue = appendage.getVar("flag").get_vector(2);
			appendage.getVar("flag").clear_vector();
			appendage.getVar("flag").push_vector(1);
			appendage.getVar("flag").push_vector(200);
			appendage.getVar("flag").push_vector(defValue);
			//sqrChr.sq_AddSetStatePacket(STATE_DOWN, STATE_PRIORITY_IGNORE_FORCE, true);
			local maxHp = sqrChr.getHpMax() * recRate/1000;
			hp = maxHp.tointeger();
			//parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
			//local appendage = CNSquirrelAppendage.sq_AppendAppendage(parentObj, parentObj, SKILL_RELIVE, false,"character/new_mage/relive/ap_relive_alter.nut", true);
		}
	}
	else{
		local defValue = appendage.getVar("flag").get_vector(2);
		if (defValue > 0){
			local ohp = sqrChr.getHp();
			local chp = ohp - hp;
			if(chp > 0){
				appendage.getVar("flag").clear_vector();
				appendage.getVar("flag").push_vector(1);
				appendage.getVar("flag").push_vector(200);
				appendage.getVar("flag").push_vector(defValue - chp);
			}
			else{
				return hp;
			}
			return ohp;
		}else{
			appendage.setValid(false);
		}
		
	}
	
	return hp;
}

function proc_appendage_eternalpossession(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!parentObj) 
	{
		//appendage.setValid(false);
		return;
	}

	//if (appendage.getVar("flag").get_vector(0) == 1)
	//{

	//}
	//parentObj.setCurrentPos(0,0,0);
}



function onStart_appendage_eternalpossession(appendage)
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
	appendage.getVar("flag").push_vector(0);
	appendage.getVar("flag").push_vector(appendage.getVar("relivedata").get_vector(0));
	appendage.getVar("flag").push_vector(appendage.getVar("relivedata").get_vector(1));

}


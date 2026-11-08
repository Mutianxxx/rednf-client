
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_HitEffect")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_HitEffect")
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_HitEffect")	
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_HitEffect")
}

function sq_AddEffect(appendage)
{
}

function getImmuneTypeDamageRate_appendage_HitEffect(appendage, damageRate, attacker)
{

	local sourceObj = appendage.getSource();
	local parentObj = appendage.getParent();

	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);

    if (parentObj.getHp() == 0 )
        damageRate = 0;

    return damageRate;
}


function onDamageParent_appendage_HitEffect(appendage ,attacker, boundingBox, isStuck) 
{
	local parentObj = appendage.getParent();	
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}

}

function proc_appendage_HitEffect(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();


	if(!sourceObj || !parentObj ) 
    {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_HitEffect(appendage)
{
	if(!appendage) {
		return;
	}
	
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
    
//    appendage.getVar("hpMax").push_vector(10000);
}


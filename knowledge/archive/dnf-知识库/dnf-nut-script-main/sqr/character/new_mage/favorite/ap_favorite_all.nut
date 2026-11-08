
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_FavoriteAll")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_FavoriteAll")
	appendage.sq_AddFunctionName("onApplyHpDamage", "onApplyHpDamage_appendage_FavoriteAll")
}



function sq_AddEffect(appendage)
{
}

function proc_appendage_FavoriteAll(appendage)
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
	local obj = appendage.getParent();
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(obj);
//    sqrObj.setCurrentPos(0,0,0);
}

function onApplyHpDamage_appendage_FavoriteAll(appendage, newHpDamage, attacker)
{
	local obj = appendage.getParent();
	
	if(!obj)
		return newHpDamage;
	
	local damage = newHpDamage;
	
		local frozenAddDamageRate = -appendage.getVar("define").get_vector(0);
		
		local addDamage = newHpDamage.tofloat() * frozenAddDamageRate.tofloat() / 100.0;
		
		//print(" addDamage:" + addDamage);
		
		damage = damage + addDamage.tointeger();

	return damage;
}


function onStart_appendage_FavoriteAll(appendage)
{

}


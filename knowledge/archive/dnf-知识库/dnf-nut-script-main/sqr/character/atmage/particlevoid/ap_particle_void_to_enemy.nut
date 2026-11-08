
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ParticleVoid_Enemy")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ParticleVoid_Enemy")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ParticleVoid_Enemy")
	appendage.sq_AddFunctionName("onApplyHpDamage", "onApplyHpDamage_appendage_ParticleVoid_Enemy")
}

function onStart_appendage_ParticleVoid_Enemy(appendage)
{
	if(!appendage) {
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj ) {
		appendage.setValid(false);
		return;
	}
    
}

function onApplyHpDamage_appendage_ParticleVoid_Enemy(appendage, newHpDamage, attacker)
{
	if(!appendage) {
		return newHpDamage;
	}
	local obj = appendage.getParent();
	
	if(!obj)
		return newHpDamage;

	local damage = newHpDamage;

	local frozenAddDamageRate = appendage.getVar("atkRate").get_vector(0);
	local addDamage = newHpDamage.tofloat() * frozenAddDamageRate.tofloat() / 100.0;
	damage = damage + addDamage.tointeger();
	return damage;
}

function proc_appendage_ParticleVoid_Enemy(appendage)
{
	if(!appendage || !appendage.isValid()) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();//voidObj
				
	if(!sourceObj || !parentObj || sourceObj.getVar("state").get_vector(0) != PARTICLE_VOLD_STATE_TO_ENEMY) {
		appendage.setValid(false);
		return;
	}
}

function onEnd_appendage_ParticleVoid_Enemy(appendage)
{
	if(!appendage) {
		return;
	}
		
	local parentObj = appendage.getParent();
				
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}
	
}


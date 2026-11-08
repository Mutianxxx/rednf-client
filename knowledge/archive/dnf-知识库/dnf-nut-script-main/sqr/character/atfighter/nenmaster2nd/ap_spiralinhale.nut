

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_SpiralInhale")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_SpiralInhale")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_SpiralInhale")
}

function onStart_appendage_SpiralInhale(appendage)
{
	if(!appendage) {
		return;
	}
	local obj = appendage.getParent();
	local obj = sq_GetCNRDObjectToCharacter(obj);
	obj.getVar("SpiralInhaleEnergy").clear_vector();
	obj.getVar("SpiralInhaleEnergy").push_vector(0);
}

function proc_appendage_SpiralInhale(appendage)
{
	if(!appendage) return;
	local parobj = appendage.getParent();
	if(!parobj) 
	{
		appendage.setValid(false);
		return;
	}
	
}

function onAttackParent_appendage_SpiralInhale(obj, realAttacker, damager, boundingBox, isStuck) {
	if (!obj || !obj.isValid()) return;
	if (isStuck) return;
	local parentObj = obj.getParent();
	local chr = sq_GetCNRDObjectToCharacter(parentObj);

	if (realAttacker.isObjectType(OBJECTTYPE_PASSIVE)) {
		realAttacker = sq_GetCNRDObjectToCollisionObject(realAttacker);
		local passiveIndex = realAttacker.getCollisionObjectIndex();

		local energy = chr.getVar("SpiralInhaleEnergy").get_vector(0);
		local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
		local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(chr, append);
		if (passiveIndex == 46004 || passiveIndex == 21054 || passiveIndex == 21055 || passiveIndex == 21056 || passiveIndex == 21079 || passiveIndex == 21067 || passiveIndex == 21062) {
			if (!realAttacker.getVar("SpiralInhaleIs").getBool(0) && !appendage) {
				chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
				realAttacker.getVar("SpiralInhaleIs").setBool(0, true);
			}
		} else if (passiveIndex == 21085 && !appendage) {
			if (!chr.getVar("SpiralInhaleIs").getBool(0)) {
				chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
				chr.getVar("SpiralInhaleIs").setBool(0, true);
			}
		} else if (passiveIndex == 24375) {
			local id = realAttacker.getVar("skill").get_vector(0);
			if (id == 220 || id == 20 || id == 21)
			{
				if (!chr.getVar("SpiralInhaleIs").getBool(0)) {
					chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
					chr.getVar("SpiralInhaleIs").setBool(0, true);
				}
			}
			if(!appendage)
			{
				if (id == 23){
					if (!chr.getVar("SpiralInhaleIs").getBool(0)) {
						chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
						chr.getVar("SpiralInhaleIs").setBool(0, true);
					}
				}
			}
		} else if (passiveIndex == 21053) {
			if (!realAttacker.getVar("SpiralInhaleIs").getBool(0)) {
				chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
				realAttacker.getVar("SpiralInhaleIs").setBool(0, true);
			}
		}
	} else if (realAttacker.isObjectType(OBJECTTYPE_CHARACTER)) {
		local energy = chr.getVar("SpiralInhaleEnergy").get_vector(0);
		local skillIndex = chr.getCurrentSkillIndex();
		if (chr.isCurrentCutomAniIndex(52))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		else if (chr.isCurrentCutomAniIndex(53))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		else if (chr.isCurrentCutomAniIndex(54))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		else if (chr.isCurrentCutomAniIndex(55))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		else if (chr.isCurrentCutomAniIndex(57))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		else if (chr.isCurrentCutomAniIndex(58))
			chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 50);
		if(skillIndex == 222)
		{
			if (!chr.getVar("SpiralInhaleIs").getBool(0)) {
				chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 500);
				chr.getVar("SpiralInhaleIs").setBool(0, true);
			}
		}
		else if(skillIndex == 221)
		{
			if (!chr.getVar("SpiralInhaleIs").getBool(0)) {
				chr.getVar("SpiralInhaleEnergy").set_vector(0, energy + 100);
				chr.getVar("SpiralInhaleIs").setBool(0, true);
			}
		}
	}

	if (chr.getVar("SpiralInhaleEnergy").get_vector(0) > 1000)
		chr.getVar("SpiralInhaleEnergy").set_vector(0, 1000);
}

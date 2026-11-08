
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart" ,  "onStart_appendage_cintamani")
	appendage.sq_AddFunctionName("proc" ,  "proc_appendage_cintamani")
	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_cintamani")
	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_cintamani")
	appendage.sq_AddFunctionName("onAttackParent" ,  "onAttackParent_appendage_cintamani")
}

function onAttackParent_appendage_cintamani(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if(!appendage) return;
	
	local obj = appendage.getParent();
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(!damager.isObjectType(OBJECTTYPE_ACTIVE)) 
		return 0;
	local active_damager = sq_GetCNRDObjectToActiveObject(damager);
	if(isStuck){
		return 0;
	}
	if(!pChr) {
		appendage.setValid(false);
		return;
	}
	if(!active_damager){
		return 0;
	}
	if(!pChr.isEnemy(active_damager))
	{
		return 0;
	}
	if(isSameObject(pChr,active_damager))
	{
		return 0;
	}
	if(!isSameObject(pChr,realAttacker))
	{
		if(realAttacker.isObjectType(OBJECTTYPE_PASSIVE))
		{
			local id = realAttacker.getVar("id").get_vector(0);
			if(id < 1)
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	local attackBonusRate =  pChr.sq_GetBonusRateWithPassive(SKILL_CINTAMANI, -1, 3, 1.0);
	local attackInfo = sq_getNewAttackInfoPacket();
	attackInfo.useWeapon = true;
	attackInfo.powerRate = attackBonusRate;
	attackInfo.element = ENUM_ELEMENT_NONE;
	attackInfo.eType = ATTACKTYPE_MAGICAL;
	attackInfo.stuckRate = -1000.0;
	
	sq_SendHitObjectPacketByAttackInfo(pChr, active_damager, attackInfo);
	
}

function onStart_appendage_cintamani(appendage)
{
	if(!appendage) return;
	local UncleBangValue1 =  appendage.getParent();
	local UncleBangValue2 =  appendage.getSource();
	local UncleBangValue1 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue1);
	if(!UncleBangValue2 || !UncleBangValue1){
		appendage.setValid(false);
		return;
	}
	appendage.getVar("cintamanihit").setBool(0,true);
}

function proc_appendage_cintamani(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue1 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue1);

	if(!UncleBangValue2 || !UncleBangValue1 || UncleBangValue1.isDead())

	

{

appendage.setValid(false);

return;

	

}

}

function onEnd_appendage_cintamani(appendage)

{

	if(!appendage) return;

	appendage.sq_DeleteAppendages();

}


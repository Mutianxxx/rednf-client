
function onStartDungeon_AllGrowJob(obj)
{
	if(!obj) return;
	
	if(sq_isPVPMode()) return;
	
	if(sq_IsMyCharacter(obj))
	{
		setCharacterAppendage(obj);
		preloadSkill_AllGrowJob(obj);
		preloadCommon_AllGrowJob(obj);
		preloadAwakeCutin_AllGrowJob(obj);
	}
}


function onStartDungeon_ATSwordman(obj )
{
	if(!obj) return;

	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	DungeonStart_ATSwordman_Drawsword(obj)
	DungeonStart_ATSwordman_Magicswordshoot(obj)
	StartDungeon_AtSwordmanAddEvolve(obj)
	StartDungeon_AtSwordmanDualweapon(obj)
	DungeonStart_ATSwordman_Ecstasy(obj)
	return;
	
}

function onStartDungeon_Swordman(obj)
{
	if (!obj)
		return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	local weaponSubType = obj.getWeaponSubType(); //ï¿½ï¿½ï¿?
	obj.getVar("weaponSubType").clear_vector();
	obj.getVar("weaponSubType").push_vector(weaponSubType);
	if (!sq_IsMyCharacter(obj))
		return;
	if(sq_isPVPMode())
		return;
	if (sq_getGrowType(obj) == 3 )
	{
		if(sq_GetSkillLevel(obj,76)>0)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(76);
			obj.sq_IntVectPush(90);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(4);
			obj.sq_IntVectPush(4);
			obj.sq_AddSetStatePacket(13, STATE_PRIORITY_USER, true);
			return;
		}
	}
}


function onStartDungeon_Fighter(obj )
{
	if (!obj)
		return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	local weaponSubType = obj.getWeaponSubType(); //ï¿½ï¿½ï¿½ï¿½
	obj.getVar("weaponSubType").clear_vector();
	obj.getVar("weaponSubType").push_vector(weaponSubType);
	
	if (sq_IsMyCharacter(obj))
	{
		if (sq_getGrowType(obj) == 2 )
		{
			if(!sq_isPVPMode())
			{
				if(sq_GetSkillLevel(obj,91)>0)
				{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(91);
					obj.sq_AddSetStatePacket(17, STATE_PRIORITY_USER, true);
					return;
				}
			}
		}
	}
}

function onStartDungeon_ATFighter(obj )
{
	if (!obj)
		return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	local weaponSubType = obj.getWeaponSubType(); //ï¿½ï¿½ï¿½ï¿½
	obj.getVar("weaponSubType").clear_vector();
	obj.getVar("weaponSubType").push_vector(weaponSubType);
	
	if (sq_IsMyCharacter(obj))
	{
		if (sq_getGrowType(obj) == 2 )
		{
			if(!sq_isPVPMode())
			{
				if(sq_GetSkillLevel(obj,91)>0)
				{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(91);
					obj.sq_AddSetStatePacket(17, STATE_PRIORITY_USER, true);
					return;
				}
			}
		}
	}
}

function onStartDungeon_ATGunner(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	return;
	
}

function onStartDungeon_Gunner(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	return;
	
}

function onStartDungeon_Mage(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut")){
		print("remove ap_avatar");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/mage/avatar/ap_avatar.nut");
	}
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/doll/ap_doll.nut")){
		print("remove ap_doll");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_mage/doll/ap_doll.nut");
	}
	return;
}

function onStartDungeon_ATMage(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	return;
	
}

function onStartDungeon_Thief(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	return;
	
}

function onStartDungeon_Priest(obj )
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Appendage/Character/ap_avenger_awakening.nut")){
		print("remove ap_avenger_awakening");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "Appendage/Character/ap_avenger_awakening.nut");
	}
	//InitializeMyCharacter(obj);
	
/*	if (!sq_IsMyCharacter(obj))
		return;
	if(sq_isPVPMode())
		return;*/
	
/*	if(sq_getGrowType(obj) == 2 && sq_GetSkillLevel(obj,13) > 0)
	{
        	obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(27, STATE_PRIORITY_USER, true);
		return;
	}*/

}

function onStartDungeon_ATPriest(obj)
{
	if(!obj) return;
	onStartDungeon_AllGrowJob(obj);
	//InitializeMyCharacter(obj);
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atpriest/seducer/depravitysevensins/ap_depravitysevensins.nut")){
		print("remove ap_depravitysevensins");
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atpriest/seducer/depravitysevensins/ap_depravitysevensins.nut");
	}
	removeHolyFlame(obj);
	StartDungeon_thesevendeadlysins(obj);
	return;
	
}

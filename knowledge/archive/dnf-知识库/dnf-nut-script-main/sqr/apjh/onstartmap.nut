function onStartMap_AllGrowJob(obj)
{
	if(!obj) return;
	if(sq_IsMyCharacter(obj))
	{	
		if(!sq_isPVPMode())
		{
			setCharacterAppendage(obj);
			initDamageFontCache();
			setAllMonsterPreLoadAndAppend(obj);
		}
		removeEdification(obj);
		removeZealOfFaith(obj);
		CreateBloodyFruitDuegonDarkEffect(obj);
		InitializeTrainRoomCharacter(obj);
	}
}


function onStartMap_Swordman(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}

function onStartMap_ATSwordman(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
	SetATSwordmanStatePlaySound(obj);
}

function onStartMap_Fighter(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_ATFighter(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_Gunner(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_ATGunner(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_Mage(obj)
{
	if (!obj) return;
	onStartMap_AllGrowJob(obj);
	SetMageStatePlaySound(obj);
	sendOneSmallEvilAppendAdd(obj);
}


function onStartMap_ATMage(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_Priest(obj)
{
	if(!obj) 
		return;
	onStartMap_AllGrowJob(obj);
	
	if (!sq_IsMyCharacter(obj))
		return;
	if(sq_isPVPMode())
		return;
	local stage = sq_GetGlobaludpModuleStage();
	if (!stage) return false;
	
	local dungeon = sq_GetDungeonByStage(stage);
	if (!dungeon) return false;
	
	local dungeonIndex = sq_GetDuegonIndex(dungeon);
	if(sq_IsTowerDungeon() || dungeonIndex == 3505)
	{
		if(sq_getGrowType(obj) == 2 && sq_GetSkillLevel(obj,13) > 0)
		{
        		obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(27, STATE_PRIORITY_USER, true);
			return;
		}
	}
}


function onStartMap_Thief(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
}


function onStartMap_ATPriest(obj)
{
	if(!obj) return;
	onStartMap_AllGrowJob(obj);
	SetATPriestStatePlaySound(obj);
	setRevive(obj);
}

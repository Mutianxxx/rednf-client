/*function checkExecutableSkill_favorite(obj)  
{
	if (!obj) return false;
        local isUseSkill = obj.sq_IsUseSkill(SKILL_FAVORITE);
        if (isUseSkill) 
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);

            obj.sq_AddSetStatePacket(STATE_FAVORITE, STATE_PRIORITY_USER, true);
            return true;
        }
        return false;
}*/

function checkExecutableSkill_favorite(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_FAVORITE);

	if(isUse)
	{
		local skillLevel = sq_GetSkillLevel(obj, 94);
		local castTime = sq_GetCastTime(obj, 94, skillLevel);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(SKILL_FAVORITE);
		obj.sq_IntVectPush(castTime);
		obj.sq_IntVectPush(castTime);
		obj.sq_IntVectPush(2);
		obj.sq_IntVectPush(4);
		obj.sq_IntVectPush(4);
		obj.sq_IntVectPush(1000);
		obj.sq_IntVectPush(1000);
		obj.sq_IntVectPush(2000);
		obj.sq_AddSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function createFavoriteBuffEffect(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	
	local object = null;
	local ThrowIndex = obj.getThrowIndex();
	
	local dsgudsaduhuasoi = obj.sq_GetVectorData(datas, 1);
	object = sq_GetObjectByObjectId(obj, dsgudsaduhuasoi);
	local skillLevel = obj.sq_GetSkillLevel(SKILL_FAVORITE);
	
	if(!object)
	{
		object = obj;
	}
	local SQRch = sq_GetCNRDObjectToSQRCharacter(object);
	if(SQRch)
	{
		//drawFavoriteSelectCharacterEffect(obj);
		createFavoriteCasting_1_Shiled(SQRch);
		local Path = "character/new_mage/favorite/ap_favorite.nut";
		
		local validTime = sq_GetLevelData(obj, SKILL_FAVORITE, 0, skillLevel);
		
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(SQRch, obj, SKILL_FAVORITE,false, Path, false);
		//appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, 3, SKILL_FAVORITE, skillLevel);
		appendage.sq_SetValidTime(validTime);
		appendage.setEnableIsBuff(true);
		CNSquirrelAppendage.sq_Append(appendage, SQRch, obj, true);
		appendage.setBuffIconImage(147);
	}
	setFriendAllFavoriteBuff(obj);
	createFavoriteCasting_1_Effect(obj);
}


function setCharacterFristAnimation_Favorite(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_FAVORITE );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj, "character/mage/animation/ani_als/favoritism/favoritismshield_00.ani");
        createFristAnimationPooledObject(obj, "character/mage/animation/ani_als/favoritism/favoritismcasting_00.ani");
        createFristAnimationPooledObject(obj, "character/mage/animation/ani_als/favoritism/favoritismcasting_01.ani");
        createFristAnimationPooledObject(obj, "character/mage/animation/ani_als/favoritism/favoritism_l_heart.ani");
    }
}




function checkCommandEnable_favorite(obj)
{
	if (!obj) return false;
	return true;
}


function createFavoriteCasting_1_Shiled(obj)
{

	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/favoritism/favoritismshield_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() + 150);
	pooledObj.setCurrentDirection(obj.getDirection());
    sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	
}


function createFavoriteCasting_0_Effect(obj)
{

	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/favoritism/favoritismcasting_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createFavoriteCasting_1_Effect(obj)
{

	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/favoritism/favoritismcasting_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createFavoriteAllFriendBuffEffect(obj)
{

	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/favoritism/favoritism_l_heart.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() + obj.getObjectHeight()/2);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	
}

function setFriendAllFavoriteBuff(obj)
{
	local skill_level = sq_GetSkillLevel(obj, SKILL_FAVORITE);
	local objectManager = obj.getObjectManager();
	obj.sq_PlaySound("R_WZ_FAVORITISM"); 
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i++)
	{
		local tar = objectManager.getCollisionObject(i);
		// && !isSameObject(obj, tar) 
		if (tar && tar.isObjectType(OBJECTTYPE_CHARACTER) && !obj.isEnemy(tar))
		{
			local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(tar, "character/new_mage/favorite/ap_favorite_all.nut");
			if(!isAppend){
				local appendage_f = CNSquirrelAppendage.sq_AppendAppendage(tar, obj, SKILL_FAVORITE, false,"character/new_mage/favorite/ap_favorite_all.nut", false);
				local defRate = obj.sq_GetIntData(SKILL_FAVORITE, 0);
				local time = sq_GetLevelData(obj, SKILL_FAVORITE, 0, skill_level);
				local hpMax = sq_GetLevelData(obj, SKILL_FAVORITE, 5, skill_level);
				local mpMax = sq_GetLevelData(obj, SKILL_FAVORITE, 6, skill_level);
				local phyDef = sq_GetLevelData(obj, SKILL_FAVORITE, 1, skill_level);
				local magDef = sq_GetLevelData(obj, SKILL_FAVORITE, 2, skill_level);
				local phy = sq_GetLevelData(obj, SKILL_FAVORITE, 3, skill_level);
				local mag = sq_GetLevelData(obj, SKILL_FAVORITE, 4, skill_level);
				local atkRate = sq_GetLevelData(obj, SKILL_FAVORITE, 7, skill_level);
				local powerRate = obj.sq_GetPowerWithPassive(209, -1, 2, -1, 1.0);
				
				if (isFavoriteing(tar) )
				{
					phyDef = phyDef * 1.2;
					magDef = magDef * 1.2;
					defRate = defRate + 5;

				}
				appendage_f.sq_SetValidTime(time );
				appendage_f.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_FAVORITE, skill_level);
				appendage_f.getVar("define").clear_vector();
				appendage_f.getVar("define").push_vector( defRate );
				CNSquirrelAppendage.sq_AppendAppendageID(appendage_f, tar, tar, APID_COMMON, false);
				local change_appendage = appendage_f.sq_getChangeStatus("favoriteall");
				if(!change_appendage)
				{
					change_appendage = appendage_f.sq_AddChangeStatus("favoriteall",tar, tar, 0, 0, true, 0);
				}
				if (change_appendage)
				{
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, magDef.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, phyDef.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, mag.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, false, phy.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_HP_MAX, false, hpMax.tofloat() );
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_MAX, false, mpMax.tofloat() );
				}
				createFavoriteAllFriendBuffEffect(tar);
			}
		}
	}
}


function drawFavoriteCharacterIcon(obj)
{
    local state = obj.sq_GetState();
    if (state == STATE_FAVORITE && obj.getVar("state").get_vector(0) == 0 && obj.getVar().get_vector(0) == 1 )
    {
        local objectManager = obj.getObjectManager();
        local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL); //  mapX Pos
        local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);//mapY Pos

        local lenX = obj.getXPos() - xPos;
        local lenY = obj.getYPos() - yPos;
        local size = obj.getVar("friendCharacter").get_obj_vector_size();



        if (size >= 1)
        {
            local obj1 = obj.getVar("friendCharacter").get_obj_vector(0);
            drawFavoriteCharacterIconById(obj,getSelectTargetID(obj,obj1) ,400 + lenX -30,300 + lenY - 120);
        }
        if (size >= 2)
        {
            local obj2 = obj.getVar("friendCharacter").get_obj_vector(1);
            drawFavoriteCharacterIconById(obj,getSelectTargetID(obj,obj2) ,400 + lenX -30,300 + lenY  - 20);
        }
        if (size >= 3)
        {
            local obj3 = obj.getVar("friendCharacter").get_obj_vector(2);
            drawFavoriteCharacterIconById(obj,getSelectTargetID(obj,obj3) ,400 + lenX -60,300 + lenY - 70);
        }
        if (size >= 4)
        {
            local obj4 = obj.getVar("friendCharacter").get_obj_vector(3);
            drawFavoriteCharacterIconById(obj,getSelectTargetID(obj,obj4) ,400 + lenX +10,300 + lenY - 70);
        }
    }
}


function getSelectTargetID(obj,tar)
{
    if (tar)
    {
        tar = sq_ObjectToSQRCharacter(tar);	
        if (tar.isObjectType(OBJECTTYPE_CHARACTER) )
            return sq_getJob(tar);

    }else{
        return -1;
    }
}


function drawFavoriteCharacterIconById(obj,id,x,y)
{
    local ani = null;
    local sq_var = obj.getVar();
    if (id == 100)
        ani = sq_var.GetAnimationMap("face_mad", "character/mage/animation/ani_als/favoritism/face_mad.ani");
    else if (id == 0)
        ani = sq_var.GetAnimationMap("face_swordman", "character/mage/animation/ani_als/favoritism/face_swordman.ani");
    else if (id == 1)
        ani = sq_var.GetAnimationMap("face_fighter", "character/mage/animation/ani_als/favoritism/face_fighter.ani");
    else if (id == 2)
        ani = sq_var.GetAnimationMap("face_gunner", "character/mage/animation/ani_als/favoritism/face_gunner.ani");
    else if (id == 3)
        ani = sq_var.GetAnimationMap("face_mage", "character/mage/animation/ani_als/favoritism/face_mage.ani");
    else if (id == 4)
        ani = sq_var.GetAnimationMap("face_priest", "character/mage/animation/ani_als/favoritism/face_priest.ani");
    else if (id == 5)
        ani = sq_var.GetAnimationMap("face_atgunner", "character/mage/animation/ani_als/favoritism/face_atgunner.ani");
    else if (id == 6)
        ani = sq_var.GetAnimationMap("face_thief", "character/mage/animation/ani_als/favoritism/face_thief.ani");
    else if (id == 7)
        ani = sq_var.GetAnimationMap("face_atfighter", "character/mage/animation/ani_als/favoritism/face_atfighter.ani");
    else if (id == 8)
        ani = sq_var.GetAnimationMap("face_atmage", "character/mage/animation/ani_als/favoritism/face_atmage.ani");
    else if (id == 9)
        ani = sq_var.GetAnimationMap("face_dsw", "character/mage/animation/ani_als/favoritism/face_demosionswordman.ani");
    else if (id == 10)
        ani = sq_var.GetAnimationMap("face_creator", "character/mage/animation/ani_als/favoritism/face_creator.ani");
    else if (id == -1)
        return ;

    if (ani)
    {
        sq_AnimationProc(ani);
        sq_drawCurrentFrame(ani, x + 12, y + 12, false);
    }

}

function onEndCurrentAni_FAVORITE(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar().clear_vector();
        obj.getVar().push_vector(1);
//            obj.getVar("state").clear_vector();
//            obj.getVar("state").push_vector(1);
//            obj.sq_AddSetStatePacket(STATE_FAVORITE, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}
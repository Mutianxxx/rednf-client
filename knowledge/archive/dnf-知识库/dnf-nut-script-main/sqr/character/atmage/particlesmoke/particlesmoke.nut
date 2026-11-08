//SKILL_PARTICLE_SMOKE <- 159
//?o????S??A?O?S????@??

//hold success shake 1 100
function checkExecutableSkill_particlesomke(obj)  
{//?o????O?A???????Z?????
	if (!obj) return false;

    local voidObj = getParticleVoid(obj);
    //?p?G?o???H ???s?b ??? ?L?S???????b????W?A?N???
    if (!voidObj )
        return false;

    if (voidObj.getVar("state").get_vector(0) == PARTICLE_VOLD_STATE_MYSELF)
    {
        local level = sq_GetSkillLevel(obj, SKILL_PARTICLE_VOLD);		
        local useHp = sq_GetLevelData(obj, SKILL_PARTICLE_VOLD, 1, level);

        if (obj.getHp() < useHp)
            return false;
    }



    //

        //?p?G?o???H ???s?b ??? ?L?S???????b????W?A?N???

        //??????O?_cd?A?p?Gcd isUse??false ?_?h?|????i?J?N?o?A
        //?P??isUse???True

        local isUse = obj.sq_IsUseSkill(SKILL_PARTICLE_SMOKE);
        if (isUse) {

            sendOutParticleSmokePassiveObject(obj);

    //        obj.getVar("state").clear_vector();
    //        obj.getVar("state").push_vector(0);
    //		obj.sq_AddSetStatePacket(STATE_PARTICLELINE , STATE_PRIORITY_USER, false);
            return true;
        }


	return false;
}

function checkCommandEnable_particlesomke(obj)
{//??^ true???G ??? ??
	if (!obj) return false;

    local voidObj = getParticleVoid(obj);
    //?p?G?o???H ???s?b ??? ?L?S???????b????W?A?N???
    if (!voidObj )
        return false;

    if (voidObj.getVar("state").get_vector(0) == PARTICLE_VOLD_STATE_MYSELF)
    {
        local level = sq_GetSkillLevel(obj, SKILL_PARTICLE_VOLD);		
        local useHp = sq_GetLevelData(obj, SKILL_PARTICLE_VOLD, 1, level);

        if (obj.getHp() < useHp)
            return false;
    }

	return true;
}

function createParticleSmokeShootingNormalEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atcrowlingmyst/crowlingmist_shoot_normal.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos()+1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createParticleSmokeShootingDodgeEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atcrowlingmyst/crowlingmist_shoot_dodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos()-1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function sendOutParticleSmokePassiveObject(obj)
{
    if (!obj.isMyControlObject())
        return false;

    local voidObj = getParticleVoid(obj);

    if (voidObj)
    {
        if (voidObj.getVar("state").get_vector(0) == PARTICLE_VOLD_STATE_MYSELF)
        {
            //?o?{?@??????H?]boss?u???Q?o?{?F?^
            local tar = findOneTargetWithDistance(obj);
            if (tar)
            {
                local level = sq_GetSkillLevel(obj, SKILL_PARTICLE_VOLD);		
                local useHp = sq_GetLevelData(obj, SKILL_PARTICLE_VOLD, 1, level);
                obj.setHp( obj.getHp() - useHp , null, true);
                createParticleSmokeShootingNormalEffect(obj);
                createParticleSmokeShootingDodgeEffect(obj);

                voidObj.getVar("state").clear_vector();
                voidObj.getVar("state").push_vector(PARTICLE_VOLD_STATE_TO_ENEMY);
                voidObj.getVar("subState").clear_vector();
                voidObj.getVar("subState").push_vector(0);
                voidObj.getVar("tar").clear_obj_vector();
                voidObj.getVar("tar").push_obj_vector( tar );

                local pIntVec = sq_GetGlobalIntVector();
                sq_IntVectorClear(pIntVec);
                sq_IntVectorPush(pIntVec, 0);
                voidObj.addSetStatePacket(11, pIntVec, STATE_PRIORITY_AUTO, false, "");

                local appendage = getComboUiAppendage(obj);

                if (!appendage)
                    return true;

                local currT = appendage.getTimer().Get();

                local i = 0;

                for (;i < 400 ;i++)
                    if (appendage.getVar("damageNum").get_vector(i) == 0)
                        break;
                
                i = i % 400;
                appendage.getVar("damageNum").set_vector(i,useHp);
                appendage.getVar("damageNum").set_vector(i + 1,currT);
                appendage.getVar("damageNum").set_vector(i + 2,obj.getXPos() * 10 + 1 );
                appendage.getVar("damageNum").set_vector(i + 3,obj.getYPos() * 1000 + obj.getZPos() );


            }

        }else if (voidObj.getVar("state").get_vector(0) == PARTICLE_VOLD_STATE_TO_ENEMY) {


            if (voidObj.getVar("subState").get_vector(0) == 2)
            {

                voidObj.getVar("state").clear_vector();
                voidObj.getVar("state").push_vector(PARTICLE_VOLD_STATE_RETRUN_MYSELF);
                local pIntVec = sq_GetGlobalIntVector();
                sq_IntVectorClear(pIntVec);
                sq_IntVectorPush(pIntVec, 0);
                voidObj.addSetStatePacket(12, pIntVec, STATE_PRIORITY_AUTO, false, "");



            }

        }

    }

}




function findOneTargetWithDistance(obj)
{
	local objectManager = obj.getObjectManager();
    local distance = 1000 * 1000;
    local target = null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) &&object.isInDamagableState(obj))
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            if (true)
            {
                
                local curDistance = abs(obj.getXPos() - object.getXPos() ) * abs(obj.getXPos() - object.getXPos() ) + 
                                 abs(obj.getYPos() - object.getYPos() ) * abs(obj.getYPos() - object.getYPos() );

                if (activeObj.isBoss() )
                {
                    return activeObj;
                }
                if (curDistance < distance)
                {
                    distance = curDistance;
                    target = activeObj;


                }
                //return activeObj;
            }
		}
	}
    return target;
}

function sq_AddFunctionName(appendage)
{
	//dofile("demoniclancer/cs.nut");
	appendage.sq_AddFunctionName("proc", "proc_appendage_BodyPressedSin")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BodyPressedSin")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BodyPressedSin")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_BodyPressedSin")
}

function sq_AddEffect(appendage)
{
		
}


function onAttackParent_appendage_BodyPressedSin(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if(!appendage) return
	local parentObj = appendage.getParent();
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!obj && !obj.isMyControlObject())
		return;
	local colObj = sq_GetCNRDObjectToCollisionObject(realAttacker);
	local txobj = colObj.getCollisionObjectIndex();
	local id = colObj.getVar("id").get_vector(0);
	local ChrState = obj.sq_GetState();
	local ChrSubState = obj.getSkillSubState();
	obj.getVar("damaFirstPrana").set_vector(0,1);
	if (!damager) return;
	if (!damager.isObjectType(OBJECTTYPE_ACTIVE)) return;
	if(ChrState == 8 || ChrState == 15)  return;
	local ani = sq_AddDrawOnlyAniFromParent(damager,"common/hiteffect/animation/rosehiteffect/attemptresshiteffect_small.ani", 0, 1, sq_GetObjectHeight(damager)*2/5);
	if(ani)
		sq_moveWithParent(damager, ani);
}


function atfirstpranaObject(obj)
{
	if(!obj && !obj.isMyControlObject()) return;
	local ChrState = obj.sq_GetState();
	local ChrSubState = obj.getSkillSubState();


	local skill_level = sq_GetSkillLevel(obj, SKILL_FIRSTPRANA);//��������
	if(skill_level > 0)
	{
    if (obj.getVar("damaFirstPrana").get_vector(0) == 1 && obj.getVar("flagFirstPrana").get_vector(0) == 0 && obj.isMyControlObject())
    {
	if(ChrState == STATE_LUSTHAND && ChrSubState == 0
	|| ChrState == STATE_PRIDEACCEL && ChrSubState == 3
	|| ChrState == STATE_ENVIOUSKISS && ChrSubState == 0
	|| ChrState == STATE_FLOWEROFPURIFICATION && ChrSubState == 0
	|| ChrState == STATE_SLOTHBODY && ChrSubState == 1
	|| ChrState == STATE_SCUDTHEWRATH && ChrSubState == 1
	|| ChrState == STATE_HANDAWAKENTOSIN && ChrSubState == 1
	|| ChrState == STATE_THIRDRIB && ChrSubState == 1
	|| ChrState == STATE_LASTGENESIS && ChrSubState == 2
	)
    {
	obj.sq_StartWrite();
	obj.sq_WriteDword(17);
	obj.sq_WriteDword(obj.sq_GetIntData(SKILL_FIRSTPRANA, 1));
    obj.sq_SendCreatePassiveObjectPacket(24384, 0, 0, 0, 0 );

	}
	}
	}
}


function onEnd_appendage_BodyPressedSin(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
}


function proc_appendage_BodyPressedSin(appendage)
{
	if(!appendage) {
		return;		
	}

    local parentObj = appendage.getParent();
    local sourceObj = appendage.getSource();
    parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

	atfirstpranaObject(parentObj);
    parentObj.getVar("damaFirstPrana").set_vector(0,0);
    if (appendage.getVar("flagBodyPressedSin").get_vector(0) == 0 && parentObj.isMyControlObject())
    {
        appendage.getVar("flagBodyPressedSin").clear_vector();
        appendage.getVar("flagBodyPressedSin").push_vector(1);

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(16);
        sq_SendCreatePassiveObjectPacketPos(sourceObj, 24384, 0, sourceObj.getXPos(), sourceObj.getYPos() + 1, 0);
    }

	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_BodyPressedSin(appendage)
{
	if(!appendage) {
		return;		
	}
    appendage.getVar("flagBodyPressedSin").clear_vector();
    appendage.getVar("flagBodyPressedSin").push_vector(0);

	local DamageMonster = appendage.getParent();
	local ChrMater = appendage.getSource();
	local SqrChr = sq_GetCNRDObjectToSQRCharacter(DamageMonster);
    SqrChr.getVar("flagFirstPrana").clear_vector();
	SqrChr.getVar("flagFirstPrana").push_vector(0);

    SqrChr.getVar("damaFirstPrana").clear_vector();
	SqrChr.getVar("damaFirstPrana").push_vector(0);
}
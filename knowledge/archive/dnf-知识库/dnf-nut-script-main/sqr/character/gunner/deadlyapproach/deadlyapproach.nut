



 
function checkExecutableSkill_gunner_deadlyapproach(lxM2KkDuBOQhR)
{
 if(!lxM2KkDuBOQhR) return false; 
 local psuArGbBouoY2clAHvu = lxM2KkDuBOQhR.sq_IsUseSkill(236); 
 if(psuArGbBouoY2clAHvu) 
 {
 lxM2KkDuBOQhR.sq_IntVectClear();
 lxM2KkDuBOQhR.sq_IntVectPush(0); 
 lxM2KkDuBOQhR.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_gunner_deadlyapproach(lxM2KkDuBOQhR)
{
 if(!lxM2KkDuBOQhR) return false; 
 local psuArGbBouoY2clAHvu = lxM2KkDuBOQhR.sq_GetState(); 
 if(psuArGbBouoY2clAHvu == STATE_STAND) 
 return true; 
 if(psuArGbBouoY2clAHvu == STATE_ATTACK) 
 {
 return lxM2KkDuBOQhR.sq_IsCommandEnable(236); 
 }
 return true; 
} ;

 
function onSetState_gunner_deadlyapproach(obj, Sk6nYn81GrxbAV, kTbiDnTL6NDFvtTwaB, M46uOO8uVKijlZhJYQeMA)
{
	if(!obj) return; 
	obj.sq_StopMove(); 
	local substate = obj.sq_GetVectorData(kTbiDnTL6NDFvtTwaB, 0); 
	obj.setSkillSubState(substate); 
	switch(substate)
	{
		case 0:
			obj.sq_SetCurrentAnimation(114); 
			sq_SetCurrentDirection(sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/deadlyapproach/deadlyapproach_start_dusta.ani", ENUM_DRAWLAYER_NORMAL, true), sq_GetOppositeDirection(obj.getDirection())); 
		break;
		case 1:
			obj.sq_SetCurrentAnimation(115); 
			obj.setDirection(sq_GetOppositeDirection(obj.getDirection())); 
		break;
		case 2:
			obj.sq_SetCurrentAnimation(116); 
			sq_SetZVelocity(obj, -300, -300); 
			obj.sq_SetStaticMoveInfo(0, 480, 480, false); 
			obj.sq_SetStaticMoveInfo(1, 0, 0, false); 
			obj.sq_SetMoveDirection(sq_GetOppositeDirection(obj.getDirection()), ENUM_DIRECTION_NEUTRAL); 
		break;
		case 3:
			obj.sq_SetCurrentAnimation(117); 
			sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/deadlyapproach/deadlyapproach_end_dustback.ani", ENUM_DRAWLAYER_NORMAL, true);
		break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
} ;

function onCreateObject_gunner_deadlyapproach(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	if(state == STATE_GUNNER_DEADLYAPPROACH)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			obj.getVar("deadlyapproach").push_obj_vector(Object);
		}
	}
}
 
function onKeyFrameFlag_gunner_deadlyapproach(obj, flagIndex)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 0:
		if(flagIndex == 1)
		{
			sq_SetMyShake(obj, 3, 100); 
			sq_SetZVelocity(obj, 250, 250); 
			if(obj.sq_IsMyControlObject())
			{
				local Direction = obj.getDirection(); 
				local KeyDown = (Direction == ENUM_DIRECTION_LEFT && sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)
				|| Direction == ENUM_DIRECTION_RIGHT && sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
				? 930
				: 600; 
				
				sq_BinaryStartWrite();
				sq_BinaryWriteWord(1);
				sq_BinaryWriteDword(KeyDown);
				sq_BinaryWriteWord(Direction);
				sq_SendChangeSkillEffectPacket(obj, SKILL_GUNNER_DEADLYAPPROACH); 
			}
		}
		break;
		case 1:
			if(obj.sq_IsMyControlObject())
			{
				sq_flashScreen(obj, 0, 80, 0, 25, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
				createHeadShotDown(obj, "passiveobject/character/gunner/animation/deadlyapproach/shooteffect_1.ani",0, 0, 0,ENUM_DRAWLAYER_NORMAL,true,0,true,100,"")
				local particleCreater = obj.getVar("deadlyapproach").GetparticleCreaterMap("deadlyapproach", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos()-1, obj.getZPos());
				sq_AddParticleObject(obj, particleCreater);
			}
			if(flagIndex == 1) 
			{
				sq_SetZVelocity(obj, 25, 25); 
				obj.sq_SetStaticMoveInfo(0, 240, 240, false); 
				obj.sq_SetStaticMoveInfo(1, 0, 0, false); 
				obj.sq_SetMoveDirection(sq_GetOppositeDirection(obj.getDirection()), ENUM_DIRECTION_NEUTRAL); 
			}
		break;
	}
	return true;
}


 function createHeadShotDown(obj, aniFilename,Xpos, Ypos, Zpos,DRAWLAYER,trueImage,angle,bool,Size,Push_obj)
{
	if(!obj) return
	local image = sq_CreateDrawOnlyObject(obj,aniFilename,DRAWLAYER,trueImage);
	if(bool == true)
	{
		local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), Xpos);
		image.setCurrentPos(posX,obj.getYPos() + Ypos,obj.getZPos() + Zpos);
	}
	else
	{
		image.setCurrentPos(Xpos,Ypos,Zpos);
	}
	local rotate = angle.tointeger() * 0.017453;
	image.setCustomRotate(true,rotate);
	local imageAni = image.getCurrentAnimation();
	local SizeFloat = Size.tofloat() / 100.0;
	imageAni.Proc();
	imageAni.setImageRateFromOriginal(SizeFloat, SizeFloat);
	imageAni.setAutoLayerWorkAnimationAddSizeRate(SizeFloat);
	obj.getVar(Push_obj).push_obj_vector(image);
}

function onProc_gunner_deadlyapproach(obj)
{
	if(!obj) return;
	local substate = obj.getSkillSubState(); 
	if (substate == 1)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("deadlyapproach").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 2);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GUNNER_DEADLYAPPROACH, STATE_GUNNER_DEADLYAPPROACH, 0, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
				sq_SetCurrentAttacknBackForce(attackInfo, 0); 
				sq_SetCurrentAttacknUpForce(attackInfo, 50); 
				sq_SetCurrentAttackeHitStunTime(attackInfo, 0);
			}
		}
	}
}
 
function onProcCon_gunner_deadlyapproach(d_Ru0gCCOqz1reZ8EKjqU8nX)
{
 if(!d_Ru0gCCOqz1reZ8EKjqU8nX) return;
 local Sd3ibfZrLJ9OQiW8 = d_Ru0gCCOqz1reZ8EKjqU8nX.getSkillSubState(); 
 if(Sd3ibfZrLJ9OQiW8 == 2) 
 {
 if(d_Ru0gCCOqz1reZ8EKjqU8nX.getZPos() <= 0) 
 {
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IntVectClear();
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IntVectPush(3); 
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); 
 return; 
 }
 }
} ;

 
function onEndCurrentAni_gunner_deadlyapproach(d_Ru0gCCOqz1reZ8EKjqU8nX)
{
 if(!d_Ru0gCCOqz1reZ8EKjqU8nX) return;
 local Sd3ibfZrLJ9OQiW8 = d_Ru0gCCOqz1reZ8EKjqU8nX.getSkillSubState(); 
 switch(Sd3ibfZrLJ9OQiW8)
 {
 case 0:
 case 1:
 if(d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IsMyControlObject())
 {
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IntVectClear();
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IntVectPush(Sd3ibfZrLJ9OQiW8 + 1); 
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); 
 }
 break;
 case 3:
 d_Ru0gCCOqz1reZ8EKjqU8nX.setDirection(sq_GetOppositeDirection(d_Ru0gCCOqz1reZ8EKjqU8nX.getDirection())); 
 if(d_Ru0gCCOqz1reZ8EKjqU8nX.sq_IsMyControlObject())
 d_Ru0gCCOqz1reZ8EKjqU8nX.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
 break;
 }
} ;

function onChangeSkillEffect_gunner_deadlyapproach(OxJ176kStrwa1OykCytqdY, z6EYed4aCW6xmV8G7pH95, QoPmDKH9nlMOlVck)
{
 if(!OxJ176kStrwa1OykCytqdY) return;
 switch(z6EYed4aCW6xmV8G7pH95)
 {
 case 236:
 local cqXiAVtIvDl7J = QoPmDKH9nlMOlVck.readWord(); 
 switch(cqXiAVtIvDl7J)
 {
 case 1:
 local WOBEaVRWrcD2TcLzro = QoPmDKH9nlMOlVck.readDword(); 
 local rh_w9DdcZy5d2ICz_vp = QoPmDKH9nlMOlVck.readWord(); 
 OxJ176kStrwa1OykCytqdY.sq_SetStaticMoveInfo(0, WOBEaVRWrcD2TcLzro, WOBEaVRWrcD2TcLzro, false); 
 OxJ176kStrwa1OykCytqdY.sq_SetStaticMoveInfo(1, 0, 0, false); 
 OxJ176kStrwa1OykCytqdY.sq_SetMoveDirection(rh_w9DdcZy5d2ICz_vp, ENUM_DIRECTION_NEUTRAL); 
 break;
 }
 break;
 }
} ;

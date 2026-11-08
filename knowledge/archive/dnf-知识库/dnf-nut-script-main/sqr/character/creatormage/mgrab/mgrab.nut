
SUB_STATE_MGRAB_0	<- 0
SUB_STATE_MGRAB_1	<- 1

function setStateMouseGrab(obj)
{
	if (!obj) return;
	
	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	releaseOutLine(obj, "grabobj");
	

	obj.getVar("mgrab").clear_vector();
	obj.getVar("mgrab").push_vector(0);
	obj.getVar("mgrab").push_vector(0);
	
	obj.getVar("mgrab").clear_timer_vector();
	obj.getVar("mgrab").push_timer_vector();
	
	local t = obj.getVar("mgrab").get_timer_vector(0);
	t.setParameter(100, -1);
	t.resetInstant(0);
	
	obj.getVar("mgrab").clear_ct_vector();
	obj.getVar("mgrab").push_ct_vector();
	local timer = obj.getVar("mgrab").get_ct_vector(0);
	timer.Reset();
	timer.Start(10000,0);
}

function grabThrowObject(obj)
{
	local hoverEnemyObject = getOverClickableEnemyObject(obj, IMouse.GetXPos(), IMouse.GetYPos());
		
	if (hoverEnemyObject)
	{
		local grabable = sq_IsGrabable(obj, hoverEnemyObject);
			
		print(" grab:" + grabable + " holdable:" + sq_IsHoldable(obj, hoverEnemyObject));
		if (sq_IsHoldable(obj, hoverEnemyObject) == true && sq_IsGrabable(obj, hoverEnemyObject) == true)
		{ // ��Ⱑ�����̶�� Ǫ���մϴ�.
			
			// �������� �ִ� ��쿡��?�������� �ٿ��ݴϴ�.
			local consumeValue = getCreatorSkillConsumeValue(obj, SKILL_MGRAB);
				
			if (!useCreatorSkill(obj, SKILL_MGRAB, 0, 0, consumeValue))
				return;
			//
				
											
			obj.getVar("grabobj").push_obj_vector(hoverEnemyObject); // grabobj 				
				
			local activeobj = sq_GetCNRDObjectToActiveObject(hoverEnemyObject);
				
			if (activeobj)
			{
				// �Ѹ����� ��´�?
				local objListSize = obj.getVar("grabobj").get_obj_vector_size();
					
				print(" objListSize:" + objListSize);
					
				for (local i =0;i<objListSize;++i)
				{				
					local vObj = obj.getVar("grabobj").get_obj_vector(i);
						
					local act = sq_GetCNRDObjectToActiveObject(vObj);
						
					if (act == null)
						continue;							
						
					sq_IntVectorClear(sq_GetGlobalIntVector());
					sq_IntVectorPush(sq_GetGlobalIntVector(),0);
					sq_AddSetStatePacketActiveObject(act,STATE_HOLD, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
				}
			}
		} //if (sq_IsHoldable(obj, hoverEnemyObject) == false && sq_IsGrabable(obj, hoverEnemyObject) == true)
			
	}
}


function onSetState_Mgrab(obj,state,datas,isResetTimer)
{
}

function onChangeSkillEffect_Mgrab(obj, skillIndex, reciveData)
{
	if (!obj)
		return;
		
	local size = 8; // �ϳ� �� �߰��ؾ���
	local data_l =[];
	
	data_l.resize(size);
	
	for (local i = 0; i < 8; i++)
	{
		data_l[i] = -1;
		
		if (reciveData.getSize() > 0)
		{
			data_l[i] = reciveData.readDword();
		}
	}
		
	local targetObj = sq_GetObject(obj, data_l[0], data_l[1]);
	
	if (targetObj)
	{
		local xPos = data_l[2];
		local zPos = data_l[3];
		
		if (zPos < 0)
			zPos = 0;
		
		local stateTimer = obj.sq_GetStateTimer();
		
		if (!obj.getVar("mgrab").get_vector(0))
		{
			obj.getVar("mgrab").set_vector(0, xPos);
			obj.getVar("mgrab").set_vector(1, zPos);
		}
		
		local state = data_l[4];
		print(" on change state:" + state);
		
		//if (obj.isMyControlObject())
		{
			if (state == 0)
			{
				if (targetObj.getState() != STATE_HOLD && targetObj.getState() != STATE_DOWN)
				{
					local act = sq_GetCNRDObjectToActiveObject(targetObj);
					
					if (act)
					{
						sq_IntVectorClear(sq_GetGlobalIntVector());
						sq_IntVectorPush(sq_GetGlobalIntVector(),0);
						sq_AddSetStatePacketActiveObject(act, STATE_HOLD, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
						print(" onchange setstate hold");					
					}
				}
			}
			else if (state == 1)
			{
				local act = sq_GetCNRDObjectToActiveObject(targetObj);
				
				if (act)
				{				
					local direction = data_l[5];
					local nX = data_l[6];
					local nY = data_l[7];
					
					sq_IntVectorClear(sq_GetGlobalIntVector());
					sq_IntVectorPush(sq_GetGlobalIntVector(),direction);
					sq_IntVectorPush(sq_GetGlobalIntVector(),0);
					sq_IntVectorPush(sq_GetGlobalIntVector(),1);
					sq_IntVectorPush(sq_GetGlobalIntVector(),nX);
					sq_IntVectorPush(sq_GetGlobalIntVector(),nY);
					sq_AddSetStatePacketActiveObject(act,STATE_DOWN, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
					print(" onchange setstate down:");
				}
			}
		}
		
		
		sq_SetCurrentPos(targetObj, xPos, targetObj.getYPos(), zPos);
	}
		
}


function prepareDraw_Mgrab(obj)
{

	if (!obj) return;

}

// �Ÿ� ���� Ÿ���� ã�Ƴ��� �����ϴ� �Լ��Դϴ�.
function pushTargetDistanceMinObject(obj, targetObj, distance)
{
	if (!obj)
		return;
		
	local objectManager = obj.getObjectManager();

	if (objectManager == null)
		return;
		
	if (!targetObj)
		return;

	obj.getVar("mgrab").clear_obj_vector();
	
	local grabObj = null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (sq_IsHoldable(obj, object) == true && sq_IsGrabable(obj, object) == true)
		{ // ��Ⱑ�����̶�� Ǫ���մϴ�.					
			if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE))
			{
				local isSame = isSameObject(targetObj, object);
				if (isSame)
					continue;
				
				
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
				//	���� ������ ���� �����?���� �����?
				
				if (activeObj)
				{
					if (!activeObj.isDead())
					{
						local dis = sq_GetDistanceObject(targetObj, object, false);
						
						if (dis < distance)
						{
							distance = dis;
							grabObj = activeObj;
							//obj.getVar("mgrab").push_obj_vector(object);
						}
					}
				}
			}
		} //if (sq_IsHoldable(obj, hoverEnemyObject) == false && sq_IsGrabable(obj, hoverEnemyObject) == true)
	}
	
	if (grabObj)
	{
		obj.getVar("mgrab").push_obj_vector(grabObj);
	}
}


function onProc_Mgrab(obj)
{

	if (!obj) return;
	
	if (!obj.isMyControlObject())
		return;

	local objListSize = obj.getVar("grabobj").get_obj_vector_size();

	if (objListSize <= 0)
		return;

	local stage = sq_GetObjectManagerStage(obj);
	
	if (!stage)
		return;

	local control = stage.getMainControl();	
	
	if (control.IsRBDown())
	{
		onMouseMoveButtonDown_Mgrab(obj);
	}
	else
	{
		onMouseButtonUp_Mgrab(obj);
	}
}

// ���콺 ��ư�� �������� �� ó���ؾߵǴ� �κ��Դϴ�.
function onMouseButtonUp_Mgrab(obj)
{
	local objListSize = obj.getVar("grabobj").get_obj_vector_size();
	
	print(" onMouseButtonUp_Mgrab:" + objListSize);
	for (local i = 0; i < objListSize;++i)
	{

		local hoverEnemy = obj.getVar("grabobj").get_obj_vector(i);
		if (hoverEnemy)
		{
			local activeobj = sq_GetCNRDObjectToActiveObject(hoverEnemy);
			if (activeobj)
			{
				local srcX = obj.getVar("mgrab").get_vector(0);
				local srcY = sq_GetYPos(activeobj);
				local srcZ = obj.getVar("mgrab").get_vector(1);
				
				if (srcZ < 0)
					srcZ = 0;

				local dstX = sq_GetXPos(activeobj);
				local dstY = sq_GetYPos(activeobj);
				local dstZ = sq_GetZPos(activeobj);
				
				if (dstZ < 0)
					dstZ = 0;
				
				print(" sx:" + srcX + " sy:" + srcY + " sz:" + srcZ);				
				print(" dx:" + dstX + " dy:" + dstY + " dz:" + dstZ);
				
				local distance = sq_GetDistance( srcX, srcZ, dstX, dstZ, true);
				
				local width = sq_Abs(dstX - srcX);
				local h = sq_Abs((dstZ) - (srcZ));
				
				print(" h:" + h);
				
				if (h <= 0)
					h = 10;
				
				local angle = sq_Atan2( h.tofloat(), width.tofloat());
				
				local nRevision = distance;

				local cos = nRevision.tofloat() * sq_Cos(angle);
				local sin = nRevision.tofloat() * sq_Sin(angle);

				local nX = sq_Abs( cos.tointeger() ) * 2;
				local nY = sq_Abs( sin.tointeger() ) * 2;
				
				
				local direction = sq_GetDirection(activeobj);
				
				if ((dstX - srcX) < 0)
				{
					nX = -nX;
				}


				direction = 0;
				print(" nX:" + nX + " nY:" + nY + " offset:" + (dstX - srcX) + " direction:" + direction + " activeobj:" + activeobj);
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(),direction);
				sq_IntVectorPush(sq_GetGlobalIntVector(),0);
				sq_IntVectorPush(sq_GetGlobalIntVector(),1);
				sq_IntVectorPush(sq_GetGlobalIntVector(),nX);
				sq_IntVectorPush(sq_GetGlobalIntVector(),nY);
				sq_AddSetStatePacketActiveObject(activeobj,STATE_DOWN, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
				print(" activeobj:" + activeobj + " setstate down:");
				
				
				local group = sq_GetGroup(activeobj);
				local uniqueId = sq_GetUniqueId(activeobj);			
			
				sq_BinaryStartWrite();
				
				sq_BinaryWriteDword(group); // 0
				sq_BinaryWriteDword(uniqueId); // 1
				sq_BinaryWriteDword(dstX); // 2
				sq_BinaryWriteDword(dstZ); // 3
				// 1���� state_down�����Դϴ�.
				sq_BinaryWriteDword(1); // 4
				sq_BinaryWriteDword(direction); // 5
				sq_BinaryWriteDword(nX); // 6
				sq_BinaryWriteDword(nY); // 7
				sq_SendChangeSkillEffectPacket(obj, SKILL_MGRAB);
				print(" sq_SendChangeSkillEffectPacket down");
			}
		}
	}

	obj.getVar("mgrab").clear_vector();
	obj.getVar("mgrab").push_vector(0);
	obj.getVar("mgrab").push_vector(0);

	releaseOutLine(obj, "grabobj");
	
	if (objListSize)
	{
		obj.sq_PlaySound("R_THROW_MONSTER");
	}
}

// ���콺 ��ư�� �ٿ������?�� ó���ؾߵǴ� �κ��Դϴ�. 
function onMouseMoveCharacter_Mgrab(obj)
{
	onMouseMoveButtonDown_Mgrab(obj);
}


function onMouseMoveButtonDown_Mgrab(obj)
{
	local hoverEnemy = obj.getVar("grabobj").get_obj_vector(0);

	if (!hoverEnemy)
	{
		return;
	}
	else
	{
		local objectManager = obj.getObjectManager();
		
		local objListSize = obj.getVar("grabobj").get_obj_vector_size();
		
		local t = obj.getVar("mgrab").get_ct_vector(0);
		local time = 0;
	
		if(t)
			time = t.Get();

		local skill_level = obj.sq_GetSkillLevel(SKILL_MGRAB);


		local activeObj = sq_GetCNRDObjectToActiveObject(hoverEnemy);

		if (!activeObj)
		{
			onMouseButtonUp_Mgrab(obj);
			return;
		}

		local columnIndex = SKL_LV_0;
		if (sq_IsNamed(activeObj))
		{	
			// ���ӵ� �϶� Į��1
			columnIndex = SKL_LV_1;
		}
		else if (sq_IsBoss(activeObj))
		{
			// ���� �϶� Į��2
			columnIndex = SKL_LV_2;
		}
		else if (sq_IsHellMonster(activeObj))
		{
			// �����?�϶� Į��3
			columnIndex = SKL_LV_3;
		}
		else if (sq_IsAiCharacter(activeObj))
		{
			// apc�϶�
			columnIndex = SKL_LV_4;
		}

		// �������?�� �ִ� �ִ�ð�?
		local maxTime = obj.sq_GetLevelData(SKILL_MGRAB, columnIndex, skill_level); 

		print(" maxTime:" + maxTime + " time:" + time);

		if (time > maxTime)
		{
			onMouseButtonUp_Mgrab(obj);
		}
		else
		{
			for (local i =0;i<objListSize;++i)
			{
				local vObj = obj.getVar("grabobj").get_obj_vector(i);
			
				if (!vObj)
					continue;
			
				local xPos = objectManager.getFieldXPos(IMouse.GetXPos(), ENUM_DRAWLAYER_NORMAL);
				local zPos = objectManager.getFieldZPos(IMouse.GetYPos(), vObj.getYPos(), ENUM_DRAWLAYER_NORMAL) - (sq_GetObjectHeight(hoverEnemy) / 2);
			
				local group = sq_GetGroup(vObj);
				local uniqueId = sq_GetUniqueId(vObj);			
		
				sq_BinaryStartWrite();
			
				sq_BinaryWriteDword(group); // 
				sq_BinaryWriteDword(uniqueId); //
				sq_BinaryWriteDword(xPos);
				sq_BinaryWriteDword(zPos);
				// 0���� state_hold�����Դϴ�.
				sq_BinaryWriteDword(0); 
				sq_BinaryWriteDword(0); 
				sq_BinaryWriteDword(0); 
				sq_BinaryWriteDword(0); 
				sq_SendChangeSkillEffectPacket(obj, SKILL_MGRAB);
			}
		}
	}

}


function onProcCon_Mgrab(obj)
{

	if (!obj) return;

}

function onEndCurrentAni_Mgrab(obj)
{

	if (!obj) return;

}

function onKeyFrameFlag_Mgrab(obj,flagIndex)
{

	if (!obj) return false;

	return true;

}

function onEndState_Mgrab(obj,new_state)
{

	if (!obj) return;

}

function onAfterSetState_Mgrab(obj,state,datas,isResetTimer)
{

	if (!obj) return;

}

function onBeforeAttack_Mgrab(obj,damager,boundingBox,isStuck)
{

	if (!obj) return;

}

function onAttack_Mgrab(obj,damager,boundingBox,isStuck)
{

	if (!obj) return;

}

function onAfterAttack_Mgrab(obj,damager,boundingBox,isStuck)
{

	if (!obj) return 0;

	return 1;

}

function onBeforeDamage_Mgrab(obj,attacker,boundingBox,isStuck)
{

	if (!obj) return;

}

function onDamage_Mgrab(obj,attacker,boundingBox)
{

	if (!obj) return;

}

function onAfterDamage_Mgrab(obj,attacker,boundingBox)
{

	if (!obj) return;

}

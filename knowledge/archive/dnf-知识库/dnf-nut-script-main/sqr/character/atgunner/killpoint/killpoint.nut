


//事件：當玩家按下技能鍵時 檢查可執行技能文件
function checkExecutableSkill_atgunner_killpoint(obj)
{
	if(!obj) return false;//當對象為null時返回假

	local direction = -1;//傳遞的方向
	local myDirection = obj.getDirection();//我自己方向
	local xPos = sq_GetXPos(obj);//我自己的X坐標
	local info = [];//儲存數組
	local objectManager = obj.getObjectManager();//得到對象管理器
	local objectNumber = objectManager.getCollisionObjectNumber();//總數
	for(local i = 0; i < objectNumber; i++)
	{
		local object = objectManager.getCollisionObject(i);//得到控制類對象
		//不是敵人 不是活動類 就繼續循環
		if(!obj.isEnemy(object) || !object.isObjectType(OBJECTTYPE_ACTIVE)) continue;

		local dieHardAppendage = CNSquirrelAppendage.sq_GetAppendage(object, "character/atgunner/killpoint/ap_killpoint.nut");
		if(dieHardAppendage && isSameObject(obj, dieHardAppendage.getSource()) && dieHardAppendage.isValid())
		{
			local isInLR = (xPos > sq_GetXPos(object)) ? ENUM_DIRECTION_LEFT : ENUM_DIRECTION_RIGHT;//在我左還是右

			if(direction == -1)//沒有獲取方向
				direction = isInLR;//獲取第一個找到的敵人面向的方向

			//在我面向的方向 才會攻擊 反之 刪除它身上的ap
			if(direction != -1 && direction == isInLR)
				info.push(1);//1為攻擊
			else//反之是在我反方向
				info.push(2);//2為刪除

			info.push(sq_GetGroup(object));//加入數組
			info.push(sq_GetUniqueId(object));//加入數組
		}
	}

	if(info.len() > 0 && direction != -1)//存入的東西大于0
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_IntVectPush(sq_getRandom(0, 1));//使用的ani
		obj.sq_IntVectPush(direction);//方向
		obj.sq_IntVectPush(info.len());//多少個
		foreach(val in info)
			obj.sq_IntVectPush(val);//存入組跟ID

		obj.sq_AddSetStatePacket(STATE_ATGUNNER_KILLPOINT, STATE_PRIORITY_USER, true);//發送狀態
		return true;//返回真
	}

	local isUse = obj.sq_IsUseSkill(SKILL_ATGUNNER_KILLPOINT);//是否是可以使用的技能 而不是在冷卻或禁用
	if(isUse)//如果局部變量isUse為真
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); // substate
		obj.sq_AddSetStatePacket(STATE_ATGUNNER_KILLPOINT, STATE_PRIORITY_USER, true);//發送狀態
		return true;//返回真
	}
	return false;
}

//事件：檢查是否啟用技能
function checkCommandEnable_atgunner_killpoint(obj)
{
	if(!obj) return false;//如果對象為null返回假
	local state = obj.sq_GetState();//得到對象的狀態賦值給局部變量state
	if(state == STATE_STAND)//如果狀態是站立或跳躍
		return true;//返回真
	if(state == STATE_ATTACK)//如果狀態等于攻擊
	{
		return obj.sq_IsCommandEnable(SKILL_ATGUNNER_KILLPOINT); // 
	}
	return true;//返回真
}

// 事件：開始設置state 按下技能鍵時會第一進入此處
function onSetState_atgunner_killpoint(obj, state, datas, isResetTimer)
{
	if(!obj) return;//如果對象為null則返回
	obj.sq_StopMove();//對象停止移動
	obj.getVar().clear_vector();//清除
	local subState = obj.sq_GetVectorData(datas, 0);//得到傳過來的第0個值
	obj.setSkillSubState(subState);//設置當前技能狀態
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATGUNNER_KILLPOINTREADY_BODY);
			local skill_level = sq_GetSkillLevel(obj, SKILL_ATGUNNER_KILLPOINT);//技能等級
			obj.getVar().push_vector(obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 0, skill_level));//投擲鎖鏈槍刃數量上限
			break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATGUNNER_KILLPOINTFINISHD_BODY);
			obj.setDirection(obj.sq_GetVectorData(datas, 2));//設置方向
			local objVar = obj.getVar();//得到
			local count = obj.sq_GetVectorData(datas, 3);//多少個
			for(local i = 0; i < count; i += 3)
			{
				local atkType = obj.sq_GetVectorData(datas, 4 + i);//類型 1攻擊 2刪除
				local group = obj.sq_GetVectorData(datas, 4 + i + 1);//組
				local uniqueId = obj.sq_GetVectorData(datas, 4 + i + 2);//唯一ID
				local targetObj = sq_GetObject(obj, group, uniqueId);//得到對象
				if(targetObj)
				{
					local dieHardAppendage = CNSquirrelAppendage.sq_GetAppendage(targetObj, "character/atgunner/killpoint/ap_killpoint.nut");
					if(dieHardAppendage && dieHardAppendage.isValid())
					{
						switch(atkType)
						{
							case 1://確認攻擊
								if(dieHardAppendage.getVar().size_vector() > 0)
								{
									local limitTime = dieHardAppendage.getVar().get_vector(4);//限制時間
									if(limitTime > 0)
										dieHardAppendage.getVar().set_vector(4, 0);//改變限制時間
								}
								objVar.push_vector(group);//加入
								objVar.push_vector(uniqueId);//加入
								break;
							case 2://直接刪除ap
								dieHardAppendage.setValid(false);
								break;
						}
					}
				}
			}
			break;
	}

	local currentDelay = obj.sq_GetDelaySum();//當前延時
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);//吃攻速
	local laterDelay = obj.sq_GetDelaySum();//加速后的延時
	local speedRate = currentDelay.tofloat() / laterDelay.tofloat() * 100.0;//速度率

	switch(subState)
	{
		case 1:
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_ATGUNNER_KILLPOINTFINISH);
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_KILLPOINT, STATE_ATGUNNER_KILLPOINT, 2, 1.0);//快速射擊攻擊力
			obj.sq_SetCurrentAttackBonusRate(attackBonusRate);//設置當前百分比
			CreateAniRate(obj, "character/gunner/effect/animation/atkillpoint/finish/killpointfinishd_bullet_c.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), false, speedRate);//創建繪畫對象 射擊的掉落子彈
			break;
	}
}

function onKeyFrameFlag_atgunner_killpoint(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();//得到當前技能使用狀態
	switch(subState)
	{
		case 0:
			if(flagIndex == 1)
			{
				local count = obj.getVar().get_vector(0);//次數
				local skill_level = sq_GetSkillLevel(obj, SKILL_ATGUNNER_KILLPOINT);//技能等級
				local time = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 1, skill_level);//鎖住敵人的持續時間
				local reduceSpeedRate = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 4, skill_level) / -1;//無法鎖住的敵人移動速度減少率
				local bleedingLv = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 5, skill_level);//出血Lv
				local bleedingTime = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 6, skill_level);//出血時間
				local bleedingAtk = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 7, skill_level);//出血傷害
				local bleedingRate = obj.sq_GetLevelData(SKILL_ATGUNNER_KILLPOINT, 8, skill_level);//出血概率

				local direction = obj.getDirection();//得到方向
				local myXPos = obj.getXPos();//當前x坐標
				local myYPos = obj.getYPos();//當前y坐標
				local myZPos = obj.getZPos();//當前z坐標
				local xRange = 450;//距離450x
				local yRange = 100;//距離100y
				local zRange = 140;//距離140z

				local objectManager = obj.getObjectManager();//得到對象管理器
				local objectNumber = objectManager.getCollisionObjectNumber();//總數
				for(local i = 0; i < objectNumber; i++)
				{
					local object = objectManager.getCollisionObject(i);//得到控制類對象
					//不是敵人 不是活動類 攻擊不到 就繼續循環
					if(!obj.isEnemy(object) || !object.isObjectType(OBJECTTYPE_ACTIVE) || !object.isInDamagableState(obj)
					   || sq_GetCNRDObjectToActiveObject(object).isDead()) continue;

					local xPos = sq_GetXPos(object);//目標的x坐標
					//我的方向為左 他卻在我右邊，我的方向為右 他卻在我左邊。 則繼續循環
					if(direction == ENUM_DIRECTION_LEFT && xPos > myXPos
					   || direction == ENUM_DIRECTION_RIGHT && xPos < myXPos)continue;

					local yPos = sq_GetYPos(object);//目標的y坐標
					local zPos = sq_GetZPos(object);//目標的z坐標
					if(sq_Abs(myXPos - xPos) <= xRange
					   && sq_Abs(myYPos - yPos) <= yRange
					   && sq_Abs(myZPos - zPos) <= zRange)//在指定范圍內
					{
						if(count <= 0) break;
						else count -= 1;//減少次數
						local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_ATGUNNER_KILLPOINT, true, "character/atgunner/killpoint/ap_killpoint.nut", true);
						appendage.getVar().clear_vector();
						local apVar = appendage.getVar();//得到
						apVar.push_vector(bleedingLv);
						apVar.push_vector(bleedingTime);
						apVar.push_vector(bleedingAtk);
						apVar.push_vector(bleedingRate);
						apVar.push_vector(time);//持續時間
						if(sq_IsHoldable(obj, object))
						{
							sq_HoldAndDelayDie(object, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL, appendage);//控制并延時死亡
							apVar.setBool(0, true);//可以控制
						}
						else
						{
							sq_sendSetActiveStatusPacket(object, obj, ACTIVESTATUS_SLOW, 100.0, bleedingLv, false, time, 0, reduceSpeedRate);//減速異常
							apVar.setBool(0, false);//不可以控制
						}

					}
				}
			}
			break;
		case 1:
			if(flagIndex == 2)
			{
				obj.getVar("flag").clear_vector();
				obj.getVar("flag").push_vector(2);
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_ATGUNNER_KILLPOINTFINISHLASTSHOT);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_KILLPOINT, STATE_ATGUNNER_KILLPOINT, 3, 1.0);//最終射擊攻擊力
				obj.sq_SetCurrentAttackBonusRate(attackBonusRate);//設置當前百分比
			}

			local count = obj.getVar().size_vector();//多少個
			if(count > 0)
			{
				local objVar = obj.getVar();//得到
				for(local i = 0; i < count; i += 2)
				{
					local activeObj = sq_GetCNRDObjectToActiveObject(sq_GetObject(obj, objVar.get_vector(i), objVar.get_vector(i + 1)));//轉為活動類 
					if(activeObj && !activeObj.isDead())//為真 且 沒死亡
					{
						local isCreate = false;//判斷是否創建
						local height = sq_GetHeightObject(activeObj);//對象高度
						switch(flagIndex)
						{
							case 1:
								if(CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atgunner/killpoint/ap_killpoint.nut"))
								{
									height = height / 2 + sq_getRandom(0, (height * 0.25).tointeger());//當前高度
									if(obj.sq_IsMyControlObject()){
										obj.getVar("flag").clear_vector();
										obj.getVar("flag").push_vector(1);
										local particleCreater = obj.getVar("atgunner_killpoint").GetparticleCreaterMap("atgunner_killpoint", "character/gunner/particle/killpoint.ptl", obj);
										particleCreater.Restart(0);
										particleCreater.SetPos(sq_GetDistancePos(activeObj.getXPos(), obj.getDirection(),0),activeObj.getYPos(), sq_GetObjectHeight(activeObj)/2 + activeObj.getZPos() + 300);
										sq_AddParticleObject(obj, particleCreater);
									}
									isCreate = true;//確認創建
								}
								break;
							case 2:
								if(CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atgunner/killpoint/ap_killpoint.nut"))
									CNSquirrelAppendage.sq_RemoveAppendage(activeObj, "character/atgunner/killpoint/ap_killpoint.nut");//刪除ap
								break;
							case 3:
								if(obj.sq_IsMyControlObject()){
									local particleCreater = obj.getVar("atgunner_killpoint1").GetparticleCreaterMap("atgunner_killpoint1", "character/gunner/particle/killpoint.ptl", obj);
									particleCreater.Restart(0);
									particleCreater.SetPos(sq_GetDistancePos(activeObj.getXPos(), obj.getDirection(),0),activeObj.getYPos(), sq_GetObjectHeight(activeObj)/2 + activeObj.getZPos() + 300);
									sq_AddParticleObject(obj, particleCreater);
								}
								isCreate = true;//確認創建
								break;
						}
						if(!isCreate) continue;//為假不創建
						sq_SetMyShake(obj, 2, 100);//震動
						local angle = sq_ToRadian(sq_getRandom(0, 360).tofloat());
						local ani = sq_CreateAnimation("", "character/gunner/effect/animation/atkillpoint/hiteffect/killpointatkeff_b.ani");//創建ani
						sq_SetfRotateAngle(ani, angle);//旋轉角度
						local pAni = obj.sq_GetAutoLayerWorkAnimation(ani, "A");//得到als的ani
						if(pAni) sq_SetfRotateAngle(pAni, angle);//旋轉角度
						ani.addLayerAnimation(1, sq_CreateAnimation("", "character/gunner/effect/animation/atkillpoint/hiteffect/hiteffect_1.ani"), true);//增加層ani
						local sizeRate = sq_getRandom(20, 100).tofloat() / 100.0;
						ani.setImageRateFromOriginal(sizeRate, sizeRate);//增加ani 寬度跟高度率
						ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);//增加ani als附加 ani大小比例
						local pooledObj = sq_CreatePooledObject(ani, true);//創建繪畫對象 參數2：應該是ani結束時true 就銷毀反之false不銷毀
						sq_SetCurrentDirection(pooledObj, obj.getDirection());//設置方向
						pooledObj.setCurrentPos(sq_GetXPos(activeObj), sq_GetYPos(activeObj) + 1, sq_GetZPos(activeObj) + height);//設置pos
						pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);//設置圖層
						sq_AddObject(obj, pooledObj, OBJECTTYPE_DRAWONLY, false);//增加對象
					}
				}
			}
			break;
	}

	return true;
}

function onEndCurrentAni_atgunner_killpoint(obj)
{
	if(!obj) return;
	if(!obj.sq_IsMyControlObject()) return;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);//增加設置狀態數據包，設置為站立狀態
}

function onEndState_atgunner_killpoint(obj, new_state)
{
	if(!obj) return;
	if(new_state != STATE_ATGUNNER_KILLPOINT)
	{
		local count = obj.getVar().size_vector();//多少個
		if(count > 0)
		{
			local objVar = obj.getVar();//得到
			for(local i = 0; i < count; i += 2)
			{
				local targetObj = sq_GetObject(obj, objVar.get_vector(i), objVar.get_vector(i + 1));//得到對象
				if(!targetObj) continue;
				if(CNSquirrelAppendage.sq_IsAppendAppendage(targetObj, "character/atgunner/killpoint/ap_killpoint.nut"))
					CNSquirrelAppendage.sq_RemoveAppendage(targetObj, "character/atgunner/killpoint/ap_killpoint.nut");//刪除ap
			}
		}
	}
}

function onCreateObject_atgunner_killpoint(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	local substate = obj.getSkillSubState(); 
	if(state == STATE_ATGUNNER_KILLPOINT)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			if (substate == 1)
			{
				obj.getVar("atgunner_killpoint").push_obj_vector(Object);
				local overflag = obj.getVar("flag").get_vector(0);
				local objecttt = obj.getVar("atgunner_killpoint").is_obj_vector(Object);
				if (overflag == 2 && !objecttt)
				{
					obj.getVar("atgunner_killpoint1").push_obj_vector(Object);
				}
			}
		}
	}
}

function onProc_atgunner_killpoint(obj) {
	if (!obj) return;
	local subState = obj.getSkillSubState(); //得到當前技能使用狀態
	if (subState == 1)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("atgunner_killpoint").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 17);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_KILLPOINT, STATE_ATGUNNER_KILLPOINT, 2, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttacknUpForce(attackInfo, 10); 
				sq_SetCurrentAttacknBackForce(attackInfo, 3); 
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
		local overflag = obj.getVar("flag").get_vector(0);
		if (overflag == 2)
		{
			local Count = obj.getMyPassiveObjectCount(22001);
			for(local i=0;i<Count;++i)
			{
				local object = obj.getMyPassiveObject(22001, i);
				local objecttt = obj.getVar("atgunner_killpoint1").is_obj_vector(object);
				if(object && objecttt)
				{
					setCurrentAnimationFromCutomIndex(object, 17);
					local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_KILLPOINT, STATE_ATGUNNER_KILLPOINT, 3, 1.0);
					local attackInfo = sq_GetCurrentAttackInfo(object);
					sq_SetCurrentAttackeDamageAct(attackInfo, 2); 
					sq_SetCurrentAttacknUpForce(attackInfo, 300); 
					sq_SetCurrentAttacknBackForce(attackInfo, 300); 
					sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
				}
			}
		}
	}
}



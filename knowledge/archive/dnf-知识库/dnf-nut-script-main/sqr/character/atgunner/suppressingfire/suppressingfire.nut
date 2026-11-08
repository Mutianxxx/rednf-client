//事件：當玩家按下技能鍵時 檢查可執行技能文件
function checkExecutableSkill_atgunner_suppressingfire(obj) {
	if (!obj) return false; //當對象為null時返回假
	local IsUseSkill = obj.sq_IsUseSkill(236); //是否是可以使用的技能 而不是在冷卻或禁用
	if (IsUseSkill) //如果局部變量isUse為真
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); // substate
		obj.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); //發送狀態
		return true; //返回真
	}
	return false; //如果以上執行失敗則返回假
}

//事件：檢查是否啟用技能
function checkCommandEnable_atgunner_suppressingfire(obj) {
	if (!obj) return false; //如果對象為null返回假
	local state = obj.sq_GetState(); //得到對象的狀態賦值給局部變量state
	if (state == STATE_STAND) //如果狀態是站立或跳躍
	return true; //返回真
	if (state == STATE_ATTACK) //如果狀態等于攻擊
	{
		return obj.sq_IsCommandEnable(236);
	}
	return true; //返回真
}

// 事件：開始設置state 按下技能鍵時會第一進入此處
function onSetState_atgunner_suppressingfire(obj, state, datas, isResetTimer) {
	if (!obj) return; //如果對象為null則返回
	obj.sq_StopMove(); //對象停止移動
	local subState = obj.sq_GetVectorData(datas, 0); //得到傳過來的第0個值
	obj.setSkillSubState(subState); //設置當前技能狀態
	switch (subState) {
	case 0:
		//初始準備動作
		obj.getVar().clear_vector();
		obj.sq_SetCurrentAnimation(115); //設置人物ani
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); //吃攻速
		break;
	case 1:
		//循環射擊動作
		obj.sq_SetCurrentAnimation(116); //設置人物ani
		obj.sq_SetCurrentAttackInfo(26); //循環攻擊
		
		local particleCreater = obj.getVar("atgunner_suppressingfire").GetparticleCreaterMap("atgunner_suppressingfire", "character/gunner/particle/deadlyapproach.ptl", obj);
		particleCreater.Restart(0);
		particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
		sq_AddParticleObject(obj, particleCreater);

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(236, 236, 0, 1.0); //前方亂射攻擊力
		obj.sq_SetCurrentAttackBonusRate(attackBonusRate); //設置百分比攻擊
		local skill_level = sq_GetSkillLevel(obj, 236); //技能等級
		local maxAtkTime = obj.sq_GetLevelData(236, 3, skill_level); //最大射擊間隔
		obj.getVar().clear_timer_vector();
		obj.getVar().push_timer_vector();
		local t = obj.getVar().get_timer_vector(0);
		t.setParameter(maxAtkTime, -1); //攻擊間隔
		t.resetInstant(0);
		local time = obj.sq_GetLevelData(236, 2, skill_level); //總射擊時間
		local minAtkTime = obj.sq_GetLevelData(236, 4, skill_level); //最小射擊間隔
		local maxAniSpeed = 280; //最大播放速度
		local minAniSpeed = 100; //最小播放速度
		local maxCount = 3; //最大上限按鍵次數
		local cCount = 0; //當前按鍵次數

		obj.getVar().clear_vector();
		local objVar = obj.getVar(); //得到
		objVar.push_vector(time);
		objVar.push_vector(maxAtkTime);
		objVar.push_vector(minAtkTime);
		objVar.push_vector(maxAniSpeed);
		objVar.push_vector(minAniSpeed);
		objVar.push_vector(maxCount);
		objVar.push_vector(cCount);
		
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_ATGUNNER_SUPPRESSINGFIRE, false, "character/gunner/suppressingfire/ap_suppressingfire.nut", true);
		//appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_GUNNER_SUPPRESSINGFIRE, -1);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 238, true);
		break;
	case 2:
		//結束并最后一擊
		obj.sq_SetCurrentAnimation(117); //設置人物ani
		sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/atsuppressingfire/03_finish/dust/suppressingfire_finish_dust01.ani", 0, 0, 0); //灰塵
		sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/atsuppressingfire/03_finish/front/suppressingfire_finish_front.ani", 0, 30, 0); //射擊效果
		break;
	}
}


function onProc_atgunner_suppressingfire(obj) {
	if (!obj) return;
	local subState = obj.getSkillSubState(); //得到當前技能使用狀態
	if (subState == 1)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("atgunner_suppressingfire").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 4);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_SUPPRESSINGFIRE, SKILL_ATGUNNER_SUPPRESSINGFIRE, 0, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttacknUpForce(attackInfo, 10); 
				sq_SetCurrentAttacknBackForce(attackInfo, 3); 
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
		local t = obj.getVar().get_timer_vector(0);
		if (t)
		{
		if (t.isOnEvent(obj.sq_GetStateTimer()) == true)
			{
				local particleCreater = obj.getVar("atgunner_suppressingfire").GetparticleCreaterMap("atgunner_suppressingfire", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
				sq_AddParticleObject(obj, particleCreater);
			}
		}
	}
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	if (subState == 2 && frmIndex > 4)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("atgunner_suppressingfire1").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 5);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ATGUNNER_SUPPRESSINGFIRE, SKILL_ATGUNNER_SUPPRESSINGFIRE, 1, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttackeDamageAct(attackInfo, 2); 
				sq_SetCurrentAttacknUpForce(attackInfo, 300); 
				sq_SetCurrentAttacknBackForce(attackInfo, 300); 
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
	}
}

function onCreateObject_atgunner_suppressingfire(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	local substate = obj.getSkillSubState(); 
	if(state == STATE_ATGUNNER_SUPPRESSINGFIRE)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			if (substate == 1)
			{
				obj.getVar("atgunner_suppressingfire").push_obj_vector(Object);
			}
			local objecttt = obj.getVar("atgunner_suppressingfire").is_obj_vector(Object);
			if (substate == 2 && !objecttt)
			{
				obj.getVar("atgunner_suppressingfire1").push_obj_vector(Object);
			}
		}
	}
}

function onKeyFrameFlag_atgunner_suppressingfire(obj, flagIndex)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 2:
		if(flagIndex == 1)
		{
			local particleCreater = obj.getVar("atgunner_suppressingfire1").GetparticleCreaterMap("atgunner_suppressingfire1", "character/gunner/particle/deadlyapproach.ptl", obj);
			particleCreater.Restart(0);
			particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
			sq_AddParticleObject(obj, particleCreater);
			sq_SetMyShake(obj, 5, 200); 
		}
		break;
	}
	return true;
}

//被動
function onProcCon_atgunner_suppressingfire(obj) {
	if (!obj) return;
	local subState = obj.getSkillSubState(); //得到當前技能使用狀態
	if (subState == 1) {
		local objVar = obj.getVar(); //得到
		//狀態時間 大于等于 總時間則進入下一個狀態
		if (obj.sq_GetStateTimer() >= objVar.get_vector(0)) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2); // substate
			obj.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); //發送狀態
			return;
		}
		sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true); //設置其他按鍵
		if (sq_IsEnterCommand(obj, E_JUMP_COMMAND)) //確認按下
		{
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); //增加設置狀態數據包，設置為站立狀態
			return;
		}
		sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true); //設置其他按鍵
		obj.setSkillCommandEnable(236, true); //激活技能使圖標變亮
		if (sq_IsEnterCommand(obj, E_ATTACK_COMMAND) || obj.sq_IsEnterSkill(236) != -1) {
			local cCount = objVar.get_vector(6); //當前按鍵次數
			local maxCount = objVar.get_vector(5); //限制次數
			if (cCount < maxCount) //次數小于最大次數
			{
				cCount += 1; //增加次數
				objVar.set_vector(6, cCount); //改變當前次數
				local cAtkTime = sq_GetUniformVelocity(objVar.get_vector(1), objVar.get_vector(2), cCount, maxCount); //計算出當前的攻擊間隔
				local cAniSpeed = sq_GetUniformVelocity(objVar.get_vector(4), objVar.get_vector(3), cCount, maxCount); //計算出當前的ani速度

				//傳遞給當前狀態的效果包
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(cAtkTime);
				sq_BinaryWriteDword(cAniSpeed);
				sq_SendChangeSkillEffectPacket(obj, 236); //發送
			}
		}
	}
}

function onChangeSkillEffect_atgunner_suppressingfire(obj, skillIndex, reciveData) {
	if (!obj) return;
	if (skillIndex != 236) return;
	local subState = obj.getSkillSubState();
	if (subState == 1) {
		local cAtkTime = reciveData.readDword(); //攻擊間隔
		local cAniSpeed = (reciveData.readDword()).tofloat() / 100.0; //ani速度
		local t = obj.getVar().get_timer_vector(0); //得到重置攻擊時鐘
		if (t) t.setEventTerm(cAtkTime); //設置間隔
		obj.sq_SetStaticSpeedInfo(0, 0, SPEED_VALUE_DEFAULT, (SPEED_VALUE_DEFAULT * cAniSpeed).tointeger(), 1.0, 1.0); //設置固定速度
	}
}

//事件：結束施放ani時
function onEndState_atgunner_suppressingfire(obj, new_state)
{
	local state = obj.sq_GetState();
	local SubState0 = obj.getVar("substate").get_vector(0);
	local SubState1 = obj.getVar("substate").get_vector(1);
	local SubState2 = obj.getVar("substate").get_vector(2);
	if (new_state != SKILL_ATGUNNER_SUPPRESSINGFIRE)
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/suppressingfire/ap_suppressingfire.nut");
		removeAni(obj);
	}
}

function onEndCurrentAni_atgunner_suppressingfire(obj) {
	if (!obj) return;
	if (!obj.sq_IsMyControlObject()) return;
	local subState = obj.getSkillSubState(); //得到技能使用的狀態
	if (subState != 2) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(subState + 1); // substate
		obj.sq_AddSetStatePacket(236, STATE_PRIORITY_USER, true); //發送狀態
	}
	else obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); //增加設置狀態數據包，設置為站立狀態
}

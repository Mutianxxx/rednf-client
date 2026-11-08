OPTION_HOTKEY_QUICK_SKILL7		<- 66	//ÛâÏó??
OPTION_HOTKEY_EXSKILL7			<- 93	//ÛâÏó??

function newSkillKeyDown(obj)
{
	if(!obj) return;
	if(CFG_FUNC_NUTNEWSKILLSLOT < 1){
		return;
	}
	if(!obj.isMyControlObject()) return;
	if(!sq_IsMyCharacter(obj)) return;
	local allstate = obj.sq_GetState();
	if(allstate == 3||allstate == 4||allstate == 5||allstate == 9)
		return;
	if (!sq_IsInBattle() || sq_IsPauseTypeWorld(obj)) return;
	
	if(sq_IsKeyDown(OPTION_HOTKEY_QUICK_SKILL7 , ENUM_SUBKEY_TYPE_ALL))
	{
		if(obj.getVar("altKey").getBool(0)==false){
			isUseSkill_New_95(obj);//AltÛâÏó??
			obj.getVar("altKey").setBool(0,true);
		}
	}
	else{
		obj.getVar("altKey").setBool(0, false);
	}
	
		
	if(sq_IsKeyDown(OPTION_HOTKEY_EXSKILL7 , ENUM_SUBKEY_TYPE_ALL))
	{
		if(obj.getVar("ctrlKey").getBool(0)==false){
			isUseSkill_New_100(obj);//CtrlÛâÏó??
			obj.getVar("ctrlKey").setBool(0,true);
		}
	}
	else{
		obj.getVar("ctrlKey").setBool(0, false);
	}

}

function isUseSkill_New_100(obj) //CtrlÛâÏó??
{
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_SWORDMAN) //??£º???
	{
		if (sq_getGrowType(obj) == 0) {
			shiftCommonForce(obj, 130, 126, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 1) //??1£º??
		{
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/swordman/handlingsword/ap_handlingsword_buff.nut")) {
				onEndRangeAttack_appendage_swordman_handlingsword_buff(obj);
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/swordman/handlingsword/ap_handlingsword_buff.nut");
				return;
			}
			shiftCommon(obj, 246, 246, [-1]);
			return;
		}
		if (sq_getGrowType(obj) == 2) //??2£º??
		{

			local skill = sq_GetSkill(obj, 241);
			if (skill && skill.isSealFunction()) {
				shiftCommon(obj, 241, 241, [0]);
			} else if (skill && !skill.isSealFunction()) {
				shiftCommon(obj, 241, 241, [1]);
			}
			return;
		}
		if (sq_getGrowType(obj) == 3) //??3£º??
		{
			shiftCommon(obj, 231, 231, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 4) //??4£º?Úµ     ?????????
		{
			shiftCommon(obj, 244, 244, [-1]);
			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_FIGHTER) //??£º???
	{
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 228, 228, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 232, 232, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			shiftCommon(obj, 236, 236, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			shiftCommon(obj, 239, 239, [0]);
			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_GUNNER) //??£º??
	{
		if (sq_getGrowType(obj) == 0) {
			shiftCommon(obj, 133, 228, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 240, 240, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 235, 235, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			shiftCommon(obj, 247, 247, [-1]);
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			shiftCommon(obj, 245, 245, [-1]);
			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_MAGE) //??£º??
	{
		if (sq_getGrowType(obj) == 0) {
			shiftCommonUserSubState(obj, 213, 227, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 253, 253, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			local ramosobj = getMyMonsterObject_Character_jsqq506807329(obj, 50680732, "character/mage/summonramos/ap_summonramos.nut");
			if (ramosobj) {
				if (ramosobj.getState() == STATE_ATTACK && ramosobj.getAttackIndex() >= 11) {
					if (obj.isMessage()) sq_AddMessage(414);
					obj.sq_PlaySound("WZ_NOMANA");
					return;
				}
				local ramosapp = CNSquirrelAppendage.sq_GetAppendage(ramosobj, "character/mage/summonramos/ap_summonramos.nut");
				if (!ramosapp) return;
				local ramossqr = ramosapp.getVar("sqrChrSkill").get_timer_vector(3);
				if (!ramossqr || ramossqr.isOnEvent(ramosapp.getTimer().Get()) != true) {
					obj.startCantUseSkillWarning();
					if (obj.isMessage()) sq_AddMessage(414);
					obj.sq_PlaySound("WZ_NOMANA");
					return;
				}
				local ldata = sq_GetLevelData(obj, 139, 15, sq_GetSkillLevel(obj, 139));
				if (ramossqr.getEventTerm() != ldata) ramossqr.setEventTerm(ldata);
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1);
				obj.sq_IntVectPush(sq_GetGroup(ramosobj));
				obj.sq_IntVectPush(sq_GetUniqueId(ramosobj));
				obj.sq_AddSetStatePacket(139, STATE_PRIORITY_USER, true);
				return;
			} else {
				shiftCommon(obj, 139, 139, [0]);
				return;
			}
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			local avatarapd = CNSquirrelAppendage.sq_GetAppendage(obj, "character/mage/avatar/ap_avatar.nut");
			if (avatarapd && avatarapd.isValid()) {
				if (avatarapd.getVar("skill").getBool(0) == false) {
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(1);
					obj.sq_AddSetStatePacket(245, STATE_PRIORITY_USER, true);
					return;
				}

			} else {
				if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_bellatrix.nut")) {
					shiftCommon(obj, 245, 32, [0, 0]);
				} else {
					shiftCommon(obj, 245, 245, [0]);
				}
				return;
			}
		}
		if (sq_getGrowType(obj) == 4) {
			shiftCommon(obj, 134, 134, [0]);
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_PRIEST) //??£º???
	{
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 251, 251, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 245, 245, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofcalmness.nut") &&
				!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofpassion.nut"))
				return;
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofcalmness.nut")) {
				shiftCommon(obj, 241, 241, [0, 1]);
				return;
			} else {
				shiftCommon(obj, 241, 241, [1]);
				return;
			}
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			if (isAvengerAwakenning(obj) == true) {
				shiftCommon(obj, 138, 138, [0, 1]);
			} else {
				shiftCommon(obj, 138, 138, [0, 0]);
			}

			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_GUNNER) //??£º??
	{
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 239, 239, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 235, 235, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			shiftCommon(obj, 249, 249, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			local zPos = obj.getZPos();
			local state = obj.getState();
			if (zPos > 50 || state == 6 || state == 7) {
				shiftCommon(obj, 244, 244, [1]);
			} else {
				shiftCommon(obj, 244, 244, [0]);
			}
			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_THIEF) //??£º??
	{
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 222, 222, [1]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 225, 225, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut")) {
				obj.sq_StartWrite();
				obj.sq_WriteDword(63);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
			} else {
				shiftCommon(obj, 100, 119, [0]);
			}
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/shadowsoul/ap_shadowsoul.nut"))
			{
		
				local isUseSkill = obj.sq_IsUseSkill(247);
				if (isUseSkill) 
				{
					local pIntVec = sq_GetGlobalIntVector();
					sq_IntVectorClear(pIntVec);
					sq_IntVectorPush(pIntVec, 0);			
					obj.addSetStatePacket(247 , pIntVec,  STATE_PRIORITY_USER, false, "");
		
					return true;
				}
				return false;
			}else
			{
				local apd = obj.GetSquirrelAppendage("character/thief/4_shadow/shadowsoul/ap_shadowsoul.nut");
				if (apd)
				{
					local curApdT = apd.getTimer().Get();
				
					local ski1EncodeT = apd.getVar("CoolTimeSkill").get_vector(0);
					local ski1CoolTime = obj.sq_GetIntData(247, 0);
					
					if (curApdT - ski1EncodeT < ski1CoolTime)
						return ;
					
					apd.getVar("CoolTimeSkill").set_vector(0,curApdT);
					
				}
				
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);			
				obj.addSetStatePacket(247 , pIntVec,  STATE_PRIORITY_USER, false, "");
				return ;
			}
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_FIGHTER) //??£º???
	{
		if (sq_getGrowType(obj) == 1) {
			shiftCommon(obj, 222, 222, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 2) {
			shiftCommon(obj, 225, 225, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 3) {
			shiftCommon(obj, 228, 228, [0]);
			return;
		}
		if (sq_getGrowType(obj) == 4) {
			if (obj.sq_GetState() != 6)
				return;
			shiftCommon(obj, 231, 231, [0]);
			return;
		}
	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_MAGE) //??£º??
	{
		local growType = sq_getGrowType(obj);
		switch (growType) {
			case 0:
				shiftCommon(obj, 124, 124, [0]);
				break;
			case 1:
				shiftCommon(obj, 245, 245, [0]);
				break;
			case 2:
				shiftCommon(obj, 248, 248, [0]);
				break;
			case 3:
				shiftCommon(obj, 95, 95, [0]);
				break;
			case 4:
				local objstate = obj.sq_GetState();
				if (objstate == 121 || objstate == 3 || objstate == 4 || objstate == 5 || objstate == 9)
					return;
				if (sq_GetSkillLevel(obj, 121) < 1)
					return;
				if (obj.sq_IsUseSkill(121)) {
					obj.sq_IntVectClear();
					obj.getVar("state").clear_vector();
					obj.getVar("state").push_vector(0);
					obj.sq_AddSetStatePacket(121, STATE_PRIORITY_IGNORE_FORCE, false);
				}
				break;
		}

	} else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_PRIEST) //??£º?ì¾
	{
		local growType = sq_getGrowType(obj);
		switch (growType) {
			case 1:
				shiftCommonRootSubState(obj, 113, 230, [0]);
				break;
			case 2:
				local objstate = obj.sq_GetState();
				if (objstate == 136 || objstate == 3 || objstate == 4 || objstate == 5 || objstate == 9)
					break;
				if (sq_GetSkillLevel(obj, 136) < 1)
					break;
				if (obj.sq_IsUseSkill(136)) {
					obj.getVar("atlastgenesis_finish1_ball").clear_obj_vector();
					obj.getVar("atlastgenesis").clear_obj_vector();
					obj.getVar("damaLastGenesis").clear_obj_vector();
					obj.getVar("atlastgenesisatt1").clear_obj_vector();
					local pIntVec = sq_GetGlobalIntVector();
					sq_IntVectorClear(pIntVec);
					sq_IntVectorPush(pIntVec, 0);
					obj.addSetStatePacket(136, pIntVec, STATE_PRIORITY_FORCE, false, "");
				}
				break;
			case 3:
				shiftCommonForce(obj, 249, 249, [10]);
				break;
			case 4:
				shiftCommonEasy(obj, 164, 164);
				break;
		}
	} else if (sq_getJob(obj) == 10) {
		local growType = sq_getGrowType(obj);
		switch (growType) {
			case 0:
				if (obj.sq_IsCommandEnable(234)) {
					shiftCommon(obj, 234, 234, [0]);
				}
				break;
			case 1:
				shiftCommon(obj, 141, 141, [0]);
				break;
			case 2:
				shiftCommon(obj, 226, 226, [0]);
				break;
			case 3:
				obj.getVar("Ragnarok").clear_vector();
				obj.getVar("Ragnarok").push_vector(obj.getXPos());
				obj.getVar("Ragnarok").push_vector(obj.getYPos());
				local rk = obj.getVar("Ragnarok");
				local mfc = sq_flashScreen(obj, 150, 10500, 300, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				rk.setObject(0, mfc);
				shiftCommon(obj, 166, 166, [0]);
				break;
			case 4:
				shiftCommon(obj, 81, 81, [0]);
				break;
		}
	}

}

function isUseSkill_New_95(obj)//Alt??
{
	if (sq_getJob(obj) == ENUM_CHARACTERJOB_SWORDMAN)//??£º???
	{
		if(sq_getGrowType(obj) == 0)
		{
			shiftCommonForce(obj,48,123,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 1)
		{
			shiftCommon(obj,86,47,[obj.getDirection()]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			shiftCommon(obj,87,50,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			if(obj.getVar("nsk1st").getBool(0) == true){
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(46, STATE_PRIORITY_USER, true);
				obj.getVar("nsk1st").setBool(0,false);
			}
			if(obj.sq_GetState() == 13)
				return;
			if(sq_GetSkillLevel(obj, 85)<1)
				return;
			if(obj.sq_IsUseSkill(85))
			{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(0);
					obj.sq_IntVectPush(0);
					obj.sq_IntVectPush(85);
					obj.sq_IntVectPush(600);
					obj.sq_IntVectPush(400);
					obj.sq_IntVectPush(1);
					obj.sq_IntVectPush(3);
					obj.sq_IntVectPush(3);
					obj.sq_AddSetStatePacket(13, STATE_PRIORITY_USER, true);
					obj.getVar("nsk1st").setBool(0,true);
					return;
			}
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommon(obj,88,51,[0]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_FIGHTER)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{
			shiftCommon(obj,227,227,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			shiftCommon(obj,71,61,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			shiftCommon(obj,235,235,[-1]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommon(obj,63,22,[63]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_GUNNER)//??£º??
	{
		if(sq_getGrowType(obj) == 0)
		{
			shiftCommon(obj,118,227,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 1)
		{
			if(obj.getWeaponSubType() != 0) {
 				obj.startCantUseSkillWarning();
 				if (obj.isMessage())
 					sq_AddMessage(3587); 
 				return;
			}
			shiftCommon(obj,64,33,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			shiftCommon(obj,54,13,[0,0,54,600,600,1,3,3]);
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			shiftCommon(obj,67,34,[-1]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			local blackrose = obj.getMyPassiveObject(22229, 0);
			if(!blackrose){
				shiftCommon(obj,70,13,[0,0,70,700,700,1,3,3]);
				obj.getVar("nsk1st").setBool(0,true);
			}
			else if(obj.getVar("nsk1st").getBool(0) == true && blackrose){
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(35, STATE_PRIORITY_USER, true);
				obj.getVar("nsk1st").setBool(0,false);
			}
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_MAGE)//??£º??
	{
		if(sq_getGrowType(obj) == 0)
		{
			 if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_mage/doll/ap_doll.nut")){
				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(3);
				obj.sq_AddSetStatePacket(217, STATE_PRIORITY_USER, true);
			 }
			 else{
			 	shiftCommonUserSubState(obj,147,217,[0]);
			 }
			return;
		}
		if(sq_getGrowType(obj) == 1)
		{
			shiftCommon(obj,252,252,[-1]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			
			local objman = obj.getObjectManager(); 
			for(local i = 0; i < objman.getCollisionObjectNumber(); i++)
			{
				local monobj = objman.getCollisionObject(i); 
				if(monobj && monobj.isObjectType(OBJECTTYPE_MONSTER) && !obj.isEnemy(monobj) && monobj.getCollisionObjectIndex() == 60024) 
				{
					local actobj = sq_GetCNRDObjectToActiveObject(monobj); 
					if(actobj && !actobj.isDead()) 
					{
						if(obj.getVar("nsk1st").getBool(0) == true){
							obj.sq_IntVectClear();
							obj.sq_IntVectPush(obj.getDirection());
							obj.sq_AddSetStatePacket(30, STATE_PRIORITY_USER, true);
							obj.getVar("nsk1st").setBool(0,false);
						}
						return;
					}
				}
			}

			if(obj.sq_GetState() == 13)
				return;
			if(sq_GetSkillLevel(obj, 82)<1)
				return;
			if(obj.sq_IsUseSkill(82))
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0);
				obj.sq_IntVectPush(0);
				obj.sq_IntVectPush(82);
				obj.sq_IntVectPush(810);
				obj.sq_IntVectPush(0);
				obj.sq_IntVectPush(2);
				obj.sq_IntVectPush(4);
				obj.sq_IntVectPush(4);
				obj.sq_AddSetStatePacket(13, STATE_PRIORITY_USER, true);
				obj.getVar("nsk1st").setBool(0,true);
				return;
			}
			return;

		}
		if(sq_getGrowType(obj) == 3)
		{
			 local avatarstate = 0; 
 			if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/appendage/ap_bellatrix.nut")) 
 				avatarstate = 1;
 			else if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut")) 
 				avatarstate = 2;
			shiftCommon(obj,247,247,[avatarstate]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommon(obj,109,45,[0]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_PRIEST)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{
			shiftCommon(obj,84,47,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			local skill = sq_GetSkill(obj, 90);
			local oldstate = obj.sq_GetState();
			local dryoutapd = obj.GetSquirrelAppendage("character/new_priest/lanquan/dryout/ap_dryout.nut");
			if(dryoutapd){
				if ( !skill.isSealFunction())
				{
					SetStateDryOut(obj, 90, 50, oldstate, [4, 1]);
				}
				else if (skill.isSealFunction())
				{
					SetStateDryOut(obj, 90, 50, oldstate, [0]);
				}
				return true;
			}
			else
			{
				if ( !skill.isSealFunction())
				{
					shiftCommon(obj,90,50,[4, 1]);
				}
				else if (skill.isSealFunction())
				{
					shiftCommon(obj,90,50,[0]);
				}
			}
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofcalmness.nut")
				&& !CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofpassion.nut"))
				return;
			if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/appendage/ap_buff_chakraofcalmness.nut")){
				shiftCommon(obj,93,51,[0,1]);
				return;
			}
			else{
				shiftCommon(obj,93,51,[0,0]);
				return;
			}
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			if(isAvengerAwakenning(obj) == true)
			{
				
				local appendage = obj.GetSquirrelAppendage("Appendage/Character/ap_avenger_awakening.nut");
				appendage.sq_var.set_vector(0, 0);
			}
			else
			{
				if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/metamorphosis/ap_metamorphosis.nut")) 
				{
					shiftCommon(obj,119,67,[7]);
				}
				else
				{
					shiftCommon(obj,119,67,[0]);
				}
			}
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_GUNNER)//??£º??
	{

		
		if(sq_getGrowType(obj) == 1)
		{
			local skill = sq_GetSkill(obj, 64);
			local seal = false;
			if(skill){
				if(obj.sq_GetSkillLevel(64)<1)
				{
					return;
				}
				seal = !skill.isSealFunction();
			}
			if(obj.getVar("nsk1st").getBool(0) == true){
				if(seal)
				{
					obj.getVar("nsk1st").setBool(0,false);
				}
				else
				{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(0);
					obj.sq_AddSetStatePacket(55, STATE_PRIORITY_USER, true);
					obj.getVar("nsk1st").setBool(0,false);
				}
			}

			if(obj.sq_GetState() == 45)
				return;
			if(sq_GetSkillLevel(obj, 100)<1)
				return;
			if(obj.sq_IsUseSkill(100))
			{
					obj.sq_IntVectClear();
					obj.sq_AddSetStatePacket(45, STATE_PRIORITY_USER, true);
					obj.getVar("nsk1st").setBool(0,true);
					return;
			}
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			shiftCommon(obj,97,44,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			shiftCommon(obj,96,43,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommon(obj,98,13,[0,0,98,300,500,1,4,4]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_THIEF)//??£º??
	{
		if(sq_getGrowType(obj) == 1)
		{
			if(obj.getVar("nsk1st").getBool(0) == true){
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(92);
				obj.sq_AddSetStatePacket(45, STATE_PRIORITY_USER, true);
				obj.getVar("nsk1st").setBool(0,false);
			}

			if(obj.sq_GetState() == 45)
				return;
			if(sq_GetSkillLevel(obj, 57)<1)
				return;
			if(obj.sq_IsUseSkill(57))
			{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(91);
					obj.sq_AddSetStatePacket(45, STATE_PRIORITY_USER, true);
					obj.getVar("nsk1st").setBool(0,true);
					return;
			}
			return;
			shiftCommon(obj,57,45,[91]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			shiftCommon(obj,59,63,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			shiftCommon(obj,103,114,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommonUserSubState(obj,243,243,[0]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_FIGHTER)//??£º???
	{
		if(sq_getGrowType(obj) == 1)
		{
			shiftCommon(obj,67,45,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 2)
		{
			//shiftCommon(obj,41,62,[-1]);
			//return;
			if(obj.getVar("nsk1st").getBool(0) == true){
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(248, STATE_PRIORITY_USER, true);
				obj.getVar("nsk1st").setBool(0,false);
			}

			if(obj.sq_GetState() == 62)
				return;
			if(sq_GetSkillLevel(obj, 41)<1)
				return;
			if(obj.sq_IsUseSkill(41))
			{
					obj.sq_IntVectClear();
					obj.sq_AddSetStatePacket(62, STATE_PRIORITY_USER, true);
					obj.getVar("nsk1st").setBool(0,true);
					return;
			}
			return;
		}
		if(sq_getGrowType(obj) == 3)
		{
			shiftCommon(obj,105,60,[0]);
			return;
		}
		if(sq_getGrowType(obj) == 4)
		{
			shiftCommon(obj,63,22,[63]);
			return;
		}
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_MAGE)//??£º??
	{
		
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 0:
				local objstate = obj.sq_GetState();
				if(objstate == 126||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
					return;
				if(sq_GetSkillLevel(obj, 126)<1)
					return;
				if(obj.sq_IsUseSkill(126))
				{
        				obj.sq_AddSetStatePacket(126, STATE_PRIORITY_USER, true);
				}
			break;
			case 1:
				shiftCommon(obj,49,54,[0,0]);
			break;
			case 2:
				shiftCommon(obj,48,53,[0]);
			break;
			case 3:
				shiftCommon(obj,103,103,[4]);
			break;
			case 4:
				local objstate = obj.sq_GetState();
				if(objstate == 109||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
					return;
				if(sq_GetSkillLevel(obj, 109)<1)
					return;
				if(obj.sq_IsUseSkill(109))
				{
					obj.sq_IntVectClear();
					obj.getVar("state").clear_vector();
        				obj.getVar("state").push_vector(0);
        				obj.sq_AddSetStatePacket(109, STATE_PRIORITY_IGNORE_FORCE, false);
				}
			break;
		}
		
	}
	else if (sq_getJob(obj) == ENUM_CHARACTERJOB_AT_PRIEST)//??£º?ì¾
	{
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 1:
				obj.getVar("CruxOfVictoria").clear_vector();
				obj.getVar("CruxOfVictoria").push_vector(obj.getXPos());
				obj.getVar("CruxOfVictoria").push_vector(obj.getYPos());
				obj.getVar("CruxOfVictoria").push_vector(obj.getZPos());
				shiftCommonForce(obj,151,151,[0]);
			break;
			case 2:
				shiftCommonRootSubState(obj,134,134,[0]);
			break;
			case 3:
				shiftCommonForce(obj,244,244,[0]);
			break;
			case 4:
				shiftCommonEasy(obj,250,250);
			break;
		}
	}
	else if (sq_getJob(obj) == 10)
	{
		local growType = sq_getGrowType(obj);
		 switch(growType)
		{
			case 0:
				shiftCommon(obj,246,246,[0]);
			break;
			case 1:
				shiftCommon(obj,142,142,[0]);
			break;
			case 2:
				shiftCommon(obj,221,221,[0]);
			break;
			case 3:
				shiftCommon(obj,160,160,[0]);
			break;
			case 4:
				shiftCommon(obj,74,74,[0]);
			break;
		}
	}
}

function shiftCommon(obj,skillId,state,Arr)
{
	local objstate = obj.sq_GetState();
	if(objstate == state||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
		return;
	if(sq_GetSkillLevel(obj, skillId)<1)
		return;
	if(obj.sq_IsUseSkill(skillId))
	{
		obj.sq_IntVectClear();
		if(Arr[0]<0)
		{
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
		}
		else
		{
			foreach(sub in Arr)
				obj.sq_IntVectPush(sub);
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
		}

	}
	return;
}

function shiftCommonForce(obj,skillId,state,Arr)
{
	local objstate = obj.sq_GetState();
	if(objstate == state||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
		return;
	if(sq_GetSkillLevel(obj, skillId)<1)
		return;
	if(obj.sq_IsUseSkill(skillId))
	{
		obj.sq_IntVectClear();
		if(Arr[0]<0)
		{
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		else
		{
			foreach(sub in Arr)
				obj.sq_IntVectPush(sub);
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_IGNORE_FORCE, true);
		}

	}
	return;
}

function shiftCommonUserSubState(obj,skillId,state,Arr)
{
	local objstate = obj.sq_GetState();
	if(objstate == state||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
		return;
	if(sq_GetSkillLevel(obj, skillId)<1)
		return;
	if(obj.sq_IsUseSkill(skillId))
	{
		
		obj.getVar("state").clear_vector();
		if(Arr[0]<0)
		{
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
		}
		else
		{
			foreach(sub in Arr)
				obj.getVar("state").push_vector(sub);
			obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
		}

	}
	return;
}

function shiftCommonRootSubState(obj,skillId,state,Arr)
{
	local objstate = obj.sq_GetState();
	if(objstate == state||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
		return;
	if(sq_GetSkillLevel(obj, skillId)<1)
		return;
	if(obj.sq_IsUseSkill(skillId))
	{
		
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		if(Arr[0]<0)
		{
			obj.addSetStatePacket(state , pIntVec, STATE_PRIORITY_FORCE, false, "");
		}
		else
		{
			foreach(sub in Arr)
				sq_IntVectorPush(pIntVec, sub);
			obj.addSetStatePacket(state , pIntVec, STATE_PRIORITY_FORCE, false, "");
		}
	}
	return;
}

function shiftCommonEasy(obj,skillId,state)
{
	local objstate = obj.sq_GetState();
	if(objstate == state||objstate == 3||objstate == 4||objstate == 5||objstate == 9)
		return;
	if(sq_GetSkillLevel(obj, skillId)<1)
		return;
	if(obj.sq_IsUseSkill(skillId))
	{
		obj.getVar().clear_vector();
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		obj.addSetStatePacket(state, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
	return;
}
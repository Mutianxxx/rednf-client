

function onAttack_Attack(obj, damager, boundingBox, isStuck) {
	if (!obj.isMyControlObject())
		return false;
	local appendage2 = obj.GetSquirrelAppendage("character/atmage/attack/ap_bloodoath.nut");
	if (appendage2) {
		local attackIndex = obj.getAttackIndex();
		if (obj.getVar("flag").get_vector(0) == 0) {
			obj.getVar("flag").clear_vector();
			obj.getVar("flag").push_vector(1);
		}
		damager = sq_GetCNRDObjectToActiveObject(damager);
		if (attackIndex == 0) {
			//setCustomHitEffectBloodMageCut(obj,damager,67);
			local ania = sq_AddDrawOnlyAniFromParent(damager, "passiveobject/zrr_skill/atmage/animation/hiteffect/bloodslashsmall1.ani", 0, 1, damager.getObjectHeight() / 2);
			sq_moveWithParent(damager, ania);
			if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/append_bloodmage/ap_attack_1.nut") &&
				!CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_dieeffect.nut") &&
				!damager.isDead()) {

				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_1.nut", true);
			} else {
				return false;
			}
			if (obj) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_1_characater.nut", true);

			}

		} else if (attackIndex == 1) {
			local anib = sq_AddDrawOnlyAniFromParent(damager, "passiveobject/zrr_skill/atmage/animation/hiteffect/bloodslashsmall2.ani", 0, 1, damager.getObjectHeight() / 2);
			sq_moveWithParent(damager, anib);

			if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_attack_2.nut") &&
				!CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_dieeffect.nut") &&
				!damager.isDead()) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_2.nut", true);

			} else {
				return false;
			}

			if (obj) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_2_character.nut", true);
			}
		} else if (attackIndex == 2) {
			local anic = sq_AddDrawOnlyAniFromParent(damager, "passiveobject/zrr_skill/atmage/animation/hiteffect/bloodslashsmall3.ani", 0, 1, damager.getObjectHeight() / 2);
			sq_moveWithParent(damager, anic);

			if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_attack_3.nut") &&
				!CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_dieeffect.nut") &&
				!damager.isDead()) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_3.nut", true);
			} else {
				return false;
			}
			if (obj) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_3_character.nut", true);
			}
		} else if (attackIndex == 3) {
			local anid = sq_AddDrawOnlyAniFromParent(damager, "passiveobject/zrr_skill/atmage/animation/hiteffect/bloodslashlarge1.ani", 0, 1, damager.getObjectHeight() / 2);
			sq_moveWithParent(damager, anid);
			if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_attack_4.nut") &&
				!CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atmage/append_bloodmage/ap_dieeffect.nut") &&
				!damager.isDead()) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_4.nut", true);
			} else {
				return false;
			}
			if (obj) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODOATH, false,
					"character/atmage/append_bloodmage/ap_attack_4_character.nut", true);
			}
		}
	}
}

function createDieEffectLastSmoke(obj,damager,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atblood/lastpang_smoke.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), x);
	pooledObj.setCurrentPos(posX ,damager.getYPos() + y,damager.getZPos() + z );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createDieEffectLastBlowDown(obj,damager,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atblood/lastpang_blowdown.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), x);
	pooledObj.setCurrentPos(posX ,damager.getYPos() + y,damager.getZPos() + z );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createDieEffectLastBlowUp(obj,damager,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atblood/lastpang_blowup.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), x);
	pooledObj.setCurrentPos(posX ,damager.getYPos() + y,damager.getZPos() + z );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontBloodHitEffectUpWave(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/nnofferingatkdwave.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onProc_Attack(obj)
{
	local attackIndex = obj.getAttackIndex();
	local pAni = obj.sq_GetCurrentAni();
 	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    if (attackIndex == 3)
    {
        if (obj.sq_GetSkillLevel(SKILL_BLOODOATH) > 0)
        {



            local startFrameIndex = 3;
            local endFrameIndex = 7;

            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex <= startFrameIndex)
            {
                obj.setCurrentPos(obj.getVar().get_vector(0),obj.getYPos(),obj.getZPos() );

            }else if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex)
            {
                local startX = obj.getVar().get_vector(0);
                local maxD = obj.getVar().get_vector(1);

                currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
                local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
                if (currentT < maxT)
                {
                    local v = sq_GetAccel(0, maxD, currentT,maxT, true);
                    local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

                    if( obj.isMovablePos(dstX, obj.getYPos() ))
                    {
                        sq_setCurrentAxisPos(obj, 0, dstX);
                    }

                }
            }
        }
    }
}

function onTimeEvent_Attack(obj, timeEventIndex, timeEventCount)
{
    if (timeEventIndex == 0)
    {
        obj.resetHitObjectList();
    }
}

// state? ???? ???? ???? ???. ?? ???? ?????. 
function onSetState_Attack(obj, state, datas, isResetTimer) {
	if (!obj)
		return;

	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);

	local skillLevel = obj.sq_GetSkillLevel(SKILL_ICE_ELEMENTAL_ATTACK);
	local skillLevel2 = obj.sq_GetSkillLevel(SKILL_BLOODOATH);
	local skillLevel3 = obj.sq_GetSkillLevel(SKILL_STICKMASTER);
	// ???? ???.
	//print("set atmage atk\n\r");
	if (skillLevel > 0) {
		// ?? ???, ??? ?? ??
		obj.setAttackXVelocity(250);
		obj.setAttackXAccel(-1000);
		obj.setAttackXVelocityFast(400);
		obj.setAttackXAccelFast(-1000);

		// ??? ?? ??	
		//local datk = sq_GetCurrentAttackInfo(obj);		
		//local attackRate = 1.0+obj.sq_GetBonusRateWithPassive(174, -1, 0, 1.0); 
		//sq_SetCurrentAttackBonusRate(datk, attackRate);
		//obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());		
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
		//print("1\n\r");
	} else if (skillLevel2 > 0) {
		local attackIndex = obj.getAttackIndex();
		if (attackIndex == 0) {
			obj.setAttackXVelocity(200);
			obj.setAttackXAccel(-2000);
			obj.setAttackXVelocityFast(400);
			obj.setAttackXAccelFast(-2000);
		} else if (attackIndex == 1) {
			obj.setAttackXVelocity(150);
			obj.setAttackXAccel(-2000);
			obj.setAttackXVelocityFast(300);
			obj.setAttackXAccelFast(-2000);
		} else if (attackIndex == 2) {
			obj.setAttackXVelocity(50);
			obj.setAttackXAccel(-2000);
			obj.setAttackXVelocityFast(150);
			obj.setAttackXAccelFast(-2000);
		} else if (attackIndex == 3) {}
		//obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());		
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
		//print("2\n\r");
	} else if (skillLevel2 < 1 && skillLevel < 1) {
		// ???? ??? ???? ????? ??? ??
		obj.setAttackXVelocity(0);
		obj.setAttackXAccel(0);
		obj.setAttackXVelocityFast(0);
		obj.setAttackXAccelFast(0);
		local attackIndex = obj.getAttackIndex();
		if (sq_getGrowType(obj) == 4) {
			obj.setAttackXVelocity(200);
			obj.setAttackXAccel(-2000);
			obj.setAttackXVelocityFast(400);
			obj.setAttackXAccelFast(-2000);
			//obj.sq_SetCurrentAttackInfo(70);
			//obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());
			sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
		} else {
			local element = obj.getThrowElement();
			playSoundForAtmageAttack(obj, element, attackIndex);
		}
		//print("3\n\r");
	} else {
		//obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),obj.getState());		
		sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
		//print("0\n\r");
	}
	//print("set atmage atk success!\n\r");
}


function onAfterSetState_Attack(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	// ??? ??? ????, ?? ?????? ??
	// ???? ???? ??.
	local iceElementalAttackSkillLevel = obj.sq_GetSkillLevel(SKILL_ICE_ELEMENTAL_ATTACK);
	local bloodoath = obj.sq_GetSkillLevel(SKILL_BLOODOATH);
	
    if (bloodoath > 0)
    {
		local attackIndex = obj.getAttackIndex();
        local len = 150;

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress)
        {
            len = 50;
        }

		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) 
        {
            len = 50;
        }

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = 200;
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = 200;

        if (attackIndex == 3)
        {
            obj.getVar().clear_vector();
            obj.getVar().push_vector( obj.getXPos() );
            obj.getVar().push_vector( len );
        }

    }
	if (state == STATE_ATTACK && iceElementalAttackSkillLevel <= 0 && bloodoath <= 0&&sq_getGrowType(obj) != 4)
	{
		// ?? ???? ???.
		// ???? ?? ?? ??? ? ?? ????? ??? ???? ???? ?? (?????? ?? ???? ??)
		local element = obj.getThrowElement();
		local attackIndex = obj.getAttackIndex();
		
		// ???? appendage? ????? ???.
		// ????? ???? ??? ??? ??? ???
		local appendage = obj.GetSquirrelAppendage("Character/ATMage/ElementalChange/ap_ATMage_Elemental_Change.nut");
		if (!appendage || !appendage.isValid())
			element = ENUM_ELEMENT_NONE;

		if (attackIndex == 0)
		{
			if (element == ENUM_ELEMENT_FIRE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack1_fire_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack1_fire_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_WATER)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack1_water_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack1_water_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_DARK)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack1_dark_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack1_dark_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_LIGHT)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack1_light_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack1_light_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_NONE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack1_none_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack1_none_dodge.ani"), 0, 0);
			}
		}
		else if (attackIndex == 1)
		{
			if (element == ENUM_ELEMENT_FIRE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack2_fire_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack2_fire_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_WATER)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack2_water_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack2_water_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_DARK)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack2_dark_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack2_dark_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_LIGHT)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack2_light_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack2_light_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_NONE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack2_none_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack2_none_dodge.ani"), 0, 0);
			}
		}
		else if (attackIndex == 2)
		{
			if (element == ENUM_ELEMENT_FIRE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack3_fire_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack3_fire_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_WATER)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack3_water_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack3_water_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_DARK)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack3_dark_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack3_dark_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_LIGHT)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack3_light_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack3_light_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_NONE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack3_none_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack3_none_dodge.ani"), 0, 0);
			}
		}
		else if (attackIndex == 3)
		{
			if (element == ENUM_ELEMENT_FIRE)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack4_fire_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/fire/attack4_fire_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_WATER)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack4_water_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/water/attack4_water_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_DARK)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack4_dark_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/dark/attack4_dark_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_LIGHT)
			{	// ???
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack4_light_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/light/attack4_light_dodge.ani"), 0, 0);
			}
			else if (element == ENUM_ELEMENT_NONE)
			{
				obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack4_none_normal.ani"), 0, 0);
				obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("Effect/Animation/ATAttack/attack4_none_dodge.ani"), 0, 0);
			}
		}
	}	
}

function createMiniMagicCircle(obj, xPos, zPos, shotDirection, bonusDamage) // direction 0:??  1:???  2:??)
{	
	if(!obj)
		return;
	if (obj.sq_IsMyControlObject()) {
	
		// ???? ????
		local direction = sq_GetDirection(obj);
		local x = sq_GetDistancePos(obj.getXPos(), direction, xPos);
		local y = sq_GetDistancePos(obj.getYPos(), ENUM_DIRECTION_DOWN, 1);
		local z = sq_GetDistancePos(obj.getZPos(), ENUM_DIRECTION_UP, zPos);
		// ??? ????? ??.
		// ???
		// ?? ??(x,y,z)
		// ?? ??? (0?? ??? ??, 30?? ??? 30?? ??)
		// ?? ??? (0?? ??? ??, -30?? ??? 30?? ??)
		// ?? ?? ??? (?? ??)
		// ?? ?? ??? (?? ??)
		// ??? ?? ??. -1?? ?? ??
		// x? ?? ????
		// ?? ??? x? ??
		// ?? ??? y? ??
		// ?? ??? z? ??
		
		local activeObject;
		local searchAngleH = 0;
		local searchAngleV = 0;
		local passiveObjectIndex = 0;		
		
		if(shotDirection == 0)
		{	// ??
			//activeObject = sq_FindShootingTarget(obj, x, y, z, 0, 0, 10, 10, -1, 1000, 1000, 250, 100);	
			local distance = 1000;
			local angle = 20;
			activeObject = findAngleTarget(obj, distance, angle, 100); // ??? ??? ? ??			
			searchAngleH = 30;
			searchAngleV = 15;
			passiveObjectIndex = 24202;
		
			// ????? ???? ???, ?? ????? ??? (???? ??? ????)
			if (obj.getState() == STATE_MULTI_SHOT)
				passiveObjectIndex = 24266;
		}
		else if(shotDirection == 1) {// ???
			activeObject = sq_FindShootingTarget(obj, x, y, z, 0, 0, 4, 4, -1, 300, 100, 50, 100);
			searchAngleH = 5;
			searchAngleV = 5;			
			passiveObjectIndex = 24207;
			
			// ????? ???? ???, ?? ????? ??? (???? ??? ????)
			if (obj.getState() == STATE_MULTI_SHOT)
				passiveObjectIndex = 24271;
		}
		else if(shotDirection == 2) { // ??
			activeObject = sq_FindShootingTarget(obj, x, y, z, 0, 0, 4, 4, -1, 300, 100, 50, 100);			
			searchAngleH = 5;
			searchAngleV = 5;	
			passiveObjectIndex = 24228;
			
			// ????? ???? ???, ?? ????? ??? (???? ??? ????)
			if (obj.getState() == STATE_MULTI_SHOT)
				passiveObjectIndex = 24276;
		}				
		else {
			printc("error! magic ball create shotDirection error");
			return;
		}
		
		// ???? appendage? ????? ???.
		// ????? ???? ??? ??? ??? ???
		local horizonAngle = 0.0;
		local verticalAngle = 0.0;	
		if (activeObject != NULL) {		
			local maxDistance = abs(activeObject.getXPos() - x);
			horizonAngle = sq_GetShootingHorizonAngle(activeObject, y, 0, searchAngleH, maxDistance);
			verticalAngle = sq_GetShootingVerticalAngle(activeObject, z, 0, searchAngleV, maxDistance, 300);
		}
			
		local appendage = obj.GetSquirrelAppendage("Character/ATMage/ElementalChange/ap_ATMage_Elemental_Change.nut");
		if (appendage && appendage.isValid()) {	
			local element = obj.getThrowElement();
			passiveObjectIndex = passiveObjectIndex + 1 + element;
		}
		
		obj.sq_StartWrite();
		obj.sq_WriteFloat(horizonAngle);
		obj.sq_WriteFloat(verticalAngle);
		obj.sq_WriteDword(bonusDamage);		
		obj.sq_SendCreatePassiveObjectPacket(passiveObjectIndex, 0, xPos, 1, zPos);
	}
}

// ??? ?? ??? ????.
function onKeyFrameFlag_Attack(obj, flagIndex)
{
	if(!obj)
		return false;
	local isMyControlObject = obj.sq_IsMyControlObject();

	// ?????? ?? ??? ????.
	// ???? ??? ??? ?? ???? ? ??? ????? ??(??)
	// 
	local xPos = 0, zPos = 0;

	local attackIndex = obj.getAttackIndex();
	if (attackIndex == 0)
	{
		xPos = 65, zPos = 59;
	}
	else if (attackIndex == 1)
	{
		xPos = 60, zPos = 71;
	}
	else if (attackIndex == 2)
	{
		xPos = 55, zPos = 58;
	}
	else if (attackIndex == 3)
	{
		xPos = 65, zPos = 36;
	}

	if (flagIndex == 1)
	{
		// ????? ????.
		createMiniMagicCircle(obj, xPos, zPos, 0, 0); // direction 0:??  1:???  2:??
	}


	return true;
}

function playSoundForAtmageAttack(obj, elementalType, attackCount)
{	
	if(!obj)
		return;

	local elementalName = "MWSHOT_0";
	if (elementalType == ENUM_ELEMENT_FIRE)
		elementalName = "FIRESHOT_0";
	else if (elementalType == ENUM_ELEMENT_WATER)
		elementalName = "ICESHOT_0";
	else if (elementalType == ENUM_ELEMENT_DARK)
		elementalName = "DARKSHOT_0";
	else if (elementalType == ENUM_ELEMENT_LIGHT)
		elementalName = "LIGHTSHOT_0";
	
	obj.sq_PlaySound(elementalName + (attackCount+1));
}
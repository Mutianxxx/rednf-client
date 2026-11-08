
function procAppend_po_thief_shared(obj)
{
	if(!obj) return false;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local state = parentChr.sq_GetState();
	local pAni = obj.getCurrentAnimation();
	local frameIndex = sq_GetAnimationFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);



	switch(id)
	{
		case 0://???????? ???????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local currentX = obj.getVar("chakraMove").get_vector(0);
			local xDistance = obj.getVar("chakraMove").get_vector(1);
			local xAccel = sq_GetUniformVelocity(currentX, xDistance, currentT, 600);
			sq_setCurrentAxisPos(obj, 0, xAccel);
			local distance = sq_GetIntData(parentChr, SKILL_EQUIPCHAKRAWEAPON, 0);
			distance = distance.tofloat();
			if(obj.getDirection() == ENUM_DIRECTION_LEFT)
			{
				local maxDistance = currentX - distance;
				if(x <= maxDistance)
				{
					if(obj.isMyControlObject())
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
				}
			}
			if(obj.getDirection() == ENUM_DIRECTION_RIGHT)
			{
				local maxDistance = currentX + distance;
				if(x >= maxDistance)
				{
					if(obj.isMyControlObject())
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
				}
			}
		break;
		case 1://???????? ?????
			if(!parentChr || z == 0)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 2://???? ?? ????????? ????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 3://???? ?? ????????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 4://?????????????? ????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_ILUSIONSHURIKEN && sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 5://?????????????? ????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_ILUSIONSHURIKEN && sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 6://?????????????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_ILUSIONSHURIKEN && sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 7://?????????????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_ILUSIONSHURIKEN && sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 8://???? ?? ju??? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 9://???? ?? ju???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ju??? ???
                    //obj,Distance,Direction,LimitDistance,Limitzpos,Limitypos,MoveDistance
                    setRangeObjectXPos(obj, sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 2), ENUM_DIRECTION_NEUTRAL, 0, 300, 0, 2); 
					local xDistance = obj.getVar("flametornadoMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 40000);
					sq_setCurrentAxisPos(obj, 0, xAccel);

					// local objectManager = obj.getObjectManager();
					// for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
					// {
					// 	local mobXPos = obj.getVar("flametornadoAttract").get_vector(0);
					// 	local mobYPos = obj.getVar("flametornadoAttract").get_vector(1);
					// 	local distance = sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 2);//???????
					// 	local totalT = sq_GetIntData(parentChr, SKILL_FLAMETORNADO, 3);//??????????
					// 	local object = objectManager.getCollisionObject(i);
					// 	if(object && obj.isEnemy(object) && !sq_IsFixture(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && sq_GetDistance(x, y, mobXPos, mobYPos, true) <= distance)
                    //     {
                    //         local xAccel = sq_GetAccel(mobXPos, x, currentT, totalT, false);
					// 		local yAccel = sq_GetAccel(mobYPos, y, currentT, totalT, false);
					// 		sq_setCurrentAxisPos(object, 0, xAccel);
					// 		sq_setCurrentAxisPos(object, 1, yAccel);
                    //     }
                    // }
				break;
			}
		break;
		case 10://???? ?? ???????? ????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 11://???? ?? ???????? ????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 12://???? ?? ???????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ??? ???
					local xDistance = obj.getVar("bigkunaiMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100000);
					sq_setCurrentAxisPos(obj, 0, xAccel);
				break;
				case 11://???? ?? ???????? ??? ???
					local xDistance = obj.getVar("bigkunaiMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 150000);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					if(parentChr.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1)
					{
						sq_MoveToNearMovablePos(parentChr, x, y, z, sq_GetXPos(parentChr), sq_GetYPos(parentChr), sq_GetZPos(parentChr), 20, -1, 3);
						obj.sendStateOnlyPacket(12);
						obj.flushSetStatePacket();
					}
				break;
			}
		break;
		case 13://???? ?? ???????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ???? ???
					local zDistance = obj.getVar("bigkunaiMove").get_vector(0);
					local zAccel = sq_GetUniformVelocity(z, zDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 2, zAccel);
					if(z == 0)
					{
						obj.sendStateOnlyPacket(11);
						obj.flushSetStatePacket();
					}
				break;
				case 11://???? ?? ???????? ???? ???
					if(parentChr.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1)
					{
						sq_MoveToNearMovablePos(parentChr, x, y, z, sq_GetXPos(parentChr), sq_GetYPos(parentChr), sq_GetZPos(parentChr), 20, -1, 3);
						obj.sendStateOnlyPacket(12);
						obj.flushSetStatePacket();
					}
				break;
			}
		break;
		case 14://???? : ?????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 11://???? : ?????? ????? ???
					local xDistance = obj.getVar("migawariMove").get_vector(0);
					local zDistance = obj.getVar("migawariMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 1500);
					local zAccel = sq_GetUniformVelocity(z, zDistance, currentT, 1500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 2, zAccel);
					sq_SimpleMoveToNearMovablePos(obj, 200);
				break;
			}
			LeaveTrace_Body(obj);
		break;
		case 15://???? : ?????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 16://???? : ?????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 17://???? : ?????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 18://???? ?? ???? ????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 19://???? ?? ???? ????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 20://???? ?? ???? ???????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 21://???? ?? ???? ?????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 22://???? ?? ???? ?????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 23://???? ?? ???? ???????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 24://???? ?? ??chu?????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 25://???? ?? ??chu??????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 26://???? ?? ??chu?????? ??????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 27://???? ?? ??????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_FLAMEFLOWER && frameIndex <= 32)
			{
				if(sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
				{
					sq_SetAnimationFrameIndex(pAni, 33);
				}
			}
			if(state == STATE_FLAMEFLOWER && frameIndex >= 34 && frameIndex <= 67)
			{
				if(sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
				{
					sq_SetAnimationFrameIndex(pAni, 68);
				}
			}
			LeaveTrace_Body(obj);
		break;
		case 28://???? ?? ??????? ??????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(state == STATE_FLAMEFLOWER)
			{
				if(sq_IsEnterCommand(parentChr, E_JUMP_COMMAND))
				{
					sq_SendDestroyPacketPassiveObject(obj);
				}
			}
		break;
		case 29://???? ?? ??????? ???????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 30://???? ?? ????????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			if(frameIndex >= 17 && frameIndex <= 26)
			{
				local objectManager = obj.getObjectManager();
				for(local i = 0; i < objectManager.getCollisionObjectNumber(); ++ i)
				{
					local mobXPos = obj.getVar("attract").get_vector(0);
					local mobYPos = obj.getVar("attract").get_vector(1);
					local object = objectManager.getCollisionObject(i);
					if(object && obj.isEnemy(object) && !sq_IsFixture(object) && object.isObjectType(OBJECTTYPE_ACTIVE)&&object.isInDamagableState(obj) && sq_GetDistance(x, y, mobXPos, mobYPos, true) <= 600)
					{
						local xAccel = sq_GetAccel(mobXPos, x, currentT, 500, false);
						local yAccel = sq_GetAccel(mobYPos, y, currentT, 500, false);
						sq_setCurrentAxisPos(object, 0, xAccel);
						sq_setCurrentAxisPos(object, 1, yAccel);
					}
				}
			}
			LeaveTrace_Body(obj);
		break;
		case 31://???? ?? ????????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 32://???? ?? ????????? ????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 33://???? ?? ????????? ???????????1
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 34://???? ?? ????????? ???????????2
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 35://???? ?? ????????? ???????????3
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 36://???? ?? ????????? ???????????4
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 37://???? ?? ????????? ???????????5
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 38://???? ?? ????????? ???????????6
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 39://?????????????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 40://?????????????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 41://?????????????? ??shuo???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 42://?????????????? ?????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 43://?????????????? ?????????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 44://?????????????? ????????????????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 45://???????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 46://????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 47://???????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 48://???? ?? ???????? ????? ???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 49://???? ?? ???????? ????? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 50://???? ?? ???????? ?
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 500);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 11://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
			}
		break;
		case 51://???? ?? ???????? ?
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 500);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 11://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
			}
		break;
		case 52://???? ?? ???????? ?
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 500);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 11://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
			}
		break;
		case 53://???? ?? ???????? ?
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 500);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 11://???? ?? ???????? ? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("smallSurikenMove").get_vector(0);
					local yDistance = obj.getVar("smallSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
			}
		break;
		case 54://???? ?? ???????? ??
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10://???? ?? ???????? ?? ????
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 300);
					sq_setCurrentAxisPos(obj, 0, xAccel);
				break;
				case 11://???? ?? ???????? ?? ???1
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
					local yDistance = obj.getVar("bigSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 12://???? ?? ???????? ?? ???2
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
					local yDistance = obj.getVar("bigSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 13://???? ?? ???????? ?? ???3
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
					local yDistance = obj.getVar("bigSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
				case 14://???? ?? ???????? ?? ???4
					if(!parentChr)
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
					local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
					local yDistance = obj.getVar("bigSurikenMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					local yAccel = sq_GetUniformVelocity(y, yDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 1, yAccel);
				break;
			}
		break;
		case 55://???? ?? ???????? ?? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 56://???? ?? ???????? ?? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local xDistance = obj.getVar("bigSurikenMove").get_vector(0);
			local zDistance = obj.getVar("bigSurikenMove").get_vector(1);
			local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 300);
			local zAccel = sq_GetUniformVelocity(z, zDistance, currentT, 300);
			sq_setCurrentAxisPos(obj, 0, xAccel);
			sq_setCurrentAxisPos(obj, 2, zAccel);
		break;
		case 57://???? ?? ???????? ?? ???? ????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 58://??? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			LeaveTrace_Body(obj);
		break;
		case 59://???
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 60://??? ??????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 61://???????? ?? ?????? ????????
			local currentX = obj.getVar("swordofkusanagiMove").get_vector(0);
			local xDistance = obj.getVar("swordofkusanagiMove").get_vector(1);
			local xAccel = sq_GetUniformVelocity(currentX, xDistance, currentT, 500);
			sq_setCurrentAxisPos(obj, 0, xAccel);
			local distance = sq_GetIntData(parentChr, SKILL_SWORDOFKUSANAGI, 1);
			if(obj.getDirection() == ENUM_DIRECTION_LEFT)
			{
				local maxDistance = currentX - distance;
				if(x <= maxDistance)
				{
					if(obj.isMyControlObject())
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
				}
			}
			if(obj.getDirection() == ENUM_DIRECTION_RIGHT)
			{
				local maxDistance = currentX + distance;
				if(x >= maxDistance)
				{
					if(obj.isMyControlObject())
					{
						sq_SendDestroyPacketPassiveObject(obj);
					}
				}
			}
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 62://???????? ?? ?????? ???????? ??
			if(!parentChr || z == 0)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 63://???????? ?? ?????? ?????? ?????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 64://???????? ?? ?????? ??????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
		case 65://???? ?? ????????? ????? ????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 66://?????????????? ????? ????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 67://?????????????? ????? ???????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 68://???? ?? ju??? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 69://???? ?? ???????? ????? ????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 70://???? ?? ???????? ????? ???????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 71://???? : ?????? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 11://???? : ?????? ????? ???????????
					local xDistance = obj.getVar("migawariMove").get_vector(0);
					local zDistance = obj.getVar("migawariMove").get_vector(1);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 1500);
					local zAccel = sq_GetUniformVelocity(z, zDistance, currentT, 1500);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					sq_setCurrentAxisPos(obj, 2, zAccel);
					sq_SimpleMoveToNearMovablePos(obj, 200);
				break;
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 72://???? ?? ???? ????? ????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 73://???? ?? ???? ????? ???????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 74://???? ?? ??chu?????? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 75://???? ?? ??chu???????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 76://???? ?? ??????? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 77://???????? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 78://???? ?? ???????? ????? ????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 79://???? ?? ???????? ????? ???????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
		case 80://??? ??????????????
			if(!parentChr)
			{
				sq_SendDestroyPacketPassiveObject(obj);
			}
	        if(CNSquirrelAppendage.sq_IsAppendAppendage(parentChr, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut") == true)
	        {
				sq_SetPause(obj, PAUSETYPE_OBJECT, 1);
			}
		break;
	}
}












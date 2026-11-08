function checkExecutableSkill_SwordGhost9(obj)
{
	if (!obj) return false;
	

		local SoulIndex = [262167,262174,260182,260192,260193,260194,261151,260190,260180,260184];
		foreach(Index in SoulIndex)
		{
			local ObjCount = obj.getMyPassiveObjectCount(Index);
			if(ObjCount > 0)
			{
				local passiveObj = obj.getMyPassiveObject(Index,0);
				if(passiveObj)
				{
					local Xpos = passiveObj.getXPos();
					local Ypos = passiveObj.getYPos();
					local uid = sq_GetObjectId(obj);
					local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_9);
					if (isUse)
					{
						sq_BinaryStartWrite();
						sq_BinaryWriteDword(uid);
						sq_BinaryWriteDword(Xpos);
						sq_BinaryWriteDword(Ypos);
						sq_SendChangeSkillEffectPacket(obj, 128);
					
						sq_SendCreatePassiveObjectPacketPos(obj, 262166, 0, Xpos, Ypos, 0);
						return true;
					}
				}
			}
		}
		obj.startCantUseSkillWarning(); 
		sq_AddMessage(71099);
		return false;
}


function checkCommandEnable_SwordGhost9(obj)
{
	if (!obj) return false;
	//local state = obj.sq_GetState();

	//if (state == STATE_STAND)
	return true;
	//local SoulIndex = [262167,262174,260182,260192,260193,260194,261151,260190,260180,260184];
	//foreach(Index in SoulIndex)
	//{
	//	local ObjCount = obj.getMyPassiveObjectCount(Index);
	//	if(ObjCount > 0)
	//	{
	//		return true;
	//	}
	//}
	//return false;
}


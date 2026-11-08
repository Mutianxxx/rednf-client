
function onSetState_ATSwordmanThrow(obj, CQhUSViecCxMmfAcFAzQ, CQpkYRfTK8L2WLXT3, CQ36VmCLgemZqnXb8tS)
{
	if(!obj) return
		    local CQqCrasaPZ1AbXZx = obj.getThrowIndex()
		                             local CQKSCXqm5TyiwoLmkY = obj.sq_GetVectorData(CQpkYRfTK8L2WLXT3, 0)
		                                     obj.setSkillSubState(CQKSCXqm5TyiwoLmkY)
		                                     switch(CQKSCXqm5TyiwoLmkY)
		{
		case 0:

			break
		case 1:

			break
		}
}

function onProcCon_ATSwordmanThrow(obj)
{
	if(!obj) return
		    local CQsm7bBHCJsxxaKQy = obj.getThrowIndex()
		                              if(CQsm7bBHCJsxxaKQy == 96)
		{
			if (obj.getThrowState() == 3)
			{
				if(sq_IsKeyDown(OPTION_HOTKEY_SKILL2, ENUM_SUBKEY_TYPE_ALL))
				{
					sq_BinaryStartWrite()
					sq_SendChangeSkillEffectPacket(obj, 96)
				}
			}
		}
}

function onProc_AtSwordman_Basic(obj)
{
	if(!obj) return;

		if(sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
		{
			local itemobj = null;
			local objman = obj.getObjectManager();
			if (objman)
			{
				for(local i = 0; i < 80 ; ++i)
				{
					for(local j = 0; j<92; ++j)
					{
						itemobj = objman.getMeetItemObject(sq_GetScreenXPos(obj)-40+i, sq_GetScreenYPos(obj)-46+j);
						if (itemobj)
						{
							obj.procGetItem();
							return;
						}
					}
				}
			}
		}

}

function onAfterSetState_ATSwordmanThrow(obj, CQvw25LSIdox7sBtn9, CQDxozEWhWffgbBwwtet, CQRdgtnxyCP38XVit)
{
	local CQiMFDdCX8zZ3mVWoYB = obj.getThrowIndex()

	                            if(CQiMFDdCX8zZ3mVWoYB == 96)
	{
		if (obj.getThrowState() == 0)
			obj.setIsCustomSelectSkill(true)
			else if (obj.getThrowState() == 1)
			{
				obj.sq_PlaySound("PCHANGE_SELECT")
				local CQ1Hv2XImeKC99CE = obj.getThrowElement()
				                         if (obj.isMyControlObject())
				{
					obj.sq_IntVectClear()
					obj.sq_IntVectPush(CQ1Hv2XImeKC99CE + 1)
					obj.sq_AddSetStatePacket(96, STATE_PRIORITY_IGNORE_FORCE, true)
				}
			}
	}
}

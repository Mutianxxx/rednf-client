function onProc_AtPriest_Basic(obj)
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
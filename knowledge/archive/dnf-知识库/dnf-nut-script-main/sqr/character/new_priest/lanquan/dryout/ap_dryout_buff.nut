function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_dryout_buff")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_dryout_buff")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_dryout_buff")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_dryout_buff")

}



function sq_AddEffect(appendage)
{
	if(!appendage) return;
}


function onStart_appendage_dryout_buff(appendage)
{
	if(!appendage) return;

	local apd = appendage.getParent();
	local obj = sq_getMyCharacter();

	local spectrumAppendage = appendage.sq_GetOcularSpectrum("ocularSpectrum");
	
	if(!spectrumAppendage)
	{
		spectrumAppendage = appendage.sq_AddOcularSpectrum("ocularSpectrum", obj, obj, 100);
	}

	sq_SetParameterOcularSpectrum(spectrumAppendage, 500, 200, true, sq_RGBA(5, 121, 249, 255), sq_RGBA(5, 121, 249, 0), 0, 2, 2);
}



function proc_appendage_dryout_buff(appendage)
{
	if(!appendage) return;
}



function onEnd_appendage_dryout_buff(appendage)
{
	if(!appendage) return
	local parentObj = appendage.getParent()
	if(!parentObj ) 
	{
		appendage.setValid(false)
		return
	}
	local spectrumAppendage = appendage.sq_GetOcularSpectrum("ocularSpectrum");

	if(spectrumAppendage)
	{
		spectrumAppendage.endCreateSpectrum();
	}
}



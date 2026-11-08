function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageGaugeBasic")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageGaugeBasic")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageGaugeBasic")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageGaugeBasic(appendage)
{

}

function proc_appendage_BloodMageGaugeBasic(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				



	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}

}



function onStart_appendage_BloodMageGaugeBasic(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	

    appendage.getVar("EnergyParameter").clear_vector();
    for (local i = 0;i< 25 ;i++)
    {
        appendage.getVar("EnergyParameter").push_vector( -1 );
        appendage.getVar("EnergyParameter").push_vector( -1 );
        appendage.getVar("EnergyParameter").push_vector( -1 );
    }


    appendage.getVar("GaugeNum").clear_vector();
    appendage.getVar("GaugeNum").push_vector( -1 );
    appendage.getVar("GaugeNum").push_vector( -1 );
    appendage.getVar("GaugeNum").push_vector( -1 );



//        apd.getVar("EnergyParameter").set_vector(3 * id + 0,curT);
//        apd.getVar("EnergyParameter").set_vector(3 * id + 1,screenX);
//        apd.getVar("EnergyParameter").set_vector(3 * id + 2,screenY);


}



function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_Brionac")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Brionac")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_Brionac")
}

function sq_AddEffect(appendage) {

}

function proc_appendage_Brionac(appendage) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_Brionac(appendage) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}
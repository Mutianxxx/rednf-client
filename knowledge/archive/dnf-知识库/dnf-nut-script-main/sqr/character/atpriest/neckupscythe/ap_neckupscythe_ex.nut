function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_neckupscythe_ex")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_neckupscythe_ex")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_neckupscythe_ex")
}

function sq_AddEffect(appendage)
{
	//appendage.sq_AddEffectBack("character/atswordman/effect/animation/atfrenzy/loop_loopx.ani")
	//appendage.sq_AddEffectFront("character/atswordman/effect/animation/atfrenzy/loop_upx.ani")
}


function proc_appendage_neckupscythe_ex(appendage)
{
	if(!appendage) {
		return;
	}
	local Parentobj = appendage.getParent();
	local sourceObj = appendage.getSource();
}

function onStart_appendage_neckupscythe_ex(appendage)
{
	if(!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
}

function onEnd_appendage_neckupscythe_ex(appendage)
{
	if(!appendage) {
		return;
	}
	local obj = appendage.getParent();
}


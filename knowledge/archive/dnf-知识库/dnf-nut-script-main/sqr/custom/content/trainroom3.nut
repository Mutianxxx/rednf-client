

BackAniPath <- "map/trainingroom/trainingroomback.ani"
ControlsAniPath <- "map/trainingroom/trainingroombuttons.ani"
ControlTipsAniPath <- "map/trainingroom/trainingroomtips.ani"

ControlTipsMonName <- "map/trainingroom/mon_name.ani"
ControlTipsMonHPset <- "map/trainingroom/mon_hp.ani"
ControlTipsMonHPstate <- "map/trainingroom/mon_error_state.ani"
ControlTipsMonLv <- "map/trainingroom/mon_lv.ani"
ControlTipsMonHit <- "map/trainingroom/mon_hit_condition.ani"


ControlTipsSetTime <- "map/trainingroom/chr_set_time.ani"

ControlTipsCritical <- "map/trainingroom/chr_critical.ani"
ControlTipAttackvalue <- "map/trainingroom/chr_attackvalue.ani"
ControlTipsElement <- "map/trainingroom/chr_element_add.ani"
ControlTipsSpeed <- "map/trainingroom/chr_doublespeed.ani"
ControlTipsChrHp <- "map/trainingroom/chr_hp.ani"
ControlTipsChrMp <- "map/trainingroom/chr_mp.ani"


BackUI	<-
{

	["MainTestUI"] = ["MainBack1",BackAniPath,2,0.58,255,255,20,0,0,0,778,799,77,134],	
	["MainControlUI"] = ["MainBack2",BackAniPath,0,0.58,255,255,255,200,0,0,778,799,77,134],	
	["CloseMainUI"] = ["MainBack3",BackAniPath,0,0.58,255,255,255,200,0,0,341,358,77,134]	
}

ButtonsInfo	<- [

    ["ButtonDown1",ControlsAniPath,1,1.0,255,255,255,255,0,0,385,571,101,112],
    ["ButtonDown2",ControlsAniPath,1,1.0,255,255,255,255,0,28,482,571,129,140],
    ["ButtonDown3",ControlsAniPath,1,1.0,255,255,255,255,0,55,482,571,157,167],
    ["ButtonDown4",ControlsAniPath,1,1.0,255,255,255,255,-97,28,385,474,129,140],
    ["ButtonDown6",ControlsAniPath,1,1.0,255,255,255,255,0,136,385,571,237,250],
    ["ButtonDown5",ControlsAniPath,1,1.0,255,255,255,255,125,0,592,696,101,112],
    ["ButtonDown7",ControlsAniPath,1,1.0,255,255,255,255,125,28,592,696,129,141],
    ["ButtonDown8",ControlsAniPath,1,1.0,255,255,255,255,125,55,592,696,156,167],
    ["ButtonDown9",ControlsAniPath,1,1.0,255,255,255,255,125,82,592,696,184,196],
    ["ButtonDown10",ControlsAniPath,1,1.0,255,255,255,255,125,110,592,696,210,222],
    ["ButtonDown11",ControlsAniPath,1,1.0,255,255,255,255,125,136,592,696,239,250],
    ["Button12",ControlsAniPath,17,1.0,255,255,255,255,-36,110,521,563,210,222],
    ["Button13",ControlsAniPath,17,1.0,255,255,255,255,-113,110,442,485,210,222],
    ["Button14",ControlsAniPath,17,1.0,255,255,255,255,-172,110,383,427,210,222]

]
ButtonsInfo1	<- [
    ["Button1",ControlsAniPath,5,0.84,255,255,255,255,159,0,715,794,100,117],
    ["ButtonTip1",ControlTipsAniPath,56,0.5,255,255,255,255,159+7,2,715,794,100,117],
    ["Button2",ControlsAniPath,5,0.84,255,255,255,255,159,26,715,794,125,142],
    ["ButtonTip2",ControlTipsAniPath,60,0.5,255,255,255,255,159 +10,26+2,715,794,125,142],
    ["Button3",ControlsAniPath,5,0.84,255,255,255,255,159,52,715,794,154,169],
    ["ButtonTip3",ControlTipsAniPath,64,0.5,255,255,255,255,159 +15,54,715,794,154,169],
    ["Button4",ControlsAniPath,5,0.84,255,255,255,255,159,78,715,794,179,195],
    ["ButtonTip4",ControlTipsAniPath,68,0.5,255,255,255,255,159+15,78+2,715,794,179,195],
    ["Button5",ControlsAniPath,5,0.84,255,255,10,255,159,104,715,794,205,221],
    ["ButtonTip5",ControlTipsAniPath,72,0.5,255,255,255,255,159+4,104+2,715,794,205,221],
    ["Button6",ControlsAniPath,5,0.84,255,255,255,255,-169,53,338,466,153,170],
    ["ButtonTip6",ControlTipsAniPath,44,0.5,255,255,255,255,-166,54,338,466,153,170],
    ["Button7",ControlsAniPath,5,1.0,255,255,255,255,-181,170,375,432,271,294],
    ["ButtonTip7",ControlTipsAniPath,48,0.6,255,255,255,255,-180,172,375,432,271,294],
    ["Button8",ControlsAniPath,5,1.0,255,255,255,255,-117,170,440,496,271,294],
    ["ButtonTip8",ControlTipsAniPath,52,0.6,255,255,255,255,-114,172,440,496,271,294]

]

SeSelectsInfo	<- [
    ["SelectTip1",ControlTipsAniPath,0,0.5,255,255,255,255,-168,0+1,385,571,99,117],
    ["SelectTip2",ControlTipsAniPath,8,0.5,255,255,255,255,-70,28,482,571,129,140],
    ["SelectTip3",ControlTipsAniPath,12,0.5,255,255,255,255,-70,55,482,571,157,167],
    ["SelectTip4",ControlTipsAniPath,4,0.5,255,255,255,255,-168,28,385,474,129,140],
    ["SelectTip6",ControlTipsAniPath,16,0.5,255,255,255,255,-168,136,385,571,237,250],
    ["SelectTip5",ControlTipsAniPath,20,0.5,255,255,255,255,35,0,592,696,101,112],
    ["SelectTip7",ControlTipsAniPath,24,0.5,255,255,255,255,35,28,592,696,129,141],
    ["SelectTip8",ControlTipsAniPath,28,0.5,255,255,255,255,35,55,592,696,156,167],
    ["SelectTip9",ControlTipsAniPath,32,0.5,255,255,255,255,35,82,592,696,184,196],
    ["SelectTip10",ControlTipsAniPath,36,0.5,255,255,255,255,35,110,592,696,210,227],
    ["SelectTip11",ControlTipsAniPath,40,0.5,255,255,255,255,35,136,592,696,239,250]
]


TrainSelectWidgetsInfo	<- [
    ["Button9",ControlsAniPath,13,1.0,255,255,255,255,-40,175,518,592,275,287],
    ["Button10",ControlsAniPath,13,1.0,255,255,255,255,49,175,607,693,275,287],
    ["Button11",ControlsAniPath,13,1.0,255,255,255,255,150,175,708,780,275,287]
]

SeveralSelectBackInfo	<- [	
    ["mon_nameBack",ControlsAniPath,21,0.85,0.85,255,255,255,255,385,571,117,135],
    ["mon_LvBack",ControlsAniPath,21,0.4,0.85,255,255,255,255,385,571,129,140],
    ["mon_HPBack",ControlsAniPath,21,0.4,0.85,255,255,255,255,385,571,129,140],
    ["mon_StateBack",ControlsAniPath,21,0.4,0.85,255,255,255,255,385,571,167,185],
    ["mon_SetYimBack",ControlsAniPath,21,0.85,0.85,255,255,255,255,385,571,236,253],
    ["Chr_CritiBack",ControlsAniPath,21,0.49,0.85,255,255,255,255,592,696,167,185],
    ["Chr_ValueBack",ControlsAniPath,21,0.49,0.85,255,255,255,255,592,696,129,141],
    ["mon_EleBack",ControlsAniPath,21,0.49,0.85,255,255,255,255,592,696,156,167],
    ["mon_SpeedBack",ControlsAniPath,21,0.49,0.85,255,255,255,255,592,696,184,198],
    ["mon_SetHPBack",ControlsAniPath,21,0.49,0.85,255,255,255,255,592,696,210,227],
    ["mon_SetMPBack",ControlsAniPath,21,0.49,0.85,255,255,255,592,696,239,257]
]



SeveralSelectWidgetsInfo	<- [
    ["mon_nameTips",ControlTipsMonName,20,0.5,0.5,255,255,255,255,385,571,117,135],
    ["mon_LvTips",ControlTipsMonLv,21,0.5,0.5,255,255,255,255,385,475,129,146],
    ["mon_SetHP",ControlTipsMonHPset,11,0.5,0.5,255,255,255,255,483,571,129,147],
    ["mon_State",ControlTipsMonHPstate,15,0.5,0.5,255,255,255,255,482,571,157,172],
    ["mon_SetTim",ControlTipsSetTime,10,0.5,0.5,255,255,255,255,385,571,236,253],
    ["Chr_Critical",ControlTipsCritical,10,0.5,0.5,255,255,255,255,592,696,101,119],
    ["Chr_Value",ControlTipAttackvalue,10,0.5,0.5,255,255,255,255,592,696,129,145],
    ["Chr_Element",ControlTipsElement,9,0.5,0.5,255,255,255,255,592,696,156,174],
    ["Chr_Speed",ControlTipsSpeed,10,0.5,0.5,255,255,255,255,592,696,184,202],
    ["Chr_SetHp",ControlTipsChrHp,10,0.5,0.5,255,255,255,255,592,696,210,228],
    ["Chr_SetMp",ControlTipsChrMp,10,0.5,0.5,255,255,255,255,592,696,239,257]
]

SumMonstersId	<-  
{
	[-1] = 56923,
	[0] = 56923,
	[1] = 56921,
	[2] = 2021401,
	[3] = 2021402,
	[4] = 2021403,
	[5] = 2021404,
	[6] = 2021405,
	[7] = 2021406,
	[8] = 2021407,
	[9] = 2021408,
	[10] = 2021409,
	[11] = 2021410,
	[12] = 2021411,
	[13] = 2021412,
	[14] = 2021413,
	[15] = 2021414,
	[16] = 711,
	[17] = 1085,
	[18] = 61001,
	[19] = 43016
}


TrainMonIcons<-
{
	[56923]=0, 
	[56921]=1, 
	[2021401]=2, 
	[2021402]=3, 
	[2021403]=4, 
	[2021404]=5, 
	[2021405]=6, 
	[2021406]=7, 
	[2021407]=8, 
	[2021408]=9, 
	[2021409]=10, 
	[2021410]=11, 
	[2021411]=12, 
	[2021412]=13, 
	[2021413]=14, 
	[2021414]=15, 
	[711]=16, 
	[1085]=17, 
	[61001]=18, 
	[43016]=19 
}



function DrawBackWithAni(obj,WidgetInfo,isOpen,Xpos,Ypos)
{
	if(isOpen == false)
		Xpos = Xpos + 438;

	DrawTrainRoomAniUI(obj,WidgetInfo[0],WidgetInfo[1],WidgetInfo[3],WidgetInfo[3],WidgetInfo[4],WidgetInfo[5],WidgetInfo[6],WidgetInfo[7],WidgetInfo[2],WidgetInfo[8] + Xpos,WidgetInfo[9] + Ypos);

	return;
}

function DrawTrainTips(obj,isOpen)
{
	if(isOpen == false)
		return;
	local areainfo = [518,592,275,288];
	local AniPath = "map/trainingroom/trainingroomtips.ani";
	local Rate = 0.7;
	if(isMouseInScreenArea(obj,areainfo))
	{
		DrawTrainRoomAniUI(obj,"TKeyBoard1",AniPath,Rate,Rate,255,255,255,240,76,420,250);
		
	}

	
}


function DrawWidgetsWithAni(obj,WidgetInfo,isOpen,Xpos,Ypos)
{
	local FramId = 0;
	local moshi = 1;
	
	local temp = ["Button12","Button13","Button14"];
	local mousArea = [WidgetInfo[10], WidgetInfo[11], WidgetInfo[12], WidgetInfo[13]];
	if(isMouseInScreenArea(obj,mousArea) && !IsLightWidgets(obj))
		FramId = 1;
	if(isOpen && isLeftMouseInAreaDown(obj,mousArea) && !IsLightWidgets(obj)) 
	{
		FramId = 2;
		foreach(index,val in temp) 
		{
			ButtonsFunctions["SelectTip6"][1] = -1;
			if(WidgetInfo[0] == val)
				SingleTrainSelect = index;
		}

	}
	if(WidgetInfo[0] == "Button7" || WidgetInfo[0] == "Button8")
		moshi = 0.6;

	if(WidgetInfo[0] == temp[SingleTrainSelect])
		FramId = 2;

	if(WidgetInfo[0] == "ButtonDown6" && SingleTrainSelect != 0)
		FramId = 3;

	if(isOpen == false)
		Xpos = Xpos + 438;
	DrawTrainRoomAniUI(obj,WidgetInfo[0] ,WidgetInfo[1],WidgetInfo[3]*moshi,WidgetInfo[3],WidgetInfo[4],WidgetInfo[5],WidgetInfo[6],WidgetInfo[7],WidgetInfo[2] + FramId,WidgetInfo[8] + Xpos,WidgetInfo[9] + Ypos);

	return;
}
function DrawWidgetsWithAni_1(obj,WidgetInfo,isOpen,Xpos,Ypos)
{
	local FuncButton = [
	                       "Button1",
	                       "Button2",
	                       "Button3",
	                       "Button4",
	                       "Button5",
	                       "Button6",
	                       "Button7",
	                       "Button8"
	                   ]
	                   local FramId = 0;
	local moshi = 1;
	
	local temp = ["Button12","Button13","Button14"];
	local mousArea = [WidgetInfo[10], WidgetInfo[11], WidgetInfo[12], WidgetInfo[13]];
	if(isMouseInScreenArea(obj,mousArea) && !IsLightWidgets(obj))
		FramId = 1;
	if(isOpen && isLeftMouseInAreaDown(obj,mousArea) && !IsLightWidgets(obj))
	{
		
		FramId = 2;
		foreach(index,val in temp) 
		{
			if(WidgetInfo[0] == val)
				SingleTrainSelect = index;
		}

		PushDownCount2++;
		if(PushDownCount2 > 0 && PushDownCount2 < 2)
		{
			if(WidgetInfo[0] == FuncButton[0]) 
			{
				IsMouseDown = true;	
				sq_SendCreatePassiveObjectPacket(obj, 20214291, 0, 0, 0, 0, obj.getDirection());
			}
			else if(WidgetInfo[0] == FuncButton[1])  
			{
				InitializeMyCharacter(obj);
			}
			else if(WidgetInfo[0] == FuncButton[2])  
			{
				if(IsTrainSkilllAnalyse && !IsMouseDown)
				{
					IsMouseDown = true;	
					IsTrainSkilllAnalyse = false;
				}else if(!IsTrainSkilllAnalyse && !IsMouseDown)
				{
					IsMouseDown = true;	
					IsTrainSkilllAnalyse = true;
				}				

			}
			else if(WidgetInfo[0] == FuncButton[3])  
			{
				if(IsTrainFighterRecord && !IsMouseDown)
				{
					IsMouseDown = true;	
					IsTrainFighterRecord = false;
				}else if(!IsTrainFighterRecord && !IsMouseDown)
				{
					IsMouseDown = true;	
					IsTrainFighterRecord = true;
				}
			}
			else if(WidgetInfo[0] == FuncButton[4])  
			{
				ClearSkillsCooltime(obj);
			}
			else if(WidgetInfo[0] == FuncButton[5])  
			{
				if(!IsTrainSetHitCondition && !IsMouseDown){
					IsMouseDown = true ;
					IsTrainSetHitCondition = true;
				}
				else if(IsTrainSetHitCondition && !IsMouseDown){
					IsMouseDown = true ;
					IsTrainSetHitCondition = false;
				}
			}
			else if(WidgetInfo[0] == FuncButton[6])  
			{
				

				local LimitTime = ButtonsFunctions["SelectTip6"][1];
				local RealTime = [10000,15000,20000,25000,30000,60000,120000,180000,24000,300000];
				local CutTime = obj.getVar("TrainRoomTimeGet").get_vector(0);
				if(IsTrainStartTimeFight == false && LimitTime != -1) 
				{
					IsTrainStartTimeFight = true;
					TrainStartTime = CutTime;
					TrainEndTime = CutTime + RealTime[LimitTime];
					killMonsters(obj);
					ClearSkillsCooltime(obj);
					TrainningSetChrHp(obj,100);
					TrainningSetChrMp(obj,100);
					IsShowMainUI = false;
					obj.getVar("TrainTestHitDamage").clear_vector();
					obj.getVar("TrainTestHitDamage").push_vector(0);
					obj.getVar("TrainTestHitDamage").push_vector(0);
					obj.getVar("TrainTestHitDamage").push_vector(0);
					obj.getVar("TrainTestHitDamage").push_vector(-1);
					
					TraniningSummInfo[2] = TrainStartTime+4000;
					
					TrainSkilllPageNum = 0;
					TrainReset();
					TrainChrOldSkillId = -1;
					TrainChrCurSkillId = -1;
					TrainTempOldSkillId = -1;
					TrainMonHpPer = -1;
				}
				else
					TraniningSumMons(obj);

			}
			else if(WidgetInfo[0] == FuncButton[7])  
			{
				killMonsters(obj);
				if(IsTrainStartTimeFight == true)
					IsTrainFighterPrepEnd = true;
			}
		}
	}

	if(WidgetInfo[0] == "Button7" || WidgetInfo[0] == "Button8")
		moshi = 0.6;

	if(WidgetInfo[0] == temp[SingleTrainSelect])
		FramId = 2;

	if(isOpen == false)
		Xpos = Xpos + 438;
	DrawTrainRoomAniUI(obj,WidgetInfo[0] ,WidgetInfo[1],WidgetInfo[3]*moshi,WidgetInfo[3],WidgetInfo[4],WidgetInfo[5],WidgetInfo[6],WidgetInfo[7],WidgetInfo[2] + FramId,WidgetInfo[8] + Xpos,WidgetInfo[9] + Ypos);

	return;
}

function DrawTrainSelectWidgetsWithAni(obj,WidgetInfo,index,isOpen,Xpos,Ypos)
{
	local FramId = 0;
	local moshi = 1;
	local mousArea = [WidgetInfo[10], WidgetInfo[11], WidgetInfo[12], WidgetInfo[13]];

	if(IsTrainSelect[index])
		FramId = 2;
	if(isOpen && isMouseInScreenArea(obj,mousArea) && IsTrainSelect[index])
		FramId = 2;
	if(isOpen && isLeftMouseInAreaClick(obj,mousArea) && !IsLightWidgets(obj)) 
	{
		if(IsTrainSelect[index])
			IsTrainSelect[index] = false;
		else
			IsTrainSelect[index] = true;
		FramId = 2;
	}
	
	if(IsTrainSelect[2])
		TrainningRoomAbilityValue[12] = -100;
	else
		TrainningRoomAbilityValue[12] = 0;

	if(isOpen == false)
		Xpos = Xpos + 438;
	local sq_var = obj.getVar();
	local AniObj = sq_var.GetAnimationMap( WidgetInfo[0] , WidgetInfo[1] );
	sq_AnimationProc(AniObj);
	AniObj.setImageRate(WidgetInfo[3]*moshi, WidgetInfo[3]);
	AniObj.setRGBA(WidgetInfo[4], WidgetInfo[5], WidgetInfo[6], WidgetInfo[7]);
	sq_SetAnimationFrameIndex( AniObj, WidgetInfo[2] + FramId);
	sq_drawCurrentFrame(AniObj, WidgetInfo[8] + Xpos, WidgetInfo[9] + Ypos, false);
	return;
}


function DrawDropListButton(obj,WidgetInfo,Index,isOpen,Xpos,Ypos)
{
	local FramId = 0;
	local FramIdF = 0;
	local moshi = 1;
	local AniName = WidgetInfo[0];
	local AniPath = WidgetInfo[1];
	local mousArea = [WidgetInfo[10], WidgetInfo[11], WidgetInfo[12], WidgetInfo[13]];
	if(ButtonsFunctions[WidgetInfo[0]][1] != -1)
	{
		AniName = ButtonsFunctions[WidgetInfo[0]][2];
		AniPath = ButtonsFunctions[WidgetInfo[0]][3];
		FramIdF = ButtonsFunctions[WidgetInfo[0]][1];
		
	}
	else
	{
		FramIdF = WidgetInfo[2];
	}

	if(isOpen && isLeftMouseInAreaClick(obj,mousArea) && !IsLightWidgets(obj)) 
	{
		if( AniName == "SelectTip6" )
		{
			if(SingleTrainSelect != 0)
				return;
		}
		
		ButtonsFunctions[WidgetInfo[0]][1] = -1;
		ButtonsFunctions[WidgetInfo[0]][0] = true;
		
	}
	if(isOpen == false)
		Xpos = Xpos + 438;
	DrawTrainRoomAniUI(obj,AniName,AniPath,WidgetInfo[3],WidgetInfo[3],WidgetInfo[4],WidgetInfo[5],WidgetInfo[6],WidgetInfo[7],FramIdF,WidgetInfo[8] + Xpos,WidgetInfo[9] + Ypos);

	return;
}





function DrawTrainSelectDownWithAni(obj,WidgetInfoTwo,isOpen,Xpos,Ypos,key,backId)
{
	local AllCount = WidgetInfoTwo[2];
	for(local i = 0; i < AllCount; ++i) 
	{
		local Y = Ypos + (i+1)*(WidgetInfoTwo[12]-WidgetInfoTwo[11]);
		DrawSingleWidget(obj,WidgetInfoTwo,i,isOpen,Xpos,Y,key,backId);
	}

	return;
}

function DrawSingleWidget(obj,WidgetInfo,Frameindex,isOpen,Xpos,Ypos,key,backId)
{
	local arrRGB = [ WidgetInfo[5] ,WidgetInfo[6] ,WidgetInfo[7] ,WidgetInfo[8] ];
	local TempY = WidgetInfo[11] - WidgetInfo[12];
	local mousArea = [WidgetInfo[9], WidgetInfo[10], WidgetInfo[11] - TempY*Frameindex, WidgetInfo[12] - TempY*Frameindex];
	if(isMouseInScreenArea(obj,mousArea))
		arrRGB = [255,255,10,255];
	if(isOpen && isLeftMouseInAreaClick(obj,mousArea)) 
	{
		arrRGB = [10,255,255,255];
		ButtonsFunctions[key][0] = false;
		ButtonsFunctions[key][2] = WidgetInfo[0];
		ButtonsFunctions[key][3] = WidgetInfo[1];
		ButtonsFunctions[key][1] = Frameindex;
	}

	if(isOpen == false)
		Xpos = Xpos + 438;
	DrawTrainRoomAniUI(obj,SeveralSelectBackInfo[backId][0],SeveralSelectBackInfo[backId][1],SeveralSelectBackInfo[backId][3],SeveralSelectBackInfo[backId][4],arrRGB[0],arrRGB[1],arrRGB[2],arrRGB[3],21,Xpos,Ypos);

	DrawTrainRoomAniUI(obj,WidgetInfo[0],WidgetInfo[1],WidgetInfo[3],WidgetInfo[4],arrRGB[0],arrRGB[1],arrRGB[2],arrRGB[3],Frameindex,Xpos,Ypos)

	return;
}


function DrawTrainSelectDownWithAni2(obj,WidgetInfoTwo,isOpen,Xpos,Ypos,key,backId)
{
	local AllCount = WidgetInfoTwo[2];
	for(local i = 0; i < AllCount; ++i) 
	{
		local Y = Ypos + (i+1)*(WidgetInfoTwo[12]-WidgetInfoTwo[11]);
		DrawSingleWidget2(obj,WidgetInfoTwo,i,isOpen,Xpos,Y,key,backId);
	}

	return;
}


function DrawSingleWidget2(obj,WidgetInfo,Frameindex,isOpen,Xpos,Ypos,key,backId)
{
	local arrRGB = [ WidgetInfo[5] ,WidgetInfo[6] ,WidgetInfo[7] ,WidgetInfo[8] ];
	local TempY = WidgetInfo[12] - WidgetInfo[11];
	local mousArea = [WidgetInfo[9], WidgetInfo[10], WidgetInfo[11] + TempY*(Frameindex+1), WidgetInfo[12] + TempY*(Frameindex+1)];
	if(isMouseInScreenArea(obj,mousArea))
		arrRGB = [255,255,10,255];
	if(isOpen && isLeftMouseInAreaClick(obj,mousArea)) 
	{
		arrRGB = [10,255,255,255];
		ButtonsFunctions[key][0] = false;
		ButtonsFunctions[key][2] = WidgetInfo[0];
		ButtonsFunctions[key][3] = WidgetInfo[1];
		ButtonsFunctions[key][1] = Frameindex;
		if(key == "SelectTip10" && Frameindex > -1)
		{
			TrainningSetChrHp(obj,(Frameindex+1)*10);
		}
		if(key == "SelectTip11" && Frameindex > -1)
		{
			TrainningSetChrMp(obj,(Frameindex+1)*10);
		}
	}

	if(isOpen == false)
		Xpos = Xpos + 438;
	
	DrawTrainRoomAniUI(obj,SeveralSelectBackInfo[backId][0],SeveralSelectBackInfo[backId][1],SeveralSelectBackInfo[backId][3],SeveralSelectBackInfo[backId][4],arrRGB[0],arrRGB[1],arrRGB[2],arrRGB[3],21,Xpos,Ypos);
	
	DrawTrainRoomAniUI(obj,WidgetInfo[0],WidgetInfo[1],WidgetInfo[3],WidgetInfo[4],arrRGB[0],arrRGB[1],arrRGB[2],arrRGB[3],Frameindex,Xpos,Ypos);

	return;
}


function DrawTrainFightSettlement(obj,Xpos,Ypos)
{
	if(!IsTrainFighterSettlement || obj.getVar("TrainTestHitDamage").size_vector()<1)
		return;
	Ypos = Ypos - 100;
	

	local PhyDamage = obj.getVar("TrainTestHitDamage").get_vector(0);
	local MagDamage = obj.getVar("TrainTestHitDamage").get_vector(1);
	local AbsoluteDamage = obj.getVar("TrainTestHitDamage").get_vector(2);
	local TotleDamage = PhyDamage + MagDamage + AbsoluteDamage;
	if(IsTrainFighterSettlement && TraniningSummInfo[3] == -1)
	{
		local TrainStartTime = TraniningSummInfo[2];
		local CurTime = obj.getVar("TrainRoomTimeGet").get_vector(0);
		TraniningSummInfo[3] = CurTime;
		local TrainEndTime = CurTime;
		local LastMonsIndex = obj.getVar("TrainTestHitDamage").get_vector(3);
		local TrainTestTime = TrainEndTime-TrainStartTime;
		local aveDamage = (TotleDamage/(TrainTestTime/1000.0)).tointeger();
		
		local recordLine = [LastMonsIndex,TrainTestTime,PhyDamage,MagDamage,AbsoluteDamage,TotleDamage,aveDamage];
		TraniningLastRecord.append(recordLine);
	}

	

	
	local aniName = "TrainSettlement";
	local aniName2 = "TrainSettlement2";
	local AniTitle = "TrainSettlementTitle";
	local FenaniName = "TrainSettlementF";
	local AniPath1 = "map/trainingroom/trainingroomback.ani";
	local AniPathF = "map/trainingroom/trainingroomfighttime.ani";
	local Back2 = ControlsAniPath;
	local TitlePath = "map/trainingroom/damage_analyse.ani";
	local ButtonFramId = 5;
	
	local MoveArea = [Xpos,Xpos+451,Ypos,Ypos +18];  

	local areainfo = [Xpos+180,Xpos+253,Ypos +162,Ypos +186]; 
	if(isMouseInScreenArea(obj,areainfo))
		ButtonFramId = 6;
	if(isLeftMouseInAreaDown(obj,areainfo)) 
	{
		IsMouseDown = true;

		ButtonFramId = 7;
		IsTrainFighterSettlement = false;
		TraniningSummInfo = [-1,-1,-1,-1];
	}

	DrawTrainRoomAniUI2(obj,aniName,AniPath1,0.67,0.42,255,255,255,200,11,Xpos,Ypos);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,4.5,0.8,255,255,255,200,5,Xpos-3,Ypos);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,0,Xpos+189,Ypos);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId,Xpos+179,Ypos+160);
	DrawTrainRoomAniUI2(obj,"TrainQTip",ControlTipsAniPath,0.7,0.7,255,255,255,200,ButtonFramId + 72,Xpos+200,Ypos+161);

	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,5,Xpos+50,Ypos + 40);
	DrawTrainRoomSmallNumber(obj,TotleDamage,0.57,0.57,245,220,255,240,7,Xpos+213,Ypos+40);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,11,Xpos+50,Ypos +80);
	DrawTrainRoomSmallNumber(obj,PhyDamage,0.57,0.57,245,220,255,240,7,Xpos+213,Ypos+80);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,12,Xpos+50,Ypos +100);
	DrawTrainRoomSmallNumber(obj,MagDamage,0.57,0.57,245,220,255,240,7,Xpos+213,Ypos+100);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,13,Xpos+50,Ypos +120);
	DrawTrainRoomSmallNumber(obj,AbsoluteDamage,0.57,0.57,245,220,255,240,7,Xpos+213,Ypos+120);
	

	return;
}


function DrawTrainMonHitCondition(obj,Xpos,Ypos)
{
	if(!IsTrainSetHitCondition || !IsShowMainUI)
		return;

	local TrainBackSeclet = [
	                            "gSelectBack",
	                            "map/trainingroom/trainingroomback.ani"
	                        ]
	                        DrawTrainRoomAniUI(obj,TrainBackSeclet[0],TrainBackSeclet[1],0.17,0.25,255,255,255,200,11,Xpos,Ypos);



	local HitCondition	= [
	                          ["gSelect1",ControlsAniPath,13,1.0,255,255,255,255,18,20,271,344,172,184],	
	                          ["gSelect2",ControlsAniPath,13,1.0,255,255,255,255,18,50,271,321,203,213],	
	                          ["gSelect3",ControlsAniPath,13,1.0,255,255,255,255,18,80,271,346,232,245]	
	                      ]
	local HitConditionTip	=  [
	                          ["gSelectTip1",ControlTipsMonHit,0,0.57,255,255,255,255,40,16,271,344,172,184],	
	                          ["gSelectTip2",ControlTipsMonHit,4,0.57,255,255,255,255,40,46,271,321,203,213],	
	                          ["gSelectTip3",ControlTipsMonHit,8,0.57,255,255,255,255,40,76,341,346,232,245]	
	] 
	foreach(key,Arr in HitConditionTip)
	{
		local aniName = Arr[0];
		local AniPath = Arr[1];
		local Xrate = Arr[3];
		local R = Arr[4];
		local G = Arr[5];
		local B = Arr[6];
		local alpaha = Arr[7];
		local FramIndex = Arr[2];
		local X = Xpos + Arr[8];
		local Y = Ypos + Arr[9];
		local FramId = 0;
		local mousArea = [Arr[10],Arr[11],Arr[12],Arr[13]];
		
		DrawTrainRoomAniUI(obj,aniName,AniPath,Xrate,Xrate,R,G,B,alpaha,FramIndex,X,Y);
	}	
	foreach(key,Arr in HitCondition)
	{
		local aniName = Arr[0];
		local AniPath = Arr[1];
		local Xrate = Arr[3];
		local R = Arr[4];
		local G = Arr[5];
		local B = Arr[6];
		local alpaha = Arr[7];
		local FramIndex = Arr[2];
		local X = Xpos + Arr[8];
		local Y = Ypos + Arr[9];
		local FramId = 0;
		local mousArea = [Arr[10],Arr[11],Arr[12],Arr[13]];
		if(isLeftMouseInAreaDown(obj,mousArea) && key < 3) 
		{
			if(!TrainSetHitCondition[key] && !IsMouseDown){
				IsMouseDown = true ;
				TrainSetHitCondition[key] = true;
			}
			else if(TrainSetHitCondition[key] && !IsMouseDown){
				IsMouseDown = true ;
				TrainSetHitCondition[key] = false;
			}
		}
		if(TrainSetHitCondition[key])
			FramId = 2;
		DrawTrainRoomAniUI(obj,aniName,AniPath,Xrate,Xrate,R,G,B,alpaha,FramIndex + FramId,X,Y);
	}
	return;
}


function DrawTrainFightRecord(obj,Xpos,Ypos)
{
	if(!IsTrainFighterRecord)
		return;
	
	Ypos = Ypos - 200;
	local Size = 0.48;
	local space = 6;
	local aniName = "TrainSettlement";
	local aniName2 = "TrainSettlement2";
	local AniTitle2 = "TrainRecordTitle2";
	local AniTitle = "TrainRecordTitle";
	local AniPath1 = "map/trainingroom/trainingroomback.ani";
	local Back2 = ControlsAniPath;
	local TitlePath = "map/trainingroom/challenge_record.ani";
	local TitlePath2 = "map/trainingroom/damage_analyse.ani";
	local ButtonFramId = 5;
	local ButtonFramId2 = 5;
	
	local MoveArea = [Xpos + 312,Xpos + 312+451,Ypos+100,Ypos+100 +18];  

	local areainfo = [Xpos + 312+250,Xpos + 312+323,Ypos+110 +362,Ypos+110 +386]; 
	local areainfo2 = [Xpos + 312+21,Xpos + 406,Ypos+110 +362,Ypos+110 +386]; 
	if(isMouseInScreenArea(obj,areainfo))
		ButtonFramId = 6;
	if(isLeftMouseInAreaDown(obj,areainfo)) 
	{
		ButtonFramId = 7;
		IsTrainFighterRecord = false;
	}
	
	if(isMouseInScreenArea(obj,areainfo2))
		ButtonFramId2 = 6;
	if(isLeftMouseInAreaDown(obj,areainfo2)) 
	{
		ButtonFramId2 = 7;
		TraniningLastRecord = [];
		
	}

	DrawTrainRoomAniUI2(obj,aniName,AniPath1,0.9,0.85,255,255,255,200,11,Xpos + 312,Ypos+100);
	DrawTrainRoomAniUI2(obj,aniName,AniPath1,0.83,0.66,255,255,255,255,11,Xpos + 312 + 21,Ypos+100+30);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,6.0,0.8,255,255,255,200,5,Xpos + 312-3,Ypos+100);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,0,Xpos + 568,Ypos+100);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId,Xpos + 312+250,Ypos+470);
	DrawTrainRoomAniUI2(obj,"TrainQTip",ControlTipsAniPath,0.7,0.7,255,255,255,200,ButtonFramId + 72,Xpos + 312+270,Ypos+471);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId2,Xpos +333,Ypos+470);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.7,0.7,255,255,255,200,6,Xpos + 353,Ypos+471);

	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,1,Xpos + 312+40,Ypos+100 + 40);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,2,Xpos + 312+110,Ypos+100 +40);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,11,Xpos + 312+185,Ypos+100 +40);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,12,Xpos + 312+265,Ypos+100 +40);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,13,Xpos + 312+340,Ypos+100 +40);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,3,Xpos + 312+410,Ypos+100 +40);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.6,0.6,255,255,255,200,4,Xpos + 312+475,Ypos+100 +40);
	

	local data = [
		[2021402,5000,95254,15444,1525,5486,1521],
		[2021403,15000,252959596,1002,25295959,262959596,26295959],
		[2021407,5000,25295959,1040,2529959,26299596,2629559],
		[56923,30000,125295959,1300,12529959,136299596,26229559],
		[2021407,15000,252959596,1002,25295959,262959596,26295959],
		[56923,5000,25295959,1040,2529959,26299596,2629559],
		[2021407,30000,125295959,1300,12529959,136299596,26229559],
		[56923,5000,25295959,1040,2529959,26299596,2629559],
		[2021407,30000,125295959,1300,12529959,136299596,26229559],
		[56923,5000,25295959,1040,2529959,26299596,2629559],
		[2021407,30000,125295959,1300,12529959,136299596,26229559]
	]
	
	
	local DataLen = TraniningLastRecord.len();
	if(DataLen<1)
		return;
	local page = DataLen/9+1;
	if(DataLen%9==0)
		--page;	
	
	
	local PageNum = TrainSelectPagrNum;
	local startN = PageNum*9;
	local EndN = startN + 9;
	if(EndN > TraniningLastRecord.len())
		EndN = TraniningLastRecord.len();
	local NewDatas = TraniningLastRecord.slice( startN ,EndN ); 
	
	foreach(key ,DataArr in NewDatas)
	{
		DrawTrainFightRecordLine(obj,DataArr,Xpos,Ypos + 30*key,Size,space);
	}
	
	

	local WidGetInfo1 = [1.0,1.0,255,255,255,255,page];
	DrawTrainFightTrainTuenPageButton(obj,WidGetInfo1,360,430,1.0,7);
	return;
}


function DrawTrainFightRecordLine(obj,DataArr,Xpos,Ypos,Size,space)
{
	local aniName = "TrainMonIcons";
	local AniPath = "map/trainingroom/trainingroommonicons.ani";
	local Xrate = 1.0;
	local FramIndex = TrainMonIcons[DataArr[0]];
	DrawTrainRoomAniUI(obj,aniName,AniPath,Xrate,Xrate,255,255,255,255,FramIndex,Xpos+357,Ypos+175);
	TrainningDrawTimeCount(obj,DataArr[1],0.5,255,255,255,255,5,Xpos,Ypos);
	DrawTrainRoomSmallNumber(obj,DataArr[2],Size,Size,245,220,255,240,space,Xpos + 512,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[3],Size,Size,245,220,255,240,space,Xpos + 592,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[4],Size,Size,245,220,255,240,space,Xpos + 667,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[5],Size,Size,245,220,255,240,space,Xpos + 742,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[6],Size,Size,245,220,255,240,space,Xpos + 818,Ypos+180);
	return;
}

function DrawTrainFightTrainTuenPageButton(obj,WidGetInfo,Xpos,Ypos,Size,space)
{
	
	local ButtonaniName = "TrainTuenPageButton";
	local ButtonAniPath = "map/trainingroom/trainingroombuttons.ani";
	
	local NumaniName = "TrainTuenPageNum";
	local NumAniPath = "map/trainingroom/damage_analyse.ani";
	
	local Xrate = WidGetInfo[0];
	local Yrate = WidGetInfo[1];
	local R = WidGetInfo[2];
	local G = WidGetInfo[3];
	local B = WidGetInfo[4];
	local ALPHA = WidGetInfo[5];
	local TotlePage = WidGetInfo[6];
	
	local SelectNum1 = 1;
	local SelectSlice = 0;
	local SelectNum2 = 2;
	local FramIndex1 = 22;
	local FramIndex2 = 26;
	local AddFram = 0;
	local AddFram2 = 0;

	local areainfo1 = [Xpos,Xpos+14,Ypos,Ypos+10]; 
	if(isMouseInScreenArea(obj,areainfo1))
		AddFram = 1;
	if(isLeftMouseInAreaDown(obj,areainfo1)) 
	{
		AddFram = 2;
		if(TrainSelectPagrNum+1>1 && !IsMouseDown)
			TrainSelectPagrNum = TrainSelectPagrNum -1;
		IsMouseDown = true;
		
	}

	local areainfo2 = [Xpos+70,Xpos+84,Ypos,Ypos+10]; 
	if(isMouseInScreenArea(obj,areainfo2))
		AddFram2 = 1;
	if(isLeftMouseInAreaDown(obj,areainfo2)) 
	{
		AddFram2 = 2;
		if(TrainSelectPagrNum+1<TotlePage && !IsMouseDown)
			TrainSelectPagrNum = TrainSelectPagrNum + 1;
		IsMouseDown = true;
		
		
	}
	DrawTrainRoomAniUI(obj,ButtonaniName,ButtonAniPath,Xrate,Yrate,R,G,B,ALPHA,FramIndex1+AddFram,Xpos,Ypos);
	DrawTrainRoomAniUI(obj,ButtonaniName,ButtonAniPath,Xrate,Yrate,R,G,B,ALPHA,FramIndex2+AddFram2,Xpos+70,Ypos);
	TrainDrawNum(obj , TrainSelectPagrNum+1 , Xpos +30 , Ypos-5 ,1);
	TrainDrawNum(obj , TotlePage , Xpos +38 , Ypos-5 ,0);
	DrawTrainRoomAniUI2(obj,NumaniName,NumAniPath,1.0,1.0,255,255,255,255,70,Xpos+30,Ypos-6);
	
	return;
}



function DrawTrainFightAnalyse(obj,Xpos,Ypos)
{
	if(!IsTrainSkilllAnalyse)
		return;
	
	Ypos = Ypos - 200;
	local Size = 0.52;
	local space = 6;
	local aniName = "TrainSettlement";
	local aniName2 = "TrainSettlement2";
	local AniTitle2 = "TrainRecordTitle2";
	local AniTitle = "TrainRecordTitle";
	local AniPath1 = "map/trainingroom/trainingroomback.ani";
	local Back2 = ControlsAniPath;
	local TitlePath = "map/trainingroom/challenge_record.ani";
	local TitlePath2 = "map/trainingroom/damage_analyse.ani";
	local ButtonFramId = 5;
	local ButtonFramId2 = 5;
	local ButtonFramId3 = 5;
	
	local MoveArea = [Xpos + 312,Xpos +763,Ypos+100,Ypos+118];  

	local areainfo = [Xpos +562,Xpos +635,Ypos+472,Ypos+496]; 
	local areainfo2 = [Xpos +333,Xpos + 406,Ypos+472,Ypos+496]; 
	local areainfo3 = [Xpos +792,Xpos + 865,Ypos+472,Ypos+496]; 
	local yDs1 = 0;
	local yDs2 = 0;
	if(isMouseInScreenArea(obj,areainfo))
		ButtonFramId = 6;
	if(isLeftMouseInAreaDown(obj,areainfo)) 
	{
		ButtonFramId = 7;
		IsTrainSkilllAnalyse = false;
	}
	
	if(isMouseInScreenArea(obj,areainfo3))
		ButtonFramId3 = 6;
	
	if(isMouseInScreenArea(obj,areainfo2))
		ButtonFramId2 = 6;
	if(isLeftMouseInAreaDown(obj,areainfo2)) 
	{
		ButtonFramId2 = 7;
		yDs2 = 1;
		
		TrainSkilllPageNum = 0;
		TrainReset();
		TrainChrOldSkillId = -1;
		TrainChrCurSkillId = -1;
		TrainTempOldSkillId = -1;
		TrainMonHpPer = -1;
	}

	DrawTrainRoomAniUI2(obj,aniName,AniPath1,0.9,0.85,255,255,255,200,11,Xpos + 312,Ypos+100);
	DrawTrainRoomAniUI2(obj,aniName,AniPath1,0.83,0.66,255,255,255,255,11,Xpos + 312 + 21,Ypos+100+30);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,6.0,0.8,255,255,255,200,5,Xpos + 312-3,Ypos+100);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,0,Xpos + 568,Ypos+100);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId,Xpos +562,Ypos+470);
	DrawTrainRoomAniUI2(obj,"TrainQTip",ControlTipsAniPath,0.7,0.7,255,255,255,200,ButtonFramId + 72,Xpos + 312+270,Ypos+471);
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId2,Xpos +333,Ypos+470);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.7,0.7,255,255,255,200,6,Xpos + 353,Ypos+471+yDs2);

	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,3,Xpos + 370,Ypos+140);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,4,Xpos + 450,Ypos+140);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,5,Xpos + 575,Ypos+140);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,6,Xpos + 670,Ypos+140);
	DrawTrainRoomAniUI2(obj,AniTitle2,TitlePath2,0.6,0.6,255,255,255,200,7,Xpos + 770,Ypos+140);
	

	local data = [
		[243,1,95254,95254,88.8],
		[20,2,12554,12502,50],
		[22,2,12554,12502,50],
		[21,2,12554,12502,50],
		[100,2,12554,12502,50],
		[50,2,12554,12502,50],
		[22,2,12554,12502,50],
		[21,2,12554,12502,50],
		[100,2,12554,12502,50],
		[50,2,12554,12502,50]
	]
	
	local NewDataArr = [];
	local ToTalDamage = 0;
	local SkillCount = 0;
	foreach(Arr in TrainSkillDamage)
	{
		if(Arr[1]<0)
			Arr[1] = 0;
		ToTalDamage = ToTalDamage + Arr[1];
	}
	foreach(key ,Arr in TrainSkillDamage)
	{
		local TempAr = [];
		if(Arr[0]>0)
		{
			++SkillCount;
			local ToDamage = Arr[1];
			local AveDamage = ToDamage/Arr[0];
			local Per = ToDamage*100.0/ToTalDamage;
			Per = (Per*100).tointeger()/100.0
			TempAr.push(key);
			TempAr.push(Arr[0]);
			TempAr.push(ToDamage);
			TempAr.push(AveDamage);
			TempAr.push(Per);
		}
		if(TempAr.len()>0)
			NewDataArr.push(TempAr);
	}
	if(SkillCount<1)
		return;

	
	
	local DataLen = NewDataArr.len();
	if(DataLen<1)
		return;
	local page = DataLen/9+1;
	if(DataLen%9==0)
		--page;	
	
	
	if(DataLen<10)
		TrainSkilllPageNum = 0;
	local PageNum = TrainSkilllPageNum;
	local startN = PageNum*9;
	local EndN = startN + 9;
	if(EndN > NewDataArr.len())
	{
		EndN = NewDataArr.len();
	}
	
	local NewDatas = NewDataArr.slice( startN ,EndN ); 
	
	foreach(key ,DataArr in NewDatas)
	{
		DrawTrainFightSkillAnalyseLine(obj,DataArr,Xpos,Ypos + 30*key,Size,space);
	}
	
	

	local WidGetInfo1 = [1.0,1.0,255,255,255,255,page];
	DrawTrainSkillAnalyseTuenPageButton(obj,WidGetInfo1,360,430,1.0,7);
	if(isLeftMouseInAreaDown(obj,areainfo3)) 
	{
		ButtonFramId3 = 7;
		yDs1 = 1;
		if(!IsMouseDown)
		{
			IsMouseDown = true;	
			TrainPrintTxtMain(obj,NewDatas);
		}
	}
	DrawTrainRoomAniUI2(obj,aniName2,Back2,0.8,1.1,255,255,255,200,ButtonFramId3,Xpos +792,Ypos+470);
	DrawTrainRoomAniUI2(obj,AniTitle,TitlePath,0.7,0.7,255,255,255,200,5,Xpos + 797,Ypos+471+yDs1);
	return;
}


function DrawTrainFightSkillAnalyseLine(obj,DataArr,Xpos,Ypos,Size,space)
{
	local SklIcon = sq_GetSkill(obj, DataArr[0]);
	local Alpha = sq_ALPHA(255);
	sq_DrawSkillIcon(SklIcon, Xpos + 372, Ypos+175, Alpha);
	DrawTrainRoomSmallNumber(obj,DataArr[1],Size,Size,245,220,255,240,space,Xpos + 480,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[2],Size,Size,245,220,255,240,space,Xpos + 597,Ypos+180);
	DrawTrainRoomSmallNumber(obj,DataArr[3],Size,Size,245,220,255,240,space,Xpos + 699,Ypos+180);
	
	TrainDrawNum(obj, DataArr[4] ,Xpos + 791,Ypos+175,2);
	return;
}


function DrawTrainSkillAnalyseTuenPageButton(obj,WidGetInfo,Xpos,Ypos,Size,space)
{
	
	local ButtonaniName = "TrainTuenPageButton";
	local ButtonAniPath = "map/trainingroom/trainingroombuttons.ani";
	
	local NumaniName = "TrainTuenPageNum";
	local NumAniPath = "map/trainingroom/damage_analyse.ani";
	
	local Xrate = WidGetInfo[0];
	local Yrate = WidGetInfo[1];
	local R = WidGetInfo[2];
	local G = WidGetInfo[3];
	local B = WidGetInfo[4];
	local ALPHA = WidGetInfo[5];
	local TotlePage = WidGetInfo[6];
	
	local SelectNum1 = 1;
	local SelectSlice = 0;
	local SelectNum2 = 2;
	local FramIndex1 = 22;
	local FramIndex2 = 26;
	local AddFram = 0;
	local AddFram2 = 0;

	local areainfo1 = [Xpos,Xpos+14,Ypos,Ypos+10]; 
	if(isMouseInScreenArea(obj,areainfo1))
		AddFram = 1;
	if(isLeftMouseInAreaDown(obj,areainfo1)) 
	{
		AddFram = 2;
		if(TrainSkilllPageNum+1>1 && !IsMouseDown)
			TrainSkilllPageNum = TrainSkilllPageNum -1;
		IsMouseDown = true;
		
	}

	local areainfo2 = [Xpos+70,Xpos+84,Ypos,Ypos+10]; 
	if(isMouseInScreenArea(obj,areainfo2))
		AddFram2 = 1;
	if(isLeftMouseInAreaDown(obj,areainfo2)) 
	{
		AddFram2 = 2;
		if(TrainSkilllPageNum+1<TotlePage && !IsMouseDown)
			TrainSkilllPageNum = TrainSkilllPageNum + 1;
		IsMouseDown = true;
		
		
	}
	DrawTrainRoomAniUI(obj,ButtonaniName,ButtonAniPath,Xrate,Yrate,R,G,B,ALPHA,FramIndex1+AddFram,Xpos,Ypos);
	DrawTrainRoomAniUI(obj,ButtonaniName,ButtonAniPath,Xrate,Yrate,R,G,B,ALPHA,FramIndex2+AddFram2,Xpos+70,Ypos);
	TrainDrawNum(obj , TrainSkilllPageNum+1 , Xpos +30 , Ypos-5 ,1);
	TrainDrawNum(obj , TotlePage , Xpos +38 , Ypos-5 ,0);
	DrawTrainRoomAniUI2(obj,NumaniName,NumAniPath,1.0,1.0,255,255,255,255,70,Xpos+30,Ypos-6);
	
	return;
}

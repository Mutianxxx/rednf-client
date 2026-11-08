function setCustomData_po_fluorecolliderstart(obj, receiveData)
{
	if(!obj)
		return;		
}

function procAppend_po_fluorecolliderstart(obj)
{

	if(!obj) return;
	if(!obj.isMyControlObject())
	  return;
	
	local parentChr = obj.getTopCharacter();//ÊÇßä
	
	
	local fluorecollider = parentChr.getMyPassiveObject(90010009, 0);
	local fluorecolliderhit = parentChr.getMyPassiveObject(24303, 0);
	//if(!fluorecolliderhit&&fluorecollider) {
		local fx = parentChr.getXPos();
		local fy = parentChr.getYPos(); //Íªß©ĞüÒöüùÍı?Óßñ¦øö£¬ì¤øµñıı¨óÜËïîÜĞüÒöüùÍıêÈöÇÍ³ïÒ
		sq_BinaryWriteDword(60);
		sq_SendCreatePassiveObjectPacketPos( parentChr, 24303, 0, fx, fy, 0);
				//óÜËïĞüÒöüùÍı
	//}
	return;

}

function onTimeEvent_po_fluorecolliderstart(obj, timeEventIndex, timeEventCount)
{		
	if(!obj)
		return false;
	return false;	
} 


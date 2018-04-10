#include "MotionTableEntry.h"



MotionTableEntry::MotionTableEntry(string direct, int destRoomNum, string deniedA, string symb)
{
	direction = direct;
	destinationRoomNum = destRoomNum;
	deniedAccess = deniedA;
	symbol = symb;
}


MotionTableEntry::~MotionTableEntry()
{
}

string MotionTableEntry::getDirection()
{
	return direction;
}
int MotionTableEntry::getDestination()
{
	return destinationRoomNum;
}
string MotionTableEntry::getDeniedAccess()
{
	return deniedAccess;
}
string MotionTableEntry::getSymbol() {
	return symbol;
}

bool MotionTableEntry::getHidden()
{
	return isHidden;
}
void MotionTableEntry::setHidden(bool hid)
{
	isHidden = hid;
}
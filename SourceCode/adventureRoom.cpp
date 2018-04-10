#include "adventureRoom.h"



adventureRoom::adventureRoom(int numb, string name, int eventNum)
{
	roomNumb = numb;
	roomName = name;
	eventType = eventNum;
	eventHasHappened = false;
}


adventureRoom::~adventureRoom()
{
}

string adventureRoom::getName()
{
	return roomName;
}

bool adventureRoom::getActive()
{
	return isActive;
}

void adventureRoom::setActive(bool active)
{

	isActive = active;

}
bool adventureRoom::getEventStatus()
{
	return eventHasHappened;
}

void adventureRoom::setEventStatus(bool status)
{

	eventHasHappened = status;

}

int adventureRoom::getEventType()
{
	return eventType;

}



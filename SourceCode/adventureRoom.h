#pragma once
#include "Object.h"
#include "MotionTableEntry.h"
#include <vector>
#include "Enemy.h"


class adventureRoom
{
private:
	int roomNumb;
	int eventType;
	string roomName;
	bool isActive;
	bool eventHasHappened;

public:
	adventureRoom(int numb, string name, int eventNum);
	~adventureRoom();
	string getName();
	bool getActive();
	void setActive(bool active);
	bool getEventStatus();
	void setEventStatus(bool status);
	int getEventType();
	Enemy* enemy;
	vector<Object*> roomObjects;
	vector<MotionTableEntry*> motionTable;
	vector<string>roomDescription;
	vector<string>roomDescription2;


};


#pragma once
#include "Object.h"
#include <vector>

class MotionTableEntry
{
private:
	string direction;
	int destinationRoomNum;
	string deniedAccess;
	string symbol;
	bool isHidden;


public:
	MotionTableEntry(string direction, int destinationRoomNum, string deniedA, string symbol);
	~MotionTableEntry();
	vector<Object*> requiredObjects;
	string getDirection();
	int getDestination();
	string getDeniedAccess();
	string getSymbol();
	bool getHidden();
	void setHidden(bool hid);
};


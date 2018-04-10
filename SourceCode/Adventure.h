#pragma once
#include <iostream>

#include <string>
#include <vector>
#include "adventureRoom.h"
#include "Object.h"
#include <time.h>
#include <fstream>
#include "color.h"
#include "Player.h"
#include <algorithm>
#include <sstream>
#include "MotionTableEntry.h"
#include "Enemy.h"

using namespace std;
class Player;

class Adventure
{
private:
	vector<adventureRoom*> myRooms;
	bool restart;
	bool soundIsPlaying;
	bool musicIsOn;
	void Battle(Player *generalStyrax, Enemy* enemy, color color);

public:


	Adventure();
	~Adventure();
	bool run(Player* generalStyrax, color color);
	void readFile(ifstream& myDataFile);
	void setRestart(bool re);
	bool getRestart();
	void deleteRooms();
	void playMusic(int location);
};



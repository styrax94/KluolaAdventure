#include "Adventure.h"
#pragma comment(lib,"winmm.lib")




Adventure::Adventure()
{
	restart = true;
	soundIsPlaying = false;
	musicIsOn = true;
}


Adventure::~Adventure()
{

}

void Adventure::setRestart(bool re)
{
	restart = re;
}
bool Adventure::getRestart()
{
	return restart;
}
void Adventure::playMusic(int location)
{
	if (musicIsOn)
	{
		switch (location)
		{
		case 0:
		{
			if (!soundIsPlaying)
			{
				PlaySound(TEXT("music\\Syberia-melancholic-ambient-music.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
				soundIsPlaying = true;
			}

			break;
		}
		case 1:
		{
			if (!soundIsPlaying)
			{
				PlaySound(TEXT("music\\Into_Battle_4.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
				soundIsPlaying = true;
			}

			break;
		}
		case 2:
		{
			if (!soundIsPlaying)
			{
				PlaySound(TEXT("music\\Mysterious-synth-pad-104-bpm.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
				soundIsPlaying = true;
			}
			break;
		}
		case 3:
		{
			if (!soundIsPlaying)
			{
				PlaySound(TEXT("music\\Creepy_Hollow.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
				soundIsPlaying = true;
			}
			break;
		}

		case 5:
		{
			if (!soundIsPlaying)
			{
				PlaySound(TEXT("music\\Dark-Things-2.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
				soundIsPlaying = true;
			}
			break;
		}
		}

	}
	else
	{
		PlaySound(NULL, 0, 0);
		soundIsPlaying = false;
	}

}
void Adventure::Battle(Player *generalStyrax, Enemy* enemy, color color)
{
	if (musicIsOn)
		PlaySound(TEXT("music\\Battle_Lines.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
	bool playerTurn = true;
	bool ifDefended = false;
	bool specialAttack = false;
	int countForSpecial = 0;
	bool battleEnded = false;
	bool needRefresh = true;
	bool hasFallen = false;
	int command;
	int attackDmg;

	while (!battleEnded)
	{

		if (generalStyrax->getHealth() == 0 || enemy->getHealth() == 0)
		{
			needRefresh = true;
			hasFallen = true;
		}


		if (needRefresh)
		{
			;
			system("cls");
			color.setcolor(color.dark_green, color.black);
			cout << "==================================================================================================" << endl;
			cout << "General Styrax" << "                                                          " << enemy->getName() << endl;
			cout << "Health  : " << generalStyrax->getHealthS() << "                                                         " << "Health: " << enemy->getHealthS() << endl;
			cout << "Attack  : " << generalStyrax->getAttackS() << "                                                         " << "Attack:  " << enemy->getAttackDamageS() << endl;
			cout << "Defense : " << generalStyrax->getDefenseS() << "                                                         " << "Defense: " << enemy->getDefenseS() << endl;
			cout << "==================================================================================================" << endl;
			color.setcolor(color.red, color.black);

			cout << "Enter Battle mode :" << endl << endl;
			needRefresh = false;
		}

		if (hasFallen)
		{

			if (generalStyrax->getHealth() == 0)
			{
				generalStyrax->styraxHasFallen();

				cout << endl;
				cout << "The battle has ended" << endl;
				cout << enemy->getVictory();
				cout << endl;
				battleEnded = true;
				PlaySound(NULL, 0, 0);
				system("pause");
				break;

			}
			else if (enemy->getHealth() == 0 && enemy->bossSpecial() == 1)
			{

				cout << enemy->getDefeated() << endl << endl;
				cout << "You have obtained: " << endl;

				for (int i = 0; i < enemy->getItemVector().size(); i++)
				{

					cout << enemy->getItemVector()[i]->getType() << endl;
					generalStyrax->inventory.push_back(enemy->getItemVector()[i]);
				}

				cout << "The battle has ended" << endl;
				battleEnded = true;
				enemy->killEnemy();
				cout << endl;
				if (myRooms[generalStyrax->getLocation() - 1]->getEventType() == 2)
					myRooms[generalStyrax->getLocation() - 1]->setEventStatus(true);
				break;
			}
			else if (enemy->getHealth() == 0 && enemy->bossSpecial() == 2)
			{

				cout << enemy->getDefeated() << endl << endl;

				cout << "The battle has ended" << endl;
				battleEnded = true;
				enemy->killEnemy();
				cout << endl;
				generalStyrax->setVictory();

				break;
			}


		}



		if (playerTurn)
		{
			cout << "Choose the number of your Desired Command: " << endl << "[0]: Attack" << endl << "[1]: Defend" << endl;
			playerTurn = false;

			cin >> command;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			Sleep(1000);

			if (command == 0)
			{
				attackDmg = generalStyrax->getAttack() - enemy->getDefense();
				if (attackDmg < 0)
				{
					attackDmg = 0;
				}
				enemy->getDamaged(attackDmg);
				if (enemy->getHealth() == 0)
				{
					cout << "You attacked and defeated your enemy!" << endl;
					system("PAUSE");

				}
				else  cout << "You attacked the enemy! You have dealt " << attackDmg << " damage!" << endl;

			}
			else if (command == 1)
			{
				ifDefended = true;
				cout << "You have braced yourself for an attack." << endl;


			}
			else
			{
				cout << "That is not a proper Battle command." << endl;
				system("PAUSE");
				playerTurn = true;
				needRefresh = true;

			}
		}
		else
		{
			Sleep(1500);
			if (enemy->isAlive() && enemy->bossSpecial() == 1)
			{
				attackDmg = enemy->getAttackDamage() - generalStyrax->getDefense();
				if (attackDmg < 0)
				{
					attackDmg = 0;
				}

				if (ifDefended)
				{
					if (attackDmg > 2)
					{
						attackDmg = 2;
					}
					generalStyrax->getDamaged(attackDmg);
					ifDefended = false;
					cout << enemy->getName() << " has Attacked you! You braced through the attack and only suffered " << attackDmg << " damage!" << endl;
				}
				else
				{
					generalStyrax->getDamaged(attackDmg);
					cout << enemy->getName() << " has Attacked you! You have suffered " << attackDmg << " damage!" << endl;
				}

			}
			else
			{
				attackDmg = enemy->getAttackDamage() - generalStyrax->getDefense();
				if (attackDmg < 0)
				{
					attackDmg = 0;
				}
				if (specialAttack)
				{
					cout << "Goblin King: Special Attack-> King SMASH" << endl;
					attackDmg = attackDmg * 2;
					specialAttack = false;
				}
				else countForSpecial++;

				if (ifDefended)
				{
					if (attackDmg > 2)
					{
						attackDmg = 2;
					}
					generalStyrax->getDamaged(attackDmg);
					ifDefended = false;
					cout << enemy->getName() << " has Attacked you! You braced through the attack and only suffered " << attackDmg << " damage!" << endl;
				}
				else
				{
					generalStyrax->getDamaged(attackDmg);
					cout << enemy->getName() << " has Attacked you! You have suffered " << attackDmg << "  damage!" << endl;

				}



				if (countForSpecial == 2)
				{
					specialAttack = true;
					countForSpecial = 0;
				}

			}
			playerTurn = true;
			needRefresh = true;
			system("PAUSE");
		}



	}
}

void Adventure::readFile(ifstream& myDataFile)
{

	int numberOfRooms;
	myDataFile >> numberOfRooms;

	for (int size = 0; size < numberOfRooms; size++)
	{
		int roomNumb, currentInt, descriptionRepeat, eventNumber;
		string roomName, direction, symbol;
		string roomDescription, dialogueDescription, deniedAccessDesc;
		string currentLine;
		MotionTableEntry *motion = NULL;
		Enemy * myEnemy = NULL;
		vector<MotionTableEntry*>motionVector;

		myDataFile >> roomNumb;
		myDataFile >> eventNumber;
		//reads in info to create a room
		do
		{
			myDataFile >> currentLine;

			if (currentLine != "****")
				roomName += currentLine + " ";

		} while (currentLine != "****");
		adventureRoom *room = new adventureRoom(roomNumb, roomName, eventNumber);

		//Used to read in two sets of room descriptions
		myDataFile >> descriptionRepeat;
		for (int d = 0; d < descriptionRepeat; d++)
		{
			do
			{
				myDataFile >> currentLine;

				if (currentLine != "****")
				{
					roomDescription += currentLine + " ";

				}
			} while (currentLine != "****");

			if (d == 0)
			{
				room->roomDescription.push_back(roomDescription);
			}
			else room->roomDescription2.push_back(roomDescription);

			roomDescription = "";
			myDataFile >> currentInt;


			if (currentInt == 1)
			{
				do
				{
					myDataFile >> currentLine;

					if (currentLine != "****" && currentLine != "+")
					{
						dialogueDescription += currentLine + " ";
					}
					if (currentLine == "+")
					{
						if (d == 0)
							room->roomDescription.push_back(dialogueDescription);
						else room->roomDescription2.push_back(dialogueDescription);
						dialogueDescription = "";
					}


				} while (currentLine != "****");
			}
		}

		//reads in if the room should be active at the start or not
		myDataFile >> currentInt;
		if (currentInt == 2)
		{
			room->setActive(true);

		}
		else room->setActive(false);

		//reads in all possible directions for the room and their conditions
		do
		{

			myDataFile >> currentLine;

			if (currentLine != "****")
			{
				direction = currentLine;

				myDataFile >> currentInt;

				myDataFile >> symbol;

				while (currentLine != "===" && currentLine != "****")
				{
					myDataFile >> currentLine;

					if (currentLine != "===" && currentLine != "****")
					{
						deniedAccessDesc += currentLine + " ";
					}

				}


				motion = new MotionTableEntry(direction, currentInt, deniedAccessDesc, symbol);

				if (roomNumb == motion->getDestination())
				{
					motion->setHidden(true);

				}
				else motion->setHidden(false);

				motionVector.push_back(motion);
				deniedAccessDesc = "";

			}

		} while (currentLine != "****");

		//reads in the objects in the room and their attributes
		do
		{

			myDataFile >> currentLine;

			if (currentLine == "<>")
			{

				myDataFile >> currentLine;

				string name;
				string description;
				string type;
				int attribute;

				if (currentLine == "SWORD")
				{
					type = currentLine;

					while (currentLine != "===")
					{
						myDataFile >> currentLine;

						if (currentLine != "===")
							name += currentLine + " ";
					}

					do
					{
						myDataFile >> currentLine;


						if (currentLine != "===")
							description += currentLine + " ";

					} while (currentLine != "===");

					myDataFile >> attribute;
					myDataFile >> currentLine;
					if (currentLine == "+" || currentLine == "<" || currentLine == "V" || currentLine == ">")
					{
						Object *item = new Sword(name, description, type, attribute);
						room->roomObjects.push_back(item);
						for (int count = 0; count < motionVector.size(); count++)
						{
							if (currentLine == motionVector[count]->getSymbol())
								motionVector[count]->requiredObjects.push_back(item);
						}


					}
					else
					{
						Object *item = new Sword(name, description, type, attribute);
						room->roomObjects.push_back(item);

					}


				}
				else if (currentLine == "SHIELD")
				{
					type = currentLine;
					while (currentLine != "===")
					{
						myDataFile >> currentLine;

						if (currentLine != "===")
							name += currentLine + " ";
					}

					do
					{
						myDataFile >> currentLine;


						if (currentLine != "===")
							description += currentLine + " ";

					} while (currentLine != "===");

					myDataFile >> attribute;
					myDataFile >> currentLine;

					if (currentLine == "+" || currentLine == "<" || currentLine == "V" || currentLine == ">")
					{
						Object *item = new Shield(name, description, type, attribute);
						room->roomObjects.push_back(item);
						for (int count = 0; count < motionVector.size(); count++)
						{
							if (currentLine == motionVector[count]->getSymbol())
								motionVector[count]->requiredObjects.push_back(item);
						}

					}
					else
					{
						Object *item = new Shield(name, description, type, attribute);
						room->roomObjects.push_back(item);

					}
				}
				else if (currentLine == "ORB")
				{

					type = currentLine;
					while (currentLine != "===")
					{
						myDataFile >> currentLine;

						if (currentLine != "===")
							name += currentLine + " ";
					}

					do
					{
						myDataFile >> currentLine;


						if (currentLine != "===")
							description += currentLine + " ";

					} while (currentLine != "===");

					myDataFile >> attribute;
					myDataFile >> currentLine;

					if (currentLine == "+" || currentLine == "<" || currentLine == "V" || currentLine == ">")
					{
						Object *item = new Orb(name, description, type, attribute, "The Orb of Light glows strongly as it brings light to the dark");
						room->roomObjects.push_back(item);
						for (int count = 0; count < motionVector.size(); count++)
						{
							if (currentLine == motionVector[count]->getSymbol())
								motionVector[count]->requiredObjects.push_back(item);
						}

					}
					else
					{
						Object *item = new Orb(name, description, type, attribute, "The Orb of Light glows strongly as it brings light to the dark");
						room->roomObjects.push_back(item);

					}
				}
				else if (currentLine == "PUDDLE")
				{

					type = currentLine;
					while (currentLine != "===")
					{
						myDataFile >> currentLine;

						if (currentLine != "===")
							name += currentLine + " ";
					}

					do
					{
						myDataFile >> currentLine;


						if (currentLine != "===")
							description += currentLine + " ";

					} while (currentLine != "===");

					myDataFile >> attribute;

					myDataFile >> currentLine;

					if (currentLine == "+" || currentLine == "<" || currentLine == "V" || currentLine == ">")
					{
						Object *item = new Puddle(name, description, type, attribute, "You cannot use a puddle?");
						room->roomObjects.push_back(item);
						for (int count = 0; count < motionVector.size(); count++)
						{
							if (currentLine == motionVector[count]->getSymbol())
								motionVector[count]->requiredObjects.push_back(item);
						}

					}
					else
					{

						Object *item = new Puddle(name, description, type, attribute, "You cannot use a puddle?");
						room->roomObjects.push_back(item);

					}
				}

			}
		} while (currentLine != "****");

		//reads in the enemies attributes and objects it drops after being defeated
		do {

			myDataFile >> currentLine;

			if (currentLine == "###")
			{

				string type, defeat, victory, name;
				int hp, ad, def;

				myDataFile >> type;

				do {
					myDataFile >> currentLine;

					if (currentLine != "===")
						name += currentLine + " ";
				} while (currentLine != "===");


				do {
					myDataFile >> currentLine;

					if (currentLine != "===")
						defeat += currentLine + " ";
				} while (currentLine != "===");

				do {
					myDataFile >> currentLine;

					if (currentLine != "===")
						victory += currentLine + " ";
				} while (currentLine != "===");

				myDataFile >> hp;
				myDataFile >> ad;
				myDataFile >> def;

				if (type == "ENEMY")
				{

					myDataFile >> currentLine;
					myEnemy = new Goblin(type, hp, ad, def, name, defeat, victory, currentLine);
				}
				else if (type == "BOSS")
				{
					myDataFile >> currentLine;
					myEnemy = new GoblinKing(type, hp, ad, def, name, defeat, victory, currentLine);
				}

				while (currentLine != "****")
				{

					myDataFile >> currentLine;

					if (currentLine == "<>")
					{

						myDataFile >> currentLine;
						string name;
						string description;
						string type;
						int attribute;

						if (currentLine == "POTION")
						{
							type = currentLine;

							while (currentLine != "===")
							{
								myDataFile >> currentLine;

								if (currentLine != "===")
									name += currentLine + " ";
							}

							do
							{
								myDataFile >> currentLine;


								if (currentLine != "===")
									description += currentLine + " ";

							} while (currentLine != "===");

							string whenUsed;
							myDataFile >> attribute;

							do
							{
								myDataFile >> currentLine;


								if (currentLine != "===")
									whenUsed += currentLine + " ";
							} while (currentLine != "===");


							Object *item = new Potion(name, description, type, attribute, whenUsed);
							myEnemy->getItem(item);
						}
						else if (currentLine == "HINT")
						{
							type = currentLine;
							while (currentLine != "===")
							{
								myDataFile >> currentLine;

								if (currentLine != "===")
									name += currentLine + " ";
							}

							do
							{
								myDataFile >> currentLine;


								if (currentLine != "===")
									description += currentLine + " ";

							} while (currentLine != "===");

							string whenUsed;
							myDataFile >> attribute;
							do
							{
								myDataFile >> currentLine;


								if (currentLine != "===")
									whenUsed += currentLine + " ";

							} while (currentLine != "===");

							Object *item = new Hint(name, description, type, attribute, whenUsed);
							myEnemy->getItem(item);
						}
					}
				}
				room->enemy = myEnemy;

			}


		} while (currentLine != "****");

		room->motionTable = motionVector;
		myRooms.push_back(room);
	}



}
void Adventure::deleteRooms()
{
	myRooms.empty();
}

bool Adventure::run(Player* generalStyrax, color color)
{

	playMusic(generalStyrax->getLocation() - 1);
	string command = " ";
	string input = "start";

	bool viableCommand;
	string object;
	input = "start";
	viableCommand = false;
	color.setcolor(color.dark_green, color.black);
	cout << "==================================================================================================" << endl;
	cout << "Health  : " << generalStyrax->getHealth() << "                                                          " << "Movements: " << generalStyrax->getMovements() << endl;

	cout << "Attack  : " << generalStyrax->getAttack() << "                                                " << "Currently Equiped: " << endl;
	if (generalStyrax->getSword() == NULL)
		cout << "Defense : " << generalStyrax->getDefense() << "                                                            " << "Sword: none" << endl;
	else
		cout << "Defense : " << generalStyrax->getDefense() << "                                                           " << "Sword: " << generalStyrax->getSword()->getName() << endl;
	if (generalStyrax->getShield() == NULL)
		cout << "                                                                       " << "Shield: none" << endl;
	else
		cout << "                                                                       " << "Shield: " << generalStyrax->getShield()->getName() << endl;
	cout << "==================================================================================================" << endl;
	color.setcolor(color.dark_red, color.black);
	cout << myRooms[(generalStyrax->getLocation()) - 1]->getName() << endl;
	if (myRooms[(generalStyrax->getLocation()) - 1]->getActive())
	{
		if (!myRooms[(generalStyrax->getLocation()) - 1]->getEventStatus())
		{
			for (int a = 0; a < myRooms[generalStyrax->getLocation() - 1]->roomDescription.size(); a++)
			{
				cout << myRooms[generalStyrax->getLocation() - 1]->roomDescription[a] << endl;
			}
		}
		else
		{
			for (int a = 0; a < myRooms[generalStyrax->getLocation() - 1]->roomDescription2.size(); a++)
			{
				cout << myRooms[generalStyrax->getLocation() - 1]->roomDescription2[a] << endl;
			}
		}

	}
	else
	{
		cout << "????????????????????????" << endl;
		cout << "General Styrax: I cannot see a thing..." << endl;
		cout << "General Styrax: Maybe if could USE something to illuminate this place" << endl;

	}
	cout << "==================================================================================================" << endl;
	color.setcolor(color.dark_aqua, color.black);
	cout << "You can travel in these Directions: " << endl;
	color.setcolor(color.aqua, color.black);
	if (myRooms[(generalStyrax->getLocation()) - 1]->getActive())
	{
		for (int c = 0; c < myRooms[generalStyrax->getLocation() - 1]->motionTable.size(); c++) {
			if (!myRooms[generalStyrax->getLocation() - 1]->motionTable[c]->getHidden())
				cout << myRooms[generalStyrax->getLocation() - 1]->motionTable[c]->getDirection() << endl;
		}
	}
	else
	{
		cout << "????" << endl << "????" << endl << "????" << endl;
	}
	color.setcolor(color.dark_aqua, color.black);
	cout << "==================================================================================================" << endl;
	color.setcolor(color.white, color.black);

	while (!viableCommand)
	{
		viableCommand = true;

		getline(cin, input);
		istringstream iss(input);

		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		int count = 0;
		while (iss)
		{
			if (count == 0)
			{
				iss >> command;
				object = "";
			}
			else if (count == 1)
			{
				iss >> object;
			}
			else
			{
				break;
			}
			count++;
		}
		iss.clear();
		iss.ignore();

		transform(command.begin(), command.end(), command.begin(), ::toupper);
		transform(object.begin(), object.end(), object.begin(), ::toupper);


		if (command == "EXIT")
		{
			cout << "Thank you for playing" << endl;
			system("PAUSE");
			setRestart(false);
			return true;


		}
		/*
		else if(command == "WARP")
		{
		if(object == "ONE")
		{
		generalStyrax->setLocation(1);
		}

		else if (object == "TWO")
		{
		generalStyrax->setLocation(2);
		}
		else if (object == "THREE")
		{
		generalStyrax->setLocation(3);
		}
		else if (object == "FOUR")
		{
		generalStyrax->setLocation(4);
		}
		else if (object == "FIVE")
		{
		generalStyrax->setLocation(5);
		}
		else if (object == "SIX")
		{
		generalStyrax->setLocation(6);
		}

		soundIsPlaying = false;
		}
		*/ //used just for testing
		else if (command == "MUSIC")
		{
			if (object == "ON")
			{
				musicIsOn = true;
				cout << "Music is enabled" << endl;

			}
			else if (object == "OFF")
			{
				musicIsOn = false;
				cout << "Music is disabled" << endl;
			}

		}
		else if (command == "HELP")
		{
			system("cls");
			cout << "The way you maneuver around the game is by inputing singular word commands, some commands are followed by an ojbect." << endl;
			cout << "Commands: " << endl;
			cout << "EXIT" << endl;
			cout << "HELP" << endl;
			cout << "INVENTORY" << endl;
			cout << "BATTLE   [Object options: BOSS, ENEMY]" << endl;
			cout << "TAKE" << endl;
			cout << "EQUIP   [Object options: SWORD, SHIELD]" << endl;
			cout << "USE      [Object options(some): POTION, HINT]" << endl;
			cout << "LOOK" << endl << endl;
			cout << "Commands[Direction]:" << endl;
			cout << "NORTH" << endl << "EAST " << endl << "SOUTH" << endl << "WEST" << endl << endl;
			cout << "Tip: to change the font size, right click on the console header -> properties -> font. Change according to your liking but font size 28 is suggested." << endl;
			cout << "To turn off the music, type 'music off' and to turn on, type 'music on'" << endl;
		}
		else if (command == "INVENTORY")
		{

			generalStyrax->displayInventory();
		}
		else if (command == "BATTLE")
		{

			if (object == "ENEMY" && myRooms[generalStyrax->getLocation() - 1]->enemy != NULL && myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() != "FORCED" && myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
			{
				if (myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
					Battle(generalStyrax, myRooms[generalStyrax->getLocation() - 1]->enemy, color);
				else
				{
					cout << "You have already defeated the enemy in here." << endl;
				}
			}
			else if (object == "BOSS" && myRooms[generalStyrax->getLocation() - 1]->enemy != NULL)
			{
				if (object == "BOSS" && myRooms[generalStyrax->getLocation() - 1]->enemy != NULL)
					Battle(generalStyrax, myRooms[generalStyrax->getLocation() - 1]->enemy, color);
				else cout << "There is no Boss you can fight here." << endl;
			}
			else
			{
				cout << "You cannot battle that." << endl;
			}

		}
		else if (command == "TAKE")
		{
			bool objectTaken = false;

			for (int i = 0; i < myRooms[generalStyrax->getLocation() - 1]->roomObjects.size(); i++)
			{
				//checks if the object the user gave as input is in the room
				if (object == myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->getType())
				{
					if (object != "PUDDLE")
					{

						generalStyrax->take(myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]);
						cout << "You have obtained " << myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->getName() << endl << endl;
						myRooms[generalStyrax->getLocation() - 1]->roomObjects.erase(myRooms[generalStyrax->getLocation() - 1]->roomObjects.begin() + i);
						objectTaken = true;
						if (myRooms[generalStyrax->getLocation() - 1]->getEventType() == 2)
							myRooms[generalStyrax->getLocation() - 1]->setEventStatus(true);
						//if there is a hidden enemy guarding the object, innitiates battle mode
						if (myRooms[generalStyrax->getLocation() - 1]->enemy != NULL && myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == "FORCED" && myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
						{
							cout << "Look out! An enemy has Ambushed you!" << endl;
							system("PAUSE");
							Battle(generalStyrax, myRooms[generalStyrax->getLocation() - 1]->enemy, color);

						}
					}
				}
				if (objectTaken)break;
			}
			if (!objectTaken)
			{
				cout << "Sorry, that is not an Object you can take" << endl;
			}



		}
		else if (command == "EQUIP")
		{
			int choice;
			bool equip = false;
			int count = 0;
			if (generalStyrax->inventory.size() != 0)
			{
				if (object == "SWORD")
				{

					cout << "Enter the number of the sword you wish to equip" << endl << "Inventory: " << endl;
					for (int i = 0; i < generalStyrax->inventory.size(); i++)
					{
						if (generalStyrax->inventory[i]->getType() == object)
						{
							cout << "\t[" << i << "] " << generalStyrax->inventory[i]->getName() << endl;
							count++;
						}
					}
					if (count == 0)
					{
						cout << "There are no Swords in your inventory" << endl;
						system("PAUSE");
						system("cls");
						break;
					}
					cin >> choice;
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail(), '\n');
					if (choice >= generalStyrax->inventory.size() || choice < 0 || generalStyrax->inventory[choice]->getType() != object)
					{
						cout << "Sorry, that is not an option in your Inventory" << endl;
						system("PAUSE");
						system("cls");
						break;
					}
					generalStyrax->setAttackEquip(generalStyrax->inventory[choice]);


					cout << "You have equipped " << generalStyrax->inventory[choice]->getName() << endl;


				}
				else if (object == "SHIELD")
				{
					cout << "Enter the number of the shield you wish to equip" << endl << "Inventory: " << endl;
					for (int i = 0; i < generalStyrax->inventory.size(); i++)
					{
						if (generalStyrax->inventory[i]->getType() == object)
						{
							cout << "\t[" << i << "] " << generalStyrax->inventory[i]->getName() << endl;
							count++;
						}

					}
					if (count == 0)
					{
						cout << "There are no Shields in your inventory" << endl;
						system("PAUSE");
						system("cls");
						break;
					}
					cin >> choice;
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail(), '\n');
					if (choice >= generalStyrax->inventory.size() || choice < 0 || generalStyrax->inventory[choice]->getType() != object)
					{
						cout << "Sorry, that is not an option in your Inventory" << endl;
						system("PAUSE");
						system("cls");
						break;
					}
					generalStyrax->setDefenseEquip(generalStyrax->inventory[choice]);
					equip = true;
					cout << "You have equipped " << generalStyrax->inventory[choice]->getName() << endl;
				}
				else
				{
					cout << "No object was given with Command" << endl;
				}

			}
			else
			{
				cout << "you have no item in your inventory that you can equip" << endl;

			}

		}
		else if (command == "USE")
		{
			int choice;

			if (object == "POTION")
			{
				cout << "Enter the number of the potion you wish to use" << endl << "Inventory: " << endl;
				for (int i = 0; i < generalStyrax->inventory.size(); i++)
				{
					if (generalStyrax->inventory[i]->getType() == object)
						cout << "\t[" << i << "] " << generalStyrax->inventory[i]->getName() << endl;
				}
				cin >> choice;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');

				if (choice >= generalStyrax->inventory.size() || choice < 0 || generalStyrax->inventory[choice]->getType() != object)
				{
					cout << "Sorry, that is not an option in your Inventory" << endl;
					system("PAUSE");
					system("cls");
					break;
				}
				else
				{
					string red = "Red";
					string yellow = "Yellow";
					if (generalStyrax->inventory[choice]->getName()[0] == red[0])
					{
						generalStyrax->regainHP(generalStyrax->inventory[choice]);
					}
					else if (generalStyrax->inventory[choice]->getName()[0] == yellow[0])
					{
						generalStyrax->increaseMaxHP(generalStyrax->inventory[choice]);
					}

					cout << generalStyrax->inventory[choice]->getUsed() << endl;
					generalStyrax->inventory.erase(generalStyrax->inventory.begin() + choice);

				}

			}
			else if (object == "HINT")
			{
				cout << "Enter the number of the Hint you wish to use" << endl << "Inventory: " << endl;
				for (int i = 0; i < generalStyrax->inventory.size(); i++)
				{
					if (generalStyrax->inventory[i]->getType() == object)
						cout << "\t[" << i << "] " << generalStyrax->inventory[i]->getName() << endl;
				}
				cin >> choice;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				if (choice >= generalStyrax->inventory.size() || choice < 0 || generalStyrax->inventory[choice]->getType() != object)
				{
					cout << "Sorry, that is not an option in your Inventory" << endl;
					system("PAUSE");
					system("cls");
					break;
				}
				else
				{
					cout << generalStyrax->inventory[choice]->getUsed() << endl;
					generalStyrax->inventory.erase(generalStyrax->inventory.begin() + choice);

				}


			}
			else if (object == "ORB")
			{
				for (int i = 0; i < generalStyrax->inventory.size(); i++)
				{
					if (generalStyrax->inventory[i]->getType() == object)
					{
						if (generalStyrax->inventory[i]->getAttribute() == generalStyrax->getLocation())
						{
							if (!myRooms[generalStyrax->getLocation() - 1]->getActive())
							{
								myRooms[generalStyrax->getLocation() - 1]->setActive(true);
								cout << generalStyrax->inventory[i]->getUsed();
								cout << endl;

							}
						}
						else
						{
							cout << "Nothing happened..." << endl;
						}
					}
				}

			}
			else
			{
				cout << "No object was given with Command" << endl;

			}

		}
		else if (command == "LOOK")
		{
			bool objectLooked = false;

			for (int i = 0; i < myRooms[generalStyrax->getLocation() - 1]->roomObjects.size(); i++)
			{

				if (object == myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->getType())
				{
					cout << myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->examine() << endl;
					objectLooked = true;
					if (myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->getType() == "PUDDLE")
					{
						generalStyrax->setLocation(myRooms[generalStyrax->getLocation() - 1]->roomObjects[i]->getAttribute());
						//system("PAUSE");
						//system("cls");
					}

				}
			}
			if (objectLooked == false)
			{
				cout << "Sorry, that is not an Object" << endl;
			}

		}
		else
		{
			//Movement between rooms
			bool matchFound = false;
			if (myRooms[(generalStyrax->getLocation()) - 1]->getActive())
			{
				for (int i = 0; i < myRooms[generalStyrax->getLocation() - 1]->motionTable.size(); i++)
				{
					if (matchFound)break;

					//checks if the command = a possible direction in the room
					//&& if the room is not hidden
					if (command == myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDirection() && !myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getHidden())
					{
						//checks if there is no object required
						if (myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->requiredObjects.size() == 0)
						{
							//checks if there is no enemy blocking the way
							if (myRooms[generalStyrax->getLocation() - 1]->enemy == NULL || (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() != command) || (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == command && !myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive()))
							{
								//move to the new location

								generalStyrax->setLocation(myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDestination());
								generalStyrax->increaseMovements();
								matchFound = true;
								soundIsPlaying = false;
								if (myRooms[generalStyrax->getLocation() - 1]->getEventType() == 1)
									myRooms[generalStyrax->getLocation() - 1]->setEventStatus(true);

							}
							//if enemy is blocking the way, deny the access
							else if (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == command && myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
							{
								cout << myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDeniedAccess() << endl;
								matchFound = true;

							}
						}
						else //if there is objects required
						{
							int count = 0;
							//checks how much objects you have of the required objects
							for (int b = 0; b < myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->requiredObjects.size(); b++)
							{
								for (int c = 0; c < generalStyrax->inventory.size(); c++)
								{
									if (generalStyrax->inventory[c] == myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->requiredObjects[b])
									{
										count++;
									}
								}
							}
							//checks if you have all of the objects required
							if (count == myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->requiredObjects.size())
							{
								//checks if theres no enemy blocking the way
								if (myRooms[generalStyrax->getLocation() - 1]->enemy == NULL || (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() != command) || (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == command && !myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive()))
								{
									//move to the new location

									generalStyrax->setLocation(myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDestination());
									generalStyrax->increaseMovements();
									matchFound = true;
									soundIsPlaying = false;
									if (myRooms[generalStyrax->getLocation() - 1]->getEventType() == 1)
										myRooms[generalStyrax->getLocation() - 1]->setEventStatus(true);

								}//if there is, deny access
								else if (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == command && myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
								{
									cout << myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDeniedAccess() << endl;
									matchFound = true;
								}

							}
							else // deny access if insuffcient objects required
							{
								cout << myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getDeniedAccess() << endl;
								matchFound = true;
							}

						}


					}

					else if (myRooms[generalStyrax->getLocation() - 1]->enemy != NULL && myRooms[generalStyrax->getLocation() - 1]->motionTable[i]->getHidden())
					{

						if (myRooms[generalStyrax->getLocation() - 1]->enemy->minionSpecial() == command && myRooms[generalStyrax->getLocation() - 1]->enemy->isAlive())
						{
							cout << "Look out! An enemy has Ambushed you!" << endl;
							Battle(generalStyrax, myRooms[generalStyrax->getLocation() - 1]->enemy, color);
							matchFound = true;
						}

					}

				}
				if (!matchFound)
				{
					viableCommand = false;
				}
			}
			else if (!myRooms[(generalStyrax->getLocation()) - 1]->getActive())
			{
				if (command == "NORTH" || command == "WEST" || command == "EAST")
				{
					cout << "General Styrax: OUCH! I think i just walked into something, probably lost some health..." << endl;;
					generalStyrax->getDamaged(2);

				}
				else if (command == "SOUTH")
				{
					generalStyrax->setLocation(2);

				}

			}

		}

		if (generalStyrax->getLocation() == 5)
		{

			if (myRooms[4]->roomObjects.size() == 0)
			{
				cout << "*Angelic voice*: There is nothing for you here anymore, go and fullfill your destiny" << endl;
				generalStyrax->setLocation(4);

			}

		}



		if (generalStyrax->getVictory())
		{
			cout << "General Styrax: The Ancient One huh? i guess this story continues.." << endl;
			Sleep(2500);
			system("cls");
			color.setcolor(color.dark_purple, color.black);
			cout << "=====================================================" << endl;
			color.setcolor(color.red, color.black);
			cout << "                   YOU WIN!                         " << endl;
			color.setcolor(color.dark_purple, color.black);
			cout << "=====================================================" << endl << endl;

			system("PAUSE");
			system("cls");
			cout << "Thank you for Playing" << endl;
			cout << "The game will now exit" << endl;
			setRestart(false);
			system("PAUSE");
			return true;
		}

		if (generalStyrax->getFallen())
		{
			cout << generalStyrax->getDeathS() << endl;
			Sleep(2500);
			system("cls");
			color.setcolor(color.dark_purple, color.black);
			cout << "=====================================================" << endl;
			color.setcolor(color.red, color.black);
			cout << "                   GAME OVER                         " << endl;
			color.setcolor(color.dark_purple, color.black);
			cout << "=====================================================" << endl << endl;


			system("PAUSE");
			system("cls");

			return true;
		}

		if (!viableCommand)
			cout << "Not a viable command, try again" << endl;
		else
		{
			system("PAUSE");
			system("cls");
		}

	}	return false;

}
int main()
{
	bool exit = false;
	Player *generalStyrax = new Player();
	Adventure myAdventure;

	while (myAdventure.getRestart())
	{
		myAdventure = Adventure();
		ifstream myFile("Kluola.txt", ios::out);
		while (!myFile.is_open())
		{
			cout << "invalid name, insert another one" << endl;
			string name;
			cin >> name;
			myFile.open(name);
		}
		myAdventure.readFile(myFile);

		myFile.close();

		color color;
		color.setcolor(color.dark_red, color.black);
		string intro[4] = { "General! \n","Wake up!\n","General! The king needs you!","General Styrax! Princess Kaly was abducted!" };
		Sleep(2000);
		for (int i = 0; i <(sizeof(intro) / sizeof(intro[0])); i++)
		{

			PlaySound(TEXT("music\\knock-on-the-door.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Sleep(1500);
			cout << intro[i];
			Sleep(1500);
			system("cls");
		}


		while (!exit)
		{
			exit = myAdventure.run(generalStyrax, color);
		}
		generalStyrax->setDefault();
		myAdventure.deleteRooms();
		exit = false;
		system("cls");
	}
	return 0;
}

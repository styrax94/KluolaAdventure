#pragma once
#include "Adventure.h"
class Player
{
private:

	int currentLocation;
	int hitPoints;
	int maxHp;
	int attackDamage;
	int defense;
	int numberOfMovements;
	Object* attack;
	Object* defenseEquip;
	string deathString;
	bool hasFallen;
	bool victory;

public:
	Player();
	~Player();

	void displayInventory();
	void take(Object* object);
	void regainHP(Object* object);
	void increaseMaxHP(Object* object);
	int getLocation();
	void setLocation(int loc);
	vector<Object*> inventory;
	void setAttackEquip(Object* aEquip);
	void setDefenseEquip(Object* dEquip);
	void getDamaged(int dmg);
	int getHealth();
	int getAttack();
	int getDefense();
	void increaseMovements();

	string getAttackS();
	string getDefenseS();
	string getHealthS();
	string getDeathS();

	void styraxHasFallen();
	bool getFallen();
	bool getVictory();
	void setVictory();
	int getMovements();
	Object* getSword();
	Object* getShield();

	void setDefault();
};


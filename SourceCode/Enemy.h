#pragma once
#include <string>
using namespace std;

class Enemy
{
protected:
	int health;
	int attackDamage;
	int defense;
	string defeated;
	string victory;
	string type;
	string name;
	vector<Object*> itemDrops;
	bool alive;

public:

	~Enemy() {};
	virtual string getName() = 0;
	virtual void getDamaged(int dmg) = 0;

	virtual string getDefeated() = 0;
	virtual string getVictory() = 0;
	virtual string getType() = 0;
	virtual string minionSpecial() = 0;
	virtual int bossSpecial() = 0;
	virtual void killEnemy() = 0;
	virtual bool isAlive() = 0;
	virtual int getHealth() = 0;
	virtual int getAttackDamage() = 0;
	virtual int getDefense() = 0;
	virtual string getHealthS() = 0;
	virtual string getAttackDamageS() = 0;
	virtual string getDefenseS() = 0;
	virtual void getItem(Object* item) = 0;
	virtual vector<Object*> getItemVector() = 0;
};

class Goblin : public Enemy
{
private:
	string guardedDirection;

public:
	Goblin(string t, int h, int ad, int de, string n, string defeat, string vict, string guard)
	{
		type = t;
		health = h;
		attackDamage = ad;
		defense = de;
		name = n;
		defeated = defeat;
		victory = vict;
		guardedDirection = guard;
		alive = true;

	}
	string getName()
	{
		return name;
	}
	void getDamaged(int dmg)
	{

		health -= dmg;
		if (health < 0)
		{
			health = 0;
		}
	}

	int getHealth()
	{
		return health;
	}

	int getAttackDamage()
	{
		return attackDamage;
	}

	string getDefeated()
	{
		return defeated;
	}
	string getVictory()
	{
		return victory;
	}
	string getType()
	{
		return type;
	}
	string minionSpecial()
	{
		return guardedDirection;
	}
	int bossSpecial()
	{
		return 1;
	};

	void killEnemy()
	{
		alive = false;
	}
	bool isAlive() {
		return alive;
	}
	int getDefense()
	{
		return defense;
	}
	string getHealthS()
	{
		if (health < 10)
		{
			return "0" + to_string(health);
		}
		else return to_string(health);
	}
	string getAttackDamageS()
	{
		if (attackDamage <10)
		{
			return "0" + to_string(attackDamage);
		}
		else return to_string(attackDamage);
	}
	string getDefenseS()
	{
		if (defense <10)
		{
			return "0" + to_string(defense);
		}
		else return to_string(defense);
	}
	void getItem(Object* item)
	{
		itemDrops.push_back(item);

	}
	vector<Object*> getItemVector()
	{
		return itemDrops;

	}

};
class GoblinKing : public Enemy
{
private:
	string guardedDirection;
public:
	GoblinKing(string t, int h, int ad, int de, string n, string defeat, string vict, string guard)
	{
		type = t;
		health = h;
		attackDamage = ad;
		defense = de;
		name = n;
		defeated = defeat;
		victory = vict;
		guardedDirection = guard;
		alive = true;

	}
	string getName()
	{
		return name;
	}
	void getDamaged(int dmg)
	{

		health -= dmg;
		if (health < 0)
		{
			health = 0;
		}
	}

	int getHealth()
	{
		return health;
	}

	int getAttackDamage()
	{
		return attackDamage;
	}

	string getDefeated()
	{
		return defeated;
	}
	string getVictory()
	{
		return victory;
	}
	string getType()
	{
		return type;
	}
	string minionSpecial()
	{
		return guardedDirection;
	}
	int bossSpecial()
	{
		return 2;
	};

	void killEnemy()
	{
		alive = false;
	}
	bool isAlive() {
		return alive;
	}
	int getDefense()
	{
		return defense;
	}
	string getHealthS()
	{
		if (health < 10)
		{
			return "0" + to_string(health);
		}
		else return to_string(health);
	}
	string getAttackDamageS()
	{
		if (attackDamage <10)
		{
			return "0" + to_string(attackDamage);
		}
		else return to_string(attackDamage);
	}
	string getDefenseS()
	{
		if (defense <10)
		{
			return "0" + to_string(defense);
		}
		else return to_string(defense);
	}
	void getItem(Object* item)
	{
		itemDrops.push_back(item);

	}
	vector<Object*> getItemVector()
	{
		return itemDrops;

	}

};

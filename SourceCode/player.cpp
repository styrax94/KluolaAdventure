#include "Player.h"



Player::Player()
{
	currentLocation = 1;
	hitPoints = 25;
	maxHp = 25;
	attackDamage = 2;
	defense = 1;
	numberOfMovements = 0;
	attack = NULL;
	defenseEquip = NULL;
	hasFallen = false;
	victory = false;
	deathString = "General Styrax: No.. Princess Kaly.. Kluola Kingdom.. i have failed you X_X";
}


Player::~Player()
{
}

void Player::displayInventory()
{
	if (inventory.size() == 0) cout << "There are currently no items in your Inventory" << endl;
	else
	{
		cout << "Your current Inventory includes: " << endl;
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << "\t[" << i << "]: " << inventory[i]->getName() << endl;
		}

	}

}

void Player::take(Object* item)
{
	inventory.push_back(item);
}
void Player::regainHP(Object* item)
{
	hitPoints += item->getAttribute();
	if (hitPoints > maxHp) hitPoints = maxHp;
}
void Player::increaseMaxHP(Object* item)
{
	maxHp += item->getAttribute();
	hitPoints = maxHp;
}
int Player::getLocation()
{
	return currentLocation;
}
void Player::setLocation(int loc)
{
	currentLocation = loc;
}
void Player::setAttackEquip(Object* aEquip)
{
	attack = aEquip;

}
void Player::setDefenseEquip(Object* dEquip)
{
	defenseEquip = dEquip;

}

void Player::getDamaged(int dmg)
{
	hitPoints -= dmg;

	if (hitPoints < 0)
	{
		hitPoints = 0;
	}
}

int Player::getHealth()
{
	return hitPoints;
}
int Player::getMovements()
{
	return numberOfMovements;
}
void Player::increaseMovements()
{
	numberOfMovements++;
}
string Player::getHealthS()
{

	if (hitPoints < 10)
		return "0" + to_string(hitPoints);
	else
		return  to_string(hitPoints);

}
int Player::getAttack()
{
	int newAttack;
	if (attack != NULL)
	{
		newAttack = attackDamage + attack->getAttribute();
	}
	else newAttack = attackDamage;

	return newAttack;
}
string Player::getAttackS()
{
	int newAttack;
	if (attack != NULL)
	{
		newAttack = attackDamage + attack->getAttribute();
	}
	else newAttack = attackDamage;
	if (newAttack < 10)
		return "0" + to_string(newAttack);
	else
		return  to_string(newAttack);
}

int Player::getDefense()
{

	int newDef;
	if (defenseEquip != NULL)
	{
		newDef = defense + defenseEquip->getAttribute();
	}
	else newDef = defense;

	return newDef;


}
string Player::getDefenseS()
{
	int newDefense;
	if (defenseEquip != NULL)
	{
		newDefense = defense + defenseEquip->getAttribute();
	}
	else newDefense = defense;
	if (newDefense < 10)
		return "0" + to_string(newDefense);
	else
		return to_string(newDefense);
}
Object* Player::getSword()
{
	return attack;
}
Object* Player::getShield()
{
	return defenseEquip;
}

void Player::styraxHasFallen()
{
	hasFallen = true;
}

string Player::getDeathS()
{
	return deathString;
}
bool Player::getFallen()
{
	return hasFallen;
}

void Player::setDefault()
{
	currentLocation = 1;
	hitPoints = 25;
	maxHp = 25;
	attackDamage = 2;
	defense = 1;
	numberOfMovements = 0;
	attack = NULL;
	defenseEquip = NULL;
	hasFallen = false;
	victory = false;
	deathString = "General Styrax: No.. Princess Kaly.. Kluola Kingdom.. i have failed you X_X";
	inventory.clear();

}

bool Player::getVictory()
{
	return victory;
}
void Player::setVictory()
{
	victory = true;
}
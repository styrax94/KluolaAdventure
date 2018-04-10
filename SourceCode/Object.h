#pragma once
#include <string>
using namespace std;

class Object
{
protected:
	string name;
	string description;
	string type;
public:
	Object(){}
	~Object(){}

	virtual string examine() = 0;
	virtual string getName() = 0;
	virtual int getAttribute() = 0;
	virtual string getType() = 0;
	virtual string getUsed() = 0;
};

class Sword : public Object
{
private:
	int attackDamage;


public:
	Sword(string n, string d, string t, int dmg)
	{
		name = n;
		description = d;
		type = t;
		attackDamage = dmg;
	}
	Sword()
	{

	}

	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return attackDamage;
	}
	string getType()
	{
		return type;
	}
	string getUsed()
	{
		return "Cannot use a sword\n";
	}
};

class Shield : public Object
{
private:
	int defense;

public:

	Shield(string n, string d, string t, int def)
	{
		name = n;
		description = d;
		type = t;
		defense = def;
	}
	Shield() {}

	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return defense;
	}
	string getType()
	{
		return type;
	}
	string getUsed()
	{
		return "Cannot use a shield\n";
	}
};

class Potion : public Object
{
private:
	int healAmount;
	string whenUsed;

public:

	Potion(string n, string d, string t, int heal, string used)
	{
		name = n;
		description = d;
		type = t;
		healAmount = heal;
		whenUsed = used;
	}
	Potion() {}

	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return healAmount;
	}
	string getType()
	{
		return type;
	}
	string getUsed()
	{
		return whenUsed;
	}
};

class Hint : public Object
{
private:
	int dummy;
	string whenUsed;
public:

	Hint(string n, string d, string t, int atri, string used)
	{
		name = n;
		description = d;
		type = t;
		dummy = atri;
		whenUsed = used;
	}
	Hint() {}

	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return dummy;
	}
	string getType()
	{
		return type;
	}

	string getUsed()
	{
		return whenUsed;
	}
};

class Orb : public Object
{
private:
	int dummy;
	string whenUsed;
public:

	Orb(string n, string d, string t, int atri, string used)
	{
		name = n;
		description = d;
		type = t;
		dummy = atri;
		whenUsed = used;
	}
	Orb() {}

	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return dummy;
	}
	string getType()
	{
		return type;
	}

	string getUsed()
	{
		return whenUsed;
	}
};

class Puddle : public Object
{
private:
	int dummy;
	string whenUsed;
public:

	Puddle(string n, string d, string t, int atri, string used)
	{
		name = n;
		description = d;
		type = t;
		dummy = atri;
		whenUsed = used;
	}


	string examine()
	{
		return description;
	}

	string getName()
	{
		return name;
	}
	int getAttribute()
	{
		return dummy;
	}
	string getType()
	{
		return type;
	}

	string getUsed()
	{
		return whenUsed;
	}
};



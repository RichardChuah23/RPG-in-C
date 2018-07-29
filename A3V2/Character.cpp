#include "Character.h" 
#include <sstream>
#include <string>

#include <random>
using namespace std;

Character::Character()
{
	m_name = new string("Undefined");
	m_pType = new string("");
	m_attack = new int(0);
	m_curHealth = new int(0);
	m_maxHealth = new int(0);
	m_defense = new int(0);

}

Character::Character(string name, string pType, int health, int attack, int defense) {
	m_name = new string(name);
	m_pType = new string(pType);
	m_attack = new int(attack);
	m_curHealth = new int(health);
	m_maxHealth = new int(50);
	m_defense = new int(defense);

}

Character::~Character() {
	delete m_name;
	delete m_pType;
	delete m_attack;
	delete m_curHealth;
	delete m_maxHealth;
	delete m_defense;
}


string Character::displayCharacter() {
	stringstream m_playerDetails;

	m_playerDetails << "Current stats for " << *m_name << "\n";
	m_playerDetails << "Type: " << *m_pType << "\n";
	m_playerDetails << "attack: " << *m_attack << "\n";
	m_playerDetails << "Cur Health: " << *m_curHealth << endl;
	m_playerDetails << "Defense: " << *m_defense << endl;

	return m_playerDetails.str();

}

int Character::attack()
{
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(1, 6);
	return (uni(rng)) + *m_attack;
}

int Character::defense()
{
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(1, 6);
	return (uni(rng)) + *m_defense;
}

string Character::name()
{
	return *m_name; 

}

void Character::beHit(int amount)
{

	*m_curHealth -= amount;

}

int Character::curHealth()
{
	return *m_curHealth;
}

int Character::maxHealth()
{
	return *m_maxHealth; 
}

int Character::getAttackVal()
{
	return *m_attack; 
}
int Character::getDefenseVal()
{
	return *m_defense;
}
















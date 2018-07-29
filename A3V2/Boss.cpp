

#include "Boss.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;



Boss::Boss() {
	m_specialAttack = new int(0); 

}

Boss::Boss(string name, string pType, int health, int attack, int specialAttack, int defense) :Character(name, pType, health, attack, defense)
{
	m_specialAttack = new int(specialAttack);
}


int Boss::specialAttack()
{
	srand(time(NULL));
	return (rand() % 6 + 1) + *m_attack + *m_specialAttack;
}

string Boss::displayCharacter() {
	stringstream m_playerDetails;
	m_playerDetails << "Current stats for " << *m_name << "\n";
	m_playerDetails << "Type: " << *m_pType << "\n";
	m_playerDetails << "attack: " << *m_attack << "\n";
	m_playerDetails << "Cur Health: " << *m_curHealth << endl;
	m_playerDetails << "Max Health: " << *m_maxHealth << endl;
	m_playerDetails << "Defense: " << *m_defense << endl;
	return m_playerDetails.str();
}




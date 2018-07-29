

#ifndef A3_Character_h
#define A3_Character_h

#include <string>

using namespace std;

class Character
{
protected:
	string* m_name;
	string* m_pType;
	int* m_curHealth;
	int* m_maxHealth;
	int* m_attack;
	int* m_defense;

public:
	Character();
	Character(string name, string pType, int health, int attack, int defense);
	~Character();
	void beHit(int amount);
	int attack();
	int defense();
	int getAttackVal(); 
	int getDefenseVal(); 
	int maxHealth();
	string name(); 
	int curHealth();
	virtual string displayCharacter();

};








#endif
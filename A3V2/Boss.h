#ifndef A3_Boss_h
#define A3_Boss_h
#include <string>
#include "Character.h"

using namespace std;

class Boss : public Character
{

private:
	int* m_specialAttack;

public:
	Boss();
	Boss(string name, string pType, int health, int attack, int specialAttack, int defense);

	int specialAttack();
	string displayCharacter();

};




#endif
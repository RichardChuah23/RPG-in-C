#ifndef A3_Hero_h
#define A3_Hero_h
#include <string>
#include "Character.h"


using namespace std;

class Hero : public Character
{

private:
	int* m_priceMoney;
	int* m_specialAttack;

public:
	Hero();
	Hero(string name, string pType, int health, int attack, int specialAttack, int defense, int money);

	int specialAttack();
	string displayCharacter();
	int priceMoney();
	string pType();
	int getSpecialAttackVal(); 
	int addHealth(int amount);
	int addAttack(int amount); 
	int addsAttack(int amount); 
	int addMaxHealth(int amount);
	int addDef(int amount);
	int addMoney(int amount); 
	int deductMoney(int amount);

};

#endif
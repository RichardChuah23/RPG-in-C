

#include "Hero.h"
#include <sstream>
#include <random>

using namespace std;



Hero::Hero() {
	m_priceMoney = new int(0);
	m_specialAttack = new int(0);

}

Hero::Hero(string name, string pType, int health, int attack, int specialAttack, int defense, int money) :Character(name, pType, health, attack, defense)
{
	m_priceMoney = new int(money);
	m_specialAttack = new int(specialAttack);
}


int Hero::specialAttack()
{
	//Initialize random machine
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(1, 6);
	return (uni(rng)) + *m_attack + *m_specialAttack;
}

string Hero::displayCharacter() {
	stringstream m_playerDetails;
	m_playerDetails << "Current stats for " << *m_name << "\n";
	m_playerDetails << "Type: " << *m_pType << "\n";
	m_playerDetails << "attack: " << *m_attack << "\n";
	m_playerDetails << "Special attack: " << *m_specialAttack << "\n";
	m_playerDetails << "Cur Health: " << *m_curHealth << endl;
	m_playerDetails << "Max Health: " << *m_maxHealth << endl;
	m_playerDetails << "Defense: " << *m_defense << endl;
	m_playerDetails << "Money: " << *m_priceMoney << endl;
	return m_playerDetails.str();
}

int Hero::addHealth(int amount) {
	*m_curHealth += amount; 
	return 0; 
}

int Hero::addMaxHealth(int amount) {
	*m_maxHealth += amount; 
	return 0;
}



int Hero::addAttack(int amount) {
	*m_attack += amount;
	return 0; 
}

int Hero::addsAttack(int amount) {
	*m_specialAttack += amount; 
	return 0;
}

int Hero::addDef(int amount) {
	*m_defense += amount; 
	return 0; 
}

int Hero::addMoney(int amount) {
	*m_priceMoney += amount;
	return 0; 
}

int Hero::deductMoney(int amount) {
	*m_priceMoney -= amount;
	return 0;
}

int Hero::priceMoney()
{
	return *m_priceMoney;
}

int Hero::getSpecialAttackVal()
{
	return *m_specialAttack;
}

string Hero::pType() {
	return *m_pType; 
}




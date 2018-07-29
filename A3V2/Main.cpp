#include <iostream>
#include <time.h>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Boss.h"
#include <string>
#include <thread>
#include <random>
#include <chrono>



using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


int heroAttack(Hero& p1, Character& p2, string spAttack);
int bossAttack(Boss& p1, Hero& p2, string spAttack);
int battle(Hero& p1, Character& p2);
int bossBattle(Hero& p1, Boss& p2);
int shop(Hero& p1);
Hero* createHero(); 
Boss* createBoss();
int endGame(string win);
vector<Character*> createMonsters(); 
int reward(Hero& p1);

//Main function
int main() {
	//Declare pointers variables 
	string* win = new string("");

	//Create Hero
	Hero *h1 = new Hero(); 
	h1 = createHero();

	//Create List of Monsters
	vector<Character*> MonsterList;
	MonsterList = createMonsters();

	//Create the Boss 
	Boss *b1 = new Boss();
	b1 = createBoss();

	//Fight the monsters in the list 
	for (int i = 0; i < MonsterList.size(); i++) {
		battle(*h1, *MonsterList[i]);
		shop(*h1);
	}
	
	//Fight the boss 
	bossBattle(*h1, *b1);
	
	//End Game 
	if (h1->curHealth() > 0) {
		*win = "True"; 
	}
	else {
		*win = "False"; 
	}

	//End Game 
	endGame(*win);

	//Clear memory 
	delete h1;
	delete b1; 
	for (int i = 0; i < MonsterList.size(); i++) {
		delete MonsterList[i];
	}

	system("Pause");

	return 0;
}

//End game 
int endGame(string win) {

	//If the player won the game
	if(win == "True") {
		cout << "THE HERO MAKE A FINAL BLOW TO THE BOSS" << endl; 
		sleep_for(milliseconds(700)); 
		cout << "THE BOSS FELL DOWN, THE CROWRD CHEERERD";
		sleep_for(milliseconds(700));
		cout << "YOU WON THE ALL THE FIGHT !" << endl <<
			"YOU ARE THE CHAMPION OF THE ARENA" << endl;
		sleep_for(milliseconds(700));
		cout << "----GAME OVER----" << endl; 
	}
	//Lost
	else {
		
		cout << "YOUR HERO HAS FALLEN !" << endl <<
			"BETTER LUCK NEXT TIME." << endl;
		sleep_for(milliseconds(700));
		cout << "----GAME OVER----" << endl;
	}

	return 0; 
}

//Create a boss object instance 
Boss* createBoss() {

	Boss *b1 = new Boss();

	//Generate a random number from 0-2 
	int* rnd = new int(0);
	srand(time(NULL));
	*rnd = rand() % 3 + 1  ;

	//Create the boss 
	if (*rnd == 1) {
		Boss *b1 = new Boss("DeathAdder", "Boss", 50, 8, 8, 5);
		return b1;
	}
	else if (*rnd == 2) {
		Boss *b1 = new Boss("Naga Queen", "Boss", 40, 10, 7, 5);
		return b1;
	}
	else if (*rnd == 3){
		Boss *b1 = new Boss("Mamba King", "Boss", 45, 9, 8, 5);
		return b1;
	}
	else {
		cout << "Error: no boss found" << endl;
	}

	delete rnd;
	return b1;
}

//Create a hero object instance
Hero* createHero() {
	
	int* choice = new int(0); 
	string* name = new string("");

	Hero *h1 = new Hero();

	//Create Hero
	cout << "Name your hero " << endl; 
	cin >> *name; 

	cout << "Choose your class" << endl; 
	cout << "Crusader[1] Samurai[2] Prince[3]" << endl; 
	cin >> *choice; 

	//Input validation
	while (cin.fail()|| *choice != 1 && *choice != 2 && *choice != 3) {
		cout << "Please enter a valid input(1-3)" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> *choice;
	}

	if (*choice == 1) {
		Hero *h1 = new Hero(*name, "Crusader", 25, 5, 3, 4, 0);
		return h1;
	}
	else if (*choice == 2)
	{
		Hero *h1 = new Hero(*name, "Samurai", 20, 7, 4, 3, 0);
		return h1;
	}
	else if(*choice == 3 )
	{
		Hero *h1 = new Hero(*name, "Prince", 20, 5, 3, 3, 100 );
		return h1;
	}

	delete choice; 
	delete name; 
	return h1; 
	
}

//Create 4 monsters and push it into list
vector<Character*> createMonsters() {
	
	//Push Monsters into vector 
	vector<Character*> MonsterList;
	MonsterList.push_back(new Character("Slaughter", "Monster", 10, 1, 1));
	MonsterList.push_back(new Character("RoadHoug", "Monster", 20, 3, 2));
	MonsterList.push_back(new Character("Reaper", "Monster", 30, 5, 4));
	MonsterList.push_back(new Character("Junkart", "Monster", 40, 6, 7));

	return MonsterList ; 
}

//Hero attack Monster/Boss
int heroAttack(Hero& p1, Character& p2, string attackType) {
	
	//Decare variable for pointers
	int* p1Attack = new int(p1.attack());
	int* p2Defense = new int(p2.defense());

	cout << p1.name() << " SLASH THROUGH THE ENEMY ! With damage of " << *p1Attack  << endl;
	sleep_for(milliseconds(600));

	//Special Attack condition 
	if (attackType == "Y" || attackType == "y") {
		*p1Attack = p1.specialAttack();
		cout << p1.name() << " USES SPECIAL ATTACK! DAMAGE BOOSTED TO " <<  *p1Attack << endl;
		sleep_for(milliseconds(600));
	}
	
	
	cout << p2.name() << " DEFENDED HIMSELF, With defense of " << *p2Defense << endl;
	sleep_for(milliseconds(600));

	//Compare attack and defense values. Determine hit or miss 
	if (*p1Attack > *p2Defense) {
		
		p2.beHit(*p1Attack - *p2Defense);
		cout << "ITS A HIT ! DEALING A DAMGE OF " << *p1Attack - *p2Defense  << endl; 
		sleep_for(milliseconds(600));
		
	}
	else {
		cout << "The hero misses !" << endl;
		sleep_for(milliseconds(600));
	}
	
	delete p1Attack; 
	delete p2Defense; 

	return 0 ; 
}

//Monster Attack Hero
int monsterAttack(Character& p1, Hero& p2) {

	//Decare variable for pointers
	int* p1Attack = new int(p1.attack());
	int* p2Defense = new int(p2.defense());
	
	cout << p1.name() << " MONSTER INITIATE AN ATTACK ! With the damage of " << *p1Attack << endl;
	sleep_for(milliseconds(600));

	cout << p2.name() << " DEFENDED HIMSELF, With the defense of " << *p2Defense << endl;
	sleep_for(milliseconds(600));

	//Compare attack and defense values. Determine hit or miss 
	if (*p1Attack > *p2Defense) {
		p2.beHit(*p1Attack - *p2Defense);
		cout << "ITS A HIT ! DEALING A DAMGE OF " << *p1Attack - *p2Defense << endl;
		sleep_for(milliseconds(600));
	}

	else {
		cout << "The Monster MISSED !" << endl;
		sleep_for(milliseconds(600));
	}

	//Clear memory
	delete p1Attack;
	delete p2Defense;

	return 0;
}

//Boss Attack Hero
int bossAttack(Boss& p1, Hero& p2, string attackType) {
	//Decare variable for pointers

	int* p1Attack = new int(p1.attack());
	int* p2Defense = new int(p2.defense());

	cout << p1.name() << " MONSTER INITIATE AN ATTACK ! With the damage of " << *p1Attack << endl;
	sleep_for(milliseconds(600));

	//Special Attack
	if (attackType == "Y" || attackType == "y") {
		*p1Attack = p1.specialAttack();
		cout << p1.name() << " USES SPECIAL ATTACK! DAMAGE BOOSTED TO " << *p1Attack << endl;
		sleep_for(milliseconds(600));
	}
	cout << p2.name() << " DEFENDED HIMSELF, With the defense of " << *p2Defense << endl;
	sleep_for(milliseconds(600));

	//Determine hit or miss 
	if (*p1Attack > *p2Defense) {
		p2.beHit(*p1Attack - *p2Defense);
		cout << "ITS A HIT ! DEALING A DAMGE OF " << *p1Attack - *p2Defense << endl;
		sleep_for(milliseconds(600));
	}

	else {
		cout << "THE BOSS MISSED !" << endl;
		sleep_for(milliseconds(600));
	}

	//Clear memory 
	delete p1Attack;
	delete p2Defense;

	return 0;
}

//Battle between the hero and a monster
int battle(Hero& p1, Character& p2) {

	//Declare pointer
	int* heroSpecialUsed = new int(0);
	int* bossSpecialUsed = new int(0);
	string* attackType = new string("");
	int* tmp = new int(0);

	cout << "THE " << p1.pType() << " STEPED INTO THE ARENA !" << endl; 
	sleep_for(milliseconds(600));
	cout << "THE ENEMY IS....THE " << p2.name() << " !!" << endl; 
	sleep_for(milliseconds(600));
	cout << "THE BATTLE BEGINS !" << endl;
	sleep_for(milliseconds(600));

	while (p1.curHealth() > 0 && p2.curHealth() > 0) {
		
		cout << "Hero's health: " <<  p1.curHealth() << endl ;
		cout << "Monster's health: " << p2.curHealth() << endl << endl;
		sleep_for(milliseconds(600));

		cout << "Its Hero's turn " << endl;
		sleep_for(milliseconds(600));
		if (*heroSpecialUsed == 0) {
			cout << "Special Attack(Y/N) ? " << endl;
			cin >> *attackType;

			//Input validation
			while (cin.fail() || *attackType != "Y" && *attackType != "y" && *attackType !=  "N"  && *attackType != "n") {
				cout << "Please enter a valid input(Y/N)" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> *attackType;
			}

		}

		if (*attackType == "Y" || *attackType == "y") {
			*heroSpecialUsed = 1;
		}


		//Hero attack monster
		heroAttack(p1, p2, *attackType);
		cout << endl;

		//Break the loop if the monster is dead.
		if (p2.curHealth() < 1) {
			cout << p2.name() << " IS SLAYED !" << endl;
			sleep_for(milliseconds(600));
			break;
		}

		//Monster attack hero 
		//If its a boss. Boss choose attack type 
		//Produce a random number of 0-2 (Boss has 1/3 chance to use special attack
		srand(time(NULL));
		*tmp = rand() % 2 + 0;

		//Set attackType Back to N
		*attackType = "N";

		//If the specialAttack is not used
		if (bossSpecialUsed = 0) {
			//If the random number is 0 
			if (*tmp = 0) {
				//Change attackType
				*attackType = "Y";
			}
		}

		cout << "Its Monster's turn " << endl;
		sleep_for(milliseconds(600));
		monsterAttack(p2, p1);
		cout << endl;

	}

	cout << p1.displayCharacter();
	cout << endl;

	//If the hero survived 
	if (p1.curHealth() > 0) {
		reward(p1);
		cout  << p1.displayCharacter()<< endl; 
	}

	//Remove memory
	delete tmp; 
	delete attackType;
	delete heroSpecialUsed;
	delete bossSpecialUsed; 
	
	return 0;

}

//Battle between hero and boss
int bossBattle(Hero& p1, Boss& p2) {
	//Declare variables 
	int* heroSpecialUsed = new int(0);
	int* bossSpecialUsed = new int(0);
	string* attackType = new string("");
	int* tmp = new int(0);

	cout << "THE " << p1.pType() << " STEPED INTO THE ARENA FOR HIS FINAL BATTLE!" << endl;
	sleep_for(milliseconds(600));
	cout << "THE FINAL ENEMY IS....THE " << p2.name() << " !!" << endl;
	sleep_for(milliseconds(600));
	cout << "THE FINAL BATTLE BEGINS !" << endl;
	sleep_for(milliseconds(600));

	cout << p1.displayCharacter();
	cout << endl;
	cout << p2.displayCharacter();

	//Loop when both are alive 
	while (p1.curHealth() > 0 && p2.curHealth() > 0) {

		cout << "Hero's health: " << p1.curHealth() << endl;
		cout << "Monster's health: " << p2.curHealth() << endl << endl;
		sleep_for(milliseconds(600));

		cout << "Its Hero's turn " << endl;
		sleep_for(milliseconds(600));
		if (*heroSpecialUsed == 0) {
			*heroSpecialUsed = 1;
			cout << "Special Attack(Y/N) ? " << endl;
			cin >> *attackType;

			//Input validation
			while (cin.fail() || *attackType != "Y" && *attackType != "y" && *attackType != "N"  && *attackType != "n") {
				cout << "Please enter a valid input(Y/N)" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> *attackType;
			}
		}

		//Hero attack monster
		heroAttack(p1, p2, *attackType);
		cout << endl;

		//Break the loop if the monster is dead.
		if (p2.curHealth() < 1) {
			cout << p2.name() << " IS SLAYED !" << endl;
			sleep_for(milliseconds(600));
			break;
		}

		//Monster attack hero 
		//If its a boss. Boss choose attack type 
		//Produce a random number of 1-3 (Boss has 1/3 chance to use special attack
		random_device rd;
		mt19937 rng(rd());
		uniform_int_distribution<int> uni(1, 3);
		*tmp = uni(rng);
		//Set attackType Back to N
		*attackType = "N";

		//If the specialAttack is not used
		if (*bossSpecialUsed == 0) {
			//If the random number is 0 
			if (*tmp == 1) {
				//Change attackType
				*attackType = "Y";
				*bossSpecialUsed = 1; 

			}
		}

		cout << "Its Monster's turn " << endl;
		sleep_for(milliseconds(600));
		bossAttack(p2, p1, *attackType);
		cout << endl;

	}

	delete tmp;
	delete attackType;
	delete heroSpecialUsed;
	delete bossSpecialUsed;

	return 0;

}

//Upgrade hero's stat after every battle
int reward(Hero& p1) {

	int* tmp = new int(0);

	cout << "Hero gained : ";

	//Add money 
	cout << p1.curHealth() << " $$" << endl;
	p1.addMoney(p1.curHealth());


	//Add hp. Add up never exceed maxHealth. 
	if (p1.curHealth() + 20 > p1.maxHealth()) {
		cout << p1.maxHealth() - p1.curHealth() << " hp recovered" << endl;
		p1.addHealth(p1.maxHealth() - p1.curHealth());
	}
	else {
		cout << "20 hp recovered" << endl;
		p1.addHealth(20);
	}

	//Initialize Random machine
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni(0, 2);

	//Add attack. never exceed 10 
	*tmp = (uni(rng));
	//If reached 10 
	if (p1.getAttackVal() == 10) {
		cout << "Maxinum attack reached" << endl;
	}
	//If summed up less than 10 
	else if (p1.getAttackVal() + *tmp <= 10) {
		cout << *tmp << " Attack point" << endl;
		p1.addAttack(*tmp);
	}
	//If summed up more than 10 
	else if (p1.getAttackVal() + *tmp > 10) {
		//Add until 10 
		cout << *tmp << "  Attack point (Max)" << endl;
		p1.addAttack(10 - p1.attack());
	}
	else {
		cout << "Maxinum attack reached" << endl;
	}


	//Add sAtk. never exceed 10
	*tmp = uni(rng);
	if (p1.getSpecialAttackVal() == 10) {
		cout << "Maxinum special attack reached" << endl;
	}
	else if (p1.getSpecialAttackVal() + *tmp <= 10) {
		cout << *tmp << " Special Attack point" << endl;
		p1.addsAttack(*tmp);
	}
	else if (p1.getSpecialAttackVal() + *tmp > 10) {
		//Add until 10 
		cout << *tmp << " Special Attack point (Max)" << endl;
		p1.addsAttack(10 - p1.attack());
	}
	else {
		cout << "Maxinum special attack reached" << endl;
	}


	//Add def. never exceed 10
	*tmp = (uni(rng));

	if (p1.getDefenseVal() == 10) {
		cout << "Maxinum defense reached" << endl;
	}
	else if (p1.getDefenseVal() + *tmp <= 10) {
		cout << *tmp << " Defense point" << endl;
		p1.addDef(*tmp);
	}
	else if (p1.getDefenseVal() + *tmp > 10) {
		//Add until 10 
		cout << *tmp << "  Defense point (Max)" << endl;
		p1.addDef(10 - p1.attack());
	}
	else {
		cout << "Maxinum defense reached" << endl;
	}


	delete tmp;

	return 0;
}

//Shop for hero after every battle
int shop(Hero& p1) {

	int* choice = new int(0);

	cout << "Welcome to the battle shop ! " << endl;
	cout << "Any of these suits you ? " << endl;

	cout << "[0]No thanks, real hero needs no help !" << endl;
	cout << "[1]Dragon blood    Max health      +5  45$" << endl;
	cout << "[2]Ironide         Recover health  +10 40$" << endl;
	cout << "[3]Boost Juice     Attack          +2  40$" << endl;
	cout << "[4]Elves water     Special Attack  +2  40$" << endl;
	cout << p1.displayCharacter();
	cin >> *choice;

	//Loop until user decide to leave the shop
	while (*choice != 0) {
		sleep_for(milliseconds(600));
		
		if (*choice == 0) {
			return 0;
		}
		else if (*choice == 1) {

			if (p1.priceMoney() >= 45) {
				//Increase hero stat
				p1.addMaxHealth(5);

				//Deduct money
				p1.deductMoney(45);
				cout << "Dragon blood purchased !" << endl;
				cout << "Current max health: " << p1.maxHealth() << endl;
			}
			else {
				cout << "Insufficient fund " << endl;
			}
		}
		else if (*choice == 2) {

			//If hero already has max health
			if (p1.curHealth() == p1.maxHealth()) {
				cout << "You health is full" << endl;
			}
			//If exceed health
			else if (p1.curHealth() + 10 > p1.maxHealth()) {
				if (p1.priceMoney() >= 40) {
					//Deduct money 
					p1.deductMoney(40);
					p1.addHealth(p1.maxHealth() - p1.curHealth());
					cout << "Dragon blood purchased !" << endl;
					cout << "Current health: " << p1.curHealth() << endl;
					

				}
				else {
					cout << "Insufficient fund " << endl;
				}

			}
			else {
				//Add 10 to health
				if (p1.priceMoney() >= 40) {
					//Deduct money 
					p1.deductMoney(40);
					p1.addHealth(10);
					cout << "Dragon blood purchased !" << endl;
					cout << "Current health: " << p1.curHealth() << endl;
					

				}
				else {
					cout << "Insufficient fund " << endl;
				}
			}
		}
		else if (*choice == 3) {
			if (p1.priceMoney() >= 40 && p1.getAttackVal() <= 8) {
				//Deduct money 
				p1.deductMoney(40);
				p1.addAttack(2);
				cout << "Spinach purchased !" << endl;
				cout << "Current Attack: " << p1.getAttackVal() << endl;
				
			}
			else if (p1.getAttackVal() == 9) {
				//Deduct money 
				p1.deductMoney(40);
				p1.addAttack(1);
				cout << "Spinach purchased !" << endl;
				cout << "Current Attack: " << p1.getAttackVal() << endl;
				

			}
			else if (p1.getAttackVal() >= 10) {
				cout << "You have reached maxinum attack" << endl;
			}
			else {
				cout << "Insufficient fund " << endl;
			}
		}
		else if (*choice == 4) {
			if (p1.priceMoney() >= 40 && p1.getSpecialAttackVal() <= 8) {
				//Deduct money 
				p1.deductMoney(40);
				p1.addsAttack(2);
				cout << "Elves Water purchased !" << endl;
				cout << "Current Special Attack: " << p1.getSpecialAttackVal() << endl;
				
			}
			else if (p1.getSpecialAttackVal() >= 10) {
				cout << "You have reached maxinum special attack" << endl;
			}
			else if (p1.getSpecialAttackVal() == 9) {
				//Deduct money 
				p1.deductMoney(40);
				p1.addsAttack(1);
				cout << "Elves Water purchased !" << endl;
				cout << "Current Special Attack: " << p1.getSpecialAttackVal() << endl;
			

			}
			else {
				cout << "Insufficient fund " << endl;
			}

		}
		else {
			cout << "Choice not found" << endl;
		}

		cout << p1.displayCharacter();
		cout << "[0] That's enough for me. Cheers !" << endl;
		cout << "[1]Dragon blood    Max health      +5  45$" << endl;
		cout << "[2]Ironide         Recover health  +10 40$" << endl;
		cout << "[3]Boost Juice     Attack          +2  40$" << endl;
		cout << "[4]Elves water     Special Attack  +2  40$" << endl;
		cin >> *choice;

		
	} //While

	cout << "Hero's stats" << p1.displayCharacter() << endl;
	sleep_for(milliseconds(600));

	delete choice; 
	return 0;
}



#pragma once
#include "BossEnemy.h"
#include "Hero.h"
#include "Hunter.h"
#include "Mage.h"
#include "Warrior.h"
class GameManager {
private:
	int rowGameManager, columnGameManager, rowPassage, columnPassage;
	Hero * heroType;
	void print();
	void generateRandomsForNewRoom();
	void enemyAttackHero();
	void heroAttackEnemy();
	void printEnemy();
	void printEnemyAttributes();
	void printHeroAttributes();
	void enemyStrength(int);
	void chooseHero(int);
	void setNextHeroLevel();
	void enemyMuve();
	void HeroHpRegen(int);
	void gameOver();
public:
	GameManager(int);
	void threadPrintInterface();
	void threadMuveHero();
};


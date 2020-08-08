#include "GameManager.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace std;

bool enemyShow = false;
bool endGame = false;
int randomNumber(int minNumber, int maxNumber);

vector<Enemy*>enemy;

int rowPrint, columnPrint, numberOfEnemy, enemyAttackRandom, enemyArrmorRandom, enemyHealthRandom, enemyExp, enemyLvl;
int bossEnemyAttackRandom, bossEnemyArrmorRandom, bossEnemyHealthRandom, bossEnemyExp, bossEnemyLvl;
const int rowDefault = 16, columnDefault = 34;

GameManager::GameManager(int typeHero) {
	endGame = false;
	srand((unsigned)time(0));
	chooseHero(typeHero);
	rowPassage = randomNumber(3, rowGameManager - 3);
	columnPassage = randomNumber(3, columnGameManager - 3);
	rowGameManager = rowDefault;
	columnGameManager = columnDefault;
	numberOfEnemy = randomNumber(2, 6);
	for (int i = 0; i < numberOfEnemy; i++) {
		int enemyRedRnd = randomNumber(1, rowGameManager - 2);
		int enemyKolonaRnd = randomNumber(1, columnGameManager - 2);
		enemyStrength(heroType->getAttributes()->getLevel());
		if (i == 0) {
			enemy.push_back(new BossEnemy(enemyRedRnd, enemyKolonaRnd, bossEnemyHealthRandom, bossEnemyAttackRandom, bossEnemyArrmorRandom, bossEnemyLvl, bossEnemyExp, 'B'));
		}
		else {
			enemy.push_back(new Enemy(enemyRedRnd, enemyKolonaRnd, enemyHealthRandom, enemyAttackRandom, enemyArrmorRandom, enemyLvl, enemyExp, 'e'));
		}
	}
}

void GameManager::print() {
	for (rowPrint = 0; rowPrint < rowGameManager; rowPrint++) {
		for (columnPrint = 0; columnPrint < columnGameManager; columnPrint++) {
			bool Passage = false;
			if ((rowPrint == 0 || rowPrint == rowGameManager - 1) || (columnPrint == 0 || columnPrint == columnGameManager - 1)) {
				if ((columnPrint == columnGameManager - 1 && rowPrint == rowPassage) || (rowPrint == rowGameManager - 1 && columnPrint == columnPassage)) {
					Passage = true;
					cout << static_cast<unsigned char>(177);
				}
				else if (!Passage) {
					cout << static_cast<unsigned char>(219);
				}
			}
			else if (rowPrint == heroType->getRowHero() && columnPrint == heroType->getColumnHero()) {
				cout << heroType->getLogo();
			}
			else if ((heroType->getColumnHero() == columnGameManager - 1 && heroType->getRowHero() == rowPassage) || (heroType->getRowHero() == rowGameManager - 1 && heroType->getColumnHero() == columnPassage)) {
				generateRandomsForNewRoom();
			}
			else {
				enemyShow = false;
				printEnemy();
				if (!enemyShow) {
					cout << static_cast<unsigned char>(250);
				}
			}
		}
		cout << endl;
	}
}

void GameManager::threadPrintInterface() {
	while (!endGame) {
		print();
		printHeroAttributes();
		printEnemyAttributes();
		enemyMuve();
		enemyAttackHero();
		HeroHpRegen(heroType->getAttributes()->getLevel());
		gameOver();
		Sleep(220);
		system("cls");
	}
}

void GameManager::threadMuveHero(){
	while (!endGame) {
		gameOver();
		heroType->muveHero(rowGameManager, columnGameManager, rowPassage, columnPassage, enemy);
		heroAttackEnemy();
	}
}

void GameManager::generateRandomsForNewRoom() {
	heroType->setColumnHero(1);
	heroType->setRowHero(1);
	enemy.clear();
	rowGameManager = randomNumber(rowDefault / 2, rowDefault);
	columnGameManager = randomNumber(columnDefault / 2, columnDefault);
	rowPassage = randomNumber(1, rowGameManager - 3);
	columnPassage = randomNumber(1, columnGameManager - 3);
	numberOfEnemy = randomNumber(2, 6);
	for (int i = 0; i < numberOfEnemy; i++) {
		int enemyRedRnd = randomNumber(1, rowGameManager - 2);
		int enemyKolonaRnd = randomNumber(1, columnGameManager - 2);
		enemyStrength(heroType->getAttributes()->getLevel());
		if (i == 0) {
			enemy.push_back(new BossEnemy(enemyRedRnd, enemyKolonaRnd, bossEnemyHealthRandom, bossEnemyAttackRandom, bossEnemyArrmorRandom, bossEnemyLvl, bossEnemyExp, 'B'));
		}
		else {
			enemy.push_back(new Enemy(enemyRedRnd, enemyKolonaRnd, enemyHealthRandom, enemyAttackRandom, enemyArrmorRandom, enemyLvl, enemyExp, 'e'));
		}
		enemy.at(i)->setEnemyHitWallRow(false);
		enemy.at(i)->setEnemyHitWallColumn(false);
	}
}

void GameManager::enemyAttackHero() {
	for (int i = 0; i < enemy.size(); i++) {
		if ((heroType->getRowHero() == enemy.at(i)->getRowEnemy() - 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy() + 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy())
			&& (heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() - 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() + 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy())) {
			heroType->getAttributes()->setReduceHealth(enemy.at(i)->getAttributesEnemy()->getAttack());
		}
	}
}

void GameManager::heroAttackEnemy() {
	for (int i = 0; i < enemy.size(); i++) {
		if ((heroType->getRowHero() == enemy.at(i)->getRowEnemy() - 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy() + 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy())
			&& (heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() - 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() + 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy())) {
			if (heroType->getButton() == 32) {
				enemy.at(i)->getAttributesEnemy()->setReduceHealth(heroType->getAttributes()->getAttack());
				if (enemy.at(i)->getAttributesEnemy()->getHealth() <= 0) {
					setNextHeroLevel();
					enemy.erase(enemy.begin() + i);
				}
			}
		}
	}
}

void GameManager::printEnemy() {
	for (int i = 0; i < enemy.size(); i++) {
		if (rowPrint == enemy.at(i)->getRowEnemy() && columnPrint == enemy.at(i)->getColumnEnemy()) {
			cout << enemy.at(i)->getLogo();
			enemyShow = true;
		}
	}
}

void GameManager::printEnemyAttributes() {
	for (int i = 0; i < enemy.size(); i++) {
		if ((heroType->getRowHero() == enemy.at(i)->getRowEnemy() - 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy() + 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy())
			&& (heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() - 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() + 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy())) {
			cout << "Enemy " <<enemy.at(i)->getLogo() << " stats" << endl << " Health: " << enemy.at(i)->getAttributesEnemy()->getHealth() << "/" << enemy.at(i)->getAttributesEnemy()->getMaxHealth() << endl << " Attack: " << enemy.at(i)->getAttributesEnemy()->getAttack() << endl << " Armor: "
				<< enemy.at(i)->getAttributesEnemy()->getArmor() << endl << " Level: " << enemy.at(i)->getAttributesEnemy()->getLevel() << endl << " Experience: " << enemy.at(i)->getAttributesEnemy()->getExperience() << endl;
			break;
		}
	}
}

void GameManager::printHeroAttributes() {
	cout << "Hero stats for " << heroType->getLogo() << endl << " Health: " << heroType->getAttributes()->getHealth() << "/" << heroType->getAttributes()->getMaxHealth() << endl << " Attack: " << heroType->getAttributes()->getAttack() << endl << " Armor: "
		<< heroType->getAttributes()->getArmor() << endl << " Level: " << heroType->getAttributes()->getLevel() << endl << " Experience: " << heroType->getAttributes()->getExperience() << "/" << heroType->getAttributes()->getMaxExperience() << endl;
}

void GameManager::enemyStrength(int heroLevel) {
	if (heroLevel >= 1 || heroLevel <= 3) {
		enemyHealthRandom = randomNumber(45, 55);
		enemyAttackRandom = randomNumber(15, 19);
		enemyArrmorRandom = randomNumber(2, 4);
		enemyExp = 0;
		enemyLvl = 0;
		bossEnemyHealthRandom = randomNumber(65, 70);
		bossEnemyAttackRandom = randomNumber(30, 39);
		bossEnemyArrmorRandom = randomNumber(8, 10);
		bossEnemyLvl = 2;
		bossEnemyExp = 0;
	}
	else if (heroLevel >= 4 || heroLevel <= 7) {
		enemyHealthRandom = randomNumber(50, 70);
		enemyAttackRandom = randomNumber(20, 27);
		enemyArrmorRandom = randomNumber(5, 8);
		enemyExp = 0;
		enemyLvl = 1;
		bossEnemyHealthRandom = randomNumber(75, 90);
		bossEnemyAttackRandom = randomNumber(42, 51);
		bossEnemyArrmorRandom = randomNumber(11, 15);
		bossEnemyLvl = 4;
		bossEnemyExp = 0;
	}
	else if (heroLevel >= 8 || heroLevel <= 12) {
		enemyHealthRandom = randomNumber(68, 90);
		enemyAttackRandom = randomNumber(26, 34);
		enemyArrmorRandom = randomNumber(9, 13);
		enemyExp = 0;
		enemyLvl = 2;
		bossEnemyHealthRandom = randomNumber(96, 115);
		bossEnemyAttackRandom = randomNumber(54, 65);
		bossEnemyArrmorRandom = randomNumber(16, 21);
		bossEnemyLvl = 6;
		bossEnemyExp = 0;
	}
	else if (heroLevel >= 13 || heroLevel <= 17) {
		enemyHealthRandom = randomNumber(87, 110);
		enemyAttackRandom = randomNumber(39, 49);
		enemyArrmorRandom = randomNumber(12, 16);
		enemyExp = 0;
		enemyLvl = 3;
		bossEnemyHealthRandom = randomNumber(123, 154);
		bossEnemyAttackRandom = randomNumber(69, 73);
		bossEnemyArrmorRandom = randomNumber(22, 28);
		bossEnemyLvl = 8;
		bossEnemyExp = 0;
	}
	else if (heroLevel >= 18 || heroLevel <= 21) {
		enemyHealthRandom = randomNumber(105, 143);
		enemyAttackRandom = randomNumber(42, 68);
		enemyArrmorRandom = randomNumber(18, 20);
		enemyExp = 0;
		enemyLvl = 4;
		bossEnemyHealthRandom = randomNumber(160, 184);
		bossEnemyAttackRandom = randomNumber(70, 81);
		bossEnemyArrmorRandom = randomNumber(29, 33);
		bossEnemyLvl = 10;
		bossEnemyExp = 0;
	}
	else if (heroLevel >= 22 || heroLevel <= 30) {
		enemyHealthRandom = randomNumber(115, 200);
		enemyAttackRandom = randomNumber(70, 98);
		enemyArrmorRandom = randomNumber(20, 28);
		enemyExp = 0;
		enemyLvl = 5;
		bossEnemyHealthRandom = randomNumber(240, 350);
		bossEnemyAttackRandom = randomNumber(100, 123);
		bossEnemyArrmorRandom = randomNumber(34, 46);
		bossEnemyLvl = 12;
		bossEnemyExp = 0;
	}
}

void GameManager::chooseHero(int typeHero) {
	if (typeHero == 1) {
		heroType = new Hunter(1, 1, 200, 21, 10, 1, 0, 'H');
	}
	else if (typeHero == 2) {
		heroType = new Mage(1, 1, 175, 18, 15, 1, 0, 'M');
	}
	else if (typeHero == 3) {
		heroType = new Warrior(1, 1, 270, 25, 6, 1, 0, 'W');
	}
}

void GameManager::setNextHeroLevel() {
	int tempHeroLevel = heroType->getAttributes()->getLevel();
	heroType->getAttributes()->setExperience();
	heroType->getAttributes()->setAttack(heroType->getAttributes()->getLevel());
	heroType->getAttributes()->setArmor(heroType->getAttributes()->getLevel());
	heroType->getAttributes()->setLevel();
	if (tempHeroLevel != heroType->getAttributes()->getLevel()) {
		heroType->getAttributes()->setHealthOnLevel();
	}
}

void GameManager::enemyMuve() {
	for (int i = 0; i < enemy.size(); i++) {
		for (int j = 1; j < enemy.size() - 1; j++) {
			if ((enemy.at(i)->getRowEnemy() == enemy.at(j)->getRowEnemy() + 1) || (enemy.at(i)->getRowEnemy() == enemy.at(j)->getRowEnemy() - 1) || (enemy.at(i)->getRowEnemy() == enemy.at(j)->getRowEnemy()) && (enemy.at(i)->getColumnEnemy() == enemy.at(j)->getColumnEnemy())) {
				enemy.at(i)->setEnemyHitWallRow(!enemy.at(i)->getEnemyHitWallRow());
			}
			else if ((enemy.at(i)->getColumnEnemy() == enemy.at(j)->getColumnEnemy() + 1) || (enemy.at(i)->getColumnEnemy() == enemy.at(j)->getColumnEnemy() - 1) || (enemy.at(i)->getColumnEnemy() == enemy.at(j)->getColumnEnemy()) && (enemy.at(i)->getRowEnemy() == enemy.at(j)->getRowEnemy())) {
				enemy.at(i)->setEnemyHitWallColumn(!enemy.at(i)->getEnemyHitWallColumn());
			}
		}
		if ((heroType->getRowHero() == enemy.at(i)->getRowEnemy() - 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy() + 1 || heroType->getRowHero() == enemy.at(i)->getRowEnemy())
			&& (heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() - 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy() + 1 || heroType->getColumnHero() == enemy.at(i)->getColumnEnemy())) {
			continue;
		}
		else {
			if (!enemy.at(i)->getEnemyHitWallRow()) {
				if (enemy.at(i)->getRowEnemy() == rowGameManager - 2) {
					enemy.at(i)->setEnemyHitWallRow(true);
					break;
				}
				enemy.at(i)->setRowEnemy(enemy.at(i)->getRowEnemy() + 1);
			}
			else if (!enemy.at(i)->getEnemyHitWallColumn()) {
				if (enemy.at(i)->getColumnEnemy() == columnGameManager - 2) {
					enemy.at(i)->setEnemyHitWallColumn(true);
					break;
				}
				enemy.at(i)->setColumnEnemy(enemy.at(i)->getColumnEnemy() + 1);
			}
			if (enemy.at(i)->getEnemyHitWallRow()) {
				if (enemy.at(i)->getRowEnemy() == 1) {
					enemy.at(i)->setEnemyHitWallRow(false);
					break;
				}
				enemy.at(i)->setRowEnemy(enemy.at(i)->getRowEnemy() - 1);
			}
			else if (enemy.at(i)->getEnemyHitWallColumn()) {
				if (enemy.at(i)->getColumnEnemy() == 1) {
					enemy.at(i)->setEnemyHitWallColumn(false);
					break;
				}
				enemy.at(i)->setColumnEnemy(enemy.at(i)->getColumnEnemy() - 1);
			}
		}
	}
}

void GameManager::HeroHpRegen(int heroLevel) {
	if (heroLevel >= 1 || heroLevel <= 3) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(1);
		}
	}
	else if (heroLevel >= 4 || heroLevel <= 7) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(2);
		}
	}
	else if (heroLevel >= 8 || heroLevel <= 12) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(3);
		}
	}
	else if (heroLevel >= 13 || heroLevel <= 17) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(4);
		}
	}
	else if (heroLevel >= 18 || heroLevel <= 21) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(5);
		}
	}
	else if (heroLevel >= 22 || heroLevel <= 30) {
		if (heroType->getAttributes()->getHealth() < heroType->getAttributes()->getMaxHealth()) {
			heroType->getAttributes()->setHealth(6);
		}
	}
}

void GameManager::gameOver() {
	if (heroType->getAttributes()->getHealth() <= 0) {
		endGame = true;
		delete heroType;
		enemy.clear();
	}
	else if (heroType->getButton() == 27) {
		endGame = true;
		delete heroType;
		enemy.clear();
	}
}

int randomNumber(int minNumber, int maxNumber) {
	return (rand() % (maxNumber - minNumber)) + minNumber;
}
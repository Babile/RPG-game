#include "Hero.h"
#include "Attributes.h"
#include <conio.h>

char inputCharacter;

Hero::Hero(int r, int c, int helt, int attk, int arm, int lvl, int exp, char lg) {
	logo = lg;
	rowHero = r;
	columnHero = c;
	atrributes = new Attributes(helt, attk, arm, lvl, exp);
}

int Hero::getRowHero() {
	return rowHero;
}

int Hero::getColumnHero() {
	return columnHero;
}

void Hero::setRowHero(int rowHeroInput) {
	rowHero = rowHeroInput;
}

void Hero::setColumnHero(int columnHeroInput) {
	columnHero = columnHeroInput;
}

char Hero::getButton() {
	return inputCharacter;
}

char Hero::getLogo() {
	return logo;
}

Attributes* Hero::getAttributes() {
	return atrributes;
}

void Hero::muveHero(int rowGameManager, int columnGameManager, int rowPassage, int columnPassage, vector<Enemy*> enemy) {
	inputCharacter = _getch();
	switch (inputCharacter) {
	case 'w': case 'W':
		if (rowHero == 1) {
			return;
		}
		for (int i = 0; i < enemy.size(); i++) {
			if (rowHero - 1 == enemy.at(i)->getRowEnemy() && columnHero == enemy.at(i)->getColumnEnemy()) {
				return;
			}
		}
		rowHero--;
		break;
	case 's': case 'S':
		if ((rowHero == rowGameManager - 2) && (columnHero != columnPassage)) {
			return;
		}
		for (int i = 0; i < enemy.size(); i++) {
			if (rowHero + 1 == enemy.at(i)->getRowEnemy() && columnHero == enemy.at(i)->getColumnEnemy()) {
				return;
			}
		}
		rowHero++;
		break;
	case 'a': case 'A':
		if (columnHero == 1) {
			return;
		}
		for (int i = 0; i < enemy.size(); i++) {
			if (rowHero == enemy.at(i)->getRowEnemy() && columnHero - 1 == enemy.at(i)->getColumnEnemy()) {
				return;
			}
		}
		columnHero--;
		break;
	case 'd': case 'D':
		if ((columnHero == columnGameManager - 2) && (rowHero != rowPassage)) {
			return;
		}
		for (int i = 0; i < enemy.size(); i++) {
			if (rowHero == enemy.at(i)->getRowEnemy() && columnHero + 1 == enemy.at(i)->getColumnEnemy()) {
				return;
			}
		}
		columnHero++;
		break;
	default:
		break;
	}
}
